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

    verbose = True

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

    RECO_leading_pt_full = ROOT.TH1D("RECO_leading_pt_full","",25,0.,50.);
    RECO_leading_eta_full = ROOT.TH1D("RECO_leading_eta_full","",25,-2.5,2.5);
    RECO_leading_phi_full = ROOT.TH1D("RECO_leading_phi_full","",30,-ROOT.TMath.Pi(),ROOT.TMath.Pi());

    hlt_RECO_leading_pt_full = {}
    hlt_RECO_leading_eta_full = {}
    hlt_RECO_leading_phi_full = {}
    
    eff_hlt_RECO_leading_pt_full = {}
    eff_hlt_RECO_leading_eta_full = {}
    eff_hlt_RECO_leading_phi_full = {}

    for trigger in triggerPaths:
        hlt_RECO_leading_pt[trigger] = ROOT.TH1D("hlt_RECO_leading_pt_" + trigger,"",25,0.,50.)
        hlt_RECO_leading_eta[trigger] = ROOT.TH1D("hlt_RECO_leading_eta_" + trigger,"",25,-2.5,2.5)
        hlt_RECO_leading_phi[trigger] = ROOT.TH1D("hlt_RECO_leading_phi_" + trigger,"",30,-ROOT.TMath.Pi(),ROOT.TMath.Pi())

        hlt_RECO_leading_pt_barrel[trigger] = ROOT.TH1D("hlt_RECO_leading_pt_barrel_" + trigger,"",25,0.,50.)
        hlt_RECO_leading_eta_barrel[trigger] = ROOT.TH1D("hlt_RECO_leading_eta_barrel_" + trigger,"",25,-2.5,2.5)
        hlt_RECO_leading_phi_barrel[trigger] = ROOT.TH1D("hlt_RECO_leading_phi_barrel_" + trigger,"",30,-ROOT.TMath.Pi(),ROOT.TMath.Pi())

        hlt_RECO_leading_pt_full[trigger] = ROOT.TH1D("hlt_RECO_leading_pt_full_" + trigger,"",25,0.,50.)
        hlt_RECO_leading_eta_full[trigger] = ROOT.TH1D("hlt_RECO_leading_eta_full_" + trigger,"",25,-2.5,2.5)
        hlt_RECO_leading_phi_full[trigger] = ROOT.TH1D("hlt_RECO_leading_phi_full_" + trigger,"",30,-ROOT.TMath.Pi(),ROOT.TMath.Pi())

    print "Adding files to the chain"
    for p in dirNames:
        addfile(chain, p)

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
        
        tree = myfile.Get("cutFlowAnalyzerPXBL3PXFL2_Data/Events")

        if not tree: 
            if (verbose): print "Tree cutFlowAnalyzerPXBL3PXFL2_Data/Events does not exist"
            continue

        if (verbose): print "  Events  ", tree.GetEntries()

        for k in range(0, tree.GetEntries()):

            if k%100000==0: print "Processing event ", k 
            tree.GetEntry(k)

            ## check for 4 reco muons 
            nMu = int(tree.selMu0_pT != -100) + int(tree.selMu1_pT != -100) + int(tree.selMu2_pT != -100) + int(tree.selMu3_pT != -100) 

            if (nMu<4):
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
 
            print nMuPt8, nMuPt17, nMuPt17Barrel
            print tree.selMu0_pT, tree.selMu0_eta
            print tree.selMu1_pT, tree.selMu1_eta
            print tree.selMu2_pT, tree.selMu2_eta
            print tree.selMu3_pT, tree.selMu3_eta
            
            ## require baseline selection!!!
            if (nMuPt8>=4 and nMuPt17 >=1):

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
            if (nMuPt8>=4 and nMuPt17Barrel>=1):

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

                is2DiMuonsDzOK_FittedVtx = abs(tree.diMuonC_FittedVtx_dz - tree.diMuonF_FittedVtx_dz) < 0.1
                is2DiMuonsIsoTkOK_FittedVtx = (tree.diMuonC_IsoTk_FittedVtx < 2 and tree.diMuonF_IsoTk_FittedVtx < 2)
                is2DiMuonsPixelOk = ( (tree.diMuonC_m1_FittedVtx_hitpix_l3inc==1 or 
                                       tree.diMuonC_m2_FittedVtx_hitpix_l3inc==1) and 
                                      (tree.diMuonF_m1_FittedVtx_hitpix_l3inc==1 or 
                                       tree.diMuonF_m2_FittedVtx_hitpix_l3inc==1) )

                ## require additional selections
                if (tree.isVertexOK and 
                    tree.is2MuJets and 
                    tree.is2DiMuons and
                    tree.is2DiMuonsFittedVtxOK and
#                    is2DiMuonsPixelOk and 
                    is2DiMuonsDzOK_FittedVtx and
#                    tree.is2DiMuonsMassOK_FittedVtx and
                    is2DiMuonsIsoTkOK_FittedVtx):
                    
                    RECO_leading_pt_full.Fill(tree.selMu0_pT)
                    RECO_leading_eta_full.Fill(tree.selMu0_eta)
                    RECO_leading_phi_full.Fill(tree.selMu0_phi)

                    ## check if triggerPath is in the list
                    ## check each trigger
                    for trigger in triggerPaths:

                        ## print list(tree.hltPaths)
                        if any(trigger in s for s in list(tree.hltPaths)):
                            if (verbose): print trigger, "is available"

                            ## print "\tPass num"
                            hlt_RECO_leading_pt_full[trigger].Fill(tree.selMu0_pT)
                            hlt_RECO_leading_eta_full[trigger].Fill(tree.selMu0_eta)
                            hlt_RECO_leading_phi_full[trigger].Fill(tree.selMu0_phi)


    ### make the efficiency plots
    for trigger in triggerPaths:
        eff_hlt_RECO_leading_pt[trigger] = ROOT.TEfficiency(hlt_RECO_leading_pt[trigger], RECO_leading_pt)
        eff_hlt_RECO_leading_eta[trigger] = ROOT.TEfficiency(hlt_RECO_leading_eta[trigger], RECO_leading_eta)
        eff_hlt_RECO_leading_phi[trigger] = ROOT.TEfficiency(hlt_RECO_leading_phi[trigger], RECO_leading_phi)

        eff_hlt_RECO_leading_pt_barrel[trigger] = ROOT.TEfficiency(hlt_RECO_leading_pt_barrel[trigger], RECO_leading_pt_barrel)
        eff_hlt_RECO_leading_eta_barrel[trigger] = ROOT.TEfficiency(hlt_RECO_leading_eta_barrel[trigger], RECO_leading_eta_barrel)
        eff_hlt_RECO_leading_phi_barrel[trigger] = ROOT.TEfficiency(hlt_RECO_leading_phi_barrel[trigger], RECO_leading_phi_barrel)

        eff_hlt_RECO_leading_pt_full[trigger] = ROOT.TEfficiency(hlt_RECO_leading_pt_full[trigger], RECO_leading_pt_full)
        eff_hlt_RECO_leading_eta_full[trigger] = ROOT.TEfficiency(hlt_RECO_leading_eta_full[trigger], RECO_leading_eta_full)
        eff_hlt_RECO_leading_phi_full[trigger] = ROOT.TEfficiency(hlt_RECO_leading_phi_full[trigger], RECO_leading_phi_full)

    MyFile = TFile("HLT_efficiency_signal_backup_2016DoubleMuon_BCDEFGH_13TeV.root","RECREATE");

    for trigger in triggerPaths:
        eff_hlt_RECO_leading_pt[trigger].Write("eff_hlt_RECO_leading_pt_" + trigger)
        eff_hlt_RECO_leading_eta[trigger].Write("eff_hlt_RECO_leading_eta_" + trigger)
        eff_hlt_RECO_leading_phi[trigger].Write("eff_hlt_RECO_leading_phi_" + trigger)

        eff_hlt_RECO_leading_pt_barrel[trigger].Write("eff_hlt_RECO_leading_pt_barrel_" + trigger)
        eff_hlt_RECO_leading_eta_barrel[trigger].Write("eff_hlt_RECO_leading_eta_barrel_" + trigger)
        eff_hlt_RECO_leading_phi_barrel[trigger].Write("eff_hlt_RECO_leading_phi_barrel_" + trigger)

        eff_hlt_RECO_leading_pt_full[trigger].Write("eff_hlt_RECO_leading_pt_full_" + trigger)
        eff_hlt_RECO_leading_eta_full[trigger].Write("eff_hlt_RECO_leading_eta_full_" + trigger)
        eff_hlt_RECO_leading_phi_full[trigger].Write("eff_hlt_RECO_leading_phi_full_" + trigger)

    MyFile.Close();
    

