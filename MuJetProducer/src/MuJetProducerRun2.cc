// -*- C++ -*-
//
// Package:    MuJetProducerRun2
// Class:      MuJetProducerRun2
//
/**\class MuJetProducerRun2 MuJetProducerRun2.cc MuJetAnalysis/MuJetProducer/src/MuJetProducerRun2.cc

Description: <one line class summary>

Implementation:
<Notes on implementation>
*/
// Wei Shi <weishi@rice.edu>
//
// Created:  Wed Mar 6 14:12 CST 2019

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
#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexFitter.h"
#include "RecoVertex/VertexTools/interface/SequentialVertexFitter.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"

#include "TRandom3.h"
#include "TLorentzVector.h"

// class declaration
class MuJetProducerRun2 : public edm::EDProducer {
  public:
  explicit MuJetProducerRun2(const edm::ParameterSet&);
  ~MuJetProducerRun2();

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
  //edm::EDGetTokenT<reco::TrackCollection> m_DSAmuons;
  edm::EDGetTokenT<reco::BeamSpot> m_beamSpot;
  //edm::InputTag m_tracks;
  //edm::InputTag m_caloTowers;
  double m_minPt;
  double m_maxAbsEta;
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
MuJetProducerRun2::MuJetProducerRun2(const edm::ParameterSet& iConfig)
   : m_muons(                           consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("muons")))
   //, m_DSAmuons(                        consumes<reco::TrackCollection>(iConfig.getParameter<edm::InputTag>("DSAmuons")))//might consume?
   , m_beamSpot(                        consumes<reco::BeamSpot>(iConfig.getParameter<edm::InputTag>("beamSpot")))
   //, m_tracks(                          iConfig.getParameter<edm::InputTag>("tracks"))
   //, m_caloTowers(                      iConfig.getParameter<edm::InputTag>("caloTowers"))
   , m_minPt(                           iConfig.getParameter<double>("minPt"))
   , m_maxAbsEta(                       iConfig.getParameter<double>("maxAbsEta"))
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
    throw cms::Exception("BadConfig") << "groupingMode string not recognized (see MuJetProducerRun2.cc)" << std::endl;
  }

  if       (m_groupByCharge_string == "any"     ) m_groupByCharge = kGroupByAnyCharge;
  else if (m_groupByCharge_string == "opposite") m_groupByCharge = kGroupByOppositeCharge;
  else if (m_groupByCharge_string == "same"    ) m_groupByCharge = kGroupBySameCharge;
  else {
    throw cms::Exception("BadConfig") << "groupByCharge string not recognized (see MuJetProducerRun2.cc)" << std::endl;
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


MuJetProducerRun2::~MuJetProducerRun2()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

bool MuJetProducerRun2::muonOkay(const pat::Muon &muon) {
  //This should be consistent with PassMuonId in main analysis code: CutFlowAnalyzer_MiniAOD,
  //allow ONLY one of four muons can be a standalone muon, here it's pairing two muons, so can't enforce ONLY one of four be SA muon
  //Just relax it allow SA muon in the pairing
  if ( !muon.isStandAloneMuon() && ( !muon.isPFMuon() || ( (!muon.isTrackerMuon()) && (!muon.isGlobalMuon()) ) ) ) return false;

  //muon pt is the muonBestTrack pT, which usually is the tracker track pT if it's tracker muon,
  //otherwise it uses a tuneP algo pT or a PF algo pT which is usually close to globalTrack pT
  //Reference: https://twiki.cern.ch/twiki/bin/view/CMSPublic/MuonReferenceScaleResolRun2
  //In our case, if it's not a tracker mu, it means the tracker track/innerTrack can't find compatible hit in calo & muon sys.;
  //it's high chance the global mu is wrong (pT) and the inner track not right, should just use the outerTrack pT
  //Here: only use out-of-the-box pT if the muon is tracker muon & PF muon, otherwise use outerTrack pT
  //if ( muon.isTrackerMuon() && muon.isPFMuon() && ( muon.pt() < m_minPt || fabs(muon.eta()) > m_maxAbsEta ) ) return false;
  //else if ( muon.outerTrack().isAvailable() && ( muon.outerTrack()->pt() < m_minPt || fabs(muon.outerTrack()->eta()) > m_maxAbsEta ) ) return false;

  if (muon.pt() < m_minPt || fabs(muon.eta()) > m_maxAbsEta) return false;

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
void MuJetProducerRun2::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  edm::Handle<pat::MuonCollection> muons;
  iEvent.getByToken(m_muons, muons);
  //const pat::MuonCollection *muons_ptr = &*muons;

  //edm::Handle<reco::TrackCollection> DSAmuons;
  //iEvent.getByToken(m_DSAmuons, DSAmuons);

  edm::Handle<reco::BeamSpot> beamSpot;
  iEvent.getByToken(m_beamSpot, beamSpot);

  //edm::Handle<reco::TrackCollection> tracks;
  //edm::Handle<CaloTowerCollection> caloTowers;
  //const reco::TrackCollection *tracks_ptr = NULL;
  //const CaloTowerCollection *caloTowers_ptr = NULL;
  /*if (m_calculateIsolation) {
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
  std::vector<pat::MultiMuon> jets;

  //DEBUG@Wei SHI 2019.04.18
  //std::cout << "*******************************" << std::endl;
  //std::cout << "BeamSpot:    (x,y,z)[cm]: "<< beamSpot->position().x() << ", " << beamSpot->position().y() <<", "<< beamSpot->position().z() <<std::endl;
  double MuonCount=0;
  for (pat::MuonCollection::const_iterator mui = muons->begin();  mui != muons->end();  ++mui) {

    //std::cout << "Muon     #"<<MuonCount<<": (x,y,z)[cm]: "<< mui->vx() <<", "<< mui->vy() <<", "<< mui->vz() <<std::endl;
    //std::cout << "                 pT[GeV]: " << mui->pt() << "; eta: " << mui->eta() << "; phi: " << mui->phi() << "; q: " << mui->charge() << "; Tracker Mu: " << mui->isTrackerMuon() << "; Global Mu: " << mui->isGlobalMuon() << "; PF Mu:" << mui->isPFMuon() <<std::endl;
    if ( mui->innerTrack().isAvailable() ) {
    //std::cout << " innerTrk ValidPixelHits: " << mui->innerTrack()->hitPattern().numberOfValidPixelHits() << std::endl;
    }
    /*
    const pat::PackedCandidate* Candmui = dynamic_cast<const pat::PackedCandidate*>(mui->sourceCandidatePtr(0).get());
    if ( Candmui != 0 && Candmui->hasTrackDetails() ){
      const reco::HitPattern& pi = Candmui->pseudoTrack().hitPattern();
      //std::cout << "Cast Hit BPix layer #1: "<< pi.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 1) <<std::endl;
      //std::cout << "                    #2: "<< pi.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 2) <<std::endl;
      //std::cout << "                    #3: "<< pi.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 3) <<std::endl;
      //std::cout << "                    #4: "<< pi.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 4) <<std::endl;
      //std::cout << "         FPix layer #1: "<< pi.hasValidHitInPixelLayer(PixelSubdetector::PixelEndcap, 1) <<std::endl;
      //std::cout << "                    #2: "<< pi.hasValidHitInPixelLayer(PixelSubdetector::PixelEndcap, 2) <<std::endl;
      //std::cout << "                    #3: "<< pi.hasValidHitInPixelLayer(PixelSubdetector::PixelEndcap, 3) <<std::endl;
    }
    else{
      //std::cout <<"Didn't find a PFCandidates the muon was made from..."<<std::endl;
    }
    */
    //MC truth
    if(mui->genParticle() != 0){
      //std::cout << "Matched GEN: (x,y,z)[cm]: "<< mui->genParticle()->vx() << ", " <<mui->genParticle()->vy() <<", "<< mui->genParticle()->vz() <<std::endl;
      //std::cout << "                 pT[GeV]: "<< mui->genParticle()->pt() << "; eta: " << mui->genParticle()->eta() <<"; phi: "<< mui->genParticle()->phi() <<std::endl;
      //std::cout << "                  PDG ID: "<< mui->genParticle()->pdgId() << "; Status: " << mui->genParticle()->status() <<std::endl;
    }
    if (muonOkay(*mui)) {
      //std::cout <<"muonOkay"<<std::endl;
    }
    MuonCount++;
  }
/*
  for (reco::TrackCollection::const_iterator muj = DSAmuons->begin();  muj != DSAmuons->end();  ++muj) {

    std::cout << "DSA Mu     (x,y,z)[cm]: "<< muj->vx() - beamSpot->position().x() <<", "<< muj->vy() - beamSpot->position().y() <<", "<< muj->vz() - beamSpot->position().z() <<std::endl;
    std::cout << "               pT[GeV]: "<< muj->pt() <<"; eta: "<< muj->eta() <<"; phi: "<< muj->phi() << "; Q: " << muj->charge() <<std::endl;
    const reco::HitPattern& pj = muj->hitPattern();
    std::cout << "     Hit BPix layer #1: "<< pj.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 1) <<std::endl;
    std::cout << "                    #2: "<< pj.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 2) <<std::endl;
    std::cout << "                    #3: "<< pj.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 3) <<std::endl;
    std::cout << "                    #4: "<< pj.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 4) <<std::endl;
    std::cout << "         FPix layer #1: "<< pj.hasValidHitInPixelLayer(PixelSubdetector::PixelEndcap, 1) <<std::endl;
    std::cout << "                    #2: "<< pj.hasValidHitInPixelLayer(PixelSubdetector::PixelEndcap, 2) <<std::endl;
    std::cout << "                    #3: "<< pj.hasValidHitInPixelLayer(PixelSubdetector::PixelEndcap, 3) <<std::endl;

  }


  //Built Transient tracks from DSA muons and fit their vertex
  for (reco::TrackCollection::const_iterator ONE = DSAmuons->begin();  ONE != DSAmuons->end();  ++ONE) {
    for (reco::TrackCollection::const_iterator TWO = ONE;  TWO != DSAmuons->end();  ++TWO) {
      TLorentzVector P4ONE, P4TWO;
      P4ONE.SetPtEtaPhiM(ONE->pt(), ONE->eta(), ONE->phi(), 0.105);
      P4TWO.SetPtEtaPhiM(TWO->pt(), TWO->eta(), TWO->phi(), 0.105);
      if (ONE != TWO && ONE->pt() > 8 && TWO->pt() > 8 && fabs(ONE->eta()) < 2.4 && fabs(TWO->eta()) < 2.4
      && (ONE->charge() != TWO->charge()) && (P4ONE + P4TWO).M() < 60.0 ){

        std::cout << "    mu ONE   (x,y,z)[cm]: " << ONE->vx() - beamSpot->position().x() <<", "<< ONE->vy() - beamSpot->position().y() <<", "<< ONE->vz() - beamSpot->position().z() <<std::endl;
        std::cout << "                 pT[GeV]: " << ONE->pt() <<"; eta: "<< ONE->eta() <<"; phi: "<< ONE->phi() << "; Q: " << ONE->charge() <<std::endl;
        std::cout << "       TWO   (x,y,z)[cm]: " << TWO->vx() - beamSpot->position().x() <<", "<< TWO->vy() - beamSpot->position().y() <<", "<< TWO->vz() - beamSpot->position().z() <<std::endl;
        std::cout << "                 pT[GeV]: " << TWO->pt() <<"; eta: "<< TWO->eta() <<"; phi: "<< TWO->phi() << "; Q: " << TWO->charge() <<std::endl;
        std::cout << "          Pair mass[GeV]: " << (P4ONE + P4TWO).M() <<std::endl;

        std::vector<reco::TransientTrack> DimuTT;
        DimuTT.push_back( (*transientTrackBuilder).build(*ONE) );
        DimuTT.push_back( (*transientTrackBuilder).build(*TWO) );

        //Fitting Vtx
        KalmanVertexFitter KVF;
        CachingVertex<5> DimuVtx = KVF.vertex(DimuTT);
        if( DimuVtx.isValid() ){
          std::cout << "    * DSA dimu vtx valid! *" <<std::endl;
          //setVertex(Point(DimuVtx.position().x(), DimuVtx.position().y(), DimuVtx.position().z()));
          std::cout << "         vtx (x,y,z)[cm]: " << DimuVtx.position().x() << ", " << DimuVtx.position().y() << ", " << DimuVtx.position().z()<<std::endl;
        }
        else{
          std::cout << "    * DSA dimu vtx NOT valid! *" <<std::endl;
        }
        std::cout << "-----------" <<std::endl;

      }//end if
    }//end for TWO
  }//end for One
  */
  //end DEBUG @Wei SHI 2019.04.18

  //double PairCount = 0;
  for (pat::MuonCollection::const_iterator one = muons->begin();  one != muons->end();  ++one) {
    if (muonOkay(*one)) {
	    for (pat::MuonCollection::const_iterator two = one;  two != muons->end();  ++two) {
	      if (one != two  &&  muonOkay(*two)) {

          std::vector<const pat::Muon*> pairOfMuons;
          pairOfMuons.push_back(&*one);
          pairOfMuons.push_back(&*two);

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

          bool satisfied_mass = (muonPair.mass() < m_maxMass);//This is simply muon pair mass, not the fitted vtx mass

          bool satisfied_vertexProb = (muonPair.vertexValid() && muonPair.vertexProb() > m_minVertexProb);

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

          //Start DEBUG@WeiShi
          /*std::cout <<"----------"<<std::endl;
          std::cout << "Muon one (x,y,z)[cm]: " << one->vx() <<", "<< one->vy() <<", "<< one->vz() <<std::endl;
          std::cout << "             pT[GeV]: " << one->pt() << "; eta: " << one->eta() << "; phi: " << one->phi() << "; q: " << one->charge() << "; Tracker Mu: " << one->isTrackerMuon() << "; Global Mu: " << one->isGlobalMuon() << "; PF Mu:" << one->isPFMuon() << "; SA Mu: " << one->isStandAloneMuon() <<std::endl;
          if( one->innerTrack().isAvailable() )    std::cout << "  innerTrack pT[GeV]: " << one->innerTrack()->pt()    << "; eta: " << one->innerTrack()->eta()    << "; phi: " << one->innerTrack()->phi()    <<std::endl;
          if( one->outerTrack().isAvailable() )    std::cout << "  outerTrack pT[GeV]: " << one->outerTrack()->pt()    << "; eta: " << one->outerTrack()->eta()    << "; phi: " << one->outerTrack()->phi()    <<std::endl;
          if( one->globalTrack().isAvailable() )   std::cout << " globalTrack pT[GeV]: " << one->globalTrack()->pt()   << "; eta: " << one->globalTrack()->eta()   << "; phi: " << one->globalTrack()->phi()   <<std::endl;
          if( one->muonBestTrack().isAvailable() ) std::cout << "   bestTrack pT[GeV]: " << one->muonBestTrack()->pt() << "; eta: " << one->muonBestTrack()->eta() << "; phi: " << one->muonBestTrack()->phi() <<std::endl;

          std::cout << "Muon two (x,y,z)[cm]: " << two->vx() <<", "<< two->vy() <<", "<< two->vz() <<std::endl;
          std::cout << "             pT[GeV]: " << two->pt() << "; eta: " << two->eta() << "; phi: " << two->phi() << "; q: " << two->charge() << "; Tracker Mu: " << two->isTrackerMuon() << "; Global Mu: " << two->isGlobalMuon() << "; PF Mu:" << two->isPFMuon() << "; SA Mu: " << two->isStandAloneMuon() <<std::endl;
          if( two->innerTrack().isAvailable() )    std::cout << "  innerTrack pT[GeV]: " << two->innerTrack()->pt()    << "; eta: " << two->innerTrack()->eta()    << "; phi: " << two->innerTrack()->phi()    <<std::endl;
          if( two->outerTrack().isAvailable() )    std::cout << "  outerTrack pT[GeV]: " << two->outerTrack()->pt()    << "; eta: " << two->outerTrack()->eta()    << "; phi: " << two->outerTrack()->phi()    <<std::endl;
          if( two->globalTrack().isAvailable() )   std::cout << " globalTrack pT[GeV]: " << two->globalTrack()->pt()   << "; eta: " << two->globalTrack()->eta()   << "; phi: " << two->globalTrack()->phi()   <<std::endl;
          if( two->muonBestTrack().isAvailable() ) std::cout << "   bestTrack pT[GeV]: " << two->muonBestTrack()->pt() << "; eta: " << two->muonBestTrack()->eta() << "; phi: " << two->muonBestTrack()->phi() <<std::endl;

          std::cout << "muonPair fitted vtx valid: " << muonPair.vertexValid() <<", dR: "<< muonPair.dR(0, 1, muonPair.vertexValid()) <<std::endl;
          if( muonPair.vertexValid() ) std::cout << "muonPair fitted vtx mass: " << muonPair.vertexMass() << ", prob.: "<< muonPair.vertexProb() <<std::endl;*/
          //End DEBUG@WeiShi

          if (satisfied) {
            Pairs->push_back(muonPair);//All possible pairs
            jets.push_back(muonPair);//tmp jets/pairs, to be cleaned further
            //Start DEBUG@WeiShi
            //PairCount++;
            //std::cout << "Satisfied pair #" << PairCount <<std::endl;
            //End DEBUG@WeiShi
          }//end if satisfied

	      }//end if muon two okay
	    }//end loop over muon two
    }//end if muon one okay
  }//end for loop over muon one

  //Select two jets with min |dM| (jets are the same as Pairs, just a different name)
  pat::MultiMuon PairOne;
  pat::MultiMuon PairTwo;
  std::vector<pat::MultiMuon> FinalJets;//Final selected two pairs delivered to CutFlowAnalyzer_MiniAOD
  double deltaMassTmp = 13000.;

  //delta mass b/t each two pairs
  std::vector<float> AbsdMass;//value: AbsdMass.at(X)
  std::vector<int> Alice;//1st pair index in jets: Alice.at(X)
  std::vector<int> Bob;//2nd pair index in jets: Bob.at(X)

  if ( jets.size() > 1 ){
    //Store |dM| b/t each two pairs
    for (unsigned int Ajet = 0;  Ajet < jets.size();  Ajet++) {
      for (unsigned int Bjet = Ajet+1;  Bjet < jets.size();  Bjet++) {
        //Note: here need to use the fitted vertex mass, not the muon pair mass
        //Need to check/calculate vertex before referernce to vertexMass
        /*if( jets[Ajet].vertexValid() && jets[Bjet].vertexValid() ){
          deltaMassTmp = fabs( jets[Ajet].vertexMass() - jets[Bjet].vertexMass() );
          AbsdMass.push_back(deltaMassTmp);
          Alice.push_back(Ajet);
          Bob.push_back(Bjet);
        }*/
        deltaMassTmp = fabs( jets[Ajet].mass() - jets[Bjet].mass() );
        AbsdMass.push_back(deltaMassTmp);
        Alice.push_back(Ajet);
        Bob.push_back(Bjet);
      }//end loop over pair A
    }//end loop over pair B

    //std::cout << "AbsdMass size = "<< AbsdMass.size() << "; Alice size = " << Alice.size() << "; Bob size = " << Bob.size() << std::endl;
    //Find two distinct pairs with min |dM|, i.e., don't have overlapping muon
    //Sanity Check
    if( ( AbsdMass.size() == Alice.size() ) &&
        ( AbsdMass.size() == Bob.size()   )   ){

      //std::cout << "FinalJets size = "<< FinalJets.size() << std::endl;
      unsigned int FindCount = 0;//count how many times we find two pairs, terminate when it exceeds AbsdMass.size()-1 times
      while( FinalJets.size() != 2 && FindCount < AbsdMass.size() ){
        //find two pairs with min |dM|
        double MinDeltaMass = 13000.;
        unsigned int Index = -1;
        FindCount++;
        for (unsigned int X = 0; X < AbsdMass.size(); X++) {
          //std::cout << ">>>>>> AbsdMass.at("<<X<<") = "<< AbsdMass.at(X) << std::endl;
          if( AbsdMass.at(X) < MinDeltaMass){
            MinDeltaMass = AbsdMass.at(X);
            PairOne = jets[Alice.at(X)];
            PairTwo = jets[Bob.at(X)];
            Index = X;
          }//end if
        }//end find pairs with min |dM|

        //check if two pairs overlap
        if ( PairOne.overlaps(PairTwo) ) {
          //std::cout << ">>>>>> Two pairs overlap!" << std::endl;
          AbsdMass.at(Index) = 13001.;
          continue;
        }//overlap pairs
        else{
          FinalJets.push_back(PairOne);
          FinalJets.push_back(PairTwo);
          //Start DEBUG@WeiShi
          //std::cout << ">>> Two distinct pairs!" << std::endl;
          //if( PairOne.vertexValid() ) std::cout << ">>>> Pair one fitted vtx mass: " << PairOne.vertexMass() << std::endl;
          //if( PairTwo.vertexValid() ) std::cout << ">>>> Pair two fitted vtx mass: " << PairTwo.vertexMass() << std::endl;
          //End DEBUG@WeiShi
        }//distinct pairs

      }//end while

      //If still can't find two distinct pairs, do nothing: TBD
      //if( FinalJets.size() != 2 && FindCount == AbsdMass.size() ){}

    }
    else{
      std::cout << "WARNING! Alice and Bob don't have the same size." << std::endl;
    }//end sanity check
  }//end jets.size()>1

  if ( jets.size() == 1 ){
    //std::cout << "jets.size() == 1" << std::endl;
    FinalJets.push_back(jets[0]);
    PairOne = jets[0];
  }

  // output #2: a collection of muons not belonging to any surviving pair
  std::unique_ptr<pat::MuonCollection> Orphans(new pat::MuonCollection);
  for (pat::MuonCollection::const_iterator muon = muons->begin();  muon != muons->end();  ++muon) {
    if (muonOkay(*muon)) {
      bool isUsed = false;
      //std::cout << "muon okay "<< std::endl;
      //std::cout << "     (x,y,z)[cm]: " << muon->vx() <<", "<< muon->vy() <<", "<< muon->vz() <<std::endl;
      //std::cout << "         pT[GeV]: " << muon->pt() << "; eta: " << muon->eta() << "; phi: " << muon->phi() << "; q: " << muon->charge() << "; Tracker Mu: " << muon->isTrackerMuon() << "; Global Mu: " << muon->isGlobalMuon() << "; PF Mu:" << muon->isPFMuon() <<std::endl;

      if ( FinalJets.size() == 2 ){
        if ( muon->pt() == FinalJets.at(0).muon(0)->pt() ||
             muon->pt() == FinalJets.at(0).muon(1)->pt() ||
             muon->pt() == FinalJets.at(1).muon(0)->pt() ||
             muon->pt() == FinalJets.at(1).muon(1)->pt()
           ) {
             isUsed = true;
             //std::cout << ">>> Used "<< std::endl;
           }
      }
      else if ( FinalJets.size() == 1 ){
        if ( muon->pt() == FinalJets.at(0).muon(0)->pt() ||
             muon->pt() == FinalJets.at(0).muon(1)->pt()
           ) {
             isUsed = true;
             //std::cout << ">>> Used "<< std::endl;
           }
      }

      if (!isUsed) {
        pat::Muon newMuon(*muon);
        Orphans->push_back(newMuon);
      }

    }//end muon ok
  }//end output #2

  // output #3: a collection of equivalence classes
  std::unique_ptr<pat::MultiMuonCollection> EquivalenceClasses(new pat::MultiMuonCollection);
  for (unsigned int i = 0;  i < FinalJets.size();  i++) {
    EquivalenceClasses->push_back(FinalJets[i]);
  }

  iEvent.put(std::move(Pairs), "Pairs");//all muon pairs formed passing the group mode if(satisfied)
  iEvent.put(std::move(Orphans), "Orphans");//final orphans delivered to the analyzer
  iEvent.put(std::move(EquivalenceClasses));//final muon pairs/jets delivered to the analyzer
}

// ------------ method called once each job just before starting event loop  ------------
void
MuJetProducerRun2::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
MuJetProducerRun2::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(MuJetProducerRun2);
