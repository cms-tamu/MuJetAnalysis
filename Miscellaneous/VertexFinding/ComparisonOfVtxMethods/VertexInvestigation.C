#include <iostream>
using namespace std;
#include <algorithm>    // std::max
#include <stdlib.h>
#include <iomanip>
#include "TMath.h"
#include <math.h>
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>
#include "TChain.h"
#include "TGraphErrors.h" 
#include "TCollection.h"
#include "TSystemFile.h"
#include "TSystemDirectory.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TChainElement.h" 
#include "TStyle.h"
#include <TObjArray.h>
#include <TDirectory.h>
#include <TGraphAsymmErrors.h>

//============= Global Variables ===========================//

TFile *BAM = new TFile("Vtx_Investigation.root","RECREATE");

//============== VTX plots ================================//

//Basic distributions
TH1F *GenA0_x = new TH1F("GenA0_x", "GenA0_x", 400, -40, 40);
TH1F *GenA0_y = new TH1F("GenA0_y", "GenA0_y", 400, -40, 40);
TH1F *GenA0_z = new TH1F("GenA0_z", "GenA0_z", 400, -40, 40);

TH1F *GenA1_x = new TH1F("GenA1_x", "GenA1_x", 400, -40, 40);
TH1F *GenA1_y = new TH1F("GenA1_y", "GenA1_y", 400, -40, 40);
TH1F *GenA1_z = new TH1F("GenA1_z", "GenA1_z", 400, -40, 40);

TH1F *FittedC_x = new TH1F("FittedC_x", "FittedC_x", 400, -40, 40);
TH1F *FittedC_y = new TH1F("FittedC_y", "FittedC_y", 400, -40, 40);
TH1F *FittedC_z = new TH1F("FittedC_z", "FittedC_z", 400, -40, 40);

TH1F *FittedF_x = new TH1F("FittedF_x", "FittedF_x", 400, -40, 40);
TH1F *FittedF_y = new TH1F("FittedF_y", "FittedF_y", 400, -40, 40);
TH1F *FittedF_z = new TH1F("FittedF_z", "FittedF_z", 400, -40, 40);

TH1F *ConsistentF_x = new TH1F("ConsistentF_x", "ConsistentF_x", 400, -40, 40);
TH1F *ConsistentF_y = new TH1F("ConsistentF_y", "ConsistentF_y", 400, -40, 40);
TH1F *ConsistentF_z = new TH1F("ConsistentF_z", "ConsistentF_z", 400, -40, 40);

TH1F *ConsistentC_x = new TH1F("ConsistentC_x", "ConsistentC_x", 400, -40, 40);
TH1F *ConsistentC_y = new TH1F("ConsistentC_y", "ConsistentC_y", 400, -40, 40);
TH1F *ConsistentC_z = new TH1F("ConsistentC_z", "ConsistentC_z", 400, -40, 40);

//GEN - Fitted (Kalman)
TH1F *GEN_Fitted_dx = new TH1F("GEN_Fitted_dx", "GEN_Fitted_dx", 100, -10, 10);
TH1F *GEN_Fitted_dy = new TH1F("GEN_Fitted_dy", "GEN_Fitted_dy", 100, -10, 10);
TH1F *GEN_Fitted_dz = new TH1F("GEN_Fitted_dz", "GEN_Fitted_dz", 100, -10, 10);

TH2F *GEN_Fitted_dx_residual_vs_Gen = new TH2F("GEN_Fitted_dx_residual_vs_Gen", "GEN_Fitted_dx_residual_vs_Gen", 400, -40, 40, 100, -10, 10);
TH2F *GEN_Fitted_dy_residual_vs_Gen = new TH2F("GEN_Fitted_dy_residual_vs_Gen", "GEN_Fitted_dy_residual_vs_Gen", 400, -40, 40, 100, -10, 10);
TH2F *GEN_Fitted_dz_residual_vs_Gen = new TH2F("GEN_Fitted_dz_residual_vs_Gen", "GEN_Fitted_dz_residual_vs_Gen", 400, -40, 40, 100, -10, 10);

//GEN - Consistent (DCA)
TH1F *GEN_Consistent_dx = new TH1F("GEN_Consistent_dx", "GEN_Consistent_dx", 100, -10, 10);
TH1F *GEN_Consistent_dy = new TH1F("GEN_Consistent_dy", "GEN_Consistent_dy", 100, -10, 10);
TH1F *GEN_Consistent_dz = new TH1F("GEN_Consistent_dz", "GEN_Consistent_dz", 100, -10, 10);

TH2F *GEN_Consistent_dx_residual_vs_Gen = new TH2F("GEN_Consistent_dx_residual_vs_Gen", "GEN_Consistent_dx_residual_vs_Gen", 400, -40, 40, 100, -10, 10);
TH2F *GEN_Consistent_dy_residual_vs_Gen = new TH2F("GEN_Consistent_dy_residual_vs_Gen", "GEN_Consistent_dy_residual_vs_Gen", 400, -40, 40, 100, -10, 10);
TH2F *GEN_Consistent_dz_residual_vs_Gen = new TH2F("GEN_Consistent_dz_residual_vs_Gen", "GEN_Consistent_dz_residual_vs_Gen", 400, -40, 40, 100, -10, 10);

//Consistent (DCA)
TH1F *Fitted_Consistent_dx = new TH1F("Fitted_Consistent_dx", "Fitted_Consistent_dx", 100, -10, 10);
TH1F *Fitted_Consistent_dy = new TH1F("Fitted_Consistent_dy", "Fitted_Consistent_dy", 100, -10, 10);
TH1F *Fitted_Consistent_dz = new TH1F("Fitted_Consistent_dz", "Fitted_Consistent_dz", 100, -10, 10);


//============= Private Functions ===========================//
double My_dPhi (double phi1, double phi2) {
	double dPhi = phi1 - phi2;
	if (dPhi >  TMath::Pi()) dPhi -= 2*TMath::Pi();
	if (dPhi <  -TMath::Pi()) dPhi += 2*TMath::Pi();
	return abs(dPhi); //Changed to abs 1/5/2016
}


