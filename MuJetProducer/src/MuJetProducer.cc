// -*- C++ -*-
//
// Package:    MuJetProducer
// Class:      MuJetProducer
//
/**\class MuJetProducer MuJetProducer.cc MuJetAnalysis/MuJetProducer/src/MuJetProducer.cc

Description: <one line class summary>

Implementation:
<Notes on implementation>
*/
//
// Jim Pivarski <pivarski@physics.tamu.edu>
//
//         Created:  Mon Feb  8 23:07:29 CST 2010
// $Id: MuJetProducer.cc,v 1.6 2013/03/05 23:16:04 pakhotin Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "MuJetAnalysis/DataFormats/interface/MultiMuon.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"
//
// class decleration
//


class MuJetProducer : public edm::EDProducer {
  public:
  explicit MuJetProducer(const edm::ParameterSet&);
  ~MuJetProducer();

  private:
  virtual void beginJob() ;
  virtual void produce(edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

  bool muonOkay(const pat::Muon &muon);

  enum {
    kGroupByDeltaR,
    kGroupByMass,
    kGroupByVertexProb,
    kGroupByDeltaRAndVertexProb,
    kGroupByMassAndVertexProb,
    kGroupByDeltaROrMass,
    kGroupByDeltaRAndMass,
    kGroupByDeltaROrMassAndVertexProb,
    kGroupByMassAndVertexProbOrDeltaR,

    kGroupByAnyCharge,
    kGroupByOppositeCharge,
    kGroupBySameCharge
  };

  // ----------member data ---------------------------
  edm::EDGetTokenT<pat::MuonCollection> m_muons;
  //edm::InputTag m_tracks;
  //edm::InputTag m_caloTowers;
  double m_minPt;
  double m_minPmag;
  double m_maxAbsEta;
  bool m_selectTrackerMuons;
  bool m_selectGlobalMuons;
  int m_minTrackerHits;
  double m_maxTrackerNormChi2;
  double m_maxTrackerDxy;
  double m_maxTrackerDz;
  double m_maxQoverpError;
  double m_maxPhiError;
  double m_maxEtaError;
  double m_maxDxyError;
  double m_maxDzError;
  int m_minOuterHits;
  double m_maxOuterNormChi2;
  double m_maxGlobalNormChi2;
  double m_maxStaRelChi2;
  int m_minSegmentMatches;
  std::vector<std::string> m_muonSelectors_strings;
  std::vector<muon::SelectionType> m_muonSelectors;
  std::vector<edm::ParameterSet> m_detailedSelectors;
  std::vector<muon::AlgorithmType> m_detailed_algorithmType;
  std::vector<int> m_detailed_minNumberOfMatches;
  std::vector<double> m_detailed_maxAbsDx;
  std::vector<double> m_detailed_maxAbsPullX;
  std::vector<double> m_detailed_maxAbsDy;
  std::vector<double> m_detailed_maxAbsPullY;
  std::vector<double> m_detailed_maxChamberDist;
  std::vector<double> m_detailed_maxChamberDistPull;
  std::vector<reco::Muon::ArbitrationType> m_detailed_arbitrationType;
  bool m_calculateVertex;
  //bool m_calculateIsolation;
  std::string m_groupingMode_string;
  int m_groupingMode;
  double m_maxDeltaR;
  double m_maxMass;
  double m_minVertexProb;
  std::string m_groupByCharge_string;
  int m_groupByCharge;
  //double m_centralTrackIsolationCone;
  //double m_unionTrackIsolationCone;
  //double m_centralTrackThresholdPt;
  //double m_unionTrackThresholdPt;
  //double m_centralCaloIsolationCone;
  //double m_unionCaloIsolationCone;
  //double m_centralNumberAboveThresholdCone;
  //double m_unionNumberAboveThresholdCone;
  //double m_centralNumberAboveThresholdPt;
  //double m_unionNumberAboveThresholdPt;
  int m_barrelPixelLayer;
  int m_endcapPixelLayer;
};

//
// constants, enums and typedefs
//


//
// static data member definitions
//

//
// constructors and destructor
//
MuJetProducer::MuJetProducer(const edm::ParameterSet& iConfig)
   : m_muons(                           consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("muons")))
   //, m_tracks(                          iConfig.getParameter<edm::InputTag>("tracks"))
   //, m_caloTowers(                      iConfig.getParameter<edm::InputTag>("caloTowers"))
   , m_minPt(                           iConfig.getParameter<double>("minPt"))
   , m_minPmag(                         iConfig.getParameter<double>("minPmag"))
   , m_maxAbsEta(                       iConfig.getParameter<double>("maxAbsEta"))
   , m_selectTrackerMuons(              iConfig.getParameter<bool>("selectTrackerMuons"))
   , m_selectGlobalMuons(               iConfig.getParameter<bool>("selectGlobalMuons"))
   , m_minTrackerHits(                  iConfig.getParameter<int>("minTrackerHits"))
   , m_maxTrackerNormChi2(              iConfig.getParameter<double>("maxTrackerNormChi2"))
   , m_maxTrackerDxy(                   iConfig.getParameter<double>("maxTrackerDxy"))
   , m_maxTrackerDz(                    iConfig.getParameter<double>("maxTrackerDz"))
   , m_maxQoverpError(                  iConfig.getParameter<double>("maxQoverpError"))
   , m_maxPhiError(                     iConfig.getParameter<double>("maxPhiError"))
   , m_maxEtaError(                     iConfig.getParameter<double>("maxEtaError"))
   , m_maxDxyError(                     iConfig.getParameter<double>("maxDxyError"))
   , m_maxDzError(                      iConfig.getParameter<double>("maxDzError"))
   , m_minOuterHits(                    iConfig.getParameter<int>("minOuterHits"))
   , m_maxOuterNormChi2(                iConfig.getParameter<double>("maxOuterNormChi2"))
   , m_maxGlobalNormChi2(               iConfig.getParameter<double>("maxGlobalNormChi2"))
   , m_maxStaRelChi2(                   iConfig.getParameter<double>("maxStaRelChi2"))
   , m_minSegmentMatches(               iConfig.getParameter<int>("minSegmentMatches"))
   , m_muonSelectors_strings(           iConfig.getParameter<std::vector<std::string> >("muonSelectors"))
   , m_detailedSelectors(               iConfig.getParameter<std::vector<edm::ParameterSet> >("detailedSelectors"))
   , m_calculateVertex(                 iConfig.getParameter<bool>("calculateVertex"))
   //, m_calculateIsolation(              iConfig.getParameter<bool>("calculateIsolation"))
   , m_groupingMode_string(             iConfig.getParameter<std::string>("groupingMode"))
   , m_maxDeltaR(                       iConfig.getParameter<double>("maxDeltaR"))
   , m_maxMass(                         iConfig.getParameter<double>("maxMass"))
   , m_minVertexProb(                   iConfig.getParameter<double>("minVertexProb"))
   , m_groupByCharge_string(            iConfig.getParameter<std::string>("groupByCharge"))
   //, m_centralTrackIsolationCone(       iConfig.getParameter<double>("centralTrackIsolationCone"))
   //, m_unionTrackIsolationCone(         iConfig.getParameter<double>("unionTrackIsolationCone"))
   //, m_centralTrackThresholdPt(         iConfig.getParameter<double>("centralTrackThresholdPt"))
   //, m_unionTrackThresholdPt(           iConfig.getParameter<double>("unionTrackThresholdPt"))
   //, m_centralCaloIsolationCone(        iConfig.getParameter<double>("centralCaloIsolationCone"))
   //, m_unionCaloIsolationCone(          iConfig.getParameter<double>("unionCaloIsolationCone"))
   //, m_centralNumberAboveThresholdCone( iConfig.getParameter<double>("centralNumberAboveThresholdCone"))
   //, m_unionNumberAboveThresholdCone(   iConfig.getParameter<double>("unionNumberAboveThresholdCone"))
   //, m_centralNumberAboveThresholdPt(   iConfig.getParameter<double>("centralNumberAboveThresholdPt"))
   //, m_unionNumberAboveThresholdPt(     iConfig.getParameter<double>("unionNumberAboveThresholdPt"))
   , m_barrelPixelLayer(                iConfig.getParameter<int>("barrelPixelLayer"))
   , m_endcapPixelLayer(                iConfig.getParameter<int>("endcapPixelLayer"))
{
  //register your products
  produces<pat::MultiMuonCollection>("Pairs");
  produces<pat::MuonCollection>("Orphans");
  produces<pat::MultiMuonCollection>();

  //now do what ever other initialization is needed
  if       (m_groupingMode_string == "GroupByDeltaR"                  ) m_groupingMode = kGroupByDeltaR;
  else if (m_groupingMode_string == "GroupByMass"                     ) m_groupingMode = kGroupByMass;
  else if (m_groupingMode_string == "GroupByVertexProb"               ) m_groupingMode = kGroupByVertexProb;
  else if (m_groupingMode_string == "GroupByDeltaRAndVertexProb"      ) m_groupingMode = kGroupByDeltaRAndVertexProb;
  else if (m_groupingMode_string == "GroupByMassAndVertexProb"        ) m_groupingMode = kGroupByMassAndVertexProb;
  else if (m_groupingMode_string == "GroupByDeltaROrMass"             ) m_groupingMode = kGroupByDeltaROrMass;
  else if (m_groupingMode_string == "GroupByDeltaRAndMass"            ) m_groupingMode = kGroupByDeltaRAndMass;
  else if (m_groupingMode_string == "GroupByDeltaROrMassAndVertexProb") m_groupingMode = kGroupByDeltaROrMassAndVertexProb;
  else if (m_groupingMode_string == "GroupByMassAndVertexProbOrDeltaR") m_groupingMode = kGroupByMassAndVertexProbOrDeltaR;
  else {
    throw cms::Exception("BadConfig") << "groupingMode string not recognized (see MuJetProducer.cc)" << std::endl;
  }

  if       (m_groupByCharge_string == "any"     ) m_groupByCharge = kGroupByAnyCharge;
  else if (m_groupByCharge_string == "opposite") m_groupByCharge = kGroupByOppositeCharge;
  else if (m_groupByCharge_string == "same"    ) m_groupByCharge = kGroupBySameCharge;
  else {
    throw cms::Exception("BadConfig") << "groupByCharge string not recognized (see MuJetProducer.cc)" << std::endl;
  }

  for (std::vector<std::string>::const_iterator muonSelector = m_muonSelectors_strings.begin();  muonSelector != m_muonSelectors_strings.end();  ++muonSelector) {
    m_muonSelectors.push_back(muon::selectionTypeFromString(*muonSelector));
  }

  for (std::vector<edm::ParameterSet>::const_iterator detailedSelector = m_detailedSelectors.begin();  detailedSelector != m_detailedSelectors.end();  ++detailedSelector) {
    std::string algorithmType = detailedSelector->getParameter<std::string>("algorithm");
    if       (algorithmType == std::string("TMLastStation")   ) m_detailed_algorithmType.push_back(muon::TMLastStation);
    else if (algorithmType == std::string("TM2DCompatibility")) m_detailed_algorithmType.push_back(muon::TM2DCompatibility);
    else if (algorithmType == std::string("TMOneStation")     ) m_detailed_algorithmType.push_back(muon::TMOneStation);
    else {
      throw cms::Exception("BadConfig") << "algorithm must be one of \"TMLastStation\", \"TM2DCompatibility\", \"TMOneStation\"" << std::endl;
    }

    m_detailed_minNumberOfMatches.push_back( detailedSelector->getParameter<int>(   "minNumberOfMatches"));
    m_detailed_maxAbsDx.push_back(           detailedSelector->getParameter<double>("maxAbsDx"));
    m_detailed_maxAbsPullX.push_back(        detailedSelector->getParameter<double>("maxAbsPullX"));
    m_detailed_maxAbsDy.push_back(           detailedSelector->getParameter<double>("maxAbsDy"));
    m_detailed_maxAbsPullY.push_back(        detailedSelector->getParameter<double>("maxAbsPullY"));
    m_detailed_maxChamberDist.push_back(     detailedSelector->getParameter<double>("maxChamberDist"));
    m_detailed_maxChamberDistPull.push_back( detailedSelector->getParameter<double>("maxChamberDistPull"));

    std::string arbitrationType = detailedSelector->getParameter<std::string>("arbitrationType");
    if       (arbitrationType == std::string("NoArbitration")            ) m_detailed_arbitrationType.push_back(reco::Muon::NoArbitration);
    else if (arbitrationType == std::string("SegmentArbitration")        ) m_detailed_arbitrationType.push_back(reco::Muon::SegmentArbitration);
    else if (arbitrationType == std::string("SegmentAndTrackArbitration")) m_detailed_arbitrationType.push_back(reco::Muon::SegmentAndTrackArbitration);
    else {
      throw cms::Exception("BadConfig") << "arbitrationType must be one of \"NoArbitration\", \"SegmentArbitration\", \"SegmentAndTrackArbitration\"" << std::endl;
    }
  }
}


