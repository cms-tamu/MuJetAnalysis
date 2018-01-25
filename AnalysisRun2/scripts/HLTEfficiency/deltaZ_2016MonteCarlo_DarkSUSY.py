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
def merge_darkSUSY_files(dirNames):

    verbose = True

    if verbose: print dirNames
    n1, ma, ctau = decodeDarkSUSYFileName(dirNames[0])

    if verbose: print "Checking", "mN1", n1, "mA", ma, "cT", ctau

    darkSUSY = getDarkSUSYFileName(n1,ma,ctau)

    chain = ROOT.TChain("cutFlowAnalyzerPXBL3PXFL2/Events")

    if verbose: print "Adding files to the chain"
    chain = addfilesMany(chain, dirNames)
    chain.Merge("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_X_cT_Y_13TeV_PATANA_Total/" + darkSUSY + "_pythia8_PATANA_total.root")


##____________________________________________________________
def deltaZ(dirNames):

    verbose = False

    if verbose: print "Preparing histograms"

    chain = ROOT.TChain("cutFlowAnalyzerPXBL3PXFL2/Events")

    deltaZ_DiMuonC_DiMuonF = ROOT.TH1D("deltaZ_DiMuonC_DiMuonF","",1000,-0.5,0.5);

    n1, ma, ctau = decodeDarkSUSYFileNameMany(dirNames)

    if verbose: print "Checking", "mN1", n1, "mA", ma, "cT", ctau

    darkSUSY = getDarkSUSYFileName(n1,ma,ctau)

    addfilesMany(chain, dirNames, "out_ana")

    chain.Draw("diMuons_dz_FittedVtx>>deltaZ_DiMuonC_DiMuonF","is4SelMu8 && isVertexOK && is2MuJets && is2DiMuons && (diMuonF_m1_FittedVtx_hitpix_l3inc==1 || diMuonF_m2_FittedVtx_hitpix_l3inc==1) && (diMuonC_m1_FittedVtx_hitpix_l3inc==1 || diMuonC_m2_FittedVtx_hitpix_l3inc==1)")

    ## save per mass point and per ctau point!!
    MyFile = TFile("deltaZ_DiMuonC_DiMuonF_2016.root","UPDATE");
    deltaZ_DiMuonC_DiMuonF.Write(darkSUSY + "_deltaZ_DiMuonC_DiMuonF")
    MyFile.Close();
    del deltaZ_DiMuonC_DiMuonF
    
## open the file with locations to MC files
mcSamples = readTextFileWithSamples("../DarkSUSY_All_2016.txt")

def calculateDeltaZs():

    for iSample, sample in enumerate(mcSamples):

        n1, ma, ctau = decodeDarkSUSYFileNameMany(sample)
        darkSUSY = getDarkSUSYFileName(n1,ma,ctau)
            
        if ma == '8p5' or True:
        
            print "Processing", iSample, "mN1", n1, "mA", ma, "cT", ctau
            deltaZ(sample)

calculateDeltaZs()
