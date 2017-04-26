import FWCore.ParameterSet.Config as cms

process = cms.Process("MUONJET")

## MessageLogger
process.load("FWCore.MessageLogger.MessageLogger_cfi")

# verbose flags for the PF2PAT modules
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.options.allowUnscheduled = cms.untracked.bool(False)

## Geometry and Detector Conditions (needed for a few patTuple production steps)
process.load("Configuration.Geometry.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_data')
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("MuJetAnalysis.DataFormats.AODtoPAT_cff")
process.load("MuJetAnalysis.MuJetProducer.MuJetProducer_cff")
process.load("MuJetAnalysis.CutFlowAnalyzer.CutFlowAnalyzer_cff")

process.source = cms.Source ("PoolSource",
                              fileNames=cms.untracked.vstring(
                                'file:root://eoscms//eos/cms/store/group/alca_muonalign/lpernie/RUN_LOCALLY/2016D_00B6F73F-C889-E611-938D-A0369F7FC83C.root' #2016D
                              ),
                              skipEvents=cms.untracked.uint32(0)
                            )
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(10))

process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string('patTuple.root')
)

### Add MuJet Dataformats
from MuJetAnalysis.DataFormats.EventContent_version10_cff import *
process = customizePatOutput(process)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.p = cms.Path(
    process.patifyData *
    process.MuJetProducers *
    process.cutFlowAnalyzers_Data
)

#process.outpath = cms.EndPath(process.out)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("out_ana.root")
)
