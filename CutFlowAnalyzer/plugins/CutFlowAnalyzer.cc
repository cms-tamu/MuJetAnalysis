// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Candidate/interface/CandMatchMap.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/TriggerEvent.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "PhysicsTools/RecoUtils/interface/CheckHitPattern.h"
#include "RecoTracker/MeasurementDet/interface/MeasurementTrackerEvent.h"
#include "TrackingTools/PatternTools/interface/Trajectory.h"

#include "MuJetAnalysis/DataFormats/interface/MultiMuon.h"
//#include "MuJetAnalysis/AnalysisTools/interface/ConsistentVertexesCalculator.h"
//#include "MuJetAnalysis/AnalysisTools/interface/DisplacedVertexFinder.h"
#include "MuJetAnalysis/AnalysisTools/interface/Helpers.h"

// user include files
#include "TTree.h"
#include "TRandom3.h"
#include "TMath.h"
#include "TVector2.h"
#include "TLorentzVector.h"

//******************************************************************************
//                           Class declaration
//******************************************************************************

const unsigned int MAX_MUONS = 4;

class CutFlowAnalyzer : public edm::EDAnalyzer
{
public:
  explicit CutFlowAnalyzer(const edm::ParameterSet&);
  ~CutFlowAnalyzer();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  void FillTrigInfo( TH1F *h1, const edm::TriggerNames&, std::map<int,std::string> nameAndNumb );
  TH1F* triggerComposition;
  TH1F* triggerComposition_bb;

private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

  bool wasRecoMuonTriggerMatched(const pat::Muon* mu, const std::string& name, const float pt);

  edm::EDGetTokenT<MeasurementTrackerEvent> measurementTrkToken_;

  //****************************************************************************
  //                          THRESHOLDS
  //****************************************************************************

  Float_t m_threshold_Mu17_pT;
  Float_t m_threshold_Mu17_eta;
  Float_t m_threshold_Mu8_pT;
  Float_t m_threshold_Mu8_eta;

  Float_t m_threshold_DiMuons_Iso_dR;
  Float_t m_threshold_DiMuons_Iso_dz;
  Float_t m_threshold_DiMuons_Iso_pT;

  //****************************************************************************
  //          EVENT LEVEL VARIABLES, COUNTERS, BRANCHES AND SELECTORS
  //****************************************************************************

  Int_t   m_debug;         // Debug level
  TTree * m_ttree;         // Store variables in branches of this tree for later access
  TTree * m_ttree_orphan;  // Store variables in branches of this tree for later access
  Int_t   m_events;        // Counter: number of analyzed events

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

  std::vector<std::string> signalHltPaths_;
  std::vector<std::string> b_hltPaths;
  bool histo_name;
  std::map<int,std::string> NameAndNumb;
  //****************************************************************************
  //          RECO LEVEL VARIABLES, BRANCHES, COUNTERS AND SELECTORS
  //****************************************************************************

  // Labels to access
  edm::EDGetTokenT<pat::MuonCollection> m_muons;        // reconstructed muons
  edm::EDGetTokenT<pat::MultiMuonCollection> m_muJets;       // muon jets built from reconstructed muons
  edm::EDGetTokenT<reco::BeamSpot> m_beamSpot;
  edm::EDGetTokenT<pat::MuonCollection> m_muJetOrphans; // muon orphan, not found in any group
  edm::EDGetTokenT<reco::TrackCollection> m_tracks;
  edm::EDGetTokenT<reco::GenParticleCollection> m_genParticles;
  edm::EDGetTokenT<edm::TriggerResults> m_trigRes;
  edm::EDGetTokenT<pat::TriggerEvent> m_triggerEvent;
  edm::EDGetTokenT<reco::TrackCollection> m_trackRef;
  edm::EDGetTokenT< std::vector<Trajectory> > m_traj;
  edm::EDGetTokenT<reco::VertexCollection> m_primaryVertices;
  edm::EDGetTokenT<std::vector<pat::Jet> > m_PATJet;

  //Int_t         m_nThrowsConsistentVertexesCalculator;
  Int_t         m_barrelPixelLayer;
  Int_t         m_endcapPixelLayer;

  unsigned int  m_randomSeed;
  TRandom3      m_trandom3;

  // bb Estimation
  Float_t b_massC;
  Float_t b_massF;
  Float_t b_isoC_1mm;
  Float_t b_isoF_1mm;

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
  Bool_t b_is2DiMuonsFittedVtxOK_KF;
  Bool_t b_is2DiMuonsFittedVtxOK_VS;
  //Bool_t b_is2DiMuonsConsistentVtxOK;

  //BAM: added for vertex finding sanity checks
  Int_t hitsBeforeVertex_diMuonC_FittedVTX;
  Int_t hitsBeforeVertex_diMuonF_FittedVTX;
//  Int_t hitsBeforeVertex_diMuonC_ConsistentVTX;
  //Int_t hitsBeforeVertex_diMuonF_ConsistentVTX;

  Int_t missingHitsAfterVertex_diMuonC_FittedVTX;
  Int_t missingHitsAfterVertex_diMuonF_FittedVTX;
//  Int_t missingHitsAfterVertex_diMuonC_ConsistentVTX;
  //Int_t missingHitsAfterVertex_diMuonF_ConsistentVTX;

  Bool_t b_isDiMuonHLTFired;

  Bool_t b_is2DiMuonsMassOK_FittedVtx;

  //Bool_t b_is2DiMuonsMassOK_ConsistentVtx;

  Bool_t b_isVertexOK;

  Float_t b_Mass4Mu;

  // Reco branches in ROOT tree (they all start with b_)
  Int_t b_nRecoMu;

  Float_t b_selMu_px[MAX_MUONS];
  Float_t b_selMu_py[MAX_MUONS];
  Float_t b_selMu_pz[MAX_MUONS];
  Float_t b_selMu_pT[MAX_MUONS];
  Float_t b_selMu_eta[MAX_MUONS];
  Float_t b_selMu_phi[MAX_MUONS];
  Bool_t b_selMu_trigHLT16[MAX_MUONS];
  Bool_t b_selMu_trigHLT6[MAX_MUONS];

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

  Float_t b_selMu0_pT;
  Float_t b_selMu1_pT;
  Float_t b_selMu2_pT;
  Float_t b_selMu3_pT;

  Bool_t b_selMu0_trigHLT16;
  Bool_t b_selMu1_trigHLT16;
  Bool_t b_selMu2_trigHLT16;
  Bool_t b_selMu3_trigHLT16;

  Bool_t b_selMu0_trigHLT6;
  Bool_t b_selMu1_trigHLT6;
  Bool_t b_selMu2_trigHLT6;
  Bool_t b_selMu3_trigHLT6;

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

  Int_t b_diMuonC_m1_FittedVtx_hitpix_l2inc;
  Int_t b_diMuonC_m2_FittedVtx_hitpix_l2inc;
  Int_t b_diMuonF_m1_FittedVtx_hitpix_l2inc;
  Int_t b_diMuonF_m2_FittedVtx_hitpix_l2inc;

  Int_t b_diMuonC_m1_FittedVtx_hitpix_l3inc;
  Int_t b_diMuonC_m2_FittedVtx_hitpix_l3inc;
  Int_t b_diMuonF_m1_FittedVtx_hitpix_l3inc;
  Int_t b_diMuonF_m2_FittedVtx_hitpix_l3inc;

  Int_t b_diMuonC_m1_FittedVtx_hitpix_Phase1;
  Int_t b_diMuonC_m2_FittedVtx_hitpix_Phase1;
  Int_t b_diMuonF_m1_FittedVtx_hitpix_Phase1;
  Int_t b_diMuonF_m2_FittedVtx_hitpix_Phase1;

/*
  Int_t b_pixelhitfailure_C;
  Int_t b_pixelhitfailure_F;

  Int_t b_diMuonC_m1_FittedVtx_HBV;
  Int_t b_diMuonC_m2_FittedVtx_HBV;
  Int_t b_diMuonF_m1_FittedVtx_HBV;
  Int_t b_diMuonF_m2_FittedVtx_HBV;

  Int_t b_diMuonC_m1_FittedVtx_MHAV;
  Int_t b_diMuonC_m2_FittedVtx_MHAV;
  Int_t b_diMuonF_m1_FittedVtx_MHAV;
  Int_t b_diMuonF_m2_FittedVtx_MHAV;
  */

  Float_t b_diMuonC_FittedVtx_Lxy;
  Float_t b_diMuonC_FittedVtx_Lxy_rclstvtx;
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
  Float_t b_diMuonF_FittedVtx_Lxy_rclstvtx; // respect to closest vertex
  Float_t b_diMuonF_FittedVtx_L;
  Float_t b_diMuonF_FittedVtx_dz;
/*
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
*/
  Float_t b_diMuons_dz_FittedVtx;
  //Float_t b_diMuons_dz_ConsistentVtx;

  Float_t b_diMuonC_IsoTk_FittedVtx;
  Float_t b_diMuonF_IsoTk_FittedVtx;
  //Float_t b_diMuonC_IsoTk_ConsistentVtx;
  //Float_t b_diMuonF_IsoTk_ConsistentVtx;

  //bool runDisplacedVtxFinder_;
  bool skimOutput_; //fill only events with 2 good dimuons

  //PixelHitRecovery
  Int_t b_NPATJet;
  Float_t b_PAT_jet_pt[100];
  Float_t b_PAT_jet_eta[100];
  Float_t b_PAT_jet_phi[100];
  Float_t b_PAT_jet_en[100];
  Float_t b_PAT_jet_Btag1[100];
  Float_t b_PAT_jet_Btag2[100];
  Float_t b_PAT_jet_Btag3[100];

  Int_t b_ntracks;

  Float_t b_track_pt[1000];
  Float_t b_track_charge[1000];
  Float_t b_track_qoverp[1000];
  Float_t b_track_theta[1000];
  Float_t b_track_phi[1000];
  Float_t b_track_dxy[1000];
  Float_t b_track_dz[1000];

  Float_t b_track_errpt[1000];
  Float_t b_track_errcharge[1000];
  Float_t b_track_errqoverp[1000];
  Float_t b_track_errtheta[1000];
  Float_t b_track_errphi[1000];
  Float_t b_track_errdxy[1000];
  Float_t b_track_errdz[1000];

  Int_t b_match_mu1track_muJetC;
  Int_t b_match_mu2track_muJetC;
  Int_t b_match_mu1track_muJetF;
  Int_t b_match_mu2track_muJetF;

  Float_t mtrack_pt[10];
  Float_t mtrack_charge[10];
  Float_t mtrack_qoverp[10];
  Float_t mtrack_theta[10];
  Float_t mtrack_phi[10];
  Float_t mtrack_dxy[10];
  Float_t mtrack_dz[10];

  Float_t mtrack_errpt[10];
  Float_t mtrack_errcharge[10];
  Float_t mtrack_errqoverp[10];
  Float_t mtrack_errtheta[10];
  Float_t mtrack_errphi[10];
  Float_t mtrack_errdxy[10];
  Float_t mtrack_errdz[10];

  Float_t muJetC_muon1_track_diffcharge[1000];
  Float_t muJetC_muon1_track_diffpt[1000];
  Float_t muJetC_muon1_track_diffqoverp[1000];
  Float_t muJetC_muon1_track_difftheta[1000];
  Float_t muJetC_muon1_track_diffphi[1000];
  Float_t muJetC_muon1_track_diffdxy[1000];
  Float_t muJetC_muon1_track_diffdz[1000];

  Float_t muJetC_muon1_track_diffchi2[1000];
  Float_t muJetC_muon1_track_diffchi2theta[1000];
  Float_t muJetC_muon1_track_diffchi2qoverpt[1000];
  Float_t muJetC_muon1_track_diffchi2phi[1000];
  Float_t muJetC_muon1_track_diffchi2dxy[1000];
  Float_t muJetC_muon1_track_diffchi2dz[1000];


  Float_t muJetC_muon1_track_mincharge;
  Float_t muJetC_muon1_track_minqoverpt;
  Float_t muJetC_muon1_track_mintheta;
  Float_t muJetC_muon1_track_minphi;
  Float_t muJetC_muon1_track_mindxy;
  Float_t muJetC_muon1_track_mindz;

  Float_t muJetC_muon1_track_minchi2;
  Float_t muJetC_muon2_track_minchi2;
  Float_t muJetF_muon1_track_minchi2;
  Float_t muJetF_muon2_track_minchi2;


  Float_t muJetC_muon1_track_minchi2theta;
  Float_t muJetC_muon1_track_minchi2qoverpt;
  Float_t muJetC_muon1_track_minchi2phi;
  Float_t muJetC_muon1_track_minchi2dxy;
  Float_t muJetC_muon1_track_minchi2dz;


