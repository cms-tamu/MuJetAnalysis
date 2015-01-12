//
// $Id: MultiMuon.cc,v 1.12 2013/08/04 21:36:36 pakhotin Exp $
// 
// Jim Pivarski <pivarski@physics.tamu.edu>
// 

#include "MuJetAnalysis/DataFormats/interface/MultiMuon.h"

#ifndef MULTIMUONCANDIDATE_FOR_FWLITE
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexFitter.h"
#else
class TransientTrackBuilder {};
#endif // MULTIMUONCANDIDATE_FOR_FWLITE

/// default constructor
pat::MultiMuon::MultiMuon( std::vector<const pat::Muon*> &muons,
                          const TransientTrackBuilder    *transientTrackBuilder,
                          const reco::TrackCollection    *tracks,
                          const pat::MuonCollection      *allmuons,
                          const CaloTowerCollection      *caloTowers,
                          double centralTrackIsolationCone,
                          double unionTrackIsolationCone,
                          double centralTrackThresholdPt,
                          double unionTrackThresholdPt,
                          double centralCaloIsolationCone,
                          double unionCaloIsolationCone,
                          double centralNumberAboveThresholdCone,
                          double unionNumberAboveThresholdCone,
                          double centralNumberAboveThresholdPt,
                          double unionNumberAboveThresholdPt)
{
  pat::CompositeCandidate();

  int charge = 0;
  LorentzVector lorentzVector;
  
  for (std::vector<const pat::Muon*>::const_iterator muon = muons.begin();  muon != muons.end();  ++muon) {
    addDaughter(**muon);
    charge += (*muon)->charge();
    lorentzVector += (*muon)->p4();
  }
  
  setCharge(charge);
  pt_   = lorentzVector.pt();
  eta_  = lorentzVector.eta();
  phi_  = lorentzVector.phi();
  mass_ = lorentzVector.mass();

  std::map<const reco::Candidate*,unsigned int> ancestorCounter;
  for (std::vector<const pat::Muon*>::const_iterator muon = muons.begin();  muon != muons.end();  ++muon) {
    const reco::GenParticle *genParticle = (*muon)->genParticle();
    if (genParticle != NULL) {
      const reco::Candidate *mother = genParticle->mother();
      while (mother != NULL) {
	      if (ancestorCounter.find(mother) == ancestorCounter.end()) {
	        ancestorCounter[mother] = 0;
	      }
	      ancestorCounter[mother]++;
	      mother = mother->mother();
	    }
    }
  }

  const reco::Candidate *youngestCommonAncestor = NULL;
  unsigned int maxDepth = 0;
  for (std::map<const reco::Candidate*,unsigned int>::const_iterator ancestor = ancestorCounter.begin();  ancestor != ancestorCounter.end();  ++ancestor) {
    if (ancestor->second == numberOfDaughters()) {
      unsigned int depth = 0;
      for (const reco::Candidate *mother = ancestor->first;  mother != NULL;  mother = mother->mother()) {
        depth++;
      }
      if (depth > maxDepth) {
        maxDepth = depth;
	      youngestCommonAncestor = ancestor->first;
      }
    }
  }

  if (youngestCommonAncestor != NULL) {
    const reco::GenParticle *asGenParticle = dynamic_cast<const reco::GenParticle*>(youngestCommonAncestor);
    setGenParticle(*asGenParticle);
  }

// Fitted vertex
  m_vertexValid = false;
  m_chi2 = 0.;
  m_ndof = 0.;
  if (transientTrackBuilder != NULL) {
    calculateVertex(transientTrackBuilder);
  }

// Consistent vertex
  m_consistentVtxValid = false;
  
  m_centralTrackIsolationCone = 0.;
  m_unionTrackIsolationCone   = 0.;
  m_centralTrackThresholdPt   = 0.;
  m_unionTrackThresholdPt     = 0.;
  m_centralTrackIsolation     = 0.;
  m_unionTrackIsolation       = 0.;
  if (tracks != NULL) {
    calculateTrackIsolation(tracks, allmuons, centralTrackIsolationCone, unionTrackIsolationCone, centralTrackThresholdPt, unionTrackThresholdPt);
  }

  m_centralCaloIsolationCone = 0.;
  m_unionCaloIsolationCone   = 0.;
  m_centralECALIsolation     = 0.;
  m_unionECALIsolation       = 0.;
  m_centralHCALIsolation     = 0.;
  m_unionHCALIsolation       = 0.;
  if (caloTowers != NULL) {
    calculateCaloIsolation(caloTowers, centralCaloIsolationCone, unionCaloIsolationCone);
  }

  m_centralNumberAboveThresholdCone = 0.;
  m_unionNumberAboveThresholdCone = 0.;
  m_centralNumberAboveThresholdPt = 0.;
  m_unionNumberAboveThresholdPt = 0.;
  m_centralNumberAboveThreshold = 0;
  m_unionNumberAboveThreshold = 0;
  if (tracks != NULL) {
    calculateNumberAboveThresholdIsolation(tracks, allmuons, centralNumberAboveThresholdCone,
                                                             unionNumberAboveThresholdCone,
                                                             centralNumberAboveThresholdPt, 
                                                             unionNumberAboveThresholdPt);
  }
}

