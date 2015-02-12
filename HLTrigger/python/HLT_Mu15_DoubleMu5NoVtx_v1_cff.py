import FWCore.ParameterSet.Config as cms

hltPreMu15DoubleMu5NoFiltersNoVtx = cms.EDFilter( "HLTPrescaler",
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

hltL3pfL1sDoubleMu103p5L1f0L2pf0ThreeMuL3PreFiltered5NoVtx = cms.EDFilter("HLTMuonL3PreFilter",
    MaxNormalizedChi2 = cms.double( 9999.0 ),
    saveTags = cms.bool( True ),
    PreviousCandTag = cms.InputTag( "hltL2pfL1sDoubleMu103p5L1f0L2PreFiltered0NoVtx" ),
    MinNmuonHits = cms.int32( 0 ),
    MinN = cms.int32( 3 ),
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

def addHLT_Mu15_DoubleMu5NoVtx_v1(process):

    process.hltPreMu15DoubleMu5NoFiltersNoVtx = hltPreMu15DoubleMu5NoFiltersNoVtx
    process.hltL2pfL1sDoubleMu103p5L1f0L2PreFiltered0NoVtx = hltL2pfL1sDoubleMu103p5L1f0L2PreFiltered0NoVtx
    process.hltL2fL1sDoubleMu103p5L1f0L2Filtered10OneMuNoVtx = hltL2fL1sDoubleMu103p5L1f0L2Filtered10OneMuNoVtx
    process.hltL3pfL1sDoubleMu103p5L1f0L2pf0ThreeMuL3PreFiltered5NoVtx = hltL3pfL1sDoubleMu103p5L1f0L2pf0ThreeMuL3PreFiltered5NoVtx
    process.hltL3fL1sDoubleMu103p5L1f0L2f10OneMuL3Filtered15NoVtx = hltL3fL1sDoubleMu103p5L1f0L2f10OneMuL3Filtered15NoVtx
                                                                     
    process.HLT_Mu15_DoubleMu5NoVtx_v1 = cms.Path( 
        process.HLTBeginSequence + 
        process.hltL1sL1DoubleMu103p5ORDoubleMu125 + 
        process.hltPreMu15DoubleMu5NoFiltersNoVtx + 
        process.hltL1fL1sDoubleMu103p5ORDoubleMu125L1Filtered0 + 
        process.HLTL2muonrecoSequenceNoVtx + 
        process.hltL2pfL1sDoubleMu103p5L1f0L2PreFiltered0NoVtx +
        process.hltL2fL1sDoubleMu103p5L1f0L2Filtered10OneMuNoVtx +
        process.HLTL3NoFiltersNoVtxmuonrecoSequence +
        process.hltL3pfL1sDoubleMu103p5L1f0L2pf0ThreeMuL3PreFiltered5NoVtx +
        process.hltL3fL1sDoubleMu103p5L1f0L2f10OneMuL3Filtered15NoVtx +
        process.HLTEndSequence 
   )
    return process
