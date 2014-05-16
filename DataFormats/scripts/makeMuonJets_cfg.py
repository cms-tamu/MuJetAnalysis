import FWCore.ParameterSet.Config as cms
import os

realData = False

WHICH = int(os.getenv("PROCESS"))

if WHICH == 0: sample = "ppMuX_CMSSW382_v6"
elif WHICH in (1, 2, 3, 4): sample = "InclusiveMu5_Pt30_CMSSW382_v6"
elif WHICH in (5, 6, 7, 8): sample = "InclusiveMu5_Pt50_CMSSW382_v6"
elif WHICH in (9, 10): sample = "InclusiveMu5_Pt150_CMSSW382_v6"
elif WHICH == 11: sample = "InclusiveMu5_Pt250_CMSSW382_v6"
elif WHICH == 12: sample = "InclusiveMu5_Pt350_CMSSW382_v6"

elif WHICH in (13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26): sample = "DrellYanPythia8_CMSSW382_v6"

elif WHICH == 27: sample = "JPsiToMuMu_CMSSW382_v6"
elif WHICH == 28: sample = "Psi2SToJpsiPiPi_CMSSW382_v6"
elif WHICH == 29: sample = "Psi2SToMuMu_CMSSW382_v6"

elif WHICH in (30, 31, 32, 33, 34, 35, 36, 37, 38, 39): sample = "PairGun100_mass50_alternating_CMSSW382_v6"
elif WHICH in (40, 41): sample = "PairGun100_alternating_CMSSW382_v6"
elif WHICH in (42, 43): sample = "PairGun100_pileup_alternating_CMSSW382_v6"
elif WHICH in (44, 45): sample = "PairGun100_pileup5_alternating_CMSSW382_v6"
elif WHICH in (46, 47): sample = "PairGun100_dispvert100_alternating_CMSSW382_v6"
elif WHICH in (48, 49): sample = "PairPairGun100_pileup_alternating_CMSSW382_v6"

elif WHICH in (50, 51, 52): sample = "NMSSMHiggs_h100_a2_pileup_CMSSW382_v6"
elif WHICH in (53, 54, 55): sample = "EXTRAU1_DMAA_pileup_CMSSW382_v6"
elif WHICH in (56, 57, 58): sample = "EXTRAU1_DMMIXED_pileup_CMSSW382_v6"
elif WHICH in (59, 60, 61): sample = "EXTRAU1_electrons_pileup_CMSSW382_v6"
elif WHICH in (62, 63, 64): sample = "EXTRAU1_pions_pileup_CMSSW382_v6"

elif WHICH == 65: sample = "WZ_CMSSW382_v6"
elif WHICH == 66: sample = "ZZ_CMSSW382_v6"
elif WHICH == 67: sample = "WW_CMSSW382_v6"

elif WHICH in (68, 69, 70, 71, 72, 73, 74, 75): sample = "inclBB2mu_CMSSW384_v6"
elif WHICH in (76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87): sample = "inclBB4mu_CMSSW384_v6"

elif WHICH == 88: sample = "inclBB4mu_Pt50_CMSSW384_v6"
elif WHICH == 89: sample = "inclBB4mu_Pt150_CMSSW384_v6"
elif WHICH == 90: sample = "inclBB4mu_Pt250_CMSSW384_v6"
elif WHICH == 91: sample = "inclBB4mu_Pt350_CMSSW384_v6"

elif WHICH in (92, 93, 94, 95, 96, 97, 98, 99, 100, 101):
    sample = "DataSep17_CMSSW382_v6"
    realData = True
elif WHICH in (102, 103, 104, 105, 106, 107, 108, 109, 110, 111):
    sample = "Data2010BPromptAll_CMSSW384_v6"
    realData = True

else: raise Exception

process = cms.Process("LEPTONJETS")
process.load("AnalysisDataFormats.MuJetAnalysis.filelists.%s_cff" % sample)
lenFileNames = len(process.source.fileNames)

