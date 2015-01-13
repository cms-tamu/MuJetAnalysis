#include "MuJetAnalysis/AnalysisTools/interface/ConsistentVertexesCalculator.h"

//******************************************************************************
// Returns Cholesky decomposition of input matrix A
//******************************************************************************
std::vector< std::vector<double> > ConsistentVertexesCalculator::cholesky(std::vector<std::vector<double> > A) {
  int an = A.size();
  double sum1 = 0.0;
  double sum2 = 0.0;
  double sum3 = 0.0;

  std::vector<std::vector<double> > l(an, std::vector<double> (an));

  l[0][0] = sqrt(A[0][0]);
  for (int j = 1; j <= an-1; j++) {
    l[j][0] = A[j][0]/l[0][0];
  }
  
  for (int i = 1; i <= (an-2); i++) {
    for (int k = 0; k <= (i-1); k++) {
      sum1 += pow(l[i][k], 2);
    }
    l[i][i]= sqrt(A[i][i]-sum1);
    for (int j = (i+1); j <= (an-1); j++) {
      for (int k = 0; k <= (i-1); k++) {
        sum2 += l[j][k]*l[i][k];
      }
      l[j][i]= (A[j][i]-sum2)/l[i][i];
    }
  }
  
  for (int k = 0; k <= (an-2); k++) {
    sum3 += pow(l[an-1][k], 2);
  }
  
  l[an-1][an-1] = sqrt(A[an-1][an-1]-sum3);
  
  return l;
}

//******************************************************************************
// Calculates consistent vertex for 2 muon jets
//******************************************************************************

