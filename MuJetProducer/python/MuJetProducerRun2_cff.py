import FWCore.ParameterSet.Config as cms

from MuJetAnalysis.MuJetProducer.MuJetProducerRun2_cfi import *

PFMuJetProducer05 = MuJetProducer.clone(
    maxMass = cms.double(60.),
    muons = cms.InputTag("cleanPatPFMuonsTriggerMatch"),
    selectTrackerMuons = cms.bool(False),
    selectGlobalMuons = cms.bool(False),
    groupingMode = cms.string("GroupByMassAndVertexProbOrDeltaR"),
    maxDeltaR = cms.double(0.01),
    minSegmentMatches = cms.int32(-1),
    minTrackerHits = cms.int32(-1),
    maxTrackerNormChi2 = cms.double(-1.0)
)

#Used in Phase-0 Pixel: PFMuJetProducer05PXBL3PXFL2
#PFMuJetProducer05PXBL3PXFL2 = PFMuJetProducer05.clone(
#    barrelPixelLayer = cms.int32(3),
#    endcapPixelLayer = cms.int32(2),
#)

PFMuJetProducer05PXBL4PXFL3 = PFMuJetProducer05.clone(
    barrelPixelLayer = cms.int32(4),
    endcapPixelLayer = cms.int32(3),
)

MuJetProducers = cms.Sequence(
    PFMuJetProducer05 *
    #PFMuJetProducer05PXBL3PXFL2 *
    PFMuJetProducer05PXBL4PXFL3
)
