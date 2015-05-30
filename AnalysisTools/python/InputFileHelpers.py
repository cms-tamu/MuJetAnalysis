import FWCore.ParameterSet.Config as cms
import os

## use all ROOT files in a given directory as input
def useInputDir(process, inputDir, pattern="pat"):
    theInputFiles = []
    if not os.path.isdir(inputDir):
        print "ERROR: This is not a valid directory: ", inputDir
        exit()
    theInputFiles.extend(['file:' + inputDir + x for x in os.listdir(inputDir) if (x.endswith('root') and (pattern in x))])
    process.source.fileNames = cms.untracked.vstring(*theInputFiles)	
    return process
