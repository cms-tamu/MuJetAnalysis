#ifndef MuJetAnalysis_CutFlowAnalyzer_Helpers
#define MuJetAnalysis_CutFlowAnalyzer_Helpers

#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/MuonReco/interface/Muon.h"

//******************************************************************************
//              Auxiliary function: Order objects by pT                         
//******************************************************************************
namespace tamu{

namespace helpers{

inline bool PtOrder (const reco::GenParticle* p1, const reco::GenParticle* p2) { return (p1->pt() > p2->pt() ); }

inline bool sameTrack(const reco::Track *one, const reco::Track *two) {
  return (fabs(one->px() - two->px()) < 1e-10  &&
	  fabs(one->py() - two->py()) < 1e-10  &&
	  fabs(one->pz() - two->pz()) < 1e-10  &&
	  fabs(one->vx() - two->vx()) < 1e-10  &&
	  fabs(one->vy() - two->vy()) < 1e-10  &&
	  fabs(one->vz() - two->vz()) < 1e-10);
}

//******************************************************************************
// Auxiliary function: Calculate difference between two angles: -PI < phi < PI  
//******************************************************************************
double My_dPhi (double phi1, double phi2) {
  double dPhi = phi1 - phi2;
  if (dPhi >  M_PI) dPhi -= 2.*M_PI;
  if (dPhi < -M_PI) dPhi += 2.*M_PI;
  return dPhi;
}

// Loose ID for PF Muons
bool isPFMuonLoose (const reco::Muon* mu) {
  bool isMoonLoose = false;
  if (    fabs(mu->eta()) < 2.4
       && ( mu->isTrackerMuon() || mu->isGlobalMuon() )
  ) {
    isMoonLoose = true;
  }
  return isMoonLoose;
}

// Private ID for Muons
bool isTrackerMuonPrivateID (const reco::Muon* mu) {
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

}

}

#endif
