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
float eta_min		= 2.2;	
float eta_max		= 3;
float eta_stepsize	= 0.1;

float lxy_min		= 5;
float lxy_max		= 15;
float lxy_stepsize	= 1;

float exp_min           = 1;
float exp_max           = 2;
float exp_stepsize      = 0.1;

int negCounter = 0;
int goodCounter = 0;
TFile *BAM = new TFile("erec_alphagen_FittedVTX_withEllipticCutEfficiencies.root","RECREATE");

//Plot initialization
//Efficiency plots
TObjArray HList(0);
//Float_t bins_eta[] = {0,.1,.2,.3,.4,.5,.6,.7,.8,.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.1,2.2,2.3,2.4,2.5};
//Int_t binnum_eta = sizeof(bins_eta)/sizeof(Float_t) - 1;


Float_t bins_lxy[] = {0., 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1., 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2., 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3., 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9, 4., 4.2, 4.4, 4.6, 4.8, 5., 5.2, 5.4, 5.6, 5.8, 6};

Int_t binnum_lxy = sizeof(bins_lxy)/sizeof(Float_t) - 1;

void initPlots(){

	//TDirectory *Eff = BAM->mkdir("Eff");
	//Eff->cd();
	//	TObjArray HList(0);

	TString histoname_num_eta = "eta_num"; 
	TH1F *myhist_numeta = ((TH1F *)(HList.FindObject(histoname_num_eta)));
	if(!myhist_numeta){
		myhist_numeta = new TH1F(histoname_num_eta, histoname_num_eta, 100, -5, 5);
		HList.Add(myhist_numeta);
	}
	TString histoname_den_eta = "eta_den";
	TH1F *myhist_deneta = ((TH1F *)(HList.FindObject(histoname_den_eta)));
	if(!myhist_deneta){
		myhist_deneta = new TH1F(histoname_den_eta, histoname_den_eta, 100, -5, 5);
		HList.Add(myhist_deneta);
	}
	TString histoname_num_lxy = "lxy_num";
	TH1F *myhist_numlxy = ((TH1F *)(HList.FindObject(histoname_num_lxy)));
	if(!myhist_numlxy){
		myhist_numlxy = new TH1F(histoname_num_lxy, histoname_num_lxy, binnum_lxy, bins_lxy);
		HList.Add(myhist_numlxy);
	}
	TString histoname_den_lxy = "lxy_den"; 
	TH1F *myhist_denlxy = ((TH1F *)(HList.FindObject(histoname_den_lxy)));
	if(!myhist_denlxy){
		myhist_denlxy = new TH1F(histoname_den_lxy, histoname_den_lxy, binnum_lxy, bins_lxy);
		HList.Add(myhist_denlxy);
	}


}

//RECO level plots
TH1F *reco_num_eta = new TH1F("reco_num_eta","reco_num_eta", 100, -5, 5);
TH1F *reco_den_eta = new TH1F("reco_den_eta","reco_den_eta", 100, -5, 5);

TH1F *reco_num_lxy = new TH1F("reco_num_lxy","reco_num_lxy", binnum_lxy, bins_lxy);
TH1F *reco_den_lxy = new TH1F("reco_den_lxy","reco_den_lxy", binnum_lxy, bins_lxy);

TH2F *Real_Reco_Eta_vs_Lxy = new TH2F("Real_Reco_Eta_vs_Lxy","Real_Reco_Eta_vs_Lxy",100, -5, 5, 800, -80, 80); //In Mathematica Script
TH2F *Fake_Reco_Eta_vs_Lxy = new TH2F("Fake_Reco_Eta_vs_Lxy","Fake_Reco_Eta_vs_Lxy",100, -5, 5, 800, -80, 80); //In Mathematica Script
TH2F *FakeEvent_Reco_Eta_vs_Lxy = new TH2F("FakeEvent_Reco_Eta_vs_Lxy","FakeEvent_Reco_Eta_vs_Lxy",100, -5, 5, 800, -80, 80); //In Mathematica Script

