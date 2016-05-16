#include <algorithm>    // std::max
#include "TMath.h"
#include <math.h>
#include "TEfficiency.h"
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

///----Global Variables ----///
TFile *BAM = new TFile("Efficiency_Plots.root","RECREATE");

Float_t count_gam_A0[160][160];
Float_t count_rec_A0[160][160];
Float_t eff_A0[160][160];

Float_t count_gam_A1[160][160];
Float_t count_rec_A1[160][160];
Float_t eff_A1[160][160];

void makeCounters(){

	for(int k=0;k<160;k++){
		for(int j=0;j<160;j++){
			count_gam_A0[k][j]=0.0;
			count_rec_A0[k][j]=0.0;
			eff_A0[k][j]=0.0;

			count_gam_A1[k][j]=0.0;
			count_rec_A1[k][j]=0.0;
			eff_A1[k][j]=0.0;
		}
	}
}



double My_dPhi (double phi1, double phi2) {
	double dPhi = phi1 - phi2;
	if (dPhi >  TMath::Pi()) dPhi -= 2*TMath::Pi();
	if (dPhi <  -TMath::Pi()) dPhi += 2*TMath::Pi();
	return fabs(dPhi);
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

void create_eff_pergamD2DLxyLz(TString fileName){


	//bool verbose(true);
	bool verbose(false);
	TString dirname(fileName);
	TChain* chain = new TChain("dummy");
	TString ext("out_ana_");

	//Get the sample mass
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


	Float_t ev_all[40]={0.0};

	Bool_t is1GenMu17;
	Bool_t is2GenMu8;
	Bool_t is3GenMu8;
	Bool_t is4GenMu8;

	Bool_t is1SelMu17;
	Bool_t is2SelMu8;
	Bool_t is3SelMu8;
	Bool_t is4SelMu8;

	Int_t npatm;


	Float_t genA0_Lxy_rdet;
	Float_t genA1_Lxy_rdet;

	Float_t genA0_Lz_rdet;
	Float_t genA1_Lz_rdet;

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

	Float_t genA0Mu0_eta;
	Float_t genA1Mu0_eta;
	Float_t genA0Mu1_eta;
	Float_t genA1Mu1_eta;


	Float_t genA0Mu0_phi;
	Float_t genA1Mu0_phi;
	Float_t genA0Mu1_phi;
	Float_t genA1Mu1_phi;

	Float_t muJetC_muon1_track_minchi2;
	Float_t muJetC_muon2_track_minchi2;
	Float_t muJetF_muon1_track_minchi2;
	Float_t muJetF_muon2_track_minchi2;

	Int_t event;
	Int_t ev2dim;
	Int_t ev2mj;

	Bool_t isVtxOK;
	Bool_t is2DimDzOK;
	Bool_t is2DimVtxOK;
	Bool_t is2DimHLTFired;
	Bool_t is2DimIsoTkOK;
	Bool_t is2DimMassOK;

	Float_t genA0_px;
	Float_t genA0_py;
	Float_t genA1_px;
	Float_t genA1_py;

	Bool_t isDiMuonHLTFired;


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




		t->SetBranchAddress("event",&event);

		t->SetBranchAddress("is1GenMu17",&is1GenMu17);
		t->SetBranchAddress("is2GenMu8",&is2GenMu8);
		t->SetBranchAddress("is3GenMu8",&is3GenMu8);
		t->SetBranchAddress("is4GenMu8",&is4GenMu8);

		t->SetBranchAddress("is1SelMu17",&is1SelMu17);
		t->SetBranchAddress("is2SelMu8",&is2SelMu8);
		t->SetBranchAddress("is3SelMu8",&is3SelMu8);
		t->SetBranchAddress("is4SelMu8",&is4SelMu8);

		t->SetBranchAddress("isVertexOK",&isVtxOK);

		//t->SetBranchAddress("is4GenMu8",&is4GenMu8);

		t->SetBranchAddress("genA0_Lxy", &genA0_Lxy_rdet);
		t->SetBranchAddress("genA0_Lz",  &genA0_Lz_rdet);
		t->SetBranchAddress("genA1_Lxy", &genA1_Lxy_rdet);
		t->SetBranchAddress("genA1_Lz",  &genA1_Lz_rdet);


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

		t->SetBranchAddress("genA0Mu0_eta",&genA0Mu0_eta);
		t->SetBranchAddress("genA1Mu0_eta",&genA1Mu0_eta);
		t->SetBranchAddress("genA0Mu1_eta",&genA0Mu1_eta);
		t->SetBranchAddress("genA1Mu1_eta",&genA1Mu1_eta);

		t->SetBranchAddress("genA0Mu0_phi",&genA0Mu0_phi);
		t->SetBranchAddress("genA1Mu0_phi",&genA1Mu0_phi);
		t->SetBranchAddress("genA0Mu1_phi",&genA0Mu1_phi);
		t->SetBranchAddress("genA1Mu1_phi",&genA1Mu1_phi);

		t->SetBranchAddress("diMuonC_FittedVtx_px", &diMuonC_FittedVtx_px);
		t->SetBranchAddress("diMuonC_FittedVtx_py", &diMuonC_FittedVtx_py);
		t->SetBranchAddress("diMuonF_FittedVtx_px", &diMuonF_FittedVtx_px);
		t->SetBranchAddress("diMuonF_FittedVtx_py", &diMuonF_FittedVtx_py);

		t->SetBranchAddress("genA0_px", & genA0_px);
		t->SetBranchAddress("genA0_py", & genA0_py);
		t->SetBranchAddress("genA1_px", & genA1_px);
		t->SetBranchAddress("genA1_py", & genA1_py);

		t->SetBranchAddress("isDiMuonHLTFired",               &isDiMuonHLTFired);

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

		Int_t nentries = t->GetEntries();


		//Float_t bin_edges[41]={0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,78,80};
		Float_t bin_edges[161]={0.,0.5,1.,1.5,2.,2.5,3.,3.5,4.,4.5,5.,5.5,6.,6.5,7.,7.5,8.,8.5,9.,9.5,10.,10.5,11.,11.5,12.,12.5,13.,13.5,14.,14.5,15.,15.5,16.,16.5,17.,17.5,18.,18.5,19.,19.5,20.,20.5,21.,21.5,22.,22.5,23.,23.5,24.,24.5,25.,25.5,26.,26.5,27.,27.5,28.,28.5,29.,29.5,30.,30.5,31.,31.5,32.,32.5,33.,33.5,34.,34.5,35.,35.5,36.,36.5,37.,37.5,38.,38.5,39.,39.5,40.,40.5,41.,41.5,42.,42.5,43.,43.5,44.,44.5,45.,45.5,46.,46.5,47.,47.5,48.,48.5,49.,49.5,50.,50.5,51.,51.5,52.,52.5,53.,53.5,54.,54.5,55.,55.5,56.,56.5,57.,57.5,58.,58.5,59.,59.5,60.,60.5,61.,61.5,62.,62.5,63.,63.5,64.,64.5,65.,65.5,66.,66.5,67.,67.5,68.,68.5,69.,69.5,70.,70.5,71.,71.5,72.,72.5,73.,73.5,74.,74.5,75.,75.5,76.,76.5,77.,77.5,78.,78.5,79.,79.5,80.};
		//Float_t bin_edges_Lz[21]={0,4,8,12,16,20,24,28,32,36,40,44,48,52,56,60,64,68,72,76,80};
		Float_t bin_edges_Lz[161]={0.,0.5,1.,1.5,2.,2.5,3.,3.5,4.,4.5,5.,5.5,6.,6.5,7.,7.5,8.,8.5,9.,9.5,10.,10.5,11.,11.5,12.,12.5,13.,13.5,14.,14.5,15.,15.5,16.,16.5,17.,17.5,18.,18.5,19.,19.5,20.,20.5,21.,21.5,22.,22.5,23.,23.5,24.,24.5,25.,25.5,26.,26.5,27.,27.5,28.,28.5,29.,29.5,30.,30.5,31.,31.5,32.,32.5,33.,33.5,34.,34.5,35.,35.5,36.,36.5,37.,37.5,38.,38.5,39.,39.5,40.,40.5,41.,41.5,42.,42.5,43.,43.5,44.,44.5,45.,45.5,46.,46.5,47.,47.5,48.,48.5,49.,49.5,50.,50.5,51.,51.5,52.,52.5,53.,53.5,54.,54.5,55.,55.5,56.,56.5,57.,57.5,58.,58.5,59.,59.5,60.,60.5,61.,61.5,62.,62.5,63.,63.5,64.,64.5,65.,65.5,66.,66.5,67.,67.5,68.,68.5,69.,69.5,70.,70.5,71.,71.5,72.,72.5,73.,73.5,74.,74.5,75.,75.5,76.,76.5,77.,77.5,78.,78.5,79.,79.5,80.};


		for(int k=0;k<nentries;k++){
			t->GetEntry(k);
			//Only find the efficiency for events which pass the trigger
			if(isDiMuonHLTFired){
			if(is4GenMu8==true){
				Float_t dphi_gD = My_dPhi(genA1_phi,genA0_phi);
				//A0 loop
				for(int n=0;n<160;n++){
					if(fabs(genA0_Lz_rdet)>bin_edges_Lz[n] && fabs(genA0_Lz_rdet)<bin_edges_Lz[n+1]){
						for(int m=0;m<160;m++){
							if(genA0_Lxy_rdet>bin_edges[m] && genA0_Lxy_rdet<bin_edges[m+1]){
								count_gam_A0[n][m]++;

								if(MatchRECOtoGENdimuons(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_phi, diMuonF_FittedVtx_eta, diMuonF_FittedVtx_phi, genA0_eta, genA0_phi, genA1_eta, genA0_phi) == 0){ //diMuonC -> A0, diMuonF -> A1

								}else{ //diMuonC -> A1, diMuonF -> A0

								}

							if(dr < 0.5) count_rec_A0[n][m]++;
							}
						}
					}
				}
				//A1 loop
				for(int n=0;n<160;n++){
					if(fabs(genA1_Lz_rdet)>bin_edges_Lz[n] && fabs(genA1_Lz_rdet)<bin_edges_Lz[n+1]){
						for(int m=0;m<160;m++){
							if(genA1_Lxy_rdet>bin_edges[m] && genA1_Lxy_rdet<bin_edges[m+1]){
								count_gam_A1[n][m]++;
									Float_t dR1=0.0;
									Float_t dphi1=0.0;
									Float_t deta1=0.0;

									Int_t match_mu=0;

									   if(j==0){ dphi1 = My_dPhi(selMu0_phi,genA1_phi); deta1 = selMu0_eta - genA1_eta;}
									   if(j==1){ dphi1 = My_dPhi(selMu1_phi,genA1_phi); deta1 = selMu1_eta - genA1_eta;}
									   if(j==2){ dphi1 = My_dPhi(selMu2_phi,genA1_phi); deta1 = selMu2_eta - genA1_eta;}
									   if(j==3){ dphi1 = My_dPhi(selMu3_phi,genA1_phi); deta1 = selMu3_eta - genA1_eta;}

									   dR1 = sqrt(dphi1*dphi1+deta1*deta1);
									   if(dR1<0.5) match_mu++;
									   if(match_mu >= 2) count_rec_A1[n][m]++;
									   }
								}
							}
						}
			} //dPhi loop
			}//Trigger loop
			} //event loop
			myfile->Close();
			}//closing while loop
		}//closing method


		void makePlots(){

			TH2F *den_2D_A0 = new TH2F("den_2D_A0","den_2D_A0",160,0,80,160,0.0,80.0);
			TH2F *num_2D_A0 = new TH2F("num_2D_A0","num_2D_A0",160,0,80,160,0.0,80.0);

			TH2F *eff_2D_A0 = new TH2F("eff_2D_A0","eff_2D_A0",160,0,80,160,0.0,80.0);
			TH2F *eff_2D_A1 = new TH2F("eff_2D_A1","eff_2D_A1",160,0,80,160,0.0,80.0);


			for(int k=0;k<160;k++){
				for(int j=0;j<160;j++){

					num_2D_A0->SetBinContent(k+1,j+1,count_rec_A0[k][j]);

					den_2D_A0->SetBinContent(k+1,j+1,count_gam_A0[k][j]);

					if(count_gam_A0[k][j]!=0) eff_A0[k][j] = count_rec_A0[k][j]/(count_gam_A0[k][j]*1.0);
					if(count_rec_A0[k][j]==0 && count_gam_A0[k][j]!=0)   eff_A0[k][j] = 0.0001;

					cout<<" efficiency A0   "<<eff_A0[k][j]<<endl;
					eff_2D_A0->SetBinContent(k+1,j+1,eff_A0[k][j]);


					if(count_gam_A1[k][j]!=0) eff_A1[k][j] = count_rec_A1[k][j]/(count_gam_A1[k][j]*1.0);
					if(count_rec_A1[k][j]==0 && count_gam_A1[k][j]!=0)   eff_A1[k][j] = 0.0001;

					cout<<" efficiency A1   "<<eff_A1[k][j]<<endl;

					eff_2D_A1->SetBinContent(k+1,j+1,eff_A1[k][j]);
				}
			}

			eff_2D_A0->GetZaxis()->SetRangeUser(0.0,1.0);
			eff_2D_A1->GetZaxis()->SetRangeUser(0.0,1.0);

			UInt_t Number = 5;
			Double_t Red[5]   = { 0.00, 0.09, 0.18, 0.09, 0.00 };
			Double_t Green[5] = { 0.01, 0.02, 0.39, 0.68, 0.97 };
			Double_t Blue[5]  = { 0.17, 0.39, 0.62, 0.79, 0.97 };
			Double_t Length[5] = { 0.00, 0.34, 0.61, 0.84, 1.00 };

			Int_t nb=50;
			TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,nb);

			Int_t colors[] = {0,1,2,3,4,5,6}; // #colors >= #levels - 1
			gStyle->SetPalette((sizeof(colors)/sizeof(Int_t)), colors);

			Double_t levels[] = {-10,0.0,0.2,0.4,0.6,0.8,1.0, 3.4e38};

			eff_2D_A0->SetContour((sizeof(levels)/sizeof(Double_t)), levels);

			const Int_t NRGBs = 5;
			const Int_t NCont = 104;

			Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
			Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
			Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
			Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };

			TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);

			gStyle->SetNumberContours(NCont);

			eff_2D_A0->SetContour(NCont);


			TCanvas *c = new TCanvas("c","c",700,500);
			c->SetRightMargin(0.15);
			eff_2D_A0->GetYaxis()->SetTitle("#gamma_{D1} Lxy [cm]");
			eff_2D_A0->GetXaxis()->SetTitle("|#gamma_{D1} Lz| [cm]");
			eff_2D_A0->GetZaxis()->SetTitle("Eff_{rec}/accep_{gen}");
			gStyle->SetOptStat(0);
			//    eff_2D_A0->SetContour((sizeof(levels)/sizeof(Double_t)), levels);
			eff_2D_A0->Draw("COLZ");

			c->SaveAs("eff_2D_LxyLz_A0.pdf","recreate");
			//I am not quite sure what this did...    
			//if(l==0) c->SaveAs("eff_2D_LxyLz_A0_ct05.pdf","recreate");




			TCanvas *c1 = new TCanvas("c1","c1",700,500);
			c1->SetRightMargin(0.15);
			eff_2D_A1->GetYaxis()->SetTitle("#gamma_{D2} Lxy [cm]");
			eff_2D_A1->GetXaxis()->SetTitle("|#gamma_{D2} Lz| [cm]");
			eff_2D_A1->GetZaxis()->SetTitle("Eff_{rec}/accep_{gen}");
			gStyle->SetOptStat(0);
			eff_2D_A1->Draw("COLZ");
			c1->SaveAs("eff_2D_LxyLz_A1.pdf","recreate");
			//I am not quite sure what this did...    
			//if(l==0) c1->SaveAs("eff_2D_LxyLz_A1_ct05.pdf","recreate");

		}//closing method

		void bam2_eff_pergramD2DLxyLz(){
			makeCounters();

			//These cT's should be in order.
			/*
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_100_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_300_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");

			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_1000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_2000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");


			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f//");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_100_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_300_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_1000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_2000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
			   */

			create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
			create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
			create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
			create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
			create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
			create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
			create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
			create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
			create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");

			create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_1000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
			create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_2000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");

			/*
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_100_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_300_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");



			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_100_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_300_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");



			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
			   create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
			   */


			makePlots();

			BAM->Write();
		}
