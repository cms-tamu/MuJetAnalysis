
import FWCore.ParameterSet.Config as cms

process = cms.Process("SKIM")
# initialize  MessageLogger
process.load("FWCore.MessageService.MessageLogger_cfi")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring("file:/uscms_data/d3/dildick/work/HLTDev2017MC/CMSSW_9_2_9/src/708FA0FE-A770-E711-B738-02163E011E1A.root")
)
process.maxEvents = cms.untracked.PSet ( input = cms.untracked.int32 ( 1000 ) )

process.myfilter = cms.EDFilter("FilterSample3RecoMu")

process.filterPath = cms.Path(process.myfilter)

process.output = cms.OutputModule(
    "PoolOutputModule",
    fileName = cms.untracked.string( "Filter.root" ),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring("filterPath")
        )
    )

process.out = cms.EndPath( process.output )
