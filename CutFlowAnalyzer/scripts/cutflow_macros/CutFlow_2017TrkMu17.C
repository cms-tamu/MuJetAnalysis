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
#include <TString.h>
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

int k = -1;//counts sample number
int counter[500][18];//limit # of samples: 500; 18 total selections per sample for run 2; will be used in final cut flow
int counterGENMatch[500][18];//counts events by including GEN selections (GEN Match), for studies on Monte Carlo (signal)
Float_t TotEff[500][18];//Total efficiency at each selection
Float_t TotEffErr[500][18];//Err. of total efficiency
Float_t RelEff[500][18];//Relative efficiency to previous selection
Float_t RelEffErr[500][18];//Err. of relative efficiency

Float_t epsvsalph[500] = {0.0};//Model independence const.: offline reconstruction efficiency over generator level cut efficiency
Float_t Err[500] = {0.0};
Float_t FitMean = 0.0;
Float_t FitSigma = 0.0;

void setup()
{
  for (int i=0;i<500;i++) {
    for (int j=0;j<18;j++) {
      counter[i][j]=0;
      counterGENMatch[i][j]=0;
      TotEff[i][j]=0.0;
      RelEff[i][j]=0.0;
      TotEffErr[i][j]=0.0;
      RelEffErr[i][j]=0.0;
    }
  }
}//end setup

