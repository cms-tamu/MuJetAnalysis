import sys
from ROOT import *
from argparse import ArgumentParser

from hepPlotter import HepPlotter
import hepPlotterTools as hpt
#import hepPlotterLabels as hpl
import math as m
import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from Helpers import *

## mass of the muon in GeV
mmu = 105.6583745 * 0.001
mZ = 91.1876

def getPT(m1):
    px = m1[1]
    py = m1[2]
    return m.sqrt(px*px + py*py)

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
    return m.sqrt(mmu*mmu + px*px + py*py + pz*pz)

## dimuon invariant mass
def inner(m1, m2):
    return m1[0] * m2[0] - m1[1] * m2[1] - m1[2] * m2[2] - m1[3] * m2[3]

def invmass(m1, m2):
    a = inner(m1,m1)
    b = inner(m2,m2)
    c = 2*inner(m1,m2)
    return m.sqrt(a+b+c)

def inv3mass(m1, m2, m3):
    a = inner(m1,m1)
    b = inner(m2,m2)
    c = inner(m3,m3)
    d = 2*inner(m1,m2)
    e = 2*inner(m1,m3)
    f = 2*inner(m2,m3)
    return m.sqrt(a+b+c+d+e+f)

def isMassInZPeak(m):
    return abs(m-mZ)<15

def bestMassInZPeak(m1, m2, m3):
    masses = [m1, m2, m3]
    massdiffs = [abs(m1-mZ), abs(m2-mZ), abs(m3-mZ)]
    index = massdiffs.index(min(massdiffs))
    return masses[index]

dataFiles = {}
dataFiles['WZTo3LNu'] = [
    '/fdata/hepx/store/user/dildick/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/crab_WZTo3LNu_Inclusive_ANA_v1/180216_034648/0000/',
    '/fdata/hepx/store/user/dildick/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/crab_WZTo3LNu_Inclusive_ANA_v1/180216_034648/0001/'
]
dataFiles['ZZTo4Nu'] = [
    '/fdata/hepx/store/user/dildick/EWK_13TeV_CALCHEP_50K_batch1_GEN_SIM_v1_TAMU/crab_ZZTo4L_ANA_v6/180208_060822/0000/',
    '/fdata/hepx/store/user/dildick/EWK_13TeV_CALCHEP_50K_batch2_GEN_SIM_v3_TAMU/crab_ZZTo4L_ANA_v6_PartTwo/180208_060940/0000/'
]
dataFiles['TTWJetsToLNu'] = [
    '/fdata/hepx/store/user/dildick/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_TTbarW_ANA_v1/180216_032728/0000/'
]
dataFiles['TTZJetsToLNu'] = [
    '/fdata/hepx/store/user/dildick/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/crab_TTbarZ_ANA_v2/180221_004015/0000/'
]
dataFiles['METData'] = [
    '/home/dildick/DisplacedMuonJetAnalysis_2016/CMSSW_8_0_24/src/MuJetAnalysis/AnalysisRun2/scripts/HLTEfficiency/orthogonalMethod/'
]

histograms = {}
histograms['mu_pT0'] = ROOT.TH1D("mu_pT0","",150,0,300)
histograms['mu_pT1'] = ROOT.TH1D("mu_pT1","",150,0,300)
histograms['mu_pT2'] = ROOT.TH1D("mu_pT2","",150,0,300)

histograms['mu_eta0'] = ROOT.TH1D("mu_eta0","",25,-2.5,2.5)
histograms['mu_eta1'] = ROOT.TH1D("mu_eta1","",25,-2.5,2.5)
histograms['mu_eta2'] = ROOT.TH1D("mu_eta2","",25,-2.5,2.5)

histograms['mu_phi0'] = ROOT.TH1D("mu_phi0","",16,-3.2,3.2)
histograms['mu_phi1'] = ROOT.TH1D("mu_phi1","",16,-3.2,3.2)
histograms['mu_phi2'] = ROOT.TH1D("mu_phi2","",16,-3.2,3.2)

histograms['Mass12_OS'] = ROOT.TH1D("Mass12_OS","",32,83,99)
histograms['Mass12_SS'] = ROOT.TH1D("Mass12_SS","",32,83,99)
histograms['mT'] = ROOT.TH1D("mT","",25,0,100)
histograms['m123'] = ROOT.TH1D("m123","",25,50,250)

histograms['WmupT'] = ROOT.TH1D("WmupT","",50,0,1000)
histograms['WmuPhi'] = ROOT.TH1D("WmuPhi","",80,-4,4)

histograms['WmNuDeltaPhi'] = ROOT.TH1D("WmNuDeltaPhi","",80,-4,4)
histograms['MET'] = ROOT.TH1D("PFMET","",100,0,2500)
histograms['METPhi'] = ROOT.TH1D("METPhi","",80,-4,4)

for sample in dataFiles:
    print "Running on sample", sample

    chain = ROOT.TChain("Events")

    print "Adding files to the chain"
    addfilesMany(chain, dataFiles[sample], "out_ana")

    for rootFile in chain.GetListOfFiles():
        
        ## loop on events in the ROOT file
        if (verbose): print "running on file ", rootFile.GetTitle()

        myfile = ROOT.TFile(rootFile.GetTitle())
        if (not myfile):
            if (verbose): print "File ", rootFile.GetTitle(), " does not exist"
            continue

        if (verbose): print "Loading directory cutFlowAnalyzerPXBL3PXFL2"
       
        tree = myfile.Get("cutFlowAnalyzerPXBL3PXFL2/Events")

        if not tree: 
            if (verbose): print "Tree cutFlowAnalyzerPXBL3PXFL2/Events does not exist"
            continue

        if (verbose): print "  Events  ", tree.GetEntries()

        nTriggers = 0
        for k in range(0, tree.GetEntries()):
            nTotalEvents += 1

            if nTotalEvents%1000==0: print "Processing event ", nTotalEvents  
            tree.GetEntry(k)
