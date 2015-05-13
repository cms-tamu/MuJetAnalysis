import FWCore.ParameterSet.Config as cms
import sys
import os


## import skeleton process
from PhysicsTools.PatAlgos.patTemplate_cfg import *

# verbose flags for the PF2PAT modules
process.options.allowUnscheduled = cms.untracked.bool(True)

### Add MuJet Dataformats
from MuJetAnalysis.DataFormats.EventContent_version10_cff import *
process = customizePatOutput(process)



################## RECO Input #############################

PROCESS = str(os.getenv("PROCESS"))
if ( PROCESS == None or PROCESS == "" ): PROCESS = int(0)
else : PROCESS = int(PROCESS)
JOBS = int(sys.argv[3])

sample_name = sys.argv[2]

file_list = "MuJetAnalysis.CutFlowAnalyzer."+sys.argv[2]+"_cff"
process.load(file_list)

lenFileNames   = len(process.source.fileNames)
process.source.fileNames = process.source.fileNames[lenFileNames*PROCESS/JOBS:lenFileNames*(PROCESS+1)/JOBS]

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

######## PAT producer ########################################

process.load("MuJetAnalysis.DataFormats.RECOtoPAT_cff")

process.patMuons.addGenMatch = cms.bool(True)
process.patMuons.embedGenMatch = cms.bool(True)

## pick latest HLT process
process.patTrigger.processName = cms.string( "*" )
process.patTriggerEvent.processName = cms.string( "*" )

############## Analysis Modules ###################################


process.load("MuJetAnalysis.MuJetProducer.MuJetProducer_cfi")


process.PFMuJetProducer05 = process.MuJetProducer.clone(
    maxMass = cms.double(5.),
    minPt = cms.double(8.0),
    maxAbsEta = cms.double(2.4),
    muons = cms.InputTag("cleanPatPFMuonsTriggerMatch"),
#    selectTrackerMuons = cms.bool(True),
#    selectGlobalMuons = cms.bool(True),
    groupingMode = cms.string("GroupByMassAndVertexProbOrDeltaR"),
    maxDeltaR = cms.double(0.01),
    #  minSegmentMatches = cms.int32(2),
    minSegmentMatches = cms.int32(-1),
    minTrackerHits = cms.int32(-1),
    maxTrackerNormChi2 = cms.double(-1.0)
)


process.cutFlowAnalyzer = cms.EDAnalyzer('CutFlowAnalyzer',
        analyzerDebug = cms.int32(0),
        fillGenLevel = cms.bool(True),
#       muons = cms.InputTag("cleanPatTrackerMuonsTriggerMatch"),
#       muJets = cms.InputTag("TrackerMuJetProducer05"),
        muons = cms.InputTag("cleanPatPFMuonsTriggerMatch"),
        muJets = cms.InputTag("PFMuJetProducer05"),
        DiMuons_Iso_Max = cms.double(2.0),
        nThrowsConsistentVertexesCalculator = cms.int32(100000),
        hltPaths = cms.vstring(
        'HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx_v1',
  )
)

process.Path = cms.Path(process.patifyData * process.PFMuJetProducer05 * process.cutFlowAnalyzer)

process.TFileService = cms.Service("TFileService", fileName = cms.string(sys.argv[2]+"/Ntup_%03d.root" % PROCESS) )

