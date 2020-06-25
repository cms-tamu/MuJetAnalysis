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
#include "HLTrigger/HLTcore/interface/HLTPrescaleProvider.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "PhysicsTools/RecoUtils/interface/CheckHitPattern.h"
#include "RecoTracker/MeasurementDet/interface/MeasurementTrackerEvent.h"
#include "TrackingTools/PatternTools/interface/Trajectory.h"

#include "MuJetAnalysis/DataFormats/interface/MultiMuon.h"
#include "MuJetAnalysis/AnalysisTools/interface/Helpers.h"

#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

// user include files
#include "TTree.h"
#include "TRandom3.h"
#include "TMath.h"
#include "TVector2.h"
#include "TLorentzVector.h"

//******************************************************************************
//                           Class declaration
//******************************************************************************

class CutFlowAnalyzer_MiniAOD : public edm::EDAnalyzer
{
private:
  HLTPrescaleProvider hltPSProv_;
  std::string hltProcess_; //name of HLT process, usually "HLT"

public:
  explicit CutFlowAnalyzer_MiniAOD(const edm::ParameterSet&);
  ~CutFlowAnalyzer_MiniAOD();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  void FillTrigInfo( TH1F *h1, const edm::TriggerNames&, std::map<int,std::string> nameAndNumb );
  TH1F* triggerComposition;
  TH1F* triggerComposition_bb;

private:
  virtual void beginJob() ;
  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

  //virtual void endRun(edm::Run const&, edm::EventSetup const&);
  //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

  edm::ParameterSet param_;
  edm::EDGetTokenT<MeasurementTrackerEvent> measurementTrkToken_;

  //****************************************************************************
  //                          THRESHOLDS
  //****************************************************************************

  Float_t m_threshold_Mu17_pT;
  Float_t m_threshold_Mu17_eta;
  Float_t m_threshold_Mu8_pT;
  Float_t m_threshold_Mu8_eta;
  //For HLT eff
  Float_t m_HLT_Mu16_pT;
  Float_t m_HLT_Mu6_pT;
  Float_t m_HLT_Mu_eta;

  Float_t m_threshold_DiMuons_Iso_dR;
  Float_t m_threshold_DiMuons_Iso_dz;
  Float_t m_threshold_DiMuons_Iso_pT;
  //To be used in orphan-dimuon iso
  Float_t iso_track_pt_threshold;
  Float_t iso_track_dR_threshold;
  Float_t iso_track_dz_threshold;

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

  Int_t b_npv =-1;

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

  // GEN Level Selectors
  Bool_t b_is4GenMu;
  Bool_t b_is1GenMu17;
  Bool_t b_is2GenMu8;
  Bool_t b_is3GenMu8;
  Bool_t b_is4GenMu8;

  // For HLT eff
  Bool_t b_has1GenMu16;
  Bool_t b_has1GenMu6;
  Bool_t b_has1GenMu16Mu6Mu6;

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

  Float_t b_genA_dPhi;//Use phi of two A
  Float_t b_genA_dEta;
  Float_t b_genA_dR;

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

  Float_t b_genA0Mu0_pt;
  Float_t b_genA0Mu1_pt;
  Float_t b_genA1Mu0_pt;
  Float_t b_genA1Mu1_pt;

  Float_t b_genA0Mu0_eta;
  Float_t b_genA0Mu1_eta;
  Float_t b_genA1Mu0_eta;
  Float_t b_genA1Mu1_eta;

  Float_t b_genA0Mu0_phi;
  Float_t b_genA0Mu1_phi;
  Float_t b_genA1Mu0_phi;
  Float_t b_genA1Mu1_phi;

  Float_t b_genA0Mu0_charge;
  Float_t b_genA0Mu1_charge;
  Float_t b_genA1Mu0_charge;
  Float_t b_genA1Mu1_charge;

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

  //Geometry of muons from same boson
  Float_t b_genA0Mu_dEta;
  Float_t b_genA1Mu_dEta;
  Float_t b_genA0Mu_dPhi;
  Float_t b_genA1Mu_dPhi;
  Float_t b_genA0Mu_dR;
  Float_t b_genA1Mu_dR;
  Float_t b_genA0Mu_dCharge;
  Float_t b_genA1Mu_dCharge;//Should be 2 or -2
  Float_t b_genA0Mu_dPt;
  Float_t b_genA1Mu_dPt;
  Float_t b_genA0Mu_RPt;
  Float_t b_genA1Mu_RPt;

  //Geometry of dimu
  //Use muons from the same A
  Float_t b_genDiMu0_Eta;
  Float_t b_genDiMu1_Eta;
  Float_t b_genDiMu0_Phi;
  Float_t b_genDiMu1_Phi;
  Float_t b_genDiMu0_M;
  Float_t b_genDiMu1_M;
  Float_t b_genDiMu0_Pt;
  Float_t b_genDiMu1_Pt;
  Float_t b_genDiMu_dPhi;
  Float_t b_genDiMu_dEta;
  Float_t b_genDiMu_dR;
  Float_t b_genDiMu_dM;
  //Use muons from different A
  Float_t b_genFakeDiMu0_Eta;
  Float_t b_genFakeDiMu1_Eta;
  Float_t b_genFakeDiMu0_Phi;
  Float_t b_genFakeDiMu1_Phi;
  Float_t b_genFakeDiMu0_M;
  Float_t b_genFakeDiMu1_M;
  Float_t b_genFakeDiMu0_Pt;
  Float_t b_genFakeDiMu1_Pt;
  Float_t b_genFakeDiMu_dPhi;
  Float_t b_genFakeDiMu_dEta;
  Float_t b_genFakeDiMu_dR;
  Float_t b_genFakeDiMu_dM;
  //ddPhi
  Float_t b_gen_ddPhi;

  //****************************************************************************
  //          HLT LEVEL VARIABLES, BRANCHES, COUNTERS AND SELECTORS
  //****************************************************************************

  std::vector<std::string> signalHltPaths_;
  std::vector<std::string> controlHltPaths_;
  std::vector<std::string> l1algos_;
  std::vector<std::string> b_hltPaths;
  bool histo_name;
  std::map<int,std::string> NameAndNumb;
  //****************************************************************************
  //          RECO LEVEL VARIABLES, BRANCHES, COUNTERS AND SELECTORS
  //****************************************************************************

  // Labels to access
  edm::EDGetTokenT<pat::MuonCollection> m_muons;        // reconstructed muons
  edm::EDGetTokenT<pat::MultiMuonCollection> m_muPairs;
  edm::EDGetTokenT<pat::MultiMuonCollection> m_muJets;
  edm::EDGetTokenT<pat::MuonCollection> m_muJetOrphans;
  edm::EDGetTokenT<reco::BeamSpot> m_beamSpot;
  edm::EDGetTokenT<reco::TrackCollection> m_tracks;
  edm::EDGetTokenT<reco::GenParticleCollection> m_genParticles;
  edm::EDGetTokenT<edm::TriggerResults> m_trigRes;
  //edm::EDGetTokenT<L1GlobalTriggerReadoutRecord> m_L1Res;
  edm::EDGetTokenT<reco::TrackCollection> m_trackRef;
  edm::EDGetTokenT< std::vector<Trajectory> > m_traj;
  edm::EDGetTokenT<reco::VertexCollection> m_primaryVertices;
  edm::EDGetTokenT<reco::VertexCollection> m_secondaryVertices;
  edm::EDGetTokenT<std::vector<pat::Jet> > m_PATJet;

  edm::EDGetTokenT<std::vector<PileupSummaryInfo> > m_pileupCollection;

  Int_t         m_nThrowsConsistentVertexesCalculator;
  Int_t         m_barrelPixelLayer;
  Int_t         m_endcapPixelLayer;

  unsigned int  m_randomSeed;
  TRandom3      m_trandom3;

  Float_t b_massC;
  Float_t b_massF;

  Float_t b_muJetC_Mu0_pt;
  Float_t b_muJetC_Mu1_pt;
  Float_t b_muJetF_Mu0_pt;
  Float_t b_muJetF_Mu1_pt;

  Float_t b_muJetC_Mu0_eta;
  Float_t b_muJetC_Mu1_eta;
  Float_t b_muJetF_Mu0_eta;
  Float_t b_muJetF_Mu1_eta;

  Float_t b_muJetC_Mu0_phi;
  Float_t b_muJetC_Mu1_phi;
  Float_t b_muJetF_Mu0_phi;
  Float_t b_muJetF_Mu1_phi;

  Float_t b_muJetC_Mu0_charge;
  Float_t b_muJetC_Mu1_charge;
  Float_t b_muJetF_Mu0_charge;
  Float_t b_muJetF_Mu1_charge;

  Float_t b_reco4mu_pt;
  Float_t b_reco4mu_eta;
  Float_t b_reco4mu_phi;
  Float_t b_reco4mu_m;

  Float_t b_recoFakeDiMu0_pt;
  Float_t b_recoFakeDiMu0_eta;
  Float_t b_recoFakeDiMu0_phi;
  Float_t b_recoFakeDiMu0_m;

  Float_t b_recoFakeDiMu1_pt;
  Float_t b_recoFakeDiMu1_eta;
  Float_t b_recoFakeDiMu1_phi;
  Float_t b_recoFakeDiMu1_m;

  Float_t b_dEtaRePairedDimuA;
  Float_t b_dEtaRePairedDimuB;
  Float_t b_dPhiRePairedDimuA;
  Float_t b_dPhiRePairedDimuB;
  Float_t b_dRrePairedDimuA;
  Float_t b_dRrePairedDimuB;

  Float_t b_recoRePaired2muleading_m;
  Float_t b_recoRePaired2mutrailing_m;
  Float_t b_recoRePaired2muleading_dR;
  Float_t b_recoRePaired2mutrailing_dR;

  Float_t b_isoC_1mm;
  Float_t b_isoF_1mm;

  // Selectors and counters of events with ...
  Bool_t b_is1SelMu17;
  Int_t  m_events1SelMu17; // ... with 1 selected reco muon: pT > 17 GeV, |eta| < 0.9

  Bool_t b_is2SelMu8;
  Int_t  m_events2SelMu8;  // ... with 2 selected reco muon: pT > 8 GeV,  |eta| < 2.4

  Bool_t b_is3SelMu8;
  Int_t  m_events3SelMu8;  // ... with 3 selected reco muon: pT > 8 GeV,  |eta| < 2.4

  Bool_t b_is4SelMu8;
  Int_t  m_events4SelMu8;  // ... with 4 selected reco muon: pT > 8 GeV,  |eta| < 2.4

  Bool_t b_is2MuJets;
  Int_t  m_events2MuJets;  // ... with 2 muon jets

  Bool_t b_is2DiMuons;
  Int_t  m_events2DiMuons; // ... with 2 dimuons (dimuon = muon jet with 2 muons)

  Bool_t b_is2DiMuonsFittedVtxOK;

  Bool_t b_isSignalHLTFired;
  //Start DEBUG HLT paths
  /*
  Bool_t b_isSignalHLT_0_Fired;
  Bool_t b_isSignalHLT_1_Fired;
  Bool_t b_isSignalHLT_2_Fired;
  Bool_t b_isSignalHLT_3_Fired;
  Bool_t b_isSignalHLT_4_Fired;
  Bool_t b_isSignalHLT_5_Fired;
  Bool_t b_isSignalHLT_6_Fired;
  Bool_t b_isSignalHLT_7_Fired;
  Bool_t b_isSignalHLT_8_Fired;
  Bool_t b_isSignalHLT_9_Fired;
  Bool_t b_isSignalHLT_10_Fired;
  Bool_t b_isSignalHLT_11_Fired;
  Bool_t b_isSignalHLT_12_Fired;
  Bool_t b_isSignalHLT_13_Fired;
  Bool_t b_isSignalHLT_14_Fired;
  Bool_t b_isSignalHLT_15_Fired;
  Bool_t b_isSignalHLT_16_Fired;
  Bool_t b_isSignalHLT_17_Fired;
  Bool_t b_isSignalHLT_18_Fired;
  Bool_t b_isSignalHLT_19_Fired;*/
  //End DEBUG HLT paths
  Bool_t b_isControlHLT16Fired;
  Bool_t b_isControlHLT6Fired;
  Bool_t b_isSignalHLTL1Fired;

  Bool_t b_is2DiMuonsMassOK_FittedVtx;
  Bool_t b_isVertexOK;
  Bool_t b_orphan_isVertexOK;

  // Reco branches in ROOT tree
  Int_t b_nRecoMu;
  Int_t b_nSAMu;
  Int_t b_dimuC_nSAMu;
  Int_t b_dimuF_nSAMu;
  Int_t b_nNonTrackerMu;
  Int_t b_dimuC_nNonTrackerMu;
  Int_t b_dimuF_nNonTrackerMu;
  Int_t b_nMuPairs;
  Int_t b_nMuJets;
  Int_t b_nOrphans;
  Float_t b_nDaughterPerMuPair;
  Float_t b_nDaughterPerMuJet;

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

  Float_t b_diMuonC_FittedVtx_dR;
  Float_t b_diMuonC_FittedVtx_m;
  Float_t b_diMuonC_FittedVtx_px;
  Float_t b_diMuonC_FittedVtx_py;
  Float_t b_diMuonC_FittedVtx_pz;
  Float_t b_diMuonC_FittedVtx_eta;
  Float_t b_diMuonC_FittedVtx_phi;
  Float_t b_diMuonC_FittedVtx_vx;
  Float_t b_diMuonC_FittedVtx_vy;
  Float_t b_diMuonC_FittedVtx_vz;
  Float_t b_diMuonC_FittedVtx_Lxy;
  Float_t b_diMuonC_FittedVtx_L;
  Float_t b_diMuonC_FittedVtx_dz;
  Float_t b_diMuonC_FittedVtx_chi2;
  Float_t b_diMuonC_FittedVtx_ndof;
  Float_t b_diMuonC_FittedVtx_prob;

  Float_t b_diMuonF_FittedVtx_dR;
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
  Float_t b_diMuonF_FittedVtx_chi2;
  Float_t b_diMuonF_FittedVtx_ndof;
  Float_t b_diMuonF_FittedVtx_prob;

  Int_t b_nMuHasValidHitInPixel;//# of muons in 2 signal dimu with valid hit in pixel
  Int_t b_diMuonC_m1_FittedVtx_hitpix_Phase1;
  Int_t b_diMuonC_m2_FittedVtx_hitpix_Phase1;
  Int_t b_diMuonF_m1_FittedVtx_hitpix_Phase1;
  Int_t b_diMuonF_m2_FittedVtx_hitpix_Phase1;

  Int_t b_diMuonC_m1_FittedVtx_ValidPixelHits;
  Int_t b_diMuonC_m2_FittedVtx_ValidPixelHits;
  Int_t b_diMuonF_m1_FittedVtx_ValidPixelHits;
  Int_t b_diMuonF_m2_FittedVtx_ValidPixelHits;

  Int_t b_diMuonC_m1_FittedVtx_ValidPixelBarrelHits;
  Int_t b_diMuonC_m2_FittedVtx_ValidPixelBarrelHits;
  Int_t b_diMuonF_m1_FittedVtx_ValidPixelBarrelHits;
  Int_t b_diMuonF_m2_FittedVtx_ValidPixelBarrelHits;

  Int_t b_diMuonC_m1_FittedVtx_ValidPixelEndcapHits;
  Int_t b_diMuonC_m2_FittedVtx_ValidPixelEndcapHits;
  Int_t b_diMuonF_m1_FittedVtx_ValidPixelEndcapHits;
  Int_t b_diMuonF_m2_FittedVtx_ValidPixelEndcapHits;

  Int_t b_diMuonC_m1_FittedVtx_pixelLayersWithMeasurement;
  Int_t b_diMuonC_m2_FittedVtx_pixelLayersWithMeasurement;
  Int_t b_diMuonF_m1_FittedVtx_pixelLayersWithMeasurement;
  Int_t b_diMuonF_m2_FittedVtx_pixelLayersWithMeasurement;

  Float_t b_diMuons_dz_FittedVtx;

  Float_t b_diMuonC_IsoTk_FittedVtx;
  Float_t b_diMuonF_IsoTk_FittedVtx;
  Float_t b_diMuonCMu0_IsoTk0p3_FittedVtx;
  Float_t b_diMuonCMu0_IsoTk0p4_FittedVtx;
  Float_t b_diMuonCMu0_IsoTk0p5_FittedVtx;
  Float_t b_diMuonCMu1_IsoTk0p3_FittedVtx;
  Float_t b_diMuonCMu1_IsoTk0p4_FittedVtx;
  Float_t b_diMuonCMu1_IsoTk0p5_FittedVtx;
  Float_t b_diMuonFMu0_IsoTk0p3_FittedVtx;
  Float_t b_diMuonFMu0_IsoTk0p4_FittedVtx;
  Float_t b_diMuonFMu0_IsoTk0p5_FittedVtx;
  Float_t b_diMuonFMu1_IsoTk0p3_FittedVtx;
  Float_t b_diMuonFMu1_IsoTk0p4_FittedVtx;
  Float_t b_diMuonFMu1_IsoTk0p5_FittedVtx;

  bool skimOutput_; //fill only events with 2 good dimuons
  bool useFinalDecision_;//L1 fin-OR

  Int_t b_NPATJet;
  Int_t b_NPATJetTightB;
  Int_t b_NPATJetMediumB;
  Int_t b_NPATJetLooseB;
  Float_t b_PAT_jet_pt[100];
  Float_t b_PAT_jet_eta[100];
  Float_t b_PAT_jet_phi[100];
  Float_t b_PAT_jet_E[100];
  Float_t b_PAT_jet_CSVv2[100];

  //For Control Region Events
  Bool_t  m_orphan_passOffLineSel;
  Bool_t  m_orphan_passOffLineSelPtEta;
  Bool_t  m_orphan_AllTrackerMu;

  Int_t m_dimuorphan_containstrig;
  Int_t m_dimuorphan_containstrig2;
  Int_t m_orphan_dimu_nSAMu;
  Int_t m_orphan_dimu_nNonTrackerMu;
  Int_t m_orphan_nSAMu;
  Int_t m_orphan_nNonTrackerMu;
  Int_t m_orphan_dimu_Mu0_hitpix_Phase1;
  Int_t m_orphan_dimu_Mu1_hitpix_Phase1;
  Int_t m_orphan_dimu_Mu0_ValidPixelHits;
  Int_t m_orphan_dimu_Mu1_ValidPixelHits;
  Int_t m_orphan_dimu_Mu0_ValidPixelBarrelHits;
  Int_t m_orphan_dimu_Mu1_ValidPixelBarrelHits;
  Int_t m_orphan_dimu_Mu0_ValidPixelEndcapHits;
  Int_t m_orphan_dimu_Mu1_ValidPixelEndcapHits;
  Int_t m_orphan_dimu_Mu0_pixelLayersWithMeasurement;
  Int_t m_orphan_dimu_Mu1_pixelLayersWithMeasurement;

  Float_t m_orphan_dimu_dR;
  Float_t m_orphan_dimu_mass;
  Float_t m_orphan_dimu_z;
  Float_t m_orphan_dimu_Lxy;
  Float_t m_orphan_dimu_L;
  Float_t m_orphan_dimu_chi2;
  Float_t m_orphan_dimu_ndof;
  Float_t m_orphan_dimu_prob;
  Float_t m_orphan_dimu_isoTk;
  Float_t m_orphan_dimu_Mu0_isoTk0p3;
  Float_t m_orphan_dimu_Mu0_isoTk0p4;
  Float_t m_orphan_dimu_Mu0_isoTk0p5;
  Float_t m_orphan_dimu_Mu1_isoTk0p3;
  Float_t m_orphan_dimu_Mu1_isoTk0p4;
  Float_t m_orphan_dimu_Mu1_isoTk0p5;
  Float_t m_orphan_isoTk;

  Float_t m_orphan_PtOrph;
  Float_t m_orphan_EtaOrph;
  Float_t m_orphan_PtMu0;
  Float_t m_orphan_EtaMu0;
  Float_t m_orphan_PtMu1;
  Float_t m_orphan_EtaMu1;
};

