import FWCore.ParameterSet.Config as cms

process = cms.Process("PATIFY")
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring("/store/data/Run2010B/Mu/RECO/Dec22ReReco_v1/0047/70529068-F012-E011-B717-0022199305B1.root"))

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.MessageLogger = cms.Service("MessageLogger", destinations = cms.untracked.vstring("cout"), cout = cms.untracked.PSet(threshold = cms.untracked.string("ERROR")))

process.load("Configuration/StandardSequences/FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = "FT_R_44_V11::All"

process.HighPtBarrelMuonFilter = cms.EDFilter("HighPtBarrelMuonFilter")

process.EventCounterForCRAB = cms.EDAnalyzer("EventCounterForCRAB")
process.EventCounterPath = cms.Path(process.EventCounterForCRAB)

process.load("AnalysisDataFormats.MuJetAnalysis.RECOtoPAT_cff")
process.patMuons.addGenMatch = cms.bool(False)
process.patMuons.embedGenMatch = cms.bool(False)
process.countPatMuons.minNumber = cms.uint32(2)
process.Path = cms.Path(process.HighPtBarrelMuonFilter * process.patifyData)

process.load("AnalysisDataFormats.MuJetAnalysis.EventContent_version7_cff")
process.patOutput.fileName = cms.untracked.string("output.root")
process.patOutput.SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring("Path"))
process.EndPath = cms.EndPath(process.patOutput)

process.schedule = cms.Schedule(process.EventCounterPath, process.Path, process.EndPath)
