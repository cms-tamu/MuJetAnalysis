from root_numpy import root2array, root2rec, tree2rec
from root_numpy.testdata import get_filepath

import sys
from ROOT import *
from argparse import ArgumentParser

#from hepPlotter import HepPlotter
#from hepPlotterDataMC import HepPlotterDataMC
#import hepPlotterTools as hpt
#import hepPlotterLabels as hpl
import math as m
import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from Helpers import *
import numpy

verbose = False

## mass of the muon in GeV
mmu = 105.6583745 * 0.001
mZ = 91.1876

verbose = True

def getPT(m1):
    px = m1[1]
    py = m1[2]
    return numpy.sqrt(px*px + py*py)

def getPhi(m1):
    return m1[4]

def normalizePhi(result):
    while (result > M_PI):
        result -= 2*M_PI;
    while (result <= -M_PI):
        result += 2*M_PI;
    return result

## total energy of the muon
def energy(mmu, px, py, pz):
    return numpy.sqrt(mmu*mmu + px*px + py*py + pz*pz)

## dimuon invariant mass
def inner(m1, m2):
    return m1[0] * m2[0] - m1[1] * m2[1] - m1[2] * m2[2] - m1[3] * m2[3]

def invmass(m1, m2):
    a = inner(m1,m1)
    b = inner(m2,m2)
    c = 2*inner(m1,m2)
    return numpy.sqrt(a+b+c)

def inv3mass(m1, m2, m3):
    a = inner(m1,m1)
    b = inner(m2,m2)
    c = inner(m3,m3)
    d = 2*inner(m1,m2)
    e = 2*inner(m1,m3)
    f = 2*inner(m2,m3)
    return numpy.sqrt(a+b+c+d+e+f)

def isMassInZPeak(m):
    return abs(m-mZ)<15

def bestMassInZPeak(m1, m2, m3):
    masses = [m1, m2, m3]
    massdiffs = [abs(m1-mZ), abs(m2-mZ), abs(m3-mZ)]
    index = massdiffs.index(min(massdiffs))
    return masses[index]

def bestMassInZPeak(m1, m2):
    masses = [m1, m2]
    massdiffs = [abs(m1-mZ), abs(m2-mZ)]
    index = massdiffs.index(min(massdiffs))
    return masses[index]

def wasTriggered(tree):
    isTriggered = False
    ## was triggered?
    signalTriggers = [
        "HLT_TrkMu12_DoubleTrkMu5NoFiltersNoVtx",
        "HLT_DoubleL2Mu23NoVtx_2Cha",
        "HLT_TripleMu_12_10_5",
        "HLT_Mu18_Mu9_SameSign"
    ]
    for trigger in signalTriggers:
        if any(trigger in s for s in list(tree.hltPaths)):
            isTriggered = True
    return isTriggered

datasets = ['WZTo3LNu', 'ZZTo4Nu','TTWJetsToLNu', 'TTZJetsToLNu', 'METData']

dataFiles = {}
def add_ZZ(dataFiles):
    dataFiles['ZZTo4Nu'] = [
        '/home/dildick/out_ana_all_ZZ.root'
        ]

def add_WZ(dataFiles):
    dataFiles['WZTo3LNu'] = [
        '/uscms_data/d3/dildick/work/DisplacedMuonJetAnalysis_Run2/CMSSW_10_2_18/src/MuJetAnalysis/CutFlowAnalyzer/scripts/highleveltrigger/out_ana_WZ_2018.root'
        ]

def add_TTW(dataFiles):
    dataFiles['TTWJetsToLNu'] = [
        '/fdata/hepx/store/user/dildick/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_TTbarW_ANA_v1/180216_032728/0000/'
        ]

def add_TTZ(dataFiles):
    dataFiles['TTZJetsToLNu'] = [
        '/uscms_data/d3/dildick/work/DisplacedMuonJetAnalysis_Run2/CMSSW_10_2_18/src/MuJetAnalysis/CutFlowAnalyzer/scripts/highleveltrigger/out_ana_TTZ_2018.root'
        ]

def add_METData(dataFiles):
    dataFiles['METData'] = [
        '/home/dildick/DisplacedMuonJetAnalysis_2016/CMSSW_8_0_24/src/MuJetAnalysis/AnalysisRun2/scripts/HLTEfficiency/orthogonalMethod/out_ana_selected_MET_2016BH_20180208_clone.root'
        ]

