import FWCore.ParameterSet.Config as cms

def customizePatOutput(process):
    process.out.outputCommands = cms.untracked.vstring(
        "drop *",
        "keep *_patMuons_*_*",
        "keep *_patJets_*_*",
        "keep *_cleanPatTrackerMuons_*_*",
        "keep *_cleanPatPFMuons_*_*",
        "keep *_patTrigger_*_*",
        "keep *_patTriggerEvent_*_*",
        "keep *_muonTriggerMatch*_*_*",
        "keep *_cleanPatTrackerMuonsTriggerMatch_*_*",
        "keep *_cleanPatPFMuonsTriggerMatch_*_*",

        "keep *_PFMuJetProducer05_*_*",
        "keep *_TrackerMuJetProducer05_*_*",
        "keep *_PFMuJetProducer05PXBL2PXFL2_*_*",
        "keep *_TrackerMuJetProducer05PXBL2PXFL2_*_*",
        "keep *_PFMuJetProducer05PXBL3PXFL2_*_*",
        "keep *_TrackerMuJetProducer05PXBL3PXFL2_*_*",

        "keep *_muons_*_*",
        "keep recoTracks_generalTracks_*_*",
        "keep recoTrackExtras_generalTracks_*_*",
        "keep *_standAloneMuons_*_*",
        "keep *_globalMuons_*_*",

        "keep *_genParticles_*_*",
        "keep *_generator_*_*",
        "drop edmHepMCProduct_generator_*_*",

        "keep *_cscSegments_*_*",
        "keep *_dt4DSegments_*_*",

        "keep *_TriggerResults_*_TEST",
        "keep L1AcceptBunchCrossings_*_*_*",
        "keep L1GlobalTriggerReadoutRecord_gtDigis_*_*",
        
        'keep recoPFCandidates_particleFlow_*_*',

        "keep *_offlineBeamSpot_*_*",
        "keep *_offlinePrimaryVertices_*_*",
        "keep *_offlinePrimaryVerticesWithBS_*_*",

        "keep *_genMetCalo_*_*",
        "keep *_genMetCaloAndNonPrompt_*_*",
        "keep *_genMetTrue_*_*",
        "keep *_met_*_*",
        "keep *_metHO_*_*",
        "keep *_metNoHF_*_*",
        "keep *_metNoHFHO_*_*",
        "keep *_metOpt_*_*",
        "keep *_metOptHO_*_*",
        "keep *_metOptNoHF_*_*",
        "keep *_metOptNoHFHO_*_*",
        "keep *_tcMet_*_*",
        "keep *_pfMet_*_*",

        "keep *_ak5GenJets_*_*",
        "keep *_ak5CaloJets_*_*",
        "keep *_ak5PFJets_*_*",
        "keep *_ak5TrackJets_*_*",
        "keep *_ak7GenJets_*_*",
        "keep *_ak7CaloJets_*_*",
        "keep *_ak7PFJets_*_*",
        "keep *_ak7TrackJets_*_*",
    )
    process.out.fileName = cms.untracked.string("out_pat.root")
    return process