/// constructor from MultiMuonType
pat::MultiMuon::MultiMuon(const pat::MultiMuon &aMultiMuon): pat::CompositeCandidate(aMultiMuon) {
  pt_ = aMultiMuon.pt_;
  eta_ = aMultiMuon.eta_;
  phi_ = aMultiMuon.phi_;
  mass_ = aMultiMuon.mass_;

  if (aMultiMuon.genParticle() != NULL) setGenParticle(*(aMultiMuon.genParticle()));

  m_vertexValid = aMultiMuon.m_vertexValid;
  m_chi2 = aMultiMuon.m_chi2;
  m_ndof = aMultiMuon.m_ndof;
  m_covarianceMatrix = aMultiMuon.m_covarianceMatrix;
  for (unsigned int i = 0;  i < aMultiMuon.m_vertexPCA.size();  i++) {
    m_vertexPCA.push_back(aMultiMuon.m_vertexPCA[i]);
    m_vertexPCACovarianceMatrix.push_back(aMultiMuon.m_vertexPCACovarianceMatrix[i]);
    m_vertexP4.push_back(aMultiMuon.m_vertexP4[i]);
  }
  
  m_consistentVtxValid = aMultiMuon.m_consistentVtxValid;
  
  m_centralTrackIsolationCone       = aMultiMuon.m_centralTrackIsolationCone;
  m_unionTrackIsolationCone         = aMultiMuon.m_unionTrackIsolationCone;
  m_centralTrackThresholdPt         = aMultiMuon.m_centralTrackThresholdPt;
  m_unionTrackThresholdPt           = aMultiMuon.m_unionTrackThresholdPt;
  m_centralCaloIsolationCone        = aMultiMuon.m_centralCaloIsolationCone;
  m_unionCaloIsolationCone          = aMultiMuon.m_unionCaloIsolationCone;
  m_centralNumberAboveThresholdCone = aMultiMuon.m_centralNumberAboveThresholdCone;
  m_unionNumberAboveThresholdCone   = aMultiMuon.m_unionNumberAboveThresholdCone;
  m_centralNumberAboveThresholdPt   = aMultiMuon.m_centralNumberAboveThresholdPt;
  m_unionNumberAboveThresholdPt     = aMultiMuon.m_unionNumberAboveThresholdPt;

  m_centralTrackIsolation       = aMultiMuon.m_centralTrackIsolation;
  m_unionTrackIsolation         = aMultiMuon.m_unionTrackIsolation;
  m_centralECALIsolation        = aMultiMuon.m_centralECALIsolation;
  m_unionECALIsolation          = aMultiMuon.m_unionECALIsolation;
  m_centralHCALIsolation        = aMultiMuon.m_centralHCALIsolation;
  m_unionHCALIsolation          = aMultiMuon.m_unionHCALIsolation;
  m_centralNumberAboveThreshold = aMultiMuon.m_centralNumberAboveThreshold;
  m_unionNumberAboveThreshold   = aMultiMuon.m_unionNumberAboveThreshold;
}

/// destructor
pat::MultiMuon::~MultiMuon() {}

