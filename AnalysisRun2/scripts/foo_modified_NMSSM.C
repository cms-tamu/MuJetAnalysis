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

Float_t counter[20][18];//samples; selections
Float_t TotEff[20][18];
Float_t TotEffErr[20][18];
Float_t RelEff[20][18];
Float_t RelEffErr[20][18];
Float_t epsvsalph1[20]={0.0};
Float_t Err[20]={0.0};
Float_t epsvsalph2[20]={0.0};
Float_t epsvsalph[20]={0.0};
Float_t epsvalp[20]={0.0};
Float_t epsvalp2[20]={0.0};

double calc_eff(double num, double denom)
{
  //eff = num/denom;
  double eff_uncert = sqrt( ( (num/denom)*(1-(num/denom) ) )/denom );
  return eff_uncert;
}

void printLine(std::string word, int n1, float n2, float n3, float n4, float n5){
  cout<< word << " &   "<< left << setw(7) 
      << "$"<<int(n1)<<"$     &   "<<fixed<< std::setprecision(3)<< "$"<<n2<<"\\pm"<<n3<<"$         &     $"<< n4<<" \\pm " << n5<<"$ \\\\"<<endl;         
}


void printLine(std::string word){
  cout<< word <<"\\\\"<<endl;         
}


void printLine(int n1, float n2, float n3, float n4, float n5){
  cout<< left << setw(7) 
      << "$"<<int(n1)<<"$     &   "<<fixed<< std::setprecision(3)<< "$"<<n2<<"\\pm"<<n3<<"$         &     $"<< n4<<" \\pm " << n5<<"$ \\\\"<<endl;         
}

void printHeader()
{
  string cutsgen[6]={"All events",
		     "$p_{T_1} > 17~\\gev$ , $|\\eta|< 0.9$",
		     "$p_{T_2} > 8~\\gev$ , $|\\eta|< 2.4$",
		     "$p_{T_3} > 8~\\gev$ , $|\\eta|< 2.4$",
		     "$p_{T_4} > 8~\\gev$ , $|\\eta|< 2.4$",
		     "$L_{xy}<9.8~\\mathrm{cm}$ and $L_z<46.5~\\mathrm{cm}$"};
  string cutsrec[4+8]={"$p_{T_1} > 17~\\gev$ , $|\\eta|< 0.9$",
		       "$p_{T_2} > 8~\\gev$ , $|\\eta|< 2.4$",
		       "$p_{T_3} > 8~\\gev$ , $|\\eta|< 2.4$",
		       "$p_{T_4} > 8~\\gev$ , $|\\eta|< 2.4$",
		       "Good primary vertex",
		       "Two muon-jets",
		       "Two dimuons",
		       "Pixel hit requirement",
		       "$|z_{\\mu\\mu_1} - z_{\\mu\\mu_2}|<0.1~\\mathrm{cm}$",
		       "$m_{\\mu\\mu_1} \\approx m_{\\mu\\mu_2}$",
		       "Dimuon isolation $<2~\\gev$",
		       "Trigger"
  };
  cout<<"\\caption{Acceptances and efficiencies of the event selection requirements for several representative dark SUSY benchmark models in MC simulation."<<endl;
  cout<<"\\begin{tabular}{ |l|}"<<endl;
  
  cout<<"\\hline"<<endl;
  cout<<" Sample  "<<"\\\\ \\hline \\hline"<<endl;
  cout<<" Selection  "<<"\\\\ \\hline "<<endl;
  cout<<" All events  "<<"\\\\ \\hline "<<endl;
  cout << "\\multicolumn{1}{|l|}{\\textbf{Basic GEN level selections}} \\\\"<<endl;
  cout << "\\hline" << endl;
  for (int i=1; i<=5; i++)
    printLine(cutsgen[i]);
  cout << "\\hline" << endl;
  cout << "\\multicolumn{1}{|l|}{\\textbf{Basic RECO level selections}} \\\\"<<endl;
  cout << "\\hline" << endl;
  for (int i=0; i<=3; i++)
    printLine(cutsrec[i]);
  cout << "\\hline" << endl;
  cout << "\\multicolumn{1}{|l|}{\\textbf{Extra RECO level selections}} \\\\"<<endl;
  cout << "\\hline" << endl;
  for (int i=0; i<=7; i++)
    printLine(cutsrec[i+4]);
  cout << "\\hline" << endl;
  cout<<"$\\alpha_{\\mathrm{GEN}}$" <<" \\\\ "<<endl;
  cout<<"$\\epsilon_{\\mathrm{SIM}}$"<<" \\\\ \\hline "<<endl;
  cout<<"$\\epsilon_{\\mathrm{SIM}}/\\alpha_{\\mathrm{GEN}}$"<<" \\\\ \\hline "<<endl;
  cout<<"\\end{tabular}"<<endl;
  cout<<"\\end{table}"<<endl;

}

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
}

