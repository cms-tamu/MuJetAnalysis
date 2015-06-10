#!/usr/bin/expect -f

#To run this script you must:
#1. Download desired DarkSusySamples (lhe files) from github and place them in your equivalent of /home/bmichlin/CMSSW_7_1_15/src 
#2. Rename MuJetAnalysis_DarkSusySamples_LHE_13TeV_XX to MuJetAnalysis_DarkSusySamples_LHE_13TeV (merge directories if necessary)
#3. May need to change number of events in file name (if different than 80k).  Easiest way is with a search and replace. 
#4. May need to replace path to working directory if different from /home/bmichlin/CMSSW_7_1_15/src/ .  Easiest way is with a search and replace.
#5. May also need to change lifetimes (as desired) on line 30

set timeout 86400

send_user "Brazos Username: "
expect_user -re "(.*)\n" {set USER $expect_out(1,string)}

stty -echo
send_user "Brazos Password: "
expect_user -re "(.*)\n" {set PASSWORD $expect_out(1,string)}

tty -echo
send_user "GRID Password: "
expect_user -re "(.*)\n" {set GRIDPASSWORD $expect_out(1,string)}


send_user "mGammaD GeV (XXXX): "
#ie: 2000 for 2.000 GeV, 0275 for 0.275 GeV
expect_user -re "(.*)\n" {set mGammaD $expect_out(1,string)}



set lifetimes [list 000 005 010 020 050 100 200 300 500]
# These are the liftimes used formated as X.XX mm (e.g.: 010 === 0.10 mm)

spawn ssh -X -Y $USER@login02.brazos.tamu.edu
expect "$USER@login02.brazos.tamu.edu's password: "
send "$PASSWORD\r"
expect "$ "
send "cd /home/bmichlin/CMSSW_7_1_15/src\r"
expect "$ "
send "cd MuJetAnalysis_DarkSusySamples_LHE_13TeV/DarkSUSY_mH_125/mGammaD_$mGammaD \r"

foreach CT $lifetimes {
	expect "$ ";
	send "cd cT_$CT \r";	
	expect "$ ";
	send "tar -zxvf DarkSUSY_mH_125_mGammaD_$mGammaD\_13TeV_cT_$CT\_madgraph452_bridge224_events80k.lhe.tar.gz \r";
	expect "$ ";
	send "mv *.lhe DarkSUSY_mH_125_mGammaD_$mGammaD\_13TeV_cT_$CT\_madgraph452_bridge224_events80k.lhe \r";
	expect "$ ";
	send "cd /home/bmichlin/CMSSW_7_1_15/src\r";	
	expect "$ ";
	send "cmsenv \r";
	expect "$ ";
	send "getcert1 \r";
	#expect "Enter GRID pass phrase:";
	#send "$GRIDPASSWORD\r";
	expect { 
		"Enter GRID pass phrase:" {send "$GRIDPASSWORD\r"}
	}
	expect "$ ";
	send "getcert2\r";
	expect "$ ";
	send "setupcrab\r";
	expect "$ ";
	send "cmsenv\r";
	expect "$ ";
	send "cd /home/bmichlin/CMSSW_7_1_15/src/MuJetAnalysis/GEN_SIM \r";	
	expect "$ ";
	send "cmsDriver.py MuJetAnalysis/GenProduction/Pythia8HadronizerFilter_13TeV_cfi -s GEN,SIM --mc --datatier GEN-SIM --beamspot NominalCollision2015 --conditions MCRUN2_71_V1::All --magField 38T_PostLS1 --eventcontent RAWSIM --customise=SLHCUpgradeSimulations/Configuration/postLS1Customs.customisePostLS1 --python_filename DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_madgraph452_bridge224_LHE_pythia8_cfi_GEN_SIM.py --filetype LHE --filein file:/home/bmichlin/CMSSW_7_1_15/src/MuJetAnalysis_DarkSusySamples_LHE_13TeV/DarkSUSY_mH_125/mGammaD_$mGammaD/cT_$CT/DarkSUSY_mH_125_mGammaD_$mGammaD\_13TeV_cT_$CT\_madgraph452_bridge224_events80k.lhe --fileout out_sim.root -n 10 --no_exec \r";
	sleep 10;
	expect "$ ";
	send "cp ../GEN_SIM_TEST/DarkSUSY_mH_125_mGammaD_0850_13TeV_madgraph452_bridge224_events80k_LHE_pythia8_cfi_GEN_SIM_v1.CRAB.cfg . \r";
	expect "$ ";
	send "mv DarkSUSY_mH_125_mGammaD_0850_13TeV_madgraph452_bridge224_events80k_LHE_pythia8_cfi_GEN_SIM_v1.CRAB.cfg DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_madgraph452_bridge224_events80k_LHE_pythia8_cfi_GEN_SIM_v1.CRAB.cfg \r";
	expect "$ ";
	send "sed -i '/pset/c\pset        = DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_madgraph452_bridge224_LHE_pythia8_cfi_GEN_SIM.py' DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_madgraph452_bridge224_events80k_LHE_pythia8_cfi_GEN_SIM_v1.CRAB.cfg \r";	
	expect "$ ";
	send "sed -i '/additional_input_files/c\additional_input_files  = /home/bmichlin/CMSSW_7_1_15/src/MuJetAnalysis_DarkSusySamples_LHE_13TeV/DarkSUSY_mH_125/mGammaD_$mGammaD/cT_$CT/DarkSUSY_mH_125_mGammaD_$mGammaD\_13TeV_cT_$CT\_madgraph452_bridge224_events80k.lhe' DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_madgraph452_bridge224_events80k_LHE_pythia8_cfi_GEN_SIM_v1.CRAB.cfg \r";	
	expect "$ ";
	send "sed -i '/user_remote_dir/c\user_remote_dir         = DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1' DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_madgraph452_bridge224_events80k_LHE_pythia8_cfi_GEN_SIM_v1.CRAB.cfg \r";
	expect "$ ";
	send "sed -i '/ui_working_dir/c\ui_working_dir          = DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1' DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_madgraph452_bridge224_events80k_LHE_pythia8_cfi_GEN_SIM_v1.CRAB.cfg \r";
	expect "$ ";
	send "sed -i '/publish_data_name/c\publish_data_name       = DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1' DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_madgraph452_bridge224_events80k_LHE_pythia8_cfi_GEN_SIM_v1.CRAB.cfg \r";
	expect "$ ";
	send "crab -create -cfg DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_madgraph452_bridge224_events80k_LHE_pythia8_cfi_GEN_SIM_v1.CRAB.cfg \r";
	sleep 10;
	#expect "Enter GRID pass phrase:";
	#send "$GRIDPASSWORD
	expect {
		"Enter GRID pass phrase:" {send "$GRIDPASSWORD\r"}
	}
	sleep 10;
	expect "$ ";
	sleep 2;
	send "crab -submit -c DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1 \r";	
	expect "$ ";
	send "cd /home/bmichlin/CMSSW_7_1_15/src/MuJetAnalysis_DarkSusySamples_LHE_13TeV/DarkSUSY_mH_125/mGammaD_$mGammaD \r";
	expect "$ ";
	send "cd /home/bmichlin/CMSSW_7_1_15/src/MuJetAnalysis_DarkSusySamples_LHE_13TeV/DarkSUSY_mH_125/mGammaD_$mGammaD \r";
	sleep 1;
}

exit
