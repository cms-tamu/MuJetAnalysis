## Pythia8 fragment for 14TeV collisions
import FWCore.ParameterSet.Config as cms

from Configuration.Generator.PythiaUEZ2starSettings_cfi import *

generator = cms.EDFilter("Pythia6HadronizerFilter",
    pythiaPylistVerbosity = cms.untracked.int32(0),
    # put here the efficiency of your filter (1. if no filter)
    filterEfficiency = cms.untracked.double(1.0),
    pythiaHepMCVerbosity = cms.untracked.bool(False),
    # put here the cross section of your process (in pb)
    crossSection = cms.untracked.double(1.0),
    maxEventsToPrint = cms.untracked.int32(0),
    # Center-of-mass Energy
    comEnergy = cms.double(14000.0),
    PythiaParameters = cms.PSet(
        pythiaUESettingsBlock,
        processParameters = cms.vstring(
             'MSEL=0          ! User defined processes'
        ),
        parameterSets = cms.vstring(
            'pythiaUESettings',
            'processParameters'
        )
    )
)
