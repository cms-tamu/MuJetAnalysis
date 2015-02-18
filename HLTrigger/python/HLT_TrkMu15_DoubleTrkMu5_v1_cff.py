import FWCore.ParameterSet.Config as cms

hltPreTrkMu15DoubleTrkMu5 = cms.EDFilter( "HLTPrescaler",
    L1GtReadoutRecordTag = cms.InputTag( "hltGtDigis" ),
    offset = cms.uint32( 0 )
)

hltL3pfL1sDoubleMu103p5L1f0L2pf0TwoMuL3PreFiltered5 = cms.EDFilter( "HLTMuonL3PreFilter",
    MaxNormalizedChi2 = cms.double( 9999.0 ),
    saveTags = cms.bool( True ),
    PreviousCandTag = cms.InputTag( "hltL2pfL1sDoubleMu103p5L1f0L2PreFiltered0" ),
    MinNmuonHits = cms.int32( 0 ),
    MinN = cms.int32( 2 ),
    MinTrackPt = cms.double( 0.0 ),
    MaxEta = cms.double( 2.5 ),
    MaxDXYBeamSpot = cms.double( 9999.0 ),
    MinNhits = cms.int32( 0 ),
    MinDxySig = cms.double( -1.0 ),
    NSigmaPt = cms.double( 0.0 ),
    MaxDz = cms.double( 9999.0 ),
    MaxPtDifference = cms.double( 9999.0 ),
    MaxDr = cms.double( 2.0 ),
    CandTag = cms.InputTag( "hltL3MuonCandidates" ),
    MinDXYBeamSpot = cms.double( -1.0 ),
    MinDr = cms.double( -1.0 ),
    BeamSpotTag = cms.InputTag( "hltOnlineBeamSpot" ),
    MinPt = cms.double( 5.0 )
)

hltL3fL1sDoubleMu103p5L1f0L2f10OneMuL3Filtered15 = cms.EDFilter( "HLTMuonL3PreFilter",
    MaxNormalizedChi2 = cms.double( 9999.0 ),
    saveTags = cms.bool( True ),
    PreviousCandTag = cms.InputTag( "hltL2fL1sDoubleMu103p5L1f0L2Filtered10OneMu" ),
    MinNmuonHits = cms.int32( 0 ),
    MinN = cms.int32( 1 ),
    MinTrackPt = cms.double( 0.0 ),
    MaxEta = cms.double( 2.5 ),
    MaxDXYBeamSpot = cms.double( 9999.0 ),
    MinNhits = cms.int32( 0 ),
    MinDxySig = cms.double( -1.0 ),
    NSigmaPt = cms.double( 0.0 ),
    MaxDz = cms.double( 9999.0 ),
    MaxPtDifference = cms.double( 9999.0 ),
    MaxDr = cms.double( 2.0 ),
    CandTag = cms.InputTag( "hltL3MuonCandidates" ),
    MinDXYBeamSpot = cms.double( -1.0 ),
    MinDr = cms.double( -1.0 ),
    BeamSpotTag = cms.InputTag( "hltOnlineBeamSpot" ),
    MinPt = cms.double( 15.0 )
)

hltTripleTrkMuFiltered5 = cms.EDFilter("HLTMuonTrkFilter",
    maxNormalizedChi2 = cms.double( 1.0E99 ),
    saveTags = cms.bool( False ),
    maxAbsEta = cms.double( 2.5 ),
    previousCandTag = cms.InputTag( "" ),
    minPt = cms.double( 5.0 ),
    minN = cms.uint32( 3 ),
    inputCandCollection = cms.InputTag( "hltGlbTrkMuonCands" ),
    minMuonStations = cms.int32( 2 ),
    trkMuonId = cms.uint32( 0 ),
    requiredTypeMask = cms.uint32( 0 ),
    minMuonHits = cms.int32( -1 ),
    minTrkHits = cms.int32( -1 ),
    inputMuonCollection = cms.InputTag( "hltGlbTrkMuons" ),
    allowedTypeMask = cms.uint32( 255 )
)

hltSingleTrkMuFiltered15 = cms.EDFilter("HLTMuonTrkFilter",
    maxNormalizedChi2 = cms.double( 1.0E99 ),
    saveTags = cms.bool( False ),
    maxAbsEta = cms.double( 2.5 ),
    previousCandTag = cms.InputTag( "" ),
    minPt = cms.double( 15.0 ),
    minN = cms.uint32( 1 ),
    inputCandCollection = cms.InputTag( "hltGlbTrkMuonCands" ),
    minMuonStations = cms.int32( 2 ),
    trkMuonId = cms.uint32( 0 ),
    requiredTypeMask = cms.uint32( 0 ),
    minMuonHits = cms.int32( -1 ),
    minTrkHits = cms.int32( -1 ),
    inputMuonCollection = cms.InputTag( "hltGlbTrkMuons" ),
    allowedTypeMask = cms.uint32( 255 )
)

def addHLT_TrkMu15_DoubleTrkMu5_v1(process):
    
    process.hltPreTrkMu15DoubleTrkMu5 = hltPreTrkMu15DoubleTrkMu5
    process.hltL3pfL1sDoubleMu103p5L1f0L2pf0TwoMuL3PreFiltered5 = hltL3pfL1sDoubleMu103p5L1f0L2pf0TwoMuL3PreFiltered5
    process.hltL3fL1sDoubleMu103p5L1f0L2f10OneMuL3Filtered15 = hltL3fL1sDoubleMu103p5L1f0L2f10OneMuL3Filtered15
    process.hltTripleTrkMuFiltered5 = hltTripleTrkMuFiltered5
    process.hltSingleTrkMuFiltered15 = hltSingleTrkMuFiltered15

    process.HLT_TrkMu15_DoubleTrkMu5_v1 = cms.Path( 
        process.HLTBeginSequence + 
        process.hltL1sL1DoubleMu103p5ORDoubleMu125 + 
        process.hltPreTrkMu15DoubleTrkMu5 + 
        process.hltL1fL1sDoubleMu103p5ORDoubleMu125L1Filtered0 + 
        process.HLTL2muonrecoSequence + 
        process.hltL2pfL1sDoubleMu103p5L1f0L2PreFiltered0 + 
        process.hltL2fL1sDoubleMu103p5L1f0L2Filtered10OneMu + 
        process.HLTL3muonrecoSequence + 
        process.hltL3pfL1sDoubleMu103p5L1f0L2pf0TwoMuL3PreFiltered5 + 
        process.hltL3fL1sDoubleMu103p5L1f0L2f10OneMuL3Filtered15 + 
        process.HLTTrackerMuonSequence +
        process.hltTripleTrkMuFiltered5 +
        process.hltSingleTrkMuFiltered15 +
        process.HLTEndSequence 
    )
    return process
