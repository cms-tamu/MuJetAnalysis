## import skeleton process
from PhysicsTools.PatAlgos.patTemplate_cfg import *

from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
###process.GlobalTag = GlobalTag(process.GlobalTag, '74X_dataRun2_Prompt_v2')
process.GlobalTag = GlobalTag(process.GlobalTag, '76X_dataRun2_v15')

# verbose flags for the PF2PAT modules
process.options.allowUnscheduled = cms.untracked.bool(True)

### Add MuJet Dataformats
from MuJetAnalysis.DataFormats.EventContent_version10_cff import *
process = customizePatOutput(process)

process.load("MuJetAnalysis.DataFormats.RECOtoPAT_cff")
#process.patMuons.addGenMatch = cms.bool(True)
#process.patMuons.embedGenMatch = cms.bool(True)
process.patMuons.addGenMatch = cms.bool(False)
process.patMuons.embedGenMatch = cms.bool(False)

## pick latest HLT process
process.patTrigger.processName = cms.string( "*" )
process.patTriggerEvent.processName = cms.string( "*" )

process.load("MuJetAnalysis.MuJetProducer.MuJetProducer_cff")
process.load("MuJetAnalysis.CutFlowAnalyzer.CutFlowAnalyzer_cfi")
process.cutFlowAnalyzer.fillGenLevel = cms.bool(False)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
		"file:002DAE91-77A7-E511-B61B-00266CFAEA48.root"
    )
)

process.maxEvents.input = -1

process.p = cms.Path(
	process.MuJetProducers * 
    process.cutFlowAnalyzer
)

process.outpath = cms.EndPath(process.out)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("out_ana.root")
)
