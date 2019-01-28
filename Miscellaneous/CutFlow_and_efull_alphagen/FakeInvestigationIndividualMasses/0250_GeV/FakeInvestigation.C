#include <iostream>
using namespace std;
#include <algorithm>    // std::max
#include <stdlib.h>
#include <iomanip>
#include "TMath.h"
#include <math.h>
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>
#include "TChain.h"
#include "TGraphErrors.h" 
#include "TCollection.h"
#include "TSystemFile.h"
#include "TSystemDirectory.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TChainElement.h" 
#include "TStyle.h"

//============= Global Variables ===========================//
TFile *BAM = new TFile("erec_alphagen_FittedVTX_0250_GeV.root","RECREATE");

//Plot initialization
//{{{
TH1F *Real_Gen_Lxy = new TH1F("Real_Gen_Lxy", "Real_Gen_Lxy", 400, 0, 80 );
TH1F *Real_Gen_Lz = new TH1F("Real_Gen_Lz", "Real_Gen_Lz", 400, 0, 80 );
TH1F *Real_Gen_Eta = new TH1F("Real_Gen_Eta", "Real_Gen_Eta", 500, -5, 5);
TH1F *Real_Gen_Phi = new TH1F("Real_Gen_Phi", "Real_Gen_Phi", 340, -3.4, 3.4);
TH1F *Real_Gen_pT = new TH1F("Real_Gen_pT", "Real_Gen_pT", 100, 0, 100);
TH2F *Real_Gen_MassCompatability = new TH2F("Real_Gen_MassCompatability","Real_Gen_MassCompatability", 100, 0, 10, 100, 0, 10);
TH2F *Real_Gen_pT_vs_Lxy = new TH2F("Real_Gen_pT_vs_Lxy", "Real_Gen_pT_vs_Lxy", 100,0,100,400,0,80);

TH1F *Real_Reco_Lxy = new TH1F("Real_Reco_Lxy", "Real_Reco_Lxy", 400, 0, 80 );
TH1F *Real_Reco_Eta = new TH1F("Real_Reco_Eta", "Real_Reco_Eta", 500, -5, 5);
TH1F *Real_Reco_Phi = new TH1F("Real_Reco_Phi", "Real_Reco_Phi", 340, -3.4, 3.4);
TH1F *Real_Reco_pT = new TH1F("Real_Reco_pT", "Real_Reco_pT", 100, 0, 100);
TH2F *Real_Reco_MassCompatability = new TH2F("Real_Reco_MassCompatability","Real_Reco_MassCompatability", 100, 0, 10, 100, 0, 10);
TH2F *Real_Reco_pT_vs_Lxy = new TH2F("Real_Reco_pT_vs_Lxy", "Real_Reco_pT_vs_Lxy", 100,0,100,400,0,80);

TH1F *Fake_Gen_Lxy = new TH1F("Fake_Gen_Lxy", "Fake_Gen_Lxy", 400, 0, 80 );
TH1F *Fake_Gen_Lz = new TH1F("Fake_Gen_Lz", "Fake_Gen_Lz", 400, 0, 80 );
TH1F *Fake_Gen_Eta = new TH1F("Fake_Gen_Eta", "Fake_Gen_Eta", 500, -5, 5);
TH1F *Fake_Gen_Phi = new TH1F("Fake_Gen_Phi", "Fake_Gen_Phi", 340, -3.4, 3.4);
TH1F *Fake_Gen_pT = new TH1F("Fake_Gen_pT", "Fake_Gen_pT", 100, 0, 100);
TH2F *Fake_Gen_MassCompatability = new TH2F("Fake_Gen_MassCompatability","Fake_Gen_MassCompatability", 100, 0, 10, 100, 0, 10);
TH2F *Fake_Gen_pT_vs_Lxy = new TH2F("Fake_Gen_pT_vs_Lxy", "Fake_Gen_pT_vs_Lxy", 100,0,100,400,0,80);

TH1F *Fake_Reco_Lxy = new TH1F("Fake_Reco_Lxy", "Fake_Reco_Lxy", 400, 0, 80 );
TH1F *Fake_Reco_Eta = new TH1F("Fake_Reco_Eta", "Fake_Reco_Eta", 500, -5, 5);
TH1F *Fake_Reco_Phi = new TH1F("Fake_Reco_Phi", "Fake_Reco_Phi", 340, -3.4, 3.4);
TH1F *Fake_Reco_pT = new TH1F("Fake_Reco_pT", "Fake_Reco_pT", 100, 0, 100);
TH2F *Fake_Reco_MassCompatability = new TH2F("Fake_Reco_MassCompatability","Fake_Reco_MassCompatability", 100, 0, 10, 100, 0, 10);
TH2F *Fake_Reco_pT_vs_Lxy = new TH2F("Fake_Reco_pT_vs_Lxy", "Fake_Reco_pT_vs_Lxy", 100,0,100,400,0,80);

TH1F *Real_dimuon1_Gen_Lxy = new TH1F("Real_dimuon1_Gen_Lxy", "Real_dimuon1_Gen_Lxy", 400, 0, 80 );
TH1F *Real_dimuon1_Gen_Lz = new TH1F("Real_dimuon1_Gen_Lz", "Real_dimuon1_Gen_Lz", 400, 0, 80 );
TH1F *Real_dimuon1_Gen_Eta = new TH1F("Real_dimuon1_Gen_Eta", "Real_dimuon1_Gen_Eta", 500, -5, 5);
TH1F *Real_dimuon1_Gen_Phi = new TH1F("Real_dimuon1_Gen_Phi", "Real_dimuon1_Gen_Phi", 340, -3.4, 3.4);
TH1F *Real_dimuon1_Gen_pT = new TH1F("Real_dimuon1_Gen_pT", "Real_dimuon1_Gen_pT", 100, 0, 100);
TH2F *Real_dimuon1_Gen_MassCompatability = new TH2F("Real_dimuon1_Gen_MassCompatability","Real_dimuon1_Gen_MassCompatability", 100, 0, 10, 100, 0, 10);
TH2F *Real_dimuon1_Gen_pT_vs_Lxy = new TH2F("Real_dimuon1_Gen_pT_vs_Lxy", "Real_dimuon1_Gen_pT_vs_Lxy", 100,0,100,400,0,80);

TH1F *Real_dimuon1_Reco_Lxy = new TH1F("Real_dimuon1_Reco_Lxy", "Real_dimuon1_Reco_Lxy", 400, 0, 80 );
TH1F *Real_dimuon1_Reco_Eta = new TH1F("Real_dimuon1_Reco_Eta", "Real_dimuon1_Reco_Eta", 500, -5, 5);
TH1F *Real_dimuon1_Reco_Phi = new TH1F("Real_dimuon1_Reco_Phi", "Real_dimuon1_Reco_Phi", 340, -3.4, 3.4);
TH1F *Real_dimuon1_Reco_pT = new TH1F("Real_dimuon1_Reco_pT", "Real_dimuon1_Reco_pT", 100, 0, 100); 
TH2F *Real_dimuon1_Reco_MassCompatability = new TH2F("Real_dimuon1_Reco_MassCompatability","Real_dimuon1_Reco_MassCompatability", 100, 0, 10, 100, 0, 10);
TH2F *Real_dimuon1_Reco_pT_vs_Lxy = new TH2F("Real_dimuon1_Reco_pT_vs_Lxy", "Real_dimuon1_Reco_pT_vs_Lxy", 100,0,100,400,0,80);

TH1F *Fake_dimuon1_Gen_Lxy = new TH1F("Fake_dimuon1_Gen_Lxy", "Fake_dimuon1_Gen_Lxy", 400, 0, 80 );
TH1F *Fake_dimuon1_Gen_Lz = new TH1F("Fake_dimuon1_Gen_Lz", "Fake_dimuon1_Gen_Lz", 400, 0, 80 ); 
TH1F *Fake_dimuon1_Gen_Eta = new TH1F("Fake_dimuon1_Gen_Eta", "Fake_dimuon1_Gen_Eta", 500, -5, 5);
TH1F *Fake_dimuon1_Gen_Phi = new TH1F("Fake_dimuon1_Gen_Phi", "Fake_dimuon1_Gen_Phi", 340, -3.4, 3.4);
TH1F *Fake_dimuon1_Gen_pT = new TH1F("Fake_dimuon1_Gen_pT", "Fake_dimuon1_Gen_pT", 100, 0, 100); 
TH2F *Fake_dimuon1_Gen_MassCompatability = new TH2F("Fake_dimuon1_Gen_MassCompatability","Fake_dimuon1_Gen_MassCompatability", 100, 0, 10, 100, 0, 10);
TH2F *Fake_dimuon1_Gen_pT_vs_Lxy = new TH2F("Fake_dimuon1_Gen_pT_vs_Lxy", "Fake_dimuon1_Gen_pT_vs_Lxy", 100,0,100,400,0,80);

TH1F *Fake_dimuon1_Reco_Lxy = new TH1F("Fake_dimuon1_Reco_Lxy", "Fake_dimuon1_Reco_Lxy", 400, 0, 80 );
TH1F *Fake_dimuon1_Reco_Eta = new TH1F("Fake_dimuon1_Reco_Eta", "Fake_dimuon1_Reco_Eta", 500, -5, 5);
TH1F *Fake_dimuon1_Reco_Phi = new TH1F("Fake_dimuon1_Reco_Phi", "Fake_dimuon1_Reco_Phi", 340, -3.4, 3.4);
TH1F *Fake_dimuon1_Reco_pT = new TH1F("Fake_dimuon1_Reco_pT", "Fake_dimuon1_Reco_pT", 100, 0, 100); 
TH2F *Fake_dimuon1_Reco_MassCompatability = new TH2F("Fake_dimuon1_Reco_MassCompatability","Fake_dimuon1_Reco_MassCompatability", 100, 0, 10, 100, 0, 10);
TH2F *Fake_dimuon1_Reco_pT_vs_Lxy = new TH2F("Fake_dimuon1_Reco_pT_vs_Lxy", "Fake_dimuon1_Reco_pT_vs_Lxy", 100,0,100,400,0,80);

TH1F *Real_dimuon2_Gen_Lxy = new TH1F("Real_dimuon2_Gen_Lxy", "Real_dimuon2_Gen_Lxy", 400, 0, 80 );
TH1F *Real_dimuon2_Gen_Lz = new TH1F("Real_dimuon2_Gen_Lz", "Real_dimuon2_Gen_Lz", 400, 0, 80 );
TH1F *Real_dimuon2_Gen_Eta = new TH1F("Real_dimuon2_Gen_Eta", "Real_dimuon2_Gen_Eta", 500, -5, 5);
TH1F *Real_dimuon2_Gen_Phi = new TH1F("Real_dimuon2_Gen_Phi", "Real_dimuon2_Gen_Phi", 340, -3.4, 3.4);
TH1F *Real_dimuon2_Gen_pT = new TH1F("Real_dimuon2_Gen_pT", "Real_dimuon2_Gen_pT", 100, 0, 100);
TH2F *Real_dimuon2_Gen_MassCompatability = new TH2F("Real_dimuon2_Gen_MassCompatability","Real_dimuon2_Gen_MassCompatability", 100, 0, 10, 100, 0, 10);
TH2F *Real_dimuon2_Gen_pT_vs_Lxy = new TH2F("Real_dimuon2_Gen_pT_vs_Lxy", "Real_dimuon2_Gen_pT_vs_Lxy", 100,0,100,400,0,80);

TH1F *Real_dimuon2_Reco_Lxy = new TH1F("Real_dimuon2_Reco_Lxy", "Real_dimuon2_Reco_Lxy", 400, 0, 80 );
TH1F *Real_dimuon2_Reco_Eta = new TH1F("Real_dimuon2_Reco_Eta", "Real_dimuon2_Reco_Eta", 500, -5, 5);
TH1F *Real_dimuon2_Reco_Phi = new TH1F("Real_dimuon2_Reco_Phi", "Real_dimuon2_Reco_Phi", 340, -3.4, 3.4);
TH1F *Real_dimuon2_Reco_pT = new TH1F("Real_dimuon2_Reco_pT", "Real_dimuon2_Reco_pT", 100, 0, 100); 
TH2F *Real_dimuon2_Reco_MassCompatability = new TH2F("Real_dimuon2_Reco_MassCompatability","Real_dimuon2_Reco_MassCompatability", 100, 0, 10, 100, 0, 10);
TH2F *Real_dimuon2_Reco_pT_vs_Lxy = new TH2F("Real_dimuon2_Reco_pT_vs_Lxy", "Real_dimuon2_Reco_pT_vs_Lxy", 100,0,100,400,0,80);

TH1F *Fake_dimuon2_Gen_Lxy = new TH1F("Fake_dimuon2_Gen_Lxy", "Fake_dimuon2_Gen_Lxy", 400, 0, 80 );
TH1F *Fake_dimuon2_Gen_Lz = new TH1F("Fake_dimuon2_Gen_Lz", "Fake_dimuon2_Gen_Lz", 400, 0, 80 ); 
TH1F *Fake_dimuon2_Gen_Eta = new TH1F("Fake_dimuon2_Gen_Eta", "Fake_dimuon2_Gen_Eta", 500, -5, 5);
TH1F *Fake_dimuon2_Gen_Phi = new TH1F("Fake_dimuon2_Gen_Phi", "Fake_dimuon2_Gen_Phi", 340, -3.4, 3.4);
TH1F *Fake_dimuon2_Gen_pT = new TH1F("Fake_dimuon2_Gen_pT", "Fake_dimuon2_Gen_pT", 100, 0, 100); 
TH2F *Fake_dimuon2_Gen_MassCompatability = new TH2F("Fake_dimuon2_Gen_MassCompatability","Fake_dimuon2_Gen_MassCompatability", 100, 0, 10, 100, 0, 10);
TH2F *Fake_dimuon2_Gen_pT_vs_Lxy = new TH2F("Fake_dimuon2_Gen_pT_vs_Lxy", "Fake_dimuon2_Gen_pT_vs_Lxy", 100,0,100,400,0,80);

TH1F *Fake_dimuon2_Reco_Lxy = new TH1F("Fake_dimuon2_Reco_Lxy", "Fake_dimuon2_Reco_Lxy", 400, 0, 80 );
TH1F *Fake_dimuon2_Reco_Eta = new TH1F("Fake_dimuon2_Reco_Eta", "Fake_dimuon2_Reco_Eta", 500, -5, 5);
TH1F *Fake_dimuon2_Reco_Phi = new TH1F("Fake_dimuon2_Reco_Phi", "Fake_dimuon2_Reco_Phi", 340, -3.4, 3.4);
TH1F *Fake_dimuon2_Reco_pT = new TH1F("Fake_dimuon2_Reco_pT", "Fake_dimuon2_Reco_pT", 100, 0, 100); 
TH2F *Fake_dimuon2_Reco_MassCompatability = new TH2F("Fake_dimuon2_Reco_MassCompatability","Fake_dimuon2_Reco_MassCompatability", 100, 0, 10, 100, 0, 10);
TH2F *Fake_dimuon2_Reco_pT_vs_Lxy = new TH2F("Fake_dimuon2_Reco_pT_vs_Lxy", "Fake_dimuon2_Reco_pT_vs_Lxy", 100,0,100,400,0,80);

//Eta residuals
TH1F *Fake_dimuon1_EtaResidual = new TH1F("Fake_dimuon1_EtaResidual", "Fake_dimuon1_EtaResidual", 10, -0.1, 0.1);
TH1F *Fake_dimuon2_EtaResidual = new TH1F("Fake_dimuon2_EtaResidual", "Fake_dimuon2_EtaResidual", 10, -0.1, 0.1);

TH2F *Fake_dimuon1_EtaResidual_vs_Eta = new TH2F("Fake_dimuon1_EtaResidual_vs_Eta", "Fake_dimuon1_EtaResidual_vs_Eta", 500, -5, 5, 10, -0.1, 0.1);
TH2F *Fake_dimuon2_EtaResidual_vs_Eta = new TH2F("Fake_dimuon2_EtaResidual_vs_Eta", "Fake_dimuon2_EtaResidual_vs_Eta",500, -5, 5, 10, -0.1, 0.1);

TH2F *Real_dimuon1_EtaResidual_vs_Eta = new TH2F("Real_dimuon1_EtaResidual_vs_Eta", "Real_dimuon1_EtaResidual_vs_Eta",500, -5, 5, 10, -0.1, 0.1);
TH2F *Real_dimuon2_EtaResidual_vs_Eta = new TH2F("Real_dimuon2_EtaResidual_vs_Eta", "Real_dimuon2_EtaResidual_vs_Eta",500, -5, 5, 10, -0.1, 0.1);
TH1F *Real_dimuon1_EtaResidual = new TH1F("Real_dimuon1_EtaResidual", "Real_dimuon1_EtaResidual", 10, -0.1, 0.1);
TH1F *Real_dimuon2_EtaResidual = new TH1F("Real_dimuon2_EtaResidual", "Real_dimuon2_EtaResidual", 10, -0.1, 0.1);

TH2F *Fake_dimuon1_EtaResidual_vs_Lxy = new TH2F("Fake_dimuon1_EtaResidual_vs_Lxy", "Fake_dimuon1_EtaResidual_vs_Lxy", 150, 0, 30, 10, -0.1, 0.1);
TH2F *Fake_dimuon2_EtaResidual_vs_Lxy = new TH2F("Fake_dimuon2_EtaResidual_vs_Lxy", "Fake_dimuon2_EtaResidual_vs_Lxy",150, 0, 30, 10, -0.1, 0.1);

TH2F *Real_dimuon1_EtaResidual_vs_Lxy = new TH2F("Real_dimuon1_EtaResidual_vs_Lxy", "Real_dimuon1_EtaResidual_vs_Lxy",150, 0, 30, 10, -0.1, 0.1);
TH2F *Real_dimuon2_EtaResidual_vs_Lxy = new TH2F("Real_dimuon2_EtaResidual_vs_Lxy", "Real_dimuon2_EtaResidual_vs_Lxy",150, 0, 30, 10, -0.1, 0.1);


//Phi residuals
TH1F *Fake_dimuon1_PhiResidual = new TH1F("Fake_dimuon1_PhiResidual", "Fake_dimuon1_PhiResidual", 700, -7, 7);
TH1F *Fake_dimuon2_PhiResidual = new TH1F("Fake_dimuon2_PhiResidual", "Fake_dimuon2_PhiResidual", 700, -7, 7);
TH1F *Real_dimuon1_PhiResidual = new TH1F("Real_dimuon1_PhiResidual", "Real_dimuon1_PhiResidual", 700, -7, 7);
TH1F *Real_dimuon2_PhiResidual = new TH1F("Real_dimuon2_PhiResidual", "Real_dimuon2_PhiResidual", 700, -7, 7);

TH2F *Fake_dimuon1_PhiResidual_vs_Phi = new TH2F("Fake_dimuon1_PhiResidual_vs_Phi", "Fake_dimuon1_PhiResidual_vs_Phi", 400, -4, 4, 700, -7, 7);
TH2F *Fake_dimuon2_PhiResidual_vs_Phi = new TH2F("Fake_dimuon2_PhiResidual_vs_Phi", "Fake_dimuon2_PhiResidual_vs_Phi",400, -4, 4, 700, -7, 7);
TH2F *Real_dimuon1_PhiResidual_vs_Phi = new TH2F("Real_dimuon1_PhiResidual_vs_Phi", "Real_dimuon1_PhiResidual_vs_Phi",400, -4, 4, 700, -7, 7);
TH2F *Real_dimuon2_PhiResidual_vs_Phi = new TH2F("Real_dimuon2_PhiResidual_vs_Phi", "Real_dimuon2_PhiResidual_vs_Phi",400, -4, 4, 700, -7, 7);


TH2F *Fake_dimuon1_PhiResidual_vs_Lxy = new TH2F("Fake_dimuon1_PhiResidual_vs_Lxy", "Fake_dimuon1_PhiResidual_vs_Lxy", 150, 0, 30, 700, -7, 7);
TH2F *Fake_dimuon2_PhiResidual_vs_Lxy = new TH2F("Fake_dimuon2_PhiResidual_vs_Lxy", "Fake_dimuon2_PhiResidual_vs_Lxy",150, 0, 30, 700, -7, 7);


TH2F *Real_dimuon1_PhiResidual_vs_Lxy = new TH2F("Real_dimuon1_PhiResidual_vs_Lxy", "Real_dimuon1_PhiResidual_vs_Lxy",150, 0, 30, 700, -7, 7);
TH2F *Real_dimuon2_PhiResidual_vs_Lxy = new TH2F("Real_dimuon2_PhiResidual_vs_Lxy", "Real_dimuon2_PhiResidual_vs_Lxy",150, 0, 30, 700, -7, 7);

//Lxy residuals
TH1F *Fake_dimuon1_LxyResidual = new TH1F("Fake_dimuon1_LxyResidual", "Fake_dimuon1_LxyResidual", 300, -30, 30);
TH1F *Fake_dimuon2_LxyResidual = new TH1F("Fake_dimuon2_LxyResidual", "Fake_dimuon2_LxyResidual", 300, -30, 30);
TH1F *Real_dimuon1_LxyResidual = new TH1F("Real_dimuon1_LxyResidual", "Real_dimuon1_LxyResidual", 300, -30, 30);
TH1F *Real_dimuon2_LxyResidual = new TH1F("Real_dimuon2_LxyResidual", "Real_dimuon2_LxyResidual", 300, -30, 30);

TH2F *Fake_dimuon1_LxyResidual_vs_Lxy = new TH2F("Fake_dimuon1_LxyResidual_vs_Lxy", "Fake_dimuon1_LxyResidual_vs_Lxy", 150, 0, 30, 300, -30, 30);
TH2F *Fake_dimuon2_LxyResidual_vs_Lxy = new TH2F("Fake_dimuon2_LxyResidual_vs_Lxy", "Fake_dimuon2_LxyResidual_vs_Lxy",150, 0, 30, 300, -30, 30);
TH2F *Real_dimuon1_LxyResidual_vs_Lxy = new TH2F("Real_dimuon1_LxyResidual_vs_Lxy", "Real_dimuon1_LxyResidual_vs_Lxy",150, 0, 30, 300, -30, 30);
TH2F *Real_dimuon2_LxyResidual_vs_Lxy = new TH2F("Real_dimuon2_LxyResidual_vs_Lxy", "Real_dimuon2_LxyResidual_vs_Lxy",150, 0, 30, 300, -30, 30);


//Individual Muon Residuals

TH1F *Real_Muon_00_Eta_Residual = new TH1F("Real_Muon_00_Eta_Residual", "Real_Muon_00_Eta_Residual", 10, -0.1, 0.1);
TH1F *Real_Muon_01_Eta_Residual = new TH1F("Real_Muon_01_Eta_Residual", "Real_Muon_01_Eta_Residual", 10, -0.1, 0.1);
TH1F *Real_Muon_10_Eta_Residual = new TH1F("Real_Muon_10_Eta_Residual", "Real_Muon_10_Eta_Residual", 10, -0.1, 0.1);
TH1F *Real_Muon_11_Eta_Residual = new TH1F("Real_Muon_11_Eta_Residual", "Real_Muon_11_Eta_Residual", 10, -0.1, 0.1);

TH1F *Fake_Muon_00_Eta_Residual = new TH1F("Fake_Muon_00_Eta_Residual", "Fake_Muon_00_Eta_Residual", 10, -0.1, 0.1);
TH1F *Fake_Muon_01_Eta_Residual = new TH1F("Fake_Muon_01_Eta_Residual", "Fake_Muon_01_Eta_Residual", 10, -0.1, 0.1);
TH1F *Fake_Muon_10_Eta_Residual = new TH1F("Fake_Muon_10_Eta_Residual", "Fake_Muon_10_Eta_Residual", 10, -0.1, 0.1);
TH1F *Fake_Muon_11_Eta_Residual = new TH1F("Fake_Muon_11_Eta_Residual", "Fake_Muon_11_Eta_Residual", 10, -0.1, 0.1);

TH1F *Real_Muon_00_Phi_Residual = new TH1F("Real_Muon_00_Phi_Residual", "Real_Muon_00_Phi_Residual", 700, -7, 7);
TH1F *Real_Muon_01_Phi_Residual = new TH1F("Real_Muon_01_Phi_Residual", "Real_Muon_01_Phi_Residual", 700, -7, 7);
TH1F *Real_Muon_10_Phi_Residual = new TH1F("Real_Muon_10_Phi_Residual", "Real_Muon_10_Phi_Residual", 700, -7, 7);
TH1F *Real_Muon_11_Phi_Residual = new TH1F("Real_Muon_11_Phi_Residual", "Real_Muon_11_Phi_Residual", 700, -7, 7);

TH1F *Fake_Muon_00_Phi_Residual = new TH1F("Fake_Muon_00_Phi_Residual", "Fake_Muon_00_Phi_Residual", 700, -7, 7);
TH1F *Fake_Muon_01_Phi_Residual = new TH1F("Fake_Muon_01_Phi_Residual", "Fake_Muon_01_Phi_Residual", 700, -7, 7);
TH1F *Fake_Muon_10_Phi_Residual = new TH1F("Fake_Muon_10_Phi_Residual", "Fake_Muon_10_Phi_Residual", 700, -7, 7);
TH1F *Fake_Muon_11_Phi_Residual = new TH1F("Fake_Muon_11_Phi_Residual", "Fake_Muon_11_Phi_Residual", 700, -7, 7);

TH2F *Real_Muon_00_Eta_Residual_vs_Eta = new TH2F("Real_Muon_00_Eta_Residual_vs_Eta", "Real_Muon_00_Eta_Residual_vs_Eta", 500, -5, 5, 10, -0.1, 0.1);
TH2F *Real_Muon_01_Eta_Residual_vs_Eta = new TH2F("Real_Muon_01_Eta_Residual_vs_Eta", "Real_Muon_01_Eta_Residual_vs_Eta", 500, -5, 5, 10, -0.1, 0.1);
TH2F *Real_Muon_10_Eta_Residual_vs_Eta = new TH2F("Real_Muon_10_Eta_Residual_vs_Eta", "Real_Muon_10_Eta_Residual_vs_Eta", 500, -5, 5, 10, -0.1, 0.1);
TH2F *Real_Muon_11_Eta_Residual_vs_Eta = new TH2F("Real_Muon_11_Eta_Residual_vs_Eta", "Real_Muon_11_Eta_Residual_vs_Eta", 500, -5, 5, 10, -0.1, 0.1);

TH2F *Fake_Muon_00_Eta_Residual_vs_Eta = new TH2F("Fake_Muon_00_Eta_Residual_vs_Eta", "Fake_Muon_00_Eta_Residual_vs_Eta", 500, -5, 5, 10, -0.1, 0.1);
TH2F *Fake_Muon_01_Eta_Residual_vs_Eta = new TH2F("Fake_Muon_01_Eta_Residual_vs_Eta", "Fake_Muon_01_Eta_Residual_vs_Eta", 500, -5, 5, 10, -0.1, 0.1);
TH2F *Fake_Muon_10_Eta_Residual_vs_Eta = new TH2F("Fake_Muon_10_Eta_Residual_vs_Eta", "Fake_Muon_10_Eta_Residual_vs_Eta", 500, -5, 5, 10, -0.1, 0.1);
TH2F *Fake_Muon_11_Eta_Residual_vs_Eta = new TH2F("Fake_Muon_11_Eta_Residual_vs_Eta", "Fake_Muon_11_Eta_Residual_vs_Eta", 500, -5, 5, 10, -0.1, 0.1);

TH2F *Real_Muon_00_Phi_Residual_vs_Phi = new TH2F("Real_Muon_00_Phi_Residual_vs_Phi", "Real_Muon_00_Phi_Residual_vs_Phi", 400, -4, 4, 700, -7, 7);
TH2F *Real_Muon_01_Phi_Residual_vs_Phi = new TH2F("Real_Muon_01_Phi_Residual_vs_Phi", "Real_Muon_01_Phi_Residual_vs_Phi", 400, -4, 4, 700, -7, 7);
TH2F *Real_Muon_10_Phi_Residual_vs_Phi = new TH2F("Real_Muon_10_Phi_Residual_vs_Phi", "Real_Muon_10_Phi_Residual_vs_Phi", 400, -4, 4, 700, -7, 7);
TH2F *Real_Muon_11_Phi_Residual_vs_Phi = new TH2F("Real_Muon_11_Phi_Residual_vs_Phi", "Real_Muon_11_Phi_Residual_vs_Phi", 400, -4, 4, 700, -7, 7);

TH2F *Fake_Muon_00_Phi_Residual_vs_Phi = new TH2F("Fake_Muon_00_Phi_Residual_vs_Phi", "Fake_Muon_00_Phi_Residual_vs_Phi", 400, -4, 4, 700, -7, 7);
TH2F *Fake_Muon_01_Phi_Residual_vs_Phi = new TH2F("Fake_Muon_01_Phi_Residual_vs_Phi", "Fake_Muon_01_Phi_Residual_vs_Phi", 400, -4, 4, 700, -7, 7);
TH2F *Fake_Muon_10_Phi_Residual_vs_Phi = new TH2F("Fake_Muon_10_Phi_Residual_vs_Phi", "Fake_Muon_10_Phi_Residual_vs_Phi", 400, -4, 4, 700, -7, 7);
TH2F *Fake_Muon_11_Phi_Residual_vs_Phi = new TH2F("Fake_Muon_11_Phi_Residual_vs_Phi", "Fake_Muon_11_Phi_Residual_vs_Phi", 400, -4, 4, 700, -7, 7);



//Geometry plots

TH1F *Real_GEN_Dimuon_Opening_Angle = new TH1F("Real_GEN_Dimuon_Opening_Angle", "Real_GEN_Dimuon_Opening_Angle", 400, -4, 4);
TH1F *Real_RECO_Dimuon_Opening_Angle = new TH1F("Real_RECO_Dimuon_Opening_Angle", "Real_RECO_Dimuon_Opening_Angle", 400, -4, 4);
TH1F *Real_Dimuon_Opening_Angle_Residual = new TH1F("Real_Dimuon_Opening_Angle_Residual", "Real_Dimuon_Opening_Angle_Residual", 700, -7, 7);
TH2F *Real_Dimuon_opening_Angle_Residual_vs_GENangle = new TH2F("Real_Dimuon_opening_Angle_Residual_vs_GENangle", "Real_Dimuon_opening_Angle_Residual_vs_GENangle", 400, -4, 4, 700, -7, 7);

TH1F *Fake_GEN_Dimuon_Opening_Angle = new TH1F("Fake_GEN_Dimuon_Opening_Angle", "Fake_GEN_Dimuon_Opening_Angle", 400, -4, 4);
TH1F *Fake_RECO_Dimuon_Opening_Angle = new TH1F("Fake_RECO_Dimuon_Opening_Angle", "Fake_RECO_Dimuon_Opening_Angle", 400, -4, 4);
TH1F *Fake_Dimuon_Opening_Angle_Residual = new TH1F("Fake_Dimuon_Opening_Angle_Residual", "Fake_Dimuon_Opening_Angle_Residual", 700, -7, 7);
TH2F *Fake_Dimuon_opening_Angle_Residual_vs_GENangle = new TH2F("Fake_Dimuon_opening_Angle_Residual_vs_GENangle", "Fake_Dimuon_opening_Angle_Residual_vs_GENangle", 400, -4, 4, 700, -7, 7);

TH1F *Real_GEN_deltaR_Between_Dimuons = new TH1F("Real_GEN_deltaR_Between_Dimuons", "Real_GEN_deltaR_Between_Dimuons", 750, 0, 15);
TH1F *Real_RECO_deltaR_Between_Dimuons = new TH1F("Real_RECO_deltaR_Between_Dimuons", "Real_RECO_deltaR_Between_Dimuons", 750, 0, 15);
TH1F *Real_deltaR_Between_Dimuons_Residual = new TH1F("Real_deltaR_Between_Dimuons_Residual", "Real_deltaR_Between_Dimuons_Residual", 1500, -15, 15);
TH2F *Real_deltaR_Between_Dimuons_Residual_vs_GENdeltaR = new TH2F("Real_deltaR_Between_Dimuons_Residual_vs_GENdeltaR", "Real_deltaR_Between_Dimuons_Residual_vs_GENdeltaR", 750, 0, 15, 1500, -15, 15);

TH1F *Fake_GEN_deltaR_Between_Dimuons = new TH1F("Fake_GEN_deltaR_Between_Dimuons", "Fake_GEN_deltaR_Between_Dimuons", 750, 0, 15);
TH1F *Fake_RECO_deltaR_Between_Dimuons = new TH1F("Fake_RECO_deltaR_Between_Dimuons", "Fake_RECO_deltaR_Between_Dimuons", 750, 0, 15);
TH1F *Fake_deltaR_Between_Dimuons_Residual = new TH1F("Fake_deltaR_Between_Dimuons_Residual", "Fake_deltaR_Between_Dimuons_Residual", 1500, -15, 15);
TH2F *Fake_deltaR_Between_Dimuons_Residual_vs_GENdeltaR = new TH2F("Fake_deltaR_Between_Dimuons_Residual_vs_GENdeltaR", "Fake_deltaR_Between_Dimuons_Residual_vs_GENdeltaR", 750, 0, 15, 1500, -15, 15);

//Vertex plots
TH1F *Real_Dimuon1_GEN_Dimuon_vertex_r = new TH1F("Real_Dimuon1_GEN_Dimuon_vertex_r", "Real_Dimuon1_GEN_Dimuon_vertex_r", 300, -30, 30);
TH1F *Real_Dimuon1_RECO_Dimuon_vertex_r = new TH1F("Real_Dimuon1_RECO_Dimuon_vertex_r", "Real_Dimuon1_RECO_Dimuon_vertex_r", 300, -30, 30);
TH1F *Real_Dimuon1_Dimuon_vertex_r_Residual = new TH1F("Real_Dimuon1_Dimuon_vertex_r_Residual", "Real_Dimuon1_Dimuon_vertex_r_Residual", 300, -30, 30);
TH2F *Real_Dimuon1_Dimuon_vertex_r_Residual_vs_GEN = new TH2F("Real_Dimuon1_Dimuon_vertex_r_Residual_vs_GEN", "Real_Dimuon1_Dimuon_vertex_r_Residual_vs_GEN", 300, -30, 30, 300, -30, 30);
TH2F *Real_Dimuon1_Dimuon_Lxy_Residual_vs_GEN_vertex_r = new TH2F("Real_Dimuon1_Dimuon_Lxy_Residual_vs_GEN_vertex_r", "Real_Dimuon1_Dimuon_Lxy_Residual_vs_GEN_vertex_r", 60, 0, 30, 300, -30, 30);
TH2F *Real_Dimuon1_Dimuon_Lxy_Residual_vs_RECO_vertex_r = new TH2F("Real_Dimuon1_Dimuon_Lxy_Residual_vs_RECO_vertex_r", "Real_Dimuon1_Dimuon_Lxy_Residual_vs_RECO_vertex_r", 60, 0, 30, 300, -30, 30);

TH1F *Real_Dimuon1_GEN_Dimuon_vertex_z = new TH1F("Real_Dimuon1_GEN_Dimuon_vertex_z", "Real_Dimuon1_GEN_Dimuon_vertex_z", 300, -30, 30);
TH1F *Real_Dimuon1_RECO_Dimuon_vertex_z = new TH1F("Real_Dimuon1_RECO_Dimuon_vertex_z", "Real_Dimuon1_RECO_Dimuon_vertex_z", 300, -30, 30);
TH1F *Real_Dimuon1_Dimuon_vertex_z_Residual = new TH1F("Real_Dimuon1_Dimuon_vertex_z_Residual", "Real_Dimuon1_Dimuon_vertex_z_Residual", 300, -30, 30);
TH2F *Real_Dimuon1_Dimuon_vertex_z_Residual_vs_GEN = new TH2F("Real_Dimuon1_Dimuon_vertex_z_Residual_vs_GEN", "Real_Dimuon1_Dimuon_vertex_z_Residual_vs_GEN", 300, -30, 30, 300, -30, 30);
TH2F *Real_Dimuon1_Dimuon_Lxy_Residual_vs_GEN_vertex_z = new TH2F("Real_Dimuon1_Dimuon_Lxy_Residual_vs_GEN_vertex_z", "Real_Dimuon1_Dimuon_Lxy_Residual_vs_GEN_vertex_z", 60, 0, 30, 300, -30, 30);
TH2F *Real_Dimuon1_Dimuon_Lxy_Residual_vs_RECO_vertex_z = new TH2F("Real_Dimuon1_Dimuon_Lxy_Residual_vs_RECO_vertex_z", "Real_Dimuon1_Dimuon_Lxy_Residual_vs_RECO_vertex_z", 60, 0, 30, 300, -30, 30);

