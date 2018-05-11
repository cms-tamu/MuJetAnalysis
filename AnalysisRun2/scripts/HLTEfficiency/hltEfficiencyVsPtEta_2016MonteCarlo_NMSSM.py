import sys
from ROOT import *
from argparse import ArgumentParser

from hepPlotter import HepPlotter
import hepPlotterTools as hpt
#import hepPlotterLabels as hpl

import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from Helpers import *

from subprocess import call

##____________________________________________________________
def efficiency_trigger(rootFile, triggerPaths):

    verbose = False

    if verbose: print "Preparing histograms"

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

    nmssmString = "NMSSM_HToAATo4Mu_M_125_M_2"

    for trigger in triggerPaths:
        hlt_RECO_leading_pt[nmssmString + "_" + trigger] = ROOT.TH1D("hlt_RECO_leading_pt_" + trigger,"",25,0.,50.)
        hlt_RECO_leading_eta[nmssmString + "_" + trigger] = ROOT.TH1D("hlt_RECO_leading_eta_" + trigger,"",25,-2.5,2.5)
        hlt_RECO_leading_phi[nmssmString + "_" + trigger] = ROOT.TH1D("hlt_RECO_leading_phi_" + trigger,"",30,-ROOT.TMath.Pi(),ROOT.TMath.Pi())

        hlt_RECO_leading_pt_barrel[nmssmString + "_" + trigger] = ROOT.TH1D("hlt_RECO_leading_pt_barrel_" + trigger,"",25,0.,50.)
        hlt_RECO_leading_eta_barrel[nmssmString + "_" + trigger] = ROOT.TH1D("hlt_RECO_leading_eta_barrel_" + trigger,"",25,-2.5,2.5)
        hlt_RECO_leading_phi_barrel[nmssmString + "_" + trigger] = ROOT.TH1D("hlt_RECO_leading_phi_barrel_" + trigger,"",30,-ROOT.TMath.Pi(),ROOT.TMath.Pi())

        hlt_RECO_leading_pt_full[nmssmString + "_" + trigger] = ROOT.TH1D("hlt_RECO_leading_pt_full_" + trigger,"",25,0.,50.)
        hlt_RECO_leading_eta_full[nmssmString + "_" + trigger] = ROOT.TH1D("hlt_RECO_leading_eta_full_" + trigger,"",25,-2.5,2.5)
        hlt_RECO_leading_phi_full[nmssmString + "_" + trigger] = ROOT.TH1D("hlt_RECO_leading_phi_full_" + trigger,"",30,-ROOT.TMath.Pi(),ROOT.TMath.Pi())
        

    if (verbose): print "File ", rootFile, " does not exist"

    myfile = ROOT.TFile(rootFile)
    if (not myfile):
        return

    myfile.cd()
    tree = myfile.Get("cutFlowAnalyzerPXBL3PXFL2/Events")
    
    entries = tree.GetEntries()
    if (verbose): print "  Events  ", entries

    for k in range(0, entries):

            if k%10000==0: print "Processing event ", k, "/", entries
            tree.GetEntry(k)

            ## check for 4 reco muons 
            nMu = int(tree.selMu0_pT != -100) + int(tree.selMu1_pT != -100) + int(tree.selMu2_pT != -100) + int(tree.selMu3_pT != -100) 

            if (nMu<4):
                continue

            nMuPt8 = int(tree.selMu0_pT >= 8) + int(tree.selMu1_pT >= 8) + int(tree.selMu2_pT >= 8) + int(tree.selMu3_pT >= 8)
            nMuPt17 = int(tree.selMu0_pT >= 17) + int(tree.selMu1_pT >= 17) + int(tree.selMu2_pT >= 17) + int(tree.selMu3_pT >= 17)
            nMuPt17Barrel = (int(tree.selMu0_pT >= 17 and abs(tree.selMu0_eta)<=0.9) + 
                             int(tree.selMu1_pT >= 17 and abs(tree.selMu1_eta)<=0.9) + 
                             int(tree.selMu2_pT >= 17 and abs(tree.selMu2_eta)<=0.9) + 
                             int(tree.selMu3_pT >= 17 and abs(tree.selMu3_eta)<=0.9))

            #print nMu, tree.selMu0_pT, tree.selMu1_pT, tree.selMu2_pT, tree.selMu3_pT

            ## require 4mu selection!!!
            if (nMuPt8>=4 and nMuPt17>=1):

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
                        hlt_RECO_leading_pt[nmssmString + "_" + trigger].Fill(tree.selMu0_pT)
                        hlt_RECO_leading_eta[nmssmString + "_" + trigger].Fill(tree.selMu0_eta)
                        hlt_RECO_leading_phi[nmssmString + "_" + trigger].Fill(tree.selMu0_phi)

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
                        hlt_RECO_leading_pt_barrel[nmssmString + "_" + trigger].Fill(tree.selMu0_pT)
                        hlt_RECO_leading_eta_barrel[nmssmString + "_" + trigger].Fill(tree.selMu0_eta)
                        hlt_RECO_leading_phi_barrel[nmssmString + "_" + trigger].Fill(tree.selMu0_phi)

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
                            hlt_RECO_leading_pt_full[nmssmString + "_" + trigger].Fill(tree.selMu0_pT)
                            hlt_RECO_leading_eta_full[nmssmString + "_" + trigger].Fill(tree.selMu0_eta)
                            hlt_RECO_leading_phi_full[nmssmString + "_" + trigger].Fill(tree.selMu0_phi)

    ### make the efficiency plots
    for trigger in triggerPaths:
        eff_hlt_RECO_leading_pt[nmssmString + "_" + trigger] = ROOT.TEfficiency(hlt_RECO_leading_pt[nmssmString + "_" + trigger], RECO_leading_pt)
        eff_hlt_RECO_leading_eta[nmssmString + "_" + trigger] = ROOT.TEfficiency(hlt_RECO_leading_eta[nmssmString + "_" + trigger], RECO_leading_eta)
        eff_hlt_RECO_leading_phi[nmssmString + "_" + trigger] = ROOT.TEfficiency(hlt_RECO_leading_phi[nmssmString + "_" + trigger], RECO_leading_phi)

        eff_hlt_RECO_leading_pt_barrel[nmssmString + "_" + trigger] = ROOT.TEfficiency(hlt_RECO_leading_pt_barrel[nmssmString + "_" + trigger], RECO_leading_pt_barrel)
        eff_hlt_RECO_leading_eta_barrel[nmssmString + "_" + trigger] = ROOT.TEfficiency(hlt_RECO_leading_eta_barrel[nmssmString + "_" + trigger], RECO_leading_eta_barrel)
        eff_hlt_RECO_leading_phi_barrel[nmssmString + "_" + trigger] = ROOT.TEfficiency(hlt_RECO_leading_phi_barrel[nmssmString + "_" + trigger], RECO_leading_phi_barrel)

        eff_hlt_RECO_leading_pt_full[nmssmString + "_" + trigger] = ROOT.TEfficiency(hlt_RECO_leading_pt_full[nmssmString + "_" + trigger], RECO_leading_pt_full)
        eff_hlt_RECO_leading_eta_full[nmssmString + "_" + trigger] = ROOT.TEfficiency(hlt_RECO_leading_eta_full[nmssmString + "_" + trigger], RECO_leading_eta_full)
        eff_hlt_RECO_leading_phi_full[nmssmString + "_" + trigger] = ROOT.TEfficiency(hlt_RECO_leading_phi_full[nmssmString + "_" + trigger], RECO_leading_phi_full)

    ## save per mass point and per ctau point!!
    MyFile = TFile("HLT_efficiency_trigger_2016_" + nmssmString + ".root","UPDATE");

    for trigger in triggerPaths:
        eff_hlt_RECO_leading_pt[nmssmString + "_" + trigger].Write(nmssmString + "_eff_hlt_RECO_leading_pt_" + trigger)
        eff_hlt_RECO_leading_eta[nmssmString + "_" + trigger].Write(nmssmString + "_eff_hlt_RECO_leading_eta_" + trigger)
        eff_hlt_RECO_leading_phi[nmssmString + "_" + trigger].Write(nmssmString + "_eff_hlt_RECO_leading_phi_" + trigger)

        eff_hlt_RECO_leading_pt_barrel[nmssmString + "_" + trigger].Write(nmssmString + "_eff_hlt_RECO_leading_pt_barrel_" + trigger)
        eff_hlt_RECO_leading_eta_barrel[nmssmString + "_" + trigger].Write(nmssmString + "_eff_hlt_RECO_leading_eta_barrel_" + trigger)
        eff_hlt_RECO_leading_phi_barrel[nmssmString + "_" + trigger].Write(nmssmString + "_eff_hlt_RECO_leading_phi_barrel_" + trigger)

        eff_hlt_RECO_leading_pt_full[nmssmString + "_" + trigger].Write(nmssmString + "_eff_hlt_RECO_leading_pt_full_" + trigger)
        eff_hlt_RECO_leading_eta_full[nmssmString + "_" + trigger].Write(nmssmString + "_eff_hlt_RECO_leading_eta_full_" + trigger)
        eff_hlt_RECO_leading_phi_full[nmssmString + "_" + trigger].Write(nmssmString + "_eff_hlt_RECO_leading_phi_full_" + trigger)

    MyFile.Close();
    
