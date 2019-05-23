import FWCore.ParameterSet.Config as cms

process = cms.Process("MUONJET")

## MessageLogger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
# verbose flags for the PF2PAT modules
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.options.allowUnscheduled = cms.untracked.bool(False)

## Geometry and Detector Conditions (needed for a few patTuple production steps)
process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")
process.load("Configuration.Geometry.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag

#Tags are specified here: https://twiki.cern.ch/twiki/bin/viewauth/CMS/PdmVAnalysisSummaryTable
#process.GlobalTag = GlobalTag(process.GlobalTag, '102X_upgrade2018_realistic_v15')#2018 MC
#process.GlobalTag = GlobalTag(process.GlobalTag, '102X_dataRun2_Sep2018Rereco_v1')#2018 data
process.GlobalTag = GlobalTag(process.GlobalTag, '94X_mc2017_realistic_v17')#2017 MC
#process.GlobalTag = GlobalTag(process.GlobalTag, '94X_dataRun2_v11')#2017 data

process.load("Configuration.StandardSequences.MagneticField_cff")
#process.load("MuJetAnalysis.DataFormats.miniAODtoPAT_cff")
process.load("PhysicsTools.PatAlgos.slimming.unpackedTracksAndVertices_cfi")
#process.load("MuJetAnalysis.MuJetProducer.MuJetProducer_MiniAOD_cff")#Pre-Run2 mu-jet cluster
process.load("MuJetAnalysis.MuJetProducer.MuJetProducerRun2_cff")#Run2 mu-jet cluster
process.load("MuJetAnalysis.CutFlowAnalyzer.CutFlowAnalyzer_MiniAOD_cff")
#process.load("MuJetAnalysis.CutFlowAnalyzer.BaseLineSelectionFilter_MiniAOD_cfi")

process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
        #'file:/afs/cern.ch/work/w/wshi/public/INPUT/460C5E54-06B0-E811-B24D-1CB72C1B6CCA.root'#2017 ALP MINIAODSIM (mALP=30)
        #'file:/afs/cern.ch/work/w/wshi/public/INPUT/BA9717EC-3840-E911-A0A8-AC1F6B596094.root'#2017 MSSMD MINIAODSIM (mN1=10, mGammaD=5, cT=10)
        #'file:/afs/cern.ch/work/w/wshi/public/INPUT/E8D69F89-6C33-E911-B440-D4856459AC30.root'#2017 MSSMD MINIAODSIM (mN1=10, mGammaD=5, cT=50)
        #'file:/afs/cern.ch/work/w/wshi/public/INPUT/B654BC56-CC25-E911-812F-B083FECFF2BE.root'#2017 MSSMD MINIAODSIM (mN1=10, mGammaD=8.5, cT=2)
        #'file:/afs/cern.ch/work/w/wshi/public/INPUT/2828BB5C-DE50-E911-A5C2-0CC47AF9B2FE.root'#2017 MSSMD MINIAODSIM (mN1=60, mGammaD=0.25, cT=100)
        #'file:/afs/cern.ch/work/w/wshi/public/INPUT/02E0B5B4-8664-E911-9D57-0242AC1C0503.root'#2017 MSSMD MINIAODSIM (mN1=60, mGammaD=5, cT=100)
        #'file:/afs/cern.ch/work/w/wshi/public/INPUT/26762963-A74E-E911-9C6D-D4AE52901D66.root'#2017 MSSMD MINIAODSIM (mN1=60, mGammaD=15, cT=100)
        #'file:/afs/cern.ch/work/w/wshi/public/INPUT/82230C10-5931-E911-907C-008CFA1111D0.root'#2017 MSSMD MINIAODSIM (mN1=60, mGammaD=35, cT=2)
        #'file:/afs/cern.ch/work/w/wshi/public/INPUT/7A3B1907-1B47-E911-AD34-AC1F6B0DE4A2.root'#2017 MSSMD MINIAODSIM (mN1=60, mGammaD=58, cT=50)
        #'file:/afs/cern.ch/work/w/wshi/public/INPUT/76651043-7F44-E811-9D72-0025905A60C6.root'#2017 Data Era E DoubleMuon
        #'file:/afs/cern.ch/work/w/wshi/public/INPUT/DF223035-AD40-E34A-857B-5C55FC925EC8.root'#2018 NMSSM MINIAODSIM (MH=125, MA=3)
        'file:/afs/cern.ch/work/w/wshi/public/INPUT/HIG-RunIIFall17MiniAODv2-03562.root' # Private: 2017 MSSMD MINIAODSIM CMSSW_9_4_7 (mN1=10, mGammaD=5, cT=50)
        #'file:/afs/cern.ch/work/w/wshi/public/INPUT/HIG-RunIIFall17MiniAODv2-03562_noPU.root' # Same as above except no PU simulation
        #'file:/afs/cern.ch/work/w/wshi/public/INPUT/ReMiniAOD.root' # Private: 2017 MSSMD ReMiniAODed under CMSSW_10_2_5(with displaceStandaloneMuon collection) (mN1=10, mGammaD=5, cT=50)
        #'file:/afs/cern.ch/work/w/wshi/public/INPUT/ReMiniAOD_noPU.root' # Same as above except no PU simulation
        #'file:/afs/cern.ch/work/w/wshi/public/INPUT/Private_out_miniaod_noPU.root' # From privately produced LHE (without using gridpack)
        )
)

process.out = cms.OutputModule(
    "PoolOutputModule",
    fileName = cms.untracked.string('patTuple.root')
    )

### Add MuJet Dataformats
#from MuJetAnalysis.DataFormats.EventContent_version11_cff import *
#process = customizePatOutput(process)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

#Default run on data
#runOnData = False
#if runOnData: process.patifySelect = cms.Sequence(process.patifyData)
#else:         process.patifySelect = cms.Sequence(process.patifyMC)

process.p = cms.Path(
#    process.baseLineSelectionFilter *
#    process.patifySelect *
    process.unpackedTracksAndVertices *
    process.MuJetProducers *
    process.cutFlowAnalyzers
    )

#process.outpath = cms.EndPath(process.out)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("out_ana.root")
)
