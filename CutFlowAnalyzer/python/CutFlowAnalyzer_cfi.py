import FWCore.ParameterSet.Config as cms

cutFlowAnalyzer = cms.EDAnalyzer('CutFlowAnalyzer',
    analyzerDebug = cms.int32(0),
    fillGenLevel = cms.bool(True),
#    muons = cms.InputTag("cleanPatTrackerMuonsTriggerMatch"),
#    muJets = cms.InputTag("TrackerMuJetProducer05"),
    muons = cms.InputTag("cleanPatPFMuonsTriggerMatch"),
    muJets = cms.InputTag("PFMuJetProducer05GroupByDeltaROrMass"),
    muJetOrphans = cms.InputTag("PFMuJetProducer05GroupByDeltaROrMass", "Orphans"),
    DiMuons_Iso_Max = cms.double(2.0),
    nThrowsConsistentVertexesCalculator = cms.int32(100000),
    runDisplacedVtxFinder = cms.bool(False),
    runPixelHitRecovery = cms.bool(False),
    trajectoryInput = cms.string("TrackRefitter"),
    NavigationSchool   = cms.string('SimpleNavigationSchool'),
    MeasurementTracker = cms.string(''),
    MeasurementTrackerEvent = cms.InputTag('MeasurementTrackerEvent'),
    Propagator = cms.string("RungeKuttaTrackerPropagator"),
    hltPaths = cms.vstring(
        'HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx_v1',
        'HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx_v2',
    )
)
