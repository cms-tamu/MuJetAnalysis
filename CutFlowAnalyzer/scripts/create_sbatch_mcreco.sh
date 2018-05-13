#!/bin/bash

if [ ! -d  SBATCH_JOBS ];then
    mkdir SBATCH_JOBS
fi;

if [ ! -d  SBATCHLOG ];then
    mkdir SBATCHLOG
fi;


while read line
do
name=$line
echo "Sample - $name"

echo " name folder   "  $name
     
mkdir $name
      
#nJobs=$(wc -l python/$name.txt | cut -f1 -d' ')
nJobs=100
      
echo "Number of Jobs   $nJobs"
   
cat  >  SBATCH_JOBS/${name}.slrm <<EOF
#!/bin/bash      
#SBATCH -J AnalysisReco
#SBATCH -n1
#SBATCH --time=08:30:00
#SBATCH --mem-per-cpu=8000mb
#SBATCH -p background
#SBATCH --array=1-$nJobs
#SBATCH -o $PWD/SBATCHLOG/SBATCH_%a.stdout
#SBATCH -e $PWD/SBATCHLOG/SBATCH_%a.stderr
      
export PROCESS=\$SLURM_ARRAY_TASK_ID
cd /fdata/scratch/castaned/Analysis2015data/SL6/CMSSW_7_4_1_patch1/src/
export VO_CMS_SW_DIR=/cvmfs/cms.cern.ch
source $VO_CMS_SW_DIR/cmsset_default.sh
export SCRAM_ARCH=slc6_amd64_gcc491
eval \`scramv1 runtime -sh\`
cd /fdata/scratch/castaned/Analysis2015data/SL6/CMSSW_7_4_1_patch1/src/MuJetAnalysis/CutFlowAnalyzer/test
cmsRun analysis_mcreco_cfg.py $name $nJobs
      
exit 0

EOF
done < $1

