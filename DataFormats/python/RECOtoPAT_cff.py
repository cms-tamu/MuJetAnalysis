from TrackingTools.TransientTrack.TransientTrackBuilder_cfi import *
from TrackingTools.GeomPropagators.SmartPropagator_cff import *
from TrackingTools.MaterialEffects.MaterialPropagator_cfi import *
from TrackingTools.MaterialEffects.OppositeMaterialPropagator_cfi import *
from PhysicsTools.PatAlgos.patSequences_cff import *
from PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cff import *

## muon matcher
muonMatch.src = cms.InputTag("muons")
muonMatch.resolveByMatchQuality = cms.bool(True)

## pat muon
patMuons.muonSource = cms.InputTag("muons")
patMuons.genParticleMatch = cms.InputTag("muonMatch")
patMuons.addTeVRefits = cms.bool(False)
patMuons.embedTrack = cms.bool(True)
patMuons.embedCombinedMuon = cms.bool(True)
patMuons.embedStandAloneMuon = cms.bool(True)
patMuons.embedPickyMuon = cms.bool(False)
patMuons.embedTpfmsMuon = cms.bool(False)
patMuons.embedHighLevelSelection = cms.bool(True)
patMuons.usePV = cms.bool(True)
patMuons.beamLineSrc = cms.InputTag("offlineBeamSpot")
patMuons.pvSrc = cms.InputTag("offlinePrimaryVertices")
patMuons.isolation = cms.PSet()
patMuons.isoDeposits = cms.PSet()
patMuons.embedCaloMETMuonCorrs = cms.bool(False)
patMuons.embedTcMETMuonCorrs = cms.bool(False)

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

# This module is derived from from https://github.com/cms-sw/cmssw/blob/CMSSW_7_3_X/PhysicsTools/PatAlgos/python/triggerLayer1/triggerMatcherExamples_cfi.py
cleanMuonTriggerMatchHLTMu17 = cms.EDProducer("PATTriggerMatcherDRDPtLessByR", # match by DeltaR only, best match by DeltaR
    src     = cms.InputTag( "cleanPatMuons" ),
    matched = cms.InputTag( "patTrigger" ),  # default producer label as defined in PhysicsTools/PatAlgos/python/triggerLayer1/triggerProducer_cfi.py
    matchedCuts = cms.string( 'path( "HLT_Mu17_v*" )' ),
    maxDPtRel = cms.double( 0.5 ),
    maxDeltaR = cms.double( 0.5 ),
    resolveAmbiguities    = cms.bool( True ),        # only one match per trigger object
    resolveByMatchQuality = cms.bool( True )        # take best match found per reco object: by DeltaR here (s. above)
)


# Trigger match
#    First matcher from PhysicsTools/PatAlgos/python/triggerLayer1/triggerMatcher_cfi.py
#    is cleanMuonTriggerMatchHLTMu17 . Clone it!
#    Note in 2012 wildcard HLT_Mu* includes ONLY muon trigger. No more HLT_MultiVertex6 and such!
# This is trigger match for Tracker muons
cleanTrackerMuonTriggerMatchHLTMu = cleanMuonTriggerMatchHLTMu17.clone(
    src = cms.InputTag( "cleanPatTrackerMuons" ),
    matchedCuts = cms.string('path("HLT_Mu*")')
)
cleanTrackerMuonTriggerMatchHLTIsoMu = cleanMuonTriggerMatchHLTMu17.clone(
    src = cms.InputTag( "cleanPatTrackerMuons" ),
    matchedCuts = cms.string('path("HLT_IsoMu*")')
)
cleanTrackerMuonTriggerMatchHLTDoubleMu = cleanMuonTriggerMatchHLTMu17.clone(
    src = cms.InputTag( "cleanPatTrackerMuons" ),
    matchedCuts = cms.string('path("HLT_DoubleMu*_v*")')
)
cleanTrackerMuonTriggerMatchHLTTrkMu12DoubleTrkMu5 = cleanMuonTriggerMatchHLTMu17.clone(
    src = cms.InputTag( "cleanPatTrackerMuons" ),
    matchedCuts = cms.string('path("HLT_TrkMu12_DoubleTrkMu5NoFiltersNoVtx_v*")')
)
cleanTrackerMuonTriggerMatchHLTTrkMu16DoubleTrkMu6 = cleanMuonTriggerMatchHLTMu17.clone(
    src = cms.InputTag( "cleanPatTrackerMuons" ),
    matchedCuts = cms.string('path("HLT_TrkMu16_DoubleTrkMu6NoFiltersNoVtx_v*")')
)
cleanTrackerMuonTriggerMatchHLTTrkMu17DoubleTrkMu8 = cleanMuonTriggerMatchHLTMu17.clone(
    src = cms.InputTag( "cleanPatTrackerMuons" ),
    matchedCuts = cms.string('path("HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx_v*")')
)
cleanPatTrackerMuonsTriggerMatch = cms.EDProducer("PATTriggerMatchMuonEmbedder",
    src = cms.InputTag("cleanPatTrackerMuons"),
    matches = cms.VInputTag(
        "cleanTrackerMuonTriggerMatchHLTMu",
        "cleanTrackerMuonTriggerMatchHLTIsoMu",
        "cleanTrackerMuonTriggerMatchHLTDoubleMu",
        "cleanTrackerMuonTriggerMatchHLTTrkMu12DoubleTrkMu5",
        "cleanTrackerMuonTriggerMatchHLTTrkMu16DoubleTrkMu6",
        "cleanTrackerMuonTriggerMatchHLTTrkMu17DoubleTrkMu8"
    )
)