vector<double> mGammaD_0250_eff;
vector<double> mGammaD_0275_eff;
vector<double> mGammaD_0300_eff;
vector<double> mGammaD_2000_eff;
vector<double> mGammaD_8500_eff;
vector<double> mGammaD_0400_eff;
vector<double> mGammaD_0700_eff;
vector<double> mGammaD_1000_eff;
vector<double> mGammaD_1500_eff;

vector<double> mGammaD_0250_eff_uncert;
vector<double> mGammaD_0275_eff_uncert;
vector<double> mGammaD_0300_eff_uncert;
vector<double> mGammaD_2000_eff_uncert;
vector<double> mGammaD_8500_eff_uncert;
vector<double> mGammaD_0400_eff_uncert;
vector<double> mGammaD_0700_eff_uncert;
vector<double> mGammaD_1000_eff_uncert;
vector<double> mGammaD_1500_eff_uncert;

vector<double> mGammaD_0250_cT;
vector<double> mGammaD_0275_cT;
vector<double> mGammaD_0300_cT;
vector<double> mGammaD_2000_cT;
vector<double> mGammaD_8500_cT;
vector<double> mGammaD_0400_cT;
vector<double> mGammaD_0700_cT;
vector<double> mGammaD_1000_cT;
vector<double> mGammaD_1500_cT;

vector< vector<double> > FakeStatistics;

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

