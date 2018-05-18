import FWCore.ParameterSet.Config as cms
import os
import sys

## import skeleton process
from PhysicsTools.PatAlgos.patTemplate_cfg import *

# verbose flags for the PF2PAT modules
process.options.allowUnscheduled = cms.untracked.bool(True)

### Add MuJet Dataformats
from MuJetAnalysis.DataFormats.EventContent_version10_cff import *
process = customizePatOutput(process)

process.load("MuJetAnalysis.DataFormats.RECOtoPAT_cff")
process.patMuons.addGenMatch = cms.bool(True)
process.patMuons.embedGenMatch = cms.bool(True)

## pick latest HLT process
process.patTrigger.processName = cms.string( "*" )
process.patTriggerEvent.processName = cms.string( "*" )

process.load("MuJetAnalysis.MuJetProducer.MuJetProducer_cff")
process.load("MuJetAnalysis.CutFlowAnalyzer.CutFlowAnalyzer_cff")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
#        "file:out_reco.root"
#        "file:/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_000_Evt_79k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_cT000_Evt_79k_13TeV_RAW2DIGI_L1Reco_RECO_MCRUN2_74_V9_v1/151026_194054/0000/out_reco_1.root"
        'file:/fdata/hepx/store/user/wshi/NMSSM_mH_100_mA_1000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/NMSSM_mH_100_mA_1000_13TeV_RAW2DIGI_L1Reco_RECO_MINIAOD_V2_v1/161130_194925/0000/out_reco_1.root',
        'file:/fdata/hepx/store/user/wshi/NMSSM_mH_100_mA_1000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/NMSSM_mH_100_mA_1000_13TeV_RAW2DIGI_L1Reco_RECO_MINIAOD_V2_v1/161130_194925/0000/out_reco_10.root',
        'file:/fdata/hepx/store/user/wshi/NMSSM_mH_100_mA_1000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/NMSSM_mH_100_mA_1000_13TeV_RAW2DIGI_L1Reco_RECO_MINIAOD_V2_v1/161130_194925/0000/out_reco_100.root',
        'file:/fdata/hepx/store/user/wshi/NMSSM_mH_100_mA_1000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/NMSSM_mH_100_mA_1000_13TeV_RAW2DIGI_L1Reco_RECO_MINIAOD_V2_v1/161130_194925/0000/out_reco_101.root',
        'file:/fdata/hepx/store/user/wshi/NMSSM_mH_100_mA_1000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/NMSSM_mH_100_mA_1000_13TeV_RAW2DIGI_L1Reco_RECO_MINIAOD_V2_v1/161130_194925/0000/out_reco_102.root',
        'file:/fdata/hepx/store/user/wshi/NMSSM_mH_100_mA_1000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/NMSSM_mH_100_mA_1000_13TeV_RAW2DIGI_L1Reco_RECO_MINIAOD_V2_v1/161130_194925/0000/out_reco_103.root',
        'file:/fdata/hepx/store/user/wshi/NMSSM_mH_100_mA_1000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/NMSSM_mH_100_mA_1000_13TeV_RAW2DIGI_L1Reco_RECO_MINIAOD_V2_v1/161130_194925/0000/out_reco_104.root',
        'file:/fdata/hepx/store/user/wshi/NMSSM_mH_100_mA_1000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/NMSSM_mH_100_mA_1000_13TeV_RAW2DIGI_L1Reco_RECO_MINIAOD_V2_v1/161130_194925/0000/out_reco_105.root',
        'file:/fdata/hepx/store/user/wshi/NMSSM_mH_100_mA_1000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/NMSSM_mH_100_mA_1000_13TeV_RAW2DIGI_L1Reco_RECO_MINIAOD_V2_v1/161130_194925/0000/out_reco_106.root'
    )

)

process.maxEvents.input = -1

process.p = cms.Path(
    process.patifyMC *
    process.MuJetProducers * 
    process.cutFlowAnalyzers
)

process.outpath = cms.EndPath(process.out)

#process.TFileService = cms.Service("TFileService", fileName = cms.string(sys.argv[2]+"/ana_%03d.root" % PROCESS) )

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("out_ana_reco.root")
)
