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
process.GlobalTag = GlobalTag(process.GlobalTag, '92X_dataRun2_Prompt_v11')
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("MuJetAnalysis.DataFormats.miniAODtoPAT_cff")
process.load("MuJetAnalysis.MuJetProducer.MuJetProducer_cff")
process.load("MuJetAnalysis.CutFlowAnalyzer.CutFlowAnalyzer_MiniAOD_cff")
process.load("MuJetAnalysis.CutFlowAnalyzer.BaseLineSelectionFilter_MiniAOD_cfi")

process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
        #'file:/fdata/hepx/store/user/dildick/DoubleMuon/crab_DoubleMuon-Run2017C-PromptReco-v1-SKIM-20171206/171206_225208/0000/Filter_135.root',
        #'file:/fdata/hepx/store/user/dildick/MET/crab_MET-Run2017C-PromptReco-v1-SKIM-20171129/171130_025209/0000/Filter_135.root'
        #'file:/fdata/hepx/store/user/dildick/MET/crab_MET-Run2017F-PromptReco-v1-SKIM-20171129/171130_025541/0000/Filter_102.root'
        'file:/fdata/hepx/store/user/dildick/DoubleMuon/crab_DoubleMuon-Run2017D-PromptReco-v1-SKIM-20171206/171206_225345/0000/Filter_1.root'
        )
)

process.out = cms.OutputModule(
    "PoolOutputModule",
    fileName = cms.untracked.string('patTuple.root')
    )

### Add MuJet Dataformats
from MuJetAnalysis.DataFormats.EventContent_version11_cff import *
process = customizePatOutput(process)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

runOnData = True
if runOnData: process.patifySelect = cms.Sequence(process.patifyData)
else:         process.patifySelect = cms.Sequence(process.patifyMC)

process.dump=cms.EDAnalyzer('EventContentAnalyzer')

process.p = cms.Path(
    process.baseLineSelectionFilter *
    process.patifySelect *
    process.MuJetProducers *
#    process.dump *
    process.cutFlowAnalyzers
    )

#process.outpath = cms.EndPath(process.out)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("out_ana.root")
)
