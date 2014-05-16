import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)

readFiles.extend( [
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_10_1_4wD.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_11_1_Yh3.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_12_1_e6y.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_13_1_34k.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_14_1_4s5.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_15_1_uM8.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_16_1_DZw.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_1_1_rAF.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_2_1_hO8.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_3_1_ez4.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_4_1_wz8.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_5_1_LYT.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_6_1_M8n.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_7_1_Dq2.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_8_1_vRr.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_9_1_b1Y.root'
] );

secFiles.extend( [
    ] )