#add_ZZ(dataFiles)
add_WZ(dataFiles)
#add_TTW(dataFiles)
#add_TTZ(dataFiles)
#add_METData(dataFiles)

MET_Triger_Patterns = [
    'HLT_PFMET100_PFMHT100_IDTight_CaloBTagDeepCSV_3p1',
    'HLT_PFMET100_PFMHT100_IDTight_PFHT60',
    'HLT_PFMET110_PFMHT110_IDTight_CaloBTagDeepCSV_',
    'HLT_PFMET110_PFMHT110_IDTight',
    'HLT_PFMET120_PFMHT120_IDTight_CaloBTagDeepCSV_3p1',
    'HLT_PFMET120_PFMHT120_IDTight_PFHT60',
    'HLT_PFMET120_PFMHT120_IDTight',
    'HLT_PFMET130_PFMHT130_IDTight_CaloBTagDeepCSV_3p1',
    'HLT_PFMET130_PFMHT130_IDTight',
    'HLT_PFMET140_PFMHT140_IDTight_CaloBTagDeepCSV_3p1',
    'HLT_PFMET140_PFMHT140_IDTight',
    'HLT_PFMET200_HBHECleaned',
    'HLT_PFMET200_HBHE_BeamHaloCleaned',
    'HLT_PFMET200_NotCleaned',
    'HLT_PFMET250_HBHECleaned',
    'HLT_PFMET300_HBHECleaned',
    'HLT_PFMETTypeOne100_PFMHT100_IDTight_PFHT60',
]

def wasMETTriggered(MET_Triger_Patterns, tree):
    for s in MET_Triger_Patterns:
        for p in list(tree.hltPaths):
            if s in p:
                return True
    return False

histograms = {}

MET_triggers = set()

print 'Number of arguments:', len(sys.argv), 'arguments.'
print 'Argument List:', str(sys.argv)

## get the input file
inputFile = list(sys.argv)[1]
print inputFile
rootFile = ROOT.TFile(inputFile,"")

tree = rootFile.Get("cutFlowAnalyzerPXBL4PXFL3/Events")

newTitle = inputFile#rootFile.GetTitle()
print
newTitle = newTitle.replace('out_ana','out_ana_clone')
print newTitle
print tree
newfile = TFile(newTitle, "RECREATE")
print newfile
newtree = tree.CloneTree(0)
OK_MET = numpy.zeros(1, dtype=int)
OK_Signal = numpy.zeros(1, dtype=int)
best_OS_dimuon_mass = numpy.zeros(1, dtype=float)
best_SS_dimuon_mass = numpy.zeros(1, dtype=float)
m123 = numpy.zeros(1, dtype=float)
newtree.Branch( 'OK_MET', OK_MET, 'OK_MET/I' )
newtree.Branch( 'OK_Signal', OK_Signal, 'OK_Signal/I' )
newtree.Branch( 'best_OS_dimuon_mass', best_OS_dimuon_mass, 'best_OS_dimuon_mass/D')
newtree.Branch( 'best_SS_dimuon_mass', best_SS_dimuon_mass, 'best_SS_dimuon_mass/D')
newtree.Branch( 'm123', m123, 'm123/D')

