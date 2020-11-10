#!/bin/bash
#SBATCH --job-name=test
#SBATCH --time=02:00:00 #120 mins for 300k events
#SBATCH --ntasks=1
#SBATCH --mem=2000M
#SBATCH --output=batch/Test.out.%j
#SBATCH --account=122747014089

module load cctools
export PARROT_CVMFS_ALIEN_CACHE=/scratch/group/mitchcomp/CVMFS_cache
cmsSite=/scratch/group/mitchcomp/CMS/LOCAL_TAMU_HPRC
cmsMount=--mount=/cvmfs/cms.cern.ch/SITECONF/local=$cmsSite

parrot_run $cmsMount $SHELL << EOF
shopt -s expand_aliases
source /cvmfs/cms.cern.ch/cmsset_default.sh
cmsenv
cmsRun patTuple_cutana_mujets_MiniAOD_cfg.py
EOF