/// calculate the vertex from TransientTracks; return true iff successful
bool pat::MultiMuon::calculateVertex(const TransientTrackBuilder *transientTrackBuilder) {
#ifdef MULTIMUONCANDIDATE_FOR_FWLITE
  return false;
#endif // MULTIMUONCANDIDATE_FOR_FWLITE
#ifndef MULTIMUONCANDIDATE_FOR_FWLITE
  
  std::vector<reco::TransientTrack> tracksToVertex;
  for (unsigned int i = 0;  i < numberOfDaughters();  i++) {
    if (muon(i) == NULL) {
      throw cms::Exception("MultiMuon") << "MultiMuons should only contain pat::Muons";
    }
    if (muon(i)->innerTrack().isAvailable()) {
      tracksToVertex.push_back(transientTrackBuilder->build(muon(i)->innerTrack()));
    }
    else if (muon(i)->outerTrack().isAvailable()) {
      tracksToVertex.push_back(transientTrackBuilder->build(muon(i)->outerTrack()));
    }
  }

  if (tracksToVertex.size() < 2) return false;

  KalmanVertexFitter vertexFitter;
  CachingVertex<5> fittedVertex = vertexFitter.vertex(tracksToVertex);

  if (!fittedVertex.isValid()  ||  fittedVertex.totalChiSquared() < 0.) return false;

  m_vertexValid = true;
  m_chi2 = fittedVertex.totalChiSquared();
  m_ndof = fittedVertex.degreesOfFreedom();

  setVertex(Point(fittedVertex.position().x(), fittedVertex.position().y(), fittedVertex.position().z()));

//   double covarianceMatrixArray[6] = {fittedVertex.error().cxx(), fittedVertex.error().cyy(), fittedVertex.error().czz(), fittedVertex.error().cyx(), fittedVertex.error().czx(), fittedVertex.error().czy()};
  double covarianceMatrixArray[6] = {fittedVertex.error().cxx(), fittedVertex.error().cyx(), fittedVertex.error().cyy(), fittedVertex.error().czx(), fittedVertex.error().czy(), fittedVertex.error().czz() }; // YP: FIXME! Check if this definition is correct
  m_covarianceMatrix = CovarianceMatrix(covarianceMatrixArray, 6);

  m_vertexPCA.clear();
  m_vertexPCACovarianceMatrix.clear();
  m_vertexP4.clear();
  for (unsigned int i = 0;  i < numberOfDaughters();  i++) {
    TrajectoryStateClosestToPoint TSCTP = tracksToVertex[i].trajectoryStateClosestToPoint(vertexPoint());

    m_vertexPCA.push_back(TSCTP.position());

    GlobalError error = TSCTP.theState().cartesianError().position();    
//    double covarianceMatrixArray2[6] = {error.cxx(), error.cyy(), error.czz(), error.cyx(), error.czx(), error.czy()};
    double covarianceMatrixArray2[6] = {error.cxx(), error.cyx(), error.cyy(), error.czx(), error.czy(), error.czz()}; // YP: FIXME! Check if this definition is correct
    CovarianceMatrix covarianceMatrix2 = CovarianceMatrix(covarianceMatrixArray2, 6);
    m_vertexPCACovarianceMatrix.push_back(covarianceMatrix2);

    GlobalVector momentum = TSCTP.momentum();
    m_vertexP4.push_back( LorentzVector( momentum.x(), momentum.y(), momentum.z(), sqrt( momentum.mag2() + daughter(i)->mass()*daughter(i)->mass() ) ) );
  }
  
   return true;
#endif // MULTIMUONCANDIDATE_FOR_FWLITE
}

