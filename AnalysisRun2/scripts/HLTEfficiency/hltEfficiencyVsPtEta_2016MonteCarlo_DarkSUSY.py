import sys
from ROOT import *
from argparse import ArgumentParser

from hepPlotter import HepPlotter
import hepPlotterTools as hpt
#import hepPlotterLabels as hpl

import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from Helpers import *

mass_strings = {
    "0p25": "0.25", 
    "0p275" : "0.275", "0p3": "0.3", "0p4" : "0.4", "0700" : "0.7", 
    "1" : "1.0", "1500" : "1.5", "2000" : "2.0", "8500" : "8.5"
}
cT_strings = {
  "0" : 0.0, "0p05" :  0.05, "0p1" :  0.10, "0p2" :  0.20, "0p5" :  0.50, "1" :  1.00, 
  "200" :  2.00, "300" :  3.00, "500" :  5.00, "1000" :  10.0, "2000" :  20.0, "8500" :  85.0
}

cT_strings2 = {
  "0" : "0", "0p05" : "0.05", "0p1" : "0.1", "0p2" : "0.2", "0p5" : "0.50", "1" : "1", 
  "2" : "2", "3" : "3", "5" : "5", "10" : "10", "20" : "20", "50" : "50", "100" : "100"
}

mass_colors = {
  "0250", kRed, "0275", kOrange, "0300", kSpring, "0400", kGreen+2, "0700", kAzure+9, 
  "1000", kBlue, "1500", kViolet+6, "2000", kMagenta, "8500", kBlack
}