void efficiency_hitrecovery(TString fileName){
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

	//============= Counters ===========================//



	vector<double> FakesPerSample;

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

	Int_t uncuttableFakeCounter = 0;
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

			//{{{
			if(is4GenMu8){
				Float_t dphi_gD = My_dPhi(genA1_phi,genA0_phi);
				if(genA0_Lxy<=4.4 && genA1_Lxy<=4.4 && fabs(genA0_Lz)<=34.5 && fabs(genA1_Lz)<=34.5){
					ev_4gmlxylzcut++;
				}
			}

			//}}}


			//  =============  Reco information ====================//
			//{{{
			//cout << "eta, lxy for efficiency: " << eta_cut << ", " << lxy_cut << endl;
			if(is4SelMu8){
				brokenCounter++;
				if(isVertexOK){
					ev_isVtxOK++;
					brokenCounter++;
					if(is2MuJets){
						ev_is2MuJets++;
						brokenCounter++;
						if(is2DiMuons){
							ev_is2DiMuons++;
							brokenCounter++;
							if(is2DiMuonsFittedVtxOK){
								ev_is2DiMuonsFittedVtxOK++;
								brokenCounter++;
								if( (diMuonC_m1_FittedVtx_hitpix==1||diMuonC_m2_FittedVtx_hitpix==1)&&(diMuonF_m1_FittedVtx_hitpix==1||diMuonF_m2_FittedVtx_hitpix==1) ){
									ev_isPixelHitOK++;
									if(is2DiMuonsDzOK_FittedVtx){
										ev_is2DiMuonsDzOK_FittedVtx++;
										brokenCounter++;
										if(is2DiMuonsMassOK_FittedVtx){
											ev_is2DiMuonsMassOK_FittedVtx++;
											brokenCounter++;
											if(is2DiMuonsIsoTkOK_FittedVtx){
												ev_is2DiMuonsIsoTkOK_FittedVtx++;
												brokenCounter++;
												if(is4GenMu8){
					if(isDiMuonHLTFired){
						if(diMuonC_FittedVtx_eta > -800 && diMuonC_FittedVtx_Lxy > -800 && diMuonF_FittedVtx_eta > -800 && diMuonF_FittedVtx_Lxy > -800){
							//if(genA0_Lxy<=5.0 && fabs(genA0_Lz)<=34.5 && genA1_Lxy<=5.0 && fabs(genA1_Lz)<=34.5 ){	
								//if(diMuonC_FittedVtx_Lxy >= 0 && diMuonF_FittedVtx_Lxy >= 0)
								goodCounter++;
								//denominator plots go here
								TString gethist_etaden = "eta_den";
								TH1F *theHist_etaden = ((TH1F *)(HList.FindObject(gethist_etaden)));
								theHist_etaden->Fill(genA0_eta);
								theHist_etaden->Fill(genA1_eta);

								TString gethist_lxyden = "lxy_den";
								TH1F *theHist_lxyden = ((TH1F *)(HList.FindObject(gethist_lxyden)));
								theHist_lxyden->Fill(genA0_Lxy);
								theHist_lxyden->Fill(genA1_Lxy);

								reco_den_eta->Fill(diMuonC_FittedVtx_eta);
								reco_den_eta->Fill(diMuonF_FittedVtx_eta);
								reco_den_lxy->Fill(diMuonC_FittedVtx_Lxy);
								reco_den_lxy->Fill(diMuonF_FittedVtx_Lxy);

								int failure = 0;
								//cout << "" << endl;
		if( ((pow(diMuonC_FittedVtx_eta,2)/pow(2.88,2)) + (pow(diMuonC_FittedVtx_Lxy,2)/pow(8.20,2)) <= 1) || (diMuonC_FittedVtx_Lxy < 0) ){	
		if( ((pow(diMuonF_FittedVtx_eta,2)/pow(2.88,2)) + (pow(diMuonF_FittedVtx_Lxy,2)/pow(8.20,2)) <= 1) || (diMuonF_FittedVtx_Lxy < 0) ){
					ev_isDiMuonHLTFired++;
					brokenCounter++;
					triggerFlag_std++;
					//numerator plots go here

					TString gethist_etanum = "eta_num";
					TH1F *theHist_etanum = ((TH1F *)(HList.FindObject(gethist_etanum)));
					theHist_etanum->Fill(genA0_eta);
					theHist_etanum->Fill(genA1_eta);

					TString gethist_lxynum = "lxy_num";
					TH1F *theHist_lxynum = ((TH1F *)(HList.FindObject(gethist_lxynum)));
					theHist_lxynum->Fill(genA0_Lxy);
					theHist_lxynum->Fill(genA1_Lxy);

					reco_num_eta->Fill(diMuonC_FittedVtx_eta);
					reco_num_eta->Fill(diMuonF_FittedVtx_eta);
					reco_num_lxy->Fill(diMuonC_FittedVtx_Lxy);
				reco_num_lxy->Fill(diMuonF_FittedVtx_Lxy);

				Real_Reco_Eta_vs_Lxy->Fill(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_Lxy);
				Real_Reco_Eta_vs_Lxy->Fill(diMuonF_FittedVtx_eta, diMuonF_FittedVtx_Lxy);

				if(genA0_Lxy > 5.0 || genA1_Lxy > 5.0 || fabs(genA0_Lz) > 34.5 || fabs(genA1_Lz) > 34.5){ //Loop to determine fakes
FakeEvent_Reco_Eta_vs_Lxy->Fill(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_Lxy);
FakeEvent_Reco_Eta_vs_Lxy->Fill(diMuonF_FittedVtx_eta, diMuonF_FittedVtx_Lxy);

////
if(MatchRECOtoGENdimuons(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_phi, diMuonF_FittedVtx_eta, diMuonF_FittedVtx_phi, genA0_eta, genA0_phi, genA1_eta, genA0_phi) == 0){ //diMuonC -> A0, diMuonF -> A1
	if(fabs(genA0_Lxy)>=5.0 || fabs(genA0_Lz)>=34.5){ //A0 is the fake and has match diMuonC
		if(diMuonC_FittedVtx_eta > -800 && diMuonC_FittedVtx_Lxy > -800) Fake_Reco_Eta_vs_Lxy->Fill(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_Lxy);
	}
	if(fabs(genA1_Lxy)>=5.0 || fabs(genA1_Lz)>=34.5){ //A1 is the fake and has match diMuonF
		if(diMuonF_FittedVtx_eta > -800 && diMuonF_FittedVtx_Lxy > -800) Fake_Reco_Eta_vs_Lxy->Fill(diMuonF_FittedVtx_eta, diMuonF_FittedVtx_Lxy);

	}
}else{ //diMuonC -> A1, diMuonF -> A0
	if(fabs(genA0_Lxy)>=5.0 || fabs(genA0_Lz)>=34.5){ //A0 is the fake and has match diMuonF
		if(diMuonF_FittedVtx_eta > -800 && diMuonF_FittedVtx_Lxy > -800) Fake_Reco_Eta_vs_Lxy->Fill(diMuonF_FittedVtx_eta, diMuonF_FittedVtx_Lxy);
	}
	if(fabs(genA1_Lxy)>=5.0 || fabs(genA1_Lz)>=34.5){ //A1 is the fake and has match diMuonC
		if(diMuonC_FittedVtx_eta > -800 && diMuonC_FittedVtx_Lxy > -800) Fake_Reco_Eta_vs_Lxy->Fill(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_Lxy);
	}
}


////
				}
												}
											}

										//}//Fiducial cut

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
				}
			}
			//}}}

		} // closing for loop
		myfile->Close();
	} // closing while loop

	//Prepare plots and plot variables.  Also Fill final information printout vectors
	//{{{

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

	//cout << "negCounter: " << negCounter << endl;
	//cout << "GoodCounter: " << goodCounter << endl;
	//}}}
std::cout<<" ratio reco/gen for " << mass_double << " \t " << cT_double << " \t "<<ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)<<" +/-  "<<sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut))<<std::endl;

	if(mass_string == "0250"){
		mGammaD_0250_eff.push_back(ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut));  
		mGammaD_0250_eff_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut)));  
		mGammaD_0250_cT.push_back(cT_double);
	}
	if(mass_string == "0275"){
		mGammaD_0275_eff.push_back(ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut));  
		mGammaD_0275_eff_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut)));  
		mGammaD_0275_cT.push_back(cT_double);  
	}
	if(mass_string == "0300"){
		mGammaD_0300_eff.push_back(ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut));  
		mGammaD_0300_eff_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut)));  
		mGammaD_0300_cT.push_back(cT_double);  
	}
	if(mass_string == "2000"){
		mGammaD_2000_eff.push_back(ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut));  
		mGammaD_2000_eff_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut)));  
		mGammaD_2000_cT.push_back(cT_double);  
	}
	if(mass_string == "8500"){
		mGammaD_8500_eff.push_back(ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut));  
		mGammaD_8500_eff_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut)));  
		mGammaD_8500_cT.push_back(cT_double);  
	}
	if(mass_string == "0400"){
		mGammaD_0400_eff.push_back(ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut));
		mGammaD_0400_eff_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut)));
		mGammaD_0400_cT.push_back(cT_double);
	}
	if(mass_string == "0700"){
		mGammaD_0700_eff.push_back(ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut));
		mGammaD_0700_eff_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut)));
		mGammaD_0700_cT.push_back(cT_double);
	}
	if(mass_string == "1000"){
		mGammaD_1000_eff.push_back(ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut));
		mGammaD_1000_eff_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut)));
		mGammaD_1000_cT.push_back(cT_double);
	}
	if(mass_string == "1500"){
		mGammaD_1500_eff.push_back(ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut));
		mGammaD_1500_eff_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut)));
		mGammaD_1500_cT.push_back(cT_double);
	}

}

