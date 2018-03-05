
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

def makePlot(histogram1,
             histogram2,
             histogram3, 
             histogram4,
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
    hist.format      = format      # file format for saving image
    hist.saveDir     = 'trigger_efficiency_plots_2016Combined_WZ_20180227/'
    hist.saveAs      = saveAs# "Z_peak_2016MonteCarlo_WZ" # save figure with name
    hist.CMSlabel       = 'outer'  # 'top left', 'top right'; hack code for something else
    hist.CMSlabelStatus = 'Preliminary'  # ('Simulation')+'Internal' || 'Preliminary' 
    hist.initialize()
    hist.lumi = '2016 MET B-H, 35.9'
    hist.plotLUMI = True
    hist.Add(histogram3, name='ttW', sampleType='background')
    hist.Add(histogram4, name='ttZ', sampleType='background')
    hist.Add(histogram2, name='ZZto4Mu', sampleType='background')
    hist.Add(histogram1, name='WZto3Mu', sampleType='background')
    hist.Add(histogram5, name='data', sampleType='data')
    hist.drawStatUncertainty = True      # draw stat uncertainty separately
    hist.drawSystUncertainty = False     # draw syst uncertainty separately
    hist.drawStatSystUncertainty = False  # draw stat+syst uncertainty
    hist.blind       = False
    hist.ratio_plot  = False        # plot a ratio of things [Data/MC]
    hist.ratio_type  = "ratio"     # "ratio"
    hist.stacked     = True        # stack plots
    plot = hist.execute()
    hist.savefig()


MyFile1 = TFile("HLT_Z_peak_signal_2016MonteCarlo_WZ_13TeV.root");
MyFile2 = TFile("HLT_Z_peak_signal_2016MonteCarlo_ZZto4L_13TeV.root");
MyFile3 = TFile("HLT_Z_peak_signal_2016MET_WZ_13TeV.root");
MyFile4 = TFile("HLT_Z_peak_signal_2016MonteCarlo_TTZJets_13TeV.root");
MyFile5 = TFile("HLT_Z_peak_signal_2016MonteCarlo_TTWJets_13TeV.root");

Invariant_Mass12_WZ = MyFile1.Get("Invariant_Mass12")
Invariant_Mass12_ZZ = MyFile2.Get("Invariant_Mass12")
Invariant_Mass12_MET = MyFile3.Get("Invariant_Mass12_OS")
Invariant_Mass12_TTZ = MyFile4.Get("Invariant_Mass12")
Invariant_Mass12_TTW = MyFile5.Get("Invariant_Mass12")

lumi = 35.9 #data processing penalty
WZ_xsec = 575#4430#fb
ZZ_xsec = 55.884#fb
TTW_xsec = 200.1 #fb
TTZ_xsec = 252.9 #fb
WZ_events = 496684.#18000000
ZZ_events = 100000.
TTW_events = 3120397
TTZ_events = 5934228

Invariant_Mass12_WZ.Scale(lumi*WZ_xsec/WZ_events)
Invariant_Mass12_ZZ.Scale(lumi*ZZ_xsec/ZZ_events)
Invariant_Mass12_TTW.Scale(lumi*TTW_xsec/TTW_events)
Invariant_Mass12_TTZ.Scale(lumi*TTZ_xsec/TTZ_events)
Invariant_Mass12_MET.Scale(1)

makePlot(Invariant_Mass12_WZ,
         Invariant_Mass12_ZZ,
         Invariant_Mass12_TTW,
         Invariant_Mass12_TTZ,
         Invariant_Mass12_MET,
         r"Dimuon invariant mass [GeV]", "Entries", "Z_peak_2016MonteCarlo_WZ_extra", format='pdf')

print Invariant_Mass12_MET.Integral()/(Invariant_Mass12_WZ.Integral()*1.0 + Invariant_Mass12_ZZ.Integral()*1.0)
print (Invariant_Mass12_MET.Integral() - (Invariant_Mass12_WZ.Integral()*1.0 + Invariant_Mass12_ZZ.Integral()*1.0))/(Invariant_Mass12_WZ.Integral()*1.0 + Invariant_Mass12_ZZ.Integral()*1.0)
MyFile1.Close()
MyFile2.Close()
MyFile3.Close()
MyFile4.Close()
MyFile5.Close()

exit(1)
