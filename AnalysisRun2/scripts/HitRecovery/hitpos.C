#include <iostream>
#include "TH2F.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TString.h"
#include "TEllipse.h"
#include "TCut.h"
using namespace std;

void hitpos(){

  TFile *f = new TFile("../MCsamples/DarkSUSY_mH_125_mGammaD_0250_cT_000_13TeV_RAW2DIGI_L1Reco_RECO_MCRUN2_74_V9_v1.root");
  //  TFile *f = new TFile("../../test/DarkSUSY_mH_125_mGammaD_0250_cT_000_13TeV_RAW2DIGI_L1Reco_RECO_MCRUN2_74_V9_v1/Ntup_ALL.root");
  f->cd("ana2012");
  TTree *t = (TTree*)f->Get("ana2012/Events");

  cout<<"  Events  "<<t->GetEntries()<<endl;

  TCut  sel = "2dimuon&&2mjets&&is2DiMuonsDzOK&&is2DiMuonsMassOK&&is2DiMuonsIsoTkOK&&is2DiMuonHLTFired";
  //  TCut  sel = "2dimuon";

  Float_t ev_2dim;

  ev_2dim = t->GetEntries(sel);

  cout<<" Events with 2 dimuons  "<<ev_2dim<<endl;

  Float_t ev_2dimhit;
  ev_2dimhit = t->GetEntries(sel&&"( (muJetC_hitpix[0]==1||muJetC_hitpix[1]==1)&&(muJetF_hitpix[0]==1||muJetF_hitpix[1]==1) )");
  cout<<" Events with 2 dimuons + pixel hit "<<ev_2dimhit<<endl;


  Float_t ev_2dimhitfail;
  ev_2dimhitfail = t->GetEntries(sel&&"( (muJetC_hitpix[0]!=1&&muJetC_hitpix[1]!=1)||(muJetF_hitpix[0]!=1&&muJetF_hitpix[1]!=1) )");
  cout<<" Events with 2 dimuons + pixel hit fail "<<ev_2dimhitfail<<endl;

  Float_t ev_2dimhitfail_muJets;
  ev_2dimhitfail_muJets = t->GetEntries(sel&&"( (muJetC_hitpix[0]!=1&&muJetC_hitpix[1]!=1)&&(muJetF_hitpix[0]!=1&&muJetF_hitpix[1]!=1) )");
  cout<<" Events with 2 dimuons + pixel hit fail both dimuons   "<<ev_2dimhitfail_muJets<<endl;

  Float_t ev_2dimhitfail_muJetC;
  ev_2dimhitfail_muJetC = t->GetEntries(sel&&"( (muJetC_hitpix[0]!=1&&muJetC_hitpix[1]!=1)&&(muJetF_hitpix[0]==1||muJetF_hitpix[1]==1 ) )");
  cout<<" Events with 2 dimuons + pixel hit fail muJetC   "<<ev_2dimhitfail_muJetC<<endl;

  Float_t ev_2dimhitfail_muJetF;
  ev_2dimhitfail_muJetF = t->GetEntries(sel&&"( (muJetF_hitpix[0]!=1&&muJetF_hitpix[1]!=1)&&(muJetC_hitpix[0]==1||muJetC_hitpix[1]==1 ) )");
  cout<<" Events with 2 dimuons + pixel hit fail muJetF   "<<ev_2dimhitfail_muJetF<<endl;



  //===================================================================

  Int_t event;
  Int_t nevent;
  Int_t nJob;
  Int_t lumi;
  Int_t ev2dim;
  Int_t ev2mj;
  Bool_t isVtxOK;
  Bool_t is2DimDzOK;
  Bool_t is2DimVtxOK;
  Bool_t is2DimHLTFired;
  Bool_t is2DimIsoTkOK;
  Bool_t is2DimMassOK;

  Int_t muJetChit[2];
  Int_t muJetFhit[2];
  Int_t comphitmu1JetC;
  Int_t comphitmu2JetC;
  Int_t comphitmu1JetF;
  Int_t comphitmu2JetF;

  Int_t Detmu1jetC;
  Int_t Detmu2jetC;
  Int_t Detmu1jetF;
  Int_t Detmu2jetF;


  Float_t mu1JetCposx[500];
  Float_t mu2JetCposx[500];
  Float_t mu1JetCposy[500];
  Float_t mu2JetCposy[500];

  Float_t mu1JetFposx[500];
  Float_t mu2JetFposx[500];
  Float_t mu1JetFposy[500];
  Float_t mu2JetFposy[500];

  Float_t pixelhitmu1JetCx[500];
  Float_t pixelhitmu2JetCx[500];
  Float_t pixelhitmu1JetCy[500];
  Float_t pixelhitmu2JetCy[500];
  Float_t pixelhitmu1JetFx[500];
  Float_t pixelhitmu2JetFx[500];
  Float_t pixelhitmu1JetFy[500];
  Float_t pixelhitmu2JetFy[500];

  Float_t pixelhitmu1JetCerrx[700];
  Float_t pixelhitmu2JetCerrx[700];
  Float_t pixelhitmu1JetCerry[700];
  Float_t pixelhitmu2JetCerry[700];
  Float_t pixelhitmu1JetFerrx[700];
  Float_t pixelhitmu2JetFerrx[700];
  Float_t pixelhitmu1JetFerry[700];
  Float_t pixelhitmu2JetFerry[700];


  Float_t mu1JetCerrposx[300];
  Float_t mu2JetCerrposx[300];
  Float_t mu1JetCerrposy[300];
  Float_t mu2JetCerrposy[300];

  Float_t mu1JetFerrposx[300];
  Float_t mu2JetFerrposx[300];
  Float_t mu1JetFerrposy[300];
  Float_t mu2JetFerrposy[300];


  Float_t genA0_Lxy_rdet;
  Float_t genA1_Lxy_rdet;
  Float_t genA0_Lz_rdet;
  Float_t genA1_Lz_rdet;

  t->SetBranchAddress("genA0_Lxy_rdet",&genA0_Lxy_rdet);
  t->SetBranchAddress("genA1_Lxy_rdet",&genA1_Lxy_rdet);

  t->SetBranchAddress("genA0_Lz_rdet",&genA0_Lz_rdet);
  t->SetBranchAddress("genA1_Lz_rdet",&genA1_Lz_rdet);


  t->SetBranchAddress("event",&event);
  t->SetBranchAddress("nevent",&nevent);
  t->SetBranchAddress("nJob",&nJob);
  t->SetBranchAddress("2dimuon",&ev2dim);
  t->SetBranchAddress("2mjets",&ev2mj);

  t->SetBranchAddress("isVertexOK",&isVtxOK);
  t->SetBranchAddress("is2DiMuonsDzOK",&is2DimDzOK);
  t->SetBranchAddress("is2DiMuonsVtxOK",&is2DimVtxOK);
  t->SetBranchAddress("is2DiMuonsMassOK",&is2DimMassOK);
  t->SetBranchAddress("is2DiMuonsIsoTkOK",&is2DimIsoTkOK);
  t->SetBranchAddress("is2DiMuonHLTFired",&is2DimHLTFired);

  t->SetBranchAddress("muJetC_hitpix",&muJetChit);
  t->SetBranchAddress("muJetF_hitpix",&muJetFhit);

  t->SetBranchAddress("Det_mu1_muJetC",&Detmu1jetC);
  t->SetBranchAddress("Det_mu2_muJetC",&Detmu2jetC);
  t->SetBranchAddress("Det_mu1_muJetF",&Detmu1jetF);
  t->SetBranchAddress("Det_mu2_muJetF",&Detmu2jetF);

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

  TH2F *muJetC_pos_muon1[5000];
  TH2F *muJetC_pos_muon2[5000];

  TH2F *muJetC_pos_muon1_zoomin[5000];
  TH2F *muJetC_pos_muon2_zoomin[5000];

  TH2F *muJetC_pos_muon1_rechit;
  TH2F *muJetC_pos_muon2_rechit;
  TH2F *muJetC_pos_muon1_rechit_zoomin;
  TH2F *muJetC_pos_muon2_rechit_zoomin;
    
  TH2F *muJetF_pos_muon1[5000];
  TH2F *muJetF_pos_muon2[5000];
  TH2F *muJetF_pos_muon1_rechit;
  TH2F *muJetF_pos_muon2_rechit;

  TH2F *muJetF_pos_muon1_zoomin[5000];
  TH2F *muJetF_pos_muon2_zoomin[5000];
  TH2F *muJetF_pos_muon1_rechit_zoomin;
  TH2F *muJetF_pos_muon2_rechit_zoomin;

  Int_t nentries = t->GetEntries();

  Int_t count_dmCfail=0;
  Int_t count_dmFfail=0;

  Int_t evid=0;

  Float_t ymin2=-4.0;
  Float_t ymax2=4.0;
  Float_t xmin2=-1.5;
  Float_t xmax2=1.5;  

  Float_t ymin=0.;
  Float_t ymax=0.;
  Float_t xmin=0.;
  Float_t xmax=0.;


  Float_t ymin2e=-4.0;
  Float_t ymax2e=4.0;
  Float_t xmin2e=-1.5;
  Float_t xmax2e=1.5;  

  Float_t ymine=0.;
  Float_t ymaxe=0.;
  Float_t xmine=0.;
  Float_t xmaxe=0.;

  char nameh[80];
  char nameh2[80];
  char nameh3[80];
  char nameh4[80];
  char nameh5[80];
  char nameh6[80];

  Int_t counter_F=0;
  
  for(int k=0;k<nentries;k++){

    //  for(int k=0;k<1000;k++){
    t->GetEntry(k);

    
    if(ev2dim&&isVtxOK&&is2DimDzOK&&is2DimVtxOK&&is2DimMassOK&&is2DimIsoTkOK&&is2DimHLTFired){
    
      evid = (nJob*10000)+nevent;
      cout<<" ev id   "<<evid<<endl;

      if( (muJetChit[0]!=1&&muJetChit[1]!=1) && (muJetFhit[0]==1||muJetFhit[1]==1)){

	ymin=mu1JetCposy[0]-0.5;
	ymax=mu1JetCposy[0]+0.5;
	xmin=mu1JetCposx[0]-0.05;
	xmax=mu1JetCposx[0]+0.05;

	for(int j=0;j<Detmu1jetC;j++){
	  sprintf(nameh,"muJetC_pos_muon1_det%d_%d",j,evid);
	  muJetC_pos_muon1[j] = new TH2F(nameh,"",100,xmin2,xmax2,100,ymin2,ymax2);
	  muJetC_pos_muon1[j]->Fill(mu1JetCposx[j],mu1JetCposy[j]);
      
	  sprintf(nameh2,"muJetC_pos_muon1_det%d_%d_zoomin",j,evid);
	  muJetC_pos_muon1_zoomin[j] = new TH2F(nameh2,"",100,xmin,xmax,100,ymin,ymax);
	  muJetC_pos_muon1_zoomin[j]->Fill(mu1JetCposx[j],mu1JetCposy[j]);
	}

	for(int j=0;j<Detmu2jetC;j++){
	  sprintf(nameh,"muJetC_pos_muon2_det%d_%d",j,evid);
	  muJetC_pos_muon2[j] = new TH2F(nameh,"",100,xmin2,xmax2,100,ymin2,ymax2);
	  muJetC_pos_muon2[j]->Fill(mu2JetCposx[j],mu2JetCposy[j]);

	  sprintf(nameh2,"muJetC_pos_muon2_det%d_%d_zoomin",j,evid);
	  muJetC_pos_muon2_zoomin[j] = new TH2F(nameh2,"",100,xmin,xmax,100,ymin,ymax);
	  muJetC_pos_muon2_zoomin[j]->Fill(mu2JetCposx[j],mu2JetCposy[j]);
	}

	//  	  TEllipse el1(mu2JetCposx[0],mu2JetCposy[0],0.001,0.001)x;
	//        TEllipse el2(0.604465,-0.0119769,0.004,0.004);
	// el2.Draw("same");
    
	sprintf(nameh3,"muJetC_pos_muon1_rechit_%d",evid);
	sprintf(nameh4,"muJetC_pos_muon1_rechit_zoomin_%d",evid);
	muJetC_pos_muon1_rechit = new TH2F(nameh3,"",100,xmin2,xmax2,100,ymin2,ymax2);
	muJetC_pos_muon1_rechit_zoomin = new TH2F(nameh4,"",100,xmin,xmax,100,ymin,ymax);
    
	for(int j=0;j<comphitmu1JetC;j++){
	  muJetC_pos_muon1_rechit->Fill(pixelhitmu1JetCx[j],pixelhitmu1JetCy[j]);
	  muJetC_pos_muon1_rechit_zoomin->Fill(pixelhitmu1JetCx[j],pixelhitmu1JetCy[j]);
	  //       cout<<" hit position x  "<<pixelhitmu1JetCx[j]<<" hit position y  "<<pixelhitmu1JetCy[j]<<endl;
	}

	sprintf(nameh5,"muJetC_pos_muon2_rechit_%d",evid);
	sprintf(nameh6,"muJetC_pos_muon2_rechit_zoomin_%d",evid);
	muJetC_pos_muon2_rechit = new TH2F(nameh5,"",100,xmin2,xmax2,100,ymin2,ymax2);
	muJetC_pos_muon2_rechit_zoomin = new TH2F(nameh6,"",100,xmin,xmax,100,ymin,ymax);
	for(int j=0;j<comphitmu2JetC;j++){
	  muJetC_pos_muon2_rechit->Fill(pixelhitmu2JetCx[j],pixelhitmu2JetCy[j]);
	  muJetC_pos_muon2_rechit_zoomin->Fill(pixelhitmu2JetCx[j],pixelhitmu2JetCy[j]);
	}
     
	TCanvas *c = new TCanvas("c","c",700,500);
	for(int l=0;l<Detmu1jetC;l++){
	  muJetC_pos_muon1[l]->SetFillColor(4+l);
	  if(l==0) muJetC_pos_muon1[l]->Draw("BOX");
	  if(l==0) muJetC_pos_muon1[l]->GetXaxis()->SetTitle("local x position [cm]");
	  if(l==0) muJetC_pos_muon1[l]->GetYaxis()->SetTitle("local y position [cm]");
	  else muJetC_pos_muon1[l]->Draw("BOXsame");
	}
     
	char legname[50];
	for(int l=0;l<Detmu2jetC;l++){
	  muJetC_pos_muon2[l]->SetLineColor(4+l);
	  if(l==0) muJetC_pos_muon2[l]->Draw("BOXsame");
	  else muJetC_pos_muon2[l]->Draw("BOXsame");
	  sprintf(legname,"muJetC muon2 Det_%d",l);
	}
     
	//  	  el1.Draw("same");
     
     
	muJetC_pos_muon1_rechit->SetFillColor(2);
	muJetC_pos_muon1_rechit->Draw("BOXsame");
	muJetC_pos_muon2_rechit->SetFillColor(2);
	muJetC_pos_muon2_rechit->Draw("BOXsame");
     
     
     
	char namec[50];
	sprintf(namec,"muon_recover_pos/muJetC/muJetC_hits_%d.pdf",evid);
	c->SaveAs(namec,"recreate");
	c->Close();

	  
	char legname1[50];
	TCanvas *c1 = new TCanvas("c1","c1",700,500);
	for(int l=0;l<Detmu1jetC;l++){
	  muJetC_pos_muon1_zoomin[l]->SetFillColor(4+l);
	  if(l==0) muJetC_pos_muon1_zoomin[l]->Draw("BOX");
	  if(l==0) muJetC_pos_muon1_zoomin[l]->GetXaxis()->SetTitle("local x position [cm]");
	  if(l==0) muJetC_pos_muon1_zoomin[l]->GetYaxis()->SetTitle("local y position [cm]");
	  else muJetC_pos_muon1_zoomin[l]->Draw("BOXsame");
	}
      
	for(int l=0;l<Detmu2jetC;l++){
	  muJetC_pos_muon2_zoomin[l]->SetLineColor(4+l);
	  if(l==0) muJetC_pos_muon2_zoomin[l]->Draw("BOXsame");
	  else muJetC_pos_muon2_zoomin[l]->Draw("BOXsame");
	}
      
	muJetC_pos_muon1_rechit_zoomin->SetFillColor(2);
	muJetC_pos_muon1_rechit_zoomin->Draw("BOXsame");
	muJetC_pos_muon2_rechit_zoomin->SetFillColor(2);
	muJetC_pos_muon2_rechit_zoomin->Draw("BOXsame");

	char namec2[50];
	sprintf(namec2,"muon_recover_pos/muJetC/muJetC_hits_%d_zoomin.pdf",evid);
	c1->SaveAs(namec2,"recreate");
	c1->Close();
      }




    
      if( (muJetFhit[0]!=1&&muJetFhit[1]!=1) && (muJetChit[0]==1||muJetChit[1]==1)){

	counter_F++;
	
	ymin=mu1JetFposy[0]-0.1;
	ymax=mu1JetFposy[0]+0.1;
	xmin=mu1JetFposx[0]-0.05;
	xmax=mu1JetFposx[0]+0.05;
      
	for(int j=0;j<Detmu1jetF;j++){
	  sprintf(nameh,"muJetF_pos_muon1_det%d_%d",j,nJob*10000+nevent);
	  muJetF_pos_muon1[j] = new TH2F(nameh,"",100,xmin2,xmax2,100,ymin2,ymax2);
	  muJetF_pos_muon1[j]->Fill(mu1JetFposx[j],mu1JetFposy[j]);
	
	  sprintf(nameh2,"muJetF_pos_muon1_det%d_%d_zoomin",j,nJob*10000+nevent);
	  muJetF_pos_muon1_zoomin[j] = new TH2F(nameh2,"",100,xmin,xmax,100,ymin,ymax);
	  muJetF_pos_muon1_zoomin[j]->Fill(mu1JetFposx[j],mu1JetFposy[j]);
	}
      
	for(int j=0;j<Detmu2jetF;j++){
	  sprintf(nameh,"muJetF_pos_muon2_det%d_%d",j,nJob*10000+nevent);
	  muJetF_pos_muon2[j] = new TH2F(nameh,"",100,xmin2,xmax2,100,ymin2,ymax2);
	  muJetF_pos_muon2[j]->Fill(mu2JetFposx[j],mu2JetFposy[j]);
	
	  sprintf(nameh2,"muJetF_pos_muon2_det%d_%d_zoomin",j,nJob*10000+nevent);
	  muJetF_pos_muon2_zoomin[j] = new TH2F(nameh2,"",100,xmin,xmax,100,ymin,ymax);
	  muJetF_pos_muon2_zoomin[j]->Fill(mu2JetFposx[j],mu2JetFposy[j]);
	}
      
	muJetF_pos_muon1_rechit = new TH2F("muJetF_pos_muon1_rechit","",100,xmin2,xmax2,100,ymin2,ymax2);
	muJetF_pos_muon1_rechit_zoomin = new TH2F("muJetF_pos_muon1_rechit_zoomin","",100,xmin,xmax,100,ymin,ymax);
      
	for(int j=0;j<comphitmu1JetF;j++){
	  muJetF_pos_muon1_rechit->Fill(pixelhitmu1JetFx[j],pixelhitmu1JetFy[j]);
	  muJetF_pos_muon1_rechit_zoomin->Fill(pixelhitmu1JetFx[j],pixelhitmu1JetFy[j]);
	  //	    cout<<" hit position x  "<<pixelhitmu1JetCx[j]<<" hit position y  "<<pixelhitmu1JetCy[j]<<endl;
	}
      
	muJetF_pos_muon2_rechit = new TH2F("muJetF_pos_muon2_rechit","",100,xmin2,xmax2,100,ymin2,ymax2);
	muJetF_pos_muon2_rechit_zoomin = new TH2F("muJetF_pos_muon2_rechit_zoomin","",100,xmin,xmax,100,ymin,ymax);
	for(int j=0;j<comphitmu2JetF;j++){
	  muJetF_pos_muon2_rechit->Fill(pixelhitmu2JetFx[j],pixelhitmu2JetFy[j]);
	  muJetF_pos_muon2_rechit_zoomin->Fill(pixelhitmu2JetFx[j],pixelhitmu2JetFy[j]);
	}
      
      
	char legname2[50];
	TCanvas *c = new TCanvas("c","c",700,500);
	for(int l=0;l<Detmu1jetF;l++){
	  muJetF_pos_muon1[l]->SetFillColor(4+l);
	  if(l==0) muJetF_pos_muon1[l]->Draw("BOX");
	  if(l==0) muJetF_pos_muon1[l]->GetXaxis()->SetTitle("local x position [cm]");
	  if(l==0) muJetF_pos_muon1[l]->GetYaxis()->SetTitle("local y position [cm]");
	  else muJetF_pos_muon1[l]->Draw("BOXsame");
	}
      
	for(int l=0;l<Detmu2jetF;l++){
	  muJetF_pos_muon2[l]->SetLineColor(4+l);
	  if(l==0) muJetF_pos_muon2[l]->Draw("BOXsame");
	  else muJetF_pos_muon2[l]->Draw("BOXsame");
	}
      
	muJetF_pos_muon1_rechit->SetFillColor(2);
	muJetF_pos_muon1_rechit->Draw("BOXsame");
      
	muJetF_pos_muon2_rechit->SetFillColor(2);
	muJetF_pos_muon2_rechit->Draw("BOXsame");
      
	char namec3[50];
	sprintf(namec3,"muon_recover_pos/muJetF/muJetF_hits_%d.pdf",evid);
	c->SaveAs(namec3,"recreate");
	c->Close();
      
	char legname3[50];
	TCanvas *c2 = new TCanvas("c1","c1",700,500);
	for(int l=0;l<Detmu1jetF;l++){
	  muJetF_pos_muon1_zoomin[l]->SetFillColor(4+l);
	  if(l==0) muJetF_pos_muon1_zoomin[l]->Draw("BOX");
	  if(l==0) muJetF_pos_muon1_zoomin[l]->GetXaxis()->SetTitle("local x position [cm]");
	  if(l==0) muJetF_pos_muon1_zoomin[l]->GetYaxis()->SetTitle("local y position [cm]");
	  else muJetF_pos_muon1_zoomin[l]->Draw("BOXsame");
	}
      
	for(int l=0;l<Detmu2jetF;l++){
	  muJetF_pos_muon2_zoomin[l]->SetLineColor(4+l);
	  if(l==0) muJetF_pos_muon2_zoomin[l]->Draw("BOXsame");
	  else muJetF_pos_muon2_zoomin[l]->Draw("BOXsame");
	}
      
	muJetF_pos_muon1_rechit_zoomin->SetFillColor(2);
	muJetF_pos_muon1_rechit_zoomin->Draw("BOXsame");
	muJetF_pos_muon2_rechit_zoomin->SetFillColor(2);
	muJetF_pos_muon2_rechit_zoomin->Draw("BOXsame");
      
	char namec4[50];
	sprintf(namec4,"muon_recover_pos/muJetF/muJetF_hits_%d_zoomin.pdf",evid);
	c2->SaveAs(namec4,"recreate");
	c2->Close();

      }

    
      if((muJetFhit[0]!=1&&muJetFhit[1]!=1) && (muJetChit[0]!=1&&muJetChit[1]!=1)){
      
	// ymin2=mu1JetFposy[0]-8.0;
	// ymax2=mu1JetFposy[0]+8.0;
	// xmin2=mu1JetFposx[0]-2.0;
	// xmax2=mu1JetFposx[0]+2.0;
      
	ymin=mu1JetFposy[0]-0.5;
	ymax=mu1JetFposy[0]+0.5;
	xmin=mu1JetFposx[0]-0.05;
	xmax=mu1JetFposx[0]+0.05;
      
	// ymin2e=mu1JetCposy[0]-8.0;
	// ymax2e=mu1JetCposy[0]+8.0;
	// xmin2e=mu1JetCposx[0]-2.0;
	// xmax2e=mu1JetCposx[0]+2.0;
      
	ymine=mu1JetCposy[0]-0.5;
	ymaxe=mu1JetCposy[0]+0.5;
	xmine=mu1JetCposx[0]-0.05;
	xmaxe=mu1JetCposx[0]+0.05;
      

	for(int j=0;j<Detmu1jetF;j++){
	  sprintf(nameh,"muJetF_pos_muon1_det%d_%d",j,evid);
	  muJetF_pos_muon1[j] = new TH2F(nameh,"",100,xmin2,xmax2,100,ymin2,ymax2);
	  muJetF_pos_muon1[j]->Fill(mu1JetFposx[j],mu1JetFposy[j]);
	
	  sprintf(nameh2,"muJetF_pos_muon1_det%d_%d_zoomin",j,evid);
	  muJetF_pos_muon1_zoomin[j] = new TH2F(nameh2,"",100,xmin,xmax,100,ymin,ymax);
	  muJetF_pos_muon1_zoomin[j]->Fill(mu1JetFposx[j],mu1JetFposy[j]);
	}
      
	for(int j=0;j<Detmu2jetF;j++){
	  sprintf(nameh,"muJetF_pos_muon2_det%d_%d",j,evid);
	  muJetF_pos_muon2[j] = new TH2F(nameh,"",100,xmin2,xmax2,100,ymin2,ymax2);
	  muJetF_pos_muon2[j]->Fill(mu2JetFposx[j],mu2JetFposy[j]);
	
	  sprintf(nameh2,"muJetF_pos_muon2_det%d_%d_zoomin",j,evid);
	  muJetF_pos_muon2_zoomin[j] = new TH2F(nameh2,"",100,xmin,xmax,100,ymin,ymax);
	  muJetF_pos_muon2_zoomin[j]->Fill(mu2JetFposx[j],mu2JetFposy[j]);
	}

	muJetF_pos_muon1_rechit = new TH2F("muJetF_pos_muon1_rechit","",100,xmin2,xmax2,100,ymin2,ymax2);
	muJetF_pos_muon1_rechit_zoomin = new TH2F("muJetF_pos_muon1_rechit_zoomin","",100,xmin,xmax,100,ymin,ymax);
      
	for(int j=0;j<comphitmu1JetF;j++){
	  muJetF_pos_muon1_rechit->Fill(pixelhitmu1JetFx[j],pixelhitmu1JetFy[j]);
	  muJetF_pos_muon1_rechit_zoomin->Fill(pixelhitmu1JetFx[j],pixelhitmu1JetFy[j]);
	  //	    cout<<" hit position x  "<<pixelhitmu1JetCx[j]<<" hit position y  "<<pixelhitmu1JetCy[j]<<endl;
	}
      
	muJetF_pos_muon2_rechit = new TH2F("muJetF_pos_muon2_rechit","",100,xmin2,xmax2,100,ymin2,ymax2);
	muJetF_pos_muon2_rechit_zoomin = new TH2F("muJetF_pos_muon2_rechit_zoomin","",100,xmin,xmax,100,ymin,ymax);
	for(int j=0;j<comphitmu2JetF;j++){
	  muJetF_pos_muon2_rechit->Fill(pixelhitmu2JetFx[j],pixelhitmu2JetFy[j]);
	  muJetF_pos_muon2_rechit_zoomin->Fill(pixelhitmu2JetFx[j],pixelhitmu2JetFy[j]);
	}
      

	for(int j=0;j<Detmu1jetC;j++){
	  sprintf(nameh,"muJetC_pos_muon1_det%d_%d",j,evid);
	  muJetC_pos_muon1[j] = new TH2F(nameh,"",100,xmin2e,xmax2e,100,ymin2e,ymax2e);
	  muJetC_pos_muon1[j]->Fill(mu1JetCposx[j],mu1JetCposy[j]);
	
	  sprintf(nameh2,"muJetC_pos_muon1_det%d_%d_zoomin",j,evid);
	  muJetC_pos_muon1_zoomin[j] = new TH2F(nameh2,"",100,xmine,xmaxe,100,ymine,ymaxe);
	  muJetC_pos_muon1_zoomin[j]->Fill(mu1JetCposx[j],mu1JetCposy[j]);
	}

	for(int j=0;j<Detmu2jetC;j++){
	  sprintf(nameh,"muJetC_pos_muon2_det%d_%d",j,evid);
	  muJetC_pos_muon2[j] = new TH2F(nameh,"",100,xmin2e,xmax2e,100,ymin2e,ymax2e);
	  muJetC_pos_muon2[j]->Fill(mu2JetCposx[j],mu2JetCposy[j]);
	
	  sprintf(nameh2,"muJetC_pos_muon2_det%d_%d_zoomin",j,evid);
	  muJetC_pos_muon2_zoomin[j] = new TH2F(nameh2,"",100,xmine,xmaxe,100,ymine,ymaxe);
	  muJetC_pos_muon2_zoomin[j]->Fill(mu2JetCposx[j],mu2JetCposy[j]);
	}
      
	muJetC_pos_muon1_rechit = new TH2F("muJetC_pos_muon1_rechit","",100,xmin2e,xmax2e,100,ymin2e,ymax2e);
	muJetC_pos_muon1_rechit_zoomin = new TH2F("muJetC_pos_muon1_rechit_zoomin","",100,xmine,xmaxe,100,ymine,ymaxe);
      
	for(int j=0;j<comphitmu1JetC;j++){
	  muJetC_pos_muon1_rechit->Fill(pixelhitmu1JetCx[j],pixelhitmu1JetCy[j]);
	  muJetC_pos_muon1_rechit_zoomin->Fill(pixelhitmu1JetCx[j],pixelhitmu1JetCy[j]);
	  //	    cout<<" hit position x  "<<pixelhitmu1JetCx[j]<<" hit position y  "<<pixelhitmu1JetCy[j]<<endl;
	}
      
	muJetC_pos_muon2_rechit = new TH2F("muJetC_pos_muon2_rechit","",100,xmin2e,xmax2e,100,ymin2e,ymax2e);
	muJetC_pos_muon2_rechit_zoomin = new TH2F("muJetC_pos_muon2_rechit_zoomin","",100,xmine,xmaxe,100,ymine,ymaxe);
	for(int j=0;j<comphitmu2JetC;j++){
	  muJetC_pos_muon2_rechit->Fill(pixelhitmu2JetCx[j],pixelhitmu2JetCy[j]);
	  muJetC_pos_muon2_rechit_zoomin->Fill(pixelhitmu2JetCx[j],pixelhitmu2JetCy[j]);
	}
      
	TLegend *leg = new TLegend(0.6,0.5,0.8,0.9);
	leg->SetBorderSize(0);
	leg->SetFillColor(0);
	leg->SetTextSize(0.036);	  
      
	char legname4[50];
	TCanvas *c3 = new TCanvas("c3","c3",700,500);
	for(int l=0;l<Detmu1jetF;l++){
	  muJetF_pos_muon1[l]->SetFillColor(4+l);
	  if(l==0) muJetF_pos_muon1[l]->Draw("BOX");
	  if(l==0) muJetF_pos_muon1[l]->GetXaxis()->SetTitle("local x position [cm]");
	  if(l==0) muJetF_pos_muon1[l]->GetYaxis()->SetTitle("local y position [cm]");
	  else muJetF_pos_muon1[l]->Draw("BOXsame");
	  //    	sprintf(legname4,"muJetF muon1 Det_%d",l);
	  leg->AddEntry(muJetF_pos_muon1[l], legname4,"P");
	}

	for(int l=0;l<Detmu2jetF;l++){
	  muJetF_pos_muon2[l]->SetLineColor(4+l);
	  if(l==0) muJetF_pos_muon2[l]->Draw("BOXsame");
	  else muJetF_pos_muon2[l]->Draw("BOXsame");
	  //    	sprintf(legname4,"muJetF muon2 Det_%d",l);
	  leg->AddEntry(muJetF_pos_muon2[l], legname4,"L");
	}
      
	muJetF_pos_muon1_rechit->SetFillColor(2);
	muJetF_pos_muon1_rechit->Draw("BOXsame");
      
	muJetF_pos_muon2_rechit->SetFillColor(2);
	muJetF_pos_muon2_rechit->Draw("BOXsame");
      
	//   leg->Draw("same");
      
	char namec5[50];
	sprintf(namec5,"muon_recover_pos/muJetCF/muJetF_2dim_hits_%d.pdf",evid);
	c3->SaveAs(namec5,"recreate");
	c3->Close();


        // TLegend *leg = new TLegend(0.6,0.5,0.8,0.9);
	// leg->SetBorderSize(0);
	// leg->SetFillColor(0);
	// leg->SetTextSize(0.036);	  
      
	char legname5[50];
	TCanvas *c4 = new TCanvas("c4","c4",700,500);
	for(int l=0;l<Detmu1jetF;l++){
	  muJetF_pos_muon1_zoomin[l]->SetFillColor(4+l);
	  if(l==0) muJetF_pos_muon1_zoomin[l]->Draw("BOX");
	  if(l==0) muJetF_pos_muon1_zoomin[l]->GetXaxis()->SetTitle("local x position [cm]");
	  if(l==0) muJetF_pos_muon1_zoomin[l]->GetYaxis()->SetTitle("local y position [cm]");
	  else muJetF_pos_muon1_zoomin[l]->Draw("BOXsame");
	  sprintf(legname5,"muJetF muon1 Det_%d",l);
	  leg->AddEntry(muJetF_pos_muon1[l], legname5,"P");
	}
      
	for(int l=0;l<Detmu2jetF;l++){
	  muJetF_pos_muon2_zoomin[l]->SetLineColor(4+l);
	  if(l==0) muJetF_pos_muon2_zoomin[l]->Draw("BOXsame");
	  else muJetF_pos_muon2_zoomin[l]->Draw("BOXsame");
	  sprintf(legname5,"muJetF muon2 Det_%d",l);
	  leg->AddEntry(muJetF_pos_muon2[l], legname5,"L");
	}
      
	muJetF_pos_muon1_rechit_zoomin->SetFillColor(2);
	muJetF_pos_muon1_rechit_zoomin->Draw("BOXsame");
	muJetF_pos_muon2_rechit_zoomin->SetFillColor(2);
	muJetF_pos_muon2_rechit_zoomin->Draw("BOXsame");
      

	//   leg->Draw("same");
	char namec6[50];
	sprintf(namec6,"muon_recover_pos/muJetCF/muJetF_2dim_hits_%d_zoomin.pdf",evid);
	c4->SaveAs(namec6,"recreate");
	c4->Close();



	TCanvas *c5 = new TCanvas("c5","c5",700,500);
	for(int l=0;l<Detmu1jetC;l++){
	  muJetC_pos_muon1[l]->SetFillColor(4+l);
	  if(l==0) muJetC_pos_muon1[l]->Draw("BOX");
	  if(l==0) muJetC_pos_muon1[l]->GetXaxis()->SetTitle("local x position [cm]");
	  if(l==0) muJetC_pos_muon1[l]->GetYaxis()->SetTitle("local y position [cm]");
	  else muJetC_pos_muon1[l]->Draw("BOXsame");
	  //    	sprintf(legname4,"muJetC muon1 Det_%d",l);
	  leg->AddEntry(muJetC_pos_muon1[l], legname4,"P");
	}

	for(int l=0;l<Detmu2jetC;l++){
	  muJetC_pos_muon2[l]->SetLineColor(4+l);
	  if(l==0) muJetC_pos_muon2[l]->Draw("BOXsame");
	  else muJetC_pos_muon2[l]->Draw("BOXsame");
	  //    	sprintf(legname4,"muJetF muon2 Det_%d",l);
	  leg->AddEntry(muJetC_pos_muon2[l], legname4,"L");
	}
      
	muJetC_pos_muon1_rechit->SetFillColor(2);
	muJetC_pos_muon1_rechit->Draw("BOXsame");
      
	muJetC_pos_muon2_rechit->SetFillColor(2);
	muJetC_pos_muon2_rechit->Draw("BOXsame");
      
	//   leg->Draw("same");
      
	char namec7[50];
	sprintf(namec7,"muon_recover_pos/muJetCF/muJetC_2dim_hits_%d.pdf",evid);
	c5->SaveAs(namec7,"recreate");
	c5->Close();
      
	// TLegend *leg = new TLegend(0.6,0.5,0.8,0.9);
	// leg->SetBorderSize(0);
	// leg->SetFillColor(0);
	// leg->SetTextSize(0.036);	  
      
	char legname6[50];
	TCanvas *c6 = new TCanvas("c6","c6",700,500);
	for(int l=0;l<Detmu1jetC;l++){
	  muJetC_pos_muon1_zoomin[l]->SetFillColor(4+l);
	  if(l==0) muJetC_pos_muon1_zoomin[l]->Draw("BOX");
	  if(l==0) muJetC_pos_muon1_zoomin[l]->GetXaxis()->SetTitle("local x position [cm]");
	  if(l==0) muJetC_pos_muon1_zoomin[l]->GetYaxis()->SetTitle("local y position [cm]");
	  else muJetC_pos_muon1_zoomin[l]->Draw("BOXsame");
	  sprintf(legname6,"muJetC muon1 Det_%d",l);
	  leg->AddEntry(muJetC_pos_muon1[l], legname6,"P");
	}
      
	for(int l=0;l<Detmu2jetC;l++){
	  muJetC_pos_muon2_zoomin[l]->SetLineColor(4+l);
	  if(l==0) muJetC_pos_muon2_zoomin[l]->Draw("BOXsame");
	  else muJetC_pos_muon2_zoomin[l]->Draw("BOXsame");
	  sprintf(legname6,"muJetC muon2 Det_%d",l);
	  leg->AddEntry(muJetC_pos_muon2[l], legname6,"L");
	}
      
	muJetC_pos_muon1_rechit_zoomin->SetFillColor(2);
	muJetC_pos_muon1_rechit_zoomin->Draw("BOXsame");
	muJetC_pos_muon2_rechit_zoomin->SetFillColor(2);
	muJetC_pos_muon2_rechit_zoomin->Draw("BOXsame");
      
	//   leg->Draw("same");
      
	char namec8[50];
	sprintf(namec8,"muon_recover_pos/muJetCF/muJetC_2dim_hits_%d_zoomin.pdf",evid);
	c6->SaveAs(namec8,"recreate");
	c6->Close();
      }
    }
  }

  cout<<"counter F "<<counter_F<<endl;
}




