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
#process.GlobalTag = GlobalTag(process.GlobalTag, '94X_mc2017_realistic_v17')       #2017 MC
process.GlobalTag = GlobalTag(process.GlobalTag, '94X_dataRun2_v11')               #2017 data

process.load("Configuration.StandardSequences.MagneticField_cff")
#process.load("MuJetAnalysis.DataFormats.miniAODtoPAT_cff")
process.load("PhysicsTools.PatAlgos.slimming.unpackedTracksAndVertices_cfi")
#process.load("MuJetAnalysis.MuJetProducer.MuJetProducer_MiniAOD_cff")#Pre-Run2 mu-jet cluster
process.load("MuJetAnalysis.MuJetProducer.MuJetProducerRun2_cff")#Run2 mu-jet cluster
process.load("MuJetAnalysis.CutFlowAnalyzer.CutFlowAnalyzer_MiniAOD_cff")

process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
    'file:/scratch/user/ws13/2017TestData/FAC28F5A-C639-E811-B4BB-10604BA8FC24.root', #one file from /DoubleMuon/Run2017C-31Mar2018-v1/MINIAOD
    #'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIFall17MiniAODv2/MSSMD_mH_125_mN1_60_mGammaD_58_cT_0_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/120000/0228EDB3-A855-E911-8BCD-842B2B180C66.root',
    #'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIFall17MiniAODv2/MSSMD_mH_125_mN1_60_mGammaD_58_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/110000/02E71858-9C36-EA11-9831-0CC47A57CEB4.root',
    #'file:/home/ws13/Run2Analysis/CMSSW_10_2_18/src/MuJetAnalysis/DataFormats/scripts/patifyMC_13TeV/HIG-RunIIFall17MiniAODv2-03652.root' #private production of 400 events for 2017 mGammaD_25_cT_100
    #'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIFall17MiniAODv2/MSSMD_mH_125_mN1_60_mGammaD_25_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/260000/0C6708F8-CE5D-EA11-AE6D-B8CA3A709648.root',
    #'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIFall17MiniAODv2/MSSMD_mH_125_mN1_60_mGammaD_25_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/260000/143727A9-125E-EA11-B92A-801844DF001C.root',
    #'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIFall17MiniAODv2/MSSMD_mH_125_mN1_60_mGammaD_25_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/260000/2AB95635-6F5D-EA11-A014-20040FE9BCD4.root',
    #'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIFall17MiniAODv2/MSSMD_mH_125_mN1_60_mGammaD_25_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/260000/30C02F06-6E5C-EA11-8400-0CC47A78A360.root',
    #'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIFall17MiniAODv2/MSSMD_mH_125_mN1_60_mGammaD_25_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/260000/3C2B998E-125E-EA11-844A-0CC47AA99070.root',
    #'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIFall17MiniAODv2/MSSMD_mH_125_mN1_60_mGammaD_25_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/260000/3E53C3A8-125E-EA11-8533-0CC47A0AD668.root',
    #'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIFall17MiniAODv2/MSSMD_mH_125_mN1_60_mGammaD_25_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/260000/680CAC78-125E-EA11-94A0-AC1F6BAC7C16.root',
    #'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIFall17MiniAODv2/MSSMD_mH_125_mN1_60_mGammaD_25_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/260000/8285E191-125E-EA11-87C3-F01FAFD69863.root',
    #'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIFall17MiniAODv2/MSSMD_mH_125_mN1_60_mGammaD_25_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/260000/F458BFE0-A55D-EA11-9FF1-0CC47A4C8EE2.root',
    #'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIFall17MiniAODv2/MSSMD_mH_125_mN1_60_mGammaD_25_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/260000/F82A3277-DB5C-EA11-8F69-0CC47A4C8E46.root',
    )
)

process.out = cms.OutputModule(
    "PoolOutputModule",
    fileName = cms.untracked.string('patTuple.root')
    )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.p = cms.Path(
    process.unpackedTracksAndVertices *
    process.MuJetProducers *
    process.cutFlowAnalyzers
    )

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("out_ana_1.root")
)
