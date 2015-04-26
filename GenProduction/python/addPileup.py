import FWCore.ParameterSet.Config as cms
from MuJetAnalysis.GenProduction.fileNamesPU import fileNamesPU

def addPileup(process):
    process.mix.input.fileNames = fileNamesPU
    return process