dirNames = ['/fdata/hepx/store/user/lpernie/DoubleMuon/']
triggerPaths = ["HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx", 
                "HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx"]

dirNames = [
'/fdata/hepx/store/user/lpernie/DoubleMuon/crab_Run2016B-23Sep2016-v3_FINAL.root',
'/fdata/hepx/store/user/lpernie/DoubleMuon/crab_Run2016C-23Sep2016-v1_FINAL.root',
'/fdata/hepx/store/user/lpernie/DoubleMuon/crab_Run2016D-23Sep2016-v1_v2_FINAL.root',
'/fdata/hepx/store/user/lpernie/DoubleMuon/crab_Run2016E-23Sep2016-v1_v2_FINAL.root',
'/fdata/hepx/store/user/lpernie/DoubleMuon/crab_Run2016F-23Sep2016-v1_v2_FINAL.root',
'/fdata/hepx/store/user/lpernie/DoubleMuon/crab_Run2016G-23Sep2016-v1_v2_FINAL.root',
'/fdata/hepx/store/user/lpernie/DoubleMuon/crab_Run2016H-PromptReco-v3_v2_FINAL.root'
]

efficiency_trigger(dirNames, triggerPaths)

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
    hist.saveDir     = 'trigger_efficiency_plots_2016DoubleMuon_BCDEFGH_20171024/'
    if 'full' in effTuple[0].GetName():
        hist.saveAs      = "eff_" + triggerPath + "_2016BCDEFGH_MuJetVtxDzIso_" + effTuple[2] # save figure with name
    elif 'barrel' in effTuple[0].GetName():
        hist.saveAs      = "eff_" + triggerPath + "_2016BCDEFGH_barrel_" + effTuple[2] # save figure with name
    else:
        hist.saveAs      = "eff_" + triggerPath + "_2016BCDEFGH_" + effTuple[2] # save figure with name
    hist.CMSlabel       = 'outer'  # 'top left', 'top right'; hack code for something else
    hist.CMSlabelStatus = 'Preliminary'  # ('Simulation')+'Internal' || 'Preliminary' 
    hist.initialize()
    hist.lumi = '2016 DoubleMuon B-H, 35.9'
    hist.drawStatUncertainty = True    
    hist.Add(effTuple[0], draw='errorbar', color='blue', linecolor='blue', label=triggerPath.replace('_','\_'))
    plot = hist.execute()
    hist.savefig()

