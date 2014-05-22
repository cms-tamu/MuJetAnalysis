#ifndef ConsistentVertexesCalculator_H
#define ConsistentVertexesCalculator_H
// -*- C++ -*-
//
// Package:    AnalysisTools
// Class:      ConsistentVertexesCalculator
// 
//
// Original Author:  Anthony Rose and Yuriy Pakhotin
//         Created:  Tue May 20 16:32:35 CDT 2014
//
//

// user include files
#include "TTree.h"
#include "TRandom3.h"
#include "TMath.h"

#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "DataFormats/GeometryVector/interface/GlobalVector.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"

#include "MuJetAnalysis/DataFormats/interface/MultiMuon.h"
#include "MuJetAnalysis/AnalysisTools/interface/eig3.h"
#include "MuJetAnalysis/AnalysisTools/src/eig3.cc"

class ConsistentVertexesCalculator {
  public:
    ConsistentVertexesCalculator(const TransientTrackBuilder *transientTrackBuilder, const GlobalPoint beamSpotPosition );
    ~ConsistentVertexesCalculator();
    
    void SetDebug(int debug = 0) { _debug = debug; }
    
    void SetRandomSeed( unsigned int randomSeed = 0 ) { _randomSeed = randomSeed; }
    void SetNThrows( int nThrows = 0 ) { _nThrows = nThrows; }
        
    GlobalPoint             vertexPoint(int i)     { if (i == 0) return _vtx3D_0; else return _vtx3D_1; }
    math::XYZTLorentzVector vertexP4(int i)        { if (i == 0) return _vtxP4_0; else return _vtxP4_1; }
	  GlobalVector            vertexMomentum(int i)  { math::XYZTLorentzVector v = vertexP4(i);  return GlobalVector(v.x(), v.y(), v.z()); }
	  double                 vertexMass(int i)      { return vertexP4(i).mass(); }
	  double                 vertexDZ(int i)        { if (i == 0) return _dZ_0; else return _dZ_1; }
	  double                 dZ()                    { return _dZ; }
  
    bool Calculate(const pat::MultiMuon *&mm_0, const pat::MultiMuon *&mm_1);
  
  private:
    
    int  _debug;
    
    unsigned int _randomSeed;
    int _nThrows;
    
    const TransientTrackBuilder *_transientTrackBuilder;
    GlobalPoint _beamSpotPosition;
    
    double _dZ;
    double _dZ_0;
    double _dZ_1;
    
    GlobalPoint _vtx3D_0;
    GlobalPoint _vtx3D_1;
    
    math::XYZTLorentzVector _vtxP4_0;
    math::XYZTLorentzVector _vtxP4_1;
    
};

//
// constructors and destructor
//
ConsistentVertexesCalculator::ConsistentVertexesCalculator(const TransientTrackBuilder *transientTrackBuilder, GlobalPoint beamSpotPosition)
{
  
  _debug   = 0;
  
  if ( _debug > 10 ) std::cout << "ConsistentVertexesCalculator::ConsistentVertexesCalculator" << std::endl;
  
  _randomSeed = 0;
  _nThrows = 100000;
  
  _transientTrackBuilder = transientTrackBuilder;
  _beamSpotPosition = GlobalPoint( beamSpotPosition.x(), beamSpotPosition.y(), beamSpotPosition.z());
  
    _dZ   = 1000.0;
    _dZ_0 = 1000.0;
    _dZ_1 = 1000.0;
    
    _vtx3D_0 = GlobalPoint(1000., 1000., 1000.);
    _vtx3D_1 = GlobalPoint(1000., 1000., 1000.);
    
    _vtxP4_0 = math::XYZTLorentzVector(0,0,0,10000.);
    _vtxP4_1 = math::XYZTLorentzVector(0,0,0,10000.);
  
}  

ConsistentVertexesCalculator::~ConsistentVertexesCalculator()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

#endif // ConsistentVertexesCalculator_H
