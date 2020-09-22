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
process.GlobalTag = GlobalTag(process.GlobalTag, '102X_upgrade2018_realistic_v20') #2018 MC
#process.GlobalTag = GlobalTag(process.GlobalTag, '102X_dataRun2_v12')              #2018 data: Era ABC
#process.GlobalTag = GlobalTag(process.GlobalTag, '102X_dataRun2_Prompt_v15')       #2018 data: Era D
#process.GlobalTag = GlobalTag(process.GlobalTag, '94X_mc2017_realistic_v17')       #2017 MC
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
    'file:/home/ws13/Run2Analysis/CMSSW_10_2_18/src/MuJetAnalysis/DataFormats/scripts/patifyMC_13TeV/2BBCB9BA-7D95-A44D-8397-E436424290AD.root'
    #'file:02105075-21AE-E811-BA26-008CFA111184.root', ##TT_Dilept 2017
    #'file:DEF2411F-2DAC-E811-85F7-7845C4F92C96.root', ##TT_Dilept 2017
    #'file:F7D3D6CF-1B85-8241-933E-27452382FB9F.root', ##WZTo3LNu 2018 for trigger study
    #'file:105518D4-CDCA-7640-B0E8-E2368C8FE208.root', ##2018 EraA MET
    #'file:/scratch/user/ws13/2017TestData/FAC28F5A-C639-E811-B4BB-10604BA8FC24.root', #one file from /DoubleMuon/Run2017C-31Mar2018-v1/MINIAOD
    #'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIFall17MiniAODv2/MSSMD_mH_125_mN1_60_mGammaD_58_cT_0_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/120000/0228EDB3-A855-E911-8BCD-842B2B180C66.root',
    #'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIFall17MiniAODv2/MSSMD_mH_125_mN1_60_mGammaD_58_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/110000/02E71858-9C36-EA11-9831-0CC47A57CEB4.root',
    #'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_5_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/100000/2C5B15B8-1CFF-3449-972E-2DB77E9361AF.root',
    #'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_5_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/100000/624E9E0B-ADC7-9140-B515-8DF9EDAFFF08.root',
    #'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_5_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/100000/78C8681A-A3EC-4D43-91ED-BFCFAF666E5E.root',
    #'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_5_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/100000/909C8559-85BB-FD4F-B27A-D05BEF91BC9F.root',
    #'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_5_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/100000/A3E1E207-765C-0B4D-BBD0-E408CC03DE9A.root',
    #'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_5_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/100000/B534ECD1-EF7F-404C-A1C4-B63083DF3844.root',
    #'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_5_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/100000/B7DBDBA3-BEC0-9449-94D0-DA6EAE968D95.root',
    #'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_5_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/100000/F818A22C-5481-6A47-93AE-1F01C5B5F8C7.root',
    #'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_5_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/260000/6E458A81-DDA0-2F46-956C-AC4A813A3486.root',
    #'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_25_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/260000/5650FDF7-A2B3-9E45-8E2C-63E518959EEC.root',
    #'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_25_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/260000/F7C9A2AE-0619-D64E-BC28-1CB8D6196B66.root',
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
