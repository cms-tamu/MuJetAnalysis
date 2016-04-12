#include <iostream>
using namespace std;
#include <algorithm>    // std::max
#include <stdlib.h>
#include "TMath.h"
#include <math.h>
//============= Global Variables ===========================//
TFile *BAM = new TFile("erec_alphagen.root","RECREATE");

TH1F *Real_Gen_Lxy = new TH1F("Real_Gen_Lxy", "Real_Gen_Lxy", 400, 0, 80 );
TH1F *Real_Gen_Lz = new TH1F("Real_Gen_Lz", "Real_Gen_Lz", 400, 0, 80 );
TH1F *Real_Gen_Eta = new TH1F("Real_Gen_Eta", "Real_Gen_Eta", 500, -5, 5);
TH1F *Real_Gen_Phi = new TH1F("Real_Gen_Phi", "Real_Gen_Phi", 340, -3.4, 3.4);
TH1F *Real_Gen_pT = new TH1F("Real_Gen_pT", "Real_Gen_pT", 100, 0, 100);
TH2F *Real_Gen_MassCompatability = new TH2F("Real_Gen_MassCompatability","Real_Gen_MassCompatability", 100, 0, 10, 100, 0, 10);
TH2F *Real_Gen_pT_vs_Lxy = new TH2F("Real_Gen_pT_vs_Lxy", "Real_Gen_pT_vs_Lxy", 100,0,100,400,0,80);

TH1F *Real_Reco_Lxy = new TH1F("Real_Reco_Lxy", "Real_Reco_Lxy", 400, 0, 80 );
TH1F *Real_Reco_Eta = new TH1F("Real_Reco_Eta", "Real_Reco_Eta", 500, -5, 5);
TH1F *Real_Reco_Phi = new TH1F("Real_Reco_Phi", "Real_Reco_Phi", 340, -3.4, 3.4);
TH1F *Real_Reco_pT = new TH1F("Real_Reco_pT", "Real_Reco_pT", 100, 0, 100);
TH2F *Real_Reco_MassCompatability = new TH2F("Real_Reco_MassCompatability","Real_Reco_MassCompatability", 100, 0, 10, 100, 0, 10);
TH2F *Real_Reco_pT_vs_Lxy = new TH2F("Real_Reco_pT_vs_Lxy", "Real_Reco_pT_vs_Lxy", 100,0,100,400,0,80);

TH1F *Fake_Gen_Lxy = new TH1F("Fake_Gen_Lxy", "Fake_Gen_Lxy", 400, 0, 80 );
TH1F *Fake_Gen_Lz = new TH1F("Fake_Gen_Lz", "Fake_Gen_Lz", 400, 0, 80 );
TH1F *Fake_Gen_Eta = new TH1F("Fake_Gen_Eta", "Fake_Gen_Eta", 500, -5, 5);
TH1F *Fake_Gen_Phi = new TH1F("Fake_Gen_Phi", "Fake_Gen_Phi", 340, -3.4, 3.4);
TH1F *Fake_Gen_pT = new TH1F("Fake_Gen_pT", "Fake_Gen_pT", 100, 0, 100);
TH2F *Fake_Gen_MassCompatability = new TH2F("Fake_Gen_MassCompatability","Fake_Gen_MassCompatability", 100, 0, 10, 100, 0, 10);
TH2F *Fake_Gen_pT_vs_Lxy = new TH2F("Fake_Gen_pT_vs_Lxy", "Fake_Gen_pT_vs_Lxy", 100,0,100,400,0,80);

TH1F *Fake_Reco_Lxy = new TH1F("Fake_Reco_Lxy", "Fake_Reco_Lxy", 400, 0, 80 );
TH1F *Fake_Reco_Eta = new TH1F("Fake_Reco_Eta", "Fake_Reco_Eta", 500, -5, 5);
TH1F *Fake_Reco_Phi = new TH1F("Fake_Reco_Phi", "Fake_Reco_Phi", 340, -3.4, 3.4);
TH1F *Fake_Reco_pT = new TH1F("Fake_Reco_pT", "Fake_Reco_pT", 100, 0, 100);
TH2F *Fake_Reco_MassCompatability = new TH2F("Fake_Reco_MassCompatability","Fake_Reco_MassCompatability", 100, 0, 10, 100, 0, 10);
TH2F *Fake_Reco_pT_vs_Lxy = new TH2F("Fake_Reco_pT_vs_Lxy", "Fake_Reco_pT_vs_Lxy", 100,0,100,400,0,80);

TH1F *Real_dimuon1_Gen_Lxy = new TH1F("Real_dimuon1_Gen_Lxy", "Real_dimuon1_Gen_Lxy", 400, 0, 80 );
TH1F *Real_dimuon1_Gen_Lz = new TH1F("Real_dimuon1_Gen_Lz", "Real_dimuon1_Gen_Lz", 400, 0, 80 );
TH1F *Real_dimuon1_Gen_Eta = new TH1F("Real_dimuon1_Gen_Eta", "Real_dimuon1_Gen_Eta", 500, -5, 5);
TH1F *Real_dimuon1_Gen_Phi = new TH1F("Real_dimuon1_Gen_Phi", "Real_dimuon1_Gen_Phi", 340, -3.4, 3.4);
TH1F *Real_dimuon1_Gen_pT = new TH1F("Real_dimuon1_Gen_pT", "Real_dimuon1_Gen_pT", 100, 0, 100);
TH2F *Real_dimuon1_Gen_MassCompatability = new TH2F("Real_dimuon1_Gen_MassCompatability","Real_dimuon1_Gen_MassCompatability", 100, 0, 10, 100, 0, 10);
TH2F *Real_dimuon1_Gen_pT_vs_Lxy = new TH2F("Real_dimuon1_Gen_pT_vs_Lxy", "Real_dimuon1_Gen_pT_vs_Lxy", 100,0,100,400,0,80);

