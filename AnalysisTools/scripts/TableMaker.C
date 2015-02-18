// Script to produce latex tables uses in AN-13-250. It also produces a bunch of the final efficiency plots but much of this could be redundant - I was only using it for the tables. Anthony
 
// compile with g++ `root-config --cflags` TableMaker.C `root-config --glibs` -o tableMaker -Wl,--no-as-needed


#include <iostream>
#include <cstdio>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <sstream>

#include "TFile.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TTree.h"
#include "TGraphErrors.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TLegend.h"
#include <TApplication.h>

using namespace std;

int main( int argc, char **argv ){

  TApplication theApp("App", &argc, argv);
 
  TFile *f[100];
  
  f[0] = new TFile("DarkSUSY_mH_125_mGammaD_0250_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[1] = new TFile("DarkSUSY_mH_125_mGammaD_0250_ctauExp_005_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[2] = new TFile("DarkSUSY_mH_125_mGammaD_0250_ctauExp_01_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[3] = new TFile("DarkSUSY_mH_125_mGammaD_0250_ctauExp_02_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[4] = new TFile("DarkSUSY_mH_125_mGammaD_0250_ctauExp_05_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[5] = new TFile("DarkSUSY_mH_125_mGammaD_0250_ctauExp_1_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[6] = new TFile("DarkSUSY_mH_125_mGammaD_0250_ctauExp_2_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[7] = new TFile("DarkSUSY_mH_125_mGammaD_0250_ctauExp_3_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[8] = new TFile("DarkSUSY_mH_125_mGammaD_0250_ctauExp_5_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[9] = new TFile("DarkSUSY_mH_125_mGammaD_0275_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[10] = new TFile("DarkSUSY_mH_125_mGammaD_0300_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[11] = new TFile("DarkSUSY_mH_125_mGammaD_0300_ctauExp_01_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[12] = new TFile("DarkSUSY_mH_125_mGammaD_0300_ctauExp_02_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[13] = new TFile("DarkSUSY_mH_125_mGammaD_0300_ctauExp_05_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[14] = new TFile("DarkSUSY_mH_125_mGammaD_0350_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[15] = new TFile("DarkSUSY_mH_125_mGammaD_0400_ctauExp_02_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[16] = new TFile("DarkSUSY_mH_125_mGammaD_0400_ctauExp_05_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[17] = new TFile("DarkSUSY_mH_125_mGammaD_0400_ctauExp_2_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[18] = new TFile("DarkSUSY_mH_125_mGammaD_0400_ctauExp_5_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[19] = new TFile("DarkSUSY_mH_125_mGammaD_0550_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[20] = new TFile("DarkSUSY_mH_125_mGammaD_0550_ctauExp_02_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[21] = new TFile("DarkSUSY_mH_125_mGammaD_0550_ctauExp_05_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[22] = new TFile("DarkSUSY_mH_125_mGammaD_0550_ctauExp_1_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  // f[23] = new TFile("DarkSUSY_mH_125_mGammaD_0550_ctauExp_2_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  // f[24] = new TFile("DarkSUSY_mH_125_mGammaD_0550_ctauExp_3_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[25] = new TFile("DarkSUSY_mH_125_mGammaD_0550_ctauExp_5_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[26] = new TFile("DarkSUSY_mH_125_mGammaD_0700_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[27] = new TFile("DarkSUSY_mH_125_mGammaD_0700_ctauExp_02_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[28] = new TFile("DarkSUSY_mH_125_mGammaD_0700_ctauExp_05_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[29] = new TFile("DarkSUSY_mH_125_mGammaD_0700_ctauExp_2_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[30] = new TFile("DarkSUSY_mH_125_mGammaD_0700_ctauExp_5_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[31] = new TFile("DarkSUSY_mH_125_mGammaD_0850_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[32] = new TFile("DarkSUSY_mH_125_mGammaD_0850_ctauExp_02_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[33] = new TFile("DarkSUSY_mH_125_mGammaD_0850_ctauExp_05_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[34] = new TFile("DarkSUSY_mH_125_mGammaD_0850_ctauExp_2_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[35] = new TFile("DarkSUSY_mH_125_mGammaD_0850_ctauExp_5_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[36] = new TFile("DarkSUSY_mH_125_mGammaD_1000_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[37] = new TFile("DarkSUSY_mH_125_mGammaD_1000_ctauExp_02_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[38] = new TFile("DarkSUSY_mH_125_mGammaD_1000_ctauExp_1_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[39] = new TFile("DarkSUSY_mH_125_mGammaD_1000_ctauExp_2_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[40] = new TFile("DarkSUSY_mH_125_mGammaD_1000_ctauExp_3_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[41] = new TFile("DarkSUSY_mH_125_mGammaD_1000_ctauExp_5_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[42] = new TFile("DarkSUSY_mH_125_mGammaD_1500_ctauExp_05_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[43] = new TFile("DarkSUSY_mH_125_mGammaD_1500_ctauExp_2_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[44] = new TFile("DarkSUSY_mH_125_mGammaD_1500_ctauExp_5_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[45] = new TFile("DarkSUSY_mH_125_mGammaD_2000_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[46] = new TFile("DarkSUSY_mH_125_mGammaD_2000_ctauExp_05_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[47] = new TFile("DarkSUSY_mH_125_mGammaD_2000_ctauExp_2_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");
  f[48] = new TFile("MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_5312_GEN_v1.root");
  f[49] = new TFile("MSSM_mH_100_mA_0250_Hto2Ato4mu_8TeV-pythia6_5312_GEN_v1.root");
  f[50] = new TFile("MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_5312_GEN_v1.root");
  f[51] = new TFile("MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_5312_GEN_v1.root");
  f[52] = new TFile("MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_5312_GEN_v1.root");
  f[53] = new TFile("MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_5312_GEN_v1.root");
  f[54] = new TFile("MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_5312_GEN_v1.root");
  f[55] = new TFile("MSSM_mH_125_mA_1000_Hto2Ato4mu_8TeV-pythia6_5312_GEN_v1.root");
  f[56] = new TFile("MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_5312_GEN_v1.root");
  f[57] = new TFile("MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_5312_GEN_v1.root");
  f[58] = new TFile("MSSM_mH_150_mA_0250_Hto2Ato4mu_8TeV-pythia6_5312_GEN_v1.root");
  f[59] = new TFile("MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_5312_GEN_v1.root");

  // f[48] = new TFile("DarkSUSY_mH_125_mGammaD_2000_ctauExp_5_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1.root");




  int counter_gen[60][10];
  int counter_genlxylz[60][10];
  int counter_genlxylz2[60][10];
  int counter_rec[60][10];
  int counter_rec_hits[60][10];
  int counter_rec_dimuons[60][10];

  for(int k=0;k<60;k++){
    for(int j=0;j<10;j++){
      counter_gen[k][j]=0.0;
      counter_genlxylz[k][j]=0.0;
      counter_genlxylz2[k][j]=0.0;
      counter_rec[k][j]=0.0;
      counter_rec_hits[k][j]=0.0;
      counter_rec_dimuons[k][j]=0.0;
    }
  }


  for(int p=0;p<60;p++){


    if ( (p == 23) || (p == 24) ) continue;


    Float_t ev_all[40]={0.0};
    Float_t ev_4gm[40]={0.0};
    Float_t ev_4gmlxylzcut[40]={0.0};

    Float_t ev_4rm[40]={0.0};

    Float_t eventsrecover[40]={0.0};
    Float_t ev_2dim[40]={0.0};
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

    Bool_t isVtxOK;
    Bool_t is2DimVtxOK;
    Bool_t is2DimDzOK;
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


    Int_t is1GenMu17;
    Int_t is2GenMu8;
    Int_t is3GenMu8;
    Int_t is4GenMu8;
    Float_t genA0_Lxy;
    Float_t genA1_Lxy;
    Float_t genA0_Lz;
    Float_t genA1_Lz;

    Int_t is4Rmu8;

    Int_t is2mjets;


    Int_t is1SelMu17;
    Int_t is2SelMu8;
    Int_t is3SelMu8;
    Int_t is4SelMu8;




    TTree *t = (TTree*)f[p]->Get("anatraj/Events");


    t->SetBranchAddress("event",&event);


    t->SetBranchAddress("2dimuon",&ev2dim);

    
    t->SetBranchAddress("isVertexOK",&isVtxOK);
    t->SetBranchAddress("is2DiMuonsDzOK",&is2DimDzOK);
    t->SetBranchAddress("is2DiMuonsVtxOK",&is2DimVtxOK);
    t->SetBranchAddress("is2DiMuonsMassOK",&is2DimMassOK);
    t->SetBranchAddress("is2DiMuonsIsoTkOK",&is2DimIsoTkOK);
    t->SetBranchAddress("is2DiMuonHLTFired",&is2DimHLTFired);

    t->SetBranchAddress("2mjets",&is2mjets);

    t->SetBranchAddress("is1GenMu17",&is1GenMu17);
    t->SetBranchAddress("is2GenMu8",&is2GenMu8);
    t->SetBranchAddress("is3GenMu8",&is3GenMu8);
    t->SetBranchAddress("is4GenMu8",&is4GenMu8);
    t->SetBranchAddress("genA0_Lxy_rdet",&genA0_Lxy);
    t->SetBranchAddress("genA1_Lxy_rdet",&genA1_Lxy);
    t->SetBranchAddress("genA0_Lz_rdet",&genA0_Lz);
    t->SetBranchAddress("genA1_Lz_rdet",&genA1_Lz);

    t->SetBranchAddress("is1SelMu17",&is1SelMu17);
    t->SetBranchAddress("is2SelMu8",&is2SelMu8);
    t->SetBranchAddress("is3SelMu8",&is3SelMu8);
    t->SetBranchAddress("is4SelMu8",&is4SelMu8);

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


    int nentries = t->GetEntries();

    
    for(int k=0;k<nentries;k++){

      t->GetEntry(k);

      counter_gen[p][0]++;
      counter_genlxylz[p][0]++;
      
      if(is1GenMu17) counter_gen[p][1]++;
      if(is2GenMu8) counter_gen[p][2]++;
      if(is3GenMu8) counter_gen[p][3]++;
      if(is4GenMu8) counter_gen[p][4]++;
      
      if(genA0_Lxy<22.0 && fabs(genA0_Lz)<34.0 && genA1_Lxy<22.0 && fabs(genA1_Lz)<34.0){
  	if(is1GenMu17) counter_genlxylz[p][1]++;
  	if(is2GenMu8) counter_genlxylz[p][2]++;
  	if(is3GenMu8) counter_genlxylz[p][3]++;
  	if(is4GenMu8) counter_genlxylz[p][4]++;
      }

      if(genA0_Lxy<4.4 && fabs(genA0_Lz)<34.0 && genA1_Lxy<4.4 && fabs(genA1_Lz)<34.0){
  	if(is1GenMu17) counter_genlxylz2[p][1]++;
  	if(is2GenMu8) counter_genlxylz2[p][2]++;
  	if(is3GenMu8) counter_genlxylz2[p][3]++;
  	if(is4GenMu8) counter_genlxylz2[p][4]++;
      }

      if(is1SelMu17) counter_rec[p][0]++;
      if(is2SelMu8)  counter_rec[p][1]++;
      if(is3SelMu8)  counter_rec[p][2]++;
      if(is4SelMu8)  counter_rec[p][3]++;
     
      if(is2mjets){
  	counter_rec_dimuons[p][0]++;
    	ev_4rm[p]++;

  	if(ev2dim){
  	  counter_rec_dimuons[p][1]++;
    	  ev_2dim[p]++;

   	  bool diMuonC_hits=false;
  	  bool diMuonF_hits=false;

	  // if( (muJetChit[0]==1||muJetChit[1]==1)) diMuonC_hits=true;
	  // if( (muJetFhit[0]==1||muJetFhit[1]==1)) diMuonF_hits=true;

	  if( (muJetChitgt[0]==1||muJetChitgt[1]==1)) diMuonC_hits=true;
	  if( (muJetFhitgt[0]==1||muJetFhitgt[1]==1)) diMuonF_hits=true;


          //=======================  Hit Recovery ==============================================//
	    
          if( (muJetChit[0]!=1&&muJetChit[1]!=1)||(muJetFhit[0]!=1&&muJetFhit[1]!=1) ){

            if( (muJetChit[0]!=1&&muJetChit[1]!=1)&&(muJetFhit[0]!=1&&muJetFhit[1]!=1)){

              bool recover_muJetC=false;
              bool recover_muJetF=false;
		
              // if(Detmu1jetC>0 && Detmu2jetC>0){
              //   for(int j=0;j<Detmu1jetC;j++){
              //     if(mindist_mu1hit_muJetC[j]<0.03 && mindist_mu1hit_muJetC[j]>=0.0) recover_muJetC=true;
              //   }
              //   for(int j=0;j<Detmu2jetC;j++){
              //     if(mindist_mu2hit_muJetC[j]<0.03 && mindist_mu2hit_muJetC[j]>=0.0) recover_muJetC=true;
              //   }
              // }
		
              // if(Detmu1jetF>0 && Detmu2jetF>0){
              //   for(int j=0;j<Detmu1jetF;j++){
              //     if(mindist_mu1hit_muJetF[j]<0.03 && mindist_mu1hit_muJetF[j]>=0.0) recover_muJetF=true;
              //   }
              //   for(int j=0;j<Detmu2jetC;j++){
              //     if(mindist_mu2hit_muJetF[j]<0.03 && mindist_mu2hit_muJetF[j]>=0.0) recover_muJetF=true;
              //   }
              // }
		
              if(recover_muJetC) diMuonC_hits = true;
              if(recover_muJetF) diMuonF_hits = true;
              if(hitrecover_mj12_r005){
                diMuonC_hits = true;
                diMuonF_hits = true;
              }
            }
	      
            if( (muJetChit[0]!=1&&muJetChit[1]!=1)&&(muJetFhit[0]==1||muJetFhit[1]==1)){
		
              bool recover_muJetC=false;
              // if(Detmu1jetC>0 && Detmu2jetC>0){
              //   for(int j=0;j<Detmu1jetC;j++){
              //     if(mindist_mu1hit_muJetC[j]<0.03 && mindist_mu1hit_muJetC[j]>=0.0) recover_muJetC=true;
              //   }
              //   for(int j=0;j<Detmu2jetC;j++){
              //     if(mindist_mu2hit_muJetC[j]<0.03 && mindist_mu2hit_muJetC[j]>=0.0) recover_muJetC=true;
              //   }
              // }
		
              if(recover_muJetC) diMuonC_hits = true;
              if(hitrecover_mj1_r005==1) diMuonC_hits = true;;
            }

            if( (muJetFhit[0]!=1&&muJetFhit[1]!=1)&&(muJetChit[0]==1||muJetChit[1]==1)){
		
              bool recover_muJetF=false;
		
              // if(Detmu1jetF>0 && Detmu2jetF>0){
              //   for(int j=0;j<Detmu1jetF;j++){
              //     if(mindist_mu1hit_muJetF[j]<0.03 && mindist_mu1hit_muJetF[j]>=0.0) recover_muJetF=true;
              //   }
              //   for(int j=0;j<Detmu2jetF;j++){
              //     if(mindist_mu2hit_muJetF[j]<0.03 && mindist_mu2hit_muJetF[j]>=0.0) recover_muJetF=true;
              //   }
              // }

              if(recover_muJetF )  diMuonF_hits = true;
              if(hitrecover_mj2_r005==1 ) diMuonF_hits = true;
            }
	      
          }

          if(diMuonC_hits && diMuonF_hits){
            counter_rec_dimuons[p][2]++;
            if(is2DimDzOK){
              counter_rec_dimuons[p][3]++;
              if(is2DimHLTFired){
                counter_rec_dimuons[p][4]++;
                if(is2DimMassOK){
                  counter_rec_dimuons[p][5]++;
                  if(is2DimIsoTkOK){
                    counter_rec_dimuons[p][6]++;
                  }
                }
              }
            }
          }
  	}
      }
    }
  }
  


  double counter_gen_uncert[60][10];
  double counter_genlxylz_uncert[60][10];
  double counter_genlxylz2_uncert[60][10];
  double counter_rec_uncert[60][10];
  double counter_rec_hits_uncert[60][10];
  double counter_rec_dimuons_uncert[60][10];

  for(int k=0;k<60;k++){
    for(int j=0;j<10;j++){
      counter_gen_uncert[k][j] = sqrt((double)counter_gen[k][j]);
      counter_genlxylz_uncert[k][j] = sqrt((double)counter_genlxylz[k][j]);
      counter_genlxylz2_uncert[k][j] = sqrt((double)counter_genlxylz2[k][j]);
      counter_rec_uncert[k][j] = sqrt((double)counter_rec[k][j]);
      counter_rec_hits_uncert[k][j] = sqrt((double)counter_rec_hits[k][j]);
      counter_rec_dimuons_uncert[k][j] = sqrt((double)counter_rec_dimuons[k][j]);
    }
  }






  Float_t eff_mD0250[9]={0.0};
  Float_t eff_mD0275[1]={0.0};
  Float_t eff_mD0300[4]={0.0};
  Float_t eff_mD0350[1]={0.0};
  Float_t eff_mD0400[4]={0.0};
  Float_t eff_mD0550[5]={0.0};
  Float_t eff_mD0700[5]={0.0};
  Float_t eff_mD0850[5]={0.0};
  Float_t eff_mD1000[6]={0.0};
  Float_t eff_mD1500[3]={0.0};
  Float_t eff_mD2000[3]={0.0};
  Float_t eff_mssm[12]={0.0};

  Float_t erreff_mD0250[9]={0.0};
  Float_t erreff_mD0275[1]={0.0};
  Float_t erreff_mD0300[4]={0.0};
  Float_t erreff_mD0350[1]={0.0};
  Float_t erreff_mD0400[4]={0.0};
  Float_t erreff_mD0550[5]={0.0};
  Float_t erreff_mD0700[5]={0.0};
  Float_t erreff_mD0850[5]={0.0};
  Float_t erreff_mD1000[6]={0.0};
  Float_t erreff_mD1500[3]={0.0};
  Float_t erreff_mD2000[3]={0.0};
  Float_t erreff_mssm[12]={0.0};


  Float_t effr_mD0250[9]={0.0};
  Float_t effr_mD0275[1]={0.0};
  Float_t effr_mD0300[4]={0.0};
  Float_t effr_mD0350[1]={0.0};
  Float_t effr_mD0400[4]={0.0};
  Float_t effr_mD0550[5]={0.0};
  Float_t effr_mD0700[5]={0.0};
  Float_t effr_mD0850[5]={0.0};
  Float_t effr_mD1000[6]={0.0};
  Float_t effr_mD1500[3]={0.0};
  Float_t effr_mD2000[3]={0.0};
  Float_t effr_mssm[12]={0.0};

  Float_t erreffr_mD0250[9]={0.0};
  Float_t erreffr_mD0275[1]={0.0};
  Float_t erreffr_mD0300[4]={0.0};
  Float_t erreffr_mD0350[1]={0.0};
  Float_t erreffr_mD0400[4]={0.0};
  Float_t erreffr_mD0550[5]={0.0};
  Float_t erreffr_mD0700[5]={0.0};
  Float_t erreffr_mD0850[5]={0.0};
  Float_t erreffr_mD1000[6]={0.0};
  Float_t erreffr_mD1500[3]={0.0};
  Float_t erreffr_mD2000[3]={0.0};
  Float_t erreffr_mssm[12]={0.0};



  Float_t effr_mD0250_2[9]={0.0};
  Float_t effr_mD0275_2[1]={0.0};
  Float_t effr_mD0300_2[4]={0.0};
  Float_t effr_mD0350_2[1]={0.0};
  Float_t effr_mD0400_2[4]={0.0};
  Float_t effr_mD0550_2[5]={0.0};
  Float_t effr_mD0700_2[5]={0.0};
  Float_t effr_mD0850_2[5]={0.0};
  Float_t effr_mD1000_2[6]={0.0};
  Float_t effr_mD1500_2[3]={0.0};
  Float_t effr_mD2000_2[3]={0.0};

  Float_t erreffr_mD0250_2[9]={0.0};
  Float_t erreffr_mD0275_2[1]={0.0};
  Float_t erreffr_mD0300_2[4]={0.0};
  Float_t erreffr_mD0350_2[1]={0.0};
  Float_t erreffr_mD0400_2[4]={0.0};
  Float_t erreffr_mD0550_2[5]={0.0};
  Float_t erreffr_mD0700_2[5]={0.0};
  Float_t erreffr_mD0850_2[5]={0.0};
  Float_t erreffr_mD1000_2[6]={0.0};
  Float_t erreffr_mD1500_2[3]={0.0};
  Float_t erreffr_mD2000_2[3]={0.0};


  Float_t effr2_mD0250[9]={0.0};
  Float_t effr2_mD0275[1]={0.0};
  Float_t effr2_mD0300[4]={0.0};
  Float_t effr2_mD0350[1]={0.0};
  Float_t effr2_mD0400[4]={0.0};
  Float_t effr2_mD0550[5]={0.0};
  Float_t effr2_mD0700[5]={0.0};
  Float_t effr2_mD0850[5]={0.0};
  Float_t effr2_mD1000[6]={0.0};
  Float_t effr2_mD1500[3]={0.0};
  Float_t effr2_mD2000[3]={0.0};

  Float_t effr2_mssm[12]={0.0};






  Float_t erreffr2_mD0250[9]={0.0};
  Float_t erreffr2_mD0275[1]={0.0};
  Float_t erreffr2_mD0300[4]={0.0};
  Float_t erreffr2_mD0350[1]={0.0};
  Float_t erreffr2_mD0400[4]={0.0};
  Float_t erreffr2_mD0550[5]={0.0};
  Float_t erreffr2_mD0700[5]={0.0};
  Float_t erreffr2_mD0850[5]={0.0};
  Float_t erreffr2_mD1000[6]={0.0};
  Float_t erreffr2_mD1500[3]={0.0};
  Float_t erreffr2_mD2000[3]={0.0};

  Float_t erreffr2_mssm[12]={0.0};



  Float_t eff_ctau0[9];
  Float_t eff_ctau01[2];
  Float_t eff_ctau02[7];
  Float_t eff_ctau05[8];
  Float_t eff_ctau1[3];
  Float_t eff_ctau2[8];
  Float_t eff_ctau3[3];
  Float_t eff_ctau5[7];

  Float_t erreff_ctau0[9];
  Float_t erreff_ctau01[2];
  Float_t erreff_ctau02[7];
  Float_t erreff_ctau05[8];
  Float_t erreff_ctau1[3];
  Float_t erreff_ctau2[8];
  Float_t erreff_ctau3[3];
  Float_t erreff_ctau5[7];





  int counter_mass_ctau0[9] = {0,9,10,14,19,26,31,36,45};
  int counter_mass_ctau01[2] = {2,11};
  int counter_mass_ctau02[7] = {3,12,15,20,27,32,37};
  int counter_mass_ctau05[8] = {4,13,16,21,28,33,42,46};
  int counter_mass_ctau1[3] = {5,22,38};
  int counter_mass_ctau2[8] = {6,17,23,29,34,39,43,47};
  int counter_mass_ctau3[3] = {7,24,40};
  int counter_mass_ctau5[7] = {8,18,25,30,35,41,44};

  int counter_mssm[12] = {48,49,50,51,52,53,54,55,56,57,58,59};



  for(int l=0;l<9;l++) eff_ctau0[l]  = counter_rec_dimuons[counter_mass_ctau0[l]][6]/(counter_gen[counter_mass_ctau0[l]][0]*1.0);
  for(int l=0;l<2;l++) eff_ctau01[l]  = counter_rec_dimuons[counter_mass_ctau01[l]][6]/(counter_gen[counter_mass_ctau01[l]][0]*1.0);
  for(int l=0;l<7;l++) eff_ctau02[l]  = counter_rec_dimuons[counter_mass_ctau02[l]][6]/(counter_gen[counter_mass_ctau02[l]][0]*1.0);
  for(int l=0;l<8;l++) eff_ctau05[l]  = counter_rec_dimuons[counter_mass_ctau05[l]][6]/(counter_gen[counter_mass_ctau05[l]][0]*1.0);
  for(int l=0;l<3;l++) eff_ctau1[l]  = counter_rec_dimuons[counter_mass_ctau1[l]][6]/(counter_gen[counter_mass_ctau1[l]][0]*1.0);
  for(int l=0;l<8;l++) eff_ctau2[l]  = counter_rec_dimuons[counter_mass_ctau2[l]][6]/(counter_gen[counter_mass_ctau2[l]][0]*1.0);
  for(int l=0;l<3;l++) eff_ctau3[l]  = counter_rec_dimuons[counter_mass_ctau3[l]][6]/(counter_gen[counter_mass_ctau3[l]][0]*1.0);
  for(int l=0;l<7;l++) eff_ctau5[l]  = counter_rec_dimuons[counter_mass_ctau5[l]][6]/(counter_gen[counter_mass_ctau5[l]][0]*1.0);
  for(int l=0;l<12;l++) eff_mssm[l]  = counter_rec_dimuons[counter_mssm[l]][6]/(counter_gen[counter_mssm[l]][0]*1.0);

  for(int l=0;l<9;l++) erreff_ctau0[l]  = sqrt( (eff_ctau0[l]*(1-eff_ctau0[l]))/(counter_gen[counter_mass_ctau0[l]][0]*1.0));
  for(int l=0;l<2;l++) erreff_ctau01[l]  = sqrt( (eff_ctau01[l]*(1-eff_ctau01[l]))/(counter_gen[counter_mass_ctau01[l]][0]*1.0));
  for(int l=0;l<7;l++) erreff_ctau02[l]  = sqrt( (eff_ctau02[l]*(1-eff_ctau02[l]))/(counter_gen[counter_mass_ctau02[l]][0]*1.0));
  for(int l=0;l<8;l++) erreff_ctau05[l]  = sqrt( (eff_ctau05[l]*(1-eff_ctau05[l]))/(counter_gen[counter_mass_ctau05[l]][0]*1.0));
  for(int l=0;l<3;l++) erreff_ctau1[l]  = sqrt( (eff_ctau1[l]*(1-eff_ctau1[l]))/(counter_gen[counter_mass_ctau1[l]][0]*1.0));
  for(int l=0;l<8;l++) erreff_ctau2[l]  = sqrt( (eff_ctau2[l]*(1-eff_ctau2[l]))/(counter_gen[counter_mass_ctau2[l]][0]*1.0));
  for(int l=0;l<3;l++) erreff_ctau3[l]  = sqrt( (eff_ctau3[l]*(1-eff_ctau3[l]))/(counter_gen[counter_mass_ctau3[l]][0]*1.0));
  for(int l=0;l<7;l++) erreff_ctau5[l]  = sqrt( (eff_ctau5[l]*(1-eff_ctau5[l]))/(counter_gen[counter_mass_ctau5[l]][0]*1.0));
  for(int l=0;l<12;l++) erreff_mssm[l]  = sqrt( (eff_mssm[l]*(1-eff_mssm[l]))/(counter_gen[counter_mssm[l]][0]*1.0));

  Float_t mass1[9]={0.25,0.275,0.3,0.35,0.55,0.7,0.85,1.0,2.0};
  Float_t mass2[2]={0.25,0.3};
  Float_t mass3[7]={0.25,0.3,0.4,0.55,0.7,0.85,1.0};
  Float_t mass4[8]={0.25,0.3,0.4,0.55,0.7,0.85,1.5,2.0};
  Float_t mass5[3]={0.25,0.55,1.0};
  Float_t mass6[8]={0.25,0.4,0.55,0.7,0.85,1.0,1.5,2.0};
  Float_t mass7[3]={0.25,0.55,1.0};
  Float_t mass8[8]={0.25,0.4,0.5,0.7,0.85,1.0,1.5,2.0};

  Float_t errmass1[9]={0.0};
  Float_t errmass2[2]={0.0};
  Float_t errmass3[7]={0.0};
  Float_t errmass4[8]={0.0};
  Float_t errmass5[3]={0.0};
  Float_t errmass6[8]={0.0};
  Float_t errmass7[3]={0.0};
  Float_t errmass8[8]={0.0};




  //==========================

  for(int l=0;l<9;l++)   eff_mD0250[l] = counter_rec_dimuons[l][6]/(counter_gen[l][0]*1.0);
  for(int l=9;l<10;l++)  eff_mD0275[l-9] = counter_rec_dimuons[l][6]/(counter_gen[l][0]*1.0);
  for(int l=10;l<14;l++) eff_mD0300[l-10] = counter_rec_dimuons[l][6]/(counter_gen[l][0]*1.0);
  for(int l=14;l<15;l++) eff_mD0350[l-14] = counter_rec_dimuons[l][6]/(counter_gen[l][0]*1.0);
  for(int l=15;l<19;l++) eff_mD0400[l-15] = counter_rec_dimuons[l][6]/(counter_gen[l][0]*1.0);
  for(int l=19;l<26;l++){
    if ( (l == 23) || (l == 24) ) continue;
    eff_mD0550[l-19] = counter_rec_dimuons[l][6]/(counter_gen[l][0]*1.0);
  }
  for(int l=26;l<31;l++) eff_mD0700[l-26] = counter_rec_dimuons[l][6]/(counter_gen[l][0]*1.0);
  for(int l=31;l<36;l++) eff_mD0850[l-31] = counter_rec_dimuons[l][6]/(counter_gen[l][0]*1.0);
  for(int l=36;l<42;l++) eff_mD1000[l-36] = counter_rec_dimuons[l][6]/(counter_gen[l][0]*1.0);
  for(int l=42;l<45;l++) eff_mD1500[l-42] = counter_rec_dimuons[l][6]/(counter_gen[l][0]*1.0);
  for(int l=45;l<47;l++) eff_mD2000[l-45] = counter_rec_dimuons[l][6]/(counter_gen[l][0]*1.0);

  for(int l=0;l<9;l++)   erreff_mD0250[l] = sqrt( (eff_mD0250[l]*(1-eff_mD0250[l]))/(counter_gen[l][0]*1.0));
  for(int l=9;l<10;l++)  erreff_mD0275[l-9] = sqrt( (eff_mD0275[l-9]*(1-eff_mD0275[l-9]))/(counter_gen[l][0]*1.0));
  for(int l=10;l<14;l++) erreff_mD0300[l-10] = sqrt( (eff_mD0300[l-10]*(1-eff_mD0300[l-10]))/(counter_gen[l][0]*1.0));
  for(int l=14;l<15;l++) erreff_mD0350[l-14] = sqrt( (eff_mD0350[l-14]*(1-eff_mD0350[l-14]))/(counter_gen[l][0]*1.0));
  for(int l=15;l<19;l++) erreff_mD0400[l-15] = sqrt( (eff_mD0400[l-15]*(1-eff_mD0400[l-15]))/(counter_gen[l][0]*1.0));
  for(int l=19;l<26;l++){
    if ( (l == 23) || (l == 24) ) continue;
    erreff_mD0550[l-19] = sqrt( (eff_mD0550[l-19]*(1-eff_mD0550[l-19]))/(counter_gen[l][0]*1.0));
  }
  for(int l=26;l<31;l++) erreff_mD0700[l-26] = sqrt( (eff_mD0700[l-26]*(1-eff_mD0700[l-26]))/(counter_gen[l][0]*1.0));
  for(int l=31;l<36;l++) erreff_mD0850[l-31] = sqrt( (eff_mD0850[l-31]*(1-eff_mD0850[l-31]))/(counter_gen[l][0]*1.0));
  for(int l=36;l<42;l++) erreff_mD1000[l-36] = sqrt( (eff_mD1000[l-36]*(1-eff_mD1000[l-36]))/(counter_gen[l][0]*1.0));
  for(int l=42;l<45;l++) erreff_mD1500[l-42] = sqrt( (eff_mD1500[l-42]*(1-eff_mD1500[l-42]))/(counter_gen[l][0]*1.0));
  for(int l=45;l<47;l++) erreff_mD2000[l-45] = sqrt( (eff_mD2000[l-45]*(1-eff_mD2000[l-45]))/(counter_gen[l][0]*1.0));


  for(int l=0;l<9;l++)   effr_mD0250[l] = counter_rec_dimuons[l][6]/(counter_genlxylz2[l][4]*1.0);
  for(int l=9;l<10;l++)  effr_mD0275[l-9] = counter_rec_dimuons[l][6]/(counter_genlxylz2[l][4]*1.0);
  for(int l=10;l<14;l++) effr_mD0300[l-10] = counter_rec_dimuons[l][6]/(counter_genlxylz2[l][4]*1.0);
  for(int l=14;l<15;l++) effr_mD0350[l-14] = counter_rec_dimuons[l][6]/(counter_genlxylz2[l][4]*1.0);
  for(int l=15;l<19;l++) effr_mD0400[l-15] = counter_rec_dimuons[l][6]/(counter_genlxylz2[l][4]*1.0);
  for(int l=19;l<26;l++){
    if ( (l == 23) || (l == 24) ) continue;
    effr_mD0550[l-19] = counter_rec_dimuons[l][6]/(counter_genlxylz2[l][4]*1.0);
  }
  for(int l=26;l<31;l++) effr_mD0700[l-26] = counter_rec_dimuons[l][6]/(counter_genlxylz2[l][4]*1.0);
  for(int l=31;l<36;l++) effr_mD0850[l-31] = counter_rec_dimuons[l][6]/(counter_genlxylz2[l][4]*1.0);
  for(int l=36;l<42;l++) effr_mD1000[l-36] = counter_rec_dimuons[l][6]/(counter_genlxylz2[l][4]*1.0);
  for(int l=42;l<45;l++) effr_mD1500[l-42] = counter_rec_dimuons[l][6]/(counter_genlxylz2[l][4]*1.0);
  for(int l=45;l<47;l++) effr_mD2000[l-45] = counter_rec_dimuons[l][6]/(counter_genlxylz2[l][4]*1.0);

  for(int l=0;l<9;l++)   erreffr_mD0250[l] = sqrt( (effr_mD0250[l]*(1-effr_mD0250[l]))/(counter_genlxylz2[l][4]*1.0));
  for(int l=9;l<10;l++)  erreffr_mD0275[l-9] = sqrt( (effr_mD0275[l-9]*(1-effr_mD0275[l-9]))/(counter_genlxylz2[l][4]*1.0));
  for(int l=10;l<14;l++) erreffr_mD0300[l-10] = sqrt( (effr_mD0300[l-10]*(1-effr_mD0300[l-10]))/(counter_genlxylz2[l][4]*1.0));
  for(int l=14;l<15;l++) erreffr_mD0350[l-14] = sqrt( (effr_mD0350[l-14]*(1-effr_mD0350[l-14]))/(counter_genlxylz2[l][4]*1.0));
  for(int l=15;l<19;l++) erreffr_mD0400[l-15] = sqrt( (effr_mD0400[l-15]*(1-effr_mD0400[l-15]))/(counter_genlxylz2[l][4]*1.0));
  for(int l=19;l<26;l++){
    if ( (l == 23) || (l == 24) ) continue;
    erreffr_mD0550[l-19] = sqrt( (effr_mD0550[l-19]*(1-effr_mD0550[l-19]))/(counter_genlxylz2[l][4]*1.0));
  }
  for(int l=26;l<31;l++) erreffr_mD0700[l-26] = sqrt( (effr_mD0700[l-26]*(1-effr_mD0700[l-26]))/(counter_genlxylz2[l][4]*1.0));
  for(int l=31;l<36;l++) erreffr_mD0850[l-31] = sqrt( (effr_mD0850[l-31]*(1-effr_mD0850[l-31]))/(counter_genlxylz2[l][4]*1.0));
  for(int l=36;l<42;l++) erreffr_mD1000[l-36] = sqrt( (effr_mD1000[l-36]*(1-effr_mD1000[l-36]))/(counter_genlxylz2[l][4]*1.0));
  for(int l=42;l<45;l++) erreffr_mD1500[l-42] = sqrt( (effr_mD1500[l-42]*(1-effr_mD1500[l-42]))/(counter_genlxylz2[l][4]*1.0));
  for(int l=45;l<47;l++) erreffr_mD2000[l-45] = sqrt( (effr_mD2000[l-45]*(1-effr_mD2000[l-45]))/(counter_genlxylz2[l][4]*1.0));




  for(int l=0;l<9;l++)   effr_mD0250_2[l] = counter_rec_dimuons[l][6]/(counter_genlxylz2[l][4]*1.0);
  for(int l=9;l<10;l++)  effr_mD0275_2[l-9] = counter_rec_dimuons[l][6]/(counter_genlxylz2[l][4]*1.0);
  for(int l=10;l<14;l++) effr_mD0300_2[l-10] = counter_rec_dimuons[l][6]/(counter_genlxylz2[l][4]*1.0);
  for(int l=14;l<15;l++) effr_mD0350_2[l-14] = counter_rec_dimuons[l][6]/(counter_genlxylz2[l][4]*1.0);
  for(int l=15;l<19;l++) effr_mD0400_2[l-15] = counter_rec_dimuons[l][6]/(counter_genlxylz2[l][4]*1.0);
  for(int l=19;l<26;l++){
    if ( (l == 23) || (l == 24) ) continue;
    effr_mD0550_2[l-19] = counter_rec_dimuons[l][6]/(counter_genlxylz2[l][4]*1.0);
  }
  for(int l=26;l<31;l++) effr_mD0700_2[l-26] = counter_rec_dimuons[l][6]/(counter_genlxylz2[l][4]*1.0);
  for(int l=31;l<36;l++) effr_mD0850_2[l-31] = counter_rec_dimuons[l][6]/(counter_genlxylz2[l][4]*1.0);
  for(int l=36;l<42;l++) effr_mD1000_2[l-36] = counter_rec_dimuons[l][6]/(counter_genlxylz2[l][4]*1.0);
  for(int l=42;l<45;l++) effr_mD1500_2[l-42] = counter_rec_dimuons[l][6]/(counter_genlxylz2[l][4]*1.0);
  for(int l=45;l<47;l++) effr_mD2000_2[l-45] = counter_rec_dimuons[l][6]/(counter_genlxylz2[l][4]*1.0);

  for(int l=0;l<9;l++)   erreffr_mD0250_2[l] = sqrt( (effr_mD0250[l]*(1-effr_mD0250[l]))/(counter_genlxylz2[l][4]*1.0));
  for(int l=9;l<10;l++)  erreffr_mD0275_2[l-9] = sqrt( (effr_mD0275[l-9]*(1-effr_mD0275[l-9]))/(counter_genlxylz2[l][4]*1.0));
  for(int l=10;l<14;l++) erreffr_mD0300_2[l-10] = sqrt( (effr_mD0300[l-10]*(1-effr_mD0300[l-10]))/(counter_genlxylz2[l][4]*1.0));
  for(int l=14;l<15;l++) erreffr_mD0350_2[l-14] = sqrt( (effr_mD0350[l-14]*(1-effr_mD0350[l-14]))/(counter_genlxylz2[l][4]*1.0));
  for(int l=15;l<19;l++) erreffr_mD0400_2[l-15] = sqrt( (effr_mD0400[l-15]*(1-effr_mD0400[l-15]))/(counter_genlxylz2[l][4]*1.0));
  for(int l=19;l<26;l++){
    if ( (l == 23) || (l == 24) ) continue;
    erreffr_mD0550_2[l-19] = sqrt( (effr_mD0550[l-19]*(1-effr_mD0550[l-19]))/(counter_genlxylz2[l][4]*1.0));
  }
  for(int l=26;l<31;l++) erreffr_mD0700_2[l-26] = sqrt( (effr_mD0700[l-26]*(1-effr_mD0700[l-26]))/(counter_genlxylz2[l][4]*1.0));
  for(int l=31;l<36;l++) erreffr_mD0850_2[l-31] = sqrt( (effr_mD0850[l-31]*(1-effr_mD0850[l-31]))/(counter_genlxylz2[l][4]*1.0));
  for(int l=36;l<42;l++) erreffr_mD1000_2[l-36] = sqrt( (effr_mD1000[l-36]*(1-effr_mD1000[l-36]))/(counter_genlxylz2[l][4]*1.0));
  for(int l=42;l<45;l++) erreffr_mD1500_2[l-42] = sqrt( (effr_mD1500[l-42]*(1-effr_mD1500[l-42]))/(counter_genlxylz2[l][4]*1.0));
  for(int l=45;l<47;l++) erreffr_mD2000_2[l-45] = sqrt( (effr_mD2000[l-45]*(1-effr_mD2000[l-45]))/(counter_genlxylz2[l][4]*1.0));



  for(int l=0;l<9;l++)   effr2_mD0250[l] = counter_rec_dimuons[l][2]/(counter_rec_dimuons[l][1]*1.0);
  for(int l=9;l<10;l++)  effr2_mD0275[l-9] = counter_rec_dimuons[l][2]/(counter_rec_dimuons[l][1]*1.0);
  for(int l=10;l<14;l++) effr2_mD0300[l-10] = counter_rec_dimuons[l][2]/(counter_rec_dimuons[l][1]*1.0);
  for(int l=14;l<15;l++) effr2_mD0350[l-14] = counter_rec_dimuons[l][2]/(counter_rec_dimuons[l][1]*1.0);
  for(int l=15;l<19;l++) effr2_mD0400[l-15] = counter_rec_dimuons[l][2]/(counter_rec_dimuons[l][1]*1.0);
  for(int l=19;l<26;l++){
    if ( (l == 23) || (l == 24) ) continue;
    effr2_mD0550[l-19] = counter_rec_dimuons[l][2]/(counter_rec_dimuons[l][1]*1.0);
  }
  for(int l=26;l<31;l++) effr2_mD0700[l-26] = counter_rec_dimuons[l][2]/(counter_rec_dimuons[l][1]*1.0);
  for(int l=31;l<36;l++) effr2_mD0850[l-31] = counter_rec_dimuons[l][2]/(counter_rec_dimuons[l][1]*1.0);
  for(int l=36;l<42;l++) effr2_mD1000[l-36] = counter_rec_dimuons[l][2]/(counter_rec_dimuons[l][1]*1.0);
  for(int l=42;l<45;l++) effr2_mD1500[l-42] = counter_rec_dimuons[l][2]/(counter_rec_dimuons[l][1]*1.0);
  for(int l=45;l<47;l++) effr2_mD2000[l-45] = counter_rec_dimuons[l][2]/(counter_rec_dimuons[l][1]*1.0);

  for(int l=0;l<9;l++)   erreffr2_mD0250[l] = sqrt( (effr2_mD0250[l]*(1-effr2_mD0250[l]))/(counter_rec_dimuons[l][1]*1.0));
  for(int l=9;l<10;l++)  erreffr2_mD0275[l-9] = sqrt( (effr2_mD0275[l-9]*(1-effr2_mD0275[l-9]))/(counter_rec_dimuons[l][1]*1.0));
  for(int l=10;l<14;l++) erreffr2_mD0300[l-10] = sqrt( (effr2_mD0300[l-10]*(1-effr2_mD0300[l-10]))/(counter_rec_dimuons[l][1]*1.0));
  for(int l=14;l<15;l++) erreffr2_mD0350[l-14] = sqrt( (effr2_mD0350[l-14]*(1-effr2_mD0350[l-14]))/(counter_rec_dimuons[l][1]*1.0));
  for(int l=15;l<19;l++) erreffr2_mD0400[l-15] = sqrt( (effr2_mD0400[l-15]*(1-effr2_mD0400[l-15]))/(counter_rec_dimuons[l][1]*1.0));
  for(int l=19;l<26;l++){
    if ( (l == 23) || (l == 24) ) continue;
    erreffr2_mD0550[l-19] = sqrt( (effr2_mD0550[l-19]*(1-effr2_mD0550[l-19]))/(counter_rec_dimuons[l][1]*1.0));
  }
  for(int l=26;l<31;l++) erreffr2_mD0700[l-26] = sqrt( (effr2_mD0700[l-26]*(1-effr2_mD0700[l-26]))/(counter_rec_dimuons[l][1]*1.0));
  for(int l=31;l<36;l++) erreffr2_mD0850[l-31] = sqrt( (effr2_mD0850[l-31]*(1-effr2_mD0850[l-31]))/(counter_rec_dimuons[l][1]*1.0));
  for(int l=36;l<42;l++) erreffr2_mD1000[l-36] = sqrt( (effr2_mD1000[l-36]*(1-effr2_mD1000[l-36]))/(counter_rec_dimuons[l][1]*1.0));
  for(int l=42;l<45;l++) erreffr2_mD1500[l-42] = sqrt( (effr2_mD1500[l-42]*(1-effr2_mD1500[l-42]))/(counter_rec_dimuons[l][1]*1.0));
  for(int l=45;l<47;l++) erreffr2_mD2000[l-45] = sqrt( (effr2_mD2000[l-45]*(1-effr2_mD2000[l-45]))/(counter_rec_dimuons[l][1]*1.0));


  // cout<<" eff mD0250  "<<eff_mD0250[0]<<endl;
  // cout<<" eff mD0275  "<<eff_mD0275[0]<<endl;
  // cout<<" eff mD0300  "<<eff_mD0300[0]<<endl;
  // cout<<" eff mD0350  "<<eff_mD0350[0]<<endl;
  // cout<<" eff mD0400  "<<eff_mD0400[0]<<endl;
  // cout<<" eff mD0550  "<<eff_mD0550[0]<<endl;
  // cout<<" eff mD0700  "<<eff_mD0700[0]<<endl;
  // cout<<" eff mD0850  "<<eff_mD0850[0]<<endl;
  // cout<<" eff mD1000  "<<eff_mD1000[0]<<endl;
  // cout<<" eff mD1500  "<<eff_mD1500[0]<<endl;
  // cout<<" eff mD2000  "<<eff_mD2000[0]<<endl;



  // char *buf = new char[1000];
  char buf[100000];

  char pattern[] =  "%18s %2s %12s %2s %12s %2s %12s %2s %12s %2s %12s %2s %12s %2s %12s %2s %12s %2s";
  char pattern2[] = "%30s %2s %12.2f %2s %12.2f %12.3f %2s %12.2f %2s %12.2f %12.3f %2s %12.2f %2s %12.2f %12.3f %2s %12.2f %2s %12.2f %12.3f %2s";
  char pattern4[] = "%18s %2s %2s %12.4f %12.4f %2s %2s %12.4f %12.4f %2s %2s %12.4f %12.4f %2s %2s %12.4f %12.4f %2s";
  char pattern3[] = "%50s";




  string sample_mass[6]={"$m_{\\gamma_D}=0.25$","$m_{\\gamma_D}=0.55$","$m_{\\gamma_D}=0.7$","$m_{\\gamma_D}=0.85$","$m_{\\gamma_D}=1.0$","$m_{\\gamma_D}=2.0$"};

  string cutsgen[5]={"All events","$p_{T_1} > 17$ GeV, $|\\eta|< 0.9$","$p_{T_2} > 8$ GeV, $|\\eta|< 2.4$","$p_{T_3} > 8$ GeV, $|\\eta|< 2.4$","$p_{T_4} > 8$ GeV, $|\\eta|< 2.4$"};
  string cutsrec[4]={"$p_{T_1} > 17$ GeV, $|\\eta|< 0.9$","$p_{T_2} > 8$ GeV, $|\\eta|< 2.4$","$p_{T_3} > 8$ GeV, $|\\eta|< 2.4$","$p_{T_4} > 8$ GeV, $|\\eta|< 2.4$"};
  //  string cutsdim[7]={"2$\\mu_{jet}$","2$\\mu/\\mu_{jet}$","$hit_{1st pixel}$","$|Z_{\\mu jet1} - Z_{\\mu jet2}|<0.1$","$trigger$","$compatilbleMass.$","$Iso_{\\mu jet 1,2}<2 GeV$"};
  string cutsdim[7]={"$N$($\\mu$-jets) $= 2$","2$\\mu$ per $\\mu$-jet","PXB/PXF 1$^{\\mathrm{st}}$ layer hit","$|\\Delta z|<0.1$ cm","Trigger","$m_{\\mu\\mu_1} \\approx m_{\\mu\\mu_2}$","$\\mu$-jet isolation $ <2$ GeV"};

  std::ostringstream out;  

  std::cout << "\\documentclass[11pt]{article}" << std::endl;
  std::cout << "\\usepackage[margin=0.5in]{geometry}" << std::endl;
  std::cout << "\\usepackage{graphicx} % Allows including images" << std::endl;
  std::cout << "\\usepackage{multicol}" << std::endl;
  std::cout << "\\usepackage{lscape}" << std::endl;
  std::cout << "\\begin{document}" << std::endl;




  int indx[10];
  for(int k=0;k<6;k++){

    out.str("");
    out.clear();
    std::cout << "\\begin{landscape}" << std::endl;
    cout<<" \\begin{table}[ht]         "<<endl;
    std::cout << "\\renewcommand{\\tabcolsep}{2pt}" << std::endl;

    if (k < 6){
      cout << "\\caption{Acceptances and efficiencies (all in \\%) of the event selection requirements for several representative benchmark values of $c \\tau$ for fixed masses $m_{h_{1}} = 125$~GeV$/c^{2}$, $m_{n_{1}} = 10$~GeV$/c^{2}$,  $m_{n_{D}} = 1$~GeV$/c^{2}$ and " << sample_mass[k].c_str() << " GeV$/c^{2}$ in MC simulation of Dark SUSY signal. \\label{tab:eff_darkSUSY_mGammaD025}}" << std::endl;
    }
    else {
      cout << "\\caption{Acceptances and efficiencies (all in \\%) of the event selection requirements for the samples with $m_{h_{1}} = 125$~GeV$/c^{2}$, and several representative benchmark values of $m_{a_1}$ in the MC simulation of NMSSM signal. \\label{tab:eff_NMSSM_mh125}}" << std::endl;
    }

    cout<<" \\centering               "<<endl;
 
    if (k!=1 && k!= 5 && k != 6 && k!= 7){
      cout<<" \\begin{tabular}{|l|c|c|c|c|c|c|c|c|} \\hline  "<<endl;
      out << sample_mass[k].c_str() << "~GeV$/c^{2}$ & \\multicolumn{2}{c|}{$c\\tau=0$ mm} & \\multicolumn{2}{c|}{$c\\tau=0.2$ mm} & \\multicolumn{2}{c|}{$c\\tau=2$ mm} & \\multicolumn{2}{c|}{$c\\tau=5$ mm} \\\\ \\hline"<<endl;
      out << "  Selection  " << "&" << "  $N_{evts}$  " << "&" << "  Rel. Eff(\\%)  " << "&"  << "  $N_{evts}$  " << "&" << "  Rel. Eff(\\%)  "  << "&" << "  $N_{evts}$  " << "&" << "  Rel. Eff(\\%)  "  << "&" << "$N_{evts}$" << "&" << "Rel. Eff(\\%)" <<  "\\\\";
    }
    else if (k ==1 || k ==5) {
      cout<<" \\begin{tabular}{|l|c|c|c|c|c|c|} \\hline  "<<endl;
      if (k==1) out << sample_mass[k].c_str() << "~GeV$/c^{2}$ & \\multicolumn{2}{c|}{$c\\tau=0$ mm} & \\multicolumn{2}{c|}{$c\\tau=0.2$ mm} & \\multicolumn{2}{c|}{$c\\tau=5$ mm} \\\\ \\hline"<<endl;
      if (k==5) out << sample_mass[k].c_str() << "~GeV$/c^{2}$ & \\multicolumn{2}{c|}{$c\\tau=0$ mm} & \\multicolumn{2}{c|}{$c\\tau=0.2$ mm} & \\multicolumn{2}{c|}{$c\\tau=2$ mm} \\\\ \\hline"<<endl;
      out << "  Selection  " << "&" << "  $N_{evts}$  " << "&" << "  Rel. Eff(\\%)  " << "&"  << "  $N_{evts}$  " << "&" << "  Rel. Eff(\\%)  "  << "&" << "  $N_{evts}$  " << "&" << "  Rel. Eff(\\%)  "  << "\\\\";
    }

    out <<" \\hline  "<<endl;
    
    if(k==0){ indx[0]=0;indx[1]=3;indx[2]=6;indx[3]=8;} //mD=0.25GeV
    if(k==1){ indx[0]=19;indx[1]=20;indx[2]=25;indx[3]=25;} //mD=0.55GeV
    if(k==2){ indx[0]=26;indx[1]=27;indx[2]=29;indx[3]=30;} //mD=0.7 GeV
    if(k==3){ indx[0]=31;indx[1]=32;indx[2]=34;indx[3]=35;} //mD=0.85GeV
    if(k==4){ indx[0]=36;indx[1]=37;indx[2]=39;indx[3]=41;} //mD=1GeV
    if(k==5){ indx[0]=45;indx[1]=46;indx[2]=47;indx[3]=47;} //mD=2GeV


    if (k!=1 && k!= 5 && k !=6 && k !=7){
      out <<  cutsgen[0].c_str() << "&" << std::setprecision(2) << counter_gen[indx[0]][0] << "&" << "&" << counter_gen[indx[1]][0] << "&"  << "&" << counter_gen[indx[2]][0] << "&"  << "&" << counter_gen[indx[3]][0] <<  "&" << "\\\\ \\hline" << std::endl;
    }
    else if (k ==1 || k ==5){
      out <<  cutsgen[0].c_str() << "&" << std::setprecision(2) << counter_gen[indx[0]][0] << "&" << "&" << counter_gen[indx[1]][0] << "&"  << "&" << counter_gen[indx[2]][0] << "&"  << "\\\\ \\hline" << std::endl;
    }
    out << "\\multicolumn{2}{|c}{\\textbf{Basic event selections (gen):}} \\\\ \\hline" << std::endl;


    for(int j=1;j<5;j++){

      if (k!=1 && k!= 5 && k !=6 && k !=7){        
        out << cutsgen[j].c_str() << "&" << std::fixed << counter_gen[indx[0]][j] << "&" << counter_gen[indx[0]][j]/(counter_gen[indx[0]][j-1]*1.0) << " $\\pm$ ";
        out << std::setprecision(2) << (counter_gen[indx[0]][j]/(counter_gen[indx[0]][j-1]*1.0))*sqrt(((counter_gen_uncert[indx[0]][j]/(double)counter_gen[indx[0]][j])*(counter_gen_uncert[indx[0]][j]/(double)counter_gen[indx[0]][j])) + ((counter_gen_uncert[indx[0]][j-1]/(double)counter_gen[indx[0]][j-1])*(counter_gen_uncert[indx[0]][j-1]/(double)counter_gen[indx[0]][j-1])))  << "&" << std::fixed << counter_gen[indx[1]][j] << "&" << counter_gen[indx[1]][j]/(counter_gen[indx[1]][j-1]*1.0) << " $\\pm$ ";
        out <<  std::setprecision(2) << (counter_gen[indx[1]][j]/(counter_gen[indx[1]][j-1]*1.0))*sqrt(((counter_gen_uncert[indx[1]][j]/(double)counter_gen[indx[1]][j])*(counter_gen_uncert[indx[1]][j]/(double)counter_gen[indx[1]][j])) + ((counter_gen_uncert[indx[1]][j-1]/(double)counter_gen[indx[1]][j-1])*(counter_gen_uncert[indx[1]][j-1]/(double)counter_gen[indx[1]][j-1])))   << "&" << std::fixed << counter_gen[indx[2]][j] << "&" << counter_gen[indx[2]][j]/(counter_gen[indx[2]][j-1]*1.0) << " $\\pm$ ";
        out <<  std::setprecision(2) <<   (counter_gen[indx[2]][j]/(counter_gen[indx[2]][j-1]*1.0))*sqrt(((counter_gen_uncert[indx[2]][j]/(double)counter_gen[indx[2]][j])*(counter_gen_uncert[indx[2]][j]/(double)counter_gen[indx[2]][j])) + ((counter_gen_uncert[indx[2]][j-1]/(double)counter_gen[indx[2]][j-1])*(counter_gen_uncert[indx[2]][j-1]/(double)counter_gen[indx[2]][j-1])))  << "&" << std::fixed << counter_gen[indx[3]][j] << "&" << counter_gen[indx[3]][j]/(counter_gen[indx[3]][j-1]*1.0) << " $\\pm$ ";
        out <<  std::setprecision(2) << (counter_gen[indx[3]][j]/(counter_gen[indx[3]][j-1]*1.0))*sqrt(((counter_gen_uncert[indx[3]][j]/(double)counter_gen[indx[3]][j])*(counter_gen_uncert[indx[3]][j]/(double)counter_gen[indx[3]][j])) + ((counter_gen_uncert[indx[3]][j-1]/(double)counter_gen[indx[3]][j-1])*(counter_gen_uncert[indx[3]][j-1]/(double)counter_gen[indx[3]][j-1])))   << "\\\\" << std::endl;
      }

      else if (k ==1 || k ==5) {        
        out << cutsgen[j].c_str() << "&" << std::fixed << counter_gen[indx[0]][j] << "&" << counter_gen[indx[0]][j]/(counter_gen[indx[0]][j-1]*1.0) << " $\\pm$ ";
        out << std::setprecision(2) << (counter_gen[indx[0]][j]/(counter_gen[indx[0]][j-1]*1.0))*sqrt(((counter_gen_uncert[indx[0]][j]/(double)counter_gen[indx[0]][j])*(counter_gen_uncert[indx[0]][j]/(double)counter_gen[indx[0]][j])) + ((counter_gen_uncert[indx[0]][j-1]/(double)counter_gen[indx[0]][j-1])*(counter_gen_uncert[indx[0]][j-1]/(double)counter_gen[indx[0]][j-1])))  << "&" << std::fixed << counter_gen[indx[1]][j] << "&" << counter_gen[indx[1]][j]/(counter_gen[indx[1]][j-1]*1.0) << " $\\pm$ ";
        out <<  std::setprecision(2) << (counter_gen[indx[1]][j]/(counter_gen[indx[1]][j-1]*1.0))*sqrt(((counter_gen_uncert[indx[1]][j]/(double)counter_gen[indx[1]][j])*(counter_gen_uncert[indx[1]][j]/(double)counter_gen[indx[1]][j])) + ((counter_gen_uncert[indx[1]][j-1]/(double)counter_gen[indx[1]][j-1])*(counter_gen_uncert[indx[1]][j-1]/(double)counter_gen[indx[1]][j-1])))   << "&" << std::fixed << counter_gen[indx[2]][j] << "&" << counter_gen[indx[2]][j]/(counter_gen[indx[2]][j-1]*1.0) << " $\\pm$ ";
        out <<  std::setprecision(2) <<   (counter_gen[indx[2]][j]/(counter_gen[indx[2]][j-1]*1.0))*sqrt(((counter_gen_uncert[indx[2]][j]/(double)counter_gen[indx[2]][j])*(counter_gen_uncert[indx[2]][j]/(double)counter_gen[indx[2]][j])) + ((counter_gen_uncert[indx[2]][j-1]/(double)counter_gen[indx[2]][j-1])*(counter_gen_uncert[indx[2]][j-1]/(double)counter_gen[indx[2]][j-1])))  << "\\\\" << std::endl;
      }
    }

    if (k!=1 && k!= 5 && k !=6 && k !=7){        
      out << "$L_{xy} < 4.4$ cm, $L_z < 34.5$ cm" << "&" << counter_genlxylz2[indx[0]][4] << "&" << counter_genlxylz2[indx[0]][4]/(counter_gen[indx[0]][4]*1.0) << " $\\pm$ ";
      // out.unsetf(ios_base::fixed);
      out << std::setprecision(2) <<  (counter_genlxylz2[indx[0]][4]/(counter_gen[indx[0]][4]*1.0))*sqrt(((counter_genlxylz2_uncert[indx[0]][4]/(double)counter_genlxylz2[indx[0]][4])*(counter_genlxylz2_uncert[indx[0]][4]/(double)counter_genlxylz2[indx[0]][4])) + ((counter_gen_uncert[indx[0]][4]/(double)counter_gen[indx[0]][4])*(counter_gen_uncert[indx[0]][4]/(double)counter_gen[indx[0]][4])))  << "&" << counter_genlxylz2[indx[1]][4] << "&" << counter_genlxylz2[indx[1]][4]/(counter_gen[indx[1]][4]*1.0) << " $\\pm$ ";
      // out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_genlxylz2[indx[1]][4]/(counter_gen[indx[1]][4]*1.0))*sqrt(((counter_genlxylz2_uncert[indx[1]][4]/(double)counter_genlxylz2[indx[1]][4])*(counter_genlxylz2_uncert[indx[1]][4]/(double)counter_genlxylz2[indx[1]][4])) + ((counter_gen_uncert[indx[1]][4]/(double)counter_gen[indx[1]][4])*(counter_gen_uncert[indx[1]][4]/(double)counter_gen[indx[1]][4]))) << "&" << counter_genlxylz2[indx[2]][4] << "&" << counter_genlxylz2[indx[2]][4]/(counter_gen[indx[2]][4]*1.0) << " $\\pm$ ";
      // out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_genlxylz2[indx[2]][4]/(counter_gen[indx[2]][4]*1.0))*sqrt(((counter_genlxylz2_uncert[indx[2]][4]/(double)counter_genlxylz2[indx[2]][4])*(counter_genlxylz2_uncert[indx[2]][4]/(double)counter_genlxylz2[indx[2]][4])) + ((counter_gen_uncert[indx[2]][4]/(double)counter_gen[indx[2]][4])*(counter_gen_uncert[indx[2]][4]/(double)counter_gen[indx[2]][4])))   << "&" << counter_genlxylz2[indx[3]][4] << "&" << counter_genlxylz2[indx[3]][4]/(counter_gen[indx[3]][4]*1.0) << " $\\pm$ ";
      // out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_genlxylz2[indx[3]][4]/(counter_gen[indx[3]][4]*1.0))*sqrt(((counter_genlxylz2_uncert[indx[3]][4]/(double)counter_genlxylz2[indx[3]][4])*(counter_genlxylz2_uncert[indx[3]][4]/(double)counter_genlxylz2[indx[3]][4])) + ((counter_gen_uncert[indx[3]][4]/(double)counter_gen[indx[3]][4])*(counter_gen_uncert[indx[3]][4]/(double)counter_gen[indx[3]][4])))   << "\\\\ \\hline" << std::endl;
    }
    else if (k ==1 || k ==5) {
      out << "$L_{xy} < 4.4$ cm, $L_z < 34.5$ cm" << "&" << counter_genlxylz2[indx[0]][4] << "&" << counter_genlxylz2[indx[0]][4]/(counter_gen[indx[0]][4]*1.0) << " $\\pm$ ";
      // out.unsetf(ios_base::fixed);
      out << std::setprecision(2) <<  (counter_genlxylz2[indx[0]][4]/(counter_gen[indx[0]][4]*1.0))*sqrt(((counter_genlxylz2_uncert[indx[0]][4]/(double)counter_genlxylz2[indx[0]][4])*(counter_genlxylz2_uncert[indx[0]][4]/(double)counter_genlxylz2[indx[0]][4])) + ((counter_gen_uncert[indx[0]][4]/(double)counter_gen[indx[0]][4])*(counter_gen_uncert[indx[0]][4]/(double)counter_gen[indx[0]][4])))  << "&" << counter_genlxylz2[indx[1]][4] << "&" << counter_genlxylz2[indx[1]][4]/(counter_gen[indx[1]][4]*1.0) << " $\\pm$ ";
      // out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_genlxylz2[indx[1]][4]/(counter_gen[indx[1]][4]*1.0))*sqrt(((counter_genlxylz2_uncert[indx[1]][4]/(double)counter_genlxylz2[indx[1]][4])*(counter_genlxylz2_uncert[indx[1]][4]/(double)counter_genlxylz2[indx[1]][4])) + ((counter_gen_uncert[indx[1]][4]/(double)counter_gen[indx[1]][4])*(counter_gen_uncert[indx[1]][4]/(double)counter_gen[indx[1]][4]))) << "&" << counter_genlxylz2[indx[2]][4] << "&" << counter_genlxylz2[indx[2]][4]/(counter_gen[indx[2]][4]*1.0) << " $\\pm$ ";
      // out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_genlxylz2[indx[2]][4]/(counter_gen[indx[2]][4]*1.0))*sqrt(((counter_genlxylz2_uncert[indx[2]][4]/(double)counter_genlxylz2[indx[2]][4])*(counter_genlxylz2_uncert[indx[2]][4]/(double)counter_genlxylz2[indx[2]][4])) + ((counter_gen_uncert[indx[2]][4]/(double)counter_gen[indx[2]][4])*(counter_gen_uncert[indx[2]][4]/(double)counter_gen[indx[2]][4])))   <<  "\\\\ \\hline" << std::endl;
    }


    out << "\\multicolumn{2}{|c}{\\textbf{Basic event selections (reco):}} \\\\ \\hline" << std::endl;

    for(int j=0;j<4;j++){

      if (k!=1 && k!= 5 && k !=6 && k !=7){        
        if(j==0){
          out << cutsrec[j].c_str() << "&" << counter_rec[indx[0]][j] << "&" << counter_rec[indx[0]][j]/(counter_gen[indx[0]][j]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) << (counter_rec[indx[0]][j]/(counter_gen[indx[0]][j]*1.0))*sqrt(((counter_rec_uncert[indx[0]][j]/(double)counter_rec[indx[0]][j])*(counter_rec_uncert[indx[0]][j]/(double)counter_rec[indx[0]][j])) + ((counter_gen_uncert[indx[0]][j]/(double)counter_gen[indx[0]][j])*(counter_gen_uncert[indx[0]][j]/(double)counter_gen[indx[0]][j])))  << "&" << counter_rec[indx[1]][j] << "&" << counter_rec[indx[1]][j]/(counter_gen[indx[1]][j]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) << (counter_rec[indx[1]][j]/(counter_gen[indx[1]][j]*1.0))*sqrt(((counter_rec_uncert[indx[1]][j]/(double)counter_rec[indx[1]][j])*(counter_rec_uncert[indx[1]][j]/(double)counter_rec[indx[1]][j])) + ((counter_gen_uncert[indx[1]][j]/(double)counter_gen[indx[1]][j])*(counter_gen_uncert[indx[1]][j]/(double)counter_gen[indx[1]][j]))) << "&" << counter_rec[indx[2]][j] << "&" << counter_rec[indx[2]][j]/(counter_gen[indx[2]][j]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) << (counter_rec[indx[2]][j]/(counter_gen[indx[2]][j]*1.0))*sqrt(((counter_rec_uncert[indx[2]][j]/(double)counter_rec[indx[2]][j])*(counter_rec_uncert[indx[2]][j]/(double)counter_rec[indx[2]][j])) + ((counter_gen_uncert[indx[2]][j]/(double)counter_gen[indx[2]][j])*(counter_gen_uncert[indx[2]][j]/(double)counter_gen[indx[2]][j]))) << "&" << counter_rec[indx[3]][j] << "&" << counter_rec[indx[3]][j]/(counter_gen[indx[3]][j]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) << (counter_rec[indx[3]][j]/(counter_gen[indx[3]][j]*1.0))*sqrt(((counter_rec_uncert[indx[3]][j]/(double)counter_rec[indx[3]][j])*(counter_rec_uncert[indx[3]][j]/(double)counter_rec[indx[3]][j])) + ((counter_gen_uncert[indx[3]][j]/(double)counter_gen[indx[3]][j])*(counter_gen_uncert[indx[3]][j]/(double)counter_gen[indx[3]][j])))  << "\\\\" << std::endl;
        }
        if(j>0){
          out << cutsrec[j].c_str() << "&" << counter_rec[indx[0]][j] << "&" << counter_rec[indx[0]][j]/(counter_rec[indx[0]][j-1]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) << (counter_rec[indx[0]][j]/(counter_rec[indx[0]][j-1]*1.0))*sqrt(((counter_rec_uncert[indx[0]][j]/(double)counter_rec[indx[0]][j])*(counter_rec_uncert[indx[0]][j]/(double)counter_rec[indx[0]][j])) + ((counter_rec_uncert[indx[0]][j-1]/(double)counter_rec[indx[0]][j-1])*(counter_rec_uncert[indx[0]][j-1]/(double)counter_rec[indx[0]][j-1])))  << "&" << counter_rec[indx[1]][j] << "&" << counter_rec[indx[1]][j]/(counter_rec[indx[1]][j-1]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) << (counter_rec[indx[1]][j]/(counter_rec[indx[1]][j-1]*1.0))*sqrt(((counter_rec_uncert[indx[1]][j]/(double)counter_rec[indx[1]][j])*(counter_rec_uncert[indx[1]][j]/(double)counter_rec[indx[1]][j])) + ((counter_rec_uncert[indx[1]][j-1]/(double)counter_rec[indx[1]][j-1])*(counter_rec_uncert[indx[1]][j-1]/(double)counter_rec[indx[1]][j-1])))  << "&" << counter_rec[indx[2]][j] << "&" << counter_rec[indx[2]][j]/(counter_rec[indx[2]][j-1]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) << (counter_rec[indx[2]][j]/(counter_rec[indx[2]][j-1]*1.0))*sqrt(((counter_rec_uncert[indx[2]][j]/(double)counter_rec[indx[2]][j])*(counter_rec_uncert[indx[2]][j]/(double)counter_rec[indx[2]][j])) + ((counter_rec_uncert[indx[2]][j-1]/(double)counter_rec[indx[2]][j-1])*(counter_rec_uncert[indx[2]][j-1]/(double)counter_rec[indx[2]][j-1])))  << "&" << counter_rec[indx[3]][j] << "&" << counter_rec[indx[3]][j]/(counter_rec[indx[3]][j-1]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) << (counter_rec[indx[3]][j]/(counter_rec[indx[3]][j-1]*1.0))*sqrt(((counter_rec_uncert[indx[3]][j]/(double)counter_rec[indx[3]][j])*(counter_rec_uncert[indx[3]][j]/(double)counter_rec[indx[3]][j])) + ((counter_rec_uncert[indx[3]][j-1]/(double)counter_rec[indx[3]][j-1])*(counter_rec_uncert[indx[3]][j-1]/(double)counter_rec[indx[3]][j-1])))  << "\\\\ " << std::endl;
        }
      }
      else if (k ==1 || k ==5) {
        if(j==0){
          out << cutsrec[j].c_str() << "&" << counter_rec[indx[0]][j] << "&" << counter_rec[indx[0]][j]/(counter_gen[indx[0]][j]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) << (counter_rec[indx[0]][j]/(counter_gen[indx[0]][j]*1.0))*sqrt(((counter_rec_uncert[indx[0]][j]/(double)counter_rec[indx[0]][j])*(counter_rec_uncert[indx[0]][j]/(double)counter_rec[indx[0]][j])) + ((counter_gen_uncert[indx[0]][j]/(double)counter_gen[indx[0]][j])*(counter_gen_uncert[indx[0]][j]/(double)counter_gen[indx[0]][j])))  << "&" << counter_rec[indx[1]][j] << "&" << counter_rec[indx[1]][j]/(counter_gen[indx[1]][j]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) << (counter_rec[indx[1]][j]/(counter_gen[indx[1]][j]*1.0))*sqrt(((counter_rec_uncert[indx[1]][j]/(double)counter_rec[indx[1]][j])*(counter_rec_uncert[indx[1]][j]/(double)counter_rec[indx[1]][j])) + ((counter_gen_uncert[indx[1]][j]/(double)counter_gen[indx[1]][j])*(counter_gen_uncert[indx[1]][j]/(double)counter_gen[indx[1]][j]))) << "&" << counter_rec[indx[2]][j] << "&" << counter_rec[indx[2]][j]/(counter_gen[indx[2]][j]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) << (counter_rec[indx[2]][j]/(counter_gen[indx[2]][j]*1.0))*sqrt(((counter_rec_uncert[indx[2]][j]/(double)counter_rec[indx[2]][j])*(counter_rec_uncert[indx[2]][j]/(double)counter_rec[indx[2]][j])) + ((counter_gen_uncert[indx[2]][j]/(double)counter_gen[indx[2]][j])*(counter_gen_uncert[indx[2]][j]/(double)counter_gen[indx[2]][j]))) <<   "\\\\" << std::endl;
        }
        if(j>0){
          out << cutsrec[j].c_str() << "&" << counter_rec[indx[0]][j] << "&" << counter_rec[indx[0]][j]/(counter_rec[indx[0]][j-1]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) << (counter_rec[indx[0]][j]/(counter_rec[indx[0]][j-1]*1.0))*sqrt(((counter_rec_uncert[indx[0]][j]/(double)counter_rec[indx[0]][j])*(counter_rec_uncert[indx[0]][j]/(double)counter_rec[indx[0]][j])) + ((counter_rec_uncert[indx[0]][j-1]/(double)counter_rec[indx[0]][j-1])*(counter_rec_uncert[indx[0]][j-1]/(double)counter_rec[indx[0]][j-1])))  << "&" << counter_rec[indx[1]][j] << "&" << counter_rec[indx[1]][j]/(counter_rec[indx[1]][j-1]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) << (counter_rec[indx[1]][j]/(counter_rec[indx[1]][j-1]*1.0))*sqrt(((counter_rec_uncert[indx[1]][j]/(double)counter_rec[indx[1]][j])*(counter_rec_uncert[indx[1]][j]/(double)counter_rec[indx[1]][j])) + ((counter_rec_uncert[indx[1]][j-1]/(double)counter_rec[indx[1]][j-1])*(counter_rec_uncert[indx[1]][j-1]/(double)counter_rec[indx[1]][j-1])))  << "&" << counter_rec[indx[2]][j] << "&" << counter_rec[indx[2]][j]/(counter_rec[indx[2]][j-1]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) << (counter_rec[indx[2]][j]/(counter_rec[indx[2]][j-1]*1.0))*sqrt(((counter_rec_uncert[indx[2]][j]/(double)counter_rec[indx[2]][j])*(counter_rec_uncert[indx[2]][j]/(double)counter_rec[indx[2]][j])) + ((counter_rec_uncert[indx[2]][j-1]/(double)counter_rec[indx[2]][j-1])*(counter_rec_uncert[indx[2]][j-1]/(double)counter_rec[indx[2]][j-1])))  <<  "\\\\ " << std::endl;
        }
      }
    }
    out << " \\hline " << std::endl;
    out << "\\multicolumn{2}{|c}{\\textbf{Auxiliary event selections (reco):}} \\\\ \\hline" << std::endl;

    for(int j=0;j<2;j++){

      if (k!=1 && k!= 5 && k !=6 && k !=7){        
        if(j==0)
        {
          out << cutsdim[j].c_str() << "&" << counter_rec_dimuons[indx[0]][j] << "&" << counter_rec_dimuons[indx[0]][j]/(counter_rec[indx[0]][3]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) << (counter_rec_dimuons[indx[0]][j]/(counter_rec[indx[0]][3]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[0]][j]/(double)counter_rec_dimuons[indx[0]][j])*(counter_rec_dimuons_uncert[indx[0]][j]/(double)counter_rec_dimuons[indx[0]][j])) + ((counter_rec_uncert[indx[0]][3]/(double)counter_rec[indx[0]][3])*(counter_rec_uncert[indx[0]][3]/(double)counter_rec[indx[0]][3])))  << "&" << counter_rec_dimuons[indx[1]][j] << "&" << counter_rec_dimuons[indx[1]][j]/(counter_rec[indx[1]][3]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) << (counter_rec_dimuons[indx[1]][j]/(counter_rec[indx[1]][3]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[1]][j]/(double)counter_rec_dimuons[indx[1]][j])*(counter_rec_dimuons_uncert[indx[1]][j]/(double)counter_rec_dimuons[indx[1]][j])) + ((counter_rec_uncert[indx[1]][3]/(double)counter_rec[indx[1]][3])*(counter_rec_uncert[indx[1]][3]/(double)counter_rec[indx[1]][3]))) << "&" << counter_rec_dimuons[indx[2]][j] << "&" << counter_rec_dimuons[indx[2]][j]/(counter_rec[indx[2]][3]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) << (counter_rec_dimuons[indx[2]][j]/(counter_rec[indx[2]][3]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[2]][j]/(double)counter_rec_dimuons[indx[2]][j])*(counter_rec_dimuons_uncert[indx[2]][j]/(double)counter_rec_dimuons[indx[2]][j])) + ((counter_rec_uncert[indx[2]][3]/(double)counter_rec[indx[2]][3])*(counter_rec_uncert[indx[2]][3]/(double)counter_rec[indx[2]][3])))  << "&" << counter_rec_dimuons[indx[3]][j] << "&" << counter_rec_dimuons[indx[3]][j]/(counter_rec[indx[3]][3]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) <<  (counter_rec_dimuons[indx[3]][j]/(counter_rec[indx[3]][3]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[3]][j]/(double)counter_rec_dimuons[indx[3]][j])*(counter_rec_dimuons_uncert[indx[3]][j]/(double)counter_rec_dimuons[indx[3]][j])) + ((counter_rec_uncert[indx[3]][3]/(double)counter_rec[indx[3]][3])*(counter_rec_uncert[indx[3]][3]/(double)counter_rec[indx[3]][3])))  << "\\\\" << std::endl;
        }
        if(j>0)
        {
          out << cutsdim[j].c_str() << "&" << counter_rec_dimuons[indx[0]][j] << "&" << counter_rec_dimuons[indx[0]][j]/(counter_rec_dimuons[indx[0]][j-1]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) <<  (counter_rec_dimuons[indx[0]][j]/(counter_rec_dimuons[indx[0]][j-1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[0]][j]/(double)counter_rec_dimuons[indx[0]][j])*(counter_rec_dimuons_uncert[indx[0]][j]/(double)counter_rec_dimuons[indx[0]][j])) + ((counter_rec_uncert[indx[0]][j-1]/(double)counter_rec_dimuons[indx[0]][j-1])*(counter_rec_uncert[indx[0]][j-1]/(double)counter_rec_dimuons[indx[0]][j-1]))) << "&" << counter_rec_dimuons[indx[1]][j] << "&" << counter_rec_dimuons[indx[1]][j]/(counter_rec_dimuons[indx[1]][j-1]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) <<  (counter_rec_dimuons[indx[1]][j]/(counter_rec_dimuons[indx[1]][j-1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[1]][j]/(double)counter_rec_dimuons[indx[1]][j])*(counter_rec_dimuons_uncert[indx[1]][j]/(double)counter_rec_dimuons[indx[1]][j])) + ((counter_rec_uncert[indx[1]][j-1]/(double)counter_rec_dimuons[indx[1]][j-1])*(counter_rec_uncert[indx[1]][j-1]/(double)counter_rec_dimuons[indx[1]][j-1])))  << "&" << counter_rec_dimuons[indx[2]][j] << "&" << counter_rec_dimuons[indx[2]][j]/(counter_rec_dimuons[indx[2]][j-1]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) <<   (counter_rec_dimuons[indx[2]][j]/(counter_rec_dimuons[indx[2]][j-1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[2]][j]/(double)counter_rec_dimuons[indx[2]][j])*(counter_rec_dimuons_uncert[indx[2]][j]/(double)counter_rec_dimuons[indx[2]][j])) + ((counter_rec_uncert[indx[2]][j-1]/(double)counter_rec_dimuons[indx[2]][j-1])*(counter_rec_uncert[indx[2]][j-1]/(double)counter_rec_dimuons[indx[2]][j-1])))   << "&" << counter_rec_dimuons[indx[3]][j] << "&" << counter_rec_dimuons[indx[3]][j]/(counter_rec_dimuons[indx[3]][j-1]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) <<   (counter_rec_dimuons[indx[3]][j]/(counter_rec_dimuons[indx[3]][j-1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[3]][j]/(double)counter_rec_dimuons[indx[3]][j])*(counter_rec_dimuons_uncert[indx[3]][j]/(double)counter_rec_dimuons[indx[3]][j])) + ((counter_rec_uncert[indx[3]][j-1]/(double)counter_rec_dimuons[indx[3]][j-1])*(counter_rec_uncert[indx[3]][j-1]/(double)counter_rec_dimuons[indx[3]][j-1])))   << "\\\\" << std::endl;
        }
      }
      else if (k ==1 || k ==5) {
        if(j==0)
        {
          out << cutsdim[j].c_str() << "&" << counter_rec_dimuons[indx[0]][j] << "&" << counter_rec_dimuons[indx[0]][j]/(counter_rec[indx[0]][3]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) << (counter_rec_dimuons[indx[0]][j]/(counter_rec[indx[0]][3]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[0]][j]/(double)counter_rec_dimuons[indx[0]][j])*(counter_rec_dimuons_uncert[indx[0]][j]/(double)counter_rec_dimuons[indx[0]][j])) + ((counter_rec_uncert[indx[0]][3]/(double)counter_rec[indx[0]][3])*(counter_rec_uncert[indx[0]][3]/(double)counter_rec[indx[0]][3])))  << "&" << counter_rec_dimuons[indx[1]][j] << "&" << counter_rec_dimuons[indx[1]][j]/(counter_rec[indx[1]][3]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) << (counter_rec_dimuons[indx[1]][j]/(counter_rec[indx[1]][3]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[1]][j]/(double)counter_rec_dimuons[indx[1]][j])*(counter_rec_dimuons_uncert[indx[1]][j]/(double)counter_rec_dimuons[indx[1]][j])) + ((counter_rec_uncert[indx[1]][3]/(double)counter_rec[indx[1]][3])*(counter_rec_uncert[indx[1]][3]/(double)counter_rec[indx[1]][3]))) << "&" << counter_rec_dimuons[indx[2]][j] << "&" << counter_rec_dimuons[indx[2]][j]/(counter_rec[indx[2]][3]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) << (counter_rec_dimuons[indx[2]][j]/(counter_rec[indx[2]][3]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[2]][j]/(double)counter_rec_dimuons[indx[2]][j])*(counter_rec_dimuons_uncert[indx[2]][j]/(double)counter_rec_dimuons[indx[2]][j])) + ((counter_rec_uncert[indx[2]][3]/(double)counter_rec[indx[2]][3])*(counter_rec_uncert[indx[2]][3]/(double)counter_rec[indx[2]][3])))  <<  "\\\\" << std::endl;
        }
        if(j>0)
        {
          out << cutsdim[j].c_str() << "&" << counter_rec_dimuons[indx[0]][j] << "&" << counter_rec_dimuons[indx[0]][j]/(counter_rec_dimuons[indx[0]][j-1]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) <<  (counter_rec_dimuons[indx[0]][j]/(counter_rec_dimuons[indx[0]][j-1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[0]][j]/(double)counter_rec_dimuons[indx[0]][j])*(counter_rec_dimuons_uncert[indx[0]][j]/(double)counter_rec_dimuons[indx[0]][j])) + ((counter_rec_uncert[indx[0]][j-1]/(double)counter_rec_dimuons[indx[0]][j-1])*(counter_rec_uncert[indx[0]][j-1]/(double)counter_rec_dimuons[indx[0]][j-1]))) << "&" << counter_rec_dimuons[indx[1]][j] << "&" << counter_rec_dimuons[indx[1]][j]/(counter_rec_dimuons[indx[1]][j-1]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) <<  (counter_rec_dimuons[indx[1]][j]/(counter_rec_dimuons[indx[1]][j-1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[1]][j]/(double)counter_rec_dimuons[indx[1]][j])*(counter_rec_dimuons_uncert[indx[1]][j]/(double)counter_rec_dimuons[indx[1]][j])) + ((counter_rec_uncert[indx[1]][j-1]/(double)counter_rec_dimuons[indx[1]][j-1])*(counter_rec_uncert[indx[1]][j-1]/(double)counter_rec_dimuons[indx[1]][j-1])))  << "&" << counter_rec_dimuons[indx[2]][j] << "&" << counter_rec_dimuons[indx[2]][j]/(counter_rec_dimuons[indx[2]][j-1]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) <<   (counter_rec_dimuons[indx[2]][j]/(counter_rec_dimuons[indx[2]][j-1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[2]][j]/(double)counter_rec_dimuons[indx[2]][j])*(counter_rec_dimuons_uncert[indx[2]][j]/(double)counter_rec_dimuons[indx[2]][j])) + ((counter_rec_uncert[indx[2]][j-1]/(double)counter_rec_dimuons[indx[2]][j-1])*(counter_rec_uncert[indx[2]][j-1]/(double)counter_rec_dimuons[indx[2]][j-1])))   <<  "\\\\" << std::endl;
        }
      }
    }
  
    for(int j=2;j<7;j++){

      if (k!=1 && k!= 5 && k !=6 && k !=7){        
        
        if(j==2){
          out << cutsdim[j].c_str() << "&" << counter_rec_dimuons[indx[0]][j] << "&" << counter_rec_dimuons[indx[0]][j]/(counter_rec_dimuons[indx[0]][1]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) << (counter_rec_dimuons[indx[0]][j]/(counter_rec_dimuons[indx[0]][1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[0]][j]/(double)counter_rec_dimuons[indx[0]][j])*(counter_rec_dimuons_uncert[indx[0]][j]/(double)counter_rec_dimuons[indx[0]][j])) + ((counter_rec_dimuons_uncert[indx[0]][1]/(double)counter_rec_dimuons[indx[0]][1]*1.0)*(counter_rec_dimuons_uncert[indx[0]][1]/(double)counter_rec_dimuons[indx[0]][1]*1.0))) << "&" << counter_rec_dimuons[indx[1]][j] << "&" << counter_rec_dimuons[indx[1]][j]/(counter_rec_dimuons[indx[1]][1]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) << (counter_rec_dimuons[indx[1]][j]/(counter_rec_dimuons[indx[1]][1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[1]][j]/(double)counter_rec_dimuons[indx[1]][j])*(counter_rec_dimuons_uncert[indx[1]][j]/(double)counter_rec_dimuons[indx[1]][j])) + ((counter_rec_dimuons_uncert[indx[1]][1]/(double)counter_rec_dimuons[indx[1]][1]*1.0)*(counter_rec_dimuons_uncert[indx[1]][1]/(double)counter_rec_dimuons[indx[1]][1]*1.0))) << "&" << counter_rec_dimuons[indx[2]][j] << "&" << counter_rec_dimuons[indx[2]][j]/(counter_rec_dimuons[indx[2]][1]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) << (counter_rec_dimuons[indx[2]][j]/(counter_rec_dimuons[indx[2]][1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[2]][j]/(double)counter_rec_dimuons[indx[2]][j])*(counter_rec_dimuons_uncert[indx[2]][j]/(double)counter_rec_dimuons[indx[2]][j])) + ((counter_rec_dimuons_uncert[indx[2]][1]/(double)counter_rec_dimuons[indx[2]][1]*1.0)*(counter_rec_dimuons_uncert[indx[2]][1]/(double)counter_rec_dimuons[indx[2]][1]*1.0))) << "&" << counter_rec_dimuons[indx[3]][j] << "&" << counter_rec_dimuons[indx[3]][j]/(counter_rec_dimuons[indx[3]][1]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) << (counter_rec_dimuons[indx[3]][j]/(counter_rec_dimuons[indx[3]][1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[3]][j]/(double)counter_rec_dimuons[indx[3]][j])*(counter_rec_dimuons_uncert[indx[3]][j]/(double)counter_rec_dimuons[indx[3]][j])) + ((counter_rec_dimuons_uncert[indx[3]][1]/(double)counter_rec_dimuons[indx[3]][1]*1.0)*(counter_rec_dimuons_uncert[indx[3]][1]/(double)counter_rec_dimuons[indx[3]][1]*1.0))) << "\\\\" << std::endl;
        }
        if(j>2){
          out << cutsdim[j].c_str() << "&" << counter_rec_dimuons[indx[0]][j] << "&" << counter_rec_dimuons[indx[0]][j]/(counter_rec_dimuons[indx[0]][j-1]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) << (counter_rec_dimuons[indx[0]][j]/(counter_rec_dimuons[indx[0]][j-1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[0]][j]/(double)counter_rec_dimuons[indx[0]][j])*(counter_rec_dimuons_uncert[indx[0]][j]/(double)counter_rec_dimuons[indx[0]][j])) + ((counter_rec_dimuons_uncert[indx[0]][j-1]/(double)counter_rec_dimuons[indx[0]][j-1]*1.0)*(counter_rec_dimuons_uncert[indx[0]][j-1]/(double)counter_rec_dimuons[indx[0]][j-1]*1.0))) << "&" << counter_rec_dimuons[indx[1]][j] << "&" << counter_rec_dimuons[indx[1]][j]/(counter_rec_dimuons[indx[1]][j-1]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) << (counter_rec_dimuons[indx[1]][j]/(counter_rec_dimuons[indx[1]][j-1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[1]][j]/(double)counter_rec_dimuons[indx[1]][j])*(counter_rec_dimuons_uncert[indx[1]][j]/(double)counter_rec_dimuons[indx[1]][j])) + ((counter_rec_dimuons_uncert[indx[1]][j-1]/(double)counter_rec_dimuons[indx[1]][j-1]*1.0)*(counter_rec_dimuons_uncert[indx[1]][j-1]/(double)counter_rec_dimuons[indx[1]][j-1]*1.0))) << "&" << counter_rec_dimuons[indx[2]][j] << "&" << counter_rec_dimuons[indx[2]][j]/(counter_rec_dimuons[indx[2]][j-1]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) << (counter_rec_dimuons[indx[2]][j]/(counter_rec_dimuons[indx[2]][j-1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[2]][j]/(double)counter_rec_dimuons[indx[2]][j])*(counter_rec_dimuons_uncert[indx[2]][j]/(double)counter_rec_dimuons[indx[2]][j])) + ((counter_rec_dimuons_uncert[indx[2]][j-1]/(double)counter_rec_dimuons[indx[2]][j-1]*1.0)*(counter_rec_dimuons_uncert[indx[2]][j-1]/(double)counter_rec_dimuons[indx[2]][j-1]*1.0))) << "&" << counter_rec_dimuons[indx[3]][j] << "&" << counter_rec_dimuons[indx[3]][j]/(counter_rec_dimuons[indx[3]][j-1]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) << (counter_rec_dimuons[indx[3]][j]/(counter_rec_dimuons[indx[3]][j-1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[3]][j]/(double)counter_rec_dimuons[indx[3]][j])*(counter_rec_dimuons_uncert[indx[3]][j]/(double)counter_rec_dimuons[indx[3]][j])) + ((counter_rec_dimuons_uncert[indx[3]][j-1]/(double)counter_rec_dimuons[indx[3]][j-1]*1.0)*(counter_rec_dimuons_uncert[indx[3]][j-1]/(double)counter_rec_dimuons[indx[3]][j-1]*1.0))) << "\\\\" << std::endl;
        }
      }

      else if (k ==1 || k ==5) {
        if(j==2){
          out << cutsdim[j].c_str() << "&" << counter_rec_dimuons[indx[0]][j] << "&" << counter_rec_dimuons[indx[0]][j]/(counter_rec_dimuons[indx[0]][1]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) << (counter_rec_dimuons[indx[0]][j]/(counter_rec_dimuons[indx[0]][1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[0]][j]/(double)counter_rec_dimuons[indx[0]][j])*(counter_rec_dimuons_uncert[indx[0]][j]/(double)counter_rec_dimuons[indx[0]][j])) + ((counter_rec_dimuons_uncert[indx[0]][1]/(double)counter_rec_dimuons[indx[0]][1]*1.0)*(counter_rec_dimuons_uncert[indx[0]][1]/(double)counter_rec_dimuons[indx[0]][1]*1.0))) << "&" << counter_rec_dimuons[indx[1]][j] << "&" << counter_rec_dimuons[indx[1]][j]/(counter_rec_dimuons[indx[1]][1]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) << (counter_rec_dimuons[indx[1]][j]/(counter_rec_dimuons[indx[1]][1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[1]][j]/(double)counter_rec_dimuons[indx[1]][j])*(counter_rec_dimuons_uncert[indx[1]][j]/(double)counter_rec_dimuons[indx[1]][j])) + ((counter_rec_dimuons_uncert[indx[1]][1]/(double)counter_rec_dimuons[indx[1]][1]*1.0)*(counter_rec_dimuons_uncert[indx[1]][1]/(double)counter_rec_dimuons[indx[1]][1]*1.0))) << "&" << counter_rec_dimuons[indx[2]][j] << "&" << counter_rec_dimuons[indx[2]][j]/(counter_rec_dimuons[indx[2]][1]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) << (counter_rec_dimuons[indx[2]][j]/(counter_rec_dimuons[indx[2]][1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[2]][j]/(double)counter_rec_dimuons[indx[2]][j])*(counter_rec_dimuons_uncert[indx[2]][j]/(double)counter_rec_dimuons[indx[2]][j])) + ((counter_rec_dimuons_uncert[indx[2]][1]/(double)counter_rec_dimuons[indx[2]][1]*1.0)*(counter_rec_dimuons_uncert[indx[2]][1]/(double)counter_rec_dimuons[indx[2]][1]*1.0))) <<  "\\\\" << std::endl;
        }
        if(j>2){
          out << cutsdim[j].c_str() << "&" << counter_rec_dimuons[indx[0]][j] << "&" << counter_rec_dimuons[indx[0]][j]/(counter_rec_dimuons[indx[0]][j-1]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) << (counter_rec_dimuons[indx[0]][j]/(counter_rec_dimuons[indx[0]][j-1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[0]][j]/(double)counter_rec_dimuons[indx[0]][j])*(counter_rec_dimuons_uncert[indx[0]][j]/(double)counter_rec_dimuons[indx[0]][j])) + ((counter_rec_dimuons_uncert[indx[0]][j-1]/(double)counter_rec_dimuons[indx[0]][j-1]*1.0)*(counter_rec_dimuons_uncert[indx[0]][j-1]/(double)counter_rec_dimuons[indx[0]][j-1]*1.0))) << "&" << counter_rec_dimuons[indx[1]][j] << "&" << counter_rec_dimuons[indx[1]][j]/(counter_rec_dimuons[indx[1]][j-1]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) << (counter_rec_dimuons[indx[1]][j]/(counter_rec_dimuons[indx[1]][j-1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[1]][j]/(double)counter_rec_dimuons[indx[1]][j])*(counter_rec_dimuons_uncert[indx[1]][j]/(double)counter_rec_dimuons[indx[1]][j])) + ((counter_rec_dimuons_uncert[indx[1]][j-1]/(double)counter_rec_dimuons[indx[1]][j-1]*1.0)*(counter_rec_dimuons_uncert[indx[1]][j-1]/(double)counter_rec_dimuons[indx[1]][j-1]*1.0))) << "&" << counter_rec_dimuons[indx[2]][j] << "&" << counter_rec_dimuons[indx[2]][j]/(counter_rec_dimuons[indx[2]][j-1]*1.0) << " $\\pm$ ";
          // out.unsetf(ios_base::fixed);
          out << std::setprecision(2) << (counter_rec_dimuons[indx[2]][j]/(counter_rec_dimuons[indx[2]][j-1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[2]][j]/(double)counter_rec_dimuons[indx[2]][j])*(counter_rec_dimuons_uncert[indx[2]][j]/(double)counter_rec_dimuons[indx[2]][j])) + ((counter_rec_dimuons_uncert[indx[2]][j-1]/(double)counter_rec_dimuons[indx[2]][j-1]*1.0)*(counter_rec_dimuons_uncert[indx[2]][j-1]/(double)counter_rec_dimuons[indx[2]][j-1]*1.0))) << "\\\\" << std::endl;
        }

      }
    }
    out << "\\hline" << std::endl;
    
    if (k!=1 && k!=5){        
      
      out << "$\\alpha_{gen}$ " << " & " << "&" << counter_genlxylz2[indx[0]][4]/(counter_gen[indx[0]][0]*1.0) << " $\\pm$ ";
      out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_genlxylz2[indx[0]][4]/(counter_gen[indx[0]][0]*1.0))*sqrt(((counter_genlxylz2_uncert[indx[0]][4]/(double)counter_genlxylz2[indx[0]][4])*(counter_genlxylz2_uncert[indx[0]][4]/(double)counter_genlxylz2[indx[0]][4])) + ((counter_gen_uncert[indx[0]][0]/(double)counter_gen[indx[0]][0]*1.0)*(counter_gen_uncert[indx[0]][0]/(double)counter_gen[indx[0]][0]*1.0))) << "&" << "&" << counter_genlxylz2[indx[1]][4]/(counter_gen[indx[1]][0]*1.0) << " $\\pm$ ";
      out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_genlxylz2[indx[1]][4]/(counter_gen[indx[1]][0]*1.0))*sqrt(((counter_genlxylz2_uncert[indx[1]][4]/(double)counter_genlxylz2[indx[1]][4])*(counter_genlxylz2_uncert[indx[1]][4]/(double)counter_genlxylz2[indx[1]][4])) + ((counter_gen_uncert[indx[1]][0]/(double)counter_gen[indx[1]][0]*1.0)*(counter_gen_uncert[indx[1]][0]/(double)counter_gen[indx[1]][0]*1.0))) << "&" << "&" << counter_genlxylz2[indx[2]][4]/(counter_gen[indx[2]][0]*1.0) << " $\\pm$ ";
      out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_genlxylz2[indx[2]][4]/(counter_gen[indx[2]][0]*1.0))*sqrt(((counter_genlxylz2_uncert[indx[2]][4]/(double)counter_genlxylz2[indx[2]][4])*(counter_genlxylz2_uncert[indx[2]][4]/(double)counter_genlxylz2[indx[2]][4])) + ((counter_gen_uncert[indx[2]][0]/(double)counter_gen[indx[2]][0]*1.0)*(counter_gen_uncert[indx[2]][0]/(double)counter_gen[indx[2]][0]*1.0))) << "&" << "&" << counter_genlxylz2[indx[3]][4]/(counter_gen[indx[3]][0]*1.0) << " $\\pm$ ";
      out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_genlxylz2[indx[3]][4]/(counter_gen[indx[3]][0]*1.0))*sqrt(((counter_genlxylz2_uncert[indx[3]][4]/(double)counter_genlxylz2[indx[3]][4])*(counter_genlxylz2_uncert[indx[3]][4]/(double)counter_genlxylz2[indx[3]][4])) + ((counter_gen_uncert[indx[3]][0]/(double)counter_gen[indx[3]][0]*1.0)*(counter_gen_uncert[indx[3]][0]/(double)counter_gen[indx[3]][0]*1.0))) << "\\\\" << std::endl;


      out << "$\\epsilon_{full}$ " << " & " << "&" << counter_rec_dimuons[indx[0]][6]/(counter_gen[indx[0]][0]*1.0) << " $\\pm$ ";
      out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_rec_dimuons[indx[0]][6]/(counter_gen[indx[0]][0]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[0]][6]/(double)counter_rec_dimuons[indx[0]][6])*(counter_rec_dimuons_uncert[indx[0]][6]/(double)counter_rec_dimuons[indx[0]][6])) + ((counter_gen_uncert[indx[0]][0]/(double)counter_gen[indx[0]][0]*1.0)*(counter_gen_uncert[indx[0]][0]/(double)counter_gen[indx[0]][0]*1.0))) << "&" << "&" << counter_rec_dimuons[indx[1]][6]/(counter_gen[indx[1]][0]*1.0) << " $\\pm$ ";
      out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_rec_dimuons[indx[1]][6]/(counter_gen[indx[1]][0]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[1]][6]/(double)counter_rec_dimuons[indx[1]][6])*(counter_rec_dimuons_uncert[indx[1]][6]/(double)counter_rec_dimuons[indx[1]][6])) + ((counter_gen_uncert[indx[1]][0]/(double)counter_gen[indx[1]][0]*1.0)*(counter_gen_uncert[indx[1]][0]/(double)counter_gen[indx[1]][0]*1.0))) << "&" << "&" << counter_rec_dimuons[indx[2]][6]/(counter_gen[indx[2]][0]*1.0) << " $\\pm$ ";
      out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_rec_dimuons[indx[2]][6]/(counter_gen[indx[2]][0]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[2]][6]/(double)counter_rec_dimuons[indx[2]][6])*(counter_rec_dimuons_uncert[indx[2]][6]/(double)counter_rec_dimuons[indx[2]][6])) + ((counter_gen_uncert[indx[2]][0]/(double)counter_gen[indx[2]][0]*1.0)*(counter_gen_uncert[indx[2]][0]/(double)counter_gen[indx[2]][0]*1.0))) << "&" << "&" << counter_rec_dimuons[indx[3]][6]/(counter_gen[indx[3]][0]*1.0) << " $\\pm$ ";
      out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_rec_dimuons[indx[3]][6]/(counter_gen[indx[3]][0]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[3]][6]/(double)counter_rec_dimuons[indx[3]][6])*(counter_rec_dimuons_uncert[indx[3]][6]/(double)counter_rec_dimuons[indx[3]][6])) + ((counter_gen_uncert[indx[3]][0]/(double)counter_gen[indx[3]][0]*1.0)*(counter_gen_uncert[indx[3]][0]/(double)counter_gen[indx[3]][0]*1.0))) << "\\\\" << std::endl;

      out << "\\hline" << std::endl;

      out << " $\\epsilon_{full}/\\alpha_{gen}$ " << " & " << "&" << counter_rec_dimuons[indx[0]][6]/(counter_genlxylz2[indx[0]][4]*1.0) << " $\\pm$ ";
      // out.unsetf(ios_base::fixed);
      out << std::fixed << std::setprecision(2) << (counter_rec_dimuons[indx[0]][6]/(counter_genlxylz2[indx[0]][4]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[0]][6]/(double)counter_rec_dimuons[indx[0]][6])*(counter_rec_dimuons_uncert[indx[0]][6]/(double)counter_rec_dimuons[indx[0]][6])) + ((counter_genlxylz2_uncert[indx[0]][4]/(double)counter_genlxylz2[indx[0]][4]*1.0)*(counter_genlxylz2_uncert[indx[0]][4]/(double)counter_genlxylz2[indx[0]][4]*1.0))) << "&" << "&" << counter_rec_dimuons[indx[1]][6]/(counter_genlxylz2[indx[1]][4]*1.0) << " $\\pm$ ";
      // out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_rec_dimuons[indx[1]][6]/(counter_genlxylz2[indx[1]][4]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[1]][6]/(double)counter_rec_dimuons[indx[1]][6])*(counter_rec_dimuons_uncert[indx[1]][6]/(double)counter_rec_dimuons[indx[1]][6])) + ((counter_genlxylz2_uncert[indx[1]][4]/(double)counter_genlxylz2[indx[1]][4]*1.0)*(counter_genlxylz2_uncert[indx[1]][4]/(double)counter_genlxylz2[indx[1]][4]*1.0))) << "&" << "&" << counter_rec_dimuons[indx[2]][6]/(counter_genlxylz2[indx[2]][4]*1.0) << " $\\pm$ ";
      // out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_rec_dimuons[indx[2]][6]/(counter_genlxylz2[indx[2]][4]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[2]][6]/(double)counter_rec_dimuons[indx[2]][6])*(counter_rec_dimuons_uncert[indx[2]][6]/(double)counter_rec_dimuons[indx[2]][6])) + ((counter_genlxylz2_uncert[indx[2]][4]/(double)counter_genlxylz2[indx[2]][4]*1.0)*(counter_genlxylz2_uncert[indx[2]][4]/(double)counter_genlxylz2[indx[2]][4]*1.0))) << "&" << "&" << counter_rec_dimuons[indx[3]][6]/(counter_genlxylz2[indx[3]][4]*1.0) << " $\\pm$ ";
      // out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_rec_dimuons[indx[3]][6]/(counter_genlxylz2[indx[3]][4]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[3]][6]/(double)counter_rec_dimuons[indx[3]][6])*(counter_rec_dimuons_uncert[indx[3]][6]/(double)counter_rec_dimuons[indx[3]][6])) + ((counter_genlxylz2_uncert[indx[3]][4]/(double)counter_genlxylz2[indx[3]][4]*1.0)*(counter_genlxylz2_uncert[indx[3]][4]/(double)counter_genlxylz2[indx[3]][4]*1.0))) << "\\\\" << std::endl;
    }
    else if (k ==1 || k ==5){
      out << "$\\alpha_{gen}$ " << " & " << "&" << counter_genlxylz2[indx[0]][4]/(counter_gen[indx[0]][0]*1.0) << " $\\pm$ ";
      out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_genlxylz2[indx[0]][4]/(counter_gen[indx[0]][0]*1.0))*sqrt(((counter_genlxylz2_uncert[indx[0]][4]/(double)counter_genlxylz2[indx[0]][4])*(counter_genlxylz2_uncert[indx[0]][4]/(double)counter_genlxylz2[indx[0]][4])) + ((counter_gen_uncert[indx[0]][0]/(double)counter_gen[indx[0]][0]*1.0)*(counter_gen_uncert[indx[0]][0]/(double)counter_gen[indx[0]][0]*1.0))) << "&" << "&" << counter_genlxylz2[indx[1]][4]/(counter_gen[indx[1]][0]*1.0) << " $\\pm$ ";
      out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_genlxylz2[indx[1]][4]/(counter_gen[indx[1]][0]*1.0))*sqrt(((counter_genlxylz2_uncert[indx[1]][4]/(double)counter_genlxylz2[indx[1]][4])*(counter_genlxylz2_uncert[indx[1]][4]/(double)counter_genlxylz2[indx[1]][4])) + ((counter_gen_uncert[indx[1]][0]/(double)counter_gen[indx[1]][0]*1.0)*(counter_gen_uncert[indx[1]][0]/(double)counter_gen[indx[1]][0]*1.0))) << "&" << "&" << counter_genlxylz2[indx[2]][4]/(counter_gen[indx[2]][0]*1.0) << " $\\pm$ ";
      out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_genlxylz2[indx[2]][4]/(counter_gen[indx[2]][0]*1.0))*sqrt(((counter_genlxylz2_uncert[indx[2]][4]/(double)counter_genlxylz2[indx[2]][4])*(counter_genlxylz2_uncert[indx[2]][4]/(double)counter_genlxylz2[indx[2]][4])) + ((counter_gen_uncert[indx[2]][0]/(double)counter_gen[indx[2]][0]*1.0)*(counter_gen_uncert[indx[2]][0]/(double)counter_gen[indx[2]][0]*1.0))) <<  "\\\\" << std::endl;


      out << "$\\epsilon_{full}$ " << " & " << "&" << counter_rec_dimuons[indx[0]][6]/(counter_gen[indx[0]][0]*1.0) << " $\\pm$ ";
      out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_rec_dimuons[indx[0]][6]/(counter_gen[indx[0]][0]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[0]][6]/(double)counter_rec_dimuons[indx[0]][6])*(counter_rec_dimuons_uncert[indx[0]][6]/(double)counter_rec_dimuons[indx[0]][6])) + ((counter_gen_uncert[indx[0]][0]/(double)counter_gen[indx[0]][0]*1.0)*(counter_gen_uncert[indx[0]][0]/(double)counter_gen[indx[0]][0]*1.0))) << "&" << "&" << counter_rec_dimuons[indx[1]][6]/(counter_gen[indx[1]][0]*1.0) << " $\\pm$ ";
      out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_rec_dimuons[indx[1]][6]/(counter_gen[indx[1]][0]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[1]][6]/(double)counter_rec_dimuons[indx[1]][6])*(counter_rec_dimuons_uncert[indx[1]][6]/(double)counter_rec_dimuons[indx[1]][6])) + ((counter_gen_uncert[indx[1]][0]/(double)counter_gen[indx[1]][0]*1.0)*(counter_gen_uncert[indx[1]][0]/(double)counter_gen[indx[1]][0]*1.0))) << "&" << "&" << counter_rec_dimuons[indx[2]][6]/(counter_gen[indx[2]][0]*1.0) << " $\\pm$ ";
      out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_rec_dimuons[indx[2]][6]/(counter_gen[indx[2]][0]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[2]][6]/(double)counter_rec_dimuons[indx[2]][6])*(counter_rec_dimuons_uncert[indx[2]][6]/(double)counter_rec_dimuons[indx[2]][6])) + ((counter_gen_uncert[indx[2]][0]/(double)counter_gen[indx[2]][0]*1.0)*(counter_gen_uncert[indx[2]][0]/(double)counter_gen[indx[2]][0]*1.0))) <<  "\\\\" << std::endl;

      out << "\\hline" << std::endl;

      out << " $\\epsilon_{full}/\\alpha_{gen}$ " << " & " << "&" << counter_rec_dimuons[indx[0]][6]/(counter_genlxylz2[indx[0]][4]*1.0) << " $\\pm$ ";
      // out.unsetf(ios_base::fixed);
      out << std::fixed << std::setprecision(2) << (counter_rec_dimuons[indx[0]][6]/(counter_genlxylz2[indx[0]][4]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[0]][6]/(double)counter_rec_dimuons[indx[0]][6])*(counter_rec_dimuons_uncert[indx[0]][6]/(double)counter_rec_dimuons[indx[0]][6])) + ((counter_genlxylz2_uncert[indx[0]][4]/(double)counter_genlxylz2[indx[0]][4]*1.0)*(counter_genlxylz2_uncert[indx[0]][4]/(double)counter_genlxylz2[indx[0]][4]*1.0))) << "&" << "&" << counter_rec_dimuons[indx[1]][6]/(counter_genlxylz2[indx[1]][4]*1.0) << " $\\pm$ ";
      // out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_rec_dimuons[indx[1]][6]/(counter_genlxylz2[indx[1]][4]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[1]][6]/(double)counter_rec_dimuons[indx[1]][6])*(counter_rec_dimuons_uncert[indx[1]][6]/(double)counter_rec_dimuons[indx[1]][6])) + ((counter_genlxylz2_uncert[indx[1]][4]/(double)counter_genlxylz2[indx[1]][4]*1.0)*(counter_genlxylz2_uncert[indx[1]][4]/(double)counter_genlxylz2[indx[1]][4]*1.0))) << "&" << "&" << counter_rec_dimuons[indx[2]][6]/(counter_genlxylz2[indx[2]][4]*1.0) << " $\\pm$ ";
      // out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_rec_dimuons[indx[2]][6]/(counter_genlxylz2[indx[2]][4]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[2]][6]/(double)counter_rec_dimuons[indx[2]][6])*(counter_rec_dimuons_uncert[indx[2]][6]/(double)counter_rec_dimuons[indx[2]][6])) + ((counter_genlxylz2_uncert[indx[2]][4]/(double)counter_genlxylz2[indx[2]][4]*1.0)*(counter_genlxylz2_uncert[indx[2]][4]/(double)counter_genlxylz2[indx[2]][4]*1.0))) <<  "\\\\" << std::endl;

      
    }


    std::cout << out.str() << std::endl;
     
     
     
    cout<<"  \\hline  "<<endl;
    cout<<"\\end{tabular} "<<endl;
    cout<<"\\end{table} "<<endl;
    std::cout<<"\\end{landscape} "<<endl;
  }



  for(int k=0;k<2;k++){
    out.str("");
    out.clear();
    std::cout << "\\begin{landscape}" << std::endl;
    cout<<" \\begin{table}[ht]         "<<endl;
    std::cout << "\\renewcommand{\\tabcolsep}{0pt}" << std::endl;
    
    cout << "\\caption{Acceptances and efficiencies (all in \\%) of the event selection requirements for the samples with $m_{h_{1}} = 125$~GeV$/c^{2}$, and several representative benchmark values of $m_{a_1}$ in the MC simulation of NMSSM signal. \\label{tab:eff_NMSSM_mh125}}" << std::endl;
    
    cout<<" \\centering               "<<endl;
 
    if (k==0){
      cout<<" \\begin{tabular}{|l|c|c|c|c|c|c|c|c|c|c|c|c|} \\hline  "<<endl;
      out << "$m_{h_1}=125$~GeV$/c^{2}$ & \\multicolumn{2}{c|}{$m_{a_1}=0.25$} & \\multicolumn{2}{c|}{$m_{a_1}=0.5$} & \\multicolumn{2}{c|}{$m_{a_1}=0.75$} & \\multicolumn{2}{c|}{$m_{a_1}=1.0$} & \\multicolumn{2}{c|}{$m_{a_1}=2.0$} & \\multicolumn{2}{c|}{$m_{a_1}=3.55$} \\\\ \\hline"<<endl;
      out << "  Selection  " << "&" << "  $N_{evts}$  " << "&" << "  Rel. Eff(\\%)  " << "&"  << "  $N_{evts}$  " << "&" << "  Rel. Eff(\\%)  "  << "&" << "  $N_{evts}$  " << "&" << "  Rel. Eff(\\%)  "  << "&" << "$N_{evts}$" << "&" << "Rel. Eff(\\%)" << "&" << "$N_{evts}$" << "&" << "Rel. Eff(\\%)" << "&" << "$N_{evts}$" << "&" << "Rel. Eff(\\%)" <<  "\\\\";
    }

    if (k==1){
      cout<<" \\begin{tabular}{|l|c|c|c|c|c|c|c|c|c|c|} \\hline  "<<endl;
      out << "$m_{a_1}=2.0$~GeV$/c^{2}$ & \\multicolumn{2}{c|}{$m_{h_1}=90$} & \\multicolumn{2}{c|}{$m_{h_1}=100$} & \\multicolumn{2}{c|}{$m_{h_1}=110$} & \\multicolumn{2}{c|}{$m_{h_1}=125$} & \\multicolumn{2}{c|}{$m_{h_1}=150$} \\\\ \\hline"<<endl;
      out << "  Selection  " << "&" << "  $N_{evts}$  " << "&" << "  Rel. Eff(\\%)  " << "&"  << "  $N_{evts}$  " << "&" << "  Rel. Eff(\\%)  "  << "&" << "  $N_{evts}$  " << "&" << "  Rel. Eff(\\%)  "  << "&" << "$N_{evts}$" << "&" << "Rel. Eff(\\%)" << "&" << "$N_{evts}$" << "&" << "Rel. Eff(\\%)" <<  "\\\\";
    }

    out <<" \\hline  "<<endl;
    
    if(k==0){ indx[0]=52;indx[1]=53;indx[2]=54;indx[3]=55;indx[4]=56;indx[5]=57;} // mh=125 GeV
    if(k==1){ indx[0]=48;indx[1]=50;indx[2]=51;indx[3]=56;indx[4]=59;} // ma=2.0 GeV

    // f[48] = new TFile("MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_5312_GEN_v1.root");
    // f[49] = new TFile("MSSM_mH_100_mA_0250_Hto2Ato4mu_8TeV-pythia6_5312_GEN_v1.root");
    // f[50] = new TFile("MSSM_mH_100_mA_2000_Hto2Ato4mu_8TeV-pythia6_5312_GEN_v1.root");
    // f[51] = new TFile("MSSM_mH_110_mA_2000_Hto2Ato4mu_8TeV-pythia6_5312_GEN_v1.root");

    // f[52] = new TFile("MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_5312_GEN_v1.root");
    // f[53] = new TFile("MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_5312_GEN_v1.root");
    // f[54] = new TFile("MSSM_mH_125_mA_0750_Hto2Ato4mu_8TeV-pythia6_5312_GEN_v1.root");
    // f[55] = new TFile("MSSM_mH_125_mA_1000_Hto2Ato4mu_8TeV-pythia6_5312_GEN_v1.root");
    // f[56] = new TFile("MSSM_mH_125_mA_2000_Hto2Ato4mu_8TeV-pythia6_5312_GEN_v1.root");
    // f[57] = new TFile("MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_5312_GEN_v1.root");

    // f[58] = new TFile("MSSM_mH_150_mA_0250_Hto2Ato4mu_8TeV-pythia6_5312_GEN_v1.root");
    // f[59] = new TFile("MSSM_mH_150_mA_2000_Hto2Ato4mu_8TeV-pythia6_5312_GEN_v1.root");



    if (k==0){
      out <<  cutsgen[0].c_str() << "&" << std::setprecision(2) << counter_gen[indx[0]][0] << "&" << "&" << counter_gen[indx[1]][0] << "&"  << "&" << counter_gen[indx[2]][0] << "&"  << "&" << counter_gen[indx[3]][0] <<  "&" << "&" << counter_gen[indx[4]][0] <<  "&" << "&" << counter_gen[indx[5]][0] <<  "&" << "\\\\ \\hline" << std::endl;
    }

    if (k==1){
      out <<  cutsgen[0].c_str() << "&" << std::setprecision(2) << counter_gen[indx[0]][0] << "&" << "&" << counter_gen[indx[1]][0] << "&"  << "&" << counter_gen[indx[2]][0] << "&"  << "&" << counter_gen[indx[3]][0] <<  "&" << "&" << counter_gen[indx[4]][0] << "& \\\\ \\hline" << std::endl;
    }

    out << "\\multicolumn{2}{|c}{\\textbf{Basic event selections (gen):}} \\\\ \\hline" << std::endl;


    for(int j=1;j<5;j++){
      if (k==0){        
        out << cutsgen[j].c_str() << "&" << std::fixed << counter_gen[indx[0]][j] << "&" << counter_gen[indx[0]][j]/(counter_gen[indx[0]][j-1]*1.0) << " $\\pm$ ";
        out << std::setprecision(2) << (counter_gen[indx[0]][j]/(counter_gen[indx[0]][j-1]*1.0))*sqrt(((counter_gen_uncert[indx[0]][j]/(double)counter_gen[indx[0]][j])*(counter_gen_uncert[indx[0]][j]/(double)counter_gen[indx[0]][j])) + ((counter_gen_uncert[indx[0]][j-1]/(double)counter_gen[indx[0]][j-1])*(counter_gen_uncert[indx[0]][j-1]/(double)counter_gen[indx[0]][j-1])))  << "&" << std::fixed << counter_gen[indx[1]][j] << "&" << counter_gen[indx[1]][j]/(counter_gen[indx[1]][j-1]*1.0) << " $\\pm$ ";
        out <<  std::setprecision(2) << (counter_gen[indx[1]][j]/(counter_gen[indx[1]][j-1]*1.0))*sqrt(((counter_gen_uncert[indx[1]][j]/(double)counter_gen[indx[1]][j])*(counter_gen_uncert[indx[1]][j]/(double)counter_gen[indx[1]][j])) + ((counter_gen_uncert[indx[1]][j-1]/(double)counter_gen[indx[1]][j-1])*(counter_gen_uncert[indx[1]][j-1]/(double)counter_gen[indx[1]][j-1])))   << "&" << std::fixed << counter_gen[indx[2]][j] << "&" << counter_gen[indx[2]][j]/(counter_gen[indx[2]][j-1]*1.0) << " $\\pm$ ";
        out <<  std::setprecision(2) <<   (counter_gen[indx[2]][j]/(counter_gen[indx[2]][j-1]*1.0))*sqrt(((counter_gen_uncert[indx[2]][j]/(double)counter_gen[indx[2]][j])*(counter_gen_uncert[indx[2]][j]/(double)counter_gen[indx[2]][j])) + ((counter_gen_uncert[indx[2]][j-1]/(double)counter_gen[indx[2]][j-1])*(counter_gen_uncert[indx[2]][j-1]/(double)counter_gen[indx[2]][j-1])))  << "&" << std::fixed << counter_gen[indx[3]][j] << "&" << counter_gen[indx[3]][j]/(counter_gen[indx[3]][j-1]*1.0) << " $\\pm$ ";

        out <<  std::setprecision(2) <<   (counter_gen[indx[3]][j]/(counter_gen[indx[3]][j-1]*1.0))*sqrt(((counter_gen_uncert[indx[3]][j]/(double)counter_gen[indx[3]][j])*(counter_gen_uncert[indx[3]][j]/(double)counter_gen[indx[3]][j])) + ((counter_gen_uncert[indx[3]][j-1]/(double)counter_gen[indx[3]][j-1])*(counter_gen_uncert[indx[3]][j-1]/(double)counter_gen[indx[3]][j-1])))  << "&" << std::fixed << counter_gen[indx[4]][j] << "&" << counter_gen[indx[4]][j]/(counter_gen[indx[3]][j-1]*1.0) << " $\\pm$ ";

        out <<  std::setprecision(2) <<   (counter_gen[indx[4]][j]/(counter_gen[indx[4]][j-1]*1.0))*sqrt(((counter_gen_uncert[indx[4]][j]/(double)counter_gen[indx[4]][j])*(counter_gen_uncert[indx[4]][j]/(double)counter_gen[indx[4]][j])) + ((counter_gen_uncert[indx[4]][j-1]/(double)counter_gen[indx[4]][j-1])*(counter_gen_uncert[indx[4]][j-1]/(double)counter_gen[indx[4]][j-1])))  << "&" << std::fixed << counter_gen[indx[5]][j] << "&" << counter_gen[indx[5]][j]/(counter_gen[indx[3]][j-1]*1.0) << " $\\pm$ ";

        out <<  std::setprecision(2) << (counter_gen[indx[5]][j]/(counter_gen[indx[5]][j-1]*1.0))*sqrt(((counter_gen_uncert[indx[5]][j]/(double)counter_gen[indx[5]][j])*(counter_gen_uncert[indx[5]][j]/(double)counter_gen[indx[5]][j])) + ((counter_gen_uncert[indx[5]][j-1]/(double)counter_gen[indx[5]][j-1])*(counter_gen_uncert[indx[5]][j-1]/(double)counter_gen[indx[5]][j-1])))   << "\\\\" << std::endl;
      }
      if (k==1)
      {        
        out << cutsgen[j].c_str() << "&" << std::fixed << counter_gen[indx[0]][j] << "&" << counter_gen[indx[0]][j]/(counter_gen[indx[0]][j-1]*1.0) << " $\\pm$ ";
        out << std::setprecision(2) << (counter_gen[indx[0]][j]/(counter_gen[indx[0]][j-1]*1.0))*sqrt(((counter_gen_uncert[indx[0]][j]/(double)counter_gen[indx[0]][j])*(counter_gen_uncert[indx[0]][j]/(double)counter_gen[indx[0]][j])) + ((counter_gen_uncert[indx[0]][j-1]/(double)counter_gen[indx[0]][j-1])*(counter_gen_uncert[indx[0]][j-1]/(double)counter_gen[indx[0]][j-1])))  << "&" << std::fixed << counter_gen[indx[1]][j] << "&" << counter_gen[indx[1]][j]/(counter_gen[indx[1]][j-1]*1.0) << " $\\pm$ ";
        out <<  std::setprecision(2) << (counter_gen[indx[1]][j]/(counter_gen[indx[1]][j-1]*1.0))*sqrt(((counter_gen_uncert[indx[1]][j]/(double)counter_gen[indx[1]][j])*(counter_gen_uncert[indx[1]][j]/(double)counter_gen[indx[1]][j])) + ((counter_gen_uncert[indx[1]][j-1]/(double)counter_gen[indx[1]][j-1])*(counter_gen_uncert[indx[1]][j-1]/(double)counter_gen[indx[1]][j-1])))   << "&" << std::fixed << counter_gen[indx[2]][j] << "&" << counter_gen[indx[2]][j]/(counter_gen[indx[2]][j-1]*1.0) << " $\\pm$ ";
        out <<  std::setprecision(2) <<   (counter_gen[indx[2]][j]/(counter_gen[indx[2]][j-1]*1.0))*sqrt(((counter_gen_uncert[indx[2]][j]/(double)counter_gen[indx[2]][j])*(counter_gen_uncert[indx[2]][j]/(double)counter_gen[indx[2]][j])) + ((counter_gen_uncert[indx[2]][j-1]/(double)counter_gen[indx[2]][j-1])*(counter_gen_uncert[indx[2]][j-1]/(double)counter_gen[indx[2]][j-1])))  << "&" << std::fixed << counter_gen[indx[3]][j] << "&" << counter_gen[indx[3]][j]/(counter_gen[indx[3]][j-1]*1.0) << " $\\pm$ ";

        out <<  std::setprecision(2) <<   (counter_gen[indx[3]][j]/(counter_gen[indx[3]][j-1]*1.0))*sqrt(((counter_gen_uncert[indx[3]][j]/(double)counter_gen[indx[3]][j])*(counter_gen_uncert[indx[3]][j]/(double)counter_gen[indx[3]][j])) + ((counter_gen_uncert[indx[3]][j-1]/(double)counter_gen[indx[3]][j-1])*(counter_gen_uncert[indx[3]][j-1]/(double)counter_gen[indx[3]][j-1])))  << "&" << std::fixed << counter_gen[indx[4]][j] << "&" << counter_gen[indx[4]][j]/(counter_gen[indx[4]][j-1]*1.0) << " $\\pm$ ";

        out <<  std::setprecision(2) << (counter_gen[indx[4]][j]/(counter_gen[indx[4]][j-1]*1.0))*sqrt(((counter_gen_uncert[indx[4]][j]/(double)counter_gen[indx[4]][j])*(counter_gen_uncert[indx[4]][j]/(double)counter_gen[indx[4]][j])) + ((counter_gen_uncert[indx[4]][j-1]/(double)counter_gen[indx[4]][j-1])*(counter_gen_uncert[indx[4]][j-1]/(double)counter_gen[indx[4]][j-1])))   << "\\\\" << std::endl;
      }

    }

    if (k==0){        
      out << "$L_{xy} < 4.4$ cm, $L_z < 34.5$ cm" << "&" << counter_genlxylz2[indx[0]][4] << "&" << counter_genlxylz2[indx[0]][4]/(counter_gen[indx[0]][4]*1.0) << " $\\pm$ ";
      out << std::setprecision(2) <<  (counter_genlxylz2[indx[0]][4]/(counter_gen[indx[0]][4]*1.0))*sqrt(((counter_genlxylz2_uncert[indx[0]][4]/(double)counter_genlxylz2[indx[0]][4])*(counter_genlxylz2_uncert[indx[0]][4]/(double)counter_genlxylz2[indx[0]][4])) + ((counter_gen_uncert[indx[0]][4]/(double)counter_gen[indx[0]][4])*(counter_gen_uncert[indx[0]][4]/(double)counter_gen[indx[0]][4])))  << "&" << counter_genlxylz2[indx[1]][4] << "&" << counter_genlxylz2[indx[1]][4]/(counter_gen[indx[1]][4]*1.0) << " $\\pm$ ";
      out << std::setprecision(2) << (counter_genlxylz2[indx[1]][4]/(counter_gen[indx[1]][4]*1.0))*sqrt(((counter_genlxylz2_uncert[indx[1]][4]/(double)counter_genlxylz2[indx[1]][4])*(counter_genlxylz2_uncert[indx[1]][4]/(double)counter_genlxylz2[indx[1]][4])) + ((counter_gen_uncert[indx[1]][4]/(double)counter_gen[indx[1]][4])*(counter_gen_uncert[indx[1]][4]/(double)counter_gen[indx[1]][4]))) << "&" << counter_genlxylz2[indx[2]][4] << "&" << counter_genlxylz2[indx[2]][4]/(counter_gen[indx[2]][4]*1.0) << " $\\pm$ ";
      out << std::setprecision(2) << (counter_genlxylz2[indx[2]][4]/(counter_gen[indx[2]][4]*1.0))*sqrt(((counter_genlxylz2_uncert[indx[2]][4]/(double)counter_genlxylz2[indx[2]][4])*(counter_genlxylz2_uncert[indx[2]][4]/(double)counter_genlxylz2[indx[2]][4])) + ((counter_gen_uncert[indx[2]][4]/(double)counter_gen[indx[2]][4])*(counter_gen_uncert[indx[2]][4]/(double)counter_gen[indx[2]][4])))   << "&" << counter_genlxylz2[indx[3]][4] << "&" << counter_genlxylz2[indx[3]][4]/(counter_gen[indx[3]][4]*1.0) << " $\\pm$ ";
      out << std::setprecision(2) << (counter_genlxylz2[indx[3]][4]/(counter_gen[indx[3]][4]*1.0))*sqrt(((counter_genlxylz2_uncert[indx[3]][4]/(double)counter_genlxylz2[indx[3]][4])*(counter_genlxylz2_uncert[indx[3]][4]/(double)counter_genlxylz2[indx[3]][4])) + ((counter_gen_uncert[indx[3]][4]/(double)counter_gen[indx[3]][4])*(counter_gen_uncert[indx[3]][4]/(double)counter_gen[indx[3]][4])))   << "&" << counter_genlxylz2[indx[3]][4] << "&" << counter_genlxylz2[indx[4]][4]/(counter_gen[indx[4]][4]*1.0) << " $\\pm$ ";
      out << std::setprecision(2) << (counter_genlxylz2[indx[4]][4]/(counter_gen[indx[4]][4]*1.0))*sqrt(((counter_genlxylz2_uncert[indx[4]][4]/(double)counter_genlxylz2[indx[4]][4])*(counter_genlxylz2_uncert[indx[4]][4]/(double)counter_genlxylz2[indx[4]][4])) + ((counter_gen_uncert[indx[4]][4]/(double)counter_gen[indx[4]][4])*(counter_gen_uncert[indx[4]][4]/(double)counter_gen[indx[4]][4])))   << "&" << counter_genlxylz2[indx[4]][4] << "&" << counter_genlxylz2[indx[5]][4]/(counter_gen[indx[5]][4]*1.0) << " $\\pm$ ";

      out << std::setprecision(2) << (counter_genlxylz2[indx[5]][4]/(counter_gen[indx[5]][4]*1.0))*sqrt(((counter_genlxylz2_uncert[indx[5]][4]/(double)counter_genlxylz2[indx[5]][4])*(counter_genlxylz2_uncert[indx[5]][4]/(double)counter_genlxylz2[indx[5]][4])) + ((counter_gen_uncert[indx[5]][4]/(double)counter_gen[indx[5]][4])*(counter_gen_uncert[indx[5]][4]/(double)counter_gen[indx[5]][4])))   << "\\\\ \\hline" << std::endl;
    }


    if (k==1){        
      out << "$L_{xy} < 4.4$ cm, $L_z < 34.5$ cm" << "&" << counter_genlxylz2[indx[0]][4] << "&" << counter_genlxylz2[indx[0]][4]/(counter_gen[indx[0]][4]*1.0) << " $\\pm$ ";
      out << std::setprecision(2) <<  (counter_genlxylz2[indx[0]][4]/(counter_gen[indx[0]][4]*1.0))*sqrt(((counter_genlxylz2_uncert[indx[0]][4]/(double)counter_genlxylz2[indx[0]][4])*(counter_genlxylz2_uncert[indx[0]][4]/(double)counter_genlxylz2[indx[0]][4])) + ((counter_gen_uncert[indx[0]][4]/(double)counter_gen[indx[0]][4])*(counter_gen_uncert[indx[0]][4]/(double)counter_gen[indx[0]][4])))  << "&" << counter_genlxylz2[indx[1]][4] << "&" << counter_genlxylz2[indx[1]][4]/(counter_gen[indx[1]][4]*1.0) << " $\\pm$ ";
      out << std::setprecision(2) << (counter_genlxylz2[indx[1]][4]/(counter_gen[indx[1]][4]*1.0))*sqrt(((counter_genlxylz2_uncert[indx[1]][4]/(double)counter_genlxylz2[indx[1]][4])*(counter_genlxylz2_uncert[indx[1]][4]/(double)counter_genlxylz2[indx[1]][4])) + ((counter_gen_uncert[indx[1]][4]/(double)counter_gen[indx[1]][4])*(counter_gen_uncert[indx[1]][4]/(double)counter_gen[indx[1]][4]))) << "&" << counter_genlxylz2[indx[2]][4] << "&" << counter_genlxylz2[indx[2]][4]/(counter_gen[indx[2]][4]*1.0) << " $\\pm$ ";
      out << std::setprecision(2) << (counter_genlxylz2[indx[2]][4]/(counter_gen[indx[2]][4]*1.0))*sqrt(((counter_genlxylz2_uncert[indx[2]][4]/(double)counter_genlxylz2[indx[2]][4])*(counter_genlxylz2_uncert[indx[2]][4]/(double)counter_genlxylz2[indx[2]][4])) + ((counter_gen_uncert[indx[2]][4]/(double)counter_gen[indx[2]][4])*(counter_gen_uncert[indx[2]][4]/(double)counter_gen[indx[2]][4])))   << "&" << counter_genlxylz2[indx[3]][4] << "&" << counter_genlxylz2[indx[3]][4]/(counter_gen[indx[3]][4]*1.0) << " $\\pm$ ";
      out << std::setprecision(2) << (counter_genlxylz2[indx[3]][4]/(counter_gen[indx[3]][4]*1.0))*sqrt(((counter_genlxylz2_uncert[indx[3]][4]/(double)counter_genlxylz2[indx[3]][4])*(counter_genlxylz2_uncert[indx[3]][4]/(double)counter_genlxylz2[indx[3]][4])) + ((counter_gen_uncert[indx[3]][4]/(double)counter_gen[indx[3]][4])*(counter_gen_uncert[indx[3]][4]/(double)counter_gen[indx[3]][4])))   << "&" << counter_genlxylz2[indx[3]][4] << "&" << counter_genlxylz2[indx[4]][4]/(counter_gen[indx[4]][4]*1.0) << " $\\pm$ ";
      out << std::setprecision(2) << (counter_genlxylz2[indx[4]][4]/(counter_gen[indx[4]][4]*1.0))*sqrt(((counter_genlxylz2_uncert[indx[4]][4]/(double)counter_genlxylz2[indx[4]][4])*(counter_genlxylz2_uncert[indx[4]][4]/(double)counter_genlxylz2[indx[4]][4])) + ((counter_gen_uncert[indx[4]][4]/(double)counter_gen[indx[4]][4])*(counter_gen_uncert[indx[4]][4]/(double)counter_gen[indx[4]][4])))   << "\\\\ \\hline" << std::endl;
    }

    out << "\\multicolumn{2}{|c}{\\textbf{Basic event selections (reco):}} \\\\ \\hline" << std::endl;

    for(int j=0;j<4;j++){

      if (k==0){        
        if(j==0){
          out << cutsrec[j].c_str() << "&" << counter_rec[indx[0]][j] << "&" << counter_rec[indx[0]][j]/(counter_gen[indx[0]][j]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec[indx[0]][j]/(counter_gen[indx[0]][j]*1.0))*sqrt(((counter_rec_uncert[indx[0]][j]/(double)counter_rec[indx[0]][j])*(counter_rec_uncert[indx[0]][j]/(double)counter_rec[indx[0]][j])) + ((counter_gen_uncert[indx[0]][j]/(double)counter_gen[indx[0]][j])*(counter_gen_uncert[indx[0]][j]/(double)counter_gen[indx[0]][j])))  << "&" << counter_rec[indx[1]][j] << "&" << counter_rec[indx[1]][j]/(counter_gen[indx[1]][j]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec[indx[1]][j]/(counter_gen[indx[1]][j]*1.0))*sqrt(((counter_rec_uncert[indx[1]][j]/(double)counter_rec[indx[1]][j])*(counter_rec_uncert[indx[1]][j]/(double)counter_rec[indx[1]][j])) + ((counter_gen_uncert[indx[1]][j]/(double)counter_gen[indx[1]][j])*(counter_gen_uncert[indx[1]][j]/(double)counter_gen[indx[1]][j]))) << "&" << counter_rec[indx[2]][j] << "&" << counter_rec[indx[2]][j]/(counter_gen[indx[2]][j]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec[indx[2]][j]/(counter_gen[indx[2]][j]*1.0))*sqrt(((counter_rec_uncert[indx[2]][j]/(double)counter_rec[indx[2]][j])*(counter_rec_uncert[indx[2]][j]/(double)counter_rec[indx[2]][j])) + ((counter_gen_uncert[indx[2]][j]/(double)counter_gen[indx[2]][j])*(counter_gen_uncert[indx[2]][j]/(double)counter_gen[indx[2]][j]))) << "&" << counter_rec[indx[3]][j] << "&" << counter_rec[indx[3]][j]/(counter_gen[indx[3]][j]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec[indx[3]][j]/(counter_gen[indx[3]][j]*1.0))*sqrt(((counter_rec_uncert[indx[3]][j]/(double)counter_rec[indx[3]][j])*(counter_rec_uncert[indx[3]][j]/(double)counter_rec[indx[3]][j])) + ((counter_gen_uncert[indx[3]][j]/(double)counter_gen[indx[3]][j])*(counter_gen_uncert[indx[3]][j]/(double)counter_gen[indx[3]][j]))) << "&" << counter_rec[indx[3]][j] << "&" << counter_rec[indx[4]][j]/(counter_gen[indx[4]][j]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec[indx[4]][j]/(counter_gen[indx[4]][j]*1.0))*sqrt(((counter_rec_uncert[indx[4]][j]/(double)counter_rec[indx[4]][j])*(counter_rec_uncert[indx[4]][j]/(double)counter_rec[indx[4]][j])) + ((counter_gen_uncert[indx[4]][j]/(double)counter_gen[indx[4]][j])*(counter_gen_uncert[indx[4]][j]/(double)counter_gen[indx[4]][j]))) << "&" << counter_rec[indx[4]][j] << "&" << counter_rec[indx[5]][j]/(counter_gen[indx[5]][j]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec[indx[5]][j]/(counter_gen[indx[5]][j]*1.0))*sqrt(((counter_rec_uncert[indx[5]][j]/(double)counter_rec[indx[5]][j])*(counter_rec_uncert[indx[5]][j]/(double)counter_rec[indx[5]][j])) + ((counter_gen_uncert[indx[5]][j]/(double)counter_gen[indx[5]][j])*(counter_gen_uncert[indx[5]][j]/(double)counter_gen[indx[5]][j])))  << "\\\\" << std::endl;
        }
        if(j>0){
          out << cutsrec[j].c_str() << "&" << counter_rec[indx[0]][j] << "&" << counter_rec[indx[0]][j]/(counter_rec[indx[0]][j-1]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec[indx[0]][j]/(counter_rec[indx[0]][j-1]*1.0))*sqrt(((counter_rec_uncert[indx[0]][j]/(double)counter_rec[indx[0]][j])*(counter_rec_uncert[indx[0]][j]/(double)counter_rec[indx[0]][j])) + ((counter_rec_uncert[indx[0]][j-1]/(double)counter_rec[indx[0]][j-1])*(counter_rec_uncert[indx[0]][j-1]/(double)counter_rec[indx[0]][j-1])))  << "&" << counter_rec[indx[1]][j] << "&" << counter_rec[indx[1]][j]/(counter_rec[indx[1]][j-1]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec[indx[1]][j]/(counter_rec[indx[1]][j-1]*1.0))*sqrt(((counter_rec_uncert[indx[1]][j]/(double)counter_rec[indx[1]][j])*(counter_rec_uncert[indx[1]][j]/(double)counter_rec[indx[1]][j])) + ((counter_rec_uncert[indx[1]][j-1]/(double)counter_rec[indx[1]][j-1])*(counter_rec_uncert[indx[1]][j-1]/(double)counter_rec[indx[1]][j-1])))  << "&" << counter_rec[indx[2]][j] << "&" << counter_rec[indx[2]][j]/(counter_rec[indx[2]][j-1]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec[indx[2]][j]/(counter_rec[indx[2]][j-1]*1.0))*sqrt(((counter_rec_uncert[indx[2]][j]/(double)counter_rec[indx[2]][j])*(counter_rec_uncert[indx[2]][j]/(double)counter_rec[indx[2]][j])) + ((counter_rec_uncert[indx[2]][j-1]/(double)counter_rec[indx[2]][j-1])*(counter_rec_uncert[indx[2]][j-1]/(double)counter_rec[indx[2]][j-1])))  << "&" << counter_rec[indx[3]][j] << "&" << counter_rec[indx[3]][j]/(counter_rec[indx[3]][j-1]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec[indx[3]][j]/(counter_rec[indx[3]][j-1]*1.0))*sqrt(((counter_rec_uncert[indx[3]][j]/(double)counter_rec[indx[3]][j])*(counter_rec_uncert[indx[3]][j]/(double)counter_rec[indx[3]][j])) + ((counter_rec_uncert[indx[3]][j-1]/(double)counter_rec[indx[3]][j-1])*(counter_rec_uncert[indx[3]][j-1]/(double)counter_rec[indx[3]][j-1])))  << "&" << counter_rec[indx[4]][j] << "&" << counter_rec[indx[4]][j]/(counter_rec[indx[4]][j-1]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec[indx[4]][j]/(counter_rec[indx[4]][j-1]*1.0))*sqrt(((counter_rec_uncert[indx[4]][j]/(double)counter_rec[indx[4]][j])*(counter_rec_uncert[indx[4]][j]/(double)counter_rec[indx[4]][j])) + ((counter_rec_uncert[indx[4]][j-1]/(double)counter_rec[indx[4]][j-1])*(counter_rec_uncert[indx[4]][j-1]/(double)counter_rec[indx[4]][j-1])))  << "&" << counter_rec[indx[4]][j] << "&" << counter_rec[indx[5]][j]/(counter_rec[indx[5]][j-1]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec[indx[5]][j]/(counter_rec[indx[5]][j-1]*1.0))*sqrt(((counter_rec_uncert[indx[5]][j]/(double)counter_rec[indx[5]][j])*(counter_rec_uncert[indx[5]][j]/(double)counter_rec[indx[5]][j])) + ((counter_rec_uncert[indx[5]][j-1]/(double)counter_rec[indx[5]][j-1])*(counter_rec_uncert[indx[5]][j-1]/(double)counter_rec[indx[5]][j-1])))  << "\\\\ " << std::endl;
        }
      }

      if (k==1){        
        if(j==0){
          out << cutsrec[j].c_str() << "&" << counter_rec[indx[0]][j] << "&" << counter_rec[indx[0]][j]/(counter_gen[indx[0]][j]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec[indx[0]][j]/(counter_gen[indx[0]][j]*1.0))*sqrt(((counter_rec_uncert[indx[0]][j]/(double)counter_rec[indx[0]][j])*(counter_rec_uncert[indx[0]][j]/(double)counter_rec[indx[0]][j])) + ((counter_gen_uncert[indx[0]][j]/(double)counter_gen[indx[0]][j])*(counter_gen_uncert[indx[0]][j]/(double)counter_gen[indx[0]][j])))  << "&" << counter_rec[indx[1]][j] << "&" << counter_rec[indx[1]][j]/(counter_gen[indx[1]][j]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec[indx[1]][j]/(counter_gen[indx[1]][j]*1.0))*sqrt(((counter_rec_uncert[indx[1]][j]/(double)counter_rec[indx[1]][j])*(counter_rec_uncert[indx[1]][j]/(double)counter_rec[indx[1]][j])) + ((counter_gen_uncert[indx[1]][j]/(double)counter_gen[indx[1]][j])*(counter_gen_uncert[indx[1]][j]/(double)counter_gen[indx[1]][j]))) << "&" << counter_rec[indx[2]][j] << "&" << counter_rec[indx[2]][j]/(counter_gen[indx[2]][j]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec[indx[2]][j]/(counter_gen[indx[2]][j]*1.0))*sqrt(((counter_rec_uncert[indx[2]][j]/(double)counter_rec[indx[2]][j])*(counter_rec_uncert[indx[2]][j]/(double)counter_rec[indx[2]][j])) + ((counter_gen_uncert[indx[2]][j]/(double)counter_gen[indx[2]][j])*(counter_gen_uncert[indx[2]][j]/(double)counter_gen[indx[2]][j]))) << "&" << counter_rec[indx[3]][j] << "&" << counter_rec[indx[3]][j]/(counter_gen[indx[3]][j]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec[indx[3]][j]/(counter_gen[indx[3]][j]*1.0))*sqrt(((counter_rec_uncert[indx[3]][j]/(double)counter_rec[indx[3]][j])*(counter_rec_uncert[indx[3]][j]/(double)counter_rec[indx[3]][j])) + ((counter_gen_uncert[indx[3]][j]/(double)counter_gen[indx[3]][j])*(counter_gen_uncert[indx[3]][j]/(double)counter_gen[indx[3]][j]))) << "&" << counter_rec[indx[3]][j] << "&" << counter_rec[indx[4]][j]/(counter_gen[indx[4]][j]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec[indx[4]][j]/(counter_gen[indx[4]][j]*1.0))*sqrt(((counter_rec_uncert[indx[4]][j]/(double)counter_rec[indx[4]][j])*(counter_rec_uncert[indx[4]][j]/(double)counter_rec[indx[4]][j])) + ((counter_gen_uncert[indx[4]][j]/(double)counter_gen[indx[4]][j])*(counter_gen_uncert[indx[4]][j]/(double)counter_gen[indx[4]][j])))  << "\\\\" << std::endl;
        }
        if(j>0){
          out << cutsrec[j].c_str() << "&" << counter_rec[indx[0]][j] << "&" << counter_rec[indx[0]][j]/(counter_rec[indx[0]][j-1]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec[indx[0]][j]/(counter_rec[indx[0]][j-1]*1.0))*sqrt(((counter_rec_uncert[indx[0]][j]/(double)counter_rec[indx[0]][j])*(counter_rec_uncert[indx[0]][j]/(double)counter_rec[indx[0]][j])) + ((counter_rec_uncert[indx[0]][j-1]/(double)counter_rec[indx[0]][j-1])*(counter_rec_uncert[indx[0]][j-1]/(double)counter_rec[indx[0]][j-1])))  << "&" << counter_rec[indx[1]][j] << "&" << counter_rec[indx[1]][j]/(counter_rec[indx[1]][j-1]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec[indx[1]][j]/(counter_rec[indx[1]][j-1]*1.0))*sqrt(((counter_rec_uncert[indx[1]][j]/(double)counter_rec[indx[1]][j])*(counter_rec_uncert[indx[1]][j]/(double)counter_rec[indx[1]][j])) + ((counter_rec_uncert[indx[1]][j-1]/(double)counter_rec[indx[1]][j-1])*(counter_rec_uncert[indx[1]][j-1]/(double)counter_rec[indx[1]][j-1])))  << "&" << counter_rec[indx[2]][j] << "&" << counter_rec[indx[2]][j]/(counter_rec[indx[2]][j-1]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec[indx[2]][j]/(counter_rec[indx[2]][j-1]*1.0))*sqrt(((counter_rec_uncert[indx[2]][j]/(double)counter_rec[indx[2]][j])*(counter_rec_uncert[indx[2]][j]/(double)counter_rec[indx[2]][j])) + ((counter_rec_uncert[indx[2]][j-1]/(double)counter_rec[indx[2]][j-1])*(counter_rec_uncert[indx[2]][j-1]/(double)counter_rec[indx[2]][j-1])))  << "&" << counter_rec[indx[3]][j] << "&" << counter_rec[indx[3]][j]/(counter_rec[indx[3]][j-1]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec[indx[3]][j]/(counter_rec[indx[3]][j-1]*1.0))*sqrt(((counter_rec_uncert[indx[3]][j]/(double)counter_rec[indx[3]][j])*(counter_rec_uncert[indx[3]][j]/(double)counter_rec[indx[3]][j])) + ((counter_rec_uncert[indx[3]][j-1]/(double)counter_rec[indx[3]][j-1])*(counter_rec_uncert[indx[3]][j-1]/(double)counter_rec[indx[3]][j-1])))  << "&" << counter_rec[indx[4]][j] << "&" << counter_rec[indx[4]][j]/(counter_rec[indx[4]][j-1]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec[indx[4]][j]/(counter_rec[indx[4]][j-1]*1.0))*sqrt(((counter_rec_uncert[indx[4]][j]/(double)counter_rec[indx[4]][j])*(counter_rec_uncert[indx[4]][j]/(double)counter_rec[indx[4]][j])) + ((counter_rec_uncert[indx[4]][j-1]/(double)counter_rec[indx[4]][j-1])*(counter_rec_uncert[indx[4]][j-1]/(double)counter_rec[indx[4]][j-1])))  << "\\\\ " << std::endl;
        }
      }

    }
    out << " \\hline " << std::endl;
    out << "\\multicolumn{2}{|c}{\\textbf{Auxiliary event selections (reco):}} \\\\ \\hline" << std::endl;

    for(int j=0;j<2;j++){

      if (k==0){        
        if(j==0)
        {
          out << cutsdim[j].c_str() << "&" << counter_rec_dimuons[indx[0]][j] << "&" << counter_rec_dimuons[indx[0]][j]/(counter_rec[indx[0]][3]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec_dimuons[indx[0]][j]/(counter_rec[indx[0]][3]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[0]][j]/(double)counter_rec_dimuons[indx[0]][j])*(counter_rec_dimuons_uncert[indx[0]][j]/(double)counter_rec_dimuons[indx[0]][j])) + ((counter_rec_uncert[indx[0]][3]/(double)counter_rec[indx[0]][3])*(counter_rec_uncert[indx[0]][3]/(double)counter_rec[indx[0]][3])))  << "&" << counter_rec_dimuons[indx[1]][j] << "&" << counter_rec_dimuons[indx[1]][j]/(counter_rec[indx[1]][3]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec_dimuons[indx[1]][j]/(counter_rec[indx[1]][3]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[1]][j]/(double)counter_rec_dimuons[indx[1]][j])*(counter_rec_dimuons_uncert[indx[1]][j]/(double)counter_rec_dimuons[indx[1]][j])) + ((counter_rec_uncert[indx[1]][3]/(double)counter_rec[indx[1]][3])*(counter_rec_uncert[indx[1]][3]/(double)counter_rec[indx[1]][3]))) << "&" << counter_rec_dimuons[indx[2]][j] << "&" << counter_rec_dimuons[indx[2]][j]/(counter_rec[indx[2]][3]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec_dimuons[indx[2]][j]/(counter_rec[indx[2]][3]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[2]][j]/(double)counter_rec_dimuons[indx[2]][j])*(counter_rec_dimuons_uncert[indx[2]][j]/(double)counter_rec_dimuons[indx[2]][j])) + ((counter_rec_uncert[indx[2]][3]/(double)counter_rec[indx[2]][3])*(counter_rec_uncert[indx[2]][3]/(double)counter_rec[indx[2]][3])))  << "&" << counter_rec_dimuons[indx[3]][j] << "&" << counter_rec_dimuons[indx[3]][j]/(counter_rec[indx[3]][3]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec_dimuons[indx[3]][j]/(counter_rec[indx[3]][3]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[3]][j]/(double)counter_rec_dimuons[indx[3]][j])*(counter_rec_dimuons_uncert[indx[3]][j]/(double)counter_rec_dimuons[indx[3]][j])) + ((counter_rec_uncert[indx[3]][3]/(double)counter_rec[indx[3]][3])*(counter_rec_uncert[indx[3]][3]/(double)counter_rec[indx[3]][3])))  << "&" << counter_rec_dimuons[indx[3]][j] << "&" << counter_rec_dimuons[indx[4]][j]/(counter_rec[indx[4]][3]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec_dimuons[indx[4]][j]/(counter_rec[indx[4]][3]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[4]][j]/(double)counter_rec_dimuons[indx[4]][j])*(counter_rec_dimuons_uncert[indx[4]][j]/(double)counter_rec_dimuons[indx[4]][j])) + ((counter_rec_uncert[indx[4]][3]/(double)counter_rec[indx[4]][3])*(counter_rec_uncert[indx[4]][3]/(double)counter_rec[indx[4]][3])))  << "&" << counter_rec_dimuons[indx[3]][j] << "&" << counter_rec_dimuons[indx[5]][j]/(counter_rec[indx[5]][3]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) <<  (counter_rec_dimuons[indx[5]][j]/(counter_rec[indx[5]][3]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[5]][j]/(double)counter_rec_dimuons[indx[5]][j])*(counter_rec_dimuons_uncert[indx[5]][j]/(double)counter_rec_dimuons[indx[5]][j])) + ((counter_rec_uncert[indx[5]][3]/(double)counter_rec[indx[5]][3])*(counter_rec_uncert[indx[5]][3]/(double)counter_rec[indx[5]][3])))  << "\\\\" << std::endl;
        }
        if(j>0)
        {
          out << cutsdim[j].c_str() << "&" << counter_rec_dimuons[indx[0]][j] << "&" << counter_rec_dimuons[indx[0]][j]/(counter_rec_dimuons[indx[0]][j-1]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) <<  (counter_rec_dimuons[indx[0]][j]/(counter_rec_dimuons[indx[0]][j-1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[0]][j]/(double)counter_rec_dimuons[indx[0]][j])*(counter_rec_dimuons_uncert[indx[0]][j]/(double)counter_rec_dimuons[indx[0]][j])) + ((counter_rec_uncert[indx[0]][j-1]/(double)counter_rec_dimuons[indx[0]][j-1])*(counter_rec_uncert[indx[0]][j-1]/(double)counter_rec_dimuons[indx[0]][j-1]))) << "&" << counter_rec_dimuons[indx[1]][j] << "&" << counter_rec_dimuons[indx[1]][j]/(counter_rec_dimuons[indx[1]][j-1]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) <<  (counter_rec_dimuons[indx[1]][j]/(counter_rec_dimuons[indx[1]][j-1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[1]][j]/(double)counter_rec_dimuons[indx[1]][j])*(counter_rec_dimuons_uncert[indx[1]][j]/(double)counter_rec_dimuons[indx[1]][j])) + ((counter_rec_uncert[indx[1]][j-1]/(double)counter_rec_dimuons[indx[1]][j-1])*(counter_rec_uncert[indx[1]][j-1]/(double)counter_rec_dimuons[indx[1]][j-1])))  << "&" << counter_rec_dimuons[indx[2]][j] << "&" << counter_rec_dimuons[indx[2]][j]/(counter_rec_dimuons[indx[2]][j-1]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) <<   (counter_rec_dimuons[indx[2]][j]/(counter_rec_dimuons[indx[2]][j-1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[2]][j]/(double)counter_rec_dimuons[indx[2]][j])*(counter_rec_dimuons_uncert[indx[2]][j]/(double)counter_rec_dimuons[indx[2]][j])) + ((counter_rec_uncert[indx[2]][j-1]/(double)counter_rec_dimuons[indx[2]][j-1])*(counter_rec_uncert[indx[2]][j-1]/(double)counter_rec_dimuons[indx[2]][j-1])))   << "&" << counter_rec_dimuons[indx[3]][j] << "&" << counter_rec_dimuons[indx[3]][j]/(counter_rec_dimuons[indx[3]][j-1]*1.0) << " $\\pm$ ";

          out << std::setprecision(2) <<   (counter_rec_dimuons[indx[3]][j]/(counter_rec_dimuons[indx[3]][j-1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[3]][j]/(double)counter_rec_dimuons[indx[3]][j])*(counter_rec_dimuons_uncert[indx[3]][j]/(double)counter_rec_dimuons[indx[3]][j])) + ((counter_rec_uncert[indx[3]][j-1]/(double)counter_rec_dimuons[indx[3]][j-1])*(counter_rec_uncert[indx[3]][j-1]/(double)counter_rec_dimuons[indx[3]][j-1])))   << "&" << counter_rec_dimuons[indx[4]][j] << "&" << counter_rec_dimuons[indx[4]][j]/(counter_rec_dimuons[indx[4]][j-1]*1.0) << " $\\pm$ ";

          out << std::setprecision(2) <<   (counter_rec_dimuons[indx[4]][j]/(counter_rec_dimuons[indx[4]][j-1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[4]][j]/(double)counter_rec_dimuons[indx[4]][j])*(counter_rec_dimuons_uncert[indx[4]][j]/(double)counter_rec_dimuons[indx[4]][j])) + ((counter_rec_uncert[indx[4]][j-1]/(double)counter_rec_dimuons[indx[4]][j-1])*(counter_rec_uncert[indx[4]][j-1]/(double)counter_rec_dimuons[indx[4]][j-1])))   << "&" << counter_rec_dimuons[indx[5]][j] << "&" << counter_rec_dimuons[indx[5]][j]/(counter_rec_dimuons[indx[5]][j-1]*1.0) << " $\\pm$ ";

          out << std::setprecision(2) <<   (counter_rec_dimuons[indx[5]][j]/(counter_rec_dimuons[indx[5]][j-1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[5]][j]/(double)counter_rec_dimuons[indx[5]][j])*(counter_rec_dimuons_uncert[indx[5]][j]/(double)counter_rec_dimuons[indx[5]][j])) + ((counter_rec_uncert[indx[5]][j-1]/(double)counter_rec_dimuons[indx[5]][j-1])*(counter_rec_uncert[indx[5]][j-1]/(double)counter_rec_dimuons[indx[5]][j-1])))   << "\\\\" << std::endl;
        }
      }

      if (k==1){        
        if(j==0)
        {
          out << cutsdim[j].c_str() << "&" << counter_rec_dimuons[indx[0]][j] << "&" << counter_rec_dimuons[indx[0]][j]/(counter_rec[indx[0]][3]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec_dimuons[indx[0]][j]/(counter_rec[indx[0]][3]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[0]][j]/(double)counter_rec_dimuons[indx[0]][j])*(counter_rec_dimuons_uncert[indx[0]][j]/(double)counter_rec_dimuons[indx[0]][j])) + ((counter_rec_uncert[indx[0]][3]/(double)counter_rec[indx[0]][3])*(counter_rec_uncert[indx[0]][3]/(double)counter_rec[indx[0]][3])))  << "&" << counter_rec_dimuons[indx[1]][j] << "&" << counter_rec_dimuons[indx[1]][j]/(counter_rec[indx[1]][3]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec_dimuons[indx[1]][j]/(counter_rec[indx[1]][3]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[1]][j]/(double)counter_rec_dimuons[indx[1]][j])*(counter_rec_dimuons_uncert[indx[1]][j]/(double)counter_rec_dimuons[indx[1]][j])) + ((counter_rec_uncert[indx[1]][3]/(double)counter_rec[indx[1]][3])*(counter_rec_uncert[indx[1]][3]/(double)counter_rec[indx[1]][3]))) << "&" << counter_rec_dimuons[indx[2]][j] << "&" << counter_rec_dimuons[indx[2]][j]/(counter_rec[indx[2]][3]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec_dimuons[indx[2]][j]/(counter_rec[indx[2]][3]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[2]][j]/(double)counter_rec_dimuons[indx[2]][j])*(counter_rec_dimuons_uncert[indx[2]][j]/(double)counter_rec_dimuons[indx[2]][j])) + ((counter_rec_uncert[indx[2]][3]/(double)counter_rec[indx[2]][3])*(counter_rec_uncert[indx[2]][3]/(double)counter_rec[indx[2]][3])))  << "&" << counter_rec_dimuons[indx[3]][j] << "&" << counter_rec_dimuons[indx[3]][j]/(counter_rec[indx[3]][3]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec_dimuons[indx[3]][j]/(counter_rec[indx[3]][3]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[3]][j]/(double)counter_rec_dimuons[indx[3]][j])*(counter_rec_dimuons_uncert[indx[3]][j]/(double)counter_rec_dimuons[indx[3]][j])) + ((counter_rec_uncert[indx[3]][3]/(double)counter_rec[indx[3]][3])*(counter_rec_uncert[indx[3]][3]/(double)counter_rec[indx[3]][3])))  << "&" << counter_rec_dimuons[indx[3]][j] << "&" << counter_rec_dimuons[indx[4]][j]/(counter_rec[indx[4]][3]*1.0) << " $\\pm$ ";

          out << std::setprecision(2) <<  (counter_rec_dimuons[indx[4]][j]/(counter_rec[indx[4]][3]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[4]][j]/(double)counter_rec_dimuons[indx[4]][j])*(counter_rec_dimuons_uncert[indx[4]][j]/(double)counter_rec_dimuons[indx[4]][j])) + ((counter_rec_uncert[indx[4]][3]/(double)counter_rec[indx[4]][3])*(counter_rec_uncert[indx[4]][3]/(double)counter_rec[indx[4]][3])))  << "\\\\" << std::endl;
        }
        if(j>0)
        {
          out << cutsdim[j].c_str() << "&" << counter_rec_dimuons[indx[0]][j] << "&" << counter_rec_dimuons[indx[0]][j]/(counter_rec_dimuons[indx[0]][j-1]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) <<  (counter_rec_dimuons[indx[0]][j]/(counter_rec_dimuons[indx[0]][j-1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[0]][j]/(double)counter_rec_dimuons[indx[0]][j])*(counter_rec_dimuons_uncert[indx[0]][j]/(double)counter_rec_dimuons[indx[0]][j])) + ((counter_rec_uncert[indx[0]][j-1]/(double)counter_rec_dimuons[indx[0]][j-1])*(counter_rec_uncert[indx[0]][j-1]/(double)counter_rec_dimuons[indx[0]][j-1]))) << "&" << counter_rec_dimuons[indx[1]][j] << "&" << counter_rec_dimuons[indx[1]][j]/(counter_rec_dimuons[indx[1]][j-1]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) <<  (counter_rec_dimuons[indx[1]][j]/(counter_rec_dimuons[indx[1]][j-1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[1]][j]/(double)counter_rec_dimuons[indx[1]][j])*(counter_rec_dimuons_uncert[indx[1]][j]/(double)counter_rec_dimuons[indx[1]][j])) + ((counter_rec_uncert[indx[1]][j-1]/(double)counter_rec_dimuons[indx[1]][j-1])*(counter_rec_uncert[indx[1]][j-1]/(double)counter_rec_dimuons[indx[1]][j-1])))  << "&" << counter_rec_dimuons[indx[2]][j] << "&" << counter_rec_dimuons[indx[2]][j]/(counter_rec_dimuons[indx[2]][j-1]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) <<   (counter_rec_dimuons[indx[2]][j]/(counter_rec_dimuons[indx[2]][j-1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[2]][j]/(double)counter_rec_dimuons[indx[2]][j])*(counter_rec_dimuons_uncert[indx[2]][j]/(double)counter_rec_dimuons[indx[2]][j])) + ((counter_rec_uncert[indx[2]][j-1]/(double)counter_rec_dimuons[indx[2]][j-1])*(counter_rec_uncert[indx[2]][j-1]/(double)counter_rec_dimuons[indx[2]][j-1])))   << "&" << counter_rec_dimuons[indx[3]][j] << "&" << counter_rec_dimuons[indx[3]][j]/(counter_rec_dimuons[indx[3]][j-1]*1.0) << " $\\pm$ ";

          out << std::setprecision(2) <<   (counter_rec_dimuons[indx[3]][j]/(counter_rec_dimuons[indx[3]][j-1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[3]][j]/(double)counter_rec_dimuons[indx[3]][j])*(counter_rec_dimuons_uncert[indx[3]][j]/(double)counter_rec_dimuons[indx[3]][j])) + ((counter_rec_uncert[indx[3]][j-1]/(double)counter_rec_dimuons[indx[3]][j-1])*(counter_rec_uncert[indx[3]][j-1]/(double)counter_rec_dimuons[indx[3]][j-1])))   << "&" << counter_rec_dimuons[indx[4]][j] << "&" << counter_rec_dimuons[indx[4]][j]/(counter_rec_dimuons[indx[4]][j-1]*1.0) << " $\\pm$ ";

          out << std::setprecision(2) <<   (counter_rec_dimuons[indx[4]][j]/(counter_rec_dimuons[indx[4]][j-1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[4]][j]/(double)counter_rec_dimuons[indx[4]][j])*(counter_rec_dimuons_uncert[indx[4]][j]/(double)counter_rec_dimuons[indx[4]][j])) + ((counter_rec_uncert[indx[4]][j-1]/(double)counter_rec_dimuons[indx[4]][j-1])*(counter_rec_uncert[indx[4]][j-1]/(double)counter_rec_dimuons[indx[4]][j-1])))   << "\\\\" << std::endl;
        }
      }


    }
  
    for(int j=2;j<7;j++){

      if (k==0){        
        
        if(j==2){
          out << cutsdim[j].c_str() << "&" << counter_rec_dimuons[indx[0]][j] << "&" << counter_rec_dimuons[indx[0]][j]/(counter_rec_dimuons[indx[0]][1]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec_dimuons[indx[0]][j]/(counter_rec_dimuons[indx[0]][1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[0]][j]/(double)counter_rec_dimuons[indx[0]][j])*(counter_rec_dimuons_uncert[indx[0]][j]/(double)counter_rec_dimuons[indx[0]][j])) + ((counter_rec_dimuons_uncert[indx[0]][1]/(double)counter_rec_dimuons[indx[0]][1]*1.0)*(counter_rec_dimuons_uncert[indx[0]][1]/(double)counter_rec_dimuons[indx[0]][1]*1.0))) << "&" << counter_rec_dimuons[indx[1]][j] << "&" << counter_rec_dimuons[indx[1]][j]/(counter_rec_dimuons[indx[1]][1]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec_dimuons[indx[1]][j]/(counter_rec_dimuons[indx[1]][1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[1]][j]/(double)counter_rec_dimuons[indx[1]][j])*(counter_rec_dimuons_uncert[indx[1]][j]/(double)counter_rec_dimuons[indx[1]][j])) + ((counter_rec_dimuons_uncert[indx[1]][1]/(double)counter_rec_dimuons[indx[1]][1]*1.0)*(counter_rec_dimuons_uncert[indx[1]][1]/(double)counter_rec_dimuons[indx[1]][1]*1.0))) << "&" << counter_rec_dimuons[indx[2]][j] << "&" << counter_rec_dimuons[indx[2]][j]/(counter_rec_dimuons[indx[2]][1]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec_dimuons[indx[2]][j]/(counter_rec_dimuons[indx[2]][1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[2]][j]/(double)counter_rec_dimuons[indx[2]][j])*(counter_rec_dimuons_uncert[indx[2]][j]/(double)counter_rec_dimuons[indx[2]][j])) + ((counter_rec_dimuons_uncert[indx[2]][1]/(double)counter_rec_dimuons[indx[2]][1]*1.0)*(counter_rec_dimuons_uncert[indx[2]][1]/(double)counter_rec_dimuons[indx[2]][1]*1.0))) << "&" << counter_rec_dimuons[indx[3]][j] << "&" << counter_rec_dimuons[indx[3]][j]/(counter_rec_dimuons[indx[3]][1]*1.0) << " $\\pm$ ";

          out << std::setprecision(2) << (counter_rec_dimuons[indx[3]][j]/(counter_rec_dimuons[indx[3]][1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[3]][j]/(double)counter_rec_dimuons[indx[3]][j])*(counter_rec_dimuons_uncert[indx[3]][j]/(double)counter_rec_dimuons[indx[3]][j])) + ((counter_rec_dimuons_uncert[indx[3]][1]/(double)counter_rec_dimuons[indx[3]][1]*1.0)*(counter_rec_dimuons_uncert[indx[3]][1]/(double)counter_rec_dimuons[indx[3]][1]*1.0))) << "&" << counter_rec_dimuons[indx[4]][j] << "&" << counter_rec_dimuons[indx[4]][j]/(counter_rec_dimuons[indx[4]][1]*1.0) << " $\\pm$ ";

          out << std::setprecision(2) << (counter_rec_dimuons[indx[4]][j]/(counter_rec_dimuons[indx[4]][1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[4]][j]/(double)counter_rec_dimuons[indx[4]][j])*(counter_rec_dimuons_uncert[indx[4]][j]/(double)counter_rec_dimuons[indx[4]][j])) + ((counter_rec_dimuons_uncert[indx[4]][1]/(double)counter_rec_dimuons[indx[4]][1]*1.0)*(counter_rec_dimuons_uncert[indx[4]][1]/(double)counter_rec_dimuons[indx[4]][1]*1.0))) << "&" << counter_rec_dimuons[indx[5]][j] << "&" << counter_rec_dimuons[indx[5]][j]/(counter_rec_dimuons[indx[5]][1]*1.0) << " $\\pm$ ";

          out << std::setprecision(2) << (counter_rec_dimuons[indx[5]][j]/(counter_rec_dimuons[indx[5]][1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[5]][j]/(double)counter_rec_dimuons[indx[5]][j])*(counter_rec_dimuons_uncert[indx[5]][j]/(double)counter_rec_dimuons[indx[5]][j])) + ((counter_rec_dimuons_uncert[indx[5]][1]/(double)counter_rec_dimuons[indx[5]][1]*1.0)*(counter_rec_dimuons_uncert[indx[5]][1]/(double)counter_rec_dimuons[indx[5]][1]*1.0))) << "\\\\" << std::endl;
        }
        if(j>2){
          out << cutsdim[j].c_str() << "&" << counter_rec_dimuons[indx[0]][j] << "&" << counter_rec_dimuons[indx[0]][j]/(counter_rec_dimuons[indx[0]][j-1]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec_dimuons[indx[0]][j]/(counter_rec_dimuons[indx[0]][j-1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[0]][j]/(double)counter_rec_dimuons[indx[0]][j])*(counter_rec_dimuons_uncert[indx[0]][j]/(double)counter_rec_dimuons[indx[0]][j])) + ((counter_rec_dimuons_uncert[indx[0]][j-1]/(double)counter_rec_dimuons[indx[0]][j-1]*1.0)*(counter_rec_dimuons_uncert[indx[0]][j-1]/(double)counter_rec_dimuons[indx[0]][j-1]*1.0))) << "&" << counter_rec_dimuons[indx[1]][j] << "&" << counter_rec_dimuons[indx[1]][j]/(counter_rec_dimuons[indx[1]][j-1]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec_dimuons[indx[1]][j]/(counter_rec_dimuons[indx[1]][j-1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[1]][j]/(double)counter_rec_dimuons[indx[1]][j])*(counter_rec_dimuons_uncert[indx[1]][j]/(double)counter_rec_dimuons[indx[1]][j])) + ((counter_rec_dimuons_uncert[indx[1]][j-1]/(double)counter_rec_dimuons[indx[1]][j-1]*1.0)*(counter_rec_dimuons_uncert[indx[1]][j-1]/(double)counter_rec_dimuons[indx[1]][j-1]*1.0))) << "&" << counter_rec_dimuons[indx[2]][j] << "&" << counter_rec_dimuons[indx[2]][j]/(counter_rec_dimuons[indx[2]][j-1]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec_dimuons[indx[2]][j]/(counter_rec_dimuons[indx[2]][j-1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[2]][j]/(double)counter_rec_dimuons[indx[2]][j])*(counter_rec_dimuons_uncert[indx[2]][j]/(double)counter_rec_dimuons[indx[2]][j])) + ((counter_rec_dimuons_uncert[indx[2]][j-1]/(double)counter_rec_dimuons[indx[2]][j-1]*1.0)*(counter_rec_dimuons_uncert[indx[2]][j-1]/(double)counter_rec_dimuons[indx[2]][j-1]*1.0))) << "&" << counter_rec_dimuons[indx[3]][j] << "&" << counter_rec_dimuons[indx[3]][j]/(counter_rec_dimuons[indx[3]][j-1]*1.0) << " $\\pm$ ";

          out << std::setprecision(2) << (counter_rec_dimuons[indx[3]][j]/(counter_rec_dimuons[indx[3]][j-1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[3]][j]/(double)counter_rec_dimuons[indx[3]][j])*(counter_rec_dimuons_uncert[indx[3]][j]/(double)counter_rec_dimuons[indx[3]][j])) + ((counter_rec_dimuons_uncert[indx[3]][j-1]/(double)counter_rec_dimuons[indx[3]][j-1]*1.0)*(counter_rec_dimuons_uncert[indx[3]][j-1]/(double)counter_rec_dimuons[indx[3]][j-1]*1.0))) << "&" << counter_rec_dimuons[indx[4]][j] << "&" << counter_rec_dimuons[indx[4]][j]/(counter_rec_dimuons[indx[4]][j-1]*1.0) << " $\\pm$ ";

          out << std::setprecision(2) << (counter_rec_dimuons[indx[4]][j]/(counter_rec_dimuons[indx[4]][j-1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[4]][j]/(double)counter_rec_dimuons[indx[4]][j])*(counter_rec_dimuons_uncert[indx[4]][j]/(double)counter_rec_dimuons[indx[4]][j])) + ((counter_rec_dimuons_uncert[indx[4]][j-1]/(double)counter_rec_dimuons[indx[4]][j-1]*1.0)*(counter_rec_dimuons_uncert[indx[4]][j-1]/(double)counter_rec_dimuons[indx[4]][j-1]*1.0))) << "&" << counter_rec_dimuons[indx[5]][j] << "&" << counter_rec_dimuons[indx[5]][j]/(counter_rec_dimuons[indx[5]][j-1]*1.0) << " $\\pm$ ";

          out << std::setprecision(2) << (counter_rec_dimuons[indx[5]][j]/(counter_rec_dimuons[indx[5]][j-1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[5]][j]/(double)counter_rec_dimuons[indx[5]][j])*(counter_rec_dimuons_uncert[indx[5]][j]/(double)counter_rec_dimuons[indx[5]][j])) + ((counter_rec_dimuons_uncert[indx[5]][j-1]/(double)counter_rec_dimuons[indx[5]][j-1]*1.0)*(counter_rec_dimuons_uncert[indx[5]][j-1]/(double)counter_rec_dimuons[indx[5]][j-1]*1.0))) << "\\\\" << std::endl;
        }
      }


      if (k==1){        
        
        if(j==2){
          out << cutsdim[j].c_str() << "&" << counter_rec_dimuons[indx[0]][j] << "&" << counter_rec_dimuons[indx[0]][j]/(counter_rec_dimuons[indx[0]][1]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec_dimuons[indx[0]][j]/(counter_rec_dimuons[indx[0]][1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[0]][j]/(double)counter_rec_dimuons[indx[0]][j])*(counter_rec_dimuons_uncert[indx[0]][j]/(double)counter_rec_dimuons[indx[0]][j])) + ((counter_rec_dimuons_uncert[indx[0]][1]/(double)counter_rec_dimuons[indx[0]][1]*1.0)*(counter_rec_dimuons_uncert[indx[0]][1]/(double)counter_rec_dimuons[indx[0]][1]*1.0))) << "&" << counter_rec_dimuons[indx[1]][j] << "&" << counter_rec_dimuons[indx[1]][j]/(counter_rec_dimuons[indx[1]][1]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec_dimuons[indx[1]][j]/(counter_rec_dimuons[indx[1]][1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[1]][j]/(double)counter_rec_dimuons[indx[1]][j])*(counter_rec_dimuons_uncert[indx[1]][j]/(double)counter_rec_dimuons[indx[1]][j])) + ((counter_rec_dimuons_uncert[indx[1]][1]/(double)counter_rec_dimuons[indx[1]][1]*1.0)*(counter_rec_dimuons_uncert[indx[1]][1]/(double)counter_rec_dimuons[indx[1]][1]*1.0))) << "&" << counter_rec_dimuons[indx[2]][j] << "&" << counter_rec_dimuons[indx[2]][j]/(counter_rec_dimuons[indx[2]][1]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec_dimuons[indx[2]][j]/(counter_rec_dimuons[indx[2]][1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[2]][j]/(double)counter_rec_dimuons[indx[2]][j])*(counter_rec_dimuons_uncert[indx[2]][j]/(double)counter_rec_dimuons[indx[2]][j])) + ((counter_rec_dimuons_uncert[indx[2]][1]/(double)counter_rec_dimuons[indx[2]][1]*1.0)*(counter_rec_dimuons_uncert[indx[2]][1]/(double)counter_rec_dimuons[indx[2]][1]*1.0))) << "&" << counter_rec_dimuons[indx[3]][j] << "&" << counter_rec_dimuons[indx[3]][j]/(counter_rec_dimuons[indx[3]][1]*1.0) << " $\\pm$ ";

          out << std::setprecision(2) << (counter_rec_dimuons[indx[3]][j]/(counter_rec_dimuons[indx[3]][1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[3]][j]/(double)counter_rec_dimuons[indx[3]][j])*(counter_rec_dimuons_uncert[indx[3]][j]/(double)counter_rec_dimuons[indx[3]][j])) + ((counter_rec_dimuons_uncert[indx[3]][1]/(double)counter_rec_dimuons[indx[3]][1]*1.0)*(counter_rec_dimuons_uncert[indx[3]][1]/(double)counter_rec_dimuons[indx[3]][1]*1.0))) << "&" << counter_rec_dimuons[indx[4]][j] << "&" << counter_rec_dimuons[indx[4]][j]/(counter_rec_dimuons[indx[4]][1]*1.0) << " $\\pm$ ";

          out << std::setprecision(2) << (counter_rec_dimuons[indx[4]][j]/(counter_rec_dimuons[indx[4]][1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[4]][j]/(double)counter_rec_dimuons[indx[4]][j])*(counter_rec_dimuons_uncert[indx[4]][j]/(double)counter_rec_dimuons[indx[4]][j])) + ((counter_rec_dimuons_uncert[indx[4]][1]/(double)counter_rec_dimuons[indx[4]][1]*1.0)*(counter_rec_dimuons_uncert[indx[4]][1]/(double)counter_rec_dimuons[indx[4]][1]*1.0))) << "\\\\" << std::endl;
        }
        if(j>2){
          out << cutsdim[j].c_str() << "&" << counter_rec_dimuons[indx[0]][j] << "&" << counter_rec_dimuons[indx[0]][j]/(counter_rec_dimuons[indx[0]][j-1]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec_dimuons[indx[0]][j]/(counter_rec_dimuons[indx[0]][j-1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[0]][j]/(double)counter_rec_dimuons[indx[0]][j])*(counter_rec_dimuons_uncert[indx[0]][j]/(double)counter_rec_dimuons[indx[0]][j])) + ((counter_rec_dimuons_uncert[indx[0]][j-1]/(double)counter_rec_dimuons[indx[0]][j-1]*1.0)*(counter_rec_dimuons_uncert[indx[0]][j-1]/(double)counter_rec_dimuons[indx[0]][j-1]*1.0))) << "&" << counter_rec_dimuons[indx[1]][j] << "&" << counter_rec_dimuons[indx[1]][j]/(counter_rec_dimuons[indx[1]][j-1]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec_dimuons[indx[1]][j]/(counter_rec_dimuons[indx[1]][j-1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[1]][j]/(double)counter_rec_dimuons[indx[1]][j])*(counter_rec_dimuons_uncert[indx[1]][j]/(double)counter_rec_dimuons[indx[1]][j])) + ((counter_rec_dimuons_uncert[indx[1]][j-1]/(double)counter_rec_dimuons[indx[1]][j-1]*1.0)*(counter_rec_dimuons_uncert[indx[1]][j-1]/(double)counter_rec_dimuons[indx[1]][j-1]*1.0))) << "&" << counter_rec_dimuons[indx[2]][j] << "&" << counter_rec_dimuons[indx[2]][j]/(counter_rec_dimuons[indx[2]][j-1]*1.0) << " $\\pm$ ";
          out << std::setprecision(2) << (counter_rec_dimuons[indx[2]][j]/(counter_rec_dimuons[indx[2]][j-1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[2]][j]/(double)counter_rec_dimuons[indx[2]][j])*(counter_rec_dimuons_uncert[indx[2]][j]/(double)counter_rec_dimuons[indx[2]][j])) + ((counter_rec_dimuons_uncert[indx[2]][j-1]/(double)counter_rec_dimuons[indx[2]][j-1]*1.0)*(counter_rec_dimuons_uncert[indx[2]][j-1]/(double)counter_rec_dimuons[indx[2]][j-1]*1.0))) << "&" << counter_rec_dimuons[indx[3]][j] << "&" << counter_rec_dimuons[indx[3]][j]/(counter_rec_dimuons[indx[3]][j-1]*1.0) << " $\\pm$ ";

          out << std::setprecision(2) << (counter_rec_dimuons[indx[3]][j]/(counter_rec_dimuons[indx[3]][j-1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[3]][j]/(double)counter_rec_dimuons[indx[3]][j])*(counter_rec_dimuons_uncert[indx[3]][j]/(double)counter_rec_dimuons[indx[3]][j])) + ((counter_rec_dimuons_uncert[indx[3]][j-1]/(double)counter_rec_dimuons[indx[3]][j-1]*1.0)*(counter_rec_dimuons_uncert[indx[3]][j-1]/(double)counter_rec_dimuons[indx[3]][j-1]*1.0))) << "&" << counter_rec_dimuons[indx[4]][j] << "&" << counter_rec_dimuons[indx[4]][j]/(counter_rec_dimuons[indx[4]][j-1]*1.0) << " $\\pm$ ";


          out << std::setprecision(2) << (counter_rec_dimuons[indx[4]][j]/(counter_rec_dimuons[indx[4]][j-1]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[4]][j]/(double)counter_rec_dimuons[indx[4]][j])*(counter_rec_dimuons_uncert[indx[4]][j]/(double)counter_rec_dimuons[indx[4]][j])) + ((counter_rec_dimuons_uncert[indx[4]][j-1]/(double)counter_rec_dimuons[indx[4]][j-1]*1.0)*(counter_rec_dimuons_uncert[indx[4]][j-1]/(double)counter_rec_dimuons[indx[4]][j-1]*1.0))) << "\\\\" << std::endl;
        }
      }



    }
    out << "\\hline" << std::endl;
    
    if (k==0){        
      
      out << "$\\alpha_{gen}$ " << " & " << "&" << counter_genlxylz2[indx[0]][4]/(counter_gen[indx[0]][0]*1.0) << " $\\pm$ ";
      out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_genlxylz2[indx[0]][4]/(counter_gen[indx[0]][0]*1.0))*sqrt(((counter_genlxylz2_uncert[indx[0]][4]/(double)counter_genlxylz2[indx[0]][4])*(counter_genlxylz2_uncert[indx[0]][4]/(double)counter_genlxylz2[indx[0]][4])) + ((counter_gen_uncert[indx[0]][0]/(double)counter_gen[indx[0]][0]*1.0)*(counter_gen_uncert[indx[0]][0]/(double)counter_gen[indx[0]][0]*1.0))) << "&" << "&" << counter_genlxylz2[indx[1]][4]/(counter_gen[indx[1]][0]*1.0) << " $\\pm$ ";
      out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_genlxylz2[indx[1]][4]/(counter_gen[indx[1]][0]*1.0))*sqrt(((counter_genlxylz2_uncert[indx[1]][4]/(double)counter_genlxylz2[indx[1]][4])*(counter_genlxylz2_uncert[indx[1]][4]/(double)counter_genlxylz2[indx[1]][4])) + ((counter_gen_uncert[indx[1]][0]/(double)counter_gen[indx[1]][0]*1.0)*(counter_gen_uncert[indx[1]][0]/(double)counter_gen[indx[1]][0]*1.0))) << "&" << "&" << counter_genlxylz2[indx[2]][4]/(counter_gen[indx[2]][0]*1.0) << " $\\pm$ ";
      out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_genlxylz2[indx[2]][4]/(counter_gen[indx[2]][0]*1.0))*sqrt(((counter_genlxylz2_uncert[indx[2]][4]/(double)counter_genlxylz2[indx[2]][4])*(counter_genlxylz2_uncert[indx[2]][4]/(double)counter_genlxylz2[indx[2]][4])) + ((counter_gen_uncert[indx[2]][0]/(double)counter_gen[indx[2]][0]*1.0)*(counter_gen_uncert[indx[2]][0]/(double)counter_gen[indx[2]][0]*1.0))) << "&" << "&" << counter_genlxylz2[indx[3]][4]/(counter_gen[indx[3]][0]*1.0) << " $\\pm$ ";
      out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_genlxylz2[indx[3]][4]/(counter_gen[indx[3]][0]*1.0))*sqrt(((counter_genlxylz2_uncert[indx[3]][4]/(double)counter_genlxylz2[indx[3]][4])*(counter_genlxylz2_uncert[indx[3]][4]/(double)counter_genlxylz2[indx[3]][4])) + ((counter_gen_uncert[indx[3]][0]/(double)counter_gen[indx[3]][0]*1.0)*(counter_gen_uncert[indx[3]][0]/(double)counter_gen[indx[3]][0]*1.0))) << "&" << "&" << counter_genlxylz2[indx[4]][4]/(counter_gen[indx[4]][0]*1.0) << " $\\pm$ ";
      out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_genlxylz2[indx[4]][4]/(counter_gen[indx[4]][0]*1.0))*sqrt(((counter_genlxylz2_uncert[indx[4]][4]/(double)counter_genlxylz2[indx[4]][4])*(counter_genlxylz2_uncert[indx[4]][4]/(double)counter_genlxylz2[indx[4]][4])) + ((counter_gen_uncert[indx[4]][0]/(double)counter_gen[indx[4]][0]*1.0)*(counter_gen_uncert[indx[4]][0]/(double)counter_gen[indx[4]][0]*1.0))) << "&" << "&" << counter_genlxylz2[indx[5]][4]/(counter_gen[indx[5]][0]*1.0) << " $\\pm$ ";
      out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_genlxylz2[indx[5]][4]/(counter_gen[indx[5]][0]*1.0))*sqrt(((counter_genlxylz2_uncert[indx[5]][4]/(double)counter_genlxylz2[indx[5]][4])*(counter_genlxylz2_uncert[indx[5]][4]/(double)counter_genlxylz2[indx[5]][4])) + ((counter_gen_uncert[indx[5]][0]/(double)counter_gen[indx[5]][0]*1.0)*(counter_gen_uncert[indx[5]][0]/(double)counter_gen[indx[5]][0]*1.0))) << "\\\\" << std::endl;


      out << "$\\epsilon_{full}$ " << " & " << "&" << counter_rec_dimuons[indx[0]][6]/(counter_gen[indx[0]][0]*1.0) << " $\\pm$ ";
      out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_rec_dimuons[indx[0]][6]/(counter_gen[indx[0]][0]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[0]][6]/(double)counter_rec_dimuons[indx[0]][6])*(counter_rec_dimuons_uncert[indx[0]][6]/(double)counter_rec_dimuons[indx[0]][6])) + ((counter_gen_uncert[indx[0]][0]/(double)counter_gen[indx[0]][0]*1.0)*(counter_gen_uncert[indx[0]][0]/(double)counter_gen[indx[0]][0]*1.0))) << "&" << "&" << counter_rec_dimuons[indx[1]][6]/(counter_gen[indx[1]][0]*1.0) << " $\\pm$ ";
      out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_rec_dimuons[indx[1]][6]/(counter_gen[indx[1]][0]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[1]][6]/(double)counter_rec_dimuons[indx[1]][6])*(counter_rec_dimuons_uncert[indx[1]][6]/(double)counter_rec_dimuons[indx[1]][6])) + ((counter_gen_uncert[indx[1]][0]/(double)counter_gen[indx[1]][0]*1.0)*(counter_gen_uncert[indx[1]][0]/(double)counter_gen[indx[1]][0]*1.0))) << "&" << "&" << counter_rec_dimuons[indx[2]][6]/(counter_gen[indx[2]][0]*1.0) << " $\\pm$ ";
      out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_rec_dimuons[indx[2]][6]/(counter_gen[indx[2]][0]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[2]][6]/(double)counter_rec_dimuons[indx[2]][6])*(counter_rec_dimuons_uncert[indx[2]][6]/(double)counter_rec_dimuons[indx[2]][6])) + ((counter_gen_uncert[indx[2]][0]/(double)counter_gen[indx[2]][0]*1.0)*(counter_gen_uncert[indx[2]][0]/(double)counter_gen[indx[2]][0]*1.0))) << "&" << "&" << counter_rec_dimuons[indx[3]][6]/(counter_gen[indx[3]][0]*1.0) << " $\\pm$ ";
      out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_rec_dimuons[indx[3]][6]/(counter_gen[indx[3]][0]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[3]][6]/(double)counter_rec_dimuons[indx[3]][6])*(counter_rec_dimuons_uncert[indx[3]][6]/(double)counter_rec_dimuons[indx[3]][6])) + ((counter_gen_uncert[indx[3]][0]/(double)counter_gen[indx[3]][0]*1.0)*(counter_gen_uncert[indx[3]][0]/(double)counter_gen[indx[3]][0]*1.0))) << "&" << "&" << counter_rec_dimuons[indx[4]][6]/(counter_gen[indx[4]][0]*1.0) << " $\\pm$ ";
      out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_rec_dimuons[indx[4]][6]/(counter_gen[indx[4]][0]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[4]][6]/(double)counter_rec_dimuons[indx[4]][6])*(counter_rec_dimuons_uncert[indx[4]][6]/(double)counter_rec_dimuons[indx[4]][6])) + ((counter_gen_uncert[indx[4]][0]/(double)counter_gen[indx[4]][0]*1.0)*(counter_gen_uncert[indx[4]][0]/(double)counter_gen[indx[4]][0]*1.0))) << "&" << "&" << counter_rec_dimuons[indx[5]][6]/(counter_gen[indx[5]][0]*1.0) << " $\\pm$ ";
      out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_rec_dimuons[indx[5]][6]/(counter_gen[indx[5]][0]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[5]][6]/(double)counter_rec_dimuons[indx[5]][6])*(counter_rec_dimuons_uncert[indx[5]][6]/(double)counter_rec_dimuons[indx[5]][6])) + ((counter_gen_uncert[indx[5]][0]/(double)counter_gen[indx[5]][0]*1.0)*(counter_gen_uncert[indx[5]][0]/(double)counter_gen[indx[5]][0]*1.0))) << "\\\\" << std::endl;

      out << "\\hline" << std::endl;

      out << " $\\epsilon_{full}/\\alpha_{gen}$ " << " & " << "&" << counter_rec_dimuons[indx[0]][6]/(counter_genlxylz2[indx[0]][4]*1.0) << " $\\pm$ ";
      // out.unsetf(ios_base::fixed);
      out << std::fixed << std::setprecision(2) << (counter_rec_dimuons[indx[0]][6]/(counter_genlxylz2[indx[0]][4]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[0]][6]/(double)counter_rec_dimuons[indx[0]][6])*(counter_rec_dimuons_uncert[indx[0]][6]/(double)counter_rec_dimuons[indx[0]][6])) + ((counter_genlxylz2_uncert[indx[0]][4]/(double)counter_genlxylz2[indx[0]][4]*1.0)*(counter_genlxylz2_uncert[indx[0]][4]/(double)counter_genlxylz2[indx[0]][4]*1.0))) << "&" << "&" << counter_rec_dimuons[indx[1]][6]/(counter_genlxylz2[indx[1]][4]*1.0) << " $\\pm$ ";
      // out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_rec_dimuons[indx[1]][6]/(counter_genlxylz2[indx[1]][4]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[1]][6]/(double)counter_rec_dimuons[indx[1]][6])*(counter_rec_dimuons_uncert[indx[1]][6]/(double)counter_rec_dimuons[indx[1]][6])) + ((counter_genlxylz2_uncert[indx[1]][4]/(double)counter_genlxylz2[indx[1]][4]*1.0)*(counter_genlxylz2_uncert[indx[1]][4]/(double)counter_genlxylz2[indx[1]][4]*1.0))) << "&" << "&" << counter_rec_dimuons[indx[2]][6]/(counter_genlxylz2[indx[2]][4]*1.0) << " $\\pm$ ";
      // out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_rec_dimuons[indx[2]][6]/(counter_genlxylz2[indx[2]][4]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[2]][6]/(double)counter_rec_dimuons[indx[2]][6])*(counter_rec_dimuons_uncert[indx[2]][6]/(double)counter_rec_dimuons[indx[2]][6])) + ((counter_genlxylz2_uncert[indx[2]][4]/(double)counter_genlxylz2[indx[2]][4]*1.0)*(counter_genlxylz2_uncert[indx[2]][4]/(double)counter_genlxylz2[indx[2]][4]*1.0))) << "&" << "&" << counter_rec_dimuons[indx[3]][6]/(counter_genlxylz2[indx[3]][4]*1.0) << " $\\pm$ ";

      out << std::setprecision(2) << (counter_rec_dimuons[indx[3]][6]/(counter_genlxylz2[indx[3]][4]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[3]][6]/(double)counter_rec_dimuons[indx[3]][6])*(counter_rec_dimuons_uncert[indx[3]][6]/(double)counter_rec_dimuons[indx[3]][6])) + ((counter_genlxylz2_uncert[indx[3]][4]/(double)counter_genlxylz2[indx[3]][4]*1.0)*(counter_genlxylz2_uncert[indx[3]][4]/(double)counter_genlxylz2[indx[3]][4]*1.0))) << "&" << "&" << counter_rec_dimuons[indx[4]][6]/(counter_genlxylz2[indx[4]][4]*1.0) << " $\\pm$ ";

      out << std::setprecision(2) << (counter_rec_dimuons[indx[4]][6]/(counter_genlxylz2[indx[4]][4]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[4]][6]/(double)counter_rec_dimuons[indx[4]][6])*(counter_rec_dimuons_uncert[indx[4]][6]/(double)counter_rec_dimuons[indx[4]][6])) + ((counter_genlxylz2_uncert[indx[4]][4]/(double)counter_genlxylz2[indx[4]][4]*1.0)*(counter_genlxylz2_uncert[indx[4]][4]/(double)counter_genlxylz2[indx[4]][4]*1.0))) << "&" << "&" << counter_rec_dimuons[indx[5]][6]/(counter_genlxylz2[indx[5]][4]*1.0) << " $\\pm$ ";


      // out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_rec_dimuons[indx[5]][6]/(counter_genlxylz2[indx[5]][4]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[5]][6]/(double)counter_rec_dimuons[indx[5]][6])*(counter_rec_dimuons_uncert[indx[5]][6]/(double)counter_rec_dimuons[indx[5]][6])) + ((counter_genlxylz2_uncert[indx[5]][4]/(double)counter_genlxylz2[indx[5]][4]*1.0)*(counter_genlxylz2_uncert[indx[5]][4]/(double)counter_genlxylz2[indx[5]][4]*1.0))) << "\\\\" << std::endl;
    }

    if (k==1){        
      
      out << "$\\alpha_{gen}$ " << " & " << "&" << counter_genlxylz2[indx[0]][4]/(counter_gen[indx[0]][0]*1.0) << " $\\pm$ ";
      out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_genlxylz2[indx[0]][4]/(counter_gen[indx[0]][0]*1.0))*sqrt(((counter_genlxylz2_uncert[indx[0]][4]/(double)counter_genlxylz2[indx[0]][4])*(counter_genlxylz2_uncert[indx[0]][4]/(double)counter_genlxylz2[indx[0]][4])) + ((counter_gen_uncert[indx[0]][0]/(double)counter_gen[indx[0]][0]*1.0)*(counter_gen_uncert[indx[0]][0]/(double)counter_gen[indx[0]][0]*1.0))) << "&" << "&" << counter_genlxylz2[indx[1]][4]/(counter_gen[indx[1]][0]*1.0) << " $\\pm$ ";
      out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_genlxylz2[indx[1]][4]/(counter_gen[indx[1]][0]*1.0))*sqrt(((counter_genlxylz2_uncert[indx[1]][4]/(double)counter_genlxylz2[indx[1]][4])*(counter_genlxylz2_uncert[indx[1]][4]/(double)counter_genlxylz2[indx[1]][4])) + ((counter_gen_uncert[indx[1]][0]/(double)counter_gen[indx[1]][0]*1.0)*(counter_gen_uncert[indx[1]][0]/(double)counter_gen[indx[1]][0]*1.0))) << "&" << "&" << counter_genlxylz2[indx[2]][4]/(counter_gen[indx[2]][0]*1.0) << " $\\pm$ ";
      out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_genlxylz2[indx[2]][4]/(counter_gen[indx[2]][0]*1.0))*sqrt(((counter_genlxylz2_uncert[indx[2]][4]/(double)counter_genlxylz2[indx[2]][4])*(counter_genlxylz2_uncert[indx[2]][4]/(double)counter_genlxylz2[indx[2]][4])) + ((counter_gen_uncert[indx[2]][0]/(double)counter_gen[indx[2]][0]*1.0)*(counter_gen_uncert[indx[2]][0]/(double)counter_gen[indx[2]][0]*1.0))) << "&" << "&" << counter_genlxylz2[indx[3]][4]/(counter_gen[indx[3]][0]*1.0) << " $\\pm$ ";
      out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_genlxylz2[indx[3]][4]/(counter_gen[indx[3]][0]*1.0))*sqrt(((counter_genlxylz2_uncert[indx[3]][4]/(double)counter_genlxylz2[indx[3]][4])*(counter_genlxylz2_uncert[indx[3]][4]/(double)counter_genlxylz2[indx[3]][4])) + ((counter_gen_uncert[indx[3]][0]/(double)counter_gen[indx[3]][0]*1.0)*(counter_gen_uncert[indx[3]][0]/(double)counter_gen[indx[3]][0]*1.0))) << "&" << "&" << counter_genlxylz2[indx[4]][4]/(counter_gen[indx[4]][0]*1.0) << " $\\pm$ ";
      out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_genlxylz2[indx[4]][4]/(counter_gen[indx[4]][0]*1.0))*sqrt(((counter_genlxylz2_uncert[indx[4]][4]/(double)counter_genlxylz2[indx[4]][4])*(counter_genlxylz2_uncert[indx[4]][4]/(double)counter_genlxylz2[indx[4]][4])) + ((counter_gen_uncert[indx[4]][0]/(double)counter_gen[indx[4]][0]*1.0)*(counter_gen_uncert[indx[4]][0]/(double)counter_gen[indx[4]][0]*1.0))) << "\\\\" << std::endl;


      out << "$\\epsilon_{full}$ " << " & " << "&" << counter_rec_dimuons[indx[0]][6]/(counter_gen[indx[0]][0]*1.0) << " $\\pm$ ";
      out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_rec_dimuons[indx[0]][6]/(counter_gen[indx[0]][0]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[0]][6]/(double)counter_rec_dimuons[indx[0]][6])*(counter_rec_dimuons_uncert[indx[0]][6]/(double)counter_rec_dimuons[indx[0]][6])) + ((counter_gen_uncert[indx[0]][0]/(double)counter_gen[indx[0]][0]*1.0)*(counter_gen_uncert[indx[0]][0]/(double)counter_gen[indx[0]][0]*1.0))) << "&" << "&" << counter_rec_dimuons[indx[1]][6]/(counter_gen[indx[1]][0]*1.0) << " $\\pm$ ";
      out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_rec_dimuons[indx[1]][6]/(counter_gen[indx[1]][0]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[1]][6]/(double)counter_rec_dimuons[indx[1]][6])*(counter_rec_dimuons_uncert[indx[1]][6]/(double)counter_rec_dimuons[indx[1]][6])) + ((counter_gen_uncert[indx[1]][0]/(double)counter_gen[indx[1]][0]*1.0)*(counter_gen_uncert[indx[1]][0]/(double)counter_gen[indx[1]][0]*1.0))) << "&" << "&" << counter_rec_dimuons[indx[2]][6]/(counter_gen[indx[2]][0]*1.0) << " $\\pm$ ";
      out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_rec_dimuons[indx[2]][6]/(counter_gen[indx[2]][0]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[2]][6]/(double)counter_rec_dimuons[indx[2]][6])*(counter_rec_dimuons_uncert[indx[2]][6]/(double)counter_rec_dimuons[indx[2]][6])) + ((counter_gen_uncert[indx[2]][0]/(double)counter_gen[indx[2]][0]*1.0)*(counter_gen_uncert[indx[2]][0]/(double)counter_gen[indx[2]][0]*1.0))) << "&" << "&" << counter_rec_dimuons[indx[3]][6]/(counter_gen[indx[3]][0]*1.0) << " $\\pm$ ";
      out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_rec_dimuons[indx[3]][6]/(counter_gen[indx[3]][0]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[3]][6]/(double)counter_rec_dimuons[indx[3]][6])*(counter_rec_dimuons_uncert[indx[3]][6]/(double)counter_rec_dimuons[indx[3]][6])) + ((counter_gen_uncert[indx[3]][0]/(double)counter_gen[indx[3]][0]*1.0)*(counter_gen_uncert[indx[3]][0]/(double)counter_gen[indx[3]][0]*1.0))) << "&" << "&" << counter_rec_dimuons[indx[4]][6]/(counter_gen[indx[4]][0]*1.0) << " $\\pm$ ";
      out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_rec_dimuons[indx[4]][6]/(counter_gen[indx[4]][0]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[4]][6]/(double)counter_rec_dimuons[indx[4]][6])*(counter_rec_dimuons_uncert[indx[4]][6]/(double)counter_rec_dimuons[indx[4]][6])) + ((counter_gen_uncert[indx[4]][0]/(double)counter_gen[indx[4]][0]*1.0)*(counter_gen_uncert[indx[4]][0]/(double)counter_gen[indx[4]][0]*1.0))) << "\\\\" << std::endl;

      out << "\\hline" << std::endl;

      out << " $\\epsilon_{full}/\\alpha_{gen}$ " << " & " << "&" << counter_rec_dimuons[indx[0]][6]/(counter_genlxylz2[indx[0]][4]*1.0) << " $\\pm$ ";
      // out.unsetf(ios_base::fixed);
      out << std::fixed << std::setprecision(2) << (counter_rec_dimuons[indx[0]][6]/(counter_genlxylz2[indx[0]][4]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[0]][6]/(double)counter_rec_dimuons[indx[0]][6])*(counter_rec_dimuons_uncert[indx[0]][6]/(double)counter_rec_dimuons[indx[0]][6])) + ((counter_genlxylz2_uncert[indx[0]][4]/(double)counter_genlxylz2[indx[0]][4]*1.0)*(counter_genlxylz2_uncert[indx[0]][4]/(double)counter_genlxylz2[indx[0]][4]*1.0))) << "&" << "&" << counter_rec_dimuons[indx[1]][6]/(counter_genlxylz2[indx[1]][4]*1.0) << " $\\pm$ ";
      // out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_rec_dimuons[indx[1]][6]/(counter_genlxylz2[indx[1]][4]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[1]][6]/(double)counter_rec_dimuons[indx[1]][6])*(counter_rec_dimuons_uncert[indx[1]][6]/(double)counter_rec_dimuons[indx[1]][6])) + ((counter_genlxylz2_uncert[indx[1]][4]/(double)counter_genlxylz2[indx[1]][4]*1.0)*(counter_genlxylz2_uncert[indx[1]][4]/(double)counter_genlxylz2[indx[1]][4]*1.0))) << "&" << "&" << counter_rec_dimuons[indx[2]][6]/(counter_genlxylz2[indx[2]][4]*1.0) << " $\\pm$ ";
      // out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_rec_dimuons[indx[2]][6]/(counter_genlxylz2[indx[2]][4]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[2]][6]/(double)counter_rec_dimuons[indx[2]][6])*(counter_rec_dimuons_uncert[indx[2]][6]/(double)counter_rec_dimuons[indx[2]][6])) + ((counter_genlxylz2_uncert[indx[2]][4]/(double)counter_genlxylz2[indx[2]][4]*1.0)*(counter_genlxylz2_uncert[indx[2]][4]/(double)counter_genlxylz2[indx[2]][4]*1.0))) << "&" << "&" << counter_rec_dimuons[indx[3]][6]/(counter_genlxylz2[indx[3]][4]*1.0) << " $\\pm$ ";

      out << std::setprecision(2) << (counter_rec_dimuons[indx[3]][6]/(counter_genlxylz2[indx[3]][4]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[3]][6]/(double)counter_rec_dimuons[indx[3]][6])*(counter_rec_dimuons_uncert[indx[3]][6]/(double)counter_rec_dimuons[indx[3]][6])) + ((counter_genlxylz2_uncert[indx[3]][4]/(double)counter_genlxylz2[indx[3]][4]*1.0)*(counter_genlxylz2_uncert[indx[3]][4]/(double)counter_genlxylz2[indx[3]][4]*1.0))) << "&" << "&" << counter_rec_dimuons[indx[4]][6]/(counter_genlxylz2[indx[4]][4]*1.0) << " $\\pm$ ";


      // out.unsetf(ios_base::fixed);
      out << std::setprecision(2) << (counter_rec_dimuons[indx[4]][6]/(counter_genlxylz2[indx[4]][4]*1.0))*sqrt(((counter_rec_dimuons_uncert[indx[4]][6]/(double)counter_rec_dimuons[indx[4]][6])*(counter_rec_dimuons_uncert[indx[4]][6]/(double)counter_rec_dimuons[indx[4]][6])) + ((counter_genlxylz2_uncert[indx[4]][4]/(double)counter_genlxylz2[indx[4]][4]*1.0)*(counter_genlxylz2_uncert[indx[4]][4]/(double)counter_genlxylz2[indx[4]][4]*1.0))) << "\\\\" << std::endl;
    }

    std::cout << out.str() << std::endl;
     
     
     
    cout<<"  \\hline  "<<endl;
    cout<<"\\end{tabular} "<<endl;
    cout<<"\\end{table} "<<endl;
    std::cout<<"\\end{landscape} "<<endl;
  }

  std::cout << "\\end{document}" << std::endl;
  
  Float_t ctau1[1]={0.0};
  Float_t ctau2[3]={0.5,2.0,5.0}; 
  Float_t ctau3[4]={0.0,0.1,0.2,0.5};
  Float_t ctau4[4]={0.2,0.5,2.0,5.0};
  Float_t ctau5[3]={0.0,0.5,2.0};
  Float_t ctau6[5]={0.0,0.2,0.5,2.0,5.0};
  Float_t ctau7[7]={0.0,0.2,0.5,1.0,2.0,3.0,5.0};
  Float_t ctau8[6]={0.0,0.2,1.0,2.0,3.0,5.0};
  Float_t ctau9[9]={0.0,0.05,0.1,0.2,0.5,1.0,2.0,3.0,5.0};

  Float_t errctau1[1]={0.0};
  Float_t errctau2[3]={0.0};
  Float_t errctau3[4]={0.0};
  Float_t errctau4[4]={0.0};
  Float_t errctau5[3]={0.0};
  Float_t errctau6[5]={0.0};
  Float_t errctau7[7]={0.0};
  Float_t errctau8[6]={0.0};
  Float_t errctau9[9]={0.0};

  TGraphErrors *gr_ctau0 = new TGraphErrors(9,mass1,eff_ctau0,errmass1,erreff_ctau0);
  TGraphErrors *gr_ctau01 = new TGraphErrors(2,mass2,eff_ctau01,errmass2,erreff_ctau01);
  TGraphErrors *gr_ctau02 = new TGraphErrors(7,mass3,eff_ctau02,errmass3,erreff_ctau02);
  TGraphErrors *gr_ctau05 = new TGraphErrors(8,mass4,eff_ctau05,errmass4,erreff_ctau05);
  TGraphErrors *gr_ctau1 = new TGraphErrors(3,mass5,eff_ctau1,errmass5,erreff_ctau1);
  TGraphErrors *gr_ctau2 = new TGraphErrors(8,mass6,eff_ctau2,errmass6,erreff_ctau2);
  TGraphErrors *gr_ctau3 = new TGraphErrors(3,mass7,eff_ctau3,errmass7,erreff_ctau3);
  TGraphErrors *gr_ctau5 = new TGraphErrors(7,mass8,eff_ctau5,errmass8,erreff_ctau5);


  TGraphErrors *gr_mD0250 = new TGraphErrors(9,ctau9,eff_mD0250,errctau9,erreff_mD0250);
  TGraphErrors *gr_mD0275 = new TGraphErrors(1,ctau1,eff_mD0275,errctau1,erreff_mD0275);
  TGraphErrors *gr_mD0300 = new TGraphErrors(4,ctau3,eff_mD0300,errctau3,erreff_mD0300);
  TGraphErrors *gr_mD0350 = new TGraphErrors(1,ctau1,eff_mD0350,errctau1,erreff_mD0350);
  TGraphErrors *gr_mD0400 = new TGraphErrors(4,ctau4,eff_mD0400,errctau4,erreff_mD0400);
  TGraphErrors *gr_mD0550 = new TGraphErrors(5,ctau7,eff_mD0550,errctau7,erreff_mD0550);
  TGraphErrors *gr_mD0700 = new TGraphErrors(5,ctau6,eff_mD0700,errctau6,erreff_mD0700);
  TGraphErrors *gr_mD0850 = new TGraphErrors(5,ctau6,eff_mD0850,errctau6,erreff_mD0850);
  TGraphErrors *gr_mD1000 = new TGraphErrors(6,ctau8,eff_mD1000,errctau8,erreff_mD1000);
  TGraphErrors *gr_mD1500 = new TGraphErrors(3,ctau2,eff_mD1500,errctau2,erreff_mD1500);
  TGraphErrors *gr_mD2000 = new TGraphErrors(3,ctau5,eff_mD2000,errctau5,erreff_mD2000);

  TGraphErrors *gr2_mD0250 = new TGraphErrors(9,ctau9,effr_mD0250,errctau9,erreffr_mD0250);
  TGraphErrors *gr2_mD0275 = new TGraphErrors(1,ctau1,effr_mD0275,errctau1,erreffr_mD0275);
  TGraphErrors *gr2_mD0300 = new TGraphErrors(4,ctau3,effr_mD0300,errctau3,erreffr_mD0300);
  TGraphErrors *gr2_mD0350 = new TGraphErrors(1,ctau1,effr_mD0350,errctau1,erreffr_mD0350);
  TGraphErrors *gr2_mD0400 = new TGraphErrors(4,ctau4,effr_mD0400,errctau4,erreffr_mD0400);
  TGraphErrors *gr2_mD0550 = new TGraphErrors(5,ctau7,effr_mD0550,errctau7,erreffr_mD0550);
  TGraphErrors *gr2_mD0700 = new TGraphErrors(5,ctau6,effr_mD0700,errctau6,erreffr_mD0700);
  TGraphErrors *gr2_mD0850 = new TGraphErrors(5,ctau6,effr_mD0850,errctau6,erreffr_mD0850);
  TGraphErrors *gr2_mD1000 = new TGraphErrors(6,ctau8,effr_mD1000,errctau8,erreffr_mD1000);
  TGraphErrors *gr2_mD1500 = new TGraphErrors(3,ctau2,effr_mD1500,errctau2,erreffr_mD1500);
  TGraphErrors *gr2_mD2000 = new TGraphErrors(3,ctau5,effr_mD2000,errctau5,erreffr_mD2000);


  TGraphErrors *gr3_mD0250 = new TGraphErrors(9,ctau9,effr2_mD0250,errctau9,erreffr2_mD0250);
  TGraphErrors *gr3_mD0275 = new TGraphErrors(1,ctau1,effr2_mD0275,errctau1,erreffr2_mD0275);
  TGraphErrors *gr3_mD0300 = new TGraphErrors(4,ctau3,effr2_mD0300,errctau3,erreffr2_mD0300);
  TGraphErrors *gr3_mD0350 = new TGraphErrors(1,ctau1,effr2_mD0350,errctau1,erreffr2_mD0350);
  TGraphErrors *gr3_mD0400 = new TGraphErrors(4,ctau4,effr2_mD0400,errctau4,erreffr2_mD0400);
  TGraphErrors *gr3_mD0550 = new TGraphErrors(5,ctau7,effr2_mD0550,errctau7,erreffr2_mD0550);
  TGraphErrors *gr3_mD0700 = new TGraphErrors(5,ctau6,effr2_mD0700,errctau6,erreffr2_mD0700);
  TGraphErrors *gr3_mD0850 = new TGraphErrors(5,ctau6,effr2_mD0850,errctau6,erreffr2_mD0850);
  TGraphErrors *gr3_mD1000 = new TGraphErrors(6,ctau8,effr2_mD1000,errctau8,erreffr2_mD1000);
  TGraphErrors *gr3_mD1500 = new TGraphErrors(3,ctau2,effr2_mD1500,errctau2,erreffr2_mD1500);
  TGraphErrors *gr3_mD2000 = new TGraphErrors(3,ctau5,effr2_mD2000,errctau5,erreffr2_mD2000);
  
  TH2F *dummy = new TH2F("","",100,-0.2,5.2,100,0.0,0.1);
  TH2F *dummy3 = new TH2F("","",100,-0.2,5.2,100,0.0,1.0);
  TH2F *dummy2 = new TH2F("","",100,0.24,2.2,100,0.0,0.1);

  

  TLegend *leg = new TLegend(0.6,0.5,0.8,0.9);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetTextSize(0.036);
  leg->AddEntry(gr_mD0250,"#gamma_{D} mass = 0.25 GeV","PL");
  leg->AddEntry(gr_mD0275,"#gamma_{D} mass = 0.275 GeV","PL");
  leg->AddEntry(gr_mD0300,"#gamma_{D} mass = 0.3 GeV","PL");
  leg->AddEntry(gr_mD0350,"#gamma_{D} mass = 0.35 GeV","PL");
  leg->AddEntry(gr_mD0400,"#gamma_{D} mass = 0.4 GeV","PL");
  leg->AddEntry(gr_mD0550,"#gamma_{D} mass = 0.55 GeV","PL");
  leg->AddEntry(gr_mD0700,"#gamma_{D} mass = 0.70 GeV","PL");
  leg->AddEntry(gr_mD0850,"#gamma_{D} mass = 0.85 GeV","PL");
  leg->AddEntry(gr_mD1000,"#gamma_{D} mass = 1.0  GeV","PL");
  leg->AddEntry(gr_mD1500,"#gamma_{D} mass = 1.5  GeV","PL");
  leg->AddEntry(gr_mD2000,"#gamma_{D} mass = 2.0  GeV","PL");


  TLegend *legg = new TLegend(0.55,0.15,0.8,0.55);
  legg->SetBorderSize(0);
  legg->SetFillColor(0);
  legg->SetTextSize(0.036);
  legg->AddEntry(gr_mD0250,"#gamma_{D} mass = 0.25 GeV","PL");
  legg->AddEntry(gr_mD0275,"#gamma_{D} mass = 0.275 GeV","PL");
  legg->AddEntry(gr_mD0300,"#gamma_{D} mass = 0.3 GeV","PL");
  legg->AddEntry(gr_mD0350,"#gamma_{D} mass = 0.35 GeV","PL");
  legg->AddEntry(gr_mD0400,"#gamma_{D} mass = 0.4 GeV","PL");
  legg->AddEntry(gr_mD0550,"#gamma_{D} mass = 0.55 GeV","PL");
  legg->AddEntry(gr_mD0700,"#gamma_{D} mass = 0.70 GeV","PL");
  legg->AddEntry(gr_mD0850,"#gamma_{D} mass = 0.85 GeV","PL");
  legg->AddEntry(gr_mD1000,"#gamma_{D} mass = 1.0  GeV","PL");
  legg->AddEntry(gr_mD1500,"#gamma_{D} mass = 1.5  GeV","PL");
  legg->AddEntry(gr_mD2000,"#gamma_{D} mass = 2.0  GeV","PL");

  TLegend *leg2 = new TLegend(0.6,0.5,0.8,0.9);
  leg2->SetBorderSize(0);
  leg2->SetFillColor(0);
  leg2->SetTextSize(0.036);
  leg2->AddEntry(gr_ctau0,"#gamma_{D} c#tau = 0 mm","PL");
  leg2->AddEntry(gr_ctau01,"#gamma_{D} c#tau = 0.1 mm","PL");
  leg2->AddEntry(gr_ctau02,"#gamma_{D} c#tau = 0.2 mm","PL");
  leg2->AddEntry(gr_ctau05,"#gamma_{D} c#tau = 0.5 mm","PL");
  leg2->AddEntry(gr_ctau1,"#gamma_{D} c#tau = 1 mm","PL");
  leg2->AddEntry(gr_ctau2,"#gamma_{D} c#tau = 2 mm","PL");
  leg2->AddEntry(gr_ctau3,"#gamma_{D} c#tau = 3 mm","PL");
  leg2->AddEntry(gr_ctau5,"#gamma_{D} c#tau = 5 mm","PL");


  gr_ctau01->SetLineColor(2);
  gr_ctau02->SetLineColor(3);
  gr_ctau05->SetLineColor(4);
  gr_ctau1->SetLineColor(5);
  gr_ctau2->SetLineColor(6);
  gr_ctau3->SetLineColor(7);
  gr_ctau5->SetLineColor(8);


  gr_ctau01->SetMarkerColor(2);
  gr_ctau02->SetMarkerColor(3);
  gr_ctau05->SetMarkerColor(4);
  gr_ctau1->SetMarkerColor(5);
  gr_ctau2->SetMarkerColor(6);
  gr_ctau3->SetMarkerColor(7);
  gr_ctau5->SetMarkerColor(8);

  gr_mD0275->SetLineColor(2);
  gr_mD0300->SetLineColor(3);
  gr_mD0350->SetLineColor(4);
  gr_mD0400->SetLineColor(5);
  gr_mD0550->SetLineColor(6);
  gr_mD0700->SetLineColor(7);
  gr_mD0850->SetLineColor(8);
  gr_mD1000->SetLineColor(9);
  gr_mD1500->SetLineColor(11);
  gr_mD2000->SetLineColor(12);

  gr_mD0275->SetMarkerColor(2);
  gr_mD0300->SetMarkerColor(3);
  gr_mD0350->SetMarkerColor(4);
  gr_mD0400->SetMarkerColor(5);
  gr_mD0550->SetMarkerColor(6);
  gr_mD0700->SetMarkerColor(7);
  gr_mD0850->SetMarkerColor(8);
  gr_mD1000->SetMarkerColor(9);
  gr_mD1500->SetMarkerColor(11);
  gr_mD2000->SetMarkerColor(12);


  gr2_mD0275->SetLineColor(2);
  gr2_mD0300->SetLineColor(3);
  gr2_mD0350->SetLineColor(4);
  gr2_mD0400->SetLineColor(5);
  gr2_mD0550->SetLineColor(6);
  gr2_mD0700->SetLineColor(7);
  gr2_mD0850->SetLineColor(8);
  gr2_mD1000->SetLineColor(9);
  gr2_mD1500->SetLineColor(11);
  gr2_mD2000->SetLineColor(12);

  gr2_mD0275->SetMarkerColor(2);
  gr2_mD0300->SetMarkerColor(3);
  gr2_mD0350->SetMarkerColor(4);
  gr2_mD0400->SetMarkerColor(5);
  gr2_mD0550->SetMarkerColor(6);
  gr2_mD0700->SetMarkerColor(7);
  gr2_mD0850->SetMarkerColor(8);
  gr2_mD1000->SetMarkerColor(9);
  gr2_mD1500->SetMarkerColor(11);
  gr2_mD2000->SetMarkerColor(12);


  TFile *f1 = new TFile("effvsctau.root","recreate");
  gr_mD0250->Write();
  gr_mD0275->Write();
  gr_mD0300->Write();
  gr_mD0350->Write();
  gr_mD0400->Write();
  gr_mD0550->Write();
  gr_mD0700->Write();
  gr_mD0850->Write();
  gr_mD1000->Write();
  gr_mD1500->Write();
  gr_mD2000->Write();
  f1->Close();
  
  TCanvas *c = new TCanvas("c","c",700,500);
  dummy->GetXaxis()->SetTitle("c#tau [mm]");
  dummy->GetYaxis()->SetTitle("#epsilon_{rec} = N_{rec}/N_{tot}");
  dummy->Draw();
  gr_mD0250->Draw("PLsame");
  gr_mD0275->Draw("PLsame");
  gr_mD0300->Draw("PLsame");
  gr_mD0350->Draw("PLsame");
  gr_mD0400->Draw("PLsame");
  gr_mD0550->Draw("PLsame");
  gr_mD0700->Draw("PLsame");
  gr_mD0850->Draw("PLsame");
  gr_mD1000->Draw("PLsame");
  gr_mD1500->Draw("PLsame");
  gr_mD2000->Draw("PLsame");
  leg->Draw("same");
  c->SaveAs("eff_vs_ctau.pdf","recreate");





  TCanvas *cc = new TCanvas("cc","cc",700,500);
  dummy3->GetXaxis()->SetTitle("c#tau [mm]");
  dummy3->GetYaxis()->SetTitle("#epsilon_{rec}/#alpha_{gen}");
  dummy3->Draw();
  gr2_mD0250->Draw("PLsame");
  gr2_mD0275->Draw("PLsame");
  gr2_mD0300->Draw("PLsame");
  gr2_mD0350->Draw("PLsame");
  gr2_mD0400->Draw("PLsame");
  gr2_mD0550->Draw("PLsame");
  gr2_mD0700->Draw("PLsame");
  gr2_mD0850->Draw("PLsame");
  gr2_mD1000->Draw("PLsame");
  gr2_mD1500->Draw("PLsame");
  gr2_mD2000->Draw("PLsame");
  legg->Draw("same");
  cc->SaveAs("effr_vs_ctau.pdf","recreate");


  TCanvas *ccc = new TCanvas("ccc","ccc",700,500);
  dummy3->GetXaxis()->SetTitle("c#tau [mm]");
  dummy3->GetYaxis()->SetTitle("#epsilon_{rec}/#alpha_{gen}");
  dummy3->Draw();
  gr3_mD0250->Draw("PLsame");
  gr3_mD0275->Draw("PLsame");
  gr3_mD0300->Draw("PLsame");
  gr3_mD0350->Draw("PLsame");
  gr3_mD0400->Draw("PLsame");
  gr3_mD0550->Draw("PLsame");
  gr3_mD0700->Draw("PLsame");
  gr3_mD0850->Draw("PLsame");
  gr3_mD1000->Draw("PLsame");
  gr3_mD1500->Draw("PLsame");
  gr3_mD2000->Draw("PLsame");
  leg->Draw("same");
  ccc->SaveAs("effr2_vs_ctau.pdf","recreate");

  TCanvas *c1 = new TCanvas("c1","c1",700,500);
  dummy2->GetXaxis()->SetTitle("mass [GeV]");
  dummy2->GetYaxis()->SetTitle("#epsilon_{rec} = N_{rec}/N_{tot}");
  dummy2->Draw();
  gr_ctau0->Draw("PLsame");
  gr_ctau01->Draw("PLsame");
  gr_ctau02->Draw("PLsame");
  gr_ctau05->Draw("PLsame");
  gr_ctau1->Draw("PLsame");
  gr_ctau2->Draw("PLsame");
  gr_ctau3->Draw("PLsame");
  gr_ctau5->Draw("PLsame");
  leg2->Draw("same");
  c1->SaveAs("eff_vs_mass.pdf","recreate");

    
  return 0;    

}