if WHICH == 1: process.source.fileNames = process.source.fileNames[lenFileNames*0/4:lenFileNames*1/4]
if WHICH == 2: process.source.fileNames = process.source.fileNames[lenFileNames*1/4:lenFileNames*2/4]
if WHICH == 3: process.source.fileNames = process.source.fileNames[lenFileNames*2/4:lenFileNames*3/4]
if WHICH == 4: process.source.fileNames = process.source.fileNames[lenFileNames*3/4:lenFileNames*4/4]

if WHICH == 5: process.source.fileNames = process.source.fileNames[lenFileNames*0/4:lenFileNames*1/4]
if WHICH == 6: process.source.fileNames = process.source.fileNames[lenFileNames*1/4:lenFileNames*2/4]
if WHICH == 7: process.source.fileNames = process.source.fileNames[lenFileNames*2/4:lenFileNames*3/4]
if WHICH == 8: process.source.fileNames = process.source.fileNames[lenFileNames*3/4:lenFileNames*4/4]

if WHICH == 9: process.source.fileNames = process.source.fileNames[lenFileNames*0/2:lenFileNames*1/2]
if WHICH == 10: process.source.fileNames = process.source.fileNames[lenFileNames*1/2:lenFileNames*2/2]

if WHICH == 15: process.source.fileNames = process.source.fileNames[lenFileNames*0/2:lenFileNames*1/2]
if WHICH == 16: process.source.fileNames = process.source.fileNames[lenFileNames*1/2:lenFileNames*2/2]

if WHICH == 17: process.source.fileNames = process.source.fileNames[lenFileNames*0/10:lenFileNames*1/10]
if WHICH == 18: process.source.fileNames = process.source.fileNames[lenFileNames*1/10:lenFileNames*2/10]
if WHICH == 19: process.source.fileNames = process.source.fileNames[lenFileNames*2/10:lenFileNames*3/10]
if WHICH == 20: process.source.fileNames = process.source.fileNames[lenFileNames*3/10:lenFileNames*4/10]
if WHICH == 21: process.source.fileNames = process.source.fileNames[lenFileNames*4/10:lenFileNames*5/10]
if WHICH == 22: process.source.fileNames = process.source.fileNames[lenFileNames*5/10:lenFileNames*6/10]
if WHICH == 23: process.source.fileNames = process.source.fileNames[lenFileNames*6/10:lenFileNames*7/10]
if WHICH == 24: process.source.fileNames = process.source.fileNames[lenFileNames*7/10:lenFileNames*8/10]
if WHICH == 25: process.source.fileNames = process.source.fileNames[lenFileNames*8/10:lenFileNames*9/10]
if WHICH == 26: process.source.fileNames = process.source.fileNames[lenFileNames*9/10:lenFileNames*10/10]

if WHICH == 30: process.source.fileNames = process.source.fileNames[lenFileNames*0/10:lenFileNames*1/10]
if WHICH == 31: process.source.fileNames = process.source.fileNames[lenFileNames*1/10:lenFileNames*2/10]
if WHICH == 32: process.source.fileNames = process.source.fileNames[lenFileNames*2/10:lenFileNames*3/10]
if WHICH == 33: process.source.fileNames = process.source.fileNames[lenFileNames*3/10:lenFileNames*4/10]
if WHICH == 34: process.source.fileNames = process.source.fileNames[lenFileNames*4/10:lenFileNames*5/10]
if WHICH == 35: process.source.fileNames = process.source.fileNames[lenFileNames*5/10:lenFileNames*6/10]
if WHICH == 36: process.source.fileNames = process.source.fileNames[lenFileNames*6/10:lenFileNames*7/10]
if WHICH == 37: process.source.fileNames = process.source.fileNames[lenFileNames*7/10:lenFileNames*8/10]
if WHICH == 38: process.source.fileNames = process.source.fileNames[lenFileNames*8/10:lenFileNames*9/10]
if WHICH == 39: process.source.fileNames = process.source.fileNames[lenFileNames*9/10:lenFileNames*10/10]

