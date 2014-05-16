import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v3/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_10_1_FQx.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v3/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_11_1_hPE.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v3/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_12_1_mPi.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v3/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_13_1_UkD.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v3/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_14_1_boG.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v3/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_15_1_C7m.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v3/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_16_1_xQV.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v3/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_1_1_BB2.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v3/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_2_1_Kaj.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v3/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_3_1_UJf.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v3/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_4_1_wWO.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v3/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_5_1_40g.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v3/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_6_1_3cw.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v3/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_7_1_mX5.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v3/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_8_1_mTM.root',
       '/store/user/pakhotin/data/MC_8TeV/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/pakhotin/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_GEN_v3/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2/d7ec853f1412ed77b3135ca95d8b3a46/output_9_1_KV9.root' ] );


secFiles.extend( [
               ] )
