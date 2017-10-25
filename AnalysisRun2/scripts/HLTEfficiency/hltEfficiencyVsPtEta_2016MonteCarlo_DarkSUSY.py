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

mass_strings = {
    "0p25": "0.25", 
    "0p275" : "0.275", "0p3": "0.3", "0p4" : "0.4", "0p7" : "0.7", 
    "1" : "1.0", "1p5" : "1.5", "2" : "2.0", "5" : "5.0", "8p5" : "8.5"
}

mass_indices = {
    "0p25": 0, "0p3": 1, "0p4" : 2, "0p7" : 3, "1" : 4, "1p5" : 5, "2" : 6, "5" : 7, "8p5" : 8
}

cT_strings = {
  "0" : 0.0, "0p05" :  0.05, "0p1" :  0.10, "0p2" :  0.20, "0p5" :  0.50, "1" :  1.00, 
  "200" :  2.00, "300" :  3.00, "500" :  5.00, "1000" :  10.0, "2000" :  20.0, "8500" :  85.0
}

cT_strings2 = {
  "0" : "0", "0p05" : "0.05", "0p1" : "0.1", "0p2" : "0.2", "0p5" : "0.50", "1" : "1", 
  "2" : "2", "3" : "3", "5" : "5", "10" : "10", "20" : "20", "50" : "50", "100" : "100"
}

cT_indices = {
  "0" : 0, "0p05" : 1, "0p1" : 2, "0p2" : 3, "0p5" : 4, "1" : 5, 
  "2" : 6 ,  "3" : 7, "5" : 8, "10" : 9, "20" : 10, "50" : 11, "100" : 12
};

mass_colors = {
  "0250", kRed, "0275", kOrange, "0300", kSpring, "0400", kGreen+2, "0700", kAzure+9, 
  "1000", kBlue, "1500", kViolet+6, "2000", kMagenta, "8500", kBlack
}