if WHICH == 40: process.source.fileNames = process.source.fileNames[lenFileNames*0/2:lenFileNames*1/2]
if WHICH == 41: process.source.fileNames = process.source.fileNames[lenFileNames*1/2:lenFileNames*2/2]

if WHICH == 42: process.source.fileNames = process.source.fileNames[lenFileNames*0/2:lenFileNames*1/2]
if WHICH == 43: process.source.fileNames = process.source.fileNames[lenFileNames*1/2:lenFileNames*2/2]

if WHICH == 44: process.source.fileNames = process.source.fileNames[lenFileNames*0/2:lenFileNames*1/2]
if WHICH == 45: process.source.fileNames = process.source.fileNames[lenFileNames*1/2:lenFileNames*2/2]

if WHICH == 46: process.source.fileNames = process.source.fileNames[lenFileNames*0/2:lenFileNames*1/2]
if WHICH == 47: process.source.fileNames = process.source.fileNames[lenFileNames*1/2:lenFileNames*2/2]

if WHICH == 48: process.source.fileNames = process.source.fileNames[lenFileNames*0/2:lenFileNames*1/2]
if WHICH == 49: process.source.fileNames = process.source.fileNames[lenFileNames*1/2:lenFileNames*2/2]

if WHICH == 50: process.source.fileNames = process.source.fileNames[lenFileNames*0/3:lenFileNames*1/3]
if WHICH == 51: process.source.fileNames = process.source.fileNames[lenFileNames*1/3:lenFileNames*2/3]
if WHICH == 52: process.source.fileNames = process.source.fileNames[lenFileNames*2/3:lenFileNames*3/3]

if WHICH == 53: process.source.fileNames = process.source.fileNames[lenFileNames*0/3:lenFileNames*1/3]
if WHICH == 54: process.source.fileNames = process.source.fileNames[lenFileNames*1/3:lenFileNames*2/3]
if WHICH == 55: process.source.fileNames = process.source.fileNames[lenFileNames*2/3:lenFileNames*3/3]

if WHICH == 56: process.source.fileNames = process.source.fileNames[lenFileNames*0/3:lenFileNames*1/3]
if WHICH == 57: process.source.fileNames = process.source.fileNames[lenFileNames*1/3:lenFileNames*2/3]
if WHICH == 58: process.source.fileNames = process.source.fileNames[lenFileNames*2/3:lenFileNames*3/3]

if WHICH == 59: process.source.fileNames = process.source.fileNames[lenFileNames*0/3:lenFileNames*1/3]
if WHICH == 60: process.source.fileNames = process.source.fileNames[lenFileNames*1/3:lenFileNames*2/3]
if WHICH == 61: process.source.fileNames = process.source.fileNames[lenFileNames*2/3:lenFileNames*3/3]

if WHICH == 62: process.source.fileNames = process.source.fileNames[lenFileNames*0/3:lenFileNames*1/3]
if WHICH == 63: process.source.fileNames = process.source.fileNames[lenFileNames*1/3:lenFileNames*2/3]
if WHICH == 64: process.source.fileNames = process.source.fileNames[lenFileNames*2/3:lenFileNames*3/3]

if WHICH == 68: process.source.fileNames = process.source.fileNames[lenFileNames*0/8:lenFileNames*1/8]
if WHICH == 69: process.source.fileNames = process.source.fileNames[lenFileNames*1/8:lenFileNames*2/8]
if WHICH == 70: process.source.fileNames = process.source.fileNames[lenFileNames*2/8:lenFileNames*3/8]
if WHICH == 71: process.source.fileNames = process.source.fileNames[lenFileNames*3/8:lenFileNames*4/8]
if WHICH == 72: process.source.fileNames = process.source.fileNames[lenFileNames*4/8:lenFileNames*5/8]
if WHICH == 73: process.source.fileNames = process.source.fileNames[lenFileNames*5/8:lenFileNames*6/8]
if WHICH == 74: process.source.fileNames = process.source.fileNames[lenFileNames*6/8:lenFileNames*7/8]
if WHICH == 75: process.source.fileNames = process.source.fileNames[lenFileNames*7/8:lenFileNames*8/8]

