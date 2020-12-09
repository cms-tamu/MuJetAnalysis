#include <iostream>
using namespace std;
#include <algorithm>    // std::max
#include <stdlib.h>

void skimSample3Mu()
{
  TChain* chain = new TChain("cutFlowAnalyzerPXBL4PXFL3/Events");
  chain->Add("out_ana_WZTo3LNu4.root");

  cout << "Entries " << chain->GetEntries() << endl;
  cout << "Entries (3mu) " << chain->GetEntries("nRecoMu==3") << endl;

  TFile* newFile = TFile::Open("out_ana_WZTo3LNu4_skim3mu.root","RECREATE");
  TTree* newChain = chain->CopyTree("nRecoMu==3");
  newChain->AutoSave();
  newFile->Close();
}
