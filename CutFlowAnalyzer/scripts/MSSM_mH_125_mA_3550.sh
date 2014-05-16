#!/bin/bash

export SAMPLE_NAME="MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_537p4_PATv2"

cd /uscms/home/pakhotin/Work/2013-06-25_MuJets_Study_PF_Isolation/CMSSW_5_3_11/src/
source $HOME/Work/Scripts/cms_setup_sl5.sh
eval `scramv1 runtime -sh`

cd AnalysisTools/CutFlowAnalyzer/test
cmsRun cutflowanalyzer_cfg.py >& ${SAMPLE_NAME}.out.txt
