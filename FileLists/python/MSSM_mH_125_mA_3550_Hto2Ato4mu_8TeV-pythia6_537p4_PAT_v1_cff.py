import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)

readFiles.extend( [
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_11_1_ToO.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_10_2_sIu.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_13_1_V87.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_12_2_b4F.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_15_1_WZT.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_14_1_to9.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_1_1_HXo.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_16_1_bog.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_3_1_5RI.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_2_1_7HS.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_5_1_epo.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_4_1_zhH.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_7_2_BU1.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_6_1_C8Z.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_9_2_7uw.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_8_2_DGY.root'
] );

secFiles.extend( [
    ] )
