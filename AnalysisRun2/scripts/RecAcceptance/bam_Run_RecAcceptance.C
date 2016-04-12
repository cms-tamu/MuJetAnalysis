#include <iostream>
using namespace std;
#include <algorithm>    // std::max
#include <stdlib.h>
//============= Global Variables ===========================//

vector<double> mGammaD_0250_eff;
vector<double> mGammaD_0275_eff;
vector<double> mGammaD_0300_eff;
vector<double> mGammaD_2000_eff;
vector<double> mGammaD_8500_eff;

vector<double> mGammaD_0250_eff_uncert;
vector<double> mGammaD_0275_eff_uncert;
vector<double> mGammaD_0300_eff_uncert;
vector<double> mGammaD_2000_eff_uncert;
vector<double> mGammaD_8500_eff_uncert;

vector<double> mGammaD_0250_cT;
vector<double> mGammaD_0275_cT;
vector<double> mGammaD_0300_cT;
vector<double> mGammaD_2000_cT;
vector<double> mGammaD_8500_cT;

vector<double> cT_000_mGammaD;
vector<double> cT_005_mGammaD;
vector<double> cT_010_mGammaD;
vector<double> cT_020_mGammaD;
vector<double> cT_050_mGammaD;
vector<double> cT_100_mGammaD;
vector<double> cT_200_mGammaD;
vector<double> cT_300_mGammaD;
vector<double> cT_500_mGammaD;
vector<double> cT_1000_mGammaD;
vector<double> cT_2000_mGammaD;

vector<double> eRec_cT_000;
vector<double> eRec_cT_005;
vector<double> eRec_cT_010;
vector<double> eRec_cT_020;
vector<double> eRec_cT_050;
vector<double> eRec_cT_100;
vector<double> eRec_cT_200;
vector<double> eRec_cT_300;
vector<double> eRec_cT_500;
vector<double> eRec_cT_1000;
vector<double> eRec_cT_2000;

vector<double> eRec_cT_000_uncert;
vector<double> eRec_cT_005_uncert;
vector<double> eRec_cT_010_uncert;
vector<double> eRec_cT_020_uncert;
vector<double> eRec_cT_050_uncert;
vector<double> eRec_cT_100_uncert;
vector<double> eRec_cT_200_uncert;
vector<double> eRec_cT_300_uncert;
vector<double> eRec_cT_500_uncert;
vector<double> eRec_cT_1000_uncert;
vector<double> eRec_cT_2000_uncert;

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

void bam_RecAcceptance(TString fileName){
//cout << "Running on file: " << fileName << endl;
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

			ev_all++;

			//  ===========   GEN LEVEL information  ==============//
			//if(is4GenMu8){
				ev_4gmlxylzcut++;
			//}
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

	//Fill ratio reco/gen vectors to be plotted  


	double cT_double; 
	double mass_double;
	if(mass_string == "0250") mass_double = 0.25;
	if(mass_string == "0275") mass_double = 0.275;
	if(mass_string == "0300") mass_double = 0.30;
	if(mass_string == "2000") mass_double = 2.0;
	if(mass_string == "8500") mass_double = 8.5;


	if(cT_string == "000_") {
		cT_double = 0;
		eRec_cT_000.push_back(ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut));
		eRec_cT_000_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut)));
		cT_000_mGammaD.push_back(mass_double);
	}
	if(cT_string == "005_") {
		cT_double = 0.05;
		eRec_cT_005.push_back(ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut));
		eRec_cT_005_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut)));
		cT_005_mGammaD.push_back(mass_double);
	}
	if(cT_string == "010_") {
		cT_double = 0.1;
		eRec_cT_010.push_back(ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut));
		eRec_cT_010_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut)));
		cT_010_mGammaD.push_back(mass_double);
	}
	if(cT_string == "020_"){ 
		cT_double = 0.2;
		eRec_cT_020.push_back(ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut));
		eRec_cT_020_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut)));
		cT_020_mGammaD.push_back(mass_double);
	}
	if(cT_string == "050_"){ cT_double = 0.5;
		eRec_cT_050.push_back(ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut));
		eRec_cT_050_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut)));
		cT_050_mGammaD.push_back(mass_double);
	}
	if(cT_string == "100_"){ cT_double = 1.0;
		eRec_cT_100.push_back(ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut));
		eRec_cT_100_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut)));
		cT_100_mGammaD.push_back(mass_double);
	}
	if(cT_string == "200_"){ cT_double = 2.0;
		eRec_cT_200.push_back(ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut));
		eRec_cT_200_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut)));
		cT_200_mGammaD.push_back(mass_double);
	}
	if(cT_string == "300_"){ cT_double = 3.0;
		eRec_cT_300.push_back(ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut));
		eRec_cT_300_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut)));
		cT_300_mGammaD.push_back(mass_double);
	}
	if(cT_string == "500_"){ 
		cT_double = 5.0;
		eRec_cT_500.push_back(ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut));
		eRec_cT_500_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut)));
		cT_500_mGammaD.push_back(mass_double);
	}
	if(cT_string == "1000"){
		cT_double = 10.0;
		eRec_cT_1000.push_back(ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut));
		eRec_cT_1000_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut)));
		cT_1000_mGammaD.push_back(mass_double);
	}
	if(cT_string == "2000"){
		cT_double = 20.0;
		eRec_cT_2000.push_back(ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut));
		eRec_cT_2000_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut)));
		cT_2000_mGammaD.push_back(mass_double);
	}


