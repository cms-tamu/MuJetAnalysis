import FWCore.ParameterSet.Config as cms

from MuJetAnalysis.HLTrigger.HLT_TrkMu15_DoubleTrkMu5_v1_cff import *
from MuJetAnalysis.HLTrigger.HLT_Mu15_DoubleMu5NoVtx_v1_cff import *
from MuJetAnalysis.HLTrigger.HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx_v1_cff import *

def customizeDisplacedMuHLT(process):
    process = addHLT_TrkMu15_DoubleTrkMu5_v1(process)
    process = addHLT_Mu15_DoubleMu5NoVtx_v1(process)
    process = addHLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx_v1(process)
    return process
