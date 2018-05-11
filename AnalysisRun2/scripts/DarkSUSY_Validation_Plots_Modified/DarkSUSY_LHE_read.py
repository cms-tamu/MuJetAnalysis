import ROOT, array, os, re, math, random, string
from math import *
from operator import itemgetter
import sys 
sys.argv.append( '-b-' )
ROOT.gROOT.SetBatch(True)

muonID = 13
higgsID = 25
n1ID = 3000002 
nDID = 3000001 
nExit = 80002
#nExit = 1000
gammaDID = 3000022

hMass = "125"
n1Mass = "10"
nDMass = "1"

filename = "DarkSUSY_mH_125_mGammaD_0400_13TeV_cT_100_madgraph452_bridge224_events80k.lhe"
f = open(filename, 'r')

if len(filename) == 77:
	mass_GammaD = filename[24:-49]
	lifetime_GammaD = filename[38:-36]
	energy = filename[29:-46]
	mass_Higgs = filename[12:-62]
	lifetime_GammaD_Legend = filename[38:-38] + "." + filename[39:-36]
	mass_GammaD_Legend = filename [24:-52] + "." + filename[25:-49]
	
	if mass_GammaD_Legend[4] == "0": mass_GammaD_Legend = mass_GammaD_Legend[:-1]
	if mass_GammaD_Legend[3] == "0": mass_GammaD_Legend = mass_GammaD_Legend[:-1]
	if mass_GammaD_Legend[2] == "0": mass_GammaD_Legend = mass_GammaD_Legend[:-1]
	if mass_GammaD_Legend[1] == "." and len(mass_GammaD_Legend) == 2: mass_GammaD_Legend = mass_GammaD_Legend + "0"
	
	switch = 0
	if lifetime_GammaD_Legend[3] == "0": 
		lifetime_GammaD_Legend = lifetime_GammaD_Legend[:-1]
		switch = 1
	if lifetime_GammaD_Legend[2] == "0" and switch == 1: lifetime_GammaD_Legend = lifetime_GammaD_Legend[:-1]

else: 
	mass_GammaD = filename[24:-42]
	energy = filename[29:-39]
	mass_Higgs = filename[12:-55]       
	mass_GammaD_Legend = filename[24:-45] + "." + filename[25:-42]
	lifetime_GammaD = "000"
        lifetime_GammaD_Legend = "0.00"

print mass_GammaD
print lifetime_GammaD
print lifetime_GammaD_Legend
print mass_GammaD_Legend

BAM = ROOT.TFile("ValidationPlots_mGammaD_" + mass_GammaD + "_" + energy  + "_TeV_cT_" + lifetime_GammaD  + ".root"  , "RECREATE")

execfile("tdrStyle.py")
cnv = ROOT.TCanvas("cnv", "cnv")

txtHeader = ROOT.TLegend(.17,.935,0.97,1.)
txtHeader.SetFillColor(ROOT.kWhite)
txtHeader.SetFillStyle(0)
txtHeader.SetBorderSize(0)
txtHeader.SetTextFont(42)
txtHeader.SetTextSize(0.045)
txtHeader.SetTextAlign(22)
#txtHeader.SetHeader("CMS Simulation")
txtHeader.SetHeader("CMS Simulation (LHE) " + energy + " TeV")
#txtHeader.SetHeader("CMS Prelim. 2011   #sqrt{s} = 7 TeV   L_{int} = 5.3 fb^{-1}")
#txtHeader.SetHeader("CMS 2011   #sqrt{s} = 7 TeV   L_{int} = 5.3 fb^{-1}")
#txtHeader.SetHeader("CMS Prelim. 2012   #sqrt{s} = 8 TeV   L_{int} = 20.65 fb^{-1}")
#txtHeader.SetHeader("CMS 2012   #sqrt{s} = 8 TeV   L_{int} = 20.65 fb^{-1}")
txtHeader.Draw()

#info = ROOT.TLegend(0.33,0.8222222,0.9577778,0.9122222)
info = ROOT.TLegend(0.4566667,0.82,0.7822222,0.9066667)
info.SetFillColor(ROOT.kWhite)
info.SetFillStyle(0)
info.SetBorderSize(0)
info.SetTextFont(42)
info.SetTextSize(0.02777778)
info.SetMargin(0.13)
info.SetHeader("#splitline{pp #rightarrow h #rightarrow 2n_{1} #rightarrow 2n_{D} + 2 #gamma_{D} #rightarrow 2n_{D} + 4#mu}{#splitline{m_{h} = " + mass_Higgs +  " GeV, m_{n_{1}} = 10 GeV, m_{n_{D}} = 1 GeV}{m_{#gamma_{D}} = " + mass_GammaD_Legend + " GeV, c#tau_{#gamma_{D}} = " + lifetime_GammaD_Legend + " mm}}" )
#info.SetHeader("#splitline{pp #rightarrow h #rightarrow 2n_{1} #rightarrow 2n_{D} + 2 #gamma_{D} #rightarrow 2n_{D} + 4#mu}{#splitline{#gamma_{D} c#tau = "+lifetime_GammaD_Legend + "mm, Mass = " + mass_GammaD_Legend + "GeV}{M of h = " + hMass + "GeV, M of n_{1} = " + n1Mass + "GeV, M of n_{D} = " + nDMass + "GeV}}" )
txtHeader2 = ROOT.TLegend(0.01333333,0.9311111,0.8133333,0.9955556)
txtHeader2.SetFillColor(ROOT.kWhite)
txtHeader2.SetFillStyle(0)
txtHeader2.SetBorderSize(0)
txtHeader2.SetTextFont(42)
txtHeader2.SetTextSize(0.045)
txtHeader2.SetTextAlign(22)
txtHeader2.SetHeader("CMS Simulation #sqrt{s} = " + energy + " TeV")


################################################################################
#                                   pT of muons                                 
################################################################################

Etmiss_dummy = ROOT.TH1F("Etmiss_dummy","Etmiss_dummy", 100, 0, 100)
Etmiss_dummy.SetTitleOffset(1.5, "Y")
Etmiss_dummy.SetTitleOffset(1.4, "X")
Etmiss_dummy.SetTitleSize(0.04,"X")
Etmiss_dummy.SetXTitle("MET = #sum_{n_{D}}#vec{p_{T}} [GeV]")
Etmiss_dummy.SetYTitle("Fraction of events / 1 GeV")
Etmiss_dummy.SetMaximum( 0.1 )

Etmiss = ROOT.TH1F("Etmiss","Etmiss", 100, 0, 100)
Etmiss.SetLineColor(ROOT.kBlue)
Etmiss.SetLineWidth(2)
Etmiss.SetLineStyle(1)


nBins  = 125
binMin = 0.0
binMax = 125.0
yMax = 0.25
cTlow = 0

if float(lifetime_GammaD_Legend) != 0:
	cTlim = float(lifetime_GammaD_Legend)*5
	binwidth = float(lifetime_GammaD_Legend)
	numBins = int(cTlim/binwidth)
	binwidthRound = round(binwidth,3)
else:
	cTlim = 10
	binwidth = 1
	numBins = int(cTlim/binwidth)	
	binwidthRound = "1"

formula = "exp(-x/"+ lifetime_GammaD_Legend +")/("+ lifetime_GammaD_Legend + "*(1 - exp(-" + str(cTlim) + "/" + lifetime_GammaD_Legend + ")))"
print formula


cTlim = 100

h_gammaD_cT_dummy = ROOT.TH1F("h_gammaD_cT_dummy", "h_gammaD_cT_dummy", numBins, 0, cTlim)
#h_gammaD_cT_dummy.SetYTitle("Fraction of events")
h_gammaD_cT_dummy.SetTitleOffset(1.3, "Y")
h_gammaD_cT_dummy.SetXTitle("c#tau of #gamma_{D} [mm]")
h_gammaD_cT_dummy.SetYTitle("Normalized Fraction of Events / " + str(binwidthRound) + " mm")
h_gammaD_cT_dummy.SetTitleSize(0.05,"Y")
h_gammaD_cT_dummy.SetMaximum( 10 )

h_gammaD_cT = ROOT.TH1F("h_gammaD_cT", "h_gammaD_cT", numBins, 0, cTlim)
h_gammaD_cT.SetLineColor(ROOT.kBlue)
h_gammaD_cT.SetLineWidth(2)
h_gammaD_cT.SetLineStyle(1)

h_gammaD_cT_lab_dummy = ROOT.TH1F("h_gammaD_cT_lab_dummy", "h_gammaD_cT_lab_dummy", numBins, 0, cTlim)
#h_gammaD_cT_lab_dummy.SetYTitle("Fraction of events")
h_gammaD_cT_lab_dummy.SetTitleOffset(1.3, "Y")
h_gammaD_cT_lab_dummy.SetXTitle("L of #gamma_{D} [mm]")
h_gammaD_cT_lab_dummy.SetYTitle("Normalized Fraction of Events / " + str(binwidthRound) + " mm")
h_gammaD_cT_lab_dummy.SetTitleSize(0.05,"Y")
h_gammaD_cT_lab_dummy.SetMaximum( 10 )

h_gammaD_cT_lab = ROOT.TH1F("h_gammaD_cT_lab", "h_gammaD_cT_lab", numBins, 0, cTlim)
h_gammaD_cT_lab.SetLineColor(ROOT.kBlue)
h_gammaD_cT_lab.SetLineWidth(2)
h_gammaD_cT_lab.SetLineStyle(1)

h_gammaD_cT_XY_lab_dummy = ROOT.TH1F("h_gammaD_cT_XY_lab_dummy", "h_gammaD_cT_XY_lab_dummy", numBins, 0, cTlim)
#h_gammaD_cT_XY_lab_dummy.SetYTitle("Fraction of events")
h_gammaD_cT_XY_lab_dummy.SetTitleOffset(1.3, "Y")
h_gammaD_cT_XY_lab_dummy.SetXTitle("L_{XY} of #gamma_{D} [mm]")
h_gammaD_cT_XY_lab_dummy.SetYTitle("Normalized Fraction of Events / " + str(binwidthRound) + " mm")
h_gammaD_cT_XY_lab_dummy.SetTitleSize(0.05,"Y")
h_gammaD_cT_XY_lab_dummy.SetMaximum( 10 )

h_gammaD_cT_XY_lab = ROOT.TH1F("h_gammaD_cT_XY_lab", "h_gammaD_cT_XY_lab", numBins, 0, cTlim)
h_gammaD_cT_XY_lab.SetLineColor(ROOT.kBlue)
h_gammaD_cT_XY_lab.SetLineWidth(2)
h_gammaD_cT_XY_lab.SetLineStyle(1)

h_gammaD_cT_Z_lab_dummy = ROOT.TH1F("h_gammaD_cT_Z_lab_dummy", "h_gammaD_cT_Z_lab_dummy", numBins, 0, cTlim)
#h_gammaD_cT_Z_lab_dummy.SetYTitle("Fraction of events")
h_gammaD_cT_Z_lab_dummy.SetTitleOffset(1.3, "Y")
h_gammaD_cT_Z_lab_dummy.SetXTitle("L_{Z} of #gamma_{D} [mm]")
h_gammaD_cT_Z_lab_dummy.SetYTitle("Normalized Fraction of events / " + str(binwidthRound) + " mm")
h_gammaD_cT_Z_lab_dummy.SetTitleSize(0.05,"Y")
h_gammaD_cT_Z_lab_dummy.SetMaximum( 10 )

h_gammaD_cT_Z_lab = ROOT.TH1F("h_gammaD_cT_Z_lab", "h_gammaD_cT_Z_lab", numBins, 0, cTlim)
h_gammaD_cT_Z_lab.SetLineColor(ROOT.kBlue)
h_gammaD_cT_Z_lab.SetLineWidth(2)
h_gammaD_cT_Z_lab.SetLineStyle(1)

h_gammaD_1_cT_dummy = ROOT.TH1F("h_gammaD_1_cT_dummy", "h_gammaD_1_cT_dummy", numBins, 0, cTlim)
h_gammaD_1_cT_dummy.SetTitleOffset(1.3, "Y")
h_gammaD_1_cT_dummy.SetXTitle("c#tau of #gamma_{D} [mm]")
h_gammaD_1_cT_dummy.SetYTitle("Normalized Fraction of events / " + str(binwidthRound) + " mm")
h_gammaD_1_cT_dummy.SetTitleSize(0.05,"Y")
h_gammaD_1_cT_dummy.SetMaximum( 10 )

h_gammaD_1_cT = ROOT.TH1F("h_gammaD_1_cT", "h_gammaD_1_cT", numBins, 0, cTlim)
h_gammaD_1_cT.SetLineColor(ROOT.kBlue)
h_gammaD_1_cT.SetLineWidth(2)
h_gammaD_1_cT.SetLineStyle(1)

h_gammaD_1_cT_lab_dummy = ROOT.TH1F("h_gammaD_1_cT_lab_dummy", "h_gammaD_1_cT_lab_dummy", numBins, 0, cTlim)
h_gammaD_1_cT_lab_dummy.SetTitleOffset(1.3, "Y")
h_gammaD_1_cT_lab_dummy.SetXTitle("L of #gamma_{D} [mm]")
h_gammaD_1_cT_lab_dummy.SetYTitle("Normalized Fraction of events / " + str(binwidthRound) + " mm")
h_gammaD_1_cT_lab_dummy.SetTitleSize(0.05,"Y")
h_gammaD_1_cT_lab_dummy.SetMaximum( 10 )

h_gammaD_1_cT_lab = ROOT.TH1F("h_gammaD_1_cT_lab", "h_gammaD_1_cT_lab", numBins, 0, cTlim)
h_gammaD_1_cT_lab.SetLineColor(ROOT.kBlue)
h_gammaD_1_cT_lab.SetLineWidth(2)
h_gammaD_1_cT_lab.SetLineStyle(1)

h_gammaD_1_cT_XY_lab_dummy = ROOT.TH1F("h_gammaD_1_cT_XY_lab_dummy", "h_gammaD_1_cT_XY_lab_dummy", numBins, 0, cTlim)
h_gammaD_1_cT_XY_lab_dummy.SetTitleOffset(1.3, "Y")
h_gammaD_1_cT_XY_lab_dummy.SetXTitle("L_{XY} of #gamma_{D} [mm]")
h_gammaD_1_cT_XY_lab_dummy.SetYTitle("Normalized Fraction of events / " + str(binwidthRound) + " mm")
h_gammaD_1_cT_XY_lab_dummy.SetTitleSize(0.05,"Y")
h_gammaD_1_cT_XY_lab_dummy.SetMaximum( 10 )

h_gammaD_1_cT_XY_lab = ROOT.TH1F("h_gammaD_1_cT_XY_lab", "h_gammaD_1_cT_XY_lab", numBins, 0, cTlim)
h_gammaD_1_cT_XY_lab.SetLineColor(ROOT.kBlue)
h_gammaD_1_cT_XY_lab.SetLineWidth(2)
h_gammaD_1_cT_XY_lab.SetLineStyle(1)

h_gammaD_1_cT_Z_lab_dummy = ROOT.TH1F("h_gammaD_1_cT_Z_lab_dummy", "h_gammaD_1_cT_Z_lab_dummy", numBins, 0, cTlim)
h_gammaD_1_cT_Z_lab_dummy.SetTitleOffset(1.3, "Y")
h_gammaD_1_cT_Z_lab_dummy.SetXTitle("L_{Z} of #gamma_{D} [mm]")
h_gammaD_1_cT_Z_lab_dummy.SetYTitle("Normalized Fraction of events / " + str(binwidthRound) + " mm")
h_gammaD_1_cT_Z_lab_dummy.SetTitleSize(0.05,"Y")
h_gammaD_1_cT_Z_lab_dummy.SetMaximum( 10 )

h_gammaD_1_cT_Z_lab = ROOT.TH1F("h_gammaD_1_cT_Z_lab", "h_gammaD_1_cT_Z_lab", numBins, 0, cTlim)
h_gammaD_1_cT_Z_lab.SetLineColor(ROOT.kBlue)
h_gammaD_1_cT_Z_lab.SetLineWidth(2)
h_gammaD_1_cT_Z_lab.SetLineStyle(1)

h_gammaD_2_cT = ROOT.TH1F("h_gammaD_2_cT", "h_gammaD_2_cT", numBins, 0, cTlim)
h_gammaD_2_cT.SetLineColor(ROOT.kRed)
h_gammaD_2_cT.SetLineWidth(2)
h_gammaD_2_cT.SetLineStyle(1)

h_gammaD_2_cT_lab = ROOT.TH1F("h_gammaD_2_cT_lab", "h_gammaD_2_cT_lab", numBins, 0, cTlim)
h_gammaD_2_cT_lab.SetLineColor(ROOT.kRed)
h_gammaD_2_cT_lab.SetLineWidth(2)
h_gammaD_2_cT_lab.SetLineStyle(1)

h_gammaD_2_cT_XY_lab = ROOT.TH1F("h_gammaD_2_cT_XY_lab", "h_gammaD_2_cT_XY_lab", numBins, 0, cTlim)
h_gammaD_2_cT_XY_lab.SetLineColor(ROOT.kRed)
h_gammaD_2_cT_XY_lab.SetLineWidth(2)
h_gammaD_2_cT_XY_lab.SetLineStyle(1)

h_gammaD_2_cT_Z_lab = ROOT.TH1F("h_gammaD_2_cT_Z_lab", "h_gammaD_2_cT_Z_lab", numBins, 0, cTlim)
h_gammaD_2_cT_Z_lab.SetLineColor(ROOT.kRed)
h_gammaD_2_cT_Z_lab.SetLineWidth(2)
h_gammaD_2_cT_Z_lab.SetLineStyle(1)


h_muon_pT_dummy = ROOT.TH1F("h_muon_pT_dummy", "h_muon_pT_dummy", nBins, binMin, binMax)
h_muon_pT_dummy.SetYTitle("Fraction of events / 1 GeV")
h_muon_pT_dummy.SetTitleOffset(1.35, "Y")
h_muon_pT_dummy.SetXTitle("p_{T} of #mu [GeV]")
h_muon_pT_dummy.SetMaximum( 0.2 )

h_higgs_pT_dummy = ROOT.TH1F("h_higgs_pT_dummy", "h_higgs_pT_dummy", 10, 0, 10)
h_higgs_pT_dummy.SetYTitle("Fraction of events / 1 GeV")
h_higgs_pT_dummy.SetTitleOffset(1.35, "Y")
h_higgs_pT_dummy.SetXTitle("p_{T} of h [GeV]")
h_higgs_pT_dummy.SetMaximum( 1.1 )

h_muon_pZ_dummy = ROOT.TH1F("h_muon_pZ_dummy", "h_muon_pZ_dummy", nBins, binMin, binMax)
h_muon_pZ_dummy.SetYTitle("Fraction of events / 1 GeV")
h_muon_pZ_dummy.SetTitleOffset(1.35, "Y")
h_muon_pZ_dummy.SetXTitle("|p_{Z}| of #mu [GeV]")
h_muon_pZ_dummy.SetMaximum( yMax )

h_higgs_pZ_dummy = ROOT.TH1F("h_higgs_pZ_dummy", "h_higgs_pZ_dummy", 50, 0, 500)
h_higgs_pZ_dummy.SetYTitle("Fraction of events / 1 GeV")
h_higgs_pZ_dummy.SetTitleOffset(1.35, "Y")
h_higgs_pZ_dummy.SetXTitle("|p_{Z}| of h [GeV]")
h_higgs_pZ_dummy.SetMaximum( 0.1 )

