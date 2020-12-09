import sys
from ROOT import *
from argparse import ArgumentParser

from hepPlotter import HepPlotter
from hepPlotterDataMC import HepPlotterDataMC
import hepPlotterTools as hpt
#import hepPlotterLabels as hpl
import math as m
import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from Helpers import *

## mass of the muon in GeV
mmu = 105.6583745 * 0.001
mZ = 91.1876
verbose = False

## define each chain for plotting purposes
file_WZ = TFile("datafiles/out_ana_clone_WZTo3LNu1_skim3mu.root")
chain_WZ = file_WZ.Get("Events")

file_Data = TFile("datafiles/out_ana_clone_MET_2018.root")
chain_Data = file_Data.Get("Events")

lumi = 59.7
WZ_xsec = 5114#fb
WZ_events = 10749269.
def WZScaled(events):
    return events / WZ_events * lumi * WZ_xsec

def scaleWZ(hist):
    hist.Scale(lumi*WZ_xsec/WZ_events)

## make the selection
nMuonCut = "nRecoMu == 3"
ptMuonCut= "selMu0_pT > 20 && selMu1_pT > 20 && selMu2_pT > 10"
muonTightCut = "selMu0_isTight==1 && selMu1_isTight==1 && selMu2_isTight==1"
muonMediumCut = "selMu0_isMedium==1 && selMu1_isMedium==1 && selMu2_isMedium==1"
muonDxyCut = "selMu0_dxy < 0.01 && selMu1_dxy < 0.01 && selMu2_dxy < 0.01"
muonDzCut = "selMu0_dz < 0.1 && selMu1_dz < 0.1 && selMu2_dz < 0.1"
muonIsoCut = "selMu0_PFIso < 0.2 && selMu1_PFIso < 0.2 && selMu2_PFIso < 0.2"
OK_MET  = "isOrthogonalHLTFired==1"
SS = 'selMu0_charge == selMu1_charge && selMu1_charge == selMu2_charge'
OS = '!(%s)'%SS
bjetCut = "nBJet_20==0"
dimuonMassCut = "abs(best_OS_dimuon_mass-91.2)<15"
ok_hlt = "(isSignalHLT_0_Fired==1 || isSignalHLT_1_Fired==1 || isSignalHLT_2_Fired==1 || isSignalHLT_3_Fired==1)"
pfmet = "pfMET > 100"

cuts = [0] * 11
cuts[0] = "1==1"
cuts[1] = cuts[0] + "&&" + ptMuonCut
cuts[2] = cuts[1] + "&&" + muonMediumCut
cuts[3] = cuts[2]
cuts[4] = cuts[3] + "&&" + muonDxyCut
cuts[5] = cuts[4] + "&&" + muonDzCut
cuts[6] = cuts[5] + "&&" + muonIsoCut
cuts[7] = cuts[6]
cuts[8] = cuts[7] + "&&" + OS
cuts[9] = cuts[8] + "&&" + OK_MET
cuts[10] = cuts[9] + "&&" + ok_hlt

print "No cut"
print WZScaled(chain_WZ.GetEntries()), chain_Data.GetEntries()

for i in range(0,11):
    print cuts[i]
    print WZScaled(chain_WZ.GetEntries(cuts[i])), chain_Data.GetEntries(cuts[i])
    print


dimuonMassCut = "abs(best_OS_dimuon_mass-91.2)<15"

my_cut = (TCut(nMuonCut) +
          TCut(ptMuonCut) +
          TCut(muonMediumCut) +
          #          TCut(muonDxyCut) +
          #          TCut(muonDzCut) +
          #          TCut(muonIsoCut) +
          TCut(OS) +
          TCut(dimuonMassCut)
#          TCut(OK_MET)
          #          TCut(bjetCut)
      )

my_cut_dimuon = my_cut

my_cut_HLT = my_cut + TCut(ok_hlt)


out_dmc_directory = "data_vs_montecarlo_plots/"
out_directory = "trigger_efficiency_plots/"


variables = {}
variables["selMu0_charge"] = (3,-1,1)
variables["selMu1_charge"] = (3,-1,1)
variables["selMu2_charge"] = (3,-1,1)

variables["selMu0_pT"] = (30,0,300)
variables["selMu1_pT"] = (30,0,300)
variables["selMu2_pT"] = (30,0,300)

variables["selMu0_phi"] = (16,-3.2,3.2)
variables["selMu1_phi"] = (16,-3.2,3.2)
variables["selMu2_phi"] = (16,-3.2,3.2)