void efficiencyPlots(){
	TCanvas *eta_canvas = new TCanvas("eta_canvas", "eta_canvas", 700, 500);

	TString gethist_etanum = "eta_num";
	TH1F *theHist_etanum = ((TH1F *)(HList.FindObject(gethist_etanum)));
	TString gethist_etaden = "eta_den";
	TH1F *theHist_etaden = ((TH1F *)(HList.FindObject(gethist_etaden)));

	TGraphAsymmErrors *tgraph_eta = new TGraphAsymmErrors(theHist_etanum, theHist_etaden);
	tgraph_eta->SetTitle("");
	tgraph_eta->GetYaxis()->SetTitle("Signal Cut Efficiency");
	tgraph_eta->GetXaxis()->SetTitle("#eta_{GEN}");
	tgraph_eta->SetMaximum(1.1);
	tgraph_eta->SetMinimum(0);
	tgraph_eta->Draw("ALP");
	eta_canvas->SaveAs("eta.pdf");
	eta_canvas->Close();

	TCanvas *lxy_canvas = new TCanvas("lxy_canvas", "lxy_canvas", 700, 500);

	TString gethist_lxynum = "lxy_num";
	TH1F *theHist_lxynum = ((TH1F *)(HList.FindObject(gethist_lxynum)));
	TString gethist_lxyden = "lxy_den";
	TH1F *theHist_lxyden = ((TH1F *)(HList.FindObject(gethist_lxyden)));

	TGraphAsymmErrors *tgraph_lxy = new TGraphAsymmErrors(theHist_lxynum, theHist_lxyden);
	tgraph_lxy->SetTitle("");
	tgraph_lxy->GetYaxis()->SetTitle("Signal Cut Efficiency");
	tgraph_lxy->GetXaxis()->SetTitle("GEN L_{XY} [cm]");
	tgraph_lxy->SetMaximum(1.1);
	tgraph_lxy->SetMinimum(0);
	tgraph_lxy->Draw("ALP");
	lxy_canvas->SaveAs("lxy.pdf");
	lxy_canvas->Close();


	TCanvas *reco_eta_canvas = new TCanvas("reco_eta_canvas", "reco_eta_canvas", 700, 500);

	TGraphAsymmErrors *tgraph_reco_eta = new TGraphAsymmErrors(reco_num_eta, reco_den_eta);
	tgraph_reco_eta->SetTitle("");
	tgraph_reco_eta->GetYaxis()->SetTitle("Signal Cut Efficiency");
	tgraph_reco_eta->GetXaxis()->SetTitle("#eta_{RECO}");
	tgraph_reco_eta->SetMaximum(1.1);
	tgraph_reco_eta->SetMinimum(0);
	tgraph_reco_eta->Draw("ALP");
	reco_eta_canvas->SaveAs("reco_eta.pdf");
	reco_eta_canvas->Close();

	TCanvas *reco_lxy_canvas = new TCanvas("reco_lxy_canvas", "reco_lxy_canvas", 700, 500);

	TGraphAsymmErrors *tgraph_reco_lxy = new TGraphAsymmErrors(reco_num_lxy, reco_den_lxy);
	tgraph_reco_lxy->SetTitle("");
	tgraph_reco_lxy->GetYaxis()->SetTitle("Signal Cut Efficiency");
	tgraph_reco_lxy->GetXaxis()->SetTitle("RECO L_{XY} [cm]");
	tgraph_reco_lxy->SetMaximum(1.1);
	tgraph_reco_lxy->SetMinimum(0);
	tgraph_reco_lxy->Draw("ALP");
	reco_lxy_canvas->SaveAs("reco_lxy.pdf");
	reco_lxy_canvas->Close();

}

