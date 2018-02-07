import sys
from ROOT import *
from argparse import ArgumentParser

from hepPlotter import HepPlotter
import hepPlotterTools as hpt
#import hepPlotterLabels as hpl
import math as m
import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from Helpers import *

def makePlot(histogram1,
             histogram2,
             histogram3, 
             plotType, x_label, y_label, saveAs, format='pdf'):

    ## setup histogram
    hist = HepPlotter(plotType,1)#"histogram"
    hist.x_relative_size = 10
    hist.y_relative_size = 7
    hist.drawEffDist = False    # draw the physics distribution for efficiency (jet_pt for jet trigger)
    #hist.rebin       = 1
    hist.x_label     = x_label# "Dimuon invariant mass"
    hist.y_label     = y_label
    hist.format      = format      # file format for saving image
    hist.saveDir     = 'trigger_efficiency_plots_2016Combined_WZ_20180207/'
    hist.saveAs      = saveAs# "Z_peak_2016MonteCarlo_WZ" # save figure with name
    hist.CMSlabel       = 'outer'  # 'top left', 'top right'; hack code for something else
    hist.CMSlabelStatus = 'Preliminary'  # ('Simulation')+'Internal' || 'Preliminary' 
    hist.initialize()
    hist.lumi = '2016 MET B-H, 35.9'
    hist.plotLUMI = True
    hist.drawStatUncertainty = True    
    hist.Add(histogram1, draw='errorbar', color='blue', linecolor='blue', label=r'$WZ \rightarrow 3\mu\nu$')
    plot = hist.execute()
    hist.Add(histogram2, draw='errorbar', color='red', linecolor='red', label=r'$ZZ \rightarrow 4\mu$')
    plot = hist.execute()
    hist.Add(histogram3, draw='errorbar', color='black', linecolor='black', label=r'$2016MET$')
    plot = hist.execute()
    hist.savefig()


MyFile1 = TFile("HLT_Z_peak_signal_2016MonteCarlo_WZ_13TeV.root");
MyFile2 = TFile("HLT_Z_peak_signal_2016MonteCarlo_ZZto4L_13TeV.root");
MyFile3 = TFile("HLT_Z_peak_signal_2016MET_WZ_13TeV.root");

Invariant_Mass12_WZ = MyFile1.Get("Invariant_Mass12")
Invariant_Mass12_ZZ = MyFile2.Get("Invariant_Mass12")
Invariant_Mass12_MET = MyFile3.Get("Invariant_Mass12")

lumi = 35.9
WZ_xsec = 575.4#fb
ZZ_xsec = 55.884#fb
WZ_events = 496684.
ZZ_events = 100000.

Invariant_Mass12_WZ.Scale(lumi*WZ_xsec/WZ_events)
Invariant_Mass12_ZZ.Scale(lumi*ZZ_xsec/ZZ_events)
Invariant_Mass12_MET.Scale(1)


c = TCanvas("c","",800,600)
c.cd()

Invariant_Mass12_WZ.SetLineColor(kRed)
Invariant_Mass12_ZZ.SetLineColor(kBlue)
Invariant_Mass12_MET.SetLineColor(kBlack)

Invariant_Mass12_MET.SetMarkerSize(1)
Invariant_Mass12_MET.SetMarkerStyle(20)
Invariant_Mass12_MET.SetMarkerColor(kBlack)

Invariant_Mass12_WZ.SetFillColor(kRed)
Invariant_Mass12_ZZ.SetFillColor(kBlue)

Invariant_Mass12_WZ.Draw()
Invariant_Mass12_ZZ.Draw("same")
Invariant_Mass12_MET.Draw("samep")

c.SaveAs("trigger_efficiency_plots_2016Combined_WZ_20180207/Z_peak_2016MonteCarlo_WZ.pdf")
#makePlot(Invariant_Mass12_WZ,
#         Invariant_Mass12_ZZ,
 #        Invariant_Mass12_MET,
#         "histogram", 
#         r"Dimuon invariant mass [GeV]", "Entries", "Z_peak_2016MonteCarlo_WZ", format='pdf')

print Invariant_Mass12_MET.Integral()/(Invariant_Mass12_WZ.Integral()*1.0 + Invariant_Mass12_ZZ.Integral()*1.0)

MyFile1.Close()
MyFile2.Close()
MyFile3.Close()

exit(1)