void pat::MultiMuon::calculateTrackIsolation( const reco::TrackCollection *tracks,
                                               const pat::MuonCollection   *allmuons,
                                               double centralCone,
                                               double unionCone,
                                               double centralThreshold,
                                               double unionThreshold,
                                               TTree   *diagnosticTTree,
                                               Float_t *diagnosticdR,
                                               Float_t *diagnosticpT) {
  m_centralTrackIsolationCone = centralCone;
  m_unionTrackIsolationCone   = unionCone;
  m_centralTrackThresholdPt   = centralThreshold;
  m_unionTrackThresholdPt     = unionThreshold;
  m_centralTrackIsolation     = 0.;
  m_unionTrackIsolation       = 0.;

  std::vector<const reco::Track*> nonMuons;
  for (reco::TrackCollection::const_iterator track = tracks->begin();  track != tracks->end();  ++track) {
    bool matchesMuon = false;
    
    for (unsigned int i = 0;  i < numberOfDaughters();  i++) {
      const pat::Muon *muon = dynamic_cast<const pat::Muon*>(daughter(i));
      if (muon->innerTrack().isAvailable()  &&  sameTrack(&*track, &*(muon->innerTrack()))) {
        matchesMuon = true;
        break;
      }
    }
    
    for (pat::MuonCollection::const_iterator muon = allmuons->begin();  muon != allmuons->end();  ++muon) {
      if (muon->innerTrack().isAvailable()  &&  sameTrack(&*track, &*(muon->innerTrack()))) {
        matchesMuon = true;
        break;
      }
    }
    
    if (!matchesMuon) nonMuons.push_back(&*track);
  }

  for (std::vector<const reco::Track*>::const_iterator nonMuon = nonMuons.begin();  nonMuon != nonMuons.end();  ++nonMuon) {
    bool inUnionCone = false;
    
    for (unsigned int i = 0;  i < numberOfDaughters();  i++) {
      double dphi = daughter(i)->phi() - (*nonMuon)->phi();
      while (dphi > M_PI)  dphi -= 2.*M_PI;
      while (dphi < -M_PI) dphi += 2.*M_PI;
      double deta = daughter(i)->eta() - (*nonMuon)->eta();
      double dR = sqrt(pow(dphi, 2) + pow(deta, 2));
      if (dR < unionCone) {
        inUnionCone = true;
        break;
      }
    }
    
    if (inUnionCone  &&  (*nonMuon)->pt() > m_unionTrackThresholdPt) {
      m_unionTrackIsolation += (*nonMuon)->pt();
    }

    double dphi = phi() - (*nonMuon)->phi();
    while (dphi > M_PI) dphi -= 2.*M_PI;
    while (dphi < -M_PI) dphi += 2.*M_PI;
    double deta = eta() - (*nonMuon)->eta();
    double dR = sqrt(pow(dphi, 2) + pow(deta, 2));
    if (dR < centralCone  &&  (*nonMuon)->pt() > m_centralTrackThresholdPt) {
      m_centralTrackIsolation += (*nonMuon)->pt();
    }

    if (diagnosticTTree != NULL  &&  dR < 0.5) {
      *diagnosticdR = dR;
      *diagnosticpT = (*nonMuon)->pt();
      diagnosticTTree->Fill();
    }
  }
}

void pat::MultiMuon::calculateNumberAboveThresholdIsolation( const reco::TrackCollection *tracks,
                                                              const pat::MuonCollection *allmuons,
                                                              double centralCone,
                                                              double unionCone,
                                                              double centralThreshold,
                                                              double unionThreshold,
                                                              TTree *diagnosticTTree,
                                                              Float_t *diagnosticdR,
                                                              Float_t *diagnosticpT) {
  m_centralNumberAboveThresholdCone = centralCone;
  m_unionNumberAboveThresholdCone   = unionCone;
  m_centralNumberAboveThresholdPt   = centralThreshold;
  m_unionNumberAboveThresholdPt     = unionThreshold;
  m_centralNumberAboveThreshold     = 0;
  m_unionNumberAboveThreshold       = 0;

  std::vector<const reco::Track*> nonMuons;
  for (reco::TrackCollection::const_iterator track = tracks->begin();  track != tracks->end();  ++track) {
    bool matchesMuon = false;
    
    for (unsigned int i = 0;  i < numberOfDaughters();  i++) {
      const pat::Muon *muon = dynamic_cast<const pat::Muon*>(daughter(i));
      if (muon->innerTrack().isAvailable()  &&  sameTrack(&*track, &*(muon->innerTrack()))) {
        matchesMuon = true;
        break;
      }
    }
    
    for (pat::MuonCollection::const_iterator muon = allmuons->begin();  muon != allmuons->end();  ++muon) {
      if (muon->innerTrack().isAvailable()  &&  sameTrack(&*track, &*(muon->innerTrack()))) {
        matchesMuon = true;
        break;
      }
    }
    
    if (!matchesMuon) nonMuons.push_back(&*track);
  }

  for (std::vector<const reco::Track*>::const_iterator nonMuon = nonMuons.begin();  nonMuon != nonMuons.end();  ++nonMuon) {
    if ((*nonMuon)->pt() > unionThreshold) {
      bool inUnionCone = false;
      for (unsigned int i = 0;  i < numberOfDaughters();  i++) {
        double dphi = daughter(i)->phi() - (*nonMuon)->phi();
        while (dphi > M_PI) dphi -= 2.*M_PI;
        while (dphi < -M_PI) dphi += 2.*M_PI;
        double deta = daughter(i)->eta() - (*nonMuon)->eta();
        double dR = sqrt(pow(dphi, 2) + pow(deta, 2));
        if (dR < unionCone) {
          inUnionCone = true;
          break;
        }
      }
      if (inUnionCone) {
        m_unionNumberAboveThreshold++;
      }
    }

    double dphi = phi() - (*nonMuon)->phi();
    while (dphi > M_PI) dphi -= 2.*M_PI;
    while (dphi < -M_PI) dphi += 2.*M_PI;
    double deta = eta() - (*nonMuon)->eta();
    double dR = sqrt(pow(dphi, 2) + pow(deta, 2));
    if (dR < centralCone  &&  (*nonMuon)->pt() > centralThreshold) {
      m_centralNumberAboveThreshold++;
    }

    if (diagnosticTTree != NULL  &&  dR < 0.5) {
      *diagnosticdR = dR;
      *diagnosticpT = (*nonMuon)->pt();
      diagnosticTTree->Fill();
    }
  }
}

