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

##____________________________________________________________
def efficiency_trigger(dirNames, triggerPaths):

    verbose = False

    chain = ROOT.TChain("Events")

    print "Preparing histograms"

    Invariant_Mass12 = ROOT.TH1D("Invariant_Mass12","",60,76,106)
    Transverse_Mass = ROOT.TH1D("Transverse_Mass","",250,0,500)
    Invariant_Mass123 = ROOT.TH1D("Invariant_Mass123","",25,50,250)
    PFMET = ROOT.TH1D("PFMET","",100,0,2500)
    WmupT = ROOT.TH1D("WmupT","",50,0,1000)
    WmuPhi = ROOT.TH1D("WmuPhi","",80,-4,4)
    WmNuDeltaPhi = ROOT.TH1D("WmNuDeltaPhi","",80,-4,4)
    METPhi = ROOT.TH1D("METPhi","",80,-4,4)

    leading_muon_eta = ROOT.TH1D("leading_muon_eta","",24,0,2.4)
    trig_leading_muon_eta = ROOT.TH1D("trig_leading_muon_eta","",24,0,2.4)
    leading_muon_phi = ROOT.TH1D("leading_muon_phi","",32,-3.2,3.2)
    trig_leading_muon_phi = ROOT.TH1D("trig_leading_muon_phi","",32,-3.2,3.2)
    leading_muon_pt = ROOT.TH1D("leading_muon_pt","",40,10,110)
    trig_leading_muon_pt = ROOT.TH1D("trig_leading_muon_pt","",40,10,110)

    print "Adding files to the chain"
    addfilesMany(chain, dirNames, "out_ana")
                                   
    print "Loop over the chain"
    nEventsWith2MassInZPeak = 0

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

            nEventsPreSelected += 1

            isMETTriggered = False
            for s in list(tree.hltPaths):
                #print s, "is available"
                if 'PFMET' in s: 
                    isMETTriggered = True
                    #print "\t", s, "was MET triggered"
                
            if not isMETTriggered:
                continue

            nEventsMETTriggered += 1

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

            q0 = tree.selMu0_q
            q1 = tree.selMu1_q
            q2 = tree.selMu2_q
            
            ## two muons should have same charge, one muon should have opposite charge (-++, --+)
            ## other options --- and +++ are not allowed!
            if q0 == q1 == q2: continue

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

            pfMET = tree.pfMET
            pfMET_phi = tree.pfMET_phi
            #print "pfMET", pfMET
            #print "pfMET_phi", pfMET_phi
            
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

            ## calculate invariant masses
            if q0 * q1 < 0: mass01 = invmass(mu0, mu1)
            else:           mass01 = 0

            if q2 * q1 < 0: mass12 = invmass(mu1, mu2)
            else:           mass12 = 0

            if q0 * q2 < 0: mass02 = invmass(mu0, mu2)
            else:           mass02 = 0

            ## The invariant mass of any same-flavor dimuon pair must be greater than 4 GeV
            if q0 * q1 > 0 and invmass(mu0, mu1) < 4: continue
            if q0 * q2 > 0 and invmass(mu0, mu2) < 4: continue
            if q1 * q2 > 0 and invmass(mu1, mu2) < 4: continue

            nMassesInZPeak = int(isMassInZPeak(mass01)) + int(isMassInZPeak(mass02)) + int(isMassInZPeak(mass12))

            ## require at least one dimuon pair to be consistent with the Z pole mass 
            if nMassesInZPeak==0: continue

            bestMass = bestMassInZPeak(mass01, mass12, mass02)
            
            Zmumu = ()
            Wmu = [0,0,0,0]
            if bestMass == mass01:
                Zmumu = (mu0, mu1)
                Wmu = mu2

            if bestMass == mass02:
                Zmumu = (mu0, mu2)
                Wmu = mu1

            if bestMass == mass12:
                Zmumu = (mu1, mu2)
                Wmu = mu0

            Zmu0_pT = getPT(Zmumu[0])
            Zmu1_pT = getPT(Zmumu[1])
            Wmu_pT = getPT(Wmu)
            Wmu_phi = normalizePhi(getPhi(Wmu))
            
            ## require all muons have minimum 10 GeV pT
            if Zmu0_pT<10: continue
            if Zmu1_pT<10: continue
            if Wmu_pT<10: continue
            
            ## require 30 GeV MET from W decay
            if pfMET < 30: continue

            ## require one of the Z boson muons to have at least 20 GeV pT
            if not (Zmu0_pT > 20 or Zmu1_pT > 20): continue

            ## require the W boson muon to have at least 20 GeV pT
            if Wmu_pT < 20: continue

            ## 3-lep inv mass
            invm3 = inv3mass(mu0, mu1, mu2)
            if invm3 < 100: continue
            
            ## apply a quality criterium on the transverse mass cut
            Wmu_nu_deltaPhi = deltaPhi(Wmu_phi, normalizePhi(pfMET_phi))
            #print "Wmu_nu_deltaPhi", Wmu_nu_deltaPhi, Wmu_phi - pfMET_phi
            transverseWbosonMass = m.sqrt(2 * Wmu_pT * pfMET * (1-m.cos(Wmu_nu_deltaPhi)))
            if (verbose):
                print "transverseWbosonMass", transverseWbosonMass
            ## remove the contamination from W+jets in the sample!
            #if transverseWbosonMass > 20: continue

            print "Event passes full selection"
            nEventsSelected += 1

            Invariant_Mass12.Fill(bestMass)
            Transverse_Mass.Fill(transverseWbosonMass)
            Invariant_Mass123.Fill(invm3)
            PFMET.Fill(pfMET)
            WmupT.Fill(Wmu_pT)
            WmuPhi.Fill(Wmu_phi)
            METPhi.Fill(pfMET_phi)
            WmNuDeltaPhi.Fill(Wmu_nu_deltaPhi)

            leading_muon_eta.Fill(abs(tree.selMu0_eta))
            leading_muon_phi.Fill(tree.selMu0_phi)
            leading_muon_pt.Fill(tree.selMu0_pT)

            ## was triggered?
            isTriggered = False
            for trigger in triggerPaths:
                if (verbose): print list(tree.hltPaths)
                if any(trigger in s for s in list(tree.hltPaths)):
                    if (verbose): print trigger, "is available"
                    nEventsTriggered += 1
                    isTriggered = True

            if isTriggered:
                trig_leading_muon_eta.Fill(abs(tree.selMu0_eta))
                trig_leading_muon_phi.Fill(tree.selMu0_phi)
                trig_leading_muon_pt.Fill(tree.selMu0_pT)
                
            if nMassesInZPeak>0 and verbose:
                print "Muons"
                print mu0
                print mu1
                print mu2
                print
                print "Invariant masses"
                print "mass01", mass01, isMassInZPeak(mass01)
                print "mass12", mass12, isMassInZPeak(mass12)
                print "mass02", mass02, isMassInZPeak(mass02)
                print "best mass", bestMass
                print
                print "nEventsWith2MassInZPeak", nEventsWith2MassInZPeak
                print 


    print "n Total events analyzed", nTotalEvents
    print "nTotalEvents4Mu", nTotalEvents4Mu
    print "nEvents with 3 muons", nEventsPreSelected
    print "nEvents triggered by PFMET", nEventsMETTriggered
    print "nEvents selected after all quality cuts ", nEventsSelected
    print "nEventsTriggered", nEventsTriggered

    ## save histogram in a root file
    MyFile = TFile("HLT_Z_peak_signal_2016MonteCarlo_ZZto4L_13TeV.root","RECREATE");

    Invariant_Mass12.Write("Invariant_Mass12")
    Transverse_Mass.Write("Transverse_Mass")
    Invariant_Mass123.Write("Invariant_Mass123")
    PFMET.Write("PFMET")
    WmupT.Write("WmupT")
    WmuPhi.Write("WmuPhi")
    METPhi.Write("METPhi")
    WmNuDeltaPhi.Write("WmNuDeltaPhi")

    eff_trig_leading_muon_eta = TEfficiency(trig_leading_muon_eta, leading_muon_eta)
    eff_trig_leading_muon_phi = TEfficiency(trig_leading_muon_phi, leading_muon_phi)
    eff_trig_leading_muon_pt = TEfficiency(trig_leading_muon_pt, leading_muon_pt)
    eff_trig_leading_muon_eta.Write("eff_trig_leading_muon_eta")
    eff_trig_leading_muon_phi.Write("eff_trig_leading_muon_phi")
    eff_trig_leading_muon_pt.Write("eff_trig_leading_muon_pt")
    
    MyFile.Close();