TH1F *Real_Dimuon2_GEN_Dimuon_vertex_r = new TH1F("Real_Dimuon2_GEN_Dimuon_vertex_r", "Real_Dimuon2_GEN_Dimuon_vertex_r", 300, -30, 30);
TH1F *Real_Dimuon2_RECO_Dimuon_vertex_r = new TH1F("Real_Dimuon2_RECO_Dimuon_vertex_r", "Real_Dimuon2_RECO_Dimuon_vertex_r", 300, -30, 30);
TH1F *Real_Dimuon2_Dimuon_vertex_r_Residual = new TH1F("Real_Dimuon2_Dimuon_vertex_r_Residual", "Real_Dimuon2_Dimuon_vertex_r_Residual", 300, -30, 30);
TH2F *Real_Dimuon2_Dimuon_vertex_r_Residual_vs_GEN = new TH2F("Real_Dimuon2_Dimuon_vertex_r_Residual_vs_GEN", "Real_Dimuon2_Dimuon_vertex_r_Residual_vs_GEN", 300, -30, 30, 300, -30, 30);
TH2F *Real_Dimuon2_Dimuon_Lxy_Residual_vs_GEN_vertex_r = new TH2F("Real_Dimuon2_Dimuon_Lxy_Residual_vs_GEN_vertex_r", "Real_Dimuon2_Dimuon_Lxy_Residual_vs_GEN_vertex_r", 60, 0, 30, 300, -30, 30);
TH2F *Real_Dimuon2_Dimuon_Lxy_Residual_vs_RECO_vertex_r = new TH2F("Real_Dimuon2_Dimuon_Lxy_Residual_vs_RECO_vertex_r", "Real_Dimuon2_Dimuon_Lxy_Residual_vs_RECO_vertex_r", 60, 0, 30, 300, -30, 30);

TH1F *Real_Dimuon2_GEN_Dimuon_vertex_z = new TH1F("Real_Dimuon2_GEN_Dimuon_vertex_z", "Real_Dimuon2_GEN_Dimuon_vertex_z", 300, -30, 30);
TH1F *Real_Dimuon2_RECO_Dimuon_vertex_z = new TH1F("Real_Dimuon2_RECO_Dimuon_vertex_z", "Real_Dimuon2_RECO_Dimuon_vertex_z", 300, -30, 30);
TH1F *Real_Dimuon2_Dimuon_vertex_z_Residual = new TH1F("Real_Dimuon2_Dimuon_vertex_z_Residual", "Real_Dimuon2_Dimuon_vertex_z_Residual", 300, -30, 30);
TH2F *Real_Dimuon2_Dimuon_vertex_z_Residual_vs_GEN = new TH2F("Real_Dimuon2_Dimuon_vertex_z_Residual_vs_GEN", "Real_Dimuon2_Dimuon_vertex_z_Residual_vs_GEN", 300, -30, 30, 300, -30, 30);
TH2F *Real_Dimuon2_Dimuon_Lxy_Residual_vs_GEN_vertex_z = new TH2F("Real_Dimuon2_Dimuon_Lxy_Residual_vs_GEN_vertex_z", "Real_Dimuon2_Dimuon_Lxy_Residual_vs_GEN_vertex_z", 60, 0, 30, 300, -30, 30);
TH2F *Real_Dimuon2_Dimuon_Lxy_Residual_vs_RECO_vertex_z = new TH2F("Real_Dimuon2_Dimuon_Lxy_Residual_vs_RECO_vertex_z", "Real_Dimuon2_Dimuon_Lxy_Residual_vs_RECO_vertex_z", 60, 0, 30, 300, -30, 30);

TH1F *Fake1_GEN_Dimuon_vertex_r = new TH1F("Fake1_GEN_Dimuon_vertex_r", "Fake1_GEN_Dimuon_vertex_r", 300, -30, 30);
TH1F *Fake1_RECO_Dimuon_vertex_r = new TH1F("Fake1_RECO_Dimuon_vertex_r", "Fake1_RECO_Dimuon_vertex_r", 300, -30, 30);
TH1F *Fake1_Dimuon_vertex_r_Residual = new TH1F("Fake1_Dimuon_vertex_r_Residual", "Fake1_Dimuon_vertex_r_Residual", 300, -30, 30);
TH2F *Fake1_Dimuon_vertex_r_Residual_vs_GEN = new TH2F("Fake1_Dimuon_vertex_r_Residual_vs_GEN", "Fake1_Dimuon_vertex_r_Residual_vs_GEN", 300, -30, 30, 300, -30, 30);
TH2F *Fake1_Dimuon_Lxy_Residual_vs_GEN_vertex_r = new TH2F("Fake1_Dimuon_Lxy_Residual_vs_GEN_vertex_r", "Fake1_Dimuon_Lxy_Residual_vs_GEN_vertex_r", 60, 0, 30, 300, -30, 30);
TH2F *Fake1_Dimuon_Lxy_Residual_vs_RECO_vertex_r = new TH2F("Fake1_Dimuon_Lxy_Residual_vs_RECO_vertex_r", "Fake1_Dimuon_Lxy_Residual_vs_RECO_vertex_r", 60, 0, 30, 300, -30, 30);

TH1F *Fake2_GEN_Dimuon_vertex_r = new TH1F("Fake2_GEN_Dimuon_vertex_r", "Fake2_GEN_Dimuon_vertex_r", 300, -30, 30);
TH1F *Fake2_RECO_Dimuon_vertex_r = new TH1F("Fake2_RECO_Dimuon_vertex_r", "Fake2_RECO_Dimuon_vertex_r", 300, -30, 30);
TH1F *Fake2_Dimuon_vertex_r_Residual = new TH1F("Fake2_Dimuon_vertex_r_Residual", "Fake2_Dimuon_vertex_r_Residual", 300, -30, 30);
TH2F *Fake2_Dimuon_vertex_r_Residual_vs_GEN = new TH2F("Fake2_Dimuon_vertex_r_Residual_vs_GEN", "Fake2_Dimuon_vertex_r_Residual_vs_GEN", 300, -30, 30, 300, -30, 30);
TH2F *Fake2_Dimuon_Lxy_Residual_vs_GEN_vertex_r = new TH2F("Fake2_Dimuon_Lxy_Residual_vs_GEN_vertex_r", "Fake2_Dimuon_Lxy_Residual_vs_GEN_vertex_r", 60, 0, 30, 300, -30, 30);
TH2F *Fake2_Dimuon_Lxy_Residual_vs_RECO_vertex_r = new TH2F("Fake2_Dimuon_Lxy_Residual_vs_RECO_vertex_r", "Fake2_Dimuon_Lxy_Residual_vs_RECO_vertex_r", 60, 0, 30, 300, -30, 30);

TH1F *Fake1_GEN_Dimuon_vertex_z = new TH1F("Fake1_GEN_Dimuon_vertex_z", "Fake1_GEN_Dimuon_vertex_z", 300, -30, 30);
TH1F *Fake1_RECO_Dimuon_vertex_z = new TH1F("Fake1_RECO_Dimuon_vertex_z", "Fake1_RECO_Dimuon_vertex_z", 300, -30, 30);
TH1F *Fake1_Dimuon_vertex_z_Residual = new TH1F("Fake1_Dimuon_vertex_z_Residual", "Fake1_Dimuon_vertex_z_Residual", 300, -30, 30);
TH2F *Fake1_Dimuon_vertex_z_Residual_vs_GEN = new TH2F("Fake1_Dimuon_vertex_z_Residual_vs_GEN", "Fake1_Dimuon_vertex_z_Residual_vs_GEN", 300, -30, 30, 300, -30, 30);
TH2F *Fake1_Dimuon_Lxy_Residual_vs_GEN_vertex_z = new TH2F("Fake1_Dimuon_Lxy_Residual_vs_GEN_vertex_z", "Fake1_Dimuon_Lxy_Residual_vs_GEN_vertex_z", 60, 0, 30, 300, -30, 30);
TH2F *Fake1_Dimuon_Lxy_Residual_vs_RECO_vertex_z = new TH2F("Fake1_Dimuon_Lxy_Residual_vs_RECO_vertex_z", "Fake1_Dimuon_Lxy_Residual_vs_RECO_vertex_z", 60, 0, 30, 300, -30, 30);

TH1F *Fake2_GEN_Dimuon_vertex_z = new TH1F("Fake2_GEN_Dimuon_vertex_z", "Fake2_GEN_Dimuon_vertex_z", 300, -30, 30);
TH1F *Fake2_RECO_Dimuon_vertex_z = new TH1F("Fake2_RECO_Dimuon_vertex_z", "Fake2_RECO_Dimuon_vertex_z", 300, -30, 30);
TH1F *Fake2_Dimuon_vertex_z_Residual = new TH1F("Fake2_Dimuon_vertex_z_Residual", "Fake2_Dimuon_vertex_z_Residual", 300, -30, 30);
TH2F *Fake2_Dimuon_vertex_z_Residual_vs_GEN = new TH2F("Fake2_Dimuon_vertex_z_Residual_vs_GEN", "Fake2_Dimuon_vertex_z_Residual_vs_GEN", 300, -30, 30, 300, -30, 30);
TH2F *Fake2_Dimuon_Lxy_Residual_vs_GEN_vertex_z = new TH2F("Fake2_Dimuon_Lxy_Residual_vs_GEN_vertex_z", "Fake2_Dimuon_Lxy_Residual_vs_GEN_vertex_z", 60, 0, 30, 300, -30, 30);
TH2F *Fake2_Dimuon_Lxy_Residual_vs_RECO_vertex_z = new TH2F("Fake2_Dimuon_Lxy_Residual_vs_RECO_vertex_z", "Fake2_Dimuon_Lxy_Residual_vs_RECO_vertex_z", 60, 0, 30, 300, -30, 30);

//2 Dimensional RECO level plots

TH2F *Real_Reco_Eta_vs_Phi = new TH2F("Real_Reco_Eta_vs_Phi","Real_Reco_Eta_vs_Phi",500, -5, 5, 340, -3.4, 3.4);
TH2F *Fake_Reco_Eta_vs_Phi = new TH2F("Fake_Reco_Eta_vs_Phi","Fake_Reco_Eta_vs_Phi",500, -5, 5, 340, -3.4, 3.4);
TH2F *Fake_dimuon1_Reco_Eta_vs_Phi = new TH2F("Fake_dimuon1_Reco_Eta_vs_Phi","Fake_dimuon1_Reco_Eta_vs_Phi",500, -5, 5, 340, -3.4, 3.4);
TH2F *Fake_dimuon2_Reco_Eta_vs_Phi = new TH2F("Fake_dimuon2_Reco_Eta_vs_Phi","Fake_dimuon2_Reco_Eta_vs_Phi",500, -5, 5, 340, -3.4, 3.4);
TH2F *Real_dimuon1_Reco_Eta_vs_Phi = new TH2F("Real_dimuon1_Reco_Eta_vs_Phi","Real_dimuon1_Reco_Eta_vs_Phi",500, -5, 5, 340, -3.4, 3.4);
TH2F *Real_dimuon2_Reco_Eta_vs_Phi = new TH2F("Real_dimuon2_Reco_Eta_vs_Phi","Real_dimuon2_Reco_Eta_vs_Phi",500, -5, 5, 340, -3.4, 3.4);

//eta v vertexZ
TH2F *Real_Reco_Eta_vs_VertexZ = new TH2F("Real_Reco_Eta_vs_VertexZ","Real_Reco_Eta_vs_VertexZ",500, -5, 5, 500, -50, 50);
TH2F *Fake_Reco_Eta_vs_VertexZ = new TH2F("Fake_Reco_Eta_vs_VertexZ","Fake_Reco_Eta_vs_VertexZ",500, -5, 5, 500, -50, 50);
TH2F *Fake_dimuon1_Reco_Eta_vs_VertexZ = new TH2F("Fake_dimuon1_Reco_Eta_vs_VertexZ","Fake_dimuon1_Reco_Eta_vs_VertexZ",500, -5, 5, 500, -50, 50);
TH2F *Fake_dimuon2_Reco_Eta_vs_VertexZ = new TH2F("Fake_dimuon2_Reco_Eta_vs_VertexZ","Fake_dimuon2_Reco_Eta_vs_VertexZ",500, -5, 5, 500, -50, 50);
TH2F *Real_dimuon1_Reco_Eta_vs_VertexZ = new TH2F("Real_dimuon1_Reco_Eta_vs_VertexZ","Real_dimuon1_Reco_Eta_vs_VertexZ",500, -5, 5, 500, -50, 50);
TH2F *Real_dimuon2_Reco_Eta_vs_VertexZ = new TH2F("Real_dimuon2_Reco_Eta_vs_VertexZ","Real_dimuon2_Reco_Eta_vs_VertexZ",500, -5, 5, 500, -50, 50);

//eta v vertexR
TH2F *Real_Reco_Eta_vs_VertexR = new TH2F("Real_Reco_Eta_vs_VertexR","Real_Reco_Eta_vs_VertexR",500, -5, 5, 250, 0, 50);
TH2F *Fake_Reco_Eta_vs_VertexR = new TH2F("Fake_Reco_Eta_vs_VertexR","Fake_Reco_Eta_vs_VertexR",500, -5, 5, 250, 0, 50);
TH2F *Fake_dimuon1_Reco_Eta_vs_VertexR = new TH2F("Fake_dimuon1_Reco_Eta_vs_VertexR","Fake_dimuon1_Reco_Eta_vs_VertexR",500, -5, 5, 250, 0, 50);
TH2F *Fake_dimuon2_Reco_Eta_vs_VertexR = new TH2F("Fake_dimuon2_Reco_Eta_vs_VertexR","Fake_dimuon2_Reco_Eta_vs_VertexR",500, -5, 5, 250, 0, 50);
TH2F *Real_dimuon1_Reco_Eta_vs_VertexR = new TH2F("Real_dimuon1_Reco_Eta_vs_VertexR","Real_dimuon1_Reco_Eta_vs_VertexR",500, -5, 5, 250, 0, 50);
TH2F *Real_dimuon2_Reco_Eta_vs_VertexR = new TH2F("Real_dimuon2_Reco_Eta_vs_VertexR","Real_dimuon2_Reco_Eta_vs_VertexR",500, -5, 5, 250, 0, 50);

//eta v deltaR
TH2F *Real_Reco_Eta_vs_deltaR = new TH2F("Real_Reco_Eta_vs_deltaR","Real_Reco_Eta_vs_deltaR",500, -5, 5, 300, 0, 6);
TH2F *Fake_Reco_Eta_vs_deltaR = new TH2F("Fake_Reco_Eta_vs_deltaR","Fake_Reco_Eta_vs_deltaR",500, -5, 5, 300, 0, 6);
TH2F *Fake_dimuon1_Reco_Eta_vs_deltaR = new TH2F("Fake_dimuon1_Reco_Eta_vs_deltaR","Fake_dimuon1_Reco_Eta_vs_deltaR",500, -5, 5, 300, 0, 6);
TH2F *Fake_dimuon2_Reco_Eta_vs_deltaR = new TH2F("Fake_dimuon2_Reco_Eta_vs_deltaR","Fake_dimuon2_Reco_Eta_vs_deltaR",500, -5, 5, 300, 0, 6);
TH2F *Real_dimuon1_Reco_Eta_vs_deltaR = new TH2F("Real_dimuon1_Reco_Eta_vs_deltaR","Real_dimuon1_Reco_Eta_vs_deltaR",500, -5, 5, 300, 0, 6);
TH2F *Real_dimuon2_Reco_Eta_vs_deltaR = new TH2F("Real_dimuon2_Reco_Eta_vs_deltaR","Real_dimuon2_Reco_Eta_vs_deltaR",500, -5, 5, 300, 0, 6);

//eta v opening angle
TH2F *Real_Reco_Eta_vs_OpeningAngle = new TH2F("Real_Reco_Eta_vs_OpeningAngle","Real_Reco_Eta_vs_OpeningAngle",500, -5, 5, 200, 0, 4);
TH2F *Fake_Reco_Eta_vs_OpeningAngle = new TH2F("Fake_Reco_Eta_vs_OpeningAngle","Fake_Reco_Eta_vs_OpeningAngle",500, -5, 5, 200, 0, 4);
TH2F *Fake_dimuon1_Reco_Eta_vs_OpeningAngle = new TH2F("Fake_dimuon1_Reco_Eta_vs_OpeningAngle","Fake_dimuon1_Reco_Eta_vs_OpeningAngle",500, -5, 5, 200, 0, 4);
TH2F *Fake_dimuon2_Reco_Eta_vs_OpeningAngle = new TH2F("Fake_dimuon2_Reco_Eta_vs_OpeningAngle","Fake_dimuon2_Reco_Eta_vs_OpeningAngle",500, -5, 5, 200, 0, 4);
TH2F *Real_dimuon1_Reco_Eta_vs_OpeningAngle = new TH2F("Real_dimuon1_Reco_Eta_vs_OpeningAngle","Real_dimuon1_Reco_Eta_vs_OpeningAngle",500, -5, 5, 200, 0, 4);
TH2F *Real_dimuon2_Reco_Eta_vs_OpeningAngle = new TH2F("Real_dimuon2_Reco_Eta_vs_OpeningAngle","Real_dimuon2_Reco_Eta_vs_OpeningAngle",500, -5, 5, 200, 0, 4);

//eta v Lxy
TH2F *Real_Reco_Eta_vs_Lxy = new TH2F("Real_Reco_Eta_vs_Lxy","Real_Reco_Eta_vs_Lxy",500, -5, 5, 400, 0, 80);
TH2F *Fake_Reco_Eta_vs_Lxy = new TH2F("Fake_Reco_Eta_vs_Lxy","Fake_Reco_Eta_vs_Lxy",500, -5, 5, 400, 0, 80);
TH2F *Fake_dimuon1_Reco_Eta_vs_Lxy = new TH2F("Fake_dimuon1_Reco_Eta_vs_Lxy","Fake_dimuon1_Reco_Eta_vs_Lxy",500, -5, 5, 400, 0, 80);
TH2F *Fake_dimuon2_Reco_Eta_vs_Lxy = new TH2F("Fake_dimuon2_Reco_Eta_vs_Lxy","Fake_dimuon2_Reco_Eta_vs_Lxy",500, -5, 5, 400, 0, 80);
TH2F *Real_dimuon1_Reco_Eta_vs_Lxy = new TH2F("Real_dimuon1_Reco_Eta_vs_Lxy","Real_dimuon1_Reco_Eta_vs_Lxy",500, -5, 5, 400, 0, 80);
TH2F *Real_dimuon2_Reco_Eta_vs_Lxy = new TH2F("Real_dimuon2_Reco_Eta_vs_Lxy","Real_dimuon2_Reco_Eta_vs_Lxy",500, -5, 5, 400, 0, 80);



TH1F *Event_Fail_Reason = new TH1F("Event_Fail_Reason", "Event_Fail_Reason", 9, -0.5, 8.5);
TH1F *Fake_Dimuon_Reason = new TH1F("Fake_Dimuon_Reason", "Fake_Dimuon_Reason", 8,-0.5,7.5);

//}}}
vector<double> mGammaD_0250_eff;
vector<double> mGammaD_0275_eff;
vector<double> mGammaD_0300_eff;
vector<double> mGammaD_2000_eff;
vector<double> mGammaD_8500_eff;
vector<double> mGammaD_0400_eff;
vector<double> mGammaD_0700_eff;
vector<double> mGammaD_1000_eff;
vector<double> mGammaD_1500_eff;

vector<double> mGammaD_0250_eff_uncert;
vector<double> mGammaD_0275_eff_uncert;
vector<double> mGammaD_0300_eff_uncert;
vector<double> mGammaD_2000_eff_uncert;
vector<double> mGammaD_8500_eff_uncert;
vector<double> mGammaD_0400_eff_uncert;
vector<double> mGammaD_0700_eff_uncert;
vector<double> mGammaD_1000_eff_uncert;
vector<double> mGammaD_1500_eff_uncert;

vector<double> mGammaD_0250_cT;
vector<double> mGammaD_0275_cT;
vector<double> mGammaD_0300_cT;
vector<double> mGammaD_2000_cT;
vector<double> mGammaD_8500_cT;
vector<double> mGammaD_0400_cT;
vector<double> mGammaD_0700_cT;
vector<double> mGammaD_1000_cT;
vector<double> mGammaD_1500_cT;

vector< vector<double> > FakeStatistics;

double My_dPhi (double phi1, double phi2) {
	double dPhi = phi1 - phi2;
	if (dPhi >  TMath::Pi()) dPhi -= 2*TMath::Pi();
	if (dPhi <  -TMath::Pi()) dPhi += 2*TMath::Pi();
	return abs(dPhi); //Changed to abs 1/5/2016
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
	bool verbose(false);
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
				ch->Add(fname);
			}
		}
	}
}

