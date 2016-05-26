from CRABClient.UserUtilities import config
config = config()

config.section_("General")
config.General.requestName = 'DarkSUSY_mH_125_mGammaD_0250_cT_000_13TeV_MG452_BR224_LHE_pythia8_NTUP_V1'
config.General.workArea = 'crab_projects'
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'run_cutFlow_with_Hit.py'
config.JobType.outputFiles = ['out_pat.root','out_ana.root']

config.section_("Data")
#config.Data.inputDataset = '/DoubleMuon/Run2015D-PromptReco-v4/AOD'
config.Data.inputDataset = '/DarkSUSY_mH_125_mGammaD_0250_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/dildick-DarkSUSY_mH_125_mGammaD_0250_cT_000_13TeV_RAW2DIGI_L1Reco_RECO_MCRUN2_74_V9_v1-3'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
#config.Data.lumiMask = 'Cert_246908-260627_13TeV_PromptReco_Collisions15_25ns_JSON_MuonPhys_v2.txt'
#config.Data.outLFNDirBase = '/store/group/alca_muonalign/lpernie/DoubleMuonRun2015D_PromptReco_AOD246908-258750_7412p4_patch1_patTuple_cutana_mujets'
#config.Data.outLFNDirBase = '/store/group/lpcdarksusy/'
config.Data.outLFNDirBase =  '/store/user/castaned/'
config.Data.publication = True
config.Data.outputDatasetTag = 'DarkSUSY_mH_125_mGammaD_0250_cT_000_13TeV_MG452_BR224_LHE_pythia8_NTUP_V1'

config.section_("Site")
#config.Site.storageSite = 'T2_CH_CERN'
#config.Site.storageSite = 'T3_US_FNALLPC'
config.Site.storageSite = 'T3_US_TAMU'

#https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions15/13TeV/
#https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FDoubleMu*%2FRun2015*-PromptReco-v1%2FAOD

#NJOBS = 1
#config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
