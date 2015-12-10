#include <iostream>
using namespace std;
#include <algorithm>    // std::max

void Analysis_hitrecovery(){
  

  TFile *f[50];
  

  //==================  MD = 0.3 GeV ===================================================//
  TFile *f[0] = new TFile("~/DarkSUSY_mH_125_mGammaD_0300_cT_000_13TeV_RAW2DIGI_L1Reco_RECO_MCRUN2_74_V9_v1.root");
  TFile *f[1] = new TFile("~/DarkSUSY_mH_125_mGammaD_0300_cT_010_13TeV_RAW2DIGI_L1Reco_RECO_MCRUN2_74_V9_v1.root");
  TFile *f[2] = new TFile("~/DarkSUSY_mH_125_mGammaD_0300_cT_020_13TeV_RAW2DIGI_L1Reco_RECO_MCRUN2_74_V9_v1.root");
  TFile *f[3] = new TFile("~/DarkSUSY_mH_125_mGammaD_0300_cT_050_13TeV_RAW2DIGI_L1Reco_RECO_MCRUN2_74_V9_v1.root");
  TFile *f[4] = new TFile("~/DarkSUSY_mH_125_mGammaD_0300_cT_100_13TeV_RAW2DIGI_L1Reco_RECO_MCRUN2_74_V9_v1.root");
  TFile *f[5] = new TFile("~/DarkSUSY_mH_125_mGammaD_0300_cT_200_13TeV_RAW2DIGI_L1Reco_RECO_MCRUN2_74_V9_v1.root");
  TFile *f[6] = new TFile("~/DarkSUSY_mH_125_mGammaD_0300_cT_500_13TeV_RAW2DIGI_L1Reco_RECO_MCRUN2_74_V9_v1.root");


  Float_t ev_all[40]={0.0};

  Int_t is1GenMu17;
  Int_t is2GenMu8;
  Int_t is3GenMu8;
  Int_t is4GenMu8;

  Int_t is1SelMu17;
  Int_t is2SelMu8;
  Int_t is3SelMu8;
  Int_t is4SelMu8;


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

  Int_t muJetChit[2];
  Int_t muJetFhit[2];

  Int_t muJetChitgt[2];
  Int_t muJetFhitgt[2];

  Float_t muJetC_vtx_x;
  Float_t muJetC_vtx_y;
  Float_t muJetC_vtx_z;

  Float_t muJetF_vtx_x;
  Float_t muJetF_vtx_y;
  Float_t muJetF_vtx_z;

  Float_t muJetC_mindisttrk;
  Float_t muJetF_mindisttrk;

  Bool_t muJetC_validVtx;
  Bool_t muJetC_validVtx_fitted;
  Bool_t muJetC_validVtx_mindist;

  Bool_t muJetF_validVtx;
  Bool_t muJetF_validVtx_fitted;
  Bool_t muJetF_validVtx_mindist;

  Int_t comphitmu1JetC;
  Int_t comphitmu2JetC;
  Int_t comphitmu1JetF;
  Int_t comphitmu2JetF;

  Int_t Detmu1jetC;
  Int_t Detmu2jetC;
  Int_t Detmu1jetF;
  Int_t Detmu2jetF;


  Float_t  muJetC_trackdist_1stpixel;
  Float_t  muJetF_trackdist_1stpixel;


  Float_t mu1JetCposx[500];
  Float_t mu2JetCposx[500];
  Float_t mu1JetCposy[500];
  Float_t mu2JetCposy[500];

  Float_t mu1JetFposx[500];
  Float_t mu2JetFposx[500];
  Float_t mu1JetFposy[500];
  Float_t mu2JetFposy[500];


  Float_t mu1JetCerrposx[500];
  Float_t mu2JetCerrposx[500];
  Float_t mu1JetCerrposy[500];
  Float_t mu2JetCerrposy[500];

  Float_t mu1JetFerrposx[500];
  Float_t mu2JetFerrposx[500];
  Float_t mu1JetFerrposy[500];
  Float_t mu2JetFerrposy[500];

  Float_t pixelhitmu1JetCx[900];
  Float_t pixelhitmu2JetCx[900];
  Float_t pixelhitmu1JetCy[900];
  Float_t pixelhitmu2JetCy[900];
  Float_t pixelhitmu1JetFx[900];
  Float_t pixelhitmu2JetFx[900];
  Float_t pixelhitmu1JetFy[900];
  Float_t pixelhitmu2JetFy[900];

  Float_t pixelhitmu1JetCerrx[900];
  Float_t pixelhitmu2JetCerrx[900];
  Float_t pixelhitmu1JetCerry[900];
  Float_t pixelhitmu2JetCerry[900];
  Float_t pixelhitmu1JetFerrx[900];
  Float_t pixelhitmu2JetFerrx[900];
  Float_t pixelhitmu1JetFerry[900];
  Float_t pixelhitmu2JetFerry[900];

  Float_t mindist_mu1hit_muJetC[900];
  Float_t mindist_mu2hit_muJetC[900];
  Float_t mindist_mu1hit_muJetF[900];
  Float_t mindist_mu2hit_muJetF[900];



  Int_t hitrecover_mj2_r001;
  Int_t hitrecover_mj2_r005;
  Int_t hitrecover_mj2_r01;
  Int_t hitrecover_mj2_r03;
  Int_t hitrecover_mj2_r05;
  Int_t hitrecover_mj2_r1;

  Int_t hitrecover_mj1_r001;
  Int_t hitrecover_mj1_r005;
  Int_t hitrecover_mj1_r01;
  Int_t hitrecover_mj1_r03;
  Int_t hitrecover_mj1_r05;
  Int_t hitrecover_mj1_r1;

  Int_t hitrecover_mj12_r001;
  Int_t hitrecover_mj12_r005;
  Int_t hitrecover_mj12_r01;
  Int_t hitrecover_mj12_r03;
  Int_t hitrecover_mj12_r05;
  Int_t hitrecover_mj12_r1;



  Int_t is4Gmu8;
  Float_t genA0_Lxy;
  Float_t genA1_Lxy;
  Float_t genA0_Lz;
  Float_t genA1_Lz;

  Int_t is4Rmu8;

  //============= Counters ===========================//
  Int_t c1genm[40]={0};
  Int_t c2genm[40]={0};
  Int_t c3genm[40]={0};
  Int_t c4genm[40]={0};

  Int_t c1recm[40]={0};
  Int_t c2recm[40]={0};
  Int_t c3recm[40]={0};
  Int_t c4recm[40]={0};

  //  for(int p=36;p<37;p++){
  for(int p=0;p<7;p++){
    
    //    if(p!=10) continue;
    
    f[p]->cd("ana2012");
    
    TTree *t = (TTree*)f[p]->Get("ana2012/Events");
  
    cout<<"  Events  "<<t->GetEntries()<<endl;
    
    t->SetBranchAddress("event",&event);
    t->SetBranchAddress("2dimuon",&ev2dim);
    t->SetBranchAddress("2mjets",&ev2mj);

    t->SetBranchAddress("is1GenMu17",&is1GenMu17);
    t->SetBranchAddress("is2GenMu8",&is2GenMu8);
    t->SetBranchAddress("is3GenMu8",&is3GenMu8);
    //    t->SetBranchAddress("is4GenMu8",&is4GenMu8);

    t->SetBranchAddress("is1SelMu17",&is1SelMu17);
    t->SetBranchAddress("is2SelMu8",&is2SelMu8);
    t->SetBranchAddress("is3SelMu8",&is3SelMu8);
    t->SetBranchAddress("is4SelMu8",&is4SelMu8);
    
    t->SetBranchAddress("isVertexOK",&isVtxOK);
    t->SetBranchAddress("is2DiMuonsDzOK",&is2DimDzOK);
    t->SetBranchAddress("is2DiMuonsVtxOK",&is2DimVtxOK);
    t->SetBranchAddress("is2DiMuonsMassOK",&is2DimMassOK);
    t->SetBranchAddress("is2DiMuonsIsoTkOK",&is2DimIsoTkOK);
    t->SetBranchAddress("is2DiMuonHLTFired",&is2DimHLTFired);

    t->SetBranchAddress("is4GenMu8",&is4Gmu8);
    t->SetBranchAddress("genA0_Lxy_rdet",&genA0_Lxy);
    t->SetBranchAddress("genA1_Lxy_rdet",&genA1_Lxy);
    t->SetBranchAddress("genA0_Lz_rdet",&genA0_Lz);
    t->SetBranchAddress("genA1_Lz_rdet",&genA1_Lz);

    t->SetBranchAddress("4recm",&is4Rmu8);
    
    t->SetBranchAddress("muJetC_hitpix",&muJetChit);
    t->SetBranchAddress("muJetF_hitpix",&muJetFhit);
    
    t->SetBranchAddress("muJetC_hitpix_genTrk",&muJetChitgt);
    t->SetBranchAddress("muJetF_hitpix_genTrk",&muJetFhitgt);
    
    t->SetBranchAddress("muJetC_vtx_x",&muJetC_vtx_x);
    t->SetBranchAddress("muJetC_vtx_y",&muJetC_vtx_y);
    t->SetBranchAddress("muJetC_vtx_z",&muJetC_vtx_z);
    
    t->SetBranchAddress("muJetF_vtx_x",&muJetF_vtx_x);
    t->SetBranchAddress("muJetF_vtx_y",&muJetF_vtx_y);
    t->SetBranchAddress("muJetF_vtx_z",&muJetF_vtx_z);

    t->SetBranchAddress("muJetC_mindisttracks",&muJetC_mindisttrk);
    t->SetBranchAddress("muJetF_mindisttracks",&muJetF_mindisttrk);
    
    t->SetBranchAddress("muJetC_validVtx",&muJetC_validVtx);
    t->SetBranchAddress("muJetC_validVtx_fitted",&muJetC_validVtx_fitted);
    t->SetBranchAddress("muJetC_validVtx_mindist",&muJetC_validVtx_mindist);
    
    t->SetBranchAddress("muJetF_validVtx",&muJetF_validVtx);
    t->SetBranchAddress("muJetF_validVtx_fitted",&muJetF_validVtx_fitted);
    t->SetBranchAddress("muJetF_validVtx_mindist",&muJetF_validVtx_mindist);

    t->SetBranchAddress("Det_mu1_muJetC",&Detmu1jetC);
    t->SetBranchAddress("Det_mu2_muJetC",&Detmu2jetC);
    t->SetBranchAddress("Det_mu1_muJetF",&Detmu1jetF);
    t->SetBranchAddress("Det_mu2_muJetF",&Detmu2jetF);

    // t->SetBranchAddress("muJetC_trackdist_1stpixel",&muJetC_trackdist_1stpixel);
    // t->SetBranchAddress("muJetF_trackdist_1stpixel",&muJetF_trackdist_1stpixel);

    t->SetBranchAddress("comphits_mu1_muJetC",&comphitmu1JetC);
    t->SetBranchAddress("comphits_mu2_muJetC",&comphitmu2JetC);
    t->SetBranchAddress("comphits_mu1_muJetF",&comphitmu1JetF);
    t->SetBranchAddress("comphits_mu2_muJetF",&comphitmu2JetF);

    t->SetBranchAddress("muJetC_muon1_posx1stpix",&mu1JetCposx);
    t->SetBranchAddress("muJetC_muon2_posx1stpix",&mu2JetCposx);
    t->SetBranchAddress("muJetC_muon1_posy1stpix",&mu1JetCposy);
    t->SetBranchAddress("muJetC_muon2_posy1stpix",&mu2JetCposy);

    t->SetBranchAddress("muJetF_muon1_posx1stpix",&mu1JetFposx);
    t->SetBranchAddress("muJetF_muon2_posx1stpix",&mu2JetFposx);
    t->SetBranchAddress("muJetF_muon1_posy1stpix",&mu1JetFposy);
    t->SetBranchAddress("muJetF_muon2_posy1stpix",&mu2JetFposy);

    t->SetBranchAddress("muJetC_muon1_errposx1stpix",&mu1JetCerrposx);
    t->SetBranchAddress("muJetC_muon2_errposx1stpix",&mu2JetCerrposx);
    t->SetBranchAddress("muJetC_muon1_errposy1stpix",&mu1JetCerrposy);
    t->SetBranchAddress("muJetC_muon2_errposy1stpix",&mu2JetCerrposy);

    t->SetBranchAddress("muJetF_muon1_errposx1stpix",&mu1JetFerrposx);
    t->SetBranchAddress("muJetF_muon2_errposx1stpix",&mu2JetFerrposx);
    t->SetBranchAddress("muJetF_muon1_errposy1stpix",&mu1JetFerrposy);
    t->SetBranchAddress("muJetF_muon2_errposy1stpix",&mu2JetFerrposy);

    t->SetBranchAddress("pixelhit_mu1_muJetC_posx",&pixelhitmu1JetCx);
    t->SetBranchAddress("pixelhit_mu2_muJetC_posx",&pixelhitmu2JetCx);
    t->SetBranchAddress("pixelhit_mu1_muJetC_posy",&pixelhitmu1JetCy);
    t->SetBranchAddress("pixelhit_mu2_muJetC_posy",&pixelhitmu2JetCy);

    t->SetBranchAddress("pixelhit_mu1_muJetF_posx",&pixelhitmu1JetFx);
    t->SetBranchAddress("pixelhit_mu2_muJetF_posx",&pixelhitmu2JetFx);
    t->SetBranchAddress("pixelhit_mu1_muJetF_posy",&pixelhitmu1JetFy);
    t->SetBranchAddress("pixelhit_mu2_muJetF_posy",&pixelhitmu2JetFy);


    t->SetBranchAddress("pixelhit_mu1_muJetC_errposx",&pixelhitmu1JetCerrx);
    t->SetBranchAddress("pixelhit_mu2_muJetC_errposx",&pixelhitmu2JetCerrx);
    t->SetBranchAddress("pixelhit_mu1_muJetC_errposy",&pixelhitmu1JetCerry);
    t->SetBranchAddress("pixelhit_mu2_muJetC_errposy",&pixelhitmu2JetCerry);

    t->SetBranchAddress("pixelhit_mu1_muJetF_errposx",&pixelhitmu1JetFerrx);
    t->SetBranchAddress("pixelhit_mu2_muJetF_errposx",&pixelhitmu2JetFerrx);
    t->SetBranchAddress("pixelhit_mu1_muJetF_errposy",&pixelhitmu1JetFerry);
    t->SetBranchAddress("pixelhit_mu2_muJetF_errposy",&pixelhitmu2JetFerry);
    
    t->SetBranchAddress("mindist_hit_mu1_muJetC",mindist_mu1hit_muJetC);
    t->SetBranchAddress("mindist_hit_mu2_muJetC",mindist_mu2hit_muJetC);
    t->SetBranchAddress("mindist_hit_mu1_muJetF",mindist_mu1hit_muJetF);
    t->SetBranchAddress("mindist_hit_mu2_muJetF",mindist_mu2hit_muJetF);
  

    t->SetBranchAddress("hitrecover_mj2_r001",&hitrecover_mj2_r001);
    t->SetBranchAddress("hitrecover_mj2_r005",&hitrecover_mj2_r005);
    t->SetBranchAddress("hitrecover_mj2_r01",&hitrecover_mj2_r01);
    t->SetBranchAddress("hitrecover_mj2_r03",&hitrecover_mj2_r03);
    t->SetBranchAddress("hitrecover_mj2_r05",&hitrecover_mj2_r05);
    t->SetBranchAddress("hitrecover_mj2_r1",&hitrecover_mj2_r1);

    t->SetBranchAddress("hitrecover_mj1_r001",&hitrecover_mj1_r001);
    t->SetBranchAddress("hitrecover_mj1_r005",&hitrecover_mj1_r005);
    t->SetBranchAddress("hitrecover_mj1_r01",&hitrecover_mj1_r01);
    t->SetBranchAddress("hitrecover_mj1_r03",&hitrecover_mj1_r03);
    t->SetBranchAddress("hitrecover_mj1_r05",&hitrecover_mj1_r05);
    t->SetBranchAddress("hitrecover_mj1_r1",&hitrecover_mj1_r1);

    t->SetBranchAddress("hitrecover_mj12_r001",&hitrecover_mj12_r001);
    t->SetBranchAddress("hitrecover_mj12_r005",&hitrecover_mj12_r005);
    t->SetBranchAddress("hitrecover_mj12_r01",&hitrecover_mj12_r01);
    t->SetBranchAddress("hitrecover_mj12_r03",&hitrecover_mj12_r03);
    t->SetBranchAddress("hitrecover_mj12_r05",&hitrecover_mj12_r05);
    t->SetBranchAddress("hitrecover_mj12_r1",&hitrecover_mj12_r1);



    t->SetBranchAddress("muJetC_muon1_track_minchi2",&muJetC_muon1_track_minchi2);
    t->SetBranchAddress("muJetC_muon2_track_minchi2",&muJetC_muon2_track_minchi2);
    t->SetBranchAddress("muJetF_muon1_track_minchi2",&muJetF_muon1_track_minchi2);
    t->SetBranchAddress("muJetF_muon2_track_minchi2",&muJetF_muon2_track_minchi2);

    Int_t nentries = t->GetEntries();


    for(int k=0;k<nentries;k++){
      t->GetEntry(k);
      
      ev_all[p]++;

      if(is1GenMu17) c1genm[p]++;
      if(is2GenMu8) c2genm[p]++;
      if(is3GenMu8) c3genm[p]++;
      if(is4Gmu8) c4genm[p]++;

      if(is1SelMu17) c1recm[p]++;
      if(is2SelMu8) c2recm[p]++;
      if(is3SelMu8) c3recm[p]++;
      if(is4SelMu8) c4recm[p]++;


      //  ===========   GEN LEVEL information  ==============//
      if(is4Gmu8){
      	ev_4gm[p]++;
      	if(fabs(genA0_Lxy)<4.4 && fabs(genA1_Lxy)<4.4 && fabs(genA0_Lz)<34.5 && fabs(genA1_Lz)<34.5){
      	  ev_4gmlxylzcut[p]++;
      	}
      }
      
      //  =============  RECO information ====================//

      
      if(is4Rmu8){
    	ev_4rm[p]++;
	if(isVtxOK){
	  ev_isVtxOK[p]++;
	  if(ev2mj){
	    ev_2mj[p]++;
	    if(ev2dim){
	      ev_2dim[p]++;
	      
	      if(is2DimVtxOK && muJetC_validVtx_fitted && muJetF_validVtx_fitted){
		ev_2dimvtxok[p]++;
	  
		if( (muJetChitgt[0]==1||muJetChitgt[1]==1)&&(muJetFhitgt[0]==1||muJetFhitgt[1]==1) )  ev_2dimhitgt[p]++;  
		if( ( (muJetChitgt[0]==1||muJetChitgt[1]==1)&&(muJetFhitgt[0]==1||muJetFhitgt[1]==1) ) && muJetC_validVtx_fitted && muJetF_validVtx_fitted  )  ev_2dimhitfvtx[p]++;  

		//		if( (muJetChit[0]==1||muJetChit[1]==1)&&(muJetFhit[0]==1||muJetFhit[1]==1)){
		if( ((muJetChitgt[0]==1||muJetChitgt[1]==1)&&(muJetFhitgt[0]==1||muJetFhitgt[1]==1))    ){
		//		if( ((muJetChitgt[0]==1||muJetChitgt[1]==1)&&(muJetFhitgt[0]==1||muJetFhitgt[1]==1))  && muJetC_validVtx_fitted && muJetF_validVtx_fitted   ){
		  ev_2dimhit[p]++;
	      
		  if(is2DimDzOK){
		    ev_is2DimDzOK[p]++;
		      if(is2DimMassOK){
			ev_is2DimMassOK[p]++;
			if(is2DimIsoTkOK){
			  ev_is2DimIsoTkOK[p]++;
			  if(is2DimHLTFired){ 
			    ev_is2DimHLTFired[p]++;
			    ev_2dimhit_allcut[p]++;
			}
		      }
		    }
		  }
		}
			
	  // 	if(is2DimDzOK && is2DimHLTFired && is2DimMassOK && is2DimIsoTkOK){
		  
	  // 	  //=======================  Hit Recovery ==============================================//
		  
	  // 	  Bool_t vtx_constrain=false;
		  
	  // 	  // if(  (fabs(muJetC_vtx_x)<10.0 && fabs(muJetC_vtx_y)<10.0 && fabs(muJetC_vtx_z)<20.0) &&
	  // 	  //   	 (fabs(muJetF_vtx_x)<10.0 && fabs(muJetF_vtx_y)<10.0 && fabs(muJetF_vtx_z)<20.0) &&
	  // 	  //   	 muJetC_mindisttrk<0.03 && muJetF_mindisttrk<0.03) vtx_constrain=true;
		  
	  // 	  //	    if( fabs(muJetC_vtx_z)<24.0 && fabs(muJetF_vtx_z)<24.0 && muJetC_mindisttrk<0.03 && muJetF_mindisttrk<0.03 ) vtx_constrain=true;
	  // 	  //	    if(muJetC_mindisttrk<0.3 && muJetF_mindisttrk<0.3 ) vtx_constrain=true;
	  // 	  vtx_constrain=true;
		  
		  
	  // 	  //		  if( (muJetChit[0]!=1&&muJetChit[1]!=1)||(muJetFhit[0]!=1&&muJetFhit[1]!=1) ){
			  
	  // 	  //		    if( (muJetChit[0]!=1&&muJetChit[1]!=1)&&(muJetFhit[0]!=1&&muJetFhit[1]!=1)){

	  // 	  if( (muJetChitgt[0]!=1&&muJetChitgt[1]!=1)||(muJetFhitgt[0]!=1&&muJetFhitgt[1]!=1) ){
			  
	  // 	    if( (muJetChitgt[0]!=1&&muJetChitgt[1]!=1)&&(muJetFhitgt[0]!=1&&muJetFhitgt[1]!=1)){
			    
	  // 	      bool recover_muJetC=false;
	  // 	      bool recover_muJetF=false;
			    
	  // 	      if(Detmu1jetC>0 && Detmu2jetC>0){
	  // 		for(int j=0;j<Detmu1jetC;j++){
	  // 		  if(mindist_mu1hit_muJetC[j]<0.03 && mindist_mu1hit_muJetC[j]>=0.0) recover_muJetC=true;
	  // 		}
	  // 		for(int j=0;j<Detmu2jetC;j++){
	  // 		  if(mindist_mu2hit_muJetC[j]<0.03 && mindist_mu2hit_muJetC[j]>=0.0) recover_muJetC=true;
	  // 		}
	  // 	      }
			    
	  // 	      if(Detmu1jetF>0 && Detmu2jetF>0){
	  // 		for(int j=0;j<Detmu1jetF;j++){
	  // 		  if(mindist_mu1hit_muJetF[j]<0.03 && mindist_mu1hit_muJetF[j]>=0.0) recover_muJetF=true;
	  // 		}
	  // 		for(int j=0;j<Detmu2jetC;j++){
	  // 		  if(mindist_mu2hit_muJetF[j]<0.03 && mindist_mu2hit_muJetF[j]>=0.0) recover_muJetF=true;
	  // 		}
	  // 	      }
		    
	  // 	      if(recover_muJetC && recover_muJetF && vtx_constrain) ev_2dimhit_recov2dim[p]++;
	  // 	      if(hitrecover_mj12_r005 && vtx_constrain) ev_2dimhit_recov2dim2[p]++;
	  // 	    }
		  
		  
		  
	  // 	    //		    if( (muJetChit[0]!=1&&muJetChit[1]!=1)&&(muJetFhit[0]==1||muJetFhit[1]==1)){
	  // 	    if( (muJetChitgt[0]!=1&&muJetChitgt[1]!=1)&&(muJetFhitgt[0]==1||muJetFhitgt[1]==1)){
		    
	  // 	      bool recover_muJetC=false;
		
	  // 	      if(Detmu1jetC>0 && Detmu2jetC>0){
	  // 		for(int j=0;j<Detmu1jetC;j++){
	  // 		  if(mindist_mu1hit_muJetC[j]<0.03 && mindist_mu1hit_muJetC[j]>=0.0) recover_muJetC=true;
	  // 		}
	  // 		for(int j=0;j<Detmu2jetC;j++){
	  // 		  if(mindist_mu2hit_muJetC[j]<0.03 && mindist_mu2hit_muJetC[j]>=0.0) recover_muJetC=true;
	  // 		}
	  // 	      }
		
	  // 	      if(recover_muJetC && vtx_constrain) ev_2dimhit_recovmuJetC[p]++;
	  // 	      if(hitrecover_mj1_r005==1 && vtx_constrain ) ev_2dimhit_recovmuJetC2[p]++;
	  // 	    }
	      
	      
	  // 	    //if( (muJetFhit[0]!=1&&muJetFhit[1]!=1)&&(muJetChit[0]==1||muJetChit[1]==1)){
	  // 	    if( (muJetFhitgt[0]!=1&&muJetFhitgt[1]!=1)&&(muJetChitgt[0]==1||muJetChitgt[1]==1)){
		
	  // 	      bool recover_muJetF=false;
		
	  // 	      if(Detmu1jetF>0 && Detmu2jetF>0){
	  // 		for(int j=0;j<Detmu1jetF;j++){
	  // 		  if(mindist_mu1hit_muJetF[j]<0.03 && mindist_mu1hit_muJetF[j]>=0.0) recover_muJetF=true;
	  // 		}
	  // 		for(int j=0;j<Detmu2jetF;j++){
	  // 		  if(mindist_mu2hit_muJetF[j]<0.03 && mindist_mu2hit_muJetF[j]>=0.0) recover_muJetF=true;
	  // 		}
	  // 	      }
		
	  // 	      if(recover_muJetF && vtx_constrain ) ev_2dimhit_recovmuJetF[p]++;
	  // 	      if(hitrecover_mj2_r005==1 && vtx_constrain ) ev_2dimhit_recovmuJetF2[p]++;
		

	  // 	    }
	  // 	  }
	  // 	}
	  //     }
	  //   }
	  // }

	      }
	    }
	  }
	}
      }
    }

    // ev_2dimhit_allcutrecov[p] = ev_2dimhit_allcut[p] + ev_2dimhit_recov2dim[p] +ev_2dimhit_recovmuJetC[p] + ev_2dimhit_recovmuJetF[p];
    // ev_2dimhit_allcutrecov2[p] = ev_2dimhit_allcut[p] + ev_2dimhit_recov2dim2[p] +ev_2dimhit_recovmuJetC2[p] + ev_2dimhit_recovmuJetF2[p];

    // ev_2dim_recov[p] =  ev_2dimhit_recov2dim[p] +ev_2dimhit_recovmuJetC[p] + ev_2dimhit_recovmuJetF[p];
    // ev_2dim_recov2[p] =  ev_2dimhit_recov2dim2[p] +ev_2dimhit_recovmuJetC2[p] + ev_2dimhit_recovmuJetF2[p];
    
    std::cout<<" sample          "<<p<<std::endl;
    std::cout<<" Events          "<<t->GetEntries()<<std::endl;
    std::cout<<"  ================= GEN MUONS ========================================= "<<std::endl;
    std::cout<<" 1GenMu17        "<<c1genm[p]<<"   reff "<<c1genm[p]/(t->GetEntries()*1.0)<<"  +/-  "<<sqrt(  ((c1genm[p]/(t->GetEntries()*1.0))*(1-(c1genm[p]/(t->GetEntries()*1.0))))/(1.0*t->GetEntries()))<<std::endl;
    std::cout<<" 2GenMu8         "<<c2genm[p]<<"   reff  "<<c2genm[p]/(c1genm[p]*1.0)<<"  +/-  "<<sqrt( ( (c2genm[p]/(c1genm[p]*1.0))*(1-(c2genm[p]/(c1genm[p]*1.0))))/(1.0*c1genm[p]))<<std::endl;
    std::cout<<" 3GenMu8         "<<c3genm[p]<<"   reff  "<<c3genm[p]/(c2genm[p]*1.0)<<" +/-  "<<sqrt( ( (c3genm[p]/(c2genm[p]*1.0))*(1-(c3genm[p]/(c2genm[p]*1.0))))/(1.0*c2genm[p]))<<std::endl;
    std::cout<<" 4GenMu8         "<<c4genm[p]<<"   reff  "<<c4genm[p]/(c3genm[p]*1.0)<<" +/-  "<<sqrt( ( (c4genm[p]/(c3genm[p]*1.0))*(1-(c4genm[p]/(c3genm[p]*1.0))))/(1.0*c3genm[p]))<<std::endl;
    std::cout<<" 4GenMu8 Lxy/Lz  "<<ev_4gmlxylzcut[p]<<"   reff   "<<ev_4gmlxylzcut[p]/ev_4gm[p]<<std::endl;
    std::cout<<"  ================= RECO MUONS ========================================= "<<std::endl;
    std::cout<<" 1RecMu17    "<<c1recm[p]<<"  reff  "<<c1recm[p]/(t->GetEntries()*1.0)<<std::endl;
    std::cout<<" 2RecMu8     "<<c2recm[p]<<"  reff  "<<c2recm[p]/(c1recm[p]*1.0)<<std::endl;
    std::cout<<" 3RecMu8     "<<c3recm[p]<<"  reff  "<<c3recm[p]/(c2recm[p]*1.0)<<std::endl;
    std::cout<<" 4RecMu8     "<<c4recm[p]<<"  reff  "<<c4recm[p]/(c3recm[p]*1.0)<<std::endl;
    std::cout<<"  ================== EVENT variables (before HitRecovery) ================= "<<std::endl;
    std::cout<<"  Events with VtxOK                     "<<ev_isVtxOK[p]<<"    reff  "<<ev_isVtxOK[p]/ev_4rm[p]<<std::endl;
    std::cout<<"  Events with 2 muonjets                "<<ev_2mj[p]<<"     reff  "<<ev_2mj[p]/ev_isVtxOK[p]<<std::endl;
    std::cout<<"  Events with 2Dim                      "<<ev_2dim[p]<<"    reff  "<<ev_2dim[p]/ev_2mj[p]<<std::endl;
    std::cout<<"  Events with 2DimVtxOK                 "<<ev_2dimvtxok[p]<<"    reff  "<<ev_2dimvtxok[p]/ev_2dim[p]<<std::endl;
    std::cout<<"  Events with 2DimHitPix                "<<ev_2dimhit[p]<<"     reff  "<<ev_2dimhit[p]/ev_2dimvtxok[p]<<std::endl;
    std::cout<<"  ========================================================== "<<std::endl;
    std::cout<<"  Events with 2DimHitPix gt                             "<<ev_2dimhitgt[p]<<"  reff  "<<ev_2dimhitgt[p]/ev_2dimvtxok[p]<<std::endl;
    std::cout<<"  Events with 2DimHitPix gt fitted vtx                  "<<ev_2dimhitfvtx[p]<<"  reff  "<<ev_2dimhitfvtx[p]/ev_2dimvtxok[p]<<std::endl;
    std::cout<<"  ========================================================== "<<std::endl;
    std::cout<<"  Events with 2DimDzOK                  "<<ev_is2DimDzOK[p]<<"   reff   "<<ev_is2DimDzOK[p]/ev_2dimhit[p]<<endl;
    std::cout<<"  Events with 2DimMassOK                "<<ev_is2DimMassOK[p]<<"  reff   "<<ev_is2DimMassOK[p]/ev_is2DimDzOK[p]<<endl;
    std::cout<<"  Events with 2DimIsoOK                 "<<ev_is2DimIsoTkOK[p]<<"   reff   "<<ev_is2DimIsoTkOK[p]/ev_is2DimMassOK[p]<<endl;
    std::cout<<"  Events with 2DimHLT                   "<<ev_is2DimHLTFired[p]<<"   reff   "<<ev_is2DimHLTFired[p]/ev_is2DimIsoTkOK[p]<<endl;
    std::cout<<"  ratio reco/gen                        "<<ev_is2DimHLTFired[p]/ev_4gmlxylzcut[p]<<" +/-  "<<sqrt( ((ev_is2DimHLTFired[p]/ev_4gmlxylzcut[p])*(1- (ev_is2DimHLTFired[p]/ev_4gmlxylzcut[p]) ))/ev_4gmlxylzcut[p])<<std::endl;
    
    // std::cout<<"  ========================================================== "<<std::endl;
    // std::cout<<"  ======================= HitRecovery MinimumDistance======= "<<std::endl;
    // //    std::cout<<"  Events with allcuts Failhits                       "<<ev_2dimhit_allcut[p]<<std::endl;
    // std::cout<<"  Events 2dimuons recovered (after allcuts)  "<<ev_2dimhit_recov2dim[p]<<std::endl;
    // std::cout<<"  Events muJetC recovered  (after allcuts)   "<<ev_2dimhit_recovmuJetC[p]<<std::endl;
    // std::cout<<"  Events muJetF recovered (after allcuts)    "<<ev_2dimhit_recovmuJetF[p]<<std::endl;
    // std::cout<<"  Total events recovered                     "<<ev_2dim_recov[p]<<std::endl;
    // //    std::cout<<"  ratio  reco/gen                               "<<ev_2dimhit_allcutrecov[p]/ev_4gmlxylzcut[p]<<std::endl;
    // std::cout<<"  ===================== HitRecovery Bike Chain ============== "<<std::endl;
    // std::cout<<"  Events 2dimuons recovered (after allcuts)  "<<ev_2dimhit_recov2dim2[p]<<std::endl;
    // std::cout<<"  Events muJetC recovered  (after allcuts)   "<<ev_2dimhit_recovmuJetC2[p]<<std::endl;
    // std::cout<<"  Events muJetF recovered (after allcuts)    "<<ev_2dimhit_recovmuJetF2[p]<<std::endl;
    // std::cout<<"  Total events recovered                     "<<ev_2dim_recov2[p]<<std::endl;
    // std::cout<<"  ========================================================== "<<std::endl;
    // std::cout<<"  ========================================================== "<<std::endl;
    // std::cout<<"  ==================  EVENT variables (after HitRecovery MinDistance) ============= "<<std::endl;
    // std::cout<<"  Events with 2DimHitPix                     "<<ev_2dimhit[p]+ev_2dim_recov[p]<<"   reff  "<<ev_2dimhit[p]+ev_2dim_recov[p]/ev_2dimvtxok[p]<<std::endl;
    // std::cout<<"  Events with 2DimDzOK                       "<<ev_is2DimDzOK[p]+ev_2dim_recov[p]<<"   reff   "<<(ev_is2DimDzOK[p]+ev_2dim_recov[p])/(ev_2dimhit[p]+ev_2dim_recov[p])<<endl;
    // std::cout<<"  Events with 2DimHLT                        "<<ev_is2DimHLTFired[p]+ev_2dim_recov[p]<<"   reff   "<<(ev_is2DimHLTFired[p]+ev_2dim_recov[p])/(ev_is2DimDzOK[p]+ev_2dim_recov[p])<<endl;
    // std::cout<<"  Events with 2DimMassOK                     "<<ev_is2DimMassOK[p]+ev_2dim_recov[p]<<"   reff   "<<(ev_is2DimMassOK[p]+ev_2dim_recov[p])/(ev_is2DimHLTFired[p]+ev_2dim_recov[p])<<endl;
    // std::cout<<"  Events with 2DimIsoOK                      "<<ev_is2DimIsoTkOK[p]+ev_2dim_recov[p]<<"   reff   "<<(ev_is2DimIsoTkOK[p]+ev_2dim_recov[p])/(ev_is2DimMassOK[p]+ev_2dim_recov[p])<<endl;
    // std::cout<<"  ratio reco/gen (MinDistance)                "<<ev_2dimhit_allcutrecov[p]/ev_4gmlxylzcut[p]<<std::endl;
    // std::cout<<"  ==================  EVENT variables (after HitRecovery Bike Chain) ============= "<<std::endl;
    // std::cout<<"  Events with 2DimHitPix                     "<<ev_2dimhit[p]+ev_2dim_recov2[p]<<"   reff  "<<ev_2dimhit[p]+ev_2dim_recov2[p]/ev_2dimvtxok[p]<<std::endl;
    // std::cout<<"  Events with 2DimDzOK                       "<<ev_is2DimDzOK[p]+ev_2dim_recov2[p]<<"   reff   "<<(ev_is2DimDzOK[p]+ev_2dim_recov2[p])/(ev_2dimhit[p]+ev_2dim_recov2[p])<<endl;
    // std::cout<<"  Events with 2DimHLT                        "<<ev_is2DimHLTFired[p]+ev_2dim_recov2[p]<<"   reff   "<<(ev_is2DimHLTFired[p]+ev_2dim_recov2[p])/(ev_is2DimDzOK[p]+ev_2dim_recov2[p])<<endl;
    // std::cout<<"  Events with 2DimMassOK                     "<<ev_is2DimMassOK[p]+ev_2dim_recov2[p]<<"   reff   "<<(ev_is2DimMassOK[p]+ev_2dim_recov2[p])/(ev_is2DimHLTFired[p]+ev_2dim_recov2[p])<<endl;
    // std::cout<<"  Events with 2DimIsoOK                      "<<ev_is2DimIsoTkOK[p]+ev_2dim_recov2[p]<<"   reff   "<<(ev_is2DimIsoTkOK[p]+ev_2dim_recov2[p])/(ev_is2DimMassOK[p]+ev_2dim_recov2[p])<<endl;




    // Float_t eps_gen = ev_4gmlxylzcut[p]/(1.0*t->GetEntries());
    // Float_t eps_full = ev_2dimhit_allcutrecov2[p]/(1.0*t->GetEntries());
    // Float_t err_eps_gen = sqrt( (eps_gen*(1-eps_gen))/(1.0*t->GetEntries()));
    // Float_t err_eps_full= sqrt( (eps_full*(1-eps_full))/(1.0*t->GetEntries()));
    // Float_t err_ratio = (eps_full/eps_gen)*sqrt(pow(err_eps_full/eps_full,2)+pow(err_eps_gen/eps_gen,2));

    // std::cout<<"  ratio epsilon_gen (Bike Chain)        %    "<<(eps_gen)*100.0<<" +/-  "<<(err_eps_gen)*100.0<<std::endl;
    // std::cout<<"  ratio epsilon_full (Bike Chain)       %    "<<(eps_full)*100.0<<" +/-  "<<(err_eps_full)*100.0<<std::endl;
    // std::cout<<"  ratio reco/gen (Bike Chain)                "<<eps_full/eps_gen<<" +/-  "<<err_ratio<<std::endl;
    // std::cout<<"  Finish sample   "<<p<<std::endl;
    // std::cout<<"                                                                      "<<std::endl;
    // std::cout<<"                                                                      "<<std::endl;
    // std::cout<<"                              
    //                                        "<<std::endl;
    
  }





  Float_t ctau[7]={0.0,0.1,0.2,0.5,1.0,2.0,5.0};

  Float_t eff_mD0300[7]={0.0};
  Float_t erreff_mD0300[7]={0.0};


  for(int k=0;k<7;k++){
    eff_mD0300[k] = ev_is2DimHLTFired[k]/ev_4gmlxylzcut[k];
    erreff_mD0300[k] = sqrt( (eff_mD0300[k]*(1-eff_mD0300[k]))/(ev_4gmlxylzcut[k]*1.0));
  }

  TGraphErrors *gr_eff_mD0300 = new TGraphErrors(7,ctau,eff_mD0300,0,erreff_mD0300);

  TLegend *leg = new TLegend(0.5,0.3,0.85,0.6);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetTextSize(0.045);
  leg->AddEntry(gr_eff_mD0300,"m_{#gamma D}=0.3GeV","PL");
  
  
  TH2F *dummy3 = new TH2F("","",100,-0.2,5.2,100,0.0,1.0);
  
  TCanvas *c = new TCanvas("c","c",700,500);
  dummy3->GetXaxis()->SetTitle("c#tau [mm]");
  dummy3->GetYaxis()->SetTitle("#epsilon_{rec}/#alpha_{gen}");
  dummy3->Draw();
  gr_eff_mD0300->SetLineWidth(2);
  gr_eff_mD0300->SetLineColor(2);
  gr_eff_mD0300->SetMarkerColor(2);
  gr_eff_mD0300->Draw("PL");
  leg->Draw("same");
  c->SaveAs("eff_mD0300.pdf","recreate");






}
     