h_muon_Eta_dummy = ROOT.TH1F("h_muon_Eta_dummy", "h_muon_Eta_dummy", 100, -5, 5)
h_muon_Eta_dummy.SetYTitle("Fraction of events / 0.1")
h_muon_Eta_dummy.SetTitleOffset(1.35, "Y")
h_muon_Eta_dummy.SetXTitle("#eta of #mu")
h_muon_Eta_dummy.SetMaximum( 0.1 )

#h_higgs_Eta_dummy = ROOT.TH1F("h_higgs_Eta_dummy", "h_higgs_Eta_dummy", 100,-5,5)
#h_higgs_Eta_dummy.SetYTitle("Fraction of events / 0.1 GeV")
#h_higgs_Eta_dummy.SetTitleOffset(1.35, "Y")
#h_higgs_Eta_dummy.SetXTitle("#eta of h [GeV]")
#h_higgs_Eta_dummy.SetMaximum( 0.1 )

h_muon_Phi_dummy = ROOT.TH1F("h_muon_Phi_dummy", "h_muon_Phi_dummy", 80,-4,4)
h_muon_Phi_dummy.SetYTitle("Fraction of events / 0.1 rad")
h_muon_Phi_dummy.SetTitleOffset(1.35, "Y")
h_muon_Phi_dummy.SetXTitle("#phi of #mu [rad]")
h_muon_Phi_dummy.SetMaximum( 0.1 )

h_higgs_Phi_dummy = ROOT.TH1F("h_higgs_Phi_dummy", "h_higgs_Phi_dummy", 80,-4,4)
h_higgs_Phi_dummy.SetYTitle("Fraction of events")
h_higgs_Phi_dummy.SetTitleOffset(1.35, "Y")
h_higgs_Phi_dummy.SetXTitle("#phi of h [rad]")
h_higgs_Phi_dummy.SetMaximum( 1.4 )

h_higgs_p_dummy = ROOT.TH1F("h_higgs_p_dummy", "h_higgs_p_dummy", 50, 0, 500)
h_higgs_p_dummy.SetYTitle("Fraction of events / 1 GeV")
h_higgs_p_dummy.SetTitleOffset(1.35, "Y")
h_higgs_p_dummy.SetXTitle("p of h [GeV]")
h_higgs_p_dummy.SetMaximum( 0.1 )

h_higgs_M_dummy = ROOT.TH1F("h_higgs_M_dummy", "h_higgs_M_dummy", 220, 80.5, 300.5)
h_higgs_M_dummy.SetYTitle("Fraction of events / 1 GeV")
h_higgs_M_dummy.SetTitleOffset(1.35, "Y")
h_higgs_M_dummy.SetXTitle("Mass of h [GeV]")
h_higgs_M_dummy.SetLabelSize(0.03,"X")
h_higgs_M_dummy.SetMaximum( 1.5 )
h_higgs_M_dummy.SetNdivisions(10)
h_higgs_M_dummy.GetXaxis().SetMoreLogLabels()

h_higgs_p = ROOT.TH1F("h_higgs_p", "h_higgs_p", 50, 0, 500)
h_higgs_p.SetLineColor(ROOT.kBlue)
h_higgs_p.SetLineWidth(2)
h_higgs_p.SetLineStyle(1)

h_higgs_M = ROOT.TH1F("h_higgs_M", "h_higgs_M", 10, 120.5, 130.5)
h_higgs_M.SetLineColor(ROOT.kBlue)
h_higgs_M.SetLineWidth(2)
h_higgs_M.SetLineStyle(1)

h_higgs_pT = ROOT.TH1F("h_higgs_pT", "h_higgs_pT", 10, 0, 10)
h_higgs_pT.SetLineColor(ROOT.kBlue)
h_higgs_pT.SetLineWidth(2)
h_higgs_pT.SetLineStyle(1)

h_n1_1_pT_dummy = ROOT.TH1F("h_n1_1_pT_dummy", "h_n1_1_pT_dummy", 70, 0, 70)
h_n1_1_pT_dummy.SetYTitle("Fraction of events / 1 GeV")
h_n1_1_pT_dummy.SetTitleOffset(1.35, "Y")
h_n1_1_pT_dummy.SetXTitle("p_{T} of n_{1} [GeV]")
h_n1_1_pT_dummy.SetMaximum( yMax )

h_higgs_pZ = ROOT.TH1F("h_higgs_pZ", "h_higgs_pZ", 50, 0, 500)
h_higgs_pZ.SetLineColor(ROOT.kBlue)
h_higgs_pZ.SetLineWidth(2)
h_higgs_pZ.SetLineStyle(1)

h_n1_1_pZ_dummy = ROOT.TH1F("h_n1_1_pZ_dummy", "h_n1_1_pZ_dummy", 300, 0, 300)
h_n1_1_pZ_dummy.SetYTitle("Fraction of events / 1 GeV")
h_n1_1_pZ_dummy.SetTitleOffset(1.35, "Y")
h_n1_1_pZ_dummy.SetXTitle("|p_{Z}| of n_{1} [GeV]")
h_n1_1_pZ_dummy.SetMaximum( 0.1 )

#h_higgs_Eta = ROOT.TH1F("h_higgs_Eta", "h_higgs_Eta", 50,0,5)
#h_higgs_Eta.SetLineColor(ROOT.kBlue)
#h_higgs_Eta.SetLineWidth(2)
#h_higgs_Eta.SetLineStyle(1)

h_n1_1_Eta_dummy = ROOT.TH1F("h_n1_1_Eta_dummy", "h_n1_1_Eta_dummy", 100,-5,5)
h_n1_1_Eta_dummy.SetYTitle("Fraction of events / 0.1")
h_n1_1_Eta_dummy.SetTitleOffset(1.35, "Y")
h_n1_1_Eta_dummy.SetXTitle("#eta of n_{1}")
h_n1_1_Eta_dummy.SetMaximum( 0.1 )

h_higgs_Phi = ROOT.TH1F("h_higgs_Phi", "h_higgs_Phi", 80,-4,4)
h_higgs_Phi.SetLineColor(ROOT.kBlue)
h_higgs_Phi.SetLineWidth(2)
h_higgs_Phi.SetLineStyle(1)

h_n1_1_Phi_dummy = ROOT.TH1F("h_n1_1_Phi_dummy", "h_n1_1_Phi_dummy", 80,-4,4)
h_n1_1_Phi_dummy.SetYTitle("Fraction of events / 0.1 rad")
h_n1_1_Phi_dummy.SetTitleOffset(1.35, "Y")
h_n1_1_Phi_dummy.SetXTitle("#phi of n_{1} [rad]")
h_n1_1_Phi_dummy.SetMaximum( 0.05 )

h_n1_1_p_dummy = ROOT.TH1F("h_n1_1_p_dummy", "h_n1_1_p_dummy", 300, 0, 300)
h_n1_1_p_dummy.SetYTitle("Fraction of events / 1 GeV")
h_n1_1_p_dummy.SetTitleOffset(1.35, "Y")
h_n1_1_p_dummy.SetXTitle("p of n_{1} [GeV]")
h_n1_1_p_dummy.SetMaximum( 0.1 )

h_n1_1_M_dummy = ROOT.TH1F("h_n1_1_M_dummy", "h_n1_1_M_dummy", 200, 0.05, 20.05)
h_n1_1_M_dummy.SetYTitle("Fraction of events / 0.1 GeV")
h_n1_1_M_dummy.SetTitleOffset(1.35, "Y")
h_n1_1_M_dummy.SetXTitle("Mass of n_{1} [GeV]")
h_n1_1_M_dummy.SetMaximum( 1.6 )

h_n1_1_p = ROOT.TH1F("h_n1_1_p", "h_n1_1_p", 300, 0, 300)
h_n1_1_p.SetLineColor(ROOT.kBlue)
h_n1_1_p.SetLineWidth(2)
h_n1_1_p.SetLineStyle(1)

h_n1_1_M = ROOT.TH1F("h_n1_1_M", "h_n1_1_M", 200, 0.05, 20.05)
h_n1_1_M.SetLineColor(ROOT.kBlue)
h_n1_1_M.SetLineWidth(2)
h_n1_1_M.SetLineStyle(1)

h_n1_1_pT = ROOT.TH1F("h_n1_1_pT", "h_n1_1_pT", 70, 0, 70) #this is the peak at 60
h_n1_1_pT.SetLineColor(ROOT.kBlue)
h_n1_1_pT.SetLineWidth(2)
h_n1_1_pT.SetLineStyle(1)

h_n1_1_pZ = ROOT.TH1F("h_n1_1_pZ", "h_n1_1_pZ", 300, 0, 300) 
h_n1_1_pZ.SetLineColor(ROOT.kBlue)
h_n1_1_pZ.SetLineWidth(2)
h_n1_1_pZ.SetLineStyle(1)

h_n1_1_Eta = ROOT.TH1F("h_n1_1_Eta", "h_n1_1_Eta", 100,-5,5) 
h_n1_1_Eta.SetLineColor(ROOT.kBlue)
h_n1_1_Eta.SetLineWidth(2)
h_n1_1_Eta.SetLineStyle(1)

h_n1_1_Phi = ROOT.TH1F("h_n1_1_Phi", "h_n1_1_Phi", 80,-4,4) 
h_n1_1_Phi.SetLineColor(ROOT.kBlue)
h_n1_1_Phi.SetLineWidth(2)
h_n1_1_Phi.SetLineStyle(1)

#h_n1_2_pT_dummy = ROOT.TH1F("h_n1_2_pT_dummy", "h_n1_2_pT_dummy", 700, 0, 70) #this is the peak at ~10GeV
#h_n1_2_pT_dummy.SetYTitle("Fraction of events / 1 GeV")
#h_n1_2_pT_dummy.SetTitleOffset(1.35, "Y")
#h_n1_2_pT_dummy.SetXTitle("p_{T n_{1}} [GeV]")
#h_n1_2_pT_dummy.SetMaximum( yMax )
#
#h_n1_2_p_dummy = ROOT.TH1F("h_n1_2_p_dummy", "h_n1_2_p_dummy", 20, 50, 70)
#h_n1_2_p_dummy.SetYTitle("Fraction of events / 1 GeV")
#h_n1_2_p_dummy.SetTitleOffset(1.35, "Y")
#h_n1_2_p_dummy.SetXTitle("p_{n_{1}} [GeV]")
#h_n1_2_p_dummy.SetMaximum( 0.05 )
#
#h_n1_2_M_dummy = ROOT.TH1F("h_n1_2_M_dummy", "h_n1_2_M_dummy", 200, 0, 20)
#h_n1_2_M_dummy.SetYTitle("Fraction of events / 1 GeV")
#h_n1_2_M_dummy.SetTitleOffset(1.35, "Y")
#h_n1_2_M_dummy.SetXTitle("m_{n_{1}} [GeV]")
#h_n1_2_M_dummy.SetMaximum( 1.2 )

h_n1_2_p = ROOT.TH1F("h_n1_2_p", "h_n1_2_p", 300, 0, 300)
h_n1_2_p.SetLineColor(ROOT.kRed)
h_n1_2_p.SetLineWidth(2)
h_n1_2_p.SetLineStyle(1)

#h_n1_2_M = ROOT.TH1F("h_n1_2_M", "h_n1_2_M", 200, 0.05, 20.05)
#h_n1_2_M.SetLineColor(ROOT.kRed)
#h_n1_2_M.SetLineWidth(2)
#h_n1_2_M.SetLineStyle(1)

h_n1_2_pT = ROOT.TH1F("h_n1_2_pT", "h_n1_2_pT", 70, 0, 70)
h_n1_2_pT.SetLineColor(ROOT.kRed)
h_n1_2_pT.SetLineWidth(2)
h_n1_2_pT.SetLineStyle(1)


h_nD_1_pT_dummy = ROOT.TH1F("h_nD_1_pT_dummy", "h_nD_1_pT_dummy", 130, 0, 130)
h_nD_1_pT_dummy.SetYTitle("Fraction of events / 1 GeV")
h_nD_1_pT_dummy.SetTitleOffset(1.35, "Y")
h_nD_1_pT_dummy.SetXTitle("p_{T} of n_{D} [GeV]")
h_nD_1_pT_dummy.SetMaximum( 0.1 )

h_n1_2_pZ = ROOT.TH1F("h_n1_2_pZ", "h_n1_2_pZ", 300, 0, 300)
h_n1_2_pZ.SetLineColor(ROOT.kRed)
h_n1_2_pZ.SetLineWidth(2)
h_n1_2_pZ.SetLineStyle(1)


h_nD_1_pZ_dummy = ROOT.TH1F("h_nD_1_pZ_dummy", "h_nD_1_pZ_dummy", 130, 0, 130)
h_nD_1_pZ_dummy.SetYTitle("Fraction of events / 1 GeV")
h_nD_1_pZ_dummy.SetTitleOffset(1.35, "Y")
h_nD_1_pZ_dummy.SetXTitle("|p_{Z}| of n_{D} [GeV]")
h_nD_1_pZ_dummy.SetMaximum( 0.1 )

h_n1_2_Eta = ROOT.TH1F("h_n1_2_Eta", "h_n1_2_Eta", 100,-5,5)
h_n1_2_Eta.SetLineColor(ROOT.kRed)
h_n1_2_Eta.SetLineWidth(2)
h_n1_2_Eta.SetLineStyle(1)


h_nD_1_Eta_dummy = ROOT.TH1F("h_nD_1_Eta_dummy", "h_nD_1_Eta_dummy", 100,-5,5)
h_nD_1_Eta_dummy.SetYTitle("Fraction of events / 0.1")
h_nD_1_Eta_dummy.SetTitleOffset(1.35, "Y")
h_nD_1_Eta_dummy.SetXTitle("#eta of n_{D}")
h_nD_1_Eta_dummy.SetMaximum( 0.1 )

h_n1_2_Phi = ROOT.TH1F("h_n1_2_Phi", "h_n1_2_Phi", 80,-4,4)
h_n1_2_Phi.SetLineColor(ROOT.kRed)
h_n1_2_Phi.SetLineWidth(2)
h_n1_2_Phi.SetLineStyle(1)


h_nD_1_Phi_dummy = ROOT.TH1F("h_nD_1_Phi_dummy", "h_nD_1_Phi_dummy", 80,-4,4)
h_nD_1_Phi_dummy.SetYTitle("Fraction of events / 0.1 rad")
h_nD_1_Phi_dummy.SetTitleOffset(1.35, "Y")
h_nD_1_Phi_dummy.SetXTitle("#phi of n_{D} [rad]")
h_nD_1_Phi_dummy.SetMaximum( 0.05 )

h_nD_1_p_dummy = ROOT.TH1F("h_nD_1_p_dummy", "h_nD_1_p_dummy", 130, 0, 130)
h_nD_1_p_dummy.SetYTitle("Fraction of events / 1 GeV")
h_nD_1_p_dummy.SetTitleOffset(1.35, "Y")
h_nD_1_p_dummy.SetXTitle("p of n_{D} [GeV]")
h_nD_1_p_dummy.SetMaximum( 0.1 )

h_nD_1_M_dummy = ROOT.TH1F("h_nD_1_M_dummy", "h_nD_1_M_dummy", 20, 0.05, 2.05)
h_nD_1_M_dummy.SetYTitle("Fraction of events / 0.1 GeV")
h_nD_1_M_dummy.SetTitleOffset(1.35, "Y")
h_nD_1_M_dummy.SetXTitle("Mass of n_{D} [GeV]")
h_nD_1_M_dummy.SetMaximum( 1.6 )

h_nD_1_p = ROOT.TH1F("h_nD_1_p", "h_nD_1_p", 130, 0, 130)
h_nD_1_p.SetLineColor(ROOT.kBlue)
h_nD_1_p.SetLineWidth(2)
h_nD_1_p.SetLineStyle(1)

h_nD_1_M = ROOT.TH1F("h_nD_1_M", "h_nD_1_M", 20, 0.05, 2.05)
h_nD_1_M.SetLineColor(ROOT.kBlue)
h_nD_1_M.SetLineWidth(2)
h_nD_1_M.SetLineStyle(1)

h_nD_1_pT = ROOT.TH1F("h_nD_1_pT", "h_nD_1_pT", 130, 0, 130)
h_nD_1_pT.SetLineColor(ROOT.kBlue)
h_nD_1_pT.SetLineWidth(2)
h_nD_1_pT.SetLineStyle(1)

h_nD_1_pZ = ROOT.TH1F("h_nD_1_pZ", "h_nD_1_pZ", 130, 0, 130)
h_nD_1_pZ.SetLineColor(ROOT.kBlue)
h_nD_1_pZ.SetLineWidth(2)
h_nD_1_pZ.SetLineStyle(1)

h_nD_1_Eta = ROOT.TH1F("h_nD_1_Eta", "h_nD_1_Eta", 100,-5,5)
h_nD_1_Eta.SetLineColor(ROOT.kBlue)
h_nD_1_Eta.SetLineWidth(2)
h_nD_1_Eta.SetLineStyle(1)

h_nD_1_Phi = ROOT.TH1F("h_nD_1_Phi", "h_nD_1_Phi", 80,-4,4)
h_nD_1_Phi.SetLineColor(ROOT.kBlue)
h_nD_1_Phi.SetLineWidth(2)
h_nD_1_Phi.SetLineStyle(1)

#h_nD_2_pT_dummy = ROOT.TH1F("h_nD_2_pT_dummy", "h_nD_2_pT_dummy", 100, 0, 100)
#h_nD_2_pT_dummy.SetYTitle("Fraction of events / 1 GeV")
#h_nD_2_pT_dummy.SetTitleOffset(1.35, "Y")
#h_nD_2_pT_dummy.SetXTitle("p_{T nD_2} [GeV]")
#h_nD_2_pT_dummy.SetMaximum( 0.01 )
#
#h_nD_2_p_dummy = ROOT.TH1F("h_nD_2_p_dummy", "h_nD_2_p_dummy", 100, 0, 100)
#h_nD_2_p_dummy.SetYTitle("Fraction of events / 1 GeV")
#h_nD_2_p_dummy.SetTitleOffset(1.35, "Y")
#h_nD_2_p_dummy.SetXTitle("p_{nD_2} [GeV]")
#h_nD_2_p_dummy.SetMaximum( 0.01 )
#
#h_nD_2_M_dummy = ROOT.TH1F("h_nD_2_M_dummy", "h_nD_2_M_dummy", 20, 0, 2)
#h_nD_2_M_dummy.SetYTitle("Fraction of events / 1 GeV")
#h_nD_2_M_dummy.SetTitleOffset(1.35, "Y")
#h_nD_2_M_dummy.SetXTitle("m_{nD_2} [GeV]")
#h_nD_2_M_dummy.SetMaximum( 1.2 )

h_nD_2_p = ROOT.TH1F("h_nD_2_p", "h_nD_2_p", 130, 0, 130)
h_nD_2_p.SetLineColor(ROOT.kRed)
h_nD_2_p.SetLineWidth(2)
h_nD_2_p.SetLineStyle(1)

#h_nD_2_M = ROOT.TH1F("h_nD_2_M", "h_nD_2_M", 20, 0.05, 2.05)
#h_nD_2_M.SetLineColor(ROOT.kRed)
#h_nD_2_M.SetLineWidth(2)
#h_nD_2_M.SetLineStyle(1)

