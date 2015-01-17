## import skeleton process
from PhysicsTools.PatAlgos.patTemplate_cfg import *
# verbose flags for the PF2PAT modules
process.options.allowUnscheduled = cms.untracked.bool(True)
#process.Tracer = cms.Service("Tracer")

#process.load("PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff")
#process.load("PhysicsTools.PatAlgos.selectionLayer1.selectedPatCandidates_cff")

### Add MuJet Dataformats
process.load("MuJetAnalysis.DataFormats.RECOtoPAT_cff")
process.patMuons.addGenMatch = cms.bool(True)
process.patMuons.embedGenMatch = cms.bool(True)

process.load("MuJetAnalysis.DataFormats.EventContent_version9_cff")
process.out.fileName = cms.untracked.string("out_pat.root")
process.out.outputCommands = process.patOutput.outputCommands



## ------------------------------------------------------
#  In addition you usually want to change the following
#  parameters:
## ------------------------------------------------------
#
#   process.GlobalTag.globaltag =  ...    ##  (according to https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideFrontierConditions)
#                                         ##
process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring(
    "file:/eos/uscms/store/user/lpcgem/dildick/CMSSW_73/dildick/DarkSUSY_mH_125_mGammaD_0400_ctauExp_2_8TeV_madgraph452_bridge224_LHE_pythia6_RAW/DarkSUSY_mH_125_mGammaD_0400_ctauExp_2_8TeV_madgraph452_bridge224_LHE_pythia6_RECO/ee2b69195f87ad6497ae607e47718adf/out_reco_1_1_XNE.root"
#      "file:CrabJobs/out_reco.root"
  )
)

#                                         ##
process.maxEvents.input = 100
#                                         ##
#   process.out.outputCommands = [ ... ]  ##  (e.g. taken from PhysicsTools/PatAlgos/python/patEventContent_cff.py)
#                                         ##
#process.out.fileName = 'patTuple_PF2PAT.root'
#                                         ##
#   process.options.wantSummary = False   ##  (to suppress the long output at the end of the job)

#prints modules as they are called with times
#from Validation.Performance.TimeMemoryInfo import customise
#process = customise(process)
