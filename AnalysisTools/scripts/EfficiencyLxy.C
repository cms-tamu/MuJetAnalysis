#include <iostream>
#include "TCanvas.h"
#include "TROOT.h"
#include "TH1F.h"
#include "TString.h" 
#include <algorithm>    // std::max
#include "TMath.h"
#include <math.h>
#define _USE_MATH_DEFINES
#include <cmath>

double My_dPhi (double phi1, double phi2) {
  double dPhi = phi1 - phi2;
  if (dPhi >  TMath::Pi()) dPhi -= 2*TMath::Pi();
  if (dPhi <  -TMath::Pi()) dPhi += 2*TMath::Pi();
  return dPhi;
}

void EfficiencyLxy(){

  TString fname = "mGamma_0250_ctau1";
  TFile *f = new TFile(fname+".root");

  f->cd("Analysis");
  f->ls();

  Int_t ev;
  Int_t run;
  Int_t lumi;
  Int_t   genm;
  Int_t   trig;
  Float_t ptgenm[20];
  Float_t etagenm[20];
  Int_t recm;
  Float_t ptrecm[20];
  Float_t etarecm[20];
  Float_t phirecm[20];
  Int_t mjets;
  Int_t mj1mu;
  Int_t mj2mu;
  Float_t ptmumj1[20];
  Float_t ptmumj2[20];
  Float_t etamumj1[20];
  Float_t etamumj2[20];
  Int_t vtx;
  Float_t gen_dzmj1_0;
  Float_t gen_dzmj1_1;
  Float_t gen_mj1_0_pt;
  Float_t gen_mj1_1_pt;
  Float_t gen_mj1_0_eta;
  Float_t gen_mj1_1_eta;
  Float_t gen_mj1_0_phi;
  Float_t gen_mj1_1_phi;
  Float_t gen_dzmj2_0;
  Float_t gen_dzmj2_1;
  Float_t gen_mj2_0_pt;
  Float_t gen_mj2_1_pt;
  Float_t gen_mj2_0_eta;
  Float_t gen_mj2_1_eta;
  Float_t gen_mj2_0_phi;
  Float_t gen_mj2_1_phi;
  Float_t lxy_ge_1_0;
  Float_t lxy_ge_1_1;
  Float_t lxy_ge_2_0;
  Float_t lxy_ge_2_1;

  TTree *t = (TTree*)f->Get("Analysis/Events");

  TCanvas* c1 = new TCanvas("c1","Example",800,600);  

  c1->SetFillColor(0);
  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);  
  // SetPlotStyle();

  t->SetBranchAddress("lxy_ge_1_0", &lxy_ge_1_0);
  t->SetBranchAddress("lxy_ge_1_1", &lxy_ge_1_1);
  t->SetBranchAddress("lxy_ge_2_0", &lxy_ge_2_0);
  t->SetBranchAddress("lxy_ge_2_1", &lxy_ge_2_1);

  t->SetBranchAddress("gen_dzmj1_0", &gen_dzmj1_0);
  t->SetBranchAddress("gen_dzmj1_1", &gen_dzmj1_1);
  t->SetBranchAddress("gen_mj1_0_pt", &gen_mj1_0_pt);
  t->SetBranchAddress("gen_mj1_1_pt", &gen_mj1_1_pt);
  t->SetBranchAddress("gen_mj1_0_eta", &gen_mj1_0_eta);
  t->SetBranchAddress("gen_mj1_1_eta", &gen_mj1_1_eta);

  t->SetBranchAddress("gen_mj1_0_phi", &gen_mj1_0_phi);
  t->SetBranchAddress("gen_mj1_1_phi", &gen_mj1_1_phi);

  t->SetBranchAddress("gen_dzmj2_0", &gen_dzmj2_0);
  t->SetBranchAddress("gen_dzmj2_1", &gen_dzmj2_1);
  t->SetBranchAddress("gen_mj2_0_pt", &gen_mj2_0_pt);
  t->SetBranchAddress("gen_mj2_1_pt", &gen_mj2_1_pt);
  t->SetBranchAddress("gen_mj2_0_eta", &gen_mj2_0_eta);
  t->SetBranchAddress("gen_mj2_1_eta", &gen_mj2_1_eta);
  t->SetBranchAddress("gen_mj2_0_phi", &gen_mj2_0_phi);
  t->SetBranchAddress("gen_mj2_1_phi", &gen_mj2_1_phi);

  t->SetBranchAddress("event",&ev);
  t->SetBranchAddress("run",&run);
  t->SetBranchAddress("lumi",&lumi);
  t->SetBranchAddress("trigger",&trig);
  t->SetBranchAddress("isVtx",&vtx);

  t->SetBranchAddress("genmuons",&genm);
  t->SetBranchAddress("ptgenMuons",&ptgenm);
  t->SetBranchAddress("etagenMuons",&etagenm);
  
  t->SetBranchAddress("recmuons",&recm);
  t->SetBranchAddress("ptrecMuons",&ptrecm);
  t->SetBranchAddress("etarecMuons",&etarecm);
  t->SetBranchAddress("phirecMuons",&phirecm);

  t->SetBranchAddress("recmujets",&mjets);
  t->SetBranchAddress("mj1muons",&mj1mu);
  t->SetBranchAddress("mj2muons",&mj2mu);

  t->SetBranchAddress("ptmj1muons",&ptmumj1);
  t->SetBranchAddress("ptmj2muons",&ptmumj2);
  t->SetBranchAddress("etamj1muons",&etamumj1);
  t->SetBranchAddress("etamj2muons",&etamumj2);

  Float_t bin_edges[19]={0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36};
  Float_t bin_center[18];
  Float_t errbin_center[18];
  Float_t erry[18];

  Float_t bin_edges_lxy[19]={0,2,4,6,8,10,12,14,16,18,20,25,30,35,40,45,50,60,80};
  Float_t bin_center_lxy[18];
  Float_t errbin_center_lxy[18];
  Float_t erry_lxy[18];


  for(int k=0;k<18;k++){
    bin_center[k] = bin_edges[k] + ( (bin_edges[k+1]-bin_edges[k])/2.0);
    errbin_center[k] = ( (bin_edges[k+1]-bin_edges[k])/2.0);
    erry[k] = 0.0;
    bin_center_lxy[k] = bin_edges_lxy[k] + ( (bin_edges_lxy[k+1]-bin_edges_lxy[k])/2.0);
    errbin_center_lxy[k] = ( (bin_edges_lxy[k+1]-bin_edges_lxy[k])/2.0);
    erry_lxy[k] = 0.0;
  }


  //===============================================
  Float_t count_barrel_muonPair_1_0[18]={0.0};
  Float_t count_rec_barrel_muonPair_1_0[18]={0.0};
  Float_t count_barrel_muonPair_1_1[18]={0.0};
  Float_t count_rec_barrel_muonPair_1_1[18]={0.0};
  Float_t count_endcap_muonPair_1_0[18]={0.0};
  Float_t count_rec_endcap_muonPair_1_0[18]={0.0};
  Float_t count_endcap_muonPair_1_1[18]={0.0};
  Float_t count_rec_endcap_muonPair_1_1[18]={0.0};

  Float_t count_barrel_muonPair_2_0[18]={0.0};
  Float_t count_rec_barrel_muonPair_2_0[18]={0.0};
  Float_t count_barrel_muonPair_2_1[18]={0.0};
  Float_t count_rec_barrel_muonPair_2_1[18]={0.0};
  Float_t count_endcap_muonPair_2_0[18]={0.0};
  Float_t count_rec_endcap_muonPair_2_0[18]={0.0};
  Float_t count_endcap_muonPair_2_1[18]={0.0};
  Float_t count_rec_endcap_muonPair_2_1[18]={0.0};

  Float_t count_lxy_barrel_muonPair_1_0[18]={0.0};
  Float_t count_lxy_rec_barrel_muonPair_1_0[18]={0.0};
  Float_t count_lxy_barrel_muonPair_1_1[18]={0.0};
  Float_t count_lxy_rec_barrel_muonPair_1_1[18]={0.0};
  Float_t count_lxy_endcap_muonPair_1_0[18]={0.0};
  Float_t count_lxy_rec_endcap_muonPair_1_0[18]={0.0};
  Float_t count_lxy_endcap_muonPair_1_1[18]={0.0};
  Float_t count_lxy_rec_endcap_muonPair_1_1[18]={0.0};

  Float_t count_lxy_barrel_muonPair_2_0[18]={0.0};
  Float_t count_lxy_rec_barrel_muonPair_2_0[18]={0.0};
  Float_t count_lxy_barrel_muonPair_2_1[18]={0.0};
  Float_t count_lxy_rec_barrel_muonPair_2_1[18]={0.0};
  Float_t count_lxy_endcap_muonPair_2_0[18]={0.0};
  Float_t count_lxy_rec_endcap_muonPair_2_0[18]={0.0};
  Float_t count_lxy_endcap_muonPair_2_1[18]={0.0};
  Float_t count_lxy_rec_endcap_muonPair_2_1[18]={0.0};



  Int_t nentries = t->GetEntries();

  Int_t mcount[4]={0};
  Int_t rmcount[4]={0};


  bool verbose = false;
  int entries = 0;
  for(int k=0;k<nentries;k++){
    t->GetEntry(k);
    entries++;
    if (entries % 500 == 0) std::cout << "entries: " << entries << ", " << (entries*1.0/80000.0)*100.0 << " % " << std::endl;

    verbose = false;
    

    Int_t hptm_count=0;
    Int_t m_count=0;
    for(int j=0;j<genm;j++){
      if(ptgenm[j]>17.0 && fabs(etagenm[j])<0.9) hptm_count++;
      if(ptgenm[j]>8.0 && fabs(etagenm[j])<2.4) m_count++;
      if (verbose) std::cout << "ptgenm[j]: " << ptgenm[j] << ", fabs(etagenm[j]): " << fabs(etagenm[j]) << std::endl;
    }

    if(hptm_count>0){
      mcount[0]++;
      if(m_count>1) mcount[1]++;
      if(m_count>2) mcount[2]++;
      if(m_count>3) mcount[3]++;
    }

    if(hptm_count>0 && mcount>3){

      bool lxy = true;
      bool dz = false;

      if (gen_mj1_0_pt > 8 && gen_mj1_1_pt > 8 && gen_mj2_1_pt > 8 && gen_mj2_1_pt > 8){

        bool matchRec11 = false;
        double dphi11 = 1000.0;
        double deta11 = 1000.0;
        double dR11 = 1000.0;
        int match11 = 100;

        bool matchRec12 = false;
        double dphi12 = 1000.0;
        double deta12 = 1000.0;
        double dR12 = 1000.0;
        int match12 = 100;

        bool matchRec21 = false;
        double dphi21 = 1000.0;
        double deta21 = 1000.0;
        double dR21 = 1000.0;
        int match21 = 100;

        bool matchRec22 = false;
        double dphi22 = 1000.0;
        double deta22 = 1000.0;
        double dR22 = 1000.0;
        int match22 = 100;

        for(int j=0;j<recm;j++){

          if(ptrecm[j]<8.0 || fabs(etarecm[j])>2.4) continue;
    
          dphi11 = My_dPhi(phirecm[j], gen_mj1_0_phi); 
          dphi12 = My_dPhi(phirecm[j], gen_mj1_1_phi); 
          deta11 = (etarecm[j] - gen_mj1_0_eta); 
          deta12 = (etarecm[j] - gen_mj1_1_eta); 
          dR11 = sqrt(dphi11*dphi11+deta11*deta11);
          dR12 = sqrt(dphi12*dphi12+deta12*deta12);
          if(dR11<0.5){
            matchRec11 = true;
            match11 = j;
          }
          if(dR12<0.5){
            matchRec12 = true;
            match12 = j;
          }

          dphi21 = My_dPhi(phirecm[j], gen_mj2_0_phi); 
          dphi22 = My_dPhi(phirecm[j], gen_mj2_1_phi); 
          deta21 = (etarecm[j] - gen_mj2_0_eta); 
          deta22 = (etarecm[j] - gen_mj2_1_eta); 
          dR21 = sqrt(dphi21*dphi21+deta21*deta21);
          dR22 = sqrt(dphi22*dphi22+deta22*deta22);
          if(dR21<0.5){
            matchRec21 = true;
            match21 = j;
          }
          if(dR22<0.5){
            matchRec22 = true;
            match22 = j;
          }

        }

        for(int m=0;m<18;m++){

          if(fabs(lxy_ge_1_0)>bin_edges_lxy[m] && fabs(lxy_ge_1_0)<bin_edges_lxy[m+1]){
            if (fabs(gen_mj1_0_eta) < 0.8){
              count_lxy_barrel_muonPair_1_0[m]++;
            }
            if (fabs(gen_mj1_0_eta) > 0.8) count_lxy_endcap_muonPair_1_0[m]++;
            if (matchRec11){
              if (fabs(gen_mj1_0_eta) < 0.8){
                count_lxy_rec_barrel_muonPair_1_0[m]++;
              }
              if (fabs(gen_mj1_0_eta) > 0.8) count_lxy_rec_endcap_muonPair_1_0[m]++;
              if (verbose) std::cout << "event: " << ev << " gen1 pt: " << gen_mj1_0_pt << ", gen1 eta: " << gen_mj1_0_eta << ", rec match pt: " << ptrecm[match11] << ", rec match eta " << etarecm[match11] << ", lxy: " << lxy_ge_1_0 << std::endl; 
            }
          }
          if(fabs(lxy_ge_1_1)>bin_edges_lxy[m] && fabs(lxy_ge_1_1)<bin_edges_lxy[m+1]){
            if (fabs(gen_mj1_1_eta) < 0.8) count_lxy_barrel_muonPair_1_1[m]++;
            if (fabs(gen_mj1_1_eta) > 0.8) count_lxy_endcap_muonPair_1_1[m]++;
            if (matchRec12){
              if (fabs(gen_mj1_1_eta) < 0.8) count_lxy_rec_barrel_muonPair_1_1[m]++;
              if (fabs(gen_mj1_1_eta) > 0.8) count_lxy_rec_endcap_muonPair_1_1[m]++;
              if (verbose) std::cout << "event: " << ev << " gen1 pt: " << gen_mj1_1_pt << ", gen1 eta: " << gen_mj1_1_eta << ", rec match pt: " << ptrecm[match12] << ", rec match eta " << etarecm[match12] << ", lxy: " << lxy_ge_1_1 << std::endl; 
            }
          }
          if(fabs(lxy_ge_2_0)>bin_edges_lxy[m] && fabs(lxy_ge_2_0)<bin_edges_lxy[m+1]){
            if (fabs(gen_mj2_0_eta) < 0.8){
              count_lxy_barrel_muonPair_2_0[m]++;
            }
            if (fabs(gen_mj2_0_eta) > 0.8) count_lxy_endcap_muonPair_2_0[m]++;
            if (matchRec21){
              if (fabs(gen_mj2_0_eta) < 0.8){
                count_lxy_rec_barrel_muonPair_2_0[m]++;
              }
              if (fabs(gen_mj2_0_eta) > 0.8) count_lxy_rec_endcap_muonPair_2_0[m]++;
              if (verbose) std::cout << "event: " << ev << " gen1 pt: " << gen_mj2_0_pt << ", gen1 eta: " << gen_mj2_0_eta << ", rec match pt: " << ptrecm[match21] << ", rec match eta " << etarecm[match21] << ", lxy: " << lxy_ge_2_0 << std::endl; 
            }
          }
          if(fabs(lxy_ge_2_1)>bin_edges_lxy[m] && fabs(lxy_ge_2_1)<bin_edges_lxy[m+1]){
            if (fabs(gen_mj2_1_eta) < 0.8){
              count_lxy_barrel_muonPair_2_1[m]++;
            }
            if (fabs(gen_mj2_1_eta) > 0.8) count_lxy_endcap_muonPair_2_1[m]++;
            if (matchRec22){
              if (fabs(gen_mj2_1_eta) < 0.8){
                count_lxy_rec_barrel_muonPair_2_1[m]++;
              }
              if (fabs(gen_mj2_1_eta) > 0.8) count_lxy_rec_endcap_muonPair_2_1[m]++;
              if (verbose) std::cout << "event: " << ev << " gen1 pt: " << gen_mj2_1_pt << ", gen1 eta: " << gen_mj2_1_eta << ", rec match pt: " << ptrecm[match22] << ", rec match eta " << etarecm[match22] << ", lxy: " << lxy_ge_2_1 << std::endl; 
            }
          }
        }
      }
    }
  }
      

  std::cout << "entries: " << entries << std::endl;

  std::cout << "Entries loop finished" << std::endl;

  Float_t rval_barrel_lxy_muonPair_1_0[30]={0.0};
  Float_t rval_endcap_lxy_muonPair_1_0[30]={0.0};
  Float_t rval_barrel_lxy_muonPair_1_1[30]={0.0};
  Float_t rval_endcap_lxy_muonPair_1_1[30]={0.0};

  Float_t erval_barrel_lxy_muonPair_1_0[30]={0.0};
  Float_t erval_endcap_lxy_muonPair_1_0[30]={0.0};
  Float_t erval_barrel_lxy_muonPair_1_1[30]={0.0};
  Float_t erval_endcap_lxy_muonPair_1_1[30]={0.0};

  Float_t rval_barrel_lxy_muonPair_2_0[30]={0.0};
  Float_t rval_endcap_lxy_muonPair_2_0[30]={0.0};
  Float_t rval_barrel_lxy_muonPair_2_1[30]={0.0};
  Float_t rval_endcap_lxy_muonPair_2_1[30]={0.0};

  Float_t erval_barrel_lxy_muonPair_2_0[30]={0.0};
  Float_t erval_endcap_lxy_muonPair_2_0[30]={0.0};
  Float_t erval_barrel_lxy_muonPair_2_1[30]={0.0};
  Float_t erval_endcap_lxy_muonPair_2_1[30]={0.0};



  std::cout << "Starting fill" << std::endl;
  for(int k=0;k<18;k++) {

    if(count_lxy_barrel_muonPair_1_0[k]!=0) rval_barrel_lxy_muonPair_1_0[k] = count_lxy_rec_barrel_muonPair_1_0[k]/count_lxy_barrel_muonPair_1_0[k];
    if(count_lxy_endcap_muonPair_1_0[k]!=0) rval_endcap_lxy_muonPair_1_0[k] = count_lxy_rec_endcap_muonPair_1_0[k]/count_lxy_endcap_muonPair_1_0[k];

    if(count_lxy_barrel_muonPair_1_1[k]!=0) rval_barrel_lxy_muonPair_1_1[k] = count_lxy_rec_barrel_muonPair_1_1[k]/count_lxy_barrel_muonPair_1_1[k];
    if(count_lxy_endcap_muonPair_1_1[k]!=0) rval_endcap_lxy_muonPair_1_1[k] = count_lxy_rec_endcap_muonPair_1_1[k]/count_lxy_endcap_muonPair_1_1[k];

    if(count_lxy_barrel_muonPair_1_0[k]!=0 ) erval_barrel_lxy_muonPair_1_0[k] = sqrt( (rval_barrel_lxy_muonPair_1_0[k]*(1-rval_barrel_lxy_muonPair_1_0[k]))/count_lxy_barrel_muonPair_1_0[k]);
    if(count_lxy_endcap_muonPair_1_0[k]!=0) erval_endcap_lxy_muonPair_1_0[k] = sqrt( (rval_endcap_lxy_muonPair_1_0[k]*(1-rval_endcap_lxy_muonPair_1_0[k]))/count_lxy_endcap_muonPair_1_0[k]);

    if(count_lxy_barrel_muonPair_1_1[k]!=0 ) erval_barrel_lxy_muonPair_1_1[k] = sqrt( (rval_barrel_lxy_muonPair_1_1[k]*(1-rval_barrel_lxy_muonPair_1_1[k]))/count_lxy_barrel_muonPair_1_1[k]);
    if(count_lxy_endcap_muonPair_1_1[k]!=0) erval_endcap_lxy_muonPair_1_1[k] = sqrt( (rval_endcap_lxy_muonPair_1_1[k]*(1-rval_endcap_lxy_muonPair_1_1[k]))/count_lxy_endcap_muonPair_1_1[k]);


    if(count_lxy_barrel_muonPair_2_0[k]!=0) rval_barrel_lxy_muonPair_2_0[k] = count_lxy_rec_barrel_muonPair_2_0[k]/count_lxy_barrel_muonPair_2_0[k];
    if(count_lxy_endcap_muonPair_2_0[k]!=0) rval_endcap_lxy_muonPair_2_0[k] = count_lxy_rec_endcap_muonPair_2_0[k]/count_lxy_endcap_muonPair_2_0[k];

    if(count_lxy_barrel_muonPair_2_1[k]!=0) rval_barrel_lxy_muonPair_2_1[k] = count_lxy_rec_barrel_muonPair_2_1[k]/count_lxy_barrel_muonPair_2_1[k];
    if(count_lxy_endcap_muonPair_2_1[k]!=0) rval_endcap_lxy_muonPair_2_1[k] = count_lxy_rec_endcap_muonPair_2_1[k]/count_lxy_endcap_muonPair_2_1[k];

    if(count_lxy_barrel_muonPair_2_0[k]!=0 ) erval_barrel_lxy_muonPair_2_0[k] = sqrt( (rval_barrel_lxy_muonPair_2_0[k]*(1-rval_barrel_lxy_muonPair_2_0[k]))/count_lxy_barrel_muonPair_2_0[k]);
    if(count_lxy_endcap_muonPair_2_0[k]!=0) erval_endcap_lxy_muonPair_2_0[k] = sqrt( (rval_endcap_lxy_muonPair_2_0[k]*(1-rval_endcap_lxy_muonPair_2_0[k]))/count_lxy_endcap_muonPair_2_0[k]);

    if(count_lxy_barrel_muonPair_2_1[k]!=0 ) erval_barrel_lxy_muonPair_2_1[k] = sqrt( (rval_barrel_lxy_muonPair_2_1[k]*(1-rval_barrel_lxy_muonPair_2_1[k]))/count_lxy_barrel_muonPair_2_1[k]);
    if(count_lxy_endcap_muonPair_2_1[k]!=0) erval_endcap_lxy_muonPair_2_1[k] = sqrt( (rval_endcap_lxy_muonPair_2_1[k]*(1-rval_endcap_lxy_muonPair_2_1[k]))/count_lxy_endcap_muonPair_2_1[k]);

  }


  std::cout << "Starting TGraphs:" << std::endl;

  TGraphErrors *gr_r_barrel_lxy_muonPair_1_0 = new TGraphErrors(18,bin_center_lxy,rval_barrel_lxy_muonPair_1_0,errbin_center_lxy,erval_barrel_lxy_muonPair_1_0);
  TGraphErrors *gr_r_endcap_lxy_muonPair_1_0 = new TGraphErrors(18,bin_center_lxy,rval_endcap_lxy_muonPair_1_0,errbin_center_lxy,erval_endcap_lxy_muonPair_1_0);
  TGraphErrors *gr_r_barrel_lxy_muonPair_1_1 = new TGraphErrors(18,bin_center_lxy,rval_barrel_lxy_muonPair_1_1,errbin_center_lxy,erval_barrel_lxy_muonPair_1_1);
  TGraphErrors *gr_r_endcap_lxy_muonPair_1_1 = new TGraphErrors(18,bin_center_lxy,rval_endcap_lxy_muonPair_1_1,errbin_center_lxy,erval_endcap_lxy_muonPair_1_1);

  TGraphErrors *gr_r_barrel_lxy_muonPair_2_0 = new TGraphErrors(18,bin_center_lxy,rval_barrel_lxy_muonPair_2_0,errbin_center_lxy,erval_barrel_lxy_muonPair_2_0);
  TGraphErrors *gr_r_endcap_lxy_muonPair_2_0 = new TGraphErrors(18,bin_center_lxy,rval_endcap_lxy_muonPair_2_0,errbin_center_lxy,erval_endcap_lxy_muonPair_2_0);
  TGraphErrors *gr_r_barrel_lxy_muonPair_2_1 = new TGraphErrors(18,bin_center_lxy,rval_barrel_lxy_muonPair_2_1,errbin_center_lxy,erval_barrel_lxy_muonPair_2_1);
  TGraphErrors *gr_r_endcap_lxy_muonPair_2_1 = new TGraphErrors(18,bin_center_lxy,rval_endcap_lxy_muonPair_2_1,errbin_center_lxy,erval_endcap_lxy_muonPair_2_1);



  TCanvas *c = new TCanvas("c","c");

  TLegend *leg3 = new TLegend(0.7,0.65,0.825,0.85);

  gr_r_barrel_lxy_muonPair_2_0->GetXaxis()->SetTitle("Lxy [cm]");
  gr_r_barrel_lxy_muonPair_2_0->GetYaxis()->SetTitle("efficiency");
  gr_r_barrel_lxy_muonPair_2_0->SetTitle("");

  gr_r_barrel_lxy_muonPair_2_0->SetLineColor(kRed);
  gr_r_barrel_lxy_muonPair_2_0->SetMarkerColor(kRed);
  gr_r_barrel_lxy_muonPair_2_0->Draw("APL");
  gr_r_barrel_lxy_muonPair_2_0->GetYaxis()->SetRangeUser(0.0,1.0);
  gr_r_barrel_lxy_muonPair_2_1->GetYaxis()->SetRangeUser(0.0,1.0);
  // gr_r_barrel_lxy_muonPair_2_0->GetXaxis()->SetRangeUser(0.0,30.0);
  // gr_r_barrel_lxy_muonPair_2_0->GetXaxis()->SetRangeUser(0.0,30.0);

  gr_r_endcap_lxy_muonPair_2_0->SetLineColor(kRed);
  gr_r_endcap_lxy_muonPair_2_0->SetMarkerColor(kRed);
  gr_r_endcap_lxy_muonPair_2_0->SetLineStyle(2);
  gr_r_endcap_lxy_muonPair_2_0->Draw("PLsame");

  gr_r_barrel_lxy_muonPair_2_1->SetLineColor(kBlack);
  gr_r_barrel_lxy_muonPair_2_1->SetMarkerColor(kBlack);
  gr_r_endcap_lxy_muonPair_2_1->SetLineColor(kBlack);
  gr_r_endcap_lxy_muonPair_2_1->SetMarkerColor(kBlack);
  gr_r_endcap_lxy_muonPair_2_1->SetLineStyle(2);
  gr_r_endcap_lxy_muonPair_2_1->Draw("PLsame");
  gr_r_barrel_lxy_muonPair_2_1->Draw("PLsame");


  TLine pix1(4.4, 1e-8, 4.4,1.0);
  pix1.SetLineStyle(2); pix1.SetLineWidth(1); pix1.SetLineColor(kBlue);
  pix1.Draw("same");
  TLine pix2(7.3, 1e-8, 7.3,1.0);
  pix2.SetLineStyle(2); pix2.SetLineWidth(1); pix2.SetLineColor(kBlue);
  pix2.Draw("same");
  TLine pix3(10.2, 1e-8, 10.2,1.0);
  pix3.SetLineStyle(2); pix3.SetLineWidth(1); pix3.SetLineColor(kBlue);
  pix3.Draw("same");
  TLine trk1(22,1e-8,22,1.0);
  trk1.SetLineStyle(2); trk1.SetLineWidth(1); trk1.SetLineColor(kGreen);
  trk1.Draw("same");
  TLine trk2(60, 1e-8, 60,1.0);
  trk2.SetLineStyle(2); trk2.SetLineWidth(1); trk2.SetLineColor(kGreen);
  trk2.Draw("same");



  leg3->SetBorderSize(0);
  leg3->SetFillColor(0);
  leg3->SetTextSize(0.036);
  leg3->AddEntry(gr_r_barrel_lxy_muonPair_2_0,"|#eta_{#gamma D}|<0.8 A1 #mu_{0}","PL");
  leg3->AddEntry(gr_r_endcap_lxy_muonPair_2_0,"|#eta_{#gamma D}|>0.8 A1 #mu_{0}","PL");
  leg3->AddEntry(gr_r_barrel_lxy_muonPair_2_1,"|#eta_{#gamma D}|<0.8 A1 #mu_{1}","PL");
  leg3->AddEntry(gr_r_endcap_lxy_muonPair_2_1,"|#eta_{#gamma D}|>0.8 A1 #mu_{1}","PL");

  leg3->Draw("same");
  c->SaveAs(fname+"_eff_eta_lxy_1D_A1.pdf","recreate");
  c->Clear();

  TLegend *leg4 = new TLegend(0.7,0.65,0.825,0.85);

  gr_r_barrel_lxy_muonPair_1_0->GetXaxis()->SetTitle("Lxy [cm]");
  gr_r_barrel_lxy_muonPair_1_0->GetYaxis()->SetTitle("efficiency");
  gr_r_barrel_lxy_muonPair_1_0->SetTitle("");

  gr_r_barrel_lxy_muonPair_1_0->SetLineColor(kRed);
  gr_r_barrel_lxy_muonPair_1_0->SetMarkerColor(kRed);
  gr_r_barrel_lxy_muonPair_1_0->Draw("APL");
  gr_r_barrel_lxy_muonPair_1_0->GetYaxis()->SetRangeUser(0.0,1.0);
  gr_r_barrel_lxy_muonPair_1_1->GetYaxis()->SetRangeUser(0.0,1.0);
  // gr_r_barrel_lxy_muonPair_1_0->GetXaxis()->SetRangeUser(0.0,30.0);
  // gr_r_barrel_lxy_muonPair_1_0->GetXaxis()->SetRangeUser(0.0,30.0);

  gr_r_endcap_lxy_muonPair_1_0->SetLineColor(kRed);
  gr_r_endcap_lxy_muonPair_1_0->SetMarkerColor(kRed);
  gr_r_endcap_lxy_muonPair_1_0->SetLineStyle(2);
  gr_r_endcap_lxy_muonPair_1_0->Draw("PLsame");

  gr_r_barrel_lxy_muonPair_1_1->SetLineColor(kBlack);
  gr_r_barrel_lxy_muonPair_1_1->SetMarkerColor(kBlack);
  gr_r_endcap_lxy_muonPair_1_1->SetLineColor(kBlack);
  gr_r_endcap_lxy_muonPair_1_1->SetMarkerColor(kBlack);
  gr_r_endcap_lxy_muonPair_1_1->SetLineStyle(2);
  gr_r_endcap_lxy_muonPair_1_1->Draw("PLsame");
  gr_r_barrel_lxy_muonPair_1_1->Draw("PLsame");

  pix1.Draw("same");
  pix2.Draw("same");
  pix3.Draw("same");
  trk1.Draw("same");
  trk2.Draw("same");

  leg4->SetBorderSize(0);
  leg4->SetFillColor(0);
  leg4->SetTextSize(0.036);
  leg4->AddEntry(gr_r_barrel_lxy_muonPair_1_0,"|#eta_{#gamma D}|<0.8 A0 #mu_{0}","PL");
  leg4->AddEntry(gr_r_endcap_lxy_muonPair_1_0,"|#eta_{#gamma D}|>0.8 A0 #mu_{0}","PL");
  leg4->AddEntry(gr_r_barrel_lxy_muonPair_1_1,"|#eta_{#gamma D}|<0.8 A0 #mu_{1}","PL");
  leg4->AddEntry(gr_r_endcap_lxy_muonPair_1_1,"|#eta_{#gamma D}|>0.8 A0 #mu_{1}","PL");

  leg4->Draw("same");
  c->SaveAs(fname+"_eff_eta_lxy_1D_A0.pdf","recreate");
  c->Clear();



}

//  LocalWords:  mjcountvtx
