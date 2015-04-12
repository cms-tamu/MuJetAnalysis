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
  setP4( PolarLorentzVector(lorentzVector.pt(),lorentzVector.eta(),lorentzVector.phi(),lorentzVector.mass()));

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
pat::MultiMuon::MultiMuon(const pat::MultiMuon &aMultiMuon) : 
  pat::MultiLepton<Muon>(aMultiMuon) 
{
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

void pat::MultiMuon::calculateNumberAboveThresholdIsolation(const reco::TrackCollection *tracks,
							    const pat::MuonCollection *allmuons,
							    double centralCone,
							    double unionCone,
							    double centralThreshold,
							    double unionThreshold,
							    TTree *diagnosticTTree,
							    Float_t *diagnosticdR,
							    Float_t *diagnosticpT) 
{
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
