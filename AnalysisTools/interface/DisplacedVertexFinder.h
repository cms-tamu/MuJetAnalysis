#ifndef MuonJetAnalysis_AnalysisTools_DisplacedVertexFinder_H
#define MuonJetAnalysis_AnalysisTools_DisplacedVertexFinder_H

// user include files
#include "TTree.h"
#include "TRandom3.h"
#include "TMath.h"

#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "DataFormats/GeometryVector/interface/GlobalVector.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

#include "MuJetAnalysis/DataFormats/interface/MultiMuon.h"
#include "MuJetAnalysis/AnalysisTools/interface/Helpers.h"

/*
The purpose of this class is to estimate the production vertex for displaced muons. 
It replaces the 'hard' vertex constraint in the CutFlowAnalyzer module.
This class takes a dimuon as input
It follows the pat muons as they pass through the tracker
it calculates the closest approach at regular intervals
the closest approach is calculated + center
a volume around the center is constructed 
- circle with radius a
- ellipsoid with a,b
- ellipsoid with a,b,c


In our (displaced muon analysis for 13TeV) analysis we would like to use a loose vertex cut to increase acceptance. In the previous analysis there was a hard cut of 0.1cm on the dz compatibility between the two muon-jets. Alexei suggested to check the distance between the of a particular dimuon at regular intervals. I am working on a class that first builds transient tracks from reco::Tracks. I only wish to use the innerTracks, since our trigger uses trackerMuons. I then want to calculate the distance between the two transient tracks. I was looking at the documentation on https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideTransientTracks. However, it is not really clear to me how to proceed. I see a function that calculates the TrajectoryStateClosestToPoint with respect to a particular point.

// with respect to any specified vertex, such as primary vertex
GlobalPoint vert(pv.x(), pv.y(), pv.z());
TrajectoryStateClosestToPoint  traj = tk.trajectoryStateClosestToPoint(vert );


I was thinking to first find the straight line through the recoVertex in between the two muons. Then scan that straight line in steps of e.g. 1mm starting from the recoVertex on either side. Calculate the closest point on either muon track and then calculate the distance between the two muon tracks. 


*/

double dist (GlobalPoint f, GlobalPoint s) 
{
  return (f-s).mag();
}

GlobalVector averageDirection(GlobalVector f, GlobalVector s)
{
  return GlobalVector((f.x()+s.x())/2., (f.y()+s.y())/2., (f.z()+s.z())/2.);
}

class DisplacedVertexFinder {
  public:
    DisplacedVertexFinder(const TransientTrackBuilder *transientTrackBuilder, const GlobalPoint beamSpotPosition);
    ~DisplacedVertexFinder();

    void setDebug(int debug = 0) { debug_ = debug; }
    void loadDiMuon(const pat::MultiMuon& dimuon) {dimuons_.push_back(dimuon);}
    void findDisplacedVertex(const pat::MultiMuon* &xo, const pat::MultiMuon*& );
    reco::Vertex getEstimatedVertex() {return foundVertex_;}
    bool isRecoVertexInEstimatedVolume(const reco::Vertex&);
    bool setMethod(int);
    
    
  private:
    std::vector<pat::MultiMuon> dimuons_;
    reco::Vertex foundVertex_;
    
    const TransientTrackBuilder *_transientTrackBuilder;
    GlobalPoint _beamSpotPosition;

    double a_;
    double b_;
    double c_;
    int method_;
    int  debug_;    
};

#endif 
