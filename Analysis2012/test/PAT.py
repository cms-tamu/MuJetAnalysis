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

process.source = cms.Source("PoolSource",
              fileNames = cms.untracked.vstring('file:input.root'),
              secondaryFileNames = cms.untracked.vstring()
)

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

######## PAT producer ########################################

process.load("MuJetAnalysis.DataFormats.RECOtoPAT_cff")

process.patMuons.addGenMatch = cms.bool(True)
process.patMuons.embedGenMatch = cms.bool(True)

## pick latest HLT process
process.patTrigger.processName = cms.string( "*" )
process.patTriggerEvent.processName = cms.string( "*" )

process.Path = cms.Path(process.patifyMC)


