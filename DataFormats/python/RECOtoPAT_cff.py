from TrackingTools.TransientTrack.TransientTrackBuilder_cfi import *
from Configuration.Geometry.GeometryIdeal_cff import *
from Configuration.StandardSequences.MagneticField_cff import *
from TrackingTools.GeomPropagators.SmartPropagator_cff import *
from TrackingTools.MaterialEffects.MaterialPropagator_cfi import *
from TrackingTools.MaterialEffects.OppositeMaterialPropagator_cfi import *
from PhysicsTools.PatAlgos.patSequences_cff import *

muonMatch = muonMatch.clone(
    src = cms.InputTag("muons"),
    resolveByMatchQuality = cms.bool(True)
)
patMuons = patMuons.clone(
    muonSource = cms.InputTag("muons"),
    genParticleMatch = cms.InputTag("muonMatch"),
    addTeVRefits = cms.bool(False),
    embedTrack = cms.bool(True),
    embedCombinedMuon = cms.bool(True),
    embedStandAloneMuon = cms.bool(True),
    embedPickyMuon = cms.bool(False),
    embedTpfmsMuon = cms.bool(False),
    embedHighLevelSelection = cms.bool(True),
    usePV = cms.bool(True),
    beamLineSrc = cms.InputTag("offlineBeamSpot"),
    pvSrc = cms.InputTag("offlinePrimaryVertices"),
    isolation = cms.PSet(),
    isoDeposits = cms.PSet(),
    embedCaloMETMuonCorrs = cms.bool(False),
    embedTcMETMuonCorrs = cms.bool(False),
)
# Tracker Muons Part
selectedPatTrackerMuons = selectedPatMuons.clone(
    src = cms.InputTag("patMuons"),
    cut = cms.string("pt > 5.0 && isTrackerMuon() && numberOfMatches() > 1 && -2.4 < eta() && eta() < 2.4")
)
cleanPatTrackerMuons = cleanPatMuons.clone(
    src = cms.InputTag("selectedPatTrackerMuons")
)
countPatTrackerMuons = countPatMuons.clone(
    src = cms.InputTag("cleanPatTrackerMuons")
)
# PF Muons Part
selectedPatPFMuons = selectedPatMuons.clone(
    src = cms.InputTag("patMuons"),
    #"Loose Muon" requirement on PF muons as recommended by Muon POG:
    #https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonId#Loose_Muon
    cut = cms.string("pt > 5.0 && isPFMuon() && ( isTrackerMuon() || isGlobalMuon() ) && -2.4 < eta() && eta() < 2.4")
)
cleanPatPFMuons = cleanPatMuons.clone(
    src = cms.InputTag("selectedPatPFMuons")
)
countPatPFMuons = countPatMuons.clone(
    src = cms.InputTag("cleanPatPFMuons")
)

from PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cfi import *
from PhysicsTools.PatAlgos.triggerLayer1.triggerEventProducer_cfi import *
from PhysicsTools.PatAlgos.triggerLayer1.triggerMatcher_cfi import *

# Trigger match
#    First matcher from PhysicsTools/PatAlgos/python/triggerLayer1/triggerMatcher_cfi.py
#    is cleanMuonTriggerMatchHLTMu20 . Clone it!
#    Note in 2012 wildcard HLT_Mu* includes ONLY muon trigger. No more HLT_MultiVertex6 and such!
# This is trigger match for Tracker muons
cleanTrackerMuonTriggerMatchHLTMu = cleanMuonTriggerMatchHLTMu20.clone(src = cms.InputTag( "cleanPatTrackerMuons" ),
    matchedCuts = cms.string('path("HLT_Mu*")'))
cleanTrackerMuonTriggerMatchHLTIsoMu = cleanMuonTriggerMatchHLTMu20.clone(src = cms.InputTag( "cleanPatTrackerMuons" ),
    matchedCuts = cms.string('path("HLT_IsoMu*")'))
cleanTrackerMuonTriggerMatchHLTDoubleMu = cleanMuonTriggerMatchHLTMu20.clone(src = cms.InputTag( "cleanPatTrackerMuons" ),
    matchedCuts = cms.string('path("HLT_DoubleMu*_v*")'))
cleanPatTrackerMuonsTriggerMatch = cms.EDProducer("PATTriggerMatchMuonEmbedder",
                                           src = cms.InputTag("cleanPatTrackerMuons"),
                                           matches = cms.VInputTag("cleanTrackerMuonTriggerMatchHLTMu",
                                                                   "cleanTrackerMuonTriggerMatchHLTIsoMu",
                                                                   "cleanTrackerMuonTriggerMatchHLTDoubleMu"))
# This is trigger match for PF muons
cleanPFMuonTriggerMatchHLTMu = cleanMuonTriggerMatchHLTMu20.clone(src = cms.InputTag( "cleanPatPFMuons" ),
    matchedCuts = cms.string('path("HLT_Mu*")')) 
cleanPFMuonTriggerMatchHLTIsoMu = cleanMuonTriggerMatchHLTMu20.clone(src = cms.InputTag( "cleanPatPFMuons" ),
    matchedCuts = cms.string('path("HLT_IsoMu*")'))
cleanPFMuonTriggerMatchHLTDoubleMu = cleanMuonTriggerMatchHLTMu20.clone(src = cms.InputTag( "cleanPatPFMuons" ),
    matchedCuts = cms.string('path("HLT_DoubleMu*_v*")'))
cleanPatPFMuonsTriggerMatch = cms.EDProducer("PATTriggerMatchMuonEmbedder",
                                           src = cms.InputTag("cleanPatPFMuons"),
                                           matches = cms.VInputTag("cleanPFMuonTriggerMatchHLTMu",
                                                                   "cleanPFMuonTriggerMatchHLTIsoMu",
                                                                   "cleanPFMuonTriggerMatchHLTDoubleMu"))
                                                                   
patifyTrackerMuon = cms.Sequence(
    selectedPatTrackerMuons * 
    cleanPatTrackerMuons * 
    countPatTrackerMuons * 
    cleanTrackerMuonTriggerMatchHLTMu * 
    cleanTrackerMuonTriggerMatchHLTIsoMu * 
    cleanTrackerMuonTriggerMatchHLTDoubleMu * 
    cleanPatTrackerMuonsTriggerMatch
)
patifyPFMuon = cms.Sequence(
    selectedPatPFMuons * 
    cleanPatPFMuons * 
    countPatPFMuons * 
    cleanPFMuonTriggerMatchHLTMu * 
    cleanPFMuonTriggerMatchHLTIsoMu * 
    cleanPFMuonTriggerMatchHLTDoubleMu * 
    cleanPatPFMuonsTriggerMatch
)

patifyData = cms.Sequence(
    patMuons * 
    patTrigger * 
    patTriggerEvent * 
    patifyTrackerMuon * 
    patifyPFMuon
)
patifyMC = cms.Sequence(
    muonMatch * 
    patifyData
)

patDefaultSequence = cms.Sequence()
patCandidates = cms.Sequence()
makePatMuons = cms.Sequence()
