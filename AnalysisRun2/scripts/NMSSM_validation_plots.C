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


void makePlot(TH1F * hhh, TString cTitle)
{
  gROOT->SetBatch(true);
  
  TCanvas *c = new TCanvas("c","c",800,600);
  c->cd();

  gStyle->SetOptFit(1);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  c->SetHighLightColor(2);
  c->Range(-5.7,-0.2275,4.3,1.5225);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(2);
  c->SetTickx(1);
  c->SetTicky(1);
  c->SetLeftMargin(0.17);
  c->SetRightMargin(0.03);
  c->SetTopMargin(0.07);
  c->SetBottomMargin(0.13);
  c->SetFrameFillStyle(0);
  c->SetFrameBorderMode(0);
  c->SetFrameFillStyle(0);
  c->SetFrameBorderMode(0);

  hhh->GetYaxis()->SetTitle("Fraction of events");
  hhh->GetYaxis()->SetLabelFont(42);
  hhh->GetYaxis()->SetLabelOffset(0.007);
  hhh->GetYaxis()->SetTitleSize(0.06);
  hhh->GetYaxis()->SetTitleOffset(1.35);
  hhh->GetYaxis()->SetTitleFont(42);
  hhh->GetXaxis()->SetLabelFont(42);
  hhh->GetXaxis()->SetLabelOffset(0.007);
  hhh->GetXaxis()->SetTitleSize(0.06);
  hhh->GetXaxis()->SetTitleOffset(0.95);
  hhh->GetXaxis()->SetTitleFont(42);
  hhh->DrawNormalized();

  TLegend *leg = new TLegend(0.5,0.82,0.95,0.9066667,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  TLegendEntry *entry=leg->AddEntry("NULL","#splitline{pp #rightarrow h_{1,2} #rightarrow 2a_{1} #rightarrow 4#mu}{m_{h_{1,2}} = 125 GeV, m_{a_{1}} = 0.25 GeV}","h");
  entry->SetLineColor(1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(1);
  entry->SetMarkerColor(1);
  entry->SetMarkerStyle(21);
  entry->SetMarkerSize(1);
  entry->SetTextFont(42);
  leg->Draw();

  leg = new TLegend(0.17,0.935,0.97,1,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextAlign(22);
  leg->SetTextSize(0.045);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  entry=leg->AddEntry("NULL","CMS Simulation (Pythia) 13 TeV","h");
  entry->SetLineColor(1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(1);
  entry->SetMarkerColor(1);
  entry->SetMarkerStyle(21);
  entry->SetMarkerSize(1);
  entry->SetTextFont(42);
  leg->Draw();
  c->Modified();
  c->cd();
  c->SetSelected(c);

  c->SaveAs("NMSSM_Validation_Plots/" + cTitle + ".pdf");
}


void makePlot2(TH1F * hhh, TH1F * ggg, TString cTitle)
{
  TCanvas *c = new TCanvas("c","c",800,600);
  c->cd();

  gStyle->SetOptFit(1);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  c->SetHighLightColor(2);
  c->Range(-5.7,-0.2275,4.3,1.5225);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(2);
  c->SetTickx(1);
  c->SetTicky(1);
  c->SetLeftMargin(0.17);
  c->SetRightMargin(0.03);
  c->SetTopMargin(0.07);
  c->SetBottomMargin(0.13);
  c->SetFrameFillStyle(0);
  c->SetFrameBorderMode(0);
  c->SetFrameFillStyle(0);
  c->SetFrameBorderMode(0);

  hhh->SetLineColor(kBlue);
  hhh->GetYaxis()->SetTitle("Fraction of events");
  hhh->GetYaxis()->SetLabelFont(42);
  hhh->GetYaxis()->SetLabelOffset(0.007);
  hhh->GetYaxis()->SetTitleSize(0.06);
  hhh->GetYaxis()->SetTitleOffset(1.35);
  hhh->GetYaxis()->SetTitleFont(42);
  hhh->GetXaxis()->SetLabelFont(42);
  hhh->GetXaxis()->SetLabelOffset(0.007);
  hhh->GetXaxis()->SetTitleSize(0.06);
  hhh->GetXaxis()->SetTitleOffset(0.95);
  hhh->GetXaxis()->SetTitleFont(42);
  hhh->DrawNormalized();

  ggg->SetLineColor(kRed);
  ggg->GetYaxis()->SetTitle("Fraction of events");
  ggg->GetYaxis()->SetLabelFont(42);
  ggg->GetYaxis()->SetLabelOffset(0.007);
  ggg->GetYaxis()->SetTitleSize(0.06);
  ggg->GetYaxis()->SetTitleOffset(1.35);
  ggg->GetYaxis()->SetTitleFont(42);
  ggg->GetXaxis()->SetLabelFont(42);
  ggg->GetXaxis()->SetLabelOffset(0.007);
  ggg->GetXaxis()->SetTitleSize(0.06);
  ggg->GetXaxis()->SetTitleOffset(0.95);
  ggg->GetXaxis()->SetTitleFont(42);
  ggg->DrawNormalized("same");

  hhh->SetMaximum(std::max(hhh->GetMaximum(),
			   ggg->GetMaximum()) * 1.2);
  ggg->SetMaximum(std::max(hhh->GetMaximum(),
			   ggg->GetMaximum()) * 1.2);

  hhh->SetLineStyle(1);
  ggg->SetLineStyle(2);

  hhh->DrawNormalized();
  ggg->DrawNormalized("same");

  TLegend *leg2 = new TLegend(0.5,0.5,0.9429047,0.7,NULL,"brNDC");
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.04);
  leg2->SetLineColor(1);
  leg2->SetLineStyle(1);
  leg2->SetLineWidth(1);
  leg2->SetFillColor(0);
  leg2->SetFillStyle(0);
  leg2->AddEntry(hhh,"1st dark photon (leading p_{T})","L");
  leg2->AddEntry(ggg,"2nd dark photon","L");
  leg2->Draw();

  TLegend *leg = new TLegend(0.5,0.82,0.95,0.9066667,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  TLegendEntry *entry=leg->AddEntry("NULL","#splitline{pp #rightarrow h_{1,2} #rightarrow 2a_{1} #rightarrow 4#mu}{m_{h_{1,2}} = 125 GeV, m_{a_{1}} = 0.25 GeV}","h");
  entry->SetLineColor(1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(1);
  entry->SetMarkerColor(1);
  entry->SetMarkerStyle(21);
  entry->SetMarkerSize(1);
  entry->SetTextFont(42);
  leg->Draw();

  leg = new TLegend(0.17,0.935,0.97,1,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextAlign(22);
  leg->SetTextSize(0.045);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  entry=leg->AddEntry("NULL","CMS Simulation (Pythia) 13 TeV","h");
  entry->SetLineColor(1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(1);
  entry->SetMarkerColor(1);
  entry->SetMarkerStyle(21);
  entry->SetMarkerSize(1);
  entry->SetTextFont(42);
  leg->Draw();
  c->Modified();
  c->cd();
  c->SetSelected(c);

  c->SaveAs("NMSSM_Validation_Plots/" + cTitle + ".pdf");
}





void makePlot4(TH1F * hhh, TH1F * ggg, TH1F * fff, TH1F * kkk, TString cTitle)
{
  TCanvas *c = new TCanvas("c","c",800,600);
  c->cd();

  gStyle->SetOptFit(1);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  c->SetHighLightColor(2);
  c->Range(-5.7,-0.2275,4.3,1.5225);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(2);
  c->SetTickx(1);
  c->SetTicky(1);
  c->SetLeftMargin(0.17);
  c->SetRightMargin(0.03);
  c->SetTopMargin(0.07);
  c->SetBottomMargin(0.13);
  c->SetFrameFillStyle(0);
  c->SetFrameBorderMode(0);
  c->SetFrameFillStyle(0);
  c->SetFrameBorderMode(0);

  hhh->SetLineColor(kBlue);
  hhh->GetYaxis()->SetTitle("Fraction of events");
  hhh->GetYaxis()->SetLabelFont(42);
  hhh->GetYaxis()->SetLabelOffset(0.007);
  hhh->GetYaxis()->SetTitleSize(0.06);
  hhh->GetYaxis()->SetTitleOffset(1.35);
  hhh->GetYaxis()->SetTitleFont(42);
  hhh->GetXaxis()->SetLabelFont(42);
  hhh->GetXaxis()->SetLabelOffset(0.007);
  hhh->GetXaxis()->SetTitleSize(0.06);
  hhh->GetXaxis()->SetTitleOffset(0.95);
  hhh->GetXaxis()->SetTitleFont(42);
  hhh->DrawNormalized();

  ggg->SetLineColor(kGreen+1);
  ggg->GetYaxis()->SetTitle("Fraction of events");
  ggg->GetYaxis()->SetLabelFont(42);
  ggg->GetYaxis()->SetLabelOffset(0.007);
  ggg->GetYaxis()->SetTitleSize(0.06);
  ggg->GetYaxis()->SetTitleOffset(1.35);
  ggg->GetYaxis()->SetTitleFont(42);
  ggg->GetXaxis()->SetLabelFont(42);
  ggg->GetXaxis()->SetLabelOffset(0.007);
  ggg->GetXaxis()->SetTitleSize(0.06);
  ggg->GetXaxis()->SetTitleOffset(0.95);
  ggg->GetXaxis()->SetTitleFont(42);
  ggg->DrawNormalized("same");

  fff->SetLineColor(kRed);
  fff->GetYaxis()->SetTitle("Fraction of events");
  fff->GetYaxis()->SetLabelFont(42);
  fff->GetYaxis()->SetLabelOffset(0.007);
  fff->GetYaxis()->SetTitleSize(0.06);
  fff->GetYaxis()->SetTitleOffset(1.35);
  fff->GetYaxis()->SetTitleFont(42);
  fff->GetXaxis()->SetLabelFont(42);
  fff->GetXaxis()->SetLabelOffset(0.007);
  fff->GetXaxis()->SetTitleSize(0.06);
  fff->GetXaxis()->SetTitleOffset(0.95);
  fff->GetXaxis()->SetTitleFont(42);
  fff->DrawNormalized("same");

  kkk->SetLineColor(kBlack);
  kkk->GetYaxis()->SetTitle("Fraction of events");
  kkk->GetYaxis()->SetLabelFont(42);
  kkk->GetYaxis()->SetLabelOffset(0.007);
  kkk->GetYaxis()->SetTitleSize(0.06);
  kkk->GetYaxis()->SetTitleOffset(1.35);
  kkk->GetYaxis()->SetTitleFont(42);
  kkk->GetXaxis()->SetLabelFont(42);
  kkk->GetXaxis()->SetLabelOffset(0.007);
  kkk->GetXaxis()->SetTitleSize(0.06);
  kkk->GetXaxis()->SetTitleOffset(0.95);
  kkk->GetXaxis()->SetTitleFont(42);
  kkk->DrawNormalized("same");

  float maxValue1 = std::max(hhh->GetMaximum(), ggg->GetMaximum());
  float maxValue2 = std::max(fff->GetMaximum(), kkk->GetMaximum());
  float maxValue3 = std::max(maxValue1, maxValue2);
  hhh->SetMaximum(maxValue3 * 1.2);

  hhh->SetLineStyle(1);
  ggg->SetLineStyle(2);
  fff->SetLineStyle(9);
  kkk->SetLineStyle(10);

  hhh->DrawNormalized();
  ggg->DrawNormalized("same");
  fff->DrawNormalized("same");
  kkk->DrawNormalized("same");

  TLegend *leg2 = new TLegend(0.6175166,0.5,0.9429047,0.7,NULL,"brNDC");
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.04);
  leg2->SetLineColor(1);
  leg2->SetLineStyle(1);
  leg2->SetLineWidth(1);
  leg2->SetFillColor(0);
  leg2->SetFillStyle(0);
  leg2->AddEntry(hhh,"1st muon (leading p_{T})","L");
  leg2->AddEntry(ggg,"2nd muon","L");
  leg2->AddEntry(fff,"3rd muon","L");
  leg2->AddEntry(kkk,"4th muon","L");
  leg2->Draw();

  // ci = TColor::GetColor("#0000ff");
  // entry->SetLineColor(ci);
  // entry->SetLineStyle(1);
  // entry->SetLineWidth(2);
  // entry->SetMarkerColor(1);
  // entry->SetMarkerStyle(21);
  // entry->SetMarkerSize(1);
  // entry->SetTextFont(42);
  // entry=leg->AddEntry(ggg,"2nd muon","L");

  // ci = TColor::GetColor("#00ff00");
  // entry->SetLineColor(ci);
  // entry->SetLineStyle(2);
  // entry->SetLineWidth(2);
  // entry->SetMarkerColor(1);
  // entry->SetMarkerStyle(21);
  // entry->SetMarkerSize(1);
  // entry->SetTextFont(42);
  // entry=leg->AddEntry(fff,"3rd muon","L");

  // ci = TColor::GetColor("#ff0000");
  // entry->SetLineColor(ci);
  // entry->SetLineStyle(3);
  // entry->SetLineWidth(2);
  // entry->SetMarkerColor(1);
  // entry->SetMarkerStyle(21);
  // entry->SetMarkerSize(1);
  // entry->SetTextFont(42);
  // entry=leg->AddEntry(kkk,"4th muon","L");
  // entry->SetLineColor(1);
  // entry->SetLineStyle(4);
  // entry->SetLineWidth(2);
  // entry->SetMarkerColor(1);
  // entry->SetMarkerStyle(21);
  // entry->SetMarkerSize(1);
  // entry->SetTextFont(42);


  TLegend *leg = new TLegend(0.5,0.82,0.95,0.9066667,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  TLegendEntry *entry=leg->AddEntry("NULL","#splitline{pp #rightarrow h_{1,2} #rightarrow 2a_{1} #rightarrow 4#mu}{m_{h_{1,2}} = 125 GeV, m_{a_{1}} = 0.25 GeV}","h");
  entry->SetLineColor(1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(1);
  entry->SetMarkerColor(1);
  entry->SetMarkerStyle(21);
  entry->SetMarkerSize(1);
  entry->SetTextFont(42);
  leg->Draw();

  leg = new TLegend(0.17,0.935,0.97,1,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextAlign(22);
  leg->SetTextSize(0.045);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  entry=leg->AddEntry("NULL","CMS Simulation (Pythia) 13 TeV","h");
  entry->SetLineColor(1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(1);
  entry->SetMarkerColor(1);
  entry->SetMarkerStyle(21);
  entry->SetMarkerSize(1);
  entry->SetTextFont(42);
  leg->Draw();
  c->Modified();
  c->cd();
  c->SetSelected(c);

  c->SaveAs("NMSSM_Validation_Plots/" + cTitle + ".pdf");
}



int k = -1;
void efficiency(const std::vector<std::string>& dirNames)
{

  TString mH_string;
  TString mA_string;

  //  bool verbose(false);
  bool verbose(false);
  //	TString dirname(fileName);
  TChain* chain = new TChain("dummy");
  TString ext("out_ana_");
  
  if (dirNames.size()==0) {
    cout << "No dirnames" << endl;
    return;
  }

  cout<<" dirNames  "<<dirNames[0]<<endl;
  decodeFileNMSSMNameMany(dirNames, mH_string, mA_string);

  TString fileName;
  fileName = "NMSSM_mH_" + mH_string + "_mA_" + mA_string;

  cout<<" Sample   "<<fileName<<endl;
  
  if (mH_string != "125") return;
  if (mA_string != "0p25") return;

  // add files to the chain
  addfilesMany(chain, dirNames, ext);

  
  //Initialize Variables and counters
  // TFile *f[20]; //A root file is a suit of consecutive data records
  // TTree *t[20]; //comsists of a list of independent branches (Tbranch); one or multiple branches
  char nameFile[50]; //refers to a block of characters?
  
  // Bosons
  Float_t genH_m;
  Float_t genH_px;
  Float_t genH_py;
  Float_t genH_pz;
  Float_t genH_eta;
  Float_t genH_phi;
  
  Float_t genA0_m;
  Float_t genA0_pT;
  Float_t genA0_px;
  Float_t genA0_py;
  Float_t genA0_pz;
  Float_t genA0_eta;
  Float_t genA0_phi;
  
  Float_t genA0_Lx;
  Float_t genA0_Ly;
  Float_t genA0_Lz;
  Float_t genA0_Lxy;
  Float_t genA0_L;
  
  Float_t genA1_m;
  Float_t genA1_pT;
  Float_t genA1_px;
  Float_t genA1_py;
  Float_t genA1_pz;
  Float_t genA1_eta;
  Float_t genA1_phi;
  
  Float_t genA1_Lx;
  Float_t genA1_Ly;
  Float_t genA1_Lz;
  Float_t genA1_Lxy;
  Float_t genA1_L;
  
  Float_t genA0Mu0_pT;
  Float_t genA0Mu1_pT;
  Float_t genA1Mu0_pT;
  Float_t genA1Mu1_pT;
  
  Float_t genA0Mu0_px;
  Float_t genA0Mu1_px;
  Float_t genA1Mu0_px;
  Float_t genA1Mu1_px;

  Float_t genA0Mu0_py;
  Float_t genA0Mu1_py;
  Float_t genA1Mu0_py;
  Float_t genA1Mu1_py;

  Float_t genA0Mu0_pz;
  Float_t genA0Mu1_pz;
  Float_t genA1Mu0_pz;
  Float_t genA1Mu1_pz;

  Float_t genA0Mu0_eta;
  Float_t genA0Mu1_eta;
  Float_t genA1Mu0_eta;
  Float_t genA1Mu1_eta;
  
  Float_t genA0Mu0_phi;
  Float_t genA0Mu1_phi;
  Float_t genA1Mu0_phi;
  Float_t genA1Mu1_phi;

  TH1F * h_genH_m = new TH1F("h_genH_m","CMS Simulation (Pythia) 13 TeV; Mass of h_{1,2} [GeV]; Fraction of events",100,100,150);
  TH1F * h_genH_px = new TH1F("h_genH_px","CMS Simulation (Pythia) 13 TeV; p_{x} of h_{1,2} [GeV]; Fraction of events",100,-500,500);
  TH1F * h_genH_py = new TH1F("h_genH_py","CMS Simulation (Pythia) 13 TeV; p_{y} of h_{1,2} [GeV]; Fraction of events",100,-500,500);
  TH1F * h_genH_pz = new TH1F("h_genH_pz","CMS Simulation (Pythia) 13 TeV; p_{z} of h_{1,2} [GeV]; Fraction of events",100,-500,500);
  TH1F * h_genH_eta = new TH1F("h_genH_eta","CMS Simulation (Pythia) 13 TeV; #eta of h_{1,2}; Fraction of events",100,-4,4);
  TH1F * h_genH_phi = new TH1F("h_genH_phi","CMS Simulation (Pythia) 13 TeV; #phi of h_{1,2}; Fraction of events",100,-3.2,3.2);
  
  TH1F * h_genA0_m = new TH1F("h_genA0_m","CMS Simulation (Pythia) 13 TeV; Mass of a_{1} [GeV]; Fraction of events",10,0,0.5);
  TH1F * h_genA0_pT = new TH1F("h_genA0_pT","CMS Simulation (Pythia) 13 TeV; p_{T} of a_{1} [GeV]; Fraction of events",100,0,200);
  TH1F * h_genA0_px = new TH1F("h_genA0_px","CMS Simulation (Pythia) 13 TeV; p_{x} of a_{1} [GeV]; Fraction of events",100,-100,100);
  TH1F * h_genA0_py = new TH1F("h_genA0_py","CMS Simulation (Pythia) 13 TeV; p_{y} of a_{1} [GeV]; Fraction of events",100,-100,100);
  TH1F * h_genA0_pz = new TH1F("h_genA0_pz","CMS Simulation (Pythia) 13 TeV; p_{z} of a_{1} [GeV]; Fraction of events",100,-100,100);
  TH1F * h_genA0_eta = new TH1F("h_genA0_eta","CMS Simulation (Pythia) 13 TeV; #eta of a_{1}; Fraction of events",100,-4,4);
  TH1F * h_genA0_phi = new TH1F("h_genA0_phi","CMS Simulation (Pythia) 13 TeV; #phi of a_{1}; Fraction of events",100,-3.2,3.2);
  
  TH1F * h_genA1_m = new TH1F("h_genA1_m","CMS Simulation (Pythia) 13 TeV; Mass of a_{1} [GeV]; Fraction of events",10,0,0.5);
  TH1F * h_genA1_pT = new TH1F("h_genA1_pT","CMS Simulation (Pythia) 13 TeV; p_{T} of a_{1} [GeV]; Fraction of events",100,0,200);
  TH1F * h_genA1_px = new TH1F("h_genA1_px","CMS Simulation (Pythia) 13 TeV; p_{x} of a_{1} [GeV]; Fraction of events",100,-100,100);
  TH1F * h_genA1_py = new TH1F("h_genA1_py","CMS Simulation (Pythia) 13 TeV; p_{y} of a_{1} [GeV]; Fraction of events",100,-100,100);
  TH1F * h_genA1_pz = new TH1F("h_genA1_pz","CMS Simulation (Pythia) 13 TeV; p_{z} of a_{1} [GeV]; Fraction of events",100,-100,100);
  TH1F * h_genA1_eta = new TH1F("h_genA1_eta","CMS Simulation (Pythia) 13 TeV; #eta of a_{1}; Fraction of events",100,-4,4);
  TH1F * h_genA1_phi = new TH1F("h_genA1_phi","CMS Simulation (Pythia) 13 TeV; #phi of a_{1}; Fraction of events",100,-3.2,3.2);

  TH1F * h_genA0Mu0_pT = new TH1F("h_genA0Mu0_pT","CMS Simulation (Pythia) 13 TeV; p_{T} of #mu [GeV]; Fraction of events",100,0,200);
  TH1F * h_genA0Mu1_pT = new TH1F("h_genA0Mu1_pT","CMS Simulation (Pythia) 13 TeV; p_{T} of #mu [GeV]; Fraction of events",100,0,200);
  TH1F * h_genA1Mu0_pT = new TH1F("h_genA1Mu0_pT","CMS Simulation (Pythia) 13 TeV; p_{T} of #mu [GeV]; Fraction of events",100,0,200);
  TH1F * h_genA1Mu1_pT = new TH1F("h_genA1Mu1_pT","CMS Simulation (Pythia) 13 TeV; p_{T} of #mu [GeV]; Fraction of events",100,0,200);
  
  TH1F * h_genA0Mu0_px = new TH1F("h_genA0Mu0_px","CMS Simulation (Pythia) 13 TeV; p_{x} of #mu [GeV]; Fraction of events",100,-100,100);
  TH1F * h_genA0Mu1_px = new TH1F("h_genA0Mu1_px","CMS Simulation (Pythia) 13 TeV; p_{x} of #mu [GeV]; Fraction of events",100,-100,100);
  TH1F * h_genA1Mu0_px = new TH1F("h_genA1Mu0_px","CMS Simulation (Pythia) 13 TeV; p_{x} of #mu [GeV]; Fraction of events",100,-100,100);
  TH1F * h_genA1Mu1_px = new TH1F("h_genA1Mu1_px","CMS Simulation (Pythia) 13 TeV; p_{x} of #mu [GeV]; Fraction of events",100,-100,100);

  TH1F * h_genA0Mu0_py = new TH1F("h_genA0Mu0_py","CMS Simulation (Pythia) 13 TeV; p_{y} of #mu [GeV]; Fraction of events",100,-100,100);
  TH1F * h_genA0Mu1_py = new TH1F("h_genA0Mu1_py","CMS Simulation (Pythia) 13 TeV; p_{y} of #mu [GeV]; Fraction of events",100,-100,100);
  TH1F * h_genA1Mu0_py = new TH1F("h_genA1Mu0_py","CMS Simulation (Pythia) 13 TeV; p_{y} of #mu [GeV]; Fraction of events",100,-100,100);
  TH1F * h_genA1Mu1_py = new TH1F("h_genA1Mu1_py","CMS Simulation (Pythia) 13 TeV; p_{y} of #mu [GeV]; Fraction of events",100,-100,100);

  TH1F * h_genA0Mu0_pz = new TH1F("h_genA0Mu0_pz","CMS Simulation (Pythia) 13 TeV; p_{z} of #mu [GeV]; Fraction of events",100,-100,100);
  TH1F * h_genA0Mu1_pz = new TH1F("h_genA0Mu1_pz","CMS Simulation (Pythia) 13 TeV; p_{z} of #mu [GeV]; Fraction of events",100,-100,100);
  TH1F * h_genA1Mu0_pz = new TH1F("h_genA1Mu0_pz","CMS Simulation (Pythia) 13 TeV; p_{z} of #mu [GeV]; Fraction of events",100,-100,100);
  TH1F * h_genA1Mu1_pz = new TH1F("h_genA1Mu1_pz","CMS Simulation (Pythia) 13 TeV; p_{z} of #mu [GeV]; Fraction of events",100,-100,100);

  TH1F * h_genA0Mu0_eta = new TH1F("h_genA0Mu0_eta","CMS Simulation (Pythia) 13 TeV; #eta of #mu; Fraction of events",100,-4,4);
  TH1F * h_genA0Mu1_eta = new TH1F("h_genA0Mu1_eta","CMS Simulation (Pythia) 13 TeV; #eta of #mu; Fraction of events",100,-4,4);
  TH1F * h_genA1Mu0_eta = new TH1F("h_genA1Mu0_eta","CMS Simulation (Pythia) 13 TeV; #eta of #mu; Fraction of events",100,-4,4);
  TH1F * h_genA1Mu1_eta = new TH1F("h_genA1Mu1_eta","CMS Simulation (Pythia) 13 TeV; #eta of #mu; Fraction of events",100,-4,4);
  
  TH1F * h_genA0Mu0_phi = new TH1F("h_genA0Mu0_phi","CMS Simulation (Pythia) 13 TeV; #phi of #mu; Fraction of events",100,-3.2,3.2);
  TH1F * h_genA0Mu1_phi = new TH1F("h_genA0Mu1_phi","CMS Simulation (Pythia) 13 TeV; #phi of #mu; Fraction of events",100,-3.2,3.2);
  TH1F * h_genA1Mu0_phi = new TH1F("h_genA1Mu0_phi","CMS Simulation (Pythia) 13 TeV; #phi of #mu; Fraction of events",100,-3.2,3.2);
  TH1F * h_genA1Mu1_phi = new TH1F("h_genA1Mu1_phi","CMS Simulation (Pythia) 13 TeV; #phi of #mu; Fraction of events",100,-3.2,3.2);

  TObjArray *fileElements=chain->GetListOfFiles();
  TIter next(fileElements);
  TChainElement *chEl=0;
  
  k++;
  
  while ((chEl=(TChainElement*)next())) {  //loopforfiles
     if (verbose) std::cout << "running on file " << chEl->GetTitle() << std::endl;
     TFile* myfile = new TFile(chEl->GetTitle());
     if (!myfile) {
       if (verbose) std::cout << "File " << chEl->GetTitle() << " does not exist" << std::endl;
       continue;
     }
     if (verbose) std::cout << "Loading directory cutFlowAnalyzerPXBL3PXFL2" << std::endl;
     myfile->cd("cutFlowAnalyzerPXBL3PXFL2");
     
     TTree *t = (TTree*)myfile->Get("cutFlowAnalyzerPXBL3PXFL2/Events");
     if (!t) {
       if (verbose) std::cout << "Tree cutFlowAnalyzerPXBL3PXFL2/Events does not exist" << std::endl;
       continue;
     }
     
     if (verbose) cout<<"  Events  "<<t->GetEntries()<<endl;
     
     int nentries;
     
     // 5) allocate var to branch
     t->SetBranchAddress("genH_m",&genH_m);
     t->SetBranchAddress("genH_px",&genH_px);
     t->SetBranchAddress("genH_py",&genH_py);
     t->SetBranchAddress("genH_pz",&genH_pz);
     t->SetBranchAddress("genH_eta",&genH_eta);
     t->SetBranchAddress("genH_phi",&genH_phi);
     
     t->SetBranchAddress("genA0_m",&genA0_m);
     t->SetBranchAddress("genA0_px",&genA0_px);
     t->SetBranchAddress("genA0_py",&genA0_py);
     t->SetBranchAddress("genA0_pz",&genA0_pz);
     t->SetBranchAddress("genA0_eta",&genA0_eta);
     t->SetBranchAddress("genA0_phi",&genA0_phi);
     
     t->SetBranchAddress("genA1_m",&genA1_m);
     t->SetBranchAddress("genA1_px",&genA1_px);
     t->SetBranchAddress("genA1_py",&genA1_py);
     t->SetBranchAddress("genA1_pz",&genA1_pz);
     t->SetBranchAddress("genA1_eta",&genA1_eta);
     t->SetBranchAddress("genA1_phi",&genA1_phi);
     
     t->SetBranchAddress("genA0Mu0_px",&genA0Mu0_px);
     t->SetBranchAddress("genA0Mu1_px",&genA0Mu1_px);
     t->SetBranchAddress("genA1Mu0_px",&genA1Mu0_px);
     t->SetBranchAddress("genA1Mu1_px",&genA1Mu1_px);

     t->SetBranchAddress("genA0Mu0_py",&genA0Mu0_py);
     t->SetBranchAddress("genA0Mu1_py",&genA0Mu1_py);
     t->SetBranchAddress("genA1Mu0_py",&genA1Mu0_py);
     t->SetBranchAddress("genA1Mu1_py",&genA1Mu1_py);

     t->SetBranchAddress("genA0Mu0_pz",&genA0Mu0_pz);
     t->SetBranchAddress("genA0Mu1_pz",&genA0Mu1_pz);
     t->SetBranchAddress("genA1Mu0_pz",&genA1Mu0_pz);
     t->SetBranchAddress("genA1Mu1_pz",&genA1Mu1_pz);

     t->SetBranchAddress("genA0Mu0_eta",&genA0Mu0_eta);
     t->SetBranchAddress("genA0Mu1_eta",&genA0Mu1_eta);
     t->SetBranchAddress("genA1Mu0_eta",&genA1Mu0_eta);
     t->SetBranchAddress("genA1Mu1_eta",&genA1Mu1_eta);

     t->SetBranchAddress("genA0Mu0_phi",&genA0Mu0_phi);
     t->SetBranchAddress("genA0Mu1_phi",&genA0Mu1_phi);
     t->SetBranchAddress("genA1Mu0_phi",&genA1Mu0_phi);
     t->SetBranchAddress("genA1Mu1_phi",&genA1Mu1_phi);

     nentries = t->GetEntries(); //no of entries
     
     for(int i=0;i<nentries;i++){ //loop for number of events
       t->GetEntry(i);

       if (i%1000==0) cout << "Processing event " << i << endl;

       h_genH_m->Fill(genH_m);
       h_genH_px->Fill(genH_px);
       h_genH_py->Fill(genH_py);
       h_genH_pz->Fill(genH_pz);
       h_genH_eta->Fill(genH_eta);
       h_genH_phi->Fill(genH_phi);
       
       genA0_pT = sqrt(genA0_px*genA0_px + genA0_py*genA0_py + genA0_pz*genA0_pz);
       genA1_pT = sqrt(genA1_px*genA1_px + genA1_py*genA1_py + genA1_pz*genA1_pz);

       h_genA0_m->Fill(genA0_m);
       h_genA0_pT->Fill(genA0_pT);
       h_genA0_px->Fill(genA0_px);
       h_genA0_py->Fill(genA0_py);
       h_genA0_pz->Fill(genA0_pz);
       h_genA0_eta->Fill(genA0_eta);
       h_genA0_phi->Fill(genA0_phi);
       
       h_genA1_m->Fill(genA1_m);
       h_genA1_pT->Fill(genA1_pT);
       h_genA1_px->Fill(genA1_px);
       h_genA1_py->Fill(genA1_py);
       h_genA1_pz->Fill(genA1_pz);
       h_genA1_eta->Fill(genA1_eta);
       h_genA1_phi->Fill(genA1_phi);

       genA0Mu0_pT = sqrt(genA0Mu0_px*genA0Mu0_px + 
			  genA0Mu0_py*genA0Mu0_py + 
			  genA0Mu0_pz*genA0Mu0_pz);
       genA0Mu1_pT = sqrt(genA0Mu1_px*genA0Mu1_px + 
			  genA0Mu1_py*genA0Mu1_py + 
			  genA0Mu1_pz*genA0Mu1_pz);

       genA1Mu0_pT = sqrt(genA1Mu0_px*genA1Mu0_px + 
			  genA1Mu0_py*genA1Mu0_py + 
			  genA1Mu0_pz*genA1Mu0_pz);
       genA1Mu1_pT = sqrt(genA1Mu1_px*genA1Mu1_px + 
			  genA1Mu1_py*genA1Mu1_py + 
			  genA1Mu1_pz*genA1Mu1_pz);

       h_genA0Mu0_pT->Fill(genA0Mu0_pT);
       h_genA0Mu1_pT->Fill(genA0Mu1_pT);
       h_genA1Mu0_pT->Fill(genA1Mu0_pT);
       h_genA1Mu1_pT->Fill(genA1Mu1_pT);
       
       h_genA0Mu0_px->Fill(genA0Mu0_px);
       h_genA0Mu1_px->Fill(genA0Mu1_px);
       h_genA1Mu0_px->Fill(genA1Mu0_px);
       h_genA1Mu1_px->Fill(genA1Mu1_px);

       h_genA0Mu0_py->Fill(genA0Mu0_py);
       h_genA0Mu1_py->Fill(genA0Mu1_py);
       h_genA1Mu0_py->Fill(genA1Mu0_py);
       h_genA1Mu1_py->Fill(genA1Mu1_py);

       h_genA0Mu0_pz->Fill(genA0Mu0_pz);
       h_genA0Mu1_pz->Fill(genA0Mu1_pz);
       h_genA1Mu0_pz->Fill(genA1Mu0_pz);
       h_genA1Mu1_pz->Fill(genA1Mu1_pz);

       h_genA0Mu0_eta->Fill(genA0Mu0_eta);
       h_genA0Mu1_eta->Fill(genA0Mu1_eta);
       h_genA1Mu0_eta->Fill(genA1Mu0_eta);
       h_genA1Mu1_eta->Fill(genA1Mu1_eta);

       h_genA0Mu0_phi->Fill(genA0Mu0_phi);
       h_genA0Mu1_phi->Fill(genA0Mu1_phi);
       h_genA1Mu0_phi->Fill(genA1Mu0_phi);
       h_genA1Mu1_phi->Fill(genA1Mu1_phi);
     }
  }
  
  cout<<"  Here is where the plotting starts  "<<endl;
 
  makePlot(h_genH_m, "h_genH_m");
  makePlot(h_genH_px, "h_genH_px");
  makePlot(h_genH_py, "h_genH_py");
  makePlot(h_genH_pz, "h_genH_pz");
  makePlot(h_genH_phi, "h_genH_phi");
  makePlot(h_genH_eta, "h_genH_eta");

  makePlot2(h_genA0_m, h_genA1_m, "h_genA_m");
  makePlot2(h_genA0_pT, h_genA1_pT, "h_genA_pT");
  makePlot2(h_genA0_px, h_genA1_px, "h_genA_px");
  makePlot2(h_genA0_py, h_genA1_py, "h_genA_py");
  makePlot2(h_genA0_pz, h_genA1_pz, "h_genA_pz");
  makePlot2(h_genA0_eta, h_genA1_eta, "h_genA_eta");
  makePlot2(h_genA0_phi, h_genA1_phi, "h_genA_phi");

  makePlot4(h_genA0Mu0_pT, h_genA0Mu1_pT, h_genA1Mu0_pT, h_genA1Mu1_pT, "h_genAMu_pT");
  makePlot4(h_genA0Mu0_px, h_genA0Mu1_px, h_genA1Mu0_px, h_genA1Mu1_px, "h_genAMu_px");
  makePlot4(h_genA0Mu0_py, h_genA0Mu1_py, h_genA1Mu0_py, h_genA1Mu1_py, "h_genAMu_py");
  makePlot4(h_genA0Mu0_pz, h_genA0Mu1_pz, h_genA1Mu0_pz, h_genA1Mu1_pz, "h_genAMu_pz");
  makePlot4(h_genA0Mu0_eta, h_genA0Mu1_eta, h_genA1Mu0_eta, h_genA1Mu1_eta, "h_genAMu_eta");
  makePlot4(h_genA0Mu0_phi, h_genA0Mu1_phi, h_genA1Mu0_phi, h_genA1Mu1_phi, "h_genAMu_phi");
}

 

void NMSSM_validation_plots()
{
  std::vector< std::vector<string> > NMSSM_v;
  readTextFileWithSamples("NMSSM_125_0p25.txt", NMSSM_v);

  for(const auto& v: NMSSM_v) {
    for (const auto& p: v){
      cout << p << endl;
    }
    efficiency(v);
  }
}
