import sys
from ROOT import *
from argparse import ArgumentParser

from hepPlotter import HepPlotter
from hepPlotterDataMC import HepPlotterDataMC
import hepPlotterTools as hpt
#import hepPlotterLabels as hpl
import math as m
import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from Helpers import *

## mass of the muon in GeV
mmu = 105.6583745 * 0.001
mZ = 91.1876

verbose = True

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

def bestMassInZPeak(m1, m2):
    masses = [m1, m2]
    massdiffs = [abs(m1-mZ), abs(m2-mZ)]
    index = massdiffs.index(min(massdiffs))
    return masses[index]

def wasTriggered(tree):
    ## was triggered?
    return any('HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx' in s for s in list(tree.hltPaths))

MET_Triger_Patterns = [
    'HLT_MonoCentralPFJet80_PFMETNoMu110_PFMHTNoMu110_IDTight',
    'HLT_MET75_IsoTrk50',
    'HLT_MonoCentralPFJet80_PFMETNoMu90_PFMHTNoMu90_IDTight',
    'HLT_PFMET100_PFMHT100_IDTight',
    'HLT_MET200',
    'HLT_PFMET170_BeamHaloCleaned',
    'HLT_PFMET120_PFMHT120_IDTight',
    'HLT_Photon50_R9Id90_HE10_Iso40_EBOnly_PFMET40',
    'HLT_PFMET170_NotCleaned',
    'HLT_PFMET600',
    'HLT_PFMETNoMu120_PFMHTNoMu120_IDTight',
    'HLT_CaloMHTNoPU90_PFMET90_PFMHT90_IDTight',
    'HLT_LooseIsoPFTau50_Trk30_eta2p1_MET90',
    'HLT_PFMET110_PFMHT110_IDTight',
    'HLT_CaloMHTNoPU90_PFMET90_PFMHT90_IDTight_BTagCSV_p067',
    'HLT_MonoCentralPFJet80_PFMETNoMu100_PFMHTNoMu100_IDTight',
    'HLT_Photon120_R9Id90_HE10_Iso40_EBOnly_PFMET40',
    'HLT_MET90_IsoTrk50',
    'HLT_PFMETNoMu90_PFMHTNoMu90_IDTight',
    'HLT_PFMET170_JetIdCleaned',
    'HLT_MET300',
    'HLT_PFMET90_PFMHT90_IDTight',
    'HLT_Photon22_R9Id90_HE10_Iso40_EBOnly_PFMET40',
    'HLT_LooseIsoPFTau50_Trk30_eta2p1_MET80',
    'HLT_PFHT300_PFMET100',
    'HLT_PFMET300',
    'HLT_DiPFJet40_DEta3p5_MJJ600_PFMETNoMu140',
    'HLT_PFMET100_PFMHT100_IDTight_BeamHaloCleaned',
    'HLT_DiPFJet40_DEta3p5_MJJ600_PFMETNoMu80',
    'HLT_PFHT300_PFMET110',
    'HLT_MET250',
    'HLT_LooseIsoPFTau50_Trk30_eta2p1_MET120',
    'HLT_PFMET170_HBHE_BeamHaloCleaned',
    'HLT_Photon135_PFMET100',
    'HLT_Ele15_IsoVVVL_PFHT400_PFMET50',
    'HLT_PFMETNoMu110_PFMHTNoMu110_IDTight',
    'HLT_Photon36_R9Id90_HE10_Iso40_EBOnly_PFMET40',
    'HLT_DiCentralPFJet55_PFMET110',
    'HLT_Ele15_IsoVVVL_PFHT350_PFMET50',
    'HLT_MET60_IsoTrk35_Loose',
    'HLT_PFMETNoMu100_PFMHTNoMu100_IDTight',
    'HLT_PFMETTypeOne190_HBHE_BeamHaloCleaned',
    'HLT_PFMET400',
    'HLT_LooseIsoPFTau50_Trk30_eta2p1_MET110',
    'HLT_MonoCentralPFJet80_PFMETNoMu120_PFMHTNoMu120_IDTight',
    'HLT_PFMET500',
    'HLT_PFMET170_HBHECleaned',
    'HLT_MET600',
    'HLT_PFMET120_BTagCSV_p067',
    'HLT_Photon90_R9Id90_HE10_Iso40_EBOnly_PFMET40',
    'HLT_MET700',
    'HLT_Photon75_R9Id90_HE10_Iso40_EBOnly_PFMET40',
    'HLT_PFMET170_NoiseCleaned',
    ]

def wasMETTriggered(sample, MET_Triger_Patterns, tree):
    if sample is not 'METData':
        for s in MET_Triger_Patterns:
            for p in list(tree.hltPaths):
                if s in p:
                    return True
    ## MET Data
    else:
        return True
    ## Non-triggered MC
    return False


