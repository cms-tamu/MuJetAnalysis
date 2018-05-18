#include <iostream>
#include <iomanip>
using namespace std;
#include <algorithm>    // std::max
#include <stdlib.h>
#include <math.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH2F.h>
#include <TTree.h>
#include <TCut.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TChain.h>
#include <TChainElement.h>
#include "Helpers.h"
#include "TLatex.h"

Float_t counter[20][17];//samples; selections
Float_t TotEff[20][17];
Float_t TotEffErr[20][17];
Float_t RelEff[20][17];
Float_t RelEffErr[20][17];
Float_t epsvsalph1[20]={0.0};
Float_t Err[20]={0.0};
Float_t epsvsalph2[20]={0.0};
Float_t epsvsalph[20]={0.0};
Float_t epsvalp[20]={0.0};
Float_t epsvalp2[20]={0.0};


Int_t ev_regionA=0;
Int_t ev_regionB=0;
Int_t ev_regionB1=0;
Int_t ev_regionB2=0;
Int_t ev_regionB3=0;
Int_t ev_regionC=0;
Int_t ev_regionC1=0;
Int_t ev_regionC2=0;
Int_t ev_regionC3=0;
Int_t ev_regionD=0;
Int_t ev_regionD1=0;
Int_t ev_regionD2=0;
Int_t ev_regionD3=0;

void drawCMSPreliminaryWithLumi(double x, double y, double lumi){

  char tmp[100], tmp1[100];

  sprintf(tmp, "#intL = %d fb^{-1}, #sqrt{s} = 13 TeV", (int)(lumi));
  sprintf(tmp1, "CMS preliminary, #sqrt{s} = 13 TeV");
  // sprintf(tmp1, "CMS preliminary, #sqrt{s} = 7 TeV");


  TLatex *prelim = new TLatex;
  prelim->SetNDC();

  if (lumi>0) {
    prelim->DrawLatex(x, y, "CMS Preliminary");
    //prelim->DrawLatex(x, y, "CMS");
    prelim->DrawLatex(x, y-0.095, tmp);
  } 

  else prelim->DrawLatex(x, y, tmp1);
  //prelim->Draw();
}


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
}