##____________________________________________________________
def merge_darkSUSY_files(dirNames, triggerPaths):

    verbose = False

    if verbose: print dirNames
    n1, ma, ctau = decodeDarkSUSYFileName(dirNames[0])

    if verbose: print "Checking", "mN1", n1, "mA", ma, "cT", ctau

    darkSUSY = getDarkSUSYFileName(n1,ma,ctau)

    chain = ROOT.TChain("cutFlowAnalyzerPXBL3PXFL2/Events")

    if verbose: print "Adding files to the chain"
    chain = addfilesMany(chain, dirNames)
    chain.Merge("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_X_cT_Y_13TeV_PATANA_Total/" + darkSUSY + "_pythia8_PATANA_total.root")


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

    n1, ma, ctau = decodeDarkSUSYFileName(rootFile)

    if verbose: print "Checking", "mN1", n1, "mA", ma, "cT", ctau

    darkSUSY = getDarkSUSYFileName(n1,ma,ctau)

    for trigger in triggerPaths:
        hlt_RECO_leading_pt[darkSUSY + "_" + trigger] = ROOT.TH1D("hlt_RECO_leading_pt_" + trigger,"",25,0.,50.)
        hlt_RECO_leading_eta[darkSUSY + "_" + trigger] = ROOT.TH1D("hlt_RECO_leading_eta_" + trigger,"",25,-2.5,2.5)
        hlt_RECO_leading_phi[darkSUSY + "_" + trigger] = ROOT.TH1D("hlt_RECO_leading_phi_" + trigger,"",30,-ROOT.TMath.Pi(),ROOT.TMath.Pi())

        hlt_RECO_leading_pt_barrel[darkSUSY + "_" + trigger] = ROOT.TH1D("hlt_RECO_leading_pt_barrel_" + trigger,"",25,0.,50.)
        hlt_RECO_leading_eta_barrel[darkSUSY + "_" + trigger] = ROOT.TH1D("hlt_RECO_leading_eta_barrel_" + trigger,"",25,-2.5,2.5)
        hlt_RECO_leading_phi_barrel[darkSUSY + "_" + trigger] = ROOT.TH1D("hlt_RECO_leading_phi_barrel_" + trigger,"",30,-ROOT.TMath.Pi(),ROOT.TMath.Pi())

        hlt_RECO_leading_pt_full[darkSUSY + "_" + trigger] = ROOT.TH1D("hlt_RECO_leading_pt_full_" + trigger,"",25,0.,50.)
        hlt_RECO_leading_eta_full[darkSUSY + "_" + trigger] = ROOT.TH1D("hlt_RECO_leading_eta_full_" + trigger,"",25,-2.5,2.5)
        hlt_RECO_leading_phi_full[darkSUSY + "_" + trigger] = ROOT.TH1D("hlt_RECO_leading_phi_full_" + trigger,"",30,-ROOT.TMath.Pi(),ROOT.TMath.Pi())
        

    if (verbose): print "File ", rootFile, " does not exist"

    myfile = ROOT.TFile(rootFile)
    if (not myfile):
        return

    myfile.cd()
    tree = myfile.Get("Events")
    
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
                        hlt_RECO_leading_pt[darkSUSY + "_" + trigger].Fill(tree.selMu0_pT)
                        hlt_RECO_leading_eta[darkSUSY + "_" + trigger].Fill(tree.selMu0_eta)
                        hlt_RECO_leading_phi[darkSUSY + "_" + trigger].Fill(tree.selMu0_phi)

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
                        hlt_RECO_leading_pt_barrel[darkSUSY + "_" + trigger].Fill(tree.selMu0_pT)
                        hlt_RECO_leading_eta_barrel[darkSUSY + "_" + trigger].Fill(tree.selMu0_eta)
                        hlt_RECO_leading_phi_barrel[darkSUSY + "_" + trigger].Fill(tree.selMu0_phi)

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
                            hlt_RECO_leading_pt_full[darkSUSY + "_" + trigger].Fill(tree.selMu0_pT)
                            hlt_RECO_leading_eta_full[darkSUSY + "_" + trigger].Fill(tree.selMu0_eta)
                            hlt_RECO_leading_phi_full[darkSUSY + "_" + trigger].Fill(tree.selMu0_phi)

    ### make the efficiency plots
    for trigger in triggerPaths:
        eff_hlt_RECO_leading_pt[darkSUSY + "_" + trigger] = ROOT.TEfficiency(hlt_RECO_leading_pt[darkSUSY + "_" + trigger], RECO_leading_pt)
        eff_hlt_RECO_leading_eta[darkSUSY + "_" + trigger] = ROOT.TEfficiency(hlt_RECO_leading_eta[darkSUSY + "_" + trigger], RECO_leading_eta)
        eff_hlt_RECO_leading_phi[darkSUSY + "_" + trigger] = ROOT.TEfficiency(hlt_RECO_leading_phi[darkSUSY + "_" + trigger], RECO_leading_phi)

        eff_hlt_RECO_leading_pt_barrel[darkSUSY + "_" + trigger] = ROOT.TEfficiency(hlt_RECO_leading_pt_barrel[darkSUSY + "_" + trigger], RECO_leading_pt_barrel)
        eff_hlt_RECO_leading_eta_barrel[darkSUSY + "_" + trigger] = ROOT.TEfficiency(hlt_RECO_leading_eta_barrel[darkSUSY + "_" + trigger], RECO_leading_eta_barrel)
        eff_hlt_RECO_leading_phi_barrel[darkSUSY + "_" + trigger] = ROOT.TEfficiency(hlt_RECO_leading_phi_barrel[darkSUSY + "_" + trigger], RECO_leading_phi_barrel)

        eff_hlt_RECO_leading_pt_full[darkSUSY + "_" + trigger] = ROOT.TEfficiency(hlt_RECO_leading_pt_full[darkSUSY + "_" + trigger], RECO_leading_pt_full)
        eff_hlt_RECO_leading_eta_full[darkSUSY + "_" + trigger] = ROOT.TEfficiency(hlt_RECO_leading_eta_full[darkSUSY + "_" + trigger], RECO_leading_eta_full)
        eff_hlt_RECO_leading_phi_full[darkSUSY + "_" + trigger] = ROOT.TEfficiency(hlt_RECO_leading_phi_full[darkSUSY + "_" + trigger], RECO_leading_phi_full)

    ## save per mass point and per ctau point!!
    MyFile = TFile("HLT_efficiency_trigger_2016_" + darkSUSY + ".root","UPDATE");

    for trigger in triggerPaths:
        eff_hlt_RECO_leading_pt[darkSUSY + "_" + trigger].Write(darkSUSY + "_eff_hlt_RECO_leading_pt_" + trigger)
        eff_hlt_RECO_leading_eta[darkSUSY + "_" + trigger].Write(darkSUSY + "_eff_hlt_RECO_leading_eta_" + trigger)
        eff_hlt_RECO_leading_phi[darkSUSY + "_" + trigger].Write(darkSUSY + "_eff_hlt_RECO_leading_phi_" + trigger)

        eff_hlt_RECO_leading_pt_barrel[darkSUSY + "_" + trigger].Write(darkSUSY + "_eff_hlt_RECO_leading_pt_barrel_" + trigger)
        eff_hlt_RECO_leading_eta_barrel[darkSUSY + "_" + trigger].Write(darkSUSY + "_eff_hlt_RECO_leading_eta_barrel_" + trigger)
        eff_hlt_RECO_leading_phi_barrel[darkSUSY + "_" + trigger].Write(darkSUSY + "_eff_hlt_RECO_leading_phi_barrel_" + trigger)

        eff_hlt_RECO_leading_pt_full[darkSUSY + "_" + trigger].Write(darkSUSY + "_eff_hlt_RECO_leading_pt_full_" + trigger)
        eff_hlt_RECO_leading_eta_full[darkSUSY + "_" + trigger].Write(darkSUSY + "_eff_hlt_RECO_leading_eta_full_" + trigger)
        eff_hlt_RECO_leading_phi_full[darkSUSY + "_" + trigger].Write(darkSUSY + "_eff_hlt_RECO_leading_phi_full_" + trigger)

    MyFile.Close();
    
