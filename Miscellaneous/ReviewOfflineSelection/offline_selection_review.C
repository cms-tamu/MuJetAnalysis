#include <algorithm>   
#include <iostream>
#include <algorithm> 
#include <stdlib.h>
#include "TMath.h"
#include <math.h>

using namespace std;

///----Global Variables ----//

vector<double> mGammaD_all_Fitted_dz;
vector<double> mGammaD_0250_Fitted_dz;
vector<double> mGammaD_0275_Fitted_dz;
vector<double> mGammaD_0300_Fitted_dz;
vector<double> mGammaD_2000_Fitted_dz;
vector<double> mGammaD_8500_Fitted_dz;

vector<double> mGammaD_all_Consistent_dz;
vector<double> mGammaD_0250_Consistent_dz;
vector<double> mGammaD_0275_Consistent_dz;
vector<double> mGammaD_0300_Consistent_dz;
vector<double> mGammaD_2000_Consistent_dz;
vector<double> mGammaD_8500_Consistent_dz;

vector<double> mGammaD_all_Fitted_iso;
vector<double> mGammaD_0250_Fitted_iso;
vector<double> mGammaD_0275_Fitted_iso;
vector<double> mGammaD_0300_Fitted_iso;
vector<double> mGammaD_2000_Fitted_iso;
vector<double> mGammaD_8500_Fitted_iso;

vector<double> mGammaD_all_Consistent_iso;
vector<double> mGammaD_0250_Consistent_iso;
vector<double> mGammaD_0275_Consistent_iso;
vector<double> mGammaD_0300_Consistent_iso;
vector<double> mGammaD_2000_Consistent_iso;
vector<double> mGammaD_8500_Consistent_iso;

vector < vector<double> > mGammaD_all_MassCompatability;
vector < vector<double> > mGammaD_0250_MassCompatability;
vector < vector<double> > mGammaD_0275_MassCompatability;
vector < vector<double> > mGammaD_0300_MassCompatability;
vector < vector<double> > mGammaD_2000_MassCompatability;
vector < vector<double> > mGammaD_8500_MassCompatability;

vector<double> mGammaD_0400_Fitted_dz;
vector<double> mGammaD_0700_Fitted_dz;
vector<double> mGammaD_1000_Fitted_dz;
vector<double> mGammaD_1500_Fitted_dz;

vector<double> mGammaD_0400_Consistent_dz;
vector<double> mGammaD_0700_Consistent_dz;
vector<double> mGammaD_1000_Consistent_dz;
vector<double> mGammaD_1500_Consistent_dz;

vector<double> mGammaD_0400_Fitted_iso;
vector<double> mGammaD_0700_Fitted_iso;
vector<double> mGammaD_1000_Fitted_iso;
vector<double> mGammaD_1500_Fitted_iso;

vector<double> mGammaD_0400_Consistent_iso;
vector<double> mGammaD_0700_Consistent_iso;
vector<double> mGammaD_1000_Consistent_iso;
vector<double> mGammaD_1500_Consistent_iso;

vector < vector<double> > mGammaD_0400_MassCompatability;
vector < vector<double> > mGammaD_0700_MassCompatability;
vector < vector<double> > mGammaD_1000_MassCompatability;
vector < vector<double> > mGammaD_1500_MassCompatability;


vector<double> bbar_Fitted_dz;
vector<double> bbar_Fitted_iso;

///---- Supplimental Methods  ----//

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
				if (verbose) std::cout << "fname added" << std::endl;
			}
		}
	}
}

///---- Main Method  ----//