TH1F *Real_dimuon1_Reco_Lxy = new TH1F("Real_dimuon1_Reco_Lxy", "Real_dimuon1_Reco_Lxy", 400, 0, 80 );
TH1F *Real_dimuon1_Reco_Eta = new TH1F("Real_dimuon1_Reco_Eta", "Real_dimuon1_Reco_Eta", 500, -5, 5);
TH1F *Real_dimuon1_Reco_Phi = new TH1F("Real_dimuon1_Reco_Phi", "Real_dimuon1_Reco_Phi", 340, -3.4, 3.4);
TH1F *Real_dimuon1_Reco_pT = new TH1F("Real_dimuon1_Reco_pT", "Real_dimuon1_Reco_pT", 100, 0, 100); 
TH2F *Real_dimuon1_Reco_MassCompatability = new TH2F("Real_dimuon1_Reco_MassCompatability","Real_dimuon1_Reco_MassCompatability", 100, 0, 10, 100, 0, 10);
TH2F *Real_dimuon1_Reco_pT_vs_Lxy = new TH2F("Real_dimuon1_Reco_pT_vs_Lxy", "Real_dimuon1_Reco_pT_vs_Lxy", 100,0,100,400,0,80);

TH1F *Fake_dimuon1_Gen_Lxy = new TH1F("Fake_dimuon1_Gen_Lxy", "Fake_dimuon1_Gen_Lxy", 400, 0, 80 );
TH1F *Fake_dimuon1_Gen_Lz = new TH1F("Fake_dimuon1_Gen_Lz", "Fake_dimuon1_Gen_Lz", 400, 0, 80 ); 
TH1F *Fake_dimuon1_Gen_Eta = new TH1F("Fake_dimuon1_Gen_Eta", "Fake_dimuon1_Gen_Eta", 500, -5, 5);
TH1F *Fake_dimuon1_Gen_Phi = new TH1F("Fake_dimuon1_Gen_Phi", "Fake_dimuon1_Gen_Phi", 340, -3.4, 3.4);
TH1F *Fake_dimuon1_Gen_pT = new TH1F("Fake_dimuon1_Gen_pT", "Fake_dimuon1_Gen_pT", 100, 0, 100); 
TH2F *Fake_dimuon1_Gen_MassCompatability = new TH2F("Fake_dimuon1_Gen_MassCompatability","Fake_dimuon1_Gen_MassCompatability", 100, 0, 10, 100, 0, 10);
TH2F *Fake_dimuon1_Gen_pT_vs_Lxy = new TH2F("Fake_dimuon1_Gen_pT_vs_Lxy", "Fake_dimuon1_Gen_pT_vs_Lxy", 100,0,100,400,0,80);

TH1F *Fake_dimuon1_Reco_Lxy = new TH1F("Fake_dimuon1_Reco_Lxy", "Fake_dimuon1_Reco_Lxy", 400, 0, 80 );
TH1F *Fake_dimuon1_Reco_Eta = new TH1F("Fake_dimuon1_Reco_Eta", "Fake_dimuon1_Reco_Eta", 500, -5, 5);
TH1F *Fake_dimuon1_Reco_Phi = new TH1F("Fake_dimuon1_Reco_Phi", "Fake_dimuon1_Reco_Phi", 340, -3.4, 3.4);
TH1F *Fake_dimuon1_Reco_pT = new TH1F("Fake_dimuon1_Reco_pT", "Fake_dimuon1_Reco_pT", 100, 0, 100); 
TH2F *Fake_dimuon1_Reco_MassCompatability = new TH2F("Fake_dimuon1_Reco_MassCompatability","Fake_dimuon1_Reco_MassCompatability", 100, 0, 10, 100, 0, 10);
TH2F *Fake_dimuon1_Reco_pT_vs_Lxy = new TH2F("Fake_dimuon1_Reco_pT_vs_Lxy", "Fake_dimuon1_Reco_pT_vs_Lxy", 100,0,100,400,0,80);

TH1F *Real_dimuon2_Gen_Lxy = new TH1F("Real_dimuon2_Gen_Lxy", "Real_dimuon2_Gen_Lxy", 400, 0, 80 );
TH1F *Real_dimuon2_Gen_Lz = new TH1F("Real_dimuon2_Gen_Lz", "Real_dimuon2_Gen_Lz", 400, 0, 80 );
TH1F *Real_dimuon2_Gen_Eta = new TH1F("Real_dimuon2_Gen_Eta", "Real_dimuon2_Gen_Eta", 500, -5, 5);
TH1F *Real_dimuon2_Gen_Phi = new TH1F("Real_dimuon2_Gen_Phi", "Real_dimuon2_Gen_Phi", 340, -3.4, 3.4);
TH1F *Real_dimuon2_Gen_pT = new TH1F("Real_dimuon2_Gen_pT", "Real_dimuon2_Gen_pT", 100, 0, 100);
TH2F *Real_dimuon2_Gen_MassCompatability = new TH2F("Real_dimuon2_Gen_MassCompatability","Real_dimuon2_Gen_MassCompatability", 100, 0, 10, 100, 0, 10);
TH2F *Real_dimuon2_Gen_pT_vs_Lxy = new TH2F("Real_dimuon2_Gen_pT_vs_Lxy", "Real_dimuon2_Gen_pT_vs_Lxy", 100,0,100,400,0,80);

