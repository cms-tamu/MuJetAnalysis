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
verbose = False

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

dataFiles = {}
"""
dataFiles['WZTo3LNu'] = [
    '/fdata/hepx/store/user/dildick/WZTo3LNu_0Jets_MLL-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_WZTo3LNu_0Jets_MLL_ANA_v10/180227_231545/0000/'
    #    '/fdata/hepx/store/user/dildick/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/crab_WZTo3LNu_Inclusive_ANA_v1/180216_034648/0000/',
    #    '/fdata/hepx/store/user/dildick/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/crab_WZTo3LNu_Inclusive_ANA_v1/180216_034648/0001/'
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
"""
dataFiles['METData'] = [
    '/home/dildick/DisplacedMuonJetAnalysis_2016/CMSSW_8_0_24/src/MuJetAnalysis/AnalysisRun2/scripts/HLTEfficiency/orthogonalMethod/'
]

histograms = {}

for sample in dataFiles:

    ## register histograms
    for SS in ['SS','OS']:
        histograms[sample + "_" + p + "_mu_pT0"] = ROOT.TH1D(sample + "_" + p + "_mu_pT0","",150,0,300)
        histograms[sample + "_" + p + "_mu_pT1"] = ROOT.TH1D(sample + "_" + p + "_mu_pT1","",150,0,300)
        histograms[sample + "_" + p + "_mu_pT2"] = ROOT.TH1D(sample + "_" + p + "_mu_pT2","",150,0,300)

        histograms[sample + "_" + p + "_mu_eta0"] = ROOT.TH1D(sample + "_" + p + "_mu_eta0","",25,-2.5,2.5)
        histograms[sample + "_" + p + "_mu_eta1"] = ROOT.TH1D(sample + "_" + p + "_mu_eta1","",25,-2.5,2.5)
        histograms[sample + "_" + p + "_mu_eta2"] = ROOT.TH1D(sample + "_" + p + "_mu_eta2","",25,-2.5,2.5)
        
        histograms[sample + "_" + p + "_mu_phi0"] = ROOT.TH1D(sample + "_" + p + "_mu_phi0","",16,-3.2,3.2)
        histograms[sample + "_" + p + "_mu_phi1"] = ROOT.TH1D(sample + "_" + p + "_mu_phi1","",16,-3.2,3.2)
        histograms[sample + "_" + p + "_mu_phi2"] = ROOT.TH1D(sample + "_" + p + "_mu_phi2","",16,-3.2,3.2)

        histograms[sample + "_" + p + "_HLT_mu_pT0"] = ROOT.TH1D(sample + "_" + p + "_HLT_mu_pT0","",150,0,300)
        histograms[sample + "_" + p + "_HLT_mu_pT1"] = ROOT.TH1D(sample + "_" + p + "_HLT_mu_pT1","",150,0,300)
        histograms[sample + "_" + p + "_HLT_mu_pT2"] = ROOT.TH1D(sample + "_" + p + "_HLT_mu_pT2","",150,0,300)
        
        histograms[sample + "_" + p + "_HLT_mu_eta0"] = ROOT.TH1D(sample + "_" + p + "_HLT_mu_eta0","",25,-2.5,2.5)
        histograms[sample + "_" + p + "_HLT_mu_eta1"] = ROOT.TH1D(sample + "_" + p + "_HLT_mu_eta1","",25,-2.5,2.5)
        histograms[sample + "_" + p + "_HLT_mu_eta2"] = ROOT.TH1D(sample + "_" + p + "_HLT_mu_eta2","",25,-2.5,2.5)
        
        histograms[sample + "_" + p + "_HLT_mu_phi0"] = ROOT.TH1D(sample + "_" + p + "_HLT_mu_phi0","",16,-3.2,3.2)
        histograms[sample + "_" + p + "_HLT_mu_phi1"] = ROOT.TH1D(sample + "_" + p + "_HLT_mu_phi1","",16,-3.2,3.2)
        histograms[sample + "_" + p + "_HLT_mu_phi2"] = ROOT.TH1D(sample + "_" + p + "_HLT_mu_phi2","",16,-3.2,3.2)
        
        histograms[sample + "_" + p + "_Mass12"] = ROOT.TH1D(sample + "_" + p + "_Mass12","",32,83,99)
        histograms[sample + "_" + p + "_mT"] = ROOT.TH1D(sample + "_" + p + "_mT","",25,0,100)
        histograms[sample + "_" + p + "_m123"] = ROOT.TH1D(sample + "_" + p + "_m123","",25,50,250)
        
        histograms[sample + "_" + p + "_WmupT"] = ROOT.TH1D(sample + "_" + p + "_WmupT","",50,0,1000)
        histograms[sample + "_" + p + "_WmuPhi"] = ROOT.TH1D(sample + "_" + p + "_WmuPhi","",80,-4,4)
        
        histograms[sample + "_" + p + "_WmNuDeltaPhi"] = ROOT.TH1D(sample + "_" + p + "_WmNuDeltaPhi","",80,-4,4)
        histograms[sample + "_" + p + "_MET"] = ROOT.TH1D(sample + "_" + p + "_PFMET","",100,0,2500)
        histograms[sample + "_" + p + "_METPhi"] = ROOT.TH1D(sample + "_" + p + "_METPhi","",80,-4,4)
        

    print "Running on sample", sample
    chain = ROOT.TChain("Events")
    
    print "Adding files to the chain"
    addfilesMany(chain, dataFiles[sample], "out_ana")
    
    nTotalEvents = 0
    nTotalEvents4Mu = 0
    nEventsPreSelected = 0
    nEventsMETTriggered = 0
    nEventsSelected = 0
    nEventsTriggered = 0

    for rootFile in chain.GetListOfFiles():
        
        ## loop on events in the ROOT file
        if (verbose): print "running on file ", rootFile.GetTitle()

        myfile = ROOT.TFile(rootFile.GetTitle())
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

        if (verbose): print "  Events  ", tree.GetEntries()

        nTriggers = 0
        if nTotalEvents > 1000 and False: 
            break

        for k in range(0, tree.GetEntries()):
            nTotalEvents += 1

            if nTotalEvents%10000==0: print "Processing event ", nTotalEvents  
            tree.GetEntry(k)
            
                        ## check for 4 reco muons 
            nMu = 0
            
            if tree.selMu0_pT != -100: nMu += 1
            if tree.selMu1_pT != -100: nMu += 1
            if tree.selMu2_pT != -100: nMu += 1
            if tree.selMu3_pT != -100: nMu += 1

            if (nMu==4):
                nTotalEvents4Mu += 1

            if (nMu!=3):
                continue

            isMETTriggered = False
            MET_Triger_Patterns = [
                'HLT_PFHT300_PFMET100',
                'HLT_PFHT300_PFMET110',
                'HLT_PFMET120_BTagCSV_p067',
                'HLT_PFMETTypeOne190_HBHE_BeamHaloCleaned',
                'HLT_PFMET90_PFMHT90_IDTight',
                'HLT_PFMET100_PFMHT100_IDTight',
                'HLT_PFMET100_PFMHT100_IDTight_BeamHaloCleaned'
                'HLT_PFMET110_PFMHT110_IDTight',
                'HLT_PFMET120_PFMHT120_IDTight',
                'HLT_CaloMHTNoPU90_PFMET90_PFMHT90_IDTight_BTagCSV_p067',
                'HLT_CaloMHTNoPU90_PFMET90_PFMHT90_IDTight',
                'HLT_PFMETNoMu90_PFMHTNoMu90_IDTight',
                'HLT_PFMETNoMu100_PFMHTNoMu100_IDTight',
                'HLT_PFMETNoMu110_PFMHTNoMu110_IDTight',
                'HLT_PFMETNoMu120_PFMHTNoMu120_IDTight',
                'HLT_MonoCentralPFJet80_PFMETNoMu90_PFMHTNoMu90_IDTight',
                'HLT_MonoCentralPFJet80_PFMETNoMu100_PFMHTNoMu100_IDTight',
                'HLT_MonoCentralPFJet80_PFMETNoMu110_PFMHTNoMu110_IDTight',
                'HLT_MonoCentralPFJet80_PFMETNoMu120_PFMHTNoMu120_IDTight',
                'HLT_DiPFJet40_DEta3p5_MJJ600_PFMETNoMu140',
                'HLT_DiPFJet40_DEta3p5_MJJ600_PFMETNoMu80',
                'HLT_PFMET170_NotCleaned',
                'HLT_PFMET170_NoiseCleaned',
                'HLT_PFMET170_HBHECleaned',
                'HLT_PFMET170_JetIdCleaned',
                'HLT_PFMET170_BeamHaloCleaned',
                'HLT_PFMET170_HBHE_BeamHaloCleaned',
                'HLT_PFMETTypeOne190_HBHE_BeamHaloCleaned',
                'HLT_PFMET90_PFMHT90_IDTight',
                'HLT_PFMET100_PFMHT100_IDTight',
                'HLT_PFMET100_PFMHT100_IDTight_BeamHaloCleaned',
                'HLT_PFMET110_PFMHT110_IDTight',
                'HLT_PFMET120_PFMHT120_IDTight',
                'HLT_CaloMHTNoPU90_PFMET90_PFMHT90_IDTight',
                'HLT_PFMETNoMu90_PFMHTNoMu90_IDTight',
                'HLT_PFMETNoMu100_PFMHTNoMu100_IDTight',
                'HLT_PFMETNoMu110_PFMHTNoMu110_IDTight',
                'HLT_PFMETNoMu120_PFMHTNoMu120_IDTight',
                'HLT_MonoCentralPFJet80_PFMETNoMu90_PFMHTNoMu90_IDTight',
                'HLT_MonoCentralPFJet80_PFMETNoMu100_PFMHTNoMu100_IDTight',
                'HLT_MonoCentralPFJet80_PFMETNoMu110_PFMHTNoMu110_IDTight',
                'HLT_MonoCentralPFJet80_PFMETNoMu120_PFMHTNoMu120_IDTight',
                'HLT_PFMET300',
                'HLT_PFMET400',
                ]

            for s in list(tree.hltPaths):
                #print s, "is available"
                if 'PFMET' in s and 'HLT_' in s: 
                    isMETTriggered = True
                    #print "\t", s, "was MET triggered"
                
            if not isMETTriggered:
                continue

            q0 = tree.selMu0_q
            q1 = tree.selMu1_q
            q2 = tree.selMu2_q
            
            ## case 1: opposite sign muons
            
            
            ## case 2: same sign muons
            

            ## two muons should have same charge, one muon should have opposite charge (-++, --+)
            ## other options --- and +++ are not allowed!
            if q0 == q1 == q2: continue

            pt0 = tree.selMu0_pT
            pt1 = tree.selMu1_pT
            pt2 = tree.selMu2_pT

            px0 = tree.selMu0_px
            px1 = tree.selMu1_px
            px2 = tree.selMu2_px

            py0 = tree.selMu0_py
            py1 = tree.selMu1_py
            py2 = tree.selMu2_py

            pz0 = tree.selMu0_pz
            pz1 = tree.selMu1_pz
            pz2 = tree.selMu2_pz

            phi0 = tree.selMu0_phi
            phi1 = tree.selMu1_phi
            phi2 = tree.selMu2_phi

            eta0 = tree.selMu0_eta
            eta1 = tree.selMu1_eta
            eta2 = tree.selMu2_eta

            isMedium0 = tree.selMu0_isMedium
            isMedium1 = tree.selMu1_isMedium
            isMedium2 = tree.selMu2_isMedium

            isTight0 = tree.selMu0_isTight
            isTight1 = tree.selMu1_isTight
            isTight2 = tree.selMu2_isTight

            ## high quality muons
            if not isTight0: continue
            if not isTight1: continue
            if not isTight2: continue

            dxy0 = tree.selMu0_dxy
            dxy1 = tree.selMu1_dxy
            dxy2 = tree.selMu2_dxy

            ## prom1pt muons!
            if dxy0 > 0.01: continue
            if dxy1 > 0.01: continue
            if dxy2 > 0.01: continue

            dz0 = tree.selMu0_dz
            dz1 = tree.selMu1_dz
            dz2 = tree.selMu2_dz

            if dz0 > 0.1: continue
            if dz1 > 0.1: continue
            if dz2 > 0.1: continue

            PFIso0 = tree.selMu0_PFIso
            PFIso1 = tree.selMu1_PFIso
            PFIso2 = tree.selMu2_PFIso

            ## require tight isolation on all muons
            if PFIso0 > 0.15: continue
            if PFIso1 > 0.15: continue
            if PFIso2 > 0.15: continue

            patMET = tree.patMET
            patMET_phi = tree.patMET_phi
            #print "PATMET", patMET, patMET_phi

            ## calculate the energies
            E0 = energy(mmu, px0, py0, pz0) 
            E1 = energy(mmu, px1, py1, pz1)
            E2 = energy(mmu, px2, py2, pz2)

            if (verbose):
                print E0, px0, py0, pz0, q0, phi0
                print E1, px1, py1, pz1, q1, phi1
                print E2, px2, py2, pz2, q2, phi2

            ## declare the four vectors
            mu0 = [E0, px0, py0, pz0, phi0, eta0]
            mu1 = [E1, px1, py1, pz1, phi1, eta1]
            mu2 = [E2, px2, py2, pz2, phi2, eta2]

            numberOfMuonPairs = 0
            if q0 * q1 < 0: numberOfMuonPairs += 1
            if q1 * q2 < 0: numberOfMuonPairs += 1
            if q0 * q2 < 0: numberOfMuonPairs += 1

            if (verbose):
                print "numberOfMuonPairs", numberOfMuonPairs

            ## require 30 GeV MET from W decay
            if patMET < 100: continue

            ## 3-lep inv mass
            invm3 = inv3mass(mu0, mu1, mu2)
            if invm3 < 100: continue

            ## no b-jets with more than 20 GeV pT
            nBJets_20 = tree.nBJet_20
            #print "nBJets_20", nBJets_20
            if nBJets_20 >=1: continue;

            ## calculate the same sign mass and opposite sign masses
            SS_dimuon_mass = 0
            OS_dimuon_mass1 = 0
            OS_dimuon_mass2 = 0

            Zmumu = ()
            Wmu = [0,0,0,0]
            if q0 * q1 > 0: 
                SS_dimuon_mass = invmass(mu0, mu1)
                OS_dimuon_mass1 = invmass(mu1, mu2)
                OS_dimuon_mass2 = invmass(mu0, mu2)
                OS_dimuon_mass = bestMassInZPeak(OS_dimuon_mass1, OS_dimuon_mass2)
                if OS_dimuon_mass == OS_dimuon_mass1:
                    Zmumu = (mu1, mu2)
                    Wmu = mu0
                    
                if OS_dimuon_mass == OS_dimuon_mass2:
                    Zmumu = (mu0, mu2)
                    Wmu = mu1

            elif q0 * q2 > 0: 
                SS_dimuon_mass = invmass(mu0, mu2)
                OS_dimuon_mass1 = invmass(mu0, mu1)
                OS_dimuon_mass2 = invmass(mu1, mu2)
                OS_dimuon_mass = bestMassInZPeak(OS_dimuon_mass1, OS_dimuon_mass2)
                if OS_dimuon_mass == OS_dimuon_mass1:
                    Zmumu = (mu0, mu1)
                    Wmu = mu2
                    
                if OS_dimuon_mass == OS_dimuon_mass2:
                    Zmumu = (mu1, mu2)
                    Wmu = mu0

            elif q1 * q2 > 0: 
                SS_dimuon_mass = invmass(mu1, mu2)
                OS_dimuon_mass1 = invmass(mu0, mu1)
                OS_dimuon_mass2 = invmass(mu0, mu2)
                OS_dimuon_mass = bestMassInZPeak(OS_dimuon_mass1, OS_dimuon_mass2)
                if OS_dimuon_mass == OS_dimuon_mass1:
                    Zmumu = (mu0, mu1)
                    Wmu = mu2
                    
                if OS_dimuon_mass == OS_dimuon_mass2:
                    Zmumu = (mu0, mu2)
                    Wmu = mu1

            else: 
                SS_dimuon_mass = 0
                OS_dimuon_mass1 = 0
                OS_dimuon_mass2 = 0
                OS_dimuon_mass = 0
                Zmumu = ()
                Wmu = [0,0,0,0]

            ## The invariant mass of any same-flavor dimuon 
            ## pair must be greater than 4 GeV
            if q0 * q1 > 0 and invmass(mu0, mu1) < 4: continue
            if q0 * q2 > 0 and invmass(mu0, mu2) < 4: continue
            if q1 * q2 > 0 and invmass(mu1, mu2) < 4: continue

            nMassesInZPeak = int(isMassInZPeak(OS_dimuon_mass))

            ## require at least one dimuon pair to be consistent with the Z pole mass 
            if nMassesInZPeak==0: continue

            ## apply selections on the Z pair
            Zmu0_pT = getPT(Zmumu[0])
            Zmu1_pT = getPT(Zmumu[1])
            Wmu_pT = getPT(Wmu)
            
            ## require all muons have minimum 10 GeV pT
            if Zmu0_pT<10: continue
            if Zmu1_pT<10: continue
            if Wmu_pT<10: continue
            
            ## require one of the Z boson muons to have at least 20 GeV pT
            if not (Zmu0_pT > 20 or Zmu1_pT > 20): continue

            ## require the W boson muon to have at least 20 GeV pT
            if Wmu_pT < 20: continue

            ## apply a quality criterium on the transverse mass cut
            Wmu_phi = normalizePhi(getPhi(Wmu))
            Wmu_nu_deltaPhi = deltaPhi(Wmu_phi, normalizePhi(patMET_phi))
            transverseWbosonMass = m.sqrt(2*Wmu_pT*patMET*(1-m.cos(Wmu_nu_deltaPhi)))
            if (verbose):
                print "transverseWbosonMass", transverseWbosonMass
            ## remove the contamination from W+jets in the sample!
            #if transverseWbosonMass > 20: continue

            histograms[sample + '_mu_pT0'].Fill(pt0)
            histograms[sample + '_mu_pT1'].Fill(pt1)
            histograms[sample + '_mu_pT2'].Fill(pt2)
            
            histograms[sample + '_mu_eta0'].Fill(abs(eta0))
            histograms[sample + '_mu_eta1'].Fill(abs(eta1))
            histograms[sample + '_mu_eta2'].Fill(abs(eta2))
            
            histograms[sample + '_mu_phi0'].Fill(phi0)
            histograms[sample + '_mu_phi1'].Fill(phi1)
            histograms[sample + '_mu_phi2'].Fill(phi2)

            histograms[sample + '_Mass12'].Fill(OS_dimuon_mass)
            histograms[sample + '_mT'].Fill(transverseWbosonMass)
            histograms[sample + '_m123'].Fill(invm3)
            
            histograms[sample + '_WmupT'].Fill(Wmu_pT)
            histograms[sample + '_WmuPhi'].Fill(Wmu_phi)
            
            histograms[sample + '_WmNuDeltaPhi'].Fill(Wmu_nu_deltaPhi)
            histograms[sample + '_MET'].Fill(patMET)
            histograms[sample + '_METPhi'].Fill(patMET_phi)

            ## was triggered?
            isTriggered = False
            triggerPaths = ["HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx"]
            for trigger in triggerPaths:
                if (verbose): print list(tree.hltPaths)
                if any(trigger in s for s in list(tree.hltPaths)):
                    if (verbose): print trigger, "is available"
                    nEventsTriggered += 1
                    isTriggered = True

            if isTriggered:
                histograms[sample + '_HLT_mu_pT0'].Fill(pt0)
                histograms[sample + '_HLT_mu_pT1'].Fill(pt1)
                histograms[sample + '_HLT_mu_pT2'].Fill(pt2)
                
                histograms[sample + '_HLT_mu_eta0'].Fill(abs(eta0))
                histograms[sample + '_HLT_mu_eta1'].Fill(abs(eta1))
                histograms[sample + '_HLT_mu_eta2'].Fill(abs(eta2))

                histograms[sample + '_HLT_mu_phi0'].Fill(phi0)
                histograms[sample + '_HLT_mu_phi1'].Fill(phi1)
                histograms[sample + '_HLT_mu_phi2'].Fill(phi2)

    ## save histogram in a root file
    MyFile = TFile("HLT_Z_peak_combined_dataVsMC_MET_WZ_ZZ_ttZ_ttW_13TeV.root","UPDATE");

    histograms[sample + '_Eff_HLT_mu_pT0'] = TEfficiency(histograms[sample + '_HLT_mu_pT0'], histograms[sample + '_mu_pT0'])
    histograms[sample + '_Eff_HLT_mu_pT1'] = TEfficiency(histograms[sample + '_HLT_mu_pT1'], histograms[sample + '_mu_pT1'])
    histograms[sample + '_Eff_HLT_mu_pT2'] = TEfficiency(histograms[sample + '_HLT_mu_pT2'], histograms[sample + '_mu_pT2'])

    histograms[sample + '_Eff_HLT_mu_eta0'] = TEfficiency(histograms[sample + '_HLT_mu_eta0'], histograms[sample + '_mu_eta0'])
    histograms[sample + '_Eff_HLT_mu_eta1'] = TEfficiency(histograms[sample + '_HLT_mu_eta1'], histograms[sample + '_mu_eta1'])
    histograms[sample + '_Eff_HLT_mu_eta2'] = TEfficiency(histograms[sample + '_HLT_mu_eta2'], histograms[sample + '_mu_eta2'])

    histograms[sample + '_Eff_HLT_mu_phi0'] = TEfficiency(histograms[sample + '_HLT_mu_phi0'], histograms[sample + '_mu_phi0'])
    histograms[sample + '_Eff_HLT_mu_phi1'] = TEfficiency(histograms[sample + '_HLT_mu_phi1'], histograms[sample + '_mu_phi1'])
    histograms[sample + '_Eff_HLT_mu_phi2'] = TEfficiency(histograms[sample + '_HLT_mu_phi2'], histograms[sample + '_mu_phi2'])

    for p in histograms:
        histograms[p].Write(p)
    
    MyFile.Close();
