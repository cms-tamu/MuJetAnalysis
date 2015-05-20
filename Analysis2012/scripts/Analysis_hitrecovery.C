#include <iostream>
using namespace std;
#include <algorithm>    // std::max

void Analysis_hitrecovery(){
  

  TFile *f[50];
  
  TFile *f[0] = new TFile("DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_000_RAW2DIGI_L1Reco_RECO_v1_2012.root");

  // TFile *f[1] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_0400_ctauExp_05_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  // TFile *f[2] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_0400_ctauExp_2_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  // TFile *f[3] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_0400_ctauExp_5_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");

  // TFile *f[4] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_0250_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  // TFile *f[5] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_0250_ctauExp_02_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  // TFile *f[6] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_0250_ctauExp_05_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  // TFile *f[7] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_0250_ctauExp_1_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  // TFile *f[8] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_0250_ctauExp_2_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  // TFile *f[9] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_0250_ctauExp_3_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_alfredo_0.root");
  // //  TFile *f[9] = new TFile("~/DarkSUSY_mH_125_mGammaD_0250_ctauExp_3_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  // TFile *f[10] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_0250_ctauExp_5_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  
  // TFile *f[11] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_0700_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  // TFile *f[12] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_0700_ctauExp_05_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  // TFile *f[13] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_0700_ctauExp_2_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  // TFile *f[14] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_0700_ctauExp_5_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");

  // TFile *f[15] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_0850_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  // TFile *f[16] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_0850_ctauExp_05_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  // TFile *f[17] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_0850_ctauExp_5_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  
  // TFile *f[18] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_1000_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  // TFile *f[19] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_1000_ctauExp_05_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  // TFile *f[20] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_1000_ctauExp_2_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  // TFile *f[21] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_1000_ctauExp_5_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  
  // TFile *f[22] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_1500_ctauExp_02_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  // TFile *f[23] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_1500_ctauExp_05_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  // TFile *f[24] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_1500_ctauExp_2_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  // TFile *f[25] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_1500_ctauExp_5_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");

  // TFile *f[26] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_2000_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  // TFile *f[27] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_2000_ctauExp_02_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  // TFile *f[28] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_2000_ctauExp_05_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  // TFile *f[29] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_2000_ctauExp_2_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");

  // TFile *f[30] = new TFile("~/darkSUSYsamples_8TeV/MSSM_mH_090_mA_2000_Hto2Ato4mu_8TeV-pythia6_5312_GEN_v1_0.root");
  // TFile *f[31] = new TFile("~/darkSUSYsamples_8TeV/MSSM_mH_125_mA_0250_Hto2Ato4mu_8TeV-pythia6_5312_GEN_v1_0.root");
  // TFile *f[32] = new TFile("~/darkSUSYsamples_8TeV/MSSM_mH_125_mA_3550_Hto2Ato4mu_8TeV-pythia6_5312_GEN_v1_0.root");

  // TFile *f[33] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_0250_ctauExp_20_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  // TFile *f[34] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_0250_ctauExp_10_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  // TFile *f[35] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_2000_ctauExp_10_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");
  // TFile *f[36] = new TFile("~/darkSUSYsamples_8TeV/DarkSUSY_mH_125_mGammaD_2000_ctauExp_20_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_RECO_v1_0.root");

  // TFile *f[37] = new TFile("~/darkSUSYsamples_8TeV/MSSM_mH_125_mA_0500_Hto2Ato4mu_8TeV-pythia6_5312_GEN_v1_0.root");

 
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
  for(int p=0;p<1;p++){
    
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





   //  Float_t ctau[4]={0.2,0.5,2.0,5.0};

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
//     Float_t eff_mD0250_final2[10]={0.0};

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
//      TCanvas *c444 = new TCanvas("c444","c444",700,500);
//      dummy444->GetXaxis()->SetTitle("mass [GeV]");
//      dummy444->GetYaxis()->SetTitle("#epsilon_{rec}=N_{rec}/N_{tot}");
//      dummy444->Draw();
//      gr_eff_ctau0_final->SetLineColor(2);
//      gr_eff_ctau0_final->SetMarkerColor(2);
//      gr_eff_ctau0_final->SetLineWidth(2);
//      gr_eff_ctau0_final->Draw("PLsame");

//      gr_eff_ctau02_final->SetLineColor(3);
//      gr_eff_ctau02_final->SetMarkerColor(3);
//      gr_eff_ctau02_final->SetLineWidth(2);
//      gr_eff_ctau02_final->Draw("PLsame");

//      gr_eff_ctau05_final->SetLineColor(4);
//      gr_eff_ctau05_final->SetMarkerColor(4);
//      gr_eff_ctau05_final->SetLineWidth(2);
//      gr_eff_ctau05_final->Draw("PLsame");

//      gr_eff_ctau2_final->SetLineColor(5);
//      gr_eff_ctau2_final->SetMarkerColor(5);
//      gr_eff_ctau2_final->SetLineWidth(2);
//      gr_eff_ctau2_final->Draw("PLsame");

//      gr_eff_ctau5_final->SetLineColor(6);
//      gr_eff_ctau5_final->SetMarkerColor(6);
//      gr_eff_ctau5_final->SetLineWidth(2);
//      gr_eff_ctau5_final->Draw("PLsame");

//      leg222->Draw("same");
//      c444->SaveAs("eff_final_mass.pdf","recreate");



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

//      TGraphErrors *gr_eff_mD0250_final2 = new TGraphErrors(10,ctau2l,eff_mD0250_final2,0,erreff_mD0250_final2);
   

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


//     TH2F *dummy3 = new TH2F("","",100,-0.2,5.2,100,0.0,1.0);

//     TCanvas *c = new TCanvas("c","c",700,500);
//     dummy3->GetXaxis()->SetTitle("c#tau [mm]");
//     dummy3->GetYaxis()->SetTitle("#epsilon_{rec}/#alpha_{gen}");
//     dummy3->Draw();
//     gr_eff_mD0400_gt->SetLineWidth(2);
//     gr_eff_mD0400_gt->SetLineColor(2);
//     gr_eff_mD0400_gt->SetMarkerColor(2);
//     gr_eff_mD0400_gt->Draw("PL");
//     gr_eff_mD1000_gt->SetLineWidth(3);
//     gr_eff_mD1000_gt->SetLineColor(3);
//     gr_eff_mD1000_gt->SetMarkerColor(3);
//     gr_eff_mD1000_gt->Draw("PLsame");
//     gr_eff_mD1000_fvtx->SetLineWidth(3);
//     gr_eff_mD1000_fvtx->SetLineColor(3);
//     gr_eff_mD1000_fvtx->SetLineStyle(3);
//     gr_eff_mD1000_fvtx->SetMarkerColor(3);
//     gr_eff_mD1000_fvtx->Draw("PLsame");
//     // gr_eff_mD0400_gt->SetLineStyle(2);
//     // gr_eff_mD0400_gt->SetLineColor(2);
//     // gr_eff_mD0400_gt->SetMarkerColor(2);
//     // gr_eff_mD0400_gt->Draw("PLsame");
//     gr_eff_mD0400_fvtx->SetLineWidth(3);
//     gr_eff_mD0400_fvtx->SetLineStyle(3);
//     gr_eff_mD0400_fvtx->SetLineColor(2);
//     gr_eff_mD0400_fvtx->SetMarkerColor(2);
//     gr_eff_mD0400_fvtx->SetMarkerStyle(26);
//     gr_eff_mD0400_fvtx->Draw("PLsame");
//     gr_eff_mD0250->SetLineWidth(2);
//     gr_eff_mD0250->Draw("PLsame");
//     // gr_eff_mD0250_gt->SetLineStyle(2);
//     // gr_eff_mD0250_gt->Draw("PLsame");
//     gr_eff_mD0250_fvtx->SetLineStyle(3);
//     gr_eff_mD0250_fvtx->SetMarkerStyle(26);
//     gr_eff_mD0250_fvtx->Draw("PLsame");
//     leg->Draw("same");
//     c->SaveAs("eff_recover_newvertex.pdf","recreate");



//     TCanvas *cc = new TCanvas("cc","cc",700,500);
//     dummy3->GetXaxis()->SetTitle("c#tau [mm]");
//     dummy3->GetYaxis()->SetTitle("#epsilon_{rec}/#alpha_{gen}");
//     dummy3->Draw();
//     gr_eff_mD0400_gt->SetLineWidth(2);
//     gr_eff_mD0400_gt->SetLineColor(2);
//     gr_eff_mD0400_gt->SetMarkerColor(2);
//     gr_eff_mD0400_gt->Draw("PL");
//     gr_eff_mD1000_gt->SetLineWidth(3);
//     gr_eff_mD1000_gt->SetLineColor(3);
//     gr_eff_mD1000_gt->SetMarkerColor(3);
//     gr_eff_mD1000_gt->Draw("PLsame");
//     gr_eff_mD1000->SetLineWidth(3);
//     gr_eff_mD1000->SetLineColor(3);
//     gr_eff_mD1000->SetLineStyle(3);
//     gr_eff_mD1000->SetMarkerColor(3);
//     gr_eff_mD1000->Draw("PLsame");
//     // gr_eff_mD0400_gt->SetLineStyle(2);
//     // gr_eff_mD0400_gt->SetLineColor(2);
//     // gr_eff_mD0400_gt->SetMarkerColor(2);
//     // gr_eff_mD0400_gt->Draw("PLsame");
//     gr_eff_mD0400->SetLineWidth(3);
//     gr_eff_mD0400->SetLineStyle(3);
//     gr_eff_mD0400->SetLineColor(2);
//     gr_eff_mD0400->SetMarkerColor(2);
//     gr_eff_mD0400->SetMarkerStyle(26);
//     gr_eff_mD0400->Draw("PLsame");
//     gr_eff_mD0250_gt->SetLineWidth(2);
//     gr_eff_mD0250_gt->Draw("PLsame");
//     // gr_eff_mD0250_gt->SetLineStyle(2);
//     // gr_eff_mD0250_gt->Draw("PLsame");
//     gr_eff_mD0250->SetLineStyle(3);
//     gr_eff_mD0250->SetMarkerStyle(26);
//     gr_eff_mD0250->Draw("PLsame");
//     legg->Draw("same");
//     cc->SaveAs("eff_recover_matching.pdf","recreate");




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


//     TH2F *dummy3 = new TH2F("","",100,-0.2,5.2,100,0.0,1.0);
//     TCanvas *c1 = new TCanvas("c1","c1",700,500);
//     dummy3->GetXaxis()->SetTitle("c#tau [mm]");
//     dummy3->GetYaxis()->SetTitle("#epsilon_{full}/#alpha_{gen}");
//     dummy3->Draw();
//     gr_eff_mD0400_allcut->SetLineColor(2);
//     gr_eff_mD0400_allcut->SetMarkerColor(2);
//     gr_eff_mD0400_allcut->Draw("PL");
//     gr_eff_mD0400_allcutrecov->SetLineColor(2);
//     gr_eff_mD0400_allcutrecov->SetMarkerColor(2);
//     //   gr_eff_mD0400_allcutrecov->SetMarkerStyle(24);
//     //   gr_eff_mD0400_allcutrecov->Draw("PL");
//     gr_eff_mD0250_allcut->SetLineColor(1);
//     gr_eff_mD0250_allcut->SetMarkerColor(1);
//     gr_eff_mD0250_allcut->SetLineWidth(2);
//     gr_eff_mD0250_allcut->Draw("PLsame");
//     gr_eff_mD0250_allcutrecov->SetLineColor(1);
//     gr_eff_mD0250_allcutrecov->SetMarkerColor(1);
//     //   gr_eff_mD0250_allcutrecov->SetMarkerStyle(24);
//     //   gr_eff_mD0250_allcutrecov->Draw("PLsame");
//     gr_eff_mD0700_allcut->SetLineColor(3);
//     gr_eff_mD0700_allcut->SetMarkerColor(3);
//     gr_eff_mD0700_allcut->SetLineWidth(2);
//     gr_eff_mD0700_allcut->Draw("PLsame");
//     gr_eff_mD0700_allcutrecov->SetLineColor(3);
//     gr_eff_mD0700_allcutrecov->SetMarkerColor(3);
//     //   gr_eff_mD0700_allcutrecov->SetMarkerStyle(24);
//     //   gr_eff_mD0700_allcutrecov->Draw("PLsame");


//      gr_eff_mD0850_allcut->SetLineColor(4);
//      gr_eff_mD0850_allcut->SetMarkerColor(4);
//      gr_eff_mD0850_allcut->SetLineWidth(2);
//      gr_eff_mD0850_allcut->Draw("PLsame");
//      gr_eff_mD0850_allcutrecov->SetLineColor(4);
//      gr_eff_mD0850_allcutrecov->SetMarkerColor(4);
//      //   gr_eff_mD0850_allcutrecov->SetMarkerStyle(24);
//      //   gr_eff_mD0850_allcutrecov->Draw("PLsame");

//      gr_eff_mD1000_allcut->SetLineColor(5);
//      gr_eff_mD1000_allcut->SetMarkerColor(5);
//      gr_eff_mD1000_allcut->SetLineWidth(2);
//      gr_eff_mD1000_allcut->Draw("PLsame");
//      gr_eff_mD1000_allcutrecov->SetLineColor(5);
//      gr_eff_mD1000_allcutrecov->SetMarkerColor(5);
//      //   gr_eff_mD1000_allcutrecov->SetMarkerStyle(24);
//      //   gr_eff_mD1000_allcutrecov->Draw("PLsame");

//      gr_eff_mD1500_allcut->SetLineColor(6);
//      gr_eff_mD1500_allcut->SetMarkerColor(6);
//      gr_eff_mD1500_allcut->SetLineWidth(2);
//      gr_eff_mD1500_allcut->Draw("PLsame");
//      gr_eff_mD1500_allcutrecov->SetLineColor(6);
//      gr_eff_mD1500_allcutrecov->SetMarkerColor(6);
//      //   gr_eff_mD1500_allcutrecov->SetMarkerStyle(24);
//      //   gr_eff_mD1500_allcutrecov->Draw("PLsame");


//      gr_eff_mD2000_allcut->SetLineColor(7);
//      gr_eff_mD2000_allcut->SetMarkerColor(7);
//      gr_eff_mD2000_allcut->SetLineWidth(2);
//      gr_eff_mD2000_allcut->Draw("PLsame");
//      gr_eff_mD2000_allcutrecov->SetLineColor(7);
//      gr_eff_mD2000_allcutrecov->SetMarkerColor(7);
//      //   gr_eff_mD2000_allcutrecov->SetMarkerStyle(24);
//      //   gr_eff_mD2000_allcutrecov->Draw("PLsame");
//      leg22->Draw("same");
//      c1->SaveAs("eff_allcut.pdf","recreate");




//      TH2F *dummy3 = new TH2F("","",100,-0.2,5.2,100,0.0,1.0);
//      TCanvas *c2 = new TCanvas("c2","c2",700,500);
//      dummy3->GetXaxis()->SetTitle("c#tau [mm]");
//      dummy3->GetYaxis()->SetTitle("#epsilon_{full}/#alpha_{gen}");
//      dummy3->Draw();

//      gr_eff_mD0400_allcutrecov->SetLineColor(2);
//      gr_eff_mD0400_allcutrecov->SetLineWidth(2);
//      gr_eff_mD0400_allcutrecov->SetMarkerColor(2);
//      gr_eff_mD0400_allcutrecov->Draw("PL");

//      gr_eff_mD0250_allcutrecov->SetLineColor(1);
//      gr_eff_mD0250_allcutrecov->SetLineWidth(2);
//      gr_eff_mD0250_allcutrecov->SetMarkerColor(1);
//      gr_eff_mD0250_allcutrecov->Draw("PLsame");

//      gr_eff_mD0700_allcutrecov->SetLineColor(3);
//      gr_eff_mD0700_allcutrecov->SetLineWidth(2);
//      gr_eff_mD0700_allcutrecov->SetMarkerColor(3);
//      gr_eff_mD0700_allcutrecov->Draw("PLsame");


//      gr_eff_mD0850_allcutrecov->SetLineColor(4);
//      gr_eff_mD0850_allcutrecov->SetLineWidth(2);
//      gr_eff_mD0850_allcutrecov->SetMarkerColor(4);
//      gr_eff_mD0850_allcutrecov->Draw("PLsame");

//      gr_eff_mD1000_allcutrecov->SetMarkerColor(5);
//      gr_eff_mD1000_allcutrecov->SetLineColor(5);
//      gr_eff_mD1000_allcutrecov->SetLineWidth(2);
//      gr_eff_mD1000_allcutrecov->Draw("PLsame");

//      gr_eff_mD1500_allcutrecov->SetLineColor(6);
//      gr_eff_mD1500_allcutrecov->SetLineWidth(2);
//      gr_eff_mD1500_allcutrecov->SetMarkerColor(6);
//      gr_eff_mD1500_allcutrecov->Draw("PLsame");


//      gr_eff_mD2000_allcutrecov->SetLineColor(7);
//      gr_eff_mD2000_allcutrecov->SetLineWidth(2);
//      gr_eff_mD2000_allcutrecov->SetMarkerColor(7);
//      gr_eff_mD2000_allcutrecov->Draw("PLsame");


//      leg22->Draw("same");
//      c2->SaveAs("eff_recovery_allcut3.pdf","recreate");






//      TH2F *dummy3 = new TH2F("","",100,-0.2,5.2,100,0.0,1.0);
//      TCanvas *c3 = new TCanvas("c3","c3",700,500);
//      dummy3->GetXaxis()->SetTitle("c#tau [mm]");
//      dummy3->GetYaxis()->SetTitle("#epsilon_{full}/#alpha_{gen}");
//      dummy3->Draw();
//      gr_eff_mD0400_allcutrecov2->SetLineColor(2);
//      gr_eff_mD0400_allcutrecov2->SetMarkerColor(2);
//      gr_eff_mD0400_allcutrecov2->SetLineWidth(2);
//      gr_eff_mD0400_allcutrecov2->Draw("PL");

//      gr_eff_mD0250_allcutrecov2->SetLineColor(1);
//      gr_eff_mD0250_allcutrecov2->SetMarkerColor(1);
//      gr_eff_mD0250_allcutrecov2->SetLineWidth(2);
//      gr_eff_mD0250_allcutrecov2->Draw("PLsame");
//      gr_eff_mD0250_allcutrecov2->SetLineStyle(1);

//      gr_eff_mD0700_allcutrecov->SetLineColor(3);
//      gr_eff_mD0700_allcutrecov->SetMarkerColor(3);
//      gr_eff_mD0700_allcutrecov->SetLineWidth(2);
//      gr_eff_mD0700_allcutrecov->Draw("PLsame");


//      gr_eff_mD0850_allcutrecov->SetLineColor(4);
//      gr_eff_mD0850_allcutrecov->SetMarkerColor(4);
//      gr_eff_mD0850_allcutrecov->SetLineWidth(2);
//      gr_eff_mD0850_allcutrecov->Draw("PLsame");

//      gr_eff_mD1000_allcutrecov->SetLineColor(5);
//      gr_eff_mD1000_allcutrecov->SetMarkerColor(5);
//      gr_eff_mD1000_allcutrecov->SetLineWidth(2);
//      gr_eff_mD1000_allcutrecov->Draw("PLsame");

//      gr_eff_mD1500_allcutrecov->SetLineColor(6);
//      gr_eff_mD1500_allcutrecov->SetMarkerColor(6);
//      gr_eff_mD1500_allcutrecov->SetLineWidth(2);
//      gr_eff_mD1500_allcutrecov->Draw("PLsame");


//      gr_eff_mD2000_allcutrecov->SetLineColor(7);
//      gr_eff_mD2000_allcutrecov->SetMarkerColor(7);
//      gr_eff_mD2000_allcutrecov->SetLineWidth(2);
//      gr_eff_mD2000_allcutrecov->Draw("PLsame");
//      leg22->Draw("same");
//      c3->SaveAs("eff_recovery_allcut3.pdf","recreate");

//     Float_t x_model[31];
  
//     Float_t xin=0.0;
//     for(int k=0;k<31;k++){x_model[k]=xin;xin=xin+(5.0/30.0);}

//     Float_t x_model2[121];
  
//     Float_t xin=0.0;
//     for(int k=0;k<121;k++){x_model2[k]=xin;xin=xin+(100.0/120.0);}
  
//     Float_t model_mD0250[31] = 
//       {0.088055, 0.0580347, 0.0300059, 0.0178765, 0.0118104, 0.00837308, 
//        0.00624275, 0.0048327, 0.00385154, 0.00314149, 0.00261115, 
//        0.00220462, 0.00188616, 0.00163204, 0.00142603, 0.00125671, 
//        0.00111586, 0.000997423, 0.000896895, 0.000810836, 0.000736595, 
//        0.000672105, 0.000615728, 0.00056616, 0.000522345, 0.000483427, 
//        0.000448703, 0.00041759, 0.000389605, 0.000364341, 0.000341458};


//     TGraphErrors *gr_mod_mD0250 = new TGraphErrors(31,x_model,model_mD0250,0,0);


//     Float_t model_mD0250_2[121] = 
// {0.0876203, 0.00833174, 0.00259826, 0.00125051, 0.000732959, 
// 0.000481041, 0.000339772, 0.000252698, 0.000195264, 0.000155399, 
// 0.000126603, 0.000105129, 0.0000886887, 0.0000758237, 0.0000655677, 
// 0.0000572602, 0.000050437, 0.0000447646, 0.0000399979, 0.000035954, 
// 0.0000324937, 0.00002951, 0.0000269191, 0.000024655, 0.000022665, 
// 0.0000209066, 0.0000193451, 0.0000179523, 0.0000167046, 0.0000155827, 
// 0.00001457, 0.000013653, 0.0000128199, 0.0000120608, 0.0000113672, 
//  0.0000107317, 0.0000101481, 9.6108E-6, 9.11509E-6, 
//  8.65675E-6, 8.23214E-6, 7.83802E-6, 7.47154E-6, 
//  7.13018E-6, 6.81169E-6, 6.51407E-6, 6.23553E-6, 
//  5.97449E-6, 5.7295E-6, 5.49928E-6, 5.28266E-6, 
//  5.0786E-6, 4.88613E-6, 4.7044E-6, 4.53262E-6, 
//  4.37009E-6, 4.21614E-6, 4.07018E-6, 3.93168E-6, 
//  3.80012E-6, 3.67506E-6, 3.55608E-6, 3.44278E-6, 
//  3.33481E-6, 3.23184E-6, 3.13357E-6, 3.03971E-6, 
//  2.95E-6, 2.86421E-6, 2.78211E-6, 2.70349E-6, 
//  2.62816E-6, 2.55593E-6, 2.48663E-6, 2.42012E-6, 
//  2.35624E-6, 2.29486E-6, 2.23585E-6, 2.17908E-6, 
//  2.12445E-6, 2.07184E-6, 2.02117E-6, 1.97233E-6, 
//  1.92524E-6, 1.87982E-6, 1.83599E-6, 1.79367E-6, 
//  1.7528E-6, 1.71331E-6, 1.67514E-6, 1.63823E-6, 
//  1.60253E-6, 1.56798E-6, 1.53454E-6, 1.50215E-6, 
//  1.47078E-6, 1.44039E-6, 1.41092E-6, 1.38235E-6, 
//  1.35464E-6, 1.32776E-6, 1.30166E-6, 1.27633E-6, 
//  1.25173E-6, 1.22784E-6, 1.20462E-6, 1.18206E-6, 
//  1.16012E-6, 1.13879E-6, 1.11804E-6, 1.09786E-6, 
//  1.07821E-6, 1.05909E-6, 1.04047E-6, 1.02234E-6, 
//  1.00468E-6, 9.87471E-7, 9.70701E-7, 9.54355E-7, 
//  9.38419E-7, 9.22879E-7};
    


//     TGraphErrors *gr_mod_mD0250_2 = new TGraphErrors(121,x_model2,model_mD0250_2,0,0);



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



//    Float_t model_mD2000_2[121] = 
// {0.0594036, 0.0507552, 0.0327811, 0.0218036, 0.0153826, 0.011396, 
//  0.00877047, 0.00695485, 0.00564873, 0.00467839, 0.00393806, 
//  0.00336046, 0.00290121, 0.00253005, 0.00222583, 0.00197337, 
//  0.00176155, 0.0015821, 0.00142875, 0.00129666, 0.00118208, 
//  0.00108205, 0.000994202, 0.000916635, 0.000847807, 0.00078645, 
//  0.000731523, 0.000682156, 0.000637624, 0.000597316, 0.000560713, 
//  0.000527374, 0.000496924, 0.000469037, 0.000443433, 0.000419871, 
//  0.000398138, 0.00037805, 0.000359445, 0.00034218, 0.000326131, 
//  0.000311184, 0.000297243, 0.000284217, 0.00027203, 0.00026061, 
//  0.000249894, 0.000239826, 0.000230355, 0.000221434, 0.000213021,
//  0.000205079, 0.000197572, 0.000190471, 0.000183746, 0.00017737, 
//  0.000171321, 0.000165576, 0.000160116, 0.000154921, 0.000149975, 
//  0.000145262, 0.000140767, 0.000136479, 0.000132383, 0.000128469, 
//  0.000124726, 0.000121144, 0.000117714, 0.000114428, 0.000111278, 
//  0.000108256, 0.000105355, 0.00010257, 0.0000998932, 0.0000973201, 
//  0.0000948452, 0.0000924635, 0.0000901704, 0.0000879616, 0.0000858329, 
//  0.0000837806, 0.0000818011, 0.0000798909, 0.0000780468, 0.0000762658, 
//  0.0000745451, 0.000072882, 0.000071274, 0.0000697186, 0.0000682135, 
//  0.0000667567, 0.000065346, 0.0000639796, 0.0000626556, 0.0000613723, 
//  0.000060128, 0.0000589212, 0.0000577503, 0.000056614, 0.0000555109, 
//  0.0000544398, 0.0000533993, 0.0000523884, 0.000051406, 0.0000504509, 
//  0.0000495222, 0.0000486189, 0.0000477401, 0.0000468849, 0.0000460524, 
//  0.000045242, 0.0000444528, 0.000043684, 0.000042935, 0.0000422051, 
//  0.0000414937, 0.0000408001, 0.0000401237, 0.0000394641, 0.0000388205};

//    TGraphErrors *gr_mod_mD2000_2 = new TGraphErrors(121,x_model2,model_mD2000_2,0,0);



//      TH2F *dummy4 = new TH2F("","",100,-0.2,5.2,100,0.0,0.12);
//      TCanvas *c4 = new TCanvas("c4","c4",700,500);
//      dummy4->GetXaxis()->SetTitle("c#tau [mm]");
//      dummy4->GetYaxis()->SetTitle("#epsilon_{rec} = N_{rec}/N_{tot}");
//      dummy4->Draw();
//      gr_eff_mD0400_allcut->SetLineColor(2);
//      gr_eff_mD0400_allcut->SetMarkerColor(2);
//      //   gr_eff_mD0400_allcut->Draw("PL");
//      gr_eff_mD0400_final->SetLineColor(2);
//      gr_eff_mD0400_final->SetMarkerColor(2);
//      //   gr_eff_mD0400_final->SetMarkerStyle(24);
//      gr_eff_mD0400_final->SetLineWidth(2);
//      gr_eff_mD0400_final->Draw("P");
//      gr_mod_mD0400->SetLineWidth(2);
//      gr_mod_mD0400->SetLineColor(2);
//      gr_mod_mD0400->Draw("Lsame");
//      //   gr_eff_mD0250_allcut->SetLineColor(1);
//      //      gr_eff_mD0250_allcut->SetMarkerColor(1);
//      //      gr_eff_mD0250_allcut->Draw("Psame");
//      gr_eff_mD0250_final->SetLineColor(1);
//      gr_eff_mD0250_final->SetMarkerColor(1);
//       //   gr_eff_mD0250_final->SetMarkerStyle(24);
//      //   gr_eff_mD0250_final->Draw("Psame");
//      gr_eff_mD0250_final->SetLineWidth(2);
//      gr_eff_mD0250_final->Draw("Psame");
//      gr_mod_mD0250->SetLineWidth(2);
//      gr_mod_mD0250->Draw("Lsame");
//      gr_eff_mD0250_final->SetLineStyle(1);
//      gr_eff_mD0700_allcut->SetLineColor(3);
//      gr_eff_mD0700_allcut->SetMarkerColor(3);
//      //   gr_eff_mD0700_allcut->Draw("Psame");
//      gr_eff_mD0700_final->SetLineColor(3);
//      gr_eff_mD0700_final->SetMarkerColor(3);
//      //   gr_eff_mD0700_final->SetMarkerStyle(24);
//      gr_eff_mD0700_final->SetLineWidth(2);
//      gr_eff_mD0700_final->Draw("Psame");
//      gr_mod_mD0700->SetLineWidth(2);
//      gr_mod_mD0700->SetLineColor(3);
//      gr_mod_mD0700->Draw("Lsame");

//      gr_eff_mD0850_allcut->SetLineColor(4);
//      gr_eff_mD0850_allcut->SetMarkerColor(4);
//      //   gr_eff_mD0850_allcut->Draw("Psame");
//      gr_eff_mD0850_final->SetLineColor(4);
//      gr_eff_mD0850_final->SetMarkerColor(4);
//      //   gr_eff_mD0850_final->SetMarkerStyle(24);
//      gr_eff_mD0850_final->SetLineWidth(2);
//      gr_eff_mD0850_final->Draw("Psame");
//      gr_mod_mD0850->SetLineWidth(2);
//      gr_mod_mD0850->SetLineColor(4);
//      gr_mod_mD0850->Draw("Lsame");

//      gr_eff_mD1000_allcut->SetLineColor(5);
//      gr_eff_mD1000_allcut->SetMarkerColor(5);
//      //   gr_eff_mD1000_allcut->Draw("Psame");
//      gr_eff_mD1000_final->SetLineColor(5);
//      gr_eff_mD1000_final->SetMarkerColor(5);
//      //   gr_eff_mD1000_final->SetMarkerStyle(24);
//      gr_eff_mD1000_final->SetLineWidth(2);
//      gr_eff_mD1000_final->Draw("Psame");
//      gr_mod_mD1000->SetLineWidth(2);
//      gr_mod_mD1000->SetLineColor(5);
//      gr_mod_mD1000->Draw("Lsame");

//      gr_eff_mD1500_allcut->SetLineColor(6);
//      gr_eff_mD1500_allcut->SetMarkerColor(6);
//      //   gr_eff_mD1500_allcut->Draw("Psame");
//      gr_eff_mD1500_final->SetLineColor(6);
//      gr_eff_mD1500_final->SetMarkerColor(6);
//      //   gr_eff_mD1500_final->SetMarkerStyle(24);
//      gr_eff_mD1500_final->SetLineWidth(2);
//      gr_eff_mD1500_final->Draw("Psame");
//      gr_mod_mD1500->SetLineWidth(2);
//      gr_mod_mD1500->SetLineColor(6);
//      gr_mod_mD1500->Draw("Lsame");

//      gr_eff_mD2000_allcut->SetLineColor(7);
//      gr_eff_mD2000_allcut->SetMarkerColor(7);
//      //   gr_eff_mD2000_allcut->Draw("Psame");
//      gr_eff_mD2000_final->SetLineColor(7);
//      gr_eff_mD2000_final->SetMarkerColor(7);
//      //   gr_eff_mD2000_final->SetMarkerStyle(24);
//      gr_eff_mD2000_final->SetLineWidth(2);
//      gr_eff_mD2000_final->Draw("Psame");
//      gr_mod_mD2000->SetLineWidth(2);
//      gr_mod_mD2000->SetLineColor(7);
//      gr_mod_mD2000->Draw("Lsame");
//      leg2->Draw("same");
//      c4->SaveAs("eff_final.pdf","recreate");
//      c4->SaveAs("eff_final.C","recreate");





//      TH2F *dummy4l = new TH2F("","",100,-0.2,100.2,100,-1.0,0.2);
//      TCanvas *c4l = new TCanvas("c4l","c4l",700,500);

//       // dummy4l->GetXaxis()->SetTitle("c#tau [mm]");
//       // dummy4l->GetYaxis()->SetTitle("#epsilon_{rec} = N_{rec}/N_{tot}");
//       // dummy4l->Draw();

//      c4l->SetLogy();
//      gr_eff_mD0250_final2->GetXaxis()->SetTitle("c#tau [mm]");
//      gr_eff_mD0250_final2->GetYaxis()->SetTitle("#epsilon_{rec} = N_{rec}/N_{tot}");
     

//      gr_eff_mD0250_final2->SetLineColor(1);
//      gr_eff_mD0250_final2->SetMarkerColor(1);
//       //   gr_eff_mD0250_final->SetMarkerStyle(24);
//      //   gr_eff_mD0250_final->Draw("Psame");
//      gr_eff_mD0250_final2->SetLineWidth(2);
//      gr_eff_mD0250_final2->Draw("AP");
//      gr_eff_mD0250_final2->SetLineStyle(1);
//      gr_mod_mD0250->SetLineWidth(2);
//      gr_mod_mD0250->Draw("Lsame");

//      gr_mod_mD0250_2->SetLineWidth(2);
//      gr_mod_mD0250_2->SetLineStyle(2);
//      gr_mod_mD0250_2->Draw("Lsame");

//      gr_eff_mD0400_allcut->SetLineColor(2);
//      gr_eff_mD0400_allcut->SetMarkerColor(2);
//      //   gr_eff_mD0400_allcut->Draw("PL");
//      gr_eff_mD0400_final->SetLineColor(2);
//      gr_eff_mD0400_final->SetMarkerColor(2);
//      //   gr_eff_mD0400_final->SetMarkerStyle(24);
//      gr_eff_mD0400_final->SetLineWidth(2);
//      gr_eff_mD0400_final->Draw("P");
//      gr_mod_mD0400->SetLineWidth(2);
//      gr_mod_mD0400->SetLineColor(2);
//      gr_mod_mD0400->Draw("Lsame");
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
//      gr_mod_mD0700->SetLineWidth(2);
//      gr_mod_mD0700->SetLineColor(3);
//      gr_mod_mD0700->Draw("Lsame");

//      gr_eff_mD0850_allcut->SetLineColor(4);
//      gr_eff_mD0850_allcut->SetMarkerColor(4);
//      //   gr_eff_mD0850_allcut->Draw("Psame");
//      gr_eff_mD0850_final->SetLineColor(4);
//      gr_eff_mD0850_final->SetMarkerColor(4);
//      //   gr_eff_mD0850_final->SetMarkerStyle(24);
//      gr_eff_mD0850_final->SetLineWidth(2);
//      gr_eff_mD0850_final->Draw("Psame");
//      gr_mod_mD0850->SetLineWidth(2);
//      gr_mod_mD0850->SetLineColor(4);
//      gr_mod_mD0850->Draw("Lsame");

//      gr_eff_mD1000_allcut->SetLineColor(5);
//      gr_eff_mD1000_allcut->SetMarkerColor(5);
//      //   gr_eff_mD1000_allcut->Draw("Psame");
//      gr_eff_mD1000_final->SetLineColor(5);
//      gr_eff_mD1000_final->SetMarkerColor(5);
//      //   gr_eff_mD1000_final->SetMarkerStyle(24);
//      gr_eff_mD1000_final->SetLineWidth(2);
//      gr_eff_mD1000_final->Draw("Psame");
//      gr_mod_mD1000->SetLineWidth(2);
//      gr_mod_mD1000->SetLineColor(5);
//      gr_mod_mD1000->Draw("Lsame");

//      gr_eff_mD1500_allcut->SetLineColor(6);
//      gr_eff_mD1500_allcut->SetMarkerColor(6);
//      //   gr_eff_mD1500_allcut->Draw("Psame");
//      gr_eff_mD1500_final->SetLineColor(6);
//      gr_eff_mD1500_final->SetMarkerColor(6);
//      //   gr_eff_mD1500_final->SetMarkerStyle(24);
//      gr_eff_mD1500_final->SetLineWidth(2);
//      gr_eff_mD1500_final->Draw("Psame");
//      gr_mod_mD1500->SetLineWidth(2);
//      gr_mod_mD1500->SetLineColor(6);
//      gr_mod_mD1500->Draw("Lsame");

//      gr_eff_mD2000_allcut->SetLineColor(7);
//      gr_eff_mD2000_allcut->SetMarkerColor(7);
//      //   gr_eff_mD2000_allcut->Draw("Psame");
//      gr_eff_mD2000_final->SetLineColor(7);
//      gr_eff_mD2000_final->SetMarkerColor(7);
//      //   gr_eff_mD2000_final->SetMarkerStyle(24);
//      gr_eff_mD2000_final->SetLineWidth(2);
//      gr_eff_mD2000_final->Draw("Psame");
//      gr_mod_mD2000->SetLineWidth(2);
//      gr_mod_mD2000->SetLineColor(7);
//      gr_mod_mD2000->Draw("Lsame");
//      gr_mod_mD2000_2->SetLineStyle(2);
//      gr_mod_mD2000_2->SetLineWidth(2);
//      gr_mod_mD2000_2->SetLineColor(7);
//      gr_mod_mD2000_2->Draw("Lsame");

//      leg2->Draw("same");
//      c4l->SaveAs("eff_final_largectaulog.pdf","recreate");
//      c4l->SaveAs("eff_final_largectaulog.C","recreate");


//     TCanvas *c4l2 = new TCanvas("c4l2","c4l2",700,500);

//     dummy4l->GetXaxis()->SetTitle("c#tau [mm]");
//     dummy4l->GetYaxis()->SetTitle("#epsilon_{rec} = N_{rec}/N_{tot}");
//     dummy4l->Draw();

//     //     c4l2->SetLogy();
//     //     gr_eff_mD0250_final2->GetXaxis()->SetTitle("c#tau [mm]");
//     //     gr_eff_mD0250_final2->GetYaxis()->SetTitle("#epsilon_{rec} = N_{rec}/N_{tot}");
     

//      gr_eff_mD0250_final2->SetLineColor(1);
//      gr_eff_mD0250_final2->SetMarkerColor(1);
//       //   gr_eff_mD0250_final->SetMarkerStyle(24);
//      //   gr_eff_mD0250_final->Draw("Psame");
//      gr_eff_mD0250_final2->SetLineWidth(2);
//      gr_eff_mD0250_final2->Draw("AP");
//      gr_eff_mD0250_final2->SetLineStyle(1);
//      gr_mod_mD0250->SetLineWidth(2);
//      gr_mod_mD0250->Draw("Lsame");

//      gr_mod_mD0250_2->SetLineWidth(2);
//      gr_mod_mD0250_2->SetLineStyle(2);
//      gr_mod_mD0250_2->Draw("Lsame");

//      gr_eff_mD0400_allcut->SetLineColor(2);
//      gr_eff_mD0400_allcut->SetMarkerColor(2);
//      //   gr_eff_mD0400_allcut->Draw("PL");
//      gr_eff_mD0400_final->SetLineColor(2);
//      gr_eff_mD0400_final->SetMarkerColor(2);
//      //   gr_eff_mD0400_final->SetMarkerStyle(24);
//      gr_eff_mD0400_final->SetLineWidth(2);
//      gr_eff_mD0400_final->Draw("P");
//      gr_mod_mD0400->SetLineWidth(2);
//      gr_mod_mD0400->SetLineColor(2);
//      gr_mod_mD0400->Draw("Lsame");
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
//      gr_mod_mD0700->SetLineWidth(2);
//      gr_mod_mD0700->SetLineColor(3);
//      gr_mod_mD0700->Draw("Lsame");

//      gr_eff_mD0850_allcut->SetLineColor(4);
//      gr_eff_mD0850_allcut->SetMarkerColor(4);
//      //   gr_eff_mD0850_allcut->Draw("Psame");
//      gr_eff_mD0850_final->SetLineColor(4);
//      gr_eff_mD0850_final->SetMarkerColor(4);
//      //   gr_eff_mD0850_final->SetMarkerStyle(24);
//      gr_eff_mD0850_final->SetLineWidth(2);
//      gr_eff_mD0850_final->Draw("Psame");
//      gr_mod_mD0850->SetLineWidth(2);
//      gr_mod_mD0850->SetLineColor(4);
//      gr_mod_mD0850->Draw("Lsame");

//      gr_eff_mD1000_allcut->SetLineColor(5);
//      gr_eff_mD1000_allcut->SetMarkerColor(5);
//      //   gr_eff_mD1000_allcut->Draw("Psame");
//      gr_eff_mD1000_final->SetLineColor(5);
//      gr_eff_mD1000_final->SetMarkerColor(5);
//      //   gr_eff_mD1000_final->SetMarkerStyle(24);
//      gr_eff_mD1000_final->SetLineWidth(2);
//      gr_eff_mD1000_final->Draw("Psame");
//      gr_mod_mD1000->SetLineWidth(2);
//      gr_mod_mD1000->SetLineColor(5);
//      gr_mod_mD1000->Draw("Lsame");

//      gr_eff_mD1500_allcut->SetLineColor(6);
//      gr_eff_mD1500_allcut->SetMarkerColor(6);
//      //   gr_eff_mD1500_allcut->Draw("Psame");
//      gr_eff_mD1500_final->SetLineColor(6);
//      gr_eff_mD1500_final->SetMarkerColor(6);
//      //   gr_eff_mD1500_final->SetMarkerStyle(24);
//      gr_eff_mD1500_final->SetLineWidth(2);
//      gr_eff_mD1500_final->Draw("Psame");
//      gr_mod_mD1500->SetLineWidth(2);
//      gr_mod_mD1500->SetLineColor(6);
//      gr_mod_mD1500->Draw("Lsame");

//      gr_eff_mD2000_allcut->SetLineColor(7);
//      gr_eff_mD2000_allcut->SetMarkerColor(7);
//      //   gr_eff_mD2000_allcut->Draw("Psame");
//      gr_eff_mD2000_final->SetLineColor(7);
//      gr_eff_mD2000_final->SetMarkerColor(7);
//      //   gr_eff_mD2000_final->SetMarkerStyle(24);
//      gr_eff_mD2000_final->SetLineWidth(2);
//      gr_eff_mD2000_final->Draw("Psame");
//      gr_mod_mD2000->SetLineWidth(2);
//      gr_mod_mD2000->SetLineColor(7);
//      gr_mod_mD2000->Draw("Lsame");
//      gr_mod_mD2000_2->SetLineStyle(2);
//      gr_mod_mD2000_2->SetLineWidth(2);
//      gr_mod_mD2000_2->SetLineColor(7);
//      gr_mod_mD2000_2->Draw("Lsame");

//      leg2->Draw("same");
//      c4l2->SaveAs("eff_final_largectaulin.pdf","recreate");








//      TCanvas *c44 = new TCanvas("c44","c44",700,500);
//      dummy4->GetXaxis()->SetTitle("c#tau [mm]");
//      dummy4->GetYaxis()->SetTitle("#epsilon_{rec}=N_{rec}/N_{tot}");
//      dummy4->Draw();
//      gr_eff_mD0400_allcut->SetLineColor(2);
//      gr_eff_mD0400_allcut->SetMarkerColor(2);
//      //   gr_eff_mD0400_allcut->Draw("PL");
//      gr_eff_mD0400_final->SetLineColor(2);
//      gr_eff_mD0400_final->SetMarkerColor(2);
//      //   gr_eff_mD0400_final->SetMarkerStyle(24);
//      gr_eff_mD0400_final->SetLineWidth(2);
//      gr_eff_mD0400_final->Draw("PL");
//      //   gr_eff_mD0250_allcut->SetLineColor(1);
//      //      gr_eff_mD0250_allcut->SetMarkerColor(1);
//      //      gr_eff_mD0250_allcut->Draw("Psame");
//      gr_eff_mD0250_final->SetLineColor(1);
//      gr_eff_mD0250_final->SetMarkerColor(1);
//       //   gr_eff_mD0250_final->SetMarkerStyle(24);
//      //   gr_eff_mD0250_final->Draw("Psame");
//      gr_eff_mD0250_final->SetLineWidth(2);
//      gr_eff_mD0250_final->Draw("PLsame");
//      gr_eff_mD0250_final->SetLineStyle(1);
//      gr_eff_mD0700_allcut->SetLineColor(3);
//      gr_eff_mD0700_allcut->SetMarkerColor(3);
//      //   gr_eff_mD0700_allcut->Draw("Psame");
//      gr_eff_mD0700_final->SetLineColor(3);
//      gr_eff_mD0700_final->SetMarkerColor(3);
//      //   gr_eff_mD0700_final->SetMarkerStyle(24);
//      gr_eff_mD0700_final->SetLineWidth(2);
//      gr_eff_mD0700_final->Draw("PLsame");

//      gr_eff_mD0850_allcut->SetLineColor(4);
//      gr_eff_mD0850_allcut->SetMarkerColor(4);
//      //   gr_eff_mD0850_allcut->Draw("Psame");
//      gr_eff_mD0850_final->SetLineColor(4);
//      gr_eff_mD0850_final->SetMarkerColor(4);
//      //   gr_eff_mD0850_final->SetMarkerStyle(24);
//      gr_eff_mD0850_final->SetLineWidth(2);
//      gr_eff_mD0850_final->Draw("PLsame");

//      gr_eff_mD1000_allcut->SetLineColor(5);
//      gr_eff_mD1000_allcut->SetMarkerColor(5);
//      //   gr_eff_mD1000_allcut->Draw("Psame");
//      gr_eff_mD1000_final->SetLineColor(5);
//      gr_eff_mD1000_final->SetMarkerColor(5);
//      //   gr_eff_mD1000_final->SetMarkerStyle(24);
//      gr_eff_mD1000_final->SetLineWidth(2);
//      gr_eff_mD1000_final->Draw("PLsame");

//      gr_eff_mD1500_allcut->SetLineColor(6);
//      gr_eff_mD1500_allcut->SetMarkerColor(6);
//      //   gr_eff_mD1500_allcut->Draw("Psame");
//      gr_eff_mD1500_final->SetLineColor(6);
//      gr_eff_mD1500_final->SetMarkerColor(6);
//      //   gr_eff_mD1500_final->SetMarkerStyle(24);
//      gr_eff_mD1500_final->SetLineWidth(2);
//      gr_eff_mD1500_final->Draw("PLsame");

//      gr_eff_mD2000_allcut->SetLineColor(7);
//      gr_eff_mD2000_allcut->SetMarkerColor(7);
//      //   gr_eff_mD2000_allcut->Draw("Psame");
//      gr_eff_mD2000_final->SetLineColor(7);
//      gr_eff_mD2000_final->SetMarkerColor(7);
//      //   gr_eff_mD2000_final->SetMarkerStyle(24);
//      gr_eff_mD2000_final->SetLineWidth(2);
//      gr_eff_mD2000_final->Draw("PLsame");
//      leg2->Draw("same");
//      c44->SaveAs("eff_final_ctau.pdf","recreate");



//     // TCanvas *c1 = new TCanvas("c1","c1",700,500);
//     // dummy3->GetXaxis()->SetTitle("c#tau [mm]");
//     // dummy3->GetYaxis()->SetTitle("pixel hit efficiency");
//     // dummy3->Draw();
//     // gr_eff2->Draw("PL");
//     // // gr_eff_recover2->SetLineStyle(2);
//     // // gr_eff_recover2->Draw("PLsame");
//     // c1->SaveAs("eff_recovery2.pdf","recreate");


//     // TCanvas *c11 = new TCanvas("c11","c11",700,500);
//     // dummy3->GetXaxis()->SetTitle("c#tau [mm]");
//     // dummy3->GetYaxis()->SetTitle("pixel hit efficiency");
//     // dummy3->Draw();
//     // gr_eff2->Draw("PL");
//     // gr_eff_recover2->SetLineStyle(2);
//     // gr_eff_recover2->Draw("PLsame");
//     // c11->SaveAs("eff_recovery22.pdf","recreate");

//     // TCanvas *c111 = new TCanvas("c111","c111",700,500);
//     // dummy3->GetXaxis()->SetTitle("c#tau [mm]");
//     // dummy3->GetYaxis()->SetTitle("pixel hit efficiency");
//     // dummy3->Draw();
//     // //  gr_eff2->Draw("PL");
//     // gr_eff_recover3->SetLineStyle(2);
//     // gr_eff_recover3->Draw("PLsame");
//     // c111->SaveAs("eff_recovery3.pdf","recreate");



}
     
