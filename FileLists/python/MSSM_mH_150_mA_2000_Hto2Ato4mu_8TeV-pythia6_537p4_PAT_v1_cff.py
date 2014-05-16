import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)

readFiles.extend( [
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_9_1_yrN.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_8_1_szR.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_7_1_MKh.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_6_1_805.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_5_1_pQI.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_4_1_jH0.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_3_1_jI1.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_2_1_b5k.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_1_1_X1v.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_16_1_vDM.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_15_1_Dsp.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_14_1_0Vk.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_13_1_bdX.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_12_1_FTv.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_11_1_jRC.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_10_1_pMM.root'
] );

secFiles.extend( [
    ] )
