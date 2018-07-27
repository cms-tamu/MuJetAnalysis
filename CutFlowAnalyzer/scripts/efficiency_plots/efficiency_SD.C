#include <iostream>
#include <algorithm>    // std::max
#include "TMath.h"
#include <math.h>
#include "TEfficiency.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TSystemDirectory.h" 
#include "TChainElement.h"
#include "TLegend.h"
#include "TGraphAsymmErrors.h"
#include "TLine.h"
#include "TMultiGraph.h"
#include "TColor.h"
#include "TStyle.h"


///----Global Variables ----///
TFile *BAM = new TFile("Efficiency_Plots.root","RECREATE");

int my_canvas_x = 600;
int my_canvas_y = 600;

Float_t count_gam_A0[160][160];
Float_t count_rec_A0[160][160];
Float_t eff_A0[160][160];

Float_t count_gam_A1[160][160];
Float_t count_rec_A1[160][160];
Float_t eff_A1[160][160];

TString cms_title = "#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV"; // 1D eff
TString cms_title2 = "#scale[1.4]{#font[61]{CMS}}#font[52]{Simulation}                  13 TeV"; // 2D eff

TH1F *den_1D_A0_LXY = new TH1F("den_1D_A0_LXY", cms_title, 80, 0, 80);
TH1F *num_1D_A0_LXY = new TH1F("num_1D_A0_LXY", cms_title, 80, 0, 80);

TH1F *den_1D_A0_LZ = new TH1F("den_1D_A0_LZ", cms_title, 80, 0, 80);
TH1F *num_1D_A0_LZ = new TH1F("num_1D_A0_LZ", cms_title, 80, 0, 80);

TH1F *den_1D_A1_LXY = new TH1F("den_1D_A1_LXY", cms_title, 80, 0, 80);
TH1F *num_1D_A1_LXY = new TH1F("num_1D_A1_LXY", cms_title, 80, 0, 80);

TH1F *den_1D_A1_LZ = new TH1F("den_1D_A1_LZ", cms_title, 80, 0, 80);
TH1F *num_1D_A1_LZ = new TH1F("num_1D_A1_LZ", cms_title, 80, 0, 80);

TH1F *dR_A0 = new TH1F("dR_A0", "dR_A0", 100, 0, 1);
TH1F *dR_A1 = new TH1F("dR_A1", "dR_A1", 100, 0, 1);

TH1F *dPhi_Plot = new TH1F("dPhi_A0", "dPhi_A0", 1400, -7, 7);

TH1F *den_1D_A1_pT = new TH1F("den_1D_A1_pT", cms_title, 40, 0, 120);
TH1F *num_1D_A1_pT = new TH1F("num_1D_A1_pT", cms_title, 40, 0, 120);

TH1F *den_1D_A0_pT = new TH1F("den_1D_A0_pT", cms_title, 40, 0, 120);
TH1F *num_1D_A0_pT = new TH1F("num_1D_A0_pT", cms_title, 40, 0, 120);

//Efficiency by eta -- <= 0.9

Float_t bins[] = {0, 2, 4, 6, 8, 10, 12, 16, 18, 20, 25, 30, 35, 40, 45, 50, 60, 80};
Int_t binnum = sizeof(bins)/sizeof(Float_t) - 1;

TH1F *den_LEp9_1D_A0_LXY = new TH1F("den_LEp9_1D_A0_LXY", cms_title, binnum, bins);
TH1F *num_LEp9_1D_A0_LXY = new TH1F("num_LEp9_1D_A0_LXY", cms_title, binnum, bins);

TH1F *den_LEp9_1D_A0_LZ = new TH1F("den_LEp9_1D_A0_LZ", cms_title, binnum, bins);
TH1F *num_LEp9_1D_A0_LZ = new TH1F("num_LEp9_1D_A0_LZ", cms_title, binnum, bins);

TH1F *den_LEp9_1D_A1_LXY = new TH1F("den_LEp9_1D_A1_LXY", cms_title, binnum, bins);
TH1F *num_LEp9_1D_A1_LXY = new TH1F("num_LEp9_1D_A1_LXY", cms_title, binnum, bins);

TH1F *den_LEp9_1D_A1_LZ = new TH1F("den_LEp9_1D_A1_LZ", cms_title, binnum, bins);
TH1F *num_LEp9_1D_A1_LZ = new TH1F("num_LEp9_1D_A1_LZ", cms_title, binnum, bins);

TH1F *den_LEp9_1D_A1_pT = new TH1F("den_LEp9_1D_A1_pT", cms_title, binnum, bins);
TH1F *num_LEp9_1D_A1_pT = new TH1F("num_LEp9_1D_A1_pT", cms_title, binnum, bins);

TH1F *den_LEp9_1D_A0_pT = new TH1F("den_LEp9_1D_A0_pT", cms_title, binnum, bins);
TH1F *num_LEp9_1D_A0_pT = new TH1F("num_LEp9_1D_A0_pT", cms_title, binnum, bins);

//Efficiency by eta -- > 0.9

TH1F *den_Gp9_1D_A0_LXY = new TH1F("den_Gp9_1D_A0_LXY", cms_title, binnum, bins);
TH1F *num_Gp9_1D_A0_LXY = new TH1F("num_Gp9_1D_A0_LXY", cms_title, binnum, bins);

TH1F *den_Gp9_1D_A0_LZ = new TH1F("den_Gp9_1D_A0_LZ", cms_title, binnum, bins);
TH1F *num_Gp9_1D_A0_LZ = new TH1F("num_Gp9_1D_A0_LZ", cms_title, binnum, bins);

TH1F *den_Gp9_1D_A1_LXY = new TH1F("den_Gp9_1D_A1_LXY", cms_title, binnum, bins);
TH1F *num_Gp9_1D_A1_LXY = new TH1F("num_Gp9_1D_A1_LXY", cms_title, binnum, bins);

TH1F *den_Gp9_1D_A1_LZ = new TH1F("den_Gp9_1D_A1_LZ", cms_title, binnum, bins);
TH1F *num_Gp9_1D_A1_LZ = new TH1F("num_Gp9_1D_A1_LZ", cms_title, binnum, bins);

TH1F *den_Gp9_1D_A1_pT = new TH1F("den_Gp9_1D_A1_pT", cms_title, binnum, bins);
TH1F *num_Gp9_1D_A1_pT = new TH1F("num_Gp9_1D_A1_pT", cms_title, binnum, bins);

TH1F *den_Gp9_1D_A0_pT = new TH1F("den_Gp9_1D_A0_pT", cms_title, binnum, bins);
TH1F *num_Gp9_1D_A0_pT = new TH1F("num_Gp9_1D_A0_pT", cms_title, binnum, bins);

//Efficiency by eta && event passed the trigger

TH1F *den_Trig_LEp9_1D_A0_LXY = new TH1F("den_Trig_LEp9_1D_A0_LXY", cms_title, binnum, bins);
TH1F *num_Trig_LEp9_1D_A0_LXY = new TH1F("num_Trig_LEp9_1D_A0_LXY", cms_title, binnum, bins);

TH1F *den_Trig_LEp9_1D_A0_LZ = new TH1F("den_Trig_LEp9_1D_A0_LZ", cms_title, binnum, bins);
TH1F *num_Trig_LEp9_1D_A0_LZ = new TH1F("num_Trig_LEp9_1D_A0_LZ", cms_title, binnum, bins);

TH1F *den_Trig_LEp9_1D_A1_LXY = new TH1F("den_Trig_LEp9_1D_A1_LXY", cms_title, binnum, bins);
TH1F *num_Trig_LEp9_1D_A1_LXY = new TH1F("num_Trig_LEp9_1D_A1_LXY", cms_title, binnum, bins);

TH1F *den_Trig_LEp9_1D_A1_LZ = new TH1F("den_Trig_LEp9_1D_A1_LZ", cms_title, binnum, bins);
TH1F *num_Trig_LEp9_1D_A1_LZ = new TH1F("num_Trig_LEp9_1D_A1_LZ", cms_title, binnum, bins);

TH1F *den_Trig_LEp9_1D_A1_pT = new TH1F("den_Trig_LEp9_1D_A1_pT", cms_title, binnum, bins);
TH1F *num_Trig_LEp9_1D_A1_pT = new TH1F("num_Trig_LEp9_1D_A1_pT", cms_title, binnum, bins);

TH1F *den_Trig_LEp9_1D_A0_pT = new TH1F("den_Trig_LEp9_1D_A0_pT", cms_title, binnum, bins);
TH1F *num_Trig_LEp9_1D_A0_pT = new TH1F("num_Trig_LEp9_1D_A0_pT", cms_title, binnum, bins);

//Efficiency by eta -- > 0.9

TH1F *den_Trig_Gp9_1D_A0_LXY = new TH1F("den_Trig_Gp9_1D_A0_LXY", cms_title, binnum, bins);
TH1F *num_Trig_Gp9_1D_A0_LXY = new TH1F("num_Trig_Gp9_1D_A0_LXY", cms_title, binnum, bins);

TH1F *den_Trig_Gp9_1D_A0_LZ = new TH1F("den_Trig_Gp9_1D_A0_LZ", cms_title, binnum, bins);
TH1F *num_Trig_Gp9_1D_A0_LZ = new TH1F("num_Trig_Gp9_1D_A0_LZ", cms_title, binnum, bins);

TH1F *den_Trig_Gp9_1D_A1_LXY = new TH1F("den_Trig_Gp9_1D_A1_LXY", cms_title, binnum, bins);
TH1F *num_Trig_Gp9_1D_A1_LXY = new TH1F("num_Trig_Gp9_1D_A1_LXY", cms_title, binnum, bins);

TH1F *den_Trig_Gp9_1D_A1_LZ = new TH1F("den_Trig_Gp9_1D_A1_LZ", cms_title, binnum, bins);
TH1F *num_Trig_Gp9_1D_A1_LZ = new TH1F("num_Trig_Gp9_1D_A1_LZ", cms_title, binnum, bins);

TH1F *den_Trig_Gp9_1D_A1_pT = new TH1F("den_Trig_Gp9_1D_A1_pT", cms_title, binnum, bins);
TH1F *num_Trig_Gp9_1D_A1_pT = new TH1F("num_Trig_Gp9_1D_A1_pT", cms_title, binnum, bins);

TH1F *den_Trig_Gp9_1D_A0_pT = new TH1F("den_Trig_Gp9_1D_A0_pT", cms_title, binnum, bins);
TH1F *num_Trig_Gp9_1D_A0_pT = new TH1F("num_Trig_Gp9_1D_A0_pT", cms_title, binnum, bins);

