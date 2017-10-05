#include <iostream>
using namespace std;
#include <algorithm>    // std::max
#include "../../AnalysisRun2/scripts/Helpers.h"

TString neutralino_string;
TString mass_string;
TString cT_string;
TString fileName;

void Analysis_cutflow_per_point(const std::vector<std::string>& dirNames)
{
  bool verbose(true);
  TChain* chain = new TChain("dummy");
  TString dirname("/eos/uscms/store/user/dildick/DarkSUSY_mH_125_mGammaD_0850_cT_000_13TeV/Cutflow_Challenge_CRAB3_PAT_ANA/150803_155529/0000/");
  TString ext("out_ana_");

  // add files to the chain
  decodeFileDarkSUSYNameMany(dirNames, neutralino_string, mass_string, cT_string);

  fileName = "DarkSUSY_mH_125_mN1_" + neutralino_string + "_mGammaD_" + mass_string + "_cT_" + cT_string;
  cout << "Tag name " << fileName << endl;

  // if (cT_string != "0p5") return;

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
  // Bool_t is2DiMuonsDzOK_FittedVtx;
  Bool_t isDiMuonHLTFired;
  Bool_t is2DiMuonsMassOK_FittedVtx;
  // Bool_t is2DiMuonsIsoTkOK_FittedVtx;
  Bool_t isVertexOK;
  Float_t diMuonC_FittedVtx_dz;
  Float_t diMuonF_FittedVtx_dz;
  Float_t diMuonC_IsoTk_FittedVtx;
  Float_t diMuonF_IsoTk_FittedVtx;

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

    // if  (ev_all > 60000) break;

    if (verbose) std::cout << "running on file " << chEl->GetTitle() << std::endl;
    TFile* myfile = new TFile(chEl->GetTitle());
    if (!myfile) {
      if (verbose) std::cout << "File " << chEl->GetTitle() << " does not exist" << std::endl;
      continue;
    }
    
    if (verbose) std::cout << "Loading directory cutFlowAnalyzer" << std::endl;
    myfile->cd("cutFlowAnalyzerPXBL3PXFL2");

    TTree *t = (TTree*)myfile->Get("cutFlowAnalyzerPXBL3PXFL2/Events");
    if (!t) {
      if (verbose) std::cout << "Tree cutFlowAnalyzerPXBL3PXFL2/Events does not exist" << std::endl;
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
    // t->SetBranchAddress("is2DiMuonsDzOK_FittedVtx",       &is2DiMuonsDzOK_FittedVtx);     
    t->SetBranchAddress("isDiMuonHLTFired",               &isDiMuonHLTFired);             
    t->SetBranchAddress("is2DiMuonsMassOK_FittedVtx",     &is2DiMuonsMassOK_FittedVtx);     
    // t->SetBranchAddress("is2DiMuonsIsoTkOK_FittedVtx",    &is2DiMuonsIsoTkOK_FittedVtx);    
    t->SetBranchAddress("isVertexOK",                     &isVertexOK);                        
    t->SetBranchAddress("isDiMuonHLTFired",              &isDiMuonHLTFired);                        

    t->SetBranchAddress("diMuonC_FittedVtx_dz", &diMuonC_FittedVtx_dz);
    t->SetBranchAddress("diMuonF_FittedVtx_dz", &diMuonF_FittedVtx_dz);
    t->SetBranchAddress("diMuonC_IsoTk_FittedVtx", &diMuonC_IsoTk_FittedVtx);
    t->SetBranchAddress("diMuonF_IsoTk_FittedVtx", &diMuonF_IsoTk_FittedVtx);

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

      //  ===========   GEN LEVEL information  ==============//
      if(is4GenMu8){
      	if(fabs(genA0_Lxy)<9.8 && fabs(genA1_Lxy)<9.8 && fabs(genA0_Lz)<46.5 && fabs(genA1_Lz)<46.5){
      	  ev_4gmlxylzcut++;
      	}
      }

      bool is2DiMuonsDzOK_FittedVtx = std::abs(diMuonC_FittedVtx_dz - diMuonF_FittedVtx_dz) < 0.1;
      bool is2DiMuonsIsoTkOK_FittedVtx = ( diMuonC_IsoTk_FittedVtx < 2.0 && diMuonF_IsoTk_FittedVtx < 2.0 );
      
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
		
		if( (diMuonC_m1_FittedVtx_hitpix_l3inc==1||diMuonC_m2_FittedVtx_hitpix_l3inc==1) && 
		    (diMuonF_m1_FittedVtx_hitpix_l3inc==1||diMuonF_m2_FittedVtx_hitpix_l3inc==1) ){
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
    delete t;
    delete myfile;
    cout << "Done running on events" << endl;
  } // closing while loop

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
}
     
void Analysis_cutflow()
{
  std::vector< std::vector<string> > DarkSUSY_mH_125_mGammaD_v;
  //readTextFileWithSamples("/home/dildick/DisplacedMuonJetAnalysis_2016/CMSSW_8_0_24/src/MuJetAnalysis/AnalysisRun2/scripts/darkSUSYSamples2016Ana.txt", DarkSUSY_mH_125_mGammaD_v);
  //printFileNames(DarkSUSY_mH_125_mGammaD_v);
  std::vector<string> s;
  // s.push_back("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_0_13TeV_20k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_0_13TeV_20k_PAT_ANA_V2_v1/170124_224445/0000/");

  s.push_back("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_5_13TeV_47k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_5_13TeV_47k_PAT_ANA_V2_v1/170128_025215/0000/");
  s.push_back("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_5_13TeV_48k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_5_13TeV_48k_PAT_ANA_V2_v1/170128_025151/0000/");
  s.push_back("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_5_13TeV_49k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_5_13TeV_49k_PAT_ANA_V2_v1/170128_025140/0000/");
  s.push_back("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_5_13TeV_51k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_5_13TeV_51k_PAT_ANA_V2_v1/170128_025127/0000/");
  s.push_back("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_5_13TeV_52k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_5_13TeV_52k_PAT_ANA_V2_v1/170128_025113/0000/");
  s.push_back("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_5_13TeV_53k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_5_13TeV_53k_PAT_ANA_V2_v1/170128_025100/0000/");


  DarkSUSY_mH_125_mGammaD_v.push_back(s);
  for(auto v: DarkSUSY_mH_125_mGammaD_v) Analysis_cutflow_per_point(v);
}

