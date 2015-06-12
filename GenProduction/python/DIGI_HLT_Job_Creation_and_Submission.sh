#!/usr/bin/expect -f

#This script should be run after the GEN-SIM jobs have completed.  This script will take care of getting and publishing the GEN-SIM output, and creating and submitting the DIGI,L1,DIGI2RAW,HLT,PU CRAB jobs.

#1. Make sure that DIGI_PU exists inside of CMSSW_7_4_1_patch1/src/MuJetAnalysis
#2. Make sure that the directory paths make sense for you.
#3. Make sure that line 92 points to a valid CRAB script.
#4. May need to change lifetimes as desired on line 27.

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

spawn ssh -X -Y $USER@login02.brazos.tamu.edu
expect "$USER@login02.brazos.tamu.edu's password: "
send "$BRAZOS_PASSWORD\r"

foreach CT $lifetimes {
	expect "$ ";
	send "cd /home/$USER/CMSSW_7_1_15/src\r";
	expect "$ ";
	send "cd /home/$USER/CMSSW_7_1_15/src\r";
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
	send "cd /home/$USER/CMSSW_7_1_15/src/MuJetAnalysis/GEN_SIM \r";
	expect "$ ";
	send "crab -status -c DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1 \r";
        expect {
                "Enter GRID pass phrase:" {send "EP1D3M1C\r"}
        }
        expect "$ ";
	send "crab -getoutput -c DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1 \r";
	#expect {
	#	"Enter GRID pass phrase:" {send "$PASSWORD\r"}
	#} 
	expect "$ ";
	send "crab -publish -c DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1 > DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_madgraph452_bridge224_events80k_LHE_pythia8_cfi_GEN_SIM_v1.txt \r";
	expect "$ ";
	send "sed -i '/to publish in dataset/!d' DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_madgraph452_bridge224_events80k_LHE_pythia8_cfi_GEN_SIM_v1.txt \r";
	expect "$ ";
	send "sed -i 's/dataset/\\n/g' DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_madgraph452_bridge224_events80k_LHE_pythia8_cfi_GEN_SIM_v1.txt \r";
	expect "$ ";
	send "sed -i '/DarkSUSY/!d' DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_madgraph452_bridge224_events80k_LHE_pythia8_cfi_GEN_SIM_v1.txt \r";
	expect "$ ";
	send "cd /home/$USER/CMSSW_7_4_1_patch1/src\r";
	expect "$ ";
	send "cmsenv\r";
	expect "$ ";
	send "cmsenv\r";
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
	send "cd MuJetAnalysis/DIGI_PU \r";
	sleep 5;
	expect "$ ";
	send "cmsDriver.py DisplacedMuJet_Run2_cfi -s DIGI,L1,DIGI2RAW,HLT:@frozen25ns --datatier RAW-HLT --conditions MCRUN2_74_V9 --magField 38T_PostLS1 --eventcontent RAWSIM --customise=SLHCUpgradeSimulations/Configuration/postLS1Customs.customisePostLS1,MuJetAnalysis/GenProduction/addPileup.addPileup --pileup 2015_25ns_Startup_PoissonOOTPU --fileout out_raw.root -n 10 --no_exec \r";
	sleep 5;
	expect "$ ";
	send "mv DisplacedMuJet_Run2_cfi_DIGI_L1_DIGI2RAW_HLT_PU.py DIGI_L1_DIGI2RAW_HLT_25ns_PoissonOOTPU_MCRUN2_74_V9_cfg.py \r";	
	expect "$ ";
	send "cp ../DIGI-RAW/DIGI_L1_DIGI2RAW_HLT_25ns_PoissonOOTPU_MCRUN2_74_V9.CRAB.cfg . \r";
	expect "$ ";
	send "mv DIGI_L1_DIGI2RAW_HLT_25ns_PoissonOOTPU_MCRUN2_74_V9.CRAB.cfg DIGI_L1_DIGI2RAW_HLT_25ns_mGammaD_$mGammaD\_cT_$CT\_PoissonOOTPU_MCRUN2_74_V9.CRAB.cfg \r";
	expect "$ ";
	send "sed -i '/pset/c\pset        = DIGI_L1_DIGI2RAW_HLT_25ns_PoissonOOTPU_MCRUN2_74_V9_cfg.py' DIGI_L1_DIGI2RAW_HLT_25ns_mGammaD_$mGammaD\_cT_$CT\_PoissonOOTPU_MCRUN2_74_V9.CRAB.cfg \r";
	expect "$ ";
	send "sed -i '/datasetpath/c\datasetpath              = asdfasdf_to_be_replaced_by_datasetpath' DIGI_L1_DIGI2RAW_HLT_25ns_mGammaD_$mGammaD\_cT_$CT\_PoissonOOTPU_MCRUN2_74_V9.CRAB.cfg \r";
	expect "$ ";
	send "sed -i '/user_remote_dir/c\user_remote_dir         = DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_DIGI_L1_DIGI2RAW_HLT_PU_MCRUN2_74_V9_v1' DIGI_L1_DIGI2RAW_HLT_25ns_mGammaD_$mGammaD\_cT_$CT\_PoissonOOTPU_MCRUN2_74_V9.CRAB.cfg \r";
	expect "$ ";
	send "sed -i '/ui_working_dir/c\ui_working_dir          = DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_DIGI_L1_DIGI2RAW_HLT_PU_MCRUN2_74_V9_v1' DIGI_L1_DIGI2RAW_HLT_25ns_mGammaD_$mGammaD\_cT_$CT\_PoissonOOTPU_MCRUN2_74_V9.CRAB.cfg \r";
	expect "$ ";
	send "sed -i '/publish_data_name/c\publish_data_name       = DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_DIGI_L1_DIGI2RAW_HLT_PU_MCRUN2_74_V9_v1' DIGI_L1_DIGI2RAW_HLT_25ns_mGammaD_$mGammaD\_cT_$CT\_PoissonOOTPU_MCRUN2_74_V9.CRAB.cfg \r";
	expect "$ ";
	send "sed -i \"s/asdfasdf_to_be_replaced_by_datasetpath/\$(sed 's:\/:\\\\\/:g' /home/$USER/CMSSW_7_1_15/src/MuJetAnalysis/GEN_SIM/DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_madgraph452_bridge224_events80k_LHE_pythia8_cfi_GEN_SIM_v1.txt)/\" DIGI_L1_DIGI2RAW_HLT_25ns_mGammaD_$mGammaD\_cT_$CT\_PoissonOOTPU_MCRUN2_74_V9.CRAB.cfg \r";
	sleep 5;
	expect "$ ";
	send "crab -create -cfg DIGI_L1_DIGI2RAW_HLT_25ns_mGammaD_$mGammaD\_cT_$CT\_PoissonOOTPU_MCRUN2_74_V9.CRAB.cfg \r";	
	sleep 5;
	expect {
		"Enter GRID pass phrase:" {send "$PASSWORD\r"}
	}
	sleep 10;
	expect "$ ";
	sleep 2;	
	send "crab -submit -c DarkSUSY_mH_125_mGammaD_$mGammaD\_cT_$CT\_13TeV_DIGI_L1_DIGI2RAW_HLT_PU_MCRUN2_74_V9_v1 \r";
	sleep 1;
}
