#include <iostream>
using namespace std;
#include <algorithm>    // std::max

void Analysis_cutflow(){
  

  TFile *f[50];
  
  f[0] = new TFile("~/DarkSUSY_mH_125_mGammaD_0850_13TeV_cT_000_RAW2DIGI_L1Reco_RECO_v1_cutflow.root");
  
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


  for(int p=0;p<1;p++){
    
    
    f[p]->cd("cutFlowAnalyzer");
    
    TTree *t = (TTree*)f[p]->Get("cutFlowAnalyzer/Events");
    
    cout<<"  Events  "<<t->GetEntries()<<endl;
    
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

    Int_t nentries = t->GetEntries();
    
    for(int k=0;k<nentries;k++){
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
    }
    
    
    std::cout<<" Events          "<<t->GetEntries()<<std::endl;
    std::cout<<"  ================ GEN MUONS ========================================= "<<std::endl;
    std::cout<<" 1GenMu17                       "<<c1genm[p]<<"   reff "<<c1genm[p]/(t->GetEntries()*1.0)<<std::endl;
    std::cout<<" 2GenMu8                        "<<c2genm[p]<<"   reff  "<<c2genm[p]/(c1genm[p]*1.0)<<std::endl;
    std::cout<<" 3GenMu8                        "<<c3genm[p]<<"   reff  "<<c3genm[p]/(c2genm[p]*1.0)<<std::endl;
    std::cout<<" 4GenMu8                        "<<c4genm[p]<<"   reff  "<<c4genm[p]/(c3genm[p]*1.0)<<std::endl;
    std::cout<<" 4GenMu8 Lxy/Lz                 "<<ev_4gmlxylzcut[p]<<"   reff   "<<ev_4gmlxylzcut[p]/c4genm[p]<<std::endl;
    std::cout<<"  ================ RECO MUONS ========================================= "<<std::endl;
    std::cout<<" 1RecMu17                       "<<c1recm[p]<<"  reff  "<<c1recm[p]/(t->GetEntries()*1.0)<<std::endl;
    std::cout<<" 2RecMu8                        "<<c2recm[p]<<"  reff  "<<c2recm[p]/(c1recm[p]*1.0)<<std::endl;
    std::cout<<" 3RecMu8                        "<<c3recm[p]<<"  reff  "<<c3recm[p]/(c2recm[p]*1.0)<<std::endl;
    std::cout<<" 4RecMu8                        "<<c4recm[p]<<"  reff  "<<c4recm[p]/(c3recm[p]*1.0)<<std::endl;
    std::cout<<"  ================ EVENT variables ================= "<<std::endl;
    std::cout<<"  Events with VtxOK              "<<ev_isVtxOK[p]<<"    reff  "<<ev_isVtxOK[p]/(1.0*c4recm[p])<<std::endl;
    std::cout<<"  Events with 2 muonjets         "<<ev_is2MuJets[p]<<"     reff  "<<ev_is2MuJets[p]/(1.0*ev_isVtxOK[p])<<std::endl;
    std::cout<<"  Events with 2 Dimuons          "<<ev_is2DiMuons[p]<<"    reff  "<<ev_is2DiMuons[p]/(1.0*ev_is2MuJets[p])<<std::endl;
    std::cout<<"  Events with 2DimVtxOK          "<<ev_is2DiMuonsFittedVtxOK[p]<<"    reff  "<<ev_is2DiMuonsFittedVtxOK[p]/(1.0*ev_is2DiMuons[p])<<std::endl;
    std::cout<<"  Events with 2DimHitPix         "<<ev_isPixelHitOK[p]<<"     reff  "<<ev_isPixelHitOK[p]/(1.0*ev_is2DiMuonsFittedVtxOK[p])<<std::endl;
    std::cout<<"  Events with 2DimDzOK           "<<ev_is2DiMuonsDzOK_FittedVtx[p]<<"   reff   "<<ev_is2DiMuonsDzOK_FittedVtx[p]/(1.0*ev_isPixelHitOK[p])<<std::endl;
    std::cout<<"  Events with 2DimMassOK         "<<ev_is2DiMuonsMassOK_FittedVtx[p]<<"  reff   "<<ev_is2DiMuonsMassOK_FittedVtx[p]/(1.0*ev_is2DiMuonsDzOK_FittedVtx[p])<<endl;
    std::cout<<"  Events with 2DimIsoOK          "<<ev_is2DiMuonsIsoTkOK_FittedVtx[p]<<"   reff   "<<ev_is2DiMuonsIsoTkOK_FittedVtx[p]/(1.0*ev_is2DiMuonsMassOK_FittedVtx[p])<<endl;
    std::cout<<"  Events with 2DimHLT            "<<ev_isDiMuonHLTFired[p]<<"   reff   "<<ev_isDiMuonHLTFired[p]/(1.0*ev_is2DiMuonsIsoTkOK_FittedVtx[p])<<endl;
    std::cout<<"  ratio reco/gen                 "<<ev_isDiMuonHLTFired[p]/(1.0*ev_4gmlxylzcut[p])<<" +/-  "<<sqrt( ((ev_isDiMuonHLTFired[p]/(1.0*ev_4gmlxylzcut[p]))*(1- (ev_isDiMuonHLTFired[p]/(1.0*ev_4gmlxylzcut[p])) ))/(1.0*ev_4gmlxylzcut[p]))<<std::endl;
    
  }
}
     
