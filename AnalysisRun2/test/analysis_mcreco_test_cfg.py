import FWCore.ParameterSet.Config as cms
import sys
import os



## import skeleton process
from PhysicsTools.PatAlgos.patTemplate_cfg import *

# verbose flags for the PF2PAT modules
process.options.allowUnscheduled = cms.untracked.bool(True)

#from RecoTracker.MeasurementDet.UpdaterService_cfi import *
from RecoTracker.MeasurementDet.MeasurementTrackerESProducer_cfi import *

### Add MuJet Dataformats
from MuJetAnalysis.DataFormats.EventContent_version10_cff import *
process = customizePatOutput(process)

### Conditions
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = "IDEAL_V5::All"
#process.GlobalTag.globaltag = 'GR09_P_V6::All'


################## RECO Input #############################

# PROCESS = str(os.getenv("PROCESS"))
# if ( PROCESS == None or PROCESS == "" ): PROCESS = int(0)
# else : PROCESS = int(PROCESS)
# JOBS = int(sys.argv[3])

# sample_name = sys.argv[2]

# file_list = "MuJetAnalysis.AnalysisRun2."+sys.argv[2]+"_cff"
# process.load(file_list)

# lenFileNames   = len(process.source.fileNames)
# process.source.fileNames = process.source.fileNames[lenFileNames*PROCESS/JOBS:lenFileNames*(PROCESS+1)/JOBS]

process.source = cms.Source ("PoolSource",
                        fileNames=cms.untracked.vstring('/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_cT_000_13TeV_RAW2DIGI_L1Reco_RECO_MCRUN2_74_V9_v1/150910_131714/0000/out_reco_10.root'),
                        skipEvents=cms.untracked.uint32(0)
)

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


# process.cutFlowAnalyzer = cms.EDAnalyzer('CutFlowAnalyzer',
#         analyzerDebug = cms.int32(0),
#         fillGenLevel = cms.bool(True),
# #       muons = cms.InputTag("cleanPatTrackerMuonsTriggerMatch"),
# #       muJets = cms.InputTag("TrackerMuJetProducer05"),
#         muons = cms.InputTag("cleanPatPFMuonsTriggerMatch"),
#         muJets = cms.InputTag("PFMuJetProducer05"),
#         DiMuons_Iso_Max = cms.double(2.0),
#         nThrowsConsistentVertexesCalculator = cms.int32(100000),
#         hltPaths = cms.vstring(
#         'HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx_v1',
#   )
# )

process.load("RecoTracker.TrackProducer.TrackRefitters_cff")


process.ana2012 = cms.EDAnalyzer("AnalysisRun2",
                                 trajectoryInput = cms.string("TrackRefitter"),
                                 navigationSchool   = cms.string('SimpleNavigationSchool'),
                                 MeasurementTracker = cms.string(''),
                                 Propagator = cms.string("AnalyticalPropagator"),
                                 muJets = cms.InputTag("PFMuJetProducer05"),
                                 muons = cms.InputTag("cleanPatPFMuonsTriggerMatch"),
                                 analyzerDebug = cms.int32(100),
                                 analyzerTraj = cms.int32(1),
                                 highpT_muon_pT = cms.double(17.0),
                                 highpT_muon_eta = cms.double(0.9),
                                 muon_pT = cms.double(8.0),
                                 muon_eta = cms.double(2.4),
                                 hltPaths = cms.vstring('HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx_v1'),
                                 fillGenLevel = cms.bool(True)
                                 )


process.Path = cms.Path(process.patifyMC * process.PFMuJetProducer05 * process.ana2012)

#process.TFileService = cms.Service("TFileService", fileName = cms.string(sys.argv[2]+"/Ntup_%03d.root" % PROCESS) )
process.TFileService = cms.Service("TFileService", fileName = cms.string("test.root") )

