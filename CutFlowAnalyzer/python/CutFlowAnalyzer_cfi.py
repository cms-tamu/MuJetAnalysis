import FWCore.ParameterSet.Config as cms

cutFlowAnalyzer = cms.EDAnalyzer('CutFlowAnalyzer',
    analyzerDebug = cms.int32(0),
    fillGenLevel = cms.bool(True),
#    muons = cms.InputTag("cleanPatTrackerMuonsTriggerMatch"),
#    muJets = cms.InputTag("TrackerMuJetProducer05"),
    muons = cms.InputTag("cleanPatPFMuonsTriggerMatch"),
    muJets = cms.InputTag("PFMuJetProducer05"),
    GenA_Lxy_Max =  cms.double(4.0), ## distance to beam [cm]
    DiMuons_dz_Max = cms.double(0.1), ## Track displacement [cm]
    DiMuons_Iso_Max = cms.double(2.0), ## Isolation [Gev]
    DiMuons_Iso_dR_Max = cms.double(0.4), ## Isolation cone
    DiMuons_Iso_dz_Max = cms.double(0.1), ## Track displacement [cm]
    DiMuons_Iso_pT_Min = cms.double(0.5), ## Track pT [GeV]
    nThrowsConsistentVertexesCalculator = cms.int32(100000),
    hltPaths = cms.vstring(
        'HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx_v1',
        'HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx_v2',
    )
)
