import FWCore.ParameterSet.Config as cms
import sys
import os


## import skeleton process
from PhysicsTools.PatAlgos.patTemplate_cfg import *


# verbose flags for the PF2PAT modules
#process.options.allowUnscheduled = cms.untracked.bool(True)

### Add MuJet Dataformats
#from MuJetAnalysis.DataFormats.EventContent_version10_cff import *
#process = customizePatOutput(process)

### Conditions
# Other statements

from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'MCRUN2_74_V9', '')

#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = "MCRUN2_74_V9"
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

process = cms.Process("PATIFY")

process.source = cms.Source ("PoolSource",
                        fileNames=cms.untracked.vstring('/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v2/DarkSUSY_mH_125_mGammaD_0300_cT_010_13TeV_DIGI_L1_DIGI2RAW_HLT_RECO_PU_MCRUN2_74_V9_v1/160127_105304/0000/out_reco_106.root'),
                        skipEvents=cms.untracked.uint32(0)
)

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

process.load("FWCore.MessageService.MessageLogger_cfi")
#process.MessageLogger = cms.Service("MessageLogger",
#        destinations = cms.untracked.vstring('myOutputFile'),
#        myOutputFile = cms.untracked.PSet(threshold = cms.untracked.string( 'DEBUG' )),
#        debugModules = cms.untracked.vstring("anatraj")                                   
#)

process.MessageLogger = cms.Service("MessageLogger", destinations = cms.untracked.vstring("cout"), cout = cms.untracked.PSet(threshold = cms.untracked.string("ERROR")))




######## PAT producer ########################################

process.load("MuJetAnalysis.DataFormats.RECOtoPAT_cff")

process.patMuons.addGenMatch = cms.bool(True)
process.patMuons.embedGenMatch = cms.bool(True)

## pick latest HLT process

#process.patTrigger.processName = cms.string( "*" )
#process.patTriggerEvent.processName = cms.string( "*" )

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

#from TrackingTools.TrackRefitter.TracksToTrajectories_cff import *
# IMPORTANT !!! ##
# If you want to revert the fit direction, then
# Case 1 #
# string RefitDirection = "alongMomentum"
# KFTrajectoryFitterESProducer   ---> Fitter = "KFFitterForRefitInsideOut"
# KFTrajectorySmootherESProducer ---> Smoother = "KFSmootherForRefitInsideOut"
# Case 2 #
# string RefitDirection = "oppositeToMomentum"
# KFTrajectoryFitterESProducer   ---> Fitter = "KFFitterForRefitOutsideIn"
# KFTrajectorySmootherESProducer ---> Smoother = "KFSmootherForRefitOutsideIn"
# the propagator must be the same as the one used by the Fitter
#

# process.RefittedTracks = cms.EDProducer("TracksToTrajectories",
#                                         Type = cms.string("Default"),
#                                         Tracks = cms.InputTag("generalTracks"),
#                                         TrackTransformer = cms.PSet(DoPredictionsOnly = cms.bool(False),
#                                                                     Fitter = cms.string('KFFitterForRefitInsideOut'),
#                                                                     #        TrackerRecHitBuilder = cms.string('WithTrackAngleAndTemplate'),
#                                                                     TrackerRecHitBuilder = cms.string('WithTrackAngle'),
#                                                                     Smoother = cms.string('KFSmootherForRefitInsideOut'),
#                                                                     MuonRecHitBuilder = cms.string('MuonRecHitBuilder'),
#                                                                     RefitDirection = cms.string('alongMomentum'),
#                                                                     RefitRPCHits = cms.bool(True),
#                                                                     Propagator = cms.string('SmartPropagatorAnyRKOpposite')
#                                                                     )
#                                         )

# #process.load("RecoTracker.TrackProducer.TrackRefitters_cff")

process.load("RecoTracker.TrackProducer.TrackRefitter_cfi")

# process.RefitTracks = cms.EDProducer("TrackRefitter",
#                                      src = cms.InputTag("generalTracks"),
#                                      beamSpot = cms.InputTag("offlineBeamSpot"),
#                                      Fitter = cms.string('KFFittingSmootherWithOutliersRejectionAndRK'),
#                                      #    TTRHBuilder = cms.string('WithAngleAndTemplate'),
#                                      AlgorithmName = cms.string('undefAlgorithm'),
# #                                     Propagator = cms.string('RungeKuttaTrackerPropagator'),
                                     
#                                      ### fitting without constraints
#                                      constraint = cms.string(''),
#                                      srcConstr  = cms.InputTag(''),                   
                                     
#                                      ### fitting with constraints                             
#                                      #constraint = cms.string('momentum'),
#                                      #constraint = cms.string('vertex'),
                                     
#                                      ### Usually this parameter has not to be set True because 
#                                      ### matched hits in the Tracker are already split when 
#                                      ### the tracks are reconstructed the first time                         
#                                      useHitsSplitting = cms.bool(False),
                                     
#                                      TrajectoryInEvent = cms.bool(True),
                                     
#                                      # this parameter decides if the propagation to the beam line
#                                      # for the track parameters defiition is from the first hit
#                                      # or from the closest to the beam line
#                                      # true for cosmics, false for collision tracks (needed by loopers)
# #                                     GeometricInnerState = cms.bool(False),
                                     
# #                                     # Navigation school is necessary to fill the secondary hit patterns                         
# #                                     NavigationSchool = cms.string('SimpleNavigationSchool'),
# #                                     MeasurementTracker = cms.string(''),                                              
#                                      MeasurementTrackerEvent = cms.InputTag('MeasurementTrackerEvent'),                   
#                                      #
#                                      # in order to avoid to fill the secondary hit patterns and
#                                      # refit the tracks more quickly 
#                                      #NavigationSchool = cms.string('') 
#                                      )



# process.ana2012 = cms.EDAnalyzer("AnalysisRun2",
#                                   trajectoryInput = cms.string("RefittedTracks"),
#                                   navigationSchool   = cms.string('SimpleNavigationSchool'),
#                                   MeasurementTracker = cms.string(''),
#                                   Propagator = cms.string("AnalyticalPropagator"),
#                                   muJets = cms.InputTag("PFMuJetProducer05"),
#                                   muons = cms.InputTag("cleanPatPFMuonsTriggerMatch"),
#                                   analyzerDebug = cms.int32(100),
#                                   analyzerTraj = cms.int32(1),
#                                   highpT_muon_pT = cms.double(17.0),
#                                   highpT_muon_eta = cms.double(0.9),
#                                   muon_pT = cms.double(8.0),
#                                   muon_eta = cms.double(2.4),
#                                   hltPaths = cms.vstring('HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx_v1'),
#                                   fillGenLevel = cms.bool(True)
#                                   )


#Process.Path = cms.Path(process.patifyMC * process.PFMuJetProducer05 * process.TrackRefitter * process.ana2012)
#process.Path = cms.Path(process.patifyMC * process.PFMuJetProducer05 * process.RefitTracks)
process.Path = cms.Path(process.patifyMC * process.PFMuJetProducer05)

#process.TFileService = cms.Service("TFileService", fileName = cms.string(sys.argv[2]+"/Ntup_%03d.root" % PROCESS) )
process.TFileService = cms.Service("TFileService", fileName = cms.string("test.root") )

