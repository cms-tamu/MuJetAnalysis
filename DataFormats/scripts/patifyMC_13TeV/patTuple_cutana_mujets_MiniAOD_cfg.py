import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing

process = cms.Process("MUONJET")

options = VarParsing('analysis')
options.register ("mc", False, VarParsing.multiplicity.singleton, VarParsing.varType.bool)
options.register ("year", 2018, VarParsing.multiplicity.singleton, VarParsing.varType.int)
options.register ("era", "ABC", VarParsing.multiplicity.singleton, VarParsing.varType.string)
options.parseArguments()

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
globalTagChoice = ""
if options.mc:
    #2017 MC
    if options.year == 2017:
        globalTagChoice = '94X_mc2017_realistic_v17'
    #2018 MC
    if options.year == 2018:
        globalTagChoice = '102X_upgrade2018_realistic_v20'
else:
    #2017 data
    if options.year == 2017:
        globalTagChoice = '94X_dataRun2_v11'
    #2018 data
    if options.year == 2018:
        #2018 data: Era ABC
        if options.era == "ABC":
            globalTagChoice = '102X_dataRun2_v12'
        #2018 data: Era D
        else:
            globalTagChoice = '102X_dataRun2_Prompt_v15'

print "Chosen global tag", globalTagChoice
process.GlobalTag = GlobalTag(process.GlobalTag, globalTagChoice)

process.load("Configuration.StandardSequences.MagneticField_cff")
#process.load("MuJetAnalysis.DataFormats.miniAODtoPAT_cff")
process.load("PhysicsTools.PatAlgos.slimming.unpackedTracksAndVertices_cfi")
#process.load("MuJetAnalysis.MuJetProducer.MuJetProducer_MiniAOD_cff")#Pre-Run2 mu-jet cluster
process.load("MuJetAnalysis.MuJetProducer.MuJetProducerRun2_cff")#Run2 mu-jet cluster
process.load("MuJetAnalysis.CutFlowAnalyzer.CutFlowAnalyzer_MiniAOD_cff")

process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
        "/store/user/dildick/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/crab_WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8_Filter20201027_V3/201028_024942/0000/Filter_1-1.root"
    )
)

process.out = cms.OutputModule(
    "PoolOutputModule",
    fileName = cms.untracked.string('patTuple.root')
    )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.p = cms.Path(
    process.unpackedTracksAndVertices *
    process.MuJetProducers *
    process.cutFlowAnalyzers
    )

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("out_ana_1.root")
)