int MatchRECOtoGENdimuons(double etaC, double phiC, double etaF, double phiF, double etaAC, double phiAC, double etaAF, double phiAF){
	int matchInt = -999;
	//match RECO C to GEN C 
	double dphi_CC = My_dPhi(phiC, phiAC);
	double deta_CC = etaC - etaAC;
	double dR_CC   = sqrt(dphi_CC*dphi_CC + deta_CC*deta_CC); 
	//match RECO F to GEN F
	double dphi_FF = My_dPhi(phiF, phiAF);
	double deta_FF = etaF - etaAF;
	double dR_FF   = sqrt(dphi_FF*dphi_FF + deta_FF*deta_FF);
	//match RECO C to GEN F
	double dphi_CF = My_dPhi(phiC, phiAF);
	double deta_CF = etaC - etaAF;
	double dR_CF   = sqrt(dphi_CF*dphi_CF + deta_CF*deta_CF);
	//match RECO F to GEN C
	double dphi_FC = My_dPhi(phiF, phiAC);
	double deta_FC = etaF - etaAC;
	double dR_FC   = sqrt(dphi_FC*dphi_FC + deta_FC*deta_FC);

	if((dR_CC+dR_FF) <= (dR_CF+dR_FC)){
		matchInt = 0; //Then RECO C-> GEN C and RECO F->GEN F
	}else{
		matchInt = 1; //Then RECO C->GEN F and RECO F->GEN C
	}
	return matchInt;
}

void addfiles(TChain *ch, const TString dirname=".", const TString ext=".root")
{
	bool verbose(false);
	TSystemDirectory dir(dirname, dirname);
	TList *files = dir.GetListOfFiles();
	if (files) {
		if (verbose) std::cout << "Found files" << std::endl;
		TSystemFile *file;
		TString fname;
		TIter next(files);
		while ((file=(TSystemFile*)next())) {
			fname = file->GetName();
			if (verbose) std::cout << "found fname " << fname << std::endl;
			if (!file->IsDirectory() && fname.BeginsWith(ext)) {
				if (verbose) std::cout << "adding fname " << fname << std::endl;
				ch->Add(fname);
			}
		}
	}
}

//=================== Main Function ========================//

