import FWCore.ParameterSet.Config as cms

ElectronJetProducer = cms.EDProducer(
    "ElectronJetProducer",
    
    # source of pat::Muons with user-specified quality cuts
    muons = cms.InputTag("cleanPatMuonsTriggerMatch"),
    minPt = cms.double(8.),
    minPmag = cms.double(0.),
    maxAbsEta = cms.double(2.4),
    selectTrackerMuons = cms.bool(True),
    selectGlobalMuons = cms.bool(False),
    minTrackerHits = cms.int32(8),
    maxTrackerNormChi2 = cms.double(4.),
    maxTrackerDxy = cms.double(-1.),
    maxTrackerDz = cms.double(-1.),
    maxQoverpError = cms.double(-1.),
    maxPhiError = cms.double(-1.),
    maxEtaError = cms.double(-1.),
    maxDxyError = cms.double(-1.),
    maxDzError = cms.double(-1.),
    minOuterHits = cms.int32(-1),
    maxOuterNormChi2 = cms.double(-1.),
    maxGlobalNormChi2 = cms.double(-1.),
    maxStaRelChi2 = cms.double(-1.),
    minSegmentMatches = cms.int32(2),
    muonSelectors = cms.vstring(),
    detailedSelectors = cms.VPSet(),

    # what to include in the jets
    calculateVertex = cms.bool(True),
    calculateIsolation = cms.bool(False),

    # how to group muons into jets
    groupingMode = cms.string("GroupByMassAndVertexProbOrDeltaR"),
    maxDeltaR = cms.double(0.01),
    maxMass = cms.double(5.),
    minVertexProb = cms.double(0.01),
    groupByCharge = cms.string("opposite"),
    
    # defines isolation variables for offline cuts
    tracks = cms.InputTag("generalTracks"),
    caloTowers = cms.InputTag("towerMaker"),

    # recommended parameters for isolation
    centralTrackIsolationCone = cms.double(0.4),
    centralTrackThresholdPt = cms.double(1.5),
    centralNumberAboveThresholdCone = cms.double(0.4),
    centralNumberAboveThresholdPt = cms.double(1.5),

    # union (non-circular) isolation regions are not recommended
    unionTrackIsolationCone = cms.double(0.),
    unionTrackThresholdPt = cms.double(1e6),
    unionNumberAboveThresholdCone = cms.double(0.),
    unionNumberAboveThresholdPt = cms.double(1e6),

    # calorimeter isolation is not recommended
    centralCaloIsolationCone = cms.double(0.),
    unionCaloIsolationCone = cms.double(0.),
)
