import FWCore.ParameterSet.Config as cms
from Configuration.StandardSequences.Eras import eras

process = cms.Process("ANALYSIS", eras.Run2_2016)

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration.Geometry.GeometryExtended2016_cff')
process.load('Configuration.Geometry.GeometryExtended2016Reco_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc')

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'file:B6687419-D919-E611-9A7C-02163E014647.root'
    )
)


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32( 100 )
)

# Define the analyzer modules
process.load('Configuration/StandardSequences/SimL1Emulator_cff')
process.load("HLTrigger.HLTanalyzers.HLTAnalyser_cfi")
#process.hltanalysis.l1GtObjectMapRecord             = cms.InputTag("")
process.hltanalysis.l1GtReadoutRecord               = cms.InputTag("gtDigis::HLT")
process.hltanalysis.EERecHits                   = cms.InputTag("ecalRecHit","EcalRecHitsEE")
process.hltanalysis.EBRecHits                   = cms.InputTag("ecalRecHit","EcalRecHitsEB")
"""
process.hltanalysis.l1GctHFBitCounts                = cms.InputTag("")
process.hltanalysis.l1GctHFRingSums                 = cms.InputTag("")
process.hltanalysis.l1GtObjectMapRecord             = cms.InputTag("")
process.hltanalysis.l1GtReadoutRecord               = cms.InputTag("")
"""

#process.analyzeThis = cms.Path( process.HLTBeginSequence + process.hltanalysis )
process.analyzeThis = cms.Path(process.hltanalysis )

process.schedule = cms.Schedule(process.analyzeThis)
