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

  TString mass_string;
  TString cT_string;

  //  bool verbose(false);
  bool verbose(true);
  //	TString dirname(fileName);
  TChain* chain = new TChain("dummy");
  TString ext("out_ana_");
  
  decodeFileNameMany(dirNames, mass_string, cT_string);

  TString fileName;
  fileName = "DarkSUSY_mH_125_mGammaD_" + mass_string + "_cT_" + cT_string;
  
  cout<<" Sample   "<<fileName<<endl;
  // add files to the chain
  addfilesMany(chain, dirNames, ext);
  
  //Initialize Variables and counters
  // TFile *f[20]; //A root file is a suit of consecutive data records
  // TTree *t[20]; //comsists of a list of independent branches (Tbranch); one or multiple branches
  char nameFile[50]; //refers to a block of characters?
  
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
  
  Bool_t   is2DiMuons;

  Bool_t  is2DiMuonsFittedVtxOK;
  Bool_t  is2DiMuonsMassOK;
  
  Bool_t  is2DiMuonHLTFired;
  Float_t diMuonC_IsoTk_FittedVtx;
  Float_t  diMuonF_IsoTk_FittedVtx;
  
  Float_t  genA0_Lxy;//A0:dark photon that contains the most energetic muon; redt: wrt detector
  Float_t  genA1_Lxy;
  Float_t  genA0_Lz;
  Float_t  genA1_Lz;
  Float_t  diMuons_dz_FittedVtx;
  
  Int_t  diMuonC_m1_FittedVtx_hitpix_l3inc[2];
  Int_t  diMuonC_m2_FittedVtx_hitpix_l3inc[2];
  Int_t  diMuonF_m1_FittedVtx_hitpix_l3inc[2];
  Int_t  diMuonF_m2_FittedVtx_hitpix_l3inc[2];
  Int_t nRecoMu;
  
  //  int counter[20][17];//samples; selections
  // Float_t TotEff[20][17];
  // Float_t TotEffError[20][17];
  // Float_t RelEff[20][17];
  // Float_t RelEffError[20][17];
  // Float_t epsvsalph1[20]={0.0};
  // Float_t Error[20]={0.0};
  // Float_t epsvsalph2[20]={0.0};
  // Float_t epsvsalph[20]={0.0};
  // Float_t epsvalp[20]={0.0};
  // Float_t epsvalp2[20]={0.0};
  
  TObjArray *fileElements=chain->GetListOfFiles();
  TIter next(fileElements);
  TChainElement *chEl=0;
  
  k++;
  //cout << "p: " << p << endl;
  //if(p == 0 || p%3 == 0) setup(); //reset vectors for every 4th cT for tables.
  
  while ((chEl=(TChainElement*)next())) {  //loopforfiles
    //    if (verbose) std::cout << "running on file " << chEl->GetTitle() << std::endl;
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
		
		//   TFile *f[20];
		//   TTree *t[20];
		
		//   f[0] = new TFile("DarkSUSY_mH_125_mGammaD_0700_8TeV-madgraph452_bridge224_LHE_pythia6537p4_PAT_v1_10000.root");
//   f[1] = new TFile("DarkSUSY_mH_125_mGammaD_0700_ctauExp_02_8TeV-madgraph452_bridge224_LHE_pythia6_5374_PAT_v1_10000.root");
		//   f[2] = new TFile("DarkSUSY_mH_125_mGammaD_0700_ctauExp_05_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
		//   f[3] = new TFile("DarkSUSY_mH_125_mGammaD_0700_ctauExp_2_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
		//   f[4] = new TFile("DarkSUSY_mH_125_mGammaD_0700_ctauExp_5_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
		//   f[5] = new TFile("DarkSUSY_mH_125_mGammaD_0250_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
		//   f[6] = new TFile("DarkSUSY_mH_125_mGammaD_0250_ctauExp_005_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
		//   f[7] = new TFile("DarkSUSY_mH_125_mGammaD_0250_ctauExp_01_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
		//   f[8] = new TFile("DarkSUSY_mH_125_mGammaD_0250_ctauExp_02_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
		//   f[9] = new TFile("DarkSUSY_mH_125_mGammaD_0250_ctauExp_05_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
		//   f[10] = new TFile("DarkSUSY_mH_125_mGammaD_0250_ctauExp_1_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
		//   f[11] = new TFile("DarkSUSY_mH_125_mGammaD_0250_ctauExp_2_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
		//   f[12] = new TFile("DarkSUSY_mH_125_mGammaD_0250_ctauExp_3_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
		//   f[13] = new TFile("DarkSUSY_mH_125_mGammaD_0250_ctauExp_5_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
		//   f[14] = new TFile("ana.root");
	//   f[15] = new TFile("out_ana_reco.root");
	// 5) allocate var to branch
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
		
		t->SetBranchAddress("is2DiMuons",&is2DiMuons);
		t->SetBranchAddress("is2DiMuonsFittedVtxOK",&is2DiMuonsFittedVtxOK);
		t->SetBranchAddress("diMuons_dz_FittedVtx",&diMuons_dz_FittedVtx);
		t->SetBranchAddress("is2DiMuonsMassOK_FittedVtx",&is2DiMuonsMassOK);
		t->SetBranchAddress("isDiMuonHLTFired",&is2DiMuonHLTFired);
		t->SetBranchAddress("diMuonC_IsoTk_FittedVtx",&diMuonC_IsoTk_FittedVtx);
		t->SetBranchAddress("diMuonF_IsoTk_FittedVtx",&diMuonF_IsoTk_FittedVtx);
		t->SetBranchAddress("genA0_Lxy",&genA0_Lxy);
		t->SetBranchAddress("genA1_Lxy",&genA1_Lxy);
		t->SetBranchAddress("genA0_Lz",&genA0_Lz);
		t->SetBranchAddress("genA1_Lz",&genA1_Lz);
		
		t->SetBranchAddress("diMuonC_m1_FittedVtx_hitpix_l3inc",&diMuonC_m1_FittedVtx_hitpix_l3inc);
		t->SetBranchAddress("diMuonC_m2_FittedVtx_hitpix_l3inc",&diMuonC_m2_FittedVtx_hitpix_l3inc);
		t->SetBranchAddress("diMuonF_m1_FittedVtx_hitpix_l3inc",&diMuonF_m1_FittedVtx_hitpix_l3inc);
		t->SetBranchAddress("diMuonF_m2_FittedVtx_hitpix_l3inc",&diMuonF_m2_FittedVtx_hitpix_l3inc);
		
		// TH1F *hev = new THIF("Event Number","",1000,0.0,1000);  // as it is new variable we must change name
		//    TH2F *hdimCm = new TH2F("diMuonC_Mass","",500,0.0,1.0,500,0.0,1.0);
		//7)create loop
		
		nentries = t->GetEntries(); //no of entries
		
		for(int i=0;i<nentries;i++){ //loop for number of events
		  t->GetEntry(i);
		  counter[k][0]++;
		  // cout<<" dimuonC_Iso  "<<diMuonC_IsoTk_FittedVtx<<endl;
		  // cout<<" dimuonF_Iso  "<<diMuonF_IsoTk_FittedVtx<<endl;
		  
		  counter[k][0]++; 
		  
		  if(is1GenMu17)counter[k][1]++;
		  if(is2GenMu8) counter[k][2]++;
		  if(is3GenMu8) counter[k][3]++;
		  if(is4GenMu8){
		    counter[k][4]++;
		    if( (genA0_Lxy<4.4&&abs(genA0_Lz)<34.5) && (genA1_Lxy<4.4&&abs(genA1_Lz)<34.5)) counter[k][5]++;
		  }
		  
		  if(is1SelMu17)counter[k][6]++;
		  if(is2SelMu8)counter[k][7]++;
		  if(is3SelMu8)counter[k][8]++;
		  if(is4SelMu8)counter[k][9]++;
		  
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
		// 8)Fill Histogram with event number
		// hdimCm->Fill(diMuonC_Mass,diMuonF_Mass);
	    
		
		RelEff[k][0] = counter[k][0]/(counter[k][0]*1.0);
		for(int m=0;m<17;m++){
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
		
	  
		epsvsalph[k] = counter[k][15]/(counter[k][5]*1.0);
		cout<<" mass  "<<mass_string<<" cT  "<<cT_string<<endl;
		cout<<" epsvsalph[k]  "<<epsvsalph[k]<<endl;
		// cout<<" counter[k][5]  "<<counter[k][5]*1.0<<endl;
		Err[k]=   sqrt( (epsvsalph[k]*(1-epsvsalph[k]))/(counter[k][5]*1.0)); 
		cout<<"        "<<endl;
		cout<<"begin{landscape}"<<endl;
		cout<<"centering"<<endl;
		cout<<"begin{tabular}{ c| c | c | c | c | c }"<<endl;
		
		cout<<" Selection   "<<" \\# Events   "<<"   Total Efficiency  "<<" Relative Efficiency   "<<" TotalEffError   "<<" RelEffError "<<" hline "<<endl;
		 
		cout<<" No cut      &   "<<left<< setw(7)<< counter[k][0]<<"     &   "<<fixed<< std::setprecision(3)<< TotEff[k][0]<<"         &     "<< RelEff[k][0]<<"           &   "<<left<< setw(7)<< TotEffErr[k][0]<<"      &   "<< RelEffErr[k][0]<<" hline "<<endl;         
		cout<<" is1GenMu17  &   "<<left<< setw(7)<< counter[k][1]<<"    &    "<<left<< setw(7)<< TotEff[k][1]<<"      &        "<<left<< setw(7)<<  RelEff[k][1]<<"    &    "<<fixed<<std::setprecision(3)<< TotEffErr[k][1]<<" &   "<<left<< setw(7)<<  RelEffErr[k][1]<<" hline "<<endl;
		cout<<" is2GenMu8   &   "<<left<< setw(7)<< counter[k][2]<<"    &    "<<left<< setw(7)<< TotEff[k][2]<<"      &        "<<left<< setw(7)<<  RelEff[k][2]<<"    &     "<<left<< setw(7)<<  TotEffErr[k][2]<<" & "<<left<< setw(7)<< RelEffErr[k][2]<<" hline "<<endl;
		cout<<" is3GenMu8   &   "<<left<< setw(7)<< counter[k][3]<<"    &    "<<left<< setw(7)<< TotEff[k][3]<<"      &        "<<left<< setw(7)<<  RelEff[k][3]<<"    &     "<<left<< setw(7)<<  TotEffErr[k][3]<<" & "<<left<< setw(7)<<  RelEffErr[k][3]<<" hline "<<endl;
		cout<<" is4GenMu8   &   "<<left<< setw(7)<< counter[k][4]<<"    &    "<<left<< setw(7)<< TotEff[k][4]<<"      &        "<<left<< setw(7)<<  RelEff[k][4]<<"    &     "<<left<< setw(7)<<  TotEffErr[k][4]<<" & "<<left<< setw(7)<<  RelEffErr[k][4]<<" hline "<<endl;
		
		cout<<" Lxy<4.4&& Lz<34.5 & "<<left<< setw(7)<< counter[k][5]<<"  &  "<<left<< setw(7)<<  TotEff[k][5]<<"     &     "<<left<< setw(7)<<  RelEff[k][5]<<"       &    "<<fixed<<std::setprecision(4) << TotEffErr[k][5]<<" &   "<<fixed<<std::setprecision(3) << RelEffErr[k][5]<<" hline "<<endl;
		cout<<"                                                                          "<<" hline "<<endl;
		
		cout<<" is1SelMu17   &    "<<left<< setw(7)<< counter[k][6]<<"  &    "<<left<< setw(7)<< TotEff[k][6] <<setw(10)<<"   &    "<<left<< setw(7)<<  RelEff[k][6]<<"  &    "<<left<< setw(7)<<  TotEffErr[k][6]<<" &  " <<  RelEffErr[k][6]<<" hline "<<endl;
		cout<< setprecision(3);
		cout<<" is2SelMu8    &    "<< counter[k][7]<<"  &    "<< TotEff[k][7] <<setw(10)<<"   &   "<< RelEff[k][7]<<"   &   "<< TotEffErr[k][7]<<"  & "<< RelEffErr[k][7]<<" hline "<<endl;                                
		cout<<" is3SelMu8    &    "<< counter[k][8]<<"  &    "<< TotEff[k][8]<<"   &    "<< RelEff[k][8]<<"   &   "<< TotEffErr[k][8]<<" &  "<< RelEffErr[k][8]<<" hline "<<endl;
		cout<<" is4SelMu8    & "<<setw(7)<<"   "<< counter[k][9]<<setw(10)<<" & "<< TotEff[k][9]<<"   &    "<< RelEff[k][9]<<"   &   "<< TotEffErr[k][9]<<" &  "<< RelEffErr[k][9]<<" hline "<<endl;   
		cout<<"                                                                        "<<" hline "<<endl;
		cout<<" is2dimuon    &    "<< counter[k][10]<<" &    "<< TotEff[k][10]<<"  &    "<< RelEff[k][10]<<"  &   "<< TotEffErr[k][10]<<"&  "<< RelEffErr[k][10]<<" hline "<<endl;  
		
		cout<<" is2DiMuonsFittedVtx  &  "<< counter[k][11]<<" &    "<< TotEff[k][11]<<" &     "<< RelEff[k][11]<<" &   "<<fixed<<std::setprecision(4) << TotEffErr[k][11]<<" &  "<<fixed<<std::setprecision(3) << RelEffErr[k][11]<<" hline "<<endl;                                
		cout<<" is2DiMuonsFittedDz &  "<< counter[k][12]<<" &    "<< TotEff[k][12]<<" &     "<< RelEff[k][12]<<" &   "<<fixed<<std::setprecision(4) << TotEffErr[k][12]<<" &  "<<fixed<<std::setprecision(3) << RelEffErr[k][12]<<" hline "<<endl;                                
		cout<<" is2DiMuonsMassOK &  "<< counter[k][13]<<" &    "<< TotEff[k][13]<<" &     "<< RelEff[k][13]<<" &   "<<fixed<<std::setprecision(4) << TotEffErr[k][13]<<" &  "<<fixed<<std::setprecision(3) << RelEffErr[k][13]<<" hline "<<endl;                              
		cout<<" is2DiMuonHLTFired & "<< counter[k][14]<<" &    "<< TotEff[k][14]<<" &     "<< RelEff[k][14]<<" &   "<<fixed<<std::setprecision(4) << TotEffErr[k][14]<<" &   "<<fixed<<std::setprecision(3) << RelEffErr[k][14]<<" hline "<<endl;
		cout<<" is2DiMuonsIsoTkOK & "<< counter[k][15] <<" &    "<< TotEff[k][15]<<" &     "<< RelEff[k][15]<<" &   "<<fixed<<std::setprecision(4) << TotEffErr[k][15]<<" &   " <<fixed<<std::setprecision(3) << RelEffErr[k][15]<<" hline "<<endl;                          
		cout<<" is2DiMuonsPixHitOK & "<< counter[k][16] <<"    &   "<< TotEff[k][16]<<"   &    "<< RelEff[k][16]<<"   &   "<<fixed<<std::setprecision(4) << TotEffErr[k][16]<<"   &   " <<fixed<<std::setprecision(3) << RelEffErr[k][16]<<" hline "<<endl;                                   
 
		cout
		  <<"                                                           "<<" hline "<<endl;
		cout<<" epsilon_rec/alpha_gen  & "<< epsvsalph[k]<<"$\\pm$ "<< Err[k]<<" hline "<<endl;
		
		cout<<"end{tabular}"<<endl;
		cout<<"end{landscape}"<<endl;
	         
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
  // //	cout << "Vector Created" << endl;
  readTextFileWithSamples(txtfile, DarkSUSY_mH_125_mGammaD_v);
  // //	cout << "Samples read" << endl;
  for(auto v: DarkSUSY_mH_125_mGammaD_v) efficiency(v);
  // //	cout << "For Loop completes" << endl;
  
}