void efficiency_hitrecovery(TString fileName){
	bool verbose(false);
	TString dirname(fileName);
	TChain* chain = new TChain("dummy");
	TString ext("out_ana_");

	///Get the sample mass
	TString str = fileName;
	TString str2 = "DarkSUSY_mH_125_mGammaD_";
	Ssiz_t first = str.Index(str2);
	Ssiz_t last = str.Index("_cT_");
	TSubString mass_string = (str(first+str2.Length(),4));
	///Get the sample cT
	TString str3 = "_cT_";
	TSubString cT_string = (str(last+str3.Length(),4));

	// add files to the chain
	addfiles(chain, dirname, ext);

	//Initialize Variables and counters
	//{{{

	Int_t event;
	Int_t run;
	Int_t lumi;

	Bool_t is4GenMu;
	Bool_t is1GenMu17;
	Bool_t is2GenMu8;
	Bool_t is3GenMu8;
	Bool_t is4GenMu8;

	Bool_t is1SelMu17;
	Bool_t is2SelMu8;
	Bool_t is3SelMu8;
	Bool_t is4SelMu8;

	Bool_t is2MuJets;
	Bool_t is2DiMuons;
	Bool_t is2DiMuonsFittedVtxOK;
	Bool_t is2DiMuonsDzOK_FittedVtx;
	Bool_t isDiMuonHLTFired;
	Bool_t is2DiMuonsMassOK_FittedVtx;
	Bool_t is2DiMuonsIsoTkOK_FittedVtx;
	Bool_t isVertexOK;

	Float_t genA0_Lxy;
	Float_t genA1_Lxy;
	Float_t genA0_Lz;
	Float_t genA1_Lz;


	Int_t diMuonC_m1_FittedVtx_hitpix;
	Int_t diMuonC_m2_FittedVtx_hitpix;
	Int_t diMuonF_m1_FittedVtx_hitpix;
	Int_t diMuonF_m2_FittedVtx_hitpix;

	Float_t genA0_eta;
	Float_t genA0_phi;
	Float_t genA1_eta;
	Float_t genA1_phi;

	Float_t selMu0_phi;
	Float_t selMu1_phi;
	Float_t selMu2_phi;
	Float_t selMu3_phi;

	Float_t selMu0_eta;
	Float_t selMu1_eta;
	Float_t selMu2_eta;
	Float_t selMu3_eta;

	Float_t genA0_m;
	Float_t genA0_px;
	Float_t genA0_py;
	Float_t genA0_pz;

	Float_t genA1_m;
	Float_t genA1_px;
	Float_t genA1_py;
	Float_t genA1_pz;

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

	Float_t genA0Mu0_eta;
	Float_t genA1Mu0_eta;
	Float_t genA0Mu1_eta;
	Float_t genA1Mu1_eta;


	Float_t genA0Mu0_phi;
	Float_t genA1Mu0_phi;
	Float_t genA0Mu1_phi;
	Float_t genA1Mu1_phi;

	//Vertex information
	Float_t genA0_vx;
	Float_t genA0_vy;
	Float_t genA0_vz;

	Float_t genA1_vx;
	Float_t genA1_vy;
	Float_t genA1_vz;

	Float_t genA0Mu0_vx;
	Float_t genA0Mu1_vx;
	Float_t genA1Mu0_vx;
	Float_t genA1Mu1_vx;

	Float_t genA0Mu0_vy;
	Float_t genA0Mu1_vy;
	Float_t genA1Mu0_vy;
	Float_t genA1Mu1_vy;

	Float_t genA0Mu0_vz;
	Float_t genA0Mu1_vz;
	Float_t genA1Mu0_vz;
	Float_t genA1Mu1_vz;

	Float_t diMuonC_FittedVtx_vx;
	Float_t diMuonC_FittedVtx_vy;
	Float_t diMuonC_FittedVtx_vz;

	Float_t diMuonF_FittedVtx_vx;
	Float_t diMuonF_FittedVtx_vy;
	Float_t diMuonF_FittedVtx_vz;

	//============= Counters ===========================//

	vector<double> FakesPerSample;

	Int_t ev_all = 0;
	Int_t ev_isVtxOK = 0;
	Int_t ev_is2MuJets = 0;
	Int_t ev_is2DiMuons = 0;
	Int_t ev_is2DiMuonsFittedVtxOK = 0;
	Int_t ev_isPixelHitOK = 0;
	Int_t ev_is2DiMuonsDzOK_FittedVtx = 0;
	Int_t ev_is2DiMuonsMassOK_FittedVtx = 0;
	Int_t ev_is2DiMuonsIsoTkOK_FittedVtx = 0;
	Int_t ev_isDiMuonHLTFired = 0;

	Int_t c1genm = 0;
	Int_t c2genm = 0;
	Int_t c3genm = 0;
	Int_t c4genm = 0;
	Int_t ev_4gmlxylzcut = 0;

	Int_t c1recm = 0;
	Int_t c2recm = 0;
	Int_t c3recm = 0;
	Int_t c4recm = 0;

	Int_t uncuttableFakeCounter = 0;
	//}}}

	TObjArray *fileElements=chain->GetListOfFiles();
	TIter next(fileElements);
	TChainElement *chEl=0;

	while ((chEl=(TChainElement*)next())) {
		if (verbose) std::cout << "running on file " << chEl->GetTitle() << std::endl;
		TFile* myfile = new TFile(dirname + chEl->GetTitle());
		if (!myfile) {
			if (verbose) std::cout << "File " << chEl->GetTitle() << " does not exist" << std::endl;
			continue;
		}

		if (verbose) std::cout << "Loading directory cutFlowAnalyzer" << std::endl;
		myfile->cd("cutFlowAnalyzer");

		TTree *t = (TTree*)myfile->Get("cutFlowAnalyzer/Events");
		if (!t) {
			if (verbose) std::cout << "Tree cutFlowAnalyzer/Events does not exist" << std::endl;
			continue;
		}

		if (verbose) cout<<"  Events  "<<t->GetEntries()<<endl;

		//Pull variables from nTuple
		//{{{
		// Event info
		t->SetBranchAddress("event", &event);
		t->SetBranchAddress("run",   &run);
		t->SetBranchAddress("lumi",  &lumi);

		// GEN Level Selectors
		t->SetBranchAddress("is4GenMu",    &is4GenMu);
		t->SetBranchAddress("is1GenMu17",  &is1GenMu17);
		t->SetBranchAddress("is2GenMu8",   &is2GenMu8);
		t->SetBranchAddress("is3GenMu8",   &is3GenMu8);
		t->SetBranchAddress("is4GenMu8",   &is4GenMu8);

		// RECO Level Selectors
		t->SetBranchAddress("is1SelMu17",                     &is1SelMu17);
		t->SetBranchAddress("is2SelMu8",                      &is2SelMu8);
		t->SetBranchAddress("is3SelMu8",                      &is3SelMu8);
		t->SetBranchAddress("is4SelMu8",                      &is4SelMu8);

		t->SetBranchAddress("is2MuJets",                      &is2MuJets);
		t->SetBranchAddress("is2DiMuons",                     &is2DiMuons);
		t->SetBranchAddress("is2DiMuonsFittedVtxOK",          &is2DiMuonsFittedVtxOK);
		t->SetBranchAddress("is2DiMuonsDzOK_FittedVtx",       &is2DiMuonsDzOK_FittedVtx);
		t->SetBranchAddress("isDiMuonHLTFired",               &isDiMuonHLTFired);
		t->SetBranchAddress("is2DiMuonsMassOK_FittedVtx",     &is2DiMuonsMassOK_FittedVtx);
		t->SetBranchAddress("is2DiMuonsIsoTkOK_FittedVtx",    &is2DiMuonsIsoTkOK_FittedVtx);
		t->SetBranchAddress("isVertexOK",                     &isVertexOK);
		t->SetBranchAddress("isDiMuonHLTFired",              &isDiMuonHLTFired);

		t->SetBranchAddress("genA0_Lxy", &genA0_Lxy);
		t->SetBranchAddress("genA0_Lz",  &genA0_Lz);
		t->SetBranchAddress("genA1_Lxy", &genA1_Lxy);
		t->SetBranchAddress("genA1_Lz",  &genA1_Lz);

		t->SetBranchAddress("diMuonC_m1_FittedVtx_hitpix", &diMuonC_m1_FittedVtx_hitpix);
		t->SetBranchAddress("diMuonC_m2_FittedVtx_hitpix", &diMuonC_m2_FittedVtx_hitpix);
		t->SetBranchAddress("diMuonF_m1_FittedVtx_hitpix", &diMuonF_m1_FittedVtx_hitpix);
		t->SetBranchAddress("diMuonF_m2_FittedVtx_hitpix", &diMuonF_m2_FittedVtx_hitpix);

		t->SetBranchAddress("genA1_phi",&genA1_phi);
		t->SetBranchAddress("genA1_eta",&genA1_eta);

		t->SetBranchAddress("genA0_phi",&genA0_phi);
		t->SetBranchAddress("genA0_eta",&genA0_eta);

		t->SetBranchAddress("selMu0_phi",&selMu0_phi);
		t->SetBranchAddress("selMu1_phi",&selMu1_phi);
		t->SetBranchAddress("selMu2_phi",&selMu2_phi);
		t->SetBranchAddress("selMu3_phi",&selMu3_phi);

		t->SetBranchAddress("selMu0_eta",&selMu0_eta);
		t->SetBranchAddress("selMu1_eta",&selMu1_eta);
		t->SetBranchAddress("selMu2_eta",&selMu2_eta);
		t->SetBranchAddress("selMu3_eta",&selMu3_eta);

		t->SetBranchAddress("genA0_m" , &genA0_m);
		t->SetBranchAddress("genA0_px", &genA0_px);
		t->SetBranchAddress("genA0_py", &genA0_py);
		t->SetBranchAddress("genA0_pz", &genA0_pz);

		t->SetBranchAddress("genA1_m" , &genA1_m);
		t->SetBranchAddress("genA1_px", &genA1_px);
		t->SetBranchAddress("genA1_py", &genA1_py);
		t->SetBranchAddress("genA1_pz", &genA1_pz);

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

		t->SetBranchAddress("genA0Mu0_eta",&genA0Mu0_eta);
		t->SetBranchAddress("genA1Mu0_eta",&genA1Mu0_eta);
		t->SetBranchAddress("genA0Mu1_eta",&genA0Mu1_eta);
		t->SetBranchAddress("genA1Mu1_eta",&genA1Mu1_eta);

		t->SetBranchAddress("genA0Mu0_phi",&genA0Mu0_phi);
		t->SetBranchAddress("genA1Mu0_phi",&genA1Mu0_phi);
		t->SetBranchAddress("genA0Mu1_phi",&genA0Mu1_phi);
		t->SetBranchAddress("genA1Mu1_phi",&genA1Mu1_phi);

		t->SetBranchAddress("genA0_vx", &genA0_vx); 
		t->SetBranchAddress("genA0_vy", &genA0_vy);
		t->SetBranchAddress("genA0_vz", &genA0_vz);

		t->SetBranchAddress("genA1_vx", &genA1_vx);
		t->SetBranchAddress("genA1_vy", &genA1_vy);
		t->SetBranchAddress("genA1_vz", &genA1_vz);

		t->SetBranchAddress("genA0Mu0_vx", &genA0Mu0_vx);
		t->SetBranchAddress("genA0Mu1_vx", &genA0Mu1_vx);
		t->SetBranchAddress("genA1Mu0_vx", &genA1Mu0_vx);
		t->SetBranchAddress("genA1Mu1_vx", &genA1Mu1_vx);

		t->SetBranchAddress("genA0Mu0_vy", &genA0Mu0_vy);
		t->SetBranchAddress("genA0Mu1_vy", &genA0Mu1_vy);
		t->SetBranchAddress("genA1Mu0_vy", &genA1Mu0_vy);
		t->SetBranchAddress("genA1Mu1_vy", &genA1Mu1_vy);

		t->SetBranchAddress("genA0Mu0_vz", &genA0Mu0_vz);
		t->SetBranchAddress("genA0Mu1_vz", &genA0Mu1_vz);
		t->SetBranchAddress("genA1Mu0_vz", &genA1Mu0_vz);
		t->SetBranchAddress("genA1Mu1_vz", &genA1Mu1_vz);

		t->SetBranchAddress("diMuonC_FittedVtx_vx", &diMuonC_FittedVtx_vx);
		t->SetBranchAddress("diMuonC_FittedVtx_vy", &diMuonC_FittedVtx_vy);
		t->SetBranchAddress("diMuonC_FittedVtx_vz", &diMuonC_FittedVtx_vz);

		t->SetBranchAddress("diMuonF_FittedVtx_vx", &diMuonF_FittedVtx_vx);
		t->SetBranchAddress("diMuonF_FittedVtx_vy", &diMuonF_FittedVtx_vy);
		t->SetBranchAddress("diMuonF_FittedVtx_vz", &diMuonF_FittedVtx_vz);
		//}}}

		for(int k=0;k<t->GetEntries();k++){
			t->GetEntry(k);

			ev_all++;

			if(is1GenMu17) c1genm++;
			if(is2GenMu8)  c2genm++;
			if(is3GenMu8)  c3genm++;
			if(is4GenMu8)  c4genm++;

			if(is1SelMu17) c1recm++;
			if(is2SelMu8)  c2recm++;
			if(is3SelMu8)  c3recm++;
			if(is4SelMu8)  c4recm++;

			int triggerFlag_std = 0;
			int triggerFlag_lxy = 0;
			int fakeFlag = 0;
			int realFlag = 0;
			int fakeDimuon1 = 0;
			int fakeDimuon2 = 0;

			int brokenCounter = 0;
			int fakeCounter_dimuon1 = 0;
			int fakeCounter_dimuon2 = 0;
			int fakeCounter_both = 0;

			//  ===========   GEN LEVEL information  ==============//

			//{{{
			if(is4GenMu8){
				Float_t dphi_gD = My_dPhi(genA1_phi,genA0_phi);
				//if(fabs(dphi_gD)>=2.5){
				if(fabs(genA0_Lxy)<4.4 && fabs(genA1_Lxy)<4.4 && fabs(genA0_Lz)<34.5 && fabs(genA1_Lz)<34.5){
					ev_4gmlxylzcut++;
				}
				//}
			}

			//}}}
			//  =============  Reco information ====================//

			//Numerator of ratio
			//{{{
			//if(is4GenMu8)
			//if(fabs(genA0_Lxy)<4.4 && fabs(genA1_Lxy)<4.4 && fabs(genA0_Lz)<34.5 && fabs(genA1_Lz)<34.5){
			Float_t dphi_gD = My_dPhi(genA1_phi,genA0_phi);
			//if(fabs(dphi_gD)>=2.5){
			if(is4SelMu8){
				brokenCounter++;
				if(isVertexOK){
					ev_isVtxOK++;
					brokenCounter++;
					if(is2MuJets){
						ev_is2MuJets++;
						brokenCounter++;
						if(is2DiMuons){
							ev_is2DiMuons++;
							brokenCounter++;
							if(is2DiMuonsFittedVtxOK){
								ev_is2DiMuonsFittedVtxOK++;
								brokenCounter++;
								if( (diMuonC_m1_FittedVtx_hitpix==1||diMuonC_m2_FittedVtx_hitpix==1)&&(diMuonF_m1_FittedVtx_hitpix==1||diMuonF_m2_FittedVtx_hitpix==1) ){
									ev_isPixelHitOK++;
									if(is2DiMuonsDzOK_FittedVtx){
										ev_is2DiMuonsDzOK_FittedVtx++;
										brokenCounter++;
										if(is2DiMuonsMassOK_FittedVtx){
											ev_is2DiMuonsMassOK_FittedVtx++;
											brokenCounter++;
											if(is2DiMuonsIsoTkOK_FittedVtx){
												ev_is2DiMuonsIsoTkOK_FittedVtx++;
												brokenCounter++;
												if(isDiMuonHLTFired){
													ev_isDiMuonHLTFired++;
													brokenCounter++;
													triggerFlag_std++;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
			Event_Fail_Reason->Fill(brokenCounter);
			//}//opening angle cut
			//}// fiducial cut in numerator
			//}}}

			//GEN Fiducial cut to determine if event is a fake
			//{{{
			if(is4GenMu8){
				if(fabs(genA0_Lxy)<4.4 && fabs(genA1_Lxy)<4.4 && fabs(genA0_Lz)<34.5 && fabs(genA1_Lz)<34.5){
					triggerFlag_lxy++;
				}
			}
			//}}}

			//Real Loop/Matching/Plots.  The GEN level fiducial cut is passed for the numerator
			//{{{
			if(triggerFlag_std > 0 && triggerFlag_lxy > 0){
				realFlag++;
				//Use eta and phi to match diMuon to correct GenA (ie: match diMuonC and diMuonF to genA0 and genA1)
				//genA0 shouldusually be diMuonC, unless both dimuons have high pT and are in the barrel.  In that case, the assignment is random

				//Basic distributions for GEN and combined RECO level objects
				//{{{
				//GEN level distributions				
				Real_Gen_Lxy->Fill(genA0_Lxy);
				Real_Gen_Lxy->Fill(genA1_Lxy);		
				Real_Gen_Lz->Fill(genA0_Lz); 
				Real_Gen_Lz->Fill(genA1_Lz); 
				Real_Gen_Eta->Fill(genA1_eta);
				Real_Gen_Eta->Fill(genA0_eta);
				Real_Gen_Phi->Fill(genA1_phi);
				Real_Gen_Phi->Fill(genA0_phi);
				Real_Gen_pT->Fill(sqrt(genA1_px*genA1_px+genA1_py*genA1_py)); 
				Real_Gen_pT->Fill(sqrt(genA0_px*genA0_px+genA0_py*genA0_py)); 
				Real_Gen_MassCompatability->Fill(genA0_m, genA1_m);
				Real_Gen_pT_vs_Lxy->Fill(genA0_Lxy,sqrt(genA0_px*genA0_px+genA0_py*genA0_py));
				Real_Gen_pT_vs_Lxy->Fill(genA1_Lxy,sqrt(genA1_px*genA1_px+genA1_py*genA1_py));
				Real_dimuon1_Gen_Lxy->Fill(genA0_Lxy);
				Real_dimuon2_Gen_Lxy->Fill(genA1_Lxy);
				Real_dimuon1_Gen_Lz->Fill(genA0_Lz);
				Real_dimuon2_Gen_Lz->Fill(genA1_Lz);
				Real_dimuon2_Gen_Eta->Fill(genA1_eta);
				Real_dimuon1_Gen_Eta->Fill(genA0_eta);
				Real_dimuon2_Gen_Phi->Fill(genA1_phi);
				Real_dimuon1_Gen_Phi->Fill(genA0_phi);
				Real_dimuon2_Gen_pT->Fill(sqrt(genA1_px*genA1_px+genA1_py*genA1_py));
				Real_dimuon1_Gen_pT->Fill(sqrt(genA0_px*genA0_px+genA0_py*genA0_py));
				//Combined RECO level distributions				
				if(diMuonC_FittedVtx_Lxy > -800) Real_Reco_Lxy->Fill(diMuonC_FittedVtx_Lxy); 
				if(diMuonF_FittedVtx_Lxy > -800) Real_Reco_Lxy->Fill(diMuonF_FittedVtx_Lxy); 
				if(diMuonC_FittedVtx_eta > -800) Real_Reco_Eta->Fill(diMuonC_FittedVtx_eta);
				if(diMuonF_FittedVtx_eta > -800) Real_Reco_Eta->Fill(diMuonF_FittedVtx_eta);
				if(diMuonC_FittedVtx_phi > -800) Real_Reco_Phi->Fill(diMuonC_FittedVtx_phi);
				if(diMuonF_FittedVtx_phi > -800) Real_Reco_Phi->Fill(diMuonF_FittedVtx_phi);
				if(diMuonC_FittedVtx_px > -800 && diMuonC_FittedVtx_py > -800) Real_Reco_pT->Fill(sqrt(diMuonC_FittedVtx_px*diMuonC_FittedVtx_px+diMuonC_FittedVtx_py*diMuonC_FittedVtx_py));
				if(diMuonF_FittedVtx_px > -800 && diMuonF_FittedVtx_py > -800) Real_Reco_pT->Fill(sqrt(diMuonF_FittedVtx_px*diMuonF_FittedVtx_px+diMuonF_FittedVtx_py*diMuonF_FittedVtx_py));
				if(diMuonC_FittedVtx_m > -800) Real_Reco_MassCompatability->Fill(diMuonC_FittedVtx_m,diMuonF_FittedVtx_m); 
				if(diMuonF_FittedVtx_px > -800 && diMuonF_FittedVtx_py > -800 && diMuonF_FittedVtx_Lxy > -800) Real_Reco_pT_vs_Lxy->Fill(diMuonF_FittedVtx_Lxy, sqrt(diMuonF_FittedVtx_px*diMuonF_FittedVtx_px+diMuonF_FittedVtx_py*diMuonF_FittedVtx_py));	
				if(diMuonC_FittedVtx_px > -800 && diMuonC_FittedVtx_py > -800 && diMuonC_FittedVtx_Lxy > -800) Real_Reco_pT_vs_Lxy->Fill(diMuonC_FittedVtx_Lxy, sqrt(diMuonC_FittedVtx_px*diMuonC_FittedVtx_px+diMuonC_FittedVtx_py*diMuonC_FittedVtx_py));
				if(diMuonC_FittedVtx_eta > -800 && diMuonC_FittedVtx_phi > -800){
					Real_Reco_Eta_vs_Phi->Fill(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_phi);
				}
				if(diMuonF_FittedVtx_eta > -800 && diMuonF_FittedVtx_phi > -800){
					Real_Reco_Eta_vs_Phi->Fill(diMuonF_FittedVtx_eta, diMuonF_FittedVtx_phi);
				}
				if(diMuonC_FittedVtx_eta > -800 && diMuonC_FittedVtx_Lxy > -800){
					Real_Reco_Eta_vs_Lxy->Fill(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_Lxy);
				}
				if(diMuonF_FittedVtx_eta > -800 && diMuonF_FittedVtx_Lxy > -800){
					Real_Reco_Eta_vs_Lxy->Fill(diMuonF_FittedVtx_eta, diMuonF_FittedVtx_Lxy);
				}	
				Real_Reco_Eta_vs_VertexZ->Fill(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_vz);
				Real_Reco_Eta_vs_VertexZ->Fill(diMuonF_FittedVtx_eta, diMuonF_FittedVtx_vz);
				Real_Reco_Eta_vs_VertexR->Fill(diMuonC_FittedVtx_eta, sqrt((diMuonC_FittedVtx_vx*diMuonC_FittedVtx_vx)+(diMuonC_FittedVtx_vy*diMuonC_FittedVtx_vy)));
				Real_Reco_Eta_vs_VertexR->Fill(diMuonF_FittedVtx_eta, sqrt((diMuonF_FittedVtx_vx*diMuonF_FittedVtx_vx)+(diMuonF_FittedVtx_vy*diMuonF_FittedVtx_vy)));

				//}}}

				//real match loop so that GEN-RECO level objects may be compared
				//{{{

				vector< float > gen_real_muons_phi;
				vector< float > gen_real_muons_eta;
				vector< float > reco_real_muons_phi;
				vector< float > reco_real_muons_eta;

				gen_real_muons_phi.push_back(genA0Mu0_phi);
				gen_real_muons_phi.push_back(genA0Mu1_phi);
				gen_real_muons_phi.push_back(genA1Mu0_phi);
				gen_real_muons_phi.push_back(genA1Mu1_phi);
				gen_real_muons_eta.push_back(genA0Mu0_eta);
				gen_real_muons_eta.push_back(genA0Mu1_eta);
				gen_real_muons_eta.push_back(genA1Mu0_eta);
				gen_real_muons_eta.push_back(genA1Mu1_eta);

				if(selMu0_eta > -20){
					reco_real_muons_phi.push_back(selMu0_phi); 
					reco_real_muons_eta.push_back(selMu0_eta); 
				}
				if(selMu1_eta > -20){ 
					reco_real_muons_phi.push_back(selMu1_phi);
					reco_real_muons_eta.push_back(selMu1_eta);
				}
				if(selMu2_eta > -20){ 
					reco_real_muons_phi.push_back(selMu2_phi);
					reco_real_muons_eta.push_back(selMu2_eta);
				}
				if(selMu3_eta > -20){ 
					reco_real_muons_phi.push_back(selMu3_phi);
					reco_real_muons_eta.push_back(selMu3_eta);
				}

				//Now real_match GEN and RECO level real_muons, but only allow one RECO real_match to each GEN muon.
				int bestreal_match_no_duplicates_0 = -1; //this is the RECO index of the real_match to GEN 00
				int bestreal_match_no_duplicates_1 = -1; // 01
				int bestreal_match_no_duplicates_2 = -1; // 10
				int bestreal_match_no_duplicates_3 = -1; // 11
				vector< vector<double> >  dR_real_g_r_real;
				for(int g = 0; g < 4; g++){ //There are always 4 GEN real_muons
					double deltaR_real_noDuplicates_real = 9999;
					for(int r = 0; r < reco_real_muons_phi.size(); r++){
						vector<double> dR_realgr_real;
						double dphi_real = My_dPhi(reco_real_muons_phi[r], gen_real_muons_phi[g]);
						double deta_real = reco_real_muons_eta[r] - gen_real_muons_eta[g];
						double dR_real = sqrt(dphi_real*dphi_real + deta_real*deta_real);

						dR_realgr_real.push_back(dR_real);
						dR_realgr_real.push_back(g);
						dR_realgr_real.push_back(r);
						//cout << "pushing back dR_real, g, r: " << dR_real << ", " << g << ", " << r << endl;
						dR_real_g_r_real.push_back(dR_realgr_real);
					}
				}
				//quick loop to print dR_real_g_r_real
				double real_matcherFirst_real = 9999;
				int First_real;
				for(int i = 0; i< dR_real_g_r_real.size(); i++){
					double running_real_matchFirst_real = dR_real_g_r_real[i][0]; //This is the dR_real of entry i
					if(running_real_matchFirst_real < real_matcherFirst_real){
						real_matcherFirst_real = running_real_matchFirst_real;
						First_real = i;
						if(dR_real_g_r_real[i][1] == 0){
							bestreal_match_no_duplicates_0 = dR_real_g_r_real[i][2];
						}
						if(dR_real_g_r_real[i][1] == 1){
							bestreal_match_no_duplicates_1 = dR_real_g_r_real[i][2];
						}
						if(dR_real_g_r_real[i][1] == 2){
							bestreal_match_no_duplicates_2 = dR_real_g_r_real[i][2];
						}
						if(dR_real_g_r_real[i][1] == 3){
							bestreal_match_no_duplicates_3 = dR_real_g_r_real[i][2];
						}
					}
				}
				double real_matcherSecond_real = 9999;
				int Second_real;
				for(int i = 0; i< dR_real_g_r_real.size(); i++){
					double running_real_matchSecond_real = dR_real_g_r_real[i][0]; //This is the dR_real of entry i
					if(running_real_matchSecond_real < real_matcherSecond_real){
						if(dR_real_g_r_real[First_real][1] != dR_real_g_r_real[i][1] && dR_real_g_r_real[First_real][2] != dR_real_g_r_real[i][2]){ //make sure that the Second_real best real_match isn't the same RECO or GEN particles
							real_matcherSecond_real = running_real_matchSecond_real;
							Second_real = i;
							if(dR_real_g_r_real[i][1] == 0){
								bestreal_match_no_duplicates_0 = dR_real_g_r_real[i][2];
							}
							if(dR_real_g_r_real[i][1] == 1){
								bestreal_match_no_duplicates_1 = dR_real_g_r_real[i][2];
							}
							if(dR_real_g_r_real[i][1] == 2){
								bestreal_match_no_duplicates_2 = dR_real_g_r_real[i][2];
							}
							if(dR_real_g_r_real[i][1] == 3){
								bestreal_match_no_duplicates_3 = dR_real_g_r_real[i][2];
							}
						}
					}
				}
				double real_matcherThird_real = 9999;
				int Third_real;
				for(int i = 0; i< dR_real_g_r_real.size(); i++){
					double running_real_matchThird_real = dR_real_g_r_real[i][0]; //This is the dR_real of entry i
					if(running_real_matchThird_real < real_matcherThird_real){
						if(dR_real_g_r_real[First_real][1] != dR_real_g_r_real[i][1] && dR_real_g_r_real[First_real][2] != dR_real_g_r_real[i][2] && dR_real_g_r_real[Second_real][1] != dR_real_g_r_real[i][1] && dR_real_g_r_real[Second_real][2] != dR_real_g_r_real[i][2]){
							real_matcherThird_real = running_real_matchThird_real;
							Third_real = i;
							if(dR_real_g_r_real[i][1] == 0){
								bestreal_match_no_duplicates_0 = dR_real_g_r_real[i][2];
							}                                                                
							if(dR_real_g_r_real[i][1] == 1){
								bestreal_match_no_duplicates_1 = dR_real_g_r_real[i][2];
							}
							if(dR_real_g_r_real[i][1] == 2){
								bestreal_match_no_duplicates_2 = dR_real_g_r_real[i][2];
							}
							if(dR_real_g_r_real[i][1] == 3){
								bestreal_match_no_duplicates_3 = dR_real_g_r_real[i][2];
							}
						}
					}
				}
				double real_matcherFourth_real = 9999;
				int Fourth_real;
				for(int i = 0; i< dR_real_g_r_real.size(); i++){
					double running_real_matchFourth_real = dR_real_g_r_real[i][0]; //This is the dR_real of entry i
					if(running_real_matchFourth_real < real_matcherFourth_real){
						if(dR_real_g_r_real[First_real][1] != dR_real_g_r_real[i][1] && dR_real_g_r_real[First_real][2] != dR_real_g_r_real[i][2] && dR_real_g_r_real[Second_real][1] != dR_real_g_r_real[i][1] && dR_real_g_r_real[Second_real][2] != dR_real_g_r_real[i][2] && dR_real_g_r_real[Third_real][1] != dR_real_g_r_real[i][1] && dR_real_g_r_real[Third_real][2] != dR_real_g_r_real[i][2]){
							real_matcherFourth_real = running_real_matchFourth_real;
							Fourth_real = i;
							if(dR_real_g_r_real[i][1] == 0){
								bestreal_match_no_duplicates_0 = dR_real_g_r_real[i][2];
							}
							if(dR_real_g_r_real[i][1] == 1){
								bestreal_match_no_duplicates_1 = dR_real_g_r_real[i][2];
							}
							if(dR_real_g_r_real[i][1] == 2){
								bestreal_match_no_duplicates_2 = dR_real_g_r_real[i][2];
							}
							if(dR_real_g_r_real[i][1] == 3){
								bestreal_match_no_duplicates_3 = dR_real_g_r_real[i][2];
							}
						}
					}
				}
				//std::cout << "" << std::endl;
				//std::cout << "First_real, Second_real, Third_real, Fourth_real best real_matches: " << First_real << ", " << Second_real << ", " << Third_real << ", " << Fourth_real << endl;
				//std::cout << "" << std::endl;
				//std::cout << "The best real_match not allowing duplicates to GEN 00 is " << bestreal_match_no_duplicates_0 << std::endl;
				//std::cout << "The best real_match not allowing duplicates to GEN 01 is " << bestreal_match_no_duplicates_1 << std::endl;
				//std::cout << "The best real_match not allowing duplicates to GEN 10 is " << bestreal_match_no_duplicates_2 << std::endl;
				//std::cout << "The best real_match not allowing duplicates to GEN 11 is " << bestreal_match_no_duplicates_3 << std::endl;
				//std::cout << "" << std::endl;


				//real_match RECO level real_muons to RECO level direal_muons

				int diMuonFreal_match0 = -1;
				int diMuonFreal_match1 = -1;
				int diMuonCreal_match0 = -1;
				int diMuonCreal_match1 = -1;

				vector< float > dimuonC_real_matches;
				vector< float > dimuonF_real_matches;
				int diMuonC_real_match0 = -1;
				int diMuonC_real_match1 = -1;
				int diMuonF_real_match0 = -1;
				int diMuonF_real_match1 = -1;

				if(diMuonC_FittedVtx_eta > -800 && diMuonF_FittedVtx_eta > -800){
					double diMuonC_deltaR_real = 9999;
					//cout << "Finding best real_match to diMuonC" << endl;
					for(int r = 0; r < reco_real_muons_phi.size(); r++){ //Find best real_match to diMuonC
						double dphi_real = My_dPhi(reco_real_muons_phi[r], diMuonC_FittedVtx_phi);
						double deta_real = reco_real_muons_eta[r] - diMuonC_FittedVtx_eta;
						double dR_real = sqrt(dphi_real*dphi_real + deta_real*deta_real);
						//cout << "dR_real for reco muon " << r << " is " << dR_real << " and the current best deltaR_real is " << diMuonC_deltaR_real << endl;
						if(dR_real < diMuonC_deltaR_real){
							diMuonC_deltaR_real = dR_real;
							diMuonC_real_match0 = r;
						}
					}
					diMuonC_deltaR_real = 9999;
					//cout << "Finding the Second_real best real_match to diMuonC" << endl;
					for(int r = 0; r < reco_real_muons_phi.size(); r++){ //Find Second_real best real_match to diMuonC
						if(r != diMuonC_real_match0){
							double dphi_real = My_dPhi(reco_real_muons_phi[r], diMuonC_FittedVtx_phi);
							double deta_real = reco_real_muons_eta[r] - diMuonC_FittedVtx_eta;
							double dR_real = sqrt(dphi_real*dphi_real + deta_real*deta_real);
							//cout << "dR_real for reco muon " << r << " is " << dR_real << " and the current best deltaR_real is " << diMuonC_deltaR_real << endl;
							if(dR_real < diMuonC_deltaR_real){
								diMuonC_deltaR_real = dR_real;
								diMuonC_real_match1 = r;
							}
						}
					}

					//Now find diMuonF
					double diMuonF_deltaR_real = 9999;
					//cout << "Finding the best real_match to diMuonF" << endl;
					for(int r = 0; r < reco_real_muons_phi.size(); r++){ //Find best real_match to diMuonF
						double dphi_real = My_dPhi(reco_real_muons_phi[r], diMuonF_FittedVtx_phi);
						double deta_real = reco_real_muons_eta[r] - diMuonF_FittedVtx_eta;
						double dR_real = sqrt(dphi_real*dphi_real + deta_real*deta_real);
						//cout << "dR_real for reco muon " << r << " is " << dR_real << " and the current best deltaR_real is " << diMuonF_deltaR_real << endl;
						if(dR_real < diMuonF_deltaR_real){
							diMuonF_deltaR_real = dR_real;
							diMuonF_real_match0 = r;
						}
					}
					diMuonF_deltaR_real = 9999;
					//cout << "Finding the Second_real best real_match to diMuonF" << endl;
					for(int r = 0; r < reco_real_muons_phi.size(); r++){ //Find Second_real best real_match to diMuonF
						if(r != diMuonF_real_match0){
							double dphi_real = My_dPhi(reco_real_muons_phi[r], diMuonF_FittedVtx_phi);
							double deta_real = reco_real_muons_eta[r] - diMuonF_FittedVtx_eta;
							double dR_real = sqrt(dphi_real*dphi_real + deta_real*deta_real);
							//cout << "dR_real for reco muon " << r << " is " << dR_real << " and the current best deltaR_real is " << diMuonF_deltaR_real << endl;
							if(dR_real < diMuonF_deltaR_real){
								diMuonF_deltaR_real = dR_real;
								diMuonF_real_match1 = r;
							}
						}
					}
					//cout << "The best real_matches to diMuonC are " << diMuonC_real_match0 << " and " << diMuonC_real_match1 << endl;
					//cout << "The best real_matches to diMuonF are " << diMuonF_real_match0 << " and " << diMuonF_real_match1 << endl;
				}

				int problem_nodupCounter = 0;
				if(bestreal_match_no_duplicates_0 == diMuonC_real_match0){
					if(bestreal_match_no_duplicates_1 != diMuonC_real_match1) problem_nodupCounter++;
				}
				if(bestreal_match_no_duplicates_0 == diMuonC_real_match1){
					if(bestreal_match_no_duplicates_1 != diMuonC_real_match0) problem_nodupCounter++;
				}
				if(bestreal_match_no_duplicates_0 == diMuonF_real_match0){
					if(bestreal_match_no_duplicates_1 != diMuonF_real_match1) problem_nodupCounter++;
				}
				if(bestreal_match_no_duplicates_0 == diMuonF_real_match1){
					if(bestreal_match_no_duplicates_1 != diMuonF_real_match0) problem_nodupCounter++;
				}
				if(bestreal_match_no_duplicates_2 == diMuonC_real_match0){
					if(bestreal_match_no_duplicates_3 != diMuonC_real_match1) problem_nodupCounter++;
				}
				if(bestreal_match_no_duplicates_2 == diMuonC_real_match1){
					if(bestreal_match_no_duplicates_3 != diMuonC_real_match0) problem_nodupCounter++;
				}
				if(bestreal_match_no_duplicates_2 == diMuonF_real_match0){
					if(bestreal_match_no_duplicates_3 != diMuonF_real_match1) problem_nodupCounter++;
				}
				if(bestreal_match_no_duplicates_2 == diMuonF_real_match1){
					if(bestreal_match_no_duplicates_3 != diMuonF_real_match0) problem_nodupCounter++;
				}
				if(problem_nodupCounter > 0) cout << "There is a problem with no duplicate real_matching" << endl;

				//Match GEN dimuons to RECO dimuons
				//  GEN dimuon 	                                = genA0
				//  GEN muons to genA0                          = genA0Mu0 and genA0Mu1 
				//  These GEN muons have RECO matches           = reco_real_muons_phi[bestreal_match_no_duplicates_0] and reco_real_muons_phi[bestreal_match_no_duplicates_1]
				//  These RECO muons are either dimuon C or F   = reco_real_muons_eta[diMuonC_real_match0] and reco_real_muons_eta[diMuonC_real_match1] OR reco_real_muons_eta[diMuonF_real_match0] and reco_real_muons_eta[diMuonF_real_match1] 
				//  Check if reco C and F correspond to A0 or A1: (MatchRECOtoGENdimuons)
				//  NOW, I can finally check the residuals between GEN mu -> RECO mu and GEN dimu -> RECO dimu

				//Plot GEN dimu -> RECO dimu residuals
				//
				if(MatchRECOtoGENdimuons(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_phi, diMuonF_FittedVtx_eta, diMuonF_FittedVtx_phi, genA0_eta, genA0_phi, genA1_eta, genA0_phi) == 0){ //diMuonC -> A0, diMuonF -> A1
					//eta
					Real_dimuon1_EtaResidual->Fill(genA0_eta - diMuonC_FittedVtx_eta);
					Real_dimuon1_EtaResidual_vs_Eta->Fill(genA0_eta, genA0_eta - diMuonC_FittedVtx_eta);
					Real_dimuon1_EtaResidual_vs_Lxy->Fill(genA0_Lxy, genA0_eta - diMuonC_FittedVtx_eta);

					Real_dimuon2_EtaResidual->Fill(genA1_eta - diMuonF_FittedVtx_eta);
					Real_dimuon2_EtaResidual_vs_Eta->Fill(genA1_eta, genA1_eta - diMuonF_FittedVtx_eta);
					Real_dimuon2_EtaResidual_vs_Lxy->Fill(genA1_Lxy, genA1_eta - diMuonF_FittedVtx_eta);

					//phi
					Real_dimuon1_PhiResidual->Fill(genA0_phi - diMuonC_FittedVtx_phi);
					Real_dimuon1_PhiResidual_vs_Phi->Fill(genA0_phi, genA0_phi - diMuonC_FittedVtx_phi);
					Real_dimuon1_PhiResidual_vs_Lxy->Fill(genA0_Lxy, genA0_phi - diMuonC_FittedVtx_phi);

					Real_dimuon2_PhiResidual->Fill(genA1_phi - diMuonF_FittedVtx_phi);
					Real_dimuon2_PhiResidual_vs_Phi->Fill(genA1_phi, genA1_phi - diMuonF_FittedVtx_phi);
					Real_dimuon2_PhiResidual_vs_Lxy->Fill(genA1_Lxy, genA1_phi - diMuonF_FittedVtx_phi);

					//Lxy
					Real_dimuon1_LxyResidual->Fill(genA0_Lxy - diMuonC_FittedVtx_Lxy);
					Real_dimuon1_LxyResidual_vs_Lxy->Fill(genA0_Lxy, genA0_Lxy - diMuonC_FittedVtx_Lxy);

					Real_dimuon2_LxyResidual->Fill(genA1_Lxy - diMuonF_FittedVtx_Lxy);
					Real_dimuon2_LxyResidual_vs_Lxy->Fill(genA1_Lxy, genA1_Lxy - diMuonF_FittedVtx_Lxy);

					//vertex
					Real_Dimuon1_GEN_Dimuon_vertex_r->Fill(sqrt(genA0Mu0_vx*genA0Mu0_vx + genA0Mu0_vy*genA0Mu0_vy));
					Real_Dimuon1_RECO_Dimuon_vertex_r->Fill(sqrt(diMuonC_FittedVtx_vx*diMuonC_FittedVtx_vx + diMuonC_FittedVtx_vy*diMuonC_FittedVtx_vy));
					Real_Dimuon1_Dimuon_vertex_r_Residual->Fill( sqrt(genA0Mu0_vx*genA0Mu0_vx + genA0Mu0_vy*genA0Mu0_vy) - sqrt(diMuonC_FittedVtx_vx*diMuonC_FittedVtx_vx + diMuonC_FittedVtx_vy*diMuonC_FittedVtx_vy));
					Real_Dimuon1_Dimuon_vertex_r_Residual_vs_GEN->Fill(sqrt(genA0Mu0_vx*genA0Mu0_vx + genA0Mu0_vy*genA0Mu0_vy), sqrt(genA0Mu0_vx*genA0Mu0_vx + genA0Mu0_vy*genA0Mu0_vy) - sqrt(diMuonC_FittedVtx_vx*diMuonC_FittedVtx_vx + diMuonC_FittedVtx_vy*diMuonC_FittedVtx_vy));
					Real_Dimuon1_Dimuon_Lxy_Residual_vs_GEN_vertex_r->Fill(sqrt(genA0Mu0_vx*genA0Mu0_vx + genA0Mu0_vy*genA0Mu0_vy), genA0_Lxy - diMuonC_FittedVtx_Lxy);
					Real_Dimuon1_Dimuon_Lxy_Residual_vs_RECO_vertex_r->Fill(sqrt(diMuonC_FittedVtx_vx*diMuonC_FittedVtx_vx + diMuonC_FittedVtx_vy*diMuonC_FittedVtx_vy), genA0_Lxy - diMuonC_FittedVtx_Lxy);

					Real_Dimuon1_GEN_Dimuon_vertex_z->Fill(genA0Mu0_vz);
					Real_Dimuon1_RECO_Dimuon_vertex_z->Fill(diMuonC_FittedVtx_vz);
					Real_Dimuon1_Dimuon_vertex_z_Residual->Fill(genA0Mu0_vz - diMuonC_FittedVtx_vz);
					Real_Dimuon1_Dimuon_vertex_z_Residual_vs_GEN->Fill(genA0Mu0_vz, genA0Mu0_vz - diMuonC_FittedVtx_vz);
					Real_Dimuon1_Dimuon_Lxy_Residual_vs_GEN_vertex_z->Fill(genA0Mu0_vz, genA0_Lxy - diMuonC_FittedVtx_Lxy);
					Real_Dimuon1_Dimuon_Lxy_Residual_vs_RECO_vertex_z->Fill(diMuonC_FittedVtx_vz, genA0_Lxy - diMuonC_FittedVtx_Lxy);

					Real_Dimuon2_GEN_Dimuon_vertex_r->Fill(sqrt(genA1Mu0_vx*genA1Mu0_vx + genA1Mu0_vy*genA1Mu0_vy));
					Real_Dimuon2_RECO_Dimuon_vertex_r->Fill(sqrt(diMuonF_FittedVtx_vx*diMuonF_FittedVtx_vx + diMuonF_FittedVtx_vy*diMuonF_FittedVtx_vy));
					Real_Dimuon2_Dimuon_vertex_r_Residual->Fill( sqrt(genA1Mu0_vx*genA1Mu0_vx + genA1Mu0_vy*genA1Mu0_vy) - sqrt(diMuonF_FittedVtx_vx*diMuonF_FittedVtx_vx + diMuonF_FittedVtx_vy*diMuonF_FittedVtx_vy));
					Real_Dimuon2_Dimuon_vertex_r_Residual_vs_GEN->Fill(sqrt(genA1Mu0_vx*genA1Mu0_vx + genA1Mu0_vy*genA1Mu0_vy), sqrt(genA1Mu0_vx*genA1Mu0_vx + genA1Mu0_vy*genA1Mu0_vy) - sqrt(diMuonF_FittedVtx_vx*diMuonF_FittedVtx_vx + diMuonF_FittedVtx_vy*diMuonF_FittedVtx_vy));
					Real_Dimuon2_Dimuon_Lxy_Residual_vs_GEN_vertex_r->Fill(sqrt(genA1Mu0_vx*genA1Mu0_vx + genA1Mu0_vy*genA1Mu0_vy), genA1_Lxy - diMuonF_FittedVtx_Lxy);
					Real_Dimuon2_Dimuon_Lxy_Residual_vs_RECO_vertex_r->Fill(sqrt(diMuonF_FittedVtx_vx*diMuonF_FittedVtx_vx + diMuonF_FittedVtx_vy*diMuonF_FittedVtx_vy), genA1_Lxy - diMuonF_FittedVtx_Lxy);

					Real_Dimuon2_GEN_Dimuon_vertex_z->Fill(genA1Mu0_vz);
					Real_Dimuon2_RECO_Dimuon_vertex_z->Fill(diMuonF_FittedVtx_vz);
					Real_Dimuon2_Dimuon_vertex_z_Residual->Fill(genA1Mu0_vz - diMuonF_FittedVtx_vz);
					Real_Dimuon2_Dimuon_vertex_z_Residual_vs_GEN->Fill(genA1Mu0_vz, genA1Mu0_vz - diMuonF_FittedVtx_vz);
					Real_Dimuon2_Dimuon_Lxy_Residual_vs_GEN_vertex_z->Fill(genA1Mu0_vz, genA1_Lxy - diMuonF_FittedVtx_Lxy);
					Real_Dimuon2_Dimuon_Lxy_Residual_vs_RECO_vertex_z->Fill(diMuonF_FittedVtx_vz, genA1_Lxy - diMuonF_FittedVtx_Lxy);

					//2Dim distributions
					Real_dimuon1_Reco_Eta_vs_Phi->Fill(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_phi);
					Real_dimuon1_Reco_Eta_vs_Lxy->Fill(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_Lxy);
					Real_dimuon1_Reco_Lxy->Fill(diMuonC_FittedVtx_Lxy);
					Real_dimuon1_Reco_Eta->Fill(diMuonC_FittedVtx_eta);
					Real_dimuon1_Reco_Phi->Fill(diMuonC_FittedVtx_phi);
					Real_dimuon1_Reco_pT->Fill(sqrt(diMuonC_FittedVtx_px*diMuonC_FittedVtx_px+diMuonC_FittedVtx_py*diMuonC_FittedVtx_py));
					Real_dimuon1_Reco_MassCompatability->Fill(diMuonC_FittedVtx_m,diMuonF_FittedVtx_m);

					Real_dimuon2_Reco_Eta_vs_Phi->Fill(diMuonF_FittedVtx_eta, diMuonF_FittedVtx_phi);
					Real_dimuon2_Reco_Eta_vs_Lxy->Fill(diMuonF_FittedVtx_eta, diMuonF_FittedVtx_Lxy);
					Real_dimuon2_Reco_Lxy->Fill(diMuonF_FittedVtx_Lxy);
					Real_dimuon2_Reco_Eta->Fill(diMuonF_FittedVtx_eta);
					Real_dimuon2_Reco_Phi->Fill(diMuonF_FittedVtx_phi);
					Real_dimuon2_Reco_pT->Fill(sqrt(diMuonF_FittedVtx_px*diMuonF_FittedVtx_px+diMuonF_FittedVtx_py*diMuonF_FittedVtx_py));

				}else{ //diMuonC -> A1, diMuonF -> A0
					//eta
					Real_dimuon1_EtaResidual->Fill(genA0_eta - diMuonF_FittedVtx_eta);
					Real_dimuon1_EtaResidual_vs_Eta->Fill(genA0_eta, genA0_eta - diMuonF_FittedVtx_eta);
					Real_dimuon1_EtaResidual_vs_Lxy->Fill(genA0_Lxy, genA0_eta - diMuonF_FittedVtx_eta);

					Real_dimuon2_EtaResidual->Fill(genA1_eta - diMuonC_FittedVtx_eta);
					Real_dimuon2_EtaResidual_vs_Eta->Fill(genA1_eta, genA1_eta - diMuonC_FittedVtx_eta);
					Real_dimuon2_EtaResidual_vs_Lxy->Fill(genA1_Lxy, genA1_eta - diMuonC_FittedVtx_eta);

					//phi
					Real_dimuon1_PhiResidual->Fill(genA0_phi - diMuonF_FittedVtx_phi);
					Real_dimuon1_PhiResidual_vs_Phi->Fill(genA0_phi, genA0_phi - diMuonF_FittedVtx_phi);
					Real_dimuon1_PhiResidual_vs_Lxy->Fill(genA0_Lxy, genA0_phi - diMuonF_FittedVtx_phi);

					Real_dimuon2_PhiResidual->Fill(genA1_phi - diMuonC_FittedVtx_phi);
					Real_dimuon2_PhiResidual_vs_Phi->Fill(genA1_phi, genA1_phi - diMuonC_FittedVtx_phi);
					Real_dimuon2_PhiResidual_vs_Lxy->Fill(genA1_Lxy, genA1_phi - diMuonC_FittedVtx_phi);

					//Lxy
					Real_dimuon1_LxyResidual->Fill(genA0_Lxy - diMuonF_FittedVtx_Lxy);
					Real_dimuon1_LxyResidual_vs_Lxy->Fill(genA0_Lxy, genA0_Lxy - diMuonF_FittedVtx_Lxy);

					Real_dimuon2_LxyResidual->Fill(genA1_Lxy - diMuonC_FittedVtx_Lxy);
					Real_dimuon2_LxyResidual_vs_Lxy->Fill(genA1_Lxy, genA1_Lxy - diMuonC_FittedVtx_Lxy);

					//vertex
					Real_Dimuon1_GEN_Dimuon_vertex_r->Fill(sqrt(genA0Mu0_vx*genA0Mu0_vx + genA0Mu0_vy*genA0Mu0_vy));
					Real_Dimuon1_RECO_Dimuon_vertex_r->Fill(sqrt(diMuonF_FittedVtx_vx*diMuonF_FittedVtx_vx + diMuonF_FittedVtx_vy*diMuonF_FittedVtx_vy));
					Real_Dimuon1_Dimuon_vertex_r_Residual->Fill( sqrt(genA0Mu0_vx*genA0Mu0_vx + genA0Mu0_vy*genA0Mu0_vy) - sqrt(diMuonF_FittedVtx_vx*diMuonF_FittedVtx_vx + diMuonF_FittedVtx_vy*diMuonF_FittedVtx_vy));
					Real_Dimuon1_Dimuon_vertex_r_Residual_vs_GEN->Fill(sqrt(genA0Mu0_vx*genA0Mu0_vx + genA0Mu0_vy*genA0Mu0_vy), sqrt(genA0Mu0_vx*genA0Mu0_vx + genA0Mu0_vy*genA0Mu0_vy) - sqrt(diMuonF_FittedVtx_vx*diMuonF_FittedVtx_vx + diMuonF_FittedVtx_vy*diMuonF_FittedVtx_vy));
					Real_Dimuon1_Dimuon_Lxy_Residual_vs_GEN_vertex_r->Fill(sqrt(genA0Mu0_vx*genA0Mu0_vx + genA0Mu0_vy*genA0Mu0_vy), genA0_Lxy - diMuonF_FittedVtx_Lxy);
					Real_Dimuon1_Dimuon_Lxy_Residual_vs_RECO_vertex_r->Fill(sqrt(diMuonF_FittedVtx_vx*diMuonF_FittedVtx_vx + diMuonF_FittedVtx_vy*diMuonF_FittedVtx_vy), genA0_Lxy - diMuonF_FittedVtx_Lxy);

					Real_Dimuon1_GEN_Dimuon_vertex_z->Fill(genA0Mu0_vz);
					Real_Dimuon1_RECO_Dimuon_vertex_z->Fill(diMuonF_FittedVtx_vz);
					Real_Dimuon1_Dimuon_vertex_z_Residual->Fill(genA0Mu0_vz - diMuonF_FittedVtx_vz);
					Real_Dimuon1_Dimuon_vertex_z_Residual_vs_GEN->Fill(genA0Mu0_vz, genA0Mu0_vz - diMuonF_FittedVtx_vz);
					Real_Dimuon1_Dimuon_Lxy_Residual_vs_GEN_vertex_z->Fill(genA0Mu0_vz, genA0_Lxy - diMuonF_FittedVtx_Lxy);
					Real_Dimuon1_Dimuon_Lxy_Residual_vs_RECO_vertex_z->Fill(diMuonF_FittedVtx_vz, genA0_Lxy - diMuonF_FittedVtx_Lxy);

					Real_Dimuon2_GEN_Dimuon_vertex_r->Fill(sqrt(genA1Mu0_vx*genA1Mu0_vx + genA1Mu0_vy*genA1Mu0_vy));
					Real_Dimuon2_RECO_Dimuon_vertex_r->Fill(sqrt(diMuonC_FittedVtx_vx*diMuonC_FittedVtx_vx + diMuonC_FittedVtx_vy*diMuonC_FittedVtx_vy));
					Real_Dimuon2_Dimuon_vertex_r_Residual->Fill( sqrt(genA1Mu0_vx*genA1Mu0_vx + genA1Mu0_vy*genA1Mu0_vy) - sqrt(diMuonC_FittedVtx_vx*diMuonC_FittedVtx_vx + diMuonC_FittedVtx_vy*diMuonC_FittedVtx_vy));
					Real_Dimuon2_Dimuon_vertex_r_Residual_vs_GEN->Fill(sqrt(genA1Mu0_vx*genA1Mu0_vx + genA1Mu0_vy*genA1Mu0_vy), sqrt(genA1Mu0_vx*genA1Mu0_vx + genA1Mu0_vy*genA1Mu0_vy) - sqrt(diMuonC_FittedVtx_vx*diMuonC_FittedVtx_vx + diMuonC_FittedVtx_vy*diMuonC_FittedVtx_vy));
					Real_Dimuon2_Dimuon_Lxy_Residual_vs_GEN_vertex_r->Fill(sqrt(genA1Mu0_vx*genA1Mu0_vx + genA1Mu0_vy*genA1Mu0_vy), genA1_Lxy - diMuonC_FittedVtx_Lxy);
					Real_Dimuon2_Dimuon_Lxy_Residual_vs_RECO_vertex_r->Fill(sqrt(diMuonC_FittedVtx_vx*diMuonC_FittedVtx_vx + diMuonC_FittedVtx_vy*diMuonC_FittedVtx_vy), genA1_Lxy - diMuonC_FittedVtx_Lxy);

					Real_Dimuon2_GEN_Dimuon_vertex_z->Fill(genA1Mu0_vz);
					Real_Dimuon2_RECO_Dimuon_vertex_z->Fill(diMuonC_FittedVtx_vz);
					Real_Dimuon2_Dimuon_vertex_z_Residual->Fill(genA1Mu0_vz - diMuonC_FittedVtx_vz);
					Real_Dimuon2_Dimuon_vertex_z_Residual_vs_GEN->Fill(genA1Mu0_vz, genA1Mu0_vz - diMuonC_FittedVtx_vz);
					Real_Dimuon2_Dimuon_Lxy_Residual_vs_GEN_vertex_z->Fill(genA1Mu0_vz, genA1_Lxy - diMuonC_FittedVtx_Lxy);
					Real_Dimuon2_Dimuon_Lxy_Residual_vs_RECO_vertex_z->Fill(diMuonC_FittedVtx_vz, genA1_Lxy - diMuonC_FittedVtx_Lxy);

					//2Dim distributions
					Real_dimuon1_Reco_Eta_vs_Phi->Fill(diMuonF_FittedVtx_eta, diMuonF_FittedVtx_phi);
					Real_dimuon1_Reco_Eta_vs_Lxy->Fill(diMuonF_FittedVtx_eta, diMuonF_FittedVtx_Lxy);
					Real_dimuon1_Reco_Lxy->Fill(diMuonF_FittedVtx_Lxy);
					Real_dimuon1_Reco_Eta->Fill(diMuonF_FittedVtx_eta);
					Real_dimuon1_Reco_Phi->Fill(diMuonF_FittedVtx_phi);
					Real_dimuon1_Reco_pT->Fill(sqrt(diMuonF_FittedVtx_px*diMuonF_FittedVtx_px+diMuonF_FittedVtx_py*diMuonF_FittedVtx_py));
					Real_dimuon1_Reco_MassCompatability->Fill(diMuonF_FittedVtx_m,diMuonF_FittedVtx_m);

					Real_dimuon2_Reco_Eta_vs_Phi->Fill(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_phi);
					Real_dimuon2_Reco_Eta_vs_Lxy->Fill(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_Lxy);
					Real_dimuon2_Reco_Lxy->Fill(diMuonC_FittedVtx_Lxy);
					Real_dimuon2_Reco_Eta->Fill(diMuonC_FittedVtx_eta);
					Real_dimuon2_Reco_Phi->Fill(diMuonC_FittedVtx_phi);
					Real_dimuon2_Reco_pT->Fill(sqrt(diMuonC_FittedVtx_px*diMuonC_FittedVtx_px+diMuonC_FittedVtx_py*diMuonC_FittedVtx_py));

				}

				//WANT GEN MU -> RECO MU Residuals 

				//GEN MU -> RECO MU:
				//GEN 00 is reco_real_muons_phi[bestreal_match_no_duplicates_0];
				//GEN 01 is reco_real_muons_phi[bestreal_match_no_duplicates_1];
				//GEN 10 is reco_real_muons_phi[bestreal_match_no_duplicates_2];
				//GEN 11 is reco_real_muons_phi[bestreal_match_no_duplicates_3];

				Real_Muon_00_Eta_Residual->Fill(genA0Mu0_eta - reco_real_muons_eta[bestreal_match_no_duplicates_0]);
				Real_Muon_01_Eta_Residual->Fill(genA0Mu1_eta - reco_real_muons_eta[bestreal_match_no_duplicates_1]);
				Real_Muon_10_Eta_Residual->Fill(genA1Mu0_eta - reco_real_muons_eta[bestreal_match_no_duplicates_2]);
				Real_Muon_11_Eta_Residual->Fill(genA1Mu1_eta - reco_real_muons_eta[bestreal_match_no_duplicates_3]);

				Real_Muon_00_Eta_Residual_vs_Eta->Fill(genA0Mu0_eta, genA0Mu0_eta - reco_real_muons_eta[bestreal_match_no_duplicates_0]);
				Real_Muon_01_Eta_Residual_vs_Eta->Fill(genA0Mu1_eta, genA0Mu1_eta - reco_real_muons_eta[bestreal_match_no_duplicates_1]);
				Real_Muon_10_Eta_Residual_vs_Eta->Fill(genA1Mu0_eta, genA1Mu0_eta - reco_real_muons_eta[bestreal_match_no_duplicates_2]);
				Real_Muon_11_Eta_Residual_vs_Eta->Fill(genA1Mu1_eta, genA1Mu1_eta - reco_real_muons_eta[bestreal_match_no_duplicates_3]);

				Real_Muon_00_Phi_Residual->Fill(genA0Mu0_phi - reco_real_muons_phi[bestreal_match_no_duplicates_0]);
				Real_Muon_01_Phi_Residual->Fill(genA0Mu1_phi - reco_real_muons_phi[bestreal_match_no_duplicates_1]);
				Real_Muon_10_Phi_Residual->Fill(genA1Mu0_phi - reco_real_muons_phi[bestreal_match_no_duplicates_2]);
				Real_Muon_11_Phi_Residual->Fill(genA1Mu1_phi - reco_real_muons_phi[bestreal_match_no_duplicates_3]);

				Real_Muon_00_Phi_Residual_vs_Phi->Fill(genA0Mu0_phi, genA0Mu0_phi - reco_real_muons_phi[bestreal_match_no_duplicates_0]);
				Real_Muon_01_Phi_Residual_vs_Phi->Fill(genA0Mu1_phi, genA0Mu1_phi - reco_real_muons_phi[bestreal_match_no_duplicates_1]);
				Real_Muon_10_Phi_Residual_vs_Phi->Fill(genA1Mu0_phi, genA1Mu0_phi - reco_real_muons_phi[bestreal_match_no_duplicates_2]);
				Real_Muon_11_Phi_Residual_vs_Phi->Fill(genA1Mu1_phi, genA1Mu1_phi - reco_real_muons_phi[bestreal_match_no_duplicates_3]);

				//}}}
				//Real Geometry values
				//{{{
				Real_GEN_Dimuon_Opening_Angle->Fill(My_dPhi(genA0_phi,genA1_phi));

				if(diMuonF_FittedVtx_phi > -800 && diMuonC_FittedVtx_phi > -800 && diMuonF_FittedVtx_eta > -800 && diMuonC_FittedVtx_eta > -800){
					Real_RECO_Dimuon_Opening_Angle->Fill(My_dPhi(diMuonC_FittedVtx_phi,diMuonF_FittedVtx_phi));
					Real_Dimuon_Opening_Angle_Residual->Fill(My_dPhi(genA0_phi,genA1_phi)-My_dPhi(diMuonC_FittedVtx_phi,diMuonF_FittedVtx_phi));
					Real_Dimuon_opening_Angle_Residual_vs_GENangle->Fill(My_dPhi(genA0_phi,genA1_phi), My_dPhi(genA0_phi,genA1_phi)-My_dPhi(diMuonC_FittedVtx_phi,diMuonF_FittedVtx_phi));

					Real_dimuon1_Reco_Eta_vs_OpeningAngle->Fill(diMuonC_FittedVtx_eta, My_dPhi(diMuonC_FittedVtx_phi,diMuonF_FittedVtx_phi));
					Real_dimuon2_Reco_Eta_vs_OpeningAngle->Fill(diMuonF_FittedVtx_eta, My_dPhi(diMuonC_FittedVtx_phi,diMuonF_FittedVtx_phi));

					//Print a few values
					if(My_dPhi(genA0_phi,genA1_phi)-My_dPhi(diMuonC_FittedVtx_phi,diMuonF_FittedVtx_phi) > 0.5 || My_dPhi(genA0_phi,genA1_phi)-My_dPhi(diMuonC_FittedVtx_phi,diMuonF_FittedVtx_phi) < -0.5){
						//cout << "GenA0, GenA1       : " << genA0_phi << ", " << genA1_phi << endl;
						//cout << "RecA0, RecA1       : " << diMuonC_FittedVtx_phi << ", " << diMuonF_FittedVtx_phi << endl;
						//cout << "GEN dphi, RECO dphi: " << My_dPhi(genA0_phi,genA1_phi) << ", " << My_dPhi(diMuonC_FittedVtx_phi,diMuonF_FittedVtx_phi) << endl; 
					}
				}

				double GEN_deta = genA0_eta-genA1_eta;
				double GEN_dphi = My_dPhi(genA0_phi,genA1_phi);
				double GEN_dr = sqrt(GEN_deta*GEN_deta + GEN_dphi*GEN_dphi);

				double RECO_deta = diMuonC_FittedVtx_eta - diMuonF_FittedVtx_eta;
				double RECO_dphi = My_dPhi(diMuonC_FittedVtx_phi,diMuonF_FittedVtx_phi);
				double RECO_dr = sqrt(RECO_deta*RECO_deta + RECO_dphi*RECO_dphi);

				Real_GEN_deltaR_Between_Dimuons->Fill(GEN_dr);
				Real_RECO_deltaR_Between_Dimuons->Fill(RECO_dr);
				Real_deltaR_Between_Dimuons_Residual->Fill(GEN_dr - RECO_dr);
				Real_deltaR_Between_Dimuons_Residual_vs_GENdeltaR->Fill(GEN_dr, GEN_dr - RECO_dr);

				Real_dimuon1_Reco_Eta_vs_deltaR->Fill(diMuonC_FittedVtx_eta, RECO_dr );
				Real_dimuon2_Reco_Eta_vs_deltaR->Fill(diMuonF_FittedVtx_eta, RECO_dr );
				//}}}
			}
			//}}}

			//Fake Loop/Matching/Plots.  The GEN level fiducial cut is NOT passed for the numerator.  Either or both of the dimuons may be fake.
			if(triggerFlag_std > 0 && triggerFlag_lxy == 0){

				fakeFlag++;
				//Loop/Matching/Plots for Fake Dimuon 0
				if(fabs(genA0_Lxy)>=5.0 || fabs(genA0_Lz)>=34.5 || fabs(genA1_Lxy)>=5.0 || fabs(genA1_Lz)>=34.5 ){ //We only want to perform this loop on a very pure sample of fakes.  Set to 5.0 instead of 4.4. 
					//Now match 
					//cout << "" << endl;
					//cout << "There is a fake in this event" << endl;
					//std::cout << "Run, Event, Lumi: " << run << ", " << event << ", " << lumi << std::endl;
					//cout << "GEN Muons (00, 01, 10, 11) pT, Eta, Phi: " << endl;
					//cout << genA0Mu0_eta << ", " << genA0Mu0_phi << endl; 
					//cout << genA0Mu1_eta << ", " << genA0Mu1_phi << endl; 
					//cout << genA1Mu0_eta << ", " << genA1Mu0_phi << endl; 
					//cout << genA1Mu1_eta << ", " << genA1Mu1_phi << endl; 
					//cout << "RECO Muons (Eta,Phi):" << endl;
					//cout << selMu0_eta << ", " << selMu0_phi << endl;
					//cout << selMu1_eta << ", " << selMu1_phi << endl;
					//cout << selMu2_eta << ", " << selMu2_phi << endl;
					//cout << selMu3_eta << ", " << selMu3_phi << endl;
					//cout << "GEN dimuon C then F (eta, phi): " << endl;
					//cout << genA0_eta << ", " << genA0_phi << endl;
					//cout << genA1_eta << ", " << genA1_phi << endl;
					//cout << "RECO dimuon C then F (eta, phi): " << endl;
					//cout << diMuonC_FittedVtx_eta << ", " << diMuonC_FittedVtx_phi << endl;
					//cout << diMuonF_FittedVtx_eta << ", " << diMuonF_FittedVtx_phi << endl;

					uncuttableFakeCounter++;

					//Perform matching of GEN-RECO
					//
					//We want to know if the RECO reconstruction is bad or if the dimuon reconstruction is bad.
					//Match GEN to RECO level particles
					//To do this, match RECO muons to RECO dimuons.  Then RECO dimuons to GEN dimuons.  And then GEN muons are assigned to a dimuon.  Then do a delta R matching between muons
					//OR
					//Do a deltaR matching between GEN and RECO muons, and then the GEN muons are assigned to a dimuon and I can assume the same assignment for the RECO level dimuons.

					//I'm going to do both and then compare the answers.

					vector< float > gen_muons_phi;
					vector< float > gen_muons_eta;
					vector< float > reco_muons_phi;
					vector< float > reco_muons_eta;

					gen_muons_phi.push_back(genA0Mu0_phi);
					gen_muons_phi.push_back(genA0Mu1_phi);
					gen_muons_phi.push_back(genA1Mu0_phi);
					gen_muons_phi.push_back(genA1Mu1_phi);
					gen_muons_eta.push_back(genA0Mu0_eta);
					gen_muons_eta.push_back(genA0Mu1_eta);
					gen_muons_eta.push_back(genA1Mu0_eta);
					gen_muons_eta.push_back(genA1Mu1_eta);

					if(selMu0_eta > -20){
						reco_muons_phi.push_back(selMu0_phi); 
						reco_muons_eta.push_back(selMu0_eta); 
					}
					if(selMu1_eta > -20){ 
						reco_muons_phi.push_back(selMu1_phi);
						reco_muons_eta.push_back(selMu1_eta);
					}
					if(selMu2_eta > -20){ 
						reco_muons_phi.push_back(selMu2_phi);
						reco_muons_eta.push_back(selMu2_eta);
					}
					if(selMu3_eta > -20){ 
						reco_muons_phi.push_back(selMu3_phi);
						reco_muons_eta.push_back(selMu3_eta);
					}

					//Match GEN and RECO level muons

					int bestmatch0 = -1; //this is the RECO index of the match to GEN 00
					int bestmatch1 = -1; // 01
					int bestmatch2 = -1; // 10
					int bestmatch3 = -1; // 11

					for(int g = 0; g < 4; g++){ //There are always 4 GEN muons
						double deltaR = 9999;
						for(int r = 0; r < reco_muons_phi.size(); r++){
							double dphi = My_dPhi(reco_muons_phi[r], gen_muons_phi[g]);
							double deta = reco_muons_eta[r] - gen_muons_eta[g];
							double dR = sqrt(dphi*dphi + deta*deta);
							if(dR < deltaR && g == 0){
								deltaR = dR;
								bestmatch0 = r;
							}
							if(dR < deltaR && g == 1){ 
								deltaR = dR;
								bestmatch1 = r;
							}
							if(dR < deltaR && g == 2){ 
								deltaR = dR;
								bestmatch2 = r;
							}
							if(dR < deltaR && g == 3){ 
								deltaR = dR;
								bestmatch3 = r;
							}
						}
					}

					//Do a quick check to make sure that each GEN level muon has a unique RECO level match.
					//std::cout << "" << std::endl;
					//std::cout << "The best match to GEN 00 is " << bestmatch0 << std::endl;
					//std::cout << "The best match to GEN 01 is " << bestmatch1 << std::endl;
					//std::cout << "The best match to GEN 10 is " << bestmatch2 << std::endl;
					//std::cout << "The best match to GEN 11 is " << bestmatch3 << std::endl;
					//std::cout << "" << std::endl;

					//Now match GEN and RECO level muons, but only allow one RECO match to each GEN muon.
					int bestmatch_no_duplicates_0 = -1; //this is the RECO index of the match to GEN 00
					int bestmatch_no_duplicates_1 = -1; // 01
					int bestmatch_no_duplicates_2 = -1; // 10
					int bestmatch_no_duplicates_3 = -1; // 11
					vector< vector<double> >  dR_g_r;
					for(int g = 0; g < 4; g++){ //There are always 4 GEN muons
						for(int r = 0; r < reco_muons_phi.size(); r++){
							vector<double> drgr;
							double dphi = My_dPhi(reco_muons_phi[r], gen_muons_phi[g]);
							double deta = reco_muons_eta[r] - gen_muons_eta[g];
							double dR = sqrt(dphi*dphi + deta*deta);

							drgr.push_back(dR);
							drgr.push_back(g);
							drgr.push_back(r);
							//cout << "pushing back dR, g, r: " << dR << ", " << g << ", " << r << endl;
							dR_g_r.push_back(drgr);
						}
					}
					//quick loop to print dR_g_r
					/*
					   for(int i = 0; i < dR_g_r.size(); i++){
					   cout << "dR_g_r[" << i << "][0]: " << dR_g_r[i][0] << endl;
					   cout << "dR_g_r[" << i << "][1]: " << dR_g_r[i][1] << endl;
					   cout << "dR_g_r[" << i << "][2]: " << dR_g_r[i][2] << endl;
					   }
					   */
					double matcherFirst = 9999;
					int First;
					for(int i = 0; i< dR_g_r.size(); i++){
						double running_matchFirst = dR_g_r[i][0]; //This is the dR of entry i
						if(running_matchFirst < matcherFirst){
							matcherFirst = running_matchFirst;
							First = i;
							if(dR_g_r[i][1] == 0){
								bestmatch_no_duplicates_0 = dR_g_r[i][2];
							}
							if(dR_g_r[i][1] == 1){
								bestmatch_no_duplicates_1 = dR_g_r[i][2];
							}
							if(dR_g_r[i][1] == 2){
								bestmatch_no_duplicates_2 = dR_g_r[i][2];
							}
							if(dR_g_r[i][1] == 3){
								bestmatch_no_duplicates_3 = dR_g_r[i][2];
							}
						}
					}
					double matcherSecond = 9999;
					int Second;
					for(int i = 0; i< dR_g_r.size(); i++){
						double running_matchSecond = dR_g_r[i][0]; //This is the dR of entry i
						if(running_matchSecond < matcherSecond){
							if(dR_g_r[First][1] != dR_g_r[i][1] && dR_g_r[First][2] != dR_g_r[i][2]){ //make sure that the second best match isn't the same RECO or GEN particles
								matcherSecond = running_matchSecond;
								Second = i;
								if(dR_g_r[i][1] == 0){
									bestmatch_no_duplicates_0 = dR_g_r[i][2];
								}
								if(dR_g_r[i][1] == 1){
									bestmatch_no_duplicates_1 = dR_g_r[i][2];
								}
								if(dR_g_r[i][1] == 2){
									bestmatch_no_duplicates_2 = dR_g_r[i][2];
								}
								if(dR_g_r[i][1] == 3){
									bestmatch_no_duplicates_3 = dR_g_r[i][2];
								}
							}
						}
					}
					double matcherThird = 9999;
					int Third;
					for(int i = 0; i< dR_g_r.size(); i++){
						double running_matchThird = dR_g_r[i][0]; //This is the dR of entry i
						if(running_matchThird < matcherThird){
							if(dR_g_r[First][1] != dR_g_r[i][1] && dR_g_r[First][2] != dR_g_r[i][2] && dR_g_r[Second][1] != dR_g_r[i][1] && dR_g_r[Second][2] != dR_g_r[i][2]){
								matcherThird = running_matchThird;
								Third = i;
								if(dR_g_r[i][1] == 0){
									bestmatch_no_duplicates_0 = dR_g_r[i][2];
								}                                                                
								if(dR_g_r[i][1] == 1){
									bestmatch_no_duplicates_1 = dR_g_r[i][2];
								}
								if(dR_g_r[i][1] == 2){
									bestmatch_no_duplicates_2 = dR_g_r[i][2];
								}
								if(dR_g_r[i][1] == 3){
									bestmatch_no_duplicates_3 = dR_g_r[i][2];
								}
							}
						}
					}
					double matcherFourth = 9999;
					int Fourth;
					for(int i = 0; i< dR_g_r.size(); i++){
						double running_matchFourth = dR_g_r[i][0]; //This is the dR of entry i
						if(running_matchFourth < matcherFourth){
							if(dR_g_r[First][1] != dR_g_r[i][1] && dR_g_r[First][2] != dR_g_r[i][2] && dR_g_r[Second][1] != dR_g_r[i][1] && dR_g_r[Second][2] != dR_g_r[i][2] && dR_g_r[Third][1] != dR_g_r[i][1] && dR_g_r[Third][2] != dR_g_r[i][2]){
								matcherFourth = running_matchFourth;
								Fourth = i;
								if(dR_g_r[i][1] == 0){
									bestmatch_no_duplicates_0 = dR_g_r[i][2];
								}
								if(dR_g_r[i][1] == 1){
									bestmatch_no_duplicates_1 = dR_g_r[i][2];
								}
								if(dR_g_r[i][1] == 2){
									bestmatch_no_duplicates_2 = dR_g_r[i][2];
								}
								if(dR_g_r[i][1] == 3){
									bestmatch_no_duplicates_3 = dR_g_r[i][2];
								}
							}
						}
					}
					//std::cout << "" << std::endl;
					//std::cout << "First, Second, Third, Fourth best matches: " << First << ", " << Second << ", " << Third << ", " << Fourth << endl;
					//std::cout << "" << std::endl;
					//std::cout << "The best match not allowing duplicates to GEN 00 is " << bestmatch_no_duplicates_0 << std::endl;
					//std::cout << "The best match not allowing duplicates to GEN 01 is " << bestmatch_no_duplicates_1 << std::endl;
					//std::cout << "The best match not allowing duplicates to GEN 10 is " << bestmatch_no_duplicates_2 << std::endl;
					//std::cout << "The best match not allowing duplicates to GEN 11 is " << bestmatch_no_duplicates_3 << std::endl;
					//std::cout << "" << std::endl;


					//Match RECO level muons to RECO level dimuons

					int diMuonFmatch0 = -1;
					int diMuonFmatch1 = -1;
					int diMuonCmatch0 = -1;
					int diMuonCmatch1 = -1;

					vector< float > dimuonC_matches;
					vector< float > dimuonF_matches;
					int diMuonC_match0 = -1;
					int diMuonC_match1 = -1;
					int diMuonF_match0 = -1;
					int diMuonF_match1 = -1;

					if(diMuonC_FittedVtx_eta > -800 && diMuonF_FittedVtx_eta > -800){
						double diMuonC_deltaR = 9999;
						//cout << "Finding best match to diMuonC" << endl;
						for(int r = 0; r < reco_muons_phi.size(); r++){ //Find best match to diMuonC
							double dphi = My_dPhi(reco_muons_phi[r], diMuonC_FittedVtx_phi);
							double deta = reco_muons_eta[r] - diMuonC_FittedVtx_eta;
							double dR = sqrt(dphi*dphi + deta*deta);
							//cout << "dR for reco muon " << r << " is " << dR << " and the current best deltaR is " << diMuonC_deltaR << endl;
							if(dR < diMuonC_deltaR){
								diMuonC_deltaR = dR;
								diMuonC_match0 = r;
							}
						}
						diMuonC_deltaR = 9999;
						//cout << "Finding the second best match to diMuonC" << endl;
						for(int r = 0; r < reco_muons_phi.size(); r++){ //Find second best match to diMuonC
							if(r != diMuonC_match0){
								double dphi = My_dPhi(reco_muons_phi[r], diMuonC_FittedVtx_phi);
								double deta = reco_muons_eta[r] - diMuonC_FittedVtx_eta;
								double dR = sqrt(dphi*dphi + deta*deta);
								//cout << "dR for reco muon " << r << " is " << dR << " and the current best deltaR is " << diMuonC_deltaR << endl;
								if(dR < diMuonC_deltaR){
									diMuonC_deltaR = dR;
									diMuonC_match1 = r;
								}
							}
						}

						//Now find diMuonF
						double diMuonF_deltaR = 9999;
						//cout << "Finding the best match to diMuonF" << endl;
						for(int r = 0; r < reco_muons_phi.size(); r++){ //Find best match to diMuonF
							double dphi = My_dPhi(reco_muons_phi[r], diMuonF_FittedVtx_phi);
							double deta = reco_muons_eta[r] - diMuonF_FittedVtx_eta;
							double dR = sqrt(dphi*dphi + deta*deta);
							//cout << "dR for reco muon " << r << " is " << dR << " and the current best deltaR is " << diMuonF_deltaR << endl;
							if(dR < diMuonF_deltaR){
								diMuonF_deltaR = dR;
								diMuonF_match0 = r;
							}
						}
						diMuonF_deltaR = 9999;
						//cout << "Finding the second best match to diMuonF" << endl;
						for(int r = 0; r < reco_muons_phi.size(); r++){ //Find second best match to diMuonF
							if(r != diMuonF_match0){
								double dphi = My_dPhi(reco_muons_phi[r], diMuonF_FittedVtx_phi);
								double deta = reco_muons_eta[r] - diMuonF_FittedVtx_eta;
								double dR = sqrt(dphi*dphi + deta*deta);
								//cout << "dR for reco muon " << r << " is " << dR << " and the current best deltaR is " << diMuonF_deltaR << endl;
								if(dR < diMuonF_deltaR){
									diMuonF_deltaR = dR;
									diMuonF_match1 = r;
								}
							}
						}
						//cout << "The best matches to diMuonC are " << diMuonC_match0 << " and " << diMuonC_match1 << endl;
						//cout << "The best matches to diMuonF are " << diMuonF_match0 << " and " << diMuonF_match1 << endl;
					}
					int problemCounter = 0;
					if(bestmatch0 == diMuonC_match0){
						if(bestmatch1 != diMuonC_match1) problemCounter++;
					}
					if(bestmatch0 == diMuonC_match1){               
						if(bestmatch1 != diMuonC_match0) problemCounter++;
					}
					if(bestmatch0 == diMuonF_match0){               
						if(bestmatch1 != diMuonF_match1) problemCounter++;
					}
					if(bestmatch0 == diMuonF_match1){
						if(bestmatch1 != diMuonF_match0) problemCounter++;
					}
					if(bestmatch2 == diMuonC_match0){               
						if(bestmatch3 != diMuonC_match1) problemCounter++;
					}
					if(bestmatch2 == diMuonC_match1){
						if(bestmatch3 != diMuonC_match0) problemCounter++;
					}
					if(bestmatch2 == diMuonF_match0){
						if(bestmatch3 != diMuonF_match1) problemCounter++;
					}
					if(bestmatch2 == diMuonF_match1){
						if(bestmatch3 != diMuonF_match0) problemCounter++;
					}
					if(problemCounter > 0) cout << "There is a problem matching (dimuon 0)" << endl;
					int problem_nodupCounter = 0;
					if(bestmatch_no_duplicates_0 == diMuonC_match0){
						if(bestmatch_no_duplicates_1 != diMuonC_match1) problem_nodupCounter++;
					}
					if(bestmatch_no_duplicates_0 == diMuonC_match1){
						if(bestmatch_no_duplicates_1 != diMuonC_match0) problem_nodupCounter++;
					}
					if(bestmatch_no_duplicates_0 == diMuonF_match0){
						if(bestmatch_no_duplicates_1 != diMuonF_match1) problem_nodupCounter++;
					}
					if(bestmatch_no_duplicates_0 == diMuonF_match1){
						if(bestmatch_no_duplicates_1 != diMuonF_match0) problem_nodupCounter++;
					}
					if(bestmatch_no_duplicates_2 == diMuonC_match0){
						if(bestmatch_no_duplicates_3 != diMuonC_match1) problem_nodupCounter++;
					}
					if(bestmatch_no_duplicates_2 == diMuonC_match1){
						if(bestmatch_no_duplicates_3 != diMuonC_match0) problem_nodupCounter++;
					}
					if(bestmatch_no_duplicates_2 == diMuonF_match0){
						if(bestmatch_no_duplicates_3 != diMuonF_match1) problem_nodupCounter++;
					}
					if(bestmatch_no_duplicates_2 == diMuonF_match1){
						if(bestmatch_no_duplicates_3 != diMuonF_match0) problem_nodupCounter++;
					}
					if(problem_nodupCounter > 0) cout << "There is a problem with no duplicate matching (dimuon 0)" << endl;
					//Only twice does bestmatch_no_duplicates and the diMuon matching fail.
					//Should be able to find residuals between GEN-RECO muons and GEN-RECO diMuons
					//Match GEN dimuons to RECO dimuons
					//  GEN dimuon 	                                = genA0
					//  GEN muons to genA0                          = genA0Mu0 and genA0Mu1 
					//  These GEN muons have RECO matches           = reco_real_muons_phi[bestreal_match_no_duplicates_0] and reco_real_muons_phi[bestreal_match_no_duplicates_1]
					//  These RECO muons are either dimuon C or F   = reco_real_muons_eta[diMuonC_real_match0] and reco_real_muons_eta[diMuonC_real_match1] OR reco_real_muons_eta[diMuonF_real_match0] and reco_real_muons_eta[diMuonF_real_match1] 
					//  Check if reco C and F correspond to A0 or A1: (MatchRECOtoGENdimuons)
					//  NOW, I can finally check the residuals between GEN mu -> RECO mu and GEN dimu -> RECO dimu

					//MATCHING IS COMPLETE:

					//Now see which RECO dimuon is causing the fakes

					if(MatchRECOtoGENdimuons(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_phi, diMuonF_FittedVtx_eta, diMuonF_FittedVtx_phi, genA0_eta, genA0_phi, genA1_eta, genA0_phi) == 0){ //diMuonC -> A0, diMuonF -> A1
						if(fabs(genA0_Lxy)>=5.0 || fabs(genA0_Lz)>=34.5){ //A0 is the fake and has match diMuonC
							//NOW LOOK AT INDIVIDUAL MUONS
							//{{{
							//HERE, we know that DIMUONC is bad
							//DIMUONC contains RECO muons reco_real_muons_phi[diMuonC_match0] and reco_real_muons_phi[diMuonC_match1]
							//Now, I can pair these reco muons to GEN muons and create those plots

							if(diMuonC_match0 == bestmatch_no_duplicates_0){
								Fake_Muon_00_Eta_Residual->Fill(genA0Mu0_eta - reco_muons_eta[bestmatch_no_duplicates_0]);
								Fake_Muon_00_Eta_Residual_vs_Eta->Fill(genA0Mu0_eta, genA0Mu0_eta - reco_muons_eta[bestmatch_no_duplicates_0]);
								Fake_Muon_00_Phi_Residual->Fill(genA0Mu0_phi - reco_muons_phi[bestmatch_no_duplicates_0]);
								Fake_Muon_00_Phi_Residual_vs_Phi->Fill(genA0Mu0_phi, genA0Mu0_phi - reco_muons_phi[bestmatch_no_duplicates_0]);
							}       
							if(diMuonC_match0 == bestmatch_no_duplicates_1){
								Fake_Muon_01_Eta_Residual->Fill(genA0Mu1_eta - reco_muons_eta[bestmatch_no_duplicates_1]);
								Fake_Muon_01_Eta_Residual_vs_Eta->Fill(genA0Mu1_eta, genA0Mu1_eta - reco_muons_eta[bestmatch_no_duplicates_1]);
								Fake_Muon_01_Phi_Residual->Fill(genA0Mu1_phi - reco_muons_phi[bestmatch_no_duplicates_1]);
								Fake_Muon_01_Phi_Residual_vs_Phi->Fill(genA0Mu1_phi, genA0Mu1_phi - reco_muons_phi[bestmatch_no_duplicates_1]);
							}       
							if(diMuonC_match0 == bestmatch_no_duplicates_2){
								Fake_Muon_10_Eta_Residual->Fill(genA1Mu0_eta - reco_muons_eta[bestmatch_no_duplicates_2]);
								Fake_Muon_10_Eta_Residual_vs_Eta->Fill(genA1Mu0_eta, genA1Mu0_eta - reco_muons_eta[bestmatch_no_duplicates_2]);
								Fake_Muon_10_Phi_Residual->Fill(genA1Mu0_phi - reco_muons_phi[bestmatch_no_duplicates_2]);
								Fake_Muon_10_Phi_Residual_vs_Phi->Fill(genA1Mu0_phi, genA1Mu0_phi - reco_muons_phi[bestmatch_no_duplicates_2]);
							}       
							if(diMuonC_match0 == bestmatch_no_duplicates_3){
								Fake_Muon_11_Eta_Residual->Fill(genA1Mu1_eta - reco_muons_eta[bestmatch_no_duplicates_3]);
								Fake_Muon_11_Eta_Residual_vs_Eta->Fill(genA1Mu1_eta, genA1Mu1_eta - reco_muons_eta[bestmatch_no_duplicates_3]);
								Fake_Muon_11_Phi_Residual->Fill(genA1Mu1_phi - reco_muons_phi[bestmatch_no_duplicates_3]);
								Fake_Muon_11_Phi_Residual_vs_Phi->Fill(genA1Mu1_phi, genA1Mu1_phi - reco_muons_phi[bestmatch_no_duplicates_3]);
							}       
							if(diMuonC_match1 == bestmatch_no_duplicates_0){
								Fake_Muon_00_Eta_Residual->Fill(genA0Mu0_eta - reco_muons_eta[bestmatch_no_duplicates_0]);
								Fake_Muon_00_Eta_Residual_vs_Eta->Fill(genA0Mu0_eta, genA0Mu0_eta - reco_muons_eta[bestmatch_no_duplicates_0]);
								Fake_Muon_00_Phi_Residual->Fill(genA0Mu0_phi - reco_muons_phi[bestmatch_no_duplicates_0]);
								Fake_Muon_00_Phi_Residual_vs_Phi->Fill(genA0Mu0_phi, genA0Mu0_phi - reco_muons_phi[bestmatch_no_duplicates_0]);
							}                                                if(diMuonC_match1 == bestmatch_no_duplicates_1){
								Fake_Muon_01_Eta_Residual->Fill(genA0Mu1_eta - reco_muons_eta[bestmatch_no_duplicates_1]);
								Fake_Muon_01_Eta_Residual_vs_Eta->Fill(genA0Mu1_eta, genA0Mu1_eta - reco_muons_eta[bestmatch_no_duplicates_1]);
								Fake_Muon_01_Phi_Residual->Fill(genA0Mu1_phi - reco_muons_phi[bestmatch_no_duplicates_1]);
								Fake_Muon_01_Phi_Residual_vs_Phi->Fill(genA0Mu1_phi, genA0Mu1_phi - reco_muons_phi[bestmatch_no_duplicates_1]);
							}       
							if(diMuonC_match1 == bestmatch_no_duplicates_2){
								Fake_Muon_10_Eta_Residual->Fill(genA1Mu0_eta - reco_muons_eta[bestmatch_no_duplicates_2]);
								Fake_Muon_10_Eta_Residual_vs_Eta->Fill(genA1Mu0_eta, genA1Mu0_eta - reco_muons_eta[bestmatch_no_duplicates_2]);
								Fake_Muon_10_Phi_Residual->Fill(genA1Mu0_phi - reco_muons_phi[bestmatch_no_duplicates_2]);
								Fake_Muon_10_Phi_Residual_vs_Phi->Fill(genA1Mu0_phi, genA1Mu0_phi - reco_muons_phi[bestmatch_no_duplicates_2]);
							}       
							if(diMuonC_match1 == bestmatch_no_duplicates_3){
								Fake_Muon_11_Eta_Residual->Fill(genA1Mu1_eta - reco_muons_eta[bestmatch_no_duplicates_3]);
								Fake_Muon_11_Eta_Residual_vs_Eta->Fill(genA1Mu1_eta, genA1Mu1_eta - reco_muons_eta[bestmatch_no_duplicates_3]);
								Fake_Muon_11_Phi_Residual->Fill(genA1Mu1_phi - reco_muons_phi[bestmatch_no_duplicates_3]);
								Fake_Muon_11_Phi_Residual_vs_Phi->Fill(genA1Mu1_phi, genA1Mu1_phi - reco_muons_phi[bestmatch_no_duplicates_3]);
							}  
							//}}}	

							//Plots
							//{{{
							//General Distributions
							Fake_Gen_Lxy->Fill(genA0_Lxy);
							Fake_Gen_Lz->Fill(genA0_Lz);
							Fake_Gen_Eta->Fill(genA0_eta);
							Fake_Gen_Phi->Fill(genA0_phi);
							Fake_Gen_pT->Fill(sqrt(genA0_px*genA0_px+genA0_py*genA0_py));
							Fake_Gen_pT_vs_Lxy->Fill(genA0_Lxy,sqrt(genA0_px*genA0_px+genA0_py*genA0_py));

							//GEN Distributions for fake dimuon 1 (A0)
							Fake_dimuon1_Gen_Lxy->Fill(genA0_Lxy);
							Fake_dimuon1_Gen_Lz->Fill(genA0_Lz);
							Fake_dimuon1_Gen_Eta->Fill(genA0_eta);
							Fake_dimuon1_Gen_Phi->Fill(genA0_phi);
							Fake_dimuon1_Gen_pT->Fill(sqrt(genA0_px*genA0_px+genA0_py*genA0_py));
							Fake_dimuon1_Gen_pT_vs_Lxy->Fill(genA0_Lxy,sqrt(genA0_px*genA0_px+genA0_py*genA0_py));

							//General RECO distributions for (diMuonC)
							if(diMuonC_FittedVtx_Lxy > -800) Fake_Reco_Lxy->Fill(diMuonC_FittedVtx_Lxy);
							if(diMuonC_FittedVtx_eta > -800) Fake_Reco_Eta->Fill(diMuonC_FittedVtx_eta);
							if(diMuonC_FittedVtx_phi > -800) Fake_Reco_Phi->Fill(diMuonC_FittedVtx_phi);
							if(diMuonC_FittedVtx_px > -800 && diMuonC_FittedVtx_py > -800) Fake_Reco_pT->Fill(sqrt(diMuonC_FittedVtx_px*diMuonC_FittedVtx_px+diMuonC_FittedVtx_py*diMuonC_FittedVtx_py));
							if(diMuonC_FittedVtx_px > -800 && diMuonC_FittedVtx_py > -800 && diMuonC_FittedVtx_Lxy > -800) Fake_Reco_pT_vs_Lxy->Fill(diMuonC_FittedVtx_Lxy, sqrt(diMuonC_FittedVtx_px*diMuonC_FittedVtx_px+diMuonC_FittedVtx_py*diMuonC_FittedVtx_py));
							if(diMuonC_FittedVtx_eta > -800 && diMuonC_FittedVtx_Lxy > -800) Fake_Reco_Eta_vs_Lxy->Fill(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_Lxy);
							if(diMuonC_FittedVtx_eta > -800 && diMuonC_FittedVtx_phi > -800) Fake_Reco_Eta_vs_Phi->Fill(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_phi);

							if(diMuonC_FittedVtx_eta > -800 && diMuonC_FittedVtx_vx > -800) Fake_Reco_Eta_vs_VertexR->Fill(diMuonC_FittedVtx_eta, sqrt((diMuonC_FittedVtx_vx*diMuonC_FittedVtx_vx)+(diMuonC_FittedVtx_vy*diMuonC_FittedVtx_vy)));
							if(diMuonC_FittedVtx_eta > -800 && diMuonC_FittedVtx_vz > -800) Fake_Reco_Eta_vs_VertexZ->Fill(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_vz);

							//RECO Distributions for fake dimuon 1 (diMuonC)
							if(diMuonC_FittedVtx_Lxy > -800) Fake_dimuon1_Reco_Lxy->Fill(diMuonC_FittedVtx_Lxy);
							if(diMuonC_FittedVtx_eta > -800) Fake_dimuon1_Reco_Eta->Fill(diMuonC_FittedVtx_eta);
							if(diMuonC_FittedVtx_phi > -800) Fake_dimuon1_Reco_Phi->Fill(diMuonC_FittedVtx_phi);
							if(diMuonC_FittedVtx_px > -800 && diMuonC_FittedVtx_py > -800) Fake_dimuon1_Reco_pT->Fill(sqrt(diMuonC_FittedVtx_px*diMuonC_FittedVtx_px+diMuonC_FittedVtx_py*diMuonC_FittedVtx_py));
							if(diMuonC_FittedVtx_px > -800 && diMuonC_FittedVtx_py > -800 && diMuonC_FittedVtx_Lxy > -800) Fake_dimuon1_Reco_pT_vs_Lxy->Fill(diMuonC_FittedVtx_Lxy, sqrt(diMuonC_FittedVtx_px*diMuonC_FittedVtx_px+diMuonC_FittedVtx_py*diMuonC_FittedVtx_py));
							if(diMuonC_FittedVtx_eta > -800 && diMuonC_FittedVtx_phi > -800) Fake_dimuon1_Reco_Eta_vs_Phi->Fill(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_phi);

							if(diMuonC_FittedVtx_eta > -800 && diMuonC_FittedVtx_Lxy > -800) Fake_dimuon1_Reco_Eta_vs_Lxy->Fill(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_Lxy);

							//eta
							Fake_dimuon1_EtaResidual->Fill(genA0_eta - diMuonC_FittedVtx_eta);
							Fake_dimuon1_EtaResidual_vs_Eta->Fill(genA0_eta, genA0_eta - diMuonC_FittedVtx_eta);
							Fake_dimuon1_EtaResidual_vs_Lxy->Fill(genA0_Lxy, genA0_eta - diMuonC_FittedVtx_eta);

							//phi
							Fake_dimuon1_PhiResidual->Fill(genA0_phi - diMuonC_FittedVtx_phi);
							Fake_dimuon1_PhiResidual_vs_Phi->Fill(genA0_phi, genA0_phi - diMuonC_FittedVtx_phi);
							Fake_dimuon1_PhiResidual_vs_Lxy->Fill(genA0_Lxy, genA0_phi - diMuonC_FittedVtx_phi);

							//Lxy
							Fake_dimuon1_LxyResidual->Fill(genA0_Lxy - diMuonC_FittedVtx_Lxy);
							Fake_dimuon1_LxyResidual_vs_Lxy->Fill(genA0_Lxy, genA0_Lxy - diMuonC_FittedVtx_Lxy);

							//Vertex
							Fake1_GEN_Dimuon_vertex_r->Fill(sqrt(genA0Mu0_vx*genA0Mu0_vx + genA0Mu0_vy*genA0Mu0_vy));
							Fake1_RECO_Dimuon_vertex_r->Fill(sqrt(diMuonC_FittedVtx_vx*diMuonC_FittedVtx_vx + diMuonC_FittedVtx_vy*diMuonC_FittedVtx_vy));
							Fake1_Dimuon_vertex_r_Residual->Fill( sqrt(genA0Mu0_vx*genA0Mu0_vx + genA0Mu0_vy*genA0Mu0_vy) - sqrt(diMuonC_FittedVtx_vx*diMuonC_FittedVtx_vx + diMuonC_FittedVtx_vy*diMuonC_FittedVtx_vy));                       
							Fake1_Dimuon_vertex_r_Residual_vs_GEN->Fill(sqrt(genA0Mu0_vx*genA0Mu0_vx + genA0Mu0_vy*genA0Mu0_vy), sqrt(genA0Mu0_vx*genA0Mu0_vx + genA0Mu0_vy*genA0Mu0_vy) - sqrt(diMuonC_FittedVtx_vx*diMuonC_FittedVtx_vx + diMuonC_FittedVtx_vy*diMuonC_FittedVtx_vy));
							Fake1_Dimuon_Lxy_Residual_vs_GEN_vertex_r->Fill(sqrt(genA0Mu0_vx*genA0Mu0_vx + genA0Mu0_vy*genA0Mu0_vy), genA0_Lxy - diMuonC_FittedVtx_Lxy);
							Fake1_Dimuon_Lxy_Residual_vs_RECO_vertex_r->Fill(sqrt(diMuonC_FittedVtx_vx*diMuonC_FittedVtx_vx + diMuonC_FittedVtx_vy*diMuonC_FittedVtx_vy), genA0_Lxy - diMuonC_FittedVtx_Lxy);                               

							Fake1_GEN_Dimuon_vertex_z->Fill(genA0Mu0_vz);
							Fake1_RECO_Dimuon_vertex_z->Fill(diMuonC_FittedVtx_vz);
							Fake1_Dimuon_vertex_z_Residual->Fill(genA0Mu0_vz - diMuonC_FittedVtx_vz);
							Fake1_Dimuon_vertex_z_Residual_vs_GEN->Fill(genA0Mu0_vz, genA0Mu0_vz - diMuonC_FittedVtx_vz);
							Fake1_Dimuon_Lxy_Residual_vs_GEN_vertex_z->Fill(genA0Mu0_vz, genA0_Lxy - diMuonC_FittedVtx_Lxy);
							Fake1_Dimuon_Lxy_Residual_vs_RECO_vertex_z->Fill(diMuonC_FittedVtx_vz, genA0_Lxy - diMuonC_FittedVtx_Lxy);

							//}}}
						}
						if(fabs(genA1_Lxy)>=5.0 || fabs(genA1_Lz)>=34.5){ //A1 is the fake and has match diMuonF
							//NOW LOOK AT INDIVIDUAL MUONS
							//{{{                                        
							//HERE, we know that DIMUONF is bad
							//DIMUONF contains RECO muons reco_real_muons_phi[diMuonF_match0] and reco_real_muons_phi[diMuonF_match1]
							//Now, I can pair these reco muons to GEN muons and create those plots   


							if(diMuonF_match0 == bestmatch_no_duplicates_0){
								Fake_Muon_00_Eta_Residual->Fill(genA0Mu0_eta - reco_muons_eta[bestmatch_no_duplicates_0]);
								Fake_Muon_00_Eta_Residual_vs_Eta->Fill(genA0Mu0_eta, genA0Mu0_eta - reco_muons_eta[bestmatch_no_duplicates_0]);
								Fake_Muon_00_Phi_Residual->Fill(genA0Mu0_phi - reco_muons_phi[bestmatch_no_duplicates_0]);
								Fake_Muon_00_Phi_Residual_vs_Phi->Fill(genA0Mu0_phi, genA0Mu0_phi - reco_muons_phi[bestmatch_no_duplicates_0]);
							}
							if(diMuonF_match0 == bestmatch_no_duplicates_1){
								Fake_Muon_01_Eta_Residual->Fill(genA0Mu1_eta - reco_muons_eta[bestmatch_no_duplicates_1]);
								Fake_Muon_01_Eta_Residual_vs_Eta->Fill(genA0Mu1_eta, genA0Mu1_eta - reco_muons_eta[bestmatch_no_duplicates_1]);
								Fake_Muon_01_Phi_Residual->Fill(genA0Mu1_phi - reco_muons_phi[bestmatch_no_duplicates_1]);
								Fake_Muon_01_Phi_Residual_vs_Phi->Fill(genA0Mu1_phi, genA0Mu1_phi - reco_muons_phi[bestmatch_no_duplicates_1]);
							}
							if(diMuonF_match0 == bestmatch_no_duplicates_2){
								Fake_Muon_10_Eta_Residual->Fill(genA1Mu0_eta - reco_muons_eta[bestmatch_no_duplicates_2]);
								Fake_Muon_10_Eta_Residual_vs_Eta->Fill(genA1Mu0_eta, genA1Mu0_eta - reco_muons_eta[bestmatch_no_duplicates_2]);
								Fake_Muon_10_Phi_Residual->Fill(genA1Mu0_phi - reco_muons_phi[bestmatch_no_duplicates_2]);
								Fake_Muon_10_Phi_Residual_vs_Phi->Fill(genA1Mu0_phi, genA1Mu0_phi - reco_muons_phi[bestmatch_no_duplicates_2]);
							}
							if(diMuonF_match0 == bestmatch_no_duplicates_3){
								Fake_Muon_11_Eta_Residual->Fill(genA1Mu1_eta - reco_muons_eta[bestmatch_no_duplicates_3]);
								Fake_Muon_11_Eta_Residual_vs_Eta->Fill(genA1Mu1_eta, genA1Mu1_eta - reco_muons_eta[bestmatch_no_duplicates_3]);
								Fake_Muon_11_Phi_Residual->Fill(genA1Mu1_phi - reco_muons_phi[bestmatch_no_duplicates_3]);
								Fake_Muon_11_Phi_Residual_vs_Phi->Fill(genA1Mu1_phi, genA1Mu1_phi - reco_muons_phi[bestmatch_no_duplicates_3]);
							}
							if(diMuonF_match1 == bestmatch_no_duplicates_0){
								Fake_Muon_00_Eta_Residual->Fill(genA0Mu0_eta - reco_muons_eta[bestmatch_no_duplicates_0]);
								Fake_Muon_00_Eta_Residual_vs_Eta->Fill(genA0Mu0_eta, genA0Mu0_eta - reco_muons_eta[bestmatch_no_duplicates_0]);
								Fake_Muon_00_Phi_Residual->Fill(genA0Mu0_phi - reco_muons_phi[bestmatch_no_duplicates_0]);
								Fake_Muon_00_Phi_Residual_vs_Phi->Fill(genA0Mu0_phi, genA0Mu0_phi - reco_muons_phi[bestmatch_no_duplicates_0]);
							}
							if(diMuonF_match1 == bestmatch_no_duplicates_1){
								Fake_Muon_01_Eta_Residual->Fill(genA0Mu1_eta - reco_muons_eta[bestmatch_no_duplicates_1]);
								Fake_Muon_01_Eta_Residual_vs_Eta->Fill(genA0Mu1_eta, genA0Mu1_eta - reco_muons_eta[bestmatch_no_duplicates_1]);
								Fake_Muon_01_Phi_Residual->Fill(genA0Mu1_phi - reco_muons_phi[bestmatch_no_duplicates_1]);
								Fake_Muon_01_Phi_Residual_vs_Phi->Fill(genA0Mu1_phi, genA0Mu1_phi - reco_muons_phi[bestmatch_no_duplicates_1]);
							}
							if(diMuonF_match1 == bestmatch_no_duplicates_2){
								Fake_Muon_10_Eta_Residual->Fill(genA1Mu0_eta - reco_muons_eta[bestmatch_no_duplicates_2]);
								Fake_Muon_10_Eta_Residual_vs_Eta->Fill(genA1Mu0_eta, genA1Mu0_eta - reco_muons_eta[bestmatch_no_duplicates_2]);
								Fake_Muon_10_Phi_Residual->Fill(genA1Mu0_phi - reco_muons_phi[bestmatch_no_duplicates_2]);
								Fake_Muon_10_Phi_Residual_vs_Phi->Fill(genA1Mu0_phi, genA1Mu0_phi - reco_muons_phi[bestmatch_no_duplicates_2]);
							}
							if(diMuonF_match1 == bestmatch_no_duplicates_3){
								Fake_Muon_11_Eta_Residual->Fill(genA1Mu1_eta - reco_muons_eta[bestmatch_no_duplicates_3]);
								Fake_Muon_11_Eta_Residual_vs_Eta->Fill(genA1Mu1_eta, genA1Mu1_eta - reco_muons_eta[bestmatch_no_duplicates_3]);
								Fake_Muon_11_Phi_Residual->Fill(genA1Mu1_phi - reco_muons_phi[bestmatch_no_duplicates_3]);
								Fake_Muon_11_Phi_Residual_vs_Phi->Fill(genA1Mu1_phi, genA1Mu1_phi - reco_muons_phi[bestmatch_no_duplicates_3]);
							}
							//}}}
							//Plots
							//{{{
							//General Distributions
							Fake_Gen_Lxy->Fill(genA1_Lxy);
							Fake_Gen_Lz->Fill(genA1_Lz);
							Fake_Gen_Eta->Fill(genA1_eta);
							Fake_Gen_Phi->Fill(genA1_phi);
							Fake_Gen_pT->Fill(sqrt(genA1_px*genA1_px+genA1_py*genA1_py));
							Fake_Gen_pT_vs_Lxy->Fill(genA1_Lxy,sqrt(genA1_px*genA1_px+genA1_py*genA1_py));

							//GEN Distributions for fake dimuon 1 (A1)
							Fake_dimuon2_Gen_Lxy->Fill(genA1_Lxy);
							Fake_dimuon2_Gen_Lz->Fill(genA1_Lz);
							Fake_dimuon2_Gen_Eta->Fill(genA1_eta);
							Fake_dimuon2_Gen_Phi->Fill(genA1_phi);
							Fake_dimuon2_Gen_pT->Fill(sqrt(genA1_px*genA1_px+genA1_py*genA1_py));
							Fake_dimuon2_Gen_pT_vs_Lxy->Fill(genA1_Lxy,sqrt(genA1_px*genA1_px+genA1_py*genA1_py));

							//General RECO distributions for (diMuonF)
							if(diMuonF_FittedVtx_Lxy > -800) Fake_Reco_Lxy->Fill(diMuonF_FittedVtx_Lxy);
							if(diMuonF_FittedVtx_eta > -800) Fake_Reco_Eta->Fill(diMuonF_FittedVtx_eta);
							if(diMuonF_FittedVtx_phi > -800) Fake_Reco_Phi->Fill(diMuonF_FittedVtx_phi);
							if(diMuonF_FittedVtx_px > -800 && diMuonF_FittedVtx_py > -800) Fake_Reco_pT->Fill(sqrt(diMuonF_FittedVtx_px*diMuonF_FittedVtx_px+diMuonF_FittedVtx_py*diMuonF_FittedVtx_py));
							if(diMuonF_FittedVtx_px > -800 && diMuonF_FittedVtx_py > -800 && diMuonF_FittedVtx_Lxy > -800) Fake_Reco_pT_vs_Lxy->Fill(diMuonF_FittedVtx_Lxy, sqrt(diMuonF_FittedVtx_px*diMuonF_FittedVtx_px+diMuonF_FittedVtx_py*diMuonF_FittedVtx_py));
							if(diMuonF_FittedVtx_eta > -800 && diMuonF_FittedVtx_Lxy > -800) Fake_Reco_Eta_vs_Lxy->Fill(diMuonF_FittedVtx_eta, diMuonF_FittedVtx_Lxy);
							if(diMuonF_FittedVtx_eta > -800 && diMuonF_FittedVtx_phi > -800) Fake_Reco_Eta_vs_Phi->Fill(diMuonF_FittedVtx_eta, diMuonF_FittedVtx_phi);

							if(diMuonF_FittedVtx_eta > -800 && diMuonF_FittedVtx_vx > -800) Fake_Reco_Eta_vs_VertexR->Fill(diMuonF_FittedVtx_eta, sqrt((diMuonF_FittedVtx_vx*diMuonF_FittedVtx_vx)+(diMuonF_FittedVtx_vy*diMuonF_FittedVtx_vy)));
							if(diMuonF_FittedVtx_eta > -800 && diMuonF_FittedVtx_vz > -800) Fake_Reco_Eta_vs_VertexZ->Fill(diMuonF_FittedVtx_eta, diMuonF_FittedVtx_vz);

							//RECO Distributions for fake dimuon 1 (diMuonF)
							if(diMuonF_FittedVtx_Lxy > -800) Fake_dimuon2_Reco_Lxy->Fill(diMuonF_FittedVtx_Lxy);
							if(diMuonF_FittedVtx_eta > -800) Fake_dimuon2_Reco_Eta->Fill(diMuonF_FittedVtx_eta);
							if(diMuonF_FittedVtx_phi > -800) Fake_dimuon2_Reco_Phi->Fill(diMuonF_FittedVtx_phi);
							if(diMuonF_FittedVtx_px > -800 && diMuonF_FittedVtx_py > -800) Fake_dimuon2_Reco_pT->Fill(sqrt(diMuonF_FittedVtx_px*diMuonF_FittedVtx_px+diMuonF_FittedVtx_py*diMuonF_FittedVtx_py));
							if(diMuonF_FittedVtx_px > -800 && diMuonF_FittedVtx_py > -800 && diMuonF_FittedVtx_Lxy > -800) Fake_dimuon2_Reco_pT_vs_Lxy->Fill(diMuonF_FittedVtx_Lxy, sqrt(diMuonF_FittedVtx_px*diMuonF_FittedVtx_px+diMuonF_FittedVtx_py*diMuonF_FittedVtx_py));
							if(diMuonF_FittedVtx_eta > -800 && diMuonF_FittedVtx_phi > -800) Fake_dimuon2_Reco_Eta_vs_Phi->Fill(diMuonF_FittedVtx_eta, diMuonF_FittedVtx_phi);

							if(diMuonF_FittedVtx_eta > -800 && diMuonF_FittedVtx_Lxy > -800) Fake_dimuon2_Reco_Eta_vs_Lxy->Fill(diMuonF_FittedVtx_eta, diMuonF_FittedVtx_Lxy);

							//eta
							Fake_dimuon2_EtaResidual->Fill(genA1_eta - diMuonF_FittedVtx_eta);
							Fake_dimuon2_EtaResidual_vs_Eta->Fill(genA1_eta, genA1_eta - diMuonF_FittedVtx_eta);
							Fake_dimuon2_EtaResidual_vs_Lxy->Fill(genA1_Lxy, genA1_eta - diMuonF_FittedVtx_eta);

							//phi
							Fake_dimuon2_PhiResidual->Fill(genA1_phi - diMuonF_FittedVtx_phi);
							Fake_dimuon2_PhiResidual_vs_Phi->Fill(genA1_phi, genA1_phi - diMuonF_FittedVtx_phi);
							Fake_dimuon2_PhiResidual_vs_Lxy->Fill(genA1_Lxy, genA1_phi - diMuonF_FittedVtx_phi);

							//Lxy
							Fake_dimuon2_LxyResidual->Fill(genA1_Lxy - diMuonF_FittedVtx_Lxy);
							Fake_dimuon2_LxyResidual_vs_Lxy->Fill(genA1_Lxy, genA1_Lxy - diMuonF_FittedVtx_Lxy);

							//Vertex
							Fake2_GEN_Dimuon_vertex_r->Fill(sqrt(genA1Mu0_vx*genA1Mu0_vx + genA1Mu0_vy*genA1Mu0_vy));
							Fake2_RECO_Dimuon_vertex_r->Fill(sqrt(diMuonF_FittedVtx_vx*diMuonF_FittedVtx_vx + diMuonF_FittedVtx_vy*diMuonF_FittedVtx_vy));
							Fake2_Dimuon_vertex_r_Residual->Fill( sqrt(genA1Mu0_vx*genA1Mu0_vx + genA1Mu0_vy*genA1Mu0_vy) - sqrt(diMuonF_FittedVtx_vx*diMuonF_FittedVtx_vx + diMuonF_FittedVtx_vy*diMuonF_FittedVtx_vy));
							Fake2_Dimuon_vertex_r_Residual_vs_GEN->Fill(sqrt(genA1Mu0_vx*genA1Mu0_vx + genA1Mu0_vy*genA1Mu0_vy), sqrt(genA1Mu0_vx*genA1Mu0_vx + genA1Mu0_vy*genA1Mu0_vy) - sqrt(diMuonF_FittedVtx_vx*diMuonF_FittedVtx_vx + diMuonF_FittedVtx_vy*diMuonF_FittedVtx_vy));
							Fake2_Dimuon_Lxy_Residual_vs_GEN_vertex_r->Fill(sqrt(genA1Mu0_vx*genA1Mu0_vx + genA1Mu0_vy*genA1Mu0_vy), genA1_Lxy - diMuonF_FittedVtx_Lxy);
							Fake2_Dimuon_Lxy_Residual_vs_RECO_vertex_r->Fill(sqrt(diMuonF_FittedVtx_vx*diMuonF_FittedVtx_vx + diMuonF_FittedVtx_vy*diMuonF_FittedVtx_vy), genA1_Lxy - diMuonF_FittedVtx_Lxy);

							Fake2_GEN_Dimuon_vertex_z->Fill(genA1Mu0_vz);
							Fake2_RECO_Dimuon_vertex_z->Fill(diMuonF_FittedVtx_vz);
							Fake2_Dimuon_vertex_z_Residual->Fill(genA1Mu0_vz - diMuonF_FittedVtx_vz);
							Fake2_Dimuon_vertex_z_Residual_vs_GEN->Fill(genA1Mu0_vz, genA1Mu0_vz - diMuonF_FittedVtx_vz);
							Fake2_Dimuon_Lxy_Residual_vs_GEN_vertex_z->Fill(genA1Mu0_vz, genA1_Lxy - diMuonF_FittedVtx_Lxy);
							Fake2_Dimuon_Lxy_Residual_vs_RECO_vertex_z->Fill(diMuonF_FittedVtx_vz, genA1_Lxy - diMuonF_FittedVtx_Lxy);

							//}}}

						}
					}else{ //diMuonC -> A1, diMuonF -> A0
						if(fabs(genA0_Lxy)>=5.0 || fabs(genA0_Lz)>=34.5){ //A0 is the fake and has match diMuonF
							//NOW LOOK AT INDIVIDUAL MUONS
							//{{{                                        
							//HERE, we know that DIMUONF is bad
							//DIMUONF contains RECO muons reco_real_muons_phi[diMuonF_match0] and reco_real_muons_phi[diMuonF_match1]
							//Now, I can pair these reco muons to GEN muons and create those plots   


							if(diMuonF_match0 == bestmatch_no_duplicates_0){
								Fake_Muon_00_Eta_Residual->Fill(genA0Mu0_eta - reco_muons_eta[bestmatch_no_duplicates_0]);
								Fake_Muon_00_Eta_Residual_vs_Eta->Fill(genA0Mu0_eta, genA0Mu0_eta - reco_muons_eta[bestmatch_no_duplicates_0]);
								Fake_Muon_00_Phi_Residual->Fill(genA0Mu0_phi - reco_muons_phi[bestmatch_no_duplicates_0]);
								Fake_Muon_00_Phi_Residual_vs_Phi->Fill(genA0Mu0_phi, genA0Mu0_phi - reco_muons_phi[bestmatch_no_duplicates_0]);
							}
							if(diMuonF_match0 == bestmatch_no_duplicates_1){
								Fake_Muon_01_Eta_Residual->Fill(genA0Mu1_eta - reco_muons_eta[bestmatch_no_duplicates_1]);
								Fake_Muon_01_Eta_Residual_vs_Eta->Fill(genA0Mu1_eta, genA0Mu1_eta - reco_muons_eta[bestmatch_no_duplicates_1]);
								Fake_Muon_01_Phi_Residual->Fill(genA0Mu1_phi - reco_muons_phi[bestmatch_no_duplicates_1]);
								Fake_Muon_01_Phi_Residual_vs_Phi->Fill(genA0Mu1_phi, genA0Mu1_phi - reco_muons_phi[bestmatch_no_duplicates_1]);
							}
							if(diMuonF_match0 == bestmatch_no_duplicates_2){
								Fake_Muon_10_Eta_Residual->Fill(genA1Mu0_eta - reco_muons_eta[bestmatch_no_duplicates_2]);
								Fake_Muon_10_Eta_Residual_vs_Eta->Fill(genA1Mu0_eta, genA1Mu0_eta - reco_muons_eta[bestmatch_no_duplicates_2]);
								Fake_Muon_10_Phi_Residual->Fill(genA1Mu0_phi - reco_muons_phi[bestmatch_no_duplicates_2]);
								Fake_Muon_10_Phi_Residual_vs_Phi->Fill(genA1Mu0_phi, genA1Mu0_phi - reco_muons_phi[bestmatch_no_duplicates_2]);
							}
							if(diMuonF_match0 == bestmatch_no_duplicates_3){
								Fake_Muon_11_Eta_Residual->Fill(genA1Mu1_eta - reco_muons_eta[bestmatch_no_duplicates_3]);
								Fake_Muon_11_Eta_Residual_vs_Eta->Fill(genA1Mu1_eta, genA1Mu1_eta - reco_muons_eta[bestmatch_no_duplicates_3]);
								Fake_Muon_11_Phi_Residual->Fill(genA1Mu1_phi - reco_muons_phi[bestmatch_no_duplicates_3]);
								Fake_Muon_11_Phi_Residual_vs_Phi->Fill(genA1Mu1_phi, genA1Mu1_phi - reco_muons_phi[bestmatch_no_duplicates_3]);
							}
							if(diMuonF_match1 == bestmatch_no_duplicates_0){
								Fake_Muon_00_Eta_Residual->Fill(genA0Mu0_eta - reco_muons_eta[bestmatch_no_duplicates_0]);
								Fake_Muon_00_Eta_Residual_vs_Eta->Fill(genA0Mu0_eta, genA0Mu0_eta - reco_muons_eta[bestmatch_no_duplicates_0]);
								Fake_Muon_00_Phi_Residual->Fill(genA0Mu0_phi - reco_muons_phi[bestmatch_no_duplicates_0]);
								Fake_Muon_00_Phi_Residual_vs_Phi->Fill(genA0Mu0_phi, genA0Mu0_phi - reco_muons_phi[bestmatch_no_duplicates_0]);
							}
							if(diMuonF_match1 == bestmatch_no_duplicates_1){
								Fake_Muon_01_Eta_Residual->Fill(genA0Mu1_eta - reco_muons_eta[bestmatch_no_duplicates_1]);
								Fake_Muon_01_Eta_Residual_vs_Eta->Fill(genA0Mu1_eta, genA0Mu1_eta - reco_muons_eta[bestmatch_no_duplicates_1]);
								Fake_Muon_01_Phi_Residual->Fill(genA0Mu1_phi - reco_muons_phi[bestmatch_no_duplicates_1]);
								Fake_Muon_01_Phi_Residual_vs_Phi->Fill(genA0Mu1_phi, genA0Mu1_phi - reco_muons_phi[bestmatch_no_duplicates_1]);
							}
							if(diMuonF_match1 == bestmatch_no_duplicates_2){
								Fake_Muon_10_Eta_Residual->Fill(genA1Mu0_eta - reco_muons_eta[bestmatch_no_duplicates_2]);
								Fake_Muon_10_Eta_Residual_vs_Eta->Fill(genA1Mu0_eta, genA1Mu0_eta - reco_muons_eta[bestmatch_no_duplicates_2]);
								Fake_Muon_10_Phi_Residual->Fill(genA1Mu0_phi - reco_muons_phi[bestmatch_no_duplicates_2]);
								Fake_Muon_10_Phi_Residual_vs_Phi->Fill(genA1Mu0_phi, genA1Mu0_phi - reco_muons_phi[bestmatch_no_duplicates_2]);
							}
							if(diMuonF_match1 == bestmatch_no_duplicates_3){
								Fake_Muon_11_Eta_Residual->Fill(genA1Mu1_eta - reco_muons_eta[bestmatch_no_duplicates_3]);
								Fake_Muon_11_Eta_Residual_vs_Eta->Fill(genA1Mu1_eta, genA1Mu1_eta - reco_muons_eta[bestmatch_no_duplicates_3]);
								Fake_Muon_11_Phi_Residual->Fill(genA1Mu1_phi - reco_muons_phi[bestmatch_no_duplicates_3]);
								Fake_Muon_11_Phi_Residual_vs_Phi->Fill(genA1Mu1_phi, genA1Mu1_phi - reco_muons_phi[bestmatch_no_duplicates_3]);
							}
							//}}}

							//Plots
							//{{{
							//General Distributions
							Fake_Gen_Lxy->Fill(genA0_Lxy);
							Fake_Gen_Lz->Fill(genA0_Lz);
							Fake_Gen_Eta->Fill(genA0_eta);
							Fake_Gen_Phi->Fill(genA0_phi);
							Fake_Gen_pT->Fill(sqrt(genA0_px*genA0_px+genA0_py*genA0_py));
							Fake_Gen_pT_vs_Lxy->Fill(genA0_Lxy,sqrt(genA0_px*genA0_px+genA0_py*genA0_py));

							//GEN Distributions for fake dimuon 1 (A0)
							Fake_dimuon1_Gen_Lxy->Fill(genA0_Lxy);
							Fake_dimuon1_Gen_Lz->Fill(genA0_Lz);
							Fake_dimuon1_Gen_Eta->Fill(genA0_eta);
							Fake_dimuon1_Gen_Phi->Fill(genA0_phi);
							Fake_dimuon1_Gen_pT->Fill(sqrt(genA0_px*genA0_px+genA0_py*genA0_py));
							Fake_dimuon1_Gen_pT_vs_Lxy->Fill(genA0_Lxy,sqrt(genA0_px*genA0_px+genA0_py*genA0_py));

							//General RECO distributions for (diMuonF)
							if(diMuonF_FittedVtx_Lxy > -800) Fake_Reco_Lxy->Fill(diMuonF_FittedVtx_Lxy);
							if(diMuonF_FittedVtx_eta > -800) Fake_Reco_Eta->Fill(diMuonF_FittedVtx_eta);
							if(diMuonF_FittedVtx_phi > -800) Fake_Reco_Phi->Fill(diMuonF_FittedVtx_phi);
							if(diMuonF_FittedVtx_px > -800 && diMuonF_FittedVtx_py > -800) Fake_Reco_pT->Fill(sqrt(diMuonF_FittedVtx_px*diMuonF_FittedVtx_px+diMuonF_FittedVtx_py*diMuonF_FittedVtx_py));
							if(diMuonF_FittedVtx_px > -800 && diMuonF_FittedVtx_py > -800 && diMuonF_FittedVtx_Lxy > -800) Fake_Reco_pT_vs_Lxy->Fill(diMuonF_FittedVtx_Lxy, sqrt(diMuonF_FittedVtx_px*diMuonF_FittedVtx_px+diMuonF_FittedVtx_py*diMuonF_FittedVtx_py));
							if(diMuonF_FittedVtx_eta > -800 && diMuonF_FittedVtx_Lxy > -800) Fake_Reco_Eta_vs_Lxy->Fill(diMuonF_FittedVtx_eta, diMuonF_FittedVtx_Lxy);
							if(diMuonF_FittedVtx_eta > -800 && diMuonF_FittedVtx_phi > -800) Fake_Reco_Eta_vs_Phi->Fill(diMuonF_FittedVtx_eta, diMuonF_FittedVtx_phi);

							if(diMuonF_FittedVtx_eta > -800 && diMuonF_FittedVtx_vx > -800) Fake_Reco_Eta_vs_VertexR->Fill(diMuonF_FittedVtx_eta, sqrt((diMuonF_FittedVtx_vx*diMuonF_FittedVtx_vx)+(diMuonF_FittedVtx_vy*diMuonF_FittedVtx_vy)));
							if(diMuonF_FittedVtx_eta > -800 && diMuonF_FittedVtx_vz > -800) Fake_Reco_Eta_vs_VertexZ->Fill(diMuonF_FittedVtx_eta, diMuonF_FittedVtx_vz);

							//RECO Distributions for fake dimuon 1 (diMuonF)
							if(diMuonF_FittedVtx_Lxy > -800) Fake_dimuon1_Reco_Lxy->Fill(diMuonF_FittedVtx_Lxy);
							if(diMuonF_FittedVtx_eta > -800) Fake_dimuon1_Reco_Eta->Fill(diMuonF_FittedVtx_eta);
							if(diMuonF_FittedVtx_phi > -800) Fake_dimuon1_Reco_Phi->Fill(diMuonF_FittedVtx_phi);
							if(diMuonF_FittedVtx_px > -800 && diMuonF_FittedVtx_py > -800) Fake_dimuon1_Reco_pT->Fill(sqrt(diMuonF_FittedVtx_px*diMuonF_FittedVtx_px+diMuonF_FittedVtx_py*diMuonF_FittedVtx_py));
							if(diMuonF_FittedVtx_px > -800 && diMuonF_FittedVtx_py > -800 && diMuonF_FittedVtx_Lxy > -800) Fake_dimuon1_Reco_pT_vs_Lxy->Fill(diMuonF_FittedVtx_Lxy, sqrt(diMuonF_FittedVtx_px*diMuonF_FittedVtx_px+diMuonF_FittedVtx_py*diMuonF_FittedVtx_py));
							if(diMuonF_FittedVtx_eta > -800 && diMuonF_FittedVtx_phi > -800) Fake_dimuon1_Reco_Eta_vs_Phi->Fill(diMuonF_FittedVtx_eta, diMuonF_FittedVtx_phi);

							if(diMuonF_FittedVtx_eta > -800 && diMuonF_FittedVtx_Lxy > -800) Fake_dimuon1_Reco_Eta_vs_Lxy->Fill(diMuonF_FittedVtx_eta, diMuonF_FittedVtx_Lxy);

							//eta
							Fake_dimuon1_EtaResidual->Fill(genA0_eta - diMuonF_FittedVtx_eta);
							Fake_dimuon1_EtaResidual_vs_Eta->Fill(genA0_eta, genA0_eta - diMuonF_FittedVtx_eta);
							Fake_dimuon1_EtaResidual_vs_Lxy->Fill(genA0_Lxy, genA0_eta - diMuonF_FittedVtx_eta);

							//phi
							Fake_dimuon1_PhiResidual->Fill(genA0_phi - diMuonF_FittedVtx_phi);
							Fake_dimuon1_PhiResidual_vs_Phi->Fill(genA0_phi, genA0_phi - diMuonF_FittedVtx_phi);
							Fake_dimuon1_PhiResidual_vs_Lxy->Fill(genA0_Lxy, genA0_phi - diMuonF_FittedVtx_phi);

							//Lxy
							Fake_dimuon1_LxyResidual->Fill(genA0_Lxy - diMuonF_FittedVtx_Lxy);
							Fake_dimuon1_LxyResidual_vs_Lxy->Fill(genA0_Lxy, genA0_Lxy - diMuonF_FittedVtx_Lxy);

							//Vertex
							Fake1_GEN_Dimuon_vertex_r->Fill(sqrt(genA0Mu0_vx*genA0Mu0_vx + genA0Mu0_vy*genA0Mu0_vy));
							Fake1_RECO_Dimuon_vertex_r->Fill(sqrt(diMuonF_FittedVtx_vx*diMuonF_FittedVtx_vx + diMuonF_FittedVtx_vy*diMuonF_FittedVtx_vy));
							Fake1_Dimuon_vertex_r_Residual->Fill( sqrt(genA0Mu0_vx*genA0Mu0_vx + genA0Mu0_vy*genA0Mu0_vy) - sqrt(diMuonF_FittedVtx_vx*diMuonF_FittedVtx_vx + diMuonF_FittedVtx_vy*diMuonF_FittedVtx_vy));
							Fake1_Dimuon_vertex_r_Residual_vs_GEN->Fill(sqrt(genA0Mu0_vx*genA0Mu0_vx + genA0Mu0_vy*genA0Mu0_vy), sqrt(genA0Mu0_vx*genA0Mu0_vx + genA0Mu0_vy*genA0Mu0_vy) - sqrt(diMuonF_FittedVtx_vx*diMuonF_FittedVtx_vx + diMuonF_FittedVtx_vy*diMuonF_FittedVtx_vy));
							Fake1_Dimuon_Lxy_Residual_vs_GEN_vertex_r->Fill(sqrt(genA0Mu0_vx*genA0Mu0_vx + genA0Mu0_vy*genA0Mu0_vy), genA0_Lxy - diMuonF_FittedVtx_Lxy);
							Fake1_Dimuon_Lxy_Residual_vs_RECO_vertex_r->Fill(sqrt(diMuonF_FittedVtx_vx*diMuonF_FittedVtx_vx + diMuonF_FittedVtx_vy*diMuonF_FittedVtx_vy), genA0_Lxy - diMuonF_FittedVtx_Lxy);

							Fake1_GEN_Dimuon_vertex_z->Fill(genA0Mu0_vz);
							Fake1_RECO_Dimuon_vertex_z->Fill(diMuonF_FittedVtx_vz);
							Fake1_Dimuon_vertex_z_Residual->Fill(genA0Mu0_vz - diMuonF_FittedVtx_vz);
							Fake1_Dimuon_vertex_z_Residual_vs_GEN->Fill(genA0Mu0_vz, genA0Mu0_vz - diMuonF_FittedVtx_vz);
							Fake1_Dimuon_Lxy_Residual_vs_GEN_vertex_z->Fill(genA0Mu0_vz, genA0_Lxy - diMuonF_FittedVtx_Lxy);
							Fake1_Dimuon_Lxy_Residual_vs_RECO_vertex_z->Fill(diMuonF_FittedVtx_vz, genA0_Lxy - diMuonF_FittedVtx_Lxy);

							//}}}

						}
						if(fabs(genA1_Lxy)>=5.0 || fabs(genA1_Lz)>=34.5){ //A1 is the fake and has match diMuonC
							//NOW LOOK AT INDIVIDUAL MUONS
							//{{{
							//HERE, we know that DIMUONC is bad
							//DIMUONC contains RECO muons reco_real_muons_phi[diMuonC_match0] and reco_real_muons_phi[diMuonC_match1]
							//Now, I can pair these reco muons to GEN muons and create those plots

							if(diMuonC_match0 == bestmatch_no_duplicates_0){
								Fake_Muon_00_Eta_Residual->Fill(genA0Mu0_eta - reco_muons_eta[bestmatch_no_duplicates_0]);
								Fake_Muon_00_Eta_Residual_vs_Eta->Fill(genA0Mu0_eta, genA0Mu0_eta - reco_muons_eta[bestmatch_no_duplicates_0]);
								Fake_Muon_00_Phi_Residual->Fill(genA0Mu0_phi - reco_muons_phi[bestmatch_no_duplicates_0]);
								Fake_Muon_00_Phi_Residual_vs_Phi->Fill(genA0Mu0_phi, genA0Mu0_phi - reco_muons_phi[bestmatch_no_duplicates_0]);
							}       
							if(diMuonC_match0 == bestmatch_no_duplicates_1){
								Fake_Muon_01_Eta_Residual->Fill(genA0Mu1_eta - reco_muons_eta[bestmatch_no_duplicates_1]);
								Fake_Muon_01_Eta_Residual_vs_Eta->Fill(genA0Mu1_eta, genA0Mu1_eta - reco_muons_eta[bestmatch_no_duplicates_1]);
								Fake_Muon_01_Phi_Residual->Fill(genA0Mu1_phi - reco_muons_phi[bestmatch_no_duplicates_1]);
								Fake_Muon_01_Phi_Residual_vs_Phi->Fill(genA0Mu1_phi, genA0Mu1_phi - reco_muons_phi[bestmatch_no_duplicates_1]);
							}       
							if(diMuonC_match0 == bestmatch_no_duplicates_2){
								Fake_Muon_10_Eta_Residual->Fill(genA1Mu0_eta - reco_muons_eta[bestmatch_no_duplicates_2]);
								Fake_Muon_10_Eta_Residual_vs_Eta->Fill(genA1Mu0_eta, genA1Mu0_eta - reco_muons_eta[bestmatch_no_duplicates_2]);
								Fake_Muon_10_Phi_Residual->Fill(genA1Mu0_phi - reco_muons_phi[bestmatch_no_duplicates_2]);
								Fake_Muon_10_Phi_Residual_vs_Phi->Fill(genA1Mu0_phi, genA1Mu0_phi - reco_muons_phi[bestmatch_no_duplicates_2]);
							}       
							if(diMuonC_match0 == bestmatch_no_duplicates_3){
								Fake_Muon_11_Eta_Residual->Fill(genA1Mu1_eta - reco_muons_eta[bestmatch_no_duplicates_3]);
								Fake_Muon_11_Eta_Residual_vs_Eta->Fill(genA1Mu1_eta, genA1Mu1_eta - reco_muons_eta[bestmatch_no_duplicates_3]);
								Fake_Muon_11_Phi_Residual->Fill(genA1Mu1_phi - reco_muons_phi[bestmatch_no_duplicates_3]);
								Fake_Muon_11_Phi_Residual_vs_Phi->Fill(genA1Mu1_phi, genA1Mu1_phi - reco_muons_phi[bestmatch_no_duplicates_3]);
							}       
							if(diMuonC_match1 == bestmatch_no_duplicates_0){
								Fake_Muon_00_Eta_Residual->Fill(genA0Mu0_eta - reco_muons_eta[bestmatch_no_duplicates_0]);
								Fake_Muon_00_Eta_Residual_vs_Eta->Fill(genA0Mu0_eta, genA0Mu0_eta - reco_muons_eta[bestmatch_no_duplicates_0]);
								Fake_Muon_00_Phi_Residual->Fill(genA0Mu0_phi - reco_muons_phi[bestmatch_no_duplicates_0]);
								Fake_Muon_00_Phi_Residual_vs_Phi->Fill(genA0Mu0_phi, genA0Mu0_phi - reco_muons_phi[bestmatch_no_duplicates_0]);
							}                                                if(diMuonC_match1 == bestmatch_no_duplicates_1){
								Fake_Muon_01_Eta_Residual->Fill(genA0Mu1_eta - reco_muons_eta[bestmatch_no_duplicates_1]);
								Fake_Muon_01_Eta_Residual_vs_Eta->Fill(genA0Mu1_eta, genA0Mu1_eta - reco_muons_eta[bestmatch_no_duplicates_1]);
								Fake_Muon_01_Phi_Residual->Fill(genA0Mu1_phi - reco_muons_phi[bestmatch_no_duplicates_1]);
								Fake_Muon_01_Phi_Residual_vs_Phi->Fill(genA0Mu1_phi, genA0Mu1_phi - reco_muons_phi[bestmatch_no_duplicates_1]);
							}       
							if(diMuonC_match1 == bestmatch_no_duplicates_2){
								Fake_Muon_10_Eta_Residual->Fill(genA1Mu0_eta - reco_muons_eta[bestmatch_no_duplicates_2]);
								Fake_Muon_10_Eta_Residual_vs_Eta->Fill(genA1Mu0_eta, genA1Mu0_eta - reco_muons_eta[bestmatch_no_duplicates_2]);
								Fake_Muon_10_Phi_Residual->Fill(genA1Mu0_phi - reco_muons_phi[bestmatch_no_duplicates_2]);
								Fake_Muon_10_Phi_Residual_vs_Phi->Fill(genA1Mu0_phi, genA1Mu0_phi - reco_muons_phi[bestmatch_no_duplicates_2]);
							}       
							if(diMuonC_match1 == bestmatch_no_duplicates_3){
								Fake_Muon_11_Eta_Residual->Fill(genA1Mu1_eta - reco_muons_eta[bestmatch_no_duplicates_3]);
								Fake_Muon_11_Eta_Residual_vs_Eta->Fill(genA1Mu1_eta, genA1Mu1_eta - reco_muons_eta[bestmatch_no_duplicates_3]);
								Fake_Muon_11_Phi_Residual->Fill(genA1Mu1_phi - reco_muons_phi[bestmatch_no_duplicates_3]);
								Fake_Muon_11_Phi_Residual_vs_Phi->Fill(genA1Mu1_phi, genA1Mu1_phi - reco_muons_phi[bestmatch_no_duplicates_3]);
							}  
							//}}}

							//Plots
							//{{{
							//General Distributions
							Fake_Gen_Lxy->Fill(genA1_Lxy);
							Fake_Gen_Lz->Fill(genA1_Lz);
							Fake_Gen_Eta->Fill(genA1_eta);
							Fake_Gen_Phi->Fill(genA1_phi);
							Fake_Gen_pT->Fill(sqrt(genA1_px*genA1_px+genA1_py*genA1_py));
							Fake_Gen_pT_vs_Lxy->Fill(genA1_Lxy,sqrt(genA1_px*genA1_px+genA1_py*genA1_py));

							//GEN Distributions for fake dimuon 1 (A1)
							Fake_dimuon2_Gen_Lxy->Fill(genA1_Lxy);
							Fake_dimuon2_Gen_Lz->Fill(genA1_Lz);
							Fake_dimuon2_Gen_Eta->Fill(genA1_eta);
							Fake_dimuon2_Gen_Phi->Fill(genA1_phi);
							Fake_dimuon2_Gen_pT->Fill(sqrt(genA1_px*genA1_px+genA1_py*genA1_py));
							Fake_dimuon2_Gen_pT_vs_Lxy->Fill(genA1_Lxy,sqrt(genA1_px*genA1_px+genA1_py*genA1_py));

							//General RECO distributions for (diMuonC)
							if(diMuonC_FittedVtx_Lxy > -800) Fake_Reco_Lxy->Fill(diMuonC_FittedVtx_Lxy);
							if(diMuonC_FittedVtx_eta > -800) Fake_Reco_Eta->Fill(diMuonC_FittedVtx_eta);
							if(diMuonC_FittedVtx_phi > -800) Fake_Reco_Phi->Fill(diMuonC_FittedVtx_phi);
							if(diMuonC_FittedVtx_px > -800 && diMuonC_FittedVtx_py > -800) Fake_Reco_pT->Fill(sqrt(diMuonC_FittedVtx_px*diMuonC_FittedVtx_px+diMuonC_FittedVtx_py*diMuonC_FittedVtx_py));
							if(diMuonC_FittedVtx_px > -800 && diMuonC_FittedVtx_py > -800 && diMuonC_FittedVtx_Lxy > -800) Fake_Reco_pT_vs_Lxy->Fill(diMuonC_FittedVtx_Lxy, sqrt(diMuonC_FittedVtx_px*diMuonC_FittedVtx_px+diMuonC_FittedVtx_py*diMuonC_FittedVtx_py));
							if(diMuonC_FittedVtx_eta > -800 && diMuonC_FittedVtx_Lxy > -800) Fake_Reco_Eta_vs_Lxy->Fill(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_Lxy);
							if(diMuonC_FittedVtx_eta > -800 && diMuonC_FittedVtx_phi > -800) Fake_Reco_Eta_vs_Phi->Fill(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_phi);

							if(diMuonC_FittedVtx_eta > -800 && diMuonC_FittedVtx_vx > -800) Fake_Reco_Eta_vs_VertexR->Fill(diMuonC_FittedVtx_eta, sqrt((diMuonC_FittedVtx_vx*diMuonC_FittedVtx_vx)+(diMuonC_FittedVtx_vy*diMuonC_FittedVtx_vy)));
							if(diMuonC_FittedVtx_eta > -800 && diMuonC_FittedVtx_vz > -800) Fake_Reco_Eta_vs_VertexZ->Fill(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_vz);

							//RECO Distributions for fake dimuon 1 (diMuonC)
							if(diMuonC_FittedVtx_Lxy > -800) Fake_dimuon2_Reco_Lxy->Fill(diMuonC_FittedVtx_Lxy);
							if(diMuonC_FittedVtx_eta > -800) Fake_dimuon2_Reco_Eta->Fill(diMuonC_FittedVtx_eta);
							if(diMuonC_FittedVtx_phi > -800) Fake_dimuon2_Reco_Phi->Fill(diMuonC_FittedVtx_phi);
							if(diMuonC_FittedVtx_px > -800 && diMuonC_FittedVtx_py > -800) Fake_dimuon2_Reco_pT->Fill(sqrt(diMuonC_FittedVtx_px*diMuonC_FittedVtx_px+diMuonC_FittedVtx_py*diMuonC_FittedVtx_py));
							if(diMuonC_FittedVtx_px > -800 && diMuonC_FittedVtx_py > -800 && diMuonC_FittedVtx_Lxy > -800) Fake_dimuon2_Reco_pT_vs_Lxy->Fill(diMuonC_FittedVtx_Lxy, sqrt(diMuonC_FittedVtx_px*diMuonC_FittedVtx_px+diMuonC_FittedVtx_py*diMuonC_FittedVtx_py));
							if(diMuonC_FittedVtx_eta > -800 && diMuonC_FittedVtx_phi > -800) Fake_dimuon2_Reco_Eta_vs_Phi->Fill(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_phi);

							if(diMuonC_FittedVtx_eta > -800 && diMuonC_FittedVtx_Lxy > -800) Fake_dimuon2_Reco_Eta_vs_Lxy->Fill(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_Lxy);

							//eta
							Fake_dimuon2_EtaResidual->Fill(genA1_eta - diMuonC_FittedVtx_eta);
							Fake_dimuon2_EtaResidual_vs_Eta->Fill(genA1_eta, genA1_eta - diMuonC_FittedVtx_eta);
							Fake_dimuon2_EtaResidual_vs_Lxy->Fill(genA1_Lxy, genA1_eta - diMuonC_FittedVtx_eta);

							//phi
							Fake_dimuon2_PhiResidual->Fill(genA1_phi - diMuonC_FittedVtx_phi);
							Fake_dimuon2_PhiResidual_vs_Phi->Fill(genA1_phi, genA1_phi - diMuonC_FittedVtx_phi);
							Fake_dimuon2_PhiResidual_vs_Lxy->Fill(genA1_Lxy, genA1_phi - diMuonC_FittedVtx_phi);

							//Lxy
							Fake_dimuon2_LxyResidual->Fill(genA1_Lxy - diMuonC_FittedVtx_Lxy);
							Fake_dimuon2_LxyResidual_vs_Lxy->Fill(genA1_Lxy, genA1_Lxy - diMuonC_FittedVtx_Lxy);

							//Vertex
							Fake2_GEN_Dimuon_vertex_r->Fill(sqrt(genA1Mu0_vx*genA1Mu0_vx + genA1Mu0_vy*genA1Mu0_vy));
							Fake2_RECO_Dimuon_vertex_r->Fill(sqrt(diMuonC_FittedVtx_vx*diMuonC_FittedVtx_vx + diMuonC_FittedVtx_vy*diMuonC_FittedVtx_vy));
							Fake2_Dimuon_vertex_r_Residual->Fill( sqrt(genA1Mu0_vx*genA1Mu0_vx + genA1Mu0_vy*genA1Mu0_vy) - sqrt(diMuonC_FittedVtx_vx*diMuonC_FittedVtx_vx + diMuonC_FittedVtx_vy*diMuonC_FittedVtx_vy));
							Fake2_Dimuon_vertex_r_Residual_vs_GEN->Fill(sqrt(genA1Mu0_vx*genA1Mu0_vx + genA1Mu0_vy*genA1Mu0_vy), sqrt(genA1Mu0_vx*genA1Mu0_vx + genA1Mu0_vy*genA1Mu0_vy) - sqrt(diMuonC_FittedVtx_vx*diMuonC_FittedVtx_vx + diMuonC_FittedVtx_vy*diMuonC_FittedVtx_vy));
							Fake2_Dimuon_Lxy_Residual_vs_GEN_vertex_r->Fill(sqrt(genA1Mu0_vx*genA1Mu0_vx + genA1Mu0_vy*genA1Mu0_vy), genA1_Lxy - diMuonC_FittedVtx_Lxy);
							Fake2_Dimuon_Lxy_Residual_vs_RECO_vertex_r->Fill(sqrt(diMuonC_FittedVtx_vx*diMuonC_FittedVtx_vx + diMuonC_FittedVtx_vy*diMuonC_FittedVtx_vy), genA1_Lxy - diMuonC_FittedVtx_Lxy);

							Fake2_GEN_Dimuon_vertex_z->Fill(genA1Mu0_vz);
							Fake2_RECO_Dimuon_vertex_z->Fill(diMuonC_FittedVtx_vz);
							Fake2_Dimuon_vertex_z_Residual->Fill(genA1Mu0_vz - diMuonC_FittedVtx_vz);
							Fake2_Dimuon_vertex_z_Residual_vs_GEN->Fill(genA1Mu0_vz, genA1Mu0_vz - diMuonC_FittedVtx_vz);
							Fake2_Dimuon_Lxy_Residual_vs_GEN_vertex_z->Fill(genA1Mu0_vz, genA1_Lxy - diMuonC_FittedVtx_Lxy);
							Fake2_Dimuon_Lxy_Residual_vs_RECO_vertex_z->Fill(diMuonC_FittedVtx_vz, genA1_Lxy - diMuonC_FittedVtx_Lxy);

							//}}}

						}
					}
					//Geometry of events containing a fake
					Fake_GEN_Dimuon_Opening_Angle->Fill(My_dPhi(genA0_phi,genA1_phi));
					Fake_RECO_Dimuon_Opening_Angle->Fill(My_dPhi(diMuonC_FittedVtx_phi,diMuonF_FittedVtx_phi));
					Fake_Dimuon_Opening_Angle_Residual->Fill(My_dPhi(genA0_phi,genA1_phi)-My_dPhi(diMuonC_FittedVtx_phi,diMuonF_FittedVtx_phi));
					Fake_Dimuon_opening_Angle_Residual_vs_GENangle->Fill(My_dPhi(genA0_phi,genA1_phi), My_dPhi(genA0_phi,genA1_phi)-My_dPhi(diMuonC_FittedVtx_phi,diMuonF_FittedVtx_phi));

					double GEN_deta_forUncut1 = genA0_eta-genA1_eta;
					double GEN_dphi_forUncut1 = My_dPhi(genA0_phi,genA1_phi);
					double GEN_dr_forUncut1 = sqrt(GEN_deta_forUncut1*GEN_deta_forUncut1 + GEN_dphi_forUncut1*GEN_dphi_forUncut1);

					double RECO_deta_forUncut1 = diMuonC_FittedVtx_eta - diMuonF_FittedVtx_eta;
					double RECO_dphi_forUncut1 = My_dPhi(diMuonC_FittedVtx_phi,diMuonF_FittedVtx_phi);
					double RECO_dr_forUncut1 = sqrt(RECO_deta_forUncut1*RECO_deta_forUncut1 + RECO_dphi_forUncut1*RECO_dphi_forUncut1);

					Fake_GEN_deltaR_Between_Dimuons->Fill(GEN_dr_forUncut1);
					Fake_RECO_deltaR_Between_Dimuons->Fill(RECO_dr_forUncut1);
					Fake_deltaR_Between_Dimuons_Residual->Fill(GEN_dr_forUncut1 - RECO_dr_forUncut1);
					Fake_deltaR_Between_Dimuons_Residual_vs_GENdeltaR->Fill(GEN_dr_forUncut1, GEN_dr_forUncut1 - RECO_dr_forUncut1);



				}
				//Fill fake dimuon reason histogram
				//Fake dimuon counter begin
				if(fabs(genA0_Lxy >= 4.4) && fabs(genA0_Lz < 34.5)) fakeCounter_dimuon1 = 1; //Fails only Lxy
				if(fabs(genA0_Lxy < 4.4) && fabs(genA0_Lz >= 34.5)) fakeCounter_dimuon1 = 2; //Fails only Lz
				if(fabs(genA0_Lxy >= 4.4) && fabs(genA0_Lz >= 34.5)) fakeCounter_dimuon1 = 3; //Fails both Lxy and Lz
				if(fabs(genA1_Lxy >= 4.4) && fabs(genA1_Lz < 34.5)) fakeCounter_dimuon2 = 4; //Fails only Lxy
				if(fabs(genA1_Lxy < 4.4) && fabs(genA1_Lz >= 34.5)) fakeCounter_dimuon2 = 5; //Fails only Lz
				if(fabs(genA1_Lxy >= 4.4) && fabs(genA1_Lz >= 34.5)) fakeCounter_dimuon2 = 6; //Fails both Lxy and Lz
				if(fakeCounter_dimuon1 != 0 && fakeCounter_dimuon2 != 0) fakeCounter_both = 7;//both dimuons fail

				if(fakeCounter_both != 0) Fake_Dimuon_Reason->Fill(fakeCounter_both); 
				if(fakeCounter_dimuon1 != 0) Fake_Dimuon_Reason->Fill(fakeCounter_dimuon1);
				if(fakeCounter_dimuon2 != 0) Fake_Dimuon_Reason->Fill(fakeCounter_dimuon2);
			}

		} // closing for loop
		myfile->Close();
	} // closing while loop
	//Print out cutflow table
	//{{{
	std::cout << "" << std::endl;
	std::cout<<" Sample: " << fileName << endl;
	std::cout<<" Events          "<<ev_all<<std::endl;
	std::cout<<" ================ GEN MUONS ========================================= "<<std::endl;
	std::cout<<" 1GenMu17                       "<<c1genm<<"   reff "<<c1genm/(ev_all*1.0)<<std::endl;
	std::cout<<" 2GenMu8                        "<<c2genm<<"   reff  "<<c2genm/(c1genm*1.0)<<std::endl;
	std::cout<<" 3GenMu8                        "<<c3genm<<"   reff  "<<c3genm/(c2genm*1.0)<<std::endl;
	std::cout<<" 4GenMu8                        "<<c4genm<<"   reff  "<<c4genm/(c3genm*1.0)<<std::endl;
	std::cout<<" 4GenMu8 Lxy/Lz                 "<<ev_4gmlxylzcut<<"   reff   "<<ev_4gmlxylzcut/c4genm<<std::endl;
	std::cout<<" ================ RECO MUONS ========================================= "<<std::endl;
	std::cout<<" 1RecMu17                       "<<c1recm<<"  reff  "<<c1recm/(ev_all*1.0)<<std::endl;
	std::cout<<" 2RecMu8                        "<<c2recm<<"  reff  "<<c2recm/(c1recm*1.0)<<std::endl;
	std::cout<<" 3RecMu8                        "<<c3recm<<"  reff  "<<c3recm/(c2recm*1.0)<<std::endl;
	std::cout<<" 4RecMu8                        "<<c4recm<<"  reff  "<<c4recm/(c3recm*1.0)<<std::endl;
	std::cout<<" ================ EVENT variables ================= "<<std::endl;
	std::cout<<" Events with VtxOK              "<<ev_isVtxOK<<"    reff  "<<ev_isVtxOK/(1.0*c4recm)<<std::endl;
	std::cout<<" Events with 2 muonjets         "<<ev_is2MuJets<<"     reff  "<<ev_is2MuJets/(1.0*ev_isVtxOK)<<std::endl;
	std::cout<<" Events with 2 Dimuons          "<<ev_is2DiMuons<<"    reff  "<<ev_is2DiMuons/(1.0*ev_is2MuJets)<<std::endl;
	std::cout<<" Events with 2DimVtxOK          "<<ev_is2DiMuonsFittedVtxOK<<"    reff  "<<ev_is2DiMuonsFittedVtxOK/(1.0*ev_is2DiMuons)<<std::endl;
	std::cout<<" Events with 2DimHitPix         "<<ev_isPixelHitOK<<"     reff  "<<ev_isPixelHitOK/(1.0*ev_is2DiMuonsFittedVtxOK)<<std::endl;
	std::cout<<" Events with 2DimDzOK           "<<ev_is2DiMuonsDzOK_FittedVtx<<"   reff   "<<ev_is2DiMuonsDzOK_FittedVtx/(1.0*ev_isPixelHitOK)<<std::endl;
	std::cout<<" Events with 2DimMassOK         "<<ev_is2DiMuonsMassOK_FittedVtx<<"  reff   "<<ev_is2DiMuonsMassOK_FittedVtx/(1.0*ev_is2DiMuonsDzOK_FittedVtx)<<endl;
	std::cout<<" Events with 2DimIsoOK          "<<ev_is2DiMuonsIsoTkOK_FittedVtx<<"   reff   "<<ev_is2DiMuonsIsoTkOK_FittedVtx/(1.0*ev_is2DiMuonsMassOK_FittedVtx)<<endl;
	std::cout<<" Events with 2DimHLT            "<<ev_isDiMuonHLTFired<<"   reff   "<<ev_isDiMuonHLTFired/(1.0*ev_is2DiMuonsIsoTkOK_FittedVtx)<<endl;
	std::cout<<" ratio reco/gen                 "<<ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)<<" +/-  "<<sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut))<<std::endl;
	if(uncuttableFakeCounter != 0) std::cout << "Fake rate (#Fakes/#Events): " << std::setprecision(10) << (double)uncuttableFakeCounter/ev_all << std::endl;
	if(uncuttableFakeCounter == 0)  std::cout << "Fake rate (#Fakes/#Events): " << 0 << std::endl;
	//}}}

	//Fill ratio reco/gen vectors to be plotted  
	//Prepare plots and plot variables.  Also Fill final information printout vectors
	//{{{

	double cT_double; 
	if(cT_string == "000_") cT_double = 0;
	if(cT_string == "005_") cT_double = 0.05;
	if(cT_string == "010_") cT_double = 0.1;
	if(cT_string == "020_") cT_double = 0.2;
	if(cT_string == "050_") cT_double = 0.5;
	if(cT_string == "100_") cT_double = 1.0;
	if(cT_string == "200_") cT_double = 2.0;
	if(cT_string == "300_") cT_double = 3.0;
	if(cT_string == "500_") cT_double = 5.0;
	if(cT_string == "1000") cT_double = 10.0;
	if(cT_string == "2000") cT_double = 20.0;


	double mass_double;
	if(mass_string == "0250") mass_double = 0.25;
	if(mass_string == "0275") mass_double = 0.275;
	if(mass_string == "0300") mass_double = 0.30;
	if(mass_string == "2000") mass_double = 2.0;
	if(mass_string == "8500") mass_double = 8.5;
	if(mass_string == "0400") mass_double = 0.4;
	if(mass_string == "0700") mass_double = 0.7;
	if(mass_string == "1000") mass_double = 1.0;
	if(mass_string == "1500") mass_double = 1.5;

	//Fill final fake information vector
	cout << "Filling fake stat vector: " << endl;
	cout << "cT_string, cT_double    : " << cT_string << ", " << cT_double << endl;
	cout << "mass_string, mass_double: " << mass_string << ", " << mass_double << endl;
	cout << "ev_all                  : " << ev_all << endl;
	cout << "numFakes                : " << uncuttableFakeCounter << endl;
	FakesPerSample.push_back(mass_double);
	FakesPerSample.push_back(cT_double);
	FakesPerSample.push_back(ev_all);
	FakesPerSample.push_back(uncuttableFakeCounter);

	FakeStatistics.push_back(FakesPerSample);

	if(mass_string == "0250"){
		mGammaD_0250_eff.push_back(ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut));  
		mGammaD_0250_eff_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut)));  
		mGammaD_0250_cT.push_back(cT_double);
	}
	if(mass_string == "0275"){
		mGammaD_0275_eff.push_back(ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut));  
		mGammaD_0275_eff_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut)));  
		mGammaD_0275_cT.push_back(cT_double);  
	}
	if(mass_string == "0300"){
		mGammaD_0300_eff.push_back(ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut));  
		mGammaD_0300_eff_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut)));  
		mGammaD_0300_cT.push_back(cT_double);  
	}
	if(mass_string == "2000"){
		mGammaD_2000_eff.push_back(ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut));  
		mGammaD_2000_eff_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut)));  
		mGammaD_2000_cT.push_back(cT_double);  
	}
	if(mass_string == "8500"){
		mGammaD_8500_eff.push_back(ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut));  
		mGammaD_8500_eff_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut)));  
		mGammaD_8500_cT.push_back(cT_double);  
	}
	if(mass_string == "0400"){
		mGammaD_0400_eff.push_back(ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut));
		mGammaD_0400_eff_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut)));
		mGammaD_0400_cT.push_back(cT_double);
	}
	if(mass_string == "0700"){
		mGammaD_0700_eff.push_back(ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut));
		mGammaD_0700_eff_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut)));
		mGammaD_0700_cT.push_back(cT_double);
	}
	if(mass_string == "1000"){
		mGammaD_1000_eff.push_back(ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut));
		mGammaD_1000_eff_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut)));
		mGammaD_1000_cT.push_back(cT_double);
	}
	if(mass_string == "1500"){
		mGammaD_1500_eff.push_back(ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut));
		mGammaD_1500_eff_uncert.push_back(sqrt( ((ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut))*(1- (ev_isDiMuonHLTFired/(1.0*ev_4gmlxylzcut)) ))/(1.0*ev_4gmlxylzcut)));
		mGammaD_1500_cT.push_back(cT_double);
	}
	//}}}
}