/*
//Efficiency by eta -- <= 0.9.  

TH1F *den_LEp9_1D_A0_mu0_LXY = new TH1F("den_LEp9_1D_A0_mu0_LXY", "mu0_LXY", binnum, bins);
TH1F *num_LEp9_1D_A0_mu0_LXY = new TH1F("num_LEp9_1D_A0_mu0_LXY", "mu0_LXY", binnum, bins);

TH1F *den_LEp9_1D_A0_mu0_LZ = new TH1F("den_LEp9_1D_A0_mu0_LZ", "mu0_LZ", binnum, bins);
TH1F *num_LEp9_1D_A0_mu0_LZ = new TH1F("num_LEp9_1D_A0_mu0_LZ", "mu0_LZ", binnum, bins);

TH1F *den_LEp9_1D_A0_mu1_LXY = new TH1F("den_LEp9_1D_A0_mu1_LXY", "mu1_LXY", binnum, bins);
TH1F *num_LEp9_1D_A0_mu1_LXY = new TH1F("num_LEp9_1D_A0_mu1_LXY", "mu1_LXY", binnum, bins);

TH1F *den_LEp9_1D_A0_mu1_LZ = new TH1F("den_LEp9_1D_A0_mu1_LZ", "mu1_LZ", binnum, bins);
TH1F *num_LEp9_1D_A0_mu1_LZ = new TH1F("num_LEp9_1D_A0_mu1_LZ", "mu1_LZ", binnum, bins);

TH1F *den_LEp9_1D_A0_mu1_pT = new TH1F("den_LEp9_1D_A0_mu1_pT", "mu1_pT", binnum, bins);
TH1F *num_LEp9_1D_A0_mu1_pT = new TH1F("num_LEp9_1D_A0_mu1_pT", "mu1_pT", binnum, bins);

TH1F *den_LEp9_1D_A0_mu0_pT = new TH1F("den_LEp9_1D_A0_mu0_pT", "mu0_pT", binnum, bins);
TH1F *num_LEp9_1D_A0_mu0_pT = new TH1F("num_LEp9_1D_A0_mu0_pT", "mu0_pT", binnum, bins);

//Efficiency by eta -- > 0.9

TH1F *den_Gp9_1D_A0_mu0_LXY = new TH1F("den_Gp9_1D_A0_mu0_LXY", "mu0_LXY", binnum, bins);
TH1F *num_Gp9_1D_A0_mu0_LXY = new TH1F("num_Gp9_1D_A0_mu0_LXY", "mu0_LXY", binnum, bins);

TH1F *den_Gp9_1D_A0_mu0_LZ = new TH1F("den_Gp9_1D_A0_mu0_LZ", "mu0_LZ", binnum, bins);
TH1F *num_Gp9_1D_A0_mu0_LZ = new TH1F("num_Gp9_1D_A0_mu0_LZ", "mu0_LZ", binnum, bins);

TH1F *den_Gp9_1D_A0_mu1_LXY = new TH1F("den_Gp9_1D_A0_mu1_LXY", "mu1_LXY", binnum, bins);
TH1F *num_Gp9_1D_A0_mu1_LXY = new TH1F("num_Gp9_1D_A0_mu1_LXY", "mu1_LXY", binnum, bins);

TH1F *den_Gp9_1D_A0_mu1_LZ = new TH1F("den_Gp9_1D_A0_mu1_LZ", "mu1_LZ", binnum, bins);
TH1F *num_Gp9_1D_A0_mu1_LZ = new TH1F("num_Gp9_1D_A0_mu1_LZ", "mu1_LZ", binnum, bins);

TH1F *den_Gp9_1D_A0_mu1_pT = new TH1F("den_Gp9_1D_A0_mu1_pT", "mu1_pT", binnum, bins);
TH1F *num_Gp9_1D_A0_mu1_pT = new TH1F("num_Gp9_1D_A0_mu1_pT", "mu1_pT", binnum, bins);

TH1F *den_Gp9_1D_A0_mu0_pT = new TH1F("den_Gp9_1D_A0_mu0_pT", "mu0_pT", binnum, bins);
TH1F *num_Gp9_1D_A0_mu0_pT = new TH1F("num_Gp9_1D_A0_mu0_pT", "mu0_pT", binnum, bins);

//Efficiency by eta && event passed the trigger

TH1F *den_Trig_LEp9_1D_A0_mu0_LXY = new TH1F("den_Trig_LEp9_1D_A0_mu0_LXY", "mu0_LXY", binnum, bins);
TH1F *num_Trig_LEp9_1D_A0_mu0_LXY = new TH1F("num_Trig_LEp9_1D_A0_mu0_LXY", "mu0_LXY", binnum, bins);

TH1F *den_Trig_LEp9_1D_A0_mu0_LZ = new TH1F("den_Trig_LEp9_1D_A0_mu0_LZ", "mu0_LZ", binnum, bins);
TH1F *num_Trig_LEp9_1D_A0_mu0_LZ = new TH1F("num_Trig_LEp9_1D_A0_mu0_LZ", "mu0_LZ", binnum, bins);

TH1F *den_Trig_LEp9_1D_A0_mu1_LXY = new TH1F("den_Trig_LEp9_1D_A0_mu1_LXY", "mu1_LXY", binnum, bins);
TH1F *num_Trig_LEp9_1D_A0_mu1_LXY = new TH1F("num_Trig_LEp9_1D_A0_mu1_LXY", "mu1_LXY", binnum, bins);

TH1F *den_Trig_LEp9_1D_A0_mu1_LZ = new TH1F("den_Trig_LEp9_1D_A0_mu1_LZ", "mu1_LZ", binnum, bins);
TH1F *num_Trig_LEp9_1D_A0_mu1_LZ = new TH1F("num_Trig_LEp9_1D_A0_mu1_LZ", "mu1_LZ", binnum, bins);

TH1F *den_Trig_LEp9_1D_A0_mu1_pT = new TH1F("den_Trig_LEp9_1D_A0_mu1_pT", "mu1_pT", binnum, bins);
TH1F *num_Trig_LEp9_1D_A0_mu1_pT = new TH1F("num_Trig_LEp9_1D_A0_mu1_pT", "mu1_pT", binnum, bins);

TH1F *den_Trig_LEp9_1D_A0_mu0_pT = new TH1F("den_Trig_LEp9_1D_A0_mu0_pT", "mu0_pT", binnum, bins);
TH1F *num_Trig_LEp9_1D_A0_mu0_pT = new TH1F("num_Trig_LEp9_1D_A0_mu0_pT", "mu0_pT", binnum, bins);

//Efficiency by eta -- > 0.9

TH1F *den_Trig_Gp9_1D_A0_mu0_LXY = new TH1F("den_Trig_Gp9_1D_A0_mu0_LXY", "mu0_LXY", binnum, bins);
TH1F *num_Trig_Gp9_1D_A0_mu0_LXY = new TH1F("num_Trig_Gp9_1D_A0_mu0_LXY", "mu0_LXY", binnum, bins);

TH1F *den_Trig_Gp9_1D_A0_mu0_LZ = new TH1F("den_Trig_Gp9_1D_A0_mu0_LZ", "mu0_LZ", binnum, bins);
TH1F *num_Trig_Gp9_1D_A0_mu0_LZ = new TH1F("num_Trig_Gp9_1D_A0_mu0_LZ", "mu0_LZ", binnum, bins);

TH1F *den_Trig_Gp9_1D_A0_mu1_LXY = new TH1F("den_Trig_Gp9_1D_A0_mu1_LXY", "mu1_LXY", binnum, bins);
TH1F *num_Trig_Gp9_1D_A0_mu1_LXY = new TH1F("num_Trig_Gp9_1D_A0_mu1_LXY", "mu1_LXY", binnum, bins);

TH1F *den_Trig_Gp9_1D_A0_mu1_LZ = new TH1F("den_Trig_Gp9_1D_A0_mu1_LZ", "mu1_LZ", binnum, bins);
TH1F *num_Trig_Gp9_1D_A0_mu1_LZ = new TH1F("num_Trig_Gp9_1D_A0_mu1_LZ", "mu1_LZ", binnum, bins);

TH1F *den_Trig_Gp9_1D_A0_mu1_pT = new TH1F("den_Trig_Gp9_1D_A0_mu1_pT", "mu1_pT", binnum, bins);
TH1F *num_Trig_Gp9_1D_A0_mu1_pT = new TH1F("num_Trig_Gp9_1D_A0_mu1_pT", "mu1_pT", binnum, bins);

TH1F *den_Trig_Gp9_1D_A0_mu0_pT = new TH1F("den_Trig_Gp9_1D_A0_mu0_pT", "mu0_pT", binnum, bins);
TH1F *num_Trig_Gp9_1D_A0_mu0_pT = new TH1F("num_Trig_Gp9_1D_A0_mu0_pT", "mu0_pT", binnum, bins);
*/



//Plots WITHOUT cuts
TH2F *dR_vs_dPhi = new TH2F("dR_vs_dPhi", "dR_vs_dPhi", 100, 0, 1, 800, -4, 4);

TH2F *dR_vs_dLxy = new TH2F("dR_vs_dLxy", "dR_vs_dLxy", 100, 0, 1, 80, 0, 80);
TH2F *dPhi_vs_dLxy = new TH2F("dPhi_vs_dLxy", "dPhi_vs_dLxy", 800, -4, 4, 80, 0, 80);

TH2F *dR_vs_dLz = new TH2F("dR_vs_dLz", "dR_vs_dLz", 100, 0, 1, 80, 0, 80);
TH2F *dPhi_vs_dLz = new TH2F("dPhi_vs_dLz", "dPhi_vs_dLz", 800, -4, 4, 80, 0, 80);


TH2F *dR_vs_pt = new TH2F("dR_vs_pt", "dR_vs_pt", 100, 0, 1, 40, 0, 120);
TH2F *pt_vs_dPhi = new TH2F("pt_vs_dPhi", "pt_vs_dPhi", 130,0,130, 800, -4, 4);

TH2F *pt_vs_dLxy = new TH2F("pt_vs_dLxy", "pt_vs_dLxy", 130,0,130, 80, 0, 80);
TH2F *pt_vs_dLz = new TH2F("pt_vs_dLz", "pt_vs_dLz", 130,0,130, 80, 0, 80);

void makeCounters(){

  for(int k=0;k<40;k++){
    for(int j=0;j<80;j++){
      count_gam_A0[k][j]=0.0;
      count_rec_A0[k][j]=0.0;
      eff_A0[k][j]=0.0;

      count_gam_A1[k][j]=0.0;
      count_rec_A1[k][j]=0.0;
      eff_A1[k][j]=0.0;
    }
  }
}

double My_dPhi (double phi1, double phi2) {
  double dPhi = phi1 - phi2;
  if (dPhi >  TMath::Pi()) dPhi -= 2*TMath::Pi();
  if (dPhi <  -TMath::Pi()) dPhi += 2*TMath::Pi();
  return fabs(dPhi);
}

int MatchRECOtoGENdimuons(double etaC, double phiC, double etaF, double phiF, double etaAC, double phiAC, double etaAF, double phiAF){
  int matchInt = -999;
  //match RECO C to GEN C 
  double dphi_CC = My_dPhi(phiC, phiAC);
  double deta_CC = etaC - etaAC;
  double dR_CC   = sqrt(dphi_CC*dphi_CC + deta_CC*deta_CC);
  //match RECO F to GEN F
  double dphi_FF = My_dPhi(phiF, phiAF);
  double deta_FF = etaF - etaAF;
  double dR_FF   = sqrt(dphi_FF*dphi_FF + deta_FF*deta_FF);
  //match RECO C to GEN F
  double dphi_CF = My_dPhi(phiC, phiAF);
  double deta_CF = etaC - etaAF;
  double dR_CF   = sqrt(dphi_CF*dphi_CF + deta_CF*deta_CF);
  //match RECO F to GEN C
  double dphi_FC = My_dPhi(phiF, phiAC);
  double deta_FC = etaF - etaAC;
  double dR_FC   = sqrt(dphi_FC*dphi_FC + deta_FC*deta_FC);

  if((dR_CC+dR_FF) <= (dR_CF+dR_FC)){
    matchInt = 0; //Then RECO C-> GEN C and RECO F->GEN F
  }else{
    matchInt = 1; //Then RECO C->GEN F and RECO F->GEN C
  }
  return matchInt;
}

void addfiles(TChain *ch, const TString dirname=".", const TString ext=".root")
{
  bool verbose(true);
  TSystemDirectory dir(dirname, dirname);
  TList *files = dir.GetListOfFiles();
  if (files) {
    if (verbose) std::cout << "Found files" << std::endl;
    TSystemFile *file;
    TString fname;
    TIter next(files);
    while ((file=(TSystemFile*)next())) {
      fname = file->GetName();
      if (verbose) std::cout << "found fname " << fname << std::endl;
      if (!file->IsDirectory() && fname.BeginsWith(ext)) {
	if (verbose) std::cout << "adding fname " << fname << std::endl;
	ch->Add(dirname + "/" + fname);
      }
    }
  }
}

template <class T>
void set_title_and_label_style(T* gr)
{
   gr->GetXaxis()->SetLabelFont(42);
   gr->GetXaxis()->SetLabelOffset(0.007);
   gr->GetXaxis()->SetLabelSize(0.05);
   gr->GetXaxis()->SetTitleSize(0.06);
   gr->GetXaxis()->SetTitleFont(42);

   gr->GetYaxis()->SetLabelFont(42);
   gr->GetYaxis()->SetLabelOffset(0.007);
   gr->GetYaxis()->SetLabelSize(0.05);
   gr->GetYaxis()->SetTitleSize(0.06);
   gr->GetYaxis()->SetTitleOffset(1.1);
   gr->GetYaxis()->SetTitleFont(42);

   // gr->GetZaxis()->SetLabelFont(42);
   // gr->GetZaxis()->SetLabelOffset(0.007);
}

void set_title_and_label_style(TGraphErrors* gr)
{
   gr->GetXaxis()->SetLabelFont(42);
   gr->GetXaxis()->SetLabelOffset(0.007);
   gr->GetXaxis()->SetLabelSize(0.05);
   gr->GetXaxis()->SetTitleSize(0.06);
   gr->GetXaxis()->SetTitleFont(42);

   gr->GetYaxis()->SetLabelFont(42);
   gr->GetYaxis()->SetLabelOffset(0.007);
   gr->GetYaxis()->SetLabelSize(0.05);
   gr->GetYaxis()->SetTitleSize(0.06);
   gr->GetYaxis()->SetTitleOffset(1.1);
   gr->GetYaxis()->SetTitleFont(42);
}

