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
#include "MuJetAnalysis/AnalysisTools/interface/ConsistentVertexesCalculator.h"
#include "MuJetAnalysis/AnalysisTools/src/ConsistentVertexesCalculator.cc"

//******************************************************************************
//              Auxiliary function: Order objects by pT                         
//******************************************************************************
bool PtOrder (const reco::GenParticle* p1, const reco::GenParticle* p2) { return (p1->pt() > p2->pt() ); }

bool sameTrack(const reco::Track *one, const reco::Track *two) {
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
  
  //****************************************************************************
  //                          THRESHOLDS                                        
  //****************************************************************************
  
  Float_t m_threshold_Mu17_pT;
  Float_t m_threshold_Mu17_eta;
  Float_t m_threshold_Mu8_pT;
  Float_t m_threshold_Mu8_eta;
  
  Float_t m_threshold_GenA_Lxy;
  
  Float_t m_threshold_DiMuons_dz;
  
  Float_t m_threshold_DiMuons_Iso;
  Float_t m_threshold_DiMuons_Iso_dR;  
  Float_t m_threshold_DiMuons_Iso_dz;
  Float_t m_threshold_DiMuons_Iso_pT;
  
  //****************************************************************************
  //          EVENT LEVEL VARIABLES, COUNTERS, BRANCHES AND SELECTORS           
  //****************************************************************************
  
  Int_t   m_debug;  // Debug level
  TTree * m_ttree;  // Store variables in branches of this tree for later access
  Int_t   m_events; // Counter: number of analyzed events
  
  // Branches in ROOT tree (they all start with b_)
  Int_t b_run;   // run number   | these three numbers required to extract event
  Int_t b_lumi;  // lumi number  | from sample (data or MC) and examine it in   
  Int_t b_event; // event number | event display                                
  
  Float_t b_beamSpot_x;
  Float_t b_beamSpot_y;
  Float_t b_beamSpot_z;
  
  //****************************************************************************
  //                GEN LEVEL BRANCHES, COUNTERS AND SELECTORS                  
  //****************************************************************************
  
  bool m_fillGenLevel; // TRUE for simulation, FALSE for data
  
  // GEN Level Muon Branches: with this analyzer we search for events with 4 muons!
  Float_t b_genMu0_px;
  Float_t b_genMu1_px;
  Float_t b_genMu2_px;
  Float_t b_genMu3_px;
  
  Float_t b_genMu0_py;
  Float_t b_genMu1_py;
  Float_t b_genMu2_py;
  Float_t b_genMu3_py;
  
  Float_t b_genMu0_pz;
  Float_t b_genMu1_pz;
  Float_t b_genMu2_pz;
  Float_t b_genMu3_pz;
  
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
  
  // GEN Level Counters: number of events with ...
  Int_t m_events4GenMu;    // ... with 4 gen muons
  Int_t m_events1GenMu17;  // ... with 1 gen muon:  pT > 17 GeV, |eta| < 0.9
  Int_t m_events2GenMu8;   // ... with 2 gen muons: pT > 8 GeV,  |eta| < 2.4
  Int_t m_events3GenMu8;   // ... with 3 gen muons: pT > 8 GeV,  |eta| < 2.4
  Int_t m_events4GenMu8;   // ... with 4 gen muons: pT > 8 GeV,  |eta| < 2.4
  Int_t m_eventsGenALxyOK; // ... with both A bosons decay inside Lxy < 4 cm
  
  // GEN Level Selectors
  Bool_t b_is4GenMu;
  Bool_t b_is1GenMu17;
  Bool_t b_is2GenMu8;
  Bool_t b_is3GenMu8;
  Bool_t b_is4GenMu8;
  Bool_t b_isGenALxyOK;
  
  // Bosons
  Float_t b_genH_m;
  Float_t b_genH_px;
  Float_t b_genH_py;
  Float_t b_genH_pz;
  Float_t b_genH_eta;
  Float_t b_genH_phi;
  Float_t b_genH_vx;
  Float_t b_genH_vy;
  Float_t b_genH_vz;
  
  Float_t b_genA0_m;
  Float_t b_genA0_px;
  Float_t b_genA0_py;
  Float_t b_genA0_pz;
  Float_t b_genA0_eta;
  Float_t b_genA0_phi;
  Float_t b_genA0_vx;
  Float_t b_genA0_vy;
  Float_t b_genA0_vz;
  
  Float_t b_genA0_Lx;
  Float_t b_genA0_Ly;
  Float_t b_genA0_Lz;
  Float_t b_genA0_Lxy;
  Float_t b_genA0_L;
  
  Float_t b_genA1_m;
  Float_t b_genA1_px;
  Float_t b_genA1_py;
  Float_t b_genA1_pz;
  Float_t b_genA1_eta;
  Float_t b_genA1_phi;
  Float_t b_genA1_vx;
  Float_t b_genA1_vy;
  Float_t b_genA1_vz;
  
  Float_t b_genA1_Lx;
  Float_t b_genA1_Ly;
  Float_t b_genA1_Lz;
  Float_t b_genA1_Lxy;
  Float_t b_genA1_L;
  
  // Muons accossiated with A-bosons
  Float_t b_genA0Mu0_px;
  Float_t b_genA0Mu1_px;
  Float_t b_genA1Mu0_px;
  Float_t b_genA1Mu1_px;
  
  Float_t b_genA0Mu0_py;
  Float_t b_genA0Mu1_py;
  Float_t b_genA1Mu0_py;
  Float_t b_genA1Mu1_py;
  
  Float_t b_genA0Mu0_pz;
  Float_t b_genA0Mu1_pz;
  Float_t b_genA1Mu0_pz;
  Float_t b_genA1Mu1_pz;
  
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
  
  Float_t b_genA0Mu_dEta;
  Float_t b_genA1Mu_dEta;
  Float_t b_genA0Mu_dPhi;
  Float_t b_genA1Mu_dPhi;
  Float_t b_genA0Mu_dR;
  Float_t b_genA1Mu_dR;
  
  //****************************************************************************
  //          HLT LEVEL VARIABLES, BRANCHES, COUNTERS AND SELECTORS            
  //****************************************************************************

  std::vector<std::string> hltPaths_;  
  std::vector<std::string> b_hltPaths;

  //****************************************************************************
  //          RECO LEVEL VARIABLES, BRANCHES, COUNTERS AND SELECTORS            
  //****************************************************************************
  
  // Labels to access
  edm::InputTag m_muons;  // reconstructed muons
  edm::InputTag m_muJets; // muon jets built from reconstructed muons
  
  Int_t         m_nThrowsConsistentVertexesCalculator;
  
  unsigned int m_randomSeed;
  TRandom3       m_trandom3;
  
  // Selectors and counters of events with ...
  Bool_t b_is1SelMu17;
  Int_t  m_events1SelMu17; // ... with 1 selected reco muon: pT > 17 GeV, |eta| < 0.9
  
  Bool_t b_is2SelMu8;
  Int_t  m_events2SelMu8;  // ... with 2 selected reco muon: pT > 8 GeV,  |eta| < 2.4
  
  Bool_t b_is3SelMu8;
  Int_t  m_events3SelMu8;  // ... with 2 selected reco muon: pT > 8 GeV,  |eta| < 2.4
  
  Bool_t b_is4SelMu8;
  Int_t  m_events4SelMu8;  // ... with 2 selected reco muon: pT > 8 GeV,  |eta| < 2.4
  
  Bool_t b_is2MuJets;
  Int_t  m_events2MuJets;  // ... with 2 muon jets
  
  Bool_t b_is2DiMuons;
  Int_t  m_events2DiMuons; // ... with 2 dimuons (dimuon = muon jet with 2 muons)
  
  Bool_t b_is2DiMuonsFittedVtxOK;
  Bool_t b_is2DiMuonsConsistentVtxOK;
  
  Bool_t b_is2DiMuonsDzOK_FittedVtx;
  Int_t  m_events2DiMuonsDzOK_FittedVtx;   // ... with dz between dimuons less than 0.1
  
  Bool_t b_is2DiMuonsDzOK_ConsistentVtx;
  Int_t  m_events2DiMuonsDzOK_ConsistentVtx;   // ... with dz between dimuons less than 0.1
  
  Bool_t b_isDiMuonHLTFired;
  Int_t  m_eventsDiMuonHLTFired_FittedVtx;// ... with dimuon HLT fired
  Int_t  m_eventsDiMuonHLTFired_ConsistentVtx;// ... with dimuon HLT fired
  
  Bool_t b_is2DiMuonsMassOK_FittedVtx;
  Int_t  m_events2DiMuonsMassOK_FittedVtx;  // ... with both dimuons masses in diagonal
  
  Bool_t b_is2DiMuonsMassOK_ConsistentVtx;
  Int_t  m_events2DiMuonsMassOK_ConsistentVtx;  // ... with both dimuons masses in diagonal
  
  Bool_t b_is2DiMuonsIsoTkOK_FittedVtx;
  Int_t  m_events2DiMuonsIsoTkOK_FittedVtx;   // ... with both dimuons isolated
  
  Bool_t b_is2DiMuonsIsoTkOK_ConsistentVtx;
  Int_t  m_events2DiMuonsIsoTkOK_ConsistentVtx;   // ... with both dimuons isolated
  
  Bool_t b_isVertexOK;
  Int_t  m_eventsVertexOK_FittedVtx;       // ... with one good vertex
  Int_t  m_eventsVertexOK_ConsistentVtx;       // ... with one good vertex
  
  Bool_t b_is2DiMuonsLxyOK_FittedVtx;
  Int_t  m_events2DiMuonsLxyOK_FittedVtx;
  
  Bool_t b_is2DiMuonsLxyOK_ConsistentVtx;
  Int_t  m_events2DiMuonsLxyOK_ConsistentVtx;
  
  // Reco branches in ROOT tree (they all start with b_)
  Float_t b_selMu0_px;
  Float_t b_selMu1_px;
  Float_t b_selMu2_px;
  Float_t b_selMu3_px;
  
  Float_t b_selMu0_py;
  Float_t b_selMu1_py;
  Float_t b_selMu2_py;
  Float_t b_selMu3_py;
  
  Float_t b_selMu0_pz;
  Float_t b_selMu1_pz;
  Float_t b_selMu2_pz;
  Float_t b_selMu3_pz;
  
  Float_t b_selMu0_eta;
  Float_t b_selMu1_eta;
  Float_t b_selMu2_eta;
  Float_t b_selMu3_eta;
  
  Float_t b_selMu0_phi;
  Float_t b_selMu1_phi;
  Float_t b_selMu2_phi;
  Float_t b_selMu3_phi;
  
  Float_t b_diMuonC_FittedVtx_m;
  Float_t b_diMuonC_FittedVtx_px;
  Float_t b_diMuonC_FittedVtx_py;
  Float_t b_diMuonC_FittedVtx_pz;
  Float_t b_diMuonC_FittedVtx_eta;
  Float_t b_diMuonC_FittedVtx_phi;
  Float_t b_diMuonC_FittedVtx_vx;
  Float_t b_diMuonC_FittedVtx_vy;
  Float_t b_diMuonC_FittedVtx_vz;
  

  Int_t b_diMuonC_m1_FittedVtx_hitpix;
  Int_t b_diMuonC_m2_FittedVtx_hitpix;
  Int_t b_diMuonF_m1_FittedVtx_hitpix;
  Int_t b_diMuonF_m2_FittedVtx_hitpix;

  Float_t b_diMuonC_FittedVtx_Lxy;
  Float_t b_diMuonC_FittedVtx_L;
  Float_t b_diMuonC_FittedVtx_dz;
  
  Float_t b_diMuonF_FittedVtx_m;
  Float_t b_diMuonF_FittedVtx_px;
  Float_t b_diMuonF_FittedVtx_py;
  Float_t b_diMuonF_FittedVtx_pz;
  Float_t b_diMuonF_FittedVtx_eta;
  Float_t b_diMuonF_FittedVtx_phi;
  Float_t b_diMuonF_FittedVtx_vx;
  Float_t b_diMuonF_FittedVtx_vy;
  Float_t b_diMuonF_FittedVtx_vz;
  
  Float_t b_diMuonF_FittedVtx_Lxy;
  Float_t b_diMuonF_FittedVtx_L;
  Float_t b_diMuonF_FittedVtx_dz;
  
  Float_t b_diMuonC_ConsistentVtx_m;
  Float_t b_diMuonC_ConsistentVtx_px;
  Float_t b_diMuonC_ConsistentVtx_py;
  Float_t b_diMuonC_ConsistentVtx_pz;
  Float_t b_diMuonC_ConsistentVtx_eta;
  Float_t b_diMuonC_ConsistentVtx_phi;
  Float_t b_diMuonC_ConsistentVtx_vx;
  Float_t b_diMuonC_ConsistentVtx_vy;
  Float_t b_diMuonC_ConsistentVtx_vz;
  
  Float_t b_diMuonC_ConsistentVtx_Lxy;
  Float_t b_diMuonC_ConsistentVtx_L;
  Float_t b_diMuonC_ConsistentVtx_dz;
  
  Float_t b_diMuonF_ConsistentVtx_m;
  Float_t b_diMuonF_ConsistentVtx_px;
  Float_t b_diMuonF_ConsistentVtx_py;
  Float_t b_diMuonF_ConsistentVtx_pz;
  Float_t b_diMuonF_ConsistentVtx_eta;
  Float_t b_diMuonF_ConsistentVtx_phi;
  Float_t b_diMuonF_ConsistentVtx_vx;
  Float_t b_diMuonF_ConsistentVtx_vy;
  Float_t b_diMuonF_ConsistentVtx_vz;
  
  Float_t b_diMuonF_ConsistentVtx_Lxy;
  Float_t b_diMuonF_ConsistentVtx_L;
  Float_t b_diMuonF_ConsistentVtx_dz;
  
  Float_t b_diMuons_dz_FittedVtx;
  Float_t b_diMuons_dz_ConsistentVtx;
  
  Float_t b_diMuonC_IsoTk_FittedVtx;
  Float_t b_diMuonF_IsoTk_FittedVtx;
  Float_t b_diMuonC_IsoTk_ConsistentVtx;
  Float_t b_diMuonF_IsoTk_ConsistentVtx;
  
//  Float_t b_diMuonC_IsoPF_FittedVtx;
//  Float_t b_diMuonF_IsoPF_FittedVtx;
//  Float_t b_diMuonC_IsoPF_ConsistentVtx;
//  Float_t b_diMuonF_IsoPF_ConsistentVtx;

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
  //****************************************************************************
  //                          SET THRESHOLDS                                    
  //****************************************************************************
  
  m_threshold_Mu17_pT  = 17.0; // min pT in GeV
  m_threshold_Mu17_eta =  0.9; // max eta in Barrel
  m_threshold_Mu8_pT   =  8.0; // min pT in GeV
  m_threshold_Mu8_eta  =  2.4; // max eta in Endcaps
  
  m_threshold_GenA_Lxy = 4.0; //
  
  m_threshold_DiMuons_dz = 0.1; //
  
  m_threshold_DiMuons_Iso = iConfig.getParameter<double>("DiMuons_Iso_Max");
  
  m_threshold_DiMuons_Iso_dR = 0.4; // Isolation cone
  m_threshold_DiMuons_Iso_dz = 0.1; // Track displacement [cm]
  m_threshold_DiMuons_Iso_pT = 0.5; // Track pT [GeV]
  
  //****************************************************************************
  //               SET EVENT LEVEL VARIABLES AND COUNTERS                       
  //****************************************************************************
  
  m_debug = iConfig.getParameter<int>("analyzerDebug");
  m_ttree  = NULL;
  m_events = 0;    
  
  //****************************************************************************
  //                 SET GEN LEVEL VARIABLES AND COUNTERS                       
  //****************************************************************************
  
  m_fillGenLevel = iConfig.getParameter<bool>("fillGenLevel");

  m_events4GenMu   = 0;
  m_events1GenMu17 = 0;
  m_events2GenMu8  = 0;
  m_events3GenMu8  = 0;
  m_events4GenMu8  = 0;
  
  m_eventsGenALxyOK = 0;
  
  //****************************************************************************
  //                 SET HLT LEVEL VARIABLES AND COUNTERS                       
  //****************************************************************************

  hltPaths_ = iConfig.getParameter<std::vector<std::string> >("hltPaths");

  //****************************************************************************
  //                 SET RECO LEVEL VARIABLES AND COUNTERS                       
  //****************************************************************************
  
  m_muons = iConfig.getParameter<edm::InputTag>("muons");
  m_muJets = iConfig.getParameter<edm::InputTag>("muJets");
  m_nThrowsConsistentVertexesCalculator = iConfig.getParameter<int>("nThrowsConsistentVertexesCalculator");
  
  m_randomSeed = 1234;
  m_trandom3   = TRandom3(m_randomSeed); // Random generator 
  
  m_events1SelMu17                     = 0;
  m_events2SelMu8                      = 0;
  m_events3SelMu8                      = 0;
  m_events4SelMu8                      = 0;
  m_events2MuJets                      = 0;
  m_events2DiMuons                     = 0;
  m_events2DiMuonsDzOK_FittedVtx       = 0;
  m_events2DiMuonsDzOK_ConsistentVtx   = 0;
  m_eventsDiMuonHLTFired_FittedVtx     = 0;
  m_eventsDiMuonHLTFired_ConsistentVtx = 0;
  m_events2DiMuonsMassOK_FittedVtx     = 0;
  m_events2DiMuonsMassOK_ConsistentVtx = 0;
  m_events2DiMuonsIsoTkOK_FittedVtx    = 0;
  m_events2DiMuonsIsoTkOK_ConsistentVtx= 0;
  m_eventsVertexOK_FittedVtx           = 0;
  m_eventsVertexOK_ConsistentVtx       = 0;
  m_events2DiMuonsLxyOK_FittedVtx      = 0;
  m_events2DiMuonsLxyOK_ConsistentVtx  = 0;
  
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
  double eq = 0.000001; // small number used below to compare variables

  b_diMuonC_m1_FittedVtx_hitpix=-1000;
  b_diMuonC_m2_FittedVtx_hitpix=-1000;
  b_diMuonF_m1_FittedVtx_hitpix=-1000;
  b_diMuonF_m2_FittedVtx_hitpix=-1000;
  
  //****************************************************************************
  //                          EVENT LEVEL                                       
  //****************************************************************************
  
  // Count number of analyzed events
  m_events++;
  if ( !(m_events%1000) ) std::cout << "Event " << m_events << std::endl;

  // Event info
  b_run   = iEvent.id().run();
  b_lumi  = iEvent.id().luminosityBlock();
  b_event = iEvent.id().event();
  if ( m_debug > 10 ) {
    std::cout << " Event info: "
              << " run "   << b_run
              << " lumi "  << b_lumi
              << " event " << b_event
              << std::endl;
  }

  // Beam spot info
  edm::Handle<reco::BeamSpot> beamSpot;
  iEvent.getByLabel("offlineBeamSpot", beamSpot);
  b_beamSpot_x = beamSpot->position().x();
  b_beamSpot_y = beamSpot->position().y();
  b_beamSpot_z = beamSpot->position().z();
  if ( m_debug > 10 ) {
    std::cout << " Beam spot "
              << " x " << b_beamSpot_x
              << " y " << b_beamSpot_y
              << " z " << b_beamSpot_z
              << std::endl;
  }
  
  GlobalPoint beamSpotPosition(beamSpot->position().x(), beamSpot->position().y(), beamSpot->position().z());
  
  //****************************************************************************
  //                          GEN LEVEL ANALYSIS START                          
  //****************************************************************************

  if (m_fillGenLevel){  

    if ( m_debug > 10 ) std::cout << m_events << " Start GEN Level" << std::endl;

    edm::Handle<reco::GenParticleCollection> genParticles;
    iEvent.getByLabel("genParticles", genParticles);
  
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
      if (    ( iGenParticle->status() == 22 && iGenParticle->pdgId() == 25 ) // decaying (status = 3) SM Higgs (pdgId = 25)
	      || ( iGenParticle->status() == 22 && iGenParticle->pdgId() == 35 ) // decaying (status = 3) CP-even Higgs (pdgId = 35)
	      ) {
	genH.push_back(&(*iGenParticle)); // Store the Higgs into vector
      }
      // Check if gen particle is
      if (    ( iGenParticle->status() == 22 && iGenParticle->pdgId() == 36      ) // decaying (status = 3) CP-odd Higgs (pdgId = 36)
	      || ( iGenParticle->status() == 22 && iGenParticle->pdgId() == 3000022 ) // decaying (status = 3) gamma_Dark (pdgId = 3000022)
	      //         || ( iGenParticle->status() == 2 && iGenParticle->pdgId() == 443   ) // decaying (status = 2) J/psi (pdgId = 443)
	      ) {
	      genA_unsorted.push_back(&(*iGenParticle));
      }
    }
  
    if ( genH.size() == 1 ) {
       b_genH_m   = genH[0]->mass();
      b_genH_px  = genH[0]->px();
      b_genH_py  = genH[0]->py();
      b_genH_pz  = genH[0]->pz();
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
      b_genA0_px  = genA[0]->px();
      b_genA0_py  = genA[0]->py();
      b_genA0_pz  = genA[0]->pz();
      b_genA0_eta = genA[0]->eta();
      b_genA0_phi = genA[0]->phi();
      b_genA0_vx  = genA[0]->vx() - b_beamSpot_x;
      b_genA0_vy  = genA[0]->vy() - b_beamSpot_y;
      b_genA0_vz  = genA[0]->vz() - b_beamSpot_z;
    
      b_genA1_m   = genA[1]->mass();
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
	      if ( fabs ( genA[iA]->pt() - genMuonGroupsUnsortedMothers[iMuGroup]->pt() ) < eq ) {
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
  
    b_isGenALxyOK = false;
    if ( genMuonGroups.size() == 2 && genMuonGroups[0].size() == 2 && genMuonGroups[1].size() == 2 ) {
      std::sort( genMuonGroups[0].begin(), genMuonGroups[0].end(), PtOrder );
      std::sort( genMuonGroups[1].begin(), genMuonGroups[1].end(), PtOrder );
    
      b_genA0Mu0_px = genMuonGroups[0][0]->px();
      b_genA0Mu1_px = genMuonGroups[0][1]->px();
      b_genA1Mu0_px = genMuonGroups[1][0]->px();
      b_genA1Mu1_px = genMuonGroups[1][1]->px();
      
      b_genA0Mu0_py = genMuonGroups[0][0]->py();
      b_genA0Mu1_py = genMuonGroups[0][1]->py();
      b_genA1Mu0_py = genMuonGroups[1][0]->py();
      b_genA1Mu1_py = genMuonGroups[1][1]->py();
      
      b_genA0Mu0_pz = genMuonGroups[0][0]->pz();
      b_genA0Mu1_pz = genMuonGroups[0][1]->pz();
      b_genA1Mu0_pz = genMuonGroups[1][0]->pz();
      b_genA1Mu1_pz = genMuonGroups[1][1]->pz();
    
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
	        b_genA0_Lx = b_genA0Mu0_vx - b_genA0_vx;
	        b_genA1_Lx = b_genA1Mu0_vx - b_genA1_vx;
            
	        b_genA0_Ly = b_genA0Mu0_vy - b_genA0_vy;
	        b_genA1_Ly = b_genA1Mu0_vy - b_genA1_vy;
            
	        b_genA0_Lz = b_genA0Mu0_vz - b_genA0_vz;
	        b_genA1_Lz = b_genA1Mu0_vz - b_genA1_vz;
            
	        b_genA0_Lxy = sqrt( b_genA0_Lx * b_genA0_Lx + b_genA0_Ly * b_genA0_Ly );
	        b_genA1_Lxy = sqrt( b_genA1_Lx * b_genA1_Lx + b_genA1_Ly * b_genA1_Ly );

	        b_genA0_L = sqrt( b_genA0_Lx * b_genA0_Lx + b_genA0_Ly * b_genA0_Ly + b_genA0_Lz * b_genA0_Lz );
	        b_genA1_L = sqrt( b_genA1_Lx * b_genA1_Lx + b_genA1_Ly * b_genA1_Ly + b_genA1_Lz * b_genA1_Lz );
	        
	        if ( b_genA0_Lxy < m_threshold_GenA_Lxy && b_genA1_Lxy < m_threshold_GenA_Lxy ) b_isGenALxyOK = true;
      } else {
	      std::cout << "WARNING! Muon vertexes are different. No Lxy's are calculated." << std::endl;
	      b_genA0_Lx  = -1000.0;
	      b_genA1_Lx  = -1000.0;
	      b_genA0_Ly  = -1000.0;
	      b_genA1_Ly  = -1000.0;
	      b_genA0_Lz  = -1000.0;
	      b_genA1_Lz  = -1000.0;
	      b_genA0_Lxy = -1000.0;
	      b_genA1_Lxy = -1000.0;
	      b_genA0_L   = -1000.0;
	      b_genA1_L   = -1000.0;
      }
    
      b_genA0Mu_dEta = genMuonGroups[0][0]->eta() - genMuonGroups[0][1]->eta();
      b_genA1Mu_dEta = genMuonGroups[1][0]->eta() - genMuonGroups[1][1]->eta();
      b_genA0Mu_dPhi = My_dPhi( genMuonGroups[0][0]->phi(), genMuonGroups[0][1]->phi() );
      b_genA1Mu_dPhi = My_dPhi( genMuonGroups[1][0]->phi(), genMuonGroups[1][1]->phi() );
      b_genA0Mu_dR   = sqrt(b_genA0Mu_dEta*b_genA0Mu_dEta + b_genA0Mu_dPhi*b_genA0Mu_dPhi);
      b_genA1Mu_dR   = sqrt(b_genA1Mu_dEta*b_genA1Mu_dEta + b_genA1Mu_dPhi*b_genA1Mu_dPhi);
    } else {
      
    }
    
    if ( b_isGenALxyOK ) m_eventsGenALxyOK++;
  
    // Sort genMuons by pT (leading pT first)
    if ( genMuons.size() > 1 ) std::sort( genMuons.begin(), genMuons.end(), PtOrder );
  
    b_is4GenMu = false;

    if ( genMuons.size() == 4 ){
      m_events4GenMu++;
      b_is4GenMu = true;
    }
  
    if ( genMuons.size() > 0 ) {
      b_genMu0_px  = genMuons[0]->px();
      b_genMu0_py  = genMuons[0]->py();
      b_genMu0_pz  = genMuons[0]->pz();
      b_genMu0_pT  = genMuons[0]->pt();
      b_genMu0_eta = genMuons[0]->eta();
      b_genMu0_phi = genMuons[0]->phi();
    } else {
      b_genMu0_px  = -100.0;
      b_genMu0_py  = -100.0;
      b_genMu0_pz  = -100.0;
      b_genMu0_pT  = -100.0;
      b_genMu0_eta = -100.0;
      b_genMu0_phi = -100.0;
    }
    if ( genMuons.size() > 1 ) {
      b_genMu1_px  = genMuons[1]->px();
      b_genMu1_py  = genMuons[1]->py();
      b_genMu1_pz  = genMuons[1]->pz();
      b_genMu1_pT  = genMuons[1]->pt();
      b_genMu1_eta = genMuons[1]->eta();
      b_genMu1_phi = genMuons[1]->phi();
    } else {
      b_genMu1_px  = -100.0;
      b_genMu1_py  = -100.0;
      b_genMu1_pz  = -100.0;
      b_genMu1_pT  = -100.0;
      b_genMu1_eta = -100.0;
      b_genMu1_phi = -100.0;
    }
    if ( genMuons.size() > 2 ) {
      b_genMu2_px  = genMuons[2]->px();
      b_genMu2_py  = genMuons[2]->py();
      b_genMu2_pz  = genMuons[2]->pz();
      b_genMu2_pT  = genMuons[2]->pt();
      b_genMu2_eta = genMuons[2]->eta();
      b_genMu2_phi = genMuons[2]->phi();
    } else {
      b_genMu2_px  = -100.0;
      b_genMu2_py  = -100.0;
      b_genMu2_pz  = -100.0;
      b_genMu2_pT  = -100.0;
      b_genMu2_eta = -100.0;
      b_genMu2_phi = -100.0;
    }
    if ( genMuons.size() > 3 ) {
      b_genMu3_px  = genMuons[3]->px();
      b_genMu3_py  = genMuons[3]->py();
      b_genMu3_pz  = genMuons[3]->pz();
      b_genMu3_pT  = genMuons[3]->pt();
      b_genMu3_eta = genMuons[3]->eta();
      b_genMu3_phi = genMuons[3]->phi();
    } else {
      b_genMu3_px  = -100.0;
      b_genMu3_py  = -100.0;
      b_genMu3_pz  = -100.0;
      b_genMu3_pT  = -100.0;
      b_genMu3_eta = -100.0;
      b_genMu3_phi = -100.0;
    }

    std::vector<const reco::GenParticle*> genMuons17;
    std::vector<const reco::GenParticle*> genMuons8;
  
    for ( unsigned int i = 0; i < genMuons.size(); i++ ) {
      if ( genMuons[i]->pt() > m_threshold_Mu17_pT && fabs( genMuons[i]->eta() ) < m_threshold_Mu17_eta ) {
        genMuons17.push_back(genMuons[i]);
      }
      if ( genMuons[i]->pt() > m_threshold_Mu8_pT && fabs( genMuons[i]->eta() ) < m_threshold_Mu8_eta ) {
        genMuons8.push_back(genMuons[i]);
      }
    }
    b_is1GenMu17 = false; 
    b_is2GenMu8  = false;
    b_is3GenMu8  = false;
    b_is4GenMu8  = false;

    if ( genMuons17.size() >=1) {
      m_events1GenMu17++;
      b_is1GenMu17 = true;
      if ( genMuons8.size() >=2 ) {
        m_events2GenMu8++;
        b_is2GenMu8 = true;
      }
      if ( genMuons8.size() >=3 ) {
        m_events3GenMu8++;
        b_is3GenMu8 = true;
      }
      if ( genMuons8.size() >=4 ) {
        m_events4GenMu8++;
        b_is4GenMu8 = true;
      }
    }
  
    if ( m_debug > 10 ) std::cout << m_events << " Stop GEN Level" << std::endl;
  }
  
  //****************************************************************************
  //                          GEN LEVEL ANALYSIS FINISH                         
  //****************************************************************************
  
  //****************************************************************************
  //                          RECO LEVEL ANALYSIS START                         
  //****************************************************************************
  
  if ( m_debug > 10 ) std::cout << m_events << " Start RECO Level" << std::endl;
  
  edm::Handle<pat::MuonCollection> muons;
  iEvent.getByLabel(m_muons, muons);
  
  std::vector<const reco::Muon*> selMuons;
  std::vector<const reco::Muon*> selMuons8;
  std::vector<const reco::Muon*> selMuons17;
  
  for (pat::MuonCollection::const_iterator iMuon = muons->begin();  iMuon != muons->end();  ++iMuon) {
    if ( isPFMuonLoose( &(*iMuon) ) ) {
//    if ( isTrackerMuonPrivateID( &(*iMuon) ) ) {
      selMuons.push_back( &(*iMuon) );
      if ( iMuon->pt() > m_threshold_Mu8_pT ) {
        selMuons8.push_back( &(*iMuon) );
      }
      if ( iMuon->pt() > m_threshold_Mu17_pT && fabs(iMuon->eta()) < m_threshold_Mu17_eta ) {
        selMuons17.push_back( &(*iMuon) );
      }
    }
  }
  
  if ( selMuons.size() > 0 ) {
    b_selMu0_px  = selMuons[0]->px();
    b_selMu0_py  = selMuons[0]->py();
    b_selMu0_pz  = selMuons[0]->pz();
    b_selMu0_eta = selMuons[0]->eta();
    b_selMu0_phi = selMuons[0]->phi();
  } else {
    b_selMu0_px  = -100.0;
    b_selMu0_py  = -100.0;
    b_selMu0_pz  = -100.0;
    b_selMu0_eta = -100.0;
    b_selMu0_phi = -100.0;
  }
  if ( selMuons.size() > 1 ) {
    b_selMu1_px  = selMuons[1]->px();
    b_selMu1_py  = selMuons[1]->py();
    b_selMu1_pz  = selMuons[1]->pz();
    b_selMu1_eta = selMuons[1]->eta();
    b_selMu1_phi = selMuons[1]->phi();
  } else {
    b_selMu1_px  = -100.0;
    b_selMu1_py  = -100.0;
    b_selMu1_pz  = -100.0;
    b_selMu1_eta = -100.0;
    b_selMu1_phi = -100.0;
  }
  if ( selMuons.size() > 2 ) {
    b_selMu2_px  = selMuons[2]->px();
    b_selMu2_py  = selMuons[2]->py();
    b_selMu2_pz  = selMuons[2]->pz();
    b_selMu2_eta = selMuons[2]->eta();
    b_selMu2_phi = selMuons[2]->phi();
  } else {
    b_selMu2_px  = -100.0;
    b_selMu2_py  = -100.0;
    b_selMu2_pz  = -100.0;
    b_selMu2_eta = -100.0;
    b_selMu2_phi = -100.0;
  }
  if ( selMuons.size() > 3 ) {
    b_selMu3_px  = selMuons[3]->px();
    b_selMu3_py  = selMuons[3]->py();
    b_selMu3_pz  = selMuons[3]->pz();
    b_selMu3_eta = selMuons[3]->eta();
    b_selMu3_phi = selMuons[3]->phi();
  } else {
    b_selMu3_px  = -100.0;
    b_selMu3_py  = -100.0;
    b_selMu3_pz  = -100.0;
    b_selMu3_eta = -100.0;
    b_selMu3_phi = -100.0;
  }
  
  if ( m_debug > 10 ) std::cout << m_events << " Count selected RECO muons" << std::endl;
  
  b_is1SelMu17 = false;
  b_is2SelMu8  = false;
  b_is3SelMu8  = false;
  b_is4SelMu8  = false;
  if ( selMuons17.size() >=1 ) {
    m_events1SelMu17++;
    b_is1SelMu17 = true;
    if ( selMuons8.size() >=2 ) {
      m_events2SelMu8++;
      b_is2SelMu8 = true;
    }
    if ( selMuons8.size() >=3 ) {
      m_events3SelMu8++;
      b_is3SelMu8 = true;
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
  int   nMuJetsContainMu17     = 0;
  unsigned int nMuJets = muJets->size();
  b_is2MuJets = false;
  if ( nMuJets == 2) {
    for ( unsigned int j = 0; j < nMuJets; j++ ) {
      bool isMuJetContainMu17 = false;
      for ( unsigned int m = 0; m < (*muJets)[j].numberOfDaughters(); m++ ) {
        if ( (*muJets)[j].muon(m)->pt() > m_threshold_Mu17_pT && fabs( (*muJets)[j].muon(m)->eta() ) < m_threshold_Mu17_eta ) {
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
  
  if ( m_debug > 10 ) std::cout << m_events << " Check if exactly 2 muon jets are built" << std::endl;
  if ( b_is1SelMu17 && b_is4SelMu8 && b_is2MuJets) m_events2MuJets++;
  
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
  if ( b_is1SelMu17 && b_is4SelMu8 && b_is2MuJets && b_is2DiMuons) m_events2DiMuons++;
  
  // "Old" fitted vertexes
  b_is2DiMuonsFittedVtxOK = false;
  if ( diMuonC != NULL && diMuonF != NULL ) {
    if ( diMuonC->vertexValid() && diMuonF->vertexValid() ) {
      b_is2DiMuonsFittedVtxOK = true;
    }
  }
  // Fill branches with variables calculated with "old" fitted vertexes
  if ( b_is2DiMuonsFittedVtxOK ) {
    b_diMuonC_FittedVtx_m   = diMuonC->vertexMass();
    b_diMuonC_FittedVtx_px  = diMuonC->vertexMomentum().x();
    b_diMuonC_FittedVtx_py  = diMuonC->vertexMomentum().y();
    b_diMuonC_FittedVtx_pz  = diMuonC->vertexMomentum().z();
    b_diMuonC_FittedVtx_eta = diMuonC->vertexMomentum().eta();
    b_diMuonC_FittedVtx_phi = diMuonC->vertexMomentum().phi();
    b_diMuonC_FittedVtx_vx  = diMuonC->vertexPoint().x();
    b_diMuonC_FittedVtx_vy  = diMuonC->vertexPoint().y();
    b_diMuonC_FittedVtx_vz  = diMuonC->vertexPoint().z();

    b_diMuonC_FittedVtx_Lxy = diMuonC->vertexLxy(beamSpotPosition);
    b_diMuonC_FittedVtx_L   = diMuonC->vertexL(beamSpotPosition);
    b_diMuonC_FittedVtx_dz  = diMuonC->vertexDz(beamSpot->position());
    
    b_diMuonF_FittedVtx_m   = diMuonF->vertexMass();
    b_diMuonF_FittedVtx_px  = diMuonF->vertexMomentum().x();
    b_diMuonF_FittedVtx_py  = diMuonF->vertexMomentum().y();
    b_diMuonF_FittedVtx_pz  = diMuonF->vertexMomentum().z();
    b_diMuonF_FittedVtx_eta = diMuonF->vertexMomentum().eta();
    b_diMuonF_FittedVtx_phi = diMuonF->vertexMomentum().phi();
    b_diMuonF_FittedVtx_vx  = diMuonF->vertexPoint().x();
    b_diMuonF_FittedVtx_vy  = diMuonF->vertexPoint().y();
    b_diMuonF_FittedVtx_vz  = diMuonF->vertexPoint().z();

    b_diMuonF_FittedVtx_Lxy = diMuonF->vertexLxy(beamSpotPosition);
    b_diMuonF_FittedVtx_L   = diMuonF->vertexL(beamSpotPosition);
    b_diMuonF_FittedVtx_dz  = diMuonF->vertexDz(beamSpot->position());
  } else {
    b_diMuonC_FittedVtx_m   = -1000.0;
    b_diMuonC_FittedVtx_px  = -1000.0;
    b_diMuonC_FittedVtx_py  = -1000.0;
    b_diMuonC_FittedVtx_pz  = -1000.0;
    b_diMuonC_FittedVtx_eta = -1000.0;
    b_diMuonC_FittedVtx_phi = -1000.0;
    b_diMuonC_FittedVtx_vx  = -1000.0;
    b_diMuonC_FittedVtx_vy  = -1000.0;
    b_diMuonC_FittedVtx_vz  = -1000.0;

    b_diMuonC_FittedVtx_Lxy = -1000.0;
    b_diMuonC_FittedVtx_L   = -1000.0;
    b_diMuonC_FittedVtx_dz  = -1000.0;
    
    b_diMuonF_FittedVtx_m   = -1000.0;
    b_diMuonF_FittedVtx_px  = -1000.0;
    b_diMuonF_FittedVtx_py  = -1000.0;
    b_diMuonF_FittedVtx_pz  = -1000.0;
    b_diMuonF_FittedVtx_eta = -1000.0;
    b_diMuonF_FittedVtx_phi = -1000.0;
    b_diMuonF_FittedVtx_vx  = -1000.0;
    b_diMuonF_FittedVtx_vy  = -1000.0;
    b_diMuonF_FittedVtx_vz  = -1000.0;

    b_diMuonF_FittedVtx_Lxy = -1000.0;
    b_diMuonF_FittedVtx_L   = -1000.0;
    b_diMuonF_FittedVtx_dz  = -1000.0;
  }
  
  // "New" consistent vertexes
  b_is2DiMuonsConsistentVtxOK = false;
  if ( diMuonC != NULL && diMuonF != NULL ) {
    edm::ESHandle<TransientTrackBuilder> transientTrackBuilder;
    const TransientTrackBuilder *transientTrackBuilder_ptr = NULL;
    iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder", transientTrackBuilder);
    transientTrackBuilder_ptr = &*transientTrackBuilder;
    
    ConsistentVertexesCalculator ConsistentVtx(transientTrackBuilder_ptr, beamSpotPosition);
   
    ConsistentVtx.SetNThrows(m_nThrowsConsistentVertexesCalculator);
    ConsistentVtx.SetDebug(0);
    
    b_is2DiMuonsConsistentVtxOK = ConsistentVtx.Calculate(diMuonC, diMuonF);
  }
  // Fill branches with variables calculated with "new" consistent vertexes
  if ( b_is2DiMuonsConsistentVtxOK ) {
    b_diMuonC_ConsistentVtx_m   = diMuonC->consistentVtxMass();
    b_diMuonC_ConsistentVtx_px  = diMuonC->consistentVtxMomentum().x();
    b_diMuonC_ConsistentVtx_py  = diMuonC->consistentVtxMomentum().y();
    b_diMuonC_ConsistentVtx_pz  = diMuonC->consistentVtxMomentum().z();
    b_diMuonC_ConsistentVtx_eta = diMuonC->consistentVtxMomentum().eta();
    b_diMuonC_ConsistentVtx_phi = diMuonC->consistentVtxMomentum().phi();
    b_diMuonC_ConsistentVtx_vx  = diMuonC->consistentVtxPoint().x();
    b_diMuonC_ConsistentVtx_vy  = diMuonC->consistentVtxPoint().y();
    b_diMuonC_ConsistentVtx_vz  = diMuonC->consistentVtxPoint().z();

    b_diMuonC_ConsistentVtx_Lxy = diMuonC->consistentVtxLxy(beamSpotPosition);
    b_diMuonC_ConsistentVtx_L   = diMuonC->consistentVtxL(beamSpotPosition);
    b_diMuonC_ConsistentVtx_dz  = diMuonC->consistentVtxDz(beamSpotPosition);
    
    b_diMuonF_ConsistentVtx_m   = diMuonF->consistentVtxMass();
    b_diMuonF_ConsistentVtx_px  = diMuonF->consistentVtxMomentum().x();
    b_diMuonF_ConsistentVtx_py  = diMuonF->consistentVtxMomentum().y();
    b_diMuonF_ConsistentVtx_pz  = diMuonF->consistentVtxMomentum().z();
    b_diMuonF_ConsistentVtx_eta = diMuonF->consistentVtxMomentum().eta();
    b_diMuonF_ConsistentVtx_phi = diMuonF->consistentVtxMomentum().phi();
    b_diMuonF_ConsistentVtx_vx  = diMuonF->consistentVtxPoint().x();
    b_diMuonF_ConsistentVtx_vy  = diMuonF->consistentVtxPoint().y();
    b_diMuonF_ConsistentVtx_vz  = diMuonF->consistentVtxPoint().z();

    b_diMuonF_ConsistentVtx_Lxy = diMuonF->consistentVtxLxy(beamSpotPosition);
    b_diMuonF_ConsistentVtx_L   = diMuonF->consistentVtxL(beamSpotPosition);
    b_diMuonF_ConsistentVtx_dz  = diMuonF->consistentVtxDz(beamSpotPosition);
  } else {
    b_diMuonC_ConsistentVtx_m   = -1000.0;
    b_diMuonC_ConsistentVtx_px  = -1000.0;
    b_diMuonC_ConsistentVtx_py  = -1000.0;
    b_diMuonC_ConsistentVtx_pz  = -1000.0;
    b_diMuonC_ConsistentVtx_eta = -1000.0;
    b_diMuonC_ConsistentVtx_phi = -1000.0;
    b_diMuonC_ConsistentVtx_vx  = -1000.0;
    b_diMuonC_ConsistentVtx_vy  = -1000.0;
    b_diMuonC_ConsistentVtx_vz  = -1000.0;

    b_diMuonC_ConsistentVtx_Lxy = -1000.0;
    b_diMuonC_ConsistentVtx_L   = -1000.0;
    b_diMuonC_ConsistentVtx_dz  = -1000.0;
    
    b_diMuonF_ConsistentVtx_m   = -1000.0;
    b_diMuonF_ConsistentVtx_px  = -1000.0;
    b_diMuonF_ConsistentVtx_py  = -1000.0;
    b_diMuonF_ConsistentVtx_pz  = -1000.0;
    b_diMuonF_ConsistentVtx_eta = -1000.0;
    b_diMuonF_ConsistentVtx_phi = -1000.0;
    b_diMuonF_ConsistentVtx_vx  = -1000.0;
    b_diMuonF_ConsistentVtx_vy  = -1000.0;
    b_diMuonF_ConsistentVtx_vz  = -1000.0;

    b_diMuonF_ConsistentVtx_Lxy = -1000.0;
    b_diMuonF_ConsistentVtx_L   = -1000.0;
    b_diMuonF_ConsistentVtx_dz  = -1000.0;
  }
  
  
  // Calculate dz between dimuons - use fitted vertexes
  b_is2DiMuonsDzOK_FittedVtx = false;
  if ( b_is2DiMuonsFittedVtxOK ) {
    b_diMuons_dz_FittedVtx = b_diMuonC_FittedVtx_dz - b_diMuonF_FittedVtx_dz;
    if ( fabs( b_diMuons_dz_FittedVtx ) < m_threshold_DiMuons_dz ) b_is2DiMuonsDzOK_FittedVtx = true;
  } else {
    b_diMuons_dz_FittedVtx = -1000.0;
  }

  // Calculate dz between dimuons - use consistent vertexes
  b_is2DiMuonsDzOK_ConsistentVtx = false;
  if ( b_is2DiMuonsConsistentVtxOK ) {
    b_diMuons_dz_ConsistentVtx = b_diMuonC_ConsistentVtx_dz - b_diMuonF_ConsistentVtx_dz;
    if ( fabs( b_diMuons_dz_ConsistentVtx ) < m_threshold_DiMuons_dz ) b_is2DiMuonsDzOK_ConsistentVtx = true;
  } else {
    b_diMuons_dz_ConsistentVtx = -1000.0;
  }
  
  if ( m_debug > 10 ) std::cout << m_events << " Apply cut on dZ" << std::endl;
  if ( b_is1SelMu17 && b_is4SelMu8 && b_is2MuJets && b_is2DiMuons && b_is2DiMuonsDzOK_FittedVtx     ) m_events2DiMuonsDzOK_FittedVtx++;
  if ( b_is1SelMu17 && b_is4SelMu8 && b_is2MuJets && b_is2DiMuons && b_is2DiMuonsDzOK_ConsistentVtx ) m_events2DiMuonsDzOK_ConsistentVtx++;

  // HLT cut
  edm::Handle<pat::TriggerEvent> triggerEvent;
  iEvent.getByLabel("patTriggerEvent", triggerEvent);
  
  b_isDiMuonHLTFired = false;
  b_hltPaths.clear();
  for (auto p : hltPaths_){
    if ( !triggerEvent->path(p) ) {
      if ( m_debug > 10 ) std::cout << p << " is not present in patTriggerEvent!" << std::endl;
    }
    else{
      if ( triggerEvent->path(p)->wasAccept() ) {
	b_isDiMuonHLTFired = true;	
	b_hltPaths.push_back(p);
      }
    }
  } 
  
  if ( m_debug > 10 ) std::cout << m_events << " Apply cut on HLT" << std::endl;
  if ( b_is1SelMu17 && b_is4SelMu8 && b_is2MuJets && b_is2DiMuons && b_is2DiMuonsDzOK_FittedVtx     && b_isDiMuonHLTFired ) m_eventsDiMuonHLTFired_FittedVtx++;
  if ( b_is1SelMu17 && b_is4SelMu8 && b_is2MuJets && b_is2DiMuons && b_is2DiMuonsDzOK_ConsistentVtx && b_isDiMuonHLTFired ) m_eventsDiMuonHLTFired_ConsistentVtx++;
  
  // Cut on dimuon masses - use fitted vertexes
  b_is2DiMuonsMassOK_FittedVtx = false;
  if ( b_is2DiMuonsFittedVtxOK ) {
    double massC = b_diMuonC_FittedVtx_m;
    double massF = b_diMuonF_FittedVtx_m;
    if ( fabs(massC-massF) < (0.13 + 0.065*(massC+massF)/2.0) ) b_is2DiMuonsMassOK_FittedVtx = true;
  }
  
  // Cut on dimuon masses - use consistent vertexes
  b_is2DiMuonsMassOK_ConsistentVtx = false;
  if ( b_is2DiMuonsConsistentVtxOK ) {
    double massC = b_diMuonC_ConsistentVtx_m;
    double massF = b_diMuonF_ConsistentVtx_m;
    if ( fabs(massC-massF) < (0.13 + 0.065*(massC+massF)/2.0) ) b_is2DiMuonsMassOK_ConsistentVtx = true;
  }
  
  if ( m_debug > 10 ) std::cout << m_events << " Apply cut on dimuon mass" << std::endl;
  if ( b_is1SelMu17 && b_is4SelMu8 && b_is2MuJets && b_is2DiMuons && b_is2DiMuonsDzOK_FittedVtx     && b_isDiMuonHLTFired && b_is2DiMuonsMassOK_FittedVtx )     m_events2DiMuonsMassOK_FittedVtx++;
  if ( b_is1SelMu17 && b_is4SelMu8 && b_is2MuJets && b_is2DiMuons && b_is2DiMuonsDzOK_ConsistentVtx && b_isDiMuonHLTFired && b_is2DiMuonsMassOK_ConsistentVtx ) m_events2DiMuonsMassOK_ConsistentVtx++;
  
  // Cut on isolation
  edm::Handle<reco::TrackCollection> tracks;
  iEvent.getByLabel("generalTracks", tracks);
  
//  edm::Handle<reco::PFCandidateCollection> pfCandidates;
//  iEvent.getByLabel("particleFlow", pfCandidates);
  
  // Cut on isolation - use fitted vertexes
  b_is2DiMuonsIsoTkOK_FittedVtx = false;
  b_diMuonC_IsoTk_FittedVtx = -1.;
  b_diMuonF_IsoTk_FittedVtx = -1.;
//  b_diMuonC_IsoPF_FittedVtx = -1.;
//  b_diMuonF_IsoPF_FittedVtx = -1.;
  if ( b_is2DiMuonsFittedVtxOK ) {
    double diMuonC_IsoTk_FittedVtx = 0.0;
    double diMuonF_IsoTk_FittedVtx = 0.0;
//    double diMuonC_IsoPF_FittedVtx = 0.0;
//    double diMuonF_IsoPF_FittedVtx = 0.0;

    const pat::MultiMuon *diMuonTmp = NULL;
    for ( unsigned int i = 1; i <= 2; i++ ) { 
      double diMuonTmp_IsoTk_FittedVtx = 0.0;
//      double diMuonTmp_IsoPF_FittedVtx = 0.0;
      if ( i == 1 ) diMuonTmp = diMuonC;
      if ( i == 2 ) diMuonTmp = diMuonF;

      for (reco::TrackCollection::const_iterator track = tracks->begin(); track != tracks->end(); ++track) {
        bool trackIsMuon = false;
        if (    diMuonTmp->sameTrack( &*track, &*(diMuonTmp->muon(0)->innerTrack()) )
             || diMuonTmp->sameTrack( &*track, &*(diMuonTmp->muon(1)->innerTrack()) ) ) trackIsMuon = true;
        if ( trackIsMuon == false ) {
          double dPhi = My_dPhi( diMuonTmp->vertexMomentum().phi(), track->phi() );
          double dEta = diMuonTmp->vertexMomentum().eta() - track->eta();
          double dR   = sqrt( dPhi*dPhi + dEta*dEta ); 
          double dz   = diMuonTmp->vertexDz(beamSpot->position()) - track->dz(beamSpot->position());
          if (    dR          < m_threshold_DiMuons_Iso_dR
               && track->pt() > m_threshold_DiMuons_Iso_pT
               && fabs( dz )  < m_threshold_DiMuons_Iso_dz ) {
            diMuonTmp_IsoTk_FittedVtx += track->pt();
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
//            if ( dz < 0.1 ) diMuonTmp_IsoPF += pfCand->pt();
//          }
//        }
//      }
      if ( i == 1 ) {
        diMuonC_IsoTk_FittedVtx = diMuonTmp_IsoTk_FittedVtx;
//        diMuonC_IsoPF_FittedVtx = diMuonTmp_IsoPF_FittedVtx;
      }
      if ( i == 2 ) {
        diMuonF_IsoTk_FittedVtx = diMuonTmp_IsoTk_FittedVtx;
//        diMuonF_IsoPF_FittedVtx = diMuonTmp_IsoPF_FittedVtx;
      }
    }
    b_diMuonC_IsoTk_FittedVtx = diMuonC_IsoTk_FittedVtx;
    b_diMuonF_IsoTk_FittedVtx = diMuonF_IsoTk_FittedVtx;
//    b_diMuonC_IsoPF_FittedVtx = diMuonC_IsoPF_FittedVtx;
//    b_diMuonF_IsoPF_FittedVtx = diMuonF_IsoPF_FittedVtx;


    if ( b_diMuonC_IsoTk_FittedVtx < m_threshold_DiMuons_Iso && b_diMuonF_IsoTk_FittedVtx < m_threshold_DiMuons_Iso ) b_is2DiMuonsIsoTkOK_FittedVtx = true;
//    if ( b_diMuonC_IsoPF_FittedVtx < m_threshold_DiMuons_Iso && b_diMuonF_IsoPF_FittedVtx < m_threshold_DiMuons_Iso ) b_is2DiMuonsIsoPFOK_FittedVtx = true;
  }
  
  // Cut on isolation - use consistent vertexes
  b_is2DiMuonsIsoTkOK_ConsistentVtx = false;
  b_diMuonC_IsoTk_ConsistentVtx = -1.;
  b_diMuonF_IsoTk_ConsistentVtx = -1.;
//  b_diMuonC_IsoPF_ConsistentVtx = -1.;
//  b_diMuonF_IsoPF_ConsistentVtx = -1.;
  if ( b_is2DiMuonsConsistentVtxOK ) {
    double diMuonC_IsoTk_ConsistentVtx = 0.0;
    double diMuonF_IsoTk_ConsistentVtx = 0.0;
//    double diMuonC_IsoPF_ConsistentVtx = 0.0;
//    double diMuonF_IsoPF_ConsistentVtx = 0.0;

    const pat::MultiMuon *diMuonTmp = NULL;
    for ( unsigned int i = 1; i <= 2; i++ ) { 
      double diMuonTmp_IsoTk_ConsistentVtx = 0.0;
//      double diMuonTmp_IsoPF_ConsistentVtx = 0.0;
      if ( i == 1 ) diMuonTmp = diMuonC;
      if ( i == 2 ) diMuonTmp = diMuonF;

      for (reco::TrackCollection::const_iterator track = tracks->begin(); track != tracks->end(); ++track) {
        bool trackIsMuon = false;
        if (    diMuonTmp->sameTrack( &*track, &*(diMuonTmp->muon(0)->innerTrack()) )
             || diMuonTmp->sameTrack( &*track, &*(diMuonTmp->muon(1)->innerTrack()) ) ) trackIsMuon = true;
        if ( trackIsMuon == false ) {
          double dPhi = My_dPhi( diMuonTmp->consistentVtxMomentum().phi(), track->phi() );
          double dEta = diMuonTmp->consistentVtxMomentum().eta() - track->eta();
          double dR   = sqrt( dPhi*dPhi + dEta*dEta ); 
          double dz   = diMuonTmp->consistentVtxDz(beamSpotPosition) - track->dz(beamSpot->position());
          if (    dR          < m_threshold_DiMuons_Iso_dR
               && track->pt() > m_threshold_DiMuons_Iso_pT
               && fabs( dz )  < m_threshold_DiMuons_Iso_dz ) {
            diMuonTmp_IsoTk_ConsistentVtx += track->pt();
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
//            if ( dz < 0.1 ) diMuonTmp_IsoPF += pfCand->pt();
//          }
//        }
//      }
      if ( i == 1 ) {
        diMuonC_IsoTk_ConsistentVtx = diMuonTmp_IsoTk_ConsistentVtx;
//        diMuonC_IsoPF_ConsistentVtx = diMuonTmp_IsoPF_ConsistentVtx;
      }
      if ( i == 2 ) {
        diMuonF_IsoTk_ConsistentVtx = diMuonTmp_IsoTk_ConsistentVtx;
//        diMuonF_IsoPF_ConsistentVtx = diMuonTmp_IsoPF_ConsistentVtx;
      }
    }
    b_diMuonC_IsoTk_ConsistentVtx = diMuonC_IsoTk_ConsistentVtx;
    b_diMuonF_IsoTk_ConsistentVtx = diMuonF_IsoTk_ConsistentVtx;
//    b_diMuonC_IsoPF_ConsistentVtx = diMuonC_IsoPF_ConsistentVtx;
//    b_diMuonF_IsoPF_ConsistentVtx = diMuonF_IsoPF_ConsistentVtx;


    if ( b_diMuonC_IsoTk_ConsistentVtx < m_threshold_DiMuons_Iso && b_diMuonF_IsoTk_ConsistentVtx < m_threshold_DiMuons_Iso ) b_is2DiMuonsIsoTkOK_ConsistentVtx = true;
//    if ( b_diMuonC_IsoPF_ConsistentVtx < m_threshold_DiMuons_Iso && b_diMuonF_IsoPF_ConsistentVtx < m_threshold_DiMuons_Iso ) b_is2DiMuonsIsoPFOK_ConsistentVtx = true;
  }
  
  if ( m_debug > 10 ) std::cout << m_events << " Apply cut on dimuon isolation" << std::endl;
  
  if ( b_is1SelMu17 && b_is4SelMu8 && b_is2MuJets && b_is2DiMuons && b_is2DiMuonsDzOK_FittedVtx     && b_isDiMuonHLTFired && b_is2DiMuonsMassOK_FittedVtx     && b_is2DiMuonsIsoTkOK_FittedVtx     ) m_events2DiMuonsIsoTkOK_FittedVtx++;
  if ( b_is1SelMu17 && b_is4SelMu8 && b_is2MuJets && b_is2DiMuons && b_is2DiMuonsDzOK_ConsistentVtx && b_isDiMuonHLTFired && b_is2DiMuonsMassOK_ConsistentVtx && b_is2DiMuonsIsoTkOK_ConsistentVtx ) m_events2DiMuonsIsoTkOK_ConsistentVtx++;
  
  
  if ( b_is2DiMuonsFittedVtxOK ) {
    for(uint32_t k=0;k<2;k++){
      for (reco::TrackCollection::const_iterator track = tracks->begin(); track != tracks->end(); ++track) {
	if(sameTrack(&*track,&*(diMuonC->muon(k)->innerTrack()))){
	  const reco::HitPattern& p = track->hitPattern();
	  if(p.hasValidHitInFirstPixelEndcap() || p.hasValidHitInFirstPixelBarrel()){
	    if(k==0) b_diMuonC_m1_FittedVtx_hitpix = 1;
	    if(k==1) b_diMuonC_m2_FittedVtx_hitpix = 1;
	  }
	}
	if(sameTrack(&*track,&*(diMuonF->muon(k)->innerTrack()))){
	  const reco::HitPattern& p = track->hitPattern();
	  if(p.hasValidHitInFirstPixelEndcap() || p.hasValidHitInFirstPixelBarrel()){
	    if(k==0) b_diMuonF_m1_FittedVtx_hitpix = 1;
	    if(k==1) b_diMuonF_m2_FittedVtx_hitpix = 1;
	  }
	}
      }
    }
  }

  // Cut on primary vertex in event
  edm::Handle<reco::VertexCollection> primaryVertices;
  iEvent.getByLabel("offlinePrimaryVertices", primaryVertices);
  
  b_isVertexOK = false;
  for (reco::VertexCollection::const_iterator vertex = primaryVertices->begin();  vertex != primaryVertices->end();  ++vertex) {
    if (vertex->isValid() && !vertex->isFake() && vertex->tracksSize() >= 4 && fabs(vertex->z()) < 24.) {
      b_isVertexOK = true;
    }
  }
  
  if ( m_debug > 10 ) std::cout << m_events << " Apply cut on primary vertex in event" << std::endl;
  if ( b_is1SelMu17 && b_is4SelMu8 && b_is2MuJets && b_is2DiMuons && b_is2DiMuonsDzOK_FittedVtx     && b_isDiMuonHLTFired && b_is2DiMuonsMassOK_FittedVtx     && b_is2DiMuonsIsoTkOK_FittedVtx     && b_isVertexOK ) m_eventsVertexOK_FittedVtx++;
  if ( b_is1SelMu17 && b_is4SelMu8 && b_is2MuJets && b_is2DiMuons && b_is2DiMuonsDzOK_ConsistentVtx && b_isDiMuonHLTFired && b_is2DiMuonsMassOK_ConsistentVtx && b_is2DiMuonsIsoTkOK_ConsistentVtx && b_isVertexOK ) m_eventsVertexOK_ConsistentVtx++;
  

//  // Add dimuons' Lxy to ntuple
//  if ( m_debug > 10 ) std::cout << m_events << " Build RECO dimuon Lxy" << std::endl;
//  b_is2DiMuonsLxyOK_ConsistentVtx = false;
//  b_diMuonC_Lxy = -1000.0;
//  b_diMuonF_Lxy = -1000.0;
//  
//  if ( diMuonC != NULL && diMuonC->vertexValid() && diMuonF != NULL && diMuonF->vertexValid() ) {
//    if ( m_debug > 10 ) std::cout << m_events << " Dimuons vertexes are valid" << std::endl;
//    if ( m_debug > 10 ) std::cout << m_events << " Loop through vertexes and find closest" << std::endl;
//    reco::VertexCollection::const_iterator diMuonC_closestPrimaryVertex;
//    bool diMuonC_closestPrimaryVertex_isFound = false;
//    reco::VertexCollection::const_iterator diMuonF_closestPrimaryVertex;
//    bool diMuonF_closestPrimaryVertex_isFound = false;
//    int n_vertex =  0;
//    for (reco::VertexCollection::const_iterator vertex = primaryVertices->begin();  vertex != primaryVertices->end();  ++vertex) {
//      
//      if ( m_debug > 10 ) std::cout << m_events << " Vertex #" << n_vertex << " isValid " << vertex->isValid() << " isFake " << vertex->isFake() << " tracksSize " << vertex->tracksSize() << " z " << vertex->z() << std::endl;
//      if (vertex->isValid()  &&  !vertex->isFake()  &&  vertex->tracksSize() >= 4  &&  fabs(vertex->z()) < 24.) {
////        std::cout << "diMuonC->vertexPoint().z(): " << diMuonC->vertexPoint().z() << std::endl;
//        if ( m_debug > 10 ) std::cout << m_events << " Vertex is OK" << std::endl;
//        if ( m_debug > 10 ) std::cout << m_events << " diMuonC->vertexPoint().z() " << diMuonC->vertexPoint().z() << std::endl;
//        if ( diMuonC_closestPrimaryVertex_isFound == false ) {
//          diMuonC_closestPrimaryVertex         = vertex;
//          diMuonC_closestPrimaryVertex_isFound = true;
//        }
//        if ( fabs(vertex->z() - diMuonC->vertexPoint().z()) < fabs(diMuonC_closestPrimaryVertex->z() - diMuonC->vertexPoint().z()) ) {
//          diMuonC_closestPrimaryVertex = vertex;
//          if ( m_debug > 10 ) std::cout << m_events << " Better diMuonC_closestPrimaryVertex is found" << std::endl;
//        }
//        if ( m_debug > 10 ) std::cout << m_events << " diMuonC_closestPrimaryVertex->z() " << diMuonC_closestPrimaryVertex->z() << std::endl;
//        
//        if ( m_debug > 10 ) std::cout << m_events << " diMuonF->vertexPoint().z() " << diMuonF->vertexPoint().z() << std::endl;
//        if ( diMuonF_closestPrimaryVertex_isFound == false ) {
//          diMuonF_closestPrimaryVertex         = vertex;
//          diMuonF_closestPrimaryVertex_isFound = true;
//        }
//        if ( fabs(vertex->z() - diMuonF->vertexPoint().z()) < fabs(diMuonF_closestPrimaryVertex->z() - diMuonF->vertexPoint().z()) ) {
//          diMuonF_closestPrimaryVertex = vertex;
//          if ( m_debug > 10 ) std::cout << m_events << " Better diMuonF_closestPrimaryVertex is found" << std::endl;
//        }
//        if ( m_debug > 10 ) std::cout << m_events << " diMuonF_closestPrimaryVertex->z() " << diMuonF_closestPrimaryVertex->z() << std::endl;
//      } else {
//        if ( m_debug > 10 ) std::cout << m_events << " Vertex is not OK" << std::endl;
//      }
//      
//      n_vertex++;
//    }

//    if ( m_debug > 10 ) std::cout << m_events << " Calculate Lxy for diMuonC" << std::endl;
//    if ( diMuonC_closestPrimaryVertex_isFound ) {
//      b_diMuonC_Lxy = diMuonC->vertexLxy(diMuonC_closestPrimaryVertex->x(), diMuonC_closestPrimaryVertex->y(), diMuonC_closestPrimaryVertex->z());
//    } else {
//      b_diMuonC_Lxy = diMuonC->vertexLxy(0.0, 0.0, 0.0);
//    }
//    
//    if ( m_debug > 10 ) std::cout << m_events << " Calculate Lxy for diMuonF" << std::endl;
//    if ( diMuonF_closestPrimaryVertex_isFound ) {
//      b_diMuonF_Lxy = diMuonF->vertexLxy(diMuonF_closestPrimaryVertex->x(), diMuonF_closestPrimaryVertex->y(), diMuonF_closestPrimaryVertex->z());
//    } else {
//      b_diMuonF_Lxy = diMuonF->vertexLxy(0.0, 0.0, 0.0);
//    }
//    if ( b_diMuonC_Lxy  < 4.0 && b_diMuonF_Lxy < 4.0 ) b_is2DiMuonsLxyOK_ConsistentVtx = true;
//  }
  
  if ( m_debug > 10 ) std::cout << m_events << " Stop RECO Level" << std::endl;
  
  //****************************************************************************
  //                          RECO LEVEL ANALYSIS FINISH                        
  //****************************************************************************
  
  //****************************************************************************
  //                            FILL BRANCHES TO TREE                           
  //****************************************************************************
  
  m_ttree->Fill();
  
}


// ------------ method called once each job just before starting event loop  ------------
void 
CutFlowAnalyzer::beginJob() {
  std::cout << "BEGIN JOB" << std::endl;
  
  edm::Service<TFileService> tFileService;
  m_ttree = tFileService->make<TTree>("Events", "Events");

  //****************************************************************************
  //                          EVENT LEVEL BRANCHES                              
  //****************************************************************************

  // Event info
  m_ttree->Branch("event", &b_event, "event/I");
  m_ttree->Branch("run",   &b_run,   "run/I");
  m_ttree->Branch("lumi",  &b_lumi,  "lumi/I");

  // Beam spot
  m_ttree->Branch("beamSpot_x", &b_beamSpot_x, "beamSpot_x/F");
  m_ttree->Branch("beamSpot_y", &b_beamSpot_y, "beamSpot_y/F");
  m_ttree->Branch("beamSpot_z", &b_beamSpot_z, "beamSpot_z/F");
  
  //****************************************************************************
  //                          GEN LEVEL BRANCHES                                
  //****************************************************************************
  
  // Bosons
  m_ttree->Branch("genH_m",    &b_genH_m,    "genH_m/F");
  m_ttree->Branch("genH_px",   &b_genH_px,   "genH_px/F");
  m_ttree->Branch("genH_py",   &b_genH_py,   "genH_py/F");
  m_ttree->Branch("genH_pz",   &b_genH_pz,   "genH_pz/F");
  m_ttree->Branch("genH_eta",  &b_genH_eta,  "genH_eta/F");
  m_ttree->Branch("genH_phi",  &b_genH_phi,  "genH_phi/F");
  m_ttree->Branch("genH_vx",   &b_genH_vx,   "genH_vx/F");
  m_ttree->Branch("genH_vy",   &b_genH_vy,   "genH_vy/F");
  m_ttree->Branch("genH_vz",   &b_genH_vz,   "genH_vz/F");
  
  m_ttree->Branch("genA0_m",   &b_genA0_m,   "genA0_m/F");
  m_ttree->Branch("genA0_px",  &b_genA0_px,  "genA0_px/F");
  m_ttree->Branch("genA0_py",  &b_genA0_py,  "genA0_py/F");
  m_ttree->Branch("genA0_pz",  &b_genA0_pz,  "genA0_pz/F");
  m_ttree->Branch("genA0_eta", &b_genA0_eta, "genA0_eta/F");
  m_ttree->Branch("genA0_phi", &b_genA0_phi, "genA0_phi/F");
  m_ttree->Branch("genA0_vx",  &b_genA0_vx,  "genA0_vx/F");
  m_ttree->Branch("genA0_vy",  &b_genA0_vy,  "genA0_vy/F");
  m_ttree->Branch("genA0_vz",  &b_genA0_vz,  "genA0_vz/F");
  
  m_ttree->Branch("genA0_Lx",  &b_genA0_Lx,  "genA0_Lx/F");
  m_ttree->Branch("genA0_Ly",  &b_genA0_Ly,  "genA0_Ly/F");
  m_ttree->Branch("genA0_Lz",  &b_genA0_Lz,  "genA0_Lz/F");
  m_ttree->Branch("genA0_Lxy", &b_genA0_Lxy, "genA0_Lxy/F");
  m_ttree->Branch("genA0_L",   &b_genA0_L,   "genA0_L/F");
  
  m_ttree->Branch("genA1_m",   &b_genA1_m,   "genA1_m/F");
  m_ttree->Branch("genA1_px",  &b_genA1_px,  "genA1_px/F");
  m_ttree->Branch("genA1_py",  &b_genA1_py,  "genA1_py/F");
  m_ttree->Branch("genA1_pz",  &b_genA1_pz,  "genA1_pz/F");
  m_ttree->Branch("genA1_eta", &b_genA1_eta, "genA1_eta/F");
  m_ttree->Branch("genA1_phi", &b_genA1_phi, "genA1_phi/F");
  m_ttree->Branch("genA1_vx",  &b_genA1_vx,  "genA1_vx/F");
  m_ttree->Branch("genA1_vy",  &b_genA1_vy,  "genA1_vy/F");
  m_ttree->Branch("genA1_vz",  &b_genA1_vz,  "genA1_vz/F");
  
  m_ttree->Branch("genA1_Lx",  &b_genA1_Lx,  "genA1_Lx/F");
  m_ttree->Branch("genA1_Ly",  &b_genA1_Ly,  "genA1_Ly/F");
  m_ttree->Branch("genA1_Lz",  &b_genA1_Lz,  "genA1_Lz/F");
  m_ttree->Branch("genA1_Lxy", &b_genA1_Lxy, "genA1_Lxy/F");
  m_ttree->Branch("genA1_L",   &b_genA1_L,   "genA1_L/F");
  
  // Muons from bosons
  m_ttree->Branch("genA0Mu0_px", &b_genA0Mu0_px, "genA0Mu0_px/F");
  m_ttree->Branch("genA0Mu1_px", &b_genA0Mu1_px, "genA0Mu1_px/F");
  m_ttree->Branch("genA1Mu0_px", &b_genA1Mu0_px, "genA1Mu0_px/F");
  m_ttree->Branch("genA1Mu1_px", &b_genA1Mu1_px, "genA1Mu1_px/F");
  
  m_ttree->Branch("genA0Mu0_py", &b_genA0Mu0_py, "genA0Mu0_py/F");
  m_ttree->Branch("genA0Mu1_py", &b_genA0Mu1_py, "genA0Mu1_py/F");
  m_ttree->Branch("genA1Mu0_py", &b_genA1Mu0_py, "genA1Mu0_py/F");
  m_ttree->Branch("genA1Mu1_py", &b_genA1Mu1_py, "genA1Mu1_py/F");
  
  m_ttree->Branch("genA0Mu0_pz", &b_genA0Mu0_pz, "genA0Mu0_pz/F");
  m_ttree->Branch("genA0Mu1_pz", &b_genA0Mu1_pz, "genA0Mu1_pz/F");
  m_ttree->Branch("genA1Mu0_pz", &b_genA1Mu0_pz, "genA1Mu0_pz/F");
  m_ttree->Branch("genA1Mu1_pz", &b_genA1Mu1_pz, "genA1Mu1_pz/F");
  
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
  
  m_ttree->Branch("genA0Mu_dEta", &b_genA0Mu_dEta, "genA0Mu_dEta/F");
  m_ttree->Branch("genA1Mu_dEta", &b_genA1Mu_dEta, "genA1Mu_dEta/F");
  m_ttree->Branch("genA0Mu_dPhi", &b_genA0Mu_dPhi, "genA0Mu_dPhi/F");
  m_ttree->Branch("genA1Mu_dPhi", &b_genA1Mu_dPhi, "genA1Mu_dPhi/F");
  m_ttree->Branch("genA0Mu_dR",   &b_genA0Mu_dR,   "genA0Mu_dR/F");
  m_ttree->Branch("genA1Mu_dR",   &b_genA1Mu_dR,   "genA1Mu_dR/F");
  
  // GEN Level Muons
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
  
  // GEN Level Selectors
  m_ttree->Branch("is4GenMu",    &b_is4GenMu,       "is4GenMu/O");
  
  m_ttree->Branch("is1GenMu17",  &b_is1GenMu17,     "is1GenMu17/O");
  m_ttree->Branch("is2GenMu8",   &b_is2GenMu8,      "is2GenMu8/O");
  m_ttree->Branch("is3GenMu8",   &b_is3GenMu8,      "is3GenMu8/O");
  m_ttree->Branch("is4GenMu8",   &b_is4GenMu8,      "is4GenMu8/O");
  
  m_ttree->Branch("isGenALxyOK", &b_isGenALxyOK, "isGenALxyOK/O");
  
  //****************************************************************************
  //                          RECO LEVEL BRANCHES                               
  //****************************************************************************
  
  // Reco Muons
  m_ttree->Branch("selMu0_px",  &b_selMu0_px,  "selMu0_px/F");
  m_ttree->Branch("selMu1_px",  &b_selMu1_px,  "selMu1_px/F");
  m_ttree->Branch("selMu2_px",  &b_selMu2_px,  "selMu2_px/F");
  m_ttree->Branch("selMu3_px",  &b_selMu3_px,  "selMu3_px/F");
  
  m_ttree->Branch("selMu0_py",  &b_selMu0_py,  "selMu0_py/F");
  m_ttree->Branch("selMu1_py",  &b_selMu1_py,  "selMu1_py/F");
  m_ttree->Branch("selMu2_py",  &b_selMu2_py,  "selMu2_py/F");
  m_ttree->Branch("selMu3_py",  &b_selMu3_py,  "selMu3_py/F");
  
  m_ttree->Branch("selMu0_pz",  &b_selMu0_pz,  "selMu0_pz/F");
  m_ttree->Branch("selMu1_pz",  &b_selMu1_pz,  "selMu1_pz/F");
  m_ttree->Branch("selMu2_pz",  &b_selMu2_pz,  "selMu2_pz/F");
  m_ttree->Branch("selMu3_pz",  &b_selMu3_pz,  "selMu3_pz/F");
  
  m_ttree->Branch("selMu0_eta", &b_selMu0_eta, "selMu0_eta/F");
  m_ttree->Branch("selMu1_eta", &b_selMu1_eta, "selMu1_eta/F");
  m_ttree->Branch("selMu2_eta", &b_selMu2_eta, "selMu2_eta/F");
  m_ttree->Branch("selMu3_eta", &b_selMu3_eta, "selMu3_eta/F");
  
  m_ttree->Branch("selMu0_phi", &b_selMu0_phi, "selMu0_phi/F");
  m_ttree->Branch("selMu1_phi", &b_selMu1_phi, "selMu1_phi/F");
  m_ttree->Branch("selMu2_phi", &b_selMu2_phi, "selMu2_phi/F");
  m_ttree->Branch("selMu3_phi", &b_selMu3_phi, "selMu3_phi/F");
  
  // RECO DiMuons
  m_ttree->Branch("diMuonC_FittedVtx_m",   &b_diMuonC_FittedVtx_m,   "diMuonC_FittedVtx_m/F");
  m_ttree->Branch("diMuonC_FittedVtx_px",  &b_diMuonC_FittedVtx_px,  "diMuonC_FittedVtx_px/F");
  m_ttree->Branch("diMuonC_FittedVtx_py",  &b_diMuonC_FittedVtx_py,  "diMuonC_FittedVtx_py/F");
  m_ttree->Branch("diMuonC_FittedVtx_pz",  &b_diMuonC_FittedVtx_pz,  "diMuonC_FittedVtx_pz/F");
  m_ttree->Branch("diMuonC_FittedVtx_eta", &b_diMuonC_FittedVtx_eta, "diMuonC_FittedVtx_eta/F");
  m_ttree->Branch("diMuonC_FittedVtx_phi", &b_diMuonC_FittedVtx_phi, "diMuonC_FittedVtx_phi/F");
  m_ttree->Branch("diMuonC_FittedVtx_vx",  &b_diMuonC_FittedVtx_vx,  "diMuonC_FittedVtx_vx/F");
  m_ttree->Branch("diMuonC_FittedVtx_vy",  &b_diMuonC_FittedVtx_vy,  "diMuonC_FittedVtx_vy/F");
  m_ttree->Branch("diMuonC_FittedVtx_vz",  &b_diMuonC_FittedVtx_vz,  "diMuonC_FittedVtx_vz/F");
  
  m_ttree->Branch("diMuonC_FittedVtx_Lxy", &b_diMuonC_FittedVtx_Lxy, "diMuonC_FittedVtx_Lxy/F");
  m_ttree->Branch("diMuonC_FittedVtx_L",   &b_diMuonC_FittedVtx_L,   "diMuonC_FittedVtx_L/F");
  m_ttree->Branch("diMuonC_FittedVtx_dz",  &b_diMuonC_FittedVtx_dz,  "diMuonC_FittedVtx_dz/F");
  
  m_ttree->Branch("diMuonF_FittedVtx_m",   &b_diMuonF_FittedVtx_m,   "diMuonF_FittedVtx_m/F");
  m_ttree->Branch("diMuonF_FittedVtx_px",  &b_diMuonF_FittedVtx_px,  "diMuonF_FittedVtx_px/F");
  m_ttree->Branch("diMuonF_FittedVtx_py",  &b_diMuonF_FittedVtx_py,  "diMuonF_FittedVtx_py/F");
  m_ttree->Branch("diMuonF_FittedVtx_pz",  &b_diMuonF_FittedVtx_pz,  "diMuonF_FittedVtx_pz/F");
  m_ttree->Branch("diMuonF_FittedVtx_eta", &b_diMuonF_FittedVtx_eta, "diMuonF_FittedVtx_eta/F");
  m_ttree->Branch("diMuonF_FittedVtx_phi", &b_diMuonF_FittedVtx_phi, "diMuonF_FittedVtx_phi/F");
  m_ttree->Branch("diMuonF_FittedVtx_vx",  &b_diMuonF_FittedVtx_vx,  "diMuonF_FittedVtx_vx/F");
  m_ttree->Branch("diMuonF_FittedVtx_vy",  &b_diMuonF_FittedVtx_vy,  "diMuonF_FittedVtx_vy/F");
  m_ttree->Branch("diMuonF_FittedVtx_vz",  &b_diMuonF_FittedVtx_vz,  "diMuonF_FittedVtx_vz/F");
  
  m_ttree->Branch("diMuonF_FittedVtx_Lxy", &b_diMuonF_FittedVtx_Lxy, "diMuonF_FittedVtx_Lxy/F");
  m_ttree->Branch("diMuonF_FittedVtx_L",   &b_diMuonF_FittedVtx_L,   "diMuonF_FittedVtx_L/F");
  m_ttree->Branch("diMuonF_FittedVtx_dz",  &b_diMuonF_FittedVtx_dz,  "diMuonF_FittedVtx_dz/F");
  
  m_ttree->Branch("diMuonC_ConsistentVtx_m",   &b_diMuonC_ConsistentVtx_m,   "diMuonC_ConsistentVtx_m/F");
  m_ttree->Branch("diMuonC_ConsistentVtx_px",  &b_diMuonC_ConsistentVtx_px,  "diMuonC_ConsistentVtx_px/F");
  m_ttree->Branch("diMuonC_ConsistentVtx_py",  &b_diMuonC_ConsistentVtx_py,  "diMuonC_ConsistentVtx_py/F");
  m_ttree->Branch("diMuonC_ConsistentVtx_pz",  &b_diMuonC_ConsistentVtx_pz,  "diMuonC_ConsistentVtx_pz/F");
  m_ttree->Branch("diMuonC_ConsistentVtx_eta", &b_diMuonC_ConsistentVtx_eta, "diMuonC_ConsistentVtx_eta/F");
  m_ttree->Branch("diMuonC_ConsistentVtx_phi", &b_diMuonC_ConsistentVtx_phi, "diMuonC_ConsistentVtx_phi/F");
  m_ttree->Branch("diMuonC_ConsistentVtx_vx",  &b_diMuonC_ConsistentVtx_vx,  "diMuonC_ConsistentVtx_vx/F");
  m_ttree->Branch("diMuonC_ConsistentVtx_vy",  &b_diMuonC_ConsistentVtx_vy,  "diMuonC_ConsistentVtx_vy/F");
  m_ttree->Branch("diMuonC_ConsistentVtx_vz",  &b_diMuonC_ConsistentVtx_vz,  "diMuonC_ConsistentVtx_vz/F");
  
  m_ttree->Branch("diMuonC_ConsistentVtx_Lxy", &b_diMuonC_ConsistentVtx_Lxy, "diMuonC_ConsistentVtx_Lxy/F");
  m_ttree->Branch("diMuonC_ConsistentVtx_L",   &b_diMuonC_ConsistentVtx_L,   "diMuonC_ConsistentVtx_L/F");
  m_ttree->Branch("diMuonC_ConsistentVtx_dz",  &b_diMuonC_ConsistentVtx_dz,  "diMuonC_ConsistentVtx_dz/F");
  
  m_ttree->Branch("diMuonF_ConsistentVtx_m",   &b_diMuonF_ConsistentVtx_m,   "diMuonF_ConsistentVtx_m/F");
  m_ttree->Branch("diMuonF_ConsistentVtx_px",  &b_diMuonF_ConsistentVtx_px,  "diMuonF_ConsistentVtx_px/F");
  m_ttree->Branch("diMuonF_ConsistentVtx_py",  &b_diMuonF_ConsistentVtx_py,  "diMuonF_ConsistentVtx_py/F");
  m_ttree->Branch("diMuonF_ConsistentVtx_pz",  &b_diMuonF_ConsistentVtx_pz,  "diMuonF_ConsistentVtx_pz/F");
  m_ttree->Branch("diMuonF_ConsistentVtx_eta", &b_diMuonF_ConsistentVtx_eta, "diMuonF_ConsistentVtx_eta/F");
  m_ttree->Branch("diMuonF_ConsistentVtx_phi", &b_diMuonF_ConsistentVtx_phi, "diMuonF_ConsistentVtx_phi/F");
  m_ttree->Branch("diMuonF_ConsistentVtx_vx",  &b_diMuonF_ConsistentVtx_vx,  "diMuonF_ConsistentVtx_vx/F");
  m_ttree->Branch("diMuonF_ConsistentVtx_vy",  &b_diMuonF_ConsistentVtx_vy,  "diMuonF_ConsistentVtx_vy/F");
  m_ttree->Branch("diMuonF_ConsistentVtx_vz",  &b_diMuonF_ConsistentVtx_vz,  "diMuonF_ConsistentVtx_vz/F");
  
  m_ttree->Branch("diMuonF_ConsistentVtx_Lxy", &b_diMuonF_ConsistentVtx_Lxy, "diMuonF_ConsistentVtx_Lxy/F");
  m_ttree->Branch("diMuonF_ConsistentVtx_L",   &b_diMuonF_ConsistentVtx_L,   "diMuonF_ConsistentVtx_L/F");
  m_ttree->Branch("diMuonF_ConsistentVtx_dz",  &b_diMuonF_ConsistentVtx_dz,  "diMuonF_ConsistentVtx_dz/F");
  
  m_ttree->Branch("diMuonC_IsoTk_FittedVtx", &b_diMuonC_IsoTk_FittedVtx, "diMuonC_IsoTk_FittedVtx/F");
  m_ttree->Branch("diMuonF_IsoTk_FittedVtx", &b_diMuonF_IsoTk_FittedVtx, "diMuonF_IsoTk_FittedVtx/F");
//  m_ttree->Branch("diMuonC_IsoPF_FittedVtx", &b_diMuonC_IsoPF_FittedVtx, "diMuonC_IsoPF_FittedVtx/F");
//  m_ttree->Branch("diMuonF_IsoPF_FittedVtx", &b_diMuonF_IsoPF_FittedVtx, "diMuonF_IsoPF_FittedVtx/F");
  
  m_ttree->Branch("diMuonC_IsoTk_ConsistentVtx", &b_diMuonC_IsoTk_ConsistentVtx, "diMuonC_IsoTk_ConsistentVtx/F");
  m_ttree->Branch("diMuonF_IsoTk_ConsistentVtx", &b_diMuonF_IsoTk_ConsistentVtx, "diMuonF_IsoTk_ConsistentVtx/F");
//  m_ttree->Branch("diMuonC_IsoPF_ConsistentVtx", &b_diMuonC_IsoPF_ConsistentVtx, "diMuonC_IsoPF_ConsistentVtx/F");
//  m_ttree->Branch("diMuonF_IsoPF_ConsistentVtx", &b_diMuonF_IsoPF_ConsistentVtx, "diMuonF_IsoPF_ConsistentVtx/F");

  m_ttree->Branch("diMuonC_m1_FittedVtx_hitpix", &b_diMuonC_m1_FittedVtx_hitpix, "diMuonC_m1_FittedVtx_hitpix/I");
  m_ttree->Branch("diMuonC_m2_FittedVtx_hitpix", &b_diMuonC_m2_FittedVtx_hitpix, "diMuonC_m2_FittedVtx_hitpix/I");
  m_ttree->Branch("diMuonF_m1_FittedVtx_hitpix", &b_diMuonF_m1_FittedVtx_hitpix, "diMuonF_m1_FittedVtx_hitpix/I");
  m_ttree->Branch("diMuonF_m2_FittedVtx_hitpix", &b_diMuonF_m2_FittedVtx_hitpix, "diMuonF_m2_FittedVtx_hitpix/I");

  
  // RECO Level Selectors
  m_ttree->Branch("is1SelMu17",                     &b_is1SelMu17,                     "is1SelMu17/O");
  m_ttree->Branch("is2SelMu8",                      &b_is2SelMu8,                      "is2SelMu8/O");
  m_ttree->Branch("is3SelMu8",                      &b_is3SelMu8,                      "is3SelMu8/O");
  m_ttree->Branch("is4SelMu8",                      &b_is4SelMu8,                      "is4SelMu8/O");
  
  m_ttree->Branch("is2MuJets",                      &b_is2MuJets,                      "is2MuJets/O");
  m_ttree->Branch("is2DiMuons",                     &b_is2DiMuons,                     "is2DiMuons/O");
  m_ttree->Branch("is2DiMuonsFittedVtxOK",          &b_is2DiMuonsFittedVtxOK,          "is2DiMuonsFittedVtxOK/O");
  m_ttree->Branch("is2DiMuonsConsistentVtxOK",      &b_is2DiMuonsConsistentVtxOK,      "is2DiMuonsConsistentVtxOK/O");
  m_ttree->Branch("is2DiMuonsDzOK_FittedVtx",       &b_is2DiMuonsDzOK_FittedVtx,       "is2DiMuonsDzOK_FittedVtx/O");
  m_ttree->Branch("is2DiMuonsDzOK_ConsistentVtx",   &b_is2DiMuonsDzOK_ConsistentVtx,   "is2DiMuonsDzOK_ConsistentVtx/O");
  m_ttree->Branch("isDiMuonHLTFired",               &b_isDiMuonHLTFired,               "isDiMuonHLTFired/O");
  m_ttree->Branch("is2DiMuonsMassOK_FittedVtx",     &b_is2DiMuonsMassOK_FittedVtx,     "is2DiMuonsMassOK_FittedVtx/O");
  m_ttree->Branch("is2DiMuonsMassOK_ConsistentVtx", &b_is2DiMuonsMassOK_ConsistentVtx, "is2DiMuonsMassOK_ConsistentVtx/O");
  m_ttree->Branch("is2DiMuonsIsoTkOK_FittedVtx",    &b_is2DiMuonsIsoTkOK_FittedVtx,    "is2DiMuonsIsoTkOK_FittedVtx/O");
  m_ttree->Branch("is2DiMuonsIsoTkOK_ConsistentVtx",&b_is2DiMuonsIsoTkOK_ConsistentVtx,"is2DiMuonsIsoTkOK_ConsistentVtx/O");
  m_ttree->Branch("isVertexOK",                     &b_isVertexOK,                     "isVertexOK/O");
  
  m_ttree->Branch("is2DiMuonsLxyOK_FittedVtx",      &b_is2DiMuonsLxyOK_FittedVtx,      "is2DiMuonsLxyOK_FittedVtx/O");
  m_ttree->Branch("is2DiMuonsLxyOK_ConsistentVtx",  &b_is2DiMuonsLxyOK_ConsistentVtx,  "is2DiMuonsLxyOK_ConsistentVtx/O");

  m_ttree->Branch("hltPaths",  &b_hltPaths);  
}

// ------------ method called once each job just after ending the event loop  ------------
void 
CutFlowAnalyzer::endJob() 
{
  std::cout << "END JOB" << std::endl;
  
  std:: cout << "Total number of events:          " << m_events << std::endl;
  std:: cout << "Total number of events with 4mu: " << m_events4GenMu << " fraction: " <<  m_events4GenMu/m_events << std::endl;

  if (m_fillGenLevel){  
    std:: cout << "********** GEN **********" << std::endl;
    std:: cout << "Selection              " << "nEv"         << " \t RelEff"                                       << " \t Eff" << std::endl;
    std:: cout << "pT1>17 |eta1|<0.9:       " << m_events1GenMu17 << " \t" << (float)m_events1GenMu17/(float)m_events << " \t" << (float)m_events1GenMu17/(float)m_events << std::endl;
    std:: cout << "pT2>8  |eta2|<2.4:       " << m_events2GenMu8  << " \t" << (float)m_events2GenMu8/(float)m_events1GenMu17  << " \t" << (float)m_events2GenMu8/(float)m_events << std::endl;
    std:: cout << "pT3>8  |eta2|<2.4:       " << m_events3GenMu8  << " \t" << (float)m_events3GenMu8/(float)m_events2GenMu8   << " \t" << (float)m_events3GenMu8/(float)m_events << std::endl;
    std:: cout << "pT4>8  |eta2|<2.4:       " << m_events4GenMu8  << " \t" << (float)m_events4GenMu8/(float)m_events3GenMu8   << " \t" << (float)m_events4GenMu8/(float)m_events << std::endl;
    std:: cout << "Basic MC Acceptance:     " << (float)m_events4GenMu8/(float)m_events << std::endl;
  }
  std:: cout << "********** RECO **********" << std::endl;
  std:: cout << "Selection                " << "nEv"                   << " \t RelEff"                                                         << " \t Eff" << std::endl;
  std:: cout << "m_events1SelMu17:        " << m_events1SelMu17        << " \t" << (float)m_events1SelMu17/(float)m_events                << " \t" << (float)m_events1SelMu17/(float)m_events        << std::endl;
  std:: cout << "m_events2SelMu8:         " << m_events2SelMu8         << " \t" << (float)m_events2SelMu8/(float)m_events1SelMu17              << " \t" << (float)m_events2SelMu8/(float)m_events         << std::endl;
  std:: cout << "m_events3SelMu8:         " << m_events3SelMu8         << " \t" << (float)m_events3SelMu8/(float)m_events2SelMu8               << " \t" << (float)m_events3SelMu8/(float)m_events         << std::endl;
  std:: cout << "m_events4SelMu8:         " << m_events4SelMu8         << " \t" << (float)m_events4SelMu8/(float)m_events3SelMu8               << " \t" << (float)m_events4SelMu8/(float)m_events         << std::endl;

  std:: cout << "Basic Acceptance:        " << (float)m_events4SelMu8/(float)m_events << std::endl;
  if (m_fillGenLevel) std:: cout << "Basic MC Accept. a_gen:  " << (float)m_events4GenMu8/(float)m_events << std::endl; 

  std:: cout << "m_events2MuJets:         " << m_events2MuJets         << " \t" << (float)m_events2MuJets/(float)m_events4SelMu8               << " \t" << (float)m_events2MuJets/(float)m_events         << std::endl;
  std:: cout << "m_events2DiMuons:        " << m_events2DiMuons        << " \t" << (float)m_events2DiMuons/(float)m_events2MuJets              << " \t" << (float)m_events2DiMuons/(float)m_events        << std::endl;
  
  std:: cout << " *** FITTED VERTEXES *** " << std::endl;
  std:: cout << "m_events2DiMuonsDzOK:     " << m_events2DiMuonsDzOK_FittedVtx     << " \t" << (float)m_events2DiMuonsDzOK_FittedVtx/(float)m_events2DiMuons          << " \t" << (float)m_events2DiMuonsDzOK_FittedVtx/(float)m_events     << std::endl;
  std:: cout << "m_eventsDiMuonHLTFired: " << m_eventsDiMuonHLTFired_FittedVtx << " \t" << (float)m_eventsDiMuonHLTFired_FittedVtx/(float)m_events2DiMuonsDzOK_FittedVtx   << " \t" << (float)m_eventsDiMuonHLTFired_FittedVtx/(float)m_events << std::endl;
  std:: cout << "m_events2DiMuonsMassOK:   " << m_events2DiMuonsMassOK_FittedVtx   << " \t" << (float)m_events2DiMuonsMassOK_FittedVtx/(float)m_eventsDiMuonHLTFired_FittedVtx << " \t" << (float)m_events2DiMuonsMassOK_FittedVtx/(float)m_events   << std::endl;
  std:: cout << "m_events2DiMuonsIsoTkOK:    " << m_events2DiMuonsIsoTkOK_FittedVtx    << " \t" << (float)m_events2DiMuonsIsoTkOK_FittedVtx/(float)m_events2DiMuonsMassOK_FittedVtx    << " \t" << (float)m_events2DiMuonsIsoTkOK_FittedVtx/(float)m_events    << std::endl;
  std:: cout << "m_eventsVertexOK:        " << m_eventsVertexOK_FittedVtx        << " \t" << (float)m_eventsVertexOK_FittedVtx/(float)m_events2DiMuonsIsoTkOK_FittedVtx         << " \t" << (float)m_eventsVertexOK_FittedVtx/(float)m_events        << std::endl;
  
  std:: cout << "Further selections:      " << (float)m_eventsVertexOK_FittedVtx/(float)m_events4SelMu8 << std::endl;
  float e_full = (float)m_eventsVertexOK_FittedVtx/(float)m_events;
  float de_full = sqrt( e_full*( 1.0 - e_full )/(float)m_events );
  std:: cout << "Full sel eff e_full:     " << e_full << " +- " << de_full << std::endl;
  if (m_fillGenLevel) std:: cout << "e_full/a_gen:            " << (float)m_eventsVertexOK_FittedVtx/(float)m_events4GenMu8 << std::endl;
  
  std:: cout << " *** CONSISTENT VERTEXES *** " << std::endl;
  std:: cout << "m_events2DiMuonsDzOK:     " << m_events2DiMuonsDzOK_ConsistentVtx     << " \t" << (float)m_events2DiMuonsDzOK_ConsistentVtx/(float)m_events2DiMuons          << " \t" << (float)m_events2DiMuonsDzOK_ConsistentVtx/(float)m_events     << std::endl;
  std:: cout << "m_eventsDiMuonHLTFired: " << m_eventsDiMuonHLTFired_ConsistentVtx << " \t" << (float)m_eventsDiMuonHLTFired_ConsistentVtx/(float)m_events2DiMuonsDzOK_ConsistentVtx   << " \t" << (float)m_eventsDiMuonHLTFired_ConsistentVtx/(float)m_events << std::endl;
  std:: cout << "m_events2DiMuonsMassOK:   " << m_events2DiMuonsMassOK_ConsistentVtx   << " \t" << (float)m_events2DiMuonsMassOK_ConsistentVtx/(float)m_eventsDiMuonHLTFired_ConsistentVtx << " \t" << (float)m_events2DiMuonsMassOK_ConsistentVtx/(float)m_events   << std::endl;
  std:: cout << "m_events2DiMuonsIsoTkOK:    " << m_events2DiMuonsIsoTkOK_ConsistentVtx    << " \t" << (float)m_events2DiMuonsIsoTkOK_ConsistentVtx/(float)m_events2DiMuonsMassOK_ConsistentVtx    << " \t" << (float)m_events2DiMuonsIsoTkOK_ConsistentVtx/(float)m_events    << std::endl;
  std:: cout << "m_eventsVertexOK:        " << m_eventsVertexOK_ConsistentVtx        << " \t" << (float)m_eventsVertexOK_ConsistentVtx/(float)m_events2DiMuonsIsoTkOK_ConsistentVtx         << " \t" << (float)m_eventsVertexOK_ConsistentVtx/(float)m_events        << std::endl;
  
  std:: cout << "Further selections:      " << (float)m_eventsVertexOK_ConsistentVtx/(float)m_events4SelMu8 << std::endl;
  e_full = (float)m_eventsVertexOK_ConsistentVtx/(float)m_events;
  de_full = sqrt( e_full*( 1.0 - e_full )/(float)m_events );
  std:: cout << "Full sel eff e_full:     " << e_full << " +- " << de_full << std::endl;
  if (m_fillGenLevel) std:: cout << "e_full/a_gen:            " << (float)m_eventsVertexOK_ConsistentVtx/(float)m_events4GenMu8 << std::endl;
  
  std:: cout << " *** FITTED VERTEXES *** " << std::endl;
  std::cout << m_events << std::endl;
  std::cout << m_events1GenMu17                  << std::endl;
  std::cout << m_events2GenMu8                   << std::endl;
  std::cout << m_events3GenMu8                   << std::endl;
  std::cout << m_events4GenMu8                   << std::endl;
  std::cout << m_events1SelMu17                  << std::endl;
  std::cout << m_events2SelMu8                   << std::endl;
  std::cout << m_events3SelMu8                   << std::endl;
  std::cout << m_events4SelMu8                   << std::endl;
  std::cout << m_events2MuJets                   << std::endl;
  std::cout << m_events2DiMuons                  << std::endl;
  std::cout << m_events2DiMuonsDzOK_FittedVtx    << std::endl;
  std::cout << m_eventsDiMuonHLTFired_FittedVtx  << std::endl;
  std::cout << m_events2DiMuonsMassOK_FittedVtx  << std::endl;
  std::cout << m_events2DiMuonsIsoTkOK_FittedVtx << std::endl;
  std::cout << m_eventsVertexOK_FittedVtx        << std::endl;
  
  std:: cout << " *** CONSISTENT VERTEXES *** " << std::endl;
  std::cout << m_events << std::endl;
  std::cout << m_events1GenMu17                      << std::endl;
  std::cout << m_events2GenMu8                       << std::endl;
  std::cout << m_events3GenMu8                       << std::endl;
  std::cout << m_events4GenMu8                       << std::endl;
  std::cout << m_events1SelMu17                      << std::endl;
  std::cout << m_events2SelMu8                       << std::endl;
  std::cout << m_events3SelMu8                       << std::endl;
  std::cout << m_events4SelMu8                       << std::endl;
  std::cout << m_events2MuJets                       << std::endl;
  std::cout << m_events2DiMuons                      << std::endl;
  std::cout << m_events2DiMuonsDzOK_ConsistentVtx    << std::endl;
  std::cout << m_eventsDiMuonHLTFired_ConsistentVtx  << std::endl;
  std::cout << m_events2DiMuonsMassOK_ConsistentVtx  << std::endl;
  std::cout << m_events2DiMuonsIsoTkOK_ConsistentVtx << std::endl;
  std::cout << m_eventsVertexOK_ConsistentVtx        << std::endl;
  
  
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