void offline_vs_signal(TString fileName, int SigOrBack){
	bool verbose(true);
	//cout << SigOrBack << endl;
	TString dirname(fileName);
	TChain* chain = new TChain("dummy");

	TString ext("out_ana_");
	TString init_string = "";
	TSubString mass_string = (init_string(0,0));	
	TSubString cT_string = (init_string(0,0));
	//Get the sample mass
	if(SigOrBack == 1){
		TString str = fileName;
		TString str2 = "DarkSUSY_mH_125_mGammaD_";
		Ssiz_t first = str.Index(str2);
		Ssiz_t last = str.Index("_cT_");
		mass_string = (str(first+str2.Length(),4));
		//TSubString mass_string = (str(first+str2.Length(),4));
		///Get the sample cT
		TString str3 = "_cT_";
		TSubString cT_string = (str(last+str3.Length(),4));
	}
	// add files to the chain
	addfiles(chain, dirname, ext);
	if (verbose) std::cout << "Done adding files" << std::endl;
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

	Float_t selMu0_phi;
	Float_t selMu1_phi;
	Float_t selMu2_phi;
	Float_t selMu3_phi;

	Float_t selMu0_eta;
	Float_t selMu1_eta;
	Float_t selMu2_eta;
	Float_t selMu3_eta;

	Float_t genA0_eta;
	Float_t genA0_phi;
	Float_t genA1_eta;
	Float_t genA1_phi;

	Int_t diMuonC_m1_FittedVtx_hitpix;
	Int_t diMuonC_m2_FittedVtx_hitpix;
	Int_t diMuonF_m1_FittedVtx_hitpix;
	Int_t diMuonF_m2_FittedVtx_hitpix;

	Float_t massC;
	Float_t massF;

	Float_t diMuonC_Mass;
	Float_t diMuonF_Mass;

	Float_t diMuonF_FittedVtx_m;
	Float_t diMuonC_FittedVtx_m;

	Float_t bbar_orphan_mass;
	Float_t bbar_dimuon_mass;
	Float_t bbar_orphan_isoTk;
	Float_t bbar_dimuon_isoTk;
	Float_t bbar_orphan_z;
	Float_t bbar_dimuon_z;


	Float_t diMuonC_IsoTk_FittedVtx;
	Float_t diMuonF_IsoTk_FittedVtx;
	Float_t diMuonC_IsoTk_ConsistentVtx;
	Float_t diMuonF_IsoTk_ConsistentVtx;
	Float_t diMuonC_FittedVtx_dz;
	Float_t diMuonF_FittedVtx_dz;
	Float_t diMuonC_ConsistentVtx_dz;
	Float_t diMuonF_ConsistentVtx_dz;


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
		if (verbose) std::cout << "cutFlowAnalyzer loaded" << std::endl;
		TTree *t;
		if(SigOrBack == 1 || SigOrBack == 0) t = (TTree*)myfile->Get("cutFlowAnalyzer/Events");
		//TTree *t = (TTree*)myfile->Get("cutFlowAnalyzer/Events");
		TTree *b;
		if(SigOrBack == 0 ) {
			if (verbose) std::cout << "Getting cutFlowAnalyzer/Events_orphan" << std::endl;
			b = (TTree*)myfile->Get("cutFlowAnalyzer/Events_orphan");
			if (verbose) std::cout << "Successfully retrieved cutFlowAnalyzer/Events_orphan" << std::endl;
		}
		// b = (TTree*)myfile->Get("cutFlowAnalyzer/Events_orphan");
		if (!t) {
			if (verbose) std::cout << "Tree cutFlowAnalyzer/Events does not exist" << std::endl;
			continue;
		}

		if (!b) {
			if (verbose) std::cout << "Tree cutFlowAnalyzer/Events_orphan does not exist" << std::endl;
			continue;
		}


		if (verbose && SigOrBack == 1) cout<<"  Events  "<<t->GetEntries()<<endl;
		if (verbose && SigOrBack == 0) cout<<"  Events  "<<b->GetEntries()<<endl;

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

		t->SetBranchAddress("selMu0_phi",&selMu0_phi);
		t->SetBranchAddress("selMu1_phi",&selMu1_phi);
		t->SetBranchAddress("selMu2_phi",&selMu2_phi);
		t->SetBranchAddress("selMu3_phi",&selMu3_phi);

		t->SetBranchAddress("selMu0_eta",&selMu0_eta);
		t->SetBranchAddress("selMu1_eta",&selMu1_eta);
		t->SetBranchAddress("selMu2_eta",&selMu2_eta);
		t->SetBranchAddress("selMu3_eta",&selMu3_eta);


		t->SetBranchAddress("genA1_phi",&genA1_phi);
		t->SetBranchAddress("genA1_eta",&genA1_eta);

		t->SetBranchAddress("genA0_phi",&genA0_phi);
		t->SetBranchAddress("genA0_eta",&genA0_eta);

		t->SetBranchAddress("diMuonC_m1_FittedVtx_hitpix", &diMuonC_m1_FittedVtx_hitpix);
		t->SetBranchAddress("diMuonC_m2_FittedVtx_hitpix", &diMuonC_m2_FittedVtx_hitpix);
		t->SetBranchAddress("diMuonF_m1_FittedVtx_hitpix", &diMuonF_m1_FittedVtx_hitpix);
		t->SetBranchAddress("diMuonF_m2_FittedVtx_hitpix", &diMuonF_m2_FittedVtx_hitpix);

		t->SetBranchAddress("diMuonC_IsoTk_FittedVtx", &diMuonC_IsoTk_FittedVtx);
		t->SetBranchAddress("diMuonF_IsoTk_FittedVtx", &diMuonF_IsoTk_FittedVtx);
		t->SetBranchAddress("diMuonC_IsoTk_ConsistentVtx", &diMuonC_IsoTk_ConsistentVtx);
		t->SetBranchAddress("diMuonF_IsoTk_ConsistentVtx", &diMuonF_IsoTk_ConsistentVtx);
		t->SetBranchAddress("diMuonC_FittedVtx_dz", &diMuonC_FittedVtx_dz);
		t->SetBranchAddress("diMuonF_FittedVtx_dz", &diMuonF_FittedVtx_dz);
		t->SetBranchAddress("diMuonC_ConsistentVtx_dz", &diMuonC_ConsistentVtx_dz);
		t->SetBranchAddress("diMuonF_ConsistentVtx_dz", &diMuonF_ConsistentVtx_dz);

		if(SigOrBack == 1){
			//	t->SetBranchAddress("massC", &massC);
			//	t->SetBranchAddress("massF", &massF);
			//t->SetBranchAddress("diMuonC_Mass", &diMuonC_Mass);
			//t->SetBranchAddress("diMuonF_Mass", &diMuonF_Mass);
			t->SetBranchAddress("diMuonC_FittedVtx_m", &diMuonC_FittedVtx_m);
			t->SetBranchAddress("diMuonF_FittedVtx_m", &diMuonF_FittedVtx_m);
		}

		Int_t nentries_t;
		Int_t nentries_b;

		if(SigOrBack == 0){
			cout << "Load orphan branch variables" << endl;
			b->SetBranchAddress("orph_mass", 		&bbar_orphan_mass);
			b->SetBranchAddress("orph_dimu_mass", 		&bbar_dimuon_mass);

			b->SetBranchAddress("orph_isoTk",		&bbar_orphan_isoTk);
			b->SetBranchAddress("orph_dimu_isoTk",		&bbar_dimuon_isoTk);

			b->SetBranchAddress("orph_z",          		&bbar_orphan_z);
			b->SetBranchAddress("orph_dimu_z",        	&bbar_dimuon_z);
		}
		if(SigOrBack == 1) nentries_t = t->GetEntries();
		if(SigOrBack == 0) nentries_b = b->GetEntries();

		if(SigOrBack == 1){
			for(int k=0;k<nentries_t;k++){
				t->GetEntry(k);

				//cout << "mass_string: " << mass_string << endl;
				if(diMuonF_ConsistentVtx_dz > -1000 && diMuonC_ConsistentVtx_dz > -1000){
					double consistent_dz = diMuonC_ConsistentVtx_dz - diMuonF_ConsistentVtx_dz;
					mGammaD_all_Consistent_dz.push_back(consistent_dz);
					if(mass_string == "0250") mGammaD_0250_Consistent_dz.push_back(consistent_dz);
					if(mass_string == "0275") mGammaD_0275_Consistent_dz.push_back(consistent_dz); 
					if(mass_string == "0300") mGammaD_0300_Consistent_dz.push_back(consistent_dz);
					if(mass_string == "2000") mGammaD_2000_Consistent_dz.push_back(consistent_dz);
					if(mass_string == "8500") mGammaD_8500_Consistent_dz.push_back(consistent_dz);
					if(mass_string == "0400") mGammaD_0400_Consistent_dz.push_back(consistent_dz);
					if(mass_string == "0700") mGammaD_0700_Consistent_dz.push_back(consistent_dz);
					if(mass_string == "1000") mGammaD_1000_Consistent_dz.push_back(consistent_dz);
					if(mass_string == "1500") mGammaD_1500_Consistent_dz.push_back(consistent_dz);
				}
				if(diMuonF_FittedVtx_dz > -1000 && diMuonC_FittedVtx_dz > -1000){
					double fitted_dz = diMuonC_FittedVtx_dz - diMuonF_FittedVtx_dz;
					mGammaD_all_Fitted_dz.push_back(fitted_dz);
					if(mass_string == "0250") mGammaD_0250_Fitted_dz.push_back(fitted_dz); 
					if(mass_string == "0275") mGammaD_0275_Fitted_dz.push_back(fitted_dz); 
					if(mass_string == "0300") mGammaD_0300_Fitted_dz.push_back(fitted_dz); 
					if(mass_string == "2000") mGammaD_2000_Fitted_dz.push_back(fitted_dz); 
					if(mass_string == "8500") mGammaD_8500_Fitted_dz.push_back(fitted_dz); 
					if(mass_string == "0400") mGammaD_0400_Fitted_dz.push_back(fitted_dz);
					if(mass_string == "0700") mGammaD_0700_Fitted_dz.push_back(fitted_dz);
					if(mass_string == "1000") mGammaD_1000_Fitted_dz.push_back(fitted_dz);
					if(mass_string == "1500") mGammaD_1500_Fitted_dz.push_back(fitted_dz);
				}


				if(diMuonF_IsoTk_FittedVtx != -1){
					mGammaD_all_Fitted_iso.push_back(diMuonF_IsoTk_FittedVtx);
					if(mass_string == "0250") mGammaD_0250_Fitted_iso.push_back(diMuonF_IsoTk_FittedVtx);
					if(mass_string == "0275") mGammaD_0275_Fitted_iso.push_back(diMuonF_IsoTk_FittedVtx);
					if(mass_string == "0300") mGammaD_0300_Fitted_iso.push_back(diMuonF_IsoTk_FittedVtx);
					if(mass_string == "2000") mGammaD_2000_Fitted_iso.push_back(diMuonF_IsoTk_FittedVtx);
					if(mass_string == "8500") mGammaD_8500_Fitted_iso.push_back(diMuonF_IsoTk_FittedVtx);
					if(mass_string == "0400") mGammaD_0400_Fitted_iso.push_back(diMuonF_IsoTk_FittedVtx);
					if(mass_string == "0700") mGammaD_0700_Fitted_iso.push_back(diMuonF_IsoTk_FittedVtx);
					if(mass_string == "1000") mGammaD_1000_Fitted_iso.push_back(diMuonF_IsoTk_FittedVtx);
					if(mass_string == "1500") mGammaD_1500_Fitted_iso.push_back(diMuonF_IsoTk_FittedVtx);
				}
				if(diMuonC_IsoTk_FittedVtx != -1){
					mGammaD_all_Fitted_iso.push_back(diMuonC_IsoTk_FittedVtx);
					if(mass_string == "0250") mGammaD_0250_Fitted_iso.push_back(diMuonC_IsoTk_FittedVtx);
					if(mass_string == "0275") mGammaD_0275_Fitted_iso.push_back(diMuonC_IsoTk_FittedVtx);
					if(mass_string == "0300") mGammaD_0300_Fitted_iso.push_back(diMuonC_IsoTk_FittedVtx);
					if(mass_string == "2000") mGammaD_2000_Fitted_iso.push_back(diMuonC_IsoTk_FittedVtx);
					if(mass_string == "8500") mGammaD_8500_Fitted_iso.push_back(diMuonC_IsoTk_FittedVtx);
					if(mass_string == "0400") mGammaD_0400_Fitted_iso.push_back(diMuonC_IsoTk_FittedVtx);
					if(mass_string == "0700") mGammaD_0700_Fitted_iso.push_back(diMuonC_IsoTk_FittedVtx);
					if(mass_string == "1000") mGammaD_1000_Fitted_iso.push_back(diMuonC_IsoTk_FittedVtx);
					if(mass_string == "1500") mGammaD_1500_Fitted_iso.push_back(diMuonC_IsoTk_FittedVtx);
				}
				if(diMuonF_IsoTk_ConsistentVtx != -1){
					mGammaD_all_Consistent_iso.push_back(diMuonF_IsoTk_ConsistentVtx);
					if(mass_string == "0250") mGammaD_0250_Consistent_iso.push_back(diMuonF_IsoTk_ConsistentVtx);
					if(mass_string == "0275") mGammaD_0275_Consistent_iso.push_back(diMuonF_IsoTk_ConsistentVtx);
					if(mass_string == "0300") mGammaD_0300_Consistent_iso.push_back(diMuonF_IsoTk_ConsistentVtx);
					if(mass_string == "2000") mGammaD_2000_Consistent_iso.push_back(diMuonF_IsoTk_ConsistentVtx);
					if(mass_string == "8500") mGammaD_8500_Consistent_iso.push_back(diMuonF_IsoTk_ConsistentVtx);
					if(mass_string == "0400") mGammaD_0400_Consistent_iso.push_back(diMuonF_IsoTk_ConsistentVtx);
					if(mass_string == "0700") mGammaD_0700_Consistent_iso.push_back(diMuonF_IsoTk_ConsistentVtx);
					if(mass_string == "1000") mGammaD_1000_Consistent_iso.push_back(diMuonF_IsoTk_ConsistentVtx);
					if(mass_string == "1500") mGammaD_1500_Consistent_iso.push_back(diMuonF_IsoTk_ConsistentVtx);
				}
				if(diMuonC_IsoTk_ConsistentVtx != -1){
					mGammaD_all_Consistent_iso.push_back(diMuonC_IsoTk_ConsistentVtx);
					if(mass_string == "0250") mGammaD_0250_Consistent_iso.push_back(diMuonC_IsoTk_ConsistentVtx);
					if(mass_string == "0275") mGammaD_0275_Consistent_iso.push_back(diMuonC_IsoTk_ConsistentVtx);
					if(mass_string == "0300") mGammaD_0300_Consistent_iso.push_back(diMuonC_IsoTk_ConsistentVtx);
					if(mass_string == "2000") mGammaD_2000_Consistent_iso.push_back(diMuonC_IsoTk_ConsistentVtx);
					if(mass_string == "8500") mGammaD_8500_Consistent_iso.push_back(diMuonC_IsoTk_ConsistentVtx);
					if(mass_string == "0400") mGammaD_0400_Consistent_iso.push_back(diMuonC_IsoTk_ConsistentVtx);
					if(mass_string == "0700") mGammaD_0700_Consistent_iso.push_back(diMuonC_IsoTk_ConsistentVtx);
					if(mass_string == "1000") mGammaD_1000_Consistent_iso.push_back(diMuonC_IsoTk_ConsistentVtx);
					if(mass_string == "1500") mGammaD_1500_Consistent_iso.push_back(diMuonC_IsoTk_ConsistentVtx);
				}
				//Mass compatibility |massC-massF| < (0.13 + 0.065(massC+massF)/2)
				if(diMuonC_FittedVtx_m > -800 && diMuonF_FittedVtx_m > -800){
					if(mass_string == "0250"){
						vector<double> temp_vector;
						temp_vector.push_back(diMuonC_FittedVtx_m);
						temp_vector.push_back(diMuonF_FittedVtx_m);
						mGammaD_0250_MassCompatability.push_back(temp_vector);

						//cout << "diMuonC_FittedVtx_m, diMuonF_FittedVtx_m (vector)  : " << temp_vector[0] << ", " << temp_vector[1] << endl;
						//cout << "diMuonC_FittedVtx_m, diMuonF_FittedVtx_m (variable): " << diMuonC_FittedVtx_m << ", " << diMuonF_FittedVtx_m << endl;
						temp_vector.clear();
					}
					if(mass_string == "0275"){
						vector<double> temp_vector;
						temp_vector.push_back(diMuonC_FittedVtx_m);
						temp_vector.push_back(diMuonF_FittedVtx_m);
						mGammaD_0275_MassCompatability.push_back(temp_vector);
						temp_vector.clear();
					}

					if(mass_string == "0300"){
						vector<double> temp_vector;
						temp_vector.push_back(diMuonC_FittedVtx_m);
						temp_vector.push_back(diMuonF_FittedVtx_m);
						mGammaD_0300_MassCompatability.push_back(temp_vector);
						temp_vector.clear();
					}
					if(mass_string == "2000"){
						vector<double> temp_vector;
						temp_vector.push_back(diMuonC_FittedVtx_m);
						temp_vector.push_back(diMuonF_FittedVtx_m);
						mGammaD_2000_MassCompatability.push_back(temp_vector);
						temp_vector.clear();
					}

					if(mass_string == "8500"){
						vector<double> temp_vector;
						temp_vector.push_back(diMuonC_FittedVtx_m);
						temp_vector.push_back(diMuonF_FittedVtx_m);
						if(diMuonC_FittedVtx_m < 2 && diMuonF_FittedVtx_m < 2){
							cout << "low mass peak" << endl;
						}

						mGammaD_8500_MassCompatability.push_back(temp_vector);
						temp_vector.clear();
					}
					if(mass_string == "0400"){
						vector<double> temp_vector;
						temp_vector.push_back(diMuonC_FittedVtx_m);
						temp_vector.push_back(diMuonF_FittedVtx_m);
						mGammaD_0400_MassCompatability.push_back(temp_vector);
						temp_vector.clear();
					}

					if(mass_string == "0700"){
						vector<double> temp_vector;
						temp_vector.push_back(diMuonC_FittedVtx_m);
						temp_vector.push_back(diMuonF_FittedVtx_m);
						mGammaD_0700_MassCompatability.push_back(temp_vector);
						temp_vector.clear();
					}
					if(mass_string == "1000"){
						vector<double> temp_vector;
						temp_vector.push_back(diMuonC_FittedVtx_m);
						temp_vector.push_back(diMuonF_FittedVtx_m);
						mGammaD_1000_MassCompatability.push_back(temp_vector);
						temp_vector.clear();
					}

					if(mass_string == "1500"){
						vector<double> temp_vector;
						temp_vector.push_back(diMuonC_FittedVtx_m);
						temp_vector.push_back(diMuonF_FittedVtx_m);
						if(diMuonC_FittedVtx_m < 2 && diMuonF_FittedVtx_m < 2){
							cout << "low mass peak" << endl;
						}

						mGammaD_1500_MassCompatability.push_back(temp_vector);
						temp_vector.clear();
					}

					vector<double> temp_vector;
					temp_vector.push_back(diMuonC_FittedVtx_m);
					temp_vector.push_back(diMuonF_FittedVtx_m);
					mGammaD_all_MassCompatability.push_back(temp_vector);
					temp_vector.clear();
				}
			} // closing for loop
		}
		if(SigOrBack == 0){
			//cout << "Entering background loop" << endl;
			for(int k=0;k<nentries_b;k++){ 
				b->GetEntry(k);
				//cout << "Getting background entry" << endl;
				//cout << "bbar variables (dimuon z, orphan z)    : " << bbar_dimuon_z << ", " << bbar_orphan_z << endl;
				//cout << "bbar variables (dimuon iso, orphan iso): " << bbar_dimuon_isoTk << ", " << bbar_orphan_isoTk << endl;
				if(bbar_orphan_z > -999 && bbar_dimuon_z > -999) bbar_Fitted_dz.push_back(bbar_dimuon_z - bbar_orphan_z);
				if(bbar_dimuon_isoTk > -1) bbar_Fitted_iso.push_back(bbar_dimuon_isoTk);

			} //Closing background for loop
		}
		myfile->Close();
	} // closing while loop
}

