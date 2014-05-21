#ifndef ConsistentVertexesCalculator_CC
#define ConsistentVertexesCalculator_CC
// -*- C++ -*-
//
// Package:    CutFlowAnalyzer
// Class:      ConsistentVertexesCalculator
// 

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Anthony Rose and Yuriy Pakhotin
//         Created:  Tue May 20 16:32:35 CDT 2014
//
//

// user include files
#include "TTree.h"
#include "TRandom3.h"
#include "TMath.h"

#include "MuJetAnalysis/DataFormats/interface/MultiMuon.h"
#include "MuJetAnalysis/DataFormats/interface/eig3.h"
#include "MuJetAnalysis/DataFormats/src/eig3.cc"

class ConsistentVertexesCalculator {
  public:
    ConsistentVertexesCalculator(const pat::MultiMuon *&mm1, const pat::MultiMuon *&mm2);
    ~ConsistentVertexesCalculator();
  
  private:
    int m_debug;
  
};

#endif // ConsistentVertexesCalculator_CC
