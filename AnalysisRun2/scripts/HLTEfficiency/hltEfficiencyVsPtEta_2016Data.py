import sys
from ROOT import *
from argparse import ArgumentParser

from hepPlotter import HepPlotter
import hepPlotterTools as hpt
#import hepPlotterLabels as hpl

import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from Helpers import *

##____________________________________________________________
def efficiency_trigger(dirNames):

    verbose = False

    chain = ROOT.TChain("Events")

    print "Preparing histograms"

    RECO_leading_pt_fid = ROOT.TH1D("RECO_leading_pt_fid","",50,0.,50.);
    RECO_leading_eta_fid = ROOT.TH1D("RECO_leading_eta_fid","",50,-2.5,2.5);
    RECO_leading_phi_fid = ROOT.TH1D("RECO_leading_phi_fid","",60,-ROOT.TMath.Pi(),ROOT.TMath.Pi());

    hlt_RECO_leading_pt_fid_signal = ROOT.TH1D("hlt_RECO_leading_pt_fid_signal","",50,0.,50.);    
    hlt_RECO_leading_eta_fid_signal = ROOT.TH1D("hlt_RECO_leading_eta_fid_signal","",50,-2.5,2.5);
    hlt_RECO_leading_phi_fid_signal = ROOT.TH1D("hlt_RECO_leading_phi_fid_signal","",60,-ROOT.TMath.Pi(),ROOT.TMath.Pi());

    hlt_RECO_leading_pt_fid_backup = ROOT.TH1D("hlt_RECO_leading_pt_fid_backup","",50,0.,50.);    
    hlt_RECO_leading_eta_fid_backup = ROOT.TH1D("hlt_RECO_leading_eta_fid_backup","",50,-2.5,2.5);
    hlt_RECO_leading_phi_fid_backup = ROOT.TH1D("hlt_RECO_leading_phi_fid_backup","",60,-ROOT.TMath.Pi(),ROOT.TMath.Pi());


    print "Adding files to the chain"
    addfilesMany(chain, dirNames, "out_ana_selected_MET_2016BH_20171006.root")

    print "Loop over the chain"
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
        
        tree = myfile.Get("cutFlowAnalyzer_Data/Events")
        tree = myfile.Get("Events")

        if not tree: 
            if (verbose): print "Tree cutFlowAnalyzer_Data/Events does not exist"
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
                ## print list(tree.hltPaths)
                if any("HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx" in s for s in list(tree.hltPaths)):
                    if (verbose): print triggerPath, "is available"

                    ## print "\tPass num"
                    hlt_RECO_leading_pt_fid_signal.Fill(tree.selMu0_pT)
                    hlt_RECO_leading_eta_fid_signal.Fill(tree.selMu0_eta)
                    hlt_RECO_leading_phi_fid_signal.Fill(tree.selMu0_phi)

                if any("HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx" in s for s in list(tree.hltPaths)):
                    if (verbose): print triggerPath, "is available"

                    ## print "\tPass num"
                    hlt_RECO_leading_pt_fid_backup.Fill(tree.selMu0_pT)
                    hlt_RECO_leading_eta_fid_backup.Fill(tree.selMu0_eta)
                    hlt_RECO_leading_phi_fid_backup.Fill(tree.selMu0_phi)


    ### make the efficiency plots

    eff_hlt_RECO_leading_pt_fid_signal = ROOT.TEfficiency(hlt_RECO_leading_pt_fid_signal, RECO_leading_pt_fid)
    eff_hlt_RECO_leading_eta_fid_signal = ROOT.TEfficiency(hlt_RECO_leading_eta_fid_signal, RECO_leading_eta_fid)
    eff_hlt_RECO_leading_phi_fid_signal = ROOT.TEfficiency(hlt_RECO_leading_phi_fid_signal, RECO_leading_phi_fid)
    

    eff_hlt_RECO_leading_pt_fid_backup = ROOT.TEfficiency(hlt_RECO_leading_pt_fid_backup, RECO_leading_pt_fid)
    eff_hlt_RECO_leading_eta_fid_backup = ROOT.TEfficiency(hlt_RECO_leading_eta_fid_backup, RECO_leading_eta_fid)
    eff_hlt_RECO_leading_phi_fid_backup = ROOT.TEfficiency(hlt_RECO_leading_phi_fid_backup, RECO_leading_phi_fid)

    MyFile = TFile("HLT_efficiency_signal_backup_2016BH_13TeV.root","RECREATE");

    eff_hlt_RECO_leading_pt_fid_signal.Write("eff_hlt_RECO_leading_pt_fid_signal")
    eff_hlt_RECO_leading_eta_fid_signal.Write("eff_hlt_RECO_leading_eta_fid_signal")
    eff_hlt_RECO_leading_phi_fid_signal.Write("eff_hlt_RECO_leading_phi_fid_signal")

    eff_hlt_RECO_leading_pt_fid_backup.Write("eff_hlt_RECO_leading_pt_fid_backup")
    eff_hlt_RECO_leading_eta_fid_backup.Write("eff_hlt_RECO_leading_eta_fid_backup")
    eff_hlt_RECO_leading_phi_fid_backup.Write("eff_hlt_RECO_leading_phi_fid_backup")

    MyFile.Close();
    


