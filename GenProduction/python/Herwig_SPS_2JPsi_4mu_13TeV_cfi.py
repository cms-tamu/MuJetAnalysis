from Configuration.Generator.HerwigppDefaults_cfi import *
from Configuration.Generator.HerwigppUE_EE_5C_cfi import *
from Configuration.Generator.HerwigppPDF_CTEQ6_LO_cfi import *
from Configuration.Generator.HerwigppEnergy_13TeV_cfi import *

generator = cms.EDFilter("ThePEGGeneratorFilter",
	herwigDefaultsBlock,
	herwigppUESettingsBlock,
	herwigppPDFSettingsBlock,
	herwigppEnergySettingsBlock,
	configFiles = cms.vstring(),
	parameterSets = cms.vstring(
		'hwpp_cmsDefaults',
		'hwpp_cm_13TeV',
		'hwpp_ue_EE5C',
		'hwpp_pdf_CTEQ6L1_Common',
		'processParameters',
	),


	processParameters = cms.vstring(
		
			#############
			### Copy here the content of the Herwig++ input card, each line must be in quotation marks and separated by a comma.

			###############
		
    'cd /Herwig/Generators',
    'set LHCGenerator:NumberOfEvents 100000',
    'set LHCGenerator:RandomNumberGenerator:Seed 31122001',
    'set LHCGenerator:DebugLevel 1',
    'set LHCGenerator:PrintEvent 10',
    'set LHCGenerator:MaxErrors 10000',                

##################################################
# Matrix Elements for hadron-hadron collisions    
# PLUGIN: gg -> Jpsi Jpsi                         
##################################################
    'cd /',
    'cd /Herwig/MatrixElements/',
    'library ./MEgg2JpsiJpsi.so',
    'create PLUGIN::MEgg2JpsiJpsi MEgg2JpsiJpsi',
    'set MEgg2JpsiJpsi:Lambda 0.92',
    'insert SimpleQCD:MatrixElements[0] MEgg2JpsiJpsi',

##################################################
# Change default parton level kinematic cuts
# (default in share/Herwig++/defaults/Cuts.in)
##################################################
     'set /Herwig/Cuts/MassCut:MinM 2.0*GeV',
     'set /Herwig/Cuts/MassCut:MaxM 6.0*GeV',
     'set /Herwig/Cuts/QCDCuts:MHatMin 0.0*GeV',
     'set /Herwig/Cuts/QCDCuts:MHatMax 1000.0*GeV',
     'set /Herwig/Cuts/QCDCuts:X1Min 1.0e-8',
     'set /Herwig/Cuts/QCDCuts:X2Min 1.0e-8',
     'set /Herwig/UnderlyingEvent/MPIHandler:IdenticalToUE 0',

################################################',
### Modify Jpsi properties in this file',
################################################',
    'cd /Herwig/Particles/',
################################################
### This is the default (so don't touch it !)
### setup Jpsi 443 Jpsi 3.096916 9.34E-5 0.000934 0 0 0 3 0
################################################

################################################
### Change Jpsi properties here
### setup Jpsi 443 Jpsi 3.0 9.34E-5 0.000934 0 0 0 3 0
################################################


    ############
    ## Change part above according to the Herwig++ input card
    
    
    ################


    ####################
    # Keep the part below since it switches off the other decay modes.

    ####################



################################################
### Jpsi decay modes below
### format:          'decaymode; BR (1:on, 0:0ff) DecayMethod
### Herwig default is to set all modes on
### here only the mu decay mode is switched on
################################################
    'decaymode Jpsi->mu-,mu+; 0.05935 1 /Herwig/Decays/Vector2Leptons',
#
    'decaymode Jpsi->g,g,g; 0.486225 0 /Herwig/Decays/QDecayME130',
    'decaymode Jpsi->u,ubar; 0.0791 0 /Herwig/Decays/QDecayME0',
    'decaymode Jpsi->e-,e+; 0.05935 0 /Herwig/Decays/Vector2Leptons',
    'decaymode Jpsi->g,g,gamma; 0.05 0 /Herwig/Decays/QDecayME130',
    'decaymode Jpsi->d,dbar; 0.0198 0 /Herwig/Decays/QDecayME0',
    'decaymode Jpsi->s,sbar; 0.0198 0 /Herwig/Decays/QDecayME0',
    'decaymode Jpsi->gamma,eta_c; 0.013 0 /Herwig/Decays/VectorVP',
    'decaymode Jpsi->omega,pi+,pi-,pi+,pi-; 0.0085 0 /Herwig/Decays/Mambo',
    'decaymode Jpsi->rho-,pi+; 0.00563 0 /Herwig/Decays/VectorVP',
    'decaymode Jpsi->rho0,pi0; 0.00563 0 /Herwig/Decays/VectorVP',
    'decaymode Jpsi->rho+,pi-; 0.00563 0 /Herwig/Decays/VectorVP',
    'decaymode Jpsi->gamma,pi+,pi-,pi0,pi0; 0.005 0 /Herwig/Decays/Mambo',
    'decaymode Jpsi->omega,pi+,pi-; 0.00475 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->gamma,eta\'; 0.00471 0 /Herwig/Decays/VectorVP',
    'decaymode Jpsi->n0,nbar0,pi+,pi-; 0.0045 0 /Herwig/Decays/Mambo',
    'decaymode Jpsi->p+,pbar-,pi+,pi-; 0.0045 0 /Herwig/Decays/Mambo',
    'decaymode Jpsi->f_2,omega; 0.0043 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->a_20,rho0; 0.003634 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->a_2-,rho+; 0.003633 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->a_2+,rho-; 0.003633 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->omega,pi+,pi-,pi0; 0.0036 0 /Herwig/Decays/Mambo',
    'decaymode Jpsi->K*-,K*_2+; 0.00335 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->K*bar0,K*_20; 0.00335 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->K*0,K*_2bar0; 0.00335 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->K*+,K*_2-; 0.00335 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->pi+,pi-,pi0; 0.0033 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->gamma,eta,pi+,pi-; 0.0031 0 /Herwig/Decays/Mambo',
    'decaymode Jpsi->gamma,rho+,rho-; 0.003 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->gamma,eta(1475); 0.0028 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->K-,K*+; 0.0023 0 /Herwig/Decays/VectorVP',
    'decaymode Jpsi->Kbar0,K*0; 0.0023 0 /Herwig/Decays/VectorVP',
    'decaymode Jpsi->K0,K*bar0; 0.0023 0 /Herwig/Decays/VectorVP',
    'decaymode Jpsi->K+,K*-; 0.0023 0 /Herwig/Decays/VectorVP',
    'decaymode Jpsi->p+,pbar-,pi+,pi-,pi0; 0.0023 0 /Herwig/Decays/Mambo',
    'decaymode Jpsi->omega,pi0,pi0; 0.00217 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->n0,nbar0; 0.00217 0 /Herwig/Decays/Vector2Leptons',
    'decaymode Jpsi->p+,pbar-; 0.00217 0 /Herwig/Decays/Vector2Leptons',
    'decaymode Jpsi->gamma,K+,K-,pi+,pi-; 0.0021 0 /Herwig/Decays/Mambo',
    'decaymode Jpsi->n0,nbar0,eta; 0.00209 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->p+,pbar-,eta; 0.00209 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->pbar-,n0,pi+; 0.00204 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->p+,nbar0,pi-; 0.00204 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->gamma,K*0,K*bar0; 0.002 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->gamma,K*+,K*-; 0.002 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->K\'_1-,K+; 0.0019 0 /Herwig/Decays/VAPDecayer',
    'decaymode Jpsi->K\'_1bar0,K0; 0.0019 0 /Herwig/Decays/VAPDecayer',
    'decaymode Jpsi->K\'_10,Kbar0; 0.0019 0 /Herwig/Decays/VAPDecayer',
    'decaymode Jpsi->K\'_1+,K-; 0.0019 0 /Herwig/Decays/VAPDecayer',
    'decaymode Jpsi->omega,eta; 0.00174 0 /Herwig/Decays/VectorVP',
    'decaymode Jpsi->phi,pi+,pi-,pi+,pi-; 0.00166 0 /Herwig/Decays/Mambo',
    'decaymode Jpsi->b_1-,pi+; 0.00162 0 /Herwig/Decays/VAPDecayer',
    'decaymode Jpsi->b_10,pi0; 0.00162 0 /Herwig/Decays/VAPDecayer',
    'decaymode Jpsi->b_1+,pi-; 0.00162 0 /Herwig/Decays/VAPDecayer',
    'decaymode Jpsi->gamma,eta,pi0,pi0; 0.0016 0 /Herwig/Decays/Mambo',
    'decaymode Jpsi->gamma,omega,omega; 0.00159 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->Lambda0,Lambdabar0; 0.00154 0 /Herwig/Decays/Vector2Leptons',
    'decaymode Jpsi->gamma,rho0,rho0; 0.0015 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->pi+,pi-; 0.00147 0 /Herwig/Decays/Vector2Meson',
    'decaymode Jpsi->gamma,f_2; 0.00138 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->gamma,f_0(1710); 0.00134 0 /Herwig/Decays/VVSDecayer',
    'decaymode Jpsi->omega,K*-,K+; 0.001325 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->omega,K*bar0,K0; 0.001325 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->omega,K*0,Kbar0; 0.001325 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->omega,K*+,K-; 0.001325 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->Sigma-,Sigmabar+; 0.00131 0 /Herwig/Decays/Vector2Leptons',
    'decaymode Jpsi->Sigma0,Sigmabar0; 0.00131 0 /Herwig/Decays/Vector2Leptons',
    'decaymode Jpsi->Sigma+,Sigmabar-; 0.00131 0 /Herwig/Decays/Vector2Leptons',
    'decaymode Jpsi->n0,nbar0,omega; 0.0013 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->p+,pbar-,omega; 0.0013 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->Delta-,Deltabar+; 0.0011 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->Delta0,Deltabar0; 0.0011 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->Delta+,Deltabar-; 0.0011 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->Delta++,Deltabar--; 0.0011 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->pbar-,K0,Sigma*+; 0.00102 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->pbar-,p+,pi0; 0.00102 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->nbar0,K+,Sigma*-; 0.00102 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->n0,nbar0,pi0; 0.00102 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->n0,K-,Sigma*bar+; 0.00102 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->p+,Kbar0,Sigma*bar-; 0.00102 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->gamma,pi+,pi-,pi+,pi-; 0.001 0 /Herwig/Decays/Mambo',
    'decaymode Jpsi->gamma,eta; 0.00098 0 /Herwig/Decays/VectorVP',
    'decaymode Jpsi->gamma,f_2,f_2; 0.00095 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->eta\',n0,nbar0; 0.0009 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->eta\',p+,pbar-; 0.0009 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->Xi-,Xibar+; 0.0009 0 /Herwig/Decays/Vector2Leptons',
    'decaymode Jpsi->Xi0,Xibar0; 0.0009 0 /Herwig/Decays/Vector2Leptons',
    'decaymode Jpsi->pbar-,K+,Lambda0; 0.00089 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->nbar0,K0,Lambda0; 0.00089 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->n0,Kbar0,Lambdabar0; 0.00089 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->p+,K-,Lambdabar0; 0.00089 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->phi,f\'_2; 0.0008 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->gamma,f\'_1; 0.00079 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->phi,pi+,pi-; 0.00078 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->f_0(1710),omega; 0.00076 0 /Herwig/Decays/VVSDecayer',
    'decaymode Jpsi->phi,eta; 0.00074 0 /Herwig/Decays/VectorVP',
    'decaymode Jpsi->phi,K0,Kbar0; 0.00074 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->phi,K+,K-; 0.00074 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->omega,K0,Kbar0; 0.00071 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->omega,K+,K-; 0.00071 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->omega,f\'_1; 0.00068 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->gamma,f_1; 0.00061 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->pbar-,K0,Sigma+; 0.00058 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->nbar0,K+,Sigma-; 0.00058 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->n0,K-,Sigmabar+; 0.00058 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->p+,Kbar0,Sigmabar-; 0.00058 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->gamma,f_0(1500); 0.00057 0 /Herwig/Decays/VVSDecayer',
    'decaymode Jpsi->f_0(1710),phi; 0.00057 0 /Herwig/Decays/VVSDecayer',
    'decaymode Jpsi->Sigmabar-,pi+,Lambda0; 0.00053 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->Sigmabar0,pi0,Lambda0; 0.00053 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->Sigmabar+,pi-,Lambda0; 0.00053 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->Sigma-,pi+,Lambdabar0; 0.00053 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->Sigma0,pi0,Lambdabar0; 0.00053 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->Sigma+,pi-,Lambdabar0; 0.00053 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->Sigma*-,Sigma*bar+; 0.000515 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->Sigma*0,Sigma*bar0; 0.000515 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->Sigma*+,Sigma*bar-; 0.000515 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->pbar-,K+,Sigma*0; 0.00051 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->nbar0,K0,Sigma*0; 0.00051 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->K-,K*+,phi; 0.00051 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->Kbar0,K*0,phi; 0.00051 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->K0,K*bar0,phi; 0.00051 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->K+,K*-,phi; 0.00051 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->n0,Kbar0,Sigma*bar0; 0.00051 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->p+,K-,Sigma*bar0; 0.00051 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->gamma,f\'_2; 0.00045 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->gamma,eta(1405); 0.00045 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->omega,pi0; 0.00045 0 /Herwig/Decays/VectorVP',
    'decaymode Jpsi->Xi*bar0,Xi0; 0.000446 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->Xi*bar+,Xi-; 0.000446 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->Xi*-,Xibar+; 0.000446 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->Xi*0,Xibar0; 0.000446 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->gamma,phi,phi; 0.0004 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->phi,eta\'; 0.0004 0 /Herwig/Decays/VectorVP',
    'decaymode Jpsi->gamma,n0,nbar0; 0.00038 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->gamma,p+,pbar-; 0.00038 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->phi,f_0; 0.00032 0 /Herwig/Decays/VVSDecayer',
    'decaymode Jpsi->pbar-,K+,Sigma0; 0.00029 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->nbar0,K0,Sigma0; 0.00029 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->n0,Kbar0,Sigmabar0; 0.00029 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->p+,K-,Sigmabar0; 0.00029 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->phi,f_1; 0.00026 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->K-,K+; 0.000237 0 /Herwig/Decays/Vector2Meson',
    'decaymode Jpsi->Lambda0,Lambdabar0,pi0; 0.00022 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->rho0,eta; 0.000193 0 /Herwig/Decays/VectorVP',
    'decaymode Jpsi->omega,eta\'; 0.000182 0 /Herwig/Decays/VectorVP',
    'decaymode Jpsi->Sigma*bar-,Sigma+; 0.000155 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->Sigma*bar0,Sigma0; 0.000155 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->Sigma*bar+,Sigma-; 0.000155 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->Sigma*-,Sigmabar+; 0.000155 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->Sigma*0,Sigmabar0; 0.000155 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->Sigma*+,Sigmabar-; 0.000155 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->K_L0,K_S0; 0.000146 0 /Herwig/Decays/Vector2Meson',
    'decaymode Jpsi->omega,f_0; 0.00014 0 /Herwig/Decays/VVSDecayer',
    'decaymode Jpsi->rho0,eta\'; 0.000105 0 /Herwig/Decays/VectorVP',
    'decaymode Jpsi->phi,n0,nbar0; 4.5E-5 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->phi,p+,pbar-; 4.5E-5 0 /Herwig/Decays/DecayME0',
    'decaymode Jpsi->gamma,pi0; 3.3E-5 0 /Herwig/Decays/VectorVP',

##################################################
# Save run for later usage with 'Herwig++ run'
##################################################
     'cd /Herwig/Generators',
     'saverun LHC-SSDJpsi LHCGenerator'
    ),

    crossSection = cms.untracked.double(2.0e+10),
    filterEfficiency = cms.untracked.double(1.0),
)
