#include <iostream>
#include <iomanip>
using namespace std;
#include <algorithm>    // std::max
#include <stdlib.h>
#include <math.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH2F.h>
#include <TTree.h>
#include <TCut.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TChain.h>
#include <TChainElement.h>
#include "Helpers.h"
#include "TLatex.h"
#include "TROOT.h"

template <class T>
void makePlot(T* h)
{
  return; 
}

double calc_eff(double num, double denom)
{
  //eff = num/denom;
  double eff_uncert = sqrt( ( (num/denom)*(1-(num/denom) ) )/denom );
  return eff_uncert;
}


void jpsiScriptsSD(TString datafile)
{
  gROOT->SetBatch(true);

  // data chain
  TChain* chain = new TChain("cutFlowAnalyzerPXBL3PXFL2/Events");
  
  //std::string inputFile = "sps.txt"; TString sample = "SPS"; 
  //std::string inputFile = "dps1.txt"; TString sample = "DPS1";
  //std::string inputFile = "dps2.txt"; TString sample = "DPS2";
  //std::string inputFile = "dps3.txt"; TString sample = "DPS3";
  //std::string inputFile = "dps4.txt"; TString sample = "DPS4";
  //std::string inputFile = "dps5.txt"; TString sample = "DPS5";
  //std::string inputFile = "dps6.txt"; TString sample = "DPS6";
  //std::string inputFile = "Charmonium_all.txt"; TString sample = "2016Charmonium_BH";

  std::string inputFile = std::string(datafile.Data()) + ".txt";    TString sample = "2016" + datafile;
  //std::string inputFile = "Charmonium_C_v4.txt"; TString sample = "2016Charmonium_C";
  //std::string inputFile = "Charmonium_D.txt";    TString sample = "2016Charmonium_D";
  //std::string inputFile = "Charmonium_E.txt";    TString sample = "2016Charmonium_E";
  //std::string inputFile = "Charmonium_F.txt";    TString sample = "2016Charmonium_F";
  //std::string inputFile = "Charmonium_G.txt";    TString sample = "2016Charmonium_G";
  //std::string inputFile = "Charmonium_H.txt";    TString sample = "2016Charmonium_H";

  std::vector< std::vector<string> > input_data_files;
  readTextFileWithSamples(inputFile, input_data_files);
  addfilesMany(chain, input_data_files[0], "out_ana_");

  TString outputdir = "plots_SPS_DPS_SD20180512/";
  
  // make plots
  TH1F *P_t_Mu0 = new TH1F("P_t_Mu0",";Leading muon p_{T} [GeV];Entries",100,0.0,50.0);
  TH1F *P_t_Mu1 = new TH1F("P_t_Mu1",";Second leading muon p_{T} [GeV];Entries",100,0.0,50.0);
  TH1F *P_t_Mu2 = new TH1F("P_t_Mu2",";Third leading muon p_{T} [GeV];Entries",100,0.0,50.0);
  TH1F *P_t_Mu3 = new TH1F("P_t_Mu3",";Fourth leading muon p_{T} [GeV];Entries",100,0.0,50.0);

  TH1F *mass_C= new TH1F("mass_C",";m_{#mu#mu1} [GeV];Entries",100,0.0,5.0);
  TH1F *mass_F= new TH1F("mass_F",";m_{#mu#mu2} [GeV];Entries",100,0.0,5.0);

  TH1F *iso_C = new TH1F("iso_C",";Iso_{#mu#mu1} [GeV];Entries",100,0.0,12.0);
  TH1F *iso_F = new TH1F("iso_F",";Iso_{#mu#mu2} [GeV];Entries",100,0.0,12.0);

  TH1F *lxy_C = new TH1F("lxy_C",";Lxy_{#mu#mu1} [GeV];Entries",100,-0.02,0.2);
  TH1F *lxy_F = new TH1F("lxy_F",";Lxy_{#mu#mu2} [GeV];Entries",100,-0.02,0.2);

  TH1F *diMuon_DeltaRapidity = new TH1F("diMuon_DeltaRapidity",";;Entries",50,0,5.0);

  TH1F *eta_Mu0 = new TH1F("eta_Mu0",";Leading muon #eta;Entries",100,-2.5,2.5);
  TH1F *eta_Mu1 = new TH1F("eta_Mu1",";Second muon #eta;Entries",100,-2.5,2.5);
  TH1F *eta_Mu2 = new TH1F("eta_Mu2",";Third muon #eta;Entries",100,-2.5,2.5);
  TH1F *eta_Mu3 = new TH1F("eta_Mu3",";Fourth muon #eta;Entries",100,-2.5,2.5);


  TH1F *P_t_Mu0_aftTrig = new TH1F("P_t_Mu0_aftTrig",";Leading muon p_{T} [GeV];Entries",100,0.0,50.0);
  TH1F *P_t_Mu1_aftTrig = new TH1F("P_t_Mu1_aftTrig",";Second leading muon p_{T} [GeV];Entries",100,0.0,50.0);
  TH1F *P_t_Mu2_aftTrig = new TH1F("P_t_Mu2_aftTrig",";Third leading muon p_{T} [GeV];Entries",100,0.0,50.0);
  TH1F *P_t_Mu3_aftTrig = new TH1F("P_t_Mu3_aftTrig",";Fourth leading muon p_{T} [GeV];Entries",100,0.0,50.0);

  TH1F *mass_C_aftTrig = new TH1F("mass_C_aftTrig",";m_{#mu#mu1} [GeV];Entries",100,0.0,5.0);
  TH1F *mass_F_aftTrig = new TH1F("mass_F_aftTrig",";m_{#mu#mu2} [GeV];Entries",100,0.0,5.0);

  TH1F *mass_C_aftTrig_cut = new TH1F("mass_C_aftTrig_cut",";m_{#mu#mu1} [GeV];Entries",100,2.8,3.3);
  TH1F *mass_F_aftTrig_cut = new TH1F("mass_F_aftTrig_cut",";m_{#mu#mu2} [GeV];Entries",100,2.8,3.3);

  TH1F *mass_C_aftTrig_cut_lxylt0p05 = new TH1F("mass_C_aftTrig_cut_lxylt0p05",";m_{#mu#mu1} [GeV];Entries",100,2.8,3.3);
  TH1F *mass_C_aftTrig_cut_lxylt0p2 = new TH1F("mass_C_aftTrig_cut_lxylt0p2",";m_{#mu#mu1} [GeV];Entries",100,2.8,3.3);
  TH1F *mass_C_aftTrig_cut_lxylt0p4 = new TH1F("mass_C_aftTrig_cut_lxylt0p4",";m_{#mu#mu1} [GeV];Entries",100,2.8,3.3);
  TH1F *mass_C_aftTrig_cut_lxylt1p0 = new TH1F("mass_C_aftTrig_cut_lxylt1p0",";m_{#mu#mu1} [GeV];Entries",100,2.8,3.3);


  TH1F *iso_C_aftTrig = new TH1F("iso_C_aftTrig",";Iso_{#mu#mu1} [GeV];Entries",100,0.0,12.0);
  TH1F *iso_F_aftTrig = new TH1F("iso_F_aftTrig",";Iso_{#mu#mu2} [GeV];Entries",100,0.0,12.0);

  TH1F *eta_Mu0_aftTrig = new TH1F("eta_Mu0_aftTrig",";Leading muon #eta;Entries",100,-2.5,2.5);
  TH1F *eta_Mu1_aftTrig = new TH1F("eta_Mu1_aftTrig",";Second muon #eta;Entries",100,-2.5,2.5);
  TH1F *eta_Mu2_aftTrig = new TH1F("eta_Mu2_aftTrig",";Third muon #eta;Entries",100,-2.5,2.5);
  TH1F *eta_Mu3_aftTrig = new TH1F("eta_Mu3_aftTrig",";Fourth muon #eta;Entries",100,-2.5,2.5);

  TH1F *diMuons_dz = new TH1F("diMuons_dz",";#Delta z_{#mu#mu};Entries",100,-1.0,1.0);

  TH1F *diMuonC_Lxy_RegionA = new TH1F("diMuonC_Lxy_RegionA",";Lxy ;Entries",50,-0.2,1.0);
  TH1F *diMuonF_Lxy_RegionA = new TH1F("diMuonF_Lxy_RegionA",";;Entries",50,-0.2,1.0);

  TH1F *diMuonC_Lxy_RegionBCD = new TH1F("diMuonC_Lxy_RegionBCD",";;Entries",50,-0.2,1.0);
  TH1F *diMuonF_Lxy_RegionBCD = new TH1F("diMuonF_Lxy_RegionBCD",";;Entries",50,-0.2,1.0);

  TH1F *diMuonC_Lxy_RegionBCD_invtdz = new TH1F("diMuonC_Lxy_RegionBCD_invtdz",";;Entries",50,-0.2,1.0);
  TH1F *diMuonF_Lxy_RegionBCD_invtdz = new TH1F("diMuonF_Lxy_RegionBCD_invtdz",";;Entries",50,-0.2,1.0);

  TH1F *diMuon_DeltaRapidity_RegionA = new TH1F("diMuon_DeltaRapidity_RegionA",";;Entries",50,0,5.0);
  TH1F *diMuon_DeltaRapidity_RegionBCD = new TH1F("diMuon_DeltaRapidity_RegionBCD",";;Entries",50,0,5.0);
  
  TH2F *Iso_dim1_vs_dim2 = new TH2F("Iso_dim1_vs_dim2",";;Entries",100,0.0,12.0,100,0.0,12.0);
  TH2F *Iso_dim1_vs_dim2_aftmasscut = new TH2F("Iso_dim1_vs_dim2_aftmasscut",";;Entries",100,0.0,12.0,100,0.0,12.0);
  TH2F *mass_dim1_vs_dim2 = new TH2F("mass_dim1_vs_dim2",";;Entries",100,0.0,5.0,100,0.0,5.0);
  
  TString recoMu4 = "nRecoMu>=4";
  TString vtx =     " && isVertexOK";
  TString dimuon =  " && is2DiMuons";
  TString secvtx =  " && is2DiMuonsFittedVtxOK";
  TString dz =      " && fabs(diMuons_dz_FittedVtx)<0.1";
  TString trig =    " && isDiMuonHLTFired";

  // get the histograms
  chain->Draw("selMu0_pT>>P_t_Mu0",recoMu4);
  chain->Draw("selMu1_pT>>P_t_Mu1",recoMu4);
  chain->Draw("selMu2_pT>>P_t_Mu2",recoMu4);
  chain->Draw("selMu3_pT>>P_t_Mu3",recoMu4);

  chain->Draw("selMu0_eta>>eta_Mu0",recoMu4);
  chain->Draw("selMu1_eta>>eta_Mu1",recoMu4);
  chain->Draw("selMu2_eta>>eta_Mu2",recoMu4);
  chain->Draw("selMu3_eta>>eta_Mu3",recoMu4);

  chain->Draw("selMu0_pT>>P_t_Mu0_aftTrig",recoMu4 + trig + vtx);
  chain->Draw("selMu1_pT>>P_t_Mu1_aftTrig",recoMu4 + trig + vtx);
  chain->Draw("selMu2_pT>>P_t_Mu2_aftTrig",recoMu4 + trig + vtx);
  chain->Draw("selMu3_pT>>P_t_Mu3_aftTrig",recoMu4 + trig + vtx);

  chain->Draw("selMu0_eta>>eta_Mu0_aftTrig",recoMu4 + vtx + trig);
  chain->Draw("selMu1_eta>>eta_Mu1_aftTrig",recoMu4 + vtx + trig);
  chain->Draw("selMu2_eta>>eta_Mu2_aftTrig",recoMu4 + vtx + trig);
  chain->Draw("selMu3_eta>>eta_Mu3_aftTrig",recoMu4 + vtx + trig);

  chain->Draw("massC>>mass_C",recoMu4 + vtx + dimuon);
  chain->Draw("massF>>mass_F",recoMu4 + vtx + dimuon);
  chain->Draw("diMuonC_IsoTk_FittedVtx>>iso_C",recoMu4 + vtx + dimuon);
  chain->Draw("diMuonF_IsoTk_FittedVtx>>iso_F",recoMu4 + vtx + dimuon);

  chain->Draw("diMuonC_FittedVtx_Lxy>>lxy_C",recoMu4 + vtx + dimuon);
  chain->Draw("diMuonF_FittedVtx_Lxy>>lxy_F",recoMu4 + vtx + dimuon);

  chain->Draw("diMuons_dz_FittedVtx>>diMuons_dz",recoMu4 + vtx + dimuon + secvtx); 

  chain->Draw("massC>>mass_C_aftTrig",recoMu4 + vtx + dimuon + secvtx + dz + trig);
  chain->Draw("massF>>mass_F_aftTrig",recoMu4 + vtx + dimuon + secvtx + dz + trig);
  chain->Draw("diMuonC_IsoTk_FittedVtx>>iso_C_aftTrig",recoMu4 + vtx + dimuon + secvtx + dz + trig);
  chain->Draw("diMuonF_IsoTk_FittedVtx>>iso_F_aftTrig",recoMu4 + vtx + dimuon + secvtx + dz + trig);

  TString massCCut = "&& massC>2.8 && massC<3.3";
  TString massFCut = "&& massF>2.8 && massF<3.3";

  TString LxyC0p1 = "&& diMuonC_FittedVtx_Lxy<0.1";
  TString LxyC0p05 ="&& diMuonF_FittedVtx_Lxy<0.05";
  TString LxyC0p2 = "&& diMuonC_FittedVtx_Lxy>0.05 && diMuonC_FittedVtx_Lxy<0.2";
  TString LxyC0p4 = "&& diMuonC_FittedVtx_Lxy>0.2 && diMuonC_FittedVtx_Lxy<0.4";
  TString LxyC1p0 = "&& diMuonC_FittedVtx_Lxy>0.4 && diMuonC_FittedVtx_Lxy<1.0";

  TString LxyF0p1 = "&& diMuonF_FittedVtx_Lxy<0.1";
  TString LxyF0p05 ="&& diMuonF_FittedVtx_Lxy<0.05";
  TString LxyF0p2 = "&& diMuonF_FittedVtx_Lxy>0.05 && diMuonF_FittedVtx_Lxy<0.2";
  TString LxyF0p4 = "&& diMuonF_FittedVtx_Lxy>0.2 && diMuonF_FittedVtx_Lxy<0.4";
  TString LxyF1p0 = "&& diMuonF_FittedVtx_Lxy>0.4 && diMuonF_FittedVtx_Lxy<1.0";

  TString IsoCl2 =   "&& diMuonC_IsoTk_FittedVtx<2";
  TString IsoFl2 =   "&& diMuonF_IsoTk_FittedVtx<2";
  TString IsoCg2 =   "&& diMuonC_IsoTk_FittedVtx>2";
  TString IsoFg2 =   "&& diMuonF_IsoTk_FittedVtx>2";
  TString IsoCg2ORFg2 =   "&& (diMuonC_IsoTk_FittedVtx>2 || diMuonF_IsoTk_FittedVtx>2)";

  chain->Draw("massC>>mass_C_aftTrig_cut",recoMu4 + vtx + dimuon + secvtx + dz + trig + massCCut + IsoCl2 + LxyC0p1);
  chain->Draw("massF>>mass_F_aftTrig_cut",recoMu4 + vtx + dimuon + secvtx + dz + trig + massFCut + IsoFl2 + LxyF0p1);
  
  chain->Draw("massC>>mass_C_aftTrig_cut_lxylt0p05",recoMu4 + vtx + dimuon + secvtx + dz + trig + massCCut + IsoCl2 + LxyC0p05);
  chain->Draw("massC>>mass_C_aftTrig_cut_lxylt0p2", recoMu4 + vtx + dimuon + secvtx + dz + trig + massCCut + IsoCl2 + LxyC0p2);
  chain->Draw("massC>>mass_C_aftTrig_cut_lxylt0p4", recoMu4 + vtx + dimuon + secvtx + dz + trig + massCCut + IsoCl2 + LxyC0p4);
  chain->Draw("massC>>mass_C_aftTrig_cut_lxylt1p0", recoMu4 + vtx + dimuon + secvtx + dz + trig + massCCut + IsoCl2 + LxyC1p0);

  chain->Draw("diMuonC_FittedVtx_Lxy>>diMuonC_Lxy_RegionA", 
	      recoMu4 + vtx + dimuon + secvtx + dz + trig + IsoCl2 + IsoFl2 + massCCut + massFCut);
  chain->Draw("diMuonF_FittedVtx_Lxy>>diMuonF_Lxy_RegionA", 
	      recoMu4 + vtx + dimuon + secvtx + dz + trig + IsoFl2 + IsoFl2 + massCCut + massFCut);

  chain->Draw("diMuonC_FittedVtx_Lxy>>diMuonC_Lxy_RegionBCD", 
	      recoMu4 + vtx + dimuon + secvtx + dz + trig + IsoCg2ORFg2 + massCCut + massFCut);
  chain->Draw("diMuonF_FittedVtx_Lxy>>diMuonF_Lxy_RegionBCD", 
	      recoMu4 + vtx + dimuon + secvtx + dz + trig + IsoCg2ORFg2 + massCCut + massFCut);

  chain->Draw("abs(diMuonC_FittedVtx_Rapidity-diMuonF_FittedVtx_Rapidity)>>diMuon_DeltaRapidity", 
	      recoMu4 + vtx + dimuon);
  chain->Draw("abs(diMuonC_FittedVtx_Rapidity-diMuonF_FittedVtx_Rapidity)>>diMuon_DeltaRapidity_RegionA", 
	      recoMu4 + vtx + dimuon + secvtx + dz + trig + IsoCl2 + IsoFl2 + massCCut + massFCut);
  chain->Draw("abs(diMuonC_FittedVtx_Rapidity-diMuonF_FittedVtx_Rapidity)>>diMuon_DeltaRapidity_RegionBCD", 
	      recoMu4 + vtx + dimuon + secvtx + dz + trig + IsoCg2ORFg2 + massCCut + massFCut);

  // 2D plots for the analysis
  chain->Draw("diMuonF_IsoTk_FittedVtx:diMuonC_IsoTk_FittedVtx>>Iso_dim1_vs_dim2", 
	      recoMu4 + vtx + dimuon + secvtx + dz);
  chain->Draw("diMuonF_IsoTk_FittedVtx:diMuonC_IsoTk_FittedVtx>>Iso_dim1_vs_dim2_aftmasscut", 
	      recoMu4 + vtx + dimuon + secvtx + dz + trig + massCCut + massFCut);
  chain->Draw("massF:massC>>Iso_dim1_vs_dim2", 
	      recoMu4 + vtx + dimuon + secvtx + dz + trig);

  // print numbers
  TString baseCut = recoMu4 + vtx + dimuon + secvtx + dz + trig + massCCut + massFCut;
  int nRegionA = chain->GetEntries(baseCut + "&& diMuonC_IsoTk_FittedVtx<2.0 && diMuonF_IsoTk_FittedVtx<2.0");

  int nRegionB = chain->GetEntries(baseCut + "&& diMuonC_IsoTk_FittedVtx<2.0 && (diMuonF_IsoTk_FittedVtx>2.0 && diMuonF_IsoTk_FittedVtx<12.0)");
  int nRegionB1 = chain->GetEntries(baseCut + "&& diMuonC_IsoTk_FittedVtx<2.0 && (diMuonF_IsoTk_FittedVtx>2.0 && diMuonF_IsoTk_FittedVtx<10.0)");
  int nRegionB2 = chain->GetEntries(baseCut + "&& diMuonC_IsoTk_FittedVtx<2.0 && (diMuonF_IsoTk_FittedVtx>2.0 && diMuonF_IsoTk_FittedVtx<8.0)");
  int nRegionB3 = chain->GetEntries(baseCut + "&& diMuonC_IsoTk_FittedVtx<2.0 && (diMuonF_IsoTk_FittedVtx>2.0 && diMuonF_IsoTk_FittedVtx<6.0)");

  int nRegionC = chain->GetEntries(baseCut + "&& (diMuonC_IsoTk_FittedVtx>2.0 && diMuonC_IsoTk_FittedVtx<12.0)  && (diMuonF_IsoTk_FittedVtx>2.0 && diMuonF_IsoTk_FittedVtx<12.0)");
  int nRegionC1 = chain->GetEntries(baseCut + "&& (diMuonC_IsoTk_FittedVtx>2.0 && diMuonC_IsoTk_FittedVtx<10.0) && (diMuonF_IsoTk_FittedVtx>2.0 && diMuonF_IsoTk_FittedVtx<10.0)");
  int nRegionC2 = chain->GetEntries(baseCut + "&& (diMuonC_IsoTk_FittedVtx>2.0 && diMuonC_IsoTk_FittedVtx<8.0)  && (diMuonF_IsoTk_FittedVtx>2.0 && diMuonF_IsoTk_FittedVtx<8.0)");
  int nRegionC3 = chain->GetEntries(baseCut + "&& (diMuonC_IsoTk_FittedVtx>2.0 && diMuonC_IsoTk_FittedVtx<6.0)  && (diMuonF_IsoTk_FittedVtx>2.0 && diMuonF_IsoTk_FittedVtx<6.0)");

  int nRegionD = chain->GetEntries(baseCut + "&& diMuonF_IsoTk_FittedVtx<2.0 && (diMuonC_IsoTk_FittedVtx>2.0 && diMuonC_IsoTk_FittedVtx<12.0)");
  int nRegionD1 = chain->GetEntries(baseCut + "&& diMuonF_IsoTk_FittedVtx<2.0 && (diMuonC_IsoTk_FittedVtx>2.0 && diMuonC_IsoTk_FittedVtx<10.0)");
  int nRegionD2 = chain->GetEntries(baseCut + "&& diMuonF_IsoTk_FittedVtx<2.0 && (diMuonC_IsoTk_FittedVtx>2.0 && diMuonC_IsoTk_FittedVtx<8.0)");
  int nRegionD3 = chain->GetEntries(baseCut + "&& diMuonF_IsoTk_FittedVtx<2.0 && (diMuonC_IsoTk_FittedVtx>2.0 && diMuonC_IsoTk_FittedVtx<6.0)");
  
  cout<<" Events Total(no selections)   "<<chain->GetEntries()<<endl;
  cout<<" Events Region A   "<<nRegionA<<endl;
  cout<<"                   "<<endl;  
  cout<<" Events Region B   "<<nRegionB<<endl;
  cout<<" Events Region B1   "<<nRegionB1<<endl;
  cout<<" Events Region B2   "<<nRegionB2<<endl;
  cout<<" Events Region B3   "<<nRegionB3<<endl;
  cout<<"                   "<<endl;  
  cout<<" Events Region C   "<<nRegionC<<endl;
  cout<<" Events Region C1   "<<nRegionC1<<endl;
  cout<<" Events Region C2   "<<nRegionC2<<endl;
  cout<<" Events Region C3   "<<nRegionC3<<endl;
  cout<<"                   "<<endl;  
  cout<<" Events Region D   "<<nRegionD<<endl;
  cout<<" Events Region D1   "<<nRegionD1<<endl;
  cout<<" Events Region D2   "<<nRegionD2<<endl;
  cout<<" Events Region D3   "<<nRegionD3<<endl;
  cout<<"                   "<<endl;  

  TString step0 = "";
  TString step1 = "isDiMuonHLTFired";

  TString step2 = step1 + vtx;
  TString step3 = step2 + "&& selMu0_pT>17 && fabs(selMu0_eta)<0.9";
  TString step4 = step3 + "&& selMu1_pT>8 && fabs(selMu1_eta)<2.4";
  TString step5 = step4 + "&& selMu2_pT>8 && fabs(selMu2_eta)<2.4";
  TString step6 = step5 + "&& selMu3_pT>8 && fabs(selMu3_eta)<2.4";

  TString step7 = step6 + "&& is2MuJets";
  TString step8 = step7 + "&& is2DiMuons";
  TString step9 = step8 + "&& (diMuonC_m1_FittedVtx_hitpix_l3inc[0]==1||diMuonC_m2_FittedVtx_hitpix_l3inc[1]==1) && (diMuonF_m1_FittedVtx_hitpix_l3inc[0]==1||diMuonF_m2_FittedVtx_hitpix_l3inc[1]==1)";
  TString step10 = step9 + dz;
  TString step11 = step10 + "&& diMuonC_IsoTk_FittedVtx<2.0 && diMuonF_IsoTk_FittedVtx<2.0";
  TString step12 = step11 + "&& is2DiMuonsMassOK_FittedVtx";

  cout<<" Events Passing muon selection step1   "<<chain->GetEntries(step1)<<endl;
  cout<<" Events Passing muon selection step2   "<<chain->GetEntries(step2)<<endl;
  cout<<" Events Passing muon selection step3   "<<chain->GetEntries(step3)<<endl;
  cout<<" Events Passing muon selection step4   "<<chain->GetEntries(step4)<<endl;
  cout<<" Events Passing muon selection step5   "<<chain->GetEntries(step5)<<endl;
  cout<<" Events Passing muon selection step6   "<<chain->GetEntries(step6)<<endl;
  cout<<" Events Passing muon selection step7   "<<chain->GetEntries(step7)<<endl;
  cout<<" Events Passing muon selection step8   "<<chain->GetEntries(step8)<<endl;
  cout<<" Events Passing muon selection step9   "<<chain->GetEntries(step9)<<endl;
  cout<<" Events Passing muon selection step10   "<<chain->GetEntries(step10)<<endl;
  cout<<" Events Passing muon selection step11   "<<chain->GetEntries(step11)<<endl;
  cout<<" Events Passing muon selection step12   "<<chain->GetEntries(step12)<<endl;
  
  // write the bare histograms to file
  TFile* output_root = new TFile(outputdir + "Histograms" + sample + ".root","RECREATE");

  P_t_Mu0->Write();
  P_t_Mu1->Write();
  P_t_Mu2->Write();
  P_t_Mu3->Write();

  mass_C->Write();
  mass_F->Write();

  iso_C->Write();
  iso_F->Write();

  lxy_C->Write();
  lxy_F->Write();

  eta_Mu0->Write();
  eta_Mu1->Write();
  eta_Mu2->Write();
  eta_Mu3->Write();

  P_t_Mu0_aftTrig->Write();
  P_t_Mu1_aftTrig->Write();
  P_t_Mu2_aftTrig->Write();
  P_t_Mu3_aftTrig->Write();

  mass_C_aftTrig->Write();
  mass_F_aftTrig->Write();
  
  mass_C_aftTrig_cut->Write();
  mass_F_aftTrig_cut->Write();

  mass_C_aftTrig_cut_lxylt0p05->Write();
  mass_C_aftTrig_cut_lxylt0p2->Write(); 
  mass_C_aftTrig_cut_lxylt0p4->Write(); 
  mass_C_aftTrig_cut_lxylt1p0->Write(); 

  iso_C_aftTrig->Write();
  iso_F_aftTrig->Write();

  eta_Mu0_aftTrig->Write();
  eta_Mu1_aftTrig->Write();
  eta_Mu2_aftTrig->Write();
  eta_Mu3_aftTrig->Write();

  diMuons_dz->Write();
  diMuonC_Lxy_RegionA->Write();
  diMuonF_Lxy_RegionA->Write();

  diMuonC_Lxy_RegionBCD->Write();
  diMuonF_Lxy_RegionBCD->Write();
  diMuonC_Lxy_RegionBCD_invtdz->Write();
  diMuonF_Lxy_RegionBCD_invtdz->Write();

  diMuon_DeltaRapidity->Write();
  diMuon_DeltaRapidity_RegionA->Write(); 
  diMuon_DeltaRapidity_RegionBCD->Write();
  Iso_dim1_vs_dim2->Write();
  Iso_dim1_vs_dim2_aftmasscut->Write();
  mass_dim1_vs_dim2->Write();

  output_root->Close();
}

void analysis(const std::string txtfile)
{
  jpsiScriptsSD(TString(txtfile));
}