if WHICH == 76: process.source.fileNames = process.source.fileNames[lenFileNames*0/12:lenFileNames*1/12]
if WHICH == 77: process.source.fileNames = process.source.fileNames[lenFileNames*1/12:lenFileNames*2/12]
if WHICH == 78: process.source.fileNames = process.source.fileNames[lenFileNames*2/12:lenFileNames*3/12]
if WHICH == 79: process.source.fileNames = process.source.fileNames[lenFileNames*3/12:lenFileNames*4/12]
if WHICH == 80: process.source.fileNames = process.source.fileNames[lenFileNames*4/12:lenFileNames*5/12]
if WHICH == 81: process.source.fileNames = process.source.fileNames[lenFileNames*5/12:lenFileNames*6/12]
if WHICH == 82: process.source.fileNames = process.source.fileNames[lenFileNames*6/12:lenFileNames*7/12]
if WHICH == 83: process.source.fileNames = process.source.fileNames[lenFileNames*7/12:lenFileNames*8/12]
if WHICH == 84: process.source.fileNames = process.source.fileNames[lenFileNames*8/12:lenFileNames*9/12]
if WHICH == 85: process.source.fileNames = process.source.fileNames[lenFileNames*9/12:lenFileNames*10/12]
if WHICH == 86: process.source.fileNames = process.source.fileNames[lenFileNames*10/12:lenFileNames*11/12]
if WHICH == 87: process.source.fileNames = process.source.fileNames[lenFileNames*11/12:lenFileNames*12/12]

if WHICH == 92: process.source.fileNames = process.source.fileNames[lenFileNames*0/10:lenFileNames*1/10]
if WHICH == 93: process.source.fileNames = process.source.fileNames[lenFileNames*1/10:lenFileNames*2/10]
if WHICH == 94: process.source.fileNames = process.source.fileNames[lenFileNames*2/10:lenFileNames*3/10]
if WHICH == 95: process.source.fileNames = process.source.fileNames[lenFileNames*3/10:lenFileNames*4/10]
if WHICH == 96: process.source.fileNames = process.source.fileNames[lenFileNames*4/10:lenFileNames*5/10]
if WHICH == 97: process.source.fileNames = process.source.fileNames[lenFileNames*5/10:lenFileNames*6/10]
if WHICH == 98: process.source.fileNames = process.source.fileNames[lenFileNames*6/10:lenFileNames*7/10]
if WHICH == 99: process.source.fileNames = process.source.fileNames[lenFileNames*7/10:lenFileNames*8/10]
if WHICH == 100: process.source.fileNames = process.source.fileNames[lenFileNames*8/10:lenFileNames*9/10]
if WHICH == 101: process.source.fileNames = process.source.fileNames[lenFileNames*9/10:lenFileNames*10/10]

if WHICH == 102: process.source.fileNames = process.source.fileNames[lenFileNames*0/10:lenFileNames*1/10]
if WHICH == 103: process.source.fileNames = process.source.fileNames[lenFileNames*1/10:lenFileNames*2/10]
if WHICH == 104: process.source.fileNames = process.source.fileNames[lenFileNames*2/10:lenFileNames*3/10]
if WHICH == 105: process.source.fileNames = process.source.fileNames[lenFileNames*3/10:lenFileNames*4/10]
if WHICH == 106: process.source.fileNames = process.source.fileNames[lenFileNames*4/10:lenFileNames*5/10]
if WHICH == 107: process.source.fileNames = process.source.fileNames[lenFileNames*5/10:lenFileNames*6/10]
if WHICH == 108: process.source.fileNames = process.source.fileNames[lenFileNames*6/10:lenFileNames*7/10]
if WHICH == 109: process.source.fileNames = process.source.fileNames[lenFileNames*7/10:lenFileNames*8/10]
if WHICH == 110: process.source.fileNames = process.source.fileNames[lenFileNames*8/10:lenFileNames*9/10]
if WHICH == 111: process.source.fileNames = process.source.fileNames[lenFileNames*9/10:lenFileNames*10/10]

