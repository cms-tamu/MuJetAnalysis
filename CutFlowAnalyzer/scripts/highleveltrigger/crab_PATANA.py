from CRABAPI.RawCommand import crabCommand
from samples import *

samples = [
    #SingleMu2018A,
    #SingleMu2018B,
    #SingleMu2018C,
    #SingleMu2018D,
    #MET2018A,
    #MET2018B,
    #MET2018C,
    #MET2018D,
    TTZToLLNuNu,
    #WZTo3LNu1,
    #WZTo3LNu2,
    #WZTo3LNu3,
    #WZTo3LNu4,
    #ZZ4L
    #TTWJetsToLNu
]

def createBaseConfig():
    from CRABClient.UserUtilities import config
    config = config()
    config.General.workArea = 'crab_projects'
    config.General.transferLogs = True
    config.JobType.pluginName = 'Analysis'
    config.Data.splitting = 'FileBased'
    config.Data.outLFNDirBase = '/store/user/dildick/'
    config.Data.publication = True
    config.Site.storageSite = 'T3_US_FNALLPC'
    config.Site.whitelist = ['T2_US*']
    config.Data.ignoreLocality = True
    config.JobType.allowUndistributedCMSSW = True
    config.Data.unitsPerJob = 1
    cmsRunConfig = '/uscms/home/dildick/nobackup/work/DisplacedMuonJetAnalysis_Run2/CMSSW_10_2_18/src/MuJetAnalysis/DataFormats/scripts/patifyMC_13TeV/patTuple_cutana_mujets_MiniAOD_cfg.py'
    config.JobType.psetName = cmsRunConfig
    return config


if __name__ == '__main__':
    # process all samples
    for sample in samples:
        config = createBaseConfig()
        config.JobType.pyCfgParams = sample[2].split(' ')
        config.Data.inputDataset = sample[1]
        config.General.requestName = sample[0] + '_PATANA20201210_v4'
        config.Data.inputDBS = sample[3]
        print config
        crabCommand('submit', config = config)
