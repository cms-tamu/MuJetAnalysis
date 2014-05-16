import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)

readFiles.extend( [
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_10_1_iTp.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_11_1_cqF.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_12_1_xs9.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_13_1_wbj.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_14_1_Lxx.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_15_1_MsJ.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_1_1_Wuy.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_2_1_jjX.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_3_1_HyR.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_4_1_Teh.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_5_1_B7m.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_6_1_s9X.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_7_1_E84.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_8_1_LC5.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_9_1_J8O.root'
] );

secFiles.extend( [
    ] )
