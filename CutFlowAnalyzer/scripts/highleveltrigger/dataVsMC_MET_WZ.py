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

gStyle.SetOptStat(0)

## mass of the muon in GeV
mmu = 105.6583745 * 0.001
mZ = 91.1876
verbose = False

## TTW
##4911941

## define each chain for plotting purposes
file_WZ = TFile("datafiles_SingleMu/out_ana_WZTo3LNu2_SingleMu.root")
chain_WZ = file_WZ.Get("cutFlowAnalyzerPXBL4PXFL3/Events")

file_tZ = TFile("datafiles_SingleMu/out_ana_tZq_ll.root")
if not file_tZ:
    print "No file_tZ"
chain_tZ = file_tZ.Get("cutFlowAnalyzerPXBL4PXFL3/Events")

file_ZZ = TFile("datafiles_SingleMu/out_ana_ZZTo4L.root")
if not file_ZZ:
    print "No file_ZZ"
chain_ZZ = file_ZZ.Get("cutFlowAnalyzerPXBL4PXFL3/Events")

file_Data = TFile("datafiles_SingleMu/out_ana_SingleMuon2018.total.root")
chain_Data = file_Data.Get("cutFlowAnalyzerPXBL4PXFL3/Events")

lumi = 59.7

WZ_xsec = 5114.
WZ_events = 10749269.

tZ_xsec = 0.07358
tZ_events = 5988000.

ZZ_xsec = 1325.
ZZ_events = 19089600.

def WZScaled(events):
    return events / WZ_events * lumi * WZ_xsec

def scaleWZ(hist):
    scaleFactor = lumi * WZ_xsec / WZ_events
    hist.Scale(lumi * WZ_xsec / WZ_events)
    return hist

def ZZScaled(events):
    return events / ZZ_events * lumi * ZZ_xsec

def scaleZZ(hist):
    scaleFactor = lumi * ZZ_xsec / ZZ_events
    hist.Scale(lumi * ZZ_xsec / ZZ_events)
    return hist

def tZScaled(events):
    return events / tZ_events * lumi * tZ_xsec

def scaletZ(hist):
    scaleFactor = lumi * tZ_xsec / tZ_events
    hist.Scale(lumi * tZ_xsec / tZ_events)
    return hist

## make the selection
nMuonCut = "nRecoMu == 3"
ptMuonCut= "selMu0_pT > 20 && selMu1_pT > 20 && selMu2_pT > 10 && abs(selMu0_eta) < 2.4 && abs(selMu1_eta) < 2.4 && abs(selMu2_eta) < 2.4"
muonTightCut = "selMu0_isTight==1 && selMu1_isTight==1 && selMu2_isTight==1"
muonMediumCut = "selMu0_isMedium==1 && selMu1_isMedium==1 && selMu2_isMedium==1"
muonDxyCut = "abs(selMu0_dxy) < 0.005 && abs(selMu1_dxy) < 0.005 && abs(selMu2_dxy) < 0.005"
muonDzCut = "abs(selMu0_dz) < 0.01 && abs(selMu1_dz) < 0.01 && abs(selMu2_dz) < 0.01"
muonIsoCut = "selMu0_PFIso < 0.1 && selMu1_PFIso < 0.1 && selMu2_PFIso < 0.1"
OK_control  = "isOrthogonalHLTFired==1"
SS = 'selMu0_charge == selMu1_charge && selMu1_charge == selMu2_charge'
OS = '!(%s)'%SS
bjetCut = "nBJet_20==0"
dimuonMassCut = "abs(mMuMu_OS-91.2)<10"
ok_hlt = "(isSignalHLT_0_Fired==1 || isSignalHLT_1_Fired==1 || isSignalHLT_2_Fired==1 || isSignalHLT_3_Fired==1)"
pfmet = "pfMET > 100"

cuts = [0] * 11
cuts[0] = OK_control
cuts[1] = cuts[0] + "&&" + nMuonCut
cuts[2] = cuts[1] + "&&" + ptMuonCut
cuts[3] = cuts[2] + "&&" + muonMediumCut
cuts[4] = cuts[3] + "&&" + muonDxyCut
cuts[5] = cuts[4] + "&&" + muonDzCut
cuts[6] = cuts[5] + "&&" + muonIsoCut
cuts[7] = cuts[6] + "&&" + OS
cuts[8] = cuts[7] + "&&" + dimuonMassCut
cuts[9] = cuts[8] + "&&" + ok_hlt

