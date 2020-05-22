#!/bin/bash
#SBATCH --job-name=CutFlow
#SBATCH --time=11:59:00
#SBATCH --ntasks=1
#SBATCH --mem=10000M
#SBATCH --output=CutFlow.out.%j

module load cctools
export PARROT_CVMFS_ALIEN_CACHE=/scratch/group/mitchcomp/CVMFS_cache
cmsSite=/scratch/group/mitchcomp/CMS/LOCAL_TAMU_HPRC
cmsMount=--mount=/cvmfs/cms.cern.ch/SITECONF/local=$cmsSite

parrot_run $cmsMount $SHELL << EOF
shopt -s expand_aliases
source /cvmfs/cms.cern.ch/cmsset_default.sh
cmsenv
echo 'gROOT->ProcessLine(".L foo_modified.C++"); analysis("SignalsList2017MSSMD_1SAmu.txt")' | root -l -b
EOF