void InvestigateVertex(TString fileName){
	bool verbose(false);
	TString dirname(fileName);
	TChain* chain = new TChain("dummy");
	TString ext("out_ana_");

	///Get the sample mass
	TString str = fileName;
	TString str2 = "DarkSUSY_mH_125_mGammaD_";
	Ssiz_t first = str.Index(str2);
	Ssiz_t last = str.Index("_cT_");
	TSubString mass_string = (str(first+str2.Length(),4));
	///Get the sample cT
	TString str3 = "_cT_";
	TSubString cT_string = (str(last+str3.Length(),4));

	// add files to the chain
	addfiles(chain, dirname, ext);

	//Initialize Variables and counters
	//{{{

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

	Float_t genA0_eta;
	Float_t genA0_phi;
	Float_t genA1_eta;
	Float_t genA1_phi;

	Float_t selMu0_phi;
	Float_t selMu1_phi;
	Float_t selMu2_phi;
	Float_t selMu3_phi;

	Float_t selMu0_eta;
	Float_t selMu1_eta;
	Float_t selMu2_eta;
	Float_t selMu3_eta;

	Float_t genA0_m;
	Float_t genA0_px;
	Float_t genA0_py;
	Float_t genA0_pz;

	Float_t genA1_m;
	Float_t genA1_px;
	Float_t genA1_py;
	Float_t genA1_pz;

	Float_t diMuonC_FittedVtx_m;
	Float_t diMuonC_FittedVtx_px;
	Float_t diMuonC_FittedVtx_py;
	Float_t diMuonC_FittedVtx_pz;
	Float_t diMuonC_FittedVtx_eta;
	Float_t diMuonC_FittedVtx_phi;
	Float_t diMuonC_FittedVtx_Lxy;
	Float_t diMuonC_FittedVtx_L;

	Float_t diMuonF_FittedVtx_m;
	Float_t diMuonF_FittedVtx_px;
	Float_t diMuonF_FittedVtx_py;
	Float_t diMuonF_FittedVtx_pz;
	Float_t diMuonF_FittedVtx_eta;
	Float_t diMuonF_FittedVtx_phi;
	Float_t diMuonF_FittedVtx_Lxy;
	Float_t diMuonF_FittedVtx_L;

	Float_t genA0Mu0_eta;
	Float_t genA1Mu0_eta;
	Float_t genA0Mu1_eta;
	Float_t genA1Mu1_eta;


	Float_t genA0Mu0_phi;
	Float_t genA1Mu0_phi;
	Float_t genA0Mu1_phi;
	Float_t genA1Mu1_phi;

	//Vertex information
	Float_t genA0_vx;
	Float_t genA0_vy;
	Float_t genA0_vz;

	Float_t genA1_vx;
	Float_t genA1_vy;
	Float_t genA1_vz;

	Float_t genA0Mu0_vx;
	Float_t genA0Mu1_vx;
	Float_t genA1Mu0_vx;
	Float_t genA1Mu1_vx;

	Float_t genA0Mu0_vy;
	Float_t genA0Mu1_vy;
	Float_t genA1Mu0_vy;
	Float_t genA1Mu1_vy;

	Float_t genA0Mu0_vz;
	Float_t genA0Mu1_vz;
	Float_t genA1Mu0_vz;
	Float_t genA1Mu1_vz;

	Float_t diMuonC_FittedVtx_vx;
	Float_t diMuonC_FittedVtx_vy;
	Float_t diMuonC_FittedVtx_vz;

	Float_t diMuonF_FittedVtx_vx;
	Float_t diMuonF_FittedVtx_vy;
	Float_t diMuonF_FittedVtx_vz;

	Float_t diMuonC_ConsistentVtx_m;
	Float_t diMuonC_ConsistentVtx_px;
	Float_t diMuonC_ConsistentVtx_py;
	Float_t diMuonC_ConsistentVtx_pz;
	Float_t diMuonC_ConsistentVtx_eta;
	Float_t diMuonC_ConsistentVtx_phi;
	Float_t diMuonC_ConsistentVtx_Lxy;
	Float_t diMuonC_ConsistentVtx_L;

	Float_t diMuonF_ConsistentVtx_m;
	Float_t diMuonF_ConsistentVtx_px;
	Float_t diMuonF_ConsistentVtx_py;
	Float_t diMuonF_ConsistentVtx_pz;
	Float_t diMuonF_ConsistentVtx_eta;
	Float_t diMuonF_ConsistentVtx_phi;
	Float_t diMuonF_ConsistentVtx_Lxy;
	Float_t diMuonF_ConsistentVtx_L;

	Float_t diMuonC_ConsistentVtx_vx;
	Float_t diMuonC_ConsistentVtx_vy;
	Float_t diMuonC_ConsistentVtx_vz;

	Float_t diMuonF_ConsistentVtx_vx;
	Float_t diMuonF_ConsistentVtx_vy;
	Float_t diMuonF_ConsistentVtx_vz;


	//============= Counters ===========================//

	Int_t ev_all = 0;
	Int_t ev_isVtxOK = 0;
	Int_t ev_is2MuJets = 0;
	Int_t ev_is2DiMuons = 0;
	Int_t ev_is2DiMuonsFittedVtxOK = 0;
	Int_t ev_isPixelHitOK = 0;
	Int_t ev_is2DiMuonsDzOK_FittedVtx = 0;
	Int_t ev_is2DiMuonsMassOK_FittedVtx = 0;
	Int_t ev_is2DiMuonsIsoTkOK_FittedVtx = 0;
	Int_t ev_isDiMuonHLTFired = 0;

	Int_t c1genm = 0;
	Int_t c2genm = 0;
	Int_t c3genm = 0;
	Int_t c4genm = 0;
	Int_t ev_4gmlxylzcut = 0;

	Int_t c1recm = 0;
	Int_t c2recm = 0;
	Int_t c3recm = 0;
	Int_t c4recm = 0;

	//}}}

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

		//Pull variables from nTuple
		//{{{
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

		t->SetBranchAddress("genA1_phi",&genA1_phi);
		t->SetBranchAddress("genA1_eta",&genA1_eta);

		t->SetBranchAddress("genA0_phi",&genA0_phi);
		t->SetBranchAddress("genA0_eta",&genA0_eta);

		t->SetBranchAddress("selMu0_phi",&selMu0_phi);
		t->SetBranchAddress("selMu1_phi",&selMu1_phi);
		t->SetBranchAddress("selMu2_phi",&selMu2_phi);
		t->SetBranchAddress("selMu3_phi",&selMu3_phi);

		t->SetBranchAddress("selMu0_eta",&selMu0_eta);
		t->SetBranchAddress("selMu1_eta",&selMu1_eta);
		t->SetBranchAddress("selMu2_eta",&selMu2_eta);
		t->SetBranchAddress("selMu3_eta",&selMu3_eta);

		t->SetBranchAddress("genA0_m", &genA0_m);
		t->SetBranchAddress("genA0_px", &genA0_px);
		t->SetBranchAddress("genA0_py", &genA0_py);
		t->SetBranchAddress("genA0_pz", &genA0_pz);

		t->SetBranchAddress("genA1_m", &genA1_m);
		t->SetBranchAddress("genA1_px", &genA1_px);
		t->SetBranchAddress("genA1_py", &genA1_py);
		t->SetBranchAddress("genA1_pz", &genA1_pz);

		t->SetBranchAddress("diMuonF_FittedVtx_m", &diMuonF_FittedVtx_m);
		t->SetBranchAddress("diMuonF_FittedVtx_px", &diMuonF_FittedVtx_px);
		t->SetBranchAddress("diMuonF_FittedVtx_py", &diMuonF_FittedVtx_py);
		t->SetBranchAddress("diMuonF_FittedVtx_pz", &diMuonF_FittedVtx_pz);
		t->SetBranchAddress("diMuonF_FittedVtx_eta",&diMuonF_FittedVtx_eta);
		t->SetBranchAddress("diMuonF_FittedVtx_phi",&diMuonF_FittedVtx_phi);
		t->SetBranchAddress("diMuonF_FittedVtx_Lxy",&diMuonF_FittedVtx_Lxy);
		t->SetBranchAddress("diMuonF_FittedVtx_L",&diMuonF_FittedVtx_L);

		t->SetBranchAddress("diMuonC_FittedVtx_m", &diMuonC_FittedVtx_m);
		t->SetBranchAddress("diMuonC_FittedVtx_px", &diMuonC_FittedVtx_px);
		t->SetBranchAddress("diMuonC_FittedVtx_py", &diMuonC_FittedVtx_py);
		t->SetBranchAddress("diMuonC_FittedVtx_pz", &diMuonC_FittedVtx_pz);
		t->SetBranchAddress("diMuonC_FittedVtx_eta",&diMuonC_FittedVtx_eta);
		t->SetBranchAddress("diMuonC_FittedVtx_phi",&diMuonC_FittedVtx_phi);
		t->SetBranchAddress("diMuonC_FittedVtx_Lxy",&diMuonC_FittedVtx_Lxy);
		t->SetBranchAddress("diMuonC_FittedVtx_L",&diMuonC_FittedVtx_L);

		t->SetBranchAddress("genA0Mu0_eta",&genA0Mu0_eta);
		t->SetBranchAddress("genA1Mu0_eta",&genA1Mu0_eta);
		t->SetBranchAddress("genA0Mu1_eta",&genA0Mu1_eta);
		t->SetBranchAddress("genA1Mu1_eta",&genA1Mu1_eta);

		t->SetBranchAddress("genA0Mu0_phi",&genA0Mu0_phi);
		t->SetBranchAddress("genA1Mu0_phi",&genA1Mu0_phi);
		t->SetBranchAddress("genA0Mu1_phi",&genA0Mu1_phi);
		t->SetBranchAddress("genA1Mu1_phi",&genA1Mu1_phi);

		t->SetBranchAddress("genA0_vx", &genA0_vx); 
		t->SetBranchAddress("genA0_vy", &genA0_vy);
		t->SetBranchAddress("genA0_vz", &genA0_vz);

		t->SetBranchAddress("genA1_vx", &genA1_vx);
		t->SetBranchAddress("genA1_vy", &genA1_vy);
		t->SetBranchAddress("genA1_vz", &genA1_vz);

		t->SetBranchAddress("genA0Mu0_vx", &genA0Mu0_vx);
		t->SetBranchAddress("genA0Mu1_vx", &genA0Mu1_vx);
		t->SetBranchAddress("genA1Mu0_vx", &genA1Mu0_vx);
		t->SetBranchAddress("genA1Mu1_vx", &genA1Mu1_vx);

		t->SetBranchAddress("genA0Mu0_vy", &genA0Mu0_vy);
		t->SetBranchAddress("genA0Mu1_vy", &genA0Mu1_vy);
		t->SetBranchAddress("genA1Mu0_vy", &genA1Mu0_vy);
		t->SetBranchAddress("genA1Mu1_vy", &genA1Mu1_vy);

		t->SetBranchAddress("genA0Mu0_vz", &genA0Mu0_vz);
		t->SetBranchAddress("genA0Mu1_vz", &genA0Mu1_vz);
		t->SetBranchAddress("genA1Mu0_vz", &genA1Mu0_vz);
		t->SetBranchAddress("genA1Mu1_vz", &genA1Mu1_vz);

		t->SetBranchAddress("diMuonC_FittedVtx_vx", &diMuonC_FittedVtx_vx);
		t->SetBranchAddress("diMuonC_FittedVtx_vy", &diMuonC_FittedVtx_vy);
		t->SetBranchAddress("diMuonC_FittedVtx_vz", &diMuonC_FittedVtx_vz);

		t->SetBranchAddress("diMuonF_FittedVtx_vx", &diMuonF_FittedVtx_vx);
		t->SetBranchAddress("diMuonF_FittedVtx_vy", &diMuonF_FittedVtx_vy);
		t->SetBranchAddress("diMuonF_FittedVtx_vz", &diMuonF_FittedVtx_vz);


		t->SetBranchAddress("diMuonF_ConsistentVtx_m", &diMuonF_ConsistentVtx_m);
		t->SetBranchAddress("diMuonF_ConsistentVtx_px", &diMuonF_ConsistentVtx_px);
		t->SetBranchAddress("diMuonF_ConsistentVtx_py", &diMuonF_ConsistentVtx_py);
		t->SetBranchAddress("diMuonF_ConsistentVtx_pz", &diMuonF_ConsistentVtx_pz);
		t->SetBranchAddress("diMuonF_ConsistentVtx_eta",&diMuonF_ConsistentVtx_eta);
		t->SetBranchAddress("diMuonF_ConsistentVtx_phi",&diMuonF_ConsistentVtx_phi);
		t->SetBranchAddress("diMuonF_ConsistentVtx_Lxy",&diMuonF_ConsistentVtx_Lxy);
		t->SetBranchAddress("diMuonF_ConsistentVtx_L",&diMuonF_ConsistentVtx_L);

		t->SetBranchAddress("diMuonC_ConsistentVtx_m", &diMuonC_ConsistentVtx_m);
		t->SetBranchAddress("diMuonC_ConsistentVtx_px", &diMuonC_ConsistentVtx_px);
		t->SetBranchAddress("diMuonC_ConsistentVtx_py", &diMuonC_ConsistentVtx_py);
		t->SetBranchAddress("diMuonC_ConsistentVtx_pz", &diMuonC_ConsistentVtx_pz);
		t->SetBranchAddress("diMuonC_ConsistentVtx_eta",&diMuonC_ConsistentVtx_eta);
		t->SetBranchAddress("diMuonC_ConsistentVtx_phi",&diMuonC_ConsistentVtx_phi);
		t->SetBranchAddress("diMuonC_ConsistentVtx_Lxy",&diMuonC_ConsistentVtx_Lxy);
		t->SetBranchAddress("diMuonC_ConsistentVtx_L",&diMuonC_ConsistentVtx_L);

		t->SetBranchAddress("diMuonC_ConsistentVtx_vx", &diMuonC_ConsistentVtx_vx);
		t->SetBranchAddress("diMuonC_ConsistentVtx_vy", &diMuonC_ConsistentVtx_vy);
		t->SetBranchAddress("diMuonC_ConsistentVtx_vz", &diMuonC_ConsistentVtx_vz);

		t->SetBranchAddress("diMuonF_ConsistentVtx_vx", &diMuonF_ConsistentVtx_vx);
		t->SetBranchAddress("diMuonF_ConsistentVtx_vy", &diMuonF_ConsistentVtx_vy);
		t->SetBranchAddress("diMuonF_ConsistentVtx_vz", &diMuonF_ConsistentVtx_vz);



		//}}}

		for(int k=0;k<t->GetEntries();k++){
			t->GetEntry(k);

			ev_all++;

			if(is1GenMu17) c1genm++;
			if(is2GenMu8)  c2genm++;
			if(is3GenMu8)  c3genm++;
			if(is4GenMu8)  c4genm++;

			if(is1SelMu17) c1recm++;
			if(is2SelMu8)  c2recm++;
			if(is3SelMu8)  c3recm++;
			if(is4SelMu8)  c4recm++;

			int triggerFlag_std = 0;
			int triggerFlag_lxy = 0;
			int fakeFlag = 0;
			int realFlag = 0;
			int fakeDimuon1 = 0;
			int fakeDimuon2 = 0;

			int brokenCounter = 0;
			int fakeCounter_dimuon1 = 0;
			int fakeCounter_dimuon2 = 0;
			int fakeCounter_both = 0;

			//  ===========   GEN LEVEL information  ==============//
			/*
			//{{{
			if(is4GenMu8){
			Float_t dphi_gD = My_dPhi(genA1_phi,genA0_phi);
			if(genA0_Lxy<=4.4 && genA1_Lxy<=4.4 && fabs(genA0_Lz)<=34.5 && fabs(genA1_Lz)<=34.5){
			ev_4gmlxylzcut++;
			}
			}

			//}}}
			*/

			//  =============  Reco information ====================//

			//Only compare vertices that pass all non-vtx related requirements
			if(is4SelMu8){
				if(is4GenMu8){
					if(isDiMuonHLTFired){

//GEN level basic distributions
GenA0_x->Fill(genA0Mu0_vx);
GenA0_y->Fill(genA0Mu0_vy);
GenA0_z->Fill(genA0Mu0_vz);

GenA1_x->Fill(genA1Mu1_vx);
GenA1_y->Fill(genA1Mu1_vy);
GenA1_z->Fill(genA1Mu1_vz);

						//Match dimuons and then compare vertices

						//Make sure that both fitted VTX are found
						if(diMuonC_FittedVtx_eta > -800 && diMuonC_FittedVtx_phi > -800 && diMuonF_FittedVtx_eta > -800 && diMuonF_FittedVtx_phi > -800){ 
						//Fitted basic distributions
						FittedC_x->Fill(diMuonC_FittedVtx_vx);
						FittedC_y->Fill(diMuonC_FittedVtx_vy);
						FittedC_z->Fill(diMuonC_FittedVtx_vz);

						FittedF_x->Fill(diMuonF_FittedVtx_vx);
						FittedF_y->Fill(diMuonF_FittedVtx_vy);
						FittedF_z->Fill(diMuonF_FittedVtx_vz);
							//Match Fitted and GEN vertices
							if(MatchRECOtoGENdimuons(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_phi, diMuonF_FittedVtx_eta, diMuonF_FittedVtx_phi, genA0_eta, genA0_phi, genA1_eta, genA1_phi) == 0){ //diMuonC -> A0, diMuonF -> A1
								GEN_Fitted_dx->Fill(diMuonC_FittedVtx_vx - genA0Mu0_vx); 
								GEN_Fitted_dy->Fill(diMuonC_FittedVtx_vy - genA0Mu0_vy); 
								GEN_Fitted_dz->Fill(diMuonC_FittedVtx_vz - genA0Mu0_vz); 

								GEN_Fitted_dx->Fill(diMuonF_FittedVtx_vx - genA1Mu1_vx); 
								GEN_Fitted_dy->Fill(diMuonF_FittedVtx_vy - genA1Mu1_vy);
								GEN_Fitted_dz->Fill(diMuonF_FittedVtx_vz - genA1Mu1_vz);

								GEN_Fitted_dx_residual_vs_Gen->Fill(genA0Mu0_vx, diMuonC_FittedVtx_vx - genA0Mu0_vx); 
								GEN_Fitted_dy_residual_vs_Gen->Fill(genA0Mu0_vy, diMuonC_FittedVtx_vy - genA0Mu0_vy); 
								GEN_Fitted_dz_residual_vs_Gen->Fill(genA0Mu0_vz, diMuonC_FittedVtx_vz - genA0Mu0_vz); 

								GEN_Fitted_dx_residual_vs_Gen->Fill(genA1Mu1_vx, diMuonF_FittedVtx_vx - genA1Mu1_vx);
								GEN_Fitted_dy_residual_vs_Gen->Fill(genA1Mu1_vy, diMuonF_FittedVtx_vy - genA1Mu1_vy);
								GEN_Fitted_dz_residual_vs_Gen->Fill(genA1Mu1_vz, diMuonF_FittedVtx_vz - genA1Mu1_vz);

							}else{ //diMuonC -> A1, diMuonF -> A0
								GEN_Fitted_dx->Fill(diMuonC_FittedVtx_vx - genA1Mu1_vx);
								GEN_Fitted_dy->Fill(diMuonC_FittedVtx_vy - genA1Mu1_vy);
								GEN_Fitted_dz->Fill(diMuonC_FittedVtx_vz - genA1Mu1_vz);

								GEN_Fitted_dx->Fill(diMuonF_FittedVtx_vx - genA0Mu0_vx);
								GEN_Fitted_dy->Fill(diMuonF_FittedVtx_vy - genA0Mu0_vy);
								GEN_Fitted_dz->Fill(diMuonF_FittedVtx_vz - genA0Mu0_vz);

								GEN_Fitted_dx_residual_vs_Gen->Fill(genA1Mu1_vx, diMuonC_FittedVtx_vx - genA1Mu1_vx);
								GEN_Fitted_dy_residual_vs_Gen->Fill(genA1Mu1_vy, diMuonC_FittedVtx_vy - genA1Mu1_vy);
								GEN_Fitted_dz_residual_vs_Gen->Fill(genA1Mu1_vz, diMuonC_FittedVtx_vz - genA1Mu1_vz);

								GEN_Fitted_dx_residual_vs_Gen->Fill(genA0Mu0_vx, diMuonF_FittedVtx_vx - genA0Mu0_vx);
								GEN_Fitted_dy_residual_vs_Gen->Fill(genA0Mu0_vy, diMuonF_FittedVtx_vy - genA0Mu0_vy);
								GEN_Fitted_dz_residual_vs_Gen->Fill(genA0Mu0_vz, diMuonF_FittedVtx_vz - genA0Mu0_vz);
							}
						}

						//Match Consistent and GEN vertices
						if(diMuonC_ConsistentVtx_eta > -800 && diMuonC_ConsistentVtx_phi > -800 && diMuonF_ConsistentVtx_eta > -800 && diMuonF_ConsistentVtx_phi > -800){
						//Consistent basic distributions
							ConsistentC_x->Fill(diMuonC_ConsistentVtx_vx);
							ConsistentC_y->Fill(diMuonC_ConsistentVtx_vy);
							ConsistentC_z->Fill(diMuonC_ConsistentVtx_vz);

							ConsistentF_x->Fill(diMuonF_ConsistentVtx_vx);
							ConsistentF_y->Fill(diMuonF_ConsistentVtx_vy);
							ConsistentF_z->Fill(diMuonF_ConsistentVtx_vz);
							if(MatchRECOtoGENdimuons(diMuonC_ConsistentVtx_eta, diMuonC_ConsistentVtx_phi, diMuonF_ConsistentVtx_eta, diMuonF_ConsistentVtx_phi, genA0_eta, genA0_phi, genA1_eta, genA1_phi) == 0){ //diMuonC -> A0, diMuonF -> A1
								GEN_Consistent_dx->Fill(diMuonC_ConsistentVtx_vx - genA0Mu0_vx);
								GEN_Consistent_dy->Fill(diMuonC_ConsistentVtx_vy - genA0Mu0_vy);
								GEN_Consistent_dz->Fill(diMuonC_ConsistentVtx_vz - genA0Mu0_vz);

								GEN_Consistent_dx->Fill(diMuonF_ConsistentVtx_vx - genA1Mu1_vx);
								GEN_Consistent_dy->Fill(diMuonF_ConsistentVtx_vy - genA1Mu1_vy);
								GEN_Consistent_dz->Fill(diMuonF_ConsistentVtx_vz - genA1Mu1_vz);

								GEN_Consistent_dx_residual_vs_Gen->Fill(genA0Mu0_vx, diMuonC_ConsistentVtx_vx - genA0Mu0_vx);
								GEN_Consistent_dy_residual_vs_Gen->Fill(genA0Mu0_vy, diMuonC_ConsistentVtx_vy - genA0Mu0_vy);
								GEN_Consistent_dz_residual_vs_Gen->Fill(genA0Mu0_vz, diMuonC_ConsistentVtx_vz - genA0Mu0_vz);

								GEN_Consistent_dx_residual_vs_Gen->Fill(genA1Mu1_vx, diMuonF_ConsistentVtx_vx - genA1Mu1_vx);
								GEN_Consistent_dy_residual_vs_Gen->Fill(genA1Mu1_vy, diMuonF_ConsistentVtx_vy - genA1Mu1_vy);
								GEN_Consistent_dz_residual_vs_Gen->Fill(genA1Mu1_vz, diMuonF_ConsistentVtx_vz - genA1Mu1_vz);
							}else{ //diMuonC -> A1, diMuonF -> A0
								GEN_Consistent_dx->Fill(diMuonC_ConsistentVtx_vx - genA1Mu1_vx);
								GEN_Consistent_dy->Fill(diMuonC_ConsistentVtx_vy - genA1Mu1_vy);
								GEN_Consistent_dz->Fill(diMuonC_ConsistentVtx_vz - genA1Mu1_vz);

								GEN_Consistent_dx->Fill(diMuonF_ConsistentVtx_vx - genA0Mu0_vx);
								GEN_Consistent_dy->Fill(diMuonF_ConsistentVtx_vy - genA0Mu0_vy);
								GEN_Consistent_dz->Fill(diMuonF_ConsistentVtx_vz - genA0Mu0_vz);

								GEN_Consistent_dx_residual_vs_Gen->Fill(genA1Mu1_vx, diMuonC_ConsistentVtx_vx - genA1Mu1_vx);
								GEN_Consistent_dy_residual_vs_Gen->Fill(genA1Mu1_vy, diMuonC_ConsistentVtx_vy - genA1Mu1_vy);
								GEN_Consistent_dz_residual_vs_Gen->Fill(genA1Mu1_vz, diMuonC_ConsistentVtx_vz - genA1Mu1_vz);

								GEN_Consistent_dx_residual_vs_Gen->Fill(genA0Mu0_vx, diMuonF_ConsistentVtx_vx - genA0Mu0_vx);
								GEN_Consistent_dy_residual_vs_Gen->Fill(genA0Mu0_vy, diMuonF_ConsistentVtx_vy - genA0Mu0_vy);
								GEN_Consistent_dz_residual_vs_Gen->Fill(genA0Mu0_vz, diMuonF_ConsistentVtx_vz - genA0Mu0_vz);
							}
						}


						if(diMuonC_ConsistentVtx_eta > -800 && diMuonC_ConsistentVtx_phi > -800 && diMuonF_ConsistentVtx_eta > -800 && diMuonF_ConsistentVtx_phi > -800){
							if(diMuonC_FittedVtx_eta > -800 && diMuonC_FittedVtx_phi > -800 && diMuonF_FittedVtx_eta > -800 && diMuonF_FittedVtx_phi > -800){
								//Match Consistent and Fitted vertices
								if(MatchRECOtoGENdimuons(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_phi, diMuonF_FittedVtx_eta, diMuonF_FittedVtx_phi, diMuonC_ConsistentVtx_eta, diMuonC_ConsistentVtx_phi, diMuonF_ConsistentVtx_eta, diMuonF_ConsistentVtx_phi) == 0){ //diMuonCFit -> diMuonCCon, diMuonFFit -> diMuonFCon
									Fitted_Consistent_dx->Fill(diMuonC_ConsistentVtx_vx - diMuonC_FittedVtx_vx);
									Fitted_Consistent_dy->Fill(diMuonC_ConsistentVtx_vy - diMuonC_FittedVtx_vy);
									Fitted_Consistent_dz->Fill(diMuonC_ConsistentVtx_vz - diMuonC_FittedVtx_vz);

									Fitted_Consistent_dx->Fill(diMuonF_ConsistentVtx_vx - diMuonF_FittedVtx_vx);
									Fitted_Consistent_dy->Fill(diMuonF_ConsistentVtx_vy - diMuonF_FittedVtx_vy);
									Fitted_Consistent_dz->Fill(diMuonF_ConsistentVtx_vz - diMuonF_FittedVtx_vz);
								}else{ //diMuonCFit -> diMuonFCon, diMuonFFit -> diMuonCCon
									Fitted_Consistent_dx->Fill(diMuonC_ConsistentVtx_vx - diMuonF_FittedVtx_vx);
									Fitted_Consistent_dy->Fill(diMuonC_ConsistentVtx_vy - diMuonF_FittedVtx_vy);
									Fitted_Consistent_dz->Fill(diMuonC_ConsistentVtx_vz - diMuonF_FittedVtx_vz);

									Fitted_Consistent_dx->Fill(diMuonF_ConsistentVtx_vx - diMuonC_FittedVtx_vx);
									Fitted_Consistent_dy->Fill(diMuonF_ConsistentVtx_vy - diMuonC_FittedVtx_vy);
									Fitted_Consistent_dz->Fill(diMuonF_ConsistentVtx_vz - diMuonC_FittedVtx_vz);

								}
							}
						}
					}//Fired HLT
				}//4 GEN mu
			}//4 sel mu

		} // closing for loop
		myfile->Close();
	} // closing while loop

	//Prepare plots and plot variables.  Also Fill final information printout vectors

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


	double mass_double;
	if(mass_string == "0250") mass_double = 0.25;
	if(mass_string == "0275") mass_double = 0.275;
	if(mass_string == "0300") mass_double = 0.30;
	if(mass_string == "2000") mass_double = 2.0;
	if(mass_string == "8500") mass_double = 8.5;
	if(mass_string == "0400") mass_double = 0.4;
	if(mass_string == "0700") mass_double = 0.7;
	if(mass_string == "1000") mass_double = 1.0;
	if(mass_string == "1500") mass_double = 1.5;

}//End of Main function