// // TH2F *pixelHit1_pos = new TH2F("pixelHit1_pos","",100,xmin,xmax,100,ymin,ymax);
// // TH2F *pixelHit2_pos = new TH2F("pixelHit2_pos","",100,xmin,xmax,100,ymin,ymax);
// // TH2F *pixelHit3_pos = new TH2F("pixelHit3_pos","",100,xmin,xmax,100,ymin,ymax);
// // TH2F *pixelHit4_pos = new TH2F("pixelHit4_pos","",100,xmin,xmax,100,ymin,ymax);
// // TH2F *pixelHit5_pos = new TH2F("pixelHit5_pos","",100,xmin,xmax,100,ymin,ymax);
// // TH2F *pixelHit6_pos = new TH2F("pixelHit6_pos","",100,xmin,xmax,100,ymin,ymax);
// // TH2F *pixelHit7_pos = new TH2F("pixelHit7_pos","",100,xmin,xmax,100,ymin,ymax);
// // TH2F *pixelHit8_pos = new TH2F("pixelHit8_pos","",100,xmin,xmax,100,ymin,ymax);
// // TH2F *pixelHit9_pos = new TH2F("pixelHit9_pos","",100,xmin,xmax,100,ymin,ymax);
// // TH2F *pixelHit10_pos = new TH2F("pixelHit10_pos","",100,xmin,xmax,100,ymin,ymax);

