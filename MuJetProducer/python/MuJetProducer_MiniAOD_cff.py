import FWCore.ParameterSet.Config as cms

from MuJetAnalysis.MuJetProducer.MuJetProducer_MiniAOD_cfi import *

#TrackerMuJetProducer05 = MuJetProducer.clone(
#    maxMass = cms.double(58.),
#    muons = cms.InputTag("cleanPatTrackerMuonsTriggerMatch"),
#    selectTrackerMuons = cms.bool(True),
#    selectGlobalMuons = cms.bool(False),
#    groupingMode = cms.string("GroupByMassAndVertexProbOrDeltaR"),
#    maxDeltaR = cms.double(0.01),
#    minSegmentMatches = cms.int32(2),
#    minTrackerHits = cms.int32(8),
#    maxTrackerNormChi2 = cms.double(4.0)
#)

PFMuJetProducer05 = MuJetProducer.clone(
    maxMass = cms.double(9.),
    muons = cms.InputTag("cleanPatPFMuonsTriggerMatch"),
    selectTrackerMuons = cms.bool(False),
    selectGlobalMuons = cms.bool(False),
    groupingMode = cms.string("GroupByMassAndVertexProbOrDeltaR"),
    maxDeltaR = cms.double(0.01),
    minSegmentMatches = cms.int32(-1),
    minTrackerHits = cms.int32(-1),
    maxTrackerNormChi2 = cms.double(-1.0)
)

#TrackerMuJetProducer05PXBL3PXFL2 = TrackerMuJetProducer05.clone(
#    barrelPixelLayer = cms.int32(3),
#    endcapPixelLayer = cms.int32(2),
#)

#PFMuJetProducer05PXBL3PXFL2 = PFMuJetProducer05.clone(
#    barrelPixelLayer = cms.int32(3),
#    endcapPixelLayer = cms.int32(2),
#)

#TrackerMuJetProducer05PXBL4PXFL3 = TrackerMuJetProducer05.clone(
#    barrelPixelLayer = cms.int32(4),
#    endcapPixelLayer = cms.int32(3),
#)
PFMuJetProducer05PXBL4PXFL3 = PFMuJetProducer05.clone(
    barrelPixelLayer = cms.int32(4),
    endcapPixelLayer = cms.int32(3),
)

MuJetProducers = cms.Sequence(
    #TrackerMuJetProducer05 *
    PFMuJetProducer05 *
    #TrackerMuJetProducer05PXBL3PXFL2 *
    #PFMuJetProducer05PXBL3PXFL2 *
    #TrackerMuJetProducer05PXBL4PXFL3 *
    PFMuJetProducer05PXBL4PXFL3
)
