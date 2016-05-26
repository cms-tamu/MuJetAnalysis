#include <iostream>
using namespace std;
#include <algorithm>    // std::max

void Analysis_hitrecoveryRun1(){


  Bool_t  analysisr1=false;
  Bool_t  analysisr2=false;;
  
  
  //  analysisr1=true;
  analysisr2=true;   // Analysis with 13TeV samples
  
  
  gStyle->SetOptStat(0);

  TFile *f[50];
  
  // f[0] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_0400_ctauExp_02_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  // f[1] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_0400_ctauExp_05_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  // f[2] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_0400_ctauExp_2_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  // f[3] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_0400_ctauExp_5_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");

  if(analysisr1){
     f[0] = new TFile("../../Anal2012data/RECOsamples/DarkSUSY_mH_125_mGammaD_0250_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
    f[1] = new TFile("../../Anal2012data/RECOsamples/DarkSUSY_mH_125_mGammaD_0250_ctauExp_02_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
    f[2] = new TFile("../../Anal2012data/RECOsamples/DarkSUSY_mH_125_mGammaD_0250_ctauExp_05_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
    f[3] = new TFile("../../Anal2012data/RECOsamples/DarkSUSY_mH_125_mGammaD_0250_ctauExp_1_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
    f[4] = new TFile("../../Anal2012data/RECOsamples/DarkSUSY_mH_125_mGammaD_0250_ctauExp_3_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_alfredo_0.root");
    f[5] = new TFile("../../Anal2012data/RECOsamples/DarkSUSY_mH_125_mGammaD_0250_ctauExp_5_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  }
   // //  f[9] = new TFile("~/DarkSUSY_mH_125_mGammaD_0250_ctauExp_3_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  // f[10] = new TFile("../../Anal2012data/RECOsamples/DarkSUSY_mH_125_mGammaD_0250_ctauExp_5_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");

  //================= 13 TeV ============================================

  if(analysisr2){
  f[0] =  new TFile("../MCsamples/DarkSUSY_mH_125_mGammaD_0250_cT_000_13TeV_RAW2DIGI_L1Reco_RECO_MCRUN2_74_V9_v1.root");
   f[1] =  new TFile("../MCsamples/DarkSUSY_mH_125_mGammaD_0250_cT_010_13TeV_RAW2DIGI_L1Reco_RECO_MCRUN2_74_V9_v1.root");
   f[2] =  new TFile("../MCsamples/DarkSUSY_mH_125_mGammaD_0250_cT_050_13TeV_RAW2DIGI_L1Reco_RECO_MCRUN2_74_V9_v1.root");
   f[3] =  new TFile("../MCsamples/DarkSUSY_mH_125_mGammaD_0250_cT_100_13TeV_RAW2DIGI_L1Reco_RECO_MCRUN2_74_V9_v1.root");
   f[4] =  new TFile("../MCsamples/DarkSUSY_mH_125_mGammaD_0250_cT_300_13TeV_RAW2DIGI_L1Reco_RECO_MCRUN2_74_V9_v1.root");
   f[5] =  new TFile("../MCsamples/DarkSUSY_mH_125_mGammaD_0250_cT_500_13TeV_RAW2DIGI_L1Reco_RECO_MCRUN2_74_V9_v1.root");
  }
  
  f[11] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_0700_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  f[12] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_0700_ctauExp_05_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  f[13] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_0700_ctauExp_2_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  f[14] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_0700_ctauExp_5_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");

  f[15] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_0850_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  f[16] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_0850_ctauExp_05_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  f[17] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_0850_ctauExp_5_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  
  f[18] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_1000_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  f[19] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_1000_ctauExp_05_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  f[20] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_1000_ctauExp_2_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  f[21] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_1000_ctauExp_5_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  
  f[22] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_1500_ctauExp_02_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  f[23] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_1500_ctauExp_05_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  f[24] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_1500_ctauExp_2_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  f[25] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_1500_ctauExp_5_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");

  f[26] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_2000_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  f[27] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_2000_ctauExp_02_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  f[28] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_2000_ctauExp_05_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  f[29] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_2000_ctauExp_2_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");

  f[30] = new TFile("~/darkSUSYsamples_8TeV/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_5312_GEN_v1_0.root");
  f[31] = new TFile("~/darkSUSYsamples_8TeV/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_5312_GEN_v1_0.root");
  f[32] = new TFile("~/darkSUSYsamples_8TeV/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_5312_GEN_v1_0.root");

  f[33] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_0250_ctauExp_20_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  f[34] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_0250_ctauExp_10_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  f[35] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_2000_ctauExp_10_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  f[36] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_2000_ctauExp_20_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");

  f[37] = new TFile("~/darkSUSYsamples_8TeV/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_5312_GEN_v1_0.root");

 
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

  for(int p=0;p<6;p++){
  //  for(int p=0;p<37;p++){
    
    //    if(p!=10) continue;
    
    if(analysisr1)   f[p]->cd("anatraj");
    else f[p]->cd("ana2012");

    TTree *t;
    if(analysisr1) t = (TTree*)f[p]->Get("anatraj/Events");
    else    t = (TTree*)f[p]->Get("ana2012/Events");
  
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
	      
	      if(is2DimVtxOK){
		ev_2dimvtxok[p]++;
	  
		if( (muJetChitgt[0]==1||muJetChitgt[1]==1)&&(muJetFhitgt[0]==1||muJetFhitgt[1]==1) )  ev_2dimhitgt[p]++;  
		if( ( (muJetChitgt[0]==1||muJetChitgt[1]==1)&&(muJetFhitgt[0]==1||muJetFhitgt[1]==1) ) && muJetC_validVtx_fitted && muJetF_validVtx_fitted  )  ev_2dimhitfvtx[p]++;  

		//		if( (muJetChit[0]==1||muJetChit[1]==1)&&(muJetFhit[0]==1||muJetFhit[1]==1)){
		if( ((muJetChitgt[0]==1||muJetChitgt[1]==1)&&(muJetFhitgt[0]==1||muJetFhitgt[1]==1))    ){
		//		if( ((muJetChitgt[0]==1||muJetChitgt[1]==1)&&(muJetFhitgt[0]==1||muJetFhitgt[1]==1))  && muJetC_validVtx_fitted && muJetF_validVtx_fitted   ){
		  ev_2dimhit[p]++;
	      
		  if(is2DimDzOK){
		    ev_is2DimDzOK[p]++;
		    if(is2DimHLTFired){ 
		      ev_is2DimHLTFired[p]++;
		      if(is2DimMassOK){
			ev_is2DimMassOK[p]++;
			if(is2DimIsoTkOK){
			  ev_is2DimIsoTkOK[p]++;
			  ev_2dimhit_allcut[p]++;
			}
		      }
		    }
		  }
		}
			
		if(is2DimDzOK && is2DimHLTFired && is2DimMassOK && is2DimIsoTkOK){
		  
		  //=======================  Hit Recovery ==============================================//
		  
		  Bool_t vtx_constrain=false;
		  
		  // if(  (fabs(muJetC_vtx_x)<10.0 && fabs(muJetC_vtx_y)<10.0 && fabs(muJetC_vtx_z)<20.0) &&
		  //   	 (fabs(muJetF_vtx_x)<10.0 && fabs(muJetF_vtx_y)<10.0 && fabs(muJetF_vtx_z)<20.0) &&
		  //   	 muJetC_mindisttrk<0.03 && muJetF_mindisttrk<0.03) vtx_constrain=true;
		  
		  //	    if( fabs(muJetC_vtx_z)<24.0 && fabs(muJetF_vtx_z)<24.0 && muJetC_mindisttrk<0.03 && muJetF_mindisttrk<0.03 ) vtx_constrain=true;
		  //	    if(muJetC_mindisttrk<0.3 && muJetF_mindisttrk<0.3 ) vtx_constrain=true;
		  vtx_constrain=true;
		  
		  
		  //		  if( (muJetChit[0]!=1&&muJetChit[1]!=1)||(muJetFhit[0]!=1&&muJetFhit[1]!=1) ){
			  
		  //		    if( (muJetChit[0]!=1&&muJetChit[1]!=1)&&(muJetFhit[0]!=1&&muJetFhit[1]!=1)){

		  if( (muJetChitgt[0]!=1&&muJetChitgt[1]!=1)||(muJetFhitgt[0]!=1&&muJetFhitgt[1]!=1) ){
			  
		    if( (muJetChitgt[0]!=1&&muJetChitgt[1]!=1)&&(muJetFhitgt[0]!=1&&muJetFhitgt[1]!=1)){
			    
		      bool recover_muJetC=false;
		      bool recover_muJetF=false;
			    
		      if(Detmu1jetC>0 && Detmu2jetC>0){
			for(int j=0;j<Detmu1jetC;j++){
			  if(mindist_mu1hit_muJetC[j]<0.03 && mindist_mu1hit_muJetC[j]>=0.0) recover_muJetC=true;
			}
			for(int j=0;j<Detmu2jetC;j++){
			  if(mindist_mu2hit_muJetC[j]<0.03 && mindist_mu2hit_muJetC[j]>=0.0) recover_muJetC=true;
			}
		      }
			    
		      if(Detmu1jetF>0 && Detmu2jetF>0){
			for(int j=0;j<Detmu1jetF;j++){
			  if(mindist_mu1hit_muJetF[j]<0.03 && mindist_mu1hit_muJetF[j]>=0.0) recover_muJetF=true;
			}
			for(int j=0;j<Detmu2jetC;j++){
			  if(mindist_mu2hit_muJetF[j]<0.03 && mindist_mu2hit_muJetF[j]>=0.0) recover_muJetF=true;
			}
		      }
		    
		      if(recover_muJetC && recover_muJetF && vtx_constrain) ev_2dimhit_recov2dim[p]++;
		      if(hitrecover_mj12_r005 && vtx_constrain) ev_2dimhit_recov2dim2[p]++;
		    }
		  
		  
		  
		    //		    if( (muJetChit[0]!=1&&muJetChit[1]!=1)&&(muJetFhit[0]==1||muJetFhit[1]==1)){
		    if( (muJetChitgt[0]!=1&&muJetChitgt[1]!=1)&&(muJetFhitgt[0]==1||muJetFhitgt[1]==1)){
		    
		      bool recover_muJetC=false;
		
		      if(Detmu1jetC>0 && Detmu2jetC>0){
			for(int j=0;j<Detmu1jetC;j++){
			  if(mindist_mu1hit_muJetC[j]<0.03 && mindist_mu1hit_muJetC[j]>=0.0) recover_muJetC=true;
			}
			for(int j=0;j<Detmu2jetC;j++){
			  if(mindist_mu2hit_muJetC[j]<0.03 && mindist_mu2hit_muJetC[j]>=0.0) recover_muJetC=true;
			}
		      }
		
		      if(recover_muJetC && vtx_constrain) ev_2dimhit_recovmuJetC[p]++;
		      if(hitrecover_mj1_r005==1 && vtx_constrain ) ev_2dimhit_recovmuJetC2[p]++;
		    }
	      
	      
		    //if( (muJetFhit[0]!=1&&muJetFhit[1]!=1)&&(muJetChit[0]==1||muJetChit[1]==1)){
		    if( (muJetFhitgt[0]!=1&&muJetFhitgt[1]!=1)&&(muJetChitgt[0]==1||muJetChitgt[1]==1)){
		
		      bool recover_muJetF=false;
		
		      if(Detmu1jetF>0 && Detmu2jetF>0){
			for(int j=0;j<Detmu1jetF;j++){
			  if(mindist_mu1hit_muJetF[j]<0.03 && mindist_mu1hit_muJetF[j]>=0.0) recover_muJetF=true;
			}
			for(int j=0;j<Detmu2jetF;j++){
			  if(mindist_mu2hit_muJetF[j]<0.03 && mindist_mu2hit_muJetF[j]>=0.0) recover_muJetF=true;
			}
		      }
		
		      if(recover_muJetF && vtx_constrain ) ev_2dimhit_recovmuJetF[p]++;
		      if(hitrecover_mj2_r005==1 && vtx_constrain ) ev_2dimhit_recovmuJetF2[p]++;
		

		    }
		  }
		}
	      }
	    }
	  }
	}
      }
    }




    ev_2dimhit_allcutrecov[p] = ev_2dimhit_allcut[p] + ev_2dimhit_recov2dim[p] +ev_2dimhit_recovmuJetC[p] + ev_2dimhit_recovmuJetF[p];
    ev_2dimhit_allcutrecov2[p] = ev_2dimhit_allcut[p] + ev_2dimhit_recov2dim2[p] +ev_2dimhit_recovmuJetC2[p] + ev_2dimhit_recovmuJetF2[p];

    ev_2dim_recov[p] =  ev_2dimhit_recov2dim[p] +ev_2dimhit_recovmuJetC[p] + ev_2dimhit_recovmuJetF[p];
    ev_2dim_recov2[p] =  ev_2dimhit_recov2dim2[p] +ev_2dimhit_recovmuJetC2[p] + ev_2dimhit_recovmuJetF2[p];
    
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
    std::cout<<"  Events with 2DimHLT                   "<<ev_is2DimHLTFired[p]<<"   reff   "<<ev_is2DimHLTFired[p]/ev_is2DimDzOK[p]<<endl;
    std::cout<<"  Events with 2DimMassOK                "<<ev_is2DimMassOK[p]<<"  reff   "<<ev_is2DimMassOK[p]/ev_is2DimHLTFired[p]<<endl;
    std::cout<<"  Events with 2DimIsoOK                 "<<ev_is2DimIsoTkOK[p]<<"   reff   "<<ev_is2DimIsoTkOK[p]/ev_is2DimMassOK[p]<<endl;
    std::cout<<"  ratio reco/gen                        "<<ev_is2DimIsoTkOK[p]/ev_4gmlxylzcut[p]<<" +/-  "<<sqrt( ((ev_is2DimIsoTkOK[p]/ev_4gmlxylzcut[p])*(1- (ev_is2DimIsoTkOK[p]/ev_4gmlxylzcut[p]) ))/ev_4gmlxylzcut[p])<<std::endl;
    std::cout<<"  ========================================================== "<<std::endl;
    std::cout<<"  ======================= HitRecovery MinimumDistance======= "<<std::endl;
    //    std::cout<<"  Events with allcuts Failhits                       "<<ev_2dimhit_allcut[p]<<std::endl;
    std::cout<<"  Events 2dimuons recovered (after allcuts)  "<<ev_2dimhit_recov2dim[p]<<std::endl;
    std::cout<<"  Events muJetC recovered  (after allcuts)   "<<ev_2dimhit_recovmuJetC[p]<<std::endl;
    std::cout<<"  Events muJetF recovered (after allcuts)    "<<ev_2dimhit_recovmuJetF[p]<<std::endl;
    std::cout<<"  Total events recovered                     "<<ev_2dim_recov[p]<<std::endl;
    //    std::cout<<"  ratio  reco/gen                               "<<ev_2dimhit_allcutrecov[p]/ev_4gmlxylzcut[p]<<std::endl;
    std::cout<<"  ===================== HitRecovery Bike Chain ============== "<<std::endl;
    std::cout<<"  Events 2dimuons recovered (after allcuts)  "<<ev_2dimhit_recov2dim2[p]<<std::endl;
    std::cout<<"  Events muJetC recovered  (after allcuts)   "<<ev_2dimhit_recovmuJetC2[p]<<std::endl;
    std::cout<<"  Events muJetF recovered (after allcuts)    "<<ev_2dimhit_recovmuJetF2[p]<<std::endl;
    std::cout<<"  Total events recovered                     "<<ev_2dim_recov2[p]<<std::endl;
    std::cout<<"  ========================================================== "<<std::endl;
    std::cout<<"  ========================================================== "<<std::endl;
    std::cout<<"  ==================  EVENT variables (after HitRecovery MinDistance) ============= "<<std::endl;
    std::cout<<"  Events with 2DimHitPix                     "<<ev_2dimhit[p]+ev_2dim_recov[p]<<"   reff  "<<ev_2dimhit[p]+ev_2dim_recov[p]/ev_2dimvtxok[p]<<std::endl;
    std::cout<<"  Events with 2DimDzOK                       "<<ev_is2DimDzOK[p]+ev_2dim_recov[p]<<"   reff   "<<(ev_is2DimDzOK[p]+ev_2dim_recov[p])/(ev_2dimhit[p]+ev_2dim_recov[p])<<endl;
    std::cout<<"  Events with 2DimHLT                        "<<ev_is2DimHLTFired[p]+ev_2dim_recov[p]<<"   reff   "<<(ev_is2DimHLTFired[p]+ev_2dim_recov[p])/(ev_is2DimDzOK[p]+ev_2dim_recov[p])<<endl;
    std::cout<<"  Events with 2DimMassOK                     "<<ev_is2DimMassOK[p]+ev_2dim_recov[p]<<"   reff   "<<(ev_is2DimMassOK[p]+ev_2dim_recov[p])/(ev_is2DimHLTFired[p]+ev_2dim_recov[p])<<endl;
    std::cout<<"  Events with 2DimIsoOK                      "<<ev_is2DimIsoTkOK[p]+ev_2dim_recov[p]<<"   reff   "<<(ev_is2DimIsoTkOK[p]+ev_2dim_recov[p])/(ev_is2DimMassOK[p]+ev_2dim_recov[p])<<endl;
    std::cout<<"  ratio reco/gen (MinDistance)                "<<ev_2dimhit_allcutrecov[p]/ev_4gmlxylzcut[p]<<std::endl;
    std::cout<<"  ==================  EVENT variables (after HitRecovery Bike Chain) ============= "<<std::endl;
    std::cout<<"  Events with 2DimHitPix                     "<<ev_2dimhit[p]+ev_2dim_recov2[p]<<"   reff  "<<ev_2dimhit[p]+ev_2dim_recov2[p]/ev_2dimvtxok[p]<<std::endl;
    std::cout<<"  Events with 2DimDzOK                       "<<ev_is2DimDzOK[p]+ev_2dim_recov2[p]<<"   reff   "<<(ev_is2DimDzOK[p]+ev_2dim_recov2[p])/(ev_2dimhit[p]+ev_2dim_recov2[p])<<endl;
    std::cout<<"  Events with 2DimHLT                        "<<ev_is2DimHLTFired[p]+ev_2dim_recov2[p]<<"   reff   "<<(ev_is2DimHLTFired[p]+ev_2dim_recov2[p])/(ev_is2DimDzOK[p]+ev_2dim_recov2[p])<<endl;
    std::cout<<"  Events with 2DimMassOK                     "<<ev_is2DimMassOK[p]+ev_2dim_recov2[p]<<"   reff   "<<(ev_is2DimMassOK[p]+ev_2dim_recov2[p])/(ev_is2DimHLTFired[p]+ev_2dim_recov2[p])<<endl;
    std::cout<<"  Events with 2DimIsoOK                      "<<ev_is2DimIsoTkOK[p]+ev_2dim_recov2[p]<<"   reff   "<<(ev_is2DimIsoTkOK[p]+ev_2dim_recov2[p])/(ev_is2DimMassOK[p]+ev_2dim_recov2[p])<<endl;




    Float_t eps_gen = ev_4gmlxylzcut[p]/(1.0*t->GetEntries());
    Float_t eps_full = ev_2dimhit_allcutrecov2[p]/(1.0*t->GetEntries());
    Float_t err_eps_gen = sqrt( (eps_gen*(1-eps_gen))/(1.0*t->GetEntries()));
    Float_t err_eps_full= sqrt( (eps_full*(1-eps_full))/(1.0*t->GetEntries()));
    Float_t err_ratio = (eps_full/eps_gen)*sqrt(pow(err_eps_full/eps_full,2)+pow(err_eps_gen/eps_gen,2));

    std::cout<<"  ratio epsilon_gen (Bike Chain)        %    "<<(eps_gen)*100.0<<" +/-  "<<(err_eps_gen)*100.0<<std::endl;
    std::cout<<"  ratio epsilon_full (Bike Chain)       %    "<<(eps_full)*100.0<<" +/-  "<<(err_eps_full)*100.0<<std::endl;
    std::cout<<"  ratio reco/gen (Bike Chain)                "<<eps_full/eps_gen<<" +/-  "<<err_ratio<<std::endl;
    std::cout<<"  Finish sample   "<<p<<std::endl;
    std::cout<<"                                                                      "<<std::endl;
    std::cout<<"                                                                      "<<std::endl;
    std::cout<<"                                                                      "<<std::endl;
    
  }

  //  Float_t ctau[6]={0.0,0.1,0.5,1.0,3.0,5.0};
  Float_t ctau[6]={0.0,0.2,0.5,1.0,3.0,5.0};

  Float_t eff_mD0250[6]={0.0};
  Float_t erreff_mD0250[6]={0.0};
  Float_t eff_mD0250recov[6]={0.0};
  Float_t erreff_mD0250recov[6]={0.0};

  // Float_t eff_mD2000[7]={0.0};
  // Float_t erreff_mD2000[7]={0.0};
  // Float_t eff_mD2000pgen[7]={0.0};
  // Float_t erreff_mD2000pgen[7]={0.0};


  for(int k=0;k<6;k++){
    eff_mD0250[k] = ev_is2DimIsoTkOK[k]/ev_4gmlxylzcut[k];
    erreff_mD0250[k] = sqrt( (eff_mD0250[k]*(1-eff_mD0250[k]))/(ev_4gmlxylzcut[k]*1.0));
    
    eff_mD0250recov[k] =  (ev_is2DimIsoTkOK[k]+ev_2dim_recov2[k])/ev_4gmlxylzcut[k];
    erreff_mD0250recov[k] = sqrt( (eff_mD0250recov[k]*(1-eff_mD0250recov[k]))/(ev_4gmlxylzcut[k]*1.0));
  }
  
  // for(int k=0;k<7;k++){
  //   eff_mD2000[k] = ev_is2DimIsoTkOK[k+7]/ev_4gmlxylzcut[k+7];
  //   erreff_mD2000[k] = sqrt( (eff_mD2000[k]*(1-eff_mD2000[k]))/(ev_4gmlxylzcut[k+7]*1.0));

  //   eff_mD2000recov[k] =  ev_2dimhit_allcutplusgen[k+7]/ev_4gmlxylzcut[k+7];
  //   erreff_mD2000recov[k] = sqrt( (eff_mD2000recov[k]*(1-eff_mD2000recov[k]))/(ev_4gmlxylzcut[k+7]*1.0));
  // }

  TGraphErrors *gr_eff_mD0250 = new TGraphErrors(6,ctau,eff_mD0250,0,erreff_mD0250);
  TGraphErrors *gr_eff_mD0250recov = new TGraphErrors(6,ctau,eff_mD0250recov,0,erreff_mD0250recov);

  // TGraphErrors *gr_eff_mD2000 = new TGraphErrors(7,ctau,eff_mD2000,0,erreff_mD2000);
  // TGraphErrors *gr_eff_mD2000recov = new TGraphErrors(7,ctau,eff_mD2000recov,0,erreff_mD2000recov);

  TLegend *leg = new TLegend(0.2,0.25,0.80,0.5);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetTextSize(0.04);
  leg->AddEntry(gr_eff_mD0250,"m_{#gamma D}=0.25GeV, #epsilon_{rec}/#alpha_{gen} = rec_{cuts}/All","PL");
  leg->AddEntry(gr_eff_mD0250recov,"m_{#gamma D}=0.25GeV, #epsilon_{rec}/#alpha_{gen} = (rec_{cuts}+HitRecovery)/All ","PL");
  //  leg->AddEntry(gr_eff_mD2000,"m_{#gamma D}=2.0GeV, #epsilon_{rec} = rec_{cuts}/All","PL");
  //  leg->AddEntry(gr_eff_mD2000recov,"m_{#gamma D}=2.0GeV, #epsilon_{rec} = (rec_{cuts}+gen_{cuts})/All ","PL");
  
  
  TH2F *dummy3 = new TH2F("","",100,-0.2,5.2,100,0.0,1.0);
  
  TCanvas *c = new TCanvas("c","c",700,500);
  dummy3->GetXaxis()->SetTitle("c#tau [mm]");
  dummy3->GetYaxis()->SetTitle("#epsilon_{rec}/#alpha_{gen}");
  dummy3->Draw();
  gr_eff_mD0250->SetLineWidth(3);
  gr_eff_mD0250recov->SetLineWidth(3);
  gr_eff_mD0250->SetLineColor(1);
  gr_eff_mD0250->SetLineStyle(2);
  gr_eff_mD0250recov->SetLineColor(1);
  gr_eff_mD0250->SetMarkerColor(1);
  gr_eff_mD0250recov->SetMarkerColor(1);
  gr_eff_mD0250recov->SetLineStyle(1);
  gr_eff_mD0250->Draw("PL");
  gr_eff_mD0250recov->Draw("PLsame");

  // gr_eff_mD2000->SetLineWidth(4);
  // gr_eff_mD2000->SetLineColor(4);
  // gr_eff_mD2000->SetMarkerColor(4);

  // gr_eff_mD2000pgen->SetLineWidth(4);
  // gr_eff_mD2000pgen->SetLineColor(4);
  // gr_eff_mD2000pgen->SetMarkerColor(4);
  // gr_eff_mD2000pgen->SetLineStyle(2);
  // gr_eff_mD2000->Draw("PLsame");
  // gr_eff_mD2000pgen->Draw("PLsame");

   leg->Draw("same");

   if(analysisr1){
       c->SaveAs("eff_mD_r1.pdf","recreate");
       c->SaveAs("eff_mD_r1.png","recreate");
   }
   else{
       c->SaveAs("eff_mD_r2.pdf","recreate");
       c->SaveAs("eff_mD_r2.png","recreate");
   }     



//     Float_t ctau[4]={0.2,0.5,2.0,5.0};

//     Float_t ctau3[4]={0.0,0.2,2.0,5.0};
//     Float_t ctau4[3]={0.0,0.5,5.0};

//     Float_t ctau2[7]={0.0,0.2,0.5,1.0,2.0,3.0,5.0};
//     Float_t ctau2l[10]={0.0,0.2,0.5,1.0,2.0,3.0,5.0,10.0,20.0,100.0};

//     Float_t ctau5[4]={0.0,0.5,2.0,5.0};
//     Float_t ctau6[6]={0.0,0.2,0.5,2.0,10.0,20.0};

  
//     Float_t eff_mD0400[4]={0.0};
//     Float_t erreff_mD0400[4]={0.0};

//     Float_t eff_mD0400_gt[4]={0.0};
//     Float_t erreff_mD0400_gt[4]={0.0};

//     Float_t eff_mD0400_fvtx[4]={0.0};
//     Float_t erreff_mD0400_fvtx[4]={0.0};

//     Float_t eff_mD0400_allcut[4]={0.0};
//     Float_t erreff_mD0400_allcut[4]={0.0};

//     Float_t eff_mD0400_allcutrecov[4]={0.0};
//     Float_t erreff_mD0400_allcutrecov[4]={0.0};

//     Float_t eff_mD0400_allcutrecov2[4]={0.0};
//     Float_t erreff_mD0400_allcutrecov2[4]={0.0};

//     Float_t eff_mD0400_final[4]={0.0};
//     Float_t erreff_mD0400_final[4]={0.0};


//     Float_t eff_mD0850[3]={0.0};
//     Float_t erreff_mD0850[3]={0.0};

//     Float_t eff_mD0850_gt[3]={0.0};
//     Float_t erreff_mD0850_gt[3]={0.0};

//     Float_t eff_mD0850_fvtx[3]={0.0};
//     Float_t erreff_mD0850_fvtx[3]={0.0};

//     Float_t eff_mD0850_allcut[3]={0.0};
//     Float_t erreff_mD0850_allcut[3]={0.0};

//     Float_t eff_mD0850_allcutrecov[3]={0.0};
//     Float_t erreff_mD0850_allcutrecov[3]={0.0};

//     Float_t eff_mD0850_final[3]={0.0};
//     Float_t erreff_mD0850_final[3]={0.0};




//     Float_t eff_mD0700[4]={0.0};
//     Float_t erreff_mD0700[4]={0.0};

//     Float_t eff_mD0700_gt[4]={0.0};
//     Float_t erreff_mD0700_gt[4]={0.0};

//     Float_t eff_mD0700_fvtx[4]={0.0};
//     Float_t erreff_mD0700_fvtx[4]={0.0};

//     Float_t eff_mD0700_allcut[4]={0.0};
//     Float_t erreff_mD0700_allcut[4]={0.0};

//     Float_t eff_mD0700_allcutrecov[4]={0.0};
//     Float_t erreff_mD0700_allcutrecov[4]={0.0};

//     Float_t eff_mD0700_final[4]={0.0};
//     Float_t erreff_mD0700_final[4]={0.0};




//     Float_t eff_mD1000[4]={0.0};
//     Float_t erreff_mD1000[4]={0.0};

//     Float_t eff_mD1000_gt[4]={0.0};
//     Float_t erreff_mD1000_gt[4]={0.0};

//     Float_t eff_mD1000_fvtx[4]={0.0};
//     Float_t erreff_mD1000_fvtx[4]={0.0};

//     Float_t eff_mD1000_allcut[4]={0.0};
//     Float_t erreff_mD1000_allcut[4]={0.0};

//     Float_t eff_mD1000_allcutrecov[4]={0.0};
//     Float_t erreff_mD1000_allcutrecov[4]={0.0};

//     Float_t eff_mD1000_final[4]={0.0};
//     Float_t erreff_mD1000_final[4]={0.0};



//     Float_t eff_mD1500[4]={0.0};
//     Float_t erreff_mD1500[4]={0.0};

//     Float_t eff_mD1500_gt[4]={0.0};
//     Float_t erreff_mD1500_gt[4]={0.0};

//     Float_t eff_mD1500_fvtx[4]={0.0};
//     Float_t erreff_mD1500_fvtx[4]={0.0};

//     Float_t eff_mD1500_allcut[4]={0.0};
//     Float_t erreff_mD1500_allcut[4]={0.0};

//     Float_t eff_mD1500_allcutrecov[4]={0.0};
//     Float_t erreff_mD1500_allcutrecov[4]={0.0};

//     Float_t eff_mD1500_final[4]={0.0};
//     Float_t erreff_mD1500_final[4]={0.0};



//     Float_t eff_mD2000[4]={0.0};
//     Float_t erreff_mD2000[4]={0.0};

//     Float_t eff_mD2000_gt[4]={0.0};
//     Float_t erreff_mD2000_gt[4]={0.0};

//     Float_t eff_mD2000_fvtx[4]={0.0};
//     Float_t erreff_mD2000_fvtx[4]={0.0};

//     Float_t eff_mD2000_allcut[4]={0.0};
//     Float_t erreff_mD2000_allcut[4]={0.0};

//     Float_t eff_mD2000_allcutrecov[4]={0.0};
//     Float_t erreff_mD2000_allcutrecov[4]={0.0};

//     Float_t eff_mD2000_final[6]={0.0};
//     Float_t erreff_mD2000_final[6]={0.0};




//     Float_t eff_mD0250[7]={0.0};
//     Float_t erreff_mD0250[7]={0.0};

//     Float_t eff_mD0250_gt[7]={0.0};
//     Float_t erreff_mD0250_gt[7]={0.0};

//     Float_t eff_mD0250_fvtx[7]={0.0};
//     Float_t erreff_mD0250_fvtx[7]={0.0};


//     Float_t eff_mD0250_allcut[7]={0.0};

//     Float_t erreff_mD0250_allcut1[7]={0.0};
//     Float_t erreff_mD0250_allcut2[7]={0.0};
//     Float_t erreff_mD0250_allcut[7]={0.0};


//     Float_t eff_mD0250_allcutrecov[7]={0.0};
//     Float_t erreff_mD0250_allcutrecov[7]={0.0};

//     Float_t eff_mD0250_allcutrecov2[7]={0.0};

//     Float_t erreff_mD0250_allcutrecov21[7]={0.0};
//     Float_t erreff_mD0250_allcutrecov22[7]={0.0};
//     Float_t erreff_mD0250_allcutrecov2[7]={0.0};


//     Float_t eff_mD0250_final[7]={0.0};
//     Float_t eff_mD0250_final2[20]={0.0};

//     Float_t erreff_mD0250_final1[7]={0.0};
//     Float_t erreff_mD0250_final2[20]={0.0};
//     Float_t erreff_mD0250_final[7]={0.0};

    

//     Float_t eff_ctau0_final[5];
//     Float_t eff_ctau02_final[4];
//     Float_t eff_ctau05_final[7];
//     Float_t eff_ctau2_final[6];
//     Float_t eff_ctau5_final[6];

//     Float_t erreff_ctau0_final[5];
//     Float_t erreff_ctau02_final[4];
//     Float_t erreff_ctau05_final[7];
//     Float_t erreff_ctau2_final[6];
//     Float_t erreff_ctau5_final[6];

//     Float_t mass_ctau0[5]={0.25,0.7,0.85,1.0,2.0};
//     eff_ctau0_final[0] = ev_2dimhit_allcutrecov2[4]/ev_all[4];
//     erreff_ctau0_final[0] = sqrt( (eff_ctau0_final[0]*(1-eff_ctau0_final[0]))/(ev_all[4]*1.0));
//     eff_ctau0_final[1] = ev_2dimhit_allcutrecov2[11]/ev_all[11];
//     erreff_ctau0_final[1] = sqrt( (eff_ctau0_final[1]*(1-eff_ctau0_final[1]))/(ev_all[11]*1.0));
//     eff_ctau0_final[2] = ev_2dimhit_allcutrecov2[15]/ev_all[15];
//     erreff_ctau0_final[2] = sqrt( (eff_ctau0_final[2]*(1-eff_ctau0_final[2]))/(ev_all[15]*1.0));
//     eff_ctau0_final[3] = ev_2dimhit_allcutrecov2[18]/ev_all[18];
//     erreff_ctau0_final[3] = sqrt( (eff_ctau0_final[2]*(1-eff_ctau0_final[2]))/(ev_all[18]*1.0));
//     eff_ctau0_final[4] = ev_2dimhit_allcutrecov2[26]/ev_all[26];
//     erreff_ctau0_final[4] = sqrt( (eff_ctau0_final[2]*(1-eff_ctau0_final[2]))/(ev_all[26]*1.0));

//     Float_t mass_ctau02[4]={0.25,0.4,1.5,2.0};
//     eff_ctau02_final[0] = ev_2dimhit_allcutrecov2[5]/ev_all[5];
//     erreff_ctau02_final[0] = sqrt( (eff_ctau02_final[0]*(1-eff_ctau02_final[0]))/(ev_all[5]*1.0));
//     eff_ctau02_final[1] = ev_2dimhit_allcutrecov2[0]/ev_all[0];
//     erreff_ctau02_final[1] = sqrt( (eff_ctau02_final[1]*(1-eff_ctau02_final[1]))/(ev_all[0]*1.0));
//     eff_ctau02_final[2] = ev_2dimhit_allcutrecov2[22]/ev_all[22];
//     erreff_ctau02_final[2] = sqrt( (eff_ctau02_final[2]*(1-eff_ctau02_final[2]))/(ev_all[22]*1.0));
//     eff_ctau02_final[3] = ev_2dimhit_allcutrecov2[27]/ev_all[27];
//     erreff_ctau02_final[3] = sqrt( (eff_ctau02_final[3]*(1-eff_ctau02_final[3]))/(ev_all[27]*1.0));


//     Float_t mass_ctau05[7]={0.25,0.4,0.7,0.85,1.0,1.5,2.0};
//     eff_ctau05_final[0] = ev_2dimhit_allcutrecov2[6]/ev_all[6];
//     erreff_ctau05_final[0] = sqrt( (eff_ctau05_final[0]*(1-eff_ctau05_final[0]))/(ev_all[6]*1.0));
//     eff_ctau05_final[1] = ev_2dimhit_allcutrecov2[1]/ev_all[1];
//     erreff_ctau05_final[1] = sqrt( (eff_ctau05_final[1]*(1-eff_ctau05_final[1]))/(ev_all[1]*1.0));
//     eff_ctau05_final[2] = ev_2dimhit_allcutrecov2[12]/ev_all[12];
//     erreff_ctau05_final[2] = sqrt( (eff_ctau05_final[2]*(1-eff_ctau05_final[2]))/(ev_all[12]*1.0));
//     eff_ctau05_final[3] = ev_2dimhit_allcutrecov2[16]/ev_all[16];
//     erreff_ctau05_final[3] = sqrt( (eff_ctau05_final[3]*(1-eff_ctau05_final[3]))/(ev_all[16]*1.0));
//     eff_ctau05_final[4] = ev_2dimhit_allcutrecov2[19]/ev_all[19];
//     erreff_ctau05_final[4] = sqrt( (eff_ctau05_final[4]*(1-eff_ctau05_final[4]))/(ev_all[19]*1.0));
//     eff_ctau05_final[5] = ev_2dimhit_allcutrecov2[23]/ev_all[23];
//     erreff_ctau05_final[5] = sqrt( (eff_ctau05_final[5]*(1-eff_ctau05_final[5]))/(ev_all[23]*1.0));
//     eff_ctau05_final[6] = ev_2dimhit_allcutrecov2[28]/ev_all[28];
//     erreff_ctau05_final[6] = sqrt( (eff_ctau05_final[6]*(1-eff_ctau05_final[6]))/(ev_all[28]*1.0));

//     Float_t mass_ctau2[6]={0.25,0.4,0.7,1.0,1.5,2.0};
//     eff_ctau2_final[0] = ev_2dimhit_allcutrecov2[8]/ev_all[8];
//     erreff_ctau2_final[0] = sqrt( (eff_ctau2_final[0]*(1-eff_ctau2_final[0]))/(ev_all[8]*1.0));
//     eff_ctau2_final[1] = ev_2dimhit_allcutrecov2[2]/ev_all[2];
//     erreff_ctau2_final[1] = sqrt( (eff_ctau2_final[1]*(1-eff_ctau2_final[1]))/(ev_all[2]*1.0));
//     eff_ctau2_final[2] = ev_2dimhit_allcutrecov2[13]/ev_all[13];
//     erreff_ctau2_final[2] = sqrt( (eff_ctau2_final[2]*(1-eff_ctau2_final[2]))/(ev_all[13]*1.0));
//     eff_ctau2_final[3] = ev_2dimhit_allcutrecov2[20]/ev_all[20];
//     erreff_ctau2_final[3] = sqrt( (eff_ctau2_final[3]*(1-eff_ctau2_final[3]))/(ev_all[20]*1.0));
//     eff_ctau2_final[4] = ev_2dimhit_allcutrecov2[24]/ev_all[24];
//     erreff_ctau2_final[4] = sqrt( (eff_ctau2_final[4]*(1-eff_ctau2_final[4]))/(ev_all[24]*1.0));
//     eff_ctau2_final[5] = ev_2dimhit_allcutrecov2[29]/ev_all[29];
//     erreff_ctau2_final[5] = sqrt( (eff_ctau2_final[5]*(1-eff_ctau2_final[5]))/(ev_all[24]*1.0));

//     Float_t mass_ctau5[6]={0.25,0.4,0.7,0.85,1.0,1.5};
//     eff_ctau5_final[0] = ev_2dimhit_allcutrecov2[10]/ev_all[10];
//     erreff_ctau5_final[0] = sqrt( (eff_ctau5_final[0]*(1-eff_ctau5_final[0]))/(ev_all[10]*1.0));
//     eff_ctau5_final[1] = ev_2dimhit_allcutrecov2[3]/ev_all[3];
//     erreff_ctau5_final[1] = sqrt( (eff_ctau5_final[1]*(1-eff_ctau5_final[1]))/(ev_all[3]*1.0));
//     eff_ctau5_final[2] = ev_2dimhit_allcutrecov2[14]/ev_all[14];
//     erreff_ctau5_final[2] = sqrt( (eff_ctau5_final[2]*(1-eff_ctau5_final[2]))/(ev_all[14]*1.0));
//     eff_ctau5_final[3] = ev_2dimhit_allcutrecov2[17]/ev_all[17];
//     erreff_ctau5_final[3] = sqrt( (eff_ctau5_final[3]*(1-eff_ctau5_final[3]))/(ev_all[17]*1.0));
//     eff_ctau5_final[4] = ev_2dimhit_allcutrecov2[21]/ev_all[21];
//     erreff_ctau5_final[4] = sqrt( (eff_ctau5_final[4]*(1-eff_ctau5_final[4]))/(ev_all[21]*1.0));
//     eff_ctau5_final[5] = ev_2dimhit_allcutrecov2[25]/ev_all[25];
//     erreff_ctau5_final[5] = sqrt( (eff_ctau5_final[5]*(1-eff_ctau5_final[5]))/(ev_all[25]*1.0));



//     TGraphErrors *gr_eff_ctau0_final = new TGraphErrors(5,mass_ctau0,eff_ctau0_final,0,erreff_ctau0_final);
//     TGraphErrors *gr_eff_ctau02_final = new TGraphErrors(4,mass_ctau02,eff_ctau02_final,0,erreff_ctau02_final);
//     TGraphErrors *gr_eff_ctau05_final = new TGraphErrors(7,mass_ctau05,eff_ctau05_final,0,erreff_ctau05_final);
//     TGraphErrors *gr_eff_ctau2_final = new TGraphErrors(6,mass_ctau2,eff_ctau2_final,0,erreff_ctau2_final);
//     TGraphErrors *gr_eff_ctau5_final = new TGraphErrors(6,mass_ctau5,eff_ctau5_final,0,erreff_ctau5_final);
     

//     TLegend *leg222 = new TLegend(0.4,0.15,0.8,0.6);
//     leg222->SetBorderSize(0);
//     leg222->SetFillColor(0);
//     leg222->SetTextSize(0.042);
//     leg222->AddEntry(gr_eff_ctau0_final,"c#tau_{#gamma D}=0.0 mm ","PL");
//     leg222->AddEntry(gr_eff_ctau02_final,"c#tau_{#gamma D}=0.2 mm ","PL");
//     leg222->AddEntry(gr_eff_ctau05_final,"c#tau_{#gamma D}=0.5 mm ","PL");
//     leg222->AddEntry(gr_eff_ctau2_final,"c#tau_{#gamma D}=2.0 mm ","PL");
//     leg222->AddEntry(gr_eff_ctau5_final,"c#tau_{#gamma D}=5.0 mm ","PL");
    

//      TH2F *dummy444 = new TH2F("","",100,-0.2,2.2,100,0.0,0.12);
//      // TCanvas *c444 = new TCanvas("c444","c444",700,500);
//      // dummy444->GetXaxis()->SetTitle("mass [GeV]");
//      // dummy444->GetYaxis()->SetTitle("#epsilon_{rec}=N_{rec}/N_{tot}");
//      // dummy444->Draw();
//      // gr_eff_ctau0_final->SetLineColor(2);
//      // gr_eff_ctau0_final->SetMarkerColor(2);
//      // gr_eff_ctau0_final->SetLineWidth(2);
//      // gr_eff_ctau0_final->Draw("PLsame");

//      // gr_eff_ctau02_final->SetLineColor(3);
//      // gr_eff_ctau02_final->SetMarkerColor(3);
//      // gr_eff_ctau02_final->SetLineWidth(2);
//      // gr_eff_ctau02_final->Draw("PLsame");

//      // gr_eff_ctau05_final->SetLineColor(4);
//      // gr_eff_ctau05_final->SetMarkerColor(4);
//      // gr_eff_ctau05_final->SetLineWidth(2);
//      // gr_eff_ctau05_final->Draw("PLsame");

//      // gr_eff_ctau2_final->SetLineColor(5);
//      // gr_eff_ctau2_final->SetMarkerColor(5);
//      // gr_eff_ctau2_final->SetLineWidth(2);
//      // gr_eff_ctau2_final->Draw("PLsame");

//      // gr_eff_ctau5_final->SetLineColor(6);
//      // gr_eff_ctau5_final->SetMarkerColor(6);
//      // gr_eff_ctau5_final->SetLineWidth(2);
//      // gr_eff_ctau5_final->Draw("PLsame");

//      // leg222->Draw("same");
//      // c444->SaveAs("eff_final_mass.pdf","recreate");



//     for(int k=0;k<4;k++){


//       eff_mD0400[k] = ev_2dimhit[k]/ev_4gmlxylzcut[k];
//       erreff_mD0400[k] = sqrt( (eff_mD0400[k]*(1-eff_mD0400[k]))/(ev_4gmlxylzcut[k]*1.0));

//       eff_mD0400_gt[k] = ev_2dimhitgt[k]/ev_4gmlxylzcut[k];
//       erreff_mD0400_gt[k] = sqrt( (eff_mD0400_gt[k]*(1-eff_mD0400_gt[k]))/(ev_4gmlxylzcut[k]*1.0));

//       eff_mD0400_fvtx[k] = ev_2dimhitfvtx[k]/ev_4gmlxylzcut[k];
//       erreff_mD0400_fvtx[k] = sqrt( (eff_mD0400_fvtx[k]*(1-eff_mD0400_fvtx[k]))/(ev_4gmlxylzcut[k]*1.0));

//       eff_mD0400_allcut[k] = ev_2dimhit_allcut[k]/ev_4gmlxylzcut[k];
//       erreff_mD0400_allcut[k] = sqrt( (eff_mD0400_allcut[k]*(1-eff_mD0400_allcut[k]))/(ev_4gmlxylzcut[k]*1.0));

//       eff_mD0400_allcutrecov[k] = ev_2dimhit_allcutrecov[k]/ev_4gmlxylzcut[k];
//       erreff_mD0400_allcutrecov[k] = sqrt( (eff_mD0400_allcutrecov[k]*(1-eff_mD0400_allcutrecov[k]))/(ev_4gmlxylzcut[k]*1.0));


//       eff_mD0400_allcutrecov2[k] = ev_2dimhit_allcutrecov2[k]/ev_4gmlxylzcut[k];
//       erreff_mD0400_allcutrecov2[k] = sqrt( (eff_mD0400_allcutrecov2[k]*(1-eff_mD0400_allcutrecov2[k]))/(ev_4gmlxylzcut[k]*1.0));

//       eff_mD0400_final[k] = ev_2dimhit_allcutrecov2[k]/ev_all[k];
//       erreff_mD0400_final[k] = sqrt( (eff_mD0400_final[k]*(1-eff_mD0400_final[k]))/(ev_all[k]*1.0));

//       if(k==0) cout<<" mD0400   "<< eff_mD0400_final[k]<<endl;


//      eff_mD0700[k] = ev_2dimhit[k+11]/ev_4gmlxylzcut[k+11];
//      erreff_mD0700[k] = sqrt( (eff_mD0700[k]*(1-eff_mD0700[k]))/(ev_4gmlxylzcut[k+11]*1.0));

//      eff_mD0700_gt[k] = ev_2dimhitgt[k+11]/ev_4gmlxylzcut[k+11];
//      erreff_mD0700_gt[k] = sqrt( (eff_mD0700_gt[k]*(1-eff_mD0700_gt[k]))/(ev_4gmlxylzcut[k+11]*1.0));

//      eff_mD0700_fvtx[k] = ev_2dimhitfvtx[k+11]/ev_4gmlxylzcut[k+11];
//      erreff_mD0700_fvtx[k] = sqrt( (eff_mD0700_fvtx[k]*(1-eff_mD0700_fvtx[k]))/(ev_4gmlxylzcut[k+11]*1.0));

//      eff_mD0700_allcut[k] = ev_2dimhit_allcut[k+11]/ev_4gmlxylzcut[k+11];
//      erreff_mD0700_allcut[k] = sqrt( (eff_mD0700_allcut[k]*(1-eff_mD0700_allcut[k]))/(ev_4gmlxylzcut[k+11]*1.0));

//      eff_mD0700_allcutrecov[k] = ev_2dimhit_allcutrecov[k+11]/ev_4gmlxylzcut[k+11];
//      erreff_mD0700_allcutrecov[k] = sqrt( (eff_mD0700_allcutrecov[k]*(1-eff_mD0700_allcutrecov[k]))/(ev_4gmlxylzcut[k+11]*1.0));

//      eff_mD0700_final[k] = ev_2dimhit_allcutrecov2[k+11]/ev_all[k+11];
//      erreff_mD0700_final[k] = sqrt( (eff_mD0700_final[k]*(1-eff_mD0700_final[k]))/(ev_all[k+11]*1.0));

//       if(k==0) cout<<" mD0700   "<< eff_mD0700_final[k]<<endl;


//      eff_mD1000[k] = ev_2dimhit[k+18]/ev_4gmlxylzcut[k+18];
//      erreff_mD1000[k] = sqrt( (eff_mD1000[k]*(1-eff_mD1000[k]))/(ev_4gmlxylzcut[k+18]*1.0));

//      eff_mD1000_gt[k] = ev_2dimhitgt[k+18]/ev_4gmlxylzcut[k+18];
//      erreff_mD1000_gt[k] = sqrt( (eff_mD1000_gt[k]*(1-eff_mD1000_gt[k]))/(ev_4gmlxylzcut[k+18]*1.0));

//      eff_mD1000_fvtx[k] = ev_2dimhitfvtx[k+18]/ev_4gmlxylzcut[k+18];
//      erreff_mD1000_fvtx[k] = sqrt( (eff_mD1000_fvtx[k]*(1-eff_mD1000_fvtx[k]))/(ev_4gmlxylzcut[k+18]*1.0));

//      eff_mD1000_allcut[k] = ev_2dimhit_allcut[k+18]/ev_4gmlxylzcut[k+18];
//      erreff_mD1000_allcut[k] = sqrt( (eff_mD1000_allcut[k]*(1-eff_mD1000_allcut[k]))/(ev_4gmlxylzcut[k+18]*1.0));

//      eff_mD1000_allcutrecov[k] = ev_2dimhit_allcutrecov[k+18]/ev_4gmlxylzcut[k+18];
//      erreff_mD1000_allcutrecov[k] = sqrt( (eff_mD1000_allcutrecov[k]*(1-eff_mD1000_allcutrecov[k]))/(ev_4gmlxylzcut[k+18]*1.0));

//      eff_mD1000_final[k] = ev_2dimhit_allcutrecov2[k+18]/ev_all[k+18];
//      erreff_mD1000_final[k] = sqrt( (eff_mD1000_final[k]*(1-eff_mD1000_final[k]))/(ev_all[k+18]*1.0));


//       if(k==0) cout<<" mD1000   "<< eff_mD1000_final[k]<<endl;


//      eff_mD1500[k] = ev_2dimhit[k+22]/ev_4gmlxylzcut[k+22];
//      erreff_mD1500[k] = sqrt( (eff_mD1500[k]*(1-eff_mD1500[k]))/(ev_4gmlxylzcut[k+22]*1.0));

//      eff_mD1500_gt[k] = ev_2dimhitgt[k+22]/ev_4gmlxylzcut[k+22];
//      erreff_mD1500_gt[k] = sqrt( (eff_mD1500_gt[k]*(1-eff_mD1500_gt[k]))/(ev_4gmlxylzcut[k+22]*1.0));

//      eff_mD1500_fvtx[k] = ev_2dimhitfvtx[k+22]/ev_4gmlxylzcut[k+22];
//      erreff_mD1500_fvtx[k] = sqrt( (eff_mD1500_fvtx[k]*(1-eff_mD1500_fvtx[k]))/(ev_4gmlxylzcut[k+22]*1.0));

//      eff_mD1500_allcut[k] = ev_2dimhit_allcut[k+22]/ev_4gmlxylzcut[k+22];
//      erreff_mD1500_allcut[k] = sqrt( (eff_mD1500_allcut[k]*(1-eff_mD1500_allcut[k]))/(ev_4gmlxylzcut[k+22]*1.0));

//      eff_mD1500_allcutrecov[k] = ev_2dimhit_allcutrecov[k+22]/ev_4gmlxylzcut[k+22];
//      erreff_mD1500_allcutrecov[k] = sqrt( (eff_mD1500_allcutrecov[k]*(1-eff_mD1500_allcutrecov[k]))/(ev_4gmlxylzcut[k+22]*1.0));

//      eff_mD1500_final[k] = ev_2dimhit_allcutrecov2[k+22]/ev_all[k+22];
//      erreff_mD1500_final[k] = sqrt( (eff_mD1500_final[k]*(1-eff_mD1500_final[k]))/(ev_all[k+22]*1.0));


//      if(k==0) cout<<" mD1500   "<< eff_mD1500_final[k]<<endl;


//      eff_mD2000[k] = ev_2dimhit[k+26]/ev_4gmlxylzcut[k+26];
//      erreff_mD2000[k] = sqrt( (eff_mD2000[k]*(1-eff_mD2000[k]))/(ev_4gmlxylzcut[k+26]*1.0));

//      eff_mD2000_gt[k] = ev_2dimhitgt[k+26]/ev_4gmlxylzcut[k+26];
//      erreff_mD2000_gt[k] = sqrt( (eff_mD2000_gt[k]*(1-eff_mD2000_gt[k]))/(ev_4gmlxylzcut[k+26]*1.0));

//      eff_mD2000_fvtx[k] = ev_2dimhitfvtx[k+26]/ev_4gmlxylzcut[k+26];
//      erreff_mD2000_fvtx[k] = sqrt( (eff_mD2000_fvtx[k]*(1-eff_mD2000_fvtx[k]))/(ev_4gmlxylzcut[k+26]*1.0));

//      eff_mD2000_allcut[k] = ev_2dimhit_allcut[k+26]/ev_4gmlxylzcut[k+26];
//      erreff_mD2000_allcut[k] = sqrt( (eff_mD2000_allcut[k]*(1-eff_mD2000_allcut[k]))/(ev_4gmlxylzcut[k+26]*1.0));

//      eff_mD2000_allcutrecov[k] = ev_2dimhit_allcutrecov[k+26]/ev_4gmlxylzcut[k+26];
//      erreff_mD2000_allcutrecov[k] = sqrt( (eff_mD2000_allcutrecov[k]*(1-eff_mD2000_allcutrecov[k]))/(ev_4gmlxylzcut[k+26]*1.0));

//      eff_mD2000_final[k] = ev_2dimhit_allcutrecov2[k+26]/ev_all[k+26];
//      erreff_mD2000_final[k] = sqrt( (eff_mD2000_final[k]*(1-eff_mD2000_final[k]))/(ev_all[k+26]*1.0));

//      if(k==0) cout<<" mD2000   "<< eff_mD2000_final[k]<<endl;


//     }


//     eff_mD2000_final[4] = ev_2dimhit_allcutrecov2[35]/ev_all[35];
//     erreff_mD2000_final[4] = sqrt( (eff_mD2000_final[4]*(1-eff_mD2000_final[4]))/(ev_all[35]*1.0));

//     eff_mD2000_final[5] = ev_2dimhit_allcutrecov2[36]/ev_all[36];
//     erreff_mD2000_final[5] = sqrt( (eff_mD2000_final[5]*(1-eff_mD2000_final[5]))/(ev_all[36]*1.0));


//     for(int k=0;k<3;k++){
//       eff_mD0850[k] = ev_2dimhit[k+15]/ev_4gmlxylzcut[k+15];
//       erreff_mD0850[k] = sqrt( (eff_mD0850[k]*(1-eff_mD0850[k]))/(ev_4gmlxylzcut[k+15]*1.0));

//       eff_mD0850_gt[k] = ev_2dimhitgt[k+15]/ev_4gmlxylzcut[k+15];
//       erreff_mD0850_gt[k] = sqrt( (eff_mD0850_gt[k]*(1-eff_mD0850_gt[k]))/(ev_4gmlxylzcut[k+15]*1.0));

//       eff_mD0850_fvtx[k] = ev_2dimhitfvtx[k+15]/ev_4gmlxylzcut[k+15];
//       erreff_mD0850_fvtx[k] = sqrt( (eff_mD0850_fvtx[k]*(1-eff_mD0850_fvtx[k]))/(ev_4gmlxylzcut[k+15]*1.0));

//       eff_mD0850_allcut[k] = ev_2dimhit_allcut[k+15]/ev_4gmlxylzcut[k+15];
//       erreff_mD0850_allcut[k] = sqrt( (eff_mD0850_allcut[k]*(1-eff_mD0850_allcut[k]))/(ev_4gmlxylzcut[k+15]*1.0));

//       eff_mD0850_allcutrecov[k] = ev_2dimhit_allcutrecov[k+15]/ev_4gmlxylzcut[k+15];
//       erreff_mD0850_allcutrecov[k] = sqrt( (eff_mD0850_allcutrecov[k]*(1-eff_mD0850_allcutrecov[k]))/(ev_4gmlxylzcut[k+15]*1.0));

//       eff_mD0850_final[k] = ev_2dimhit_allcutrecov2[k+15]/ev_all[k+15];
//       erreff_mD0850_final[k] = sqrt( (eff_mD0850_final[k]*(1-eff_mD0850_final[k]))/(ev_all[k+15]*1.0));

//       if(k==0) cout<<" mD0850   "<< eff_mD0850_final[k]<<endl;

//     }



//     for(int k=0;k<7;k++){

//       eff_mD0250[k] = ev_2dimhit[k+4]/ev_4gmlxylzcut[k+4];
//       erreff_mD0250[k] = sqrt( (eff_mD0250[k]*(1-eff_mD0250[k]))/(ev_4gmlxylzcut[k+4]*1.0));

//       eff_mD0250_gt[k] = ev_2dimhitgt[k+4]/ev_4gmlxylzcut[k+4];
//       erreff_mD0250_gt[k] = sqrt( (eff_mD0250_gt[k]*(1-eff_mD0250_gt[k]))/(ev_4gmlxylzcut[k+4]*1.0));

//       eff_mD0250_fvtx[k] = ev_2dimhitfvtx[k+4]/ev_4gmlxylzcut[k+4];
//       erreff_mD0250_fvtx[k] = sqrt( (eff_mD0250_fvtx[k]*(1-eff_mD0250_fvtx[k]))/(ev_4gmlxylzcut[k+4]*1.0));

//       eff_mD0250_allcut[k] = ev_2dimhit_allcut[k+4]/ev_4gmlxylzcut[k+4];
//       erreff_mD0250_allcut[k] = sqrt( (eff_mD0250_allcut[k]*(1-eff_mD0250_allcut[k]))/(ev_4gmlxylzcut[k+4]*1.0));

//       eff_mD0250_allcutrecov[k] = ev_2dimhit_allcutrecov[k+4]/ev_4gmlxylzcut[k+4];
//       erreff_mD0250_allcutrecov[k] = sqrt( (eff_mD0250_allcutrecov[k]*(1-eff_mD0250_allcutrecov[k]))/(ev_4gmlxylzcut[k+4]*1.0));

//       eff_mD0250_allcutrecov2[k] = ev_2dimhit_allcutrecov2[k+4]/ev_4gmlxylzcut[k+4];

//       // erreff_mD0250_allcutrecov21[k] = sqrt( ( (ev_2dimhit_allcutrecov2[k+4]/ev_all[k+4])*(1 -  (ev_2dimhit_allcutrecov2[k+4]/ev_all[k+4])) )/ev_all[k+4]);
//       // erreff_mD0250_allcutrecov22[k] = sqrt( ( (ev_4gmlxylzcut[k+4]/ev_all[k+4])*(1 -  (ev_4gmlxylzcut[k+4]/ev_all[k+4])) )/ev_all[k+4] );
//       // erreff_mD0250_allcutrecov2[k] =  eff_mD0250_allcutrecov2[k]*sqrt( pow(erreff_mD0250_allcutrecov21[k],2)  + pow(erreff_mD0250_allcutrecov22[k],2) );

//       erreff_mD0250_allcutrecov2[k] =  sqrt( (eff_mD0250_allcutrecov2[k]*(1-eff_mD0250_allcutrecov2[k]))/(ev_4gmlxylzcut[k+4]*1.0));





//       eff_mD0250_final[k] = ev_2dimhit_allcutrecov2[k+4]/ev_all[k+4];
//       eff_mD0250_final2[k] = ev_2dimhit_allcutrecov2[k+4]/ev_all[k+4];

//       erreff_mD0250_final[k] = sqrt( (eff_mD0250_final[k]*(1-eff_mD0250_final[k]))/(ev_all[k+4]*1.0));
//       erreff_mD0250_final2[k] = sqrt( (eff_mD0250_final2[k]*(1-eff_mD0250_final2[k]))/(ev_all[k+4]*1.0));

//       if(k==0) cout<<" mD0250   "<< eff_mD0250_final[k]<<endl;

//     }



//     // eff_mD0250_allcutrecov2[7] = 0.5;
//     // eff_mD0250_allcutrecov2[8] = 0.66;

//     // err_eff_mD0250_allcutrecov2[7] = 0.5;
//     // err_eff_mD0250_allcutrecov2[8] = 0.66;




    
//     eff_mD0250_final2[7] = ev_2dimhit_allcutrecov2[33]/ev_all[33];
//     eff_mD0250_final2[8] = ev_2dimhit_allcutrecov2[34]/ev_all[34];
//     eff_mD0250_final2[9] = 0.0;

//     erreff_mD0250_final2[7] = sqrt( (eff_mD0250_final2[7]*(1-eff_mD0250_final2[7]))/(ev_all[33]*1.0));
//     erreff_mD0250_final2[8] = sqrt( (eff_mD0250_final2[8]*(1-eff_mD0250_final2[8]))/(ev_all[34]*1.0));
//     erreff_mD0250_final2[9] =0.0;


//      TGraphErrors *gr_eff_mD0400 = new TGraphErrors(4,ctau,eff_mD0400,0,erreff_mD0400);

//      TGraphErrors *gr_eff_mD0400_gt = new TGraphErrors(4,ctau,eff_mD0400_gt,0,erreff_mD0400_gt);
//      TGraphErrors *gr_eff_mD0400_fvtx = new TGraphErrors(4,ctau,eff_mD0400_fvtx,0,erreff_mD0400_fvtx);
//      TGraphErrors *gr_eff_mD0400_allcut = new TGraphErrors(4,ctau,eff_mD0400_allcut,0,erreff_mD0400_allcut);
//      TGraphErrors *gr_eff_mD0400_allcutrecov = new TGraphErrors(4,ctau,eff_mD0400_allcutrecov,0,erreff_mD0400_allcutrecov);
//      TGraphErrors *gr_eff_mD0400_allcutrecov2 = new TGraphErrors(4,ctau,eff_mD0400_allcutrecov2,0,erreff_mD0400_allcutrecov2);
//      TGraphErrors *gr_eff_mD0400_final = new TGraphErrors(4,ctau,eff_mD0400_final,0,erreff_mD0400_final);

//      TGraphErrors *gr_eff_mD0850 = new TGraphErrors(3,ctau4,eff_mD0850,0,erreff_mD0850);
//      TGraphErrors *gr_eff_mD0850_gt = new TGraphErrors(3,ctau4,eff_mD0850_gt,0,erreff_mD0850_gt);
//      TGraphErrors *gr_eff_mD0850_fvtx = new TGraphErrors(3,ctau4,eff_mD0850_fvtx,0,erreff_mD0850_fvtx);
//      TGraphErrors *gr_eff_mD0850_allcut = new TGraphErrors(3,ctau4,eff_mD0850_allcut,0,erreff_mD0850_allcut);
//      TGraphErrors *gr_eff_mD0850_allcutrecov = new TGraphErrors(3,ctau4,eff_mD0850_allcutrecov,0,erreff_mD0850_allcutrecov);
//      TGraphErrors *gr_eff_mD0850_final = new TGraphErrors(3,ctau4,eff_mD0850_final,0,erreff_mD0850_final);

//      TGraphErrors *gr_eff_mD1000 = new TGraphErrors(4,ctau5,eff_mD1000,0,erreff_mD1000);
//      TGraphErrors *gr_eff_mD1000_gt = new TGraphErrors(4,ctau5,eff_mD1000_gt,0,erreff_mD1000_gt);
//      TGraphErrors *gr_eff_mD1000_fvtx = new TGraphErrors(4,ctau5,eff_mD1000_fvtx,0,erreff_mD1000_fvtx);
//      TGraphErrors *gr_eff_mD1000_allcut = new TGraphErrors(4,ctau5,eff_mD1000_allcut,0,erreff_mD1000_allcut);
//      TGraphErrors *gr_eff_mD1000_allcutrecov = new TGraphErrors(4,ctau5,eff_mD1000_allcutrecov,0,erreff_mD1000_allcutrecov);
//      TGraphErrors *gr_eff_mD1000_final = new TGraphErrors(4,ctau5,eff_mD1000_final,0,erreff_mD1000_final);


//      TGraphErrors *gr_eff_mD1500 = new TGraphErrors(4,ctau,eff_mD1500,0,erreff_mD1500);
//      TGraphErrors *gr_eff_mD1500_gt = new TGraphErrors(4,ctau,eff_mD1500_gt,0,erreff_mD1500_gt);
//      TGraphErrors *gr_eff_mD1500_fvtx = new TGraphErrors(4,ctau,eff_mD1500_fvtx,0,erreff_mD1500_fvtx);
//      TGraphErrors *gr_eff_mD1500_allcut = new TGraphErrors(4,ctau,eff_mD1500_allcut,0,erreff_mD1500_allcut);
//      TGraphErrors *gr_eff_mD1500_allcutrecov = new TGraphErrors(4,ctau,eff_mD1500_allcutrecov,0,erreff_mD1500_allcutrecov);
//      TGraphErrors *gr_eff_mD1500_final = new TGraphErrors(4,ctau,eff_mD1500_final,0,erreff_mD1500_final);

   
//      TGraphErrors *gr_eff_mD2000 = new TGraphErrors(4,ctau6,eff_mD2000,0,erreff_mD2000);
//      TGraphErrors *gr_eff_mD2000_gt = new TGraphErrors(4,ctau6,eff_mD2000_gt,0,erreff_mD2000_gt);
//      TGraphErrors *gr_eff_mD2000_fvtx = new TGraphErrors(4,ctau6,eff_mD2000_fvtx,0,erreff_mD2000_fvtx);
//      TGraphErrors *gr_eff_mD2000_allcut = new TGraphErrors(4,ctau6,eff_mD2000_allcut,0,erreff_mD2000_allcut);
//      TGraphErrors *gr_eff_mD2000_allcutrecov = new TGraphErrors(4,ctau6,eff_mD2000_allcutrecov,0,erreff_mD2000_allcutrecov);
//      TGraphErrors *gr_eff_mD2000_final = new TGraphErrors(6,ctau6,eff_mD2000_final,0,erreff_mD2000_final);
   

//      TGraphErrors *gr_eff_mD0700 = new TGraphErrors(4,ctau5,eff_mD0700,0,erreff_mD0700);
//      TGraphErrors *gr_eff_mD0700_gt = new TGraphErrors(4,ctau5,eff_mD0700_gt,0,erreff_mD0700_gt);
//      TGraphErrors *gr_eff_mD0700_fvtx = new TGraphErrors(4,ctau5,eff_mD0700_fvtx,0,erreff_mD0700_fvtx);
//      TGraphErrors *gr_eff_mD0700_allcut = new TGraphErrors(4,ctau5,eff_mD0700_allcut,0,erreff_mD0700_allcut);
//      TGraphErrors *gr_eff_mD0700_allcutrecov = new TGraphErrors(4,ctau5,eff_mD0700_allcutrecov,0,erreff_mD0700_allcutrecov);
//      TGraphErrors *gr_eff_mD0700_final = new TGraphErrors(4,ctau5,eff_mD0700_final,0,erreff_mD0700_final);

//      TGraphErrors *gr_eff_mD0250 = new TGraphErrors(7,ctau2,eff_mD0250,0,erreff_mD0250);
//      TGraphErrors *gr_eff_mD0250_gt = new TGraphErrors(7,ctau2,eff_mD0250_gt,0,erreff_mD0250_gt);
//      TGraphErrors *gr_eff_mD0250_fvtx = new TGraphErrors(7,ctau2,eff_mD0250_fvtx,0,erreff_mD0250_fvtx);
//      TGraphErrors *gr_eff_mD0250_allcut = new TGraphErrors(7,ctau2,eff_mD0250_allcut,0,erreff_mD0250_allcut);
//      TGraphErrors *gr_eff_mD0250_allcutrecov = new TGraphErrors(7,ctau2,eff_mD0250_allcutrecov,0,erreff_mD0250_allcutrecov);
//      TGraphErrors *gr_eff_mD0250_allcutrecov2 = new TGraphErrors(7,ctau2,eff_mD0250_allcutrecov2,0,erreff_mD0250_allcutrecov2);

//      TGraphErrors *gr_eff_mD0250_final = new TGraphErrors(7,ctau2,eff_mD0250_final,0,erreff_mD0250_final);

//      TGraphErrors *gr_eff_mD0250_final2 = new TGraphErrors(9,ctau2l,eff_mD0250_final2,0,erreff_mD0250_final2);
   

//     TLegend *leg = new TLegend(0.25,0.2,0.85,0.6);
//     leg->SetBorderSize(0);
//     leg->SetFillColor(0);
//     leg->SetTextSize(0.035);
//     leg->AddEntry(gr_eff_mD0250_fvtx,"m_{#gamma D} =0.25GeV KalmanFitterVtx","PL");
//     leg->AddEntry(gr_eff_mD0400_fvtx,"m_{#gamma D} =0.4GeV KalmanFitterVtx","PL");
//     leg->AddEntry(gr_eff_mD1000_fvtx,"m_{#gamma D} =1.0GeV KalmanFitterVtx","PL");
//     leg->AddEntry(gr_eff_mD0250_gt,  "m_{#gamma D} =0.25GeV KalmanFitterVtx+ recoverVtx","PL");
//     leg->AddEntry(gr_eff_mD0400_gt,  "m_{#gamma D} =0.4GeV  KalmanFitterVtx+recoverVtx","PL");
//     leg->AddEntry(gr_eff_mD1000_gt,  "m_{#gamma D} =1.0GeV  KalmanFitterVtx+recoverVtx","PL");



//     TLegend *legg = new TLegend(0.2,0.15,0.75,0.55);
//     legg->SetBorderSize(0);
//     legg->SetFillColor(0);
//     legg->SetTextSize(0.037);
//     legg->AddEntry(gr_eff_mD0250_gt,  "m_{#gamma D} =0.25GeV KalmanFitterVtx+recoverVtx genTrk","PL");
//     legg->AddEntry(gr_eff_mD0400_gt,  "m_{#gamma D} =0.4GeV  KalmanFitterVtx+recoverVtx genTrk","PL");
//     legg->AddEntry(gr_eff_mD1000_gt,  "m_{#gamma D} =1.0GeV  KalmanFitterVtx+recoverVtx genTrk","PL");
//     legg->AddEntry(gr_eff_mD0250,  "m_{#gamma D} =0.25GeV KalmanFitterVtx+recoverVtx RefittedTrk","PL");
//     legg->AddEntry(gr_eff_mD0400,  "m_{#gamma D} =0.4GeV  KalmanFitterVtx+recoverVtx RefittedTrk","PL");
//     legg->AddEntry(gr_eff_mD1000,  "m_{#gamma D} =1.0GeV  KalmanFitterVtx+recoverVtx RefittedTrk","PL");


//     TLegend *leg2 = new TLegend(0.6,0.45,0.8,0.95);
//     leg2->SetBorderSize(0);
//     leg2->SetFillColor(0);
//     leg2->SetTextSize(0.035);
//     leg2->AddEntry(gr_eff_mD0250_allcut,"mass_{#gamma D}=0.25GeV ","PL");
//     leg2->AddEntry(gr_eff_mD0400_allcut,"mass_{#gamma D}=0.4GeV ","PL");
//     leg2->AddEntry(gr_eff_mD0700_allcut,"mass_{#gamma D}=0.7GeV ","PL");
//     leg2->AddEntry(gr_eff_mD0850_allcut,"mass_{#gamma D}=0.85GeV ","PL");
//     leg2->AddEntry(gr_eff_mD1000_allcut,"mass_{#gamma D}=1.0GeV ","PL");
//     leg2->AddEntry(gr_eff_mD1500_allcut,"mass_{#gamma D}=1.5GeV ","PL");
//     leg2->AddEntry(gr_eff_mD2000_allcut,"mass_{#gamma D}=2.0GeV ","PL");


//     //    TH2F *dummy3 = new TH2F("","",100,-0.2,5.2,100,0.0,1.0);

//     // TCanvas *c = new TCanvas("c","c",700,500);
//     // dummy3->GetXaxis()->SetTitle("c#tau [mm]");
//     // dummy3->GetYaxis()->SetTitle("#epsilon_{rec}/#alpha_{gen}");
//     // dummy3->Draw();
//     // gr_eff_mD0400_gt->SetLineWidth(2);
//     // gr_eff_mD0400_gt->SetLineColor(2);
//     // gr_eff_mD0400_gt->SetMarkerColor(2);
//     // gr_eff_mD0400_gt->Draw("PL");
//     // gr_eff_mD1000_gt->SetLineWidth(3);
//     // gr_eff_mD1000_gt->SetLineColor(3);
//     // gr_eff_mD1000_gt->SetMarkerColor(3);
//     // gr_eff_mD1000_gt->Draw("PLsame");
//     // gr_eff_mD1000_fvtx->SetLineWidth(3);
//     // gr_eff_mD1000_fvtx->SetLineColor(3);
//     // gr_eff_mD1000_fvtx->SetLineStyle(3);
//     // gr_eff_mD1000_fvtx->SetMarkerColor(3);
//     // gr_eff_mD1000_fvtx->Draw("PLsame");
//     // // gr_eff_mD0400_gt->SetLineStyle(2);
//     // // gr_eff_mD0400_gt->SetLineColor(2);
//     // // gr_eff_mD0400_gt->SetMarkerColor(2);
//     // // gr_eff_mD0400_gt->Draw("PLsame");
//     // gr_eff_mD0400_fvtx->SetLineWidth(3);
//     // gr_eff_mD0400_fvtx->SetLineStyle(3);
//     // gr_eff_mD0400_fvtx->SetLineColor(2);
//     // gr_eff_mD0400_fvtx->SetMarkerColor(2);
//     // gr_eff_mD0400_fvtx->SetMarkerStyle(26);
//     // gr_eff_mD0400_fvtx->Draw("PLsame");
//     // gr_eff_mD0250->SetLineWidth(2);
//     // gr_eff_mD0250->Draw("PLsame");
//     // // gr_eff_mD0250_gt->SetLineStyle(2);
//     // // gr_eff_mD0250_gt->Draw("PLsame");
//     // gr_eff_mD0250_fvtx->SetLineStyle(3);
//     // gr_eff_mD0250_fvtx->SetMarkerStyle(26);
//     // gr_eff_mD0250_fvtx->Draw("PLsame");
//     // leg->Draw("same");
//     // c->SaveAs("eff_recover_newvertex.pdf","recreate");



//     // TCanvas *cc = new TCanvas("cc","cc",700,500);
//     // dummy3->GetXaxis()->SetTitle("c#tau [mm]");
//     // dummy3->GetYaxis()->SetTitle("#epsilon_{rec}/#alpha_{gen}");
//     // dummy3->Draw();
//     // gr_eff_mD0400_gt->SetLineWidth(2);
//     // gr_eff_mD0400_gt->SetLineColor(2);
//     // gr_eff_mD0400_gt->SetMarkerColor(2);
//     // gr_eff_mD0400_gt->Draw("PL");
//     // gr_eff_mD1000_gt->SetLineWidth(3);
//     // gr_eff_mD1000_gt->SetLineColor(3);
//     // gr_eff_mD1000_gt->SetMarkerColor(3);
//     // gr_eff_mD1000_gt->Draw("PLsame");
//     // gr_eff_mD1000->SetLineWidth(3);
//     // gr_eff_mD1000->SetLineColor(3);
//     // gr_eff_mD1000->SetLineStyle(3);
//     // gr_eff_mD1000->SetMarkerColor(3);
//     // gr_eff_mD1000->Draw("PLsame");
//     // // gr_eff_mD0400_gt->SetLineStyle(2);
//     // // gr_eff_mD0400_gt->SetLineColor(2);
//     // // gr_eff_mD0400_gt->SetMarkerColor(2);
//     // // gr_eff_mD0400_gt->Draw("PLsame");
//     // gr_eff_mD0400->SetLineWidth(3);
//     // gr_eff_mD0400->SetLineStyle(3);
//     // gr_eff_mD0400->SetLineColor(2);
//     // gr_eff_mD0400->SetMarkerColor(2);
//     // gr_eff_mD0400->SetMarkerStyle(26);
//     // gr_eff_mD0400->Draw("PLsame");
//     // gr_eff_mD0250_gt->SetLineWidth(2);
//     // gr_eff_mD0250_gt->Draw("PLsame");
//     // // gr_eff_mD0250_gt->SetLineStyle(2);
//     // // gr_eff_mD0250_gt->Draw("PLsame");
//     // gr_eff_mD0250->SetLineStyle(3);
//     // gr_eff_mD0250->SetMarkerStyle(26);
//     // gr_eff_mD0250->Draw("PLsame");
//     // legg->Draw("same");
//     // cc->SaveAs("eff_recover_matching.pdf","recreate");




//     TLegend *leg22 = new TLegend(0.4,0.25,0.8,0.8);
//     leg22->SetBorderSize(0);
//     leg22->SetFillColor(0);
//     leg22->SetTextSize(0.036);
//     leg22->AddEntry(gr_eff_mD0250_allcut,"mass_{#gamma D}=0.25GeV ","PL");
//     leg22->AddEntry(gr_eff_mD0400_allcut,"mass_{#gamma D}=0.4GeV ","PL");
//     leg22->AddEntry(gr_eff_mD0700_allcut,"mass_{#gamma D}=0.7GeV ","PL");
//     leg22->AddEntry(gr_eff_mD0850_allcut,"mass_{#gamma D}=0.85GeV ","PL");
//     leg22->AddEntry(gr_eff_mD1000_allcut,"mass_{#gamma D}=1.0GeV ","PL");
//     leg22->AddEntry(gr_eff_mD1500_allcut,"mass_{#gamma D}=1.5GeV ","PL");
//     leg22->AddEntry(gr_eff_mD2000_allcut,"mass_{#gamma D}=2.0GeV ","PL");


//     // TH2F *dummy3 = new TH2F("","",100,-0.2,5.2,100,0.0,1.0);
//     // TCanvas *c1 = new TCanvas("c1","c1",700,500);
//     // dummy3->GetXaxis()->SetTitle("c#tau [mm]");
//     // dummy3->GetYaxis()->SetTitle("#epsilon_{full}/#alpha_{gen}");
//     // dummy3->Draw();
//     // gr_eff_mD0400_allcut->SetLineColor(2);
//     // gr_eff_mD0400_allcut->SetMarkerColor(2);
//     // gr_eff_mD0400_allcut->Draw("PL");
//     // gr_eff_mD0400_allcutrecov->SetLineColor(2);
//     // gr_eff_mD0400_allcutrecov->SetMarkerColor(2);
//     // //   gr_eff_mD0400_allcutrecov->SetMarkerStyle(24);
//     // //   gr_eff_mD0400_allcutrecov->Draw("PL");
//     // gr_eff_mD0250_allcut->SetLineColor(1);
//     // gr_eff_mD0250_allcut->SetMarkerColor(1);
//     // gr_eff_mD0250_allcut->SetLineWidth(2);
//     // gr_eff_mD0250_allcut->Draw("PLsame");
//     // gr_eff_mD0250_allcutrecov->SetLineColor(1);
//     // gr_eff_mD0250_allcutrecov->SetMarkerColor(1);
//     // //   gr_eff_mD0250_allcutrecov->SetMarkerStyle(24);
//     // //   gr_eff_mD0250_allcutrecov->Draw("PLsame");
//     // gr_eff_mD0700_allcut->SetLineColor(3);
//     // gr_eff_mD0700_allcut->SetMarkerColor(3);
//     // gr_eff_mD0700_allcut->SetLineWidth(2);
//     // gr_eff_mD0700_allcut->Draw("PLsame");
//     // gr_eff_mD0700_allcutrecov->SetLineColor(3);
//     // gr_eff_mD0700_allcutrecov->SetMarkerColor(3);
//     // //   gr_eff_mD0700_allcutrecov->SetMarkerStyle(24);
//     // //   gr_eff_mD0700_allcutrecov->Draw("PLsame");


//     //  gr_eff_mD0850_allcut->SetLineColor(4);
//     //  gr_eff_mD0850_allcut->SetMarkerColor(4);
//     //  gr_eff_mD0850_allcut->SetLineWidth(2);
//     //  gr_eff_mD0850_allcut->Draw("PLsame");
//     //  gr_eff_mD0850_allcutrecov->SetLineColor(4);
//     //  gr_eff_mD0850_allcutrecov->SetMarkerColor(4);
//     //  //   gr_eff_mD0850_allcutrecov->SetMarkerStyle(24);
//     //  //   gr_eff_mD0850_allcutrecov->Draw("PLsame");

//     //  gr_eff_mD1000_allcut->SetLineColor(5);
//     //  gr_eff_mD1000_allcut->SetMarkerColor(5);
//     //  gr_eff_mD1000_allcut->SetLineWidth(2);
//     //  gr_eff_mD1000_allcut->Draw("PLsame");
//     //  gr_eff_mD1000_allcutrecov->SetLineColor(5);
//     //  gr_eff_mD1000_allcutrecov->SetMarkerColor(5);
//     //  //   gr_eff_mD1000_allcutrecov->SetMarkerStyle(24);
//     //  //   gr_eff_mD1000_allcutrecov->Draw("PLsame");

//     //  gr_eff_mD1500_allcut->SetLineColor(6);
//     //  gr_eff_mD1500_allcut->SetMarkerColor(6);
//     //  gr_eff_mD1500_allcut->SetLineWidth(2);
//     //  gr_eff_mD1500_allcut->Draw("PLsame");
//     //  gr_eff_mD1500_allcutrecov->SetLineColor(6);
//     //  gr_eff_mD1500_allcutrecov->SetMarkerColor(6);
//     //  //   gr_eff_mD1500_allcutrecov->SetMarkerStyle(24);
//     //  //   gr_eff_mD1500_allcutrecov->Draw("PLsame");


//     //  gr_eff_mD2000_allcut->SetLineColor(7);
//     //  gr_eff_mD2000_allcut->SetMarkerColor(7);
//     //  gr_eff_mD2000_allcut->SetLineWidth(2);
//     //  gr_eff_mD2000_allcut->Draw("PLsame");
//     //  gr_eff_mD2000_allcutrecov->SetLineColor(7);
//     //  gr_eff_mD2000_allcutrecov->SetMarkerColor(7);
//     //  //   gr_eff_mD2000_allcutrecov->SetMarkerStyle(24);
//     //  //   gr_eff_mD2000_allcutrecov->Draw("PLsame");
//     //  leg22->Draw("same");
//     //  c1->SaveAs("eff_allcut.pdf","recreate");




//     //     TH2F *dummy3 = new TH2F("","",100,-0.2,5.2,100,0.0,1.0);
//      // TCanvas *c2 = new TCanvas("c2","c2",700,500);
//      // dummy3->GetXaxis()->SetTitle("c#tau [mm]");
//      // dummy3->GetYaxis()->SetTitle("#epsilon_{full}/#alpha_{gen}");
//      // dummy3->Draw();

//      // gr_eff_mD0400_allcutrecov->SetLineColor(2);
//      // gr_eff_mD0400_allcutrecov->SetLineWidth(2);
//      // gr_eff_mD0400_allcutrecov->SetMarkerColor(2);
//      // gr_eff_mD0400_allcutrecov->Draw("PL");

//      // gr_eff_mD0250_allcutrecov->SetLineColor(1);
//      // gr_eff_mD0250_allcutrecov->SetLineWidth(2);
//      // gr_eff_mD0250_allcutrecov->SetMarkerColor(1);
//      // gr_eff_mD0250_allcutrecov->Draw("PLsame");

//      // gr_eff_mD0700_allcutrecov->SetLineColor(3);
//      // gr_eff_mD0700_allcutrecov->SetLineWidth(2);
//      // gr_eff_mD0700_allcutrecov->SetMarkerColor(3);
//      // gr_eff_mD0700_allcutrecov->Draw("PLsame");


//      // gr_eff_mD0850_allcutrecov->SetLineColor(4);
//      // gr_eff_mD0850_allcutrecov->SetLineWidth(2);
//      // gr_eff_mD0850_allcutrecov->SetMarkerColor(4);
//      // gr_eff_mD0850_allcutrecov->Draw("PLsame");

//      // gr_eff_mD1000_allcutrecov->SetMarkerColor(5);
//      // gr_eff_mD1000_allcutrecov->SetLineColor(5);
//      // gr_eff_mD1000_allcutrecov->SetLineWidth(2);
//      // gr_eff_mD1000_allcutrecov->Draw("PLsame");

//      // gr_eff_mD1500_allcutrecov->SetLineColor(6);
//      // gr_eff_mD1500_allcutrecov->SetLineWidth(2);
//      // gr_eff_mD1500_allcutrecov->SetMarkerColor(6);
//      // gr_eff_mD1500_allcutrecov->Draw("PLsame");


//      // gr_eff_mD2000_allcutrecov->SetLineColor(7);
//      // gr_eff_mD2000_allcutrecov->SetLineWidth(2);
//      // gr_eff_mD2000_allcutrecov->SetMarkerColor(7);
//      // gr_eff_mD2000_allcutrecov->Draw("PLsame");


//      // leg22->Draw("same");
//      // c2->SaveAs("eff_recovery_allcut3.pdf","recreate");






//     //     TH2F *dummy3 = new TH2F("","",100,-0.2,5.2,100,0.0,1.0);
//      // TCanvas *c3 = new TCanvas("c3","c3",700,500);
//      // dummy3->GetXaxis()->SetTitle("c#tau [mm]");
//      // dummy3->GetYaxis()->SetTitle("#epsilon_{full}/#alpha_{gen}");
//      // dummy3->Draw();
//      // gr_eff_mD0400_allcutrecov2->SetLineColor(2);
//      // gr_eff_mD0400_allcutrecov2->SetMarkerColor(2);
//      // gr_eff_mD0400_allcutrecov2->SetLineWidth(2);
//      // gr_eff_mD0400_allcutrecov2->Draw("PL");

//      // gr_eff_mD0250_allcutrecov2->SetLineColor(1);
//      // gr_eff_mD0250_allcutrecov2->SetMarkerColor(1);
//      // gr_eff_mD0250_allcutrecov2->SetLineWidth(2);
//      // gr_eff_mD0250_allcutrecov2->Draw("PLsame");
//      // gr_eff_mD0250_allcutrecov2->SetLineStyle(1);

//      // gr_eff_mD0700_allcutrecov->SetLineColor(3);
//      // gr_eff_mD0700_allcutrecov->SetMarkerColor(3);
//      // gr_eff_mD0700_allcutrecov->SetLineWidth(2);
//      // gr_eff_mD0700_allcutrecov->Draw("PLsame");


//      // gr_eff_mD0850_allcutrecov->SetLineColor(4);
//      // gr_eff_mD0850_allcutrecov->SetMarkerColor(4);
//      // gr_eff_mD0850_allcutrecov->SetLineWidth(2);
//      // gr_eff_mD0850_allcutrecov->Draw("PLsame");

//      // gr_eff_mD1000_allcutrecov->SetLineColor(5);
//      // gr_eff_mD1000_allcutrecov->SetMarkerColor(5);
//      // gr_eff_mD1000_allcutrecov->SetLineWidth(2);
//      // gr_eff_mD1000_allcutrecov->Draw("PLsame");

//      // gr_eff_mD1500_allcutrecov->SetLineColor(6);
//      // gr_eff_mD1500_allcutrecov->SetMarkerColor(6);
//      // gr_eff_mD1500_allcutrecov->SetLineWidth(2);
//      // gr_eff_mD1500_allcutrecov->Draw("PLsame");


//      // gr_eff_mD2000_allcutrecov->SetLineColor(7);
//      // gr_eff_mD2000_allcutrecov->SetMarkerColor(7);
//      // gr_eff_mD2000_allcutrecov->SetLineWidth(2);
//      // gr_eff_mD2000_allcutrecov->Draw("PLsame");
//      // leg22->Draw("same");
//      // c3->SaveAs("eff_recovery_allcut3.pdf","recreate");

//     Float_t x_model[31];
  
//     Float_t xin=0.0;
//     for(int k=0;k<31;k++){x_model[k]=xin;xin=xin+(5.0/30.0);}

//     Float_t x_model2[101];
  
//     xin=0.0;
//     for(int k=0;k<101;k++){x_model2[k]=xin;xin=xin+(20.0/100.0);}
  
//     Float_t model_mD0250[31] = 
//       {0.088055, 0.0580347, 0.0300059, 0.0178765, 0.0118104, 0.00837308, 
//        0.00624275, 0.0048327, 0.00385154, 0.00314149, 0.00261115, 
//        0.00220462, 0.00188616, 0.00163204, 0.00142603, 0.00125671, 
//        0.00111586, 0.000997423, 0.000896895, 0.000810836, 0.000736595, 
//        0.000672105, 0.000615728, 0.00056616, 0.000522345, 0.000483427, 
//        0.000448703, 0.00041759, 0.000389605, 0.000364341, 0.000341458};


//     TGraphErrors *gr_mod_mD0250 = new TGraphErrors(31,x_model,model_mD0250,0,0);


//     Float_t model_mD0250_2[101] = 
//       {0.0876203, 0.0500764, 0.0239049, 0.0137341, 0.00888464, 0.00621193, 
// 0.00458579, 0.00352368, 0.00279202, 0.0022667, 0.00187685, 
// 0.00157958, 0.00134773, 0.00116344, 0.00101452, 0.000892467, 
// 0.00079119, 0.000706225, 0.000634248, 0.000572741, 0.000519766, 
// 0.000473816, 0.000433701, 0.000398474, 0.000367371, 0.000339772, 
// 0.000315171, 0.000293148, 0.000273356, 0.000255503, 0.000239343, 
// 0.000224669, 0.000211305, 0.000199099, 0.00018792, 0.000177657, 
// 0.000168213, 0.000159502, 0.000151451, 0.000143995, 0.000137075, 
// 0.000130643, 0.000124653, 0.000119066, 0.000113846, 0.000108963, 
// 0.000104386, 0.000100093, 0.0000960584, 0.0000922633, 0.0000886887, 
// 0.0000853178, 0.0000821356, 0.0000791282, 0.0000762829, 0.0000735885, 
// 0.0000710343, 0.0000686108, 0.0000663092, 0.0000641216, 0.0000620404, 
// 0.000060059, 0.000058171, 0.0000563706, 0.0000546526, 0.0000530119, 
// 0.000051444, 0.0000499446, 0.0000485099, 0.0000471361, 0.0000458198, 
// 0.0000445579, 0.0000433475, 0.0000421857, 0.00004107, 0.0000399979, 
// 0.0000389673, 0.0000379761, 0.0000370222, 0.0000361037, 0.0000352191, 
// 0.0000343665, 0.0000335446, 0.0000327518, 0.0000319867, 0.0000312482, 
// 0.0000305349, 0.0000298458, 0.0000291798, 0.0000285358, 0.0000279129, 
// 0.0000273101, 0.0000267267, 0.0000261618, 0.0000256146, 0.0000250844, 
//        0.0000245705, 0.0000240722, 0.0000235889, 0.0000231201, 0.000022665};

//     TGraphErrors *gr_mod_mD0250_2 = new TGraphErrors(101,x_model2,model_mD0250_2,0,0);



//     Float_t model_mD0400[31] = 
//   {0.0784426, 0.067021, 0.0432866, 0.0287911, 0.0203124, 0.0150483, 
//   0.0115813, 0.0091838, 0.0074591, 0.00617778, 0.00520018, 0.00443746, 
//   0.00383102, 0.00334092, 0.0029392, 0.00260582, 0.00232612, 
//   0.00208916, 0.00188665, 0.00171223, 0.00156093, 0.00142884, 
//   0.00131284, 0.00121041, 0.00111953, 0.00103851, 0.000965975,
//    0.000900786, 0.000841982, 0.000788754, 0.00074042};

//     TGraphErrors *gr_mod_mD0400 = new TGraphErrors(31,x_model,model_mD0400,0,0);


//    Float_t model_mD0700[31] = 
//   {0.0636091, 0.0619584, 0.0512775, 0.0398318, 0.0310512, 0.0246551, 
//   0.0199696, 0.0164715, 0.0138043, 0.0117298, 0.010087, 0.00876494, 
//   0.0076859, 0.00679404, 0.00604862, 0.00541933, 0.00488329, 
//   0.00442298, 0.00402479, 0.00367804, 0.00337425, 0.00310659, 
//   0.00286957, 0.00265868, 0.00247021, 0.0023011, 0.00214878, 
//    0.00201111, 0.00188626, 0.00177268, 0.00166907};


//     TGraphErrors *gr_mod_mD0700 = new TGraphErrors(31,x_model,model_mD0700,0,0);


//    Float_t model_mD0850[31] = 
//   {0.0583882, 0.0577449, 0.0510247, 0.0418668, 0.0339295, 0.0277107, 
//   0.0229278, 0.0192294, 0.0163336, 0.0140335, 0.0121807, 0.0106686, 
//   0.00941955, 0.00837656, 0.00749701, 0.00674867, 0.00610679, 
//   0.00555216, 0.00506971, 0.00464746, 0.00427581, 0.00394701, 
//   0.00365471, 0.00339372, 0.00315971, 0.0029491, 0.00275887, 
//    0.00258647, 0.00242974, 0.00228684, 0.00215619};


//     TGraphErrors *gr_mod_mD0850 = new TGraphErrors(31,x_model,model_mD0850,0,0);


//    Float_t model_mD1000[31] = 
//   {0.0607299, 0.0604448, 0.0557563, 0.0477829, 0.0400268, 0.0335128, 
//   0.0282639, 0.0240665, 0.0206951, 0.0179629, 0.015726, 0.0138754, 
//   0.0123293, 0.0110256, 0.00991677, 0.00896627, 0.00814558, 0.00743225, 
//   0.00680843, 0.00625983, 0.00577485, 0.00534405, 0.00495968, 
//   0.0046153, 0.00430556, 0.00402598, 0.00377277, 0.00354271, 
//    0.00333306, 0.00314149, 0.00296598};

//     TGraphErrors *gr_mod_mD1000 = new TGraphErrors(31,x_model,model_mD1000,0,0);


//    Float_t model_mD1500[31] = 
//   {0.0595531, 0.0595378, 0.0583923, 0.054676, 0.0495462, 0.0442137, 
//   0.0392513, 0.0348475, 0.0310188, 0.0277162, 0.0248719, 0.0224181, 
//   0.0202941, 0.0184478, 0.0168356, 0.0154212, 0.0141748, 0.0130714, 
//   0.0120904, 0.0112148, 0.0104302, 0.00972462, 0.00908784, 0.00851132, 
//   0.00798774, 0.00751087, 0.00707533, 0.00667651, 0.00631041, 
//    0.00597356, 0.00566295};
//     TGraphErrors *gr_mod_mD1500 = new TGraphErrors(31,x_model,model_mD1500,0,0);


//    Float_t model_mD2000[31] = 
//      {0.0594774, 0.0594774, 0.0591982, 0.0576092, 0.0546066, 0.0508183, 
//       0.0467976, 0.0428721, 0.0392015, 0.035848, 0.0328218, 0.0301081, 
//       0.0276811, 0.0255114, 0.0235703, 0.0218307, 0.0202684, 0.0188619, 
//       0.0175925, 0.0164438, 0.0154017, 0.0144537, 0.0135893, 0.0127991, 
//       0.0120751, 0.0114102, 0.0107982, 0.0102338, 0.00971228, 0.00922935, 
//       0.00878138};
//     TGraphErrors *gr_mod_mD2000 = new TGraphErrors(31,x_model,model_mD2000,0,0);



//    Float_t model_mD2000_2[101] = 
// {0.0594036, 0.0593987, 0.058684, 0.0558705, 0.0515447, 0.0467395, 
// 0.0420622, 0.0377737, 0.0339514, 0.030589, 0.0276467, 0.0250746, 
// 0.0228233, 0.0208475, 0.0191079, 0.0175707, 0.0162072, 0.0149932, 
// 0.0139084, 0.0129355, 0.0120601, 0.0112697, 0.0105539, 0.00990373, 
// 0.00931145, 0.00877047, 0.00827509, 0.00782036, 0.00740199, 
// 0.00701621, 0.00665975, 0.00632972, 0.00602359, 0.0057391, 
// 0.00547428, 0.00522734, 0.00499674, 0.00478104, 0.00457901, 
// 0.00438951, 0.00421154, 0.00404416, 0.00388657, 0.00373801, 
// 0.0035978, 0.00346534, 0.00334006, 0.00322145, 0.00310905, 
// 0.00300243, 0.00290121, 0.00280501, 0.00271353, 0.00262645, 
// 0.00254349, 0.00246441, 0.00238896, 0.00231692, 0.00224809, 
// 0.00218229, 0.00211933, 0.00205906, 0.00200133, 0.00194599, 
// 0.00189291, 0.00184198, 0.00179308, 0.0017461, 0.00170094, 
// 0.00165751, 0.00161573, 0.0015755, 0.00153676, 0.00149943, 
// 0.00146345, 0.00142875, 0.00139526, 0.00136294, 0.00133173, 
// 0.00130158, 0.00127245, 0.00124428, 0.00121704, 0.00119068, 
// 0.00116517, 0.00114047, 0.00111655, 0.00109337, 0.00107091, 
// 0.00104913, 0.00102801, 0.00100752, 0.00098764, 0.000968342, 
// 0.000949604, 0.000931405, 0.000913724, 0.000896541, 0.00087984, 
//  0.0008636, 0.000847807};
     
//    TGraphErrors *gr_mod_mD2000_2 = new TGraphErrors(101,x_model2,model_mD2000_2,0,0);


//    Float_t model_mD0850_2[101] = 
// {0.0623737, 0.0608305, 0.050566, 0.0394122, 0.0307956, 0.0244928, 
// 0.0198629, 0.0163994, 0.0137547, 0.0116951, 0.0100625, 0.0087477, 
// 0.0076738, 0.00678569, 0.00604302, 0.00541577, 0.00488126, 0.0044221, 
// 0.00402478, 0.00367869, 0.0033754, 0.00310812, 0.00287137, 
// 0.00266069, 0.00247237, 0.00230337, 0.00215112, 0.00201349, 
// 0.00188866, 0.00177509, 0.00167147, 0.00157667, 0.00148971, 
// 0.00140975, 0.00133607, 0.00126801, 0.00120503, 0.00114663, 
// 0.00109237, 0.00104188, 0.000994806, 0.000950855, 0.000909754, 
// 0.000871262, 0.000835163, 0.000801262, 0.000769385, 0.000739373, 
// 0.000711084, 0.000684389, 0.000659169, 0.000635318, 0.000612739, 
// 0.000591343, 0.000571048, 0.000551781, 0.000533473, 0.000516061, 
// 0.000499488, 0.000483701, 0.000468651, 0.000454293, 0.000440584, 
// 0.000427487, 0.000414966, 0.000402987, 0.000391519, 0.000380534, 
// 0.000370004, 0.000359906, 0.000350216, 0.000340912, 0.000331974, 
// 0.000323383, 0.000315121, 0.000307172, 0.00029952, 0.00029215, 
// 0.000285049, 0.000278204, 0.000271603, 0.000265233, 0.000259086, 
// 0.000253149, 0.000247414, 0.000241872, 0.000236515, 0.000231333, 
// 0.000226319, 0.000221467, 0.00021677, 0.00021222, 0.000207812, 
// 0.00020354, 0.000199398, 0.000195382, 0.000191485, 0.000187704, 
//  0.000184034, 0.000180471, 0.00017701};
     
//    TGraphErrors *gr_mod_mD0850_2 = new TGraphErrors(101,x_model2,model_mD0850_2,0,0);


//    Float_t model_mD0400_2[101] = 
// {0.0531662, 0.041831, 0.0247433, 0.0157255, 0.0107936, 0.00784948, 
// 0.00596042, 0.00467843, 0.00376929, 0.00310145, 0.00259656, 
// 0.00220563, 0.00189679, 0.00164856, 0.00144607, 0.00127872, 
// 0.00113884, 0.00102071, 0.000920065, 0.000833604, 0.000758784, 
// 0.000693605, 0.000636479, 0.000586132, 0.000541532, 0.000501836, 
// 0.000466351, 0.000434501, 0.000405807, 0.000379864, 0.000356332, 
// 0.000334921, 0.000315384, 0.000297508, 0.00028111, 0.000266031, 
// 0.000252134, 0.000239299, 0.000227419, 0.000216402, 0.000206167, 
// 0.000196642, 0.000187761, 0.000179469, 0.000171715, 0.000164452, 
// 0.000157641, 0.000151244, 0.000145229, 0.000139565, 0.000134227, 
// 0.000129189, 0.00012443, 0.000119929, 0.000115667, 0.000111629, 
// 0.000107799, 0.000104163, 0.000100707, 0.0000974208, 0.0000942928, 
// 0.000091313, 0.0000884723, 0.0000857621, 0.0000831746, 0.0000807024, 
// 0.0000783389, 0.0000760777, 0.0000739129, 0.0000718393, 0.0000698518, 
// 0.0000679456, 0.0000661164, 0.00006436, 0.0000626728, 0.000061051, 
// 0.0000594914, 0.0000579908, 0.0000565462, 0.000055155, 0.0000538145, 
// 0.0000525223, 0.0000512761, 0.0000500737, 0.0000489131, 0.0000477924, 
// 0.0000467097, 0.0000456635, 0.000044652, 0.0000436738, 0.0000427273, 
// 0.0000418113, 0.0000409244, 0.0000400655, 0.0000392333, 0.0000384268, 
//  0.0000376449, 0.0000368866, 0.000036151, 0.0000354372, 0.0000347443};
     
//    TGraphErrors *gr_mod_mD0400_2 = new TGraphErrors(101,x_model2,model_mD0400_2,0,0);


//    Float_t model_mD0700_2[101] = 
// {0.0623737, 0.0592116, 0.0455336, 0.0335743, 0.0252767, 0.0195817, 
// 0.0155722, 0.012663, 0.0104925, 0.00883284, 0.00753662, 0.00650549, 
// 0.00567204, 0.00498892, 0.0044221, 0.00394662, 0.00354389, 0.0031998, 
// 0.0029035, 0.00264653, 0.00242223, 0.00222529, 0.00205143, 
// 0.00189719, 0.00175971, 0.00163665, 0.00152607, 0.00142634, 
// 0.00133607, 0.00125411, 0.00117947, 0.0011113, 0.00104887, 
// 0.000991566, 0.000938831, 0.000890195, 0.000845244, 0.000803614, 
// 0.000764987, 0.000729079, 0.000695642, 0.000664454, 0.000635318, 
// 0.000608057, 0.000582515, 0.000558549, 0.000536032, 0.00051485, 
// 0.0004949, 0.000476087, 0.000458327, 0.000441543, 0.000425664, 
// 0.000410627, 0.000396373, 0.000382848, 0.000370004, 0.000357796, 
// 0.000346183, 0.000335125, 0.00032459, 0.000314543, 0.000304956, 
// 0.000295801, 0.000287051, 0.000278685, 0.000270679, 0.000263013, 
// 0.000255668, 0.000248627, 0.000241872, 0.00023539, 0.000229164, 
// 0.000223182, 0.000217432, 0.0002119, 0.000206578, 0.000201453, 
// 0.000196517, 0.00019176, 0.000187173, 0.00018275, 0.000178481, 
// 0.00017436, 0.00017038, 0.000166535, 0.000162819, 0.000159225, 
// 0.00015575, 0.000152387, 0.000149131, 0.000145979, 0.000142926, 
// 0.000139968, 0.0001371, 0.00013432, 0.000131623, 0.000129007, 
//  0.000126468, 0.000124004, 0.00012161};
     
//    TGraphErrors *gr_mod_mD0700_2 = new TGraphErrors(101,x_model2,model_mD0700_2,0,0);

//    Float_t model_mD1000_2[101] = 
// {0.0613837, 0.0606401, 0.0532626, 0.0434641, 0.0350829, 0.0285681, 
// 0.023584, 0.0197448, 0.0167473, 0.0143719, 0.0124621, 0.0109057, 
// 0.0096218, 0.0085509, 0.0076487, 0.00688173, 0.00622436, 0.00565674, 
// 0.00516328, 0.00473164, 0.00435191, 0.00401611, 0.00371772, 
// 0.00345139, 0.00321268, 0.00299791, 0.00280398, 0.00262827, 
// 0.00246859, 0.00232303, 0.00218997, 0.00206803, 0.00195601, 
// 0.00185284, 0.00175763, 0.00166958, 0.00158799, 0.00151223, 
// 0.00144177, 0.00137612, 0.00131486, 0.0012576, 0.001204, 0.00115376, 
// 0.0011066, 0.00106228, 0.00102056, 0.000981256, 0.00094418, 
// 0.000909167, 0.000876066, 0.000844741, 0.000815067, 0.000786929, 
// 0.000760225, 0.000734857, 0.000710738, 0.000687788, 0.000665932, 
// 0.000645102, 0.000625234, 0.00060627, 0.000588156, 0.000570843, 
// 0.000554282, 0.000538433, 0.000523253, 0.000508707, 0.000494759, 
// 0.000481377, 0.00046853, 0.000456192, 0.000444334, 0.000432933, 
// 0.000421965, 0.000411409, 0.000401244, 0.000391451, 0.000382012, 
// 0.000372911, 0.000364131, 0.000355658, 0.000347477, 0.000339576, 
// 0.00033194, 0.00032456, 0.000317423, 0.000310518, 0.000303837, 
// 0.000297369, 0.000291105, 0.000285038, 0.000279158, 0.000273458, 
// 0.000267931, 0.00026257, 0.000257368, 0.000252319, 0.000247417, 
//  0.000242657, 0.000238033};
     
//    TGraphErrors *gr_mod_mD1000_2 = new TGraphErrors(101,x_model2,model_mD1000_2,0,0);


//    Float_t model_mD1500_2[101] = 
// {0.0593892, 0.0593222, 0.0570198, 0.0515322, 0.045137, 0.0391433, 
// 0.0339431, 0.0295567, 0.0258877, 0.0228177, 0.0202383, 0.0180581, 
// 0.0162032, 0.0146146, 0.0132451, 0.0120572, 0.0110206, 0.0101112, 
// 0.00930919, 0.00859845, 0.00796577, 0.00740019, 0.00689261, 
// 0.0064354, 0.00602213, 0.00564736, 0.00530648, 0.00499553, 0.0047111, 
// 0.00445027, 0.00421052, 0.00398961, 0.00378565, 0.00359693, 
// 0.00342198, 0.00325948, 0.0031083, 0.00296739, 0.00283585, 
// 0.00271287, 0.00259772, 0.00248975, 0.00238838, 0.00229308, 
// 0.00220336, 0.00211882, 0.00203905, 0.0019637, 0.00189245, 
// 0.00182502, 0.00176112, 0.00170053, 0.00164301, 0.00158836, 
// 0.00153639, 0.00148693, 0.00143983, 0.00139492, 0.00135209, 
// 0.0013112, 0.00127214, 0.0012348, 0.00119908, 0.00116488, 0.00113213, 
// 0.00110075, 0.00107065, 0.00104177, 0.00101404, 0.000987402, 
// 0.000961802, 0.000937186, 0.000913503, 0.000890706, 0.000868753, 
// 0.000847601, 0.000827213, 0.000807552, 0.000788584, 0.000770277, 
// 0.0007526, 0.000735524, 0.000719023, 0.000703072, 0.000687646, 
// 0.000672722, 0.000658278, 0.000644295, 0.000630753, 0.000617634, 
// 0.000604919, 0.000592594, 0.000580641, 0.000569046, 0.000557796, 
// 0.000546876, 0.000536273, 0.000525976, 0.000515972, 0.000506252, 
//  0.000496803};
     
//    TGraphErrors *gr_mod_mD1500_2 = new TGraphErrors(101,x_model2,model_mD1500_2,0,0);


   
   
//    // TH2F *dummy4 = new TH2F("","",100,10E-2,10.,100,0.0,0.14);
//    //   TCanvas *c4 = new TCanvas("c4","c4",700,500);
//    //   c4->SetLogy();
//    //   c4->SetLogx();
//    //   //     dummy4->GetXaxis()->SetTitle("c#tau [mm]");
//    //   //     dummy4->GetYaxis()->SetTitle("#epsilon_{rec} = N_{rec}/N_{tot}");
//    //   //     dummy4->Draw();
//    //   //     dummy4->SetLogy();
//    //   //     dummy4->SetLogx();
//    //   gr_eff_mD0400_allcut->SetLineColor(2);
//    //   gr_eff_mD0400_allcut->SetMarkerColor(2);
//    //   //   gr_eff_mD0400_allcut->Draw("PL");
//    //   gr_eff_mD0400_final->SetLineColor(2);
//    //   gr_eff_mD0400_final->SetMarkerColor(2);
//    //   //   gr_eff_mD0400_final->SetMarkerStyle(24);
//    //   gr_eff_mD0400_final->SetLineWidth(2);
//    //   gr_eff_mD0400_final->Draw("AP");
//    //   gr_mod_mD0400->SetLineWidth(2);
//    //   gr_mod_mD0400->SetLineColor(2);
//    //   gr_mod_mD0400->Draw("Lsame");
//    //   //   gr_eff_mD0250_allcut->SetLineColor(1);
//    //   //      gr_eff_mD0250_allcut->SetMarkerColor(1);
//    //   //      gr_eff_mD0250_allcut->Draw("Psame");
//    //   gr_eff_mD0250_final->SetLineColor(1);
//    //   gr_eff_mD0250_final->SetMarkerColor(1);
//    //    //   gr_eff_mD0250_final->SetMarkerStyle(24);
//    //   //   gr_eff_mD0250_final->Draw("Psame");
//    //   gr_eff_mD0250_final->SetLineWidth(2);
//    //   gr_eff_mD0250_final->Draw("Psame");
//    //   gr_mod_mD0250->SetLineWidth(2);
//    //   gr_mod_mD0250->Draw("Lsame");
//    //   gr_eff_mD0250_final->SetLineStyle(1);
//    //   gr_eff_mD0700_allcut->SetLineColor(3);
//    //   gr_eff_mD0700_allcut->SetMarkerColor(3);
//    //   //   gr_eff_mD0700_allcut->Draw("Psame");
//    //   gr_eff_mD0700_final->SetLineColor(3);
//    //   gr_eff_mD0700_final->SetMarkerColor(3);
//    //   //   gr_eff_mD0700_final->SetMarkerStyle(24);
//    //   gr_eff_mD0700_final->SetLineWidth(2);
//    //   gr_eff_mD0700_final->Draw("Psame");
//    //   gr_mod_mD0700->SetLineWidth(2);
//    //   gr_mod_mD0700->SetLineColor(3);
//    //   gr_mod_mD0700->Draw("Lsame");

//    //   gr_eff_mD0850_allcut->SetLineColor(4);
//    //   gr_eff_mD0850_allcut->SetMarkerColor(4);
//    //   //   gr_eff_mD0850_allcut->Draw("Psame");
//    //   gr_eff_mD0850_final->SetLineColor(4);
//    //   gr_eff_mD0850_final->SetMarkerColor(4);
//    //   //   gr_eff_mD0850_final->SetMarkerStyle(24);
//    //   gr_eff_mD0850_final->SetLineWidth(2);
//    //   gr_eff_mD0850_final->Draw("Psame");
//    //   gr_mod_mD0850->SetLineWidth(2);
//    //   gr_mod_mD0850->SetLineColor(4);
//    //   gr_mod_mD0850->Draw("Lsame");

     

//    //   gr_eff_mD1000_allcut->SetLineColor(5);
//    //   gr_eff_mD1000_allcut->SetMarkerColor(5);
//    //   //   gr_eff_mD1000_allcut->Draw("Psame");
//    //   gr_eff_mD1000_final->SetLineColor(5);
//    //   gr_eff_mD1000_final->SetMarkerColor(5);
//    //   //   gr_eff_mD1000_final->SetMarkerStyle(24);
//    //   gr_eff_mD1000_final->SetLineWidth(2);
//    //   gr_eff_mD1000_final->Draw("Psame");
//    //   gr_mod_mD1000->SetLineWidth(2);
//    //   gr_mod_mD1000->SetLineColor(5);
//    //   gr_mod_mD1000->Draw("Lsame");

//    //   gr_eff_mD1500_allcut->SetLineColor(6);
//    //   gr_eff_mD1500_allcut->SetMarkerColor(6);
//    //   //   gr_eff_mD1500_allcut->Draw("Psame");
//    //   gr_eff_mD1500_final->SetLineColor(6);
//    //   gr_eff_mD1500_final->SetMarkerColor(6);
//    //   //   gr_eff_mD1500_final->SetMarkerStyle(24);
//    //   gr_eff_mD1500_final->SetLineWidth(2);
//    //   gr_eff_mD1500_final->Draw("Psame");
//    //   gr_mod_mD1500->SetLineWidth(2);
//    //   gr_mod_mD1500->SetLineColor(6);
//    //   gr_mod_mD1500->Draw("Lsame");

//    //   gr_eff_mD2000_allcut->SetLineColor(7);
//    //   gr_eff_mD2000_allcut->SetMarkerColor(7);
//    //   //   gr_eff_mD2000_allcut->Draw("Psame");
//    //   gr_eff_mD2000_final->SetLineColor(7);
//    //   gr_eff_mD2000_final->SetMarkerColor(7);
//    //   //   gr_eff_mD2000_final->SetMarkerStyle(24);
//    //   gr_eff_mD2000_final->SetLineWidth(2);
//    //   gr_eff_mD2000_final->Draw("Psame");
//    //   gr_mod_mD2000->SetLineWidth(2);
//    //   gr_mod_mD2000->SetLineColor(7);
//    //   gr_mod_mD2000->Draw("Lsame");
//    //   leg2->Draw("same");
//    //   c4->SaveAs("eff_final.pdf","recreate");
//    //   c4->SaveAs("eff_final.C","recreate");





//      TH2F *dummy4l = new TH2F("","",100,-0.2,100.2,100,-1.0,0.2);
//      TCanvas *c4l = new TCanvas("c4l","c4l",700,500);

//       // dummy4l->GetXaxis()->SetTitle("c#tau [mm]");
//       // dummy4l->GetYaxis()->SetTitle("#epsilon_{rec} = N_{rec}/N_{tot}");
//       // dummy4l->Draw();

//      c4l->SetLogy();
//      c4l->SetLogx();
//      gr_eff_mD0250_final2->GetXaxis()->SetTitle("c#tau [mm]");
//      gr_eff_mD0250_final2->GetYaxis()->SetTitle("#epsilon_{rec} = N_{rec}/N_{tot}");
     

//      gr_eff_mD0250_final2->SetLineColor(1);
//      gr_eff_mD0250_final2->SetMarkerColor(1);
//       //   gr_eff_mD0250_final->SetMarkerStyle(24);
//      //   gr_eff_mD0250_final->Draw("Psame");
//      gr_eff_mD0250_final2->SetLineWidth(2);
//      gr_eff_mD0250_final2->Draw("AP");
//      //     gr_eff_mD0250_final2->SetLineStyle(1);
//      // gr_mod_mD0250->SetLineWidth(2);
//      // gr_mod_mD0250->Draw("Lsame");

//      gr_mod_mD0250_2->SetLineWidth(2);
//      //     gr_mod_mD0250_2->SetLineStyle(2);
//      gr_mod_mD0250_2->Draw("Lsame");

//      gr_eff_mD0400_allcut->SetLineColor(2);
//      gr_eff_mD0400_allcut->SetMarkerColor(2);
//      //   gr_eff_mD0400_allcut->Draw("PL");
//      gr_eff_mD0400_final->SetLineColor(2);
//      gr_eff_mD0400_final->SetMarkerColor(2);
//      //   gr_eff_mD0400_final->SetMarkerStyle(24);
//      gr_eff_mD0400_final->SetLineWidth(2);
//      gr_eff_mD0400_final->Draw("P");

//      gr_mod_mD0400_2->SetLineWidth(2);
//      gr_mod_mD0400_2->SetLineColor(2);
//      gr_mod_mD0400_2->Draw("Lsame");
//      //   gr_eff_mD0250_allcut->SetLineColor(1);
//      //      gr_eff_mD0250_allcut->SetMarkerColor(1);
//      //      gr_eff_mD0250_allcut->Draw("Psame");


//      gr_eff_mD0700_allcut->SetLineColor(3);
//      gr_eff_mD0700_allcut->SetMarkerColor(3);
//      //   gr_eff_mD0700_allcut->Draw("Psame");
//      gr_eff_mD0700_final->SetLineColor(3);
//      gr_eff_mD0700_final->SetMarkerColor(3);
//      //   gr_eff_mD0700_final->SetMarkerStyle(24);
//      gr_eff_mD0700_final->SetLineWidth(2);
//      gr_eff_mD0700_final->Draw("Psame");

//      gr_mod_mD0700_2->SetLineWidth(2);
//      gr_mod_mD0700_2->SetLineColor(3);
//      gr_mod_mD0700_2->Draw("Lsame");

//      gr_eff_mD0850_allcut->SetLineColor(4);
//      gr_eff_mD0850_allcut->SetMarkerColor(4);
//      //   gr_eff_mD0850_allcut->Draw("Psame");
//      gr_eff_mD0850_final->SetLineColor(4);
//      gr_eff_mD0850_final->SetMarkerColor(4);
//      //   gr_eff_mD0850_final->SetMarkerStyle(24);
//      gr_eff_mD0850_final->SetLineWidth(2);
//      gr_eff_mD0850_final->Draw("Psame");
//      //     gr_mod_mD0850->SetLineWidth(2);
//      //     gr_mod_mD0850->SetLineColor(4);
//      //     gr_mod_mD0850->Draw("Lsame");

//      gr_mod_mD0850_2->SetLineWidth(2);
//      gr_mod_mD0850_2->SetLineColor(4);
//      //     gr_mod_mD0850_2->SetLineStyle(2);
//      gr_mod_mD0850_2->Draw("Lsame");

//      gr_eff_mD1000_allcut->SetLineColor(5);
//      gr_eff_mD1000_allcut->SetMarkerColor(5);
//      //   gr_eff_mD1000_allcut->Draw("Psame");
//      gr_eff_mD1000_final->SetLineColor(5);
//      gr_eff_mD1000_final->SetMarkerColor(5);
//      //   gr_eff_mD1000_final->SetMarkerStyle(24);
//      gr_eff_mD1000_final->SetLineWidth(2);
//      gr_eff_mD1000_final->Draw("Psame");

//      gr_mod_mD1000_2->SetLineWidth(2);
//      gr_mod_mD1000_2->SetLineColor(5);
//      gr_mod_mD1000_2->Draw("Lsame");

//      gr_eff_mD1500_allcut->SetLineColor(6);
//      gr_eff_mD1500_allcut->SetMarkerColor(6);
//      //   gr_eff_mD1500_allcut->Draw("Psame");
//      gr_eff_mD1500_final->SetLineColor(6);
//      gr_eff_mD1500_final->SetMarkerColor(6);
//      //   gr_eff_mD1500_final->SetMarkerStyle(24);
//      gr_eff_mD1500_final->SetLineWidth(2);
//      gr_eff_mD1500_final->Draw("Psame");

//      // gr_mod_mD1500->SetLineWidth(2);
//      // gr_mod_mD1500->SetLineColor(6);
//      // gr_mod_mD1500->Draw("Lsame");

//      gr_mod_mD1500_2->SetLineWidth(2);
//      gr_mod_mD1500_2->SetLineColor(6);
//      gr_mod_mD1500_2->Draw("Lsame");

//      gr_eff_mD2000_allcut->SetLineColor(7);
//      gr_eff_mD2000_allcut->SetMarkerColor(7);
//      //   gr_eff_mD2000_allcut->Draw("Psame");
//      gr_eff_mD2000_final->SetLineColor(7);
//      gr_eff_mD2000_final->SetMarkerColor(7);
//      //   gr_eff_mD2000_final->SetMarkerStyle(24);
//      gr_eff_mD2000_final->SetLineWidth(2);
//      gr_eff_mD2000_final->Draw("Psame");
//      // gr_mod_mD2000->SetLineWidth(2);
//      // gr_mod_mD2000->SetLineColor(7);
//      // gr_mod_mD2000->Draw("Lsame");

//      //     gr_mod_mD2000_2->SetLineStyle(2);
//      gr_mod_mD2000_2->SetLineWidth(2);
//      gr_mod_mD2000_2->SetLineColor(7);
//      gr_mod_mD2000_2->Draw("Lsame");

//      leg2->Draw("same");
//      c4l->SaveAs("eff_final_largectaulog.pdf","recreate");
//      c4l->SaveAs("eff_final_largectaulog.C","recreate");


//     // TCanvas *c4l2 = new TCanvas("c4l2","c4l2",700,500);

//     // dummy4l->GetXaxis()->SetTitle("c#tau [mm]");
//     // dummy4l->GetYaxis()->SetTitle("#epsilon_{rec} = N_{rec}/N_{tot}");
//     // dummy4l->Draw();

//     // //     c4l2->SetLogy();
//     // //     gr_eff_mD0250_final2->GetXaxis()->SetTitle("c#tau [mm]");
//     // //     gr_eff_mD0250_final2->GetYaxis()->SetTitle("#epsilon_{rec} = N_{rec}/N_{tot}");
     

//     //  gr_eff_mD0250_final2->SetLineColor(1);
//     //  gr_eff_mD0250_final2->SetMarkerColor(1);
//     //   //   gr_eff_mD0250_final->SetMarkerStyle(24);
//     //  //   gr_eff_mD0250_final->Draw("Psame");
//     //  gr_eff_mD0250_final2->SetLineWidth(2);
//     //  gr_eff_mD0250_final2->Draw("AP");
//     //  gr_eff_mD0250_final2->SetLineStyle(1);
//     //  gr_mod_mD0250->SetLineWidth(2);
//     //  gr_mod_mD0250->Draw("Lsame");

//     //  gr_mod_mD0250_2->SetLineWidth(2);
//     //  gr_mod_mD0250_2->SetLineStyle(2);
//     //  gr_mod_mD0250_2->Draw("Lsame");

//     //  gr_eff_mD0400_allcut->SetLineColor(2);
//     //  gr_eff_mD0400_allcut->SetMarkerColor(2);
//     //  //   gr_eff_mD0400_allcut->Draw("PL");
//     //  gr_eff_mD0400_final->SetLineColor(2);
//     //  gr_eff_mD0400_final->SetMarkerColor(2);
//     //  //   gr_eff_mD0400_final->SetMarkerStyle(24);
//     //  gr_eff_mD0400_final->SetLineWidth(2);
//     //  gr_eff_mD0400_final->Draw("P");
//     //  gr_mod_mD0400->SetLineWidth(2);
//     //  gr_mod_mD0400->SetLineColor(2);
//     //  gr_mod_mD0400->Draw("Lsame");
//     //  //   gr_eff_mD0250_allcut->SetLineColor(1);
//     //  //      gr_eff_mD0250_allcut->SetMarkerColor(1);
//     //  //      gr_eff_mD0250_allcut->Draw("Psame");


//     //  gr_eff_mD0700_allcut->SetLineColor(3);
//     //  gr_eff_mD0700_allcut->SetMarkerColor(3);
//     //  //   gr_eff_mD0700_allcut->Draw("Psame");
//     //  gr_eff_mD0700_final->SetLineColor(3);
//     //  gr_eff_mD0700_final->SetMarkerColor(3);
//     //  //   gr_eff_mD0700_final->SetMarkerStyle(24);
//     //  gr_eff_mD0700_final->SetLineWidth(2);
//     //  gr_eff_mD0700_final->Draw("Psame");
//     //  gr_mod_mD0700->SetLineWidth(2);
//     //  gr_mod_mD0700->SetLineColor(3);
//     //  gr_mod_mD0700->Draw("Lsame");

//     //  gr_eff_mD0850_allcut->SetLineColor(4);
//     //  gr_eff_mD0850_allcut->SetMarkerColor(4);
//     //  //   gr_eff_mD0850_allcut->Draw("Psame");
//     //  gr_eff_mD0850_final->SetLineColor(4);
//     //  gr_eff_mD0850_final->SetMarkerColor(4);
//     //  //   gr_eff_mD0850_final->SetMarkerStyle(24);
//     //  gr_eff_mD0850_final->SetLineWidth(2);
//     //  gr_eff_mD0850_final->Draw("Psame");
//     //  gr_mod_mD0850->SetLineWidth(2);
//     //  gr_mod_mD0850->SetLineColor(4);
//     //  gr_mod_mD0850->Draw("Lsame");

//     //  gr_eff_mD1000_allcut->SetLineColor(5);
//     //  gr_eff_mD1000_allcut->SetMarkerColor(5);
//     //  //   gr_eff_mD1000_allcut->Draw("Psame");
//     //  gr_eff_mD1000_final->SetLineColor(5);
//     //  gr_eff_mD1000_final->SetMarkerColor(5);
//     //  //   gr_eff_mD1000_final->SetMarkerStyle(24);
//     //  gr_eff_mD1000_final->SetLineWidth(2);
//     //  gr_eff_mD1000_final->Draw("Psame");
//     //  gr_mod_mD1000->SetLineWidth(2);
//     //  gr_mod_mD1000->SetLineColor(5);
//     //  gr_mod_mD1000->Draw("Lsame");

//     //  gr_eff_mD1500_allcut->SetLineColor(6);
//     //  gr_eff_mD1500_allcut->SetMarkerColor(6);
//     //  //   gr_eff_mD1500_allcut->Draw("Psame");
//     //  gr_eff_mD1500_final->SetLineColor(6);
//     //  gr_eff_mD1500_final->SetMarkerColor(6);
//     //  //   gr_eff_mD1500_final->SetMarkerStyle(24);
//     //  gr_eff_mD1500_final->SetLineWidth(2);
//     //  gr_eff_mD1500_final->Draw("Psame");
//     //  gr_mod_mD1500->SetLineWidth(2);
//     //  gr_mod_mD1500->SetLineColor(6);
//     //  gr_mod_mD1500->Draw("Lsame");

//     //  gr_eff_mD2000_allcut->SetLineColor(7);
//     //  gr_eff_mD2000_allcut->SetMarkerColor(7);
//     //  //   gr_eff_mD2000_allcut->Draw("Psame");
//     //  gr_eff_mD2000_final->SetLineColor(7);
//     //  gr_eff_mD2000_final->SetMarkerColor(7);
//     //  //   gr_eff_mD2000_final->SetMarkerStyle(24);
//     //  gr_eff_mD2000_final->SetLineWidth(2);
//     //  gr_eff_mD2000_final->Draw("Psame");
//     //  gr_mod_mD2000->SetLineWidth(2);
//     //  gr_mod_mD2000->SetLineColor(7);
//     //  gr_mod_mD2000->Draw("Lsame");
//     //  gr_mod_mD2000_2->SetLineStyle(2);
//     //  gr_mod_mD2000_2->SetLineWidth(2);
//     //  gr_mod_mD2000_2->SetLineColor(7);
//     //  gr_mod_mD2000_2->Draw("Lsame");

//     //  leg2->Draw("same");
//     //  c4l2->SaveAs("eff_final_largectaulin.pdf","recreate");








//     //  TCanvas *c44 = new TCanvas("c44","c44",700,500);
//     //  dummy4->GetXaxis()->SetTitle("c#tau [mm]");
//     //  dummy4->GetYaxis()->SetTitle("#epsilon_{rec}=N_{rec}/N_{tot}");
//     //  dummy4->Draw();
//     //  gr_eff_mD0400_allcut->SetLineColor(2);
//     //  gr_eff_mD0400_allcut->SetMarkerColor(2);
//     //  //   gr_eff_mD0400_allcut->Draw("PL");
//     //  gr_eff_mD0400_final->SetLineColor(2);
//     //  gr_eff_mD0400_final->SetMarkerColor(2);
//     //  //   gr_eff_mD0400_final->SetMarkerStyle(24);
//     //  gr_eff_mD0400_final->SetLineWidth(2);
//     //  gr_eff_mD0400_final->Draw("PL");
//     //  //   gr_eff_mD0250_allcut->SetLineColor(1);
//     //  //      gr_eff_mD0250_allcut->SetMarkerColor(1);
//     //  //      gr_eff_mD0250_allcut->Draw("Psame");
//     //  gr_eff_mD0250_final->SetLineColor(1);
//     //  gr_eff_mD0250_final->SetMarkerColor(1);
//     //   //   gr_eff_mD0250_final->SetMarkerStyle(24);
//     //  //   gr_eff_mD0250_final->Draw("Psame");
//     //  gr_eff_mD0250_final->SetLineWidth(2);
//     //  gr_eff_mD0250_final->Draw("PLsame");
//     //  gr_eff_mD0250_final->SetLineStyle(1);
//     //  gr_eff_mD0700_allcut->SetLineColor(3);
//     //  gr_eff_mD0700_allcut->SetMarkerColor(3);
//     //  //   gr_eff_mD0700_allcut->Draw("Psame");
//     //  gr_eff_mD0700_final->SetLineColor(3);
//     //  gr_eff_mD0700_final->SetMarkerColor(3);
//     //  //   gr_eff_mD0700_final->SetMarkerStyle(24);
//     //  gr_eff_mD0700_final->SetLineWidth(2);
//     //  gr_eff_mD0700_final->Draw("PLsame");

//     //  gr_eff_mD0850_allcut->SetLineColor(4);
//     //  gr_eff_mD0850_allcut->SetMarkerColor(4);
//     //  //   gr_eff_mD0850_allcut->Draw("Psame");
//     //  gr_eff_mD0850_final->SetLineColor(4);
//     //  gr_eff_mD0850_final->SetMarkerColor(4);
//     //  //   gr_eff_mD0850_final->SetMarkerStyle(24);
//     //  gr_eff_mD0850_final->SetLineWidth(2);
//     //  gr_eff_mD0850_final->Draw("PLsame");

//     //  gr_eff_mD1000_allcut->SetLineColor(5);
//     //  gr_eff_mD1000_allcut->SetMarkerColor(5);
//     //  //   gr_eff_mD1000_allcut->Draw("Psame");
//     //  gr_eff_mD1000_final->SetLineColor(5);
//     //  gr_eff_mD1000_final->SetMarkerColor(5);
//     //  //   gr_eff_mD1000_final->SetMarkerStyle(24);
//     //  gr_eff_mD1000_final->SetLineWidth(2);
//     //  gr_eff_mD1000_final->Draw("PLsame");

//     //  gr_eff_mD1500_allcut->SetLineColor(6);
//     //  gr_eff_mD1500_allcut->SetMarkerColor(6);
//     //  //   gr_eff_mD1500_allcut->Draw("Psame");
//     //  gr_eff_mD1500_final->SetLineColor(6);
//     //  gr_eff_mD1500_final->SetMarkerColor(6);
//     //  //   gr_eff_mD1500_final->SetMarkerStyle(24);
//     //  gr_eff_mD1500_final->SetLineWidth(2);
//     //  gr_eff_mD1500_final->Draw("PLsame");

//     //  gr_eff_mD2000_allcut->SetLineColor(7);
//     //  gr_eff_mD2000_allcut->SetMarkerColor(7);
//     //  //   gr_eff_mD2000_allcut->Draw("Psame");
//     //  gr_eff_mD2000_final->SetLineColor(7);
//     //  gr_eff_mD2000_final->SetMarkerColor(7);
//     //  //   gr_eff_mD2000_final->SetMarkerStyle(24);
//     //  gr_eff_mD2000_final->SetLineWidth(2);
//     //  gr_eff_mD2000_final->Draw("PLsame");
//     //  leg2->Draw("same");
//     //  c44->SaveAs("eff_final_ctau.pdf","recreate");



//     // // TCanvas *c1 = new TCanvas("c1","c1",700,500);
//     // // dummy3->GetXaxis()->SetTitle("c#tau [mm]");
//     // // dummy3->GetYaxis()->SetTitle("pixel hit efficiency");
//     // // dummy3->Draw();
//     // // gr_eff2->Draw("PL");
//     // // // gr_eff_recover2->SetLineStyle(2);
//     // // // gr_eff_recover2->Draw("PLsame");
//     // // c1->SaveAs("eff_recovery2.pdf","recreate");


//     // // TCanvas *c11 = new TCanvas("c11","c11",700,500);
//     // // dummy3->GetXaxis()->SetTitle("c#tau [mm]");
//     // // dummy3->GetYaxis()->SetTitle("pixel hit efficiency");
//     // // dummy3->Draw();
//     // // gr_eff2->Draw("PL");
//     // // gr_eff_recover2->SetLineStyle(2);
//     // // gr_eff_recover2->Draw("PLsame");
//     // // c11->SaveAs("eff_recovery22.pdf","recreate");

//     // // TCanvas *c111 = new TCanvas("c111","c111",700,500);
//     // // dummy3->GetXaxis()->SetTitle("c#tau [mm]");
//     // // dummy3->GetYaxis()->SetTitle("pixel hit efficiency");
//     // // dummy3->Draw();
//     // // //  gr_eff2->Draw("PL");
//     // // gr_eff_recover3->SetLineStyle(2);
//     // // gr_eff_recover3->Draw("PLsame");
//     // // c111->SaveAs("eff_recovery3.pdf","recreate");



}
     
