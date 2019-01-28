#include <iostream>
using namespace std;
#include <algorithm>    // std::max
#include <stdlib.h>
//============= Global Variables ===========================//

vector<double> mGammaD_0250_Lxy;
vector<double> mGammaD_0275_Lxy;
vector<double> mGammaD_0300_Lxy;
vector<double> mGammaD_2000_Lxy;
vector<double> mGammaD_8500_Lxy;

vector<double> mGammaD_0250_Lz;
vector<double> mGammaD_0275_Lz;
vector<double> mGammaD_0300_Lz;
vector<double> mGammaD_2000_Lz;
vector<double> mGammaD_8500_Lz;

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

void bam_Make_Lxy_Lz_Distributions(TString fileName){

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

		for(int k=0;k<t->GetEntries();k++){
			t->GetEntry(k);

			if(mass_string == "0250"){
				mGammaD_0250_Lxy.push_back(genA0_Lxy);
				mGammaD_0250_Lxy.push_back(genA1_Lxy);
				mGammaD_0250_Lz.push_back(genA0_Lz);
				mGammaD_0250_Lz.push_back(genA1_Lz);
			}
			if(mass_string == "0275"){
				mGammaD_0275_Lxy.push_back(genA0_Lxy);
				mGammaD_0275_Lxy.push_back(genA1_Lxy);
				mGammaD_0275_Lz.push_back(genA0_Lz);
				mGammaD_0275_Lz.push_back(genA1_Lz);
			}
			if(mass_string == "0300"){
				mGammaD_0300_Lxy.push_back(genA0_Lxy);
				mGammaD_0300_Lxy.push_back(genA1_Lxy);
				mGammaD_0300_Lz.push_back(genA0_Lz);
				mGammaD_0300_Lz.push_back(genA1_Lz);
			}
			if(mass_string == "2000"){
				mGammaD_2000_Lxy.push_back(genA0_Lxy);
				mGammaD_2000_Lxy.push_back(genA1_Lxy);
				mGammaD_2000_Lz.push_back(genA0_Lz);
				mGammaD_2000_Lz.push_back(genA1_Lz);
			}
			if(mass_string == "8500"){
				mGammaD_8500_Lxy.push_back(genA0_Lxy);
				mGammaD_8500_Lxy.push_back(genA1_Lxy);
				mGammaD_8500_Lz.push_back(genA0_Lz);
				mGammaD_8500_Lz.push_back(genA1_Lz);
			}



		} // closing for loop
		myfile->Close();
	} // closing while loop

}

