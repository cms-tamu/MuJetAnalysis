# NMSSM Hto2Ato4mu 13TeV pythia8 configuration file
import FWCore.ParameterSet.Config as cms
from Configuration.Generator.Pythia8CommonSettings_cfi import *
from Configuration.Generator.Pythia8CUEP8M1Settings_cfi import *

process = cms.Process('GEN')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic8TeVCollision_cfi')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
	input = cms.untracked.int32(20000)
)

# Input source
process.source = cms.Source("EmptySource")

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
	version = cms.untracked.string('$Revision: 1.381.2.13 $'),
	annotation = cms.untracked.string('Configuration/GenProduction/python/EightTeV/MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_cfi.py nevts:10'),
	name = cms.untracked.string('PyReleaseValidation')
)

# Output definition
process.RECOSIMoutput = cms.OutputModule("PoolOutputModule",
	splitLevel = cms.untracked.int32(0),
	eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
	outputCommands = process.RECOSIMEventContent.outputCommands,
	fileName = cms.untracked.string('NMSSM_Hto2Ato4mu_mH_125_mA_2000_13TeV-pythia8_731p2_GEN_WorkAround.root'),
	dataset = cms.untracked.PSet(
		filterName = cms.untracked.string(''),
		dataTier = cms.untracked.string('GEN'),
	),
	SelectEvents = cms.untracked.PSet(
		SelectEvents = cms.vstring('generation_step'),
	),
)

# Additional output definition

# Other statements
process.genstepfilter.triggerConditions=cms.vstring("generation_step")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:startup', '')

process.generator = cms.EDFilter("Pythia8GeneratorFilter",
	pythiaPylistVerbosity = cms.untracked.int32(1),
	filterEfficiency = cms.untracked.double(1.0),
	pythiaHepMCVerbosity = cms.untracked.bool(False),
	comEnergy = cms.double(13000.0),
	crossSection = cms.untracked.double(1.0),
	maxEventsToPrint = cms.untracked.int32(1000),
	PythiaParameters = cms.PSet(
		pythia8CommonSettingsBlock,
		pythia8CUEP8M1SettingsBlock,
		pythiaUESettings = cms.vstring(),

		processParameters = cms.vstring(
			# This section should be entirely in Pythia 8. See details in
			#   - http://home.thep.lu.se/~torbjorn/pythia82html/HiggsProcesses.html
			#   - http://home.thep.lu.se/~torbjorn/pythia82html/ParticleDataScheme.html
			'Higgs:useBSM = on',
			'HiggsBSM:all = off',    # Switch off all BSM Higgs production
			'HiggsBSM:gg2H2 = on',
			'35:m0 = 90',
			#'35:mMin = 50.',

			'35:addChannel 1 0.01 100 54 54', 
			'35:onMode = off',
			'35:onIfMatch = 54 54',

			'54:isResonance = false',
			'54:mWidth = 0',
			'54:m0 = 0.25',
			'54:onMode = off',
			'54:onIfMatch = 13 -13',

			#'Higgs:useBSM = on',     # Initialize and use the two-Higgs-doublet BSM states
			#'HiggsBSM:all = off',    # Switch off all BSM Higgs production
			#'HiggsBSM:gg2H2 = on',   # Switch on gg->H^0(H_2^0) scattering via loop contributions primarily from top. Code 1022. 
			#'35:m0 = 90.0',         #  mass in GeV of H0 (PDG ID = 35)
			#'36:m0 = 0.5',           #  mass in GeV of A0 (PDG ID = 36)
			# decays of H0 (PDG ID = 35)
			#'35:onMode = off',       # Turn off all H0 decay modes 
			#'35:onIfMatch = 36 36',  # Allow H0 decays to A0: H0 ->A0A0
			# decays of A0 (PDG ID = 36)
			#'36:onMode = off',       # Turn off all A0 decay modes
			#'36:onIfMatch = 13 -13', # Allow A0 decays to muons: A0 ->mu+mu-
			# Useful debug printouts
			'Init:showProcesses = on',        # Print a list of all processes that will be simulated, with their estimated cross section maxima
			'Init:showChangedSettings = on',  # Print a list of the changed flag/mode/parameter/word setting
			#'Init:showAllParticleData = on', # Print a list of all particle and decay data. Warning: this will be a long list
	),
		parameterSets = cms.vstring('pythiaUESettings', 
			'pythia8CommonSettings',
			'pythia8CUEP8M1Settings',
			'processParameters')
 )
)

# Path and EndPath definitions
process.generation_step = cms.Path(process.pgen)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RECOSIMoutput_step = cms.EndPath(process.RECOSIMoutput)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.genfiltersummary_step,process.endjob_step,process.RECOSIMoutput_step)
# filter all path with the production filter sequence
for path in process.paths:
	getattr(process,path)._seq = process.generator * getattr(process,path)._seq