void set_title_and_label_style(TMultiGraph* gr)
{
   gr->GetHistogram()->GetXaxis()->SetLabelFont(42);
   gr->GetHistogram()->GetXaxis()->SetLabelOffset(0.007);
   gr->GetHistogram()->GetXaxis()->SetLabelSize(0.05);
   gr->GetHistogram()->GetXaxis()->SetTitleSize(0.06);
   gr->GetHistogram()->GetXaxis()->SetTitleFont(42);

   gr->GetHistogram()->GetYaxis()->SetLabelFont(42);
   gr->GetHistogram()->GetYaxis()->SetLabelOffset(0.007);
   gr->GetHistogram()->GetYaxis()->SetLabelSize(0.05);
   gr->GetHistogram()->GetYaxis()->SetTitleSize(0.06);
   gr->GetHistogram()->GetYaxis()->SetTitleOffset(1.1);
   gr->GetHistogram()->GetYaxis()->SetTitleFont(42);
}

void set_canvas_style(TCanvas* c)
{
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetTickx(1);
   c->SetTicky(1);
   c->SetLeftMargin(0.15);
   c->SetRightMargin(0.18);
   c->SetTopMargin(0.07);
   c->SetBottomMargin(0.17);
   c->SetFrameFillStyle(0);
   c->SetFrameBorderMode(0);
   c->SetFrameFillStyle(0);
   c->SetFrameBorderMode(0);
}

void set_canvas_style_tgraph(TCanvas* c)
{
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetTickx(1);
   c->SetTicky(1);
   c->SetLeftMargin(0.15);
   c->SetRightMargin(0.05);
   c->SetTopMargin(0.07);
   c->SetBottomMargin(0.15);
   c->SetFrameFillStyle(0);
   c->SetFrameBorderMode(0);
   c->SetFrameFillStyle(0);
   c->SetFrameBorderMode(0);
}