variables["selMu0_eta"] = (25,-2.5,2.5)
variables["selMu1_eta"] = (25,-2.5,2.5)
variables["selMu2_eta"] = (25,-2.5,2.5)
"""
variables["selMu0_isMedium"] = (2,0,1)
variables["selMu1_isMedium"] = (2,0,1)
variables["selMu2_isMedium"] = (2,0,1)

variables["selMu0_isTight"] = (2,0,1)
variables["selMu1_isTight"] = (2,0,1)
variables["selMu2_isTight"] = (2,0,1)

variables["selMu0_dxy"] = (100,-10,10)
variables["selMu1_dxy"] = (100,-10,10)
variables["selMu2_dxy"] = (100,-10,10)

variables["selMu0_dz"] = (160,-32,32)
variables["selMu1_dz"] = (160,-32,32)
variables["selMu2_dz"] = (160,-32,32)

variables["selMu0_PFIso"] = (100,0,100)
variables["selMu1_PFIso"] = (100,0,100)
variables["selMu2_PFIso"] = (100,0,100)
"""
variables["pfMET"] = (75,0,750)
variables["pfMET_phi"] = (16,-3.2,3.2)
variables["nBJet_20"] = (5,0,4)
variables["best_OS_dimuon_mass"] = (40,70,110)
variables["best_SS_dimuon_mass"] = (40,70,110)
variables["m123"] = (50,0,500)



x_axis_labels = {}
x_axis_labels["selMu0_charge"] = r"Leading muon charge"
x_axis_labels["selMu1_charge"] = r"Second leading muon charge"
x_axis_labels["selMu2_charge"] = r"Third leading muon charge"

x_axis_labels["selMu0_pT"] = r"Leading muon $p_\mathrm{T}$ [GeV]"
x_axis_labels["selMu1_pT"] = r"Second leading muon $p_\mathrm{T}$ [GeV]"
x_axis_labels["selMu2_pT"] = r"Third leading muon $p_\mathrm{T}$ [GeV]"

x_axis_labels["selMu0_phi"] = r"Leading muon $\phi$"
x_axis_labels["selMu1_phi"] = r"Second leading muon $\phi$"
x_axis_labels["selMu2_phi"] = r"Third leading muon $\phi$"

x_axis_labels["selMu0_eta"] = r"Leading muon $\eta$"
x_axis_labels["selMu1_eta"] = r"Second leading muon $\eta$"
x_axis_labels["selMu2_eta"] = r"Third leading muon $\eta$"

x_axis_labels["pfMET"] = r"MET [GeV]"
x_axis_labels["pfMET_phi"] = r"MET $\phi$"
x_axis_labels["nBJet_20"] = r"Number of $b$ jets with $p_\mathrm{T} > 20$ GeV"
x_axis_labels["best_OS_dimuon_mass"] = "Best OS dimuon mass [GeV]"
x_axis_labels["best_SS_dimuon_mass"] = "Best SS dimuon mass [GeV]"
x_axis_labels["m123"] = r"$m_{123}$ [GeV]"

def makePlotDataVsMC(histogram1,
                     histogram2,
                     x_label,
                     y_label,
                     saveAs,
                     cformat = '.pdf'):

    c = TCanvas("c","",800,600)
    c.cd()
    histogram2.SetTitle('CMS Simulation       2018 MET, 59.7')
    histogram2.SetFillColor(kBlue)
    histogram2.GetYaxis().SetTitle(x_label)
    histogram2.GetYaxis().SetTitle(y_label)
    histogram2.Draw()
    histogram1.SetLineColor(kBlack)
    histogram1.SetMarkerColor(kBlack)
    histogram1.Draw("same")
    c.SaveAs(out_dmc_directory + "/" + saveAs + cformat)


## for each kinematic property, plot all contributions
for myvar in variables:

    bins = "(" + str(variables[myvar][0]) + "," + str(variables[myvar][1]) + "," + str(variables[myvar][2]) + ")"

    chain_WZ.Draw("(" + myvar + ")" + ">>h_WZ_" + myvar + bins, my_cut)
    chain_Data.Draw(myvar + ">>h_Data_" + myvar + bins, my_cut)

    h_WZ = TH1F(gDirectory.Get("h_WZ_" + myvar).Clone("h_WZ_" + myvar))
    h_Data = TH1F(gDirectory.Get("h_Data_" + myvar).Clone("h_Data_" + myvar))
    scaleWZ(h_WZ)

    makePlotDataVsMC(h_WZ, h_Data, x_axis_labels[myvar], "Entries", "Combine_" + myvar)