# This is trigger match for PF muons
cleanPFMuonTriggerMatchHLTMu = cleanMuonTriggerMatchHLTMu17.clone(
    src = cms.InputTag( "cleanPatPFMuons" ),
    matchedCuts = cms.string('path("HLT_Mu*")')
)
cleanPFMuonTriggerMatchHLTIsoMu = cleanMuonTriggerMatchHLTMu17.clone(
    src = cms.InputTag( "cleanPatPFMuons" ),
    matchedCuts = cms.string('path("HLT_IsoMu*")')
)
cleanPFMuonTriggerMatchHLTDoubleMu = cleanMuonTriggerMatchHLTMu17.clone(
    src = cms.InputTag( "cleanPatPFMuons" ),
    matchedCuts = cms.string('path("HLT_DoubleMu*_v*")')
)
cleanPFMuonTriggerMatchHLTTrkMu12DoubleTrkMu5 = cleanMuonTriggerMatchHLTMu17.clone(
    src = cms.InputTag( "cleanPatPFMuons" ),
    matchedCuts = cms.string('path("HLT_TrkMu12_DoubleTrkMu5NoFiltersNoVtx_v*")')
)
cleanPFMuonTriggerMatchHLTTrkMu16DoubleTrkMu6 = cleanMuonTriggerMatchHLTMu17.clone(
    src = cms.InputTag( "cleanPatPFMuons" ),
    matchedCuts = cms.string('path("HLT_TrkMu16_DoubleTrkMu6NoFiltersNoVtx_v*")')
)
cleanPFMuonTriggerMatchHLTTrkMu17DoubleTrkMu8 = cleanMuonTriggerMatchHLTMu17.clone(
    src = cms.InputTag( "cleanPatPFMuons" ),
    matchedCuts = cms.string('path("HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx_v*")')
)
cleanPatPFMuonsTriggerMatch = cms.EDProducer("PATTriggerMatchMuonEmbedder",
    src = cms.InputTag("cleanPatPFMuons"),
    matches = cms.VInputTag(
        "cleanPFMuonTriggerMatchHLTMu",
        "cleanPFMuonTriggerMatchHLTIsoMu",
        "cleanPFMuonTriggerMatchHLTDoubleMu",
        "cleanPFMuonTriggerMatchHLTTrkMu12DoubleTrkMu5",
        "cleanPFMuonTriggerMatchHLTTrkMu16DoubleTrkMu6",
        "cleanPFMuonTriggerMatchHLTTrkMu17DoubleTrkMu8"
    )
)
patifyTrackerMuon = cms.Sequence(
    selectedPatTrackerMuons *
    cleanPatTrackerMuons *
    countPatTrackerMuons *
    cleanTrackerMuonTriggerMatchHLTMu *
    cleanTrackerMuonTriggerMatchHLTIsoMu *
    cleanTrackerMuonTriggerMatchHLTDoubleMu *
    cleanTrackerMuonTriggerMatchHLTTrkMu12DoubleTrkMu5 *
    cleanTrackerMuonTriggerMatchHLTTrkMu16DoubleTrkMu6 *
    cleanTrackerMuonTriggerMatchHLTTrkMu17DoubleTrkMu8 *
    cleanPatTrackerMuonsTriggerMatch
)
patifyPFMuon = cms.Sequence(
    selectedPatPFMuons *
    cleanPatPFMuons *
    countPatPFMuons *
    cleanPFMuonTriggerMatchHLTMu *
    cleanPFMuonTriggerMatchHLTIsoMu *
    cleanPFMuonTriggerMatchHLTDoubleMu *
    cleanPFMuonTriggerMatchHLTTrkMu12DoubleTrkMu5 *
    cleanPFMuonTriggerMatchHLTTrkMu16DoubleTrkMu6 *
    cleanPFMuonTriggerMatchHLTTrkMu17DoubleTrkMu8 *
    cleanPatPFMuonsTriggerMatch
)

patifyData = cms.Sequence(
    pfParticleSelectionForIsoSequence *
    muonPFIsolationPATSequence *
    patMuons *
    patTrigger *
    patTriggerEvent *
    patifyTrackerMuon *
    patifyPFMuon
#    patJetCorrections *
#    patJetCharge *
#    patJets
)

patifyMC = cms.Sequence(
    muonMatch *
    patifyData
)