void create_eff_pergamD2DLxyLz(TString fileName){

gROOT->SetBatch(kTRUE);

  //  bool verbose(true);
  bool verbose(false);
  TString dirname(fileName);
  TChain* chain = new TChain("cutFlowAnalyzerPXBL3PXFL2/Events");
  TString ext("out_ana_");

  //Get the sample mass
  TString str = fileName;
  TString str2 = "DarkSUSY_mH_125_mN1_10_mGammaD_";
  Ssiz_t first = str.Index(str2);
  Ssiz_t last = str.Index("_cT_");
  TSubString mass_string = (str(first+str2.Length(),4));
  ///Get the sample cT
  TString str3 = "_cT_";
  TSubString cT_string = (str(last+str3.Length(),4));

  std::cout<<"  Dark photon mass   "<<mass_string<<"  ctau   "<<cT_string<<std::endl;
  // add files to the chain
  addfiles(chain, dirname, ext);

  TFile *file = TFile::Open("total_DarkSUSY_mH_125_mN1_10_mGammaD_" + mass_string + "_cT_" + cT_string + ".root","RECREATE"); 
  chain->CloneTree(-1,"fast"); 
  file->Write(); 
  delete file;
  
  return;
  Float_t ev_all[40]={0.0};

  Bool_t is1GenMu17;
  Bool_t is2GenMu8;
  Bool_t is3GenMu8;
  Bool_t is4GenMu8;

  Bool_t is1SelMu17;
  Bool_t is2SelMu8;
  Bool_t is3SelMu8;
  Bool_t is4SelMu8;

  Int_t npatm;


  Float_t genA0_Lxy;
  Float_t genA1_Lxy;

  Float_t genA0_Lz;
  Float_t genA1_Lz;

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

  Float_t genA0_px;
  Float_t genA0_py;
  Float_t genA1_px;
  Float_t genA1_py;

  Bool_t isDiMuonHLTFired;


  Float_t diMuonC_FittedVtx_m;
  Float_t diMuonC_FittedVtx_px;
  Float_t diMuonC_FittedVtx_py;
  Float_t diMuonC_FittedVtx_pz;
  Float_t diMuonC_FittedVtx_eta;
  Float_t diMuonC_FittedVtx_phi;
  Float_t diMuonC_FittedVtx_Lxy;
  Float_t diMuonC_FittedVtx_L;

  Float_t diMuonF_FittedVtx_m;
  Float_t diMuonF_FittedVtx_px;
  Float_t diMuonF_FittedVtx_py;
  Float_t diMuonF_FittedVtx_pz;
  Float_t diMuonF_FittedVtx_eta;
  Float_t diMuonF_FittedVtx_phi;
  Float_t diMuonF_FittedVtx_Lxy;
  Float_t diMuonF_FittedVtx_L;


  TObjArray *fileElements=chain->GetListOfFiles();
  TIter next(fileElements);
  TChainElement *chEl=0;

  while ((chEl=(TChainElement*)next())) {
    //    if (verbose) std::cout << "running on file " << chEl->GetTitle() << std::endl;
    //    std::cout << "running on file " << chEl->GetTitle() << std::endl;
    TFile* myfile = new TFile(dirname + chEl->GetTitle());
    if (!myfile) {
      if (verbose) std::cout << "File " << chEl->GetTitle() << " does not exist" << std::endl;
      continue;
    }

    if (verbose) std::cout << "Loading directory cutFlowAnalyzer" << std::endl;
    myfile->cd("cutFlowAnalyzerPXBL3PXFL2");

    TTree *t = (TTree*)myfile->Get("cutFlowAnalyzerPXBL3PXFL2/Events");
    if (!t) {
      if (verbose) std::cout << "Tree cutFlowAnalyzer/Events does not exist" << std::endl;
      continue;
    }

    if (verbose) cout<<"  Events  "<<t->GetEntries()<<endl;

    t->SetBranchStatus("*",0);
    t->SetBranchStatus("event",1);
    t->SetBranchStatus("is1GenMu17",1);
    t->SetBranchStatus("is2GenMu8",1);
    t->SetBranchStatus("is3GenMu8",1);
    t->SetBranchStatus("is4GenMu8",1);
    t->SetBranchStatus("is1SelMu17",1);
    t->SetBranchStatus("is2SelMu8",1);
    t->SetBranchStatus("is3SelMu8",1);
    t->SetBranchStatus("is4SelMu8",1);
    t->SetBranchStatus("isVertexOK",1);
    t->SetBranchStatus("genA0_Lxy",1); 
    t->SetBranchStatus("genA0_Lz",1);  
    t->SetBranchStatus("genA1_Lxy",1); 
    t->SetBranchStatus("genA1_Lz",1);  
    t->SetBranchStatus("selMu0_phi",1);
    t->SetBranchStatus("selMu1_phi",1);
    t->SetBranchStatus("selMu2_phi",1);
    t->SetBranchStatus("selMu3_phi",1);
    t->SetBranchStatus("selMu0_eta",1);
    t->SetBranchStatus("selMu1_eta",1);
    t->SetBranchStatus("selMu2_eta",1);
    t->SetBranchStatus("selMu3_eta",1);
    t->SetBranchStatus("genA1_phi",1);
    t->SetBranchStatus("genA1_eta",1);
    t->SetBranchStatus("genA0_phi",1);
    t->SetBranchStatus("genA0_eta",1);
    t->SetBranchStatus("diMuonC_FittedVtx_px",1); 
    t->SetBranchStatus("diMuonC_FittedVtx_py",1); 
    t->SetBranchStatus("diMuonF_FittedVtx_px",1); 
    t->SetBranchStatus("diMuonF_FittedVtx_py",1); 
    t->SetBranchStatus("genA0_px",1); 
    t->SetBranchStatus("genA0_py",1); 
    t->SetBranchStatus("genA1_px",1); 
    t->SetBranchStatus("genA1_py",1); 
    t->SetBranchStatus("isDiMuonHLTFired",1);  
    t->SetBranchStatus("diMuonF_FittedVtx_m",1);
    t->SetBranchStatus("diMuonF_FittedVtx_px",1); 
    t->SetBranchStatus("diMuonF_FittedVtx_py",1); 
    t->SetBranchStatus("diMuonF_FittedVtx_pz",1); 
    t->SetBranchStatus("diMuonF_FittedVtx_eta",1);
    t->SetBranchStatus("diMuonF_FittedVtx_phi",1);
    t->SetBranchStatus("diMuonF_FittedVtx_Lxy",1);
    t->SetBranchStatus("diMuonF_FittedVtx_L",1);
    t->SetBranchStatus("diMuonC_FittedVtx_m",1); 
    t->SetBranchStatus("diMuonC_FittedVtx_px",1);
    t->SetBranchStatus("diMuonC_FittedVtx_py",1);
    t->SetBranchStatus("diMuonC_FittedVtx_pz",1);
    t->SetBranchStatus("diMuonC_FittedVtx_eta",1);
    t->SetBranchStatus("diMuonC_FittedVtx_phi",1);
    t->SetBranchStatus("diMuonC_FittedVtx_Lxy",1);
    t->SetBranchStatus("diMuonC_FittedVtx_L",1);


    t->SetBranchAddress("event",&event);
    t->SetBranchAddress("is1GenMu17",&is1GenMu17);
    t->SetBranchAddress("is2GenMu8",&is2GenMu8);
    t->SetBranchAddress("is3GenMu8",&is3GenMu8);
    t->SetBranchAddress("is4GenMu8",&is4GenMu8);
    t->SetBranchAddress("is1SelMu17",&is1SelMu17);
    t->SetBranchAddress("is2SelMu8",&is2SelMu8);
    t->SetBranchAddress("is3SelMu8",&is3SelMu8);
    t->SetBranchAddress("is4SelMu8",&is4SelMu8);
    t->SetBranchAddress("isVertexOK",&isVtxOK);
    t->SetBranchAddress("genA0_Lxy", &genA0_Lxy);
    t->SetBranchAddress("genA0_Lz",  &genA0_Lz);
    t->SetBranchAddress("genA1_Lxy", &genA1_Lxy);
    t->SetBranchAddress("genA1_Lz",  &genA1_Lz);
    t->SetBranchAddress("selMu0_phi",&selMu0_phi);
    t->SetBranchAddress("selMu1_phi",&selMu1_phi);
    t->SetBranchAddress("selMu2_phi",&selMu2_phi);
    t->SetBranchAddress("selMu3_phi",&selMu3_phi);
    t->SetBranchAddress("selMu0_eta",&selMu0_eta);
    t->SetBranchAddress("selMu1_eta",&selMu1_eta);
    t->SetBranchAddress("selMu2_eta",&selMu2_eta);
    t->SetBranchAddress("selMu3_eta",&selMu3_eta);
    t->SetBranchAddress("genA1_phi",&genA1_phi);
    t->SetBranchAddress("genA1_eta",&genA1_eta);
    t->SetBranchAddress("genA0_phi",&genA0_phi);
    t->SetBranchAddress("genA0_eta",&genA0_eta);
    t->SetBranchAddress("diMuonC_FittedVtx_px", &diMuonC_FittedVtx_px);
    t->SetBranchAddress("diMuonC_FittedVtx_py", &diMuonC_FittedVtx_py);
    t->SetBranchAddress("diMuonF_FittedVtx_px", &diMuonF_FittedVtx_px);
    t->SetBranchAddress("diMuonF_FittedVtx_py", &diMuonF_FittedVtx_py);
    t->SetBranchAddress("genA0_px", & genA0_px);
    t->SetBranchAddress("genA0_py", & genA0_py);
    t->SetBranchAddress("genA1_px", & genA1_px);
    t->SetBranchAddress("genA1_py", & genA1_py);
    t->SetBranchAddress("isDiMuonHLTFired",               &isDiMuonHLTFired);
    t->SetBranchAddress("diMuonF_FittedVtx_m", &diMuonF_FittedVtx_m);
    t->SetBranchAddress("diMuonF_FittedVtx_px", &diMuonF_FittedVtx_px);
    t->SetBranchAddress("diMuonF_FittedVtx_py", &diMuonF_FittedVtx_py);
    t->SetBranchAddress("diMuonF_FittedVtx_pz", &diMuonF_FittedVtx_pz);
    t->SetBranchAddress("diMuonF_FittedVtx_eta",&diMuonF_FittedVtx_eta);
    t->SetBranchAddress("diMuonF_FittedVtx_phi",&diMuonF_FittedVtx_phi);
    t->SetBranchAddress("diMuonF_FittedVtx_Lxy",&diMuonF_FittedVtx_Lxy);
    t->SetBranchAddress("diMuonF_FittedVtx_L",&diMuonF_FittedVtx_L);
    t->SetBranchAddress("diMuonC_FittedVtx_m", &diMuonC_FittedVtx_m);
    t->SetBranchAddress("diMuonC_FittedVtx_px", &diMuonC_FittedVtx_px);
    t->SetBranchAddress("diMuonC_FittedVtx_py", &diMuonC_FittedVtx_py);
    t->SetBranchAddress("diMuonC_FittedVtx_pz", &diMuonC_FittedVtx_pz);
    t->SetBranchAddress("diMuonC_FittedVtx_eta",&diMuonC_FittedVtx_eta);
    t->SetBranchAddress("diMuonC_FittedVtx_phi",&diMuonC_FittedVtx_phi);
    t->SetBranchAddress("diMuonC_FittedVtx_Lxy",&diMuonC_FittedVtx_Lxy);
    t->SetBranchAddress("diMuonC_FittedVtx_L",&diMuonC_FittedVtx_L);

    Int_t nentries = t->GetEntries();


    //    Float_t bin_edges[41]={0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,78,80};
    Float_t bin_edges[81]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80};

    //    Float_t bin_edges[161]={0.,0.5,1.,1.5,2.,2.5,3.,3.5,4.,4.5,5.,5.5,6.,6.5,7.,7.5,8.,8.5,9.,9.5,10.,10.5,11.,11.5,12.,12.5,13.,13.5,14.,14.5,15.,15.5,16.,16.5,17.,17.5,18.,18.5,19.,19.5,20.,20.5,21.,21.5,22.,22.5,23.,23.5,24.,24.5,25.,25.5,26.,26.5,27.,27.5,28.,28.5,29.,29.5,30.,30.5,31.,31.5,32.,32.5,33.,33.5,34.,34.5,35.,35.5,36.,36.5,37.,37.5,38.,38.5,39.,39.5,40.,40.5,41.,41.5,42.,42.5,43.,43.5,44.,44.5,45.,45.5,46.,46.5,47.,47.5,48.,48.5,49.,49.5,50.,50.5,51.,51.5,52.,52.5,53.,53.5,54.,54.5,55.,55.5,56.,56.5,57.,57.5,58.,58.5,59.,59.5,60.,60.5,61.,61.5,62.,62.5,63.,63.5,64.,64.5,65.,65.5,66.,66.5,67.,67.5,68.,68.5,69.,69.5,70.,70.5,71.,71.5,72.,72.5,73.,73.5,74.,74.5,75.,75.5,76.,76.5,77.,77.5,78.,78.5,79.,79.5,80.};

    //    Float_t bin_edges_Lz[21]={0,4,8,12,16,20,24,28,32,36,40,44,48,52,56,60,64,68,72,76,80};
    Float_t bin_edges_Lz[41]={0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80};

    //    Float_t bin_edges_Lz[161]={0.,0.5,1.,1.5,2.,2.5,3.,3.5,4.,4.5,5.,5.5,6.,6.5,7.,7.5,8.,8.5,9.,9.5,10.,10.5,11.,11.5,12.,12.5,13.,13.5,14.,14.5,15.,15.5,16.,16.5,17.,17.5,18.,18.5,19.,19.5,20.,20.5,21.,21.5,22.,22.5,23.,23.5,24.,24.5,25.,25.5,26.,26.5,27.,27.5,28.,28.5,29.,29.5,30.,30.5,31.,31.5,32.,32.5,33.,33.5,34.,34.5,35.,35.5,36.,36.5,37.,37.5,38.,38.5,39.,39.5,40.,40.5,41.,41.5,42.,42.5,43.,43.5,44.,44.5,45.,45.5,46.,46.5,47.,47.5,48.,48.5,49.,49.5,50.,50.5,51.,51.5,52.,52.5,53.,53.5,54.,54.5,55.,55.5,56.,56.5,57.,57.5,58.,58.5,59.,59.5,60.,60.5,61.,61.5,62.,62.5,63.,63.5,64.,64.5,65.,65.5,66.,66.5,67.,67.5,68.,68.5,69.,69.5,70.,70.5,71.,71.5,72.,72.5,73.,73.5,74.,74.5,75.,75.5,76.,76.5,77.,77.5,78.,78.5,79.,79.5,80.};


    for(int k=0;k<nentries;k++){
      t->GetEntry(k);	
      //      std::cout<<"  Enter new event  "<<std::endl;
      if(true or isDiMuonHLTFired == 1){ //Make sure that the event fired the HLT
	//Loop for Efficienies
	//	std::cout<<"  Enter trigger  "<<std::endl;

	if(is4GenMu8==true){
	  //	  std::cout<<"  Four gen muons  "<<std::endl;

	  Float_t dphi_gD = My_dPhi(genA1_phi,genA0_phi);
	  dPhi_Plot->Fill(dphi_gD);
	  //if(fabs(dphi_gD)>=0) //What does this cut do?  Why do we want to make sure that the muons are back-to-back?
	  //if(fabs(dphi_gD)>2) //What does this cut do?  Why do we want to make sure that the muons are back-to-back?
	  //if(fabs(dphi_gD)>2.5) //What does this cut do?  Why do we want to make sure that the muons are back-to-back?

	  //This begins the loop for A0
	  //	  if(fabs(genA0_Lz) <= 46.5){ //second pixel endcap
	  //	    if(genA0_Lxy <= 11.0){ //third tracker barrel
	  if(fabs(genA0_Lz) <= 80){ //second pixel endcap
	    if(genA0_Lxy <= 80){ //third tracker barrel
	      //	      std::cout<<"  Fiducial  "<<std::endl;

	      for(int n=0;n<40;n++){
		if(fabs(genA0_Lz)>bin_edges_Lz[n] && fabs(genA0_Lz)<bin_edges_Lz[n+1]){
		  for(int m=0;m<80;m++){
		    if(genA0_Lxy>bin_edges[m] && genA0_Lxy<bin_edges[m+1]){
		      count_gam_A0[n][m]++;
		      den_1D_A0_LXY->Fill(genA0_Lxy);
		      den_1D_A0_LZ->Fill(genA0_Lz);

		      double denpt = sqrt(genA0_px*genA0_px + genA0_py*genA0_py);
		      den_1D_A0_pT->Fill(denpt);
		      if(abs(genA0_eta) <= 0.9){
			den_LEp9_1D_A0_pT->Fill(denpt);
			den_LEp9_1D_A0_LXY->Fill(genA0_Lxy);
			den_LEp9_1D_A0_LZ->Fill(genA0_Lz);
			if(isDiMuonHLTFired){
			  den_Trig_LEp9_1D_A0_pT->Fill(denpt);
			  den_Trig_LEp9_1D_A0_LXY->Fill(genA0_Lxy);
			  den_Trig_LEp9_1D_A0_LZ->Fill(genA0_Lz);
			}


		      }else{
			den_Gp9_1D_A0_pT->Fill(denpt);
			den_Gp9_1D_A0_LXY->Fill(genA0_Lxy);
			den_Gp9_1D_A0_LZ->Fill(genA0_Lz);
			if(isDiMuonHLTFired){
			  den_Trig_Gp9_1D_A0_pT->Fill(denpt);
			  den_Trig_Gp9_1D_A0_LXY->Fill(genA0_Lxy);
			  den_Trig_Gp9_1D_A0_LZ->Fill(genA0_Lz);
			}
		      }

		      npatm = 0;
		      if(selMu0_eta != -100) npatm++;
		      if(selMu1_eta != -100) npatm++;
		      if(selMu2_eta != -100) npatm++;
		      if(selMu3_eta != -100) npatm++;

		      /// Individual muon efficiencies                                                
		      /*	if(abs(genA0_eta) <= 0.9)
				if(sqrt(My_dPhi(selMu0_phi,genA0_phi)*My_dPhi(selMu0_phi,genA0_phi) + (selMu0_eta - genA0_eta)*(selMu0_eta - genA0Mu0_eta)) < 0.5) num_LEp9_1D_A0_mu0_LXY->Fill(genA0_Lxy); num_LEp9_1D_A0_mu0_LZ->Fill(genA0_Lz);
				else


		      */
		      ///	
		      if(npatm>=2 && is2SelMu8){
			Float_t dR1=0.0;
			Float_t dphi1=0.0;
			Float_t deta1=0.0;

			Int_t match_mu=0;

			//This method matches RECO muons to GEN dark photons.  This is probably not the best way to do the matching.
			//I should do matching as I normally do in my updated method
			//checkpoint


			for(int j=0;j<npatm;j++){

			  if(j==0){ dphi1 = My_dPhi(selMu0_phi,genA0_phi); deta1 = selMu0_eta - genA0_eta;}
			  if(j==1){ dphi1 = My_dPhi(selMu1_phi,genA0_phi); deta1 = selMu1_eta - genA0_eta;}
			  if(j==2){ dphi1 = My_dPhi(selMu2_phi,genA0_phi); deta1 = selMu2_eta - genA0_eta;}
			  if(j==3){ dphi1 = My_dPhi(selMu3_phi,genA0_phi); deta1 = selMu3_eta - genA0_eta;}

			  dR1 = sqrt(dphi1*dphi1+deta1*deta1);
			  dR_A0->Fill(dR1);
			  if(dR1<0.5) match_mu++;
			}
			if(match_mu>=2)   {
			  count_rec_A0[n][m]++;
			  num_1D_A0_LXY->Fill(genA0_Lxy);
			  num_1D_A0_LZ->Fill(genA0_Lz);
			  double numpt = sqrt(genA0_px*genA0_px + genA0_py*genA0_py);
			  num_1D_A0_pT->Fill(numpt);

			  if(abs(genA0_eta) <= 0.9){
			    num_LEp9_1D_A0_pT->Fill(numpt);
			    num_LEp9_1D_A0_LXY->Fill(genA0_Lxy);
			    num_LEp9_1D_A0_LZ->Fill(genA0_Lz);

			    if(isDiMuonHLTFired){
			      num_Trig_LEp9_1D_A0_pT->Fill(numpt);
			      num_Trig_LEp9_1D_A0_LXY->Fill(genA0_Lxy);
			      num_Trig_LEp9_1D_A0_LZ->Fill(genA0_Lz);
			    }

			  }else{
			    num_Gp9_1D_A0_pT->Fill(numpt);
			    num_Gp9_1D_A0_LXY->Fill(genA0_Lxy);
			    num_Gp9_1D_A0_LZ->Fill(genA0_Lz);
			    if(isDiMuonHLTFired){
			      num_Trig_Gp9_1D_A0_pT->Fill(numpt);
			      num_Trig_Gp9_1D_A0_LXY->Fill(genA0_Lxy);
			      num_Trig_Gp9_1D_A0_LZ->Fill(genA0_Lz);
			    }
			  }

			}
		      }
		    }
		  }
		}
	      }
	    }//A0 Lxy
	  }//A0 Lz
	  //This begins the loop for A1
	  //	  if(fabs(genA1_Lz) <= 46.5){ //Second pixel endcap
	  //	    if(genA1_Lxy <= 11.0){ //Third tracker barrel
	  if(fabs(genA1_Lz) <= 80){ //Second pixel endcap
	    if(genA1_Lxy <= 80){ //Third tracker barrel
	      for(int n=0;n<40;n++){
		if(fabs(genA1_Lz)>bin_edges_Lz[n] && fabs(genA1_Lz)<bin_edges_Lz[n+1]){

		  for(int m=0;m<80;m++){
		    if(genA1_Lxy>bin_edges[m] && genA1_Lxy<bin_edges[m+1]){
		      count_gam_A1[n][m]++;
		      den_1D_A1_LXY->Fill(genA1_Lxy);
		      den_1D_A1_LZ->Fill(genA1_Lz);

		      double denpt = sqrt(genA1_px*genA1_px + genA1_py*genA1_py);
		      den_1D_A1_pT->Fill(denpt);
		      if(abs(genA0_eta) <= 0.9){
			den_LEp9_1D_A1_pT->Fill(denpt);
			den_LEp9_1D_A1_LXY->Fill(genA1_Lxy);
			den_LEp9_1D_A1_LZ->Fill(genA1_Lz);
			if(isDiMuonHLTFired){
			  den_Trig_LEp9_1D_A1_pT->Fill(denpt);
			  den_Trig_LEp9_1D_A1_LXY->Fill(genA1_Lxy);
			  den_Trig_LEp9_1D_A1_LZ->Fill(genA1_Lz);

			}

		      }else{
			den_Gp9_1D_A1_pT->Fill(denpt);
			den_Gp9_1D_A1_LXY->Fill(genA1_Lxy);
			den_Gp9_1D_A1_LZ->Fill(genA1_Lz);
			if(isDiMuonHLTFired){
			  den_Trig_Gp9_1D_A1_pT->Fill(denpt);
			  den_Trig_Gp9_1D_A1_LXY->Fill(genA1_Lxy);
			  den_Trig_Gp9_1D_A1_LZ->Fill(genA1_Lz);
			}
		      }
		      npatm = 0;
		      if(selMu0_eta != -100) npatm++;
		      if(selMu1_eta != -100) npatm++;
		      if(selMu2_eta != -100) npatm++;
		      if(selMu3_eta != -100) npatm++;

		      if(npatm>=2 && is2SelMu8){
			Float_t dR1=0.0;
			Float_t dphi1=0.0;
			Float_t deta1=0.0;

			Int_t match_mu=0;
			//checkpoint
			for(int j=0;j<npatm;j++){	

			  if(j==0){ dphi1 = My_dPhi(selMu0_phi,genA1_phi); deta1 = selMu0_eta - genA1_eta;}
			  if(j==1){ dphi1 = My_dPhi(selMu1_phi,genA1_phi); deta1 = selMu1_eta - genA1_eta;}
			  if(j==2){ dphi1 = My_dPhi(selMu2_phi,genA1_phi); deta1 = selMu2_eta - genA1_eta;}
			  if(j==3){ dphi1 = My_dPhi(selMu3_phi,genA1_phi); deta1 = selMu3_eta - genA1_eta;}

			  dR1 = sqrt(dphi1*dphi1+deta1*deta1);
			  dR_A1->Fill(dR1);
			  if(dR1<0.5) match_mu++;
			}
			if(match_mu>=2) {
			  count_rec_A1[n][m]++;
			  num_1D_A1_LXY->Fill(genA1_Lxy);
			  num_1D_A1_LZ->Fill(genA1_Lz);
			  double numpt = sqrt(genA1_px*genA1_px + genA1_py*genA1_py);
			  num_1D_A1_pT->Fill(numpt);
			  if(abs(genA0_eta) <= 0.9){
			    num_LEp9_1D_A1_pT->Fill(numpt);
			    num_LEp9_1D_A1_LXY->Fill(genA1_Lxy);
			    num_LEp9_1D_A1_LZ->Fill(genA1_Lz);
			    if(isDiMuonHLTFired){
			      num_Trig_LEp9_1D_A1_pT->Fill(numpt);
			      num_Trig_LEp9_1D_A1_LXY->Fill(genA1_Lxy);
			      num_Trig_LEp9_1D_A1_LZ->Fill(genA1_Lz);
			    }

			  }else{
			    num_Gp9_1D_A1_pT->Fill(numpt);
			    num_Gp9_1D_A1_LXY->Fill(genA1_Lxy);
			    num_Gp9_1D_A1_LZ->Fill(genA1_Lz);
			    if(isDiMuonHLTFired){
			      num_Trig_Gp9_1D_A1_pT->Fill(numpt);
			      num_Trig_Gp9_1D_A1_LXY->Fill(genA1_Lxy);
			      num_Trig_Gp9_1D_A1_LZ->Fill(genA1_Lz);
			    }
			  }

			}

		      }
		    }
		  }
		}
	      }

	    } //A1 Lxy
	  } //A1 Lz
	}//4Gen mu

	//Rather unnecessary extra loop for distributions.
	//{{{
	if(is4GenMu8==true){
	  Float_t dphi_gD = My_dPhi(genA1_phi,genA0_phi);
	  //if(fabs(dphi_gD)>2.5) 
	  for(int n=0;n<20;n++){
	    if(fabs(genA0_Lz)>bin_edges_Lz[n] && fabs(genA0_Lz)<bin_edges_Lz[n+1]){
	      for(int m=0;m<40;m++){
		if(genA0_Lxy>bin_edges[m] && genA0_Lxy<bin_edges[m+1]){

		  npatm = 0;
		  if(selMu0_eta != -100) npatm++;
		  if(selMu1_eta != -100) npatm++;
		  if(selMu2_eta != -100) npatm++;
		  if(selMu3_eta != -100) npatm++;
		  if(npatm>=2 && is2SelMu8){
		    Float_t dR1=0.0;
		    Float_t dphi1=0.0;
		    Float_t deta1=0.0;

		    Int_t match_mu=0;
		    //checkpoint
		    for(int j=0;j<npatm;j++){

		      if(j==0){ dphi1 = My_dPhi(selMu0_phi,genA0_phi); deta1 = selMu0_eta - genA0_eta;}
		      if(j==1){ dphi1 = My_dPhi(selMu1_phi,genA0_phi); deta1 = selMu1_eta - genA0_eta;}
		      if(j==2){ dphi1 = My_dPhi(selMu2_phi,genA0_phi); deta1 = selMu2_eta - genA0_eta;}
		      if(j==3){ dphi1 = My_dPhi(selMu3_phi,genA0_phi); deta1 = selMu3_eta - genA0_eta;}

		      dR1 = sqrt(dphi1*dphi1+deta1*deta1);
		      //if(dR1<0.5) match_mu++;
		      match_mu++;
		      dR_vs_dPhi->Fill(dR1, dphi_gD);
		      dR_vs_pt->Fill(dR1, sqrt(genA0_px*genA0_px + genA0_py*genA0_py));
		    }
		    if(match_mu>=2)   {
		      dR_vs_dLxy->Fill(dR1, genA0_Lxy);
		      dPhi_vs_dLxy->Fill(dphi_gD, genA0_Lxy);

		      dR_vs_dLz->Fill(dR1, genA0_Lz);
		      dPhi_vs_dLz->Fill(dphi_gD, genA0_Lz);

		      pt_vs_dPhi->Fill(sqrt(genA0_px*genA0_px + genA0_py*genA0_py),dphi_gD);

		      pt_vs_dLxy->Fill(sqrt(genA0_px*genA0_px + genA0_py*genA0_py),genA0_Lxy);
		      pt_vs_dLz->Fill(sqrt(genA0_px*genA0_px + genA0_py*genA0_py), genA0_Lz);
		    }
		  }
		}
	      }
	    }
	  }


	  for(int n=0;n<20;n++){
	    if(fabs(genA1_Lz)>bin_edges_Lz[n] && fabs(genA1_Lz)<bin_edges_Lz[n+1]){

	      for(int m=0;m<40;m++){
		if(genA1_Lxy>bin_edges[m] && genA1_Lxy<bin_edges[m+1]){

		  npatm = 0;
		  if(selMu0_eta != -100) npatm++;
		  if(selMu1_eta != -100) npatm++;
		  if(selMu2_eta != -100) npatm++;
		  if(selMu3_eta != -100) npatm++;

		  if(npatm>=2 && is2SelMu8){
		    Float_t dR1=0.0;
		    Float_t dphi1=0.0;
		    Float_t deta1=0.0;

		    Int_t match_mu=0;
		    //checkpoint
		    for(int j=0;j<npatm;j++){	

		      if(j==0){ dphi1 = My_dPhi(selMu0_phi,genA1_phi); deta1 = selMu0_eta - genA1_eta;}
		      if(j==1){ dphi1 = My_dPhi(selMu1_phi,genA1_phi); deta1 = selMu1_eta - genA1_eta;}
		      if(j==2){ dphi1 = My_dPhi(selMu2_phi,genA1_phi); deta1 = selMu2_eta - genA1_eta;}
		      if(j==3){ dphi1 = My_dPhi(selMu3_phi,genA1_phi); deta1 = selMu3_eta - genA1_eta;}

		      dR1 = sqrt(dphi1*dphi1+deta1*deta1);
		      //if(dR1<0.5) match_mu++;
		      match_mu++;
		      dR_vs_dPhi->Fill(dR1, dphi_gD);
		      dR_vs_pt->Fill(dR1, sqrt(genA1_px*genA1_px + genA1_py*genA1_py));

		    }
		    if(match_mu>=2) {
		      dR_vs_dLxy->Fill(dR1, genA1_Lxy);
		      dPhi_vs_dLxy->Fill(dphi_gD, genA1_Lxy);

		      dR_vs_dLz->Fill(dR1, genA1_Lz);
		      dPhi_vs_dLz->Fill(dphi_gD, genA1_Lz);}
		    pt_vs_dPhi->Fill(sqrt(genA1_px*genA1_px + genA1_py*genA1_py) ,dphi_gD);
		    pt_vs_dLxy->Fill(sqrt(genA1_px*genA1_px + genA1_py*genA1_py),genA1_Lxy);
		    pt_vs_dLz->Fill(sqrt(genA1_px*genA1_px + genA1_py*genA1_py), genA1_Lz);


		  }
		}
	      }
	    }
	  }

	}
	//}}}

      }// HLT loop 
    } //for loop
    myfile->Close();
  } //While loop
} //Method loop


