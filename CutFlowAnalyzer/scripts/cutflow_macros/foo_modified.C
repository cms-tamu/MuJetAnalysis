//===========================================================================
//Note: ( @Wei SHI, Jun 28, 2019 )
//This program may be terminated in the case of large number of events,
//      depending on running cluster limit settings on CPU time, etc
//To check settings:
//      Bash: ulimit -H -a, ulimit -S -a; tcsh: limit -h, limit
//To resolve this on TAMU Brazos, use sintr or srun to get interactive node
//===========================================================================

#include <iostream>
#include <iomanip>
using namespace std;
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <TH2.h>
#include <TF1.h>
#include <TCut.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TPaveStats.h>
#include <THStack.h>
#include <TFitResultPtr.h>
#include <TChain.h>
#include <TChainElement.h>
#include <TEfficiency.h>
#include <TMath.h>
#include "Helpers.h"

int counter[20][17];//samples:20; selections
Float_t TotEff[20][17];
Float_t TotEffErr[20][17];
Float_t RelEff[20][17];
Float_t RelEffErr[20][17];
Float_t epsvsalph1[20] = {0.0};
Float_t Err[20] = {0.0};
Float_t epsvsalph2[20] = {0.0};
Float_t epsvsalph[20] = {0.0};
Float_t epsvalp[20] = {0.0};
Float_t epsvalp2[20] = {0.0};
Float_t weight2017 = 1.0;//weight2017 = (lumi[fb-1] * Xsection of the process[fb]) / # of MC events for the process
Float_t weight2018 = 1.0;//TBD
Float_t FitMean = 0.0;
Float_t FitSigma = 0.0;

void setup()
{
for(int i=0;i<20;i++){
  for(int j=0;j<17;j++){
    counter[i][j]=0;
    TotEff[i][j]=0.0;
    RelEff[i][j]=0.0;
    TotEffErr[i][j]=0.0;
    RelEffErr[i][j]=0.0;
  }
 }
}//end setup

