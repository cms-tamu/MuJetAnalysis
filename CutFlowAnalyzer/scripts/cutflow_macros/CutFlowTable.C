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

void CutFlowTable()
{

  bool verbose(true);
  bool CheckRecoVtx(false);
  bool ModelBKGShape(false);
  bool ModelSRWidth(false);
  bool PlotDimuIso(false);
  bool PerEventTriggerEff(false);

  const string dirName="/fdata/hepx/store/user/wshi/QCD_Pt-470to600_MuEnrichedPt5_TuneCP5_13TeV_pythia8/Run2/190604_192236/0000/";
  const std::vector<std::string> dirNames;
  dirNames.push_back(dirName);
  cout<<" dirNames  "<<dirNames[0]<<endl;
  //	TString dirname(fileName);
  TChain* chain = new TChain("dummy");
  TString ext("out_ana_");

  // add files to the chain
  addfilesMany(chain, dirNames, ext);

  Int_t counter[17];//number of selections
  Float_t TotEff[17];
  Float_t TotEffErr[17];
  Float_t RelEff[17];
  Float_t RelEffErr[17];
  Float_t Err = 0.0;
  Float_t epsvsalph = 0.0;

  Float_t weight2017 = 1.0;//weight2017 = (lumi[fb-1] * Xsection of the process[fb]) / # of MC events for the process, e.g. 36.734*56.36/1000000
  Float_t weight2018 = 1.0;//TBD
  Float_t FitMean = 0.0;
  Float_t FitSigma = 0.0;

  //Set up
  for(int j=0;j<17;j++){
    counter[j]=0;
    TotEff[j]=0.0;
    RelEff[j]=0.0;
    TotEffErr[j]=0.0;
    RelEffErr[j]=0.0;
  }

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

  Int_t  diMuonC_m1_FittedVtx_hitpix_Phase1;
  Int_t  diMuonC_m2_FittedVtx_hitpix_Phase1;
  Int_t  diMuonF_m1_FittedVtx_hitpix_Phase1;
  Int_t  diMuonF_m2_FittedVtx_hitpix_Phase1;

  Int_t diMuonC_m1_FittedVtx_NonZero_ValidPixelHits;
  Int_t diMuonC_m2_FittedVtx_NonZero_ValidPixelHits;
  Int_t diMuonF_m1_FittedVtx_NonZero_ValidPixelHits;
  Int_t diMuonF_m2_FittedVtx_NonZero_ValidPixelHits;

  Int_t diMuonC_m1_FittedVtx_NonZero_pixelLayersWithMeasurement;
  Int_t diMuonC_m2_FittedVtx_NonZero_pixelLayersWithMeasurement;
  Int_t diMuonF_m1_FittedVtx_NonZero_pixelLayersWithMeasurement;
  Int_t diMuonF_m2_FittedVtx_NonZero_pixelLayersWithMeasurement;

  Float_t  diMuonC_FittedVtx_Lxy;
  Float_t  diMuonC_FittedVtx_L;
  Float_t  diMuonF_FittedVtx_Lxy;
  Float_t  diMuonF_FittedVtx_L;
  Int_t  nRecoMu;

  TH2F* Lxy_Residual_GEN_leading_pT = new TH2F("Lxy_Residual_GEN_leading_pT","",150,0.01,300.,300,-300.,300.);//cm
  TH2F* Abs_Lz_Residual_GEN_leading_pT = new TH2F("Abs_Lz_Residual_GEN_leading_pT","",150,0.01,300.,300,-300.,300.);

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

  //Actual dimu mass starts from 0.2113, ends at 58 GeV; binning 0.2GeV
  TH2F *BKGShapeCR = new TH2F("BKGShapeCR","",300,0.0,60.0,300,0.0,60.0);
  TH1F *BKGShapeCRmassC = new TH1F("BKGShapeCRmassC","",300,0.0,60.0);
  TH1F *BKGShapeCRmassF = new TH1F("BKGShapeCRmassF","",300,0.0,60.0);
  //Scaled to Run2 lumi
  TH2F *BKGShapeCRScaled = new TH2F("BKGShapeCRScaled","",300,0.0,60.0,300,0.0,60.0);
  TH1F *BKGShapeCRmassCScaled = new TH1F("BKGShapeCRmassCScaled","",300,0.0,60.0);
  TH1F *BKGShapeCRmassFScaled = new TH1F("BKGShapeCRmassFScaled","",300,0.0,60.0);

  TH1F *DimuMass = new TH1F("DimuMass","",6000,0.0,60.0);//binning 0.01 GeV

  TH1F *IsoDimuC = new TH1F("IsoDimuC","",1000,0.0,100.0);//binning 0.1 GeV
  TH1F *IsoDimuF = new TH1F("IsoDimuF","",1000,0.0,100.0);//binning 0.1 GeV

  TObjArray *fileElements=chain->GetListOfFiles();
  TIter next(fileElements);
  TChainElement *chEl=0;

  int nf = 0;//Number of input files

  while ((chEl=(TChainElement*)next())) {
    if (verbose) std::cout << "running on file " << chEl->GetTitle() << std::endl;
    TFile* myfile = new TFile(chEl->GetTitle());
    if (!myfile) {
      if (verbose) std::cout << "File " << chEl->GetTitle() << " does not exist" << std::endl;
      continue;
    }
		myfile->cd("cutFlowAnalyzerPXBL4PXFL3");

		TTree *t = (TTree*)myfile->Get("cutFlowAnalyzerPXBL4PXFL3/Events");
		if (!t) {
		  if (verbose) std::cout << "Tree cutFlowAnalyzerPXBL4PXFL3/Events does not exist" << std::endl;
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

    //To be used for Run2
    t->SetBranchAddress("diMuonC_m1_FittedVtx_hitpix_Phase1",&diMuonC_m1_FittedVtx_hitpix_Phase1);
		t->SetBranchAddress("diMuonC_m2_FittedVtx_hitpix_Phase1",&diMuonC_m2_FittedVtx_hitpix_Phase1);
		t->SetBranchAddress("diMuonF_m1_FittedVtx_hitpix_Phase1",&diMuonF_m1_FittedVtx_hitpix_Phase1);
		t->SetBranchAddress("diMuonF_m2_FittedVtx_hitpix_Phase1",&diMuonF_m2_FittedVtx_hitpix_Phase1);
    //
    t->SetBranchAddress("diMuonC_m1_FittedVtx_NonZero_ValidPixelHits",&diMuonC_m1_FittedVtx_NonZero_ValidPixelHits);
		t->SetBranchAddress("diMuonC_m2_FittedVtx_NonZero_ValidPixelHits",&diMuonC_m2_FittedVtx_NonZero_ValidPixelHits);
		t->SetBranchAddress("diMuonF_m1_FittedVtx_NonZero_ValidPixelHits",&diMuonF_m1_FittedVtx_NonZero_ValidPixelHits);
		t->SetBranchAddress("diMuonF_m2_FittedVtx_NonZero_ValidPixelHits",&diMuonF_m2_FittedVtx_NonZero_ValidPixelHits);
    //
    t->SetBranchAddress("diMuonC_m1_FittedVtx_NonZero_pixelLayersWithMeasurement",&diMuonC_m1_FittedVtx_NonZero_pixelLayersWithMeasurement);
		t->SetBranchAddress("diMuonC_m2_FittedVtx_NonZero_pixelLayersWithMeasurement",&diMuonC_m2_FittedVtx_NonZero_pixelLayersWithMeasurement);
		t->SetBranchAddress("diMuonF_m1_FittedVtx_NonZero_pixelLayersWithMeasurement",&diMuonF_m1_FittedVtx_NonZero_pixelLayersWithMeasurement);
		t->SetBranchAddress("diMuonF_m2_FittedVtx_NonZero_pixelLayersWithMeasurement",&diMuonF_m2_FittedVtx_NonZero_pixelLayersWithMeasurement);
    //For checking pixel Hit
    t->SetBranchAddress("diMuonC_FittedVtx_Lxy",&diMuonC_FittedVtx_Lxy);
		t->SetBranchAddress("diMuonC_FittedVtx_L",&diMuonC_FittedVtx_L);
		t->SetBranchAddress("diMuonF_FittedVtx_Lxy",&diMuonF_FittedVtx_Lxy);
		t->SetBranchAddress("diMuonF_FittedVtx_L",&diMuonF_FittedVtx_L);

		nentries = t->GetEntries();
    nf++;
    if (verbose) std::cout << "nentries: "<< nentries << std::endl;
    if (verbose) std::cout << "nf: "<< nf << std::endl;

		for( int i = 0; i < nentries; i++ ){
		  t->GetEntry(i);
		  counter[0]++;

      //Check vtx significance without any selections
      if ( CheckRecoVtx ){
        Lxy_Residual_GEN_leading_pT->Fill(genA0_Lxy, genA0_Lxy-diMuonC_FittedVtx_Lxy);//assume they match
        Abs_Lz_Residual_GEN_leading_pT->Fill(genA0_Lz, genA0_Lz-sqrt( pow(diMuonC_FittedVtx_L,2) - pow(diMuonC_FittedVtx_Lxy,2) ) );
      }//end CheckRecoVtx

		  if( is1GenMu17 ) counter[1]++;
		  if( is2GenMu8 ) counter[2]++;
		  if( is3GenMu8 ) counter[3]++;
		  if( is4GenMu8 ){
		    counter[4]++;
        //Phase-0 pixel system (Pre2017): 3rd barrel pixel layer and 2nd fwd layer -> Lxy = 10.2 cm; Lz = 48.5 cm
        //Phase-1 pixel system (2017+2018): 3rd barrel pixel layer and 2nd fwd layer -> Lxy = 10.9 cm; Lz = 39.6 cm
        //Phase-1 pixel system (2017+2018): 4th barrel pixel layer and 3rd fwd layer -> Lxy = 16.0 cm; Lz = 51.6 cm //To be used for Run2
        //[1]Reference: https://iopscience.iop.org/article/10.1088/1748-0221/12/07/C07009/pdf
        //[2]TDR: https://cds.cern.ch/record/1481838/files/CMS-TDR-011.pdf
		    if( ( genA0_Lxy < 16.0 && fabs(genA0_Lz) < 51.6 ) &&
            ( genA1_Lxy < 16.0 && fabs(genA1_Lz) < 51.6 ) ) {
              counter[5]++;
            }
		  }//End GEN Level

		  if( is1SelMu17 ) counter[6]++;
		  if( is2SelMu8 ) counter[7]++;
		  if( is3SelMu8 ) counter[8]++;
		  if( is4SelMu8 ){

        counter[9]++;
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
          counter[10]++;

          if( is2DiMuons ){
            counter[11]++;

            if( ( diMuonC_m1_FittedVtx_hitpix_Phase1 == 1 || diMuonC_m2_FittedVtx_hitpix_Phase1 == 1 ) &&
            ( diMuonF_m1_FittedVtx_hitpix_Phase1 == 1 || diMuonF_m2_FittedVtx_hitpix_Phase1 == 1 ) ){
              //!!! Note: this needs to match counter[5] geometry
              counter[12]++;
              if (verbose) std::cout << "counter 12: "<< counter[12] << std::endl;

              //**********************************************
              // Placeholder for dz, iso distributions for dark SUSY samples,
              // especially for large displaced ones
              //**********************************************
              if( fabs(diMuons_dz_FittedVtx) < 0.1 ){
                counter[13]++;

                if( diMuonC_IsoTk_FittedVtx < 2.0 && diMuonF_IsoTk_FittedVtx < 2.0  ){
                  counter[14]++;

                  if( PerEventTriggerEff ) {
                    //pass all offline selections (except HLT fired, otherwise will show 100% all-time for L1 and HLT)
                    // !!!Note: to be more precise, need to put isSignalHLTFired as the last counter and this section in
                    //the second to last counter for these plots to make sense
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
                  if (verbose) std::cout << "counter 14: "<< counter[14] << std::endl;

                  if( is2DiMuonHLTFired ) {
                    counter[15]++;

                    if( is2DiMuonsMassOK ){
                      counter[16]++;
                      if (verbose) std::cout << "counter 16: "<< counter[16] << std::endl;
                      //**********************************************
                      // All offline analysis selections finished
                      //**********************************************

                      if( ModelSRWidth ) {
                        DimuMass->Fill( (massC+massF)/2 );
                      }//end if ModelSRWidth

                      //Note to eliminate/relax Iso cut at counter 14, e.g. Iso<50 GeV or Iso>0
                      if( PlotDimuIso ) {
                        IsoDimuC->Fill(diMuonC_IsoTk_FittedVtx);
                        IsoDimuF->Fill(diMuonF_IsoTk_FittedVtx);
                      }

                    }//end 16: massconsistent
                    else{
                      //************************************************
                      //Control region: for bkg comparison on data and MC
                      //plot BKG shape on mmumu1 and mmumu2
                      //************************************************
                      if( ModelBKGShape ) {
                        BKGShapeCR->Fill(massC,massF);
                        BKGShapeCRmassC->Fill(massC);
                        BKGShapeCRmassF->Fill(massF);
                        BKGShapeCRScaled->Fill(massC,massF,weight2017);
                        BKGShapeCRmassCScaled->Fill(massC,weight2017);
                        BKGShapeCRmassFScaled->Fill(massF,weight2017);
                      }//end if ModelBKGShape

                    }//end else

                  }//end 15
                }//end 14
              }//end 13
            }//end 12
          }//end 11
        }//end 10
      }//end 9
    }//end for entries

    myfile->Close();
    if (verbose) std::cout << "myfile->Close() " << std::endl;

  }//end while next

  RelEff[0] = counter[0]/(counter[0]*1.0);
  for(int m=0;m<17;m++){
    TotEff[m]= counter[m]/(counter[0]*1.0);
    TotEffErr[m]= sqrt( (TotEff[m]*(1-TotEff[m]))/(counter[0]*1.0));
    if(m>0){
      if(m==6){
        RelEff[m]= counter[m]/(counter[0]*1.0);
        RelEffErr[m]= sqrt( (RelEff[m]*(1-RelEff[m]))/(counter[0]*1.0));
      }
      else{
        RelEff[m]=  counter[m]/(counter[m-1]*1.0);
        RelEffErr[m]= sqrt( (RelEff[m]*(1-RelEff[m]))/(counter[m-1]*1.0));
      }
    }
  }//end for

  epsvsalph = counter[16]/(counter[5]*1.0); //mainvalue of epsilob_rec/alpha_gen
  cout<<" Here is the cut-flow-table:"<<endl;
  cout<<" epsvsalph  "<<epsvsalph<<endl;
  Err=   sqrt( (epsvsalph*(1-epsvsalph))/(counter[5]*1.0));
  cout<<"        "<<endl;
  cout<<"begin{landscape}"<<endl;
  cout<<"centering"<<endl;
  cout<<"begin{tabular}{ c| c | c | c | c | c }"<<endl;

  cout<<" Selection   "<<" \\# Events   "<<"   Total Efficiency  "<<" Relative Efficiency   "<<" TotalEffError   "<<" RelEffError "<<" hline "<<endl;

  cout<<" No cut      &   "<<left<< setw(7)<< counter[0]<<"     &   "<<fixed<< std::setprecision(3)<< TotEff[0]<<"         &     "<< RelEff[0]<<"           &   "<<left<< setw(7)<< TotEffErr[0]<<"      &   "<< RelEffErr[0]<<" hline "<<endl;
  cout<<" is1GenMu17  &   "<<left<< setw(7)<< counter[1]<<"    &    "<<left<< setw(7)<< TotEff[1]<<"      &        "<<left<< setw(7)<<  RelEff[1]<<"    &    "<<fixed<<std::setprecision(3)<< TotEffErr[1]<<" &   "<<left<< setw(7)<<  RelEffErr[1]<<" hline "<<endl;
  cout<<" is2GenMu8   &   "<<left<< setw(7)<< counter[2]<<"    &    "<<left<< setw(7)<< TotEff[2]<<"      &        "<<left<< setw(7)<<  RelEff[2]<<"    &     "<<left<< setw(7)<<  TotEffErr[2]<<" & "<<left<< setw(7)<< RelEffErr[2]<<" hline "<<endl;
  cout<<" is3GenMu8   &   "<<left<< setw(7)<< counter[3]<<"    &    "<<left<< setw(7)<< TotEff[3]<<"      &        "<<left<< setw(7)<<  RelEff[3]<<"    &     "<<left<< setw(7)<<  TotEffErr[3]<<" & "<<left<< setw(7)<<  RelEffErr[3]<<" hline "<<endl;
  cout<<" is4GenMu8   &   "<<left<< setw(7)<< counter[4]<<"    &    "<<left<< setw(7)<< TotEff[4]<<"      &        "<<left<< setw(7)<<  RelEff[4]<<"    &     "<<left<< setw(7)<<  TotEffErr[4]<<" & "<<left<< setw(7)<<  RelEffErr[4]<<" hline "<<endl;

  cout<<" Lxy<16.0 && Lz<51.6 & "<<left<< setw(7)<< counter[5]<<"  &  "<<left<< setw(7)<<  TotEff[5]<<"     &     "<<left<< setw(7)<<  RelEff[5]<<"       &    "<<fixed<<std::setprecision(4) << TotEffErr[5]<<" &   "<<fixed<<std::setprecision(3) << RelEffErr[5]<<" hline "<<endl;
  cout<<"                                                                          "<<" hline "<<endl;

  cout<<" is1SelMu17   &    "<<left<< setw(7)<< counter[6]<<"  &    "<<left<< setw(7)<< TotEff[6] <<setw(10)<<"   &    "<<left<< setw(7)<<  RelEff[6]<<"  &    "<<left<< setw(7)<<  TotEffErr[6]<<" &  " <<  RelEffErr[6]<<" hline "<<endl;
  cout<< setprecision(3);
  cout<<" is2SelMu8    &    "<< counter[7]<<"  &    "<< TotEff[7] <<setw(10)<<"   &   "<< RelEff[7]<<"   &   "<< TotEffErr[7]<<"  & "<< RelEffErr[7]<<" hline "<<endl;
  cout<<" is3SelMu8    &    "<< counter[8]<<"  &    "<< TotEff[8]<<"   &    "<< RelEff[8]<<"   &   "<< TotEffErr[8]<<" &  "<< RelEffErr[8]<<" hline "<<endl;
  cout<<" is4SelMu8    &    "<< counter[9]<<"  &    "<< TotEff[9]<<"   &    "<< RelEff[9]<<"   &   "<< TotEffErr[9]<<" &  "<< RelEffErr[9]<<" hline "<<endl;
  cout<<"                                                                        "<<" hline "<<endl;
  cout<<" isVertexOK            &  "<< counter[10]<<"  &    "<< TotEff[10]<<" &    "<< RelEff[10]<<"  &   "<<fixed<<std::setprecision(4) << TotEffErr[10]<<" &  "<< RelEffErr[10]<<" hline "<<endl;
  cout<<" is2dimuon            &  "<< counter[11]<<"  &    "<< TotEff[11]<<" &    "<< RelEff[11]<<"  &   "<<fixed<<std::setprecision(4) << TotEffErr[11]<<" &  "<< RelEffErr[11]<<" hline "<<endl;

  cout<<" is2DiMuonsPixHitOk  &  "<< counter[12]<<"  &    "<< TotEff[12]<<" &     "<< RelEff[12]<<" &   "<<fixed<<std::setprecision(4) << TotEffErr[12]<<" &  "<<fixed<<std::setprecision(3) << RelEffErr[12]<<" hline "<<endl;
  cout<<" is2DiMuonsFittedDzOk    &  "<< counter[13]<<"  &    "<< TotEff[13]<<" &     "<< RelEff[13]<<" &   "<<fixed<<std::setprecision(4) << TotEffErr[13]<<" &  "<<fixed<<std::setprecision(3) << RelEffErr[13]<<" hline "<<endl;
  cout<<" is2DiMuonsIsoTkOK   &  "<< counter[14]<<"  &    "<< TotEff[14]<<" &     "<< RelEff[14]<<" &   "<<fixed<<std::setprecision(4) << TotEffErr[14]<<" &  "<<fixed<<std::setprecision(3) << RelEffErr[14]<<" hline "<<endl;
  cout<<" isSignalHLTFired    &  "<< counter[15] <<" &    "<< TotEff[15]<<" &     "<< RelEff[15]<<" &   "<<fixed<<std::setprecision(4) << TotEffErr[15]<<" &  " <<fixed<<std::setprecision(3) << RelEffErr[15]<<" hline "<<endl;
  cout<<" is2DiMuonsMassOK    &  "<< counter[16] <<" &    "<< TotEff[16]<<" &     "<< RelEff[16]<<" &   "<<fixed<<std::setprecision(4) << TotEffErr[16]<<" &  " <<fixed<<std::setprecision(3) << RelEffErr[16]<<" hline "<<endl;

  cout
    <<"                                                           "<<" hline "<<endl;
  cout<<" epsilon_rec/alpha_gen  & "<< epsvsalph<<"$\\pm$ "<< Err<<" hline "<<endl;

  cout<<"end{tabular}"<<endl;
  cout<<"end{landscape}"<<endl;

  TString output="./foo_modified.root";
  TFile myPlot(output,"RECREATE");

   if ( CheckRecoVtx ){
     Lxy_Residual_GEN_leading_pT->Write();
     Abs_Lz_Residual_GEN_leading_pT->Write();
   }//end CheckRecoVtx

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

   if ( ModelBKGShape ) {
     BKGShapeCR->Write();
     BKGShapeCRmassC->Write();
     BKGShapeCRmassF->Write();
     BKGShapeCRScaled->Write();
     BKGShapeCRmassCScaled->Write();
     BKGShapeCRmassFScaled->Write();
   } //end if ( ModelBKGShape )

   if ( ModelSRWidth ) {
     DimuMass->SetLineColor(kBlue);
     DimuMass->SetLineWidth(2);
     DimuMass->GetXaxis()->SetTitle("#frac{m_{#mu#mu1}+m_{#mu#mu2}}{2} [GeV]");
     DimuMass->GetYaxis()->SetTitle("Events/0.01GeV");
     DimuMass->Fit("gaus","","",0,60);
     FitMean = DimuMass->GetFunction("gaus")->GetParameter(1);//get 2nd parameter Mean
     FitSigma = DimuMass->GetFunction("gaus")->GetParameter(2);//get 3rd parameter Sigma
     DimuMass->GetFunction("gaus")->SetLineColor(kBlue);
     DimuMass->GetFunction("gaus")->SetLineStyle(2);
     gStyle->SetOptStat(0);
     DimuMass->Write();

     cout<<"Dimu Mass Fit Mean: "<< FitMean<<"; Fit Sigma: "<< FitSigma<<endl;
   }//end if ( ModelSRWidth )

   if ( PlotDimuIso ) {
     IsoDimuC->Write();
     IsoDimuF->Write();
   }//end if ( PlotDimuIso )

   myPlot.Close();
}//end CutFlowTable
