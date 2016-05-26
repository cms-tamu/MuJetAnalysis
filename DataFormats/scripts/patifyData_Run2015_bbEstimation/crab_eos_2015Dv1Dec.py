from CRABClient.UserUtilities import config
config = config()

config.section_("General")
config.General.requestName = 'DoubleMuon_2015Dv1noPrompt_AOD_260373_260534_7412p4_p1_patTuple_cutana_mujets_14'
config.General.workArea = 'crab_projects'
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'patTuple_cutana_mujets_73X_cfg.py'
config.JobType.outputFiles = ['out_pat.root','out_ana.root']

config.section_("Data")
config.Data.inputDataset = '/DoubleMuon/Run2015D-16Dec2015-v1/AOD'
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 5
config.Data.lumiMask = 'Cert_246908-260627_13TeV_PromptReco_Collisions15_25ns_JSON_MuonPhys_v2.txt'
#config.Data.outLFNDirBase = '/store/group/alca_muonalign/lpernie/DoubleMuonRun2015D_PromptReco_AOD246908-258750_7412p4_patch1_patTuple_cutana_mujets'
#config.Data.outLFNDirBase = '/store/group/lpcdarksusy/'
config.Data.outLFNDirBase = '/store/user/lpernie/'
config.Data.publication = True
config.Data.outputDatasetTag = 'DoubleMuon_2015Dv1noPrompt_AOD_260373_260534_7412p4_p1_patTuple_cutana_mujets_14'

config.section_("Site")
#config.Site.storageSite = 'T2_CH_CERN'
#config.Site.storageSite = 'T3_US_FNALLPC'
config.Site.storageSite = 'T3_US_TAMU'

#https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions15/13TeV/
#https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FDoubleMu*%2FRun2015*-PromptReco-v1%2FAOD

#NJOBS = 1
#config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