## triggers to examine
triggerPaths = ["HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx", 
                "HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx"]

## open the file with locations to MC files
mcSamples = readTextFileWithSamples("../DarkSUSY_All_2016.txt")

def calculateEfficiencies():

    for iSample, sample in enumerate(mcSamples):
        chain = TChain("cutFlowAnalyzerPXBL3PXFL2/Events")

        n1, ma, ctau = decodeDarkSUSYFileNameMany(sample)
        darkSUSY = getDarkSUSYFileName(n1,ma,ctau)

        if iSample < 11:
            print "Processing", iSample, "mN1", n1, "mA", ma, "cT", ctau
            efficiency_trigger(sample, triggerPaths)

#calculateEfficiencies()

#exit(1)

def makePlot(effTuple, darkSUSY, triggerPath, format='pdf'):

    ## setup histogram
    hist = HepPlotter("efficiency",1)
    hist.x_relative_size = 10
    hist.y_relative_size = 7
    hist.drawEffDist = False    # draw the physics distribution for efficiency (jet_pt for jet trigger)
    #hist.rebin       = 1
    hist.x_label     = effTuple[1]
    hist.y_label     = "Trigger efficiency"
    hist.format      = format      # file format for saving image
    hist.saveDir     = 'trigger_efficiency_plots_2016_DarkSUSY_13TeV_20171024/'
    hist.saveAs      = "eff_" + triggerPath + "_" + darkSUSY + "_" + effTuple[2] # save figure with name
    hist.CMSlabel       = 'outer'  # 'top left', 'top right'; hack code for something else
    hist.CMSlabelStatus = 'Simulation Preliminary'  # ('Simulation')+'Internal' || 'Preliminary' 
    hist.initialize()
    hist.plotLUMI = False
    hist.drawStatUncertainty = True    
    hist.Add(effTuple[0], draw='errorbar', color='blue', linecolor='blue', label=triggerPath.replace('_','\_'))

    n1, ma, ctau = decodeDarkSUSYFileName(darkSUSY)
    #print n1, ma, ctau

    hist.extra_text.Add(r"\textbf{Dark SUSY}", coords=[0.1,0.4])
    hist.extra_text.Add(r"$m_{N1} = %s~\mathrm{GeV}$"%n1, coords=[0.1,0.35])
    hist.extra_text.Add(r"$m_{\gamma D} = %s~\mathrm{GeV}$"%(mass_strings[ma]), coords=[0.1,0.3])
    hist.extra_text.Add(r"$c_{\tau} = %s~\mathrm{mm}$"%cT_strings2[ctau], coords=[0.1,0.25])
    plot = hist.execute()
    hist.savefig()




