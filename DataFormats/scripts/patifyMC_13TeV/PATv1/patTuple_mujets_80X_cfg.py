## import skeleton process
from PhysicsTools.PatAlgos.patTemplate_cfg import *

# verbose flags for the PF2PAT modules
process.options.allowUnscheduled = cms.untracked.bool(True)

### Add MuJet Dataformats
from MuJetAnalysis.DataFormats.EventContent_version10_cff import *
process = customizePatOutput(process)

process.load("MuJetAnalysis.DataFormats.miniAODtoPAT_cff")
process.patMuons.addGenMatch = cms.bool(True)
process.patMuons.embedGenMatch = cms.bool(True)

## pick latest HLT process
process.patTrigger.processName = cms.string( "*" )
process.patTriggerEvent.processName = cms.string( "*" )

process.load("MuJetAnalysis.MuJetProducer.MuJetProducer_cff")

process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring(
		'file:out_miniaod.root'
  )
)

process.maxEvents.input = 100

process.p = cms.Path(
	process.MuJetProducers
)
