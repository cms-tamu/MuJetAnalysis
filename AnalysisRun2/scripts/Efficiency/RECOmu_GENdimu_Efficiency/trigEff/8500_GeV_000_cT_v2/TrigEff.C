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

//============= Global Variables ===========================//
TFile *BAM = new TFile("Trig_Efficiency_Plots.root","RECREATE");

TH1F *etaNum = new TH1F("etaNum", "etaNum", 60, -3, 3);
TH1F *etaDen = new TH1F("etaDen", "etaDen", 60, -3, 3);

TH1F *pTNum = new TH1F("pTNum", "pTNum", 160, 0, 160);
TH1F *pTDen = new TH1F("pTDen", "pTDen", 160, 0, 160);

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


	Float_t genA0Mu0_px;
	Float_t genA1Mu0_px;
	Float_t genA0Mu1_px;
	Float_t genA1Mu1_px;

	Float_t genA0Mu0_py;
	Float_t genA1Mu0_py;
	Float_t genA0Mu1_py;
	Float_t genA1Mu1_py;

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

		t->SetBranchAddress("genA0_m" , &genA0_m);
		t->SetBranchAddress("genA0_px", &genA0_px);
		t->SetBranchAddress("genA0_py", &genA0_py);
		t->SetBranchAddress("genA0_pz", &genA0_pz);

		t->SetBranchAddress("genA1_m" , &genA1_m);
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

		t->SetBranchAddress("genA0Mu0_px",&genA0Mu0_px);
		t->SetBranchAddress("genA1Mu0_px",&genA1Mu0_px);
		t->SetBranchAddress("genA0Mu1_px",&genA0Mu1_px);
		t->SetBranchAddress("genA1Mu1_px",&genA1Mu1_px);

		t->SetBranchAddress("genA0Mu0_py",&genA0Mu0_py);
		t->SetBranchAddress("genA1Mu0_py",&genA1Mu0_py);
		t->SetBranchAddress("genA0Mu1_py",&genA0Mu1_py);
		t->SetBranchAddress("genA1Mu1_py",&genA1Mu1_py);

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
 double pT_00 = sqrt(genA0Mu0_px*genA0Mu0_px + genA0Mu0_py*genA0Mu0_py);
 double pT_01 = sqrt(genA0Mu1_px*genA0Mu1_px + genA0Mu1_py*genA0Mu1_py);
 double pT_10 = sqrt(genA1Mu0_px*genA1Mu0_px + genA1Mu0_py*genA1Mu0_py);
 double pT_11 = sqrt(genA1Mu1_px*genA1Mu1_px + genA1Mu1_py*genA1Mu1_py);

double leadingPt = 0;
double leadingEta = 0;

if(pT_00 >= pT_01 && pT_00 >= pT_10 && pT_00 >= pT_11){ //00 is leading mu
leadingPt = pT_00;
leadingEta = genA0Mu0_eta;
}
if(pT_01 >= pT_00 && pT_01 >= pT_10 && pT_01 >= pT_11){ //01 is leading mu
leadingPt = pT_01;
leadingEta = genA0Mu1_eta;
}
if(pT_10 >= pT_00 && pT_10 >= pT_01 && pT_10 >= pT_11){ //10 is leading mu
leadingPt = pT_10;
leadingEta = genA1Mu0_eta;
}
if(pT_11 >= pT_00 && pT_11 >= pT_10 && pT_11 >= pT_01){ //11 is leading mu
leadingPt = pT_11;
leadingEta = genA1Mu1_eta;
}


			etaDen->Fill(leadingEta);
			pTDen->Fill(leadingPt);
			if(isDiMuonHLTFired == 1){ 
				etaNum->Fill(leadingEta);
				pTNum->Fill(leadingPt);
			}
		} // closing for loop
		myfile->Close();
	} // closing while loop
	//Print out cutflow table
	//Fill ratio reco/gen vectors to be plotted  
	//Prepare plots and plot variables.  Also Fill final information printout vectors
}

void makePlot(){

TCanvas *c = new TCanvas("c","c",700,500);
	TGraphAsymmErrors *etaEff = new TGraphAsymmErrors(etaNum, etaDen);
	etaEff->GetXaxis()->SetTitle("GEN #eta");
	etaEff->GetYaxis()->SetTitle("HLT Efficiency");
	etaEff->Draw();
	c->SaveAs("TrigEffVsEta.pdf");
	c->SaveAs("TrigEffVsEta.C");

TCanvas *c1 = new TCanvas("c1","c1",700,500);
	TGraphAsymmErrors *pTEff = new TGraphAsymmErrors(pTNum, pTDen);
	pTEff->GetXaxis()->SetTitle("GEN p_{T} [GeV]");
	pTEff->GetYaxis()->SetTitle("HLT Efficiency");
	pTEff->Draw();

	c1->SaveAs("TrigEffVsPT.pdf");
	c1->SaveAs("TrigEffVsPT.C");
}



void TrigEff()
{
	cout << "Begin Fake Investigation" << endl;
	//only run over samples that have individual files (to make it easier to find them with Fireworks)
	//These cT's should be in order.
	//2.0 GeV
	//{{{
/*
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

//Ben's 0.25 GeV sample with ability to extend fiducial cut (also includes vertex sanity checks)
/*
//{{{
efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_000_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_cT_000_Evt_80k_PATANA_APL_v12/160311_152439/Combined/");
efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_005_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_cT_005_Evt_80k_PATANA_APL_v12/160311_152551/Combined/");
efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_010_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_cT_010_Evt_80k_PATANA_APL_v12/160311_152700/Combined/");
efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_020_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_cT_020_Evt_80k_PATANA_APL_v12/160311_152808/Combined/");
efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_050_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_cT_050_Evt_80k_PATANA_APL_v12/160311_152916/Combined/");
efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_100_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_cT_100_Evt_80k_PATANA_APL_v12/160311_153323/Combined/");
efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_200_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_cT_200_Evt_80k_PATANA_APL_v12/160311_153723/Combined/");
efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_300_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_cT_300_Evt_80k_PATANA_APL_v12/160311_153836/Combined/");
efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_500_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_cT_500_Evt_80k_PATANA_APL_v12/160311_154223/Combined/");
efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_1000_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_cT_1000_Evt_80k_PATANA_APL_v12/160311_153212/Combined/");
efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_2000_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_cT_2000_Evt_80k_PATANA_APL_v12/160311_153610/Combined/");
//}}}
*/

	//8.5 GeV sample
	//{{{
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
/*
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
/*
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
*/

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
	makePlot();
	BAM->Write();

}     
