import sys
from ROOT import *
from argparse import ArgumentParser

from hepPlotter import HepPlotter
import hepPlotterTools as hpt
#import hepPlotterLabels as hpl

import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from Helpers import *

##____________________________________________________________
def efficiency_trigger(dirNames, triggerPaths):

    verbose = False

    chain = ROOT.TChain("Events")

    print "Preparing histograms"

    RECO_leading_pt = ROOT.TH1D("RECO_leading_pt","",25,0.,50.);
    RECO_leading_eta = ROOT.TH1D("RECO_leading_eta","",25,-2.5,2.5);
    RECO_leading_phi = ROOT.TH1D("RECO_leading_phi","",30,-ROOT.TMath.Pi(),ROOT.TMath.Pi());

    hlt_RECO_leading_pt = {}
    hlt_RECO_leading_eta = {}
    hlt_RECO_leading_phi = {}
    
    eff_hlt_RECO_leading_pt = {}
    eff_hlt_RECO_leading_eta = {}
    eff_hlt_RECO_leading_phi = {}

    RECO_leading_pt_barrel = ROOT.TH1D("RECO_leading_pt_barrel","",25,0.,50.);
    RECO_leading_eta_barrel = ROOT.TH1D("RECO_leading_eta_barrel","",25,-2.5,2.5);
    RECO_leading_phi_barrel = ROOT.TH1D("RECO_leading_phi_barrel","",30,-ROOT.TMath.Pi(),ROOT.TMath.Pi());

    hlt_RECO_leading_pt_barrel = {}
    hlt_RECO_leading_eta_barrel = {}
    hlt_RECO_leading_phi_barrel = {}
    
    eff_hlt_RECO_leading_pt_barrel = {}
    eff_hlt_RECO_leading_eta_barrel = {}
    eff_hlt_RECO_leading_phi_barrel = {}

    for trigger in triggerPaths:
        hlt_RECO_leading_pt[trigger] = ROOT.TH1D("hlt_RECO_leading_pt_" + trigger,"",25,0.,50.)
        hlt_RECO_leading_eta[trigger] = ROOT.TH1D("hlt_RECO_leading_eta_" + trigger,"",25,-2.5,2.5)
        hlt_RECO_leading_phi[trigger] = ROOT.TH1D("hlt_RECO_leading_phi_" + trigger,"",30,-ROOT.TMath.Pi(),ROOT.TMath.Pi())

        hlt_RECO_leading_pt_barrel[trigger] = ROOT.TH1D("hlt_RECO_leading_pt_barrel_" + trigger,"",25,0.,50.)
        hlt_RECO_leading_eta_barrel[trigger] = ROOT.TH1D("hlt_RECO_leading_eta_barrel_" + trigger,"",25,-2.5,2.5)
        hlt_RECO_leading_phi_barrel[trigger] = ROOT.TH1D("hlt_RECO_leading_phi_barrel_" + trigger,"",30,-ROOT.TMath.Pi(),ROOT.TMath.Pi())

    print "Adding files to the chain"
    addfilesMany(chain, dirNames, "out_ana_selected_MET_2016BH_20171006.root")
                                   
    print "Loop over the chain"
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

        for k in range(0, tree.GetEntries()):

            if k%100000==0: print "Processing event ", k 
            tree.GetEntry(k)

            ## check for 4 reco muons 
            nMu = int(tree.selMu0_pT != -100) + int(tree.selMu1_pT != -100) + int(tree.selMu2_pT != -100) + int(tree.selMu3_pT != -100) 

            if (nMu<3):
                continue

            nMuPt8 = 0
            if tree.selMu0_pT >= 8: nMuPt8 += 1
            if tree.selMu1_pT >= 8: nMuPt8 += 1
            if tree.selMu2_pT >= 8: nMuPt8 += 1
            if tree.selMu3_pT >= 8: nMuPt8 += 1

            nMuPt17 = 0
            if tree.selMu0_pT >= 17: nMuPt17 += 1
            if tree.selMu1_pT >= 17: nMuPt17 += 1
            if tree.selMu2_pT >= 17: nMuPt17 += 1
            if tree.selMu3_pT >= 17: nMuPt17 += 1

            nMuPt17Barrel = 0
            if (tree.selMu0_pT>=17 and abs(tree.selMu0_eta)<=0.9): nMuPt17Barrel += 1
            if (tree.selMu1_pT>=17 and abs(tree.selMu1_eta)<=0.9): nMuPt17Barrel += 1
            if (tree.selMu2_pT>=17 and abs(tree.selMu2_eta)<=0.9): nMuPt17Barrel += 1
            if (tree.selMu3_pT>=17 and abs(tree.selMu3_eta)<=0.9): nMuPt17Barrel += 1
 
            ## require baseline selection!!!
            if (nMuPt8>=3 and nMuPt17 >=1):

                if (verbose): print "Pass denom"
                RECO_leading_pt.Fill(tree.selMu0_pT)
                RECO_leading_eta.Fill(tree.selMu0_eta)
                RECO_leading_phi.Fill(tree.selMu0_phi)

                ## check if triggerPath is in the list
                ## check each trigger
                for trigger in triggerPaths:

                    ## print list(tree.hltPaths)
                    if any(trigger in s for s in list(tree.hltPaths)):
                        if (verbose): print trigger, "is available"

                        ## print "\tPass num"
                        hlt_RECO_leading_pt[trigger].Fill(tree.selMu0_pT)
                        hlt_RECO_leading_eta[trigger].Fill(tree.selMu0_eta)
                        hlt_RECO_leading_phi[trigger].Fill(tree.selMu0_phi)

            ## require baseline selection!!!
            if (nMuPt8>=3 and nMuPt17Barrel>=1):

                if (verbose): print "Pass denom"
                RECO_leading_pt_barrel.Fill(tree.selMu0_pT)
                RECO_leading_eta_barrel.Fill(tree.selMu0_eta)
                RECO_leading_phi_barrel.Fill(tree.selMu0_phi)
                
                ## check if triggerPath is in the list
                ## check each trigger
                for trigger in triggerPaths:

                    ## print list(tree.hltPaths)
                    if any(trigger in s for s in list(tree.hltPaths)):
                        if (verbose): print trigger, "is available"

                        ## print "\tPass num"
                        hlt_RECO_leading_pt_barrel[trigger].Fill(tree.selMu0_pT)
                        hlt_RECO_leading_eta_barrel[trigger].Fill(tree.selMu0_eta)
                        hlt_RECO_leading_phi_barrel[trigger].Fill(tree.selMu0_phi)


    ### make the efficiency plots
    for trigger in triggerPaths:
        eff_hlt_RECO_leading_pt[trigger] = ROOT.TEfficiency(hlt_RECO_leading_pt[trigger], RECO_leading_pt)
        eff_hlt_RECO_leading_eta[trigger] = ROOT.TEfficiency(hlt_RECO_leading_eta[trigger], RECO_leading_eta)
        eff_hlt_RECO_leading_phi[trigger] = ROOT.TEfficiency(hlt_RECO_leading_phi[trigger], RECO_leading_phi)

        eff_hlt_RECO_leading_pt_barrel[trigger] = ROOT.TEfficiency(hlt_RECO_leading_pt_barrel[trigger], RECO_leading_pt_barrel)
        eff_hlt_RECO_leading_eta_barrel[trigger] = ROOT.TEfficiency(hlt_RECO_leading_eta_barrel[trigger], RECO_leading_eta_barrel)
        eff_hlt_RECO_leading_phi_barrel[trigger] = ROOT.TEfficiency(hlt_RECO_leading_phi_barrel[trigger], RECO_leading_phi_barrel)

    MyFile = TFile("HLT_efficiency_signal_backup_2016MET_BH_13TeV_3Mu.root","RECREATE");

    for trigger in triggerPaths:
        eff_hlt_RECO_leading_pt[trigger].Write("eff_hlt_RECO_leading_pt_" + trigger)
        eff_hlt_RECO_leading_eta[trigger].Write("eff_hlt_RECO_leading_eta_" + trigger)
        eff_hlt_RECO_leading_phi[trigger].Write("eff_hlt_RECO_leading_phi_" + trigger)

        eff_hlt_RECO_leading_pt_barrel[trigger].Write("eff_hlt_RECO_leading_pt_barrel_" + trigger)
        eff_hlt_RECO_leading_eta_barrel[trigger].Write("eff_hlt_RECO_leading_eta_barrel_" + trigger)
        eff_hlt_RECO_leading_phi_barrel[trigger].Write("eff_hlt_RECO_leading_phi_barrel_" + trigger)

    MyFile.Close();
    


