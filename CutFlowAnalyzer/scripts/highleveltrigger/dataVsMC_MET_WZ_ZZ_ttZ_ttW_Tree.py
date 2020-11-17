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

def getPT(m1):
    px = m1[1]
    py = m1[2]
    return m.sqrt(px*px + py*py)

def getPhi(m1):
    return m1[4]

def normalizePhi(result):
    while (result > M_PI):
        result -= 2*M_PI;
    while (result <= -M_PI):
        result += 2*M_PI;
    return result

## total energy of the muon
def energy(mmu, px, py, pz):
    return m.sqrt(mmu*mmu + px*px + py*py + pz*pz)

## dimuon invariant mass
def inner(m1, m2):
    return m1[0] * m2[0] - m1[1] * m2[1] - m1[2] * m2[2] - m1[3] * m2[3]

def invmass(m1, m2):
    a = inner(m1,m1)
    b = inner(m2,m2)
    c = 2*inner(m1,m2)
    return m.sqrt(a+b+c)

def inv3mass(m1, m2, m3):
    a = inner(m1,m1)
    b = inner(m2,m2)
    c = inner(m3,m3)
    d = 2*inner(m1,m2)
    e = 2*inner(m1,m3)
    f = 2*inner(m2,m3)
    return m.sqrt(a+b+c+d+e+f)

def isMassInZPeak(m):
    return abs(m-mZ)<15

def bestMassInZPeak(m1, m2, m3):
    masses = [m1, m2, m3]
    massdiffs = [abs(m1-mZ), abs(m2-mZ), abs(m3-mZ)]
    index = massdiffs.index(min(massdiffs))
    return masses[index]

def bestMassInZPeak(m1, m2):
    masses = [m1, m2]
    massdiffs = [abs(m1-mZ), abs(m2-mZ)]
    index = massdiffs.index(min(massdiffs))
    return masses[index]

datasets = ['WZTo3LNu', 'ZZTo4Mu','TTWJetsToLNu', 'TTZJetsToLNu', 'METData']

dataFiles = {}
dataFiles['WZTo3LNu'] = [
]
dataFiles['TTWJetsToLNu'] = [
]
dataFiles['TTZJetsToLNu'] = [
]
"""
dataFiles['ZZTo4Mu'] = [
]
dataFiles['METData'] = [
]
"""


## define each chain for plotting purposes
file_WZ = TFile("datafiles/out_ana_clone_WZ_2018.root")
chain_WZ = file_WZ.Get("Events")

file_TTZ = TFile("datafiles/out_ana_clone_TTZ_2018.root")
chain_TTZ = file_TTZ.Get("Events")

file_Data = TFile("datafiles/out_ana_clone_MET_2018.root")
chain_Data = file_Data.Get("Events")

#ROOT.TChain("Events")
#addfilesMany(chain_WZ, dataFiles['WZTo3LNu'], "out_ana_clone")

#chain_TTW = ROOT.TChain("Events")
#addfilesMany(chain_TTW, dataFiles['TTWJetsToLNu'], "out_ana_clone")

#chain_TTZ = ROOT.TChain("Events")
#addfilesMany(chain_TTZ, dataFiles['TTZJetsToLNu'], "out_ana_clone")

#"/home/dildick/DisplacedMuonJetAnalysis_2016/CMSSW_8_0_24/src/MuJetAnalysis/AnalysisRun2/scripts/HLTEfficiency/orthogonalMethod/out_ana_selected_MET_2016BH_20180307.dimuonMass.root")

#file_ZZ = TFile("datafiles/")
#chain_ZZ = file_ZZ.Get("Events")

chains = {}
chains['WZTo3LNu'] = chain_WZ
#chains['ZZTo4Mu'] = chain_ZZ
#chains['TTWJetsToLNu'] = chain_TTW
chains['TTZJetsToLNu'] = chain_TTZ
chains['METData'] = chain_Data

lumi = 59.8

WZ_xsec = 5052#fb#575
ZZ_xsec = 55.884#fb
TTW_xsec = 200.1 #fb
TTZ_xsec = 243.2 #fb

WZ_events = 18000000. #496684.
ZZ_events = 100000.
TTW_events = 3120397
TTZ_events = 5934228

def scaleWZ(hist):
    hist.Scale(lumi*WZ_xsec/WZ_events)

def scaleZZ(hist):
    hist.Scale(lumi*ZZ_xsec/ZZ_events)

