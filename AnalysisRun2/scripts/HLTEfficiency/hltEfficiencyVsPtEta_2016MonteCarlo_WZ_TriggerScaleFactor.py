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

    Invariant_Mass12 = ROOT.TH1D("Invariant_Mass12","",60,76,106);


    print "Adding files to the chain"
    addfilesMany(chain, dirNames, "out_ana")
                                   
    print "Loop over the chain"
    nEventsWith2MassInZPeak = 0
    for rootFile in chain.GetListOfFiles():
        
        ## loop on events in the ROOT file
        if (verbose): print "running on file ", rootFile.GetTitle()

        myfile = ROOT.TFile(rootFile.GetTitle())
        if (not myfile):
            if (verbose): print "File ", rootFile.GetTitle(), " does not exist"
            continue

        #myfile.cd("cutFlowAnalyzer_Data")  
        #myfile.cd("Events")

        if (verbose): print "Loading directory cutFlowAnalyzer"
       
        tree = myfile.Get("cutFlowAnalyzer/Events")

        if not tree: 
            if (verbose): print "Tree cutFlowAnalyzer/Events does not exist"
            continue

        if (verbose): print "  Events  ", tree.GetEntries()

        nTriggers = 0
        for k in range(0, tree.GetEntries()):

            if k%100000==0: print "Processing event ", k 
            tree.GetEntry(k)

            ## check for 4 reco muons 
            nMu = 0
            
            if tree.selMu0_pT != -100: nMu += 1
            if tree.selMu1_pT != -100: nMu += 1
            if tree.selMu2_pT != -100: nMu += 1
            if tree.selMu3_pT != -100: nMu += 1
      
            if (nMu!=3):
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

            phi0 = tree.selMu0_phi
            phi1 = tree.selMu1_phi
            phi2 = tree.selMu2_phi

            q0 = tree.selMu0_q
            q1 = tree.selMu1_q
            q2 = tree.selMu2_q

            isMedium0 = tree.selMu0_isMedium
            isMedium1 = tree.selMu1_isMedium
            isMedium2 = tree.selMu2_isMedium

            isTight0 = tree.selMu0_isTight
            isTight1 = tree.selMu1_isTight
            isTight2 = tree.selMu2_isTight

            dxy0 = tree.selMu0_dxy
            dxy1 = tree.selMu1_dxy
            dxy2 = tree.selMu2_dxy

            dz0 = tree.selMu0_dz
            dz1 = tree.selMu1_dz
            dz2 = tree.selMu2_dz

            pfMET = tree.pfMET

            ## calculate the energies
            E0 = energy(mmu, px0, py0, pz0) 
            E1 = energy(mmu, px1, py1, pz1)
            E2 = energy(mmu, px2, py2, pz2)

            print E0, px0, py0, pz0, q0, phi0
            print E1, px1, py1, pz1, q1, phi1
            print E2, px2, py2, pz2, q2, phi2

            ## declare the four vectors
            mu0 = [E0, px0, py0, pz0]
            mu1 = [E1, px1, py1, pz1]
            mu2 = [E2, px2, py2, pz2]

            numberOfMuonPairs = 0
            if q0 * q1 < 0: numberOfMuonPairs += 1
            if q1 * q2 < 0: numberOfMuonPairs += 1
            if q0 * q2 < 0: numberOfMuonPairs += 1

            print "numberOfMuonPairs", numberOfMuonPairs

            ## calculate invariant masses
            if q0 * q1 < 0: 
                mass01 = invmass(mu0, mu1)
            else:
                mass01 = 0

            if q2 * q1 < 0: 
                mass12 = invmass(mu1, mu2)
            else:
                mass12 = 0

            if q0 * q2 < 0: 
                mass02 = invmass(mu0, mu2)
            else:
                mass02 = 0

            print mass01, mass12, mass02
            print

            nMassesInZPeak = int(isMassInZPeak(mass01)) + int(isMassInZPeak(mass02)) + int(isMassInZPeak(mass12))

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
            
            ## require all muons have minimum 10 GeV pT
            if Zmu0_pT<10: continue
            if Zmu1_pT<10: continue
            if Wmu_pT<10: continue
            
            if not isTight0: continue
            if not isTight1: continue
            if not isTight2: continue

            if dxy0 > 0.01: continue
            if dxy1 > 0.01: continue
            if dxy2 > 0.01: continue

            if dz0 > 0.1: continue
            if dz1 > 0.1: continue
            if dz2 > 0.1: continue

            ## require 30 GeV MET from W decay
            if pfMET < 30: continue

            if Zmu0_pT < 20 or Zmu1_pT < 20: continue

            if Wmu_pT < 20: continue

            ## 3-lep inv mass
            invm3 = inv3mass(mu0, mu1, mu2)

            if invm3 < 100: continue

            Invariant_Mass12.Fill(bestMass)
            #if nMassesInZPeak>0: 
            #    #nEventsWith2MassInZPeak += 1
            if nMassesInZPeak>0 and True:
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

    ## save histogram in a root file
    MyFile = TFile("HLT_Z_peak_signal_2016MonteCarlo_WZ_13TeV.root","RECREATE");

    Invariant_Mass12.Write("Invariant_Mass12")

    MyFile.Close();

dirNames = [
    '/fdata/hepx/store/user/dildick/WZTo3LNu_0Jets_MLL-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_WZ_RunIISummer16DR80Premix-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1-20171108_v2/171108_153358/0000/'
]

efficiency_trigger(dirNames, ["HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx"])

#exit(1)

def makePlot(histogram, format='pdf'):

    ## setup histogram
    hist = HepPlotter("histogram",1)
    hist.x_relative_size = 10
    hist.y_relative_size = 7
    hist.drawEffDist = False    # draw the physics distribution for efficiency (jet_pt for jet trigger)
    #hist.rebin       = 1
    hist.x_label     = "Dimuon invariant mass"
    hist.y_label     = "Entries"
    hist.format      = format      # file format for saving image
    hist.saveDir     = 'trigger_efficiency_plots_2016MonteCarlo_WZ_20171108/'
    hist.saveAs      = "Z_peak_2016MonteCarlo_WZ" # save figure with name
    hist.CMSlabel       = 'outer'  # 'top left', 'top right'; hack code for something else
    hist.CMSlabelStatus = 'Preliminary Simulation'  # ('Simulation')+'Internal' || 'Preliminary' 
    hist.initialize()
    hist.lumi = '2016 MET B-H, 35.9'
    hist.plotLUMI = False
    hist.drawStatUncertainty = True    
    hist.Add(histogram, draw='errorbar', color='black', linecolor='black', label='WZ MonteCarlo')
    plot = hist.execute()
    hist.savefig()


MyFile = TFile("HLT_Z_peak_signal_2016MonteCarlo_WZ_13TeV.root")

Invariant_Mass12 = MyFile.Get("Invariant_Mass12")

makePlot(Invariant_Mass12, format='pdf')

MyFile.Close()

