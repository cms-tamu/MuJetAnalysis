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

##____________________________________________________________
def efficiency_trigger(dirNames, triggerPaths):

    verbose = False

    chain = ROOT.TChain("Events")

    print "Preparing histograms"

    Invariant_Mass12 = ROOT.TH1D("Invariant_Mass12","",60,75,105);


    print "Adding files to the chain"
    addfilesMany(chain, dirNames, "out_ana_selected_MET_2016BH_20171006.root")
                                   
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

        if (verbose): print "Loading directory cutFlowAnalyzer_Data"
        
        tree = myfile.Get("cutFlowAnalyzer_Data/Events")
        tree = myfile.Get("Events")

        if not tree: 
            if (verbose): print "Tree cutFlowAnalyzer_Data/Events does not exist"
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
      
            if (nMu<3):
                continue

            ## mass of the muon in GeV
            mmu = 105.6583745 * 0.001
            mZ = 91.1876
            
            px0 = tree.selMu0_px
            px1 = tree.selMu1_px
            px2 = tree.selMu2_px

            py0 = tree.selMu0_py
            py1 = tree.selMu1_py
            py2 = tree.selMu2_py

            pz0 = tree.selMu0_pz
            pz1 = tree.selMu1_pz
            pz2 = tree.selMu2_pz

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
                
            def isMassInZPeak(m):
                return abs(m-mZ)<15

            def bestMassInZPeak(m1, m2, m3):
                masses = [m1, m2, m3]
                massdiffs = [abs(m1-mZ), abs(m2-mZ), abs(m3-mZ)]
                index = massdiffs.index(min(massdiffs))
                return masses[index]

            ## calculate the energies
            E0 = energy(mmu, px0, py0, pz0) 
            E1 = energy(mmu, px1, py1, pz1)
            E2 = energy(mmu, px2, py2, pz2)

            ## declare the four vectors
            mu0 = [E0, px0, py0, pz0]
            mu1 = [E1, px1, py1, pz1]
            mu2 = [E2, px2, py2, pz2]

            ## calculate invariant masses
            mass01 = invmass(mu0, mu1)
            mass12 = invmass(mu1, mu2)
            mass02 = invmass(mu0, mu2)

            nMassesInZPeak = int(isMassInZPeak(mass01)) + int(isMassInZPeak(mass02)) + int(isMassInZPeak(mass12))

            bestMass = bestMassInZPeak(mass01, mass12, mass02)

            Invariant_Mass12.Fill(bestMass)
                #nEventsWith2MassInZPeak += 1
            if False:
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
    MyFile = TFile("HLT_Z_peak_signal_2016MET_BH_13TeV.root","RECREATE");

    Invariant_Mass12.Write("Invariant_Mass12")

    MyFile.Close();

dirNames = [
    '/home/dildick/DisplacedMuonJetAnalysis_2016/CMSSW_8_0_24/src/MuJetAnalysis/AnalysisRun2/scripts/HLTEfficiency/orthogonalMethod/'
]
efficiency_trigger(dirNames, ["HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx"])


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
    hist.saveDir     = 'trigger_efficiency_plots_2016METB-H_20171107/'
    hist.saveAs      = "Z_peak_2016MET_BH_" # save figure with name
    hist.CMSlabel       = 'outer'  # 'top left', 'top right'; hack code for something else
    hist.CMSlabelStatus = 'Preliminary'  # ('Simulation')+'Internal' || 'Preliminary' 
    hist.initialize()
    hist.lumi = '2016 MET B-H, 35.9'
    hist.drawStatUncertainty = True    
    hist.Add(histogram, draw='errorbar', color='black', linecolor='black', label='Data')
    plot = hist.execute()
    hist.savefig()


MyFile = TFile("HLT_Z_peak_signal_2016MET_BH_13TeV.root")

Invariant_Mass12 = MyFile.Get("Invariant_Mass12")

makePlot(Invariant_Mass12, format='pdf')

MyFile.Close()

