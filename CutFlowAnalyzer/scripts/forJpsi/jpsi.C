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
Int_t ev_regionC=0;
Int_t ev_regionD=0;

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

int k = -1;
void efficiency(const std::vector<std::string>& dirNames)
{

  TString Run_period;


  bool verbose(true);

  //	TString dirname(fileName);
  TChain* chain = new TChain("dummy");
  TString ext("out_ana_");
  
  if(verbose) cout<<" dirNames  "<<dirNames[0]<<endl;
  
  
  bool alldata=false;
  //  bool alldata=true;
  //  bool mcsps=true;
  bool mcsps=false;
  if(alldata) Run_period = "all";
  if(mcsps) Run_period = "SPS";
  if(!alldata && !mcsps)  decodeFileNameManyData(dirNames, Run_period);
  
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

  TH1F *iso_C_aftTrig = new TH1F("iso_C_aftTrig","",100,0.0,12.0);
  TH1F *iso_F_aftTrig = new TH1F("iso_F_aftTrig","",100,0.0,12.0);

  TH1F *eta_Mu0_aftTrig = new TH1F("eta_Mu0_aftTrig","",100,-2.5,2.5);
  TH1F *eta_Mu1_aftTrig = new TH1F("eta_Mu1_aftTrig","",100,-2.5,2.5);
  TH1F *eta_Mu2_aftTrig = new TH1F("eta_Mu2_aftTrig","",100,-2.5,2.5);
  TH1F *eta_Mu3_aftTrig = new TH1F("eta_Mu3_aftTrig","",100,-2.5,2.5);

  TH1F *diMuonC_Lxy_RegionA = new TH1F("diMuonC_Lxy_RegionA","",100,-0.3,2.0);
  TH1F *diMuonF_Lxy_RegionA = new TH1F("diMuonF_Lxy_RegionA","",100,-0.3,2.0);

  TH1F *diMuonC_Lxy_RegionC = new TH1F("diMuonC_Lxy_RegionC","",100,-0.3,2.0);
  TH1F *diMuonF_Lxy_RegionC = new TH1F("diMuonF_Lxy_RegionC","",100,-0.3,2.0);

  TH1F *diMuonC_Rapidity_RegionA = new TH1F("diMuonC_Rapidity_RegionA","",100,-0.3,2.0);
  TH1F *diMuonF_Rapidity_RegionA = new TH1F("diMuonF_Rapidity_RegionA","",100,-0.3,2.0);

  TH1F *diMuonC_Rapidity_RegionC = new TH1F("diMuonC_Rapidity_RegionC","",100,-0.3,2.0);
  TH1F *diMuonF_Rapidity_RegionC = new TH1F("diMuonF_Rapidity_RegionC","",100,-0.3,2.0);
  
  TH2F *Iso_dim1_vs_dim2 = new TH2F("Iso_dim1_vs_dim2","",100,0.0,12.0,100,0.0,12.0);
  TH2F *Iso_dim1_vs_dim2_aftmasscut = new TH2F("Iso_dim1_vs_dim2_aftmasscut","",100,0.0,12.0,100,0.0,12.0);
  TH2F *mass_dim1_vs_dim2 = new TH2F("mass_dim1_vs_dim2","",100,0.0,5.0,100,0.0,5.0);

  TObjArray *fileElements=chain->GetListOfFiles();
  TIter next(fileElements);
  TChainElement *chEl=0;

  //  k++;
  //cout << "p: " << p << endl;
  //if(p == 0 || p%3 == 0) setup(); //reset vectors for every 4th cT for tables.


  TFile *savehist = new TFile("plots/savehist_"+Run_period+".root","RECREATE");
  
  
  while ((chEl=(TChainElement*)next())) {  //loopforfiles
    if (verbose) std::cout << "running on file " << chEl->GetTitle() << std::endl;
    TFile* myfile = new TFile(chEl->GetTitle());
    if (!myfile) {
      if (verbose) std::cout << "File " << chEl->GetTitle() << " does not exist" << std::endl;
      continue;
    }
    //		if (verbose) std::cout << "Loading directory cutFlowAnalyzerPXBL3PXFL2" << std::endl;
    myfile->cd("cutFlowAnalyzerPXBL3PXFL2");

    TTree *t = (TTree*)myfile->Get("cutFlowAnalyzerPXBL3PXFL2/Events");
    if (!t) {
      if (verbose) std::cout << "Tree cutFlowAnalyzerPXBL3PXFL2/Events does not exist" << std::endl;
      continue;
    }

    //		if (verbose) cout<<"  Events  "<<t->GetEntries()<<endl;

    int nentries;


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

    nentries = t->GetEntries(); //no of entries

    for(int i=0;i<nentries;i++){ //loop for number of events
      t->GetEntry(i);
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
      
      if(nRecoMu>=4 && is2DiMuonHLTFired && isVtxOK){
	P_t_Mu0_aftTrig->Fill(selMu0_pT);
	P_t_Mu1_aftTrig->Fill(selMu1_pT);
	P_t_Mu2_aftTrig->Fill(selMu2_pT);
	P_t_Mu3_aftTrig->Fill(selMu3_pT);

	eta_Mu0_aftTrig->Fill(selMu0_eta);
	eta_Mu1_aftTrig->Fill(selMu1_eta);
	eta_Mu2_aftTrig->Fill(selMu2_eta);
	eta_Mu3_aftTrig->Fill(selMu3_eta);

	if(is2DiMuons && is2DiMuonsFittedVtxOK && fabs(diMuons_dz_FittedVtx)<0.1){
	  mass_C_aftTrig->Fill(massC);
	  mass_F_aftTrig->Fill(massF);
	  iso_C_aftTrig->Fill(diMuonC_IsoTk_FittedVtx);
	  iso_F_aftTrig->Fill(diMuonF_IsoTk_FittedVtx);

	  Iso_dim1_vs_dim2->Fill(diMuonC_IsoTk_FittedVtx,diMuonF_IsoTk_FittedVtx);
	  mass_dim1_vs_dim2->Fill(massC,massF);

	  if( (massC>2.8 && massC<3.3) && (massF>2.8 && massF<3.3) ){
	    Iso_dim1_vs_dim2_aftmasscut->Fill(diMuonC_IsoTk_FittedVtx,diMuonF_IsoTk_FittedVtx);

	    if(diMuonC_IsoTk_FittedVtx<2.0 && diMuonF_IsoTk_FittedVtx<2.0)  ev_regionA++;
	    if(diMuonC_IsoTk_FittedVtx<2.0 && diMuonF_IsoTk_FittedVtx>2.0)  ev_regionB++;
	    if(diMuonC_IsoTk_FittedVtx>2.0 && diMuonF_IsoTk_FittedVtx>2.0)  ev_regionC++;
	    if(diMuonC_IsoTk_FittedVtx>2.0 && diMuonF_IsoTk_FittedVtx<2.0)  ev_regionD++;

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
      }


      if(is1SelMu3p5)counter[k][6]++;
      if(is2SelMu3p5)counter[k][7]++;
      if(is3SelMu3p5)counter[k][8]++;
      if(is4SelMu3p5)counter[k][9]++;

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
    myfile->Close();
  }

  // 8)Fill Histogram with event number
  // hdimCm->Fill(diMuonC_Mass,diMuonF_Mass);
  cout<<"  Here is where the plotting starts  "<<endl;
  cout<<"  Here is where the plotting starts  "<<endl;

  //  Run_period="jpsi_SPS";

  savehist->cd();
  
  TCanvas *cevt = new TCanvas("cevt","cevt",800,600);
  evt_number->Draw();
  cevt->SaveAs("plots/event_"+Run_period+".png","recreate");


  //    TCanvas *cc = new TCanvas("cc","cc",800,600);
  //   mass_C->Draw();
  //   cc->SaveAs("plots/massC_"+Run_period+".png","recreate");

  //   TCanvas *cf = new TCanvas("cf","cf",800,600);
  //   mass_F->Draw();
  //   cf->SaveAs("plots/massF_"+Run_period+".png","recreate");

  //   TCanvas *e = new TCanvas("e","e",800,600);
  //  eta_Mu0->Draw();
  //  e->SaveAs("plots/e0_"+Run_period+".png","recreate");

  //  TCanvas *e1 = new TCanvas("e1","e1",800,600);
  //  eta_Mu0->Draw();
  //  e1->SaveAs("plots/e1_"+Run_period+".png","recreate");

  //  TCanvas *e2 = new TCanvas("e2","e2",800,600);
  // eta_Mu0->Draw();
  // e2->SaveAs("plots/e2_"+Run_period+".png","recreate");

  // TCanvas *e3 = new TCanvas("e3","e3",800,600);
  // eta_Mu0->Draw();
  // e3->SaveAs("plots/e3_"+Run_period+".png","recreate");

  // TCanvas *isoC = new TCanvas("isoC","isoC",800,600);
  // iso_C->Draw();
  // isoC->SaveAs("plots/isoC_"+Run_period+".png","recreate");

  // TCanvas *isoF = new TCanvas("isoF","isoF",800,600);
  // iso_C->Draw();
  // isoF->SaveAs("plots/isoF_"+Run_period+".png","recreate");

  // TCanvas *c = new TCanvas("c","c",800,600);
  //  P_t_Mu0->Draw();
  //  c->SaveAs("plots/pt_mu0_"+Run_period+".png","recreate");

  //  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  //  P_t_Mu1->Draw();
  //  c1->SaveAs("plots/pt_mu1_"+Run_period+".png","recreate");

  //  TCanvas *c2 = new TCanvas("c2","c2",800,600);
  //  P_t_Mu2->Draw();
  //  c2->SaveAs("plots/pt_mu2_"+Run_period+".png","recreate");

  //  TCanvas *c3 = new TCanvas("c3","c3",800,600);
  //  P_t_Mu3->Draw();
  //  c3->SaveAs("plots/pt_mu3_"+Run_period+".png","recreate");



  TCanvas *tcc = new TCanvas("tcc","tcc",800,600);
  mass_C_aftTrig->Write();
  mass_C_aftTrig->Draw();
  tcc->SaveAs("plots/massC_aftTrig_"+Run_period+".png","recreate");

  TCanvas *tcf = new TCanvas("tcf","tcf",800,600);
  mass_F_aftTrig->Draw();
  tcf->SaveAs("plots/massF_aftTrig_"+Run_period+".png","recreate");

  TCanvas *te = new TCanvas("te","te",800,600);
  eta_Mu0_aftTrig->Draw();
  te->SaveAs("plots/eta0_aftTrig_"+Run_period+".png","recreate");

  TCanvas *te1 = new TCanvas("te1","te1",800,600);
  eta_Mu0_aftTrig->Draw();
  te1->SaveAs("plots/eta1_aftTrig_"+Run_period+".png","recreate");

  TCanvas *te2 = new TCanvas("te2","te2",800,600);
  eta_Mu0_aftTrig->Draw();
  te2->SaveAs("plots/eta2_aftTrig_"+Run_period+".png","recreate");

  TCanvas *te3 = new TCanvas("te3","te3",800,600);
  eta_Mu0_aftTrig->Draw();
  te3->SaveAs("plots/eta3_aftTrig_"+Run_period+".png","recreate");

  TCanvas *tisoC = new TCanvas("tisoC","tisoC",800,600);
  iso_C_aftTrig->Draw();
  tisoC->SaveAs("plots/isoC_aftTrig_"+Run_period+".png","recreate");

  TCanvas *tisoF = new TCanvas("tisoF","tisoF",800,600);
  iso_F_aftTrig->Draw();
  tisoF->SaveAs("plots/isoF_aftTrig_"+Run_period+".png","recreate");

  TCanvas *tc = new TCanvas("tc","tc",800,600);
  P_t_Mu0_aftTrig->Draw();
  tc->SaveAs("plots/pt_mu0_aftTrig_"+Run_period+".png","recreate");

  TCanvas *tc1 = new TCanvas("tc1","tc1",800,600);
  P_t_Mu1_aftTrig->Draw();
  tc1->SaveAs("plots/pt_mu1_aftTrig_"+Run_period+".png","recreate");

  TCanvas *tc2 = new TCanvas("tc2","tc2",800,600);
  P_t_Mu2_aftTrig->Draw();
  tc2->SaveAs("plots/pt_mu2_aftTrig_"+Run_period+".png","recreate");

  TCanvas *tc3 = new TCanvas("tc3","tc3",800,600);
  P_t_Mu3_aftTrig->Draw();
  tc3->SaveAs("plots/pt_mu3_aftTrig_"+Run_period+".png","recreate");

  TCanvas *c2d = new TCanvas("c2d","c2d",800,600);
  Iso_dim1_vs_dim2->Draw("COLORZ");
  c2d->SaveAs("plots/Iso_dim1_vs_dim2_"+Run_period+".png","recreate");

  TCanvas *c2d1 = new TCanvas("c2d1","c2d1",800,600);
  mass_dim1_vs_dim2->Draw("COLORZ");
  c2d1->SaveAs("plots/mass_dim1_vs_dim2_"+Run_period+".png","recreate");

  TCanvas *c222 = new TCanvas("c222","c222",800,600);
  Iso_dim1_vs_dim2_aftmasscut->GetXaxis()->SetTitle("Iso di-#mu_{1} [GeV]");
  Iso_dim1_vs_dim2_aftmasscut->GetYaxis()->SetTitle("Iso di-#mu_{2} [GeV]");
  Iso_dim1_vs_dim2_aftmasscut->Draw("COLORZ");
  c222->SaveAs("plots/mass_dim1_vs_dim2_aftmasscut"+Run_period+".png","recreate");

  diMuonC_Lxy_RegionA->Write();
  diMuonF_Lxy_RegionA->Write();
  diMuonC_Lxy_RegionC->Write();
  diMuonF_Lxy_RegionC->Write();

  diMuonC_Rapidity_RegionA->Write();
  diMuonF_Rapidity_RegionA->Write();
  diMuonC_Rapidity_RegionC->Write();
  diMuonF_Rapidity_RegionC->Write();

  TCanvas *c2221 = new TCanvas("c2221","c2221",800,600);
  diMuonC_Lxy_RegionA->Draw();
  c2221->SaveAs("plots/diMuonC_Lxy_regionA_"+Run_period+".png","recreate");

  TCanvas *c2222 = new TCanvas("c2222","c2222",800,600);
  diMuonF_Lxy_RegionA->Draw();
  c2222->SaveAs("plots/diMuonF_Lxy_regionA_"+Run_period+".png","recreate");

  TCanvas *c2223 = new TCanvas("c2223","c2223",800,600);
  diMuonC_Lxy_RegionC->Draw();
  c2223->SaveAs("plots/diMuonC_Lxy_regionC_"+Run_period+".png","recreate");

  TCanvas *c2224 = new TCanvas("c2224","c2224",800,600);
  diMuonF_Lxy_RegionC->Draw();
  c2224->SaveAs("plots/diMuonF_Lxy_regionC_"+Run_period+".png","recreate");



  TCanvas *c22221 = new TCanvas("c22221","c22221",800,600);
  diMuonC_Rapidity_RegionA->Draw();
  c22221->SaveAs("plots/diMuonC_Rapidity_regionA_"+Run_period+".png","recreate");

  TCanvas *c22222 = new TCanvas("c22222","c22222",800,600);
  diMuonF_Rapidity_RegionA->Draw();
  c22222->SaveAs("plots/diMuonF_Rapidity_regionA_"+Run_period+".png","recreate");

  TCanvas *c22223 = new TCanvas("c22223","c22223",800,600);
  diMuonC_Rapidity_RegionC->Draw();
  c22223->SaveAs("plots/diMuonC_Rapidity_regionC_"+Run_period+".png","recreate");

  TCanvas *c22224 = new TCanvas("c22224","c22224",800,600);
  diMuonF_Rapidity_RegionC->Draw();
  c22224->SaveAs("plots/diMuonF_Rapidity_regionC_"+Run_period+".png","recreate");
  
  delete savehist;
  
  /* RelEff[k][0] = counter[k][0]/(counter[k][0]*1.0); */
  /* for(int m=6;m<17;m++){ */
  /*   TotEff[k][m]= counter[k][m]/(counter[k][0]*1.0); */
  /*   TotEffErr[k][m]= sqrt( (TotEff[k][m]*(1-TotEff[k][m]))/(counter[k][0]*1.0)); */
  /*   if(m>0){ */
  /*     if(m==6){ */
  /* 	RelEff[k][m]= counter[k][m]/(counter[k][0]*1.0); */
  /* 	RelEffErr[k][m]= sqrt( (RelEff[k][m]*(1-RelEff[k][m]))/(counter[k][0]*1.0)); */
  /*     } */
  /*     else{ */
  /* 	RelEff[k][m]=  counter[k][m]/(counter[k][m-1]*1.0); */
  /* 	RelEffErr[k][m]= sqrt( (RelEff[k][m]*(1-RelEff[k][m]))/(counter[k][m-1]*1.0)); */
  /*     } */
  /*   } */
  /* } */


  /* cout<<"        "<<endl; */
  /* cout<<"begin{landscape}"<<endl; */
  /* cout<<"centering"<<endl; */
  /* cout<<"begin{tabular}{ c| c | c | c | c | c }"<<endl; */

  /* cout<<" Selection   "<<" \\# Events   "<<"   Total Efficiency  "<<" Relative Efficiency   "<<" TotalEffError   "<<" RelEffError "<<" hline "<<endl; */

  /* cout<<" No cut      &   "<<left<< setw(7)<< counter[k][0]<<"     &   "<<fixed<< std::setprecision(3)<< TotEff[k][0]<<"         &     "<< RelEff[k][0]<<"           &   "<<left<< setw(7)<< TotEffErr[k][0]<<"      &   "<< RelEffErr[k][0]<<" hline "<<endl; */

  /* cout<<" is1SelMu3p5   &    "<<left<< setw(7)<< counter[k][6]<<"  &    "<<left<< setw(7)<< TotEff[k][6] <<setw(10)<<"   &    "<<left<< setw(7)<<  RelEff[k][6]<<"  &    "<<left<< setw(7)<<  TotEffErr[k][6]<<" &  " <<  RelEffErr[k][6]<<" hline "<<endl; */
  /* cout<< setprecision(3); */
  /* cout<<" is2SelMu3p5    &    "<< counter[k][7]<<"  &    "<< TotEff[k][7] <<setw(10)<<"   &   "<< RelEff[k][7]<<"   &   "<< TotEffErr[k][7]<<"  & "<< RelEffErr[k][7]<<" hline "<<endl; */
  /* cout<<" is3SelMu3p5    &    "<< counter[k][8]<<"  &    "<< TotEff[k][8]<<"   &    "<< RelEff[k][8]<<"   &   "<< TotEffErr[k][8]<<" &  "<< RelEffErr[k][8]<<" hline "<<endl; */
  /* cout<<" is4SelMu3p5    &    "<< counter[k][9]<<"  &    "<< TotEff[k][9]<<"   &    "<< RelEff[k][9]<<"   &   "<< TotEffErr[k][9]<<" &  "<< RelEffErr[k][9]<<" hline "<<endl; */
  /* cout<<"                                                                        "<<" hline "<<endl; */
  /* cout<<" is2dimuon            &  "<< counter[k][10]<<"  &    "<< TotEff[k][10]<<" &    "<< RelEff[k][10]<<"  &   "<<fixed<<std::setprecision(4) << TotEffErr[k][10]<<" &  "<< RelEffErr[k][10]<<" hline "<<endl; */

  /* cout<<" is2DiMuonsFittedVtx  &  "<< counter[k][11]<<"  &    "<< TotEff[k][11]<<" &     "<< RelEff[k][11]<<" &   "<<fixed<<std::setprecision(4) << TotEffErr[k][11]<<" &  "<<fixed<<std::setprecision(3) << RelEffErr[k][11]<<" hline "<<endl; */
  /* cout<<" is2DiMuonsFittedDz   &  "<< counter[k][12]<<"  &    "<< TotEff[k][12]<<" &     "<< RelEff[k][12]<<" &   "<<fixed<<std::setprecision(4) << TotEffErr[k][12]<<" &  "<<fixed<<std::setprecision(3) << RelEffErr[k][12]<<" hline "<<endl; */
  /* cout<<" is2DiMuonsMassOK     &  "<< counter[k][13]<<"  &    "<< TotEff[k][13]<<" &     "<< RelEff[k][13]<<" &   "<<fixed<<std::setprecision(4) << TotEffErr[k][13]<<" &  "<<fixed<<std::setprecision(3) << RelEffErr[k][13]<<" hline "<<endl; */
  /* cout<<" is2DiMuonHLTFired    &  "<< counter[k][14]<<"  &    "<< TotEff[k][14]<<" &     "<< RelEff[k][14]<<" &   "<<fixed<<std::setprecision(4) << TotEffErr[k][14]<<" &  "<<fixed<<std::setprecision(3) << RelEffErr[k][14]<<" hline "<<endl; */
  /* cout<<" is2DiMuonsIsoTkOK    &  "<< counter[k][15] <<" &    "<< TotEff[k][15]<<" &     "<< RelEff[k][15]<<" &   "<<fixed<<std::setprecision(4) << TotEffErr[k][15]<<" &  " <<fixed<<std::setprecision(3) << RelEffErr[k][15]<<" hline "<<endl; */
  /* cout<<" is2DiMuonsPixHitOK   &  "<< counter[k][16] <<" &    "<< TotEff[k][16]<<" &     "<< RelEff[k][16]<<" &   "<<fixed<<std::setprecision(4) << TotEffErr[k][16]<<" &  " <<fixed<<std::setprecision(3) << RelEffErr[k][16]<<" hline "<<endl; */


  /* cout<<"end{tabular}"<<endl; */
  /* cout<<"end{landscape}"<<endl; */


  cout<<" Events Region A   "<<ev_regionA<<endl;
  cout<<" Events Region B   "<<ev_regionB<<endl;
  cout<<" Events Region C   "<<ev_regionC<<endl;
  cout<<" Events Region D   "<<ev_regionD<<endl;


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

//   TCanvas *c = new TCanvas("c","c",800,600);
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