void makePlots(){
	TFile *BAM = new TFile("Review_Offline_Selection.root","RECREATE");

	TH2D * mGammaD_0250_MassCompatability_plot = new TH2D("mGammaD_0250_MassCompatability_plot", "mGammaD_0250_MassCompatability_plot", 1000, 0, 10, 1000, 0, 10);
	TH2D * mGammaD_0275_MassCompatability_plot = new TH2D("mGammaD_0275_MassCompatability_plot", "mGammaD_0275_MassCompatability_plot", 1000, 0, 10, 1000, 0, 10);
	TH2D * mGammaD_0300_MassCompatability_plot = new TH2D("mGammaD_0300_MassCompatability_plot", "mGammaD_0300_MassCompatability_plot", 1000, 0, 10, 1000, 0, 10);
	TH2D * mGammaD_2000_MassCompatability_plot = new TH2D("mGammaD_2000_MassCompatability_plot", "mGammaD_2000_MassCompatability_plot", 1000, 0, 10, 1000, 0, 10);
	TH2D * mGammaD_8500_MassCompatability_plot = new TH2D("mGammaD_8500_MassCompatability_plot", "mGammaD_8500_MassCompatability_plot", 1000, 0, 10, 1000, 0, 10);
	TH2D * mGammaD_0400_MassCompatability_plot = new TH2D("mGammaD_0400_MassCompatability_plot", "mGammaD_0400_MassCompatability_plot", 1000, 0, 10, 1000, 0, 10);
	TH2D * mGammaD_0700_MassCompatability_plot = new TH2D("mGammaD_0700_MassCompatability_plot", "mGammaD_0700_MassCompatability_plot", 1000, 0, 10, 1000, 0, 10);
	TH2D * mGammaD_1000_MassCompatability_plot = new TH2D("mGammaD_1000_MassCompatability_plot", "mGammaD_1000_MassCompatability_plot", 1000, 0, 10, 1000, 0, 10);
	TH2D * mGammaD_1500_MassCompatability_plot = new TH2D("mGammaD_1500_MassCompatability_plot", "mGammaD_1500_MassCompatability_plot", 1000, 0, 10, 1000, 0, 10);
	TH2D * mGammaD_all_MassCompatability_plot = new TH2D("mGammaD_all_MassCompatability_plot", "mGammaD_all_MassCompatability_plot", 1000, 0, 10, 1000, 0, 10);
	TF1 *func1 = new TF1("func1", "(1/387)*(413*x+52)",0,10);
	TF1 *func2 = new TF1("func2", "(1/413)*(387*x-52)",0,10);

	TCanvas *m = new TCanvas("m", "m", 700, 500);
	m->SetLogz();
	mGammaD_0250_MassCompatability_plot->GetXaxis()->SetTitle("#mu#mu_{1}");
	mGammaD_0250_MassCompatability_plot->GetYaxis()->SetTitle("#mu#mu_{2}");
	mGammaD_0250_MassCompatability_plot->SetTitle("Mass Compatability for #gamma_{D} = 0.250 GeV");
	gStyle->SetOptStat(0);
	for(int i = 0; i < mGammaD_0250_MassCompatability.size(); i ++){
		//cout << "mGammaD_0250_MassCompatability[i][0], mGammaD_0250_MassCompatability[i][1]: " << mGammaD_0250_MassCompatability[i][0] <<  ", " << mGammaD_0250_MassCompatability[i][1] << endl;
		mGammaD_0250_MassCompatability_plot->Fill(mGammaD_0250_MassCompatability[i][0], mGammaD_0250_MassCompatability[i][1]);
	}
	mGammaD_0250_MassCompatability_plot->Draw("colz");
	func1->Draw("same");
	func2->Draw("same");
	m->SaveAs("mGammaD_0250_MassCompatability.pdf","recreate");

	TCanvas *m1 = new TCanvas("m1", "m1", 700, 500);
	m1->SetLogz();
	mGammaD_0275_MassCompatability_plot->GetXaxis()->SetTitle("#mu#mu_{1}");
	mGammaD_0275_MassCompatability_plot->GetYaxis()->SetTitle("#mu#mu_{2}");
	mGammaD_0275_MassCompatability_plot->SetTitle("Mass Compatability for #gamma_{D} = 0.275 GeV");
	gStyle->SetOptStat(0);
	for(int i = 0; i < mGammaD_0275_MassCompatability.size(); i ++){
		mGammaD_0275_MassCompatability_plot->Fill(mGammaD_0275_MassCompatability[i][0], mGammaD_0275_MassCompatability[i][1]);
	}
	mGammaD_0275_MassCompatability_plot->Draw("colz");
	func1->Draw("same");
	func2->Draw("same");
	m1->SaveAs("mGammaD_0275_MassCompatability.pdf","recreate");

	TCanvas *m2 = new TCanvas("m2", "m2", 700, 500);
	m2->SetLogz();
	mGammaD_0300_MassCompatability_plot->GetXaxis()->SetTitle("#mu#mu_{1}");
	mGammaD_0300_MassCompatability_plot->GetYaxis()->SetTitle("#mu#mu_{2}");
	mGammaD_0300_MassCompatability_plot->SetTitle("Mass Compatability for #gamma_{D} = 0.300 GeV");
	gStyle->SetOptStat(0);
	for(int i = 0; i < mGammaD_0300_MassCompatability.size(); i ++){
		mGammaD_0300_MassCompatability_plot->Fill(mGammaD_0300_MassCompatability[i][0], mGammaD_0300_MassCompatability[i][1]);
	}
	mGammaD_0300_MassCompatability_plot->Draw("colz");
	func1->Draw("same");
	func2->Draw("same");
	m2->SaveAs("mGammaD_0300_MassCompatability.pdf","recreate");

	TCanvas *m3 = new TCanvas("m3", "m3", 700, 500);
	m3->SetLogz();
	mGammaD_2000_MassCompatability_plot->GetXaxis()->SetTitle("#mu#mu_{1}");
	mGammaD_2000_MassCompatability_plot->GetYaxis()->SetTitle("#mu#mu_{2}");
	mGammaD_2000_MassCompatability_plot->SetTitle("Mass Compatability for #gamma_{D} = 2.0 GeV");
	gStyle->SetOptStat(0);
	for(int i = 0; i < mGammaD_2000_MassCompatability.size(); i ++){
		mGammaD_2000_MassCompatability_plot->Fill(mGammaD_2000_MassCompatability[i][0], mGammaD_2000_MassCompatability[i][1]);
	}
	mGammaD_2000_MassCompatability_plot->Draw("colz");
	func1->Draw("same");
	func2->Draw("same");
	m3->SaveAs("mGammaD_2000_MassCompatability.pdf","recreate");

	TCanvas *m4 = new TCanvas("m4", "m4", 700, 500);
	m4->SetLogz();
	mGammaD_8500_MassCompatability_plot->GetXaxis()->SetTitle("#mu#mu_{1}");
	mGammaD_8500_MassCompatability_plot->GetYaxis()->SetTitle("#mu#mu_{2}");
	mGammaD_8500_MassCompatability_plot->SetTitle("Mass Compatability for #gamma_{D} = 8.5 GeV");
	gStyle->SetOptStat(0);
	for(int i = 0; i < mGammaD_8500_MassCompatability.size(); i ++){
		mGammaD_8500_MassCompatability_plot->Fill(mGammaD_8500_MassCompatability[i][0], mGammaD_8500_MassCompatability[i][1]);
	}
	mGammaD_8500_MassCompatability_plot->Draw("colz");
	func1->Draw("same");
	func2->Draw("same");
	m4->SaveAs("mGammaD_8500_MassCompatability.pdf","recreate");

	TCanvas *ma = new TCanvas("ma", "ma", 700, 500);
	ma->SetLogz();
	mGammaD_0400_MassCompatability_plot->GetXaxis()->SetTitle("#mu#mu_{1}");
	mGammaD_0400_MassCompatability_plot->GetYaxis()->SetTitle("#mu#mu_{2}");
	mGammaD_0400_MassCompatability_plot->SetTitle("Mass Compatability for #gamma_{D} = 0.275 GeV");
	gStyle->SetOptStat(0);
	for(int i = 0; i < mGammaD_0400_MassCompatability.size(); i ++){
		mGammaD_0400_MassCompatability_plot->Fill(mGammaD_0400_MassCompatability[i][0], mGammaD_0400_MassCompatability[i][1]);
	}
	mGammaD_0400_MassCompatability_plot->Draw("colz");
	func1->Draw("same");
	func2->Draw("same");
	ma->SaveAs("mGammaD_0400_MassCompatability.pdf","recreate");

	TCanvas *mb = new TCanvas("mb", "mb", 700, 500);
	mb->SetLogz();
	mGammaD_0700_MassCompatability_plot->GetXaxis()->SetTitle("#mu#mu_{1}");
	mGammaD_0700_MassCompatability_plot->GetYaxis()->SetTitle("#mu#mu_{2}");
	mGammaD_0700_MassCompatability_plot->SetTitle("Mass Compatability for #gamma_{D} = 0.300 GeV");
	gStyle->SetOptStat(0);
	for(int i = 0; i < mGammaD_0700_MassCompatability.size(); i ++){
		mGammaD_0700_MassCompatability_plot->Fill(mGammaD_0700_MassCompatability[i][0], mGammaD_0700_MassCompatability[i][1]);
	}
	mGammaD_0700_MassCompatability_plot->Draw("colz");
	func1->Draw("same");
	func2->Draw("same");
	mb->SaveAs("mGammaD_0700_MassCompatability.pdf","recreate");

	TCanvas *mc = new TCanvas("mc", "mc", 700, 500);
	mc->SetLogz();
	mGammaD_1000_MassCompatability_plot->GetXaxis()->SetTitle("#mu#mu_{1}");
	mGammaD_1000_MassCompatability_plot->GetYaxis()->SetTitle("#mu#mu_{2}");
	mGammaD_1000_MassCompatability_plot->SetTitle("Mass Compatability for #gamma_{D} = 2.0 GeV");
	gStyle->SetOptStat(0);
	for(int i = 0; i < mGammaD_1000_MassCompatability.size(); i ++){
		mGammaD_1000_MassCompatability_plot->Fill(mGammaD_1000_MassCompatability[i][0], mGammaD_1000_MassCompatability[i][1]);
	}
	mGammaD_1000_MassCompatability_plot->Draw("colz");
	func1->Draw("same");
	func2->Draw("same");
	mc->SaveAs("mGammaD_1000_MassCompatability.pdf","recreate");

	TCanvas *md = new TCanvas("md", "md", 700, 500);
	md->SetLogz();
	mGammaD_1500_MassCompatability_plot->GetXaxis()->SetTitle("#mu#mu_{1}");
	mGammaD_1500_MassCompatability_plot->GetYaxis()->SetTitle("#mu#mu_{2}");
	mGammaD_1500_MassCompatability_plot->SetTitle("Mass Compatability for #gamma_{D} = 8.5 GeV");
	gStyle->SetOptStat(0);
	for(int i = 0; i < mGammaD_1500_MassCompatability.size(); i ++){
		mGammaD_1500_MassCompatability_plot->Fill(mGammaD_1500_MassCompatability[i][0], mGammaD_1500_MassCompatability[i][1]);
	}
	mGammaD_1500_MassCompatability_plot->Draw("colz");
	func1->Draw("same");
	func2->Draw("same");
	md->SaveAs("mGammaD_1500_MassCompatability.pdf","recreate");




	TCanvas *m5 = new TCanvas("m5", "m5", 700, 500);
	m5->SetLogz();
	mGammaD_all_MassCompatability_plot->GetXaxis()->SetTitle("#mu#mu_{1}");
	mGammaD_all_MassCompatability_plot->GetYaxis()->SetTitle("#mu#mu_{2}");
	mGammaD_all_MassCompatability_plot->SetTitle("Mass Compatability for #gamma_{D}");
	gStyle->SetOptStat(0);
	for(int i = 0; i < mGammaD_all_MassCompatability.size(); i ++){
		mGammaD_all_MassCompatability_plot->Fill(mGammaD_all_MassCompatability[i][0], mGammaD_all_MassCompatability[i][1]);
	}
	mGammaD_all_MassCompatability_plot->Draw("colz");
	func1->Draw("same");
	func2->Draw("same");
	m5->SaveAs("mGammaD_all_MassCompatability.pdf","recreate");

	TH1D *mGammaD_0250_Fitted_dz_plot = new TH1D("mGammaD_0250_Fitted_dz_plot", "mGammaD_0250_Fitted_dz_plot", 150, -0.15, 0.15);
	TH1D *mGammaD_0275_Fitted_dz_plot = new TH1D("mGammaD_0275_Fitted_dz_plot", "mGammaD_0275_Fitted_dz_plot", 150, -.15, .15);
	TH1D *mGammaD_0300_Fitted_dz_plot = new TH1D("mGammaD_0300_Fitted_dz_plot", "mGammaD_0300_Fitted_dz_plot", 150, -.15, .15);
	TH1D *mGammaD_2000_Fitted_dz_plot = new TH1D("mGammaD_2000_Fitted_dz_plot", "mGammaD_2000_Fitted_dz_plot", 150, -.15, .15);
	TH1D *mGammaD_8500_Fitted_dz_plot = new TH1D("mGammaD_8500_Fitted_dz_plot", "mGammaD_8500_Fitted_dz_plot", 150, -0.15, 0.15);
	//TH1D *mGammaD_all_Fitted_dz_plot = new TH1D("mGammaD_all_Fitted_dz_plot", "mGammaD_all_Fitted_dz_plot", 150, -0.15, 0.15);
	TH1D *mGammaD_all_Fitted_dz_plot = new TH1D("mGammaD_all_Fitted_dz_plot", "mGammaD_all_Fitted_dz_plot", 150, -0.15, 0.15);
	TH1D *bbar_Fitted_dz_plot = new TH1D("bbar_Fitted_dz_plot", "bbar_Fitted_dz_plot", 150, -0.15, 0.15);
	TH1D *mGammaD_0400_Fitted_dz_plot = new TH1D("mGammaD_0400_Fitted_dz_plot", "mGammaD_0400_Fitted_dz_plot", 150, -.15, .15);
	TH1D *mGammaD_0700_Fitted_dz_plot = new TH1D("mGammaD_0700_Fitted_dz_plot", "mGammaD_0700_Fitted_dz_plot", 150, -.15, .15);
	TH1D *mGammaD_1000_Fitted_dz_plot = new TH1D("mGammaD_1000_Fitted_dz_plot", "mGammaD_1000_Fitted_dz_plot", 150, -.15, .15);
	TH1D *mGammaD_1500_Fitted_dz_plot = new TH1D("mGammaD_1500_Fitted_dz_plot", "mGammaD_1500_Fitted_dz_plot", 150, -0.15, 0.15);

	TCanvas *c0 = new TCanvas("c0", "c0", 700, 500);
	bbar_Fitted_dz_plot->GetXaxis()->SetTitle("#Delta z [cm]");
	bbar_Fitted_dz_plot->GetYaxis()->SetTitle("Fraction of events/0.002 cm");
	bbar_Fitted_dz_plot->SetTitle("Distance Between Vertices for bbar");
	gStyle->SetOptStat("Merou");
	for(int i =0; i < bbar_Fitted_dz.size(); i++){
		bbar_Fitted_dz_plot->Fill(bbar_Fitted_dz[i]);
	}
	bbar_Fitted_dz_plot->SetLineColor(kBlue);
	bbar_Fitted_dz_plot->DrawNormalized();
	c0->SaveAs("bbar_dz_plot.pdf", "recreate");


	TCanvas *c = new TCanvas("c","c",700,500);
	mGammaD_0250_Fitted_dz_plot->GetXaxis()->SetTitle("#Delta z [cm]");
	mGammaD_0250_Fitted_dz_plot->GetYaxis()->SetTitle("Fraction of events/0.002 cm");
	mGammaD_0250_Fitted_dz_plot->SetTitle("Distance Between Vertices for #gamma_{D} = 0.250 GeV");
	gStyle->SetOptStat("Merou");
	for(int i =0; i < mGammaD_0250_Fitted_dz.size(); i++){
		mGammaD_0250_Fitted_dz_plot->Fill(mGammaD_0250_Fitted_dz[i]);
	}
	mGammaD_0250_Fitted_dz_plot->SetFillColor(kRed);
	mGammaD_0250_Fitted_dz_plot->DrawNormalized();
	bbar_Fitted_dz_plot->DrawNormalized("same");
	c->SaveAs("mGammaD_0250_Fitted_dz_plot.pdf", "recreate");


	TCanvas *c1 = new TCanvas("c1","c1",700,500);
	mGammaD_0275_Fitted_dz_plot->GetXaxis()->SetTitle("#Delta z [cm]");
	mGammaD_0275_Fitted_dz_plot->GetYaxis()->SetTitle("Fraction of events");
	mGammaD_0275_Fitted_dz_plot->SetTitle("Distance Between Vertices for #gamma_{D} = 0.275 GeV");
	gStyle->SetOptStat("Merou");
	for(int i =0; i < mGammaD_0275_Fitted_dz.size(); i++){
		mGammaD_0275_Fitted_dz_plot->Fill(mGammaD_0275_Fitted_dz[i]);
	}
	mGammaD_0275_Fitted_dz_plot->SetFillColor(kRed);
	mGammaD_0275_Fitted_dz_plot->DrawNormalized();
	c1->SaveAs("mGammaD_0275_Fitted_dz_plot.pdf", "recreate");


	TCanvas *c2 = new TCanvas("c2","c2",700,500);
	mGammaD_0300_Fitted_dz_plot->GetXaxis()->SetTitle("#Delta z [cm]");
	mGammaD_0300_Fitted_dz_plot->GetYaxis()->SetTitle("Fraction of events");
	mGammaD_0300_Fitted_dz_plot->SetTitle("Distance Between Vertices for #gamma_{D} = 0.300 GeV");
	gStyle->SetOptStat("Merou");
	for(int i =0; i < mGammaD_0300_Fitted_dz.size(); i++){
		mGammaD_0300_Fitted_dz_plot->Fill(mGammaD_0300_Fitted_dz[i]);
	}
	mGammaD_0300_Fitted_dz_plot->SetFillColor(kRed);
	mGammaD_0300_Fitted_dz_plot->DrawNormalized();
	c2->SaveAs("mGammaD_0300_Fitted_dz_plot.pdf", "recreate");



	TCanvas *c3 = new TCanvas("c3","c3",700,500);
	mGammaD_2000_Fitted_dz_plot->GetXaxis()->SetTitle("#Delta z [cm]");
	mGammaD_2000_Fitted_dz_plot->GetYaxis()->SetTitle("Fraction of events");
	mGammaD_2000_Fitted_dz_plot->SetTitle("Distance Between Vertices for #gamma_{D} = 2.0 GeV");
	gStyle->SetOptStat("Merou");
	for(int i =0; i < mGammaD_2000_Fitted_dz.size(); i++){
		mGammaD_2000_Fitted_dz_plot->Fill(mGammaD_2000_Fitted_dz[i]);
	}
	mGammaD_2000_Fitted_dz_plot->SetFillColor(kRed);
	mGammaD_2000_Fitted_dz_plot->DrawNormalized();
	c3->SaveAs("mGammaD_2000_Fitted_dz_plot.pdf", "recreate");


	TCanvas *c4 = new TCanvas("c4","c4",700,500);
	mGammaD_8500_Fitted_dz_plot->GetXaxis()->SetTitle("#Delta z [cm]");
	mGammaD_8500_Fitted_dz_plot->GetYaxis()->SetTitle("Fraction of events/0.002 cm");
	mGammaD_8500_Fitted_dz_plot->SetTitle("Distance Between Vertices for #gamma_{D} = 8.5 GeV");
	gStyle->SetOptStat("Merou");
	for(int i =0; i < mGammaD_8500_Fitted_dz.size(); i++){
		mGammaD_8500_Fitted_dz_plot->Fill(mGammaD_8500_Fitted_dz[i]);
	}
	mGammaD_8500_Fitted_dz_plot->SetFillColor(kRed);
	mGammaD_8500_Fitted_dz_plot->DrawNormalized();
	bbar_Fitted_dz_plot->DrawNormalized("same");
	c4->SaveAs("mGammaD_8500_Fitted_dz_plot.pdf", "recreate");
	TCanvas *ca = new TCanvas("ca","ca",700,500);
	mGammaD_0400_Fitted_dz_plot->GetXaxis()->SetTitle("#Delta z [cm]");
	mGammaD_0400_Fitted_dz_plot->GetYaxis()->SetTitle("Fraction of events");
	mGammaD_0400_Fitted_dz_plot->SetTitle("Distance Between Vertices for #gamma_{D} = 0.275 GeV");
	gStyle->SetOptStat("Merou");
	for(int i =0; i < mGammaD_0400_Fitted_dz.size(); i++){
		mGammaD_0400_Fitted_dz_plot->Fill(mGammaD_0400_Fitted_dz[i]);
	}
	mGammaD_0400_Fitted_dz_plot->SetFillColor(kRed);
	mGammaD_0400_Fitted_dz_plot->DrawNormalized();
	ca->SaveAs("mGammaD_0400_Fitted_dz_plot.pdf", "recreate");


	TCanvas *cb = new TCanvas("cb","cb",700,500);
	mGammaD_0700_Fitted_dz_plot->GetXaxis()->SetTitle("#Delta z [cm]");
	mGammaD_0700_Fitted_dz_plot->GetYaxis()->SetTitle("Fraction of events");
	mGammaD_0700_Fitted_dz_plot->SetTitle("Distance Between Vertices for #gamma_{D} = 0.300 GeV");
	gStyle->SetOptStat("Merou");
	for(int i =0; i < mGammaD_0700_Fitted_dz.size(); i++){
		mGammaD_0700_Fitted_dz_plot->Fill(mGammaD_0700_Fitted_dz[i]);
	}
	mGammaD_0700_Fitted_dz_plot->SetFillColor(kRed);
	mGammaD_0700_Fitted_dz_plot->DrawNormalized();
	cb->SaveAs("mGammaD_0700_Fitted_dz_plot.pdf", "recreate");



	TCanvas *cc = new TCanvas("cc","cc",700,500);
	mGammaD_1000_Fitted_dz_plot->GetXaxis()->SetTitle("#Delta z [cm]");
	mGammaD_1000_Fitted_dz_plot->GetYaxis()->SetTitle("Fraction of events");
	mGammaD_1000_Fitted_dz_plot->SetTitle("Distance Between Vertices for #gamma_{D} = 2.0 GeV");
	gStyle->SetOptStat("Merou");
	for(int i =0; i < mGammaD_1000_Fitted_dz.size(); i++){
		mGammaD_1000_Fitted_dz_plot->Fill(mGammaD_1000_Fitted_dz[i]);
	}
	mGammaD_1000_Fitted_dz_plot->SetFillColor(kRed);
	mGammaD_1000_Fitted_dz_plot->DrawNormalized();
	cc->SaveAs("mGammaD_1000_Fitted_dz_plot.pdf", "recreate");

	TCanvas *cd = new TCanvas("cd","cd",700,500);
	mGammaD_1500_Fitted_dz_plot->GetXaxis()->SetTitle("#Delta z [cm]");
	mGammaD_1500_Fitted_dz_plot->GetYaxis()->SetTitle("Fraction of events/0.002 cm");
	mGammaD_1500_Fitted_dz_plot->SetTitle("Distance Between Vertices for #gamma_{D} = 8.5 GeV");
	gStyle->SetOptStat("Merou");
	for(int i =0; i < mGammaD_1500_Fitted_dz.size(); i++){
		mGammaD_1500_Fitted_dz_plot->Fill(mGammaD_1500_Fitted_dz[i]);
	}
	mGammaD_1500_Fitted_dz_plot->SetFillColor(kRed);
	mGammaD_1500_Fitted_dz_plot->DrawNormalized();
	bbar_Fitted_dz_plot->DrawNormalized("same");
	cd->SaveAs("mGammaD_1500_Fitted_dz_plot.pdf", "recreate");


	TCanvas *c5 = new TCanvas("c5","c5",700,500);
	mGammaD_all_Fitted_dz_plot->GetXaxis()->SetTitle("#Delta z [cm]");
	mGammaD_all_Fitted_dz_plot->GetYaxis()->SetTitle("Fraction of events/0.002 cm");
	mGammaD_all_Fitted_dz_plot->SetTitle("Distance Between Vertices for #gamma_{D}");
	gStyle->SetOptStat("Merou");
	for(int i =0; i < mGammaD_all_Fitted_dz.size(); i++){
		mGammaD_all_Fitted_dz_plot->Fill(mGammaD_all_Fitted_dz[i]);
	}
	mGammaD_all_Fitted_dz_plot->SetFillColor(kRed);
	mGammaD_all_Fitted_dz_plot->DrawNormalized();
	bbar_Fitted_dz_plot->DrawNormalized("same");
	c5->SaveAs("mGammaD_all_Fitted_dz_plot.pdf", "recreate");

	/*
	   TH1D *mGammaD_0250_Consistent_dz_plot = new TH1D("mGammaD_0250_Consistent_dz_plot", "mGammaD_0250_Consistent_dz_plot", 300, -1.5, 1.5);
	   TH1D *mGammaD_0275_Consistent_dz_plot = new TH1D("mGammaD_0275_Consistent_dz_plot", "mGammaD_0275_Consistent_dz_plot", 300, -1.5, 1.5);
	   TH1D *mGammaD_0300_Consistent_dz_plot = new TH1D("mGammaD_0300_Consistent_dz_plot", "mGammaD_0300_Consistent_dz_plot", 300, -1.5, 1.5);
	   TH1D *mGammaD_2000_Consistent_dz_plot = new TH1D("mGammaD_2000_Consistent_dz_plot", "mGammaD_2000_Consistent_dz_plot", 300, -1.5, 1.5);
	   TH1D *mGammaD_8500_Consistent_dz_plot = new TH1D("mGammaD_8500_Consistent_dz_plot", "mGammaD_8500_Consistent_dz_plot", 300, -1.5, 1.5);
	//TH1D *mGammaD_all_Consistent_dz_plot = new TH1D("mGammaD_all_Consistent_dz_plot", "mGammaD_all_Consistent_dz_plot", 300, -1.5, 1.5);
	TH1D *mGammaD_all_Consistent_dz_plot = new TH1D("mGammaD_all_Consistent_dz_plot", "mGammaD_all_Consistent_dz_plot", 500, -0.5, 0.5);

	TCanvas *c6 = new TCanvas("c6","c6",700,500);
	mGammaD_0250_Consistent_dz_plot->GetXaxis()->SetTitle("#Delta z [cm]");
	mGammaD_0250_Consistent_dz_plot->GetYaxis()->SetTitle("Fraction of events");
	mGammaD_0250_Consistent_dz_plot->SetTitle("Distance Between Vertices for #gamma_{D} = 0.250 GeV");
	gStyle->SetOptStat("Merou");
	for(int i =0; i < mGammaD_0250_Consistent_dz.size(); i++){
	mGammaD_0250_Consistent_dz_plot->Fill(mGammaD_0250_Consistent_dz[i]);
	}
	mGammaD_0250_Consistent_dz_plot->SetFillColor(kRed);
	mGammaD_0250_Consistent_dz_plot->DrawNormalized();
	c6->SaveAs("mGammaD_0250_Consistent_dz_plot.pdf", "recreate");


	TCanvas *c7 = new TCanvas("c7","c7",700,500);
	mGammaD_0275_Consistent_dz_plot->GetXaxis()->SetTitle("#Delta z [cm]");
	mGammaD_0275_Consistent_dz_plot->GetYaxis()->SetTitle("Fraction of events");
	mGammaD_0275_Consistent_dz_plot->SetTitle("Distance Between Vertices for #gamma_{D} = 0.275 GeV");
	gStyle->SetOptStat("Merou");
	for(int i =0; i < mGammaD_0275_Consistent_dz.size(); i++){
	mGammaD_0275_Consistent_dz_plot->Fill(mGammaD_0275_Consistent_dz[i]);
	}
	mGammaD_0275_Consistent_dz_plot->SetFillColor(kRed);
	mGammaD_0275_Consistent_dz_plot->DrawNormalized();
	c7->SaveAs("mGammaD_0275_Consistent_dz_plot.pdf", "recreate");


	TCanvas *c8 = new TCanvas("c8","c8",700,500);
	mGammaD_0300_Consistent_dz_plot->GetXaxis()->SetTitle("#Delta z [cm]");
	mGammaD_0300_Consistent_dz_plot->GetYaxis()->SetTitle("Fraction of events");
	mGammaD_0300_Consistent_dz_plot->SetTitle("Distance Between Vertices for #gamma_{D} = 0.300 GeV");
	gStyle->SetOptStat("Merou");
	for(int i =0; i < mGammaD_0300_Consistent_dz.size(); i++){
	mGammaD_0300_Consistent_dz_plot->Fill(mGammaD_0300_Consistent_dz[i]);
	}
	mGammaD_0300_Consistent_dz_plot->SetFillColor(kRed);
	mGammaD_0300_Consistent_dz_plot->DrawNormalized();
	c8->SaveAs("mGammaD_0300_Consistent_dz_plot.pdf", "recreate");



	TCanvas *c9 = new TCanvas("c9","c9",700,500);
	mGammaD_2000_Consistent_dz_plot->GetXaxis()->SetTitle("#Delta z [cm]");
	mGammaD_2000_Consistent_dz_plot->GetYaxis()->SetTitle("Fraction of events");
	mGammaD_2000_Consistent_dz_plot->SetTitle("Distance Between Vertices for #gamma_{D} = 2.0 GeV");
	gStyle->SetOptStat("Merou");
	for(int i =0; i < mGammaD_2000_Consistent_dz.size(); i++){
	mGammaD_2000_Consistent_dz_plot->Fill(mGammaD_2000_Consistent_dz[i]);
	}
	mGammaD_2000_Consistent_dz_plot->SetFillColor(kRed);
	mGammaD_2000_Consistent_dz_plot->DrawNormalized();
	c9->SaveAs("mGammaD_2000_Consistent_dz_plot.pdf", "recreate");


	TCanvas *c10 = new TCanvas("c10","c10",700,500);
	mGammaD_8500_Consistent_dz_plot->GetXaxis()->SetTitle("#Delta z [cm]");
	mGammaD_8500_Consistent_dz_plot->GetYaxis()->SetTitle("Fraction of events");
	mGammaD_8500_Consistent_dz_plot->SetTitle("Distance Between Vertices for #gamma_{D} = 8.5 GeV");
	gStyle->SetOptStat("Merou");
	for(int i =0; i < mGammaD_8500_Consistent_dz.size(); i++){
	mGammaD_8500_Consistent_dz_plot->Fill(mGammaD_8500_Consistent_dz[i]);
	}
	mGammaD_8500_Consistent_dz_plot->SetFillColor(kRed);
	mGammaD_8500_Consistent_dz_plot->DrawNormalized();
	c10->SaveAs("mGammaD_8500_Consistent_dz_plot.pdf", "recreate");


	TCanvas *c11 = new TCanvas("c11","c11",700,500);
	mGammaD_all_Consistent_dz_plot->GetXaxis()->SetTitle("#Delta z [cm]");
	mGammaD_all_Consistent_dz_plot->GetYaxis()->SetTitle("Fraction of events/0.002 cm");
	mGammaD_all_Consistent_dz_plot->SetTitle("Distance Between Vertices for #gamma_{D}");
	gStyle->SetOptStat("Merou");
	for(int i =0; i < mGammaD_all_Consistent_dz.size(); i++){
		mGammaD_all_Consistent_dz_plot->Fill(mGammaD_all_Consistent_dz[i]);
	}
	mGammaD_all_Consistent_dz_plot->SetFillColor(kRed);
	mGammaD_all_Consistent_dz_plot->DrawNormalized();
	c11->SaveAs("mGammaD_all_Consistent_dz_plot.pdf", "recreate");
	*/
		//Now plot isolation

		TH1D *mGammaD_0250_Fitted_Iso_plot = new TH1D("mGammaD_0250_Fitted_Iso_plot", "mGammaD_0250_Fitted_Iso_plot", 100, 0, 100);
	TH1D *mGammaD_0275_Fitted_Iso_plot = new TH1D("mGammaD_0275_Fitted_Iso_plot", "mGammaD_0275_Fitted_Iso_plot", 100, 0, 100);
	TH1D *mGammaD_0300_Fitted_Iso_plot = new TH1D("mGammaD_0300_Fitted_Iso_plot", "mGammaD_0300_Fitted_Iso_plot", 100, 0, 100);
	TH1D *mGammaD_2000_Fitted_Iso_plot = new TH1D("mGammaD_2000_Fitted_Iso_plot", "mGammaD_2000_Fitted_Iso_plot", 100, 0, 100);
	TH1D *mGammaD_8500_Fitted_Iso_plot = new TH1D("mGammaD_8500_Fitted_Iso_plot", "mGammaD_8500_Fitted_Iso_plot", 100, 0, 100);
	TH1D *mGammaD_all_Fitted_Iso_plot = new TH1D("mGammaD_all_Fitted_Iso_plot", "mGammaD_all_Fitted_Iso_plot", 100, 0, 100);

	TH1D *mGammaD_0250_Fitted_Iso_zoom_plot = new TH1D("mGammaD_0250_Fitted_Iso_zoom_plot", "mGammaD_0250_Fitted_Iso_zoom_plot", 100, 0, 10);
	TH1D *mGammaD_0275_Fitted_Iso_zoom_plot = new TH1D("mGammaD_0275_Fitted_Iso_zoom_plot", "mGammaD_0275_Fitted_Iso_zoom_plot", 100, 0, 10);
	TH1D *mGammaD_0300_Fitted_Iso_zoom_plot = new TH1D("mGammaD_0300_Fitted_Iso_zoom_plot", "mGammaD_0300_Fitted_Iso_zoom_plot", 100, 0, 10);
	TH1D *mGammaD_2000_Fitted_Iso_zoom_plot = new TH1D("mGammaD_2000_Fitted_Iso_zoom_plot", "mGammaD_2000_Fitted_Iso_zoom_plot", 100, 0, 10);
	TH1D *mGammaD_8500_Fitted_Iso_zoom_plot = new TH1D("mGammaD_8500_Fitted_Iso_zoom_plot", "mGammaD_8500_Fitted_Iso_zoom_plot", 100, 0, 10);
	TH1D *mGammaD_all_Fitted_Iso_zoom_plot = new TH1D("mGammaD_all_Fitted_Iso_zoom_plot", "mGammaD_all_Fitted_Iso_zoom_plot", 100, 0, 10);

	TH1D *mGammaD_0400_Fitted_Iso_plot = new TH1D("mGammaD_0400_Fitted_Iso_plot", "mGammaD_0400_Fitted_Iso_plot", 100, 0, 100);
	TH1D *mGammaD_0700_Fitted_Iso_plot = new TH1D("mGammaD_0700_Fitted_Iso_plot", "mGammaD_0700_Fitted_Iso_plot", 100, 0, 100);
	TH1D *mGammaD_1000_Fitted_Iso_plot = new TH1D("mGammaD_1000_Fitted_Iso_plot", "mGammaD_1000_Fitted_Iso_plot", 100, 0, 100);
	TH1D *mGammaD_1500_Fitted_Iso_plot = new TH1D("mGammaD_1500_Fitted_Iso_plot", "mGammaD_1500_Fitted_Iso_plot", 100, 0, 100);

	TH1D *mGammaD_0400_Fitted_Iso_zoom_plot = new TH1D("mGammaD_0400_Fitted_Iso_zoom_plot", "mGammaD_0400_Fitted_Iso_zoom_plot", 100, 0, 10);
	TH1D *mGammaD_0700_Fitted_Iso_zoom_plot = new TH1D("mGammaD_0700_Fitted_Iso_zoom_plot", "mGammaD_0700_Fitted_Iso_zoom_plot", 100, 0, 10);
	TH1D *mGammaD_1000_Fitted_Iso_zoom_plot = new TH1D("mGammaD_1000_Fitted_Iso_zoom_plot", "mGammaD_1000_Fitted_Iso_zoom_plot", 100, 0, 10);
	TH1D *mGammaD_1500_Fitted_Iso_zoom_plot = new TH1D("mGammaD_1500_Fitted_Iso_zoom_plot", "mGammaD_1500_Fitted_Iso_zoom_plot", 100, 0, 10);

	TH1D *bbar_Iso_plot = new TH1D("bbar_Iso_plot", "bbar_Iso_plot", 100, 0, 100);
	TH1D *bbar_Iso_zoom_plot = new TH1D("bbar_Iso_zoom_plot", "bbar_Iso_zoom_plot", 100, 0, 10);


	TCanvas *c120 = new TCanvas("c120","c120",700,500);
	bbar_Iso_plot->GetXaxis()->SetTitle("Iso_{#mu#mu} [GeV/c]");
	bbar_Iso_plot->GetYaxis()->SetTitle("Fraction of events/1.0 GeV/c");
	bbar_Iso_plot->SetTitle("Dimuon Tracker Isolation for bbar");
	gStyle->SetOptStat("Mero");
	for(int i =0; i < bbar_Fitted_iso.size(); i++){
		bbar_Iso_plot->Fill(bbar_Fitted_iso[i]);
		bbar_Iso_zoom_plot->Fill(bbar_Fitted_iso[i]);
	}
	bbar_Iso_plot->SetLineColor(kBlue);
	bbar_Iso_plot->DrawNormalized();
	c120->SaveAs("bbar_Iso_plot.pdf", "recreate");
	c120->Clear();
	bbar_Iso_zoom_plot->GetXaxis()->SetTitle("Iso_{#mu#mu} [GeV/c]");
	bbar_Iso_zoom_plot->GetYaxis()->SetTitle("Fraction of events/0.1 GeV/c");
	bbar_Iso_zoom_plot->SetTitle("Dimuon Tracker Isolation for bbar");
	bbar_Iso_zoom_plot->SetLineColor(kBlue);
	bbar_Iso_zoom_plot->DrawNormalized();
	c120->SaveAs("bbar_Iso_zoom_plot.pdf", "recreate");

	TCanvas *c12 = new TCanvas("c12","c12",700,500);
	mGammaD_0250_Fitted_Iso_plot->GetXaxis()->SetTitle("Iso_{#mu#mu} [GeV/c]");
	mGammaD_0250_Fitted_Iso_plot->GetYaxis()->SetTitle("Fraction of events/1.0 GeV/c");
	mGammaD_0250_Fitted_Iso_plot->SetTitle("Dimuon Tracker Isolation for #gamma_{D} = 0.250 GeV");
	gStyle->SetOptStat("Mero");
	for(int i =0; i < mGammaD_0250_Fitted_iso.size(); i++){
		mGammaD_0250_Fitted_Iso_plot->Fill(mGammaD_0250_Fitted_iso[i]);
		mGammaD_0250_Fitted_Iso_zoom_plot->Fill(mGammaD_0250_Fitted_iso[i]);
	}
	mGammaD_0250_Fitted_Iso_plot->SetFillColor(kRed);
	mGammaD_0250_Fitted_Iso_plot->DrawNormalized();
	bbar_Iso_plot->DrawNormalized("same");
	c12->SaveAs("mGammaD_0250_Fitted_Iso_plot.pdf", "recreate");
	c12->Clear();
	mGammaD_0250_Fitted_Iso_zoom_plot->GetXaxis()->SetTitle("Iso_{#mu#mu} [GeV/c]");
	mGammaD_0250_Fitted_Iso_zoom_plot->GetYaxis()->SetTitle("Fraction of events/0.1 GeV/c");
	mGammaD_0250_Fitted_Iso_zoom_plot->SetTitle("Dimuon Tracker Isolation for #gamma_{D} = 0.250 GeV");
	mGammaD_0250_Fitted_Iso_zoom_plot->SetFillColor(kRed);
	mGammaD_0250_Fitted_Iso_zoom_plot->DrawNormalized();
	bbar_Iso_zoom_plot->DrawNormalized("same");
	c12->SaveAs("mGammaD_0250_Fitted_Iso_zoom_plot.pdf", "recreate");

	TCanvas *c13 = new TCanvas("c13","c13",700,500);
	mGammaD_0275_Fitted_Iso_plot->GetXaxis()->SetTitle("Iso_{#mu#mu} [GeV/c]");
	mGammaD_0275_Fitted_Iso_plot->GetYaxis()->SetTitle("Fraction of events/1.0 GeV/c");
	mGammaD_0275_Fitted_Iso_plot->SetTitle("Dimuon Tracker Isolation for #gamma_{D} = 0.275 GeV");
	gStyle->SetOptStat("Mero");
	for(int i =0; i < mGammaD_0275_Fitted_iso.size(); i++){
		mGammaD_0275_Fitted_Iso_plot->Fill(mGammaD_0275_Fitted_iso[i]);
		mGammaD_0275_Fitted_Iso_zoom_plot->Fill(mGammaD_0275_Fitted_iso[i]);
	}
	mGammaD_0275_Fitted_Iso_plot->SetFillColor(kRed);
	mGammaD_0275_Fitted_Iso_plot->DrawNormalized();
	c13->SaveAs("mGammaD_0275_Fitted_Iso_plot.pdf", "recreate");
	c13->Clear();
	mGammaD_0275_Fitted_Iso_zoom_plot->GetXaxis()->SetTitle("Iso_{#mu#mu} [GeV/c]");
	mGammaD_0275_Fitted_Iso_zoom_plot->GetYaxis()->SetTitle("Fraction of events/0.1 GeV/c");
	mGammaD_0275_Fitted_Iso_zoom_plot->SetTitle("Dimuon Tracker Isolation for #gamma_{D} = 0.275 GeV");
	mGammaD_0275_Fitted_Iso_zoom_plot->SetFillColor(kRed);
	mGammaD_0275_Fitted_Iso_zoom_plot->DrawNormalized();
	c13->SaveAs("mGammaD_0275_Fitted_Iso_zoom_plot.pdf", "recreate");

	TCanvas *c14 = new TCanvas("c14","c14",700,500);
	mGammaD_0300_Fitted_Iso_plot->GetXaxis()->SetTitle("Iso_{#mu#mu} [GeV/c]");
	mGammaD_0300_Fitted_Iso_plot->GetYaxis()->SetTitle("Fraction of events/1.0 GeV/c");
	mGammaD_0300_Fitted_Iso_plot->SetTitle("Dimuon Tracker Isolation for #gamma_{D} = 0.300 GeV");
	gStyle->SetOptStat("Mero");
	for(int i =0; i < mGammaD_0300_Fitted_iso.size(); i++){
		mGammaD_0300_Fitted_Iso_plot->Fill(mGammaD_0300_Fitted_iso[i]);
		mGammaD_0300_Fitted_Iso_zoom_plot->Fill(mGammaD_0300_Fitted_iso[i]);
	}
	mGammaD_0300_Fitted_Iso_plot->SetFillColor(kRed);
	mGammaD_0300_Fitted_Iso_plot->DrawNormalized();
	c14->SaveAs("mGammaD_0300_Fitted_Iso_plot.pdf", "recreate");
	c14->Clear();
	mGammaD_0300_Fitted_Iso_zoom_plot->GetXaxis()->SetTitle("Iso_{#mu#mu} [GeV/c]");
	mGammaD_0300_Fitted_Iso_zoom_plot->GetYaxis()->SetTitle("Fraction of events/0.1 GeV/c");
	mGammaD_0300_Fitted_Iso_zoom_plot->SetTitle("Dimuon Tracker Isolation for #gamma_{D} = 0.300 GeV");
	mGammaD_0300_Fitted_Iso_zoom_plot->SetFillColor(kRed);
	mGammaD_0300_Fitted_Iso_zoom_plot->DrawNormalized();
	c14->SaveAs("mGammaD_0300_Fitted_Iso_zoom_plot.pdf", "recreate");

	TCanvas *c15 = new TCanvas("c15","c15",700,500);
	mGammaD_2000_Fitted_Iso_plot->GetXaxis()->SetTitle("Iso_{#mu#mu} [GeV/c]");
	mGammaD_2000_Fitted_Iso_plot->GetYaxis()->SetTitle("Fraction of events/1.0 GeV/c");
	mGammaD_2000_Fitted_Iso_plot->SetTitle("Dimuon Tracker Isolation for #gamma_{D} = 2.0 GeV");
	gStyle->SetOptStat("Mero");
	for(int i =0; i < mGammaD_2000_Fitted_iso.size(); i++){
		mGammaD_2000_Fitted_Iso_plot->Fill(mGammaD_2000_Fitted_iso[i]);
		mGammaD_2000_Fitted_Iso_zoom_plot->Fill(mGammaD_2000_Fitted_iso[i]);
	}
	mGammaD_2000_Fitted_Iso_plot->SetFillColor(kRed);
	mGammaD_2000_Fitted_Iso_plot->DrawNormalized();
	c15->SaveAs("mGammaD_2000_Fitted_Iso_plot.pdf", "recreate");
	c15->Clear();
	mGammaD_2000_Fitted_Iso_zoom_plot->GetXaxis()->SetTitle("Iso_{#mu#mu} [GeV/c]");
	mGammaD_2000_Fitted_Iso_zoom_plot->GetYaxis()->SetTitle("Fraction of events/0.1 GeV/c");
	mGammaD_2000_Fitted_Iso_zoom_plot->SetTitle("Dimuon Tracker Isolation for #gamma_{D} = 2.0 GeV");
	mGammaD_2000_Fitted_Iso_zoom_plot->SetFillColor(kRed);
	mGammaD_2000_Fitted_Iso_zoom_plot->DrawNormalized();
	c15->SaveAs("mGammaD_2000_Fitted_Iso_zoom_plot.pdf", "recreate");

	TCanvas *c16 = new TCanvas("c16","c16",700,500);
	mGammaD_8500_Fitted_Iso_plot->GetXaxis()->SetTitle("Iso_{#mu#mu} [GeV/c]");
	mGammaD_8500_Fitted_Iso_plot->GetYaxis()->SetTitle("Fraction of events/1.0 GeV/c");
	mGammaD_8500_Fitted_Iso_plot->SetTitle("Dimuon Tracker Isolation for #gamma_{D} = 8.5 GeV");
	gStyle->SetOptStat("Mero");
	for(int i =0; i < mGammaD_8500_Fitted_iso.size(); i++){
		mGammaD_8500_Fitted_Iso_plot->Fill(mGammaD_8500_Fitted_iso[i]);
		mGammaD_8500_Fitted_Iso_zoom_plot->Fill(mGammaD_8500_Fitted_iso[i]);
	}
	mGammaD_8500_Fitted_Iso_plot->SetFillColor(kRed);
	mGammaD_8500_Fitted_Iso_plot->DrawNormalized();
	bbar_Iso_plot->DrawNormalized("same");
	c16->SaveAs("mGammaD_8500_Fitted_Iso_plot.pdf", "recreate");
	c16->Clear();
	mGammaD_8500_Fitted_Iso_zoom_plot->GetXaxis()->SetTitle("Iso_{#mu#mu} [GeV/c]");
	mGammaD_8500_Fitted_Iso_zoom_plot->GetYaxis()->SetTitle("Fraction of events/0.1 GeV/c");
	mGammaD_8500_Fitted_Iso_zoom_plot->SetTitle("Dimuon Tracker Isolation for #gamma_{D} = 8.5 GeV");
	mGammaD_8500_Fitted_Iso_zoom_plot->SetFillColor(kRed);
	mGammaD_8500_Fitted_Iso_zoom_plot->DrawNormalized();
	bbar_Iso_zoom_plot->DrawNormalized("same");
	c16->SaveAs("mGammaD_8500_Fitted_Iso_zoom_plot.pdf", "recreate");

	TCanvas *caa = new TCanvas("caa","caa",700,500);
	mGammaD_0400_Fitted_Iso_plot->GetXaxis()->SetTitle("Iso_{#mu#mu} [GeV/c]");
	mGammaD_0400_Fitted_Iso_plot->GetYaxis()->SetTitle("Fraction of events/1.0 GeV/c");
	mGammaD_0400_Fitted_Iso_plot->SetTitle("Dimuon Tracker Isolation for #gamma_{D} = 0.275 GeV");
	gStyle->SetOptStat("Mero");
	for(int i =0; i < mGammaD_0400_Fitted_iso.size(); i++){
		mGammaD_0400_Fitted_Iso_plot->Fill(mGammaD_0400_Fitted_iso[i]);
		mGammaD_0400_Fitted_Iso_zoom_plot->Fill(mGammaD_0400_Fitted_iso[i]);
	}
	mGammaD_0400_Fitted_Iso_plot->SetFillColor(kRed);
	mGammaD_0400_Fitted_Iso_plot->DrawNormalized();
	caa->SaveAs("mGammaD_0400_Fitted_Iso_plot.pdf", "recreate");
	caa->Clear();
	mGammaD_0400_Fitted_Iso_zoom_plot->GetXaxis()->SetTitle("Iso_{#mu#mu} [GeV/c]");
	mGammaD_0400_Fitted_Iso_zoom_plot->GetYaxis()->SetTitle("Fraction of events/0.1 GeV/c");
	mGammaD_0400_Fitted_Iso_zoom_plot->SetTitle("Dimuon Tracker Isolation for #gamma_{D} = 0.275 GeV");
	mGammaD_0400_Fitted_Iso_zoom_plot->SetFillColor(kRed);
	mGammaD_0400_Fitted_Iso_zoom_plot->DrawNormalized();
	caa->SaveAs("mGammaD_0400_Fitted_Iso_zoom_plot.pdf", "recreate");

	TCanvas *cbb = new TCanvas("cbb","cbb",700,500);
	mGammaD_0700_Fitted_Iso_plot->GetXaxis()->SetTitle("Iso_{#mu#mu} [GeV/c]");
	mGammaD_0700_Fitted_Iso_plot->GetYaxis()->SetTitle("Fraction of events/1.0 GeV/c");
	mGammaD_0700_Fitted_Iso_plot->SetTitle("Dimuon Tracker Isolation for #gamma_{D} = 0.300 GeV");
	gStyle->SetOptStat("Mero");
	for(int i =0; i < mGammaD_0700_Fitted_iso.size(); i++){
		mGammaD_0700_Fitted_Iso_plot->Fill(mGammaD_0700_Fitted_iso[i]);
		mGammaD_0700_Fitted_Iso_zoom_plot->Fill(mGammaD_0700_Fitted_iso[i]);
	}
	mGammaD_0700_Fitted_Iso_plot->SetFillColor(kRed);
	mGammaD_0700_Fitted_Iso_plot->DrawNormalized();
	cbb->SaveAs("mGammaD_0700_Fitted_Iso_plot.pdf", "recreate");
	cbb->Clear();
	mGammaD_0700_Fitted_Iso_zoom_plot->GetXaxis()->SetTitle("Iso_{#mu#mu} [GeV/c]");
	mGammaD_0700_Fitted_Iso_zoom_plot->GetYaxis()->SetTitle("Fraction of events/0.1 GeV/c");
	mGammaD_0700_Fitted_Iso_zoom_plot->SetTitle("Dimuon Tracker Isolation for #gamma_{D} = 0.300 GeV");
	mGammaD_0700_Fitted_Iso_zoom_plot->SetFillColor(kRed);
	mGammaD_0700_Fitted_Iso_zoom_plot->DrawNormalized();
	cbb->SaveAs("mGammaD_0700_Fitted_Iso_zoom_plot.pdf", "recreate");

	TCanvas *ccc = new TCanvas("ccc","ccc",700,500);
	mGammaD_1000_Fitted_Iso_plot->GetXaxis()->SetTitle("Iso_{#mu#mu} [GeV/c]");
	mGammaD_1000_Fitted_Iso_plot->GetYaxis()->SetTitle("Fraction of events/1.0 GeV/c");
	mGammaD_1000_Fitted_Iso_plot->SetTitle("Dimuon Tracker Isolation for #gamma_{D} = 2.0 GeV");
	gStyle->SetOptStat("Mero");
	for(int i =0; i < mGammaD_1000_Fitted_iso.size(); i++){
		mGammaD_1000_Fitted_Iso_plot->Fill(mGammaD_1000_Fitted_iso[i]);
		mGammaD_1000_Fitted_Iso_zoom_plot->Fill(mGammaD_1000_Fitted_iso[i]);
	}
	mGammaD_1000_Fitted_Iso_plot->SetFillColor(kRed);
	mGammaD_1000_Fitted_Iso_plot->DrawNormalized();
	ccc->SaveAs("mGammaD_1000_Fitted_Iso_plot.pdf", "recreate");
	ccc->Clear();
	mGammaD_1000_Fitted_Iso_zoom_plot->GetXaxis()->SetTitle("Iso_{#mu#mu} [GeV/c]");
	mGammaD_1000_Fitted_Iso_zoom_plot->GetYaxis()->SetTitle("Fraction of events/0.1 GeV/c");
	mGammaD_1000_Fitted_Iso_zoom_plot->SetTitle("Dimuon Tracker Isolation for #gamma_{D} = 2.0 GeV");
	mGammaD_1000_Fitted_Iso_zoom_plot->SetFillColor(kRed);
	mGammaD_1000_Fitted_Iso_zoom_plot->DrawNormalized();
	ccc->SaveAs("mGammaD_1000_Fitted_Iso_zoom_plot.pdf", "recreate");

	TCanvas *cdd = new TCanvas("cdd","cdd",700,500);
	mGammaD_1500_Fitted_Iso_plot->GetXaxis()->SetTitle("Iso_{#mu#mu} [GeV/c]");
	mGammaD_1500_Fitted_Iso_plot->GetYaxis()->SetTitle("Fraction of events/1.0 GeV/c");
	mGammaD_1500_Fitted_Iso_plot->SetTitle("Dimuon Tracker Isolation for #gamma_{D} = 8.5 GeV");
	gStyle->SetOptStat("Mero");
	for(int i =0; i < mGammaD_1500_Fitted_iso.size(); i++){
		mGammaD_1500_Fitted_Iso_plot->Fill(mGammaD_1500_Fitted_iso[i]);
		mGammaD_1500_Fitted_Iso_zoom_plot->Fill(mGammaD_1500_Fitted_iso[i]);
	}
	mGammaD_1500_Fitted_Iso_plot->SetFillColor(kRed);
	mGammaD_1500_Fitted_Iso_plot->DrawNormalized();
	bbar_Iso_plot->DrawNormalized("same");
	cdd->SaveAs("mGammaD_1500_Fitted_Iso_plot.pdf", "recreate");
	cdd->Clear();
	mGammaD_1500_Fitted_Iso_zoom_plot->GetXaxis()->SetTitle("Iso_{#mu#mu} [GeV/c]");
	mGammaD_1500_Fitted_Iso_zoom_plot->GetYaxis()->SetTitle("Fraction of events/0.1 GeV/c");
	mGammaD_1500_Fitted_Iso_zoom_plot->SetTitle("Dimuon Tracker Isolation for #gamma_{D} = 8.5 GeV");
	mGammaD_1500_Fitted_Iso_zoom_plot->SetFillColor(kRed);


	mGammaD_1500_Fitted_Iso_zoom_plot->DrawNormalized();
	bbar_Iso_zoom_plot->DrawNormalized("same");
	cdd->SaveAs("mGammaD_1500_Fitted_Iso_zoom_plot.pdf", "recreate");


	TCanvas *c17 = new TCanvas("c17","c17",700,500);
	mGammaD_all_Fitted_Iso_plot->GetXaxis()->SetTitle("Iso_{#mu#mu} [GeV/c]");
	mGammaD_all_Fitted_Iso_plot->GetYaxis()->SetTitle("Fraction of events/1.0 GeV/c");
	mGammaD_all_Fitted_Iso_plot->SetTitle("Dimuon Tracker Isolation");
	gStyle->SetOptStat("Mero");
	for(int i =0; i < mGammaD_all_Fitted_iso.size(); i++){
		mGammaD_all_Fitted_Iso_plot->Fill(mGammaD_all_Fitted_iso[i]);
		mGammaD_all_Fitted_Iso_zoom_plot->Fill(mGammaD_all_Fitted_iso[i]);
	}
	mGammaD_all_Fitted_Iso_plot->SetFillColor(kRed);
	mGammaD_all_Fitted_Iso_plot->DrawNormalized();
	bbar_Iso_plot->DrawNormalized("same");
	c17->SaveAs("mGammaD_all_Fitted_Iso_plot.pdf", "recreate");
	c17->Clear();
	mGammaD_all_Fitted_Iso_zoom_plot->GetXaxis()->SetTitle("Iso_{#mu#mu} [GeV/c]");
	mGammaD_all_Fitted_Iso_zoom_plot->GetYaxis()->SetTitle("Fraction of events/0.1 GeV/c");
	mGammaD_all_Fitted_Iso_zoom_plot->SetTitle("Dimuon Tracker Isolation");
	mGammaD_all_Fitted_Iso_zoom_plot->SetFillColor(kRed);
	mGammaD_all_Fitted_Iso_zoom_plot->DrawNormalized();
	bbar_Iso_zoom_plot->DrawNormalized("same");
	c17->SaveAs("mGammaD_all_Fitted_Iso_zoom_plot.pdf", "recreate");

	/*
	   TH1D *mGammaD_0250_Consistent_Iso_plot = new TH1D("mGammaD_0250_Consistent_Iso_plot", "mGammaD_0250_Consistent_Iso_plot", 100, 0, 100);
	   TH1D *mGammaD_0275_Consistent_Iso_plot = new TH1D("mGammaD_0275_Consistent_Iso_plot", "mGammaD_0275_Consistent_Iso_plot", 100, 0, 100);
	   TH1D *mGammaD_0300_Consistent_Iso_plot = new TH1D("mGammaD_0300_Consistent_Iso_plot", "mGammaD_0300_Consistent_Iso_plot", 100, 0, 100);
	   TH1D *mGammaD_2000_Consistent_Iso_plot = new TH1D("mGammaD_2000_Consistent_Iso_plot", "mGammaD_2000_Consistent_Iso_plot", 100, 0, 100);
	   TH1D *mGammaD_8500_Consistent_Iso_plot = new TH1D("mGammaD_8500_Consistent_Iso_plot", "mGammaD_8500_Consistent_Iso_plot", 100, 0, 100);
	   TH1D *mGammaD_all_Consistent_Iso_plot = new TH1D("mGammaD_all_Consistent_Iso_plot", "mGammaD_all_Consistent_Iso_plot", 100, 0, 100);

	   TH1D *mGammaD_0250_Consistent_Iso_zoom_plot = new TH1D("mGammaD_0250_Consistent_Iso_zoom_plot", "mGammaD_0250_Consistent_Iso_zoom_plot", 100, 0, 10);
	   TH1D *mGammaD_0275_Consistent_Iso_zoom_plot = new TH1D("mGammaD_0275_Consistent_Iso_zoom_plot", "mGammaD_0275_Consistent_Iso_zoom_plot", 100, 0, 10);
	   TH1D *mGammaD_0300_Consistent_Iso_zoom_plot = new TH1D("mGammaD_0300_Consistent_Iso_zoom_plot", "mGammaD_0300_Consistent_Iso_zoom_plot", 100, 0, 10);
	   TH1D *mGammaD_2000_Consistent_Iso_zoom_plot = new TH1D("mGammaD_2000_Consistent_Iso_zoom_plot", "mGammaD_2000_Consistent_Iso_zoom_plot", 100, 0, 10);
	   TH1D *mGammaD_8500_Consistent_Iso_zoom_plot = new TH1D("mGammaD_8500_Consistent_Iso_zoom_plot", "mGammaD_8500_Consistent_Iso_zoom_plot", 100, 0, 10);
	   TH1D *mGammaD_all_Consistent_Iso_zoom_plot = new TH1D("mGammaD_all_Consistent_Iso_zoom_plot", "mGammaD_all_Consistent_Iso_zoom_plot", 100, 0, 10);

	   TCanvas *c18 = new TCanvas("c18","c18",700,500);
	   mGammaD_0250_Consistent_Iso_plot->GetXaxis()->SetTitle("Iso_{#mu#mu} [GeV/c]");
	   mGammaD_0250_Consistent_Iso_plot->GetYaxis()->SetTitle("Fraction of events/1.0 GeV/c");
	   mGammaD_0250_Consistent_Iso_plot->SetTitle("Dimuon Tracker Isolation for #gamma_{D} = 0.250 GeV");
	   gStyle->SetOptStat("Mero");
	   for(int i =0; i < mGammaD_0250_Consistent_iso.size(); i++){
	   mGammaD_0250_Consistent_Iso_plot->Fill(mGammaD_0250_Consistent_iso[i]);
	   mGammaD_0250_Consistent_Iso_zoom_plot->Fill(mGammaD_0250_Consistent_iso[i]);
	   }
	   mGammaD_0250_Consistent_Iso_plot->SetFillColor(kRed);
	   mGammaD_0250_Consistent_Iso_plot->DrawNormalized();
	   c18->SaveAs("mGammaD_0250_Consistent_Iso_plot.pdf", "recreate");
	   c18->Clear();
	   mGammaD_0250_Consistent_Iso_zoom_plot->GetXaxis()->SetTitle("Iso_{#mu#mu} [GeV/c]");
	   mGammaD_0250_Consistent_Iso_zoom_plot->GetYaxis()->SetTitle("Fraction of events/0.1 GeV/c");
	   mGammaD_0250_Consistent_Iso_zoom_plot->SetTitle("Dimuon Tracker Isolation for #gamma_{D} = 0.250 GeV");
	   mGammaD_0250_Consistent_Iso_zoom_plot->SetFillColor(kRed);
	   mGammaD_0250_Consistent_Iso_zoom_plot->DrawNormalized();
	   c18->SaveAs("mGammaD_0250_Consistent_Iso_zoom_plot.pdf", "recreate");

	   TCanvas *c19 = new TCanvas("c19","c19",700,500);
	   mGammaD_0275_Consistent_Iso_plot->GetXaxis()->SetTitle("Iso_{#mu#mu} [GeV/c]");
	   mGammaD_0275_Consistent_Iso_plot->GetYaxis()->SetTitle("Fraction of events/1.0 GeV/c");
	   mGammaD_0275_Consistent_Iso_plot->SetTitle("Dimuon Tracker Isolation for #gamma_{D} = 0.275 GeV");
	   gStyle->SetOptStat("Mero");
	   for(int i =0; i < mGammaD_0275_Consistent_iso.size(); i++){
	   mGammaD_0275_Consistent_Iso_plot->Fill(mGammaD_0275_Consistent_iso[i]);
	   mGammaD_0275_Consistent_Iso_zoom_plot->Fill(mGammaD_0275_Consistent_iso[i]);
	   }
	   mGammaD_0275_Consistent_Iso_plot->SetFillColor(kRed);
	   mGammaD_0275_Consistent_Iso_plot->DrawNormalized();
	   c19->SaveAs("mGammaD_0275_Consistent_Iso_plot.pdf", "recreate");
	   c19->Clear();
	   mGammaD_0275_Consistent_Iso_zoom_plot->GetXaxis()->SetTitle("Iso_{#mu#mu} [GeV/c]");
	   mGammaD_0275_Consistent_Iso_zoom_plot->GetYaxis()->SetTitle("Fraction of events/0.1 GeV/c");
	   mGammaD_0275_Consistent_Iso_zoom_plot->SetTitle("Dimuon Tracker Isolation for #gamma_{D} = 0.275 GeV");
	   mGammaD_0275_Consistent_Iso_zoom_plot->SetFillColor(kRed);
	   mGammaD_0275_Consistent_Iso_zoom_plot->DrawNormalized();
	   c19->SaveAs("mGammaD_0275_Consistent_Iso_zoom_plot.pdf", "recreate");

	   TCanvas *c20 = new TCanvas("c20","c20",700,500);
	   mGammaD_0300_Consistent_Iso_plot->GetXaxis()->SetTitle("Iso_{#mu#mu} [GeV/c]");
	   mGammaD_0300_Consistent_Iso_plot->GetYaxis()->SetTitle("Fraction of events/1.0 GeV/c");
	   mGammaD_0300_Consistent_Iso_plot->SetTitle("Dimuon Tracker Isolation for #gamma_{D} = 0.300 GeV");
	   gStyle->SetOptStat("Mero");
	   for(int i =0; i < mGammaD_0300_Consistent_iso.size(); i++){
	   mGammaD_0300_Consistent_Iso_plot->Fill(mGammaD_0300_Consistent_iso[i]);
	   mGammaD_0300_Consistent_Iso_zoom_plot->Fill(mGammaD_0300_Consistent_iso[i]);
	   }
	   mGammaD_0300_Consistent_Iso_plot->SetFillColor(kRed);
	   mGammaD_0300_Consistent_Iso_plot->DrawNormalized();
	   c20->SaveAs("mGammaD_0300_Consistent_Iso_plot.pdf", "recreate");
	   c20->Clear();
	   mGammaD_0300_Consistent_Iso_zoom_plot->GetXaxis()->SetTitle("Iso_{#mu#mu} [GeV/c]");
	   mGammaD_0300_Consistent_Iso_zoom_plot->GetYaxis()->SetTitle("Fraction of events/0.1 GeV/c");
	   mGammaD_0300_Consistent_Iso_zoom_plot->SetTitle("Dimuon Tracker Isolation for #gamma_{D} = 0.300 GeV");
	mGammaD_0300_Consistent_Iso_zoom_plot->SetFillColor(kRed);
	mGammaD_0300_Consistent_Iso_zoom_plot->DrawNormalized();
	c20->SaveAs("mGammaD_0300_Consistent_Iso_zoom_plot.pdf", "recreate");

	TCanvas *c21 = new TCanvas("c21","c21",700,500);
	mGammaD_2000_Consistent_Iso_plot->GetXaxis()->SetTitle("Iso_{#mu#mu} [GeV/c]");
	mGammaD_2000_Consistent_Iso_plot->GetYaxis()->SetTitle("Fraction of events/1.0 GeV/c");
	mGammaD_2000_Consistent_Iso_plot->SetTitle("Dimuon Tracker Isolation for #gamma_{D} = 2.0 GeV");
	gStyle->SetOptStat("Mero");
	for(int i =0; i < mGammaD_2000_Consistent_iso.size(); i++){
		mGammaD_2000_Consistent_Iso_plot->Fill(mGammaD_2000_Consistent_iso[i]);
		mGammaD_2000_Consistent_Iso_zoom_plot->Fill(mGammaD_2000_Consistent_iso[i]);
	}
	mGammaD_2000_Consistent_Iso_plot->SetFillColor(kRed);
	mGammaD_2000_Consistent_Iso_plot->DrawNormalized();
	c21->SaveAs("mGammaD_2000_Consistent_Iso_plot.pdf", "recreate");
	c21->Clear();
	mGammaD_2000_Consistent_Iso_zoom_plot->GetXaxis()->SetTitle("Iso_{#mu#mu} [GeV/c]");
	mGammaD_2000_Consistent_Iso_zoom_plot->GetYaxis()->SetTitle("Fraction of events/0.1 GeV/c");
	mGammaD_2000_Consistent_Iso_zoom_plot->SetTitle("Dimuon Tracker Isolation for #gamma_{D} = 2.0 GeV");
	mGammaD_2000_Consistent_Iso_zoom_plot->SetFillColor(kRed);
	mGammaD_2000_Consistent_Iso_zoom_plot->DrawNormalized();
	c21->SaveAs("mGammaD_2000_Consistent_Iso_zoom_plot.pdf", "recreate");

	TCanvas *c22 = new TCanvas("c22","c22",700,500);
	mGammaD_8500_Consistent_Iso_plot->GetXaxis()->SetTitle("Iso_{#mu#mu} [GeV/c]");
	mGammaD_8500_Consistent_Iso_plot->GetYaxis()->SetTitle("Fraction of events/1.0 GeV/c");
	mGammaD_8500_Consistent_Iso_plot->SetTitle("Dimuon Tracker Isolation for #gamma_{D} = 8.5 GeV");
	gStyle->SetOptStat("Mero");
	for(int i =0; i < mGammaD_8500_Consistent_iso.size(); i++){
		mGammaD_8500_Consistent_Iso_plot->Fill(mGammaD_8500_Consistent_iso[i]);
		mGammaD_8500_Consistent_Iso_zoom_plot->Fill(mGammaD_8500_Consistent_iso[i]);
	}
	mGammaD_8500_Consistent_Iso_plot->SetFillColor(kRed);
	mGammaD_8500_Consistent_Iso_plot->DrawNormalized();
	c22->SaveAs("mGammaD_8500_Consistent_Iso_plot.pdf", "recreate");
	c22->Clear();
	mGammaD_8500_Consistent_Iso_zoom_plot->GetXaxis()->SetTitle("Iso_{#mu#mu} [GeV/c]");
	mGammaD_8500_Consistent_Iso_zoom_plot->GetYaxis()->SetTitle("Fraction of events/0.1 GeV/c");
	mGammaD_8500_Consistent_Iso_zoom_plot->SetTitle("Dimuon Tracker Isolation for #gamma_{D} = 8.5 GeV");
	mGammaD_8500_Consistent_Iso_zoom_plot->SetFillColor(kRed);
	mGammaD_8500_Consistent_Iso_zoom_plot->DrawNormalized();
	c22->SaveAs("mGammaD_8500_Consistent_Iso_zoom_plot.pdf", "recreate");


	TCanvas *c23 = new TCanvas("c23","c23",700,500);
	mGammaD_all_Consistent_Iso_plot->GetXaxis()->SetTitle("Iso_{#mu#mu} [GeV/c]");
	mGammaD_all_Consistent_Iso_plot->GetYaxis()->SetTitle("Fraction of events/1.0 GeV/c");
	mGammaD_all_Consistent_Iso_plot->SetTitle("Dimuon Tracker Isolation");
	gStyle->SetOptStat("Mero");
	for(int i =0; i < mGammaD_all_Consistent_iso.size(); i++){
		mGammaD_all_Consistent_Iso_plot->Fill(mGammaD_all_Consistent_iso[i]);
		mGammaD_all_Consistent_Iso_zoom_plot->Fill(mGammaD_all_Consistent_iso[i]);
	}
	mGammaD_all_Consistent_Iso_plot->SetFillColor(kRed);
	mGammaD_all_Consistent_Iso_plot->DrawNormalized();
	c23->SaveAs("mGammaD_all_Consistent_Iso_plot.pdf", "recreate");
	c23->Clear();
	mGammaD_all_Consistent_Iso_zoom_plot->GetXaxis()->SetTitle("Iso_{#mu#mu} [GeV/c]");
	mGammaD_all_Consistent_Iso_zoom_plot->GetYaxis()->SetTitle("Fraction of events/0.1 GeV/c");
	mGammaD_all_Consistent_Iso_zoom_plot->SetTitle("Dimuon Tracker Isolation");
	mGammaD_all_Consistent_Iso_zoom_plot->SetFillColor(kRed);
	mGammaD_all_Consistent_Iso_zoom_plot->DrawNormalized();
	c23->SaveAs("mGammaD_all_Consistent_Iso_zoom_plot.pdf", "recreate");
	*/	

		BAM->Write();
}

