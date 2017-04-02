from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'crab_2016B_MuOnia_AnaPromptJpsi_v3'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'patTuple_cutana_mujets_73X_cfg.py'

config.Data.inputDataset = '/MuOnia/Run2016B-23Sep2016-v3/AOD'
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 20
config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions16/13TeV/Cert_271036-282092_13TeV_PromptReco_Collisions16_JSON_MuonPhys.txt'
#config.Data.runRange = '273150-273406' 
config.Data.outLFNDirBase = '/store/user/castaned/' 
config.Data.publication = True
config.Data.outputDatasetTag = 'MuOnia_Run2016B_AnaPromptJpsi_v3'
config.JobType.allowUndistributedCMSSW = True 

config.Site.storageSite = 'T3_US_TAMU'