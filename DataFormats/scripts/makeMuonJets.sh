#!/bin/sh

# set up
export PROCESS=$1
export LOCALDISK=`pwd`
export AFSDISK=/uscms/home/pivarski/NOBACKUP/MuonJetsAnalysis/analyze_3_8_4/src


cd $AFSDISK
eval `scramv1 run -sh`
cd $LOCALDISK

cmsRun $AFSDISK/AnalysisDataFormats/MuJetAnalysis/scripts/makeMuonJets_cfg.py
