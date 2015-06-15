#!/usr/bin/expect -f

#This script should be run after the DIGI-HLT-PU jobs have completed.  This script will take care of getting and publishing the DIGI-PU output, and creating and submitting the RAW2DIGI, L1Reco, RECO  CRAB jobs.

#1. Make sure that DIGI2RAW_RECO exists inside of CMSSW_7_4_1_patch1/src/MuJetAnalysis
#2. Change file paths and lifetimes as necessary.

set timeout 86400

send_user "Brazos Username: "
expect_user -re "(.*)\n" {set USER $expect_out(1,string)}

stty -echo
send_user "Brazos Password: "
expect_user -re "(.*)\n" {set BRAZOS_PASSWORD $expect_out(1,string)}

stty -echo
send_user "GRID Password: "
expect_user -re "(.*)\n" {set PASSWORD $expect_out(1,string)}


send_user "mGammaD GeV (XXXX): "
#ie: 2000 for 2.000 GeV, 0275 for 0.275 GeV
expect_user -re "(.*)\n" {set mGammaD $expect_out(1,string)}

set lifetimes [list 000 005 010 020 050 100 200 300 500] 
#005 010 020 050 100] 
#200 300 500] 
# 000 005 010 020 050 100 200 300 500] 
#000] 
#005 010 020 050 100 200 300 500]

spawn ssh -X -Y $USER@login02.brazos.tamu.edu
expect "$USER@login02.brazos.tamu.edu's password: "
send "$BRAZOS_PASSWORD\r"

