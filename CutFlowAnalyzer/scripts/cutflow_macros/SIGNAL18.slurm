#!/bin/bash
#SBATCH --job-name=SIGNAL18
#SBATCH --time=00:30:00 #DATA2017 need 2hr, MSSMD/BKG/TESTMC need 4hr
#SBATCH --ntasks=1
#SBATCH --mem=9000M    #DATA2017/BKG/TESTMC need 1000M, MSSMD need 7000M
#SBATCH --output=CutFlow.out.%j
#SBATCH --account=122747014489

module load cctools
export PARROT_CVMFS_ALIEN_CACHE=/scratch/group/mitchcomp/CVMFS_cache
cmsSite=/scratch/group/mitchcomp/CMS/LOCAL_TAMU_HPRC
cmsMount=--mount=/cvmfs/cms.cern.ch/SITECONF/local=$cmsSite

parrot_run $cmsMount $SHELL << EOF
shopt -s expand_aliases
source /cvmfs/cms.cern.ch/cmsset_default.sh
cmsenv
echo 'gROOT->ProcessLine(".L CutFlow_2018L2Mu23.C++"); analysis("SignalsList2018ALP_2SAmu_NoVtxProbCut_4HLT.txt")' | root -l -b
EOF
