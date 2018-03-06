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

datasets = ['WZTo3LNu', 'ZZTo4Mu','TTWJetsToLNu', 'TTZJetsToLNu', 'METData']

dataFiles = {}
dataFiles['WZTo3LNu'] = [
    #'/fdata/hepx/store/user/dildick/WZTo3LNu_0Jets_MLL-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_WZTo3LNu_0Jets_MLL_ANA_v10/180227_231545/0000/'
    '/fdata/hepx/store/user/dildick/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/crab_WZTo3LNu_Inclusive_ANA_v2/180227_231243/0000_backup/',
    '/fdata/hepx/store/user/dildick/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/crab_WZTo3LNu_Inclusive_ANA_v2/180227_231243/0001_backup/'
]
dataFiles['TTWJetsToLNu'] = [
    '/fdata/hepx/store/user/dildick/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_TTbarW_ANA_v1/180216_032728/0000_backup/'
]
dataFiles['TTZJetsToLNu'] = [
    '/fdata/hepx/store/user/dildick/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/crab_TTbarZ_ANA_v2/180221_004015/0000_backup/'
]
"""
dataFiles['ZZTo4Mu'] = [
    '/fdata/hepx/store/user/dildick/EWK_13TeV_CALCHEP_50K_batch1_GEN_SIM_v1_TAMU/crab_ZZTo4L_ANA_v6/180208_060822/0000/',
    '/fdata/hepx/store/user/dildick/EWK_13TeV_CALCHEP_50K_batch2_GEN_SIM_v3_TAMU/crab_ZZTo4L_ANA_v6_PartTwo/180208_060940/0000/'
]
dataFiles['METData'] = [
    '/home/dildick/DisplacedMuonJetAnalysis_2016/CMSSW_8_0_24/src/MuJetAnalysis/AnalysisRun2/scripts/HLTEfficiency/orthogonalMethod/'
]
"""


## define each chain for plotting purposes
chain_WZ = ROOT.TChain("Events")
addfilesMany(chain_WZ, dataFiles['WZTo3LNu'], "out_ana_clone")

chain_TTW = ROOT.TChain("Events")
addfilesMany(chain_TTW, dataFiles['TTWJetsToLNu'], "out_ana_clone")

chain_TTZ = ROOT.TChain("Events")
addfilesMany(chain_TTZ, dataFiles['TTZJetsToLNu'], "out_ana_clone")

file_Data = TFile("/home/dildick/DisplacedMuonJetAnalysis_2016/CMSSW_8_0_24/src/MuJetAnalysis/AnalysisRun2/scripts/HLTEfficiency/orthogonalMethod/out_ana_selected_MET_2016BH_20180208_clone.root")
chain_Data = file_Data.Get("Events")

file_ZZ = TFile("/fdata/hepx/store/user/dildick/EWK_13TeV_CALCHEP_50K_batch1_GEN_SIM_v1_TAMU/crab_ZZTo4L_ANA_v6/180208_060822/0000/out_ana_all_ZZ_TrigBranch.root")
chain_ZZ = file_ZZ.Get("Events")

chains = {}
chains['WZTo3LNu'] = chain_WZ
chains['ZZTo4Mu'] = chain_ZZ
chains['TTWJetsToLNu'] = chain_TTW
chains['TTZJetsToLNu'] = chain_TTZ
chains['METData'] = chain_Data

lumi = 35.9 #data processing penalty

WZ_xsec = 4430#fb#575
ZZ_xsec = 55.884#fb
TTW_xsec = 200.1 #fb
TTZ_xsec = 252.9 #fb

WZ_events = 18000000. #496684.
ZZ_events = 100000.
TTW_events = 3120397
TTZ_events = 5934228

def scaleWZ(hist):
    hist.Scale(lumi*WZ_xsec/WZ_events)

def scaleZZ(hist):
    hist.Scale(lumi*ZZ_xsec/ZZ_events)

def scaleTTW(hist):
    hist.Scale(lumi*TTW_xsec/TTW_events)

def scaleTTZ(hist):
    hist.Scale(lumi*TTZ_xsec/TTZ_events)

def scaleMET(hist):
    pass


