import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing

process = cms.Process("MUONJET")

options = VarParsing('analysis')
options.register ("mc", False, VarParsing.multiplicity.singleton, VarParsing.varType.bool)
options.register ("year", 2018, VarParsing.multiplicity.singleton, VarParsing.varType.int)
options.register ("era", "ABC", VarParsing.multiplicity.singleton, VarParsing.varType.string)
options.parseArguments()

## MessageLogger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
# verbose flags for the PF2PAT modules
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.options.allowUnscheduled = cms.untracked.bool(False)

## Geometry and Detector Conditions (needed for a few patTuple production steps)
process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")
process.load("Configuration.Geometry.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag

#Tags are specified here: https://twiki.cern.ch/twiki/bin/viewauth/CMS/PdmVAnalysisSummaryTable
globalTagChoice = ""
if options.mc:
    #2017 MC
    if options.year == 2017:
        globalTagChoice = '94X_mc2017_realistic_v17'
    #2018 MC
    if options.year == 2018:
        globalTagChoice = '102X_upgrade2018_realistic_v20'
else:
    #2017 data
    if options.year == 2017:
        globalTagChoice = '94X_dataRun2_v11'
    #2018 data
    if options.year == 2018:
        #2018 data: Era ABC
        if options.era == "ABC":
            globalTagChoice = '102X_dataRun2_v12'
        #2018 data: Era D
        else:
            globalTagChoice = '102X_dataRun2_Prompt_v15'

print "Chosen global tag", globalTagChoice
process.GlobalTag = GlobalTag(process.GlobalTag, globalTagChoice)

process.load("Configuration.StandardSequences.MagneticField_cff")
#process.load("MuJetAnalysis.DataFormats.miniAODtoPAT_cff")
process.load("PhysicsTools.PatAlgos.slimming.unpackedTracksAndVertices_cfi")
#process.load("MuJetAnalysis.MuJetProducer.MuJetProducer_MiniAOD_cff")#Pre-Run2 mu-jet cluster
process.load("MuJetAnalysis.MuJetProducer.MuJetProducerRun2_cff")#Run2 mu-jet cluster
process.load("MuJetAnalysis.CutFlowAnalyzer.CutFlowAnalyzer_MiniAOD_cff")

process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
    'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_35_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/00000/0CABE26E-1139-274F-9FBC-524B81FF4DFF.root',
    'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_35_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/00000/141E5474-1D77-3B40-9668-26734EE7CFAE.root',
    'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_35_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/00000/17AD3880-5F49-4C48-B373-A03EF0FAA1B1.root',
    'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_35_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/00000/22D8D543-D0F4-5F4A-B74F-6B86086EC697.root',
    'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_35_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/00000/2B2EA0D9-9BDC-E143-91CF-2868D020449F.root',
    'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_35_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/00000/5BB2AC85-68FA-8943-B08A-0999B5327E83.root',
    'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_35_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/00000/A3043536-BF2F-D043-8FB6-E65F984534D1.root',
    'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_35_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/00000/AC3EE1A9-B10A-3045-B3CE-DD1F3F21CCF6.root',
    'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_35_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/00000/AFD20DC5-3C93-0347-983D-BDB9CD529942.root',
    'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_35_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/00000/DB853551-1045-F445-9618-32C306F0AB43.root',
    'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_35_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/00000/E9D33B62-2BC8-AA48-8777-DBD8BD799E7D.root',
    'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_35_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/00000/EE0C457B-5858-4F42-B75B-A1B1101279B7.root',
    'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_35_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/00000/F2FAB06C-872E-1C42-BE79-A4ED09541A08.root',
    'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_35_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/130000/236E6B83-E3C6-EE43-822C-029F867D5CE1.root',
    'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_35_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/130000/2FA14425-F7E5-C243-866D-F542F9D43C78.root',
    'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_35_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/130000/516283AE-4CCE-344C-8EA1-7A60C9DC45BB.root',
    'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_35_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/130000/6639580B-CC85-F045-8FAE-1162A2279741.root',
    'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_35_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/130000/7AB3BE9D-4CB5-E94F-B340-35E11B0D284F.root',
    'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_35_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/130000/905967A1-B3BA-6D4B-98B6-3788426F4BE8.root',
    'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_35_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/130000/BD974275-4107-BE4A-8D7A-2F01A7D7CF8E.root',
    'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_35_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/130000/D654B382-A6D6-CC4F-8CDE-A734310F73C8.root',
    'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_35_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/130000/DB291F65-1A2C-F64C-AE5D-1C8F5CDD98B1.root',
    'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_35_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/130000/FF605D79-C66B-C542-BEB5-5AA5486283DD.root',
    'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_35_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/40000/3F7FE0F2-DE94-7E48-AA4E-A22E87171B26.root',
    'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_35_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/40000/A2AD7897-2618-7246-9BA5-F7DAF9CB6200.root',
    'file:/scratch/group/mitchcomp/CMS/data/mc/RunIIAutumn18MiniAOD/MSSMD_mH_125_mN1_60_mGammaD_35_cT_100_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/40000/C7C6D175-61CA-2B40-8A68-DCB1EC6E6DFC.root',
    )
)

process.out = cms.OutputModule(
    "PoolOutputModule",
    fileName = cms.untracked.string('patTuple.root')
    )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.p = cms.Path(
    process.unpackedTracksAndVertices *
    process.MuJetProducers *
    process.cutFlowAnalyzers
    )

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("out_ana_1.root")
)
