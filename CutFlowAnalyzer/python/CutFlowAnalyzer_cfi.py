
import FWCore.ParameterSet.Config as cms

cutFlowAnalyzer = cms.EDAnalyzer('CutFlowAnalyzer',
    analyzerDebug = cms.int32(0),
    muons = cms.InputTag("cleanPatPFMuonsTriggerMatch"),
    beamSpot = cms.InputTag("offlineBeamSpot"),
    muJets = cms.InputTag("PFMuJetProducer05"),
    muJetOrphans = cms.InputTag("PFMuJetProducer05", "Orphans"),
    triggerEvent = cms.InputTag("patTriggerEvent"),
    tracks = cms.InputTag("generalTracks"),
    TriggerResults = cms.InputTag("TriggerResults","","HLT"),
    TrackRefitter = cms.InputTag("TrackRefitter"),
    genParticles = cms.InputTag("genParticles"),
    primaryVertices = cms.InputTag("offlinePrimaryVertices"),
    PATJet = cms.InputTag("patJets"),
    DiMuons_Iso_Max = cms.double(2.0),
    #nThrowsConsistentVertexesCalculator = cms.int32(0),
    barrelPixelLayer = cms.int32(1),
    endcapPixelLayer = cms.int32(1),
    #runDisplacedVtxFinder = cms.bool(False),
    Traj = cms.InputTag("TrackRefitter"),
    NavigationSchool   = cms.string('SimpleNavigationSchool'),
    MeasurementTracker = cms.string(''),
    MeasurementTrackerEvent = cms.InputTag('MeasurementTrackerEvent'),
    Propagator = cms.string("RungeKuttaTrackerPropagator"),
    runBBestimation = cms.bool(False),
    skimOutput = cms.bool(False),
    ## no need to version it!
    signalHltPaths = cms.vstring(
        'HLT_TrkMu16_DoubleTrkMu6NoFiltersNoVtx',
    ),
)
