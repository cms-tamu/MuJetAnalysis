# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: MuJetAnalysis/GenProduction/Pythia8GeneratorFilter_DPS_2JPsi_4mu_13TeV_cfi -s GEN,SIM --mc --datatier GEN-SIM --beamspot Realistic25ns13TeV2016Collision --conditions 80X_mcRun2_asymptotic_2016_miniAODv2_v1 --eventcontent RAWSIM --era Run2_2016 --customise MuJetAnalysis/GenProduction/filter_2JPsi_4mu_cfi.filter_2JPsi_Pt3_4mu --python_filename DPS_2JPsi_Pt3_4mu_13TeV_pythia8_cfi_GEN_SIM.py --fileout out_sim.root -n 10 --no_exec
import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('SIM',eras.Run2_2016)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.Geometry.GeometrySimDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic25ns13TeV2016Collision_cfi')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10)
)

# Input source
process.source = cms.Source("EmptySource")

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('MuJetAnalysis/GenProduction/Pythia8GeneratorFilter_DPS_2JPsi_4mu_13TeV_cfi nevts:10'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.RAWSIMoutput = cms.OutputModule("PoolOutputModule",
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    ),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM'),
        filterName = cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    fileName = cms.untracked.string('out_sim.root'),
    outputCommands = process.RAWSIMEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

# Additional output definition

# Other statements
process.genstepfilter.triggerConditions=cms.vstring("generation_step")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '80X_mcRun2_asymptotic_2016_miniAODv2_v1', '')

process.generator = cms.EDFilter("Pythia8GeneratorFilter",
    PythiaParameters = cms.PSet(
        parameterSets = cms.vstring('pythia8CommonSettings', 
            'pythia8CUEP8M1Settings', 
            'processParameters'),
        processParameters = cms.vstring('Main:timesAllowErrors = 10000', 
            'Charmonium:all = on', 
            'PartonLevel:MPI = on', 
            'SecondHard:generate = on', 
            'SecondHard:Charmonium = on', 
            'PhaseSpace:pTHatMin = 3.0', 
            'PhaseSpace:pTHatMinSecond = 3.0', 
            'PhaseSpace:pTHatMinDiverge = 0.5', 
            '443:onMode = off', 
            '443:onIfAny = -13 13', 
            '445:onMode    = off', 
            '445:onIfAny   = 443 22', 
            '10441:onMode  = off', 
            '10441:onIfAny = 443 22', 
            '20443:onMode  = off', 
            '20443:onIfAny = 443 22', 
            '9940003:onMode = off', 
            '9940003:onIfAny = 443 21', 
            '9940005:onMode = off', 
            '9940005:onIfAny = 445 21', 
            '9940011:onMode = off', 
            '9940011:onIfAny = 10441 21', 
            '9940023:onMode = off', 
            '9940023:onIfAny = 20443 21', 
            '9941003:onMode = off', 
            '9941003:onIfAny = 443 21', 
            '9942003:onMode = off', 
            '9942003:onIfAny = 443 21'),
        pythia8CUEP8M1Settings = cms.vstring('Tune:pp 14', 
            'Tune:ee 7', 
            'MultipartonInteractions:pT0Ref=2.4024', 
            'MultipartonInteractions:ecmPow=0.25208', 
            'MultipartonInteractions:expPow=1.6'),
        pythia8CommonSettings = cms.vstring('Tune:preferLHAPDF = 2', 
            'Main:timesAllowErrors = 10000', 
            'Check:epTolErr = 0.01', 
            'Beams:setProductionScalesFromLHEF = off', 
            'SLHA:keepSM = on', 
            'SLHA:minMassSM = 1000.', 
            'ParticleDecays:limitTau0 = on', 
            'ParticleDecays:tau0Max = 10', 
            'ParticleDecays:allowPhotonRadiation = on')
    ),
    comEnergy = cms.double(13000.0),
    crossSection = cms.untracked.double(0.0001755),
    filterEfficiency = cms.untracked.double(0.000416),
    maxEventsToPrint = cms.untracked.int32(1),
    pythiaHepMCVerbosity = cms.untracked.bool(True),
    pythiaPylistVerbosity = cms.untracked.int32(1)
)


# Path and EndPath definitions
process.generation_step = cms.Path(process.pgen)
process.simulation_step = cms.Path(process.psim)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RAWSIMoutput_step = cms.EndPath(process.RAWSIMoutput)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.genfiltersummary_step,process.simulation_step,process.endjob_step,process.RAWSIMoutput_step)
# filter all path with the production filter sequence
for path in process.paths:
	getattr(process,path)._seq = process.generator * getattr(process,path)._seq 

# customisation of the process.

# Automatic addition of the customisation function from MuJetAnalysis.GenProduction.filter_2JPsi_4mu_cfi
from MuJetAnalysis.GenProduction.filter_2JPsi_4mu_cfi import filter_2JPsi_Pt3_4mu 

#call to customisation function filter_2JPsi_Pt3_4mu imported from MuJetAnalysis.GenProduction.filter_2JPsi_4mu_cfi
process = filter_2JPsi_Pt3_4mu(process)

# End of customisation functions