MyFile = TFile("HLT_efficiency_signal_backup_2016DoubleMuon_BCDEFGH_13TeV.root");

eff_hlt_RECO_leading_pt = {}
eff_hlt_RECO_leading_eta = {}
eff_hlt_RECO_leading_phi = {}

eff_hlt_RECO_leading_pt_barrel = {}
eff_hlt_RECO_leading_eta_barrel = {}
eff_hlt_RECO_leading_phi_barrel = {}

eff_hlt_RECO_leading_pt_full = {}
eff_hlt_RECO_leading_eta_full = {}
eff_hlt_RECO_leading_phi_full = {}

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


    eff_hlt_RECO_leading_pt_full[trigger] = MyFile.Get("eff_hlt_RECO_leading_pt_full_" + trigger)
    eff_hlt_RECO_leading_eta_full[trigger] = MyFile.Get("eff_hlt_RECO_leading_eta_full_" + trigger)
    eff_hlt_RECO_leading_phi_full[trigger] = MyFile.Get("eff_hlt_RECO_leading_phi_full_" + trigger)
    
    eff_pt = (eff_hlt_RECO_leading_pt_full[trigger], r"Leading muon $p_\mathrm{T}$ [GeV]", "pt")
    eff_eta = (eff_hlt_RECO_leading_eta_full[trigger], r"Leading muon $\eta$", "eta")
    eff_phi = (eff_hlt_RECO_leading_phi_full[trigger], r"Leading muon $\phi$", "phi")

    eff_hlt_RECO_list = [eff_pt, eff_eta, eff_phi]

    makePlot(eff_pt, trigger, format='png')
    makePlot(eff_eta, trigger, format='png')
    makePlot(eff_phi, trigger, format='png')

    makePlot(eff_pt, trigger, format='pdf')
    makePlot(eff_eta, trigger, format='pdf')
    makePlot(eff_phi, trigger, format='pdf')

MyFile.Close()