void makePlots(){

  TH2F *den_2D_A0 = new TH2F("den_2D_A0",cms_title2,40,0,80,80,0.0,80.0);
  TH2F *num_2D_A0 = new TH2F("num_2D_A0",cms_title2,40,0,80,80,0.0,80.0);

  TH2F *eff_2D_A0 = new TH2F("eff_2D_A0",cms_title2,40,0,80,80,0.0,80.0);
  TH2F *eff_2D_A1 = new TH2F("eff_2D_A1",cms_title2,40,0,80,80,0.0,80.0);


  for(int k=0;k<40;k++){
    for(int j=0;j<80;j++){

      num_2D_A0->SetBinContent(k+1,j+1,count_rec_A0[k][j]);

      den_2D_A0->SetBinContent(k+1,j+1,count_gam_A0[k][j]);

      if(count_gam_A0[k][j]!=0) eff_A0[k][j] = count_rec_A0[k][j]/(count_gam_A0[k][j]*1.0);
      if(count_rec_A0[k][j]==0 && count_gam_A0[k][j]!=0)   eff_A0[k][j] = 0.0001;

      // cout<<" efficiency A0   "<<eff_A0[k][j]<<endl;
      eff_2D_A0->SetBinContent(k+1,j+1,eff_A0[k][j]);


      if(count_gam_A1[k][j]!=0) eff_A1[k][j] = count_rec_A1[k][j]/(count_gam_A1[k][j]*1.0);
      if(count_rec_A1[k][j]==0 && count_gam_A1[k][j]!=0)   eff_A1[k][j] = 0.0001;

      // cout<<" efficiency A1   "<<eff_A1[k][j]<<endl;

      eff_2D_A1->SetBinContent(k+1,j+1,eff_A1[k][j]);
    }
  }



  TCanvas *effxy = new TCanvas("effxy", "effxy", my_canvas_x, my_canvas_y);
  set_canvas_style_tgraph(effxy);
  gStyle->SetTitleFontSize(0.07);
    gStyle->SetTitleStyle( 0 );
  gStyle->SetTitleAlign(13);
  gStyle->SetTitleX(0.);
  gStyle->SetTitleY(1.);
  gStyle->SetTitleW(1);
  gStyle->SetTitleH(0.058);
  gStyle->SetTitleBorderSize( 0 );
  
  gr1 = new TGraphAsymmErrors(num_1D_A0_LXY, den_1D_A0_LXY);
  gr1->SetTitle(cms_title);
  gr1->GetYaxis()->SetTitle("Efficiency");
  gr1->GetXaxis()->SetTitle("L_{xy} [cm]");
  gr1->SetMarkerColor(kRed);
  gr1->SetLineColor(kRed);
  gr1->SetMarkerStyle(25);
  gr1->SetMinimum(0);
  gr1->SetMaximum(1);
  gr1->Draw("ALP");

  gr0 = new TGraphAsymmErrors(num_1D_A1_LXY, den_1D_A1_LXY);
  gr0->SetMarkerColor(kBlue);
  gr0->SetLineColor(kBlue);
  gr0->SetMarkerStyle(22);
  gr0->Draw("P same");

  set_title_and_label_style(gr1);
  set_title_and_label_style(gr0);

  TLegend *leg = new TLegend(0.2,0.2,0.35,0.35);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetTextSize(0.05);
  leg->AddEntry(gr1,"#gamma_{D1}","LP");
  leg->AddEntry(gr0,"#gamma_{D2}","LP");
  leg->Draw("same");

  effxy->SaveAs("Efficiency_1D_LXY.pdf");
  effxy->SaveAs("Efficiency_1D_LXY.C");

  
  gr1->GetXaxis()->SetLimits(0,12);
  gr1->Draw("ALP");
  gr0->Draw("P same");
  leg->Draw("same");

  effxy->SaveAs("Efficiency_1D_LXY_0to12.pdf");
  effxy->SaveAs("Efficiency_1D_LXY_0to12.C");


  TCanvas *effz2 = new TCanvas("effz2", "effz2", my_canvas_x, my_canvas_y);
  set_canvas_style_tgraph(effz2);

  gStyle->SetTitleFontSize(0.07);
  gStyle->SetTitleStyle( 0 );
  gStyle->SetTitleAlign(13);
  gStyle->SetTitleX(0.);
  gStyle->SetTitleY(1.);
  gStyle->SetTitleW(1);
  gStyle->SetTitleH(0.058);
  gStyle->SetTitleBorderSize( 0 );

  gr2 = new TGraphAsymmErrors(num_1D_A0_LZ, den_1D_A0_LZ);
  gr2->SetMarkerColor(kRed);
  gr2->SetLineColor(kRed);
  gr2->SetTitle(cms_title);
  gr2->GetYaxis()->SetTitle("Efficiency");
  gr2->GetXaxis()->SetTitle("L_{z} [cm]");
  gr2->SetMarkerStyle(21);
  gr2->SetMinimum(0);
  gr2->SetMaximum(1);
  gr2->Draw("ALP");


  gr3 = new TGraphAsymmErrors(num_1D_A1_LZ, den_1D_A1_LZ);
  gr3->SetMarkerColor(kBlue);
  gr3->SetLineColor(kBlue);
  gr3->SetMarkerStyle(21);
  gr3->Draw("P same");

  set_title_and_label_style(gr2);
  set_title_and_label_style(gr3);

  leg->Draw("same");

  effz2->SaveAs("Efficiency_1D_Lz.pdf");
  effz2->SaveAs("Efficiency_1D_Lz.C");


  gr2->GetXaxis()->SetLimits(0,12);
  gr2->Draw("ALP");
  gr3->Draw("P same");
  leg->Draw("same");

  effz2->SaveAs("Efficiency_1D_Lz_0to12.pdf");
  effz2->SaveAs("Efficiency_1D_Lz_0to12.C");


  TCanvas *effpt = new TCanvas("effpt", "effpt", my_canvas_x, my_canvas_y);
  set_canvas_style_tgraph(effpt);

  gStyle->SetTitleFontSize(0.07);
  gStyle->SetTitleStyle( 0 );
  gStyle->SetTitleAlign(13);
  gStyle->SetTitleX(0.);
  gStyle->SetTitleY(1.);
  gStyle->SetTitleW(1);
  gStyle->SetTitleH(0.058);
  gStyle->SetTitleBorderSize( 0 );

  gr_eff = new TGraphAsymmErrors(num_1D_A0_pT, den_1D_A0_pT);
  gr_eff->SetMarkerColor(kRed);
  gr_eff->SetLineColor(kRed);
  gr_eff->SetTitle(cms_title);
  gr_eff->GetYaxis()->SetTitle("Efficiency");
  gr_eff->GetXaxis()->SetTitle("p_{T} [GeV]");
  gr_eff->SetMarkerStyle(21);
  set_title_and_label_style(gr_eff);
  gr_eff->Draw("ALP");

  gr_eff2 = new TGraphAsymmErrors(num_1D_A1_pT, den_1D_A1_pT);
  gr_eff2->SetMarkerColor(kBlue);
  gr_eff2->SetLineColor(kBlue);
  gr_eff2->SetMarkerStyle(21);
  gr_eff2->Draw("P same");

  set_title_and_label_style(gr_eff);
  set_title_and_label_style(gr_eff2);

  leg->Draw("same");
  effpt->SaveAs("Efficiency_vs_Gen_pT.pdf");
  effpt->SaveAs("Efficiency_vs_Gen_pT.C");

  //Efficiency by Eta plots
  TLine *pixel_1 = new TLine(4.0, 0, 4.0, 1);
  TLine *pixel_11 = new TLine(4.4, 0, 4.4, 1);

  TLine *pixel_2 = new TLine(6.9, 0, 6.9, 1);
  TLine *pixel_21 = new TLine(7.3, 0, 7.3, 1);

  TLine *pixel_3 = new TLine(9.8, 0,9.8, 1);
  TLine *pixel_31 = new TLine(10.2, 0,10.2, 1);

  TLine *pixel_endcap_1 = new TLine(34.5, 0, 34.5, 1);
  TLine *pixel_endcap_2 = new TLine(46.5, 0, 46.5, 1);

  TLine *tracker_innerbarrel = new TLine(23.9, 0, 23.9, 1); 
  TLine *tracker_outerbarrel = new TLine(60.5, 0, 60.5, 1);

  //Blue Lines
  int linestyle = 2;
  int linewidth = 2;
  pixel_1->SetLineStyle(linestyle);
  pixel_2->SetLineStyle(linestyle);
  pixel_3->SetLineStyle(linestyle);
  pixel_1->SetLineWidth(linewidth);
  pixel_2->SetLineWidth(linewidth);
  pixel_3->SetLineWidth(linewidth);
  pixel_1->SetLineColor(kBlue);
  pixel_2->SetLineColor(kBlue);
  pixel_3->SetLineColor(kBlue);

  pixel_endcap_1->SetLineStyle(linestyle);
  pixel_endcap_2->SetLineStyle(linestyle);
  pixel_endcap_1->SetLineWidth(linewidth);
  pixel_endcap_2->SetLineWidth(linewidth);
  pixel_endcap_1->SetLineColor(kBlue);
  pixel_endcap_2->SetLineColor(kBlue);

  //Green Lines
  tracker_innerbarrel->SetLineStyle(linestyle);
  tracker_outerbarrel->SetLineStyle(linestyle);
  tracker_innerbarrel->SetLineColor(kGreen+1);
  tracker_outerbarrel->SetLineColor(kGreen+1);
  tracker_innerbarrel->SetLineWidth(linewidth);
  tracker_outerbarrel->SetLineWidth(linewidth);

  TCanvas *eta_lxy = new TCanvas("eta_lxy", "eta_lxy", my_canvas_x, my_canvas_y);
  set_canvas_style_tgraph(eta_lxy);

  gStyle->SetTitleFontSize(0.07);
  gStyle->SetTitleStyle( 0 );
  gStyle->SetTitleAlign(13);
  gStyle->SetTitleX(0.);
  gStyle->SetTitleY(1.);
  gStyle->SetTitleW(1);
  gStyle->SetTitleH(0.058);
  gStyle->SetTitleBorderSize( 0 );

  TMultiGraph *mg_lxy = new TMultiGraph("",cms_title);
  gr_a0_le_lxy = new TGraphAsymmErrors(num_LEp9_1D_A0_LXY, den_LEp9_1D_A0_LXY);
  gr_a1_le_lxy = new TGraphAsymmErrors(num_LEp9_1D_A1_LXY, den_LEp9_1D_A1_LXY);
  gr_a1_g_lxy = new TGraphAsymmErrors(num_Gp9_1D_A1_LXY, den_Gp9_1D_A1_LXY);
  gr_a0_g_lxy = new TGraphAsymmErrors(num_Gp9_1D_A0_LXY, den_Gp9_1D_A0_LXY);

  gr_a0_le_lxy->SetMarkerColor(kRed);
  gr_a0_le_lxy->SetMarkerStyle(2);
  gr_a0_le_lxy->SetLineColor(kRed);
  gr_a0_le_lxy->SetLineStyle(1);
  mg_lxy->Add(gr_a0_le_lxy);

  gr_a0_g_lxy->SetMarkerColor(kRed);
  gr_a0_g_lxy->SetMarkerStyle(2);
  gr_a0_g_lxy->SetLineColor(kRed);
  gr_a0_g_lxy->SetLineStyle(2);
  mg_lxy->Add(gr_a0_g_lxy);

  gr_a1_le_lxy->SetMarkerColor(kBlack);
  gr_a1_le_lxy->SetMarkerStyle(2);
  gr_a1_le_lxy->SetLineColor(kBlack);
  gr_a1_le_lxy->SetLineStyle(1);
  mg_lxy->Add(gr_a1_le_lxy);

  gr_a1_g_lxy->SetMarkerColor(kBlack);
  gr_a1_g_lxy->SetMarkerStyle(2);
  gr_a1_g_lxy->SetLineColor(kBlack);
  gr_a1_g_lxy->SetLineStyle(2);
  mg_lxy->Add(gr_a1_g_lxy);

  set_title_and_label_style(gr_a0_le_lxy);
  set_title_and_label_style(gr_a1_le_lxy);
  set_title_and_label_style(gr_a1_g_lxy);
  set_title_and_label_style(gr_a0_g_lxy);

  TLegend *etaleg = new TLegend(0.5866762,0.2447257,0.7858166,0.4535865);
  etaleg->SetBorderSize(0);
  etaleg->SetFillColor(0);
  etaleg->SetTextSize(0.05);
  etaleg->SetFillStyle(0);
  etaleg->AddEntry(gr_a0_le_lxy,"|#eta_{#gamma D1}| #leq 0.9","L");
  etaleg->AddEntry(gr_a0_g_lxy, "|#eta_{#gamma D1}| > 0.9","L");
  etaleg->AddEntry(gr_a1_le_lxy,"|#eta_{#gamma D2}| #leq 0.9","L");
  etaleg->AddEntry(gr_a1_g_lxy, "|#eta_{#gamma D2}| > 0.9","L");
  mg_lxy->Draw("ALP");
  mg_lxy->GetXaxis()->SetTitle("L_{xy} [cm]");
  mg_lxy->GetYaxis()->SetTitle("Efficiency");
  mg_lxy->SetMinimum(0.);
  mg_lxy->SetMaximum(1.);
  etaleg->Draw("P same");
  set_title_and_label_style(mg_lxy);

  TLegend *etalegz = new TLegend(0.6389685,0.2447257,0.8381089,0.4535865);
  etalegz->SetBorderSize(0);
  etalegz->SetFillColor(0);
  etalegz->SetTextSize(0.05);
  etalegz->SetFillStyle(0);
  etalegz->AddEntry(gr_a0_le_lxy,"|#eta_{#gamma D1}| #leq 0.9","L");
  etalegz->AddEntry(gr_a0_g_lxy, "|#eta_{#gamma D1}| > 0.9","L");
  etalegz->AddEntry(gr_a1_le_lxy,"|#eta_{#gamma D2}| #leq 0.9","L");
  etalegz->AddEntry(gr_a1_g_lxy, "|#eta_{#gamma D2}| > 0.9","L");

  pixel_1->Draw("same");
  pixel_2->Draw("same");
  pixel_3->Draw("same");
  tracker_innerbarrel->Draw("same");
  tracker_outerbarrel->Draw("same");


  eta_lxy->SaveAs("EfficiencyByEta_vs_Lxy.pdf");
  eta_lxy->SaveAs("EfficiencyByEta_vs_Lxy.C");

  
  mg_lxy->GetXaxis()->SetLimits(0,12);
  mg_lxy->Draw("ALP");
  etaleg->Draw("same");
  pixel_1->Draw("same");
  pixel_2->Draw("same");
  pixel_3->Draw("same");
  tracker_innerbarrel->Draw("same");
  tracker_outerbarrel->Draw("same");

  effxy->SaveAs("EfficiencyByEta_1D_vs_Lxy_0to12.pdf");
  effxy->SaveAs("EfficiencyByEta_1D_vs_Lxy_0to12.C");



  cout << "Checkpoint 1" << endl;
  //eta_lxy->SaveAs("EfficiencyByEta_vs_Lxy.C");

  cout << "Checkpoint 2" << endl;

  TCanvas *eta_lz = new TCanvas("eta_lz", "eta_lz", my_canvas_x, my_canvas_y);
  set_canvas_style_tgraph(eta_lz);
  TMultiGraph *mg_lz = new TMultiGraph("",cms_title);

  gStyle->SetTitleFontSize(0.07);
  gStyle->SetTitleStyle( 0 );
  gStyle->SetTitleAlign(13);
  gStyle->SetTitleX(0.);
  gStyle->SetTitleY(1.);
  gStyle->SetTitleW(1);
  gStyle->SetTitleH(0.058);
  gStyle->SetTitleBorderSize( 0 );

  gr_a0_le_lz = new TGraphAsymmErrors(num_LEp9_1D_A0_LZ, den_LEp9_1D_A0_LZ);
  gr_a1_le_lz = new TGraphAsymmErrors(num_LEp9_1D_A1_LZ, den_LEp9_1D_A1_LZ);
  gr_a1_g_lz = new TGraphAsymmErrors(num_Gp9_1D_A1_LZ, den_Gp9_1D_A1_LZ);
  gr_a0_g_lz = new TGraphAsymmErrors(num_Gp9_1D_A0_LZ, den_Gp9_1D_A0_LZ);
  cout << "Checkpoint 3" << endl;

  set_title_and_label_style(gr_a0_le_lz);
  set_title_and_label_style(gr_a1_le_lz);
  set_title_and_label_style(gr_a1_g_lz);
  set_title_and_label_style(gr_a0_g_lz);

  gr_a0_le_lz->SetMarkerColor(kRed);
  gr_a0_le_lz->SetMarkerStyle(2);
  gr_a0_le_lz->SetLineColor(kRed);
  gr_a0_le_lz->SetLineStyle(1);

  gr_a0_g_lz->SetMarkerColor(kRed);
  gr_a0_g_lz->SetMarkerStyle(2);
  gr_a0_g_lz->SetLineColor(kRed);
  gr_a0_g_lz->SetLineStyle(2);

  gr_a1_le_lz->SetMarkerColor(kBlack);
  gr_a1_le_lz->SetMarkerStyle(2);
  gr_a1_le_lz->SetLineColor(kBlack);
  gr_a1_le_lz->SetLineStyle(1);

  gr_a1_g_lz->SetMarkerColor(kBlack);
  gr_a1_g_lz->SetMarkerStyle(2);
  gr_a1_g_lz->SetLineColor(kBlack);
  gr_a1_g_lz->SetLineStyle(2);

  mg_lz->Add(gr_a0_le_lz);
  mg_lz->Add(gr_a1_le_lz);
  mg_lz->Add(gr_a0_g_lz);
  mg_lz->Add(gr_a1_g_lz);

  cout << "Checkpoint 4" << endl;
  mg_lz->Draw("ALP");
  set_title_and_label_style(mg_lz);
  mg_lz->GetXaxis()->SetTitle("L_{z} [cm]");
  mg_lz->GetYaxis()->SetTitle("Efficiency");
  mg_lz->SetMinimum(0.);
  mg_lz->SetMaximum(1.);

  pixel_endcap_1->Draw("same");
  pixel_endcap_2->Draw("same");

  etalegz->Draw("same");
  eta_lz->SaveAs("EfficiencyByEta_vs_Lz.pdf");
  eta_lz->SaveAs("EfficiencyByEta_vs_Lz.C");



  mg_lz->GetXaxis()->SetLimits(0,12);
  mg_lz->Draw("ALP");
  etalegz->Draw("same");
  pixel_1->Draw("same");
  pixel_2->Draw("same");
  pixel_3->Draw("same");
  tracker_innerbarrel->Draw("same");
  tracker_outerbarrel->Draw("same");

  eta_lz->SaveAs("EfficiencyByEta_1D_vs_Lz_0to12.pdf");
  eta_lz->SaveAs("EfficiencyByEta_1D_vs_Lz_0to12.C");


  //Eta plots including Trigger

  TCanvas *eta_lxy_trig = new TCanvas("eta_lxy_trig", "eta_lxy_trig", my_canvas_x, my_canvas_y);
  set_canvas_style_tgraph(eta_lxy_trig);
  TMultiGraph *mg_lxy_trig = new TMultiGraph("",cms_title);

  gStyle->SetTitleFontSize(0.07);
  gStyle->SetTitleStyle( 0 );
  gStyle->SetTitleAlign(13);
  gStyle->SetTitleX(0.);
  gStyle->SetTitleY(1.);
  gStyle->SetTitleW(1);
  gStyle->SetTitleH(0.058);
  gStyle->SetTitleBorderSize( 0 );

  gr_a0_le_lxy_trig = new TGraphAsymmErrors(num_Trig_LEp9_1D_A0_LXY, den_Trig_LEp9_1D_A0_LXY);
  gr_a1_le_lxy_trig = new TGraphAsymmErrors(num_Trig_LEp9_1D_A1_LXY, den_Trig_LEp9_1D_A1_LXY);
  gr_a1_g_lxy_trig = new TGraphAsymmErrors(num_Trig_Gp9_1D_A1_LXY, den_Trig_Gp9_1D_A1_LXY);
  gr_a0_g_lxy_trig = new TGraphAsymmErrors(num_Trig_Gp9_1D_A0_LXY, den_Trig_Gp9_1D_A0_LXY);

  set_title_and_label_style(gr_a0_le_lxy_trig);
  set_title_and_label_style(gr_a1_le_lxy_trig);
  set_title_and_label_style(gr_a1_g_lxy_trig);
  set_title_and_label_style(gr_a0_g_lxy_trig);

  gr_a0_le_lxy_trig->SetMarkerColor(kRed);
  gr_a0_le_lxy_trig->SetMarkerStyle(2);
  gr_a0_le_lxy_trig->SetLineColor(kRed);
  gr_a0_le_lxy_trig->SetLineStyle(1);
  mg_lxy_trig->Add(gr_a0_le_lxy_trig);

  gr_a0_g_lxy_trig->SetMarkerColor(kRed);
  gr_a0_g_lxy_trig->SetMarkerStyle(2);
  gr_a0_g_lxy_trig->SetLineColor(kRed);
  gr_a0_g_lxy_trig->SetLineStyle(2);
  mg_lxy_trig->Add(gr_a0_g_lxy_trig);

  gr_a1_le_lxy_trig->SetMarkerColor(kBlack);
  gr_a1_le_lxy_trig->SetMarkerStyle(2);
  gr_a1_le_lxy_trig->SetLineColor(kBlack);
  gr_a1_le_lxy_trig->SetLineStyle(1);
  mg_lxy_trig->Add(gr_a1_le_lxy_trig);

  gr_a1_g_lxy_trig->SetMarkerColor(kBlack);
  gr_a1_g_lxy_trig->SetMarkerStyle(2);
  gr_a1_g_lxy_trig->SetLineColor(kBlack);
  gr_a1_g_lxy_trig->SetLineStyle(2);
  mg_lxy_trig->Add(gr_a1_g_lxy_trig);

  mg_lxy_trig->Draw("ALP");
  set_title_and_label_style(mg_lxy_trig);
  mg_lxy_trig->GetXaxis()->SetTitle("L_{xy} [cm]");
  mg_lxy_trig->GetYaxis()->SetTitle("Efficiency");
  mg_lxy_trig->SetMinimum(0.);
  mg_lxy_trig->SetMaximum(1.);
  etaleg->Draw("same");

  pixel_1->Draw("same");
  pixel_2->Draw("same");
  pixel_3->Draw("same");
  tracker_innerbarrel->Draw("same");
  tracker_outerbarrel->Draw("same");


  eta_lxy_trig->SaveAs("EfficiencyByEta_vs_Lxy_Trig.pdf");
  eta_lxy_trig->SaveAs("EfficiencyByEta_vs_Lxy_Trig.C");



  mg_lxy_trig->GetXaxis()->SetLimits(0,12);
  mg_lxy_trig->Draw("ALP");
  etaleg->Draw("same");
  pixel_1->Draw("same");
  pixel_2->Draw("same");
  pixel_3->Draw("same");
  tracker_innerbarrel->Draw("same");
  tracker_outerbarrel->Draw("same");

  eta_lxy_trig->SaveAs("EfficiencyByEta_1D_vs_Lxy_Trig_0to12.pdf");
  eta_lxy_trig->SaveAs("EfficiencyByEta_1D_vs_Lxy_Trig_0to12.C");


  TCanvas *eta_lz_trig = new TCanvas("eta_lz_trig", "eta_lz_trig", my_canvas_x, my_canvas_y);
  set_canvas_style_tgraph(eta_lz_trig);
  TMultiGraph *mg_lz_trig = new TMultiGraph("",cms_title);

  gStyle->SetTitleFontSize(0.07);
  gStyle->SetTitleStyle( 0 );
  gStyle->SetTitleAlign(13);
  gStyle->SetTitleX(0.);
  gStyle->SetTitleY(1.);
  gStyle->SetTitleW(1);
  gStyle->SetTitleH(0.058);
  gStyle->SetTitleBorderSize( 0 );

  gr_a0_le_lz_trig = new TGraphAsymmErrors(num_Trig_LEp9_1D_A0_LZ, den_Trig_LEp9_1D_A0_LZ);
  gr_a1_le_lz_trig = new TGraphAsymmErrors(num_Trig_LEp9_1D_A1_LZ, den_Trig_LEp9_1D_A1_LZ);
  gr_a1_g_lz_trig = new TGraphAsymmErrors(num_Trig_Gp9_1D_A1_LZ, den_Trig_Gp9_1D_A1_LZ);
  gr_a0_g_lz_trig = new TGraphAsymmErrors(num_Trig_Gp9_1D_A0_LZ, den_Trig_Gp9_1D_A0_LZ);

  set_title_and_label_style(gr_a0_le_lz_trig);
  set_title_and_label_style(gr_a1_le_lz_trig);
  set_title_and_label_style(gr_a1_g_lz_trig);
  set_title_and_label_style(gr_a0_g_lz_trig);

  gr_a0_le_lz_trig->SetMarkerColor(kRed);
  gr_a0_le_lz_trig->SetMarkerStyle(2);
  gr_a0_le_lz_trig->SetLineColor(kRed);
  gr_a0_le_lz_trig->SetLineStyle(1);

  gr_a0_g_lz_trig->SetMarkerColor(kRed);
  gr_a0_g_lz_trig->SetMarkerStyle(2);
  gr_a0_g_lz_trig->SetLineColor(kRed);
  gr_a0_g_lz_trig->SetLineStyle(2);

  gr_a1_le_lz_trig->SetMarkerColor(kBlack);
  gr_a1_le_lz_trig->SetMarkerStyle(2);
  gr_a1_le_lz_trig->SetLineColor(kBlack);
  gr_a1_le_lz_trig->SetLineStyle(1);

  gr_a1_g_lz_trig->SetMarkerColor(kBlack);
  gr_a1_g_lz_trig->SetMarkerStyle(2);
  gr_a1_g_lz_trig->SetLineColor(kBlack);
  gr_a1_g_lz_trig->SetLineStyle(2);

  mg_lz_trig->Add(gr_a0_le_lz_trig);
  mg_lz_trig->Add(gr_a1_le_lz_trig);
  mg_lz_trig->Add(gr_a0_g_lz_trig);
  mg_lz_trig->Add(gr_a1_g_lz_trig);

  mg_lz_trig->Draw("ALP");
  set_title_and_label_style(mg_lz_trig);
  mg_lz_trig->GetXaxis()->SetTitle("L_{z} [cm]");
  mg_lz_trig->GetYaxis()->SetTitle("Efficiency");
  mg_lz_trig->SetMinimum(0.);
  mg_lz_trig->SetMaximum(1.);


  pixel_endcap_1->Draw("same");
  pixel_endcap_2->Draw("same");

  etalegz->Draw("same");
  eta_lz_trig->SaveAs("EfficiencyByEta_vs_Lz_Trig.pdf");
  eta_lz_trig->SaveAs("EfficiencyByEta_vs_Lz_Trig.C");


  mg_lz_trig->GetXaxis()->SetLimits(0,12);
  mg_lz_trig->Draw("ALP");
  etalegz->Draw("same");
  pixel_1->Draw("same");
  pixel_2->Draw("same");
  pixel_3->Draw("same");
  tracker_innerbarrel->Draw("same");
  tracker_outerbarrel->Draw("same");

  eta_lz_trig->SaveAs("EfficiencyByEta_1D_vs_Lz_Trig_0to12.pdf");
  eta_lz_trig->SaveAs("EfficiencyByEta_1D_vs_Lz_Trig_0to12.C");


  /*
    TCanvas *effxy0 = new TCanvas("effxy0", "effxy0", my_canvas_x, my_canvas_y);
    gr4 = new TGraphAsymmErrors(num_1D_A1_LXY, den_1D_A1_LXY);
    gr4->SetTitle("1D Efficiency #gamma_{D2} L_{xy}");
    gr4->GetYaxis()->SetTitle("Efficiency");
    gr4->GetXaxis()->SetTitle("L_{xy} [cm]");
    gr4->SetMarkerColor(kBlue);
    gr4->SetMarkerStyle(21);
    gr4->Draw("ALP");

    TCanvas *effz = new TCanvas("effz", "effz", my_canvas_x, my_canvas_y);
    gr5 = new TGraphAsymmErrors(num_1D_A1_LZ, den_1D_A1_LZ);
    gr5->SetTitle("1D Efficiency #gamma_{D2} L_{z}");
    gr5->SetMarkerColor(4);
    gr5->SetMarkerStyle(21);
    gr5->Draw("ALP");

    TCanvas *effxy3 = new TCanvas("effxy3", "effxy3", my_canvas_x, my_canvas_y);
    gr6 = new TGraphAsymmErrors(num_1D_A0_LXY, den_1D_A0_LXY);
    gr6->SetTitle("1D Efficiency #gamma_{D1} L_{xy}");
    gr6->SetMarkerColor(4);
    gr6->SetMarkerStyle(21);
    gr6->Draw("ALP");

    TCanvas *effz3 = new TCanvas("effz3", "effz3", my_canvas_x, my_canvas_y);
    gr7 = new TGraphAsymmErrors(num_1D_A0_LZ, den_1D_A0_LZ);
    gr7->SetTitle("1D Efficiency #gamma_{D1} L_{z");
    gr7->SetMarkerColor(4);
    gr7->SetMarkerStyle(21);
    gr7->Draw("ALP");
  */

  eff_2D_A0->GetZaxis()->SetRangeUser(0.0,1.0);
  eff_2D_A1->GetZaxis()->SetRangeUser(0.0,1.0);

  UInt_t Number = 5;
  Double_t Red[5]   = { 0.00, 0.09, 0.18, 0.09, 0.00 };
  Double_t Green[5] = { 0.01, 0.02, 0.39, 0.68, 0.97 };
  Double_t Blue[5]  = { 0.17, 0.39, 0.62, 0.79, 0.97 };
  Double_t Length[5] = { 0.00, 0.34, 0.61, 0.84, 1.00 };

  Int_t nb=50;
  TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,nb);

  Int_t colors[] = {0,1,2,3,4,5,6}; // #colors >= #levels - 1
  gStyle->SetPalette((sizeof(colors)/sizeof(Int_t)), colors);

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

  set_title_and_label_style(eff_2D_A0);
  set_title_and_label_style(eff_2D_A1);

  float bpx = 9.8;
  float epx = 46.5;

  pixel_3 = new TLine(0, bpx, epx, bpx);
  pixel_endcap_2 = new TLine(epx, 0, epx, bpx);

  //Blue Lines
  linestyle = 2;
  linewidth = 3;
  pixel_3->SetLineStyle(linestyle);
  pixel_3->SetLineWidth(linewidth);
  pixel_3->SetLineColor(kGray+2);

  pixel_endcap_2->SetLineStyle(linestyle);
  pixel_endcap_2->SetLineWidth(linewidth);
  pixel_endcap_2->SetLineColor(kGray+2);

  TLine* eta0p9 = new TLine(0, 0, 80, 80*tan(2*atan(exp(-0.9))));
  TLine* eta1p55 = new TLine(0, 0, 80, 80*tan(2*atan(exp(-1.55))));

  eta0p9->SetLineStyle(1);
  eta0p9->SetLineWidth(linewidth);
  eta0p9->SetLineColor(kBlack);

  eta1p55->SetLineStyle(5);
  eta1p55->SetLineWidth(linewidth);
  eta1p55->SetLineColor(kBlack);


  TCanvas *c = new TCanvas("c","c",my_canvas_x, my_canvas_y);
  set_canvas_style(c);

  gStyle->SetTitleFontSize(0.07);
  gStyle->SetTitleStyle( 0 );
  gStyle->SetTitleAlign(13);
  gStyle->SetTitleX(0.);
  gStyle->SetTitleY(1.);
  gStyle->SetTitleW(1);
  gStyle->SetTitleH(0.058);
  gStyle->SetTitleBorderSize( 0 );

  c->SetRightMargin(0.15);
  eff_2D_A0->GetYaxis()->SetTitle("#gamma_{D1} L_{xy} [cm]");
  eff_2D_A0->GetXaxis()->SetTitle("#gamma_{D1} |L_{z}| [cm]");
  eff_2D_A0->GetZaxis()->SetTitle("#varepsilon_{Full}/#alpha_{GEN}");
  eff_2D_A0->GetZaxis()->SetLabelFont(42);
  eff_2D_A0->GetZaxis()->SetLabelOffset(0.007);
  eff_2D_A0->GetZaxis()->SetTitleFont(42);
  eff_2D_A0->GetZaxis()->SetTitleOffset(1.15);
  eff_2D_A0->GetZaxis()->SetTitleSize(0.04);

  gStyle->SetOptStat(0);
  //    eff_2D_A0->SetContour((sizeof(levels)/sizeof(Double_t)), levels);
  eff_2D_A0->Draw("COLZ");

  pixel_3->Draw("same");
  pixel_endcap_2->Draw("same");
  eta0p9->Draw("same");
  eta1p55->Draw("same");

  leg = new TLegend(0.17,0.80,0.45,0.92);
  leg->SetBorderSize(1);
  leg->SetFillColor(0);
  leg->SetTextSize(0.03);
  leg->AddEntry(eta0p9,"|#eta| = 0.9","L");
  leg->AddEntry(eta1p55,"|#eta| = 1.55","L");
  leg->AddEntry(pixel_3,"Fiducial volume","L");
  leg->Draw("same");

  c->SaveAs("eff_2D_LxyLz_A0.pdf");
  c->SaveAs("eff_2D_LxyLz_A0.C");
  //I am not quite sure what this did...    
  //if(l==0) c->SaveAs("eff_2D_LxyLz_A0_ct05.pdf","recreate");




  TCanvas *c1 = new TCanvas("c1","c1",my_canvas_x, my_canvas_y);
  set_canvas_style(c1);
  gStyle->SetTitleFontSize(0.07);
  gStyle->SetTitleStyle( 0 );
  gStyle->SetTitleAlign(13);
  gStyle->SetTitleX(0.);
  gStyle->SetTitleY(1.);
  gStyle->SetTitleW(1);
  gStyle->SetTitleH(0.058);
  gStyle->SetTitleBorderSize( 0 );

  c1->SetRightMargin(0.15);
  eff_2D_A1->GetYaxis()->SetTitle("#gamma_{D2} L_{xy} [cm]");
  eff_2D_A1->GetXaxis()->SetTitle("#gamma_{D2} |L_{z}| [cm]");
  eff_2D_A1->GetZaxis()->SetTitle("#varepsilon_{Full}/#alpha_{GEN}");
  eff_2D_A1->GetZaxis()->SetLabelFont(42);
  eff_2D_A1->GetZaxis()->SetLabelOffset(0.007);
  eff_2D_A1->GetZaxis()->SetTitleFont(42);
  eff_2D_A1->GetZaxis()->SetTitleOffset(1.15);
  eff_2D_A1->GetZaxis()->SetTitleSize(0.04);
  gStyle->SetOptStat(0);
  eff_2D_A1->Draw("COLZ");

  pixel_3->Draw("same");
  pixel_endcap_2->Draw("same");
  eta0p9->Draw("same");
  eta1p55->Draw("same");
  leg->Draw("same");

  c1->SaveAs("eff_2D_LxyLz_A1.pdf");
  c1->SaveAs("eff_2D_LxyLz_A1.C");
  //I am not quite sure what this did...    
  //if(l==0) c1->SaveAs("eff_2D_LxyLz_A1_ct05.pdf","recreate");

}//closing method

