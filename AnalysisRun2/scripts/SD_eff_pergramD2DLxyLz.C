#include <algorithm>    // std::max
#include "TMath.h"
#include <math.h>
#include "TEfficiency.h"
#include "Helpers.h"
#include "TString.h"

///----Global Variables ----///
TFile *SD = new TFile("Efficiency_Plots.root","RECREATE");

Float_t count_gam_A0[20][40];
Float_t count_rec_A0[20][40];
Float_t eff_A0[20][40];

Float_t count_gam_A1[20][40];
Float_t count_rec_A1[20][40];
Float_t eff_A1[20][40];

TH1F *den_1D_A0_LXY = new TH1F("den_1D_A0_LXY", "den_1D_A0_LXY", 40, 0, 80);
TH1F *num_1D_A0_LXY = new TH1F("num_1D_A0_LXY", "num_1D_A0_LXY", 40, 0, 80);

TH1F *den_1D_A0_LZ = new TH1F("den_1D_A0_LZ", "den_1D_A0_LZ", 20, 0, 80);
TH1F *num_1D_A0_LZ = new TH1F("num_1D_A0_LZ", "num_1D_A0_LZ", 20, 0, 80);

TH1F *den_1D_A1_LXY = new TH1F("den_1D_A1_LXY", "den_1D_A1_LXY", 40, 0, 80);
TH1F *num_1D_A1_LXY = new TH1F("num_1D_A1_LXY", "num_1D_A1_LXY", 40, 0, 80);

TH1F *den_1D_A1_LZ = new TH1F("den_1D_A1_LZ", "den_1D_A1_LZ", 20, 0, 80);
TH1F *num_1D_A1_LZ = new TH1F("num_1D_A1_LZ", "num_1D_A1_LZ", 20, 0, 80);

TH1F *dR_A0 = new TH1F("dR_A0", "dR_A0", 100, 0, 1);
TH1F *dR_A1 = new TH1F("dR_A1", "dR_A1", 100, 0, 1);

TH1F *dPhi_Plot = new TH1F("dPhi_A0", "dPhi_A0", 1400, -7, 7);

TH1F *den_1D_A1_pT = new TH1F("den_1D_A1_pT", "den_1D_A1_pT", 130, 0, 130);
TH1F *num_1D_A1_pT = new TH1F("num_1D_A1_pT", "num_1D_A1_pT", 130, 0, 130);

TH1F *den_1D_A0_pT = new TH1F("den_1D_A0_pT", "den_1D_A0_pT", 130, 0, 130);
TH1F *num_1D_A0_pT = new TH1F("num_1D_A0_pT", "num_1D_A0_pT", 130, 0, 130);

//Efficiency by eta -- <= 0.8

Float_t bins[] = {0, 2, 4, 6, 8, 10, 12, 16, 18, 20, 25, 30, 35, 40, 45, 50, 60, 80};
Int_t binnum = sizeof(bins)/sizeof(Float_t) - 1;

TH1F *den_LEp9_1D_A0_LXY = new TH1F("den_LEp9_1D_A0_LXY", "den_LEp9_1D_A0_LXY", binnum, bins);
TH1F *num_LEp9_1D_A0_LXY = new TH1F("num_LEp9_1D_A0_LXY", "num_LEp9_1D_A0_LXY", binnum, bins);

TH1F *den_LEp9_1D_A0_LZ = new TH1F("den_LEp9_1D_A0_LZ", "den_LEp9_1D_A0_LZ", binnum, bins);
TH1F *num_LEp9_1D_A0_LZ = new TH1F("num_LEp9_1D_A0_LZ", "num_LEp9_1D_A0_LZ", binnum, bins);

TH1F *den_LEp9_1D_A1_LXY = new TH1F("den_LEp9_1D_A1_LXY", "den_LEp9_1D_A1_LXY", binnum, bins);
TH1F *num_LEp9_1D_A1_LXY = new TH1F("num_LEp9_1D_A1_LXY", "num_LEp9_1D_A1_LXY", binnum, bins);

TH1F *den_LEp9_1D_A1_LZ = new TH1F("den_LEp9_1D_A1_LZ", "den_LEp9_1D_A1_LZ", binnum, bins);
TH1F *num_LEp9_1D_A1_LZ = new TH1F("num_LEp9_1D_A1_LZ", "num_LEp9_1D_A1_LZ", binnum, bins);

TH1F *den_LEp9_1D_A1_pT = new TH1F("den_LEp9_1D_A1_pT", "den_LEp9_1D_A1_pT", binnum, bins);
TH1F *num_LEp9_1D_A1_pT = new TH1F("num_LEp9_1D_A1_pT", "num_LEp9_1D_A1_pT", binnum, bins);

TH1F *den_LEp9_1D_A0_pT = new TH1F("den_LEp9_1D_A0_pT", "den_LEp9_1D_A0_pT", binnum, bins);
TH1F *num_LEp9_1D_A0_pT = new TH1F("num_LEp9_1D_A0_pT", "num_LEp9_1D_A0_pT", binnum, bins);

//Efficiency by eta -- > 0.8

TH1F *den_Gp9_1D_A0_LXY = new TH1F("den_Gp9_1D_A0_LXY", "den_Gp9_1D_A0_LXY", binnum, bins);
TH1F *num_Gp9_1D_A0_LXY = new TH1F("num_Gp9_1D_A0_LXY", "num_Gp9_1D_A0_LXY", binnum, bins);

TH1F *den_Gp9_1D_A0_LZ = new TH1F("den_Gp9_1D_A0_LZ", "den_Gp9_1D_A0_LZ", binnum, bins);
TH1F *num_Gp9_1D_A0_LZ = new TH1F("num_Gp9_1D_A0_LZ", "num_Gp9_1D_A0_LZ", binnum, bins);

TH1F *den_Gp9_1D_A1_LXY = new TH1F("den_Gp9_1D_A1_LXY", "den_Gp9_1D_A1_LXY", binnum, bins);
TH1F *num_Gp9_1D_A1_LXY = new TH1F("num_Gp9_1D_A1_LXY", "num_Gp9_1D_A1_LXY", binnum, bins);

TH1F *den_Gp9_1D_A1_LZ = new TH1F("den_Gp9_1D_A1_LZ", "den_Gp9_1D_A1_LZ", binnum, bins);
TH1F *num_Gp9_1D_A1_LZ = new TH1F("num_Gp9_1D_A1_LZ", "num_Gp9_1D_A1_LZ", binnum, bins);

TH1F *den_Gp9_1D_A1_pT = new TH1F("den_Gp9_1D_A1_pT", "den_Gp9_1D_A1_pT", binnum, bins);
TH1F *num_Gp9_1D_A1_pT = new TH1F("num_Gp9_1D_A1_pT", "num_Gp9_1D_A1_pT", binnum, bins);

TH1F *den_Gp9_1D_A0_pT = new TH1F("den_Gp9_1D_A0_pT", "den_Gp9_1D_A0_pT", binnum, bins);
TH1F *num_Gp9_1D_A0_pT = new TH1F("num_Gp9_1D_A0_pT", "num_Gp9_1D_A0_pT", binnum, bins);

//Efficiency by eta && event passed the trigger