void pat::MultiMuon::calculateCaloIsolation(const CaloTowerCollection *caloTowers, double centralCone, double unionCone) {
  m_centralCaloIsolationCone = centralCone;
  m_unionCaloIsolationCone   = unionCone;
  m_centralECALIsolation     = 0.;
  m_unionECALIsolation       = 0.;
  m_centralHCALIsolation     = 0.;
  m_unionHCALIsolation       = 0.;

  for (CaloTowerCollection::const_iterator caloTower = caloTowers->begin();  caloTower != caloTowers->end();  ++caloTower) {
    // following http://cmslxr.fnal.gov/lxr/source/RecoMuon/MuonIsolation/plugins/CaloExtractorByAssociator.cc#269
    // and http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/CMSSW/RecoMuon/MuonIsolationProducers/python/caloExtractorByAssociatorBlocks_cff.py?view=markup
    // just the "TowersBlock" and the "Towers" else block
    const double theThreshold_E  = 0.2;
    const double theThreshold_H  = 0.5;
    const double theThreshold_HO = 0.5;

    double ECALcontribution = 0.;
    double HCALcontribution = 0.;

    double etecal = caloTower->emEt();
    double eecal  = caloTower->emEnergy();
    if (etecal > theThreshold_E  &&  eecal > 3.*noiseEcal(*caloTower)) {
      ECALcontribution += etecal;
    }
    double ethcal = caloTower->hadEt();
    double ehcal  = caloTower->hadEnergy();
    if (ethcal > theThreshold_H  &&  ehcal > 3.*noiseHcal(*caloTower)) {
      HCALcontribution += ethcal;
    }
    double ethocal = caloTower->outerEt();
    double ehocal  = caloTower->outerEnergy();
    if (ethocal > theThreshold_HO  &&  ehocal > 3.*noiseHOcal(*caloTower)) {
      HCALcontribution += ethocal;
    }

    bool inUnionCone = false;
    for (unsigned int i = 0;  i < numberOfDaughters();  i++) {
      double dphi = daughter(i)->phi() - caloTower->phi();
      while (dphi > M_PI) dphi -= 2.*M_PI;
      while (dphi < -M_PI) dphi += 2.*M_PI;
      double deta = daughter(i)->eta() - caloTower->eta();
      double dR = sqrt(pow(dphi, 2) + pow(deta, 2));
      if (dR < unionCone) {
        inUnionCone = true;
        break;
      }
    }
    if (inUnionCone) {
      m_unionECALIsolation += ECALcontribution;
      m_unionHCALIsolation += HCALcontribution;
    }

    double dphi = phi() - caloTower->phi();
    while (dphi > M_PI) dphi -= 2.*M_PI;
    while (dphi < -M_PI) dphi += 2.*M_PI;
    double deta = eta() - caloTower->eta();
    double dR = sqrt(pow(dphi, 2) + pow(deta, 2));
    if (dR < centralCone) {
      m_centralECALIsolation += ECALcontribution;
      m_centralHCALIsolation += HCALcontribution;
    }
  }
}

bool pat::MultiMuon::overlaps(const pat::MultiMuon &aMultiMuon) const {
  for (unsigned int i = 0;  i < numberOfDaughters();  i++) {
    const pat::Muon *daughter_i = muon(i);

    for (unsigned int j = 0;  j < aMultiMuon.numberOfDaughters();  j++) {
      const pat::Muon *daughter_j = aMultiMuon.muon(j);

      if (daughter_i->innerTrack().isAvailable()  &&  daughter_j->innerTrack().isAvailable()) {
        if (sameTrack(&*(daughter_i->innerTrack()), &*(daughter_j->innerTrack()))) return true;
      }
      else if (daughter_i->outerTrack().isAvailable()  &&  daughter_j->outerTrack().isAvailable()) {
        if (sameTrack(&*(daughter_i->outerTrack()), &*(daughter_j->outerTrack()))) return true;
      }
    }
  }
  return false;
}