def scaleTTW(hist):
    hist.Scale(lumi*TTW_xsec/TTW_events)

def scaleTTZ(hist):
    hist.Scale(lumi*TTZ_xsec/TTZ_events)

def scaleMET(hist):
    pass


def scaleSample(sample, hist):
    if sample is 'WZTo3LNu':
        hist.Scale(lumi*WZ_xsec/WZ_events)
    if sample is 'ZZTo4Mu':
        hist.Scale(lumi*ZZ_xsec/ZZ_events)
    if sample is 'TTWJetsToLNu':
        hist.Scale(lumi*TTW_xsec/TTW_events)
    if sample is 'TTZJetsToLNu':
        hist.Scale(lumi*TTZ_xsec/TTZ_events)
    if sample is 'METData':
        pass

## make the selection
nMuonCut = "nRecoMu == 3"
ptMuonCut= "selMu0_pT > 30 && selMu1_pT > 30 && selMu2_pT > 10"
muonTightCut = "selMu0_isTight==1 && selMu1_isTight==1 && selMu2_isTight==1"
muonDxyCut = "selMu0_dxy < 0.01 && selMu1_dxy < 0.01 && selMu2_dxy < 0.01"
muonDzCut = "selMu0_dz < 0.1 && selMu1_dz < 0.1 && selMu2_dz < 0.1"
muonIsoCut = "selMu0_PFIso < 0.15 && selMu1_PFIso < 0.15 && selMu2_PFIso < 0.15"
OK_MET  = "OK_MET==1"
SS = 'selMu0_charge == selMu1_charge && selMu1_charge == selMu2_charge'
OS = '!(%s)'%SS
bjetCut = "nBJet_20==0"
dimuonMassCut = "abs(best_OS_dimuon_mass-91.2)<15"

my_cut = (TCut(nMuonCut) +
          TCut(ptMuonCut) +
#          TCut(muonTightCut) +
#          TCut(muonDxyCut) +
#          TCut(muonDzCut) +
#          TCut(muonIsoCut) +
          TCut(OK_MET)
#          TCut(bjetCut)
          )

my_cut_dimuon = my_cut + TCut(dimuonMassCut) + TCut(OS)
my_cut_SS = my_cut + TCut(SS)

my_cut_HLT = my_cut + TCut("OK_Signal==1")
my_cut_dimuon_HLT = my_cut_dimuon + TCut("OK_Signal==1")

out_directory = "trigger_efficiency_plots/"

print my_cut
"""
chain_WZ_filtered_OS = chain_WZ.CopyTree(my_cut_OS.GetTitle())
chain_ZZ_filtered_OS = chain_ZZ.CopyTree(my_cut_OS.GetTitle())
chain_TTW_filtered_OS = chain_TTW.CopyTree(my_cut_OS.GetTitle())
chain_TTZ_filtered_OS = chain_TTW.CopyTree(my_cut_OS.GetTitle())
chain_Data_filtered_OS = chain_Data.CopyTree(my_cut_OS.GetTitle())

chain_WZ_filtered_SS = chain_WZ.CopyTree(my_cut_SS.GetTitle())
chain_ZZ_filtered_SS = chain_ZZ.CopyTree(my_cut_SS.GetTitle())
chain_TTW_filtered_SS = chain_TTW.CopyTree(my_cut_SS.GetTitle())
chain_TTZ_filtered_SS = chain_TTW.CopyTree(my_cut_SS.GetTitle())
chain_Data_filtered_SS = chain_Data.CopyTree(my_cut_SS.GetTitle())
"""
variables = {}
variables["selMu0_charge"] = (3,-1,1)
variables["selMu1_charge"] = (3,-1,1)
variables["selMu2_charge"] = (3,-1,1)

