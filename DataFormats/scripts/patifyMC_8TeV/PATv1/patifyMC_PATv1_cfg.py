import FWCore.ParameterSet.Config as cms

process = cms.Process("PATIFY")

process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring(
    "/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_AOD_v2/pakhotin/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v3/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_AOD_v2/2d78404b872edb8cc4e80b73fda3bcfb/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_AOD_100_1_ZYB.root"
  )
)
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

process.MessageLogger = cms.Service("MessageLogger",
  destinations = cms.untracked.vstring("cout"),
  cout = cms.untracked.PSet(threshold = cms.untracked.string("ERROR"))
)

process.load("Configuration/StandardSequences/FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:startup_GRun', '')

process.load("AnalysisDataFormats.MuJetAnalysis.RECOtoPAT_cff")
process.patMuons.addGenMatch = cms.bool(True)
process.patMuons.embedGenMatch = cms.bool(True)
process.Path = cms.Path(process.patifyMC)

process.load("AnalysisDataFormats.MuJetAnalysis.EventContent_version8_cff")
process.patOutput.fileName = cms.untracked.string("output.root")
process.EndPath = cms.EndPath(process.patOutput)

process.schedule = cms.Schedule(process.Path, process.EndPath)