  Float_t muJetC_muon2_track_diffcharge[1000];
  Float_t muJetC_muon2_track_diffpt[1000];
  Float_t muJetC_muon2_track_diffqoverp[1000];
  Float_t muJetC_muon2_track_difftheta[1000];
  Float_t muJetC_muon2_track_diffphi[1000];
  Float_t muJetC_muon2_track_diffdxy[1000];
  Float_t muJetC_muon2_track_diffdz[1000];

  Float_t b_mutrack_pT_mu1JetC;
  Float_t b_mutrack_pT_mu2JetC;
  Float_t b_mutrack_pT_mu1JetF;
  Float_t b_mutrack_pT_mu2JetF;

  Float_t b_mutrack_eta_mu1JetC;
  Float_t b_mutrack_eta_mu2JetC;
  Float_t b_mutrack_eta_mu1JetF;
  Float_t b_mutrack_eta_mu2JetF;

  Float_t b_mutrack_phi_mu1JetC;
  Float_t b_mutrack_phi_mu2JetC;
  Float_t b_mutrack_phi_mu1JetF;
  Float_t b_mutrack_phi_mu2JetF;

  Float_t b_mutrack_charge_mu1JetC;
  Float_t b_mutrack_charge_mu2JetC;
  Float_t b_mutrack_charge_mu1JetF;
  Float_t b_mutrack_charge_mu2JetF;

  Int_t b_innerlayers_mu1_muJetC;
  Int_t b_innerlayers_mu2_muJetC;
  Int_t b_innerlayers_mu1_muJetF;
  Int_t b_innerlayers_mu2_muJetF;

  Int_t b_compdet_mu1_muJetC[10];
  Int_t b_compdet_mu2_muJetC[10];
  Int_t b_compdet_mu1_muJetF[10];
  Int_t b_compdet_mu2_muJetF[10];

  Int_t b_numhit_mu1_muJetC[100];
  Int_t b_numhit_mu2_muJetC[100];
  Int_t b_numhit_mu1_muJetF[100];
  Int_t b_numhit_mu2_muJetF[100];

  Int_t b_PXBID_mu1muJetC[10][10];
  Int_t b_PXFID_mu1muJetC[10][10];
  Int_t b_PXBID_mu2muJetC[10][10];
  Int_t b_PXFID_mu2muJetC[10][10];

  Int_t b_PXBID_mu1muJetF[10][10];
  Int_t b_PXFID_mu1muJetF[10][10];
  Int_t b_PXBID_mu2muJetF[10][10];
  Int_t b_PXFID_mu2muJetF[10][10];

  Float_t b_mj1m0posx[10][10];
  Float_t b_mj1m0posy[10][10];
  Float_t b_mj1m0posx_err[10][10];
  Float_t b_mj1m0posy_err[10][10];
  Float_t b_mj1m1posx[10][10];
  Float_t b_mj1m1posy[10][10];
  Float_t b_mj1m1posx_err[10][10];
  Float_t b_mj1m1posy_err[10][10];

  Float_t  b_mj2m0posx[10][10];
  Float_t  b_mj2m0posy[10][10];
  Float_t  b_mj2m0posx_err[10][10];
  Float_t  b_mj2m0posy_err[10][10];
  Float_t  b_mj2m1posx[10][10];
  Float_t  b_mj2m1posy[10][10];
  Float_t  b_mj2m1posx_err[10][10];
  Float_t  b_mj2m1posy_err[10][10];

  Float_t b_pixelhit_mu1_muJetC_posx[10][100];
  Float_t b_pixelhit_mu1_muJetC_posy[10][100];
  Float_t b_pixelhit_mu1_muJetC_errposx[10][100];
  Float_t b_pixelhit_mu1_muJetC_errposy[10][100];
  Float_t b_pixelhit_mu2_muJetC_posx[10][100];
  Float_t b_pixelhit_mu2_muJetC_posy[10][100];
  Float_t b_pixelhit_mu2_muJetC_errposx[10][100];
  Float_t b_pixelhit_mu2_muJetC_errposy[10][100];

  Float_t b_pixelhit_mu1_muJetF_posx[10][100];
  Float_t b_pixelhit_mu1_muJetF_posy[10][100];
  Float_t b_pixelhit_mu1_muJetF_errposx[10][100];
  Float_t b_pixelhit_mu1_muJetF_errposy[10][100];
  Float_t b_pixelhit_mu2_muJetF_posx[10][100];
  Float_t b_pixelhit_mu2_muJetF_posy[10][100];
  Float_t b_pixelhit_mu2_muJetF_errposx[10][100];
  Float_t b_pixelhit_mu2_muJetF_errposy[10][100];

  //BB estimation
  Bool_t runBBestimation_;
  Float_t m_orphan_dimu_mass;
  Float_t m_orphan_mass;
  Int_t m_dimuorphan_containstrig;
  Int_t m_dimuorphan_containstrig2;
  Float_t m_orphan_z;
  Float_t m_orphan_dimu_z;
  Float_t m_orphan_isoTk;
  Float_t m_orphan_dimu_isoTk;
  Bool_t  m_orphan_passOffLineSel;
  Bool_t  m_orphan_passOffLineSelPt;
  Bool_t  m_orphan_passOffLineSelPtEta;
  Bool_t  m_orphan_passOffLineSelPt1788;
  Bool_t  m_orphan_AllTrackerMu;
  Float_t  m_orphan_PtOrph;
  Float_t  m_orphan_EtaOrph;
  Float_t  m_orphan_PhiOrph;
  Float_t  m_orphan_PtMu0;
  Float_t  m_orphan_EtaMu0;
  Float_t  m_orphan_PhiMu0;
  Float_t  m_orphan_PtMu1;
  Float_t  m_orphan_EtaMu1;
  Float_t  m_orphan_PhiMu1;
  Float_t  m_orphan_PtMu01;
  Float_t  m_orphan_EtaMu01;
  Float_t  m_orphan_PhiMu01;
  Float_t  m_orphan_DRdiMuOrph;
};

CutFlowAnalyzer::CutFlowAnalyzer(const edm::ParameterSet& iConfig)
{
  //****************************************************************************
  //                          SET THRESHOLDS
  //****************************************************************************

  m_threshold_Mu17_pT  = 17.0; // min pT in GeV      //These values are set by trigger efficiencies and detector geometry so may be left hard-coded
  m_threshold_Mu17_eta =  0.9; // max eta in Barrel  //These values are set by trigger efficiencies and detector geometry so may be left hard-coded
  m_threshold_Mu8_pT   =  8.0; // min pT in GeV      //These values are set by trigger efficiencies and detector geometry so may be left hard-coded
  m_threshold_Mu8_eta  =  2.4; // max eta in Endcaps //These values are set by trigger efficiencies and detector geometry so may be left hard-coded


  m_threshold_DiMuons_Iso_dR = 0.4; // Isolation cone              //There is no real way to avoid hard-coding this value
  m_threshold_DiMuons_Iso_dz = 0.1; // Track displacement [cm]     //There is no real way to avoid hard-coding this value
  m_threshold_DiMuons_Iso_pT = 0.5; // Track pT [GeV]              //There is no real way to avoid hard-coding this value

  //****************************************************************************
  //               SET EVENT LEVEL VARIABLES AND COUNTERS
  //****************************************************************************

  m_debug = iConfig.getParameter<int>("analyzerDebug");
  m_ttree  = NULL;
  m_ttree_orphan = NULL;
  m_events = 0;

  //****************************************************************************
  //                 SET GEN LEVEL VARIABLES AND COUNTERS
  //****************************************************************************

  m_events4GenMu   = 0;
  m_events1GenMu17 = 0;
  m_events2GenMu8  = 0;
  m_events3GenMu8  = 0;
  m_events4GenMu8  = 0;

  //****************************************************************************
  //                 SET HLT LEVEL VARIABLES AND COUNTERS
  //****************************************************************************

  signalHltPaths_ = iConfig.getParameter<std::vector<std::string> >("signalHltPaths");

  //****************************************************************************
  //                 SET RECO LEVEL VARIABLES AND COUNTERS
  //****************************************************************************

  m_muons           = consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("muons"));
  m_muJets          = consumes<pat::MultiMuonCollection>(iConfig.getParameter<edm::InputTag>("muJets"));
  m_beamSpot        = consumes<reco::BeamSpot>(iConfig.getParameter<edm::InputTag>("beamSpot"));
  m_muJetOrphans    = consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("muJetOrphans"));
  m_tracks          = consumes<reco::TrackCollection>(iConfig.getParameter<edm::InputTag>("tracks"));
  m_genParticles    = consumes<reco::GenParticleCollection>(iConfig.getParameter<edm::InputTag>("genParticles"));
  m_trigRes         = consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("TriggerResults"));
  m_triggerEvent    = consumes<pat::TriggerEvent>(iConfig.getParameter<edm::InputTag>("triggerEvent"));
  //m_trackRef        = consumes<reco::TrackCollection>(iConfig.getParameter<edm::InputTag>("TrackRefitter"));
  //m_traj            = consumes< std::vector<Trajectory> >(iConfig.getParameter<edm::InputTag>("Traj"));
  m_primaryVertices = consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("primaryVertices"));
  m_PATJet          = consumes<std::vector<pat::Jet> >(iConfig.getParameter<edm::InputTag>("PATJet"));
  //m_nThrowsConsistentVertexesCalculator = iConfig.getParameter<int>("nThrowsConsistentVertexesCalculator");
  m_barrelPixelLayer = iConfig.getParameter<int>("barrelPixelLayer");
  m_endcapPixelLayer = iConfig.getParameter<int>("endcapPixelLayer");
  runBBestimation_ = iConfig.getParameter<bool>("runBBestimation");
  skimOutput_ = iConfig.getParameter<bool>("skimOutput");

  m_randomSeed = 1234;
  m_trandom3   = TRandom3(m_randomSeed); // Random generator

  m_events1SelMu17                     = 0;
  m_events2SelMu8                      = 0;
  m_events3SelMu8                      = 0;
  m_events4SelMu8                      = 0;
  m_events2MuJets                      = 0;
  m_events2DiMuons                     = 0;
  //Fill trigger histo
  histo_name = true;
  NameAndNumb.clear();

  //runDisplacedVtxFinder_ = iConfig.getParameter<bool>("runDisplacedVtxFinder");
  //measurementTrkToken_ = consumes<MeasurementTrackerEvent>(iConfig.getParameter<edm::InputTag>("MeasurementTrackerEvent"));
}