void makePlot(){
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

	TLegend *leg = new TLegend(0.5,0.3,0.85,0.6);
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


	TH2F *dummy3 = new TH2F("dummy3","",400,-0.2,20.2,100,0.0,1.0);


	TCanvas *c = new TCanvas("c","c",700,500);
	dummy3->GetXaxis()->SetTitle("c#tau [mm]");
	dummy3->GetYaxis()->SetTitle("#epsilon_{full}/#alpha_{gen}");
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
	gr_eff_mD_1000->SetLineColor(9);
	gr_eff_mD_1000->SetMarkerColor(9);
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
	//c->SaveAs("e_rec_alpha_gen_vs_cT.C");
	c->SaveAs("e_rec_alpha_gen_vs_cT.pdf","recreate");
}

void make2DPlots(){
	TCanvas *a = new TCanvas("a","a",700,500);
	Real_Reco_Eta_vs_Lxy->Draw("colz");
	gStyle->SetOptStat(1);
	Real_Reco_Eta_vs_Lxy->GetXaxis()->SetTitle("#eta");
	Real_Reco_Eta_vs_Lxy->GetYaxis()->SetTitle("L_{XY} [cm]");
	a->SetLogz();
	a->SaveAs("Real_Reco_Eta_vs_Lxy.pdf","recreate");

	TCanvas *b = new TCanvas("b","b",700,500);
	Fake_Reco_Eta_vs_Lxy->Draw("colz");
	gStyle->SetOptStat(1);
	Fake_Reco_Eta_vs_Lxy->GetXaxis()->SetTitle("#eta");
	Fake_Reco_Eta_vs_Lxy->GetYaxis()->SetTitle("L_{XY} [cm]");
	b->SetLogz();
	b->SaveAs("Fake_Reco_Eta_vs_Lxy.pdf","recreate");

	TCanvas *ab = new TCanvas("ab","ab",700,500);
	FakeEvent_Reco_Eta_vs_Lxy->Draw("colz");
	gStyle->SetOptStat(1);
	FakeEvent_Reco_Eta_vs_Lxy->GetXaxis()->SetTitle("#eta");
	FakeEvent_Reco_Eta_vs_Lxy->GetYaxis()->SetTitle("L_{XY} [cm]");
	ab->SetLogz();
	ab->SaveAs("FakeEvent_Reco_Eta_vs_Lxy.pdf","recreate");
}

