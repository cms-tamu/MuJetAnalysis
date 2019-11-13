//===========================================================================
//Note: ( @Wei SHI, Jun 28, 2019 )
//This program may be terminated in the case of large number of events,
//      depending on running cluster limit settings on CPU time, etc
//To check settings:
//      Bash: ulimit -H -a, ulimit -S -a; tcsh: limit -h, limit
//To resolve this on TAMU Brazos, use sintr --help or srun to get interactive node
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

int k = -1;
int counter[500][18];//limit # of samples: 500; 18 total selections per sample
Float_t TotEff[500][18];//Total efficiency at each selection
Float_t TotEffErr[500][18];
Float_t RelEff[500][18];//Relative efficiency to previous selection
Float_t RelEffErr[500][18];

Float_t epsvsalph[500] = {0.0};//Model independence indicator: offline reconstruction efficiency over generator level cut efficiency
Float_t Err[500] = {0.0};
Float_t FitMean = 0.0;
Float_t FitSigma = 0.0;

void setup()
{
  for(int i=0;i<20;i++){
    for(int j=0;j<18;j++){
      counter[i][j]=0;
      TotEff[i][j]=0.0;
      RelEff[i][j]=0.0;
      TotEffErr[i][j]=0.0;
      RelEffErr[i][j]=0.0;
    }
  }
}//end setup

