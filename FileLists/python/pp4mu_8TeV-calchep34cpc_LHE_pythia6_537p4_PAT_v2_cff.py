import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/pakhotin/pp4mu_8TeV-calchep34cpc_LHE_pythia6_537p4_GEN_v2/pp4mu_8TeV-calchep34cpc_LHE_pythia6_537p4_PAT_v2/d7ec853f1412ed77b3135ca95d8b3a46/output_3_1_Fga.root',
       '/store/user/pakhotin/pp4mu_8TeV-calchep34cpc_LHE_pythia6_537p4_GEN_v2/pp4mu_8TeV-calchep34cpc_LHE_pythia6_537p4_PAT_v2/d7ec853f1412ed77b3135ca95d8b3a46/output_2_1_VGU.root',
       '/store/user/pakhotin/pp4mu_8TeV-calchep34cpc_LHE_pythia6_537p4_GEN_v2/pp4mu_8TeV-calchep34cpc_LHE_pythia6_537p4_PAT_v2/d7ec853f1412ed77b3135ca95d8b3a46/output_1_1_gbC.root' ] );


secFiles.extend( [
               ] )
