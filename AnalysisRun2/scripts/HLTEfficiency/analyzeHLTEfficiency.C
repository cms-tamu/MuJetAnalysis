#include <iostream>
using namespace std;
#include <algorithm>    // std::max
#include <stdlib.h>
#include "../Helpers.h"

//============= Global Variables ===========================//
vector<double> mGammaD_0250_eff;
vector<double> mGammaD_0275_eff;
vector<double> mGammaD_0300_eff;
vector<double> mGammaD_0400_eff;
vector<double> mGammaD_0700_eff;
vector<double> mGammaD_1000_eff;
vector<double> mGammaD_1500_eff;
vector<double> mGammaD_2000_eff;
vector<double> mGammaD_8500_eff;

vector<double> mGammaD_0250_eff_uncert;
vector<double> mGammaD_0275_eff_uncert;
vector<double> mGammaD_0300_eff_uncert;
vector<double> mGammaD_0400_eff_uncert;
vector<double> mGammaD_0700_eff_uncert;
vector<double> mGammaD_1000_eff_uncert;
vector<double> mGammaD_1500_eff_uncert;
vector<double> mGammaD_2000_eff_uncert;
vector<double> mGammaD_8500_eff_uncert;

vector<double> mGammaD_0250_cT;
vector<double> mGammaD_0275_cT;
vector<double> mGammaD_0300_cT;
vector<double> mGammaD_0400_cT;
vector<double> mGammaD_0700_cT;
vector<double> mGammaD_1000_cT;
vector<double> mGammaD_1500_cT;
vector<double> mGammaD_2000_cT;
vector<double> mGammaD_8500_cT;