bool ConsistentVertexesCalculator::Calculate( const pat::MultiMuon *&mm_0, const pat::MultiMuon *&mm_1 ) {
  if ( _debug > 10 ) std::cout << "Begin: Calculate" << std::endl;
  
  _resultIsValid = false;

//------------------------------------------------------------------------------
// Step 1: Build vecor of transient tracks from muons for each muon jet
//------------------------------------------------------------------------------
  
  if ( mm_0 != NULL && mm_0->vertexValid() && mm_1 != NULL && mm_1->vertexValid() && _transientTrackBuilder != NULL) {     
    
    std::vector<reco::TransientTrack> mm_0_tracksToVertex;
    std::vector<reco::TransientTrack> mm_1_tracksToVertex;
    
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
// Step 2.1: Extract fitted "regular" vertexes from muon jets
//           This is starting point calculated without any optimization!
//------------------------------------------------------------------------------
    Global3DPoint mm_0_vtx = mm_0->vertexPoint();
    Global3DPoint mm_1_vtx = mm_1->vertexPoint();

//------------------------------------------------------------------------------
// Step 2.2: Extract covariance matrixes from muon jets
//           Perform Cholesky decomposition!
//------------------------------------------------------------------------------
    
    // Vectors to hold vertex covariance matrices:
    std::vector<std::vector<double> > mm_0_covMatrix(3,std::vector<double>(3));
    std::vector<std::vector<double> > mm_1_covMatrix(3,std::vector<double>(3));
    
    // Extract
    for (unsigned int i = 0; i < 3; ++i){
      for (unsigned int j = 0; j < 3; ++j){
        mm_0_covMatrix[i][j] = mm_0->my_vertexCovariance(i,j);
        mm_1_covMatrix[i][j] = mm_1->my_vertexCovariance(i,j);
      }
    }
    
    // Perform the decomposition
    std::vector<std::vector<double> > mm_0_choleskyMatrix = cholesky(mm_0_covMatrix);
    std::vector<std::vector<double> > mm_1_choleskyMatrix = cholesky(mm_1_covMatrix);

//------------------------------------------------------------------------------
// Step 3: Throw vertexes inside ellipse defined in Step 2 and find
//         consistent pair of vertexes                                   
//------------------------------------------------------------------------------
    
    TRandom3 *rnd = new TRandom3(_randomSeed);
    // This loop implements iterative vertex approach
    for (int dice = 0; dice < _nThrows; dice++) {

      // Sample Gaussian of mean 0 and width 1:
      double rnd0x = rnd->Gaus(0., 1.);
      double rnd0y = rnd->Gaus(0., 1.);
      double rnd0z = rnd->Gaus(0., 1.);
      double rnd1x = rnd->Gaus(0., 1.);
      double rnd1y = rnd->Gaus(0., 1.);
      double rnd1z = rnd->Gaus(0., 1.);

      double rnd0[3][3];
      double rnd1[3][3];

      for (unsigned int a = 0; a < 3; ++a){
        for (unsigned int b = 0; b < 3; ++b){
          rnd0[a][b]=0.;
          rnd1[a][b]=0.;
        }
      }

      // Steps to multiply the Cholesky decomposition matrix by the Gaussian sampled points:
      // (All this to be moved to a function)

      rnd0[0][0] = rnd0x*mm_0_choleskyMatrix[0][0];
      rnd0[0][1] = rnd0x*mm_0_choleskyMatrix[0][1];
      rnd0[0][2] = rnd0x*mm_0_choleskyMatrix[0][2];

      rnd0[1][0] = rnd0y*mm_0_choleskyMatrix[1][0];
      rnd0[1][1] = rnd0y*mm_0_choleskyMatrix[1][1];
      rnd0[1][2] = rnd0y*mm_0_choleskyMatrix[1][2];

      rnd0[2][0] = rnd0z*mm_0_choleskyMatrix[2][0];
      rnd0[2][1] = rnd0z*mm_0_choleskyMatrix[2][1];
      rnd0[2][2] = rnd0z*mm_0_choleskyMatrix[2][2];

      rnd1[0][0] = rnd1x*mm_1_choleskyMatrix[0][0];
      rnd1[0][1] = rnd1x*mm_1_choleskyMatrix[0][1];
      rnd1[0][2] = rnd1x*mm_1_choleskyMatrix[0][2];

      rnd1[1][0] = rnd1y*mm_1_choleskyMatrix[1][0];
      rnd1[1][1] = rnd1y*mm_1_choleskyMatrix[1][1];
      rnd1[1][2] = rnd1y*mm_1_choleskyMatrix[1][2];

      rnd1[2][0] = rnd1z*mm_1_choleskyMatrix[2][0];
      rnd1[2][1] = rnd1z*mm_1_choleskyMatrix[2][1];
      rnd1[2][2] = rnd1z*mm_1_choleskyMatrix[2][2];


      double newVtx_0_x = mm_0_vtx.x() + rnd0[0][0]+rnd0[0][1]+rnd0[0][2];
      double newVtx_0_y = mm_0_vtx.y() + rnd0[1][0]+rnd0[1][1]+rnd0[1][2];
      double newVtx_0_z = mm_0_vtx.z() + rnd0[2][0]+rnd0[2][1]+rnd0[2][2];

      double newVtx_1_x = mm_1_vtx.x() + rnd1[0][0]+rnd1[0][1]+rnd1[0][2];
      double newVtx_1_y = mm_1_vtx.y() + rnd1[1][0]+rnd1[1][1]+rnd1[1][2];
      double newVtx_1_z = mm_1_vtx.z() + rnd1[2][0]+rnd1[2][1]+rnd1[2][2];

      // These newly calculated points form the new vertex:
      Global3DPoint newVtx3D_0(newVtx_0_x, newVtx_0_y, newVtx_0_z);
      Global3DPoint newVtx3D_1(newVtx_1_x, newVtx_1_y, newVtx_1_z);

      // Refit tracks to new vertex position
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

      //calculate dz and dxy:
      double rex0  = newVtx3D_0.x() - _beamSpotPosition.x();
      double rey0  = newVtx3D_0.y() - _beamSpotPosition.y();
      double rez0  = newVtx3D_0.z() - _beamSpotPosition.z();
      double repx0 = newVtxP4_0.x();
      double repy0 = newVtxP4_0.y();
      double repz0 = newVtxP4_0.z();
      double rept0 = sqrt( repx0*repx0 + repy0*repy0 );			
      double dz_0   = (rez0) - ((rex0)*repx0+(rey0)*repy0)/rept0 * repz0/rept0;
      double dxy_0  = ( - (rex0) * repy0 + (rey0) * repx0 ) / rept0;

      double rex1  = newVtx3D_1.x() - _beamSpotPosition.x();
      double rey1  = newVtx3D_1.y() - _beamSpotPosition.y();
      double rez1  = newVtx3D_1.z() - _beamSpotPosition.z();
      double repx1 = newVtxP4_1.x();
      double repy1 = newVtxP4_1.y();
      double repz1 = newVtxP4_1.z();
      double rept1 = sqrt( repx1*repx1 + repy1*repy1 );			
      double dz_1   = (rez1) - ((rex1)*repx1+(rey1)*repy1)/rept1 * repz1/rept1;
      double dxy_1  = ( - (rex1) * repy1 + (rey1) * repx1 ) / rept1;
      
      double dz  = dz_0  - dz_1;
//      double dxy = dxy_0 - dxy_1;
      
      // calculate chi2 - different values for sigma are taken from gen level
      double chi2_dz    = 0.;
      double chi2_dxy_0 = 0.;
      double chi2_dxy_1 = 0.;
//      double chi2_dxy   = 0.;
      
      bool pix1 = false;
      bool pix2 = false;

      if ( ((newVtx3D_0.x()*newVtx3D_0.x())+(newVtx3D_0.y()*newVtx3D_0.y())) > 16.0 ){
        pix1 = true;
      }
      if ( fabs(newVtx3D_0.z()) > 34.5 ){
        pix1 = true;
      }
      if ( ((newVtx3D_1.x()*newVtx3D_1.x())+(newVtx3D_1.y()*newVtx3D_1.y())) > 16.0 ){
        pix2 = true;
      }
      if ( fabs(newVtx3D_1.z()) > 34.5 ){
        pix2 = true;
      }

      if (pix1 && pix2){
        chi2_dz  = ( dz  / 0.03276  ) * ( dz  / 0.03276  );
//        chi2_dxy = ( dxy / 0.009981 ) * ( dxy / 0.009981 );
      }
      if (pix1 && !pix2){
        chi2_dz  = ( dz  / 0.01785  ) * ( dz  / 0.01785  );
//        chi2_dxy = ( dxy / 0.005864 ) * ( dxy / 0.005864 );
      }
      if (!pix1 && pix2){
        chi2_dz  = ( dz  / 0.01785  ) * ( dz  / 0.01785  );
//        chi2_dxy = ( dxy / 0.005864 ) * ( dxy / 0.005864 );
      }
      if (!pix1 && !pix2){
        chi2_dz  = ( dz  / 0.003264 ) * ( dz  / 0.003264 );
//        chi2_dxy = ( dxy / 0.002386 ) * ( dxy / 0.002386 );
      }


      if (pix1){
	chi2_dxy_0 = (dxy_0 / 0.00516114) * (dxy_0 / 0.00516114);
      }
      else {
	chi2_dxy_0 = (dxy_0 / 0.00375716) * (dxy_0 / 0.00375716);
      }
      if (pix2){
	chi2_dxy_1 = (dxy_1 / 0.00560319) * (dxy_1 / 0.00560319);
      }
      else {
	chi2_dxy_1 = (dxy_1 / 0.00391578) * (dxy_1 / 0.00391578);
      }


//       chi2_dxy_0 = ( dxy_0 /  ) * ( dxy_0 / 0.00284177 );
//       chi2_dxy_1 = ( dxy_1 / 0.00377043 ) * ( dxy_1 / 0.00377043 );

      // Check for minimum sum of chi2, store variables for minimum
//      double chi2_sum   = chi2_dz + chi2_dxy;
      double chi2_sum   = chi2_dz + chi2_dxy_0 + chi2_dxy_1;
      if ( chi2_sum < _chi2_threshold ) {
        _chi2_threshold = chi2_sum;

        _chi2_sum   = chi2_sum;
        _chi2_dz    = chi2_dz;
        _chi2_dxy_0 = chi2_dxy_0;
        _chi2_dxy_1 = chi2_dxy_1;

        _dz_0 = dz_0;
        _dz_1 = dz_1;
        _dz   = dz;
        
        _dxy_0 = dxy_0;
        _dxy_1 = dxy_1;
        
        _vtx3D_0 = newVtx3D_0;
        _vtx3D_1 = newVtx3D_1;
        
        _vtxP4_0 = newVtxP4_0;
        _vtxP4_1 = newVtxP4_1;
        
        _vVtxP4_0 = vNewVtxP4_0;
        _vVtxP4_1 = vNewVtxP4_1;
        
      }
    }
    
    if ( _debug > 10 ) std::cout << "End: Calculate" << std::endl;
    _resultIsValid = true;

  } else {
    if ( _debug > 0 ) std::cout << "Warning! Consistent vertexes not found" << std::endl;
    _resultIsValid = false;
  }
  
  mm_0->SetConsistentVtxValid(_resultIsValid);
  mm_1->SetConsistentVtxValid(_resultIsValid);
  
  if ( _resultIsValid ) {
    mm_0->SetConsistentVtx3D(_vtx3D_0);
    mm_0->SetConsistentVtxP4(_vtxP4_0);
    mm_0->SetVConsistentVtxP4(_vVtxP4_0);
    
    mm_1->SetConsistentVtx3D(_vtx3D_1);
    mm_1->SetConsistentVtxP4(_vtxP4_1);
    mm_1->SetVConsistentVtxP4(_vVtxP4_1);
  }
  
  return _resultIsValid;
}
