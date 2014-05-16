import FWCore.ParameterSet.Config as cms

process = cms.Process("PATIFY")
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring(
#     "/store/mc/Spring10/InclusiveMu5_Pt30/GEN-SIM-RECO/START3X_V26_S09-v1/0036/BE72C174-4149-DF11-B02B-001A92810AA6.root",
#     "/store/mc/Spring10/InclusiveMu5_Pt30/GEN-SIM-RECO/START3X_V26_S09-v1/0035/00B02ADB-1648-DF11-A6D3-00261894385A.root",
#     "/store/mc/Spring10/InclusiveMu5_Pt30/GEN-SIM-RECO/START3X_V26_S09-v1/0032/F87ED408-4346-DF11-8A63-003048678F78.root",
#     "/store/mc/Spring10/InclusiveMu5_Pt30/GEN-SIM-RECO/START3X_V26_S09-v1/0032/F4E452B6-5046-DF11-8CF1-0018F3D096FE.root",
#     "/store/mc/Spring10/InclusiveMu5_Pt30/GEN-SIM-RECO/START3X_V26_S09-v1/0032/F04970BD-4346-DF11-BCEA-00304867923E.root",
#     "/store/mc/Summer10/ppMuX/GEN-SIM-RECO/START37_V5_S09-v1/0007/FEB66DFA-2586-DF11-96CA-003048678F6C.root",
#     "/store/mc/Summer10/ppMuX/GEN-SIM-RECO/START37_V5_S09-v1/0007/FE7FC9BA-1D86-DF11-8A70-002618FDA208.root",
#     "/store/mc/Summer10/ppMuX/GEN-SIM-RECO/START37_V5_S09-v1/0007/FE67B88A-2686-DF11-B2AA-0026189438D2.root",
#     "/store/mc/Summer10/ppMuX/GEN-SIM-RECO/START37_V5_S09-v1/0007/FCCC98C1-2486-DF11-A4A0-00261894395F.root",
#     "/store/mc/Summer10/ppMuX/GEN-SIM-RECO/START37_V5_S09-v1/0007/FCBA2595-2186-DF11-A8DC-002618943885.root",
#     "/store/mc/Summer10/ppMuX/GEN-SIM-RECO/START37_V5_S09-v1/0007/FABA8CD6-2086-DF11-A7F5-002618943857.root",
    "/store/mc/Spring10/ZZ/GEN-SIM-RECO/START3X_V26_S09-v1/0035/FE159566-B847-DF11-82C4-0017A4771028.root",
    "/store/mc/Spring10/ZZ/GEN-SIM-RECO/START3X_V26_S09-v1/0035/F0353B38-BB47-DF11-9DC2-0017A4770000.root",
    "/store/mc/Spring10/ZZ/GEN-SIM-RECO/START3X_V26_S09-v1/0035/CADD6C43-BB47-DF11-B297-00237DA096F8.root",
    "/store/mc/Spring10/ZZ/GEN-SIM-RECO/START3X_V26_S09-v1/0035/BECE79B5-CA47-DF11-99C6-0017A4770C1C.root",
#     "/store/mc/Spring10/WZ/GEN-SIM-RECO/START3X_V26_S09-v1/0086/786148D4-6C4D-DF11-9229-0017A477100C.root",
#     "/store/mc/Spring10/WZ/GEN-SIM-RECO/START3X_V26_S09-v1/0070/FEE84FC1-E54A-DF11-9AEF-001E0B48A1C4.root",
#     "/store/mc/Spring10/WZ/GEN-SIM-RECO/START3X_V26_S09-v1/0070/C81A83CD-E64A-DF11-8510-00237DA24DE0.root",
#     "/store/mc/Spring10/WZ/GEN-SIM-RECO/START3X_V26_S09-v1/0070/BA2E133D-E64A-DF11-82DB-0017A4770C00.root",
))
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

process.MessageLogger = cms.Service("MessageLogger", destinations = cms.untracked.vstring("cout"), cout = cms.untracked.PSet(threshold = cms.untracked.string("ERROR")))

process.load("Configuration/StandardSequences/FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = "MC_38Y_V12::All"

process.EventCounterForCRAB = cms.EDAnalyzer("EventCounterForCRAB")
process.EventCounterPath = cms.Path(process.EventCounterForCRAB)

process.load("AnalysisDataFormats.MuJetAnalysis.RECOtoPAT_cff")
process.countPatMuons.minNumber = cms.uint32(2)
process.Path = cms.Path(process.patify)

process.load("AnalysisDataFormats.MuJetAnalysis.EventContent_version6_cff")
process.patOutput.fileName = cms.untracked.string("output.root")
process.patOutput.SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring("Path"))

process.EndPath = cms.EndPath(process.patOutput)

process.schedule = cms.Schedule(process.EventCounterPath, process.Path, process.EndPath)