int k = -1;
void efficiency(const std::vector<std::string>& dirNames)
{
  //=============================================================
  // Flags to run different plots, by default runs cut-flow-table
  //=============================================================
  bool verbose(true);
  bool CutFlowTable(true);
  bool CheckRecoVtx(false);
  bool ModelBKGShape(false);
  bool Model1DTemplate(false);
  bool ModelSRWidth(false);
  bool PlotIso(false);
  bool PerEventTriggerEff(false);
  TString ext("out_ana_");

  cout<<" dirNames  "<<dirNames[0]<<endl;

  TChain *t = new TChain("cutFlowAnalyzerPXBL4PXFL3/Events");
  TChain *o = new TChain("cutFlowAnalyzerPXBL4PXFL3/Events_orphan");
  // add files to the chain
  addfilesMany(t, dirNames, ext);
  addfilesMany(o, dirNames, ext);

  Float_t diMuonC_Mass;//allows for effective use of architecture with wider formats
  Float_t diMuonF_Mass;
  Bool_t  is1GenMu17;
  Bool_t  is2GenMu8;
  Bool_t  is3GenMu8;
  Bool_t  is4GenMu8;

  Bool_t  is1SelMu17;
  Bool_t  is2SelMu8;
  Bool_t  is3SelMu8;
  Bool_t  is4SelMu8;

  Float_t selMu0_pT;
  Float_t selMu1_pT;
  Float_t selMu2_pT;
  Float_t selMu3_pT;

  Float_t massC;
  Float_t massF;

  Float_t selMu0_eta;
  Float_t selMu1_eta;
  Float_t selMu2_eta;
  Float_t selMu3_eta;

  Float_t selMu0_phi;
  Float_t selMu1_phi;
  Float_t selMu2_phi;
  Float_t selMu3_phi;

  Bool_t  is2DiMuons;
  Bool_t  is2MuJets;
  Bool_t  isVtxOK;

  Bool_t  is2DiMuonsFittedVtxOK;
  Bool_t  is2DiMuonsMassOK;

  Bool_t  isSignalHLTFired;
  Bool_t  isSignalHLTL1Fired;
  Float_t diMuonC_IsoTk_FittedVtx;
  Float_t diMuonF_IsoTk_FittedVtx;
  Float_t diMuonCMu0_IsoTk0p3_FittedVtx;
  Float_t diMuonCMu0_IsoTk0p4_FittedVtx;
  Float_t diMuonCMu0_IsoTk0p5_FittedVtx;
  Float_t diMuonCMu1_IsoTk0p3_FittedVtx;
  Float_t diMuonCMu1_IsoTk0p4_FittedVtx;
  Float_t diMuonCMu1_IsoTk0p5_FittedVtx;

  Float_t diMuonFMu0_IsoTk0p3_FittedVtx;
  Float_t diMuonFMu0_IsoTk0p4_FittedVtx;
  Float_t diMuonFMu0_IsoTk0p5_FittedVtx;
  Float_t diMuonFMu1_IsoTk0p3_FittedVtx;
  Float_t diMuonFMu1_IsoTk0p4_FittedVtx;
  Float_t diMuonFMu1_IsoTk0p5_FittedVtx;

  Float_t  genA0_Lxy;//A0:dark photon that contains the most energetic muon; redt: wrt detector
  Float_t  genA1_Lxy;
  Float_t  genA0_Lz;
  Float_t  genA1_Lz;
  Float_t  diMuons_dz_FittedVtx;

  Int_t  diMuonC_m1_FittedVtx_hitpix_Phase1;
  Int_t  diMuonC_m2_FittedVtx_hitpix_Phase1;
  Int_t  diMuonF_m1_FittedVtx_hitpix_Phase1;
  Int_t  diMuonF_m2_FittedVtx_hitpix_Phase1;

  Int_t diMuonC_m1_FittedVtx_ValidPixelHits;
  Int_t diMuonC_m2_FittedVtx_ValidPixelHits;
  Int_t diMuonF_m1_FittedVtx_ValidPixelHits;
  Int_t diMuonF_m2_FittedVtx_ValidPixelHits;

  Int_t diMuonC_m1_FittedVtx_pixelLayersWithMeasurement;
  Int_t diMuonC_m2_FittedVtx_pixelLayersWithMeasurement;
  Int_t diMuonF_m1_FittedVtx_pixelLayersWithMeasurement;
  Int_t diMuonF_m2_FittedVtx_pixelLayersWithMeasurement;

  Float_t diMuonC_FittedVtx_Lxy;
  Float_t diMuonC_FittedVtx_L;
  Float_t diMuonF_FittedVtx_Lxy;
  Float_t diMuonF_FittedVtx_L;
  Int_t nRecoMu;

  Bool_t orph_passOffLineSelPtEta;
  Bool_t orph_AllTrackerMu;
  Bool_t orph_isSignalHLTFired;
  Bool_t orph_isVertexOK;
  Int_t orph_dimu_Mu0_hitpix_Phase1;
  Int_t orph_dimu_Mu1_hitpix_Phase1;
  Int_t containstrig;//high pT trigger mu obj is the orphan
  Int_t containstrig2;//high pT trigger mu obj is in the dimu
  Float_t orph_dimu_mass;
  Float_t orph_dimu_isoTk;
  Float_t orph_dimu_Mu0_isoTk0p3;
  Float_t orph_dimu_Mu0_isoTk0p4;
  Float_t orph_dimu_Mu0_isoTk0p5;
  Float_t orph_dimu_Mu1_isoTk0p3;
  Float_t orph_dimu_Mu1_isoTk0p4;
  Float_t orph_dimu_Mu1_isoTk0p5;
  Float_t orph_dimu_z;
  Float_t orph_isoTk;

  TH2F* Lxy_Residual_GEN_leading_pT = new TH2F("Lxy_Residual_GEN_leading_pT","",150,0.01,300.,300,-300.,300.);//cm
  TH2F* Abs_Lz_Residual_GEN_leading_pT = new TH2F("Abs_Lz_Residual_GEN_leading_pT","",150,0.01,300.,300,-300.,300.);

  TH1F* leading_pt_pass_basic = new TH1F("leading_pt_pass_basic","",50,0.,50.);
  TH1F* leading_eta_pass_basic = new TH1F("leading_eta_pass_basic","",50,-2.5,2.5);
  TH1F* leading_phi_pass_basic = new TH1F("leading_phi_pass_basic","",60,-TMath::Pi(),TMath::Pi());
  TH1F* HLT_leading_pt_pass_basic = new TH1F("HLT_leading_pt_pass_basic","",50,0.,50.);
  TH1F* HLT_leading_eta_pass_basic = new TH1F("HLT_leading_eta_pass_basic","",50,-2.5,2.5);
  TH1F* HLT_leading_phi_pass_basic = new TH1F("HLT_leading_phi_pass_basic","",60,-TMath::Pi(),TMath::Pi());
  TH1F* L1_leading_pt_pass_basic = new TH1F("L1_leading_pt_pass_basic","",50,0.,50.);
  TH1F* L1_leading_eta_pass_basic = new TH1F("L1_leading_eta_pass_basic","",50,-2.5,2.5);
  TH1F* L1_leading_phi_pass_basic = new TH1F("L1_leading_phi_pass_basic","",60,-TMath::Pi(),TMath::Pi());

  TH1F* leading_pt_pass_all = new TH1F("leading_pt_pass_all","",50,0.,50.);
  TH1F* leading_eta_pass_all = new TH1F("leading_eta_pass_all","",50,-2.5,2.5);
  TH1F* leading_phi_pass_all = new TH1F("leading_phi_pass_all","",60,-TMath::Pi(),TMath::Pi());
  TH1F* HLT_leading_pt_pass_all = new TH1F("HLT_leading_pt_pass_all","",50,0.,50.);
  TH1F* HLT_leading_eta_pass_all = new TH1F("HLT_leading_eta_pass_all","",50,-2.5,2.5);
  TH1F* HLT_leading_phi_pass_all = new TH1F("HLT_leading_phi_pass_all","",60,-TMath::Pi(),TMath::Pi());
  TH1F* L1_leading_pt_pass_all = new TH1F("L1_leading_pt_pass_all","",50,0.,50.);
  TH1F* L1_leading_eta_pass_all = new TH1F("L1_leading_eta_pass_all","",50,-2.5,2.5);
  TH1F* L1_leading_phi_pass_all = new TH1F("L1_leading_phi_pass_all","",60,-TMath::Pi(),TMath::Pi());

  //Actual dimu mass starts from 0.2113, ends at 58 GeV; binning 0.2GeV
  TH2F *BKGShapeCR = new TH2F("BKGShapeCR","",300,0.0,60.0,300,0.0,60.0);
  TH1F *BKGShapeCRmassC = new TH1F("BKGShapeCRmassC","",300,0.0,60.0);
  TH1F *BKGShapeCRmassF = new TH1F("BKGShapeCRmassF","",300,0.0,60.0);
  //Scaled to Run2 lumi
  TH2F *BKGShapeCRScaled = new TH2F("BKGShapeCRScaled","",300,0.0,60.0,300,0.0,60.0);
  TH1F *BKGShapeCRmassCScaled = new TH1F("BKGShapeCRmassCScaled","",300,0.0,60.0);
  TH1F *BKGShapeCRmassFScaled = new TH1F("BKGShapeCRmassFScaled","",300,0.0,60.0);

  TH1F *DimuMass = new TH1F("DimuMass","",6000,0.0,60.0);//binning 0.01 GeV
  TH1F *MassC = new TH1F("MassC","",600,0.0,60.0);//binning 0.1 GeV
  TH1F *MassF = new TH1F("MassF","",600,0.0,60.0);//binning 0.1 GeV

  TH1F *IsoDimuC = new TH1F("IsoDimuC","",1000,0.0,100.0);//binning 0.1 GeV
  TH1F *IsoDimuF = new TH1F("IsoDimuF","",1000,0.0,100.0);//binning 0.1 GeV
  TH1F *IsoDimuCMu0_dR0p3 = new TH1F("IsoDimuCMu0_dR0p3","",1000,0.0,100.0);//binning 0.1 GeV
  TH1F *IsoDimuCMu0_dR0p4 = new TH1F("IsoDimuCMu0_dR0p4","",1000,0.0,100.0);//binning 0.1 GeV
  TH1F *IsoDimuCMu0_dR0p5 = new TH1F("IsoDimuCMu0_dR0p5","",1000,0.0,100.0);//binning 0.1 GeV
  TH1F *IsoDimuCMu1_dR0p3 = new TH1F("IsoDimuCMu1_dR0p3","",1000,0.0,100.0);//binning 0.1 GeV
  TH1F *IsoDimuCMu1_dR0p4 = new TH1F("IsoDimuCMu1_dR0p4","",1000,0.0,100.0);//binning 0.1 GeV
  TH1F *IsoDimuCMu1_dR0p5 = new TH1F("IsoDimuCMu1_dR0p5","",1000,0.0,100.0);//binning 0.1 GeV
  TH1F *IsoDimuFMu0_dR0p3 = new TH1F("IsoDimuFMu0_dR0p3","",1000,0.0,100.0);//binning 0.1 GeV
  TH1F *IsoDimuFMu0_dR0p4 = new TH1F("IsoDimuFMu0_dR0p4","",1000,0.0,100.0);//binning 0.1 GeV
  TH1F *IsoDimuFMu0_dR0p5 = new TH1F("IsoDimuFMu0_dR0p5","",1000,0.0,100.0);//binning 0.1 GeV
  TH1F *IsoDimuFMu1_dR0p3 = new TH1F("IsoDimuFMu1_dR0p3","",1000,0.0,100.0);//binning 0.1 GeV
  TH1F *IsoDimuFMu1_dR0p4 = new TH1F("IsoDimuFMu1_dR0p4","",1000,0.0,100.0);//binning 0.1 GeV
  TH1F *IsoDimuFMu1_dR0p5 = new TH1F("IsoDimuFMu1_dR0p5","",1000,0.0,100.0);//binning 0.1 GeV

  TH1F *OrphanDimuMass = new TH1F("OrphanDimuMass","",600,0.0,60.0);//binning 0.1GeV
  TH1F *Mass1DTemplate = new TH1F("Mass1DTemplate","",600,0.0,60.0);//binning 0.1GeV

  TH1F *IsoOrphanDimu = new TH1F("IsoOrphanDimu","",1000,0.0,100.0);//binning 0.1 GeV
  TH1F *IsoOrphanDimuMu0_dR0p3 = new TH1F("IsoOrphanDimuMu0_dR0p3","",1000,0.0,100.0);//binning 0.1 GeV
  TH1F *IsoOrphanDimuMu0_dR0p4 = new TH1F("IsoOrphanDimuMu0_dR0p4","",1000,0.0,100.0);//binning 0.1 GeV
  TH1F *IsoOrphanDimuMu0_dR0p5 = new TH1F("IsoOrphanDimuMu0_dR0p5","",1000,0.0,100.0);//binning 0.1 GeV
  TH1F *IsoOrphanDimuMu1_dR0p3 = new TH1F("IsoOrphanDimuMu1_dR0p3","",1000,0.0,100.0);//binning 0.1 GeV
  TH1F *IsoOrphanDimuMu1_dR0p4 = new TH1F("IsoOrphanDimuMu1_dR0p4","",1000,0.0,100.0);//binning 0.1 GeV
  TH1F *IsoOrphanDimuMu1_dR0p5 = new TH1F("IsoOrphanDimuMu1_dR0p5","",1000,0.0,100.0);//binning 0.1 GeV
  TH1F *IsoOrphan = new TH1F("IsoOrphan","",1000,0.0,100.0);//binning 0.1 GeV

  k++;//Print k

  int nentries;//entries in main tree
  int mentries;//entries in orphan tree

  t->SetBranchAddress("diMuonC_FittedVtx_m",&diMuonC_Mass);
	t->SetBranchAddress("diMuonF_FittedVtx_m",&diMuonF_Mass);
	t->SetBranchAddress("nRecoMu",&nRecoMu);
  t->SetBranchAddress("is1GenMu17",&is1GenMu17);
	t->SetBranchAddress("is2GenMu8",&is2GenMu8);
	t->SetBranchAddress("is3GenMu8",&is3GenMu8);
	t->SetBranchAddress("is4GenMu8",&is4GenMu8);
	t->SetBranchAddress("is1SelMu17",&is1SelMu17);
	t->SetBranchAddress("is2SelMu8",&is2SelMu8);
	t->SetBranchAddress("is3SelMu8",&is3SelMu8);
	t->SetBranchAddress("is4SelMu8",&is4SelMu8);
	t->SetBranchAddress("selMu0_pT",&selMu0_pT);
	t->SetBranchAddress("selMu1_pT",&selMu1_pT);
	t->SetBranchAddress("selMu2_pT",&selMu2_pT);
	t->SetBranchAddress("selMu3_pT",&selMu3_pT);
	t->SetBranchAddress("selMu0_eta",&selMu0_eta);
	t->SetBranchAddress("selMu1_eta",&selMu1_eta);
	t->SetBranchAddress("selMu2_eta",&selMu2_eta);
	t->SetBranchAddress("selMu3_eta",&selMu3_eta);
  t->SetBranchAddress("selMu0_phi",&selMu0_phi);
	t->SetBranchAddress("selMu1_phi",&selMu1_phi);
	t->SetBranchAddress("selMu2_phi",&selMu2_phi);
	t->SetBranchAddress("selMu3_phi",&selMu3_phi);
  t->SetBranchAddress("massC",&massC);
	t->SetBranchAddress("massF",&massF);
	t->SetBranchAddress("isVertexOK",&isVtxOK);
	t->SetBranchAddress("is2DiMuons",&is2DiMuons);
	t->SetBranchAddress("is2MuJets",&is2MuJets);
	t->SetBranchAddress("is2DiMuonsFittedVtxOK",&is2DiMuonsFittedVtxOK);
	t->SetBranchAddress("diMuons_dz_FittedVtx",&diMuons_dz_FittedVtx);
	t->SetBranchAddress("is2DiMuonsMassOK_FittedVtx",&is2DiMuonsMassOK);
	t->SetBranchAddress("isSignalHLTFired",&isSignalHLTFired);
  t->SetBranchAddress("isSignalHLTL1Fired",&isSignalHLTL1Fired);
	t->SetBranchAddress("diMuonC_IsoTk_FittedVtx",&diMuonC_IsoTk_FittedVtx);
	t->SetBranchAddress("diMuonF_IsoTk_FittedVtx",&diMuonF_IsoTk_FittedVtx);
  t->SetBranchAddress("diMuonCMu0_IsoTk0p3_FittedVtx",&diMuonCMu0_IsoTk0p3_FittedVtx);
  t->SetBranchAddress("diMuonCMu0_IsoTk0p4_FittedVtx",&diMuonCMu0_IsoTk0p4_FittedVtx);
  t->SetBranchAddress("diMuonCMu0_IsoTk0p5_FittedVtx",&diMuonCMu0_IsoTk0p5_FittedVtx);
  t->SetBranchAddress("diMuonCMu1_IsoTk0p3_FittedVtx",&diMuonCMu1_IsoTk0p3_FittedVtx);
  t->SetBranchAddress("diMuonCMu1_IsoTk0p4_FittedVtx",&diMuonCMu1_IsoTk0p4_FittedVtx);
  t->SetBranchAddress("diMuonCMu1_IsoTk0p5_FittedVtx",&diMuonCMu1_IsoTk0p5_FittedVtx);
  t->SetBranchAddress("diMuonFMu0_IsoTk0p3_FittedVtx",&diMuonFMu0_IsoTk0p3_FittedVtx);
  t->SetBranchAddress("diMuonFMu0_IsoTk0p4_FittedVtx",&diMuonFMu0_IsoTk0p4_FittedVtx);
  t->SetBranchAddress("diMuonFMu0_IsoTk0p5_FittedVtx",&diMuonFMu0_IsoTk0p5_FittedVtx);
  t->SetBranchAddress("diMuonFMu1_IsoTk0p3_FittedVtx",&diMuonFMu1_IsoTk0p3_FittedVtx);
  t->SetBranchAddress("diMuonFMu1_IsoTk0p4_FittedVtx",&diMuonFMu1_IsoTk0p4_FittedVtx);
  t->SetBranchAddress("diMuonFMu1_IsoTk0p5_FittedVtx",&diMuonFMu1_IsoTk0p5_FittedVtx);
  t->SetBranchAddress("genA0_Lxy",&genA0_Lxy);
	t->SetBranchAddress("genA1_Lxy",&genA1_Lxy);
	t->SetBranchAddress("genA0_Lz",&genA0_Lz);
	t->SetBranchAddress("genA1_Lz",&genA1_Lz);
  //To be used for Run2
  t->SetBranchAddress("diMuonC_m1_FittedVtx_hitpix_Phase1",&diMuonC_m1_FittedVtx_hitpix_Phase1);
	t->SetBranchAddress("diMuonC_m2_FittedVtx_hitpix_Phase1",&diMuonC_m2_FittedVtx_hitpix_Phase1);
	t->SetBranchAddress("diMuonF_m1_FittedVtx_hitpix_Phase1",&diMuonF_m1_FittedVtx_hitpix_Phase1);
	t->SetBranchAddress("diMuonF_m2_FittedVtx_hitpix_Phase1",&diMuonF_m2_FittedVtx_hitpix_Phase1);
  t->SetBranchAddress("diMuonC_m1_FittedVtx_ValidPixelHits",&diMuonC_m1_FittedVtx_ValidPixelHits);
	t->SetBranchAddress("diMuonC_m2_FittedVtx_ValidPixelHits",&diMuonC_m2_FittedVtx_ValidPixelHits);
	t->SetBranchAddress("diMuonF_m1_FittedVtx_ValidPixelHits",&diMuonF_m1_FittedVtx_ValidPixelHits);
	t->SetBranchAddress("diMuonF_m2_FittedVtx_ValidPixelHits",&diMuonF_m2_FittedVtx_ValidPixelHits);
  t->SetBranchAddress("diMuonC_m1_FittedVtx_pixelLayersWithMeasurement",&diMuonC_m1_FittedVtx_pixelLayersWithMeasurement);
	t->SetBranchAddress("diMuonC_m2_FittedVtx_pixelLayersWithMeasurement",&diMuonC_m2_FittedVtx_pixelLayersWithMeasurement);
	t->SetBranchAddress("diMuonF_m1_FittedVtx_pixelLayersWithMeasurement",&diMuonF_m1_FittedVtx_pixelLayersWithMeasurement);
	t->SetBranchAddress("diMuonF_m2_FittedVtx_pixelLayersWithMeasurement",&diMuonF_m2_FittedVtx_pixelLayersWithMeasurement);
  //For checking pixel Hit
  t->SetBranchAddress("diMuonC_FittedVtx_Lxy",&diMuonC_FittedVtx_Lxy);
	t->SetBranchAddress("diMuonC_FittedVtx_L",&diMuonC_FittedVtx_L);
	t->SetBranchAddress("diMuonF_FittedVtx_Lxy",&diMuonF_FittedVtx_Lxy);
	t->SetBranchAddress("diMuonF_FittedVtx_L",&diMuonF_FittedVtx_L);

  //Get branch from orphan-dimuon tree
  o->SetBranchAddress("orph_passOffLineSelPtEta",&orph_passOffLineSelPtEta);//offline pT, eta selection same as signal
  o->SetBranchAddress("orph_AllTrackerMu",&orph_AllTrackerMu);//tracker mu
  o->SetBranchAddress("orph_isSignalHLTFired",&orph_isSignalHLTFired);
  o->SetBranchAddress("orph_isVertexOK",&orph_isVertexOK);
  o->SetBranchAddress("orph_dimu_Mu0_hitpix_Phase1",&orph_dimu_Mu0_hitpix_Phase1);
  o->SetBranchAddress("orph_dimu_Mu1_hitpix_Phase1",&orph_dimu_Mu1_hitpix_Phase1);
  o->SetBranchAddress("containstrig",&containstrig);
  o->SetBranchAddress("containstrig2",&containstrig2);
  o->SetBranchAddress("orph_dimu_mass",&orph_dimu_mass);
  o->SetBranchAddress("orph_dimu_z",&orph_dimu_z);
  o->SetBranchAddress("orph_dimu_isoTk",&orph_dimu_isoTk);
  o->SetBranchAddress("orph_dimu_Mu0_isoTk0p3",&orph_dimu_Mu0_isoTk0p3);
  o->SetBranchAddress("orph_dimu_Mu0_isoTk0p4",&orph_dimu_Mu0_isoTk0p4);
  o->SetBranchAddress("orph_dimu_Mu0_isoTk0p5",&orph_dimu_Mu0_isoTk0p5);
  o->SetBranchAddress("orph_dimu_Mu1_isoTk0p3",&orph_dimu_Mu1_isoTk0p3);
  o->SetBranchAddress("orph_dimu_Mu1_isoTk0p4",&orph_dimu_Mu1_isoTk0p4);
  o->SetBranchAddress("orph_dimu_Mu1_isoTk0p5",&orph_dimu_Mu1_isoTk0p5);
  o->SetBranchAddress("orph_isoTk",&orph_isoTk);

	nentries = t->GetEntries();
  if( verbose ) std::cout << "main tree entries: "<< nentries << std::endl;

  if( CutFlowTable ){
    for( int i = 0; i < nentries; i++ ){
      t->GetEntry(i);
      if ( (i % 1000000) == 0  ) std::cout << "Looking at Events " << i << std::endl;
      counter[k][0]++;

      //Check vtx significance without any selections
      if ( CheckRecoVtx ){
        Lxy_Residual_GEN_leading_pT->Fill(genA0_Lxy, genA0_Lxy-diMuonC_FittedVtx_Lxy);//assume they match
        Abs_Lz_Residual_GEN_leading_pT->Fill(genA0_Lz, genA0_Lz-sqrt( pow(diMuonC_FittedVtx_L,2) - pow(diMuonC_FittedVtx_Lxy,2) ) );
      }//end CheckRecoVtx

      if( is1GenMu17 ) counter[k][1]++;
      if( is2GenMu8  ) counter[k][2]++;
      if( is3GenMu8  ) counter[k][3]++;
      if( is4GenMu8  ){
        counter[k][4]++;
        //Phase-0 pixel system (Pre2017): 3rd barrel pixel layer and 2nd fwd layer -> Lxy = 10.2 cm; Lz = 48.5 cm
        //Phase-1 pixel system (2017+2018): 3rd barrel pixel layer and 2nd fwd layer -> Lxy = 10.9 cm; Lz = 39.6 cm
        //Phase-1 pixel system (2017+2018): 4th barrel pixel layer and 3rd fwd layer -> Lxy = 16.0 cm; Lz = 51.6 cm //To be used for Run2
        //[1]Reference: https://iopscience.iop.org/article/10.1088/1748-0221/12/07/C07009/pdf
        //[2]TDR: https://cds.cern.ch/record/1481838/files/CMS-TDR-011.pdf
        if( ( genA0_Lxy < 16.0 && fabs(genA0_Lz) < 51.6 ) &&
          ( genA1_Lxy < 16.0 && fabs(genA1_Lz) < 51.6 ) ) {
            counter[k][5]++;
        }
      }//End GEN Level

      if( is1SelMu17 ) counter[k][6]++;
      if( is2SelMu8  ) counter[k][7]++;
      if( is3SelMu8  ) counter[k][8]++;
      if( is4SelMu8  ){
        counter[k][9]++;
        //==============================================
        // Basic offline pT selections finished
        //==============================================
        //pass basic offline pT selections
        if( PerEventTriggerEff ) {
          leading_pt_pass_basic->Fill(selMu0_pT);
          leading_eta_pass_basic->Fill(selMu0_eta);
          leading_phi_pass_basic->Fill(selMu0_phi);

          if ( isSignalHLTFired ) {
            HLT_leading_pt_pass_basic->Fill(selMu0_pT);
            HLT_leading_eta_pass_basic->Fill(selMu0_eta);
            HLT_leading_phi_pass_basic->Fill(selMu0_phi);
          }//HLT fired

          if ( isSignalHLTL1Fired ) {
            L1_leading_pt_pass_basic->Fill(selMu0_pT);
            L1_leading_eta_pass_basic->Fill(selMu0_eta);
            L1_leading_phi_pass_basic->Fill(selMu0_phi);
          }//L1 seeds fired

        }//end if PerEventTriggerEff

        if( isVtxOK ){
          counter[k][10]++;

          if( is2DiMuons ){
            counter[k][11]++;

            if( ( diMuonC_m1_FittedVtx_hitpix_Phase1 == 1 || diMuonC_m2_FittedVtx_hitpix_Phase1 == 1 ) &&
              ( diMuonF_m1_FittedVtx_hitpix_Phase1 == 1 || diMuonF_m2_FittedVtx_hitpix_Phase1 == 1 ) ){
              //!!! Note: this needs to match counter[k][5] geometry
              counter[k][12]++;

              if( fabs(diMuons_dz_FittedVtx) < 0.1 ){
                counter[k][13]++;

                if( diMuonCMu0_IsoTk0p3_FittedVtx >= 0.0 && diMuonCMu0_IsoTk0p3_FittedVtx < 1.5 &&
                    diMuonFMu0_IsoTk0p3_FittedVtx >= 0.0 && diMuonFMu0_IsoTk0p3_FittedVtx < 1.5 ){
                  counter[k][14]++;

                  //Note: for this study need to eliminate/relax Iso cut at counter 14, e.g. Iso<100 GeV or Iso>0
                  if( PlotIso ) {
                    MassC->Fill(massC);
                    MassF->Fill(massF);
                    IsoDimuC->Fill(diMuonC_IsoTk_FittedVtx);
                    IsoDimuF->Fill(diMuonF_IsoTk_FittedVtx);
                    IsoDimuCMu0_dR0p3->Fill(diMuonCMu0_IsoTk0p3_FittedVtx);
                    IsoDimuCMu0_dR0p4->Fill(diMuonCMu0_IsoTk0p4_FittedVtx);
                    IsoDimuCMu0_dR0p5->Fill(diMuonCMu0_IsoTk0p5_FittedVtx);
                    IsoDimuCMu1_dR0p3->Fill(diMuonCMu1_IsoTk0p3_FittedVtx);
                    IsoDimuCMu1_dR0p4->Fill(diMuonCMu1_IsoTk0p4_FittedVtx);
                    IsoDimuCMu1_dR0p5->Fill(diMuonCMu1_IsoTk0p5_FittedVtx);
                    IsoDimuFMu0_dR0p3->Fill(diMuonFMu0_IsoTk0p3_FittedVtx);
                    IsoDimuFMu0_dR0p4->Fill(diMuonFMu0_IsoTk0p4_FittedVtx);
                    IsoDimuFMu0_dR0p5->Fill(diMuonFMu0_IsoTk0p5_FittedVtx);
                    IsoDimuFMu1_dR0p3->Fill(diMuonFMu1_IsoTk0p3_FittedVtx);
                    IsoDimuFMu1_dR0p4->Fill(diMuonFMu1_IsoTk0p4_FittedVtx);
                    IsoDimuFMu1_dR0p5->Fill(diMuonFMu1_IsoTk0p5_FittedVtx);
                  }//end PlotIso

                  //========================================================
                  //PerEventTriggerEff after pass all offline selections except HLT fired
                  // !!!Note: To be more precise, need to put isSignalHLTFired
                  //          as the last counter and this section in the second to
                  //          last counter for these plots to make sense
                  //========================================================
                  if( PerEventTriggerEff ) {

                    leading_pt_pass_all->Fill(selMu0_pT);
                    leading_eta_pass_all->Fill(selMu0_eta);
                    leading_phi_pass_all->Fill(selMu0_phi);

                    if ( isSignalHLTFired ) {
                      HLT_leading_pt_pass_all->Fill(selMu0_pT);
                      HLT_leading_eta_pass_all->Fill(selMu0_eta);
                      HLT_leading_phi_pass_all->Fill(selMu0_phi);
                    }//HLT fired

                    if ( isSignalHLTL1Fired ) {
                      L1_leading_pt_pass_all->Fill(selMu0_pT);
                      L1_leading_eta_pass_all->Fill(selMu0_eta);
                      L1_leading_phi_pass_all->Fill(selMu0_phi);
                    }//L1 seeds fired

                  }//end if PerEventTriggerEff

                  if( isSignalHLTFired ) {
                    counter[k][15]++;

                    if( ModelSRWidth ) {
                      DimuMass->Fill( (massC+massF)/2 );
                    }//end if ModelSRWidth

                    if( is2DiMuonsMassOK ) {
                      counter[k][16]++;
                      //==============================================
                      // All offline analysis selections finished
                      //==============================================

                    }//end 16: mass consistent
                    else{
                      //================================================
                      //               2D mass control region
                      //BKG validation on data and MC for high mass range
                      //=================================================
                      if( ModelBKGShape ) {
                        BKGShapeCR->Fill(massC,massF);
                        BKGShapeCRmassC->Fill(massC);
                        BKGShapeCRmassF->Fill(massF);
                        BKGShapeCRScaled->Fill(massC,massF,weight2017);
                        BKGShapeCRmassCScaled->Fill(massC,weight2017);
                        BKGShapeCRmassFScaled->Fill(massF,weight2017);
                      }//end if ModelBKGShape

                    }//end else
                  }//end 15
                }//end 14
              }//end 13
            }//end 12
          }//end 11
        }//end 10
      }//end 9
    }//end for i entries
  }//end if( CutFlowTable )

  //Loop over orphan-dimuon tree
  mentries = o->GetEntries();
  if( verbose ) std::cout << "orphan-dimu tree entries: "<< mentries << std::endl;
  for( int j = 0; j < mentries; j++ ){
    if ( (j % 1000000) == 0  ) std::cout << "Looking at Events_orphan " << j << std::endl;
    o->GetEntry(j);

    //Pass offline basic selections, same as signal for isolation cut study
    if( PlotIso && orph_passOffLineSelPtEta && orph_AllTrackerMu ){
      OrphanDimuMass->Fill(orph_dimu_mass);
      IsoOrphanDimu->Fill(orph_dimu_isoTk);
      IsoOrphanDimuMu0_dR0p3->Fill(orph_dimu_Mu0_isoTk0p3);
      IsoOrphanDimuMu0_dR0p4->Fill(orph_dimu_Mu0_isoTk0p4);
      IsoOrphanDimuMu0_dR0p5->Fill(orph_dimu_Mu0_isoTk0p5);
      IsoOrphanDimuMu1_dR0p3->Fill(orph_dimu_Mu1_isoTk0p3);
      IsoOrphanDimuMu1_dR0p4->Fill(orph_dimu_Mu1_isoTk0p4);
      IsoOrphanDimuMu1_dR0p5->Fill(orph_dimu_Mu1_isoTk0p5);
      IsoOrphan->Fill(orph_isoTk);
    }

    //Pass same cut as signal, for study 1-D template distribution
    //Note: May need to add orph_dimu_z cut in the future
    if( Model1DTemplate && orph_passOffLineSelPtEta && orph_AllTrackerMu &&
        orph_isSignalHLTFired && orph_isVertexOK &&
        ( orph_dimu_Mu0_hitpix_Phase1 ==1 || orph_dimu_Mu0_hitpix_Phase1==1 ) &&
        orph_dimu_Mu0_isoTk0p3 >= 0.0 && orph_dimu_Mu0_isoTk0p3 < 1.5 ){
        Mass1DTemplate->Fill(orph_dimu_mass);
    }
  }//end for j entries

  RelEff[k][0] = counter[k][0]/(counter[k][0]*1.0);
  for(int m=0;m<17;m++){
    TotEff[k][m]= counter[k][m]/(counter[k][0]*1.0);
    TotEffErr[k][m]= sqrt( (TotEff[k][m]*(1-TotEff[k][m]))/(counter[k][0]*1.0));
    if( m>0 ){
      if( m==6 ){
        RelEff[k][m]= counter[k][m]/(counter[k][0]*1.0);
        RelEffErr[k][m]= sqrt( (RelEff[k][m]*(1-RelEff[k][m]))/(counter[k][0]*1.0));
      }
      else{
        RelEff[k][m]=  counter[k][m]/(counter[k][m-1]*1.0);
        RelEffErr[k][m]= sqrt( (RelEff[k][m]*(1-RelEff[k][m]))/(counter[k][m-1]*1.0));
      }
    }
  }//end Eff calc.

  epsvsalph[k] = counter[k][16]/(counter[k][5]*1.0); //mainvalue of epsilob_rec/alpha_gen
  cout<<"Here is the cut-flow-table:"<<endl;
  cout<<"epsvsalph[k]:  "<<epsvsalph[k]<<endl;
  Err[k]=   sqrt( (epsvsalph[k]*(1-epsvsalph[k]))/(counter[k][5]*1.0));
  cout<<"        "<<endl;
  cout<<"begin{landscape}"<<endl;
  cout<<"centering"<<endl;
  cout<<"begin{tabular}{ c| c | c | c | c | c }"<<endl;

  cout<<" Selection               & "<<left<< setw(11)<<" \\# Evts "    <<" & "<<left << setw(13) << " Tot. Eff. " << " & " << left << setw(13) << " Rel. Eff. "<<" & "<< left << setw(16) << " Tot. Eff. Err. "<<" & "<< left << setw(16) << " Rel. Eff. Err. " <<" hline "<<endl;
  cout<<" No cut                  & "<<left<< setw(11)<< counter[k][0]  <<" & "<<left << setw(13) << TotEff[k][0]  << " & " << left << setw(13) << RelEff[k][0] <<" & "<< left << setw(16) << TotEffErr[k][0]   <<" & "<< left << setw(16) << RelEffErr[k][0]    <<" hline "<<endl;
  cout<<" is1GenMu17Barrel        & "<<left<< setw(11)<< counter[k][1]  <<" & "<<left << setw(13) << TotEff[k][1]  << " & " << left << setw(13) << RelEff[k][1] <<" & "<< left << setw(16) << TotEffErr[k][1]   <<" & "<< left << setw(16) << RelEffErr[k][1]    <<" hline "<<endl;
  cout<<" is2GenMu8               & "<<left<< setw(11)<< counter[k][2]  <<" & "<<left << setw(13) << TotEff[k][2]  << " & " << left << setw(13) << RelEff[k][2] <<" & "<< left << setw(16) << TotEffErr[k][2]   <<" & "<< left << setw(16) << RelEffErr[k][2]    <<" hline "<<endl;
  cout<<" is3GenMu8               & "<<left<< setw(11)<< counter[k][3]  <<" & "<<left << setw(13) << TotEff[k][3]  << " & " << left << setw(13) << RelEff[k][3] <<" & "<< left << setw(16) << TotEffErr[k][3]   <<" & "<< left << setw(16) << RelEffErr[k][3]    <<" hline "<<endl;
  cout<<" is4GenMu8               & "<<left<< setw(11)<< counter[k][4]  <<" & "<<left << setw(13) << TotEff[k][4]  << " & " << left << setw(13) << RelEff[k][4] <<" & "<< left << setw(16) << TotEffErr[k][4]   <<" & "<< left << setw(16) << RelEffErr[k][4]    <<" hline "<<endl;
  cout<<" Lxy<16.0cm && Lz<51.6cm & "<<left<< setw(11)<< counter[k][5]  <<" & "<<left << setw(13) << TotEff[k][5]  << " & " << left << setw(13) << RelEff[k][5] <<" & "<< left << setw(16) << TotEffErr[k][5]   <<" & "<< left << setw(16) << RelEffErr[k][5]    <<" hline "<<endl;
  cout<<"                                                                                                                         " << " hline "<< endl;

  cout<<" is1SelMu17              & "<<left<< setw(11)<< counter[k][6]  <<" & "<<left << setw(13) << TotEff[k][6]  << " & " << left << setw(13) << RelEff[k][6] <<" & "<< left << setw(16) << TotEffErr[k][6]   <<" & "<< left << setw(16) << RelEffErr[k][6]    <<" hline "<<endl;
  cout<<" is2SelMu8               & "<<left<< setw(11)<< counter[k][7]  <<" & "<<left << setw(13) << TotEff[k][7]  << " & " << left << setw(13) << RelEff[k][7] <<" & "<< left << setw(16) << TotEffErr[k][7]   <<" & "<< left << setw(16) << RelEffErr[k][7]    <<" hline "<<endl;
  cout<<" is3SelMu8               & "<<left<< setw(11)<< counter[k][8]  <<" & "<<left << setw(13) << TotEff[k][8]  << " & " << left << setw(13) << RelEff[k][8] <<" & "<< left << setw(16) << TotEffErr[k][8]   <<" & "<< left << setw(16) << RelEffErr[k][8]    <<" hline "<<endl;
  cout<<" is4SelMu8               & "<<left<< setw(11)<< counter[k][9]  <<" & "<<left << setw(13) << TotEff[k][9]  << " & " << left << setw(13) << RelEff[k][9] <<" & "<< left << setw(16) << TotEffErr[k][9]   <<" & "<< left << setw(16) << RelEffErr[k][9]    <<" hline "<<endl;
  cout<<" isVertexOK              & "<<left<< setw(11)<< counter[k][10] <<" & "<<left << setw(13) << TotEff[k][10] << " & " << left << setw(13) << RelEff[k][10]<<" & "<< left << setw(16) << TotEffErr[k][10]  <<" & "<< left << setw(16) << RelEffErr[k][10]   <<" hline "<<endl;
  cout<<" is2Dimuons              & "<<left<< setw(11)<< counter[k][11] <<" & "<<left << setw(13) << TotEff[k][11] << " & " << left << setw(13) << RelEff[k][11]<<" & "<< left << setw(16) << TotEffErr[k][11]  <<" & "<< left << setw(16) << RelEffErr[k][11]   <<" hline "<<endl;
  cout<<" is2DiMuonsPixHitOk      & "<<left<< setw(11)<< counter[k][12] <<" & "<<left << setw(13) << TotEff[k][12] << " & " << left << setw(13) << RelEff[k][12]<<" & "<< left << setw(16) << TotEffErr[k][12]  <<" & "<< left << setw(16) << RelEffErr[k][12]   <<" hline "<<endl;
  cout<<" is2DiMuonsFittedDzOk    & "<<left<< setw(11)<< counter[k][13] <<" & "<<left << setw(13) << TotEff[k][13] << " & " << left << setw(13) << RelEff[k][13]<<" & "<< left << setw(16) << TotEffErr[k][13]  <<" & "<< left << setw(16) << RelEffErr[k][13]   <<" hline "<<endl;
  cout<<" is2MuonsIsolationOK     & "<<left<< setw(11)<< counter[k][14] <<" & "<<left << setw(13) << TotEff[k][14] << " & " << left << setw(13) << RelEff[k][14]<<" & "<< left << setw(16) << TotEffErr[k][14]  <<" & "<< left << setw(16) << RelEffErr[k][14]   <<" hline "<<endl;
  cout<<" isSignalHLTFired        & "<<left<< setw(11)<< counter[k][15] <<" & "<<left << setw(13) << TotEff[k][15] << " & " << left << setw(13) << RelEff[k][15]<<" & "<< left << setw(16) << TotEffErr[k][15]  <<" & "<< left << setw(16) << RelEffErr[k][15]   <<" hline "<<endl;
  cout<<" is2DiMuonsMassOK        & "<<left<< setw(11)<< counter[k][16] <<" & "<<left << setw(13) << TotEff[k][16] << " & " << left << setw(13) << RelEff[k][16]<<" & "<< left << setw(16) << TotEffErr[k][16]  <<" & "<< left << setw(16) << RelEffErr[k][16]   <<" hline "<<endl;
  cout<<"                                                                                                                         " << " hline "<< endl;
  cout<<" epsilon_rec/alpha_gen   & "<< epsvsalph[k]<<"$\\pm$ "<< Err[k]<<" hline "<<endl;

  cout<<"end{tabular}"<<endl;
  cout<<"end{landscape}"<<endl;

  //kth sample
  TString output="";
  output = output + "./foo_modified_sample_" + Form("%d", k)+ ".root";
  TFile myPlot(output,"RECREATE");

  if ( CheckRecoVtx ){
    Lxy_Residual_GEN_leading_pT->Write();
    Abs_Lz_Residual_GEN_leading_pT->Write();
  }//end CheckRecoVtx

  if ( PerEventTriggerEff ) {
    //Per-event Efficiency for signal "HLT" and "L1 seeds" after "BASIC" offline pT selections
    if( TEfficiency::CheckConsistency(*HLT_leading_pt_pass_basic, *leading_pt_pass_basic) ) {
      TEfficiency* eff_HLT_leading_pt_pass_basic  = new TEfficiency(*HLT_leading_pt_pass_basic, *leading_pt_pass_basic);
      eff_HLT_leading_pt_pass_basic->SetTitle("HLT efficiency vs leading pT (after basic offline pT selections);Leading pT [GeV];#epsilon");
      eff_HLT_leading_pt_pass_basic->Write();
    }
    if( TEfficiency::CheckConsistency(*HLT_leading_eta_pass_basic, *leading_eta_pass_basic) ) {
      TEfficiency* eff_HLT_leading_eta_pass_basic = new TEfficiency(*HLT_leading_eta_pass_basic, *leading_eta_pass_basic);
      eff_HLT_leading_eta_pass_basic->SetTitle("HLT efficiency vs leading eta (after basic offline pT selections);Leading eta;#epsilon");
      eff_HLT_leading_eta_pass_basic->Write();
    }
    if( TEfficiency::CheckConsistency(*HLT_leading_phi_pass_basic, *leading_phi_pass_basic) ) {
      TEfficiency* eff_HLT_leading_phi_pass_basic = new TEfficiency(*HLT_leading_phi_pass_basic, *leading_phi_pass_basic);
      eff_HLT_leading_phi_pass_basic->SetTitle("HLT efficiency vs leading phi (after basic offline pT selections);Leading phi;#epsilon");
      eff_HLT_leading_phi_pass_basic->Write();
    }
    if( TEfficiency::CheckConsistency(*L1_leading_pt_pass_basic, *leading_pt_pass_basic) ) {
      TEfficiency* eff_L1_leading_pt_past_basic  = new TEfficiency(*L1_leading_pt_pass_basic, *leading_pt_pass_basic);
      eff_L1_leading_pt_past_basic->SetTitle("L1 efficiency vs leading pT (after basic offline pT selections);Leading pT[GeV];#epsilon");
      eff_L1_leading_pt_past_basic->Write();
    }
    if( TEfficiency::CheckConsistency(*L1_leading_eta_pass_basic, *leading_eta_pass_basic) ) {
      TEfficiency* eff_L1_leading_eta_past_basic = new TEfficiency(*L1_leading_eta_pass_basic, *leading_eta_pass_basic);
      eff_L1_leading_eta_past_basic->SetTitle("L1 efficiency vs leading eta (after basic offline pT selections);Leading eta;#epsilon");
      eff_L1_leading_eta_past_basic->Write();
    }
    if( TEfficiency::CheckConsistency(*L1_leading_phi_pass_basic, *leading_phi_pass_basic) ) {
      TEfficiency* eff_L1_leading_phi_pass_basic = new TEfficiency(*L1_leading_phi_pass_basic, *leading_phi_pass_basic);
      eff_L1_leading_phi_pass_basic->SetTitle("L1 efficiency vs leading phi (after basic offline pT selections);Leading phi;#epsilon");
      eff_L1_leading_phi_pass_basic->Write();
    }

    //Per-event Efficiency for signal "HLT" and "L1 seeds" after "ALL" offline selections
    if( TEfficiency::CheckConsistency(*HLT_leading_pt_pass_all, *leading_pt_pass_all) ) {
      TEfficiency* eff_HLT_leading_pt_pass_all  = new TEfficiency(*HLT_leading_pt_pass_all, *leading_pt_pass_all);
      eff_HLT_leading_pt_pass_all->SetTitle("HLT efficiency vs leading pT (after all offline selections);Leading pT [GeV];#epsilon");
      eff_HLT_leading_pt_pass_all->Write();
    }
    if( TEfficiency::CheckConsistency(*HLT_leading_eta_pass_all, *leading_eta_pass_all) ) {
      TEfficiency* eff_HLT_leading_eta_pass_all = new TEfficiency(*HLT_leading_eta_pass_all, *leading_eta_pass_all);
      eff_HLT_leading_eta_pass_all->SetTitle("HLT efficiency vs leading eta (after all offline selections);Leading eta;#epsilon");
      eff_HLT_leading_eta_pass_all->Write();
    }
    if( TEfficiency::CheckConsistency(*HLT_leading_phi_pass_all, *leading_phi_pass_all) ) {
      TEfficiency* eff_HLT_leading_phi_pass_all = new TEfficiency(*HLT_leading_phi_pass_all, *leading_phi_pass_all);
      eff_HLT_leading_phi_pass_all->SetTitle("HLT efficiency vs leading phi (after all offline selections);Leading phi;#epsilon");
      eff_HLT_leading_phi_pass_all->Write();
    }
    if( TEfficiency::CheckConsistency(*L1_leading_pt_pass_all, *leading_pt_pass_all) ) {
      TEfficiency* eff_L1_leading_pt_past_all  = new TEfficiency(*L1_leading_pt_pass_all, *leading_pt_pass_all);
      eff_L1_leading_pt_past_all->SetTitle("L1 efficiency vs leading pT (after all offline selections);Leading pT [GeV];#epsilon");
      eff_L1_leading_pt_past_all->Write();
    }
    if( TEfficiency::CheckConsistency(*L1_leading_eta_pass_all, *leading_eta_pass_all) ) {
      TEfficiency* eff_L1_leading_eta_past_all = new TEfficiency(*L1_leading_eta_pass_all, *leading_eta_pass_all);
      eff_L1_leading_eta_past_all->SetTitle("L1 efficiency vs leading eta (after all offline selections);Leading eta;#epsilon");
      eff_L1_leading_eta_past_all->Write();
    }
    if( TEfficiency::CheckConsistency(*L1_leading_phi_pass_all, *leading_phi_pass_all) ) {
      TEfficiency* eff_L1_leading_phi_pass_all = new TEfficiency(*L1_leading_phi_pass_all, *leading_phi_pass_all);
      eff_L1_leading_phi_pass_all->SetTitle("L1 efficiency vs leading phi (after all offline selections);Leading phi;#epsilon");
      eff_L1_leading_phi_pass_all->Write();
    }
  }//end if (PerEventTriggerEff)

  if ( ModelBKGShape ) {
    BKGShapeCR->Write();
    BKGShapeCRmassC->Write();
    BKGShapeCRmassF->Write();
    BKGShapeCRScaled->Write();
    BKGShapeCRmassCScaled->Write();
    BKGShapeCRmassFScaled->Write();
  } //end if ( ModelBKGShape )

  if ( ModelSRWidth && DimuMass->Integral() > 0 ) {
    DimuMass->SetLineColor(kBlue);
    DimuMass->SetLineWidth(2);
    DimuMass->GetXaxis()->SetTitle("#frac{m_{#mu#mu1}+m_{#mu#mu2}}{2} [GeV]");
    DimuMass->GetYaxis()->SetTitle("Events/0.01GeV");
    DimuMass->Fit("gaus","","",0,60);
    FitMean = DimuMass->GetFunction("gaus")->GetParameter(1);//get 2nd parameter Mean
    FitSigma = DimuMass->GetFunction("gaus")->GetParameter(2);//get 3rd parameter Sigma
    DimuMass->GetFunction("gaus")->SetLineColor(kBlue);
    DimuMass->GetFunction("gaus")->SetLineStyle(2);
    gStyle->SetOptStat(0);
    DimuMass->Write();

    cout<<"Dimu Mass Fit Mean: "<< FitMean<<"; Fit Sigma: "<< FitSigma<<endl;
  }//end if ( ModelSRWidth )

  if ( PlotIso ) {
    MassC->GetXaxis()->SetTitle("m_{#mu#mu1} [GeV]");
    MassC->GetYaxis()->SetTitle("Events/0.1GeV");
    MassF->GetXaxis()->SetTitle("m_{#mu#mu2} [GeV]");
    MassF->GetYaxis()->SetTitle("Events/0.1GeV");
    MassC->Write();
    MassF->Write();
    IsoDimuC->Write();
    IsoDimuF->Write();
    IsoDimuCMu0_dR0p3->Write();
    IsoDimuCMu0_dR0p4->Write();
    IsoDimuCMu0_dR0p5->Write();
    IsoDimuCMu1_dR0p3->Write();
    IsoDimuCMu1_dR0p4->Write();
    IsoDimuCMu1_dR0p5->Write();
    IsoDimuFMu0_dR0p3->Write();
    IsoDimuFMu0_dR0p4->Write();
    IsoDimuFMu0_dR0p5->Write();
    IsoDimuFMu1_dR0p3->Write();
    IsoDimuFMu1_dR0p4->Write();
    IsoDimuFMu1_dR0p5->Write();

    //Normalize iso
    TH1F *IsoDimuCNormalized = (TH1F*)IsoDimuC->Clone("IsoDimuCNormalized");
    TH1F *IsoDimuFNormalized = (TH1F*)IsoDimuF->Clone("IsoDimuFNormalized");
    TH1F *IsoDimuCMu0_dR0p3_Normalized = (TH1F*)IsoDimuCMu0_dR0p3->Clone("IsoDimuCMu0_dR0p3_Normalized");
    TH1F *IsoDimuCMu0_dR0p4_Normalized = (TH1F*)IsoDimuCMu0_dR0p4->Clone("IsoDimuCMu0_dR0p4_Normalized");
    TH1F *IsoDimuCMu0_dR0p5_Normalized = (TH1F*)IsoDimuCMu0_dR0p5->Clone("IsoDimuCMu0_dR0p5_Normalized");
    TH1F *IsoDimuCMu1_dR0p3_Normalized = (TH1F*)IsoDimuCMu1_dR0p3->Clone("IsoDimuCMu1_dR0p3_Normalized");
    TH1F *IsoDimuCMu1_dR0p4_Normalized = (TH1F*)IsoDimuCMu1_dR0p4->Clone("IsoDimuCMu1_dR0p4_Normalized");
    TH1F *IsoDimuCMu1_dR0p5_Normalized = (TH1F*)IsoDimuCMu1_dR0p5->Clone("IsoDimuCMu1_dR0p5_Normalized");
    TH1F *IsoDimuFMu0_dR0p3_Normalized = (TH1F*)IsoDimuFMu0_dR0p3->Clone("IsoDimuFMu0_dR0p3_Normalized");
    TH1F *IsoDimuFMu0_dR0p4_Normalized = (TH1F*)IsoDimuFMu0_dR0p4->Clone("IsoDimuFMu0_dR0p4_Normalized");
    TH1F *IsoDimuFMu0_dR0p5_Normalized = (TH1F*)IsoDimuFMu0_dR0p5->Clone("IsoDimuFMu0_dR0p5_Normalized");
    TH1F *IsoDimuFMu1_dR0p3_Normalized = (TH1F*)IsoDimuFMu1_dR0p3->Clone("IsoDimuFMu1_dR0p3_Normalized");
    TH1F *IsoDimuFMu1_dR0p4_Normalized = (TH1F*)IsoDimuFMu1_dR0p4->Clone("IsoDimuFMu1_dR0p4_Normalized");
    TH1F *IsoDimuFMu1_dR0p5_Normalized = (TH1F*)IsoDimuFMu1_dR0p5->Clone("IsoDimuFMu1_dR0p5_Normalized");
    //Protect against 0 entry
    if ( IsoDimuC->Integral() > 0 ){ Double_t scaleC = 1./IsoDimuC->Integral(); IsoDimuCNormalized->Scale(scaleC); IsoDimuCNormalized->Write(); }
    if ( IsoDimuF->Integral() > 0 ){ Double_t scaleF = 1./IsoDimuF->Integral(); IsoDimuFNormalized->Scale(scaleF); IsoDimuFNormalized->Write(); }
    if ( IsoDimuCMu0_dR0p3->Integral() > 0 ){ Double_t scaleCMu0_dR0p3 = 1./IsoDimuCMu0_dR0p3->Integral(); IsoDimuCMu0_dR0p3_Normalized->Scale(scaleCMu0_dR0p3); IsoDimuCMu0_dR0p3_Normalized->Write(); }
    if ( IsoDimuCMu0_dR0p4->Integral() > 0 ){ Double_t scaleCMu0_dR0p4 = 1./IsoDimuCMu0_dR0p4->Integral(); IsoDimuCMu0_dR0p4_Normalized->Scale(scaleCMu0_dR0p4); IsoDimuCMu0_dR0p4_Normalized->Write(); }
    if ( IsoDimuCMu0_dR0p5->Integral() > 0 ){ Double_t scaleCMu0_dR0p5 = 1./IsoDimuCMu0_dR0p5->Integral(); IsoDimuCMu0_dR0p5_Normalized->Scale(scaleCMu0_dR0p5); IsoDimuCMu0_dR0p5_Normalized->Write(); }

    if ( IsoDimuCMu1_dR0p3->Integral() > 0 ){ Double_t scaleCMu1_dR0p3 = 1./IsoDimuCMu1_dR0p3->Integral(); IsoDimuCMu1_dR0p3_Normalized->Scale(scaleCMu1_dR0p3); IsoDimuCMu1_dR0p3_Normalized->Write(); }
    if ( IsoDimuCMu1_dR0p4->Integral() > 0 ){ Double_t scaleCMu1_dR0p4 = 1./IsoDimuCMu1_dR0p4->Integral(); IsoDimuCMu1_dR0p4_Normalized->Scale(scaleCMu1_dR0p4); IsoDimuCMu1_dR0p4_Normalized->Write(); }
    if ( IsoDimuCMu1_dR0p5->Integral() > 0 ){ Double_t scaleCMu1_dR0p5 = 1./IsoDimuCMu1_dR0p5->Integral(); IsoDimuCMu1_dR0p5_Normalized->Scale(scaleCMu1_dR0p5); IsoDimuCMu1_dR0p5_Normalized->Write(); }

    if ( IsoDimuFMu0_dR0p3->Integral() > 0 ){ Double_t scaleFMu0_dR0p3 = 1./IsoDimuFMu0_dR0p3->Integral(); IsoDimuFMu0_dR0p3_Normalized->Scale(scaleFMu0_dR0p3); IsoDimuFMu0_dR0p3_Normalized->Write(); }
    if ( IsoDimuFMu0_dR0p4->Integral() > 0 ){ Double_t scaleFMu0_dR0p4 = 1./IsoDimuFMu0_dR0p4->Integral(); IsoDimuFMu0_dR0p4_Normalized->Scale(scaleFMu0_dR0p4); IsoDimuFMu0_dR0p4_Normalized->Write(); }
    if ( IsoDimuFMu0_dR0p5->Integral() > 0 ){ Double_t scaleFMu0_dR0p5 = 1./IsoDimuFMu0_dR0p5->Integral(); IsoDimuFMu0_dR0p5_Normalized->Scale(scaleFMu0_dR0p5); IsoDimuFMu0_dR0p5_Normalized->Write(); }

    if ( IsoDimuFMu1_dR0p3->Integral() > 0 ){ Double_t scaleFMu1_dR0p3 = 1./IsoDimuFMu1_dR0p3->Integral(); IsoDimuFMu1_dR0p3_Normalized->Scale(scaleFMu1_dR0p3); IsoDimuFMu1_dR0p3_Normalized->Write(); }
    if ( IsoDimuFMu1_dR0p4->Integral() > 0 ){ Double_t scaleFMu1_dR0p4 = 1./IsoDimuFMu1_dR0p4->Integral(); IsoDimuFMu1_dR0p4_Normalized->Scale(scaleFMu1_dR0p4); IsoDimuFMu1_dR0p4_Normalized->Write(); }
    if ( IsoDimuFMu1_dR0p5->Integral() > 0 ){ Double_t scaleFMu1_dR0p5 = 1./IsoDimuFMu1_dR0p5->Integral(); IsoDimuFMu1_dR0p5_Normalized->Scale(scaleFMu1_dR0p5); IsoDimuFMu1_dR0p5_Normalized->Write(); }

    OrphanDimuMass->GetXaxis()->SetTitle("m_{orphan_#mu#mu} [GeV]");
    OrphanDimuMass->GetYaxis()->SetTitle("Events/0.1GeV");
    OrphanDimuMass->Write();
    IsoOrphanDimu->Write();
    IsoOrphanDimuMu0_dR0p3->Write();
    IsoOrphanDimuMu0_dR0p4->Write();
    IsoOrphanDimuMu0_dR0p5->Write();
    IsoOrphanDimuMu1_dR0p3->Write();
    IsoOrphanDimuMu1_dR0p4->Write();
    IsoOrphanDimuMu1_dR0p5->Write();
    IsoOrphan->Write();

    TH1F *IsoOrphanDimuNormalized = (TH1F*)IsoOrphanDimu->Clone("IsoOrphanDimuNormalized");
    TH1F *IsoOrphanDimuMu0_dR0p3_Normalized = (TH1F*)IsoOrphanDimuMu0_dR0p3->Clone("IsoOrphanDimuMu0_dR0p3_Normalized");
    TH1F *IsoOrphanDimuMu0_dR0p4_Normalized = (TH1F*)IsoOrphanDimuMu0_dR0p4->Clone("IsoOrphanDimuMu0_dR0p4_Normalized");
    TH1F *IsoOrphanDimuMu0_dR0p5_Normalized = (TH1F*)IsoOrphanDimuMu0_dR0p5->Clone("IsoOrphanDimuMu0_dR0p5_Normalized");
    TH1F *IsoOrphanDimuMu1_dR0p3_Normalized = (TH1F*)IsoOrphanDimuMu1_dR0p3->Clone("IsoOrphanDimuMu1_dR0p3_Normalized");
    TH1F *IsoOrphanDimuMu1_dR0p4_Normalized = (TH1F*)IsoOrphanDimuMu1_dR0p4->Clone("IsoOrphanDimuMu1_dR0p4_Normalized");
    TH1F *IsoOrphanDimuMu1_dR0p5_Normalized = (TH1F*)IsoOrphanDimuMu1_dR0p5->Clone("IsoOrphanDimuMu1_dR0p5_Normalized");
    TH1F *IsoOrphanNormalized = (TH1F*)IsoOrphan->Clone("IsoOrphanNormalized");
    //Protect against 0 entry
    if ( IsoOrphanDimu->Integral() > 0 ){ Double_t scaleOrphanDimu = 1./IsoOrphanDimu->Integral(); IsoOrphanDimuNormalized->Scale(scaleOrphanDimu); IsoOrphanDimuNormalized->Write(); }
    if ( IsoOrphanDimuMu0_dR0p3->Integral() > 0 ){ Double_t scaleMu0_dR0p3 = 1./IsoOrphanDimuMu0_dR0p3->Integral(); IsoOrphanDimuMu0_dR0p3_Normalized->Scale(scaleMu0_dR0p3); IsoOrphanDimuMu0_dR0p3_Normalized->Write(); }
    if ( IsoOrphanDimuMu0_dR0p4->Integral() > 0 ){ Double_t scaleMu0_dR0p4 = 1./IsoOrphanDimuMu0_dR0p4->Integral(); IsoOrphanDimuMu0_dR0p4_Normalized->Scale(scaleMu0_dR0p4); IsoOrphanDimuMu0_dR0p4_Normalized->Write(); }
    if ( IsoOrphanDimuMu0_dR0p5->Integral() > 0 ){ Double_t scaleMu0_dR0p5 = 1./IsoOrphanDimuMu0_dR0p5->Integral(); IsoOrphanDimuMu0_dR0p5_Normalized->Scale(scaleMu0_dR0p5); IsoOrphanDimuMu0_dR0p5_Normalized->Write(); }
    if ( IsoOrphanDimuMu1_dR0p3->Integral() > 0 ){ Double_t scaleMu1_dR0p3 = 1./IsoOrphanDimuMu1_dR0p3->Integral(); IsoOrphanDimuMu1_dR0p3_Normalized->Scale(scaleMu1_dR0p3); IsoOrphanDimuMu1_dR0p3_Normalized->Write(); }
    if ( IsoOrphanDimuMu1_dR0p4->Integral() > 0 ){ Double_t scaleMu1_dR0p4 = 1./IsoOrphanDimuMu1_dR0p4->Integral(); IsoOrphanDimuMu1_dR0p4_Normalized->Scale(scaleMu1_dR0p4); IsoOrphanDimuMu1_dR0p4_Normalized->Write(); }
    if ( IsoOrphanDimuMu1_dR0p5->Integral() > 0 ){ Double_t scaleMu1_dR0p5 = 1./IsoOrphanDimuMu1_dR0p5->Integral(); IsoOrphanDimuMu1_dR0p5_Normalized->Scale(scaleMu1_dR0p5); IsoOrphanDimuMu1_dR0p5_Normalized->Write(); }
    if ( IsoOrphan->Integral() > 0 ){ Double_t scaleOrphan = 1./IsoOrphan->Integral(); IsoOrphanNormalized->Scale(scaleOrphan); IsoOrphanNormalized->Write(); }
  }//end if ( PlotIso )

  if( Model1DTemplate ){
    Mass1DTemplate->GetXaxis()->SetTitle("m_{orphan_#mu#mu} [GeV]");
    Mass1DTemplate->GetYaxis()->SetTitle("Events/0.1GeV");
    Mass1DTemplate->Write();
    TH1F *Mass1DTemplateNormalized = (TH1F*)Mass1DTemplate->Clone("Mass1DTemplateNormalized");
    if ( Mass1DTemplate->Integral() > 0 ){ Double_t scale1DTemplate = 1./Mass1DTemplate->Integral(); Mass1DTemplateNormalized->Scale(scale1DTemplate); Mass1DTemplateNormalized->Write(); }
  }//end if ( Model1DTemplate )

  myPlot.Close();

}//end efficiency function

void analysis(const std::string txtfile)
{
setup();
std::vector< std::vector<string> > NtuplePaths;
// // cout << "Vector Created" << endl;
readTextFileWithSamples(txtfile, NtuplePaths);
// // cout << "Samples read" << endl;
for(auto v: NtuplePaths) efficiency(v);
// // cout << "For Loop completes" << endl;
}
