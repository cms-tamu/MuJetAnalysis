# Auto generated configuration file
# using: 
# Revision: 1.172.2.5 
# Source: /cvs_server/repositories/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: Configuration/Generator/PairGun100_dispvert100_cfg -s GEN:ProductionFilterSequence,SIM,DIGI,L1,DIGI2RAW,HLT --eventcontent RAWSIM --datatier GEN-SIM-RAW --conditions FrontierConditions_GlobalTag,MC_36Y_V10::All --pileup=E7TeV_AVE_5_BX156 -n 10 --no_exec
import FWCore.ParameterSet.Config as cms

################## BEGIN ADDED BY HAND
import os
GENERATOR = os.getenv("GENERATOR")
NUMBEROFEVENTS = int(os.getenv("NUMBEROFEVENTS"))
RANDOMSEED = (int(os.getenv("PROCESS")) + 1) * 1000
PILEUP = os.getenv("PILEUP")
################## END ADDED BY HAND

process = cms.Process('HLT')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
# process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger = cms.Service("MessageLogger", destinations = cms.untracked.vstring("cout"), cout = cms.untracked.PSet(threshold = cms.untracked.string("ERROR")))
process.load('Configuration.StandardSequences.Mixing%s_cff' % PILEUP)
process.load('Configuration.StandardSequences.GeometryExtended_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('Configuration.StandardSequences.VtxSmearedRealistic7TeVCollision_cff')
process.load('Configuration.StandardSequences.Sim_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('HLTrigger.Configuration.HLT_1E31_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.EventContent.EventContent_cff')

################## BEGIN ADDED BY HAND
process.load("Configuration.Generator.%s_cfg" % GENERATOR)

process.RandomNumberGeneratorService.hiSignalG4SimHits.initialSeed = cms.untracked.uint32(RANDOMSEED+0)
process.RandomNumberGeneratorService.simCastorDigis.initialSeed = cms.untracked.uint32(RANDOMSEED+1)
process.RandomNumberGeneratorService.generator.initialSeed = cms.untracked.uint32(RANDOMSEED+2)
process.RandomNumberGeneratorService.simMuonRPCDigis.initialSeed = cms.untracked.uint32(RANDOMSEED+3)
process.RandomNumberGeneratorService.hiSignal.initialSeed = cms.untracked.uint32(RANDOMSEED+4)
process.RandomNumberGeneratorService.simEcalUnsuppressedDigis.initialSeed = cms.untracked.uint32(RANDOMSEED+5)
process.RandomNumberGeneratorService.simSiStripDigis.initialSeed = cms.untracked.uint32(RANDOMSEED+6)
process.RandomNumberGeneratorService.mix.initialSeed = cms.untracked.uint32(RANDOMSEED+7)
process.RandomNumberGeneratorService.simHcalUnsuppressedDigis.initialSeed = cms.untracked.uint32(RANDOMSEED+8)
process.RandomNumberGeneratorService.LHCTransport.initialSeed = cms.untracked.uint32(RANDOMSEED+9)
process.RandomNumberGeneratorService.simMuonCSCDigis.initialSeed = cms.untracked.uint32(RANDOMSEED+10)
process.RandomNumberGeneratorService.mixData.initialSeed = cms.untracked.uint32(RANDOMSEED+11)
process.RandomNumberGeneratorService.VtxSmeared.initialSeed = cms.untracked.uint32(RANDOMSEED+12)
process.RandomNumberGeneratorService.g4SimHits.initialSeed = cms.untracked.uint32(RANDOMSEED+13)
process.RandomNumberGeneratorService.simMuonDTDigis.initialSeed = cms.untracked.uint32(RANDOMSEED+14)
process.RandomNumberGeneratorService.simSiPixelDigis.initialSeed = cms.untracked.uint32(RANDOMSEED+15)
process.RandomNumberGeneratorService.hiSignalLHCTransport.initialSeed = cms.untracked.uint32(RANDOMSEED+16)

if PILEUP != "NoPileUp":
    # /RelValMinBias/CMSSW_3_6_3-MC_36Y_V10-v1/GEN-SIM-DIGI-RAW-HLTDEBUG
    process.mix.input.fileNames = cms.untracked.vstring(
        '/store/relval/CMSSW_3_6_3/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_36Y_V10-v1/0006/FA6B7B0D-5878-DF11-851D-0018F3D09680.root',
        '/store/relval/CMSSW_3_6_3/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_36Y_V10-v1/0005/ECFDCB5A-0478-DF11-B366-00261894383C.root',
        '/store/relval/CMSSW_3_6_3/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_36Y_V10-v1/0005/B230D11E-0178-DF11-A85E-003048678FF4.root',
        '/store/relval/CMSSW_3_6_3/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_36Y_V10-v1/0005/8ED645A8-0378-DF11-8501-002618943875.root',
        '/store/relval/CMSSW_3_6_3/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_36Y_V10-v1/0005/6E3AF182-0278-DF11-9BB6-003048678F8C.root',
        )

process.RAWSIMEventContent.outputCommands.append("keep *_generator_*_*")
################## END ADDED BY HAND

process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.1 $'),
    annotation = cms.untracked.string('Configuration/Generator/PairGun100_dispvert100_cfg nevts:%d' % NUMBEROFEVENTS),
    name = cms.untracked.string('PyReleaseValidation')
)
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(NUMBEROFEVENTS)
)
process.options = cms.untracked.PSet(

)
# Input source
### process.source = cms.Source("EmptySource")   # duplicated in source

# Output definition
process.output = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    outputCommands = process.RAWSIMEventContent.outputCommands,
    fileName = cms.untracked.string('GEN-SIM-RAW.root'),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM-RAW'),
        filterName = cms.untracked.string('')
    ),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    )
)

# Additional output definition

# Other statements
process.GlobalTag.globaltag = 'MC_36Y_V10::All'

# Path and EndPath definitions
process.generation_step = cms.Path(process.pgen)
process.simulation_step = cms.Path(process.psim)
process.digitisation_step = cms.Path(process.pdigi)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.digi2raw_step = cms.Path(process.DigiToRaw)
process.endjob_step = cms.Path(process.endOfProcess)
process.out_step = cms.EndPath(process.output)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.simulation_step,process.digitisation_step,process.L1simulation_step,process.digi2raw_step)
process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.endjob_step,process.out_step])
# special treatment in case of production filter sequence  
for path in process.paths: 
    getattr(process,path)._seq = process.ProductionFilterSequence*getattr(process,path)._seq
