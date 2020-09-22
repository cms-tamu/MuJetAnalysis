#include "MuJetAnalysis/AnalysisTools/interface/Helpers.h"

double tamu::helpers::cotan(double i) {
  return(1 / tan(i));
}

bool tamu::helpers::PtOrder (const reco::GenParticle* p1, const reco::GenParticle* p2) {
  return (p1->pt() > p2->pt() );
}
//Added for PF muon sorting for 2017 and 2018 by Wei @01.15.2019
bool tamu::helpers::PtOrderRecoMu (const reco::Muon* p1, const reco::Muon* p2) {
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

// Update muon ID requirement for run2 analysis: @Wei May12, 2020
// Note: same ID requirement is in MuJetProducerRun2.cc when paring muons, better to combine the two into one single module
bool tamu::helpers::PassMuonId (const reco::Muon* mu) {
  bool pass = false;
  //can be PF loose/standalone
  if ( fabs(mu->eta()) < 2.4 && ( ( (mu->isTrackerMuon() || mu->isGlobalMuon()) && mu->isPFMuon() ) || mu->isStandAloneMuon() ) ) {
    pass = true;
  }
  return pass;
}