## open the file with locations to MC files
#mcSamples = readTextFileWithSamples("../DarkSUSY_All_2016.txt")

rootFiles = [

"DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_0_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_0p05_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_0p1_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_0p5_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_100_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_10_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_1_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_20_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_2_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_50_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_5_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_0p3_cT_0p05_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_0p3_cT_0p2_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_0p3_cT_3_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_0p3_cT_50_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_0p4_cT_0_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_0p4_cT_0p05_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_0p4_cT_0p1_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_0p4_cT_0p5_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_0p4_cT_100_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_0p4_cT_10_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_0p4_cT_1_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_0p4_cT_20_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_0p4_cT_2_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_0p4_cT_3_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_0p4_cT_50_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_0p7_cT_0_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_0p7_cT_0p05_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_0p7_cT_0p1_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_0p7_cT_0p2_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_0p7_cT_0p5_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_0p7_cT_100_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_0p7_cT_10_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_0p7_cT_1_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_0p7_cT_20_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_0p7_cT_3_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_0p7_cT_50_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_1_cT_0_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_1_cT_100_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_1_cT_10_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_1_cT_20_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_1_cT_3_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_1_cT_50_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_1_cT_5_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_1p5_cT_10_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_1p5_cT_3_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_1p5_cT_50_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_2_cT_10_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_2_cT_50_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_5_cT_0_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_5_cT_100_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_5_cT_10_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_5_cT_20_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_5_cT_3_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_5_cT_50_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_8p5_cT_0_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_8p5_cT_10_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_8p5_cT_20_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_8p5_cT_2_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_8p5_cT_3_13TeV_pythia8_PATANA_total.root",
"DarkSUSY_mH_125_mN1_10_mGammaD_8p5_cT_50_13TeV_pythia8_PATANA_total.root",

]


path = "/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_X_cT_Y_13TeV_PATANA_Total/"

def calculateEfficiencies2():

    for iFile, rootFile in enumerate(rootFiles):

        n1, ma, ctau = decodeDarkSUSYFileName(rootFile)
        darkSUSY = getDarkSUSYFileName(n1,ma,ctau)

        if ma == "8p5":
        #if iFile >= 26 and iFile <= 36 :
            if not ctau == "50":
                continue

            print "Checking", iFile, "mN1", n1, "mA", ma, "cT", ctau
            print path + rootFile
            efficiency_trigger(path + rootFile, triggerPaths)

#calculateEfficiencies2()

#exit(1)


## make plots

eff_hlt_RECO_leading_pt = {}
eff_hlt_RECO_leading_eta = {}
eff_hlt_RECO_leading_phi = {}

eff_hlt_RECO_leading_pt_barrel = {}
eff_hlt_RECO_leading_eta_barrel = {}
eff_hlt_RECO_leading_phi_barrel = {}

eff_hlt_RECO_leading_pt_full = {}
eff_hlt_RECO_leading_eta_full = {}
eff_hlt_RECO_leading_phi_full = {}


darkSUSY_HLT_Samples = [
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_0_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_0p05_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_0p1_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_0p5_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_100_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_10_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_1_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_20_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_2_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_50_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_5_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p3_cT_0p05_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p3_cT_0p2_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p3_cT_3_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p3_cT_50_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p4_cT_0_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p4_cT_0p05_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p4_cT_0p1_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p4_cT_0p5_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p4_cT_100_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p4_cT_10_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p4_cT_1_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p4_cT_20_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p4_cT_2_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p4_cT_3_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p4_cT_50_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p7_cT_0_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p7_cT_0p05_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p7_cT_0p1_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p7_cT_0p2_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p7_cT_0p5_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p7_cT_100_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p7_cT_10_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p7_cT_1_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p7_cT_20_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p7_cT_3_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_0p7_cT_50_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_1_cT_0_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_1_cT_100_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_1_cT_10_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_1_cT_20_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_1_cT_3_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_1_cT_50_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_1_cT_5_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_1p5_cT_10_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_1p5_cT_3_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_1p5_cT_50_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_2_cT_10_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_2_cT_50_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_5_cT_0_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_5_cT_100_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_5_cT_10_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_5_cT_20_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_5_cT_3_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_5_cT_50_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_8p5_cT_0_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_8p5_cT_10_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_8p5_cT_20_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_8p5_cT_2_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_8p5_cT_3_13TeV.root",
    "HLT_efficiency_trigger_2016_DarkSUSY_mH_125_mN1_10_mGammaD_8p5_cT_50_13TeV.root",
]