void makePlotsPretty(){

TCanvas *a1 = new TCanvas("a1","a1",700,500);
GEN_Fitted_dx->Draw();
gStyle->SetOptStat(1);
GEN_Fitted_dx->GetXaxis()->SetTitle("Fitted VTX_{X} - GEN VTX_{X} [cm]");
a1->SaveAs("GEN_Fitted_dx.pdf","recreate");
a1->Clear();

TCanvas *a2 = new TCanvas("a2","a2",700,500);
GEN_Fitted_dy->Draw();
gStyle->SetOptStat(1);
GEN_Fitted_dy->GetXaxis()->SetTitle("Fitted VTX_{Y} - GEN VTX_{Y} [cm]");
a2->SaveAs("GEN_Fitted_dy.pdf","recreate");
a2->Clear();

TCanvas *a3 = new TCanvas("a3","a3",700,500);
GEN_Fitted_dz->Draw();
gStyle->SetOptStat(1);
GEN_Fitted_dz->GetXaxis()->SetTitle("Fitted VTX_{Z} - GEN VTX_{Z} [cm]");
a3->SaveAs("GEN_Fitted_dz.pdf","recreate");
a3->Clear();

TCanvas *b1 = new TCanvas("b1","b1",700,500);
GEN_Consistent_dx->Draw();
gStyle->SetOptStat(1);
GEN_Consistent_dx->GetXaxis()->SetTitle("Consistent VTX_{X} - GEN VTX_{X} [cm]");
b1->SaveAs("GEN_Consistent_dx.pdf","recreate");
b1->Clear();

TCanvas *b2 = new TCanvas("b2","b2",700,500);
GEN_Consistent_dy->Draw();
gStyle->SetOptStat(1);
GEN_Consistent_dy->GetXaxis()->SetTitle("Consistent VTX_{Y} - GEN VTX_{Y} [cm]");
b2->SaveAs("GEN_Consistent_dy.pdf","recreate");
b2->Clear();

TCanvas *b3 = new TCanvas("b3","b3",700,500);
GEN_Consistent_dz->Draw();
gStyle->SetOptStat(1);
GEN_Consistent_dz->GetXaxis()->SetTitle("Consistent VTX_{Z} - GEN VTX_{Z} [cm]");
b3->SaveAs("GEN_Consistent_dz.pdf","recreate");
b3->Clear();

TCanvas *c1 = new TCanvas("c1","c1",700,500);
Fitted_Consistent_dx->Draw();
gStyle->SetOptStat(1);
Fitted_Consistent_dx->GetXaxis()->SetTitle("Consistent VTX_{X} - Fitted VTX_{X} [cm]");
c1->SaveAs("Fitted_Consistent_dx.pdf","recreate");
c1->Clear();

TCanvas *c2 = new TCanvas("c2","c2",700,500);
Fitted_Consistent_dy->Draw();
gStyle->SetOptStat(1);
Fitted_Consistent_dy->GetXaxis()->SetTitle("Consistent VTX_{Y} - Fitted VTX_{Y} [cm]");
c2->SaveAs("Fitted_Consistent_dy.pdf","recreate");
c2->Clear();

TCanvas *c3 = new TCanvas("c3","c3",700,500);
Fitted_Consistent_dz->Draw();
gStyle->SetOptStat(1);
Fitted_Consistent_dz->GetXaxis()->SetTitle("Consistent VTX_{Z} - Fitted VTX_{Z} [cm]");
c3->SaveAs("Fitted_Consistent_dz.pdf","recreate");
c3->Clear();

//2D plots

TCanvas *d1 = new TCanvas("d1","d1",700,500);
GEN_Fitted_dx_residual_vs_Gen->Draw("colz");
gStyle->SetOptStat(1);
GEN_Fitted_dx_residual_vs_Gen->GetXaxis()->SetTitle("GEN VTX_{X} [cm]");
GEN_Fitted_dx_residual_vs_Gen->GetYaxis()->SetTitle("Fitted VTX_{X} - GEN VTX_{X} [cm]");
d1->SetLogz();
d1->SaveAs("GEN_Fitted_Residual_dx_vs_GEN.pdf", "recreate");
d1->Clear();

TCanvas *d2 = new TCanvas("d2","d2",700,500);
GEN_Fitted_dy_residual_vs_Gen->Draw("colz");
gStyle->SetOptStat(1);
GEN_Fitted_dy_residual_vs_Gen->GetXaxis()->SetTitle("GEN VTX_{Y} [cm]");
GEN_Fitted_dy_residual_vs_Gen->GetYaxis()->SetTitle("Fitted VTX_{Y} - GEN VTX_{Y} [cm]");
d2->SetLogz();
d2->SaveAs("GEN_Fitted_Residual_dy_vs_GEN.pdf", "recreate");
d2->Clear();

TCanvas *d3 = new TCanvas("d3","d3",700,500);
GEN_Fitted_dz_residual_vs_Gen->Draw("colz");
gStyle->SetOptStat(1);
GEN_Fitted_dz_residual_vs_Gen->GetXaxis()->SetTitle("GEN VTX_{Z} [cm]");
GEN_Fitted_dz_residual_vs_Gen->GetYaxis()->SetTitle("Fitted VTX_{Z} - GEN VTX_{Z} [cm]");
d3->SetLogz();
d3->SaveAs("GEN_Fitted_Residual_dz_vs_GEN.pdf", "recreate");
d3->Clear();

TCanvas *e1 = new TCanvas("e1","e1",700,500);
GEN_Consistent_dx_residual_vs_Gen->Draw("colz");
gStyle->SetOptStat(1);
GEN_Consistent_dx_residual_vs_Gen->GetXaxis()->SetTitle("GEN VTX_{X} [cm]");
GEN_Consistent_dx_residual_vs_Gen->GetYaxis()->SetTitle("Consistent VTX_{X} - GEN VTX_{X} [cm]");
e1->SetLogz();
e1->SaveAs("GEN_Consistent_Residual_dx_vs_GEN.pdf", "recreate");
e1->Clear();

TCanvas *e2 = new TCanvas("e2","e2",700,500);
GEN_Consistent_dy_residual_vs_Gen->Draw("colz");
gStyle->SetOptStat(1);
GEN_Consistent_dy_residual_vs_Gen->GetXaxis()->SetTitle("GEN VTX_{Y} [cm]");
GEN_Consistent_dy_residual_vs_Gen->GetYaxis()->SetTitle("Consistent VTX_{Y} - GEN VTX_{Y} [cm]");
e2->SetLogz();
e2->SaveAs("GEN_Consistent_Residual_dy_vs_GEN.pdf", "recreate");
e2->Clear();

TCanvas *e3 = new TCanvas("e3","e3",700,500);
GEN_Consistent_dz_residual_vs_Gen->Draw("colz");
gStyle->SetOptStat(1);
GEN_Consistent_dz_residual_vs_Gen->GetXaxis()->SetTitle("GEN VTX_{Z} [cm]");
GEN_Consistent_dz_residual_vs_Gen->GetYaxis()->SetTitle("Consistent VTX_{Z} - GEN VTX_{Z} [cm]");
e3->SetLogz();
e3->SaveAs("GEN_Consistent_Residual_dz_vs_GEN.pdf", "recreate");
e3->Clear();

}