void makePlot(){
	//Turn vectors in to arrays of data
	vector<double> null_0250;
	for(int i=0; i < mGammaD_0250_cT.size(); i++){
		null_0250.push_back(0);
	}
	double* array_null_0250               = &null_0250[0];
	double* array_mGammaD_0250_eff        = &mGammaD_0250_eff[0];
	double* array_mGammaD_0250_eff_uncert = &mGammaD_0250_eff_uncert[0];
	double* array_mGammaD_0250_cT         = &mGammaD_0250_cT[0];
	int size_0250 = null_0250.size();

	TGraphErrors *gr_eff_mD_0250 = new TGraphErrors(size_0250,array_mGammaD_0250_cT,array_mGammaD_0250_eff,array_null_0250,array_mGammaD_0250_eff_uncert);

	vector<double> null_0275;
	for(int i=0; i < mGammaD_0275_cT.size(); i++){
		null_0275.push_back(0);
	}
	double* array_null_0275               = &null_0275[0];
	double* array_mGammaD_0275_eff        = &mGammaD_0275_eff[0];
	double* array_mGammaD_0275_eff_uncert = &mGammaD_0275_eff_uncert[0];
	double* array_mGammaD_0275_cT         = &mGammaD_0275_cT[0];
	int size_0275 = null_0275.size();

	TGraphErrors *gr_eff_mD_0275 = new TGraphErrors(size_0275,array_mGammaD_0275_cT,array_mGammaD_0275_eff,array_null_0275,array_mGammaD_0275_eff_uncert);

	vector<double> null_0300;
	for(int i=0; i < mGammaD_0300_cT.size(); i++){
		null_0300.push_back(0);
	}
	double* array_null_0300               = &null_0300[0];
	double* array_mGammaD_0300_eff        = &mGammaD_0300_eff[0];
	double* array_mGammaD_0300_eff_uncert = &mGammaD_0300_eff_uncert[0];
	double* array_mGammaD_0300_cT         = &mGammaD_0300_cT[0];
	int size_0300 = null_0300.size();

	TGraphErrors *gr_eff_mD_0300 = new TGraphErrors(size_0300,array_mGammaD_0300_cT,array_mGammaD_0300_eff,array_null_0300,array_mGammaD_0300_eff_uncert);

	vector<double> null_2000;
	for(int i=0; i < mGammaD_2000_cT.size(); i++){
		null_2000.push_back(0);
	}
	double* array_null_2000		      = &null_2000[0];
	double* array_mGammaD_2000_eff        = &mGammaD_2000_eff[0];
	double* array_mGammaD_2000_eff_uncert = &mGammaD_2000_eff_uncert[0];
	double* array_mGammaD_2000_cT	      = &mGammaD_2000_cT[0];
	int size_2000 = null_2000.size();
	TGraphErrors *gr_eff_mD_2000 = new TGraphErrors(size_2000,array_mGammaD_2000_cT,array_mGammaD_2000_eff,array_null_2000,array_mGammaD_2000_eff_uncert);

	vector<double> null_8500;
	for(int i=0; i < mGammaD_8500_cT.size(); i++){
		null_8500.push_back(0);
	}
	double* array_null_8500               = &null_8500[0];
	double* array_mGammaD_8500_eff        = &mGammaD_8500_eff[0];
	double* array_mGammaD_8500_eff_uncert = &mGammaD_8500_eff_uncert[0];
	double* array_mGammaD_8500_cT         = &mGammaD_8500_cT[0];
	int size_8500 = null_8500.size();

	TGraphErrors *gr_eff_mD_8500 = new TGraphErrors(size_8500,array_mGammaD_8500_cT,array_mGammaD_8500_eff,array_null_8500,array_mGammaD_8500_eff_uncert);

	vector<double> null_0400;
	for(int i=0; i < mGammaD_0400_cT.size(); i++){
		null_0400.push_back(0);
	}
	double* array_null_0400               = &null_0400[0];
	double* array_mGammaD_0400_eff        = &mGammaD_0400_eff[0];
	double* array_mGammaD_0400_eff_uncert = &mGammaD_0400_eff_uncert[0];
	double* array_mGammaD_0400_cT         = &mGammaD_0400_cT[0];
	int size_0400 = null_0400.size();

	TGraphErrors *gr_eff_mD_0400 = new TGraphErrors(size_0400,array_mGammaD_0400_cT,array_mGammaD_0400_eff,array_null_0400,array_mGammaD_0400_eff_uncert);

	vector<double> null_0700;
	for(int i=0; i < mGammaD_0700_cT.size(); i++){
		null_0700.push_back(0);
	}
	double* array_null_0700               = &null_0700[0];
	double* array_mGammaD_0700_eff        = &mGammaD_0700_eff[0];
	double* array_mGammaD_0700_eff_uncert = &mGammaD_0700_eff_uncert[0];
	double* array_mGammaD_0700_cT         = &mGammaD_0700_cT[0];
	int size_0700 = null_0700.size();

	TGraphErrors *gr_eff_mD_0700 = new TGraphErrors(size_0700,array_mGammaD_0700_cT,array_mGammaD_0700_eff,array_null_0700,array_mGammaD_0700_eff_uncert);

	vector<double> null_1000;
	for(int i=0; i < mGammaD_1000_cT.size(); i++){
		null_1000.push_back(0);
	}
	double* array_null_1000               = &null_1000[0];
	double* array_mGammaD_1000_eff        = &mGammaD_1000_eff[0];
	double* array_mGammaD_1000_eff_uncert = &mGammaD_1000_eff_uncert[0];
	double* array_mGammaD_1000_cT         = &mGammaD_1000_cT[0];
	int size_1000 = null_1000.size();

	TGraphErrors *gr_eff_mD_1000 = new TGraphErrors(size_1000,array_mGammaD_1000_cT,array_mGammaD_1000_eff,array_null_1000,array_mGammaD_1000_eff_uncert);

	vector<double> null_1500;
	for(int i=0; i < mGammaD_1500_cT.size(); i++){
		null_1500.push_back(0);
	}
	double* array_null_1500               = &null_1500[0];
	double* array_mGammaD_1500_eff        = &mGammaD_1500_eff[0];
	double* array_mGammaD_1500_eff_uncert = &mGammaD_1500_eff_uncert[0];
	double* array_mGammaD_1500_cT         = &mGammaD_1500_cT[0];
	int size_1500 = null_1500.size();

	TGraphErrors *gr_eff_mD_1500 = new TGraphErrors(size_1500,array_mGammaD_1500_cT,array_mGammaD_1500_eff,array_null_1500,array_mGammaD_1500_eff_uncert);

	TLegend *leg = new TLegend(0.5,0.3,0.85,0.6);
	leg->SetBorderSize(0);
	leg->SetFillColor(0);
	leg->SetTextSize(0.045);
	leg->AddEntry(gr_eff_mD_0250,"m_{#gamma D}=0.250 GeV","PL");
	leg->AddEntry(gr_eff_mD_0275,"m_{#gamma D}=0.275 GeV","PL");
	leg->AddEntry(gr_eff_mD_0300,"m_{#gamma D}=0.300 GeV","PL");
	leg->AddEntry(gr_eff_mD_0400,"m_{#gamma D}=0.400 GeV","PL");
	leg->AddEntry(gr_eff_mD_0700,"m_{#gamma D}=0.700 GeV","PL");
	leg->AddEntry(gr_eff_mD_1000,"m_{#gamma D}=1.000 GeV","PL");
	leg->AddEntry(gr_eff_mD_1500,"m_{#gamma D}=1.500 GeV","PL");
	leg->AddEntry(gr_eff_mD_2000,"m_{#gamma D}=2.000 GeV","PL");
	leg->AddEntry(gr_eff_mD_8500,"m_{#gamma D}=8.500 GeV","PL");


	TH2F *dummy3 = new TH2F("dummy3","",400,-0.2,20.2,100,0.0,1.0);


	TCanvas *c = new TCanvas("c","c",700,500);
	dummy3->GetXaxis()->SetTitle("c#tau [mm]");
	dummy3->GetYaxis()->SetTitle("#epsilon_{full}/#alpha_{gen}");
	gStyle->SetOptStat(0);
	dummy3->Draw();

	gr_eff_mD_0250->SetLineWidth(1);
	gr_eff_mD_0250->SetMarkerSize(5);
	gr_eff_mD_0250->SetLineColor(1);
	gr_eff_mD_0250->SetMarkerColor(1);
	gr_eff_mD_0250->SetMarkerStyle(7);
	gr_eff_mD_0250->Draw("SAME PL");

	gr_eff_mD_0275->SetLineWidth(1);
	gr_eff_mD_0275->SetMarkerSize(5);
	gr_eff_mD_0275->SetLineColor(2);
	gr_eff_mD_0275->SetMarkerColor(2);
	gr_eff_mD_0275->SetMarkerStyle(7);
	gr_eff_mD_0275->Draw("SAME PL");

	gr_eff_mD_0300->SetLineWidth(1);
	gr_eff_mD_0300->SetMarkerSize(5);
	gr_eff_mD_0300->SetLineColor(3);
	gr_eff_mD_0300->SetMarkerColor(3);
	gr_eff_mD_0300->SetMarkerStyle(7);
	gr_eff_mD_0300->Draw("SAME PL");

	gr_eff_mD_0400->SetLineWidth(1);
	gr_eff_mD_0400->SetMarkerSize(5);
	gr_eff_mD_0400->SetLineColor(7);
	gr_eff_mD_0400->SetMarkerColor(7);
	gr_eff_mD_0400->SetMarkerStyle(7);
	gr_eff_mD_0400->Draw("SAME PL");

	gr_eff_mD_0700->SetLineWidth(1);
	gr_eff_mD_0700->SetMarkerSize(5);
	gr_eff_mD_0700->SetLineColor(8);
	gr_eff_mD_0700->SetMarkerColor(8);
	gr_eff_mD_0700->SetMarkerStyle(7);
	gr_eff_mD_0700->Draw("SAME PL");

	gr_eff_mD_1000->SetLineWidth(1);
	gr_eff_mD_1000->SetMarkerSize(5);
	gr_eff_mD_1000->SetLineColor(9);
	gr_eff_mD_1000->SetMarkerColor(9);
	gr_eff_mD_1000->SetMarkerStyle(7);
	gr_eff_mD_1000->Draw("SAME PL");

	gr_eff_mD_1500->SetLineWidth(1);
	gr_eff_mD_1500->SetMarkerSize(5);
	gr_eff_mD_1500->SetLineColor(kOrange);
	gr_eff_mD_1500->SetMarkerColor(kOrange);
	gr_eff_mD_1500->SetMarkerStyle(7);
	gr_eff_mD_1500->Draw("SAME PL");

	gr_eff_mD_2000->SetLineWidth(1);
	gr_eff_mD_2000->SetMarkerSize(5);
	gr_eff_mD_2000->SetLineColor(4);
	gr_eff_mD_2000->SetMarkerColor(4);
	gr_eff_mD_2000->SetMarkerStyle(7);
	gr_eff_mD_2000->Draw("SAME PL");

	gr_eff_mD_8500->SetLineWidth(1);
	gr_eff_mD_8500->SetMarkerSize(5);
	gr_eff_mD_8500->SetLineColor(6);
	gr_eff_mD_8500->SetMarkerColor(6);
	gr_eff_mD_8500->SetMarkerStyle(7);
	gr_eff_mD_8500->Draw("SAME PL");

	leg->Draw("same");
	//c->SaveAs("e_rec_alpha_gen_vs_cT.C");
	c->SaveAs("e_rec_alpha_gen_vs_cT_0250_GeV.pdf","recreate");
}

