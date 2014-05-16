from TrackingTools.TransientTrack.TransientTrackBuilder_cfi import *
from Configuration.StandardSequences.Geometry_cff import *
from Configuration.StandardSequences.MagneticField_cff import *
from TrackingTools.GeomPropagators.SmartPropagator_cff import *
from TrackingTools.MaterialEffects.MaterialPropagator_cfi import *
from TrackingTools.MaterialEffects.OppositeMaterialPropagator_cfi import *

import PhysicsTools.PatAlgos.patSequences_cff

muonMatch = PhysicsTools.PatAlgos.patSequences_cff.muonMatch.clone(src = cms.InputTag("muons"),
                                                                   resolveByMatchQuality = cms.bool(True))
patMuons = PhysicsTools.PatAlgos.patSequences_cff.patMuons.clone(muonSource = cms.InputTag("muons"),
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
selectedPatMuons = PhysicsTools.PatAlgos.patSequences_cff.selectedPatMuons.clone(src = cms.InputTag("patMuons"),
    cut = cms.string("pt > 5.0 && isTrackerMuon() && numberOfMatches() > 1 && -2.4 < eta() && eta() < 2.4"))
cleanPatMuons = PhysicsTools.PatAlgos.patSequences_cff.cleanPatMuons.clone(src = cms.InputTag("selectedPatMuons"))
countPatMuons = PhysicsTools.PatAlgos.patSequences_cff.countPatMuons.clone(src = cms.InputTag("cleanPatMuons"))

from PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cfi import *
from PhysicsTools.PatAlgos.triggerLayer1.triggerEventProducer_cfi import *
from PhysicsTools.PatAlgos.triggerLayer1.triggerMatcher_cfi import *

cleanMuonTriggerMatchHLTMu15 = cleanMuonTriggerMatchHLTMu20.clone(matchedCuts = cms.string('path("HLT_Mu15_*")'))
cleanMuonTriggerMatchHLTMu20copy = cleanMuonTriggerMatchHLTMu20.clone(matchedCuts = cms.string('path("HLT_Mu20_*")'))
cleanMuonTriggerMatchHLTMu24 = cleanMuonTriggerMatchHLTMu20.clone(matchedCuts = cms.string('path("HLT_Mu24_*")'))
cleanMuonTriggerMatchHLTMu30 = cleanMuonTriggerMatchHLTMu20.clone(matchedCuts = cms.string('path("HLT_Mu30_*")'))
cleanMuonTriggerMatchHLTMu40 = cleanMuonTriggerMatchHLTMu20.clone(matchedCuts = cms.string('path("HLT_Mu40_*")'))
cleanMuonTriggerMatchHLTIsoMu = cleanMuonTriggerMatchHLTMu20.clone(matchedCuts = cms.string('path("HLT_IsoMu*")'))
cleanMuonTriggerMatchHLTDoubleMu = cleanMuonTriggerMatchHLTMu20.clone(matchedCuts = cms.string('path("HLT_DoubleMu*_v*")'))
cleanMuonTriggerMatchHLTMu13Mu8 = cleanMuonTriggerMatchHLTMu20.clone(matchedCuts = cms.string('path("HLT_Mu13_Mu8_v*")'))
cleanMuonTriggerMatchHLTMu17Mu8 = cleanMuonTriggerMatchHLTMu20.clone(matchedCuts = cms.string('path("HLT_Mu17_Mu8_v*")'))

cleanPatMuonsTriggerMatch = cms.EDProducer("PATTriggerMatchMuonEmbedder",
                                           src = cms.InputTag("cleanPatMuons"),
                                           matches = cms.VInputTag("cleanMuonTriggerMatchHLTMu15", "cleanMuonTriggerMatchHLTMu20copy", "cleanMuonTriggerMatchHLTMu24", "cleanMuonTriggerMatchHLTMu30", "cleanMuonTriggerMatchHLTMu40", "cleanMuonTriggerMatchHLTIsoMu","cleanMuonTriggerMatchHLTDoubleMu","cleanMuonTriggerMatchHLTMu13Mu8","cleanMuonTriggerMatchHLTMu17Mu8")) 

patTriggerEvent = PhysicsTools.PatAlgos.triggerLayer1.triggerEventProducer_cfi.patTriggerEvent.clone()

import os
nonstandard_trigger = os.getenv("NONSTANDARD_TRIGGER")
if nonstandard_trigger is not None:
    patTriggerEvent.processName = cms.string(nonstandard_trigger)
    patTrigger.processName = cms.string(nonstandard_trigger)

patify = cms.Sequence(muonMatch * patMuons * selectedPatMuons * cleanPatMuons * countPatMuons * patTrigger * patTriggerEvent * cleanMuonTriggerMatchHLTMu15 * cleanMuonTriggerMatchHLTMu20copy * cleanMuonTriggerMatchHLTMu24 * cleanMuonTriggerMatchHLTMu30 * cleanMuonTriggerMatchHLTMu40 * cleanMuonTriggerMatchHLTIsoMu * cleanMuonTriggerMatchHLTDoubleMu * cleanMuonTriggerMatchHLTMu13Mu8 * cleanMuonTriggerMatchHLTMu17Mu8 * cleanPatMuonsTriggerMatch)
patifyData = cms.Sequence(patMuons * selectedPatMuons * cleanPatMuons * countPatMuons * patTrigger * patTriggerEvent * cleanMuonTriggerMatchHLTMu15 * cleanMuonTriggerMatchHLTMu20copy * cleanMuonTriggerMatchHLTMu24 * cleanMuonTriggerMatchHLTMu30 * cleanMuonTriggerMatchHLTMu40 * cleanMuonTriggerMatchHLTIsoMu * cleanMuonTriggerMatchHLTDoubleMu * cleanMuonTriggerMatchHLTMu13Mu8 * cleanMuonTriggerMatchHLTMu17Mu8 * cleanPatMuonsTriggerMatch)