void VertexInvestigation(){
	cout << "Begin vertex investigation..." << endl;
	//These cT's should be in order.
	//2.0 GeV
	/*
	//{{{
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");

	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_100_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_300_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_1000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_2000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");

	//}}}
	*/
	//Sven's 0.25 GeV sample

	/*
	//{{{
	InvestigateVertex("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f//");
	InvestigateVertex("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	InvestigateVertex("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	InvestigateVertex("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	InvestigateVertex("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	InvestigateVertex("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_100_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	InvestigateVertex("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	InvestigateVertex("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_300_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	InvestigateVertex("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	//}}}
	*/


	// Ben's 0.25 GeV sample
	//{{{

	//InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_1000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	//InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_2000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");


	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_1000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_2000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");

	//}}}
	//8.5 GeV sample
	/*
	//{{{
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_100_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_300_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	//}}}
	*/
	//Jamal's 0.275 GeV sample
	/*
	//{{{
	InvestigateVertex("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	InvestigateVertex("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	InvestigateVertex("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	InvestigateVertex("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	InvestigateVertex("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	InvestigateVertex("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_100_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	InvestigateVertex("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	InvestigateVertex("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_300_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	InvestigateVertex("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	//}}}
	*/

	//Alfredo's 0.3 GeV sample
	/*
	//{{{
	InvestigateVertex("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
	InvestigateVertex("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
	InvestigateVertex("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
	InvestigateVertex("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
	InvestigateVertex("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
	InvestigateVertex("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
	//}}}
	*/


	//Ben's 0.275 GeV sample
	/*
	//{{{
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0275_cT_000_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_000_Evt_80k_PATANA_v4/151117_123308/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0275_cT_005_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_005_Evt_80k_PATANA_v4/151117_151528/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0275_cT_010_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_010_Evt_80k_PATANA_v4/151117_151628/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0275_cT_020_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_020_Evt_80k_PATANA_v4/151117_151724/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0275_cT_050_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_050_Evt_80k_PATANA_v4/151117_151824/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0275_cT_100_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_100_Evt_80k_PATANA_v4/151117_151935/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0275_cT_200_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_200_Evt_80k_PATANA_v4/151117_152115/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0275_cT_300_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_300_Evt_80k_PATANA_v4/151117_152230/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0275_cT_500_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_500_Evt_80k_PATANA_v4/151117_152335/asdf/"); 
	//}}}
	*/
	//Ben's 0.3 GeV sample
	/*
	//{{{
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_000_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_000_Evt_80k_PATANA_v4/151117_152519/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_005_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_005_Evt_80k_PATANA_v4/151117_152556/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_010_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_010_Evt_80k_PATANA_v4/151117_152703/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_020_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_020_Evt_80k_PATANA_v4/151117_152813/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_050_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_050_Evt_80k_PATANA_v4/151117_153006/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_100_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_100_Evt_80k_PATANA_v4/151117_153036/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_200_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_200_Evt_80k_PATANA_v4/151117_153141/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_300_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_300_Evt_80k_PATANA_v4/151117_153244/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_500_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_500_Evt_80k_PATANA_v4/151117_153321/asdf/"); 
	//}}}
	*/
	//0.4 GeV sample
	/*
	//{{{
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0400_cT_000_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_000_Evt_80k_PATANA_v4/151117_153421/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0400_cT_005_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_005_Evt_80k_PATANA_v4/151117_153513/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0400_cT_010_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_010_Evt_80k_PATANA_v4/151117_153558/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0400_cT_020_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_020_Evt_80k_PATANA_v4/151117_153657/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0400_cT_050_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_050_Evt_80k_PATANA_v4/151117_153812/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0400_cT_100_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_100_Evt_80k_PATANA_v4/151117_153904/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0400_cT_200_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_200_Evt_80k_PATANA_v4/151117_153951/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0400_cT_300_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_300_Evt_80k_PATANA_v4/151117_154045/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0400_cT_500_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_500_Evt_80k_PATANA_v4/151117_154251/asdf/"); 
	//}}}
	*/
	//0.7 GeV sample
	/*
	//{{{
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0700_cT_000_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_000_Evt_80k_PATANA_v4/151117_154344/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0700_cT_005_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_005_Evt_80k_PATANA_v4/151117_154442/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0700_cT_010_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_010_Evt_80k_PATANA_v4/151117_154535/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0700_cT_020_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_020_Evt_80k_PATANA_v4/151117_154632/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0700_cT_050_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_050_Evt_80k_PATANA_v4/151117_154716/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0700_cT_100_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_100_Evt_80k_PATANA_v4/151117_154749/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0700_cT_200_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_200_Evt_80k_PATANA_v4/151117_154834/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0700_cT_300_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_300_Evt_80k_PATANA_v4/151117_154929/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0700_cT_500_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_500_Evt_80k_PATANA_v4/151117_155023/asdf/"); 
	//}}}
	*/
	//1.0 GeV sample
	/*
	//{{{
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1000_cT_000_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_000_Evt_80k_PATANA_v4/151117_155128/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1000_cT_005_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_005_Evt_80k_PATANA_v4/151117_155253/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1000_cT_010_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_010_Evt_80k_PATANA_v4/151117_155348/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1000_cT_020_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_020_Evt_80k_PATANA_v4/151117_155445/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1000_cT_050_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_050_Evt_80k_PATANA_v4/151117_155539/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1000_cT_100_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_100_Evt_80k_PATANA_v4/151117_155629/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1000_cT_200_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_200_Evt_80k_PATANA_v4/151117_155726/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1000_cT_300_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_300_Evt_80k_PATANA_v4/151117_155825/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1000_cT_500_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_500_Evt_80k_PATANA_v4/151117_155914/asdf/"); 
	//}}}
	*/
	// 1.5 GeV sample
	/*
	//{{{
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1500_cT_000_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_000_Evt_80k_PATANA_v4/151117_160012/asdf/");
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1500_cT_005_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_005_Evt_80k_PATANA_v4/151117_160122/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1500_cT_010_Evt_79k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_010_Evt_79k_PATANA_v4/151117_160146/asdf/");
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1500_cT_020_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_020_Evt_80k_PATANA_v4/151117_160315/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1500_cT_100_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_100_Evt_80k_PATANA_v4/151117_160426/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1500_cT_200_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_200_Evt_80k_PATANA_v4/151117_160522/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1500_cT_300_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_300_Evt_80k_PATANA_v4/151117_160613/asdf/"); 
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1500_cT_500_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_500_Evt_80k_PATANA_v4/151117_160729/asdf/");
	//}}}
	*/	
	//8 TeV samples
	/*	
	//{{{

	//8 Tev
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_000_Evt_80k_8TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0250_cT_000_Evt_80k_PATANA_v4/151117_151201/0000/");
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_005_Evt_80k_8TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0250_cT_005_Evt_80k_PATANA_v4/151117_151250/0000/");
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_010_Evt_80k_8TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0250_cT_010_Evt_80k_PATANA_v4/151117_151325/0000/");
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_020_Evt_80k_8TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0250_cT_020_Evt_80k_PATANA_v4/151117_151402/0000/");
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_050_Evt_80k_8TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0250_cT_050_Evt_80k_PATANA_v4/151117_151430/0000/");
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_100_Evt_80k_8TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0250_cT_100_Evt_80k_PATANA_v4/151117_151508/0000/");
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_200_Evt_80k_8TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0250_cT_200_Evt_80k_PATANA_v4/151117_151538/0000/");
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_300_Evt_80k_8TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0250_cT_300_Evt_80k_PATANA_v4/151117_151622/0000/");
	InvestigateVertex("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_500_Evt_80k_8TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0250_cT_500_Evt_80k_PATANA_v4/151117_151650/0000/");
	//}}}
	*/


	makePlotsPretty();
	BAM->Write();

}

