#!/bin/bash

if [ ! -d  SBATCH_JOBS ];then
    mkdir SBATCH_JOBS
fi;

if [ ! -d  SBATCHLOG ];then
    mkdir SBATCHLOG
fi;


declare -a arr=("Charmonium_B" "Charmonium_C" "Charmonium_D" "Charmonium_E" "Charmonium_F" "Charmonium_G" "Charmonium_H")

## now loop through the above array
for i in "${arr[@]}"
do

cat  >  SBATCH_JOBS/${i}.slrm <<EOF
#!/bin/bash      
#SBATCH -J AnalysisJpsi
#SBATCH -n1
#SBATCH --time=08:30:00
#SBATCH --mem-per-cpu=8000mb
#SBATCH -p background
#SBATCH -o $PWD/SBATCHLOG/SBATCH_${i}.stdout
#SBATCH -e $PWD/SBATCHLOG/SBATCH_${i}.stderr
      
cd  /fdata/scratch/castaned/DisplacedMuonJetAnalysis_2016/CMSSW_8_0_20/src
export VO_CMS_SW_DIR=/cvmfs/cms.cern.ch
source $VO_CMS_SW_DIR/cmsset_default.sh
export SCRAM_ARCH=slc6_amd64_gcc493
eval \`scramv1 runtime -sh\`
cd  /fdata/scratch/castaned/DisplacedMuonJetAnalysis_2016/CMSSW_8_0_20/src/MuJetAnalysis/CutFlowAnalyzer/scripts/forJpsi
echo 'gROOT->ProcessLine(".L jpsi.C++"); analysis("${i}.txt")' | root -l -b 
      
exit 0

EOF
done 