def scaleSample(sample, hist):
    if sample is 'WZTo3LNu':
        hist.Scale(lumi*WZ_xsec/WZ_events)
    if sample is 'ZZTo4Mu':
        hist.Scale(lumi*ZZ_xsec/ZZ_events)
    if sample is 'TTWJetsToLNu':
        hist.Scale(lumi*TTW_xsec/TTW_events)
    if sample is 'TTZJetsToLNu':
        hist.Scale(lumi*TTZ_xsec/TTZ_events)
    if sample is 'METData':
        pass

## make the selection
nMuonCut = "int(selMu0_pT != -100) + int(selMu1_pT != -100) + int(selMu2_pT != -100) + int(selMu3_pT != -100) == 3"
ptMuonCut= "selMu0_pT > 10 && selMu1_pT > 10 && selMu2_pT > 10" 
muonTightCut = "isTight0 && isTight1 && isTight2"
muonDxyCut = "dxy0 < 0.01 && dxy1 < 0.01 && dxy2 < 0.01"
muonDzCut = "dz0 < 0.1 && dz1 < 0.1 && dz2 < 0.1"
muonIsoCut = "PFIso0 < 0.15 && PFIso1 < 0.15 && PFIso2 < 0.15"
OK_MET  = "OK_MET==1"
SS = 'selMu0_q == selMu1_q && selMu1_q == selMu2_q'
OS = '!(%s)'%SS

my_cut = (TCut(nMuonCut) + 
          TCut(ptMuonCut) + 
          TCut(muonTightCut) + 
          TCut(muonDxyCut) + 
          TCut(muonDzCut) + 
          TCut(muonIsoCut) + 
          TCut(OK_MET)
          )

variables = [
("selMu0_q",2,0,1),
("selMu1_q",2,0,1),
("selMu2_q",2,0,1),

("selMu0_pT",150,0,300),
("selMu1_pT",150,0,300),
("selMu2_pT",150,0,300),

("selMu0_px",150,0,300),
("selMu1_px",150,0,300),
("selMu2_px",150,0,300),

("selMu0_py",150,0,300),
("selMu1_py",150,0,300),
("selMu2_py",150,0,300),

("selMu0_pz",150,0,300),
("selMu1_pz",150,0,300),
("selMu2_pz",150,0,300),

("selMu0_phi",16,-3.2,3.2),
("selMu1_phi",16,-3.2,3.2),
("selMu2_phi",16,-3.2,3.2),

("selMu0_eta",25,-2.5,2.5),
("selMu1_eta",25,-2.5,2.5),
("selMu2_eta",25,-2.5,2.5),

("selMu0_isMedium",2,0,1),
("selMu1_isMedium",2,0,1),
("selMu2_isMedium",2,0,1),

("selMu0_isTight",2,0,1),
("selMu1_isTight",2,0,1),
("selMu2_isTight",2,0,1),

("selMu0_dxy",100,-10,10),
("selMu1_dxy",100,-10,10),
("selMu2_dxy",100,-10,10),

("selMu0_dz",160,-32,32),
("selMu1_dz",160,-32,32),
("selMu2_dz",160,-32,32),

("selMu0_PFIso",100,0,100),
("selMu1_PFIso",100,0,100),
("selMu2_PFIso",100,0,100),

("patMET",250,0,2500),
("patMET_phi",80,-4,4),
("nBJet_20",5,0,4),
]

