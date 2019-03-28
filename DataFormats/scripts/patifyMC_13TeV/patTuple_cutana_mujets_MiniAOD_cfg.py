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
#Default run on data
#Tags are specified here: https://twiki.cern.ch/twiki/bin/viewauth/CMS/PdmVAnalysisSummaryTable
#process.GlobalTag = GlobalTag(process.GlobalTag, '102X_upgrade2018_realistic_v15')#2018 MC
#process.GlobalTag = GlobalTag(process.GlobalTag, '102X_dataRun2_Sep2018Rereco_v1')#2018 data
process.GlobalTag = GlobalTag(process.GlobalTag, '94X_mc2017_realistic_v17')#2017 MC
#process.GlobalTag = GlobalTag(process.GlobalTag, '94X_dataRun2_v11')#2017 data
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("MuJetAnalysis.DataFormats.miniAODtoPAT_cff")
#process.load("MuJetAnalysis.MuJetProducer.MuJetProducer_MiniAOD_cff")#Pre-Run2 mu-jet cluster
process.load("MuJetAnalysis.MuJetProducer.MuJetProducerRun2_cff")#Run2 mu-jet cluster
process.load("MuJetAnalysis.CutFlowAnalyzer.CutFlowAnalyzer_MiniAOD_cff")
process.load("MuJetAnalysis.CutFlowAnalyzer.BaseLineSelectionFilter_MiniAOD_cfi")

process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
        #'file:/afs/cern.ch/work/w/wshi/public/dPhiForMuJet/CMSSW_9_4_7/src/B6C2D7D2-BDB1-E811-937D-A4BF01125BD0.root'#2017 NMSSM MC(mH=125,mA=3)
        #'file:/afs/cern.ch/work/w/wshi/public/2017MuClusterdM/CMSSW_9_4_7/src/460C5E54-06B0-E811-B24D-1CB72C1B6CCA.root'#2017 ALP MC (mALP=30)
        'file:/afs/cern.ch/work/w/wshi/public/Run2DimuSorting/CMSSW_9_4_7/src/BA9717EC-3840-E911-A0A8-AC1F6B596094.root'#2017 MSSMD MC (mN1=10, mGammaD=5, cT=10)
        #'file:/afs/cern.ch/work/w/wshi/public/2017MuClusterdM/CMSSW_9_4_7/src/B654BC56-CC25-E911-812F-B083FECFF2BE.root'#2017 MSSMD MC (mN1=10, mGammaD=8.5, cT=2)
        #'file:/afs/cern.ch/work/w/wshi/public/2017MuClusterdM/CMSSW_9_4_7/src/82230C10-5931-E911-907C-008CFA1111D0.root'#2017 MSSMD MC (mN1=60, mGammaD=35, cT=2)
        #'file:/afs/cern.ch/work/w/wshi/public/RunII2017Analysis/CMSSW_9_4_7/src/FAC28F5A-C639-E811-B4BB-10604BA8FC24.root'#2017C Data
        )
)

process.out = cms.OutputModule(
    "PoolOutputModule",
    fileName = cms.untracked.string('patTuple.root')
    )

### Add MuJet Dataformats
from MuJetAnalysis.DataFormats.EventContent_version11_cff import *
process = customizePatOutput(process)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

#Default run on data
runOnData = False
if runOnData: process.patifySelect = cms.Sequence(process.patifyData)
else:         process.patifySelect = cms.Sequence(process.patifyMC)

process.dump=cms.EDAnalyzer('EventContentAnalyzer')

process.p = cms.Path(
#    process.baseLineSelectionFilter *
    process.patifySelect *
    process.MuJetProducers *
#    process.dump *
    process.cutFlowAnalyzers
    )

#process.outpath = cms.EndPath(process.out)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("out_ana.root")
)
