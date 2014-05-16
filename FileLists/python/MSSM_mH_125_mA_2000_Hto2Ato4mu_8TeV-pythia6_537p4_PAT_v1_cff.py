import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)

readFiles.extend( [
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v3/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_9_1_IYH.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v3/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_8_2_BPR.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v3/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_7_1_E77.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v3/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_6_1_bS0.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v3/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_5_1_lp0.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v3/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_4_1_2ps.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v3/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_3_1_F9N.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v3/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_2_2_sMZ.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v3/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_1_1_yNH.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v3/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_16_1_eYK.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v3/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_15_1_K9U.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v3/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_14_1_XRs.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v3/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_13_2_Jln.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v3/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_12_1_jHB.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v3/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_11_2_6El.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/pakhotin/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v3/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PAT_v1/d7ec853f1412ed77b3135ca95d8b3a46/output_10_1_eJF.root'
] );

secFiles.extend( [
    ] )