print "No cut"
print WZScaled(chain_WZ.GetEntries()), ZZScaled(chain_ZZ.GetEntries()), tZScaled(chain_tZ.GetEntries()), chain_Data.GetEntries()

for i in range(0,10):
    print cuts[i]
    print WZScaled(chain_WZ.GetEntries(cuts[i])), ZZScaled(chain_ZZ.GetEntries(cuts[i])), tZScaled(chain_tZ.GetEntries(cuts[i])), chain_Data.GetEntries(cuts[i])
    print

#exit(1)

my_cut = (
    TCut(OK_control) +
    TCut(nMuonCut) +
    TCut(ptMuonCut) +
    TCut(muonMediumCut) +
    TCut(muonDxyCut) +
    TCut(muonDzCut) +
    TCut(muonIsoCut) +
    TCut(OS) +
    TCut(dimuonMassCut) +
    TCut(ok_hlt)
    #TCut(bjetCut)
)

my_cut_dimuon = my_cut

my_cut_HLT = my_cut + TCut(ok_hlt)

out_dmc_directory = "data_vs_montecarlo_plots_singlemu/"
out_directory = "trigger_efficiency_plots/"

variables = {}
variables["selMu0_charge"] = (3,-1,2)
variables["selMu1_charge"] = (3,-1,2)
variables["selMu2_charge"] = (3,-1,2)

variables["selMu0_pT"] = (30,0,300)
variables["selMu1_pT"] = (30,0,300)
variables["selMu2_pT"] = (30,0,300)

variables["selMu0_phi"] = (16,-3.2,3.2)
variables["selMu1_phi"] = (16,-3.2,3.2)
variables["selMu2_phi"] = (16,-3.2,3.2)

variables["selMu0_eta"] = (25,-2.5,2.5)
variables["selMu1_eta"] = (25,-2.5,2.5)
variables["selMu2_eta"] = (25,-2.5,2.5)

variables["selMu0_isMedium"] = (2,0,2)
variables["selMu1_isMedium"] = (2,0,2)
variables["selMu2_isMedium"] = (2,0,2)

variables["selMu0_isTight"] = (2,0,2)
variables["selMu1_isTight"] = (2,0,2)
variables["selMu2_isTight"] = (2,0,2)

variables["selMu0_dxy"] = (100,-0.02,0.02)
variables["selMu1_dxy"] = (100,-0.02,0.02)
variables["selMu2_dxy"] = (100,-0.02,0.02)

variables["selMu0_dz"] = (160,-0.02,0.02)
variables["selMu1_dz"] = (160,-0.02,0.02)
variables["selMu2_dz"] = (160,-0.02,0.02)

variables["selMu0_PFIso"] = (100,0,1)
variables["selMu1_PFIso"] = (100,0,1)
variables["selMu2_PFIso"] = (100,0,1)

variables["pfMET"] = (75,0,750)
variables["pfMET_phi"] = (16,-3.2,3.2)
variables["nBJet_20"] = (5,0,4)
variables["mMuMu_OS"] = (40,70,110)
variables["mMuMu_SS"] = (40,70,110)



x_axis_labels = {}

x_axis_labels["selMu0_charge"] = "Leading muon charge"
x_axis_labels["selMu1_charge"] = "Second leading muon charge"
x_axis_labels["selMu2_charge"] = "Third leading muon charge"

x_axis_labels["selMu0_pT"] = "Leading muon pT [GeV]"
x_axis_labels["selMu1_pT"] = "Second leading muon pT [GeV]"
x_axis_labels["selMu2_pT"] = "Third leading muon pT [GeV]"

x_axis_labels["selMu0_phi"] = "Leading muon #phi"
x_axis_labels["selMu1_phi"] = "Second leading muon #phi"
x_axis_labels["selMu2_phi"] = "Third leading muon #phi"

x_axis_labels["selMu0_eta"] = "Leading muon #eta"
x_axis_labels["selMu1_eta"] = "Second leading muon #eta"
x_axis_labels["selMu2_eta"] = "Third leading muon #eta"

