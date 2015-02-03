## Customization for HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx_v1

import FWCore.ParameterSet.Config as cms

hltPreTrkMu15DoubleTrkMu5NoFiltersNoVtx = cms.EDFilter( "HLTPrescaler",
    L1GtReadoutRecordTag = cms.InputTag( "hltGtDigis" ),
    offset = cms.uint32( 0 )
)

hltL2pfL1sDoubleMu103p5L1f0L2PreFiltered0NoVtx = cms.EDFilter("HLTMuonL2PreFilter",
    saveTags = cms.bool( True ),
    MaxDr = cms.double( 9999.0 ),
    CutOnChambers = cms.bool( False ),
    PreviousCandTag = cms.InputTag( "hltL1fL1sDoubleMu103p5ORDoubleMu125L1Filtered0" ),
    MinPt = cms.double( 0.0 ),
    MinN = cms.int32( 2 ),
    SeedMapTag = cms.InputTag( "hltL2Muons" ),
    MaxEta = cms.double( 2.5 ),
    MinNhits = cms.vint32( 0 ),
    MinDxySig = cms.double( -1.0 ),
    MinNchambers = cms.vint32( 0 ),
    AbsEtaBins = cms.vdouble( 5.0 ),
    MaxDz = cms.double( 9999.0 ),
    CandTag = cms.InputTag( "hltL2MuonCandidatesNoVtx" ),
    BeamSpotTag = cms.InputTag( "hltOnlineBeamSpot" ),
    MinDr = cms.double( -1.0 ),
    NSigmaPt = cms.double( 0.0 ),
    MinNstations = cms.vint32( 0 )
)

hltL2fL1sDoubleMu103p5L1f0L2Filtered10OneMuNoVtx = cms.EDFilter("HLTMuonL2PreFilter",
    saveTags = cms.bool( True ),
    MaxDr = cms.double( 9999.0 ),
    CutOnChambers = cms.bool( False ),
    PreviousCandTag = cms.InputTag( "hltL1fL1sDoubleMu103p5ORDoubleMu125L1Filtered0" ),
    MinPt = cms.double( 10.0 ),
    MinN = cms.int32( 1 ),
    SeedMapTag = cms.InputTag( "hltL2Muons" ),
    MaxEta = cms.double( 2.5 ),
    MinNhits = cms.vint32( 0 ),
    MinDxySig = cms.double( -1.0 ),
    MinNchambers = cms.vint32( 0 ),
    AbsEtaBins = cms.vdouble( 5.0 ),
    MaxDz = cms.double( 9999.0 ),
    CandTag = cms.InputTag( "hltL2MuonCandidatesNoVtx" ),
    BeamSpotTag = cms.InputTag( "hltOnlineBeamSpot" ),
    MinDr = cms.double( -1.0 ),
    NSigmaPt = cms.double( 0.0 ),
    MinNstations = cms.vint32( 0 )
)

hltL3pfL1sDoubleMu103p5L1f0L2pf0TwoMuL3PreFiltered5NoVtx = cms.EDFilter("HLTMuonL3PreFilter",
    MaxNormalizedChi2 = cms.double( 9999.0 ),
    saveTags = cms.bool( True ),
    PreviousCandTag = cms.InputTag( "hltL2pfL1sDoubleMu103p5L1f0L2PreFiltered0NoVtx" ),
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
    CandTag = cms.InputTag( "hltL3NoFiltersNoVtxMuonCandidates" ),
    MinDXYBeamSpot = cms.double( -1.0 ),
    MinDr = cms.double( -1.0 ),
    BeamSpotTag = cms.InputTag( "hltOnlineBeamSpot" ),
    MinPt = cms.double( 5.0 )
)

hltL3fL1sDoubleMu103p5L1f0L2f10OneMuL3Filtered15NoVtx = cms.EDFilter("HLTMuonL3PreFilter",
    MaxNormalizedChi2 = cms.double( 9999.0 ),
    saveTags = cms.bool( True ),
    PreviousCandTag = cms.InputTag( "hltL2fL1sDoubleMu103p5L1f0L2Filtered10OneMuNoVtx" ),
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
    CandTag = cms.InputTag( "hltL3NoFiltersNoVtxMuonCandidates" ),
    MinDXYBeamSpot = cms.double( -1.0 ),
    MinDr = cms.double( -1.0 ),
    BeamSpotTag = cms.InputTag( "hltOnlineBeamSpot" ),
    MinPt = cms.double( 15.0 )
)

hltTripleTrkMuFiltered5NoVtx = cms.EDFilter("HLTMuonTrkFilter",
    maxNormalizedChi2 = cms.double( 1.0E99 ),
    saveTags = cms.bool( False ),
    maxAbsEta = cms.double( 2.5 ),
    previousCandTag = cms.InputTag( "" ),
    minPt = cms.double( 5.0 ),
    minN = cms.uint32( 3 ),
    inputCandCollection = cms.InputTag( "hltGlbTrkMuonCandsNoVtx" ),
    minMuonStations = cms.int32( 2 ),
    trkMuonId = cms.uint32( 0 ),
    requiredTypeMask = cms.uint32( 0 ),
    minMuonHits = cms.int32( -1 ),
    minTrkHits = cms.int32( -1 ),
    inputMuonCollection = cms.InputTag( "hltGlbTrkMuonsNoVtx" ),
    allowedTypeMask = cms.uint32( 255 )
)

