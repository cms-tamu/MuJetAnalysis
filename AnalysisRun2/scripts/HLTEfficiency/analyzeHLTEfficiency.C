#include <iostream>
using namespace std;
#include <algorithm>    // std::max
#include <stdlib.h>
#include "../Helpers.h"

//============= Global Variables ===========================//
vector<double> mGammaD_0250_eff;
vector<double> mGammaD_0275_eff;
vector<double> mGammaD_0300_eff;
vector<double> mGammaD_2000_eff;
vector<double> mGammaD_8500_eff;

vector<double> mGammaD_0250_eff_uncert;
vector<double> mGammaD_0275_eff_uncert;
vector<double> mGammaD_0300_eff_uncert;
vector<double> mGammaD_2000_eff_uncert;
vector<double> mGammaD_8500_eff_uncert;

vector<double> mGammaD_0250_cT;
vector<double> mGammaD_0275_cT;
vector<double> mGammaD_0300_cT;
vector<double> mGammaD_2000_cT;
vector<double> mGammaD_8500_cT;

void efficiency_trigger(TString fileName)
{
  bool verbose(false);
  TString dirname(fileName);
  TChain* chain = new TChain("dummy");
  TString ext("out_ana_");
  
  TString mass_string;
  TString cT_string;
  decodeFileName(fileName, mass_string, cT_string);

  // add files to the chain
  addfiles(chain, dirname, ext);

  Int_t event;
  Int_t run;
  Int_t lumi;

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
    TFile* myfile = new TFile(dirname + chEl->GetTitle());
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

    // RECO Level Selectors
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
    
    for(int k=0;k<t->GetEntries();k++){
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
      int layers = 1;

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

      //  =============  Reco information ====================//
      if(is4SelMu8){
	if(isVertexOK){
	  ev_isVtxOK++;
	  if(is2MuJets){
	    ev_is2MuJets++;
	    if(is2DiMuons){
	      ev_is2DiMuons++;
	      if(is2DiMuonsFittedVtxOK){
		ev_is2DiMuonsFittedVtxOK++;
		if( pixelLayer ){
		  ev_isPixelHitOK++;
		  if(is2DiMuonsDzOK_FittedVtx){
		    ev_is2DiMuonsDzOK_FittedVtx++;
		    if(is2DiMuonsMassOK_FittedVtx){
		      ev_is2DiMuonsMassOK_FittedVtx++;
		      if(is2DiMuonsIsoTkOK_FittedVtx){
			ev_is2DiMuonsIsoTkOK_FittedVtx++;
			if(isDiMuonHLTFired){
			  ev_isDiMuonHLTFired++;
			}
		      }
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
    } // closing for loop
    myfile->Close();
  } // closing while loop
  std::cout<<" Sample: " << fileName << endl;
  std::cout<<" Events          "<<ev_all<<std::endl;
  std::cout<<" ================ RECO MUONS ========================================= "<<std::endl;
  std::cout<<" 1RecMu17                       "<<c1recm<<"  reff  "<<c1recm/(ev_all*1.0)<<std::endl;
  std::cout<<" 2RecMu8                        "<<c2recm<<"  reff  "<<c2recm/(c1recm*1.0)<<std::endl;
  std::cout<<" 3RecMu8                        "<<c3recm<<"  reff  "<<c3recm/(c2recm*1.0)<<std::endl;
  std::cout<<" 4RecMu8                        "<<c4recm<<"  reff  "<<c4recm/(c3recm*1.0)<<std::endl;
  std::cout<<" ================ EVENT variables ================= "<<std::endl;
  std::cout<<" Events with VtxOK              "<<ev_isVtxOK<<"    reff  "<<ev_isVtxOK/(1.0*c4recm)<<std::endl;
  std::cout<<" Events with 2 muonjets         "<<ev_is2MuJets<<"     reff  "<<ev_is2MuJets/(1.0*ev_isVtxOK)<<std::endl;
  std::cout<<" Events with 2 Dimuons          "<<ev_is2DiMuons<<"    reff  "<<ev_is2DiMuons/(1.0*ev_is2MuJets)<<std::endl;
  std::cout<<" Events with 2DimVtxOK          "<<ev_is2DiMuonsFittedVtxOK<<"    reff  "<<ev_is2DiMuonsFittedVtxOK/(1.0*ev_is2DiMuons)<<std::endl;
  std::cout<<" Events with 2DimHitPix         "<<ev_isPixelHitOK<<"     reff  "<<ev_isPixelHitOK/(1.0*ev_is2DiMuonsFittedVtxOK)<<std::endl;
  std::cout<<" Events with 2DimDzOK           "<<ev_is2DiMuonsDzOK_FittedVtx<<"   reff   "<<ev_is2DiMuonsDzOK_FittedVtx/(1.0*ev_isPixelHitOK)<<std::endl;
  std::cout<<" Events with 2DimMassOK         "<<ev_is2DiMuonsMassOK_FittedVtx<<"  reff   "<<ev_is2DiMuonsMassOK_FittedVtx/(1.0*ev_is2DiMuonsDzOK_FittedVtx)<<endl;
  std::cout<<" Events with 2DimIsoOK          "<<ev_is2DiMuonsIsoTkOK_FittedVtx<<"   reff   "<<ev_is2DiMuonsIsoTkOK_FittedVtx/(1.0*ev_is2DiMuonsMassOK_FittedVtx)<<endl;
  std::cout<<" Events with 2DimHLT            "<<ev_isDiMuonHLTFired<<"   reff   "<<ev_isDiMuonHLTFired/(1.0*ev_is2DiMuonsIsoTkOK_FittedVtx)<<endl;

  //Fill ratio reco/gen vectors to be plotted  


  double cT_double; 
  if(cT_string == "000_") cT_double = 0;
  if(cT_string == "005_") cT_double = 0.05;
  if(cT_string == "010_") cT_double = 0.1;
  if(cT_string == "020_") cT_double = 0.2;
  if(cT_string == "050_") cT_double = 0.5;
  if(cT_string == "100_") cT_double = 1.0;
  if(cT_string == "200_") cT_double = 2.0;
  if(cT_string == "300_") cT_double = 3.0;
  if(cT_string == "500_") cT_double = 5.0;
  if(cT_string == "1000") cT_double = 10.0;
  if(cT_string == "2000") cT_double = 20.0;

  if(mass_string == "0250"){
	  mGammaD_0250_eff.push_back(ev_isDiMuonHLTFired/(1.0*ev_is2DiMuonsIsoTkOK_FittedVtx));  
	  mGammaD_0250_eff_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_is2DiMuonsIsoTkOK_FittedVtx))*(1- (ev_isDiMuonHLTFired/(1.0*ev_is2DiMuonsIsoTkOK_FittedVtx)) ))/(1.0*ev_is2DiMuonsIsoTkOK_FittedVtx)));  
	  mGammaD_0250_cT.push_back(cT_double);
  }
  if(mass_string == "0275"){
	  mGammaD_0275_eff.push_back(ev_isDiMuonHLTFired/(1.0*ev_is2DiMuonsIsoTkOK_FittedVtx));  
	  mGammaD_0275_eff_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_is2DiMuonsIsoTkOK_FittedVtx))*(1- (ev_isDiMuonHLTFired/(1.0*ev_is2DiMuonsIsoTkOK_FittedVtx)) ))/(1.0*ev_is2DiMuonsIsoTkOK_FittedVtx)));  
	  mGammaD_0275_cT.push_back(cT_double);  
  }
  if(mass_string == "0300"){
	  mGammaD_0300_eff.push_back(ev_isDiMuonHLTFired/(1.0*ev_is2DiMuonsIsoTkOK_FittedVtx));  
	  mGammaD_0300_eff_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_is2DiMuonsIsoTkOK_FittedVtx))*(1- (ev_isDiMuonHLTFired/(1.0*ev_is2DiMuonsIsoTkOK_FittedVtx)) ))/(1.0*ev_is2DiMuonsIsoTkOK_FittedVtx)));  
	  mGammaD_0300_cT.push_back(cT_double);  
  }
  if(mass_string == "2000"){
	  mGammaD_2000_eff.push_back(ev_isDiMuonHLTFired/(1.0*ev_is2DiMuonsIsoTkOK_FittedVtx));  
	  mGammaD_2000_eff_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_is2DiMuonsIsoTkOK_FittedVtx))*(1- (ev_isDiMuonHLTFired/(1.0*ev_is2DiMuonsIsoTkOK_FittedVtx)) ))/(1.0*ev_is2DiMuonsIsoTkOK_FittedVtx)));  
	  mGammaD_2000_cT.push_back(cT_double);  
  }
  if(mass_string == "8500"){
	  mGammaD_8500_eff.push_back(ev_isDiMuonHLTFired/(1.0*ev_is2DiMuonsIsoTkOK_FittedVtx));  
	  mGammaD_8500_eff_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_is2DiMuonsIsoTkOK_FittedVtx))*(1- (ev_isDiMuonHLTFired/(1.0*ev_is2DiMuonsIsoTkOK_FittedVtx)) ))/(1.0*ev_is2DiMuonsIsoTkOK_FittedVtx)));  
	  mGammaD_8500_cT.push_back(cT_double);  
  }