void efficiency(const std::vector<std::string>& dirNames)
{
  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  //! Flags for USER to configure  !
  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  bool verbose(true);//Debug and printout basic info from ntuple
  bool CutFlowTable(true);//Loop 2-dimu events and print cutflow table
  bool LoopOrphanTree(false);//Loop over orphan-dimu events
  bool Model1DTemplate(false);//plot dimu mass in orphan-dimu events
  bool PlotdZ(true);//Plot dZ of two dimuon vtx
  bool PlotIso(true);//Plot isolation for dimuon(s)
  bool PerEventTriggerEff(true);//Plot per event trigger eff.
  bool ModelSRWidth(true);//Plot mass and fit to obtain width for 2D signal corridor
  bool ModelBKGShape(true);//Plot histograms to be used in high mass background estimation

  TString ext("out_ana_");
  cout<<"Directory Names  "<<dirNames[0]<<endl;
  TChain *t = new TChain("cutFlowAnalyzerPXBL4PXFL3/Events");
  TChain *o = new TChain("cutFlowAnalyzerPXBL4PXFL3/Events_orphan");
  //add files to the chain
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
  Float_t genMu0_pT; //leading mu
  Float_t genMu1_pT;
  Float_t genMu2_pT;
  Float_t genMu3_pT;
  Float_t genMu0_eta;
  Float_t genMu1_eta;
  Float_t genMu2_eta;
  Float_t genMu3_eta;
  Float_t genMu0_phi;
  Float_t genMu1_phi;
  Float_t genMu2_phi;
  Float_t genMu3_phi;
  Float_t genA0_Lxy; //A0:dark photon that contains the most energetic muon; redt: wrt detector
  Float_t genA1_Lxy;
  Float_t genA0_Lz;
  Float_t genA1_Lz;
  Float_t genA0Mu0_pt;
  Float_t genA0Mu1_pt;
  Float_t genA1Mu0_pt;
  Float_t genA1Mu1_pt;
  Float_t genA0Mu_dR;
  Float_t genA1Mu_dR;

  Bool_t  is1SelMu17;
  Bool_t  is2SelMu8;
  Bool_t  is3SelMu8;
  Bool_t  is4SelMu8;
  Float_t selMu0_pT; //leading mu
  Float_t selMu1_pT;
  Float_t selMu2_pT;
  Float_t selMu3_pT;
  Float_t selMu0_eta;
  Float_t selMu1_eta;
  Float_t selMu2_eta;
  Float_t selMu3_eta;
  Float_t selMu0_phi;
  Float_t selMu1_phi;
  Float_t selMu2_phi;
  Float_t selMu3_phi;
  Float_t muJetC_Mu0_pt;
  Float_t muJetC_Mu1_pt;
  Float_t muJetF_Mu0_pt;
  Float_t muJetF_Mu1_pt;
  Float_t muJetC_Mu0_eta;
  Float_t muJetC_Mu1_eta;
  Float_t muJetF_Mu0_eta;
  Float_t muJetF_Mu1_eta;
  Float_t muJetC_Mu0_phi;
  Float_t muJetC_Mu1_phi;
  Float_t muJetF_Mu0_phi;
  Float_t muJetF_Mu1_phi;

  Int_t   nMuJets;
  Bool_t  is2MuJets;
  Bool_t  is2DiMuons;
  Bool_t  dimuC_Mu0_SA;
  Bool_t  dimuC_Mu1_SA;
  Bool_t  dimuF_Mu0_SA;
  Bool_t  dimuF_Mu1_SA;
  Int_t   nSAMu;
  Int_t   dimuC_nSAMu;
  Int_t   dimuF_nSAMu;
  Int_t   nNonTrackerMu;
  Int_t   dimuC_nNonTrackerMu;
  Int_t   dimuF_nNonTrackerMu;
  Int_t   SAmu_nTrkWP1;
  Int_t   SAmu_nTrkWP2;
  Int_t   SAmu_nTrkWP3;
  Int_t   SAmu_nTrkNodzWP1;
  Int_t   SAmu_nTrkNodzWP2;
  Int_t   SAmu_nTrkNodzWP3;
  Float_t SAmu_TrkIsoWP1;
  Float_t SAmu_TrkIsoWP2;
  Float_t SAmu_TrkIsoWP3;
  Float_t SAmu_TrkIsoNodzWP1;
  Float_t SAmu_TrkIsoNodzWP2;
  Float_t SAmu_TrkIsoNodzWP3;
  Float_t diMuonC_FittedVtx_prob;
  Float_t diMuonF_FittedVtx_prob;
  Float_t diMuonC_FittedVtx_dR;
  Float_t diMuonF_FittedVtx_dR;
  Float_t diMuonC_FittedVtx_Lxy;
  Float_t diMuonC_FittedVtx_L;
  Float_t diMuonF_FittedVtx_Lxy;
  Float_t diMuonF_FittedVtx_L;
  Float_t massC;
  Float_t massF;
  Int_t   NPATJet;
  Int_t   NPATJetTightB;
  Int_t   NPATJetMediumB;
  Int_t   NPATJetLooseB;

  Float_t reco4mu_m;
  Float_t recoRePaired2muleading_m;
  Float_t recoRePaired2mutrailing_m;
  Float_t recoRePaired2muleading_dR;
  Float_t recoRePaired2mutrailing_dR;

  Bool_t  isVtxOK;
  Float_t diMuons_dz_FittedVtx;
  Float_t diMuonC_FittedVtx_dz;
  Float_t diMuonF_FittedVtx_dz;
  Bool_t  is2DiMuonsMassOK;

  //Start DEBUG: many HLT paths
  Bool_t  isSignalHLT_0_Fired;
  Bool_t  isSignalHLT_1_Fired;
  Bool_t  isSignalHLT_2_Fired;
  Bool_t  isSignalHLT_3_Fired;
  //End DEBUG: many HLT paths
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

  TCanvas *Lxy          = new TCanvas("Lxy",          "L_{xy} of A_{0, 1} (GEN) in Phase-1 Pixel Volume", 700, 500);
  TCanvas *Lz           = new TCanvas("Lz",           "L_{z} of A_{0, 1} (GEN) in Phase-1 Pixel Volume",  700, 500);
  TCanvas *GENMuPt      = new TCanvas("GENMuPt",      "Muon p_{T} (GEN) in Phase-1 Pixel Volume", 700, 500);
  TCanvas *GENMuEta     = new TCanvas("GENMuEta",     "Muon #eta (GEN) in Phase-1 Pixel Volume",  700, 500);
  TCanvas *GENMuPhi     = new TCanvas("GENMuPhi",     "Muon #phi (GEN) in Phase-1 Pixel Volume",  700, 500);
  TCanvas *GENAMuPt     = new TCanvas("GENAMuPt",     "Signal A Daughter Muon p_{T} (GEN) in Phase-1 Pixel Volume", 700, 500);
  TCanvas *RECOMuPt     = new TCanvas("RECOMuPt",     "Muon p_{T} (RECO) in Phase-1 Pixel Volume", 700, 500);
  TCanvas *RECOMuEta    = new TCanvas("RECOMuEta",    "Muon #eta (RECO) in Phase-1 Pixel Volume",  700, 500);
  TCanvas *RECOMuPhi    = new TCanvas("RECOMuPhi",    "Muon #phi (RECO) in Phase-1 Pixel Volume",  700, 500);
  TCanvas *RECODimuMuPt = new TCanvas("RECODimuMuPt", "Candidate Di-#mu Muon p_{T} (RECO) in Phase-1 Pixel Volume", 700, 500);

  TH1F* Phase1Pix_GEN_A0_Lxy = new TH1F("Phase1Pix_GEN_A0_Lxy", "L_{xy} of A0 (GEN) in Phase-1 Pixel Volume", 40,   0., 20.); //per 0.5cm
  TH1F* Phase1Pix_GEN_A0_Lz  = new TH1F("Phase1Pix_GEN_A0_Lz",  "L_{z} of A0 (GEN) in Phase-1 Pixel Volume", 240, -60., 60.); //per 0.5cm
  TH1F* Phase1Pix_GEN_A1_Lxy = new TH1F("Phase1Pix_GEN_A1_Lxy", "L_{xy} of A1 (GEN) in Phase-1 Pixel Volume", 40,   0., 20.);
  TH1F* Phase1Pix_GEN_A1_Lz  = new TH1F("Phase1Pix_GEN_A1_Lz",  "L_{z} of A1 (GEN) in Phase-1 Pixel Volume", 240, -60., 60.);

  TH1F* Phase1Pix_GEN_Mu0_pT = new TH1F("Phase1Pix_GEN_Mu0_pT", "1st GEN #mu in Phase-1 Pixel Volume", 130, 0., 130.); //per GeV
  TH1F* Phase1Pix_GEN_Mu1_pT = new TH1F("Phase1Pix_GEN_Mu1_pT", "2nd GEN #mu in Phase-1 Pixel Volume", 130, 0., 130.);
  TH1F* Phase1Pix_GEN_Mu2_pT = new TH1F("Phase1Pix_GEN_Mu2_pT", "3rd GEN #mu in Phase-1 Pixel Volume", 130, 0., 130.);
  TH1F* Phase1Pix_GEN_Mu3_pT = new TH1F("Phase1Pix_GEN_Mu3_pT", "4th GEN #mu in Phase-1 Pixel Volume", 130, 0., 130.);

  TH1F* Phase1Pix_GEN_Mu0_eta = new TH1F("Phase1Pix_GEN_Mu0_eta", "1st GEN #mu in Phase-1 Pixel Volume", 50, -2.5, 2.5); //per 0.1
  TH1F* Phase1Pix_GEN_Mu1_eta = new TH1F("Phase1Pix_GEN_Mu1_eta", "2nd GEN #mu in Phase-1 Pixel Volume", 50, -2.5, 2.5);
  TH1F* Phase1Pix_GEN_Mu2_eta = new TH1F("Phase1Pix_GEN_Mu2_eta", "3rd GEN #mu in Phase-1 Pixel Volume", 50, -2.5, 2.5);
  TH1F* Phase1Pix_GEN_Mu3_eta = new TH1F("Phase1Pix_GEN_Mu3_eta", "4th GEN #mu in Phase-1 Pixel Volume", 50, -2.5, 2.5);

  TH1F* Phase1Pix_GEN_Mu0_phi = new TH1F("Phase1Pix_GEN_Mu0_phi", "1st GEN #mu in Phase-1 Pixel Volume", 70, -3.5, 3.5); //per 0.1
  TH1F* Phase1Pix_GEN_Mu1_phi = new TH1F("Phase1Pix_GEN_Mu1_phi", "2nd GEN #mu in Phase-1 Pixel Volume", 70, -3.5, 3.5);
  TH1F* Phase1Pix_GEN_Mu2_phi = new TH1F("Phase1Pix_GEN_Mu2_phi", "3rd GEN #mu in Phase-1 Pixel Volume", 70, -3.5, 3.5);
  TH1F* Phase1Pix_GEN_Mu3_phi = new TH1F("Phase1Pix_GEN_Mu3_phi", "4th GEN #mu in Phase-1 Pixel Volume", 70, -3.5, 3.5);

  TH1F* Phase1Pix_GEN_A0_Mu0_pT = new TH1F("Phase1Pix_GEN_A0_Mu0_pT", "p_{T} of Leading Muon in A0 (GEN) in Phase-1 Pixel Volume",  130, 0., 130.);
  TH1F* Phase1Pix_GEN_A0_Mu1_pT = new TH1F("Phase1Pix_GEN_A0_Mu1_pT", "p_{T} of Trailing Muon in A0 (GEN) in Phase-1 Pixel Volume", 130, 0., 130.);
  TH1F* Phase1Pix_GEN_A1_Mu0_pT = new TH1F("Phase1Pix_GEN_A1_Mu0_pT", "p_{T} of Leading Muon in A1 (GEN) in Phase-1 Pixel Volume",  130, 0., 130.);
  TH1F* Phase1Pix_GEN_A1_Mu1_pT = new TH1F("Phase1Pix_GEN_A1_Mu1_pT", "p_{T} of Trailing Muon in A1 (GEN) in Phase-1 Pixel Volume", 130, 0., 130.);


  TH1F* Phase1Pix_RECO_Mu0_pT = new TH1F("Phase1Pix_RECO_Mu0_pT", "1st RECO #mu in Phase-1 Pixel Volume", 130, 0., 130.);
  TH1F* Phase1Pix_RECO_Mu1_pT = new TH1F("Phase1Pix_RECO_Mu1_pT", "2nd RECO #mu in Phase-1 Pixel Volume", 130, 0., 130.);
  TH1F* Phase1Pix_RECO_Mu2_pT = new TH1F("Phase1Pix_RECO_Mu2_pT", "3rd RECO #mu in Phase-1 Pixel Volume", 130, 0., 130.);
  TH1F* Phase1Pix_RECO_Mu3_pT = new TH1F("Phase1Pix_RECO_Mu3_pT", "4th RECO #mu in Phase-1 Pixel Volume", 130, 0., 130.);

  TH1F* Phase1Pix_RECO_Mu0_eta = new TH1F("Phase1Pix_RECO_Mu0_eta", "1st RECO #mu in Phase-1 Pixel Volume", 50, -2.5, 2.5); //per 0.1
  TH1F* Phase1Pix_RECO_Mu1_eta = new TH1F("Phase1Pix_RECO_Mu1_eta", "2nd RECO #mu in Phase-1 Pixel Volume", 50, -2.5, 2.5);
  TH1F* Phase1Pix_RECO_Mu2_eta = new TH1F("Phase1Pix_RECO_Mu2_eta", "3rd RECO #mu in Phase-1 Pixel Volume", 50, -2.5, 2.5);
  TH1F* Phase1Pix_RECO_Mu3_eta = new TH1F("Phase1Pix_RECO_Mu3_eta", "4th RECO #mu in Phase-1 Pixel Volume", 50, -2.5, 2.5);

  TH1F* Phase1Pix_RECO_Mu0_phi = new TH1F("Phase1Pix_RECO_Mu0_phi", "1st RECO #mu in Phase-1 Pixel Volume", 70, -3.5, 3.5); //per 0.1
  TH1F* Phase1Pix_RECO_Mu1_phi = new TH1F("Phase1Pix_RECO_Mu1_phi", "2nd RECO #mu in Phase-1 Pixel Volume", 70, -3.5, 3.5);
  TH1F* Phase1Pix_RECO_Mu2_phi = new TH1F("Phase1Pix_RECO_Mu2_phi", "3rd RECO #mu in Phase-1 Pixel Volume", 70, -3.5, 3.5);
  TH1F* Phase1Pix_RECO_Mu3_phi = new TH1F("Phase1Pix_RECO_Mu3_phi", "4th RECO #mu in Phase-1 Pixel Volume", 70, -3.5, 3.5);

  TH1F* Phase1Pix_RECO_DimuC_Mu0_pT = new TH1F("Phase1Pix_RECO_DimuC_Mu0_pT", "p_{T} of Leading Muon in 1st Di-#mu (RECO) in Phase-1 Pixel Volume",  130, 0., 130.);
  TH1F* Phase1Pix_RECO_DimuC_Mu1_pT = new TH1F("Phase1Pix_RECO_DimuC_Mu1_pT", "p_{T} of Trailing Muon in 1st Di-#mu (RECO) in Phase-1 Pixel Volume", 130, 0., 130.);
  TH1F* Phase1Pix_RECO_DimuF_Mu0_pT = new TH1F("Phase1Pix_RECO_DimuF_Mu0_pT", "p_{T} of Leading Muon in 2nd Di-#mu (RECO) in Phase-1 Pixel Volume",  130, 0., 130.);
  TH1F* Phase1Pix_RECO_DimuF_Mu1_pT = new TH1F("Phase1Pix_RECO_DimuF_Mu1_pT", "p_{T} of Trailing Muon in 2nd Di-#mu (RECO) in Phase-1 Pixel Volume", 130, 0., 130.);

  TH1F* GENMudR_A0 = new TH1F("GENMudR_A0", "", 80, 0, 8);//per 0.1
  TH1F* GENMudR_A1 = new TH1F("GENMudR_A1", "", 80, 0, 8);

  TH1F* DimuCdR = new TH1F("DimuCdR", "#DeltaR of muons from 1st di-#mu", 80, 0, 8);//per 0.1
  TH1F* DimuFdR = new TH1F("DimuFdR", "#DeltaR of muons from 2nd di-#mu", 80, 0, 8);

  TH1F* GEN1stPt_pass_GEN = new TH1F("GEN1stPt_pass_GEN", "", 150, 0, 150);
  TH1F* GEN2ndPt_pass_GEN = new TH1F("GEN2ndPt_pass_GEN", "", 150, 0, 150);
  TH1F* GEN3rdPt_pass_GEN = new TH1F("GEN3rdPt_pass_GEN", "", 150, 0, 150);
  TH1F* GEN4thPt_pass_GEN = new TH1F("GEN4thPt_pass_GEN", "", 150, 0, 150);
  TH1F* GENLeadingLxy_pass_GEN   = new TH1F("GENLeadingLxy_pass_GEN",   "",  40, 0., 20.); //per 0.5cm
  TH1F* GENLeadingLz_pass_GEN    = new TH1F("GENLeadingLz_pass_GEN",    "", 120, 0., 60.); //per 0.5cm

  TH1F* GEN1stPt_pass_1stRECOmu = new TH1F("GEN1stPt_pass_1stRECOmu", "", 150, 0, 150);
  TH1F* GEN2ndPt_pass_2ndRECOmu = new TH1F("GEN2ndPt_pass_2ndRECOmu", "", 150, 0, 150);
  TH1F* GEN3rdPt_pass_3rdRECOmu = new TH1F("GEN3rdPt_pass_3rdRECOmu", "", 150, 0, 150);
  TH1F* GEN4thPt_pass_4thRECOmu = new TH1F("GEN4thPt_pass_4thRECOmu", "", 150, 0, 150);
  TH1F* GEN1stPt_pass_RECOmu12   = new TH1F("GEN1stPt_pass_RECOmu12",   "", 150, 0, 150);
  TH1F* GEN1stPt_pass_RECOmu123  = new TH1F("GEN1stPt_pass_RECOmu123",  "", 150, 0, 150);
  TH1F* GEN1stPt_pass_RECOmu1234 = new TH1F("GEN1stPt_pass_RECOmu1234", "", 150, 0, 150);
  TH1F* GENLeadingLxy_pass_RECOmu1234 = new TH1F("GENLeadingLxy_pass_RECOmu1234",   "",  40, 0., 20.);
  TH1F* GENLeadingLz_pass_RECOmu1234  = new TH1F("GENLeadingLz_pass_RECOmu1234",    "", 120, 0., 60.);

  TH1F* CvtxProbNoSAmu  = new TH1F("CvtxProbNoSAmu",  "Di-#mu0 Vtx Fit Prob. (all PF loose mu)", 1000, 0., 1.);//per 0.001
  TH1F* FvtxProbNoSAmu  = new TH1F("FvtxProbNoSAmu",  "Di-#mu1 Vtx Fit Prob. (all PF loose mu)", 1000, 0., 1.);
  TH1F* CvtxProbSAmuInC = new TH1F("CvtxProbSAmuInC", "Di-#mu0 Vtx Fit Prob. (di-#mu0 has one SA mu)", 1000, 0., 1.);
  TH1F* FvtxProbSAmuInF = new TH1F("FvtxProbSAmuInF", "Di-#mu1 Vtx Fit Prob. (di-#mu1 has one SA mu)", 1000, 0., 1.);

  //Trigger accept eff as function of leading muon pT, eta and phi after cut #9
  TH1F* leading_pt_pass_basic      = new TH1F("leading_pt_pass_basic",      "", 150,    0, 150); //per 1
  TH1F* leading_eta_pass_basic     = new TH1F("leading_eta_pass_basic",     "",  50, -2.5, 2.5); //per 0.1
  TH1F* leading_phi_pass_basic     = new TH1F("leading_phi_pass_basic",     "",  70, -3.5, 3.5); //per 0.1
  TH1F* HLT_leading_pt_pass_basic  = new TH1F("HLT_leading_pt_pass_basic",  "", 150,    0, 150);
  TH1F* HLT_leading_eta_pass_basic = new TH1F("HLT_leading_eta_pass_basic", "",  50, -2.5, 2.5);
  TH1F* HLT_leading_phi_pass_basic = new TH1F("HLT_leading_phi_pass_basic", "",  70, -3.5, 3.5);
  TH1F* L1_leading_pt_pass_basic   = new TH1F("L1_leading_pt_pass_basic",   "", 150,    0, 150);
  TH1F* L1_leading_eta_pass_basic  = new TH1F("L1_leading_eta_pass_basic",  "",  50, -2.5, 2.5);
  TH1F* L1_leading_phi_pass_basic  = new TH1F("L1_leading_phi_pass_basic",  "",  70, -3.5, 3.5);

  TH1F* second_pt_pass_basic      = new TH1F("second_pt_pass_basic",      "", 150,    0, 150);
  TH1F* second_eta_pass_basic     = new TH1F("second_eta_pass_basic",     "",  50, -2.5, 2.5);
  TH1F* second_phi_pass_basic     = new TH1F("second_phi_pass_basic",     "",  70, -3.5, 3.5);
  TH1F* HLT_second_pt_pass_basic  = new TH1F("HLT_second_pt_pass_basic",  "", 150,    0, 150);
  TH1F* HLT_second_eta_pass_basic = new TH1F("HLT_second_eta_pass_basic", "",  50, -2.5, 2.5);
  TH1F* HLT_second_phi_pass_basic = new TH1F("HLT_second_phi_pass_basic", "",  70, -3.5, 3.5);
  TH1F* L1_second_pt_pass_basic   = new TH1F("L1_second_pt_pass_basic",   "", 150,    0, 150);
  TH1F* L1_second_eta_pass_basic  = new TH1F("L1_second_eta_pass_basic",  "",  50, -2.5, 2.5);
  TH1F* L1_second_phi_pass_basic  = new TH1F("L1_second_phi_pass_basic",  "",  70, -3.5, 3.5);

  TH1F* third_pt_pass_basic      = new TH1F("third_pt_pass_basic",      "", 150,    0, 150);
  TH1F* third_eta_pass_basic     = new TH1F("third_eta_pass_basic",     "",  50, -2.5, 2.5);
  TH1F* third_phi_pass_basic     = new TH1F("third_phi_pass_basic",     "",  70, -3.5, 3.5);
  TH1F* HLT_third_pt_pass_basic  = new TH1F("HLT_third_pt_pass_basic",  "", 150,    0, 150);
  TH1F* HLT_third_eta_pass_basic = new TH1F("HLT_third_eta_pass_basic", "",  50, -2.5, 2.5);
  TH1F* HLT_third_phi_pass_basic = new TH1F("HLT_third_phi_pass_basic", "",  70, -3.5, 3.5);
  TH1F* L1_third_pt_pass_basic   = new TH1F("L1_third_pt_pass_basic",   "", 150,    0, 150);
  TH1F* L1_third_eta_pass_basic  = new TH1F("L1_third_eta_pass_basic",  "",  50, -2.5, 2.5);
  TH1F* L1_third_phi_pass_basic  = new TH1F("L1_third_phi_pass_basic",  "",  70, -3.5, 3.5);

  TH1F* fourth_pt_pass_basic      = new TH1F("fourth_pt_pass_basic",      "", 150,    0, 150);
  TH1F* fourth_eta_pass_basic     = new TH1F("fourth_eta_pass_basic",     "",  50, -2.5, 2.5);
  TH1F* fourth_phi_pass_basic     = new TH1F("fourth_phi_pass_basic",     "",  70, -3.5, 3.5);
  TH1F* HLT_fourth_pt_pass_basic  = new TH1F("HLT_fourth_pt_pass_basic",  "", 150,    0, 150);
  TH1F* HLT_fourth_eta_pass_basic = new TH1F("HLT_fourth_eta_pass_basic", "",  50, -2.5, 2.5);
  TH1F* HLT_fourth_phi_pass_basic = new TH1F("HLT_fourth_phi_pass_basic", "",  70, -3.5, 3.5);
  TH1F* L1_fourth_pt_pass_basic   = new TH1F("L1_fourth_pt_pass_basic",   "", 150,    0, 150);
  TH1F* L1_fourth_eta_pass_basic  = new TH1F("L1_fourth_eta_pass_basic",  "",  50, -2.5, 2.5);
  TH1F* L1_fourth_phi_pass_basic  = new TH1F("L1_fourth_phi_pass_basic",  "",  70, -3.5, 3.5);

  //Trigger accept eff as function of leading 4 muons pT, eta and phi after cut #15
  TH1F* leading_pt_pass_all      = new TH1F("leading_pt_pass_all",      "", 150,    0, 150);
  TH1F* leading_eta_pass_all     = new TH1F("leading_eta_pass_all",     "",  50, -2.5, 2.5);
  TH1F* leading_phi_pass_all     = new TH1F("leading_phi_pass_all",     "",  70, -3.5, 3.5);
  TH1F* HLT_leading_pt_pass_all  = new TH1F("HLT_leading_pt_pass_all",  "", 150,    0, 150);
  TH1F* HLT_leading_eta_pass_all = new TH1F("HLT_leading_eta_pass_all", "",  50, -2.5, 2.5);
  TH1F* HLT_leading_phi_pass_all = new TH1F("HLT_leading_phi_pass_all", "",  70, -3.5, 3.5);
  TH1F* L1_leading_pt_pass_all   = new TH1F("L1_leading_pt_pass_all",   "", 150,    0, 150);
  TH1F* L1_leading_eta_pass_all  = new TH1F("L1_leading_eta_pass_all",  "",  50, -2.5, 2.5);
  TH1F* L1_leading_phi_pass_all  = new TH1F("L1_leading_phi_pass_all",  "",  70, -3.5, 3.5);

  TH1F* second_pt_pass_all      = new TH1F("second_pt_pass_all",      "", 150,    0, 150);
  TH1F* second_eta_pass_all     = new TH1F("second_eta_pass_all",     "",  50, -2.5, 2.5);
  TH1F* second_phi_pass_all     = new TH1F("second_phi_pass_all",     "",  70, -3.5, 3.5);
  TH1F* HLT_second_pt_pass_all  = new TH1F("HLT_second_pt_pass_all",  "", 150,    0, 150);
  TH1F* HLT_second_eta_pass_all = new TH1F("HLT_second_eta_pass_all", "",  50, -2.5, 2.5);
  TH1F* HLT_second_phi_pass_all = new TH1F("HLT_second_phi_pass_all", "",  70, -3.5, 3.5);
  TH1F* L1_second_pt_pass_all   = new TH1F("L1_second_pt_pass_all",   "", 150,    0, 150);
  TH1F* L1_second_eta_pass_all  = new TH1F("L1_second_eta_pass_all",  "",  50, -2.5, 2.5);
  TH1F* L1_second_phi_pass_all  = new TH1F("L1_second_phi_pass_all",  "",  70, -3.5, 3.5);

  TH1F* third_pt_pass_all      = new TH1F("third_pt_pass_all",      "", 150,    0, 150);
  TH1F* third_eta_pass_all     = new TH1F("third_eta_pass_all",     "",  50, -2.5, 2.5);
  TH1F* third_phi_pass_all     = new TH1F("third_phi_pass_all",     "",  70, -3.5, 3.5);
  TH1F* HLT_third_pt_pass_all  = new TH1F("HLT_third_pt_pass_all",  "", 150,    0, 150);
  TH1F* HLT_third_eta_pass_all = new TH1F("HLT_third_eta_pass_all", "",  50, -2.5, 2.5);
  TH1F* HLT_third_phi_pass_all = new TH1F("HLT_third_phi_pass_all", "",  70, -3.5, 3.5);
  TH1F* L1_third_pt_pass_all   = new TH1F("L1_third_pt_pass_all",   "", 150,    0, 150);
  TH1F* L1_third_eta_pass_all  = new TH1F("L1_third_eta_pass_all",  "",  50, -2.5, 2.5);
  TH1F* L1_third_phi_pass_all  = new TH1F("L1_third_phi_pass_all",  "",  70, -3.5, 3.5);

  TH1F* fourth_pt_pass_all      = new TH1F("fourth_pt_pass_all",      "", 150,    0, 150);
  TH1F* fourth_eta_pass_all     = new TH1F("fourth_eta_pass_all",     "",  50, -2.5, 2.5);
  TH1F* fourth_phi_pass_all     = new TH1F("fourth_phi_pass_all",     "",  70, -3.5, 3.5);
  TH1F* HLT_fourth_pt_pass_all  = new TH1F("HLT_fourth_pt_pass_all",  "", 150,    0, 150);
  TH1F* HLT_fourth_eta_pass_all = new TH1F("HLT_fourth_eta_pass_all", "",  50, -2.5, 2.5);
  TH1F* HLT_fourth_phi_pass_all = new TH1F("HLT_fourth_phi_pass_all", "",  70, -3.5, 3.5);
  TH1F* L1_fourth_pt_pass_all   = new TH1F("L1_fourth_pt_pass_all",   "", 150,    0, 150);
  TH1F* L1_fourth_eta_pass_all  = new TH1F("L1_fourth_eta_pass_all",  "",  50, -2.5, 2.5);
  TH1F* L1_fourth_phi_pass_all  = new TH1F("L1_fourth_phi_pass_all",  "",  70, -3.5, 3.5);

  //As a function of Lxy at GEN and RECO
  TH1F* genA_leading_Lxy_pass_all   = new TH1F("genA_leading_Lxy_pass_all",   "",  40, 0., 20.); //per 0.5cm
  TH1F* genA_leading_Lz_pass_all    = new TH1F("genA_leading_Lz_pass_all",    "", 120, 0., 60.); //per 0.5cm
  TH1F* diMuon_leading_Lxy_pass_all = new TH1F("diMuon_leading_Lxy_pass_all", "",  40, 0., 20.);
  TH1F* diMuon_leading_Lz_pass_all  = new TH1F("diMuon_leading_Lz_pass_all",  "", 120, 0., 60.);

  TH1F* HLT_genA_leading_Lxy_pass_all   = new TH1F("HLT_genA_leading_Lxy_pass_all",   "",  40, 0., 20.);
  TH1F* HLT_genA_leading_Lz_pass_all    = new TH1F("HLT_genA_leading_Lz_pass_all",    "", 120, 0., 60.);
  TH1F* HLT_diMuon_leading_Lxy_pass_all = new TH1F("HLT_diMuon_leading_Lxy_pass_all", "",  40, 0., 20.);
  TH1F* HLT_diMuon_leading_Lz_pass_all  = new TH1F("HLT_diMuon_leading_Lz_pass_all",  "", 120, 0., 60.);

  //For BKG modeling at high mass 11-59 GeV
  //Control Region/Validation Region
  TH2F *BKGShapeCR      = new TH2F("BKGShapeCR",      "", 12, 11., 59., 12, 11., 59.);//binning 4 GeV
  TH1F *BKGShapeCRmassC = new TH1F("BKGShapeCRmassC", "", 12, 11., 59.);
  TH1F *BKGShapeCRmassF = new TH1F("BKGShapeCRmassF", "", 12, 11., 59.);
  TH1F *NJetCR = new TH1F("NJetCR", "", 100, 0, 100);
  TH1F *NTightBCR  = new TH1F("NTightBCR",  "", 10, 0, 10);
  TH1F *NMediumBCR = new TH1F("NMediumBCR", "", 10, 0, 10);
  TH1F *NLooseBCR  = new TH1F("NLooseBCR",  "", 10, 0, 10);
  TH1F *SAmuNTrkWP1CR = new TH1F("SAmuNTrkWP1CR", "", 100, 0, 100);
  TH1F *SAmuNTrkWP2CR = new TH1F("SAmuNTrkWP2CR", "", 100, 0, 100);
  TH1F *SAmuNTrkWP3CR = new TH1F("SAmuNTrkWP3CR", "", 100, 0, 100);
  TH1F *SAmuTrkIsoWP1CR = new TH1F("SAmuTrkIsoWP1CR", "", 1000, 0, 100);//bin 0.1GeV
  TH1F *SAmuTrkIsoWP2CR = new TH1F("SAmuTrkIsoWP2CR", "", 1000, 0, 100);
  TH1F *SAmuTrkIsoWP3CR = new TH1F("SAmuTrkIsoWP3CR", "", 1000, 0, 100);
  //no dz version
  TH1F *SAmuNTrkNoDzWP1CR = new TH1F("SAmuNTrkNoDzWP1CR", "", 100, 0, 100);
  TH1F *SAmuNTrkNoDzWP2CR = new TH1F("SAmuNTrkNoDzWP2CR", "", 100, 0, 100);
  TH1F *SAmuNTrkNoDzWP3CR = new TH1F("SAmuNTrkNoDzWP3CR", "", 100, 0, 100);
  TH1F *SAmuTrkIsoNoDzWP1CR = new TH1F("SAmuTrkIsoNoDzWP1CR", "", 1000, 0, 100);//bin 0.1GeV
  TH1F *SAmuTrkIsoNoDzWP2CR = new TH1F("SAmuTrkIsoNoDzWP2CR", "", 1000, 0, 100);
  TH1F *SAmuTrkIsoNoDzWP3CR = new TH1F("SAmuTrkIsoNoDzWP3CR", "", 1000, 0, 100);
  TH1F* SAmuPtCR  = new TH1F("SAmuPtCR",  "", 150,    0, 150);//per 1GeV
  TH1F* SAmuEtaCR = new TH1F("SAmuEtaCR", "",  50, -2.5, 2.5);//per 0.1
  TH1F* SAmuPhiCR = new TH1F("SAmuPhiCR", "",  70, -3.5, 3.5);//per 0.1
  //Signal Region
  TH2F *BKGShapeSR      = new TH2F("BKGShapeSR",      "", 12, 11., 59., 12, 11., 59.);
  TH1F *BKGShapeSRmassC = new TH1F("BKGShapeSRmassC", "", 12, 11., 59.);
  TH1F *BKGShapeSRmassF = new TH1F("BKGShapeSRmassF", "", 12, 11., 59.);
  TH1F *NJetSR = new TH1F("NJetSR", "", 100, 0, 100);
  TH1F *NTightBSR  = new TH1F("NTightBSR",  "", 10, 0, 10);
  TH1F *NMediumBSR = new TH1F("NMediumBSR", "", 10, 0, 10);
  TH1F *NLooseBSR  = new TH1F("NLooseBSR",  "", 10, 0, 10);
  TH1F *SAmuNTrkWP1SR = new TH1F("SAmuNTrkWP1SR", "", 100, 0, 100);
  TH1F *SAmuNTrkWP2SR = new TH1F("SAmuNTrkWP2SR", "", 100, 0, 100);
  TH1F *SAmuNTrkWP3SR = new TH1F("SAmuNTrkWP3SR", "", 100, 0, 100);
  TH1F *SAmuTrkIsoWP1SR = new TH1F("SAmuTrkIsoWP1SR", "", 1000, 0, 100);//bin 0.1GeV
  TH1F *SAmuTrkIsoWP2SR = new TH1F("SAmuTrkIsoWP2SR", "", 1000, 0, 100);
  TH1F *SAmuTrkIsoWP3SR = new TH1F("SAmuTrkIsoWP3SR", "", 1000, 0, 100);
  //no dz version
  TH1F *SAmuNTrkNoDzWP1SR = new TH1F("SAmuNTrkNoDzWP1SR", "", 100, 0, 100);
  TH1F *SAmuNTrkNoDzWP2SR = new TH1F("SAmuNTrkNoDzWP2SR", "", 100, 0, 100);
  TH1F *SAmuNTrkNoDzWP3SR = new TH1F("SAmuNTrkNoDzWP3SR", "", 100, 0, 100);
  TH1F *SAmuTrkIsoNoDzWP1SR = new TH1F("SAmuTrkIsoNoDzWP1SR", "", 1000, 0, 100);//bin 0.1GeV
  TH1F *SAmuTrkIsoNoDzWP2SR = new TH1F("SAmuTrkIsoNoDzWP2SR", "", 1000, 0, 100);
  TH1F *SAmuTrkIsoNoDzWP3SR = new TH1F("SAmuTrkIsoNoDzWP3SR", "", 1000, 0, 100);
  TH1F* SAmuPtSR  = new TH1F("SAmuPtSR",  "", 150,    0, 150);//per 1GeV
  TH1F* SAmuEtaSR = new TH1F("SAmuEtaSR", "",  50, -2.5, 2.5);//per 0.1
  TH1F* SAmuPhiSR = new TH1F("SAmuPhiSR", "",  70, -3.5, 3.5);//per 0.1

  TH1F* L_DimuC_CR_HighMass   = new TH1F("L_DimuC_CR_HighMass",   "", 800, 0., 80.);//cm
  TH1F* L_DimuF_CR_HighMass   = new TH1F("L_DimuF_CR_HighMass",   "", 800, 0., 80.);
  TH1F* Lxy_DimuC_CR_HighMass = new TH1F("Lxy_DimuC_CR_HighMass", "", 500, 0., 50.);
  TH1F* Lxy_DimuF_CR_HighMass = new TH1F("Lxy_DimuF_CR_HighMass", "", 500, 0., 50.);
  TH1F* Lz_DimuC_CR_HighMass  = new TH1F("Lz_DimuC_CR_HighMass",  "", 600, 0., 60.);
  TH1F* Lz_DimuF_CR_HighMass  = new TH1F("Lz_DimuF_CR_HighMass",  "", 600, 0., 60.);

  TH1F* L_DimuC_SR_HighMass   = new TH1F("L_DimuC_SR_HighMass",   "", 800, 0., 80.);
  TH1F* L_DimuF_SR_HighMass   = new TH1F("L_DimuF_SR_HighMass",   "", 800, 0., 80.);
  TH1F* Lxy_DimuC_SR_HighMass = new TH1F("Lxy_DimuC_SR_HighMass", "", 500, 0., 50.);
  TH1F* Lxy_DimuF_SR_HighMass = new TH1F("Lxy_DimuF_SR_HighMass", "", 500, 0., 50.);
  TH1F* Lz_DimuC_SR_HighMass  = new TH1F("Lz_DimuC_SR_HighMass",  "", 600, 0., 60.);
  TH1F* Lz_DimuF_SR_HighMass  = new TH1F("Lz_DimuF_SR_HighMass",  "", 600, 0., 60.);

  TH1F *DimuMass = new TH1F("DimuMass", "", 6000, 0., 60.);//binning 0.01 GeV
  TH1F *DimuCMassAfterCut12 = new TH1F("DimuCMassAfterCut12", "Di-#mu #1 Mass after Cut 12", 3000, 0., 60.);//binning 0.02 GeV
  TH1F *DimuFMassAfterCut12 = new TH1F("DimuFMassAfterCut12", "Di-#mu #2 Mass after Cut 12", 3000, 0., 60.);
  TH1F *DimuCMassAfterCut16 = new TH1F("DimuCMassAfterCut16", "Di-#mu #1 Mass after Cut 16", 3000, 0., 60.);
  TH1F *DimuFMassAfterCut16 = new TH1F("DimuFMassAfterCut16", "Di-#mu #2 Mass after Cut 16", 3000, 0., 60.);

  TH1F *RECO4muMass                 = new TH1F("RECO4muMass",                 "", 180, 0., 180.);//binning 1 GeV
  TH1F *RECOrePaired2muLeadingMass  = new TH1F("RECOrePaired2muLeadingMass",  "", 180, 0., 180.);
  TH1F *RECOrePaired2muTrailingMass = new TH1F("RECOrePaired2muTrailingMass", "", 180, 0., 180.);
  TH1F *RECOrePaired2muLeadingdR    = new TH1F("RECOrePaired2muLeadingdR",    "", 450, 0., 4.5);//binning 0.01
  TH1F *RECOrePaired2muTrailingdR   = new TH1F("RECOrePaired2muTrailingdR",   "", 450, 0., 4.5);

  TH1F *dZDimuC   = new TH1F("dZDimuC", "dz of 1st RECO Di-#mu Production Vtx (w.r.t. Beamspot)", 4800, -24, 24);//binning 0.01 cm
  TH1F *dZDimuF   = new TH1F("dZDimuF", "dz of 2nd RECO Di-#mu Production Vtx (w.r.t. Beamspot)", 4800, -24, 24);
  TH1F *dZdimuons = new TH1F("dZdimuons", "dz of RECO Di-#mu Production Vtx", 4800, -24, 24);

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

  t->SetBranchAddress("is1GenMu17",    &is1GenMu17);
	t->SetBranchAddress("is2GenMu8",     &is2GenMu8);
	t->SetBranchAddress("is3GenMu8",     &is3GenMu8);
	t->SetBranchAddress("is4GenMu8",     &is4GenMu8);
  t->SetBranchAddress("genMu0_pT",     &genMu0_pT); //leading mu
  t->SetBranchAddress("genMu1_pT",     &genMu1_pT);
  t->SetBranchAddress("genMu2_pT",     &genMu2_pT);
  t->SetBranchAddress("genMu3_pT",     &genMu3_pT);
  t->SetBranchAddress("genMu0_eta",    &genMu0_eta);
  t->SetBranchAddress("genMu1_eta",    &genMu1_eta);
  t->SetBranchAddress("genMu2_eta",    &genMu2_eta);
  t->SetBranchAddress("genMu3_eta",    &genMu3_eta);
  t->SetBranchAddress("genMu0_phi",    &genMu0_phi);
  t->SetBranchAddress("genMu1_phi",    &genMu1_phi);
  t->SetBranchAddress("genMu2_phi",    &genMu2_phi);
  t->SetBranchAddress("genMu3_phi",    &genMu3_phi);

  t->SetBranchAddress("genA0_Lxy",     &genA0_Lxy);
	t->SetBranchAddress("genA1_Lxy",     &genA1_Lxy);
	t->SetBranchAddress("genA0_Lz",      &genA0_Lz);
	t->SetBranchAddress("genA1_Lz",      &genA1_Lz);
  t->SetBranchAddress("genA0Mu0_pt",   &genA0Mu0_pt);
  t->SetBranchAddress("genA0Mu1_pt",   &genA0Mu1_pt);
  t->SetBranchAddress("genA1Mu0_pt",   &genA1Mu0_pt);
  t->SetBranchAddress("genA1Mu1_pt",   &genA1Mu1_pt);

  t->SetBranchAddress("genA0Mu_dR",    &genA0Mu_dR);
  t->SetBranchAddress("genA1Mu_dR",    &genA1Mu_dR);

	t->SetBranchAddress("is1SelMu17",    &is1SelMu17);
	t->SetBranchAddress("is2SelMu8",     &is2SelMu8);
	t->SetBranchAddress("is3SelMu8",     &is3SelMu8);
	t->SetBranchAddress("is4SelMu8",     &is4SelMu8);
  t->SetBranchAddress("selMu0_pT",     &selMu0_pT); //leading mu
  t->SetBranchAddress("selMu1_pT",     &selMu1_pT);
  t->SetBranchAddress("selMu2_pT",     &selMu2_pT);
  t->SetBranchAddress("selMu3_pT",     &selMu3_pT);
	t->SetBranchAddress("selMu0_eta",    &selMu0_eta);
  t->SetBranchAddress("selMu1_eta",    &selMu1_eta);
  t->SetBranchAddress("selMu2_eta",    &selMu2_eta);
  t->SetBranchAddress("selMu3_eta",    &selMu3_eta);
  t->SetBranchAddress("selMu0_phi",    &selMu0_phi);
  t->SetBranchAddress("selMu1_phi",    &selMu1_phi);
  t->SetBranchAddress("selMu2_phi",    &selMu2_phi);
  t->SetBranchAddress("selMu3_phi",    &selMu3_phi);
  t->SetBranchAddress("muJetC_Mu0_pt", &muJetC_Mu0_pt);
  t->SetBranchAddress("muJetC_Mu1_pt", &muJetC_Mu1_pt);
  t->SetBranchAddress("muJetF_Mu0_pt", &muJetF_Mu0_pt);
  t->SetBranchAddress("muJetF_Mu1_pt", &muJetF_Mu1_pt);
  t->SetBranchAddress("muJetC_Mu0_eta", &muJetC_Mu0_eta);
  t->SetBranchAddress("muJetC_Mu1_eta", &muJetC_Mu1_eta);
  t->SetBranchAddress("muJetF_Mu0_eta", &muJetF_Mu0_eta);
  t->SetBranchAddress("muJetF_Mu1_eta", &muJetF_Mu1_eta);
  t->SetBranchAddress("muJetC_Mu0_phi", &muJetC_Mu0_phi);
  t->SetBranchAddress("muJetC_Mu1_phi", &muJetC_Mu1_phi);
  t->SetBranchAddress("muJetF_Mu0_phi", &muJetF_Mu0_phi);
  t->SetBranchAddress("muJetF_Mu1_phi", &muJetF_Mu1_phi);

  t->SetBranchAddress("isVertexOK", &isVtxOK);
  t->SetBranchAddress("nMuJets",    &nMuJets);
	t->SetBranchAddress("is2MuJets",  &is2MuJets);
  t->SetBranchAddress("is2DiMuons", &is2DiMuons);
  t->SetBranchAddress("nSAMu",      &nSAMu);
  t->SetBranchAddress("dimuC_nSAMu",&dimuC_nSAMu);
  t->SetBranchAddress("dimuF_nSAMu",&dimuF_nSAMu);
  t->SetBranchAddress("nNonTrackerMu", &nNonTrackerMu);
  t->SetBranchAddress("dimuC_nNonTrackerMu", &dimuC_nNonTrackerMu);
  t->SetBranchAddress("dimuF_nNonTrackerMu", &dimuF_nNonTrackerMu);
  t->SetBranchAddress("dimuC_Mu0_SA", &dimuC_Mu0_SA);
  t->SetBranchAddress("dimuC_Mu1_SA", &dimuC_Mu1_SA);
  t->SetBranchAddress("dimuF_Mu0_SA", &dimuF_Mu0_SA);
  t->SetBranchAddress("dimuF_Mu1_SA", &dimuF_Mu1_SA);
  t->SetBranchAddress("SAmu_nTrkWP1", &SAmu_nTrkWP1);
  t->SetBranchAddress("SAmu_nTrkWP2", &SAmu_nTrkWP2);
  t->SetBranchAddress("SAmu_nTrkWP3", &SAmu_nTrkWP3);
  t->SetBranchAddress("SAmu_nTrkNodzWP1", &SAmu_nTrkNodzWP1);
  t->SetBranchAddress("SAmu_nTrkNodzWP2", &SAmu_nTrkNodzWP2);
  t->SetBranchAddress("SAmu_nTrkNodzWP3", &SAmu_nTrkNodzWP3);
  t->SetBranchAddress("SAmu_TrkIsoWP1", &SAmu_TrkIsoWP1);
  t->SetBranchAddress("SAmu_TrkIsoWP2", &SAmu_TrkIsoWP2);
  t->SetBranchAddress("SAmu_TrkIsoWP3", &SAmu_TrkIsoWP3);
  t->SetBranchAddress("SAmu_TrkIsoNodzWP1", &SAmu_TrkIsoNodzWP1);
  t->SetBranchAddress("SAmu_TrkIsoNodzWP2", &SAmu_TrkIsoNodzWP2);
  t->SetBranchAddress("SAmu_TrkIsoNodzWP3", &SAmu_TrkIsoNodzWP3);
  t->SetBranchAddress("diMuonC_FittedVtx_prob",&diMuonC_FittedVtx_prob);
  t->SetBranchAddress("diMuonF_FittedVtx_prob",&diMuonF_FittedVtx_prob);
  t->SetBranchAddress("diMuonC_FittedVtx_dR",  &diMuonC_FittedVtx_dR);
  t->SetBranchAddress("diMuonF_FittedVtx_dR",  &diMuonF_FittedVtx_dR);
  t->SetBranchAddress("diMuonC_FittedVtx_Lxy", &diMuonC_FittedVtx_Lxy);
	t->SetBranchAddress("diMuonC_FittedVtx_L",   &diMuonC_FittedVtx_L);
	t->SetBranchAddress("diMuonF_FittedVtx_Lxy", &diMuonF_FittedVtx_Lxy);
	t->SetBranchAddress("diMuonF_FittedVtx_L",   &diMuonF_FittedVtx_L);
  //Need to use fitted vertex mass, not the muon pair mass
  //In most cases, they are the close, but not necessarily in some cases
  t->SetBranchAddress("diMuonC_FittedVtx_m", &massC);
	t->SetBranchAddress("diMuonF_FittedVtx_m", &massF);
  t->SetBranchAddress("NPATJet",       &NPATJet);
  t->SetBranchAddress("NPATJetTightB", &NPATJetTightB);
  t->SetBranchAddress("NPATJetMediumB",&NPATJetMediumB);
  t->SetBranchAddress("NPATJetLooseB", &NPATJetLooseB);

  t->SetBranchAddress("reco4mu_m",                  &reco4mu_m);
  t->SetBranchAddress("recoRePaired2muleading_m",   &recoRePaired2muleading_m);
  t->SetBranchAddress("recoRePaired2mutrailing_m",  &recoRePaired2mutrailing_m);
  t->SetBranchAddress("recoRePaired2muleading_dR",  &recoRePaired2muleading_dR);
  t->SetBranchAddress("recoRePaired2mutrailing_dR", &recoRePaired2mutrailing_dR);

  t->SetBranchAddress("diMuonC_m1_FittedVtx_hitpix_Phase1", &diMuonC_m1_FittedVtx_hitpix_Phase1);
	t->SetBranchAddress("diMuonC_m2_FittedVtx_hitpix_Phase1", &diMuonC_m2_FittedVtx_hitpix_Phase1);
	t->SetBranchAddress("diMuonF_m1_FittedVtx_hitpix_Phase1", &diMuonF_m1_FittedVtx_hitpix_Phase1);
	t->SetBranchAddress("diMuonF_m2_FittedVtx_hitpix_Phase1", &diMuonF_m2_FittedVtx_hitpix_Phase1);

  t->SetBranchAddress("diMuonC_FittedVtx_dz",          &diMuonC_FittedVtx_dz);
  t->SetBranchAddress("diMuonF_FittedVtx_dz",          &diMuonF_FittedVtx_dz);
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
  //Start Debug: many HLT paths
  t->SetBranchAddress("isSignalHLT_0_Fired",           &isSignalHLT_0_Fired);
  t->SetBranchAddress("isSignalHLT_1_Fired",           &isSignalHLT_1_Fired);
  t->SetBranchAddress("isSignalHLT_2_Fired",           &isSignalHLT_2_Fired);
  t->SetBranchAddress("isSignalHLT_3_Fired",           &isSignalHLT_3_Fired);
  //End Debug: many HLT paths
  t->SetBranchAddress("isSignalHLTFired",              &isSignalHLTFired);
  t->SetBranchAddress("isSignalHLTL1Fired",            &isSignalHLTL1Fired);
  t->SetBranchAddress("is2DiMuonsMassOK_FittedVtx",    &is2DiMuonsMassOK);

  //Get branch from orphan-dimuon tree
  o->SetBranchAddress("orph_passOffLineSelPtEta",    &orph_passOffLineSelPtEta); //offline pT, eta selection same as signal
  o->SetBranchAddress("orph_AllTrackerMu",           &orph_AllTrackerMu); //tracker mu
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
  //For some basic test
  int newcount = 0;
  int newcountmu1st = 0;
  int newcountmu2nd = 0;
  int newcountmu3rd = 0;
  int newcountmu4th = 0;
  int newcountmu12   = 0;
  int newcountmu123  = 0;
  int newcountmu1234 = 0;
  int newcount0SAzeromujet = 0;
  int newcount0SAonemujet = 0;
  int newcount0SAtwomujet = 0;
  int newcount0NonTrkMu = 0;
  int newcount1NonTrkMu = 0;
  int newcount2NonTrkMu = 0;
  int newcount3NonTrkMu = 0;
  int newcount4NonTrkMu = 0;
  int newcount0SAmu = 0;
  int newcount1SAmu = 0;
  int newcount2SAmu = 0;
  Float_t ProbSA = 0;
  Float_t ProbPF = 0.01;
  Float_t E1 = 0.5;
  Float_t E2 = 1.0;
  Float_t R0 = 2.9;
  Float_t P0 = 0.18;
  Float_t C0 = 0.1;
  Float_t N0 = 1.0;
  int newcountHLT = 0;
  int newcountHLT0 = 0;
  int newcountHLT1 = 0;
  int newcountHLT2 = 0;
  int newcountHLT3 = 0;

  if ( verbose ) std::cout << "main tree entries: "<< nentries << std::endl;

  if ( CutFlowTable ) {
    for ( int i = 0; i < nentries; i++ ) {
      t->GetEntry(i);
      if ( verbose && (i % 1000000) == 0  ) std::cout << "Looking at Events " << i << std::endl;
      counter[k][0]++;
      counterGENMatch[k][0]++;

      //std::cout << "run: " << run << ", lumi: " << lumi << ", event: " << event << std::endl;
      //std::cout << ">>> selMu3 pT: " << selMu3_pT << ", eta: " << selMu3_eta << ", phi: " << selMu3_phi << std::endl;
      //std::cout << "    genMu3 pT: " << genMu3_pT << ", eta: " << genMu3_eta << ", phi: " << genMu3_phi << std::endl;
      //Some basic efficiency tests on muon selections
      if (genMu0_pT > 8 && fabs(genMu0_eta) < 2.4 &&
          genMu1_pT > 8 && fabs(genMu1_eta) < 2.4 &&
          genMu2_pT > 8 && fabs(genMu2_eta) < 2.4 &&
          genMu3_pT > 8 && fabs(genMu3_eta) < 2.4 && ( genA0_Lxy < 16.0 && fabs(genA0_Lz) < 51.6 ) && ( genA1_Lxy < 16.0 && fabs(genA1_Lz) < 51.6 ) ) {
            newcount++;

            GEN1stPt_pass_GEN->Fill(genMu0_pT);
            GEN2ndPt_pass_GEN->Fill(genMu1_pT);
            GEN3rdPt_pass_GEN->Fill(genMu2_pT);
            GEN4thPt_pass_GEN->Fill(genMu3_pT);

            GENMudR_A0->Fill(genA0Mu_dR);
            GENMudR_A1->Fill(genA1Mu_dR);

            if ( genA0_Lxy > genA1_Lxy ) GENLeadingLxy_pass_GEN->Fill(genA0_Lxy);
            else GENLeadingLxy_pass_GEN->Fill(genA1_Lxy);

            if ( fabs(genA0_Lz) > fabs(genA1_Lz) ) GENLeadingLz_pass_GEN->Fill(fabs(genA0_Lz));
            else GENLeadingLz_pass_GEN->Fill(fabs(genA1_Lz));

            //selections
            if (selMu0_pT > 8 && fabs(selMu0_eta) < 2.4) {
               newcountmu1st++;
               GEN1stPt_pass_1stRECOmu->Fill(genMu0_pT);
            }

            if (selMu1_pT > 8 && fabs(selMu1_eta) < 2.4) {
               newcountmu2nd++;
               GEN2ndPt_pass_2ndRECOmu->Fill(genMu1_pT);
            }

            if (selMu2_pT > 8 && fabs(selMu2_eta) < 2.4) {
               newcountmu3rd++;
               GEN3rdPt_pass_3rdRECOmu->Fill(genMu2_pT);
            }

            if (selMu3_pT > 8 && fabs(selMu3_eta) < 2.4) {
               newcountmu4th++;
               GEN4thPt_pass_4thRECOmu->Fill(genMu3_pT);
            }

            if (selMu0_pT > 8 && fabs(selMu0_eta) < 2.4 && selMu1_pT > 8 && fabs(selMu1_eta) < 2.4) {
               newcountmu12++;
               GEN1stPt_pass_RECOmu12->Fill(genMu0_pT);
            }

            if (selMu0_pT > 8 && fabs(selMu0_eta) < 2.4 && selMu1_pT > 8 && fabs(selMu1_eta) < 2.4 && selMu2_pT > 8 && fabs(selMu2_eta) < 2.4) {
               newcountmu123++;
               GEN1stPt_pass_RECOmu123->Fill(genMu0_pT);
            }

            if (selMu0_pT > 8 && fabs(selMu0_eta) < 2.4 && selMu1_pT > 8 && fabs(selMu1_eta) < 2.4 && selMu2_pT > 8 && fabs(selMu2_eta) < 2.4 && selMu3_pT > 8 && fabs(selMu3_eta) < 2.4) {
               newcountmu1234++;
               GEN1stPt_pass_RECOmu1234->Fill(genMu0_pT);

               if ( genA0_Lxy > genA1_Lxy ) GENLeadingLxy_pass_RECOmu1234->Fill(genA0_Lxy);
               else GENLeadingLxy_pass_RECOmu1234->Fill(genA1_Lxy);

               if ( fabs(genA0_Lz) > fabs(genA1_Lz) ) GENLeadingLz_pass_RECOmu1234->Fill(fabs(genA0_Lz));
               else GENLeadingLz_pass_RECOmu1234->Fill(fabs(genA1_Lz));
            }

      }//basic gen selections

      //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      //!        Cut Flow Starts@ GEN Level       !
      //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      if ( is1GenMu17 ) {counter[k][1]++; counterGENMatch[k][1]++;} //Ask for one barrel muon pT>17GeV @GEN
      if ( is2GenMu8  ) {counter[k][2]++; counterGENMatch[k][2]++;} //Ask for two muons pT>8GeV (including 1st barrel muon) @GEN
      if ( is3GenMu8  ) {counter[k][3]++; counterGENMatch[k][3]++;} //Ask for three muons pT>8GeV (including 1st barrel muon) @GEN
      if ( is4GenMu8  ) {
        counter[k][4]++;
        counterGENMatch[k][4]++;

        //Phase-0 pixel system (Pre2017): 3rd barrel pixel layer and 2nd fwd layer -> Lxy = 10.2 cm; Lz = 48.5 cm
        //Phase-1 pixel system (2017+2018): 3rd barrel pixel layer and 2nd fwd layer -> Lxy = 10.9 cm; Lz = 39.6 cm
        //Phase-1 pixel system (2017+2018): 4th barrel pixel layer and 3rd fwd layer -> Lxy = 16.0 cm; Lz = 51.6 cm //To be used for Run2
        //[1]Reference: https://iopscience.iop.org/article/10.1088/1748-0221/12/07/C07009/pdf
        //[2]TDR: https://cds.cern.ch/record/1481838/files/CMS-TDR-011.pdf
        if ( ( genA0_Lxy < 16.0 && fabs(genA0_Lz) < 51.6 ) && ( genA1_Lxy < 16.0 && fabs(genA1_Lz) < 51.6 ) ) {
            counter[k][5]++;
            counterGENMatch[k][5]++;

            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++
            //+ Start to use GEN Match counter ONLY, for MC studies +
            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++

            Phase1Pix_GEN_Mu0_pT->Fill(genMu0_pT);
            Phase1Pix_GEN_Mu1_pT->Fill(genMu1_pT);
            Phase1Pix_GEN_Mu2_pT->Fill(genMu2_pT);
            Phase1Pix_GEN_Mu3_pT->Fill(genMu3_pT);
            Phase1Pix_GEN_Mu0_eta->Fill(genMu0_eta);
            Phase1Pix_GEN_Mu1_eta->Fill(genMu1_eta);
            Phase1Pix_GEN_Mu2_eta->Fill(genMu2_eta);
            Phase1Pix_GEN_Mu3_eta->Fill(genMu3_eta);
            Phase1Pix_GEN_Mu0_phi->Fill(genMu0_phi);
            Phase1Pix_GEN_Mu1_phi->Fill(genMu1_phi);
            Phase1Pix_GEN_Mu2_phi->Fill(genMu2_phi);
            Phase1Pix_GEN_Mu3_phi->Fill(genMu3_phi);
            Phase1Pix_GEN_A0_Lxy->Fill(genA0_Lxy);
            Phase1Pix_GEN_A1_Lxy->Fill(genA1_Lxy);
            Phase1Pix_GEN_A0_Lz->Fill(genA0_Lz);
            Phase1Pix_GEN_A1_Lz->Fill(genA1_Lz);
            Phase1Pix_GEN_A0_Mu0_pT->Fill(genA0Mu0_pt);
            Phase1Pix_GEN_A0_Mu1_pT->Fill(genA0Mu1_pt);
            Phase1Pix_GEN_A1_Mu0_pT->Fill(genA1Mu0_pt);
            Phase1Pix_GEN_A1_Mu1_pT->Fill(genA1Mu1_pt);

            Phase1Pix_RECO_Mu0_pT->Fill(selMu0_pT);
            Phase1Pix_RECO_Mu1_pT->Fill(selMu1_pT);
            Phase1Pix_RECO_Mu2_pT->Fill(selMu2_pT);
            Phase1Pix_RECO_Mu3_pT->Fill(selMu3_pT);
            Phase1Pix_RECO_Mu0_eta->Fill(selMu0_eta);
            Phase1Pix_RECO_Mu1_eta->Fill(selMu1_eta);
            Phase1Pix_RECO_Mu2_eta->Fill(selMu2_eta);
            Phase1Pix_RECO_Mu3_eta->Fill(selMu3_eta);
            Phase1Pix_RECO_Mu0_phi->Fill(selMu0_phi);
            Phase1Pix_RECO_Mu1_phi->Fill(selMu1_phi);
            Phase1Pix_RECO_Mu2_phi->Fill(selMu2_phi);
            Phase1Pix_RECO_Mu3_phi->Fill(selMu3_phi);
            Phase1Pix_RECO_DimuC_Mu0_pT->Fill(muJetC_Mu0_pt);
            Phase1Pix_RECO_DimuC_Mu1_pT->Fill(muJetC_Mu1_pt);
            Phase1Pix_RECO_DimuF_Mu0_pT->Fill(muJetF_Mu0_pt);
            Phase1Pix_RECO_DimuF_Mu1_pT->Fill(muJetF_Mu1_pt);

            if ( is1SelMu17 ) counterGENMatch[k][6]++;
            if ( is2SelMu8  ) counterGENMatch[k][7]++;
            if ( is3SelMu8  ) counterGENMatch[k][8]++;
            if ( is4SelMu8  ) {
              counterGENMatch[k][9]++;

              //###########################################################
              // Check trigger efficiency after basic offline pT selections
              // Need to put before "isSignalHLTFired" selector
              //###########################################################
              if ( PerEventTriggerEff ) {
                leading_pt_pass_basic->Fill(selMu0_pT); second_pt_pass_basic->Fill(selMu1_pT); third_pt_pass_basic->Fill(selMu2_pT); fourth_pt_pass_basic->Fill(selMu3_pT);
                leading_eta_pass_basic->Fill(selMu0_eta); second_eta_pass_basic->Fill(selMu1_eta); third_eta_pass_basic->Fill(selMu2_eta); fourth_eta_pass_basic->Fill(selMu3_eta);
                leading_phi_pass_basic->Fill(selMu0_phi); second_phi_pass_basic->Fill(selMu1_phi); third_phi_pass_basic->Fill(selMu2_phi); fourth_phi_pass_basic->Fill(selMu3_phi);

                if ( isSignalHLTFired ) {
                  HLT_leading_pt_pass_basic->Fill(selMu0_pT); HLT_second_pt_pass_basic->Fill(selMu1_pT); HLT_third_pt_pass_basic->Fill(selMu2_pT); HLT_fourth_pt_pass_basic->Fill(selMu3_pT);
                  HLT_leading_eta_pass_basic->Fill(selMu0_eta); HLT_second_eta_pass_basic->Fill(selMu1_eta); HLT_third_eta_pass_basic->Fill(selMu2_eta); HLT_fourth_eta_pass_basic->Fill(selMu3_eta);
                  HLT_leading_phi_pass_basic->Fill(selMu0_phi); HLT_second_phi_pass_basic->Fill(selMu1_phi); HLT_third_phi_pass_basic->Fill(selMu2_phi); HLT_fourth_phi_pass_basic->Fill(selMu3_phi);
                }//HLT accept

                if ( isSignalHLTL1Fired ) {
                  L1_leading_pt_pass_basic->Fill(selMu0_pT); L1_second_pt_pass_basic->Fill(selMu1_pT); L1_third_pt_pass_basic->Fill(selMu2_pT); L1_fourth_pt_pass_basic->Fill(selMu3_pT);
                  L1_leading_eta_pass_basic->Fill(selMu0_eta); L1_second_eta_pass_basic->Fill(selMu1_eta); L1_third_eta_pass_basic->Fill(selMu2_eta); L1_fourth_eta_pass_basic->Fill(selMu3_eta);
                  L1_leading_phi_pass_basic->Fill(selMu0_phi); L1_second_phi_pass_basic->Fill(selMu1_phi); L1_third_phi_pass_basic->Fill(selMu2_phi); L1_fourth_phi_pass_basic->Fill(selMu3_phi);
                }//L1 filter accept

              }//end if PerEventTriggerEff

              if ( isVtxOK ) {
                counterGENMatch[k][10]++;

                if ( nSAMu == 0 && nMuJets == 0 ) newcount0SAzeromujet++;
                if ( nSAMu == 0 && nMuJets == 1 ) newcount0SAonemujet++;
                if ( nSAMu == 0 && nMuJets == 2 ) newcount0SAtwomujet++;

                //nSAMu = dimuC_nSAMu + dimuF_nSAMu
                if ( is2DiMuons && nSAMu <= 1 && diMuonC_FittedVtx_prob > P0*(1 - dimuC_nSAMu)*exp( -( 0.099 + 0.115*diMuonC_FittedVtx_dR + 0.311*pow(diMuonC_FittedVtx_dR, 2) + 0.074*pow(diMuonC_FittedVtx_dR, 3) )*fabs(diMuonC_FittedVtx_Lxy/R0) ) &&
                     diMuonF_FittedVtx_prob > P0*(1 - dimuF_nSAMu)*exp( -( 0.099 + 0.115*diMuonF_FittedVtx_dR + 0.311*pow(diMuonF_FittedVtx_dR, 2) + 0.074*pow(diMuonF_FittedVtx_dR, 3) )*fabs(diMuonF_FittedVtx_Lxy/R0) ) ) {
                  counterGENMatch[k][11]++;

                  if ( ( diMuonC_m1_FittedVtx_hitpix_Phase1 == 1 || diMuonC_m2_FittedVtx_hitpix_Phase1 == 1 ) && ( diMuonF_m1_FittedVtx_hitpix_Phase1 == 1 || diMuonF_m2_FittedVtx_hitpix_Phase1 == 1 ) ) {
                    //!!! Note: this needs to match GEN cut on geometry
                    counterGENMatch[k][12]++;

                    if ( nSAMu == 0 ) {
                      CvtxProbNoSAmu->Fill(diMuonC_FittedVtx_prob);
                      FvtxProbNoSAmu->Fill(diMuonF_FittedVtx_prob);
                    }
                    if ( dimuC_nSAMu == 1 ) CvtxProbSAmuInC->Fill(diMuonC_FittedVtx_prob);
                    if ( dimuF_nSAMu == 1 ) FvtxProbSAmuInF->Fill(diMuonF_FittedVtx_prob);

                    if ( nNonTrackerMu == 0 ) newcount0NonTrkMu++;
                    if ( nNonTrackerMu == 1 ) newcount1NonTrkMu++;
                    if ( nNonTrackerMu == 2 ) newcount2NonTrkMu++;
                    if ( nNonTrackerMu == 3 ) newcount3NonTrkMu++;
                    if ( nNonTrackerMu == 4 ) newcount4NonTrkMu++;
                    if ( nSAMu == 0 ) newcount0SAmu++;
                    if ( nSAMu == 1 ) newcount1SAmu++;
                    if ( nSAMu == 2 ) newcount2SAmu++;

                    DimuCdR->Fill(diMuonC_FittedVtx_dR);
                    DimuFdR->Fill(diMuonF_FittedVtx_dR);

                    if ( ModelSRWidth ) {
                      DimuCMassAfterCut12->Fill(massC);
                      DimuFMassAfterCut12->Fill(massF);
                    }

                    //Note: this needs to be before the cut on dz
                    if ( PlotdZ ) {
                      dZDimuC->Fill(diMuonC_FittedVtx_dz);
                      dZDimuF->Fill(diMuonF_FittedVtx_dz);
                      dZdimuons->Fill(diMuons_dz_FittedVtx);
                    }

                    if ( (massC >= 9.5 && massF >= 9.5 && (recoRePaired2mutrailing_dR >= 0.2 || recoRePaired2mutrailing_m >= 3) ) || (massC > 0 && massC < 9.5 && massF > 0 && massF < 9.5) ) {
                      counterGENMatch[k][13]++;

                      //Note: this needs to be before the cut on iso
                      if ( PlotIso ) {
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


                      if ( diMuonC_IsoTk_FittedVtx < 2.3 && diMuonF_IsoTk_FittedVtx < 2.3 ) {
                        counterGENMatch[k][14]++;

                        //###########################################################
                        // Check trigger efficiency after most selections
                        // Need to put before "isSignalHLTFired" selector
                        //###########################################################
                        if ( PerEventTriggerEff ) {
                          //L1, HLT eff.: denominator
                          leading_pt_pass_all->Fill(selMu0_pT); second_pt_pass_all->Fill(selMu1_pT); third_pt_pass_all->Fill(selMu2_pT); fourth_pt_pass_all->Fill(selMu3_pT);
                          leading_eta_pass_all->Fill(selMu0_eta); second_eta_pass_all->Fill(selMu1_eta); third_eta_pass_all->Fill(selMu2_eta); fourth_eta_pass_all->Fill(selMu3_eta);
                          leading_phi_pass_all->Fill(selMu0_phi); second_phi_pass_all->Fill(selMu1_phi); third_phi_pass_all->Fill(selMu2_phi); fourth_phi_pass_all->Fill(selMu3_phi);

                          if ( isSignalHLTFired ) {
                            HLT_leading_pt_pass_all->Fill(selMu0_pT); HLT_second_pt_pass_all->Fill(selMu1_pT); HLT_third_pt_pass_all->Fill(selMu2_pT); HLT_fourth_pt_pass_all->Fill(selMu3_pT);
                            HLT_leading_eta_pass_all->Fill(selMu0_eta); HLT_second_eta_pass_all->Fill(selMu1_eta); HLT_third_eta_pass_all->Fill(selMu2_eta); HLT_fourth_eta_pass_all->Fill(selMu3_eta);
                            HLT_leading_phi_pass_all->Fill(selMu0_phi); HLT_second_phi_pass_all->Fill(selMu1_phi); HLT_third_phi_pass_all->Fill(selMu2_phi); HLT_fourth_phi_pass_all->Fill(selMu3_phi);
                          }//HLT accept: numerator

                          if ( isSignalHLTL1Fired ) {
                            L1_leading_pt_pass_all->Fill(selMu0_pT); L1_second_pt_pass_all->Fill(selMu1_pT); L1_third_pt_pass_all->Fill(selMu2_pT); L1_fourth_pt_pass_all->Fill(selMu3_pT);
                            L1_leading_eta_pass_all->Fill(selMu0_eta); L1_second_eta_pass_all->Fill(selMu1_eta); L1_third_eta_pass_all->Fill(selMu2_eta); L1_fourth_eta_pass_all->Fill(selMu3_eta);
                            L1_leading_phi_pass_all->Fill(selMu0_phi); L1_second_phi_pass_all->Fill(selMu1_phi); L1_third_phi_pass_all->Fill(selMu2_phi); L1_fourth_phi_pass_all->Fill(selMu3_phi);
                          }//L1 filter accept: numerator

                          if ( genA0_Lxy > genA1_Lxy ) {
                            genA_leading_Lxy_pass_all->Fill(genA0_Lxy);
                            if ( isSignalHLTFired ) HLT_genA_leading_Lxy_pass_all->Fill(genA0_Lxy);
                          }
                          else{
                            genA_leading_Lxy_pass_all->Fill(genA1_Lxy);
                            if ( isSignalHLTFired ) HLT_genA_leading_Lxy_pass_all->Fill(genA1_Lxy);
                          }

                          if ( fabs(genA0_Lz) > fabs(genA1_Lz) ) {
                            genA_leading_Lz_pass_all->Fill(fabs(genA0_Lz));
                            if ( isSignalHLTFired ) HLT_genA_leading_Lz_pass_all->Fill(fabs(genA0_Lz));
                          }
                          else{
                            genA_leading_Lz_pass_all->Fill(fabs(genA1_Lz));
                            if ( isSignalHLTFired ) HLT_genA_leading_Lz_pass_all->Fill(fabs(genA1_Lz));
                          }

                          if ( diMuonC_FittedVtx_Lxy > diMuonF_FittedVtx_Lxy ) {
                            diMuon_leading_Lxy_pass_all->Fill(diMuonC_FittedVtx_Lxy);
                            if ( isSignalHLTFired ) HLT_diMuon_leading_Lxy_pass_all->Fill(diMuonC_FittedVtx_Lxy);
                          }
                          else{
                            diMuon_leading_Lxy_pass_all->Fill(diMuonF_FittedVtx_Lxy);
                            if ( isSignalHLTFired ) HLT_diMuon_leading_Lxy_pass_all->Fill(diMuonF_FittedVtx_Lxy);
                          }

                          if ( sqrt( pow(diMuonC_FittedVtx_L, 2) - pow(diMuonC_FittedVtx_Lxy, 2) ) > sqrt( pow(diMuonF_FittedVtx_L, 2) - pow(diMuonF_FittedVtx_Lxy, 2) ) ) {
                            diMuon_leading_Lz_pass_all->Fill( sqrt( pow(diMuonC_FittedVtx_L, 2) - pow(diMuonC_FittedVtx_Lxy, 2) ) );
                            if ( isSignalHLTFired ) HLT_diMuon_leading_Lz_pass_all->Fill( sqrt( pow(diMuonC_FittedVtx_L, 2) - pow(diMuonC_FittedVtx_Lxy, 2) ) );
                          }
                          else{
                            diMuon_leading_Lz_pass_all->Fill( sqrt( pow(diMuonF_FittedVtx_L, 2) - pow(diMuonF_FittedVtx_Lxy, 2) ) );
                            if ( isSignalHLTFired ) HLT_diMuon_leading_Lz_pass_all->Fill( sqrt( pow(diMuonF_FittedVtx_L, 2) - pow(diMuonF_FittedVtx_Lxy, 2) ) );
                          }
                        }//end if PerEventTriggerEff

                        //START: DEBUG Many HLT paths
                        newcountHLT++;
                        if ( isSignalHLT_0_Fired ) newcountHLT0++;
                        if ( isSignalHLT_1_Fired ) newcountHLT1++;
                        if ( isSignalHLT_2_Fired ) newcountHLT2++;
                        if ( isSignalHLT_3_Fired ) newcountHLT3++;
                        //End: DEBUG Many HLT paths

                        if ( isSignalHLTFired ) {
                          counterGENMatch[k][15]++;

                          //if ( ( massC >= 9.5 && massF >= 9.5 && SAmu_nTrkNodzWP1 < 5 ) || (massC > 0 && massC < 9.5 && massF > 0 && massF < 9.5) ) {
                          if ( ( massC > 0 && massC < 9.5 && massF > 0 && massF < 9.5 ) ||
                               ( massC >= 9.5 && massF >= 9.5 && ( nSAMu == 0 || (dimuC_nSAMu == 1 && diMuonC_FittedVtx_Lxy > 0.1) || (dimuF_nSAMu == 1 && diMuonF_FittedVtx_Lxy > 0.1) ) ) ) {
                            counterGENMatch[k][16]++;

                            if ( ModelSRWidth ) {
                              DimuMass->Fill( (massC+massF)/2 );
                              DimuCMassAfterCut16->Fill(massC);
                              DimuFMassAfterCut16->Fill(massF);
                            }

                            if ( is2DiMuonsMassOK ) counterGENMatch[k][17]++; //end 17
                          }//end 16
                        }//end 15
                      }//end 14
                    }//end 13
                  }//end 12
                }//end 11
              }//end 10
            }//end 9

            //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            //+   End using GEN Match counter ONLY, for signal MC studies  +
            //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

        }//End fiducial volume cut on Phase-1 pixel @GEN
      }//End asking for four muons pT>8GeV (including 1st barrel muon) @GEN
      //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      //!        Cut Flow Ends@ GEN Level         !
      //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

      //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      //!        Cut Flow Starts@ RECO Level      !
      //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      if ( is1SelMu17 ) counter[k][6]++;
      if ( is2SelMu8  ) counter[k][7]++;
      if ( is3SelMu8  ) counter[k][8]++;
      if ( is4SelMu8  ) {
        counter[k][9]++;

        if ( isVtxOK ) {
          counter[k][10]++;

          //nSAMu = dimuC_nSAMu + dimuF_nSAMu
          if ( is2DiMuons && nSAMu <= 1 && diMuonC_FittedVtx_prob > P0*(1 - dimuC_nSAMu)*exp( -( 0.099 + 0.115*diMuonC_FittedVtx_dR + 0.311*pow(diMuonC_FittedVtx_dR, 2) + 0.074*pow(diMuonC_FittedVtx_dR, 3) )*fabs(diMuonC_FittedVtx_Lxy/R0) ) &&
               diMuonF_FittedVtx_prob > P0*(1 - dimuF_nSAMu)*exp( -( 0.099 + 0.115*diMuonF_FittedVtx_dR + 0.311*pow(diMuonF_FittedVtx_dR, 2) + 0.074*pow(diMuonF_FittedVtx_dR, 3) )*fabs(diMuonF_FittedVtx_Lxy/R0) ) ) {
            counter[k][11]++;

            if ( ModelBKGShape ) {
              RECO4muMass->Fill(reco4mu_m);
              RECOrePaired2muLeadingMass->Fill(recoRePaired2muleading_m);
              RECOrePaired2muTrailingMass->Fill(recoRePaired2mutrailing_m);
              RECOrePaired2muLeadingdR->Fill(recoRePaired2muleading_dR);
              RECOrePaired2muTrailingdR->Fill(recoRePaired2mutrailing_dR);
            }//end ModelBKGShape

            if ( ( diMuonC_m1_FittedVtx_hitpix_Phase1 == 1 || diMuonC_m2_FittedVtx_hitpix_Phase1 == 1 ) && ( diMuonF_m1_FittedVtx_hitpix_Phase1 == 1 || diMuonF_m2_FittedVtx_hitpix_Phase1 == 1 ) ) {
              //!!! Note: this needs to match GEN cut on geometry
              counter[k][12]++;

              if ( (massC >= 9.5 && massF >= 9.5 && (recoRePaired2mutrailing_dR >= 0.2 || recoRePaired2mutrailing_m >= 3) ) || (massC > 0 && massC < 9.5 && massF > 0 && massF < 9.5) ) {
                counter[k][13]++;

                if ( diMuonC_IsoTk_FittedVtx < 2.3 && diMuonF_IsoTk_FittedVtx < 2.3 ) {
                  counter[k][14]++;

                  if ( isSignalHLTFired ) {
                    counter[k][15]++;

                    //if ( (massC >= 9.5 && massF >= 9.5 && SAmu_nTrkNodzWP1 < 5 ) || (massC > 0 && massC < 9.5 && massF > 0 && massF < 9.5) ) {
                    if ( ( massC > 0 && massC < 9.5 && massF > 0 && massF < 9.5 ) ||
                         ( massC >= 9.5 && massF >= 9.5 && ( nSAMu == 0 || (dimuC_nSAMu == 1 && diMuonC_FittedVtx_Lxy > 0.1) || (dimuF_nSAMu == 1 && diMuonF_FittedVtx_Lxy > 0.1) ) ) ) {
                      counter[k][16]++;

                      if ( is2DiMuonsMassOK ) {
                        counter[k][17]++;

                        //=================================
                        // All offline selections finished
                        //=================================
                        //std::cout << "run: " << run << ", lumi: " << lumi << ", event: " << event << std::endl;
                        //std::cout << ">>> selMu3 pT: " << selMu3_pT << ", eta: " << selMu3_eta << ", phi: " << selMu3_phi << std::endl;
                        //std::cout << "    genMu3 pT: " << genMu3_pT << ", eta: " << genMu3_eta << ", phi: " << genMu3_phi << std::endl;
                        /*std::cout << ">>> massC: " << massC << "GeV; massF: " << massF << "GeV;"<< std::endl;
                        std::cout << "    1st Dimu Mu0 pT: " << muJetC_Mu0_pt << "GeV; eta: " << muJetC_Mu0_eta << "; phi: " << muJetC_Mu0_phi << std::endl;
                        std::cout << "    1st Dimu Mu1 pT: " << muJetC_Mu1_pt << "GeV; eta: " << muJetC_Mu1_eta << "; phi: " << muJetC_Mu1_phi << std::endl;
                        std::cout << "    2nd Dimu Mu0 pT: " << muJetF_Mu0_pt << "GeV; eta: " << muJetF_Mu0_eta << "; phi: " << muJetF_Mu0_phi << std::endl;
                        std::cout << "    2nd Dimu Mu1 pT: " << muJetF_Mu1_pt << "GeV; eta: " << muJetF_Mu1_eta << "; phi: " << muJetF_Mu1_phi << std::endl;*/

                        if ( ModelBKGShape ) {
                          BKGShapeSR->Fill(massC,massF);
                          BKGShapeSRmassC->Fill(massC);
                          BKGShapeSRmassF->Fill(massF);

                          //Number of jets
                          NJetSR->Fill(NPATJet);
                          //Number of B jets
                          NTightBSR->Fill(NPATJetTightB);
                          NMediumBSR->Fill(NPATJetMediumB);
                          NLooseBSR->Fill(NPATJetLooseB);

                          //SA mu iso and trk multiplicity
                          SAmuNTrkWP1SR->Fill(SAmu_nTrkWP1);
                          SAmuNTrkWP2SR->Fill(SAmu_nTrkWP2);
                          SAmuNTrkWP3SR->Fill(SAmu_nTrkWP3);
                          SAmuTrkIsoWP1SR->Fill(SAmu_TrkIsoWP1);
                          SAmuTrkIsoWP2SR->Fill(SAmu_TrkIsoWP2);
                          SAmuTrkIsoWP3SR->Fill(SAmu_TrkIsoWP3);
                          //no dz version
                          SAmuNTrkNoDzWP1SR->Fill(SAmu_nTrkNodzWP1);
                          SAmuNTrkNoDzWP2SR->Fill(SAmu_nTrkNodzWP2);
                          SAmuNTrkNoDzWP3SR->Fill(SAmu_nTrkNodzWP3);
                          SAmuTrkIsoNoDzWP1SR->Fill(SAmu_TrkIsoNodzWP1);
                          SAmuTrkIsoNoDzWP2SR->Fill(SAmu_TrkIsoNodzWP2);
                          SAmuTrkIsoNoDzWP3SR->Fill(SAmu_TrkIsoNodzWP3);
                          if( dimuC_Mu0_SA ){
                            SAmuPtSR->Fill(muJetC_Mu0_pt); SAmuEtaSR->Fill(muJetC_Mu0_eta); SAmuPhiSR->Fill(muJetC_Mu0_phi);
                            L_DimuC_SR_HighMass->Fill(fabs(diMuonC_FittedVtx_L));
                            Lxy_DimuC_SR_HighMass->Fill(fabs(diMuonC_FittedVtx_Lxy));
                            Lz_DimuC_SR_HighMass->Fill( sqrt( pow(diMuonC_FittedVtx_L,2) - pow(diMuonC_FittedVtx_Lxy,2) ) );
                          }
                          if( dimuC_Mu1_SA ){
                            SAmuPtSR->Fill(muJetC_Mu1_pt); SAmuEtaSR->Fill(muJetC_Mu1_eta); SAmuPhiSR->Fill(muJetC_Mu1_phi);
                            L_DimuC_SR_HighMass->Fill(fabs(diMuonC_FittedVtx_L));
                            Lxy_DimuC_SR_HighMass->Fill(fabs(diMuonC_FittedVtx_Lxy));
                            Lz_DimuC_SR_HighMass->Fill( sqrt( pow(diMuonC_FittedVtx_L,2) - pow(diMuonC_FittedVtx_Lxy,2) ) );
                          }
                          if( dimuF_Mu0_SA ){
                            SAmuPtSR->Fill(muJetF_Mu0_pt); SAmuEtaSR->Fill(muJetF_Mu0_eta); SAmuPhiSR->Fill(muJetF_Mu0_phi);
                            L_DimuF_SR_HighMass->Fill(fabs(diMuonF_FittedVtx_L));
                            Lxy_DimuF_SR_HighMass->Fill(fabs(diMuonF_FittedVtx_Lxy));
                            Lz_DimuF_SR_HighMass->Fill( sqrt( pow(diMuonF_FittedVtx_L,2) - pow(diMuonF_FittedVtx_Lxy,2) ) );
                          }
                          if( dimuF_Mu1_SA ){
                            SAmuPtSR->Fill(muJetF_Mu1_pt); SAmuEtaSR->Fill(muJetF_Mu1_eta); SAmuPhiSR->Fill(muJetF_Mu1_phi);
                            L_DimuF_SR_HighMass->Fill(fabs(diMuonF_FittedVtx_L));
                            Lxy_DimuF_SR_HighMass->Fill(fabs(diMuonF_FittedVtx_Lxy));
                            Lz_DimuF_SR_HighMass->Fill( sqrt( pow(diMuonF_FittedVtx_L,2) - pow(diMuonF_FittedVtx_Lxy,2) ) );
                          }
                        }//end if ModelBKGShape
                      }//end 17
                      else{
                        //================================================
                        //               2D mass control region
                        //Validation region on data and MC for high mass BKG
                        //=================================================
                        if ( ModelBKGShape ) {
                          BKGShapeCR->Fill(massC,massF);
                          BKGShapeCRmassC->Fill(massC);
                          BKGShapeCRmassF->Fill(massF);

                          //Number of jets
                          NJetCR->Fill(NPATJet);
                          //Number of B jets
                          NTightBCR->Fill(NPATJetTightB);
                          NMediumBCR->Fill(NPATJetMediumB);
                          NLooseBCR->Fill(NPATJetLooseB);

                          //SA mu iso and trk multiplicity
                          SAmuNTrkWP1CR->Fill(SAmu_nTrkWP1);
                          SAmuNTrkWP2CR->Fill(SAmu_nTrkWP2);
                          SAmuNTrkWP3CR->Fill(SAmu_nTrkWP3);
                          SAmuTrkIsoWP1CR->Fill(SAmu_TrkIsoWP1);
                          SAmuTrkIsoWP2CR->Fill(SAmu_TrkIsoWP2);
                          SAmuTrkIsoWP3CR->Fill(SAmu_TrkIsoWP3);
                          //no dz version
                          SAmuNTrkNoDzWP1CR->Fill(SAmu_nTrkNodzWP1);
                          SAmuNTrkNoDzWP2CR->Fill(SAmu_nTrkNodzWP2);
                          SAmuNTrkNoDzWP3CR->Fill(SAmu_nTrkNodzWP3);
                          SAmuTrkIsoNoDzWP1CR->Fill(SAmu_TrkIsoNodzWP1);
                          SAmuTrkIsoNoDzWP2CR->Fill(SAmu_TrkIsoNodzWP2);
                          SAmuTrkIsoNoDzWP3CR->Fill(SAmu_TrkIsoNodzWP3);
                          if( dimuC_Mu0_SA ){
                            SAmuPtCR->Fill(muJetC_Mu0_pt); SAmuEtaCR->Fill(muJetC_Mu0_eta); SAmuPhiCR->Fill(muJetC_Mu0_phi);
                            L_DimuC_CR_HighMass->Fill(fabs(diMuonC_FittedVtx_L));
                            Lxy_DimuC_CR_HighMass->Fill(fabs(diMuonC_FittedVtx_Lxy));
                            Lz_DimuC_CR_HighMass->Fill( sqrt( pow(diMuonC_FittedVtx_L,2) - pow(diMuonC_FittedVtx_Lxy,2) ) );
                          }
                          if( dimuC_Mu1_SA ){
                            SAmuPtCR->Fill(muJetC_Mu1_pt); SAmuEtaCR->Fill(muJetC_Mu1_eta); SAmuPhiCR->Fill(muJetC_Mu1_phi);
                            L_DimuC_CR_HighMass->Fill(fabs(diMuonC_FittedVtx_L));
                            Lxy_DimuC_CR_HighMass->Fill(fabs(diMuonC_FittedVtx_Lxy));
                            Lz_DimuC_CR_HighMass->Fill( sqrt( pow(diMuonC_FittedVtx_L,2) - pow(diMuonC_FittedVtx_Lxy,2) ) );
                          }
                          if( dimuF_Mu0_SA ){
                            SAmuPtCR->Fill(muJetF_Mu0_pt); SAmuEtaCR->Fill(muJetF_Mu0_eta); SAmuPhiCR->Fill(muJetF_Mu0_phi);
                            L_DimuF_CR_HighMass->Fill(fabs(diMuonF_FittedVtx_L));
                            Lxy_DimuF_CR_HighMass->Fill(fabs(diMuonF_FittedVtx_Lxy));
                            Lz_DimuF_CR_HighMass->Fill( sqrt( pow(diMuonF_FittedVtx_L,2) - pow(diMuonF_FittedVtx_Lxy,2) ) );
                          }
                          if( dimuF_Mu1_SA ){
                            SAmuPtCR->Fill(muJetF_Mu1_pt); SAmuEtaCR->Fill(muJetF_Mu1_eta); SAmuPhiCR->Fill(muJetF_Mu1_phi);
                            L_DimuF_CR_HighMass->Fill(fabs(diMuonF_FittedVtx_L));
                            Lxy_DimuF_CR_HighMass->Fill(fabs(diMuonF_FittedVtx_Lxy));
                            Lz_DimuF_CR_HighMass->Fill( sqrt( pow(diMuonF_FittedVtx_L,2) - pow(diMuonF_FittedVtx_Lxy,2) ) );
                          }
                        }//end if ModelBKGShape
                      }//end else in loop 17
                    }//end 16
                  }//end 15
                }//end 14
              }//end 13
            }//end 12
          }//end 11
        }//end 10
      }//end 9

      //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      //!        Cut Flow Ends@ RECO Level        !
      //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    }//end for i entries
  }//end CutFlowTable

  std::cout << "-------------------------" << std::endl;
  std::cout << "GEN-8-8-8-8@PIX: " << newcount << std::endl;
  std::cout << "RECO1stMu8: "      << newcountmu1st << std::endl;
  std::cout << "RECO2ndMu8: "      << newcountmu2nd << std::endl;
  std::cout << "RECO3rdMu8: "      << newcountmu3rd << std::endl;
  std::cout << "RECO4thMu8: "      << newcountmu4th << std::endl;
  std::cout << "RECO1+2Mu8: "      << newcountmu12  << std::endl;
  std::cout << "RECO1+2+3Mu8: "    << newcountmu123 << std::endl;
  std::cout << "RECO1+2+3+4Mu8: "  << newcountmu1234 << std::endl;
  std::cout << "-------------------------" << std::endl;
  std::cout << "GEN matched cut 10: " << counterGENMatch[k][10] << std::endl;
  std::cout << "0 SA mu, 0 mujet: "  << newcount0SAzeromujet << std::endl;
  std::cout << "0 SA mu, 1 mujet: "  << newcount0SAonemujet << std::endl;
  std::cout << "0 SA mu, 2 mujet: "  << newcount0SAtwomujet << std::endl;
  std::cout << "-------------------------" << std::endl;
  std::cout << "GEN matched cut 11: " << counterGENMatch[k][11] << std::endl;
  std::cout << "GEN matched cut 12: " << counterGENMatch[k][12] << std::endl;
  std::cout << "2 dimu, 0 Non-Tracker mu: "  << newcount0NonTrkMu << std::endl;
  std::cout << "2 dimu, 1 Non-Tracker mu: "  << newcount1NonTrkMu << std::endl;
  std::cout << "2 dimu, 2 Non-Tracker mu: "  << newcount2NonTrkMu << std::endl;
  std::cout << "2 dimu, 3 Non-Tracker mu: "  << newcount3NonTrkMu << std::endl;
  std::cout << "2 dimu, 4 Non-Tracker mu: "  << newcount4NonTrkMu << std::endl;
  std::cout << "2 dimu, 0 SA mu: "  << newcount0SAmu << std::endl;
  std::cout << "2 dimu, 1 SA mu: "  << newcount1SAmu << std::endl;
  std::cout << "2 dimu, 2 SA mu: "  << newcount2SAmu << std::endl;
  std::cout << "-------------------------" << std::endl;
  //Start: DEBUG many HLT
  std::cout << "HLT0: "  << newcountHLT0*1.0/newcountHLT << std::endl;
  std::cout << "HLT1: "  << newcountHLT1*1.0/newcountHLT << std::endl;
  std::cout << "HLT2: "  << newcountHLT2*1.0/newcountHLT << std::endl;
  std::cout << "HLT3: "  << newcountHLT3*1.0/newcountHLT << std::endl;
  std::cout << "-------------------------" << std::endl;
  //End: DEBUG many HLT

  //Loop over orphan-dimuon tree
  mentries = o->GetEntries();
  if ( verbose ) std::cout << "orphan-dimu tree entries: "<< mentries << std::endl;

  if ( LoopOrphanTree ) {
    for ( int j = 0; j < mentries; j++ ) {
      if ( verbose && (j % 1000000) == 0 ) std::cout << "Looking at Events_orphan " << j << std::endl;
      o->GetEntry(j);

      //Pass offline basic selections, same as signal for isolation cut study
      if ( PlotIso && orph_passOffLineSelPtEta && orph_AllTrackerMu ) {
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
      if ( ( ModelBKGShape || Model1DTemplate ) && orph_passOffLineSelPtEta && orph_AllTrackerMu && orph_isSignalHLTFired && orph_isVertexOK && ( orph_dimu_Mu0_hitpix_Phase1 == 1 || orph_dimu_Mu1_hitpix_Phase1 == 1 ) && orph_dimu_Mu0_isoTk0p3 >= 0.0 && orph_dimu_Mu0_isoTk0p3 < 1.5 ) {
        Mass1DTemplate->Fill(orph_dimu_mass);
      }
    }//end for j entries
  }//end LoopOrphanTree

  RelEff[k][0] = counter[k][0]/(counter[k][0]*1.0);
  for (int m=0;m<18;m++) {
    TotEff[k][m]= counter[k][m]/(counter[k][0]*1.0);
    TotEffErr[k][m]= sqrt( (TotEff[k][m]*(1-TotEff[k][m]))/(counter[k][0]*1.0));
    if ( m>0 ) {
      if ( m == 6 ) {
        RelEff[k][m]= counter[k][m]/(counter[k][0]*1.0);
        RelEffErr[k][m]= sqrt( (RelEff[k][m]*(1-RelEff[k][m]))/(counter[k][0]*1.0));
      }
      else {
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

  cout<<" #   Selection             & "<<left<< setw(11)<<" \\# Evts "    <<" & "<<left << setw(13) << " Tot. Eff. " << " & " << left << setw(13) << " Rel. Eff. "<<" & "<< left << setw(16) << " Tot. Eff. Err. "<<" & "<< left << setw(16) << " Rel. Eff. Err. " <<" hline "<<endl;
  cout<<" #0  No cut                & "<<left<< setw(11)<< counter[k][0]  <<" & "<<left << setw(13) <<setprecision(3)<< TotEff[k][0]  << " & " << left << setw(13) <<setprecision(3)<< RelEff[k][0] <<" & "<< left << setw(16) <<setprecision(3)<< TotEffErr[k][0]   <<" & "<< left << setw(16) <<setprecision(3)<< RelEffErr[k][0]    <<" hline "<<endl;
  cout<<" #1  1GenMu17Barrel        & "<<left<< setw(11)<< counter[k][1]  <<" & "<<left << setw(13) <<setprecision(3)<< TotEff[k][1]  << " & " << left << setw(13) <<setprecision(3)<< RelEff[k][1] <<" & "<< left << setw(16) <<setprecision(3)<< TotEffErr[k][1]   <<" & "<< left << setw(16) <<setprecision(3)<< RelEffErr[k][1]    <<" hline "<<endl;
  cout<<" #2  2GenMu8               & "<<left<< setw(11)<< counter[k][2]  <<" & "<<left << setw(13) <<setprecision(3)<< TotEff[k][2]  << " & " << left << setw(13) <<setprecision(3)<< RelEff[k][2] <<" & "<< left << setw(16) <<setprecision(3)<< TotEffErr[k][2]   <<" & "<< left << setw(16) <<setprecision(3)<< RelEffErr[k][2]    <<" hline "<<endl;
  cout<<" #3  3GenMu8               & "<<left<< setw(11)<< counter[k][3]  <<" & "<<left << setw(13) <<setprecision(3)<< TotEff[k][3]  << " & " << left << setw(13) <<setprecision(3)<< RelEff[k][3] <<" & "<< left << setw(16) <<setprecision(3)<< TotEffErr[k][3]   <<" & "<< left << setw(16) <<setprecision(3)<< RelEffErr[k][3]    <<" hline "<<endl;
  cout<<" #4  4GenMu8               & "<<left<< setw(11)<< counter[k][4]  <<" & "<<left << setw(13) <<setprecision(3)<< TotEff[k][4]  << " & " << left << setw(13) <<setprecision(3)<< RelEff[k][4] <<" & "<< left << setw(16) <<setprecision(3)<< TotEffErr[k][4]   <<" & "<< left << setw(16) <<setprecision(3)<< RelEffErr[k][4]    <<" hline "<<endl;
  cout<<" #5  BothDecayinPhase1Pix  & "<<left<< setw(11)<< counter[k][5]  <<" & "<<left << setw(13) <<setprecision(3)<< TotEff[k][5]  << " & " << left << setw(13) <<setprecision(3)<< RelEff[k][5] <<" & "<< left << setw(16) <<setprecision(3)<< TotEffErr[k][5]   <<" & "<< left << setw(16) <<setprecision(3)<< RelEffErr[k][5]    <<" hline "<<endl;
  cout<<"                                                                                                                            " << " hline "<< endl;

  cout<<" #6  1RecoMu17Barrel       & "<<left<< setw(11)<< counter[k][6]  <<" & "<<left << setw(13) <<setprecision(3)<< TotEff[k][6]  << " & " << left << setw(13) <<setprecision(3)<< RelEff[k][6] <<" & "<< left << setw(16) <<setprecision(3)<< TotEffErr[k][6]   <<" & "<< left << setw(16) <<setprecision(3)<< RelEffErr[k][6]    <<" hline "<<endl;
  cout<<" #7  2RecoMu8              & "<<left<< setw(11)<< counter[k][7]  <<" & "<<left << setw(13) <<setprecision(3)<< TotEff[k][7]  << " & " << left << setw(13) <<setprecision(3)<< RelEff[k][7] <<" & "<< left << setw(16) <<setprecision(3)<< TotEffErr[k][7]   <<" & "<< left << setw(16) <<setprecision(3)<< RelEffErr[k][7]    <<" hline "<<endl;
  cout<<" #8  3RecoMu8              & "<<left<< setw(11)<< counter[k][8]  <<" & "<<left << setw(13) <<setprecision(3)<< TotEff[k][8]  << " & " << left << setw(13) <<setprecision(3)<< RelEff[k][8] <<" & "<< left << setw(16) <<setprecision(3)<< TotEffErr[k][8]   <<" & "<< left << setw(16) <<setprecision(3)<< RelEffErr[k][8]    <<" hline "<<endl;
  cout<<" #9  4RecoMu8              & "<<left<< setw(11)<< counter[k][9]  <<" & "<<left << setw(13) <<setprecision(3)<< TotEff[k][9]  << " & " << left << setw(13) <<setprecision(3)<< RelEff[k][9] <<" & "<< left << setw(16) <<setprecision(3)<< TotEffErr[k][9]   <<" & "<< left << setw(16) <<setprecision(3)<< RelEffErr[k][9]    <<" hline "<<endl;
  cout<<" #10 PrimaryVtxOK          & "<<left<< setw(11)<< counter[k][10] <<" & "<<left << setw(13) <<setprecision(3)<< TotEff[k][10] << " & " << left << setw(13) <<setprecision(3)<< RelEff[k][10]<<" & "<< left << setw(16) <<setprecision(3)<< TotEffErr[k][10]  <<" & "<< left << setw(16) <<setprecision(3)<< RelEffErr[k][10]   <<" hline "<<endl;
  cout<<" #11 2CandDimuMindM        & "<<left<< setw(11)<< counter[k][11] <<" & "<<left << setw(13) <<setprecision(3)<< TotEff[k][11] << " & " << left << setw(13) <<setprecision(3)<< RelEff[k][11]<<" & "<< left << setw(16) <<setprecision(3)<< TotEffErr[k][11]  <<" & "<< left << setw(16) <<setprecision(3)<< RelEffErr[k][11]   <<" hline "<<endl;
  cout<<" #12 2DimuPixHitOK         & "<<left<< setw(11)<< counter[k][12] <<" & "<<left << setw(13) <<setprecision(3)<< TotEff[k][12] << " & " << left << setw(13) <<setprecision(3)<< RelEff[k][12]<<" & "<< left << setw(16) <<setprecision(3)<< TotEffErr[k][12]  <<" & "<< left << setw(16) <<setprecision(3)<< RelEffErr[k][12]   <<" hline "<<endl;
  cout<<" #13 VetoDYQEDRadiate      & "<<left<< setw(11)<< counter[k][13] <<" & "<<left << setw(13) <<setprecision(3)<< TotEff[k][13] << " & " << left << setw(13) <<setprecision(3)<< RelEff[k][13]<<" & "<< left << setw(16) <<setprecision(3)<< TotEffErr[k][13]  <<" & "<< left << setw(16) <<setprecision(3)<< RelEffErr[k][13]   <<" hline "<<endl;
  cout<<" #14 2DimuIsoOK            & "<<left<< setw(11)<< counter[k][14] <<" & "<<left << setw(13) <<setprecision(3)<< TotEff[k][14] << " & " << left << setw(13) <<setprecision(3)<< RelEff[k][14]<<" & "<< left << setw(16) <<setprecision(3)<< TotEffErr[k][14]  <<" & "<< left << setw(16) <<setprecision(3)<< RelEffErr[k][14]   <<" hline "<<endl;
  cout<<" #15 SignalHLTAccepted     & "<<left<< setw(11)<< counter[k][15] <<" & "<<left << setw(13) <<setprecision(3)<< TotEff[k][15] << " & " << left << setw(13) <<setprecision(3)<< RelEff[k][15]<<" & "<< left << setw(16) <<setprecision(3)<< TotEffErr[k][15]  <<" & "<< left << setw(16) <<setprecision(3)<< RelEffErr[k][15]   <<" hline "<<endl;
  cout<<" #16 SA-only Muon Cut      & "<<left<< setw(11)<< counter[k][16] <<" & "<<left << setw(13) <<setprecision(3)<< TotEff[k][16] << " & " << left << setw(13) <<setprecision(3)<< RelEff[k][16]<<" & "<< left << setw(16) <<setprecision(3)<< TotEffErr[k][16]  <<" & "<< left << setw(16) <<setprecision(3)<< RelEffErr[k][16]   <<" hline "<<endl;
  cout<<" #17 2DimuMassOK           & "<<left<< setw(11)<< counter[k][17] <<" & "<<left << setw(13) <<setprecision(3)<< TotEff[k][17] << " & " << left << setw(13) <<setprecision(3)<< RelEff[k][17]<<" & "<< left << setw(16) <<setprecision(3)<< TotEffErr[k][17]  <<" & "<< left << setw(16) <<setprecision(3)<< RelEffErr[k][17]   <<" hline "<<endl;
  cout<<"                                                                                                                         " << " hline "<< endl;
  cout<<" epsilon_rec/alpha_gen     & "<<setprecision(3)<< epsvsalph[k]  << " $\\pm$ "  << Err[k]<<" hline "<<endl;

  cout<<"end{tabular}"<<endl;
  cout<<"end{landscape}"<<endl;

  //kth sample
  TString output="";
  output = output + "./foo_modified_sample_" + Form("%d", k+1)+ ".root";
  TFile myPlot(output,"RECREATE");

  genA_leading_Lxy_pass_all->GetXaxis()->SetTitle("Lxy [cm]"); genA_leading_Lxy_pass_all->GetYaxis()->SetTitle("Events/0.5 cm"); genA_leading_Lxy_pass_all->Write();
  genA_leading_Lz_pass_all->GetXaxis()->SetTitle("Lz [cm]");   genA_leading_Lz_pass_all->GetYaxis()->SetTitle("Events/0.5 cm");  genA_leading_Lz_pass_all->Write();
  HLT_genA_leading_Lxy_pass_all->GetXaxis()->SetTitle("Lxy [cm]"); HLT_genA_leading_Lxy_pass_all->GetYaxis()->SetTitle("Events/0.5 cm"); HLT_genA_leading_Lxy_pass_all->Write();
  HLT_genA_leading_Lz_pass_all->GetXaxis()->SetTitle("Lxy [cm]");  HLT_genA_leading_Lz_pass_all->GetYaxis()->SetTitle("Events/0.5 cm");  HLT_genA_leading_Lz_pass_all->Write();
  diMuon_leading_Lxy_pass_all->GetXaxis()->SetTitle("Lxy [cm]"); diMuon_leading_Lxy_pass_all->GetYaxis()->SetTitle("Events/0.5 cm"); diMuon_leading_Lxy_pass_all->Write();
  diMuon_leading_Lz_pass_all->GetXaxis()->SetTitle("Lz [cm]");   diMuon_leading_Lz_pass_all->GetYaxis()->SetTitle("Events/0.5 cm");  diMuon_leading_Lz_pass_all->Write();
  HLT_diMuon_leading_Lxy_pass_all->GetXaxis()->SetTitle("Lxy [cm]"); HLT_diMuon_leading_Lxy_pass_all->GetYaxis()->SetTitle("Events/0.5 cm"); HLT_diMuon_leading_Lxy_pass_all->Write();
  HLT_diMuon_leading_Lz_pass_all->GetXaxis()->SetTitle("Lz [cm]");   HLT_diMuon_leading_Lz_pass_all->GetYaxis()->SetTitle("Events/0.5 cm");  HLT_diMuon_leading_Lz_pass_all->Write();

  GENMudR_A0->GetXaxis()->SetTitle("#DeltaR of muons from leading pT GEN boson");     GENMudR_A0->GetYaxis()->SetTitle("Events/0.1"); GENMudR_A0->Write();
  GENMudR_A1->GetXaxis()->SetTitle("#DeltaR of muons from sub-leading pT GEN boson"); GENMudR_A1->GetYaxis()->SetTitle("Events/0.1"); GENMudR_A1->Write();

  CvtxProbNoSAmu->GetXaxis()->SetTitle("Vtx Prob.");  CvtxProbNoSAmu->GetYaxis()->SetTitle("Events/0.001");  CvtxProbNoSAmu->Write();
  FvtxProbNoSAmu->GetXaxis()->SetTitle("Vtx Prob.");  FvtxProbNoSAmu->GetYaxis()->SetTitle("Events/0.001");  FvtxProbNoSAmu->Write();
  CvtxProbSAmuInC->GetXaxis()->SetTitle("Vtx Prob."); CvtxProbSAmuInC->GetYaxis()->SetTitle("Events/0.001"); CvtxProbSAmuInC->Write();
  FvtxProbSAmuInF->GetXaxis()->SetTitle("Vtx Prob."); FvtxProbSAmuInF->GetYaxis()->SetTitle("Events/0.001"); FvtxProbSAmuInF->Write();

  DimuCdR->GetXaxis()->SetTitle("#DeltaR"); DimuCdR->GetYaxis()->SetTitle("Events/0.1"); DimuCdR->Write();
  DimuFdR->GetXaxis()->SetTitle("#DeltaR"); DimuFdR->GetYaxis()->SetTitle("Events/0.1"); DimuFdR->Write();

  Lxy->cd();
  Phase1Pix_GEN_A0_Lxy->SetLineColor(2); Phase1Pix_GEN_A0_Lxy->SetLineStyle(1); Phase1Pix_GEN_A0_Lxy->GetXaxis()->SetTitle("L_{xy} [cm]"); Phase1Pix_GEN_A0_Lxy->GetYaxis()->SetTitle("Events/0.5 cm"); Phase1Pix_GEN_A0_Lxy->Draw();
  Phase1Pix_GEN_A1_Lxy->SetLineColor(2); Phase1Pix_GEN_A1_Lxy->SetLineStyle(2); Phase1Pix_GEN_A1_Lxy->GetXaxis()->SetTitle("L_{xy} [cm]"); Phase1Pix_GEN_A1_Lxy->GetYaxis()->SetTitle("Events/0.5 cm"); Phase1Pix_GEN_A1_Lxy->Draw("SAME");
  Lxy->Write();

  Lz->cd();
  Phase1Pix_GEN_A0_Lz->SetLineColor(4); Phase1Pix_GEN_A0_Lz->SetLineStyle(1); Phase1Pix_GEN_A0_Lz->GetXaxis()->SetTitle("L_{z} [cm]"); Phase1Pix_GEN_A0_Lz->GetYaxis()->SetTitle("Events/0.5 cm"); Phase1Pix_GEN_A0_Lz->Draw();
  Phase1Pix_GEN_A1_Lz->SetLineColor(4); Phase1Pix_GEN_A1_Lz->SetLineStyle(2); Phase1Pix_GEN_A1_Lz->GetXaxis()->SetTitle("L_{z} [cm]"); Phase1Pix_GEN_A1_Lz->GetYaxis()->SetTitle("Events/0.5 cm"); Phase1Pix_GEN_A1_Lz->Draw("SAME");
  Lz->Write();

  GENMuPt->cd();
  Phase1Pix_GEN_Mu0_pT->SetLineColor(1); Phase1Pix_GEN_Mu0_pT->GetXaxis()->SetTitle("p_{T} [GeV]"); Phase1Pix_GEN_Mu0_pT->GetYaxis()->SetTitle("Events/GeV"); Phase1Pix_GEN_Mu0_pT->Draw();
  Phase1Pix_GEN_Mu1_pT->SetLineColor(2); Phase1Pix_GEN_Mu1_pT->GetXaxis()->SetTitle("p_{T} [GeV]"); Phase1Pix_GEN_Mu1_pT->GetYaxis()->SetTitle("Events/GeV"); Phase1Pix_GEN_Mu1_pT->Draw("SAME");
  Phase1Pix_GEN_Mu2_pT->SetLineColor(3); Phase1Pix_GEN_Mu2_pT->GetXaxis()->SetTitle("p_{T} [GeV]"); Phase1Pix_GEN_Mu2_pT->GetYaxis()->SetTitle("Events/GeV"); Phase1Pix_GEN_Mu2_pT->Draw("SAME");
  Phase1Pix_GEN_Mu3_pT->SetLineColor(4); Phase1Pix_GEN_Mu3_pT->GetXaxis()->SetTitle("p_{T} [GeV]"); Phase1Pix_GEN_Mu3_pT->GetYaxis()->SetTitle("Events/GeV"); Phase1Pix_GEN_Mu3_pT->Draw("SAME");
  GENMuPt->Write();

  GENMuEta->cd();
  Phase1Pix_GEN_Mu0_eta->SetLineColor(1); Phase1Pix_GEN_Mu0_eta->GetXaxis()->SetTitle("#eta"); Phase1Pix_GEN_Mu0_eta->GetYaxis()->SetTitle("Events/0.1"); Phase1Pix_GEN_Mu0_eta->Draw();
  Phase1Pix_GEN_Mu1_eta->SetLineColor(2); Phase1Pix_GEN_Mu1_eta->GetXaxis()->SetTitle("#eta"); Phase1Pix_GEN_Mu1_eta->GetYaxis()->SetTitle("Events/0.1"); Phase1Pix_GEN_Mu1_eta->Draw("SAME");
  Phase1Pix_GEN_Mu2_eta->SetLineColor(3); Phase1Pix_GEN_Mu2_eta->GetXaxis()->SetTitle("#eta"); Phase1Pix_GEN_Mu2_eta->GetYaxis()->SetTitle("Events/0.1"); Phase1Pix_GEN_Mu2_eta->Draw("SAME");
  Phase1Pix_GEN_Mu3_eta->SetLineColor(4); Phase1Pix_GEN_Mu3_eta->GetXaxis()->SetTitle("#eta"); Phase1Pix_GEN_Mu3_eta->GetYaxis()->SetTitle("Events/0.1"); Phase1Pix_GEN_Mu3_eta->Draw("SAME");
  GENMuEta->Write();

  GENMuPhi->cd();
  Phase1Pix_GEN_Mu0_phi->SetLineColor(1); Phase1Pix_GEN_Mu0_phi->GetXaxis()->SetTitle("#phi"); Phase1Pix_GEN_Mu0_phi->GetYaxis()->SetTitle("Events/0.1"); Phase1Pix_GEN_Mu0_phi->Draw();
  Phase1Pix_GEN_Mu1_phi->SetLineColor(2); Phase1Pix_GEN_Mu1_phi->GetXaxis()->SetTitle("#phi"); Phase1Pix_GEN_Mu1_phi->GetYaxis()->SetTitle("Events/0.1"); Phase1Pix_GEN_Mu1_phi->Draw("SAME");
  Phase1Pix_GEN_Mu2_phi->SetLineColor(3); Phase1Pix_GEN_Mu2_phi->GetXaxis()->SetTitle("#phi"); Phase1Pix_GEN_Mu2_phi->GetYaxis()->SetTitle("Events/0.1"); Phase1Pix_GEN_Mu2_phi->Draw("SAME");
  Phase1Pix_GEN_Mu3_phi->SetLineColor(4); Phase1Pix_GEN_Mu3_phi->GetXaxis()->SetTitle("#phi"); Phase1Pix_GEN_Mu3_phi->GetYaxis()->SetTitle("Events/0.1"); Phase1Pix_GEN_Mu3_phi->Draw("SAME");
  GENMuPhi->Write();

  GENAMuPt->cd();
  Phase1Pix_GEN_A0_Mu0_pT->SetLineColor(2); Phase1Pix_GEN_A0_Mu0_pT->SetLineStyle(1); Phase1Pix_GEN_A0_Mu0_pT->GetXaxis()->SetTitle("p_{T} [GeV]"); Phase1Pix_GEN_A0_Mu0_pT->GetYaxis()->SetTitle("Events/GeV"); Phase1Pix_GEN_A0_Mu0_pT->Draw();
  Phase1Pix_GEN_A0_Mu1_pT->SetLineColor(2); Phase1Pix_GEN_A0_Mu1_pT->SetLineStyle(2); Phase1Pix_GEN_A0_Mu1_pT->GetXaxis()->SetTitle("p_{T} [GeV]"); Phase1Pix_GEN_A0_Mu1_pT->GetYaxis()->SetTitle("Events/GeV"); Phase1Pix_GEN_A0_Mu1_pT->Draw("SAME");
  Phase1Pix_GEN_A1_Mu0_pT->SetLineColor(4); Phase1Pix_GEN_A1_Mu0_pT->SetLineStyle(1); Phase1Pix_GEN_A1_Mu0_pT->GetXaxis()->SetTitle("p_{T} [GeV]"); Phase1Pix_GEN_A1_Mu0_pT->GetYaxis()->SetTitle("Events/GeV"); Phase1Pix_GEN_A1_Mu0_pT->Draw("SAME");
  Phase1Pix_GEN_A1_Mu1_pT->SetLineColor(4); Phase1Pix_GEN_A1_Mu1_pT->SetLineStyle(2); Phase1Pix_GEN_A1_Mu1_pT->GetXaxis()->SetTitle("p_{T} [GeV]"); Phase1Pix_GEN_A1_Mu1_pT->GetYaxis()->SetTitle("Events/GeV"); Phase1Pix_GEN_A1_Mu1_pT->Draw("SAME");
  GENAMuPt->Write();

  RECOMuPt->cd();
  Phase1Pix_RECO_Mu0_pT->SetLineColor(1); Phase1Pix_RECO_Mu0_pT->GetXaxis()->SetTitle("p_{T} [GeV]"); Phase1Pix_RECO_Mu0_pT->GetYaxis()->SetTitle("Events/GeV"); Phase1Pix_RECO_Mu0_pT->Draw();
  Phase1Pix_RECO_Mu1_pT->SetLineColor(2); Phase1Pix_RECO_Mu1_pT->GetXaxis()->SetTitle("p_{T} [GeV]"); Phase1Pix_RECO_Mu1_pT->GetYaxis()->SetTitle("Events/GeV"); Phase1Pix_RECO_Mu1_pT->Draw("SAME");
  Phase1Pix_RECO_Mu2_pT->SetLineColor(3); Phase1Pix_RECO_Mu2_pT->GetXaxis()->SetTitle("p_{T} [GeV]"); Phase1Pix_RECO_Mu2_pT->GetYaxis()->SetTitle("Events/GeV"); Phase1Pix_RECO_Mu2_pT->Draw("SAME");
  Phase1Pix_RECO_Mu3_pT->SetLineColor(4); Phase1Pix_RECO_Mu3_pT->GetXaxis()->SetTitle("p_{T} [GeV]"); Phase1Pix_RECO_Mu3_pT->GetYaxis()->SetTitle("Events/GeV"); Phase1Pix_RECO_Mu3_pT->Draw("SAME");
  RECOMuPt->Write();

  RECOMuEta->cd();
  Phase1Pix_RECO_Mu0_eta->SetLineColor(1); Phase1Pix_RECO_Mu0_eta->GetXaxis()->SetTitle("#eta"); Phase1Pix_RECO_Mu0_eta->GetYaxis()->SetTitle("Events/0.1"); Phase1Pix_RECO_Mu0_eta->Draw();
  Phase1Pix_RECO_Mu1_eta->SetLineColor(2); Phase1Pix_RECO_Mu1_eta->GetXaxis()->SetTitle("#eta"); Phase1Pix_RECO_Mu1_eta->GetYaxis()->SetTitle("Events/0.1"); Phase1Pix_RECO_Mu1_eta->Draw("SAME");
  Phase1Pix_RECO_Mu2_eta->SetLineColor(3); Phase1Pix_RECO_Mu2_eta->GetXaxis()->SetTitle("#eta"); Phase1Pix_RECO_Mu2_eta->GetYaxis()->SetTitle("Events/0.1"); Phase1Pix_RECO_Mu2_eta->Draw("SAME");
  Phase1Pix_RECO_Mu3_eta->SetLineColor(4); Phase1Pix_RECO_Mu3_eta->GetXaxis()->SetTitle("#eta"); Phase1Pix_RECO_Mu3_eta->GetYaxis()->SetTitle("Events/0.1"); Phase1Pix_RECO_Mu3_eta->Draw("SAME");
  RECOMuEta->Write();

  RECOMuPhi->cd();
  Phase1Pix_RECO_Mu0_phi->SetLineColor(1); Phase1Pix_RECO_Mu0_phi->GetXaxis()->SetTitle("#phi"); Phase1Pix_RECO_Mu0_phi->GetYaxis()->SetTitle("Events/0.1"); Phase1Pix_RECO_Mu0_phi->Draw();
  Phase1Pix_RECO_Mu1_phi->SetLineColor(2); Phase1Pix_RECO_Mu1_phi->GetXaxis()->SetTitle("#phi"); Phase1Pix_RECO_Mu1_phi->GetYaxis()->SetTitle("Events/0.1"); Phase1Pix_RECO_Mu1_phi->Draw("SAME");
  Phase1Pix_RECO_Mu2_phi->SetLineColor(3); Phase1Pix_RECO_Mu2_phi->GetXaxis()->SetTitle("#phi"); Phase1Pix_RECO_Mu2_phi->GetYaxis()->SetTitle("Events/0.1"); Phase1Pix_RECO_Mu2_phi->Draw("SAME");
  Phase1Pix_RECO_Mu3_phi->SetLineColor(4); Phase1Pix_RECO_Mu3_phi->GetXaxis()->SetTitle("#phi"); Phase1Pix_RECO_Mu3_phi->GetYaxis()->SetTitle("Events/0.1"); Phase1Pix_RECO_Mu3_phi->Draw("SAME");
  RECOMuPhi->Write();

  RECODimuMuPt->cd();
  Phase1Pix_RECO_DimuC_Mu0_pT->SetLineColor(2); Phase1Pix_RECO_DimuC_Mu0_pT->SetLineStyle(1); Phase1Pix_RECO_DimuC_Mu0_pT->GetXaxis()->SetTitle("p_{T} [GeV]"); Phase1Pix_RECO_DimuC_Mu0_pT->GetYaxis()->SetTitle("Events/GeV"); Phase1Pix_RECO_DimuC_Mu0_pT->Draw();
  Phase1Pix_RECO_DimuC_Mu1_pT->SetLineColor(2); Phase1Pix_RECO_DimuC_Mu1_pT->SetLineStyle(2); Phase1Pix_RECO_DimuC_Mu1_pT->GetXaxis()->SetTitle("p_{T} [GeV]"); Phase1Pix_RECO_DimuC_Mu1_pT->GetYaxis()->SetTitle("Events/GeV"); Phase1Pix_RECO_DimuC_Mu1_pT->Draw("SAME");
  Phase1Pix_RECO_DimuF_Mu0_pT->SetLineColor(4); Phase1Pix_RECO_DimuF_Mu0_pT->SetLineStyle(1); Phase1Pix_RECO_DimuF_Mu0_pT->GetXaxis()->SetTitle("p_{T} [GeV]"); Phase1Pix_RECO_DimuF_Mu0_pT->GetYaxis()->SetTitle("Events/GeV"); Phase1Pix_RECO_DimuF_Mu0_pT->Draw("SAME");
  Phase1Pix_RECO_DimuF_Mu1_pT->SetLineColor(4); Phase1Pix_RECO_DimuF_Mu1_pT->SetLineStyle(2); Phase1Pix_RECO_DimuF_Mu1_pT->GetXaxis()->SetTitle("p_{T} [GeV]"); Phase1Pix_RECO_DimuF_Mu1_pT->GetYaxis()->SetTitle("Events/GeV"); Phase1Pix_RECO_DimuF_Mu1_pT->Draw("SAME");
  RECODimuMuPt->Write();

  //some basic selections eff check
  if ( TEfficiency::CheckConsistency(*GEN1stPt_pass_1stRECOmu, *GEN1stPt_pass_GEN) ) {
    TEfficiency* eff_GEN1stPt_pass_1stRECOmu = new TEfficiency(*GEN1stPt_pass_1stRECOmu, *GEN1stPt_pass_GEN);
    eff_GEN1stPt_pass_1stRECOmu->SetTitle("Efficiency: 1st RECO mu pT > 8 GeV;p_{T, 1st GEN #mu} [GeV];#epsilon");
    eff_GEN1stPt_pass_1stRECOmu->Write();
  }
  if ( TEfficiency::CheckConsistency(*GEN2ndPt_pass_2ndRECOmu, *GEN2ndPt_pass_GEN) ) {
    TEfficiency* eff_GEN2ndPt_pass_2ndRECOmu = new TEfficiency(*GEN2ndPt_pass_2ndRECOmu, *GEN2ndPt_pass_GEN);
    eff_GEN2ndPt_pass_2ndRECOmu->SetTitle("Efficiency: 2nd RECO mu pT > 8 GeV;p_{T, 2nd GEN #mu} [GeV];#epsilon");
    eff_GEN2ndPt_pass_2ndRECOmu->Write();
  }
  if ( TEfficiency::CheckConsistency(*GEN3rdPt_pass_3rdRECOmu, *GEN3rdPt_pass_GEN) ) {
    TEfficiency* eff_GEN3rdPt_pass_3rdRECOmu = new TEfficiency(*GEN3rdPt_pass_3rdRECOmu, *GEN3rdPt_pass_GEN);
    eff_GEN3rdPt_pass_3rdRECOmu->SetTitle("Efficiency: 3rd RECO mu pT > 8 GeV;p_{T, 3rd GEN #mu} [GeV];#epsilon");
    eff_GEN3rdPt_pass_3rdRECOmu->Write();
  }
  if ( TEfficiency::CheckConsistency(*GEN4thPt_pass_4thRECOmu, *GEN4thPt_pass_GEN) ) {
    TEfficiency* eff_GEN4thPt_pass_4thRECOmu = new TEfficiency(*GEN4thPt_pass_4thRECOmu, *GEN4thPt_pass_GEN);
    eff_GEN4thPt_pass_4thRECOmu->SetTitle("Efficiency: 4th RECO mu pT > 8 GeV;p_{T, 4th GEN #mu} [GeV];#epsilon");
    eff_GEN4thPt_pass_4thRECOmu->Write();
  }

  if ( TEfficiency::CheckConsistency(*GEN1stPt_pass_RECOmu12, *GEN1stPt_pass_GEN) ) {
    TEfficiency* eff_GEN1stPt_pass_RECOmu12 = new TEfficiency(*GEN1stPt_pass_RECOmu12, *GEN1stPt_pass_GEN);
    eff_GEN1stPt_pass_RECOmu12->SetTitle("Efficiency: 1 & 2 RECO mu pT > 8 GeV;p_{T, 1st GEN #mu} [GeV];#epsilon");
    eff_GEN1stPt_pass_RECOmu12->Write();
  }
  if ( TEfficiency::CheckConsistency(*GEN1stPt_pass_RECOmu123, *GEN1stPt_pass_GEN) ) {
    TEfficiency* eff_GEN1stPt_pass_RECOmu123 = new TEfficiency(*GEN1stPt_pass_RECOmu123, *GEN1stPt_pass_GEN);
    eff_GEN1stPt_pass_RECOmu123->SetTitle("Efficiency: 1 & 2 & 3 RECO mu pT > 8 GeV;p_{T, 1st GEN #mu} [GeV];#epsilon");
    eff_GEN1stPt_pass_RECOmu123->Write();
  }
  if ( TEfficiency::CheckConsistency(*GEN1stPt_pass_RECOmu1234, *GEN1stPt_pass_GEN) ) {
    TEfficiency* eff_GEN1stPt_pass_RECOmu1234 = new TEfficiency(*GEN1stPt_pass_RECOmu1234, *GEN1stPt_pass_GEN);
    eff_GEN1stPt_pass_RECOmu1234->SetTitle("Efficiency: 1 & 2 & 3 & 4 RECO mu pT > 8 GeV;p_{T, 1st GEN #mu} [GeV];#epsilon");
    eff_GEN1stPt_pass_RECOmu1234->Write();
  }


  if ( TEfficiency::CheckConsistency(*GENLeadingLxy_pass_RECOmu1234, *GENLeadingLxy_pass_GEN) ) {
    TEfficiency* eff_GENLeadingLxy_pass_RECOmu1234 = new TEfficiency(*GENLeadingLxy_pass_RECOmu1234, *GENLeadingLxy_pass_GEN);
    eff_GENLeadingLxy_pass_RECOmu1234->SetTitle("Efficiency: 1 & 2 & 3 & 4 RECO mu pT > 8 GeV;GEN A leading L_{xy} [cm];#epsilon");
    eff_GENLeadingLxy_pass_RECOmu1234->Write();
  }

  if ( TEfficiency::CheckConsistency(*GENLeadingLz_pass_RECOmu1234, *GENLeadingLz_pass_GEN) ) {
    TEfficiency* eff_GENLeadingLz_pass_RECOmu1234 = new TEfficiency(*GENLeadingLz_pass_RECOmu1234, *GENLeadingLz_pass_GEN);
    eff_GENLeadingLz_pass_RECOmu1234->SetTitle("Efficiency: 1 & 2 & 3 & 4 RECO mu pT > 8 GeV;GEN A leading L_{z} [cm];#epsilon");
    eff_GENLeadingLz_pass_RECOmu1234->Write();
  }

  if ( PerEventTriggerEff ) {
    //Per-event Efficiency for signal "HLT" and "L1 seeds" after "BASIC" offline pT selections
    if ( TEfficiency::CheckConsistency(*HLT_leading_pt_pass_basic, *leading_pt_pass_basic) ) {
      TEfficiency* eff_HLT_leading_pt_pass_basic  = new TEfficiency(*HLT_leading_pt_pass_basic, *leading_pt_pass_basic);
      eff_HLT_leading_pt_pass_basic->SetTitle("Signal HLT Efficiency After Cut #9;p_{T, leading #mu} [GeV];#epsilon");
      eff_HLT_leading_pt_pass_basic->Write(); }
    if ( TEfficiency::CheckConsistency(*HLT_leading_eta_pass_basic, *leading_eta_pass_basic) ) {
      TEfficiency* eff_HLT_leading_eta_pass_basic = new TEfficiency(*HLT_leading_eta_pass_basic, *leading_eta_pass_basic);
      eff_HLT_leading_eta_pass_basic->SetTitle("Signal HLT Efficiency After Cut #9;#eta_{leading #mu};#epsilon");
      eff_HLT_leading_eta_pass_basic->Write(); }
    if ( TEfficiency::CheckConsistency(*HLT_leading_phi_pass_basic, *leading_phi_pass_basic) ) {
      TEfficiency* eff_HLT_leading_phi_pass_basic = new TEfficiency(*HLT_leading_phi_pass_basic, *leading_phi_pass_basic);
      eff_HLT_leading_phi_pass_basic->SetTitle("Signal HLT Efficiency After Cut #9;#phi_{leading #mu};#epsilon");
      eff_HLT_leading_phi_pass_basic->Write(); }
    if ( TEfficiency::CheckConsistency(*L1_leading_pt_pass_basic, *leading_pt_pass_basic) ) {
      TEfficiency* eff_L1_leading_pt_pass_basic  = new TEfficiency(*L1_leading_pt_pass_basic, *leading_pt_pass_basic);
      eff_L1_leading_pt_pass_basic->SetTitle("Signal L1 Efficiency After Cut #9;p_{T, leading #mu} [GeV];#epsilon");
      eff_L1_leading_pt_pass_basic->Write(); }
    if ( TEfficiency::CheckConsistency(*L1_leading_eta_pass_basic, *leading_eta_pass_basic) ) {
      TEfficiency* eff_L1_leading_eta_pass_basic = new TEfficiency(*L1_leading_eta_pass_basic, *leading_eta_pass_basic);
      eff_L1_leading_eta_pass_basic->SetTitle("Signal L1 Efficiency After Cut #9;#eta_{leading #mu};#epsilon");
      eff_L1_leading_eta_pass_basic->Write(); }
    if ( TEfficiency::CheckConsistency(*L1_leading_phi_pass_basic, *leading_phi_pass_basic) ) {
      TEfficiency* eff_L1_leading_phi_pass_basic = new TEfficiency(*L1_leading_phi_pass_basic, *leading_phi_pass_basic);
      eff_L1_leading_phi_pass_basic->SetTitle("Signal L1 Efficiency After Cut #9;#phi_{leading #mu};#epsilon");
      eff_L1_leading_phi_pass_basic->Write();
    }

    if ( TEfficiency::CheckConsistency(*HLT_second_pt_pass_basic, *second_pt_pass_basic) ) {
      TEfficiency* eff_HLT_second_pt_pass_basic  = new TEfficiency(*HLT_second_pt_pass_basic, *second_pt_pass_basic);
      eff_HLT_second_pt_pass_basic->SetTitle("Signal HLT Efficiency After Cut #9;p_{T, second #mu} [GeV];#epsilon");
      eff_HLT_second_pt_pass_basic->Write(); }
    if ( TEfficiency::CheckConsistency(*HLT_second_eta_pass_basic, *second_eta_pass_basic) ) {
      TEfficiency* eff_HLT_second_eta_pass_basic = new TEfficiency(*HLT_second_eta_pass_basic, *second_eta_pass_basic);
      eff_HLT_second_eta_pass_basic->SetTitle("Signal HLT Efficiency After Cut #9;#eta_{second #mu};#epsilon");
      eff_HLT_second_eta_pass_basic->Write(); }
    if ( TEfficiency::CheckConsistency(*HLT_second_phi_pass_basic, *second_phi_pass_basic) ) {
      TEfficiency* eff_HLT_second_phi_pass_basic = new TEfficiency(*HLT_second_phi_pass_basic, *second_phi_pass_basic);
      eff_HLT_second_phi_pass_basic->SetTitle("Signal HLT Efficiency After Cut #9;#phi_{second #mu};#epsilon");
      eff_HLT_second_phi_pass_basic->Write(); }
    if ( TEfficiency::CheckConsistency(*L1_second_pt_pass_basic, *second_pt_pass_basic) ) {
      TEfficiency* eff_L1_second_pt_pass_basic  = new TEfficiency(*L1_second_pt_pass_basic, *second_pt_pass_basic);
      eff_L1_second_pt_pass_basic->SetTitle("Signal L1 Efficiency After Cut #9;p_{T, second #mu} [GeV];#epsilon");
      eff_L1_second_pt_pass_basic->Write(); }
    if ( TEfficiency::CheckConsistency(*L1_second_eta_pass_basic, *second_eta_pass_basic) ) {
      TEfficiency* eff_L1_second_eta_pass_basic = new TEfficiency(*L1_second_eta_pass_basic, *second_eta_pass_basic);
      eff_L1_second_eta_pass_basic->SetTitle("Signal L1 Efficiency After Cut #9;#eta_{second #mu};#epsilon");
      eff_L1_second_eta_pass_basic->Write(); }
    if ( TEfficiency::CheckConsistency(*L1_second_phi_pass_basic, *second_phi_pass_basic) ) {
      TEfficiency* eff_L1_second_phi_pass_basic = new TEfficiency(*L1_second_phi_pass_basic, *second_phi_pass_basic);
      eff_L1_second_phi_pass_basic->SetTitle("Signal L1 Efficiency After Cut #9;#phi_{second #mu};#epsilon");
      eff_L1_second_phi_pass_basic->Write();
    }

    if ( TEfficiency::CheckConsistency(*HLT_third_pt_pass_basic, *third_pt_pass_basic) ) {
      TEfficiency* eff_HLT_third_pt_pass_basic  = new TEfficiency(*HLT_third_pt_pass_basic, *third_pt_pass_basic);
      eff_HLT_third_pt_pass_basic->SetTitle("Signal HLT Efficiency After Cut #9;p_{T, third #mu} [GeV];#epsilon");
      eff_HLT_third_pt_pass_basic->Write(); }
    if ( TEfficiency::CheckConsistency(*HLT_third_eta_pass_basic, *third_eta_pass_basic) ) {
      TEfficiency* eff_HLT_third_eta_pass_basic = new TEfficiency(*HLT_third_eta_pass_basic, *third_eta_pass_basic);
      eff_HLT_third_eta_pass_basic->SetTitle("Signal HLT Efficiency After Cut #9;#eta_{third #mu};#epsilon");
      eff_HLT_third_eta_pass_basic->Write(); }
    if ( TEfficiency::CheckConsistency(*HLT_third_phi_pass_basic, *third_phi_pass_basic) ) {
      TEfficiency* eff_HLT_third_phi_pass_basic = new TEfficiency(*HLT_third_phi_pass_basic, *third_phi_pass_basic);
      eff_HLT_third_phi_pass_basic->SetTitle("Signal HLT Efficiency After Cut #9;#phi_{third #mu};#epsilon");
      eff_HLT_third_phi_pass_basic->Write(); }
    if ( TEfficiency::CheckConsistency(*L1_third_pt_pass_basic, *third_pt_pass_basic) ) {
      TEfficiency* eff_L1_third_pt_pass_basic  = new TEfficiency(*L1_third_pt_pass_basic, *third_pt_pass_basic);
      eff_L1_third_pt_pass_basic->SetTitle("Signal L1 Efficiency After Cut #9;p_{T, third #mu} [GeV];#epsilon");
      eff_L1_third_pt_pass_basic->Write(); }
    if ( TEfficiency::CheckConsistency(*L1_third_eta_pass_basic, *third_eta_pass_basic) ) {
      TEfficiency* eff_L1_third_eta_pass_basic = new TEfficiency(*L1_third_eta_pass_basic, *third_eta_pass_basic);
      eff_L1_third_eta_pass_basic->SetTitle("Signal L1 Efficiency After Cut #9;#eta_{third #mu};#epsilon");
      eff_L1_third_eta_pass_basic->Write(); }
    if ( TEfficiency::CheckConsistency(*L1_third_phi_pass_basic, *third_phi_pass_basic) ) {
      TEfficiency* eff_L1_third_phi_pass_basic = new TEfficiency(*L1_third_phi_pass_basic, *third_phi_pass_basic);
      eff_L1_third_phi_pass_basic->SetTitle("Signal L1 Efficiency After Cut #9;#phi_{third #mu};#epsilon");
      eff_L1_third_phi_pass_basic->Write();
    }

    if ( TEfficiency::CheckConsistency(*HLT_fourth_pt_pass_basic, *fourth_pt_pass_basic) ) {
      TEfficiency* eff_HLT_fourth_pt_pass_basic  = new TEfficiency(*HLT_fourth_pt_pass_basic, *fourth_pt_pass_basic);
      eff_HLT_fourth_pt_pass_basic->SetTitle("Signal HLT Efficiency After Cut #9;p_{T, fourth #mu} [GeV];#epsilon"); eff_HLT_fourth_pt_pass_basic->Write();
    }
    if ( TEfficiency::CheckConsistency(*HLT_fourth_eta_pass_basic, *fourth_eta_pass_basic) ) {
      TEfficiency* eff_HLT_fourth_eta_pass_basic = new TEfficiency(*HLT_fourth_eta_pass_basic, *fourth_eta_pass_basic);
      eff_HLT_fourth_eta_pass_basic->SetTitle("Signal HLT Efficiency After Cut #9;#eta_{fourth #mu};#epsilon"); eff_HLT_fourth_eta_pass_basic->Write();
    }
    if ( TEfficiency::CheckConsistency(*HLT_fourth_phi_pass_basic, *fourth_phi_pass_basic) ) {
      TEfficiency* eff_HLT_fourth_phi_pass_basic = new TEfficiency(*HLT_fourth_phi_pass_basic, *fourth_phi_pass_basic);
      eff_HLT_fourth_phi_pass_basic->SetTitle("Signal HLT Efficiency After Cut #9;#phi_{fourth #mu};#epsilon"); eff_HLT_fourth_phi_pass_basic->Write();
    }
    if ( TEfficiency::CheckConsistency(*L1_fourth_pt_pass_basic, *fourth_pt_pass_basic) ) {
      TEfficiency* eff_L1_fourth_pt_pass_basic  = new TEfficiency(*L1_fourth_pt_pass_basic, *fourth_pt_pass_basic);
      eff_L1_fourth_pt_pass_basic->SetTitle("Signal L1 Efficiency After Cut #9;p_{T, fourth #mu} [GeV];#epsilon"); eff_L1_fourth_pt_pass_basic->Write();
    }
    if ( TEfficiency::CheckConsistency(*L1_fourth_eta_pass_basic, *fourth_eta_pass_basic) ) {
      TEfficiency* eff_L1_fourth_eta_pass_basic = new TEfficiency(*L1_fourth_eta_pass_basic, *fourth_eta_pass_basic);
      eff_L1_fourth_eta_pass_basic->SetTitle("Signal L1 Efficiency After Cut #9;#eta_{fourth #mu};#epsilon"); eff_L1_fourth_eta_pass_basic->Write();
    }
    if ( TEfficiency::CheckConsistency(*L1_fourth_phi_pass_basic, *fourth_phi_pass_basic) ) {
      TEfficiency* eff_L1_fourth_phi_pass_basic = new TEfficiency(*L1_fourth_phi_pass_basic, *fourth_phi_pass_basic);
      eff_L1_fourth_phi_pass_basic->SetTitle("Signal L1 Efficiency After Cut #9;#phi_{fourth #mu};#epsilon"); eff_L1_fourth_phi_pass_basic->Write();
    }

    //Per-event Efficiency for signal "HLT" and "L1 seeds" after cut #15
    if ( TEfficiency::CheckConsistency(*HLT_leading_pt_pass_all, *leading_pt_pass_all) ) {
      TEfficiency* eff_HLT_leading_pt_pass_all  = new TEfficiency(*HLT_leading_pt_pass_all, *leading_pt_pass_all);
      eff_HLT_leading_pt_pass_all->SetTitle("Signal HLT Efficiency After Cut #15;p_{T, leading #mu} [GeV];#epsilon");
      eff_HLT_leading_pt_pass_all->Write(); }
    if ( TEfficiency::CheckConsistency(*HLT_leading_eta_pass_all, *leading_eta_pass_all) ) {
      TEfficiency* eff_HLT_leading_eta_pass_all = new TEfficiency(*HLT_leading_eta_pass_all, *leading_eta_pass_all);
      eff_HLT_leading_eta_pass_all->SetTitle("Signal HLT Efficiency After Cut #15;#eta_{leading #mu};#epsilon");
      eff_HLT_leading_eta_pass_all->Write(); }
    if ( TEfficiency::CheckConsistency(*HLT_leading_phi_pass_all, *leading_phi_pass_all) ) {
      TEfficiency* eff_HLT_leading_phi_pass_all = new TEfficiency(*HLT_leading_phi_pass_all, *leading_phi_pass_all);
      eff_HLT_leading_phi_pass_all->SetTitle("Signal HLT Efficiency After Cut #15;#phi_{leading #mu};#epsilon");
      eff_HLT_leading_phi_pass_all->Write(); }
    if ( TEfficiency::CheckConsistency(*L1_leading_pt_pass_all, *leading_pt_pass_all) ) {
      TEfficiency* eff_L1_leading_pt_pass_all  = new TEfficiency(*L1_leading_pt_pass_all, *leading_pt_pass_all);
      eff_L1_leading_pt_pass_all->SetTitle("Signal L1 Efficiency After Cut #15;p_{T, leading #mu} [GeV];#epsilon");
      eff_L1_leading_pt_pass_all->Write(); }
    if ( TEfficiency::CheckConsistency(*L1_leading_eta_pass_all, *leading_eta_pass_all) ) {
      TEfficiency* eff_L1_leading_eta_pass_all = new TEfficiency(*L1_leading_eta_pass_all, *leading_eta_pass_all);
      eff_L1_leading_eta_pass_all->SetTitle("Signal L1 Efficiency After Cut #15;#eta_{leading #mu};#epsilon");
      eff_L1_leading_eta_pass_all->Write(); }
    if ( TEfficiency::CheckConsistency(*L1_leading_phi_pass_all, *leading_phi_pass_all) ) {
      TEfficiency* eff_L1_leading_phi_pass_all = new TEfficiency(*L1_leading_phi_pass_all, *leading_phi_pass_all);
      eff_L1_leading_phi_pass_all->SetTitle("Signal L1 Efficiency After Cut #15;#phi_{leading #mu};#epsilon");
      eff_L1_leading_phi_pass_all->Write();
    }

    if ( TEfficiency::CheckConsistency(*HLT_second_pt_pass_all, *second_pt_pass_all) ) {
      TEfficiency* eff_HLT_second_pt_pass_all  = new TEfficiency(*HLT_second_pt_pass_all, *second_pt_pass_all);
      eff_HLT_second_pt_pass_all->SetTitle("Signal HLT Efficiency After Cut #15;p_{T, second #mu} [GeV];#epsilon");
      eff_HLT_second_pt_pass_all->Write(); }
    if ( TEfficiency::CheckConsistency(*HLT_second_eta_pass_all, *second_eta_pass_all) ) {
      TEfficiency* eff_HLT_second_eta_pass_all = new TEfficiency(*HLT_second_eta_pass_all, *second_eta_pass_all);
      eff_HLT_second_eta_pass_all->SetTitle("Signal HLT Efficiency After Cut #15;#eta_{second #mu};#epsilon");
      eff_HLT_second_eta_pass_all->Write(); }
    if ( TEfficiency::CheckConsistency(*HLT_second_phi_pass_all, *second_phi_pass_all) ) {
      TEfficiency* eff_HLT_second_phi_pass_all = new TEfficiency(*HLT_second_phi_pass_all, *second_phi_pass_all);
      eff_HLT_second_phi_pass_all->SetTitle("Signal HLT Efficiency After Cut #15;#phi_{second #mu};#epsilon");
      eff_HLT_second_phi_pass_all->Write(); }
    if ( TEfficiency::CheckConsistency(*L1_second_pt_pass_all, *second_pt_pass_all) ) {
      TEfficiency* eff_L1_second_pt_pass_all  = new TEfficiency(*L1_second_pt_pass_all, *second_pt_pass_all);
      eff_L1_second_pt_pass_all->SetTitle("Signal L1 Efficiency After Cut #15;p_{T, second #mu} [GeV];#epsilon");
      eff_L1_second_pt_pass_all->Write(); }
    if ( TEfficiency::CheckConsistency(*L1_second_eta_pass_all, *second_eta_pass_all) ) {
      TEfficiency* eff_L1_second_eta_pass_all = new TEfficiency(*L1_second_eta_pass_all, *second_eta_pass_all);
      eff_L1_second_eta_pass_all->SetTitle("Signal L1 Efficiency After Cut #15;#eta_{second #mu};#epsilon");
      eff_L1_second_eta_pass_all->Write(); }
    if ( TEfficiency::CheckConsistency(*L1_second_phi_pass_all, *second_phi_pass_all) ) {
      TEfficiency* eff_L1_second_phi_pass_all = new TEfficiency(*L1_second_phi_pass_all, *second_phi_pass_all);
      eff_L1_second_phi_pass_all->SetTitle("Signal L1 Efficiency After Cut #15;#phi_{second #mu};#epsilon");
      eff_L1_second_phi_pass_all->Write();
    }

    if ( TEfficiency::CheckConsistency(*HLT_third_pt_pass_all, *third_pt_pass_all) ) {
      TEfficiency* eff_HLT_third_pt_pass_all  = new TEfficiency(*HLT_third_pt_pass_all, *third_pt_pass_all);
      eff_HLT_third_pt_pass_all->SetTitle("Signal HLT Efficiency After Cut #15;p_{T, third #mu} [GeV];#epsilon");
      eff_HLT_third_pt_pass_all->Write(); }
    if ( TEfficiency::CheckConsistency(*HLT_third_eta_pass_all, *third_eta_pass_all) ) {
      TEfficiency* eff_HLT_third_eta_pass_all = new TEfficiency(*HLT_third_eta_pass_all, *third_eta_pass_all);
      eff_HLT_third_eta_pass_all->SetTitle("Signal HLT Efficiency After Cut #15;#eta_{third #mu};#epsilon");
      eff_HLT_third_eta_pass_all->Write(); }
    if ( TEfficiency::CheckConsistency(*HLT_third_phi_pass_all, *third_phi_pass_all) ) {
      TEfficiency* eff_HLT_third_phi_pass_all = new TEfficiency(*HLT_third_phi_pass_all, *third_phi_pass_all);
      eff_HLT_third_phi_pass_all->SetTitle("Signal HLT Efficiency After Cut #15;#phi_{third #mu};#epsilon");
      eff_HLT_third_phi_pass_all->Write(); }
    if ( TEfficiency::CheckConsistency(*L1_third_pt_pass_all, *third_pt_pass_all) ) {
      TEfficiency* eff_L1_third_pt_pass_all  = new TEfficiency(*L1_third_pt_pass_all, *third_pt_pass_all);
      eff_L1_third_pt_pass_all->SetTitle("Signal L1 Efficiency After Cut #15;p_{T, third #mu} [GeV];#epsilon");
      eff_L1_third_pt_pass_all->Write(); }
    if ( TEfficiency::CheckConsistency(*L1_third_eta_pass_all, *third_eta_pass_all) ) {
      TEfficiency* eff_L1_third_eta_pass_all = new TEfficiency(*L1_third_eta_pass_all, *third_eta_pass_all);
      eff_L1_third_eta_pass_all->SetTitle("Signal L1 Efficiency After Cut #15;#eta_{third #mu};#epsilon");
      eff_L1_third_eta_pass_all->Write(); }
    if ( TEfficiency::CheckConsistency(*L1_third_phi_pass_all, *third_phi_pass_all) ) {
      TEfficiency* eff_L1_third_phi_pass_all = new TEfficiency(*L1_third_phi_pass_all, *third_phi_pass_all);
      eff_L1_third_phi_pass_all->SetTitle("Signal L1 Efficiency After Cut #15;#phi_{third #mu};#epsilon");
      eff_L1_third_phi_pass_all->Write();
    }

    if ( TEfficiency::CheckConsistency(*HLT_fourth_pt_pass_all, *fourth_pt_pass_all) ) {
      TEfficiency* eff_HLT_fourth_pt_pass_all  = new TEfficiency(*HLT_fourth_pt_pass_all, *fourth_pt_pass_all);
      eff_HLT_fourth_pt_pass_all->SetTitle("Signal HLT Efficiency After Cut #15;p_{T, fourth #mu} [GeV];#epsilon");
      eff_HLT_fourth_pt_pass_all->Write(); }
    if ( TEfficiency::CheckConsistency(*HLT_fourth_eta_pass_all, *fourth_eta_pass_all) ) {
      TEfficiency* eff_HLT_fourth_eta_pass_all = new TEfficiency(*HLT_fourth_eta_pass_all, *fourth_eta_pass_all);
      eff_HLT_fourth_eta_pass_all->SetTitle("Signal HLT Efficiency After Cut #15;#eta_{fourth #mu};#epsilon");
      eff_HLT_fourth_eta_pass_all->Write(); }
    if ( TEfficiency::CheckConsistency(*HLT_fourth_phi_pass_all, *fourth_phi_pass_all) ) {
      TEfficiency* eff_HLT_fourth_phi_pass_all = new TEfficiency(*HLT_fourth_phi_pass_all, *fourth_phi_pass_all);
      eff_HLT_fourth_phi_pass_all->SetTitle("Signal HLT Efficiency After Cut #15;#phi_{fourth #mu};#epsilon");
      eff_HLT_fourth_phi_pass_all->Write(); }
    if ( TEfficiency::CheckConsistency(*L1_fourth_pt_pass_all, *fourth_pt_pass_all) ) {
      TEfficiency* eff_L1_fourth_pt_pass_all  = new TEfficiency(*L1_fourth_pt_pass_all, *fourth_pt_pass_all);
      eff_L1_fourth_pt_pass_all->SetTitle("Signal L1 Efficiency After Cut #15;p_{T, fourth #mu} [GeV];#epsilon");
      eff_L1_fourth_pt_pass_all->Write(); }
    if ( TEfficiency::CheckConsistency(*L1_fourth_eta_pass_all, *fourth_eta_pass_all) ) {
      TEfficiency* eff_L1_fourth_eta_pass_all = new TEfficiency(*L1_fourth_eta_pass_all, *fourth_eta_pass_all);
      eff_L1_fourth_eta_pass_all->SetTitle("Signal L1 Efficiency After Cut #15;#eta_{fourth #mu};#epsilon");
      eff_L1_fourth_eta_pass_all->Write(); }
    if ( TEfficiency::CheckConsistency(*L1_fourth_phi_pass_all, *fourth_phi_pass_all) ) {
      TEfficiency* eff_L1_fourth_phi_pass_all = new TEfficiency(*L1_fourth_phi_pass_all, *fourth_phi_pass_all);
      eff_L1_fourth_phi_pass_all->SetTitle("Signal L1 Efficiency After Cut #15;#phi_{fourth #mu};#epsilon");
      eff_L1_fourth_phi_pass_all->Write();
    }

    if ( TEfficiency::CheckConsistency(*HLT_genA_leading_Lxy_pass_all, *genA_leading_Lxy_pass_all) ) {
      TEfficiency* eff_HLT_genA_leading_Lxy_pass_all = new TEfficiency(*HLT_genA_leading_Lxy_pass_all, *genA_leading_Lxy_pass_all);
      eff_HLT_genA_leading_Lxy_pass_all->SetTitle("Signal HLT Efficiency After Cut #15;Leading L_{xy, GEN A} [cm];#epsilon");
      eff_HLT_genA_leading_Lxy_pass_all->Write();
    }
    if ( TEfficiency::CheckConsistency(*HLT_genA_leading_Lz_pass_all, *genA_leading_Lz_pass_all) ) {
      TEfficiency* eff_HLT_genA_leading_Lz_pass_all = new TEfficiency(*HLT_genA_leading_Lz_pass_all, *genA_leading_Lz_pass_all);
      eff_HLT_genA_leading_Lz_pass_all->SetTitle("Signal HLT Efficiency After Cut #15;Leading L_{z, GEN A} [cm];#epsilon");
      eff_HLT_genA_leading_Lz_pass_all->Write();
    }
    if ( TEfficiency::CheckConsistency(*HLT_diMuon_leading_Lxy_pass_all, *diMuon_leading_Lxy_pass_all) ) {
      TEfficiency* eff_HLT_diMuon_leading_Lxy_pass_all = new TEfficiency(*HLT_diMuon_leading_Lxy_pass_all, *diMuon_leading_Lxy_pass_all);
      eff_HLT_diMuon_leading_Lxy_pass_all->SetTitle("Signal HLT Efficiency After Cut #15;Leading L_{xy, RECO di-#mu} [cm];#epsilon");
      eff_HLT_diMuon_leading_Lxy_pass_all->Write();
    }
    if ( TEfficiency::CheckConsistency(*HLT_diMuon_leading_Lz_pass_all, *diMuon_leading_Lz_pass_all) ) {
      TEfficiency* eff_HLT_diMuon_leading_Lz_pass_all = new TEfficiency(*HLT_diMuon_leading_Lz_pass_all, *diMuon_leading_Lz_pass_all);
      eff_HLT_diMuon_leading_Lz_pass_all->SetTitle("Signal HLT Efficiency After Cut #15;Leading L_{z, RECO di-#mu} [cm];#epsilon");
      eff_HLT_diMuon_leading_Lz_pass_all->Write();
    }

  }//end if (PerEventTriggerEff)

  if ( ModelBKGShape ) {
    RECO4muMass->GetXaxis()->SetTitle("m_{4#mu} [GeV]"); RECO4muMass->GetYaxis()->SetTitle("Events/GeV"); RECO4muMass->Write();
    RECOrePaired2muLeadingMass->GetXaxis()->SetTitle("Leading mass of re-paired OS di-#mu [GeV]"); RECOrePaired2muLeadingMass->GetYaxis()->SetTitle("Events/GeV"); RECOrePaired2muLeadingMass->Write();
    RECOrePaired2muTrailingMass->GetXaxis()->SetTitle("Trailing mass of re-paired OS di-#mu [GeV]"); RECOrePaired2muTrailingMass->GetYaxis()->SetTitle("Events/GeV"); RECOrePaired2muTrailingMass->Write();
    RECOrePaired2muLeadingdR->GetXaxis()->SetTitle("Leading dR of re-paired OS di-#mu"); RECOrePaired2muLeadingdR->GetYaxis()->SetTitle("Events/0.01"); RECOrePaired2muLeadingdR->Write();
    RECOrePaired2muTrailingdR->GetXaxis()->SetTitle("Trailing dR of re-paired OS di-#mu"); RECOrePaired2muTrailingdR->GetYaxis()->SetTitle("Events/0.01"); RECOrePaired2muTrailingdR->Write();

    BKGShapeCR->Write(); BKGShapeCRmassC->Write(); BKGShapeCRmassF->Write();
    NJetCR->Write(); NTightBCR->Write(); NMediumBCR->Write(); NLooseBCR->Write();
    SAmuTrkIsoWP1CR->Write(); SAmuTrkIsoWP2CR->Write(); SAmuTrkIsoWP3CR->Write(); SAmuNTrkWP1CR->Write(); SAmuNTrkWP2CR->Write(); SAmuNTrkWP3CR->Write();
    SAmuNTrkNoDzWP1CR->Write(); SAmuNTrkNoDzWP2CR->Write(); SAmuNTrkNoDzWP3CR->Write(); SAmuTrkIsoNoDzWP1CR->Write(); SAmuTrkIsoNoDzWP2CR->Write(); SAmuTrkIsoNoDzWP3CR->Write();
    SAmuPtCR->Write(); SAmuEtaCR->Write(); SAmuPhiCR->Write();

    BKGShapeSR->Write(); BKGShapeSRmassC->Write(); BKGShapeSRmassF->Write();
    NJetSR->Write(); NTightBSR->Write(); NMediumBSR->Write(); NLooseBSR->Write();
    SAmuTrkIsoWP1SR->Write(); SAmuTrkIsoWP2SR->Write(); SAmuTrkIsoWP3SR->Write(); SAmuNTrkWP1SR->Write(); SAmuNTrkWP2SR->Write(); SAmuNTrkWP3SR->Write();
    SAmuNTrkNoDzWP1SR->Write(); SAmuNTrkNoDzWP2SR->Write(); SAmuNTrkNoDzWP3SR->Write(); SAmuTrkIsoNoDzWP1SR->Write(); SAmuTrkIsoNoDzWP2SR->Write(); SAmuTrkIsoNoDzWP3SR->Write();
    SAmuPtSR->Write(); SAmuEtaSR->Write(); SAmuPhiSR->Write();

    L_DimuC_SR_HighMass->GetXaxis()->SetTitle("L [cm]");     L_DimuC_SR_HighMass->GetYaxis()->SetTitle("Events/0.1 cm");   L_DimuC_SR_HighMass->Write();
    L_DimuF_SR_HighMass->GetXaxis()->SetTitle("L [cm]");     L_DimuF_SR_HighMass->GetYaxis()->SetTitle("Events/0.1 cm");   L_DimuF_SR_HighMass->Write();
    Lxy_DimuC_SR_HighMass->GetXaxis()->SetTitle("Lxy [cm]"); Lxy_DimuC_SR_HighMass->GetYaxis()->SetTitle("Events/0.1 cm"); Lxy_DimuC_SR_HighMass->Write();
    Lxy_DimuF_SR_HighMass->GetXaxis()->SetTitle("Lxy [cm]"); Lxy_DimuF_SR_HighMass->GetYaxis()->SetTitle("Events/0.1 cm"); Lxy_DimuF_SR_HighMass->Write();
    Lz_DimuC_SR_HighMass->GetXaxis()->SetTitle("Lz [cm]");   Lz_DimuC_SR_HighMass->GetYaxis()->SetTitle("Events/0.1 cm");  Lz_DimuC_SR_HighMass->Write();
    Lz_DimuF_SR_HighMass->GetXaxis()->SetTitle("Lz [cm]");   Lz_DimuF_SR_HighMass->GetYaxis()->SetTitle("Events/0.1 cm");  Lz_DimuF_SR_HighMass->Write();
    L_DimuC_CR_HighMass->GetXaxis()->SetTitle("L [cm]");     L_DimuC_CR_HighMass->GetYaxis()->SetTitle("Events/0.1 cm");   L_DimuC_CR_HighMass->Write();
    L_DimuF_CR_HighMass->GetXaxis()->SetTitle("L [cm]");     L_DimuF_CR_HighMass->GetYaxis()->SetTitle("Events/0.1 cm");   L_DimuF_CR_HighMass->Write();
    Lxy_DimuC_CR_HighMass->GetXaxis()->SetTitle("Lxy [cm]"); Lxy_DimuC_CR_HighMass->GetYaxis()->SetTitle("Events/0.1 cm"); Lxy_DimuC_CR_HighMass->Write();
    Lxy_DimuF_CR_HighMass->GetXaxis()->SetTitle("Lxy [cm]"); Lxy_DimuF_CR_HighMass->GetYaxis()->SetTitle("Events/0.1 cm"); Lxy_DimuF_CR_HighMass->Write();
    Lz_DimuC_CR_HighMass->GetXaxis()->SetTitle("Lz [cm]");   Lz_DimuC_CR_HighMass->GetYaxis()->SetTitle("Events/0.1 cm");  Lz_DimuC_CR_HighMass->Write();
    Lz_DimuF_CR_HighMass->GetXaxis()->SetTitle("Lz [cm]");   Lz_DimuF_CR_HighMass->GetYaxis()->SetTitle("Events/0.1 cm");  Lz_DimuF_CR_HighMass->Write();
  } //end if ( ModelBKGShape )

  if ( ModelSRWidth ) {

    DimuCMassAfterCut12->GetXaxis()->SetTitle("m_{#mu#mu1} [GeV]"); DimuCMassAfterCut12->GetYaxis()->SetTitle("Events/0.02 GeV"); DimuCMassAfterCut12->Write();
    DimuFMassAfterCut12->GetXaxis()->SetTitle("m_{#mu#mu2} [GeV]"); DimuFMassAfterCut12->GetYaxis()->SetTitle("Events/0.02 GeV"); DimuFMassAfterCut12->Write();
    DimuCMassAfterCut16->GetXaxis()->SetTitle("m_{#mu#mu1} [GeV]"); DimuCMassAfterCut16->GetYaxis()->SetTitle("Events/0.02 GeV"); DimuCMassAfterCut16->Write();
    DimuFMassAfterCut16->GetXaxis()->SetTitle("m_{#mu#mu2} [GeV]"); DimuFMassAfterCut16->GetYaxis()->SetTitle("Events/0.02 GeV"); DimuFMassAfterCut16->Write();

    //This fits the width
    if (DimuMass->Integral() > 0) {
      DimuMass->SetLineColor(kBlue);
      DimuMass->SetLineWidth(2);
      DimuMass->GetXaxis()->SetTitle("#frac{m_{#mu#mu1}+m_{#mu#mu2}}{2} [GeV]");
      DimuMass->GetYaxis()->SetTitle("Events/0.01 GeV");
      DimuMass->Fit("gaus","","",0,60);
      FitMean = DimuMass->GetFunction("gaus")->GetParameter(1);//get 2nd parameter Mean
      FitSigma = DimuMass->GetFunction("gaus")->GetParameter(2);//get 3rd parameter Sigma
      DimuMass->GetFunction("gaus")->SetLineColor(kBlue);
      DimuMass->GetFunction("gaus")->SetLineStyle(2);
      gStyle->SetOptStat(0);
      DimuMass->Write();

      cout<<"Dimu Mass Fit Mean: "<< FitMean<<"; Fit Sigma: "<< FitSigma<<endl;
    }
  }//end if ( ModelSRWidth )

  if ( PlotdZ ) {
    dZDimuC->GetXaxis()->SetTitle("#Delta z [cm]");   dZDimuC->GetYaxis()->SetTitle("Events/0.01 cm");   dZDimuC->Write();
    dZDimuF->GetXaxis()->SetTitle("#Delta z [cm]");   dZDimuF->GetYaxis()->SetTitle("Events/0.01 cm");   dZDimuF->Write();
    dZdimuons->GetXaxis()->SetTitle("#Delta z [cm]"); dZdimuons->GetYaxis()->SetTitle("Events/0.01 cm"); dZdimuons->Write();
    //Normalized plot
    TH1F *dZdimuons_Normalized = (TH1F*)dZdimuons->Clone("dZdimuons_Normalized");
    //Protect against 0 entry
    if ( dZdimuons->Integral() > 0 ) {
      Double_t scaledZdimuons = 1./dZdimuons->Integral();
      dZdimuons_Normalized->Scale(scaledZdimuons);
      dZdimuons_Normalized->GetXaxis()->SetTitle("#Delta z [cm]"); dZdimuons_Normalized->GetYaxis()->SetTitle("Fraction/0.01 cm"); dZdimuons_Normalized->Write();
    }
  }//end PlotdZ

  if ( PlotIso ) {
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
    if ( IsoDimuC->Integral() > 0 ) { Double_t scaleC = 1./IsoDimuC->Integral(); IsoDimuCNormalized->Scale(scaleC); IsoDimuCNormalized->Write(); }
    if ( IsoDimuF->Integral() > 0 ) { Double_t scaleF = 1./IsoDimuF->Integral(); IsoDimuFNormalized->Scale(scaleF); IsoDimuFNormalized->Write(); }
    if ( IsoDimuCMu0_dR0p3->Integral() > 0 ) { Double_t scaleCMu0_dR0p3 = 1./IsoDimuCMu0_dR0p3->Integral(); IsoDimuCMu0_dR0p3_Normalized->Scale(scaleCMu0_dR0p3); IsoDimuCMu0_dR0p3_Normalized->Write(); }
    if ( IsoDimuCMu0_dR0p4->Integral() > 0 ) { Double_t scaleCMu0_dR0p4 = 1./IsoDimuCMu0_dR0p4->Integral(); IsoDimuCMu0_dR0p4_Normalized->Scale(scaleCMu0_dR0p4); IsoDimuCMu0_dR0p4_Normalized->Write(); }
    if ( IsoDimuCMu0_dR0p5->Integral() > 0 ) { Double_t scaleCMu0_dR0p5 = 1./IsoDimuCMu0_dR0p5->Integral(); IsoDimuCMu0_dR0p5_Normalized->Scale(scaleCMu0_dR0p5); IsoDimuCMu0_dR0p5_Normalized->Write(); }

    if ( IsoDimuCMu1_dR0p3->Integral() > 0 ) { Double_t scaleCMu1_dR0p3 = 1./IsoDimuCMu1_dR0p3->Integral(); IsoDimuCMu1_dR0p3_Normalized->Scale(scaleCMu1_dR0p3); IsoDimuCMu1_dR0p3_Normalized->Write(); }
    if ( IsoDimuCMu1_dR0p4->Integral() > 0 ) { Double_t scaleCMu1_dR0p4 = 1./IsoDimuCMu1_dR0p4->Integral(); IsoDimuCMu1_dR0p4_Normalized->Scale(scaleCMu1_dR0p4); IsoDimuCMu1_dR0p4_Normalized->Write(); }
    if ( IsoDimuCMu1_dR0p5->Integral() > 0 ) { Double_t scaleCMu1_dR0p5 = 1./IsoDimuCMu1_dR0p5->Integral(); IsoDimuCMu1_dR0p5_Normalized->Scale(scaleCMu1_dR0p5); IsoDimuCMu1_dR0p5_Normalized->Write(); }

    if ( IsoDimuFMu0_dR0p3->Integral() > 0 ) { Double_t scaleFMu0_dR0p3 = 1./IsoDimuFMu0_dR0p3->Integral(); IsoDimuFMu0_dR0p3_Normalized->Scale(scaleFMu0_dR0p3); IsoDimuFMu0_dR0p3_Normalized->Write(); }
    if ( IsoDimuFMu0_dR0p4->Integral() > 0 ) { Double_t scaleFMu0_dR0p4 = 1./IsoDimuFMu0_dR0p4->Integral(); IsoDimuFMu0_dR0p4_Normalized->Scale(scaleFMu0_dR0p4); IsoDimuFMu0_dR0p4_Normalized->Write(); }
    if ( IsoDimuFMu0_dR0p5->Integral() > 0 ) { Double_t scaleFMu0_dR0p5 = 1./IsoDimuFMu0_dR0p5->Integral(); IsoDimuFMu0_dR0p5_Normalized->Scale(scaleFMu0_dR0p5); IsoDimuFMu0_dR0p5_Normalized->Write(); }

    if ( IsoDimuFMu1_dR0p3->Integral() > 0 ) { Double_t scaleFMu1_dR0p3 = 1./IsoDimuFMu1_dR0p3->Integral(); IsoDimuFMu1_dR0p3_Normalized->Scale(scaleFMu1_dR0p3); IsoDimuFMu1_dR0p3_Normalized->Write(); }
    if ( IsoDimuFMu1_dR0p4->Integral() > 0 ) { Double_t scaleFMu1_dR0p4 = 1./IsoDimuFMu1_dR0p4->Integral(); IsoDimuFMu1_dR0p4_Normalized->Scale(scaleFMu1_dR0p4); IsoDimuFMu1_dR0p4_Normalized->Write(); }
    if ( IsoDimuFMu1_dR0p5->Integral() > 0 ) { Double_t scaleFMu1_dR0p5 = 1./IsoDimuFMu1_dR0p5->Integral(); IsoDimuFMu1_dR0p5_Normalized->Scale(scaleFMu1_dR0p5); IsoDimuFMu1_dR0p5_Normalized->Write(); }
  }//end if PlotIso

  if ( LoopOrphanTree && PlotIso ) {
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
    if ( IsoOrphanDimu->Integral() > 0 ) { Double_t scaleOrphanDimu = 1./IsoOrphanDimu->Integral(); IsoOrphanDimuNormalized->Scale(scaleOrphanDimu); IsoOrphanDimuNormalized->Write(); }
    if ( IsoOrphanDimuMu0_dR0p3->Integral() > 0 ) { Double_t scaleMu0_dR0p3 = 1./IsoOrphanDimuMu0_dR0p3->Integral(); IsoOrphanDimuMu0_dR0p3_Normalized->Scale(scaleMu0_dR0p3); IsoOrphanDimuMu0_dR0p3_Normalized->Write(); }
    if ( IsoOrphanDimuMu0_dR0p4->Integral() > 0 ) { Double_t scaleMu0_dR0p4 = 1./IsoOrphanDimuMu0_dR0p4->Integral(); IsoOrphanDimuMu0_dR0p4_Normalized->Scale(scaleMu0_dR0p4); IsoOrphanDimuMu0_dR0p4_Normalized->Write(); }
    if ( IsoOrphanDimuMu0_dR0p5->Integral() > 0 ) { Double_t scaleMu0_dR0p5 = 1./IsoOrphanDimuMu0_dR0p5->Integral(); IsoOrphanDimuMu0_dR0p5_Normalized->Scale(scaleMu0_dR0p5); IsoOrphanDimuMu0_dR0p5_Normalized->Write(); }
    if ( IsoOrphanDimuMu1_dR0p3->Integral() > 0 ) { Double_t scaleMu1_dR0p3 = 1./IsoOrphanDimuMu1_dR0p3->Integral(); IsoOrphanDimuMu1_dR0p3_Normalized->Scale(scaleMu1_dR0p3); IsoOrphanDimuMu1_dR0p3_Normalized->Write(); }
    if ( IsoOrphanDimuMu1_dR0p4->Integral() > 0 ) { Double_t scaleMu1_dR0p4 = 1./IsoOrphanDimuMu1_dR0p4->Integral(); IsoOrphanDimuMu1_dR0p4_Normalized->Scale(scaleMu1_dR0p4); IsoOrphanDimuMu1_dR0p4_Normalized->Write(); }
    if ( IsoOrphanDimuMu1_dR0p5->Integral() > 0 ) { Double_t scaleMu1_dR0p5 = 1./IsoOrphanDimuMu1_dR0p5->Integral(); IsoOrphanDimuMu1_dR0p5_Normalized->Scale(scaleMu1_dR0p5); IsoOrphanDimuMu1_dR0p5_Normalized->Write(); }
    if ( IsoOrphan->Integral() > 0 ) { Double_t scaleOrphan = 1./IsoOrphan->Integral(); IsoOrphanNormalized->Scale(scaleOrphan); IsoOrphanNormalized->Write(); }
  }//end if LoopOrphanTree and PlotIso

  if ( LoopOrphanTree && Model1DTemplate ) {
    Mass1DTemplate->GetXaxis()->SetTitle("m_{orphan_#mu#mu} [GeV]");
    Mass1DTemplate->GetYaxis()->SetTitle("Events/0.1 GeV");
    Mass1DTemplate->Write();
    TH1F *Mass1DTemplateNormalized = (TH1F*)Mass1DTemplate->Clone("Mass1DTemplateNormalized");
    if ( Mass1DTemplate->Integral() > 0 ) { Double_t scale1DTemplate = 1./Mass1DTemplate->Integral(); Mass1DTemplateNormalized->Scale(scale1DTemplate); Mass1DTemplateNormalized->Write(); }
  }//end if LoopOrphanTree and Model1DTemplate

  myPlot.Close();

  //Delete objects to avoid potential memory leak
  delete Phase1Pix_GEN_Mu0_pT; delete Phase1Pix_GEN_Mu0_eta; delete Phase1Pix_GEN_Mu0_phi;
  delete Phase1Pix_GEN_Mu1_pT; delete Phase1Pix_GEN_Mu1_eta; delete Phase1Pix_GEN_Mu1_phi;
  delete Phase1Pix_GEN_Mu2_pT; delete Phase1Pix_GEN_Mu2_eta; delete Phase1Pix_GEN_Mu2_phi;
  delete Phase1Pix_GEN_Mu3_pT; delete Phase1Pix_GEN_Mu3_eta; delete Phase1Pix_GEN_Mu3_phi;
  delete Phase1Pix_GEN_A0_Lxy; delete Phase1Pix_GEN_A0_Lz;
  delete Phase1Pix_GEN_A1_Lxy; delete Phase1Pix_GEN_A1_Lz;
  delete Phase1Pix_GEN_A0_Mu0_pT; delete Phase1Pix_GEN_A0_Mu1_pT;
  delete Phase1Pix_GEN_A1_Mu0_pT; delete Phase1Pix_GEN_A1_Mu1_pT;
  delete CvtxProbNoSAmu; delete FvtxProbNoSAmu;
  delete CvtxProbSAmuInC; delete FvtxProbSAmuInF;
  delete DimuCdR; delete DimuFdR;
  delete GENMudR_A0; delete GENMudR_A1;
  delete Phase1Pix_RECO_Mu0_pT; delete Phase1Pix_RECO_Mu0_eta; delete Phase1Pix_RECO_Mu0_phi;
  delete Phase1Pix_RECO_Mu1_pT; delete Phase1Pix_RECO_Mu1_eta; delete Phase1Pix_RECO_Mu1_phi;
  delete Phase1Pix_RECO_Mu2_pT; delete Phase1Pix_RECO_Mu2_eta; delete Phase1Pix_RECO_Mu2_phi;
  delete Phase1Pix_RECO_Mu3_pT; delete Phase1Pix_RECO_Mu3_eta; delete Phase1Pix_RECO_Mu3_phi;
  delete Phase1Pix_RECO_DimuC_Mu0_pT; delete Phase1Pix_RECO_DimuC_Mu1_pT;
  delete Phase1Pix_RECO_DimuF_Mu0_pT; delete Phase1Pix_RECO_DimuF_Mu1_pT;
  delete Lxy; delete Lz;
  delete GENMuPt; delete GENMuEta; delete GENMuPhi; delete GENAMuPt;
  delete RECOMuPt; delete RECOMuEta; delete RECOMuPhi; delete RECODimuMuPt;
  delete GEN1stPt_pass_GEN; delete GEN2ndPt_pass_GEN; delete GEN3rdPt_pass_GEN; delete GEN4thPt_pass_GEN;
  delete GENLeadingLxy_pass_GEN; delete GENLeadingLz_pass_GEN;
  delete GEN1stPt_pass_1stRECOmu; delete GEN2ndPt_pass_2ndRECOmu; delete GEN3rdPt_pass_3rdRECOmu; delete GEN4thPt_pass_4thRECOmu;
  delete GEN1stPt_pass_RECOmu12; delete GEN1stPt_pass_RECOmu123; delete GEN1stPt_pass_RECOmu1234;
  delete GENLeadingLxy_pass_RECOmu1234; delete GENLeadingLz_pass_RECOmu1234;
  delete leading_pt_pass_basic; delete second_pt_pass_basic; delete third_pt_pass_basic; delete fourth_pt_pass_basic;
  delete leading_eta_pass_basic; delete second_eta_pass_basic; delete third_eta_pass_basic; delete fourth_eta_pass_basic;
  delete leading_phi_pass_basic; delete second_phi_pass_basic; delete third_phi_pass_basic; delete fourth_phi_pass_basic;
  delete HLT_leading_pt_pass_basic; delete HLT_second_pt_pass_basic; delete HLT_third_pt_pass_basic; delete HLT_fourth_pt_pass_basic;
  delete HLT_leading_eta_pass_basic; delete HLT_second_eta_pass_basic; delete HLT_third_eta_pass_basic; delete HLT_fourth_eta_pass_basic;
  delete HLT_leading_phi_pass_basic; delete HLT_second_phi_pass_basic; delete HLT_third_phi_pass_basic; delete HLT_fourth_phi_pass_basic;
  delete L1_leading_pt_pass_basic; delete L1_second_pt_pass_basic; delete L1_third_pt_pass_basic; delete L1_fourth_pt_pass_basic;
  delete L1_leading_eta_pass_basic; delete L1_second_eta_pass_basic; delete L1_third_eta_pass_basic; delete L1_fourth_eta_pass_basic;
  delete L1_leading_phi_pass_basic; delete L1_second_phi_pass_basic; delete L1_third_phi_pass_basic; delete L1_fourth_phi_pass_basic;
  delete leading_pt_pass_all; delete second_pt_pass_all; delete third_pt_pass_all; delete fourth_pt_pass_all;
  delete leading_eta_pass_all; delete second_eta_pass_all; delete third_eta_pass_all; delete fourth_eta_pass_all;
  delete leading_phi_pass_all; delete second_phi_pass_all; delete third_phi_pass_all; delete fourth_phi_pass_all;
  delete HLT_leading_pt_pass_all; delete HLT_second_pt_pass_all; delete HLT_third_pt_pass_all; delete HLT_fourth_pt_pass_all;
  delete HLT_leading_eta_pass_all; delete HLT_second_eta_pass_all; delete HLT_third_eta_pass_all; delete HLT_fourth_eta_pass_all;
  delete HLT_leading_phi_pass_all; delete HLT_second_phi_pass_all; delete HLT_third_phi_pass_all; delete HLT_fourth_phi_pass_all;
  delete L1_leading_pt_pass_all; delete L1_second_pt_pass_all; delete L1_third_pt_pass_all; delete L1_fourth_pt_pass_all;
  delete L1_leading_eta_pass_all; delete L1_second_eta_pass_all; delete L1_third_eta_pass_all; delete L1_fourth_eta_pass_all;
  delete L1_leading_phi_pass_all; delete L1_second_phi_pass_all; delete L1_third_phi_pass_all; delete L1_fourth_phi_pass_all;
  delete genA_leading_Lxy_pass_all; delete HLT_genA_leading_Lxy_pass_all;
  delete genA_leading_Lz_pass_all; delete HLT_genA_leading_Lz_pass_all;
  delete diMuon_leading_Lxy_pass_all; delete HLT_diMuon_leading_Lxy_pass_all;
  delete diMuon_leading_Lz_pass_all; delete HLT_diMuon_leading_Lz_pass_all;
  delete BKGShapeCR; delete BKGShapeCRmassC; delete BKGShapeCRmassF;
  delete BKGShapeSR; delete BKGShapeSRmassC; delete BKGShapeSRmassF;
  delete NJetCR; delete NTightBCR; delete NMediumBCR; delete NLooseBCR;
  delete NJetSR; delete NTightBSR; delete NMediumBSR; delete NLooseBSR;
  delete SAmuTrkIsoWP1CR; delete SAmuTrkIsoWP2CR; delete SAmuTrkIsoWP3CR; delete SAmuNTrkWP1CR; delete SAmuNTrkWP2CR; delete SAmuNTrkWP3CR;
  delete SAmuTrkIsoWP1SR; delete SAmuTrkIsoWP2SR; delete SAmuTrkIsoWP3SR; delete SAmuNTrkWP1SR; delete SAmuNTrkWP2SR; delete SAmuNTrkWP3SR;
  delete SAmuTrkIsoNoDzWP1CR; delete SAmuTrkIsoNoDzWP2CR; delete SAmuTrkIsoNoDzWP3CR; delete SAmuNTrkNoDzWP1CR; delete SAmuNTrkNoDzWP2CR; delete SAmuNTrkNoDzWP3CR;
  delete SAmuTrkIsoNoDzWP1SR; delete SAmuTrkIsoNoDzWP2SR; delete SAmuTrkIsoNoDzWP3SR; delete SAmuNTrkNoDzWP1SR; delete SAmuNTrkNoDzWP2SR; delete SAmuNTrkNoDzWP3SR;
  delete SAmuPtCR; delete SAmuEtaCR; delete SAmuPhiCR; delete SAmuPtSR; delete SAmuEtaSR; delete SAmuPhiSR;
  delete L_DimuC_CR_HighMass; delete Lxy_DimuC_CR_HighMass; delete Lz_DimuC_CR_HighMass;
  delete L_DimuF_CR_HighMass; delete Lxy_DimuF_CR_HighMass; delete Lz_DimuF_CR_HighMass;
  delete L_DimuC_SR_HighMass; delete Lxy_DimuC_SR_HighMass; delete Lz_DimuC_SR_HighMass;
  delete L_DimuF_SR_HighMass; delete Lxy_DimuF_SR_HighMass; delete Lz_DimuF_SR_HighMass;
  delete DimuMass;
  delete DimuCMassAfterCut12; delete DimuCMassAfterCut16;
  delete DimuFMassAfterCut12; delete DimuFMassAfterCut16;
  delete RECO4muMass;
  delete RECOrePaired2muLeadingMass; delete RECOrePaired2muLeadingdR;
  delete RECOrePaired2muTrailingMass; delete RECOrePaired2muTrailingdR;
  delete dZDimuC; delete dZDimuF; delete dZdimuons;
  delete IsoDimuC; delete IsoDimuF;
  delete IsoDimuCMu0_dR0p3; delete IsoDimuCMu0_dR0p4; delete IsoDimuCMu0_dR0p5;
  delete IsoDimuCMu1_dR0p3; delete IsoDimuCMu1_dR0p4; delete IsoDimuCMu1_dR0p5;
  delete IsoDimuFMu0_dR0p3; delete IsoDimuFMu0_dR0p4; delete IsoDimuFMu0_dR0p5;
  delete IsoDimuFMu1_dR0p3; delete IsoDimuFMu1_dR0p4; delete IsoDimuFMu1_dR0p5;
  delete Mass1DTemplate;
  delete IsoOrphanDimu;
  delete IsoOrphanDimuMu0_dR0p3; delete IsoOrphanDimuMu0_dR0p4; delete IsoOrphanDimuMu0_dR0p5;
  delete IsoOrphanDimuMu1_dR0p3; delete IsoOrphanDimuMu1_dR0p4; delete IsoOrphanDimuMu1_dR0p5;
  delete IsoOrphan;

}//end efficiency function

void analysis(const std::string SamplesList)
{
  setup();
  //SamplesList is a txt file that lists all sample points, one txt file per sample
  //each txt file contains the Ntuples path of this sample
  //Read sample line by line
  ifstream inputlist(SamplesList);
  string sampletxtfile;
  int linecount = 0;
  //if MSSMD, register mGammaD and cT strings from sampletxtfile
  std::vector<double> mGammaDarray;
  std::vector<double> cTauarray;
  //if NMSSM, register cp-even higgs and cp-odd higgs mass strings from sampletxtfile
  std::vector<double> CPevenHiggs;
  std::vector<double> CPoddHiggs;

  while (std::getline(inputlist, sampletxtfile)) {
    linecount++;
    cout << "Sample #"<< linecount << ": "<< sampletxtfile << endl;

    //MSSMD: assume file format MSSMD_mH_125_mN1_60_mGammaD_XXX_cT_YYYY.txt
    if ( sampletxtfile.find("mGammaD_") != string::npos && sampletxtfile.find("_cT_") != string::npos && sampletxtfile.find(".txt") != string::npos ) {
      unsigned delimiterleft  = sampletxtfile.find("mGammaD_");
      unsigned delimitermiddle = sampletxtfile.find("_cT_");
      unsigned delimiterright = sampletxtfile.find(".txt");
      string mass = sampletxtfile.substr(delimiterleft+8, delimitermiddle-delimiterleft-8);
      string lifetime = sampletxtfile.substr(delimitermiddle+4, delimiterright-delimitermiddle-4);
      if ( mass.find("p") != string::npos ) { std::replace( mass.begin(), mass.end(), 'p', '.'); }
      if ( lifetime.find("p") != string::npos ) { std::replace( lifetime.begin(), lifetime.end(), 'p', '.'); }
      double mGammaD  = std::stod(mass);
      double cTau  = std::stod(lifetime);
      mGammaDarray.push_back(mGammaD);
      cTauarray.push_back(cTau);
      if (sampletxtfile.find("2017") != string::npos) {
        cout << "This is a 2017 MSSMD MC sample: " << "mass = " << mGammaD << " GeV, cT = " << cTau << " mm" << endl;
      }
      if (sampletxtfile.find("2018") != string::npos) {
        cout << "This is a 2018 MSSMD MC sample: " << "mass = " << mGammaD << " GeV, cT = " << cTau << " mm" << endl;
      }

    }//if sampletxtfile is MSSMD

    const std::string txtfile = sampletxtfile;
    std::vector< std::vector<string> > NtuplePaths;
    readTextFileWithSamples(txtfile, NtuplePaths);
    for (auto v: NtuplePaths)  efficiency(v);
    cout << "                       " << endl;
    cout << "#######################" << endl;
  }//end while

  //store selection efficiency plots over all mass points/samples
  TFile finalPlot("analysis.root", "RECREATE");
  cout << "Tot. # of samples: "<< linecount << endl;

  //at least one sample
  if ( linecount >= 1 ) {
    //Calcaulate standard deviation (SD) for selection 12: DY cut
    //Smaller SD indicate better performance on model independence for the selection
    TH1F *finalratio  = new TH1F("finalratio", "", 100, 0., 1.);//binning 0.01
    TH1F *cut12releff = new TH1F("cut12releff","", 100, 0., 1.);
    TH1F *cut12ratio  = new TH1F("cut12ratio", "", 100, 0., 1.);
    for (int iline = 0; iline < linecount; iline++) {
      //cout << iline+1 << ": final ratio = "<< epsvsalph[iline] << "; cut12 releff = " << RelEff[iline][12] << "; cut12 ratio = "<< counter[iline][12]*1.0/counter[iline][5] << endl;
      finalratio->Fill(epsvsalph[iline]);
      cut12releff->Fill(RelEff[iline][12]);
      cut12ratio->Fill(counter[iline][12]*1.0/counter[iline][5]);
    }
    //cout << "final ratio  Sigma: " << finalratio->GetStdDev()  << "; Mean: " << finalratio->GetMean() << endl;
    //cout << "cut12 releff Sigma: " << cut12releff->GetStdDev() << "; Mean: " << cut12releff->GetMean() << endl;
    //cout << "cut12 ratio  Sigma: " << cut12ratio->GetStdDev()  << "; Mean: " << cut12ratio->GetMean() << endl;

    finalratio->Write();
    cut12releff->Write();
    cut12ratio->Write();

    //Each offline selection efficiency/GEN Accept.: counter[12-17]/counter[5]
    //=============================
    //   Efficiency for MSSMD
    //=============================
    double massbin[11] = {0.25, 0.4, 0.7, 1, 2, 5, 8.5, 15, 25, 35, 58};//Exclude 10GeV becaue it's in Upsilon range
    double cTbin[13]   = {0, 0.05, 0.1, 0.2, 0.5, 1, 2, 3, 5, 10, 20, 50, 100};
    int ix, iy;

    //For GEN matched counters
    TCanvas *c_MSSMD_GENMatch_Cut6_5  = new TCanvas("c_MSSMD_GENMatch_Cut6_5",  "c_MSSMD_GENMatch_Cut6_5",  700, 500);
    TCanvas *c_MSSMD_GENMatch_Cut7_5  = new TCanvas("c_MSSMD_GENMatch_Cut7_5",  "c_MSSMD_GENMatch_Cut7_5",  700, 500);
    TCanvas *c_MSSMD_GENMatch_Cut8_5  = new TCanvas("c_MSSMD_GENMatch_Cut8_5",  "c_MSSMD_GENMatch_Cut8_5",  700, 500);
    TCanvas *c_MSSMD_GENMatch_Cut9_5  = new TCanvas("c_MSSMD_GENMatch_Cut9_5",  "c_MSSMD_GENMatch_Cut9_5",  700, 500);
    TCanvas *c_MSSMD_GENMatch_Cut10_5 = new TCanvas("c_MSSMD_GENMatch_Cut10_5", "c_MSSMD_GENMatch_Cut10_5", 700, 500);
    TCanvas *c_MSSMD_GENMatch_Cut11_5 = new TCanvas("c_MSSMD_GENMatch_Cut11_5", "c_MSSMD_GENMatch_Cut11_5", 700, 500);
    TCanvas *c_MSSMD_GENMatch_Cut12_5 = new TCanvas("c_MSSMD_GENMatch_Cut12_5", "c_MSSMD_GENMatch_Cut12_5", 700, 500);
    TCanvas *c_MSSMD_GENMatch_Cut13_5 = new TCanvas("c_MSSMD_GENMatch_Cut13_5", "c_MSSMD_GENMatch_Cut13_5", 700, 500);
    TCanvas *c_MSSMD_GENMatch_Cut14_5 = new TCanvas("c_MSSMD_GENMatch_Cut14_5", "c_MSSMD_GENMatch_Cut14_5", 700, 500);
    TCanvas *c_MSSMD_GENMatch_Cut15_5 = new TCanvas("c_MSSMD_GENMatch_Cut15_5", "c_MSSMD_GENMatch_Cut15_5", 700, 500);
    TCanvas *c_MSSMD_GENMatch_Cut16_5 = new TCanvas("c_MSSMD_GENMatch_Cut16_5", "c_MSSMD_GENMatch_Cut16_5", 700, 500);
    TCanvas *c_MSSMD_GENMatch_Cut17_5 = new TCanvas("c_MSSMD_GENMatch_Cut17_5", "c_MSSMD_GENMatch_Cut17_5", 700, 500);

    TCanvas *c_MSSMD_GENMatch_Cut7_6    = new TCanvas("c_MSSMD_GENMatch_Cut7_6",    "c_MSSMD_GENMatch_Cut7_6",   700, 500);
    TCanvas *c_MSSMD_GENMatch_Cut8_7    = new TCanvas("c_MSSMD_GENMatch_Cut8_7",    "c_MSSMD_GENMatch_Cut8_7",   700, 500);
    TCanvas *c_MSSMD_GENMatch_Cut9_8    = new TCanvas("c_MSSMD_GENMatch_Cut9_8",    "c_MSSMD_GENMatch_Cut9_8",   700, 500);
    TCanvas *c_MSSMD_GENMatch_Cut10_9   = new TCanvas("c_MSSMD_GENMatch_Cut10_9",   "c_MSSMD_GENMatch_Cut10_9",  700, 500);
    TCanvas *c_MSSMD_GENMatch_Cut11_10  = new TCanvas("c_MSSMD_GENMatch_Cut11_10",  "c_MSSMD_GENMatch_Cut11_10", 700, 500);
    TCanvas *c_MSSMD_GENMatch_Cut12_11  = new TCanvas("c_MSSMD_GENMatch_Cut12_11",  "c_MSSMD_GENMatch_Cut12_11", 700, 500);
    TCanvas *c_MSSMD_GENMatch_Cut13_12  = new TCanvas("c_MSSMD_GENMatch_Cut13_12",  "c_MSSMD_GENMatch_Cut13_12", 700, 500);
    TCanvas *c_MSSMD_GENMatch_Cut14_13  = new TCanvas("c_MSSMD_GENMatch_Cut14_13",  "c_MSSMD_GENMatch_Cut14_13", 700, 500);
    TCanvas *c_MSSMD_GENMatch_Cut15_14  = new TCanvas("c_MSSMD_GENMatch_Cut15_14",  "c_MSSMD_GENMatch_Cut15_14", 700, 500);
    TCanvas *c_MSSMD_GENMatch_Cut16_15  = new TCanvas("c_MSSMD_GENMatch_Cut16_15",  "c_MSSMD_GENMatch_Cut16_15", 700, 500);
    TCanvas *c_MSSMD_GENMatch_Cut17_16  = new TCanvas("c_MSSMD_GENMatch_Cut17_16",  "c_MSSMD_GENMatch_Cut17_16", 700, 500);

    TH2F *h_MSSMD_GENMatch_Cut6_5  = new TH2F("h_MSSMD_GENMatch_Cut6_5",  "#splitline{#scale[0.8]{GEN Matched Sel. #6 / Sel. #5}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}",  11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_GENMatch_Cut7_5  = new TH2F("h_MSSMD_GENMatch_Cut7_5",  "#splitline{#scale[0.8]{GEN Matched Sel. #7 / Sel. #5}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}",  11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_GENMatch_Cut8_5  = new TH2F("h_MSSMD_GENMatch_Cut8_5",  "#splitline{#scale[0.8]{GEN Matched Sel. #8 / Sel. #5}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}",  11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_GENMatch_Cut9_5  = new TH2F("h_MSSMD_GENMatch_Cut9_5",  "#splitline{#scale[0.8]{GEN Matched Sel. #9 / Sel. #5}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}",  11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_GENMatch_Cut10_5 = new TH2F("h_MSSMD_GENMatch_Cut10_5", "#splitline{#scale[0.8]{GEN Matched Sel. #10 / Sel. #5}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}", 11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_GENMatch_Cut11_5 = new TH2F("h_MSSMD_GENMatch_Cut11_5", "#splitline{#scale[0.8]{GEN Matched Sel. #11 / Sel. #5}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}", 11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_GENMatch_Cut12_5 = new TH2F("h_MSSMD_GENMatch_Cut12_5", "#splitline{#scale[0.8]{GEN Matched Sel. #12 / Sel. #5}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}", 11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_GENMatch_Cut13_5 = new TH2F("h_MSSMD_GENMatch_Cut13_5", "#splitline{#scale[0.8]{GEN Matched Sel. #13 / Sel. #5}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}", 11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_GENMatch_Cut14_5 = new TH2F("h_MSSMD_GENMatch_Cut14_5", "#splitline{#scale[0.8]{GEN Matched Sel. #14 / Sel. #5}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}", 11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_GENMatch_Cut15_5 = new TH2F("h_MSSMD_GENMatch_Cut15_5", "#splitline{#scale[0.8]{GEN Matched Sel. #15 / Sel. #5}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}", 11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_GENMatch_Cut16_5 = new TH2F("h_MSSMD_GENMatch_Cut16_5", "#splitline{#scale[0.8]{GEN Matched Sel. #16 / Sel. #5}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}", 11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_GENMatch_Cut17_5 = new TH2F("h_MSSMD_GENMatch_Cut17_5", "#splitline{#scale[0.8]{GEN Matched Sel. #17 / Sel. #5}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}", 11, 0, 11, 13, 0, 13);

    TH2F *h_MSSMD_GENMatch_Cut7_6    = new TH2F("h_MSSMD_GENMatch_Cut7_6",    "#splitline{#scale[0.8]{GEN Matched Sel. #7 / Sel. #6}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}",    11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_GENMatch_Cut8_7    = new TH2F("h_MSSMD_GENMatch_Cut8_7",    "#splitline{#scale[0.8]{GEN Matched Sel. #8 / Sel. #7}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}",    11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_GENMatch_Cut9_8    = new TH2F("h_MSSMD_GENMatch_Cut9_8",    "#splitline{#scale[0.8]{GEN Matched Sel. #9 / Sel. #8}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}",    11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_GENMatch_Cut10_9   = new TH2F("h_MSSMD_GENMatch_Cut10_9",   "#splitline{#scale[0.8]{GEN Matched Sel. #10 / Sel. #9}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}",   11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_GENMatch_Cut11_10  = new TH2F("h_MSSMD_GENMatch_Cut11_10",  "#splitline{#scale[0.8]{GEN Matched Sel. #11 / Sel. #10}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}",  11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_GENMatch_Cut12_11  = new TH2F("h_MSSMD_GENMatch_Cut12_11",  "#splitline{#scale[0.8]{GEN Matched Sel. #12 / Sel. #11}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}",  11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_GENMatch_Cut13_12  = new TH2F("h_MSSMD_GENMatch_Cut13_12",  "#splitline{#scale[0.8]{GEN Matched Sel. #13 / Sel. #12}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}",  11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_GENMatch_Cut14_13  = new TH2F("h_MSSMD_GENMatch_Cut14_13",  "#splitline{#scale[0.8]{GEN Matched Sel. #14 / Sel. #13}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}",  11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_GENMatch_Cut15_14  = new TH2F("h_MSSMD_GENMatch_Cut15_14",  "#splitline{#scale[0.8]{GEN Matched Sel. #15 / Sel. #14}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}",  11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_GENMatch_Cut16_15  = new TH2F("h_MSSMD_GENMatch_Cut16_15",  "#splitline{#scale[0.8]{GEN Matched Sel. #16 / Sel. #15}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}",  11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_GENMatch_Cut17_16  = new TH2F("h_MSSMD_GENMatch_Cut17_16",  "#splitline{#scale[0.8]{GEN Matched Sel. #17 / Sel. #16}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}",  11, 0, 11, 13, 0, 13);

    //For cut flow counter (no GEN match)
    TCanvas *c_MSSMD_Cut6_1  = new TCanvas("c_MSSMD_Cut6_1",  "c_MSSMD_Cut6_1",  700, 500);
    TCanvas *c_MSSMD_Cut7_2  = new TCanvas("c_MSSMD_Cut7_2",  "c_MSSMD_Cut7_2",  700, 500);
    TCanvas *c_MSSMD_Cut8_3  = new TCanvas("c_MSSMD_Cut8_3",  "c_MSSMD_Cut8_3",  700, 500);
    TCanvas *c_MSSMD_Cut9_4  = new TCanvas("c_MSSMD_Cut9_4",  "c_MSSMD_Cut9_4",  700, 500);
    TCanvas *c_MSSMD_Cut10_4 = new TCanvas("c_MSSMD_Cut10_4", "c_MSSMD_Cut10_4", 700, 500);
    TCanvas *c_MSSMD_Cut11_4 = new TCanvas("c_MSSMD_Cut11_4", "c_MSSMD_Cut11_4", 700, 500);
    TCanvas *c_MSSMD_Cut12_5 = new TCanvas("c_MSSMD_Cut12_5", "c_MSSMD_Cut12_5", 700, 500);
    TCanvas *c_MSSMD_Cut13_5 = new TCanvas("c_MSSMD_Cut13_5", "c_MSSMD_Cut13_5", 700, 500);
    TCanvas *c_MSSMD_Cut14_5 = new TCanvas("c_MSSMD_Cut14_5", "c_MSSMD_Cut14_5", 700, 500);
    TCanvas *c_MSSMD_Cut15_5 = new TCanvas("c_MSSMD_Cut15_5", "c_MSSMD_Cut15_5", 700, 500);
    TCanvas *c_MSSMD_Cut16_5 = new TCanvas("c_MSSMD_Cut16_5", "c_MSSMD_Cut16_5", 700, 500);
    TCanvas *c_MSSMD_Cut17_5 = new TCanvas("c_MSSMD_Cut17_5", "c_MSSMD_Cut17_5", 700, 500);

    TCanvas *c_MSSMD_Cut10_9  = new TCanvas("c_MSSMD_Cut10_9",  "c_MSSMD_Cut10_9",  700, 500);
    TCanvas *c_MSSMD_Cut11_10 = new TCanvas("c_MSSMD_Cut11_10", "c_MSSMD_Cut11_10", 700, 500);

    TCanvas *c_MSSMD_Cut13_12 = new TCanvas("c_MSSMD_Cut13_12", "c_MSSMD_Cut13_12", 700, 500);
    TCanvas *c_MSSMD_Cut14_13 = new TCanvas("c_MSSMD_Cut14_13", "c_MSSMD_Cut14_13", 700, 500);
    TCanvas *c_MSSMD_Cut15_14 = new TCanvas("c_MSSMD_Cut15_14", "c_MSSMD_Cut15_14", 700, 500);
    TCanvas *c_MSSMD_Cut16_15 = new TCanvas("c_MSSMD_Cut16_15", "c_MSSMD_Cut16_15", 700, 500);
    TCanvas *c_MSSMD_Cut17_16 = new TCanvas("c_MSSMD_Cut17_16", "c_MSSMD_Cut17_16", 700, 500);

    TH2F *h_MSSMD_Cut6_1  = new TH2F("h_MSSMD_Cut6_1",  "#splitline{#scale[0.8]{Offline Sel. #6 / GEN. Sel. #1}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}",  11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_Cut7_2  = new TH2F("h_MSSMD_Cut7_2",  "#splitline{#scale[0.8]{Offline Sel. #7 / GEN. Sel. #2}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}",  11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_Cut8_3  = new TH2F("h_MSSMD_Cut8_3",  "#splitline{#scale[0.8]{Offline Sel. #8 / GEN. Sel. #3}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}",  11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_Cut9_4  = new TH2F("h_MSSMD_Cut9_4",  "#splitline{#scale[0.8]{Offline Sel. #9 / GEN. Sel. #4}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}",  11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_Cut10_4 = new TH2F("h_MSSMD_Cut10_4", "#splitline{#scale[0.8]{Offline Sel. #10 / GEN. Sel. #4}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}", 11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_Cut11_4 = new TH2F("h_MSSMD_Cut11_4", "#splitline{#scale[0.8]{Offline Sel. #11 / GEN. Sel. #4}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}", 11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_Cut12_5 = new TH2F("h_MSSMD_Cut12_5", "#splitline{#scale[0.8]{Offline Sel. #12 / GEN. Sel. #5}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}", 11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_Cut13_5 = new TH2F("h_MSSMD_Cut13_5", "#splitline{#scale[0.8]{Offline Sel. #13 / GEN. Sel. #5}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}", 11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_Cut14_5 = new TH2F("h_MSSMD_Cut14_5", "#splitline{#scale[0.8]{Offline Sel. #14 / GEN. Sel. #5}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}", 11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_Cut15_5 = new TH2F("h_MSSMD_Cut15_5", "#splitline{#scale[0.8]{Offline Sel. #15 / GEN. Sel. #5}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}", 11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_Cut16_5 = new TH2F("h_MSSMD_Cut16_5", "#splitline{#scale[0.8]{Offline Sel. #16 / GEN. Sel. #5}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}", 11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_Cut17_5 = new TH2F("h_MSSMD_Cut17_5", "#splitline{#scale[0.8]{Offline Sel. #17 / GEN. Sel. #5}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}", 11, 0, 11, 13, 0, 13);

    TH2F *h_MSSMD_Cut10_9  = new TH2F("h_MSSMD_Cut10_9",  "#splitline{#scale[0.8]{Offline Sel. #10 / Sel. #9}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}",  11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_Cut11_10 = new TH2F("h_MSSMD_Cut11_10", "#splitline{#scale[0.8]{Offline Sel. #11 / Sel. #10}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}", 11, 0, 11, 13, 0, 13);

    TH2F *h_MSSMD_Cut13_12 = new TH2F("h_MSSMD_Cut13_12", "#splitline{#scale[0.8]{Offline Sel. #13 / Sel. #12}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}", 11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_Cut14_13 = new TH2F("h_MSSMD_Cut14_13", "#splitline{#scale[0.8]{Offline Sel. #14 / Sel. #13}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}", 11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_Cut15_14 = new TH2F("h_MSSMD_Cut15_14", "#splitline{#scale[0.8]{Offline Sel. #15 / Sel. #14}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}", 11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_Cut16_15 = new TH2F("h_MSSMD_Cut16_15", "#splitline{#scale[0.8]{Offline Sel. #16 / Sel. #15}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}", 11, 0, 11, 13, 0, 13);
    TH2F *h_MSSMD_Cut17_16 = new TH2F("h_MSSMD_Cut17_16", "#splitline{#scale[0.8]{Offline Sel. #17 / Sel. #16}}{#scale[0.5]{MSSMD: m_{h}=125GeV, m_{n_{1}}=60GeV, m_{n_{D}}=1GeV}}", 11, 0, 11, 13, 0, 13);

    if ( mGammaDarray.size() > 0 ) {

      for (UInt_t i = 0; i < mGammaDarray.size(); i++) {
        ix = 0;
        iy = 0;
        //loop through all mass to get bin index
        for (int j=0; j<11; j++) {
          if ( mGammaDarray[i] == massbin[j] ) { ix = j+1; }
        }//end loop mass
        //loop through all cT to get bin index
        for (int k=0; k<13; k++) {
          if ( cTauarray[i] == cTbin[k] ) { iy = k+1; }
        }//end loop mass
        //cout << "ix: " << ix  << "; iy: " << iy << endl;

        h_MSSMD_GENMatch_Cut6_5->SetBinContent(ix,  iy, round(counterGENMatch[i][6]*10000.0/counterGENMatch[i][5])/10000 );
        h_MSSMD_GENMatch_Cut7_5->SetBinContent(ix,  iy, round(counterGENMatch[i][7]*10000.0/counterGENMatch[i][5])/10000 );
        h_MSSMD_GENMatch_Cut8_5->SetBinContent(ix,  iy, round(counterGENMatch[i][8]*10000.0/counterGENMatch[i][5])/10000 );
        h_MSSMD_GENMatch_Cut9_5->SetBinContent(ix,  iy, round(counterGENMatch[i][9]*10000.0/counterGENMatch[i][5])/10000 );
        h_MSSMD_GENMatch_Cut10_5->SetBinContent(ix, iy, round(counterGENMatch[i][10]*10000.0/counterGENMatch[i][5])/10000 );
        h_MSSMD_GENMatch_Cut11_5->SetBinContent(ix, iy, round(counterGENMatch[i][11]*10000.0/counterGENMatch[i][5])/10000 );
        h_MSSMD_GENMatch_Cut12_5->SetBinContent(ix, iy, round(counterGENMatch[i][12]*10000.0/counterGENMatch[i][5])/10000 );
        h_MSSMD_GENMatch_Cut13_5->SetBinContent(ix, iy, round(counterGENMatch[i][13]*10000.0/counterGENMatch[i][5])/10000 );
        h_MSSMD_GENMatch_Cut14_5->SetBinContent(ix, iy, round(counterGENMatch[i][14]*10000.0/counterGENMatch[i][5])/10000 );
        h_MSSMD_GENMatch_Cut15_5->SetBinContent(ix, iy, round(counterGENMatch[i][15]*10000.0/counterGENMatch[i][5])/10000 );
        h_MSSMD_GENMatch_Cut16_5->SetBinContent(ix, iy, round(counterGENMatch[i][16]*10000.0/counterGENMatch[i][5])/10000 );
        h_MSSMD_GENMatch_Cut17_5->SetBinContent(ix, iy, round(counterGENMatch[i][17]*10000.0/counterGENMatch[i][5])/10000 );

        h_MSSMD_GENMatch_Cut7_6->SetBinContent(ix,   iy, round(counterGENMatch[i][7]*10000.0/counterGENMatch[i][6])/10000 );
        h_MSSMD_GENMatch_Cut8_7->SetBinContent(ix,   iy, round(counterGENMatch[i][8]*10000.0/counterGENMatch[i][7])/10000 );
        h_MSSMD_GENMatch_Cut9_8->SetBinContent(ix,   iy, round(counterGENMatch[i][9]*10000.0/counterGENMatch[i][8])/10000 );
        h_MSSMD_GENMatch_Cut10_9->SetBinContent(ix,  iy, round(counterGENMatch[i][10]*10000.0/counterGENMatch[i][9])/10000 );
        h_MSSMD_GENMatch_Cut11_10->SetBinContent(ix, iy, round(counterGENMatch[i][11]*10000.0/counterGENMatch[i][10])/10000 );
        h_MSSMD_GENMatch_Cut12_11->SetBinContent(ix, iy, round(counterGENMatch[i][12]*10000.0/counterGENMatch[i][11])/10000 );
        h_MSSMD_GENMatch_Cut13_12->SetBinContent(ix, iy, round(counterGENMatch[i][13]*10000.0/counterGENMatch[i][12])/10000 );
        h_MSSMD_GENMatch_Cut14_13->SetBinContent(ix, iy, round(counterGENMatch[i][14]*10000.0/counterGENMatch[i][13])/10000 );
        h_MSSMD_GENMatch_Cut15_14->SetBinContent(ix, iy, round(counterGENMatch[i][15]*10000.0/counterGENMatch[i][14])/10000 );
        h_MSSMD_GENMatch_Cut16_15->SetBinContent(ix, iy, round(counterGENMatch[i][16]*10000.0/counterGENMatch[i][15])/10000 );
        h_MSSMD_GENMatch_Cut17_16->SetBinContent(ix, iy, round(counterGENMatch[i][17]*10000.0/counterGENMatch[i][16])/10000 );

        h_MSSMD_Cut6_1->SetBinContent(ix, iy, round(counter[i][6]*1000.0/counter[i][1])/1000 );
        h_MSSMD_Cut7_2->SetBinContent(ix, iy, round(counter[i][7]*1000.0/counter[i][2])/1000 );
        h_MSSMD_Cut8_3->SetBinContent(ix, iy, round(counter[i][8]*1000.0/counter[i][3])/1000 );
        h_MSSMD_Cut9_4->SetBinContent(ix, iy, round(counter[i][9]*1000.0/counter[i][4])/1000 );
        h_MSSMD_Cut10_4->SetBinContent(ix, iy, round(counter[i][10]*1000.0/counter[i][4])/1000 );
        h_MSSMD_Cut11_4->SetBinContent(ix, iy, round(counter[i][11]*1000.0/counter[i][4])/1000 );//doesn't make sense to compare to #5
        h_MSSMD_Cut12_5->SetBinContent(ix, iy, round(counter[i][12]*1000.0/counter[i][5])/1000 );
        h_MSSMD_Cut13_5->SetBinContent(ix, iy, round(counter[i][13]*1000.0/counter[i][5])/1000 );
        h_MSSMD_Cut14_5->SetBinContent(ix, iy, round(counter[i][14]*1000.0/counter[i][5])/1000 );
        h_MSSMD_Cut15_5->SetBinContent(ix, iy, round(counter[i][15]*1000.0/counter[i][5])/1000 );
        h_MSSMD_Cut16_5->SetBinContent(ix, iy, round(counter[i][16]*1000.0/counter[i][5])/1000 );
        h_MSSMD_Cut17_5->SetBinContent(ix, iy, round(epsvsalph[i]*1000.0)/1000 );

        h_MSSMD_Cut10_9->SetBinContent(ix, iy, round(counter[i][10]*1000.0/counter[i][9])/1000 );
        h_MSSMD_Cut11_10->SetBinContent(ix, iy, round(counter[i][11]*1000.0/counter[i][10])/1000 );

        h_MSSMD_Cut13_12->SetBinContent(ix, iy, round(counter[i][13]*1000.0/counter[i][12])/1000 );
        h_MSSMD_Cut14_13->SetBinContent(ix, iy, round(counter[i][14]*1000.0/counter[i][13])/1000 );
        h_MSSMD_Cut15_14->SetBinContent(ix, iy, round(counter[i][15]*1000.0/counter[i][14])/1000 );
        h_MSSMD_Cut16_15->SetBinContent(ix, iy, round(counter[i][16]*1000.0/counter[i][15])/1000 );
        h_MSSMD_Cut17_16->SetBinContent(ix, iy, round(counter[i][17]*1000.0/counter[i][16])/1000 );
        //cout << "Mass: " << mGammaDarray[i]  << "; cT: " << cTauarray[i] << "; eff: "<< counter[i][12]*1.0/counter[i][5] << endl;
      }

      for (unsigned int iXL=1; iXL<=11; iXL++) {
        //cout << "iXL: " << iXL  << endl;
        h_MSSMD_GENMatch_Cut6_5->GetXaxis()->SetBinLabel(iXL,  Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_GENMatch_Cut7_5->GetXaxis()->SetBinLabel(iXL,  Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_GENMatch_Cut8_5->GetXaxis()->SetBinLabel(iXL,  Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_GENMatch_Cut9_5->GetXaxis()->SetBinLabel(iXL,  Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_GENMatch_Cut10_5->GetXaxis()->SetBinLabel(iXL, Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_GENMatch_Cut11_5->GetXaxis()->SetBinLabel(iXL, Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_GENMatch_Cut12_5->GetXaxis()->SetBinLabel(iXL, Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_GENMatch_Cut13_5->GetXaxis()->SetBinLabel(iXL, Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_GENMatch_Cut14_5->GetXaxis()->SetBinLabel(iXL, Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_GENMatch_Cut15_5->GetXaxis()->SetBinLabel(iXL, Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_GENMatch_Cut16_5->GetXaxis()->SetBinLabel(iXL, Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_GENMatch_Cut17_5->GetXaxis()->SetBinLabel(iXL, Form("%.2f", massbin[iXL-1]) );

        h_MSSMD_GENMatch_Cut7_6->GetXaxis()->SetBinLabel(iXL,   Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_GENMatch_Cut8_7->GetXaxis()->SetBinLabel(iXL,   Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_GENMatch_Cut9_8->GetXaxis()->SetBinLabel(iXL,   Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_GENMatch_Cut10_9->GetXaxis()->SetBinLabel(iXL,  Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_GENMatch_Cut11_10->GetXaxis()->SetBinLabel(iXL, Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_GENMatch_Cut12_11->GetXaxis()->SetBinLabel(iXL, Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_GENMatch_Cut13_12->GetXaxis()->SetBinLabel(iXL, Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_GENMatch_Cut14_13->GetXaxis()->SetBinLabel(iXL, Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_GENMatch_Cut15_14->GetXaxis()->SetBinLabel(iXL, Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_GENMatch_Cut16_15->GetXaxis()->SetBinLabel(iXL, Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_GENMatch_Cut17_16->GetXaxis()->SetBinLabel(iXL, Form("%.2f", massbin[iXL-1]) );

        h_MSSMD_Cut6_1->GetXaxis()->SetBinLabel(iXL,  Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_Cut7_2->GetXaxis()->SetBinLabel(iXL,  Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_Cut8_3->GetXaxis()->SetBinLabel(iXL,  Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_Cut9_4->GetXaxis()->SetBinLabel(iXL,  Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_Cut10_4->GetXaxis()->SetBinLabel(iXL, Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_Cut11_4->GetXaxis()->SetBinLabel(iXL, Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_Cut12_5->GetXaxis()->SetBinLabel(iXL, Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_Cut13_5->GetXaxis()->SetBinLabel(iXL, Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_Cut14_5->GetXaxis()->SetBinLabel(iXL, Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_Cut15_5->GetXaxis()->SetBinLabel(iXL, Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_Cut16_5->GetXaxis()->SetBinLabel(iXL, Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_Cut17_5->GetXaxis()->SetBinLabel(iXL, Form("%.2f", massbin[iXL-1]) );

        h_MSSMD_Cut10_9->GetXaxis()->SetBinLabel(iXL,  Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_Cut11_10->GetXaxis()->SetBinLabel(iXL, Form("%.2f", massbin[iXL-1]) );

        h_MSSMD_Cut13_12->GetXaxis()->SetBinLabel(iXL, Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_Cut14_13->GetXaxis()->SetBinLabel(iXL, Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_Cut15_14->GetXaxis()->SetBinLabel(iXL, Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_Cut16_15->GetXaxis()->SetBinLabel(iXL, Form("%.2f", massbin[iXL-1]) );
        h_MSSMD_Cut17_16->GetXaxis()->SetBinLabel(iXL, Form("%.2f", massbin[iXL-1]) );
      }

      for (unsigned int iYL=1; iYL<=13; iYL++) {
        //cout << "iYL: " << iYL  << endl;
        h_MSSMD_GENMatch_Cut6_5->GetYaxis()->SetBinLabel(iYL,   Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_GENMatch_Cut7_5->GetYaxis()->SetBinLabel(iYL,   Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_GENMatch_Cut8_5->GetYaxis()->SetBinLabel(iYL,   Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_GENMatch_Cut9_5->GetYaxis()->SetBinLabel(iYL,   Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_GENMatch_Cut10_5->GetYaxis()->SetBinLabel(iYL,  Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_GENMatch_Cut11_5->GetYaxis()->SetBinLabel(iYL,  Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_GENMatch_Cut12_5->GetYaxis()->SetBinLabel(iYL,  Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_GENMatch_Cut13_5->GetYaxis()->SetBinLabel(iYL,  Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_GENMatch_Cut14_5->GetYaxis()->SetBinLabel(iYL,  Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_GENMatch_Cut15_5->GetYaxis()->SetBinLabel(iYL,  Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_GENMatch_Cut16_5->GetYaxis()->SetBinLabel(iYL,  Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_GENMatch_Cut17_5->GetYaxis()->SetBinLabel(iYL,  Form("%.2f", cTbin[iYL-1]) );

        h_MSSMD_GENMatch_Cut7_6->GetYaxis()->SetBinLabel(iYL,    Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_GENMatch_Cut8_7->GetYaxis()->SetBinLabel(iYL,    Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_GENMatch_Cut9_8->GetYaxis()->SetBinLabel(iYL,    Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_GENMatch_Cut10_9->GetYaxis()->SetBinLabel(iYL,   Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_GENMatch_Cut11_10->GetYaxis()->SetBinLabel(iYL,  Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_GENMatch_Cut12_11->GetYaxis()->SetBinLabel(iYL,  Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_GENMatch_Cut13_12->GetYaxis()->SetBinLabel(iYL,  Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_GENMatch_Cut14_13->GetYaxis()->SetBinLabel(iYL,  Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_GENMatch_Cut15_14->GetYaxis()->SetBinLabel(iYL,  Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_GENMatch_Cut16_15->GetYaxis()->SetBinLabel(iYL,  Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_GENMatch_Cut17_16->GetYaxis()->SetBinLabel(iYL,  Form("%.2f", cTbin[iYL-1]) );

        h_MSSMD_Cut6_1->GetYaxis()->SetBinLabel(iYL,  Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_Cut7_2->GetYaxis()->SetBinLabel(iYL,  Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_Cut8_3->GetYaxis()->SetBinLabel(iYL,  Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_Cut9_4->GetYaxis()->SetBinLabel(iYL,  Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_Cut10_4->GetYaxis()->SetBinLabel(iYL, Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_Cut11_4->GetYaxis()->SetBinLabel(iYL, Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_Cut12_5->GetYaxis()->SetBinLabel(iYL, Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_Cut13_5->GetYaxis()->SetBinLabel(iYL, Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_Cut14_5->GetYaxis()->SetBinLabel(iYL, Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_Cut15_5->GetYaxis()->SetBinLabel(iYL, Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_Cut16_5->GetYaxis()->SetBinLabel(iYL, Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_Cut17_5->GetYaxis()->SetBinLabel(iYL, Form("%.2f", cTbin[iYL-1]) );

        h_MSSMD_Cut10_9->GetYaxis()->SetBinLabel(iYL,  Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_Cut11_10->GetYaxis()->SetBinLabel(iYL, Form("%.2f", cTbin[iYL-1]) );

        h_MSSMD_Cut13_12->GetYaxis()->SetBinLabel(iYL, Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_Cut14_13->GetYaxis()->SetBinLabel(iYL, Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_Cut15_14->GetYaxis()->SetBinLabel(iYL, Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_Cut16_15->GetYaxis()->SetBinLabel(iYL, Form("%.2f", cTbin[iYL-1]) );
        h_MSSMD_Cut17_16->GetYaxis()->SetBinLabel(iYL, Form("%.2f", cTbin[iYL-1]) );
      }

      c_MSSMD_GENMatch_Cut6_5->cd();  h_MSSMD_GENMatch_Cut6_5->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]");  h_MSSMD_GENMatch_Cut6_5->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]");  h_MSSMD_GENMatch_Cut6_5->SetStats(0);  h_MSSMD_GENMatch_Cut6_5->Draw("COLZ TEXT");  h_MSSMD_GENMatch_Cut6_5->SetMinimum(0);  h_MSSMD_GENMatch_Cut6_5->SetMaximum(1);  c_MSSMD_GENMatch_Cut6_5->Write();
      c_MSSMD_GENMatch_Cut7_5->cd();  h_MSSMD_GENMatch_Cut7_5->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]");  h_MSSMD_GENMatch_Cut7_5->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]");  h_MSSMD_GENMatch_Cut7_5->SetStats(0);  h_MSSMD_GENMatch_Cut7_5->Draw("COLZ TEXT");  h_MSSMD_GENMatch_Cut7_5->SetMinimum(0);  h_MSSMD_GENMatch_Cut7_5->SetMaximum(1);  c_MSSMD_GENMatch_Cut7_5->Write();
      c_MSSMD_GENMatch_Cut8_5->cd();  h_MSSMD_GENMatch_Cut8_5->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]");  h_MSSMD_GENMatch_Cut8_5->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]");  h_MSSMD_GENMatch_Cut8_5->SetStats(0);  h_MSSMD_GENMatch_Cut8_5->Draw("COLZ TEXT");  h_MSSMD_GENMatch_Cut8_5->SetMinimum(0);  h_MSSMD_GENMatch_Cut8_5->SetMaximum(1);  c_MSSMD_GENMatch_Cut8_5->Write();
      c_MSSMD_GENMatch_Cut9_5->cd();  h_MSSMD_GENMatch_Cut9_5->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]");  h_MSSMD_GENMatch_Cut9_5->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]");  h_MSSMD_GENMatch_Cut9_5->SetStats(0);  h_MSSMD_GENMatch_Cut9_5->Draw("COLZ TEXT");  h_MSSMD_GENMatch_Cut9_5->SetMinimum(0);  h_MSSMD_GENMatch_Cut9_5->SetMaximum(1);  c_MSSMD_GENMatch_Cut9_5->Write();
      c_MSSMD_GENMatch_Cut10_5->cd(); h_MSSMD_GENMatch_Cut10_5->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]"); h_MSSMD_GENMatch_Cut10_5->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]"); h_MSSMD_GENMatch_Cut10_5->SetStats(0); h_MSSMD_GENMatch_Cut10_5->Draw("COLZ TEXT"); h_MSSMD_GENMatch_Cut10_5->SetMinimum(0); h_MSSMD_GENMatch_Cut10_5->SetMaximum(1); c_MSSMD_GENMatch_Cut10_5->Write();
      c_MSSMD_GENMatch_Cut11_5->cd(); h_MSSMD_GENMatch_Cut11_5->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]"); h_MSSMD_GENMatch_Cut11_5->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]"); h_MSSMD_GENMatch_Cut11_5->SetStats(0); h_MSSMD_GENMatch_Cut11_5->Draw("COLZ TEXT"); h_MSSMD_GENMatch_Cut11_5->SetMinimum(0); h_MSSMD_GENMatch_Cut11_5->SetMaximum(1); c_MSSMD_GENMatch_Cut11_5->Write();
      c_MSSMD_GENMatch_Cut12_5->cd(); h_MSSMD_GENMatch_Cut12_5->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]"); h_MSSMD_GENMatch_Cut12_5->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]"); h_MSSMD_GENMatch_Cut12_5->SetStats(0); h_MSSMD_GENMatch_Cut12_5->Draw("COLZ TEXT"); h_MSSMD_GENMatch_Cut12_5->SetMinimum(0); h_MSSMD_GENMatch_Cut12_5->SetMaximum(1); c_MSSMD_GENMatch_Cut12_5->Write();
      c_MSSMD_GENMatch_Cut13_5->cd(); h_MSSMD_GENMatch_Cut13_5->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]"); h_MSSMD_GENMatch_Cut13_5->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]"); h_MSSMD_GENMatch_Cut13_5->SetStats(0); h_MSSMD_GENMatch_Cut13_5->Draw("COLZ TEXT"); h_MSSMD_GENMatch_Cut13_5->SetMinimum(0); h_MSSMD_GENMatch_Cut13_5->SetMaximum(1); c_MSSMD_GENMatch_Cut13_5->Write();
      c_MSSMD_GENMatch_Cut14_5->cd(); h_MSSMD_GENMatch_Cut14_5->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]"); h_MSSMD_GENMatch_Cut14_5->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]"); h_MSSMD_GENMatch_Cut14_5->SetStats(0); h_MSSMD_GENMatch_Cut14_5->Draw("COLZ TEXT"); h_MSSMD_GENMatch_Cut14_5->SetMinimum(0); h_MSSMD_GENMatch_Cut14_5->SetMaximum(1); c_MSSMD_GENMatch_Cut14_5->Write();
      c_MSSMD_GENMatch_Cut15_5->cd(); h_MSSMD_GENMatch_Cut15_5->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]"); h_MSSMD_GENMatch_Cut15_5->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]"); h_MSSMD_GENMatch_Cut15_5->SetStats(0); h_MSSMD_GENMatch_Cut15_5->Draw("COLZ TEXT"); h_MSSMD_GENMatch_Cut15_5->SetMinimum(0); h_MSSMD_GENMatch_Cut15_5->SetMaximum(1); c_MSSMD_GENMatch_Cut15_5->Write();
      c_MSSMD_GENMatch_Cut16_5->cd(); h_MSSMD_GENMatch_Cut16_5->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]"); h_MSSMD_GENMatch_Cut16_5->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]"); h_MSSMD_GENMatch_Cut16_5->SetStats(0); h_MSSMD_GENMatch_Cut16_5->Draw("COLZ TEXT"); h_MSSMD_GENMatch_Cut16_5->SetMinimum(0); h_MSSMD_GENMatch_Cut16_5->SetMaximum(1); c_MSSMD_GENMatch_Cut16_5->Write();
      c_MSSMD_GENMatch_Cut17_5->cd(); h_MSSMD_GENMatch_Cut17_5->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]"); h_MSSMD_GENMatch_Cut17_5->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]"); h_MSSMD_GENMatch_Cut17_5->SetStats(0); h_MSSMD_GENMatch_Cut17_5->Draw("COLZ TEXT"); h_MSSMD_GENMatch_Cut17_5->SetMinimum(0); h_MSSMD_GENMatch_Cut17_5->SetMaximum(1); c_MSSMD_GENMatch_Cut17_5->Write();

      c_MSSMD_GENMatch_Cut7_6->cd();   h_MSSMD_GENMatch_Cut7_6->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]");   h_MSSMD_GENMatch_Cut7_6->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]");   h_MSSMD_GENMatch_Cut7_6->SetStats(0);   h_MSSMD_GENMatch_Cut7_6->Draw("COLZ TEXT");   h_MSSMD_GENMatch_Cut7_6->SetMinimum(0);   h_MSSMD_GENMatch_Cut7_6->SetMaximum(1);   c_MSSMD_GENMatch_Cut7_6->Write();
      c_MSSMD_GENMatch_Cut8_7->cd();   h_MSSMD_GENMatch_Cut8_7->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]");   h_MSSMD_GENMatch_Cut8_7->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]");   h_MSSMD_GENMatch_Cut8_7->SetStats(0);   h_MSSMD_GENMatch_Cut8_7->Draw("COLZ TEXT");   h_MSSMD_GENMatch_Cut8_7->SetMinimum(0);   h_MSSMD_GENMatch_Cut8_7->SetMaximum(1);   c_MSSMD_GENMatch_Cut8_7->Write();
      c_MSSMD_GENMatch_Cut9_8->cd();   h_MSSMD_GENMatch_Cut9_8->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]");   h_MSSMD_GENMatch_Cut9_8->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]");   h_MSSMD_GENMatch_Cut9_8->SetStats(0);   h_MSSMD_GENMatch_Cut9_8->Draw("COLZ TEXT");   h_MSSMD_GENMatch_Cut9_8->SetMinimum(0);   h_MSSMD_GENMatch_Cut9_8->SetMaximum(1);   c_MSSMD_GENMatch_Cut9_8->Write();
      c_MSSMD_GENMatch_Cut10_9->cd();  h_MSSMD_GENMatch_Cut10_9->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]");  h_MSSMD_GENMatch_Cut10_9->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]");  h_MSSMD_GENMatch_Cut10_9->SetStats(0);  h_MSSMD_GENMatch_Cut10_9->Draw("COLZ TEXT");  h_MSSMD_GENMatch_Cut10_9->SetMinimum(0);  h_MSSMD_GENMatch_Cut10_9->SetMaximum(1);  c_MSSMD_GENMatch_Cut10_9->Write();
      c_MSSMD_GENMatch_Cut11_10->cd(); h_MSSMD_GENMatch_Cut11_10->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]"); h_MSSMD_GENMatch_Cut11_10->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]"); h_MSSMD_GENMatch_Cut11_10->SetStats(0); h_MSSMD_GENMatch_Cut11_10->Draw("COLZ TEXT"); h_MSSMD_GENMatch_Cut11_10->SetMinimum(0); h_MSSMD_GENMatch_Cut11_10->SetMaximum(1); c_MSSMD_GENMatch_Cut11_10->Write();
      c_MSSMD_GENMatch_Cut12_11->cd(); h_MSSMD_GENMatch_Cut12_11->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]"); h_MSSMD_GENMatch_Cut12_11->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]"); h_MSSMD_GENMatch_Cut12_11->SetStats(0); h_MSSMD_GENMatch_Cut12_11->Draw("COLZ TEXT"); h_MSSMD_GENMatch_Cut12_11->SetMinimum(0); h_MSSMD_GENMatch_Cut12_11->SetMaximum(1); c_MSSMD_GENMatch_Cut12_11->Write();
      c_MSSMD_GENMatch_Cut13_12->cd(); h_MSSMD_GENMatch_Cut13_12->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]"); h_MSSMD_GENMatch_Cut13_12->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]"); h_MSSMD_GENMatch_Cut13_12->SetStats(0); h_MSSMD_GENMatch_Cut13_12->Draw("COLZ TEXT"); h_MSSMD_GENMatch_Cut13_12->SetMinimum(0); h_MSSMD_GENMatch_Cut13_12->SetMaximum(1); c_MSSMD_GENMatch_Cut13_12->Write();
      c_MSSMD_GENMatch_Cut14_13->cd(); h_MSSMD_GENMatch_Cut14_13->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]"); h_MSSMD_GENMatch_Cut14_13->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]"); h_MSSMD_GENMatch_Cut14_13->SetStats(0); h_MSSMD_GENMatch_Cut14_13->Draw("COLZ TEXT"); h_MSSMD_GENMatch_Cut14_13->SetMinimum(0); h_MSSMD_GENMatch_Cut14_13->SetMaximum(1); c_MSSMD_GENMatch_Cut14_13->Write();
      c_MSSMD_GENMatch_Cut15_14->cd(); h_MSSMD_GENMatch_Cut15_14->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]"); h_MSSMD_GENMatch_Cut15_14->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]"); h_MSSMD_GENMatch_Cut15_14->SetStats(0); h_MSSMD_GENMatch_Cut15_14->Draw("COLZ TEXT"); h_MSSMD_GENMatch_Cut15_14->SetMinimum(0); h_MSSMD_GENMatch_Cut15_14->SetMaximum(1); c_MSSMD_GENMatch_Cut15_14->Write();
      c_MSSMD_GENMatch_Cut16_15->cd(); h_MSSMD_GENMatch_Cut16_15->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]"); h_MSSMD_GENMatch_Cut16_15->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]"); h_MSSMD_GENMatch_Cut16_15->SetStats(0); h_MSSMD_GENMatch_Cut16_15->Draw("COLZ TEXT"); h_MSSMD_GENMatch_Cut16_15->SetMinimum(0); h_MSSMD_GENMatch_Cut16_15->SetMaximum(1); c_MSSMD_GENMatch_Cut16_15->Write();
      c_MSSMD_GENMatch_Cut17_16->cd(); h_MSSMD_GENMatch_Cut17_16->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]"); h_MSSMD_GENMatch_Cut17_16->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]"); h_MSSMD_GENMatch_Cut17_16->SetStats(0); h_MSSMD_GENMatch_Cut17_16->Draw("COLZ TEXT"); h_MSSMD_GENMatch_Cut17_16->SetMinimum(0); h_MSSMD_GENMatch_Cut17_16->SetMaximum(1); c_MSSMD_GENMatch_Cut17_16->Write();

      c_MSSMD_Cut6_1->cd();  h_MSSMD_Cut6_1->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]");  h_MSSMD_Cut6_1->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]");  h_MSSMD_Cut6_1->SetStats(0);  h_MSSMD_Cut6_1->Draw("COLZ TEXT");  h_MSSMD_Cut6_1->SetMinimum(0);  h_MSSMD_Cut6_1->SetMaximum(1);  c_MSSMD_Cut6_1->Write();
      c_MSSMD_Cut7_2->cd();  h_MSSMD_Cut7_2->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]");  h_MSSMD_Cut7_2->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]");  h_MSSMD_Cut7_2->SetStats(0);  h_MSSMD_Cut7_2->Draw("COLZ TEXT");  h_MSSMD_Cut7_2->SetMinimum(0);  h_MSSMD_Cut7_2->SetMaximum(1);  c_MSSMD_Cut7_2->Write();
      c_MSSMD_Cut8_3->cd();  h_MSSMD_Cut8_3->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]");  h_MSSMD_Cut8_3->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]");  h_MSSMD_Cut8_3->SetStats(0);  h_MSSMD_Cut8_3->Draw("COLZ TEXT");  h_MSSMD_Cut8_3->SetMinimum(0);  h_MSSMD_Cut8_3->SetMaximum(1);  c_MSSMD_Cut8_3->Write();
      c_MSSMD_Cut9_4->cd();  h_MSSMD_Cut9_4->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]");  h_MSSMD_Cut9_4->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]");  h_MSSMD_Cut9_4->SetStats(0);  h_MSSMD_Cut9_4->Draw("COLZ TEXT");  h_MSSMD_Cut9_4->SetMinimum(0);  h_MSSMD_Cut9_4->SetMaximum(1);  c_MSSMD_Cut9_4->Write();
      c_MSSMD_Cut10_4->cd(); h_MSSMD_Cut10_4->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]"); h_MSSMD_Cut10_4->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]"); h_MSSMD_Cut10_4->SetStats(0); h_MSSMD_Cut10_4->Draw("COLZ TEXT"); h_MSSMD_Cut10_4->SetMinimum(0); h_MSSMD_Cut10_4->SetMaximum(1); c_MSSMD_Cut10_4->Write();
      c_MSSMD_Cut11_4->cd(); h_MSSMD_Cut11_4->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]"); h_MSSMD_Cut11_4->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]"); h_MSSMD_Cut11_4->SetStats(0); h_MSSMD_Cut11_4->Draw("COLZ TEXT"); h_MSSMD_Cut11_4->SetMinimum(0); h_MSSMD_Cut11_4->SetMaximum(1); c_MSSMD_Cut11_4->Write();
      c_MSSMD_Cut12_5->cd(); h_MSSMD_Cut12_5->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]"); h_MSSMD_Cut12_5->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]"); h_MSSMD_Cut12_5->SetStats(0); h_MSSMD_Cut12_5->Draw("COLZ TEXT"); h_MSSMD_Cut12_5->SetMinimum(0); h_MSSMD_Cut12_5->SetMaximum(1); c_MSSMD_Cut12_5->Write();
      c_MSSMD_Cut13_5->cd(); h_MSSMD_Cut13_5->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]"); h_MSSMD_Cut13_5->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]"); h_MSSMD_Cut13_5->SetStats(0); h_MSSMD_Cut13_5->Draw("COLZ TEXT"); h_MSSMD_Cut13_5->SetMinimum(0); h_MSSMD_Cut13_5->SetMaximum(1); c_MSSMD_Cut13_5->Write();
      c_MSSMD_Cut14_5->cd(); h_MSSMD_Cut14_5->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]"); h_MSSMD_Cut14_5->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]"); h_MSSMD_Cut14_5->SetStats(0); h_MSSMD_Cut14_5->Draw("COLZ TEXT"); h_MSSMD_Cut14_5->SetMinimum(0); h_MSSMD_Cut14_5->SetMaximum(1); c_MSSMD_Cut14_5->Write();
      c_MSSMD_Cut15_5->cd(); h_MSSMD_Cut15_5->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]"); h_MSSMD_Cut15_5->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]"); h_MSSMD_Cut15_5->SetStats(0); h_MSSMD_Cut15_5->Draw("COLZ TEXT"); h_MSSMD_Cut15_5->SetMinimum(0); h_MSSMD_Cut15_5->SetMaximum(1); c_MSSMD_Cut15_5->Write();
      c_MSSMD_Cut16_5->cd(); h_MSSMD_Cut16_5->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]"); h_MSSMD_Cut16_5->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]"); h_MSSMD_Cut16_5->SetStats(0); h_MSSMD_Cut16_5->Draw("COLZ TEXT"); h_MSSMD_Cut16_5->SetMinimum(0); h_MSSMD_Cut16_5->SetMaximum(1); c_MSSMD_Cut16_5->Write();
      c_MSSMD_Cut17_5->cd(); h_MSSMD_Cut17_5->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]"); h_MSSMD_Cut17_5->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]"); h_MSSMD_Cut17_5->SetStats(0); h_MSSMD_Cut17_5->Draw("COLZ TEXT"); h_MSSMD_Cut17_5->SetMinimum(0); h_MSSMD_Cut17_5->SetMaximum(1); c_MSSMD_Cut17_5->Write();

      c_MSSMD_Cut10_9->cd();  h_MSSMD_Cut10_9->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]");  h_MSSMD_Cut10_9->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]");  h_MSSMD_Cut10_9->SetStats(0);  h_MSSMD_Cut10_9->Draw("COLZ TEXT");  h_MSSMD_Cut10_9->SetMinimum(0);  h_MSSMD_Cut10_9->SetMaximum(1);  c_MSSMD_Cut10_9->Write();
      c_MSSMD_Cut11_10->cd(); h_MSSMD_Cut11_10->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]"); h_MSSMD_Cut11_10->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]"); h_MSSMD_Cut11_10->SetStats(0); h_MSSMD_Cut11_10->Draw("COLZ TEXT"); h_MSSMD_Cut11_10->SetMinimum(0); h_MSSMD_Cut11_10->SetMaximum(1); c_MSSMD_Cut11_10->Write();

      c_MSSMD_Cut13_12->cd(); h_MSSMD_Cut13_12->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]"); h_MSSMD_Cut13_12->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]"); h_MSSMD_Cut13_12->SetStats(0); h_MSSMD_Cut13_12->Draw("COLZ TEXT"); h_MSSMD_Cut13_12->SetMinimum(0); h_MSSMD_Cut13_12->SetMaximum(1); c_MSSMD_Cut13_12->Write();
      c_MSSMD_Cut14_13->cd(); h_MSSMD_Cut14_13->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]"); h_MSSMD_Cut14_13->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]"); h_MSSMD_Cut14_13->SetStats(0); h_MSSMD_Cut14_13->Draw("COLZ TEXT"); h_MSSMD_Cut14_13->SetMinimum(0); h_MSSMD_Cut14_13->SetMaximum(1); c_MSSMD_Cut14_13->Write();
      c_MSSMD_Cut15_14->cd(); h_MSSMD_Cut15_14->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]"); h_MSSMD_Cut15_14->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]"); h_MSSMD_Cut15_14->SetStats(0); h_MSSMD_Cut15_14->Draw("COLZ TEXT"); h_MSSMD_Cut15_14->SetMinimum(0); h_MSSMD_Cut15_14->SetMaximum(1); c_MSSMD_Cut15_14->Write();
      c_MSSMD_Cut16_15->cd(); h_MSSMD_Cut16_15->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]"); h_MSSMD_Cut16_15->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]"); h_MSSMD_Cut16_15->SetStats(0); h_MSSMD_Cut16_15->Draw("COLZ TEXT"); h_MSSMD_Cut16_15->SetMinimum(0); h_MSSMD_Cut16_15->SetMaximum(1); c_MSSMD_Cut16_15->Write();
      c_MSSMD_Cut17_16->cd(); h_MSSMD_Cut17_16->GetXaxis()->SetTitle("m_{#gamma_{D}} [GeV]"); h_MSSMD_Cut17_16->GetYaxis()->SetTitle("c#tau_{#gamma_{D}} [mm]"); h_MSSMD_Cut17_16->SetStats(0); h_MSSMD_Cut17_16->Draw("COLZ TEXT"); h_MSSMD_Cut17_16->SetMinimum(0); h_MSSMD_Cut17_16->SetMaximum(1); c_MSSMD_Cut17_16->Write();

    }//if MSSMD sample exists

  }//end at least one sample

  finalPlot.Close();

}//end analysis
