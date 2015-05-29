#!/bin/bash

mass=$1
ctau=$2

mkdir Submit_mass_${1}_ctau_${2}
cd Submit_mass_${1}_ctau_${2}


#=========================      cmsDriver configurations ===========================================//

cmsDriver.py DarkSUSY_cfi --mc --conditions MCRUN2_74_V9 --pileup 2015_25ns_Startup_PoissonOOTPU -s DIGI,L1,DIGI2RAW,HLT:@frozen25ns --datatier GEN-SIM-RAW --customise SLHCUpgradeSimulations/Configuration/postLS1Customs.customisePostLS1 --eventcontent RAWSIM --magField 38T_PostLS1 --fileout file:output.root -n 10 --no_exec

cat >> DarkSUSY_cfi_DIGI_L1_DIGI2RAW_HLT_PU.py <<EOF
# Automatic addition of the customisation function from MuJetAnalysis.GenProduction.addPileup                                                                                              
from MuJetAnalysis.GenProduction.addPileup import addPileup

#call to customisation function addPileup imported from MuJetAnalysis.GenProduction.addPileup                                                                                              
process = addPileup(process)
EOF

cmsDriver.py DarkSUSY_cfi --mc --conditions MCRUN2_74_V9 -s RAW2DIGI,L1Reco,RECO --datatier RECOSIM --customise SLHCUpgradeSimulations/Configuration/postLS1Customs.customisePostLS1 --eventcontent RECOSIM --magField 38T_PostLS1 --fileout file:output.root -n 10 --no_exec

#========================    CRAB submission scripts ====================================================//


cat > DIGI.cfg <<EOF
[SLURM]
queue		        = hepx
wnBase                  = /tmp
workernodebase          = /tmp

[CMSSW]
total_number_of_events   = -1
number_of_jobs           = 100
pset                     = DarkSUSY_cfi_DIGI_L1_DIGI2RAW_HLT_PU.py
use_dbs3                 = 1
dbs_url                  = phys03
datasetpath              = 
output_file              = output.root
allow_NonProductionCMSSW = 1


[USER]
thresholdLevel          = 80
return_data             = 0
copy_data               = 1
storage_element         = T3_US_TAMU
check_user_remote_dir   = 1
user_remote_dir         = DarkSUSY_mH_125_mGammaD_$1_13TeV_cT_$2_DIGI_L1_DIGI2RAW_HLT_PU_741p1_v1
ui_working_dir          = DarkSUSY_mH_125_mGammaD_$1_13TeV_cT_$2_DIGI_L1_DIGI2RAW_HLT_PU_741p1_v1
publish_data_name       = DarkSUSY_mH_125_mGammaD_$1_13TeV_cT_$2_DIGI_L1_DIGI2RAW_HLT_PU_741p1_v1
publish_data            = 1
dbs_url_for_publication = https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_01_writer/servlet/DBSServlet
srm_version 		= srmv2


[CRAB]
scheduler               = slurm
use_server              = 0
jobtype                 = cmssw

[GRID]
dont_check_proxy        = 1
rb                      = CERN
proxy_server            = fg-myproxy.fnal.gov
virtual_organization    = cms
se_white_list           = T3_US_TAMU
EOF

cat > RECO.cfg <<EOF

[SLURM]
queue		        = hepx
wnBase                  = /tmp
workernodebase          = /tmp

[CMSSW]
total_number_of_events   = -1
number_of_jobs           = 100
pset                     = DarkSUSY_cfi_RAW2DIGI_L1Reco_RECO.py
use_dbs3                 = 1
dbs_url                  = phys03
datasetpath              = 
output_file              = output.root
allow_NonProductionCMSSW = 1


[USER]
thresholdLevel          = 80
return_data             = 0
copy_data               = 1
storage_element         = T3_US_TAMU
check_user_remote_dir   = 1
user_remote_dir         = DarkSUSY_mH_125_mGammaD_$1_13TeV_cT_$2_RAW2DIGI_L1Reco_RECO_741p1_v1
ui_working_dir          = DarkSUSY_mH_125_mGammaD_$1_13TeV_cT_$2_RAW2DIGI_L1Reco_RECO_741p1_v1
publish_data_name       = DarkSUSY_mH_125_mGammaD_$1_13TeV_cT_$2_RAW2DIGI_L1Reco_RECO_741p1_v1
publish_data            = 1
dbs_url_for_publication = https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_01_writer/servlet/DBSServlet
srm_version 		= srmv2



[CRAB]
scheduler               = slurm
use_server              = 0
jobtype                 = cmssw

[GRID]
dont_check_proxy        = 1
rb                      = CERN
proxy_server            = fg-myproxy.fnal.gov
virtual_organization    = cms
se_white_list           = T3_US_TAMU
EOF



