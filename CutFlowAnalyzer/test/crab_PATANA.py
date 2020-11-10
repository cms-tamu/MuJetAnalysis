from CRABClient.UserUtilities import config
config = config()
config.General.workArea = 'crab_projects'
config.General.transferLogs = True
config.JobType.pluginName = 'Analysis'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.lumiMask = 'Cert_314472-325175_13TeV_PromptReco_Collisions18_JSON.txt'
config.Data.outLFNDirBase = '/store/user/dildick/'
config.Data.publication = True
config.Site.storageSite = 'T3_US_FNALLPC'
config.JobType.allowUndistributedCMSSW = True
config.Data.unitsPerJob = 10

cmsRunConfig = '/uscms/home/dildick/nobackup/work/DisplacedMuonJetAnalysis_Run2/CMSSW_10_2_18/src/MuJetAnalysis/DataFormats/scripts/patifyMC_13TeV/patTuple_cutana_mujets_MiniAOD_cfg.py'
cmsRunArgData2018ABC = " mc=False year=2018 era=ABC"
cmsRunArgData2018D = " mc=False year=2018 era=ABC"
cmsRunArgMC2018 = " mc=True year=2018"

samples = {
    'MET2018A' : [
        '/MET/dildick-crab_METRun2018A-17Sep2018-v1_Filter20201027_V2-463ea116673913e009b1f501c2d5b5ef/USER',
        cmsRunConfig + cmsRunArgData2018ABC
    ],
    'MET2018B' : [
        '/MET/dildick-crab_METRun2018B-17Sep2018-v1_Filter20201027_V2-463ea116673913e009b1f501c2d5b5ef/USER',
        cmsRunConfig + cmsRunArgData2018ABC
    ],
    'MET2018C' : [
        '/MET/dildick-crab_METRun2018C-17Sep2018-v1_Filter20201027_V2-463ea116673913e009b1f501c2d5b5ef/USER',
        cmsRunConfig + cmsRunArgData2018ABC
    ],
    'MET2018D' : [
        '/MET/dildick-crab_METRun2018D-PromptReco-v2_Filter20201027_V3-463ea116673913e009b1f501c2d5b5ef/USER',
        cmsRunConfig + cmsRunArgData2018D
    ],
    'TTWZ' : [
        '/TTWZ_TuneCP5_13TeV-madgraph-pythia8/dildick-crab_TTWZ_TuneCP5_13TeV-madgraph-pythia8_Filter20201027_V3-463ea116673913e009b1f501c2d5b5ef/USER',
        cmsRunConfig + cmsRunArgMC2018
    ],
    'TTZToLLNuNu' : [
        '/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/dildick-crab_TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8_Filter20201027_V3-463ea116673913e009b1f501c2d5b5ef/USER',
        cmsRunConfig + cmsRunArgMC2018
    ],
    'TTZZ' : [
        '/TTZZ_TuneCP5_13TeV-madgraph-pythia8/dildick-crab_TTZZ_TuneCP5_13TeV-madgraph-pythia8_Filter20201027_V3-463ea116673913e009b1f501c2d5b5ef/USER',
        cmsRunConfig + cmsRunArgMC2018
    ],
    'WWZTo4L2Nu' : [
        '/WWZTo4L2Nu_4f_TuneCP5_13TeV_amcatnlo_pythia8/dildick-crab_WWZTo4L2Nu_4f_TuneCP5_13TeV_amcatnlo_pythia8_Filter20201027_V3-463ea116673913e009b1f501c2d5b5ef/USER',
        cmsRunConfig + cmsRunArgMC2018
    ],
    'WZTo3LNu' : [
        '/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/dildick-crab_WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8_Filter20201027_V3-463ea116673913e009b1f501c2d5b5ef/USER',
        cmsRunConfig + cmsRunArgMC2018
    ],
    'WZZ' : [
        '/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/dildick-crab_WZZ_TuneCP5_13TeV-amcatnlo-pythia8_Filter20201027_V3-463ea116673913e009b1f501c2d5b5ef/USER',
        cmsRunConfig + cmsRunArgMC2018
    ],
    'ZZTo4L': [
        '/ZZTo4L_TuneCP5_13TeV-amcatnloFXFX-pythia8/dildick-crab_ZZTo4L_TuneCP5_13TeV-amcatnloFXFX-pythia8_Filter20201027_V3-463ea116673913e009b1f501c2d5b5ef/USER',
        cmsRunConfig + cmsRunArgMC2018
    ],
    'ZZZ' : [
        '/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/dildick-crab_ZZZ_TuneCP5_13TeV-amcatnlo-pythia8_Filter20201027_V3-463ea116673913e009b1f501c2d5b5ef/USER',
        cmsRunConfig + cmsRunArgMC2018
    ]
}


if __name__ == '__main__':
    from CRABAPI.RawCommand import crabCommand

    # process all samples
    for s in samples:
        config.JobType.psetName = samples[s][1]
        config.Data.inputDataset = samples[s][0]
        config.General.requestName = s + '_PATANA20201110_v1'
        print config
        #crabCommand('submit', config = config)