dirNames = ['/home/dildick/DisplacedMuonJetAnalysis_2016/CMSSW_8_0_24/src/MuJetAnalysis/AnalysisRun2/scripts/HLTEfficiency/orthogonalMethod/']
triggerPaths = ["HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx", "HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx"]
efficiency_trigger(dirNames, ["HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx", "HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx"])

def makePlot(effTuple, triggerPath, format='pdf'):

    ## setup histogram
    hist = HepPlotter("efficiency",1)
    hist.x_relative_size = 10
    hist.y_relative_size = 7
    hist.drawEffDist = False    # draw the physics distribution for efficiency (jet_pt for jet trigger)
    #hist.rebin       = 1
    hist.x_label     = effTuple[1]
    hist.y_label     = "Trigger efficiency"
    hist.format      = format      # file format for saving image
    hist.saveDir     = 'trigger_efficiency_plots_2016METB-H_20171107/'
    if 'barrel' in effTuple[0].GetName():
        hist.saveAs      = "eff_" + triggerPath + "_2016MET_BH_barrel_" + effTuple[2] # save figure with name
    else:
        hist.saveAs      = "eff_" + triggerPath + "_2016MET_BH_" + effTuple[2] # save figure with name
    hist.CMSlabel       = 'outer'  # 'top left', 'top right'; hack code for something else
    hist.CMSlabelStatus = 'Preliminary'  # ('Simulation')+'Internal' || 'Preliminary' 
    hist.initialize()
    hist.lumi = '2016 MET B-H, 35.9'
    hist.drawStatUncertainty = True    
    hist.Add(effTuple[0], draw='errorbar', color='blue', linecolor='blue', label=triggerPath.replace('_','\_'))
    plot = hist.execute()
    hist.savefig()

