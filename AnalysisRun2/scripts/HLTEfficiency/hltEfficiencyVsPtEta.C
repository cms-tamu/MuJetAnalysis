#include <iostream>
using namespace std;
#include <algorithm>    // std::max
#include <stdlib.h>
#include "../Helpers.h"

TString mass_string;
TString cT_string;
TString fileName;

std::map<TString, TString > mass_strings = {
  {"0250", "0.25"}, {"0275", "0.275"}, {"0300","0.3"}, {"0400", "0.4"}, {"0700", "0.7"}, 
  {"1000", "1.0"}, {"1500", "1.5"}, {"2000", "2.0"}, {"8500", "8.5"}
};
std::map<TString, double > cT_strings = {
  {"000_",0.0}, {"005_", 0.05}, {"010_", 0.10}, {"020_", 0.20}, {"050_", 0.50}, {"100_", 1.00}, 
  {"200_", 2.00}, {"300_", 3.00}, {"500_", 5.00}, {"1000", 10.0}, {"2000", 20.0}, {"8500", 85.0}
};
std::map<TString, TString > cT_strings2 = {
  {"000_","0.0"}, {"005_", "0.05"}, {"010_", "0.10"}, {"020_", "0.20"}, {"050_", "0.50"}, {"100_", "1.00"}, 
  {"200_", "2.00"}, {"300_", "3.00"}, {"500_", "5.00"}, {"1000", "10.0"}, {"2000", "20.0"}, {"8500", "85.0"}
};
std::map<TString, int > mass_colors = {
  {"0250", kRed}, {"0275", kOrange}, {"0300", kSpring}, {"0400", kGreen+2}, {"0700", kAzure+9}, 
  {"1000", kBlue}, {"1500", kViolet+6}, {"2000", kMagenta}, {"8500", kBlack}
};