void efficiency_trigger(TString fileName)
{
  bool verbose(false);
  TString dirname(fileName);
  cout << "Tag name " << fileName << endl;
  TChain* chain = new TChain("dummy");
  TString ext("out_ana_");
  
  TString mass_string;
  TString cT_string;
  decodeFileName(fileName, mass_string, cT_string);

  // add files to the chain
  addfilesMany(chain, fileName, ext);

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
  
  const double eff(ev_isDiMuonHLTFired/(1.0*ev_is2DiMuonsIsoTkOK_FittedVtx));
  const double eff_uncert(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_is2DiMuonsIsoTkOK_FittedVtx))*(1- (ev_isDiMuonHLTFired/(1.0*ev_is2DiMuonsIsoTkOK_FittedVtx)) ))/(1.0*ev_is2DiMuonsIsoTkOK_FittedVtx)));

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

  // check if the efficiency makes sense    
  if (not (eff != eff)) {
  
  if(mass_string == "0250"){
	  mGammaD_0250_eff.push_back(eff);  
	  mGammaD_0250_eff_uncert.push_back(eff_uncert);  
	  mGammaD_0250_cT.push_back(cT_double);
  }
  if(mass_string == "0275"){
	  mGammaD_0275_eff.push_back(eff);  
	  mGammaD_0275_eff_uncert.push_back(eff_uncert);  
	  mGammaD_0275_cT.push_back(cT_double);  
  }
  if(mass_string == "0300"){
	  mGammaD_0300_eff.push_back(eff);  
	  mGammaD_0300_eff_uncert.push_back(eff_uncert);  
	  mGammaD_0300_cT.push_back(cT_double);  
  }
  if(mass_string == "0400"){
	  mGammaD_0400_eff.push_back(eff);  
	  mGammaD_0400_eff_uncert.push_back(eff_uncert);  
	  mGammaD_0400_cT.push_back(cT_double);  
  }
  if(mass_string == "0700"){
	  mGammaD_0700_eff.push_back(eff);  
	  mGammaD_0700_eff_uncert.push_back(eff_uncert);  
	  mGammaD_0700_cT.push_back(cT_double);  
  }
  if(mass_string == "1000"){
	  mGammaD_1000_eff.push_back(eff);  
	  mGammaD_1000_eff_uncert.push_back(eff_uncert);  
	  mGammaD_1000_cT.push_back(cT_double);  
  }
  if(mass_string == "1500"){
	  mGammaD_1500_eff.push_back(eff);  
	  mGammaD_1500_eff_uncert.push_back(eff_uncert);  
	  mGammaD_1500_cT.push_back(cT_double);  
  }
  if(mass_string == "2000"){
	  mGammaD_2000_eff.push_back(eff);  
	  mGammaD_2000_eff_uncert.push_back(eff_uncert);  
	  mGammaD_2000_cT.push_back(cT_double);  
  }
  if(mass_string == "8500"){
	  mGammaD_8500_eff.push_back(eff);  
	  mGammaD_8500_eff_uncert.push_back(eff_uncert);  
	  mGammaD_8500_cT.push_back(cT_double);  
  }

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
  
  vector<double> null_0400;
  for(int i=0; i < mGammaD_0400_cT.size(); i++){
    null_0400.push_back(0);
  }
  double* array_null_0400               = &null_0400[0];
  double* array_mGammaD_0400_eff        = &mGammaD_0400_eff[0];
  double* array_mGammaD_0400_eff_uncert = &mGammaD_0400_eff_uncert[0];
  double* array_mGammaD_0400_cT         = &mGammaD_0400_cT[0];
  int size_0400 = null_0400.size();

  TGraphErrors *gr_eff_mD_0400 = new TGraphErrors(size_0400,array_mGammaD_0400_cT,array_mGammaD_0400_eff,array_null_0400,array_mGammaD_0400_eff_uncert);

  vector<double> null_0700;
  for(int i=0; i < mGammaD_0700_cT.size(); i++){
    null_0700.push_back(0);
  }
  double* array_null_0700               = &null_0700[0];
  double* array_mGammaD_0700_eff        = &mGammaD_0700_eff[0];
  double* array_mGammaD_0700_eff_uncert = &mGammaD_0700_eff_uncert[0];
  double* array_mGammaD_0700_cT         = &mGammaD_0700_cT[0];
  int size_0700 = null_0700.size();

  TGraphErrors *gr_eff_mD_0700 = new TGraphErrors(size_0700,array_mGammaD_0700_cT,array_mGammaD_0700_eff,array_null_0700,array_mGammaD_0700_eff_uncert);

  vector<double> null_1000;
  for(int i=0; i < mGammaD_1000_cT.size(); i++){
    null_1000.push_back(0);
  }
  double* array_null_1000               = &null_1000[0];
  double* array_mGammaD_1000_eff        = &mGammaD_1000_eff[0];
  double* array_mGammaD_1000_eff_uncert = &mGammaD_1000_eff_uncert[0];
  double* array_mGammaD_1000_cT         = &mGammaD_1000_cT[0];
  int size_1000 = null_1000.size();

  TGraphErrors *gr_eff_mD_1000 = new TGraphErrors(size_1000,array_mGammaD_1000_cT,array_mGammaD_1000_eff,array_null_1000,array_mGammaD_1000_eff_uncert);

  vector<double> null_1500;
  for(int i=0; i < mGammaD_1500_cT.size(); i++){
    null_1500.push_back(0);
  }
  double* array_null_1500               = &null_1500[0];
  double* array_mGammaD_1500_eff        = &mGammaD_1500_eff[0];
  double* array_mGammaD_1500_eff_uncert = &mGammaD_1500_eff_uncert[0];
  double* array_mGammaD_1500_cT         = &mGammaD_1500_cT[0];
  int size_1500 = null_1500.size();

  TGraphErrors *gr_eff_mD_1500 = new TGraphErrors(size_1500,array_mGammaD_1500_cT,array_mGammaD_1500_eff,array_null_1500,array_mGammaD_1500_eff_uncert);

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
  leg->AddEntry(gr_eff_mD_0400,"m_{#gamma D}=0.400 GeV","PL");
  leg->AddEntry(gr_eff_mD_0700,"m_{#gamma D}=0.700 GeV","PL");
  leg->AddEntry(gr_eff_mD_1000,"m_{#gamma D}=1.000 GeV","PL");
  leg->AddEntry(gr_eff_mD_1500,"m_{#gamma D}=1.500 GeV","PL");
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
  
  gr_eff_mD_0400->SetLineWidth(1);
  gr_eff_mD_0400->SetMarkerSize(5);
  gr_eff_mD_0400->SetLineColor(7);
  gr_eff_mD_0400->SetMarkerColor(7);
  gr_eff_mD_0400->SetMarkerStyle(7);
  gr_eff_mD_0400->Draw("SAME PL");

  gr_eff_mD_0700->SetLineWidth(1);
  gr_eff_mD_0700->SetMarkerSize(5);
  gr_eff_mD_0700->SetLineColor(8);
  gr_eff_mD_0700->SetMarkerColor(8);
  gr_eff_mD_0700->SetMarkerStyle(7);
  gr_eff_mD_0700->Draw("SAME PL");

  gr_eff_mD_1000->SetLineWidth(1);
  gr_eff_mD_1000->SetMarkerSize(5);
  gr_eff_mD_1000->SetLineColor(kOrange+1);
  gr_eff_mD_1000->SetMarkerColor(kOrange+1);
  gr_eff_mD_1000->SetMarkerStyle(7);
  gr_eff_mD_1000->Draw("SAME PL");

  gr_eff_mD_1500->SetLineWidth(1);
  gr_eff_mD_1500->SetMarkerSize(5);
  gr_eff_mD_1500->SetLineColor(kOrange);
  gr_eff_mD_1500->SetMarkerColor(kOrange);
  gr_eff_mD_1500->SetMarkerStyle(7);
  gr_eff_mD_1500->Draw("SAME PL");

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
  c->SaveAs("e_hlt_vs_cT.test.pdf","recreate");
  c->SaveAs("e_hlt_vs_cT.test.C","recreate");
}

void analyzeHLTEfficiency()
{
  //  efficiency_trigger("DarkSUSY_mH_125_mGammaD_0250_cT_000");
  for(auto fileName: DarkSUSY_mH_125_mGammaD_map){
    efficiency_trigger(fileName.first);
  }
  
  // makePlot();
}