void makePlotsPretty(){
	Real_Gen_Lxy->GetXaxis()->SetTitle("L_{XY} [cm]");
	Real_Gen_Lxy->GetYaxis()->SetTitle("Events / 0.2 cm");
	Real_Gen_Eta->GetXaxis()->SetTitle("#eta");
	Real_Gen_Eta->GetYaxis()->SetTitle("Events / 0.02 cm");
	Real_Gen_Phi->GetXaxis()->SetTitle("#phi [rad]");
	Real_Gen_Phi->GetYaxis()->SetTitle("Events / 0.02 rad");
	Real_Gen_pT->GetXaxis()->SetTitle("p_{T} [GeV]");
	Real_Gen_pT->GetYaxis()->SetTitle("Events / 1 [GeV]");
	Real_Gen_MassCompatability->GetXaxis()->SetTitle("Mass #mu#mu_{1} [GeV/c^{2}]");
	Real_Gen_MassCompatability->GetYaxis()->SetTitle("Mass #mu#mu_{2} [GeV/c^{2}]");
	Real_Gen_pT_vs_Lxy->GetXaxis()->SetTitle("p_{T} [GeV]");
	Real_Gen_pT_vs_Lxy->GetYaxis()->SetTitle("L_{XY} [cm]");

	Real_Reco_Lxy->GetXaxis()->SetTitle("L_{XY} [cm]");
	Real_Reco_Lxy->GetYaxis()->SetTitle("Events / 0.2 cm");
	Real_Reco_Eta->GetXaxis()->SetTitle("#eta");
	Real_Reco_Eta->GetYaxis()->SetTitle("Events / 0.02 cm");
	Real_Reco_Phi->GetXaxis()->SetTitle("#phi [rad]");
	Real_Reco_Phi->GetYaxis()->SetTitle("Events / 0.02 rad");
	Real_Reco_pT->GetXaxis()->SetTitle("p_{T} [GeV]");
	Real_Reco_pT->GetYaxis()->SetTitle("Events / 1 [GeV]");
	Real_Reco_MassCompatability->GetXaxis()->SetTitle("Mass #mu#mu_{1} [GeV/c^{2}]");
	Real_Reco_MassCompatability->GetYaxis()->SetTitle("Mass #mu#mu_{2} [GeV/c^{2}]");
	Real_Reco_pT_vs_Lxy->GetXaxis()->SetTitle("p_{T} [GeV]");
	Real_Reco_pT_vs_Lxy->GetYaxis()->SetTitle("L_{XY} [cm]");

	Fake_Reco_Lxy->GetXaxis()->SetTitle("L_{XY} [cm]");
	Fake_Reco_Lxy->GetYaxis()->SetTitle("Events / 0.2 cm");
	Fake_Reco_Eta->GetXaxis()->SetTitle("#eta");
	Fake_Reco_Eta->GetYaxis()->SetTitle("Events / 0.02 cm");
	Fake_Reco_Phi->GetXaxis()->SetTitle("#phi [rad]");
	Fake_Reco_Phi->GetYaxis()->SetTitle("Events / 0.02 rad");
	Fake_Reco_pT->GetXaxis()->SetTitle("p_{T} [GeV]");
	Fake_Reco_pT->GetYaxis()->SetTitle("Events / 1 [GeV]");
	Fake_Reco_MassCompatability->GetXaxis()->SetTitle("Mass #mu#mu_{1} [GeV/c^{2}]");
	Fake_Reco_MassCompatability->GetYaxis()->SetTitle("Mass #mu#mu_{2} [GeV/c^{2}]");
	Fake_Reco_pT_vs_Lxy->GetXaxis()->SetTitle("p_{T} [GeV]");
	Fake_Reco_pT_vs_Lxy->GetYaxis()->SetTitle("L_{XY} [cm]");

	Fake_Gen_Lxy->GetXaxis()->SetTitle("L_{XY} [cm]");
	Fake_Gen_Lxy->GetYaxis()->SetTitle("Events / 0.2 cm");
	Fake_Gen_Eta->GetXaxis()->SetTitle("#eta");
	Fake_Gen_Eta->GetYaxis()->SetTitle("Events / 0.02 cm");
	Fake_Gen_Phi->GetXaxis()->SetTitle("#phi [rad]");
	Fake_Gen_Phi->GetYaxis()->SetTitle("Events / 0.02 rad");
	Fake_Gen_pT->GetXaxis()->SetTitle("p_{T} [GeV]");
	Fake_Gen_pT->GetYaxis()->SetTitle("Events / 1 [GeV]");
	Fake_Gen_MassCompatability->GetXaxis()->SetTitle("Mass #mu#mu_{1} [GeV/c^{2}]");
	Fake_Gen_MassCompatability->GetYaxis()->SetTitle("Mass #mu#mu_{2} [GeV/c^{2}]");
	Fake_Gen_pT_vs_Lxy->GetXaxis()->SetTitle("p_{T} [GeV]");
	Fake_Gen_pT_vs_Lxy->GetYaxis()->SetTitle("L_{XY} [cm]");

	Real_dimuon1_Gen_Lxy->GetXaxis()->SetTitle("L_{XY} [cm]");
	Real_dimuon1_Gen_Lxy->GetYaxis()->SetTitle("Events / 0.2 cm");
	Real_dimuon1_Gen_Eta->GetXaxis()->SetTitle("#eta");
	Real_dimuon1_Gen_Eta->GetYaxis()->SetTitle("Events / 0.02 cm");
	Real_dimuon1_Gen_Phi->GetXaxis()->SetTitle("#phi [rad]");
	Real_dimuon1_Gen_Phi->GetYaxis()->SetTitle("Events / 0.02 rad");
	Real_dimuon1_Gen_pT->GetXaxis()->SetTitle("p_{T} [GeV]");
	Real_dimuon1_Gen_pT->GetYaxis()->SetTitle("Events / 1 [GeV]");
	Real_dimuon1_Gen_MassCompatability->GetXaxis()->SetTitle("Mass #mu#mu_{1} [GeV/c^{2}]");
	Real_dimuon1_Gen_MassCompatability->GetYaxis()->SetTitle("Mass #mu#mu_{2} [GeV/c^{2}]");
	Real_dimuon1_Gen_pT_vs_Lxy->GetXaxis()->SetTitle("p_{T} [GeV]");
	Real_dimuon1_Gen_pT_vs_Lxy->GetYaxis()->SetTitle("L_{XY} [cm]");

	Real_dimuon1_Reco_Lxy->GetXaxis()->SetTitle("L_{XY} [cm]");
	Real_dimuon1_Reco_Lxy->GetYaxis()->SetTitle("Events / 0.2 cm");
	Real_dimuon1_Reco_Eta->GetXaxis()->SetTitle("#eta");
	Real_dimuon1_Reco_Eta->GetYaxis()->SetTitle("Events / 0.02 cm");
	Real_dimuon1_Reco_Phi->GetXaxis()->SetTitle("#phi [rad]");
	Real_dimuon1_Reco_Phi->GetYaxis()->SetTitle("Events / 0.02 rad");
	Real_dimuon1_Reco_pT->GetXaxis()->SetTitle("p_{T} [GeV]");
	Real_dimuon1_Reco_pT->GetYaxis()->SetTitle("Events / 1 [GeV]");
	Real_dimuon1_Reco_MassCompatability->GetXaxis()->SetTitle("Mass #mu#mu_{1} [GeV/c^{2}]");
	Real_dimuon1_Reco_MassCompatability->GetYaxis()->SetTitle("Mass #mu#mu_{2} [GeV/c^{2}]");
	Real_dimuon1_Reco_pT_vs_Lxy->GetXaxis()->SetTitle("p_{T} [GeV]");
	Real_dimuon1_Reco_pT_vs_Lxy->GetYaxis()->SetTitle("L_{XY} [cm]");

	Fake_dimuon1_Reco_Lxy->GetXaxis()->SetTitle("L_{XY} [cm]");
	Fake_dimuon1_Reco_Lxy->GetYaxis()->SetTitle("Events / 0.2 cm");
	Fake_dimuon1_Reco_Eta->GetXaxis()->SetTitle("#eta");
	Fake_dimuon1_Reco_Eta->GetYaxis()->SetTitle("Events / 0.02 cm");
	Fake_dimuon1_Reco_Phi->GetXaxis()->SetTitle("#phi [rad]");
	Fake_dimuon1_Reco_Phi->GetYaxis()->SetTitle("Events / 0.02 rad");
	Fake_dimuon1_Reco_pT->GetXaxis()->SetTitle("p_{T} [GeV]");
	Fake_dimuon1_Reco_pT->GetYaxis()->SetTitle("Events / 1 [GeV]");
	Fake_dimuon1_Reco_MassCompatability->GetXaxis()->SetTitle("Mass #mu#mu_{1} [GeV/c^{2}]");
	Fake_dimuon1_Reco_MassCompatability->GetYaxis()->SetTitle("Mass #mu#mu_{2} [GeV/c^{2}]");
	Fake_dimuon1_Reco_pT_vs_Lxy->GetXaxis()->SetTitle("p_{T} [GeV]");
	Fake_dimuon1_Reco_pT_vs_Lxy->GetYaxis()->SetTitle("L_{XY} [cm]");

	Fake_dimuon1_Gen_Lxy->GetXaxis()->SetTitle("L_{XY} [cm]");
	Fake_dimuon1_Gen_Lxy->GetYaxis()->SetTitle("Events / 0.2 cm");
	Fake_dimuon1_Gen_Eta->GetXaxis()->SetTitle("#eta");
	Fake_dimuon1_Gen_Eta->GetYaxis()->SetTitle("Events / 0.02 cm");
	Fake_dimuon1_Gen_Phi->GetXaxis()->SetTitle("#phi [rad]");
	Fake_dimuon1_Gen_Phi->GetYaxis()->SetTitle("Events / 0.02 rad");
	Fake_dimuon1_Gen_pT->GetXaxis()->SetTitle("p_{T} [GeV]");
	Fake_dimuon1_Gen_pT->GetYaxis()->SetTitle("Events / 1 [GeV]");
	Fake_dimuon1_Gen_MassCompatability->GetXaxis()->SetTitle("Mass #mu#mu_{1} [GeV/c^{2}]");
	Fake_dimuon1_Gen_MassCompatability->GetYaxis()->SetTitle("Mass #mu#mu_{2} [GeV/c^{2}]");
	Fake_dimuon1_Gen_pT_vs_Lxy->GetXaxis()->SetTitle("p_{T} [GeV]");
	Fake_dimuon1_Gen_pT_vs_Lxy->GetYaxis()->SetTitle("L_{XY} [cm]");

	Real_dimuon2_Gen_Lxy->GetXaxis()->SetTitle("L_{XY} [cm]");
	Real_dimuon2_Gen_Lxy->GetYaxis()->SetTitle("Events / 0.2 cm");
	Real_dimuon2_Gen_Eta->GetXaxis()->SetTitle("#eta");
	Real_dimuon2_Gen_Eta->GetYaxis()->SetTitle("Events / 0.02 cm");
	Real_dimuon2_Gen_Phi->GetXaxis()->SetTitle("#phi [rad]");
	Real_dimuon2_Gen_Phi->GetYaxis()->SetTitle("Events / 0.02 rad");
	Real_dimuon2_Gen_pT->GetXaxis()->SetTitle("p_{T} [GeV]");
	Real_dimuon2_Gen_pT->GetYaxis()->SetTitle("Events / 1 [GeV]");
	Real_dimuon2_Gen_MassCompatability->GetXaxis()->SetTitle("Mass #mu#mu_{1} [GeV/c^{2}]");
	Real_dimuon2_Gen_MassCompatability->GetYaxis()->SetTitle("Mass #mu#mu_{2} [GeV/c^{2}]");
	Real_dimuon2_Gen_pT_vs_Lxy->GetXaxis()->SetTitle("p_{T} [GeV]");
	Real_dimuon2_Gen_pT_vs_Lxy->GetYaxis()->SetTitle("L_{XY} [cm]");

	Real_dimuon2_Reco_Lxy->GetXaxis()->SetTitle("L_{XY} [cm]");
	Real_dimuon2_Reco_Lxy->GetYaxis()->SetTitle("Events / 0.2 cm");
	Real_dimuon2_Reco_Eta->GetXaxis()->SetTitle("#eta");
	Real_dimuon2_Reco_Eta->GetYaxis()->SetTitle("Events / 0.02 cm");
	Real_dimuon2_Reco_Phi->GetXaxis()->SetTitle("#phi [rad]");
	Real_dimuon2_Reco_Phi->GetYaxis()->SetTitle("Events / 0.02 rad");
	Real_dimuon2_Reco_pT->GetXaxis()->SetTitle("p_{T} [GeV]");
	Real_dimuon2_Reco_pT->GetYaxis()->SetTitle("Events / 1 [GeV]");
	Real_dimuon2_Reco_MassCompatability->GetXaxis()->SetTitle("Mass #mu#mu_{1} [GeV/c^{2}]");
	Real_dimuon2_Reco_MassCompatability->GetYaxis()->SetTitle("Mass #mu#mu_{2} [GeV/c^{2}]");
	Real_dimuon2_Reco_pT_vs_Lxy->GetXaxis()->SetTitle("p_{T} [GeV]");
	Real_dimuon2_Reco_pT_vs_Lxy->GetYaxis()->SetTitle("L_{XY} [cm]");

	Fake_dimuon2_Reco_Lxy->GetXaxis()->SetTitle("L_{XY} [cm]");
	Fake_dimuon2_Reco_Lxy->GetYaxis()->SetTitle("Events / 0.2 cm");
	Fake_dimuon2_Reco_Eta->GetXaxis()->SetTitle("#eta");
	Fake_dimuon2_Reco_Eta->GetYaxis()->SetTitle("Events / 0.02 cm");
	Fake_dimuon2_Reco_Phi->GetXaxis()->SetTitle("#phi [rad]");
	Fake_dimuon2_Reco_Phi->GetYaxis()->SetTitle("Events / 0.02 rad");
	Fake_dimuon2_Reco_pT->GetXaxis()->SetTitle("p_{T} [GeV]");
	Fake_dimuon2_Reco_pT->GetYaxis()->SetTitle("Events / 1 [GeV]");
	Fake_dimuon2_Reco_MassCompatability->GetXaxis()->SetTitle("Mass #mu#mu_{1} [GeV/c^{2}]");
	Fake_dimuon2_Reco_MassCompatability->GetYaxis()->SetTitle("Mass #mu#mu_{2} [GeV/c^{2}]");
	Fake_dimuon2_Reco_pT_vs_Lxy->GetXaxis()->SetTitle("p_{T} [GeV]");
	Fake_dimuon2_Reco_pT_vs_Lxy->GetYaxis()->SetTitle("L_{XY} [cm]");

	Fake_dimuon2_Gen_Lxy->GetXaxis()->SetTitle("L_{XY} [cm]");
	Fake_dimuon2_Gen_Lxy->GetYaxis()->SetTitle("Events / 0.2 cm");
	Fake_dimuon2_Gen_Eta->GetXaxis()->SetTitle("#eta");
	Fake_dimuon2_Gen_Eta->GetYaxis()->SetTitle("Events / 0.02 cm");
	Fake_dimuon2_Gen_Phi->GetXaxis()->SetTitle("#phi [rad]");
	Fake_dimuon2_Gen_Phi->GetYaxis()->SetTitle("Events / 0.02 rad");
	Fake_dimuon2_Gen_pT->GetXaxis()->SetTitle("p_{T} [GeV]");
	Fake_dimuon2_Gen_pT->GetYaxis()->SetTitle("Events / 1 [GeV]");
	Fake_dimuon2_Gen_MassCompatability->GetXaxis()->SetTitle("Mass #mu#mu_{1} [GeV/c^{2}]");
	Fake_dimuon2_Gen_MassCompatability->GetYaxis()->SetTitle("Mass #mu#mu_{2} [GeV/c^{2}]");
	Fake_dimuon2_Gen_pT_vs_Lxy->GetXaxis()->SetTitle("p_{T} [GeV]");
	Fake_dimuon2_Gen_pT_vs_Lxy->GetYaxis()->SetTitle("L_{XY} [cm]");

	Real_Reco_Eta_vs_Phi->GetXaxis()->SetTitle("#eta"); 
	Real_Reco_Eta_vs_Phi->GetYaxis()->SetTitle("#phi [rad]"); 

	Fake_Reco_Eta_vs_Phi->GetXaxis()->SetTitle("#eta");
	Fake_Reco_Eta_vs_Phi->GetYaxis()->SetTitle("#phi [rad]");

	Fake_dimuon1_Reco_Eta_vs_Phi->GetXaxis()->SetTitle("#eta");
	Fake_dimuon1_Reco_Eta_vs_Phi->GetYaxis()->SetTitle("#phi [rad]");

	Fake_dimuon2_Reco_Eta_vs_Phi->GetXaxis()->SetTitle("#eta");
	Fake_dimuon2_Reco_Eta_vs_Phi->GetYaxis()->SetTitle("#phi [rad]");

	Real_Reco_Eta_vs_Phi->GetXaxis()->SetTitle("#eta");
	Real_Reco_Eta_vs_Phi->GetYaxis()->SetTitle("#phi [rad]");

	Real_dimuon1_Reco_Eta_vs_Phi->GetXaxis()->SetTitle("#eta");
	Real_dimuon1_Reco_Eta_vs_Phi->GetYaxis()->SetTitle("#phi [rad]");

	Real_dimuon2_Reco_Eta_vs_Phi->GetXaxis()->SetTitle("#eta");
	Real_dimuon2_Reco_Eta_vs_Phi->GetYaxis()->SetTitle("#phi [rad]");

	Real_Reco_Eta_vs_Lxy->GetXaxis()->SetTitle("#eta");
	Real_Reco_Eta_vs_Lxy->GetYaxis()->SetTitle("L_{XY} [cm]"); 

	Fake_Reco_Eta_vs_Lxy->GetXaxis()->SetTitle("#eta");
	Fake_Reco_Eta_vs_Lxy->GetYaxis()->SetTitle("L_{XY} [cm]");

	Fake_dimuon1_Reco_Eta_vs_Lxy->GetXaxis()->SetTitle("#eta");
	Fake_dimuon1_Reco_Eta_vs_Lxy->GetYaxis()->SetTitle("L_{XY} [cm]");

	Fake_dimuon2_Reco_Eta_vs_Lxy->GetXaxis()->SetTitle("#eta");
	Fake_dimuon2_Reco_Eta_vs_Lxy->GetYaxis()->SetTitle("L_{XY} [cm]");

	Real_Reco_Eta_vs_Lxy->GetXaxis()->SetTitle("#eta");
	Real_Reco_Eta_vs_Lxy->GetYaxis()->SetTitle("L_{XY} [cm]");

	Real_dimuon1_Reco_Eta_vs_Lxy->GetXaxis()->SetTitle("#eta");
	Real_dimuon1_Reco_Eta_vs_Lxy->GetYaxis()->SetTitle("L_{XY} [cm]");

	Real_dimuon2_Reco_Eta_vs_Lxy->GetXaxis()->SetTitle("#eta");
	Real_dimuon2_Reco_Eta_vs_Lxy->GetYaxis()->SetTitle("L_{XY} [cm]");

	Fake_dimuon1_EtaResidual->GetXaxis()->SetTitle("#eta_{GEN}-#eta_{RECO}");
	Fake_dimuon1_EtaResidual->GetYaxis()->SetTitle("Events / 0.02 cm");
	Fake_dimuon2_EtaResidual->GetXaxis()->SetTitle("#eta_{GEN}-#eta_{RECO}");
	Fake_dimuon2_EtaResidual->GetYaxis()->SetTitle("Events / 0.02 cm");

	Real_dimuon2_EtaResidual->GetXaxis()->SetTitle("#eta_{GEN}-#eta_{RECO}");
	Real_dimuon2_EtaResidual->GetYaxis()->SetTitle("Events / 0.02 cm");

	Fake_dimuon1_EtaResidual_vs_Eta->GetXaxis()->SetTitle("#eta_{GEN}");
	Fake_dimuon1_EtaResidual_vs_Eta->GetYaxis()->SetTitle("#eta_{GEN}-#eta_{RECO}");
	Fake_dimuon2_EtaResidual_vs_Eta->GetXaxis()->SetTitle("#eta_{GEN}");
	Fake_dimuon2_EtaResidual_vs_Eta->GetYaxis()->SetTitle("#eta_{GEN}-#eta_{RECO}");
	Real_dimuon1_EtaResidual_vs_Eta->GetXaxis()->SetTitle("#eta_{GEN}");
	Real_dimuon1_EtaResidual_vs_Eta->GetYaxis()->SetTitle("#eta_{GEN}-#eta_{RECO}");
	Real_dimuon2_EtaResidual_vs_Eta->GetXaxis()->SetTitle("#eta_{GEN}");
	Real_dimuon2_EtaResidual_vs_Eta->GetYaxis()->SetTitle("#eta_{GEN}-#eta_{RECO}");

	Fake_dimuon1_EtaResidual_vs_Lxy->GetXaxis()->SetTitle("L_{XY}");
	Fake_dimuon1_EtaResidual_vs_Lxy->GetYaxis()->SetTitle("#eta_{GEN}-#eta_{RECO}");
	Fake_dimuon2_EtaResidual_vs_Lxy->GetXaxis()->SetTitle("L_{XY}");
	Fake_dimuon2_EtaResidual_vs_Lxy->GetYaxis()->SetTitle("#eta_{GEN}-#eta_{RECO}");
	Real_dimuon1_EtaResidual_vs_Lxy->GetXaxis()->SetTitle("L_{XY}");
	Real_dimuon1_EtaResidual_vs_Lxy->GetYaxis()->SetTitle("#eta_{GEN}-#eta_{RECO}");
	Real_dimuon2_EtaResidual_vs_Lxy->GetXaxis()->SetTitle("L_{XY}");
	Real_dimuon2_EtaResidual_vs_Lxy->GetYaxis()->SetTitle("#eta_{GEN}-#eta_{RECO}");

	Fake_dimuon1_PhiResidual->GetXaxis()->SetTitle("#phi_{GEN}-#phi_{RECO}");
	Fake_dimuon1_PhiResidual->GetYaxis()->SetTitle("Events / 0.02 cm");
	Fake_dimuon2_PhiResidual->GetXaxis()->SetTitle("#phi_{GEN}-#phi_{RECO}");
	Fake_dimuon2_PhiResidual->GetYaxis()->SetTitle("Events / 0.02 cm");

	Real_dimuon2_PhiResidual->GetXaxis()->SetTitle("#phi_{GEN}-#phi_{RECO}");
	Real_dimuon2_PhiResidual->GetYaxis()->SetTitle("Events / 0.02 cm");

	Fake_dimuon1_PhiResidual_vs_Phi->GetXaxis()->SetTitle("#phi_{GEN}");
	Fake_dimuon1_PhiResidual_vs_Phi->GetYaxis()->SetTitle("#phi_{GEN}-#phi_{RECO}");
	Fake_dimuon2_PhiResidual_vs_Phi->GetXaxis()->SetTitle("#phi_{GEN}");
	Fake_dimuon2_PhiResidual_vs_Phi->GetYaxis()->SetTitle("#phi_{GEN}-#phi_{RECO}");
	Real_dimuon1_PhiResidual_vs_Phi->GetXaxis()->SetTitle("#phi_{GEN}");
	Real_dimuon1_PhiResidual_vs_Phi->GetYaxis()->SetTitle("#phi_{GEN}-#phi_{RECO}");
	Real_dimuon2_PhiResidual_vs_Phi->GetXaxis()->SetTitle("#phi_{GEN}");
	Real_dimuon2_PhiResidual_vs_Phi->GetYaxis()->SetTitle("#phi_{GEN}-#phi_{RECO}");

	Fake_dimuon1_PhiResidual_vs_Lxy->GetXaxis()->SetTitle("L_{XY}");
	Fake_dimuon1_PhiResidual_vs_Lxy->GetYaxis()->SetTitle("#phi_{GEN}-#phi_{RECO}");
	Fake_dimuon2_PhiResidual_vs_Lxy->GetXaxis()->SetTitle("L_{XY}");
	Fake_dimuon2_PhiResidual_vs_Lxy->GetYaxis()->SetTitle("#phi_{GEN}-#phi_{RECO}");
	Real_dimuon1_PhiResidual_vs_Lxy->GetXaxis()->SetTitle("L_{XY}");
	Real_dimuon1_PhiResidual_vs_Lxy->GetYaxis()->SetTitle("#phi_{GEN}-#phi_{RECO}");
	Real_dimuon2_PhiResidual_vs_Lxy->GetXaxis()->SetTitle("L_{XY}");
	Real_dimuon2_PhiResidual_vs_Lxy->GetYaxis()->SetTitle("#phi_{GEN}-#phi_{RECO}");

	Fake_dimuon1_LxyResidual->GetXaxis()->SetTitle("#Lxy{GEN}-#Lxy{RECO}");
	Fake_dimuon1_LxyResidual->GetYaxis()->SetTitle("Events / 0.02 cm");
	Fake_dimuon2_LxyResidual->GetXaxis()->SetTitle("#Lxy{GEN}-#Lxy{RECO}");
	Fake_dimuon2_LxyResidual->GetYaxis()->SetTitle("Events / 0.02 cm");

	Real_dimuon2_LxyResidual->GetXaxis()->SetTitle("#Lxy{GEN}-#Lxy{RECO}");
	Real_dimuon2_LxyResidual->GetYaxis()->SetTitle("Events / 0.02 cm");

	Fake_dimuon1_LxyResidual_vs_Lxy->GetXaxis()->SetTitle("#Lxy{GEN}");
	Fake_dimuon1_LxyResidual_vs_Lxy->GetYaxis()->SetTitle("#Lxy{GEN}-#Lxy{RECO}");
	Fake_dimuon2_LxyResidual_vs_Lxy->GetXaxis()->SetTitle("#Lxy{GEN}");
	Fake_dimuon2_LxyResidual_vs_Lxy->GetYaxis()->SetTitle("#Lxy{GEN}-#Lxy{RECO}");
	Real_dimuon1_LxyResidual_vs_Lxy->GetXaxis()->SetTitle("#Lxy{GEN}");
	Real_dimuon1_LxyResidual_vs_Lxy->GetYaxis()->SetTitle("#Lxy{GEN}-#Lxy{RECO}");
	Real_dimuon2_LxyResidual_vs_Lxy->GetXaxis()->SetTitle("#Lxy{GEN}");
	Real_dimuon2_LxyResidual_vs_Lxy->GetYaxis()->SetTitle("#Lxy{GEN}-#Lxy{RECO}");

	Real_Muon_00_Eta_Residual->GetXaxis()->SetTitle("#eta_{GEN}-#eta_{RECO}");
	Real_Muon_00_Eta_Residual->GetYaxis()->SetTitle("Events / 0.02");
	Real_Muon_01_Eta_Residual->GetXaxis()->SetTitle("#eta_{GEN}-#eta_{RECO}");
	Real_Muon_01_Eta_Residual->GetYaxis()->SetTitle("Events / 0.02");
	Real_Muon_10_Eta_Residual->GetXaxis()->SetTitle("#eta_{GEN}-#eta_{RECO}");
	Real_Muon_10_Eta_Residual->GetYaxis()->SetTitle("Events / 0.02");
	Real_Muon_11_Eta_Residual->GetXaxis()->SetTitle("#eta_{GEN}-#eta_{RECO}");
	Real_Muon_11_Eta_Residual->GetYaxis()->SetTitle("Events / 0.02");

	Fake_Muon_00_Eta_Residual->GetXaxis()->SetTitle("#eta_{GEN}-#eta_{RECO}");
	Fake_Muon_00_Eta_Residual->GetYaxis()->SetTitle("Events / 0.02");
	Fake_Muon_01_Eta_Residual->GetXaxis()->SetTitle("#eta_{GEN}-#eta_{RECO}");
	Fake_Muon_01_Eta_Residual->GetYaxis()->SetTitle("Events / 0.02");
	Fake_Muon_10_Eta_Residual->GetXaxis()->SetTitle("#eta_{GEN}-#eta_{RECO}");
	Fake_Muon_10_Eta_Residual->GetYaxis()->SetTitle("Events / 0.02");
	Fake_Muon_11_Eta_Residual->GetXaxis()->SetTitle("#eta_{GEN}-#eta_{RECO}");
	Fake_Muon_11_Eta_Residual->GetYaxis()->SetTitle("Events / 0.02");

	Real_Muon_00_Phi_Residual->GetXaxis()->SetTitle("#phi_{GEN}-#phi_{RECO} [rad]");
	Real_Muon_00_Phi_Residual->GetYaxis()->SetTitle("Events / 0.02 rad");
	Real_Muon_01_Phi_Residual->GetXaxis()->SetTitle("#phi_{GEN}-#phi_{RECO} [rad]");
	Real_Muon_01_Phi_Residual->GetYaxis()->SetTitle("Events / 0.02 rad");
	Real_Muon_10_Phi_Residual->GetXaxis()->SetTitle("#phi_{GEN}-#phi_{RECO} [rad]");
	Real_Muon_10_Phi_Residual->GetYaxis()->SetTitle("Events / 0.02 rad");
	Real_Muon_11_Phi_Residual->GetXaxis()->SetTitle("#phi_{GEN}-#phi_{RECO} [rad]");
	Real_Muon_11_Phi_Residual->GetYaxis()->SetTitle("Events / 0.02 rad");

	Fake_Muon_00_Phi_Residual->GetXaxis()->SetTitle("#phi_{GEN}-#phi_{RECO} [rad]");
	Fake_Muon_00_Phi_Residual->GetYaxis()->SetTitle("Events / 0.02 rad");
	Fake_Muon_01_Phi_Residual->GetXaxis()->SetTitle("#phi_{GEN}-#phi_{RECO} [rad]");
	Fake_Muon_01_Phi_Residual->GetYaxis()->SetTitle("Events / 0.02 rad");
	Fake_Muon_10_Phi_Residual->GetXaxis()->SetTitle("#phi_{GEN}-#phi_{RECO} [rad]");
	Fake_Muon_10_Phi_Residual->GetYaxis()->SetTitle("Events / 0.02 rad");
	Fake_Muon_11_Phi_Residual->GetXaxis()->SetTitle("#phi_{GEN}-#phi_{RECO} [rad]");
	Fake_Muon_11_Phi_Residual->GetYaxis()->SetTitle("Events / 0.02 rad");

	Real_Muon_00_Eta_Residual_vs_Eta->GetYaxis()->SetTitle("#eta_{GEN}-#eta_{RECO}");
	Real_Muon_00_Eta_Residual_vs_Eta->GetXaxis()->SetTitle("GEN #eta");
	Real_Muon_01_Eta_Residual_vs_Eta->GetYaxis()->SetTitle("#eta_{GEN}-#eta_{RECO}");
	Real_Muon_01_Eta_Residual_vs_Eta->GetXaxis()->SetTitle("GEN #eta");
	Real_Muon_10_Eta_Residual_vs_Eta->GetYaxis()->SetTitle("#eta_{GEN}-#eta_{RECO}");
	Real_Muon_10_Eta_Residual_vs_Eta->GetXaxis()->SetTitle("GEN #eta");
	Real_Muon_11_Eta_Residual_vs_Eta->GetYaxis()->SetTitle("#eta_{GEN}-#eta_{RECO}");
	Real_Muon_11_Eta_Residual_vs_Eta->GetXaxis()->SetTitle("GEN #eta");

	Fake_Muon_00_Eta_Residual_vs_Eta->GetYaxis()->SetTitle("#eta_{GEN}-#eta_{RECO}");
	Fake_Muon_00_Eta_Residual_vs_Eta->GetXaxis()->SetTitle("GEN #eta");
	Fake_Muon_01_Eta_Residual_vs_Eta->GetYaxis()->SetTitle("#eta_{GEN}-#eta_{RECO}");
	Fake_Muon_01_Eta_Residual_vs_Eta->GetXaxis()->SetTitle("GEN #eta");
	Fake_Muon_10_Eta_Residual_vs_Eta->GetYaxis()->SetTitle("#eta_{GEN}-#eta_{RECO}");
	Fake_Muon_10_Eta_Residual_vs_Eta->GetXaxis()->SetTitle("GEN #eta");
	Fake_Muon_11_Eta_Residual_vs_Eta->GetYaxis()->SetTitle("#eta_{GEN}-#eta_{RECO}");
	Fake_Muon_11_Eta_Residual_vs_Eta->GetXaxis()->SetTitle("GEN #eta");

	Real_Muon_00_Phi_Residual_vs_Phi->GetYaxis()->SetTitle("#phi_{GEN}-#phi_{RECO}");
	Real_Muon_00_Phi_Residual_vs_Phi->GetXaxis()->SetTitle("GEN #phi");
	Real_Muon_01_Phi_Residual_vs_Phi->GetYaxis()->SetTitle("#phi_{GEN}-#phi_{RECO}");
	Real_Muon_01_Phi_Residual_vs_Phi->GetXaxis()->SetTitle("GEN #phi");
	Real_Muon_10_Phi_Residual_vs_Phi->GetYaxis()->SetTitle("#phi_{GEN}-#phi_{RECO}");
	Real_Muon_10_Phi_Residual_vs_Phi->GetXaxis()->SetTitle("GEN #phi");
	Real_Muon_11_Phi_Residual_vs_Phi->GetYaxis()->SetTitle("#phi_{GEN}-#phi_{RECO}");
	Real_Muon_11_Phi_Residual_vs_Phi->GetXaxis()->SetTitle("GEN #phi");

	Fake_Muon_00_Phi_Residual_vs_Phi->GetYaxis()->SetTitle("#phi_{GEN}-#phi_{RECO}");
	Fake_Muon_00_Phi_Residual_vs_Phi->GetXaxis()->SetTitle("GEN #phi");
	Fake_Muon_01_Phi_Residual_vs_Phi->GetYaxis()->SetTitle("#phi_{GEN}-#phi_{RECO}");
	Fake_Muon_01_Phi_Residual_vs_Phi->GetXaxis()->SetTitle("GEN #phi");
	Fake_Muon_10_Phi_Residual_vs_Phi->GetYaxis()->SetTitle("#phi_{GEN}-#phi_{RECO}");
	Fake_Muon_10_Phi_Residual_vs_Phi->GetXaxis()->SetTitle("GEN #phi");
	Fake_Muon_11_Phi_Residual_vs_Phi->GetYaxis()->SetTitle("#phi_{GEN}-#phi_{RECO}");
	Fake_Muon_11_Phi_Residual_vs_Phi->GetXaxis()->SetTitle("GEN #phi");


	//Geometry plots
	Real_GEN_Dimuon_Opening_Angle->GetXaxis()->SetTitle("#Delta#phi Between GEN Dimuons [rads]");
	Real_GEN_Dimuon_Opening_Angle->GetYaxis()->SetTitle("Events / 0.02 rad");

	Real_RECO_Dimuon_Opening_Angle->GetXaxis()->SetTitle("#Delta#phi Between RECO Dimuons [rads]");
	Real_RECO_Dimuon_Opening_Angle->GetYaxis()->SetTitle("Events / 0.02 rad");

	Real_Dimuon_Opening_Angle_Residual->GetXaxis()->SetTitle("Residual #Delta#phi Between Dimuon (#Delta#phi_{GEN}-#Delta#phi_{RECO}) [rads]");
	Real_Dimuon_Opening_Angle_Residual->GetYaxis()->SetTitle("Events / 0.02 rad");

	Real_Dimuon_opening_Angle_Residual_vs_GENangle->GetYaxis()->SetTitle("Residual #Delta#phi Between Dimuon (#Delta#phi_{GEN}-#Delta#phi_{RECO}) [rads]");
	Real_Dimuon_opening_Angle_Residual_vs_GENangle->GetXaxis()->SetTitle("GEN #Delta#phi [rads]");

	Fake_GEN_Dimuon_Opening_Angle->GetXaxis()->SetTitle("#Delta#phi Between GEN Dimuons [rads]");
	Fake_GEN_Dimuon_Opening_Angle->GetYaxis()->SetTitle("Events / 0.02 rad");

	Fake_RECO_Dimuon_Opening_Angle->GetXaxis()->SetTitle("#Delta#phi Between RECO Dimuons [rads]");
	Fake_RECO_Dimuon_Opening_Angle->GetYaxis()->SetTitle("Events / 0.02 rad");

	Fake_Dimuon_Opening_Angle_Residual->GetXaxis()->SetTitle("Residual #Delta#phi Between Dimuon (#Delta#phi_{GEN}-#Delta#phi_{RECO}) [rads]");
	Fake_Dimuon_Opening_Angle_Residual->GetYaxis()->SetTitle("Events / 0.02 rad");

	Fake_Dimuon_opening_Angle_Residual_vs_GENangle->GetYaxis()->SetTitle("Residual #Delta#phi Between Dimuon (#Delta#phi_{GEN}-#Delta#phi_{RECO}) [rads]");
	Fake_Dimuon_opening_Angle_Residual_vs_GENangle->GetXaxis()->SetTitle("GEN #Delta#phi [rads]");

	Fake_GEN_Dimuon_Opening_Angle->GetXaxis()->SetTitle("#Delta#phi Between GEN Dimuons [rads]");
	Fake_GEN_Dimuon_Opening_Angle->GetYaxis()->SetTitle("Events / 0.02 rad");

	Fake_RECO_Dimuon_Opening_Angle->GetXaxis()->SetTitle("#Delta#phi Between RECO Dimuons [rads]");
	Fake_RECO_Dimuon_Opening_Angle->GetYaxis()->SetTitle("Events / 0.02 rad");

	Fake_Dimuon_Opening_Angle_Residual->GetXaxis()->SetTitle("Residual #Delta#phi Between Dimuon (#Delta#phi_{GEN}-#Delta#phi_{RECO}) [rads]");
	Fake_Dimuon_Opening_Angle_Residual->GetYaxis()->SetTitle("Events / 0.02 rad");

	Fake_Dimuon_opening_Angle_Residual_vs_GENangle->GetYaxis()->SetTitle("Residual #Delta#phi Between Dimuon (#Delta#phi_{GEN}-#Delta#phi_{RECO}) [rads]");
	Fake_Dimuon_opening_Angle_Residual_vs_GENangle->GetXaxis()->SetTitle("GEN #Delta#phi [rads]");

	Real_GEN_deltaR_Between_Dimuons->GetXaxis()->SetTitle("#Delta R Between GEN Dimuons");
	Real_GEN_deltaR_Between_Dimuons->GetYaxis()->SetTitle("Events / 0.02");

	Real_RECO_deltaR_Between_Dimuons->GetXaxis()->SetTitle("#Delta R Between RECO Dimuons");
	Real_RECO_deltaR_Between_Dimuons->GetYaxis()->SetTitle("Events / 0.02");

	Real_deltaR_Between_Dimuons_Residual->GetXaxis()->SetTitle("Residual #Delta R Between Dimuon (#Delta R_{GEN}-#Delta R_{RECO})");
	Real_deltaR_Between_Dimuons_Residual->GetYaxis()->SetTitle("Events / 0.02");

	Real_deltaR_Between_Dimuons_Residual_vs_GENdeltaR->GetYaxis()->SetTitle("Residual #Delta R Between Dimuon (#Delta R_{GEN}-#Delta R_{RECO})");
	Real_deltaR_Between_Dimuons_Residual_vs_GENdeltaR->GetXaxis()->SetTitle("GEN #Delta R");

	Fake_GEN_deltaR_Between_Dimuons->GetXaxis()->SetTitle("#Delta R Between GEN Dimuons");
	Fake_GEN_deltaR_Between_Dimuons->GetYaxis()->SetTitle("Events / 0.02");

	Fake_RECO_deltaR_Between_Dimuons->GetXaxis()->SetTitle("#Delta R Between RECO Dimuons");
	Fake_RECO_deltaR_Between_Dimuons->GetYaxis()->SetTitle("Events / 0.02");

	Fake_deltaR_Between_Dimuons_Residual->GetXaxis()->SetTitle("Residual #Delta R Between Dimuon (#Delta R_{GEN}-#Delta R_{RECO})");
	Fake_deltaR_Between_Dimuons_Residual->GetYaxis()->SetTitle("Events / 0.02");

	Fake_deltaR_Between_Dimuons_Residual_vs_GENdeltaR->GetYaxis()->SetTitle("Residual #Delta R Between Dimuon (#Delta R_{GEN}-#Delta R_{RECO})");
	Fake_deltaR_Between_Dimuons_Residual_vs_GENdeltaR->GetXaxis()->SetTitle("GEN #Delta R");

	Fake_GEN_deltaR_Between_Dimuons->GetXaxis()->SetTitle("#Delta R Between GEN Dimuons");
	Fake_GEN_deltaR_Between_Dimuons->GetYaxis()->SetTitle("Events / 0.02");

	Fake_RECO_deltaR_Between_Dimuons->GetXaxis()->SetTitle("#Delta R Between RECO Dimuons");
	Fake_RECO_deltaR_Between_Dimuons->GetYaxis()->SetTitle("Events / 0.02");

	Fake_deltaR_Between_Dimuons_Residual->GetXaxis()->SetTitle("Residual #Delta R Between Dimuon (#Delta R_{GEN}-#Delta R_{RECO})");
	Fake_deltaR_Between_Dimuons_Residual->GetYaxis()->SetTitle("Events / 0.02");

	Fake_deltaR_Between_Dimuons_Residual_vs_GENdeltaR->GetYaxis()->SetTitle("Residual #Delta R Between Dimuon (#Delta R_{GEN}-#Delta R_{RECO})");
	Fake_deltaR_Between_Dimuons_Residual_vs_GENdeltaR->GetXaxis()->SetTitle("GEN #Delta R");


	//Vertex position
	Real_Dimuon1_GEN_Dimuon_vertex_r->GetXaxis()->SetTitle("GEN Vertex Position R [cm]");
	Real_Dimuon1_GEN_Dimuon_vertex_r->GetYaxis()->SetTitle("Events / 0.02 [cm]");

	Real_Dimuon1_RECO_Dimuon_vertex_r->GetXaxis()->SetTitle("RECO Vertex Position R [cm]");
	Real_Dimuon1_RECO_Dimuon_vertex_r->GetYaxis()->SetTitle("Events / 0.02 [cm]");

	Real_Dimuon1_Dimuon_vertex_r_Residual->GetXaxis()->SetTitle("Vertex Position R Residual (GEN-RECO) [cm]");
	Real_Dimuon1_Dimuon_vertex_r_Residual->GetYaxis()->SetTitle("Events / 0.02 [cm]");

	Real_Dimuon1_Dimuon_vertex_r_Residual_vs_GEN->GetYaxis()->SetTitle("Vertex Position R Residual (GEN-RECO) [cm]");
	Real_Dimuon1_Dimuon_vertex_r_Residual_vs_GEN->GetXaxis()->SetTitle("GEN Vertex Position R [cm]");

	Real_Dimuon1_Dimuon_Lxy_Residual_vs_GEN_vertex_r->GetYaxis()->SetTitle("Dimuon L_{XY} Residual [cm]");
	Real_Dimuon1_Dimuon_Lxy_Residual_vs_GEN_vertex_r->GetXaxis()->SetTitle("GEN Vertex Position R [cm]");

	Real_Dimuon1_Dimuon_Lxy_Residual_vs_RECO_vertex_r->GetYaxis()->SetTitle("Dimuon L_{XY} Residual [cm]");
	Real_Dimuon1_Dimuon_Lxy_Residual_vs_RECO_vertex_r->GetXaxis()->SetTitle("RECO Vertex Position R [cm]");

	Real_Dimuon1_GEN_Dimuon_vertex_z->GetXaxis()->SetTitle("GEN Vertex Position Z [cm]");
	Real_Dimuon1_GEN_Dimuon_vertex_z->GetYaxis()->SetTitle("Events / 0.02 [cm]");

	Real_Dimuon1_RECO_Dimuon_vertex_z->GetXaxis()->SetTitle("RECO Vertex Position Z [cm]");
	Real_Dimuon1_RECO_Dimuon_vertex_z->GetYaxis()->SetTitle("Events / 0.02 [cm]");

	Real_Dimuon1_Dimuon_vertex_z_Residual->GetXaxis()->SetTitle("Vertex Position Z Residual (GEN-RECO) [cm]");
	Real_Dimuon1_Dimuon_vertex_z_Residual->GetYaxis()->SetTitle("Events / 0.02 [cm]");

	Real_Dimuon1_Dimuon_vertex_z_Residual_vs_GEN->GetYaxis()->SetTitle("Vertex Position Z Residual (GEN-RECO) [cm]");
	Real_Dimuon1_Dimuon_vertex_z_Residual_vs_GEN->GetXaxis()->SetTitle("GEN Vertex Position Z [cm]");

	Real_Dimuon1_Dimuon_Lxy_Residual_vs_GEN_vertex_z->GetYaxis()->SetTitle("Dimuon L_{XY} Residual [cm]");
	Real_Dimuon1_Dimuon_Lxy_Residual_vs_GEN_vertex_z->GetXaxis()->SetTitle("GEN Vertex Position Z [cm]");

	Real_Dimuon1_Dimuon_Lxy_Residual_vs_RECO_vertex_z->GetYaxis()->SetTitle("Dimuon L_{XY} Residual [cm]");
	Real_Dimuon1_Dimuon_Lxy_Residual_vs_RECO_vertex_z->GetXaxis()->SetTitle("RECO Vertex Position Z [cm]");

	Real_Dimuon2_GEN_Dimuon_vertex_r->GetXaxis()->SetTitle("GEN Vertex Position R [cm]");
	Real_Dimuon2_GEN_Dimuon_vertex_r->GetYaxis()->SetTitle("Events / 0.02 [cm]");

	Real_Dimuon2_RECO_Dimuon_vertex_r->GetXaxis()->SetTitle("RECO Vertex Position R [cm]");
	Real_Dimuon2_RECO_Dimuon_vertex_r->GetYaxis()->SetTitle("Events / 0.02 [cm]");

	Real_Dimuon2_Dimuon_vertex_r_Residual->GetXaxis()->SetTitle("Vertex Position R Residual (GEN-RECO) [cm]");
	Real_Dimuon2_Dimuon_vertex_r_Residual->GetYaxis()->SetTitle("Events / 0.02 [cm]");

	Real_Dimuon2_Dimuon_vertex_r_Residual_vs_GEN->GetYaxis()->SetTitle("Vertex Position R Residual (GEN-RECO) [cm]");
	Real_Dimuon2_Dimuon_vertex_r_Residual_vs_GEN->GetXaxis()->SetTitle("GEN Vertex Position R [cm]");

	Real_Dimuon2_Dimuon_Lxy_Residual_vs_GEN_vertex_r->GetYaxis()->SetTitle("Dimuon L_{XY} Residual [cm]");
	Real_Dimuon2_Dimuon_Lxy_Residual_vs_GEN_vertex_r->GetXaxis()->SetTitle("GEN Vertex Position R [cm]");

	Real_Dimuon2_Dimuon_Lxy_Residual_vs_RECO_vertex_r->GetYaxis()->SetTitle("Dimuon L_{XY} Residual [cm]");
	Real_Dimuon2_Dimuon_Lxy_Residual_vs_RECO_vertex_r->GetXaxis()->SetTitle("RECO Vertex Position R [cm]");

	Real_Dimuon2_GEN_Dimuon_vertex_z->GetXaxis()->SetTitle("GEN Vertex Position Z [cm]");
	Real_Dimuon2_GEN_Dimuon_vertex_z->GetYaxis()->SetTitle("Events / 0.02 [cm]");

	Real_Dimuon2_RECO_Dimuon_vertex_z->GetXaxis()->SetTitle("RECO Vertex Position Z [cm]");
	Real_Dimuon2_RECO_Dimuon_vertex_z->GetYaxis()->SetTitle("Events / 0.02 [cm]");

	Real_Dimuon2_Dimuon_vertex_z_Residual->GetXaxis()->SetTitle("Vertex Position Z Residual (GEN-RECO) [cm]");
	Real_Dimuon2_Dimuon_vertex_z_Residual->GetYaxis()->SetTitle("Events / 0.02 [cm]");

	Real_Dimuon2_Dimuon_vertex_z_Residual_vs_GEN->GetYaxis()->SetTitle("Vertex Position Z Residual (GEN-RECO) [cm]");
	Real_Dimuon2_Dimuon_vertex_z_Residual_vs_GEN->GetXaxis()->SetTitle("GEN Vertex Position Z [cm]");

	Real_Dimuon2_Dimuon_Lxy_Residual_vs_GEN_vertex_z->GetYaxis()->SetTitle("Dimuon L_{XY} Residual [cm]");
	Real_Dimuon2_Dimuon_Lxy_Residual_vs_GEN_vertex_z->GetXaxis()->SetTitle("GEN Vertex Position Z [cm]");

	Real_Dimuon2_Dimuon_Lxy_Residual_vs_RECO_vertex_z->GetYaxis()->SetTitle("Dimuon L_{XY} Residual [cm]");
	Real_Dimuon2_Dimuon_Lxy_Residual_vs_RECO_vertex_z->GetXaxis()->SetTitle("RECO Vertex Position Z [cm]");

	Fake1_GEN_Dimuon_vertex_r->GetXaxis()->SetTitle("GEN Vertex Position R [cm]");
	Fake1_GEN_Dimuon_vertex_r->GetYaxis()->SetTitle("Events / 0.02 [cm]");

	Fake1_RECO_Dimuon_vertex_r->GetXaxis()->SetTitle("RECO Vertex Position R [cm]");
	Fake1_RECO_Dimuon_vertex_r->GetYaxis()->SetTitle("Events / 0.02 [cm]");

	Fake1_Dimuon_vertex_r_Residual->GetXaxis()->SetTitle("Vertex Position R Residual (GEN-RECO) [cm]");
	Fake1_Dimuon_vertex_r_Residual->GetYaxis()->SetTitle("Events / 0.02 [cm]");

	Fake1_Dimuon_vertex_r_Residual_vs_GEN->GetYaxis()->SetTitle("Vertex Position R Residual (GEN-RECO) [cm]");
	Fake1_Dimuon_vertex_r_Residual_vs_GEN->GetXaxis()->SetTitle("GEN Vertex Position R [cm]");

	Fake1_Dimuon_Lxy_Residual_vs_GEN_vertex_r->GetYaxis()->SetTitle("Dimuon L_{XY} Residual [cm]");
	Fake1_Dimuon_Lxy_Residual_vs_GEN_vertex_r->GetXaxis()->SetTitle("GEN Vertex Position R [cm]");

	Fake1_Dimuon_Lxy_Residual_vs_RECO_vertex_r->GetYaxis()->SetTitle("Dimuon L_{XY} Residual [cm]");
	Fake1_Dimuon_Lxy_Residual_vs_RECO_vertex_r->GetXaxis()->SetTitle("RECO Vertex Position R [cm]");

	Fake1_GEN_Dimuon_vertex_z->GetXaxis()->SetTitle("GEN Vertex Position Z [cm]");
	Fake1_GEN_Dimuon_vertex_z->GetYaxis()->SetTitle("Events / 0.02 [cm]");

	Fake1_RECO_Dimuon_vertex_z->GetXaxis()->SetTitle("RECO Vertex Position Z [cm]");
	Fake1_RECO_Dimuon_vertex_z->GetYaxis()->SetTitle("Events / 0.02 [cm]");

	Fake1_Dimuon_vertex_z_Residual->GetXaxis()->SetTitle("Vertex Position Z Residual (GEN-RECO) [cm]");
	Fake1_Dimuon_vertex_z_Residual->GetYaxis()->SetTitle("Events / 0.02 [cm]");

	Fake1_Dimuon_vertex_z_Residual_vs_GEN->GetYaxis()->SetTitle("Vertex Position Z Residual (GEN-RECO) [cm]");
	Fake1_Dimuon_vertex_z_Residual_vs_GEN->GetXaxis()->SetTitle("GEN Vertex Position Z [cm]");

	Fake1_Dimuon_Lxy_Residual_vs_GEN_vertex_z->GetYaxis()->SetTitle("Dimuon L_{XY} Residual [cm]");
	Fake1_Dimuon_Lxy_Residual_vs_GEN_vertex_z->GetXaxis()->SetTitle("GEN Vertex Position Z [cm]");

	Fake1_Dimuon_Lxy_Residual_vs_RECO_vertex_z->GetYaxis()->SetTitle("Dimuon L_{XY} Residual [cm]");
	Fake1_Dimuon_Lxy_Residual_vs_RECO_vertex_z->GetXaxis()->SetTitle("RECO Vertex Position Z [cm]");



	Fake2_GEN_Dimuon_vertex_r->GetXaxis()->SetTitle("GEN Vertex Position R [cm]");
	Fake2_GEN_Dimuon_vertex_r->GetYaxis()->SetTitle("Events / 0.02 [cm]");

	Fake2_RECO_Dimuon_vertex_r->GetXaxis()->SetTitle("RECO Vertex Position R [cm]");
	Fake2_RECO_Dimuon_vertex_r->GetYaxis()->SetTitle("Events / 0.02 [cm]");

	Fake2_Dimuon_vertex_r_Residual->GetXaxis()->SetTitle("Vertex Position R Residual (GEN-RECO) [cm]");
	Fake2_Dimuon_vertex_r_Residual->GetYaxis()->SetTitle("Events / 0.02 [cm]");

	Fake2_Dimuon_vertex_r_Residual_vs_GEN->GetYaxis()->SetTitle("Vertex Position R Residual (GEN-RECO) [cm]");
	Fake2_Dimuon_vertex_r_Residual_vs_GEN->GetXaxis()->SetTitle("GEN Vertex Position R [cm]");

	Fake2_Dimuon_Lxy_Residual_vs_GEN_vertex_r->GetYaxis()->SetTitle("Dimuon L_{XY} Residual [cm]");
	Fake2_Dimuon_Lxy_Residual_vs_GEN_vertex_r->GetXaxis()->SetTitle("GEN Vertex Position R [cm]");

	Fake2_Dimuon_Lxy_Residual_vs_RECO_vertex_r->GetYaxis()->SetTitle("Dimuon L_{XY} Residual [cm]");
	Fake2_Dimuon_Lxy_Residual_vs_RECO_vertex_r->GetXaxis()->SetTitle("RECO Vertex Position R [cm]");

	Fake2_GEN_Dimuon_vertex_z->GetXaxis()->SetTitle("GEN Vertex Position Z [cm]");
	Fake2_GEN_Dimuon_vertex_z->GetYaxis()->SetTitle("Events / 0.02 [cm]");

	Fake2_RECO_Dimuon_vertex_z->GetXaxis()->SetTitle("RECO Vertex Position Z [cm]");
	Fake2_RECO_Dimuon_vertex_z->GetYaxis()->SetTitle("Events / 0.02 [cm]");

	Fake2_Dimuon_vertex_z_Residual->GetXaxis()->SetTitle("Vertex Position Z Residual (GEN-RECO) [cm]");
	Fake2_Dimuon_vertex_z_Residual->GetYaxis()->SetTitle("Events / 0.02 [cm]");

	Fake2_Dimuon_vertex_z_Residual_vs_GEN->GetYaxis()->SetTitle("Vertex Position Z Residual (GEN-RECO) [cm]");
	Fake2_Dimuon_vertex_z_Residual_vs_GEN->GetXaxis()->SetTitle("GEN Vertex Position Z [cm]");

	Fake2_Dimuon_Lxy_Residual_vs_GEN_vertex_z->GetYaxis()->SetTitle("Dimuon L_{XY} Residual [cm]");
	Fake2_Dimuon_Lxy_Residual_vs_GEN_vertex_z->GetXaxis()->SetTitle("GEN Vertex Position Z [cm]");

	Fake2_Dimuon_Lxy_Residual_vs_RECO_vertex_z->GetYaxis()->SetTitle("Dimuon L_{XY} Residual [cm]");
	Fake2_Dimuon_Lxy_Residual_vs_RECO_vertex_z->GetXaxis()->SetTitle("RECO Vertex Position Z [cm]");


	//2D eta plots continued...
	Real_Reco_Eta_vs_VertexZ->GetXaxis()->SetTitle("#eta");
	Real_Reco_Eta_vs_VertexZ->GetYaxis()->SetTitle("RECO Vertex Position [cm]");

	Real_Reco_Eta_vs_VertexR->GetXaxis()->SetTitle("#eta");
	Real_Reco_Eta_vs_VertexR->GetYaxis()->SetTitle("RECO Vertex Position R [cm]");

	Real_Reco_Eta_vs_deltaR->GetXaxis()->SetTitle("#eta");
	Real_Reco_Eta_vs_deltaR->GetYaxis()->SetTitle("#Delta R Between RECO Dimuons");

	Real_Reco_Eta_vs_OpeningAngle->GetXaxis()->SetTitle("#eta");
	Real_Reco_Eta_vs_OpeningAngle->GetYaxis()->SetTitle("#Delta#phi Between RECO Dimuons [rads]");

	Fake_Reco_Eta_vs_VertexZ->GetXaxis()->SetTitle("#eta");
	Fake_Reco_Eta_vs_VertexZ->GetYaxis()->SetTitle("RECO Vertex Position [cm]");

	Fake_Reco_Eta_vs_VertexR->GetXaxis()->SetTitle("#eta");
	Fake_Reco_Eta_vs_VertexR->GetYaxis()->SetTitle("RECO Vertex Position R [cm]");

	Fake_Reco_Eta_vs_deltaR->GetXaxis()->SetTitle("#eta");
	Fake_Reco_Eta_vs_deltaR->GetYaxis()->SetTitle("#Delta R Between RECO Dimuons");

	Fake_Reco_Eta_vs_OpeningAngle->GetXaxis()->SetTitle("#eta");
	Fake_Reco_Eta_vs_OpeningAngle->GetYaxis()->SetTitle("#Delta#phi Between RECO Dimuons [rads]");

	Fake_dimuon1_Reco_Eta_vs_VertexZ->GetXaxis()->SetTitle("#eta");
	Fake_dimuon1_Reco_Eta_vs_VertexZ->GetYaxis()->SetTitle("RECO Vertex Position [cm]");

	Fake_dimuon1_Reco_Eta_vs_VertexR->GetXaxis()->SetTitle("#eta");
	Fake_dimuon1_Reco_Eta_vs_VertexR->GetYaxis()->SetTitle("RECO Vertex Position R [cm]");

	Fake_dimuon1_Reco_Eta_vs_deltaR->GetXaxis()->SetTitle("#eta");
	Fake_dimuon1_Reco_Eta_vs_deltaR->GetYaxis()->SetTitle("#Delta R Between RECO Dimuons");

	Fake_dimuon1_Reco_Eta_vs_OpeningAngle->GetXaxis()->SetTitle("#eta");
	Fake_dimuon1_Reco_Eta_vs_OpeningAngle->GetYaxis()->SetTitle("#Delta#phi Between RECO Dimuons [rads]");

	Fake_dimuon2_Reco_Eta_vs_VertexZ->GetXaxis()->SetTitle("#eta");
	Fake_dimuon2_Reco_Eta_vs_VertexZ->GetYaxis()->SetTitle("RECO Vertex Position [cm]");

	Fake_dimuon2_Reco_Eta_vs_VertexR->GetXaxis()->SetTitle("#eta");
	Fake_dimuon2_Reco_Eta_vs_VertexR->GetYaxis()->SetTitle("RECO Vertex Position R [cm]");

	Fake_dimuon2_Reco_Eta_vs_deltaR->GetXaxis()->SetTitle("#eta");
	Fake_dimuon2_Reco_Eta_vs_deltaR->GetYaxis()->SetTitle("#Delta R Between RECO Dimuons");

	Fake_dimuon2_Reco_Eta_vs_OpeningAngle->GetXaxis()->SetTitle("#eta");
	Fake_dimuon2_Reco_Eta_vs_OpeningAngle->GetYaxis()->SetTitle("#Delta#phi Between RECO Dimuons [rads]");

	Real_dimuon2_Reco_Eta_vs_VertexZ->GetXaxis()->SetTitle("#eta");
	Real_dimuon2_Reco_Eta_vs_VertexZ->GetYaxis()->SetTitle("RECO Vertex Position [cm]");

	Real_dimuon2_Reco_Eta_vs_VertexR->GetXaxis()->SetTitle("#eta");
	Real_dimuon2_Reco_Eta_vs_VertexR->GetYaxis()->SetTitle("RECO Vertex Position R [cm]");

	Real_dimuon2_Reco_Eta_vs_deltaR->GetXaxis()->SetTitle("#eta");
	Real_dimuon2_Reco_Eta_vs_deltaR->GetYaxis()->SetTitle("#Delta R Between RECO Dimuons");

	Real_dimuon2_Reco_Eta_vs_OpeningAngle->GetXaxis()->SetTitle("#eta");
	Real_dimuon2_Reco_Eta_vs_OpeningAngle->GetYaxis()->SetTitle("#Delta#phi Between RECO Dimuons [rads]");

	Real_dimuon1_Reco_Eta_vs_VertexZ->GetXaxis()->SetTitle("#eta");
	Real_dimuon1_Reco_Eta_vs_VertexZ->GetYaxis()->SetTitle("RECO Vertex Position [cm]");

	Real_dimuon1_Reco_Eta_vs_VertexR->GetXaxis()->SetTitle("#eta");
	Real_dimuon1_Reco_Eta_vs_VertexR->GetYaxis()->SetTitle("RECO Vertex Position R [cm]");

	Real_dimuon1_Reco_Eta_vs_deltaR->GetXaxis()->SetTitle("#eta");
	Real_dimuon1_Reco_Eta_vs_deltaR->GetYaxis()->SetTitle("#Delta R Between RECO Dimuons");

	Real_dimuon1_Reco_Eta_vs_OpeningAngle->GetXaxis()->SetTitle("#eta");
	Real_dimuon1_Reco_Eta_vs_OpeningAngle->GetYaxis()->SetTitle("#Delta#phi Between RECO Dimuons [rads]");

}