h_nD_2_pT = ROOT.TH1F("h_nD_2_pT", "h_nD_2_pT", 130, 0, 130)
h_nD_2_pT.SetLineColor(ROOT.kRed)
h_nD_2_pT.SetLineWidth(2)
h_nD_2_pT.SetLineStyle(1)

h_gammaD_1_pT_dummy = ROOT.TH1F("h_gammaD_1_pT_dummy", "h_gammaD_1_pT_dummy", 100, 0, 100)
h_gammaD_1_pT_dummy.SetYTitle("Fraction of events / 1 GeV")
h_gammaD_1_pT_dummy.SetTitleOffset(1.35, "Y")
h_gammaD_1_pT_dummy.SetXTitle("p_{T} of #gamma_{D} [GeV]")
h_gammaD_1_pT_dummy.SetMaximum( 0.1 )

h_nD_2_pZ = ROOT.TH1F("h_nD_2_pZ", "h_nD_2_pZ", 130, 0, 130)
h_nD_2_pZ.SetLineColor(ROOT.kRed)
h_nD_2_pZ.SetLineWidth(2)
h_nD_2_pZ.SetLineStyle(1)

h_gammaD_1_pZ_dummy = ROOT.TH1F("h_gammaD_1_pZ_dummy", "h_gammaD_1_pZ_dummy", 100, 0, 100)
h_gammaD_1_pZ_dummy.SetYTitle("Fraction of events / 1 GeV")
h_gammaD_1_pZ_dummy.SetTitleOffset(1.35, "Y")
h_gammaD_1_pZ_dummy.SetXTitle("|p_{Z}| of #gamma_{D} [GeV]")
h_gammaD_1_pZ_dummy.SetMaximum( 0.1 )

h_nD_2_Eta = ROOT.TH1F("h_nD_2_Eta", "h_nD_2_Eta", 100,-5,5)
h_nD_2_Eta.SetLineColor(ROOT.kRed)
h_nD_2_Eta.SetLineWidth(2)
h_nD_2_Eta.SetLineStyle(1)

h_gammaD_1_Eta_dummy = ROOT.TH1F("h_gammaD_1_Eta_dummy", "h_gammaD_1_Eta_dummy",100,-5,5) 
h_gammaD_1_Eta_dummy.SetYTitle("Fraction of events / 0.1")
h_gammaD_1_Eta_dummy.SetTitleOffset(1.35, "Y")
h_gammaD_1_Eta_dummy.SetXTitle("#eta of #gamma_{D}")
h_gammaD_1_Eta_dummy.SetMaximum( 0.1 )

h_nD_2_Phi = ROOT.TH1F("h_nD_2_Phi", "h_nD_2_Phi", 80,-4,4)
h_nD_2_Phi.SetLineColor(ROOT.kRed)
h_nD_2_Phi.SetLineWidth(2)
h_nD_2_Phi.SetLineStyle(1)

h_gammaD_1_Phi_dummy = ROOT.TH1F("h_gammaD_1_Phi_dummy", "h_gammaD_1_Phi_dummy",80,-4,4 )
h_gammaD_1_Phi_dummy.SetYTitle("Fraction of events / 0.1 rad")
h_gammaD_1_Phi_dummy.SetTitleOffset(1.35, "Y")
h_gammaD_1_Phi_dummy.SetXTitle("#phi of #gamma_{D} [rad]")
h_gammaD_1_Phi_dummy.SetMaximum( 0.05 )

h_gammaD_1_p_dummy = ROOT.TH1F("h_gammaD_1_p_dummy", "h_gammaD_1_p_dummy", 100, 0, 100)
h_gammaD_1_p_dummy.SetYTitle("Fraction of events / 1 GeV")
h_gammaD_1_p_dummy.SetTitleOffset(1.35, "Y")
h_gammaD_1_p_dummy.SetXTitle("p of #gamma_{D} [GeV]")
h_gammaD_1_p_dummy.SetMaximum( 0.1 )

h_gammaD_1_M_dummy = ROOT.TH1F("h_gammaD_1_M_dummy", "h_gammaD_1_M_dummy", 101, 0.1, 10.1)
h_gammaD_1_M_dummy.SetYTitle("Fraction of events / 0.1 GeV")
h_gammaD_1_M_dummy.SetTitleOffset(1.35, "Y")
h_gammaD_1_M_dummy.SetXTitle("Mass of #gamma_{D} [GeV]")
h_gammaD_1_M_dummy.SetMaximum( 1.4 )

h_gammaD_1_p = ROOT.TH1F("h_gammaD_1_p", "h_gammaD_1_p", 100, 0, 100)
h_gammaD_1_p.SetLineColor(ROOT.kBlue)
h_gammaD_1_p.SetLineWidth(2)
h_gammaD_1_p.SetLineStyle(1)

h_gammaD_1_M = ROOT.TH1F("h_gammaD_1_M", "h_gammaD_1_M", 101, 0.1, 10.1)
h_gammaD_1_M.SetLineColor(ROOT.kBlue)
h_gammaD_1_M.SetLineWidth(2)
h_gammaD_1_M.SetLineStyle(1)

h_gammaD_1_pT = ROOT.TH1F("h_gammaD_1_pT", "h_gammaD_1_pT", 100, 0, 100)
h_gammaD_1_pT.SetLineColor(ROOT.kBlue)
h_gammaD_1_pT.SetLineWidth(2)
h_gammaD_1_pT.SetLineStyle(1)

h_gammaD_1_pZ = ROOT.TH1F("h_gammaD_1_pZ", "h_gammaD_1_pZ", 100, 0, 100)
h_gammaD_1_pZ.SetLineColor(ROOT.kBlue)
h_gammaD_1_pZ.SetLineWidth(2)
h_gammaD_1_pZ.SetLineStyle(1)

h_gammaD_1_Eta = ROOT.TH1F("h_gammaD_1_Eta", "h_gammaD_1_Eta",100,-5,5) 
h_gammaD_1_Eta.SetLineColor(ROOT.kBlue)
h_gammaD_1_Eta.SetLineWidth(2)
h_gammaD_1_Eta.SetLineStyle(1)

h_gammaD_1_Phi = ROOT.TH1F("h_gammaD_1_Phi", "h_gammaD_1_Phi", 80,-4,4)
h_gammaD_1_Phi.SetLineColor(ROOT.kBlue)
h_gammaD_1_Phi.SetLineWidth(2)
h_gammaD_1_Phi.SetLineStyle(1)

#h_gammaD_2_pT_dummy = ROOT.TH1F("h_gammaD_2_pT_dummy", "h_gammaD_2_pT_dummy", 100, 0, 100)
#h_gammaD_2_pT_dummy.SetYTitle("Fraction of events / 1 GeV")
#h_gammaD_2_pT_dummy.SetTitleOffset(1.35, "Y")
#h_gammaD_2_pT_dummy.SetXTitle("p_{T gammaD_2} [GeV]")
#h_gammaD_2_pT_dummy.SetMaximum( 0.01 )
#
#h_gammaD_2_p_dummy = ROOT.TH1F("h_gammaD_2_p_dummy", "h_gammaD_2_p_dummy", 100, 0, 100)
#h_gammaD_2_p_dummy.SetYTitle("Fraction of events / 1 GeV")
#h_gammaD_2_p_dummy.SetTitleOffset(1.35, "Y")
#h_gammaD_2_p_dummy.SetXTitle("p_{gammaD_2} [GeV]")
#h_gammaD_2_p_dummy.SetMaximum( 0.01 )
#
#h_gammaD_2_M_dummy = ROOT.TH1F("h_gammaD_2_M_dummy", "h_gammaD_2_M_dummy", 300, 0, 3)
#h_gammaD_2_M_dummy.SetYTitle("Fraction of events / 1 GeV")
#h_gammaD_2_M_dummy.SetTitleOffset(1.35, "Y")
#h_gammaD_2_M_dummy.SetXTitle("m_{gammaD_2} [GeV]")
#h_gammaD_2_M_dummy.SetMaximum( 1.2 )

h_gammaD_2_p = ROOT.TH1F("h_gammaD_2_p", "h_gammaD_2_p", 100, 0, 100)
h_gammaD_2_p.SetLineColor(ROOT.kRed)
h_gammaD_2_p.SetLineWidth(2)
h_gammaD_2_p.SetLineStyle(1)

#h_gammaD_2_M = ROOT.TH1F("h_gammaD_2_M", "h_gammaD_2_M", 500, 0.005, 10.005)
#h_gammaD_2_M.SetLineColor(ROOT.kRed)
#h_gammaD_2_M.SetLineWidth(2)
#h_gammaD_2_M.SetLineStyle(1)

h_gammaD_2_pT = ROOT.TH1F("h_gammaD_2_pT", "h_gammaD_2_pT", 100, 0, 100)
h_gammaD_2_pT.SetLineColor(ROOT.kRed)
h_gammaD_2_pT.SetLineWidth(2)
h_gammaD_2_pT.SetLineStyle(1)

h_gammaD_2_pZ = ROOT.TH1F("h_gammaD_2_pZ", "h_gammaD_2_pZ", 100, 0, 100)
h_gammaD_2_pZ.SetLineColor(ROOT.kRed)
h_gammaD_2_pZ.SetLineWidth(2)
h_gammaD_2_pZ.SetLineStyle(1)

h_gammaD_2_Eta = ROOT.TH1F("h_gammaD_2_Eta", "h_gammaD_2_Eta", 100,-5,5)
h_gammaD_2_Eta.SetLineColor(ROOT.kRed)
h_gammaD_2_Eta.SetLineWidth(2)
h_gammaD_2_Eta.SetLineStyle(1)

h_gammaD_2_Phi = ROOT.TH1F("h_gammaD_2_Phi", "h_gammaD_2_Phi", 80,-4,4)
h_gammaD_2_Phi.SetLineColor(ROOT.kRed)
h_gammaD_2_Phi.SetLineWidth(2)
h_gammaD_2_Phi.SetLineStyle(1)

h_muon_pT_0 = ROOT.TH1F("h_muon_pT_0", "h_muon_pT_0", nBins, binMin, binMax)
h_muon_pT_0.SetLineColor(ROOT.kBlue)
h_muon_pT_0.SetLineWidth(2)
h_muon_pT_0.SetLineStyle(1)

h_muon_pT_1 = ROOT.TH1F("h_muon_pT_1", "h_muon_pT_1", nBins, binMin, binMax)
h_muon_pT_1.SetLineColor(ROOT.kGreen+1)
h_muon_pT_1.SetLineWidth(2)
h_muon_pT_1.SetLineStyle(2)

h_muon_pT_2 = ROOT.TH1F("h_muon_pT_2", "h_muon_pT_2", nBins, binMin, binMax)
h_muon_pT_2.SetLineColor(ROOT.kRed)
h_muon_pT_2.SetLineWidth(2)
h_muon_pT_2.SetLineStyle(3)

h_muon_pT_3 = ROOT.TH1F("h_muon_pT_3", "h_muon_pT_3", nBins, binMin, binMax)
h_muon_pT_3.SetLineColor(ROOT.kBlack)
h_muon_pT_3.SetLineWidth(2)
h_muon_pT_3.SetLineStyle(4)

h_muon_phi_dummy = ROOT.TH1F("h_muon_phi_dummy", "h_muon_phi_dummy", 80, -4, 4)
h_muon_phi_dummy.SetYTitle("Fraction of events / 0.1 rad")
h_muon_phi_dummy.SetTitleOffset(1.35, "Y")
h_muon_phi_dummy.SetXTitle("#phi of #mu [rad]")
h_muon_phi_dummy.SetMaximum( 0.1 )

h_muon_phi_0 = ROOT.TH1F("h_muon_phi_0", "h_muon_phi_0", 80, -4, 4)
h_muon_phi_0.SetLineColor(ROOT.kBlue)
h_muon_phi_0.SetLineWidth(2)
h_muon_phi_0.SetLineStyle(1)

h_muon_phi_1 = ROOT.TH1F("h_muon_phi_1", "h_muon_phi_1", 80, -4, 4)
h_muon_phi_1.SetLineColor(ROOT.kGreen+1)
h_muon_phi_1.SetLineWidth(2)
h_muon_phi_1.SetLineStyle(2)

h_muon_phi_2 = ROOT.TH1F("h_muon_phi_2", "h_muon_phi_2", 80, -4, 4)
h_muon_phi_2.SetLineColor(ROOT.kRed)
h_muon_phi_2.SetLineWidth(2)
h_muon_phi_2.SetLineStyle(3)

h_muon_phi_3 = ROOT.TH1F("h_muon_phi_3", "h_muon_phi_3", 80, -4, 4)
h_muon_phi_3.SetLineColor(ROOT.kBlack)
h_muon_phi_3.SetLineWidth(2)
h_muon_phi_3.SetLineStyle(4)

h_muon_p_dummy = ROOT.TH1F("h_muon_p_dummy", "h_muon_p_dummy", 125, 0, 125)
h_muon_p_dummy.SetYTitle("Fraction of events / 1 GeV")
h_muon_p_dummy.SetTitleOffset(1.35, "Y")
h_muon_p_dummy.SetXTitle("p of #mu [GeV]")
h_muon_p_dummy.SetMaximum( 0.2 )

h_muon_p_0 = ROOT.TH1F("h_muon_p_0", "h_muon_p_0", 125, 0, 125)
h_muon_p_0.SetLineColor(ROOT.kBlue)
h_muon_p_0.SetLineWidth(2)
h_muon_p_0.SetLineStyle(1)

h_muon_p_1 = ROOT.TH1F("h_muon_p_1", "h_muon_p_1", 125, 0, 125)
h_muon_p_1.SetLineColor(ROOT.kGreen+1)
h_muon_p_1.SetLineWidth(2)
h_muon_p_1.SetLineStyle(2)

h_muon_p_2 = ROOT.TH1F("h_muon_p_2", "h_muon_p_2", 125, 0, 125)
h_muon_p_2.SetLineColor(ROOT.kRed)
h_muon_p_2.SetLineWidth(2)
h_muon_p_2.SetLineStyle(3)

h_muon_p_3 = ROOT.TH1F("h_muon_p_3", "h_muon_p_3", 125, 0, 125)
h_muon_p_3.SetLineColor(ROOT.kBlack)
h_muon_p_3.SetLineWidth(2)
h_muon_p_3.SetLineStyle(125)

h_muon_pZ_0 = ROOT.TH1F("h_muon_pZ_0", "h_muon_pZ_0", 125, 0, 125)
h_muon_pZ_0.SetLineColor(ROOT.kBlue)
h_muon_pZ_0.SetLineWidth(2)
h_muon_pZ_0.SetLineStyle(1)

h_muon_pZ_1 = ROOT.TH1F("h_muon_pZ_1", "h_muon_pZ_1", 125, 0, 125)
h_muon_pZ_1.SetLineColor(ROOT.kGreen+1)
h_muon_pZ_1.SetLineWidth(2)
h_muon_pZ_1.SetLineStyle(2)

h_muon_pZ_2 = ROOT.TH1F("h_muon_pZ_2", "h_muon_pZ_2", 125, 0, 125)
h_muon_pZ_2.SetLineColor(ROOT.kRed)
h_muon_pZ_2.SetLineWidth(2)
h_muon_pZ_2.SetLineStyle(3)

h_muon_pZ_3 = ROOT.TH1F("h_muon_pZ_3", "h_muon_pZ_3", 125, 0, 125)
h_muon_pZ_3.SetLineColor(ROOT.kBlack)
h_muon_pZ_3.SetLineWidth(2)
h_muon_pZ_3.SetLineStyle(125)




################################################################################
#                                   eta of muons                                 
################################################################################

nBins  =   60
binMin = -3.0
binMax =  3.0
yMax = 0.045

h_muon_eta_dummy = ROOT.TH1F("h_muon_eta_dummy", "h_muon_eta_dummy", 100, -5, 5)
h_muon_eta_dummy.SetYTitle("Fraction of events / 0.1")
h_muon_eta_dummy.GetYaxis().SetNdivisions(508);
h_muon_eta_dummy.SetTitleOffset(1.35, "Y")
h_muon_eta_dummy.SetXTitle("#eta of #mu")
h_muon_eta_dummy.SetMaximum( yMax )

h_muon_eta_0 = ROOT.TH1F("h_muon_eta_0", "h_muon_eta_0", 100,-5,5)
h_muon_eta_0.SetLineColor(ROOT.kBlue)
h_muon_eta_0.SetLineWidth(2)
h_muon_eta_0.SetLineStyle(1)

h_muon_eta_1 = ROOT.TH1F("h_muon_eta_1", "h_muon_eta_1", 100,-5,5)
h_muon_eta_1.SetLineColor(ROOT.kGreen+1)
h_muon_eta_1.SetLineWidth(2)
h_muon_eta_1.SetLineStyle(2)

h_muon_eta_2 = ROOT.TH1F("h_muon_eta_2", "h_muon_eta_2", 100,-5,5)
h_muon_eta_2.SetLineColor(ROOT.kRed)
h_muon_eta_2.SetLineWidth(2)
h_muon_eta_2.SetLineStyle(3)

h_muon_eta_3 = ROOT.TH1F("h_muon_eta_3", "h_muon_eta_3", 100,-5,5)
h_muon_eta_3.SetLineColor(ROOT.kBlack)
h_muon_eta_3.SetLineWidth(2)
h_muon_eta_3.SetLineStyle(4)

################################################################################
#                                   mass of dimuons                             
################################################################################

nBins  = 125
binMin = 0.0
binMax = 125.0
yMax   = 0.4

