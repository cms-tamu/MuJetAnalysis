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
Float_t epsvsalph1[20] = {0.0};
Float_t Err[20] = {0.0};
Float_t epsvsalph2[20] = {0.0};
Float_t epsvsalph[20] = {0.0};
Float_t epsvalp[20] = {0.0};
Float_t epsvalp2[20] = {0.0};
Float_t weight2017 = 36.734*56.36/1000000;//weight2017 = (lumi * Xsection) / 2017 MC events
Float_t weight2018 = 1.0;//TBD

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
  bool SavePlots(false);
  bool ModelEWKShape(false);
  bool ModelSRWidth(false);
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

  TH2F *EWKShape2D = new TH2F("EWKShape2D","",120,0.0,60.0,120,0.0,60.0);//From MC, actual dimu mass starts from 0.2113, ends at 58 GeV
  TH2F *EWKShape2DScaled = new TH2F("EWKShape2DScaled","",120,0.0,60.0,120,0.0,60.0);//Scaled to Run2 lumi
  TH2F *EWKShapeSR = new TH2F("EWKShapeSR","",120,0.0,60.0,120,0.0,60.0);//consistent mass
  TH2F *EWKShapeSRScaled = new TH2F("EWKShapeSRScaled","",120,0.0,60.0,120,0.0,60.0);//

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

		nentries = t->GetEntries();

		for( int i = 0; i < nentries; i++ ){
		  t->GetEntry(i);
		  counter[k][0]++;

		  if( nRecoMu >= 4 && SavePlots ){
		    P_t_Mu0->Fill(selMu0_pT);
		    P_t_Mu1->Fill(selMu1_pT);
		    P_t_Mu2->Fill(selMu2_pT);
		    P_t_Mu3->Fill(selMu3_pT);
		    eta_Mu0->Fill(selMu0_eta);
		    eta_Mu1->Fill(selMu1_eta);
		    eta_Mu2->Fill(selMu2_eta);
		    eta_Mu3->Fill(selMu3_eta);

		    if( is2DiMuons && SavePlots ){
		      mass_C->Fill(massC);
		      mass_F->Fill(massF);
		      iso_C->Fill(diMuonC_IsoTk_FittedVtx);
		      iso_F->Fill(diMuonF_IsoTk_FittedVtx);
		    }
		  }

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

                        if( diMuonC_IsoTk_FittedVtx < 2.0 && diMuonF_IsoTk_FittedVtx < 2.0 ){
                          counter[k][16]++;

                          if( ModelEWKShape ){
                            EWKShape2D->Fill(massC,massF);
                            EWKShape2DScaled->Fill(massC,massF,weight2017);
                          }//end if ModelEWKShape

                          if( is2DiMuonsMassOK ){
                            counter[k][17]++;

                            if( ModelEWKShape ){
                              EWKShapeSR->Fill(massC,massF);
                              EWKShapeSRScaled->Fill(massC,massF,weight2017);
                            }//end if ModelEWKShape

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

  cout<<" Lxy<9.8&& Lz<48.5 & "<<left<< setw(7)<< counter[k][5]<<"  &  "<<left<< setw(7)<<  TotEff[k][5]<<"     &     "<<left<< setw(7)<<  RelEff[k][5]<<"       &    "<<fixed<<std::setprecision(4) << TotEffErr[k][5]<<" &   "<<fixed<<std::setprecision(3) << RelEffErr[k][5]<<" hline "<<endl;
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

  TString output="/home/ws13/EWKBKGModel2017/CMSSW_9_4_7/src/MuJetAnalysis/CutFlowAnalyzer/scripts/cutflow_macros/CutFlowPlots.root";
  TFile myPlot(output,"RECREATE");

   if( SavePlots ){
     P_t_Mu0->Write();
     P_t_Mu1->Write();
     P_t_Mu2->Write();
     P_t_Mu3->Write();
     eta_Mu0->Write();
     eta_Mu1->Write();
     eta_Mu2->Write();
     eta_Mu3->Write();
     mass_C->Write();
     mass_F->Write();
     iso_C->Write();
     iso_F->Write();
   }

   if( ModelEWKShape ){
     EWKShape2D->Write();
     EWKShape2DScaled->Write();
     EWKShapeSR->Write();
     EWKShapeSRScaled->Write();
   }

   myPlot.Close();
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
