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

verbose = True

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
dataFiles['METData'] = [
    '/home/dildick/DisplacedMuonJetAnalysis_2016/CMSSW_8_0_24/src/MuJetAnalysis/AnalysisRun2/scripts/HLTEfficiency/orthogonalMethod/'
]
"""

sample  = 'TTZJetsToLNu'

print "Running on sample", sample
chain = ROOT.TChain("Events")

print "Adding files to the chain"
addfilesMany(chain, dataFiles[sample], "out_ana")

verbose = True

for rootFile in chain.GetListOfFiles():
    
    ## loop on events in the ROOT file
    if (verbose): print "running on file ", rootFile.GetTitle()
    
    myfile = ROOT.TFile(rootFile.GetTitle(), "UPDATE")

    if (not myfile):
        if (verbose): print "File ", rootFile.GetTitle(), " does not exist"
        continue

    if sample == 'METData':
        
        if not 'out_ana_selected_MET_2016BH_20180208' in rootFile.GetTitle():
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

    newtree = tree.CloneTree(0)
    OK_MET = numpy.zeros(1, dtype=int)
    OK_Signal = numpy.zeros(1, dtype=int)
    newtree.Branch( 'OK_MET', OK_MET, 'OK_MET/I' )
    newtree.Branch( 'OK_Signal', OK_Signal, 'OK_Signal/I' )

    for k in range(0, tree.GetEntries()):

        tree.GetEntry(k)
        if k%1000==0: print "Processing event ", k, "/",tree.GetEntries()

        OK_MET[0] = 0
        if wasMETTriggered(sample, MET_Triger_Patterns, tree):
            OK_MET[0] = 1

        OK_Signal[0] = 0
        if wasTriggered(tree):
            OK_Signal[0] = 1

        newtree.Fill()

    rootFile.Write()
    print "Saved tree with %d"  % ( tree.GetEntries() )

    """
    newTitle = rootFile.GetTitle()
    newTitle = newTitle.replace('out_ana','out_ana_clone')
    print newTitle
    newfile = TFile(newTitle, "recreate")

    newtree = tree.CloneTree();
    newfile.Write()
    newfile.Close()
    """
