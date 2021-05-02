#!/bin/bash
#SBATCH --job-name=DATA18
#SBATCH --time=5:00:00 #DATA2018 need 5hr, MSSMD/BKG MC need 4hr
#SBATCH --ntasks=1
#SBATCH --mem=2000M    #DATA2018/BKG need 1000M, MSSMD need 7000M
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
echo 'gROOT->ProcessLine(".L CutFlow_2018L2Mu23.C++"); analysis("DataList2018_2SAmu_NoVtxProbCut_4HLT.txt")' | root -l -b
EOF