##____________________________________________________________
def efficiency_trigger(dirNames, triggerPaths):


    verbose = False

    if verbose: print dirNames
    n1, ma, ctau = decodeDarkSUSYFileName(dirNames[0])

    if verbose: print "Checking", "mN1", n1, "mA", ma, "cT", ctau

    chain = ROOT.TChain("cutFlowAnalyzerPXBL3PXFL2/Events")

    if verbose: print "Preparing histograms"

    darkSUSY = getDarkSUSYFileName(n1,ma,ctau)

    RECO_leading_pt = ROOT.TH1D("RECO_leading_pt","",25,0.,50.);
    RECO_leading_eta = ROOT.TH1D("RECO_leading_eta","",25,-2.5,2.5);
    RECO_leading_phi = ROOT.TH1D("RECO_leading_phi","",30,-ROOT.TMath.Pi(),ROOT.TMath.Pi());

    hlt_RECO_leading_pt = {}
    hlt_RECO_leading_eta = {}
    hlt_RECO_leading_phi = {}
    
    eff_hlt_RECO_leading_pt = {}
    eff_hlt_RECO_leading_eta = {}
    eff_hlt_RECO_leading_phi = {}

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
        hlt_RECO_leading_pt[darkSUSY + "_" + trigger] = ROOT.TH1D("hlt_RECO_leading_pt_" + trigger,"",25,0.,50.)
        hlt_RECO_leading_eta[darkSUSY + "_" + trigger] = ROOT.TH1D("hlt_RECO_leading_eta_" + trigger,"",25,-2.5,2.5)
        hlt_RECO_leading_phi[darkSUSY + "_" + trigger] = ROOT.TH1D("hlt_RECO_leading_phi_" + trigger,"",30,-ROOT.TMath.Pi(),ROOT.TMath.Pi())

        hlt_RECO_leading_pt_full[darkSUSY + "_" + trigger] = ROOT.TH1D("hlt_RECO_leading_pt_full_" + trigger,"",25,0.,50.)
        hlt_RECO_leading_eta_full[darkSUSY + "_" + trigger] = ROOT.TH1D("hlt_RECO_leading_eta_full_" + trigger,"",25,-2.5,2.5)
        hlt_RECO_leading_phi_full[darkSUSY + "_" + trigger] = ROOT.TH1D("hlt_RECO_leading_phi_full_" + trigger,"",30,-ROOT.TMath.Pi(),ROOT.TMath.Pi())
        
    if verbose: print "Adding files to the chain"
    addfilesMany(chain, dirNames)

    if verbose: print "Loop over the chain", chain.GetEntries()

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
        
        tree = myfile.Get("cutFlowAnalyzerPXBL3PXFL2/Events")

        if not tree: 
            if (verbose): print "Tree cutFlowAnalyzerPXBL3PXFL2/Events does not exist"
            continue

        if (verbose): print "  Events  ", tree.GetEntries()

        for k in range(0, tree.GetEntries()):

            if k%100000==0: print "Processing event ", k 
            tree.GetEntry(k)

            ## check for 4 reco muons 
            nMu = 0
            
            if tree.selMu0_pT != -100: nMu += 1
            if tree.selMu1_pT != -100: nMu += 1
            if tree.selMu2_pT != -100: nMu += 1
            if tree.selMu3_pT != -100: nMu += 1
      
            if (nMu<4):
                continue

            ## require baseline selection!!!
            if (tree.is4SelMu8 and tree.is1SelMu17):

                if (verbose): print "Pass denom"
                RECO_leading_pt_fid.Fill(tree.selMu0_pT)
                RECO_leading_eta_fid.Fill(tree.selMu0_eta)
                RECO_leading_phi_fid.Fill(tree.selMu0_phi)
                
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

    ### make the efficiency plots
    for trigger in triggerPaths:
        eff_hlt_RECO_leading_pt[darkSUSY + "_" + trigger] = ROOT.TEfficiency(hlt_RECO_leading_pt[darkSUSY + "_" + trigger], RECO_leading_pt)
        eff_hlt_RECO_leading_eta[darkSUSY + "_" + trigger] = ROOT.TEfficiency(hlt_RECO_leading_eta[darkSUSY + "_" + trigger], RECO_leading_eta)
        eff_hlt_RECO_leading_phi[darkSUSY + "_" + trigger] = ROOT.TEfficiency(hlt_RECO_leading_phi[darkSUSY + "_" + trigger], RECO_leading_phi)

        eff_hlt_RECO_leading_pt_full[darkSUSY + "_" + trigger] = ROOT.TEfficiency(hlt_RECO_leading_pt_full[darkSUSY + "_" + trigger], RECO_leading_pt_full)
        eff_hlt_RECO_leading_eta_full[darkSUSY + "_" + trigger] = ROOT.TEfficiency(hlt_RECO_leading_eta_full[darkSUSY + "_" + trigger], RECO_leading_eta_full)
        eff_hlt_RECO_leading_phi_full[darkSUSY + "_" + trigger] = ROOT.TEfficiency(hlt_RECO_leading_phi_full[darkSUSY + "_" + trigger], RECO_leading_phi_full)

        ## because ROOT is fucking retarded...
        eff_hlt_RECO_leading_pt_fid[darkSUSY + "_" + trigger].SetName(darkSUSY + "_eff_hlt_RECO_leading_pt_fid_" + trigger)
        eff_hlt_RECO_leading_eta_fid[darkSUSY + "_" + trigger].SetName(darkSUSY + "_eff_hlt_RECO_leading_eta_fid_" + trigger)
        eff_hlt_RECO_leading_phi_fid[darkSUSY + "_" + trigger].SetName(darkSUSY + "_eff_hlt_RECO_leading_phi_fid_" + trigger)
        
    ## save per mass point and per ctau point!!
    MyFile = TFile("HLT_efficiency_trigger_2016_DarkSUSY_13TeV.root","UPDATE");

    for trigger in triggerPaths:
        eff_hlt_RECO_leading_pt[darkSUSY + "_" + trigger].Write(darkSUSY + "_eff_hlt_RECO_leading_pt_" + trigger)
        eff_hlt_RECO_leading_eta[darkSUSY + "_" + trigger].Write(darkSUSY + "_eff_hlt_RECO_leading_eta_" + trigger)
        eff_hlt_RECO_leading_phi[darkSUSY + "_" + trigger].Write(darkSUSY + "_eff_hlt_RECO_leading_phi_" + trigger)

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

    for sample in mcSamples:
        chain = TChain("cutFlowAnalyzerPXBL3PXFL2/Events")

        n1, ma, ctau = decodeDarkSUSYFileNameMany(sample)
        print "Checking", "mN1", n1, "mA", ma, "cT", ctau

        print "Processing", n1, ma, ctau
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
    hist.saveDir     = 'trigger_efficiency_plots_2016_DarkSUSY_13TeV_20171011/'
    hist.saveAs      = "eff_" + triggerPath + "_" + darkSUSY + "_" + effTuple[2] # save figure with name
    hist.CMSlabel       = 'outer'  # 'top left', 'top right'; hack code for something else
    hist.CMSlabelStatus = 'Simulation Preliminary'  # ('Simulation')+'Internal' || 'Preliminary' 
    hist.initialize()
    hist.plotLUMI = False
    hist.drawStatUncertainty = True    
    hist.Add(effTuple[0], draw='errorbar', color='blue', linecolor='blue', label=triggerPath.replace('_','\_'))

    n1, ma, ctau = decodeDarkSUSYFileName(darkSUSY)
    print n1, ma, ctau

    hist.extra_text.Add(r"\textbf{Dark SUSY}", coords=[0.1,0.4])
    hist.extra_text.Add(r"$m_{N1} = %s~\mathrm{GeV}$"%n1, coords=[0.1,0.35])
    hist.extra_text.Add(r"$m_{\gamma D} = %s~\mathrm{GeV}$"%(mass_strings[ma]), coords=[0.1,0.3])
    hist.extra_text.Add(r"$c_{\tau} = %s~\mathrm{mm}$"%cT_strings2[ctau], coords=[0.1,0.25])
    plot = hist.execute()
    hist.savefig()



