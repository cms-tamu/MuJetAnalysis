import FWCore.ParameterSet.Config as cms
import os

## helper function for pile-up
def addPileUp(process, pu = 140, filelist = def_filelist):
    ff = open(filelist, "r")
    pu_files = ff.read().split('\n')
    ff.close()
    pu_files = filter(lambda x: x.endswith('.root'),  pu_files)
    
    process.mix.input = cms.SecSource("PoolSource",
        nbPileupEvents = cms.PSet(
            averageNumber = cms.double(pu)
        ),
        type = cms.string('poisson'),
        sequential = cms.untracked.bool(False),
        fileNames = cms.untracked.vstring(*pu_files)
    )
    return process

## use all ROOT files in a given directory as input
def useInputDir(process, inputDir, pattern="pat"):
    theInputFiles = []
    if not os.path.isdir(inputDir):
        print "ERROR: This is not a valid directory: ", inputDir
        exit()
    theInputFiles.extend(['file:' + inputDir + x for x in os.listdir(inputDir) if (x.endswith('root') and (pattern in x))])
    process.source.fileNames = cms.untracked.vstring(*theInputFiles)	
    return process