cout << "GeV, cT, e_rec" << endl;

	if(mass_string == "0250"){
		mGammaD_0250_eff.push_back(ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut));  
		mGammaD_0250_eff_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut)));  
		mGammaD_0250_cT.push_back(cT_double);
	cout << "0.25, " << cT_double << ", " << ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut) << endl;
	}
	if(mass_string == "0275"){
		mGammaD_0275_eff.push_back(ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut));  
		mGammaD_0275_eff_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut)));  
		mGammaD_0275_cT.push_back(cT_double);  
		         cout << "0.275, " << cT_double << ", " << ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut) << endl;
	}
	if(mass_string == "0300"){
		mGammaD_0300_eff.push_back(ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut));  
		mGammaD_0300_eff_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut)));  
		mGammaD_0300_cT.push_back(cT_double);  
		         cout << "0.30, " << cT_double << ", " << ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut) << endl;
	}
	if(mass_string == "2000"){
		mGammaD_2000_eff.push_back(ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut));  
		mGammaD_2000_eff_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut)));  
		mGammaD_2000_cT.push_back(cT_double);  
		         cout << "2.0, " << cT_double << ", " << ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut) << endl;
	}
	if(mass_string == "8500"){
		mGammaD_8500_eff.push_back(ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut));  
		mGammaD_8500_eff_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut)));  
		mGammaD_8500_cT.push_back(cT_double);  
		         cout << "8.5, " << cT_double << ", " << ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut) << endl;
	}
}