CutFlowAnalyzer::~CutFlowAnalyzer()
{
  if (m_events==0) return;
  triggerComposition->Write();
  triggerComposition_bb->Write();
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
  m_fillGenLevel = !iEvent.eventAuxiliary().isRealData();

  using namespace edm;
  double eq = 0.000001; // small number used below to compare variables

  b_diMuonC_m1_FittedVtx_hitpix=-1000;
  b_diMuonC_m2_FittedVtx_hitpix=-1000;
  b_diMuonF_m1_FittedVtx_hitpix=-1000;
  b_diMuonF_m2_FittedVtx_hitpix=-1000;

  b_diMuonC_m1_FittedVtx_hitpix_l2inc=-1000;
  b_diMuonC_m2_FittedVtx_hitpix_l2inc=-1000;
  b_diMuonF_m1_FittedVtx_hitpix_l2inc=-1000;
  b_diMuonF_m2_FittedVtx_hitpix_l2inc=-1000;

  b_diMuonC_m1_FittedVtx_hitpix_l3inc=-1000;
  b_diMuonC_m2_FittedVtx_hitpix_l3inc=-1000;
  b_diMuonF_m1_FittedVtx_hitpix_l3inc=-1000;
  b_diMuonF_m2_FittedVtx_hitpix_l3inc=-1000;

  b_diMuonC_m1_FittedVtx_hitpix_Phase1=-1000;
  b_diMuonC_m2_FittedVtx_hitpix_Phase1=-1000;
  b_diMuonF_m1_FittedVtx_hitpix_Phase1=-1000;
  b_diMuonF_m2_FittedVtx_hitpix_Phase1=-1000;

/*
  b_diMuonC_m1_FittedVtx_HBV = -1000;
  b_diMuonC_m2_FittedVtx_HBV = -1000;
  b_diMuonF_m1_FittedVtx_HBV = -1000;
  b_diMuonF_m2_FittedVtx_HBV = -1000;

  b_diMuonC_m1_FittedVtx_MHAV = -1000;
  b_diMuonC_m2_FittedVtx_MHAV = -1000;
  b_diMuonF_m1_FittedVtx_MHAV = -1000;
  b_diMuonF_m2_FittedVtx_MHAV = -1000;
*/

  //Pixel Hit Recovery
  muJetC_muon1_track_minchi2=-10000000;
  muJetC_muon2_track_minchi2=-10000000;
  muJetF_muon1_track_minchi2=-10000000;
  muJetF_muon2_track_minchi2=-10000000;

  muJetC_muon1_track_minchi2theta=-10000000;
  muJetC_muon1_track_minchi2qoverpt=-10000000;
  muJetC_muon1_track_minchi2phi=-10000000;
  muJetC_muon1_track_minchi2dxy=-10000000;
  muJetC_muon1_track_minchi2dz=-10000000;

  muJetC_muon1_track_mincharge=-10000000;
  muJetC_muon1_track_minqoverpt=-10000000;
  muJetC_muon1_track_mintheta=-10000000;
  muJetC_muon1_track_minphi=-10000000;
  muJetC_muon1_track_mindxy=-10000000;
  muJetC_muon1_track_mindz=-10000000;

  for(int k=0;k<1000;k++){
    muJetC_muon1_track_diffchi2[k]=-10000000;
    muJetC_muon1_track_diffchi2theta[k]=-10000000;
    muJetC_muon1_track_diffchi2qoverpt[k]=-10000000;
    muJetC_muon1_track_diffchi2phi[k]=-10000000;
    muJetC_muon1_track_diffchi2dxy[k]=-10000000;
    muJetC_muon1_track_diffchi2dz[k]=-10000000;

    muJetC_muon1_track_diffcharge[k]=-10000000;
    muJetC_muon1_track_diffpt[k]=-10000000;
    muJetC_muon1_track_diffqoverp[k]=-10000000;
    muJetC_muon1_track_difftheta[k]=-10000000;
    muJetC_muon1_track_diffphi[k]=-10000000;
    muJetC_muon1_track_diffdxy[k]=-10000000;
    muJetC_muon1_track_diffdz[k]=-10000000;

    muJetC_muon2_track_diffcharge[k]=-10000000;
    muJetC_muon2_track_diffpt[k]=-10000000;
    muJetC_muon2_track_diffqoverp[k]=-10000000;
    muJetC_muon2_track_difftheta[k]=-10000000;
    muJetC_muon2_track_diffphi[k]=-10000000;
    muJetC_muon2_track_diffdxy[k]=-10000000;
    muJetC_muon2_track_diffdz[k]=-10000000;
  }



  for(int k=0;k<1000;k++){
    b_track_pt[k]=-10000000.0;
    b_track_charge[k]=-10000000;
    b_track_qoverp[k]=-10000000;
    b_track_theta[k]=-10000000;
    b_track_phi[k]=-10000000;
    b_track_dxy[k]=-10000000;
    b_track_dz[k]=-10000000;

    b_track_errpt[k]=-10000000;
    b_track_errcharge[k]=-10000000;
    b_track_errqoverp[k]=-10000000;
    b_track_errtheta[k]=-10000000;
    b_track_errphi[k]=-10000000;
    b_track_errdxy[k]=-10000000;
    b_track_errdz[k]=-10000000;
  }


  for(int k=0;k<10;k++){
    mtrack_pt[k]=-10000000;
    mtrack_charge[k]=-10000000;
    mtrack_qoverp[k]=-10000000;
    mtrack_theta[k]=-10000000;
    mtrack_phi[k]=-10000000;
    mtrack_dxy[k]=-10000000;
    mtrack_dz[k]=-10000000;

    mtrack_errpt[k]=-10000000;
    mtrack_errcharge[k]=-10000000;
    mtrack_errqoverp[k]=-10000000;
    mtrack_errtheta[k]=-10000000;
    mtrack_errphi[k]=-10000000;
    mtrack_errdxy[k]=-10000000;
    mtrack_errdz[k]=-10000000;
  }

  b_match_mu1track_muJetC=0;
  b_match_mu2track_muJetC=0;
  b_match_mu1track_muJetF=0;
  b_match_mu2track_muJetF=0;

  b_mutrack_pT_mu1JetC=-100000;
  b_mutrack_pT_mu2JetC=-100000;
  b_mutrack_pT_mu1JetF=-100000;
  b_mutrack_pT_mu2JetF=-100000;

  b_mutrack_eta_mu1JetC=-100000;
  b_mutrack_eta_mu2JetC=-100000;
  b_mutrack_eta_mu1JetF=-100000;
  b_mutrack_eta_mu2JetF=-100000;

  b_mutrack_phi_mu1JetC=-100000;
  b_mutrack_phi_mu2JetC=-100000;
  b_mutrack_phi_mu1JetF=-100000;
  b_mutrack_phi_mu2JetF=-100000;

  b_mutrack_charge_mu1JetC=-100000;
  b_mutrack_charge_mu2JetC=-100000;
  b_mutrack_charge_mu1JetF=-100000;
  b_mutrack_charge_mu2JetF=-100000;

  b_NPATJet=-10000;
  for(int k=0;k<100;k++){
    b_PAT_jet_pt[k]=-999.;
    b_PAT_jet_eta[k]=-999.;
    b_PAT_jet_phi[k]=-999.;
    b_PAT_jet_en[k]=-999.;
    b_PAT_jet_Btag1[k]=-999.;
    b_PAT_jet_Btag2[k]=-999.;
    b_PAT_jet_Btag3[k]=-999.;
  }

  b_ntracks=-10000;

  b_innerlayers_mu1_muJetC=-10000;
  b_innerlayers_mu2_muJetC=-10000;
  b_innerlayers_mu1_muJetF=-10000;
  b_innerlayers_mu2_muJetF=-10000;

  for(int k=0;k<10;k++){
    b_compdet_mu1_muJetC[k]=-10000;
    b_compdet_mu2_muJetC[k]=-10000;
    b_compdet_mu1_muJetF[k]=-10000;
    b_compdet_mu2_muJetF[k]=-10000;
  }

  for(int k=0;k<100;k++){
    b_numhit_mu1_muJetC[k]=-10000;
    b_numhit_mu2_muJetC[k]=-10000;
    b_numhit_mu1_muJetF[k]=-10000;
    b_numhit_mu2_muJetF[k]=-10000;
  }

  for(int k=0;k<10;k++){
    for(int j=0;j<10;j++){
      b_PXBID_mu1muJetC[k][j]=-10000;
      b_PXFID_mu1muJetC[k][j]=-10000;
      b_PXBID_mu2muJetC[k][j]=-10000;
      b_PXFID_mu2muJetC[k][j]=-10000;

      b_PXBID_mu1muJetF[k][j]=-10000;
      b_PXFID_mu1muJetF[k][j]=-10000;
      b_PXBID_mu2muJetF[k][j]=-10000;
      b_PXFID_mu2muJetF[k][j]=-10000;

      b_mj1m0posx[k][j]=-10000;
      b_mj1m0posy[k][j]=-10000;
      b_mj1m0posx_err[k][j]=-10000;
      b_mj1m0posy_err[k][j]=-10000;
      b_mj1m1posx[k][j]=-10000;
      b_mj1m1posy[k][j]=-10000;
      b_mj1m1posx_err[k][j]=-10000;
      b_mj1m1posy_err[k][j]=-10000;

      b_mj2m0posx[k][j]=-10000;
      b_mj2m0posy[k][j]=-10000;
      b_mj2m0posx_err[k][j]=-10000;
      b_mj2m0posy_err[k][j]=-10000;
      b_mj2m1posx[k][j]=-10000;
      b_mj2m1posy[k][j]=-10000;
      b_mj2m1posx_err[k][j]=-10000;
      b_mj2m1posy_err[k][j]=-10000;

    }
  }

  for(int k=0;k<10;k++){
    for(int j=0;j<100;j++){
      b_pixelhit_mu1_muJetC_posx[k][j]=-10000;
      b_pixelhit_mu1_muJetC_posy[k][j]=-10000;
      b_pixelhit_mu1_muJetC_errposx[k][j]=-10000;
      b_pixelhit_mu1_muJetC_errposy[k][j]=-10000;
      b_pixelhit_mu2_muJetC_posx[k][j]=-10000;
      b_pixelhit_mu2_muJetC_posy[k][j]=-10000;
      b_pixelhit_mu2_muJetC_errposx[k][j]=-10000;
      b_pixelhit_mu2_muJetC_errposy[k][j]=-10000;

      b_pixelhit_mu1_muJetF_posx[k][j]=-10000;
      b_pixelhit_mu1_muJetF_posy[k][j]=-10000;
      b_pixelhit_mu1_muJetF_errposx[k][j]=-10000;
      b_pixelhit_mu1_muJetF_errposy[k][j]=-10000;
      b_pixelhit_mu2_muJetF_posx[k][j]=-10000;
      b_pixelhit_mu2_muJetF_posy[k][j]=-10000;
      b_pixelhit_mu2_muJetF_errposx[k][j]=-10000;
      b_pixelhit_mu2_muJetF_errposy[k][j]=-10000;
    }
  }
  b_Mass4Mu = -1.;

  //****************************************************************************
  //                          EVENT LEVEL
  //****************************************************************************

  // Count number of analyzed events
  m_events++;
  if ( !(m_events%1000) ) std::cout << "Event " << m_events << std::endl;
  if(m_debug > 10) std::cout << "m_barrelPixelLayer: " << m_barrelPixelLayer << std::endl;

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
  iEvent.getByToken(m_beamSpot, beamSpot);
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
  //Trigger names
  if( histo_name ){
    edm::Handle<edm::TriggerResults> TrResults;
    iEvent.getByToken( m_trigRes, TrResults);
    const TriggerResults *trRes = TrResults.product();
    int ntrigs = trRes->size();
    if (ntrigs==0) std::cout << "No trigger name given in TriggerResults of the input " << std::endl;
    edm::TriggerNames const& triggerNames = iEvent.triggerNames(*trRes);
    int nBin=0, nBins=0;
    for (int itrig = 0; itrig != ntrigs; ++itrig) {
	TString trigName = triggerNames.triggerName(itrig);
	if( trigName.BeginsWith("HLT_") && (trigName.Contains("Double") || trigName.Contains("TripleMu")) ){
	  nBins++;
	}
    }
    edm::Service<TFileService> tFileService;
    triggerComposition = tFileService->make<TH1F>( "triggerComposition", "", nBins, -0.5, nBins-0.5 );
    triggerComposition_bb = tFileService->make<TH1F>( "triggerComposition_bb", "", nBins, -0.5, nBins-0.5 );
    for (int itrig = 0; itrig != ntrigs; ++itrig) {
	TString trigName = triggerNames.triggerName(itrig);
	if( trigName.BeginsWith("HLT_") && (trigName.Contains("Double") || trigName.Contains("TripleMu")) ){
	  NameAndNumb[nBin] = trigName;
	  triggerComposition->GetXaxis()->SetBinLabel(nBin+1,trigName);
	  triggerComposition_bb->GetXaxis()->SetBinLabel(nBin+1,trigName);
	  nBin++;
	}
    }
    histo_name = false;
  }

  //****************************************************************************
  //                          GEN LEVEL ANALYSIS START
  //****************************************************************************

  if (m_fillGenLevel){

    if ( m_debug > 10 ) std::cout << m_events << " Start GEN Level" << std::endl;

    edm::Handle<reco::GenParticleCollection> genParticles;
    iEvent.getByToken(m_genParticles, genParticles);

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
          //        if ( genMuonCand->mother(iMother)->pdgId() == 36 || genMuonCand->mother(iMother)->pdgId() == 3000022 || genMuonCand->mother(iMother)->pdgId() == 443 )
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
      std::sort (genA_unsorted.begin(), genA_unsorted.end(), tamu::helpers::PtOrder);
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

    if ( genMuonGroups.size() == 2 && genMuonGroups[0].size() == 2 && genMuonGroups[1].size() == 2 ) {
      std::sort( genMuonGroups[0].begin(), genMuonGroups[0].end(), tamu::helpers::PtOrder );
      std::sort( genMuonGroups[1].begin(), genMuonGroups[1].end(), tamu::helpers::PtOrder );

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

        std::cout<<">>> AOD Event #"<<m_events<<std::endl;
        std::cout<<"GENA mass (0, 1)[GeV]: "<<b_genA0_m    <<", "<<b_genA1_m       << std::endl;
        std::cout<<"genA0     (x,y,z)[cm]: "<<b_genA0_vx   <<", "<<b_genA0_vy      <<", "<<b_genA0_vz<<std::endl;
        std::cout<<"genA0 Mu0 (x,y,z)[cm]: "<<b_genA0Mu0_vx<<", "<<b_genA0Mu0_vy   <<", "<<b_genA0Mu0_vz<<std::endl;
        std::cout<<"genA0 Mu1 (x,y,z)[cm]: "<<b_genA0Mu1_vx<<", "<<b_genA0Mu1_vy   <<", "<<b_genA0Mu1_vz<<std::endl;
        std::cout<<"genA0 (Lxy, |Lz|)[cm]: "<<b_genA0_Lxy  <<", "<<fabs(b_genA0_Lz)<<std::endl;
        std::cout<<"genA1     (x,y,z)[cm]: "<<b_genA1_vx   <<", "<<b_genA1_vy      <<", "<<b_genA1_vz<<std::endl;
        std::cout<<"genA1 Mu0 (x,y,z)[cm]: "<<b_genA1Mu0_vx<<", "<<b_genA1Mu0_vy   <<", "<<b_genA1Mu0_vz<<std::endl;
        std::cout<<"genA1 Mu1 (x,y,z)[cm]: "<<b_genA1Mu1_vx<<", "<<b_genA1Mu1_vy   <<", "<<b_genA1Mu1_vz<<std::endl;
        std::cout<<"genA1 (Lxy, |Lz|)[cm]: "<<b_genA1_Lxy  <<", "<<fabs(b_genA1_Lz)<<std::endl;

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
      b_genA0Mu_dPhi = tamu::helpers::My_dPhi( genMuonGroups[0][0]->phi(), genMuonGroups[0][1]->phi() );
      b_genA1Mu_dPhi = tamu::helpers::My_dPhi( genMuonGroups[1][0]->phi(), genMuonGroups[1][1]->phi() );
      b_genA0Mu_dR   = sqrt(b_genA0Mu_dEta*b_genA0Mu_dEta + b_genA0Mu_dPhi*b_genA0Mu_dPhi);
      b_genA1Mu_dR   = sqrt(b_genA1Mu_dEta*b_genA1Mu_dEta + b_genA1Mu_dPhi*b_genA1Mu_dPhi);
    } else {

    }


    // Sort genMuons by pT (leading pT first)
    if ( genMuons.size() > 1 ) std::sort( genMuons.begin(), genMuons.end(), tamu::helpers::PtOrder );

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
  iEvent.getByToken(m_muons, muons);

  std::vector<const pat::Muon*> selMuons;
  std::vector<const pat::Muon*> selMuons8;
  std::vector<const pat::Muon*> selMuons17;

  for (pat::MuonCollection::const_iterator iMuon = muons->begin();  iMuon != muons->end();  ++iMuon) {
    if ( tamu::helpers::PassMuonId( &(*iMuon) ) ) {
      selMuons.push_back( &(*iMuon) );
      if ( iMuon->pt() > m_threshold_Mu8_pT ) {
        selMuons8.push_back( &(*iMuon) );
      }
      if ( iMuon->pt() > m_threshold_Mu17_pT && fabs(iMuon->eta()) < m_threshold_Mu17_eta ) {
        selMuons17.push_back( &(*iMuon) );
      }
    }
  }

  b_nRecoMu = selMuons.size();

  if ( selMuons.size() > 0 ) {
    b_selMu0_px  = selMuons[0]->px();
    b_selMu0_py  = selMuons[0]->py();
    b_selMu0_pz  = selMuons[0]->pz();
    b_selMu0_pT  = selMuons[0]->pt();
    b_selMu0_eta = selMuons[0]->eta();
    b_selMu0_phi = selMuons[0]->phi();
    b_selMu0_trigHLT16 = wasRecoMuonTriggerMatched(selMuons[0], signalHltPaths_[0] + "_v*", 16.);
    b_selMu0_trigHLT6 = wasRecoMuonTriggerMatched(selMuons[0], signalHltPaths_[0] + "_v*", 6.);
  } else {
    b_selMu0_px  = -100.0;
    b_selMu0_py  = -100.0;
    b_selMu0_pz  = -100.0;
    b_selMu0_pT  = -100.0;
    b_selMu0_eta = -100.0;
    b_selMu0_phi = -100.0;
    b_selMu0_trigHLT16 = false;
    b_selMu0_trigHLT6 = false;
  }
  if ( selMuons.size() > 1 ) {
    b_selMu1_px  = selMuons[1]->px();
    b_selMu1_py  = selMuons[1]->py();
    b_selMu1_pz  = selMuons[1]->pz();
    b_selMu1_pT  = selMuons[1]->pt();
    b_selMu1_eta = selMuons[1]->eta();
    b_selMu1_phi = selMuons[1]->phi();
    b_selMu1_trigHLT16 = wasRecoMuonTriggerMatched(selMuons[1], signalHltPaths_[0] + "_v*", 16.);
    b_selMu1_trigHLT6 = wasRecoMuonTriggerMatched(selMuons[1], signalHltPaths_[0] + "_v*", 6.);
  } else {
    b_selMu1_px  = -100.0;
    b_selMu1_py  = -100.0;
    b_selMu1_pz  = -100.0;
    b_selMu1_pT  = -100.0;
    b_selMu1_eta = -100.0;
    b_selMu1_phi = -100.0;
    b_selMu1_trigHLT16 = false;
    b_selMu1_trigHLT6 = false;
  }
  if ( selMuons.size() > 2 ) {
    b_selMu2_px  = selMuons[2]->px();
    b_selMu2_py  = selMuons[2]->py();
    b_selMu2_pz  = selMuons[2]->pz();
    b_selMu2_pT  = selMuons[2]->pt();
    b_selMu2_eta = selMuons[2]->eta();
    b_selMu2_phi = selMuons[2]->phi();
    b_selMu2_trigHLT16 = wasRecoMuonTriggerMatched(selMuons[2], signalHltPaths_[0] + "_v*", 16.);
    b_selMu2_trigHLT6 = wasRecoMuonTriggerMatched(selMuons[2], signalHltPaths_[0] + "_v*", 6.);
  } else {
    b_selMu2_px  = -100.0;
    b_selMu2_py  = -100.0;
    b_selMu2_pz  = -100.0;
    b_selMu2_pT  = -100.0;
    b_selMu2_eta = -100.0;
    b_selMu2_phi = -100.0;
    b_selMu2_trigHLT16 = false;
    b_selMu2_trigHLT6 = false;
  }
  if ( selMuons.size() > 3 ) {
    b_selMu3_px  = selMuons[3]->px();
    b_selMu3_py  = selMuons[3]->py();
    b_selMu3_pz  = selMuons[3]->pz();
    b_selMu3_pT  = selMuons[3]->pt();
    b_selMu3_eta = selMuons[3]->eta();
    b_selMu3_phi = selMuons[3]->phi();
    b_selMu3_trigHLT16 = wasRecoMuonTriggerMatched(selMuons[3], signalHltPaths_[0] + "_v*", 16.);
    b_selMu3_trigHLT6 = wasRecoMuonTriggerMatched(selMuons[3], signalHltPaths_[0] + "_v*", 6.);
  } else {
    b_selMu3_px  = -100.0;
    b_selMu3_py  = -100.0;
    b_selMu3_pz  = -100.0;
    b_selMu3_pT  = -100.0;
    b_selMu3_eta = -100.0;
    b_selMu3_phi = -100.0;
    b_selMu3_trigHLT16 = false;
    b_selMu3_trigHLT6 = false;
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
  iEvent.getByToken(m_muJets, muJets);
  const pat::MultiMuon *muJetC = NULL;
  const pat::MultiMuon *muJetF = NULL;
  int   nMuJetsContainMu17     = 0;
  unsigned int nMuJets = muJets->size();
  b_massC = -999.; b_massF = -999.;
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
  if ( b_is1SelMu17 && b_is4SelMu8 && b_is2MuJets && b_is2DiMuons){
    m_events2DiMuons++;
    b_massC = muJetC->mass();
    b_massF = muJetF->mass();
  }
  // "Old" fitted vertexes
  b_is2DiMuonsFittedVtxOK = false;
  if ( diMuonC != NULL && diMuonF != NULL ) {
    if ( diMuonC->vertexValid() && diMuonF->vertexValid() ) {
      b_is2DiMuonsFittedVtxOK = true;
    }
  }

  b_is2DiMuonsFittedVtxOK_KF = false;
  if ( diMuonC != NULL && diMuonF != NULL ) {
    if ( diMuonC->vertexValid_fitted() && diMuonF->vertexValid_fitted() ) {
      b_is2DiMuonsFittedVtxOK_KF = true;
    }
  }
  b_is2DiMuonsFittedVtxOK_VS = false;
  if ( diMuonC != NULL && diMuonF != NULL ) {
    if ( diMuonC->vertexValid_mindist() && diMuonF->vertexValid_mindist() ) {
      b_is2DiMuonsFittedVtxOK_VS = true;
    }
  }



  // Cut on primary vertex in event
  edm::Handle<reco::VertexCollection> primaryVertices;
  iEvent.getByToken(m_primaryVertices, primaryVertices);


  reco::VertexCollection::const_iterator closestPrimaryVertex = primaryVertices->end();
  if (muJets->size() > 0) {
    pat::MultiMuonCollection::const_iterator muJet0 = muJets->end();
    for (pat::MultiMuonCollection::const_iterator muJet = muJets->begin();  muJet != muJets->end();  ++muJet) {
      if (muJet->vertexValid()) {
        muJet0 = muJet;
        break;
      }
    }

    if (muJet0 != muJets->end()) {
      for (reco::VertexCollection::const_iterator vertex = primaryVertices->begin();  vertex != primaryVertices->end();  ++vertex) {
        if (vertex->isValid()  &&  !vertex->isFake()  &&  vertex->tracksSize() > 3  &&  fabs(vertex->z()) < 24.) {
          if (closestPrimaryVertex == primaryVertices->end()  ||  fabs(vertex->z() - muJet0->vertexPoint().z()) < fabs(closestPrimaryVertex->z() - muJet0->vertexPoint().z())) {
            closestPrimaryVertex = vertex;
          }
        } // end vertex quality cuts
      } // end loop over primary vertices
    } // end if muJet0 exists
  } // end if muJets->size > 0


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
    b_diMuonC_FittedVtx_Lxy_rclstvtx = diMuonC->vertexLxy(GlobalPoint(closestPrimaryVertex->x(), closestPrimaryVertex->y(), closestPrimaryVertex->z()));
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
    b_diMuonF_FittedVtx_Lxy_rclstvtx = diMuonF->vertexLxy(GlobalPoint(closestPrimaryVertex->x(), closestPrimaryVertex->y(), closestPrimaryVertex->z()));
    b_diMuonF_FittedVtx_L   = diMuonF->vertexL(beamSpotPosition);
    b_diMuonF_FittedVtx_dz  = diMuonF->vertexDz(beamSpot->position());

  std::cout << "diMuC vtx         (x,y,z)[cm]: " << b_diMuonC_FittedVtx_vx << ", " << b_diMuonC_FittedVtx_vy << ", " << b_diMuonC_FittedVtx_vz << std::endl;
  std::cout << "diMuC Mu0 innerTrk(x,y,z)[cm]: " << diMuonC->muon(0)->innerTrack()->vx() << ", " << diMuonC->muon(0)->innerTrack()->vy() << ", " << diMuonC->muon(0)->innerTrack()->vz() << std::endl;
  std::cout << "diMuC Mu1 innerTrk(x,y,z)[cm]: " << diMuonC->muon(1)->innerTrack()->vx() << ", " << diMuonC->muon(1)->innerTrack()->vy() << ", " << diMuonC->muon(1)->innerTrack()->vz() << std::endl;
  std::cout << "diMuC vtx   (Lxy,|Lz|,dz)[cm]: " << b_diMuonC_FittedVtx_Lxy<< ", " << sqrt( pow(b_diMuonC_FittedVtx_L,2) - pow(b_diMuonC_FittedVtx_Lxy,2) )<<", "<<b_diMuonC_FittedVtx_dz<< std::endl;

  std::cout << "diMuF vtx         (x,y,z)[cm]: " << b_diMuonF_FittedVtx_vx << ", " << b_diMuonF_FittedVtx_vy << ", " << b_diMuonF_FittedVtx_vz << std::endl;
  std::cout << "diMuF Mu0 innerTrk(x,y,z)[cm]: " << diMuonF->muon(0)->innerTrack()->vx() << ", " << diMuonF->muon(0)->innerTrack()->vy() << ", " << diMuonF->muon(0)->innerTrack()->vz() << std::endl;
  std::cout << "diMuF Mu1 innerTrk(x,y,z)[cm]: " << diMuonF->muon(1)->innerTrack()->vx() << ", " << diMuonF->muon(1)->innerTrack()->vy() << ", " << diMuonF->muon(1)->innerTrack()->vz() << std::endl;
  std::cout << "diMuF vtx   (Lxy,|Lz|,dz)[cm]: " << b_diMuonF_FittedVtx_Lxy<< ", " << sqrt( pow(b_diMuonF_FittedVtx_L,2) - pow(b_diMuonF_FittedVtx_Lxy,2) )<<", "<<b_diMuonF_FittedVtx_dz<< std::endl;

  std::cout << "Dimu vtx mass     (C, F)[GeV]: " << b_diMuonC_FittedVtx_m  << ", " << b_diMuonF_FittedVtx_m  << std::endl;
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
    b_diMuonC_FittedVtx_Lxy_rclstvtx = -1000.0;
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
    b_diMuonF_FittedVtx_Lxy_rclstvtx = -1000.0;
    b_diMuonF_FittedVtx_L   = -1000.0;
    b_diMuonF_FittedVtx_dz  = -1000.0;
  }
/*
  // "New" consistent vertexes
  b_is2DiMuonsConsistentVtxOK = false;
  if ( diMuonC != NULL && diMuonF != NULL ) {
    if ( m_debug > 10 ) std::cout << "Two good dimuons" << std::endl;
    edm::ESHandle<TransientTrackBuilder> transientTrackBuilder;
    const TransientTrackBuilder *transientTrackBuilder_ptr = NULL;
    try {
      iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder", transientTrackBuilder);
      transientTrackBuilder_ptr = &*transientTrackBuilder;

      ConsistentVertexesCalculator ConsistentVtx(transientTrackBuilder_ptr, beamSpotPosition);
      ConsistentVtx.SetNThrows(m_nThrowsConsistentVertexesCalculator);
      ConsistentVtx.SetDebug(99);
      ConsistentVtx.setBarrelPixelLayer(m_barrelPixelLayer);
      ConsistentVtx.setEndcapPixelLayer(m_endcapPixelLayer);

      b_is2DiMuonsConsistentVtxOK = ConsistentVtx.Calculate(diMuonC, diMuonF);

      if (runDisplacedVtxFinder_) {
        DisplacedVertexFinder displacedVtx(transientTrackBuilder_ptr, beamSpotPosition);
        displacedVtx.setDebug(99);
        displacedVtx.findDisplacedVertex(diMuonC, diMuonF);
      }
    } catch (...) {
      std::cout << ">>>> WARNING!!! TransientTrackRecord is not available!!! <<<<" << std::endl;
    }
  }
  */
  /*
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
*/

  // Calculate dz between dimuons - use fitted vertexes
  if ( b_is2DiMuonsFittedVtxOK ) {
    b_diMuons_dz_FittedVtx = b_diMuonC_FittedVtx_dz - b_diMuonF_FittedVtx_dz;
  } else {
    b_diMuons_dz_FittedVtx = -1000.0;
  }
/*
  // Calculate dz between dimuons - use consistent vertexes
  if ( b_is2DiMuonsConsistentVtxOK ) {
    b_diMuons_dz_ConsistentVtx = b_diMuonC_ConsistentVtx_dz - b_diMuonF_ConsistentVtx_dz;
  } else {
    b_diMuons_dz_ConsistentVtx = -1000.0;
  }
  */

  if ( m_debug > 10 ) std::cout << m_events << " Apply cut on dZ" << std::endl;

  // HLT cut
  b_isDiMuonHLTFired = false;
  b_hltPaths.clear();

  edm::Handle<edm::TriggerResults> TrResults;
  iEvent.getByToken( m_trigRes, TrResults);
  const TriggerResults *trRes = TrResults.product();
  edm::TriggerNames const& triggerNames = iEvent.triggerNames(*trRes);

  // HLT cut
  edm::Handle<pat::TriggerEvent> triggerEvent;
  iEvent.getByToken(m_triggerEvent, triggerEvent);

  int ntrigs = trRes->size();
  for (int itrig = 0; itrig != ntrigs; ++itrig) {
    const TString& trigName = triggerNames.triggerName(itrig);
    const std::string& trigNameStr(trigName.Data());

    if ( triggerEvent->path(trigNameStr)->wasAccept() ) {
      if ( m_debug > 10 ) std::cout << trigNameStr << " is present in patTriggerEvent!" << std::endl;
    }

    if (trRes->accept(triggerNames.triggerIndex(trigNameStr))){
      b_hltPaths.push_back(trigNameStr);
      if ( m_debug > 10 ) std::cout << trigNameStr << " is present in edmTriggerResults!" << std::endl;

      // check if this event was fired by the signal trigger!
      for (const auto& p: signalHltPaths_){
        if (trigNameStr.find(p) != std::string::npos) {
          b_isDiMuonHLTFired = true;
        if ( m_debug > 10 ) std::cout << trigNameStr << " signal trigger!" << std::endl;
        }
      }
    }
  }


  if ( m_debug > 10 ) std::cout << m_events << " Apply cut on HLT" << std::endl;

  // Cut on dimuon masses - use fitted vertexes
  b_is2DiMuonsMassOK_FittedVtx = false;
  if ( b_is2DiMuonsFittedVtxOK ) {
    double massC = b_diMuonC_FittedVtx_m;
    double massF = b_diMuonF_FittedVtx_m;
    if ( fabs(massC-massF) < (0.13 + 0.065*(massC+massF)/2.0) ) b_is2DiMuonsMassOK_FittedVtx = true;
  }
/*
  // Cut on dimuon masses - use consistent vertexes
  b_is2DiMuonsMassOK_ConsistentVtx = false;
  if ( b_is2DiMuonsConsistentVtxOK ) {
    double massC = b_diMuonC_ConsistentVtx_m;
    double massF = b_diMuonF_ConsistentVtx_m;
    if ( fabs(massC-massF) < (0.13 + 0.065*(massC+massF)/2.0) ) b_is2DiMuonsMassOK_ConsistentVtx = true;
  }
  */

  if ( m_debug > 10 ) std::cout << m_events << " Apply cut on dimuon mass" << std::endl;

  // Cut on isolation
  edm::Handle<reco::TrackCollection> tracks;
  iEvent.getByToken(m_tracks, tracks);

  // Cut on isolation - use fitted vertexes
  b_diMuonC_IsoTk_FittedVtx = -1.;
  b_diMuonF_IsoTk_FittedVtx = -1.;
  b_isoC_1mm = -1.;
  b_isoF_1mm = -1.;
  if ( b_is2DiMuonsFittedVtxOK ) {
    double diMuonC_IsoTk_FittedVtx = 0.0;
    double diMuonF_IsoTk_FittedVtx = 0.0;

    const pat::MultiMuon *diMuonTmp = NULL;
    for ( unsigned int i = 1; i <= 2; i++ ) {
      double diMuonTmp_IsoTk_FittedVtx = 0.0;
      if ( i == 1 ) diMuonTmp = diMuonC;
      if ( i == 2 ) diMuonTmp = diMuonF;

      for (reco::TrackCollection::const_iterator track = tracks->begin(); track != tracks->end(); ++track) {
        bool trackIsMuon = false;
        if (    diMuonTmp->sameTrack( &*track, &*(diMuonTmp->muon(0)->innerTrack()) )
		|| diMuonTmp->sameTrack( &*track, &*(diMuonTmp->muon(1)->innerTrack()) ) ) trackIsMuon = true;
        if ( trackIsMuon == false ) {
          double dPhi = tamu::helpers::My_dPhi( diMuonTmp->vertexMomentum().phi(), track->phi() );
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
      if ( i == 1 ) {
        diMuonC_IsoTk_FittedVtx = diMuonTmp_IsoTk_FittedVtx;
      }
      if ( i == 2 ) {
        diMuonF_IsoTk_FittedVtx = diMuonTmp_IsoTk_FittedVtx;
      }
    }
    b_diMuonC_IsoTk_FittedVtx = diMuonC_IsoTk_FittedVtx;
    b_diMuonF_IsoTk_FittedVtx = diMuonF_IsoTk_FittedVtx;
    b_isoC_1mm = b_diMuonC_IsoTk_FittedVtx;
    b_isoF_1mm = b_diMuonF_IsoTk_FittedVtx;

  }
/*
  // Cut on isolation - use consistent vertexes
  b_diMuonC_IsoTk_ConsistentVtx = -1.;
  b_diMuonF_IsoTk_ConsistentVtx = -1.;
  if ( b_is2DiMuonsConsistentVtxOK ) {
    double diMuonC_IsoTk_ConsistentVtx = 0.0;
    double diMuonF_IsoTk_ConsistentVtx = 0.0;

    const pat::MultiMuon *diMuonTmp = NULL;
    for ( unsigned int i = 1; i <= 2; i++ ) {
      double diMuonTmp_IsoTk_ConsistentVtx = 0.0;
      if ( i == 1 ) diMuonTmp = diMuonC;
      if ( i == 2 ) diMuonTmp = diMuonF;

      for (reco::TrackCollection::const_iterator track = tracks->begin(); track != tracks->end(); ++track) {
        bool trackIsMuon = false;
        if (    diMuonTmp->sameTrack( &*track, &*(diMuonTmp->muon(0)->innerTrack()) )
		|| diMuonTmp->sameTrack( &*track, &*(diMuonTmp->muon(1)->innerTrack()) ) ) trackIsMuon = true;
        if ( trackIsMuon == false ) {
          double dPhi = tamu::helpers::My_dPhi( diMuonTmp->consistentVtxMomentum().phi(), track->phi() );
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
      if ( i == 1 ) {
        diMuonC_IsoTk_ConsistentVtx = diMuonTmp_IsoTk_ConsistentVtx;
      }
      if ( i == 2 ) {
        diMuonF_IsoTk_ConsistentVtx = diMuonTmp_IsoTk_ConsistentVtx;
      }
    }
    b_diMuonC_IsoTk_ConsistentVtx = diMuonC_IsoTk_ConsistentVtx;
    b_diMuonF_IsoTk_ConsistentVtx = diMuonF_IsoTk_ConsistentVtx;


  }
  */

  if ( m_debug > 10 ) std::cout << m_events << " Apply cut on dimuon isolation" << std::endl;



  if ( b_is2DiMuonsFittedVtxOK ) {
    for(uint32_t k=0;k<2;k++){
      for (reco::TrackCollection::const_iterator track = tracks->begin(); track != tracks->end(); ++track) {
        if(tamu::helpers::sameTrack(&*track,&*(diMuonC->muon(k)->innerTrack()))){
          const reco::HitPattern& p = track->hitPattern();

          std::cout << "diMuC Mu"<<k<<" innerTrk(x,y,z)[cm]: " << diMuonC->muon(k)->innerTrack()->vx() << ", "<< diMuonC->muon(k)->innerTrack()->vy() <<", "<< diMuonC->muon(k)->innerTrack()->vz() <<std::endl;

          /*
          static CheckHitPattern checkHitPattern;
          GlobalPoint pos(diMuonC->vertexPoint().x(), diMuonC->vertexPoint().y(), diMuonC->vertexPoint().z());
          VertexState trueDecVert(pos, GlobalError());
          CheckHitPattern::Result hitInfo = checkHitPattern.analyze(iSetup, *track, trueDecVert , true);
	  //To be used for Run 2018
	  //checkHitPattern.init(iSetup);
          //CheckHitPattern::Result hitInfo = checkHitPattern.operator()(*track, trueDecVert);

          if(k==0) b_diMuonC_m1_FittedVtx_HBV = hitInfo.hitsInFrontOfVert;
          if(k==0) b_diMuonC_m1_FittedVtx_MHAV = hitInfo.missHitsAfterVert;
          if(k==1) b_diMuonC_m2_FittedVtx_HBV = hitInfo.hitsInFrontOfVert;
          if(k==1) b_diMuonC_m2_FittedVtx_MHAV = hitInfo.missHitsAfterVert;
          */

          if(p.hasValidHitInPixelLayer(PixelSubdetector::PixelEndcap, 1) || p.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 1)){
            if(k==0) b_diMuonC_m1_FittedVtx_hitpix = 1;
            if(k==1) b_diMuonC_m2_FittedVtx_hitpix = 1;
          }
          if(p.hasValidHitInPixelLayer(PixelSubdetector::PixelEndcap, 1) || p.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 1) ||
	     p.hasValidHitInPixelLayer(PixelSubdetector::PixelEndcap, 2) || p.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 2)){
            if(k==0) b_diMuonC_m1_FittedVtx_hitpix_l2inc = 1;
            if(k==1) b_diMuonC_m2_FittedVtx_hitpix_l2inc = 1;
          }
          if(p.hasValidHitInPixelLayer(PixelSubdetector::PixelEndcap, 1) || p.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 1) ||
	     p.hasValidHitInPixelLayer(PixelSubdetector::PixelEndcap, 2) || p.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 2) ||
	     p.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 3)){
            if(k==0) b_diMuonC_m1_FittedVtx_hitpix_l3inc = 1;
            if(k==1) b_diMuonC_m2_FittedVtx_hitpix_l3inc = 1;
          }
          if( p.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 1) || p.hasValidHitInPixelLayer(PixelSubdetector::PixelEndcap, 1) ||
	     p.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 2) || p.hasValidHitInPixelLayer(PixelSubdetector::PixelEndcap, 2) ||
	     p.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 3) || p.hasValidHitInPixelLayer(PixelSubdetector::PixelEndcap, 3) ||
       p.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 4) ){
            if(k==0) b_diMuonC_m1_FittedVtx_hitpix_Phase1 = 1;
            if(k==1) b_diMuonC_m2_FittedVtx_hitpix_Phase1 = 1;
          }

        }

        if(tamu::helpers::sameTrack(&*track,&*(diMuonF->muon(k)->innerTrack()))){
          const reco::HitPattern& p = track->hitPattern();
          std::cout << "diMuF Mu"<<k<<" innerTrk(x,y,z)[cm]: " << diMuonF->muon(k)->innerTrack()->vx() << ", "<< diMuonF->muon(k)->innerTrack()->vy() <<", "<< diMuonF->muon(k)->innerTrack()->vz() <<std::endl;

          /*
          static CheckHitPattern checkHitPattern;
          GlobalPoint pos(diMuonF->vertexPoint().x(), diMuonF->vertexPoint().y(), diMuonF->vertexPoint().z());
          VertexState trueDecVert(pos, GlobalError());
          CheckHitPattern::Result hitInfo = checkHitPattern.analyze(iSetup, *track, trueDecVert , true);
	  //To be used for Run 2018
	  //checkHitPattern.init(iSetup);
          //CheckHitPattern::Result hitInfo = checkHitPattern.operator()(*track, trueDecVert);

          if(k==0) b_diMuonF_m1_FittedVtx_HBV = hitInfo.hitsInFrontOfVert;
          if(k==0) b_diMuonF_m1_FittedVtx_MHAV = hitInfo.missHitsAfterVert;
          if(k==1) b_diMuonF_m2_FittedVtx_HBV = hitInfo.hitsInFrontOfVert;
          if(k==1) b_diMuonF_m2_FittedVtx_MHAV = hitInfo.missHitsAfterVert;
          */
          if(p.hasValidHitInPixelLayer(PixelSubdetector::PixelEndcap, 1) || p.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 1)){
            if(k==0) b_diMuonF_m1_FittedVtx_hitpix = 1;
            if(k==1) b_diMuonF_m2_FittedVtx_hitpix = 1;
          }
          if(p.hasValidHitInPixelLayer(PixelSubdetector::PixelEndcap, 1) || p.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 1) ||
	     p.hasValidHitInPixelLayer(PixelSubdetector::PixelEndcap, 2) || p.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 2)){
            if(k==0) b_diMuonF_m1_FittedVtx_hitpix_l2inc = 1;
            if(k==1) b_diMuonF_m2_FittedVtx_hitpix_l2inc = 1;
          }
          if(p.hasValidHitInPixelLayer(PixelSubdetector::PixelEndcap, 1) || p.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 1) ||
	     p.hasValidHitInPixelLayer(PixelSubdetector::PixelEndcap, 2) || p.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 2) ||
	     p.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 3) ){
            if(k==0) b_diMuonF_m1_FittedVtx_hitpix_l3inc = 1;
            if(k==1) b_diMuonF_m2_FittedVtx_hitpix_l3inc = 1;
          }
          if( p.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 1) || p.hasValidHitInPixelLayer(PixelSubdetector::PixelEndcap, 1) ||
	     p.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 2) || p.hasValidHitInPixelLayer(PixelSubdetector::PixelEndcap, 2) ||
	     p.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 3) || p.hasValidHitInPixelLayer(PixelSubdetector::PixelEndcap, 3) ||
       p.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 4) ){
            if(k==0) b_diMuonF_m1_FittedVtx_hitpix_Phase1 = 1;
            if(k==1) b_diMuonF_m2_FittedVtx_hitpix_Phase1 = 1;
          }

        }
      }
    }
    std::cout<<"ValidHit  PixelLayers: C_m1 = "<<b_diMuonC_m1_FittedVtx_hitpix_Phase1<<"; C_m2 = "<<b_diMuonC_m2_FittedVtx_hitpix_Phase1<<std::endl;
    std::cout<<"ValidHit  PixelLayers: F_m1 = "<<b_diMuonF_m1_FittedVtx_hitpix_Phase1<<"; F_m2 = "<<b_diMuonF_m2_FittedVtx_hitpix_Phase1<<std::endl;
  }


  // Cut on primary vertex in event
  b_isVertexOK = false;
  for (reco::VertexCollection::const_iterator vertex = primaryVertices->begin();  vertex != primaryVertices->end();  ++vertex) {
    if (vertex->isValid() && !vertex->isFake() && vertex->tracksSize() >= 4 && fabs(vertex->z()) < 24.) {
      b_isVertexOK = true;
    }
  }

  if ( m_debug > 10 ) std::cout << m_events << " Stop RECO Level" << std::endl;

  if (m_debug>10 && b_is4SelMu8 && b_is2MuJets && b_is2DiMuons && b_is2DiMuonsFittedVtxOK){
    std::cout<<"  hitpix diMuonF m1   "<<b_diMuonF_m1_FittedVtx_hitpix_l3inc<<std::endl;
    std::cout<<"  hitpix diMuonF m2   "<<b_diMuonF_m2_FittedVtx_hitpix_l3inc<<std::endl;
    std::cout<<"  hitpix diMuonC m1   "<<b_diMuonC_m1_FittedVtx_hitpix_l3inc<<std::endl;
    std::cout<<"  hitpix diMuonC m2   "<<b_diMuonC_m2_FittedVtx_hitpix_l3inc<<std::endl;
  }

  if(runBBestimation_){
    FillTrigInfo(triggerComposition, triggerNames, NameAndNumb );
    m_orphan_passOffLineSel = false;
    m_orphan_passOffLineSelPt = false;
    m_orphan_passOffLineSelPtEta = false;
    m_orphan_passOffLineSelPt1788 = false;
    m_orphan_AllTrackerMu = false;
    m_orphan_PtOrph  = -99.;
    m_orphan_EtaOrph = -99.;
    m_orphan_PhiOrph = -99.;
    m_orphan_PtMu0   = -99.;
    m_orphan_EtaMu0  = -99.;
    m_orphan_PhiMu0  = -99.;
    m_orphan_PtMu1   = -99.;
    m_orphan_EtaMu1  = -99.;
    m_orphan_PhiMu1  = -99.;
    m_orphan_PtMu01   = -99.;
    m_orphan_EtaMu01  = -99.;
    m_orphan_PhiMu01  = -99.;
    m_orphan_DRdiMuOrph  = -99.;
    // B-Jets
    int NPATJet=0;
    edm::Handle<std::vector<pat::Jet> > PATJet;
    iEvent.getByToken(m_PATJet, PATJet);
    for( auto Myjet = PATJet->begin(); Myjet != PATJet->end(); ++Myjet ){
      if( fabs(Myjet->eta())<2.4 && Myjet->pt()>5. ){
        // B-tags available:
        //'pfTrackCountingHighEffBJetTags', 'pfTtrackCountingHighPurBJetTags', 'pfJetProbabilityBJetTags', 'pfJetBProbabilityBJetTags', 'pfSimpleSecondaryVertexHighEffBJetTags',
        //'pfSimpleSecondaryVertexHighPurBJetTags', 'pfCombinedSecondaryVertexV2BJetTags', 'pfCombinedInclusiveSecondaryVertexV2BJetTags', 'pfCombinedMVAV2BJetTags'
        b_PAT_jet_pt[NPATJet]    = Myjet->pt();
        b_PAT_jet_eta[NPATJet]   = Myjet->eta();
        b_PAT_jet_phi[NPATJet]   = Myjet->phi();
        b_PAT_jet_en[NPATJet]    = Myjet->energy();
        b_PAT_jet_Btag1[NPATJet] = Myjet->bDiscriminator("pfCombinedSecondaryVertexV2BJetTags");
        b_PAT_jet_Btag2[NPATJet] = Myjet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
        b_PAT_jet_Btag3[NPATJet] = Myjet->bDiscriminator("pfCombinedMVAV2BJetTags");
        NPATJet++;
      }
    }
    if(NPATJet>0) b_NPATJet=NPATJet;

    // Trimuons
    std::vector<pat::MuonCollection::const_iterator> hightrigmuons;
    for (auto muon = muons->begin(); muon != muons->end(); ++muon) {

      if (muon->pt() > m_threshold_Mu17_pT  &&  fabs(muon->eta()) < m_threshold_Mu17_eta) {
        const pat::TriggerObjectStandAlone *mu01 = muon->triggerObjectMatchByPath("HLT_TrkMu16_DoubleTrkMu6NoFiltersNoVtx_v*");

        if((mu01 != NULL && mu01->collection() == std::string("hltGlbTrkMuonCandsNoVtx::HLT") && mu01->pt() > m_threshold_Mu17_pT)  ){
          hightrigmuons.push_back(muon);
        }
      }
    }
    //Orphan branches
    m_orphan_dimu_mass = -999.;
    m_orphan_mass = -999.;
    m_orphan_isoTk = -999.;
    m_orphan_dimu_isoTk = -999.;
    m_orphan_z = -999.;
    m_orphan_dimu_z = -999.;
    m_dimuorphan_containstrig = 0;
    m_dimuorphan_containstrig2 = 0;
    edm::Handle<pat::MuonCollection> orphans;
    iEvent.getByToken(m_muJetOrphans, orphans);
    float mu1788 = 0;
    if (muJets->size() == 1 && (*muJets)[0].numberOfDaughters() == 2 && orphans->size() == 1 ) {
      m_orphan_passOffLineSel = true;
      pat::MultiMuonCollection::const_iterator muJet = muJets->begin();
      pat::MuonCollection::const_iterator orphan = orphans->begin();
      if( muJet->muon(0)->pt() > m_threshold_Mu17_pT || muJet->muon(1)->pt() > m_threshold_Mu17_pT || orphan->pt() > m_threshold_Mu17_pT ) m_orphan_passOffLineSelPt = true;
      if((muJet->muon(0)->pt() > m_threshold_Mu17_pT && fabs(muJet->muon(0)->eta())<m_threshold_Mu17_eta) || (muJet->muon(1)->pt() > m_threshold_Mu17_pT && fabs(muJet->muon(1)->eta())<m_threshold_Mu17_eta) || (orphan->pt() > m_threshold_Mu17_pT && fabs(orphan->eta())<m_threshold_Mu17_eta)) m_orphan_passOffLineSelPtEta = true;
      m_orphan_PtOrph  = orphan->pt();
      m_orphan_EtaOrph = orphan->eta();
      m_orphan_PhiOrph = orphan->phi();
      m_orphan_PtMu0   = muJet->muon(0)->pt();
      m_orphan_EtaMu0  = muJet->muon(0)->eta();
      m_orphan_PhiMu0  = muJet->muon(0)->phi();
      m_orphan_PtMu1   = muJet->muon(1)->pt();
      m_orphan_EtaMu1  = muJet->muon(1)->eta();
      m_orphan_PhiMu1  = muJet->muon(1)->phi();
      TLorentzVector mymu0, mymu1;
      mymu0.SetPtEtaPhiM(m_orphan_PtMu0,m_orphan_EtaMu0,m_orphan_PhiMu0,0);
      mymu1.SetPtEtaPhiM(m_orphan_PtMu1,m_orphan_EtaMu1,m_orphan_PhiMu1,0);
      m_orphan_PtMu01   = (mymu0+mymu1).Pt();
      m_orphan_EtaMu01  = (mymu0+mymu1).Eta();
      m_orphan_PhiMu01  = (mymu0+mymu1).Phi();
      m_orphan_DRdiMuOrph  = sqrt( pow(m_orphan_EtaMu01-m_orphan_EtaOrph,2) + pow(TVector2::Phi_mpi_pi(m_orphan_PhiMu01-m_orphan_PhiOrph),2) );
      m_orphan_z = orphan->innerTrack()->dz(beamSpot->position());
      m_orphan_dimu_z = muJet->vertexDz(beamSpot->position());
      double triPt[3]  = {muJet->muon(0)->pt(), muJet->muon(1)->pt(), orphan->pt()};
      double triEta[3] = {fabs(muJet->muon(0)->eta()), fabs(muJet->muon(1)->eta()), fabs(orphan->eta())};
      int Index17=-1; bool found=false;
      for(int i=0; i<3; i++){
        if( found ) continue;
        if(triPt[i]>m_threshold_Mu17_pT && triEta[i]<m_threshold_Mu17_eta){ Index17 = i; found=true; }
      }
      if(Index17>-1){
         for(int i=0; i<3; i++){ if(i!=Index17 && triPt[i]>8) mu1788+=0.5; }
      }
      if( mu1788==1 ) m_orphan_passOffLineSelPt1788 = true;
      if ( muJet->muon(0)->isTrackerMuon() &&
           muJet->muon(0)->innerTrack().isNonnull() &&
           muJet->muon(1)->isTrackerMuon() &&
           muJet->muon(1)->innerTrack().isNonnull() &&
           orphan->isTrackerMuon() &&
           orphan->innerTrack().isNonnull() ) m_orphan_AllTrackerMu = true;

      if( m_orphan_passOffLineSelPtEta &&
          m_orphan_passOffLineSelPt1788 ) FillTrigInfo(triggerComposition_bb, triggerNames, NameAndNumb );

      for (auto iter = hightrigmuons.begin();  iter != hightrigmuons.end();  ++iter) {
        if( orphan->innerTrack().isAvailable() &&
            (*iter)->innerTrack().isAvailable() &&
            tamu::helpers::sameTrack(&*(orphan->innerTrack()), &*((*iter)->innerTrack()))){
          m_dimuorphan_containstrig++;
        }
      }
      for (auto iter = hightrigmuons.begin();  iter != hightrigmuons.end();  ++iter) {
        if( muJet->muon(0)->innerTrack().isAvailable() &&
            (*iter)->innerTrack().isAvailable() &&
            tamu::helpers::sameTrack(&*(muJet->muon(0)->innerTrack()), &*((*iter)->innerTrack()))) {
          m_dimuorphan_containstrig2++;
        }
        if( muJet->muon(1)->innerTrack().isAvailable() &&
            (*iter)->innerTrack().isAvailable() &&
            tamu::helpers::sameTrack(&*(muJet->muon(1)->innerTrack()), &*((*iter)->innerTrack()))) {
          m_dimuorphan_containstrig2++;
        }
      }
      m_orphan_dimu_mass = muJet->mass();
      m_orphan_mass = orphan->mass();
      //iso orphan
      double iso_track_pt_treshold = 0.5;
      m_orphan_isoTk = 0.;
      m_orphan_dimu_isoTk = 0.;
      for (reco::TrackCollection::const_iterator track = tracks->begin(); track != tracks->end(); ++track) {
        if (!muJet->sameTrack(&*track,&*(orphan->innerTrack()))) {
          double dphi = orphan->innerTrack()->phi() - track->phi();
          if (dphi > M_PI) dphi -= 2.*M_PI;
          if (dphi < -M_PI) dphi += 2.*M_PI;
          double deta = orphan->innerTrack()->eta() - track->eta();
          double dR = sqrt(pow(dphi, 2) + pow(deta, 2));
          if (dR < 0.4 && track->pt() > iso_track_pt_treshold) {
            double dz = fabs(track->dz(beamSpot->position())-orphan->innerTrack()->dz(beamSpot->position()));
            if (dz < 0.1){ m_orphan_isoTk += track->pt(); }
          }
        }
      }
      //iso dimuon-orphan
       for (reco::TrackCollection::const_iterator track = tracks->begin(); track != tracks->end(); ++track) {
         bool track_is_muon = false;
         if (muJet->sameTrack(&*track,&*(muJet->muon(0)->innerTrack())) || muJet->sameTrack(&*track,&*(muJet->muon(1)->innerTrack()))) track_is_muon = true;
         if (!track_is_muon) {
           double dphi = muJet->phi() - track->phi();
           if (dphi > M_PI) dphi -= 2.*M_PI;
           if (dphi < -M_PI) dphi += 2.*M_PI;
           double deta = muJet->eta() - track->eta();
           double dR   = sqrt(pow(dphi, 2) + pow(deta, 2));
           if (dR < 0.4 && track->pt() > iso_track_pt_treshold) {
             double dz = fabs(track->dz(beamSpot->position())-muJet->vertexDz(beamSpot->position()));
             if (dz < 0.1){ m_orphan_dimu_isoTk += track->pt(); }
           }
         }
       }
     }
   }
  //****************************************************************************
  //                          RECO LEVEL ANALYSIS FINISH
  //****************************************************************************

  //****************************************************************************
  //                            FILL BRANCHES TO TREE
  //****************************************************************************

  if(skimOutput_) { if (b_massC>-1. && b_massF>-1.) m_ttree->Fill(); }
  else m_ttree->Fill();

  if(runBBestimation_ && m_orphan_passOffLineSel) m_ttree_orphan->Fill();
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


  //****************************************************************************
  //                          RECO LEVEL BRANCHES
  //****************************************************************************

  // Reco Muons
  m_ttree->Branch("nRecoMu",  &b_nRecoMu,  "nRecoMu/I");

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

  m_ttree->Branch("selMu0_trigHLT16", &b_selMu0_trigHLT16, "selMu0_trigHLT16/O");
  m_ttree->Branch("selMu1_trigHLT16", &b_selMu1_trigHLT16, "selMu1_trigHLT16/O");
  m_ttree->Branch("selMu2_trigHLT16", &b_selMu2_trigHLT16, "selMu2_trigHLT16/O");
  m_ttree->Branch("selMu3_trigHLT16", &b_selMu3_trigHLT16, "selMu3_trigHLT16/O");

  m_ttree->Branch("selMu0_trigHLT6", &b_selMu0_trigHLT6, "selMu0_trigHLT6/O");
  m_ttree->Branch("selMu1_trigHLT6", &b_selMu1_trigHLT6, "selMu1_trigHLT6/O");
  m_ttree->Branch("selMu2_trigHLT6", &b_selMu2_trigHLT6, "selMu2_trigHLT6/O");
  m_ttree->Branch("selMu3_trigHLT6", &b_selMu3_trigHLT6, "selMu3_trigHLT6/O");

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
  m_ttree->Branch("diMuonC_FittedVtx_Lxy_rclstvtx", &b_diMuonC_FittedVtx_Lxy_rclstvtx, "diMuonC_FittedVtx_Lxy_rclstvtx/F");
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
  m_ttree->Branch("diMuonF_FittedVtx_Lxy_rclstvtx", &b_diMuonF_FittedVtx_Lxy_rclstvtx, "diMuonF_FittedVtx_Lxy_rclstvtx/F");
  m_ttree->Branch("diMuonF_FittedVtx_L",   &b_diMuonF_FittedVtx_L,   "diMuonF_FittedVtx_L/F");
  m_ttree->Branch("diMuonF_FittedVtx_dz",  &b_diMuonF_FittedVtx_dz,  "diMuonF_FittedVtx_dz/F");