TH1F *den_Trig_LEp9_1D_A0_LXY = new TH1F("den_Trig_LEp9_1D_A0_LXY", "den_Trig_LEp9_1D_A0_LXY", binnum, bins);
TH1F *num_Trig_LEp9_1D_A0_LXY = new TH1F("num_Trig_LEp9_1D_A0_LXY", "num_Trig_LEp9_1D_A0_LXY", binnum, bins);

TH1F *den_Trig_LEp9_1D_A0_LZ = new TH1F("den_Trig_LEp9_1D_A0_LZ", "den_Trig_LEp9_1D_A0_LZ", binnum, bins);
TH1F *num_Trig_LEp9_1D_A0_LZ = new TH1F("num_Trig_LEp9_1D_A0_LZ", "num_Trig_LEp9_1D_A0_LZ", binnum, bins);

TH1F *den_Trig_LEp9_1D_A1_LXY = new TH1F("den_Trig_LEp9_1D_A1_LXY", "den_Trig_LEp9_1D_A1_LXY", binnum, bins);
TH1F *num_Trig_LEp9_1D_A1_LXY = new TH1F("num_Trig_LEp9_1D_A1_LXY", "num_Trig_LEp9_1D_A1_LXY", binnum, bins);

TH1F *den_Trig_LEp9_1D_A1_LZ = new TH1F("den_Trig_LEp9_1D_A1_LZ", "den_Trig_LEp9_1D_A1_LZ", binnum, bins);
TH1F *num_Trig_LEp9_1D_A1_LZ = new TH1F("num_Trig_LEp9_1D_A1_LZ", "num_Trig_LEp9_1D_A1_LZ", binnum, bins);

TH1F *den_Trig_LEp9_1D_A1_pT = new TH1F("den_Trig_LEp9_1D_A1_pT", "den_Trig_LEp9_1D_A1_pT", binnum, bins);
TH1F *num_Trig_LEp9_1D_A1_pT = new TH1F("num_Trig_LEp9_1D_A1_pT", "num_Trig_LEp9_1D_A1_pT", binnum, bins);

TH1F *den_Trig_LEp9_1D_A0_pT = new TH1F("den_Trig_LEp9_1D_A0_pT", "den_Trig_LEp9_1D_A0_pT", binnum, bins);
TH1F *num_Trig_LEp9_1D_A0_pT = new TH1F("num_Trig_LEp9_1D_A0_pT", "num_Trig_LEp9_1D_A0_pT", binnum, bins);

//Efficiency by eta -- > 0.8

TH1F *den_Trig_Gp9_1D_A0_LXY = new TH1F("den_Trig_Gp9_1D_A0_LXY", "den_Trig_Gp9_1D_A0_LXY", binnum, bins);
TH1F *num_Trig_Gp9_1D_A0_LXY = new TH1F("num_Trig_Gp9_1D_A0_LXY", "num_Trig_Gp9_1D_A0_LXY", binnum, bins);

TH1F *den_Trig_Gp9_1D_A0_LZ = new TH1F("den_Trig_Gp9_1D_A0_LZ", "den_Trig_Gp9_1D_A0_LZ", binnum, bins);
TH1F *num_Trig_Gp9_1D_A0_LZ = new TH1F("num_Trig_Gp9_1D_A0_LZ", "num_Trig_Gp9_1D_A0_LZ", binnum, bins);

TH1F *den_Trig_Gp9_1D_A1_LXY = new TH1F("den_Trig_Gp9_1D_A1_LXY", "den_Trig_Gp9_1D_A1_LXY", binnum, bins);
TH1F *num_Trig_Gp9_1D_A1_LXY = new TH1F("num_Trig_Gp9_1D_A1_LXY", "num_Trig_Gp9_1D_A1_LXY", binnum, bins);

TH1F *den_Trig_Gp9_1D_A1_LZ = new TH1F("den_Trig_Gp9_1D_A1_LZ", "den_Trig_Gp9_1D_A1_LZ", binnum, bins);
TH1F *num_Trig_Gp9_1D_A1_LZ = new TH1F("num_Trig_Gp9_1D_A1_LZ", "num_Trig_Gp9_1D_A1_LZ", binnum, bins);

TH1F *den_Trig_Gp9_1D_A1_pT = new TH1F("den_Trig_Gp9_1D_A1_pT", "den_Trig_Gp9_1D_A1_pT", binnum, bins);
TH1F *num_Trig_Gp9_1D_A1_pT = new TH1F("num_Trig_Gp9_1D_A1_pT", "num_Trig_Gp9_1D_A1_pT", binnum, bins);

TH1F *den_Trig_Gp9_1D_A0_pT = new TH1F("den_Trig_Gp9_1D_A0_pT", "den_Trig_Gp9_1D_A0_pT", binnum, bins);
TH1F *num_Trig_Gp9_1D_A0_pT = new TH1F("num_Trig_Gp9_1D_A0_pT", "num_Trig_Gp9_1D_A0_pT", binnum, bins);

