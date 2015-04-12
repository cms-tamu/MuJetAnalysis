import FWCore.ParameterSet.Config as cms

process = cms.Process("CutFlowAnalyzer")

# Input source
process.source = cms.Source("PoolSource",
    secondaryFileNames = cms.untracked.vstring(),
    fileNames = cms.untracked.vstring(
        'file:out_pat.root'
    )
)

process.maxEvents = cms.untracked.PSet( 
    input = cms.untracked.int32(100) 
)

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger = cms.Service("MessageLogger", 
    destinations = cms.untracked.vstring("cout"), 
    cout = cms.untracked.PSet(threshold = cms.untracked.string("ERROR"))
)

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = "MCRUN2_72_V3::All"

process.load("MuJetAnalysis.LeptonJetProducer.LeptonJetProducer_cff")
process.load("MuJetAnalysis.CutFlowAnalyzer.CutFlowAnalyzer_cfi")

process.p = cms.Path(
    process.TrackerMuJetProducer05 *
    process.PFMuJetProducer05 *
    process.cutFlowAnalyzer
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("out_ana.root")
)