/*
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
*/
  m_ttree->Branch("diMuonC_IsoTk_FittedVtx", &b_diMuonC_IsoTk_FittedVtx, "diMuonC_IsoTk_FittedVtx/F");
  m_ttree->Branch("diMuonF_IsoTk_FittedVtx", &b_diMuonF_IsoTk_FittedVtx, "diMuonF_IsoTk_FittedVtx/F");

  m_ttree->Branch("diMuons_dz_FittedVtx", &b_diMuons_dz_FittedVtx, "diMuons_dz_FittedVtx/F");
  //m_ttree->Branch("diMuons_dz_ConsistentVtx", &b_diMuons_dz_ConsistentVtx, "diMuons_dz_ConsistentVtx/F");

  //m_ttree->Branch("diMuonC_IsoTk_ConsistentVtx", &b_diMuonC_IsoTk_ConsistentVtx, "diMuonC_IsoTk_ConsistentVtx/F");
  //m_ttree->Branch("diMuonF_IsoTk_ConsistentVtx", &b_diMuonF_IsoTk_ConsistentVtx, "diMuonF_IsoTk_ConsistentVtx/F");

  m_ttree->Branch("diMuonC_m1_FittedVtx_hitpix", &b_diMuonC_m1_FittedVtx_hitpix, "diMuonC_m1_FittedVtx_hitpix/I");
  m_ttree->Branch("diMuonC_m2_FittedVtx_hitpix", &b_diMuonC_m2_FittedVtx_hitpix, "diMuonC_m2_FittedVtx_hitpix/I");
  m_ttree->Branch("diMuonF_m1_FittedVtx_hitpix", &b_diMuonF_m1_FittedVtx_hitpix, "diMuonF_m1_FittedVtx_hitpix/I");
  m_ttree->Branch("diMuonF_m2_FittedVtx_hitpix", &b_diMuonF_m2_FittedVtx_hitpix, "diMuonF_m2_FittedVtx_hitpix/I");

  m_ttree->Branch("diMuonC_m1_FittedVtx_hitpix_l2inc", &b_diMuonC_m1_FittedVtx_hitpix_l2inc, "diMuonC_m1_FittedVtx_hitpix_l2inc/I");
  m_ttree->Branch("diMuonC_m2_FittedVtx_hitpix_l2inc", &b_diMuonC_m2_FittedVtx_hitpix_l2inc, "diMuonC_m2_FittedVtx_hitpix_l2inc/I");
  m_ttree->Branch("diMuonF_m1_FittedVtx_hitpix_l2inc", &b_diMuonF_m1_FittedVtx_hitpix_l2inc, "diMuonF_m1_FittedVtx_hitpix_l2inc/I");
  m_ttree->Branch("diMuonF_m2_FittedVtx_hitpix_l2inc", &b_diMuonF_m2_FittedVtx_hitpix_l2inc, "diMuonF_m2_FittedVtx_hitpix_l2inc/I");

  m_ttree->Branch("diMuonC_m1_FittedVtx_hitpix_l3inc", &b_diMuonC_m1_FittedVtx_hitpix_l3inc, "diMuonC_m1_FittedVtx_hitpix_l3inc/I");
  m_ttree->Branch("diMuonC_m2_FittedVtx_hitpix_l3inc", &b_diMuonC_m2_FittedVtx_hitpix_l3inc, "diMuonC_m2_FittedVtx_hitpix_l3inc/I");
  m_ttree->Branch("diMuonF_m1_FittedVtx_hitpix_l3inc", &b_diMuonF_m1_FittedVtx_hitpix_l3inc, "diMuonF_m1_FittedVtx_hitpix_l3inc/I");
  m_ttree->Branch("diMuonF_m2_FittedVtx_hitpix_l3inc", &b_diMuonF_m2_FittedVtx_hitpix_l3inc, "diMuonF_m2_FittedVtx_hitpix_l3inc/I");

  m_ttree->Branch("diMuonC_m1_FittedVtx_hitpix_Phase1", &b_diMuonC_m1_FittedVtx_hitpix_Phase1, "diMuonC_m1_FittedVtx_hitpix_Phase1/I");
  m_ttree->Branch("diMuonC_m2_FittedVtx_hitpix_Phase1", &b_diMuonC_m2_FittedVtx_hitpix_Phase1, "diMuonC_m2_FittedVtx_hitpix_Phase1/I");
  m_ttree->Branch("diMuonF_m1_FittedVtx_hitpix_Phase1", &b_diMuonF_m1_FittedVtx_hitpix_Phase1, "diMuonF_m1_FittedVtx_hitpix_Phase1/I");
  m_ttree->Branch("diMuonF_m2_FittedVtx_hitpix_Phase1", &b_diMuonF_m2_FittedVtx_hitpix_Phase1, "diMuonF_m2_FittedVtx_hitpix_Phase1/I");