MyFile = TFile("HLT_efficiency_signal_backup_2016MET_BH_13TeV_3Mu.root");

eff_hlt_RECO_leading_pt = {}
eff_hlt_RECO_leading_eta = {}
eff_hlt_RECO_leading_phi = {}

eff_hlt_RECO_leading_pt_barrel = {}
eff_hlt_RECO_leading_eta_barrel = {}
eff_hlt_RECO_leading_phi_barrel = {}

## make trigger efficiencies for each trigger path
for trigger in triggerPaths:
    eff_hlt_RECO_leading_pt[trigger] = MyFile.Get("eff_hlt_RECO_leading_pt_" + trigger)
    eff_hlt_RECO_leading_eta[trigger] = MyFile.Get("eff_hlt_RECO_leading_eta_" + trigger)
    eff_hlt_RECO_leading_phi[trigger] = MyFile.Get("eff_hlt_RECO_leading_phi_" + trigger)
    
    eff_pt = (eff_hlt_RECO_leading_pt[trigger], r"Leading muon $p_\mathrm{T}$ [GeV]", "pt")
    eff_eta = (eff_hlt_RECO_leading_eta[trigger], r"Leading muon $\eta$", "eta")
    eff_phi = (eff_hlt_RECO_leading_phi[trigger], r"Leading muon $\phi$", "phi")

    eff_hlt_RECO_list = [eff_pt, eff_eta, eff_phi]

    makePlot(eff_pt, trigger, format='png')
    makePlot(eff_eta, trigger, format='png')
    makePlot(eff_phi, trigger, format='png')

    makePlot(eff_pt, trigger, format='pdf')
    makePlot(eff_eta, trigger, format='pdf')
    makePlot(eff_phi, trigger, format='pdf')

    
    eff_hlt_RECO_leading_pt_barrel[trigger] = MyFile.Get("eff_hlt_RECO_leading_pt_barrel_" + trigger)
    eff_hlt_RECO_leading_eta_barrel[trigger] = MyFile.Get("eff_hlt_RECO_leading_eta_barrel_" + trigger)
    eff_hlt_RECO_leading_phi_barrel[trigger] = MyFile.Get("eff_hlt_RECO_leading_phi_barrel_" + trigger)
    
    eff_pt = (eff_hlt_RECO_leading_pt_barrel[trigger], r"Leading muon $p_\mathrm{T}$ [GeV]", "pt")
    eff_eta = (eff_hlt_RECO_leading_eta_barrel[trigger], r"Leading muon $\eta$", "eta")
    eff_phi = (eff_hlt_RECO_leading_phi_barrel[trigger], r"Leading muon $\phi$", "phi")

    eff_hlt_RECO_list = [eff_pt, eff_eta, eff_phi]

    makePlot(eff_pt, trigger, format='png')
    makePlot(eff_eta, trigger, format='png')
    makePlot(eff_phi, trigger, format='png')

    makePlot(eff_pt, trigger, format='pdf')
    makePlot(eff_eta, trigger, format='pdf')
    makePlot(eff_phi, trigger, format='pdf')

MyFile.Close()