//delete chEl;
//delete fileElements;
}

void makePlot()
{
  //Turn vectors in to arrays of data
  vector<double> null_0250;
  for(int i=0; i < mGammaD_0250_cT.size(); i++){
    null_0250.push_back(0);
  }
  double* array_null_0250               = &null_0250[0];
  double* array_mGammaD_0250_eff        = &mGammaD_0250_eff[0];
  double* array_mGammaD_0250_eff_uncert = &mGammaD_0250_eff_uncert[0];
  double* array_mGammaD_0250_cT         = &mGammaD_0250_cT[0];
  int size_0250 = null_0250.size();
  
  TGraphErrors *gr_eff_mD_0250 = new TGraphErrors(size_0250,array_mGammaD_0250_cT,array_mGammaD_0250_eff,array_null_0250,array_mGammaD_0250_eff_uncert);
  
  vector<double> null_0275;
  for(int i=0; i < mGammaD_0275_cT.size(); i++){
    null_0275.push_back(0);
  }
  double* array_null_0275               = &null_0275[0];
  double* array_mGammaD_0275_eff        = &mGammaD_0275_eff[0];
  double* array_mGammaD_0275_eff_uncert = &mGammaD_0275_eff_uncert[0];
  double* array_mGammaD_0275_cT         = &mGammaD_0275_cT[0];
  int size_0275 = null_0275.size();
  
  TGraphErrors *gr_eff_mD_0275 = new TGraphErrors(size_0275,array_mGammaD_0275_cT,array_mGammaD_0275_eff,array_null_0275,array_mGammaD_0275_eff_uncert);
  
  vector<double> null_0300;
  for(int i=0; i < mGammaD_0300_cT.size(); i++){
    null_0300.push_back(0);
  }
  double* array_null_0300               = &null_0300[0];
  double* array_mGammaD_0300_eff        = &mGammaD_0300_eff[0];
  double* array_mGammaD_0300_eff_uncert = &mGammaD_0300_eff_uncert[0];
  double* array_mGammaD_0300_cT         = &mGammaD_0300_cT[0];
  int size_0300 = null_0300.size();

  TGraphErrors *gr_eff_mD_0300 = new TGraphErrors(size_0300,array_mGammaD_0300_cT,array_mGammaD_0300_eff,array_null_0300,array_mGammaD_0300_eff_uncert);
  
  vector<double> null_2000;
  for(int i=0; i < mGammaD_2000_cT.size(); i++){
    null_2000.push_back(0);
  }
  double* array_null_2000		      = &null_2000[0];
  double* array_mGammaD_2000_eff        = &mGammaD_2000_eff[0];
  double* array_mGammaD_2000_eff_uncert = &mGammaD_2000_eff_uncert[0];
  double* array_mGammaD_2000_cT	      = &mGammaD_2000_cT[0];
  int size_2000 = null_2000.size();
  TGraphErrors *gr_eff_mD_2000 = new TGraphErrors(size_2000,array_mGammaD_2000_cT,array_mGammaD_2000_eff,array_null_2000,array_mGammaD_2000_eff_uncert);
  
  vector<double> null_8500;
  for(int i=0; i < mGammaD_8500_cT.size(); i++){
    null_8500.push_back(0);
  }
  double* array_null_8500               = &null_8500[0];
  double* array_mGammaD_8500_eff        = &mGammaD_8500_eff[0];
  double* array_mGammaD_8500_eff_uncert = &mGammaD_8500_eff_uncert[0];
  double* array_mGammaD_8500_cT         = &mGammaD_8500_cT[0];
  int size_8500 = null_8500.size();
  
  TGraphErrors *gr_eff_mD_8500 = new TGraphErrors(size_8500,array_mGammaD_8500_cT,array_mGammaD_8500_eff,array_null_8500,array_mGammaD_8500_eff_uncert);
  
  TLegend *leg = new TLegend(0.5,0.15,0.85,0.45);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetTextSize(0.045);
  leg->AddEntry(gr_eff_mD_0250,"m_{#gamma D}=0.250 GeV","PL");
  leg->AddEntry(gr_eff_mD_0275,"m_{#gamma D}=0.275 GeV","PL");
  leg->AddEntry(gr_eff_mD_0300,"m_{#gamma D}=0.300 GeV","PL");
  leg->AddEntry(gr_eff_mD_2000,"m_{#gamma D}=2.000 GeV","PL");
  leg->AddEntry(gr_eff_mD_8500,"m_{#gamma D}=8.500 GeV","PL");
  
  
  TH2F *dummy3 = new TH2F("","",400,-0.2,20.2,100,0.0,1.0);

  
  TCanvas *c = new TCanvas("c","c",700,500);
  dummy3->GetXaxis()->SetTitle("c#tau [mm]");
  dummy3->GetYaxis()->SetTitle("HLT efficiency");
  gStyle->SetOptStat(0);
  dummy3->Draw();
  
  gr_eff_mD_0250->SetLineWidth(1);
  gr_eff_mD_0250->SetMarkerSize(5);
  gr_eff_mD_0250->SetLineColor(1);
  gr_eff_mD_0250->SetMarkerColor(1);
  gr_eff_mD_0250->SetMarkerStyle(7);
  gr_eff_mD_0250->Draw("SAME PL");
  
  gr_eff_mD_0275->SetLineWidth(1);
  gr_eff_mD_0275->SetMarkerSize(5);
  gr_eff_mD_0275->SetLineColor(2);
  gr_eff_mD_0275->SetMarkerColor(2);
  gr_eff_mD_0275->SetMarkerStyle(7);
  gr_eff_mD_0275->Draw("SAME PL");
  
  gr_eff_mD_0300->SetLineWidth(1);
  gr_eff_mD_0300->SetMarkerSize(5);
  gr_eff_mD_0300->SetLineColor(3);
  gr_eff_mD_0300->SetMarkerColor(3);
  gr_eff_mD_0300->SetMarkerStyle(7);
  gr_eff_mD_0300->Draw("SAME PL");
  
  gr_eff_mD_2000->SetLineWidth(1);
  gr_eff_mD_2000->SetMarkerSize(5);
  gr_eff_mD_2000->SetLineColor(4);
  gr_eff_mD_2000->SetMarkerColor(4);
  gr_eff_mD_2000->SetMarkerStyle(7);
  gr_eff_mD_2000->Draw("SAME PL");
  
  gr_eff_mD_8500->SetLineWidth(1);
  gr_eff_mD_8500->SetMarkerSize(5);
  gr_eff_mD_8500->SetLineColor(6);
  gr_eff_mD_8500->SetMarkerColor(6);
  gr_eff_mD_8500->SetMarkerStyle(7);
  gr_eff_mD_8500->Draw("SAME PL");
  
  leg->Draw("same");
  c->SaveAs("e_hlt_vs_cT.pdf","recreate");
  c->SaveAs("e_hlt_vs_cT.C","recreate");
}

