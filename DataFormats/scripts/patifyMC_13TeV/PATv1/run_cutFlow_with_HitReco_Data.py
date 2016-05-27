import FWCore.ParameterSet.Config as cms
import sys
import os

from PhysicsTools.PatAlgos.patTemplate_cfg import *
from MuJetAnalysis.DataFormats.EventContent_version10_cff import *
process = customizePatOutput(process)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')

process.options = cms.untracked.PSet(
    allowUnscheduled = cms.untracked.bool(True)
)

# Other statements
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_data', '')

### Track refitter specific stuff
from RecoTracker.TkNavigation.NavigationSchoolESProducer_cff import *
process.load("RecoTracker.TrackProducer.TrackRefitter_cfi")
process.TrackRefitter.NavigationSchool = ''

################## RECO Input #############################

process.source = cms.Source ("PoolSource",
                             fileNames=cms.untracked.vstring(
        'file:B6687419-D919-E611-9A7C-02163E014647.root'
							 ),
                             skipEvents=cms.untracked.uint32(0)
                            )
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))


process.Path = cms.Path(process.TrackRefitter*process.MeasurementTrackerEvent)

# End of customisation functions
#do not add changes to your config after this point (unless you know what you are doing)
from FWCore.ParameterSet.Utilities import convertToUnscheduled
process=convertToUnscheduled(process)

################# RECOtoPAT  ==========================================
process.load("MuJetAnalysis.DataFormats.RECOtoPAT_cff")
process.patMuons.addGenMatch = cms.bool(False)
process.patMuons.embedGenMatch = cms.bool(False)

## pick latest HLT process
process.patTrigger.processName = cms.string( "*" )
process.patTriggerEvent.processName = cms.string( "*" )

############## Analysis Modules ###################################
process.load("MuJetAnalysis.MuJetProducer.MuJetProducer_cff")
process.load("MuJetAnalysis.CutFlowAnalyzer.CutFlowAnalyzer_cff")
process.cutFlowAnalyzer_Data.runBBestimation = cms.untracked.bool(False)

process.Path = cms.Path(process.patifyData * process.MuJetProducers  * process.cutFlowAnalyzer_Data)
# customisation of the process.

process.TFileService = cms.Service("TFileService", fileName = cms.string("out_ana.root") )

# End of customisation functions
