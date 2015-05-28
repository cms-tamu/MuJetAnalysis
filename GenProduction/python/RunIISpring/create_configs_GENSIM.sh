#!/bin/bash

mass=$1
ctau=$2

mkdir Submit_mass_${1}_ctau_${2}
cd Submit_mass_${1}_ctau_${2}


#=========================      cmsDriver configurations ===========================================//

cmsDriver.py MuJetAnalysis/GenProduction/Pythia8HadronizerFilter_13TeV_cfi --step GEN,SIM --mc --eventcontent RAWSIM --datatier GEN-SIM --conditions MCRUN2_71_V1::All --customise SLHCUpgradeSimulations/Configuration/postLS1Customs.customisePostLS1 --beamspot NominalCollision2015 --magField 38T_PostLS1 --python_filename DarkSUSY_mH_125_mGammaD_$1_13TeV_cT_$2_madgraph452_bridge224_LHE_pythia8_cfi_GEN-SIM.py --filetype LHE --filein file:DarkSUSY_mH_125_mGammaD_$1_13TeV_cT_$2_madgraph452_bridge224_events80k.lhe --fileout file:output.root -n 10 --no_exec

#========================    CRAB submission scripts ====================================================//

cat > GEN.cfg     <<EOF
[CRAB]
jobtype     = cmssw
scheduler   = slurm
use_server  = 0

[SLURM]
queue		        = hepx
wnBase                  = /tmp
workernodebase          = /tmp


[GRID]
dont_check_proxy     = 1
rb                   = CERN
proxy_server         = fg-myproxy.fnal.gov
virtual_organization = cms
se_white_list        = T3_US_TAMU


[CMSSW]
pset        = DarkSUSY_mH_125_mGammaD_${1}_13TeV_cT_${2}_madgraph452_bridge224_LHE_pythia8_cfi_GEN-SIM.py
output_file = output.root
datasetpath = None
generator   = lhe
total_number_of_events = 80000
number_of_jobs         = 100

[USER]
thresholdLevel          = 80
email                   = amch031182@gmail.com
copy_data               = 1
return_data             = 0
storage_element         = T3_US_TAMU
additional_input_files  = DarkSUSY_mH_125_mGammaD_$1_13TeV_cT_$2_madgraph452_bridge224_events80k.lhe
user_remote_dir         = DarkSUSY_mH_125_mGammaD_$1_13TeV_cT_$2_madgraph452_bridge224_LHE_pythia8_7115p1_GEN-SIM_v1
ui_working_dir          = DarkSUSY_mH_125_mGammaD_$1_13TeV_cT_$2_madgraph452_bridge224_LHE_pythia8_7115p1_GEN-SIM_v1
publish_data_name       = DarkSUSY_mH_125_mGammaD_$1_13TeV_cT_$2_madgraph452_bridge224_LHE_pythia8_7115p1_GEN-SIM_v1
publish_data            = 1
dbs_url_for_publication = https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_01_writer/servlet/DBSServlet
srm_version 		= srmv2
EOF

