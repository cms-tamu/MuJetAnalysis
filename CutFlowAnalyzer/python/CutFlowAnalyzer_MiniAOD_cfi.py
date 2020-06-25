import FWCore.ParameterSet.Config as cms

cutFlowAnalyzer = cms.EDAnalyzer('CutFlowAnalyzer_MiniAOD',
    analyzerDebug = cms.int32(-1),
    #muons = cms.InputTag("cleanPatPFMuonsTriggerMatch"),
    muons = cms.InputTag("slimmedMuons"),
    beamSpot = cms.InputTag("offlineBeamSpot"),
    muPairs = cms.InputTag("PFMuJetProducer05", "Pairs"),
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
    pileupCollection = cms.InputTag("slimmedAddPileupInfo"),
    primaryVertices = cms.InputTag("unpackedTracksAndVertices"),
    secondaryVertices = cms.InputTag("unpackedTracksAndVertices","secondary"),
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
    skimOutput = cms.bool(False),
    signalHltPaths = cms.vstring(
    'HLT_TrkMu16_DoubleTrkMu6NoFiltersNoVtx',
    #'HLT_TrkMu12_DoubleTrkMu5NoFiltersNoVtx',
    #'HLT_Mu18_Mu9_SameSign',
    #'HLT_DoubleL2Mu23NoVtx_2Cha_CosmicSeed',
    #'HLT_DoubleL2Mu23NoVtx_2Cha',
    #'HLT_TripleMu_12_10_5',
    #'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8',
    #'HLT_IsoMu24',
    ),
    controlHltPaths = cms.vstring(
    'HLT_TrkMu16NoFiltersNoVtx',
    'HLT_TrkMu6NoFiltersNoVtx',
    ),
    #L1 algos for signal HLT (FIN-OR)
    l1algos = cms.vstring(
    #Seeds for TripleTrkMu HLT_TrkMu16_DoubleTrkMu6NoFiltersNoVtx
    "L1_DoubleMu_12_5",
    "L1_DoubleMu_15_5_SQ",
    "L1_DoubleMu_15_7" ,
    "L1_TripleMu_5_3_3",
    #Seeds for TripleMu HLT 10_5_5/12_10_5
    #"L1_TripleMu0",
    #"L1_TripleMu_5_5_3",
    #"L1_TripleMu_5_3_3",
    #"L1_TripleMu3_SQ",
    #Seeds for SingleMu HLT_Mu8
    #"L1_SingleMu3",
    #"L1_SingleMu5",
    #"L1_SingleMu7",
    #Seeds for SingleMu HLT_Mu17
    #"L1_SingleMu15_DQ",
    ),
)
