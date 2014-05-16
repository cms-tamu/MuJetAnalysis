#!/bin/sh

# set up
export PROCESS=$1
export LOCALDIR=`pwd`
# SET ME! This is folder where CMSSW installed
export CMSSWDIR=/uscms/home/pakhotin/Work/2013-06-27_MuJets_Data2012_PAT_to_ROOT_with_PFCandidates/CMSSW_5_3_7_patch4/src
export OUTPUTDIR=${CMSSWDIR}/FitNtuple_DoubleMu_Run2012_PATv3

cd $CMSSWDIR
export SCRAM_ARCH=slc5_amd64_gcc462
source /uscmst1/prod/sw/cms/shrc prod
eval `scramv1 run -sh`

cd $LOCALDIR
cmsRun $OUTPUTDIR/FitNtuple_cfg.py
