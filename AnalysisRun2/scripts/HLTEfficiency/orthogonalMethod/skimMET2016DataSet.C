#include <iostream>
using namespace std;
#include <algorithm>    // std::max
#include <stdlib.h>

void analyzeHLTEfficiencyOrthogonal()
{
  TChain* chain = new TChain("cutFlowAnalyzer_Data/Events");
  // B-v2 missing
  // H missing
  // F missing

  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016B-23Sep2016-v3/170201_153656/0000/out_ana*.root");
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
    
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016D-23Sep2016-v1/170206_184239/0000/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016D-23Sep2016-v1/170206_184239/0001/out_ana*.root");

  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016G-23Sep2016-v1/170201_155152/0000/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016G-23Sep2016-v1/170201_155152/0001/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016G-23Sep2016-v1/170201_155152/0002/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016G-23Sep2016-v1/170201_155152/0003/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016G-23Sep2016-v1/170201_155152/0004/out_ana*.root");

  TFile* newFile = TFile::Open("out_ana_selected.root","RECREATE"); 
  TTree* newChain = chain->CopyTree("nRecoMu>=3");
  newChain->AutoSave();
  newFile->Close();
}

