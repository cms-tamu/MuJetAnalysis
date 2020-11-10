//**********************************************************************
//* For Z mass shape comparison between WZ MC and MET Dataset of 2018  *
//* Run it as: root -l -b -q TriggerSF18.C                               *
//*                    Wei Shi @Aug 19, 2020, Houston                  *
//**********************************************************************
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include <vector>
#include "stdio.h"
#include "TMath.h"
#include "TGraph.h"
#include "TSystem.h"
#include "TChain.h"
#include "TBranch.h"

//local const file
#include "Constants.h"
#include "Config.h"

void TriggerSF18()
{
  //Configure inputs for year
  BKG_cfg::ConfigureInput(year);

  TLegend *txtHeader = new TLegend(.13, .935, 0.97, 1.);
  txtHeader->SetFillColor(kWhite);
  txtHeader->SetFillStyle(0);
  txtHeader->SetBorderSize(0);
  txtHeader->SetTextFont(42);
  txtHeader->SetTextSize(0.045);
  txtHeader->SetTextAlign(22);
  txtHeader->SetHeader(header);

  // Initialize empty file to access each file in the list
  TFile *file_tmp(0);
  THStack *MC_hs_Z_mass = new THStack("MC_hs_Z_mass", "");
  //For plotting summed error for above stacked plots
  TH1F *MC_Z_mass = new TH1F("MC_Z_mass", "", HM_m_bins, HM_m_min, HM_m_max);

  //WZ MC
  TString MC_file_name;
  for (int i = 0; i < 1; i++) {
    MC_file_name.Form( "%s/%s", store.Data(), MC_files[i].Data() );
    std::cout << "Opening file #"<< i+1 << ": " << MC_file_name.Data() << std::endl;
    file_tmp = TFile::Open(MC_file_name);
    if (!file_tmp) {
      std::cout << "ERROR: could not open file " << MC_file_name.Data() << std::endl;
      return;
    }

    TH1F *MCBestZMass = (TH1F*)file_tmp->Get("BestZMass")->Clone("MCBestZMass");
    MCBestZMass->Scale(MC_ScaleFactors[i]);
    MCBestZMass->SetLineColor(MC_Colors[i]);
    MCBestZMass->SetFillColor(MC_Colors[i]);
    MCBestZMass->SetMarkerColor(MC_Colors[i]);
    MC_hs_Z_mass->Add(MCBestZMass);
    MC_Z_mass->Add(MCBestZMass);

  }

  //MET Dataset
  TString DATA_file_name;
  TH1F *DATA_Z_mass = new TH1F("DATA_Z_mass", "", HM_m_bins, HM_m_min, HM_m_max);

  for (int j = 0; j < 1; j++) {
    DATA_file_name.Form( "%s/%s", store.Data(), DATA_files[j].Data() );
    std::cout << "Opening file #"<< j+1 << ": " << DATA_file_name.Data() << std::endl;
    file_tmp = TFile::Open(DATA_file_name);
    if (!file_tmp) {
      std::cout << "ERROR: could not open file " << DATA_file_name.Data() << std::endl;
      return;
    }

    TH1F *DATABestZMass = (TH1F*)file_tmp->Get("BestZMass")->Clone("DATABestZMass");
    DATA_Z_mass->Add(DATABestZMass);
  }

  //write to output file
  TFile myPlot(outFileTriggerSF, "RECREATE");

  //====================
  //= For Z dimu mass  =
  //====================
  TCanvas *CR1=new TCanvas("CR1", "CR m1", 700, 500); CR1->Clear();
  TPad *CR1pad1 = new TPad("CR1pad1", "CR1pad1", 0, 0.3, 1, 1.0);//xlow, ylow, xup, yup
  CR1pad1->SetBottomMargin(0); CR1pad1->Draw();
  TPad *CR1pad2 = new TPad("CR1pad2", "CR1pad2", 0, 0.0, 1, 0.29);
  CR1pad2->SetTopMargin(0); CR1pad2->SetBottomMargin(0.3); CR1pad2->SetGridy(); CR1pad2->Draw();
  //MC vs DATA
  CR1pad1->cd();
  //Plot stacked histogram from MC
  MC_hs_Z_mass->Draw("HIST"); MC_hs_Z_mass->SetMaximum(10000); MC_hs_Z_mass->GetYaxis()->SetTitle("Events/GeV");
  //Plot MC error
  MC_Z_mass->SetLineColor(2); MC_Z_mass->SetFillColor(2); MC_Z_mass->SetFillStyle(3004); MC_Z_mass->Draw("E2 SAME");
  Double_t MC_Z_mass_error;
  Double_t MC_Z_mass_integral = MC_Z_mass->IntegralAndError(1, HM_m_bins, MC_Z_mass_error, "");
  std::cout << "MC Z dimu mass integral = " << MC_Z_mass_integral << " +/- " << MC_Z_mass_error << std::endl;
  //Overlay data
  DATA_Z_mass->SetFillColor(1); DATA_Z_mass->SetLineColor(1); DATA_Z_mass->SetMarkerStyle(20); DATA_Z_mass->SetMarkerSize(0.6); DATA_Z_mass->Draw("E1 X0 SAME"); txtHeader->Draw("SAME");//Draw Error bars
  Double_t DATA_Z_mass_error;
  Double_t DATA_Z_mass_integral = DATA_Z_mass->IntegralAndError(1, HM_m_bins, DATA_Z_mass_error, ""); // "": width
  std::cout << "DATA Z dimu mass integral = " << DATA_Z_mass_integral << " +/- " << DATA_Z_mass_error << std::endl;
  //Build Legend
  TLegend* CR1pad1L = CR1pad1->BuildLegend();
  CR1pad1L->SetBorderSize(0); CR1pad1L->SetFillStyle(0); CR1pad1L->SetNColumns(2);
  TList *CR1pad1P = CR1pad1L->GetListOfPrimitives();
  TIter CR1pad1next(CR1pad1P);
  TObject *CR1pad1obj;
  TLegendEntry *CR1pad1li;
  int CR1pad1iEntry = 0;
  while ((CR1pad1obj = CR1pad1next())) {
    CR1pad1li = (TLegendEntry*)CR1pad1obj;
    CR1pad1iEntry++;
    if (CR1pad1iEntry==1) CR1pad1li->SetLabel("WZTo3LNu");
    if (CR1pad1iEntry==2) {CR1pad1li->SetLabel("MC Error"); CR1pad1li->SetOption("f");}
    if (CR1pad1iEntry==3) {CR1pad1li->SetLabel("Data"); CR1pad1li->SetOption("ep");}
  }
  CR1pad1->Update(); CR1pad1L->SetX1NDC(0.15); CR1pad1L->SetX2NDC(0.5); CR1pad1L->SetY1NDC(0.5); CR1pad1L->SetY2NDC(0.9); CR1pad1->Modified();
  gPad->RedrawAxis();
  CR1->cd(); CR1->Update();
  //Plot pull distribution
  CR1pad2->cd();
  //fill pull histogram
  TH1F *pull_CR_m1 = new TH1F("pull_CR_m1","", HM_m_bins, HM_m_min, HM_m_max);
  for(unsigned int iB=1; iB<=HM_m_bins; iB++){
    //pull definition: considering data and MC error
    float pull_CR_m1_iB = ( DATA_Z_mass->GetBinContent(iB) - MC_Z_mass->GetBinContent(iB) ) / sqrt( pow(DATA_Z_mass->GetBinError(iB), 2) + pow(MC_Z_mass->GetBinError(iB), 2) );
    pull_CR_m1->SetBinContent(iB, pull_CR_m1_iB );//iB starts from #1
  }
  pull_CR_m1->GetXaxis()->SetTitle("m_{#mu#mu} [GeV]");
  pull_CR_m1->GetXaxis()->SetTitleSize(15);
  pull_CR_m1->GetXaxis()->SetTitleFont(43);
  pull_CR_m1->GetXaxis()->SetTitleOffset(3.0);
  pull_CR_m1->GetXaxis()->SetLabelSize(15);// labels will be 15 pixels
  pull_CR_m1->GetXaxis()->SetLabelFont(43);// Absolute font size in pixel (precision 3)
  pull_CR_m1->GetYaxis()->SetTitle("Pull");
  pull_CR_m1->GetYaxis()->CenterTitle();
  pull_CR_m1->GetYaxis()->SetTitleSize(15);
  pull_CR_m1->GetYaxis()->SetTitleFont(43);
  pull_CR_m1->GetYaxis()->SetTitleOffset(.9);
  pull_CR_m1->GetYaxis()->SetLabelSize(15);
  pull_CR_m1->GetYaxis()->SetLabelFont(43);
  pull_CR_m1->SetMinimum(-3.5);
  pull_CR_m1->SetMaximum(3.5);
  pull_CR_m1->SetStats(0);
  pull_CR_m1->SetMarkerStyle(20);
  pull_CR_m1->SetMarkerSize(0.6);
  pull_CR_m1->Draw("P");
  CR1->Write();

  myPlot.Close();

} // End function: void
