import FWCore.ParameterSet.Config as cms

cutFlowAnalyzer = cms.EDAnalyzer('CutFlowAnalyzer_MiniAOD',
    analyzerDebug = cms.int32(-1),
    muons = cms.InputTag("cleanPatPFMuonsTriggerMatch"),
    beamSpot = cms.InputTag("offlineBeamSpot"),
    muJets = cms.InputTag("PFMuJetProducer05"),
    muJetOrphans = cms.InputTag("PFMuJetProducer05", "Orphans"),
    tracks = cms.InputTag("unpackedTracksAndVertices"),
    TriggerResults = cms.InputTag("TriggerResults","","HLT"),
    # Access L1 decision: Method 1 input
    #L1Results = cms.InputTag("gtDigis"),
    #useFinalDecision = cms.bool(False),
    # Access L1 decision: Method 2 input
    hltProcess=cms.string("HLT"),
    TrackRefitter = cms.InputTag("TrackRefitter"),
    PrunedGenParticles = cms.InputTag("prunedGenParticles"),
    primaryVertices = cms.InputTag("unpackedTracksAndVertices"),
    PATJet = cms.InputTag("slimmedJets"),
    DiMuons_Iso_Max = cms.double(2.0),
    nThrowsConsistentVertexesCalculator = cms.int32(0),
    barrelPixelLayer = cms.int32(1),
    endcapPixelLayer = cms.int32(1),
    runDisplacedVtxFinder = cms.bool(False),
    Traj = cms.InputTag("TrackRefitter"),
    NavigationSchool   = cms.string('SimpleNavigationSchool'),
    MeasurementTracker = cms.string(''),
    MeasurementTrackerEvent = cms.InputTag('MeasurementTrackerEvent'),
    Propagator = cms.string("RungeKuttaTrackerPropagator"),
    runBBestimation = cms.bool(True),
    skimOutput = cms.bool(False),
    ## no need to version it!
    signalHltPaths = cms.vstring(
    'HLT_TrkMu16_DoubleTrkMu6NoFiltersNoVtx',
    ),
    controlHltPaths = cms.vstring(
    'HLT_TrkMu16NoFiltersNoVtx',
    'HLT_TrkMu6NoFiltersNoVtx',
    ),
    #L1 algos for signal HLT (FIN-OR)
    l1algos = cms.vstring(
    "L1_DoubleMu_12_5",
    "L1_DoubleMu_15_5_SQ",
    "L1_DoubleMu_15_7" ,
    "L1_TripleMu_5_3_3"),
)