foreach CT $lifetimes {
	expect "$ ";
	send "cd /home/$USER/CMSSW_7_4_1_patch1/src\r";
	expect "$ ";
	send "cd /home/$USER/CMSSW_7_4_1_patch1/src\r";
	expect "$ ";
	send "cmsenv \r";
	expect "$ ";
	send "getcert1 \r";
	expect {
		"Enter GRID pass phrase:" {send "$PASSWORD\r"}
	}
	expect "$ ";
	send "getcert2\r";
	expect "$ ";
	send "setupcrab\r";
	expect "$ ";
	send "cmsenv\r";
	expect "$ ";
	send "cd /home/$USER/CMSSW_7_4_1_patch1/src/MuJetAnalysis/DIGI_PU \r";
	expect "$ ";

	send "crab -status -c DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_DIGI_L1_DIGI2RAW_HLT_PU_MCRUN2_74_V9_v1 \r";
	expect {
		"Enter GRID pass phrase:" {send "$PASSWORD\r"}
	}

	expect "$ ";
	send "crab -getoutput -c DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_DIGI_L1_DIGI2RAW_HLT_PU_MCRUN2_74_V9_v1 \r";
	#	set timeout 20;
	#expect {
#		"Enter GRID pass phrase:" {send "$PASSWORD\r"}
#	} 
#set timeout 86400;
	expect "$ ";
	send "crab -publish -c DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_DIGI_L1_DIGI2RAW_HLT_PU_MCRUN2_74_V9_v1 > DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_DIGI_L1_DIGI2RAW_HLT_PU_MCRUN2_74_V9_v1.txt \r";
	expect "$ ";
	send "sed -i '/to publish in dataset/!d' DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_DIGI_L1_DIGI2RAW_HLT_PU_MCRUN2_74_V9_v1.txt \r";
	expect "$ ";
	send "sed -i 's/dataset/\\n/g' DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_DIGI_L1_DIGI2RAW_HLT_PU_MCRUN2_74_V9_v1.txt \r";
	expect "$ ";
	send "sed -i '/DarkSUSY/!d' DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_DIGI_L1_DIGI2RAW_HLT_PU_MCRUN2_74_V9_v1.txt \r";
	expect "$ ";
#At this point, I have the GEN-SIM datapath inside of the file above located in  cd /home/$USER/CMSSW_7_1_15/src/MuJetAnalysis/GEN_SIM.
#Now, I need to go in to the CMSSW 741p1 directory, reset cmsenv, and create the necessary python script.
	send "cd ..\r";
	expect "$ ";
	send "cd RAW2DIGI_RECO \r";
	sleep 5;
	expect "$ ";
	send "cmsDriver.py DisplacedMuJet_Run2_cfi -s RAW2DIGI,L1Reco,RECO --datatier RECO --conditions MCRUN2_74_V9 --magField 38T_PostLS1 --eventcontent RECOSIM --customise=SLHCUpgradeSimulations/Configuration/postLS1Customs.customisePostLS1 --fileout out_reco.root -n 10 --no_exec \r";
	sleep 5;
	expect "$ ";
	send "mv DisplacedMuJet_Run2_cfi_RAW2DIGI_L1Reco_RECO.py RAW2DIGI_L1Reco_RECO_MCRUN2_74_V9_cfg.py \r";	
	expect "$ ";
	send "cp ../RAW2DIGI_RECO_Test/DarkSUSY_mH_125_mGammaD_0850_13TeV_cT_000_DIGI_L1_DIGI2RAW_HLT_PU_MCRUN2_74_V9_v1.CRAB.cfg . \r";
	expect "$ ";
	send "mv DarkSUSY_mH_125_mGammaD_0850_13TeV_cT_000_DIGI_L1_DIGI2RAW_HLT_PU_MCRUN2_74_V9_v1.CRAB.cfg DarkSUSY_mH_125_mGammaD_$mGammaD\_13TeV_cT_$CT\_DIGI_L1_DIGI2RAW_HLT_PU_MCRUN2_74_V9_v1.CRAB.cfg \r";
	expect "$ ";
	send "sed -i '/pset/c\pset        = RAW2DIGI_L1Reco_RECO_MCRUN2_74_V9_cfg.py' DarkSUSY_mH_125_mGammaD_$mGammaD\_13TeV_cT_$CT\_DIGI_L1_DIGI2RAW_HLT_PU_MCRUN2_74_V9_v1.CRAB.cfg \r";
	expect "$ ";
	send "sed -i '/datasetpath/c\datasetpath              = asdfasdf_to_be_replaced_by_datasetpath' DarkSUSY_mH_125_mGammaD_$mGammaD\_13TeV_cT_$CT\_DIGI_L1_DIGI2RAW_HLT_PU_MCRUN2_74_V9_v1.CRAB.cfg \r";
	expect "$ ";
	send "sed -i '/user_remote_dir/c\user_remote_dir         = DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_RAW2DIGI_L1Reco_RECO_MCRUN2_74_V9_v1' DarkSUSY_mH_125_mGammaD_$mGammaD\_13TeV_cT_$CT\_DIGI_L1_DIGI2RAW_HLT_PU_MCRUN2_74_V9_v1.CRAB.cfg \r";
	expect "$ ";
	send "sed -i '/ui_working_dir/c\ui_working_dir          = DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_RAW2DIGI_L1Reco_RECO_MCRUN2_74_V9_v1' DarkSUSY_mH_125_mGammaD_$mGammaD\_13TeV_cT_$CT\_DIGI_L1_DIGI2RAW_HLT_PU_MCRUN2_74_V9_v1.CRAB.cfg \r";
	expect "$ ";
	send "sed -i '/publish_data_name/c\publish_data_name       = DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_RAW2DIGI_L1Reco_RECO_MCRUN2_74_V9_v1' DarkSUSY_mH_125_mGammaD_$mGammaD\_13TeV_cT_$CT\_DIGI_L1_DIGI2RAW_HLT_PU_MCRUN2_74_V9_v1.CRAB.cfg \r";
	expect "$ ";
	#############
	send "sed -i \"s/asdfasdf_to_be_replaced_by_datasetpath/\$(sed 's:\/:\\\\\/:g' /home/$USER/CMSSW_7_4_1_patch1/src/MuJetAnalysis/DIGI_PU/DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_DIGI_L1_DIGI2RAW_HLT_PU_MCRUN2_74_V9_v1.txt)/\" DarkSUSY_mH_125_mGammaD_$mGammaD\_13TeV_cT_$CT\_DIGI_L1_DIGI2RAW_HLT_PU_MCRUN2_74_V9_v1.CRAB.cfg \r";
	sleep 5;
	expect "$ ";
	send "crab -create -cfg DarkSUSY_mH_125_mGammaD_$mGammaD\_13TeV_cT_$CT\_DIGI_L1_DIGI2RAW_HLT_PU_MCRUN2_74_V9_v1.CRAB.cfg \r";	
	sleep 5;
	expect {
		"Enter GRID pass phrase:" {send "$PASSWORD\r"}
	}
	sleep 10;
	expect "$ ";
	sleep 10;	
	send "crab -submit -c DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_RAW2DIGI_L1Reco_RECO_MCRUN2_74_V9_v1 \r";
	sleep 10;
}
