#!/bin/bash
#SBATCH --job-name=CutFlow
#SBATCH --time=4:00:00
#SBATCH --ntasks=1
#SBATCH --mem=7000M
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
echo 'gROOT->ProcessLine(".L foo_modified.C++"); analysis("SignalsList2017MSSMD_2SAmu_NoVtxProbCut.txt")' | root -l -b
EOF