CutFlowAnalyzer_MiniAOD::CutFlowAnalyzer_MiniAOD(const edm::ParameterSet& iConfig):
//Add for accessing L1 decision   @Wei SHI, Mar 11, 2019
hltPSProv_(iConfig,consumesCollector(),*this),//it needs a referernce to the calling module for some reason, hence the *this
hltProcess_(iConfig.getParameter<std::string>("hltProcess"))
{

  //****************************************************************************
  //                          SET THRESHOLDS
  //****************************************************************************

  m_threshold_Mu17_pT  = 17.0; // min pT in GeV      //These values are set by trigger efficiencies and detector geometry so may be left hard-coded
  m_threshold_Mu17_eta =  0.9; // max eta in Barrel  //These values are set by trigger efficiencies and detector geometry so may be left hard-coded
  m_threshold_Mu8_pT   =  8.0; // min pT in GeV      //These values are set by trigger efficiencies and detector geometry so may be left hard-coded
  m_threshold_Mu8_eta  =  2.4; // max eta in Endcaps //These values are set by trigger efficiencies and detector geometry so may be left hard-coded

  m_HLT_Mu16_pT = 16.0; //High pT (GeV) leg of the signal HLT
  m_HLT_Mu6_pT  =  6.0; //Low  pT (GeV) leg of the signal HLT
  m_HLT_Mu_eta  =  2.5; //abs(eta) restriction of the signal HLT

  m_threshold_DiMuons_Iso_dR = 0.4; // Isolation cone              //There is no real way to avoid hard-coding this value
  m_threshold_DiMuons_Iso_dz = 0.1; // Track displacement [cm]     //There is no real way to avoid hard-coding this value
  m_threshold_DiMuons_Iso_pT = 0.5; // Track pT [GeV]              //There is no real way to avoid hard-coding this value
  //To be used in orphan-dimuon iso
  iso_track_dR_threshold = 0.4;
  iso_track_dz_threshold = 0.1;
  iso_track_pt_threshold = 0.5;

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

  signalHltPaths_  = iConfig.getParameter<std::vector<std::string> >("signalHltPaths");
  controlHltPaths_ = iConfig.getParameter<std::vector<std::string> >("controlHltPaths");
  l1algos_         = iConfig.getParameter<std::vector<std::string> >("l1algos");//l1 seeds for signal

  //****************************************************************************
  //                 SET RECO LEVEL VARIABLES AND COUNTERS
  //****************************************************************************

  m_muons           = consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("muons"));
  m_muPairs         = consumes<pat::MultiMuonCollection>(iConfig.getParameter<edm::InputTag>("muPairs"));
  m_muJets          = consumes<pat::MultiMuonCollection>(iConfig.getParameter<edm::InputTag>("muJets"));
  m_muJetOrphans    = consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("muJetOrphans"));
  m_beamSpot        = consumes<reco::BeamSpot>(iConfig.getParameter<edm::InputTag>("beamSpot"));
  m_tracks          = consumes<reco::TrackCollection>(iConfig.getParameter<edm::InputTag>("tracks"));
  m_genParticles    = consumes<reco::GenParticleCollection>(iConfig.getParameter<edm::InputTag>("PrunedGenParticles"));
  m_trigRes         = consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("TriggerResults"));
  //m_L1Res           = consumes<L1GlobalTriggerReadoutRecord>(iConfig.getParameter< edm::InputTag >("L1Results"));
  m_trackRef        = consumes<reco::TrackCollection>(iConfig.getParameter<edm::InputTag>("TrackRefitter"));
  m_traj            = consumes< std::vector<Trajectory> >(iConfig.getParameter<edm::InputTag>("Traj"));
  m_primaryVertices = consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("primaryVertices"));
  m_secondaryVertices = consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("secondaryVertices"));
  m_PATJet          = consumes<std::vector<pat::Jet> >(iConfig.getParameter<edm::InputTag>("PATJet"));
  m_nThrowsConsistentVertexesCalculator = iConfig.getParameter<int>("nThrowsConsistentVertexesCalculator");
  m_barrelPixelLayer = iConfig.getParameter<int>("barrelPixelLayer");
  m_endcapPixelLayer = iConfig.getParameter<int>("endcapPixelLayer");
  skimOutput_ = iConfig.getParameter<bool>("skimOutput");
  //useFinalDecision_ = iConfig.getParameter<bool>("useFinalDecision");
  m_pileupCollection = consumes<std::vector<PileupSummaryInfo> >(iConfig.getParameter<edm::InputTag>("pileupCollection"));

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

  param_ = iConfig;
  measurementTrkToken_ = consumes<MeasurementTrackerEvent>(iConfig.getParameter<edm::InputTag>("MeasurementTrackerEvent"));

}


CutFlowAnalyzer_MiniAOD::~CutFlowAnalyzer_MiniAOD()
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
// ------------ method called when starting to processes a run  ------------
void CutFlowAnalyzer_MiniAOD::beginRun(const edm::Run& run,const edm::EventSetup& setup)
{
  //Added for L1 decision @Wei SHI, Mar 11, 2019
  //Need to initalise the menu each run (menu can and will change on run boundaries)
  bool changed=false;
  hltPSProv_.init(run,setup,hltProcess_,changed);
  const l1t::L1TGlobalUtil& l1GtUtils = hltPSProv_.l1tGlobalUtil();
  if ( m_debug > 10 ) std::cout <<"l1 menu "<<l1GtUtils.gtTriggerMenuName()<<" version "<<l1GtUtils.gtTriggerMenuVersion()<<" comment "<<std::endl;
  if ( m_debug > 10 ) std::cout <<"hlt name "<<hltPSProv_.hltConfigProvider().tableName()<<std::endl;
}

