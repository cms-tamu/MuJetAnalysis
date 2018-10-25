#include "MuJetAnalysis/AnalysisTools/interface/Helpers.h"

double tamu::helpers::cotan(double i) { 
  return(1 / tan(i)); 
}

bool tamu::helpers::PtOrder (const reco::GenParticle* p1, const reco::GenParticle* p2) { 
  return (p1->pt() > p2->pt() ); 
}

bool tamu::helpers::sameTrack(const reco::Track *one, const reco::Track *two) {
  return (fabs(one->px() - two->px()) < 1e-10  &&
	  fabs(one->py() - two->py()) < 1e-10  &&
	  fabs(one->pz() - two->pz()) < 1e-10  &&
	  fabs(one->vx() - two->vx()) < 1e-10  &&
	  fabs(one->vy() - two->vy()) < 1e-10 &&
	  fabs(one->vz() - two->vz()) < 1e-10);
}


bool tamu::helpers::sameTrackRF(const reco::Track *one, const reco::Track *two) {
  return ( fabs( one->charge() - two->charge())==0 && 
	   fabs( cotan(one->theta()) - cotan(two->theta()) ) < 0.02  &&
	   fabs( (1/one->pt()) - (1/two->pt()) ) < 0.02  &&
	   fabs( one->phi() - two->phi() ) < 0.02  &&
	   fabs( one->dxy() - two->dxy() ) < 0.1  && 
	   fabs( one->dz() - two->dz() ) < 0.1);
}

bool tamu::helpers::matchorder(const std::pair<Int_t,Float_t>  &v1, const std::pair<Int_t,Float_t> &v2) { return (fabs(v1.second) < fabs(v2.second) ); }


bool tamu::helpers::order(Float_t v1, Float_t v2){ 
  return (fabs(v1)<fabs(v2));
}

//******************************************************************************
// Auxiliary function: Calculate difference between two angles: -PI < phi < PI  
//******************************************************************************
double tamu::helpers::My_dPhi (double phi1, double phi2) {
  double dPhi = phi1 - phi2;
  if (dPhi >  M_PI) dPhi -= 2.*M_PI;
  if (dPhi < -M_PI) dPhi += 2.*M_PI;
  return dPhi;
}

// Loose ID for PF Muons
bool tamu::helpers::isPFMuonLoose (const reco::Muon* mu) {
  bool isMoonLoose = false;
  if (    fabs(mu->eta()) < 2.4
       && ( mu->isTrackerMuon() || mu->isGlobalMuon() )
  ) {
    isMoonLoose = true;
  }
  return isMoonLoose;
}

// Private ID for Muons
bool tamu::helpers::isTrackerMuonPrivateID (const reco::Muon* mu) {
  bool isTrackerMuonPrivateID = false;
  if (    fabs(mu->eta()) < 2.4
       && mu->isTrackerMuon()
       && mu->numberOfMatches(reco::Muon::SegmentAndTrackArbitration) >= 2
       && mu->innerTrack()->numberOfValidHits() >= 8
       && mu->innerTrack()->normalizedChi2() < 4. ) {
    isTrackerMuonPrivateID = true;
  }
  return isTrackerMuonPrivateID;
}
