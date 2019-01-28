#include <algorithm>    // std::max
#include "TMath.h"
#include <math.h>
#include "TEfficiency.h"

///----Global Variables ----///
TFile *BAM = new TFile("Efficiency_Plots.root","RECREATE");

Float_t count_gam_A0[20][40];
Float_t count_rec_A0[20][40];
Float_t eff_A0[20][40];

Float_t count_gam_A1[20][40];
Float_t count_rec_A1[20][40];
Float_t eff_A1[20][40];

TH1F *den_1D_A0_LXY = new TH1F("den_1D_A0_LXY", "den_1D_A0_LXY", 40, 0, 80);
TH1F *num_1D_A0_LXY = new TH1F("num_1D_A0_LXY", "num_1D_A0_LXY", 40, 0, 80);

TH1F *den_1D_A0_LZ = new TH1F("den_1D_A0_LZ", "den_1D_A0_LZ", 20, 0, 80);
TH1F *num_1D_A0_LZ = new TH1F("num_1D_A0_LZ", "num_1D_A0_LZ", 20, 0, 80);

TH1F *den_1D_A1_LXY = new TH1F("den_1D_A1_LXY", "den_1D_A1_LXY", 40, 0, 80);
TH1F *num_1D_A1_LXY = new TH1F("num_1D_A1_LXY", "num_1D_A1_LXY", 40, 0, 80);

TH1F *den_1D_A1_LZ = new TH1F("den_1D_A1_LZ", "den_1D_A1_LZ", 20, 0, 80);
TH1F *num_1D_A1_LZ = new TH1F("num_1D_A1_LZ", "num_1D_A1_LZ", 20, 0, 80);

TH1F *dR_A0 = new TH1F("dR_A0", "dR_A0", 100, 0, 1);
TH1F *dR_A1 = new TH1F("dR_A1", "dR_A1", 100, 0, 1);

TH1F *dPhi_Plot = new TH1F("dPhi_A0", "dPhi_A0", 1400, -7, 7);

TH1F *den_1D_A1_pT = new TH1F("den_1D_A1_pT", "den_1D_A1_pT", 130, 0, 130);
TH1F *num_1D_A1_pT = new TH1F("num_1D_A1_pT", "num_1D_A1_pT", 130, 0, 130);

TH1F *den_1D_A0_pT = new TH1F("den_1D_A0_pT", "den_1D_A0_pT", 130, 0, 130);
TH1F *num_1D_A0_pT = new TH1F("num_1D_A0_pT", "num_1D_A0_pT", 130, 0, 130);

//Plots WITHOUT cuts
TH2F *dR_vs_dPhi = new TH2F("dR_vs_dPhi", "dR_vs_dPhi", 100, 0, 1, 800, -4, 4);

TH2F *dR_vs_dLxy = new TH2F("dR_vs_dLxy", "dR_vs_dLxy", 100, 0, 1, 40, 0, 80);
TH2F *dPhi_vs_dLxy = new TH2F("dPhi_vs_dLxy", "dPhi_vs_dLxy", 800, -4, 4, 40, 0, 80);

TH2F *dR_vs_dLz = new TH2F("dR_vs_dLz", "dR_vs_dLz", 100, 0, 1, 20, 0, 80);
TH2F *dPhi_vs_dLz = new TH2F("dPhi_vs_dLz", "dPhi_vs_dLz", 800, -4, 4, 20, 0, 80);


TH2F *dR_vs_pt = new TH2F("dR_vs_pt", "dR_vs_pt", 100, 0, 1, 130, 0, 130);
TH2F *pt_vs_dPhi = new TH2F("pt_vs_dPhi", "pt_vs_dPhi", 130,0,130, 800, -4, 4);

TH2F *pt_vs_dLxy = new TH2F("pt_vs_dLxy", "pt_vs_dLxy", 130,0,130, 40, 0, 80);
TH2F *pt_vs_dLz = new TH2F("pt_vs_dLz", "pt_vs_dLz", 130,0,130, 20, 0, 80);