void FakeInvestigation()
{
	cout << "Begin Efficiency Investigation..." << endl;
	initPlots();
	//only run over samples that have individual files (to make it easier to find them with Fireworks)
	//These cT's should be in order.
	//2.0 GeV
	/*
	//{{{
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");

	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_100_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_300_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_1000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_2000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");

	//}}}
	*/
	//Sven's 0.25 GeV sample

	/*
	//{{{
	efficiency_hitrecovery("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f//");
	efficiency_hitrecovery("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_100_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_300_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	//}}}
	*/


	// Ben's 0.25 GeV sample
	/*
//{{{

	//efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_1000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	//efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_2000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");


	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_1000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_2000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");

	//}}}
	*/
	//8.5 GeV sample
	/*
	//{{{
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_100_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_300_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	//}}}
	*/
	//Jamal's 0.275 GeV sample
	/*
	//{{{
	efficiency_hitrecovery("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_100_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_300_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	//}}}
	*/

	//Alfredo's 0.3 GeV sample
	/*
	//{{{
	efficiency_hitrecovery("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
	efficiency_hitrecovery("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
	efficiency_hitrecovery("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
	efficiency_hitrecovery("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
	efficiency_hitrecovery("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
	efficiency_hitrecovery("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
	//}}}
	*/


	//Ben's 0.275 GeV sample
	/*
	//{{{
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0275_cT_000_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_000_Evt_80k_PATANA_v4/151117_123308/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0275_cT_005_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_005_Evt_80k_PATANA_v4/151117_151528/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0275_cT_010_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_010_Evt_80k_PATANA_v4/151117_151628/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0275_cT_020_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_020_Evt_80k_PATANA_v4/151117_151724/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0275_cT_050_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_050_Evt_80k_PATANA_v4/151117_151824/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0275_cT_100_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_100_Evt_80k_PATANA_v4/151117_151935/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0275_cT_200_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_200_Evt_80k_PATANA_v4/151117_152115/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0275_cT_300_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_300_Evt_80k_PATANA_v4/151117_152230/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0275_cT_500_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_500_Evt_80k_PATANA_v4/151117_152335/asdf/"); 
	//}}}
	*/
	//Ben's 0.3 GeV sample
	/*
	//{{{
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_000_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_000_Evt_80k_PATANA_v4/151117_152519/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_005_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_005_Evt_80k_PATANA_v4/151117_152556/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_010_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_010_Evt_80k_PATANA_v4/151117_152703/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_020_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_020_Evt_80k_PATANA_v4/151117_152813/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_050_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_050_Evt_80k_PATANA_v4/151117_153006/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_100_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_100_Evt_80k_PATANA_v4/151117_153036/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_200_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_200_Evt_80k_PATANA_v4/151117_153141/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_300_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_300_Evt_80k_PATANA_v4/151117_153244/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_500_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_500_Evt_80k_PATANA_v4/151117_153321/asdf/"); 
	//}}}
	*/
	//0.4 GeV sample
	/*
	//{{{
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0400_cT_000_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_000_Evt_80k_PATANA_v4/151117_153421/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0400_cT_005_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_005_Evt_80k_PATANA_v4/151117_153513/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0400_cT_010_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_010_Evt_80k_PATANA_v4/151117_153558/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0400_cT_020_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_020_Evt_80k_PATANA_v4/151117_153657/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0400_cT_050_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_050_Evt_80k_PATANA_v4/151117_153812/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0400_cT_100_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_100_Evt_80k_PATANA_v4/151117_153904/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0400_cT_200_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_200_Evt_80k_PATANA_v4/151117_153951/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0400_cT_300_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_300_Evt_80k_PATANA_v4/151117_154045/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0400_cT_500_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_500_Evt_80k_PATANA_v4/151117_154251/asdf/"); 
	//}}}
	*/
	//0.7 GeV sample
	//{{{
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0700_cT_000_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_000_Evt_80k_PATANA_v4/151117_154344/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0700_cT_005_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_005_Evt_80k_PATANA_v4/151117_154442/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0700_cT_010_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_010_Evt_80k_PATANA_v4/151117_154535/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0700_cT_020_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_020_Evt_80k_PATANA_v4/151117_154632/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0700_cT_050_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_050_Evt_80k_PATANA_v4/151117_154716/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0700_cT_100_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_100_Evt_80k_PATANA_v4/151117_154749/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0700_cT_200_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_200_Evt_80k_PATANA_v4/151117_154834/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0700_cT_300_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_300_Evt_80k_PATANA_v4/151117_154929/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0700_cT_500_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_500_Evt_80k_PATANA_v4/151117_155023/asdf/"); 
	//}}}
	//1.0 GeV sample
	/*
	//{{{
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1000_cT_000_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_000_Evt_80k_PATANA_v4/151117_155128/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1000_cT_005_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_005_Evt_80k_PATANA_v4/151117_155253/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1000_cT_010_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_010_Evt_80k_PATANA_v4/151117_155348/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1000_cT_020_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_020_Evt_80k_PATANA_v4/151117_155445/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1000_cT_050_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_050_Evt_80k_PATANA_v4/151117_155539/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1000_cT_100_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_100_Evt_80k_PATANA_v4/151117_155629/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1000_cT_200_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_200_Evt_80k_PATANA_v4/151117_155726/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1000_cT_300_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_300_Evt_80k_PATANA_v4/151117_155825/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1000_cT_500_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_500_Evt_80k_PATANA_v4/151117_155914/asdf/"); 
	//}}}
	*/
	// 1.5 GeV sample
	/*
	//{{{
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1500_cT_000_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_000_Evt_80k_PATANA_v4/151117_160012/asdf/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1500_cT_005_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_005_Evt_80k_PATANA_v4/151117_160122/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1500_cT_010_Evt_79k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_010_Evt_79k_PATANA_v4/151117_160146/asdf/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1500_cT_020_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_020_Evt_80k_PATANA_v4/151117_160315/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1500_cT_100_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_100_Evt_80k_PATANA_v4/151117_160426/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1500_cT_200_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_200_Evt_80k_PATANA_v4/151117_160522/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1500_cT_300_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_300_Evt_80k_PATANA_v4/151117_160613/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1500_cT_500_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_500_Evt_80k_PATANA_v4/151117_160729/asdf/");
	//}}}
*/	
	//8 TeV samples
	/*	
	//{{{

	//8 Tev
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_000_Evt_80k_8TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0250_cT_000_Evt_80k_PATANA_v4/151117_151201/0000/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_005_Evt_80k_8TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0250_cT_005_Evt_80k_PATANA_v4/151117_151250/0000/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_010_Evt_80k_8TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0250_cT_010_Evt_80k_PATANA_v4/151117_151325/0000/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_020_Evt_80k_8TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0250_cT_020_Evt_80k_PATANA_v4/151117_151402/0000/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_050_Evt_80k_8TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0250_cT_050_Evt_80k_PATANA_v4/151117_151430/0000/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_100_Evt_80k_8TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0250_cT_100_Evt_80k_PATANA_v4/151117_151508/0000/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_200_Evt_80k_8TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0250_cT_200_Evt_80k_PATANA_v4/151117_151538/0000/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_300_Evt_80k_8TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0250_cT_300_Evt_80k_PATANA_v4/151117_151622/0000/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_500_Evt_80k_8TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0250_cT_500_Evt_80k_PATANA_v4/151117_151650/0000/");
	//}}}
	*/
	efficiencyPlots();
	makePlot();
	make2DPlots();
	HList.Write();
	BAM->Write();

}     
