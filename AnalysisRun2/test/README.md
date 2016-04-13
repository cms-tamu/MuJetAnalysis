HitRecovery analyzer


********************************************
- Use CMSSW_7_4_1_patch1 

cmsrel CMSSW_7_4_1_patch1

cd CMSSW_7_4_1_patch1/src

cmsenv

git clone -b for-CMSSW-74X https://github.com/castaned/MuJetAnalysis.git

cd MuJetAnalysis/

scram b -j 12

cd AnalysisRun2/test


- create followig directories

mkdir SBATCH_JOBS
mkdir SBATCHLOG

- creates SBATCH submission scripts

./create_sbatch_mcreco.sh mc0250.txt

- go to SBATCH_JOBS directory

cd SBATCH_JOBS

-submit jobs

i.e.  sbatch DarkSUSY_mH_125_mGammaD_0250_cT_000_13TeV_RAW2DIGI_L1Reco_RECO_MCRUN2_74_V9_v1.slrm

- Monitor jobs

squeue -u <userame>

output files in AnalysisRun2/test/<sample_name>