int k = -1;
void efficiency(const std::vector<std::string>& dirNames)
{

  TString mH_string;
  TString mA_string;

  //  bool verbose(false);
  bool verbose(false);
  //	TString dirname(fileName);
  TChain* chain = new TChain("dummy");
  TString ext("out_ana_");
  
  if (dirNames.size()==0) return;

  cout<<" dirNames  "<<dirNames[0]<<endl;
  decodeFileNMSSMNameMany(dirNames, mH_string, mA_string);

  TString fileName;
  fileName = "NMSSM_mH_" + mH_string + "_mA_" + mA_string;
  
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
  
  Float_t selMu0_pT;
  Float_t selMu1_pT;
  Float_t selMu2_pT;
  Float_t selMu3_pT;

  Float_t massC;
  Float_t massF;
 
  Float_t selMu0_eta;
  Float_t selMu1_eta;
  Float_t selMu2_eta;
  Float_t selMu3_eta;

  Bool_t  is2DiMuons;
  Bool_t  is2MuJets;
  Bool_t  isVtxOK;

  Bool_t  is2DiMuonsFittedVtxOK;
  Bool_t  is2DiMuonsMassOK;
  
  Bool_t  is2DiMuonHLTFired;
  Float_t diMuonC_IsoTk_FittedVtx;
  Float_t diMuonF_IsoTk_FittedVtx;
  
  Float_t  genA0_Lxy;//A0:dark photon that contains the most energetic muon; redt: wrt detector
  Float_t  genA1_Lxy;
  Float_t  genA0_Lz;
  Float_t  genA1_Lz;
  Float_t  diMuons_dz_FittedVtx;
  
  Int_t  diMuonC_m1_FittedVtx_hitpix_l3inc;
  Int_t  diMuonC_m2_FittedVtx_hitpix_l3inc;
  Int_t  diMuonF_m1_FittedVtx_hitpix_l3inc;
  Int_t  diMuonF_m2_FittedVtx_hitpix_l3inc;
  Int_t  nRecoMu;


  TH1F *diMuons_dz = new TH1F("diMuons_dz","",100,-1.0,1.0);

  TH1F *P_t_Mu0 = new TH1F("P_t_Mu0","",200,0.0,100.0);   
  TH1F *P_t_Mu1 = new TH1F("P_t_Mu1","",200,0.0,100.0); 
  TH1F *P_t_Mu2 = new TH1F("P_t_Mu2","",200,0.0,100.0); 
  TH1F *P_t_Mu3 = new TH1F("P_t_Mu3","",200,0.0,100.0); 
  
  TH1F *mass_C= new TH1F("mass_C","",200,0.0,1.0);
  TH1F *mass_F= new TH1F("mass_F","",200,0.0,1.0);

  TH1F *iso_C = new TH1F("iso_C","",200,0.0,10.0);
  TH1F *iso_F = new TH1F("iso_F","",200,0.0,10.0);

  TH1F *eta_Mu0 = new TH1F("eta_Mu0","",100,-2.5,2.5);
  TH1F *eta_Mu1 = new TH1F("eta_Mu1","",100,-2.5,2.5);
  TH1F *eta_Mu2 = new TH1F("eta_Mu2","",100,-2.5,2.5);
  TH1F *eta_Mu3 = new TH1F("eta_Mu3","",100,-2.5,2.5);

  TObjArray *fileElements=chain->GetListOfFiles();
  TIter next(fileElements);
  TChainElement *chEl=0;
  
  k++;
  //cout << "p: " << p << endl;
  //if(p == 0 || p%3 == 0) setup(); //reset vectors for every 4th cT for tables.
  
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
     
     //   TFile *f[20];
     //   TTree *t[20];
		
     //   f[0] = new TFile("NMSSM_0700_8TeV-madgraph452_bridge224_LHE_pythia6537p4_PAT_v1_10000.root");
     //   f[1] = new TFile("NMSSM_0700_ctauExp_02_8TeV-madgraph452_bridge224_LHE_pythia6_5374_PAT_v1_10000.root");
     //   f[2] = new TFile("NMSSM_0700_ctauExp_05_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
     //   f[3] = new TFile("NMSSM_0700_ctauExp_2_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
     //   f[4] = new TFile("NMSSM_0700_ctauExp_5_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
     //   f[5] = new TFile("NMSSM_0250_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
     //   f[6] = new TFile("NMSSM_0250_ctauExp_005_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
     //   f[7] = new TFile("NMSSM_0250_ctauExp_01_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
     //   f[8] = new TFile("NMSSM_0250_ctauExp_02_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
     //   f[9] = new TFile("NMSSM_0250_ctauExp_05_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
     //   f[10] = new TFile("NMSSM_0250_ctauExp_1_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
     //   f[11] = new TFile("NMSSM_0250_ctauExp_2_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
     //   f[12] = new TFile("NMSSM_0250_ctauExp_3_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
     //   f[13] = new TFile("NMSSM_0250_ctauExp_5_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1_10000.root");
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
     t->SetBranchAddress("isVertexOK",&isVtxOK);
     t->SetBranchAddress("is2DiMuons",&is2DiMuons);
     t->SetBranchAddress("is2MuJets",&is2MuJets);
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
       
       if(is1GenMu17)counter[k][1]++;
       if(is2GenMu8) counter[k][2]++;
       if(is3GenMu8) counter[k][3]++;
       if(is4GenMu8){
	 counter[k][4]++;
	 if( (genA0_Lxy<9.8&&fabs(genA0_Lz)<46.5) && (genA1_Lxy<9.8&&fabs(genA1_Lz)<46.5)) counter[k][5]++;
	 //if( (genA0_Lxy<9.8&&fabs(genA0_Lz)<48.5) && (genA1_Lxy<9.8&&fabs(genA1_Lz)<48.5)) counter[k][5]++;
       }
       
       if(is1SelMu17)counter[k][6]++;
       if(is2SelMu8)counter[k][7]++;
       if(is3SelMu8)counter[k][8]++;
       if(is4SelMu8){
	 counter[k][9]++;
	 
	 if(isVtxOK){
	   counter[k][10]++;
	   if(is2MuJets){
	     counter[k][11]++;
	     if(is2DiMuons){

	       diMuons_dz->Fill(diMuons_dz_FittedVtx);
	       counter[k][12]++;
	       if( (diMuonC_m1_FittedVtx_hitpix_l3inc==1||diMuonC_m2_FittedVtx_hitpix_l3inc==1) &&
		   (diMuonF_m1_FittedVtx_hitpix_l3inc==1||diMuonF_m2_FittedVtx_hitpix_l3inc==1)){
		 counter[k][13]++;
		 if( fabs(diMuons_dz_FittedVtx)<0.1){
		   counter[k][14]++;
		   if(is2DiMuonsMassOK){
		     counter[k][15]++;
		     if(diMuonC_IsoTk_FittedVtx<2.0 && diMuonF_IsoTk_FittedVtx<2.0){
		       counter[k][16]++;
		       if(is2DiMuonHLTFired){
			 counter[k][17]++;
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
     myfile->Close();
  }
  
  // 8)Fill Histogram with event number
  // hdimCm->Fill(diMuonC_Mass,diMuonF_Mass);
  // cout<<"  Here is where the plotting starts  "<<endl;
  // cout<<"  Here is where the plotting starts  "<<endl;
 
  // TCanvas *c = new TCanvas("c","c",800,600);
  // diMuons_dz->Draw();
  // c->SaveAs("diMuons_dz.png","recreate");

 //  TCanvas *cc = new TCanvas("cc","cc",800,600);
 //  mass_C->Draw();
 //  cc->SaveAs("massC.png","recreate");

 //  TCanvas *cf = new TCanvas("cf","cf",800,600);
 //  mass_F->Draw();
 //  cf->SaveAs("massF.png","recreate");
 
 //  TCanvas *e = new TCanvas("e","e",800,600);
 //  eta_Mu0->Draw();
 //  e->SaveAs("e0.png","recreate");

 //  TCanvas *e1 = new TCanvas("e1","e1",800,600);
 //  eta_Mu0->Draw();
 //  e1->SaveAs("e1.png","recreate");

 //  TCanvas *e2 = new TCanvas("e2","e2",800,600);
 // eta_Mu0->Draw();
 // e2->SaveAs("e2.png","recreate");
 
 // TCanvas *e3 = new TCanvas("e3","e3",800,600);
 // eta_Mu0->Draw();
 // e3->SaveAs("e3.png","recreate");

 // TCanvas *isoC = new TCanvas("isoC","isoC",800,600);
 // iso_C->Draw();
 // isoC->SaveAs("isoC.png","recreate");

 // TCanvas *isoF = new TCanvas("isoF","isoF",800,600);
 // iso_C->Draw();
 // isoF->SaveAs("isoF.png","recreate");

 // TCanvas *c = new TCanvas("c","c",800,600);
 //  P_t_Mu0->Draw();
 //  c->SaveAs("pt_mu0.png","recreate");

 //  TCanvas *c1 = new TCanvas("c1","c1",800,600);
 //  P_t_Mu1->Draw();
 //  c1->SaveAs("pt_mu1x.png","recreate");
  
 //  TCanvas *c2 = new TCanvas("c2","c2",800,600);
 //  P_t_Mu2->Draw();
 //  c2->SaveAs("pt_mu2.png","recreate");

 //  TCanvas *c3 = new TCanvas("c3","c3",800,600);
 //  P_t_Mu3->Draw();
 //  c3->SaveAs("pt_mu3.png","recreate");

  RelEff[k][0] = counter[k][0]/(counter[k][0]*1.0);
  for(int m=0;m<18;m++){
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
  

  float alpha_gen = counter[k][5]/(counter[k][0]*1.0);
  float alpha_gen_err = sqrt( (alpha_gen*(1-alpha_gen))/(counter[k][0]*1.0));
  cout << "alpha_gen_err " << alpha_gen_err << endl;

  float reco_sim = counter[k][17]/(counter[k][0]*1.0);
  float reco_sim_err = sqrt( (reco_sim*(1-reco_sim))/(counter[k][0]*1.0));
  cout << "reco_sim_err " << reco_sim_err << endl;

  epsvsalph[k] = reco_sim/alpha_gen;
  Err[k]= sqrt( ( epsvsalph[k] * (1-epsvsalph[k]) ) / counter[k][5] );

// calc_eff(reco_sim, alpha_gen);

  cout<<" mass  "<<mH_string<<" cT  "<<mA_string<<endl;
  cout<<" TotEff "<<counter[k][17]/(counter[k][0]*1.0)<<endl;
  // cout<<" epsvsalph[k]  "<<epsvsalph[k]<<endl;

  string cutsgen[6]={"All events",
		     "$p_{T_1} > 17$ GeV, $|\\eta|< 0.9$",
		     "$p_{T_2} > 8$ GeV, $|\\eta|< 2.4$",
		     "$p_{T_3} > 8$ GeV, $|\\eta|< 2.4$",
		     "$p_{T_4} > 8$ GeV, $|\\eta|< 2.4$",
		     "$L_{xy}<9.8~\\mathrm{cm}$ and $L_z<46.5~\\mathrm{cm}$"};
  string cutsrec[4+8]={"$p_{T_1} > 17$ GeV, $|\\eta|< 0.9$",
		       "$p_{T_2} > 8$ GeV, $|\\eta|< 2.4$",
		       "$p_{T_3} > 8$ GeV, $|\\eta|< 2.4$",
		       "$p_{T_4} > 8$ GeV, $|\\eta|< 2.4$",
		       "Good primary vertex",
		       "Two muon-jets",
		       "Two dimuons",
		       "Pixel hit requirement",
		       "$|z_{\\mu\\mu_1} - z_{\\mu\\mu_2}|<0.1~\\mathrm{cm}$",
		       "$m_{\\mu\\mu_1} \\approx m_{\\mu\\mu_2}$",
		       "Dimuon isolation $<2~\\mathrm{GeV}$",
		       "Trigger"
  };
  // printHeader();


  // cout<<"\\caption{Acceptances and efficiencies of the event selection requirements for dark photon m="<<mH_string<<" and ctau="<<mA_string<<"}  "<<endl;
  // cout<<"\\centering "<<endl;
  cout<<"\\begin{tabular}{ |c|c|c|}"<<endl;
  cout << "\\hline" << endl;
  cout<<"\\multicolumn{3}{c|}{$m_{H} = "<<mH_string<<"~\\gev$, $m_{A} = "<< mA_string<<"~\\gev$} \\\\ \\hline \\hline"<<endl;  
  cout<<" Events &  "<<"   Tot. Eff. [\\%]  & "<<" Rel. Eff. [\\%] "<<"\\\\ \\hline"<<endl;
  printLine(counter[k][0], TotEff[k][0], TotEffErr[k][0], RelEff[k][0], RelEffErr[k][0]);
  cout << "\\hline" << endl;
  cout << "\\multicolumn{3}{|l|}{} \\\\"<<endl;
  cout << "\\hline" << endl;
  for (int i=1; i<=5; i++)
    printLine(counter[k][i], TotEff[k][i], TotEffErr[k][i], RelEff[k][i], RelEffErr[k][i]);
  cout << "\\hline" << endl;
  cout << "\\multicolumn{3}{|l|}{} \\\\"<<endl;
  cout << "\\hline" << endl;
  for (int i=0; i<=3; i++)
    printLine(counter[k][i+6], TotEff[k][i+6], TotEffErr[k][i+6], RelEff[k][i+6], RelEffErr[k][i+6]);
  cout << "\\hline" << endl;
  cout << "\\multicolumn{3}{|l|}{} \\\\"<<endl;
  cout << "\\hline" << endl;
  for (int i=0; i<=7; i++)
    printLine(counter[k][i+10], TotEff[k][i+10], TotEffErr[k][i+10], RelEff[k][i+10], RelEffErr[k][i+10]);
  cout << "\\hline" << endl;
  cout<<"\\multicolumn{3}{r|}{$"  << alpha_gen<<"\\pm "<< alpha_gen_err<<"$} \\\\ "<<endl;
  cout<<"\\multicolumn{3}{r|}{$"  << reco_sim<<"\\pm "<< reco_sim_err<<"$} \\\\ \\hline "<<endl;
  cout<<"\\multicolumn{3}{r|}{$"  << epsvsalph[k]<<"\\pm "<< Err[k]<<"$} \\\\ \\hline "<<endl;
  cout<<"\\end{tabular}"<<endl;




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

 

void foo_modified_NMSSM()
{
  setup();
  std::string samples[] = { 
    "NMSSM_mH_90_mA_0p25.txt",
    "NMSSM_mH_90_mA_0p5.txt",
    "NMSSM_mH_90_mA_0p75.txt",
    "NMSSM_mH_90_mA_1.txt",
    "NMSSM_mH_90_mA_2.txt",
    "NMSSM_mH_90_mA_3.txt",
    "NMSSM_mH_90_mA_3p55.txt",
    "NMSSM_mH_90_mA_4.txt",
    "NMSSM_mH_100_mA_0p25.txt",
    "NMSSM_mH_100_mA_0p5.txt",
    "NMSSM_mH_100_mA_0p75.txt",
    "NMSSM_mH_100_mA_1.txt",
    "NMSSM_mH_100_mA_2.txt",
    "NMSSM_mH_100_mA_3.txt",
    "NMSSM_mH_100_mA_3p55.txt",
    "NMSSM_mH_100_mA_4.txt",
    "NMSSM_mH_110_mA_0p25.txt",
    "NMSSM_mH_110_mA_0p5.txt",
    "NMSSM_mH_110_mA_0p75.txt",
    "NMSSM_mH_110_mA_1.txt",
    "NMSSM_mH_110_mA_2.txt",
    "NMSSM_mH_110_mA_3.txt",
    "NMSSM_mH_110_mA_3p55.txt",
    "NMSSM_mH_110_mA_4.txt",
    "NMSSM_mH_125_mA_0p25.txt",
    "NMSSM_mH_125_mA_0p5.txt",
    "NMSSM_mH_125_mA_0p75.txt",
    "NMSSM_mH_125_mA_1.txt",
    "NMSSM_mH_125_mA_2.txt",
    "NMSSM_mH_125_mA_3.txt",
    "NMSSM_mH_125_mA_3p55.txt",
    "NMSSM_mH_125_mA_4.txt",
    "NMSSM_mH_150_mA_0p25.txt",
    "NMSSM_mH_150_mA_0p5.txt",
    "NMSSM_mH_150_mA_0p75.txt",
    "NMSSM_mH_150_mA_1.txt",
    "NMSSM_mH_150_mA_2.txt",
    "NMSSM_mH_150_mA_3.txt",
    "NMSSM_mH_150_mA_3550.txt",
    "NMSSM_mH_150_mA_3p55.txt",
    "NMSSM_mH_150_mA_4.txt"
  };
  int i =0;
  std::vector< std::vector<string> > NMSSM_v;
  for (const auto& p : samples){
    // if (i==6)
    readTextFileWithSamples(p, NMSSM_v);
    i++;
  }

  // // cout << "Vector Created" << endl;                                                
  // readTextFileWithSamples("DarkSUSY_m5_cT_20.txt", NMSSM_v);
  // // cout << "Samples read" << endl;                                                  
  for(const auto& v: NMSSM_v) efficiency(v);
  // // cout << "For Loop completes" << endl;        
}