def makePlot(histogram1,
             histogram2,
             histogram3, 
             histogram4,
             histogram5,
             x_label, y_label, saveAs, format='pdf'):

    ## setup histogram
    hist = HepPlotterDataMC()#"histogram"
    hist.x_relative_size = 10
    hist.y_relative_size = 7
    hist.drawEffDist = False    # draw the physics distribution for efficiency (jet_pt for jet trigger)
    #hist.rebin       = 1
    hist.x_label     = x_label# "Dimuon invariant mass"
    hist.y_label     = y_label
    hist.format      = format      # file format for saving image
    hist.saveDir     = 'trigger_efficiency_plots_2016Combined_WZ_20180305/'
    hist.saveAs      = saveAs# "Z_peak_2016MonteCarlo_WZ" # save figure with name
    hist.CMSlabel       = 'outer'  # 'top left', 'top right'; hack code for something else
    hist.CMSlabelStatus = 'Preliminary'  # ('Simulation')+'Internal' || 'Preliminary' 
    hist.initialize()
    hist.lumi = '2016 MET B-H, 35.9'
    hist.plotLUMI = True
    hist.Add(histogram3, name='ttW', sampleType='background')
    hist.Add(histogram4, name='ttZ', sampleType='background')
    hist.Add(histogram2, name='ZZto4Mu', sampleType='background')
    hist.Add(histogram1, name='WZto3Mu', sampleType='background')
    hist.Add(histogram5, name='data', sampleType='data')
    hist.drawStatUncertainty = True      # draw stat uncertainty separately
    hist.drawSystUncertainty = False     # draw syst uncertainty separately
    hist.drawStatSystUncertainty = False  # draw stat+syst uncertainty
    hist.blind       = False
    hist.ratio_plot  = False        # plot a ratio of things [Data/MC]
    hist.ratio_type  = "ratio"     # "ratio"
    hist.stacked     = True        # stack plots
    plot = hist.execute()
    hist.savefig()


## for each kinematic property, plot all contributions
for myvar in variables:
    
    bins = "(" + variables[myvar][0] + "," + variables[myvar][1] + "," variables[myvar][2] + ")" 
    chain_WZ.Draw(myvar + ">>h_WZ_" + myvar + bins, my_cut)
    chain_TTW.Draw(myvar + ">>h_TTW_" + myvar + bins, my_cut)
    chain_TTZ.Draw(myvar + ">>h_TTZ_" + myvar + bins, my_cut)
    chain_Data.Draw(myvar + ">>h_Data_" + myvar + bins, my_cut)
    chain_ZZ.Draw(myvar + ">>h_ZZ_" + myvar + bins, my_cut)

    h_WZ = TH1F(gDirectory.Get("h_WZ_" + myvar).Clone("h_WZ_" + myvar))
    h_ZZ = TH1F(gDirectory.Get("h_ZZ_" + myvar).Clone("h_ZZ_" + myvar))
    h_TTW = TH1F(gDirectory.Get("h_TTW_" + myvar).Clone("h_TTW_" + myvar))
    h_TTZ = TH1F(gDirectory.Get("h_TTZ_" + myvar).Clone("h_TTZ_" + myvar))
    h_Data = TH1F(gDirectory.Get("h_Data_" + myvar).Clone("h_Data_" + myvar))

    scaleWZ(h_WZ)
    scaleZZ(h_ZZ)
    scaleTTW(h_TTW)
    scaleTTZ(h_TTZ)

    makePlot(h_TTW, h_TTZ, h_ZZ, h_WZ, h_Data, r"Plot", "Entries", "Combine_" + myvar, format='pdf')
    