variables["selMu0_pT"] = (30,0,300)
variables["selMu1_pT"] = (30,0,300)
variables["selMu2_pT"] = (30,0,300)
"""
variables["selMu0_px"] = (150,0,300)
variables["selMu1_px"] = (150,0,300)
variables["selMu2_px"] = (150,0,300)

variables["selMu0_py"] = (150,0,300)
variables["selMu1_py"] = (150,0,300)
variables["selMu2_py"] = (150,0,300)

variables["selMu0_pz"] = (150,0,300)
variables["selMu1_pz"] = (150,0,300)
variables["selMu2_pz"] = (150,0,300)
"""
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
                     #histogram3,
                     #histogram4,
                     histogram5,
                     x_label, y_label, saveAs, format='pdf'):

    ## setup histogram
    hist = HepPlotterDataMC()#"histogram"
    hist.x_relative_size = 10
    hist.y_relative_size = 7
    hist.drawEffDist = False    # draw the physics distribution for efficiency (jet_pt for jet trigger)
    #hist.rebin       = 1
    hist.x_label     = x_label# "Dimuon invariant mass"
    hist.y_label     = y_label
    hist.y_ratio_label     = "Data/MC"
    hist.format      = format      # file format for saving image
    hist.saveDir     = out_directory
    hist.saveAs      = saveAs# "Z_peak_2016MonteCarlo_WZ" # save figure with name
    hist.CMSlabel       = 'outer'  # 'top left', 'top right'; hack code for something else
    hist.CMSlabelStatus = ''  # ('Simulation')+'Internal' || 'Preliminary'
    hist.initialize()
    hist.lumi = '2018 MET, 59.8'
    hist.plotLUMI = True
    #    hist.Add(histogram3, name='ttW', sampleType='background')
    hist.Add(histogram2, name='ttZ', sampleType='background')
    #    hist.Add(histogram2, name='ZZto4Mu', sampleType='background')
    hist.Add(histogram1, name='WZto3Mu', sampleType='background')
    hist.Add(histogram5, name='data', sampleType='data')
    hist.drawSystUncertainty = False     # draw syst uncertainty separately
    hist.drawStatSystUncertainty = False  # draw stat+syst uncertainty
    hist.blind       = False
    hist.ratio_plot  = False        # plot a ratio of things [Data/MC]
    hist.ratio_type  = "ratio"     # "ratio"
    hist.stacked     = True        # stack plots
    fig = hist.execute()
    fig.text(0.95, 0.04, x_label, horizontalalignment='right', fontsize=20)
    fig.tight_layout()
    fig.subplots_adjust(bottom=0.15)
    #plot.xlabel(x_label, horizontalalignment='right', x=1.0)
    hist.savefig()


def makePlot(histogram, plotType, x_label, y_label, saveAs, isData = False, format='pdf'):

    ## setup histogram
    hist = HepPlotter("efficiency",1)#"histogram"
    hist.x_relative_size = 10
    hist.y_relative_size = 7
    hist.drawEffDist = False    # draw the physics distribution for efficiency (jet_pt for jet trigger)
    #hist.rebin       = 1
    hist.x_label     = x_label# "Dimuon invariant mass"
    hist.y_label     = y_label
    hist.format      = format      # file format for saving image
    hist.saveDir     = out_directory
    hist.saveAs      = saveAs# "Z_peak_2016MonteCarlo_WZ" # save figure with name
    hist.CMSlabel       = 'outer'  # 'top left', 'top right'; hack code for something else
    if isData:
        hist.CMSlabelStatus = ''  # ('Simulation')+'Internal' || 'Preliminary'
    else:
        hist.CMSlabelStatus = 'Simulation'  # ('Simulation')+'Internal' || 'Preliminary'
    hist.initialize()
    hist.lumi = '2016 MET, 59.8'
    hist.plotLUMI = isData
    hist.drawStatUncertainty = True
    hist.Add(histogram, draw='errorbar', color='black', linecolor='black', label='Signal Triggers')

    dataLabel = saveAs.split("_")[0]
    print dataLabel
    if dataLabel == "WZ":
        extraText = r"$pp \rightarrow WZ$"
        hist.extra_text.Add(extraText, coords=[0.1,0.3])
    if dataLabel == "ZZ":
        extraText = r"$pp \rightarrow ZZ$"
        hist.extra_text.Add(extraText, coords=[0.1,0.3])
    if dataLabel == "TTZ":
        extraText = r"$pp \rightarrow t\bar{t}Z$"
        hist.extra_text.Add(extraText, coords=[0.1,0.3])
    if dataLabel == "TTW":
        extraText = r"$pp \rightarrow t\bar{t}W$"
        hist.extra_text.Add(extraText, coords=[0.1,0.3])

    plot = hist.execute()
    hist.savefig()