void makePlots(){
	TH1D *Lxy_plot = new TH1D("Lxy_plot", "Lxy_plot", 800, 0, 80);
	TH1D *Lz_plot = new TH1D("Lz_plot", "Lz_plot", 800, 0, 80);

	TH1D *Lxy_temp_plot_0250 = new TH1D("Lxy_temp_plot_0250", "Lxy_temp_plot_0250", 800, 0, 80);
	TH1D *Lxy_temp_plot_0275 = new TH1D("Lxy_temp_plot_0275", "Lxy_temp_plot_0275", 800, 0, 80);
	TH1D *Lxy_temp_plot_0300 = new TH1D("Lxy_temp_plot_0300", "Lxy_temp_plot_0300", 800, 0, 80);
	TH1D *Lxy_temp_plot_2000 = new TH1D("Lxy_temp_plot_2000", "Lxy_temp_plot_2000", 800, 0, 80);
	TH1D *Lxy_temp_plot_8500 = new TH1D("Lxy_temp_plot_8500", "Lxy_temp_plot_8500", 800, 0, 80);

	TH1D *Lz_temp_plot_0250 = new TH1D("Lz_temp_plot_0250", "Lz_temp_plot_0250", 800, 0, 80);
	TH1D *Lz_temp_plot_0275 = new TH1D("Lz_temp_plot_0275", "Lz_temp_plot_0275", 800, 0, 80);
	TH1D *Lz_temp_plot_0300 = new TH1D("Lz_temp_plot_0300", "Lz_temp_plot_0300", 800, 0, 80);
	TH1D *Lz_temp_plot_2000 = new TH1D("Lz_temp_plot_2000", "Lz_temp_plot_2000", 800, 0, 80);
	TH1D *Lz_temp_plot_8500 = new TH1D("Lz_temp_plot_8500", "Lz_temp_plot_8500", 800, 0, 80);

	for(int i = 0; i < mGammaD_0250_Lxy.size(); i++){
		Lxy_temp_plot_0250->Fill(mGammaD_0250_Lxy[i]);
		Lz_temp_plot_0250->Fill(mGammaD_0250_Lz[i]);
	}
	for(int i = 0; i < mGammaD_0275_Lxy.size(); i++){
		Lxy_temp_plot_0275->Fill(mGammaD_0275_Lxy[i]);
		Lz_temp_plot_0275->Fill(mGammaD_0275_Lz[i]);
	}
	for(int i = 0; i < mGammaD_0300_Lxy.size(); i++){
		Lxy_temp_plot_0300->Fill(mGammaD_0300_Lxy[i]);
		Lz_temp_plot_0300->Fill(mGammaD_0300_Lz[i]);
	}
	for(int i = 0; i < mGammaD_2000_Lxy.size(); i++){
		Lxy_temp_plot_2000->Fill(mGammaD_2000_Lxy[i]);
		Lz_temp_plot_2000->Fill(mGammaD_2000_Lz[i]);
	}
	for(int i = 0; i < mGammaD_8500_Lxy.size(); i++){
		Lxy_temp_plot_8500->Fill(mGammaD_8500_Lxy[i]);
		Lz_temp_plot_8500->Fill(mGammaD_8500_Lz[i]);
	}

	TCanvas *c = new TCanvas("c","c",700,500);
	c->SetLogy();
	Lxy_temp_plot_8500->GetXaxis()->SetTitle("L_{XY} [cm]");
	Lxy_temp_plot_8500->GetYaxis()->SetTitle("Number of events/0.1 cm");
	Lxy_temp_plot_8500->SetTitle("L_{XY}");
	gStyle->SetOptStat(0);
	Lxy_temp_plot_8500->SetLineColor(6);
	Lxy_temp_plot_8500->Draw();

	Lxy_temp_plot_0250->SetLineColor(1);
	Lxy_temp_plot_0250->Draw("same");

	Lxy_temp_plot_0275->SetLineColor(2);
	Lxy_temp_plot_0275->Draw("same");

	Lxy_temp_plot_0300->SetLineColor(3);
	Lxy_temp_plot_0300->Draw("same");

	Lxy_temp_plot_2000->SetLineColor(4);
	Lxy_temp_plot_2000->Draw("same");

	TLegend *leg = new TLegend(0.5344828,0.5813953,0.8836207,0.8816068);
	//TLegend *leg = new TLegend(0.5,0.3,0.85,0.6);
	leg->SetBorderSize(0);
	leg->SetFillColor(0);
	leg->SetTextSize(0.045);
	leg->AddEntry(Lxy_temp_plot_0250,"m_{#gamma D}=0.250 GeV","L");
	leg->AddEntry(Lxy_temp_plot_0275,"m_{#gamma D}=0.275 GeV","L");
	leg->AddEntry(Lxy_temp_plot_0300,"m_{#gamma D}=0.300 GeV","L");
	leg->AddEntry(Lxy_temp_plot_2000,"m_{#gamma D}=2.000 GeV","L");
	leg->AddEntry(Lxy_temp_plot_8500,"m_{#gamma D}=8.500 GeV","L");

	leg->Draw("same");

	c->SaveAs("Lxy.pdf");

	TCanvas *c1 = new TCanvas("c1","c1",700,500);
	c1->SetLogy();
	Lz_temp_plot_8500->GetXaxis()->SetTitle("L_{Z} [cm]");
	Lz_temp_plot_8500->GetYaxis()->SetTitle("Number of events/0.1 cm");
	Lz_temp_plot_8500->SetTitle("L_{Z}");
	gStyle->SetOptStat(0);
	Lz_temp_plot_8500->SetLineColor(6);
	Lz_temp_plot_8500->Draw();

	Lz_temp_plot_0250->SetLineColor(1);
	Lz_temp_plot_0250->Draw("same");

	Lz_temp_plot_0275->SetLineColor(2);
	Lz_temp_plot_0275->Draw("same");

	Lz_temp_plot_0300->SetLineColor(3);
	Lz_temp_plot_0300->Draw("same");

	Lz_temp_plot_2000->SetLineColor(4);
	Lz_temp_plot_2000->Draw("same");

	leg->Draw("same");

	c1->SaveAs("Lz.pdf");


}

void bam_check_efficiencies()
{
	//These cT's should be in order.
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_100_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_300_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_1000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_2000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");


	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f//");
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_100_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_300_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_1000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_2000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");


bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_100_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_300_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");

	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_100_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_300_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");

	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
	bam_Make_Lxy_Lz_Distributions("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");


	makePlots();
}     
