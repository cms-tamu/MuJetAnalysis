import FWCore.ParameterSet.Config as cms
import os
import sys

process = cms.Process("CutFlowAnalyzer")
process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.Geometry.GeometryRecoDB_cff")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("MuJetAnalysis.CutFlowAnalyzer.CutFlowAnalyzer_cfi")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')

process.source = cms.Source("PoolSource",
    secondaryFileNames = cms.untracked.vstring(),
    fileNames = cms.untracked.vstring(
        'file:output.root'
    )
)


process.maxEvents = cms.untracked.PSet( 
    input = cms.untracked.int32(-1) 
)

process.MessageLogger = cms.Service("MessageLogger", 
    destinations = cms.untracked.vstring("cout"), 
    cout = cms.untracked.PSet(threshold = cms.untracked.string("ERROR"))
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("out_ana.root")
)

process.p = cms.Path(
    process.cutFlowAnalyzer
)