// // cout<<"  2 dimuons         "<<t->GetEntries("2dimuon==1")<<endl;
// // cout<<"  2 dimuons+hit     "<<t->GetEntries("2dimuon==1&&( (muJetC_hitpix[0]==1||muJetC_hitpix[1]==1)&&(muJetC_hitpix[0]==1||muJetC_hitpix[1]==1) )")<<endl;

// // // t->Scan("muJetC_muon_posx1stpix[0]:muJetC_muon_posz1stpix[0]:muJetC_muon_posx1stpix[1]:muJetC_muon_posz1stpix[1]:comphits_muJetC:pixelhit_muJetC_posx[0]:pixelhit_muJetC_posz[0]:pixelhit_muJetC_posx[1]:pixelhit_muJetC_posz[1]:pixelhit_muJetC_posx[2]:pixelhit_muJetC_posz[2]:pixelhit_muJetC_posx[3]:pixelhit_muJetC_posz[3]:pixelhit_muJetC_posx[4]:pixelhit_muJetC_posz[4]:pixelhit_muJetC_posx[5]:pixelhit_muJetC_posz[5]:pixelhit_muJetC_posx[6]:pixelhit_muJetC_posz[6]","2dimuon==1&&((muJetC_hitpix[0]==0&&muJetC_hitpix[1]==0)||(muJetC_hitpix[0]==0&&muJetC_hitpix[1]==0))","BOX");