for k in range(0, tree.GetEntries()):

    if k%1==0: print "Processing event ", k, "/",tree.GetEntries()
    tree.GetEntry(k)

    q0 = tree.selMu0_charge
    q1 = tree.selMu1_charge
    q2 = tree.selMu2_charge

    if q0 == q1 == q2:
        print "\tSkip"
        continue

    px0 = tree.selMu0_px
    px1 = tree.selMu1_px
    px2 = tree.selMu2_px

    py0 = tree.selMu0_py
    py1 = tree.selMu1_py
    py2 = tree.selMu2_py

    pz0 = tree.selMu0_pz
    pz1 = tree.selMu1_pz
    pz2 = tree.selMu2_pz

    E0 = energy(mmu, tree.selMu0_px, py0, pz0)
    E1 = energy(mmu, px1, py1, pz1)
    E2 = energy(mmu, px2, py2, pz2)

    mu0 = [E0, tree.selMu0_px, py0, pz0]
    mu1 = [E1, px1, py1, pz1]
    mu2 = [E2, px2, py2, pz2]

    invm3 = inv3mass(mu0, mu1, mu2)
    m123[0] = invm3
    #print m123[0], type(invm3)

    SS_dimuon_mass = 0
    OS_dimuon_mass1 = 0
    OS_dimuon_mass2 = 0

    if q0 * q1 > 0:
        SS_dimuon_mass = invmass(mu0, mu1)
        OS_dimuon_mass1 = invmass(mu1, mu2)
        OS_dimuon_mass2 = invmass(mu0, mu2)
        OS_dimuon_mass = bestMassInZPeak(OS_dimuon_mass1, OS_dimuon_mass2)

    elif q0 * q2 > 0:
        SS_dimuon_mass = invmass(mu0, mu2)
        OS_dimuon_mass1 = invmass(mu0, mu1)
        OS_dimuon_mass2 = invmass(mu1, mu2)
        OS_dimuon_mass = bestMassInZPeak(OS_dimuon_mass1, OS_dimuon_mass2)

    elif q1 * q2 > 0:
        SS_dimuon_mass = invmass(mu1, mu2)
        OS_dimuon_mass1 = invmass(mu0, mu1)
        OS_dimuon_mass2 = invmass(mu0, mu2)
        OS_dimuon_mass = bestMassInZPeak(OS_dimuon_mass1, OS_dimuon_mass2)

    else:
        SS_dimuon_mass = 0
        OS_dimuon_mass1 = 0
        OS_dimuon_mass2 = 0
        OS_dimuon_mass = 0

    best_OS_dimuon_mass[0] = 0
    best_SS_dimuon_mass[0] = 0
    best_OS_dimuon_mass[0] = OS_dimuon_mass
    best_SS_dimuon_mass[0] = SS_dimuon_mass

    OK_MET[0] = 0
    if wasMETTriggered(MET_Triger_Patterns, tree):
        OK_MET[0] = 1

    OK_Signal[0] = 0
    if wasTriggered(tree):
        OK_Signal[0] = 1

    newtree.Fill()

newfile.Write()
newfile.Close()

"""
exit(1)

for sample in dataFiles:

    print "Running on sample", sample
    print dataFiles[sample][0]
    rootFile = TFile(dataFiles[sample][0],"UPDATE")

    if sample == 'METData':

        if (verbose): print "Loading tree Events"
        tree = rootFile.Get("Events")
    else:
        if (verbose): print "Loading directory cutFlowAnalyzerPXBL3PXFL2"
        tree = rootFile.Get("cutFlowAnalyzerPXBL3PXFL2/Events")

        if not tree:
            if (verbose): print "Tree cutFlowAnalyzerPXBL3PXFL2/Events does not exist"
            continue

    if (verbose): print "  Events  ", tree.GetEntries()

    newtree = tree.CloneTree(0)

    ## add OK_MET branch
    ## add OK_Signal branch
    OK_MET = numpy.zeros(1, dtype=int)
    OK_Signal = numpy.zeros(1, dtype=int)
    newtree.Branch( 'OK_MET', OK_MET, 'OK_MET/I' )
    newtree.Branch( 'OK_Signal', OK_Signal, 'OK_Signal/I' )

    nEvents = 0
    for k in range(0, tree.GetEntries()):

        nEvents += 1

        if k%10000==0: print "Processing event ", k, "/",tree.GetEntries()
        tree.GetEntry(k)
        if k>1000000000: break

        #print list(tree.hltPaths)
        #for p in list(tree.hltPaths):
        #    if "MET" in p:
        #        MET_triggers.add(p)

        OK_MET[0] = 0
        if wasMETTriggered(MET_Triger_Patterns, tree):
            OK_MET[0] = 1

        OK_Signal[0] = 0
        if wasTriggered(tree):
            OK_Signal[0] = 1

        newtree.Fill()

    rootFile.Write()
    rootFile.Close()

    print "Saved tree with %d"  % ( nEvents )

exit(1)

print MET_triggers
for p in MET_triggers:
    print p

MET_triggers_cleaned = set()
for p in MET_triggers:
    temp = p.find('_v')
    index =  temp - len(p)
    pp = p[:index]
    MET_triggers_cleaned.add(pp)
## remove the version number

print
print
for p in MET_triggers_cleaned:
    print p
"""
