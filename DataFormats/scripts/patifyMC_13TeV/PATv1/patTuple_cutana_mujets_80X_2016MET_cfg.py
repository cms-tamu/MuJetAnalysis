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
process.GlobalTag = GlobalTag(process.GlobalTag, '80X_dataRun2_2016LegacyRepro_v3')
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("MuJetAnalysis.CutFlowAnalyzer.FilterSample3RecoMu_cfi")
process.load("MuJetAnalysis.DataFormats.RECOtoPAT_cff")
process.load("MuJetAnalysis.MuJetProducer.MuJetProducer_cff")
process.load("MuJetAnalysis.CutFlowAnalyzer.CutFlowAnalyzer_2016MET_cff")
process.load("MuJetAnalysis.CutFlowAnalyzer.FilterSample3RecoMu_cfi")

process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
        #'file:/fdata/hepx/store/user/dildick/Run2016B_MET_AOD_23Sep2016_v3/00A94E9A-0F99-E611-8F0F-0CC47A4D76B8.root'
        'file:/fdata/hepx/store/user/dildick/MET/2016C/AOD/07Aug17/1CC7F855-2BAF-E711-B898-0CC47A4D766C.root'
    )
)

process.out = cms.OutputModule(
    "PoolOutputModule",
    fileName = cms.untracked.string('patTuple.root')
)

### Add MuJet Dataformats
from MuJetAnalysis.DataFormats.EventContent_version10_cff import *
process = customizePatOutput(process)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.p = cms.Path(
    process.tripleRecoMuFilter *
    process.patifyData *
    process.MuJetProducers *
    process.cutFlowAnalyzers
)

#process.outpath = cms.EndPath(process.out)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("out_ana.root")
)
