#include <iostream>
using namespace std;
#include <algorithm>    // std::max
#include <stdlib.h>
#include <stdio.h>
#include "string"
#include "fstream"
#include "../Helpers.h"

//============= Global Variables ===========================//
std::vector<double> mGammaD_0250_eff;
std::vector<double> mGammaD_0275_eff;
std::vector<double> mGammaD_0300_eff;
std::vector<double> mGammaD_0400_eff;
std::vector<double> mGammaD_0700_eff;
std::vector<double> mGammaD_1000_eff;
std::vector<double> mGammaD_1500_eff;
std::vector<double> mGammaD_2000_eff;
std::vector<double> mGammaD_8500_eff;

std::vector<double> mGammaD_0250_eff_uncert;
std::vector<double> mGammaD_0275_eff_uncert;
std::vector<double> mGammaD_0300_eff_uncert;
std::vector<double> mGammaD_0400_eff_uncert;
std::vector<double> mGammaD_0700_eff_uncert;
std::vector<double> mGammaD_1000_eff_uncert;
std::vector<double> mGammaD_1500_eff_uncert;
std::vector<double> mGammaD_2000_eff_uncert;
std::vector<double> mGammaD_8500_eff_uncert;

std::vector<double> mGammaD_0250_cT;
std::vector<double> mGammaD_0275_cT;
std::vector<double> mGammaD_0300_cT;
std::vector<double> mGammaD_0400_cT;
std::vector<double> mGammaD_0700_cT;
std::vector<double> mGammaD_1000_cT;
std::vector<double> mGammaD_1500_cT;
std::vector<double> mGammaD_2000_cT;
std::vector<double> mGammaD_8500_cT;

std::map<TString, double > cT_strings = {
  {"000_",0.0}, {"005_", 0.05}, {"010_", 0.10}, {"020_", 0.20}, {"050_", 0.50}, {"100_", 1.00}, 
  {"200_", 2.00}, {"300_", 3.00}, {"500_", 5.00}, {"1000", 10.0}, {"2000", 20.0}
};
std::map<TString, int > mass_colors = {
  {"0250", kRed}, {"0275", kOrange}, {"0300", kSpring}, {"0400", kGreen+2}, {"0700", kAzure+9}, 
  {"1000", kBlue}, {"1500", kViolet+6}, {"2000", kMagenta}, {"8500", kBlack}
};

double calc_eff(double num, double denom)
{
  //eff = num/denom;
  double eff_uncert = sqrt( ((num/(1.0*denom))*(1-(num/(1.0*denom)) ))/(1.0*denom) );
  return eff_uncert;
}