bool pat::MultiMuon::contains(const pat::Muon &aMuon) const {
  for (unsigned int i = 0;  i < numberOfDaughters();  i++) {
    const pat::Muon *daughter_i = muon(i);

    if (daughter_i->innerTrack().isAvailable()  &&  aMuon.innerTrack().isAvailable()) {
      if (sameTrack(&*(daughter_i->innerTrack()), &*(aMuon.innerTrack()))) return true;
    }
    else if (daughter_i->outerTrack().isAvailable()  &&  aMuon.outerTrack().isAvailable()) {
      if (sameTrack(&*(daughter_i->outerTrack()), &*(aMuon.outerTrack()))) return true;
    }
  }
  return false;
}

pat::MultiMuon pat::MultiMuon::merge( const pat::MultiMuon &aMultiMuon,
                                      const TransientTrackBuilder *transientTrackBuilder,
                                      const reco::TrackCollection *tracks,
                                      const pat::MuonCollection *allmuons,
                                      const CaloTowerCollection *caloTowers,
                                      double centralTrackIsolationCone,
                                      double unionTrackIsolationCone,
                                      double centralTrackThresholdPt,
                                      double unionTrackThresholdPt,
                                      double centralCaloIsolationCone,
                                      double unionCaloIsolationCone,
                                      double centralNumberAboveThresholdCone,
                                      double unionNumberAboveThresholdCone,
                                      double centralNumberAboveThresholdPt,
                                      double unionNumberAboveThresholdPt) {
  
  std::vector<const pat::Muon*> muons;

  for (unsigned int i = 0;  i < numberOfDaughters();  i++) {
    muons.push_back(muon(i));
  }

  for (unsigned int j = 0;  j < aMultiMuon.numberOfDaughters();  j++) {
    const pat::Muon *daughter_j = aMultiMuon.muon(j);

    bool same = false;
    for (unsigned int i = 0;  i < numberOfDaughters();  i++) {
      const pat::Muon *daughter_i = muon(i);

      if (daughter_i->innerTrack().isAvailable()  &&  daughter_j->innerTrack().isAvailable()) {
        if (sameTrack(&*(daughter_i->innerTrack()), &*(daughter_j->innerTrack()))) {
          same = true;
          break;
        }
      }
      else if (daughter_i->outerTrack().isAvailable()  &&  daughter_j->outerTrack().isAvailable()) {
        if (sameTrack(&*(daughter_i->outerTrack()), &*(daughter_j->outerTrack()))) {
          same = true;
          break;
        }
      }
    }

    if (!same) muons.push_back(daughter_j);
  }

  return pat::MultiMuon(muons, transientTrackBuilder, tracks, allmuons, caloTowers, centralTrackIsolationCone, unionTrackIsolationCone, centralTrackThresholdPt, unionTrackThresholdPt, centralCaloIsolationCone, unionCaloIsolationCone, centralNumberAboveThresholdCone, unionNumberAboveThresholdCone, centralNumberAboveThresholdPt, unionNumberAboveThresholdPt);
}

void pat::MultiMuon::checkVertex() const {
  if (!m_vertexValid) {
    throw cms::Exception("MultiMuon") << "Request for vertex information, but no vertex has been calculated.";
  }
}

void pat::MultiMuon::checkConsistentVtx() const {
  if (!m_consistentVtxValid) {
    throw cms::Exception("MultiMuon") << "Request for consistent vertex information, but no vertex has been calculated.";
  }
}

bool pat::MultiMuon::sameTrack(const reco::Track *one, const reco::Track *two) const {
  return (fabs(one->px() - two->px()) < 1e-10  &&
           fabs(one->py() - two->py()) < 1e-10  &&
           fabs(one->pz() - two->pz()) < 1e-10  &&
           fabs(one->vx() - two->vx()) < 1e-10  &&
           fabs(one->vy() - two->vy()) < 1e-10  &&
           fabs(one->vz() - two->vz()) < 1e-10    );
}

double pat::MultiMuon::noiseEcal(const CaloTower &tower) const {
  const double theNoiseTow_EB = 0.04;
  const double theNoiseTow_EE = 0.15;
  return (fabs(tower.eta()) > 1.479 ? theNoiseTow_EE : theNoiseTow_EB);
}