void offline_selection_review(){
	//flag == 1 for signal and 0 for background

	//only run over samples that have individual files (to make it easier to find them with Fireworks)
	//These cT's should be in order.
//2.0 GeV
	//{{{
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/", 1);

	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/", 1);
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/", 1);
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/", 1);
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/", 1);
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_100_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/", 1);
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/", 1);
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_300_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/", 1);
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/", 1);
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_1000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/", 1);
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_2000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/", 1);

	//}}}
	//Sven's 0.25 GeV sample
	/*
	//{{{
	offline_vs_signal("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f//", 1);
	offline_vs_signal("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/", 1);
	offline_vs_signal("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/", 1);
	offline_vs_signal("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/", 1);
	offline_vs_signal("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/", 1);
	offline_vs_signal("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_100_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/", 1);
	offline_vs_signal("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/", 1);
	offline_vs_signal("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_300_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/", 1);
	offline_vs_signal("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/", 1);
	//}}}
	*/

	// Ben's 0.25 GeV sample

	//{{{

	//offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_1000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/", 1);
	//offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_2000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/", 1);


	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/", 1);
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/", 1);
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/", 1);
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/", 1);
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/", 1);
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/", 1);
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/", 1);
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/", 1);
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_1000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/", 1);
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_2000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/", 1);

	//}}}


	//8.5 GeV sample
	//{{{
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/", 1);
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/", 1);
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/", 1);
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/", 1);
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/", 1);
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_100_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/", 1);
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/", 1);
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_300_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/", 1);
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/", 1);
	//}}}
	//Jamal's 0.275 GeV sample
	/*
	//{{{
	offline_vs_signal("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/", 1);
	offline_vs_signal("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/", 1);
	offline_vs_signal("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/", 1);
	offline_vs_signal("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/", 1);
	offline_vs_signal("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/", 1);
	offline_vs_signal("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_100_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/", 1);
	offline_vs_signal("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/", 1);
	offline_vs_signal("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_300_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/", 1);
	offline_vs_signal("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/", 1);
	//}}}
	*/

	//Alfredo's 0.3 GeV sample
	/*
	//{{{
	offline_vs_signal("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/", 1);
	offline_vs_signal("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/", 1);
	offline_vs_signal("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/", 1);
	offline_vs_signal("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/", 1);
	offline_vs_signal("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/", 1);
	offline_vs_signal("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/", 1);
	//}}}
	*/

	//Ben's 0.275 GeV sample
	//{{{
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0275_cT_000_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_000_Evt_80k_PATANA_v4/151117_123308/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0275_cT_005_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_005_Evt_80k_PATANA_v4/151117_151528/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0275_cT_010_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_010_Evt_80k_PATANA_v4/151117_151628/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0275_cT_020_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_020_Evt_80k_PATANA_v4/151117_151724/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0275_cT_050_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_050_Evt_80k_PATANA_v4/151117_151824/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0275_cT_100_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_100_Evt_80k_PATANA_v4/151117_151935/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0275_cT_200_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_200_Evt_80k_PATANA_v4/151117_152115/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0275_cT_300_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_300_Evt_80k_PATANA_v4/151117_152230/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0275_cT_500_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_500_Evt_80k_PATANA_v4/151117_152335/asdf/", 1); 
	//}}}
	//Ben's 0.3 GeV sample
	//{{{
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_000_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_000_Evt_80k_PATANA_v4/151117_152519/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_005_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_005_Evt_80k_PATANA_v4/151117_152556/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_010_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_010_Evt_80k_PATANA_v4/151117_152703/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_020_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_020_Evt_80k_PATANA_v4/151117_152813/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_050_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_050_Evt_80k_PATANA_v4/151117_153006/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_100_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_100_Evt_80k_PATANA_v4/151117_153036/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_200_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_200_Evt_80k_PATANA_v4/151117_153141/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_300_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_300_Evt_80k_PATANA_v4/151117_153244/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_500_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_500_Evt_80k_PATANA_v4/151117_153321/asdf/", 1); 
	//}}}

	//0.4 GeV sample
	//{{{
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0400_cT_000_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_000_Evt_80k_PATANA_v4/151117_153421/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0400_cT_005_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_005_Evt_80k_PATANA_v4/151117_153513/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0400_cT_010_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_010_Evt_80k_PATANA_v4/151117_153558/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0400_cT_020_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_020_Evt_80k_PATANA_v4/151117_153657/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0400_cT_050_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_050_Evt_80k_PATANA_v4/151117_153812/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0400_cT_100_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_100_Evt_80k_PATANA_v4/151117_153904/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0400_cT_200_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_200_Evt_80k_PATANA_v4/151117_153951/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0400_cT_300_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_300_Evt_80k_PATANA_v4/151117_154045/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0400_cT_500_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_500_Evt_80k_PATANA_v4/151117_154251/asdf/", 1); 
	//}}}

	//0.7 GeV sample
	//{{{
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0700_cT_000_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_000_Evt_80k_PATANA_v4/151117_154344/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0700_cT_005_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_005_Evt_80k_PATANA_v4/151117_154442/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0700_cT_010_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_010_Evt_80k_PATANA_v4/151117_154535/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0700_cT_020_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_020_Evt_80k_PATANA_v4/151117_154632/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0700_cT_050_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_050_Evt_80k_PATANA_v4/151117_154716/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0700_cT_100_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_100_Evt_80k_PATANA_v4/151117_154749/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0700_cT_200_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_200_Evt_80k_PATANA_v4/151117_154834/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0700_cT_300_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_300_Evt_80k_PATANA_v4/151117_154929/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0700_cT_500_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_500_Evt_80k_PATANA_v4/151117_155023/asdf/", 1); 
	//}}}

	//1.0 GeV sample
	//{{{
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1000_cT_000_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_000_Evt_80k_PATANA_v4/151117_155128/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1000_cT_005_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_005_Evt_80k_PATANA_v4/151117_155253/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1000_cT_010_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_010_Evt_80k_PATANA_v4/151117_155348/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1000_cT_020_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_020_Evt_80k_PATANA_v4/151117_155445/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1000_cT_050_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_050_Evt_80k_PATANA_v4/151117_155539/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1000_cT_100_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_100_Evt_80k_PATANA_v4/151117_155629/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1000_cT_200_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_200_Evt_80k_PATANA_v4/151117_155726/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1000_cT_300_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_300_Evt_80k_PATANA_v4/151117_155825/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1000_cT_500_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_500_Evt_80k_PATANA_v4/151117_155914/asdf/", 1); 
	//}}}
	// 1.5 GeV sample
	//{{{
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1500_cT_000_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_000_Evt_80k_PATANA_v4/151117_160012/asdf/", 1);
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1500_cT_005_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_005_Evt_80k_PATANA_v4/151117_160122/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1500_cT_010_Evt_79k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_010_Evt_79k_PATANA_v4/151117_160146/asdf/", 1);
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1500_cT_020_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_020_Evt_80k_PATANA_v4/151117_160315/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1500_cT_100_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_100_Evt_80k_PATANA_v4/151117_160426/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1500_cT_200_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_200_Evt_80k_PATANA_v4/151117_160522/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1500_cT_300_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_300_Evt_80k_PATANA_v4/151117_160613/asdf/", 1); 
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1500_cT_500_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_500_Evt_80k_PATANA_v4/151117_160729/asdf/", 1);
	//}}}

//8 TeV samples
	/*
	//{{{

	//8 Tev
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_000_Evt_80k_8TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0250_cT_000_Evt_80k_PATANA_v4/151117_151201/0000/", 1);
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_005_Evt_80k_8TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0250_cT_005_Evt_80k_PATANA_v4/151117_151250/0000/", 1);
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_010_Evt_80k_8TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0250_cT_010_Evt_80k_PATANA_v4/151117_151325/0000/", 1);
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_020_Evt_80k_8TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0250_cT_020_Evt_80k_PATANA_v4/151117_151402/0000/", 1);
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_050_Evt_80k_8TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0250_cT_050_Evt_80k_PATANA_v4/151117_151430/0000/", 1);
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_100_Evt_80k_8TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0250_cT_100_Evt_80k_PATANA_v4/151117_151508/0000/", 1);
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_200_Evt_80k_8TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0250_cT_200_Evt_80k_PATANA_v4/151117_151538/0000/", 1);
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_300_Evt_80k_8TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0250_cT_300_Evt_80k_PATANA_v4/151117_151622/0000/", 1);
	offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_500_Evt_80k_8TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0250_cT_500_Evt_80k_PATANA_v4/151117_151650/0000/", 1);
	//}}}
	*/


	offline_vs_signal("/fdata/hepx/store/user/bmichlin/bbar/asdf/",0);
	//offline_vs_signal("/fdata/hepx/store/user/bmichlin/DarkSUSY_bbar/2015D/",0); //old, first run of bbar

	makePlots();


}


