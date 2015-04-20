## import skeleton process
from PhysicsTools.PatAlgos.patTemplate_cfg import *

# verbose flags for the PF2PAT modules
process.options.allowUnscheduled = cms.untracked.bool(True)

### Add MuJet Dataformats
from MuJetAnalysis.DataFormats.EventContent_version10_cff import *
process = customizePatOutput(process)

process.load("MuJetAnalysis.DataFormats.RECOtoPAT_cff")
process.patMuons.addGenMatch = cms.bool(True)
process.patMuons.embedGenMatch = cms.bool(True)

## pick latest HLT process
process.patTrigger.processName = cms.string( "*" )
process.patTriggerEvent.processName = cms.string( "*" )

process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring(
        'file:/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_13TeV-madgraph452_bridge224_LHE_pythia8_731p2_GEN_v2/DarkSUSY_mH_125_mGammaD_0250_ctau_0_13TeV_madgraph452_bridge224_LHE_pythia8_731p2_RECO/0c27b465590c55ed0293b8cec2e2e17b/out_reco_1_1_cp4.root'
  )
)

process.maxEvents.input = -1

process.load("MuJetAnalysis.MuJetProducer.MuJetProducer_cff")
process.load("MuJetAnalysis.CutFlowAnalyzer.CutFlowAnalyzer_cfi")

process.p = cms.Path(
    process.TrackerMuJetProducer05 *
    process.PFMuJetProducer05 *
    process.cutFlowAnalyzer
)

process.outpath = cms.EndPath(process.out)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("out_ana.root")
)
