#!/bin/bash
#SBATCH --job-name=CutFlow
#SBATCH --time=4:00:00 #DATA2017 need 2hr, MSSMD/BKG2017/TESTMC need 4hr
#SBATCH --ntasks=1
#SBATCH --mem=7000M    #DATA2017/BKG/TESTMC need 1000M, MSSMD2017 need 7000M
#SBATCH --output=CutFlow.out.%j
#SBATCH --account=122747014089

module load cctools
export PARROT_CVMFS_ALIEN_CACHE=/scratch/group/mitchcomp/CVMFS_cache
cmsSite=/scratch/group/mitchcomp/CMS/LOCAL_TAMU_HPRC
cmsMount=--mount=/cvmfs/cms.cern.ch/SITECONF/local=$cmsSite

parrot_run $cmsMount $SHELL << EOF
shopt -s expand_aliases
source /cvmfs/cms.cern.ch/cmsset_default.sh
cmsenv
echo 'gROOT->ProcessLine(".L foo_modified_2018L2Mu23Cosmic.C++"); analysis("SignalsList2018MSSMD_2SAmu_NoVtxProbCut_L2Mu23Cosmic.txt")' | root -l -b
EOF