#h_dimuon_m_dummy = ROOT.TH1F("h_dimuon_m_dummy", "h_dimuon_m_dummy", nBins, binMin, binMax)
#h_dimuon_m_dummy.SetYTitle("Fraction of events / 1 GeV")
#h_dimuon_m_dummy.GetYaxis().SetNdivisions(508);
#h_dimuon_m_dummy.SetTitleOffset(1.35, "Y")
#h_dimuon_m_dummy.SetXTitle("m_{#mu#mu} [GeV]")
#h_dimuon_m_dummy.SetMaximum( 1.2 )
#
#h_dimuon_m_0 = ROOT.TH1F("h_dimuon_m_0", "h_dimuon_m_0", nBins, binMin, binMax)
#h_dimuon_m_0.SetLineColor(ROOT.kBlue)
#h_dimuon_m_0.SetLineWidth(2)
#h_dimuon_m_0.SetLineStyle(1)
#
#h_dimuon_m_1 = ROOT.TH1F("h_dimuon_m_1", "h_dimuon_m_1", nBins, binMin, binMax)
#h_dimuon_m_1.SetLineColor(ROOT.kGreen+1)
#h_dimuon_m_1.SetLineWidth(2)
#h_dimuon_m_1.SetLineStyle(2)
#
#h_dimuon_m_2 = ROOT.TH1F("h_dimuon_m_2", "h_dimuon_m_2", nBins, binMin, binMax)
#h_dimuon_m_2.SetLineColor(ROOT.kRed)
#h_dimuon_m_2.SetLineWidth(2)
#h_dimuon_m_2.SetLineStyle(3)
#
#h_dimuon_m_3 = ROOT.TH1F("h_dimuon_m_3", "h_dimuon_m_3", nBins, binMin, binMax)
#h_dimuon_m_3.SetLineColor(ROOT.kBlack)
#h_dimuon_m_3.SetLineWidth(2)
#h_dimuon_m_3.SetLineStyle(4)
#
#h_dimuon_m_log_dummy = ROOT.TH1F("h_dimuon_m_log_dummy", "h_dimuon_m_log_dummy", nBins, binMin, binMax)
#h_dimuon_m_log_dummy.SetYTitle("Fraction of events / 1 GeV")
#h_dimuon_m_log_dummy.GetYaxis().SetNdivisions(508);
#h_dimuon_m_log_dummy.SetTitleOffset(1.35, "Y")
#h_dimuon_m_log_dummy.SetXTitle("m_{#mu#mu} [GeV]")
#h_dimuon_m_log_dummy.SetMaximum( 1.2 )
#
#h_dimuon_m_log_0 = ROOT.TH1F("h_dimuon_m_log_0", "h_dimuon_m_log_0", nBins, binMin, binMax)
#h_dimuon_m_log_0.SetLineColor(ROOT.kBlue)
#h_dimuon_m_log_0.SetLineWidth(2)
#h_dimuon_m_log_0.SetLineStyle(1)
#
#h_dimuon_m_log_1 = ROOT.TH1F("h_dimuon_m_log_1", "h_dimuon_m_log_1", nBins, binMin, binMax)
#h_dimuon_m_log_1.SetLineColor(ROOT.kGreen+1)
#h_dimuon_m_log_1.SetLineWidth(2)
#h_dimuon_m_log_1.SetLineStyle(2)
#
#h_dimuon_m_log_2 = ROOT.TH1F("h_dimuon_m_log_2", "h_dimuon_m_log_2", nBins, binMin, binMax)
#h_dimuon_m_log_2.SetLineColor(ROOT.kRed)
#h_dimuon_m_log_2.SetLineWidth(2)
#h_dimuon_m_log_2.SetLineStyle(3)
#
#h_dimuon_m_log_3 = ROOT.TH1F("h_dimuon_m_log_3", "h_dimuon_m_log_3", nBins, binMin, binMax)
#h_dimuon_m_log_3.SetLineColor(ROOT.kBlack)
#h_dimuon_m_log_3.SetLineWidth(2)
#h_dimuon_m_log_3.SetLineStyle(4)
#
#h_dimuon_m_real_fake_dummy = ROOT.TH1F("h_dimuon_m_real_fake_dummy", "h_dimuon_m_real_fake_dummy", nBins, binMin, binMax)
#h_dimuon_m_real_fake_dummy.SetYTitle("Fraction of events / 1 GeV")
#h_dimuon_m_real_fake_dummy.GetYaxis().SetNdivisions(508);
#h_dimuon_m_real_fake_dummy.SetTitleOffset(1.35, "Y")
#h_dimuon_m_real_fake_dummy.SetXTitle("m_{#mu#mu} [GeV]")
#h_dimuon_m_real_fake_dummy.SetMaximum( 1.2 )
#
#h_dimuon_m_real_fake_0 = ROOT.TH1F("h_dimuon_m_real_fake_0", "h_dimuon_m_real_fake_0", nBins, binMin, binMax)
#h_dimuon_m_real_fake_0.SetLineColor(ROOT.kRed)
#h_dimuon_m_real_fake_0.SetLineWidth(2)
#h_dimuon_m_real_fake_0.SetLineStyle(1)
#
#h_dimuon_m_real_fake_1 = ROOT.TH1F("h_dimuon_m_real_fake_1", "h_dimuon_m_real_fake_1", nBins, binMin, binMax)
#h_dimuon_m_real_fake_1.SetLineColor(ROOT.kBlue)
#h_dimuon_m_real_fake_1.SetLineWidth(2)
#h_dimuon_m_real_fake_1.SetLineStyle(2)
#
#h_dimuon_m_real_fake_log_dummy = ROOT.TH1F("h_dimuon_m_real_fake_log_dummy", "h_dimuon_m_real_fake_log_dummy", nBins, binMin, binMax)
#h_dimuon_m_real_fake_log_dummy.SetYTitle("Fraction of events / 1 GeV")
#h_dimuon_m_real_fake_log_dummy.GetYaxis().SetNdivisions(508);
#h_dimuon_m_real_fake_log_dummy.SetTitleOffset(1.35, "Y")
#h_dimuon_m_real_fake_log_dummy.SetXTitle("m_{#mu#mu} [GeV]")
#h_dimuon_m_real_fake_log_dummy.SetMaximum( 1.2 )
#
#h_dimuon_m_real_fake_log_0 = ROOT.TH1F("h_dimuon_m_real_fake_log_0", "h_dimuon_m_real_fake_log_0", nBins, binMin, binMax)
#h_dimuon_m_real_fake_log_0.SetLineColor(ROOT.kRed)
#h_dimuon_m_real_fake_log_0.SetLineWidth(2)
#h_dimuon_m_real_fake_log_0.SetLineStyle(1)
#
#h_dimuon_m_real_fake_log_1 = ROOT.TH1F("h_dimuon_m_real_fake_log_1", "h_dimuon_m_real_fake_log_1", nBins, binMin, binMax)
#h_dimuon_m_real_fake_log_1.SetLineColor(ROOT.kBlue)
#h_dimuon_m_real_fake_log_1.SetLineWidth(2)
#h_dimuon_m_real_fake_log_1.SetLineStyle(2)


#########################
h_dimuon_m_fake_log_dummy = ROOT.TH1F("h_dimuon_m_fake_log_dummy", "h_dimuon_m_fake_log_dummy", 1250, 0, 125)
h_dimuon_m_fake_log_dummy.SetYTitle("Fraction of events / 0.1 GeV")
h_dimuon_m_fake_log_dummy.GetYaxis().SetNdivisions(508);
h_dimuon_m_fake_log_dummy.SetTitleOffset(1.4, "Y")
h_dimuon_m_fake_log_dummy.SetXTitle("Mass of Fake #mu#mu [GeV]")
h_dimuon_m_fake_log_dummy.SetMaximum( 1 )

h_dimuon_m_fake_log_0 = ROOT.TH1F("h_dimuon_m_fake_log_0", "h_dimuon_m_fake_log_0", 1250, 0, 125)
h_dimuon_m_fake_log_0.SetLineColor(ROOT.kRed)
h_dimuon_m_fake_log_0.SetLineWidth(2)
h_dimuon_m_fake_log_0.SetLineStyle(1)

h_dimuon_m_fake_dummy = ROOT.TH1F("h_dimuon_m_fake_dummy", "h_dimuon_m_fake_dummy", nBins, binMin, binMax)
h_dimuon_m_fake_dummy.SetYTitle("Fraction of events / 1 GeV")
h_dimuon_m_fake_dummy.GetYaxis().SetNdivisions(508);
h_dimuon_m_fake_dummy.SetTitleOffset(1.35, "Y") 
h_dimuon_m_fake_dummy.SetXTitle("Mass of Fake #mu#mu [GeV]")
h_dimuon_m_fake_dummy.SetMaximum( 1.2 )

h_dimuon_m_fake_0 = ROOT.TH1F("h_dimuon_m_fake_0", "h_dimuon_m_fake_0", nBins, binMin, binMax)
h_dimuon_m_fake_0.SetLineColor(ROOT.kRed)
h_dimuon_m_fake_0.SetLineWidth(2)
h_dimuon_m_fake_0.SetLineStyle(1)


################################################################################
#                        mass of 2 selected dimuons                             
################################################################################

m_min  = 0.2113
m_max  = 3.5536
m_bins = 66

h_m1_vs_m2 = ROOT.TH2F("h_m1_vs_m2", "h_m1_vs_m2", m_bins, m_min, m_max, m_bins, m_min, m_max)
h_m1_vs_m2.SetYTitle("m_{1#mu#mu} [GeV]")
h_m1_vs_m2.SetTitleOffset(1.3, "Y")
h_m1_vs_m2.SetXTitle("m_{2#mu#mu} [GeV]")

h_m1 = ROOT.TH1F("h_m1", "h_m1", 101, 0.1, 10.1)
h_m1.SetLineColor(ROOT.kRed)
h_m1.SetLineWidth(2)
h_m1.SetLineStyle(1)

h_m2 = ROOT.TH1F("h_m2", "h_m2", 101, 0.1, 10.1)
h_m2.SetYTitle("Events / 0.1 GeV")
h_m2.SetXTitle("m_{#mu#mu} [GeV]")
h_m2.SetTitleOffset(1.35, "Y")
h_m2.SetLineColor(ROOT.kBlue)
h_m2.SetLineWidth(2)
h_m2.SetLineStyle(1)
h_m2.SetMaximum(110000)

h_dimuon_1_pT_dummy = ROOT.TH1F("h_dimuon_1_pT_dummy", "h_dimuon_1_pT_dummy", 100, 0, 100)
h_dimuon_1_pT_dummy.SetYTitle("Fraction of events / 1 GeV")
h_dimuon_1_pT_dummy.SetTitleOffset(1.35, "Y")
h_dimuon_1_pT_dummy.SetXTitle("p_{T} of #mu#mu [GeV]")
h_dimuon_1_pT_dummy.SetMaximum( 0.1 )

h_dimuon_1_pZ_dummy = ROOT.TH1F("h_dimuon_1_pZ_dummy", "h_dimuon_1_pZ_dummy", 100, 0, 100)
h_dimuon_1_pZ_dummy.SetYTitle("Fraction of events / 1 GeV")
h_dimuon_1_pZ_dummy.SetTitleOffset(1.35, "Y")
h_dimuon_1_pZ_dummy.SetXTitle("|p_{Z}| of #mu#mu [GeV]")
h_dimuon_1_pZ_dummy.SetMaximum( 0.1 )

h_dimuon_1_Eta_dummy = ROOT.TH1F("h_dimuon_1_Eta_dummy", "h_dimuon_1_Eta_dummy",100,-5,5) 
h_dimuon_1_Eta_dummy.SetYTitle("Fraction of events / 0.1")
h_dimuon_1_Eta_dummy.SetTitleOffset(1.35, "Y")
h_dimuon_1_Eta_dummy.SetXTitle("#eta of #mu#mu")
h_dimuon_1_Eta_dummy.SetMaximum( 0.1 )

h_dimuon_1_Phi_dummy = ROOT.TH1F("h_dimuon_1_Phi_dummy", "h_dimuon_1_Phi_dummy",80,-4,4 )
h_dimuon_1_Phi_dummy.SetYTitle("Fraction of events / 0.1 rad")
h_dimuon_1_Phi_dummy.SetTitleOffset(1.35, "Y")
h_dimuon_1_Phi_dummy.SetXTitle("#phi of #mu#mu [rad]")
h_dimuon_1_Phi_dummy.SetMaximum( 0.05 )

h_dimuon_1_p_dummy = ROOT.TH1F("h_dimuon_1_p_dummy", "h_dimuon_1_p_dummy", 100, 0, 100)
h_dimuon_1_p_dummy.SetYTitle("Fraction of events / 1 GeV")
h_dimuon_1_p_dummy.SetTitleOffset(1.35, "Y")
h_dimuon_1_p_dummy.SetXTitle("p of #mu#mu [GeV]")
h_dimuon_1_p_dummy.SetMaximum( 0.1 )

h_dimuon_1_M_dummy = ROOT.TH1F("h_dimuon_1_M_dummy", "h_dimuon_1_M_dummy", 50, 0.5, 10.005)
h_dimuon_1_M_dummy.SetYTitle("Fraction of events / 0.2 GeV")
h_dimuon_1_M_dummy.SetTitleOffset(1.35, "Y")
h_dimuon_1_M_dummy.SetXTitle("Mass of #mu#mu [GeV]")
h_dimuon_1_M_dummy.SetMaximum( 1.4 )

h_dimuon_1_p = ROOT.TH1F("h_dimuon_1_p", "h_dimuon_1_p", 100, 0, 100)
h_dimuon_1_p.SetLineColor(ROOT.kBlue)
h_dimuon_1_p.SetLineWidth(2)
h_dimuon_1_p.SetLineStyle(1)

h_dimuon_1_M = ROOT.TH1F("h_dimuon_1_M", "h_dimuon_1_M", 500, 0.005, 10.005)
h_dimuon_1_M.SetLineColor(ROOT.kBlue)
h_dimuon_1_M.SetLineWidth(2)
h_dimuon_1_M.SetLineStyle(1)

h_dimuon_1_pT = ROOT.TH1F("h_dimuon_1_pT", "h_dimuon_1_pT", 100, 0, 100)
h_dimuon_1_pT.SetLineColor(ROOT.kBlue)
h_dimuon_1_pT.SetLineWidth(2)
h_dimuon_1_pT.SetLineStyle(1)

h_dimuon_1_pZ = ROOT.TH1F("h_dimuon_1_pZ", "h_dimuon_1_pZ", 100, 0, 100)
h_dimuon_1_pZ.SetLineColor(ROOT.kBlue)
h_dimuon_1_pZ.SetLineWidth(2)
h_dimuon_1_pZ.SetLineStyle(1)

h_dimuon_1_Eta = ROOT.TH1F("h_dimuon_1_Eta", "h_dimuon_1_Eta",100,-5,5) 
h_dimuon_1_Eta.SetLineColor(ROOT.kBlue)
h_dimuon_1_Eta.SetLineWidth(2)
h_dimuon_1_Eta.SetLineStyle(1)

h_dimuon_1_Phi = ROOT.TH1F("h_dimuon_1_Phi", "h_dimuon_1_Phi", 80,-4,4)
h_dimuon_1_Phi.SetLineColor(ROOT.kBlue)
h_dimuon_1_Phi.SetLineWidth(2)
h_dimuon_1_Phi.SetLineStyle(1)

h_dimuon_2_p = ROOT.TH1F("h_dimuon_2_p", "h_dimuon_2_p", 100, 0, 100)
h_dimuon_2_p.SetLineColor(ROOT.kRed)
h_dimuon_2_p.SetLineWidth(2)
h_dimuon_2_p.SetLineStyle(1)

h_dimuon_2_pT = ROOT.TH1F("h_dimuon_2_pT", "h_dimuon_2_pT", 100, 0, 100)
h_dimuon_2_pT.SetLineColor(ROOT.kRed)
h_dimuon_2_pT.SetLineWidth(2)
h_dimuon_2_pT.SetLineStyle(1)

h_dimuon_2_pZ = ROOT.TH1F("h_dimuon_2_pZ", "h_dimuon_2_pZ", 100, 0, 100)
h_dimuon_2_pZ.SetLineColor(ROOT.kRed)
h_dimuon_2_pZ.SetLineWidth(2)
h_dimuon_2_pZ.SetLineStyle(1)

h_dimuon_2_Eta = ROOT.TH1F("h_dimuon_2_Eta", "h_dimuon_2_Eta", 100,-5,5)
h_dimuon_2_Eta.SetLineColor(ROOT.kRed)
h_dimuon_2_Eta.SetLineWidth(2)
h_dimuon_2_Eta.SetLineStyle(1)

h_dimuon_2_Phi = ROOT.TH1F("h_dimuon_2_Phi", "h_dimuon_2_Phi", 80,-4,4)
h_dimuon_2_Phi.SetLineColor(ROOT.kRed)
h_dimuon_2_Phi.SetLineWidth(2)
h_dimuon_2_Phi.SetLineStyle(1)



################################################################################
#                               BAM Functions                                
################################################################################
   
def plotOverflow(hist):
        name = hist.GetName()
        title = hist.GetTitle()
        nx = hist.GetNbinsX()+1
        x1 = hist.GetBinLowEdge(1)
        bw = hist.GetBinWidth(nx)
        x2 = hist.GetBinLowEdge(nx)+bw
        htmp = ROOT.TH1F(name, title, nx, x1, x2)

        for i in range(1, nx):
                htmp.Fill(htmp.GetBinCenter(i), hist.GetBinContent(i))

        htmp.Fill(hist.GetNbinsX()-1, hist.GetBinContent(0))
        htmp.SetEntries(hist.GetEntries())
        htmp.SetLineColor(hist.GetLineColor())
        htmp.SetLineWidth(hist.GetLineWidth())
        htmp.SetLineStyle(hist.GetLineStyle())
        htmp.DrawNormalized("same")
        return 

def integral(hist):
	eachBinWidth = hist.GetBinWidth(hist.GetNbinsX()+1)
	#print "Begin Integral"
	#print eachBinWidth
	runningSum = 0
	for i in range(0, hist.GetNbinsX()+1):
		area =  eachBinWidth * hist.GetBinContent(i)
		runningSum = runningSum + area
		
		#print i
		#print area

	return runningSum

def getEta(pz, p):
	output = atanh(pz/p)
	return output

def scaleAxisY(hist, dummy):
	normFactor =  hist.Integral()
	max = hist.GetBinContent(hist.GetMaximumBin()) / normFactor 
	scale = 1.8
	newMax = scale*max
	dummy.SetMaximum(newMax)

def scaleAxisYcT(hist, dummy):
	normFactor = integral(hist)
	max = hist.GetBinContent(hist.GetMaximumBin()) / normFactor
	scale = 1.8
	newMax = scale*max
	dummy.SetMaximum(newMax)

################################################################################
#                               Loop over events                                
################################################################################

nEvents = 0
isEvent = False
nEventsOK = 0
for line in f:
	if line == '<event>\n':
		isEvent           = True
		isEvent           = True
		nEvents           = nEvents + 1
		nLinesInEvent     = 0
		nParticlesInEvent = 0
		muons   = []
		dimuons = []
		DimuonIndex1 = []
		DimuonIndex2 = []
		bamDimuons = []
		FakeIndex1 = []
		FakeIndex2 = []
		FakeDimuons = []
		lifetimes = []
		higgs = []
		neutralinos = []
		darkNeutralinos = []
		gammaDs = []
		n1PlotCounter = 0
		gammaDPlotCounter = 0
		nDPlotCounter = 0
		if nEvents > nExit: break
		continue
	if line == '</event>\n':
		isEvent = False
		continue
	if isEvent == True:
		nLinesInEvent = nLinesInEvent + 1
		#***************************************************************************
		# first line with common event information                                  
		#***************************************************************************
		if nLinesInEvent == 1:
		  word_n = 0
#		  print "I", line
		  for word in line.split():
		    word_n = word_n + 1
		    if word_n == 1: NUP    = int(word)   # number of particles in the event
		    if word_n == 2: IDPRUP = int(word)   # process type
		    if word_n == 3: XWGTUP = float(word) # event weight
		    if word_n == 4: SCALUP = float(word) # factorization scale Q
		    if word_n == 5: AQEDUP = float(word) # the QED coupling alpha_em
		    if word_n == 6: AQCDUP = float(word) # the QCD coupling alpha_s
		  if word_n > 6: print "Warning! Wrong common event information", line
		#***************************************************************************
		# line with particle information                                            
		#***************************************************************************
		if nLinesInEvent >= 2:
		  nParticlesInEvent = nParticlesInEvent + 1
		  word_n = 0