void makePlot(){
//	for(int i = 0; i < cT_000_mGammaD.size(); i++){
//		cout << "Plot Details: " << cT_000_mGammaD[i] << ", " << eRec_cT_000[i] << ", " <<  eRec_cT_000_uncert[i] << endl;
//	}

	vector<double> null_000;
	vector<double> null_005;
	vector<double> null_010;
	vector<double> null_020;
	vector<double> null_050;
	vector<double> null_100;
	vector<double> null_200;
	vector<double> null_300;
	vector<double> null_500;
	vector<double> null_1000;
	vector<double> null_2000;

	for(int i=0; i < eRec_cT_000.size(); i++) null_000.push_back(0);
	for(int i=0; i < eRec_cT_005.size(); i++) null_005.push_back(0);
	for(int i=0; i < eRec_cT_010.size(); i++) null_010.push_back(0);
	for(int i=0; i < eRec_cT_020.size(); i++) null_020.push_back(0);
	for(int i=0; i < eRec_cT_050.size(); i++) null_050.push_back(0);
	for(int i=0; i < eRec_cT_100.size(); i++) null_100.push_back(0);
	for(int i=0; i < eRec_cT_200.size(); i++) null_200.push_back(0);
	for(int i=0; i < eRec_cT_300.size(); i++) null_300.push_back(0);
	for(int i=0; i < eRec_cT_500.size(); i++) null_500.push_back(0);
	for(int i=0; i < eRec_cT_1000.size(); i++) null_1000.push_back(0);
	for(int i=0; i < eRec_cT_2000.size(); i++) null_2000.push_back(0);

	int size_000 = eRec_cT_000.size();
	int size_005 = eRec_cT_005.size();
	int size_010 = eRec_cT_010.size();
	int size_020 = eRec_cT_020.size();
	int size_050 = eRec_cT_050.size();
	int size_100 = eRec_cT_100.size();
	int size_200 = eRec_cT_200.size();
	int size_300 = eRec_cT_300.size();
	int size_500 = eRec_cT_500.size();
	int size_1000 = eRec_cT_1000.size();
	int size_2000 = eRec_cT_2000.size();


//cout << "size_000: " << size_000 << endl;

	double* array_eRec_cT_000  = &eRec_cT_000[0];
	double* array_eRec_cT_005  = &eRec_cT_005[0];
	double* array_eRec_cT_010  = &eRec_cT_010[0];
	double* array_eRec_cT_020  = &eRec_cT_020[0];
	double* array_eRec_cT_050  = &eRec_cT_050[0];
	double* array_eRec_cT_100  = &eRec_cT_100[0];
	double* array_eRec_cT_200  = &eRec_cT_200[0];
	double* array_eRec_cT_300  = &eRec_cT_300[0];
	double* array_eRec_cT_500  = &eRec_cT_500[0];
	double* array_eRec_cT_1000  = &eRec_cT_1000[0];
	double* array_eRec_cT_2000  = &eRec_cT_2000[0];

	double* array_eRec_cT_000_uncert  = &eRec_cT_000_uncert[0];
	double* array_eRec_cT_005_uncert  = &eRec_cT_005_uncert[0];
	double* array_eRec_cT_010_uncert  = &eRec_cT_010_uncert[0];
	double* array_eRec_cT_020_uncert  = &eRec_cT_020_uncert[0];
	double* array_eRec_cT_050_uncert  = &eRec_cT_050_uncert[0];
	double* array_eRec_cT_100_uncert  = &eRec_cT_100_uncert[0];
	double* array_eRec_cT_200_uncert  = &eRec_cT_200_uncert[0];
	double* array_eRec_cT_300_uncert  = &eRec_cT_300_uncert[0];
	double* array_eRec_cT_500_uncert  = &eRec_cT_500_uncert[0];
	double* array_eRec_cT_1000_uncert  = &eRec_cT_1000_uncert[0];
	double* array_eRec_cT_2000_uncert  = &eRec_cT_2000_uncert[0];

	double* array_cT_000_mGammaD = &cT_000_mGammaD[0]; 
	double* array_cT_005_mGammaD = &cT_005_mGammaD[0];
	double* array_cT_010_mGammaD = &cT_010_mGammaD[0];
	double* array_cT_020_mGammaD = &cT_020_mGammaD[0];
	double* array_cT_050_mGammaD = &cT_050_mGammaD[0];
	double* array_cT_100_mGammaD = &cT_100_mGammaD[0];
	double* array_cT_200_mGammaD = &cT_200_mGammaD[0];
	double* array_cT_300_mGammaD = &cT_300_mGammaD[0];
	double* array_cT_500_mGammaD = &cT_500_mGammaD[0];
	double* array_cT_1000_mGammaD = &cT_1000_mGammaD[0];
	double* array_cT_2000_mGammaD = &cT_2000_mGammaD[0];

	double* array_null_000 = &null_000[0]; 
	double* array_null_005 = &null_005[0];
	double* array_null_010 = &null_010[0];
	double* array_null_020 = &null_020[0];
	double* array_null_050 = &null_050[0];
	double* array_null_100 = &null_100[0];
	double* array_null_200 = &null_200[0];
	double* array_null_300 = &null_300[0];
	double* array_null_500 = &null_500[0];
	double* array_null_1000 = &null_1000[0];
	double* array_null_2000 = &null_2000[0];
/*
cout << "size_000                   : " << size_000 << endl;
cout << "array_eRec_cT_000[0]       :" << array_eRec_cT_000[0] << endl;
cout << "array_null_000[0]          : " << array_null_000[0] << endl;
cout << "array_eRec_cT_000_uncert[0]: " << array_eRec_cT_000_uncert[0] << endl;
cout << "array_cT_000_mGammaD[0]    : " << array_cT_000_mGammaD[0] << endl;

cout << "size_000, array_cT_000_mGammaD, array_eRec_cT_000, array_null_000, array_eRec_cT_000_uncert: " << size_000 << ", " << array_cT_000_mGammaD[0] << ", " << array_eRec_cT_000[0] << ", " << array_null_000[0] << ", " << array_eRec_cT_000_uncert[0] << endl;
*/
	TGraphErrors *gr_eRec_000 = new TGraphErrors(size_000, array_cT_000_mGammaD, array_eRec_cT_000, array_null_000, array_eRec_cT_000_uncert);
	TGraphErrors *gr_eRec_005 = new TGraphErrors(size_005, array_cT_005_mGammaD, array_eRec_cT_005, array_null_005, array_eRec_cT_005_uncert);
	TGraphErrors *gr_eRec_010 = new TGraphErrors(size_010, array_cT_010_mGammaD, array_eRec_cT_010, array_null_010, array_eRec_cT_010_uncert);
	TGraphErrors *gr_eRec_020 = new TGraphErrors(size_020, array_cT_020_mGammaD, array_eRec_cT_020, array_null_020, array_eRec_cT_020_uncert);
	TGraphErrors *gr_eRec_050 = new TGraphErrors(size_050, array_cT_050_mGammaD, array_eRec_cT_050, array_null_050, array_eRec_cT_050_uncert);
	TGraphErrors *gr_eRec_100 = new TGraphErrors(size_100, array_cT_100_mGammaD, array_eRec_cT_100, array_null_100, array_eRec_cT_100_uncert);
	TGraphErrors *gr_eRec_200 = new TGraphErrors(size_200, array_cT_200_mGammaD, array_eRec_cT_200, array_null_200, array_eRec_cT_200_uncert);
	TGraphErrors *gr_eRec_300 = new TGraphErrors(size_300, array_cT_300_mGammaD, array_eRec_cT_300, array_null_300, array_eRec_cT_300_uncert);
	TGraphErrors *gr_eRec_500 = new TGraphErrors(size_500, array_cT_500_mGammaD, array_eRec_cT_500, array_null_500, array_eRec_cT_500_uncert);
	TGraphErrors *gr_eRec_1000 = new TGraphErrors(size_1000, array_cT_1000_mGammaD, array_eRec_cT_1000, array_null_1000, array_eRec_cT_1000_uncert);
	TGraphErrors *gr_eRec_2000 = new TGraphErrors(size_2000, array_cT_2000_mGammaD, array_eRec_cT_2000, array_null_2000, array_eRec_cT_2000_uncert);

	gr_eRec_000->Sort(); 
	gr_eRec_005->Sort();
	gr_eRec_010->Sort();
	gr_eRec_020->Sort();
	gr_eRec_050->Sort();
	gr_eRec_100->Sort();
	gr_eRec_200->Sort();
	gr_eRec_300->Sort();
	gr_eRec_500->Sort();
	gr_eRec_1000->Sort();
	gr_eRec_2000->Sort();

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

	vector<double> null_2000m;
	for(int i=0; i < mGammaD_2000_cT.size(); i++){
		null_2000m.push_back(0);
	}
	double* array_null_2000m		      = &null_2000m[0];
	double* array_mGammaD_2000_eff        = &mGammaD_2000_eff[0];
	double* array_mGammaD_2000_eff_uncert = &mGammaD_2000_eff_uncert[0];
	double* array_mGammaD_2000_cT	      = &mGammaD_2000_cT[0];
	int size_2000m = null_2000m.size();
	TGraphErrors *gr_eff_mD_2000 = new TGraphErrors(size_2000m,array_mGammaD_2000_cT,array_mGammaD_2000_eff,array_null_2000m,array_mGammaD_2000_eff_uncert);

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

	TLegend *leg = new TLegend(0.5387931,0.5813953,0.887931,0.8816068);
	leg->SetBorderSize(0);
	leg->SetFillColor(0);
	leg->SetTextSize(0.045);
	leg->AddEntry(gr_eff_mD_0250,"m_{#gamma D}=0.250 GeV","PL");
	leg->AddEntry(gr_eff_mD_0275,"m_{#gamma D}=0.275 GeV","PL");
	leg->AddEntry(gr_eff_mD_0300,"m_{#gamma D}=0.300 GeV","PL");
	leg->AddEntry(gr_eff_mD_2000,"m_{#gamma D}=2.000 GeV","PL");
	leg->AddEntry(gr_eff_mD_8500,"m_{#gamma D}=8.500 GeV","PL");

	TLegend *leg2 = new TLegend(0.158046,0.5369979,0.5071839,0.8372093);
	leg2->SetBorderSize(0);
	leg2->SetFillColor(0);
	leg2->SetTextSize(0.045);
	leg2->AddEntry(gr_eRec_000,"c#Tau=0.00 mm","PL");
	leg2->AddEntry(gr_eRec_005,"c#Tau=0.05 mm","PL");
	leg2->AddEntry(gr_eRec_010,"c#Tau=0.10 mm","PL");
	leg2->AddEntry(gr_eRec_020,"c#Tau=0.20 mm","PL");
	leg2->AddEntry(gr_eRec_050,"c#Tau=0.50 mm","PL");
	leg2->AddEntry(gr_eRec_100,"c#Tau=1.00 mm","PL");
	leg2->AddEntry(gr_eRec_200,"c#Tau=2.00 mm","PL");
	leg2->AddEntry(gr_eRec_300,"c#Tau=3.00 mm","PL");
	leg2->AddEntry(gr_eRec_500,"c#Tau=5.00 mm","PL");

	TH2F *dummy3 = new TH2F("dummy3","dummy3",400,-0.2,20.2,100,0.0,0.2);
	TCanvas *c = new TCanvas("c","c",700,500);
	dummy3->GetXaxis()->SetTitle("c#tau [mm]");
	dummy3->GetYaxis()->SetTitle("#epsilon_{rec} = N_{rec}/N_{tot}");
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
	c->SaveAs("acceptance_cT.pdf","recreate");
	c->SaveAs("acceptance_cT.C", "recreate");

	TH2F *dummy4 = new TH2F("dummy4","dummy4",178,-0.2,8.7,100,0.0,0.2);
	TCanvas *c2 = new TCanvas("c2","c2",700,500);
	dummy4->GetXaxis()->SetTitle("Mass [GeV]");
	dummy4->GetYaxis()->SetTitle("#epsilon_{rec} = N_{rec}/N_{tot}");
	gStyle->SetOptStat(0);
	dummy4->Draw();

	gr_eRec_000->SetLineWidth(1); 
	gr_eRec_005->SetLineWidth(1);
	gr_eRec_010->SetLineWidth(1);
	gr_eRec_020->SetLineWidth(1);
	gr_eRec_050->SetLineWidth(1);
	gr_eRec_100->SetLineWidth(1);
	gr_eRec_200->SetLineWidth(1);
	gr_eRec_300->SetLineWidth(1);
	gr_eRec_500->SetLineWidth(1);
	gr_eRec_1000->SetLineWidth(1);
	gr_eRec_2000->SetLineWidth(1);


	gr_eRec_000->SetMarkerSize(5);
	gr_eRec_005->SetMarkerSize(5);
	gr_eRec_010->SetMarkerSize(5);
	gr_eRec_020->SetMarkerSize(5);
	gr_eRec_050->SetMarkerSize(5);
	gr_eRec_100->SetMarkerSize(5);
	gr_eRec_200->SetMarkerSize(5);
	gr_eRec_300->SetMarkerSize(5);
	gr_eRec_500->SetMarkerSize(5);
	gr_eRec_1000->SetMarkerSize(5);
	gr_eRec_2000->SetMarkerSize(5);

	gr_eRec_000->SetMarkerStyle(7);
	gr_eRec_005->SetMarkerStyle(7);
	gr_eRec_010->SetMarkerStyle(7);
	gr_eRec_020->SetMarkerStyle(7);
	gr_eRec_050->SetMarkerStyle(7);
	gr_eRec_100->SetMarkerStyle(7);
	gr_eRec_200->SetMarkerStyle(7);
	gr_eRec_300->SetMarkerStyle(7);
	gr_eRec_500->SetMarkerStyle(7);
	gr_eRec_1000->SetMarkerStyle(7);
	gr_eRec_2000->SetMarkerStyle(7);

	gr_eRec_000->SetMarkerColor(1);
	gr_eRec_005->SetMarkerColor(2);
	gr_eRec_010->SetMarkerColor(3);
	gr_eRec_020->SetMarkerColor(4);
	gr_eRec_050->SetMarkerColor(6);
	gr_eRec_100->SetMarkerColor(7);
	gr_eRec_200->SetMarkerColor(8);
	gr_eRec_300->SetMarkerColor(9);
	gr_eRec_500->SetMarkerColor(kOrange);
	gr_eRec_500->SetMarkerColor(43);
	gr_eRec_500->SetMarkerColor(40);

	gr_eRec_000->SetLineColor(1);
	gr_eRec_005->SetLineColor(2);
	gr_eRec_010->SetLineColor(3);
	gr_eRec_020->SetLineColor(4);
	gr_eRec_050->SetLineColor(6);
	gr_eRec_100->SetLineColor(7);
	gr_eRec_200->SetLineColor(8);
	gr_eRec_300->SetLineColor(9);
	gr_eRec_500->SetLineColor(kOrange);
	gr_eRec_500->SetLineColor(43);
	gr_eRec_500->SetLineColor(40);

	gr_eRec_000->Draw("SAME PL");
	gr_eRec_005->Draw("SAME PL");
	gr_eRec_010->Draw("SAME PL");
	gr_eRec_020->Draw("SAME PL");
	gr_eRec_050->Draw("SAME PL");
	gr_eRec_100->Draw("SAME PL");
	gr_eRec_200->Draw("SAME PL");
	gr_eRec_300->Draw("SAME PL");
	gr_eRec_500->Draw("SAME PL");
	gr_eRec_1000->Draw("SAME PL");
	gr_eRec_2000->Draw("SAME PL");
	leg2->Draw("same");
	c2->SaveAs("acceptance_mass.pdf","recreate");
	c2->SaveAs("acceptance_mass.C", "recreate");

}