void efficiency_trigger(const std::vector<std::string>& dirNames, int layers = 1)
{
  bool verbose(false);
  TChain* chain = new TChain("dummy");
  TString ext("out_ana_");

  decodeFileNameMany(dirNames, mass_string, cT_string);
  fileName = "DarkSUSY_mH_125_mGammaD_" + mass_string + "_cT_" + cT_string;
  cout << "Tag name " << fileName << endl;

  cout << "Preparing histograms" << endl;
  TH1D* leading_pt_fid = new TH1D("leading_pt_fid" + fileName,"",50,0.,50.);
  TH1D* RECO_leading_pt_fid = new TH1D("RECO_leading_pt_fid" + fileName,"",50,0.,50.);
  TH1D* hlt_leading_pt_fid = new TH1D("hlt_leading_pt_fid" + fileName,"",50,0.,50.);
  TH1D* hlt_RECO_leading_pt_fid = new TH1D("hlt_RECO_leading_pt_fid" + fileName,"",50,0.,50.);

  TH1D* leading_eta_fid = new TH1D("leading_eta_fid" + fileName,"",50,-2.5,2.5);
  TH1D* RECO_leading_eta_fid = new TH1D("RECO_leading_eta_fid" + fileName,"",50,-2.5,2.5);
  TH1D* hlt_leading_eta_fid = new TH1D("hlt_leading_eta_fid" + fileName,"",50,-2.5,2.5);
  TH1D* hlt_RECO_leading_eta_fid = new TH1D("hlt_RECO_leading_eta_fid" + fileName,"",50,-2.5,2.5);

  TH1D* leading_phi_fid = new TH1D("leading_phi_fid" + fileName,"",60,-TMath::Pi(),TMath::Pi());
  TH1D* RECO_leading_phi_fid = new TH1D("RECO_leading_phi_fid" + fileName,"",60,-TMath::Pi(),TMath::Pi());
  TH1D* hlt_leading_phi_fid = new TH1D("hlt_leading_phi_fid" + fileName,"",60,-TMath::Pi(),TMath::Pi());
  TH1D* hlt_RECO_leading_phi_fid = new TH1D("hlt_RECO_leading_phi_fid" + fileName,"",60,-TMath::Pi(),TMath::Pi());

  // add files to the chain
  addfilesMany(chain, dirNames, ext);

  Int_t event;
  Int_t run;
  Int_t lumi;

  Bool_t is4GenMu;
  Bool_t is1GenMu17;
  Bool_t is2GenMu8;
  Bool_t is3GenMu8;
  Bool_t is4GenMu8;

  Float_t genMu0_pT;
  Float_t genMu1_pT;
  Float_t genMu2_pT;
  Float_t genMu3_pT;
  
  Float_t genMu0_eta;
  Float_t genMu1_eta;
  Float_t genMu2_eta;
  Float_t genMu3_eta;
  
  Float_t genMu0_phi;
  Float_t genMu1_phi;
  Float_t genMu2_phi;
  Float_t genMu3_phi;

  Float_t selMu0_px;
  Float_t selMu1_px;
  Float_t selMu2_px;
  Float_t selMu3_px;

  Float_t selMu0_py;
  Float_t selMu1_py;
  Float_t selMu2_py;
  Float_t selMu3_py;

  Float_t selMu0_eta;
  Float_t selMu1_eta;
  Float_t selMu2_eta;
  Float_t selMu3_eta;

  Bool_t is1SelMu17;
  Bool_t is2SelMu8;
  Bool_t is3SelMu8;
  Bool_t is4SelMu8;

  Bool_t is2MuJets;
  Bool_t is2DiMuons;
  Bool_t is2DiMuonsFittedVtxOK;
  Bool_t is2DiMuonsDzOK_FittedVtx;
  Bool_t isDiMuonHLTFired;
  Bool_t is2DiMuonsMassOK_FittedVtx;
  Bool_t is2DiMuonsIsoTkOK_FittedVtx;
  Bool_t isVertexOK;

  Float_t genA0_Lxy;
  Float_t genA1_Lxy;
  Float_t genA0_Lz;
  Float_t genA1_Lz;

  Int_t diMuonC_m1_FittedVtx_hitpix;
  Int_t diMuonC_m2_FittedVtx_hitpix;
  Int_t diMuonF_m1_FittedVtx_hitpix;
  Int_t diMuonF_m2_FittedVtx_hitpix;

  Int_t diMuonC_m1_FittedVtx_hitpix_l2inc;
  Int_t diMuonC_m2_FittedVtx_hitpix_l2inc;
  Int_t diMuonF_m1_FittedVtx_hitpix_l2inc;
  Int_t diMuonF_m2_FittedVtx_hitpix_l2inc;

  Int_t diMuonC_m1_FittedVtx_hitpix_l3inc;
  Int_t diMuonC_m2_FittedVtx_hitpix_l3inc;
  Int_t diMuonF_m1_FittedVtx_hitpix_l3inc;
  Int_t diMuonF_m2_FittedVtx_hitpix_l3inc;

  //============= Counters ===========================//

  Int_t ev_all = 0;

  Int_t c1recm = 0;
  Int_t c2recm = 0;
  Int_t c3recm = 0;
  Int_t c4recm = 0;

  Int_t ev_isVtxOK = 0;
  Int_t ev_is2MuJets = 0;
  Int_t ev_is2DiMuons = 0;
  Int_t ev_is2DiMuonsFittedVtxOK = 0;
  Int_t ev_isPixelHitOK = 0;
  Int_t ev_is2DiMuonsDzOK_FittedVtx = 0;
  Int_t ev_is2DiMuonsMassOK_FittedVtx = 0;
  Int_t ev_is2DiMuonsIsoTkOK_FittedVtx = 0;
  Int_t ev_isDiMuonHLTFired = 0;

  TObjArray *fileElements=chain->GetListOfFiles();
  TIter next(fileElements);
  TChainElement *chEl=0;

  while ((chEl=(TChainElement*)next())) {
    if (verbose) std::cout << "running on file " << chEl->GetTitle() << std::endl;
    TFile* myfile = new TFile(chEl->GetTitle()); //dirname  +
    if (!myfile) {
      if (verbose) std::cout << "File " << chEl->GetTitle() << " does not exist" << std::endl;
      continue;
    }

    if (verbose) std::cout << "Loading directory cutFlowAnalyzer" << std::endl;
    myfile->cd("cutFlowAnalyzer");

    TTree *t = (TTree*)myfile->Get("cutFlowAnalyzer/Events");
    if (!t) {
      if (verbose) std::cout << "Tree cutFlowAnalyzer/Events does not exist" << std::endl;
      continue;
    }

    if (verbose) cout<<"  Events  "<<t->GetEntries()<<endl;

    // Event info
    t->SetBranchAddress("event", &event);
    t->SetBranchAddress("run",   &run);
    t->SetBranchAddress("lumi",  &lumi);

    // GEN Level Selectors
    t->SetBranchAddress("is4GenMu",    &is4GenMu);
    t->SetBranchAddress("is1GenMu17",  &is1GenMu17);
    t->SetBranchAddress("is2GenMu8",   &is2GenMu8);
    t->SetBranchAddress("is3GenMu8",   &is3GenMu8);
    t->SetBranchAddress("is4GenMu8",   &is4GenMu8);

    t->SetBranchAddress("genMu0_pT",    &genMu0_pT);
    t->SetBranchAddress("genMu1_pT",    &genMu1_pT);
    t->SetBranchAddress("genMu2_pT",    &genMu2_pT);
    t->SetBranchAddress("genMu3_pT",    &genMu3_pT);

    t->SetBranchAddress("genMu0_eta",    &genMu0_eta);
    t->SetBranchAddress("genMu1_eta",    &genMu1_eta);
    t->SetBranchAddress("genMu2_eta",    &genMu2_eta);
    t->SetBranchAddress("genMu3_eta",    &genMu3_eta);

    t->SetBranchAddress("genMu0_phi",    &genMu0_phi);
    t->SetBranchAddress("genMu1_phi",    &genMu1_phi);
    t->SetBranchAddress("genMu2_phi",    &genMu2_phi);
    t->SetBranchAddress("genMu3_phi",    &genMu3_phi);

    // RECO Level Selectors
    t->SetBranchAddress("selMu0_px",    &selMu0_px);
    t->SetBranchAddress("selMu1_px",    &selMu1_px);
    t->SetBranchAddress("selMu2_px",    &selMu2_px);
    t->SetBranchAddress("selMu3_px",    &selMu3_px);

    t->SetBranchAddress("selMu0_py",    &selMu0_py);
    t->SetBranchAddress("selMu1_py",    &selMu1_py);
    t->SetBranchAddress("selMu2_py",    &selMu2_py);
    t->SetBranchAddress("selMu3_py",    &selMu3_py);

    t->SetBranchAddress("selMu0_eta",    &selMu0_eta);
    t->SetBranchAddress("selMu1_eta",    &selMu1_eta);
    t->SetBranchAddress("selMu2_eta",    &selMu2_eta);
    t->SetBranchAddress("selMu3_eta",    &selMu3_eta);

    t->SetBranchAddress("is1SelMu17",                     &is1SelMu17);
    t->SetBranchAddress("is2SelMu8",                      &is2SelMu8);
    t->SetBranchAddress("is3SelMu8",                      &is3SelMu8);
    t->SetBranchAddress("is4SelMu8",                      &is4SelMu8);

    t->SetBranchAddress("is2MuJets",                      &is2MuJets);
    t->SetBranchAddress("is2DiMuons",                     &is2DiMuons);
    t->SetBranchAddress("is2DiMuonsFittedVtxOK",          &is2DiMuonsFittedVtxOK);
    t->SetBranchAddress("is2DiMuonsDzOK_FittedVtx",       &is2DiMuonsDzOK_FittedVtx);
    t->SetBranchAddress("isDiMuonHLTFired",               &isDiMuonHLTFired);
    t->SetBranchAddress("is2DiMuonsMassOK_FittedVtx",     &is2DiMuonsMassOK_FittedVtx);
    t->SetBranchAddress("is2DiMuonsIsoTkOK_FittedVtx",    &is2DiMuonsIsoTkOK_FittedVtx);
    t->SetBranchAddress("isVertexOK",                     &isVertexOK);
    t->SetBranchAddress("isDiMuonHLTFired",              &isDiMuonHLTFired);

    t->SetBranchAddress("genA0_Lxy", &genA0_Lxy);
    t->SetBranchAddress("genA0_Lz",  &genA0_Lz);
    t->SetBranchAddress("genA1_Lxy", &genA1_Lxy);
    t->SetBranchAddress("genA1_Lz",  &genA1_Lz);

    t->SetBranchAddress("diMuonC_m1_FittedVtx_hitpix", &diMuonC_m1_FittedVtx_hitpix);
    t->SetBranchAddress("diMuonC_m2_FittedVtx_hitpix", &diMuonC_m2_FittedVtx_hitpix);
    t->SetBranchAddress("diMuonF_m1_FittedVtx_hitpix", &diMuonF_m1_FittedVtx_hitpix);
    t->SetBranchAddress("diMuonF_m2_FittedVtx_hitpix", &diMuonF_m2_FittedVtx_hitpix);

    t->SetBranchAddress("diMuonC_m1_FittedVtx_hitpix_l2inc", &diMuonC_m1_FittedVtx_hitpix_l2inc);
    t->SetBranchAddress("diMuonC_m2_FittedVtx_hitpix_l2inc", &diMuonC_m2_FittedVtx_hitpix_l2inc);
    t->SetBranchAddress("diMuonF_m1_FittedVtx_hitpix_l2inc", &diMuonF_m1_FittedVtx_hitpix_l2inc);
    t->SetBranchAddress("diMuonF_m2_FittedVtx_hitpix_l2inc", &diMuonF_m2_FittedVtx_hitpix_l2inc);
    
    t->SetBranchAddress("diMuonC_m1_FittedVtx_hitpix_l3inc", &diMuonC_m1_FittedVtx_hitpix_l3inc);
    t->SetBranchAddress("diMuonC_m2_FittedVtx_hitpix_l3inc", &diMuonC_m2_FittedVtx_hitpix_l3inc);
    t->SetBranchAddress("diMuonF_m1_FittedVtx_hitpix_l3inc", &diMuonF_m1_FittedVtx_hitpix_l3inc);
    t->SetBranchAddress("diMuonF_m2_FittedVtx_hitpix_l3inc", &diMuonF_m2_FittedVtx_hitpix_l3inc);
    
    for(int k=0; k<t->GetEntries(); k++) {
      t->GetEntry(k);
      
      const bool firstPixelLayer((diMuonC_m1_FittedVtx_hitpix==1 || 
				  diMuonC_m2_FittedVtx_hitpix==1) && 
				 (diMuonF_m1_FittedVtx_hitpix==1 || 
				  diMuonF_m2_FittedVtx_hitpix==1));
      const bool secondPixelLayer((diMuonC_m1_FittedVtx_hitpix_l2inc==1 || 
       				   diMuonC_m2_FittedVtx_hitpix_l2inc==1) && 
       				  (diMuonF_m1_FittedVtx_hitpix_l2inc==1 || 
       				   diMuonF_m2_FittedVtx_hitpix_l2inc==1));
      const bool thirdPixelLayer((diMuonC_m1_FittedVtx_hitpix_l3inc==1 || 
       				  diMuonC_m2_FittedVtx_hitpix_l3inc==1) && 
       				 (diMuonF_m1_FittedVtx_hitpix_l3inc==1 || 
       				  diMuonF_m2_FittedVtx_hitpix_l3inc==1));
      
      const double firstPixelLayerRadius(4.4);
      const double secondPixelLayerRadius(7.3);
      const double thirdPixelLayerRadius(10.2);
      
      bool pixelLayer;
      double pixelLayerRadius;
      
      if (layers==1) {
	pixelLayer = firstPixelLayer;
	pixelLayerRadius = firstPixelLayerRadius;
      }
      else if (layers==2) {
       	pixelLayer = secondPixelLayer;
       	pixelLayerRadius = secondPixelLayerRadius;
      }
      else if (layers==3) {
       	pixelLayer = thirdPixelLayer;
       	pixelLayerRadius = thirdPixelLayerRadius;
      }
      
      ev_all++;

      if(is1SelMu17) c1recm++;
      if(is2SelMu8)  c2recm++;
      if(is3SelMu8)  c3recm++;
      if(is4SelMu8)  c4recm++;

      //  ===========   GEN LEVEL information  ==============//
      // if(//is4GenMu8 and 
      // 	 fabs(genA0_Lxy)< pixelLayerRadius and 
      // 	 fabs(genA1_Lxy)< pixelLayerRadius and 
      // 	 fabs(genA0_Lz)<34.5 and 
      // 	 fabs(genA1_Lz)<34.5){
	
      // 	leading_pt_fid->Fill(genMu0_pT);
      // 	leading_eta_fid->Fill(genMu0_eta);
      // 	leading_phi_fid->Fill(genMu0_phi);
	
      // 	if (isDiMuonHLTFired){
      // 	  hlt_leading_pt_fid->Fill(genMu0_pT);
      // 	  hlt_leading_eta_fid->Fill(genMu0_eta);
      // 	  hlt_leading_phi_fid->Fill(genMu0_phi);
      // 	}
      // }
      
      // check for 4 reco muons 
      Int_t nMu = 0;
      if (selMu0_px!=-100 and selMu0_py!=-100) nMu++;
      if (selMu1_px!=-100 and selMu1_py!=-100) nMu++;
      if (selMu2_px!=-100 and selMu2_py!=-100) nMu++;
      if (selMu3_px!=-100 and selMu3_py!=-100) nMu++;
      
      if (nMu>=4) {
	Float_t selMu0_pT = TMath::Sqrt(selMu0_px*selMu0_px + selMu0_py*selMu0_py);
	Float_t selMu1_pT = TMath::Sqrt(selMu1_px*selMu1_px + selMu1_py*selMu1_py);
	Float_t selMu2_pT = TMath::Sqrt(selMu2_px*selMu2_px + selMu2_py*selMu2_py);
	Float_t selMu3_pT = TMath::Sqrt(selMu3_px*selMu3_px + selMu3_py*selMu3_py);
	
	Int_t nMuPt8 = 0;
	Int_t nMuPt17 = 0;
	
	if (selMu0_pT>=8) nMuPt8++;
	if (selMu1_pT>=8) nMuPt8++;
	if (selMu2_pT>=8) nMuPt8++;
	if (selMu3_pT>=8) nMuPt8++;
	
	if (selMu0_pT>=17) nMuPt17++;
	if (selMu1_pT>=17) nMuPt17++;
	if (selMu2_pT>=17) nMuPt17++;
	if (selMu3_pT>=17) nMuPt17++;

	if (nMuPt8>=4 and nMuPt17>=1){
	  RECO_leading_pt_fid->Fill(selMu0_pT);
	  RECO_leading_eta_fid->Fill(selMu0_eta);
	  //	RECO_leading_phi_fid->Fill(selMu0_phi);
	  if (isDiMuonHLTFired){
	    hlt_RECO_leading_pt_fid->Fill(selMu0_pT);
	    hlt_RECO_leading_eta_fid->Fill(selMu0_eta);
	    //	  hlt_RECO_leading_phi_fid->Fill(selMu0_phi);
	  }
	}
      }
    } // closing for loop
    myfile->Close();
  } // closing while loop
  
  // TEfficiency objects
  TEfficiency* eff_hlt_leading_pt_fid = new TEfficiency(*hlt_leading_pt_fid, *leading_pt_fid);
  TEfficiency* eff_hlt_leading_eta_fid = new TEfficiency(*hlt_leading_eta_fid, *leading_eta_fid);
  TEfficiency* eff_hlt_leading_phi_fid = new TEfficiency(*hlt_leading_phi_fid, *leading_phi_fid);
  TEfficiency* eff_hlt_RECO_leading_pt_fid = new TEfficiency(*hlt_RECO_leading_pt_fid, *RECO_leading_pt_fid);
  TEfficiency* eff_hlt_RECO_leading_eta_fid = new TEfficiency(*hlt_RECO_leading_eta_fid, *RECO_leading_eta_fid);
  TEfficiency* eff_hlt_RECO_leading_phi_fid = new TEfficiency(*hlt_RECO_leading_phi_fid, *RECO_leading_phi_fid);
  
  enum Variable{Pt=0,Eta=1,Phi=3};

  // Plots
  struct MyEfficiencyPlot
  {
    static void plot(enum Variable v, TEfficiency* eff, TString cTitle) { 

      TCanvas *c = new TCanvas("c","c",700,500);
      gStyle->SetOptStat(0);
      
      double xMin;
      double xMax;
      int xBin = 50;
      TString xTitle;
      TString yTitle = "HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx efficiency";
      TString title;

      if (v==Variable::Pt){
	xMin = 0;
	xMax = 50;
	xTitle = "Leading muon p_{T} [GeV]";
	title = "leading muon p_{T}";
      }
      else if (v==Variable::Eta){
	xMin = -2.5;
	xMax = 2.5;
	xTitle ="Leading muon #eta";
	title = "leading muon #eta";
      }
      else if (v==Variable::Phi){
	xMin = -TMath::Pi();
	xMax = TMath::Pi();
	xBin = 60;
	xTitle ="Leading muon #phi";
	title = "leading muon #phi";
      }
      
      TH1F *base = new TH1F("","Trigger efficiency versus " + title, xBin, xMin, xMax);
      base->GetXaxis()->SetTitle(xTitle);
      base->GetYaxis()->SetTitle(yTitle);
      base->Draw();
      
      eff->SetLineWidth(1);
      eff->SetMarkerSize(5);
      eff->SetLineColor(kBlue);
      eff->SetMarkerColor(kBlue);
      eff->SetMarkerStyle(7);
      eff->Draw("same");

      TLegend *leg = new TLegend(0.15,0.15,0.85,0.45);
      leg->SetBorderSize(0);
      leg->SetFillColor(0);
      leg->SetTextSize(0.045);
      leg->AddEntry(eff,"m_{#gamma D}= " + mass_strings[mass_string] +  " GeV, " + "c#tau_{#gamma D}= " + cT_strings2[cT_string] + " mm", "PL");      
      leg->Draw("same");

      c->SaveAs(TString("trigger_efficiency_plots_pt_eta_phi/" + cTitle + "_" + fileName + ".png"),"recreate");
      c->Clear();
    }
  };

  // MyEfficiencyPlot::plot(Variable::Pt,  eff_hlt_leading_pt_fid, "eff_hlt_vs_leading_pT_L" + std::to_string(layers));
  // MyEfficiencyPlot::plot(Variable::Eta, eff_hlt_leading_eta_fid, "eff_hlt_vs_leading_eta_L" + std::to_string(layers));
  // MyEfficiencyPlot::plot(Variable::Phi, eff_hlt_leading_phi_fid, "eff_hlt_vs_leading_phi_L" + std::to_string(layers));
  // MyEfficiencyPlot::plot(Variable::Pt,  eff_hlt_RECO_leading_pt_fid, "eff_hlt_RECO_vs_leading_pT_L" + std::to_string(layers));
  MyEfficiencyPlot::plot(Variable::Eta, eff_hlt_RECO_leading_eta_fid, "eff_hlt_RECO_vs_leading_eta");
  // MyEfficiencyPlot::plot(Variable::Phi, eff_hlt_RECO_leading_phi_fid, "eff_hlt_RECO_vs_leading_phi_L" + std::to_string(layers));
}

void hltEfficiencyVsPtEta()
{
  std::vector< std::vector<string> > DarkSUSY_mH_125_mGammaD_v;
  readTextFileWithSamples("ANASamplesSven2.txt", DarkSUSY_mH_125_mGammaD_v);
  // printFileNames(DarkSUSY_mH_125_mGammaD_v);

  for(auto v: DarkSUSY_mH_125_mGammaD_v) efficiency_trigger(v);
  // for(auto v: DarkSUSY_mH_125_mGammaD_v) efficiency_trigger(v, 2);
  // for(auto v: DarkSUSY_mH_125_mGammaD_v) efficiency_trigger(v, 3);
}

