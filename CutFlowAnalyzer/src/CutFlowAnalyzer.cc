// -*- C++ -*-
//
// Package:    CutFlowAnalyzer
// Class:      CutFlowAnalyzer
// 
/**\class CutFlowAnalyzer CutFlowAnalyzer.cc MuJetAnalysis/CutFlowAnalyzer/src/CutFlowAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Yuriy Pakhotin
//         Created:  Tue Feb 19 18:51:12 CST 2013
// $Id: CutFlowAnalyzer.cc,v 1.14 2013/08/04 22:28:44 pakhotin Exp $
//
//


// system include files
#include <memory>


// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

// user include files
#include "TTree.h"
#include "TRandom3.h"
#include "TMath.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/GeometrySurface/interface/Cylinder.h"
#include "DataFormats/GeometrySurface/interface/Plane.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/MuonReco/interface/MuonChamberMatch.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonSegmentMatch.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/TriggerEvent.h"
#include "DataFormats/TrackingRecHit/interface/TrackingRecHit.h"
#include "DataFormats/TrackReco/interface/HitPattern.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "Geometry/CommonDetUnit/interface/GlobalTrackingGeometry.h"
#include "Geometry/CommonTopologies/interface/PixelTopology.h"
#include "Geometry/Records/interface/GlobalTrackingGeometryRecord.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "Geometry/TrackerGeometryBuilder/interface/PixelGeomDetUnit.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "MagneticField/Engine/interface/MagneticField.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "TrackingTools/GeomPropagators/interface/Propagator.h"
#include "TrackingTools/Records/interface/TrackingComponentsRecord.h"
#include "TrackingTools/TrajectoryState/interface/FreeTrajectoryState.h"
#include "TrackingTools/TrajectoryState/interface/TrajectoryStateOnSurface.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "TrackPropagation/SteppingHelixPropagator/interface/SteppingHelixPropagator.h"

#include "MuJetAnalysis/DataFormats/interface/MultiMuon.h"
#include "MuJetAnalysis/DataFormats/interface/interface/eig3.h"
#include "MuJetAnalysis/DataFormats/src/eig3.cc"

//******************************************************************************
//              Auxiliary function: Order objects by pT                         
//******************************************************************************
bool PtOrder (const reco::GenParticle* p1, const reco::GenParticle* p2) { return (p1->pt() > p2->pt() ); }

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

//******************************************************************************
//                           Class declaration                                  
//******************************************************************************

class CutFlowAnalyzer : public edm::EDAnalyzer {
  public:
    explicit CutFlowAnalyzer(const edm::ParameterSet&);
    ~CutFlowAnalyzer();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

  private:
    virtual void beginJob() ;
    virtual void analyze(const edm::Event&, const edm::EventSetup&);
    virtual void endJob() ;

    virtual void beginRun(edm::Run const&, edm::EventSetup const&);
    virtual void endRun(edm::Run const&, edm::EventSetup const&);
    virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
    virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      
  // ---------- Member data ----------
  
  int m_debug;
  
  TTree * m_ttree; // Store some variables in this tree for later access
  
  Int_t m_run;   // run number   | these three numbers required to extract event
  Int_t m_lumi;  // lumi number  | from sample (data or MC) and examine it in   
  Int_t m_event; // event number | event display                                
  
  Float_t b_beamSpot_x;
  Float_t b_beamSpot_y;
  Float_t b_beamSpot_z;
  
  Int_t m_events; // total number of events
  
  Float_t m_Mu17_threshold;
  Float_t m_Mu8_threshold;
  
  // ---------- Generator Level ----------
  
  edm::InputTag m_genParticles; // Label to access generator particles
  
  // Events counters
  Int_t m_events4GenMu;   // number of events with 4 gen muons
  Int_t m_events1GenMu17; // n events with 1 gen muon:  pT > 17 GeV, |eta| < 0.9
  Int_t m_events2GenMu8;  // n events with 2 gen muons: pT > 8 GeV,  |eta| < 2.4
  Int_t m_events3GenMu8;  // n events with 3 gen muons: pT > 8 GeV,  |eta| < 2.4
  Int_t m_events4GenMu8;  // n events with 4 gen muons: pT > 8 GeV,  |eta| < 2.4
  
  // Gen branches in ROOT tree (they all start with b_)
  Float_t b_genH_m;
  Float_t b_genH_p;
  Float_t b_genH_pT;
  Float_t b_genH_eta;
  Float_t b_genH_phi;
  Float_t b_genH_vx;
  Float_t b_genH_vy;
  Float_t b_genH_vz;
  
  Float_t b_genA0_m;
  Float_t b_genA0_E;
  Float_t b_genA0_p;
  Float_t b_genA0_pT;
  Float_t b_genA0_px;
  Float_t b_genA0_py;
  Float_t b_genA0_pz;
  Float_t b_genA0_eta;
  Float_t b_genA0_phi;
  Float_t b_genA0_vx;
  Float_t b_genA0_vy;
  Float_t b_genA0_vz;
  
  Float_t b_genA1_m;
  Float_t b_genA1_E;
  Float_t b_genA1_p;
  Float_t b_genA1_pT;
  Float_t b_genA1_px;
  Float_t b_genA1_py;
  Float_t b_genA1_pz;
  Float_t b_genA1_eta;
  Float_t b_genA1_phi;
  Float_t b_genA1_vx;
  Float_t b_genA1_vy;
  Float_t b_genA1_vz;
  
  Float_t b_genA0Mu0_p;
  Float_t b_genA0Mu1_p;
  Float_t b_genA1Mu0_p;
  Float_t b_genA1Mu1_p;
  
  Float_t b_genA0Mu0_pT;
  Float_t b_genA0Mu1_pT;
  Float_t b_genA1Mu0_pT;
  Float_t b_genA1Mu1_pT;
  
  Float_t b_genA0Mu0_eta;
  Float_t b_genA0Mu1_eta;
  Float_t b_genA1Mu0_eta;
  Float_t b_genA1Mu1_eta;
  
  Float_t b_genA0Mu0_phi;
  Float_t b_genA0Mu1_phi;
  Float_t b_genA1Mu0_phi;
  Float_t b_genA1Mu1_phi;
  
  Float_t b_genA0Mu0_vx;
  Float_t b_genA0Mu1_vx;
  Float_t b_genA1Mu0_vx;
  Float_t b_genA1Mu1_vx;
  
  Float_t b_genA0Mu0_vy;
  Float_t b_genA0Mu1_vy;
  Float_t b_genA1Mu0_vy;
  Float_t b_genA1Mu1_vy;
  
  Float_t b_genA0Mu0_vz;
  Float_t b_genA0Mu1_vz;
  Float_t b_genA1Mu0_vz;
  Float_t b_genA1Mu1_vz;
  
  Float_t b_genA0_vLT;
  Float_t b_genA1_vLT;
  
  Float_t b_genA0_vL;
  Float_t b_genA1_vL;
  
  Float_t b_genA0Mu_dEta;
  Float_t b_genA1Mu_dEta;
  Float_t b_genA0Mu_dPhi;
  Float_t b_genA1Mu_dPhi;
  Float_t b_genA0Mu_dR;
  Float_t b_genA1Mu_dR;
  
  Float_t b_genMu0_pT;
  Float_t b_genMu1_pT;
  Float_t b_genMu2_pT;
  Float_t b_genMu3_pT;
  
  Float_t b_genMu0_eta;
  Float_t b_genMu1_eta;
  Float_t b_genMu2_eta;
  Float_t b_genMu3_eta;
  
  Float_t b_genMu0_phi;
  Float_t b_genMu1_phi;
  Float_t b_genMu2_phi;
  Float_t b_genMu3_phi;
  
  // ---------- RECO Level ----------
  
  // Labels to access
  edm::InputTag m_muons;  // reconstructed muons
  edm::InputTag m_muJets; // muon jets built from reconstructed muons
  
  // Events counters
  Int_t m_events1SelMu17; // n events with 1 selected reco muon: pT > 17 GeV, |eta| < 0.9
  Int_t m_events2SelMu8;  // n events with 2 selected reco muon: pT > 8 GeV,  |eta| < 2.4
  Int_t m_events3SelMu8;  // n events with 2 selected reco muon: pT > 8 GeV,  |eta| < 2.4
  Int_t m_events4SelMu8;  // n events with 2 selected reco muon: pT > 8 GeV,  |eta| < 2.4
  Int_t m_events2MuJets;  // n events with 2 muon jets
  Int_t m_events2DiMuons; // n events with 2 dimuons (dimuon = muon jet with 2 muons)
  Int_t m_eventsDz2DiMuonsOK;   // n events with dz between dimuons less than 0.1
  Int_t m_eventsDiMuonsHLTFired;// n events with dimuon HLT fired
  Int_t m_eventsMassDiMuonsOK;  // n events with both dimuons masses in diagonal
  Int_t m_eventsIsoDiMuonsOK;   // n events with both dimuons isolated
  Int_t m_eventsVertexOK;       // n events with one good vertex
  
  // Cuts thresholds from Python config file
  Double_t m_maxIsoDiMuons;
  
  // Auxiliary variables
  TRandom3 m_trandom3;
  
  // Reco branches in ROOT tree (they all start with b_)
  
  Float_t b_selMu0_pT;
  Float_t b_selMu1_pT;
  Float_t b_selMu2_pT;
  Float_t b_selMu3_pT;
  
  Float_t b_selMu0_eta;
  Float_t b_selMu1_eta;
  Float_t b_selMu2_eta;
  Float_t b_selMu3_eta;
  
  Float_t b_selMu0_phi;
  Float_t b_selMu1_phi;
  Float_t b_selMu2_phi;
  Float_t b_selMu3_phi;
  
  Float_t b_diMuonC_isoTk;
  Float_t b_diMuonF_isoTk;
  Float_t b_diMuonC_isoPF;
  Float_t b_diMuonF_isoPF;
  
  Float_t b_dZDiMuonC;
  Float_t b_dZDiMuonF;
  Float_t b_dZDiMuons;
  
  Float_t b_diMuonC_Lxy;
  Float_t b_diMuonF_Lxy;
  
  Float_t b_diMuonC_eta;
  Float_t b_diMuonF_eta;
  Float_t b_diMuonC_phi;
  Float_t b_diMuonF_phi;
  
  // Bool branches in ROOT tree
  
  Bool_t b_is1SelMu17;
  Bool_t b_is4SelMu8;
  Bool_t b_is2MuJets;
  Bool_t b_is2DiMuons;
  Bool_t b_isDzDiMuonsOK;
  Bool_t b_isDiMuonHLTFired;
  Bool_t b_isMassDiMuonsOK;
  Bool_t b_isIsoDiMuonsOK;
  Bool_t b_isVLT;
  Bool_t b_isOK_diMuonsLxy;

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
CutFlowAnalyzer::CutFlowAnalyzer(const edm::ParameterSet& iConfig)

{
  m_debug = iConfig.getParameter<int>("analyzerDebug");
  
  m_events = 0;    
  m_ttree  = NULL;    
  
  // ---------- Generator Level ----------
  m_genParticles = iConfig.getParameter<edm::InputTag>("genParticles");
  
  m_events4GenMu = 0;
  m_events1GenMu17 = 0;
  m_events2GenMu8 = 0;
  m_events3GenMu8 = 0;
  m_events4GenMu8 = 0;
  
  // ---------- RECO Level ----------
  m_muons = iConfig.getParameter<edm::InputTag>("muons");
  m_muJets = iConfig.getParameter<edm::InputTag>("muJets");
  
  m_maxIsoDiMuons = iConfig.getParameter<double>("maxIsoDiMuons");
  m_Mu17_threshold = 17.0;
  m_Mu8_threshold  = 8.0;
  
  m_events1SelMu17 = 0;
  m_events2SelMu8  = 0;
  m_events3SelMu8  = 0;
  m_events4SelMu8  = 0;
  m_events2MuJets  = 0;
  m_events2DiMuons = 0;
  m_eventsDz2DiMuonsOK    = 0;
  m_eventsDiMuonsHLTFired = 0;
  m_eventsMassDiMuonsOK   = 0;
  m_eventsIsoDiMuonsOK    = 0;
  m_eventsVertexOK        = 0;
}


CutFlowAnalyzer::~CutFlowAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

//
// member functions
//

// ------------ method called for each event  ------------
void
CutFlowAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  
  double eq = 0.000001;
  
  // get the run, lumi and event number
  m_run   = iEvent.id().run();
  m_lumi  = iEvent.id().luminosityBlock();
  m_event = iEvent.id().event();
  
  edm::Handle<reco::BeamSpot> beamSpot;
  iEvent.getByLabel("offlineBeamSpot",beamSpot);
  b_beamSpot_x = beamSpot->position().x();
  b_beamSpot_y = beamSpot->position().y();
  b_beamSpot_z = beamSpot->position().z();
  
//  std::cout << "Beam spot x: " << m_beamSpot_x << " y: " << m_beamSpot_y << " z: " << m_beamSpot_z << std::endl;
  
  // count events
  m_events++;
  if ( !(m_events%1000) ) std::cout << "Event " << m_events << std::endl;
  
  //****************************************************************************
  //                              GEN LEVEL                                     
  //****************************************************************************
  
  if ( m_debug > 10 ) std::cout << m_events << " Start GEN Level" << std::endl;
  
  edm::Handle<reco::GenParticleCollection> genParticles;
  iEvent.getByLabel(m_genParticles, genParticles);
  
  // Loop over all genParticles and save prompt muons from particles with codes 36 (a1) or 3000022 (gammaD) in vector genMuons
  std::vector<const reco::GenParticle*> genH;
  std::vector<const reco::GenParticle*> genA_unsorted;
  std::vector<const reco::GenParticle*> genA;
  std::vector<const reco::GenParticle*> genMuons;
  std::vector<const reco::Candidate*>   genMuonMothers;
  // Loop over all gen particles
  int counterGenParticle = 0;
  for(reco::GenParticleCollection::const_iterator iGenParticle = genParticles->begin();  iGenParticle != genParticles->end();  ++iGenParticle) {
    counterGenParticle++;
//    std::cout << counterGenParticle << " " << iGenParticle->status() << " " << iGenParticle->pdgId() << " " << iGenParticle->vx() << " " << iGenParticle->vy() << " " << iGenParticle->vz() << std::endl;
    // Check if gen particle is muon (pdgId = +/-13) and stable (status = 1)
    if ( fabs( iGenParticle->pdgId() ) == 13 && iGenParticle->status() == 1 ) {
      // Mother of the muon can be muon. Find the last muon in this chain: genMuonCand
      // Example: a1 -> mu+ (status = 3) mu- (status = 3)
      //          mu- (status = 3) -> mu- (status = 2) -> mu- (status = 1)
      const reco::Candidate *genMuonCand = &(*iGenParticle);
      bool isMuonMother = true;
      while(isMuonMother) {
        isMuonMother = false;
        for ( size_t iMother = 0; iMother < genMuonCand->numberOfMothers(); iMother++ ) {
          if ( fabs( genMuonCand->mother(iMother)->pdgId() ) == 13 ) {
            isMuonMother = true;
            genMuonCand = genMuonCand->mother(iMother);
          }
        }
      }
      // Loop over all real (non-muon) mothers of the muon (here we use genMuonCand)
      for ( size_t iMother = 0; iMother < genMuonCand->numberOfMothers(); iMother++ ) {
        // Check if mother is CP-odd Higgs (PdgId = 36) or gamma_Dark (PdgId = 3000022)
//        if ( genMuonCand->mother(iMother)->pdgId() == 36 || genMuonCand->mother(iMother)->pdgId() == 3000022 || genMuonCand->mother(iMother)->pdgId() == 443 ) {
        if ( genMuonCand->mother(iMother)->pdgId() == 36 || genMuonCand->mother(iMother)->pdgId() == 3000022 ) {
          // Store the muon (stable, first in chain) into vector
          genMuons.push_back(&(*iGenParticle));
          // Store mother of the muon into vector. We need this to group muons into dimuons later
          genMuonMothers.push_back(genMuonCand->mother(iMother));
        }
      }
    }
    // Check if gen particle is
    if (    ( iGenParticle->status() == 3 && iGenParticle->pdgId() == 25 ) // decaying (status = 3) SM Higgs (pdgId = 25)
         || ( iGenParticle->status() == 3 && iGenParticle->pdgId() == 35 ) // decaying (status = 3) CP-even Higgs (pdgId = 35)
    ) {
      genH.push_back(&(*iGenParticle)); // Store the Higgs into vector
    }
    // Check if gen particle is
    if (    ( iGenParticle->status() == 3 && iGenParticle->pdgId() == 36      ) // decaying (status = 3) CP-odd Higgs (pdgId = 36)
         || ( iGenParticle->status() == 3 && iGenParticle->pdgId() == 3000022 ) // decaying (status = 3) gamma_Dark (pdgId = 3000022)
//         || ( iGenParticle->status() == 2 && iGenParticle->pdgId() == 443   ) // decaying (status = 2) J/psi (pdgId = 443)
    ) {
      genA_unsorted.push_back(&(*iGenParticle));
    }
  }
  
  if ( genH.size() == 1 ) {
    b_genH_m   = genH[0]->mass();
    b_genH_p   = genH[0]->p();
    b_genH_pT  = genH[0]->pt();
    b_genH_eta = genH[0]->eta();
    b_genH_phi = genH[0]->phi();
    b_genH_vx  = genH[0]->vx() - b_beamSpot_x;
    b_genH_vy  = genH[0]->vy() - b_beamSpot_y;
    b_genH_vz  = genH[0]->vz() - b_beamSpot_z;
  } else {
//    std::cout << "WARNING! genH.size() != 1" << std::endl;
  }
  
  if ( genA_unsorted.size() >= 2 ) {
    // Sort genA by pT (leading pT first)
    std::sort (genA_unsorted.begin(), genA_unsorted.end(), PtOrder);
    // Remove duplicates from genA
//    Float_t A_pT = genA_unsorted[0]->pt();
//    for ( unsigned int i = 1; i < genA_unsorted.size(); i++ ) {
//      if ( fabs( genA_unsorted[i]->pt() - A_pT) > eq ) {
//        A_pT = genA_unsorted[i]->pt();
//        genA.push_back( genA_unsorted[i] );
//      }
//    }
  }
  
  genA = genA_unsorted;
  
  if ( genA.size() >= 2 ) {
    b_genA0_m   = genA[0]->mass();
    b_genA0_E   = genA[0]->energy();
    b_genA0_p   = genA[0]->p();
    b_genA0_pT  = genA[0]->pt();
    b_genA0_px  = genA[0]->px();
    b_genA0_py  = genA[0]->py();
    b_genA0_pz  = genA[0]->pz();
    b_genA0_eta = genA[0]->eta();
    b_genA0_phi = genA[0]->phi();
    b_genA0_vx  = genA[0]->vx() - b_beamSpot_x;
    b_genA0_vy  = genA[0]->vy() - b_beamSpot_y;
    b_genA0_vz  = genA[0]->vz() - b_beamSpot_z;
    
    b_genA1_m   = genA[1]->mass();
    b_genA1_E   = genA[1]->energy();
    b_genA1_p   = genA[1]->p();
    b_genA1_pT  = genA[1]->pt();
    b_genA1_px  = genA[1]->px();
    b_genA1_py  = genA[1]->py();
    b_genA1_pz  = genA[1]->pz();
    b_genA1_eta = genA[1]->eta();
    b_genA1_phi = genA[1]->phi();
    b_genA1_vx  = genA[1]->vx() - b_beamSpot_x;
    b_genA1_vy  = genA[1]->vy() - b_beamSpot_y;
    b_genA1_vz  = genA[1]->vz() - b_beamSpot_z;
  } else {
    std::cout << "WARNING! genA.size() < 2" << std::endl;
  }
  
  // Group muons with the same mother
  std::vector< std::vector<const reco::GenParticle*> > genMuonGroupsUnsorted;
  std::vector<const reco::Candidate*> genMuonGroupsUnsortedMothers;
  std::vector<const reco::GenParticle*> genMuonsTMP1       = genMuons;
  std::vector<const reco::Candidate*>   genMuonMothersTMP1 = genMuonMothers;
  unsigned int nMuonGroup = 0;
  while ( genMuonsTMP1.size() > 0 ) {
    std::vector<const reco::GenParticle*> genMuonsTMP2;
    std::vector<const reco::Candidate*>   genMuonMothersTMP2;
    std::vector<const reco::GenParticle*> genMuonsSameMother;
    std::vector<const reco::Candidate*>   genMuonMothersSame;
    for ( unsigned int j = 0; j < genMuonsTMP1.size(); j++ ) {
      // Check if mothers are the same particle
      if ( fabs( genMuonMothersTMP1[0]->pt() - genMuonMothersTMP1[j]->pt() ) < eq ) {
        genMuonsSameMother.push_back( genMuonsTMP1[j] );
      } else {
        genMuonsTMP2.push_back( genMuonsTMP1[j] );
        genMuonMothersTMP2.push_back( genMuonMothersTMP1[j] );
      }
    }
    genMuonGroupsUnsorted.push_back(genMuonsSameMother);
    genMuonGroupsUnsortedMothers.push_back(genMuonMothersTMP1[0]);
    genMuonsTMP1       = genMuonsTMP2;
    genMuonMothersTMP1 = genMuonMothersTMP2;
    nMuonGroup++;
  }
  
  // Sort muon groups to match order of genA vector
  std::vector< std::vector<const reco::GenParticle*> > genMuonGroups;
  std::vector<const reco::Candidate*> genMuonGroupsMothers;
  for (unsigned int iA = 0; iA < genA.size(); iA++ ) {
    bool isMuGroupMatchedToA = false;
    int  nMuGroup = -1;
    for ( unsigned int iMuGroup = 0; iMuGroup < genMuonGroupsUnsortedMothers.size(); iMuGroup++ ) {
      if ( fabs ( genA[iA]->pt() - genMuonGroupsUnsortedMothers[iMuGroup]->pt() ) < 0.000001 ) {
        isMuGroupMatchedToA = true;
        nMuGroup = iMuGroup;
        break;
      }
    }
    if ( isMuGroupMatchedToA && nMuGroup >= 0 ) {
      genMuonGroups.push_back( genMuonGroupsUnsorted[nMuGroup] );
      genMuonGroupsMothers.push_back( genMuonGroupsUnsortedMothers[nMuGroup] );
    } else {
      std::cout << "Error! Muon group has no matched boson A" << std::endl;
    }
  }
  
  bool b_isVLT = true;
  if ( genMuonGroups.size() == 2 && genMuonGroups[0].size() == 2 && genMuonGroups[1].size() == 2 ) {
    std::sort( genMuonGroups[0].begin(), genMuonGroups[0].end(), PtOrder );
    std::sort( genMuonGroups[1].begin(), genMuonGroups[1].end(), PtOrder );
    
    b_genA0Mu0_p = genMuonGroups[0][0]->p();
    b_genA0Mu1_p = genMuonGroups[0][1]->p();
    b_genA1Mu0_p = genMuonGroups[1][0]->p();
    b_genA1Mu1_p = genMuonGroups[1][1]->p();
    
    b_genA0Mu0_pT = genMuonGroups[0][0]->pt();
    b_genA0Mu1_pT = genMuonGroups[0][1]->pt();
    b_genA1Mu0_pT = genMuonGroups[1][0]->pt();
    b_genA1Mu1_pT = genMuonGroups[1][1]->pt();
    
    b_genA0Mu0_eta = genMuonGroups[0][0]->eta();
    b_genA0Mu1_eta = genMuonGroups[0][1]->eta();
    b_genA1Mu0_eta = genMuonGroups[1][0]->eta();
    b_genA1Mu1_eta = genMuonGroups[1][1]->eta();
    
    b_genA0Mu0_phi = genMuonGroups[0][0]->phi();
    b_genA0Mu1_phi = genMuonGroups[0][1]->phi();
    b_genA1Mu0_phi = genMuonGroups[1][0]->phi();
    b_genA1Mu1_phi = genMuonGroups[1][1]->phi();
    
    b_genA0Mu0_vx = genMuonGroups[0][0]->vx() - b_beamSpot_x;
    b_genA0Mu1_vx = genMuonGroups[0][1]->vx() - b_beamSpot_x;
    b_genA1Mu0_vx = genMuonGroups[1][0]->vx() - b_beamSpot_x;
    b_genA1Mu1_vx = genMuonGroups[1][1]->vx() - b_beamSpot_x;
    
    b_genA0Mu0_vy = genMuonGroups[0][0]->vy() - b_beamSpot_y;
    b_genA0Mu1_vy = genMuonGroups[0][1]->vy() - b_beamSpot_y;
    b_genA1Mu0_vy = genMuonGroups[1][0]->vy() - b_beamSpot_y;
    b_genA1Mu1_vy = genMuonGroups[1][1]->vy() - b_beamSpot_y;
    
    b_genA0Mu0_vz = genMuonGroups[0][0]->vz() - b_beamSpot_z;
    b_genA0Mu1_vz = genMuonGroups[0][1]->vz() - b_beamSpot_z;
    b_genA1Mu0_vz = genMuonGroups[1][0]->vz() - b_beamSpot_z;
    b_genA1Mu1_vz = genMuonGroups[1][1]->vz() - b_beamSpot_z;
    
    if (    fabs(b_genA0Mu0_vx - b_genA0Mu1_vx) < eq
         && fabs(b_genA1Mu0_vx - b_genA1Mu1_vx) < eq
         && fabs(b_genA0Mu0_vy - b_genA0Mu1_vy) < eq
         && fabs(b_genA1Mu0_vy - b_genA1Mu1_vy) < eq
         && fabs(b_genA0Mu0_vz - b_genA0Mu1_vz) < eq
         && fabs(b_genA1Mu0_vz - b_genA1Mu1_vz) < eq
          ) {
      Float_t genA0_vLx = b_genA0Mu0_vx - b_genA0_vx;
      Float_t genA1_vLx = b_genA1Mu0_vx - b_genA1_vx;
    
      Float_t genA0_vLy = b_genA0Mu0_vy - b_genA0_vy;
      Float_t genA1_vLy = b_genA1Mu0_vy - b_genA1_vy;
    
      Float_t genA0_vLz = b_genA0Mu0_vz - b_genA0_vz;
      Float_t genA1_vLz = b_genA1Mu0_vz - b_genA1_vz;
    
      b_genA0_vLT = sqrt( genA0_vLx * genA0_vLx + genA0_vLy * genA0_vLy );
      b_genA1_vLT = sqrt( genA1_vLx * genA1_vLx + genA1_vLy * genA1_vLy );
    
      if ( b_genA0_vLT < 4. && b_genA0_vLT < 4. ) b_isVLT = true;
    
      b_genA0_vL = sqrt( genA0_vLx * genA0_vLx + genA0_vLy * genA0_vLy + genA0_vLz * genA0_vLz );
      b_genA1_vL = sqrt( genA1_vLx * genA1_vLx + genA1_vLy * genA1_vLy + genA1_vLz * genA1_vLz );
    } else {
      std::cout << "WARNING! Muon vertexes are different" << std::endl;
    }
    
    b_genA0Mu_dEta = genMuonGroups[0][0]->eta() - genMuonGroups[0][1]->eta();
    b_genA1Mu_dEta = genMuonGroups[1][0]->eta() - genMuonGroups[1][1]->eta();
    b_genA0Mu_dPhi = My_dPhi( genMuonGroups[0][0]->phi(), genMuonGroups[0][1]->phi() );
    b_genA1Mu_dPhi = My_dPhi( genMuonGroups[1][0]->phi(), genMuonGroups[1][1]->phi() );
    b_genA0Mu_dR   = sqrt(b_genA0Mu_dEta*b_genA0Mu_dEta + b_genA0Mu_dPhi*b_genA0Mu_dPhi);
    b_genA1Mu_dR   = sqrt(b_genA1Mu_dEta*b_genA1Mu_dEta + b_genA1Mu_dPhi*b_genA1Mu_dPhi);
  }
  
  // Sort genMuons by pT (leading pT first)
  if ( genMuons.size() > 1 ) std::sort( genMuons.begin(), genMuons.end(), PtOrder );
  
  if ( genMuons.size() == 4 ) m_events4GenMu++;
  
  if ( genMuons.size() > 0 ) {
    b_genMu0_pT  = genMuons[0]->pt();
    b_genMu0_eta = genMuons[0]->eta();
    b_genMu0_phi = genMuons[0]->phi();
  } else {
    b_genMu0_pT  = -100.0;
    b_genMu0_eta = -100.0;
    b_genMu0_phi = -100.0;
  }
  if ( genMuons.size() > 1 ) {
    b_genMu1_pT  = genMuons[1]->pt();
    b_genMu1_eta = genMuons[1]->eta();
    b_genMu1_phi = genMuons[1]->phi();
  } else {
    b_genMu1_pT  = -100.0;
    b_genMu1_eta = -100.0;
    b_genMu1_phi = -100.0;
  }
  if ( genMuons.size() > 2 ) {
    b_genMu2_pT  = genMuons[2]->pt();
    b_genMu2_eta = genMuons[2]->eta();
    b_genMu2_phi = genMuons[2]->phi();
  } else {
    b_genMu2_pT  = -100.0;
    b_genMu2_eta = -100.0;
    b_genMu2_phi = -100.0;
  }
  if ( genMuons.size() > 3 ) {
    b_genMu3_pT  = genMuons[3]->pt();
    b_genMu3_eta = genMuons[3]->eta();
    b_genMu3_phi = genMuons[3]->phi();
  } else {
    b_genMu3_pT  = -100.0;
    b_genMu3_eta = -100.0;
    b_genMu3_phi = -100.0;
  }

  
  std::vector<const reco::GenParticle*> genMuons17;
  std::vector<const reco::GenParticle*> genMuons8;
  
  for ( unsigned int i = 0; i < genMuons.size(); i++ ) {
    if ( genMuons[i]->pt() > m_Mu17_threshold && fabs( genMuons[i]->eta() ) < 0.9 ) {
      genMuons17.push_back(genMuons[i]);
    }
    if ( genMuons[i]->pt() > m_Mu8_threshold && fabs( genMuons[i]->eta() ) < 2.4 ) {
      genMuons8.push_back(genMuons[i]);
    }
  }
  
//  std::cout << " b_isVLT: " << b_isVLT << std::endl;
  if ( genMuons17.size() >=1 && b_isVLT) {
    m_events1GenMu17++;
    if ( genMuons8.size() >=2 ) {
      m_events2GenMu8++;
    }
    if ( genMuons8.size() >=3 ) {
      m_events3GenMu8++;
    }
    if ( genMuons8.size() >=4 ) {
      m_events4GenMu8++;
    }
  }
  
  if ( m_debug > 10 ) std::cout << m_events << " Stop GEN Level" << std::endl;
  
  //****************************************************************************
  //                              RECO LEVEL                                     
  //****************************************************************************
  
  if ( m_debug > 10 ) std::cout << m_events << " Start RECO Level" << std::endl;
  
  if ( m_debug > 10 ) std::cout << m_events << " Access RECO muons" << std::endl;
  
  edm::Handle<pat::MuonCollection> muons;
  iEvent.getByLabel(m_muons, muons);
  
  std::vector<const reco::Muon*> selMuons;
  std::vector<const reco::Muon*> selMuons8;
  std::vector<const reco::Muon*> selMuons17;
  
  for (pat::MuonCollection::const_iterator iMuon = muons->begin();  iMuon != muons->end();  ++iMuon) {
    if ( isPFMuonLoose( &(*iMuon) ) ) {
//    if ( isTrackerMuonPrivateID( &(*iMuon) ) ) {
      selMuons.push_back( &(*iMuon) );
      if ( iMuon->pt() > m_Mu8_threshold ) {
        selMuons8.push_back( &(*iMuon) );
      }
      if ( iMuon->pt() > m_Mu17_threshold && fabs(iMuon->eta()) < 0.9 ) {
        selMuons17.push_back( &(*iMuon) );
      }
    }
  }
  
  if ( m_debug > 10 ) std::cout << m_events << " Apply pT and eta cuts to RECO muons" << std::endl;
  
  if ( selMuons.size() > 0 ) {
    b_selMu0_pT  = selMuons[0]->pt();
    b_selMu0_eta = selMuons[0]->eta();
    b_selMu0_phi = selMuons[0]->phi();
  } else {
    b_selMu0_pT  = -100.0;
    b_selMu0_eta = -100.0;
    b_selMu0_phi = -100.0;
  }
  if ( selMuons.size() > 1 ) {
    b_selMu1_pT  = selMuons[1]->pt();
    b_selMu1_eta = selMuons[1]->eta();
    b_selMu1_phi = selMuons[1]->phi();
  } else {
    b_selMu1_pT  = -100.0;
    b_selMu1_eta = -100.0;
    b_selMu1_phi = -100.0;
  }
  if ( selMuons.size() > 2 ) {
    b_selMu2_pT  = selMuons[2]->pt();
    b_selMu2_eta = selMuons[2]->eta();
    b_selMu2_phi = selMuons[2]->phi();
  } else {
    b_selMu2_pT  = -100.0;
    b_selMu2_eta = -100.0;
    b_selMu2_phi = -100.0;
  }
  if ( selMuons.size() > 3 ) {
    b_selMu3_pT  = selMuons[3]->pt();
    b_selMu3_eta = selMuons[3]->eta();
    b_selMu3_phi = selMuons[3]->phi();
  } else {
    b_selMu3_pT  = -100.0;
    b_selMu3_eta = -100.0;
    b_selMu3_phi = -100.0;
  }
  
  if ( m_debug > 10 ) std::cout << m_events << " Count selected RECO muons" << std::endl;
  
  b_is1SelMu17 = false;
  b_is4SelMu8  = false;
  if ( selMuons17.size() >=1 ) {
    m_events1SelMu17++;
    b_is1SelMu17 = true;
    if ( selMuons8.size() >=2 ) {
      m_events2SelMu8++;
    }
    if ( selMuons8.size() >=3 ) {
      m_events3SelMu8++;
    }
    if ( selMuons8.size() >=4 ) {
      m_events4SelMu8++;
      b_is4SelMu8 = true;
    }
  }
  
  if ( m_debug > 10 ) std::cout << m_events << " Build RECO muon jets" << std::endl;
  
  edm::Handle<pat::MultiMuonCollection> muJets;
  iEvent.getByLabel(m_muJets, muJets);
  const pat::MultiMuon *muJetC = NULL;
  const pat::MultiMuon *muJetF = NULL;
  int nMuJetsContainMu17 = 0;
  unsigned int nMuJets = muJets->size();
  b_is2MuJets = false;
  if ( nMuJets == 2) {
    for ( unsigned int j = 0; j < nMuJets; j++ ) {
      bool isMuJetContainMu17 = false;
      for ( unsigned int m = 0; m < (*muJets)[j].numberOfDaughters(); m++ ) {
        if ( (*muJets)[j].muon(m)->pt() > m_Mu17_threshold && fabs( (*muJets)[j].muon(m)->eta() ) < 0.9 ) {
          isMuJetContainMu17 = true;
          nMuJetsContainMu17++;
          break;
        }
      }
      if ( isMuJetContainMu17 ) {
        muJetC = &((*muJets)[j]);
      } else {
        muJetF = &((*muJets)[j]);
      }
    }
    if ( nMuJetsContainMu17 == 2 ) {
      if (m_trandom3.Integer(2) == 0) {
        muJetC = &((*muJets)[0]);
        muJetF = &((*muJets)[1]);
      } else {
        muJetC = &((*muJets)[1]);
        muJetF = &((*muJets)[0]);
      }
    }
    if ( nMuJetsContainMu17 > 0 ) b_is2MuJets = true;
  }
  
  if ( m_debug > 10 ) std::cout << m_events << " Check if 2 muon jets built" << std::endl;
  if ( b_is1SelMu17 && b_is4SelMu8 && b_is2MuJets && b_isVLT) m_events2MuJets++;
  
  b_is2DiMuons = false;
  const pat::MultiMuon *diMuonC = NULL;
  const pat::MultiMuon *diMuonF = NULL;
  if ( muJetC != NULL && muJetF != NULL ) {
    if ( muJetC->numberOfDaughters() == 2 && muJetF->numberOfDaughters() == 2 ) {
      diMuonC = muJetC;
      diMuonF = muJetF;
      b_is2DiMuons = true;
    }
  }
  
  if ( m_debug > 10 ) std::cout << m_events << " Check if 2 muon jets are dimuons" << std::endl;
  if ( b_is1SelMu17 && b_is4SelMu8 && b_is2MuJets && b_is2DiMuons && b_isVLT) m_events2DiMuons++;
  
  b_diMuonC_eta = -1000.0;
  b_diMuonF_eta = -1000.0;
  b_diMuonC_phi = -1000.0;
  b_diMuonF_phi = -1000.0;
//  b_diMuonC_pt  = -1000.0;
//  b_diMuonF_pt  = -1000.0;
  if ( diMuonC != NULL && diMuonF != NULL ) {
    b_diMuonC_eta = diMuonC->eta();
    b_diMuonF_eta = diMuonF->eta();
    b_diMuonC_phi = diMuonC->phi();
    b_diMuonF_phi = diMuonF->phi();
//    b_diMuonC_pt  = diMuonC->pt();
//    b_diMuonF_pt  = diMuonF->pt();
  }
  
  b_isDzDiMuonsOK = false;
  b_dZDiMuonC = -1000.0;
  b_dZDiMuonF = -1000.0;
  b_dZDiMuons = -1000.0;
  if ( diMuonC != NULL && diMuonF != NULL ) {
    b_dZDiMuonC = diMuonC->dz(beamSpot->position());
    b_dZDiMuonF = diMuonF->dz(beamSpot->position());
    b_dZDiMuons = b_dZDiMuonC - b_dZDiMuonF;
    if ( fabs( b_dZDiMuons ) < 0.1 ) b_isDzDiMuonsOK = true;
  }
  
  if ( m_debug > 10 ) std::cout << m_events << " Apply cut on dZ" << std::endl;
  if ( b_is1SelMu17 && b_is4SelMu8 && b_is2MuJets && b_is2DiMuons && b_isDzDiMuonsOK && b_isVLT ) m_eventsDz2DiMuonsOK++;
  
  //****************************************************************************
  // Begin: new vertex code
  //****************************************************************************
  
  const unsigned int seed = 0;

  TRandom3 *rnd = new TRandom3(seed);

  edm::Handle<reco::TrackCollection> tracks;
  iEvent.getByLabel("generalTracks", tracks);

  std::vector<reco::TransientTrack> tracksToVertex1;
  std::vector<reco::TransientTrack> tracksToVertex2;
  
  const pat::MultiMuon *muJet1 = NULL;
  const pat::MultiMuon *muJet2 = NULL;
  
  muJet1 = diMuonC;
  muJet2 = diMuonF;
  
  if ( muJet1 != NULL && muJet2 != NULL ) {     

   edm::ESHandle<TransientTrackBuilder> transientTrackBuilder;
   iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder", transientTrackBuilder);

   for (unsigned int i = 0;  i < muJet1->numberOfDaughters();  i++) {
     if ( muJet1->muon(i)->innerTrack().isAvailable() ) {
       tracksToVertex1.push_back( transientTrackBuilder->build( muJet1->muon(i)->innerTrack() ) );
     }
     else if (muJet1->muon(i)->outerTrack().isAvailable()) {
       tracksToVertex1.push_back( transientTrackBuilder->build( muJet1->muon(i)->outerTrack() ) );
     }
   }

   for (unsigned int i = 0;  i < muJet2->numberOfDaughters();  i++) {
     if (muJet2->muon(i)->innerTrack().isAvailable()) {
       tracksToVertex2.push_back(transientTrackBuilder->build(muJet2->muon(i)->innerTrack()));
     }
     else if (muJet2->muon(i)->outerTrack().isAvailable()) {
       tracksToVertex2.push_back(transientTrackBuilder->build(muJet2->muon(i)->outerTrack()));
     }
   }
  }

  double min_dz_n = 10000.;


  math::XYZTLorentzVector diMuonTmp;


  if ( muJet1 != NULL && muJet2 != NULL ) {     

    if (nMuJets == 2) {
      if ((muJet1->vertexValid()) && (muJet2->vertexValid())){

	double A1[3][3];
	double V1[3][3];
	double d1[3];
	d1[0]=0.;
	d1[1]=0.;
	d1[2]=0.;

	double A2[3][3];
	double V2[3][3];
	double d2[3];
	d2[0]=0.;
	d2[1]=0.;
	d2[2]=0.;

	for (unsigned int a = 0; a < 3; ++a){
	  for (unsigned int b = 0; b < 3; ++b){
	    A1[a][b] = muJet1->vertexCovariance(a,b);
	    A2[a][b] = muJet2->vertexCovariance(a,b);
	  }
	}

	// Perform the decomposition       
	eigen_decomposition(A1, V1, d1);
	eigen_decomposition(A2, V2, d2);


	double elipiseX1Size = sqrt(d1[0]);
	double elipiseX2Size = sqrt(d2[0]);
	double elipiseY1Size = sqrt(d1[1]);
	double elipiseY2Size = sqrt(d2[1]);
	double elipiseZ1Size = sqrt(d1[2]);
	double elipiseZ2Size = sqrt(d2[2]);

	Global3DPoint muonjet1v = muJet1->vertexPoint();
	Global3DPoint muonjet2v = muJet2->vertexPoint();

	int throws = 100000;

	math::XYZTLorentzVector final_mj1_vtx;
	math::XYZTLorentzVector final_mj2_vtx;


	for (int dice = 0; dice < throws; dice++) {

	  double rnd_X1 = rnd->Gaus(muonjet1v.x(), elipiseX1Size);
	  double rnd_Y1 = rnd->Gaus(muonjet1v.y(), elipiseY1Size);
	  double rnd_Z1 = rnd->Gaus(muonjet1v.z(), elipiseZ1Size);

	  double rnd_X2 = rnd->Gaus(muonjet2v.x(), elipiseX2Size);
	  double rnd_Y2 = rnd->Gaus(muonjet2v.y(), elipiseY2Size);
	  double rnd_Z2 = rnd->Gaus(muonjet2v.z(), elipiseZ2Size);


	  Global3DPoint newVtx1(rnd_X1, rnd_Y1, rnd_Z1);
	  Global3DPoint newVtx2(rnd_X2, rnd_Y2, rnd_Z2);

	  std::vector<math::XYZTLorentzVector> new_vertex1_P4;
	  std::vector<math::XYZTLorentzVector> new_vertex2_P4;

	  for (unsigned int i = 0;  i < tracksToVertex1.size();  i++) {
	    TrajectoryStateClosestToPoint TSCTP1 = tracksToVertex1[i].trajectoryStateClosestToPoint(newVtx1);
	    Global3DVector momentum1 = TSCTP1.momentum();      
	    new_vertex1_P4.push_back(math::XYZTLorentzVector(momentum1.x(), momentum1.y(), momentum1.z(), sqrt(momentum1.mag2() + pow(muJet1->muon(i)->mass(), 2))));
	  }
	  for (unsigned int i = 0;  i < tracksToVertex2.size();  i++) {
	    TrajectoryStateClosestToPoint TSCTP2 = tracksToVertex2[i].trajectoryStateClosestToPoint(newVtx2);
	    Global3DVector momentum2 = TSCTP2.momentum();
	    new_vertex2_P4.push_back(math::XYZTLorentzVector(momentum2.x(), momentum2.y(), momentum2.z(), sqrt(momentum2.mag2() + pow(muJet2->muon(i)->mass(), 2))));
	  }

	  math::XYZTLorentzVector new_mj1_vtx;
	  math::XYZTLorentzVector new_mj2_vtx;

	  for (unsigned int i = 0;  i < tracksToVertex1.size();  i++) {
	    new_mj1_vtx+= new_vertex1_P4[i];
	  }
	  for (unsigned int i = 0;  i < tracksToVertex2.size();  i++) {
	    new_mj2_vtx+= new_vertex2_P4[i];
	  }

	  double rez1 = rnd_Z1-beamSpot->position().z();
	  double rex1 = rnd_X1-beamSpot->position().x();
	  double rey1 = rnd_Y1-beamSpot->position().y();
	  double repx1 = new_mj1_vtx.x();
	  double repy1 = new_mj1_vtx.y();
	  double repz1 = new_mj1_vtx.z();
	  double rept1 = pow((new_mj1_vtx.x()*new_mj1_vtx.x())+(new_mj1_vtx.y()*new_mj1_vtx.y()),0.5);			

	  double re_dzmj1 = (rez1) - ((rex1)*repx1+(rey1)*repy1)/rept1 * repz1/rept1;

	  double rez2 = rnd_Z2-beamSpot->position().z();
	  double rex2 = rnd_X2-beamSpot->position().x();
	  double rey2 = rnd_Y2-beamSpot->position().y();
	  double repx2 = new_mj2_vtx.x();
	  double repy2 = new_mj2_vtx.y();
	  double repz2 = new_mj2_vtx.z();
	  double rept2 = pow((new_mj2_vtx.x()*new_mj2_vtx.x())+(new_mj2_vtx.y()*new_mj2_vtx.y()),0.5);
	    
	  double re_dzmj2 = (rez2) - ((rex2)*repx2+(rey2)*repy2)/rept2 * repz2/rept2;

	  if (fabs(re_dzmj1-re_dzmj2) < min_dz_n){

	    massmj1 = new_mj1_vtx.M();
	    massmj2 = new_mj2_vtx.M();
	    dzmj1 =  re_dzmj1;
	    dzmj2 =  re_dzmj2;
	    min_dz_n = fabs(re_dzmj1-re_dzmj2);	    

	    final_mj1_vtx = new_mj1_vtx;
	    final_mj2_vtx = new_mj2_vtx;


	    if (min_dz_n < 0.1){
	      for ( unsigned int i = 0; i <= 1; i++ ) { 

		double isoTmp = 0.0;
		double n_dz;
		if ( i == 0 ){
		  diMuonTmp = final_mj1_vtx;
		  n_dz = dzmj1;
		}
		if ( i == 1 ){
		  diMuonTmp = final_mj2_vtx;
		  n_dz = dzmj2;
		}
	      
		for (reco::TrackCollection::const_iterator track = tracks->begin(); track != tracks->end(); ++track) {
		  bool trackIsMuon = false;
		  if ( sameTrack( &*track, &*((*muJets)[i].muon(0)->innerTrack()) ) || sameTrack( &*track, &*((*muJets)[i].muon(1)->innerTrack()) ) ) trackIsMuon = true;
		  if (!trackIsMuon) {
		    double dPhi = My_dPhi( diMuonTmp.phi(), track->phi() );
		    double dEta = diMuonTmp.eta() - track->eta();
		    double dR = sqrt( dPhi*dPhi + dEta*dEta ); 

		    if ( dR < 0.4 && track->pt() > 0.5 ) {
		      double dz = fabs( track->dz(beamSpot->position()) - n_dz);
		      if ( dz < 0.1 ){
			isoTmp += track->pt();
		      }
		    }    
		  }
		}
		if ( i == 0 ) isomj1 = isoTmp;
		if ( i == 1 ) isomj2 = isoTmp;
	      }
	    }  
	  

	  }
	}

      }
      else std::cout << "muJet vertex not valid" << std::endl;
    }
  }
  
  //****************************************************************************
  // End: new vertex code
  //****************************************************************************
  
  
  edm::Handle<pat::TriggerEvent> triggerEvent;
  iEvent.getByLabel("patTriggerEvent", triggerEvent);
  
  b_isDiMuonHLTFired = false;
  if (    ( triggerEvent->path("HLT_Mu17_Mu8_v22") && triggerEvent->path("HLT_Mu17_Mu8_v22")->wasAccept() )
       || ( triggerEvent->path("HLT_Mu17_Mu8_v21") && triggerEvent->path("HLT_Mu17_Mu8_v21")->wasAccept() )
       || ( triggerEvent->path("HLT_Mu17_Mu8_v19") && triggerEvent->path("HLT_Mu17_Mu8_v19")->wasAccept() )
       || ( triggerEvent->path("HLT_Mu17_Mu8_v18") && triggerEvent->path("HLT_Mu17_Mu8_v18")->wasAccept() )
       || ( triggerEvent->path("HLT_Mu17_Mu8_v17") && triggerEvent->path("HLT_Mu17_Mu8_v17")->wasAccept() )
       || ( triggerEvent->path("HLT_Mu17_Mu8_v16") && triggerEvent->path("HLT_Mu17_Mu8_v16")->wasAccept() ) ) {
    b_isDiMuonHLTFired = true;
  }
  
  if ( m_debug > 10 ) std::cout << m_events << " Apply cut on HLT" << std::endl;
  if ( b_is1SelMu17 && b_is4SelMu8 && b_is2MuJets && b_is2DiMuons && b_isDzDiMuonsOK && b_isDiMuonHLTFired && b_isVLT ) m_eventsDiMuonsHLTFired++;
  
  b_isMassDiMuonsOK = false;
  if ( diMuonC != NULL && diMuonF != NULL ) {
    double massC = diMuonC->mass();
    double massF = diMuonF->mass();
    if ( fabs(massC-massF) < (0.13 + 0.065*(massC+massF)/2.0) ) b_isMassDiMuonsOK = true;
  }
  
  if ( m_debug > 10 ) std::cout << m_events << " Apply cut on dimuon mass" << std::endl;
  if ( b_is1SelMu17 && b_is4SelMu8 && b_is2MuJets && b_is2DiMuons && b_isDzDiMuonsOK && b_isDiMuonHLTFired && b_isMassDiMuonsOK && b_isVLT ) m_eventsMassDiMuonsOK++;
  
//  edm::Handle<reco::TrackCollection> tracks; // defined above
//  iEvent.getByLabel("generalTracks", tracks);
  
//  edm::Handle<reco::PFCandidateCollection> pfCandidates;
//  iEvent.getByLabel("particleFlow", pfCandidates);
  
  b_isIsoDiMuonsOK = false;
  b_diMuonC_isoTk = -1.;
  b_diMuonF_isoTk = -1.;
  b_diMuonC_isoPF = -1.;
  b_diMuonF_isoPF = -1.;
  if ( diMuonC != NULL && diMuonF != NULL ) {
    double diMuonC_isoTk = 0.0;
    double diMuonF_isoTk = 0.0;
    double diMuonC_isoPF = 0.0;
    double diMuonF_isoPF = 0.0;
    const pat::MultiMuon *diMuonTmp = NULL;
    for ( unsigned int i = 1; i <= 2; i++ ) { 
      double diMuonTmp_isoTk = 0.0;
      double diMuonTmp_isoPF = 0.0;
      if ( i == 1 ) diMuonTmp = diMuonC;
      if ( i == 2 ) diMuonTmp = diMuonF;
      for (reco::TrackCollection::const_iterator track = tracks->begin(); track != tracks->end(); ++track) {
        bool trackIsMuon = false;
        if ( diMuonTmp->sameTrack( &*track, &*(diMuonTmp->muon(0)->innerTrack()) ) || diMuonTmp->sameTrack( &*track, &*(diMuonTmp->muon(1)->innerTrack()) ) ) trackIsMuon = true;
        if ( trackIsMuon == false ) {
          double dPhi = My_dPhi( diMuonTmp->phi(), track->phi() );
          double dEta = diMuonTmp->eta() - track->eta();
          double dR   = sqrt( dPhi*dPhi + dEta*dEta ); 
          if ( dR < 0.4 && track->pt() > 0.5 ) {
            double dz = fabs( track->dz(beamSpot->position()) - diMuonTmp->dz(beamSpot->position()) );
            if ( dz < 0.1 ) diMuonTmp_isoTk += track->pt();
          }    
        }
      }
//      for (reco::PFCandidateCollection::const_iterator pfCand = pfCandidates->begin(); pfCand != pfCandidates->end(); ++pfCand) {
//        if ( pfCand->particleId() == reco::PFCandidate::h ) {
//          double dPhi = My_dPhi( diMuonTmp->phi(), pfCand->phi() );
//          double dEta = diMuonTmp->eta() - pfCand->eta();
//          double dR   = sqrt( dPhi*dPhi + dEta*dEta ); 
////          if ( dR < 0.4 && pfCand->pt() > 0.5 ) {
//          if ( dR < 0.4 ) {
//            double dz = fabs( pfCand->vertex().z() - beamSpot->position().z() - diMuonTmp->dz(beamSpot->position()) );
//            if ( dz < 0.1 ) diMuonTmp_isoPF += pfCand->pt();
//          }
//        }
//      }
      if ( i == 1 ) {
        diMuonC_isoTk = diMuonTmp_isoTk;
        diMuonC_isoPF = diMuonTmp_isoPF;
      }
      if ( i == 2 ) {
        diMuonF_isoTk = diMuonTmp_isoTk;
        diMuonF_isoPF = diMuonTmp_isoPF;
      }
    }
    b_diMuonC_isoTk = diMuonC_isoTk;
    b_diMuonF_isoTk = diMuonF_isoTk;
    b_diMuonC_isoPF = diMuonC_isoPF;
    b_diMuonF_isoPF = diMuonF_isoPF;
//    std::cout << "diMuonC_isoTk: " << diMuonC_isoTk << " diMuonC_isoPF: " << diMuonC_isoPF << " diMuonF_isoTk: " << diMuonF_isoTk << " diMuonF_isoPF: " <<  diMuonF_isoPF << std::endl;
    if ( diMuonC_isoTk < m_maxIsoDiMuons && diMuonF_isoTk < m_maxIsoDiMuons ) b_isIsoDiMuonsOK = true;
//    if ( diMuonC_isoPF < m_maxIsoDiMuons && diMuonF_isoPF < m_maxIsoDiMuons ) b_isIsoDiMuonsOK = true;
  }
  
  if ( m_debug > 10 ) std::cout << m_events << " Apply cut on dimuon isolation" << std::endl;
  if ( b_is1SelMu17 && b_is4SelMu8 && b_is2MuJets && b_is2DiMuons && b_isDzDiMuonsOK && b_isDiMuonHLTFired && b_isMassDiMuonsOK && b_isIsoDiMuonsOK && b_isVLT ) m_eventsIsoDiMuonsOK++;
  
  edm::Handle<reco::VertexCollection> primaryVertices;
  iEvent.getByLabel("offlinePrimaryVertices", primaryVertices);
  
  bool isVertexOK = false;
  for (reco::VertexCollection::const_iterator vertex = primaryVertices->begin();  vertex != primaryVertices->end();  ++vertex) {
    if (vertex->isValid() && !vertex->isFake() && vertex->tracksSize() >= 4 && fabs(vertex->z()) < 24.) isVertexOK = true;
  }
  
  if ( m_debug > 10 ) std::cout << m_events << " Apply cut on dimuon vertex" << std::endl;
  if ( b_is1SelMu17 && b_is4SelMu8 && b_is2MuJets && b_is2DiMuons && b_isDzDiMuonsOK && b_isDiMuonHLTFired && b_isMassDiMuonsOK && b_isIsoDiMuonsOK && isVertexOK && b_isVLT ) m_eventsVertexOK++;
  
  // Add dimuons' Lxy to ntuple
  if ( m_debug > 10 ) std::cout << m_events << " Build RECO dimuon Lxy" << std::endl;
  b_isOK_diMuonsLxy = false;
  b_diMuonC_Lxy = -1000.0;
  b_diMuonF_Lxy = -1000.0;
  
  if ( diMuonC != NULL && diMuonC->vertexValid() && diMuonF != NULL && diMuonF->vertexValid() ) {
    if ( m_debug > 10 ) std::cout << m_events << " Dimuons vertexes are valid" << std::endl;
    if ( m_debug > 10 ) std::cout << m_events << " Loop through vertexes and find closest" << std::endl;
    reco::VertexCollection::const_iterator diMuonC_closestPrimaryVertex;
    bool diMuonC_closestPrimaryVertex_isFound = false;
    reco::VertexCollection::const_iterator diMuonF_closestPrimaryVertex;
    bool diMuonF_closestPrimaryVertex_isFound = false;
    int n_vertex =  0;
    for (reco::VertexCollection::const_iterator vertex = primaryVertices->begin();  vertex != primaryVertices->end();  ++vertex) {
      
      if ( m_debug > 10 ) std::cout << m_events << " Vertex #" << n_vertex << " isValid " << vertex->isValid() << " isFake " << vertex->isFake() << " tracksSize " << vertex->tracksSize() << " z " << vertex->z() << std::endl;
      if (vertex->isValid()  &&  !vertex->isFake()  &&  vertex->tracksSize() >= 4  &&  fabs(vertex->z()) < 24.) {
//        std::cout << "diMuonC->vertexPoint().z(): " << diMuonC->vertexPoint().z() << std::endl;
        if ( m_debug > 10 ) std::cout << m_events << " Vertex is OK" << std::endl;
        if ( m_debug > 10 ) std::cout << m_events << " diMuonC->vertexPoint().z() " << diMuonC->vertexPoint().z() << std::endl;
        if ( diMuonC_closestPrimaryVertex_isFound == false ) {
          diMuonC_closestPrimaryVertex         = vertex;
          diMuonC_closestPrimaryVertex_isFound = true;
        }
        if ( fabs(vertex->z() - diMuonC->vertexPoint().z()) < fabs(diMuonC_closestPrimaryVertex->z() - diMuonC->vertexPoint().z()) ) {
          diMuonC_closestPrimaryVertex = vertex;
          if ( m_debug > 10 ) std::cout << m_events << " Better diMuonC_closestPrimaryVertex is found" << std::endl;
        }
        if ( m_debug > 10 ) std::cout << m_events << " diMuonC_closestPrimaryVertex->z() " << diMuonC_closestPrimaryVertex->z() << std::endl;
        
        if ( m_debug > 10 ) std::cout << m_events << " diMuonF->vertexPoint().z() " << diMuonF->vertexPoint().z() << std::endl;
        if ( diMuonF_closestPrimaryVertex_isFound == false ) {
          diMuonF_closestPrimaryVertex         = vertex;
          diMuonF_closestPrimaryVertex_isFound = true;
        }
        if ( fabs(vertex->z() - diMuonF->vertexPoint().z()) < fabs(diMuonF_closestPrimaryVertex->z() - diMuonF->vertexPoint().z()) ) {
          diMuonF_closestPrimaryVertex = vertex;
          if ( m_debug > 10 ) std::cout << m_events << " Better diMuonF_closestPrimaryVertex is found" << std::endl;
        }
        if ( m_debug > 10 ) std::cout << m_events << " diMuonF_closestPrimaryVertex->z() " << diMuonF_closestPrimaryVertex->z() << std::endl;
      } else {
        if ( m_debug > 10 ) std::cout << m_events << " Vertex is not OK" << std::endl;
      }
      
      n_vertex++;
    }

    if ( m_debug > 10 ) std::cout << m_events << " Calculate Lxy for diMuonC" << std::endl;
    if ( diMuonC_closestPrimaryVertex_isFound ) {
      b_diMuonC_Lxy = diMuonC->lxy(diMuonC_closestPrimaryVertex->x(), diMuonC_closestPrimaryVertex->y(), diMuonC_closestPrimaryVertex->z());
    } else {
      b_diMuonC_Lxy = diMuonC->lxy(0.0, 0.0, 0.0);
    }
    
    if ( m_debug > 10 ) std::cout << m_events << " Calculate Lxy for diMuonF" << std::endl;
    if ( diMuonF_closestPrimaryVertex_isFound ) {
      b_diMuonF_Lxy = diMuonF->lxy(diMuonF_closestPrimaryVertex->x(), diMuonF_closestPrimaryVertex->y(), diMuonF_closestPrimaryVertex->z());
    } else {
      b_diMuonF_Lxy = diMuonF->lxy(0.0, 0.0, 0.0);
    }
    if ( b_diMuonC_Lxy  < 4.0 && b_diMuonF_Lxy < 4.0 ) b_isOK_diMuonsLxy = true;
  }
  
  if ( m_debug > 10 ) std::cout << m_events << " Stop RECO Level" << std::endl;
  
  m_ttree->Fill();
  
}


// ------------ method called once each job just before starting event loop  ------------
void 
CutFlowAnalyzer::beginJob()
{
  std::cout << "BEGIN JOB" << std::endl;
  
  edm::Service<TFileService> tFileService;
  m_ttree = tFileService->make<TTree>("Events", "Events");
  // Beam spot
  m_ttree->Branch("beamSpot_x",    &b_beamSpot_x,    "beamSpot_x/F");
  m_ttree->Branch("beamSpot_y",    &b_beamSpot_y,    "beamSpot_y/F");
  m_ttree->Branch("beamSpot_z",    &b_beamSpot_z,    "beamSpot_z/F");
  // Bosons
  m_ttree->Branch("genH_m",    &b_genH_m,    "genH_m/F");
  m_ttree->Branch("genH_p",    &b_genH_p,    "genH_p/F");
  m_ttree->Branch("genH_pT",   &b_genH_pT,   "genH_pT/F");
  m_ttree->Branch("genH_eta",  &b_genH_eta,  "genH_eta/F");
  m_ttree->Branch("genH_phi",  &b_genH_phi,  "genH_phi/F");
  m_ttree->Branch("genH_vx",   &b_genH_vx,   "genH_vx/F");
  m_ttree->Branch("genH_vy",   &b_genH_vy,   "genH_vy/F");
  m_ttree->Branch("genH_vz",   &b_genH_vz,   "genH_vz/F");
  
  m_ttree->Branch("genA0_m",   &b_genA0_m,   "genA0_m/F");
  m_ttree->Branch("genA0_E",   &b_genA0_E,   "genA0_E/F");
  m_ttree->Branch("genA0_p",   &b_genA0_p,   "genA0_p/F");
  m_ttree->Branch("genA0_pT",  &b_genA0_pT,  "genA0_pT/F");
  m_ttree->Branch("genA0_px",  &b_genA0_px,  "genA0_px/F");
  m_ttree->Branch("genA0_py",  &b_genA0_py,  "genA0_py/F");
  m_ttree->Branch("genA0_pz",  &b_genA0_pz,  "genA0_pz/F");
  m_ttree->Branch("genA0_eta", &b_genA0_eta, "genA0_eta/F");
  m_ttree->Branch("genA0_phi", &b_genA0_phi, "genA0_phi/F");
  m_ttree->Branch("genA0_vx",  &b_genA0_vx,  "genA0_vx/F");
  m_ttree->Branch("genA0_vy",  &b_genA0_vy,  "genA0_vy/F");
  m_ttree->Branch("genA0_vz",  &b_genA0_vz,  "genA0_vz/F");
  
  m_ttree->Branch("genA1_m",   &b_genA1_m,   "genA1_m/F");
  m_ttree->Branch("genA1_E",   &b_genA1_E,   "genA1_E/F");
  m_ttree->Branch("genA1_p",   &b_genA1_p,   "genA1_p/F");
  m_ttree->Branch("genA1_pT",  &b_genA1_pT,  "genA1_pT/F");
  m_ttree->Branch("genA1_px",  &b_genA1_px,  "genA1_px/F");
  m_ttree->Branch("genA1_py",  &b_genA1_py,  "genA1_py/F");
  m_ttree->Branch("genA1_pz",  &b_genA1_pz,  "genA1_pz/F");
  m_ttree->Branch("genA1_eta", &b_genA1_eta, "genA1_eta/F");
  m_ttree->Branch("genA1_phi", &b_genA1_phi, "genA1_phi/F");
  m_ttree->Branch("genA1_vx",  &b_genA1_vx,  "genA1_vx/F");
  m_ttree->Branch("genA1_vy",  &b_genA1_vy,  "genA1_vy/F");
  m_ttree->Branch("genA1_vz",  &b_genA1_vz,  "genA1_vz/F");
  
  // Dimuons
  m_ttree->Branch("genA0Mu0_p", &b_genA0Mu0_p, "genA0Mu0_p/F");
  m_ttree->Branch("genA0Mu1_p", &b_genA0Mu1_p, "genA0Mu1_p/F");
  m_ttree->Branch("genA1Mu0_p", &b_genA1Mu0_p, "genA1Mu0_p/F");
  m_ttree->Branch("genA1Mu1_p", &b_genA1Mu1_p, "genA1Mu1_p/F");
  
  m_ttree->Branch("genA0Mu0_pT", &b_genA0Mu0_pT, "genA0Mu0_pT/F");
  m_ttree->Branch("genA0Mu1_pT", &b_genA0Mu1_pT, "genA0Mu1_pT/F");
  m_ttree->Branch("genA1Mu0_pT", &b_genA1Mu0_pT, "genA1Mu0_pT/F");
  m_ttree->Branch("genA1Mu1_pT", &b_genA1Mu1_pT, "genA1Mu1_pT/F");
  
  m_ttree->Branch("genA0Mu0_eta", &b_genA0Mu0_eta, "genA0Mu0_eta/F");
  m_ttree->Branch("genA0Mu1_eta", &b_genA0Mu1_eta, "genA0Mu1_eta/F");
  m_ttree->Branch("genA1Mu0_eta", &b_genA1Mu0_eta, "genA1Mu0_eta/F");
  m_ttree->Branch("genA1Mu1_eta", &b_genA1Mu1_eta, "genA1Mu1_eta/F");
  
  m_ttree->Branch("genA0Mu0_phi", &b_genA0Mu0_phi, "genA0Mu0_phi/F");
  m_ttree->Branch("genA0Mu1_phi", &b_genA0Mu1_phi, "genA0Mu1_phi/F");
  m_ttree->Branch("genA1Mu0_phi", &b_genA1Mu0_phi, "genA1Mu0_phi/F");
  m_ttree->Branch("genA1Mu1_phi", &b_genA1Mu1_phi, "genA1Mu1_phi/F");
  
  m_ttree->Branch("genA0Mu0_vx", &b_genA0Mu0_vx, "genA0Mu0_vx/F");
  m_ttree->Branch("genA0Mu1_vx", &b_genA0Mu1_vx, "genA0Mu1_vx/F");
  m_ttree->Branch("genA1Mu0_vx", &b_genA1Mu0_vx, "genA1Mu0_vx/F");
  m_ttree->Branch("genA1Mu1_vx", &b_genA1Mu1_vx, "genA1Mu1_vx/F");
  
  m_ttree->Branch("genA0Mu0_vy", &b_genA0Mu0_vy, "genA0Mu0_vy/F");
  m_ttree->Branch("genA0Mu1_vy", &b_genA0Mu1_vy, "genA0Mu1_vy/F");
  m_ttree->Branch("genA1Mu0_vy", &b_genA1Mu0_vy, "genA1Mu0_vy/F");
  m_ttree->Branch("genA1Mu1_vy", &b_genA1Mu1_vy, "genA1Mu1_vy/F");
  
  m_ttree->Branch("genA0Mu0_vz", &b_genA0Mu0_vz, "genA0Mu0_vz/F");
  m_ttree->Branch("genA0Mu1_vz", &b_genA0Mu1_vz, "genA0Mu1_vz/F");
  m_ttree->Branch("genA1Mu0_vz", &b_genA1Mu0_vz, "genA1Mu0_vz/F");
  m_ttree->Branch("genA1Mu1_vz", &b_genA1Mu1_vz, "genA1Mu1_vz/F");
  
  m_ttree->Branch("genA0_vLT", &b_genA0_vLT, "genA0_vLT/F");
  m_ttree->Branch("genA1_vLT", &b_genA1_vLT, "genA1_vLT/F");
  m_ttree->Branch("genA0_vL",  &b_genA0_vL,  "genA0_vL/F");
  m_ttree->Branch("genA1_vL",  &b_genA1_vL,  "genA1_vL/F");
  
  m_ttree->Branch("genA0Mu_dEta", &b_genA0Mu_dEta, "genA0Mu_dEta/F");
  m_ttree->Branch("genA1Mu_dEta", &b_genA1Mu_dEta, "genA1Mu_dEta/F");
  m_ttree->Branch("genA0Mu_dPhi", &b_genA0Mu_dPhi, "genA0Mu_dPhi/F");
  m_ttree->Branch("genA1Mu_dPhi", &b_genA1Mu_dPhi, "genA1Mu_dPhi/F");
  m_ttree->Branch("genA0Mu_dR",   &b_genA0Mu_dR,   "genA0Mu_dR/F");
  m_ttree->Branch("genA1Mu_dR",   &b_genA1Mu_dR,   "genA1Mu_dR/F");
  
  // Generator Muons
  m_ttree->Branch("genMu0_pT",  &b_genMu0_pT,  "genMu0_pT/F");
  m_ttree->Branch("genMu1_pT",  &b_genMu1_pT,  "genMu1_pT/F");
  m_ttree->Branch("genMu2_pT",  &b_genMu2_pT,  "genMu2_pT/F");
  m_ttree->Branch("genMu3_pT",  &b_genMu3_pT,  "genMu3_pT/F");
  m_ttree->Branch("genMu0_eta", &b_genMu0_eta, "genMu0_eta/F");
  m_ttree->Branch("genMu1_eta", &b_genMu1_eta, "genMu1_eta/F");
  m_ttree->Branch("genMu2_eta", &b_genMu2_eta, "genMu2_eta/F");
  m_ttree->Branch("genMu3_eta", &b_genMu3_eta, "genMu3_eta/F");
  m_ttree->Branch("genMu0_phi", &b_genMu0_phi, "genMu0_phi/F");
  m_ttree->Branch("genMu1_phi", &b_genMu1_phi, "genMu1_phi/F");
  m_ttree->Branch("genMu2_phi", &b_genMu2_phi, "genMu2_phi/F");
  m_ttree->Branch("genMu3_phi", &b_genMu3_phi, "genMu3_phi/F");
  
  // Reco Muons
  m_ttree->Branch("selMu0_pT",  &b_selMu0_pT,  "selMu0_pT/F");
  m_ttree->Branch("selMu1_pT",  &b_selMu1_pT,  "selMu1_pT/F");
  m_ttree->Branch("selMu2_pT",  &b_selMu2_pT,  "selMu2_pT/F");
  m_ttree->Branch("selMu3_pT",  &b_selMu3_pT,  "selMu3_pT/F");
  m_ttree->Branch("selMu0_eta", &b_selMu0_eta, "selMu0_eta/F");
  m_ttree->Branch("selMu1_eta", &b_selMu1_eta, "selMu1_eta/F");
  m_ttree->Branch("selMu2_eta", &b_selMu2_eta, "selMu2_eta/F");
  m_ttree->Branch("selMu3_eta", &b_selMu3_eta, "selMu3_eta/F");
  m_ttree->Branch("selMu0_phi", &b_selMu0_phi, "selMu0_phi/F");
  m_ttree->Branch("selMu1_phi", &b_selMu1_phi, "selMu1_phi/F");
  m_ttree->Branch("selMu2_phi", &b_selMu2_phi, "selMu2_phi/F");
  m_ttree->Branch("selMu3_phi", &b_selMu3_phi, "selMu3_phi/F");
  
  m_ttree->Branch("dZDiMuonC", &b_dZDiMuonC, "dZDiMuonC/F");
  m_ttree->Branch("dZDiMuonF", &b_dZDiMuonF, "dZDiMuonF/F");
  m_ttree->Branch("dZDiMuons", &b_dZDiMuons, "dZDiMuons/F");
  
  m_ttree->Branch("diMuonC_isoTk", &b_diMuonC_isoTk, "diMuonC_isoTk/F");
  m_ttree->Branch("diMuonF_isoTk", &b_diMuonF_isoTk, "diMuonF_isoTk/F");
  m_ttree->Branch("diMuonC_isoPF", &b_diMuonC_isoPF, "diMuonC_isoPF/F");
  m_ttree->Branch("diMuonF_isoPF", &b_diMuonF_isoPF, "diMuonF_isoPF/F");
  
  m_ttree->Branch("diMuonC_Lxy", &b_diMuonC_Lxy, "diMuonC_Lxy/F");
  m_ttree->Branch("diMuonF_Lxy", &b_diMuonF_Lxy, "diMuonF_Lxy/F");
  
  m_ttree->Branch("diMuonC_eta", &b_diMuonC_eta, "diMuonC_eta/F");
  m_ttree->Branch("diMuonF_eta", &b_diMuonF_eta, "diMuonF_eta/F");
  m_ttree->Branch("diMuonC_phi", &b_diMuonC_phi, "diMuonC_phi/F");
  m_ttree->Branch("diMuonF_phi", &b_diMuonF_phi, "diMuonF_phi/F");
  
  m_ttree->Branch("is1SelMu17",       &b_is1SelMu17,       "is1SelMu17/O");
  m_ttree->Branch("is4SelMu8",        &b_is4SelMu8,        "is4SelMu8/O");
  m_ttree->Branch("is2MuJets",        &b_is2MuJets,        "is2MuJets/O");
  m_ttree->Branch("is2DiMuons",       &b_is2DiMuons,       "is2DiMuons/O");
  m_ttree->Branch("isDzDiMuonsOK",    &b_isDzDiMuonsOK,    "isDzDiMuonsOK/O");
  m_ttree->Branch("isDiMuonHLTFired", &b_isDiMuonHLTFired, "isDiMuonHLTFired/O");
  m_ttree->Branch("isMassDiMuonsOK",  &b_isMassDiMuonsOK,  "isMassDiMuonsOK/O");
  m_ttree->Branch("isIsoDiMuonsOK",   &b_isIsoDiMuonsOK,   "isIsoDiMuonsOK/O");
  m_ttree->Branch("isVLT",            &b_isVLT,            "isVLT/O");
  
}

// ------------ method called once each job just after ending the event loop  ------------
void 
CutFlowAnalyzer::endJob() 
{
  std::cout << "END JOB" << std::endl;
  
  std:: cout << "Total number of events:          " << m_events << std::endl;
  std:: cout << "Total number of events with 4mu: " << m_events4GenMu << " fraction: " <<  m_events4GenMu/m_events << std::endl;
  
  std:: cout << "********** GEN **********" << std::endl;
    std:: cout << "Selection              " << "nEv"         << " \t RelEff"                                       << " \t Eff" << std::endl;
  std:: cout << "pT1>17 |eta1|<0.9:       " << m_events1GenMu17 << " \t" << (float)m_events1GenMu17/(float)m_events << " \t" << (float)m_events1GenMu17/(float)m_events << std::endl;
  std:: cout << "pT2>8  |eta2|<2.4:       " << m_events2GenMu8  << " \t" << (float)m_events2GenMu8/(float)m_events1GenMu17  << " \t" << (float)m_events2GenMu8/(float)m_events << std::endl;
  std:: cout << "pT3>8  |eta2|<2.4:       " << m_events3GenMu8  << " \t" << (float)m_events3GenMu8/(float)m_events2GenMu8   << " \t" << (float)m_events3GenMu8/(float)m_events << std::endl;
  std:: cout << "pT4>8  |eta2|<2.4:       " << m_events4GenMu8  << " \t" << (float)m_events4GenMu8/(float)m_events3GenMu8   << " \t" << (float)m_events4GenMu8/(float)m_events << std::endl;
  std:: cout << "Basic MC Acceptance:     " << (float)m_events4GenMu8/(float)m_events << std::endl;

  std:: cout << "********** RECO **********" << std::endl;
  std:: cout << "Selection                " << "nEv"                   << " \t RelEff"                                                         << " \t Eff" << std::endl;
  std:: cout << "m_events1SelMu17:        " << m_events1SelMu17        << " \t" << (float)m_events1SelMu17/(float)m_events                << " \t" << (float)m_events1SelMu17/(float)m_events        << std::endl;
  std:: cout << "m_events2SelMu8:         " << m_events2SelMu8         << " \t" << (float)m_events2SelMu8/(float)m_events1SelMu17              << " \t" << (float)m_events2SelMu8/(float)m_events         << std::endl;
  std:: cout << "m_events3SelMu8:         " << m_events3SelMu8         << " \t" << (float)m_events3SelMu8/(float)m_events2SelMu8               << " \t" << (float)m_events3SelMu8/(float)m_events         << std::endl;
  std:: cout << "m_events4SelMu8:         " << m_events4SelMu8         << " \t" << (float)m_events4SelMu8/(float)m_events3SelMu8               << " \t" << (float)m_events4SelMu8/(float)m_events         << std::endl;

  std:: cout << "Basic Acceptance:        " << (float)m_events4SelMu8/(float)m_events << std::endl;
  std:: cout << "Basic MC Accept. a_gen:  " << (float)m_events4GenMu8/(float)m_events << std::endl; 

  std:: cout << "m_events2MuJets:         " << m_events2MuJets         << " \t" << (float)m_events2MuJets/(float)m_events4SelMu8               << " \t" << (float)m_events2MuJets/(float)m_events         << std::endl;
  std:: cout << "m_events2DiMuons:        " << m_events2DiMuons        << " \t" << (float)m_events2DiMuons/(float)m_events2MuJets              << " \t" << (float)m_events2DiMuons/(float)m_events        << std::endl;
  std:: cout << "m_eventsDz2DiMuonsOK:     " << m_eventsDz2DiMuonsOK     << " \t" << (float)m_eventsDz2DiMuonsOK/(float)m_events2DiMuons          << " \t" << (float)m_eventsDz2DiMuonsOK/(float)m_events     << std::endl;
  std:: cout << "m_eventsDiMuonsHLTFired: " << m_eventsDiMuonsHLTFired << " \t" << (float)m_eventsDiMuonsHLTFired/(float)m_eventsDz2DiMuonsOK   << " \t" << (float)m_eventsDiMuonsHLTFired/(float)m_events << std::endl;
  std:: cout << "m_eventsMassDiMuonsOK:   " << m_eventsMassDiMuonsOK   << " \t" << (float)m_eventsMassDiMuonsOK/(float)m_eventsDiMuonsHLTFired << " \t" << (float)m_eventsMassDiMuonsOK/(float)m_events   << std::endl;
  std:: cout << "m_eventsIsoDiMuonsOK:    " << m_eventsIsoDiMuonsOK    << " \t" << (float)m_eventsIsoDiMuonsOK/(float)m_eventsMassDiMuonsOK    << " \t" << (float)m_eventsIsoDiMuonsOK/(float)m_events    << std::endl;
  std:: cout << "m_eventsVertexOK:        " << m_eventsVertexOK        << " \t" << (float)m_eventsVertexOK/(float)m_eventsIsoDiMuonsOK         << " \t" << (float)m_eventsVertexOK/(float)m_events        << std::endl;
  
  std:: cout << "Further selections:      " << (float)m_eventsVertexOK/(float)m_events4SelMu8 << std::endl;
  float e_full = (float)m_eventsVertexOK/(float)m_events;
  float de_full = sqrt( e_full*( 1.0 - e_full )/(float)m_events );
  std:: cout << "Full sel eff e_full:     " << e_full << " +- " << de_full << std::endl;
  std:: cout << "e_full/a_gen:            " << (float)m_eventsVertexOK/(float)m_events4GenMu8 << std::endl;
  
  std::cout << m_events << std::endl;
  std::cout << m_events1GenMu17 << std::endl;
  std::cout << m_events2GenMu8 << std::endl;
  std::cout << m_events3GenMu8 << std::endl;
  std::cout << m_events4GenMu8 << std::endl;
  std::cout << m_events1SelMu17 << std::endl;
  std::cout << m_events2SelMu8 << std::endl;
  std::cout << m_events3SelMu8 << std::endl;
  std::cout << m_events4SelMu8 << std::endl;
  std::cout << m_events2MuJets << std::endl;
  std::cout << m_events2DiMuons << std::endl;
  std::cout << m_eventsDz2DiMuonsOK << std::endl;
  std::cout << m_eventsDiMuonsHLTFired << std::endl;
  std::cout << m_eventsMassDiMuonsOK << std::endl;
  std::cout << m_eventsIsoDiMuonsOK << std::endl;
  std::cout << m_eventsVertexOK << std::endl;
  
  
}

// ------------ method called when starting to processes a run  ------------
void 
CutFlowAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
CutFlowAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
CutFlowAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
CutFlowAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
CutFlowAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(CutFlowAnalyzer);