## for each kinematic property, plot all contributions
for myvar in variables:
    #continue


    print myvar
    bins = "(" + str(variables[myvar][0]) + "," + str(variables[myvar][1]) + "," + str(variables[myvar][2]) + ")"
    print bins

    """
    print chain_WZ.GetEntries(my_cut.GetTitle())
    print chain_ZZ.GetEntries(my_cut.GetTitle())
    print chain_TTW.GetEntries(my_cut.GetTitle())
    print chain_TTZ.GetEntries(my_cut.GetTitle())
    print chain_Data.GetEntries(my_cut.GetTitle())

    chain_WZ_filtered_OS.Draw(myvar + ">>h_WZ_" + myvar + bins)
    chain_ZZ_filtered_OS.Draw(myvar + ">>h_ZZ_" + myvar + bins)
    chain_TTW_filtered_OS.Draw(myvar + ">>h_TTW_" + myvar + bins)
    chain_TTZ_filtered_OS.Draw(myvar + ">>h_TTZ_" + myvar + bins)
    chain_Data_filtered_OS.Draw(myvar + ">>h_Data_" + myvar + bins)
    """

    #    chain_TTW.Draw(myvar + ">>h_TTW_" + myvar + bins, my_cut)
    #    chain_ZZ.Draw(myvar + ">>h_ZZ_" + myvar + bins, my_cut)
    chain_WZ.Draw(myvar + ">>h_WZ_" + myvar + bins, my_cut_dimuon)
    chain_TTZ.Draw(myvar + ">>h_TTZ_" + myvar + bins, my_cut_dimuon)
    chain_Data.Draw(myvar + ">>h_Data_" + myvar + bins, my_cut_dimuon)

    h_WZ = TH1F(gDirectory.Get("h_WZ_" + myvar).Clone("h_WZ_" + myvar))
    h_TTZ = TH1F(gDirectory.Get("h_TTZ_" + myvar).Clone("h_TTZ_" + myvar))
    h_Data = TH1F(gDirectory.Get("h_Data_" + myvar).Clone("h_Data_" + myvar))

    #    if not (myvar is "best_OS_dimuon_mass" or myvar is"best_SS_dimuon_mass" or myvar is"m123"):
    #        h_ZZ = TH1F(gDirectory.Get("h_ZZ_" + myvar).Clone("h_ZZ_" + myvar))
    #        h_TTW = TH1F(gDirectory.Get("h_TTW_" + myvar).Clone("h_TTW_" + myvar))
    #    else:
    #        h_ZZ = TH1F("h_ZZ","",variables[myvar][0],variables[myvar][1],variables[myvar][2])
    #        h_TTW = TH1F("h_TTW","",variables[myvar][0],variables[myvar][1],variables[myvar][2])

    #    scaleZZ(h_ZZ)
    #    scaleTTW(h_TTW)
    scaleWZ(h_WZ)
    scaleTTZ(h_TTZ)

    #    print h_Data.Integral() / (h_WZ.Integral() + h_ZZ.Integral() + h_TTZ.Integral() + h_TTW.Integral())
    #    print h_Data.Integral(), h_WZ.Integral() + h_ZZ.Integral() + h_TTZ.Integral() + h_TTW.Integral()

    makePlotDataVsMC(h_WZ, #h_ZZ, h_TTW,
                     h_TTZ, h_Data, x_axis_labels[myvar], "Entries", "Combine_" + myvar, format='pdf')



#exit(1)



## efficiency plots
for myvar in variables:
    if not ('pT' in myvar or 'eta' in myvar or 'phi' in myvar or 'best_OS_dimuon_mass' in myvar): continue
    print myvar
    bins = "(" + str(variables[myvar][0]) + "," + str(variables[myvar][1]) + "," + str(variables[myvar][2]) + ")"
    #    continue

    myvar_actual = ""
    if 'best_OS_dimuon_mass' in myvar:
        myvar_actual = 'abs(' + myvar + '-91.2)'
        bins = "(8,0,16)"
    else:
        myvar_actual = myvar

    if 'best_OS_dimuon_mass' in myvar:
        continue

    chain_WZ.Draw(myvar_actual + ">>h_WZ_" + myvar + bins, my_cut_dimuon)
#    chain_ZZ.Draw(myvar_actual + ">>h_ZZ_" + myvar + bins, my_cut)
#    chain_TTW.Draw(myvar_actual + ">>h_TTW_" + myvar + bins, my_cut)
    chain_TTZ.Draw(myvar_actual + ">>h_TTZ_" + myvar + bins, my_cut_dimuon)
    chain_Data.Draw(myvar_actual + ">>h_Data_" + myvar + bins, my_cut_dimuon)