// // t->Draw("muJetC_muon_posy1stpix[0]:muJetC_muon_posx1stpix[0]>>muJetC_pos_mu1","event==6675","BOX");
// // t->Draw("muJetC_muon_posy1stpix[1]:muJetC_muon_posx1stpix[1]>>muJetC_pos_mu2","event==6675","BOX");



// // t->Draw("pixelhit_muJetC_posy[0]:pixelhit_muJetC_posx[0]>>pixelHit1_pos","event==6675","BOX");
// // t->Draw("pixelhit_muJetC_posy[1]:pixelhit_muJetC_posx[1]>>pixelHit2_pos","event==6675","BOX");
// // t->Draw("pixelhit_muJetC_posy[2]:pixelhit_muJetC_posx[2]>>pixelHit3_pos","event==6675","BOX");
// // t->Draw("pixelhit_muJetC_posy[3]:pixelhit_muJetC_posx[3]>>pixelHit4_pos","event==6675","BOX");
// // t->Draw("pixelhit_muJetC_posy[4]:pixelhit_muJetC_posx[4]>>pixelHit5_pos","event==6675","BOX");
// // t->Draw("pixelhit_muJetC_posy[5]:pixelhit_muJetC_posx[5]>>pixelHit6_pos","event==6675","BOX");
// // t->Draw("pixelhit_muJetC_posy[6]:pixelhit_muJetC_posx[6]>>pixelHit7_pos","event==6675","BOX");


