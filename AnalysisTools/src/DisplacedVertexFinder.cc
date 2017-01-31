#include "MuJetAnalysis/AnalysisTools/interface/DisplacedVertexFinder.h"

namespace{ 
  
  double dist (GlobalPoint f, GlobalPoint s)  
  { 
    return (f-s).mag(); 
  } 
  
  GlobalVector averageDirection(GlobalVector f, GlobalVector s) 
  { 
    return GlobalVector((f.x()+s.x())/2., (f.y()+s.y())/2., (f.z()+s.z())/2.); 
  } 
  
} 


DisplacedVertexFinder::DisplacedVertexFinder(const TransientTrackBuilder *transientTrackBuilder, const GlobalPoint beamSpotPosition)
{
  debug_   = 99;
  if ( debug_ > 10 ) std::cout << "DisplacedVertexFinder::DisplacedVertexFinder" << std::endl;
  
  _transientTrackBuilder = transientTrackBuilder;
  _beamSpotPosition = GlobalPoint( beamSpotPosition.x(), beamSpotPosition.y(), beamSpotPosition.z());

}
DisplacedVertexFinder::~DisplacedVertexFinder()
{
}

void
DisplacedVertexFinder::findDisplacedVertex(const pat::MultiMuon *&mm_0, const pat::MultiMuon *&mm_1)
{
  
  if ( debug_ > 10 ) std::cout << "DisplacedVertexFinder::findDisplacedVertex" << std::endl;

  //------------------------------------------------------------------------------
  // Step 1: Build vecor of transient tracks from muons for each muon jet
  //------------------------------------------------------------------------------
   
  if ( debug_ > 10 ) std::cout << "Step 1: Build vecor of transient tracks from muons for each muon jet" << std::endl;
  // check for valid vertices 
  if ( mm_0 != NULL && mm_0->vertexValid() && mm_1 != NULL && mm_1->vertexValid() && _transientTrackBuilder != NULL) {     
    if ( debug_ > 10 ) std::cout << "Both dimuons have valid vertices!" << std::endl;
    std::vector<reco::TransientTrack> mm_0_tracksToVertex;
    std::vector<reco::TransientTrack> mm_1_tracksToVertex;
        
    if ( debug_ > 10 ) std::cout << "Collecting outer tracks!" << std::endl;
    for (unsigned int i = 0;  i < mm_0->numberOfDaughters();  i++) {
      if ( mm_0->muon(i)->innerTrack().isAvailable() ) {
       mm_0_tracksToVertex.push_back( _transientTrackBuilder->build( mm_0->muon(i)->innerTrack() ) );
      }
    }

    for (unsigned int i = 0;  i < mm_1->numberOfDaughters();  i++) {
      if (mm_1->muon(i)->innerTrack().isAvailable()) {
        mm_1_tracksToVertex.push_back( _transientTrackBuilder->build( mm_1->muon(i)->innerTrack() ) );
      }
    }
    if ( debug_ > 10 ) {
      std::cout << "Dimuon 0 has " << mm_0_tracksToVertex.size() << " associated tracker tracks." << std::endl;
      std::cout << "Dimuon 1 has " << mm_1_tracksToVertex.size() << " associated tracker tracks." << std::endl;
    }
    
    Global3DPoint mm_0_vtx = mm_0->vertexPoint();
    Global3DPoint mm_1_vtx = mm_1->vertexPoint();
    
    std::cout << "Fitted vertexes mm0 " << mm_0_vtx << std::endl;
    std::cout << "Fitted vertexes mm1 " << mm_1_vtx << std::endl;
    
    std::cout << "Investigation transient tracks for dimuon 0" << std::endl;
    TrajectoryStateClosestToPoint closestPoint00 = mm_0_tracksToVertex[0].trajectoryStateClosestToPoint(mm_0_vtx);
    TrajectoryStateClosestToPoint closestPoint01 = mm_0_tracksToVertex[1].trajectoryStateClosestToPoint(mm_0_vtx);
    std::cout << "Closest position 00" << closestPoint00.position() << std::endl;
    std::cout << "Closest momentum 00" << closestPoint00.momentum() << std::endl;      
    std::cout << "Closest position 01" << closestPoint01.position() << std::endl;
    std::cout << "Closest momentum 01" << closestPoint01.momentum() << std::endl;
    GlobalVector aveDirection = averageDirection(closestPoint00.momentum(), closestPoint01.momentum());
    
    std::cout << "Distance between v0 and closest position 00: " << dist(closestPoint00.position(), mm_0_vtx) << " [cm]." << std::endl;
    std::cout << "Distance between v0 and closest position 01: " << dist(closestPoint01.position(), mm_0_vtx) << " [cm]." << std::endl;

    for (double r=0; r<1; r = r + 0.01){
      std::cout << "Distance r compared to vertex: " << r << " [cm]." << std::endl;
      double newX(mm_0_vtx.x() + r*aveDirection.x());
      double newY(mm_0_vtx.y() + r*aveDirection.y());
      double newZ(mm_0_vtx.z() + r*aveDirection.z());
      GlobalPoint newVtx = GlobalPoint(newX, newY, newZ);
      std::cout << "Closest new vertex " << newVtx << std::endl;

      // find the new points on the transient tracks closest to the new 'vtx'
      
      TrajectoryStateClosestToPoint newClosestPoint00 = mm_0_tracksToVertex[0].trajectoryStateClosestToPoint(newVtx);
      TrajectoryStateClosestToPoint newClosestPoint01 = mm_0_tracksToVertex[1].trajectoryStateClosestToPoint(newVtx);
      std::cout << "Closest new position 00" << closestPoint00.position() << std::endl;
      std::cout << "Closest new position 01" << closestPoint01.position() << std::endl;
      std::cout << "New distance between newVtx and closest position 00: " << dist(newClosestPoint00.position(), newVtx) << " [cm]." << std::endl;
      std::cout << "New distance between newVtx and closest position 01: " << dist(newClosestPoint01.position(), newVtx) << " [cm]." << std::endl;

     
    }

    // Std ::cout << "Investigation transient tracks for dimuon 1" << std::endl;
    // TrajectoryStateClosestToPoint closestPoint10 = mm_1_tracksToVertex[0].trajectoryStateClosestToPoint(mm_1_vtx);
    // TrajectoryStateClosestToPoint closestPoint11 = mm_1_tracksToVertex[1].trajectoryStateClosestToPoint(mm_1_vtx);
    // std::cout << "Closest position 10" << closestPoint10.position() << std::endl;
    // std::cout << "Closest momentum 10" << closestPoint10.momentum() << std::endl;      
    // std::cout << "Closest position 11" << closestPoint11.position() << std::endl;
    // std::cout << "Closest momentum 11" << closestPoint11.momentum() << std::endl;      

    // use the fitted vertex and the average direction to construct a straight line
    // mm_0_vtx
    // closestPoint.momentum()
    //      Average 
  }
}

bool 
isRecoVertexInEstimatedVolume(const reco::Vertex& recoVtx) 
{
  // return true if the reconstructed vertex from the offline muon reconstruction 
  // is located in the 95% confidence region
  return false;
}