/*
//Efficiency by eta -- <= 0.8.  

TH1F *den_LEp9_1D_A0_mu0_LXY = new TH1F("den_LEp9_1D_A0_mu0_LXY", "den_LEp9_1D_A0_mu0_LXY", binnum, bins);
TH1F *num_LEp9_1D_A0_mu0_LXY = new TH1F("num_LEp9_1D_A0_mu0_LXY", "num_LEp9_1D_A0_mu0_LXY", binnum, bins);

TH1F *den_LEp9_1D_A0_mu0_LZ = new TH1F("den_LEp9_1D_A0_mu0_LZ", "den_LEp9_1D_A0_mu0_LZ", binnum, bins);
TH1F *num_LEp9_1D_A0_mu0_LZ = new TH1F("num_LEp9_1D_A0_mu0_LZ", "num_LEp9_1D_A0_mu0_LZ", binnum, bins);

TH1F *den_LEp9_1D_A0_mu1_LXY = new TH1F("den_LEp9_1D_A0_mu1_LXY", "den_LEp9_1D_A0_mu1_LXY", binnum, bins);
TH1F *num_LEp9_1D_A0_mu1_LXY = new TH1F("num_LEp9_1D_A0_mu1_LXY", "num_LEp9_1D_A0_mu1_LXY", binnum, bins);

TH1F *den_LEp9_1D_A0_mu1_LZ = new TH1F("den_LEp9_1D_A0_mu1_LZ", "den_LEp9_1D_A0_mu1_LZ", binnum, bins);
TH1F *num_LEp9_1D_A0_mu1_LZ = new TH1F("num_LEp9_1D_A0_mu1_LZ", "num_LEp9_1D_A0_mu1_LZ", binnum, bins);

TH1F *den_LEp9_1D_A0_mu1_pT = new TH1F("den_LEp9_1D_A0_mu1_pT", "den_LEp9_1D_A0_mu1_pT", binnum, bins);
TH1F *num_LEp9_1D_A0_mu1_pT = new TH1F("num_LEp9_1D_A0_mu1_pT", "num_LEp9_1D_A0_mu1_pT", binnum, bins);

TH1F *den_LEp9_1D_A0_mu0_pT = new TH1F("den_LEp9_1D_A0_mu0_pT", "den_LEp9_1D_A0_mu0_pT", binnum, bins);
TH1F *num_LEp9_1D_A0_mu0_pT = new TH1F("num_LEp9_1D_A0_mu0_pT", "num_LEp9_1D_A0_mu0_pT", binnum, bins);

//Efficiency by eta -- > 0.8

TH1F *den_Gp9_1D_A0_mu0_LXY = new TH1F("den_Gp9_1D_A0_mu0_LXY", "den_Gp9_1D_A0_mu0_LXY", binnum, bins);
TH1F *num_Gp9_1D_A0_mu0_LXY = new TH1F("num_Gp9_1D_A0_mu0_LXY", "num_Gp9_1D_A0_mu0_LXY", binnum, bins);

TH1F *den_Gp9_1D_A0_mu0_LZ = new TH1F("den_Gp9_1D_A0_mu0_LZ", "den_Gp9_1D_A0_mu0_LZ", binnum, bins);
TH1F *num_Gp9_1D_A0_mu0_LZ = new TH1F("num_Gp9_1D_A0_mu0_LZ", "num_Gp9_1D_A0_mu0_LZ", binnum, bins);

TH1F *den_Gp9_1D_A0_mu1_LXY = new TH1F("den_Gp9_1D_A0_mu1_LXY", "den_Gp9_1D_A0_mu1_LXY", binnum, bins);
TH1F *num_Gp9_1D_A0_mu1_LXY = new TH1F("num_Gp9_1D_A0_mu1_LXY", "num_Gp9_1D_A0_mu1_LXY", binnum, bins);

TH1F *den_Gp9_1D_A0_mu1_LZ = new TH1F("den_Gp9_1D_A0_mu1_LZ", "den_Gp9_1D_A0_mu1_LZ", binnum, bins);
TH1F *num_Gp9_1D_A0_mu1_LZ = new TH1F("num_Gp9_1D_A0_mu1_LZ", "num_Gp9_1D_A0_mu1_LZ", binnum, bins);

TH1F *den_Gp9_1D_A0_mu1_pT = new TH1F("den_Gp9_1D_A0_mu1_pT", "den_Gp9_1D_A0_mu1_pT", binnum, bins);
TH1F *num_Gp9_1D_A0_mu1_pT = new TH1F("num_Gp9_1D_A0_mu1_pT", "num_Gp9_1D_A0_mu1_pT", binnum, bins);

TH1F *den_Gp9_1D_A0_mu0_pT = new TH1F("den_Gp9_1D_A0_mu0_pT", "den_Gp9_1D_A0_mu0_pT", binnum, bins);
TH1F *num_Gp9_1D_A0_mu0_pT = new TH1F("num_Gp9_1D_A0_mu0_pT", "num_Gp9_1D_A0_mu0_pT", binnum, bins);

//Efficiency by eta && event passed the trigger

TH1F *den_Trig_LEp9_1D_A0_mu0_LXY = new TH1F("den_Trig_LEp9_1D_A0_mu0_LXY", "den_Trig_LEp9_1D_A0_mu0_LXY", binnum, bins);
TH1F *num_Trig_LEp9_1D_A0_mu0_LXY = new TH1F("num_Trig_LEp9_1D_A0_mu0_LXY", "num_Trig_LEp9_1D_A0_mu0_LXY", binnum, bins);

TH1F *den_Trig_LEp9_1D_A0_mu0_LZ = new TH1F("den_Trig_LEp9_1D_A0_mu0_LZ", "den_Trig_LEp9_1D_A0_mu0_LZ", binnum, bins);
TH1F *num_Trig_LEp9_1D_A0_mu0_LZ = new TH1F("num_Trig_LEp9_1D_A0_mu0_LZ", "num_Trig_LEp9_1D_A0_mu0_LZ", binnum, bins);

TH1F *den_Trig_LEp9_1D_A0_mu1_LXY = new TH1F("den_Trig_LEp9_1D_A0_mu1_LXY", "den_Trig_LEp9_1D_A0_mu1_LXY", binnum, bins);
TH1F *num_Trig_LEp9_1D_A0_mu1_LXY = new TH1F("num_Trig_LEp9_1D_A0_mu1_LXY", "num_Trig_LEp9_1D_A0_mu1_LXY", binnum, bins);

TH1F *den_Trig_LEp9_1D_A0_mu1_LZ = new TH1F("den_Trig_LEp9_1D_A0_mu1_LZ", "den_Trig_LEp9_1D_A0_mu1_LZ", binnum, bins);
TH1F *num_Trig_LEp9_1D_A0_mu1_LZ = new TH1F("num_Trig_LEp9_1D_A0_mu1_LZ", "num_Trig_LEp9_1D_A0_mu1_LZ", binnum, bins);

TH1F *den_Trig_LEp9_1D_A0_mu1_pT = new TH1F("den_Trig_LEp9_1D_A0_mu1_pT", "den_Trig_LEp9_1D_A0_mu1_pT", binnum, bins);
TH1F *num_Trig_LEp9_1D_A0_mu1_pT = new TH1F("num_Trig_LEp9_1D_A0_mu1_pT", "num_Trig_LEp9_1D_A0_mu1_pT", binnum, bins);

TH1F *den_Trig_LEp9_1D_A0_mu0_pT = new TH1F("den_Trig_LEp9_1D_A0_mu0_pT", "den_Trig_LEp9_1D_A0_mu0_pT", binnum, bins);
TH1F *num_Trig_LEp9_1D_A0_mu0_pT = new TH1F("num_Trig_LEp9_1D_A0_mu0_pT", "num_Trig_LEp9_1D_A0_mu0_pT", binnum, bins);

//Efficiency by eta -- > 0.9

TH1F *den_Trig_Gp9_1D_A0_mu0_LXY = new TH1F("den_Trig_Gp9_1D_A0_mu0_LXY", "den_Trig_Gp9_1D_A0_mu0_LXY", binnum, bins);
TH1F *num_Trig_Gp9_1D_A0_mu0_LXY = new TH1F("num_Trig_Gp9_1D_A0_mu0_LXY", "num_Trig_Gp9_1D_A0_mu0_LXY", binnum, bins);

TH1F *den_Trig_Gp9_1D_A0_mu0_LZ = new TH1F("den_Trig_Gp9_1D_A0_mu0_LZ", "den_Trig_Gp9_1D_A0_mu0_LZ", binnum, bins);
TH1F *num_Trig_Gp9_1D_A0_mu0_LZ = new TH1F("num_Trig_Gp9_1D_A0_mu0_LZ", "num_Trig_Gp9_1D_A0_mu0_LZ", binnum, bins);

TH1F *den_Trig_Gp9_1D_A0_mu1_LXY = new TH1F("den_Trig_Gp9_1D_A0_mu1_LXY", "den_Trig_Gp9_1D_A0_mu1_LXY", binnum, bins);
TH1F *num_Trig_Gp9_1D_A0_mu1_LXY = new TH1F("num_Trig_Gp9_1D_A0_mu1_LXY", "num_Trig_Gp9_1D_A0_mu1_LXY", binnum, bins);

TH1F *den_Trig_Gp9_1D_A0_mu1_LZ = new TH1F("den_Trig_Gp9_1D_A0_mu1_LZ", "den_Trig_Gp9_1D_A0_mu1_LZ", binnum, bins);
TH1F *num_Trig_Gp9_1D_A0_mu1_LZ = new TH1F("num_Trig_Gp9_1D_A0_mu1_LZ", "num_Trig_Gp9_1D_A0_mu1_LZ", binnum, bins);

TH1F *den_Trig_Gp9_1D_A0_mu1_pT = new TH1F("den_Trig_Gp9_1D_A0_mu1_pT", "den_Trig_Gp9_1D_A0_mu1_pT", binnum, bins);
TH1F *num_Trig_Gp9_1D_A0_mu1_pT = new TH1F("num_Trig_Gp9_1D_A0_mu1_pT", "num_Trig_Gp9_1D_A0_mu1_pT", binnum, bins);

TH1F *den_Trig_Gp9_1D_A0_mu0_pT = new TH1F("den_Trig_Gp9_1D_A0_mu0_pT", "den_Trig_Gp9_1D_A0_mu0_pT", binnum, bins);
TH1F *num_Trig_Gp9_1D_A0_mu0_pT = new TH1F("num_Trig_Gp9_1D_A0_mu0_pT", "num_Trig_Gp9_1D_A0_mu0_pT", binnum, bins);
*/



