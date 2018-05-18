import FWCore.ParameterSet.Config as cms
import os
import sys

process = cms.Process("MUONJET")

## MessageLogger
process.load("FWCore.MessageLogger.MessageLogger_cfi")

# verbose flags for the PF2PAT modules
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.options.allowUnscheduled = cms.untracked.bool(False)

## Geometry and Detector Conditions (needed for a few patTuple production steps)
process.load("Configuration.Geometry.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc')
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("MuJetAnalysis.DataFormats.miniAODtoPAT_cff")
process.load("MuJetAnalysis.MuJetProducer.MuJetProducer_cff")
process.load("MuJetAnalysis.CutFlowAnalyzer.CutFlowAnalyzer_cff")


PROCESS = str(os.getenv("PROCESS"))
if ( PROCESS == None or PROCESS == "" ): PROCESS = int(0)
else : PROCESS = int(PROCESS)-1
JOBS = int(sys.argv[3])

process.load("MuJetAnalysis.CutFlowAnalyzer."+sys.argv[2]+"_cff");

lenFileNames = len(process.source.fileNames)
process.source.fileNames = process.source.fileNames[lenFileNames*PROCESS/JOBS:lenFileNames*(PROCESS+1)/JOBS]


#process.source = cms.Source("PoolSource",
#    fileNames = cms.untracked.vstring(
#        "file:out_reco.root"
#        'file:/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/crab_DarkSUSY_mH_125_mGammaD_0250_cT_000_13TeV_MG452_BR224_LHE_pythia8_MINIAOD_MINIAOD_V2_v2/161005_194724/0000/out_miniaod_1.root'
#    )
#)

process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string('patTuple.root')
)

### Add MuJet Dataformats
from MuJetAnalysis.DataFormats.EventContent_version11_cff import *
process = customizePatOutput(process)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.p = cms.Path(
    process.patifyMC *
    process.MuJetProducers *
    process.cutFlowAnalyzers
)

process.outpath = cms.EndPath(process.out)

process.TFileService = cms.Service("TFileService", fileName = cms.string(sys.argv[2]+"/ana_%03d.root" % PROCESS) )

# process.TFileService = cms.Service("TFileService",
#     fileName = cms.string("out_ana.root")
# )