MuJetProducer::~MuJetProducer()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

bool MuJetProducer::muonOkay(const pat::Muon &muon) {
  if (muon.pt() < m_minPt  ||  muon.p() < m_minPmag  ||  fabs(muon.eta()) > m_maxAbsEta) return false;

  if (m_selectTrackerMuons  &&  !muon.isTrackerMuon() ) return false;
  if (m_selectGlobalMuons   &&  !muon.isGlobalMuon()  ) return false;

  if (m_minTrackerHits > 0) {
    if (muon.innerTrack().isNull()) return false;
    if (muon.innerTrack()->numberOfValidHits() < m_minTrackerHits) return false;
  }

  if (m_maxTrackerNormChi2 > 0.) {
    if (muon.innerTrack().isNull()) return false;
    if (muon.innerTrack()->normalizedChi2() > m_maxTrackerNormChi2) return false;
  }

  if (m_maxTrackerDxy > 0.) {
    if (muon.innerTrack().isNull()) return false;
    if (fabs(muon.innerTrack()->dxy()) > m_maxTrackerDxy) return false;
  }

  if (m_maxTrackerDz > 0.) {
    if (muon.innerTrack().isNull()) return false;
    if (fabs(muon.innerTrack()->dsz()) > m_maxTrackerDz) return false;
  }

  if (m_maxQoverpError > 0.) {
    if (muon.innerTrack().isNull()) return false;
    if (muon.innerTrack()->qoverpError() > m_maxQoverpError) return false;
  }

  if (m_maxPhiError > 0.) {
    if (muon.innerTrack().isNull()) return false;
    if (muon.innerTrack()->phiError() > m_maxPhiError) return false;
  }

  if (m_maxEtaError > 0.) {
    if (muon.innerTrack().isNull()) return false;
    if (muon.innerTrack()->etaError() > m_maxEtaError) return false;
  }

  if (m_maxDxyError > 0.) {
    if (muon.innerTrack().isNull()) return false;
    if (muon.innerTrack()->dxyError() > m_maxDxyError) return false;
  }

  if (m_maxDzError > 0.) {
    if (muon.innerTrack().isNull()) return false;
    if (muon.innerTrack()->dzError() > m_maxDzError) return false;
  }

  if (m_minOuterHits > 0) {
    if (muon.outerTrack().isNull()) return false;
    if (muon.outerTrack()->numberOfValidHits() < m_minOuterHits) return false;
  }

  if (m_maxOuterNormChi2 > 0.) {
    if (muon.outerTrack().isNull()) return false;
    if (muon.outerTrack()->normalizedChi2() > m_maxOuterNormChi2) return false;
  }

  if (m_maxGlobalNormChi2 > 0.) {
    if (muon.globalTrack().isNull()) return false;
    if (muon.globalTrack()->normalizedChi2() > m_maxGlobalNormChi2) return false;
  }

  if (m_maxStaRelChi2 > 0.) {
    if (!muon.isQualityValid()) return false;
    if (muon.combinedQuality().staRelChi2 > m_maxStaRelChi2) return false;
  }

  if (m_minSegmentMatches > 0) {
    if (muon.numberOfMatches(reco::Muon::SegmentAndTrackArbitration) < m_minSegmentMatches) return false;
  }

  for (std::vector<muon::SelectionType>::const_iterator muonSelector = m_muonSelectors.begin();  muonSelector != m_muonSelectors.end();  ++muonSelector) {
    if (!muon::isGoodMuon(muon, *muonSelector)) return false;
  }

  std::vector<muon::AlgorithmType>::const_iterator algorithmType = m_detailed_algorithmType.begin();
  std::vector<int>::const_iterator                        minNumberOfMatches = m_detailed_minNumberOfMatches.begin();
  std::vector<double>::const_iterator                     maxAbsDx           = m_detailed_maxAbsDx.begin();
  std::vector<double>::const_iterator                     maxAbsPullX        = m_detailed_maxAbsPullX.begin();
  std::vector<double>::const_iterator                     maxAbsDy           = m_detailed_maxAbsDy.begin();
  std::vector<double>::const_iterator                     maxAbsPullY        = m_detailed_maxAbsPullY.begin();
  std::vector<double>::const_iterator                     maxChamberDist     = m_detailed_maxChamberDist.begin();
  std::vector<double>::const_iterator                     maxChamberDistPull = m_detailed_maxChamberDistPull.begin();
  std::vector<reco::Muon::ArbitrationType>::const_iterator arbitrationType    = m_detailed_arbitrationType.begin();

  for (;  algorithmType != m_detailed_algorithmType.end();  ++algorithmType, ++minNumberOfMatches, ++maxAbsDx, ++maxAbsPullX, ++maxAbsDy, ++maxAbsPullY, ++maxChamberDist, ++maxChamberDistPull, ++arbitrationType) {
    if (!muon::isGoodMuon(muon, *algorithmType, *minNumberOfMatches, *maxAbsDx, *maxAbsPullX, *maxAbsDy, *maxAbsPullY, *maxChamberDist, *maxChamberDistPull, *arbitrationType)) return false;
  }

  return true;
}