// ------------ method called for each event  ------------
void
CutFlowAnalyzer_MiniAOD::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  m_fillGenLevel = !iEvent.eventAuxiliary().isRealData();

  using namespace edm;
  double eq = 0.000001; // small number used below to compare variables

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

    if ( m_debug > 0 ) std::cout << m_events << " Start GEN Level" << std::endl;

    edm::Handle<reco::GenParticleCollection> genParticles;
    iEvent.getByToken(m_genParticles, genParticles);

    //@Wei SHI
    //Note for PDG ID in benchmark models:
    //(1) NMSSM: Higgs={35}, new light boson={36,54}, muons={13,-13},
    //    '54' is the corner case in pythia when '36' doesn't work for some mass points
    //(2) MSSMD (Dark SUSY): Higgs={25}, new light boson={3000022}, muons={13,-13}
    //(3) ALP: Higgs={25}, new light boson={9000005}, muons={13,-13}
    //(4) Scalar Model from Mehdi: Higgs like ZD={5000002}, new light boson SD={5000512, -5000512}, muons={13,-13}
    //(5) Fermionic Model from Mehdi: Higgs like ZD={5000002}, new light fermion? F11&F12?={5000521}, muons={13,-13}
    std::vector<const reco::GenParticle*> genH;
    std::vector<const reco::GenParticle*> genA_unsorted;
    std::vector<const reco::GenParticle*> genA;
    std::vector<const reco::GenParticle*> genMuons;
    std::vector<const reco::Candidate*>   genMuonMothers;

    // Loop over all gen particles
    int counterGenParticle = 0;
    for(reco::GenParticleCollection::const_iterator iGenParticle = genParticles->begin();  iGenParticle != genParticles->end();  ++iGenParticle) {
      counterGenParticle++;
      //std::cout << "#" <<counterGenParticle << " id: " << iGenParticle->pdgId() << "; status: " << iGenParticle->status() <<"; pT: "<< iGenParticle->pt() <<"; eta: "<< iGenParticle->eta() << "; phi: " << iGenParticle->phi() << "; vx: " << iGenParticle->vx()<<"; vy: "<<iGenParticle->vy()<<"; vz: "<<iGenParticle->vz()<< std::endl;

      // Check if gen particle is muon
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

          if (
            genMuonCand->mother(iMother)->pdgId() == 36 ||
            genMuonCand->mother(iMother)->pdgId() == 54 ||
            genMuonCand->mother(iMother)->pdgId() == 3000022 ||
            genMuonCand->mother(iMother)->pdgId() == 9000005 ||
            fabs( genMuonCand->mother(iMother)->pdgId() ) == 5000512 ||
            genMuonCand->mother(iMother)->pdgId() == 5000521
          ) {
            // Store the muon (stable, first in chain) into vector
            genMuons.push_back(&(*iGenParticle));
            // Store mother of the muon into vector. We need this to group muons into dimuons later
            genMuonMothers.push_back(genMuonCand->mother(iMother));
          }
        }
      }//end check if gen particle is muon

      //=======================================================================
      // !!!Note: Wei SHI @Aug 1, 2019
      // Below status code 22 is PYTHIA8 convention for intermediate partiles, this should be changed
      // if one uses another showering program, for example, Herwig7 uses status code 11 for intermediate particles
      //=======================================================================
      // Check if gen particle is Higgs(like), these branches are not used at the moment
      if (
        ( iGenParticle->status() == 22 && iGenParticle->pdgId() == 25 ) ||
        ( iGenParticle->status() == 22 && iGenParticle->pdgId() == 35 ) ||
        ( iGenParticle->status() == 22 && iGenParticle->pdgId() == 5000002 )
       ) {
        genH.push_back(&(*iGenParticle));
      }

      // Check if gen particle is new light boson
      if (
        ( iGenParticle->status() == 22 && iGenParticle->pdgId() == 36 ) ||
	      ( iGenParticle->status() == 22 && iGenParticle->pdgId() == 54 ) ||
	      ( iGenParticle->status() == 22 && iGenParticle->pdgId() == 3000022 ) ||
	      ( iGenParticle->status() == 22 && iGenParticle->pdgId() == 9000005 ) ||
        ( iGenParticle->status() == 22 && fabs( iGenParticle->pdgId() ) == 5000512 ) ||
        ( iGenParticle->status() == 22 && iGenParticle->pdgId() == 5000521 )
      ) {
        genA_unsorted.push_back(&(*iGenParticle));
      }
    }//end loop over gen particle

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
      std::cout << "WARNING! genH.size() != 1" << std::endl;
    }

    // Sort genA by pT (leading pT first)
    if ( genA_unsorted.size() >= 2 ) std::sort (genA_unsorted.begin(), genA_unsorted.end(), tamu::helpers::PtOrder);

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

      b_genA_dEta = b_genA0_eta - b_genA1_eta;
      b_genA_dPhi = tamu::helpers::My_dPhi( b_genA0_phi, b_genA1_phi );
      b_genA_dR   = sqrt(b_genA_dEta*b_genA_dEta + b_genA_dPhi*b_genA_dPhi);

      //std::cout << "* Check genA pt order *"<< std::endl;
      //std::cout << "genA[0] pT: " <<genA[0]->pt()<< std::endl;
      //std::cout << "genA[1] pT: " <<genA[1]->pt()<< std::endl;

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

      b_genA0Mu0_pt = genMuonGroups[0][0]->pt();
      b_genA0Mu1_pt = genMuonGroups[0][1]->pt();
      b_genA1Mu0_pt = genMuonGroups[1][0]->pt();
      b_genA1Mu1_pt = genMuonGroups[1][1]->pt();

      b_genA0Mu0_eta = genMuonGroups[0][0]->eta();
      b_genA0Mu1_eta = genMuonGroups[0][1]->eta();
      b_genA1Mu0_eta = genMuonGroups[1][0]->eta();
      b_genA1Mu1_eta = genMuonGroups[1][1]->eta();

      b_genA0Mu0_phi = genMuonGroups[0][0]->phi();
      b_genA0Mu1_phi = genMuonGroups[0][1]->phi();
      b_genA1Mu0_phi = genMuonGroups[1][0]->phi();
      b_genA1Mu1_phi = genMuonGroups[1][1]->phi();

      b_genA0Mu0_charge = genMuonGroups[0][0]->charge();
      b_genA0Mu1_charge = genMuonGroups[0][1]->charge();
      b_genA1Mu0_charge = genMuonGroups[1][0]->charge();
      b_genA1Mu1_charge = genMuonGroups[1][1]->charge();

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

        //std::cout<<">>> MINIAOD Event #"<<m_events<<std::endl;
        //std::cout<<"GENA mass (0, 1)[GeV]: "<<b_genA0_m    <<", "<<b_genA1_m       << std::endl;

        //std::cout<<"genA0     (x,y,z)[cm]: "<<b_genA0_vx   <<", "<<b_genA0_vy      <<", "<<b_genA0_vz<<std::endl;
        //std::cout<<"      (Lxy, |Lz|)[cm]: "<<b_genA0_Lxy  <<", "<<fabs(b_genA0_Lz)<<std::endl;
        //std::cout<<"genA0 Mu0 (x,y,z)[cm]: "<<b_genA0Mu0_vx<<", "<<b_genA0Mu0_vy   <<", "<<b_genA0Mu0_vz<<std::endl;
        //std::cout<<"          pT    [GeV]: "<<b_genA0Mu0_pt<<"; eta: "<<b_genA0Mu0_eta   <<"; phi: "<<b_genA0Mu0_phi<<std::endl;
        //std::cout<<"genA0 Mu1 (x,y,z)[cm]: "<<b_genA0Mu1_vx<<", "<<b_genA0Mu1_vy   <<", "<<b_genA0Mu1_vz<<std::endl;
        //std::cout<<"          pT    [GeV]: "<<b_genA0Mu1_pt<<"; eta: "<<b_genA0Mu1_eta   <<"; phi: "<<b_genA0Mu1_phi<<std::endl;

        //std::cout<<"genA1     (x,y,z)[cm]: "<<b_genA1_vx   <<", "<<b_genA1_vy      <<", "<<b_genA1_vz<<std::endl;
        //std::cout<<"      (Lxy, |Lz|)[cm]: "<<b_genA1_Lxy  <<", "<<fabs(b_genA1_Lz)<<std::endl;
        //std::cout<<"genA1 Mu0 (x,y,z)[cm]: "<<b_genA1Mu0_vx<<", "<<b_genA1Mu0_vy   <<", "<<b_genA1Mu0_vz<<std::endl;
        //std::cout<<"          pT    [GeV]: "<<b_genA1Mu0_pt<<"; eta: "<<b_genA1Mu0_eta   <<"; phi: "<<b_genA1Mu0_phi<<std::endl;
        //std::cout<<"genA1 Mu1 (x,y,z)[cm]: "<<b_genA1Mu1_vx<<", "<<b_genA1Mu1_vy   <<", "<<b_genA1Mu1_vz<<std::endl;
        //std::cout<<"          pT    [GeV]: "<<b_genA1Mu1_pt<<"; eta: "<<b_genA1Mu1_eta   <<"; phi: "<<b_genA1Mu1_phi<<std::endl;

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

      b_genA0Mu_dEta = b_genA0Mu0_eta - b_genA0Mu1_eta;
      b_genA1Mu_dEta = b_genA1Mu0_eta - b_genA1Mu1_eta;
      b_genA0Mu_dPhi = tamu::helpers::My_dPhi( b_genA0Mu0_phi, b_genA0Mu1_phi );
      b_genA1Mu_dPhi = tamu::helpers::My_dPhi( b_genA1Mu0_phi, b_genA1Mu1_phi );
      b_genA0Mu_dR   = sqrt(b_genA0Mu_dEta*b_genA0Mu_dEta + b_genA0Mu_dPhi*b_genA0Mu_dPhi);
      b_genA1Mu_dR   = sqrt(b_genA1Mu_dEta*b_genA1Mu_dEta + b_genA1Mu_dPhi*b_genA1Mu_dPhi);
      //Check if muons from same mother has oppo. charge
      //they should be as they are generated this way
      b_genA0Mu_dCharge = b_genA0Mu0_charge - b_genA0Mu1_charge;
      b_genA1Mu_dCharge = b_genA1Mu0_charge - b_genA1Mu1_charge;
      //pT difference/ratio of two muons inside one dimuon
      b_genA0Mu_dPt = b_genA0Mu0_pt - b_genA0Mu1_pt;
      b_genA1Mu_dPt = b_genA1Mu0_pt - b_genA1Mu1_pt;
      if( b_genA0Mu1_pt != 0 ) b_genA0Mu_RPt = b_genA0Mu0_pt/b_genA0Mu1_pt;
      if( b_genA1Mu1_pt != 0 ) b_genA1Mu_RPt = b_genA1Mu0_pt/b_genA1Mu1_pt;

      TLorentzVector A0Mu0, A0Mu1, A1Mu0, A1Mu1;
      A0Mu0.SetPtEtaPhiM(b_genA0Mu0_pt, b_genA0Mu0_eta, b_genA0Mu0_phi, 0.105);
      A0Mu1.SetPtEtaPhiM(b_genA0Mu1_pt, b_genA0Mu1_eta, b_genA0Mu1_phi, 0.105);
      A1Mu0.SetPtEtaPhiM(b_genA1Mu0_pt, b_genA1Mu0_eta, b_genA1Mu0_phi, 0.105);
      A1Mu1.SetPtEtaPhiM(b_genA1Mu1_pt, b_genA1Mu1_eta, b_genA1Mu1_phi, 0.105);

      //Form nominal Dimu 4-v from gen muons
      if ( (b_genA0Mu0_charge * b_genA0Mu1_charge < 0) &&
           (b_genA1Mu0_charge * b_genA1Mu1_charge < 0) ) {
             b_genDiMu0_Eta = (A0Mu0 + A0Mu1).Eta();
             b_genDiMu1_Eta = (A1Mu0 + A1Mu1).Eta();
             b_genDiMu0_Phi = (A0Mu0 + A0Mu1).Phi();
             b_genDiMu1_Phi = (A1Mu0 + A1Mu1).Phi();
             b_genDiMu0_M   = (A0Mu0 + A0Mu1).M();
             b_genDiMu1_M   = (A1Mu0 + A1Mu1).M();
             b_genDiMu0_Pt  = (A0Mu0 + A0Mu1).Pt();
             b_genDiMu1_Pt  = (A1Mu0 + A1Mu1).Pt();
             b_genDiMu_dEta = b_genDiMu0_Eta - b_genDiMu1_Eta;
             b_genDiMu_dPhi = tamu::helpers::My_dPhi( b_genDiMu0_Phi, b_genDiMu1_Phi );
             b_genDiMu_dR   = sqrt( b_genDiMu_dEta*b_genDiMu_dEta + b_genDiMu_dPhi*b_genDiMu_dPhi );
             b_genDiMu_dM   = b_genDiMu0_M - b_genDiMu1_M;
      } else {
             std::cout << "WARNING! GEN level muon from the same mother have same charge!" << std::endl;
             b_genDiMu0_Eta = -999.;
             b_genDiMu1_Eta = -999.;
             b_genDiMu0_Phi = -999.;
             b_genDiMu1_Phi = -999.;
             b_genDiMu0_M   = -999.;
             b_genDiMu1_M   = -999.;
             b_genDiMu0_Pt  = -999.;
             b_genDiMu1_Pt  = -999.;
             b_genDiMu_dEta = -999.;
             b_genDiMu_dPhi = -999.;
             b_genDiMu_dR   = -999.;
             b_genDiMu_dM   = -999.;
      }

      //Form Fake Dimu 4-v using muons with oppo. charge from different genA
      if ( (b_genA0Mu0_charge * b_genA1Mu0_charge < 0) &&
           (b_genA0Mu1_charge * b_genA1Mu1_charge < 0) ) {
        b_genFakeDiMu0_Eta = (A0Mu0 + A1Mu0).Eta();
        b_genFakeDiMu1_Eta = (A0Mu1 + A1Mu1).Eta();
        b_genFakeDiMu0_Phi = (A0Mu0 + A1Mu0).Phi();
        b_genFakeDiMu1_Phi = (A0Mu0 + A1Mu1).Phi();
        b_genFakeDiMu0_M   = (A0Mu0 + A1Mu0).M();
        b_genFakeDiMu1_M   = (A0Mu1 + A1Mu1).M();
        b_genFakeDiMu0_Pt  = (A0Mu0 + A1Mu0).Pt();
        b_genFakeDiMu1_Pt  = (A0Mu1 + A1Mu1).Pt();
        b_genFakeDiMu_dEta = b_genFakeDiMu0_Eta - b_genFakeDiMu1_Eta;
        b_genFakeDiMu_dPhi = tamu::helpers::My_dPhi( b_genFakeDiMu0_Phi, b_genFakeDiMu1_Phi );
        b_genFakeDiMu_dR   = sqrt( b_genFakeDiMu_dEta*b_genFakeDiMu_dEta + b_genFakeDiMu_dPhi*b_genFakeDiMu_dPhi );
        b_genFakeDiMu_dM   = b_genFakeDiMu0_M - b_genFakeDiMu1_M;
      }
      else if ( (b_genA0Mu0_charge * b_genA1Mu1_charge < 0) &&
                (b_genA0Mu1_charge * b_genA1Mu0_charge < 0) ) {
        b_genFakeDiMu0_Eta = (A0Mu0 + A1Mu1).Eta();
        b_genFakeDiMu1_Eta = (A0Mu1 + A1Mu0).Eta();
        b_genFakeDiMu0_Phi = (A0Mu0 + A1Mu1).Phi();
        b_genFakeDiMu1_Phi = (A0Mu1 + A1Mu0).Phi();
        b_genFakeDiMu0_M   = (A0Mu0 + A1Mu1).M();
        b_genFakeDiMu1_M   = (A0Mu1 + A1Mu0).M();
        b_genFakeDiMu0_Pt  = (A0Mu0 + A1Mu1).Pt();
        b_genFakeDiMu1_Pt  = (A0Mu1 + A1Mu0).Pt();
        b_genFakeDiMu_dEta = b_genFakeDiMu0_Eta - b_genFakeDiMu1_Eta;
        b_genFakeDiMu_dPhi = tamu::helpers::My_dPhi( b_genFakeDiMu0_Phi, b_genFakeDiMu1_Phi );
        b_genFakeDiMu_dR   = sqrt( b_genFakeDiMu_dEta*b_genFakeDiMu_dEta + b_genFakeDiMu_dPhi*b_genFakeDiMu_dPhi );
        b_genFakeDiMu_dM   = b_genFakeDiMu0_M - b_genFakeDiMu1_M;
      } else {
        b_genFakeDiMu0_Eta = -99.;
        b_genFakeDiMu1_Eta = -99.;
        b_genFakeDiMu0_Phi = -99.;
        b_genFakeDiMu1_Phi = -99.;
        b_genFakeDiMu0_M   = -999.;
        b_genFakeDiMu1_M   = -999.;
        b_genFakeDiMu0_Pt  = -999.;
        b_genFakeDiMu1_Pt  = -999.;
        b_genFakeDiMu_dEta = -99.;
        b_genFakeDiMu_dPhi = -99.;
        b_genFakeDiMu_dR   = -99.;
        b_genFakeDiMu_dM   = -999.;
      }//end Form Dimu 4-v using muons with oppo. charge from different genA

      //Store the difference b/t dPhi of nominal and fake dimu pairs
      b_gen_ddPhi = fabs(b_genDiMu_dPhi) - fabs(b_genFakeDiMu_dPhi);

    } else {
      std::cout << "WARNING! No signal topology found at GEN level!" << std::endl;
    }//end if ( genMuonGroups.size() == 2 ...) else {}

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

    //For analysis basic selections
    std::vector<const reco::GenParticle*> genMuons17;
    std::vector<const reco::GenParticle*> genMuons8;
    //For HLT eff study on MC
    std::vector<const reco::GenParticle*> genMuons16;
    std::vector<const reco::GenParticle*> genMuons6;

    for ( unsigned int i = 0; i < genMuons.size(); i++ ) {
      if ( genMuons[i]->pt() > m_threshold_Mu17_pT && fabs( genMuons[i]->eta() ) < m_threshold_Mu17_eta ) {
        genMuons17.push_back(genMuons[i]);
      }
      if ( genMuons[i]->pt() > m_threshold_Mu8_pT && fabs( genMuons[i]->eta() ) < m_threshold_Mu8_eta ) {
        genMuons8.push_back(genMuons[i]);
      }
      if ( genMuons[i]->pt() > m_HLT_Mu16_pT && fabs( genMuons[i]->eta() ) < m_HLT_Mu_eta) {
        genMuons16.push_back(genMuons[i]);
      }
      if ( genMuons[i]->pt() > m_HLT_Mu6_pT  && fabs( genMuons[i]->eta() ) < m_HLT_Mu_eta ) {
        genMuons6.push_back(genMuons[i]);
      }
    }

    //Analysis selections
    b_is1GenMu17 = false;
    b_is2GenMu8  = false;
    b_is3GenMu8  = false;
    b_is4GenMu8  = false;
    //For HLT: only care three muons
    b_has1GenMu16 = false;
    b_has1GenMu6  = false;
    b_has1GenMu16Mu6Mu6  = false;

    if ( genMuons17.size() >= 1) {
      m_events1GenMu17++;
      b_is1GenMu17 = true;
      if ( genMuons8.size() >= 2 ) {
        m_events2GenMu8++;
        b_is2GenMu8 = true;
      }
      if ( genMuons8.size() >= 3 ) {
        m_events3GenMu8++;
        b_is3GenMu8 = true;
      }
      if ( genMuons8.size() >= 4 ) {
        m_events4GenMu8++;
        b_is4GenMu8 = true;
      }
    }

    if ( genMuons16.size() >= 1) {
      b_has1GenMu16 = true;
    }
    if ( genMuons6.size() >= 1) {
      b_has1GenMu6 = true;
    }
    if ( genMuons16.size() >= 1 && genMuons6.size() >= 3) {
      b_has1GenMu16Mu6Mu6 = true;
    }

    if ( m_debug > 0 ) std::cout << m_events << " GEN Level Done " << std::endl;
  }

  //****************************************************************************
  //                          GEN LEVEL ANALYSIS FINISH
  //****************************************************************************

  //****************************************************************************
  //                          RECO LEVEL ANALYSIS START
  //****************************************************************************

  if ( m_debug > 0 ) std::cout << m_events << " Start RECO Level" << std::endl;

  edm::Handle<pat::MuonCollection> muons;
  iEvent.getByToken(m_muons, muons);
  std::vector<const pat::Muon*> selMuons;

  for (pat::MuonCollection::const_iterator iMuon = muons->begin();  iMuon != muons->end();  ++iMuon) {
    //START DEBUG@Wei May5, 2020
    //FYI: https://github.com/cms-sw/cmssw/blob/master/DataFormats/TrackReco/interface/HitPattern.h#L275
    //if ( (b_run == 1 && b_lumi == 177 && b_event == 17673) || (b_run == 1 && b_lumi == 441 && b_event == 44056) || (b_run == 1 && b_lumi == 444 && b_event == 44314) ){
    //if ( (b_run == 1 && b_lumi == 246 && b_event == 24533) || (b_run == 1 && b_lumi == 305 && b_event == 30409) || (b_run == 1 && b_lumi == 306 && b_event == 30555) || (b_run == 1 && b_lumi == 373 && b_event == 37287) ){
    //if ( (b_run == 1 && b_lumi == 1 && b_event == 247) || (b_run == 1 && b_lumi == 1 && b_event == 364) ){
    /*if ( (b_run == 1 && b_lumi == 2301 && b_event == 230014) ){
      std::cout << ">>> run: " << b_run << ", lumi: " << b_lumi << ", event: " << b_event << std::endl;
      std::cout << "Mu pT: " << iMuon->pt() << "; eta: " << iMuon->eta() << "; phi: " << iMuon->phi() <<std::endl;
      std::cout << "   isLooseMuon: " << iMuon->isLooseMuon() << "; isMediumMuon: " << iMuon->isMediumMuon() << "; isTrackerMuon: " << iMuon->isTrackerMuon() << "; isGlobalMuon: " << iMuon->isGlobalMuon() << "; isPFMuon:" << iMuon->isPFMuon() << "; isStandAloneMuon: "<< iMuon->isStandAloneMuon() <<std::endl;
      if ( iMuon->innerTrack().isAvailable() ){
        std::cout << "   innerTrack available, pT: " << iMuon->innerTrack()->pt() << ", eta: "<< iMuon->innerTrack()->eta() << ", phi: "<< iMuon->innerTrack()->phi() << ", dxy: " << iMuon->innerTrack()->dxy(beamSpot->position()) << ", dz: " << iMuon->innerTrack()->dz(beamSpot->position()) << std::endl;
        const reco::HitPattern& ipa = iMuon->innerTrack()->hitPattern();
        std::cout << "   Valid hits in PIX: " << ipa.numberOfValidPixelHits() << "; BPIX: " << ipa.numberOfValidPixelBarrelHits() << "; FPIX: " << ipa.numberOfValidPixelEndcapHits() << std::endl;
        std::cout << "                           B1: " << ipa.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 1) << ";   F1: " << ipa.hasValidHitInPixelLayer(PixelSubdetector::PixelEndcap, 1) << std::endl;
        std::cout << "                           B2: " << ipa.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 2) << ";   F1: " << ipa.hasValidHitInPixelLayer(PixelSubdetector::PixelEndcap, 2) << std::endl;
        std::cout << "                           B3: " << ipa.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 3) << ";   F1: " << ipa.hasValidHitInPixelLayer(PixelSubdetector::PixelEndcap, 3) << std::endl;
        std::cout << "                           B4: " << ipa.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 4) << std::endl;
        std::cout << "               strip: " << ipa.numberOfValidStripHits() << "; tracker: " << ipa.numberOfValidTrackerHits() << std::endl;
      }
      if ( iMuon->outerTrack().isAvailable() ){
        std::cout << "   outerTrack available, pT: " << iMuon->outerTrack()->pt() << ", eta: "<< iMuon->outerTrack()->eta() << ", phi: "<< iMuon->outerTrack()->phi() << ", dxy: " << iMuon->outerTrack()->dxy(beamSpot->position()) << ", dz: " << iMuon->outerTrack()->dz(beamSpot->position()) << std::endl;
        const reco::HitPattern& ipa = iMuon->outerTrack()->hitPattern();
        std::cout << "   Valid hits in muon: " << ipa.numberOfValidMuonHits() << "; DT: " << ipa.numberOfValidMuonDTHits() << "; CSC: " << ipa.numberOfValidMuonCSCHits() << "; RPC: " << ipa.numberOfValidMuonRPCHits() << std::endl;
      }
      if ( iMuon->globalTrack().isAvailable() ){
        std::cout << "   globalTrack available, pt: " << iMuon->globalTrack()->pt() << ", eta: "<< iMuon->globalTrack()->eta() << ", phi: "<< iMuon->globalTrack()->phi() << ", dxy: " << iMuon->globalTrack()->dxy(beamSpot->position()) << ", dz: " << iMuon->globalTrack()->dz(beamSpot->position()) << std::endl;
      }
      if ( iMuon->muonBestTrack().isAvailable() ){
        std::cout << "   bestTrack available, pt: " << iMuon->muonBestTrack()->pt() << ", eta: "<< iMuon->muonBestTrack()->eta() << ", phi: "<< iMuon->muonBestTrack()->phi() << ", dxy: " << iMuon->muonBestTrack()->dxy(beamSpot->position()) << ", dz: " << iMuon->muonBestTrack()->dz(beamSpot->position()) << std::endl;
      }
    }*/
    //End DEBUG@Wei May5, 2020
    //@Wei May12, 2020: Update muon ID requirement for run2 analysis: push back PF loose muons or standalone muons,
    //allow standalone muon to gain lost efficiency in the displaced muon reconstruction inside tracker (innerTrack)
    //At dimu selection later, require LESS THAN TWO (<=1) standalone muon among four muons from 2 dimu
    if ( tamu::helpers::PassMuonId( &(*iMuon) ) ) {
      selMuons.push_back( &(*iMuon) );
    }
  }

  // Sort selMuons by pT (leading pT first)
  if ( selMuons.size() > 1 ) std::sort( selMuons.begin(), selMuons.end(), tamu::helpers::PtOrderRecoMu );
  b_nRecoMu = selMuons.size();

  if ( selMuons.size() > 0 ) {
    b_selMu0_px  = selMuons[0]->px();
    b_selMu0_py  = selMuons[0]->py();
    b_selMu0_pz  = selMuons[0]->pz();
    b_selMu0_pT  = selMuons[0]->pt();
    b_selMu0_eta = selMuons[0]->eta();
    b_selMu0_phi = selMuons[0]->phi();
  } else {
    b_selMu0_px  = -100.0;
    b_selMu0_py  = -100.0;
    b_selMu0_pz  = -100.0;
    b_selMu0_pT  = -100.0;
    b_selMu0_eta = -100.0;
    b_selMu0_phi = -100.0;
  }

  if ( selMuons.size() > 1 ) {
    b_selMu1_px  = selMuons[1]->px();
    b_selMu1_py  = selMuons[1]->py();
    b_selMu1_pz  = selMuons[1]->pz();
    b_selMu1_pT  = selMuons[1]->pt();
    b_selMu1_eta = selMuons[1]->eta();
    b_selMu1_phi = selMuons[1]->phi();
  } else {
    b_selMu1_px  = -100.0;
    b_selMu1_py  = -100.0;
    b_selMu1_pz  = -100.0;
    b_selMu1_pT  = -100.0;
    b_selMu1_eta = -100.0;
    b_selMu1_phi = -100.0;
  }

  if ( selMuons.size() > 2 ) {
    b_selMu2_px  = selMuons[2]->px();
    b_selMu2_py  = selMuons[2]->py();
    b_selMu2_pz  = selMuons[2]->pz();
    b_selMu2_pT  = selMuons[2]->pt();
    b_selMu2_eta = selMuons[2]->eta();
    b_selMu2_phi = selMuons[2]->phi();
  } else {
    b_selMu2_px  = -100.0;
    b_selMu2_py  = -100.0;
    b_selMu2_pz  = -100.0;
    b_selMu2_pT  = -100.0;
    b_selMu2_eta = -100.0;
    b_selMu2_phi = -100.0;
  }

  if ( selMuons.size() > 3 ) {
    b_selMu3_px  = selMuons[3]->px();
    b_selMu3_py  = selMuons[3]->py();
    b_selMu3_pz  = selMuons[3]->pz();
    b_selMu3_pT  = selMuons[3]->pt();
    b_selMu3_eta = selMuons[3]->eta();
    b_selMu3_phi = selMuons[3]->phi();
  } else {
    b_selMu3_px  = -100.0;
    b_selMu3_py  = -100.0;
    b_selMu3_pz  = -100.0;
    b_selMu3_pT  = -100.0;
    b_selMu3_eta = -100.0;
    b_selMu3_phi = -100.0;
  }

  if ( m_debug > 0 ) std::cout << m_events << " Count selected RECO muons" << std::endl;
  std::vector<const pat::Muon*> selMuons17;
  std::vector<const pat::Muon*> selMuons8;

  for ( unsigned int i = 0; i < selMuons.size(); i++ ) {
      if ( selMuons[i]->pt() > m_threshold_Mu17_pT && fabs( selMuons[i]->eta() ) < m_threshold_Mu17_eta ) {
        selMuons17.push_back(selMuons[i]);
      }
      if ( selMuons[i]->pt() > m_threshold_Mu8_pT && fabs( selMuons[i]->eta() ) < m_threshold_Mu8_eta ) {
        selMuons8.push_back(selMuons[i]);
      }
  }

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

  if ( m_debug > 0 ) std::cout <<"---------------------"<< std::endl;
  if ( m_debug > 0 ) std::cout <<"Event #"<< m_events << ": build RECO muon pairs" << std::endl;

  //Check all formed mu pairs in each event
  edm::Handle<pat::MultiMuonCollection> muPairs;
  iEvent.getByToken(m_muPairs, muPairs);
  b_nMuPairs = muPairs->size();
  b_nDaughterPerMuPair = -999.;

  if ( m_debug > 0 ) std::cout << ">>> Tot No. of Mu pairs: " << b_nMuPairs << std::endl;
  if ( b_nMuPairs!=0 ){
    b_nDaughterPerMuPair = 0.;
    for ( int i = 0; i < b_nMuPairs; i++ ) {
      //Sanity check: should always equal 2
      b_nDaughterPerMuPair = b_nDaughterPerMuPair + (*muPairs)[i].numberOfDaughters();
      //print out mu pair masses
      if ( m_debug > 10 ) std::cout << "Mu pair #" << i+1 <<" mass: "<< (*muPairs)[i].mass() <<"; No. of Daughters: "<< (*muPairs)[i].numberOfDaughters() << std::endl;
    }
    b_nDaughterPerMuPair = b_nDaughterPerMuPair / b_nMuPairs;
    if ( m_debug > 0 ) std::cout << "Avg. No. of Daughter per Mu pair: " << b_nDaughterPerMuPair << std::endl;
  }

  edm::Handle<pat::MultiMuonCollection> muJets;
  iEvent.getByToken(m_muJets, muJets);
  b_nMuJets = muJets->size();
  b_nDaughterPerMuJet  = -999.;

  const pat::MultiMuon *muJetC = NULL;
  const pat::MultiMuon *muJetF = NULL;
  int nMuJetsContainMu17 = 0;
  b_is2MuJets = false;

  if ( m_debug > 0 ) std::cout << ">>> Tot No. of Mu Jets: " << b_nMuJets << std::endl;

  //Store average no. of daughters in one mujet
  if ( b_nMuJets!=0 ) {
    b_nDaughterPerMuJet  = 0.;
    for ( int d = 0; d < b_nMuJets; d++ ) {
      b_nDaughterPerMuJet = b_nDaughterPerMuJet + (*muJets)[d].numberOfDaughters();
      if ( m_debug > 10 ) std::cout << "Mu Jet #" << d+1 <<" mass: "<< (*muJets)[d].mass() << "; No. of Daughters: "<< (*muJets)[d].numberOfDaughters() << std::endl;
    }
    b_nDaughterPerMuJet = b_nDaughterPerMuJet / b_nMuJets;
    if ( m_debug > 0 ) std::cout << "Avg. No. of Daughter per Mu Jet: " << b_nDaughterPerMuJet << std::endl;
  }

  if ( b_nMuJets == 2) {
    if ( m_debug > 0 ) std::cout << "Exactly two mu jets !! PairOne mass: "<< (*muJets)[0].mass() << "; PairTwo mass: "<< (*muJets)[1].mass() << std::endl;
    for ( int j = 0; j < b_nMuJets; j++ ) {
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

  if ( m_debug > 0 ) std::cout << m_events << " Check if exactly 2 muon jets are built" << std::endl;
  if ( b_is1SelMu17 && b_is4SelMu8 && b_is2MuJets) m_events2MuJets++;

  //Note@Wei, May 20, 2020: Below count SA muons is not ideal, as muJetC and muJetF are registered together when mujet size is two,
  //so you only get correct count nSA when there are two mujets.
  //In a way this is what we preferred now because we are more concerned how many SA muons are in the final dimu, not the sel mu
  //In the future, need to disentangle the nSA count with mu jet size equal two
  //Even better, merge the MuJetProducerRun2.cc with this CutFlowAnalyzer_MiniAOD.cc
  //Use 4 sel muon as input to MuJetProducerRun2.cc instead of slimmedMuons
  b_nSAMu = 0;//total number of SA-only mu in 2 dimuons: not a PF loose mu
  b_dimuC_nSAMu = 0;//... in dimuC
  b_dimuF_nSAMu = 0;//... in dimuF
  b_nNonTrackerMu = 0;//total number of muons that's PF loose global mu (PF & global), but not a tracker mu.
  b_dimuC_nNonTrackerMu = 0;//... in dimuC
  b_dimuF_nNonTrackerMu = 0;//... in dimuF
  if ( muJetC != NULL && muJetC->numberOfDaughters() == 2 ) {
    if( muJetC->muon(0)->isStandAloneMuon() && !( muJetC->muon(0)->isPFMuon() && ( muJetC->muon(0)->isTrackerMuon() || muJetC->muon(0)->isGlobalMuon() ) ) ){
      b_nSAMu++;
      b_dimuC_nSAMu++;
    }
    if( muJetC->muon(1)->isStandAloneMuon() && !( muJetC->muon(1)->isPFMuon() && ( muJetC->muon(1)->isTrackerMuon() || muJetC->muon(1)->isGlobalMuon() ) ) ){
      b_nSAMu++;
      b_dimuC_nSAMu++;
    }
    if( muJetC->muon(0)->isPFMuon() && muJetC->muon(0)->isGlobalMuon() && !muJetC->muon(0)->isTrackerMuon() ){
      b_nNonTrackerMu++;
      b_dimuC_nNonTrackerMu++;
    }
    if( muJetC->muon(1)->isPFMuon() && muJetC->muon(1)->isGlobalMuon() && !muJetC->muon(1)->isTrackerMuon() ){
      b_nNonTrackerMu++;
      b_dimuC_nNonTrackerMu++;
    }
  }
  if ( muJetF != NULL && muJetF->numberOfDaughters() == 2 ) {
    if( muJetF->muon(0)->isStandAloneMuon() && !( muJetF->muon(0)->isPFMuon() && ( muJetF->muon(0)->isTrackerMuon() || muJetF->muon(0)->isGlobalMuon() ) ) ){
      b_nSAMu++;
      b_dimuF_nSAMu++;
    }
    if( muJetF->muon(1)->isStandAloneMuon() && !( muJetF->muon(1)->isPFMuon() && ( muJetF->muon(1)->isTrackerMuon() || muJetF->muon(1)->isGlobalMuon() ) ) ){
      b_nSAMu++;
      b_dimuF_nSAMu++;
    }
    if( muJetF->muon(0)->isPFMuon() && muJetF->muon(0)->isGlobalMuon() && !muJetF->muon(0)->isTrackerMuon() ){
      b_nNonTrackerMu++;
      b_dimuF_nNonTrackerMu++;
    }
    if( muJetF->muon(1)->isPFMuon() && muJetF->muon(1)->isGlobalMuon() && !muJetF->muon(1)->isTrackerMuon() ){
      b_nNonTrackerMu++;
      b_dimuF_nNonTrackerMu++;
    }
  }

  b_is2DiMuons = false;
  const pat::MultiMuon *diMuonC = NULL;
  const pat::MultiMuon *diMuonF = NULL;
  if ( muJetC != NULL && muJetF != NULL ) {
    if ( muJetC->numberOfDaughters() == 2 && muJetF->numberOfDaughters() == 2 ) {
      //std::cout << "b_nSAMu: " << b_nSAMu << std::endl;
      if( b_nSAMu <= 2 ){
        diMuonC = muJetC;
        diMuonF = muJetF;
        b_is2DiMuons = true;
      }
    }
  }

  if ( m_debug > 0 ) std::cout << m_events << " Check if 2 muon jets are dimuons" << std::endl;

  if ( b_is1SelMu17 && b_is4SelMu8 && b_is2MuJets && b_is2DiMuons){
    m_events2DiMuons++;
    b_massC = muJetC->mass();
    b_massF = muJetF->mass();

    b_muJetC_Mu0_pt = muJetC->muon(0)->pt();
    b_muJetC_Mu1_pt = muJetC->muon(1)->pt();
    b_muJetF_Mu0_pt = muJetF->muon(0)->pt();
    b_muJetF_Mu1_pt = muJetF->muon(1)->pt();

    b_muJetC_Mu0_eta = muJetC->muon(0)->eta();
    b_muJetC_Mu1_eta = muJetC->muon(1)->eta();
    b_muJetF_Mu0_eta = muJetF->muon(0)->eta();
    b_muJetF_Mu1_eta = muJetF->muon(1)->eta();

    b_muJetC_Mu0_phi = muJetC->muon(0)->phi();
    b_muJetC_Mu1_phi = muJetC->muon(1)->phi();
    b_muJetF_Mu0_phi = muJetF->muon(0)->phi();
    b_muJetF_Mu1_phi = muJetF->muon(1)->phi();

    b_muJetC_Mu0_charge = muJetC->muon(0)->charge();
    b_muJetC_Mu1_charge = muJetC->muon(1)->charge();
    b_muJetF_Mu0_charge = muJetF->muon(0)->charge();
    b_muJetF_Mu1_charge = muJetF->muon(1)->charge();
  } else {
    b_massC = -999.;
    b_massF = -999.;

    b_muJetC_Mu0_pt = -999.;
    b_muJetC_Mu1_pt = -999.;
    b_muJetF_Mu0_pt = -999.;
    b_muJetF_Mu1_pt = -999.;

    b_muJetC_Mu0_eta = -999.;
    b_muJetC_Mu1_eta = -999.;
    b_muJetF_Mu0_eta = -999.;
    b_muJetF_Mu1_eta = -999.;

    b_muJetC_Mu1_phi = -999.;
    b_muJetF_Mu0_phi = -999.;
    b_muJetC_Mu0_phi = -999.;
    b_muJetF_Mu1_phi = -999.;

    b_muJetC_Mu0_charge = 0.;
    b_muJetC_Mu1_charge = 0.;
    b_muJetF_Mu0_charge = 0.;
    b_muJetF_Mu1_charge = 0.;
  }

  //Now we have two distinct dimuons, we do a sanity check to reject rare events
  //where DY muons come with additional muons from FSR/ISR photon,
  //which could radiate from: (I) protons; (II) DY muons
  if ( b_is2DiMuons ){//Need to have two dimuons at least
    TLorentzVector diMuonCMu0_4Vect, diMuonCMu1_4Vect, diMuonFMu0_4Vect, diMuonFMu1_4Vect;
    diMuonCMu0_4Vect.SetPtEtaPhiM(b_muJetC_Mu0_pt, b_muJetC_Mu0_eta, b_muJetC_Mu0_phi, 0.105);
    diMuonCMu1_4Vect.SetPtEtaPhiM(b_muJetC_Mu1_pt, b_muJetC_Mu1_eta, b_muJetC_Mu1_phi, 0.105);
    diMuonFMu0_4Vect.SetPtEtaPhiM(b_muJetF_Mu0_pt, b_muJetF_Mu0_eta, b_muJetF_Mu0_phi, 0.105);
    diMuonFMu1_4Vect.SetPtEtaPhiM(b_muJetF_Mu1_pt, b_muJetF_Mu1_eta, b_muJetF_Mu1_phi, 0.105);

    b_reco4mu_pt  = (diMuonCMu0_4Vect + diMuonCMu1_4Vect + diMuonFMu0_4Vect + diMuonFMu1_4Vect).Pt();
    b_reco4mu_eta = (diMuonCMu0_4Vect + diMuonCMu1_4Vect + diMuonFMu0_4Vect + diMuonFMu1_4Vect).Eta();
    b_reco4mu_phi = (diMuonCMu0_4Vect + diMuonCMu1_4Vect + diMuonFMu0_4Vect + diMuonFMu1_4Vect).Phi();
    b_reco4mu_m   = (diMuonCMu0_4Vect + diMuonCMu1_4Vect + diMuonFMu0_4Vect + diMuonFMu1_4Vect).M();

    //Form new dimuons 4-v using muons with oppo. charge from diMuonC and diMuonF
    if ( (b_muJetC_Mu0_charge * b_muJetF_Mu0_charge < 0) && (b_muJetC_Mu1_charge * b_muJetF_Mu1_charge < 0) ) {
      b_recoFakeDiMu0_pt  = (diMuonCMu0_4Vect + diMuonFMu0_4Vect).Pt();
      b_recoFakeDiMu1_pt  = (diMuonCMu1_4Vect + diMuonFMu1_4Vect).Pt();
      b_recoFakeDiMu0_eta = (diMuonCMu0_4Vect + diMuonFMu0_4Vect).Eta();
      b_recoFakeDiMu1_eta = (diMuonCMu1_4Vect + diMuonFMu1_4Vect).Eta();
      b_recoFakeDiMu0_phi = (diMuonCMu0_4Vect + diMuonFMu0_4Vect).Phi();
      b_recoFakeDiMu1_phi = (diMuonCMu1_4Vect + diMuonFMu1_4Vect).Phi();
      b_recoFakeDiMu0_m   = (diMuonCMu0_4Vect + diMuonFMu0_4Vect).M();
      b_recoFakeDiMu1_m   = (diMuonCMu1_4Vect + diMuonFMu1_4Vect).M();

      b_dEtaRePairedDimuA = b_muJetC_Mu0_eta - b_muJetF_Mu0_eta;
      b_dEtaRePairedDimuB = b_muJetC_Mu1_eta - b_muJetF_Mu1_eta;
      b_dPhiRePairedDimuA = tamu::helpers::My_dPhi( b_muJetC_Mu0_phi, b_muJetF_Mu0_phi );
      b_dPhiRePairedDimuB = tamu::helpers::My_dPhi( b_muJetC_Mu1_phi, b_muJetF_Mu1_phi );

    }
    else if ( (b_muJetC_Mu0_charge * b_muJetF_Mu1_charge < 0) && (b_muJetC_Mu1_charge * b_muJetF_Mu0_charge < 0) ) {
      b_recoFakeDiMu0_pt  = (diMuonCMu0_4Vect + diMuonFMu1_4Vect).Pt();
      b_recoFakeDiMu1_pt  = (diMuonCMu1_4Vect + diMuonFMu0_4Vect).Pt();
      b_recoFakeDiMu0_eta = (diMuonCMu0_4Vect + diMuonFMu1_4Vect).Eta();
      b_recoFakeDiMu1_eta = (diMuonCMu1_4Vect + diMuonFMu0_4Vect).Eta();
      b_recoFakeDiMu0_phi = (diMuonCMu0_4Vect + diMuonFMu1_4Vect).Phi();
      b_recoFakeDiMu1_phi = (diMuonCMu1_4Vect + diMuonFMu0_4Vect).Phi();
      b_recoFakeDiMu0_m   = (diMuonCMu0_4Vect + diMuonFMu1_4Vect).M();
      b_recoFakeDiMu1_m   = (diMuonCMu1_4Vect + diMuonFMu0_4Vect).M();

      b_dEtaRePairedDimuA = b_muJetC_Mu0_eta - b_muJetF_Mu1_eta;
      b_dEtaRePairedDimuB = b_muJetC_Mu1_eta - b_muJetF_Mu0_eta;
      b_dPhiRePairedDimuA = tamu::helpers::My_dPhi( b_muJetC_Mu0_phi, b_muJetF_Mu1_phi );
      b_dPhiRePairedDimuB = tamu::helpers::My_dPhi( b_muJetC_Mu1_phi, b_muJetF_Mu0_phi );
    }

    //re-paired mass order
    if(b_recoFakeDiMu0_m >= b_recoFakeDiMu1_m){
      b_recoRePaired2muleading_m = b_recoFakeDiMu0_m;
      b_recoRePaired2mutrailing_m = b_recoFakeDiMu1_m;
    }
    else{
      b_recoRePaired2muleading_m = b_recoFakeDiMu1_m;
      b_recoRePaired2mutrailing_m = b_recoFakeDiMu0_m;
    }

    b_dRrePairedDimuA   = sqrt(b_dEtaRePairedDimuA*b_dEtaRePairedDimuA + b_dPhiRePairedDimuA*b_dPhiRePairedDimuA);
    b_dRrePairedDimuB   = sqrt(b_dEtaRePairedDimuB*b_dEtaRePairedDimuB + b_dPhiRePairedDimuB*b_dPhiRePairedDimuB);
    //re-paired dR order
    if(b_dRrePairedDimuA >= b_dRrePairedDimuB){
      b_recoRePaired2muleading_dR = b_dRrePairedDimuA;
      b_recoRePaired2mutrailing_dR = b_dRrePairedDimuB;
    }
    else{
      b_recoRePaired2muleading_dR = b_dRrePairedDimuB;
      b_recoRePaired2mutrailing_dR = b_dRrePairedDimuA;
    }

  }
  else{
    b_reco4mu_pt  = -999.;
    b_reco4mu_eta = -999.;
    b_reco4mu_phi = -999.;
    b_reco4mu_m   = -999.;
    b_recoFakeDiMu0_pt  = -999.;
    b_recoFakeDiMu1_pt  = -999.;
    b_recoFakeDiMu0_eta = -999.;
    b_recoFakeDiMu1_eta = -999.;
    b_recoFakeDiMu0_phi = -999.;
    b_recoFakeDiMu1_phi = -999.;
    b_recoFakeDiMu0_m   = -999.;
    b_recoFakeDiMu1_m   = -999.;
    b_dEtaRePairedDimuA = -999.;
    b_dEtaRePairedDimuB = -999.;
    b_dPhiRePairedDimuA = -999.;
    b_dPhiRePairedDimuB = -999.;
    b_dRrePairedDimuA = -999.;
    b_dRrePairedDimuB = -999.;
    b_recoRePaired2muleading_m = -999.;
    b_recoRePaired2mutrailing_m = -999.;
    b_recoRePaired2muleading_dR = -999.;
    b_recoRePaired2mutrailing_dR = -999.;
  }

  // Variables calculated with fitted vertexes
  if ( diMuonC != NULL ) b_diMuonC_FittedVtx_dR = diMuonC->dR(0, 1, diMuonC->vertexValid());
  else b_diMuonC_FittedVtx_dR = -1000.0;

  if ( diMuonC != NULL && diMuonC->vertexValid() ) {
    //All vertex* functions below defined in MuJetAnalysis/DataFormats/interface/MultiMuon.h
    b_diMuonC_FittedVtx_m   = diMuonC->vertexMass();//seems ok
    //variables below are relevant when calculate dimu iso
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
    //This should propagate back to the beam line, looks right
    b_diMuonC_FittedVtx_dz  = diMuonC->vertexDz(beamSpot->position());
    b_diMuonC_FittedVtx_chi2= diMuonC->vertexChi2();
    b_diMuonC_FittedVtx_ndof= diMuonC->vertexNdof();
    b_diMuonC_FittedVtx_prob= diMuonC->vertexProb();
    //std::cout << ">>> dimuC vtx prob: " << b_diMuonC_FittedVtx_prob << ", mass: " << b_diMuonC_FittedVtx_m << ", SAmu ONLY: " << b_dimuC_nSAMu << std::endl;
	  //std::cout << "diMuC vtx         (x,y,z)[cm]: " << b_diMuonC_FittedVtx_vx << ", " << b_diMuonC_FittedVtx_vy << ", " << b_diMuonC_FittedVtx_vz << std::endl;
    //std::cout << "            (Lxy,|Lz|,dz)[cm]: " << b_diMuonC_FittedVtx_Lxy<< ", " << sqrt( pow(b_diMuonC_FittedVtx_L,2) - pow(b_diMuonC_FittedVtx_Lxy,2) )<<", "<<b_diMuonC_FittedVtx_dz<< std::endl;
    //std::cout << "diMuF vtx         (x,y,z)[cm]: " << b_diMuonF_FittedVtx_vx << ", " << b_diMuonF_FittedVtx_vy << ", " << b_diMuonF_FittedVtx_vz << std::endl;
    //std::cout << "            (Lxy,|Lz|,dz)[cm]: " << b_diMuonF_FittedVtx_Lxy<< ", " << sqrt( pow(b_diMuonF_FittedVtx_L,2) - pow(b_diMuonF_FittedVtx_Lxy,2) )<<", "<<b_diMuonF_FittedVtx_dz<< std::endl;
    //std::cout << "Dimu vtx mass     (C, F)[GeV]: " << b_diMuonC_FittedVtx_m  << ", " << b_diMuonF_FittedVtx_m  << std::endl;
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
    b_diMuonC_FittedVtx_chi2= -1000.0;
    b_diMuonC_FittedVtx_ndof= -1000.0;
    b_diMuonC_FittedVtx_prob= -1000.0;
  }

  if ( diMuonF != NULL ) b_diMuonF_FittedVtx_dR = diMuonF->dR(0, 1, diMuonF->vertexValid());
  else b_diMuonF_FittedVtx_dR = -1000.0;

  if ( diMuonF != NULL && diMuonF->vertexValid() ) {
    b_diMuonF_FittedVtx_m   = diMuonF->vertexMass();//seems ok
    //variables below are relevant when calculate dimu iso
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
    //This should propagate back to the beam line, looks right
    b_diMuonF_FittedVtx_dz  = diMuonF->vertexDz(beamSpot->position());
    b_diMuonF_FittedVtx_chi2= diMuonF->vertexChi2();
    b_diMuonF_FittedVtx_ndof= diMuonF->vertexNdof();
    b_diMuonF_FittedVtx_prob= diMuonF->vertexProb();
    //std::cout << "    dimuF vtx prob: " << b_diMuonF_FittedVtx_prob << ", mass: " << b_diMuonF_FittedVtx_m <<  ", SAmu ONLY: " << b_dimuF_nSAMu << std::endl;
  } else {
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
    b_diMuonF_FittedVtx_chi2= -1000.0;
    b_diMuonF_FittedVtx_ndof= -1000.0;
    b_diMuonF_FittedVtx_prob= -1000.0;
  }

  // fitted vertexes
  b_is2DiMuonsFittedVtxOK = false;
  if ( diMuonC != NULL && diMuonF != NULL ) {
    if ( diMuonC->vertexValid() && diMuonF->vertexValid() ) {
      b_is2DiMuonsFittedVtxOK = true;
    }
  }

  // Calculate dz between dimuons - use fitted vertexes
  if ( b_is2DiMuonsFittedVtxOK ) {
    b_diMuons_dz_FittedVtx = b_diMuonC_FittedVtx_dz - b_diMuonF_FittedVtx_dz;
  } else {
    b_diMuons_dz_FittedVtx = -1000.0;
  }

  if ( m_debug > 0 ) std::cout << m_events << " Apply cut on dZ" << std::endl;

  // HLT cut
  b_isSignalHLTFired = false;
  //START DEBUG Many HLT paths
  /*
  b_isSignalHLT_0_Fired = false;
  b_isSignalHLT_1_Fired = false;
  b_isSignalHLT_2_Fired = false;
  b_isSignalHLT_3_Fired = false;
  b_isSignalHLT_4_Fired = false;
  b_isSignalHLT_5_Fired = false;
  b_isSignalHLT_6_Fired = false;
  b_isSignalHLT_7_Fired = false;
  b_isSignalHLT_8_Fired = false;
  b_isSignalHLT_9_Fired = false;
  b_isSignalHLT_10_Fired = false;
  b_isSignalHLT_11_Fired = false;
  b_isSignalHLT_12_Fired = false;
  b_isSignalHLT_13_Fired = false;
  b_isSignalHLT_14_Fired = false;
  b_isSignalHLT_15_Fired = false;
  b_isSignalHLT_16_Fired = false;
  b_isSignalHLT_17_Fired = false;
  b_isSignalHLT_18_Fired = false;
  b_isSignalHLT_19_Fired = false;
  */
  //End DEBUG Many HLT paths
  b_isControlHLT16Fired = false;
  b_isControlHLT6Fired = false;
  b_hltPaths.clear();

  edm::Handle<edm::TriggerResults> TrResults;
  iEvent.getByToken( m_trigRes, TrResults);
  const TriggerResults *trRes = TrResults.product();
  int ntrigs = trRes->size();
  edm::TriggerNames const& triggerNames = iEvent.triggerNames(*trRes);
  for (int itrig = 0; itrig != ntrigs; ++itrig) {
    TString trigName = triggerNames.triggerName(itrig);
    std::string trigNameStr(trigName.Data());
    if ( m_debug > 10 ) std::cout << "HLT Menu #"<<itrig<<": "<<trigNameStr << std::endl;

    if(trRes->accept(itrig)){
      b_hltPaths.push_back(trigNameStr);
      if ( m_debug > 10 ) std::cout << trigNameStr << " is present in edmTriggerResults!" << std::endl;

      // check if this event was fired by the signal trigger!
      for (const auto& p: signalHltPaths_){
        if ( m_debug > 10 ) std::cout << "Signal trigger is "<< p << std::endl;
        if (trigNameStr.find(p) != std::string::npos) {
          if ( m_debug > 10 ) std::cout << "Signal trigger " << p << " fired!" << std::endl;
          b_isSignalHLTFired = true;
        }
      }//end for signal hlt

      //Start: DEBUG Many HLT Paths
      //0: 'HLT_TrkMu16_DoubleTrkMu6NoFiltersNoVtx',
      //1: 'HLT_TrkMu12_DoubleTrkMu5NoFiltersNoVtx',
      //2: 'HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx',
      //3: 'HLT_Mu18_Mu9_SameSign',
      //4: 'HLT_DoubleL2Mu23NoVtx_2Cha_CosmicSeed',
      //5: 'HLT_DoubleL2Mu23NoVtx_2Cha',
      //6: 'HLT_TripleMu_10_5_5_DZ',
      //7: 'HLT_TripleMu_12_10_5',
      //8: 'HLT_DoubleL2Mu50',
      //9: 'HLT_DoubleMu43NoFiltersNoVtx',
      //10: 'HLT_DoubleMu33NoFiltersNoVtxDisplaced',
      //11: 'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8',
      //12: 'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8',
      //13: 'HLT_Mu37_TkMu27',
      //14: 'HLT_IsoMu24',
      //15: 'HLT_IsoMu27',
      //16: 'HLT_Mu50',
      //17: 'HLT_Mu55',
      //18: 'HLT_OldMu100',
      //19: 'HLT_TkMu100',
      /*
      const std::string& s0 = signalHltPaths_[0];
      const std::string& s1 = signalHltPaths_[1];
      const std::string& s2 = signalHltPaths_[2];
      const std::string& s3 = signalHltPaths_[3];
      const std::string& s4 = signalHltPaths_[4];
      const std::string& s5 = signalHltPaths_[5];
      const std::string& s6 = signalHltPaths_[6];
      const std::string& s7 = signalHltPaths_[7];
      const std::string& s8 = signalHltPaths_[8];
      const std::string& s9 = signalHltPaths_[9];
      const std::string& s10 = signalHltPaths_[10];
      const std::string& s11 = signalHltPaths_[11];
      const std::string& s12 = signalHltPaths_[12];
      const std::string& s13 = signalHltPaths_[13];
      const std::string& s14 = signalHltPaths_[14];
      const std::string& s15 = signalHltPaths_[15];
      const std::string& s16 = signalHltPaths_[16];
      const std::string& s17 = signalHltPaths_[17];
      const std::string& s18 = signalHltPaths_[18];
      const std::string& s19 = signalHltPaths_[19];
      if (trigNameStr.find(s0) != std::string::npos) b_isSignalHLT_0_Fired = true;
      if (trigNameStr.find(s1) != std::string::npos) b_isSignalHLT_1_Fired = true;
      if (trigNameStr.find(s2) != std::string::npos) b_isSignalHLT_2_Fired = true;
      if (trigNameStr.find(s3) != std::string::npos) b_isSignalHLT_3_Fired = true;
      if (trigNameStr.find(s4) != std::string::npos) b_isSignalHLT_4_Fired = true;
      if (trigNameStr.find(s5) != std::string::npos) b_isSignalHLT_5_Fired = true;
      if (trigNameStr.find(s6) != std::string::npos) b_isSignalHLT_6_Fired = true;
      if (trigNameStr.find(s7) != std::string::npos) b_isSignalHLT_7_Fired = true;
      if (trigNameStr.find(s8) != std::string::npos) b_isSignalHLT_8_Fired = true;
      if (trigNameStr.find(s9) != std::string::npos) b_isSignalHLT_9_Fired = true;
      if (trigNameStr.find(s10) != std::string::npos) b_isSignalHLT_10_Fired = true;
      if (trigNameStr.find(s11) != std::string::npos) b_isSignalHLT_11_Fired = true;
      if (trigNameStr.find(s12) != std::string::npos) b_isSignalHLT_12_Fired = true;
      if (trigNameStr.find(s13) != std::string::npos) b_isSignalHLT_13_Fired = true;
      if (trigNameStr.find(s14) != std::string::npos) b_isSignalHLT_14_Fired = true;
      if (trigNameStr.find(s15) != std::string::npos) b_isSignalHLT_15_Fired = true;
      if (trigNameStr.find(s16) != std::string::npos) b_isSignalHLT_16_Fired = true;
      if (trigNameStr.find(s17) != std::string::npos) b_isSignalHLT_17_Fired = true;
      if (trigNameStr.find(s18) != std::string::npos) b_isSignalHLT_18_Fired = true;
      if (trigNameStr.find(s19) != std::string::npos) b_isSignalHLT_19_Fired = true;*/
      //End: DEBUG Many HLT Paths

      const std::string& p0 = controlHltPaths_[0];
      const std::string& p1 = controlHltPaths_[1];
      if ( m_debug > 10 ) std::cout << "Control trigger is "<< p0 << std::endl;
      if (trigNameStr.find(p0) != std::string::npos) {
        if ( m_debug > 10 ) std::cout << "Control trigger " << p0 << " fired!" << std::endl;
          b_isControlHLT16Fired = true;
      }
      if ( m_debug > 10 ) std::cout << "Control trigger is "<< p1 << std::endl;
      if (trigNameStr.find(p1) != std::string::npos) {
        if ( m_debug > 10 ) std::cout << "Control trigger " << p1 << " fired!" << std::endl;
          b_isControlHLT6Fired = true;
      }

    }
  }//end for trig
  if ( m_debug > 0 )  std::cout << m_events << " Apply cut on HLT" << std::endl;

  //get L1 decisions for signal HLT L1 seeds
  b_isSignalHLTL1Fired = false;
  std::vector<std::string>::const_iterator algo;

  /*
  //Access L1 decisions: Method 1 --> Not working as of Mar 11, 2019
  //Adapt from: https://github.com/cms-sw/cmssw/blob/CMSSW_9_4_X/L1Trigger/Skimmer/src/L1Filter.cc
  //get L1 menu
  edm::ESHandle<L1GtTriggerMenu> menuRcd;
  iSetup.get<L1GtTriggerMenuRcd>().get(menuRcd) ;
  const L1GtTriggerMenu* menu = menuRcd.product();
  edm::Handle<L1GlobalTriggerReadoutRecord> gtRecord;
  iEvent.getByToken(m_L1Res, gtRecord);
  const DecisionWord dWord = gtRecord->decisionWord();
  if (useFinalDecision_) {
    b_isSignalHLTL1Fired = gtRecord->decision();
  }
  else if ( !dWord.empty() ) {
    for (algo = l1algos_.begin(); algo != l1algos_.end(); ++algo) {
      b_isSignalHLTL1Fired |= menu->gtAlgorithmResult( (*algo), dWord);
    }
  }//end else if
  */

  //Access L1 decisions: Method 2
  //I seem to recall this function being slow so perhaps cache for a given lumi
  //(it only changes on lumi boundaries)
  int psColumn = hltPSProv_.prescaleSet(iEvent,iSetup);
  if ( m_debug > 10 ) std::cout <<"PS column "<<psColumn<<std::endl;
  if(psColumn==0 && iEvent.isRealData()){
    std::cout <<"PS column zero detected for data, this is unlikely (almost all triggers are disabled in normal menus here) and its more likely that you've not loaded the correct global tag in "<<std::endl;
  }

  //note to the reader, what I'm doing is extremely dangerious (a const cast), never do this!
  //however in this narrow case, it fixes a bug in l1t::L1TGlobalUtil (the method should be const)
  //and it is safe for this specific instance
  l1t::L1TGlobalUtil& l1GtUtils = const_cast<l1t::L1TGlobalUtil&> (hltPSProv_.l1tGlobalUtil());
  if ( m_debug > 10 ) std::cout <<"l1 menu: name decisions prescale "<<std::endl;
  for(size_t bitNr=0;bitNr<l1GtUtils.decisionsFinal().size();bitNr++){
    const std::string& bitName = l1GtUtils.decisionsFinal()[bitNr].first; // l1GtUtils.decisionsFinal() is of type std::vector<std::pair<std::string,bool> >

    bool passInitial = l1GtUtils.decisionsInitial()[bitNr].second; //before masks and prescales, so if we have a 15 GeV electron passing L1_SingleEG10, it will show up as true but will likely not cause a L1 acccept due to the seeds high prescale
    bool passInterm = l1GtUtils.decisionsInterm()[bitNr].second; //after mask (?, unsure what this is)
    bool passFinal = l1GtUtils.decisionsFinal()[bitNr].second; //after masks & prescales, true means it gives a L1 accept to the HLT
    int prescale = l1GtUtils.prescales()[bitNr].second;
    for (algo = l1algos_.begin(); algo != l1algos_.end(); ++algo) {
      if (bitName == *algo && passFinal){
        b_isSignalHLTL1Fired = true;
      }
    }//end loop over L1 seeds in signal HLT
    if ( m_debug > 10 ) std::cout <<"   "<<bitNr<<" "<<bitName<<" "<<passInitial<<" "<<passInterm<<" "<<passFinal<<" "<<prescale<<std::endl;
  }

  // Cut on dimuon masses - use fitted vertexes
  //* Run2 (2017+2018): Poly-2 Fit from 2017 ALP signal samples (currently adopted below):
  b_is2DiMuonsMassOK_FittedVtx = false;
  if ( b_is2DiMuonsFittedVtxOK ) {
    if ( fabs(b_diMuonC_FittedVtx_m - b_diMuonF_FittedVtx_m) < 3*(0.003044 + 0.007025*(b_diMuonC_FittedVtx_m + b_diMuonF_FittedVtx_m)/2.0 + 0.000053*(b_diMuonC_FittedVtx_m + b_diMuonF_FittedVtx_m)*(b_diMuonC_FittedVtx_m + b_diMuonF_FittedVtx_m)/4.0) ) {
      b_is2DiMuonsMassOK_FittedVtx = true;
    }
  }

  if ( m_debug > 0 ) std::cout << m_events << " Apply cut on dimuon mass" << std::endl;

  edm::Handle<reco::TrackCollection> tracks;
  iEvent.getByToken(m_tracks, tracks);

  // Calculate isolation for dimuon and single muons inside: require valid fitted vertex of each dimu
  b_diMuonC_IsoTk_FittedVtx = -999.;
  b_diMuonF_IsoTk_FittedVtx = -999.;
  b_isoC_1mm = -999.;
  b_isoF_1mm = -999.;
  b_diMuonCMu0_IsoTk0p3_FittedVtx = -999.;
  b_diMuonCMu0_IsoTk0p4_FittedVtx = -999.;
  b_diMuonCMu0_IsoTk0p5_FittedVtx = -999.;
  b_diMuonCMu1_IsoTk0p3_FittedVtx = -999.;
  b_diMuonCMu1_IsoTk0p4_FittedVtx = -999.;
  b_diMuonCMu1_IsoTk0p5_FittedVtx = -999.;
  b_diMuonFMu0_IsoTk0p3_FittedVtx = -999.;
  b_diMuonFMu0_IsoTk0p4_FittedVtx = -999.;
  b_diMuonFMu0_IsoTk0p5_FittedVtx = -999.;
  b_diMuonFMu1_IsoTk0p3_FittedVtx = -999.;
  b_diMuonFMu1_IsoTk0p4_FittedVtx = -999.;
  b_diMuonFMu1_IsoTk0p5_FittedVtx = -999.;

  if ( diMuonC != NULL && diMuonC->vertexValid() ) {

    double diMuonC_IsoTk_FittedVtx = -999.;
    double diMuonCMu0_IsoTk0p3_FittedVtx = -999.;
    double diMuonCMu0_IsoTk0p4_FittedVtx = -999.;
    double diMuonCMu0_IsoTk0p5_FittedVtx = -999.;
    double diMuonCMu1_IsoTk0p3_FittedVtx = -999.;
    double diMuonCMu1_IsoTk0p4_FittedVtx = -999.;
    double diMuonCMu1_IsoTk0p5_FittedVtx = -999.;

    const pat::PackedCandidate* candFittedVtx_diMuonCMu0 = dynamic_cast<const pat::PackedCandidate*>(diMuonC->muon(0)->sourceCandidatePtr(0).get());
    const pat::PackedCandidate* candFittedVtx_diMuonCMu1 = dynamic_cast<const pat::PackedCandidate*>(diMuonC->muon(1)->sourceCandidatePtr(0).get());

    //Avoid null dynamic cast: casuing segmentation violation error
    //In cases no dynamic cast exists, the event shouldn't be considered
    //since the track couldn't be matched to the muons in the dimuon, this will lead to wrong iso.
    if ( candFittedVtx_diMuonCMu0 != 0 && candFittedVtx_diMuonCMu1 != 0 && candFittedVtx_diMuonCMu0->hasTrackDetails() && candFittedVtx_diMuonCMu1->hasTrackDetails() ){

        diMuonC_IsoTk_FittedVtx = 0.0;
        diMuonCMu0_IsoTk0p3_FittedVtx = 0.0;
        diMuonCMu0_IsoTk0p4_FittedVtx = 0.0;
        diMuonCMu0_IsoTk0p5_FittedVtx = 0.0;
        diMuonCMu1_IsoTk0p3_FittedVtx = 0.0;
        diMuonCMu1_IsoTk0p4_FittedVtx = 0.0;
        diMuonCMu1_IsoTk0p5_FittedVtx = 0.0;

        for (reco::TrackCollection::const_iterator track = tracks->begin(); track != tracks->end(); ++track) {
          bool trackIsMuon = false;
          if ( m_debug > 10 ) std::cout << "track_px: " <<track->px() << "; track_py: "<<track->py() <<"; track_pz: "<<track->pz()<< "; track_vx: " <<track->vx() << "; track_vy: "<<track->vy() <<"; track_vz: "<<track->vz()<<std::endl;

          //Track used for iso calculation can't be from signal muons
          if ( tamu::helpers::sameTrack( &*track, &(candFittedVtx_diMuonCMu0->pseudoTrack()) ) || tamu::helpers::sameTrack( &*track, &(candFittedVtx_diMuonCMu1->pseudoTrack()) ) ) trackIsMuon = true;
          //If the other dimu exists, also exclude its signal muons
          if ( diMuonF != NULL && diMuonF->vertexValid() ) {
            const pat::PackedCandidate* candTmp_diMuonFMu0 = dynamic_cast<const pat::PackedCandidate*>(diMuonF->muon(0)->sourceCandidatePtr(0).get());
            const pat::PackedCandidate* candTmp_diMuonFMu1 = dynamic_cast<const pat::PackedCandidate*>(diMuonF->muon(1)->sourceCandidatePtr(0).get());
            if ( candTmp_diMuonFMu0!=0 && candTmp_diMuonFMu1!=0 && candTmp_diMuonFMu0->hasTrackDetails() && candTmp_diMuonFMu1->hasTrackDetails() ){
              if ( tamu::helpers::sameTrack( &*track, &(candTmp_diMuonFMu0->pseudoTrack()) ) || tamu::helpers::sameTrack( &*track, &(candTmp_diMuonFMu1->pseudoTrack()) ) ) trackIsMuon = true;
            }
          }

          if ( trackIsMuon == false ) {
            //dimuC iso
            double dPhiC = tamu::helpers::My_dPhi( diMuonC->vertexMomentum().phi(), track->phi() );
            double dEtaC = diMuonC->vertexMomentum().eta() - track->eta();
            double dRC   = sqrt( dPhiC*dPhiC + dEtaC*dEtaC );
            double dzC   = b_diMuonC_FittedVtx_dz - track->dz(beamSpot->position());
            if ( dRC < m_threshold_DiMuons_Iso_dR && track->pt() > m_threshold_DiMuons_Iso_pT && fabs(dzC) < m_threshold_DiMuons_Iso_dz ) diMuonC_IsoTk_FittedVtx += track->pt();

            //dimuC mu0 iso
            double dPhiC0 = tamu::helpers::My_dPhi( candFittedVtx_diMuonCMu0->pseudoTrack().phi(), track->phi() );
            double dEtaC0 = candFittedVtx_diMuonCMu0->pseudoTrack().eta() - track->eta();
            double dRC0   = sqrt( dPhiC0*dPhiC0 + dEtaC0*dEtaC0 );
            double dzC0   = candFittedVtx_diMuonCMu0->pseudoTrack().dz(beamSpot->position()) - track->dz(beamSpot->position());
            if ( dRC0 < 0.3 && track->pt() > 0.5 && fabs( dzC0 ) < 0.1 ) diMuonCMu0_IsoTk0p3_FittedVtx += track->pt();//cone size: 0.3
            if ( dRC0 < 0.4 && track->pt() > 0.5 && fabs( dzC0 ) < 0.1 ) diMuonCMu0_IsoTk0p4_FittedVtx += track->pt();//cone size: 0.4
            if ( dRC0 < 0.5 && track->pt() > 0.5 && fabs( dzC0 ) < 0.1 ) diMuonCMu0_IsoTk0p5_FittedVtx += track->pt();//cone size: 0.5

            //dimuC mu1 iso
            double dPhiC1 = tamu::helpers::My_dPhi( candFittedVtx_diMuonCMu1->pseudoTrack().phi(), track->phi() );
            double dEtaC1 = candFittedVtx_diMuonCMu1->pseudoTrack().eta() - track->eta();
            double dRC1   = sqrt( dPhiC1*dPhiC1 + dEtaC1*dEtaC1 );
            double dzC1   = candFittedVtx_diMuonCMu1->pseudoTrack().dz(beamSpot->position()) - track->dz(beamSpot->position());
            if ( dRC1 < 0.3 && track->pt() > 0.5 && fabs( dzC1 ) < 0.1 ) diMuonCMu1_IsoTk0p3_FittedVtx += track->pt();//cone size: 0.3
            if ( dRC1 < 0.4 && track->pt() > 0.5 && fabs( dzC1 ) < 0.1 ) diMuonCMu1_IsoTk0p4_FittedVtx += track->pt();//cone size: 0.4
            if ( dRC1 < 0.5 && track->pt() > 0.5 && fabs( dzC1 ) < 0.1 ) diMuonCMu1_IsoTk0p5_FittedVtx += track->pt();//cone size: 0.5

          }//end trackIsMuon

        }//end loop over tracks

      }//end if cast exists

      b_diMuonC_IsoTk_FittedVtx = diMuonC_IsoTk_FittedVtx;
      b_isoC_1mm = b_diMuonC_IsoTk_FittedVtx;
      b_diMuonCMu0_IsoTk0p3_FittedVtx = diMuonCMu0_IsoTk0p3_FittedVtx;
      b_diMuonCMu0_IsoTk0p4_FittedVtx = diMuonCMu0_IsoTk0p4_FittedVtx;
      b_diMuonCMu0_IsoTk0p5_FittedVtx = diMuonCMu0_IsoTk0p5_FittedVtx;
      b_diMuonCMu1_IsoTk0p3_FittedVtx = diMuonCMu1_IsoTk0p3_FittedVtx;
      b_diMuonCMu1_IsoTk0p4_FittedVtx = diMuonCMu1_IsoTk0p4_FittedVtx;
      b_diMuonCMu1_IsoTk0p5_FittedVtx = diMuonCMu1_IsoTk0p5_FittedVtx;

  }//end diMuonC not null and vertex valid

  if ( diMuonF != NULL && diMuonF->vertexValid() ) {

    double diMuonF_IsoTk_FittedVtx = -999.;
    double diMuonFMu0_IsoTk0p3_FittedVtx = -999.;
    double diMuonFMu0_IsoTk0p4_FittedVtx = -999.;
    double diMuonFMu0_IsoTk0p5_FittedVtx = -999.;
    double diMuonFMu1_IsoTk0p3_FittedVtx = -999.;
    double diMuonFMu1_IsoTk0p4_FittedVtx = -999.;
    double diMuonFMu1_IsoTk0p5_FittedVtx = -999.;

    const pat::PackedCandidate* candFittedVtx_diMuonFMu0 = dynamic_cast<const pat::PackedCandidate*>(diMuonF->muon(0)->sourceCandidatePtr(0).get());
    const pat::PackedCandidate* candFittedVtx_diMuonFMu1 = dynamic_cast<const pat::PackedCandidate*>(diMuonF->muon(1)->sourceCandidatePtr(0).get());

    //Avoid null dynamic cast: casuing segmentation violation error
    //In cases no dynamic cast exists, the event shouldn't be considered
    //since the track couldn't be matched to the muons in the dimuon, this will lead to wrong iso.
    if ( candFittedVtx_diMuonFMu0!=0 && candFittedVtx_diMuonFMu1!=0 && candFittedVtx_diMuonFMu0->hasTrackDetails() && candFittedVtx_diMuonFMu1->hasTrackDetails() ){

        diMuonF_IsoTk_FittedVtx = 0.0;
        diMuonFMu0_IsoTk0p3_FittedVtx = 0.0;
        diMuonFMu0_IsoTk0p4_FittedVtx = 0.0;
        diMuonFMu0_IsoTk0p5_FittedVtx = 0.0;
        diMuonFMu1_IsoTk0p3_FittedVtx = 0.0;
        diMuonFMu1_IsoTk0p4_FittedVtx = 0.0;
        diMuonFMu1_IsoTk0p5_FittedVtx = 0.0;

        for (reco::TrackCollection::const_iterator track = tracks->begin(); track != tracks->end(); ++track) {
          bool trackIsMuon = false;
          if ( m_debug > 10 ) std::cout << "track_px: " <<track->px() << "; track_py: "<<track->py() <<"; track_pz: "<<track->pz()<< "; track_vx: " <<track->vx() << "; track_vy: "<<track->vy() <<"; track_vz: "<<track->vz()<<std::endl;

          //Track used for iso calculation can't be from signal muons
          if ( tamu::helpers::sameTrack( &*track, &(candFittedVtx_diMuonFMu0->pseudoTrack()) ) || tamu::helpers::sameTrack( &*track, &(candFittedVtx_diMuonFMu1->pseudoTrack()) ) ) trackIsMuon = true;
          //If the other dimu exists, also exclude its signal muons
          if ( diMuonC != NULL && diMuonC->vertexValid() ) {
            const pat::PackedCandidate* candTmp_diMuonCMu0 = dynamic_cast<const pat::PackedCandidate*>(diMuonC->muon(0)->sourceCandidatePtr(0).get());
            const pat::PackedCandidate* candTmp_diMuonCMu1 = dynamic_cast<const pat::PackedCandidate*>(diMuonC->muon(1)->sourceCandidatePtr(0).get());
            if ( candTmp_diMuonCMu0!=0 && candTmp_diMuonCMu1!=0 && candTmp_diMuonCMu0->hasTrackDetails() && candTmp_diMuonCMu1->hasTrackDetails() ){
              if ( tamu::helpers::sameTrack( &*track, &(candTmp_diMuonCMu0->pseudoTrack()) ) || tamu::helpers::sameTrack( &*track, &(candTmp_diMuonCMu1->pseudoTrack()) ) ) trackIsMuon = true;
            }
          }

          if ( trackIsMuon == false ) {
            //dimuF iso
            double dPhiF = tamu::helpers::My_dPhi( diMuonF->vertexMomentum().phi(), track->phi() );
            double dEtaF = diMuonF->vertexMomentum().eta() - track->eta();
            double dRF   = sqrt( dPhiF*dPhiF + dEtaF*dEtaF );
            double dzF   = b_diMuonF_FittedVtx_dz - track->dz(beamSpot->position());
            if ( dRF < m_threshold_DiMuons_Iso_dR && track->pt() > m_threshold_DiMuons_Iso_pT && fabs(dzF) < m_threshold_DiMuons_Iso_dz ) diMuonF_IsoTk_FittedVtx += track->pt();

            //dimuF mu0 iso
            double dPhiF0 = tamu::helpers::My_dPhi( candFittedVtx_diMuonFMu0->pseudoTrack().phi(), track->phi() );
            double dEtaF0 = candFittedVtx_diMuonFMu0->pseudoTrack().eta() - track->eta();
            double dRF0   = sqrt( dPhiF0*dPhiF0 + dEtaF0*dEtaF0 );
            double dzF0   = candFittedVtx_diMuonFMu0->pseudoTrack().dz(beamSpot->position()) - track->dz(beamSpot->position());
            if ( dRF0 < 0.3 && track->pt() > 0.5 && fabs( dzF0 ) < 0.1 ) diMuonFMu0_IsoTk0p3_FittedVtx += track->pt();//cone size: 0.3
            if ( dRF0 < 0.4 && track->pt() > 0.5 && fabs( dzF0 ) < 0.1 ) diMuonFMu0_IsoTk0p4_FittedVtx += track->pt();//cone size: 0.4
            if ( dRF0 < 0.5 && track->pt() > 0.5 && fabs( dzF0 ) < 0.1 ) diMuonFMu0_IsoTk0p5_FittedVtx += track->pt();//cone size: 0.5

            //dimuF mu1 iso
            double dPhiF1 = tamu::helpers::My_dPhi( candFittedVtx_diMuonFMu1->pseudoTrack().phi(), track->phi() );
            double dEtaF1 = candFittedVtx_diMuonFMu1->pseudoTrack().eta() - track->eta();
            double dRF1   = sqrt( dPhiF1*dPhiF1 + dEtaF1*dEtaF1 );
            double dzF1   = candFittedVtx_diMuonFMu1->pseudoTrack().dz(beamSpot->position()) - track->dz(beamSpot->position());
            if ( dRF1 < 0.3 && track->pt() > 0.5 && fabs( dzF1 ) < 0.1 ) diMuonFMu1_IsoTk0p3_FittedVtx += track->pt();//cone size: 0.3
            if ( dRF1 < 0.4 && track->pt() > 0.5 && fabs( dzF1 ) < 0.1 ) diMuonFMu1_IsoTk0p4_FittedVtx += track->pt();//cone size: 0.4
            if ( dRF1 < 0.5 && track->pt() > 0.5 && fabs( dzF1 ) < 0.1 ) diMuonFMu1_IsoTk0p5_FittedVtx += track->pt();//cone size: 0.5

          }//end trackIsMuon

        }//end loop over tracks

      }//end if cast exists

      b_diMuonF_IsoTk_FittedVtx = diMuonF_IsoTk_FittedVtx;
      b_isoF_1mm = b_diMuonF_IsoTk_FittedVtx;
      b_diMuonFMu0_IsoTk0p3_FittedVtx = diMuonFMu0_IsoTk0p3_FittedVtx;
      b_diMuonFMu0_IsoTk0p4_FittedVtx = diMuonFMu0_IsoTk0p4_FittedVtx;
      b_diMuonFMu0_IsoTk0p5_FittedVtx = diMuonFMu0_IsoTk0p5_FittedVtx;
      b_diMuonFMu1_IsoTk0p3_FittedVtx = diMuonFMu1_IsoTk0p3_FittedVtx;
      b_diMuonFMu1_IsoTk0p4_FittedVtx = diMuonFMu1_IsoTk0p4_FittedVtx;
      b_diMuonFMu1_IsoTk0p5_FittedVtx = diMuonFMu1_IsoTk0p5_FittedVtx;
  }//end diMuonF not null and vertex valid

  //Register pixel hits info for two muons of each dimuon
  b_nMuHasValidHitInPixel = 0;
  b_diMuonC_m1_FittedVtx_hitpix_Phase1 = -1000;
  b_diMuonC_m2_FittedVtx_hitpix_Phase1 = -1000;
  b_diMuonF_m1_FittedVtx_hitpix_Phase1 = -1000;
  b_diMuonF_m2_FittedVtx_hitpix_Phase1 = -1000;

  b_diMuonC_m1_FittedVtx_ValidPixelHits = -1000;
  b_diMuonC_m2_FittedVtx_ValidPixelHits = -1000;
  b_diMuonF_m1_FittedVtx_ValidPixelHits = -1000;
  b_diMuonF_m2_FittedVtx_ValidPixelHits = -1000;

  b_diMuonC_m1_FittedVtx_ValidPixelBarrelHits = -1000;
  b_diMuonC_m2_FittedVtx_ValidPixelBarrelHits = -1000;
  b_diMuonF_m1_FittedVtx_ValidPixelBarrelHits = -1000;
  b_diMuonF_m2_FittedVtx_ValidPixelBarrelHits = -1000;

  b_diMuonC_m1_FittedVtx_ValidPixelEndcapHits = -1000;
  b_diMuonC_m2_FittedVtx_ValidPixelEndcapHits = -1000;
  b_diMuonF_m1_FittedVtx_ValidPixelEndcapHits = -1000;
  b_diMuonF_m2_FittedVtx_ValidPixelEndcapHits = -1000;

  b_diMuonC_m1_FittedVtx_pixelLayersWithMeasurement = -1000;
  b_diMuonC_m2_FittedVtx_pixelLayersWithMeasurement = -1000;
  b_diMuonF_m1_FittedVtx_pixelLayersWithMeasurement = -1000;
  b_diMuonF_m2_FittedVtx_pixelLayersWithMeasurement = -1000;

  //Here only need diMu not NULL
  if ( diMuonC != NULL ) {
    for(uint32_t k=0;k<2;k++){

      if ( diMuonC->muon(k)->innerTrack().isAvailable() ){
        const reco::HitPattern& p = diMuonC->muon(k)->innerTrack()->hitPattern();

        if( p.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 1) || p.hasValidHitInPixelLayer(PixelSubdetector::PixelEndcap, 1) ||
            p.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 2) || p.hasValidHitInPixelLayer(PixelSubdetector::PixelEndcap, 2) ||
            p.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 3) || p.hasValidHitInPixelLayer(PixelSubdetector::PixelEndcap, 3) ||
            p.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 4) ){
              if(k==0) {
                b_diMuonC_m1_FittedVtx_hitpix_Phase1 = 1;
                b_nMuHasValidHitInPixel++;
              }
              if(k==1) {
                b_diMuonC_m2_FittedVtx_hitpix_Phase1 = 1;
                b_nMuHasValidHitInPixel++;
              }
        }
        //Refer to: https://github.com/cms-sw/cmssw/blob/master/DataFormats/TrackReco/interface/HitPattern.h#L294
        if ( p.numberOfValidPixelHits() > 0 ){
          if(k==0) b_diMuonC_m1_FittedVtx_ValidPixelHits = p.numberOfValidPixelHits();
          if(k==1) b_diMuonC_m2_FittedVtx_ValidPixelHits = p.numberOfValidPixelHits();
        }
        if ( p.numberOfValidPixelBarrelHits() > 0 ){
          if(k==0) b_diMuonC_m1_FittedVtx_ValidPixelBarrelHits = p.numberOfValidPixelBarrelHits();
          if(k==1) b_diMuonC_m2_FittedVtx_ValidPixelBarrelHits = p.numberOfValidPixelBarrelHits();
        }
        if ( p.numberOfValidPixelEndcapHits() > 0 ){
          if(k==0) b_diMuonC_m1_FittedVtx_ValidPixelEndcapHits = p.numberOfValidPixelEndcapHits();
          if(k==1) b_diMuonC_m2_FittedVtx_ValidPixelEndcapHits = p.numberOfValidPixelEndcapHits();
        }
        if ( p.pixelLayersWithMeasurement() > 0 ){
          if(k==0) b_diMuonC_m1_FittedVtx_pixelLayersWithMeasurement = p.pixelLayersWithMeasurement();
          if(k==1) b_diMuonC_m2_FittedVtx_pixelLayersWithMeasurement = p.pixelLayersWithMeasurement();
        }
      }//C innerTrack available
    }//end loop k
  }//end diMuonC not null

  if ( diMuonF != NULL ) {
    for(uint32_t k=0;k<2;k++){

      if ( diMuonF->muon(k)->innerTrack().isAvailable() ){
        const reco::HitPattern& p = diMuonF->muon(k)->innerTrack()->hitPattern();

        if( p.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 1) || p.hasValidHitInPixelLayer(PixelSubdetector::PixelEndcap, 1) ||
            p.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 2) || p.hasValidHitInPixelLayer(PixelSubdetector::PixelEndcap, 2) ||
            p.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 3) || p.hasValidHitInPixelLayer(PixelSubdetector::PixelEndcap, 3) ||
            p.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 4) ){
              if(k==0) {
                b_diMuonF_m1_FittedVtx_hitpix_Phase1 = 1;
                b_nMuHasValidHitInPixel++;
              }
              if(k==1) {
                b_diMuonF_m2_FittedVtx_hitpix_Phase1 = 1;
                b_nMuHasValidHitInPixel++;
              }
        }
        if ( p.numberOfValidPixelHits() > 0 ){
          if(k==0) b_diMuonF_m1_FittedVtx_ValidPixelHits = p.numberOfValidPixelHits();
          if(k==1) b_diMuonF_m2_FittedVtx_ValidPixelHits = p.numberOfValidPixelHits();
        }
        if ( p.numberOfValidPixelBarrelHits() > 0 ){
          if(k==0) b_diMuonF_m1_FittedVtx_ValidPixelBarrelHits = p.numberOfValidPixelBarrelHits();
          if(k==1) b_diMuonF_m2_FittedVtx_ValidPixelBarrelHits = p.numberOfValidPixelBarrelHits();
        }
        if ( p.numberOfValidPixelEndcapHits() > 0 ){
          if(k==0) b_diMuonF_m1_FittedVtx_ValidPixelEndcapHits = p.numberOfValidPixelEndcapHits();
          if(k==1) b_diMuonF_m2_FittedVtx_ValidPixelEndcapHits = p.numberOfValidPixelEndcapHits();
        }
        if ( p.pixelLayersWithMeasurement() > 0 ){
          if(k==0) b_diMuonF_m1_FittedVtx_pixelLayersWithMeasurement = p.pixelLayersWithMeasurement();
          if(k==1) b_diMuonF_m2_FittedVtx_pixelLayersWithMeasurement = p.pixelLayersWithMeasurement();
        }
      }//F innerTrack available
    }//end loop k
  }//end dimuF not null

  //****************************************************************************
  //                    Control Region Events for BKG Modeling
  //****************************************************************************
  FillTrigInfo(triggerComposition, triggerNames, NameAndNumb );
  m_orphan_passOffLineSel = false;
  m_orphan_passOffLineSelPtEta = false;
  m_orphan_AllTrackerMu = false;

  m_orphan_dimu_dR = -999.;
  m_orphan_dimu_mass = -999.;
  m_orphan_dimu_z = -999.;
  m_orphan_dimu_Lxy  = -999.;
  m_orphan_dimu_L    = -999.;
  m_orphan_dimu_chi2 = -999.;
  m_orphan_dimu_ndof = -999.;
  m_orphan_dimu_prob = -999.;
  m_orphan_dimu_isoTk = -999.;
  m_orphan_dimu_Mu0_isoTk0p3 = -999.;
  m_orphan_dimu_Mu0_isoTk0p4 = -999.;
  m_orphan_dimu_Mu0_isoTk0p5 = -999.;
  m_orphan_dimu_Mu1_isoTk0p3 = -999.;
  m_orphan_dimu_Mu1_isoTk0p4 = -999.;
  m_orphan_dimu_Mu1_isoTk0p5 = -999.;
  m_orphan_PtOrph  = -99.;
  m_orphan_EtaOrph = -99.;
  m_orphan_PtMu0   = -99.;
  m_orphan_EtaMu0  = -99.;
  m_orphan_PtMu1   = -99.;
  m_orphan_EtaMu1  = -99.;
  m_orphan_isoTk = -999.;
  m_dimuorphan_containstrig = 0;
  m_dimuorphan_containstrig2 = 0;
  m_orphan_dimu_nSAMu = 0;
  m_orphan_dimu_nNonTrackerMu = 0;
  m_orphan_nSAMu = 0;
  m_orphan_nNonTrackerMu = 0;
  float mu1788 = 0;

  //Note: b-tagging itself is from MVA which could probably introduce bias
  int NPATJet        = 0;
  int NPATJetTightB  = 0;
  int NPATJetMediumB = 0;
  int NPATJetLooseB  = 0;
  edm::Handle<std::vector<pat::Jet> > PATJet;
  iEvent.getByToken(m_PATJet, PATJet);
  for( auto Myjet = PATJet->begin(); Myjet != PATJet->end(); ++Myjet ){
    if( fabs(Myjet->eta())<2.4 && Myjet->pt()>5. ){
      // B-tags: https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookMiniAOD2017#Jets
      // 2017 WP: https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation94X
      b_PAT_jet_pt[NPATJet]   = Myjet->pt();
      b_PAT_jet_eta[NPATJet]  = Myjet->eta();
      b_PAT_jet_phi[NPATJet]  = Myjet->phi();
      b_PAT_jet_E[NPATJet]    = Myjet->energy();
      b_PAT_jet_CSVv2[NPATJet] = Myjet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
      if( b_PAT_jet_CSVv2[NPATJet] > 0.9693 ) {
        NPATJetTightB++;
      }
      if( b_PAT_jet_CSVv2[NPATJet] > 0.8838 ) {
        NPATJetMediumB++;
      }
      if( b_PAT_jet_CSVv2[NPATJet] > 0.5803 ) {
        NPATJetLooseB++;
      }
      NPATJet++;
    }
  }//end loop over jets
  b_NPATJet = NPATJet;
  b_NPATJetTightB = NPATJetTightB;
  b_NPATJetMediumB = NPATJetMediumB;
  b_NPATJetLooseB = NPATJetLooseB;

  //high pT muon trigger object
  std::vector<pat::MuonCollection::const_iterator> hightrigmuons;
  for (pat::MuonCollection::const_iterator muon = muons->begin();  muon != muons->end();  ++muon) {
    if (muon->pt() > m_threshold_Mu17_pT  &&  fabs(muon->eta()) < m_threshold_Mu17_eta) {
      const pat::TriggerObjectStandAlone *mu01  = muon->triggerObjectMatchByPath("HLT_TrkMu16_DoubleTrkMu6NoFiltersNoVtx_v*");
      if((mu01 != NULL && mu01->collection() == std::string("hltGlbTrkMuonCandsNoVtx::HLT") && mu01->pt() > m_threshold_Mu17_pT)  ){
        hightrigmuons.push_back(muon);
      }
    }
  }//end high pT mu matching to trigger objects

  edm::Handle<pat::MuonCollection> orphans_unsorted;
  iEvent.getByToken(m_muJetOrphans, orphans_unsorted);
  std::vector<const pat::Muon*> orphans;
  for (pat::MuonCollection::const_iterator iOrph = orphans_unsorted->begin();  iOrph != orphans_unsorted->end();  ++iOrph) {
    orphans.push_back( &(*iOrph) );
  }

  // Sort orphan muons by pT (leading pT first)
  if ( orphans.size() > 1 ) std::sort( orphans.begin(), orphans.end(), tamu::helpers::PtOrderRecoMu );
  b_nOrphans = orphans.size();

  //===============================================================================
  //                      Control Region Event Selection
  //Run 2: 1 dimuon and >=1 orphan muon, need at least 3 muons to fire the HLT
  //===============================================================================
  if (b_nMuJets == 1  &&  (*muJets)[0].numberOfDaughters() == 2  &&  b_nOrphans >= 1 ) {
    m_orphan_passOffLineSel = true;
    pat::MultiMuonCollection::const_iterator muJet = muJets->begin();
    m_orphan_PtOrph  = orphans[0]->pt();
    m_orphan_EtaOrph = orphans[0]->eta();
    m_orphan_PtMu0   = muJet->muon(0)->pt();
    m_orphan_PtMu1   = muJet->muon(1)->pt();
    m_orphan_EtaMu0  = muJet->muon(0)->eta();
    m_orphan_EtaMu1  = muJet->muon(1)->eta();

    if ( muJet->vertexValid() ){
      m_orphan_dimu_mass = muJet->vertexMass();
      m_orphan_dimu_z    = muJet->vertexDz(beamSpot->position());
      m_orphan_dimu_Lxy  = muJet->vertexLxy(beamSpotPosition);
      m_orphan_dimu_L    = muJet->vertexL(beamSpotPosition);
      //fitted vtx GoF
      m_orphan_dimu_chi2 = muJet->vertexChi2();
      m_orphan_dimu_ndof = muJet->vertexNdof();
      m_orphan_dimu_prob = muJet->vertexProb();
    }
    m_orphan_dimu_dR = muJet->dR(0, 1, muJet->vertexValid());

    //This part echos the branches/tags for 2 dimu events
    if ( muJet->numberOfDaughters() == 2 ) {
      if( muJet->muon(0)->isStandAloneMuon() && !( muJet->muon(0)->isPFMuon() && ( muJet->muon(0)->isTrackerMuon() || muJet->muon(0)->isGlobalMuon() ) ) ) m_orphan_dimu_nSAMu++;
      if( muJet->muon(1)->isStandAloneMuon() && !( muJet->muon(1)->isPFMuon() && ( muJet->muon(1)->isTrackerMuon() || muJet->muon(1)->isGlobalMuon() ) ) ) m_orphan_dimu_nSAMu++;
      if( muJet->muon(0)->isPFMuon() && muJet->muon(0)->isGlobalMuon() && !muJet->muon(0)->isTrackerMuon() ) m_orphan_dimu_nNonTrackerMu++;
      if( muJet->muon(1)->isPFMuon() && muJet->muon(1)->isGlobalMuon() && !muJet->muon(1)->isTrackerMuon() ) m_orphan_dimu_nNonTrackerMu++;
    }

    if( orphans[0]->isStandAloneMuon() && !( orphans[0]->isPFMuon() && ( orphans[0]->isTrackerMuon() || orphans[0]->isGlobalMuon() ) ) ) m_orphan_nSAMu++;//1 or 0
    if( orphans[0]->isPFMuon() && orphans[0]->isGlobalMuon() && !orphans[0]->isTrackerMuon() ) m_orphan_nNonTrackerMu++;//1 or 0

    double triPt[3]  = {m_orphan_PtMu0, m_orphan_PtMu1, m_orphan_PtOrph};
    double triEta[3] = {fabs( m_orphan_EtaMu0 ), fabs( m_orphan_EtaMu1 ), fabs( m_orphan_EtaOrph)};
    int Index17=-1;
    for(int i=0; i<3; i++){
      if( triPt[i] > m_threshold_Mu17_pT && triEta[i] < m_threshold_Mu17_eta ) Index17 = i;
    }
    if( Index17>-1 ){
      for(int i=0; i<3; i++){
        if(i!=Index17 && triPt[i]>m_threshold_Mu8_pT && triEta[i]<m_threshold_Mu8_eta) mu1788 += 0.5;
      }
    }
    if( mu1788==1 ) m_orphan_passOffLineSelPtEta = true;

    if ( muJet->muon(0)->isTrackerMuon() && muJet->muon(0)->innerTrack().isNonnull() &&
         muJet->muon(1)->isTrackerMuon() && muJet->muon(1)->innerTrack().isNonnull() &&
         orphans[0]->isTrackerMuon() && orphans[0]->innerTrack().isNonnull() ) m_orphan_AllTrackerMu = true;

    if( m_orphan_passOffLineSelPtEta ) FillTrigInfo(triggerComposition_bb, triggerNames, NameAndNumb );

    //Check whether orphan muon or dimu muons fired high pT leg
    for (auto iter = hightrigmuons.begin();  iter != hightrigmuons.end();  ++iter) {
      if( orphans[0]->innerTrack().isAvailable() &&
          (*iter)->innerTrack().isAvailable() &&
          tamu::helpers::sameTrack(&*(orphans[0]->innerTrack()), &*((*iter)->innerTrack())) ){
            m_dimuorphan_containstrig++;
      }
    }
    for (auto iter = hightrigmuons.begin();  iter != hightrigmuons.end();  ++iter) {
      if( muJet->muon(0)->innerTrack().isAvailable() &&
          (*iter)->innerTrack().isAvailable() &&
          tamu::helpers::sameTrack(&*(muJet->muon(0)->innerTrack()), &*((*iter)->innerTrack())) ){
            m_dimuorphan_containstrig2++;
      }
      if( muJet->muon(1)->innerTrack().isAvailable() &&
          (*iter)->innerTrack().isAvailable() &&
          tamu::helpers::sameTrack(&*(muJet->muon(1)->innerTrack()), &*((*iter)->innerTrack()))) {
            m_dimuorphan_containstrig2++;
      }
    }

    //@Wei Shi 10.25.2018: Can't use the old method in AOD below since MiniAOD has different precision for the two collections:
    /*if (tamu::helpers::sameTrack(&*track,&*(muJet->muon(0)->innerTrack())) ||
          tamu::helpers::sameTrack(&*track,&*(muJet->muon(1)->innerTrack()))) track_is_muon = true;
    */
    //Instead, get the packed PF candidate associated to the slimmedMuons, and then use the pseudoTrack pointer, this is essentially
    //what was done for the unpackedTracksAndVertices collection(i.e., tracks here)
    //Refer to MiniAOD workbook: https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookMiniAOD2017#Pointers_and_navigation
    //and https://github.com/cms-sw/cmssw/blob/CMSSW_9_4_X/PhysicsTools/PatAlgos/plugins/TrackAndVertexUnpacker.cc#L87
    if ( muJet->vertexValid() ){

      const pat::PackedCandidate* candOrphanDimu0 = dynamic_cast<const pat::PackedCandidate*>(muJet->muon(0)->sourceCandidatePtr(0).get());
      const pat::PackedCandidate* candOrphanDimu1 = dynamic_cast<const pat::PackedCandidate*>(muJet->muon(1)->sourceCandidatePtr(0).get());
      const pat::PackedCandidate* candOrphan = dynamic_cast<const pat::PackedCandidate*>(orphans[0]->sourceCandidatePtr(0).get());

      if ( candOrphanDimu0 != 0 && candOrphanDimu1 != 0 && candOrphan != 0 && candOrphanDimu0->hasTrackDetails() && candOrphanDimu1->hasTrackDetails() && candOrphan->hasTrackDetails() ){
        m_orphan_isoTk = 0.;
        m_orphan_dimu_isoTk = 0.;
        m_orphan_dimu_Mu0_isoTk0p3 = 0.;
        m_orphan_dimu_Mu0_isoTk0p4 = 0.;
        m_orphan_dimu_Mu0_isoTk0p5 = 0.;
        m_orphan_dimu_Mu1_isoTk0p3 = 0.;
        m_orphan_dimu_Mu1_isoTk0p4 = 0.;
        m_orphan_dimu_Mu1_isoTk0p5 = 0.;

        for (reco::TrackCollection::const_iterator track = tracks->begin(); track != tracks->end(); ++track) {
          bool track_is_muon = false;

          if ( tamu::helpers::sameTrack( &*track, &(candOrphanDimu0->pseudoTrack()) ) || tamu::helpers::sameTrack( &*track, &(candOrphanDimu1->pseudoTrack()) ) || tamu::helpers::sameTrack( &*track, &(candOrphan->pseudoTrack()) ) ) track_is_muon = true;

          if ( track_is_muon == false ) {
            /*Iso for orphan associated dimuon*/
            double dphi = tamu::helpers::My_dPhi( muJet->vertexMomentum().phi(), track->phi() );
            double deta = muJet->vertexMomentum().eta() - track->eta();
            double dR   = sqrt(pow(dphi, 2) + pow(deta, 2));
            double dz   = track->dz(beamSpot->position()) - m_orphan_dimu_z;
            if ( dR < iso_track_dR_threshold && track->pt() > iso_track_pt_threshold && fabs(dz) < iso_track_dz_threshold ) m_orphan_dimu_isoTk += track->pt();

            /*Iso for orphan associated dimu mu0*/
            double dPhiMu0 = tamu::helpers::My_dPhi( candOrphanDimu0->pseudoTrack().phi(), track->phi() );
            double dEtaMu0 = candOrphanDimu0->pseudoTrack().eta() - track->eta();
            double dRMu0   = sqrt( dPhiMu0*dPhiMu0 + dEtaMu0*dEtaMu0 );
            double dzMu0   = candOrphanDimu0->pseudoTrack().dz(beamSpot->position()) - track->dz(beamSpot->position());
            if ( dRMu0 < 0.3 && track->pt() > 0.5 && fabs( dzMu0 ) < 0.1 ) m_orphan_dimu_Mu0_isoTk0p3 += track->pt(); //cone size: 0.3
            if ( dRMu0 < 0.4 && track->pt() > 0.5 && fabs( dzMu0 ) < 0.1 ) m_orphan_dimu_Mu0_isoTk0p4 += track->pt(); //cone size: 0.4
            if ( dRMu0 < 0.5 && track->pt() > 0.5 && fabs( dzMu0 ) < 0.1 ) m_orphan_dimu_Mu0_isoTk0p5 += track->pt(); //cone size: 0.5

            /*Iso for orphan associated dimu mu1*/
            double dPhiMu1 = tamu::helpers::My_dPhi( candOrphanDimu1->pseudoTrack().phi(), track->phi() );
            double dEtaMu1 = candOrphanDimu1->pseudoTrack().eta() - track->eta();
            double dRMu1   = sqrt( dPhiMu1*dPhiMu1 + dEtaMu1*dEtaMu1 );
            double dzMu1   = candOrphanDimu1->pseudoTrack().dz(beamSpot->position()) - track->dz(beamSpot->position());
            if ( dRMu1 < 0.3 && track->pt() > 0.5 && fabs( dzMu1 ) < 0.1 ) m_orphan_dimu_Mu1_isoTk0p3 += track->pt(); //cone size: 0.3
            if ( dRMu1 < 0.4 && track->pt() > 0.5 && fabs( dzMu1 ) < 0.1 ) m_orphan_dimu_Mu1_isoTk0p4 += track->pt(); //cone size: 0.4
            if ( dRMu1 < 0.5 && track->pt() > 0.5 && fabs( dzMu1 ) < 0.1 ) m_orphan_dimu_Mu1_isoTk0p5 += track->pt(); //cone size: 0.5

            /*Iso for orphan muon*/
            double dphiOrph = tamu::helpers::My_dPhi( candOrphan->pseudoTrack().phi(), track->phi() );
            double detaOrph = candOrphan->pseudoTrack().eta() - track->eta();
            double dROrph = sqrt(pow(dphiOrph, 2) + pow(detaOrph, 2));
            double dzOrph = candOrphan->pseudoTrack().dz(beamSpot->position()) - track->dz(beamSpot->position());
            if ( dROrph < iso_track_dR_threshold && track->pt() > iso_track_pt_threshold && fabs(dzOrph) < iso_track_dz_threshold ) m_orphan_isoTk += track->pt();

          }//End if track_is_muon
        }//End loop over tracks
      }//end if cast exists
    }//end if vertex valid

    //Register pixel hits info for the orphan-dimu
    m_orphan_dimu_Mu0_hitpix_Phase1              = -1000;
    m_orphan_dimu_Mu1_hitpix_Phase1              = -1000;
    m_orphan_dimu_Mu0_ValidPixelHits             = -1000;
    m_orphan_dimu_Mu1_ValidPixelHits             = -1000;
    m_orphan_dimu_Mu0_ValidPixelBarrelHits       = -1000;
    m_orphan_dimu_Mu1_ValidPixelBarrelHits       = -1000;
    m_orphan_dimu_Mu0_ValidPixelEndcapHits       = -1000;
    m_orphan_dimu_Mu1_ValidPixelEndcapHits       = -1000;
    m_orphan_dimu_Mu0_pixelLayersWithMeasurement = -1000;
    m_orphan_dimu_Mu1_pixelLayersWithMeasurement = -1000;

    for(uint32_t l=0;l<2;l++){
      if ( muJet->muon(l)->innerTrack().isAvailable() ){
        const reco::HitPattern& p = muJet->muon(l)->innerTrack()->hitPattern();

        if( p.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 1) || p.hasValidHitInPixelLayer(PixelSubdetector::PixelEndcap, 1) ||
            p.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 2) || p.hasValidHitInPixelLayer(PixelSubdetector::PixelEndcap, 2) ||
            p.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 3) || p.hasValidHitInPixelLayer(PixelSubdetector::PixelEndcap, 3) ||
            p.hasValidHitInPixelLayer(PixelSubdetector::PixelBarrel, 4) ){
              if(l==0) m_orphan_dimu_Mu0_hitpix_Phase1 = 1;
              if(l==1) m_orphan_dimu_Mu1_hitpix_Phase1 = 1;
        }
        //Refer to: https://github.com/cms-sw/cmssw/blob/master/DataFormats/TrackReco/interface/HitPattern.h#L294
        if ( p.numberOfValidPixelHits() > 0 ){
          if(l==0) m_orphan_dimu_Mu0_ValidPixelHits = p.numberOfValidPixelHits();
          if(l==1) m_orphan_dimu_Mu1_ValidPixelHits = p.numberOfValidPixelHits();
        }
        if ( p.numberOfValidPixelBarrelHits() > 0 ){
          if(l==0) m_orphan_dimu_Mu0_ValidPixelBarrelHits = p.numberOfValidPixelBarrelHits();
          if(l==1) m_orphan_dimu_Mu1_ValidPixelBarrelHits = p.numberOfValidPixelBarrelHits();
        }
        if ( p.numberOfValidPixelEndcapHits() > 0 ){
          if(l==0) m_orphan_dimu_Mu0_ValidPixelEndcapHits = p.numberOfValidPixelEndcapHits();
          if(l==1) m_orphan_dimu_Mu1_ValidPixelEndcapHits = p.numberOfValidPixelEndcapHits();
        }
        if ( p.pixelLayersWithMeasurement() > 0 ){
          if(l==0) m_orphan_dimu_Mu0_pixelLayersWithMeasurement = p.pixelLayersWithMeasurement();
          if(l==1) m_orphan_dimu_Mu1_pixelLayersWithMeasurement = p.pixelLayersWithMeasurement();
        }
      }//orphan-dimu innerTrack available
    }//end for loop l
  }//end event selection: one dimuon + one orphan

  //===============================================================================
  //                      Control Region Event Selection Finish
  //===============================================================================

  // Cut on primary vertex in event
  //std::cout<<"Define PupInfo"<<std::endl;
  edm::Handle<std::vector<PileupSummaryInfo> > PupInfo;
  //std::cout<<"Get by token"<<std::endl;
  if(m_fillGenLevel){
    iEvent.getByToken(m_pileupCollection, PupInfo);
    std::vector<PileupSummaryInfo>::const_iterator PVI;
    for (PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI){
        int BX = PVI->getBunchCrossing();
        //std::cout<<"BX is "<<BX<<std::endl;
        if ( BX == 0 ){
                //std::cout<<"BX should be 0. BX is "<<BX<<std::endl;
                b_npv = PVI->getTrueNumInteractions();
                //std::cout<<"b_npv is "<<b_npv<<std::endl;
                continue;
        }
    }
  }

  edm::Handle<reco::VertexCollection> primaryVertices;
  iEvent.getByToken(m_primaryVertices, primaryVertices);

  b_isVertexOK = false;
  b_orphan_isVertexOK = false;
  for (reco::VertexCollection::const_iterator vertex = primaryVertices->begin();  vertex != primaryVertices->end();  ++vertex) {
    //For main signal events selection
    if (vertex->isValid() && !vertex->isFake() && vertex->tracksSize() >= 4 && fabs(vertex->z()) < 24.) {
      b_isVertexOK = true;
    }
    //For orphan-dimu events selection
    if (vertex->isValid() && !vertex->isFake() && vertex->tracksSize() >= 3 && fabs(vertex->z()) < 24.) {
      b_orphan_isVertexOK = true;
    }
  }

  // Check secondary vertices
  edm::Handle<reco::VertexCollection> secondaryVertices;
  iEvent.getByToken(m_secondaryVertices, secondaryVertices);
  //Check if muon tracks belong to the secondary vertices, if so check the vertex position
  for (reco::VertexCollection::const_iterator sv = secondaryVertices->begin();  sv != secondaryVertices->end();  ++sv) {
    //std::cout<<"SV (x,y,z)[cm]: "<<sv->x()<<", "<<sv->y()<<", "<<sv->z()<<std::endl;
    //std::cout<<"SV tracksSize : "<<sv->tracksSize()<<std::endl;
    for(reco::Vertex::trackRef_iterator tt = sv->tracks_begin(); tt != sv->tracks_end(); ++tt) {
      //std::cout<<"trk pT   [GeV]: "<<tt->castTo<reco::TrackRef>()->pt()<<std::endl;
    }
  }

  if ( m_debug > 0 ) std::cout << m_events << " Stop RECO Level" << std::endl;
  //****************************************************************************
  //                          RECO LEVEL ANALYSIS FINISH
  //****************************************************************************

  //****************************************************************************
  //                            FILL BRANCHES TO TREE
  //****************************************************************************
  if(skimOutput_) { if (b_massC>-1. && b_massF>-1.) m_ttree->Fill(); }
  else m_ttree->Fill();

  if(m_orphan_passOffLineSel) m_ttree_orphan->Fill();
}


