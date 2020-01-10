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
#process.GlobalTag = GlobalTag(process.GlobalTag, '102X_upgrade2018_realistic_v20') #2018 MC
#process.GlobalTag = GlobalTag(process.GlobalTag, '102X_dataRun2_v12')              #2018 data: Era ABC
#process.GlobalTag = GlobalTag(process.GlobalTag, '102X_dataRun2_Prompt_v15')       #2018 data: Era D
process.GlobalTag = GlobalTag(process.GlobalTag, '94X_mc2017_realistic_v17')        #2017 MC
#process.GlobalTag = GlobalTag(process.GlobalTag, '94X_dataRun2_v11')               #2017 data

process.load("Configuration.StandardSequences.MagneticField_cff")
#process.load("MuJetAnalysis.DataFormats.miniAODtoPAT_cff")
process.load("PhysicsTools.PatAlgos.slimming.unpackedTracksAndVertices_cfi")
#process.load("MuJetAnalysis.MuJetProducer.MuJetProducer_MiniAOD_cff")#Pre-Run2 mu-jet cluster
process.load("MuJetAnalysis.MuJetProducer.MuJetProducerRun2_cff")#Run2 mu-jet cluster
process.load("MuJetAnalysis.CutFlowAnalyzer.CutFlowAnalyzer_MiniAOD_cff")

process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
        'file:/afs/cern.ch/work/w/wshi/public/INPUT/460C5E54-06B0-E811-B24D-1CB72C1B6CCA.root'#2017 ALP MINIAODSIM (mALP=30)
        #'file:/afs/cern.ch/work/w/wshi/public/INPUT/76651043-7F44-E811-9D72-0025905A60C6.root'#2017 Data Era E DoubleMuon
        #'file:/afs/cern.ch/work/w/wshi/public/INPUT/DF223035-AD40-E34A-857B-5C55FC925EC8.root'#2018 NMSSM MINIAODSIM (MH=125, MA=3)
        #'file:/afs/cern.ch/work/w/wshi/public/INPUT/09C645BA-5536-F04E-954B-7BFDF9E4B130.root'#2018 Data: /DoubleMuon/Run2018A-17Sep2018-v2/MINIAOD
        #'file:/afs/cern.ch/work/w/wshi/public/INPUT/HIG-RunIIFall17MiniAODv2-03562.root' # Private: 2017 MSSMD MINIAODSIM CMSSW_9_4_7 (mN1=10, mGammaD=5, cT=50)
        #'file:/afs/cern.ch/work/w/wshi/public/INPUT/HIG-RunIIFall17MiniAODv2-03562_noPU.root' # Same as above except no PU simulation
        )
)

process.out = cms.OutputModule(
    "PoolOutputModule",
    fileName = cms.untracked.string('patTuple.root')
    )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.p = cms.Path(
    process.unpackedTracksAndVertices *
    process.MuJetProducers *
    process.cutFlowAnalyzers
    )

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("out_ana.root")
)