double pat::MultiMuon::noiseHcal(const CaloTower &tower) const {
  const double theNoise_HB = 0.2;
  const double theNoise_HE = 0.2;
  return (fabs(tower.eta()) > 1.479 ? theNoise_HE : theNoise_HB);
}

double pat::MultiMuon::noiseHOcal(const CaloTower &tower) const {
  const double theNoise_HO = 0.2;
  return theNoise_HO;
}

GlobalVector pat::MultiMuon::daughterCOM(int i, bool vertex) const {
  double betax = 0.;
  double betay = 0.;
  double betaz = 0.;
  GlobalVector d;

  if (vertex) {
    LorentzVector p = vertexP4();
    betax = -p.px() / p.energy();
    betay = -p.py() / p.energy();
    betaz = -p.pz() / p.energy();
    d = vertexMomentum(i);
  }
  else {
    betax = -px() / energy();
    betay = -py() / energy();
    betaz = -pz() / energy();
    d = GlobalVector(daughter(i)->px(), daughter(i)->py(), daughter(i)->pz());
  }

  double gamma = 1. / sqrt(1. - pow(betax, 2) - pow(betay, 2) - pow(betaz, 2));
  double bgam = pow(gamma, 2) / (1. + gamma);

  double denergy = sqrt(pow(daughter(i)->mass(), 2) + pow(d.x(), 2) + pow(d.y(), 2) + pow(d.z(), 2));

  // double E  = denergy*(gamma) +       d.x()*(gamma*betax) +             d.y()*(gamma*betay) +             d.z()*(gamma*betaz);
  double px = denergy*(gamma*betax) + d.x()*(1. + bgam * betax*betax) + d.y()*(bgam * betax * betay) +    d.z()*(bgam * betax * betaz);
  double py = denergy*(gamma*betay) + d.x()*(bgam * betax * betay) +    d.y()*(1. + bgam * betay*betay) + d.z()*(bgam * betay * betaz);
  double pz = denergy*(gamma*betaz) + d.x()*(bgam * betax * betaz) +    d.y()*(bgam * betay * betaz) +    d.z()*(1. + bgam * betaz*betaz);

  return GlobalVector(px, py, pz);
}

GlobalVector pat::MultiMuon::daughterCOMrot(int i, bool vertex) const {
  GlobalVector d = daughterCOM(i, vertex);

  double anglexz = atan2(px(), pz());
  double arotxz1 = d.x()*cos(anglexz) + d.y()*0. - d.z()*sin(anglexz);
  double arotxz2 = d.x()*0.           + d.y()*1. + d.z()*0.;
  double arotxz3 = d.x()*sin(anglexz) + d.y()*0. + d.z()*cos(anglexz);

  double angleyz = atan2(py(), sqrt(pow(px(), 2) + pow(pz(), 2)));
  double arot1 = arotxz1*1. + arotxz2*0.           + arotxz3*0.;
  double arot2 = arotxz1*0. + arotxz2*cos(angleyz) - arotxz3*sin(angleyz);
  double arot3 = arotxz1*0. + arotxz2*sin(angleyz) + arotxz3*cos(angleyz);

  return GlobalVector(arot1, arot2, arot3);
}

double pat::MultiMuon::daughterCOMcosTheta(int i, bool vertex) const {
  GlobalVector d = daughterCOMrot(i, vertex);
  return d.z() / d.mag();
}