hltSingleTrkMuFiltered15NoVtx = cms.EDFilter("HLTMuonTrkFilter",
    maxNormalizedChi2 = cms.double( 1.0E99 ),
    saveTags = cms.bool( False ),
    maxAbsEta = cms.double( 2.5 ),
    previousCandTag = cms.InputTag( "" ),
    minPt = cms.double( 15.0 ),
    minN = cms.uint32( 1 ),
    inputCandCollection = cms.InputTag( "hltGlbTrkMuonCandsNoVtx" ),
    minMuonStations = cms.int32( 2 ),
    trkMuonId = cms.uint32( 0 ),
    requiredTypeMask = cms.uint32( 0 ),
    minMuonHits = cms.int32( -1 ),
    minTrkHits = cms.int32( -1 ),
    inputMuonCollection = cms.InputTag( "hltGlbTrkMuonsNoVtx" ),
    allowedTypeMask = cms.uint32( 255 )
)

def add_HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx_v1(process):

    process.hltPreTrkMu15DoubleTrkMu5NoFiltersNoVtx = hltPreTrkMu15DoubleTrkMu5NoFiltersNoVtx
    process.hltL2pfL1sDoubleMu103p5L1f0L2PreFiltered0NoVtx = hltL2pfL1sDoubleMu103p5L1f0L2PreFiltered0NoVtx
    process.hltL2fL1sDoubleMu103p5L1f0L2Filtered10OneMuNoVtx = hltL2fL1sDoubleMu103p5L1f0L2Filtered10OneMuNoVtx
    process.hltL3pfL1sDoubleMu103p5L1f0L2pf0TwoMuL3PreFiltered5NoVtx = hltL3pfL1sDoubleMu103p5L1f0L2pf0TwoMuL3PreFiltered5NoVtx
    process.hltL3fL1sDoubleMu103p5L1f0L2f10OneMuL3Filtered15NoVtx = hltL3fL1sDoubleMu103p5L1f0L2f10OneMuL3Filtered15NoVtx
    process.hltTripleTrkMuFiltered5NoVtx = hltTripleTrkMuFiltered5NoVtx 
    process.hltSingleTrkMuFiltered15NoVtx = hltSingleTrkMuFiltered15NoVtx

    process.hltDiMuonMergingNoVtx = process.hltDiMuonMerging.clone(
        selectedTrackQuals = cms.VInputTag( 'hltL3NoFiltersTkTracksFromL2Novtx','hltMuCtfTracks' ),
        TrackProducers = cms.VInputTag( 'hltL3NoFiltersTkTracksFromL2Novtx','hltMuCtfTracks' ),
    )
    process.hltDiMuonLinksNoVtx = process.hltDiMuonLinks.clone(
        InclusiveTrackerTrackCollection = cms.InputTag( "hltDiMuonMergingNoVtx" ),
        LinkCollection = cms.InputTag( "hltL3NoFiltersNoVtxMuonsLinksCombination" ),
    )
    process.hltGlbTrkMuonsNoVtx = process.hltGlbTrkMuons.clone(
        inputCollectionLabels = cms.VInputTag( 'hltDiMuonMergingNoVtx','hltDiMuonLinksNoVtx' ),
    )
    process.hltGlbTrkMuonCandsNoVtx = process.hltGlbTrkMuonCands.clone(
        InputObjects = cms.InputTag( "hltGlbTrkMuonsNoVtx" )
    )

    process.HLTTrackerMuonSequenceNoVtx = cms.Sequence( 
        process.HLTDoLocalPixelSequence + 
        process.hltPixelLayerTriplets + 
        process.hltPixelTracks + 
        process.HLTDoLocalStripSequence + 
        process.hltMuTrackSeeds + 
        process.hltMuCkfTrackCandidates + 
        process.hltMuCtfTracks + 
        process.HLTL3NoFiltersNoVtxmuonrecoNocandSequence + 
        process.hltDiMuonMergingNoVtx + 
        process.hltDiMuonLinksNoVtx + 
        process.hltGlbTrkMuonsNoVtx + 
        process.hltGlbTrkMuonCandsNoVtx 
    )
    
    process.HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx_v1 = cms.Path( 
        process.HLTBeginSequence + 
        process.hltL1sL1DoubleMu103p5ORDoubleMu125 + 
        process.hltPreTrkMu15DoubleTrkMu5NoFiltersNoVtx + 
        process.hltL1fL1sDoubleMu103p5ORDoubleMu125L1Filtered0 + 
        process.HLTL2muonrecoSequenceNoVtx +  
        process.hltL2pfL1sDoubleMu103p5L1f0L2PreFiltered0NoVtx + 
        process.hltL2fL1sDoubleMu103p5L1f0L2Filtered10OneMuNoVtx +
        process.HLTL3NoFiltersNoVtxmuonrecoSequence +
        process.hltL3pfL1sDoubleMu103p5L1f0L2pf0TwoMuL3PreFiltered5NoVtx + 
        process.hltL3fL1sDoubleMu103p5L1f0L2f10OneMuL3Filtered15NoVtx +
        process.HLTTrackerMuonSequenceNoVtx + 
        process.hltTripleTrkMuFiltered5NoVtx + 
        process.hltSingleTrkMuFiltered15NoVtx + 
        process.HLTEndSequence
    )

    return process
