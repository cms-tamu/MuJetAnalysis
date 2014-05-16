# Auto generated configuration file
# using: 
# Revision: 1.207 
# Source: /cvs_server/repositories/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: Configuration/Generator/PairGun100_cfg -s GEN:ProductionFilterSequence,SIM,DIGI,L1,DIGI2RAW,HLT:GRun --eventcontent RAWSIM --datatier GEN-SIM-RAW --conditions FrontierConditions_GlobalTag,MC_38Y_V9::All --pileup=E7TeV_AVE_5_BX156 -n 10 --no_exec
import FWCore.ParameterSet.Config as cms

################## BEGIN ADDED BY HAND
import os
GENERATOR = os.getenv("GENERATOR")
NUMBEROFEVENTS = int(os.getenv("NUMBEROFEVENTS"))
RANDOMSEED = (int(os.getenv("PROCESS")) + 1) * 1000
PILEUP = os.getenv("PILEUP")

# Turned off HLT emulation because it apparently isn't
# working... besides, it's not important for these simulations; mostly
# just InclusiveMu (which I don't control)

################## END ADDED BY HAND

process = cms.Process('HLT')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
# process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger = cms.Service("MessageLogger", destinations = cms.untracked.vstring("cout"), cout = cms.untracked.PSet(threshold = cms.untracked.string("ERROR")))
process.load('Configuration.StandardSequences.Mixing%s_cff' % PILEUP)
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('Configuration.StandardSequences.VtxSmearedRealistic7TeVCollision_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('HLTrigger.Configuration.HLT_GRun_cff')
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
    # /RelValMinBias/CMSSW_3_8_2-MC_38Y_V9-v1/GEN-SIM-DIGI-RAW-HLTDEBUG
    process.mix.input.fileNames = cms.untracked.vstring(
#         "/store/relval/CMSSW_3_8_2/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_38Y_V9-v1/0019/A8606447-BFAF-DF11-940B-00304867900C.root",
#         "/store/relval/CMSSW_3_8_2/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_38Y_V9-v1/0018/B0DFBA95-93AF-DF11-A096-00248C0BE013.root",
#         "/store/relval/CMSSW_3_8_2/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_38Y_V9-v1/0017/9EBD3091-83AF-DF11-AB8B-003048678BAA.root",
#         "/store/relval/CMSSW_3_8_2/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_38Y_V9-v1/0017/8CFBF58C-82AF-DF11-AF7E-0026189438A2.root",
#         "/store/relval/CMSSW_3_8_2/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_38Y_V9-v1/0017/12D80D9C-85AF-DF11-9CB8-003048678F8A.root",
        "/store/relval/CMSSW_3_8_7/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_38Y_V13-v1/0017/82073890-93FC-DF11-8BF6-0030486790BA.root",
        "/store/relval/CMSSW_3_8_7/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_38Y_V13-v1/0016/748BCF89-8CFC-DF11-8C62-001A92810AD0.root",
        "/store/relval/CMSSW_3_8_7/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_38Y_V13-v1/0016/2A6588FE-8DFC-DF11-BA52-002354EF3BD2.root",
        "/store/relval/CMSSW_3_8_7/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_38Y_V13-v1/0016/2280CA87-8CFC-DF11-9800-00304867BF18.root",
        "/store/relval/CMSSW_3_8_7/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_38Y_V13-v1/0016/008B147B-8EFC-DF11-A90E-002354EF3BD2.root",
        )

process.RAWSIMEventContent.outputCommands.append("keep *_generator_*_*")
################## END ADDED BY HAND

process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.4 $'),
    annotation = cms.untracked.string('Configuration/Generator/PairGun100_cfg nevts:%d' % NUMBEROFEVENTS),
    name = cms.untracked.string('PyReleaseValidation')
)
process.maxEvents = cms.untracked.PSet(
    output = cms.untracked.int32(NUMBEROFEVENTS)
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
process.GlobalTag.globaltag = 'MC_38Y_V12::All'

### BEGIN EDITED BY HAND Nov 2010
process.simCsctfTrackDigis.SectorProcessor.initializeFromPSet = cms.bool(True)
# Force singles off
process.simCsctfTrackDigis.SectorProcessor.trigger_on_ME1a = cms.bool(False)
process.simCsctfTrackDigis.SectorProcessor.trigger_on_ME1b = cms.bool(False)
# Tighten maximum eta/phi differences for ghost cancellation logic as in
# https://twiki.cern.ch/twiki/bin/viewauth/CMS/CSCTFWindowStudies
process.simCsctfTrackDigis.SectorProcessor.mindetap = cms.uint32(7)
process.simCsctfTrackDigis.SectorProcessor.mindphip = cms.uint32(180)
process.simCsctfTrackDigis.SectorProcessor.EtaMin = cms.vuint32(0, 0, 0, 0, 0, 0, 0, 0)
### END EDITED BY HAND

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
