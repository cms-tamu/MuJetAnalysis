import FWCore.ParameterSet.Config as cms

process = cms.Process("CutFlowAnalyzer")

process.load("MuJetAnalysis.CutFlowAnalyzer.CutFlowAnalyzer_cfi")
process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger = cms.Service("MessageLogger", 
    destinations = cms.untracked.vstring("cout"), 
    cout = cms.untracked.PSet(threshold = cms.untracked.string("ERROR"))
)

from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')

process.source = cms.Source("PoolSource",
    secondaryFileNames = cms.untracked.vstring(),
    fileNames = cms.untracked.vstring(
        'file:out_pat.root'
    )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100) 
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("out_ana.root")
)

process.p = cms.Path(
    process.cutFlowAnalyzer
)

