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
#Default run on data
#process.GlobalTag = GlobalTag(process.GlobalTag, '94X_mc2017_realistic_v14')
process.GlobalTag = GlobalTag(process.GlobalTag, '94X_dataRun2_v6')
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("MuJetAnalysis.DataFormats.miniAODtoPAT_cff")
process.load("MuJetAnalysis.MuJetProducer.MuJetProducer_MiniAOD_cff")
process.load("MuJetAnalysis.CutFlowAnalyzer.CutFlowAnalyzer_MiniAOD_cff")
process.load("MuJetAnalysis.CutFlowAnalyzer.BaseLineSelectionFilter_MiniAOD_cfi")

process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
        'file:/afs/cern.ch/work/w/wshi/public/RunII2017Analysis/CMSSW_9_4_7/src/E00B7630-A1AF-E811-AF7B-EC0D9A0B3260.root'
        )
)

process.out = cms.OutputModule(
    "PoolOutputModule",
    fileName = cms.untracked.string('patTuple.root')
    )

### Add MuJet Dataformats
from MuJetAnalysis.DataFormats.EventContent_version11_cff import *
process = customizePatOutput(process)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

#Default run on data
runOnData = True
if runOnData: process.patifySelect = cms.Sequence(process.patifyData)
else:         process.patifySelect = cms.Sequence(process.patifyMC)

process.dump=cms.EDAnalyzer('EventContentAnalyzer')

process.p = cms.Path(
#    process.baseLineSelectionFilter *
    process.patifySelect *
    process.MuJetProducers *
#    process.dump *
    process.cutFlowAnalyzers
    )

#process.outpath = cms.EndPath(process.out)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("out_ana.root")
)
