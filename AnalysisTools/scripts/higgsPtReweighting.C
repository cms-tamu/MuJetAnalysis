#include <iostream>
#include "TCanvas.h"
#include "TROOT.h"
#include "TH1F.h"


// This is the script that was used to perform this Higgs pT reweighting study for HIG-13-010

void higgsPtReweighting() {


  TCanvas* c1 = new TCanvas("c1","Example",800,600);  

  c1->SetFillColor(0);
  gStyle->SetPalette(1);

  gStyle->SetOptStat(0);  
  // gStyle->SetOptFit(1111);
  // gStyle->SetOptStat("emr");

  Float_t HiggsPt;

  Int_t event;
  Int_t run;
  Int_t lumi;

  Bool_t is2DiMuonsVtxOK;
  Bool_t is2DiMuonsDzOK;
  Bool_t is2DiMuonHLTFired;
  Bool_t is2DiMuonsMassOK;
  Bool_t is2DiMuonsIsoTkOK;
  Int_t b_2mjets;
  Int_t b_4recm;
  Int_t b_2dimuon;

  TString fname = "DarkSUSY_0250_ctau0";

  TFile *f = new TFile(fname+".root");
  TFile *g = new TFile("HRes_weight_pTH_mH125_8TeV.root");

  f->cd("anatraj");

  TTree *t = (TTree*)f->Get("anatraj/Events");

  TH1F *higgsPt = new TH1F("higgsPt", "", 500, 0, 500);
  TH1F *higgsPt_weighted = new TH1F("higgsPt_weighted", "", 500, 0, 500);


  t->SetBranchAddress("HiggsPt",&HiggsPt); 

  t->SetBranchAddress("event", &event);
  t->SetBranchAddress("run", &run);
  t->SetBranchAddress("lumi", &lumi);

  t->SetBranchAddress("is2DiMuonsVtxOK", &is2DiMuonsVtxOK);
  t->SetBranchAddress("is2DiMuonsDzOK", &is2DiMuonsDzOK);
  t->SetBranchAddress("is2DiMuonHLTFired", &is2DiMuonHLTFired);
  t->SetBranchAddress("is2DiMuonsMassOK", &is2DiMuonsMassOK);
  t->SetBranchAddress("is2DiMuonsIsoTkOK", &is2DiMuonsIsoTkOK);
  t->SetBranchAddress("2mjets", &b_2mjets);
  t->SetBranchAddress("2dimuon", &b_2dimuon);
  t->SetBranchAddress("4recm", &b_4recm);


  std::cout<<"Events  "<<t->GetEntries()<<std::endl;
  Int_t nentries = t->GetEntries();

  for(int k=0;k<nentries;k++){
    t->GetEntry(k);
    if (is2DiMuonsVtxOK && is2DiMuonsDzOK && is2DiMuonHLTFired && is2DiMuonsMassOK && is2DiMuonsIsoTkOK && b_2mjets && b_2dimuon && b_4recm){
      higgsPt->Fill(HiggsPt);
    }
  }
 

  TLegend *legend2 = new TLegend(.60,.85,.78,.70); legend2->SetFillColor(0); legend2->SetMargin(0.4);
  c1->cd();

  c1->cd();
  c1->SetLogy();

  // higgsPt->Scale(1/higgsPt->GetEntries());
  higgsPt->SetLineColor(kRed);higgsPt->SetLineWidth(3);
  // higgsPt->Draw();
  // higgsPt->Fit("gaus");
  // higgsPt->GetFunction("gaus")->SetLineColor(kBlack);
  // higgsPt->GetFunction("gaus")->SetLineStyle(2);

  TLegend *legend = new TLegend(.60,.85,.85,.70); legend->SetFillColor(0); legend->SetMargin(0.4);
  g->cd();
  TH1F *  Nominal = (TH1F*)g->Get("Nominal");
  Nominal->SetLineColor(kGreen+3);

  for (int i = 0; i < 500; ++i){
    double temp1 = higgsPt->GetBinContent(i);
    double temp2 = Nominal->GetBinContent(i);
    higgsPt_weighted->SetBinContent(i, temp1*temp2);
  }

  double hr = higgsPt->Integral();
  double hrw =  higgsPt_weighted->Integral();
  double errn;
  higgsPt->IntegralAndError(0, 500, errn);
  double err;
  higgsPt_weighted->IntegralAndError(0, 500, err);

  higgsPt_weighted->SetLineColor(kBlack);
  higgsPt_weighted->SetLineStyle(2);
  higgsPt_weighted->SetLineWidth(3);
  higgsPt->SetLineStyle(2);
  higgsPt->SetLineWidth(3);
  // higgsPt_weighted->Draw("same");

  TH1F *hnew = higgsPt->Rebin(10,"hnew");
  TH1F *hnew_rw = higgsPt_weighted->Rebin(10,"hnew_rw");

  hnew->Draw();

  TH1D* RatioP = (TH1D*)hnew->Clone();
  RatioP->Divide(hnew_rw);

  RatioP->SetLineColor(kBlue);

  legend->AddEntry(hnew,"Nominal","L");
  legend->AddEntry(hnew_rw,"Reweighted","L");
  legend->AddEntry(Nominal,"Weight function","L");
  legend->AddEntry(RatioP,"Ratio","L");
  legend->Draw("same");

  hnew->GetXaxis()->SetTitle("Higgs p_{T} [GeV]");
  // hnew->SetTitle("m(#gamma_{D}) = 0.25 GeV, c#tau = 2 mm");
  hnew->GetYaxis()->SetTitle("Events / 10 GeV");
  // hnew->GetYaxis()->SetTitleOffset(1.2);
  // hnew->GetXaxis()->SetTitleOffset(1.2);
  hnew->GetYaxis()->SetRangeUser(0.5,100000);
  hnew->GetXaxis()->SetRangeUser(0,500);

  hnew_rw->Draw("same");
  Nominal->Draw("same");

  c1->SetFillColor(kWhite);
  c1->Update();
  // c1->GetFrame()->SetFillColor(kWhite);
  // c1->GetFrame()->SetBorderSize(12);
  // c1->Modified();
  c1->Print(fname + "_higgsPt.png");
  c1->Print(fname + "_higgsPt.pdf");
  c1->Clear();


  TLegend *legend3 = new TLegend(.60,.85,.85,.70); legend3->SetFillColor(0); legend3->SetMargin(0.4);

  g->cd();
  TH1F *  Up = (TH1F*)g->Get("Up");
  Up->SetLineColor(kOrange+3);
  TH1F *  Down = (TH1F*)g->Get("Down");
  Down->SetLineColor(kAzure+1);

  // c1->SetLogy(false);

  // c1->cd();
  // c1->SetBottomMargin(0.1);
  // c1->SetLeftMargin(0.13);
  // Nominal->Draw();
  // Nominal->GetXaxis()->SetTitle("Higgs p_{T} [GeV]");
  // Nominal->GetYaxis()->SetTitle("Reweighting value");
  // Nominal->GetXaxis()->SetLabelSize(0.034);
  // Nominal->GetYaxis()->SetLabelSize(0.034);
  // Nominal->GetXaxis()->SetTitleSize(0.034);
  // Nominal->GetYaxis()->SetTitleSize(0.034);
  // Nominal->GetYaxis()->SetRangeUser(0,1.2);
  // // Up->Draw("same");
  // // Down->Draw("same");

  // // legend3->AddEntry(Nominal,"Nominal","L");
  // // legend3->AddEntry(Up,"Up","L");
  // // legend3->AddEntry(Down,"Down","L");
  // // legend3->Draw("same");

  // c1->Print(fname + "_weights_nominal.png");
  // c1->Print(fname + "_weights_nominal.pdf");
  // c1->Clear();

  // c1->SetLogy();


  TPad *c1_1 = new TPad("c1_1", "c1_1",0 ,0, 1,1);
  c1_1->Draw();
  c1_1->cd();

  c1_1->SetLogy();
  c1_1->SetLeftMargin(0.1);
  c1_1->SetRightMargin(0.04);
  c1_1->SetTopMargin(0.04);
  c1_1->SetBottomMargin(0.35);

  g->cd();
  TH1F *  NewNominal = (TH1F*)g->Get("Nominal");
  NewNominal->SetLineColor(kGreen+3);

  hnew->Draw("same");
  hnew_rw->Draw("same");
  NewNominal->Draw("same");
  legend->Draw("same");

  TPad *c1_2 = new TPad("c1_2", "c1_2",0,0,1,0.35);
  c1_2->Draw();
  c1_2->cd();
  
  c1_2->SetLogy(0);
  c1_2->SetBorderMode(0);
  c1_2->SetTickx(1);
  c1_2->SetTicky(1);
  
  c1_2->SetLeftMargin(0.1);
  c1_2->SetRightMargin(0.04);
  c1_2->SetTopMargin(0.);
  c1_2->SetBottomMargin(0.32);
  
  
  TH1D* Ratio = (TH1D*)hnew_rw->Clone();
  Ratio->Divide(hnew);

  Ratio->SetLineColor(kBlue);
  Ratio->SetLineWidth(3);
  
  int xmin=0;
  Ratio->GetXaxis()->SetRangeUser(0, 500 );
  Ratio->GetYaxis()->SetRangeUser(0, 1.5 );
  Ratio->SetTitle(0);
  Ratio->GetXaxis()->SetTitle("Higgs p_{T} [GeV]");
  Ratio->GetXaxis()->SetLabelSize(0.10);
  Ratio->GetXaxis()->SetLabelOffset(0.0);
  Ratio->GetXaxis()->SetTitleSize(0.1);
  Ratio->GetXaxis()->SetTitleOffset(1.1);

  Ratio->GetYaxis()->SetTitle("Rew./Nom.");
  Ratio->GetYaxis()->SetTitleOffset(0.3);
  Ratio->GetYaxis()->CenterTitle(1);
  Ratio->GetYaxis()->SetTitleSize(0.1);
  Ratio->GetYaxis()->SetLabelSize(0.09);
  Ratio->GetYaxis()->SetNdivisions(503);
  Ratio->Draw();

  Ratio->Draw("axis same");
  Ratio->Draw("same");
  
  TLine* lineratio1 = new TLine( 0, 1, 500, 1);
  lineratio1->SetLineStyle(3);
  lineratio1->Draw("same");
  // Nominal->Draw("same");
  c1->Print(fname + "_higgsPtReweight_withRatio.png");
  c1->Print(fname + "_higgsPtReweight_withRatio.pdf");
  c1->Clear(); 

  c1->Close();

}
