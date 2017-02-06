#include <iostream>
using namespace std;
#include <algorithm>    // std::max
#include <stdlib.h>
//#include "../Helpers.h"

double calc_eff(double num, double denom)
{
  //eff = num/denom;
  double eff_uncert = sqrt( ((num/(1.0*denom))*(1-(num/(1.0*denom)) ))/(1.0*denom) );
  return eff_uncert;
}

void analyzeHLTEfficiencyOrthogonal()
{
  TChain* chain = new TChain("cutFlowAnalyzer_Data/Events");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016B-23Sep2016-v3/170201_153656/0000/out_ana*.root");
  /*
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016B-23Sep2016-v3/170201_153656/0001/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016B-23Sep2016-v3/170201_153656/0002/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016B-23Sep2016-v3/170201_153656/0003/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016B-23Sep2016-v3/170201_153656/0004/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016B-23Sep2016-v3/170201_153656/0005/out_ana*.root");
  
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016C-23Sep2016-v1/170201_153948/0000/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016C-23Sep2016-v1/170201_153948/0001/out_ana*.root");

  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016E-23Sep2016-v1/170201_154551/0000/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016E-23Sep2016-v1/170201_154551/0001/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016E-23Sep2016-v1/170201_154551/0002/out_ana*.root");
    
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016G-23Sep2016-v1/170201_155152/0000/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016G-23Sep2016-v1/170201_155152/0001/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016G-23Sep2016-v1/170201_155152/0002/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016G-23Sep2016-v1/170201_155152/0003/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016G-23Sep2016-v1/170201_155152/0004/out_ana*.root");
  */

  TFile* newFile = TFile::Open("out_ana_selected.root","RECREATE"); 
  TTree* newChain = chain->CloneTree(0);
  //  chain->SetBranchStatus("*", 1);
  
  TObjArray *fileElements=chain->GetListOfFiles();
  TIter next(fileElements);
  TChainElement *chEl=0;
  bool verbose = true;
  
  int nEvents=0;
  int nFiles=0;
  Int_t nRecoMu;
  Int_t nSelMu8=0;
  
  while ((chEl=(TChainElement*)next())) {
    nFiles++;
    if (nFiles>10)
      break;

    if (verbose) std::cout << "running on file " << chEl->GetTitle() << std::endl;
    TFile* myfile = new TFile(chEl->GetTitle()); 
    if (!myfile) {
      if (verbose) std::cout << "File " << chEl->GetTitle() << " does not exist" << std::endl;
      continue;
    }
    
    if (verbose) std::cout << "Loading directory cutFlowAnalyzer_Data" << std::endl;
    myfile->cd("cutFlowAnalyzer_Data");
    
    TTree *t = (TTree*)myfile->Get("cutFlowAnalyzer_Data/Events");
    if (!t) {
      if (verbose) std::cout << "Tree cutFlowAnalyzer_Data/Events does not exist" << std::endl;
      continue;
    }
    
    if (verbose) cout<<"  Events  "<<t->GetEntries()<<endl;
    
    // RECO Level Selectors
    t->SetBranchAddress("nRecoMu",                     &nRecoMu);
    
    for(int k=0; k<t->GetEntries(); k++) {
      nEvents++;
      t->GetEntry(k);
      //t->GetEvent(k);
      
      // selection: at least 3 muons in the event
      if (nRecoMu >= 3){
	cout << "Fill out chain" << endl;
	newChain->Fill();
      }
    }
  }

  // newChain->Print();
  newChain->AutoSave();
  newFile->Close();
  // delete chain;
  // delete newFile;
}

