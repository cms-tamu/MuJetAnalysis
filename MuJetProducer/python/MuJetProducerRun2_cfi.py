import FWCore.ParameterSet.Config as cms

MuJetProducer = cms.EDProducer(
    "MuJetProducerRun2",

    # source of pat::Muons with user-specified quality cuts
    #muons = cms.InputTag("cleanPatPFMuonsTriggerMatch"),
    #StandAlone muons might be embedded in the pat::Muon
    muons = cms.InputTag("slimmedMuons"),
    #DSA collection
    #DSAmuons = cms.InputTag("displacedStandAloneMuons"),#Available in Re-MiniAOD under 10_2_X
    beamSpot = cms.InputTag("offlineBeamSpot"),
    minPt = cms.double(8.),#this needs to match CutFlowAnalyzer_MiniAOD.cc: LowPt threshold
    maxAbsEta = cms.double(2.4),
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
    #calculateIsolation = cms.bool(False),
    # how to group muons into jets
    groupingMode = cms.string("GroupByMassAndVertexProbOrDeltaR"),
    maxDeltaR = cms.double(0.01),
    maxMass = cms.double(60.),
    minVertexProb = cms.double(-1),
    groupByCharge = cms.string("opposite"),
    # fiducial region
    barrelPixelLayer = cms.int32(1),
    endcapPixelLayer = cms.int32(1),
    )