// // TLegend *leg = new TLegend(0.65,0.5,0.8,0.9);
// // leg->SetBorderSize(0);
// // leg->SetFillColor(0);
// // leg->SetTextSize(0.015);
// // leg->AddEntry(muJetC_pos_mu1,"Extrapolated dimuon position in 1st pixel layer","L");
// // leg->AddEntry(pixelHit1_pos, "compatible Hits in 1st pixel Layer","L");


// // TCanvas *c = new TCanvas("c","c");
// // muJetC_pos_mu1->SetLineColor(4);
// // muJetC_pos_mu2->SetLineColor(4);
// // muJetC_pos_mu2->SetFillColor(4);
// // muJetC_pos_mu1->SetFillColor(4);
// // muJetC_pos_mu1->GetXaxis()->SetTitle("local x position 1stpix [cm]");
// // muJetC_pos_mu1->GetYaxis()->SetTitle("local y position 1stpix [cm]");
// // muJetC_pos_mu1->Draw("BOX");
// // muJetC_pos_mu2->Draw("BOXSAME");

// // pixelHit1_pos->SetLineColor(2);
// // pixelHit1_pos->SetLineWidth(3);
// // pixelHit1_pos->SetFillColor(2);
// // pixelHit1_pos->SetMarkerSize(2);
// // pixelHit1_pos->Draw("BOXSAME");

// // pixelHit2_pos->SetLineColor(2);
// // pixelHit2_pos->SetFillColor(2);
// // pixelHit2_pos->Draw("BOXSAME");

// // pixelHit3_pos->SetLineColor(2);
// // pixelHit3_pos->SetFillColor(2);
// // pixelHit3_pos->Draw("BOXSAME");

// // pixelHit4_pos->SetLineColor(2);
// // pixelHit4_pos->SetFillColor(2);
// // pixelHit4_pos->Draw("BOXSAME");
// //  leg->Draw("same");

// // pixelHit5_pos->SetLineColor(2);
// // pixelHit5_pos->Draw("BOXSAME");

// // pixelHit6_pos->SetLineColor(2);
// // pixelHit6_pos->Draw("BOXSAME");

// // pixelHit7_pos->SetLineColor(2);
// // pixelHit7_pos->Draw("BOXSAME");

// // pixelHit8_pos->SetLineColor(2);
// // pixelHit8_pos->Draw("BOXSAME");

// // pixelHit9_pos->SetLineColor(2);
// // pixelHit9_pos->Draw("BOXSAME");

// // pixelHit10_pos->SetLineColor(2);
// // pixelHit10_pos->Draw("BOXSAME");


