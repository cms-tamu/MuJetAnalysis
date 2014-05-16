import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)

readFiles.extend( [
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_11_1_f39.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_10_2_6qu.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_13_2_nfq.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_12_2_362.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_15_2_lUx.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_14_2_2Ir.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_1_1_p4S.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_16_1_l9f.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_3_1_2mp.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_2_1_2QR.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_5_2_txM.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_4_1_oHF.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_6_1_8uy.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_7_2_ekF.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_8_3_XBx.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_9_2_ji6.root'
] );

secFiles.extend( [
    ] )