dirNames = [
    '/fdata/hepx/store/user/dildick/EWK_13TeV_CALCHEP_50K_batch1_GEN_SIM_v1_TAMU/crab_ZZTo4L_ANA_v4/180123_053149/0000/',
    '/fdata/hepx/store/user/dildick/EWK_13TeV_CALCHEP_50K_batch2_GEN_SIM_v3_TAMU/crab_ZZTo4L_ANA_v4_PartTwo/180123_053222/0000/'
]

efficiency_trigger(dirNames, ["HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx"])

#exit(1)

def makePlot(histogram, plotType, x_label, y_label, saveAs, format='pdf'):

    ## setup histogram
    hist = HepPlotter(plotType,1)#"histogram"
    hist.x_relative_size = 10
    hist.y_relative_size = 7
    hist.drawEffDist = False    # draw the physics distribution for efficiency (jet_pt for jet trigger)
    #hist.rebin       = 1
    hist.x_label     = x_label# "Dimuon invariant mass"
    hist.y_label     = y_label
    hist.format      = format      # file format for saving image
    hist.saveDir     = 'trigger_efficiency_plots_2016MonteCarlo_ZZto4L_20181029/'
    hist.saveAs      = saveAs# "Z_peak_2016MonteCarlo_ZZto4L" # save figure with name
    hist.CMSlabel       = 'outer'  # 'top left', 'top right'; hack code for something else
    hist.CMSlabelStatus = 'Preliminary Simulation'  # ('Simulation')+'Internal' || 'Preliminary' 
    hist.initialize()
    hist.lumi = '2016 MET B-H, 35.9'
    hist.plotLUMI = False
    hist.drawStatUncertainty = True    
    hist.Add(histogram, draw='errorbar', color='black', linecolor='black', label=r'$ZZ \rightarrow 4\mu$')
    plot = hist.execute()
    hist.savefig()