void printFakeStats(){
	cout << "" << endl;
	cout << "Fake Statistics" << endl;
	cout << "Mass (GeV)" << "\t" << "cT (mm)" << "\t" << "Num Events in Sample" << "\t" << "Num Fakes in Sample" << endl;
	for(int i = 0; i < FakeStatistics.size(); i++){
		cout << FakeStatistics[i][0] << "\t" << FakeStatistics[i][1] << "\t" << FakeStatistics[i][2] << "\t" << FakeStatistics[i][3] << endl;
	}
	cout << "" << endl;
}

void FakeInvestigation()
{
	cout << "Begin Fake Investigation" << endl;
	//only run over samples that have individual files (to make it easier to find them with Fireworks)
	//These cT's should be in order.
	//2.0 GeV
/*
	//{{{
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_100_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_300_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_2000_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_1000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_2000_cT_2000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	
	//}}}
*/
	//Sven's 0.25 GeV sample

	/*
	//{{{
	efficiency_hitrecovery("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f//");
	efficiency_hitrecovery("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_100_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_300_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	//}}}
	*/


	// Ben's 0.25 GeV sample

	//{{{

	//efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_1000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	//efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_2000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");


	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_1000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_2000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");

	//}}}


	//8.5 GeV sample
/*
	//{{{
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN_71_v1_v2/asdf/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_100_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_300_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_8500_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/226daabb7c2674ae5cd9e5d6ac58846b/");
	//}}}
*/

	//Jamal's 0.275 GeV sample
	/*
	//{{{
	efficiency_hitrecovery("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_100_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_100_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_300_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_300_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	efficiency_hitrecovery("/fdata/hepx/store/user/jrorie/DarkSUSY_mH_125_mGammaD_0275_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/f543ab33d972fd2ae528b8fb60581c3f/");
	//}}}
	*/

	//Alfredo's 0.3 GeV sample
	/*
	//{{{
	efficiency_hitrecovery("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
	efficiency_hitrecovery("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_010_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_010_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
	efficiency_hitrecovery("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_020_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_020_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
	efficiency_hitrecovery("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_050_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_050_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
	efficiency_hitrecovery("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_200_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_200_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
	efficiency_hitrecovery("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mGammaD_0300_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0300_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_PAT_ANA/d0f588fd6866a3a3094022dcf1ebdad3/");
	//}}}
	*/


	//Ben's 0.275 GeV sample
/*
	//{{{
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0275_cT_000_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_000_Evt_80k_PATANA_v4/151117_123308/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0275_cT_005_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_005_Evt_80k_PATANA_v4/151117_151528/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0275_cT_010_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_010_Evt_80k_PATANA_v4/151117_151628/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0275_cT_020_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_020_Evt_80k_PATANA_v4/151117_151724/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0275_cT_050_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_050_Evt_80k_PATANA_v4/151117_151824/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0275_cT_100_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_100_Evt_80k_PATANA_v4/151117_151935/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0275_cT_200_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_200_Evt_80k_PATANA_v4/151117_152115/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0275_cT_300_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_300_Evt_80k_PATANA_v4/151117_152230/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0275_cT_500_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0275_cT_500_Evt_80k_PATANA_v4/151117_152335/asdf/"); 
	//}}}
*/
	//Ben's 0.3 GeV sample
/*
	//{{{
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_000_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_000_Evt_80k_PATANA_v4/151117_152519/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_005_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_005_Evt_80k_PATANA_v4/151117_152556/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_010_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_010_Evt_80k_PATANA_v4/151117_152703/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_020_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_020_Evt_80k_PATANA_v4/151117_152813/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_050_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_050_Evt_80k_PATANA_v4/151117_153006/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_100_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_100_Evt_80k_PATANA_v4/151117_153036/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_200_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_200_Evt_80k_PATANA_v4/151117_153141/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_300_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_300_Evt_80k_PATANA_v4/151117_153244/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_500_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_500_Evt_80k_PATANA_v4/151117_153321/asdf/"); 
	//}}}
*/

	//0.4 GeV sample
/*
	//{{{
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0400_cT_000_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_000_Evt_80k_PATANA_v4/151117_153421/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0400_cT_005_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_005_Evt_80k_PATANA_v4/151117_153513/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0400_cT_010_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_010_Evt_80k_PATANA_v4/151117_153558/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0400_cT_020_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_020_Evt_80k_PATANA_v4/151117_153657/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0400_cT_050_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_050_Evt_80k_PATANA_v4/151117_153812/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0400_cT_100_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_100_Evt_80k_PATANA_v4/151117_153904/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0400_cT_200_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_200_Evt_80k_PATANA_v4/151117_153951/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0400_cT_300_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_300_Evt_80k_PATANA_v4/151117_154045/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0400_cT_500_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0400_cT_500_Evt_80k_PATANA_v4/151117_154251/asdf/"); 
	//}}}
*/

	//0.7 GeV sample
/*
	//{{{
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0700_cT_000_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_000_Evt_80k_PATANA_v4/151117_154344/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0700_cT_005_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_005_Evt_80k_PATANA_v4/151117_154442/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0700_cT_010_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_010_Evt_80k_PATANA_v4/151117_154535/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0700_cT_020_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_020_Evt_80k_PATANA_v4/151117_154632/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0700_cT_050_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_050_Evt_80k_PATANA_v4/151117_154716/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0700_cT_100_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_100_Evt_80k_PATANA_v4/151117_154749/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0700_cT_200_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_200_Evt_80k_PATANA_v4/151117_154834/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0700_cT_300_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_300_Evt_80k_PATANA_v4/151117_154929/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0700_cT_500_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0700_cT_500_Evt_80k_PATANA_v4/151117_155023/asdf/"); 
	//}}}
*/

	//1.0 GeV sample
/*
	//{{{
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1000_cT_000_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_000_Evt_80k_PATANA_v4/151117_155128/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1000_cT_005_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_005_Evt_80k_PATANA_v4/151117_155253/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1000_cT_010_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_010_Evt_80k_PATANA_v4/151117_155348/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1000_cT_020_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_020_Evt_80k_PATANA_v4/151117_155445/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1000_cT_050_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_050_Evt_80k_PATANA_v4/151117_155539/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1000_cT_100_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_100_Evt_80k_PATANA_v4/151117_155629/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1000_cT_200_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_200_Evt_80k_PATANA_v4/151117_155726/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1000_cT_300_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_300_Evt_80k_PATANA_v4/151117_155825/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1000_cT_500_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1000_cT_500_Evt_80k_PATANA_v4/151117_155914/asdf/"); 
	//}}}
*/
	// 1.5 GeV sample
/*
	//{{{
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1500_cT_000_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_000_Evt_80k_PATANA_v4/151117_160012/asdf/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1500_cT_005_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_005_Evt_80k_PATANA_v4/151117_160122/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1500_cT_010_Evt_79k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_010_Evt_79k_PATANA_v4/151117_160146/asdf/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1500_cT_020_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_020_Evt_80k_PATANA_v4/151117_160315/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1500_cT_100_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_100_Evt_80k_PATANA_v4/151117_160426/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1500_cT_200_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_200_Evt_80k_PATANA_v4/151117_160522/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1500_cT_300_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_300_Evt_80k_PATANA_v4/151117_160613/asdf/"); 
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_1500_cT_500_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_1500_cT_500_Evt_80k_PATANA_v4/151117_160729/asdf/");
	//}}}
*/
	//8 TeV samples
	/*
	//{{{

	//8 Tev
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_000_Evt_80k_8TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0250_cT_000_Evt_80k_PATANA_v4/151117_151201/0000/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_005_Evt_80k_8TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0250_cT_005_Evt_80k_PATANA_v4/151117_151250/0000/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_010_Evt_80k_8TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0250_cT_010_Evt_80k_PATANA_v4/151117_151325/0000/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_020_Evt_80k_8TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0250_cT_020_Evt_80k_PATANA_v4/151117_151402/0000/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_050_Evt_80k_8TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0250_cT_050_Evt_80k_PATANA_v4/151117_151430/0000/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_100_Evt_80k_8TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0250_cT_100_Evt_80k_PATANA_v4/151117_151508/0000/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_200_Evt_80k_8TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0250_cT_200_Evt_80k_PATANA_v4/151117_151538/0000/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_300_Evt_80k_8TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0250_cT_300_Evt_80k_PATANA_v4/151117_151622/0000/");
	efficiency_hitrecovery("/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0250_cT_500_Evt_80k_8TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0250_cT_500_Evt_80k_PATANA_v4/151117_151650/0000/");
	//}}}
	*/
	makePlot();
	makePlotsPretty();
	printFakeStats();
	BAM->Write();

}     
