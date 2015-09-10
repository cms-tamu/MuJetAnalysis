import FWCore.ParameterSet.Config as cms
import sys
import os

process = cms.Process("ANA")


################## PAT Input #############################

process.source = cms.Source("PoolSource",
              fileNames = cms.untracked.vstring('file:out_pat.root'),
              secondaryFileNames = cms.untracked.vstring()
)

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))


############## Analysis Modules ###################################


process.load("MuJetAnalysis.MuJetProducer.MuJetProducer_cfi")


process.PFMuJetProducer05 = process.MuJetProducer.clone(
    maxMass = cms.double(5.),
    minPt = cms.double(8.0),
    maxAbsEta = cms.double(2.4),
    muons = cms.InputTag("cleanPatPFMuonsTriggerMatch"),
#    selectTrackerMuons = cms.bool(True),
#    selectGlobalMuons = cms.bool(True),
    groupingMode = cms.string("GroupByMassAndVertexProbOrDeltaR"),
    maxDeltaR = cms.double(0.01),
    #  minSegmentMatches = cms.int32(2),
    minSegmentMatches = cms.int32(-1),
    minTrackerHits = cms.int32(-1),
    maxTrackerNormChi2 = cms.double(-1.0)
)


# process.cutFlowAnalyzer = cms.EDAnalyzer('CutFlowAnalyzer',
#         analyzerDebug = cms.int32(0),
#         fillGenLevel = cms.bool(True),
# #       muons = cms.InputTag("cleanPatTrackerMuonsTriggerMatch"),
# #       muJets = cms.InputTag("TrackerMuJetProducer05"),
#         muons = cms.InputTag("cleanPatPFMuonsTriggerMatch"),
#         muJets = cms.InputTag("PFMuJetProducer05"),
#         DiMuons_Iso_Max = cms.double(2.0),
#         nThrowsConsistentVertexesCalculator = cms.int32(100000),
#         hltPaths = cms.vstring(
#         'HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx_v1',
#   )
# )

process.ana2012 = cms.EDAnalyzer("Analysis2012",
                                 trajectoryInput = cms.string("TrackRefitter"),
                                 navigationSchool   = cms.string('SimpleNavigationSchool'),
                                 MeasurementTracker = cms.string(''),
                                 Propagator = cms.string("AnalyticalPropagator"),
                                 muJets = cms.InputTag("PFMuJetProducer05"),
                                 muons = cms.InputTag("cleanPatPFMuonsTriggerMatch"),
                                 analyzerDebug = cms.int32(100),
                                 analyzerTraj = cms.int32(0),
                                 highpT_muon_pT = cms.double(17.0),
                                 highpT_muon_eta = cms.double(0.9),
                                 muon_pT = cms.double(8.0),
                                 muon_eta = cms.double(2.4),
                                 hltPaths = cms.vstring('HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx_v1'),
                                 fillGenLevel = cms.bool(False)
                                 )


process.Path = cms.Path(process.PFMuJetProducer05 * process.ana2012)


process.TFileService = cms.Service("TFileService", fileName = cms.string("out_ana.root"))

