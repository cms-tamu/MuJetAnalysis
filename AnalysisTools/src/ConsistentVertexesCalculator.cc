#include "MuJetAnalysis/AnalysisTools/interface/ConsistentVertexesCalculator.h"

bool ConsistentVertexesCalculator::Calculate( const pat::MultiMuon *&mm_0, const pat::MultiMuon *&mm_1 ) {
  if ( _debug > 10 ) std::cout << "Begin: Calculate" << std::endl;
  
  bool resultIsValid = false;

//------------------------------------------------------------------------------
// Step 1: Build vecor of transient tracks from muons for each muon jet
//------------------------------------------------------------------------------
  std::vector<reco::TransientTrack> mm_0_tracksToVertex;
  std::vector<reco::TransientTrack> mm_1_tracksToVertex;
  
  if ( mm_0 != NULL && mm_0->vertexValid() && mm_1 != NULL && mm_1->vertexValid() && _transientTrackBuilder != NULL) {     

    for (unsigned int i = 0;  i < mm_0->numberOfDaughters();  i++) {
      if ( mm_0->muon(i)->innerTrack().isAvailable() ) {
       mm_0_tracksToVertex.push_back( _transientTrackBuilder->build( mm_0->muon(i)->innerTrack() ) );
      }
      else if (mm_0->muon(i)->outerTrack().isAvailable()) {
       mm_0_tracksToVertex.push_back( _transientTrackBuilder->build( mm_0->muon(i)->outerTrack() ) );
      }
    }

    for (unsigned int i = 0;  i < mm_1->numberOfDaughters();  i++) {
      if (mm_1->muon(i)->innerTrack().isAvailable()) {
        mm_1_tracksToVertex.push_back( _transientTrackBuilder->build( mm_1->muon(i)->innerTrack() ) );
      }
      else if (mm_1->muon(i)->outerTrack().isAvailable()) {
        mm_1_tracksToVertex.push_back( _transientTrackBuilder->build( mm_1->muon(i)->outerTrack() ) );
      }
    }
    
//------------------------------------------------------------------------------
// Step 2: Extract covariance matrixes from muon jets and find eigenvalues
//         sqrt(eigenvalues) = size of the 1-sigma ellipse around vertex
//------------------------------------------------------------------------------
    // Define
    double A0[3][3]; // Covariance matrix
    double V0[3][3]; // Matrix of eigenvectors
    double d0[3];    // Vector of eigenvalues
    d0[0]=0.;
    d0[1]=0.;
    d0[2]=0.;

    double A1[3][3]; // Covariance matrix
    double V1[3][3]; // Matrix of eigenvectors
    double d1[3];    // Vector of eigenvalues
    d1[0]=0.;
    d1[1]=0.;
    d1[2]=0.;
    
    // Extract
    for (unsigned int a = 0; a < 3; ++a){
      for (unsigned int b = 0; b < 3; ++b){
        A0[a][b] = mm_0->vertexCovariance(a,b);
        A1[a][b] = mm_1->vertexCovariance(a,b);
      }
    }
    
    // Perform the decomposition
    eigen_decomposition(A0, V0, d0);
    eigen_decomposition(A1, V1, d1);

    double ellipseX0Size = sqrt(d0[0]);
    double ellipseX1Size = sqrt(d1[0]);
    double ellipseY0Size = sqrt(d0[1]);
    double ellipseY1Size = sqrt(d1[1]);
    double ellipseZ0Size = sqrt(d0[2]);
    double ellipseZ1Size = sqrt(d1[2]);

//------------------------------------------------------------------------------
// Step 3: Throw vertexes inside ellipse defined in Step 2 and find vertex
//         with minimal distance dZ along beamline between muon jets
//------------------------------------------------------------------------------

    Global3DPoint mm_0_vtx = mm_0->vertexPoint();
    Global3DPoint mm_1_vtx = mm_1->vertexPoint();
    
    TRandom3 *rnd = new TRandom3(_randomSeed);
    double dZ_TmpMin = 10000.;
    
    for (int dice = 0; dice < _nThrows; dice++) {
      
      double rnd_X0 = rnd->Gaus(mm_0_vtx.x(), ellipseX0Size);
      double rnd_Y0 = rnd->Gaus(mm_0_vtx.y(), ellipseY0Size);
      double rnd_Z0 = rnd->Gaus(mm_0_vtx.z(), ellipseZ0Size);

      double rnd_X1 = rnd->Gaus(mm_1_vtx.x(), ellipseX1Size);
      double rnd_Y1 = rnd->Gaus(mm_1_vtx.y(), ellipseY1Size);
      double rnd_Z1 = rnd->Gaus(mm_1_vtx.z(), ellipseZ1Size);
      
      GlobalPoint newVtx3D_0(rnd_X0, rnd_Y0, rnd_Z0);
      GlobalPoint newVtx3D_1(rnd_X1, rnd_Y1, rnd_Z1);
      
      math::XYZTLorentzVector newVtxP4_0;
      math::XYZTLorentzVector newVtxP4_1;
      
      std::vector<math::XYZTLorentzVector> vNewVtxP4_0;
      std::vector<math::XYZTLorentzVector> vNewVtxP4_1;

      for (unsigned int i = 0;  i < mm_0_tracksToVertex.size();  i++) {
        TrajectoryStateClosestToPoint TSCTP0 = mm_0_tracksToVertex[i].trajectoryStateClosestToPoint(newVtx3D_0);
        Global3DVector momentum0 = TSCTP0.momentum();      
        vNewVtxP4_0.push_back(math::XYZTLorentzVector( momentum0.x(), momentum0.y(), momentum0.z(), sqrt(momentum0.mag2() + mm_0->muon(i)->mass()*mm_0->muon(i)->mass() ) ) );
        newVtxP4_0+= vNewVtxP4_0[i];
      }
      
      for (unsigned int i = 0;  i < mm_1_tracksToVertex.size();  i++) {
        TrajectoryStateClosestToPoint TSCTP1 = mm_1_tracksToVertex[i].trajectoryStateClosestToPoint(newVtx3D_1);
        Global3DVector momentum1 = TSCTP1.momentum();
        vNewVtxP4_1.push_back(math::XYZTLorentzVector( momentum1.x(), momentum1.y(), momentum1.z(), sqrt(momentum1.mag2() + mm_1->muon(i)->mass()*mm_1->muon(i)->mass() ) ) );
        newVtxP4_1+= vNewVtxP4_1[i];
      }
    
      double rex0  = newVtx3D_0.x() - _beamSpotPosition.x();
      double rey0  = newVtx3D_0.y() - _beamSpotPosition.y();
      double rez0  = newVtx3D_0.z() - _beamSpotPosition.z();
      double repx0 = newVtxP4_0.x();
      double repy0 = newVtxP4_0.y();
      double repz0 = newVtxP4_0.z();
      double rept0 = sqrt( repx0*repx0 + repy0*repy0 );			
      double dZ0   = (rez0) - ((rex0)*repx0+(rey0)*repy0)/rept0 * repz0/rept0;

      double rex1  = newVtx3D_1.x() - _beamSpotPosition.x();
      double rey1  = newVtx3D_1.y() - _beamSpotPosition.y();
      double rez1  = newVtx3D_1.z() - _beamSpotPosition.z();
      double repx1 = newVtxP4_1.x();
      double repy1 = newVtxP4_1.y();
      double repz1 = newVtxP4_1.z();
      double rept1 = sqrt( repx1*repx1 + repy1*repy1 );			
      double dZ1   = (rez1) - ((rex1)*repx1+(rey1)*repy1)/rept1 * repz1/rept1;
      
      double dZ = dZ0 - dZ1;
      if ( fabs(dZ) < dZ_TmpMin ){
        dZ_TmpMin = fabs(dZ);
        
        _dZ   = dZ;
        _dZ_0 = dZ0;
        _dZ_1 = dZ1;
        
        _vtx3D_0 = newVtx3D_0;
        _vtx3D_1 = newVtx3D_1;
        
        _vtxP4_0 = newVtxP4_0;
        _vtxP4_1 = newVtxP4_1;
      }
    }
    
    if ( _debug > 10 ) std::cout << "End: Calculate" << std::endl;
    resultIsValid = true;
    
  } else {
    if ( _debug > 0 ) std::cout << "Dimuons vertexes not valid" << std::endl;
    resultIsValid = false;
  }
  
  return resultIsValid;
}