for sample in darkSUSY_HLT_Samples:

    ## do not process
    continue
    
    MyFile = TFile(sample);


    n1, ma, ctau = decodeDarkSUSYFileName(sample)
    darkSUSY = getDarkSUSYFileName(n1,ma,ctau)

    print "Checking", "mN1", n1, "mA", ma, "cT", ctau
    if not ma == "8p5":
        continue


    ## make trigger efficiencies for each trigger path
    for trigger in triggerPaths:
        print trigger
        print darkSUSY + "_eff_hlt_RECO_leading_pt_" + trigger

        eff_hlt_RECO_leading_pt[darkSUSY + "_" + trigger] = MyFile.Get(darkSUSY + "_eff_hlt_RECO_leading_pt_" + trigger)
        eff_hlt_RECO_leading_eta[darkSUSY + "_" + trigger] = MyFile.Get(darkSUSY + "_eff_hlt_RECO_leading_eta_" + trigger)
        eff_hlt_RECO_leading_phi[darkSUSY + "_" + trigger] = MyFile.Get(darkSUSY + "_eff_hlt_RECO_leading_phi_" + trigger)
        
        eff_pt = (eff_hlt_RECO_leading_pt[darkSUSY + "_" + trigger], r"Leading muon $p_\mathrm{T}$ [GeV]", "pt")
        eff_eta = (eff_hlt_RECO_leading_eta[darkSUSY + "_" + trigger], r"Leading muon $\eta$", "eta")
        eff_phi = (eff_hlt_RECO_leading_phi[darkSUSY + "_" + trigger], r"Leading muon $\phi$", "phi")
        
        eff_hlt_RECO_list = [eff_pt, eff_eta, eff_phi]
            
        makePlot(eff_pt, darkSUSY, trigger, format='png')
        makePlot(eff_eta, darkSUSY, trigger, format='png')
        makePlot(eff_phi, darkSUSY, trigger, format='png')
            
        makePlot(eff_pt, darkSUSY, trigger, format='pdf')
        makePlot(eff_eta, darkSUSY, trigger, format='pdf')
        makePlot(eff_phi, darkSUSY, trigger, format='pdf')

    
        eff_hlt_RECO_leading_pt_full[darkSUSY + "_" + trigger] = MyFile.Get(darkSUSY + "_eff_hlt_RECO_leading_pt_full_" + trigger)
        eff_hlt_RECO_leading_eta_full[darkSUSY + "_" + trigger] = MyFile.Get(darkSUSY + "_eff_hlt_RECO_leading_eta_full_" + trigger)
        eff_hlt_RECO_leading_phi_full[darkSUSY + "_" + trigger] = MyFile.Get(darkSUSY + "_eff_hlt_RECO_leading_phi_full_" + trigger)
    
        eff_pt = (eff_hlt_RECO_leading_pt_full[darkSUSY + "_" + trigger], r"Leading muon $p_\mathrm{T}$ [GeV]", "pt")
        eff_eta = (eff_hlt_RECO_leading_eta_full[darkSUSY + "_" + trigger], r"Leading muon $\eta$", "eta")
        eff_phi = (eff_hlt_RECO_leading_phi_full[darkSUSY + "_" + trigger], r"Leading muon $\phi$", "phi")

        eff_hlt_RECO_list = [eff_pt, eff_eta, eff_phi]

        makePlot(eff_pt, darkSUSY, trigger, format='png')
        makePlot(eff_eta, darkSUSY, trigger, format='png')
        makePlot(eff_phi, darkSUSY, trigger, format='png')

        makePlot(eff_pt, darkSUSY, trigger, format='pdf')
        makePlot(eff_eta, darkSUSY, trigger, format='pdf')
        makePlot(eff_phi, darkSUSY, trigger, format='pdf')

    MyFile.Close();
    
        

## make a 2D efficiency plot
def get_mass_index(massStr):
    return mass_indices[massStr]

def get_cT_index(cTStr):
  return cT_indices[cTStr]