#    if not (myvar is "best_OS_dimuon_mass" or myvar is"best_SS_dimuon_mass" or myvar is"m123"):
#        h_ZZ = TH1F(gDirectory.Get("h_ZZ_" + myvar).Clone("h_ZZ_" + myvar))
#        h_TTW = TH1F(gDirectory.Get("h_TTW_" + myvar).Clone("h_TTW_" + myvar))
#    else:
#        h_ZZ = TH1F("h_ZZ","",variables[myvar][0],variables[myvar][1],variables[myvar][2])
#        h_TTW = TH1F("h_TTW","",variables[myvar][0],variables[myvar][1],variables[myvar][2])

    h_WZ = TH1F(gDirectory.Get("h_WZ_" + myvar).Clone("h_WZ_" + myvar))
    h_TTZ = TH1F(gDirectory.Get("h_TTZ_" + myvar).Clone("h_TTZ_" + myvar))
    h_Data = TH1F(gDirectory.Get("h_Data_" + myvar).Clone("h_Data_" + myvar))

    chain_WZ.Draw(myvar_actual + ">>h_WZ_" + myvar + "_HLT" + bins, my_cut_dimuon_HLT)
#    chain_ZZ.Draw(myvar_actual + ">>h_ZZ_" + myvar + "_HLT" + bins, my_cut_HLT)
#    chain_TTW.Draw(myvar_actual + ">>h_TTW_" + myvar + "_HLT" + bins, my_cut_HLT)
    chain_TTZ.Draw(myvar_actual + ">>h_TTZ_" + myvar + "_HLT" + bins, my_cut_dimuon_HLT)
    chain_Data.Draw(myvar_actual + ">>h_Data_" + myvar + "_HLT" + bins, my_cut_dimuon_HLT)

    h_WZ_HLT = TH1F(gDirectory.Get("h_WZ_" + myvar + "_HLT").Clone("h_WZ_" + myvar + "_HLT"))
#    h_ZZ_HLT = TH1F(gDirectory.Get("h_ZZ_" + myvar + "_HLT").Clone("h_ZZ_" + myvar + "_HLT"))
#    h_TTW_HLT = TH1F(gDirectory.Get("h_TTW_" + myvar + "_HLT").Clone("h_TTW_" + myvar + "_HLT"))
    h_TTZ_HLT = TH1F(gDirectory.Get("h_TTZ_" + myvar + "_HLT").Clone("h_TTZ_" + myvar + "_HLT"))
    h_Data_HLT = TH1F(gDirectory.Get("h_Data_" + myvar + "_HLT").Clone("h_Data_" + myvar + "_HLT"))

    h_WZ_HLT_Eff = TEfficiency(h_WZ_HLT, h_WZ)
#    h_ZZ_HLT_Eff = TEfficiency(h_ZZ_HLT, h_ZZ)
#    h_TTW_HLT_Eff = TEfficiency(h_TTW_HLT, h_TTW)
    h_TTZ_HLT_Eff = TEfficiency(h_TTZ_HLT, h_TTZ)
    h_Data_HLT_Eff = TEfficiency(h_Data_HLT, h_Data)

    print float(h_Data.GetEntries())
    print "WZ eff", h_WZ_HLT.GetEntries() / float(h_WZ.GetEntries())
#    print "ZZ eff", h_ZZ_HLT.GetEntries() / float(h_ZZ.GetEntries())
#    print "TTW eff", h_TTW_HLT.GetEntries() / float(h_TTW.GetEntries())
    print "TTZ eff", h_TTZ_HLT.GetEntries() / float(h_TTZ.GetEntries())
    print "Data eff", h_Data_HLT.GetEntries() / float(h_Data.GetEntries())

    x_label = x_axis_labels[myvar]

    makePlot(h_WZ_HLT_Eff, "efficiency", x_label, "Trigger efficiency", "WZ_" + myvar + "_HLT",
             isData=False, format='pdf')
#    makePlot(h_ZZ_HLT_Eff, "efficiency", x_label, "Trigger efficiency", "ZZ_" + myvar + "_HLT",
#             isData=False, format='pdf')
#    makePlot(h_TTW_HLT_Eff, "efficiency", x_label, "Trigger efficiency", "TTW_" + myvar + "_HLT",
#             isData=False, format='pdf')
    makePlot(h_TTZ_HLT_Eff, "efficiency", x_label, "Trigger efficiency", "TTZ_" + myvar + "_HLT",
             isData=False, format='pdf')

    makePlot(h_Data_HLT_Eff, "efficiency", x_label, "Trigger efficiency", "Data_" + myvar + "_HLT",
             isData=True, format='pdf')
