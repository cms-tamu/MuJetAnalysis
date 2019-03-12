#include <iostream>
#include <iomanip>
using namespace std;
#include <algorithm>    // std::max
#include <stdlib.h>
#include <math.h>
#include <TFile.h>
#include <TTree.h>
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

Float_t counter[20][18];//samples; selections
Float_t TotEff[20][18];
Float_t TotEffErr[20][18];
Float_t RelEff[20][18];
Float_t RelEffErr[20][18];
Float_t epsvsalph1[20] = {0.0};
Float_t Err[20] = {0.0};
Float_t epsvsalph2[20] = {0.0};
Float_t epsvsalph[20] = {0.0};
Float_t epsvalp[20] = {0.0};
Float_t epsvalp2[20] = {0.0};
Float_t weight2017 = 36.734*56.36/1000000;//weight2017 = (lumi * Xsection) / 2017 MC events
Float_t weight2018 = 1.0;//TBD
Float_t FitMean = 0.0;
Float_t FitSigma = 0.0;

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

  bool verbose(true);
  bool ModelEWKShape(false);
  bool ModelSRWidth(false);
  bool PerEventTriggerEff(false);
  //	TString dirname(fileName);
  TChain* chain = new TChain("dummy");
  TString ext("out_ana_");

  cout<<" dirNames  "<<dirNames[0]<<endl;
  // add files to the chain
  addfilesMany(chain, dirNames, ext);

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

  Float_t selMu0_phi;
  Float_t selMu1_phi;
  Float_t selMu2_phi;
  Float_t selMu3_phi;

  Bool_t  is2DiMuons;
  Bool_t  is2MuJets;
  Bool_t  isVtxOK;

  Bool_t  is2DiMuonsFittedVtxOK;
  Bool_t  is2DiMuonsMassOK;

  Bool_t  is2DiMuonHLTFired;
  Bool_t  isSignalHLTL1Fired;
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

  TH1F* leading_pt_pass_basic = new TH1F("leading_pt_pass_basic","",50,0.,50.);
  TH1F* leading_eta_pass_basic = new TH1F("leading_eta_pass_basic","",50,-2.5,2.5);
  TH1F* leading_phi_pass_basic = new TH1F("leading_phi_pass_basic","",60,-TMath::Pi(),TMath::Pi());
  TH1F* HLT_leading_pt_pass_basic = new TH1F("HLT_leading_pt_pass_basic","",50,0.,50.);
  TH1F* HLT_leading_eta_pass_basic = new TH1F("HLT_leading_eta_pass_basic","",50,-2.5,2.5);
  TH1F* HLT_leading_phi_pass_basic = new TH1F("HLT_leading_phi_pass_basic","",60,-TMath::Pi(),TMath::Pi());
  TH1F* L1_leading_pt_pass_basic = new TH1F("L1_leading_pt_pass_basic","",50,0.,50.);
  TH1F* L1_leading_eta_pass_basic = new TH1F("L1_leading_eta_pass_basic","",50,-2.5,2.5);
  TH1F* L1_leading_phi_pass_basic = new TH1F("L1_leading_phi_pass_basic","",60,-TMath::Pi(),TMath::Pi());

  TH1F* leading_pt_pass_all = new TH1F("leading_pt_pass_all","",50,0.,50.);
  TH1F* leading_eta_pass_all = new TH1F("leading_eta_pass_all","",50,-2.5,2.5);
  TH1F* leading_phi_pass_all = new TH1F("leading_phi_pass_all","",60,-TMath::Pi(),TMath::Pi());
  TH1F* HLT_leading_pt_pass_all = new TH1F("HLT_leading_pt_pass_all","",50,0.,50.);
  TH1F* HLT_leading_eta_pass_all = new TH1F("HLT_leading_eta_pass_all","",50,-2.5,2.5);
  TH1F* HLT_leading_phi_pass_all = new TH1F("HLT_leading_phi_pass_all","",60,-TMath::Pi(),TMath::Pi());
  TH1F* L1_leading_pt_pass_all = new TH1F("L1_leading_pt_pass_all","",50,0.,50.);
  TH1F* L1_leading_eta_pass_all = new TH1F("L1_leading_eta_pass_all","",50,-2.5,2.5);
  TH1F* L1_leading_phi_pass_all = new TH1F("L1_leading_phi_pass_all","",60,-TMath::Pi(),TMath::Pi());

  TH2F *EWKShape2D = new TH2F("EWKShape2D","",120,0.0,60.0,120,0.0,60.0);//From MC, actual dimu mass starts from 0.2113, ends at 58 GeV
  TH2F *EWKShapeSR = new TH2F("EWKShapeSR","",120,0.0,60.0,120,0.0,60.0);//consistent mass
  TH1F *EWKShape2DmassC = new TH1F("EWKShape2DmassC","",120,0.0,60.0);
  TH1F *EWKShape2DmassF = new TH1F("EWKShape2DmassF","",120,0.0,60.0);
  TH1F *EWKShapeSRmassC = new TH1F("EWKShapeSRmassC","",120,0.0,60.0);
  TH1F *EWKShapeSRmassF = new TH1F("EWKShapeSRmassF","",120,0.0,60.0);

  TH2F *EWKShape2DScaled = new TH2F("EWKShape2DScaled","",120,0.0,60.0,120,0.0,60.0);//Scaled to Run2 lumi
  TH2F *EWKShapeSRScaled = new TH2F("EWKShapeSRScaled","",120,0.0,60.0,120,0.0,60.0);
  TH1F *EWKShape2DmassCScaled = new TH1F("EWKShape2DmassCScaled","",120,0.0,60.0);
  TH1F *EWKShape2DmassFScaled = new TH1F("EWKShape2DmassFScaled","",120,0.0,60.0);
  TH1F *EWKShapeSRmassCScaled = new TH1F("EWKShapeSRmassCScaled","",120,0.0,60.0);
  TH1F *EWKShapeSRmassFScaled = new TH1F("EWKShapeSRmassFScaled","",120,0.0,60.0);

  TH1F *DimuMass= new TH1F("DimuMass","",6000,0.0,60.0);//bin width 0.01 GeV

  TObjArray *fileElements=chain->GetListOfFiles();
  TIter next(fileElements);
  TChainElement *chEl=0;

  k++;

  while ((chEl=(TChainElement*)next())) {
    if (verbose) std::cout << "running on file " << chEl->GetTitle() << std::endl;
    TFile* myfile = new TFile(chEl->GetTitle());
    if (!myfile) {
      if (verbose) std::cout << "File " << chEl->GetTitle() << " does not exist" << std::endl;
      continue;
    }
		myfile->cd("cutFlowAnalyzerPXBL3PXFL2");

		TTree *t = (TTree*)myfile->Get("cutFlowAnalyzerPXBL3PXFL2/Events");
		if (!t) {
		  if (verbose) std::cout << "Tree cutFlowAnalyzerPXBL3PXFL2/Events does not exist" << std::endl;
		  continue;
		}

    //if (verbose) cout<<"  Events  "<<t->GetEntries()<<endl;
    int nentries;

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
		t->SetBranchAddress("selMu0_eta",&selMu0_eta);
		t->SetBranchAddress("selMu1_eta",&selMu1_eta);
		t->SetBranchAddress("selMu2_eta",&selMu2_eta);
		t->SetBranchAddress("selMu3_eta",&selMu3_eta);
    t->SetBranchAddress("selMu0_phi",&selMu0_phi);
		t->SetBranchAddress("selMu1_phi",&selMu1_phi);
		t->SetBranchAddress("selMu2_phi",&selMu2_phi);
		t->SetBranchAddress("selMu3_phi",&selMu3_phi);

    t->SetBranchAddress("massC",&massC);
		t->SetBranchAddress("massF",&massF);

		t->SetBranchAddress("diMuonC_IsoTk_FittedVtx",&diMuonC_IsoTk_FittedVtx);
		t->SetBranchAddress("diMuonF_IsoTk_FittedVtx",&diMuonF_IsoTk_FittedVtx);

		t->SetBranchAddress("isVertexOK",&isVtxOK);
		t->SetBranchAddress("is2DiMuons",&is2DiMuons);
		t->SetBranchAddress("is2MuJets",&is2MuJets);
		t->SetBranchAddress("is2DiMuonsFittedVtxOK",&is2DiMuonsFittedVtxOK);
		t->SetBranchAddress("diMuons_dz_FittedVtx",&diMuons_dz_FittedVtx);
		t->SetBranchAddress("is2DiMuonsMassOK_FittedVtx",&is2DiMuonsMassOK);
		t->SetBranchAddress("isDiMuonHLTFired",&is2DiMuonHLTFired);
    t->SetBranchAddress("isSignalHLTL1Fired",&isSignalHLTL1Fired);
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

		nentries = t->GetEntries();

		for( int i = 0; i < nentries; i++ ){
		  t->GetEntry(i);
		  counter[k][0]++;

		  if( is1GenMu17 ) counter[k][1]++;
		  if( is2GenMu8 ) counter[k][2]++;
		  if( is3GenMu8 ) counter[k][3]++;
		  if( is4GenMu8 ){
		    counter[k][4]++;
		    if( ( genA0_Lxy < 9.8 && fabs(genA0_Lz) < 46.5 ) &&
            ( genA1_Lxy < 9.8 && fabs(genA1_Lz) < 46.5 ) ) counter[k][5]++;
		  }

		  if( is1SelMu17 ) counter[k][6]++;
		  if( is2SelMu8 ) counter[k][7]++;
		  if( is3SelMu8 ) counter[k][8]++;
		  if( is4SelMu8 ){

        counter[k][9]++;

        //**********************************************
        // Basic offline pT selections finished
        //**********************************************

        if( PerEventTriggerEff ) {//pass basic offline pT selections

          leading_pt_pass_basic->Fill(selMu0_pT);
          leading_eta_pass_basic->Fill(selMu0_eta);
          leading_phi_pass_basic->Fill(selMu0_phi);

          if ( is2DiMuonHLTFired ) {
            HLT_leading_pt_pass_basic->Fill(selMu0_pT);
            HLT_leading_eta_pass_basic->Fill(selMu0_eta);
            HLT_leading_phi_pass_basic->Fill(selMu0_phi);
          }//HLT fired

          if ( isSignalHLTL1Fired ) {
            L1_leading_pt_pass_basic->Fill(selMu0_pT);
            L1_leading_eta_pass_basic->Fill(selMu0_eta);
            L1_leading_phi_pass_basic->Fill(selMu0_phi);
          }//L1 seeds fired

        }//end if PerEventTriggerEff

        if( isVtxOK ){
          counter[k][10]++;

          if( is2MuJets ){
            counter[k][11]++;

            if( is2DiMuons ){
              counter[k][12]++;

              if( ( diMuonC_m1_FittedVtx_hitpix_l3inc == 1 || diMuonC_m2_FittedVtx_hitpix_l3inc == 1 ) &&
                  ( diMuonF_m1_FittedVtx_hitpix_l3inc == 1 || diMuonF_m2_FittedVtx_hitpix_l3inc == 1 ) ){
                    counter[k][13]++;

                    if( fabs(diMuons_dz_FittedVtx) < 0.1 ){
                      counter[k][14]++;

                      if( is2DiMuonHLTFired ){
                        counter[k][15]++;

                        if( diMuonC_IsoTk_FittedVtx < 2.0 && diMuonF_IsoTk_FittedVtx < 2.0 ) {
                          counter[k][16]++;

                          if( ModelEWKShape ) {
                            EWKShape2D->Fill(massC,massF);
                            EWKShape2DmassC->Fill(massC);
                            EWKShape2DmassF->Fill(massF);
                            EWKShape2DScaled->Fill(massC,massF,weight2017);
                            EWKShape2DmassCScaled->Fill(massC,weight2017);
                            EWKShape2DmassFScaled->Fill(massF,weight2017);
                          }//end if ModelEWKShape

                          if( is2DiMuonsMassOK ){
                            counter[k][17]++;

                            //**********************************************
                            // All offline analysis selections finished
                            //**********************************************

                            if( PerEventTriggerEff ) {//pass all offline selections

                              leading_pt_pass_all->Fill(selMu0_pT);
                              leading_eta_pass_all->Fill(selMu0_eta);
                              leading_phi_pass_all->Fill(selMu0_phi);

                              if ( is2DiMuonHLTFired ) {
                                HLT_leading_pt_pass_all->Fill(selMu0_pT);
	                              HLT_leading_eta_pass_all->Fill(selMu0_eta);
                                HLT_leading_phi_pass_all->Fill(selMu0_phi);
                              }//HLT fired

                              if ( isSignalHLTL1Fired ) {
                                L1_leading_pt_pass_all->Fill(selMu0_pT);
                                L1_leading_eta_pass_all->Fill(selMu0_eta);
                                L1_leading_phi_pass_all->Fill(selMu0_phi);
                              }//L1 seeds fired

                            }//end if PerEventTriggerEff

                            if( ModelEWKShape ) {
                              EWKShapeSR->Fill(massC,massF);
                              EWKShapeSRmassC->Fill(massC);
                              EWKShapeSRmassF->Fill(massF);
                              EWKShapeSRScaled->Fill(massC,massF,weight2017);
                              EWKShapeSRmassCScaled->Fill(massC,weight2017);
                              EWKShapeSRmassFScaled->Fill(massF,weight2017);
                            }//end if ModelEWKShape

                            if( ModelSRWidth ) {
                    		      DimuMass->Fill( (massC+massF)/2 );
                    		    }//end if ModelSRWidth

                          }//end 17
                        }//end 16
                      }//end 15
                    }//end 14
                  }//end 13
                }//end 12
              }//end 11
            }//end 10
          }//end 9
        }//end for entries
        myfile->Close();
  }

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

  epsvsalph[k] = counter[k][17]/(counter[k][5]*1.0); //mainvalue of epsilob_rec/alpha_gen
  cout<<" Here is the cut-flow-table:"<<endl;
  cout<<" epsvsalph[k]  "<<epsvsalph[k]<<endl;
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

  cout<<" Lxy<9.8 && Lz<48.5 & "<<left<< setw(7)<< counter[k][5]<<"  &  "<<left<< setw(7)<<  TotEff[k][5]<<"     &     "<<left<< setw(7)<<  RelEff[k][5]<<"       &    "<<fixed<<std::setprecision(4) << TotEffErr[k][5]<<" &   "<<fixed<<std::setprecision(3) << RelEffErr[k][5]<<" hline "<<endl;
  cout<<"                                                                          "<<" hline "<<endl;

  cout<<" is1SelMu17   &    "<<left<< setw(7)<< counter[k][6]<<"  &    "<<left<< setw(7)<< TotEff[k][6] <<setw(10)<<"   &    "<<left<< setw(7)<<  RelEff[k][6]<<"  &    "<<left<< setw(7)<<  TotEffErr[k][6]<<" &  " <<  RelEffErr[k][6]<<" hline "<<endl;
  cout<< setprecision(3);
  cout<<" is2SelMu8    &    "<< counter[k][7]<<"  &    "<< TotEff[k][7] <<setw(10)<<"   &   "<< RelEff[k][7]<<"   &   "<< TotEffErr[k][7]<<"  & "<< RelEffErr[k][7]<<" hline "<<endl;
  cout<<" is3SelMu8    &    "<< counter[k][8]<<"  &    "<< TotEff[k][8]<<"   &    "<< RelEff[k][8]<<"   &   "<< TotEffErr[k][8]<<" &  "<< RelEffErr[k][8]<<" hline "<<endl;
  cout<<" is4SelMu8    &    "<< counter[k][9]<<"  &    "<< TotEff[k][9]<<"   &    "<< RelEff[k][9]<<"   &   "<< TotEffErr[k][9]<<" &  "<< RelEffErr[k][9]<<" hline "<<endl;
  cout<<"                                                                        "<<" hline "<<endl;
  cout<<" isVertexOK            &  "<< counter[k][10]<<"  &    "<< TotEff[k][10]<<" &    "<< RelEff[k][10]<<"  &   "<<fixed<<std::setprecision(4) << TotEffErr[k][10]<<" &  "<< RelEffErr[k][10]<<" hline "<<endl;
  cout<<" is2MuJets            &  "<< counter[k][11]<<"  &    "<< TotEff[k][11]<<" &    "<< RelEff[k][11]<<"  &   "<<fixed<<std::setprecision(4) << TotEffErr[k][11]<<" &  "<< RelEffErr[k][11]<<" hline "<<endl;
  cout<<" is2dimuon            &  "<< counter[k][12]<<"  &    "<< TotEff[k][12]<<" &    "<< RelEff[k][12]<<"  &   "<<fixed<<std::setprecision(4) << TotEffErr[k][12]<<" &  "<< RelEffErr[k][12]<<" hline "<<endl;

  cout<<" is2DiMuonsPixHitOk  &  "<< counter[k][13]<<"  &    "<< TotEff[k][13]<<" &     "<< RelEff[k][13]<<" &   "<<fixed<<std::setprecision(4) << TotEffErr[k][13]<<" &  "<<fixed<<std::setprecision(3) << RelEffErr[k][13]<<" hline "<<endl;
  cout<<" is2DiMuonsFittedDzOk    &  "<< counter[k][14]<<"  &    "<< TotEff[k][14]<<" &     "<< RelEff[k][14]<<" &   "<<fixed<<std::setprecision(4) << TotEffErr[k][14]<<" &  "<<fixed<<std::setprecision(3) << RelEffErr[k][14]<<" hline "<<endl;
  cout<<" isSignalHLTFired   &  "<< counter[k][15]<<"  &    "<< TotEff[k][15]<<" &     "<< RelEff[k][15]<<" &   "<<fixed<<std::setprecision(4) << TotEffErr[k][15]<<" &  "<<fixed<<std::setprecision(3) << RelEffErr[k][15]<<" hline "<<endl;
  cout<<" is2DiMuonsIsoTkOK    &  "<< counter[k][16] <<" &    "<< TotEff[k][16]<<" &     "<< RelEff[k][16]<<" &   "<<fixed<<std::setprecision(4) << TotEffErr[k][16]<<" &  " <<fixed<<std::setprecision(3) << RelEffErr[k][16]<<" hline "<<endl;
  cout<<" is2DiMuonsMassOK    &  "<< counter[k][17] <<" &    "<< TotEff[k][17]<<" &     "<< RelEff[k][17]<<" &   "<<fixed<<std::setprecision(4) << TotEffErr[k][17]<<" &  " <<fixed<<std::setprecision(3) << RelEffErr[k][17]<<" hline "<<endl;

  cout
    <<"                                                           "<<" hline "<<endl;
  cout<<" epsilon_rec/alpha_gen  & "<< epsvsalph[k]<<"$\\pm$ "<< Err[k]<<" hline "<<endl;

  cout<<"end{tabular}"<<endl;
  cout<<"end{landscape}"<<endl;

  TString output="./foo_modified.root";
  TFile myPlot(output,"RECREATE");

   if ( PerEventTriggerEff ) {
     //Per-event Efficiency for signal HLT and L1 seeds after basic offline pT selections
     if( TEfficiency::CheckConsistency(*HLT_leading_pt_pass_basic, *leading_pt_pass_basic) ) {
       TEfficiency* eff_HLT_leading_pt_pass_basic  = new TEfficiency(*HLT_leading_pt_pass_basic, *leading_pt_pass_basic);
       eff_HLT_leading_pt_pass_basic->SetTitle("HLT efficiency vs leading pT (after basic offline pT selections);Leading pT [GeV];#epsilon");
       eff_HLT_leading_pt_pass_basic->Write();
     }
     if( TEfficiency::CheckConsistency(*HLT_leading_eta_pass_basic, *leading_eta_pass_basic) ) {
       TEfficiency* eff_HLT_leading_eta_pass_basic = new TEfficiency(*HLT_leading_eta_pass_basic, *leading_eta_pass_basic);
       eff_HLT_leading_eta_pass_basic->SetTitle("HLT efficiency vs leading eta (after basic offline pT selections);Leading eta;#epsilon");
       eff_HLT_leading_eta_pass_basic->Write();
     }
     if( TEfficiency::CheckConsistency(*HLT_leading_phi_pass_basic, *leading_phi_pass_basic) ) {
       TEfficiency* eff_HLT_leading_phi_pass_basic = new TEfficiency(*HLT_leading_phi_pass_basic, *leading_phi_pass_basic);
       eff_HLT_leading_phi_pass_basic->SetTitle("HLT efficiency vs leading phi (after basic offline pT selections);Leading phi;#epsilon");
       eff_HLT_leading_phi_pass_basic->Write();
     }
     if( TEfficiency::CheckConsistency(*L1_leading_pt_pass_basic, *leading_pt_pass_basic) ) {
       TEfficiency* eff_L1_leading_pt_past_basic  = new TEfficiency(*L1_leading_pt_pass_basic, *leading_pt_pass_basic);
       eff_L1_leading_pt_past_basic->SetTitle("L1 efficiency vs leading pT (after basic offline pT selections);Leading pT[GeV];#epsilon");
       eff_L1_leading_pt_past_basic->Write();
     }
     if( TEfficiency::CheckConsistency(*L1_leading_eta_pass_basic, *leading_eta_pass_basic) ) {
       TEfficiency* eff_L1_leading_eta_past_basic = new TEfficiency(*L1_leading_eta_pass_basic, *leading_eta_pass_basic);
       eff_L1_leading_eta_past_basic->SetTitle("L1 efficiency vs leading eta (after basic offline pT selections);Leading eta;#epsilon");
       eff_L1_leading_eta_past_basic->Write();
     }
     if( TEfficiency::CheckConsistency(*L1_leading_phi_pass_basic, *leading_phi_pass_basic) ) {
       TEfficiency* eff_L1_leading_phi_pass_basic = new TEfficiency(*L1_leading_phi_pass_basic, *leading_phi_pass_basic);
       eff_L1_leading_phi_pass_basic->SetTitle("L1 efficiency vs leading phi (after basic offline pT selections);Leading phi;#epsilon");
       eff_L1_leading_phi_pass_basic->Write();
     }

     //Per-event Efficiency for signal HLT and L1 seeds after all offline selections
     if( TEfficiency::CheckConsistency(*HLT_leading_pt_pass_all, *leading_pt_pass_all) ) {
       TEfficiency* eff_HLT_leading_pt_pass_all  = new TEfficiency(*HLT_leading_pt_pass_all, *leading_pt_pass_all);
       eff_HLT_leading_pt_pass_all->SetTitle("HLT efficiency vs leading pT (after all offline selections);Leading pT [GeV];#epsilon");
       eff_HLT_leading_pt_pass_all->Write();
     }
     if( TEfficiency::CheckConsistency(*HLT_leading_eta_pass_all, *leading_eta_pass_all) ) {
       TEfficiency* eff_HLT_leading_eta_pass_all = new TEfficiency(*HLT_leading_eta_pass_all, *leading_eta_pass_all);
       eff_HLT_leading_eta_pass_all->SetTitle("HLT efficiency vs leading eta (after all offline selections);Leading eta;#epsilon");
       eff_HLT_leading_eta_pass_all->Write();
     }
     if( TEfficiency::CheckConsistency(*HLT_leading_phi_pass_all, *leading_phi_pass_all) ) {
       TEfficiency* eff_HLT_leading_phi_pass_all = new TEfficiency(*HLT_leading_phi_pass_all, *leading_phi_pass_all);
       eff_HLT_leading_phi_pass_all->SetTitle("HLT efficiency vs leading phi (after all offline selections);Leading phi;#epsilon");
       eff_HLT_leading_phi_pass_all->Write();
     }
     if( TEfficiency::CheckConsistency(*L1_leading_pt_pass_all, *leading_pt_pass_all) ) {
       TEfficiency* eff_L1_leading_pt_past_all  = new TEfficiency(*L1_leading_pt_pass_all, *leading_pt_pass_all);
       eff_L1_leading_pt_past_all->SetTitle("L1 efficiency vs leading pT (after all offline selections);Leading pT [GeV];#epsilon");
       eff_L1_leading_pt_past_all->Write();
     }
     if( TEfficiency::CheckConsistency(*L1_leading_eta_pass_all, *leading_eta_pass_all) ) {
       TEfficiency* eff_L1_leading_eta_past_all = new TEfficiency(*L1_leading_eta_pass_all, *leading_eta_pass_all);
       eff_L1_leading_eta_past_all->SetTitle("L1 efficiency vs leading eta (after all offline selections);Leading eta;#epsilon");
       eff_L1_leading_eta_past_all->Write();
     }
     if( TEfficiency::CheckConsistency(*L1_leading_phi_pass_all, *leading_phi_pass_all) ) {
       TEfficiency* eff_L1_leading_phi_pass_all = new TEfficiency(*L1_leading_phi_pass_all, *leading_phi_pass_all);
       eff_L1_leading_phi_pass_all->SetTitle("L1 efficiency vs leading phi (after all offline selections);Leading phi;#epsilon");
       eff_L1_leading_phi_pass_all->Write();
     }

   }//end if (PerEventTriggerEff)

   if ( ModelEWKShape ) {
     EWKShape2D->Write();
     EWKShape2DmassC->Write();
     EWKShape2DmassF->Write();
     EWKShape2DScaled->Write();
     EWKShape2DmassCScaled->Write();
     EWKShape2DmassFScaled->Write();

     EWKShapeSR->Write();
     EWKShapeSRmassC->Write();
     EWKShapeSRmassF->Write();
     EWKShapeSRScaled->Write();
     EWKShapeSRmassCScaled->Write();
     EWKShapeSRmassFScaled->Write();
   } //end if ( ModelEWKShape )

   if ( ModelSRWidth ) {
     DimuMass->SetLineColor(kBlue);
     DimuMass->SetLineWidth(2);
     DimuMass->Fit("gaus","","",0,60);
     FitMean = DimuMass->GetFunction("gaus")->GetParameter(1);//get 2nd parameter Mean
     FitSigma = DimuMass->GetFunction("gaus")->GetParameter(2);//get 3rd parameter Sigma
     DimuMass->GetFunction("gaus")->SetLineColor(kBlue);
     DimuMass->GetFunction("gaus")->SetLineStyle(2);
     gStyle->SetOptStat(0);
     DimuMass->Write();

     cout<<"Dimu Mass Fit Mean: "<< FitMean<<"; Fit Sigma: "<< FitSigma<<endl;
   }//end if ( ModelSRWidth )

   myPlot.Close();
}

void analysis(const std::string txtfile)
{
setup();
std::vector< std::vector<string> > NtuplePaths;
// // cout << "Vector Created" << endl;
readTextFileWithSamples(txtfile, NtuplePaths);
// // cout << "Samples read" << endl;
for(auto v: NtuplePaths) efficiency(v);
// // cout << "For Loop completes" << endl;
}