def getAverageEfficiency(myEff):
  return myEff.GetPassedHistogram().GetEntries() / myEff.GetTotalHistogram().GetEntries();

def getAverageEfficiencyError(myEff):
  num = myEff.GetPassedHistogram().GetEntries();
  denom = myEff.GetTotalHistogram().GetEntries();
  eff_uncert = sqrt( ((num/(1.0*denom))*(1-(num/(1.0*denom)) ))/(1.0*denom) );
  return eff_uncert;


def make_2D_plot(selection, trigger):

    if selection == '': selStr = ""
    elif selection == 'barrel': selStr = "_barrel"
    elif selection == 'full': selStr = "_full"
    else: selStr == ""

    c = TCanvas("c","c",800,600);
    gStyle.SetOptStat(0);
    gStyle.SetPalette(55);
    gStyle.SetTitleStyle( 0 );
    gStyle.SetTitleAlign(13); # coord in top left                                                                                                                              
    gStyle.SetTitleX(0.);
    gStyle.SetTitleY(1.);
    gStyle.SetTitleW(1);
    gStyle.SetTitleH(0.058);
    gStyle.SetTitleBorderSize( 0 );
  
    gStyle.SetPadLeftMargin(0.126);
    gStyle.SetPadRightMargin(0.15);
    gStyle.SetPadTopMargin(0.06);
    gStyle.SetPadBottomMargin(0.13);
    gStyle.SetOptStat( 0 );
    gStyle.SetMarkerStyle(1);
    gStyle.SetTitleFontSize(0.07);
  
    base = TH2F("","#scale[1.4]{#font[61]{CMS}} #font[52]{Simulation preliminary}                       13 TeV", 9, 1, 10, 13, 1, 14);
    base.GetXaxis().SetTitle("m_{#gamma_{D}} [Gev]");
    base.GetYaxis().SetTitle("c#tau_{#gamma_{D}} [mm]");
    base.GetZaxis().SetRangeUser(0.7,1.0);
    base.GetXaxis().SetTitleOffset(1.2);
    base.GetYaxis().SetTitleOffset(1.2);
    base.GetXaxis().SetTitleSize(0.05);
    base.GetYaxis().SetTitleSize(0.05);
    base.GetXaxis().SetLabelSize(0.05);
    base.GetYaxis().SetLabelSize(0.05);

    eff_hlt_RECO_leading_pt = {}
    eff_hlt_RECO_leading_eta = {}
    eff_hlt_RECO_leading_phi = {}
    
    for sample in darkSUSY_HLT_Samples:

        MyFile = TFile(sample);

        n1, ma, ctau = decodeDarkSUSYFileName(sample)
        darkSUSY = getDarkSUSYFileName(n1,ma,ctau)
        print "Checking", "mN1", n1, "mA", ma, "cT", ctau

        mass_index = get_mass_index(ma) + 1;
        cT_index = get_cT_index(ctau) + 1;

        eff_hlt_RECO_leading_pt[darkSUSY + "_" + trigger] = MyFile.Get(darkSUSY + "_eff_hlt_RECO_leading_pt" + selStr + "_" + trigger)
        eff_hlt_RECO_leading_eta[darkSUSY + "_" + trigger] = MyFile.Get(darkSUSY + "_eff_hlt_RECO_leading_eta" + selStr + "_" + trigger)
        eff_hlt_RECO_leading_phi[darkSUSY + "_" + trigger] = MyFile.Get(darkSUSY + "_eff_hlt_RECO_leading_phi" + selStr + "_" + trigger)
        
        base.SetBinContent( mass_index , cT_index, getAverageEfficiency(eff_hlt_RECO_leading_eta[darkSUSY + "_" + trigger]));
        base.GetXaxis().SetBinLabel(mass_index, mass_strings[ma]);
        base.GetYaxis().SetBinLabel(cT_index, cT_strings2[ctau]);

    base.Draw("COLZ TEXT");

    c.SaveAs("DarkSUSY_GammaD_cT_2016MonteCarlo_efficiency" + selStr + "_" + trigger + ".pdf","recreate");


## make trigger efficiencies for each trigger path
for trigger in triggerPaths:
    print trigger

    make_2D_plot("", trigger)
    make_2D_plot("", trigger)
    make_2D_plot("barrel", trigger)
    make_2D_plot("full", trigger)