MyFile = TFile("HLT_Z_peak_signal_2016MonteCarlo_ZZto4L_13TeV.root")

Invariant_Mass12 = MyFile.Get("Invariant_Mass12")
makePlot(Invariant_Mass12, "histogram", 
         r"Dimuon invariant mass [GeV]", "Entries", "Z_peak_2016MonteCarlo_ZZto4L", format='pdf')

Invariant_Mass123 = MyFile.Get("Invariant_Mass123")
makePlot(Invariant_Mass123, "histogram", 
         r"Trimuon invariant mass [GeV]", "Entries", "Trimuon_invariant_mass_2016MonteCarlo_ZZto4L", format='pdf')

Transverse_Mass = MyFile.Get("Transverse_Mass")
makePlot(Transverse_Mass, "histogram", 
         r"Transverse mass m_\mathrm{T} [GeV]", "Entries", "Transverse_mass_2016MonteCarlo_ZZto4L", format='pdf')

PFMET = MyFile.Get("PFMET")
makePlot(PFMET, "histogram", 
         r"PFMET [GeV]", "Entries", "PFMET_2016MonteCarlo_ZZto4L", format='pdf')

eff_trig_leading_muon_pt = MyFile.Get("eff_trig_leading_muon_pt")
makePlot(eff_trig_leading_muon_pt, "efficiency", 
         r"Leading muon $p_\mathrm{T}$ [GeV]", "Trigger efficiency", "Trigger_efficiency_leading_pt_2016MonteCarlo_ZZto4L", format='pdf')

eff_trig_leading_muon_eta = MyFile.Get("eff_trig_leading_muon_eta")
makePlot(eff_trig_leading_muon_eta, "efficiency", 
         r"Leading muon $\eta$", "Trigger efficiency", "Trigger_efficiency_leading_eta_2016MonteCarlo_ZZto4L", format='pdf')

eff_trig_leading_muon_phi = MyFile.Get("eff_trig_leading_muon_phi")
makePlot(eff_trig_leading_muon_phi, "efficiency", 
         r"Leading muon $\phi$", "Trigger efficiency", "Trigger_efficiency_leading_phi_2016MonteCarlo_ZZto4L", format='pdf')

MyFile.Close()
