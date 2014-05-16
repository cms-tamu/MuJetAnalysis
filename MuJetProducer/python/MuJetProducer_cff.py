import FWCore.ParameterSet.Config as cms

# TransientTrackBuilder is needed for vertexing in MuJetProducer
from TrackingTools.TransientTrack.TransientTrackBuilder_cfi import *
from Configuration.Geometry.GeometryIdeal_cff import *
from Configuration.StandardSequences.MagneticField_cff import *
from TrackingTools.GeomPropagators.SmartPropagator_cff import *

from MuJetAnalysis.MuJetProducer.MuJetProducer_cfi import *