//Plots WITHOUT cuts
TH2F *dR_vs_dPhi = new TH2F("dR_vs_dPhi", "dR_vs_dPhi", 100, 0, 1, 800, -4, 4);

TH2F *dR_vs_dLxy = new TH2F("dR_vs_dLxy", "dR_vs_dLxy", 100, 0, 1, 40, 0, 80);
TH2F *dPhi_vs_dLxy = new TH2F("dPhi_vs_dLxy", "dPhi_vs_dLxy", 800, -4, 4, 40, 0, 80);

TH2F *dR_vs_dLz = new TH2F("dR_vs_dLz", "dR_vs_dLz", 100, 0, 1, 20, 0, 80);
TH2F *dPhi_vs_dLz = new TH2F("dPhi_vs_dLz", "dPhi_vs_dLz", 800, -4, 4, 20, 0, 80);


TH2F *dR_vs_pt = new TH2F("dR_vs_pt", "dR_vs_pt", 100, 0, 1, 130, 0, 130);
TH2F *pt_vs_dPhi = new TH2F("pt_vs_dPhi", "pt_vs_dPhi", 130,0,130, 800, -4, 4);

TH2F *pt_vs_dLxy = new TH2F("pt_vs_dLxy", "pt_vs_dLxy", 130,0,130, 40, 0, 80);
TH2F *pt_vs_dLz = new TH2F("pt_vs_dLz", "pt_vs_dLz", 130,0,130, 20, 0, 80);

void makeCounters(){

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
}



double My_dPhi (double phi1, double phi2) {
  double dPhi = phi1 - phi2;
  if (dPhi >  TMath::Pi()) dPhi -= 2*TMath::Pi();
  if (dPhi <  -TMath::Pi()) dPhi += 2*TMath::Pi();
  return dPhi;
}