dirNames = ['/home/dildick/DisplacedMuonJetAnalysis_2016/CMSSW_8_0_24/src/MuJetAnalysis/AnalysisRun2/scripts/HLTEfficiency/orthogonalMethod/']
#efficiency_trigger("HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx", dirNames)


def makePlot(effTuple, triggerPath):

    ## setup histogram
    hist = HepPlotter("efficiency",1)
    hist.drawEffDist = False    # draw the physics distribution for efficiency (jet_pt for jet trigger)
    #hist.rebin       = 1
    hist.x_label     = effTuple[1]
    hist.y_label     = "Trigger efficiency"
    hist.format      = 'png'       # file format for saving image
    hist.saveAs      = "eff_" + triggerPath + "_" + effTuple[2] # save figure with name
    hist.CMSlabel       = 'outer'  # 'top left', 'top right'; hack code for something else
    hist.CMSlabelStatus = 'Simulation Preliminary'  # ('Simulation')+'Internal' || 'Preliminary' 
    hist.initialize()
    #triggerPath.replace('_','\_')
    hist.extra_text.Add(r"\mathrm{" + triggerPath.replace('_','\_') + r"}",coords=[0.05,0.80])
    hist.drawStatUncertainty   = True

    hist.Add(effTuple[0], draw='errorbar', color='blue', linecolor='blue')
    
    plot = hist.execute()
    hist.savefig()


MyFile = TFile("Histograms.root");

eff_hlt_RECO_leading_pt_fid = MyFile.Get("RECO_leading_pt_fid_clone")
eff_hlt_RECO_leading_eta_fid = MyFile.Get("RECO_leading_eta_fid_clone")
eff_hlt_RECO_leading_phi_fid = MyFile.Get("RECO_leading_phi_fid_clone")

eff_pt = (eff_hlt_RECO_leading_pt_fid, r"Leading muon $p_\mathrm{T}$ [$\mathrm{GeV}$]", "pt")
eff_eta = (eff_hlt_RECO_leading_eta_fid, r"Leading muon #eta", "eta")
eff_phi = (eff_hlt_RECO_leading_phi_fid, r"Leading muon #phi", "phi")

eff_hlt_RECO_list = [eff_pt, eff_eta, eff_phi]

makePlot(eff_pt, "HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx")

MyFile.Close();

"""
void hltEfficiencyVsPtEta_Data()
{
  std::vector< std::vector<string> > samples_v
  readTextFileWithSamples("ANASamples2016METData_SD.txt", samples_v)

  const std::string hltPath = "HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx"
  for(const auto& v: samples_v) efficiency_trigger(v, hltPath)
}


  ## add files to the chain
  std::vector<std::string> dirNames2
  dirNames2.clear()
  dirNames2.push_back("/home/dildick/DisplacedMuonJetAnalysis_2016/CMSSW_8_0_24/src/MuJetAnalysis/AnalysisRun2/scripts/HLTEfficiency/orthogonalMethod/")
  addfilesMany(chain, dirNames2, "out_ana_selected_MET_2016BH_20171006.root")
  cout << "Total number of events: " << chain.GetEntries() << endl
"""
