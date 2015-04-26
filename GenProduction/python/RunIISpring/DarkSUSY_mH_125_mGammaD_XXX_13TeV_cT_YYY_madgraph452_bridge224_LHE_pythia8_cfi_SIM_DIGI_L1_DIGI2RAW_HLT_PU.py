# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: DarkSUSY_mH_125_mGammaD_XXX_13TeV_cT_YYY_madgraph452_bridge224_LHE_pythia8_cfi --mc --conditions MCRUN2_74_V7 --pileup_input das:/MinBias_TuneCUETP8M1_13TeV-pythia8/RunIIWinter15GS-MCRUN2_71_V1-v1/GEN-SIM --pileup 2015_25ns_Startup_PoissonOOTPU -s SIM,DIGI,L1,DIGI2RAW,HLT:@frozen25ns --datatier GEN-SIM-RAW --customise SLHCUpgradeSimulations/Configuration/postLS1Customs.customisePostLS1 --eventcontent RAWSIM --magField 38T_PostLS1 --no_exec
import FWCore.ParameterSet.Config as cms

process = cms.Process('HLT')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mix_2015_25ns_Startup_PoissonOOTPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.Geometry.GeometrySimDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_PostLS1_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('HLTrigger.Configuration.HLT_25ns14e33_v1_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1)
)

# Input source
process.source = cms.Source("PoolSource",
    dropDescendantsOfDroppedBranches = cms.untracked.bool(False),
    fileNames = cms.untracked.vstring('file:output.root'),
    inputCommands = cms.untracked.vstring('keep *', 
#        'drop *_genParticlesForJets_*_*', 
#        'drop *_kt4GenJets_*_*', 
#        'drop *_kt6GenJets_*_*', 
        # 'drop *_iterativeCone5GenJets_*_*', 
        # 'drop *_ak4GenJets_*_*', 
        # 'drop *_ak7GenJets_*_*', 
        # 'drop *_ak8GenJets_*_*', 
        # 'drop *_ak4GenJetsNoNu_*_*', 
        # 'drop *_ak8GenJetsNoNu_*_*', 
        # 'drop *_genCandidatesForMET_*_*', 
        # 'drop *_genParticlesForMETAllVisible_*_*', 
        # 'drop *_genMetCalo_*_*', 
        # 'drop *_genMetCaloAndNonPrompt_*_*', 
        # 'drop *_genMetTrue_*_*', 
        'drop *_genMetIC5GenJs_*_*'),
    secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('DarkSUSY_mH_125_mGammaD_XXX_13TeV_cT_YYY_madgraph452_bridge224_LHE_pythia8_cfi nevts:1'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.RAWSIMoutput = cms.OutputModule("PoolOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM-RAW'),
        filterName = cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    fileName = cms.untracked.string('output.root'),
    outputCommands = process.RAWSIMEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

# Additional output definition

# Other statements
#process.mix.input.fileNames = cms.untracked.vstring(['/store/mc/RunIIWinter15GS/MinBias_TuneCUETP8M1_13TeV-pythia8/GEN-SIM/MCRUN2_71_V1-v1/00000/0028ABCB-74B0-E411-B596-0025904C4F50.root', '/store/mc/RunIIWinter15GS/MinBias_TuneCUETP8M1_13TeV-pythia8/GEN-SIM/MCRUN2_71_V1-v1/00000/007FD3D8-74B0-E411-AC02-782BCB67826E.root', '/store/mc/RunIIWinter15GS/MinBias_TuneCUETP8M1_13TeV-pythia8/GEN-SIM/MCRUN2_71_V1-v1/00000/00AAE11D-74B0-E411-BCF8-DF448471F33D.root', '/store/mc/RunIIWinter15GS/MinBias_TuneCUETP8M1_13TeV-pythia8/GEN-SIM/MCRUN2_71_V1-v1/00000/00BC66B7-6CAF-E411-86B6-20CF3056171F.root', '/store/mc/RunIIWinter15GS/MinBias_TuneCUETP8M1_13TeV-pythia8/GEN-SIM/MCRUN2_71_V1-v1/00000/00C59C87-75B0-E411-918F-63BFB108B170.root', '/store/mc/RunIIWinter15GS/MinBias_TuneCUETP8M1_13TeV-pythia8/GEN-SIM/MCRUN2_71_V1-v1/00000/02052468-72AF-E411-9F90-002590D9D990.root', '/store/mc/RunIIWinter15GS/MinBias_TuneCUETP8M1_13TeV-pythia8/GEN-SIM/MCRUN2_71_V1-v1/00000/022D9B0E-6EAF-E411-90AA-0022195E66A7.root', '/store/mc/RunIIWinter15GS/MinBias_TuneCUETP8M1_13TeV-pythia8/GEN-SIM/MCRUN2_71_V1-v1/00000/027B2D2C-74B0-E411-8DF1-001E682F8C7C.root', '/store/mc/RunIIWinter15GS/MinBias_TuneCUETP8M1_13TeV-pythia8/GEN-SIM/MCRUN2_71_V1-v1/00000/02B9B6A5-74B0-E411-A287-002590491B22.root', '/store/mc/RunIIWinter15GS/MinBias_TuneCUETP8M1_13TeV-pythia8/GEN-SIM/MCRUN2_71_V1-v1/00000/02C48802-6EAF-E411-96A0-001E67248688.root'])
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'MCRUN2_74_V7', '')

# Path and EndPath definitions
process.simulation_step = cms.Path(process.psim)
process.digitisation_step = cms.Path(process.pdigi)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.digi2raw_step = cms.Path(process.DigiToRaw)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RAWSIMoutput_step = cms.EndPath(process.RAWSIMoutput)

# Schedule definition
process.schedule = cms.Schedule(process.simulation_step,process.digitisation_step,process.L1simulation_step,process.digi2raw_step)
process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.endjob_step,process.RAWSIMoutput_step])

# customisation of the process.

# Automatic addition of the customisation function from SLHCUpgradeSimulations.Configuration.postLS1Customs
from SLHCUpgradeSimulations.Configuration.postLS1Customs import customisePostLS1 

#call to customisation function customisePostLS1 imported from SLHCUpgradeSimulations.Configuration.postLS1Customs
process = customisePostLS1(process)

# Automatic addition of the customisation function from HLTrigger.Configuration.customizeHLTforMC
from HLTrigger.Configuration.customizeHLTforMC import customizeHLTforMC 

#call to customisation function customizeHLTforMC imported from HLTrigger.Configuration.customizeHLTforMC
process = customizeHLTforMC(process)

# Automatic addition of the customisation function from MuJetAnalysis.GenProduction.addPileup
from MuJetAnalysis.GenProduction.addPileup import addPileup 

#call to customisation function addPileup imported from MuJetAnalysis.GenProduction.addPileup
process = addPileup(process)


# End of customisation functions

