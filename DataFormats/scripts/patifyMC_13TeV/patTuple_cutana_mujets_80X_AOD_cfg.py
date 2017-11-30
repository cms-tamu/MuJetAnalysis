import FWCore.ParameterSet.Config as cms

process = cms.Process("MUONJET")

## MessageLogger
process.load("FWCore.MessageLogger.MessageLogger_cfi")

# verbose flags for the PF2PAT modules
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

## Geometry and Detector Conditions (needed for a few patTuple production steps)
process.load("Configuration.Geometry.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc')
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("MuJetAnalysis.DataFormats.AODtoPAT_cff")
process.load("MuJetAnalysis.MuJetProducer.MuJetProducer_cff")
process.load("MuJetAnalysis.CutFlowAnalyzer.CutFlowAnalyzer_cff")

process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
        'file:/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_1000_cT_020_14TeV/DarkSUSY_mH_125_mGammaD_1000_cT_020_13TeV_RECO_v2/170919_201313/0000/out_reco_1.root'
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
    process.patifyMC *
    process.MuJetProducers *
    process.cutFlowAnalyzers
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("out_ana.root")
)
