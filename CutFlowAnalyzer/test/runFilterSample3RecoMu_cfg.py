import FWCore.ParameterSet.Config as cms

process = cms.Process("SKIM")
# initialize  MessageLogger
process.load("FWCore.MessageService.MessageLogger_cfi")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring("/store/data/Run2018B/MET/MINIAOD/17Sep2018-v1/100000/05924C04-3B47-3243-9030-6D9AE5964620.root")
)
process.maxEvents = cms.untracked.PSet ( input = cms.untracked.int32 ( 1000 ) )

process.myfilter = cms.EDFilter("FilterSample3RecoMu_MiniAOD")

process.filterPath = cms.Path(process.myfilter)

process.output = cms.OutputModule(
    "PoolOutputModule",
    fileName = cms.untracked.string( "Filter.root" ),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring("filterPath")
        )
    )

process.out = cms.EndPath( process.output )