void create_eff_pergamD2DLxyLz(const std::vector<std::string>& dirNames){
  
  
  //bool verbose(true);
  bool verbose(false);
  TChain* chain = new TChain("dummy");
  TString ext("out_ana_");
  
  TString mass_string = "";
  TString cT_string = "";

  decodeFileNameMany(dirNames, mass_string, cT_string);
  fileName = "DarkSUSY_mH_125_mGammaD_" + mass_string + "_cT_" + cT_string;
  cout << "Tag name " << fileName << endl;

  cout << "Preparing histograms" << endl;

  if (mass_string != "0p25") return;

  // add files to the chain
  addfilesMany(chain, dirNames, ext);
  
  
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
  
  Float_t diMuonC_FittedVtx_px;
  Float_t diMuonC_FittedVtx_py;
  Float_t diMuonF_FittedVtx_px;
  Float_t diMuonF_FittedVtx_py;
  
  Float_t genA0_px;
  Float_t genA0_py;
  Float_t genA1_px;
  Float_t genA1_py;
  
  Bool_t isDiMuonHLTFired;
  
  
  TObjArray *fileElements=chain->GetListOfFiles();
  TIter next(fileElements);
  TChainElement *chEl=0;
  
  while ((chEl=(TChainElement*)next())) {
    if (verbose) std::cout << "running on file " << chEl->GetTitle() << std::endl;
    TFile* myfile = new TFile(chEl->GetTitle());
    if (!myfile) {
      if (verbose) std::cout << "File " << chEl->GetTitle() << " does not exist" << std::endl;
      continue;
    }
    
    if (verbose) std::cout << "Loading directory cutFlowAnalyzerPXBL3PXFL2" << std::endl;
    myfile->cd("cutFlowAnalyzerPXBL3PXFL2");
    
    TTree *t = (TTree*)myfile->Get("cutFlowAnalyzerPXBL3PXFL2/Events");
    if (!t) {
      if (verbose) std::cout << "Tree cutFlowAnalyzerPXBL3PXFL2/Events does not exist" << std::endl;
      continue;
    }
    
    if (verbose) cout<<"  Events  "<<t->GetEntries()<<endl;
    
    
    
    
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
    
    //t->SetBranchAddress("is4GenMu8",&is4GenMu8);
    
    t->SetBranchAddress("genA0_Lxy", &genA0_Lxy_rdet);
    t->SetBranchAddress("genA0_Lz",  &genA0_Lz_rdet);
    t->SetBranchAddress("genA1_Lxy", &genA1_Lxy_rdet);
    t->SetBranchAddress("genA1_Lz",  &genA1_Lz_rdet);
    
    
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
    
    Int_t nentries = t->GetEntries();
    
    
    Float_t bin_edges[41]={0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,78,80};
    Float_t bin_edges_Lz[21]={0,4,8,12,16,20,24,28,32,36,40,44,48,52,56,60,64,68,72,76,80};
    
    
    for(int k=0;k<nentries;k++){
      t->GetEntry(k);
      if(is4GenMu8==true){
	Float_t dphi_gD = My_dPhi(genA1_phi,genA0_phi);
	dPhi_Plot->Fill(dphi_gD);
	if(fabs(dphi_gD)>=2){ //What does this cut do?  Why do we want to make sure that the muons are back-to-back?
	  //if(fabs(dphi_gD)>2){ //What does this cut do?  Why do we want to make sure that the muons are back-to-back?
	  //if(fabs(dphi_gD)>2.5){ //What does this cut do?  Why do we want to make sure that the muons are back-to-back?
	  for(int n=0;n<20;n++){
	    if(fabs(genA0_Lz_rdet)>bin_edges_Lz[n] && fabs(genA0_Lz_rdet)<bin_edges_Lz[n+1]){
	      for(int m=0;m<40;m++){
		if(genA0_Lxy_rdet>bin_edges[m] && genA0_Lxy_rdet<bin_edges[m+1]){
		  count_gam_A0[n][m]++;
		  den_1D_A0_LXY->Fill(genA0_Lxy_rdet);
		  den_1D_A0_LZ->Fill(genA0_Lz_rdet);
		  
		  double denpt = sqrt(genA0_px*genA0_px + genA0_py*genA0_py);
		  den_1D_A0_pT->Fill(denpt);
		  if(abs(genA0_eta) <= 0.9){
		    den_LEp9_1D_A0_pT->Fill(denpt);
		    den_LEp9_1D_A0_LXY->Fill(genA0_Lxy_rdet);
		    den_LEp9_1D_A0_LZ->Fill(genA0_Lz_rdet);
		    /*
		      den_LEp9_1D_A0_mu0_pT->Fill(denpt);
		      den_LEp9_1D_A0_mu0_LXY->Fill(genA0_Lxy_rdet);
		      den_LEp9_1D_A0_mu0_LZ->Fill(genA0_Lz_rdet);
		      
		      den_LEp9_1D_A0_mu1_pT->Fill(denpt);
		      den_LEp9_1D_A0_mu1_LXY->Fill(genA0_Lxy_rdet);
		      den_LEp9_1D_A0_mu1_LZ->Fill(genA0_Lz_rdet);
		    */
		    if(isDiMuonHLTFired){
		      den_Trig_LEp9_1D_A0_pT->Fill(denpt);
		      den_Trig_LEp9_1D_A0_LXY->Fill(genA0_Lxy_rdet);
		      den_Trig_LEp9_1D_A0_LZ->Fill(genA0_Lz_rdet);
		      /*
			den_Trig_LEp9_1D_A0_mu0_pT->Fill(denpt);
			den_Trig_LEp9_1D_A0_mu0_LXY->Fill(genA0_Lxy_rdet);
			den_Trig_LEp9_1D_A0_mu0_LZ->Fill(genA0_Lz_rdet);
			
			den_Trig_LEp9_1D_A0_mu1_pT->Fill(denpt);
			den_Trig_LEp9_1D_A0_mu1_LXY->Fill(genA0_Lxy_rdet);
			den_Trig_LEp9_1D_A0_mu1_LZ->Fill(genA0_Lz_rdet);
		      */
		    }
		    
		    
		  }else{
		    den_Gp9_1D_A0_pT->Fill(denpt);
		    den_Gp9_1D_A0_LXY->Fill(genA0_Lxy_rdet);
		    den_Gp9_1D_A0_LZ->Fill(genA0_Lz_rdet);
		    /*
		      den_Gp9_1D_A0_mu0_pT->Fill(denpt);
		      den_Gp9_1D_A0_mu0_LXY->Fill(genA0_Lxy_rdet);
		      den_Gp9_1D_A0_mu0_LZ->Fill(genA0_Lz_rdet);
		      
		      den_Gp9_1D_A0_mu1_pT->Fill(denpt);
		      den_Gp9_1D_A0_mu1_LXY->Fill(genA0_Lxy_rdet);
		      den_Gp9_1D_A0_mu1_LZ->Fill(genA0_Lz_rdet);
		    */
		    if(isDiMuonHLTFired){
		      den_Trig_Gp9_1D_A0_pT->Fill(denpt);
		      den_Trig_Gp9_1D_A0_LXY->Fill(genA0_Lxy_rdet);
		      den_Trig_Gp9_1D_A0_LZ->Fill(genA0_Lz_rdet);
		      /*
			den_Trig_Gp9_1D_A0_mu0_pT->Fill(denpt);
			den_Trig_Gp9_1D_A0_mu0_LXY->Fill(genA0_Lxy_rdet);
			den_Trig_Gp9_1D_A0_mu0_LZ->Fill(genA0_Lz_rdet);
			
			den_Trig_Gp9_1D_A0_mu1_pT->Fill(denpt);
			den_Trig_Gp9_1D_A0_mu1_LXY->Fill(genA0_Lxy_rdet);
			den_Trig_Gp9_1D_A0_mu1_LZ->Fill(genA0_Lz_rdet);
		      */
		    }
		  }
		  
		  npatm = 0;
		  if(selMu0_eta != -100) npatm++;
		  if(selMu1_eta != -100) npatm++;
		  if(selMu2_eta != -100) npatm++;
		  if(selMu3_eta != -100) npatm++;
		  
		  /// Individual muon efficiencies                                                
		  /*	if(abs(genA0_eta) <= 0.9){
			if(sqrt(My_dPhi(selMu0_phi,genA0_phi)*My_dPhi(selMu0_phi,genA0_phi) + (selMu0_eta - genA0_eta)*(selMu0_eta - genA0Mu0_eta)) < 0.5){ num_LEp9_1D_A0_mu0_LXY->Fill(genA0_Lxy_rdet); num_LEp9_1D_A0_mu0_LZ->Fill(genA0_Lz_rdet);}
			}else{
			
			}
		  */
		  ///	
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
		      dR_A0->Fill(dR1);
		      if(dR1<0.5) match_mu++;
		    }
		    if(match_mu>=2)   {
		      count_rec_A0[n][m]++;
		      num_1D_A0_LXY->Fill(genA0_Lxy_rdet);
		      num_1D_A0_LZ->Fill(genA0_Lz_rdet);
		      double numpt = sqrt(genA0_px*genA0_px + genA0_py*genA0_py);
		      num_1D_A0_pT->Fill(numpt);
		      
		      if(abs(genA0_eta) <= 0.9){
			num_LEp9_1D_A0_pT->Fill(numpt);
			num_LEp9_1D_A0_LXY->Fill(genA0_Lxy_rdet);
			num_LEp9_1D_A0_LZ->Fill(genA0_Lz_rdet);
			
			if(isDiMuonHLTFired){
			  num_Trig_LEp9_1D_A0_pT->Fill(numpt);
			  num_Trig_LEp9_1D_A0_LXY->Fill(genA0_Lxy_rdet);
			  num_Trig_LEp9_1D_A0_LZ->Fill(genA0_Lz_rdet);
			}
			
		      }else{
			num_Gp9_1D_A0_pT->Fill(numpt);
			num_Gp9_1D_A0_LXY->Fill(genA0_Lxy_rdet);
			num_Gp9_1D_A0_LZ->Fill(genA0_Lz_rdet);
			if(isDiMuonHLTFired){
			  num_Trig_Gp9_1D_A0_pT->Fill(numpt);
			  num_Trig_Gp9_1D_A0_LXY->Fill(genA0_Lxy_rdet);
			  num_Trig_Gp9_1D_A0_LZ->Fill(genA0_Lz_rdet);
			}
		      }
		      
		    }
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
		  den_1D_A1_LXY->Fill(genA1_Lxy_rdet);
		  den_1D_A1_LZ->Fill(genA1_Lz_rdet);
		  
		  double denpt = sqrt(genA1_px*genA1_px + genA1_py*genA1_py);
		  den_1D_A1_pT->Fill(denpt);
		  if(abs(genA0_eta) <= 0.9){
		    den_LEp9_1D_A1_pT->Fill(denpt);
		    den_LEp9_1D_A1_LXY->Fill(genA1_Lxy_rdet);
		    den_LEp9_1D_A1_LZ->Fill(genA1_Lz_rdet);
		    if(isDiMuonHLTFired){
		      den_Trig_LEp9_1D_A1_pT->Fill(denpt);
		      den_Trig_LEp9_1D_A1_LXY->Fill(genA1_Lxy_rdet);
		      den_Trig_LEp9_1D_A1_LZ->Fill(genA1_Lz_rdet);
		      
		    }
		    
		  }else{
		    den_Gp9_1D_A1_pT->Fill(denpt);
		    den_Gp9_1D_A1_LXY->Fill(genA1_Lxy_rdet);
		    den_Gp9_1D_A1_LZ->Fill(genA1_Lz_rdet);
		    if(isDiMuonHLTFired){
		      den_Trig_Gp9_1D_A1_pT->Fill(denpt);
		      den_Trig_Gp9_1D_A1_LXY->Fill(genA1_Lxy_rdet);
		      den_Trig_Gp9_1D_A1_LZ->Fill(genA1_Lz_rdet);
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
		      num_1D_A1_LXY->Fill(genA1_Lxy_rdet);
		      num_1D_A1_LZ->Fill(genA1_Lz_rdet);
		      double numpt = sqrt(genA1_px*genA1_px + genA1_py*genA1_py);
		      num_1D_A1_pT->Fill(numpt);
		      if(abs(genA0_eta) <= 0.9){
			num_LEp9_1D_A1_pT->Fill(numpt);
			num_LEp9_1D_A1_LXY->Fill(genA1_Lxy_rdet);
			num_LEp9_1D_A1_LZ->Fill(genA1_Lz_rdet);
			if(isDiMuonHLTFired){
			  num_Trig_LEp9_1D_A1_pT->Fill(numpt);
			  num_Trig_LEp9_1D_A1_LXY->Fill(genA1_Lxy_rdet);
			  num_Trig_LEp9_1D_A1_LZ->Fill(genA1_Lz_rdet);
			}
			
		      }else{
			num_Gp9_1D_A1_pT->Fill(numpt);
			num_Gp9_1D_A1_LXY->Fill(genA1_Lxy_rdet);
			num_Gp9_1D_A1_LZ->Fill(genA1_Lz_rdet);
			if(isDiMuonHLTFired){
			  num_Trig_Gp9_1D_A1_pT->Fill(numpt);
			  num_Trig_Gp9_1D_A1_LXY->Fill(genA1_Lxy_rdet);
			  num_Trig_Gp9_1D_A1_LZ->Fill(genA1_Lz_rdet);
			}
		      }
		      
		    }
		    
		  }
		}
	      }
	    }
	  }
	  
	} //dPhi loop
      }
      ///Test loop
      
      if(is4GenMu8==true){
	Float_t dphi_gD = My_dPhi(genA1_phi,genA0_phi);
	//if(fabs(dphi_gD)>2.5){ 
	for(int n=0;n<20;n++){
	  if(fabs(genA0_Lz_rdet)>bin_edges_Lz[n] && fabs(genA0_Lz_rdet)<bin_edges_Lz[n+1]){
	    for(int m=0;m<40;m++){
	      if(genA0_Lxy_rdet>bin_edges[m] && genA0_Lxy_rdet<bin_edges[m+1]){
		
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
		    dR_vs_dLxy->Fill(dR1, genA0_Lxy_rdet);
		    dPhi_vs_dLxy->Fill(dphi_gD, genA0_Lxy_rdet);
		    
		    dR_vs_dLz->Fill(dR1, genA0_Lz_rdet);
		    dPhi_vs_dLz->Fill(dphi_gD, genA0_Lz_rdet);
		    
		    pt_vs_dPhi->Fill(sqrt(genA0_px*genA0_px + genA0_py*genA0_py),dphi_gD);
		    
		    pt_vs_dLxy->Fill(sqrt(genA0_px*genA0_px + genA0_py*genA0_py),genA0_Lxy_rdet);
		    pt_vs_dLz->Fill(sqrt(genA0_px*genA0_px + genA0_py*genA0_py), genA0_Lz_rdet);
		  }
		}
	      }
	    }
	  }
	}
	
	
	for(int n=0;n<20;n++){
	  if(fabs(genA1_Lz_rdet)>bin_edges_Lz[n] && fabs(genA1_Lz_rdet)<bin_edges_Lz[n+1]){
	    
	    for(int m=0;m<40;m++){
	      if(genA1_Lxy_rdet>bin_edges[m] && genA1_Lxy_rdet<bin_edges[m+1]){
		
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
		    dR_vs_dLxy->Fill(dR1, genA1_Lxy_rdet);
		    dPhi_vs_dLxy->Fill(dphi_gD, genA1_Lxy_rdet);
		    
		    dR_vs_dLz->Fill(dR1, genA1_Lz_rdet);
		    dPhi_vs_dLz->Fill(dphi_gD, genA1_Lz_rdet);}
		  pt_vs_dPhi->Fill(sqrt(genA1_px*genA1_px + genA1_py*genA1_py) ,dphi_gD);
		  pt_vs_dLxy->Fill(sqrt(genA1_px*genA1_px + genA1_py*genA1_py),genA1_Lxy_rdet);
		  pt_vs_dLz->Fill(sqrt(genA1_px*genA1_px + genA1_py*genA1_py), genA1_Lz_rdet);
		  
		  
		}
	      }
	    }
	  }
	}
	
	//} //dPhi loop
      }
      
      //End Test loop
      
      
    } //closing for loop
    myfile->Close();
  }//closing while loop
}//closing method