TH1F *Real_dimuon2_Reco_Lxy = new TH1F("Real_dimuon2_Reco_Lxy", "Real_dimuon2_Reco_Lxy", 400, 0, 80 );
TH1F *Real_dimuon2_Reco_Eta = new TH1F("Real_dimuon2_Reco_Eta", "Real_dimuon2_Reco_Eta", 500, -5, 5);
TH1F *Real_dimuon2_Reco_Phi = new TH1F("Real_dimuon2_Reco_Phi", "Real_dimuon2_Reco_Phi", 340, -3.4, 3.4);
TH1F *Real_dimuon2_Reco_pT = new TH1F("Real_dimuon2_Reco_pT", "Real_dimuon2_Reco_pT", 100, 0, 100); 
TH2F *Real_dimuon2_Reco_MassCompatability = new TH2F("Real_dimuon2_Reco_MassCompatability","Real_dimuon2_Reco_MassCompatability", 100, 0, 10, 100, 0, 10);
TH2F *Real_dimuon2_Reco_pT_vs_Lxy = new TH2F("Real_dimuon2_Reco_pT_vs_Lxy", "Real_dimuon2_Reco_pT_vs_Lxy", 100,0,100,400,0,80);

TH1F *Fake_dimuon2_Gen_Lxy = new TH1F("Fake_dimuon2_Gen_Lxy", "Fake_dimuon2_Gen_Lxy", 400, 0, 80 );
TH1F *Fake_dimuon2_Gen_Lz = new TH1F("Fake_dimuon2_Gen_Lz", "Fake_dimuon2_Gen_Lz", 400, 0, 80 ); 
TH1F *Fake_dimuon2_Gen_Eta = new TH1F("Fake_dimuon2_Gen_Eta", "Fake_dimuon2_Gen_Eta", 500, -5, 5);
TH1F *Fake_dimuon2_Gen_Phi = new TH1F("Fake_dimuon2_Gen_Phi", "Fake_dimuon2_Gen_Phi", 340, -3.4, 3.4);
TH1F *Fake_dimuon2_Gen_pT = new TH1F("Fake_dimuon2_Gen_pT", "Fake_dimuon2_Gen_pT", 100, 0, 100); 
TH2F *Fake_dimuon2_Gen_MassCompatability = new TH2F("Fake_dimuon2_Gen_MassCompatability","Fake_dimuon2_Gen_MassCompatability", 100, 0, 10, 100, 0, 10);
TH2F *Fake_dimuon2_Gen_pT_vs_Lxy = new TH2F("Fake_dimuon2_Gen_pT_vs_Lxy", "Fake_dimuon2_Gen_pT_vs_Lxy", 100,0,100,400,0,80);

TH1F *Fake_dimuon2_Reco_Lxy = new TH1F("Fake_dimuon2_Reco_Lxy", "Fake_dimuon2_Reco_Lxy", 400, 0, 80 );
TH1F *Fake_dimuon2_Reco_Eta = new TH1F("Fake_dimuon2_Reco_Eta", "Fake_dimuon2_Reco_Eta", 500, -5, 5);
TH1F *Fake_dimuon2_Reco_Phi = new TH1F("Fake_dimuon2_Reco_Phi", "Fake_dimuon2_Reco_Phi", 340, -3.4, 3.4);
TH1F *Fake_dimuon2_Reco_pT = new TH1F("Fake_dimuon2_Reco_pT", "Fake_dimuon2_Reco_pT", 100, 0, 100); 
TH2F *Fake_dimuon2_Reco_MassCompatability = new TH2F("Fake_dimuon2_Reco_MassCompatability","Fake_dimuon2_Reco_MassCompatability", 100, 0, 10, 100, 0, 10);
TH2F *Fake_dimuon2_Reco_pT_vs_Lxy = new TH2F("Fake_dimuon2_Reco_pT_vs_Lxy", "Fake_dimuon2_Reco_pT_vs_Lxy", 100,0,100,400,0,80);


//2 Dimensional RECO level plots

TH2F *Real_Reco_Eta_vs_Phi = new TH2F("Real_Reco_Eta_vs_Phi","Real_Reco_Eta_vs_Phi",500, -5, 5, 340, -3.4, 3.4);
TH2F *Fake_Reco_Eta_vs_Phi = new TH2F("Fake_Reco_Eta_vs_Phi","Fake_Reco_Eta_vs_Phi",500, -5, 5, 340, -3.4, 3.4);
TH2F *Fake_dimuon1_Reco_Eta_vs_Phi = new TH2F("Fake_dimuon1_Reco_Eta_vs_Phi","Fake_dimuon1_Reco_Eta_vs_Phi",500, -5, 5, 340, -3.4, 3.4);
TH2F *Fake_dimuon2_Reco_Eta_vs_Phi = new TH2F("Fake_dimuon2_Reco_Eta_vs_Phi","Fake_dimuon2_Reco_Eta_vs_Phi",500, -5, 5, 340, -3.4, 3.4);
TH2F *Real_dimuon1_Reco_Eta_vs_Phi = new TH2F("Real_dimuon1_Reco_Eta_vs_Phi","Real_dimuon1_Reco_Eta_vs_Phi",500, -5, 5, 340, -3.4, 3.4);
TH2F *Real_dimuon2_Reco_Eta_vs_Phi = new TH2F("Real_dimuon2_Reco_Eta_vs_Phi","Real_dimuon2_Reco_Eta_vs_Phi",500, -5, 5, 340, -3.4, 3.4);

TH2F *Real_Reco_Eta_vs_Lxy = new TH2F("Real_Reco_Eta_vs_Lxy","Real_Reco_Eta_vs_Lxy",500, -5, 5, 400, 0, 80);
TH2F *Fake_Reco_Eta_vs_Lxy = new TH2F("Fake_Reco_Eta_vs_Lxy","Fake_Reco_Eta_vs_Lxy",500, -5, 5, 400, 0, 80);
TH2F *Fake_dimuon1_Reco_Eta_vs_Lxy = new TH2F("Fake_dimuon1_Reco_Eta_vs_Lxy","Fake_dimuon1_Reco_Eta_vs_Lxy",500, -5, 5, 400, 0, 80);
TH2F *Fake_dimuon2_Reco_Eta_vs_Lxy = new TH2F("Fake_dimuon2_Reco_Eta_vs_Lxy","Fake_dimuon2_Reco_Eta_vs_Lxy",500, -5, 5, 400, 0, 80);
TH2F *Real_dimuon1_Reco_Eta_vs_Lxy = new TH2F("Real_dimuon1_Reco_Eta_vs_Lxy","Real_dimuon1_Reco_Eta_vs_Lxy",500, -5, 5, 400, 0, 80);
TH2F *Real_dimuon2_Reco_Eta_vs_Lxy = new TH2F("Real_dimuon2_Reco_Eta_vs_Lxy","Real_dimuon2_Reco_Eta_vs_Lxy",500, -5, 5, 400, 0, 80);




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