#		  print "P", line
		  for word in line.split():
		    word_n = word_n + 1
		    if word_n ==  1: IDUP    = int(word)   # particle PDG identity code
		    if word_n ==  2: ISTUP   = int(word)   # status code
		    if word_n ==  3: MOTHUP1 = int(word)   # position of the first mother of particle
		    if word_n ==  4: MOTHUP2 = int(word)   # position of the last mother of particle
		    if word_n ==  5: ICOLUP1 = int(word)   # tag for the colour flow info
		    if word_n ==  6: ICOLUP2 = int(word)   # tag for the colour flow info
		    if word_n ==  7: PUP1    = float(word) # px in GeV
		    if word_n ==  8: PUP2    = float(word) # py in GeV
		    if word_n ==  9: PUP3    = float(word) # pz in GeV
		    if word_n == 10: PUP4    = float(word) # E in GeV
		    if word_n == 11: PUP5    = float(word) # m in GeV
		    if word_n == 12: VTIMUP  = float(word) # invariant lifetime ctau in mm
		    if word_n == 13: SPINUP  = float(word) # cosine of the angle between the spin vector of a particle and its three-momentum
		  if word_n > 13: print "Warning! Wrong particle line", line
		  
		  if abs(IDUP) == muonID:
		    if IDUP > 0: q = -1
		    if IDUP < 0: q  = 1
		    v4 = ROOT.TLorentzVector(PUP1, PUP2, PUP3, PUP4)
		    muons.append(( q, v4.Px(), v4.Py(), v4.Pz(), v4.E(), v4.M(), v4.Pt(), v4.Eta(), v4.Phi(), MOTHUP1 ))
		  if abs(IDUP) == higgsID:
		    if IDUP > 0: q = 0
		    if IDUP < 0: q = 0
		    vHiggs = ROOT.TLorentzVector(PUP1, PUP2, PUP3, PUP4)
		    higgs.append((q, vHiggs.Px(), vHiggs.Py(), vHiggs.Pz(), vHiggs.E(), vHiggs.M(), vHiggs.Pt(), vHiggs.Eta(), vHiggs.Phi() )) 
		    h_higgs_pT.Fill( higgs[len(higgs)-1][6] )
		    h_higgs_M.Fill( higgs[len(higgs)-1][5] )
		    h_higgs_p.Fill( sqrt( higgs[len(higgs)-1][1]*higgs[len(higgs)-1][1] + higgs[len(higgs)-1][2]*higgs[len(higgs)-1][2] + higgs[len(higgs)-1][3]*higgs[len(higgs)-1][3] ) )
		    h_higgs_pZ.Fill( fabs(higgs[len(higgs)-1][3])  ) 
		    #h_higgs_Eta.Fill( higgs[len(higgs)-1][7]  ) 
		    h_higgs_Phi.Fill( higgs[len(higgs)-1][8]  ) 
		  if abs(IDUP) == n1ID:
		    q = 0
		    vNeutralino = ROOT.TLorentzVector(PUP1, PUP2, PUP3, PUP4)
		    neutralinos.append((q, vNeutralino.Px(), vNeutralino.Py(), vNeutralino.Pz(), vNeutralino.E(), vNeutralino.M(), vNeutralino.Pt(), vNeutralino.Eta(), vNeutralino.Phi() ))

		  if len(neutralinos) == 2 and n1PlotCounter == 0:
		    neutralinos_sorted_pT = sorted(neutralinos, key=itemgetter(6), reverse=True)
		    neutralinos = neutralinos_sorted_pT
		    h_n1_1_pT.Fill( neutralinos[0][6] )
		    h_n1_2_pT.Fill( neutralinos[1][6] )
		    h_n1_1_p.Fill( sqrt( neutralinos[0][1]*neutralinos[0][1] + neutralinos[0][2]*neutralinos[0][2] + neutralinos[0][3]*neutralinos[0][3] )  )
		    h_n1_2_p.Fill( sqrt( neutralinos[1][1]*neutralinos[1][1] + neutralinos[1][2]*neutralinos[1][2] + neutralinos[1][3]*neutralinos[1][3] )  )
		    h_n1_1_M.Fill( neutralinos[0][5] )
		    h_n1_1_M.Fill( neutralinos[1][5] )
		    

	   	    h_n1_1_pZ.Fill( fabs(neutralinos[0][3]) )
		    h_n1_2_pZ.Fill( fabs(neutralinos[1][3]) )

	   	    h_n1_1_Eta.Fill( getEta(neutralinos[0][3],(sqrt( neutralinos[0][1]*neutralinos[0][1] + neutralinos[0][2]*neutralinos[0][2] + neutralinos[0][3]*neutralinos[0][3] ))) )
	   	    h_n1_1_Phi.Fill( neutralinos[0][8] )
		    h_n1_2_Eta.Fill( getEta(neutralinos[1][3], sqrt( neutralinos[1][1]*neutralinos[1][1] + neutralinos[1][2]*neutralinos[1][2] + neutralinos[1][3]*neutralinos[1][3] )) )
		    #print "PUP3, PZ, P, ETA:"
		    #print neutralinos[0][7]
		    #print neutralinos[0][3]
		    #print (sqrt( neutralinos[0][1]*neutralinos[0][1] + neutralinos[0][2]*neutralinos[0][2] + neutralinos[0][3]*neutralinos[0][3] ))
		    #print getEta(neutralinos[0][3],(sqrt( neutralinos[0][1]*neutralinos[0][1] + neutralinos[0][2]*neutralinos[0][2] + neutralinos[0][3]*neutralinos[0][3] )))
		    h_n1_2_Phi.Fill( neutralinos[1][8] )

		    n1PlotCounter = 1
		  if abs(IDUP) == nDID:
                    q = 0
                    vDarkNeutralino = ROOT.TLorentzVector(PUP1, PUP2, PUP3, PUP4)
                    darkNeutralinos.append((q, vDarkNeutralino.Px(), vDarkNeutralino.Py(), vDarkNeutralino.Pz(), vDarkNeutralino.E(), vDarkNeutralino.M(), vDarkNeutralino.Pt(), vDarkNeutralino.Eta(), vDarkNeutralino.Phi() ))

                  if len(darkNeutralinos) == 2 and nDPlotCounter == 0:
                    darkNeutralinos_sorted_pT = sorted(darkNeutralinos, key=itemgetter(6), reverse=True)
                    darkNeutralinos = darkNeutralinos_sorted_pT
                    h_nD_1_pT.Fill( darkNeutralinos[0][6] )
                    h_nD_2_pT.Fill( darkNeutralinos[1][6] )
                    h_nD_1_p.Fill( sqrt( darkNeutralinos[0][1]*darkNeutralinos[0][1] + darkNeutralinos[0][2]*darkNeutralinos[0][2] + darkNeutralinos[0][3]*darkNeutralinos[0][3] )  )
                    h_nD_2_p.Fill( sqrt( darkNeutralinos[1][1]*darkNeutralinos[1][1] + darkNeutralinos[1][2]*darkNeutralinos[1][2] + darkNeutralinos[1][3]*darkNeutralinos[1][3] )  )
                    h_nD_1_M.Fill( darkNeutralinos[0][5] )
                    h_nD_1_M.Fill( darkNeutralinos[1][5] ) 

		    h_nD_1_pZ.Fill( fabs(darkNeutralinos[0][3]) )
		    h_nD_2_pZ.Fill( fabs(darkNeutralinos[1][3]) )
		  
		    h_nD_1_Eta.Fill( getEta(darkNeutralinos[0][3], sqrt( darkNeutralinos[0][1]*darkNeutralinos[0][1] + darkNeutralinos[0][2]*darkNeutralinos[0][2] + darkNeutralinos[0][3]*darkNeutralinos[0][3] )) )
		    h_nD_1_Phi.Fill( darkNeutralinos[0][8] )
		    h_nD_2_Eta.Fill( getEta(darkNeutralinos[1][3], sqrt( darkNeutralinos[1][1]*darkNeutralinos[1][1] + darkNeutralinos[1][2]*darkNeutralinos[1
][2] + darkNeutralinos[1][3]*darkNeutralinos[1][3] )) )
		    h_nD_2_Phi.Fill( darkNeutralinos[1][8] )
	
		    vectorSum =( ( darkNeutralinos[0][1] + darkNeutralinos[1][1] )*( darkNeutralinos[0][1] + darkNeutralinos[1][1] ) ) + ( (darkNeutralinos[0][2] + darkNeutralinos[1][2])*(darkNeutralinos[0][2] + darkNeutralinos[1][2]) ) 
		    
		    Etmiss.Fill(vectorSum)


		    nDPlotCounter = 1
		  if abs(IDUP) == gammaDID:
		    q = 0
		    vgammaDs = ROOT.TLorentzVector(PUP1, PUP2, PUP3, PUP4)
		    gammaDs.append(( q, vgammaDs.Px(), vgammaDs.Py(), vgammaDs.Pz(), vgammaDs.E(), vgammaDs.M(), vgammaDs.Pt(), vgammaDs.Eta(), vgammaDs.Phi()))		
		    h_gammaD_cT.Fill( VTIMUP )

		    pmom = sqrt( vgammaDs.Px()*vgammaDs.Px() + vgammaDs.Py()*vgammaDs.Py() + vgammaDs.Pz()*vgammaDs.Pz()  )
		    beta = pmom/(sqrt(vgammaDs.M()*vgammaDs.M() + pmom*pmom ))
		    lorentz = 1/sqrt( 1 - beta*beta  )
		    
		    h_gammaD_cT_lab.Fill( lorentz*VTIMUP )

		    pmomxy = sqrt( vgammaDs.Px()*vgammaDs.Px() + vgammaDs.Py()*vgammaDs.Py()  )
		    betaxy = pmomxy/sqrt( vgammaDs.M()*vgammaDs.M() + pmomxy*pmomxy ) 
		    lorentzxy = 1/sqrt(1- betaxy*betaxy)
		    
		    h_gammaD_cT_XY_lab.Fill( lorentzxy*VTIMUP  )
		    
		    pmomz = sqrt( vgammaDs.Pz()*vgammaDs.Pz()  )
		    betaz = pmomz/sqrt( vgammaDs.M()*vgammaDs.M() + pmomz*pmomz  )
		    lorentzZ = 1/sqrt(1 - betaz*betaz  )
		    
		    h_gammaD_cT_Z_lab.Fill( lorentzZ * VTIMUP )


		    lifetimes.append( (VTIMUP, vgammaDs.Px(), vgammaDs.Py(), vgammaDs.Pz(), vgammaDs.Pt(), vgammaDs.M() ))

		  if len(gammaDs) == 2 and gammaDPlotCounter == 0:
		    gammaDs_sorted_pT = sorted(gammaDs, key=itemgetter(6), reverse=True)
		    gammaDs = gammaDs_sorted_pT

		    lifetimes_sorted_pT = sorted(lifetimes, key=itemgetter(4), reverse=True)
		    lifetimes = lifetimes_sorted_pT

		    h_gammaD_1_cT.Fill( lifetimes[0][0] )

                    pmom = sqrt( lifetimes[0][1]*lifetimes[0][1] + lifetimes[0][2]*lifetimes[0][2] + lifetimes[0][3]*lifetimes[0][3]  )
                    beta = pmom/(sqrt(lifetimes[0][5]*lifetimes[0][5] + pmom*pmom ))
                    lorentz = 1/sqrt( 1 - beta*beta  )

                    h_gammaD_1_cT_lab.Fill( lorentz*lifetimes[0][0] )

		    #print "pmom, beta, lorentz"
		    #print pmom
		    #print beta
		    #print lorentz
		    #print lorentz*lifetimes[0][0]

                    pmomxy = sqrt( lifetimes[0][1]*lifetimes[0][1] + lifetimes[0][2]*lifetimes[0][2]  )
                    betaxy = pmomxy/sqrt( lifetimes[0][5]*lifetimes[0][5] + pmomxy*pmomxy )
                    lorentzxy = 1/sqrt(1- betaxy*betaxy)

                    h_gammaD_1_cT_XY_lab.Fill( lorentzxy*lifetimes[0][0]  )

                    pmomz = sqrt( lifetimes[0][3]*lifetimes[0][3]  )
                    betaz = pmomz/sqrt( lifetimes[0][5]*lifetimes[0][5] + pmomz*pmomz  )
                    lorentzZ = 1/sqrt(1 - betaz*betaz  )
                    
                    h_gammaD_1_cT_Z_lab.Fill( lorentzZ * lifetimes[0][0] )

                    h_gammaD_2_cT.Fill( lifetimes[1][0] )

                    pmom = sqrt( lifetimes[1][1]*lifetimes[1][1] + lifetimes[1][2]*lifetimes[1][2] + lifetimes[1][3]*lifetimes[1][3]  )
                    beta = pmom/(sqrt(lifetimes[1][5]*lifetimes[1][5] + pmom*pmom ))
                    lorentz = 1/sqrt( 1 - beta*beta  )

                    h_gammaD_2_cT_lab.Fill( lorentz*lifetimes[1][0] )

                    pmomxy = sqrt( lifetimes[1][1]*lifetimes[1][1] + lifetimes[1][2]*lifetimes[1][2]  )
                    betaxy = pmomxy/sqrt( lifetimes[1][5]*lifetimes[1][5] + pmomxy*pmomxy )
                    lorentzxy = 1/sqrt(1- betaxy*betaxy)

                    h_gammaD_2_cT_XY_lab.Fill( lorentzxy*lifetimes[1][0]  )

                    pmomz = sqrt( lifetimes[1][3]*lifetimes[1][3]  )
                    betaz = pmomz/sqrt( lifetimes[1][5]*lifetimes[1][5] + pmomz*pmomz  )
                    lorentzZ = 1/sqrt(1 - betaz*betaz  )
                    
                    h_gammaD_2_cT_Z_lab.Fill( lorentzZ * lifetimes[1][0] )

 

		    h_gammaD_1_pT.Fill( gammaDs[0][6]  )
		    h_gammaD_2_pT.Fill( gammaDs[1][6]  )
		    h_gammaD_1_p.Fill( sqrt( gammaDs[0][1]*gammaDs[0][1] + gammaDs[0][2]*gammaDs[0][2] + gammaDs[0][3]*gammaDs[0][3] )  )
                    h_gammaD_2_p.Fill( sqrt( gammaDs[1][1]*gammaDs[1][1] + gammaDs[1][2]*gammaDs[1][2] + gammaDs[1][3]*gammaDs[1][3] )  )
                    h_gammaD_1_M.Fill( gammaDs[0][5] )
                    h_gammaD_1_M.Fill( gammaDs[1][5] )

		    h_gammaD_1_pZ.Fill( fabs(gammaDs[0][3]) )
		    h_gammaD_2_pZ.Fill( fabs(gammaDs[1][3]) )

		    h_gammaD_1_Eta.Fill( getEta(gammaDs[0][3],  sqrt( gammaDs[0][1]*gammaDs[0][1] + gammaDs[0][2]*gammaDs[0][2] + gammaDs[0][3]*gammaDs[0][3] )  ) )
		    h_gammaD_1_Phi.Fill( gammaDs[0][8] )
		    h_gammaD_2_Eta.Fill( getEta(gammaDs[1][3], sqrt( gammaDs[1][1]*gammaDs[1][1] + gammaDs[1][2]*gammaDs[1][2] + gammaDs[1][3]*gammaDs[1][3] ) ) )
		    h_gammaD_2_Phi.Fill( gammaDs[1][8] )
		   
		    gammaDPlotCounter = 1
		  if len(muons) == 4:
		    muons_sorted_pT = sorted(muons, key=itemgetter(6), reverse=True)
		    muons = muons_sorted_pT
		    
		    h_muon_pT_0.Fill( muons[0][6] )
		    h_muon_pT_1.Fill( muons[1][6] )
		    h_muon_pT_2.Fill( muons[2][6] )
		    h_muon_pT_3.Fill( muons[3][6] )
		    
		    h_muon_eta_0.Fill( muons[0][7] )
		    h_muon_eta_1.Fill( muons[1][7] )
		    h_muon_eta_2.Fill( muons[2][7] )
		    h_muon_eta_3.Fill( muons[3][7] )
		   
		    h_muon_phi_0.Fill( muons[0][8]  )  
		    h_muon_phi_1.Fill( muons[1][8]  )
 		    h_muon_phi_2.Fill( muons[2][8]  )
		    h_muon_phi_3.Fill( muons[3][8]  )
		   
                    h_muon_p_0.Fill( sqrt( muons[0][1]*muons[0][1] + muons[0][2]*muons[0][2] + muons[0][3]*muons[0][3] )  )
                    h_muon_p_1.Fill( sqrt( muons[1][1]*muons[1][1] + muons[1][2]*muons[1][2] + muons[1][3]*muons[1][3] )  )
                    h_muon_p_2.Fill( sqrt( muons[2][1]*muons[2][1] + muons[2][2]*muons[2][2] + muons[2][3]*muons[2][3] )  )
                    h_muon_p_3.Fill( sqrt( muons[3][1]*muons[3][1] + muons[3][2]*muons[3][2] + muons[3][3]*muons[3][3] )  )

                    h_muon_pZ_0.Fill( muons[0][3]  )
                    h_muon_pZ_1.Fill( muons[1][3]  )
                    h_muon_pZ_2.Fill( muons[2][3]  )
		    h_muon_pZ_3.Fill( muons[3][3]  )
                    


		    parent = muons[1][9] #this is an arbitrary choice to find real dimuons

		    for i in range(0, len(muons) ):
		     if parent == muons[i][9]: 
			DimuonIndex1.append(i)
		     else: 
			DimuonIndex2.append(i)

		    px1 = muons[DimuonIndex1[0]][1] + muons[DimuonIndex1[1]][1]
		    py1 = muons[DimuonIndex1[0]][2] + muons[DimuonIndex1[1]][2]
		    pz1 = muons[DimuonIndex1[0]][3] + muons[DimuonIndex1[1]][3]
		    e1  = muons[DimuonIndex1[0]][4] + muons[DimuonIndex1[1]][4]
		   
		    px2 = muons[DimuonIndex2[0]][1] + muons[DimuonIndex2[1]][1]
                    py2 = muons[DimuonIndex2[0]][2] + muons[DimuonIndex2[1]][2]
                    pz2 = muons[DimuonIndex2[0]][3] + muons[DimuonIndex2[1]][3]
                    e2  = muons[DimuonIndex2[0]][4] + muons[DimuonIndex2[1]][4] 

		    bamV4_1 = ROOT.TLorentzVector(px1, py1, pz1, e1)
		    bamV4_2 = ROOT.TLorentzVector(px2, py2, pz2, e2)
		    bamDimuons.append(( bamV4_1.Px(), bamV4_1.Py(), bamV4_1.Pz(), bamV4_1.E(), bamV4_1.M(), bamV4_1.Pt(), bamV4_1.Eta(), bamV4_1.Phi()  ))
		    bamDimuons.append(( bamV4_2.Px(), bamV4_2.Py(), bamV4_2.Pz(), bamV4_2.E(), bamV4_2.M(), bamV4_2.Pt(), bamV4_2.Eta(), bamV4_2.Phi()  ))

		    bamDimuons_Sorted_M = sorted(bamDimuons, key=itemgetter(4), reverse=True)
		    bamDimuons = bamDimuons_Sorted_M 

		    h_m1_vs_m2.Fill(bamDimuons[0][4],bamDimuons[1][4])
		    h_m1.Fill(bamDimuons[0][4])
		    h_m2.Fill(bamDimuons[1][4])

		    bamDimuons_Sorted_pT = sorted(bamDimuons, key=itemgetter(5), reverse=True)
                    bamDimuons = bamDimuons_Sorted_pT

		    h_dimuon_1_pT.Fill(bamDimuons[0][5]) 
		    h_dimuon_2_pT.Fill(bamDimuons[1][5])
		    
		    h_dimuon_1_pZ.Fill(bamDimuons[0][2]) 
		    h_dimuon_2_pZ.Fill(bamDimuons[1][2]) 
		    		    	
		    h_dimuon_1_p.Fill(sqrt( bamDimuons[0][0]*bamDimuons[0][0] + bamDimuons[0][1]*bamDimuons[0][1] + bamDimuons[0][2]*bamDimuons[0][2]  ))
		    h_dimuon_2_p.Fill(sqrt( bamDimuons[1][0]*bamDimuons[1][0] + bamDimuons[1][1]*bamDimuons[1][1] + bamDimuons[1][2]*bamDimuons[1][2]  ))
		    
		    h_dimuon_1_Eta.Fill(bamDimuons[0][6])
		    h_dimuon_2_Eta.Fill(bamDimuons[1][6])
		    
		    h_dimuon_1_Phi.Fill(bamDimuons[0][7])
		    h_dimuon_2_Phi.Fill(bamDimuons[1][7])

	            parent = muons[1][9] #this is an arbitrary choice to find the fake dimuons
		    charge = muons[1][0]
                    for i in range(0, len(muons) ):
                      if parent != muons[i][9] and charge != muons[i][0]:
                        FakeIndex1.append(i)
			FakeIndex1.append(1)

		    for j in range(0, len(muons) ):
		      if j != FakeIndex1[0] and j != FakeIndex1[1]:
		  	FakeIndex2.append(j)

                    Fakepx1 = muons[FakeIndex1[0]][1] + muons[FakeIndex1[1]][1]
                    Fakepy1 = muons[FakeIndex1[0]][2] + muons[FakeIndex1[1]][2]
                    Fakepz1 = muons[FakeIndex1[0]][3] + muons[FakeIndex1[1]][3]
                    Fakee1  = muons[FakeIndex1[0]][4] + muons[FakeIndex1[1]][4]
                    
		    Fakepx2 = muons[FakeIndex2[0]][1] + muons[FakeIndex2[1]][1]
                    Fakepy2 = muons[FakeIndex2[0]][2] + muons[FakeIndex2[1]][2]
                    Fakepz2 = muons[FakeIndex2[0]][3] + muons[FakeIndex2[1]][3]
                    Fakee2  = muons[FakeIndex2[0]][4] + muons[FakeIndex2[1]][4]
                    
                    fakeV4_1 = ROOT.TLorentzVector(Fakepx1, Fakepy1, Fakepz1, Fakee1)
                    fakeV4_2 = ROOT.TLorentzVector(Fakepx2, Fakepy2, Fakepz2, Fakee2)
    		    FakeDimuons.append(( fakeV4_1.Px(), fakeV4_1.Py(), fakeV4_1.Pz(), fakeV4_1.E(), fakeV4_1.M(), fakeV4_1.Pt(), fakeV4_1.Eta(), fakeV4_1.Phi()  ))
                    FakeDimuons.append(( fakeV4_2.Px(), fakeV4_2.Py(), fakeV4_2.Pz(), fakeV4_2.E(), fakeV4_2.M(), fakeV4_2.Pt(), fakeV4_2.Eta(), fakeV4_2.Phi()  ))

		    h_dimuon_m_fake_log_0.Fill(FakeDimuons[0][4])
		    h_dimuon_m_fake_log_0.Fill(FakeDimuons[1][4])
		    h_dimuon_m_fake_0.Fill(FakeDimuons[0][4])
		    h_dimuon_m_fake_0.Fill(FakeDimuons[1][4])



		   # is1SelMu17 = False
		   # for i in range(0, len(muons) ):
		   #   if muons[i][6] >= 17. and abs(muons[i][7]) <= 0.9: is1SelMu17 = True
		   # 
		   # is4SelMu8 = False
		   # nSelMu8   = 0
		   # for i in range(0, len(muons) ):
		   #   if muons[i][6] >= 8. and abs(muons[i][7]) <= 2.4: nSelMu8 = nSelMu8 + 1
		   # if nSelMu8 == 4: is4SelMu8 = True
		   # 
		   # if is1SelMu17 and is4SelMu8:
		   #   for i in range(0, len(muons) ):
		   #     for j in range(i+1, len(muons) ):
		   #       if muons[i][0] * muons[j][0] < 0:
		   #         px = muons[i][1] + muons[j][1]
		   #         py = muons[i][2] + muons[j][2]
		   #         pz = muons[i][3] + muons[j][3]
		   #         E  = muons[i][4] + muons[j][4]
		   #         v4 = ROOT.TLorentzVector(px, py, pz, E)
		   #         dimuons.append(( i, j, v4.Px(), v4.Py(), v4.Pz(), v4.E(), v4.M(), v4.Pt(), v4.Eta(), v4.Phi() ))
		   #   dimuons_sorted_M = sorted(dimuons, key=itemgetter(6), reverse=True)
		   #   dimuons = dimuons_sorted_M
