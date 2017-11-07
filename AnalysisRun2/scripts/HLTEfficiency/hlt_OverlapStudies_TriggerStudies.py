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

myfile = TFile.Open("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_X_cT_Y_13TeV_PATANA_Total/" + "DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_0_13TeV_pythia8_PATANA_total.root")

myfile.cd()
tree = myfile.Get("Events")
    
entries = tree.GetEntries()
verbose = True
if (verbose): print "  Events  ", entries

M_PI = 3.14159265359

def deltaPhi(phi1, phi2):
    result = phi1 - phi2;
    if (result > M_PI): 
        result -= 2*M_PI;
    if (result <= -M_PI):
        result += 2*M_PI;
    return result;

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

    mu0_phi = tree.selMu0_phi
    mu1_phi = tree.selMu1_phi
    mu2_phi = tree.selMu2_phi
    mu3_phi = tree.selMu3_phi

    delta_phi01 = deltaPhi(mu0_phi, mu1_phi)
    delta_phi23 = deltaPhi(mu2_phi, mu3_phi)

    delta_phi02 = deltaPhi(mu0_phi, mu2_phi)
    delta_phi13 = deltaPhi(mu1_phi, mu3_phi)

    delta_phi03 = deltaPhi(mu0_phi, mu3_phi)
    delta_phi12 = deltaPhi(mu1_phi, mu2_phi)

    grouping = -1
    if delta_phi01 < 0.1 and delta_phi23 < 0.1

    #print nMu, tree.selMu0_pT, tree.selMu1_pT, tree.selMu2_pT, tree.selMu3_pT
    
    ## require 4mu selection!!!
    if (nMuPt8>=4 and nMuPt17>=1):


        print delta_phi01, delta_phi23
        print delta_phi02, delta_phi13
        print delta_phi03, delta_phi12

        if (verbose): print "Pass denom"
        #RECO_leading_pt.Fill(tree.selMu0_pT)
        #RECO_leading_eta.Fill(tree.selMu0_eta)
        #RECO_leading_phi.Fill(tree.selMu0_phi)
        
        ## check if triggerPath is in the list
        ## check each trigger
        print list(tree.hltPaths)
        continue
        for trigger in triggerPaths:

            ## print list(tree.hltPaths)
            if any(trigger in s for s in list(tree.hltPaths)):
                if (verbose): print trigger, "is available"

                ## print "\tPass num"
                #hlt_RECO_leading_pt[darkSUSY + "_" + trigger].Fill(tree.selMu0_pT)
                #hlt_RECO_leading_eta[darkSUSY + "_" + trigger].Fill(tree.selMu0_eta)
                #hlt_RECO_leading_phi[darkSUSY + "_" + trigger].Fill(tree.selMu0_phi)
