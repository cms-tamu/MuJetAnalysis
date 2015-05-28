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
  
  f[0] = new TFile("DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_200_RAW2DIGI_L1Reco_RECO_v1.root");
  
  TTree *t[4];
  
  for(int l=0;l<1;l++){

    f[l]->cd("ana2012");
    
    t[l] = (TTree*)f[l]->Get("ana2012/Events");
    
    Int_t   event;
    Float_t beamSpot_x;
    Float_t beamSpot_y;
    Float_t beamSpot_z;
    Int_t   numrecm;
    Int_t   numgenA;
    Int_t   num17GeVm;
    Int_t   num8GeVm;
    Int_t is4GenMu8;
    Int_t is1SelMu17;
    Int_t is2SelMu8;
    Int_t is3SelMu8;
    Int_t is4SelMu8;
    
    
    Float_t genA1_vz;
    Float_t genA0_vz;
    Float_t genA1_vz_rorig;
    Float_t genA0_vz_rorig;
    Float_t genA0_Lxy;
    Float_t genA1_Lxy;
    Float_t genA0_Lxy_rdet;
    Float_t genA1_Lxy_rdet;
    Float_t genA0_Lz_rdet;
    Float_t genA1_Lz_rdet;

    Float_t genA0_eta;
    Float_t genA0_phi;
    Float_t genA0Mu0_px;
    Float_t genA0Mu0_py;
    Float_t genA0Mu0_pz;
    Float_t genA0Mu1_px;
    Float_t genA0Mu1_py;
    Float_t genA0Mu1_pz;
    Float_t genA0Mu0_vx;
    Float_t genA0Mu0_vy;
    Float_t genA0Mu0_vz;
    Float_t genA0Mu1_vx;
    Float_t genA0Mu1_vy;
    Float_t genA0Mu1_vz;


    Float_t genA0Mu0_vx_rorig;
    Float_t genA0Mu0_vy_rorig;
    Float_t genA0Mu0_vz_rorig;
    Float_t genA0Mu1_vx_rorig;
    Float_t genA0Mu1_vy_rorig;
    Float_t genA0Mu1_vz_rorig;

    Float_t genA0Mu0_eta;
    Float_t genA0Mu1_eta;

    Float_t genA1_eta;
    Float_t genA1_phi;
    Float_t genA1Mu0_px;
    Float_t genA1Mu0_py;
    Float_t genA1Mu0_pz;
    Float_t genA1Mu1_px;
    Float_t genA1Mu1_py;
    Float_t genA1Mu1_pz;

    Float_t genA1Mu0_vx;
    Float_t genA1Mu0_vy;
    Float_t genA1Mu0_vz;
    Float_t genA1Mu1_vx;
    Float_t genA1Mu1_vy;
    Float_t genA1Mu1_vz;

    Float_t genA1Mu0_vx_rorig;
    Float_t genA1Mu0_vy_rorig;
    Float_t genA1Mu0_vz_rorig;
    Float_t genA1Mu1_vx_rorig;
    Float_t genA1Mu1_vy_rorig;
    Float_t genA1Mu1_vz_rorig;
    Float_t genA1Mu0_eta;
    Float_t genA1Mu1_eta;

    Float_t selMu0_px;
    Float_t selMu0_py;
    Float_t selMu1_px;
    Float_t selMu1_py;
    Float_t selMu2_px;
    Float_t selMu2_py;
    Float_t selMu3_px;
    Float_t selMu3_py;

    Float_t selMu0_eta;
    Float_t selMu1_eta;
    Float_t selMu2_eta;
    Float_t selMu3_eta;
    Float_t selMu0_phi;
    Float_t selMu1_phi;
    Float_t selMu2_phi;
    Float_t selMu3_phi;

 
    t[l]->SetBranchAddress("event",&event);

    t[l]->SetBranchAddress("beamSpot_x",&beamSpot_x);
    t[l]->SetBranchAddress("beamSpot_y",&beamSpot_y);
    t[l]->SetBranchAddress("beamSpot_z",&beamSpot_z);
    t[l]->SetBranchAddress("numgenA",&numgenA);
    t[l]->SetBranchAddress("npatm",&numrecm);
    t[l]->SetBranchAddress("num17GeVm",&num17GeVm);
    t[l]->SetBranchAddress("num8GeVm", &num8GeVm);
    t[l]->SetBranchAddress("is4GenMu8", &is4GenMu8);
    t[l]->SetBranchAddress("is1SelMu17", &is1SelMu17);
    t[l]->SetBranchAddress("is2SelMu8", &is2SelMu8);
    t[l]->SetBranchAddress("is3SelMu8", &is3SelMu8);
    t[l]->SetBranchAddress("is4SelMu8", &is4SelMu8);
    t[l]->SetBranchAddress("genA0_Lxy", &genA0_Lxy);
    t[l]->SetBranchAddress("genA1_Lxy", &genA1_Lxy);
    t[l]->SetBranchAddress("genA0_Lxy_rdet", &genA0_Lxy_rdet);
    t[l]->SetBranchAddress("genA1_Lxy_rdet", &genA1_Lxy_rdet);
    t[l]->SetBranchAddress("genA0_Lz_rdet", &genA0_Lz_rdet);
    t[l]->SetBranchAddress("genA1_Lz_rdet", &genA1_Lz_rdet);

    t[l]->SetBranchAddress("genA0_vz",   &genA0_vz);
    t[l]->SetBranchAddress("genA1_vz",   &genA1_vz);

    t[l]->SetBranchAddress("genA0_vz_rorig",   &genA0_vz_rorig);
    t[l]->SetBranchAddress("genA1_vz_rorig",   &genA1_vz_rorig);

    t[l]->SetBranchAddress("genA0_eta",   &genA0_eta);
    t[l]->SetBranchAddress("genA0_phi",   &genA0_phi);
    t[l]->SetBranchAddress("genA0Mu0_eta",&genA0Mu0_eta);
    t[l]->SetBranchAddress("genA0Mu1_eta",&genA0Mu1_eta);
    t[l]->SetBranchAddress("genA0Mu0_px", &genA0Mu0_px);
    t[l]->SetBranchAddress("genA0Mu0_py", &genA0Mu0_py);
    t[l]->SetBranchAddress("genA0Mu0_pz", &genA0Mu0_pz);
    t[l]->SetBranchAddress("genA0Mu1_px", &genA0Mu1_px);
    t[l]->SetBranchAddress("genA0Mu1_py", &genA0Mu1_py);
    t[l]->SetBranchAddress("genA0Mu1_pz", &genA0Mu1_pz);

    t[l]->SetBranchAddress("genA0Mu0_vx", &genA0Mu0_vx);
    t[l]->SetBranchAddress("genA0Mu0_vy", &genA0Mu0_vy);
    t[l]->SetBranchAddress("genA0Mu0_vz", &genA0Mu0_vz);
    t[l]->SetBranchAddress("genA0Mu1_vx", &genA0Mu1_vx);
    t[l]->SetBranchAddress("genA0Mu1_vy", &genA0Mu1_vy);
    t[l]->SetBranchAddress("genA0Mu1_vz", &genA0Mu1_vz);

    t[l]->SetBranchAddress("genA0Mu0_vx_rorig", &genA0Mu0_vx_rorig);
    t[l]->SetBranchAddress("genA0Mu0_vy_rorig", &genA0Mu0_vy_rorig);
    t[l]->SetBranchAddress("genA0Mu0_vz_rorig", &genA0Mu0_vz_rorig);
    t[l]->SetBranchAddress("genA0Mu1_vx_rorig", &genA0Mu1_vx_rorig);
    t[l]->SetBranchAddress("genA0Mu1_vy_rorig", &genA0Mu1_vy_rorig);
    t[l]->SetBranchAddress("genA0Mu1_vz_rorig", &genA0Mu1_vz_rorig);

    t[l]->SetBranchAddress("genA1_eta",   &genA1_eta);
    t[l]->SetBranchAddress("genA1_phi",   &genA1_phi);
    t[l]->SetBranchAddress("genA1Mu0_eta",&genA1Mu0_eta);
    t[l]->SetBranchAddress("genA1Mu1_eta",&genA1Mu1_eta);
    t[l]->SetBranchAddress("genA1Mu0_px", &genA1Mu0_px);
    t[l]->SetBranchAddress("genA1Mu0_py", &genA1Mu0_py);
    t[l]->SetBranchAddress("genA1Mu0_pz", &genA1Mu0_pz);
    t[l]->SetBranchAddress("genA1Mu1_px", &genA1Mu1_px);
    t[l]->SetBranchAddress("genA1Mu1_py", &genA1Mu1_py);
    t[l]->SetBranchAddress("genA1Mu1_pz", &genA1Mu1_pz);


    t[l]->SetBranchAddress("genA1Mu0_vx", &genA1Mu0_vx);
    t[l]->SetBranchAddress("genA1Mu0_vy", &genA1Mu0_vy);
    t[l]->SetBranchAddress("genA1Mu0_vz", &genA1Mu0_vz);
    t[l]->SetBranchAddress("genA1Mu1_vx", &genA1Mu1_vx);
    t[l]->SetBranchAddress("genA1Mu1_vy", &genA1Mu1_vy);
    t[l]->SetBranchAddress("genA1Mu1_vz", &genA1Mu1_vz);


    t[l]->SetBranchAddress("genA1Mu0_vx_rorig", &genA1Mu0_vx_rorig);
    t[l]->SetBranchAddress("genA1Mu0_vy_rorig", &genA1Mu0_vy_rorig);
    t[l]->SetBranchAddress("genA1Mu0_vz_rorig", &genA1Mu0_vz_rorig);
    t[l]->SetBranchAddress("genA1Mu1_vx_rorig", &genA1Mu1_vx_rorig);
    t[l]->SetBranchAddress("genA1Mu1_vy_rorig", &genA1Mu1_vy_rorig);
    t[l]->SetBranchAddress("genA1Mu1_vz_rorig", &genA1Mu1_vz_rorig);


    t[l]->SetBranchAddress("selMu0_eta",&selMu0_eta);
    t[l]->SetBranchAddress("selMu1_eta",&selMu1_eta);
    t[l]->SetBranchAddress("selMu2_eta",&selMu2_eta);
    t[l]->SetBranchAddress("selMu3_eta",&selMu3_eta);
    t[l]->SetBranchAddress("selMu0_phi",&selMu0_phi);
    t[l]->SetBranchAddress("selMu1_phi",&selMu1_phi);
    t[l]->SetBranchAddress("selMu2_phi",&selMu2_phi);
    t[l]->SetBranchAddress("selMu3_phi",&selMu3_phi);
  
    t[l]->SetBranchAddress("selMu0_px",&selMu0_px);
    t[l]->SetBranchAddress("selMu0_py",&selMu0_py);
    t[l]->SetBranchAddress("selMu1_px",&selMu1_px);
    t[l]->SetBranchAddress("selMu1_py",&selMu1_py);
    t[l]->SetBranchAddress("selMu2_px",&selMu2_px);
    t[l]->SetBranchAddress("selMu2_py",&selMu2_py);
    t[l]->SetBranchAddress("selMu3_px",&selMu3_px);
    t[l]->SetBranchAddress("selMu3_py",&selMu3_py);

    Int_t nentries = t[l]->GetEntries();
  
  
    for(int p=0;p<1;p++){

      
      // Float_t bin_edges[41]={0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,78,80};
      // Float_t bin_edges_Lz[21]={0,4,8,12,16,20,24,28,32,36,40,44,48,52,56,60,64,68,72,76,80};
      
      Float_t bin_edges[21]={0,4,8,12,16,20,24,28,32,36,40,44,48,52,56,60,64,68,72,76,80};
      Float_t bin_edges_Lz[11]={0,8,16,24,32,40,48,56,64,72,80};
      
      Float_t count_gam_A0[20][40];
      Float_t count_rec_A0[20][40];
      Float_t eff_A0[20][40];
      
      Float_t count_gam_A1[20][40];
      Float_t count_rec_A1[20][40];
      Float_t eff_A1[20][40];      
  
      for(int k=0;k<10;k++){
	for(int j=0;j<20;j++){
	  count_gam_A0[k][j]=0.0;
	  count_rec_A0[k][j]=0.0;
	  eff_A0[k][j]=0.0;
      
	  count_gam_A1[k][j]=0.0;
	  count_rec_A1[k][j]=0.0;
	  eff_A1[k][j]=0.0;
	}
      }      


      cout<<" sample "<<l<<"  nentries  "<<nentries<<endl;


      // TH1F *dR_A0 = new TH1F("dR_A0","dR_A0",500,0.0,4.0);
      // TH1F *dR_A1 = new TH1F("dR_A1","dR_A1",500,0.0,4.0);
  

      // TH1F *dZ_limit_A0mu0  = new TH1F("dZ_limit_A0mu0","dZ_limit_A0mu0",100,0.0,50.0);
      // TH1F *dZ_limit_A0mu1  = new TH1F("dZ_limit_A0mu1","dZ_limit_A0mu1",100,0.0,50.0);
      // TH1F *dZ_limit_A1mu0  = new TH1F("dZ_limit_A1mu0","dZ_limit_A1mu0",100,0.0,50.0);
      // TH1F *dZ_limit_A1mu1  = new TH1F("dZ_limit_A1mu1","dZ_limit_A1mu1",100,0.0,50.0);

      // TH1F *dZ_A0mu0  = new TH1F("dZ_A0mu0","dZ_A0mu0",100,0.0,200.0);
      // TH1F *dZ_A0mu1  = new TH1F("dZ_A0mu1","dZ_A0mu1",100,0.0,200.0);
      // TH1F *dZ_A1mu0  = new TH1F("dZ_A1mu0","dZ_A1mu0",100,0.0,200.0);
      // TH1F *dZ_A1mu1  = new TH1F("dZ_A1mu1","dZ_A1mu1",100,0.0,200.0);

      // TH1F *R_A0mu0  = new TH1F("R_A0mu0","R_A0mu0",100,0.0,400.0);
      // TH1F *R_A0mu1  = new TH1F("R_A0mu1","R_A0mu1",100,0.0,400.0);
      // TH1F *R_A1mu0  = new TH1F("R_A1mu0","R_A1mu0",100,0.0,400.0);
      // TH1F *R_A1mu1  = new TH1F("R_A1mu1","R_A1mu1",100,0.0,400.0);


      // TH1F *Rnew_A0mu0  = new TH1F("Rnew_A0mu0","Rnew_A0mu0",200,0.0,400.0);
      // TH1F *Rnew_A0mu1  = new TH1F("Rnew_A0mu1","Rnew_A0mu1",200,0.0,400.0);
      // TH1F *Rnew_A1mu0  = new TH1F("Rnew_A1mu0","Rnew_A1mu0",200,0.0,400.0);
      // TH1F *Rnew_A1mu1  = new TH1F("Rnew_A1mu1","Rnew_A1mu1",200,0.0,400.0);

      // TH2F *R_dZ_limit_A0mu0  = new TH2F("R_dZ_limit_A0mu0","R_dZ_limit_A0mu0",100,0.0,50.0,100,0.0,200);
      // TH2F *R_dZ_limit_A0mu1  = new TH2F("R_dZ_limit_A0mu1","R_dZ_limit_A0mu1",100,0.0,50.0,100,0.0,200);
      // TH2F *R_dZ_limit_A1mu0  = new TH2F("R_dZ_limit_A1mu0","R_dZ_limit_A1mu0",100,0.0,50.0,100,0.0,200);
      // TH2F *R_dZ_limit_A1mu1  = new TH2F("R_dZ_limit_A1mu1","R_dZ_limit_A1mu1",100,0.0,50.0,100,0.0,200);


      // TH2F *Rnew_A0mu0_A0eta = new TH2F("Rnew_A0mu0_A0eta","Rnew_A0mu0_A0eta",100,0.0,4.0,100,0.0,600.0);
      // TH1F *A0eta = new TH1F("A0eta","A0eta",100,0.0,4.0);
    

      
      for(int k=0;k<nentries;k++){
	t[l]->GetEntry(k);

	cout<<" entry   "<<k<<endl;



	if(is4GenMu8==1){
	  
	  // cout<<"  4 GenMuons  "<<endl;

	  // cout<<" gen A0 phi   "<<genA0_phi<<" gen A0 phi  "<<genA1_phi<<endl;
	  
	  Float_t dphi_gD = My_dPhi(genA1_phi,genA0_phi);
	  

	  //	  cout<<" delta phi   "<<dphi_gD<<endl;
	  
	  if(fabs(dphi_gD)>=1.5){


	    cout<<" well separated dark photons  "<<endl;
	    
	    //  if(fabs(dphi_gD)>2.5 && fabs(genA0_eta)<2.4 && fabs(genA1_eta)<2.4){


	    // Float_t ptmagA1Mu0 = sqrt(pow(genA1Mu0_px,2)+pow(genA1Mu0_py,2));
	    // Float_t ptmagA1Mu1 = sqrt(pow(genA1Mu1_px,2)+pow(genA1Mu1_py,2));
	  
	    // Float_t ptmagA0Mu0 = sqrt(pow(genA0Mu0_px,2)+pow(genA0Mu0_py,2));
	    // Float_t ptmagA0Mu1 = sqrt(pow(genA0Mu1_px,2)+pow(genA0Mu1_py,2));
	  

	    // Float_t refpoint_z = 34.0;
	    // Float_t refpoint_R = 6.2;

	    // Float_t A1mu0_z =(genA1Mu0_vz_rorig-refpoint_z) - ((genA1Mu0_vx_rorig)*genA1Mu0_px+(genA1Mu0_vy_rorig)*genA1Mu0_py)/ptmagA1Mu0 * genA1Mu0_pz/ptmagA1Mu0;
	    // Float_t A1mu1_z =(genA1Mu1_vz_rorig-refpoint_z) - ((genA1Mu1_vx_rorig)*genA1Mu1_px+(genA1Mu1_vy_rorig)*genA1Mu1_py)/ptmagA1Mu1 * genA1Mu1_pz/ptmagA1Mu1;
	  
	    // Float_t A0mu0_z =(genA0Mu0_vz_rorig-refpoint_z) - ((genA0Mu0_vx_rorig)*genA0Mu0_px+(genA0Mu0_vy_rorig)*genA0Mu0_py)/ptmagA0Mu0 * genA0Mu0_pz/ptmagA0Mu0;
	    // Float_t A0mu1_z =(genA0Mu1_vz_rorig-refpoint_z) - ((genA0Mu1_vx_rorig)*genA0Mu1_px+(genA0Mu1_vy_rorig)*genA0Mu1_py)/ptmagA0Mu1 * genA0Mu1_pz/ptmagA0Mu1;

	    // Float_t A0mu0_lxy = (genA0Mu0_vx_rorig*genA0Mu0_px + genA0Mu0_vy_rorig*genA0Mu0_py)/ptmagA0Mu0;
	    // Float_t A0mu1_lxy = (genA0Mu1_vx_rorig*genA0Mu1_px + genA0Mu1_vy_rorig*genA0Mu1_py)/ptmagA0Mu1;
	    // Float_t A1mu0_lxy = (genA1Mu0_vx_rorig*genA1Mu0_px + genA1Mu0_vy_rorig*genA1Mu0_py)/ptmagA1Mu0;
	    // Float_t A1mu1_lxy = (genA1Mu1_vx_rorig*genA1Mu1_px + genA1Mu1_vy_rorig*genA1Mu1_py)/ptmagA1Mu1;

	    // //	  Float_t A0mu0_R = sqrt(pow(genA0Mu0_vx_rorig,2)+pow(genA0Mu0_vy_rorig,2));

	    // if(fabs(A0mu0_z)<10.0) cout<<" A0mu0 vz  "<<genA0Mu0_vz_rorig<<"  A0mu0 z=34 cm  "<<A0mu0_z<<endl;

	    // dZ_limit_A0mu0->Fill(fabs(A0mu0_z)-34);
	    // dZ_limit_A0mu1->Fill(fabs(A0mu1_z)-34);
	    // dZ_limit_A1mu0->Fill(fabs(A1mu0_z)-34);
	    // dZ_limit_A1mu1->Fill(fabs(A1mu1_z)-34);

	    // dZ_A0mu0->Fill(fabs(genA0Mu0_vz_rorig));
	    // dZ_A0mu1->Fill(fabs(genA0Mu1_vz_rorig));
	    // dZ_A1mu0->Fill(fabs(genA1Mu0_vz_rorig));
	    // dZ_A1mu1->Fill(fabs(genA1Mu1_vz_rorig));
	  
	    // R_A0mu0->Fill(A0mu0_lxy);
	    // R_A0mu1->Fill(A0mu1_lxy);
	    // R_A1mu0->Fill(A1mu0_lxy);
	    // R_A1mu1->Fill(A1mu1_lxy);

	    // R_dZ_limit_A0mu0->Fill(fabs(A0mu0_z)-34,fabs(A0mu0_lxy));
	    // R_dZ_limit_A0mu1->Fill(fabs(A0mu1_z)-34,fabs(A0mu1_lxy));
	    // R_dZ_limit_A1mu0->Fill(fabs(A1mu0_z)-34,fabs(A1mu0_lxy));
	    // R_dZ_limit_A1mu1->Fill(fabs(A1mu1_z)-34,fabs(A1mu1_lxy));

	    // A0eta->Fill(fabs(genA0_eta));



	    // Float_t A0mu0_newx = genA0Mu0_vx_rorig + genA0Mu0_px*( (34-fabs(genA0Mu0_vz_rorig))/genA0Mu0_pz);
	    // Float_t A0mu1_newx = genA0Mu1_vx_rorig + genA0Mu1_px*( (34-fabs(genA0Mu1_vz_rorig))/genA0Mu1_pz);
	    // Float_t A1mu0_newx = genA1Mu0_vx_rorig + genA1Mu0_px*( (34-fabs(genA1Mu0_vz_rorig))/genA1Mu0_pz);
	    // Float_t A1mu1_newx = genA1Mu1_vx_rorig + genA1Mu1_px*( (34-fabs(genA1Mu1_vz_rorig))/genA1Mu1_pz);

	    // Float_t A0mu0_newy = genA0Mu0_vy_rorig + genA0Mu0_py*( (34-fabs(genA0Mu0_vz_rorig))/genA0Mu0_pz);
	    // Float_t A0mu1_newy = genA0Mu1_vy_rorig + genA0Mu1_py*( (34-fabs(genA0Mu1_vz_rorig))/genA0Mu1_pz);
	    // Float_t A1mu0_newy = genA1Mu0_vy_rorig + genA1Mu0_py*( (34-fabs(genA1Mu0_vz_rorig))/genA1Mu0_pz);
	    // Float_t A1mu1_newy = genA1Mu1_vy_rorig + genA1Mu1_py*( (34-fabs(genA1Mu1_vz_rorig))/genA1Mu1_pz);


	    // Float_t A0mu0_newlxy = sqrt(pow(A0mu0_newx,2)+pow(A0mu0_newy,2));
	    // Float_t A0mu1_newlxy = sqrt(pow(A0mu1_newx,2)+pow(A0mu1_newy,2));
	    // Float_t A1mu0_newlxy = sqrt(pow(A1mu0_newx,2)+pow(A1mu0_newy,2));
	    // Float_t A1mu1_newlxy = sqrt(pow(A1mu1_newx,2)+pow(A1mu1_newy,2));

	    // Rnew_A0mu0->Fill(A0mu0_newlxy);
	    // Rnew_A0mu1->Fill(A0mu1_newlxy);
	    // Rnew_A1mu0->Fill(A1mu0_newlxy);
	    // Rnew_A1mu1->Fill(A1mu1_newlxy);

	    // Rnew_A0mu0_A0eta->Fill(fabs(genA0_eta),A0mu0_newlxy);


	    // // Float_t A1mu0_dxy = (-genA1Mu0_vx_rorig*genA1Mu0_py + genA1Mu0_vy_rorig*genA1Mu0_px)/ptmagA1Mu0;
	    // // Float_t A1mu1_dxy = (-genA1Mu1_vx_rorig*genA1Mu1_py + genA1Mu1_vy_rorig*genA1Mu1_px)/ptmagA1Mu1;
	  
	    // //	  Float_t A0mu0_dxy = (-genA0Mu0_vx_rorig*genA0Mu0_py + genA0Mu0_vy_rorig*genA0Mu0_px)/ptmagA0Mu0;
	    // // Float_t A0mu1_dxy = (-genA0Mu1_vx_rorig*genA0Mu1_py + genA0Mu1_vy_rorig*genA0Mu1_px)/ptmagA0Mu1;


	    // // cout<<" genA1_phi  "<<genA1_phi<<endl;
	    // // cout<<" genA0 phi   "<<genA0_phi<<endl;
	    // // cout<<" dphi   "<<dphi_gD<<endl;
	

	    // bool A0muoncut;
	    // bool fiducial_cut;


	  
	    // A0muoncut=false;
	    // fiducial_cut=false;


	    // if(A0mu0_newlxy>6.0 && A0mu1_newlxy>6.0) A0muoncut=true;
	  


	    if(p==0) fiducial_cut=true;
	    // if(p==1 && genA0_Lxy_rdet<22.0 && fabs(genA0_Lz_rdet)<34.0) fiducial_cut=true;
	    // if(p==2 && fabs(genA0_eta)<2.4) fiducial_cut=true;
	    // if(p==3 && fabs(genA0_eta)<2.4 && genA0_Lxy_rdet<22.0 && fabs(genA0_Lz_rdet)<34.0) fiducial_cut=true;
	    // if(p==4 && A0muoncut && genA0_Lxy_rdet<22.0 && fabs(genA0_Lz_rdet)<34.0) fiducial_cut=true;
	  
	    
	    if(fiducial_cut){

	      cout<<" inside fiducial cut   "<<endl;
	      
	      for(int n=0;n<10;n++){
		if(fabs(genA0_Lz_rdet)>bin_edges_Lz[n] && fabs(genA0_Lz_rdet)<bin_edges_Lz[n+1]){
	    
		  for(int m=0;m<20;m++){
		    if(genA0_Lxy_rdet>bin_edges[m] && genA0_Lxy_rdet<bin_edges[m+1]){
		      count_gam_A0[n][m]++;
	      
		      // Int_t nrecm=0;
		      // if(is1SelMu17==1) nrecm=1;
		      // if(is2SelMu8==1) nrecm=2;
		      // if(is3SelMu8==1) nrecm=3;
		      // if(is4SelMu8==1) nrecm=4;

		      if(numrecm>=2){

			cout<<" number of rec muons   "<<numrecm<<endl;
			//		      if(numrecm>=2 && num8GeVm>=2){

			Float_t dR1=0.0;
			Float_t dphi1=0.0;
			Float_t deta1=0.0;
		  
			Int_t match_mu=0;
			for(int j=0;j<numrecm;j++){
			  
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


	      for(int n=0;n<10;n++){
		if(fabs(genA1_Lz_rdet)>bin_edges_Lz[n] && fabs(genA1_Lz_rdet)<bin_edges_Lz[n+1]){

		  for(int m=0;m<20;m++){
		    if(genA1_Lxy_rdet>bin_edges[m] && genA1_Lxy_rdet<bin_edges[m+1]){
		      count_gam_A1[n][m]++;
	      
		      // Int_t nrecm=0;
		      // if(is1SelMu17==1) nrecm=1;
		      // if(is2SelMu8==1) nrecm=2;
		      // if(is3SelMu8==1) nrecm=3;
		      // if(is4SelMu8==1) nrecm=4;

		      //		      if(numrecm>=2 && num8GeVm>=2){
		      if(numrecm>=2){
			Float_t dR1=0.0;
			Float_t dphi1=0.0;
			Float_t deta1=0.0;
		  
			Int_t match_mu=0;
			for(int j=0;j<numrecm;j++){	
	    
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
      
      }


      TH2F *den_2D_A0 = new TH2F("den_2D_A0","den_2D_A0",10,0,80,20,0.0,80.0);
      // TH2F *den_2D_A1 = new TH2F("den_2D_A1","den_2D_A1",25,0,30,15,0.0,48);



      TH2F *num_2D_A0 = new TH2F("num_2D_A0","num_2D_A0",10,0,80,20,0.0,80.0);
      // TH2F *num_2D_A1 = new TH2F("num_2D_A1","num_2D_A1",25,0,30,15,0.0,48);




      TH2F *eff_2D_A0 = new TH2F("eff_2D_A0","eff_2D_A0",10,0,80,20,0.0,80.0);
      TH2F *eff_2D_A1 = new TH2F("eff_2D_A1","eff_2D_A1",10,0,80,20,0.0,80.0);

      // TH2F *eff_2D_A0 = new TH2F("eff_2D_A0","eff_2D_A0",25,0,30,15,0.0,48);
      // TH2F *eff_2D_A1 = new TH2F("eff_2D_A1","eff_2D_A1",25,0,30,15,0.0,48);

      for(int k=0;k<10;k++){
	for(int j=0;j<20;j++){

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


	  eff_2D_A1->SetBinContent(k+1,j+1,eff_A1[k][j]);
	}
      }



      //    eff_2D_A0->GetZaxis()->SetRangeUser(0.0,1.0);
      //    eff_2D_A1->GetZaxis()->SetRangeUser(0.0,1.0);

      // UInt_t Number = 5;
      // Double_t Red[5]   = { 0.00, 0.09, 0.18, 0.09, 0.00 };
      // Double_t Green[5] = { 0.01, 0.02, 0.39, 0.68, 0.97 };
      // Double_t Blue[5]  = { 0.17, 0.39, 0.62, 0.79, 0.97 };
      // Double_t Length[5] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
      // //    gStyle->SetPalette(53);

      // // UInt_t Number = 3;
      // // Double_t Red[3]    = { 1.00, 0.00, 0.00};
      // // Double_t Green[3]  = { 0.00, 1.00, 0.00};
      // // Double_t Blue[3]   = { 1.00, 0.00, 1.00};
      // // Double_t Length[3] = { 0.80, 0.50, 0.20 };
      // Int_t nb=50;
      // TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,nb);

      // Int_t colors[] = {0,1,2,3,4,5,6}; // #colors >= #levels - 1
      // gStyle->SetPalette((sizeof(colors)/sizeof(Int_t)), colors);
    
      // //#levels <= #colors + 1 (notes: +-3.4e38 = +-FLT_MAX; +1.17e-38 = +FLT_MIN)
      // Double_t levels[] = {-10,0.0,0.2,0.4,0.6,0.8,1.0, 3.4e38}

      // eff_2D_A0->SetContour((sizeof(levels)/sizeof(Double_t)), levels);
  
      // const Int_t NRGBs = 5;
      // const Int_t NCont = 104;
    
      // Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
      // Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
      // Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
      // Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    
      // TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    
      // gStyle->SetNumberContours(NCont);

      //    eff_2D_A0->SetContour(NCont);


      TCanvas *c = new TCanvas("c","c",700,500);
      c->SetRightMargin(0.15);
      eff_2D_A0->GetYaxis()->SetTitle("#gamma_{D1} Lxy [cm]");
      eff_2D_A0->GetXaxis()->SetTitle("|#gamma_{D1} Lz| [cm]");
      eff_2D_A0->GetZaxis()->SetTitle("Eff_{rec}/accep_{gen}");
      //    eff_2D_A0->SetContour((sizeof(levels)/sizeof(Double_t)), levels);
      eff_2D_A0->Draw("COLZ");

      if(l==0) c->SaveAs("eff_2D_LxyLz_A0_ct01.pdf","recreate");
      if(l==1) c->SaveAs("eff_2D_LxyLz_A0_ct02.pdf","recreate");
      if(l==2) c->SaveAs("eff_2D_LxyLz_A0_ct1.pdf","recreate");
      if(l==3) c->SaveAs("eff_2D_LxyLz_A0_ct5.pdf","recreate");




      TCanvas *c1 = new TCanvas("c1","c1",700,500);
      c1->SetRightMargin(0.15);
      eff_2D_A1->GetYaxis()->SetTitle("#gamma_{D2} Lxy [cm]");
      eff_2D_A1->GetXaxis()->SetTitle("|#gamma_{D2} Lz| [cm]");
      eff_2D_A1->GetZaxis()->SetTitle("Eff_{rec}/accep_{gen}");
      eff_2D_A1->Draw("COLZ");
      if(l==0) c1->SaveAs("eff_2D_LxyLz_A1_ct01.pdf","recreate");
      if(l==1) c1->SaveAs("eff_2D_LxyLz_A1_ct02.pdf","recreate");
      if(l==2) c1->SaveAs("eff_2D_LxyLz_A1_ct1.pdf","recreate");
      if(l==3) c1->SaveAs("eff_2D_LxyLz_A1_ct5.pdf","recreate");


      // TCanvas *c2 = new TCanvas("c2","c2",700,500);
      // c2->SetRightMargin(0.15);
      // num_2D_A0->GetYaxis()->SetTitle("Lxy [cm]");
      // num_2D_A0->GetXaxis()->SetTitle("|Lz_{#gamma D_{2}}|");
      // num_2D_A0->Draw("COLZTEXT");
      // if(l==0) c2->SaveAs("num_2D_LxyLz_A0_ct01.pdf","recreate");
      // if(l==1) c2->SaveAs("num_2D_LxyLz_A0_ct02.pdf","recreate");
      // if(l==2) c2->SaveAs("num_2D_LxyLz_A0_ct1.pdf","recreate");
      // if(l==3) c2->SaveAs("num_2D_LxyLz_A0_ct5.pdf","recreate");

      // TCanvas *c3 = new TCanvas("c3","c3",700,500);
      // c3->SetRightMargin(0.15);
      // den_2D_A0->GetYaxis()->SetTitle("Lxy [cm]");
      // den_2D_A0->GetXaxis()->SetTitle("|Lz_{#gamma D_{2}}|");
      // den_2D_A0->Draw("COLZTEXT");

      // if(p==0){
      //   if(l==0) c3->SaveAs("den_2D_LxyLz_A0_ct01_nofid.pdf","recreate");
      //   if(l==1) c3->SaveAs("den_2D_LxyLz_A0_ct02_nofid.pdf","recreate");
      //   if(l==2) c3->SaveAs("den_2D_LxyLz_A0_ct1_nofid.pdf","recreate");
      //   if(l==3) c3->SaveAs("den_2D_LxyLz_A0_ct5_nofid.pdf","recreate");
      // }
      // if(p==1){
      //   if(l==0) c3->SaveAs("den_2D_LxyLz_A0_ct01_lxycut.pdf","recreate");
      //   if(l==1) c3->SaveAs("den_2D_LxyLz_A0_ct02_lxycut.pdf","recreate");
      //   if(l==2) c3->SaveAs("den_2D_LxyLz_A0_ct1_lxycut.pdf","recreate");
      //   if(l==3) c3->SaveAs("den_2D_LxyLz_A0_ct5_lxycut.pdf","recreate");
      // }
      // if(p==2){
      //   if(l==0) c3->SaveAs("den_2D_LxyLz_A0_ct01_etacut.pdf","recreate");
      //   if(l==1) c3->SaveAs("den_2D_LxyLz_A0_ct02_etacut.pdf","recreate");
      //   if(l==2) c3->SaveAs("den_2D_LxyLz_A0_ct1_etacut.pdf","recreate");
      //   if(l==3) c3->SaveAs("den_2D_LxyLz_A0_ct5_etacut.pdf","recreate");
      // }

      // if(p==3){
      //   if(l==0) c3->SaveAs("den_2D_LxyLz_A0_ct01_etacutlxylz.pdf","recreate");
      //   if(l==1) c3->SaveAs("den_2D_LxyLz_A0_ct02_etacutlxyz.pdf","recreate");
      //   if(l==2) c3->SaveAs("den_2D_LxyLz_A0_ct1_etacutlxylz.pdf","recreate");
      //   if(l==3) c3->SaveAs("den_2D_LxyLz_A0_ct5_etacutlxylz.pdf","recreate");
      // }

      // if(p==4){
      //   if(l==0) c3->SaveAs("den_2D_LxyLz_A0_ct01_muoncutlxylz.pdf","recreate");
      //   if(l==1) c3->SaveAs("den_2D_LxyLz_A0_ct02_muoncutlxyz.pdf","recreate");
      //   if(l==2) c3->SaveAs("den_2D_LxyLz_A0_ct1_muoncutlxylz.pdf","recreate");
      //   if(l==3) c3->SaveAs("den_2D_LxyLz_A0_ct5_muoncutlxylz.pdf","recreate");
      // }




      // TCanvas *c4 = new TCanvas("c4","c4",700,500);
      // c4->SetRightMargin(0.15);
      // num_2D_A0->GetYaxis()->SetTitle("Lxy [cm]");
      // num_2D_A0->GetXaxis()->SetTitle("|Lz_{#gamma D_{2}}|");
      // num_2D_A0->Draw("COLZTEXT");

      // if(p==0){
      //   if(l==0) c4->SaveAs("num_2D_LxyLz_A0_ct01_nofid.pdf","recreate");
      //   if(l==1) c4->SaveAs("num_2D_LxyLz_A0_ct02_nofid.pdf","recreate");
      //   if(l==2) c4->SaveAs("num_2D_LxyLz_A0_ct1_nofid.pdf","recreate");
      //   if(l==3) c4->SaveAs("num_2D_LxyLz_A0_ct5_nofid.pdf","recreate");
      // }
      // if(p==1){
      //   if(l==0) c4->SaveAs("num_2D_LxyLz_A0_ct01_lxycut.pdf","recreate");
      //   if(l==1) c4->SaveAs("num_2D_LxyLz_A0_ct02_lxycut.pdf","recreate");
      //   if(l==2) c4->SaveAs("num_2D_LxyLz_A0_ct1_lxycut.pdf","recreate");
      //   if(l==3) c4->SaveAs("num_2D_LxyLz_A0_ct5_lxycut.pdf","recreate");
      // }
      // if(p==2){
      //   if(l==0) c4->SaveAs("num_2D_LxyLz_A0_ct01_etacut.pdf","recreate");
      //   if(l==1) c4->SaveAs("num_2D_LxyLz_A0_ct02_etacut.pdf","recreate");
      //   if(l==2) c4->SaveAs("num_2D_LxyLz_A0_ct1_etacut.pdf","recreate");
      //   if(l==3) c4->SaveAs("num_2D_LxyLz_A0_ct5_etacut.pdf","recreate");
      // }

      // if(p==3){
      //   if(l==0) c4->SaveAs("num_2D_LxyLz_A0_ct01_etacutlxylz.pdf","recreate");
      //   if(l==1) c4->SaveAs("num_2D_LxyLz_A0_ct02_etacutlxyz.pdf","recreate");
      //   if(l==2) c4->SaveAs("num_2D_LxyLz_A0_ct1_etacutlxylz.pdf","recreate");
      //   if(l==3) c4->SaveAs("num_2D_LxyLz_A0_ct5_etacutlxylz.pdf","recreate");
      // }

      // if(p==4){
      //   if(l==0) c4->SaveAs("num_2D_LxyLz_A0_ct01_muoncutlxylz.pdf","recreate");
      //   if(l==1) c4->SaveAs("num_2D_LxyLz_A0_ct02_muoncutlxyz.pdf","recreate");
      //   if(l==2) c4->SaveAs("num_2D_LxyLz_A0_ct1_muoncutlxylz.pdf","recreate");
      //   if(l==3) c4->SaveAs("num_2D_LxyLz_A0_ct5_muoncutlxylz.pdf","recreate");
      // }

    }

    // TCanvas *c6 = new TCanvas("c6","c6",700,500);
    // c6->SetRightMargin(0.15);
    // num_2D_A1->GetXaxis()->SetTitle("Lxy [cm]");
    // num_2D_A1->GetYaxis()->SetTitle("|Lz_{#gamma D_{2}}|");
    // num_2D_A1->Draw("COLZTEXT");
    // if(l==0) c6->SaveAs("num_2D_A1_ct01.png","recreate");
    // if(l==1) c6->SaveAs("num_2D_A1_ct02.png","recreate");
    // if(l==2) c6->SaveAs("num_2D_A1_ct1.png","recreate");
    // if(l==3) c6->SaveAs("num_2D_A1_ct5.png","recreate");

    // TCanvas *c7 = new TCanvas("c2","c2",700,500);
    // c7->SetRightMargin(0.15);
    // den_2D_A1->GetXaxis()->SetTitle("Lxy [cm]");
    // den_2D_A1->GetYaxis()->SetTitle("|Lz_{#gamma D_{2}}|");
    // den_2D_A1->Draw("COLZTEXT");
    // if(l==0) c7->SaveAs("den_2D_A1_ct01.png","recreate");
    // if(l==1) c7->SaveAs("den_2D_A1_ct02.png","recreate");
    // if(l==2) c7->SaveAs("den_2D_A1_ct1.png","recreate");
    // if(l==3) c7->SaveAs("den_2D_A1_ct5.png","recreate");


    // TCanvas *c4 = new TCanvas("c4","c4",700,500);
    // dR_A0->Draw();
    // if(l==0) c4->SaveAs("dR_A0_ct01.png","recreate");
    // if(l==1) c4->SaveAs("dR_A0_ct02.png","recreate");
    // if(l==2) c4->SaveAs("dR_A0_ct1.png","recreate");
    // if(l==3) c4->SaveAs("dR_A0_ct5.png","recreate");

    // TCanvas *c5 = new TCanvas("c5","c5",700,500);
    // dR_A1->Draw();
    // if(l==0) c5->SaveAs("dR_A1_ct01.png","recreate");
    // if(l==1) c5->SaveAs("dR_A1_ct02.png","recreate");
    // if(l==2) c5->SaveAs("dR_A1_ct1.png","recreate");
    // if(l==3) c5->SaveAs("dR_A1_ct5.png","recreate");


    // dZ_limit_A0mu1->SetLineStyle(2);
    // dZ_limit_A0mu1->SetLineWidth(3);
    // dZ_limit_A1mu0->SetLineWidth(3);
    // dZ_limit_A1mu1->SetLineWidth(3);

    // R_A0mu1->SetLineStyle(2);
    // R_A0mu1->SetLineWidth(3);
    // R_A1mu0->SetLineWidth(3);
    // R_A1mu1->SetLineWidth(3);

    // Rnew_A0mu1->SetLineStyle(2);
    // Rnew_A0mu1->SetLineWidth(3);
    // Rnew_A1mu0->SetLineWidth(3);
    // Rnew_A1mu1->SetLineWidth(3);

    // dZ_A0mu1->SetLineWidth(3);
    // dZ_A1mu0->SetLineWidth(3);
    // dZ_A1mu1->SetLineWidth(3);

    // dZ_limit_A1mu0->SetLineColor(2);
    // dZ_limit_A1mu1->SetLineColor(2);
    // dZ_limit_A1mu1->SetLineStyle(2);

    // R_A1mu0->SetLineColor(2);
    // R_A1mu1->SetLineColor(2);
    // R_A1mu1->SetLineStyle(2);

    // Rnew_A1mu0->SetLineColor(2);
    // Rnew_A1mu1->SetLineColor(2);
    // Rnew_A1mu1->SetLineStyle(2);

    // dZ_A1mu0->SetLineColor(2);
    // dZ_A1mu1->SetLineColor(2);
    // dZ_A1mu1->SetLineStyle(2);


    // TLegend *leg = new TLegend(0.6,0.7,0.8,0.9);
    // leg->SetBorderSize(0);
    // leg->SetFillColor(0);
    // leg->SetTextSize(0.036);
    // leg->SetHeader("m_{#gamma D}=0.25 GeV,c#tau_{#gamma D} = 5mm");
    // leg->AddEntry(dZ_limit_A0mu0,"A0 #mu_{0}","L");
    // leg->AddEntry(dZ_limit_A0mu1,"A0 #mu_{1}","L");
    // leg->AddEntry(dZ_limit_A1mu0,"A1 #mu_{0}","L");
    // leg->AddEntry(dZ_limit_A1mu1,"A1 #mu_{1}","L");

    


    // TCanvas *c6 = new TCanvas("c6","c6",700,500);
    // dZ_limit_A0mu0->GetXaxis()->SetTitle("|#mu_{z extrapolated}| [cm]");
    // dZ_limit_A0mu0->SetLineWidth(3);
    // dZ_limit_A0mu0->Draw();
    // dZ_limit_A0mu1->Draw("same");
    // dZ_limit_A1mu0->Draw("same");
    // dZ_limit_A1mu1->Draw("same");
    // leg->Draw("same");
    // c6->SaveAs("mu_zext.pdf","recreate");


    // TCanvas *c66 = new TCanvas("c66","c66",700,500);
    // dZ_A0mu0->GetXaxis()->SetTitle("|#mu_{z}| [cm]");
    // dZ_A0mu0->SetLineWidth(3);
    // dZ_A0mu0->Draw();
    // dZ_A0mu1->Draw("same");
    // dZ_A1mu0->Draw("same");
    // dZ_A1mu1->Draw("same");
    // leg->Draw("same");
    // c66->SaveAs("mu_z.pdf","recreate");

    // TCanvas *c666 = new TCanvas("c666","c666",700,500);
    // R_A0mu0->GetXaxis()->SetTitle("|#mu_{lxy}| [cm]");
    // R_A0mu0->SetLineWidth(3);
    // R_A0mu0->Draw();
    // R_A0mu1->Draw("same");
    // R_A1mu0->Draw("same");
    // R_A1mu1->Draw("same");
    // leg->Draw("same");
    // c666->SaveAs("mu_z.pdf","recreate");


    // TCanvas *c6666 = new TCanvas("c6666","c6666",700,500);
    // Rnew_A0mu0->GetXaxis()->SetTitle("|#mu_{lxy}| [cm]");
    // Rnew_A0mu0->SetLineWidth(3);
    // Rnew_A0mu0->Draw();
    // Rnew_A0mu1->Draw("same");
    // Rnew_A1mu0->Draw("same");
    // Rnew_A1mu1->Draw("same");
    // leg->Draw("same");
    // c6666->SaveAs("mu_z.pdf","recreate");

    // TLine *line4 = new TLine(2.4,0.0,2.4,600);
    // line4->SetLineColor(2);
    // line4->SetLineStyle(2);
    // line4->SetLineWidth(3);

    // TCanvas *c77 = new TCanvas("c77","c77",700,500);
    // Rnew_A0mu0_A0eta->Draw("COLZ");
    // Rnew_A0mu0_A0eta->GetXaxis()->SetTitle("|#eta_{A_{0}}|");
    // Rnew_A0mu0_A0eta->GetYaxis()->SetTitle("|R_{ext} A0#mu_{0} at z=34cm [cm]");
    // line4->Draw("same");
    // c77->SaveAs("Rnew_A0geneta.pdf","recreate");


    // TLine *line = new TLine(34.0,0.0,34.0,200.0);
    // line->SetLineColor(2);
    // line->SetLineStyle(2);

    // TLine *line2 = new TLine(0.0,6.0,50.0,6.0);
    // line2->SetLineColor(2);
    // line2->SetLineStyle(2);

    // TLine *line3 = new TLine(0.0,20.0,50.0,20.0);
    // line3->SetLineColor(2);
    // line3->SetLineStyle(2);


    // TCanvas *c7 = new TCanvas("c7","c7",700,500);
    // c7->Divide(2,2);
    // c7->cd(1);
    // R_dZ_limit_A0mu0->Draw("COLZ");
    // R_dZ_limit_A0mu0->GetXaxis()->SetTitle("A0 #mu_{z extrapolated}");
    // R_dZ_limit_A0mu0->GetYaxis()->SetTitle("A0 #mu_{lxy}");
    // line->Draw("same");
    // line2->Draw("same");
    // line3->Draw("same");
    // c7->cd(2);
    // R_dZ_limit_A0mu1->Draw("COLZ");
    // R_dZ_limit_A0mu1->GetXaxis()->SetTitle("A0 #mu_{z extrapolated}");
    // R_dZ_limit_A0mu1->GetYaxis()->SetTitle("A0 #mu_{lxy}");
    // line->Draw("same");
    // line2->Draw("same");
    // line3->Draw("same");
    // c7->cd(3);
    // R_dZ_limit_A1mu0->Draw("COLZ");
    // R_dZ_limit_A1mu0->GetXaxis()->SetTitle("A1 #mu_{z extrapolated}");
    // R_dZ_limit_A1mu0->GetYaxis()->SetTitle("A1 #mu_{lxy}");
    // line->Draw("same");
    // line2->Draw("same");
    // line3->Draw("same");
    // c7->cd(4);
    // R_dZ_limit_A1mu1->Draw("COLZ");
    // R_dZ_limit_A1mu1->GetXaxis()->SetTitle("A1 #mu_{z extrapolated}");
    // R_dZ_limit_A1mu1->GetYaxis()->SetTitle("A1 #mu_{lxy}");
    // line->Draw("same");
    // line2->Draw("same");
    // line3->Draw("same");
    // c7->SaveAs("mu_lxy_zext.pdf","recreate");



    // TCanvas *c100 = new TCanvas("c100","c100");
    // A0eta->Draw();

    // R_dZ_limit->Draw("COLZ");
    // if(l==0) c5->SaveAs("dR_A1_ct01.png","recreate");
    // if(l==1) c5->SaveAs("dR_A1_ct02.png","recreate");
    // if(l==2) c5->SaveAs("dR_A1_ct1.png","recreate");
    // if(l==3) c5->SaveAs("dR_A1_ct5.png","recreate");

  }
}