void makePlots(){
  
  gROOT->SetBatch(true);
  TH2F *den_2D_A0 = new TH2F("den_2D_A0","",20,0,80,40,0.0,80.0);
  TH2F *num_2D_A0 = new TH2F("num_2D_A0","",20,0,80,40,0.0,80.0);
  
  TH2F *eff_2D_A0 = new TH2F("eff_2D_A0","",20,0,80,40,0.0,80.0);
  TH2F *eff_2D_A1 = new TH2F("eff_2D_A1","",20,0,80,40,0.0,80.0);
  
  
  for(int k=0;k<20;k++){
    for(int j=0;j<40;j++){
      
      num_2D_A0->SetBinContent(k+1,j+1,count_rec_A0[k][j]);
      
      den_2D_A0->SetBinContent(k+1,j+1,count_gam_A0[k][j]);
      
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
  
  TString dirRecoEffPlots = "RecoEffPlots_DarkSUSY_2016/";

  TCanvas *effxy = new TCanvas("effxy", "effxy", 700, 500);
  gr1 = new TGraphAsymmErrors(num_1D_A0_LXY, den_1D_A0_LXY);
  gr1->SetTitle("");
  gr1->GetYaxis()->SetTitle("Efficiency");
  gr1->GetXaxis()->SetTitle("L_{xy} [cm]");
  gr1->SetMarkerColor(kRed);
  gr1->SetLineColor(kRed);
  gr1->SetMarkerStyle(21);
  gr1->Draw("ALP");
  
  gr0 = new TGraphAsymmErrors(num_1D_A1_LXY, den_1D_A1_LXY);
  gr0->SetMarkerColor(kBlue);
  gr0->SetLineColor(kBlue);
  gr0->SetMarkerStyle(21);
  gr0->Draw("same");
  
  TLegend *leg = new TLegend(0.1695402,0.1458774,0.2816092,0.4460888);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetTextSize(0.045);
  leg->AddEntry(gr1,"#gamma_{D1}","L");
  leg->AddEntry(gr0,"#gamma_{D2}","L");
  leg->Draw("same");
  
  effxy->SaveAs(dirRecoEffPlots + "Efficiency_1D_LXY.pdf");
  
  TCanvas *effz2 = new TCanvas("effz2", "effz2", 700, 500);
  gr2 = new TGraphAsymmErrors(num_1D_A0_LZ, den_1D_A0_LZ);
  gr2->SetMarkerColor(kRed);
  gr2->SetLineColor(kRed);
  gr2->SetTitle("");
  gr2->GetYaxis()->SetTitle("Efficiency");
  gr2->GetXaxis()->SetTitle("L_{z} [cm]");
  gr2->SetMarkerStyle(21);
  gr2->Draw("ALP");
  
  gr3 = new TGraphAsymmErrors(num_1D_A1_LZ, den_1D_A1_LZ);
  gr3->SetMarkerColor(kBlue);
  gr3->SetLineColor(kBlue);
  gr3->SetMarkerStyle(21);
  gr3->Draw("same");
  
  leg->Draw("same");
  
  effz2->SaveAs(dirRecoEffPlots + "Efficiency_1D_Lz.pdf");
  
  TCanvas *effpt = new TCanvas("effpt", "effpt", 700, 500);
  gr_eff = new TGraphAsymmErrors(num_1D_A0_pT, den_1D_A0_pT);
  gr_eff->SetMarkerColor(kRed);
  gr_eff->SetLineColor(kRed);
  gr_eff->SetTitle("");
  gr_eff->GetYaxis()->SetTitle("Efficiency");
  gr_eff->GetXaxis()->SetTitle("p_{T} [GeV]");
  gr_eff->SetMarkerStyle(21);
  gr_eff->Draw("ALP");
  
  gr_eff2 = new TGraphAsymmErrors(num_1D_A1_pT, den_1D_A1_pT);
  gr_eff2->SetMarkerColor(kBlue);
  gr_eff2->SetLineColor(kBlue);
  gr_eff2->SetMarkerStyle(21);
  gr_eff2->Draw("same");
  
  leg->Draw("same");
  effpt->SaveAs(dirRecoEffPlots + "Efficiency_vs_Gen_pT.pdf");
  
  //Efficiency by Eta plots
  TLine *pixel_1 = new TLine(4.4, 0, 4.4, 1);
  TLine *pixel_2 = new TLine(7.3, 0, 7.3, 1);
  TLine *pixel_3 = new TLine(9.8, 0, 9.8, 1);
  TLine *tracker_innerbarrel = new TLine(23.9, 0, 23.9, 1); 
  TLine *tracker_outerbarrel = new TLine(60.5, 0, 60.5, 1);
  
  TLine *pixel_endcap_1 = new TLine(34.5, 0, 34.5, 1);
  TLine *pixel_endcap_2 = new TLine(46.5, 0, 46.5, 1);
  
  //Blue Lines
  pixel_1->SetLineStyle(2);
  pixel_2->SetLineStyle(2);
  pixel_3->SetLineStyle(2);
  pixel_endcap_1->SetLineStyle(2);
  pixel_endcap_2->SetLineStyle(2);
  
  pixel_1->SetLineColor(kBlue);
  pixel_2->SetLineColor(kBlue);
  pixel_3->SetLineColor(kBlue);
  pixel_endcap_1->SetLineColor(kBlue);
  pixel_endcap_2->SetLineColor(kBlue);
  
  //Green Lines
  tracker_innerbarrel->SetLineStyle(2);
  tracker_outerbarrel->SetLineStyle(2);
  
  tracker_innerbarrel->SetLineColor(kGreen+1);
  tracker_outerbarrel->SetLineColor(kGreen+1);
  
  TCanvas *eta_lxy = new TCanvas("eta_lxy", "eta_lxy", 700, 500);
  TMultiGraph *mg_lxy = new TMultiGraph();
  
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
  
  TLegend *etaleg = new TLegend(0.6982759,0.6701903,0.8979885,0.8794926);
  etaleg->SetBorderSize(0);
  etaleg->SetFillColor(0);
  etaleg->SetTextSize(0.03171247);
  etaleg->AddEntry(gr_a0_le_lxy,"|#eta_{#gamma_{D}}| #leq 0.9 A0","L");
  etaleg->AddEntry(gr_a0_g_lxy, "|#eta_{#gamma_{D}}| > 0.9 A0","L");
  etaleg->AddEntry(gr_a1_le_lxy,"|#eta_{#gamma_{D}}| #leq 0.9 A1","L");
  etaleg->AddEntry(gr_a1_g_lxy, "|#eta_{#gamma_{D}}| > 0.9 A1","L");
  mg_lxy->Draw("ALP");
  mg_lxy->GetXaxis()->SetTitle("L_{xy} [cm]");
  mg_lxy->GetYaxis()->SetTitle("Efficiency");
  mg_lxy->SetMinimum(0.);
  mg_lxy->SetMaximum(1.);
  etaleg->Draw("same");
  
  pixel_1->Draw("same");
  pixel_2->Draw("same");
  pixel_3->Draw("same");
  tracker_innerbarrel->Draw("same");
  tracker_outerbarrel->Draw("same");
  
  
  eta_lxy->SaveAs(dirRecoEffPlots + "EfficiencyByEta_vs_Lxy.pdf");
  cout << "Checkpoint 1" << endl;
  //eta_lxy->SaveAs(dirRecoEffPlots + "EfficiencyByEta_vs_Lxy.C");
  
  cout << "Checkpoint 2" << endl;
  
  TCanvas *eta_lz = new TCanvas("eta_lz", "eta_lz", 700, 500);
  TMultiGraph *mg_lz = new TMultiGraph();
  
  gr_a0_le_lz = new TGraphAsymmErrors(num_LEp9_1D_A0_LZ, den_LEp9_1D_A0_LZ);
  gr_a1_le_lz = new TGraphAsymmErrors(num_LEp9_1D_A1_LZ, den_LEp9_1D_A1_LZ);
  gr_a1_g_lz = new TGraphAsymmErrors(num_Gp9_1D_A1_LZ, den_Gp9_1D_A1_LZ);
  gr_a0_g_lz = new TGraphAsymmErrors(num_Gp9_1D_A0_LZ, den_Gp9_1D_A0_LZ);
  cout << "Checkpoint 3" << endl;
  
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
  mg_lz->GetXaxis()->SetTitle("L_{z} [cm]");
  mg_lz->GetYaxis()->SetTitle("Efficiency");
  mg_lz->SetMinimum(0.);
  mg_lz->SetMaximum(1.);
  
  pixel_endcap_1->Draw("same");
  pixel_endcap_2->Draw("same");
  
  etaleg->Draw("same");
  eta_lz->SaveAs(dirRecoEffPlots + "EfficiencyByEta_vs_Lz.pdf");
  eta_lz->SaveAs(dirRecoEffPlots + "EfficiencyByEta_vs_Lz.C");
  
  //Eta plots including Trigger
  
  TCanvas *eta_lxy_trig = new TCanvas("eta_lxy_trig", "eta_lxy_trig", 700, 500);
  TMultiGraph *mg_lxy_trig = new TMultiGraph();
  
  gr_a0_le_lxy_trig = new TGraphAsymmErrors(num_Trig_LEp9_1D_A0_LXY, den_Trig_LEp9_1D_A0_LXY);
  gr_a1_le_lxy_trig = new TGraphAsymmErrors(num_Trig_LEp9_1D_A1_LXY, den_Trig_LEp9_1D_A1_LXY);
  gr_a1_g_lxy_trig = new TGraphAsymmErrors(num_Trig_Gp9_1D_A1_LXY, den_Trig_Gp9_1D_A1_LXY);
  gr_a0_g_lxy_trig = new TGraphAsymmErrors(num_Trig_Gp9_1D_A0_LXY, den_Trig_Gp9_1D_A0_LXY);
  
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
  
  
  eta_lxy_trig->SaveAs(dirRecoEffPlots + "EfficiencyByEta_vs_Lxy_Trig.pdf");
  //eta_lxy_trig->SaveAs(dirRecoEffPlots + "EfficiencyByEta_vs_Lxy_Trig.C");
  
  TCanvas *eta_lz_trig = new TCanvas("eta_lz_trig", "eta_lz_trig", 700, 500);
  TMultiGraph *mg_lz_trig = new TMultiGraph();
  
  gr_a0_le_lz_trig = new TGraphAsymmErrors(num_Trig_LEp9_1D_A0_LZ, den_Trig_LEp9_1D_A0_LZ);
  gr_a1_le_lz_trig = new TGraphAsymmErrors(num_Trig_LEp9_1D_A1_LZ, den_Trig_LEp9_1D_A1_LZ);
  gr_a1_g_lz_trig = new TGraphAsymmErrors(num_Trig_Gp9_1D_A1_LZ, den_Trig_Gp9_1D_A1_LZ);
  gr_a0_g_lz_trig = new TGraphAsymmErrors(num_Trig_Gp9_1D_A0_LZ, den_Trig_Gp9_1D_A0_LZ);
  
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
  mg_lz_trig->GetXaxis()->SetTitle("L_{z} [cm]");
  mg_lz_trig->GetYaxis()->SetTitle("Efficiency");
  mg_lz_trig->SetMinimum(0.);
  mg_lz_trig->SetMaximum(1.);
  
  
  pixel_endcap_1->Draw("same");
  pixel_endcap_2->Draw("same");
  
  etaleg->Draw("same");
  eta_lz_trig->SaveAs(dirRecoEffPlots + "EfficiencyByEta_vs_Lz_Trig.pdf");
  //eta_lz_trig->SaveAs(dirRecoEffPlots + "EfficiencyByEta_vs_Lz_Trig.C");
  
  
  /*
    TCanvas *effxy0 = new TCanvas("effxy0", "effxy0", 700, 500);
    gr4 = new TGraphAsymmErrors(num_1D_A1_LXY, den_1D_A1_LXY);
    gr4->SetTitle("1D Efficiency #gamma_{D2} L_{xy}");
    gr4->GetYaxis()->SetTitle("Efficiency");
    gr4->GetXaxis()->SetTitle("L_{xy} [cm]");
    gr4->SetMarkerColor(kBlue);
    gr4->SetMarkerStyle(21);
    gr4->Draw("ALP");
    
    TCanvas *effz = new TCanvas("effz", "effz", 700, 500);
    gr5 = new TGraphAsymmErrors(num_1D_A1_LZ, den_1D_A1_LZ);
    gr5->SetTitle("1D Efficiency #gamma_{D2} L_{z}");
    gr5->SetMarkerColor(4);
    gr5->SetMarkerStyle(21);
    gr5->Draw("ALP");
    
    TCanvas *effxy3 = new TCanvas("effxy3", "effxy3", 700, 500);
    gr6 = new TGraphAsymmErrors(num_1D_A0_LXY, den_1D_A0_LXY);
    gr6->SetTitle("1D Efficiency #gamma_{D1} L_{xy}");
    gr6->SetMarkerColor(4);
    gr6->SetMarkerStyle(21);
    gr6->Draw("ALP");
    
    TCanvas *effz3 = new TCanvas("effz3", "effz3", 700, 500);
    gr7 = new TGraphAsymmErrors(num_1D_A0_LZ, den_1D_A0_LZ);
    gr7->SetTitle("1D Efficiency #gamma_{D1} L_{z}");
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
  
  TLine *etaline_11 = new TLine(0, 0, 80, 80*tan(0.7723));
  TLine *etaline_21 = new TLine(0, 0, 80, 80*tan(0.46964244059));
  
  etaline_11->SetLineStyle(1);
  etaline_21->SetLineStyle(2);
  
  etaline_11->SetLineColor(kBlack);
  etaline_21->SetLineColor(kBlack);


  TCanvas *c = new TCanvas("c","c",700,500);
  c->SetRightMargin(0.15);
  eff_2D_A0->GetYaxis()->SetTitle("#gamma_{D1} L_{xy} [cm]");
  eff_2D_A0->GetXaxis()->SetTitle("#gamma_{D1} |L_{z}| [cm]");
  eff_2D_A0->GetZaxis()->SetTitle("#varepsilon_{Full}/#alpha_{GEN}");
  gStyle->SetOptStat(0);
  //    eff_2D_A0->SetContour((sizeof(levels)/sizeof(Double_t)), levels);
  eff_2D_A0->Draw("COLZ");
  
  etaline_11->Draw("same");
  etaline_21->Draw("same");

  c->SaveAs(dirRecoEffPlots + "eff_2D_LxyLz_A0.pdf","recreate");
  //I am not quite sure what this did...    
  //if(l==0) c->SaveAs(dirRecoEffPlots + "eff_2D_LxyLz_A0_ct05.pdf","recreate");
  
  
  
  
  TCanvas *c1 = new TCanvas("c1","c1",700,500);
  c1->SetRightMargin(0.15);
  eff_2D_A1->GetYaxis()->SetTitle("#gamma_{D2} L_{xy} [cm]");
  eff_2D_A1->GetXaxis()->SetTitle("|#gamma_{D2} L_{z}| [cm]");
  eff_2D_A1->GetZaxis()->SetTitle("#varepsilon_{Full}/#alpha_{GEN}");
  gStyle->SetOptStat(0);
  eff_2D_A1->Draw("COLZ");

  etaline_11->Draw("same");
  etaline_21->Draw("same");

  c1->SaveAs(dirRecoEffPlots + "eff_2D_LxyLz_A1.pdf","recreate");
  //I am not quite sure what this did...    
  //if(l==0) c1->SaveAs(dirRecoEffPlots + "eff_2D_LxyLz_A1_ct05.pdf","recreate");
  
}//closing method

void SD_eff_pergramD2DLxyLz()
{
  makeCounters();
  
  std::vector< std::vector<string> > DarkSUSY_mH_125_mGammaD_v;
  readTextFileWithSamples("DarkSUSY_All_2016.txt", DarkSUSY_mH_125_mGammaD_v);

  for(const auto& v: DarkSUSY_mH_125_mGammaD_v) create_eff_pergamD2DLxyLz(v);

  makePlots();  
  SD->Write();
}
