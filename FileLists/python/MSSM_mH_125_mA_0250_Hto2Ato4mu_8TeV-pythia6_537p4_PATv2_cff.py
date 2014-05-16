import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)

readFiles.extend( [
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_10_1_wkf.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_11_1_tv9.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_12_1_LzB.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_13_1_pj5.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_14_1_hT7.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_15_1_nAE.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_16_1_KMO.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_1_1_8OO.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_2_1_EqD.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_3_1_e9S.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_4_1_cWA.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_5_1_ofZ.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_6_1_wCp.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_7_1_ChM.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_8_1_eB2.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_9_1_q4N.root'
] );

secFiles.extend( [
    ] )
