// -*- C++ -*-
//
// Package:    CutFlowAnalyzer
// Class:      ConsistentVertexesCalculator
// 
/**\class ConsistentVertexesCalculator ConsistentVertexesCalculator.cc MuJetAnalysis/CutFlowAnalyzer/src/ConsistentVertexesCalculator.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Anthony Rose and Yuriy Pakhotin
//         Created:  Tue May 20 16:32:35 CDT 2014
//
//

#include "MuJetAnalysis/CutFlowAnalyzer/interface/ConsistentVertexesCalculator.h

//
// constructors and destructor
//
ConsistentVertexesCalculator::ConsistentVertexesCalculator(const pat::MultiMuon *&mm1, const pat::MultiMuon *&mm2)
{
  
  m_debug = true;
  std::cout << "ConsistentVertexesCalculator::ConsistentVertexesCalculator" << std::endl;
  
}  

ConsistentVertexesCalculator::~ConsistentVertexesCalculator()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}
