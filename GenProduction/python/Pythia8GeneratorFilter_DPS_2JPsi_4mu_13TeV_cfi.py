import FWCore.ParameterSet.Config as cms

from Configuration.Generator.Pythia8CommonSettings_cfi import *
from Configuration.Generator.Pythia8CUEP8M1Settings_cfi import *

generator = cms.EDFilter("Pythia8GeneratorFilter",
   crossSection = cms.untracked.double(1.755e-04),  
   maxEventsToPrint = cms.untracked.int32(1),
   pythiaPylistVerbosity = cms.untracked.int32(1),
   filterEfficiency = cms.untracked.double(0.000416),
   pythiaHepMCVerbosity = cms.untracked.bool(True),
   comEnergy = cms.double(13000.0),
   PythiaParameters = cms.PSet(
   pythia8CommonSettingsBlock,
   pythia8CUEP8M1SettingsBlock,
   processParameters = cms.vstring(
           'Main:timesAllowErrors = 10000',
           'Charmonium:all = on', # turn on charmonium production
#!           'PartonLevel:MI = on', # worked before Pythia 8.20
           'PartonLevel:MPI = on', # works since Pythia 8.20
           'SecondHard:generate = on',
           'SecondHard:Charmonium = on',
           # Modify phase-space for pTHat
           'PhaseSpace:pTHatMin = 3.0',
           'PhaseSpace:pTHatMinSecond = 3.0',
           'PhaseSpace:pTHatMinDiverge = 0.5',
           # Allow Jpsi-->2mu only:
           '443:onMode = off',
           '443:onIfAny = -13 13',
           # Modify Singlet decays:
           '445:onMode    = off',    # turn off all chi_2c decays 
           '445:onIfAny   = 443 22', # turn on chi_2c --> Jpsi+gamma (bRatio="0.2020000")
           '10441:onMode  = off',    # chi_0c
           '10441:onIfAny = 443 22', # turn on chi_0c --> Jpsi+gamma (bRatio="0.0200000")
           '20443:onMode  = off',    # chi_1c
           '20443:onIfAny = 443 22', # turn on chi_1c --> Jpsi+gamma (bRatio="0.3560000")
           # Modify Octet decays (worked before Pythia 8.20)
#!           '9900443:onMode = off', # ccbar[3S1(8)]
#!           '9900443:onIfAny = 443 21',                                  
#!           '9900441:onMode = off', # ccbar[1S0(8)]
#!           '9900441:onIfAny = 443 21',                                  
#!           '9910441:onMode = off', # ccbar[3P0(8)]
#!           '9910441:onIfAny = 443 21',
           # Modify Octet decays (works since Pythia 8.20):
           '9940003:onMode = off', # J/psi[3S1(8)]
           '9940003:onIfAny = 443 21',
           '9940005:onMode = off', # chi_2c[3S1(8)]
           '9940005:onIfAny = 445 21',
           '9940011:onMode = off', # chi_0c[3S1(8)]
           '9940011:onIfAny = 10441 21',
           '9940023:onMode = off', # chi_1c[3S1(8)]
           '9940023:onIfAny = 20443 21',
           '9941003:onMode = off', # J/psi[1S0(8)]
           '9941003:onIfAny = 443 21',
           '9942003:onMode = off', # J/psi[3PJ(8)]
           '9942003:onIfAny = 443 21',
       ),
       parameterSets = cms.vstring('pythia8CommonSettings',
                                   'pythia8CUEP8M1Settings',
                                   'processParameters')
   )
)
