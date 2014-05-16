#!/bin/bash

export SAMPLE_NAME="DarkSUSY_mH_150_Hto2n1to2nD2gammaD_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PATv2"

cd /uscms/home/pakhotin/Work/2013-06-25_MuJets_Study_PF_Isolation/CMSSW_5_3_11/src/
source $HOME/Work/Scripts/cms_setup_sl5.sh
eval `scramv1 runtime -sh`

cd AnalysisTools/CutFlowAnalyzer/test
cmsRun cutflowanalyzer_cfg.py >& ${SAMPLE_NAME}.out.txt
