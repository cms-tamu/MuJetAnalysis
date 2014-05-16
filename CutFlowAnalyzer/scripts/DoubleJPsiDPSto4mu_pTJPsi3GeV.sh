#!/bin/bash

export SAMPLE_NAME="DoubleJPsiDPSto4mu_pTJPsi3GeV_8TeV-pythia8_537p4_PATv3"

cd /uscms/home/pakhotin/Work/2013-04-25_MuJetAnalysis_MC/CMSSW_5_3_7_patch4/src/
source $HOME/Work/Scripts/cms_setup_sl5.sh
eval `scramv1 runtime -sh`

cd AnalysisTools/CutFlowAnalyzer/test
cmsRun cutflowanalyzer_cfg.py >& ${SAMPLE_NAME}.out.txt