#		   #   print "Dimuons:", dimuons
		   #   h_dimuon_m_0.Fill( dimuons[0][6] )
		   #   h_dimuon_m_1.Fill( dimuons[1][6] )
		   #   h_dimuon_m_2.Fill( dimuons[2][6] )
		   #   h_dimuon_m_3.Fill( dimuons[3][6] )
		   #  

		   #   h_dimuon_m_log_0.Fill( dimuons[0][6] )
                   #   h_dimuon_m_log_1.Fill( dimuons[1][6] )
                   #   h_dimuon_m_log_2.Fill( dimuons[2][6] )
                   #   h_dimuon_m_log_3.Fill( dimuons[3][6] ) 
		   #
		   #   #print dimuons[0][6]
		   #   #print float(mass_GammaD_Legend)
		   #   #if dimuons[0][6] >  float(mass_GammaD_Legend): print "fake"
		   #   #if dimuons[0][6] <= float(mass_GammaD_Legend): print "real" 
                   #   if dimuons[0][6] >  float(mass_GammaD_Legend): h_dimuon_m_real_fake_1.Fill(dimuons[0][6])
                   #   if dimuons[0][6] <= float(mass_GammaD_Legend): h_dimuon_m_real_fake_0.Fill(dimuons[0][6])
                   #   if dimuons[1][6] >  float(mass_GammaD_Legend): h_dimuon_m_real_fake_1.Fill(dimuons[1][6])
                   #   if dimuons[1][6] <= float(mass_GammaD_Legend): h_dimuon_m_real_fake_0.Fill(dimuons[1][6])
                   #   if dimuons[2][6] >  float(mass_GammaD_Legend): h_dimuon_m_real_fake_1.Fill(dimuons[2][6])
                   #   if dimuons[2][6] <= float(mass_GammaD_Legend): h_dimuon_m_real_fake_0.Fill(dimuons[2][6])
                   #   if dimuons[3][6] >  float(mass_GammaD_Legend): h_dimuon_m_real_fake_1.Fill(dimuons[3][6])
                   #   if dimuons[3][6] <= float(mass_GammaD_Legend): h_dimuon_m_real_fake_0.Fill(dimuons[3][6])
		   #   

		   #   if dimuons[0][6] >  float(mass_GammaD_Legend): h_dimuon_m_real_fake_log_1.Fill(dimuons[0][6])
                   #   if dimuons[0][6] <= float(mass_GammaD_Legend): h_dimuon_m_real_fake_log_0.Fill(dimuons[0][6])
                   #   if dimuons[1][6] >  float(mass_GammaD_Legend): h_dimuon_m_real_fake_log_1.Fill(dimuons[1][6])
                   #   if dimuons[1][6] <= float(mass_GammaD_Legend): h_dimuon_m_real_fake_log_0.Fill(dimuons[1][6])
                   #   if dimuons[2][6] >  float(mass_GammaD_Legend): h_dimuon_m_real_fake_log_1.Fill(dimuons[2][6])
                   #   if dimuons[2][6] <= float(mass_GammaD_Legend): h_dimuon_m_real_fake_log_0.Fill(dimuons[2][6])
                   #   if dimuons[3][6] >  float(mass_GammaD_Legend): h_dimuon_m_real_fake_log_1.Fill(dimuons[3][6])
                   #   if dimuons[3][6] <= float(mass_GammaD_Legend): h_dimuon_m_real_fake_log_0.Fill(dimuons[3][6]) 

		   #   dimuons5GeV = []
		   #   for i in range(0, len(dimuons)):
		   #     # select only dimuons with invariant mass less than 5 GeV
		   #     if dimuons[i][6] < 5.0: dimuons5GeV.append( dimuons[i] )
		   #   
		   #   nDimuons5GeV = len(dimuons5GeV)
		   #   
		   #   is2DiMuons           = False
		   #   nMuJetsContainMu17   = 0
		   #   m_threshold_Mu17_pT  = 17.0
		   #   m_threshold_Mu17_eta = 0.9
		   #   m_randomSeed         = 1234
		   #   if nDimuons5GeV == 2:
		   #     # select only dimuons that do NOT share muons
		   #     if dimuons5GeV[0][0] != dimuons5GeV[1][0] and dimuons5GeV[0][0] != dimuons5GeV[1][1] and dimuons5GeV[0][1] != dimuons5GeV[1][1] and dimuons5GeV[0][1] != dimuons5GeV[1][0]:
		   #       isDimuon0ContainMu17 = False
		   #       if ( muons[ dimuons5GeV[0][0] ][6] > m_threshold_Mu17_pT and muons[ dimuons5GeV[0][0] ][7] < m_threshold_Mu17_eta ) or ( muons[ dimuons5GeV[0][1] ][6] > m_threshold_Mu17_pT and muons[ dimuons5GeV[0][1] ][7] < m_threshold_Mu17_eta ):
		   #         isDimuon0ContainMu17 = True
		   #       if ( muons[ dimuons5GeV[1][0] ][6] > m_threshold_Mu17_pT and muons[ dimuons5GeV[1][0] ][7] < m_threshold_Mu17_eta ) or ( muons[ dimuons5GeV[1][1] ][6] > m_threshold_Mu17_pT and muons[ dimuons5GeV[1][1] ][7] < m_threshold_Mu17_eta ):
		   #         isDimuon1ContainMu17 = True
		   #       if isDimuon0ContainMu17 == True and isDimuon1ContainMu17 == False:
		   #         is2DiMuons = True
		   #         muJetC = dimuons5GeV[0]
		   #         muJetF = dimuons5GeV[1]
		   #       elif isDimuon0ContainMu17 == False and isDimuon1ContainMu17 == True:
		   #         is2DiMuons = True
		   #         muJetC = dimuons5GeV[1]
		   #         muJetF = dimuons5GeV[0]
		   #       elif isDimuon0ContainMu17 == True and isDimuon1ContainMu17 == True:
		   #         is2DiMuons = True
		   #         if(ROOT.TRandom3(m_randomSeed).Integer(2) == 0):
		   #           muJetC = dimuons5GeV[0]
		   #           muJetF = dimuons5GeV[1]
		   #         else:
		   #           muJetC = dimuons5GeV[1]
		   #           muJetF = dimuons5GeV[0]
		   #       else:
		   #         is2DiMuons = False
		   #   
		   #   is2DiMuonsMassOK = False
		   #   if is2DiMuons:
		   #     massC = muJetC[6]
		   #     massF = muJetF[6]
		   #     h_m1_vs_m2.Fill(massC, massF)
		   #     h_m1.Fill( massC )
		   #     h_m2.Fill( massF )
		   #     if abs(massC-massF) < (0.13 + 0.065*(massC+massF)/2.0):
		   #       is2DiMuonsMassOK = True
		   #   
		   #   if is2DiMuonsMassOK == True:
		   #     nEventsOK = nEventsOK + 1

print "nEvents   = ", nEvents
print "nEventsOK = ", nEventsOK

################################################################################
#                               Draw histograms                                 
################################################################################

Etmiss_dummy.Draw()
Etmiss.DrawNormalized("same")
scaleAxisY(Etmiss,Etmiss_dummy)
info.Draw()
txtHeader.Draw()
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_nD_EtMiss.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_nD_EtMiss.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_nD_EtMiss.C")

h_higgs_pT_dummy.Draw()
h_higgs_pT.DrawNormalized("same")
info.Draw()
txtHeader.Draw()
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_Higgs_pT.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_Higgs_pT.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_Higgs_pT.C")

h_higgs_pZ_dummy.Draw()
#h_higgs_pZ.DrawNormalized("same")
plotOverflow(h_higgs_pZ)
scaleAxisY(h_higgs_pZ,h_higgs_pZ_dummy)
info.Draw()
txtHeader.Draw()
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_Higgs_pZ.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_Higgs_pZ.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_Higgs_pZ.C")

#h_higgs_Eta_dummy.Draw()
#h_higgs_Eta.DrawNormalized("same")
#info.Draw()
#txtHeader.Draw()
#cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_Higgs_Eta.pdf")
#cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_Higgs_Eta.png")
#cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_Higgs_Eta.png")

h_higgs_Phi_dummy.Draw()
h_higgs_Phi.DrawNormalized("same")
#scaleAxisY(h_higgs_Phi,h_higgs_Phi_dummy)
info.Draw()
txtHeader.Draw()
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_Higgs_Phi.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_Higgs_Phi.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_Higgs_Phi.C")

cnv.SetLogx()
h_higgs_M_dummy.Draw()
h_higgs_M_dummy.SetNdivisions(10)
h_higgs_M_dummy.GetXaxis().SetMoreLogLabels()
h_higgs_M_dummy.Draw("same")
h_higgs_M.DrawNormalized("same")
h_higgs_M.GetXaxis().SetMoreLogLabels()
h_higgs_M.DrawNormalized("same")

info.Draw()
txtHeader.Draw()
h_higgs_M_dummy.SetNdivisions(10)
h_higgs_M_dummy.GetXaxis().SetMoreLogLabels()
h_higgs_M_dummy.Draw("same")
h_higgs_M.DrawNormalized("same")

cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_Higgs_m.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_Higgs_m.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_Higgs_m.C")
cnv.SetLogx(0)

h_higgs_p_dummy.Draw()
#h_higgs_p.DrawNormalized("same")
plotOverflow(h_higgs_p)
scaleAxisY(h_higgs_p,h_higgs_p_dummy)
info.Draw()
txtHeader.Draw()
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_Higgs_p.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_Higgs_p.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_Higgs_p.C")

h_n1_1_pT_dummy.Draw()
h_n1_1_pT.DrawNormalized("same")
h_n1_2_pT.DrawNormalized("same")
scaleAxisY(h_n1_1_pT, h_n1_1_pT_dummy)
legend = ROOT.TLegend(0.46,0.6744444,0.6955556,0.7644444)
legend.SetFillColor(ROOT.kWhite)
legend.SetFillStyle(0)
legend.SetBorderSize(0)
legend.SetTextFont(42)
legend.SetTextSize(0.02777778)
legend.SetMargin(0.13)
legend.AddEntry(h_n1_1_pT,"1st neutralino","L")
legend.AddEntry(h_n1_2_pT,"2nd neutralino","L")
legend.Draw()
info.Draw()
txtHeader.Draw()

cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_n1_pT.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_n1_pT.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_n1_pT.C")

h_n1_1_pZ_dummy.Draw()
plotOverflow(h_n1_1_pZ)
plotOverflow(h_n1_2_pZ)
scaleAxisY(h_n1_1_pZ,h_n1_1_pZ_dummy)
#h_n1_1_pZ.DrawNormalized("same")
#h_n1_2_pZ.DrawNormalized("same")

legend = ROOT.TLegend(0.46,0.6744444,0.6955556,0.7644444)
legend.SetFillColor(ROOT.kWhite)
legend.SetFillStyle(0)
legend.SetBorderSize(0)
legend.SetTextFont(42)
legend.SetTextSize(0.02777778)
legend.SetMargin(0.13)
legend.AddEntry(h_n1_1_pZ,"1st neutralino","L")
legend.AddEntry(h_n1_2_pZ,"2nd neutralino","L")
legend.Draw()
info.Draw()
txtHeader.Draw()

cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_n1_pZ.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_n1_pZ.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_n1_pZ.C")

h_n1_1_Eta_dummy.Draw()
h_n1_1_Eta.DrawNormalized("same")
h_n1_2_Eta.DrawNormalized("same")
scaleAxisY(h_n1_1_Eta,h_n1_1_Eta_dummy)

legend = ROOT.TLegend(0.46,0.6744444,0.6955556,0.7644444)
legend.SetFillColor(ROOT.kWhite)
legend.SetFillStyle(0)
legend.SetBorderSize(0)
legend.SetTextFont(42)
legend.SetTextSize(0.02777778)
legend.SetMargin(0.13)
legend.AddEntry(h_n1_1_Eta,"1st neutralino","L")
legend.AddEntry(h_n1_2_Eta,"2nd neutralino","L")
legend.Draw()
info.Draw()
txtHeader.Draw()

cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_n1_Eta.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_n1_Eta.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_n1_Eta.C")

h_n1_1_Phi_dummy.Draw()
h_n1_1_Phi.DrawNormalized("same")
h_n1_2_Phi.DrawNormalized("same")
scaleAxisY(h_n1_1_Phi,h_n1_1_Phi_dummy)
legend = ROOT.TLegend(0.46,0.6744444,0.6955556,0.7644444)
legend.SetFillColor(ROOT.kWhite)
legend.SetFillStyle(0)
legend.SetBorderSize(0)
legend.SetTextFont(42)
legend.SetTextSize(0.02777778)
legend.SetMargin(0.13)
legend.AddEntry(h_n1_1_Phi,"1st neutralino","L")
legend.AddEntry(h_n1_2_Phi,"2nd neutralino","L")
legend.Draw()
info.Draw()
txtHeader.Draw()

cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_n1_Phi.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_n1_Phi.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_n1_Phi.C")


h_n1_1_p_dummy.Draw()
plotOverflow(h_n1_1_p)
plotOverflow(h_n1_2_p)
scaleAxisY(h_n1_1_p,h_n1_1_p_dummy)
#h_n1_1_p.DrawNormalized("same")
#h_n1_2_p.DrawNormalized("same")

legend = ROOT.TLegend(0.46,0.6744444,0.6955556,0.7644444)
legend.SetFillColor(ROOT.kWhite)
legend.SetFillStyle(0)
legend.SetBorderSize(0)
legend.SetTextFont(42)
legend.SetTextSize(0.02777778)
legend.SetMargin(0.13)
legend.AddEntry(h_n1_1_p,"1st neutralino","L")
legend.AddEntry(h_n1_2_p,"2nd neutralino","L")
legend.Draw()
info.Draw()
txtHeader.Draw()

cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_n1_p.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_n1_p.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_n1_p.C")

h_n1_1_M_dummy.Draw()
h_n1_1_M.DrawNormalized("same")
#h_n1_2_M.DrawNormalized("same")

#legend = ROOT.TLegend(0.46,0.6744444,0.6955556,0.7644444)
#legend.SetFillColor(ROOT.kWhite)
#legend.SetFillStyle(0)
#legend.SetBorderSize(0)
#legend.SetTextFont(42)
#legend.SetTextSize(0.02777778)
#legend.SetMargin(0.13)
#legend.AddEntry(h_n1_1_M,"1st neutralino (leading p_{T})","L")
#legend.AddEntry(h_n1_2_M,"2nd neutralino","L")
#legend.Draw()
info.Draw()
txtHeader.Draw()

cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_n1_M.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_n1_M.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_n1_M.C")

h_nD_1_pT_dummy.Draw()
#h_nD_1_pT.DrawNormalized("same")
#h_nD_2_pT.DrawNormalized("same")
plotOverflow(h_nD_1_pT)
plotOverflow(h_nD_2_pT)
scaleAxisY(h_nD_2_pT,h_nD_1_pT)

