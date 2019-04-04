import FWCore.ParameterSet.Config as cms
from MuJetAnalysis.MuJetProducer.MuJetProducerRun2_cfi import *

PFMuJetProducer05PXBL4PXFL3 = MuJetProducer.clone(
    maxMass = cms.double(60.),
    muons = cms.InputTag("cleanPatPFMuonsTriggerMatch"),
    selectTrackerMuons = cms.bool(False),
    selectGlobalMuons = cms.bool(False),
    minSegmentMatches = cms.int32(-1),
    minTrackerHits = cms.int32(-1),
    maxTrackerNormChi2 = cms.double(-1.0),
    barrelPixelLayer = cms.int32(4),
    endcapPixelLayer = cms.int32(3)
)

MuJetProducers = cms.Sequence(
    PFMuJetProducer05PXBL4PXFL3
)