int k = 0;
void efficiency(const std::vector<std::string>& dirNames)
{

  TString Run_period;


  bool verbose(true);

  //	TString dirname(fileName);
  TChain* chain = new TChain("dummy");
  TString ext("out_ana_");
  
  if(verbose) cout<<" dirNames  "<<dirNames[0]<<endl;
  
  
  //      bool alldata=false;
  bool alldata=true;
    //    bool mcsps=true;
      //      bool mcdps=true;
      bool mcdps=false;
    bool mcsps=false;
  //  bool test=true;
  bool test=false;
  if(alldata) Run_period = "all";
  if(mcsps) Run_period = "SPS";
  if(mcdps) Run_period = "DPS";
  if(test) Run_period = "test";
  if(!alldata && !mcsps && !mcdps && !test)  decodeFileNameManyData(dirNames, Run_period);
  
  TString fileName;
  fileName = "MuOnia dataset Run2016" + Run_period;

  cout<<" Sample   "<<fileName<<endl;
  // add files to the chain
  addfilesMany(chain, dirNames, ext);
  
  //Initialize Variables and counters
  // TFile *f[20]; //A root file is a suit of consecutive data records
  // TTree *t[20]; //comsists of a list of independent branches (Tbranch); one or multiple branches
  char nameFile[50]; //refers to a block of characters?

  Float_t diMuonC_Mass;//allows for effective use of architecture with wider formats
  Float_t diMuonF_Mass;

  Float_t diMuonC_FittedVtx_Lxy;
  Float_t diMuonF_FittedVtx_Lxy;

  Float_t diMuonC_FittedVtx_Rapidity;
  Float_t diMuonF_FittedVtx_Rapidity;
  
  Bool_t  is1SelMu3p5;
  Bool_t  is2SelMu3p5;
  Bool_t  is3SelMu3p5;
  Bool_t  is4SelMu3p5;

  Float_t selMu0_pT;
  Float_t selMu1_pT;
  Float_t selMu2_pT;
  Float_t selMu3_pT;

  Bool_t isVtxOK;
  Bool_t is2MuJets;

  Float_t massC;
  Float_t massF;

  Int_t event;

  Float_t selMu0_eta;
  Float_t selMu1_eta;
  Float_t selMu2_eta;
  Float_t selMu3_eta;

  Bool_t  is2DiMuons;

  Bool_t  is2DiMuonsFittedVtxOK;
  Bool_t  is2DiMuonsMassOK;

  Bool_t  is2DiMuonHLTFired;
  Float_t diMuonC_IsoTk_FittedVtx;
  Float_t diMuonF_IsoTk_FittedVtx;

  Float_t  diMuons_dz_FittedVtx;

  Int_t  diMuonC_m1_FittedVtx_hitpix_l3inc[2];
  Int_t  diMuonC_m2_FittedVtx_hitpix_l3inc[2];
  Int_t  diMuonF_m1_FittedVtx_hitpix_l3inc[2];
  Int_t  diMuonF_m2_FittedVtx_hitpix_l3inc[2];
  Int_t  nRecoMu;

  TH1F *evt_number = new TH1F("evt_number","",200,0.0,100000.0);


  TH1F *P_t_Mu0 = new TH1F("P_t_Mu0","",100,0.0,50.0);
  TH1F *P_t_Mu1 = new TH1F("P_t_Mu1","",100,0.0,50.0);
  TH1F *P_t_Mu2 = new TH1F("P_t_Mu2","",100,0.0,50.0);
  TH1F *P_t_Mu3 = new TH1F("P_t_Mu3","",100,0.0,50.0);

  TH1F *mass_C= new TH1F("mass_C","",100,0.0,5.0);
  TH1F *mass_F= new TH1F("mass_F","",100,0.0,5.0);

  TH1F *iso_C = new TH1F("iso_C","",100,0.0,12.0);
  TH1F *iso_F = new TH1F("iso_F","",100,0.0,12.0);

  TH1F *eta_Mu0 = new TH1F("eta_Mu0","",100,-2.5,2.5);
  TH1F *eta_Mu1 = new TH1F("eta_Mu1","",100,-2.5,2.5);
  TH1F *eta_Mu2 = new TH1F("eta_Mu2","",100,-2.5,2.5);
  TH1F *eta_Mu3 = new TH1F("eta_Mu3","",100,-2.5,2.5);


  TH1F *P_t_Mu0_aftTrig = new TH1F("P_t_Mu0_aftTrig","",100,0.0,50.0);
  TH1F *P_t_Mu1_aftTrig = new TH1F("P_t_Mu1_aftTrig","",100,0.0,50.0);
  TH1F *P_t_Mu2_aftTrig = new TH1F("P_t_Mu2_aftTrig","",100,0.0,50.0);
  TH1F *P_t_Mu3_aftTrig = new TH1F("P_t_Mu3_aftTrig","",100,0.0,50.0);

  TH1F *mass_C_aftTrig = new TH1F("mass_C_aftTrig","",100,0.0,5.0);
  TH1F *mass_F_aftTrig = new TH1F("mass_F_aftTrig","",100,0.0,5.0);

  TH1F *mass_C_aftTrig_cut = new TH1F("mass_C_aftTrig_cut","",100,2.8,3.3);
  TH1F *mass_F_aftTrig_cut = new TH1F("mass_F_aftTrig_cut","",100,2.8,3.3);

  TH1F *mass_C_aftTrig_cut_lxylt0p05 = new TH1F("mass_C_aftTrig_cut_lxylt0p05","",100,2.8,3.3);
  TH1F *mass_C_aftTrig_cut_lxylt0p2 = new TH1F("mass_C_aftTrig_cut_lxylt0p2","",100,2.8,3.3);
  TH1F *mass_C_aftTrig_cut_lxylt0p4 = new TH1F("mass_C_aftTrig_cut_lxylt0p4","",100,2.8,3.3);
  TH1F *mass_C_aftTrig_cut_lxylt1p0 = new TH1F("mass_C_aftTrig_cut_lxylt1p0","",100,2.8,3.3);


  TH1F *iso_C_aftTrig = new TH1F("iso_C_aftTrig","",100,0.0,12.0);
  TH1F *iso_F_aftTrig = new TH1F("iso_F_aftTrig","",100,0.0,12.0);

  TH1F *eta_Mu0_aftTrig = new TH1F("eta_Mu0_aftTrig","",100,-2.5,2.5);
  TH1F *eta_Mu1_aftTrig = new TH1F("eta_Mu1_aftTrig","",100,-2.5,2.5);
  TH1F *eta_Mu2_aftTrig = new TH1F("eta_Mu2_aftTrig","",100,-2.5,2.5);
  TH1F *eta_Mu3_aftTrig = new TH1F("eta_Mu3_aftTrig","",100,-2.5,2.5);

  TH1F *diMuons_dz = new TH1F("diMuons_dz","",100,-1.0,1.0);

  TH1F *diMuonC_Lxy_RegionA = new TH1F("diMuonC_Lxy_RegionA","",50,-0.2,1.0);
  TH1F *diMuonF_Lxy_RegionA = new TH1F("diMuonF_Lxy_RegionA","",50,-0.2,1.0);

  TH1F *diMuonC_Lxy_RegionC = new TH1F("diMuonC_Lxy_RegionC","",50,-0.2,1.0);
  TH1F *diMuonF_Lxy_RegionC = new TH1F("diMuonF_Lxy_RegionC","",50,-0.2,1.0);

  TH1F *diMuonC_Lxy_RegionC_invtdz = new TH1F("diMuonC_Lxy_RegionC_invtdz","",50,-0.2,1.0);
  TH1F *diMuonF_Lxy_RegionC_invtdz = new TH1F("diMuonF_Lxy_RegionC_invtdz","",50,-0.2,1.0);

  TH1F *diMuonC_Rapidity_RegionA = new TH1F("diMuonC_Rapidity_RegionA","",50,-0.3,3.0);
  TH1F *diMuonF_Rapidity_RegionA = new TH1F("diMuonF_Rapidity_RegionA","",50,-0.3,3.0);

  TH1F *diMuonC_Rapidity_RegionC = new TH1F("diMuonC_Rapidity_RegionC","",50,-0.3,3.0);
  TH1F *diMuonF_Rapidity_RegionC = new TH1F("diMuonF_Rapidity_RegionC","",50,-0.3,3.0);
  
  TH2F *Iso_dim1_vs_dim2 = new TH2F("Iso_dim1_vs_dim2","",100,0.0,12.0,100,0.0,12.0);
  TH2F *Iso_dim1_vs_dim2_aftmasscut = new TH2F("Iso_dim1_vs_dim2_aftmasscut","",100,0.0,12.0,100,0.0,12.0);
  TH2F *mass_dim1_vs_dim2 = new TH2F("mass_dim1_vs_dim2","",100,0.0,5.0,100,0.0,5.0);

  TObjArray *fileElements=chain->GetListOfFiles();
  TIter next(fileElements);
  TChainElement *chEl=0;

  //  k++;
  //cout << "p: " << p << endl;
  //if(p == 0 || p%3 == 0) setup(); //reset vectors for every 4th cT for tables.


  TFile *savehist = new TFile("plots_SD20180512/savehist_"+Run_period+".root","RECREATE");
  
  
  while ((chEl=(TChainElement*)next())) {  //loopforfiles
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

    int nentries;


    /*
    */
    t->SetBranchAddress("event",&event);
    t->SetBranchAddress("diMuonC_FittedVtx_m",&diMuonC_Mass);
    t->SetBranchAddress("diMuonF_FittedVtx_m",&diMuonF_Mass);
    t->SetBranchAddress("diMuonC_FittedVtx_Lxy",&diMuonC_FittedVtx_Lxy);
    t->SetBranchAddress("diMuonF_FittedVtx_Lxy",&diMuonF_FittedVtx_Lxy);
    t->SetBranchAddress("diMuonC_FittedVtx_Rapidity",&diMuonC_FittedVtx_Rapidity);
    t->SetBranchAddress("diMuonF_FittedVtx_Rapidity",&diMuonF_FittedVtx_Rapidity);
    t->SetBranchAddress("isVertexOK",&isVtxOK);
    t->SetBranchAddress("nRecoMu",&nRecoMu);
    t->SetBranchAddress("is1SelMu3p5",&is1SelMu3p5);
    t->SetBranchAddress("is2SelMu3p5",&is2SelMu3p5);
    t->SetBranchAddress("is3SelMu3p5",&is3SelMu3p5);
    t->SetBranchAddress("is4SelMu3p5",&is4SelMu3p5);
    t->SetBranchAddress("selMu0_pT",&selMu0_pT);
    t->SetBranchAddress("selMu1_pT",&selMu1_pT);
    t->SetBranchAddress("selMu2_pT",&selMu2_pT);
    t->SetBranchAddress("selMu3_pT",&selMu3_pT);
    t->SetBranchAddress("massC",&massC);
    t->SetBranchAddress("massF",&massF);
    t->SetBranchAddress("selMu0_eta",&selMu0_eta);
    t->SetBranchAddress("selMu1_eta",&selMu1_eta);
    t->SetBranchAddress("selMu2_eta",&selMu2_eta);
    t->SetBranchAddress("selMu3_eta",&selMu3_eta);
    t->SetBranchAddress("diMuonC_IsoTk_FittedVtx",&diMuonC_IsoTk_FittedVtx);
    t->SetBranchAddress("diMuonF_IsoTk_FittedVtx",&diMuonF_IsoTk_FittedVtx);
    t->SetBranchAddress("is2DiMuons",&is2DiMuons);
    t->SetBranchAddress("is2MuJets",&is2MuJets);
    t->SetBranchAddress("is2DiMuonsFittedVtxOK",&is2DiMuonsFittedVtxOK);
    t->SetBranchAddress("diMuons_dz_FittedVtx",&diMuons_dz_FittedVtx);
    t->SetBranchAddress("is2DiMuonsMassOK_FittedVtx",&is2DiMuonsMassOK);
    t->SetBranchAddress("isDiMuonHLTFired",&is2DiMuonHLTFired);
    t->SetBranchAddress("diMuonC_IsoTk_FittedVtx",&diMuonC_IsoTk_FittedVtx);
    t->SetBranchAddress("diMuonF_IsoTk_FittedVtx",&diMuonF_IsoTk_FittedVtx);
    t->SetBranchAddress("diMuonC_m1_FittedVtx_hitpix_l3inc",&diMuonC_m1_FittedVtx_hitpix_l3inc);
    t->SetBranchAddress("diMuonC_m2_FittedVtx_hitpix_l3inc",&diMuonC_m2_FittedVtx_hitpix_l3inc);
    t->SetBranchAddress("diMuonF_m1_FittedVtx_hitpix_l3inc",&diMuonF_m1_FittedVtx_hitpix_l3inc);
    t->SetBranchAddress("diMuonF_m2_FittedVtx_hitpix_l3inc",&diMuonF_m2_FittedVtx_hitpix_l3inc);

    t->GetEntry(0);

    t->SetBranchStatus("*",0);
    t->SetBranchStatus("event",1);
    t->SetBranchStatus("diMuonC_FittedVtx_m",1);
    t->SetBranchStatus("diMuonF_FittedVtx_m",1);
    t->SetBranchStatus("diMuonC_FittedVtx_Lxy",1);
    t->SetBranchStatus("diMuonF_FittedVtx_Lxy",1);
    t->SetBranchStatus("diMuonC_FittedVtx_Rapidity",1);
    t->SetBranchStatus("diMuonF_FittedVtx_Rapidity",1);
    t->SetBranchStatus("isVertexOK",1);
    t->SetBranchStatus("nRecoMu",1);
    t->SetBranchStatus("is1SelMu3p5",1);
    t->SetBranchStatus("is2SelMu3p5",1);
    t->SetBranchStatus("is3SelMu3p5",1);
    t->SetBranchStatus("is4SelMu3p5",1);
    t->SetBranchStatus("selMu0_pT",1);
    t->SetBranchStatus("selMu1_pT",1);
    t->SetBranchStatus("selMu2_pT",1);
    t->SetBranchStatus("selMu3_pT",1);
    t->SetBranchStatus("massC",1);
    t->SetBranchStatus("massF",1);
    t->SetBranchStatus("selMu0_eta",1);
    t->SetBranchStatus("selMu1_eta",1);
    t->SetBranchStatus("selMu2_eta",1);
    t->SetBranchStatus("selMu3_eta",1);
    t->SetBranchStatus("diMuonC_IsoTk_FittedVtx",1);
    t->SetBranchStatus("diMuonF_IsoTk_FittedVtx",1);
    t->SetBranchStatus("is2DiMuons",1);
    t->SetBranchStatus("is2MuJets",1);
    t->SetBranchStatus("is2DiMuonsFittedVtxOK",1);
    t->SetBranchStatus("diMuons_dz_FittedVtx",1);
    t->SetBranchStatus("is2DiMuonsMassOK_FittedVtx",1);
    t->SetBranchStatus("isDiMuonHLTFired",1);
    t->SetBranchStatus("diMuonC_IsoTk_FittedVtx",1);
    t->SetBranchStatus("diMuonF_IsoTk_FittedVtx",1);
    t->SetBranchStatus("diMuonC_m1_FittedVtx_hitpix_l3inc",1);
    t->SetBranchStatus("diMuonC_m2_FittedVtx_hitpix_l3inc",1);
    t->SetBranchStatus("diMuonF_m1_FittedVtx_hitpix_l3inc",1);
    t->SetBranchStatus("diMuonF_m2_FittedVtx_hitpix_l3inc",1);


    nentries = t->GetEntries(); //no of entries

    if (verbose) cout<<"  Events  "<<t->GetEntries()<<endl;

    for(int i = 0; i<nentries; i++){ //loop for number of events
      t->GetEntry(i);
      // cout << "Get event " << i << endl;
      counter[k][0]++;

      evt_number->Fill(event);

      if(nRecoMu>=4){
      	P_t_Mu0->Fill(selMu0_pT);
      	P_t_Mu1->Fill(selMu1_pT);
      	P_t_Mu2->Fill(selMu2_pT);
      	P_t_Mu3->Fill(selMu3_pT);
	
      	eta_Mu0->Fill(selMu0_eta);
      	eta_Mu1->Fill(selMu1_eta);
      	eta_Mu2->Fill(selMu2_eta);
      	eta_Mu3->Fill(selMu3_eta);
	
      	if(is2DiMuons){
      	  mass_C->Fill(massC);
      	  mass_F->Fill(massF);
      	  iso_C->Fill(diMuonC_IsoTk_FittedVtx);
      	  iso_F->Fill(diMuonF_IsoTk_FittedVtx);
      	}
      }
      

      // cout << "Control region selections " << i << endl;

      //  Selection for control region
      if(nRecoMu>=4 && is2DiMuonHLTFired && isVtxOK){
	P_t_Mu0_aftTrig->Fill(selMu0_pT);
	P_t_Mu1_aftTrig->Fill(selMu1_pT);
	P_t_Mu2_aftTrig->Fill(selMu2_pT);
	P_t_Mu3_aftTrig->Fill(selMu3_pT);

	eta_Mu0_aftTrig->Fill(selMu0_eta);
	eta_Mu1_aftTrig->Fill(selMu1_eta);
	eta_Mu2_aftTrig->Fill(selMu2_eta);
	eta_Mu3_aftTrig->Fill(selMu3_eta);

	if(is2DiMuons && is2DiMuonsFittedVtxOK){
	  diMuons_dz->Fill(diMuons_dz_FittedVtx);

	  if(fabs(diMuons_dz_FittedVtx)<0.1){
	    mass_C_aftTrig->Fill(massC);
	    mass_F_aftTrig->Fill(massF);
	    iso_C_aftTrig->Fill(diMuonC_IsoTk_FittedVtx);
	    iso_F_aftTrig->Fill(diMuonF_IsoTk_FittedVtx);
	    
	    Iso_dim1_vs_dim2->Fill(diMuonC_IsoTk_FittedVtx,diMuonF_IsoTk_FittedVtx);
	    mass_dim1_vs_dim2->Fill(massC,massF);

	    if(massC>2.8 && massC<3.3 && diMuonC_IsoTk_FittedVtx<2.0 && diMuonC_FittedVtx_Lxy<0.1) mass_C_aftTrig_cut->Fill(massC);
	    if(massF>2.8 && massF<3.3 && diMuonF_IsoTk_FittedVtx<2.0 && diMuonF_FittedVtx_Lxy<0.1) mass_F_aftTrig_cut->Fill(massF);


	    if(massC>2.8 && massC<3.3 && diMuonC_IsoTk_FittedVtx<2.0 && diMuonC_FittedVtx_Lxy<0.05) mass_C_aftTrig_cut_lxylt0p05->Fill(massC);
	    if(massC>2.8 && massC<3.3 && diMuonC_IsoTk_FittedVtx<2.0 && diMuonC_FittedVtx_Lxy>0.05 && diMuonC_FittedVtx_Lxy<0.2) mass_C_aftTrig_cut_lxylt0p2->Fill(massC);
	    if(massC>2.8 && massC<3.3 && diMuonC_IsoTk_FittedVtx<2.0 && diMuonC_FittedVtx_Lxy>0.2 && diMuonC_FittedVtx_Lxy<0.4) mass_C_aftTrig_cut_lxylt0p4->Fill(massC);
	    if(massC>2.8 && massC<3.3 && diMuonC_IsoTk_FittedVtx<2.0 && diMuonC_FittedVtx_Lxy>0.4)  mass_C_aftTrig_cut_lxylt1p0->Fill(massC);




	    
	    if( (massC>2.8 && massC<3.3) && (massF>2.8 && massF<3.3) ){


	      Iso_dim1_vs_dim2_aftmasscut->Fill(diMuonC_IsoTk_FittedVtx,diMuonF_IsoTk_FittedVtx);
	      
	      if(diMuonC_IsoTk_FittedVtx<2.0 && diMuonF_IsoTk_FittedVtx<2.0)  ev_regionA++;

	      if(diMuonC_IsoTk_FittedVtx<2.0 && (diMuonF_IsoTk_FittedVtx>2.0 && diMuonF_IsoTk_FittedVtx<12.0))  ev_regionB++;
	      if(diMuonC_IsoTk_FittedVtx<2.0 && (diMuonF_IsoTk_FittedVtx>2.0 && diMuonF_IsoTk_FittedVtx<10.0))  ev_regionB1++;
	      if(diMuonC_IsoTk_FittedVtx<2.0 && (diMuonF_IsoTk_FittedVtx>2.0 && diMuonF_IsoTk_FittedVtx<8.0))  ev_regionB2++;
	      if(diMuonC_IsoTk_FittedVtx<2.0 && (diMuonF_IsoTk_FittedVtx>2.0 && diMuonF_IsoTk_FittedVtx<6.0))  ev_regionB3++;

	      if((diMuonC_IsoTk_FittedVtx>2.0 && diMuonC_IsoTk_FittedVtx<12.0)  && (diMuonF_IsoTk_FittedVtx>2.0 && diMuonF_IsoTk_FittedVtx<12.0))  ev_regionC++;
	      if((diMuonC_IsoTk_FittedVtx>2.0 && diMuonC_IsoTk_FittedVtx<10.0)  && (diMuonF_IsoTk_FittedVtx>2.0 && diMuonF_IsoTk_FittedVtx<10.0))  ev_regionC1++;
	      if((diMuonC_IsoTk_FittedVtx>2.0 && diMuonC_IsoTk_FittedVtx<8.0)   && (diMuonF_IsoTk_FittedVtx>2.0 && diMuonF_IsoTk_FittedVtx<8.0))  ev_regionC2++;
	      if((diMuonC_IsoTk_FittedVtx>2.0 && diMuonC_IsoTk_FittedVtx<6.0)   && (diMuonF_IsoTk_FittedVtx>2.0 && diMuonF_IsoTk_FittedVtx<6.0))  ev_regionC3++;

	      if((diMuonC_IsoTk_FittedVtx>2.0 && diMuonC_IsoTk_FittedVtx<12.0) && diMuonF_IsoTk_FittedVtx<2.0)  ev_regionD++;
	      if((diMuonC_IsoTk_FittedVtx>2.0 && diMuonC_IsoTk_FittedVtx<10.0) && diMuonF_IsoTk_FittedVtx<2.0)  ev_regionD1++;
	      if((diMuonC_IsoTk_FittedVtx>2.0 && diMuonC_IsoTk_FittedVtx<8.0)  && diMuonF_IsoTk_FittedVtx<2.0)  ev_regionD2++;
	      if((diMuonC_IsoTk_FittedVtx>2.0 && diMuonC_IsoTk_FittedVtx<6.0)  && diMuonF_IsoTk_FittedVtx<2.0)  ev_regionD3++;

	      
	    if(diMuonC_IsoTk_FittedVtx<2.0 && diMuonF_IsoTk_FittedVtx<2.0){
	      diMuonC_Lxy_RegionA->Fill(diMuonC_FittedVtx_Lxy);
	      diMuonF_Lxy_RegionA->Fill(diMuonF_FittedVtx_Lxy);
	      
	      diMuonC_Rapidity_RegionA->Fill(diMuonC_FittedVtx_Rapidity);
	      diMuonF_Rapidity_RegionA->Fill(diMuonF_FittedVtx_Rapidity);
	    }
	    if(diMuonC_IsoTk_FittedVtx>2.0 && diMuonF_IsoTk_FittedVtx>2.0){
	      diMuonC_Lxy_RegionC->Fill(diMuonC_FittedVtx_Lxy);
	      diMuonF_Lxy_RegionC->Fill(diMuonF_FittedVtx_Lxy);
	      
	      diMuonC_Rapidity_RegionC->Fill(diMuonC_FittedVtx_Rapidity);
	      diMuonF_Rapidity_RegionC->Fill(diMuonF_FittedVtx_Rapidity);
	    }
	  }
	  }
	  if(fabs(diMuons_dz_FittedVtx)>0.1){
	    if( (massC>2.8 && massC<3.3) && (massF>2.8 && massF<3.3) ){
	      if(diMuonC_IsoTk_FittedVtx>2.0 && diMuonF_IsoTk_FittedVtx>2.0){
		diMuonC_Lxy_RegionC_invtdz->Fill(diMuonC_FittedVtx_Lxy);
		diMuonF_Lxy_RegionC_invtdz->Fill(diMuonF_FittedVtx_Lxy);
	      }
	    }	    
	  }
	  
	}
      }
      
      
      // Selection for default analysis
      if(is1SelMu3p5)counter[k][6]++;
      if(is2SelMu3p5)counter[k][7]++;
      if(is3SelMu3p5)counter[k][8]++;
      if(is4SelMu3p5 && selMu0_pT>17.0 && fabs(selMu0_eta)<0.9&& selMu3_pT>8.0){
      //	if(is4SelMu3p5){
	  counter[k][9]++;
	  if(is2DiMuons){
	    counter[k][10]++;
	    if(is2DiMuonsFittedVtxOK){
	      counter[k][11]++;
	      if( fabs(diMuons_dz_FittedVtx)<0.1){
		counter[k][12]++;
		if(is2DiMuonsMassOK){
		  counter[k][13]++;
		  if(is2DiMuonHLTFired){
		    counter[k][14]++;
		    if(diMuonC_IsoTk_FittedVtx<2.0 && diMuonF_IsoTk_FittedVtx<2.0){
		      counter[k][15]++;
		      if( (diMuonC_m1_FittedVtx_hitpix_l3inc[0]==1||diMuonC_m2_FittedVtx_hitpix_l3inc[1]==1) &&
			  (diMuonF_m1_FittedVtx_hitpix_l3inc[0]==1||diMuonF_m2_FittedVtx_hitpix_l3inc[1]==1)) counter[k][16]++;
		      
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
      myfile->Close();
    }
    
    // 8)Fill Histogram with event number
  // hdimCm->Fill(diMuonC_Mass,diMuonF_Mass);
  cout<<"  Here is where the plotting starts  "<<endl;
  cout<<"  Here is where the plotting starts  "<<endl;

  //  Run_period="jpsi_SPS";

  savehist->cd();
  
  TText *t2;
  if(alldata){t2 = new TText(0.18,0.85,"CMS");}
  else{  t2 = new TText(0.18,0.85, "CMS Simulation");}
  t2->SetNDC();
  
  
  TLatex *t1 = new TLatex;
  t1->SetNDC();
  t1->SetTextSize(0.035);



  TCanvas *cevt = new TCanvas("cevt","cevt");
  evt_number->Draw();
  cevt->SaveAs("plots_SD20180512/event_"+Run_period+".png","recreate");


  //    TCanvas *cc = new TCanvas("cc","cc");
  //   mass_C->Draw();
  //   cc->SaveAs("plots_SD20180512/massC_"+Run_period+".png","recreate");

  //   TCanvas *cf = new TCanvas("cf","cf");
  //   mass_F->Draw();
  //   cf->SaveAs("plots_SD20180512/massF_"+Run_period+".png","recreate");

  //   TCanvas *e = new TCanvas("e","e");
  //  eta_Mu0->Draw();
  //  e->SaveAs("plots_SD20180512/e0_"+Run_period+".png","recreate");

  //  TCanvas *e1 = new TCanvas("e1","e1");
  //  eta_Mu0->Draw();
  //  e1->SaveAs("plots_SD20180512/e1_"+Run_period+".png","recreate");

  //  TCanvas *e2 = new TCanvas("e2","e2");
  // eta_Mu0->Draw();
  // e2->SaveAs("plots_SD20180512/e2_"+Run_period+".png","recreate");

  // TCanvas *e3 = new TCanvas("e3","e3");
  // eta_Mu0->Draw();
  // e3->SaveAs("plots_SD20180512/e3_"+Run_period+".png","recreate");

  // TCanvas *isoC = new TCanvas("isoC","isoC");
  // iso_C->Draw();
  // isoC->SaveAs("plots_SD20180512/isoC_"+Run_period+".png","recreate");

  // TCanvas *isoF = new TCanvas("isoF","isoF");
  // iso_C->Draw();
  // isoF->SaveAs("plots_SD20180512/isoF_"+Run_period+".png","recreate");

  // TCanvas *c = new TCanvas("c","c");
  //  P_t_Mu0->Draw();
  //  c->SaveAs("plots_SD20180512/pt_mu0_"+Run_period+".png","recreate");

  //  TCanvas *c1 = new TCanvas("c1","c1");
  //  P_t_Mu1->Draw();
  //  c1->SaveAs("plots_SD20180512/pt_mu1_"+Run_period+".png","recreate");

  //  TCanvas *c2 = new TCanvas("c2","c2");
  //  P_t_Mu2->Draw();
  //  c2->SaveAs("plots_SD20180512/pt_mu2_"+Run_period+".png","recreate");

  //  TCanvas *c3 = new TCanvas("c3","c3");
  //  P_t_Mu3->Draw();
  //  c3->SaveAs("plots_SD20180512/pt_mu3_"+Run_period+".png","recreate");


  TCanvas *tesa = new TCanvas("tesa","tesa");
  diMuons_dz->Write();
  diMuons_dz->GetXaxis()->SetTitle("di-#mu_{1z}  - di-#mu_{2z} [cm]");
  diMuons_dz->Draw();
  tesa->SaveAs("plots_SD20180512/diMuons_dz_"+Run_period+".png","recreate");
  tesa->SaveAs("plots_SD20180512/diMuons_dz_"+Run_period+".pdf","recreate");

  mass_C_aftTrig_cut_lxylt0p05->Write();
  mass_C_aftTrig_cut_lxylt0p2->Write(); 
  mass_C_aftTrig_cut_lxylt0p4->Write(); 
  mass_C_aftTrig_cut_lxylt1p0->Write();
  
  TCanvas *tccc = new TCanvas("tccc","tccc");
  mass_C_aftTrig_cut->Write();
  mass_C_aftTrig_cut->GetXaxis()->SetTitle("m_{di-#mu_{1}} [GeV]");
  mass_C_aftTrig_cut->Draw();
  tccc->SaveAs("plots_SD20180512/massC_aftTrig_cut"+Run_period+".png","recreate");
  tccc->SaveAs("plots_SD20180512/massC_aftTrig_cut"+Run_period+".pdf","recreate");

  TCanvas *tcc = new TCanvas("tcc","tcc");
  mass_C_aftTrig->Write();
  mass_C_aftTrig->GetXaxis()->SetTitle("m_{di-#mu_{1}} [GeV]");
  mass_C_aftTrig->Draw();
  tcc->SaveAs("plots_SD20180512/massC_aftTrig_"+Run_period+".png","recreate");
  tcc->SaveAs("plots_SD20180512/massC_aftTrig_"+Run_period+".pdf","recreate");

  TCanvas *tcf = new TCanvas("tcf","tcf");
  mass_F_aftTrig->Write();
  mass_F_aftTrig->GetXaxis()->SetTitle("m_{di-#mu_{2}} [GeV]");
  mass_F_aftTrig->Draw();
  tcf->SaveAs("plots_SD20180512/massF_aftTrig_"+Run_period+".png","recreate");
  tcf->SaveAs("plots_SD20180512/massF_aftTrig_"+Run_period+".pdf","recreate");

  TCanvas *te = new TCanvas("te","te");
  eta_Mu0_aftTrig->Write();
  eta_Mu0_aftTrig->GetXaxis()->SetTitle("#eta_{#mu_{1}}");
  eta_Mu0_aftTrig->Draw();
  te->SaveAs("plots_SD20180512/eta0_aftTrig_"+Run_period+".png","recreate");
  te->SaveAs("plots_SD20180512/eta0_aftTrig_"+Run_period+".pdf","recreate");

  TCanvas *te1 = new TCanvas("te1","te1");
  eta_Mu1_aftTrig->GetXaxis()->SetTitle("#eta_{#mu_{2}}");
  eta_Mu1_aftTrig->Draw();
  te1->SaveAs("plots_SD20180512/eta1_aftTrig_"+Run_period+".png","recreate");
  te1->SaveAs("plots_SD20180512/eta1_aftTrig_"+Run_period+".pdf","recreate");

  TCanvas *te2 = new TCanvas("te2","te2");
  eta_Mu2_aftTrig->GetXaxis()->SetTitle("#eta_{#mu_{3}}");
  eta_Mu2_aftTrig->Draw();
  te2->SaveAs("plots_SD20180512/eta2_aftTrig_"+Run_period+".png","recreate");
  te2->SaveAs("plots_SD20180512/eta2_aftTrig_"+Run_period+".pdf","recreate");

  TCanvas *te3 = new TCanvas("te3","te3");
  eta_Mu3_aftTrig->GetXaxis()->SetTitle("#eta_{#mu_{4}}");
  eta_Mu3_aftTrig->Draw();
  te3->SaveAs("plots_SD20180512/eta3_aftTrig_"+Run_period+".png","recreate");
  te3->SaveAs("plots_SD20180512/eta3_aftTrig_"+Run_period+".pdf","recreate");

  TCanvas *tisoC = new TCanvas("tisoC","tisoC");
  iso_C_aftTrig->GetXaxis()->SetTitle("Iso_{di-#mu_{1}} [GeV]");
  iso_C_aftTrig->Draw();
  tisoC->SaveAs("plots_SD20180512/isoC_aftTrig_"+Run_period+".png","recreate");
  tisoC->SaveAs("plots_SD20180512/isoC_aftTrig_"+Run_period+".pdf","recreate");

  TCanvas *tisoF = new TCanvas("tisoF","tisoF");
  iso_F_aftTrig->GetXaxis()->SetTitle("Iso_{di-#mu_{2}} [GeV]");
  iso_F_aftTrig->Draw();
  tisoF->SaveAs("plots_SD20180512/isoF_aftTrig_"+Run_period+".png","recreate");
  tisoF->SaveAs("plots_SD20180512/isoF_aftTrig_"+Run_period+".pdf","recreate");

  TCanvas *tc = new TCanvas("tc","tc");
  P_t_Mu0_aftTrig->GetXaxis()->SetTitle("Pt_{#mu_{0}} [GeV]");
  P_t_Mu0_aftTrig->Draw();
  tc->SaveAs("plots_SD20180512/pt_mu0_aftTrig_"+Run_period+".png","recreate");
  tc->SaveAs("plots_SD20180512/pt_mu0_aftTrig_"+Run_period+".pdf","recreate");

  TCanvas *tc1 = new TCanvas("tc1","tc1");
  P_t_Mu1_aftTrig->GetXaxis()->SetTitle("Pt_{#mu_{1}} [GeV]");
  P_t_Mu1_aftTrig->Draw();
  tc1->SaveAs("plots_SD20180512/pt_mu1_aftTrig_"+Run_period+".png","recreate");
  tc1->SaveAs("plots_SD20180512/pt_mu1_aftTrig_"+Run_period+".pdf","recreate");

  TCanvas *tc2 = new TCanvas("tc2","tc2");
  P_t_Mu2_aftTrig->GetXaxis()->SetTitle("Pt_{#mu_{2}} [GeV]");
  P_t_Mu2_aftTrig->Draw();
  tc2->SaveAs("plots_SD20180512/pt_mu2_aftTrig_"+Run_period+".png","recreate");
  tc2->SaveAs("plots_SD20180512/pt_mu2_aftTrig_"+Run_period+".pdf","recreate");

  TCanvas *tc3 = new TCanvas("tc3","tc3");
  P_t_Mu3_aftTrig->GetXaxis()->SetTitle("Pt_{#mu_{3}} [GeV]");
  P_t_Mu3_aftTrig->Draw();
  tc3->SaveAs("plots_SD20180512/pt_mu3_aftTrig_"+Run_period+".png","recreate");
  tc3->SaveAs("plots_SD20180512/pt_mu3_aftTrig_"+Run_period+".pdf","recreate");


  // TLatex *prelim = new TLatex;
  // prelim->SetNDC();
  // prelim->DrawLatex(0.575, 0.85, "CMS Preliminary");

  TCanvas *c2d = new TCanvas("c2d","c2d");
  c2d->SetRightMargin(0.18);
  Iso_dim1_vs_dim2->GetXaxis()->SetTitle("Iso di-#mu_{1} [GeV]");
  Iso_dim1_vs_dim2->GetYaxis()->SetTitle("Iso di-#mu_{2} [GeV]");
  Iso_dim1_vs_dim2->Draw("COLORZ");
  t2->Draw("same");
  if(alldata) t1->DrawLatex(0.6,0.95,"35.9 fb^{-1} (13 TeV)");  

  c2d->SaveAs("plots_SD20180512/Iso_dim1_vs_dim2_"+Run_period+".png","recreate");
  c2d->SaveAs("plots_SD20180512/Iso_dim1_vs_dim2_"+Run_period+".pdf","recreate");
  c2d->SaveAs("plots_SD20180512/Iso_dim1_vs_dim2_"+Run_period+".C","recreate");

  //  TCanvas *c2d1 = new TCanvas("c2d1","c2d1",900,700);
  TCanvas *c2d1 = new TCanvas("c2d1","c2d1");
  c2d1->SetRightMargin(0.18);
  mass_dim1_vs_dim2->GetXaxis()->SetTitle("mass di-#mu_{1} [GeV]");
  mass_dim1_vs_dim2->GetYaxis()->SetTitle("mass di-#mu_{2} [GeV]");
  mass_dim1_vs_dim2->Write();
  mass_dim1_vs_dim2->Draw("COLORZ");
  t2->Draw("same");
  if(alldata) t1->DrawLatex(0.6,0.95,"35.9 fb^{-1} (13 TeV)");
  c2d1->SaveAs("plots_SD20180512/mass_dim1_vs_dim2_"+Run_period+".png","recreate");
  c2d1->SaveAs("plots_SD20180512/mass_dim1_vs_dim2_"+Run_period+".pdf","recreate");
  c2d1->SaveAs("plots_SD20180512/mass_dim1_vs_dim2_"+Run_period+".C","recreate");

  TCanvas *c222 = new TCanvas("c222","c222");
  c222->SetRightMargin(0.18);
  Iso_dim1_vs_dim2_aftmasscut->GetXaxis()->SetTitle("Iso di-#mu_{1} [GeV]");
  Iso_dim1_vs_dim2_aftmasscut->GetYaxis()->SetTitle("Iso di-#mu_{2} [GeV]");
  Iso_dim1_vs_dim2_aftmasscut->Write();
  Iso_dim1_vs_dim2_aftmasscut->Draw("COLORZ");
  t2->Draw("same");
  if(alldata) t1->DrawLatex(0.6,0.95,"35.9 fb^{-1} (13 TeV)");
  c222->SaveAs("plots_SD20180512/Iso_dim1_vs_dim2_aftmasscut"+Run_period+".png","recreate");
  c222->SaveAs("plots_SD20180512/Iso_dim1_vs_dim2_aftmasscut"+Run_period+".pdf","recreate");
  c222->SaveAs("plots_SD20180512/Iso_dim1_vs_dim2_aftmasscut"+Run_period+".C","recreate");

  diMuonC_Lxy_RegionA->Write();
  diMuonF_Lxy_RegionA->Write();
  diMuonC_Lxy_RegionC->Write();
  diMuonF_Lxy_RegionC->Write();
  diMuonC_Lxy_RegionC_invtdz->Write();
  diMuonF_Lxy_RegionC_invtdz->Write();

  diMuonC_Rapidity_RegionA->Write();
  diMuonF_Rapidity_RegionA->Write();
  diMuonC_Rapidity_RegionC->Write();
  diMuonF_Rapidity_RegionC->Write();

  TCanvas *c2221 = new TCanvas("c2221","c2221");
  diMuonC_Lxy_RegionA->GetXaxis()->SetTitle("Lxy_{di-#mu_{1}} [cm]");
  diMuonC_Lxy_RegionA->Draw();
  t2->Draw("same");
  if(alldata) t1->DrawLatex(0.6,0.95,"35.9 fb^{-1} (13 TeV)");
  c2221->SaveAs("plots_SD20180512/diMuonC_Lxy_regionA_"+Run_period+".png","recreate");
  c2221->SaveAs("plots_SD20180512/diMuonC_Lxy_regionA_"+Run_period+".pdf","recreate");
  c2221->SaveAs("plots_SD20180512/diMuonC_Lxy_regionA_"+Run_period+".C","recreate");

  TCanvas *c2222 = new TCanvas("c2222","c2222");
  diMuonF_Lxy_RegionA->GetXaxis()->SetTitle("Lxy_{di-#mu_{2}} [cm]");
  diMuonF_Lxy_RegionA->Draw();
  t2->Draw("same");
  if(alldata) t1->DrawLatex(0.6,0.95,"35.9 fb^{-1} (13 TeV)");
  c2222->SaveAs("plots_SD20180512/diMuonF_Lxy_regionA_"+Run_period+".png","recreate");
  c2222->SaveAs("plots_SD20180512/diMuonF_Lxy_regionA_"+Run_period+".pdf","recreate");
  c2222->SaveAs("plots_SD20180512/diMuonF_Lxy_regionA_"+Run_period+".C","recreate");

  TCanvas *c2223 = new TCanvas("c2223","c2223");
  diMuonC_Lxy_RegionC->GetXaxis()->SetTitle("Lxy_{di-#mu_{1}} [cm]");
  diMuonC_Lxy_RegionC->Draw();
  t2->Draw("same");
  if(alldata) t1->DrawLatex(0.6,0.95,"35.9 fb^{-1} (13 TeV)");
  c2223->SaveAs("plots_SD20180512/diMuonC_Lxy_regionC_"+Run_period+".png","recreate");
  c2223->SaveAs("plots_SD20180512/diMuonC_Lxy_regionC_"+Run_period+".pdf","recreate");
  c2223->SaveAs("plots_SD20180512/diMuonC_Lxy_regionC_"+Run_period+".C","recreate");

  TCanvas *c2224 = new TCanvas("c2224","c2224");
  diMuonF_Lxy_RegionC->GetXaxis()->SetTitle("Lxy_{di-#mu_{2}} [cm]");
  diMuonF_Lxy_RegionC->Draw();
  t2->Draw("same");
  if(alldata) t1->DrawLatex(0.6,0.95,"35.9 fb^{-1} (13 TeV)");
  c2224->SaveAs("plots_SD20180512/diMuonF_Lxy_regionC_"+Run_period+".png","recreate");
  c2224->SaveAs("plots_SD20180512/diMuonF_Lxy_regionC_"+Run_period+".pdf","recreate");
  c2224->SaveAs("plots_SD20180512/diMuonF_Lxy_regionC_"+Run_period+".C","recreate");

  TCanvas *c22231 = new TCanvas("c22231","c22231");
  diMuonC_Lxy_RegionC_invtdz->Draw();
  c22231->SaveAs("plots_SD20180512/diMuonC_Lxy_regionC_invtdz_"+Run_period+".png","recreate");
  c22231->SaveAs("plots_SD20180512/diMuonC_Lxy_regionC_invtdz_"+Run_period+".pdf","recreate");

  TCanvas *c22242 = new TCanvas("c22242","c22242");
  diMuonF_Lxy_RegionC_invtdz->Draw();
  c22242->SaveAs("plots_SD20180512/diMuonF_Lxy_regionF_invtdz_"+Run_period+".png","recreate");
  c22242->SaveAs("plots_SD20180512/diMuonF_Lxy_regionF_invtdz_"+Run_period+".pdf","recreate");



  TCanvas *c22221 = new TCanvas("c22221","c22221");
  diMuonC_Rapidity_RegionA->GetXaxis()->SetTitle("Rapidity_{di-#mu_{1}}");
  diMuonC_Rapidity_RegionA->Draw();
  t2->Draw("same");
  if(alldata) t1->DrawLatex(0.6,0.95,"35.9 fb^{-1} (13 TeV)");
  c22221->SaveAs("plots_SD20180512/diMuonC_Rapidity_regionA_"+Run_period+".png","recreate");
  c22221->SaveAs("plots_SD20180512/diMuonC_Rapidity_regionA_"+Run_period+".pdf","recreate");
  c22221->SaveAs("plots_SD20180512/diMuonC_Rapidity_regionA_"+Run_period+".C","recreate");

  TCanvas *c22222 = new TCanvas("c22222","c22222");
  diMuonF_Rapidity_RegionA->GetXaxis()->SetTitle("Rapidity_{di-#mu_{2}}");
  diMuonF_Rapidity_RegionA->Draw();
  t2->Draw("same");
  if(alldata) t1->DrawLatex(0.6,0.95,"35.9 fb^{-1} (13 TeV)");
  c22222->SaveAs("plots_SD20180512/diMuonF_Rapidity_regionA_"+Run_period+".png","recreate");
  c22222->SaveAs("plots_SD20180512/diMuonF_Rapidity_regionA_"+Run_period+".pdf","recreate");
  c22222->SaveAs("plots_SD20180512/diMuonF_Rapidity_regionA_"+Run_period+".C","recreate");

  TCanvas *c22223 = new TCanvas("c22223","c22223");
  diMuonC_Rapidity_RegionC->GetXaxis()->SetTitle("Rapidity_{di-#mu_{1}}");
  diMuonC_Rapidity_RegionC->Draw();
  t2->Draw("same");
  if(alldata) t1->DrawLatex(0.6,0.95,"35.9 fb^{-1} (13 TeV)");
  c22223->SaveAs("plots_SD20180512/diMuonC_Rapidity_regionC_"+Run_period+".png","recreate");
  c22223->SaveAs("plots_SD20180512/diMuonC_Rapidity_regionC_"+Run_period+".pdf","recreate");
  c22223->SaveAs("plots_SD20180512/diMuonC_Rapidity_regionC_"+Run_period+".C","recreate");

  TCanvas *c22224 = new TCanvas("c22224","c22224");
  diMuonF_Rapidity_RegionC->GetXaxis()->SetTitle("Rapidity_{di-#mu_{2}}");
  diMuonF_Rapidity_RegionC->Draw();
  t2->Draw("same");
  if(alldata) t1->DrawLatex(0.6,0.95,"35.9 fb^{-1} (13 TeV)");
  c22224->SaveAs("plots_SD20180512/diMuonF_Rapidity_regionC_"+Run_period+".png","recreate");
  c22224->SaveAs("plots_SD20180512/diMuonF_Rapidity_regionC_"+Run_period+".pdf","recreate");
  c22224->SaveAs("plots_SD20180512/diMuonF_Rapidity_regionC_"+Run_period+".C","recreate");
  
  delete savehist;
  
  RelEff[k][0] = counter[k][0]/(counter[k][0]*1.0);
  for(int m=6;m<17;m++){
    TotEff[k][m]= counter[k][m]/(counter[k][0]*1.0);
    TotEffErr[k][m]= sqrt( (TotEff[k][m]*(1-TotEff[k][m]))/(counter[k][0]*1.0));
    if(m>0){
      if(m==6){
  	RelEff[k][m]= counter[k][m]/(counter[k][0]*1.0);
  	RelEffErr[k][m]= sqrt( (RelEff[k][m]*(1-RelEff[k][m]))/(counter[k][0]*1.0));
      }
      else{
  	RelEff[k][m]=  counter[k][m]/(counter[k][m-1]*1.0);
  	RelEffErr[k][m]= sqrt( (RelEff[k][m]*(1-RelEff[k][m]))/(counter[k][m-1]*1.0));
      }
    }
  }


  cout<<"        "<<endl;
  cout<<"begin{landscape}"<<endl;
  cout<<"centering"<<endl;
  cout<<"begin{tabular}{ c| c | c | c | c | c }"<<endl;
  
  cout<<" Selection   "<<" \\# Events   "<<"   Total Efficiency  "<<" Relative Efficiency   "<<" TotalEffError   "<<" RelEffError "<<" hline "<<endl;
  
  cout<<" No cut      &   "<<left<< setw(7)<< counter[k][0]<<"     &   "<<fixed<< std::setprecision(3)<< TotEff[k][0]<<"         &     "<< RelEff[k][0]<<"           &   "<<left<< setw(7)<< TotEffErr[k][0]<<"      &   "<< RelEffErr[k][0]<<" hline "<<endl;
  
  cout<<" is1SelMu3p5   &    "<<left<< setw(7)<< counter[k][6]<<"  &    "<<left<< setw(7)<< TotEff[k][6] <<setw(10)<<"   &    "<<left<< setw(7)<<  RelEff[k][6]<<"  &    "<<left<< setw(7)<<  TotEffErr[k][6]<<" &  " <<  RelEffErr[k][6]<<" hline "<<endl;
  cout<< setprecision(3);
  cout<<" is2SelMu3p5    &    "<< counter[k][7]<<"  &    "<< TotEff[k][7] <<setw(10)<<"   &   "<< RelEff[k][7]<<"   &   "<< TotEffErr[k][7]<<"  & "<< RelEffErr[k][7]<<" hline "<<endl;
  cout<<" is3SelMu3p5    &    "<< counter[k][8]<<"  &    "<< TotEff[k][8]<<"   &    "<< RelEff[k][8]<<"   &   "<< TotEffErr[k][8]<<" &  "<< RelEffErr[k][8]<<" hline "<<endl;
  cout<<" is4SelMu3p5    &    "<< counter[k][9]<<"  &    "<< TotEff[k][9]<<"   &    "<< RelEff[k][9]<<"   &   "<< TotEffErr[k][9]<<" &  "<< RelEffErr[k][9]<<" hline "<<endl;
  cout<<"                                                                        "<<" hline "<<endl;
  cout<<" is2dimuon            &  "<< counter[k][10]<<"  &    "<< TotEff[k][10]<<" &    "<< RelEff[k][10]<<"  &   "<<fixed<<std::setprecision(4) << TotEffErr[k][10]<<" &  "<< RelEffErr[k][10]<<" hline "<<endl;
  
  cout<<" is2DiMuonsFittedVtx  &  "<< counter[k][11]<<"  &    "<< TotEff[k][11]<<" &     "<< RelEff[k][11]<<" &   "<<fixed<<std::setprecision(4) << TotEffErr[k][11]<<" &  "<<fixed<<std::setprecision(3) << RelEffErr[k][11]<<" hline "<<endl;
  cout<<" is2DiMuonsFittedDz   &  "<< counter[k][12]<<"  &    "<< TotEff[k][12]<<" &     "<< RelEff[k][12]<<" &   "<<fixed<<std::setprecision(4) << TotEffErr[k][12]<<" &  "<<fixed<<std::setprecision(3) << RelEffErr[k][12]<<" hline "<<endl;
  cout<<" is2DiMuonsMassOK     &  "<< counter[k][13]<<"  &    "<< TotEff[k][13]<<" &     "<< RelEff[k][13]<<" &   "<<fixed<<std::setprecision(4) << TotEffErr[k][13]<<" &  "<<fixed<<std::setprecision(3) << RelEffErr[k][13]<<" hline "<<endl;
  cout<<" is2DiMuonHLTFired    &  "<< counter[k][14]<<"  &    "<< TotEff[k][14]<<" &     "<< RelEff[k][14]<<" &   "<<fixed<<std::setprecision(4) << TotEffErr[k][14]<<" &  "<<fixed<<std::setprecision(3) << RelEffErr[k][14]<<" hline "<<endl;
  cout<<" is2DiMuonsIsoTkOK    &  "<< counter[k][15] <<" &    "<< TotEff[k][15]<<" &     "<< RelEff[k][15]<<" &   "<<fixed<<std::setprecision(4) << TotEffErr[k][15]<<" &  " <<fixed<<std::setprecision(3) << RelEffErr[k][15]<<" hline "<<endl;
  cout<<" is2DiMuonsPixHitOK   &  "<< counter[k][16] <<" &    "<< TotEff[k][16]<<" &     "<< RelEff[k][16]<<" &   "<<fixed<<std::setprecision(4) << TotEffErr[k][16]<<" &  " <<fixed<<std::setprecision(3) << RelEffErr[k][16]<<" hline "<<endl;
  
  cout<<"end{tabular}"<<endl;
  cout<<"end{landscape}"<<endl;
  
  cout<<" Events Region A   "<<ev_regionA<<endl;
  cout<<"                   "<<endl;  
  cout<<" Events Region B   "<<ev_regionB<<endl;
  cout<<" Events Region B1   "<<ev_regionB1<<endl;
  cout<<" Events Region B2   "<<ev_regionB2<<endl;
  cout<<" Events Region B3   "<<ev_regionB3<<endl;
  cout<<" Events Region C   "<<ev_regionC<<endl;
  cout<<" Events Region C1   "<<ev_regionC1<<endl;
  cout<<" Events Region C2   "<<ev_regionC2<<endl;
  cout<<" Events Region C3   "<<ev_regionC3<<endl;
  cout<<" Events Region D   "<<ev_regionD<<endl;
  cout<<" Events Region D1   "<<ev_regionD1<<endl;
  cout<<" Events Region D2   "<<ev_regionD2<<endl;
  cout<<" Events Region D3   "<<ev_regionD3<<endl;
  
  
}



//  Float_t ctau1[15]={0,0.2,0.5,2.0,5.0};
//   Float_t ctauerr1[15]={0.0};

//   TGraphErrors *epsvsalp1 = new TGraphErrors(5,ctau1,epsvsalph,ctauerr1,Error);

//   TH2F *dummy = new TH2F("dummy","",100,-0.1,5.1,100,0.0,1.0);

//   TAxis *yaxis = epsvsalp1->GetYaxis();
//   yaxis->SetLimits(0.0,1.0);

//   //second graph
//   Float_t ctau2[9]={0,0.05,0.1,0.1,0.5,1.0,2.0,3.0,5.0};
//   Float_t ctauerr2[9]={0.0};
//   Float_t Error2[9]={0.0};

//   for(int m=0;m<9;m++){
//     Error2[m] = Error[m+5];
//     epsvsalph2[m] = epsvsalph[m+5];
//   }

//  TGraphErrors *epsvsalp2 = new TGraphErrors(9,ctau2,epsvsalph2,ctauerr2,Error2);

//   TLegend *leg = new TLegend(0.1,0.7,0.48,0.9);
//   leg->SetHeader("Mass","C");
//   leg->AddEntry(epsvsalp1,"Mass = 0.7 GeV", "pl");
//   leg->AddEntry(epsvsalp2,"Mass = 0.25 GeV", "pl");

//   TCanvas *c = new TCanvas("c","c");
//   dummy->GetYaxis()->SetTitle("#epsilon/#alpha");
//   dummy->GetXaxis()->SetTitle("c#tau[mm]");
//   dummy->Draw();
//   epsvsalp1->SetMarkerStyle(20);
//   epsvsalp1->SetMarkerSize(1.2);
//   epsvsalp2->SetMarkerStyle(20);
//   epsvsalp2->SetMarkerSize(1.2);
//   epsvsalp2->SetLineColor(kRed);
//   epsvsalp2->SetMarkerColor(kRed);

//   epsvsalp1->Draw("PL");
//   epsvsalp2->Draw("PLSAME");
//   leg->Draw("SAME");



void jpsi()
{
  const std::string txtfile = "Charmonium_all.txt";
    
  setup();
  std::vector< std::vector<string> > vector_of_files;
  // // cout << "Vector Created" << endl;
  readTextFileWithSamples(txtfile, vector_of_files);
  // // cout << "Samples read" << endl;
  for(auto v: vector_of_files) efficiency(v);
  // // cout << "For Loop completes" << endl;

}

void analysis(const std::string txtfile)
{

  setup();
  std::vector< std::vector<string> > DarkSUSY_mH_125_mGammaD_v;
  // // cout << "Vector Created" << endl;
  readTextFileWithSamples(txtfile, DarkSUSY_mH_125_mGammaD_v);
  // // cout << "Samples read" << endl;
  for(auto v: DarkSUSY_mH_125_mGammaD_v) efficiency(v);
  // // cout << "For Loop completes" << endl;

}
