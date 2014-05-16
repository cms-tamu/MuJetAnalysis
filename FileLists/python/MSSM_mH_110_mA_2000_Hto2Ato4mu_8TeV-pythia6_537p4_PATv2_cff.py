import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)

readFiles.extend( [
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_10_1_zAJ.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_11_1_Oj8.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_12_1_k2q.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_13_1_Gu1.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_14_1_wDI.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_15_1_ZV7.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_16_1_frr.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_1_1_npf.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_2_1_AHP.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_3_1_g8u.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_4_1_3UZ.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_5_1_bRY.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_6_1_afV.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_7_1_jAb.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_8_1_lzK.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_9_1_Uey.root'
] );

secFiles.extend( [
    ] )