void efficiency_SD(){
  //  makeCounters();

  
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_0_13TeV_20k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_0_13TeV_20k_PAT_ANA_V2_v1/170124_224445/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_0p05_13TeV_20k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_0p05_13TeV_20k_PAT_ANA_V2_v1/170128_023406/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_0p1_13TeV_20k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_0p1_13TeV_20k_PAT_ANA_V2_v1/170128_024144/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_0p1_13TeV_80k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_0p1_13TeV_80k_PAT_ANA_V2_v1/170128_024130/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_0p5_13TeV_20k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_0p5_13TeV_20k_PAT_ANA_V2_v1/170128_024115/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_0p5_13TeV_80k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_0p5_13TeV_80k_PAT_ANA_V2_v1/170128_024023/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_1_13TeV_53k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_1_13TeV_53k_PAT_ANA_V2_v1/170128_025345/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_2_13TeV_47k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_2_13TeV_47k_PAT_ANA_V2_v1/170128_025333/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_2_13TeV_48k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_2_13TeV_48k_PAT_ANA_V2_v1/170128_025321/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_2_13TeV_49k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_2_13TeV_49k_PAT_ANA_V2_v1/170128_025306/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_2_13TeV_51k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_2_13TeV_51k_PAT_ANA_V2_v1/170128_025255/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_2_13TeV_52k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_2_13TeV_52k_PAT_ANA_V2_v1/170128_025240/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_2_13TeV_53k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_2_13TeV_53k_PAT_ANA_V2_v1/170128_025229/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_5_13TeV_47k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_5_13TeV_47k_PAT_ANA_V2_v1/170128_025215/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_5_13TeV_48k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_5_13TeV_48k_PAT_ANA_V2_v1/170128_025151/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_5_13TeV_49k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_5_13TeV_49k_PAT_ANA_V2_v1/170128_025140/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_5_13TeV_51k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_5_13TeV_51k_PAT_ANA_V2_v1/170128_025127/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_5_13TeV_52k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_5_13TeV_52k_PAT_ANA_V2_v1/170128_025113/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_5_13TeV_53k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_5_13TeV_53k_PAT_ANA_V2_v1/170128_025100/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_20_13TeV_67k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_20_13TeV_67k_PAT_ANA_V2_v1/170128_025026/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_20_13TeV_68k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_20_13TeV_68k_PAT_ANA_V2_v1/170128_025002/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_20_13TeV_69k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_20_13TeV_69k_PAT_ANA_V2_v1/170128_024949/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_20_13TeV_69k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_20_13TeV_69k_PAT_ANA_V2_v1/170128_024949/0001/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_20_13TeV_70k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_20_13TeV_70k_PAT_ANA_V2_v1/170128_024937/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_20_13TeV_71k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_20_13TeV_71k_PAT_ANA_V2_v1/170128_024926/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_20_13TeV_72k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_20_13TeV_72k_PAT_ANA_V2_v1/170128_024915/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_20_13TeV_72k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_20_13TeV_72k_PAT_ANA_V2_v1/170128_024915/0001/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_20_13TeV_73k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_20_13TeV_73k_PAT_ANA_V2_v1/170128_024900/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_20_13TeV_74k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_20_13TeV_74k_PAT_ANA_V2_v1/170128_024849/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_20_13TeV_75k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_20_13TeV_75k_PAT_ANA_V2_v1/170128_024837/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_20_13TeV_76k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_20_13TeV_76k_PAT_ANA_V2_v1/170128_024825/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_20_13TeV_77k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_20_13TeV_77k_PAT_ANA_V2_v1/170128_024813/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_20_13TeV_78k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_20_13TeV_78k_PAT_ANA_V2_v1/170128_024757/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_20_13TeV_79k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_20_13TeV_79k_PAT_ANA_V2_v1/170128_024745/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_20_13TeV_80k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_20_13TeV_80k_PAT_ANA_V2_v1/170128_024734/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_100_13TeV_60k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_100_13TeV_60k_PAT_ANA_V2_v1/170128_023957/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_100_13TeV_62k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_100_13TeV_62k_PAT_ANA_V2_v1/170128_023934/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_100_13TeV_63k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_100_13TeV_63k_PAT_ANA_V2_v1/170128_023922/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_100_13TeV_64k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_100_13TeV_64k_PAT_ANA_V2_v1/170128_023909/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_100_13TeV_67k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_100_13TeV_67k_PAT_ANA_V2_v1/170128_024648/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_100_13TeV_68k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_100_13TeV_68k_PAT_ANA_V2_v1/170128_024635/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_100_13TeV_70k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_100_13TeV_70k_PAT_ANA_V2_v1/170128_024435/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_100_13TeV_72k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_100_13TeV_72k_PAT_ANA_V2_v1/170128_024402/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_100_13TeV_73k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_100_13TeV_73k_PAT_ANA_V2_v1/170128_024351/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_100_13TeV_74k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_100_13TeV_74k_PAT_ANA_V2_v1/170128_024336/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_100_13TeV_75k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_100_13TeV_75k_PAT_ANA_V2_v1/170128_024318/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_100_13TeV_76k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_100_13TeV_76k_PAT_ANA_V2_v1/170128_024306/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_100_13TeV_77k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_100_13TeV_77k_PAT_ANA_V2_v1/170128_024255/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_100_13TeV_79k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_100_13TeV_79k_PAT_ANA_V2_v1/170128_024211/0000/");
  create_eff_pergamD2DLxyLz("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_100_13TeV_80k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_100_13TeV_80k_PAT_ANA_V2_v1/170128_024159/0000/");

  //  makePlots();

  //  BAM->Write();
}
