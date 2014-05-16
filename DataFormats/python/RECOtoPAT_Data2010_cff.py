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
    cut = cms.string("pt > 5.0 && ((isTrackerMuon() && numberOfMatches() > 1.5 && -2.4 < eta() && eta() < 2.4) || isGlobalMuon() || isStandAloneMuon())"))
cleanPatMuons = PhysicsTools.PatAlgos.patSequences_cff.cleanPatMuons.clone(src = cms.InputTag("selectedPatMuons"))
countPatMuons = PhysicsTools.PatAlgos.patSequences_cff.countPatMuons.clone(src = cms.InputTag("cleanPatMuons"))

from PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cfi import *
from PhysicsTools.PatAlgos.triggerLayer1.triggerEventProducer_cfi import *
from PhysicsTools.PatAlgos.triggerLayer1.triggerMatcher_cfi import *

# HLT_Mu5 -- 4e29 (prescale 1), 8e29 (prescale 1), 2e30 (prescale 1), 3.5e30 (prescale 1)
# HLT_Mu5 -- 7.5E30 (prescale 7), 9.0E30 (prescale 40), 2E31 (prescale 84)
cleanMuonTriggerMatchHLTMu5  = cleanMuonTriggerMatchHLTMu20.clone(matchedCuts = cms.string('path("HLT_Mu5")'))
# HLT_Mu7 -- 7.5E30 (prescale 1), 9.0E30 (prescale 1)
# HLT_Mu7 -- 2E31 (prescale 10)
cleanMuonTriggerMatchHLTMu7  = cleanMuonTriggerMatchHLTMu20.clone(matchedCuts = cms.string('path("HLT_Mu7")'))
# HLT_Mu9 -- 4e29 (prescale 1), 8e29 (prescale 1), 2e30 (prescale 1), 3.5e30 (prescale 1), 7.5E30 (prescale 1), 9.0E30 (prescale 1), 2E31 (prescale 1)
# HLT_Mu9 -- 6E31 (prescale 10), 2E32 (prescale 30)
cleanMuonTriggerMatchHLTMu9  = cleanMuonTriggerMatchHLTMu20.clone(matchedCuts = cms.string('path("HLT_Mu9")'))
# HLT_Mu11 -- 6E31 (prescale 1), 2E32 (prescale 20)
cleanMuonTriggerMatchHLTMu11 = cleanMuonTriggerMatchHLTMu20.clone(matchedCuts = cms.string('path("HLT_Mu11")'))
# HLT_Mu13 -- 2E32 (prescale 10)
cleanMuonTriggerMatchHLTMu13 = cleanMuonTriggerMatchHLTMu20.clone(matchedCuts = cms.string('path("HLT_Mu13_v*")'))
# HLT_Mu15 -- 2E32 (prescale 1)
cleanMuonTriggerMatchHLTMu15 = cleanMuonTriggerMatchHLTMu20.clone(matchedCuts = cms.string('path("HLT_Mu15_v*")'))

cleanPatMuonsTriggerMatch = cms.EDProducer("PATTriggerMatchMuonEmbedder",
                                           src = cms.InputTag("cleanPatMuons"),
                                           matches = cms.VInputTag("cleanMuonTriggerMatchHLTMu5", "cleanMuonTriggerMatchHLTMu7", "cleanMuonTriggerMatchHLTMu9", "cleanMuonTriggerMatchHLTMu11", "cleanMuonTriggerMatchHLTMu13", "cleanMuonTriggerMatchHLTMu15"))

patTriggerEvent = PhysicsTools.PatAlgos.triggerLayer1.triggerEventProducer_cfi.patTriggerEvent.clone()

import os
nonstandard_trigger = os.getenv("NONSTANDARD_TRIGGER")
if nonstandard_trigger is not None:
    patTriggerEvent.processName = cms.string(nonstandard_trigger)
    patTrigger.processName = cms.string(nonstandard_trigger)

patify = cms.Sequence(muonMatch * patMuons * selectedPatMuons * cleanPatMuons * countPatMuons * patTrigger * patTriggerEvent * cleanMuonTriggerMatchHLTMu5 * cleanMuonTriggerMatchHLTMu7 * cleanMuonTriggerMatchHLTMu9 * cleanMuonTriggerMatchHLTMu11 * cleanMuonTriggerMatchHLTMu13 * cleanMuonTriggerMatchHLTMu15 * cleanPatMuonsTriggerMatch)
patifyData = cms.Sequence(patMuons * selectedPatMuons * cleanPatMuons * countPatMuons * patTrigger * patTriggerEvent * cleanMuonTriggerMatchHLTMu5 * cleanMuonTriggerMatchHLTMu7 * cleanMuonTriggerMatchHLTMu9 * cleanMuonTriggerMatchHLTMu11 * cleanMuonTriggerMatchHLTMu13 * cleanMuonTriggerMatchHLTMu15 * cleanPatMuonsTriggerMatch)