dataFiles = {}
dataFiles['WZTo3LNu'] = [
    '/fdata/hepx/store/user/dildick/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/crab_WZTo3LNu_Inclusive_ANA_v2/180227_231243/0000_backup/',
    '/fdata/hepx/store/user/dildick/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/crab_WZTo3LNu_Inclusive_ANA_v2/180227_231243/0001_backup/'
]
dataFiles['TTWJetsToLNu'] = [
    '/fdata/hepx/store/user/dildick/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_TTbarW_ANA_v1/180216_032728/0000_backup/'
]
dataFiles['TTZJetsToLNu'] = [
    '/home/dildick/DisplacedMuonJetAnalysis_2016/CMSSW_8_0_24/src/MuJetAnalysis/AnalysisRun2/scripts/HLTEfficiency/'
    #'/fdata/hepx/store/user/dildick/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/crab_TTbarZ_ANA_v2/180221_004015/0000_backup/'
]
"""
dataFiles['ZZTo4Nu'] = [
    '/fdata/hepx/store/user/dildick/EWK_13TeV_CALCHEP_50K_batch1_GEN_SIM_v1_TAMU/crab_ZZTo4L_ANA_v6/180208_060822/0000/',
    '/fdata/hepx/store/user/dildick/EWK_13TeV_CALCHEP_50K_batch2_GEN_SIM_v3_TAMU/crab_ZZTo4L_ANA_v6_PartTwo/180208_060940/0000/'
]
"""
dataFiles['METData'] = [
    '/home/dildick/DisplacedMuonJetAnalysis_2016/CMSSW_8_0_24/src/MuJetAnalysis/AnalysisRun2/scripts/HLTEfficiency/orthogonalMethod/'
]


sample  = 'METData'

print "Running on sample", sample
chain = ROOT.TChain("Events")

print "Adding files to the chain"
addfilesMany(chain, dataFiles[sample], "out_ana")

verbose = True

for rootFile in chain.GetListOfFiles():
    
    ## loop on events in the ROOT file
    if (verbose): print "running on file ", rootFile.GetTitle()
    
    myfile = ROOT.TFile(rootFile.GetTitle())

    if (not myfile):
        if (verbose): print "File ", rootFile.GetTitle(), " does not exist"
        continue

    if sample == 'METData':
        
        if not 'out_ana_selected_MET_2016BH_20180307.root' in rootFile.GetTitle():
            continue
        else: 
            if (verbose): print "Loading tree Events"
            tree = myfile.Get("Events")
    else:                
        if (verbose): print "Loading directory cutFlowAnalyzerPXBL3PXFL2"           
        tree = myfile.Get("cutFlowAnalyzerPXBL3PXFL2/Events")
        
    if not tree: 
        if (verbose): print "Tree cutFlowAnalyzerPXBL3PXFL2/Events does not exist"
        continue

    #gDirectory.Cd("cutFlowAnalyzerPXBL3PXFL2")


    newTitle = rootFile.GetTitle()
    newTitle = newTitle.replace('root','dimuonMass.root')
    newfile = ROOT.TFile(newTitle,  "RECREATE")

    newtree = tree.CloneTree(0)
    OK_MET = numpy.zeros(1, dtype=int)
    OK_Signal = numpy.zeros(1, dtype=int)
    best_OS_dimuon_mass = numpy.zeros(1, dtype=float)
    best_SS_dimuon_mass = numpy.zeros(1, dtype=float)
    m123 = numpy.zeros(1, dtype=float)

    newtree.Branch( 'OK_MET', OK_MET, 'OK_MET/I')
    newtree.Branch( 'OK_Signal', OK_Signal, 'OK_Signal/I')
    newtree.Branch( 'best_OS_dimuon_mass', best_OS_dimuon_mass, 'best_OS_dimuon_mass/D')
    newtree.Branch( 'best_SS_dimuon_mass', best_SS_dimuon_mass, 'best_SS_dimuon_mass/D')
    newtree.Branch( 'm123', m123, 'm123/D')

    for k in range(0, tree.GetEntries()):

        tree.GetEntry(k)
        if k%1000==0: print "Processing event ", k, "/",tree.GetEntries()

        q0 = tree.selMu0_q
        q1 = tree.selMu1_q
        q2 = tree.selMu2_q

        px0 = tree.selMu0_px
        px1 = tree.selMu1_px
        px2 = tree.selMu2_px
        
        py0 = tree.selMu0_py
        py1 = tree.selMu1_py
        py2 = tree.selMu2_py
        
        pz0 = tree.selMu0_pz
        pz1 = tree.selMu1_pz
        pz2 = tree.selMu2_pz

        E0 = energy(mmu, px0, py0, pz0) 
        E1 = energy(mmu, px1, py1, pz1)
        E2 = energy(mmu, px2, py2, pz2)

        mu0 = [E0, px0, py0, pz0]
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

        #print  best_OS_dimuon_mass[0], best_SS_dimuon_mass[0]

        OK_MET[0] = 0
        if wasMETTriggered(sample, MET_Triger_Patterns, tree):
            OK_MET[0] = 1

        OK_Signal[0] = 0
        if wasTriggered(tree):
            OK_Signal[0] = 1

        newtree.Fill()

    rootFile.Write()
    print "Saved tree with %d"  % ( tree.GetEntries() )
    newfile.Close()

    """
    newTitle = rootFile.GetTitle()
    newTitle = newTitle.replace('out_ana','out_ana_clone')
    print newTitle
    newfile = TFile(newTitle, "recreate")

    newtree = tree.CloneTree();
    newfile.Write()
    newfile.Close()
    """
