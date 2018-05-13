//Corrected code for dimuon decay mass
#include <iostream>
using namespace std;
#include <algorithm>    // std::max
#include <TH1F.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH2F.h>
#include <TTree.h>
#include <TCut.h>
#include <TGraph.h>
#include "Helpers.h"

void analysis() {

//   TFile *f[20];
//   TTree *t[20];
  char nameFile[50];
  
  Float_t diMuonC_Mass;
  Float_t diMuonF_Mass;
  Bool_t  is1GenMu17;
  Bool_t  is2GenMu8;
  Bool_t  is3GenMu8;
  Bool_t  is4GenMu8;
  
  Bool_t  is1SelMu17;
  Bool_t  is2SelMu8;
  Bool_t  is3SelMu8;
  Bool_t  is4SelMu8;
  
  Bool_t   is2DiMuons;
  Bool_t  is2DiMuonsDzOK;
  Bool_t  is2DiMuonsMassOK;
  
  Bool_t  is2DiMuonHLTFired;
  Bool_t  is2DiMuonsIsoTkOK;
  
  Float_t  genA0_Lxy_rdet;//A0:dark photon that contains the most energetic muon; redt: wrt detector
  Float_t  genA1_Lxy_rdet;
  Float_t  genA0_Lz_rdet;
  Float_t  genA1_Lz_rdet;
  
  Int_t muJetC_hitpix_genTrk[2];
  Int_t muJetF_hitpix_genTrk[2];
  Int_t nrecm;
  
  int counter[20][16];
  Float_t TotEff[20][16];
  Float_t RelEff[20][16];
  Float_t epsvsalph[20]={0.0};
  
  for(int i=0;i<20;i++){
    for(int j=0;j<16;j++){
      counter[i][j]=0;
      TotEff[i][j]=0.0;
      RelEff[i][j]=0.0;
    }
  }

  int nentries;
  
  TFile *f[20];
  TTree *t[20];

  f[0] = new TFile("DarkSUSY_mH_125_mGammaD_0700_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
  f[1] = new TFile("DarkSUSY_mH_125_mGammaD_0700_ctauExp_02_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
  f[2] = new TFile("DarkSUSY_mH_125_mGammaD_0700_ctauExp_05_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
  f[3] = new TFile("DarkSUSY_mH_125_mGammaD_0700_ctauExp_2_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
  f[4] = new TFile("DarkSUSY_mH_125_mGammaD_0700_ctauExp_5_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");


  for(int k=0;k<5;k++){  // loop for samples


    cout<<"  Sample  :  "<<k<<endl;

    //    sprintf(nameFile,"DarkPhoton_mass%iGeV_Lifetime%imm_13TeV.root",i,10*i);
    //    f[k] = new TFile("");
    //    cout<<" nameFile  "<<nameFile<<endl;
    f[k]->cd("cutFlowAnalyzer");
    t[k] = (TTree*)f[k]->Get("cutFlowAnalyzer/Events");
              

    //5) allocate var to branch
    t[k]->SetBranchAddress("diMuonC_FittedVtx_m",&diMuonC_Mass);
    t[k]->SetBranchAddress("diMuonF_FittedVtx_m",&diMuonF_Mass);
    
    t[k]->SetBranchAddress("numrecm",&nrecm);
    
    t[k]->SetBranchAddress("is1GenMu17",&is1GenMu17);
    t[k]->SetBranchAddress("is2GenMu8",&is2GenMu8);
    t[k]->SetBranchAddress("is3GenMu8",&is3GenMu8);
    t[k]->SetBranchAddress("is4GenMu8",&is4GenMu8);
    
    t[k]->SetBranchAddress("is1SelMu17",&is1SelMu17);
    t[k]->SetBranchAddress("is2SelMu8",&is2SelMu8);
    t[k]->SetBranchAddress("is3SelMu8",&is3SelMu8);
    t[k]->SetBranchAddress("is4SelMu8",&is4SelMu8);
    
    t[k]->SetBranchAddress("is2DiMuons",&is2DiMuons);
    t[k]->SetBranchAddress("is2DiMuonsDzOK_FittedVtx",&is2DiMuonsDzOK);
    t[k]->SetBranchAddress("is2DiMuonsMassOK_FittedVtx",&is2DiMuonsMassOK);
    t[k]->SetBranchAddress("isDiMuonHLTFired",&is2DiMuonHLTFired);
    t[k]->SetBranchAddress("is2DiMuonsIsoTkOK_FittedVtx",&is2DiMuonsIsoTkOK);
    
    t[k]->SetBranchAddress("genA0_Lxy_rdet",&genA0_Lxy_rdet);
    t[k]->SetBranchAddress("genA1_Lxy_rdet",&genA1_Lxy_rdet);
    t[k]->SetBranchAddress("genA0_Lz_rdet",&genA0_Lz_rdet);
    t[k]->SetBranchAddress("genA1_Lz_rdet",&genA1_Lz_rdet);
    
    t[k]->SetBranchAddress("selected_hits_diMuonC_1stpix",&muJetC_hitpix_genTrk);
    t[k]->SetBranchAddress("selected_hits_diMuonF_1stpix",&muJetF_hitpix_genTrk);
    

//     // TH1F *hev = new THIF("Event Number","",1000,0.0,1000);  // as it is new variable we must change name
//     //    TH2F *hdimCm = new TH2F("diMuonC_Mass","",500,0.0,1.0,500,0.0,1.0);
//     //7)create loop
    
    nentries = t[k]->GetEntries();
  

    for (int i=0;i<nentries;i++){ // loop for number of events
      t[k]->GetEntry(i);

      cout<<" Event  :  "<<i<<endl;

      counter[k][0]++; 
      
      if(is1GenMu17)counter[k][1]++;
      if(is2GenMu8) counter[k][2]++;
      if(is3GenMu8) counter[k][3]++;
      if(is4GenMu8){
	counter[k][4]++;
	if( (genA0_Lxy_rdet<4.4&&abs(genA0_Lz_rdet)<34.5) && (genA1_Lxy_rdet<4.4&&abs(genA1_Lz_rdet)<34.5)) counter[k][5]++;
      }
      
      //    if(fiddimuon1) counter14++;
      
      //     if(genA1_Lxy_rdet<4.4)counter15++;
      //     if(abs(genA0_Lz_rdet)<34.5)counter16++;
      //     if(abs(genA1_Lz_rdet)<34.5)counter17++;
      
      if(is1SelMu17)counter[k][6]++;
      if(is2SelMu8)counter[k][7]++;
      if(is3SelMu8)counter[k][8]++;
      if(is4SelMu8)counter[k][9]++;
    
      if(is2DiMuons){
	counter[k][10]++;
	if(is2DiMuonsDzOK){
	  counter[k][11]++;
	  if(is2DiMuonsMassOK){
	    counter[k][12]++;
	    if(is2DiMuonHLTFired){
	      counter[k][13]++;
	      if(is2DiMuonsIsoTkOK){
		counter[k][14]++;
		
  		if( (muJetC_hitpix_genTrk[0]==1||muJetC_hitpix_genTrk[1]==1) && 
 		    (muJetF_hitpix_genTrk[0]==1||muJetF_hitpix_genTrk[1]==1)) counter[k][15]++;

//		counter[k][15]++;
	      }
	    }
	  }
	} 
      }
    
      //8)Fill Histogram with event number
      //   hdimCm->Fill(diMuonC_Mass,diMuonF_Mass);
    }
    
    
    RelEff[k][0] = counter[k][0]/(counter[k][0]*1.0);
    for(int m=0;m<16;m++){
      TotEff[k][m]= counter[k][m]/(counter[k][0]*1.0);
      if(m>0){
	if(m==6) RelEff[k][m]= counter[k][m]/(counter[k][0]*1.0);
	else RelEff[k][m]= counter[k][m]/(counter[k][m-1]*1.0);
      }
    }
    

    epsvsalph[k] = counter[k][15]/(counter[k][5]*1.0);

    cout<<" Selection   "<<"  # Events   "<<" Total Efficiency  "<<" Rel. Efficiency "<<endl;
    cout<<" No cut          "<< counter[k][0]<<"      "<< TotEff[k][0]<<"       "<< RelEff[k][0]<<endl;
    cout<<" is1GenMu17      "<< counter[k][1]<<"      "<< TotEff[k][1]<<"       "<< RelEff[k][1]<<endl;
    cout<<" is2GenMu8       "<< counter[k][2]<<"      "<< TotEff[k][2]<<"       "<< RelEff[k][2]<<endl;
    cout<<" is3GenMu8       "<< counter[k][3]<<"      "<< TotEff[k][3]<<"       "<< RelEff[k][3]<<endl;
    cout<<" is4GenMu8       "<< counter[k][4]<<"      "<< TotEff[k][4]<<"       "<< RelEff[k][4]<<endl;
    cout<<" Lxy<4.4&&Lz<34.5 "<< counter[k][5]<<"      "<< TotEff[k][5]<<"       "<< RelEff[k][5]<<endl;
    cout<<"                                                                          "<<endl;
    //  cout<<" genA0_Lxy_rdet   "<< counter14<<"     "<< TotEff14<<"      "<< RelEff14<<endl;
    //  cout<<" genA1_Lxy_rdet   "<< counter15<<"     "<< TotEff15<<"      "<< RelEff15<<endl;
    //  cout<<" genA0_Lz_rdet    "<< counter16<<"     "<< TotEff16<<"      "<< RelEff16<<endl;
    //  cout<<" genA1_Lz_rdet    "<< counter17<<"     "<< TotEff17<<"      "<< RelEff17<<endl;
    //  cout<<"                                                                          "<<endl;
   cout<<" is1SelMu17       "<< counter[k][6]<<"      "<< TotEff[k][6]<<"       "<< RelEff[k][6]<<endl;
    cout<<" is2SelMu8        "<< counter[k][7]<<"      "<< TotEff[k][7]<<"       "<< RelEff[k][7]<<endl;
    cout<<" is3SelMu8        "<< counter[k][8]<<"      "<< TotEff[k][8]<<"       "<< RelEff[k][8]<<endl;
    cout<<" is4SelMu8        "<< counter[k][9]<<"      "<< TotEff[k][9]<<"       "<< RelEff[k][9]<<endl;
    cout<<"                                                                        "<<endl;
    cout<<" is2dimuon         "<< counter[k][10]<<"      "<< TotEff[k][10]<<"       "<< RelEff[k][10]<<endl;
    cout<<" is2DiMuonsDzOK    "<< counter[k][11]<<"     "<< TotEff[k][11]<<"      "<< RelEff[k][11]<<endl;
    cout<<" is2DiMuonsMassOK  "<< counter[k][12]<<"     "<< TotEff[k][12]<<"      "<< RelEff[k][12]<<endl;
    cout<<" is2DiMuonHLTFired "<< counter[k][13]<<"     "<< TotEff[k][13]<<"      "<< RelEff[k][13]<<endl;
    cout<<" is2DiMuonsIsoTkOK "<< counter[k][14]<<"     "<< TotEff[k][14]<<"      "<< RelEff[k][14]<<endl;
    cout<<" is2DiMuonsPixHitOK "<< counter[k][15]<<"     "<< TotEff[k][15]<<"      "<< RelEff[k][15]<<endl;
    cout<<"                                                                        "<<endl;
    cout<<" epsilon_rec/alpha_gen  "<< epsvsalph[k]   <<endl;



  }

  Float_t ctau[5]={0,0.2,0.5,2.0,5.0};

  TGraph *epsvsalp = new TGraph(5,ctau,epsvsalph);

  TH2F *dummy = new TH2F("dummy","dummy",100,-0.1,5.1,100,0.0,1.0);

  TCanvas *c = new TCanvas("c","c",800,600); 
  c->SetGridx();
  c->SetGridy();
  dummy->GetYaxis()->SetTitle("#epsilon/#alpha");
  dummy->GetXaxis()->SetTitle("c#tau [mm]");
  dummy->Draw();
  
  // epsvsalp->GetXaxis()->SetTitle("c#tau [mm]");
  // epsvsalp->GetYaxis()->SetTitle("#epsilon/#alpha");
  //  epsvsalp->Draw("PLSAME");
  // epsvsalp->GetYaxis()->SetRangeUser(0.0,1.0);
  
}



  //
  //
  //2dimuon
  //2dimuonDz0k
  //2DimuonMass0k
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  ////#include <iostream>
  ////using namespace std;
  ////#include <algorithm>    // std::max
  ////#include <TH1F.h>
  ////
  ////void analysis() {
  ////
  ////// 1) accessing ROOT file via TFile command
  ////TFile *f = new TFile("DarkPhoton_mass3GeV_Lifetime10mm_13TeV.root"); 
  //////2) going inside specific folder
  ////f->cd("ana2012");
  //////3) copy tree events in TTree ROOT var
  ////TTree *t = (TTree*)f->Get("ana2012/Events");
  //////4) Defining integer var to store event number
  ////
  ////// Int_t event;  // the name of the variable must coincide with what we are using in t->SetBranchAddress
  //// Float_t diMuonC_Mass;
  //// Float_t diMuonF_Mass;
  //////5) allocate var to branch
  ////t->SetBranchAddress("diMuonC_Mass",&diMuonC_Mass);
  ////t->SetBranchAddress("diMuonC_Mass",&diMuonF_Mass)
  //// TH2F *hdimCm = new TH2F("2Dplot","",500,0.0,1.0,500,0.0,1); //THIF("hist","title",nbins,xlow,xhigh)
  ////
  ////
  //// //7)create loop
  ////int nentries = t->GetEntries();
  ////for (int i=0;i<nentries;i++){
  ////   t->GetEntry(i);
  //////8)Fill Histogram with event number
  ////   hdimCm->Fill(diMuonC_Mass,diMuonF_Mass);
  ////  }
  ////  //9) Define canvas to plot histogram; Draw; Save
  ////  TCanvas *c = new TCanvas("c","c",1000,1000);
  ////  hdimCm->Draw();
  ////  c->SaveAs("2Dplot.pdf","recreate");
  ////  }
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //////2D his example from net that produces 3 histograms
  ////#include <iostream>
  ////using namespace std;
  ////#include <algorithm>    // std::max
  ////#include <TH1F.h>
  ////
  ////void analysis()
  ////{
  ////   TCanvas *c1 = new TCanvas("c1", "c1",900,900);
  ////   gStyle->SetOptStat(0); //creates the info bar up top
  ////   
  ////   // Create the three pads
  ////   TPad *center_pad = new TPad("center_pad", "center_pad",0.0,0.0,0.6,0.6);
  ////   center_pad->Draw();
  ////
  ////   right_pad = new TPad("right_pad", "right_pad",0.55,0.0,1.0,0.6);
  ////   right_pad->Draw();
  ////
  ////   top_pad = new TPad("top_pad", "top_pad",0.0,0.55,0.6,1.0);
  ////   top_pad->Draw();
  ////
  ////   // Create, fill and project a 2D histogram.
  ////   TH2F *h2 = new TH2F("h2","",40,-4,4,40,-20,20);
  ////   Float_t px, py;
  ////   for (Int_t i = 0; i < 25000; i++) {
  ////      gRandom->Rannor(px,py);
  ////      h2->Fill(px,5*py);
  ////   }
  ////   TH1D * projh2X = h2->ProjectionX();
  ////   TH1D * projh2Y = h2->ProjectionY();
  ////
  ////   // Drawing
  ////   center_pad->cd();
  ////   gStyle->SetPalette(1);
  ////   h2->Draw("COL");
  ////
  ////   top_pad->cd();
  ////   projh2X->SetFillColor(kBlue+1);
  ////   projh2X->Draw("bar");
  ////
  ////   right_pad->cd();
  ////   projh2Y->SetFillColor(kBlue-2);
  ////   projh2Y->Draw("hbar");
  ////   
  ////   c1->cd();
  ////   TLatex *t = new TLatex();
  ////   t->SetTextFont(42);
  ////   t->SetTextSize(0.02);
  ////   t->DrawLatex(0.6,0.88,"This example demonstrate how to display");
  ////   t->DrawLatex(0.6,0.85,"a histogram and its two projections.");
  ////}
  //// 
  //
  //
  ////
  ////Corrected code for dimuon decay mass
  //#include <iostream>
  //using namespace std;
  //#include <algorithm>    // std::max
  //#include <TH1F.h>
  //
  //void analysis() {
  //
  //// 1) accessing ROOT file via TFile command
  //TFile *f = new TFile("DarkPhoton_mass3GeV_Lifetime10mm_13TeV.root"); 
  ////2) going inside specific folder
  //f->cd("ana2012");
  ////3) copy tree events in TTree ROOT var
  //TTree *t = (TTree*)f->Get("ana2012/Events");
  ////4) Defining integer var to store event number
  //
  //// Int_t event;  // the name of the variable must coincide with what we are using in t->SetBranchAddress
  // Float_t diMuonC_Mass;
  //
  // 
  ////5) allocate var to branch
  //t->SetBranchAddress("diMuonC_Mass",&diMuonC_Mass);
  //
  ////6) Define the histogram
  //
  //
  //// TH1F *hev = new THIF("Event Number","",1000,0.0,1000);  // as it is new variable we must change name
  // TH2F *hdimCm = new TH2F("diMuonC_Mass","",500,0.0,1.0,500,0.0,9000);
  //
  //
  // //7)create loop
  // int nentries = t->GetEntries();
  //for (int i=0;i<nentries;i++){
  //   t->GetEntry(i);
  ////8)Fill Histogram with event number
  //   hdimCm->Fill(diMuonC_Mass,y);
  //  }
  //  //9) Define canvas to plot histogram; Draw; Save
  //  TCanvas *c = new TCanvas("c","c",500,500);
  //  hdimCm->Draw();
  //  c->SaveAs("DD_C.pdf","recreate");
  //  }
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  ////my code for dimuondecay mass:
  ////#include <iostream>
  ////using namespace std;
  ////#include <algorithm>    // std::max
  ////void analysis() {
  ////
  ////// 1) accessing ROOT file via TFile command
  ////TFile *f = new TFile("DarkPhoton_mass3Gev_Lifetime10mm_13Tev.root"); 
  //////2) going inside specific folder
  ////f->cd("ana2012");
  //////3) copy tree events in TTree ROOT var
  ////TTree *t = (TTree*)f->Get("ana2012/Events");
  //////4) Defining integer var to store event number
  ////Int_t event;
  //////5) allocate var to branch
  ////t->SetBranchAddress("diMuonC_Mass",&diMuonC_Mass);
  //////6) Define the histogram
  ////TH1F *hev = new THIF("Event Number","",1000,0.0,1000);
  //////7)create loop
  ////int nentries = t->GetEntries();
  ////for (int i=0;i<nentries;i++){
  ////   t->GetEntry(i);
  //////8)Fill Histogram with event number
  ////  hev->Fill(event);
  ////  }
  ////  //9) Define canvas to plot histogram; Draw; Save
  ////  TCanvas *c = new TCanvas("c","c");
  ////  hev->Draw();
  ////  c->SaveAs("Dimuondecay_C.pdf",recreate)
  ////  }
  ////Initial code
  //////#include <iostream>
  //////using namespace std;
  //////#include <algorithm>    // std::max
  //////
  ////void analysis(){
  ////  
  ////  
  ////  TFile *f = new TFile("DarkPhoton_mass3GeV_Lifetime10mm_13TeV.root");    // accessing ROOT file and via TFile command
  ////  
  //  f->cd("ana2012");                             // going inside folder ana2012 (where the Tree is located)
  //  
  //  TTree *t = (TTree*)f->Get("ana2012/Events");  // Copy the Tree (Events) in a TTree ROOT variable (t)
  //  
  //  cout<<" Number of events in the ROOT file  "<<t->GetEntries()<<endl;  // prints out the number of events in the Tree
  //  
  //  Int_t event;  // Defining a interger variable to store the event number
  //  t->SetBranchAddress("event",&event); // allocate the variable to the corresponding branch
  //  
  //  
  //  TH1F *hev = new TH1F("Event Number","",1000,0.0,1000);  // Histogram definition
  //  // Loop in the number of events
  //  int nentries = t->GetEntries();         
  //  for(int i=0;i<nentries;i++){
  //    t->GetEntry(i);                          // This is needed at the beginning of the loop to call each event
  //    cout<<" Event Number   "<<event<<endl;   // prints the Event number (for each event)
  //    hev->Fill(event);                        // Fill the histogram with the Event Number
  ////  }
  ////  
  ////  TCanvas *c = new TCanvas("c","c");  // Define the canvas to plot the Histogram
  ////  hev->Draw();                        // Draw the histogram
  ////  c->SaveAs("hev.pdf","recreate");    // Save the histogram to a pdf file
  ////  
  ////}
