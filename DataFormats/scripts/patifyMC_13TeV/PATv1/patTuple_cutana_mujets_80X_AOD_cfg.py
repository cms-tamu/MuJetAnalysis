import FWCore.ParameterSet.Config as cms

process = cms.Process("MUONJET")

## MessageLogger
process.load("FWCore.MessageLogger.MessageLogger_cfi")

# verbose flags for the PF2PAT modules
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.options.allowUnscheduled = cms.untracked.bool(False)

## Geometry and Detector Conditions (needed for a few patTuple production steps)
process.load("Configuration.Geometry.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '80X_mcRun2_asymptotic_2016_miniAODv2_v1')
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("MuJetAnalysis.DataFormats.RECOtoPAT_cff")
process.load("MuJetAnalysis.MuJetProducer.MuJetProducer_cff")
process.load("MuJetAnalysis.CutFlowAnalyzer.CutFlowAnalyzer_cff")
process.load("MuJetAnalysis.CutFlowAnalyzer.FilterSample3RecoMu_cfi")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'file:/fdata/hepx/store/user/wshi/NMSSM_mH_90_mA_3p55_13TeV_pythia8/RAW2DIGI_L1Reco_RECO/180411_073623/0000/out_reco_287.root',
        'file:/fdata/hepx/store/user/wshi/NMSSM_mH_90_mA_3p55_13TeV_pythia8/RAW2DIGI_L1Reco_RECO/180411_073623/0000/out_reco_288.root',
        'file:/fdata/hepx/store/user/wshi/NMSSM_mH_90_mA_3p55_13TeV_pythia8/RAW2DIGI_L1Reco_RECO/180411_073623/0000/out_reco_289.root',
        'file:/fdata/hepx/store/user/wshi/NMSSM_mH_90_mA_3p55_13TeV_pythia8/RAW2DIGI_L1Reco_RECO/180411_073623/0000/out_reco_290.root',
        #/fdata/hepx/store/mc/RunIISummer16DR80Premix/NMSSM_HToAATo4Mu_M-125_M-3p55_TuneCUETP8M1_13TeV_pythia8/AODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/60000/F6319178-28D6-E611-A6C5-02163E012A93.root'
#/fdata/hepx/store/mc/RunIISummer16DR80Premix/NMSSM_HToAATo4Mu_mH_100_mA_3p55_TuneCUETP8M1_13TeV_pythia8/AODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/110000/06F8E271-45FC-E611-A8DA-C45444922D6C.root'
#file:/fdata/hepx/store/mc/RunIISummer16DR80Premix/NMSSM_HToAATo4Mu_mH_150_mA_3p55_TuneCUETP8M1_13TeV_pythia8/AODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/00000/E0EB5616-DCFC-E611-B71F-0025904A9472.root'
#/fdata/hepx/store/mc/RunIISummer16DR80Premix/NMSSM_HToAATo4Mu_mH_150_mA_4_TuneCUETP8M1_13TeV_pythia8/AODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/130000/0A7FA694-C1FA-E611-B5CD-002590494CBC.root'
        #'file:/fdata/hepx/store/mc/RunIISummer16DR80Premix/NMSSM_HToAATo4Mu_mH_150_mA_0p24_TuneCUETP8M1_13TeV_pythia8/AODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/130000/0A7FA694-C1FA-E611-B5CD-002590494CBC.root',
        #'file:/fdata/hepx/store/mc/RunIISummer16DR80Premix/NMSSM_HToAATo4Mu_mH_90_mA_0p25_TuneCUETP8M1_13TeV_pythia8/AODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/110000/04BAD758-A4FC-E611-92E9-02163E019BAF.root'
        #'file:/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_0_13TeV_20k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_0_13TeV_20k_PAT_ANA_V2_v1/170124_224445/0000/out_pat_17.root'
    )
)

process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string('patTuple.root')
)

### Add MuJet Dataformats
from MuJetAnalysis.DataFormats.EventContent_version10_cff import *
process = customizePatOutput(process)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-100) )

process.p = cms.Path(
#    process.tripleRecoMuFilter *
    process.patifyMC *
    process.MuJetProducers *
    process.cutFlowAnalyzers
)

#process.outpath = cms.EndPath(process.out)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("out_ana.root")
)

