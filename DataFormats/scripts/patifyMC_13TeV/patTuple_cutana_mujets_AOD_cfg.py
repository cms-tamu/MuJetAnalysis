import FWCore.ParameterSet.Config as cms

process = cms.Process("MUONJET")

## MessageLogger
process.load("FWCore.MessageLogger.MessageLogger_cfi")

# verbose flags for the PF2PAT modules
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

## Geometry and Detector Conditions (needed for a few patTuple production steps)
process.load("Configuration.Geometry.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_data')
process.GlobalTag = GlobalTag(process.GlobalTag, '94X_mc2017_realistic_v17')#2017 MC
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("MuJetAnalysis.DataFormats.RECOtoPAT_cff")
process.load("MuJetAnalysis.MuJetProducer.MuJetProducer_cff")
process.load("MuJetAnalysis.CutFlowAnalyzer.CutFlowAnalyzer_cff")
#process.load("MuJetAnalysis.CutFlowAnalyzer.BaseLineSelectionFilter_AOD_cfi")

process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
        'file:/afs/cern.ch/work/w/wshi/public/INPUT/68D1D254-E22B-E911-890C-002590E7E07A.root' #Central: 2017 MSSMD AODSIM CMSSW_9_4_7 (mN1=10, mGammaD=5, cT=50)
        #'file:/afs/cern.ch/work/w/wshi/public/INPUT/HIG-RunIIFall17DRPremix-03630.root'  #Private: 2017 MSSMD AODSIM CMSSW_9_4_7 (mN1=10, mGammaD=5, cT=50)
    )
)

process.out = cms.OutputModule(
    "PoolOutputModule",
    fileName = cms.untracked.string('patTuple.root')
)

### Add MuJet Dataformats
from MuJetAnalysis.DataFormats.EventContent_version10_cff import *
process = customizePatOutput(process)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

runOnData = False
if runOnData: process.patifySelect = cms.Sequence(process.patifyData)
else:         process.patifySelect = cms.Sequence(process.patifyMC)

process.p = cms.Path(
    ## before PAT-ANA step, require events to have at least
    ## 3 muons with 5 GeV pT in |eta|<2.4
    #process.baseLineSelectionFilter *
    process.patifySelect *
    process.MuJetProducers *
    process.cutFlowAnalyzers
    )



process.TFileService = cms.Service("TFileService",
    fileName = cms.string("out_ana.root")
)
