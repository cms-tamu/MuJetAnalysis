import FWCore.ParameterSet.Config as cms

process = cms.Process("PATIFY")

process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring(
    "/store/data/Run2012A/DoubleMu/AOD/13Jul2012-v1/00000/FEADAE94-B9D2-E111-B484-002618943960.root"
  )
)
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

process.MessageLogger = cms.Service("MessageLogger",
  destinations = cms.untracked.vstring("cout"),
  cout = cms.untracked.PSet(threshold = cms.untracked.string("ERROR"))
)

process.load("Configuration/StandardSequences/FrontierConditions_GlobalTag_cff")
# Check latest Global Tag on twiki
# https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideFrontierConditions
process.GlobalTag.globaltag = "FT_53_V6_AN2::All"

process.HighPtBarrelMuonFilter = cms.EDFilter("HighPtBarrelMuonFilter")

process.EventCounterForCRAB = cms.EDAnalyzer("EventCounterForCRAB")
process.EventCounterPath = cms.Path(process.EventCounterForCRAB)

process.load("AnalysisDataFormats.MuJetAnalysis.RECOtoPAT_cff")
process.patMuons.addGenMatch = cms.bool(False)
process.patMuons.embedGenMatch = cms.bool(False)
process.countPatTrackerMuons.minNumber = cms.uint32(2)
process.countPatPFMuons.minNumber = cms.uint32(2)
process.Path = cms.Path(process.HighPtBarrelMuonFilter * process.patifyData)

process.load("AnalysisDataFormats.MuJetAnalysis.EventContent_version8_cff")
process.patOutput.fileName = cms.untracked.string("output.root")
process.patOutput.SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring("Path"))
process.EndPath = cms.EndPath(process.patOutput)

process.schedule = cms.Schedule(process.EventCounterPath, process.Path, process.EndPath)
