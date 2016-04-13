# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: step3 --conditions auto:run2_mc -n 10 --eventcontent RECOSIM,MINIAODSIM --runUnscheduled -s RAW2DIGI,L1Reco,RECO,PAT --datatier GEN-SIM-RECO,MINIAODSIM --customise SLHCUpgradeSimulations/Configuration/postLS1Customs.customisePostLS1 --magField 38T_PostLS1 --no_exec
import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.Config as cms
import sys
import os


process = cms.Process('TEST')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_PostLS1_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')

process.options = cms.untracked.PSet(
    allowUnscheduled = cms.untracked.bool(True)
)

# Other statements
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'MCRUN2_74_V9', '')

# Automatic addition of the customisation function from SLHCUpgradeSimulations.Configuration.postLS1Customs
#from SLHCUpgradeSimulations.Configuration.postLS1Customs import customisePostLS1 

### Track refitter specific stuff
from RecoTracker.TkNavigation.NavigationSchoolESProducer_cff import *
process.load("RecoTracker.TrackProducer.TrackRefitter_cfi")
process.TrackRefitter.NavigationSchool = ''

################## RECO Input #############################

PROCESS = str(os.getenv("PROCESS"))
if ( PROCESS == None or PROCESS == "" ): PROCESS = int(0)
else : PROCESS = int(PROCESS)
JOBS = int(sys.argv[3])

sample_name = sys.argv[2]

file_list = "MuJetAnalysis.AnalysisRun2."+sys.argv[2]+"_cff"
process.load(file_list)

lenFileNames   = len(process.source.fileNames)
process.source.fileNames = process.source.fileNames[lenFileNames*PROCESS/JOBS:lenFileNames*(PROCESS+1)/JOBS]

# process.source = cms.Source ("PoolSource",
# #                            fileNames=cms.untracked.vstring('file:/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_000_Evt_79k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_cT_000_Evt_79k_13TeV_RAW2DIGI_L1Reco_RECO_MCRUN2_74_V9_v1/151026_194054/0000/out_reco_1.root'),
#                              fileNames=cms.untracked.vstring('file:out_reco_106.root'),
#                              skipEvents=cms.untracked.uint32(0)
#                             )
# process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(30))


process.Path = cms.Path(process.TrackRefitter*process.MeasurementTrackerEvent)

# End of customisation functions
#do not add changes to your config after this point (unless you know what you are doing)
from FWCore.ParameterSet.Utilities import convertToUnscheduled
process=convertToUnscheduled(process)

################# RECOtoPAT  ==========================================
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

#process.load("MuJetAnalysis.CutFlowAnalyzer.CutFlowAnalyzer_cfi")


process.ana2012 = cms.EDAnalyzer("AnalysisRun2",
                                 trajectoryInput = cms.string("TrackRefitter"),
                                 NavigationSchool   = cms.string('SimpleNavigationSchool'),
#                                navigationSchool   = cms.string(''),
                                 MeasurementTracker = cms.string(''),
                                 MeasurementTrackerEvent = cms.InputTag('MeasurementTrackerEvent'),
                                 Propagator = cms.string("RungeKuttaTrackerPropagator"),
                                 muJets = cms.InputTag("PFMuJetProducer05"),
                                 muons = cms.InputTag("cleanPatPFMuonsTriggerMatch"),
                                 analyzerDebug = cms.int32(100),
                                 analyzerTraj = cms.int32(1),
                                 highpT_muon_pT = cms.double(17.0),
                                 highpT_muon_eta = cms.double(0.9),
                                 muon_pT = cms.double(8.0),
                                 muon_eta = cms.double(2.4),
                                 hltPaths = cms.vstring('HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx_v1'),
                                 fillGenLevel = cms.bool(True),
                                 nJob = cms.int32(PROCESS)
                                   )

#process.Path = cms.Path(process.patifyMC * process.PFMuJetProducer05 * process.cutFlowAnalyzer)
#process.Path = cms.Path(process.patifyMC * process.PFMuJetProducer05 * process.TrackRefitter * process.cutFlowAnalyzer)
process.Path = cms.Path(process.patifyMC * process.PFMuJetProducer05 * process.TrackRefitter * process.ana2012)
# customisation of the process.

process.TFileService = cms.Service("TFileService", fileName = cms.string(sys.argv[2]+"/Ntup_%03d.root" % PROCESS) )
#process.TFileService = cms.Service("TFileService", fileName = cms.string("test.root") )

# End of customisation functions


