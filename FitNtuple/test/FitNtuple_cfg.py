import FWCore.ParameterSet.Config as cms
import os

PROCESS = str(os.getenv("PROCESS"))
if ( PROCESS == None or PROCESS == "" ): PROCESS = int(0)
else : PROCESS = int(PROCESS)
JOBS = 100

realData = True

process = cms.Process("FITNTUPLE")
process.load("MuJetAnalysis.FileLists.DoubleMu_Run2012_PATv3_FileList_cff")
lenFileNames = len(process.source.fileNames)

process.source.fileNames = process.source.fileNames[lenFileNames*PROCESS/JOBS:lenFileNames*(PROCESS+1)/JOBS]

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

process.MessageLogger = cms.Service("MessageLogger", destinations = cms.untracked.vstring("cout"), cout = cms.untracked.PSet(threshold = cms.untracked.string("ERROR")))
process.load("Configuration/StandardSequences/FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = "FT_53_V6_AN3::All"

process.load("RecoVertex.PrimaryVertexProducer.OfflinePrimaryVertices_cfi")
process.OneGoodVertexFilter = cms.EDFilter("VertexSelector",
                                           src = cms.InputTag("offlinePrimaryVertices"),
                                           cut = cms.string("!isFake && tracksSize > 3 && abs(z) <= 24"),
                                           filter = cms.bool(True),
                                           )

process.load("MuJetAnalysis.LeptonJetProducer.LeptonJetProducer_cff")

process.MuJetProducerTrackerMuons = process.MuJetProducer.clone()
process.MuJetProducerTrackerMuons.muons = cms.InputTag("cleanPatTrackerMuonsTriggerMatch")
process.MuJetProducerTrackerMuons.maxMass = cms.double(5.)
process.MuJetProducerTrackerMuons.selectTrackerMuons = cms.bool(True)
process.MuJetProducerTrackerMuons.selectGlobalMuons = cms.bool(False)
process.MuJetProducerTrackerMuons.minTrackerHits = cms.int32(8)
process.MuJetProducerTrackerMuons.maxTrackerNormChi2 = cms.double(4.0)
process.MuJetProducerTrackerMuons.minSegmentMatches = cms.int32(2)
process.MuJetProducerTrackerMuons.groupingMode = cms.string("GroupByMassAndVertexProbOrDeltaR")
process.MuJetProducerTrackerMuons.maxMass = cms.double(5.)
process.MuJetProducerTrackerMuons.minVertexProb = cms.double(0.01)
process.MuJetProducerTrackerMuons.maxDeltaR = cms.double(0.02)

process.MuJetProducerPFMuons = process.MuJetProducer.clone()
process.MuJetProducerPFMuons.muons = cms.InputTag("cleanPatPFMuonsTriggerMatch")
process.MuJetProducerPFMuons.maxMass = cms.double(5.)
process.MuJetProducerPFMuons.selectTrackerMuons = cms.bool(False)
process.MuJetProducerPFMuons.selectGlobalMuons = cms.bool(False)
process.MuJetProducerPFMuons.minTrackerHits = cms.int32(-1)
process.MuJetProducerPFMuons.maxTrackerNormChi2 = cms.double(-1.)
process.MuJetProducerPFMuons.minSegmentMatches = cms.int32(-1)
process.MuJetProducerPFMuons.groupingMode = cms.string("GroupByMassAndVertexProbOrDeltaR")
process.MuJetProducerPFMuons.maxMass = cms.double(5.)
process.MuJetProducerPFMuons.minVertexProb = cms.double(0.01)
process.MuJetProducerPFMuons.maxDeltaR = cms.double(0.02)

process.FitNtupleTrackerMuons = cms.EDAnalyzer("FitNtuple",
                                     fillGenLevel = cms.bool(not realData),
                                     muons = cms.InputTag("cleanPatTrackerMuons"),
                                     muonsTriggerMatch = cms.InputTag("cleanPatTrackerMuonsTriggerMatch"),
                                     muJets = cms.InputTag("MuJetProducerTrackerMuons"),
                                     muJetOrphans = cms.InputTag("MuJetProducerTrackerMuons", "Orphans"),
                                     muJetPlusTracks = cms.InputTag("MuJetPlusTracks15"),
				                             trigpt = cms.double(17),
																		 dataset = cms.string("DoubleMu")
                                     )

process.FitNtuplePFMuons = cms.EDAnalyzer("FitNtuple",
                                     fillGenLevel = cms.bool(not realData),
                                     muons = cms.InputTag("cleanPatPFMuons"),
                                     muonsTriggerMatch = cms.InputTag("cleanPatPFMuonsTriggerMatch"),
                                     muJets = cms.InputTag("MuJetProducerPFMuons"),
                                     muJetOrphans = cms.InputTag("MuJetProducerPFMuons", "Orphans"),
                                     muJetPlusTracks = cms.InputTag("MuJetPlusTracks15"),
				                             trigpt = cms.double(17),
																		 dataset = cms.string("DoubleMu")
                                     )

process.Path = cms.Path(process.OneGoodVertexFilter * process.MuJetProducerTrackerMuons * process.MuJetProducerPFMuons * process.FitNtupleTrackerMuons * process.FitNtuplePFMuons)

process.TFileService = cms.Service("TFileService", fileName = cms.string("FitNtuple_%03d.root" % PROCESS ) )