x_axis_labels["pfMET"] = "MET [GeV]"
x_axis_labels["pfMET_phi"] = "MET #phi"
x_axis_labels["nBJet_20"] = "Number of b jets with pT > 20 GeV"
x_axis_labels["mMuMu_OS"] = "Best OS dimuon mass [GeV]"
x_axis_labels["mMuMu_SS"] = "Best SS dimuon mass [GeV]"

x_axis_labels["selMu0_isMedium"] = "Medium ID"
x_axis_labels["selMu1_isMedium"] = "Medium ID"
x_axis_labels["selMu2_isMedium"] = "Medium ID"

x_axis_labels["selMu0_isTight"] = "Tight ID"
x_axis_labels["selMu1_isTight"] = "Tight ID"
x_axis_labels["selMu2_isTight"] = "Tight ID"

x_axis_labels["selMu0_dxy"] = "dxy"
x_axis_labels["selMu1_dxy"] = "dxy"
x_axis_labels["selMu2_dxy"] = "dxy"

x_axis_labels["selMu0_dz"] = "dz"
x_axis_labels["selMu1_dz"] = "dz"
x_axis_labels["selMu2_dz"] = "dz"

x_axis_labels["selMu0_PFIso"] = "PF RelIso"
x_axis_labels["selMu1_PFIso"] = "PF RelIso"
x_axis_labels["selMu2_PFIso"] = "PF RelIso"


def makePlotDataVsMC(mc1,
                     mc2,
                     mc3,
                     data,
                     x_label,
                     y_label,
                     myvar,
                     cformat = '.pdf'):

    c = TCanvas("c_" + myvar, "",800,600)
    c.cd()
    mc1.SetTitle('CMS Preliminary       59.7 fb^{-1} (13 TeV)')
    mc1.SetMinimum(0)
    data.SetMinimum(0)
    mc1.SetMaximum(max(mc1.GetMaximum(), data.GetMaximum()) * 1.2)
    mc1.SetLineColor(kAzure-4)
    mc1.SetFillColor(kAzure-4)

    mc1.GetXaxis().SetTitle(x_label)
    mc1.GetYaxis().SetTitle(y_label)
    mc1.Draw("hist")

    data.SetMarkerColor(kBlack)
    data.SetMarkerStyle(8)
    data.SetMarkerSize(1)
    data.Draw("psame")

    saveAs = "Combine_" + myvar
    c.SaveAs(out_dmc_directory + "/" + saveAs + cformat)
    del c

## for each kinematic property, plot all contributions
for myvar in variables:

    bins = "(" + str(variables[myvar][0]) + "," + str(variables[myvar][1]) + "," + str(variables[myvar][2]) + ")"

    weight = "* (sign(genWeight) * pileupWeight)"
    chain_WZ.Draw(myvar + ">>h_WZ_" + myvar + bins, my_cut.GetTitle() + weight)
    chain_tZ.Draw(myvar + ">>h_tZ_" + myvar + bins, my_cut.GetTitle() + weight)
    chain_ZZ.Draw(myvar + ">>h_ZZ_" + myvar + bins, my_cut.GetTitle() + weight)
    chain_Data.Draw(myvar + ">>h_Data_" + myvar + bins, my_cut)

    h_WZ = TH1F(gDirectory.Get("h_WZ_" + myvar).Clone("h_WZ_" + myvar))
    h_tZ = TH1F(gDirectory.Get("h_tZ_" + myvar).Clone("h_tZ_" + myvar))
    h_ZZ = TH1F(gDirectory.Get("h_ZZ_" + myvar).Clone("h_ZZ_" + myvar))
    h_Data = TH1F(gDirectory.Get("h_Data_" + myvar).Clone("h_Data_" + myvar))

    h_WZ.Sumw2()
    h_tZ.Sumw2()
    h_ZZ.Sumw2()
    h_Data.Sumw2()

    h_WZ = scaleWZ(h_WZ)
    h_tZ = scaletZ(h_tZ)
    h_ZZ = scaleZZ(h_ZZ)

    makePlotDataVsMC(h_WZ, h_tZ, h_ZZ, h_Data, x_axis_labels[myvar], "Entries", myvar)
