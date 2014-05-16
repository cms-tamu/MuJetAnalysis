import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Services_cff import *
from Configuration.StandardSequences.Geometry_cff import *
from Configuration.StandardSequences.MagneticField_38T_cff import *
from Configuration.StandardSequences.Reconstruction_cff import *

ReRecoTracks = cms.Sequence(siPixelRecHits * siStripMatchedRecHits * recopixelvertexing * ckftracks * muonreco)