void efficiency_vertex(const std::vector<std::string>& dirNames, int layers = 1){

  bool verbose(false);
  TChain* chain = new TChain("dummy");
  TString ext("out_ana_");

  TString mass_string;
  TString cT_string;
  decodeFileNameMany(dirNames, mass_string, cT_string);
  TString fileName = "DarkSUSY_mH_125_mGammaD_" + mass_string + "_cT_" + cT_string;
  cout << "Tag name " << fileName << endl;

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

  Bool_t is1SelMu17;
  Bool_t is2SelMu8;
  Bool_t is3SelMu8;
  Bool_t is4SelMu8;

  Bool_t is2MuJets;
  Bool_t is2DiMuons;
  Bool_t is2DiMuonsFittedVtxOK;
  Bool_t is2DiMuonsFittedVtxOK_KF;
  Bool_t is2DiMuonsFittedVtxOK_VS;
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

  Float_t diMuonF_FittedVtx_vx;
  Float_t diMuonF_FittedVtx_vy;
  Float_t diMuonF_FittedVtx_vz;

  Float_t diMuonC_FittedVtx_vx;
  Float_t diMuonC_FittedVtx_vy;
  Float_t diMuonC_FittedVtx_vz;

  Float_t diMuonF_ConsistentVtx_vx;
  Float_t diMuonF_ConsistentVtx_vy;
  Float_t diMuonF_ConsistentVtx_vz;

  Float_t diMuonC_ConsistentVtx_vx;
  Float_t diMuonC_ConsistentVtx_vy;
  Float_t diMuonC_ConsistentVtx_vz;

  Float_t diMuonF_FittedVtx_px;
  Float_t diMuonF_FittedVtx_py;
  Float_t diMuonF_FittedVtx_pz;

  Float_t diMuonC_FittedVtx_px;
  Float_t diMuonC_FittedVtx_py;
  Float_t diMuonC_FittedVtx_pz;

  Float_t beamSpot_x;
  Float_t beamSpot_y;
  Float_t beamSpot_z;

  //============= Counters ===========================//

  Double_t ev_all = 0.;
  Double_t ev_isSelMu8 = 0.;
  Double_t ev_isVtxOK = 0.;
  Double_t ev_is2MuJets = 0.;
  Double_t ev_is2DiMuons = 0.;
  Double_t ev_is2DiMuonsFittedVtxOK = 0.;
  Double_t ev_is2DiMuonsFittedVtxOK_C_F_Fid = 0.;
  Double_t ev_is2DiMuonsFittedVtxOK_C_Fid = 0.;
  Double_t ev_is2DiMuonsFittedVtxOK_F_Fid = 0.;
  Double_t ev_is2DiMuonsFittedVtxOK_C_F_Non_Fid = 0.;

  Double_t ev_is2DiMuonsConsistentVtxOK = 0.;
  Double_t ev_is2DiMuonsConsistentVtxOK_C_F_Fid = 0.;
  Double_t ev_is2DiMuonsConsistentVtxOK_C_Fid = 0.;
  Double_t ev_is2DiMuonsConsistentVtxOK_F_Fid = 0.;
  Double_t ev_is2DiMuonsConsistentVtxOK_C_F_Non_Fid = 0.;

  Double_t ev_isPixelHitOK = 0.;
  Double_t ev_is2DiMuonsDzOK_FittedVtx = 0.;
  Double_t ev_is2DiMuonsMassOK_FittedVtx = 0.;
  Double_t ev_is2DiMuonsIsoTkOK_FittedVtx = 0.;
  Double_t ev_isDiMuonHLTFired = 0.;

  Int_t c1genm = 0;
  Int_t c2genm = 0;
  Int_t c3genm = 0;
  Int_t c4genm = 0;
  Int_t ev_4gmlxylzcut = 0;
  Int_t ev_4SelMu = 0;

  Double_t c1recm = 0.;
  Double_t c2recm = 0.;
  Double_t c3recm = 0.;
  Double_t c4recm = 0.;
  
  Double_t ev_GoodFVtx = 0;
  Double_t ev_GoodCVtx = 0;

  TObjArray *fileElements=chain->GetListOfFiles();
  TIter next(fileElements);
  TChainElement *chEl=0;

  TH1F* hist = new TH1F("hist",fileName + " dimuon vertex reconstruction; Events; ",4,0,4);
  hist->GetXaxis()->SetNdivisions(4,true);
  hist->GetXaxis()->SetBinLabel(1, "Both F and C Vtx bad");
  hist->GetXaxis()->SetBinLabel(2, "Only good F Vtx");
  hist->GetXaxis()->SetBinLabel(3, "Only good C Vtx");
  hist->GetXaxis()->SetBinLabel(4, "Both F and C Vtx good");

  while ((chEl=(TChainElement*)next())) {
    if (verbose) std::cout << "running on file " << chEl->GetTitle() << std::endl;
    TFile* myfile = new TFile(chEl->GetTitle());
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

    // RECO Level Selectors
    t->SetBranchAddress("is1SelMu17",                     &is1SelMu17);
    t->SetBranchAddress("is2SelMu8",                      &is2SelMu8);
    t->SetBranchAddress("is3SelMu8",                      &is3SelMu8);
    t->SetBranchAddress("is4SelMu8",                      &is4SelMu8);

    t->SetBranchAddress("is2MuJets",                      &is2MuJets);
    t->SetBranchAddress("is2DiMuons",                     &is2DiMuons);
    t->SetBranchAddress("is2DiMuonsFittedVtxOK",          &is2DiMuonsFittedVtxOK);
    // t->SetBranchAddress("is2DiMuonsFittedVtxOK_KF",          &is2DiMuonsFittedVtxOK_KF);
    // t->SetBranchAddress("is2DiMuonsFittedVtxOK_VS",          &is2DiMuonsFittedVtxOK_VS);
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

    t->SetBranchAddress("diMuonF_FittedVtx_vx", &diMuonF_FittedVtx_vx);
    t->SetBranchAddress("diMuonF_FittedVtx_vy", &diMuonF_FittedVtx_vy);
    t->SetBranchAddress("diMuonF_FittedVtx_vz", &diMuonF_FittedVtx_vz);
    
    t->SetBranchAddress("diMuonC_FittedVtx_vx", &diMuonC_FittedVtx_vx);
    t->SetBranchAddress("diMuonC_FittedVtx_vy", &diMuonC_FittedVtx_vy);
    t->SetBranchAddress("diMuonC_FittedVtx_vz", &diMuonC_FittedVtx_vz);

    t->SetBranchAddress("diMuonF_ConsistentVtx_vx", &diMuonF_ConsistentVtx_vx);
    t->SetBranchAddress("diMuonF_ConsistentVtx_vy", &diMuonF_ConsistentVtx_vy);
    t->SetBranchAddress("diMuonF_ConsistentVtx_vz", &diMuonF_ConsistentVtx_vz);
    
    t->SetBranchAddress("diMuonC_ConsistentVtx_vx", &diMuonC_ConsistentVtx_vx);
    t->SetBranchAddress("diMuonC_ConsistentVtx_vy", &diMuonC_ConsistentVtx_vy);
    t->SetBranchAddress("diMuonC_ConsistentVtx_vz", &diMuonC_ConsistentVtx_vz);

    t->SetBranchAddress("diMuonF_FittedVtx_px", &diMuonF_FittedVtx_px);
    t->SetBranchAddress("diMuonF_FittedVtx_py", &diMuonF_FittedVtx_py);
    t->SetBranchAddress("diMuonF_FittedVtx_pz", &diMuonF_FittedVtx_pz);
    
    t->SetBranchAddress("diMuonC_FittedVtx_px", &diMuonC_FittedVtx_px);
    t->SetBranchAddress("diMuonC_FittedVtx_py", &diMuonC_FittedVtx_py);
    t->SetBranchAddress("diMuonC_FittedVtx_pz", &diMuonC_FittedVtx_pz);

    t->SetBranchAddress("beamSpot_x", &beamSpot_x);
    t->SetBranchAddress("beamSpot_y", &beamSpot_y);
    t->SetBranchAddress("beamSpot_z", &beamSpot_z);

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
      
      bool pixelLayer = false;;
      double pixelLayerRadius = 0.;
      
      if (layers==1) {
	//std::cout << "init layers 1" << std::endl;
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

      if(is1GenMu17) c1genm++;
      if(is2GenMu8)  c2genm++;
      if(is3GenMu8)  c3genm++;
      if(is4GenMu8)  c4genm++;

      if(is1SelMu17) c1recm++;
      if(is2SelMu8)  c2recm++;
      if(is3SelMu8)  c3recm++;
      if(is4SelMu8)  c4recm++;


     /*
      //  ===========   GEN LEVEL information  ==============//
      if(is4GenMu8){
        if(fabs(genA0_Lxy)< pixelLayerRadius && fabs(genA1_Lxy)< pixelLayerRadius && fabs(genA0_Lz)<34.5 && fabs(genA1_Lz)<34.5){
          ev_4gmlxylzcut++;
        }
      }
      if(is4SelMu8){
	if(isVertexOK){
	  ev_isVtxOK++;
	  if(is2MuJets){
	    ev_is2MuJets++;
	    if(is2DiMuons){
	      ev_is2DiMuons++;
	      if(is2DiMuonsFittedVtxOK){
		ev_is2DiMuonsFittedVtxOK++;
		if(pixelLayer and fabs(genA0_Lxy)< pixelLayerRadius && fabs(genA1_Lxy)< pixelLayerRadius && fabs(genA0_Lz)<34.5 && fabs(genA1_Lz)<34.5){
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
      */

      //  ===========   GEN LEVEL information  ==============//
      if(is4GenMu8){
        if(fabs(genA0_Lxy)< pixelLayerRadius && fabs(genA1_Lxy)< pixelLayerRadius && fabs(genA0_Lz)<34.5 && fabs(genA1_Lz)<34.5){
          ev_4gmlxylzcut++;
	  if(is4SelMu8){
	    ev_isSelMu8++;
	    if(isVertexOK){
	      ev_isVtxOK++;
	      if(is2MuJets){
		ev_is2MuJets++;
		if(is2DiMuons){
		  ev_is2DiMuons++;
		  if(pixelLayer){
		    ev_isPixelHitOK++;
		    if(is2DiMuonsFittedVtxOK){
		      ev_is2DiMuonsFittedVtxOK++;
		      bool diMuonF_FittedVtx_fiducial = TMath::Sqrt(diMuonF_FittedVtx_vx*diMuonF_FittedVtx_vx + 
								    diMuonF_FittedVtx_vy*diMuonF_FittedVtx_vy)<pixelLayerRadius and TMath::Abs(diMuonF_FittedVtx_vz < 34.5);
		      bool diMuonC_FittedVtx_fiducial = TMath::Sqrt(diMuonC_FittedVtx_vx*diMuonC_FittedVtx_vx + 
								    diMuonC_FittedVtx_vy*diMuonC_FittedVtx_vy)<pixelLayerRadius and TMath::Abs(diMuonC_FittedVtx_vz < 34.5);

		      bool diMuonF_ConsistentVtx_fiducial = TMath::Sqrt(diMuonF_ConsistentVtx_vx*diMuonF_ConsistentVtx_vx + 
									diMuonF_ConsistentVtx_vy*diMuonF_ConsistentVtx_vy)<pixelLayerRadius and TMath::Abs(diMuonF_ConsistentVtx_vz < 34.5);
		      bool diMuonC_ConsistentVtx_fiducial = TMath::Sqrt(diMuonC_ConsistentVtx_vx*diMuonC_ConsistentVtx_vx + 
									diMuonC_ConsistentVtx_vy*diMuonC_ConsistentVtx_vy)<pixelLayerRadius and TMath::Abs(diMuonC_ConsistentVtx_vz < 34.5);
		      if (diMuonF_FittedVtx_fiducial and diMuonC_FittedVtx_fiducial) ev_is2DiMuonsFittedVtxOK_C_F_Fid++;
		      if (diMuonF_FittedVtx_fiducial and not diMuonC_FittedVtx_fiducial) ev_is2DiMuonsFittedVtxOK_F_Fid++; 
		      if (not diMuonF_FittedVtx_fiducial and diMuonC_FittedVtx_fiducial) ev_is2DiMuonsFittedVtxOK_C_Fid++;
		      if (not diMuonF_FittedVtx_fiducial and not diMuonC_FittedVtx_fiducial) ev_is2DiMuonsFittedVtxOK_C_F_Non_Fid++;
  		    }
		    if(is2DiMuonsConsistentVtxOK){
		      ev_is2DiMuonsConsistentVtxOK++;
		      bool diMuonF_ConsistentVtx_fiducial = TMath::Sqrt(diMuonF_ConsistentVtx_vx*diMuonF_ConsistentVtx_vx + 
								    diMuonF_ConsistentVtx_vy*diMuonF_ConsistentVtx_vy)<pixelLayerRadius and TMath::Abs(diMuonF_ConsistentVtx_vz < 34.5);
		      bool diMuonC_ConsistentVtx_fiducial = TMath::Sqrt(diMuonC_ConsistentVtx_vx*diMuonC_ConsistentVtx_vx + 
								    diMuonC_ConsistentVtx_vy*diMuonC_ConsistentVtx_vy)<pixelLayerRadius and TMath::Abs(diMuonC_ConsistentVtx_vz < 34.5);

		      bool diMuonF_ConsistentVtx_fiducial = TMath::Sqrt(diMuonF_ConsistentVtx_vx*diMuonF_ConsistentVtx_vx + 
									diMuonF_ConsistentVtx_vy*diMuonF_ConsistentVtx_vy)<pixelLayerRadius and TMath::Abs(diMuonF_ConsistentVtx_vz < 34.5);
		      bool diMuonC_ConsistentVtx_fiducial = TMath::Sqrt(diMuonC_ConsistentVtx_vx*diMuonC_ConsistentVtx_vx + 
									diMuonC_ConsistentVtx_vy*diMuonC_ConsistentVtx_vy)<pixelLayerRadius and TMath::Abs(diMuonC_ConsistentVtx_vz < 34.5);
		      if (diMuonF_ConsistentVtx_fiducial and diMuonC_ConsistentVtx_fiducial) ev_is2DiMuonsConsistentVtxOK_C_F_Fid++;
		      if (diMuonF_ConsistentVtx_fiducial and not diMuonC_ConsistentVtx_fiducial) ev_is2DiMuonsConsistentVtxOK_F_Fid++; 
		      if (not diMuonF_ConsistentVtx_fiducial and diMuonC_ConsistentVtx_fiducial) ev_is2DiMuonsConsistentVtxOK_C_Fid++;
		      if (not diMuonF_ConsistentVtx_fiducial and not diMuonC_ConsistentVtx_fiducial) ev_is2DiMuonsConsistentVtxOK_C_F_Non_Fid++;
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
  
  TCanvas *c = new TCanvas("c","c",700,500);
  c->cd();
  gStyle->SetOptStat(1111111);  
  hist->Draw();
  c->SaveAs(fileName + "Vtx.png");

  std::cout<<" Sample: " << fileName << endl;
  std::cout<<" Events          "<<ev_all<<std::endl;
  std::cout<<" ================ GEN MUONS ========================================= "<<std::endl;
  std::cout<<" 1GenMu17                       "<<c1genm<<"   reff "<<c1genm/(ev_all*1.0)<<std::endl;
  std::cout<<" 2GenMu8                        "<<c2genm<<"   reff  "<<c2genm/(c1genm*1.0)<<std::endl;
  std::cout<<" 3GenMu8                        "<<c3genm<<"   reff  "<<c3genm/(c2genm*1.0)<<std::endl;
  std::cout<<" 4GenMu8                        "<<c4genm<<"   reff  "<<c4genm/(c3genm*1.0)<<std::endl;
  std::cout<<" 4GenMu8 Lxy/Lz                 "<<ev_4gmlxylzcut<<"   reff   "<<ev_4gmlxylzcut/(c4genm*1.0)<<std::endl;
  std::cout<<" ================ RECO MUONS ========================================= "<<std::endl;
  std::cout<<" 1RecMu17                       "<<c1recm<<"  reff  "<<c1recm/(ev_4gmlxylzcut*1.0)<<std::endl;
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
  std::cout<<" ratio reco/gen                 "<<ev_isPixelHitOK<<"    reff  "   <<ev_isPixelHitOK/(1.0*ev_4gmlxylzcut)<<std::endl;
  // std::cout<<" Events with 2 muonjets         "<<ev_is2MuJets<<"     reff  "<<ev_is2MuJets/(1.0*ev_isVtxOK)<<std::endl;
  // std::cout<<" Events with 2 Dimuons          "<<ev_is2DiMuons<<"    reff  "<<ev_is2DiMuons/(1.0*ev_is2MuJets)<<std::endl;
  // std::cout<<" Events with 2DimVtxOK          "<<ev_is2DiMuonsFittedVtxOK<<"    reff  "<<ev_is2DiMuonsFittedVtxOK/(1.0*ev_is2DiMuons)<<std::endl;
  // std::cout<<" Events with 2DimHitPix         "<<ev_isPixelHitOK<<"     reff  "<<ev_isPixelHitOK/(1.0*ev_is2DiMuonsFittedVtxOK)<<std::endl;
  const double eff(ev_is2DiMuonsFittedVtxOK/(1.0*ev_isVtxOK));
  cout << eff << endl;
  const double eff_uncert(calc_eff(ev_is2DiMuonsFittedVtxOK, ev_isVtxOK));
  
  //Fill ratio reco/gen vectors to be plotted  

  double cT_double = cT_strings[cT_string];

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

void makePlot(int layers = 1)
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
  double* array_null_2000		= &null_2000[0];
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
    
  TCanvas *c = new TCanvas("c","c",700,500);
  gStyle->SetOptStat(0);

  TH2F *dummy3 = new TH2F("","",400,-0.2,20.2,100,0.7,1.1);
  dummy3->GetXaxis()->SetTitle("c#tau [mm]");
  dummy3->GetYaxis()->SetTitle("Vertex reconstruction efficiency/acceptance");
  dummy3->Draw();
  
  gr_eff_mD_0250->SetLineWidth(1);
  gr_eff_mD_0250->SetMarkerSize(5);
  gr_eff_mD_0250->SetLineColor(mass_colors["0250"]);
  gr_eff_mD_0250->SetMarkerColor(mass_colors["0250"]);
  gr_eff_mD_0250->SetMarkerStyle(7);
  gr_eff_mD_0250->Draw("SAME PL");
  
  gr_eff_mD_0275->SetLineWidth(1);
  gr_eff_mD_0275->SetMarkerSize(5);
  gr_eff_mD_0275->SetLineColor(mass_colors["0275"]);
  gr_eff_mD_0275->SetMarkerColor(mass_colors["0275"]);
  gr_eff_mD_0275->SetMarkerStyle(7);
  gr_eff_mD_0275->Draw("SAME PL");
  
  gr_eff_mD_0300->SetLineWidth(1);
  gr_eff_mD_0300->SetMarkerSize(5);
  gr_eff_mD_0300->SetLineColor(mass_colors["0300"]);
  gr_eff_mD_0300->SetMarkerColor(mass_colors["0300"]);
  gr_eff_mD_0300->SetMarkerStyle(7);
  gr_eff_mD_0300->Draw("SAME PL");
  
  gr_eff_mD_0400->SetLineWidth(1);
  gr_eff_mD_0400->SetMarkerSize(5);
  gr_eff_mD_0400->SetLineColor(mass_colors["0400"]);
  gr_eff_mD_0400->SetMarkerColor(mass_colors["0400"]);
  gr_eff_mD_0400->SetMarkerStyle(7);
  gr_eff_mD_0400->Draw("SAME PL");

  gr_eff_mD_0700->SetLineWidth(1);
  gr_eff_mD_0700->SetMarkerSize(5);
  gr_eff_mD_0700->SetLineColor(mass_colors["0700"]);
  gr_eff_mD_0700->SetMarkerColor(mass_colors["0700"]);
  gr_eff_mD_0700->SetMarkerStyle(7);
  gr_eff_mD_0700->Draw("SAME PL");

  gr_eff_mD_1000->SetLineWidth(1);
  gr_eff_mD_1000->SetMarkerSize(5);
  gr_eff_mD_1000->SetLineColor(mass_colors["1000"]);
  gr_eff_mD_1000->SetMarkerColor(mass_colors["1000"]);
  gr_eff_mD_1000->SetMarkerStyle(7);
  gr_eff_mD_1000->Draw("SAME PL");

  gr_eff_mD_1500->SetLineWidth(1);
  gr_eff_mD_1500->SetMarkerSize(5);
  gr_eff_mD_1500->SetLineColor(mass_colors["1500"]);
  gr_eff_mD_1500->SetMarkerColor(mass_colors["1500"]);
  gr_eff_mD_1500->SetMarkerStyle(7);
  gr_eff_mD_1500->Draw("SAME PL");

  gr_eff_mD_2000->SetLineWidth(1);
  gr_eff_mD_2000->SetMarkerSize(5);
  gr_eff_mD_2000->SetLineColor(mass_colors["2000"]);
  gr_eff_mD_2000->SetMarkerColor(mass_colors["2000"]);
  gr_eff_mD_2000->SetMarkerStyle(7);
  gr_eff_mD_2000->Draw("SAME PL");
  
  gr_eff_mD_8500->SetLineWidth(1);
  gr_eff_mD_8500->SetMarkerSize(5);
  gr_eff_mD_8500->SetLineColor(mass_colors["8500"]);
  gr_eff_mD_8500->SetMarkerColor(mass_colors["8500"]);
  gr_eff_mD_8500->SetMarkerStyle(7);
  gr_eff_mD_8500->Draw("SAME PL");
  
  leg->Draw("same");
  c->SaveAs(TString("e_vertex_KForVS_vs_cT_L" + std::to_string(layers) + "._20160208.pdf"),"recreate");
  //c->SaveAs(TString("e_hlt_vs_cT_L" + std::to_string(layers) + ".C"));
  c->Clear();

  mGammaD_0250_eff.clear();
  mGammaD_0275_eff.clear();
  mGammaD_0300_eff.clear();
  mGammaD_0400_eff.clear();
  mGammaD_0700_eff.clear();
  mGammaD_1000_eff.clear();
  mGammaD_1500_eff.clear();
  mGammaD_2000_eff.clear();
  mGammaD_8500_eff.clear();

  mGammaD_0250_eff_uncert.clear();
  mGammaD_0275_eff_uncert.clear();
  mGammaD_0300_eff_uncert.clear();
  mGammaD_0400_eff_uncert.clear();
  mGammaD_0700_eff_uncert.clear();
  mGammaD_1000_eff_uncert.clear();
  mGammaD_1500_eff_uncert.clear();
  mGammaD_2000_eff_uncert.clear();
  mGammaD_8500_eff_uncert.clear();

  mGammaD_0250_cT.clear();
  mGammaD_0275_cT.clear();
  mGammaD_0300_cT.clear();
  mGammaD_0400_cT.clear();
  mGammaD_0700_cT.clear();
  mGammaD_1000_cT.clear();
  mGammaD_1500_cT.clear();
  mGammaD_2000_cT.clear();
  mGammaD_8500_cT.clear();
}

void Analysis_VertexReconstructionXY()
{
  std::vector< std::vector<string> > DarkSUSY_mH_125_mGammaD_v;
  readTextFileWithSamples("ANASamplesSven2.txt", DarkSUSY_mH_125_mGammaD_v);
  //  readTextFileWithSamples("ANASamplesSven_NoVtxRequirementMuJet.txt", DarkSUSY_mH_125_mGammaD_v);

  for(auto v: DarkSUSY_mH_125_mGammaD_v) efficiency_vertex(v, 1);
  makePlot(1);
  // for(auto v: DarkSUSY_mH_125_mGammaD_v) efficiency_vertex(v, 2);
  // makePlot(2);
  // for(auto v: DarkSUSY_mH_125_mGammaD_v) efficiency_vertex(v, 3);
  // makePlot(3);
}     
