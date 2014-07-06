#!/bin/sh

# set up
export PROCESS=$1
export LOCALDIR=`pwd`
# SET ME! This is folder where CMSSW installed
export CMSSWDIR=/home/anthony.rose/CMSSW_5_3_11_patch5/src

cd $CMSSWDIR
export SCRAM_ARCH=slc5_amd64_gcc462
source /home/hepxadmin/cmssw/cmsset_default.sh
eval `scramv1 run -sh`

cd $LOCALDIR
cmsRun $CMSSWDIR/MuJetAnalysis/CutFlowAnalyzer/test/cutflowanalyzer_cfg_condor.py
