#ifndef MuJetAnalysis_AnalysisTools_Helpers_H
#define MuJetAnalysis_AnalysisTools_Helpers_H

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

bool PtOrder (const reco::GenParticle* p1, const reco::GenParticle* p2);

bool sameTrack(const reco::Track *one, const reco::Track *two);

bool matchorder(const std::pair<Int_t,Float_t>  &v1, const std::pair<Int_t,Float_t> &v2);


//******************************************************************************
// Auxiliary function: Calculate difference between two angles: -PI < phi < PI  
//******************************************************************************
double My_dPhi (double phi1, double phi2);

// Loose ID for PF Muons
bool isPFMuonLoose (const reco::Muon* mu);

// Private ID for Muons
bool isTrackerMuonPrivateID (const reco::Muon* mu);
}

}

#endif
