#include <iostream>
using namespace std;
#include <algorithm>    // std::max
#include <stdlib.h>

void skimMET2016DataSet_v2()
{
  TChain* chain = new TChain("cutFlowAnalyzer_Data/Events");
  // B-v2 missing
  // H missing
  // F missing

  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016B-23Sep2016-v3-20170411/170411_212027/0000/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016B-23Sep2016-v3-20170411/170411_212027/0001/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016B-23Sep2016-v3-20170411/170411_212027/0002/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016B-23Sep2016-v3-20170411/170411_212027/0003/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016B-23Sep2016-v3-20170411/170411_212027/0004/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016B-23Sep2016-v3-20170411/170411_212027/0005/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016B-23Sep2016-v3-20170411/170411_212027/0006/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016C-23Sep2016-v1-20170411/170411_212056/0000/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016C-23Sep2016-v1-20170411/170411_212056/0001/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016C-23Sep2016-v1-20170411/170411_212056/0002/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016D-23Sep2016-v1-20170411/170411_212121/0000/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016D-23Sep2016-v1-20170411/170411_212121/0001/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016D-23Sep2016-v1-20170411/170411_212121/0002/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016D-23Sep2016-v1-20170411/170411_212121/0003/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016E-23Sep2016-v1-20170411/170411_212148/0000/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016E-23Sep2016-v1-20170411/170411_212148/0001/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016E-23Sep2016-v1-20170411/170411_212148/0002/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016E-23Sep2016-v1-20170411/170411_212148/0003/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016G-23Sep2016-v1-20170411/170411_212235/0000/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016G-23Sep2016-v1-20170411/170411_212235/0001/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016G-23Sep2016-v1-20170411/170411_212235/0002/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016G-23Sep2016-v1-20170411/170411_212235/0003/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016G-23Sep2016-v1-20170411/170411_212235/0004/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016G-23Sep2016-v1-20170411/170411_212235/0005/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016H-PromptReco-v2-20170411/170418_120355/0000/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016H-PromptReco-v2-20170411/170418_120355/0001/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016H-PromptReco-v2-20170411/170418_120355/0002/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016H-PromptReco-v2-20170411/170418_120355/0003/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016H-PromptReco-v2-20170411/170418_120355/0004/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016H-PromptReco-v2-20170411/170418_120355/0005/out_ana*.root");
  chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016H-PromptReco-v3-20170411/170418_120415/0000/out_ana*.root");
  
  
  // chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016B-23Sep2016-v3-20170213/170213_161511/0000/out_ana*.root");
  
  // chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016B-23Sep2016-v3-20170213/170213_161511/0001/out_ana*.root");
  // chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016B-23Sep2016-v3-20170213/170213_161511/0002/out_ana*.root");
  // chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016B-23Sep2016-v3-20170213/170213_161511/0003/out_ana*.root");
  // chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016B-23Sep2016-v3-20170213/170213_161511/0004/out_ana*.root");
  // chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016B-23Sep2016-v3-20170213/170213_161511/0005/out_ana*.root");
  // chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016B-23Sep2016-v3-20170213/170213_161511/0006/out_ana*.root");
  
  // chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016C-23Sep2016-v1-20170213/170213_161533/0000/out_ana*.root");
  // chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016C-23Sep2016-v1-20170213/170213_161533/0001/out_ana*.root");
  // chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016C-23Sep2016-v1-20170213/170213_161533/0002/out_ana*.root");

  // chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016D-23Sep2016-v1-20170213/170213_161605/0000/out_ana*.root");
  // chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016D-23Sep2016-v1-20170213/170213_161605/0001/out_ana*.root");
  // chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016D-23Sep2016-v1-20170213/170213_161605/0002/out_ana*.root");
  // chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016D-23Sep2016-v1-20170213/170213_161605/0003/out_ana*.root");

  // chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016E-23Sep2016-v1-20170213/170213_161626/0000/out_ana*.root");
  // chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016E-23Sep2016-v1-20170213/170213_161626/0001/out_ana*.root");
  // chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016E-23Sep2016-v1-20170213/170213_161626/0002/out_ana*.root");
  // chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016E-23Sep2016-v1-20170213/170213_161626/0003/out_ana*.root");
    
  // chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016F-23Sep2016-v1-20170213/170213_161647/0000/out_ana*.root");
  // chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016F-23Sep2016-v1-20170213/170213_161647/0001/out_ana*.root");
  // chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016F-23Sep2016-v1-20170213/170213_161647/0002/out_ana*.root");

  // chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016G-23Sep2016-v1-20170213/170213_161713/0000/out_ana*.root");
  // chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016G-23Sep2016-v1-20170213/170213_161713/0001/out_ana*.root");
  // chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016G-23Sep2016-v1-20170213/170213_161713/0002/out_ana*.root");
  // chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016G-23Sep2016-v1-20170213/170213_161713/0003/out_ana*.root");
  // chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016G-23Sep2016-v1-20170213/170213_161713/0004/out_ana*.root");
  // chain->Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016G-23Sep2016-v1-20170213/170213_161713/0005/out_ana*.root");

  cout << "Entries " << chain->GetEntries() << endl;
  cout << "Entries (3mu) " << chain->GetEntries("nRecoMu>=3") << endl;
  return;

  TFile* newFile = TFile::Open("out_ana_selected_170418_114900.root","RECREATE"); 
  TTree* newChain = chain->CopyTree("nRecoMu>=3");
  newChain->AutoSave();
  newFile->Close();
}