MyFile = TFile("HLT_efficiency_trigger_2016_DarkSUSY_13TeV.root")
MyFile.cd()
dirList = gDirectory.GetListOfKeys()

## open the file with locations to MC files
mcSamples = readTextFileWithSamples("../DarkSUSY_All_2016.txt")

eff_hlt_RECO_leading_pt = {}
eff_hlt_RECO_leading_eta = {}
eff_hlt_RECO_leading_phi = {}

eff_hlt_RECO_leading_pt_full = {}
eff_hlt_RECO_leading_eta_full = {}
eff_hlt_RECO_leading_phi_full = {}


for sample in mcSamples:

    n1, ma, ctau = decodeDarkSUSYFileNameMany(sample)
    darkSUSY = getDarkSUSYFileName(n1,ma,ctau)
    print "Checking", "mN1", n1, "mA", ma, "cT", ctau
    
    ## make trigger efficiencies for each trigger path
    for trigger in triggerPaths:
        print trigger
        print darkSUSY + "_eff_hlt_RECO_leading_pt_fid_" + trigger

        for k1 in dirList: 
            h1 = k1.ReadObj()
            print h1.GetName()

            eff_hlt_RECO_leading_pt[darkSUSY + "_" + trigger] = MyFile.Get(darkSUSY + "_eff_hlt_RECO_leading_pt_" + trigger)
            eff_hlt_RECO_leading_eta[darkSUSY + "_" + trigger] = MyFile.Get(darkSUSY + "_eff_hlt_RECO_leading_eta_" + trigger)
            eff_hlt_RECO_leading_phi[darkSUSY + "_" + trigger] = MyFile.Get(darkSUSY + "_eff_hlt_RECO_leading_phi_" + trigger)
            
            eff_pt = (eff_hlt_RECO_leading_pt[darkSUSY + "_" + trigger], r"Leading muon $p_\mathrm{T}$ [GeV]", "pt")
            eff_eta = (eff_hlt_RECO_leading_eta[darkSUSY + "_" + trigger], r"Leading muon $\eta$", "eta")
            eff_phi = (eff_hlt_RECO_leading_phi[darkSUSY + "_" + trigger], r"Leading muon $\phi$", "phi")

            eff_hlt_RECO_list = [eff_pt, eff_eta, eff_phi]
            
            makePlot(eff_pt, trigger, format='png')
            makePlot(eff_eta, trigger, format='png')
            makePlot(eff_phi, trigger, format='png')
            
            makePlot(eff_pt, trigger, format='pdf')
            makePlot(eff_eta, trigger, format='pdf')
            makePlot(eff_phi, trigger, format='pdf')

    
            eff_hlt_RECO_leading_pt_full[darkSUSY + "_" + trigger] = MyFile.Get(darkSUSY + "_eff_hlt_RECO_leading_pt_full_" + trigger)
            eff_hlt_RECO_leading_eta_full[darkSUSY + "_" + trigger] = MyFile.Get(darkSUSY + "_eff_hlt_RECO_leading_eta_full_" + trigger)
            eff_hlt_RECO_leading_phi_full[darkSUSY + "_" + trigger] = MyFile.Get(darkSUSY + "_eff_hlt_RECO_leading_phi_full_" + trigger)
    
            eff_pt = (eff_hlt_RECO_leading_pt_full[darkSUSY + "_" + trigger], r"Leading muon $p_\mathrm{T}$ [GeV]", "pt")
            eff_eta = (eff_hlt_RECO_leading_eta_full[darkSUSY + "_" + trigger], r"Leading muon $\eta$", "eta")
            eff_phi = (eff_hlt_RECO_leading_phi_full[darkSUSY + "_" + trigger], r"Leading muon $\phi$", "phi")

            eff_hlt_RECO_list = [eff_pt, eff_eta, eff_phi]

            makePlot(eff_pt, trigger, format='png')
            makePlot(eff_eta, trigger, format='png')
            makePlot(eff_phi, trigger, format='png')

            makePlot(eff_pt, trigger, format='pdf')
            makePlot(eff_eta, trigger, format='pdf')
            makePlot(eff_phi, trigger, format='pdf')
    
        
MyFile.Close()
