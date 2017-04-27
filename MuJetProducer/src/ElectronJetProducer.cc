// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "MuJetAnalysis/DataFormats/interface/MultiElectron.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
//#include "DataFormats/MuonReco/interface/MuonSelectors.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

//
// class decleration
//


class ElectronJetProducer : public edm::EDProducer {
  public:
  explicit ElectronJetProducer(const edm::ParameterSet&);
  ~ElectronJetProducer();

  private:
  virtual void beginJob() ;
  virtual void produce(edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  bool electronOkay(const pat::Electron &);

  enum {
    kGroupByDeltaR,
    kGroupByMass,
    kGroupByVertexProb,
    kGroupByDeltaRAndVertexProb,
    kGroupByMassAndVertexProb,
    kGroupByDeltaROrMass,
    kGroupByDeltaROrMassAndVertexProb,
    kGroupByMassAndVertexProbOrDeltaR,

    kGroupByAnyCharge,
    kGroupByOppositeCharge,
    kGroupBySameCharge
  };

  // ----------member data ---------------------------
  edm::InputTag m_electrons;
  edm::InputTag m_tracks;
  edm::InputTag m_caloTowers;
  double m_minPt;
  double m_minPmag;
  double m_maxAbsEta;
  bool m_selectTrackerElectrons;
  bool m_selectGlobalElectrons;
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
  std::vector<std::string> m_electronSelectors_strings;
  // std::vector<electron::SelectionType> m_electronSelectors;
  std::vector<edm::ParameterSet> m_detailedSelectors;
  // std::vector<electron::AlgorithmType> m_detailed_algorithmType;
  std::vector<int> m_detailed_minNumberOfMatches;
  std::vector<double> m_detailed_maxAbsDx;
  std::vector<double> m_detailed_maxAbsPullX;
  std::vector<double> m_detailed_maxAbsDy;
  std::vector<double> m_detailed_maxAbsPullY;
  std::vector<double> m_detailed_maxChamberDist;
  std::vector<double> m_detailed_maxChamberDistPull;
  // std::vector<reco::GsfElectron::ArbitrationType> m_detailed_arbitrationType;
  bool m_calculateVertex;
  bool m_calculateIsolation;
  std::string m_groupingMode_string;
  int m_groupingMode;
  double m_maxDeltaR;
  double m_maxMass;
  double m_minVertexProb;
  std::string m_groupByCharge_string;
  int m_groupByCharge;
  double m_centralTrackIsolationCone;
  double m_unionTrackIsolationCone;
  double m_centralTrackThresholdPt;
  double m_unionTrackThresholdPt;
  double m_centralCaloIsolationCone;
  double m_unionCaloIsolationCone;
  double m_centralNumberAboveThresholdCone;
  double m_unionNumberAboveThresholdCone;
  double m_centralNumberAboveThresholdPt;
  double m_unionNumberAboveThresholdPt;
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
ElectronJetProducer::ElectronJetProducer(const edm::ParameterSet& iConfig)
   : m_electrons(                           iConfig.getParameter<edm::InputTag>("electrons"))
   , m_tracks(                          iConfig.getParameter<edm::InputTag>("tracks"))
   , m_caloTowers(                      iConfig.getParameter<edm::InputTag>("caloTowers"))
   , m_minPt(                           iConfig.getParameter<double>("minPt"))
   , m_minPmag(                         iConfig.getParameter<double>("minPmag"))
   , m_maxAbsEta(                       iConfig.getParameter<double>("maxAbsEta"))
   , m_selectTrackerElectrons(              iConfig.getParameter<bool>("selectTrackerElectrons"))
   , m_selectGlobalElectrons(               iConfig.getParameter<bool>("selectGlobalElectrons"))
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
   , m_electronSelectors_strings(           iConfig.getParameter<std::vector<std::string> >("electronSelectors"))
   , m_detailedSelectors(               iConfig.getParameter<std::vector<edm::ParameterSet> >("detailedSelectors"))
   , m_calculateVertex(                 iConfig.getParameter<bool>("calculateVertex"))
   , m_calculateIsolation(              iConfig.getParameter<bool>("calculateIsolation"))
   , m_groupingMode_string(             iConfig.getParameter<std::string>("groupingMode"))
   , m_maxDeltaR(                       iConfig.getParameter<double>("maxDeltaR"))
   , m_maxMass(                         iConfig.getParameter<double>("maxMass"))
   , m_minVertexProb(                   iConfig.getParameter<double>("minVertexProb"))
   , m_groupByCharge_string(            iConfig.getParameter<std::string>("groupByCharge"))
   , m_centralTrackIsolationCone(       iConfig.getParameter<double>("centralTrackIsolationCone"))
   , m_unionTrackIsolationCone(         iConfig.getParameter<double>("unionTrackIsolationCone"))
   , m_centralTrackThresholdPt(         iConfig.getParameter<double>("centralTrackThresholdPt"))
   , m_unionTrackThresholdPt(           iConfig.getParameter<double>("unionTrackThresholdPt"))
   , m_centralCaloIsolationCone(        iConfig.getParameter<double>("centralCaloIsolationCone"))
   , m_unionCaloIsolationCone(          iConfig.getParameter<double>("unionCaloIsolationCone"))
   , m_centralNumberAboveThresholdCone( iConfig.getParameter<double>("centralNumberAboveThresholdCone"))
   , m_unionNumberAboveThresholdCone(   iConfig.getParameter<double>("unionNumberAboveThresholdCone"))
   , m_centralNumberAboveThresholdPt(   iConfig.getParameter<double>("centralNumberAboveThresholdPt"))
   , m_unionNumberAboveThresholdPt(     iConfig.getParameter<double>("unionNumberAboveThresholdPt"))
{
  //register your products
  produces<pat::MultiElectronCollection>("Pairs");
  produces<pat::ElectronCollection>("Orphans");
  produces<pat::MultiElectronCollection>();

  //now do what ever other initialization is needed
  if       (m_groupingMode_string == "GroupByDeltaR"                  ) m_groupingMode = kGroupByDeltaR;
  else if (m_groupingMode_string == "GroupByMass"                     ) m_groupingMode = kGroupByMass;
  else if (m_groupingMode_string == "GroupByVertexProb"               ) m_groupingMode = kGroupByVertexProb;
  else if (m_groupingMode_string == "GroupByDeltaRAndVertexProb"      ) m_groupingMode = kGroupByDeltaRAndVertexProb;
  else if (m_groupingMode_string == "GroupByMassAndVertexProb"        ) m_groupingMode = kGroupByMassAndVertexProb;
  else if (m_groupingMode_string == "GroupByDeltaROrMass"             ) m_groupingMode = kGroupByDeltaROrMass;
  else if (m_groupingMode_string == "GroupByDeltaROrMassAndVertexProb") m_groupingMode = kGroupByDeltaROrMassAndVertexProb;
  else if (m_groupingMode_string == "GroupByMassAndVertexProbOrDeltaR") m_groupingMode = kGroupByMassAndVertexProbOrDeltaR;
  else {
    throw cms::Exception("BadConfig") << "groupingMode string not recognized (see ElectronJetProducer.cc)" << std::endl;
  }

  if       (m_groupByCharge_string == "any"     ) m_groupByCharge = kGroupByAnyCharge;
  else if (m_groupByCharge_string == "opposite") m_groupByCharge = kGroupByOppositeCharge;
  else if (m_groupByCharge_string == "same"    ) m_groupByCharge = kGroupBySameCharge;
  else {
    throw cms::Exception("BadConfig") << "groupByCharge string not recognized (see ElectronJetProducer.cc)" << std::endl;
  }

  // for (std::vector<std::string>::const_iterator electronSelector = m_electronSelectors_strings.begin();  electronSelector != m_electronSelectors_strings.end();  ++electronSelector) {
  //   m_electronSelectors.push_back(electron::selectionTypeFromString(*electronSelector));
  // }

  // for (std::vector<edm::ParameterSet>::const_iterator detailedSelector = m_detailedSelectors.begin();  detailedSelector != m_detailedSelectors.end();  ++detailedSelector) {
  //   std::string algorithmType = detailedSelector->getParameter<std::string>("algorithm");
  //   if       (algorithmType == std::string("TMLastStation")   ) m_detailed_algorithmType.push_back(electron::TMLastStation);
  //   else if (algorithmType == std::string("TM2DCompatibility")) m_detailed_algorithmType.push_back(electron::TM2DCompatibility);
  //   else if (algorithmType == std::string("TMOneStation")     ) m_detailed_algorithmType.push_back(electron::TMOneStation);
  //   else {
  //     throw cms::Exception("BadConfig") << "algorithm must be one of \"TMLastStation\", \"TM2DCompatibility\", \"TMOneStation\"" << std::endl;
  //   }
    
  //   m_detailed_minNumberOfMatches.push_back( detailedSelector->getParameter<int>(   "minNumberOfMatches"));
  //   m_detailed_maxAbsDx.push_back(           detailedSelector->getParameter<double>("maxAbsDx"));
  //   m_detailed_maxAbsPullX.push_back(        detailedSelector->getParameter<double>("maxAbsPullX"));
  //   m_detailed_maxAbsDy.push_back(           detailedSelector->getParameter<double>("maxAbsDy"));
  //   m_detailed_maxAbsPullY.push_back(        detailedSelector->getParameter<double>("maxAbsPullY"));
  //   m_detailed_maxChamberDist.push_back(     detailedSelector->getParameter<double>("maxChamberDist"));
  //   m_detailed_maxChamberDistPull.push_back( detailedSelector->getParameter<double>("maxChamberDistPull"));

  //   std::string arbitrationType = detailedSelector->getParameter<std::string>("arbitrationType");
  //   if       (arbitrationType == std::string("NoArbitration")            ) m_detailed_arbitrationType.push_back(reco::Electron::NoArbitration);
  //   else if (arbitrationType == std::string("SegmentArbitration")        ) m_detailed_arbitrationType.push_back(reco::Electron::SegmentArbitration);
  //   else if (arbitrationType == std::string("SegmentAndTrackArbitration")) m_detailed_arbitrationType.push_back(reco::Electron::SegmentAndTrackArbitration);
  //   else {
  //     throw cms::Exception("BadConfig") << "arbitrationType must be one of \"NoArbitration\", \"SegmentArbitration\", \"SegmentAndTrackArbitration\"" << std::endl;
  //   }
  // }
}


ElectronJetProducer::~ElectronJetProducer()
{
}


//
// member functions
//

bool ElectronJetProducer::electronOkay(const pat::Electron &electron) {
  /*
  if (electron.pt() < m_minPt  ||  electron.p() < m_minPmag  ||  fabs(electron.eta()) > m_maxAbsEta) return false;

  if (m_selectTrackerElectrons  &&  !electron.isTrackerElectron() ) return false;
  if (m_selectGlobalElectrons   &&  !electron.isGlobalElectron()  ) return false;

  if (m_minTrackerHits > 0) {
    if (electron.closestTrack().isNull()) return false;
    if (electron.closestTrack()->numberOfValidHits() < m_minTrackerHits) return false;
  }

  if (m_maxTrackerNormChi2 > 0.) {
    if (electron.closestTrack().isNull()) return false;
    if (electron.closestTrack()->normalizedChi2() > m_maxTrackerNormChi2) return false;
  }

  if (m_maxTrackerDxy > 0.) {
    if (electron.closestTrack().isNull()) return false;
    if (fabs(electron.closestTrack()->dxy()) > m_maxTrackerDxy) return false;
  }

  if (m_maxTrackerDz > 0.) {
    if (electron.closestTrack().isNull()) return false;
    if (fabs(electron.closestTrack()->dsz()) > m_maxTrackerDz) return false;
  }

  if (m_maxQoverpError > 0.) {
    if (electron.closestTrack().isNull()) return false;
    if (electron.closestTrack()->qoverpError() > m_maxQoverpError) return false;
  }

  if (m_maxPhiError > 0.) {
    if (electron.closestTrack().isNull()) return false;
    if (electron.closestTrack()->phiError() > m_maxPhiError) return false;
  }

  if (m_maxEtaError > 0.) {
    if (electron.closestTrack().isNull()) return false;
    if (electron.closestTrack()->etaError() > m_maxEtaError) return false;
  }

  if (m_maxDxyError > 0.) {
    if (electron.closestTrack().isNull()) return false;
    if (electron.closestTrack()->dxyError() > m_maxDxyError) return false;
  }

  if (m_maxDzError > 0.) {
    if (electron.closestTrack().isNull()) return false;
    if (electron.closestTrack()->dzError() > m_maxDzError) return false;
  }

  if (m_minOuterHits > 0) {
    if (electron.outerTrack().isNull()) return false;
    if (electron.outerTrack()->numberOfValidHits() < m_minOuterHits) return false;
  }

  if (m_maxOuterNormChi2 > 0.) {
    if (electron.outerTrack().isNull()) return false;
    if (electron.outerTrack()->normalizedChi2() > m_maxOuterNormChi2) return false;
  }

  if (m_maxGlobalNormChi2 > 0.) {
    if (electron.globalTrack().isNull()) return false;
    if (electron.globalTrack()->normalizedChi2() > m_maxGlobalNormChi2) return false;
  }

  if (m_maxStaRelChi2 > 0.) {
    if (!electron.isQualityValid()) return false;
    if (electron.combinedQuality().staRelChi2 > m_maxStaRelChi2) return false;
  }

  if (m_minSegmentMatches > 0) {
    if (electron.numberOfMatches(reco::Electron::SegmentAndTrackArbitration) < m_minSegmentMatches) return false;
  }

  for (std::vector<electron::SelectionType>::const_iterator electronSelector = m_electronSelectors.begin();  electronSelector != m_electronSelectors.end();  ++electronSelector) {
    if (!electron::isGoodElectron(electron, *electronSelector)) return false;
  }

  std::vector<electron::AlgorithmType>::const_iterator algorithmType = m_detailed_algorithmType.begin();
  std::vector<int>::const_iterator                        minNumberOfMatches = m_detailed_minNumberOfMatches.begin();
  std::vector<double>::const_iterator                     maxAbsDx           = m_detailed_maxAbsDx.begin();
  std::vector<double>::const_iterator                     maxAbsPullX        = m_detailed_maxAbsPullX.begin();
  std::vector<double>::const_iterator                     maxAbsDy           = m_detailed_maxAbsDy.begin();
  std::vector<double>::const_iterator                     maxAbsPullY        = m_detailed_maxAbsPullY.begin();
  std::vector<double>::const_iterator                     maxChamberDist     = m_detailed_maxChamberDist.begin();
  std::vector<double>::const_iterator                     maxChamberDistPull = m_detailed_maxChamberDistPull.begin();
  std::vector<reco::Electron::ArbitrationType>::const_iterator arbitrationType    = m_detailed_arbitrationType.begin();
  
  for (;  algorithmType != m_detailed_algorithmType.end();  ++algorithmType, ++minNumberOfMatches, ++maxAbsDx, ++maxAbsPullX, ++maxAbsDy, ++maxAbsPullY, ++maxChamberDist, ++maxChamberDistPull, ++arbitrationType) {
    if (!electron::isGoodElectron(electron, *algorithmType, *minNumberOfMatches, *maxAbsDx, *maxAbsPullX, *maxAbsDy, *maxAbsPullY, *maxChamberDist, *maxChamberDistPull, *arbitrationType)) return false;
  }
  */
  return true;
}

// ------------ method called to produce the data  ------------
void ElectronJetProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  edm::Handle<pat::ElectronCollection> electrons;
  iEvent.getByLabel(m_electrons, electrons);
  const pat::ElectronCollection *electrons_ptr = &*electrons;

  edm::Handle<reco::TrackCollection> tracks;
  edm::Handle<CaloTowerCollection> caloTowers;
  const reco::TrackCollection *tracks_ptr = NULL;
  const CaloTowerCollection *caloTowers_ptr = NULL;
  if (m_calculateIsolation) {
    iEvent.getByLabel(m_tracks, tracks);
    iEvent.getByLabel(m_caloTowers, caloTowers);
    tracks_ptr = &*tracks;
    caloTowers_ptr = &*caloTowers;
  }

  edm::ESHandle<TransientTrackBuilder> transientTrackBuilder;
  const TransientTrackBuilder *transientTrackBuilder_ptr = NULL;
  if (m_calculateVertex) {
    iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder", transientTrackBuilder);
    transientTrackBuilder_ptr = &*transientTrackBuilder;
  }

  // output #1: a collection of pairs of electrons
  std::unique_ptr<pat::MultiElectronCollection> Pairs(new pat::MultiElectronCollection);

  // set of jets and intermediate jets (pairs are all intermediate jets)
  // true means active (can be merged), false means inactive (already merged: data is in the merged jet)
  std::vector<pat::MultiElectron> jets;
  std::vector<bool> active;

  edm::Handle<reco::VertexCollection> primaryVertices;
  iEvent.getByLabel("offlinePrimaryVertices", primaryVertices);

  //  const reco::Vertex* vtx = &((*primaryVertices)[0]);

  std::map<const pat::Electron*,bool> used;
  for (pat::ElectronCollection::const_iterator one = electrons->begin();  one != electrons->end();  ++one) {
    if (electronOkay(*one)) {
      for (pat::ElectronCollection::const_iterator two = one;  two != electrons->end();  ++two) {
	if (one != two  &&  electronOkay(*two)) {
	  
          std::vector<const pat::Electron*> pairOfElectrons;
          pairOfElectrons.push_back(&*one);
          pairOfElectrons.push_back(&*two);
	  
          pat::MultiElectron electronPair( pairOfElectrons,
                                   transientTrackBuilder_ptr,
                                   tracks_ptr,
                                   electrons_ptr,
                                   caloTowers_ptr,
                                   m_centralTrackIsolationCone,
                                   m_unionTrackIsolationCone,
                                   m_centralTrackThresholdPt,
                                   m_unionTrackThresholdPt,
                                   m_centralCaloIsolationCone,
                                   m_unionCaloIsolationCone,
                                   m_centralNumberAboveThresholdCone,
                                   m_unionNumberAboveThresholdCone,
                                   m_centralNumberAboveThresholdPt,
                                   m_unionNumberAboveThresholdPt);

          bool satisfied_deltaR = (electronPair.dR(0, 1, electronPair.vertexValid()) < m_maxDeltaR);

          bool satisfied_mass = (electronPair.mass() < m_maxMass);

          bool satisfied_vertexProb = (electronPair.vertexValid()  &&  electronPair.vertexProb() > m_minVertexProb);

          bool satisfied = false;
          if       (m_groupingMode == kGroupByDeltaR                  ) satisfied = satisfied_deltaR;
          else if (m_groupingMode == kGroupByMass                     ) satisfied = satisfied_mass;
          else if (m_groupingMode == kGroupByVertexProb               ) satisfied = satisfied_vertexProb;
          else if (m_groupingMode == kGroupByDeltaRAndVertexProb      ) satisfied = satisfied_deltaR  &&  satisfied_vertexProb;
          else if (m_groupingMode == kGroupByMassAndVertexProb        ) satisfied = satisfied_mass    &&  satisfied_vertexProb;
          else if (m_groupingMode == kGroupByDeltaROrMass             ) satisfied = satisfied_deltaR  ||  satisfied_mass;
          else if (m_groupingMode == kGroupByDeltaROrMassAndVertexProb) satisfied = (satisfied_deltaR ||  satisfied_mass)        &&  satisfied_vertexProb;
          else if (m_groupingMode == kGroupByMassAndVertexProbOrDeltaR) satisfied = satisfied_mass    &&  (satisfied_vertexProb  ||  satisfied_deltaR);
          else     assert(false);

          if      (m_groupByCharge == kGroupByAnyCharge     ) satisfied = satisfied;
          else if (m_groupByCharge == kGroupByOppositeCharge) satisfied = satisfied  &&  (one->charge() != two->charge());
          else if (m_groupByCharge == kGroupBySameCharge    ) satisfied = satisfied  &&  (one->charge() == two->charge());

          // keep only the ones that have a small opening angle (calculated using vertexing)
          if (satisfied) {
            Pairs->push_back(electronPair);

            jets.push_back(electronPair);
            active.push_back(true);

            used[&*one] = true;
            used[&*two] = true;
          }
	}
      }
    }
  }

  // output #2: a collection of electrons not belonging to any surviving pair
  std::unique_ptr<pat::ElectronCollection> Orphans(new pat::ElectronCollection);
  for (pat::ElectronCollection::const_iterator electron = electrons->begin();  electron != electrons->end();  ++electron) {
    if (electronOkay(*electron)) {
      bool isUsed = false;
      for (std::map<const pat::Electron*,bool>::const_iterator iter = used.begin();  iter != used.end();  ++iter) {
        if (&*electron == iter->first) isUsed = true;
      }

      if (!isUsed) {
        pat::Electron newElectron(*electron);
        Orphans->push_back(newElectron);
      }
    }
  }

  // consolidate jets: group them into equivalence classes
  // if they overlap, merge them and only consider the merged version from that point onward
  // continue until there is nothing left to merge
  int newjets_size;
  do {
    std::vector<pat::MultiElectron> newjets;
    for (unsigned int i = 0;  i < jets.size();  i++) {
      for (unsigned int j = i+1;  j < jets.size();  j++) {

        if (active[i]  &&  active[j]) {
          if (jets[i].overlaps(jets[j])) {
            newjets.push_back( jets[i].merge(jets[j],
                               transientTrackBuilder_ptr,
                               tracks_ptr,
                               electrons_ptr,
                               caloTowers_ptr,
                               m_centralTrackIsolationCone,
                               m_unionTrackIsolationCone,
                               m_centralTrackThresholdPt,
                               m_unionTrackThresholdPt,
                               m_centralCaloIsolationCone,
                               m_unionCaloIsolationCone,
                               m_centralNumberAboveThresholdCone,
                               m_unionNumberAboveThresholdCone,
                               m_centralNumberAboveThresholdPt,
                               m_unionNumberAboveThresholdPt));
            active[i] = false;
            active[j] = false;
          }
        }
      }
    }

    // the new merged jets take the place of the old jets, so the new ones have active == true
    // and the old ones become active == false (above)
    for (std::vector<pat::MultiElectron>::const_iterator nj = newjets.begin();  nj != newjets.end();  ++nj) {
      jets.push_back(*nj);
      active.push_back(true);
    }

    newjets_size = newjets.size();
  } while (newjets_size > 0);

  // output #3: a collection of equivalence classes of shared daughters
  std::unique_ptr<pat::MultiElectronCollection> EquivalenceClasses(new pat::MultiElectronCollection);
  for (unsigned int i = 0;  i < jets.size();  i++) {
    if (active[i]) EquivalenceClasses->push_back(jets[i]);
  }

  iEvent.put(std::move(Pairs), "Pairs"); 
  iEvent.put(std::move(Orphans), "Orphans");
  iEvent.put(std::move(EquivalenceClasses)); 
}

// ------------ method called once each job just before starting event loop  ------------
void 
ElectronJetProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
ElectronJetProducer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(ElectronJetProducer);