"""
exit(1)

histograms = {}

sample = 'WZTo3LNu'
## register histograms

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

            invm3 = inv3mass(mu0, mu1, mu2)
            nBJets_20 = tree.nBJet_20

            ## same sign or opposite sign muons?
            SS_or_OS = ''
            if q0 == q1 == q2: 
                SS_or_OS = 'SS' ## --- or +++
            else: 
                SS_or_OS = 'OS' ## ++- or --+

            histograms[sample + '_' + SS_or_OS + '_mu_pT0'].Fill(pt0)
            histograms[sample + '_' + SS_or_OS + '_mu_pT1'].Fill(pt1)
            histograms[sample + '_' + SS_or_OS + '_mu_pT2'].Fill(pt2)
            
            histograms[sample + '_' + SS_or_OS + '_mu_eta0'].Fill(abs(eta0))
            histograms[sample + '_' + SS_or_OS + '_mu_eta1'].Fill(abs(eta1))
            histograms[sample + '_' + SS_or_OS + '_mu_eta2'].Fill(abs(eta2))
            
            histograms[sample + '_' + SS_or_OS + '_mu_phi0'].Fill(phi0)
            histograms[sample + '_' + SS_or_OS + '_mu_phi1'].Fill(phi1)
            histograms[sample + '_' + SS_or_OS + '_mu_phi2'].Fill(phi2)
            
            histograms[sample + "_" + SS_or_OS + "_mu_dxy0"].Fill(dxy0)
            histograms[sample + "_" + SS_or_OS + "_mu_dxy1"].Fill(dxy1)
            histograms[sample + "_" + SS_or_OS + "_mu_dxy2"].Fill(dxy2)
            
            histograms[sample + "_" + SS_or_OS + "_mu_PFIso0"].Fill(PFIso0)
            histograms[sample + "_" + SS_or_OS + "_mu_PFIso1"].Fill(PFIso1)
            histograms[sample + "_" + SS_or_OS + "_mu_PFIso2"].Fill(PFIso2)
            
            histograms[sample + "_" + SS_or_OS + "_mu_dz0"].Fill(dz0)
            histograms[sample + "_" + SS_or_OS + "_mu_dz1"].Fill(dz1)
            histograms[sample + "_" + SS_or_OS + "_mu_dz2"].Fill(dz2)
            
            histograms[sample + "_" + SS_or_OS + "_mu_isMedium0"].Fill(isMedium0)
            histograms[sample + "_" + SS_or_OS + "_mu_isMedium1"].Fill(isMedium1)
            histograms[sample + "_" + SS_or_OS + "_mu_isMedium2"].Fill(isMedium2)
            
            histograms[sample + "_" + SS_or_OS + "_mu_isTight0"].Fill(isTight0)
            histograms[sample + "_" + SS_or_OS + "_mu_isTight1"].Fill(isTight1)
            histograms[sample + "_" + SS_or_OS + "_mu_isTight2"].Fill(isTight2)
            
            histograms[sample + "_" + SS_or_OS + "_mu_nBJets20"].Fill(nBJets_20)
            
            histograms[sample + "_" + SS_or_OS + "_m123"].Fill(invm3)
            histograms[sample + "_" + SS_or_OS + "_MET"].Fill(patMET)
            histograms[sample + "_" + SS_or_OS + "_METPhi"].Fill(patMET_phi)

            triggerPaths = ["HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx"]
            for trigger in triggerPaths:
                if any(trigger in s for s in list(tree.hltPaths)):
                    
                    histograms[sample + '_' + SS_or_OS + '_HLT_mu_pT0'].Fill(pt0)
                    histograms[sample + '_' + SS_or_OS + '_HLT_mu_pT1'].Fill(pt1)
                    histograms[sample + '_' + SS_or_OS + '_HLT_mu_pT2'].Fill(pt2)
                    
                    histograms[sample + '_' + SS_or_OS + '_HLT_mu_eta0'].Fill(abs(eta0))
                    histograms[sample + '_' + SS_or_OS + '_HLT_mu_eta1'].Fill(abs(eta1))
                    histograms[sample + '_' + SS_or_OS + '_HLT_mu_eta2'].Fill(abs(eta2))

                    histograms[sample + '_' + SS_or_OS + '_HLT_mu_phi0'].Fill(phi0)
                    histograms[sample + '_' + SS_or_OS + '_HLT_mu_phi1'].Fill(phi1)
                    histograms[sample + '_' + SS_or_OS + '_HLT_mu_phi2'].Fill(phi2)
                    
                #histograms[sample + "_" + SS_or_OS + "_Mass12"].Fill()
                #histograms[sample + "_" + SS_or_OS + "_mT"].Fill()
                
                #histograms[sample + "_" + SS_or_OS + "_WmupT"].Fill()
                #histograms[sample + "_" + SS_or_OS + "_WmuPhi"].Fill()
                
                #histograms[sample + "_" + SS_or_OS + "_WmNuDeltaPhi"].Fill()
                
            continue            
            ## case 2: same sign muons
            
            ## two muons should have same charge, one muon should have opposite charge (-++, --+)
            ## other options --- and +++ are not allowed!
            if q0 == q1 == q2: continue




            ## require 30 GeV MET from W decay
            #if patMET < 100: continue

            ## 3-lep inv mass
            if invm3 < 100: continue

            ## no b-jets with more than 20 GeV pT
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

    newtree.Print();
    newtree.AutoSave();
    #delete newfile;

    ## save histogram in a root file
    MyFile = TFile(sample + "_kinematics_13TeV.root","RECREATE");

    for SS in ['SS','OS']:
        histograms[sample + '_' + p + '_Eff_HLT_mu_pT0'] = TEfficiency(histograms[sample + '_' + p + '_HLT_mu_pT0'], 
                                                                       histograms[sample + '_' + p + '_mu_pT0'])
        histograms[sample + '_' + p + '_Eff_HLT_mu_pT1'] = TEfficiency(histograms[sample + '_' + p + '_HLT_mu_pT1'], 
                                                                       histograms[sample + '_' + p + '_mu_pT1'])
        histograms[sample + '_' + p + '_Eff_HLT_mu_pT2'] = TEfficiency(histograms[sample + '_' + p + '_HLT_mu_pT2'], 
                                                                       histograms[sample + '_' + p + '_mu_pT2'])
        
        histograms[sample + '_' + p + '_Eff_HLT_mu_eta0'] = TEfficiency(histograms[sample + '_' + p + '_HLT_mu_eta0'], 
                                                                        histograms[sample + '_' + p + '_mu_eta0'])
        histograms[sample + '_' + p + '_Eff_HLT_mu_eta1'] = TEfficiency(histograms[sample + '_' + p + '_HLT_mu_eta1'], 
                                                                        histograms[sample + '_' + p + '_mu_eta1'])
        histograms[sample + '_' + p + '_Eff_HLT_mu_eta2'] = TEfficiency(histograms[sample + '_' + p + '_HLT_mu_eta2'], 
                                                                        histograms[sample + '_' + p + '_mu_eta2'])
        
        histograms[sample + '_' + p + '_Eff_HLT_mu_phi0'] = TEfficiency(histograms[sample + '_' + p + '_HLT_mu_phi0'], 
                                                                        histograms[sample + '_' + p + '_mu_phi0'])
        histograms[sample + '_' + p + '_Eff_HLT_mu_phi1'] = TEfficiency(histograms[sample + '_' + p + '_HLT_mu_phi1'], 
                                                                        histograms[sample + '_' + p + '_mu_phi1'])
        histograms[sample + '_' + p + '_Eff_HLT_mu_phi2'] = TEfficiency(histograms[sample + '_' + p + '_HLT_mu_phi2'], 
                                                                        histograms[sample + '_' + p + '_mu_phi2'])

    for p in histograms:
        histograms[p].Write(p)
    
    MyFile.Close();



MyFile0 = TFile("WZTo3LNu_kinematics_13TeV.lpc.root","READ")
MyFile1 = TFile("ZZTo4Mu_kinematics_13TeV.lpc.root","READ")
MyFile2 = TFile("TTWJetsToLNu_kinematics_13TeV.root","READ")
MyFile3 = TFile("TTZJetsToLNu_kinematics_13TeV.lpc.root","READ")
MyFile4 = TFile("METData_kinematics_13TeV.lpc.root","READ")


for histo in mylist:
    for SS in ['OS','SS']:

        print SS + '_' + histo
        ## get each plot from file
        h0 = MyFile0.Get(datasets[0] + '_' + SS + '_' + histo)
        h1 = MyFile1.Get(datasets[1] + '_' + SS + '_' + histo)
        h2 = MyFile2.Get(datasets[2] + '_' + SS + '_' + histo)
        h3 = MyFile3.Get(datasets[3] + '_' + SS + '_' + histo)
        h4 = MyFile4.Get(datasets[4] + '_' + SS + '_' + histo)

        #print h0.GetMinimum(), h0.GetMaximum()
        #print h1.GetMinimum(), h1.GetMaximum()
        #print h2.GetMinimum(), h2.GetMaximum()
        #print h3.GetMinimum(), h3.GetMaximum()
        #print h4.GetMinimum(), h4.GetMaximum()

        #print type(h0)
        #print type(h1)
        #print type(h2)
        #print type(h3)
        #print type(h4)

        ## scale each histo
        scaleWZ(h0)
        scaleZZ(h1)
        scaleTTW(h2)
        scaleTTZ(h3)
        scaleMET(h4)

        print h0.GetMinimum(), h0.GetMaximum()

        makePlot(h0, h1, h2, h3, h4, r"Plot", "Entries", "Combine_" + SS + '_' + histo, format='pdf')
        
MyFile0.Close()
MyFile2.Close()
MyFile3.Close()
MyFile4.Close()
MyFile1.Close()
"""