void bam_Run_RecAcceptance()
{
	//These cT's should be in order.
	bam_RecAcceptance("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	   bam_RecAcceptance("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	   bam_RecAcceptance("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	   bam_RecAcceptance("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	   bam_RecAcceptance("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	   bam_RecAcceptance("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_100_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	   bam_RecAcceptance("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	   bam_RecAcceptance("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_300_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	   bam_RecAcceptance("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
bam_RecAcceptance("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_1000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
bam_RecAcceptance("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_2000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");


	   bam_RecAcceptance("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f//");
	   bam_RecAcceptance("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	   bam_RecAcceptance("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	   bam_RecAcceptance("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	   bam_RecAcceptance("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	   bam_RecAcceptance("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_100_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	   bam_RecAcceptance("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	   bam_RecAcceptance("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_300_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	   bam_RecAcceptance("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
bam_RecAcceptance("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_1000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
bam_RecAcceptance("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_2000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");

	bam_RecAcceptance("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	bam_RecAcceptance("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	bam_RecAcceptance("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	bam_RecAcceptance("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	bam_RecAcceptance("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	bam_RecAcceptance("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_100_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	bam_RecAcceptance("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	bam_RecAcceptance("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_300_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	bam_RecAcceptance("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");

	bam_RecAcceptance("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	bam_RecAcceptance("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	bam_RecAcceptance("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	bam_RecAcceptance("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	bam_RecAcceptance("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	bam_RecAcceptance("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_100_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	bam_RecAcceptance("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	bam_RecAcceptance("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_300_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
bam_RecAcceptance("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");

	bam_RecAcceptance("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
	bam_RecAcceptance("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
	bam_RecAcceptance("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
	bam_RecAcceptance("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
	bam_RecAcceptance("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
	bam_RecAcceptance("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
	

	makePlot();
}     
