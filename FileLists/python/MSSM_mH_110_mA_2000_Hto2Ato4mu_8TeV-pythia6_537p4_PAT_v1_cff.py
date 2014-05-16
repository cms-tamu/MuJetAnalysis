import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)

readFiles.extend( [
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_9_1_AGW.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_8_1_jg4.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_7_1_71t.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_6_1_k87.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_5_2_kTX.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_4_2_bEB.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_3_1_Qbs.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_2_2_Yx2.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_1_2_EYH.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_16_1_TaB.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_15_1_Kxq.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_14_1_KvH.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_13_1_Zfc.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_12_1_Igw.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_11_1_Fgh.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_10_1_I2Q.root'
] );

secFiles.extend( [
    ] )