/*
  m_ttree->Branch("b_diMuonC_m1_FittedVtx_HBV", &b_diMuonC_m1_FittedVtx_HBV, "diMuonC_m1_FittedVtx_HBV/I");
  m_ttree->Branch("b_diMuonC_m2_FittedVtx_HBV", &b_diMuonC_m2_FittedVtx_HBV, "diMuonC_m2_FittedVtx_HBV/I");
  m_ttree->Branch("b_diMuonF_m1_FittedVtx_HBV", &b_diMuonF_m1_FittedVtx_HBV, "diMuonF_m1_FittedVtx_HBV/I");
  m_ttree->Branch("b_diMuonF_m2_FittedVtx_HBV", &b_diMuonF_m2_FittedVtx_HBV, "diMuonF_m2_FittedVtx_HBV/I");
  m_ttree->Branch("b_diMuonC_m1_FittedVtx_MHAV", &b_diMuonC_m1_FittedVtx_MHAV, "diMuonC_m1_FittedVtx_MHAV/I");
  m_ttree->Branch("b_diMuonC_m2_FittedVtx_MHAV", &b_diMuonC_m2_FittedVtx_MHAV, "diMuonC_m2_FittedVtx_MHAV/I");
  m_ttree->Branch("b_diMuonF_m1_FittedVtx_MHAV", &b_diMuonF_m1_FittedVtx_MHAV, "diMuonF_m1_FittedVtx_MHAV/I");
  m_ttree->Branch("b_diMuonF_m2_FittedVtx_MHAV", &b_diMuonF_m2_FittedVtx_MHAV, "diMuonF_m2_FittedVtx_MHAV/I");
*/
  // bb Estimation
  m_ttree->Branch("massC",                          &b_massC,                          "massC/F");
  m_ttree->Branch("massF",                          &b_massF,                          "massF/F");
  m_ttree->Branch("isoC_1mm",                       &b_isoC_1mm,                       "isoC_1mm/F");
  m_ttree->Branch("isoF_1mm",                       &b_isoF_1mm,                       "isoF_1mm/F");

  // RECO Level Selectors
  m_ttree->Branch("is1SelMu17",                     &b_is1SelMu17,                     "is1SelMu17/O");
  m_ttree->Branch("is2SelMu8",                      &b_is2SelMu8,                      "is2SelMu8/O");
  m_ttree->Branch("is3SelMu8",                      &b_is3SelMu8,                      "is3SelMu8/O");
  m_ttree->Branch("is4SelMu8",                      &b_is4SelMu8,                      "is4SelMu8/O");

  m_ttree->Branch("is2MuJets",                      &b_is2MuJets,                      "is2MuJets/O");
  m_ttree->Branch("is2DiMuons",                     &b_is2DiMuons,                     "is2DiMuons/O");
  m_ttree->Branch("is2DiMuonsFittedVtxOK",          &b_is2DiMuonsFittedVtxOK,          "is2DiMuonsFittedVtxOK/O");
  m_ttree->Branch("is2DiMuonsFittedVtxOK_KF",       &b_is2DiMuonsFittedVtxOK_KF,       "is2DiMuonsFittedVtxOK_KF/O");
  m_ttree->Branch("is2DiMuonsFittedVtxOK_VS",       &b_is2DiMuonsFittedVtxOK_VS,       "is2DiMuonsFittedVtxOK_VS/O");


  //m_ttree->Branch("is2DiMuonsConsistentVtxOK",      &b_is2DiMuonsConsistentVtxOK,      "is2DiMuonsConsistentVtxOK/O");
  m_ttree->Branch("isDiMuonHLTFired",               &b_isDiMuonHLTFired,               "isDiMuonHLTFired/O");
  m_ttree->Branch("is2DiMuonsMassOK_FittedVtx",     &b_is2DiMuonsMassOK_FittedVtx,     "is2DiMuonsMassOK_FittedVtx/O");
  //m_ttree->Branch("is2DiMuonsMassOK_ConsistentVtx", &b_is2DiMuonsMassOK_ConsistentVtx, "is2DiMuonsMassOK_ConsistentVtx/O");
  m_ttree->Branch("isVertexOK",                     &b_isVertexOK,                     "isVertexOK/O");

  m_ttree->Branch("hltPaths",  &b_hltPaths);
  m_ttree->Branch("Mass4Mu",&b_Mass4Mu,"Mass4Mu/F");


  // Orpahn Muon
  if(runBBestimation_){
    m_ttree_orphan = tFileService->make<TTree>("Events_orphan", "Events_orphan");
    m_ttree_orphan->Branch("run", &b_run, "run/I");
    m_ttree_orphan->Branch("lumi", &b_lumi, "lumi/I");
    m_ttree_orphan->Branch("event", &b_event, "event/I");
    m_ttree_orphan->Branch("orph_mass", &m_orphan_mass, "orph_mass/F");
    m_ttree_orphan->Branch("orph_dimu_mass", &m_orphan_dimu_mass, "orph_dimu_mass/F");
    m_ttree_orphan->Branch("containstrig", &m_dimuorphan_containstrig, "containstrig/I");
    m_ttree_orphan->Branch("containstrig2", &m_dimuorphan_containstrig2, "containstrig2/I");
    m_ttree_orphan->Branch("orph_z", &m_orphan_z, "orph_z/F");
    m_ttree_orphan->Branch("orph_dimu_z", &m_orphan_dimu_z, "orph_dimu_z/F");
    m_ttree_orphan->Branch("orph_isoTk", &m_orphan_isoTk, "orph_isoTk/F");
    m_ttree_orphan->Branch("orph_dimu_isoTk", &m_orphan_dimu_isoTk, "orph_dimu_isoTk/F");
    m_ttree_orphan->Branch("orph_passOffLineSel", &m_orphan_passOffLineSel, "orph_passOffLineSel/O");
    m_ttree_orphan->Branch("orph_passOffLineSelPt", &m_orphan_passOffLineSelPt, "orph_passOffLineSelPt/O");
    m_ttree_orphan->Branch("orph_passOffLineSelPtEta", &m_orphan_passOffLineSelPtEta, "orph_passOffLineSelPtEta/O");
    m_ttree_orphan->Branch("orph_passOffLineSelPt1788", &m_orphan_passOffLineSelPt1788, "orph_passOffLineSelPt1788/O");
    m_ttree_orphan->Branch("orph_AllTrackerMu", &m_orphan_AllTrackerMu, "orph_AllTrackerMu/O");
    m_ttree_orphan->Branch("orph_PtOrph", &m_orphan_PtOrph, "orph_PtOrph/F");
    m_ttree_orphan->Branch("orph_EtaOrph", &m_orphan_EtaOrph, "orph_EtaOrph/F");
    m_ttree_orphan->Branch("orph_PhiOrph", &m_orphan_PhiOrph, "orph_PhiOrph/F");
    m_ttree_orphan->Branch("orph_PtMu0", &m_orphan_PtMu0, "orph_PtMu0/F");
    m_ttree_orphan->Branch("orph_EtaMu0", &m_orphan_EtaMu0, "orph_EtaMu0/F");
    m_ttree_orphan->Branch("orph_PhiMu0", &m_orphan_PhiMu0, "orph_PhiMu0/F");
    m_ttree_orphan->Branch("orph_PtMu1", &m_orphan_PtMu1, "orph_PtMu1/F");
    m_ttree_orphan->Branch("orph_EtaMu1", &m_orphan_EtaMu1, "orph_EtaMu1/F");
    m_ttree_orphan->Branch("orph_PhiMu1", &m_orphan_PhiMu1, "orph_PhiMu1/F");
    m_ttree_orphan->Branch("orph_PtMu01", &m_orphan_PtMu01, "orph_PtMu01/F");
    m_ttree_orphan->Branch("orph_EtaMu01", &m_orphan_EtaMu01, "orph_EtaMu01/F");
    m_ttree_orphan->Branch("orph_PhiMu01", &m_orphan_PhiMu01, "orph_PhiMu01/F");
    m_ttree_orphan->Branch("orph_DRdiMuOrph", &m_orphan_DRdiMuOrph, "orph_DRdiMuOrph/F");
    m_ttree_orphan->Branch("NPATJet",       &b_NPATJet,"NPATJet/I");
    m_ttree_orphan->Branch("PAT_jet_pt",    &b_PAT_jet_pt,"PAT_jet_pt[NPATJet]/F");
    m_ttree_orphan->Branch("PAT_jet_eta",   &b_PAT_jet_eta,"PAT_jet_eta[NPATJet]/F");
    m_ttree_orphan->Branch("PAT_jet_phi",   &b_PAT_jet_phi,"PAT_jet_phi[NPATJet]/F");
    m_ttree_orphan->Branch("PAT_jet_en",    &b_PAT_jet_en,"PAT_jet_en[NPATJet]/F");
    m_ttree_orphan->Branch("PAT_jet_Btag1", &b_PAT_jet_Btag1,"PAT_jet_Btag1[NPATJet]/F");
    m_ttree_orphan->Branch("PAT_jet_Btag2", &b_PAT_jet_Btag2,"PAT_jet_Btag2[NPATJet]/F");
    m_ttree_orphan->Branch("PAT_jet_Btag3", &b_PAT_jet_Btag3,"PAT_jet_Btag3[NPATJet]/F");
  }
}

