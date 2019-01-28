#include <algorithm>    // std::max
#include "TMath.h"
#include <math.h>

double My_dPhi (double phi1, double phi2) {
  double dPhi = phi1 - phi2;
  if (dPhi >  TMath::Pi()) dPhi -= 2*TMath::Pi();
  if (dPhi <  -TMath::Pi()) dPhi += 2*TMath::Pi();
  return dPhi;
}

void eff_pergamD2DLxyLz(){


  TFile *f[4];
  
  f[0] = new TFile("~/Dropbox/darksusy_plots/Anal2015data/MCsamples/DarkSUSY_mH_125_mGammaD_0300_cT_100_13TeV_RAW2DIGI_L1Reco_RECO_MCRUN2_74_V9_v1.root");


  
  TTree *t[4];

  Float_t ev_all[40]={0.0};

  Int_t is1GenMu17;
  Int_t is2GenMu8;
  Int_t is3GenMu8;
  Int_t is4GenMu8;
  
  Int_t is1SelMu17;
  Int_t is2SelMu8;
  Int_t is3SelMu8;
  Int_t is4SelMu8;

  Int_t nrecm;
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

 
  for(int l=0;l<1;l++){

    f[l]->cd("ana2012");
    
    t[l] = (TTree*)f[l]->Get("ana2012/Events");
    
    
    t[l]->SetBranchAddress("event",&event);
    t[l]->SetBranchAddress("2dimuon",&ev2dim);
    t[l]->SetBranchAddress("2mjets",&ev2mj);

    t[l]->SetBranchAddress("is1GenMu17",&is1GenMu17);
    t[l]->SetBranchAddress("is2GenMu8",&is2GenMu8);
    t[l]->SetBranchAddress("is3GenMu8",&is3GenMu8);
    t[l]->SetBranchAddress("is4GenMu8",&is4GenMu8);

    t[l]->SetBranchAddress("is1SelMu17",&is1SelMu17);
    t[l]->SetBranchAddress("is2SelMu8",&is2SelMu8);
    t[l]->SetBranchAddress("is3SelMu8",&is3SelMu8);
    t[l]->SetBranchAddress("is4SelMu8",&is4SelMu8);
    
    t[l]->SetBranchAddress("isVertexOK",&isVtxOK);
    t[l]->SetBranchAddress("is2DiMuonsDzOK",&is2DimDzOK);
    t[l]->SetBranchAddress("is2DiMuonsVtxOK",&is2DimVtxOK);
    t[l]->SetBranchAddress("is2DiMuonsMassOK",&is2DimMassOK);
    t[l]->SetBranchAddress("is2DiMuonsIsoTkOK",&is2DimIsoTkOK);
    t[l]->SetBranchAddress("is2DiMuonHLTFired",&is2DimHLTFired);

    t[l]->SetBranchAddress("is4GenMu8",&is4GenMu8);
    t[l]->SetBranchAddress("genA0_Lxy_rdet",&genA0_Lxy_rdet);
    t[l]->SetBranchAddress("genA1_Lxy_rdet",&genA1_Lxy_rdet);
    t[l]->SetBranchAddress("genA0_Lz_rdet",&genA0_Lz_rdet);
    t[l]->SetBranchAddress("genA1_Lz_rdet",&genA1_Lz_rdet);

    t[l]->SetBranchAddress("selMu0_phi",&selMu0_phi);
    t[l]->SetBranchAddress("selMu1_phi",&selMu1_phi);
    t[l]->SetBranchAddress("selMu2_phi",&selMu2_phi);
    t[l]->SetBranchAddress("selMu3_phi",&selMu3_phi);

    t[l]->SetBranchAddress("selMu0_eta",&selMu0_eta);
    t[l]->SetBranchAddress("selMu1_eta",&selMu1_eta);
    t[l]->SetBranchAddress("selMu2_eta",&selMu2_eta);
    t[l]->SetBranchAddress("selMu3_eta",&selMu3_eta);

    
    t[l]->SetBranchAddress("genA1_phi",&genA1_phi);
    t[l]->SetBranchAddress("genA1_eta",&genA1_eta);
    
    t[l]->SetBranchAddress("genA0_phi",&genA0_phi);
    t[l]->SetBranchAddress("genA0_eta",&genA0_eta);
    
    t[l]->SetBranchAddress("nrecm",&nrecm);
    t[l]->SetBranchAddress("npatm",&npatm);
    
    t[l]->SetBranchAddress("muJetC_hitpix",&muJetChit);
    t[l]->SetBranchAddress("muJetF_hitpix",&muJetFhit);
    
    t[l]->SetBranchAddress("muJetC_hitpix_genTrk",&muJetChitgt);
    t[l]->SetBranchAddress("muJetF_hitpix_genTrk",&muJetFhitgt);
    
    t[l]->SetBranchAddress("muJetC_vtx_x",&muJetC_vtx_x);
    t[l]->SetBranchAddress("muJetC_vtx_y",&muJetC_vtx_y);
    t[l]->SetBranchAddress("muJetC_vtx_z",&muJetC_vtx_z);
    
    t[l]->SetBranchAddress("muJetF_vtx_x",&muJetF_vtx_x);
    t[l]->SetBranchAddress("muJetF_vtx_y",&muJetF_vtx_y);
    t[l]->SetBranchAddress("muJetF_vtx_z",&muJetF_vtx_z);

    t[l]->SetBranchAddress("muJetC_mindisttracks",&muJetC_mindisttrk);
    t[l]->SetBranchAddress("muJetF_mindisttracks",&muJetF_mindisttrk);
    
    t[l]->SetBranchAddress("muJetC_validVtx",&muJetC_validVtx);
    t[l]->SetBranchAddress("muJetC_validVtx_fitted",&muJetC_validVtx_fitted);
    t[l]->SetBranchAddress("muJetC_validVtx_mindist",&muJetC_validVtx_mindist);
    
    t[l]->SetBranchAddress("muJetF_validVtx",&muJetF_validVtx);
    t[l]->SetBranchAddress("muJetF_validVtx_fitted",&muJetF_validVtx_fitted);
    t[l]->SetBranchAddress("muJetF_validVtx_mindist",&muJetF_validVtx_mindist);


    Int_t nentries = t[l]->GetEntries();
    
    
    Float_t bin_edges[41]={0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,78,80};
    Float_t bin_edges_Lz[21]={0,4,8,12,16,20,24,28,32,36,40,44,48,52,56,60,64,68,72,76,80};
    
    
    Float_t count_gam_A0[20][40];
    Float_t count_rec_A0[20][40];
    Float_t eff_A0[20][40];
    
    Float_t count_gam_A1[20][40];
    Float_t count_rec_A1[20][40];
    Float_t eff_A1[20][40];      
    
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

      
    TH1F *dZ_limit_A0mu0  = new TH1F("dZ_limit_A0mu0","dZ_limit_A0mu0",100,0.0,50.0);
    TH1F *dZ_limit_A0mu1  = new TH1F("dZ_limit_A0mu1","dZ_limit_A0mu1",100,0.0,50.0);
    TH1F *dZ_limit_A1mu0  = new TH1F("dZ_limit_A1mu0","dZ_limit_A1mu0",100,0.0,50.0);
    TH1F *dZ_limit_A1mu1  = new TH1F("dZ_limit_A1mu1","dZ_limit_A1mu1",100,0.0,50.0);
      
    TH1F *dZ_A0mu0  = new TH1F("dZ_A0mu0","dZ_A0mu0",100,0.0,200.0);
    TH1F *dZ_A0mu1  = new TH1F("dZ_A0mu1","dZ_A0mu1",100,0.0,200.0);
    TH1F *dZ_A1mu0  = new TH1F("dZ_A1mu0","dZ_A1mu0",100,0.0,200.0);
    TH1F *dZ_A1mu1  = new TH1F("dZ_A1mu1","dZ_A1mu1",100,0.0,200.0);
      
    TH1F *R_A0mu0  = new TH1F("R_A0mu0","R_A0mu0",100,0.0,400.0);
    TH1F *R_A0mu1  = new TH1F("R_A0mu1","R_A0mu1",100,0.0,400.0);
    TH1F *R_A1mu0  = new TH1F("R_A1mu0","R_A1mu0",100,0.0,400.0);
    TH1F *R_A1mu1  = new TH1F("R_A1mu1","R_A1mu1",100,0.0,400.0);
      
      
    TH1F *Rnew_A0mu0  = new TH1F("Rnew_A0mu0","Rnew_A0mu0",200,0.0,400.0);
    TH1F *Rnew_A0mu1  = new TH1F("Rnew_A0mu1","Rnew_A0mu1",200,0.0,400.0);
    TH1F *Rnew_A1mu0  = new TH1F("Rnew_A1mu0","Rnew_A1mu0",200,0.0,400.0);
    TH1F *Rnew_A1mu1  = new TH1F("Rnew_A1mu1","Rnew_A1mu1",200,0.0,400.0);
      
    TH2F *R_dZ_limit_A0mu0  = new TH2F("R_dZ_limit_A0mu0","R_dZ_limit_A0mu0",100,0.0,50.0,100,0.0,200);
    TH2F *R_dZ_limit_A0mu1  = new TH2F("R_dZ_limit_A0mu1","R_dZ_limit_A0mu1",100,0.0,50.0,100,0.0,200);
    TH2F *R_dZ_limit_A1mu0  = new TH2F("R_dZ_limit_A1mu0","R_dZ_limit_A1mu0",100,0.0,50.0,100,0.0,200);
    TH2F *R_dZ_limit_A1mu1  = new TH2F("R_dZ_limit_A1mu1","R_dZ_limit_A1mu1",100,0.0,50.0,100,0.0,200);
      
      
    TH2F *Rnew_A0mu0_A0eta = new TH2F("Rnew_A0mu0_A0eta","Rnew_A0mu0_A0eta",100,0.0,4.0,100,0.0,600.0);
    TH1F *A0eta = new TH1F("A0eta","A0eta",100,0.0,4.0);
      
    for(int k=0;k<nentries;k++){
      t[l]->GetEntry(k);
	
      if(is4GenMu8==1){
	Float_t dphi_gD = My_dPhi(genA1_phi,genA0_phi);

	if(fabs(dphi_gD)>2.5){


	  for(int n=0;n<20;n++){
	    if(fabs(genA0_Lz_rdet)>bin_edges_Lz[n] && fabs(genA0_Lz_rdet)<bin_edges_Lz[n+1]){
	    
	      for(int m=0;m<40;m++){
		if(genA0_Lxy_rdet>bin_edges[m] && genA0_Lxy_rdet<bin_edges[m+1]){
		  count_gam_A0[n][m]++;
	      
		  // Int_t nrecm=0;
		  // if(is1SelMu17==1) nrecm=1;
		  // if(is2SelMu8==1) nrecm=2;
		  // if(is3SelMu8==1) nrecm=3;
		  // if(is4SelMu8==1) nrecm=4;

		  //		  if(nrecm>=2){

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
		      //		    dR_A0->Fill(dR1);
		      if(dR1<0.5) match_mu++;
		    }
		    if(match_mu>=2)   count_rec_A0[n][m]++;
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
	      

		  if(npatm>=2 && is2SelMu8){
		    //		  if(npatm>=2){
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
		      //		    dR_A1->Fill(dR1);
		      if(dR1<0.5) match_mu++;
		    }
		    if(match_mu>=2) count_rec_A1[n][m]++;

		  }
		}
	      }
	    }
	  }

	}
      }
    }


    TH2F *den_2D_A0 = new TH2F("den_2D_A0","den_2D_A0",20,0,80,40,0.0,80.0);
    // TH2F *den_2D_A1 = new TH2F("den_2D_A1","den_2D_A1",25,0,30,15,0.0,48);
    
    
    
    TH2F *num_2D_A0 = new TH2F("num_2D_A0","num_2D_A0",20,0,80,40,0.0,80.0);
    // TH2F *num_2D_A1 = new TH2F("num_2D_A1","num_2D_A1",25,0,30,15,0.0,48);
    
    

    
    TH2F *eff_2D_A0 = new TH2F("eff_2D_A0","eff_2D_A0",20,0,80,40,0.0,80.0);
    TH2F *eff_2D_A1 = new TH2F("eff_2D_A1","eff_2D_A1",20,0,80,40,0.0,80.0);
    
    // TH2F *eff_2D_A0 = new TH2F("eff_2D_A0","eff_2D_A0",25,0,30,15,0.0,48);
    // TH2F *eff_2D_A1 = new TH2F("eff_2D_A1","eff_2D_A1",25,0,30,15,0.0,48);
    
    for(int k=0;k<20;k++){
      for(int j=0;j<40;j++){

	num_2D_A0->SetBinContent(k+1,j+1,count_rec_A0[k][j]);
	// num_2D_A1->SetBinContent(k+1,j+1,count_rec_A1[k][j]);

	den_2D_A0->SetBinContent(k+1,j+1,count_gam_A0[k][j]);
	// den_2D_A1->SetBinContent(k+1,j+1,count_gam_A1[k][j]);
      

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
    //    gStyle->SetPalette(53);

    // UInt_t Number = 3;
    // Double_t Red[3]    = { 1.00, 0.00, 0.00};
    // Double_t Green[3]  = { 0.00, 1.00, 0.00};
    // Double_t Blue[3]   = { 1.00, 0.00, 1.00};
    // Double_t Length[3] = { 0.80, 0.50, 0.20 };
    Int_t nb=50;
    TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,nb);

    Int_t colors[] = {0,1,2,3,4,5,6}; // #colors >= #levels - 1
    gStyle->SetPalette((sizeof(colors)/sizeof(Int_t)), colors);
    
    //#levels <= #colors + 1 (notes: +-3.4e38 = +-FLT_MAX; +1.17e-38 = +FLT_MIN)
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
    //    eff_2D_A0->SetContour((sizeof(levels)/sizeof(Double_t)), levels);
    eff_2D_A0->Draw("COLZ");

    if(l==0) c->SaveAs("eff_2D_LxyLz_A0_ct05.pdf","recreate");




    TCanvas *c1 = new TCanvas("c1","c1",700,500);
    c1->SetRightMargin(0.15);
    eff_2D_A1->GetYaxis()->SetTitle("#gamma_{D2} Lxy [cm]");
    eff_2D_A1->GetXaxis()->SetTitle("|#gamma_{D2} Lz| [cm]");
    eff_2D_A1->GetZaxis()->SetTitle("Eff_{rec}/accep_{gen}");
    eff_2D_A1->Draw("COLZ");
    if(l==0) c1->SaveAs("eff_2D_LxyLz_A1_ct05.pdf","recreate");


  

  }
}
