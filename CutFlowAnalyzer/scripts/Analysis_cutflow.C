#include <iostream>
using namespace std;
#include <algorithm>    // std::max

void addfiles(TChain *ch, const TString dirname=".", const TString ext=".root")
{
  TSystemDirectory dir(dirname, dirname);
  TList *files = dir.GetListOfFiles();
  if (files) {
    //std::cout << "Found files" << std::endl;
    TSystemFile *file;
    TString fname;
    TIter next(files);
    while ((file=(TSystemFile*)next())) {
      fname = file->GetName();
      // std::cout << "found fname " << fname << std::endl;
      if (!file->IsDirectory() && fname.BeginsWith(ext)) {
        // std::cout << "adding fname " << fname << std::endl;
        ch->Add(fname); // or call your function on this one file
      }
    }
  }
}

void Analysis_cutflow()
{
  bool verbose(false);
  TChain* chain = new TChain("dummy");
  TString dirname("/eos/uscms/store/user/dildick/DarkSUSY_mH_125_mGammaD_0850_cT_000_13TeV/Cutflow_Challenge_CRAB3_PAT_ANA/150803_155529/0000/");
  TString ext("out_ana_");

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

  Int_t ev_all[40]={0};
  Int_t ev_isVtxOK[40]={0};
  Int_t ev_is2MuJets[40]={0};
  Int_t ev_is2DiMuons[40]={0};
  Int_t ev_is2DiMuonsFittedVtxOK[40]={0};
  Int_t ev_isPixelHitOK[40]={0};
  Int_t ev_is2DiMuonsDzOK_FittedVtx[40]={0};
  Int_t ev_is2DiMuonsMassOK_FittedVtx[40]={0};
  Int_t ev_is2DiMuonsIsoTkOK_FittedVtx[40]={0};
  Int_t ev_isDiMuonHLTFired[40]={0};
  
  Int_t c1genm[40]={0};
  Int_t c2genm[40]={0};
  Int_t c3genm[40]={0};
  Int_t c4genm[40]={0};
  Int_t ev_4gmlxylzcut[40]={0};
  
  Int_t c1recm[40]={0};
  Int_t c2recm[40]={0};
  Int_t c3recm[40]={0};
  Int_t c4recm[40]={0};

  TObjArray *fileElements=chain->GetListOfFiles();
  TIter next(fileElements);
  TChainElement *chEl=0;
  while ((chEl=(TChainElement*)next())) {
    int p=0;
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
      
      ev_all[p]++;
      
      if(is1GenMu17) c1genm[p]++;
      if(is2GenMu8)  c2genm[p]++;
      if(is3GenMu8)  c3genm[p]++;
      if(is4GenMu8)  c4genm[p]++;
      
      if(is1SelMu17) c1recm[p]++;
      if(is2SelMu8)  c2recm[p]++;
      if(is3SelMu8)  c3recm[p]++;
      if(is4SelMu8)  c4recm[p]++;

      //  ===========   GEN LEVEL information  ==============//
      if(is4GenMu8){
      	if(fabs(genA0_Lxy)<4.4 && fabs(genA1_Lxy)<4.4 && fabs(genA0_Lz)<34.5 && fabs(genA1_Lz)<34.5){
      	  ev_4gmlxylzcut[p]++;
      	}
      }
      
      //  =============  Reco information ====================//
      if(is4SelMu8){        
        if(isVertexOK){
          ev_isVtxOK[p]++;
          if(is2MuJets){
            ev_is2MuJets[p]++;
            if(is2DiMuons){
              ev_is2DiMuons[p]++;
              if(is2DiMuonsFittedVtxOK){
                ev_is2DiMuonsFittedVtxOK[p]++;
                if( (diMuonC_m1_FittedVtx_hitpix==1||diMuonC_m2_FittedVtx_hitpix==1)&&(diMuonF_m1_FittedVtx_hitpix==1||diMuonF_m2_FittedVtx_hitpix==1) ){
                  ev_isPixelHitOK[p]++;  
                  if(is2DiMuonsDzOK_FittedVtx){
                    ev_is2DiMuonsDzOK_FittedVtx[p]++;
                    if(is2DiMuonsMassOK_FittedVtx){
                      ev_is2DiMuonsMassOK_FittedVtx[p]++;
                      if(is2DiMuonsIsoTkOK_FittedVtx){
                        ev_is2DiMuonsIsoTkOK_FittedVtx[p]++;
                        if(isDiMuonHLTFired){ 
                          ev_isDiMuonHLTFired[p]++;
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
  } // closing while loop

  std::cout<<" Events          "<<ev_all[0]<<std::endl;
  std::cout<<" ================ GEN MUONS ========================================= "<<std::endl;
  std::cout<<" 1GenMu17                       "<<c1genm[0]<<"   reff "<<c1genm[0]/(ev_all[0]*1.0)<<std::endl;
  std::cout<<" 2GenMu8                        "<<c2genm[0]<<"   reff  "<<c2genm[0]/(c1genm[0]*1.0)<<std::endl;
  std::cout<<" 3GenMu8                        "<<c3genm[0]<<"   reff  "<<c3genm[0]/(c2genm[0]*1.0)<<std::endl;
  std::cout<<" 4GenMu8                        "<<c4genm[0]<<"   reff  "<<c4genm[0]/(c3genm[0]*1.0)<<std::endl;
  std::cout<<" 4GenMu8 Lxy/Lz                 "<<ev_4gmlxylzcut[0]<<"   reff   "<<ev_4gmlxylzcut[0]/c4genm[0]<<std::endl;
  std::cout<<" ================ RECO MUONS ========================================= "<<std::endl;
  std::cout<<" 1RecMu17                       "<<c1recm[0]<<"  reff  "<<c1recm[0]/(ev_all[0]*1.0)<<std::endl;
  std::cout<<" 2RecMu8                        "<<c2recm[0]<<"  reff  "<<c2recm[0]/(c1recm[0]*1.0)<<std::endl;
  std::cout<<" 3RecMu8                        "<<c3recm[0]<<"  reff  "<<c3recm[0]/(c2recm[0]*1.0)<<std::endl;
  std::cout<<" 4RecMu8                        "<<c4recm[0]<<"  reff  "<<c4recm[0]/(c3recm[0]*1.0)<<std::endl;
  std::cout<<" ================ EVENT variables ================= "<<std::endl;
  std::cout<<" Events with VtxOK              "<<ev_isVtxOK[0]<<"    reff  "<<ev_isVtxOK[0]/(1.0*c4recm[0])<<std::endl;
  std::cout<<" Events with 2 muonjets         "<<ev_is2MuJets[0]<<"     reff  "<<ev_is2MuJets[0]/(1.0*ev_isVtxOK[0])<<std::endl;
  std::cout<<" Events with 2 Dimuons          "<<ev_is2DiMuons[0]<<"    reff  "<<ev_is2DiMuons[0]/(1.0*ev_is2MuJets[0])<<std::endl;
  std::cout<<" Events with 2DimVtxOK          "<<ev_is2DiMuonsFittedVtxOK[0]<<"    reff  "<<ev_is2DiMuonsFittedVtxOK[0]/(1.0*ev_is2DiMuons[0])<<std::endl;
  std::cout<<" Events with 2DimHitPix         "<<ev_isPixelHitOK[0]<<"     reff  "<<ev_isPixelHitOK[0]/(1.0*ev_is2DiMuonsFittedVtxOK[0])<<std::endl;
  std::cout<<" Events with 2DimDzOK           "<<ev_is2DiMuonsDzOK_FittedVtx[0]<<"   reff   "<<ev_is2DiMuonsDzOK_FittedVtx[0]/(1.0*ev_isPixelHitOK[0])<<std::endl;
  std::cout<<" Events with 2DimMassOK         "<<ev_is2DiMuonsMassOK_FittedVtx[0]<<"  reff   "<<ev_is2DiMuonsMassOK_FittedVtx[0]/(1.0*ev_is2DiMuonsDzOK_FittedVtx[0])<<endl;
  std::cout<<" Events with 2DimIsoOK          "<<ev_is2DiMuonsIsoTkOK_FittedVtx[0]<<"   reff   "<<ev_is2DiMuonsIsoTkOK_FittedVtx[0]/(1.0*ev_is2DiMuonsMassOK_FittedVtx[0])<<endl;
  std::cout<<" Events with 2DimHLT            "<<ev_isDiMuonHLTFired[0]<<"   reff   "<<ev_isDiMuonHLTFired[0]/(1.0*ev_is2DiMuonsIsoTkOK_FittedVtx[0])<<endl;
  std::cout<<" ratio reco/gen                 "<<ev_isDiMuonHLTFired[0]/(1.0*ev_4gmlxylzcut[0])<<" +/-  "<<sqrt( ((ev_isDiMuonHLTFired[0]/(1.0*ev_4gmlxylzcut[0]))*(1- (ev_isDiMuonHLTFired[0]/(1.0*ev_4gmlxylzcut[0])) ))/(1.0*ev_4gmlxylzcut[0]))<<std::endl;  
}
     