void efficiency(const std::vector<std::string>& dirNames)
{
  //=======================================================================
  // Flags to configure different plots, by default will run cut-flow-table
  //=======================================================================
  bool verbose(true);
  bool CutFlowTable(true);
  bool CheckRecoVtx(false);
  bool ModelBKGShape(true);
  bool Model1DTemplate(false);
  bool ModelSRWidth(false);
  bool PlotIso(false);
  bool PerEventTriggerEff(false);
  TString ext("out_ana_");

  cout<<"Directory Names  "<<dirNames[0]<<endl;

  TChain *t = new TChain("cutFlowAnalyzerPXBL4PXFL3/Events");
  TChain *o = new TChain("cutFlowAnalyzerPXBL4PXFL3/Events_orphan");
  // add files to the chain
  cout<<" Adding signal tree...  "<<endl;
  addfilesMany(t, dirNames, ext);
  cout<<" Adding orphan tree...  "<<endl;
  addfilesMany(o, dirNames, ext);
  //Sample #(k+1): 1, 2, 3...
  k++;

  Int_t run;
  Int_t lumi;
  Int_t event;

  Bool_t  is1GenMu17;
  Bool_t  is2GenMu8;
  Bool_t  is3GenMu8;
  Bool_t  is4GenMu8;
  Float_t genA0_Lxy;//A0:dark photon that contains the most energetic muon; redt: wrt detector
  Float_t genA1_Lxy;
  Float_t genA0_Lz;
  Float_t genA1_Lz;

  Bool_t  is1SelMu17;
  Bool_t  is2SelMu8;
  Bool_t  is3SelMu8;
  Bool_t  is4SelMu8;
  Float_t selMu0_pT;//leading mu
  Float_t selMu0_eta;
  Float_t selMu0_phi;

  Bool_t  is2MuJets;
  Bool_t  is2DiMuons;
  Float_t massC;
  Float_t massF;

  Float_t reco4mu_m;
  Float_t recoRePaired2muleading_m;
  Float_t recoRePaired2mutrailing_m;
  Float_t recoRePaired2muleading_dR;
  Float_t recoRePaired2mutrailing_dR;

  Bool_t  isVtxOK;
  Float_t diMuons_dz_FittedVtx;
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

  Int_t  diMuonC_m1_FittedVtx_hitpix_Phase1;
  Int_t  diMuonC_m2_FittedVtx_hitpix_Phase1;
  Int_t  diMuonF_m1_FittedVtx_hitpix_Phase1;
  Int_t  diMuonF_m2_FittedVtx_hitpix_Phase1;

  Float_t diMuonC_FittedVtx_Lxy;
  Float_t diMuonC_FittedVtx_L;
  Float_t diMuonF_FittedVtx_Lxy;
  Float_t diMuonF_FittedVtx_L;

  Bool_t orph_passOffLineSelPtEta;
  Bool_t orph_AllTrackerMu;
  Bool_t orph_isSignalHLTFired;
  Bool_t orph_isVertexOK;
  Int_t orph_dimu_Mu0_hitpix_Phase1;
  Int_t orph_dimu_Mu1_hitpix_Phase1;
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

  TH2F* Lxy_Residual_GEN_leading_pT    = new TH2F("Lxy_Residual_GEN_leading_pT",   "", 150, 0.01, 300., 300, -300., 300.);//cm
  TH2F* Abs_Lz_Residual_GEN_leading_pT = new TH2F("Abs_Lz_Residual_GEN_leading_pT","", 150, 0.01, 300., 300, -300., 300.);

  TH1F* leading_pt_pass_basic          = new TH1F("leading_pt_pass_basic",         "", 50, 0.,           50.);
  TH1F* leading_eta_pass_basic         = new TH1F("leading_eta_pass_basic",        "", 50, -2.5,         2.5);
  TH1F* leading_phi_pass_basic         = new TH1F("leading_phi_pass_basic",        "", 60, -TMath::Pi(), TMath::Pi());
  TH1F* HLT_leading_pt_pass_basic      = new TH1F("HLT_leading_pt_pass_basic",     "", 50, 0.,           50.);
  TH1F* HLT_leading_eta_pass_basic     = new TH1F("HLT_leading_eta_pass_basic",    "", 50, -2.5,         2.5);
  TH1F* HLT_leading_phi_pass_basic     = new TH1F("HLT_leading_phi_pass_basic",    "", 60, -TMath::Pi(), TMath::Pi());
  TH1F* L1_leading_pt_pass_basic       = new TH1F("L1_leading_pt_pass_basic",      "", 50, 0.,           50.);
  TH1F* L1_leading_eta_pass_basic      = new TH1F("L1_leading_eta_pass_basic",     "", 50, -2.5,         2.5);
  TH1F* L1_leading_phi_pass_basic      = new TH1F("L1_leading_phi_pass_basic",     "", 60, -TMath::Pi(), TMath::Pi());

  TH1F* leading_pt_pass_all            = new TH1F("leading_pt_pass_all",           "", 50, 0.,           50.);
  TH1F* leading_eta_pass_all           = new TH1F("leading_eta_pass_all",          "", 50, -2.5,         2.5);
  TH1F* leading_phi_pass_all           = new TH1F("leading_phi_pass_all",          "", 60, -TMath::Pi(), TMath::Pi());
  TH1F* HLT_leading_pt_pass_all        = new TH1F("HLT_leading_pt_pass_all",       "", 50, 0.,           50.);
  TH1F* HLT_leading_eta_pass_all       = new TH1F("HLT_leading_eta_pass_all",      "", 50, -2.5,         2.5);
  TH1F* HLT_leading_phi_pass_all       = new TH1F("HLT_leading_phi_pass_all",      "", 60, -TMath::Pi(), TMath::Pi());
  TH1F* L1_leading_pt_pass_all         = new TH1F("L1_leading_pt_pass_all",        "", 50, 0.,           50.);
  TH1F* L1_leading_eta_pass_all        = new TH1F("L1_leading_eta_pass_all",       "", 50, -2.5,         2.5);
  TH1F* L1_leading_phi_pass_all        = new TH1F("L1_leading_phi_pass_all",       "", 60, -TMath::Pi(), TMath::Pi());

  //For BKG modeling at high mass 11-59 GeV
  //Control Region/Validation Region
  TH2F *BKGShapeCR      = new TH2F("BKGShapeCR",      "", 12, 11., 59., 12, 11., 59.);//binning 4 GeV
  TH1F *BKGShapeCRmassC = new TH1F("BKGShapeCRmassC", "", 12, 11., 59.);
  TH1F *BKGShapeCRmassF = new TH1F("BKGShapeCRmassF", "", 12, 11., 59.);
  TH1F *BKGShapeOrphDimumass = new TH1F("BKGShapeOrphDimumass", "", 12, 11., 59.);//Use events in orphan_dimu tree
  //Signal Region
  TH2F *BKGShapeSR      = new TH2F("BKGShapeSR",      "", 12, 11., 59., 12, 11., 59.);
  TH1F *BKGShapeSRmassC = new TH1F("BKGShapeSRmassC", "", 12, 11., 59.);
  TH1F *BKGShapeSRmassF = new TH1F("BKGShapeSRmassF", "", 12, 11., 59.);

  TH1F *DimuMass = new TH1F("DimuMass", "", 6000, 0., 60.);//binning 0.01 GeV
  TH1F *MassC    = new TH1F("MassC",    "", 600,  0., 60.);//binning 0.1 GeV
  TH1F *MassF    = new TH1F("MassF",    "", 600,  0., 60.);

  TH1F *RECO4muMass             = new TH1F("RECO4muMass",             "", 180,  0., 180.);//binning 1 GeV
  TH1F *RECOrePaired2muLeadingMass  = new TH1F("RECOrePaired2muLeadingMass",  "", 180,  0., 180.);
  TH1F *RECOrePaired2muTrailingMass = new TH1F("RECOrePaired2muTrailingMass", "", 180,  0., 180.);

  TH1F *RECOrePaired2muLeadingdR   = new TH1F("RECOrePaired2muLeadingdR",   "", 450,  0., 4.5);//binning 0.01
  TH1F *RECOrePaired2muTrailingdR  = new TH1F("RECOrePaired2muTrailingdR",  "", 450,  0., 4.5);

  TH1F *IsoDimuC          = new TH1F("IsoDimuC",          "", 1000, 0., 100.);//binning 0.1 GeV
  TH1F *IsoDimuF          = new TH1F("IsoDimuF",          "", 1000, 0., 100.);
  TH1F *IsoDimuCMu0_dR0p3 = new TH1F("IsoDimuCMu0_dR0p3", "", 1000, 0., 100.);
  TH1F *IsoDimuCMu0_dR0p4 = new TH1F("IsoDimuCMu0_dR0p4", "", 1000, 0., 100.);
  TH1F *IsoDimuCMu0_dR0p5 = new TH1F("IsoDimuCMu0_dR0p5", "", 1000, 0., 100.);
  TH1F *IsoDimuCMu1_dR0p3 = new TH1F("IsoDimuCMu1_dR0p3", "", 1000, 0., 100.);
  TH1F *IsoDimuCMu1_dR0p4 = new TH1F("IsoDimuCMu1_dR0p4", "", 1000, 0., 100.);
  TH1F *IsoDimuCMu1_dR0p5 = new TH1F("IsoDimuCMu1_dR0p5", "", 1000, 0., 100.);
  TH1F *IsoDimuFMu0_dR0p3 = new TH1F("IsoDimuFMu0_dR0p3", "", 1000, 0., 100.);
  TH1F *IsoDimuFMu0_dR0p4 = new TH1F("IsoDimuFMu0_dR0p4", "", 1000, 0., 100.);
  TH1F *IsoDimuFMu0_dR0p5 = new TH1F("IsoDimuFMu0_dR0p5", "", 1000, 0., 100.);
  TH1F *IsoDimuFMu1_dR0p3 = new TH1F("IsoDimuFMu1_dR0p3", "", 1000, 0., 100.);
  TH1F *IsoDimuFMu1_dR0p4 = new TH1F("IsoDimuFMu1_dR0p4", "", 1000, 0., 100.);
  TH1F *IsoDimuFMu1_dR0p5 = new TH1F("IsoDimuFMu1_dR0p5", "", 1000, 0., 100.);

  TH1F *OrphanDimuMass = new TH1F("OrphanDimuMass", "", 600, 0., 60.0);//binning 0.1GeV
  TH1F *Mass1DTemplate = new TH1F("Mass1DTemplate", "", 600, 0., 60.0);

  TH1F *IsoOrphanDimu          = new TH1F("IsoOrphanDimu",          "", 1000, 0., 100.);//binning 0.1 GeV
  TH1F *IsoOrphanDimuMu0_dR0p3 = new TH1F("IsoOrphanDimuMu0_dR0p3", "", 1000, 0., 100.);
  TH1F *IsoOrphanDimuMu0_dR0p4 = new TH1F("IsoOrphanDimuMu0_dR0p4", "", 1000, 0., 100.);
  TH1F *IsoOrphanDimuMu0_dR0p5 = new TH1F("IsoOrphanDimuMu0_dR0p5", "", 1000, 0., 100.);
  TH1F *IsoOrphanDimuMu1_dR0p3 = new TH1F("IsoOrphanDimuMu1_dR0p3", "", 1000, 0., 100.);
  TH1F *IsoOrphanDimuMu1_dR0p4 = new TH1F("IsoOrphanDimuMu1_dR0p4", "", 1000, 0., 100.);
  TH1F *IsoOrphanDimuMu1_dR0p5 = new TH1F("IsoOrphanDimuMu1_dR0p5", "", 1000, 0., 100.);
  TH1F *IsoOrphan              = new TH1F("IsoOrphan",              "", 1000, 0., 100.);

  int nentries;//entries in main tree
  int mentries;//entries in orphan tree

  t->SetBranchAddress("run",   &run);
  t->SetBranchAddress("lumi",  &lumi);
	t->SetBranchAddress("event", &event);

  t->SetBranchAddress("is1GenMu17", &is1GenMu17);
	t->SetBranchAddress("is2GenMu8",  &is2GenMu8);
	t->SetBranchAddress("is3GenMu8",  &is3GenMu8);
	t->SetBranchAddress("is4GenMu8",  &is4GenMu8);
  t->SetBranchAddress("genA0_Lxy",  &genA0_Lxy);
	t->SetBranchAddress("genA1_Lxy",  &genA1_Lxy);
	t->SetBranchAddress("genA0_Lz",   &genA0_Lz);
	t->SetBranchAddress("genA1_Lz",   &genA1_Lz);

	t->SetBranchAddress("is1SelMu17", &is1SelMu17);
	t->SetBranchAddress("is2SelMu8",  &is2SelMu8);
	t->SetBranchAddress("is3SelMu8",  &is3SelMu8);
	t->SetBranchAddress("is4SelMu8",  &is4SelMu8);
	t->SetBranchAddress("selMu0_pT",  &selMu0_pT);
	t->SetBranchAddress("selMu0_eta", &selMu0_eta);
  t->SetBranchAddress("selMu0_phi", &selMu0_phi);

  t->SetBranchAddress("isVertexOK", &isVtxOK);
	t->SetBranchAddress("is2MuJets",  &is2MuJets);
  t->SetBranchAddress("is2DiMuons", &is2DiMuons);
  t->SetBranchAddress("massC",      &massC);
	t->SetBranchAddress("massF",      &massF);

  t->SetBranchAddress("reco4mu_m",                  &reco4mu_m);
  t->SetBranchAddress("recoRePaired2muleading_m",   &recoRePaired2muleading_m);
  t->SetBranchAddress("recoRePaired2mutrailing_m",  &recoRePaired2mutrailing_m);
  t->SetBranchAddress("recoRePaired2muleading_dR",  &recoRePaired2muleading_dR);
  t->SetBranchAddress("recoRePaired2mutrailing_dR", &recoRePaired2mutrailing_dR);

  t->SetBranchAddress("diMuonC_m1_FittedVtx_hitpix_Phase1",              &diMuonC_m1_FittedVtx_hitpix_Phase1);
	t->SetBranchAddress("diMuonC_m2_FittedVtx_hitpix_Phase1",              &diMuonC_m2_FittedVtx_hitpix_Phase1);
	t->SetBranchAddress("diMuonF_m1_FittedVtx_hitpix_Phase1",              &diMuonF_m1_FittedVtx_hitpix_Phase1);
	t->SetBranchAddress("diMuonF_m2_FittedVtx_hitpix_Phase1",              &diMuonF_m2_FittedVtx_hitpix_Phase1);
  //For checking pixel Hit
  t->SetBranchAddress("diMuonC_FittedVtx_Lxy", &diMuonC_FittedVtx_Lxy);
	t->SetBranchAddress("diMuonC_FittedVtx_L",   &diMuonC_FittedVtx_L);
	t->SetBranchAddress("diMuonF_FittedVtx_Lxy", &diMuonF_FittedVtx_Lxy);
	t->SetBranchAddress("diMuonF_FittedVtx_L",   &diMuonF_FittedVtx_L);

  t->SetBranchAddress("diMuons_dz_FittedVtx",          &diMuons_dz_FittedVtx);
  t->SetBranchAddress("diMuonC_IsoTk_FittedVtx",       &diMuonC_IsoTk_FittedVtx);
	t->SetBranchAddress("diMuonF_IsoTk_FittedVtx",       &diMuonF_IsoTk_FittedVtx);
  t->SetBranchAddress("diMuonCMu0_IsoTk0p3_FittedVtx", &diMuonCMu0_IsoTk0p3_FittedVtx);
  t->SetBranchAddress("diMuonCMu0_IsoTk0p4_FittedVtx", &diMuonCMu0_IsoTk0p4_FittedVtx);
  t->SetBranchAddress("diMuonCMu0_IsoTk0p5_FittedVtx", &diMuonCMu0_IsoTk0p5_FittedVtx);
  t->SetBranchAddress("diMuonCMu1_IsoTk0p3_FittedVtx", &diMuonCMu1_IsoTk0p3_FittedVtx);
  t->SetBranchAddress("diMuonCMu1_IsoTk0p4_FittedVtx", &diMuonCMu1_IsoTk0p4_FittedVtx);
  t->SetBranchAddress("diMuonCMu1_IsoTk0p5_FittedVtx", &diMuonCMu1_IsoTk0p5_FittedVtx);
  t->SetBranchAddress("diMuonFMu0_IsoTk0p3_FittedVtx", &diMuonFMu0_IsoTk0p3_FittedVtx);
  t->SetBranchAddress("diMuonFMu0_IsoTk0p4_FittedVtx", &diMuonFMu0_IsoTk0p4_FittedVtx);
  t->SetBranchAddress("diMuonFMu0_IsoTk0p5_FittedVtx", &diMuonFMu0_IsoTk0p5_FittedVtx);
  t->SetBranchAddress("diMuonFMu1_IsoTk0p3_FittedVtx", &diMuonFMu1_IsoTk0p3_FittedVtx);
  t->SetBranchAddress("diMuonFMu1_IsoTk0p4_FittedVtx", &diMuonFMu1_IsoTk0p4_FittedVtx);
  t->SetBranchAddress("diMuonFMu1_IsoTk0p5_FittedVtx", &diMuonFMu1_IsoTk0p5_FittedVtx);
  t->SetBranchAddress("isSignalHLTFired",              &isSignalHLTFired);
  t->SetBranchAddress("isSignalHLTL1Fired",            &isSignalHLTL1Fired);
  t->SetBranchAddress("is2DiMuonsMassOK_FittedVtx",    &is2DiMuonsMassOK);

  //Get branch from orphan-dimuon tree
  o->SetBranchAddress("orph_passOffLineSelPtEta",    &orph_passOffLineSelPtEta);//offline pT, eta selection same as signal
  o->SetBranchAddress("orph_AllTrackerMu",           &orph_AllTrackerMu);//tracker mu
  o->SetBranchAddress("orph_isSignalHLTFired",       &orph_isSignalHLTFired);
  o->SetBranchAddress("orph_isVertexOK",             &orph_isVertexOK);
  o->SetBranchAddress("orph_dimu_Mu0_hitpix_Phase1", &orph_dimu_Mu0_hitpix_Phase1);
  o->SetBranchAddress("orph_dimu_Mu1_hitpix_Phase1", &orph_dimu_Mu1_hitpix_Phase1);
  o->SetBranchAddress("orph_dimu_mass",              &orph_dimu_mass);
  o->SetBranchAddress("orph_dimu_z",                 &orph_dimu_z);

  o->SetBranchAddress("orph_dimu_isoTk",        &orph_dimu_isoTk);
  o->SetBranchAddress("orph_dimu_Mu0_isoTk0p3", &orph_dimu_Mu0_isoTk0p3);
  o->SetBranchAddress("orph_dimu_Mu0_isoTk0p4", &orph_dimu_Mu0_isoTk0p4);
  o->SetBranchAddress("orph_dimu_Mu0_isoTk0p5", &orph_dimu_Mu0_isoTk0p5);
  o->SetBranchAddress("orph_dimu_Mu1_isoTk0p3", &orph_dimu_Mu1_isoTk0p3);
  o->SetBranchAddress("orph_dimu_Mu1_isoTk0p4", &orph_dimu_Mu1_isoTk0p4);
  o->SetBranchAddress("orph_dimu_Mu1_isoTk0p5", &orph_dimu_Mu1_isoTk0p5);
  o->SetBranchAddress("orph_isoTk",             &orph_isoTk);

	nentries = t->GetEntries();
  if( verbose ) std::cout << "main tree entries: "<< nentries << std::endl;

  if( CutFlowTable ){
    for( int i = 0; i < nentries; i++ ){
      t->GetEntry(i);
      if ( verbose && (i % 1000000) == 0  ) std::cout << "Looking at Events " << i << std::endl;
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

            if( ModelBKGShape ) {
              RECO4muMass->Fill(reco4mu_m);
              RECOrePaired2muLeadingMass->Fill(recoRePaired2muleading_m);
              RECOrePaired2muTrailingMass->Fill(recoRePaired2mutrailing_m);
              RECOrePaired2muLeadingdR->Fill(recoRePaired2muleading_dR);
              RECOrePaired2muTrailingdR->Fill(recoRePaired2mutrailing_dR);
            }//end ModelBKGShape

            if( RECOrePaired2muTrailingdR >= 0.2 || RECOrePaired2muTrailingMass >= 3 ){
              counter[k][12]++;

              if( ( diMuonC_m1_FittedVtx_hitpix_Phase1 == 1 || diMuonC_m2_FittedVtx_hitpix_Phase1 == 1 ) &&
                  ( diMuonF_m1_FittedVtx_hitpix_Phase1 == 1 || diMuonF_m2_FittedVtx_hitpix_Phase1 == 1 ) ){
                //!!! Note: this needs to match counter[k][5] geometry
                counter[k][13]++;

                if( fabs(diMuons_dz_FittedVtx) < 0.1 ){
                  counter[k][14]++;

                  if( diMuonCMu0_IsoTk0p3_FittedVtx >= 0.0 && diMuonCMu0_IsoTk0p3_FittedVtx < 1.5 &&
                      diMuonFMu0_IsoTk0p3_FittedVtx >= 0.0 && diMuonFMu0_IsoTk0p3_FittedVtx < 1.5 ){
                    counter[k][15]++;

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

                      if( isSignalHLTFired ) {
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
                      counter[k][16]++;

                      if( ModelSRWidth ) {
                        DimuMass->Fill( (massC+massF)/2 );
                      }//end if ModelSRWidth

                      if( is2DiMuonsMassOK ) {
                        counter[k][17]++;

                        //==============================================
                        // All offline analysis selections finished
                        //==============================================
                        if( ModelBKGShape ) {
                          BKGShapeSR->Fill(massC,massF);
                          BKGShapeSRmassC->Fill(massC);
                          BKGShapeSRmassF->Fill(massF);
                        }
                        //std::cout << "SR run: "<< run << "; lumi: "<< lumi << "; event: "<< event << std::endl;
                      }//end 17: mass consistent
                      else{
                        //================================================
                        //               2D mass control region
                        //Validation region on data and MC for high mass BKG
                        //=================================================
                        if( ModelBKGShape ) {
                          BKGShapeCR->Fill(massC,massF);
                          BKGShapeCRmassC->Fill(massC);
                          BKGShapeCRmassF->Fill(massF);
                        }//end if ModelBKGShape

                      }//end else
                    }//end 16
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
    if ( verbose && (j % 1000000) == 0  ) std::cout << "Looking at Events_orphan " << j << std::endl;
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
    if( ( ModelBKGShape || Model1DTemplate ) && orph_passOffLineSelPtEta && orph_AllTrackerMu && orph_isSignalHLTFired && orph_isVertexOK &&
        ( orph_dimu_Mu0_hitpix_Phase1 == 1 || orph_dimu_Mu1_hitpix_Phase1 == 1 ) &&
        orph_dimu_Mu0_isoTk0p3 >= 0.0 && orph_dimu_Mu0_isoTk0p3 < 1.5 ){
            Mass1DTemplate->Fill(orph_dimu_mass);
            BKGShapeOrphDimumass->Fill(orph_dimu_mass);
    }
  }//end for j entries

  RelEff[k][0] = counter[k][0]/(counter[k][0]*1.0);
  for(int m=0;m<18;m++){
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

  epsvsalph[k] = counter[k][17]/(counter[k][5]*1.0); //final epsilob_rec/alpha_gen
  cout<<"Here is the cut-flow-table:"<<endl;
  cout<<"epsvsalph[k]: "<<epsvsalph[k]<<endl;
  Err[k]=   sqrt( (epsvsalph[k]*(1-epsvsalph[k]))/(counter[k][5]*1.0));
  cout<<"        "<<endl;
  cout<<"begin{landscape}"<<endl;
  cout<<"centering"<<endl;
  cout<<"begin{tabular}{ c| c | c | c | c | c }"<<endl;

  cout<<" #   Selection               & "<<left<< setw(11)<<" \\# Evts "    <<" & "<<left << setw(13) << " Tot. Eff. " << " & " << left << setw(13) << " Rel. Eff. "<<" & "<< left << setw(16) << " Tot. Eff. Err. "<<" & "<< left << setw(16) << " Rel. Eff. Err. " <<" hline "<<endl;
  cout<<" #0  No cut                  & "<<left<< setw(11)<< counter[k][0]  <<" & "<<left << setw(13) <<setprecision(3)<< TotEff[k][0]  << " & " << left << setw(13) <<setprecision(3)<< RelEff[k][0] <<" & "<< left << setw(16) <<setprecision(3)<< TotEffErr[k][0]   <<" & "<< left << setw(16) <<setprecision(3)<< RelEffErr[k][0]    <<" hline "<<endl;
  cout<<" #1  is1GenMu17Barrel        & "<<left<< setw(11)<< counter[k][1]  <<" & "<<left << setw(13) <<setprecision(3)<< TotEff[k][1]  << " & " << left << setw(13) <<setprecision(3)<< RelEff[k][1] <<" & "<< left << setw(16) <<setprecision(3)<< TotEffErr[k][1]   <<" & "<< left << setw(16) <<setprecision(3)<< RelEffErr[k][1]    <<" hline "<<endl;
  cout<<" #2  is2GenMu8               & "<<left<< setw(11)<< counter[k][2]  <<" & "<<left << setw(13) <<setprecision(3)<< TotEff[k][2]  << " & " << left << setw(13) <<setprecision(3)<< RelEff[k][2] <<" & "<< left << setw(16) <<setprecision(3)<< TotEffErr[k][2]   <<" & "<< left << setw(16) <<setprecision(3)<< RelEffErr[k][2]    <<" hline "<<endl;
  cout<<" #3  is3GenMu8               & "<<left<< setw(11)<< counter[k][3]  <<" & "<<left << setw(13) <<setprecision(3)<< TotEff[k][3]  << " & " << left << setw(13) <<setprecision(3)<< RelEff[k][3] <<" & "<< left << setw(16) <<setprecision(3)<< TotEffErr[k][3]   <<" & "<< left << setw(16) <<setprecision(3)<< RelEffErr[k][3]    <<" hline "<<endl;
  cout<<" #4  is4GenMu8               & "<<left<< setw(11)<< counter[k][4]  <<" & "<<left << setw(13) <<setprecision(3)<< TotEff[k][4]  << " & " << left << setw(13) <<setprecision(3)<< RelEff[k][4] <<" & "<< left << setw(16) <<setprecision(3)<< TotEffErr[k][4]   <<" & "<< left << setw(16) <<setprecision(3)<< RelEffErr[k][4]    <<" hline "<<endl;
  cout<<" #5  Lxy<16.0cm && Lz<51.6cm & "<<left<< setw(11)<< counter[k][5]  <<" & "<<left << setw(13) <<setprecision(3)<< TotEff[k][5]  << " & " << left << setw(13) <<setprecision(3)<< RelEff[k][5] <<" & "<< left << setw(16) <<setprecision(3)<< TotEffErr[k][5]   <<" & "<< left << setw(16) <<setprecision(3)<< RelEffErr[k][5]    <<" hline "<<endl;
  cout<<"                                                                                                                            " << " hline "<< endl;

  cout<<" #6  is1SelMu17Barrel        & "<<left<< setw(11)<< counter[k][6]  <<" & "<<left << setw(13) <<setprecision(3)<< TotEff[k][6]  << " & " << left << setw(13) <<setprecision(3)<< RelEff[k][6] <<" & "<< left << setw(16) <<setprecision(3)<< TotEffErr[k][6]   <<" & "<< left << setw(16) <<setprecision(3)<< RelEffErr[k][6]    <<" hline "<<endl;
  cout<<" #7  is2SelMu8               & "<<left<< setw(11)<< counter[k][7]  <<" & "<<left << setw(13) <<setprecision(3)<< TotEff[k][7]  << " & " << left << setw(13) <<setprecision(3)<< RelEff[k][7] <<" & "<< left << setw(16) <<setprecision(3)<< TotEffErr[k][7]   <<" & "<< left << setw(16) <<setprecision(3)<< RelEffErr[k][7]    <<" hline "<<endl;
  cout<<" #8  is3SelMu8               & "<<left<< setw(11)<< counter[k][8]  <<" & "<<left << setw(13) <<setprecision(3)<< TotEff[k][8]  << " & " << left << setw(13) <<setprecision(3)<< RelEff[k][8] <<" & "<< left << setw(16) <<setprecision(3)<< TotEffErr[k][8]   <<" & "<< left << setw(16) <<setprecision(3)<< RelEffErr[k][8]    <<" hline "<<endl;
  cout<<" #9  is4SelMu8               & "<<left<< setw(11)<< counter[k][9]  <<" & "<<left << setw(13) <<setprecision(3)<< TotEff[k][9]  << " & " << left << setw(13) <<setprecision(3)<< RelEff[k][9] <<" & "<< left << setw(16) <<setprecision(3)<< TotEffErr[k][9]   <<" & "<< left << setw(16) <<setprecision(3)<< RelEffErr[k][9]    <<" hline "<<endl;
  cout<<" #10 isVertexOK              & "<<left<< setw(11)<< counter[k][10] <<" & "<<left << setw(13) <<setprecision(3)<< TotEff[k][10] << " & " << left << setw(13) <<setprecision(3)<< RelEff[k][10]<<" & "<< left << setw(16) <<setprecision(3)<< TotEffErr[k][10]  <<" & "<< left << setw(16) <<setprecision(3)<< RelEffErr[k][10]   <<" hline "<<endl;
  cout<<" #11 is2Dimuons              & "<<left<< setw(11)<< counter[k][11] <<" & "<<left << setw(13) <<setprecision(3)<< TotEff[k][11] << " & " << left << setw(13) <<setprecision(3)<< RelEff[k][11]<<" & "<< left << setw(16) <<setprecision(3)<< TotEffErr[k][11]  <<" & "<< left << setw(16) <<setprecision(3)<< RelEffErr[k][11]   <<" hline "<<endl;
  cout<<" #12 isNotDYLLQEDRadiate     & "<<left<< setw(11)<< counter[k][12] <<" & "<<left << setw(13) <<setprecision(3)<< TotEff[k][12] << " & " << left << setw(13) <<setprecision(3)<< RelEff[k][12]<<" & "<< left << setw(16) <<setprecision(3)<< TotEffErr[k][12]  <<" & "<< left << setw(16) <<setprecision(3)<< RelEffErr[k][12]   <<" hline "<<endl;
  cout<<" #13 is2DiMuonsPixHitOk      & "<<left<< setw(11)<< counter[k][13] <<" & "<<left << setw(13) <<setprecision(3)<< TotEff[k][13] << " & " << left << setw(13) <<setprecision(3)<< RelEff[k][13]<<" & "<< left << setw(16) <<setprecision(3)<< TotEffErr[k][13]  <<" & "<< left << setw(16) <<setprecision(3)<< RelEffErr[k][13]   <<" hline "<<endl;
  cout<<" #14 is2DiMuonsFittedDzOk    & "<<left<< setw(11)<< counter[k][14] <<" & "<<left << setw(13) <<setprecision(3)<< TotEff[k][14] << " & " << left << setw(13) <<setprecision(3)<< RelEff[k][14]<<" & "<< left << setw(16) <<setprecision(3)<< TotEffErr[k][14]  <<" & "<< left << setw(16) <<setprecision(3)<< RelEffErr[k][14]   <<" hline "<<endl;
  cout<<" #15 is2MuonsIsolationOK     & "<<left<< setw(11)<< counter[k][15] <<" & "<<left << setw(13) <<setprecision(3)<< TotEff[k][15] << " & " << left << setw(13) <<setprecision(3)<< RelEff[k][15]<<" & "<< left << setw(16) <<setprecision(3)<< TotEffErr[k][15]  <<" & "<< left << setw(16) <<setprecision(3)<< RelEffErr[k][15]   <<" hline "<<endl;
  cout<<" #16 isSignalHLTAccepted     & "<<left<< setw(11)<< counter[k][16] <<" & "<<left << setw(13) <<setprecision(3)<< TotEff[k][16] << " & " << left << setw(13) <<setprecision(3)<< RelEff[k][16]<<" & "<< left << setw(16) <<setprecision(3)<< TotEffErr[k][16]  <<" & "<< left << setw(16) <<setprecision(3)<< RelEffErr[k][16]   <<" hline "<<endl;
  cout<<" #17 is2DiMuonsMassOK        & "<<left<< setw(11)<< counter[k][17] <<" & "<<left << setw(13) <<setprecision(3)<< TotEff[k][17] << " & " << left << setw(13) <<setprecision(3)<< RelEff[k][17]<<" & "<< left << setw(16) <<setprecision(3)<< TotEffErr[k][17]  <<" & "<< left << setw(16) <<setprecision(3)<< RelEffErr[k][17]   <<" hline "<<endl;
  cout<<"                                                                                                                         " << " hline "<< endl;
  cout<<" epsilon_rec/alpha_gen       & "<<setprecision(3)<< epsvsalph[k]  << " $\\pm$ "  << Err[k]<<" hline "<<endl;

  cout<<"end{tabular}"<<endl;
  cout<<"end{landscape}"<<endl;

  //kth sample
  TString output="";
  output = output + "./foo_modified_sample_" + Form("%d", k+1)+ ".root";
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
    RECO4muMass->GetXaxis()->SetTitle("m_{4#mu} [GeV]"); RECO4muMass->GetYaxis()->SetTitle("Events/GeV"); RECO4muMass->Write();
    RECOrePaired2muLeadingMass->GetXaxis()->SetTitle("Leading mass of re-paired OS di-#mu [GeV]"); RECOrePaired2muLeadingMass->GetYaxis()->SetTitle("Events/GeV"); RECOrePaired2muLeadingMass->Write();
    RECOrePaired2muTrailingMass->GetXaxis()->SetTitle("Trailing mass of re-paired OS di-#mu [GeV]"); RECOrePaired2muTrailingMass->GetYaxis()->SetTitle("Events/GeV"); RECOrePaired2muTrailingMass->Write();
    RECOrePaired2muLeadingdR->GetXaxis()->SetTitle("Leading dR of re-paired OS di-#mu"); RECOrePaired2muLeadingdR->GetYaxis()->SetTitle("Events/0.01"); RECOrePaired2muLeadingdR->Write();
    RECOrePaired2muTrailingdR->GetXaxis()->SetTitle("Trailing dR of re-paired OS di-#mu"); RECOrePaired2muTrailingdR->GetYaxis()->SetTitle("Events/0.01"); RECOrePaired2muTrailingdR->Write();
    BKGShapeCR->Write();
    BKGShapeCRmassC->Write();
    BKGShapeCRmassF->Write();
    BKGShapeOrphDimumass->Write();
    BKGShapeSR->Write();
    BKGShapeSRmassC->Write();
    BKGShapeSRmassF->Write();
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

  //Delete objects to avoid potential memory leak
  delete Lxy_Residual_GEN_leading_pT;
  delete Abs_Lz_Residual_GEN_leading_pT;
  delete leading_pt_pass_basic;
  delete leading_eta_pass_basic;
  delete leading_phi_pass_basic;
  delete HLT_leading_pt_pass_basic;
  delete HLT_leading_eta_pass_basic;
  delete HLT_leading_phi_pass_basic;
  delete L1_leading_pt_pass_basic;
  delete L1_leading_eta_pass_basic;
  delete L1_leading_phi_pass_basic;
  delete leading_pt_pass_all;
  delete leading_eta_pass_all;
  delete leading_phi_pass_all;
  delete HLT_leading_pt_pass_all;
  delete HLT_leading_eta_pass_all;
  delete HLT_leading_phi_pass_all;
  delete L1_leading_pt_pass_all;
  delete L1_leading_eta_pass_all;
  delete L1_leading_phi_pass_all;
  delete BKGShapeCR;
  delete BKGShapeCRmassC;
  delete BKGShapeCRmassF;
  delete BKGShapeOrphDimumass;
  delete BKGShapeSR;
  delete BKGShapeSRmassC;
  delete BKGShapeSRmassF;
  delete DimuMass;
  delete MassC;
  delete MassF;
  delete RECO4muMass;
  delete RECOrePaired2muLeadingMass;
  delete RECOrePaired2muTrailingMass;
  delete RECOrePaired2muLeadingdR;
  delete RECOrePaired2muTrailingdR;
  delete IsoDimuC;
  delete IsoDimuF;
  delete IsoDimuCMu0_dR0p3;
  delete IsoDimuCMu0_dR0p4;
  delete IsoDimuCMu0_dR0p5;
  delete IsoDimuCMu1_dR0p3;
  delete IsoDimuCMu1_dR0p4;
  delete IsoDimuCMu1_dR0p5;
  delete IsoDimuFMu0_dR0p3;
  delete IsoDimuFMu0_dR0p4;
  delete IsoDimuFMu0_dR0p5;
  delete IsoDimuFMu1_dR0p3;
  delete IsoDimuFMu1_dR0p4;
  delete IsoDimuFMu1_dR0p5;
  delete OrphanDimuMass;
  delete Mass1DTemplate;
  delete IsoOrphanDimu;
  delete IsoOrphanDimuMu0_dR0p3;
  delete IsoOrphanDimuMu0_dR0p4;
  delete IsoOrphanDimuMu0_dR0p5;
  delete IsoOrphanDimuMu1_dR0p3;
  delete IsoOrphanDimuMu1_dR0p4;
  delete IsoOrphanDimuMu1_dR0p5;
  delete IsoOrphan;

}//end efficiency function

void analysis(const std::string SamplesList)
{
  //SamplesList is a txt file that lists all sample points, one txt file per sample
  //each txt file contains the Ntuples path of this sample
  setup();
  //Read sample line by line
  ifstream inputlist(SamplesList);
  string sampletxtfile;
  int linecount = 0;
  while (std::getline(inputlist, sampletxtfile)) {
    linecount++;
    cout << "Sample #"<< linecount << ": "<< sampletxtfile << endl;
    const std::string txtfile = sampletxtfile;
    std::vector< std::vector<string> > NtuplePaths;
    readTextFileWithSamples(txtfile, NtuplePaths);
    for(auto v: NtuplePaths)  efficiency(v);
    cout << "                       " << endl;
    cout << "#######################" << endl;
  }//end while

  //Calcaulate standard deviation (SD) for each offline selection efficiency/GEN Acceptance
  //Smaller SD indicate better performance on model independence for the selection
  cout << "Tot. # of samples: "<< linecount << endl;
  if ( linecount >= 1 ){
    TH1F *finalratio  = new TH1F("finalratio", "", 100, 0., 1.);//binning 0.01
    TH1F *cut12releff = new TH1F("cut12releff","", 100, 0., 1.);
    TH1F *cut12ratio  = new TH1F("cut12ratio", "", 100, 0., 1.);
    for (int iline = 0; iline < linecount; iline++) {
      cout << iline+1 << ": final ratio = "<< epsvsalph[iline] << "; cut12 releff = " << RelEff[iline][12] << "; cut12 ratio = "<< counter[iline][12]*1.0/counter[iline][5] << endl;
      finalratio->Fill(epsvsalph[iline]);
      cut12releff->Fill(RelEff[iline][12]);
      cut12ratio->Fill(counter[iline][12]*1.0/counter[iline][5]);
    }
    cout << "final ratio  Sigma: " << finalratio->GetStdDev()  << "; Mean: " << finalratio->GetMean() << endl;
    cout << "cut12 releff Sigma: " << cut12releff->GetStdDev() << "; Mean: " << cut12releff->GetMean() << endl;
    cout << "cut12 ratio  Sigma: " << cut12ratio->GetStdDev()  << "; Mean: " << cut12ratio->GetMean() << endl;
    TFile finalPlot("analysis.root","RECREATE");
    finalratio->Write();
    cut12releff->Write();
    cut12ratio->Write();
    finalPlot.Close();
  }

}//end analysis