// ------------ method called once each job just after ending the event loop  ------------
void
CutFlowAnalyzer::endJob()
{
  using namespace std;

  cout << "END JOB" << endl;

   cout << "Total number of events:          " << m_events << endl;

  // do not analyzer in case when there are no events!
  if (m_events==0) return;

   cout << "Total number of events with 4mu: " << m_events4GenMu << " fraction: " <<  m_events4GenMu/m_events << endl;

  if (m_fillGenLevel){
     cout << "********** GEN **********" << endl;
     cout << "Selection              " << "nEv"         << " \t RelEff"                                       << " \t Eff" << endl;
     cout << "pT1>17 |eta1|<0.9:       " << m_events1GenMu17 << " \t" << (float)m_events1GenMu17/(float)m_events << " \t" << (float)m_events1GenMu17/(float)m_events << endl;
     cout << "pT2>8  |eta2|<2.4:       " << m_events2GenMu8  << " \t" << (float)m_events2GenMu8/(float)m_events1GenMu17  << " \t" << (float)m_events2GenMu8/(float)m_events << endl;
     cout << "pT3>8  |eta2|<2.4:       " << m_events3GenMu8  << " \t" << (float)m_events3GenMu8/(float)m_events2GenMu8   << " \t" << (float)m_events3GenMu8/(float)m_events << endl;
     cout << "pT4>8  |eta2|<2.4:       " << m_events4GenMu8  << " \t" << (float)m_events4GenMu8/(float)m_events3GenMu8   << " \t" << (float)m_events4GenMu8/(float)m_events << endl;
     cout << "Basic MC Acceptance:     " << (float)m_events4GenMu8/(float)m_events << endl;
  }
   cout << "********** RECO **********" << endl;
   cout << "Selection                " << "nEv"                   << " \t RelEff"                                                         << " \t Eff" << endl;
   cout << "m_events1SelMu17:        " << m_events1SelMu17        << " \t" << (float)m_events1SelMu17/(float)m_events                << " \t" << (float)m_events1SelMu17/(float)m_events        << endl;
   cout << "m_events2SelMu8:         " << m_events2SelMu8         << " \t" << (float)m_events2SelMu8/(float)m_events1SelMu17              << " \t" << (float)m_events2SelMu8/(float)m_events         << endl;
   cout << "m_events3SelMu8:         " << m_events3SelMu8         << " \t" << (float)m_events3SelMu8/(float)m_events2SelMu8               << " \t" << (float)m_events3SelMu8/(float)m_events         << endl;
   cout << "m_events4SelMu8:         " << m_events4SelMu8         << " \t" << (float)m_events4SelMu8/(float)m_events3SelMu8               << " \t" << (float)m_events4SelMu8/(float)m_events         << endl;

   cout << "Basic Acceptance:        " << (float)m_events4SelMu8/(float)m_events << endl;
  if (m_fillGenLevel)  cout << "Basic MC Accept. a_gen:  " << (float)m_events4GenMu8/(float)m_events << endl;

   cout << "m_events2MuJets:         " << m_events2MuJets         << " \t" << (float)m_events2MuJets/(float)m_events4SelMu8               << " \t" << (float)m_events2MuJets/(float)m_events         << endl;
   cout << "m_events2DiMuons:        " << m_events2DiMuons        << " \t" << (float)m_events2DiMuons/(float)m_events2MuJets              << " \t" << (float)m_events2DiMuons/(float)m_events        << endl;

   cout << " *** FITTED VERTEXES *** " << endl;
  cout << m_events << endl;
  cout << m_events1GenMu17                  << endl;
  cout << m_events2GenMu8                   << endl;
  cout << m_events3GenMu8                   << endl;
  cout << m_events4GenMu8                   << endl;
  cout << m_events1SelMu17                  << endl;
  cout << m_events2SelMu8                   << endl;
  cout << m_events3SelMu8                   << endl;
  cout << m_events4SelMu8                   << endl;
  cout << m_events2MuJets                   << endl;
  cout << m_events2DiMuons                  << endl;
}

void CutFlowAnalyzer::FillTrigInfo( TH1F * h1, const edm::TriggerNames& triggerNames, std::map<int,std::string> nameAndNumb )
{
  for( unsigned int i=0; i<nameAndNumb.size(); i++ ){
    for (unsigned int itrig = 0; itrig != triggerNames.size(); ++itrig) {
      TString trigName = triggerNames.triggerName(itrig);
      std::string trigNameStr(trigName.Data());
      if (trigNameStr == nameAndNumb[i]){
	h1->Fill(i);
      }
    }
  }
}

bool CutFlowAnalyzer::wasRecoMuonTriggerMatched(const pat::Muon* muon,
                                                const std::string& name, const float pt)
{
  const pat::TriggerObjectStandAlone *mu01  = muon->triggerObjectMatchByPath(name);

  return (mu01 != NULL &&
          mu01->collection() == std::string("hltGlbTrkMuonCandsNoVtx::HLT") &&
          mu01->pt() >= pt);
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
//Indentation change
//define this as a plug-in
DEFINE_FWK_MODULE(CutFlowAnalyzer);