## triggers to examine
triggerPaths = ["HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx", 
                "HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx"]

def calculateEfficiencies():

    efficiency_trigger("/fdata/hepx/store/user/dildick/NMSSM_HToAATo4Mu_M-125_M-2_TuneCUETP8M1_13TeV_pythia8/out_ana_total.root", triggerPaths)

calculateEfficiencies()

def makePlot(effTuple, nmssmString, triggerPath, format='pdf'):

    ## setup histogram
    hist = HepPlotter("efficiency",1)
    hist.x_relative_size = 10
    hist.y_relative_size = 7
    hist.drawEffDist = False    # draw the physics distribution for efficiency (jet_pt for jet trigger)
    #hist.rebin       = 1
    hist.x_label     = effTuple[1]
    hist.y_label     = "Trigger efficiency"
    hist.format      = format      # file format for saving image
    hist.saveDir     = 'trigger_efficiency_plots_2016_DarkSUSY_13TeV_20180506/'
    if 'full' in effTuple[0].GetName():
        hist.saveAs      = "eff_" + triggerPath + "_" + nmssmString + "_MuJetVtxDzIso_" + effTuple[2] # save figure with name
    elif 'barrel' in effTuple[0].GetName():
        hist.saveAs      = "eff_" + triggerPath + "_" + nmssmString + "_barrel_" + effTuple[2] # save figure with name
    else:
        hist.saveAs      = "eff_" + triggerPath + "_" + nmssmString + "_" + effTuple[2] # save figure with name
    hist.CMSlabel       = 'outer'  # 'top left', 'top right'; hack code for something else
    hist.CMSlabelStatus = 'Simulation'  # ('Simulation')+'Internal' || 'Preliminary' 
    hist.initialize()
    hist.plotLUMI = False
    hist.drawStatUncertainty = True    
    hist.Add(effTuple[0], draw='errorbar', color='blue', linecolor='blue', label=triggerPath.replace('_','\_'))

    hist.extra_text.Add(r"\textbf{NMSSM}", coords=[0.1,0.4])
    hist.extra_text.Add(r"$m_{H} = 125~\mathrm{GeV}$", coords=[0.1,0.35])
    hist.extra_text.Add(r"$m_{A} = 2~\mathrm{GeV}$", coords=[0.1,0.3])
    plot = hist.execute()
    hist.savefig()