void analyzeHLTEfficiency()
{

efficiency_trigger("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151026/151026_112552/0000/");
efficiency_trigger("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151026/151026_112613/0000/");
efficiency_trigger("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151026/151026_112633/0000/");
efficiency_trigger("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151026/151026_112537/0000/");
efficiency_trigger("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_100_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151026/151026_112648/0000/");
efficiency_trigger("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151026/151026_112703/0000/");
efficiency_trigger("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_300_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151026/151026_112723/0000/");
efficiency_trigger("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151026/151026_112739/0000/");

efficiency_trigger("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0275_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151026/151027_025434/0000/");
efficiency_trigger("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0275_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151026/151027_025509/0000/");
efficiency_trigger("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0275_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151026/151027_025523/0000/");
efficiency_trigger("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0275_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151026/151027_025545/0000/");
efficiency_trigger("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0275_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151026/151027_025453/0000/");
efficiency_trigger("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0275_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_100_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151026/151027_025601/0000/");
efficiency_trigger("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0275_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151026/151027_025619/0000/");
efficiency_trigger("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0275_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_300_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151026/151027_025635/0000/");
efficiency_trigger("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0275_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151026/151027_025655/0000/");

efficiency_trigger("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_2000_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151106/151106_194045/0000/");
efficiency_trigger("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_2000_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151106/151106_194119/0000/");
efficiency_trigger("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_2000_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151106/151106_194135/0000/");
efficiency_trigger("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_2000_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151106/151106_194154/0000/");
efficiency_trigger("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_2000_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151106/151106_194104/0000/");
efficiency_trigger("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_2000_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_100_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151106/151106_194216/0000/");
efficiency_trigger("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_2000_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151106/151106_194231/0000/");
efficiency_trigger("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_2000_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_300_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151106/151106_194246/0000/");
efficiency_trigger("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_2000_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151106/151106_194304/0000/");

/*
efficiency_trigger("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_8500_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151026/151027_161154/0000/");
efficiency_trigger("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_8500_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151026/151027_161209/0000/");
efficiency_trigger("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_8500_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151026/151027_161008/0000/");
efficiency_trigger("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_8500_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151026/151027_161139/0000/");
efficiency_trigger("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_8500_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_100_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151026/151027_161229/0000/");
efficiency_trigger("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_8500_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151026/151027_161255/0000/");
efficiency_trigger("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_8500_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_300_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151026/151027_161309/0000/");
efficiency_trigger("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_8500_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151026/151027_161324/0000/");

efficiency_trigger("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/"); 
efficiency_trigger("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
efficiency_trigger("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
efficiency_trigger("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
efficiency_trigger("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
efficiency_trigger("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
efficiency_trigger("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
efficiency_trigger("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
efficiency_trigger("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
efficiency_trigger("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_1000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
efficiency_trigger("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_2000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");

*/
 makePlot();
}

