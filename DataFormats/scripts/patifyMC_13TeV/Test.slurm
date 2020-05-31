#!/bin/bash
#SBATCH --job-name=test              #Set the job name to "test"
#SBATCH --time=02:00:00              #Set the wall clock limit 
#SBATCH --ntasks=1                   #Request 1 task
#SBATCH --mem=2000M                  #Request 2000MB per node
#SBATCH --output=batch/Test.out.%j         #Send stdout/err to "Test.out.[jobID]"

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