void makeCounters(){

for(int k=0;k<20;k++){
	for(int j=0;j<40;j++){
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
	TSubString cT_string = (str(last+str3.Length(),3));

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

	Float_t ev_4gm[40]={0.0};
	Float_t ev_4gmlxylzcut[40]={0.0};

	Float_t ev_4rm[40]={0.0};

	Float_t eventsrecover[40]={0.0};
	Float_t ev_2dim[40]={0.0};
	Float_t ev_2dimvtxok[40]={0.0};
	Float_t ev_2mj[40]={0.0};
	Float_t ev_isVtxOK[40]={0.0};
	Float_t ev_is2DimDzOK[40]={0.0};
	Float_t ev_is2DimVtxOK[40]={0.0};
	Float_t ev_is2DimHLTFired[40]={0.0};
	Float_t ev_is2DimIsoTkOK[40]={0.0};
	Float_t ev_is2DimMassOK[40]={0.0};
	Float_t ev_is2DimMassOK2[40]={0.0};

	Float_t ev_2dimhit[40]={0.0};
	Float_t ev_2dimhit_allcut[40]={0.0};
	Float_t ev_2dimhit_allcutrecov[40]={0.0};
	Float_t ev_2dimhit_allcutrecov2[40]={0.0};

	Float_t ev_2dim_recov[40]={0.0};
	Float_t ev_2dim_recov2[40]={0.0};

	Float_t ev_2dimhit_recov2dim[40]={0.0};
	Float_t ev_2dimhit_recovmuJetC[40]={0.0};
	Float_t ev_2dimhit_recovmuJetF[40]={0.0};

	Float_t ev_2dimhit_recov2dim2[40]={0.0};
	Float_t ev_2dimhit_recovmuJetC2[40]={0.0};
	Float_t ev_2dimhit_recovmuJetF2[40]={0.0};

	Float_t ev_2dimhitgt[40]={0.0};
	Float_t ev_2dimhitfvtx[40]={0.0};
	Float_t ev_2dimhit_fail2mujets[40]={0.0};
	Float_t ev_2dimhit_fail2mujets_recover[40]={0.0};
	Float_t ev_2dimhit_failmuJetC[40]={0.0};
	Float_t ev_2dimhit_failmuJetC_recover[40]={0.0};
	Float_t ev_2dimhit_failmuJetF[40]={0.0};
	Float_t ev_2dimhit_failmuJetF_recover[40]={0.0};


	Float_t ev_2dimhit2[40]={0.0};
	Float_t ev_2dimhit_fail2mujets2[40]={0.0};
	Float_t ev_2dimhit_fail2mujets_recover2[40]={0.0};
	Float_t ev_2dimhit_failmuJetC2[40]={0.0};
	Float_t ev_2dimhit_failmuJetC_recover2[40]={0.0};
	Float_t ev_2dimhit_failmuJetF2[40]={0.0};
	Float_t ev_2dimhit_failmuJetF_recover2[40]={0.0};


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

	Float_t diMuonC_FittedVtx_px;
	Float_t diMuonC_FittedVtx_py;
	Float_t diMuonF_FittedVtx_px;
	Float_t diMuonF_FittedVtx_py;

	Float_t genA0_px;
	Float_t genA0_py;
	Float_t genA1_px;
	Float_t genA1_py;

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


		t->SetBranchAddress("diMuonC_FittedVtx_px", &diMuonC_FittedVtx_px);
		t->SetBranchAddress("diMuonC_FittedVtx_py", &diMuonC_FittedVtx_py);
		t->SetBranchAddress("diMuonF_FittedVtx_px", &diMuonF_FittedVtx_px);
		t->SetBranchAddress("diMuonF_FittedVtx_py", &diMuonF_FittedVtx_py);

		t->SetBranchAddress("genA0_px", & genA0_px);
		t->SetBranchAddress("genA0_py", & genA0_py);
		t->SetBranchAddress("genA1_px", & genA1_px);
		t->SetBranchAddress("genA1_py", & genA1_py);



		Int_t nentries = t->GetEntries();


		Float_t bin_edges[41]={0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,78,80};
		Float_t bin_edges_Lz[21]={0,4,8,12,16,20,24,28,32,36,40,44,48,52,56,60,64,68,72,76,80};


		for(int k=0;k<nentries;k++){
			t->GetEntry(k);
			if(is4GenMu8==true){
				Float_t dphi_gD = My_dPhi(genA1_phi,genA0_phi);
				dPhi_Plot->Fill(dphi_gD);
				if(fabs(dphi_gD)>=0){ //What does this cut do?  Why do we want to make sure that the muons are back-to-back?
				//if(fabs(dphi_gD)>2){ //What does this cut do?  Why do we want to make sure that the muons are back-to-back?
				//if(fabs(dphi_gD)>2.5){ //What does this cut do?  Why do we want to make sure that the muons are back-to-back?
					for(int n=0;n<20;n++){
						if(fabs(genA0_Lz_rdet)>bin_edges_Lz[n] && fabs(genA0_Lz_rdet)<bin_edges_Lz[n+1]){
							for(int m=0;m<40;m++){
								if(genA0_Lxy_rdet>bin_edges[m] && genA0_Lxy_rdet<bin_edges[m+1]){
									count_gam_A0[n][m]++;
									den_1D_A0_LXY->Fill(genA0_Lxy_rdet);
									den_1D_A0_LZ->Fill(genA0_Lz_rdet);

									double denpt = sqrt(genA0_px*genA0_px + genA0_py*genA0_py);
									den_1D_A0_pT->Fill(denpt);

									
									npatm = 0;
									if(selMu0_eta != -100) npatm++;
									if(selMu1_eta != -100) npatm++;
									if(selMu2_eta != -100) npatm++;
									if(selMu3_eta != -100) npatm++;
									if(npatm>=2 && is2SelMu8){
										Float_t dR1=0.0;
										Float_t dphi1=0.0;
										Float_t deta1=0.0;

										Int_t match_mu=0;
										for(int j=0;j<npatm;j++){

								if(j==0){ dphi1 = My_dPhi(selMu0_phi,genA0_phi); deta1 = selMu0_eta - genA0_eta;}
								if(j==1){ dphi1 = My_dPhi(selMu1_phi,genA0_phi); deta1 = selMu1_eta - genA0_eta;}
								if(j==2){ dphi1 = My_dPhi(selMu2_phi,genA0_phi); deta1 = selMu2_eta - genA0_eta;}
								if(j==3){ dphi1 = My_dPhi(selMu3_phi,genA0_phi); deta1 = selMu3_eta - genA0_eta;}

											dR1 = sqrt(dphi1*dphi1+deta1*deta1);
											dR_A0->Fill(dR1);
											if(dR1<0.5) match_mu++;
										}
										if(match_mu>=2)   {
											count_rec_A0[n][m]++;
											num_1D_A0_LXY->Fill(genA0_Lxy_rdet);
											num_1D_A0_LZ->Fill(genA0_Lz_rdet);
										double numpt = sqrt(genA0_px*genA0_px + genA0_py*genA0_py);
										num_1D_A0_pT->Fill(numpt);
										}
									}
								}
							}
						}
					}


					for(int n=0;n<20;n++){
						if(fabs(genA1_Lz_rdet)>bin_edges_Lz[n] && fabs(genA1_Lz_rdet)<bin_edges_Lz[n+1]){

							for(int m=0;m<40;m++){
								if(genA1_Lxy_rdet>bin_edges[m] && genA1_Lxy_rdet<bin_edges[m+1]){
									count_gam_A1[n][m]++;
									den_1D_A1_LXY->Fill(genA1_Lxy_rdet);
									den_1D_A1_LZ->Fill(genA1_Lz_rdet);

									double denpt = sqrt(genA1_px*genA1_px + genA1_py*genA1_py);
									den_1D_A1_pT->Fill(denpt);

									npatm = 0;
									if(selMu0_eta != -100) npatm++;
									if(selMu1_eta != -100) npatm++;
									if(selMu2_eta != -100) npatm++;
									if(selMu3_eta != -100) npatm++;

									if(npatm>=2 && is2SelMu8){
										Float_t dR1=0.0;
										Float_t dphi1=0.0;
										Float_t deta1=0.0;

										Int_t match_mu=0;
										for(int j=0;j<npatm;j++){	

							if(j==0){ dphi1 = My_dPhi(selMu0_phi,genA1_phi); deta1 = selMu0_eta - genA1_eta;}
							if(j==1){ dphi1 = My_dPhi(selMu1_phi,genA1_phi); deta1 = selMu1_eta - genA1_eta;}
							if(j==2){ dphi1 = My_dPhi(selMu2_phi,genA1_phi); deta1 = selMu2_eta - genA1_eta;}
							if(j==3){ dphi1 = My_dPhi(selMu3_phi,genA1_phi); deta1 = selMu3_eta - genA1_eta;}

											dR1 = sqrt(dphi1*dphi1+deta1*deta1);
											dR_A1->Fill(dR1);
											if(dR1<0.5) match_mu++;
										}
										if(match_mu>=2) {
											count_rec_A1[n][m]++;
											num_1D_A1_LXY->Fill(genA1_Lxy_rdet);
											num_1D_A1_LZ->Fill(genA1_Lz_rdet);
											double numpt = sqrt(genA1_px*genA1_px + genA1_py*genA1_py);
											num_1D_A1_pT->Fill(numpt);
}

									}
}
}
}
}

} //dPhi loop
}
///Test loop

			if(is4GenMu8==true){
				Float_t dphi_gD = My_dPhi(genA1_phi,genA0_phi);
				//if(fabs(dphi_gD)>2.5){ 
					for(int n=0;n<20;n++){
						if(fabs(genA0_Lz_rdet)>bin_edges_Lz[n] && fabs(genA0_Lz_rdet)<bin_edges_Lz[n+1]){
							for(int m=0;m<40;m++){
								if(genA0_Lxy_rdet>bin_edges[m] && genA0_Lxy_rdet<bin_edges[m+1]){
									
									npatm = 0;
									if(selMu0_eta != -100) npatm++;
									if(selMu1_eta != -100) npatm++;
									if(selMu2_eta != -100) npatm++;
									if(selMu3_eta != -100) npatm++;
									if(npatm>=2 && is2SelMu8){
										Float_t dR1=0.0;
										Float_t dphi1=0.0;
										Float_t deta1=0.0;

										Int_t match_mu=0;
										for(int j=0;j<npatm;j++){

								if(j==0){ dphi1 = My_dPhi(selMu0_phi,genA0_phi); deta1 = selMu0_eta - genA0_eta;}
								if(j==1){ dphi1 = My_dPhi(selMu1_phi,genA0_phi); deta1 = selMu1_eta - genA0_eta;}
								if(j==2){ dphi1 = My_dPhi(selMu2_phi,genA0_phi); deta1 = selMu2_eta - genA0_eta;}
								if(j==3){ dphi1 = My_dPhi(selMu3_phi,genA0_phi); deta1 = selMu3_eta - genA0_eta;}

											dR1 = sqrt(dphi1*dphi1+deta1*deta1);
											//if(dR1<0.5) match_mu++;
											 match_mu++;
											 dR_vs_dPhi->Fill(dR1, dphi_gD);
										dR_vs_pt->Fill(dR1, sqrt(genA0_px*genA0_px + genA0_py*genA0_py));
										}
										if(match_mu>=2)   {
											dR_vs_dLxy->Fill(dR1, genA0_Lxy_rdet);
											dPhi_vs_dLxy->Fill(dphi_gD, genA0_Lxy_rdet);

											dR_vs_dLz->Fill(dR1, genA0_Lz_rdet);
											dPhi_vs_dLz->Fill(dphi_gD, genA0_Lz_rdet);
											
											pt_vs_dPhi->Fill(sqrt(genA0_px*genA0_px + genA0_py*genA0_py),dphi_gD);

											pt_vs_dLxy->Fill(sqrt(genA0_px*genA0_px + genA0_py*genA0_py),genA0_Lxy_rdet);
											pt_vs_dLz->Fill(sqrt(genA0_px*genA0_px + genA0_py*genA0_py), genA0_Lz_rdet);
}
									}
								}
							}
						}
					}


					for(int n=0;n<20;n++){
						if(fabs(genA1_Lz_rdet)>bin_edges_Lz[n] && fabs(genA1_Lz_rdet)<bin_edges_Lz[n+1]){

							for(int m=0;m<40;m++){
								if(genA1_Lxy_rdet>bin_edges[m] && genA1_Lxy_rdet<bin_edges[m+1]){

									npatm = 0;
									if(selMu0_eta != -100) npatm++;
									if(selMu1_eta != -100) npatm++;
									if(selMu2_eta != -100) npatm++;
									if(selMu3_eta != -100) npatm++;

									if(npatm>=2 && is2SelMu8){
										Float_t dR1=0.0;
										Float_t dphi1=0.0;
										Float_t deta1=0.0;

										Int_t match_mu=0;
										for(int j=0;j<npatm;j++){	

							if(j==0){ dphi1 = My_dPhi(selMu0_phi,genA1_phi); deta1 = selMu0_eta - genA1_eta;}
							if(j==1){ dphi1 = My_dPhi(selMu1_phi,genA1_phi); deta1 = selMu1_eta - genA1_eta;}
							if(j==2){ dphi1 = My_dPhi(selMu2_phi,genA1_phi); deta1 = selMu2_eta - genA1_eta;}
							if(j==3){ dphi1 = My_dPhi(selMu3_phi,genA1_phi); deta1 = selMu3_eta - genA1_eta;}

											dR1 = sqrt(dphi1*dphi1+deta1*deta1);
											//if(dR1<0.5) match_mu++;
											match_mu++;
											dR_vs_dPhi->Fill(dR1, dphi_gD);
											dR_vs_pt->Fill(dR1, sqrt(genA1_px*genA1_px + genA1_py*genA1_py));
										
										}
										if(match_mu>=2) {
											dR_vs_dLxy->Fill(dR1, genA1_Lxy_rdet);
											dPhi_vs_dLxy->Fill(dphi_gD, genA1_Lxy_rdet);

											dR_vs_dLz->Fill(dR1, genA1_Lz_rdet);
											dPhi_vs_dLz->Fill(dphi_gD, genA1_Lz_rdet);}
											pt_vs_dPhi->Fill(sqrt(genA1_px*genA1_px + genA1_py*genA1_py) ,dphi_gD);
											pt_vs_dLxy->Fill(sqrt(genA1_px*genA1_px + genA1_py*genA1_py),genA1_Lxy_rdet);
											pt_vs_dLz->Fill(sqrt(genA1_px*genA1_px + genA1_py*genA1_py), genA1_Lz_rdet);

							
							}
}
}
}
}

//} //dPhi loop
}

//End Test loop


} //closing for loop
myfile->Close();
}//closing while loop
}//closing method


void makePlots(){

	TH2F *den_2D_A0 = new TH2F("den_2D_A0","den_2D_A0",20,0,80,40,0.0,80.0);
	TH2F *num_2D_A0 = new TH2F("num_2D_A0","num_2D_A0",20,0,80,40,0.0,80.0);

	TH2F *eff_2D_A0 = new TH2F("eff_2D_A0","eff_2D_A0",20,0,80,40,0.0,80.0);
	TH2F *eff_2D_A1 = new TH2F("eff_2D_A1","eff_2D_A1",20,0,80,40,0.0,80.0);


	for(int k=0;k<20;k++){
		for(int j=0;j<40;j++){

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

	TCanvas *effxy = new TCanvas("effxy", "effxy", 700, 500);
	gr1 = new TGraphAsymmErrors(num_1D_A0_LXY, den_1D_A0_LXY);
	gr1->SetTitle("");
	gr1->GetYaxis()->SetTitle("Efficiency");
	gr1->GetXaxis()->SetTitle("L_{XY} [cm]");
	gr1->SetMarkerColor(kRed);
	gr1->SetLineColor(kRed);
	gr1->SetMarkerStyle(21);
	gr1->Draw("ALP");
	
	gr0 = new TGraphAsymmErrors(num_1D_A1_LXY, den_1D_A1_LXY);
	gr0->SetMarkerColor(kBlue);
	gr0->SetLineColor(kBlue);
	gr0->SetMarkerStyle(21);
	gr0->Draw("same");

	TLegend *leg = new TLegend(0.1695402,0.1458774,0.2816092,0.4460888);
	leg->SetBorderSize(0);
	leg->SetFillColor(0);
	leg->SetTextSize(0.045);
	leg->AddEntry(gr1,"#gamma_{D1}","L");
	leg->AddEntry(gr0,"#gamma_{D2}","L");
	leg->Draw("same");

	effxy->SaveAs("Efficiency_1D_LXY.pdf");
	//effxy->SaveAs("Efficiency_1D_LXY.C");

	TCanvas *effz2 = new TCanvas("effz2", "effz2", 700, 500);
	gr2 = new TGraphAsymmErrors(num_1D_A0_LZ, den_1D_A0_LZ);
	gr2->SetMarkerColor(kRed);
	gr2->SetLineColor(kRed);
	gr2->SetTitle("");
	gr2->GetYaxis()->SetTitle("Efficiency");
	gr2->GetXaxis()->SetTitle("L_{Z} [cm]");
	gr2->SetMarkerStyle(21);
	gr2->Draw("ALP");

	gr3 = new TGraphAsymmErrors(num_1D_A1_LZ, den_1D_A1_LZ);
	gr3->SetMarkerColor(kBlue);
	gr3->SetLineColor(kBlue);
	gr3->SetMarkerStyle(21);
	gr3->Draw("same");

	leg->Draw("same");

	effz2->SaveAs("Efficiency_1D_Lz.pdf");

	TCanvas *effpt = new TCanvas("effpt", "effpt", 700, 500);
	gr_eff = new TGraphAsymmErrors(num_1D_A0_pT, den_1D_A0_pT);
	gr_eff->SetMarkerColor(kRed);
	gr_eff->SetLineColor(kRed);
	gr_eff->SetTitle("");
	gr_eff->GetYaxis()->SetTitle("Efficiency");
	gr_eff->GetXaxis()->SetTitle("p_{T} [GeV]");
	gr_eff->SetMarkerStyle(21);
	gr_eff->Draw("ALP");

	gr_eff2 = new TGraphAsymmErrors(num_1D_A1_pT, den_1D_A1_pT);
	gr_eff2->SetMarkerColor(kBlue);
	gr_eff2->SetLineColor(kBlue);
	gr_eff2->SetMarkerStyle(21);
	gr_eff2->Draw("same");

	leg->Draw("same");
	effpt->SaveAs("Efficiency_vs_Gen_pT.pdf");


/*
	TCanvas *effxy0 = new TCanvas("effxy0", "effxy0", 700, 500);
	gr4 = new TGraphAsymmErrors(num_1D_A1_LXY, den_1D_A1_LXY);
	gr4->SetTitle("1D Efficiency #gamma_{D2} L_{XY}");
	gr4->GetYaxis()->SetTitle("Efficiency");
	gr4->GetXaxis()->SetTitle("L_{XY} [cm]");
	gr4->SetMarkerColor(kBlue);
	gr4->SetMarkerStyle(21);
	gr4->Draw("ALP");

	TCanvas *effz = new TCanvas("effz", "effz", 700, 500);
	gr5 = new TGraphAsymmErrors(num_1D_A1_LZ, den_1D_A1_LZ);
	gr5->SetTitle("1D Efficiency #gamma_{D2} L_{Z}");
	gr5->SetMarkerColor(4);
	gr5->SetMarkerStyle(21);
	gr5->Draw("ALP");

	TCanvas *effxy3 = new TCanvas("effxy3", "effxy3", 700, 500);
	gr6 = new TGraphAsymmErrors(num_1D_A0_LXY, den_1D_A0_LXY);
	gr6->SetTitle("1D Efficiency #gamma_{D1} L_{XY}");
	gr6->SetMarkerColor(4);
	gr6->SetMarkerStyle(21);
	gr6->Draw("ALP");

	TCanvas *effz3 = new TCanvas("effz3", "effz3", 700, 500);
	gr7 = new TGraphAsymmErrors(num_1D_A0_LZ, den_1D_A0_LZ);
	gr7->SetTitle("1D Efficiency #gamma_{D1} L_{Z}");
	gr7->SetMarkerColor(4);
	gr7->SetMarkerStyle(21);
	gr7->Draw("ALP");
*/

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

	c->SaveAs("eff_2D_LxyLz_A0_0275.pdf","recreate");
	//I am not quite sure what this did...    
	//if(l==0) c->SaveAs("eff_2D_LxyLz_A0_ct05.pdf","recreate");




	TCanvas *c1 = new TCanvas("c1","c1",700,500);
	c1->SetRightMargin(0.15);
	eff_2D_A1->GetYaxis()->SetTitle("#gamma_{D2} Lxy [cm]");
	eff_2D_A1->GetXaxis()->SetTitle("|#gamma_{D2} Lz| [cm]");
	eff_2D_A1->GetZaxis()->SetTitle("Eff_{rec}/accep_{gen}");
	gStyle->SetOptStat(0);
	eff_2D_A1->Draw("COLZ");
	c1->SaveAs("eff_2D_LxyLz_A1_0275.pdf","recreate");
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

*/

create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f//");
create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_100_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_300_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");


/*
//create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_000_13TeV/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
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