/*
"""
from __future__ import division ## floating point division
from ROOT import *

def passedHltPath(t,trigger):
    return (trigger in t.hltPaths)

def error_binom(total, selected):
    '''Source: 'http://home.fnal.gov/~paterno/images/effic.pdf'''
    return 1/total*TMath.Sqrt(selected*(1-(selected/total)))

def analyzeHLT():


    file = '/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0275_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151026/151027_025434/0000/out_ana_1.root'
    file = '/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0275_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151026/151027_025655/0000/out_ana_1.root'

    file='/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151106/151106_193924/0000/out_ana_1.root'
    file='/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151027/151027_160931/0000/out_ana_1.root'
    file = '/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_8500_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151026/151027_161154/0000/out_ana_1.root'
    file='/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_8500_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151026/151027_161324/0000/out_ana_1.root'
    file = '/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_000_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_000_Evt_80k_PATANA_v4/151117_152519/0000/out_ana_1.root'
    file = '/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_500_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_500_Evt_80k_PATANA_v4/151117_153321/0000/out_ana_Combined_80k.root'

    f = TFile.Open(file)

    print "Processing", file
    ana = "cutFlowAnalyzer"
    dir = f.Get(ana)      
    print "Opening directory", dir.GetName()
    t = dir.Get("Events");
    print "Loading tree", t.GetName()
    
    nentries = t.GetEntries();
    m_events = 0
    m_events4GenMu = 0
    m_events1GenMu17 = 0
    m_events2GenMu8 = 0      
    m_events3GenMu8 = 0
    m_events4GenMu8 = 0
    m_events1SelMu17 = 0
    m_events2SelMu8 = 0
    m_events3SelMu8 = 0
    m_events4SelMu8 = 0
    m_events2MuJets = 0
    m_events2DiMuons = 0
    
    m_events2DiMuonsDzOK_FittedVtx = 0
    m_events2DiMuonsDzOK_ConsistentVtx = 0

    m_events2DiMuonsMassOK_FittedVtx_noHLT = 0
    m_events2DiMuonsMassOK_ConsistentVtx_noHLT = 0
    m_events2DiMuonsIsoTkOK_FittedVtx_noHLT = 0
    m_events2DiMuonsIsoTkOK_ConsistentVtx_noHLT = 0
    m_eventsVertexOK_FittedVtx_noHLT = 0
    m_eventsVertexOK_ConsistentVtx_noHLT = 0

    m_eventsDiMuonHLTFired_FittedVtx = 0
    m_eventsDiMuonHLTFired_ConsistentVtx = 0
    m_events2DiMuonsMassOK_FittedVtx = 0
    m_events2DiMuonsMassOK_ConsistentVtx = 0
    m_events2DiMuonsIsoTkOK_FittedVtx = 0
    m_events2DiMuonsIsoTkOK_ConsistentVtx = 0

    m_eventsVertexOK_FittedVtx = 0
    m_eventsVertexOK_ConsistentVtx = 0

    m_eventsGoodFailingHLT = 0
    m_eventsGoodPassingHLT = 0
    m_isDiMuonHLTFired = 0
    m_eventsVertexOK_FittedVtx_noHLT_lxyCut = 0

    ## make a dictionary to count the triggers
    hltPaths = [
        'HLT_DoubleMu33NoFiltersNoVtx_v1',
        'HLT_Mu17_Mu8_DZ_v1',
        'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v1',
        'HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v1',
        'HLT_Mu30_TkMu11_v1',
        'HLT_TripleMu_12_10_5_v1',
        'HLT_TripleMu_12_10_5_onlyL1NewSeed_v1',
        'HLT_TrkMu15_DoubleTrkMu5_v1',
        'HLT_Mu15_DoubleMu5NoVtx_v1',
        'HLT_TrkMu15_DoubleTrkMu5NoVtx_v1',
        'HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx_v1',
        'HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx_v2',
        'HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx_v1',
        'HLT_Mu17_Mu8_DZ_v1_NoDz',
        'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v1_NoIso',
        'HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v1_NoIso',
        'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v1'
    ]
    hltPathPass = {}
    hltPathFail = {}
    for p in hltPaths:
        hltPathPass[p] = 0 ## intialization
        hltPathFail[p] = 0 ## intialization

    for k in range(0,nentries):
        t.GetEntry(k)    
        m_events += 1
        ## print "Processing Event", k

        if (t.is4GenMu):
            m_events4GenMu += 1            
        if (t.is1GenMu17):
            m_events1GenMu17 += 1
            if (t.is2GenMu8):
                m_events2GenMu8 += 1      
            if (t.is3GenMu8):
                m_events3GenMu8 += 1
            if (t.is4GenMu8):
                m_events4GenMu8 += 1
        if (t.is1SelMu17):
            m_events1SelMu17 += 1
            if (t.is2SelMu8):
                m_events2SelMu8 += 1
            if (t.is3SelMu8):
                m_events3SelMu8 += 1
            if (t.is4SelMu8):
                m_events4SelMu8 += 1
                
        if (t.is2MuJets):
            m_events2MuJets += 1
            if (t.is2DiMuons):
                m_events2DiMuons += 1
                
                if (t.is2DiMuonsDzOK_FittedVtx):
                    m_events2DiMuonsDzOK_FittedVtx += 1
                    if (t.is2DiMuonsMassOK_FittedVtx):
                        m_events2DiMuonsMassOK_FittedVtx_noHLT += 1
                        if (t.is2DiMuonsIsoTkOK_FittedVtx):
                            m_events2DiMuonsIsoTkOK_FittedVtx_noHLT += 1
                            if (t.isVertexOK):
                                m_eventsVertexOK_FittedVtx_noHLT += 1                         
                                if (t.genA0_Lxy < 10.4 and t.genA1_Lxy < 10.4):                                  
                                    m_eventsVertexOK_FittedVtx_noHLT_lxyCut += 1
                                    for p in hltPaths:
                                        if passedHltPath(t,p):
                                            hltPathPass[p] += 1
                                        else:
                                            hltPathFail[p] += 1

                                    
    print "m_events", m_events
    print "m_isDiMuonHLTFired", m_isDiMuonHLTFired
    print "m_events4GenMu", m_events4GenMu
    print "m_events1GenMu17", m_events1GenMu17
    print "m_events2GenMu8", m_events2GenMu8
    print "m_events3GenMu8", m_events3GenMu8
    print "m_events4GenMu8", m_events4GenMu8
    print "m_events1SelMu17", m_events1SelMu17
    print "m_events2SelMu8", m_events2SelMu8
    print "m_events3SelMu8", m_events3SelMu8
    print "m_events4SelMu8", m_events4SelMu8

    print "m_events2MuJets", m_events2MuJets
    print "m_events2DiMuons", m_events2DiMuons

    print "m_events2DiMuonsDzOK_FittedVtx", m_events2DiMuonsDzOK_FittedVtx
#    print "m_events2DiMuonsDzOK_ConsistentVtx", m_events2DiMuonsDzOK_ConsistentVtx
    
    print "m_events2DiMuonsMassOK_FittedVtx_noHLT", m_events2DiMuonsMassOK_FittedVtx_noHLT
    print "m_events2DiMuonsIsoTkOK_FittedVtx_noHLT", m_events2DiMuonsIsoTkOK_FittedVtx_noHLT
    print "m_eventsVertexOK_FittedVtx_noHLT", m_eventsVertexOK_FittedVtx_noHLT
    print "m_eventsVertexOK_FittedVtx_noHLT_lxyCut", m_eventsVertexOK_FittedVtx_noHLT_lxyCut
    print
    print "m_events2DiMuonsMassOK_FittedVtx", m_events2DiMuonsMassOK_FittedVtx
    print "m_events2DiMuonsIsoTkOK_FittedVtx", m_events2DiMuonsIsoTkOK_FittedVtx
    print "m_eventsVertexOK_FittedVtx", m_eventsVertexOK_FittedVtx
    print
##     print "m_events2DiMuonsMassOK_ConsistentVtx_noHLT", m_events2DiMuonsMassOK_ConsistentVtx_noHLT
##     print "m_events2DiMuonsIsoTkOK_ConsistentVtx_noHLT", m_events2DiMuonsIsoTkOK_ConsistentVtx_noHLT
##     print "m_eventsVertexOK_ConsistentVtx_noHLT", m_eventsVertexOK_ConsistentVtx_noHLT
##     print
##     print "m_events2DiMuonsMassOK_ConsistentVtx", m_events2DiMuonsMassOK_ConsistentVtx
##     print "m_events2DiMuonsIsoTkOK_ConsistentVtx", m_events2DiMuonsIsoTkOK_ConsistentVtx
##     print "m_eventsVertexOK_ConsistentVtx", m_eventsVertexOK_ConsistentVtx
    print
    print "Trigger efficiencies:"
    for p in hltPaths:
        eff = hltPathPass[p]/m_eventsVertexOK_FittedVtx_noHLT_lxyCut
        data = p, hltPathPass[p], hltPathFail[p], eff
        print '\t{0[0]:<20} Pass {0[1]:<5} Fail {0[2]:<5} Efficiency {0[3]:<10}'.format(data), error_binom(m_eventsVertexOK_FittedVtx_noHLT_lxyCut, hltPathPass[p])
    
if __name__ == "__main__":
    analyzeHLT()
"""
*/
