import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)

readFiles.extend( [
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_10_1_r7D.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_11_1_SZW.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_12_1_7Rz.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_13_1_in3.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_14_1_YLX.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_15_1_jsW.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_16_1_N9K.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_1_1_Yxw.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_2_1_cfN.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_3_1_Z4M.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_4_1_xnx.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_5_1_9uB.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_6_1_nio.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_7_1_syY.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_8_1_EsG.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_9_1_zNZ.root'
] );

secFiles.extend( [
    ] )
