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

void makePlot(TH1F * SPS, TH1F * DPS,
	      TString xlabel, TString cTitle,
	      float min=0, float max=99)
{
  TCanvas *cevt = new TCanvas("cevt","cevt",600,600);
  cevt->cd();

  gStyle->SetOptStat(0);
   // gStyle->SetOptTitle(0);

  
  cevt->SetFillColor(0);
  cevt->SetBorderMode(0);
  cevt->SetBorderSize(2);
  cevt->SetTickx(1);
  cevt->SetTicky(1);
  cevt->SetLeftMargin(0.15);
  cevt->SetRightMargin(0.05);
  cevt->SetTopMargin(0.07);
  cevt->SetBottomMargin(0.15);
  cevt->SetFrameFillStyle(0);
  cevt->SetFrameBorderMode(0);
  cevt->SetFrameFillStyle(0);
  cevt->SetFrameBorderMode(0);
  
  gStyle->SetTitleFontSize(0.07);
  
  gStyle->SetTitleStyle( 0 );
  gStyle->SetTitleAlign(13);
  gStyle->SetTitleX(0.);
  gStyle->SetTitleY(1.);
  gStyle->SetTitleW(1);
  gStyle->SetTitleH(0.058);
  gStyle->SetTitleBorderSize( 0 );
  
  SPS->SetTitle("      #scale[1.4]{#font[61]{CMS}}#font[52]{Simulation}                           13 TeV");
  
  SPS->GetXaxis()->SetTitle(xlabel);
  SPS->GetXaxis()->SetLabelFont(42);
  SPS->GetXaxis()->SetLabelOffset(0.007);
  SPS->GetXaxis()->SetLabelSize(0.05);
  SPS->GetXaxis()->SetTitleSize(0.06);
  SPS->GetXaxis()->SetTitleFont(42);
  SPS->GetYaxis()->SetTitle("Normalized");
  SPS->GetYaxis()->SetLabelFont(42);
  SPS->GetYaxis()->SetLabelOffset(0.007);
  SPS->GetYaxis()->SetLabelSize(0.05);
  SPS->GetYaxis()->SetTitleSize(0.06);
  SPS->GetYaxis()->SetTitleOffset(1.25);
  
  SPS->SetLineColor(kRed);
  DPS->SetLineColor(kBlue);

  DPS->SetLineStyle(5);

  SPS->SetLineWidth(2);
  DPS->SetLineWidth(2);
  
  SPS->Scale(1./SPS->Integral());
  DPS->Scale(1./DPS->Integral());

  if (cTitle=="SPS_DPS_massC" or cTitle=="SPS_DPS_massF"){
    SPS->GetXaxis()->SetRangeUser(2.8,3.4); 
  }

  if (cTitle=="SPS_DPS_isoC" or cTitle=="SPS_DPS_isoF"){
    gPad->SetLogy(); 
  }

  SPS->Draw();
  DPS->Draw("same");

  TLegend *leg = new TLegend(0.75,0.75,0.90,0.90);
  leg->SetBorderSize(0);
  leg->AddEntry(SPS,"SPS","L");
  leg->AddEntry(DPS,"DPS","L");
  leg->Draw("same");

  cevt->SaveAs("plots_SPS_DPS_SD20180512/" + cTitle + ".pdf");
  cevt->SaveAs("plots_SPS_DPS_SD20180512/" + cTitle + ".C");
}

void makeKinematicPlotsSPSDPS()
{
  gROOT->SetBatch(1);

  TFile *f_SPS = new TFile("plots_SPS_DPS_SD20180512/HistogramsSPS.root");
  TFile *f_DPS = new TFile("plots_SPS_DPS_SD20180512/HistogramsDPS1.root");
  
  TH1F *SPS_diMuon_DeltaRapidity = (TH1F*)f_SPS->Get("diMuon_DeltaRapidity");
  TH1F *DPS_diMuon_DeltaRapidity = (TH1F*)f_DPS->Get("diMuon_DeltaRapidity");

  TH1F *SPS_mass_C = (TH1F*)f_SPS->Get("mass_C");
  TH1F *DPS_mass_C = (TH1F*)f_DPS->Get("mass_C");

  TH1F *SPS_mass_F = (TH1F*)f_SPS->Get("mass_F");
  TH1F *DPS_mass_F = (TH1F*)f_DPS->Get("mass_F");

  TH1F *SPS_iso_C = (TH1F*)f_SPS->Get("iso_C");
  TH1F *DPS_iso_C = (TH1F*)f_DPS->Get("iso_C");

  TH1F *SPS_iso_F = (TH1F*)f_SPS->Get("iso_F");
  TH1F *DPS_iso_F = (TH1F*)f_DPS->Get("iso_F");
  
  TH1F *SPS_lxy_C = (TH1F*)f_SPS->Get("lxy_C");
  TH1F *DPS_lxy_C = (TH1F*)f_DPS->Get("lxy_C");

  TH1F *SPS_lxy_F = (TH1F*)f_SPS->Get("lxy_F");
  TH1F *DPS_lxy_F = (TH1F*)f_DPS->Get("lxy_F");

  TH1F *SPS_P_t_Mu0 = (TH1F*)f_SPS->Get("P_t_Mu0");
  TH1F *DPS_P_t_Mu0 = (TH1F*)f_DPS->Get("P_t_Mu0");

  makePlot(SPS_diMuon_DeltaRapidity, DPS_diMuon_DeltaRapidity, "|Y_{(#mu#mu)_{1}} - Y_{(#mu#mu)_{2}}|", "SPS_DPS_deltaRapidity");
  makePlot(SPS_mass_C, DPS_mass_C, "m_{(#mu#mu)_{1}} [GeV]", "SPS_DPS_massC");
  makePlot(SPS_mass_F, DPS_mass_F, "m_{(#mu#mu)_{2}} [GeV]", "SPS_DPS_massF");
  makePlot(SPS_iso_C, DPS_iso_C, "Iso_{(#mu#mu)_{1}} [GeV]", "SPS_DPS_isoC");
  makePlot(SPS_iso_F, DPS_iso_F, "Iso_{(#mu#mu)_{2}} [GeV]", "SPS_DPS_isoF");
  makePlot(SPS_lxy_C, DPS_lxy_C, "Lxy_{(#mu#mu)_{1}} [GeV]", "SPS_DPS_lxyC");
  makePlot(SPS_lxy_F, DPS_lxy_F, "Lxy_{(#mu#mu)_{2}} [GeV]", "SPS_DPS_lxyF");
  makePlot(SPS_P_t_Mu0, DPS_P_t_Mu0, "p_{T,1} [GeV]", "SPS_DPS_P_t_Mu0");
}
