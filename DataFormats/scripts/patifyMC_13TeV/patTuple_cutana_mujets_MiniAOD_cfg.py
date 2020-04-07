import FWCore.ParameterSet.Config as cms

process = cms.Process("MUONJET")

## MessageLogger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
# verbose flags for the PF2PAT modules
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.options.allowUnscheduled = cms.untracked.bool(False)

## Geometry and Detector Conditions (needed for a few patTuple production steps)
process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")
process.load("Configuration.Geometry.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag

#Tags are specified here: https://twiki.cern.ch/twiki/bin/viewauth/CMS/PdmVAnalysisSummaryTable
#process.GlobalTag = GlobalTag(process.GlobalTag, '102X_upgrade2018_realistic_v20') #2018 MC
#process.GlobalTag = GlobalTag(process.GlobalTag, '102X_dataRun2_v12')              #2018 data: Era ABC
#process.GlobalTag = GlobalTag(process.GlobalTag, '102X_dataRun2_Prompt_v15')       #2018 data: Era D
process.GlobalTag = GlobalTag(process.GlobalTag, '94X_mc2017_realistic_v17')       #2017 MC
#process.GlobalTag = GlobalTag(process.GlobalTag, '94X_dataRun2_v11')               #2017 data

process.load("Configuration.StandardSequences.MagneticField_cff")
#process.load("MuJetAnalysis.DataFormats.miniAODtoPAT_cff")
process.load("PhysicsTools.PatAlgos.slimming.unpackedTracksAndVertices_cfi")
#process.load("MuJetAnalysis.MuJetProducer.MuJetProducer_MiniAOD_cff")#Pre-Run2 mu-jet cluster
process.load("MuJetAnalysis.MuJetProducer.MuJetProducerRun2_cff")#Run2 mu-jet cluster
process.load("MuJetAnalysis.CutFlowAnalyzer.CutFlowAnalyzer_MiniAOD_cff")

process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
        #'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIFall17MiniAODv2/MSSMD_mH_125_mN1_60_mGammaD_58_cT_0p1_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/00000/00D463FA-CE35-EA11-89D1-E0DB55FDAC6E.root',
        'root://cmsxrootd.fnal.gov//store/mc/RunIIFall17MiniAODv2/MSSMD_mH_125_mN1_60_mGammaD_10_cT_5_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/130000/BA79B464-7F5B-EA11-8332-001E67A42026.root'
        )
)

process.out = cms.OutputModule(
    "PoolOutputModule",
    fileName = cms.untracked.string('patTuple.root')
    )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.p = cms.Path(
    process.unpackedTracksAndVertices *
    process.MuJetProducers *
    process.cutFlowAnalyzers
    )

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("out_ana_1.root")
)