// ------------ method called to produce the data  ------------
void MuJetProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  edm::Handle<pat::MuonCollection> muons;
  iEvent.getByToken(m_muons, muons);
//  const pat::MuonCollection *muons_ptr = &*muons;
/*
  edm::Handle<reco::TrackCollection> tracks;
  edm::Handle<CaloTowerCollection> caloTowers;
  const reco::TrackCollection *tracks_ptr = NULL;
  const CaloTowerCollection *caloTowers_ptr = NULL;
  if (m_calculateIsolation) {
    iEvent.getByLabel(m_tracks, tracks);
    iEvent.getByLabel(m_caloTowers, caloTowers);
    tracks_ptr = &*tracks;
    caloTowers_ptr = &*caloTowers;
  }*/

  edm::ESHandle<TransientTrackBuilder> transientTrackBuilder;
  const TransientTrackBuilder *transientTrackBuilder_ptr = NULL;
  if (m_calculateVertex) {
    iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder", transientTrackBuilder);
    transientTrackBuilder_ptr = &*transientTrackBuilder;
  }

  // output #1: a collection of pairs of muons
  std::unique_ptr<pat::MultiMuonCollection> Pairs(new pat::MultiMuonCollection);

  // set of jets and intermediate jets (pairs are all intermediate jets)
  // true means active (can be merged), false means inactive (already merged: data is in the merged jet)
  std::vector<pat::MultiMuon> jets;
  std::vector<bool> active;

  std::map<const pat::Muon*,bool> used;
  for (pat::MuonCollection::const_iterator one = muons->begin();  one != muons->end();  ++one) {
    if (muonOkay(*one)) {
	    for (pat::MuonCollection::const_iterator two = one;  two != muons->end();  ++two) {
	      if (one != two  &&  muonOkay(*two)) {

          std::vector<const pat::Muon*> pairOfMuons;
          pairOfMuons.push_back(&*one);
          pairOfMuons.push_back(&*two);
//Checkpoint
          pat::MultiMuon muonPair( pairOfMuons,
                                   transientTrackBuilder_ptr,
                                   //tracks_ptr,
                                   //muons_ptr,
                                   //caloTowers_ptr,
                                   //m_centralTrackIsolationCone,
                                   //m_unionTrackIsolationCone,
                                   //m_centralTrackThresholdPt,
                                   //m_unionTrackThresholdPt,
                                   //m_centralCaloIsolationCone,
                                   //m_unionCaloIsolationCone,
                                   //m_centralNumberAboveThresholdCone,
                                   //m_unionNumberAboveThresholdCone,
                                   //m_centralNumberAboveThresholdPt,
								   //m_unionNumberAboveThresholdPt,
								   m_barrelPixelLayer,
								   m_endcapPixelLayer);

          bool satisfied_deltaR = (muonPair.dR(0, 1, muonPair.vertexValid()) < m_maxDeltaR);

          bool satisfied_mass = (muonPair.mass() < m_maxMass);

          bool satisfied_vertexProb = (muonPair.vertexValid()  &&  muonPair.vertexProb() > m_minVertexProb);

          bool satisfied = false;
          if       (m_groupingMode == kGroupByDeltaR                  ) satisfied = satisfied_deltaR;
          else if (m_groupingMode == kGroupByMass                     ) satisfied = satisfied_mass;
          else if (m_groupingMode == kGroupByVertexProb               ) satisfied = satisfied_vertexProb;
          else if (m_groupingMode == kGroupByDeltaRAndVertexProb      ) satisfied = satisfied_deltaR  &&  satisfied_vertexProb;
          else if (m_groupingMode == kGroupByMassAndVertexProb        ) satisfied = satisfied_mass    &&  satisfied_vertexProb;
          else if (m_groupingMode == kGroupByDeltaROrMass             ) satisfied = satisfied_deltaR  ||  satisfied_mass;
          else if (m_groupingMode == kGroupByDeltaRAndMass            ) satisfied = satisfied_deltaR  &&  satisfied_mass;
          else if (m_groupingMode == kGroupByDeltaROrMassAndVertexProb) satisfied = (satisfied_deltaR ||  satisfied_mass)        &&  satisfied_vertexProb;
          else if (m_groupingMode == kGroupByMassAndVertexProbOrDeltaR) satisfied = satisfied_mass    &&  (satisfied_vertexProb  ||  satisfied_deltaR);
          else     assert(false);

          if      (m_groupByCharge == kGroupByAnyCharge     ) satisfied = satisfied;
          else if (m_groupByCharge == kGroupByOppositeCharge) satisfied = satisfied  &&  (one->charge() != two->charge());
          else if (m_groupByCharge == kGroupBySameCharge    ) satisfied = satisfied  &&  (one->charge() == two->charge());

          // keep only the ones that have a small opening angle (calculated using vertexing)
          if (satisfied) {
            Pairs->push_back(muonPair);

            jets.push_back(muonPair);
            active.push_back(true);

            used[&*one] = true;
            used[&*two] = true;
          }
	      }
	    }
    }
  }

  // output #2: a collection of muons not belonging to any surviving pair
  std::unique_ptr<pat::MuonCollection> Orphans(new pat::MuonCollection);
  for (pat::MuonCollection::const_iterator muon = muons->begin();  muon != muons->end();  ++muon) {
    if (muonOkay(*muon)) {
      bool isUsed = false;
      for (std::map<const pat::Muon*,bool>::const_iterator iter = used.begin();  iter != used.end();  ++iter) {
        if (&*muon == iter->first) isUsed = true;
      }

      if (!isUsed) {
        pat::Muon newMuon(*muon);
        Orphans->push_back(newMuon);
      }
    }
  }

  // consolidate jets: group them into equivalence classes
  // if they overlap, merge them and only consider the merged version from that point onward
  // continue until there is nothing left to merge
  int newjets_size;
  do {
    std::vector<pat::MultiMuon> newjets;
    for (unsigned int i = 0;  i < jets.size();  i++) {
      for (unsigned int j = i+1;  j < jets.size();  j++) {

        if (active[i]  &&  active[j]) {
          if (jets[i].overlaps(jets[j])) {
            newjets.push_back( jets[i].merge(jets[j],
                               transientTrackBuilder_ptr
                               //tracks_ptr,
                               //muons_ptr,
                               //caloTowers_ptr,
                               //m_centralTrackIsolationCone,
                               //m_unionTrackIsolationCone,
                               //m_centralTrackThresholdPt,
                               //m_unionTrackThresholdPt,
                               //m_centralCaloIsolationCone,
                               //m_unionCaloIsolationCone,
                               //m_centralNumberAboveThresholdCone,
                               //m_unionNumberAboveThresholdCone,
                               //m_centralNumberAboveThresholdPt,
                               //m_unionNumberAboveThresholdPt
                             ));
            active[i] = false;
            active[j] = false;
          }
        }
      }
    }

    // the new merged jets take the place of the old jets, so the new ones have active == true
    // and the old ones become active == false (above)
    for (std::vector<pat::MultiMuon>::const_iterator nj = newjets.begin();  nj != newjets.end();  ++nj) {
      jets.push_back(*nj);
      active.push_back(true);
    }

    newjets_size = newjets.size();
  } while (newjets_size > 0);

  // output #3: a collection of equivalence classes of shared daughters
  std::unique_ptr<pat::MultiMuonCollection> EquivalenceClasses(new pat::MultiMuonCollection);
  for (unsigned int i = 0;  i < jets.size();  i++) {
    if (active[i]) EquivalenceClasses->push_back(jets[i]);
  }

  iEvent.put(std::move(Pairs), "Pairs");
  iEvent.put(std::move(Orphans), "Orphans");
  iEvent.put(std::move(EquivalenceClasses));
}

// ------------ method called once each job just before starting event loop  ------------
void
MuJetProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
MuJetProducer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(MuJetProducer);