double My_dPhi (double phi1, double phi2) {
	double dPhi = phi1 - phi2;
	if (dPhi >  TMath::Pi()) dPhi -= 2*TMath::Pi();
	if (dPhi <  -TMath::Pi()) dPhi += 2*TMath::Pi();
	return dPhi;
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


	Float_t diMuonF_FittedVtx_m;
	Float_t diMuonF_FittedVtx_px;
	Float_t diMuonF_FittedVtx_py;
	Float_t diMuonF_FittedVtx_pz;
	Float_t diMuonF_FittedVtx_eta;
	Float_t diMuonF_FittedVtx_phi;
	Float_t diMuonF_FittedVtx_Lxy;


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

		t->SetBranchAddress("diMuonC_FittedVtx_m", &diMuonC_FittedVtx_m);
		t->SetBranchAddress("diMuonC_FittedVtx_px", &diMuonC_FittedVtx_px);
		t->SetBranchAddress("diMuonC_FittedVtx_py", &diMuonC_FittedVtx_py);
		t->SetBranchAddress("diMuonC_FittedVtx_pz", &diMuonC_FittedVtx_pz);
		t->SetBranchAddress("diMuonC_FittedVtx_eta",&diMuonC_FittedVtx_eta);
		t->SetBranchAddress("diMuonC_FittedVtx_phi",&diMuonC_FittedVtx_phi);
		t->SetBranchAddress("diMuonC_FittedVtx_Lxy",&diMuonC_FittedVtx_Lxy);


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

			//  ===========   GEN LEVEL information  ==============//
			if(is4GenMu8){
				Float_t dphi_gD = My_dPhi(genA1_phi,genA0_phi);
				//if(fabs(dphi_gD)>=2.5){
				if(fabs(genA0_Lxy)<4.4 && fabs(genA1_Lxy)<4.4 && fabs(genA0_Lz)<34.5 && fabs(genA1_Lz)<34.5){
					ev_4gmlxylzcut++;
				}
				//}
			}
			//  =============  Reco information ====================//

			//if(is4GenMu8)
			//      if(fabs(genA0_Lxy)<4.4 && fabs(genA1_Lxy)<4.4 && fabs(genA0_Lz)<34.5 && fabs(genA1_Lz)<34.5)

			Float_t dphi_gD = My_dPhi(genA1_phi,genA0_phi);
			//if(fabs(dphi_gD)>=2.5){
			if(is4SelMu8){
				if(isVertexOK){
					ev_isVtxOK++;
					if(is2MuJets){
						ev_is2MuJets++;
						if(is2DiMuons){
							ev_is2DiMuons++;
							if(is2DiMuonsFittedVtxOK){
								ev_is2DiMuonsFittedVtxOK++;
								if( (diMuonC_m1_FittedVtx_hitpix==1||diMuonC_m2_FittedVtx_hitpix==1)&&(diMuonF_m1_FittedVtx_hitpix==1||diMuonF_m2_FittedVtx_hitpix==1) ){
									ev_isPixelHitOK++;
									if(is2DiMuonsDzOK_FittedVtx){
										ev_is2DiMuonsDzOK_FittedVtx++;
										if(is2DiMuonsMassOK_FittedVtx){
											ev_is2DiMuonsMassOK_FittedVtx++;
											if(is2DiMuonsIsoTkOK_FittedVtx){
												ev_is2DiMuonsIsoTkOK_FittedVtx++;
												if(isDiMuonHLTFired){
													ev_isDiMuonHLTFired++;
													triggerFlag_std++;
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
			//}
			if(is4GenMu8){
				if(fabs(genA0_Lxy)<4.4 && fabs(genA1_Lxy)<4.4 && fabs(genA0_Lz)<34.5 && fabs(genA1_Lz)<34.5){
					triggerFlag_lxy++;
				}
			}
			if(triggerFlag_std > 0 && triggerFlag_lxy > 0){
				realFlag++;

				Real_Gen_Lxy->Fill(genA0_Lxy);
				Real_Gen_Lxy->Fill(genA1_Lxy);		
				Real_Gen_Lz->Fill(genA0_Lz); 
				Real_Gen_Lz->Fill(genA1_Lz); 
				Real_Gen_Eta->Fill(genA1_eta);
				Real_Gen_Eta->Fill(genA0_eta);
				Real_Gen_Phi->Fill(genA1_phi);
				Real_Gen_Phi->Fill(genA0_phi);
				Real_Gen_pT->Fill(sqrt(genA1_px*genA1_px+genA1_py*genA1_py)); 
				Real_Gen_pT->Fill(sqrt(genA0_px*genA0_px+genA0_py*genA0_py)); 
				Real_Gen_MassCompatability->Fill(genA0_m, genA1_m);
				Real_Gen_pT_vs_Lxy->Fill(genA0_Lxy,sqrt(genA0_px*genA0_px+genA0_py*genA0_py));
				Real_Gen_pT_vs_Lxy->Fill(genA1_Lxy,sqrt(genA1_px*genA1_px+genA1_py*genA1_py));

				Real_dimuon1_Gen_Lxy->Fill(genA0_Lxy);
				Real_dimuon2_Gen_Lxy->Fill(genA1_Lxy);
				Real_dimuon1_Gen_Lz->Fill(genA0_Lz);
				Real_dimuon2_Gen_Lz->Fill(genA1_Lz);
				Real_dimuon2_Gen_Eta->Fill(genA1_eta);
				Real_dimuon1_Gen_Eta->Fill(genA0_eta);
				Real_dimuon2_Gen_Phi->Fill(genA1_phi);
				Real_dimuon1_Gen_Phi->Fill(genA0_phi);
				Real_dimuon2_Gen_pT->Fill(sqrt(genA1_px*genA1_px+genA1_py*genA1_py));
				Real_dimuon1_Gen_pT->Fill(sqrt(genA0_px*genA0_px+genA0_py*genA0_py));

				if(diMuonC_FittedVtx_Lxy > -800) Real_Reco_Lxy->Fill(diMuonC_FittedVtx_Lxy); 
				if(diMuonF_FittedVtx_Lxy > -800) Real_Reco_Lxy->Fill(diMuonF_FittedVtx_Lxy); 
				if(diMuonC_FittedVtx_eta > -800) Real_Reco_Eta->Fill(diMuonC_FittedVtx_eta);
				if(diMuonF_FittedVtx_eta > -800) Real_Reco_Eta->Fill(diMuonF_FittedVtx_eta);
				if(diMuonC_FittedVtx_phi > -800) Real_Reco_Phi->Fill(diMuonC_FittedVtx_phi);
				if(diMuonF_FittedVtx_phi > -800) Real_Reco_Phi->Fill(diMuonF_FittedVtx_phi);
				if(diMuonC_FittedVtx_px > -800 && diMuonC_FittedVtx_py > -800) Real_Reco_pT->Fill(sqrt(diMuonC_FittedVtx_px*diMuonC_FittedVtx_px+diMuonC_FittedVtx_py*diMuonC_FittedVtx_py));
				if(diMuonF_FittedVtx_px > -800 && diMuonF_FittedVtx_py > -800) Real_Reco_pT->Fill(sqrt(diMuonF_FittedVtx_px*diMuonF_FittedVtx_px+diMuonF_FittedVtx_py*diMuonF_FittedVtx_py));
				if(diMuonC_FittedVtx_m > -800) Real_Reco_MassCompatability->Fill(diMuonC_FittedVtx_m,diMuonF_FittedVtx_m); 
				if(diMuonF_FittedVtx_px > -800 && diMuonF_FittedVtx_py > -800 && diMuonF_FittedVtx_Lxy > -800) Real_Reco_pT_vs_Lxy->Fill(diMuonF_FittedVtx_Lxy, sqrt(diMuonF_FittedVtx_px*diMuonF_FittedVtx_px+diMuonF_FittedVtx_py*diMuonF_FittedVtx_py));	
				if(diMuonC_FittedVtx_px > -800 && diMuonC_FittedVtx_py > -800 && diMuonC_FittedVtx_Lxy > -800) Real_Reco_pT_vs_Lxy->Fill(diMuonC_FittedVtx_Lxy, sqrt(diMuonC_FittedVtx_px*diMuonC_FittedVtx_px+diMuonC_FittedVtx_py*diMuonC_FittedVtx_py));	
				if(diMuonC_FittedVtx_eta > -800 && diMuonC_FittedVtx_phi > -800){
					Real_Reco_Eta_vs_Phi->Fill(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_phi);
					Real_dimuon1_Reco_Eta_vs_Phi->Fill(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_phi);
				}
				if(diMuonF_FittedVtx_eta > -800 && diMuonF_FittedVtx_phi > -800){
					Real_Reco_Eta_vs_Phi->Fill(diMuonF_FittedVtx_eta, diMuonF_FittedVtx_phi);
					Real_dimuon2_Reco_Eta_vs_Phi->Fill(diMuonF_FittedVtx_eta, diMuonF_FittedVtx_phi);
				}

				if(diMuonC_FittedVtx_eta > -800 && diMuonC_FittedVtx_Lxy > -800){
					Real_Reco_Eta_vs_Lxy->Fill(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_Lxy);
					Real_dimuon1_Reco_Eta_vs_Lxy->Fill(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_Lxy);
				}
				if(diMuonF_FittedVtx_eta > -800 && diMuonF_FittedVtx_Lxy > -800){
					Real_Reco_Eta_vs_Lxy->Fill(diMuonF_FittedVtx_eta, diMuonF_FittedVtx_Lxy);
					Real_dimuon2_Reco_Eta_vs_Lxy->Fill(diMuonF_FittedVtx_eta, diMuonF_FittedVtx_Lxy);
				}

				if(diMuonC_FittedVtx_Lxy > -800) Real_dimuon1_Reco_Lxy->Fill(diMuonC_FittedVtx_Lxy);
				if(diMuonF_FittedVtx_Lxy > -800) Real_dimuon2_Reco_Lxy->Fill(diMuonF_FittedVtx_Lxy);
				if(diMuonC_FittedVtx_eta > -800) Real_dimuon1_Reco_Eta->Fill(diMuonC_FittedVtx_eta);
				if(diMuonF_FittedVtx_eta > -800) Real_dimuon2_Reco_Eta->Fill(diMuonF_FittedVtx_eta);
				if(diMuonC_FittedVtx_phi > -800) Real_dimuon1_Reco_Phi->Fill(diMuonC_FittedVtx_phi);
				if(diMuonF_FittedVtx_phi > -800) Real_dimuon2_Reco_Phi->Fill(diMuonF_FittedVtx_phi);
				if(diMuonC_FittedVtx_px > -800 && diMuonC_FittedVtx_py > -800) Real_dimuon1_Reco_pT->Fill(sqrt(diMuonC_FittedVtx_px*diMuonC_FittedVtx_px+diMuonC_FittedVtx_py*diMuonC_FittedVtx_py));
				if(diMuonF_FittedVtx_px > -800 && diMuonF_FittedVtx_py > -800) Real_dimuon2_Reco_pT->Fill(sqrt(diMuonF_FittedVtx_px*diMuonF_FittedVtx_px+diMuonF_FittedVtx_py*diMuonF_FittedVtx_py));
				if(diMuonC_FittedVtx_m > -800) Real_dimuon1_Reco_MassCompatability->Fill(diMuonC_FittedVtx_m,diMuonF_FittedVtx_m);

			}
			if(triggerFlag_std > 0 && triggerFlag_lxy == 0){
				fakeFlag++;

				Fake_Gen_Lxy->Fill(genA0_Lxy);
				Fake_Gen_Lxy->Fill(genA1_Lxy);
				Fake_Gen_Lz->Fill(genA0_Lz);
				Fake_Gen_Lz->Fill(genA1_Lz);
				Fake_Gen_Eta->Fill(genA1_eta);
				Fake_Gen_Eta->Fill(genA0_eta);
				Fake_Gen_Phi->Fill(genA1_phi);
				Fake_Gen_Phi->Fill(genA0_phi);
				Fake_Gen_pT->Fill(sqrt(genA1_px*genA1_px+genA1_py*genA1_py));
				Fake_Gen_pT->Fill(sqrt(genA0_px*genA0_px+genA0_py*genA0_py));
				Fake_Gen_MassCompatability->Fill(genA0_m, genA1_m);
				Fake_Gen_pT_vs_Lxy->Fill(genA0_Lxy,sqrt(genA0_px*genA0_px+genA0_py*genA0_py));
				Fake_Gen_pT_vs_Lxy->Fill(genA1_Lxy,sqrt(genA1_px*genA1_px+genA1_py*genA1_py));

				if(diMuonC_FittedVtx_Lxy > -800) Fake_Reco_Lxy->Fill(diMuonC_FittedVtx_Lxy);
				if(diMuonF_FittedVtx_Lxy > -800) Fake_Reco_Lxy->Fill(diMuonF_FittedVtx_Lxy);
				if(diMuonC_FittedVtx_eta > -800) Fake_Reco_Eta->Fill(diMuonC_FittedVtx_eta);
				if(diMuonF_FittedVtx_eta > -800) Fake_Reco_Eta->Fill(diMuonF_FittedVtx_eta);
				if(diMuonC_FittedVtx_phi > -800) Fake_Reco_Phi->Fill(diMuonC_FittedVtx_phi);
				if(diMuonF_FittedVtx_phi > -800) Fake_Reco_Phi->Fill(diMuonF_FittedVtx_phi);
				if(diMuonC_FittedVtx_px > -800 && diMuonC_FittedVtx_py > -800) Fake_Reco_pT->Fill(sqrt(diMuonC_FittedVtx_px*diMuonC_FittedVtx_px+diMuonC_FittedVtx_py*diMuonC_FittedVtx_py));
				if(diMuonF_FittedVtx_px > -800 && diMuonF_FittedVtx_py > -800) Fake_Reco_pT->Fill(sqrt(diMuonF_FittedVtx_px*diMuonF_FittedVtx_px+diMuonF_FittedVtx_py*diMuonF_FittedVtx_py));
				if(diMuonC_FittedVtx_m > -800) Fake_Reco_MassCompatability->Fill(diMuonC_FittedVtx_m,diMuonF_FittedVtx_m);
				if(diMuonF_FittedVtx_px > -800 && diMuonF_FittedVtx_py > -800 && diMuonF_FittedVtx_Lxy > -800) Fake_Reco_pT_vs_Lxy->Fill(diMuonF_FittedVtx_Lxy, sqrt(diMuonF_FittedVtx_px*diMuonF_FittedVtx_px+diMuonF_FittedVtx_py*diMuonF_FittedVtx_py));
				if(diMuonC_FittedVtx_px > -800 && diMuonC_FittedVtx_py > -800 && diMuonC_FittedVtx_Lxy > -800) Fake_Reco_pT_vs_Lxy->Fill(diMuonC_FittedVtx_Lxy, sqrt(diMuonC_FittedVtx_px*diMuonC_FittedVtx_px+diMuonC_FittedVtx_py*diMuonC_FittedVtx_py));

				if(fabs(genA0_Lxy)<4.4 && fabs(genA0_Lz)<34.5){
					//Dimuon0 is fake
					fakeDimuon1++;

					Fake_dimuon1_Gen_Lxy->Fill(genA0_Lxy);
					Fake_dimuon1_Gen_Lz->Fill(genA0_Lz);
					Fake_dimuon1_Gen_Eta->Fill(genA0_eta);
					Fake_dimuon1_Gen_Phi->Fill(genA0_phi);
					Fake_dimuon1_Gen_pT->Fill(sqrt(genA0_px*genA0_px+genA0_py*genA0_py));
					Fake_dimuon1_Gen_pT_vs_Lxy->Fill(genA0_Lxy,sqrt(genA0_px*genA0_px+genA0_py*genA0_py));

					if(diMuonC_FittedVtx_Lxy > -800) Fake_dimuon1_Reco_Lxy->Fill(diMuonC_FittedVtx_Lxy);
					if(diMuonC_FittedVtx_eta > -800) Fake_dimuon1_Reco_Eta->Fill(diMuonC_FittedVtx_eta);
					if(diMuonC_FittedVtx_phi > -800) Fake_dimuon1_Reco_Phi->Fill(diMuonC_FittedVtx_phi);
					if(diMuonC_FittedVtx_px > -800 && diMuonC_FittedVtx_py > -800) Fake_dimuon1_Reco_pT->Fill(sqrt(diMuonC_FittedVtx_px*diMuonC_FittedVtx_px+diMuonC_FittedVtx_py*diMuonC_FittedVtx_py));
					if(diMuonC_FittedVtx_m > -800) Fake_dimuon1_Reco_MassCompatability->Fill(diMuonC_FittedVtx_m,diMuonF_FittedVtx_m);
					if(diMuonC_FittedVtx_px > -800 && diMuonC_FittedVtx_py > -800 && diMuonC_FittedVtx_Lxy > -800) Fake_dimuon1_Reco_pT_vs_Lxy->Fill(diMuonC_FittedVtx_Lxy, sqrt(diMuonC_FittedVtx_px*diMuonC_FittedVtx_px+diMuonC_FittedVtx_py*diMuonC_FittedVtx_py));

					if(diMuonC_FittedVtx_eta > -800 && diMuonC_FittedVtx_phi > -800){
						Fake_Reco_Eta_vs_Phi->Fill(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_phi);
						Fake_dimuon1_Reco_Eta_vs_Phi->Fill(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_phi);
					}

					if(diMuonC_FittedVtx_eta > -800 && diMuonC_FittedVtx_Lxy > -800){
						Fake_Reco_Eta_vs_Lxy->Fill(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_Lxy);
						Fake_dimuon1_Reco_Eta_vs_Lxy->Fill(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_Lxy);
					}

				}
				if(fabs(genA1_Lxy)<4.4 && fabs(genA1_Lz)<34.5){
					//Dimuon1 is fake
					fakeDimuon2++;

					Fake_dimuon2_Gen_Lxy->Fill(genA1_Lxy);
					Fake_dimuon2_Gen_Lz->Fill(genA1_Lz);
					Fake_dimuon2_Gen_Eta->Fill(genA1_eta);
					Fake_dimuon2_Gen_Phi->Fill(genA1_phi);
					Fake_dimuon2_Gen_pT->Fill(sqrt(genA1_px*genA1_px+genA1_py*genA1_py));
					Fake_dimuon2_Gen_MassCompatability->Fill(genA0_m, genA1_m);
					Fake_dimuon2_Gen_pT_vs_Lxy->Fill(genA1_Lxy,sqrt(genA1_px*genA1_px+genA1_py*genA1_py));

					if(diMuonF_FittedVtx_Lxy > -800) Fake_dimuon2_Reco_Lxy->Fill(diMuonF_FittedVtx_Lxy);
					if(diMuonF_FittedVtx_eta > -800) Fake_dimuon2_Reco_Eta->Fill(diMuonF_FittedVtx_eta);
					if(diMuonF_FittedVtx_phi > -800) Fake_dimuon2_Reco_Phi->Fill(diMuonF_FittedVtx_phi);
					if(diMuonF_FittedVtx_px > -800 && diMuonF_FittedVtx_py > -800) Fake_dimuon2_Reco_pT->Fill(sqrt(diMuonF_FittedVtx_px*diMuonF_FittedVtx_px+diMuonF_FittedVtx_py*diMuonF_FittedVtx_py));
					if(diMuonF_FittedVtx_px > -800 && diMuonF_FittedVtx_py > -800 && diMuonF_FittedVtx_Lxy > -800) Fake_dimuon2_Reco_pT_vs_Lxy->Fill(diMuonF_FittedVtx_Lxy, sqrt(diMuonF_FittedVtx_px*diMuonF_FittedVtx_px+diMuonF_FittedVtx_py*diMuonF_FittedVtx_py));

					if(diMuonF_FittedVtx_eta > -800 && diMuonF_FittedVtx_phi > -800){
						Fake_Reco_Eta_vs_Phi->Fill(diMuonF_FittedVtx_eta, diMuonF_FittedVtx_phi);
						Fake_dimuon2_Reco_Eta_vs_Phi->Fill(diMuonF_FittedVtx_eta, diMuonF_FittedVtx_phi);
					}

					if(diMuonF_FittedVtx_eta > -800 && diMuonF_FittedVtx_Lxy > -800){ 
						Fake_Reco_Eta_vs_Lxy->Fill(diMuonF_FittedVtx_eta, diMuonF_FittedVtx_Lxy); 
						Fake_dimuon2_Reco_Eta_vs_Lxy->Fill(diMuonF_FittedVtx_eta, diMuonF_FittedVtx_Lxy); 
					} 

				}

			}

		} // closing for loop
		myfile->Close();
	} // closing while loop
	std::cout<<" Sample: " << fileName << endl;
	std::cout<<" Events          "<<ev_all<<std::endl;
	std::cout<<" ================ GEN MUONS ========================================= "<<std::endl;
	std::cout<<" 1GenMu17                       "<<c1genm<<"   reff "<<c1genm/(ev_all*1.0)<<std::endl;
	std::cout<<" 2GenMu8                        "<<c2genm<<"   reff  "<<c2genm/(c1genm*1.0)<<std::endl;
	std::cout<<" 3GenMu8                        "<<c3genm<<"   reff  "<<c3genm/(c2genm*1.0)<<std::endl;
	std::cout<<" 4GenMu8                        "<<c4genm<<"   reff  "<<c4genm/(c3genm*1.0)<<std::endl;
	std::cout<<" 4GenMu8 Lxy/Lz                 "<<ev_4gmlxylzcut<<"   reff   "<<ev_4gmlxylzcut/c4genm<<std::endl;
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
	std::cout<<" ratio reco/gen                 "<<ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)<<" +/-  "<<sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut))<<std::endl;

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

	//delete chEl;
	//delete fileElements;
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


	TH2F *dummy3 = new TH2F("","",400,-0.2,20.2,100,0.0,1.0);


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
	c->SaveAs("e_rec_alpha_gen_vs_cT.pdf","recreate");
	//c->SaveAs("e_rec_alpha_gen_vs_cT.C","recreate");
}

void FakeInvestigation()
{
	
	//These cT's should be in order.
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
*/	
	/*
	   efficiency_hitrecovery("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f//");
	   efficiency_hitrecovery("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	   efficiency_hitrecovery("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	   efficiency_hitrecovery("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	   efficiency_hitrecovery("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	   efficiency_hitrecovery("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_100_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	   efficiency_hitrecovery("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	   efficiency_hitrecovery("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_300_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	   efficiency_hitrecovery("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	   efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_1000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	   efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_2000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	   */
	/*
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


	   efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	   efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	   efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	   efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	   efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	   efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_100_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	   efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	   efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_300_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	   efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
*/
/*
	   efficiency_hitrecovery("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	   efficiency_hitrecovery("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	   efficiency_hitrecovery("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	   efficiency_hitrecovery("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	   efficiency_hitrecovery("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	   efficiency_hitrecovery("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_100_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	   efficiency_hitrecovery("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	   efficiency_hitrecovery("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_300_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	   efficiency_hitrecovery("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");



	
	   efficiency_hitrecovery("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
	   efficiency_hitrecovery("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
	   efficiency_hitrecovery("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
	   efficiency_hitrecovery("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
	   efficiency_hitrecovery("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
	   efficiency_hitrecovery("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");

*/
/*
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_0275_cT_000_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_000_Evt_80k_PATANA_v4/151117_123308/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_0275_cT_005_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_005_Evt_80k_PATANA_v4/151117_151528/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_0275_cT_010_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_010_Evt_80k_PATANA_v4/151117_151628/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_0275_cT_020_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_020_Evt_80k_PATANA_v4/151117_151724/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_0275_cT_050_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_050_Evt_80k_PATANA_v4/151117_151824/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_0275_cT_100_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_100_Evt_80k_PATANA_v4/151117_151935/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_0275_cT_200_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_200_Evt_80k_PATANA_v4/151117_152115/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_0275_cT_300_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_300_Evt_80k_PATANA_v4/151117_152230/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_0275_cT_500_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_500_Evt_80k_PATANA_v4/151117_152335/asdf/"); 

	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_0300_cT_000_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_000_Evt_80k_PATANA_v4/151117_152519/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_0300_cT_005_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_005_Evt_80k_PATANA_v4/151117_152556/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_0300_cT_010_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_010_Evt_80k_PATANA_v4/151117_152703/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_0300_cT_020_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_020_Evt_80k_PATANA_v4/151117_152813/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_0300_cT_050_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_050_Evt_80k_PATANA_v4/151117_153006/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_0300_cT_100_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_100_Evt_80k_PATANA_v4/151117_153036/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_0300_cT_200_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_200_Evt_80k_PATANA_v4/151117_153141/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_0300_cT_300_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_300_Evt_80k_PATANA_v4/151117_153244/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_0300_cT_500_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_500_Evt_80k_PATANA_v4/151117_153321/asdf/"); 

	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_0400_cT_000_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_000_Evt_80k_PATANA_v4/151117_153421/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_0400_cT_005_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_005_Evt_80k_PATANA_v4/151117_153513/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_0400_cT_010_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_010_Evt_80k_PATANA_v4/151117_153558/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_0400_cT_020_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_020_Evt_80k_PATANA_v4/151117_153657/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_0400_cT_050_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_050_Evt_80k_PATANA_v4/151117_153812/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_0400_cT_100_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_100_Evt_80k_PATANA_v4/151117_153904/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_0400_cT_200_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_200_Evt_80k_PATANA_v4/151117_153951/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_0400_cT_300_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_300_Evt_80k_PATANA_v4/151117_154045/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_0400_cT_500_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_500_Evt_80k_PATANA_v4/151117_154251/asdf/"); 

	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_0700_cT_000_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_000_Evt_80k_PATANA_v4/151117_154344/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_0700_cT_005_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_005_Evt_80k_PATANA_v4/151117_154442/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_0700_cT_010_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_010_Evt_80k_PATANA_v4/151117_154535/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_0700_cT_020_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_020_Evt_80k_PATANA_v4/151117_154632/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_0700_cT_050_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_050_Evt_80k_PATANA_v4/151117_154716/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_0700_cT_100_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_100_Evt_80k_PATANA_v4/151117_154749/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_0700_cT_200_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_200_Evt_80k_PATANA_v4/151117_154834/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_0700_cT_300_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_300_Evt_80k_PATANA_v4/151117_154929/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_0700_cT_500_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_500_Evt_80k_PATANA_v4/151117_155023/asdf/"); 

	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_1000_cT_000_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_000_Evt_80k_PATANA_v4/151117_155128/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_1000_cT_005_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_005_Evt_80k_PATANA_v4/151117_155253/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_1000_cT_010_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_010_Evt_80k_PATANA_v4/151117_155348/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_1000_cT_020_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_020_Evt_80k_PATANA_v4/151117_155445/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_1000_cT_050_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_050_Evt_80k_PATANA_v4/151117_155539/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_1000_cT_100_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_100_Evt_80k_PATANA_v4/151117_155629/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_1000_cT_200_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_200_Evt_80k_PATANA_v4/151117_155726/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_1000_cT_300_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_300_Evt_80k_PATANA_v4/151117_155825/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_1000_cT_500_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_500_Evt_80k_PATANA_v4/151117_155914/asdf/"); 

	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_1500_cT_000_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_000_Evt_80k_PATANA_v4/151117_160012/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_1500_cT_005_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_005_Evt_80k_PATANA_v4/151117_160122/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_1500_cT_020_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_020_Evt_80k_PATANA_v4/151117_160315/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_1500_cT_100_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_100_Evt_80k_PATANA_v4/151117_160426/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_1500_cT_200_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_200_Evt_80k_PATANA_v4/151117_160522/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_1500_cT_300_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_300_Evt_80k_PATANA_v4/151117_160613/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlinDarkSUSY_mH_125_mGammaD_1500_cT_500_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_500_Evt_80k_PATANA_v4/151117_160729/asdf/");

*/

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


	makePlot();
	BAM->Write();

}     