process.load("Configuration/StandardSequences/FrontierConditions_GlobalTag_cff")
if realData:
    process.GlobalTag.globaltag = "GR10_P_V11::All"
else:
    process.GlobalTag.globaltag = "MC_38Y_V12::All"

process.MessageLogger = cms.Service("MessageLogger", destinations = cms.untracked.vstring("cout"), cout = cms.untracked.PSet(threshold = cms.untracked.string("ERROR")))

process.load("AnalysisAlgos.MuJetProducer.MuJetProducer_cff")
process.MuJetProducer.muons = cms.InputTag("cleanPatMuonsTriggerMatch")

process.load("AnalysisAlgos.MuJetPlusFakeMuon.MuJetPlusFakeMuon_cfi")
process.MuJetPlusTracks = process.MuJetPlusFakeMuon.clone(numberOfFakes = cms.uint32(2))

if realData:
    process.NoScraping = cms.EDFilter("FilterOutScraping",
                                      applyfilter = cms.untracked.bool(True),
                                      debugOn = cms.untracked.bool(False),
                                      numtrack = cms.untracked.uint32(10),
                                      thresh = cms.untracked.double(0.25)
                                      )
    process.load("RecoVertex.PrimaryVertexProducer.OfflinePrimaryVertices_cfi")
    process.OneGoodVertexFilter = cms.EDFilter("VertexSelector",
                                               src = cms.InputTag("offlinePrimaryVertices"),
                                               cut = cms.string("!isFake && tracksSize > 3 && abs(z) <= 24"),
                                               filter = cms.bool(True),
                                               )
    process.Path = cms.Path(process.NoScraping * process.OneGoodVertexFilter * process.MuJetProducer * process.MuJetPlusTracks)
else:
    process.Path = cms.Path(process.MuJetProducer * process.MuJetPlusTracks)

process.OutputModule = cms.OutputModule("PoolOutputModule", fileName = cms.untracked.string("/uscmst1b_scratch/lpc1/3DayLifetime/pivarski/MUJETS05/MuJets_%s_%d.root" % (sample, WHICH)),
                                        SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring("Path")),
                                        outputCommands = cms.untracked.vstring("drop *",
                                                                               "keep *_MuJetProducer_*_*",
                                                                               "keep *_patMuons_*_*",
                                                                               "keep *_cleanPatMuons_*_*",
                                                                               "keep *_patTrigger*_*_*",
                                                                               "keep *_muonTriggerMatch*_*_*",
                                                                               "keep *_patTriggerEvent_*_*",
                                                                               "keep *_cleanPatMuonsTriggerMatch_*_*",
#                                                                                "keep *_towerMaker_*_*",
                                                                               "keep *_genParticles_*_*",
                                                                               "keep *_generator_*_*",
                                                                               "keep *_offlineBeamSpot_*_*",
                                                                               "keep *_offlinePrimaryVertices_*_*",
                                                                               "keep *_offlinePrimaryVerticesWithBS_*_*",
#                                                                                "keep *_met_*_*",
#                                                                                "keep *_metHO_*_*",
#                                                                                "keep *_metNoHF_*_*",
#                                                                                "keep *_metNoHFHO_*_*",
#                                                                                "keep *_metOpt_*_*",
#                                                                                "keep *_metOptHO_*_*",
#                                                                                "keep *_metOptNoHF_*_*",
#                                                                                "keep *_metOptNoHFHO_*_*",
#                                                                                "keep *_genMetCalo_*_*",
#                                                                                "keep *_genMetCaloAndNonPrompt_*_*",
#                                                                                "keep *_genMetTrue_*_*",
#                                                                                "keep *_tcMet_*_*",
#                                                                                "keep *_pfMet_*_*",
                                                                               ))

process.EndPath = cms.EndPath(process.OutputModule)