std::vector<std::pair<int,int> > pat::MultiMuon::consistentPairs(bool vertex) const {
  std::vector<int> positives, negatives;
  for (unsigned int i = 0;  i < numberOfDaughters();  i++) {
    if (daughter(i)->charge() > 0) {
      positives.push_back(i);
    } else {
      negatives.push_back(i);
    }
  }

  std::vector<int> largerset, smallerset;
  if (positives.size() > negatives.size()) {
    largerset = positives;
    smallerset = negatives;
  } else {
    largerset = negatives;
    smallerset = positives;
  }

  std::vector<std::vector<int> > permutations;
  std::vector<int> working;
  buildPermutation(permutations, working, 0, largerset.size() - 1);

  std::vector<int> bestPermutation;
  double minMassDistance = -1.;
  for (std::vector<std::vector<int> >::const_iterator permutation = permutations.begin();  permutation != permutations.end();  ++permutation) {
    std::vector<double> masses;
    unsigned int smallerset_index = 0;
    for (std::vector<int>::const_iterator largerset_index = permutation->begin();  largerset_index != permutation->end();  ++largerset_index, ++smallerset_index) {
      if (smallerset_index < smallerset.size()) {
        GlobalVector muon1, muon2;

        if (vertex) {
          muon1 = vertexMomentum(largerset[*largerset_index]);
          muon2 = vertexMomentum(smallerset[smallerset_index]);
        } else {
          reco::Candidate::Vector v1 = daughter(largerset[*largerset_index])->momentum();
          reco::Candidate::Vector v2 = daughter(smallerset[smallerset_index])->momentum();
          muon1 = GlobalVector(v1.x(), v1.y(), v1.z());
          muon2 = GlobalVector(v2.x(), v2.y(), v2.z());
        }
        
        double muon_mass    = daughter(largerset[*largerset_index])->mass();  // get the muon mass from CMSSW
        double total_energy = sqrt(muon1.mag2() + pow(muon_mass, 2)) + sqrt(muon2.mag2() + pow(muon_mass, 2));
        double total_px     = muon1.x() + muon2.x();
        double total_py     = muon1.y() + muon2.y();
        double total_pz     = muon1.z() + muon2.z();
        double mass         = sqrt(pow(total_energy, 2) - pow(total_px, 2) - pow(total_py, 2) - pow(total_pz, 2));

        masses.push_back(mass);
      }
    }

    double massDistance = 0.;
    for (unsigned int i = 0;  i < masses.size();  i++) {
      for (unsigned int j = i + 1;  j < masses.size();  j++) {
        massDistance += pow(masses[i] - masses[j], 2);
      }
    }

    if (minMassDistance < 0.  ||  massDistance < minMassDistance) {
      bestPermutation = *permutation;
      minMassDistance = massDistance;
    }
  }

  std::vector<std::pair<int,int> > output;
  unsigned int smallerset_index = 0;
  for (std::vector<int>::const_iterator largerset_index = bestPermutation.begin();  largerset_index != bestPermutation.end();  ++largerset_index, ++smallerset_index) {
    if (smallerset_index < smallerset.size()) {
	     if (daughter(largerset[*largerset_index])->charge() > 0) {
	        output.push_back(std::pair<int,int>(largerset[*largerset_index], smallerset[smallerset_index]));
	     } else {
	        output.push_back(std::pair<int,int>(smallerset[smallerset_index], largerset[*largerset_index]));
	     }
    }
  }
  
  return output;
}

void pat::MultiMuon::buildPermutation(std::vector<std::vector<int> > &results, std::vector<int> working, int where, int value) const {
  std::vector<int>::iterator iter = working.begin();
  for (int i = 0;  i < where;  i++) ++iter;
  working.insert(iter, value);

  if (value - 1 >= 0) {
    for (unsigned int i = 0;  i <= working.size();  i++) {
      buildPermutation(results, working, i, value - 1);
    }
  } else {
    results.push_back(working);
  }
}

std::vector<double> pat::MultiMuon::consistentPairMasses(bool vertex) const {
  std::vector<std::pair<int,int> > pairIndicies = consistentPairs(vertex);
  std::vector<double> output;

  for (std::vector<std::pair<int,int> >::const_iterator pairIndex = pairIndicies.begin();  pairIndex != pairIndicies.end();  ++pairIndex) {
    GlobalVector muon1, muon2;

    assert(daughter(pairIndex->first)->charge() > 0);
    assert(daughter(pairIndex->second)->charge() < 0);

    if (vertex) {
      muon1 = vertexMomentum(pairIndex->first);
      muon2 = vertexMomentum(pairIndex->second);
    } else {
      reco::Candidate::Vector v1 = daughter(pairIndex->first)->momentum();
      reco::Candidate::Vector v2 = daughter(pairIndex->second)->momentum();
      muon1 = GlobalVector(v1.x(), v1.y(), v1.z());
      muon2 = GlobalVector(v2.x(), v2.y(), v2.z());
    }
    double muon_mass = daughter(pairIndex->first)->mass();  // get the muon mass from CMSSW
    double total_energy = sqrt(muon1.mag2() + pow(muon_mass, 2)) + sqrt(muon2.mag2() + pow(muon_mass, 2));
    double total_px = muon1.x() + muon2.x();
    double total_py = muon1.y() + muon2.y();
    double total_pz = muon1.z() + muon2.z();
    double mass = sqrt(pow(total_energy, 2) - pow(total_px, 2) - pow(total_py, 2) - pow(total_pz, 2));

    output.push_back(mass);
  }

  return output;
}