legend = ROOT.TLegend(0.46,0.6744444,0.6955556,0.7644444)
legend.SetFillColor(ROOT.kWhite)
legend.SetFillStyle(0)
legend.SetBorderSize(0)
legend.SetTextFont(42)
legend.SetTextSize(0.02777778)
legend.SetMargin(0.13)
legend.AddEntry(h_nD_1_pT,"1st n_{D} (leading p_{T})","L")
legend.AddEntry(h_nD_2_pT,"2nd n_{D}","L")
legend.Draw()
info.Draw()
txtHeader.Draw()

cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_nD_pT.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_nD_pT.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_nD_pT.C")

h_nD_1_pZ_dummy.Draw()
h_nD_1_pZ.DrawNormalized("same")
h_nD_2_pZ.DrawNormalized("same")
scaleAxisY(h_nD_2_pZ,h_nD_1_pZ_dummy)

legend = ROOT.TLegend(0.46,0.6744444,0.6955556,0.7644444)
legend.SetFillColor(ROOT.kWhite)
legend.SetFillStyle(0)
legend.SetBorderSize(0)
legend.SetTextFont(42)
legend.SetTextSize(0.02777778)
legend.SetMargin(0.13)
legend.AddEntry(h_nD_1_pZ,"1st n_{D} (leading p_{T})","L")
legend.AddEntry(h_nD_2_pZ,"2nd n_{D}","L")
legend.Draw()
info.Draw()
txtHeader.Draw()

cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_nD_pZ.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_nD_pZ.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_nD_pZ.C")

h_nD_1_Eta_dummy.Draw()
h_nD_1_Eta.DrawNormalized("same")
h_nD_2_Eta.DrawNormalized("same")
scaleAxisY(h_nD_1_Eta,h_nD_1_Eta_dummy)

legend = ROOT.TLegend(0.46,0.6744444,0.6955556,0.7644444)
legend.SetFillColor(ROOT.kWhite)
legend.SetFillStyle(0)
legend.SetBorderSize(0)
legend.SetTextFont(42)
legend.SetTextSize(0.02777778)
legend.SetMargin(0.13)
legend.AddEntry(h_nD_1_Eta,"1st n_{D} (leading p_{T})","L")
legend.AddEntry(h_nD_2_Eta,"2nd n_{D}","L")
legend.Draw()
info.Draw()
txtHeader.Draw()

cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_nD_Eta.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_nD_Eta.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_nD_Eta.C")

h_nD_1_Phi_dummy.Draw()
h_nD_1_Phi.DrawNormalized("same")
h_nD_2_Phi.DrawNormalized("same")
scaleAxisY(h_nD_1_Phi,h_nD_1_Phi_dummy)

legend = ROOT.TLegend(0.46,0.6744444,0.6955556,0.7644444)
legend.SetFillColor(ROOT.kWhite)
legend.SetFillStyle(0)
legend.SetBorderSize(0)
legend.SetTextFont(42)
legend.SetTextSize(0.02777778)
legend.SetMargin(0.13)
legend.AddEntry(h_nD_1_Phi,"1st n_{D} (leading p_{T})","L")
legend.AddEntry(h_nD_2_Phi,"2nd n_{D}","L")
legend.Draw()
info.Draw()
txtHeader.Draw()

cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_nD_Phi.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_nD_Phi.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_nD_Phi.C")

h_nD_1_p_dummy.Draw()
h_nD_1_p.DrawNormalized("same")
h_nD_2_p.DrawNormalized("same")
scaleAxisY(h_nD_2_p,h_nD_1_p_dummy)

legend = ROOT.TLegend(0.46,0.6744444,0.6955556,0.7644444)
legend.SetFillColor(ROOT.kWhite)
legend.SetFillStyle(0)
legend.SetBorderSize(0)
legend.SetTextFont(42)
legend.SetTextSize(0.02777778)
legend.SetMargin(0.13)
legend.AddEntry(h_nD_1_p,"1st n_{D} (leading p_{T})","L")
legend.AddEntry(h_nD_2_p,"2nd n_{D}","L")
legend.Draw()
info.Draw()
txtHeader.Draw()

cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_nD_p.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_nD_p.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_nD_p.C")

h_nD_1_M_dummy.Draw()
h_nD_1_M.DrawNormalized("same")
#h_nD_2_M.DrawNormalized("same")

#legend = ROOT.TLegend(0.46,0.6744444,0.6955556,0.7644444)
#legend.SetFillColor(ROOT.kWhite)
#legend.SetFillStyle(0)
#legend.SetBorderSize(0)
#legend.SetTextFont(42)
#legend.SetTextSize(0.02777778)
#legend.SetMargin(0.13)
#legend.AddEntry(h_nD_1_M,"1st n_{D} (leading p_{T})","L")
#legend.AddEntry(h_nD_2_M,"2nd n_{D}","L")
#legend.Draw()
info.Draw()
txtHeader.Draw()

cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_nD_M.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_nD_M.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_nD_M.C")


h_gammaD_cT_dummy.Draw()
normConstant = integral(h_gammaD_cT)
#print normConstant
h_gammaD_cT.Scale(1/normConstant)
h_gammaD_cT.Draw("same")
scaleAxisYcT(h_gammaD_cT,h_gammaD_cT_dummy)

funct = ROOT.TF1("funct","exp(-x/"+ lifetime_GammaD_Legend +")/("+ lifetime_GammaD_Legend + "*(1 - exp(-" + str(cTlim) + "/" + lifetime_GammaD_Legend + ")))",cTlow,cTlim)
funct.SetNpx(10000)
funct.Draw("same")
h_gammaD_cT.SetTitleOffset(1.5, "Y")
h_gammaD_cT.SetXTitle("c#tau of #gamma_{D} [mm]")
h_gammaD_cT.SetYTitle("Normalized Fraction of events")
h_gammaD_cT.SetTitleSize(0.05,"Y")
info.Draw()
txtHeader.Draw()
eqn = ROOT.TLegend(0.46,0.6744444,0.6955556,0.7644444)
eqn.SetFillColor(ROOT.kWhite)
eqn.SetFillStyle(0)
eqn.SetBorderSize(0)
eqn.SetTextFont(42)
eqn.SetTextSize(0.02777778)
eqn.SetMargin(0.13)
eqn.AddEntry(funct, "#frac{e^{-x/"+ lifetime_GammaD_Legend +"}}{"+ lifetime_GammaD_Legend + " (1 - e^{-" + str(cTlim) + "/" + lifetime_GammaD_Legend + "})}", "L")
eqn.Draw()
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_cT.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_cT.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_cT.C")

h_gammaD_cT_lab_dummy.Draw()
normConstant = integral(h_gammaD_cT_lab)
h_gammaD_cT_lab.Scale(1/normConstant)
h_gammaD_cT_lab.Draw("same")
scaleAxisYcT(h_gammaD_cT_lab,h_gammaD_cT_lab_dummy)


#h_gammaD_cT_lab.DrawNormalized("same")
#myfit = ROOT.TF1("myfit", "[0]*exp(-x/[1])", 0, 10)
#myfit.SetParName(0,"C")
#myfit.SetParName(1,"L")
#myfit.SetParameter(0,1)
#myfit.SetParameter(1,1)
#h_gammaD_cT_lab.Fit("myfit").Draw("same")
h_gammaD_cT_lab.SetTitleOffset(1.5, "Y")
h_gammaD_cT_lab.SetXTitle("L of #gamma_{D} [mm]")
h_gammaD_cT_lab.SetYTitle("Events")
info.Draw()
txtHeader.Draw()
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_L.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_L.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_L.C")

h_gammaD_cT_XY_lab_dummy.Draw()
normConstant = integral(h_gammaD_cT_XY_lab)
h_gammaD_cT_XY_lab.Scale(1/normConstant)
h_gammaD_cT_XY_lab.Draw("same")
scaleAxisYcT(h_gammaD_cT_XY_lab,h_gammaD_cT_XY_lab_dummy)

#h_gammaD_cT_XY_lab.DrawNormalized("same")
#myfit = ROOT.TF1("myfit", "[0]*exp(-x/[1])", 0, 10)
#myfit.SetParName(0,"C")
#myfit.SetParName(1,"L_{xy}")
#myfit.SetParameter(0,1)
#myfit.SetParameter(1,1)
#h_gammaD_cT_XY_lab.Fit("myfit").Draw("same")
h_gammaD_cT_XY_lab.SetTitleOffset(1.5, "Y")
h_gammaD_cT_XY_lab.SetXTitle("L_{xy} of #gamma_{D} [mm]")
h_gammaD_cT_XY_lab.SetYTitle("Events")
info.Draw()
txtHeader.Draw()
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_L_XY.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_L_XY.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_L_XY.C")

h_gammaD_cT_Z_lab_dummy.Draw()
normConstant = integral(h_gammaD_cT_Z_lab)
h_gammaD_cT_Z_lab.Scale(1/normConstant)
h_gammaD_cT_Z_lab.Draw("same")
scaleAxisYcT(h_gammaD_cT_Z_lab,h_gammaD_cT_Z_lab_dummy)
#h_gammaD_cT_Z_lab.DrawNormalized("same")
#myfit = ROOT.TF1("myfit", "[0]*exp(-x/[1])", 0, 10)
#myfit.SetParName(0,"C")
#myfit.SetParName(1,"L_{z}")
#myfit.SetParameter(0,1)
#myfit.SetParameter(1,1)
#h_gammaD_cT_Z_lab.Fit("myfit").Draw("same")
h_gammaD_cT_Z_lab.SetTitleOffset(1.5, "Y")
h_gammaD_cT_Z_lab.SetXTitle("L_{z} of #gamma_{D} [mm]")
h_gammaD_cT_Z_lab.SetYTitle("Events")
info.Draw()
txtHeader.Draw()
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_L_Z.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_L_Z.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_L_Z.C")

h_gammaD_1_cT_dummy.Draw()
normConstant = integral(h_gammaD_1_cT)
h_gammaD_1_cT.Scale(1/normConstant)
h_gammaD_1_cT.Draw("same")
normConstant2 = integral(h_gammaD_2_cT)
h_gammaD_2_cT.Scale(1/normConstant2)
h_gammaD_2_cT.Draw("same")
scaleAxisYcT(h_gammaD_2_cT,h_gammaD_1_cT_dummy)

#h_gammaD_1_cT.DrawNormalized("same")
#h_gammaD_2_cT.DrawNormalized("same")
legend = ROOT.TLegend(0.46,0.6744444,0.6955556,0.7644444)
legend.SetFillColor(ROOT.kWhite)
legend.SetFillStyle(0)
legend.SetBorderSize(0)
legend.SetTextFont(42)
legend.SetTextSize(0.02777778)
legend.SetMargin(0.13)
legend.AddEntry(h_gammaD_1_cT,"1st dark photon (leading p_{T})","L")
legend.AddEntry(h_gammaD_2_cT,"2nd dark photon","L")
legend.Draw()
info.Draw()
txtHeader.Draw()
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_Sorted_cT.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_Sorted_cT.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_Sorted_cT.C")


h_gammaD_1_cT_lab_dummy.Draw()
normConstant = integral(h_gammaD_1_cT_lab)
h_gammaD_1_cT_lab.Scale(1/normConstant)
h_gammaD_1_cT_lab.Draw("same")
normConstant2 = integral(h_gammaD_2_cT_lab)
h_gammaD_2_cT_lab.Scale(1/normConstant2)
h_gammaD_2_cT_lab.Draw("same")
scaleAxisYcT(h_gammaD_2_cT_lab,h_gammaD_1_cT_lab_dummy)

#h_gammaD_1_cT_lab.DrawNormalized("same")
#h_gammaD_2_cT_lab.DrawNormalized("same")
legend = ROOT.TLegend(0.46,0.6744444,0.6955556,0.7644444)
legend.SetFillColor(ROOT.kWhite)
legend.SetFillStyle(0)
legend.SetBorderSize(0)
legend.SetTextFont(42)
legend.SetTextSize(0.02777778)
legend.SetMargin(0.13)
legend.AddEntry(h_gammaD_1_cT_lab,"1st dark photon (leading p_{T})","L")
legend.AddEntry(h_gammaD_2_cT_lab,"2nd dark photon","L")
legend.Draw()
info.Draw()
txtHeader.Draw()
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_Sorted_cT_lab.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_Sorted_cT_lab.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_Sorted_cT_lab.C")

h_gammaD_1_cT_XY_lab_dummy.Draw()

normConstant = integral(h_gammaD_1_cT_XY_lab)
h_gammaD_1_cT_XY_lab.Scale(1/normConstant)
h_gammaD_1_cT_XY_lab.Draw("same")
normConstant2 = integral(h_gammaD_2_cT_XY_lab)
h_gammaD_2_cT_XY_lab.Scale(1/normConstant2)
h_gammaD_2_cT_XY_lab.Draw("same")
scaleAxisYcT(h_gammaD_2_cT_XY_lab,h_gammaD_1_cT_XY_lab_dummy)

#h_gammaD_1_cT_XY_lab.DrawNormalized("same")
#h_gammaD_2_cT_XY_lab.DrawNormalized("same")
legend = ROOT.TLegend(0.46,0.6744444,0.6955556,0.7644444)
legend.SetFillColor(ROOT.kWhite)
legend.SetFillStyle(0)
legend.SetBorderSize(0)
legend.SetTextFont(42)
legend.SetTextSize(0.02777778)
legend.SetMargin(0.13)
legend.AddEntry(h_gammaD_1_cT_XY_lab,"1st dark photon (leading p_{T})","L")
legend.AddEntry(h_gammaD_2_cT_XY_lab,"2nd dark photon","L")
legend.Draw()
info.Draw()
txtHeader.Draw()
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_Sorted_cT_XY_lab.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_Sorted_cT_XY_lab.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_Sorted_cT_XY_lab.C")

h_gammaD_1_cT_Z_lab_dummy.Draw()
normConstant = integral(h_gammaD_1_cT_Z_lab)
h_gammaD_1_cT_Z_lab.Scale(1/normConstant)
h_gammaD_1_cT_Z_lab.Draw("same")
normConstant2 = integral(h_gammaD_2_cT_Z_lab)
h_gammaD_2_cT_Z_lab.Scale(1/normConstant2)
h_gammaD_2_cT_Z_lab.Draw("same")
scaleAxisYcT(h_gammaD_2_cT_Z_lab,h_gammaD_1_cT_Z_lab_dummy)

#h_gammaD_1_cT_Z_lab.DrawNormalized("same")
#h_gammaD_2_cT_Z_lab.DrawNormalized("same")
legend = ROOT.TLegend(0.46,0.6744444,0.6955556,0.7644444)
legend.SetFillColor(ROOT.kWhite)
legend.SetFillStyle(0)
legend.SetBorderSize(0)
legend.SetTextFont(42)
legend.SetTextSize(0.02777778)
legend.SetMargin(0.13)
legend.AddEntry(h_gammaD_1_cT_Z_lab,"1st dark photon (leading p_{T})","L")
legend.AddEntry(h_gammaD_2_cT_Z_lab,"2nd dark photon","L")
legend.Draw()
info.Draw()
txtHeader.Draw()
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_Sorted_cT_Z_lab.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_Sorted_cT_Z_lab.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_Sorted_cT_Z_lab.C")

h_gammaD_1_pT_dummy.Draw()
h_gammaD_1_pT.DrawNormalized("same")
h_gammaD_2_pT.DrawNormalized("same")
scaleAxisY(h_gammaD_2_pT,h_gammaD_1_pT_dummy)

legend = ROOT.TLegend(0.46,0.6744444,0.6955556,0.7644444)
legend.SetFillColor(ROOT.kWhite)
legend.SetFillStyle(0)
legend.SetBorderSize(0)
legend.SetTextFont(42)
legend.SetTextSize(0.02777778)
legend.SetMargin(0.13)
legend.AddEntry(h_gammaD_1_pT,"1st dark photon (leading p_{T})","L")
legend.AddEntry(h_gammaD_2_pT,"2nd dark photon","L")
legend.Draw()
info.Draw()
txtHeader.Draw()


cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_pT.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_pT.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_pT.C")

h_gammaD_1_pZ_dummy.Draw()
#plotOverflow(h_gammaD_1_pZ)
#plotOverflow(h_gammaD_2_pZ)
h_gammaD_1_pZ.DrawNormalized("same")
h_gammaD_2_pZ.DrawNormalized("same")
scaleAxisY(h_gammaD_2_pZ,h_gammaD_1_pZ_dummy)

#htmp = ROOT.TH1F(h_gammaD_1_pZ.GetName(),h_gammaD_1_pZ.GetTitle(), h_gammaD_1_pZ.GetNbinsX()+1, h_gammaD_1_pZ.GetBinLowEdge(1), h_gammaD_1_pZ.GetBinLowEdge(h_gammaD_1_pZ.GetNbinsX()+1)+h_gammaD_1_pZ.GetBinWidth(h_gammaD_1_pZ.GetNbinsX()+1))
#for i in range(1, h_gammaD_1_pZ.GetNbinsX()+1 ):
#	htmp.Fill(htmp.GetBinCenter(i), h_gammaD_1_pZ.GetBinContent(i)) 
#htmp.Fill(h_gammaD_1_pZ.GetNbinsX()-1, h_gammaD_1_pZ.GetBinContent(0))
#htmp.SetEntries(h_gammaD_1_pZ.GetEntries())
#htmp.SetLineColor(ROOT.kRed)
#htmp.DrawNormalized("same")
#htmp2 = ROOT.TH1F(h_gammaD_2_pZ.GetName(), h_gammaD_2_pZ.GetTitle(), h_gammaD_2_pZ.GetNbinsX()+1, h_gammaD_2_pZ.GetBinLowEdge(1), h_gammaD_2_pZ.GetBinLowEdge(h_gammaD_2_pZ.GetNbinsX()+1)+h_gammaD_2_pZ.GetBinWidth(h_gammaD_2_pZ.GetNbinsX()+1))
#for i in range(1, h_gammaD_2_pZ.GetNbinsX()+1 ):
#	htmp2.Fill(htmp2.GetBinCenter(i), h_gammaD_2_pZ.GetBinContent(i))
#htmp2.Fill(h_gammaD_2_pZ.GetNbinsX()-1, h_gammaD_2_pZ.GetBinContent(0))
#htmp2.SetEntries(h_gammaD_2_pZ.GetEntries())
#htmp2.SetLineColor(ROOT.kBlue)
#htmp2.DrawNormalized("same")
#h_gammaD_1_pZ.DrawNormalized("same")
#h_gammaD_2_pZ.DrawNormalized("same")

legend = ROOT.TLegend(0.46,0.6744444,0.6955556,0.7644444)
legend.SetFillColor(ROOT.kWhite)
legend.SetFillStyle(0)
legend.SetBorderSize(0)
legend.SetTextFont(42)
legend.SetTextSize(0.02777778)
legend.SetMargin(0.13)
legend.AddEntry(h_gammaD_1_pZ,"1st dark photon (leading p_{T})","L")
legend.AddEntry(h_gammaD_2_pZ,"2nd dark photon","L")
legend.Draw()
info.Draw()
txtHeader.Draw()

cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_pZ.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_pZ.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_pZ.C")

