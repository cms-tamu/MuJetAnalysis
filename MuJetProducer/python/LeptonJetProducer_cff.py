import FWCore.ParameterSet.Config as cms

# TransientTrackBuilder is needed for vertexing in MuJetProducer
#from TrackingTools.TransientTrack.TransientTrackBuilder_cfi import *
#from Configuration.Geometry.GeometryIdeal_cff import *
#from Configuration.StandardSequences.MagneticField_cff import *
#from TrackingTools.GeomPropagators.SmartPropagator_cff import *
from MuJetAnalysis.MuJetProducer.MuJetProducer_cfi import *
from MuJetAnalysis.MuJetProducer.ElectronJetProducer_cfi import *

TrackerMuJetProducer05 = MuJetProducer.clone(
    maxMass = cms.double(5.),
    muons = cms.InputTag("cleanPatTrackerMuonsTriggerMatch"),
    selectTrackerMuons = cms.bool(True),
    selectGlobalMuons = cms.bool(False),
    groupingMode = cms.string("GroupByMassAndVertexProbOrDeltaR"),
    maxDeltaR = cms.double(0.01),
    minSegmentMatches = cms.int32(2),
    minTrackerHits = cms.int32(8),
    maxTrackerNormChi2 = cms.double(4.0)
)

PFMuJetProducer05 = MuJetProducer.clone(
    maxMass = cms.double(5.),
    muons = cms.InputTag("cleanPatPFMuonsTriggerMatch"),
    selectTrackerMuons = cms.bool(False),
    selectGlobalMuons = cms.bool(False),
    groupingMode = cms.string("GroupByMassAndVertexProbOrDeltaR"),
    maxDeltaR = cms.double(0.01),
#    minSegmentMatches = cms.int32(2),
    minSegmentMatches = cms.int32(-1),
    minTrackerHits = cms.int32(-1),
    maxTrackerNormChi2 = cms.double(-1.0)
)
