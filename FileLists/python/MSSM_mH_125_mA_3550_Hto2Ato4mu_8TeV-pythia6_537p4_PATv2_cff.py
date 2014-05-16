import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)

readFiles.extend( [
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_15_1_XSn.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_16_1_Cbm.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_1_1_fde.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_2_1_jzp.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_3_1_qOY.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_4_1_Y3d.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_5_1_iSk.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_6_1_KBo.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_7_1_Zy1.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_8_1_PYo.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_9_1_Dlk.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_10_1_61Y.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_11_1_rPl.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_12_1_VwC.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_13_1_IVF.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v2/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_14_1_yIQ.root'
] );

secFiles.extend( [
    ] )