nmssmString = "NMSSM_HToAATo4Mu_M_125_M_2"

MyFile = TFile("HLT_efficiency_trigger_2016_" + nmssmString + ".root")


eff_hlt_RECO_leading_pt = {}
eff_hlt_RECO_leading_eta = {}
eff_hlt_RECO_leading_phi = {}

eff_hlt_RECO_leading_pt_barrel = {}
eff_hlt_RECO_leading_eta_barrel = {}
eff_hlt_RECO_leading_phi_barrel = {}

eff_hlt_RECO_leading_pt_full = {}
eff_hlt_RECO_leading_eta_full = {}
eff_hlt_RECO_leading_phi_full = {}

for trigger in triggerPaths:
        print trigger
        eff_hlt_RECO_leading_pt[nmssmString + "_" + trigger] = MyFile.Get(nmssmString + "_eff_hlt_RECO_leading_pt_" + trigger)
        eff_hlt_RECO_leading_eta[nmssmString + "_" + trigger] = MyFile.Get(nmssmString + "_eff_hlt_RECO_leading_eta_" + trigger)
        eff_hlt_RECO_leading_phi[nmssmString + "_" + trigger] = MyFile.Get(nmssmString + "_eff_hlt_RECO_leading_phi_" + trigger)
        
        eff_pt = (eff_hlt_RECO_leading_pt[nmssmString + "_" + trigger], r"Leading muon $p_\mathrm{T}$ [GeV]", "pt")
        eff_eta = (eff_hlt_RECO_leading_eta[nmssmString + "_" + trigger], r"Leading muon $\eta$", "eta")
        eff_phi = (eff_hlt_RECO_leading_phi[nmssmString + "_" + trigger], r"Leading muon $\phi$", "phi")
        
        eff_hlt_RECO_list = [eff_pt, eff_eta, eff_phi]
            
        makePlot(eff_pt, nmssmString, trigger, format='png')
        makePlot(eff_eta, nmssmString, trigger, format='png')
        makePlot(eff_phi, nmssmString, trigger, format='png')
            
        makePlot(eff_pt, nmssmString, trigger, format='pdf')
        makePlot(eff_eta, nmssmString, trigger, format='pdf')
        makePlot(eff_phi, nmssmString, trigger, format='pdf')

    
        eff_hlt_RECO_leading_pt_barrel[nmssmString + "_" + trigger] = MyFile.Get(nmssmString + "_eff_hlt_RECO_leading_pt_barrel_" + trigger)
        eff_hlt_RECO_leading_eta_barrel[nmssmString + "_" + trigger] = MyFile.Get(nmssmString + "_eff_hlt_RECO_leading_eta_barrel_" + trigger)
        eff_hlt_RECO_leading_phi_barrel[nmssmString + "_" + trigger] = MyFile.Get(nmssmString + "_eff_hlt_RECO_leading_phi_barrel_" + trigger)
    
        eff_pt = (eff_hlt_RECO_leading_pt_barrel[nmssmString + "_" + trigger], r"Leading muon $p_\mathrm{T}$ [GeV]", "pt")
        eff_eta = (eff_hlt_RECO_leading_eta_barrel[nmssmString + "_" + trigger], r"Leading muon $\eta$", "eta")
        eff_phi = (eff_hlt_RECO_leading_phi_barrel[nmssmString + "_" + trigger], r"Leading muon $\phi$", "phi")

        eff_hlt_RECO_list = [eff_pt, eff_eta, eff_phi]

        makePlot(eff_pt, nmssmString, trigger, format='png')
        makePlot(eff_eta, nmssmString, trigger, format='png')
        makePlot(eff_phi, nmssmString, trigger, format='png')

        makePlot(eff_pt, nmssmString, trigger, format='pdf')
        makePlot(eff_eta, nmssmString, trigger, format='pdf')
        makePlot(eff_phi, nmssmString, trigger, format='pdf')


        eff_hlt_RECO_leading_pt_full[nmssmString + "_" + trigger] = MyFile.Get(nmssmString + "_eff_hlt_RECO_leading_pt_full_" + trigger)
        eff_hlt_RECO_leading_eta_full[nmssmString + "_" + trigger] = MyFile.Get(nmssmString + "_eff_hlt_RECO_leading_eta_full_" + trigger)
        eff_hlt_RECO_leading_phi_full[nmssmString + "_" + trigger] = MyFile.Get(nmssmString + "_eff_hlt_RECO_leading_phi_full_" + trigger)
    
        eff_pt = (eff_hlt_RECO_leading_pt_full[nmssmString + "_" + trigger], r"Leading muon $p_\mathrm{T}$ [GeV]", "pt")
        eff_eta = (eff_hlt_RECO_leading_eta_full[nmssmString + "_" + trigger], r"Leading muon $\eta$", "eta")
        eff_phi = (eff_hlt_RECO_leading_phi_full[nmssmString + "_" + trigger], r"Leading muon $\phi$", "phi")

        eff_hlt_RECO_list = [eff_pt, eff_eta, eff_phi]

        makePlot(eff_pt, nmssmString, trigger, format='png')
        makePlot(eff_eta, nmssmString, trigger, format='png')
        makePlot(eff_phi, nmssmString, trigger, format='png')

        makePlot(eff_pt, nmssmString, trigger, format='pdf')
        makePlot(eff_eta, nmssmString, trigger, format='pdf')
        makePlot(eff_phi, nmssmString, trigger, format='pdf')


MyFile.Close();