// ------------ method called once each job just before starting event loop  ------------
void
CutFlowAnalyzer_MiniAOD::beginJob() {
  std::cout << "BEGIN JOB" << std::endl;
  edm::Service<TFileService> tFileService;

  //****************************************************************************
  //                          Main Tree for Signal Events
  //****************************************************************************
  m_ttree = tFileService->make<TTree>("Events", "Events");

  //****************************************************************************
  //                          EVENT LEVEL BRANCHES
  //****************************************************************************
  m_ttree->Branch("event", &b_event, "event/I");
  m_ttree->Branch("run",   &b_run,   "run/I");
  m_ttree->Branch("lumi",  &b_lumi,  "lumi/I");

  m_ttree->Branch("beamSpot_x", &b_beamSpot_x, "beamSpot_x/F");
  m_ttree->Branch("beamSpot_y", &b_beamSpot_y, "beamSpot_y/F");
  m_ttree->Branch("beamSpot_z", &b_beamSpot_z, "beamSpot_z/F");

  m_ttree->Branch("npv",       &b_npv,       "npv/I");

  //****************************************************************************
  //                          GEN LEVEL BRANCHES
  //****************************************************************************
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

  m_ttree->Branch("genA_dEta",  &b_genA_dEta,  "genA_dEta/F");
  m_ttree->Branch("genA_dPhi",  &b_genA_dPhi,  "genA_dPhi/F");
  m_ttree->Branch("genA_dR",    &b_genA_dR,    "genA_dR/F");

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

  m_ttree->Branch("genA0Mu0_pt", &b_genA0Mu0_pt, "genA0Mu0_pt/F");
  m_ttree->Branch("genA0Mu1_pt", &b_genA0Mu1_pt, "genA0Mu1_pt/F");
  m_ttree->Branch("genA1Mu0_pt", &b_genA1Mu0_pt, "genA1Mu0_pt/F");
  m_ttree->Branch("genA1Mu1_pt", &b_genA1Mu1_pt, "genA1Mu1_pt/F");

  m_ttree->Branch("genA0Mu0_eta", &b_genA0Mu0_eta, "genA0Mu0_eta/F");
  m_ttree->Branch("genA0Mu1_eta", &b_genA0Mu1_eta, "genA0Mu1_eta/F");
  m_ttree->Branch("genA1Mu0_eta", &b_genA1Mu0_eta, "genA1Mu0_eta/F");
  m_ttree->Branch("genA1Mu1_eta", &b_genA1Mu1_eta, "genA1Mu1_eta/F");

  m_ttree->Branch("genA0Mu0_phi", &b_genA0Mu0_phi, "genA0Mu0_phi/F");
  m_ttree->Branch("genA0Mu1_phi", &b_genA0Mu1_phi, "genA0Mu1_phi/F");
  m_ttree->Branch("genA1Mu0_phi", &b_genA1Mu0_phi, "genA1Mu0_phi/F");
  m_ttree->Branch("genA1Mu1_phi", &b_genA1Mu1_phi, "genA1Mu1_phi/F");

  m_ttree->Branch("genA0Mu0_charge", &b_genA0Mu0_charge, "genA0Mu0_charge/F");
  m_ttree->Branch("genA0Mu1_charge", &b_genA0Mu1_charge, "genA0Mu1_charge/F");
  m_ttree->Branch("genA1Mu0_charge", &b_genA1Mu0_charge, "genA1Mu0_charge/F");
  m_ttree->Branch("genA1Mu1_charge", &b_genA1Mu1_charge, "genA1Mu1_charge/F");

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
  m_ttree->Branch("genA0Mu_dCharge",   &b_genA0Mu_dCharge,   "genA0Mu_dCharge/F");
  m_ttree->Branch("genA1Mu_dCharge",   &b_genA1Mu_dCharge,   "genA1Mu_dCharge/F");
  m_ttree->Branch("genA0Mu_dPt",   &b_genA0Mu_dPt,   "genA0Mu_dPt/F");
  m_ttree->Branch("genA1Mu_dPt",   &b_genA1Mu_dPt,   "genA1Mu_dPt/F");
  m_ttree->Branch("genA0Mu_RPt",   &b_genA0Mu_RPt,   "genA0Mu_RPt/F");
  m_ttree->Branch("genA1Mu_RPt",   &b_genA1Mu_RPt,   "genA1Mu_RPt/F");

  m_ttree->Branch("genDiMu0_Eta",  &b_genDiMu0_Eta,  "genDiMu0_Eta/F");
  m_ttree->Branch("genDiMu0_Phi",  &b_genDiMu0_Phi,  "genDiMu0_Phi/F");
  m_ttree->Branch("genDiMu0_M",    &b_genDiMu0_M,    "genDiMu0_M/F");
  m_ttree->Branch("genDiMu0_Pt",   &b_genDiMu0_Pt,   "genDiMu0_Pt/F");
  m_ttree->Branch("genDiMu1_Eta",  &b_genDiMu1_Eta,  "genDiMu1_Eta/F");
  m_ttree->Branch("genDiMu1_Phi",  &b_genDiMu1_Phi,  "genDiMu1_Phi/F");
  m_ttree->Branch("genDiMu1_M",    &b_genDiMu1_M,    "genDiMu1_M/F");
  m_ttree->Branch("genDiMu1_Pt",   &b_genDiMu1_Pt,   "genDiMu1_Pt/F");
  m_ttree->Branch("genDiMu_dEta",  &b_genDiMu_dEta,  "genDiMu_dEta/F");
  m_ttree->Branch("genDiMu_dPhi",  &b_genDiMu_dPhi,  "genDiMu_dPhi/F");
  m_ttree->Branch("genDiMu_dR",    &b_genDiMu_dR,    "genDiMu_dR/F");
  m_ttree->Branch("genDiMu_dM",    &b_genDiMu_dM,    "genDiMu_dM/F");

  m_ttree->Branch("genFakeDiMu0_Eta",  &b_genFakeDiMu0_Eta,  "genFakeDiMu0_Eta/F");
  m_ttree->Branch("genFakeDiMu0_Phi",  &b_genFakeDiMu0_Phi,  "genFakeDiMu0_Phi/F");
  m_ttree->Branch("genFakeDiMu0_M",    &b_genFakeDiMu0_M,    "genFakeDiMu0_M/F");
  m_ttree->Branch("genFakeDiMu0_Pt",   &b_genFakeDiMu0_Pt,   "genFakeDiMu0_Pt/F");
  m_ttree->Branch("genFakeDiMu1_Eta",  &b_genFakeDiMu1_Eta,  "genFakeDiMu1_Eta/F");
  m_ttree->Branch("genFakeDiMu1_Phi",  &b_genFakeDiMu1_Phi,  "genFakeDiMu1_Phi/F");
  m_ttree->Branch("genFakeDiMu1_M",    &b_genFakeDiMu1_M,    "genFakeDiMu1_M/F");
  m_ttree->Branch("genFakeDiMu1_Pt",   &b_genFakeDiMu1_Pt,   "genFakeDiMu1_Pt/F");
  m_ttree->Branch("genFakeDiMu_dEta",  &b_genFakeDiMu_dEta,  "genFakeDiMu_dEta/F");
  m_ttree->Branch("genFakeDiMu_dPhi",  &b_genFakeDiMu_dPhi,  "genFakeDiMu_dPhi/F");
  m_ttree->Branch("genFakeDiMu_dR",    &b_genFakeDiMu_dR,    "genFakeDiMu_dR/F");
  m_ttree->Branch("genFakeDiMu_dM",    &b_genFakeDiMu_dM,    "genFakeDiMu_dM/F");
  m_ttree->Branch("gen_ddPhi",         &b_gen_ddPhi,         "gen_ddPhi/F");

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

  //For signal HLT study
  m_ttree->Branch("has1GenMu16",       &b_has1GenMu16,      "has1GenMu16/O");
  m_ttree->Branch("has1GenMu6",        &b_has1GenMu6,       "has1GenMu6/O");
  m_ttree->Branch("has1GenMu16Mu6Mu6", &b_has1GenMu16Mu6Mu6,"has1GenMu16Mu6Mu6/O");

  //****************************************************************************
  //                          RECO LEVEL BRANCHES
  //****************************************************************************
  m_ttree->Branch("nRecoMu",     &b_nRecoMu,     "nRecoMu/I");
  m_ttree->Branch("nSAMu",       &b_nSAMu,       "nSAMu/I");
  m_ttree->Branch("dimuC_nSAMu", &b_dimuC_nSAMu, "dimuC_nSAMu/I");
  m_ttree->Branch("dimuF_nSAMu", &b_dimuF_nSAMu, "dimuF_nSAMu/I");
  m_ttree->Branch("nNonTrackerMu",       &b_nNonTrackerMu,       "nNonTrackerMu/I");
  m_ttree->Branch("dimuC_nNonTrackerMu", &b_dimuC_nNonTrackerMu, "dimuC_nNonTrackerMu/I");
  m_ttree->Branch("dimuF_nNonTrackerMu", &b_dimuF_nNonTrackerMu, "dimuF_nNonTrackerMu/I");
  m_ttree->Branch("nMuPairs",  &b_nMuPairs,  "nMuPairs/I");
  m_ttree->Branch("nDaughterPerMuPair", &b_nDaughterPerMuPair, "nDaughterPerMuPair/F");
  m_ttree->Branch("nMuJets",   &b_nMuJets,   "nMuJets/I");
  m_ttree->Branch("nDaughterPerMuJet",  &b_nDaughterPerMuJet,  "nDaughterPerMuJet/F");
  m_ttree->Branch("nOrphans",  &b_nOrphans,  "nOrphans/I");

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

  m_ttree->Branch("diMuonC_FittedVtx_dR",  &b_diMuonC_FittedVtx_dR,  "diMuonC_FittedVtx_dR/F");
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
  m_ttree->Branch("diMuonC_FittedVtx_chi2",&b_diMuonC_FittedVtx_chi2,"diMuonC_FittedVtx_chi2/F");
  m_ttree->Branch("diMuonC_FittedVtx_ndof",&b_diMuonC_FittedVtx_ndof,"diMuonC_FittedVtx_ndof/F");
  m_ttree->Branch("diMuonC_FittedVtx_prob",&b_diMuonC_FittedVtx_prob,"diMuonC_FittedVtx_prob/F");

  m_ttree->Branch("diMuonF_FittedVtx_dR",  &b_diMuonF_FittedVtx_dR,  "diMuonF_FittedVtx_dR/F");
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
  m_ttree->Branch("diMuonF_FittedVtx_chi2",&b_diMuonF_FittedVtx_chi2,"diMuonF_FittedVtx_chi2/F");
  m_ttree->Branch("diMuonF_FittedVtx_ndof",&b_diMuonF_FittedVtx_ndof,"diMuonF_FittedVtx_ndof/F");
  m_ttree->Branch("diMuonF_FittedVtx_prob",&b_diMuonF_FittedVtx_prob,"diMuonF_FittedVtx_prob/F");

  m_ttree->Branch("diMuonC_IsoTk_FittedVtx", &b_diMuonC_IsoTk_FittedVtx, "diMuonC_IsoTk_FittedVtx/F");
  m_ttree->Branch("diMuonCMu0_IsoTk0p3_FittedVtx", &b_diMuonCMu0_IsoTk0p3_FittedVtx, "diMuonCMu0_IsoTk0p3_FittedVtx/F");
  m_ttree->Branch("diMuonCMu0_IsoTk0p4_FittedVtx", &b_diMuonCMu0_IsoTk0p4_FittedVtx, "diMuonCMu0_IsoTk0p4_FittedVtx/F");
  m_ttree->Branch("diMuonCMu0_IsoTk0p5_FittedVtx", &b_diMuonCMu0_IsoTk0p5_FittedVtx, "diMuonCMu0_IsoTk0p5_FittedVtx/F");
  m_ttree->Branch("diMuonCMu1_IsoTk0p3_FittedVtx", &b_diMuonCMu1_IsoTk0p3_FittedVtx, "diMuonCMu1_IsoTk0p3_FittedVtx/F");
  m_ttree->Branch("diMuonCMu1_IsoTk0p4_FittedVtx", &b_diMuonCMu1_IsoTk0p4_FittedVtx, "diMuonCMu1_IsoTk0p4_FittedVtx/F");
  m_ttree->Branch("diMuonCMu1_IsoTk0p5_FittedVtx", &b_diMuonCMu1_IsoTk0p5_FittedVtx, "diMuonCMu1_IsoTk0p5_FittedVtx/F");

  m_ttree->Branch("diMuonF_IsoTk_FittedVtx", &b_diMuonF_IsoTk_FittedVtx, "diMuonF_IsoTk_FittedVtx/F");
  m_ttree->Branch("diMuonFMu0_IsoTk0p3_FittedVtx", &b_diMuonFMu0_IsoTk0p3_FittedVtx, "diMuonFMu0_IsoTk0p3_FittedVtx/F");
  m_ttree->Branch("diMuonFMu0_IsoTk0p4_FittedVtx", &b_diMuonFMu0_IsoTk0p4_FittedVtx, "diMuonFMu0_IsoTk0p4_FittedVtx/F");
  m_ttree->Branch("diMuonFMu0_IsoTk0p5_FittedVtx", &b_diMuonFMu0_IsoTk0p5_FittedVtx, "diMuonFMu0_IsoTk0p5_FittedVtx/F");
  m_ttree->Branch("diMuonFMu1_IsoTk0p3_FittedVtx", &b_diMuonFMu1_IsoTk0p3_FittedVtx, "diMuonFMu1_IsoTk0p3_FittedVtx/F");
  m_ttree->Branch("diMuonFMu1_IsoTk0p4_FittedVtx", &b_diMuonFMu1_IsoTk0p4_FittedVtx, "diMuonFMu1_IsoTk0p4_FittedVtx/F");
  m_ttree->Branch("diMuonFMu1_IsoTk0p5_FittedVtx", &b_diMuonFMu1_IsoTk0p5_FittedVtx, "diMuonFMu1_IsoTk0p5_FittedVtx/F");

  m_ttree->Branch("diMuons_dz_FittedVtx",  &b_diMuons_dz_FittedVtx,  "diMuons_dz_FittedVtx/F");

  m_ttree->Branch("nMuHasValidHitInPixel", &b_nMuHasValidHitInPixel, "nMuHasValidHitInPixel/I");
  m_ttree->Branch("diMuonC_m1_FittedVtx_hitpix_Phase1", &b_diMuonC_m1_FittedVtx_hitpix_Phase1, "diMuonC_m1_FittedVtx_hitpix_Phase1/I");
  m_ttree->Branch("diMuonC_m2_FittedVtx_hitpix_Phase1", &b_diMuonC_m2_FittedVtx_hitpix_Phase1, "diMuonC_m2_FittedVtx_hitpix_Phase1/I");
  m_ttree->Branch("diMuonF_m1_FittedVtx_hitpix_Phase1", &b_diMuonF_m1_FittedVtx_hitpix_Phase1, "diMuonF_m1_FittedVtx_hitpix_Phase1/I");
  m_ttree->Branch("diMuonF_m2_FittedVtx_hitpix_Phase1", &b_diMuonF_m2_FittedVtx_hitpix_Phase1, "diMuonF_m2_FittedVtx_hitpix_Phase1/I");

  m_ttree->Branch("diMuonC_m1_FittedVtx_ValidPixelHits", &b_diMuonC_m1_FittedVtx_ValidPixelHits, "diMuonC_m1_FittedVtx_ValidPixelHits/I");
  m_ttree->Branch("diMuonC_m2_FittedVtx_ValidPixelHits", &b_diMuonC_m2_FittedVtx_ValidPixelHits, "diMuonC_m2_FittedVtx_ValidPixelHits/I");
  m_ttree->Branch("diMuonF_m1_FittedVtx_ValidPixelHits", &b_diMuonF_m1_FittedVtx_ValidPixelHits, "diMuonF_m1_FittedVtx_ValidPixelHits/I");
  m_ttree->Branch("diMuonF_m2_FittedVtx_ValidPixelHits", &b_diMuonF_m2_FittedVtx_ValidPixelHits, "diMuonF_m2_FittedVtx_ValidPixelHits/I");

  m_ttree->Branch("diMuonC_m1_FittedVtx_ValidPixelBarrelHits", &b_diMuonC_m1_FittedVtx_ValidPixelBarrelHits, "diMuonC_m1_FittedVtx_ValidPixelBarrelHits/I");
  m_ttree->Branch("diMuonC_m2_FittedVtx_ValidPixelBarrelHits", &b_diMuonC_m2_FittedVtx_ValidPixelBarrelHits, "diMuonC_m2_FittedVtx_ValidPixelBarrelHits/I");
  m_ttree->Branch("diMuonF_m1_FittedVtx_ValidPixelBarrelHits", &b_diMuonF_m1_FittedVtx_ValidPixelBarrelHits, "diMuonF_m1_FittedVtx_ValidPixelBarrelHits/I");
  m_ttree->Branch("diMuonF_m2_FittedVtx_ValidPixelBarrelHits", &b_diMuonF_m2_FittedVtx_ValidPixelBarrelHits, "diMuonF_m2_FittedVtx_ValidPixelBarrelHits/I");

  m_ttree->Branch("diMuonC_m1_FittedVtx_ValidPixelEndcapHits", &b_diMuonC_m1_FittedVtx_ValidPixelEndcapHits, "diMuonC_m1_FittedVtx_ValidPixelEndcapHits/I");
  m_ttree->Branch("diMuonC_m2_FittedVtx_ValidPixelEndcapHits", &b_diMuonC_m2_FittedVtx_ValidPixelEndcapHits, "diMuonC_m2_FittedVtx_ValidPixelEndcapHits/I");
  m_ttree->Branch("diMuonF_m1_FittedVtx_ValidPixelEndcapHits", &b_diMuonF_m1_FittedVtx_ValidPixelEndcapHits, "diMuonF_m1_FittedVtx_ValidPixelEndcapHits/I");
  m_ttree->Branch("diMuonF_m2_FittedVtx_ValidPixelEndcapHits", &b_diMuonF_m2_FittedVtx_ValidPixelEndcapHits, "diMuonF_m2_FittedVtx_ValidPixelEndcapHits/I");

  m_ttree->Branch("diMuonC_m1_FittedVtx_pixelLayersWithMeasurement", &b_diMuonC_m1_FittedVtx_pixelLayersWithMeasurement, "diMuonC_m1_FittedVtx_pixelLayersWithMeasurement/I");
  m_ttree->Branch("diMuonC_m2_FittedVtx_pixelLayersWithMeasurement", &b_diMuonC_m2_FittedVtx_pixelLayersWithMeasurement, "diMuonC_m2_FittedVtx_pixelLayersWithMeasurement/I");
  m_ttree->Branch("diMuonF_m1_FittedVtx_pixelLayersWithMeasurement", &b_diMuonF_m1_FittedVtx_pixelLayersWithMeasurement, "diMuonF_m1_FittedVtx_pixelLayersWithMeasurement/I");
  m_ttree->Branch("diMuonF_m2_FittedVtx_pixelLayersWithMeasurement", &b_diMuonF_m2_FittedVtx_pixelLayersWithMeasurement, "diMuonF_m2_FittedVtx_pixelLayersWithMeasurement/I");

  m_ttree->Branch("massC",                          &b_massC,                          "massC/F");
  m_ttree->Branch("massF",                          &b_massF,                          "massF/F");
  m_ttree->Branch("isoC_1mm",                       &b_isoC_1mm,                       "isoC_1mm/F");
  m_ttree->Branch("isoF_1mm",                       &b_isoF_1mm,                       "isoF_1mm/F");

  m_ttree->Branch("muJetC_Mu0_pt",                  &b_muJetC_Mu0_pt,                  "muJetC_Mu0_pt/F");
  m_ttree->Branch("muJetC_Mu1_pt",                  &b_muJetC_Mu1_pt,                  "muJetC_Mu1_pt/F");
  m_ttree->Branch("muJetC_Mu0_eta",                 &b_muJetC_Mu0_eta,                 "muJetC_Mu0_eta/F");
  m_ttree->Branch("muJetC_Mu1_eta",                 &b_muJetC_Mu1_eta,                 "muJetC_Mu1_eta/F");
  m_ttree->Branch("muJetC_Mu0_phi",                 &b_muJetC_Mu0_phi,                 "muJetC_Mu0_phi/F");
  m_ttree->Branch("muJetC_Mu1_phi",                 &b_muJetC_Mu1_phi,                 "muJetC_Mu1_phi/F");
  m_ttree->Branch("muJetC_Mu0_charge",              &b_muJetC_Mu0_charge,              "muJetC_Mu0_charge/F");
  m_ttree->Branch("muJetC_Mu1_charge",              &b_muJetC_Mu1_charge,              "muJetC_Mu1_charge/F");

  m_ttree->Branch("muJetF_Mu0_pt",                  &b_muJetF_Mu0_pt,                  "muJetF_Mu0_pt/F");
  m_ttree->Branch("muJetF_Mu1_pt",                  &b_muJetF_Mu1_pt,                  "muJetF_Mu1_pt/F");
  m_ttree->Branch("muJetF_Mu0_eta",                 &b_muJetF_Mu0_eta,                 "muJetF_Mu0_eta/F");
  m_ttree->Branch("muJetF_Mu1_eta",                 &b_muJetF_Mu1_eta,                 "muJetF_Mu1_eta/F");
  m_ttree->Branch("muJetF_Mu0_phi",                 &b_muJetF_Mu0_phi,                 "muJetF_Mu0_phi/F");
  m_ttree->Branch("muJetF_Mu1_phi",                 &b_muJetF_Mu1_phi,                 "muJetF_Mu1_phi/F");
  m_ttree->Branch("muJetF_Mu0_charge",              &b_muJetF_Mu0_charge,              "muJetF_Mu0_charge/F");
  m_ttree->Branch("muJetF_Mu1_charge",              &b_muJetF_Mu1_charge,              "muJetF_Mu1_charge/F");

  m_ttree->Branch("reco4mu_pt",                     &b_reco4mu_pt,                     "reco4mu_pt/F");
  m_ttree->Branch("reco4mu_eta",                    &b_reco4mu_eta,                    "reco4mu_eta/F");
  m_ttree->Branch("reco4mu_phi",                    &b_reco4mu_phi,                    "reco4mu_phi/F");
  m_ttree->Branch("reco4mu_m",                      &b_reco4mu_m,                      "reco4mu_m/F");

  m_ttree->Branch("recoFakeDiMu0_pt",               &b_recoFakeDiMu0_pt,               "recoFakeDiMu0_pt/F");
  m_ttree->Branch("recoFakeDiMu1_pt",               &b_recoFakeDiMu1_pt,               "recoFakeDiMu1_pt/F");
  m_ttree->Branch("recoFakeDiMu0_eta",              &b_recoFakeDiMu0_eta,              "recoFakeDiMu0_eta/F");
  m_ttree->Branch("recoFakeDiMu1_eta",              &b_recoFakeDiMu1_eta,              "recoFakeDiMu1_eta/F");
  m_ttree->Branch("recoFakeDiMu0_phi",              &b_recoFakeDiMu0_phi,              "recoFakeDiMu0_phi/F");
  m_ttree->Branch("recoFakeDiMu1_phi",              &b_recoFakeDiMu1_phi,              "recoFakeDiMu1_phi/F");
  m_ttree->Branch("recoFakeDiMu0_m",                &b_recoFakeDiMu0_m,                "recoFakeDiMu0_m/F");
  m_ttree->Branch("recoFakeDiMu1_m",                &b_recoFakeDiMu1_m,                "recoFakeDiMu1_m/F");

  m_ttree->Branch("dEtaRePairedDimuA",              &b_dEtaRePairedDimuA,              "dEtaRePairedDimuA/F");
  m_ttree->Branch("dEtaRePairedDimuB",              &b_dEtaRePairedDimuB,              "dEtaRePairedDimuB/F");
  m_ttree->Branch("dPhiRePairedDimuA",              &b_dPhiRePairedDimuA,              "dPhiRePairedDimuA/F");
  m_ttree->Branch("dPhiRePairedDimuB",              &b_dPhiRePairedDimuB,              "dPhiRePairedDimuB/F");
  m_ttree->Branch("dRrePairedDimuA",                &b_dRrePairedDimuA,                "dRrePairedDimuA/F");
  m_ttree->Branch("dRrePairedDimuB",                &b_dRrePairedDimuB,                "dRrePairedDimuB/F");

  m_ttree->Branch("recoRePaired2muleading_m",       &b_recoRePaired2muleading_m,       "recoRePaired2muleading_m/F");
  m_ttree->Branch("recoRePaired2mutrailing_m",      &b_recoRePaired2mutrailing_m,      "recoRePaired2mutrailing_m/F");
  m_ttree->Branch("recoRePaired2muleading_dR",      &b_recoRePaired2muleading_dR,      "recoRePaired2muleading_dR/F");
  m_ttree->Branch("recoRePaired2mutrailing_dR",     &b_recoRePaired2mutrailing_dR,     "recoRePaired2mutrailing_dR/F");

  // RECO Level Selectors
  m_ttree->Branch("is1SelMu17",                     &b_is1SelMu17,                     "is1SelMu17/O");
  m_ttree->Branch("is2SelMu8",                      &b_is2SelMu8,                      "is2SelMu8/O");
  m_ttree->Branch("is3SelMu8",                      &b_is3SelMu8,                      "is3SelMu8/O");
  m_ttree->Branch("is4SelMu8",                      &b_is4SelMu8,                      "is4SelMu8/O");

  m_ttree->Branch("is2MuJets",                      &b_is2MuJets,                      "is2MuJets/O");
  m_ttree->Branch("is2DiMuons",                     &b_is2DiMuons,                     "is2DiMuons/O");
  m_ttree->Branch("is2DiMuonsFittedVtxOK",          &b_is2DiMuonsFittedVtxOK,          "is2DiMuonsFittedVtxOK/O");

  m_ttree->Branch("isSignalHLTFired",               &b_isSignalHLTFired,               "isSignalHLTFired/O");
  //Start Debug
  /*
  m_ttree->Branch("isSignalHLT_0_Fired",            &b_isSignalHLT_0_Fired,            "isSignalHLT_0_Fired/O");
  m_ttree->Branch("isSignalHLT_1_Fired",            &b_isSignalHLT_1_Fired,            "isSignalHLT_1_Fired/O");
  m_ttree->Branch("isSignalHLT_2_Fired",            &b_isSignalHLT_2_Fired,            "isSignalHLT_2_Fired/O");
  m_ttree->Branch("isSignalHLT_3_Fired",            &b_isSignalHLT_3_Fired,            "isSignalHLT_3_Fired/O");
  m_ttree->Branch("isSignalHLT_4_Fired",            &b_isSignalHLT_4_Fired,            "isSignalHLT_4_Fired/O");
  m_ttree->Branch("isSignalHLT_5_Fired",            &b_isSignalHLT_5_Fired,            "isSignalHLT_5_Fired/O");
  m_ttree->Branch("isSignalHLT_6_Fired",            &b_isSignalHLT_6_Fired,            "isSignalHLT_6_Fired/O");
  m_ttree->Branch("isSignalHLT_7_Fired",            &b_isSignalHLT_7_Fired,            "isSignalHLT_7_Fired/O");
  m_ttree->Branch("isSignalHLT_8_Fired",            &b_isSignalHLT_8_Fired,            "isSignalHLT_8_Fired/O");
  m_ttree->Branch("isSignalHLT_9_Fired",            &b_isSignalHLT_9_Fired,            "isSignalHLT_9_Fired/O");
  m_ttree->Branch("isSignalHLT_10_Fired",           &b_isSignalHLT_10_Fired,           "isSignalHLT_10_Fired/O");
  m_ttree->Branch("isSignalHLT_11_Fired",           &b_isSignalHLT_11_Fired,           "isSignalHLT_11_Fired/O");
  m_ttree->Branch("isSignalHLT_12_Fired",           &b_isSignalHLT_12_Fired,           "isSignalHLT_12_Fired/O");
  m_ttree->Branch("isSignalHLT_13_Fired",           &b_isSignalHLT_13_Fired,           "isSignalHLT_13_Fired/O");
  m_ttree->Branch("isSignalHLT_14_Fired",           &b_isSignalHLT_14_Fired,           "isSignalHLT_14_Fired/O");
  m_ttree->Branch("isSignalHLT_15_Fired",           &b_isSignalHLT_15_Fired,           "isSignalHLT_15_Fired/O");
  m_ttree->Branch("isSignalHLT_16_Fired",           &b_isSignalHLT_16_Fired,           "isSignalHLT_16_Fired/O");
  m_ttree->Branch("isSignalHLT_17_Fired",           &b_isSignalHLT_17_Fired,           "isSignalHLT_17_Fired/O");
  m_ttree->Branch("isSignalHLT_18_Fired",           &b_isSignalHLT_18_Fired,           "isSignalHLT_18_Fired/O");
  m_ttree->Branch("isSignalHLT_19_Fired",           &b_isSignalHLT_19_Fired,           "isSignalHLT_19_Fired/O");*/
  //End Debug
  m_ttree->Branch("NPATJet",        &b_NPATJet,        "NPATJet/I");
  m_ttree->Branch("NPATJetTightB",  &b_NPATJetTightB,  "NPATJetTightB/I");
  m_ttree->Branch("NPATJetMediumB", &b_NPATJetMediumB, "NPATJetMediumB/I");
  m_ttree->Branch("NPATJetLooseB",  &b_NPATJetLooseB,  "NPATJetLooseB/I");
  m_ttree->Branch("isControlHLT16Fired",            &b_isControlHLT16Fired,            "isControlHLT16Fired/O");
  m_ttree->Branch("isControlHLT6Fired",             &b_isControlHLT6Fired,             "isControlHLT6Fired/O");
  m_ttree->Branch("isSignalHLTL1Fired",             &b_isSignalHLTL1Fired,             "isSignalHLTL1Fired/O");
  m_ttree->Branch("is2DiMuonsMassOK_FittedVtx",     &b_is2DiMuonsMassOK_FittedVtx,     "is2DiMuonsMassOK_FittedVtx/O");
  m_ttree->Branch("isVertexOK",                     &b_isVertexOK,                     "isVertexOK/O");
  m_ttree->Branch("hltPaths",  &b_hltPaths);

  //****************************************************************************
  //                       Main Tree for Control Region Events
  //****************************************************************************
  m_ttree_orphan = tFileService->make<TTree>("Events_orphan", "Events_orphan");
  m_ttree_orphan->Branch("run",   &b_run,   "run/I");
  m_ttree_orphan->Branch("lumi",  &b_lumi,  "lumi/I");
  m_ttree_orphan->Branch("event", &b_event, "event/I");
  m_ttree_orphan->Branch("orph_isSignalHLTFired", &b_isSignalHLTFired,         "orph_isSignalHLTFired/O");
  m_ttree_orphan->Branch("orph_isVertexOK",       &b_orphan_isVertexOK,        "orph_isVertexOK/O");
  m_ttree_orphan->Branch("containstrig",          &m_dimuorphan_containstrig,  "containstrig/I");
  m_ttree_orphan->Branch("containstrig2",         &m_dimuorphan_containstrig2, "containstrig2/I");
  m_ttree_orphan->Branch("orph_dimu_nSAMu",                          &m_orphan_dimu_nSAMu,                          "orph_dimu_nSAMu/I");
  m_ttree_orphan->Branch("orph_dimu_nNonTrackerMu",                  &m_orphan_dimu_nNonTrackerMu,                  "orph_dimu_nNonTrackerMu/I");
  m_ttree_orphan->Branch("orph_nSAMu",                               &m_orphan_nSAMu,                               "orph_nSAMu/I");
  m_ttree_orphan->Branch("orph_nNonTrackerMu",                       &m_orphan_nNonTrackerMu,                       "orph_nNonTrackerMu/I");
  m_ttree_orphan->Branch("orph_dimu_Mu0_hitpix_Phase1",              &m_orphan_dimu_Mu0_hitpix_Phase1,              "orph_dimu_Mu0_hitpix_Phase1/I");
  m_ttree_orphan->Branch("orph_dimu_Mu1_hitpix_Phase1",              &m_orphan_dimu_Mu1_hitpix_Phase1,              "orph_dimu_Mu1_hitpix_Phase1/I");
  m_ttree_orphan->Branch("orph_dimu_Mu0_ValidPixelHits",             &m_orphan_dimu_Mu0_ValidPixelHits,             "orph_dimu_Mu0_ValidPixelHits/I");
  m_ttree_orphan->Branch("orph_dimu_Mu1_ValidPixelHits",             &m_orphan_dimu_Mu1_ValidPixelHits,             "orph_dimu_Mu1_ValidPixelHits/I");
  m_ttree_orphan->Branch("orph_dimu_Mu0_ValidPixelBarrelHits",       &m_orphan_dimu_Mu0_ValidPixelBarrelHits,       "orph_dimu_Mu0_ValidPixelBarrelHits/I");
  m_ttree_orphan->Branch("orph_dimu_Mu1_ValidPixelBarrelHits",       &m_orphan_dimu_Mu1_ValidPixelBarrelHits,       "orph_dimu_Mu1_ValidPixelBarrelHits/I");
  m_ttree_orphan->Branch("orph_dimu_Mu0_ValidPixelEndcapHits",       &m_orphan_dimu_Mu0_ValidPixelEndcapHits,       "orph_dimu_Mu0_ValidPixelEndcapHits/I");
  m_ttree_orphan->Branch("orph_dimu_Mu1_ValidPixelEndcapHits",       &m_orphan_dimu_Mu1_ValidPixelEndcapHits,       "orph_dimu_Mu1_ValidPixelEndcapHits/I");
  m_ttree_orphan->Branch("orph_dimu_Mu0_pixelLayersWithMeasurement", &m_orphan_dimu_Mu0_pixelLayersWithMeasurement, "orph_dimu_Mu0_pixelLayersWithMeasurement/I");
  m_ttree_orphan->Branch("orph_dimu_Mu1_pixelLayersWithMeasurement", &m_orphan_dimu_Mu1_pixelLayersWithMeasurement, "orph_dimu_Mu1_pixelLayersWithMeasurement/I");
  m_ttree_orphan->Branch("orph_dimu_dR",   &m_orphan_dimu_dR,   "orph_dimu_dR/F");
  m_ttree_orphan->Branch("orph_dimu_mass", &m_orphan_dimu_mass, "orph_dimu_mass/F");
  m_ttree_orphan->Branch("orph_dimu_z",    &m_orphan_dimu_z,    "orph_dimu_z/F");
  m_ttree_orphan->Branch("orph_dimu_Lxy",  &m_orphan_dimu_Lxy,  "orph_dimu_Lxy/F");
  m_ttree_orphan->Branch("orph_dimu_L",    &m_orphan_dimu_L,    "orph_dimu_L/F");
  m_ttree_orphan->Branch("orph_dimu_chi2", &m_orphan_dimu_chi2, "orph_dimu_chi2/F");
  m_ttree_orphan->Branch("orph_dimu_ndof", &m_orphan_dimu_ndof, "orph_dimu_ndof/F");
  m_ttree_orphan->Branch("orph_dimu_prob", &m_orphan_dimu_prob, "orph_dimu_prob/F");
  m_ttree_orphan->Branch("orph_isoTk",               &m_orphan_isoTk,               "orph_isoTk/F");
  m_ttree_orphan->Branch("orph_dimu_isoTk",          &m_orphan_dimu_isoTk,          "orph_dimu_isoTk/F");
  m_ttree_orphan->Branch("orph_dimu_Mu0_isoTk0p3",   &m_orphan_dimu_Mu0_isoTk0p3,   "orph_dimu_Mu0_isoTk0p3/F");
  m_ttree_orphan->Branch("orph_dimu_Mu0_isoTk0p4",   &m_orphan_dimu_Mu0_isoTk0p4,   "orph_dimu_Mu0_isoTk0p4/F");
  m_ttree_orphan->Branch("orph_dimu_Mu0_isoTk0p5",   &m_orphan_dimu_Mu0_isoTk0p5,   "orph_dimu_Mu0_isoTk0p5/F");
  m_ttree_orphan->Branch("orph_dimu_Mu1_isoTk0p3",   &m_orphan_dimu_Mu1_isoTk0p3,   "orph_dimu_Mu1_isoTk0p3/F");
  m_ttree_orphan->Branch("orph_dimu_Mu1_isoTk0p4",   &m_orphan_dimu_Mu1_isoTk0p4,   "orph_dimu_Mu1_isoTk0p4/F");
  m_ttree_orphan->Branch("orph_dimu_Mu1_isoTk0p5",   &m_orphan_dimu_Mu1_isoTk0p5,   "orph_dimu_Mu1_isoTk0p5/F");
  m_ttree_orphan->Branch("orph_passOffLineSel",      &m_orphan_passOffLineSel,      "orph_passOffLineSel/O");
  m_ttree_orphan->Branch("orph_passOffLineSelPtEta", &m_orphan_passOffLineSelPtEta, "orph_passOffLineSelPtEta/O");
  m_ttree_orphan->Branch("orph_AllTrackerMu",        &m_orphan_AllTrackerMu,        "orph_AllTrackerMu/O");
  m_ttree_orphan->Branch("orph_PtOrph",  &m_orphan_PtOrph,  "orph_PtOrph/F");
  m_ttree_orphan->Branch("orph_EtaOrph", &m_orphan_EtaOrph, "orph_EtaOrph/F");
  m_ttree_orphan->Branch("orph_PtMu0",   &m_orphan_PtMu0,   "orph_PtMu0/F");
  m_ttree_orphan->Branch("orph_EtaMu0",  &m_orphan_EtaMu0,  "orph_EtaMu0/F");
  m_ttree_orphan->Branch("orph_PtMu1",   &m_orphan_PtMu1,   "orph_PtMu1/F");
  m_ttree_orphan->Branch("orph_EtaMu1",  &m_orphan_EtaMu1,  "orph_EtaMu1/F");

  m_ttree_orphan->Branch("NPATJet",        &b_NPATJet,        "NPATJet/I");
  m_ttree_orphan->Branch("NPATJetTightB",  &b_NPATJetTightB,  "NPATJetTightB/I");
  m_ttree_orphan->Branch("NPATJetMediumB", &b_NPATJetMediumB, "NPATJetMediumB/I");
  m_ttree_orphan->Branch("NPATJetLooseB",  &b_NPATJetLooseB,  "NPATJetLooseB/I");

}//end beginJob

// ------------ method called once each job just after ending the event loop  ------------
void
CutFlowAnalyzer_MiniAOD::endJob()
{
  using namespace std;
  cout << "END JOB" << endl;
}

void CutFlowAnalyzer_MiniAOD::FillTrigInfo( TH1F * h1, const edm::TriggerNames& triggerNames, std::map<int,std::string> nameAndNumb )
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

// ------------ method called when ending the processing of a run  ------------
/*void CutFlowAnalyzer_MiniAOD::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
/*
// ------------ method called when starting to processes a luminosity block  ------------
void CutFlowAnalyzer_MiniAOD::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
/*
// ------------ method called when ending the processing of a luminosity block  ------------
void CutFlowAnalyzer_MiniAOD::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void CutFlowAnalyzer_MiniAOD::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//Indentation change
//define this as a plug-in
DEFINE_FWK_MODULE(CutFlowAnalyzer_MiniAOD);