h_gammaD_1_Eta_dummy.Draw()
h_gammaD_1_Eta.DrawNormalized("same")
h_gammaD_2_Eta.DrawNormalized("same")
scaleAxisY(h_gammaD_1_Eta,h_gammaD_1_Eta_dummy)

legend = ROOT.TLegend(0.46,0.6744444,0.6955556,0.7644444)
legend.SetFillColor(ROOT.kWhite)
legend.SetFillStyle(0)
legend.SetBorderSize(0)
legend.SetTextFont(42)
legend.SetTextSize(0.02777778)
legend.SetMargin(0.13)
legend.AddEntry(h_gammaD_1_Eta,"1st dark photon (leading p_{T})","L")
legend.AddEntry(h_gammaD_2_Eta,"2nd dark photon","L")
legend.Draw()
info.Draw()
txtHeader.Draw()


cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_Eta.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_Eta.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_Eta.C")

h_gammaD_1_Phi_dummy.Draw()
h_gammaD_1_Phi.DrawNormalized("same")
h_gammaD_2_Phi.DrawNormalized("same")
scaleAxisY(h_gammaD_1_Phi,h_gammaD_1_Phi_dummy)

legend = ROOT.TLegend(0.46,0.6744444,0.6955556,0.7644444)
legend.SetFillColor(ROOT.kWhite)
legend.SetFillStyle(0)
legend.SetBorderSize(0)
legend.SetTextFont(42)
legend.SetTextSize(0.02777778)
legend.SetMargin(0.13)
legend.AddEntry(h_gammaD_1_Phi,"1st dark photon (leading p_{T})","L")
legend.AddEntry(h_gammaD_2_Phi,"2nd dark photon","L")
legend.Draw()
info.Draw()
txtHeader.Draw()


cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_Phi.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_Phi.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_Phi.C")

h_gammaD_1_p_dummy.Draw()
plotOverflow(h_gammaD_1_p)
plotOverflow(h_gammaD_2_p)
scaleAxisY(h_gammaD_2_p,h_gammaD_1_p_dummy)
#h_gammaD_1_p.DrawNormalized("same")
#h_gammaD_2_p.DrawNormalized("same")

legend = ROOT.TLegend(0.46,0.6744444,0.6955556,0.7644444)
legend.SetFillColor(ROOT.kWhite)
legend.SetFillStyle(0)
legend.SetBorderSize(0)
legend.SetTextFont(42)
legend.SetTextSize(0.02777778)
legend.SetMargin(0.13)
legend.AddEntry(h_gammaD_1_p,"1st dark photon (leading p_{T})","L")
legend.AddEntry(h_gammaD_2_p,"2nd dark photon","L")
legend.Draw()
info.Draw()
txtHeader.Draw()

cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_p.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_p.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_p.C")

h_gammaD_1_M_dummy.Draw()
cnv.SetLogx()
h_gammaD_1_M.DrawNormalized("same")
#h_gammaD_2_M.DrawNormalized("same")

#legend = ROOT.TLegend(0.46,0.6744444,0.6955556,0.7644444)
#legend.SetFillColor(ROOT.kWhite)
#legend.SetFillStyle(0)
#legend.SetBorderSize(0)
#legend.SetTextFont(42)
#legend.SetTextSize(0.02777778)
#legend.SetMargin(0.13)
#legend.AddEntry(h_gammaD_1_M,"1st dark photon (leading p_{T})","L")
#legend.AddEntry(h_gammaD_2_M,"2nd dark photon","L")
#legend.Draw()
info.Draw()
txtHeader.Draw()

cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_M.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_M.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_gammaD_M.C")
cnv.SetLogx(0)

h_muon_pT_dummy.Draw()
h_muon_pT_0.DrawNormalized("same")
h_muon_pT_1.DrawNormalized("same")
h_muon_pT_2.DrawNormalized("same")
h_muon_pT_3.DrawNormalized("same")
scaleAxisY(h_muon_pT_3,h_muon_pT_dummy)

legend = ROOT.TLegend(0.6175166,0.6730435,0.9429047,0.7626087)
legend.SetFillColor(ROOT.kWhite)
legend.SetFillStyle(0)
legend.SetBorderSize(0)
legend.SetTextFont(42)
legend.SetTextSize(0.02777778)
legend.SetMargin(0.13)
legend.AddEntry(h_muon_pT_0,"1st muon (leading p_{T})","L")
legend.AddEntry(h_muon_pT_1,"2nd muon","L")
legend.AddEntry(h_muon_pT_2,"3rd muon","L")
legend.AddEntry(h_muon_pT_3,"4th muon","L")
legend.Draw()
info.Draw()
txtHeader.Draw()

cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_muon_pT.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_muon_pT.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_muon_pT.C")

h_muon_phi_dummy.Draw()
h_muon_phi_0.DrawNormalized("same")
h_muon_phi_1.DrawNormalized("same")
h_muon_phi_2.DrawNormalized("same")
h_muon_phi_3.DrawNormalized("same")
scaleAxisY(h_muon_phi_0,h_muon_phi_dummy)

legend = ROOT.TLegend(0.6175166,0.6730435,0.9429047,0.7626087)
legend.SetFillColor(ROOT.kWhite)
legend.SetFillStyle(0)
legend.SetBorderSize(0)
legend.SetTextFont(42)
legend.SetTextSize(0.02777778)
legend.SetMargin(0.13)
legend.AddEntry(h_muon_phi_0,"1st muon (leading p_{T})","L")
legend.AddEntry(h_muon_phi_1,"2nd muon","L")
legend.AddEntry(h_muon_phi_2,"3rd muon","L")
legend.AddEntry(h_muon_phi_3,"4th muon","L")
legend.Draw()
info.Draw()
txtHeader.Draw()

cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_muon_phi.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_muon_phi.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_muon_phi.C")

h_muon_pZ_dummy.Draw()
h_muon_pZ_0.DrawNormalized("same")
h_muon_pZ_1.DrawNormalized("same")
h_muon_pZ_2.DrawNormalized("same")
h_muon_pZ_3.DrawNormalized("same")
scaleAxisY(h_muon_pZ_3,h_muon_pZ_dummy)

legend = ROOT.TLegend(0.6175166,0.6730435,0.9429047,0.7626087)
legend.SetFillColor(ROOT.kWhite)
legend.SetFillStyle(0)
legend.SetBorderSize(0)
legend.SetTextFont(42)
legend.SetTextSize(0.02777778)
legend.SetMargin(0.13)
legend.AddEntry(h_muon_pZ_0,"1st muon (leading p_{T})","L")
legend.AddEntry(h_muon_pZ_1,"2nd muon","L")
legend.AddEntry(h_muon_pZ_2,"3rd muon","L")
legend.AddEntry(h_muon_pZ_3,"4th muon","L")
legend.Draw()
info.Draw()
txtHeader.Draw()

cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_muon_pZ.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_muon_pZ.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_muon_pZ.C")

h_muon_p_dummy.Draw()
h_muon_p_0.DrawNormalized("same")
h_muon_p_1.DrawNormalized("same")
h_muon_p_2.DrawNormalized("same")
h_muon_p_3.DrawNormalized("same")
scaleAxisY(h_muon_p_3,h_muon_p_dummy)

legend = ROOT.TLegend(0.6175166,0.6730435,0.9429047,0.7626087)
legend.SetFillColor(ROOT.kWhite)
legend.SetFillStyle(0)
legend.SetBorderSize(0)
legend.SetTextFont(42)
legend.SetTextSize(0.02777778)
legend.SetMargin(0.13)
legend.AddEntry(h_muon_p_0,"1st muon (leading p_{T})","L")
legend.AddEntry(h_muon_p_1,"2nd muon","L")
legend.AddEntry(h_muon_p_2,"3rd muon","L")
legend.AddEntry(h_muon_p_3,"4th muon","L")
legend.Draw()
info.Draw()
txtHeader.Draw()

cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_muon_p.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_muon_p.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_muon_p.C")


h_muon_eta_dummy.Draw()
h_muon_eta_0.DrawNormalized("same")
h_muon_eta_1.DrawNormalized("same")
h_muon_eta_2.DrawNormalized("same")
h_muon_eta_3.DrawNormalized("same")
scaleAxisY(h_muon_eta_0,h_muon_eta_dummy)

legend = ROOT.TLegend(0.6175166,0.6730435,0.9429047,0.7626087)
legend.SetFillColor(ROOT.kWhite)
legend.SetFillStyle(0)
legend.SetBorderSize(0)
legend.SetTextFont(42)
legend.SetTextSize(0.02777778)
legend.SetMargin(0.13)
legend.AddEntry(h_muon_eta_0,"1st muon (leading p_{T})","L")
legend.AddEntry(h_muon_eta_1,"2nd muon","L")
legend.AddEntry(h_muon_eta_2,"3rd muon","L")
legend.AddEntry(h_muon_eta_3,"4th muon","L")
legend.Draw()
info.Draw()
txtHeader.Draw()

cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_muon_eta.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_muon_eta.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_muon_eta.C")

#h_dimuon_m_dummy.Draw()
#h_dimuon_m_0.DrawNormalized("same")
#h_dimuon_m_1.DrawNormalized("same")
#h_dimuon_m_2.DrawNormalized("same")
#h_dimuon_m_3.DrawNormalized("same")
#
#legend = ROOT.TLegend(0.6175166,0.6730435,0.9429047,0.7626087)
#legend.SetFillColor(ROOT.kWhite)
#legend.SetFillStyle(0)
#legend.SetBorderSize(0)
#legend.SetTextFont(42)
#legend.SetTextSize(0.02777778)
#legend.SetMargin(0.13)
#legend.AddEntry(h_dimuon_m_0,"1st dimuon (leading m_{#mu#mu})","L")
#legend.AddEntry(h_dimuon_m_1,"2nd dimuon","L")
#legend.AddEntry(h_dimuon_m_2,"3rd dimuon","L")
#legend.AddEntry(h_dimuon_m_3,"4th dimuon","L")
#legend.Draw()
#info.Draw()
#txtHeader.Draw()
#cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_dimuon_m.pdf")
#cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_dimuon_m.png")
## convert -define.pdf:use-cropbox=true -density 300 CSxBR_vs_mh.pdf -resize 900x900 CSxBR_vs_mh.png
#
#h_dimuon_m_log_dummy.Draw()
#cnv.SetLogy()
#h_dimuon_m_log_0.DrawNormalized("same")
#h_dimuon_m_log_1.DrawNormalized("same")
#h_dimuon_m_log_2.DrawNormalized("same")
#h_dimuon_m_log_3.DrawNormalized("same")
#
#legend = ROOT.TLegend(0.6175166,0.6730435,0.9429047,0.7626087)
#legend.SetFillColor(ROOT.kWhite)
#legend.SetFillStyle(0)
#legend.SetBorderSize(0)
#legend.SetTextFont(42)
#legend.SetTextSize(0.02777778)
#legend.SetMargin(0.13)
#legend.AddEntry(h_dimuon_m_log_0,"1st dimuon (leading m_{#mu#mu})","L")
#legend.AddEntry(h_dimuon_m_log_1,"2nd dimuon","L")
#legend.AddEntry(h_dimuon_m_log_2,"3rd dimuon","L")
#legend.AddEntry(h_dimuon_m_log_3,"4th dimuon","L")
#legend.Draw()
#info.Draw()
#txtHeader.Draw()
#
#cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_dimuon_m_log.pdf")
#cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_dimuon_m_log.png")
#cnv.SetLogy(0)
#
#h_dimuon_m_real_fake_dummy.Draw()
#h_dimuon_m_real_fake_0.DrawNormalized("same")
#h_dimuon_m_real_fake_1.DrawNormalized("same")
#
#legend = ROOT.TLegend(0.46,0.6744444,0.6955556,0.7644444)
#legend.SetFillColor(ROOT.kWhite)
#legend.SetFillStyle(0)
#legend.SetBorderSize(0)
#legend.SetTextFont(42)
#legend.SetTextSize(0.02777778)
#legend.SetMargin(0.13)
#legend.AddEntry(h_dimuon_m_real_fake_0,"Real dimuons","L")
#legend.AddEntry(h_dimuon_m_real_fake_1,"Fake dimuons","L")
#legend.Draw()
#info.Draw()
#txtHeader.Draw()
#
#cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_dimuon_m_real_fake.pdf")
#cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_dimuon_m_real_fake.png")
#
#h_dimuon_m_real_fake_log_dummy.Draw()
#cnv.SetLogy()
#h_dimuon_m_real_fake_log_0.DrawNormalized("same")
#h_dimuon_m_real_fake_log_1.DrawNormalized("same")
#legend = ROOT.TLegend(0.46,0.6744444,0.6955556,0.7644444)
#legend.SetFillColor(ROOT.kWhite)
#legend.SetFillStyle(0)
#legend.SetBorderSize(0)
#legend.SetTextFont(42)
#legend.SetTextSize(0.02777778)
#legend.SetMargin(0.13)
#legend.AddEntry(h_dimuon_m_real_fake_log_0,"Real dimuons","L")
#legend.AddEntry(h_dimuon_m_real_fake_log_1,"Fake dimuons","L")
#legend.Draw()
#info.Draw()
#txtHeader.Draw()
#
#cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_dimuon_m_real_fake_log.pdf")
#cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_dimuon_m_real_fake_log.png")
cnv.SetLogy(0)

h_m1_vs_m2.Draw()
info.Draw()
txtHeader.Draw()
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_dimuon_m1_vs_m2.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_dimuon_m1_vs_m2.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_dimuon_m1_vs_m2.C")

cnv.SetLogx()
h_m2.Draw()
h_m1.Draw("same")
info.Draw()
txtHeader.Draw()
txtHeader.Draw()
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_dimuon_m.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_dimuon_m.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_dimuon_m.C")
cnv.SetLogx(0)

h_dimuon_m_fake_dummy.Draw()
h_dimuon_m_fake_0.DrawNormalized("same")
scaleAxisY(h_dimuon_m_fake_0,h_dimuon_m_fake_dummy)

info.Draw()
txtHeader.Draw()

cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_dimuon_m_fake.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_dimuon_m_fake.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_dimuon_m_fake.C")

h_dimuon_m_fake_log_dummy.Draw()
cnv.SetLogy()
cnv.SetLogx()
h_dimuon_m_fake_log_0.DrawNormalized("same")
#scaleAxisY(h_dimuon_m_fake_log_0,h_dimuon_m_fake_log_dummy)

info.Draw()
txtHeader.Draw()

cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_dimuon_m_fake_log.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_dimuon_m_fake_log.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_dimuon_m_fake_log.C")
cnv.SetLogy(0)
cnv.SetLogx(0)

h_dimuon_1_pT_dummy.Draw()
h_dimuon_1_pT.DrawNormalized("same")
h_dimuon_2_pT.DrawNormalized("same")
scaleAxisY(h_dimuon_2_pT,h_dimuon_1_pT_dummy)

legend = ROOT.TLegend(0.46,0.6744444,0.6955556,0.7644444)
legend.SetFillColor(ROOT.kWhite)
legend.SetFillStyle(0)
legend.SetBorderSize(0)
legend.SetTextFont(42)
legend.SetTextSize(0.02777778)
legend.SetMargin(0.13)
legend.AddEntry(h_dimuon_1_pT,"1st #mu#mu (leading p_{T})","L")
legend.AddEntry(h_dimuon_2_pT,"2nd #mu#mu","L")
legend.Draw()
info.Draw()
txtHeader.Draw()


cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_dimuon_pT.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_dimuon_pT.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_dimuon_pT.C")

h_dimuon_1_pZ_dummy.Draw()
#plotOverflow(h_dimuon_1_pZ)
#plotOverflow(h_dimuon_2_pZ)
h_dimuon_1_pZ.DrawNormalized("same")
h_dimuon_2_pZ.DrawNormalized("same")
scaleAxisY(h_dimuon_2_pZ,h_dimuon_1_pZ_dummy)

legend = ROOT.TLegend(0.46,0.6744444,0.6955556,0.7644444)
legend.SetFillColor(ROOT.kWhite)
legend.SetFillStyle(0)
legend.SetBorderSize(0)
legend.SetTextFont(42)
legend.SetTextSize(0.02777778)
legend.SetMargin(0.13)
legend.AddEntry(h_dimuon_1_pZ,"1st #mu#mu (leading p_{T})","L")
legend.AddEntry(h_dimuon_2_pZ,"2nd #mu#mu","L")
legend.Draw()
info.Draw()
txtHeader.Draw()

cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_dimuon_pZ.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_dimuon_pZ.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_dimuon_pZ.C")

h_dimuon_1_Eta_dummy.Draw()
h_dimuon_1_Eta.DrawNormalized("same")
h_dimuon_2_Eta.DrawNormalized("same")
scaleAxisY(h_dimuon_1_Eta,h_dimuon_1_Eta_dummy)

legend = ROOT.TLegend(0.46,0.6744444,0.6955556,0.7644444)
legend.SetFillColor(ROOT.kWhite)
legend.SetFillStyle(0)
legend.SetBorderSize(0)
legend.SetTextFont(42)
legend.SetTextSize(0.02777778)
legend.SetMargin(0.13)
legend.AddEntry(h_dimuon_1_Eta,"1st #mu#mu (leading p_{T})","L")
legend.AddEntry(h_dimuon_2_Eta,"2nd #mu#mu","L")
legend.Draw()
info.Draw()
txtHeader.Draw()


cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_dimuon_Eta.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_dimuon_Eta.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_dimuon_Eta.C")

h_dimuon_1_Phi_dummy.Draw()
h_dimuon_1_Phi.DrawNormalized("same")
h_dimuon_2_Phi.DrawNormalized("same")
scaleAxisY(h_dimuon_1_Phi,h_dimuon_1_Phi_dummy)

legend = ROOT.TLegend(0.46,0.6744444,0.6955556,0.7644444)
legend.SetFillColor(ROOT.kWhite)
legend.SetFillStyle(0)
legend.SetBorderSize(0)
legend.SetTextFont(42)
legend.SetTextSize(0.02777778)
legend.SetMargin(0.13)
legend.AddEntry(h_dimuon_1_Phi,"1st #mu#mu (leading p_{T})","L")
legend.AddEntry(h_dimuon_2_Phi,"2nd #mu#mu","L")
legend.Draw()
info.Draw()
txtHeader.Draw()


cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_dimuon_Phi.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_dimuon_Phi.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_dimuon_Phi.C")

h_dimuon_1_p_dummy.Draw()
plotOverflow(h_dimuon_1_p)
plotOverflow(h_dimuon_2_p)
scaleAxisY(h_dimuon_2_p,h_dimuon_1_p_dummy)

legend = ROOT.TLegend(0.46,0.6744444,0.6955556,0.7644444)
legend.SetFillColor(ROOT.kWhite)
legend.SetFillStyle(0)
legend.SetBorderSize(0)
legend.SetTextFont(42)
legend.SetTextSize(0.02777778)
legend.SetMargin(0.13)
legend.AddEntry(h_dimuon_1_p,"1st #mu#mu (leading p_{T})","L")
legend.AddEntry(h_dimuon_2_p,"2nd #mu#mu","L")
legend.Draw()
info.Draw()
txtHeader.Draw()

cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_dimuon_p.pdf")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_dimuon_p.png")
cnv.SaveAs("DarkSusy_mH_125_mGammaD_" + mass_GammaD + "_cT_"+ lifetime_GammaD + "_LHE_dimuon_p.C")

BAM.Write()
print "Made it to the end and closes"

f.close()
