// -*- C++ -*-
//
// Package:    FitNtuple
// Class:      FitNtuple
// 
/**\class FitNtuple FitNtuple.cc MuJetAnalysis/FitNtuple/src/FitNtuple.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  James Pivarski
//         Created:  Fri Nov 19 17:04:33 CST 2010
// $Id: FitNtuple.cc,v 1.32 2013/06/27 08:16:37 pakhotin Exp $
//
//

// system include files
#include <memory>

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
#include "TrackPropagation/SteppingHelixPropagator/interface/SteppingHelixPropagator.h"

#include "MuJetAnalysis/DataFormats/interface/MultiMuon.h"

// class declaration
class FitNtuple : public edm::EDAnalyzer {

public:
  explicit FitNtuple(const edm::ParameterSet&);
  ~FitNtuple();

private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

  // ----------member data ---------------------------

  // input parameters
  edm::InputTag m_muons;
  edm::InputTag m_muonsTriggerMatch;
  edm::InputTag m_muJets;
  edm::InputTag m_muJetOrphans;
  double m_trigpt;
  std::string m_dataset;

  TRandom3 m_trandom3;

  // all ntuples need these variables
  Int_t m_run;       // run lumi, and event number so that we can look at
  Int_t m_lumi;      // interesting cases in the event display
  Int_t m_event;     //
      
  Int_t m_trigger; // satisfied trigger?  0 = failed all
                   //                     2 = passed HLT_Mu9
                   //                     4 = passed HLT_Mu11
                   //                     8 = passed HLT_Mu15_v1
                   //                    16 = passed HLT_Mu30_v*
                   // it is negative if there are no pT > 15 GeV/c, |eta| < 0.9 muons matched to L3
  Int_t m_trigger15;
  Int_t m_trigger20;
  Int_t m_trigger24;
  Int_t m_trigger30;
  Int_t m_trigger40;
  Int_t m_trigger40eta;


  Int_t m_primaryverticessize;
  Int_t m_generaltrackssize;

  Int_t m_maxtrackspervtx;

      Float_t m_muon1pt;
      Float_t m_muon1eta;
      Float_t m_muon2pt;
      Float_t m_muon2eta;
      Float_t m_muon3pt;
      Float_t m_muon3eta;
      Float_t m_muon4pt;
      Float_t m_muon4eta;
      Float_t m_muontrigpt;
      Float_t m_muontrigeta;

      // control sample "lowdimuon" (single mu-jet with two muons and low pT)
      TTree *m_lowdimuon;
      Int_t m_lowdimuon_containstrig;
      Int_t m_lowdimuon_containstrig2;
      Float_t m_lowdimuon_genmass;
      Float_t m_lowdimuon_mass;
      Float_t m_lowdimuon_corr_mass;
      Float_t m_lowdimuon_recomass;
      Float_t m_lowdimuon_pt;
      Float_t m_lowdimuon_eta;
      Float_t m_lowdimuon_phi;
      Float_t m_lowdimuon_dr;
      Float_t m_lowdimuon_pluspx;
      Float_t m_lowdimuon_pluspy;
      Float_t m_lowdimuon_pluspz;
      Float_t m_lowdimuon_minuspx;
      Float_t m_lowdimuon_minuspy;
      Float_t m_lowdimuon_minuspz;
      Float_t m_lowdimuon_vprob;
      Float_t m_lowdimuon_vnchi2;
      Float_t m_lowdimuon_vx;
      Float_t m_lowdimuon_vy;
      Float_t m_lowdimuon_vz;
      Float_t m_lowdimuon_isoTk;
      Float_t m_lowdimuon_isoTk_3mm;
      Float_t m_lowdimuon_isoTk_2mm;
      Float_t m_lowdimuon_isoTk_1mm;
      Int_t m_lowdimuon_plusmatches;
      Int_t m_lowdimuon_plushits;
      Float_t m_lowdimuon_plusnormchi2;
      Int_t m_lowdimuon_minusmatches;
      Int_t m_lowdimuon_minushits;
      Float_t m_lowdimuon_minusnormchi2;
      Float_t m_lowdimuon_lxy;
      Int_t m_lowdimuon_bbbarlike;

  Float_t m_lowdimuon_trigpt1;
  Float_t m_lowdimuon_trigeta1;
  Float_t m_lowdimuon_trigpt2;
  Float_t m_lowdimuon_trigeta2;

/*
  Float_t m_lowdimuon_dphi100;
        Float_t m_lowdimuon_dphi200;
        Float_t m_lowdimuon_dphi300;
        Float_t m_lowdimuon_dphi425;
        Float_t m_lowdimuon_dphi470;
        Float_t m_lowdimuon_dphi510;
        Float_t m_lowdimuon_dphi565;
        Float_t m_lowdimuon_dphi620;
        Float_t m_lowdimuon_dphi670;
        Float_t m_lowdimuon_dphi720;
        Float_t m_lowdimuon_dphi800;
        Float_t m_lowdimuon_dphi900;
*/

  Int_t m_lowdimuon_plus_thits;
  Int_t m_lowdimuon_plus_mhits;
  Int_t m_lowdimuon_plus_phits;

        Int_t m_lowdimuon_minus_thits;
        Int_t m_lowdimuon_minus_mhits;
        Int_t m_lowdimuon_minus_phits;

  Float_t m_lowdimuon_plus_dxy;
  Float_t m_lowdimuon_minus_dxy;

  Float_t m_lowdimuon_plus_pt;
  Float_t m_lowdimuon_minus_pt;
  Float_t m_lowdimuon_plus_eta;
  Float_t m_lowdimuon_minus_eta;
  Float_t m_lowdimuon_plus_phi;
  Float_t m_lowdimuon_minus_phi;

  Float_t m_lowdimuon_Deltaphi;

  Float_t m_lowdimuon_dz;

      // control sample "dimuorphan" (single, two-muon mu-jet and a single muon)
      TTree *m_dimuorphan;
      Float_t m_dimuorphan_deltaphi;
      Float_t m_dimuorphan_orphanpt;
      Float_t m_dimuorphan_orphaneta;
      Float_t m_dimuorphan_orphanphi;
      Int_t m_dimuorphan_orphanisglobal;
      Int_t m_dimuorphan_orphanmatches;
      Int_t m_dimuorphan_stationmask;
      Int_t m_dimuorphan_orphanhits;
      Float_t m_dimuorphan_orphanchi2;
      Int_t m_dimuorphan_containstrig;
      Int_t m_dimuorphan_containstrig2;
      Float_t m_dimuorphan_mass;
      Float_t m_dimuorphan_corr_mass;
      Float_t m_dimuorphan_recomass;
      Float_t m_dimuorphan_pt;
      Float_t m_dimuorphan_eta;
      Float_t m_dimuorphan_phi;
      Float_t m_dimuorphan_dphi;
      Float_t m_dimuorphan_dr;
      Float_t m_dimuorphan_vprob;
      Float_t m_dimuorphan_vnchi2;
      Float_t m_dimuorphan_lxy;
      Float_t m_dimuorphan_lxyz;
      Float_t m_dimuorphan_caloiso;
      Float_t m_dimuorphan_isoTk;
      Float_t m_dimuorphan_isoTk_3mm;
      Float_t m_dimuorphan_isoTk_2mm;
      Float_t m_dimuorphan_isoTk_1mm;
      Float_t m_dimuorphan_isoPF_1mm;
      Float_t m_dimuorphan_orphan_isoTk_3mm;
      Float_t m_dimuorphan_orphan_isoTk_2mm;
      Float_t m_dimuorphan_orphan_isoTk_1mm;
      Float_t m_dimuorphan_orphan_isoPF_1mm;
      Int_t m_dimuorphan_dimuoncontainstrig;
      Int_t m_dimuorphan_dimuonbbbarlike;

  Float_t m_dimuorphan_trigpt1;
  Float_t m_dimuorphan_trigeta1;
  Float_t m_dimuorphan_trigpt2;
  Float_t m_dimuorphan_trigeta2;

  Int_t m_dimuorphan_trackdensity;

      Int_t m_dimuorphan_plusmatches;
      Int_t m_dimuorphan_plushits;
      Float_t m_dimuorphan_plusnormchi2;
      Int_t m_dimuorphan_minusmatches;
      Int_t m_dimuorphan_minushits;
      Float_t m_dimuorphan_minusnormchi2;

  Int_t m_dimuorphan_plusstationmask;
  Int_t m_dimuorphan_minusstationmask;

  Float_t m_dimuorphan_plus_qoverpError;
        Float_t m_dimuorphan_plus_ptError;
        Float_t m_dimuorphan_plus_phiError;
        Float_t m_dimuorphan_plus_etaError;
        Int_t m_dimuorphan_plus_isGlobal;
        Int_t m_dimuorphan_plus_isStandAlone;
        Int_t m_dimuorphan_plus_GlobalHits;
        Float_t m_dimuorphan_plus_GlobalChi2;
        Float_t m_dimuorphan_plus_StandAloneHits;
        Float_t m_dimuorphan_plus_StandAloneChi2;

        Float_t m_dimuorphan_minus_qoverpError;
        Float_t m_dimuorphan_minus_ptError;
        Float_t m_dimuorphan_minus_phiError;
        Float_t m_dimuorphan_minus_etaError;
        Int_t m_dimuorphan_minus_isGlobal;
        Int_t m_dimuorphan_minus_isStandAlone;
        Int_t m_dimuorphan_minus_GlobalHits;
        Float_t m_dimuorphan_minus_GlobalChi2;
  Float_t m_dimuorphan_minus_StandAloneHits;
        Float_t m_dimuorphan_minus_StandAloneChi2;

/*
        Float_t m_dimuorphan_dphi100;
        Float_t m_dimuorphan_dphi200;
        Float_t m_dimuorphan_dphi300;
        Float_t m_dimuorphan_dphi425;
        Float_t m_dimuorphan_dphi470;
        Float_t m_dimuorphan_dphi510;
        Float_t m_dimuorphan_dphi565;
        Float_t m_dimuorphan_dphi620;
        Float_t m_dimuorphan_dphi670;
        Float_t m_dimuorphan_dphi720;
        Float_t m_dimuorphan_dphi800;
        Float_t m_dimuorphan_dphi900;
*/

        Int_t m_dimuorphan_plus_thits;
        Int_t m_dimuorphan_plus_mhits;
        Int_t m_dimuorphan_plus_phits;

        Int_t m_dimuorphan_minus_thits;
        Int_t m_dimuorphan_minus_mhits;
        Int_t m_dimuorphan_minus_phits;

        Float_t m_dimuorphan_plus_dxy;
        Float_t m_dimuorphan_minus_dxy;

  Float_t m_dimuorphan_plus_pt;
  Float_t m_dimuorphan_minus_pt;
  Float_t m_dimuorphan_plus_eta;
  Float_t m_dimuorphan_minus_eta;
  Float_t m_dimuorphan_plus_phi;
  Float_t m_dimuorphan_minus_phi;

  Float_t m_dimuorphan_Deltaphi;
  Float_t m_dimuorphan_Deltaphi_orphan;

  Float_t m_dimuorphan_dz1;
  Float_t m_dimuorphan_dz2;
  Float_t m_dimuorphan_deltaz;

  Int_t m_dimuorphan_muonssize;

  Float_t m_dimuorphan_dr1;
  Float_t m_dimuorphan_dr2;

      // signal region "dimudimu" (two mu-jets with two muons each)
      TTree *m_dimudimu;
      Int_t m_dimudimu_orphans;
      Float_t m_dimudimu_wholemass;
      Float_t m_dimudimu_wholept;
      Float_t m_dimudimu_deltaphi;
      Int_t m_dimudimu_containstrig;
      Int_t m_dimudimu_containstrig2;
      Float_t m_dimudimu_massC;
      Float_t m_dimudimu_ptC;
      Float_t m_dimudimu_etaC;
      Float_t m_dimudimu_phiC;
      Float_t m_dimudimu_drC;
      Float_t m_dimudimu_vprobC;
      Float_t m_dimudimu_lxyC;
      Float_t m_dimudimu_lxyzC;
      Float_t m_dimudimu_C_isoTk;
      Float_t m_dimudimu_C_isoTk_3mm;
      Float_t m_dimudimu_C_isoTk_2mm;
      Float_t m_dimudimu_C_isoTk_1mm;
      Float_t m_dimudimu_C_isoPF_1mm;
      Float_t m_dimudimu_massF;
      Float_t m_dimudimu_ptF;
      Float_t m_dimudimu_etaF;
      Float_t m_dimudimu_phiF;
      Float_t m_dimudimu_drF;
      Float_t m_dimudimu_vprobF;
      Float_t m_dimudimu_lxyF;
      Float_t m_dimudimu_lxyzF;
      Float_t m_dimudimu_F_isoTk;
      Float_t m_dimudimu_F_isoTk_3mm;
      Float_t m_dimudimu_F_isoTk_2mm;
      Float_t m_dimudimu_F_isoTk_1mm;
      Float_t m_dimudimu_F_isoPF_1mm;

  Float_t m_dimudimu_dz1;
  Float_t m_dimudimu_dz2;
  Float_t m_dimudimu_deltaz;

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
FitNtuple::FitNtuple(const edm::ParameterSet& iConfig)
   : m_muons(iConfig.getParameter<edm::InputTag>("muons")),
     m_muonsTriggerMatch(iConfig.getParameter<edm::InputTag>("muonsTriggerMatch")),
     m_muJets(iConfig.getParameter<edm::InputTag>("muJets")),
     m_muJetOrphans(iConfig.getParameter<edm::InputTag>("muJetOrphans")),
     m_trigpt(iConfig.getParameter<double>("trigpt")),
     m_dataset(iConfig.getParameter<std::string>("dataset"))
{
   //now do what ever initialization is needed
   edm::Service<TFileService> tFile;

   m_lowdimuon = tFile->make<TTree>("lowdimuon", "lowdimuon");
   m_lowdimuon->Branch("run", &m_run, "run/I");
   m_lowdimuon->Branch("lumi", &m_lumi, "lumi/I");
   m_lowdimuon->Branch("event", &m_event, "event/I");
   m_lowdimuon->Branch("trigger", &m_trigger, "trigger/I");
   m_lowdimuon->Branch("trigger15", &m_trigger15, "trigger15/I");
   m_lowdimuon->Branch("trigger20", &m_trigger20, "trigger20/I");
   m_lowdimuon->Branch("trigger24", &m_trigger24, "trigger24/I");
   m_lowdimuon->Branch("trigger30", &m_trigger30, "trigger30/I");
   m_lowdimuon->Branch("trigger40", &m_trigger40, "trigger40/I");
   m_lowdimuon->Branch("trigger40eta", &m_trigger40eta, "trigger40eta/I");
   m_lowdimuon->Branch("muon1pt", &m_muon1pt, "muon1pt/F");
   m_lowdimuon->Branch("muon1eta", &m_muon1eta, "muon1eta/F");
   m_lowdimuon->Branch("muon2pt", &m_muon2pt, "muon2pt/F");
   m_lowdimuon->Branch("muon2eta", &m_muon2eta, "muon2eta/F");
   m_lowdimuon->Branch("muontrigpt", &m_muontrigpt, "muontrigpt/F");
   m_lowdimuon->Branch("muontrigeta", &m_muontrigeta, "muontrigeta/F");
   m_lowdimuon->Branch("containstrig", &m_lowdimuon_containstrig, "containstrig/I");
   m_lowdimuon->Branch("containstrig2", &m_lowdimuon_containstrig2, "containstrig2/I");
   m_lowdimuon->Branch("genmass", &m_lowdimuon_genmass, "genmass/F");
   m_lowdimuon->Branch("mass", &m_lowdimuon_mass, "mass/F");
   m_lowdimuon->Branch("corr_mass", &m_lowdimuon_corr_mass, "corr_mass/F");
   m_lowdimuon->Branch("recomass", &m_lowdimuon_recomass, "recomass/F");
   m_lowdimuon->Branch("pt", &m_lowdimuon_pt, "pt/F");
   m_lowdimuon->Branch("eta", &m_lowdimuon_eta, "eta/F");
   m_lowdimuon->Branch("phi", &m_lowdimuon_phi, "phi/F");
   m_lowdimuon->Branch("dr", &m_lowdimuon_dr, "dr/F");
   m_lowdimuon->Branch("pluspx", &m_lowdimuon_pluspx, "pluspx/F");
   m_lowdimuon->Branch("pluspy", &m_lowdimuon_pluspy, "pluspy/F");
   m_lowdimuon->Branch("pluspz", &m_lowdimuon_pluspz, "pluspz/F");
   m_lowdimuon->Branch("minuspx", &m_lowdimuon_minuspx, "minuspx/F");
   m_lowdimuon->Branch("minuspy", &m_lowdimuon_minuspy, "minuspy/F");
   m_lowdimuon->Branch("minuspz", &m_lowdimuon_minuspz, "minuspz/F");
   m_lowdimuon->Branch("vprob", &m_lowdimuon_vprob, "vprob/F");
   m_lowdimuon->Branch("vnchi2", &m_lowdimuon_vnchi2, "vnchi2/F");
   m_lowdimuon->Branch("vx", &m_lowdimuon_vx, "vx/F");
   m_lowdimuon->Branch("vy", &m_lowdimuon_vy, "vy/F");
   m_lowdimuon->Branch("vz", &m_lowdimuon_vz, "vz/F");
   m_lowdimuon->Branch("isoTk", &m_lowdimuon_isoTk, "isoTk/F");
   m_lowdimuon->Branch("isoTk_3mm", &m_lowdimuon_isoTk_3mm, "isoTk_3mm/F");
   m_lowdimuon->Branch("isoTk_2mm", &m_lowdimuon_isoTk_2mm, "isoTk_2mm/F");
   m_lowdimuon->Branch("isoTk_1mm", &m_lowdimuon_isoTk_1mm, "isoTk_1mm/F");
   m_lowdimuon->Branch("plusmatches", &m_lowdimuon_plusmatches, "plusmatches/I");
   m_lowdimuon->Branch("plushits", &m_lowdimuon_plushits, "plushits/I");
   m_lowdimuon->Branch("plusnormchi2", &m_lowdimuon_plusnormchi2, "plusnormchi2/F");
   m_lowdimuon->Branch("minusmatches", &m_lowdimuon_minusmatches, "minusmatches/I");
   m_lowdimuon->Branch("minushits", &m_lowdimuon_minushits, "minushits/I");
   m_lowdimuon->Branch("minusnormchi2", &m_lowdimuon_minusnormchi2, "minusnormchi2/F");
   m_lowdimuon->Branch("lxy", &m_lowdimuon_lxy, "lxy/F");
   m_lowdimuon->Branch("bbbarlike", &m_lowdimuon_bbbarlike, "bbbarlike/I");

   m_lowdimuon->Branch("trigpt1", &m_lowdimuon_trigpt1, "trigpt1/F");
   m_lowdimuon->Branch("trigeta1", &m_lowdimuon_trigeta1, "trigeta1/F");
   m_lowdimuon->Branch("trigpt2", &m_lowdimuon_trigpt2, "trigpt2/F");
   m_lowdimuon->Branch("trigeta2", &m_lowdimuon_trigeta2, "trigeta2/F");


/*
  m_lowdimuon->Branch("dphi100", &m_lowdimuon_dphi100, "dphi100/F");
  m_lowdimuon->Branch("dphi200", &m_lowdimuon_dphi200, "dphi200/F");
  m_lowdimuon->Branch("dphi300", &m_lowdimuon_dphi300, "dphi300/F");
  m_lowdimuon->Branch("dphi425", &m_lowdimuon_dphi425, "dphi425/F");
  m_lowdimuon->Branch("dphi470", &m_lowdimuon_dphi470, "dphi470/F");
  m_lowdimuon->Branch("dphi510", &m_lowdimuon_dphi510, "dphi510/F");
  m_lowdimuon->Branch("dphi565", &m_lowdimuon_dphi565, "dphi565/F");
  m_lowdimuon->Branch("dphi620", &m_lowdimuon_dphi620, "dphi620/F");
  m_lowdimuon->Branch("dphi670", &m_lowdimuon_dphi670, "dphi670/F");
  m_lowdimuon->Branch("dphi720", &m_lowdimuon_dphi720, "dphi720/F");
  m_lowdimuon->Branch("dphi800", &m_lowdimuon_dphi800, "dphi800/F");
  m_lowdimuon->Branch("dphi900", &m_lowdimuon_dphi900, "dphi900/F");
*/

        m_lowdimuon->Branch("plus_thits", &m_lowdimuon_plus_thits, "plus_thits/I");
        m_lowdimuon->Branch("plus_mhits", &m_lowdimuon_plus_mhits, "plus_mhits/I");
        m_lowdimuon->Branch("plus_phits", &m_lowdimuon_plus_phits, "plus_phits/I");

  m_lowdimuon->Branch("minus_thits", &m_lowdimuon_minus_thits, "minus_thits/I");
  m_lowdimuon->Branch("minus_mhits", &m_lowdimuon_minus_mhits, "minus_mhits/I");
  m_lowdimuon->Branch("minus_phits", &m_lowdimuon_minus_phits, "minus_phits/I");

        m_lowdimuon->Branch("plus_dxy", &m_lowdimuon_plus_dxy, "plus_dxy/F");
        m_lowdimuon->Branch("minus_dxy", &m_lowdimuon_minus_dxy, "minus_dxy/F");

        m_lowdimuon->Branch("plus_pt", &m_lowdimuon_plus_pt, "plus_pt/F");
        m_lowdimuon->Branch("minus_pt", &m_lowdimuon_minus_pt, "minus_pt/F");
        m_lowdimuon->Branch("plus_eta", &m_lowdimuon_plus_eta, "plus_eta/F");
        m_lowdimuon->Branch("minus_eta", &m_lowdimuon_minus_eta, "minus_eta/F");
        m_lowdimuon->Branch("plus_phi", &m_lowdimuon_plus_phi, "plus_phi/F");
        m_lowdimuon->Branch("minus_phi", &m_lowdimuon_minus_phi, "minus_phi/F");

        m_lowdimuon->Branch("Deltaphi", &m_lowdimuon_Deltaphi, "Deltaphi/F");

  m_lowdimuon->Branch("dz", &m_lowdimuon_dz, "dz/F");

  m_lowdimuon->Branch("pvsize", &m_primaryverticessize, "pvsize/I");
  m_lowdimuon->Branch("trackssize", &m_generaltrackssize, "trackssize/I");
  m_lowdimuon->Branch("maxtrackspervtx", &m_maxtrackspervtx, "maxtrackspervtx/I");

   m_dimuorphan = tFile->make<TTree>("dimuorphan", "dimuorphan");
   m_dimuorphan->Branch("run", &m_run, "run/I");
   m_dimuorphan->Branch("lumi", &m_lumi, "lumi/I");
   m_dimuorphan->Branch("event", &m_event, "event/I");
   m_dimuorphan->Branch("trigger", &m_trigger, "trigger/I");
   m_dimuorphan->Branch("trigger15", &m_trigger15, "trigger15/I");
   m_dimuorphan->Branch("trigger20", &m_trigger20, "trigger20/I");
   m_dimuorphan->Branch("trigger24", &m_trigger24, "trigger24/I");
   m_dimuorphan->Branch("trigger30", &m_trigger30, "trigger30/I");
   m_dimuorphan->Branch("trigger40", &m_trigger40, "trigger40/I");
   m_dimuorphan->Branch("trigger40eta", &m_trigger40eta, "trigger40eta/I");
   m_dimuorphan->Branch("muon1pt", &m_muon1pt, "muon1pt/F");
   m_dimuorphan->Branch("muon1eta", &m_muon1eta, "muon1eta/F");
   m_dimuorphan->Branch("muon2pt", &m_muon2pt, "muon2pt/F");
   m_dimuorphan->Branch("muon2eta", &m_muon2eta, "muon2eta/F");
   m_dimuorphan->Branch("muon3pt", &m_muon3pt, "muon3pt/F");
   m_dimuorphan->Branch("muon3eta", &m_muon3eta, "muon3eta/F");
   m_dimuorphan->Branch("muon4pt", &m_muon4pt, "muon4pt/F");
   m_dimuorphan->Branch("muon4eta", &m_muon4eta, "muon4eta/F");
   m_dimuorphan->Branch("muontrigpt", &m_muontrigpt, "muontrigpt/F");
   m_dimuorphan->Branch("muontrigeta", &m_muontrigeta, "muontrigeta/F");
   m_dimuorphan->Branch("deltaphi", &m_dimuorphan_deltaphi, "deltaphi/F");
   m_dimuorphan->Branch("orphanpt", &m_dimuorphan_orphanpt, "orphanpt/F");
   m_dimuorphan->Branch("orphaneta", &m_dimuorphan_orphaneta, "orphaneta/F");
   m_dimuorphan->Branch("orphanphi", &m_dimuorphan_orphanphi, "orphanphi/F");
   m_dimuorphan->Branch("orphanisglobal", &m_dimuorphan_orphanisglobal, "orphanisglobal/I");
   m_dimuorphan->Branch("orphanmatches", &m_dimuorphan_orphanmatches, "orphan/I");
   m_dimuorphan->Branch("orphanstationmask", &m_dimuorphan_stationmask, "stationmask/I");
   m_dimuorphan->Branch("orphanhits", &m_dimuorphan_orphanhits, "orphanhits/I");
   m_dimuorphan->Branch("orphanchi2", &m_dimuorphan_orphanchi2, "orphanchi2/F");
   m_dimuorphan->Branch("containstrig", &m_dimuorphan_containstrig, "containstrig/I");
   m_dimuorphan->Branch("containstrig2", &m_dimuorphan_containstrig2, "containstrig2/I");
   m_dimuorphan->Branch("mass", &m_dimuorphan_mass, "mass/F");
   m_dimuorphan->Branch("corr_mass", &m_dimuorphan_corr_mass, "corr_mass/F");
   m_dimuorphan->Branch("recomass", &m_dimuorphan_recomass, "recomass/F");
   m_dimuorphan->Branch("pt", &m_dimuorphan_pt, "pt/F");
   m_dimuorphan->Branch("eta", &m_dimuorphan_eta, "eta/F");
   m_dimuorphan->Branch("phi", &m_dimuorphan_phi, "phi/F");
   m_dimuorphan->Branch("dphi", &m_dimuorphan_dphi, "dphi/F");
   m_dimuorphan->Branch("dr", &m_dimuorphan_dr, "dr/F");
   m_dimuorphan->Branch("vprob", &m_dimuorphan_vprob, "vprob/F");
   m_dimuorphan->Branch("vnchi2", &m_dimuorphan_vnchi2, "vnchi2/F");
   m_dimuorphan->Branch("lxy", &m_dimuorphan_lxy, "lxy/F");
   m_dimuorphan->Branch("lxyz", &m_dimuorphan_lxyz, "lxyz/F");
   m_dimuorphan->Branch("caloiso", &m_dimuorphan_caloiso, "caloiso/F");
   m_dimuorphan->Branch("iso", &m_dimuorphan_isoTk, "isoTk/F");
   m_dimuorphan->Branch("isoTk_3mm", &m_dimuorphan_isoTk_3mm, "isoTk_3mm/F");
   m_dimuorphan->Branch("isoTk_2mm", &m_dimuorphan_isoTk_2mm, "isoTk_2mm/F");
   m_dimuorphan->Branch("isoTk_1mm", &m_dimuorphan_isoTk_1mm, "isoTk_1mm/F");
   m_dimuorphan->Branch("isoPF_1mm", &m_dimuorphan_isoPF_1mm, "isoPF_1mm/F");
   m_dimuorphan->Branch("orphan_isoTk_3mm", &m_dimuorphan_orphan_isoTk_3mm, "orphan_isoTk_3mm/F");
   m_dimuorphan->Branch("orphan_isoTk_2mm", &m_dimuorphan_orphan_isoTk_2mm, "orphan_isoTk_2mm/F");
   m_dimuorphan->Branch("orphan_isoTk_1mm", &m_dimuorphan_orphan_isoTk_1mm, "orphan_isoTk_1mm/F");
   m_dimuorphan->Branch("orphan_isoPF_1mm", &m_dimuorphan_orphan_isoPF_1mm, "orphan_isoPF_1mm/F");
   m_dimuorphan->Branch("dimuoncontainstrig", &m_dimuorphan_dimuoncontainstrig, "dimuoncontainstrig/I");
   m_dimuorphan->Branch("dimuonbbbarlike", &m_dimuorphan_dimuonbbbarlike, "eta/I");

   m_dimuorphan->Branch("trigpt1", &m_dimuorphan_trigpt1, "trigpt1/F");
   m_dimuorphan->Branch("trigeta1", &m_dimuorphan_trigeta1, "trigeta1/F");
   m_dimuorphan->Branch("trigpt2", &m_dimuorphan_trigpt2, "trigpt2/F");
   m_dimuorphan->Branch("trigeta2", &m_dimuorphan_trigeta2, "trigeta2/F");

   m_dimuorphan->Branch("plusmatches", &m_dimuorphan_plusmatches, "plusmatches/I");
   m_dimuorphan->Branch("plushits", &m_dimuorphan_plushits, "plushits/I");
   m_dimuorphan->Branch("plusnormchi2", &m_dimuorphan_plusnormchi2, "plusnormchi2/F");
   m_dimuorphan->Branch("minusmatches", &m_dimuorphan_minusmatches, "minusmatches/I");
   m_dimuorphan->Branch("minushits", &m_dimuorphan_minushits, "minushits/I");
   m_dimuorphan->Branch("minusnormchi2", &m_dimuorphan_minusnormchi2, "minusnormchi2/F");

   m_dimuorphan->Branch("plusstationmask", &m_dimuorphan_plusstationmask, "plusstationmask/I");
   m_dimuorphan->Branch("minusstationmask", &m_dimuorphan_minusstationmask, "minusstationmask/I");

   m_dimuorphan->Branch("plus_qoverpError", &m_dimuorphan_plus_qoverpError, "plus_qoverpError/F");
   m_dimuorphan->Branch("plus_ptError", &m_dimuorphan_plus_ptError, "plus_ptError/F");
   m_dimuorphan->Branch("plus_phiError", &m_dimuorphan_plus_phiError, "plus_phiError/F");
   m_dimuorphan->Branch("plus_etaError", &m_dimuorphan_plus_etaError, "plus_etaError/F");
   m_dimuorphan->Branch("plus_isGlobal", &m_dimuorphan_plus_isGlobal, "plus_isGlobal/I");
   m_dimuorphan->Branch("plus_isStandAlone", &m_dimuorphan_plus_isStandAlone, "plus_isStandAlone/I");
   m_dimuorphan->Branch("plus_GlobalHits", &m_dimuorphan_plus_GlobalHits, "plus_GlobalHits/I");
   m_dimuorphan->Branch("plus_GlobalChi2", &m_dimuorphan_plus_GlobalChi2, "plus_GlobalChi2/F");
   m_dimuorphan->Branch("plus_StandAloneHits", &m_dimuorphan_plus_StandAloneHits, "plus_StandAloneHits/I");
   m_dimuorphan->Branch("plus_StandAloneChi2", &m_dimuorphan_plus_StandAloneChi2, "plus_StandAloneChi2/F");

   m_dimuorphan->Branch("minus_qoverpError", &m_dimuorphan_minus_qoverpError, "minus_qoverpError/F");
   m_dimuorphan->Branch("minus_ptError", &m_dimuorphan_minus_ptError, "minus_ptError/F");
   m_dimuorphan->Branch("minus_phiError", &m_dimuorphan_minus_phiError, "minus_phiError/F");
   m_dimuorphan->Branch("minus_etaError", &m_dimuorphan_minus_etaError, "minus_etaError/F");
   m_dimuorphan->Branch("minus_isGlobal", &m_dimuorphan_minus_isGlobal, "minus_isGlobal/I");
   m_dimuorphan->Branch("minus_isStandAlone", &m_dimuorphan_minus_isStandAlone, "minus_isStandAlone/I");
   m_dimuorphan->Branch("minus_GlobalHits", &m_dimuorphan_minus_GlobalHits, "minus_GlobalHits/I");
   m_dimuorphan->Branch("minus_GlobalChi2", &m_dimuorphan_minus_GlobalChi2, "minus_GlobalChi2/F");
   m_dimuorphan->Branch("minus_StandAloneHits", &m_dimuorphan_minus_StandAloneHits, "minus_StandAloneHits/I");
   m_dimuorphan->Branch("minus_StandAloneChi2", &m_dimuorphan_minus_StandAloneChi2, "minus_StandAloneChi2/F");

/*
        m_dimuorphan->Branch("dphi100", &m_dimuorphan_dphi100, "dphi100/F");
        m_dimuorphan->Branch("dphi200", &m_dimuorphan_dphi200, "dphi200/F");
        m_dimuorphan->Branch("dphi300", &m_dimuorphan_dphi300, "dphi300/F");
        m_dimuorphan->Branch("dphi425", &m_dimuorphan_dphi425, "dphi425/F");
        m_dimuorphan->Branch("dphi470", &m_dimuorphan_dphi470, "dphi470/F");
        m_dimuorphan->Branch("dphi510", &m_dimuorphan_dphi510, "dphi510/F");
        m_dimuorphan->Branch("dphi565", &m_dimuorphan_dphi565, "dphi565/F");
        m_dimuorphan->Branch("dphi620", &m_dimuorphan_dphi620, "dphi620/F");
        m_dimuorphan->Branch("dphi670", &m_dimuorphan_dphi670, "dphi670/F");
        m_dimuorphan->Branch("dphi720", &m_dimuorphan_dphi720, "dphi720/F");
        m_dimuorphan->Branch("dphi800", &m_dimuorphan_dphi800, "dphi800/F");
        m_dimuorphan->Branch("dphi900", &m_dimuorphan_dphi900, "dphi900/F");
*/

        m_dimuorphan->Branch("plus_thits", &m_dimuorphan_plus_thits, "plus_thits/I");
        m_dimuorphan->Branch("plus_mhits", &m_dimuorphan_plus_mhits, "plus_mhits/I");
        m_dimuorphan->Branch("plus_phits", &m_dimuorphan_plus_phits, "plus_phits/I");

        m_dimuorphan->Branch("minus_thits", &m_dimuorphan_minus_thits, "minus_thits/I");
        m_dimuorphan->Branch("minus_mhits", &m_dimuorphan_minus_mhits, "minus_mhits/I");
        m_dimuorphan->Branch("minus_phits", &m_dimuorphan_minus_phits, "minus_phits/I");

        m_dimuorphan->Branch("plus_dxy", &m_dimuorphan_plus_dxy, "plus_dxy/F");
        m_dimuorphan->Branch("minus_dxy", &m_dimuorphan_minus_dxy, "minus_dxy/F");

        m_dimuorphan->Branch("plus_pt", &m_dimuorphan_plus_pt, "plus_pt/F");
        m_dimuorphan->Branch("minus_pt", &m_dimuorphan_minus_pt, "minus_pt/F");
        m_dimuorphan->Branch("plus_eta", &m_dimuorphan_plus_eta, "plus_eta/F");
        m_dimuorphan->Branch("minus_eta", &m_dimuorphan_minus_eta, "minus_eta/F");
        m_dimuorphan->Branch("plus_phi", &m_dimuorphan_plus_phi, "plus_phi/F");
        m_dimuorphan->Branch("minus_phi", &m_dimuorphan_minus_phi, "minus_phi/F");

  m_dimuorphan->Branch("Deltaphi", &m_dimuorphan_Deltaphi, "Deltaphi/F");
  m_dimuorphan->Branch("Deltaphi_orphan", &m_dimuorphan_Deltaphi_orphan, "Deltaphi_orphan/F");

  m_dimuorphan->Branch("dz1", &m_dimuorphan_dz1, "dz1/F");
        m_dimuorphan->Branch("dz2", &m_dimuorphan_dz2, "dz2/F");
        m_dimuorphan->Branch("deltaz", &m_dimuorphan_deltaz, "deltaz/F");

        m_dimuorphan->Branch("muonssize", &m_dimuorphan_muonssize, "muonssize/I");

  m_dimuorphan->Branch("pvsize", &m_primaryverticessize, "pvsize/I");
  m_dimuorphan->Branch("trackssize", &m_generaltrackssize, "trackssize/I");
        m_dimuorphan->Branch("maxtrackspervtx", &m_maxtrackspervtx, "maxtrackspervtx/I");

  m_dimuorphan->Branch("dr1", &m_dimuorphan_dr1, "dr1/F");
        m_dimuorphan->Branch("dr2", &m_dimuorphan_dr2, "dr2/F");

  m_dimuorphan->Branch("trackdensity", &m_dimuorphan_trackdensity, "trackdensity/I");

   m_dimudimu = tFile->make<TTree>("dimudimu", "dimudimu");
   m_dimudimu->Branch("run", &m_run, "run/I");
   m_dimudimu->Branch("lumi", &m_lumi, "lumi/I");
   m_dimudimu->Branch("event", &m_event, "event/I");
   m_dimudimu->Branch("trigger", &m_trigger, "trigger/I");
   m_dimudimu->Branch("muon1pt", &m_muon1pt, "muon1pt/F");
   m_dimudimu->Branch("muon1eta", &m_muon1eta, "muon1eta/F");
   m_dimudimu->Branch("muon2pt", &m_muon2pt, "muon2pt/F");
   m_dimudimu->Branch("muon2eta", &m_muon2eta, "muon2eta/F");
   m_dimudimu->Branch("muon3pt", &m_muon3pt, "muon3pt/F");
   m_dimudimu->Branch("muon3eta", &m_muon3eta, "muon3eta/F");
   m_dimudimu->Branch("muon4pt", &m_muon4pt, "muon4pt/F");
   m_dimudimu->Branch("muon4eta", &m_muon4eta, "muon4eta/F");
   m_dimudimu->Branch("muontrigpt", &m_muontrigpt, "muontrigpt/F");
   m_dimudimu->Branch("muontrigeta", &m_muontrigeta, "muontrigeta/F");
   m_dimudimu->Branch("orphans", &m_dimudimu_orphans, "orphans/I");
   m_dimudimu->Branch("wholemass", &m_dimudimu_wholemass, "wholemass/F");
   m_dimudimu->Branch("wholept", &m_dimudimu_wholept, "wholept/F");
   m_dimudimu->Branch("deltaphi", &m_dimudimu_deltaphi, "deltaphi/F");
   m_dimudimu->Branch("containstrig", &m_dimudimu_containstrig, "containstrig/I");
   m_dimudimu->Branch("containstrig2", &m_dimudimu_containstrig2, "containstrig2/I");
   m_dimudimu->Branch("massC", &m_dimudimu_massC, "massC/F");
   m_dimudimu->Branch("ptC", &m_dimudimu_ptC, "ptC/F");
   m_dimudimu->Branch("etaC", &m_dimudimu_etaC, "etaC/F");
   m_dimudimu->Branch("phiC", &m_dimudimu_phiC, "phiC/F");
   m_dimudimu->Branch("drC", &m_dimudimu_drC, "drC/F");
   m_dimudimu->Branch("vprobC", &m_dimudimu_vprobC, "vprobC/F");
   m_dimudimu->Branch("lxyC", &m_dimudimu_lxyC, "lxyC/F");
   m_dimudimu->Branch("lxyzC", &m_dimudimu_lxyzC, "lxyzC/F");
   m_dimudimu->Branch("C_isoTk", &m_dimudimu_C_isoTk, "C_isoTk/F");
   m_dimudimu->Branch("C_isoTk_3mm", &m_dimudimu_C_isoTk_3mm, "C_isoTk_3mm/F");
   m_dimudimu->Branch("C_isoTk_2mm", &m_dimudimu_C_isoTk_2mm, "C_isoTk_2mm/F");
   m_dimudimu->Branch("C_isoTk_1mm", &m_dimudimu_C_isoTk_1mm, "C_isoTk_1mm/F");
   m_dimudimu->Branch("C_isoPF_1mm", &m_dimudimu_C_isoPF_1mm, "C_isoPF_1mm/F");
   m_dimudimu->Branch("massF", &m_dimudimu_massF, "massF/F");
   m_dimudimu->Branch("ptF", &m_dimudimu_ptF, "ptF/F");
   m_dimudimu->Branch("etaF", &m_dimudimu_etaF, "etaF/F");
   m_dimudimu->Branch("phiF", &m_dimudimu_phiF, "phiF/F");
   m_dimudimu->Branch("drF", &m_dimudimu_drF, "drF/F");
   m_dimudimu->Branch("vprobF", &m_dimudimu_vprobF, "vprobF/F");
   m_dimudimu->Branch("lxyF", &m_dimudimu_lxyF, "lxyF/F");
   m_dimudimu->Branch("lxyzF", &m_dimudimu_lxyzF, "lxyzF/F");
   m_dimudimu->Branch("F_isoTk", &m_dimudimu_F_isoTk, "F_isoTk/F");
   m_dimudimu->Branch("F_isoTk_3mm", &m_dimudimu_F_isoTk_3mm, "F_isoTk_3mm/F");
   m_dimudimu->Branch("F_isoTk_2mm", &m_dimudimu_F_isoTk_2mm, "F_isoTk_2mm/F");
   m_dimudimu->Branch("F_isoTk_1mm", &m_dimudimu_F_isoTk_1mm, "F_isoTk_1mm/F");
   m_dimudimu->Branch("F_isoPF_1mm", &m_dimudimu_F_isoPF_1mm, "F_isoPF_1mm/F");

        m_dimudimu->Branch("dz1", &m_dimudimu_dz1, "dz1/F");
        m_dimudimu->Branch("dz2", &m_dimudimu_dz2, "dz2/F");
        m_dimudimu->Branch("deltaz", &m_dimudimu_deltaz, "deltaz/F");

  m_dimudimu->Branch("pvsize", &m_primaryverticessize, "pvsize/I");
  m_dimudimu->Branch("trackssize", &m_generaltrackssize, "trackssize/I");
        m_dimudimu->Branch("maxtrackspervtx", &m_maxtrackspervtx, "maxtrackspervtx/I");
}


FitNtuple::~FitNtuple()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
}


//
// member functions
//


double scalePt(double pt, double eta, double phi, int charge) { 

        double b = -5.03313e-6;
        double c = -4.41463e-5;
        double d0 = -0.000148871;
        double e0 = 1.59501; 
        double d1 = 7.95495e-05;
        double e1 = -0.364823;
        double d2 = 0.000152032;
        double e2 = 0.410195;
   
        double d = 0;
        double e = 0;

        double signeta = 0;

        if (fabs(eta) <= 0.9) {
                d = d0; e = e0;
        }
        if (eta > 0.9) {
                d = d1; e = e1;
        }
        if (eta < -0.9) {
                d = d2; e = e2;
        }

        if (eta >= 0) signeta = 1;
        if (eta < 0) signeta = -1;

        return 1+b*pt+c*charge*pt*signeta*eta*eta+charge*d*pt*sin(phi+e);

}

// ------------ method called to for each event  ------------
void FitNtuple::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

   edm::ESHandle<Propagator> propagator;
   iSetup.get<TrackingComponentsRecord>().get("SteppingHelixPropagatorAny", propagator);

   edm::ESHandle<MagneticField> magneticField;
   iSetup.get<IdealMagneticFieldRecord>().get(magneticField);

   edm::ESHandle<GlobalTrackingGeometry> globalGeometry;
   iSetup.get<GlobalTrackingGeometryRecord>().get(globalGeometry);

   edm::ESHandle<TrackerGeometry> tkgeom;
   iSetup.get<TrackerDigiGeometryRecord>().get(tkgeom);

   edm::Handle<reco::BeamSpot> theBeamSpot;
   iEvent.getByLabel("offlineBeamSpot",theBeamSpot);

  // get the run and event number
  m_run = iEvent.id().run();
  m_lumi = iEvent.id().luminosityBlock();
  m_event = iEvent.id().event();

  // mu-jets (muons grouped by mass and vertex compatibility)
  edm::Handle<pat::MultiMuonCollection> muJets;
  iEvent.getByLabel(m_muJets, muJets);

  // orphans (muons not found in any group)
  edm::Handle<pat::MuonCollection> orphans;
  iEvent.getByLabel(m_muJetOrphans, orphans);

  edm::Handle<reco::TrackCollection> tracks;
  iEvent.getByLabel("generalTracks", tracks);
  
  edm::Handle<reco::PFCandidateCollection> pfCandidates;
  iEvent.getByLabel("particleFlow", pfCandidates);
  
  edm::Handle<pat::MuonCollection> allmuons;
  iEvent.getByLabel(m_muons, allmuons);

  // find the top four muons in the event (-1000. if not found)
  edm::Handle<pat::MuonCollection> muons;
  iEvent.getByLabel(m_muonsTriggerMatch, muons);
  m_muon1pt = -1000.; m_muon1eta = -1000.;
  m_muon2pt = -1000.; m_muon2eta = -1000.;
  m_muon3pt = -1000.; m_muon3eta = -1000.;
  m_muon4pt = -1000.; m_muon4eta = -1000.;
  m_muontrigpt = -1000.; m_muontrigeta = -1000.;
  std::vector<pat::MuonCollection::const_iterator> hightrigmuons;
  std::vector<pat::MuonCollection::const_iterator> lowtrigmuons;

  double iso_track_pt_treshold = 0.5;

/*
        Cylinder::CylinderPointer m_cylinder100 = Cylinder::build(Cylinder::PositionType(0., 0., 0.), Cylinder::RotationType(), 100.);
        Cylinder::CylinderPointer m_cylinder200 = Cylinder::build(Cylinder::PositionType(0., 0., 0.), Cylinder::RotationType(), 200.);
        Cylinder::CylinderPointer m_cylinder300 = Cylinder::build(Cylinder::PositionType(0., 0., 0.), Cylinder::RotationType(), 300.);
        Cylinder::CylinderPointer m_cylinder425 = Cylinder::build(Cylinder::PositionType(0., 0., 0.), Cylinder::RotationType(), 425.);
        Cylinder::CylinderPointer m_cylinder470 = Cylinder::build(Cylinder::PositionType(0., 0., 0.), Cylinder::RotationType(), 470.);
        Cylinder::CylinderPointer m_cylinder510 = Cylinder::build(Cylinder::PositionType(0., 0., 0.), Cylinder::RotationType(), 510.);
        Cylinder::CylinderPointer m_cylinder565 = Cylinder::build(Cylinder::PositionType(0., 0., 0.), Cylinder::RotationType(), 565.);
        Cylinder::CylinderPointer m_cylinder620 = Cylinder::build(Cylinder::PositionType(0., 0., 0.), Cylinder::RotationType(), 620.);
        Cylinder::CylinderPointer m_cylinder670 = Cylinder::build(Cylinder::PositionType(0., 0., 0.), Cylinder::RotationType(), 670.);
        Cylinder::CylinderPointer m_cylinder720 = Cylinder::build(Cylinder::PositionType(0., 0., 0.), Cylinder::RotationType(), 720.);
        Cylinder::CylinderPointer m_cylinder800 = Cylinder::build(Cylinder::PositionType(0., 0., 0.), Cylinder::RotationType(), 800.);
        Cylinder::CylinderPointer m_cylinder900 = Cylinder::build(Cylinder::PositionType(0., 0., 0.), Cylinder::RotationType(), 900.);
*/

  for (pat::MuonCollection::const_iterator muon = muons->begin();  muon != muons->end();  ++muon) {
//    std::cout << "MUON" << std::endl;
    if (    fabs(muon->eta()) < 2.4
         && muon->isTrackerMuon()
         && muon->numberOfMatches(reco::Muon::SegmentAndTrackArbitration) >= 2
         && muon->innerTrack()->numberOfValidHits() >= 8
         && muon->innerTrack()->normalizedChi2() < 4.) {
//         std::cout << "SELECTED MUON" << std::endl;
      if (muon->pt() > m_muon1pt) {
        m_muon4pt = m_muon3pt; m_muon4eta = m_muon3eta;
        m_muon3pt = m_muon2pt; m_muon3eta = m_muon2eta;
        m_muon2pt = m_muon1pt; m_muon2eta = m_muon1eta;
        m_muon1pt = muon->pt();  m_muon1eta = muon->eta();
      } else if (muon->pt() > m_muon2pt) {
        m_muon4pt = m_muon3pt; m_muon4eta = m_muon3eta;
        m_muon3pt = m_muon2pt; m_muon3eta = m_muon2eta;
        m_muon2pt = muon->pt(); m_muon2eta = muon->eta();
      } else if (muon->pt() > m_muon3pt) {
        m_muon4pt = m_muon3pt; m_muon4eta = m_muon3eta;
        m_muon3pt = muon->pt(); m_muon3eta = muon->eta();
      } else if (muon->pt() > m_muon4pt) {
        m_muon4pt = muon->pt(); m_muon4eta = muon->eta();
      }

   // special muon within a more limited |eta| range, to guarantee the trigger
   if (fabs(muon->eta()) < 2.4) {
      if (muon->pt() > m_muontrigpt) {
         m_muontrigpt = muon->pt(); m_muontrigeta = muon->eta();
      }
   }

  if (m_dataset == "SingleMu") {
    if (muon->pt() > m_trigpt  &&  fabs(muon->eta()) < 2.4) {
              const pat::TriggerObjectStandAlone *mu01  = muon->triggerObjectMatchByPath("HLT_Mu15_v2");
              const pat::TriggerObjectStandAlone *mu02  = muon->triggerObjectMatchByPath("HLT_Mu20_v1");
              const pat::TriggerObjectStandAlone *mu03  = muon->triggerObjectMatchByPath("HLT_Mu24_v1");
              const pat::TriggerObjectStandAlone *mu04  = muon->triggerObjectMatchByPath("HLT_Mu24_v2");
              const pat::TriggerObjectStandAlone *mu05  = muon->triggerObjectMatchByPath("HLT_Mu30_v1");
              const pat::TriggerObjectStandAlone *mu06  = muon->triggerObjectMatchByPath("HLT_Mu30_v2");
              const pat::TriggerObjectStandAlone *mu07  = muon->triggerObjectMatchByPath("HLT_Mu30_v3");
              const pat::TriggerObjectStandAlone *mu08  = muon->triggerObjectMatchByPath("HLT_Mu40_v1");
              const pat::TriggerObjectStandAlone *mu09  = muon->triggerObjectMatchByPath("HLT_Mu40_v2");
              const pat::TriggerObjectStandAlone *mu10  = muon->triggerObjectMatchByPath("HLT_Mu40_v3");
              const pat::TriggerObjectStandAlone *mu11  = muon->triggerObjectMatchByPath("HLT_Mu40_v5");
              const pat::TriggerObjectStandAlone *mu12  = muon->triggerObjectMatchByPath("HLT_Mu40_eta2p1_v1");
              const pat::TriggerObjectStandAlone *mu13  = muon->triggerObjectMatchByPath("HLT_Mu40_eta2p1_v4");
              const pat::TriggerObjectStandAlone *mu14  = muon->triggerObjectMatchByPath("HLT_Mu40_eta2p1_v5");

              if ((mu01 != NULL &&  mu01->collection() == std::string("hltL3MuonCandidates::HLT") &&  mu01->pt() > m_trigpt)  ||
                  (mu02 != NULL &&  mu02->collection() == std::string("hltL3MuonCandidates::HLT") &&  mu02->pt() > m_trigpt)  ||
                  (mu03 != NULL &&  mu03->collection() == std::string("hltL3MuonCandidates::HLT") &&  mu03->pt() > m_trigpt)  ||
                  (mu04 != NULL &&  mu04->collection() == std::string("hltL3MuonCandidates::HLT") &&  mu04->pt() > m_trigpt)  ||
                  (mu05 != NULL &&  mu05->collection() == std::string("hltL3MuonCandidates::HLT") &&  mu05->pt() > m_trigpt)  ||
                  (mu06 != NULL &&  mu06->collection() == std::string("hltL3MuonCandidates::HLT") &&  mu06->pt() > m_trigpt)  ||
                  (mu07 != NULL &&  mu07->collection() == std::string("hltL3MuonCandidates::HLT") &&  mu07->pt() > m_trigpt)  ||
                  (mu08 != NULL &&  mu08->collection() == std::string("hltL3MuonCandidates::HLT") &&  mu08->pt() > m_trigpt)  ||
                  (mu09 != NULL &&  mu09->collection() == std::string("hltL3MuonCandidates::HLT") &&  mu09->pt() > m_trigpt)  ||
                  (mu10 != NULL &&  mu10->collection() == std::string("hltL3MuonCandidates::HLT") &&  mu10->pt() > m_trigpt)  ||
                  (mu11 != NULL &&  mu11->collection() == std::string("hltL3MuonCandidates::HLT") &&  mu11->pt() > m_trigpt)  ||
                  (mu12 != NULL &&  mu12->collection() == std::string("hltL3MuonCandidates::HLT") &&  mu12->pt() > m_trigpt)  ||
                  (mu13 != NULL &&  mu13->collection() == std::string("hltL3MuonCandidates::HLT") &&  mu13->pt() > m_trigpt)  ||
                  (mu14 != NULL &&  mu14->collection() == std::string("hltL3MuonCandidates::HLT") &&  mu14->pt() > m_trigpt))
                   hightrigmuons.push_back(muon);
    }
  }
  if (m_dataset == "DoubleMu") {
    if (muon->pt() > m_trigpt  &&  fabs(muon->eta()) < 0.9) {
    //if (muon->pt() > m_trigpt) {
                  const pat::TriggerObjectStandAlone *mu01  = muon->triggerObjectMatchByPath("HLT_DoubleMu6_v1");
                  const pat::TriggerObjectStandAlone *mu02  = muon->triggerObjectMatchByPath("HLT_DoubleMu7_v1");
                  const pat::TriggerObjectStandAlone *mu03  = muon->triggerObjectMatchByPath("HLT_DoubleMu7_v2");
                  const pat::TriggerObjectStandAlone *mu04  = muon->triggerObjectMatchByPath("HLT_Mu13_Mu8_v22");
                  const pat::TriggerObjectStandAlone *mu05  = muon->triggerObjectMatchByPath("HLT_Mu13_Mu8_v21");
                  const pat::TriggerObjectStandAlone *mu06  = muon->triggerObjectMatchByPath("HLT_Mu13_Mu8_v19");
                  const pat::TriggerObjectStandAlone *mu07  = muon->triggerObjectMatchByPath("HLT_Mu13_Mu8_v18");
                  const pat::TriggerObjectStandAlone *mu08  = muon->triggerObjectMatchByPath("HLT_Mu13_Mu8_v17");
                  const pat::TriggerObjectStandAlone *mu09  = muon->triggerObjectMatchByPath("HLT_Mu13_Mu8_v16");
                  const pat::TriggerObjectStandAlone *mu10  = muon->triggerObjectMatchByPath("HLT_Mu17_Mu8_v22");
                  const pat::TriggerObjectStandAlone *mu11  = muon->triggerObjectMatchByPath("HLT_Mu17_Mu8_v21");
                  const pat::TriggerObjectStandAlone *mu12  = muon->triggerObjectMatchByPath("HLT_Mu17_Mu8_v19");
                  const pat::TriggerObjectStandAlone *mu13  = muon->triggerObjectMatchByPath("HLT_Mu17_Mu8_v18");
                  const pat::TriggerObjectStandAlone *mu14  = muon->triggerObjectMatchByPath("HLT_Mu17_Mu8_v17");
                  const pat::TriggerObjectStandAlone *mu15  = muon->triggerObjectMatchByPath("HLT_Mu17_Mu8_v16");

              if ((mu01 != NULL &&  mu01->collection() == std::string("hltL3MuonCandidates::HLT") &&  mu01->pt() > m_trigpt)  ||
                  (mu02 != NULL &&  mu02->collection() == std::string("hltL3MuonCandidates::HLT") &&  mu02->pt() > m_trigpt)  ||
                  (mu03 != NULL &&  mu03->collection() == std::string("hltL3MuonCandidates::HLT") &&  mu03->pt() > m_trigpt)  ||
                  (mu04 != NULL &&  mu04->collection() == std::string("hltL3MuonCandidates::HLT") &&  mu04->pt() > m_trigpt)  ||
                  (mu05 != NULL &&  mu05->collection() == std::string("hltL3MuonCandidates::HLT") &&  mu05->pt() > m_trigpt)  ||
                  (mu06 != NULL &&  mu06->collection() == std::string("hltL3MuonCandidates::HLT") &&  mu06->pt() > m_trigpt)  ||
                  (mu07 != NULL &&  mu07->collection() == std::string("hltL3MuonCandidates::HLT") &&  mu07->pt() > m_trigpt)  ||
                  (mu08 != NULL &&  mu08->collection() == std::string("hltL3MuonCandidates::HLT") &&  mu08->pt() > m_trigpt)  ||
                  (mu09 != NULL &&  mu09->collection() == std::string("hltL3MuonCandidates::HLT") &&  mu09->pt() > m_trigpt)  ||
                  (mu10 != NULL &&  mu10->collection() == std::string("hltL3MuonCandidates::HLT") &&  mu10->pt() > m_trigpt)  ||
                  (mu11 != NULL &&  mu11->collection() == std::string("hltL3MuonCandidates::HLT") &&  mu11->pt() > m_trigpt)  ||
                  (mu12 != NULL &&  mu12->collection() == std::string("hltL3MuonCandidates::HLT") &&  mu12->pt() > m_trigpt)  ||
                  (mu13 != NULL &&  mu13->collection() == std::string("hltL3MuonCandidates::HLT") &&  mu13->pt() > m_trigpt)  ||
                  (mu14 != NULL &&  mu14->collection() == std::string("hltL3MuonCandidates::HLT") &&  mu14->pt() > m_trigpt)  ||
                  (mu15 != NULL &&  mu15->collection() == std::string("hltL3MuonCandidates::HLT") &&  mu15->pt() > m_trigpt))
        hightrigmuons.push_back(muon);
    }
           //if (muon->pt() > 8.  &&  fabs(muon->eta()) < 0.9) {
           if (muon->pt() > 8.) {
                  const pat::TriggerObjectStandAlone *mu01  = muon->triggerObjectMatchByPath("HLT_Mu17_Mu8_v22");
                  const pat::TriggerObjectStandAlone *mu02  = muon->triggerObjectMatchByPath("HLT_Mu17_Mu8_v21");
                  const pat::TriggerObjectStandAlone *mu03  = muon->triggerObjectMatchByPath("HLT_Mu17_Mu8_v19");
                  const pat::TriggerObjectStandAlone *mu04  = muon->triggerObjectMatchByPath("HLT_Mu17_Mu8_v18");
                  const pat::TriggerObjectStandAlone *mu05  = muon->triggerObjectMatchByPath("HLT_Mu17_Mu8_v17");
                  const pat::TriggerObjectStandAlone *mu06  = muon->triggerObjectMatchByPath("HLT_Mu17_Mu8_v16");
//                  const pat::TriggerObjectStandAlone *mu07  = muon->triggerObjectMatchByPath("HLT_Mu17_Mu8_v11");

              if ((mu01 != NULL &&  mu01->collection() == std::string("hltL3MuonCandidates::HLT") &&  mu01->pt() > 8.)  ||
                  (mu02 != NULL &&  mu02->collection() == std::string("hltL3MuonCandidates::HLT") &&  mu02->pt() > 8.)  ||
                  (mu03 != NULL &&  mu03->collection() == std::string("hltL3MuonCandidates::HLT") &&  mu03->pt() > 8.)  ||
                  (mu04 != NULL &&  mu04->collection() == std::string("hltL3MuonCandidates::HLT") &&  mu04->pt() > 8.)  ||
                  (mu05 != NULL &&  mu05->collection() == std::string("hltL3MuonCandidates::HLT") &&  mu05->pt() > 8.)  ||
                  (mu06 != NULL &&  mu06->collection() == std::string("hltL3MuonCandidates::HLT") &&  mu06->pt() > 8.)
//                  || (mu07 != NULL &&  mu07->collection() == std::string("hltL3MuonCandidates::HLT") &&  mu07->pt() > 8.)
                  ) 
                   lowtrigmuons.push_back(muon);
    }
        }
     }
   }

//    // all tracker-tracks
//    edm::Handle<reco::TrackCollection> tracks;
//    iEvent.getByLabel("generalTracks", tracks);

//    // generator-level 4-vectors
//    edm::Handle<reco::GenParticleCollection> genParticles;
//    iEvent.getByLabel("genParticles", genParticles);

   // find the closest primary vertex (in Z) to the first muJet with a valid vertex
   edm::Handle<reco::VertexCollection> primaryVertices;
   iEvent.getByLabel("offlinePrimaryVertices", primaryVertices);
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

  //m_primaryverticessize = primaryVertices->size();
  m_primaryverticessize = 0;

  for (reco::VertexCollection::const_iterator vertex = primaryVertices->begin();  vertex != primaryVertices->end();  ++vertex) {
    if (vertex->isValid()  &&  !vertex->isFake()  &&  vertex->tracksSize() > 3  &&  fabs(vertex->z()) < 24.) {
      m_primaryverticessize++;
    }
  }

  m_generaltrackssize = tracks->size();
  m_maxtrackspervtx = 0;

  for (reco::VertexCollection::const_iterator vertex = primaryVertices->begin();  vertex != primaryVertices->end();  ++vertex) {
    if (vertex->isValid() && fabs(vertex->z()) < 24.) {
      if (int(vertex->tracksSize()) > m_maxtrackspervtx) m_maxtrackspervtx = int(vertex->tracksSize());
    }
  }

   // find out which trigger bits were fired
   edm::Handle<pat::TriggerEvent> triggerEvent;
   iEvent.getByLabel("patTriggerEvent", triggerEvent);
   m_trigger = 0;

  if (m_dataset == "DoubleMu") {
    if (triggerEvent->path("HLT_DoubleMu6_v1") && triggerEvent->path("HLT_DoubleMu6_v1")->wasAccept()) m_trigger += 1;
    if (triggerEvent->path("HLT_DoubleMu7_v1") && triggerEvent->path("HLT_DoubleMu7_v1")->wasAccept()) m_trigger += 2;
    if (triggerEvent->path("HLT_DoubleMu7_v2") && triggerEvent->path("HLT_DoubleMu7_v2")->wasAccept()) m_trigger += 2;
    if (triggerEvent->path("HLT_Mu13_Mu8_v2")  && triggerEvent->path("HLT_Mu13_Mu8_v2")->wasAccept())  m_trigger += 4;
    if (triggerEvent->path("HLT_Mu13_Mu8_v3")  && triggerEvent->path("HLT_Mu13_Mu8_v3")->wasAccept())  m_trigger += 4;
    if (triggerEvent->path("HLT_Mu13_Mu8_v4")  && triggerEvent->path("HLT_Mu13_Mu8_v4")->wasAccept())  m_trigger += 4;
    if (triggerEvent->path("HLT_Mu13_Mu8_v6")  && triggerEvent->path("HLT_Mu13_Mu8_v6")->wasAccept())  m_trigger += 4;
    if (triggerEvent->path("HLT_Mu13_Mu8_v7")  && triggerEvent->path("HLT_Mu13_Mu8_v7")->wasAccept())  m_trigger += 4;
    if (triggerEvent->path("HLT_Mu17_Mu8_v2")  && triggerEvent->path("HLT_Mu17_Mu8_v2")->wasAccept())  m_trigger += 8;
          if (triggerEvent->path("HLT_Mu17_Mu8_v22")  && triggerEvent->path("HLT_Mu17_Mu8_v22")->wasAccept())  m_trigger += 8;
          if (triggerEvent->path("HLT_Mu17_Mu8_v21")  && triggerEvent->path("HLT_Mu17_Mu8_v21")->wasAccept())  m_trigger += 8;
          if (triggerEvent->path("HLT_Mu17_Mu8_v19")  && triggerEvent->path("HLT_Mu17_Mu8_v19")->wasAccept())  m_trigger += 8;
          if (triggerEvent->path("HLT_Mu17_Mu8_v18")  && triggerEvent->path("HLT_Mu17_Mu8_v18")->wasAccept())  m_trigger += 8;
          if (triggerEvent->path("HLT_Mu17_Mu8_v17") && triggerEvent->path("HLT_Mu17_Mu8_v17")->wasAccept()) m_trigger += 8;
          if (triggerEvent->path("HLT_Mu17_Mu8_v16") && triggerEvent->path("HLT_Mu17_Mu8_v16")->wasAccept()) m_trigger += 8;
  }
  if (m_dataset == "SingleMu") {
     if (triggerEvent->path("HLT_Mu15_v2")        && triggerEvent->path("HLT_Mu15_v2")->wasAccept())        m_trigger += 1;
     if (triggerEvent->path("HLT_Mu20_v1")        && triggerEvent->path("HLT_Mu20_v1")->wasAccept())        m_trigger += 2;
     if (triggerEvent->path("HLT_Mu24_v1")        && triggerEvent->path("HLT_Mu24_v1")->wasAccept())        m_trigger += 4;
     if (triggerEvent->path("HLT_Mu24_v2")        && triggerEvent->path("HLT_Mu24_v2")->wasAccept())        m_trigger += 4;
     if (triggerEvent->path("HLT_Mu30_v1")        && triggerEvent->path("HLT_Mu30_v1")->wasAccept())        m_trigger += 8;
     if (triggerEvent->path("HLT_Mu30_v2")        && triggerEvent->path("HLT_Mu30_v2")->wasAccept())        m_trigger += 8;
     if (triggerEvent->path("HLT_Mu30_v3")        && triggerEvent->path("HLT_Mu30_v3")->wasAccept())        m_trigger += 8;
     if (triggerEvent->path("HLT_Mu40_v1")        && triggerEvent->path("HLT_Mu40_v1")->wasAccept())        m_trigger += 16;
     if (triggerEvent->path("HLT_Mu40_v2")        && triggerEvent->path("HLT_Mu40_v2")->wasAccept())        m_trigger += 16;
     if (triggerEvent->path("HLT_Mu40_v3")        && triggerEvent->path("HLT_Mu40_v3")->wasAccept())        m_trigger += 16;
     if (triggerEvent->path("HLT_Mu40_v5")        && triggerEvent->path("HLT_Mu40_v5")->wasAccept())        m_trigger += 16;
     if (triggerEvent->path("HLT_Mu40_eta2p1_v1") && triggerEvent->path("HLT_Mu40_eta2p1_v1")->wasAccept()) m_trigger += 16;
     if (triggerEvent->path("HLT_Mu40_eta2p1_v4") && triggerEvent->path("HLT_Mu40_eta2p1_v4")->wasAccept()) m_trigger += 16;
     if (triggerEvent->path("HLT_Mu40_eta2p1_v5") && triggerEvent->path("HLT_Mu40_eta2p1_v5")->wasAccept()) m_trigger += 16;
  }



   m_trigger15 = 0;
   m_trigger20 = 0;
   m_trigger24 = 0;
   m_trigger30 = 0;
   m_trigger40 = 0;
   m_trigger40eta = 0;

   if (triggerEvent->path("HLT_Mu15_v2")        && triggerEvent->path("HLT_Mu15_v2")->wasAccept())        m_trigger15 = 1;
   if (triggerEvent->path("HLT_Mu20_v1")        && triggerEvent->path("HLT_Mu20_v1")->wasAccept())        m_trigger20 = 1;
   if (triggerEvent->path("HLT_Mu24_v2")        && triggerEvent->path("HLT_Mu24_v2")->wasAccept())        m_trigger24 = 1;
   if (triggerEvent->path("HLT_Mu30_v3")        && triggerEvent->path("HLT_Mu30_v3")->wasAccept())        m_trigger30 = 1;
   if (triggerEvent->path("HLT_Mu40_v1")        && triggerEvent->path("HLT_Mu40_v1")->wasAccept())        m_trigger40 = 1;
   if (triggerEvent->path("HLT_Mu40_v2")        && triggerEvent->path("HLT_Mu40_v2")->wasAccept())        m_trigger40 = 1;
   if (triggerEvent->path("HLT_Mu40_v3")        && triggerEvent->path("HLT_Mu40_v3")->wasAccept())        m_trigger40 = 1;
   if (triggerEvent->path("HLT_Mu40_v5")        && triggerEvent->path("HLT_Mu40_v5")->wasAccept())        m_trigger40 = 1;
   if (triggerEvent->path("HLT_Mu40_eta2p1_v1") && triggerEvent->path("HLT_Mu40_eta2p1_v1")->wasAccept()) m_trigger40eta = 1;
   if (triggerEvent->path("HLT_Mu40_eta2p1_v4") && triggerEvent->path("HLT_Mu40_eta2p1_v4")->wasAccept()) m_trigger40eta = 1;
   if (triggerEvent->path("HLT_Mu40_eta2p1_v5") && triggerEvent->path("HLT_Mu40_eta2p1_v5")->wasAccept()) m_trigger40eta = 1;

   ////////////////////////////////////////////////////////// lowdimuon and highdimuon:
   
   //if (muJets->size() == 1  &&  (*muJets)[0].numberOfDaughters() == 2 && orphans->size() == 0 && m_trigger > 0) {
   if (muJets->size() == 1  &&  (*muJets)[0].numberOfDaughters() == 2 && orphans->size() == 0) {
      pat::MultiMuonCollection::const_iterator muJet = muJets->begin();

  m_lowdimuon_trigpt1 = -20;
  m_lowdimuon_trigeta1 = -20;
  m_lowdimuon_trigpt2 = -20;
  m_lowdimuon_trigeta2 = -20;

      m_lowdimuon_containstrig = 0;
      m_lowdimuon_containstrig2 = 0;

      for (std::vector<pat::MuonCollection::const_iterator>::const_iterator iter = lowtrigmuons.begin();  iter != lowtrigmuons.end();  ++iter) {
         if (muJet->muon(0)->innerTrack().isAvailable()  &&  (*iter)->innerTrack().isAvailable()  &&  
             muJet->sameTrack(&*(muJet->muon(0)->innerTrack()), &*((*iter)->innerTrack()))) {
            m_lowdimuon_containstrig2++;
         }
         if (muJet->muon(1)->innerTrack().isAvailable()  &&  (*iter)->innerTrack().isAvailable()  &&
             muJet->sameTrack(&*(muJet->muon(1)->innerTrack()), &*((*iter)->innerTrack()))) {
            m_lowdimuon_containstrig2++;
         }
      }

      for (std::vector<pat::MuonCollection::const_iterator>::const_iterator iter = hightrigmuons.begin();  iter != hightrigmuons.end();  ++iter) {
   if (muJet->muon(0)->innerTrack().isAvailable()  &&  (*iter)->innerTrack().isAvailable()  &&
       muJet->sameTrack(&*(muJet->muon(0)->innerTrack()), &*((*iter)->innerTrack()))) {
      m_lowdimuon_containstrig++;
    if (m_lowdimuon_containstrig2 == 2) {
      m_lowdimuon_trigpt1 = muJet->muon(0)->pt();
      m_lowdimuon_trigeta1 = muJet->muon(0)->eta();
      m_lowdimuon_trigpt2 = muJet->muon(1)->pt();
      m_lowdimuon_trigeta2 = muJet->muon(1)->eta();
    }
   }
   if (muJet->muon(1)->innerTrack().isAvailable()  &&  (*iter)->innerTrack().isAvailable()  &&
       muJet->sameTrack(&*(muJet->muon(1)->innerTrack()), &*((*iter)->innerTrack()))) {
      m_lowdimuon_containstrig++;
    if (m_lowdimuon_containstrig2 == 2) {
      m_lowdimuon_trigpt1 = muJet->muon(1)->pt();
      m_lowdimuon_trigeta1 = muJet->muon(1)->eta();
      m_lowdimuon_trigpt2 = muJet->muon(0)->pt();
      m_lowdimuon_trigeta2 = muJet->muon(0)->eta();
    }
   }
      }

      // generator-level mass using matched genParticles (for resolution of fit peak)
      m_lowdimuon_genmass = -1000.;
      if (muJet->muon(0)->genParticlesSize() == 1  &&  muJet->muon(1)->genParticlesSize() == 1) {
   const reco::GenParticle *mu0 = muJet->muon(0)->genParticle();
   const reco::GenParticle *mu1 = muJet->muon(1)->genParticle();

   double total_energy = mu0->energy() + mu1->energy();
   double total_px = mu0->px() + mu1->px();
   double total_py = mu0->py() + mu1->py();
   double total_pz = mu0->pz() + mu1->pz();
   m_lowdimuon_genmass = sqrt(total_energy*total_energy - total_px*total_px - total_py*total_py - total_pz*total_pz);
      }

      m_lowdimuon_mass = muJet->mass();
      m_lowdimuon_corr_mass = -1;
      m_lowdimuon_recomass = muJet->mass();
      m_lowdimuon_pt = muJet->pt();
      m_lowdimuon_eta = muJet->eta();
      m_lowdimuon_phi = muJet->phi();
      m_lowdimuon_dr = muJet->dRmax();
      if (muJet->daughter(0)->charge() > 0) {
   m_lowdimuon_pluspx = muJet->daughter(0)->px();
   m_lowdimuon_pluspy = muJet->daughter(0)->py();
   m_lowdimuon_pluspz = muJet->daughter(0)->pz();
   m_lowdimuon_minuspx = muJet->daughter(1)->px();
   m_lowdimuon_minuspy = muJet->daughter(1)->py();
   m_lowdimuon_minuspz = muJet->daughter(1)->pz();
      }
      else {
   m_lowdimuon_pluspx = muJet->daughter(1)->px();
   m_lowdimuon_pluspy = muJet->daughter(1)->py();
   m_lowdimuon_pluspz = muJet->daughter(1)->pz();
   m_lowdimuon_minuspx = muJet->daughter(0)->px();
   m_lowdimuon_minuspy = muJet->daughter(0)->py();
   m_lowdimuon_minuspz = muJet->daughter(0)->pz();
      }
      m_lowdimuon_vprob = -1000.;
      m_lowdimuon_vnchi2 = -1000.;
      m_lowdimuon_vx = -1000.;
      m_lowdimuon_vy = -1000.;
      m_lowdimuon_vz = -1000.;

  m_lowdimuon_lxy = -1000.;

      // replace all values with vertex-updated values if vertex fitting succeeded
      if (muJet->vertexValid()) {
   m_lowdimuon_mass = muJet->vertexMass();
   m_lowdimuon_corr_mass = muJet->vertexMass();
   m_lowdimuon_pt = muJet->vertexMomentum().perp();
   m_lowdimuon_eta = muJet->vertexMomentum().eta();
   m_lowdimuon_phi = muJet->vertexMomentum().phi();
   m_lowdimuon_dr = muJet->dRmax(true);
   if (muJet->daughter(0)->charge() > 0) {
      m_lowdimuon_pluspx = muJet->vertexMomentum(0).x();
      m_lowdimuon_pluspy = muJet->vertexMomentum(0).y();
      m_lowdimuon_pluspz = muJet->vertexMomentum(0).z();
      m_lowdimuon_minuspx = muJet->vertexMomentum(1).x();
      m_lowdimuon_minuspy = muJet->vertexMomentum(1).y();
      m_lowdimuon_minuspz = muJet->vertexMomentum(1).z();
   }
   else {
      m_lowdimuon_pluspx = muJet->vertexMomentum(1).x();
      m_lowdimuon_pluspy = muJet->vertexMomentum(1).y();
      m_lowdimuon_pluspz = muJet->vertexMomentum(1).z();
      m_lowdimuon_minuspx = muJet->vertexMomentum(0).x();
      m_lowdimuon_minuspy = muJet->vertexMomentum(0).y();
      m_lowdimuon_minuspz = muJet->vertexMomentum(0).z();
   }
   m_lowdimuon_vprob = muJet->vertexProb();
   m_lowdimuon_vnchi2 = muJet->vertexNormalizedChi2();

   if (closestPrimaryVertex != primaryVertices->end()) {
      m_lowdimuon_vx = muJet->vertexPoint().x() - closestPrimaryVertex->x();
      m_lowdimuon_vy = muJet->vertexPoint().y() - closestPrimaryVertex->y();
      m_lowdimuon_vz = muJet->vertexPoint().z() - closestPrimaryVertex->z();
      m_lowdimuon_lxy = muJet->lxy(GlobalPoint(closestPrimaryVertex->x(), closestPrimaryVertex->y(), closestPrimaryVertex->z()));
   }

  double scale0 = scalePt(muJet->vertexMomentum(0).perp(),muJet->vertexMomentum(0).eta(),muJet->vertexMomentum(0).phi(),muJet->muon(0)->charge());
  double scale1 = scalePt(muJet->vertexMomentum(1).perp(),muJet->vertexMomentum(1).eta(),muJet->vertexMomentum(1).phi(),muJet->muon(1)->charge());

  double e1 = pow(pow(muJet->vertexMomentum(0).perp()*scale0,2)+pow(muJet->vertexMomentum(0).z(),2)+pow(muJet->muon(0)->mass(),2),0.5);
  double e2 = pow(pow(muJet->vertexMomentum(1).perp()*scale1,2)+pow(muJet->vertexMomentum(1).z(),2)+pow(muJet->muon(1)->mass(),2),0.5);
  double e = e1 + e2;

  double px = muJet->vertexMomentum(0).x()*scale0 + muJet->vertexMomentum(1).x()*scale1;
  double py = muJet->vertexMomentum(0).y()*scale0 + muJet->vertexMomentum(1).y()*scale1;
  double pz = muJet->vertexMomentum(0).z() + muJet->vertexMomentum(1).z();

  m_lowdimuon_corr_mass = pow(e*e-px*px-py*py-pz*pz,0.5);

      } // end of replacements with quantities measured at the vertex

      m_lowdimuon_isoTk = muJet->centralTrackIsolation();
  
  m_lowdimuon_isoTk_3mm = 0;
  m_lowdimuon_isoTk_2mm = 0;
  m_lowdimuon_isoTk_1mm = 0;

        for (reco::TrackCollection::const_iterator track = tracks->begin(); track != tracks->end(); ++track) {
    bool track_is_muon = false;
                for (pat::MuonCollection::const_iterator muon = allmuons->begin();  muon != allmuons->end();  ++muon) {
                        if (muJet->sameTrack(&*track,&*(muon->innerTrack()))) { track_is_muon = true; break; }
    }
    if (!track_is_muon) {
                        double dphi = muJet->phi() - track->phi();
                        if (dphi > M_PI) dphi -= 2.*M_PI;
                        if (dphi < -M_PI) dphi += 2.*M_PI;
                        double deta = muJet->eta() - track->eta();
                        double dR = sqrt(pow(dphi, 2) + pow(deta, 2)); 
                        if (dR < 0.4 && track->pt() > iso_track_pt_treshold) {
                                double dz = fabs(track->dz(theBeamSpot->position())-muJet->dz(theBeamSpot->position()));
                                if (dz < 0.3) m_lowdimuon_isoTk_3mm += track->pt();
                                if (dz < 0.2) m_lowdimuon_isoTk_2mm += track->pt();
                                if (dz < 0.1) m_lowdimuon_isoTk_1mm += track->pt();
                        }
                }
        }

      std::vector<reco::MuonChamberMatch> plusmatches, minusmatches;
      if (muJet->daughter(0)->charge() > 0) {
   m_lowdimuon_plusmatches = muJet->muon(0)->numberOfMatches(reco::Muon::SegmentAndTrackArbitration);
   m_lowdimuon_minusmatches = muJet->muon(1)->numberOfMatches(reco::Muon::SegmentAndTrackArbitration);
   plusmatches = muJet->muon(0)->matches();
   minusmatches = muJet->muon(1)->matches();
   m_lowdimuon_plushits = muJet->muon(0)->innerTrack()->numberOfValidHits();
   m_lowdimuon_minushits = muJet->muon(1)->innerTrack()->numberOfValidHits();
   m_lowdimuon_plusnormchi2 = muJet->muon(0)->innerTrack()->normalizedChi2();
   m_lowdimuon_minusnormchi2 = muJet->muon(1)->innerTrack()->normalizedChi2();

  m_lowdimuon_plus_thits = muJet->muon(0)->innerTrack()->hitPattern().numberOfValidTrackerHits();
  m_lowdimuon_plus_mhits = 0;
  if (muJet->muon(0)->isGlobalMuon()) m_lowdimuon_plus_mhits = muJet->muon(0)->globalTrack()->hitPattern().numberOfValidMuonHits();
  m_lowdimuon_plus_phits = muJet->muon(0)->innerTrack()->hitPattern().numberOfValidPixelHits();

        m_lowdimuon_minus_thits = muJet->muon(1)->innerTrack()->hitPattern().numberOfValidTrackerHits();
  m_lowdimuon_minus_mhits = 0;
        if (muJet->muon(1)->isGlobalMuon()) m_lowdimuon_minus_mhits = muJet->muon(1)->globalTrack()->hitPattern().numberOfValidMuonHits();
        m_lowdimuon_minus_phits = muJet->muon(1)->innerTrack()->hitPattern().numberOfValidPixelHits();


  m_lowdimuon_plus_dxy = muJet->muon(0)->innerTrack()->dxy(theBeamSpot->position());
  m_lowdimuon_minus_dxy = muJet->muon(1)->innerTrack()->dxy(theBeamSpot->position());

        m_lowdimuon_plus_pt = muJet->muon(0)->pt();
        m_lowdimuon_minus_pt = muJet->muon(1)->pt();
        m_lowdimuon_plus_eta = muJet->muon(0)->eta();
        m_lowdimuon_minus_eta = muJet->muon(1)->eta();
        m_lowdimuon_plus_phi = muJet->muon(0)->phi();
        m_lowdimuon_minus_phi = muJet->muon(1)->phi();

  m_lowdimuon_Deltaphi = m_lowdimuon_plus_phi-m_lowdimuon_minus_phi;
  if (m_lowdimuon_Deltaphi > M_PI) m_lowdimuon_Deltaphi -= 2.*M_PI;
  if (m_lowdimuon_Deltaphi < -M_PI) m_lowdimuon_Deltaphi += 2.*M_PI;


/*
  for (trackingRecHit_iterator hit = muJet->muon(0)->innerTrack()->recHitsBegin(); hit != muJet->muon(0)->innerTrack()->recHitsEnd(); ++hit) {
    if ((*hit)->isValid()) {
      GlobalPoint p = tkgeom->idToDet((*hit)->geographicalId())->toGlobal((*hit)->localPosition());
      m_lowdimuon_plus_innerR = pow(p.x()*p.x()+p.y()*p.y(),0.5);
      break;
    }
  }
        for (trackingRecHit_iterator hit = muJet->muon(1)->innerTrack()->recHitsBegin(); hit != muJet->muon(1)->innerTrack()->recHitsEnd(); ++hit) {
                if ((*hit)->isValid()) {
                        GlobalPoint p = tkgeom->idToDet((*hit)->geographicalId())->toGlobal((*hit)->localPosition());
                        m_lowdimuon_minus_innerR = pow(p.x()*p.x()+p.y()*p.y(),0.5);
                        break;
                }
        }
*/

      }
      else {
   m_lowdimuon_plusmatches = muJet->muon(1)->numberOfMatches(reco::Muon::SegmentAndTrackArbitration);
   m_lowdimuon_minusmatches = muJet->muon(0)->numberOfMatches(reco::Muon::SegmentAndTrackArbitration);
   plusmatches = muJet->muon(1)->matches();
   minusmatches = muJet->muon(0)->matches();
   m_lowdimuon_plushits = muJet->muon(1)->innerTrack()->numberOfValidHits();
   m_lowdimuon_minushits = muJet->muon(0)->innerTrack()->numberOfValidHits();
   m_lowdimuon_plusnormchi2 = muJet->muon(1)->innerTrack()->normalizedChi2();
   m_lowdimuon_minusnormchi2 = muJet->muon(0)->innerTrack()->normalizedChi2();

        m_lowdimuon_plus_thits = muJet->muon(1)->innerTrack()->hitPattern().numberOfValidTrackerHits();
        m_lowdimuon_plus_mhits = 0; 
        if (muJet->muon(1)->isGlobalMuon()) m_lowdimuon_plus_mhits = muJet->muon(1)->globalTrack()->hitPattern().numberOfValidMuonHits();
        m_lowdimuon_plus_phits = muJet->muon(1)->innerTrack()->hitPattern().numberOfValidPixelHits();

        m_lowdimuon_minus_thits = muJet->muon(0)->innerTrack()->hitPattern().numberOfValidTrackerHits();
        m_lowdimuon_minus_mhits = 0;
        if (muJet->muon(0)->isGlobalMuon()) m_lowdimuon_minus_mhits = muJet->muon(0)->globalTrack()->hitPattern().numberOfValidMuonHits();
        m_lowdimuon_minus_phits = muJet->muon(0)->innerTrack()->hitPattern().numberOfValidPixelHits();

        m_lowdimuon_plus_dxy = muJet->muon(1)->innerTrack()->dxy(theBeamSpot->position());
        m_lowdimuon_minus_dxy = muJet->muon(0)->innerTrack()->dxy(theBeamSpot->position());

        m_lowdimuon_plus_pt = muJet->muon(1)->pt();
        m_lowdimuon_minus_pt = muJet->muon(0)->pt();
        m_lowdimuon_plus_eta = muJet->muon(1)->eta();
        m_lowdimuon_minus_eta = muJet->muon(0)->eta();
        m_lowdimuon_plus_phi = muJet->muon(1)->phi();
        m_lowdimuon_minus_phi = muJet->muon(0)->phi();

  m_lowdimuon_Deltaphi = m_lowdimuon_plus_phi-m_lowdimuon_minus_phi;
  if (m_lowdimuon_Deltaphi > M_PI) m_lowdimuon_Deltaphi -= 2.*M_PI;
  if (m_lowdimuon_Deltaphi < -M_PI) m_lowdimuon_Deltaphi += 2.*M_PI;
      }

/* 
        const pat::Muon *muplus = NULL;
        const pat::Muon *muminus = NULL;

        if (muJet->muon(0)->charge() > 0) {
                muplus = &*muJet->muon(0);
                muminus = &*muJet->muon(1);
        }
        if (muJet->muon(0)->charge() < 0) {
                muplus = &*muJet->muon(1);
                muminus = &*muJet->muon(0);
        }

      FreeTrajectoryState plus_initial(GlobalPoint(muplus->vx(), muplus->vy(), muplus->vz()), GlobalVector(muplus->px(), muplus->py(), muplus->pz()), 1, &*magneticField);
      FreeTrajectoryState minus_initial(GlobalPoint(muminus->vx(), muminus->vy(), muminus->vz()), GlobalVector(muminus->px(), muminus->py(), muminus->pz()), -1, &*magneticField);

        if (fabs(m_lowdimuon_eta) < 0.9) {
                TrajectoryStateOnSurface plus_final = propagator->propagate(plus_initial, *m_cylinder100);
                TrajectoryStateOnSurface minus_final = propagator->propagate(minus_initial, *m_cylinder100);
                if (plus_final.isValid()  &&  minus_final.isValid()) {
                        double dphi = plus_final.globalPosition().phi() - minus_final.globalPosition().phi();
                        while (dphi > M_PI) dphi -= 2.*M_PI;
                        while (dphi < -M_PI) dphi += 2.*M_PI;
                        m_lowdimuon_dphi100 = dphi;
                }
                plus_final = propagator->propagate(plus_initial, *m_cylinder200);
                minus_final = propagator->propagate(minus_initial, *m_cylinder200);
                if (plus_final.isValid()  &&  minus_final.isValid()) {
                        double dphi = plus_final.globalPosition().phi() - minus_final.globalPosition().phi();
                        while (dphi > M_PI) dphi -= 2.*M_PI;
                        while (dphi < -M_PI) dphi += 2.*M_PI;
                        m_lowdimuon_dphi200 = dphi;
                }
                plus_final = propagator->propagate(plus_initial, *m_cylinder300);
                minus_final = propagator->propagate(minus_initial, *m_cylinder300);
                if (plus_final.isValid()  &&  minus_final.isValid()) {
                        double dphi = plus_final.globalPosition().phi() - minus_final.globalPosition().phi();
                        while (dphi > M_PI) dphi -= 2.*M_PI;
                        while (dphi < -M_PI) dphi += 2.*M_PI;
                        m_lowdimuon_dphi300 = dphi;
                }
                plus_final = propagator->propagate(plus_initial, *m_cylinder425);
                minus_final = propagator->propagate(minus_initial, *m_cylinder425);
                if (plus_final.isValid()  &&  minus_final.isValid()) {
                        double dphi = plus_final.globalPosition().phi() - minus_final.globalPosition().phi();
                        while (dphi > M_PI) dphi -= 2.*M_PI;
                        while (dphi < -M_PI) dphi += 2.*M_PI;
                        m_lowdimuon_dphi425 = dphi;
                }
                plus_final = propagator->propagate(plus_initial, *m_cylinder470);
                minus_final = propagator->propagate(minus_initial, *m_cylinder470);
                if (plus_final.isValid()  &&  minus_final.isValid()) {
                        double dphi = plus_final.globalPosition().phi() - minus_final.globalPosition().phi();
                        while (dphi > M_PI) dphi -= 2.*M_PI;
                        while (dphi < -M_PI) dphi += 2.*M_PI;
                        m_lowdimuon_dphi470 = dphi;
                }
                plus_final = propagator->propagate(plus_initial, *m_cylinder510);
                minus_final = propagator->propagate(minus_initial, *m_cylinder510);
                if (plus_final.isValid()  &&  minus_final.isValid()) {
                        double dphi = plus_final.globalPosition().phi() - minus_final.globalPosition().phi();
                        while (dphi > M_PI) dphi -= 2.*M_PI;
                        while (dphi < -M_PI) dphi += 2.*M_PI;
                        m_lowdimuon_dphi510 = dphi;
                }
                plus_final = propagator->propagate(plus_initial, *m_cylinder565);
                minus_final = propagator->propagate(minus_initial, *m_cylinder565);
                if (plus_final.isValid()  &&  minus_final.isValid()) {
                        double dphi = plus_final.globalPosition().phi() - minus_final.globalPosition().phi();
                        while (dphi > M_PI) dphi -= 2.*M_PI;
                        while (dphi < -M_PI) dphi += 2.*M_PI;
                        m_lowdimuon_dphi565 = dphi;
                }
                plus_final = propagator->propagate(plus_initial, *m_cylinder620);
                minus_final = propagator->propagate(minus_initial, *m_cylinder620);
                if (plus_final.isValid()  &&  minus_final.isValid()) {
                        double dphi = plus_final.globalPosition().phi() - minus_final.globalPosition().phi();
                        while (dphi > M_PI) dphi -= 2.*M_PI;
                        while (dphi < -M_PI) dphi += 2.*M_PI;
                        m_lowdimuon_dphi620 = dphi;
                }
                plus_final = propagator->propagate(plus_initial, *m_cylinder670);
                minus_final = propagator->propagate(minus_initial, *m_cylinder670);
                if (plus_final.isValid()  &&  minus_final.isValid()) {
                        double dphi = plus_final.globalPosition().phi() - minus_final.globalPosition().phi();
                        while (dphi > M_PI) dphi -= 2.*M_PI;
                        while (dphi < -M_PI) dphi += 2.*M_PI;
                        m_lowdimuon_dphi670 = dphi;
                }
                plus_final = propagator->propagate(plus_initial, *m_cylinder720);
                minus_final = propagator->propagate(minus_initial, *m_cylinder720);
                if (plus_final.isValid()  &&  minus_final.isValid()) {
                        double dphi = plus_final.globalPosition().phi() - minus_final.globalPosition().phi();
                        while (dphi > M_PI) dphi -= 2.*M_PI;
                        while (dphi < -M_PI) dphi += 2.*M_PI;
                        m_lowdimuon_dphi720 = dphi;
                }
                plus_final = propagator->propagate(plus_initial, *m_cylinder800);
                minus_final = propagator->propagate(minus_initial, *m_cylinder800);
                if (plus_final.isValid()  &&  minus_final.isValid()) {
                        double dphi = plus_final.globalPosition().phi() - minus_final.globalPosition().phi();
                        while (dphi > M_PI) dphi -= 2.*M_PI;
                        while (dphi < -M_PI) dphi += 2.*M_PI;
                        m_lowdimuon_dphi800 = dphi;
                }
                plus_final = propagator->propagate(plus_initial, *m_cylinder900);
                minus_final = propagator->propagate(minus_initial, *m_cylinder900);
                if (plus_final.isValid()  &&  minus_final.isValid()) {
                        double dphi = plus_final.globalPosition().phi() - minus_final.globalPosition().phi();
                        while (dphi > M_PI) dphi -= 2.*M_PI;
                        while (dphi < -M_PI) dphi += 2.*M_PI;
                        m_lowdimuon_dphi900 = dphi;
                }
        }
*/

      m_lowdimuon_bbbarlike = -1;
      if (m_lowdimuon_isoTk > 4.5 || m_lowdimuon_lxy > 0.2) m_lowdimuon_bbbarlike = 1;
      if (m_lowdimuon_isoTk < 4.5 && m_lowdimuon_lxy < 0.2) m_lowdimuon_bbbarlike = 0;

  m_lowdimuon_dz = muJet->dz(theBeamSpot->position());



      if (m_lowdimuon_containstrig > 0 && m_lowdimuon_containstrig2 > 1) {
        m_lowdimuon->Fill();
      }
   }

   ////////////////////////////////////////////////////////// dimuorphan

   if (muJets->size() == 1  &&  (*muJets)[0].numberOfDaughters() == 2  &&  orphans->size() == 1 && m_trigger > 0) {
   //if (muJets->size() == 1  &&  (*muJets)[0].numberOfDaughters() == 2  &&  orphans->size() == 1) {
      pat::MultiMuonCollection::const_iterator muJet = muJets->begin();
      pat::MuonCollection::const_iterator orphan = orphans->begin();

      m_dimuorphan_deltaphi = muJet->phi() - orphan->phi();
      while (m_dimuorphan_deltaphi > M_PI) m_dimuorphan_deltaphi -= 2.*M_PI;
      while (m_dimuorphan_deltaphi < -M_PI) m_dimuorphan_deltaphi += 2.*M_PI;

  double deta = orphan->innerTrack()->eta() - muJet->muon(0)->innerTrack()->eta();
  double dphi = orphan->innerTrack()->phi() - muJet->muon(0)->innerTrack()->phi();
  if (dphi > M_PI) dphi -= 2.*M_PI;
  if (dphi < -M_PI) dphi += 2.*M_PI;
  m_dimuorphan_dr1 = pow(dphi*dphi+deta*deta,0.5);

        deta = orphan->innerTrack()->eta() - muJet->muon(1)->innerTrack()->eta();
        dphi = orphan->innerTrack()->phi() - muJet->muon(1)->innerTrack()->phi();
        if (dphi > M_PI) dphi -= 2.*M_PI;
        if (dphi < -M_PI) dphi += 2.*M_PI;
        m_dimuorphan_dr2 = pow(dphi*dphi+deta*deta,0.5);

      m_dimuorphan_orphanpt = orphan->pt();
      m_dimuorphan_orphaneta = orphan->eta();
      m_dimuorphan_orphanphi = orphan->phi();
      m_dimuorphan_orphanisglobal = (orphan->isGlobalMuon() ? 1 : 0);
      m_dimuorphan_orphanmatches = orphan->numberOfMatches(reco::Muon::SegmentAndTrackArbitration);
      m_dimuorphan_stationmask = orphan->stationMask();
      m_dimuorphan_orphanhits = (orphan->innerTrack().isAvailable() ? orphan->innerTrack()->numberOfValidHits(): -1);
      m_dimuorphan_orphanchi2 = (orphan->innerTrack().isAvailable() ? orphan->innerTrack()->normalizedChi2(): -1.);

  m_dimuorphan_trigpt1 = -20;
  m_dimuorphan_trigeta1 = -20;
  m_dimuorphan_trigpt2 = -20;
  m_dimuorphan_trigeta2 = -20;

      m_dimuorphan_containstrig = 0;
      m_dimuorphan_containstrig2 = 0;

      for (std::vector<pat::MuonCollection::const_iterator>::const_iterator iter = hightrigmuons.begin();  iter != hightrigmuons.end();  ++iter) {
   if (orphan->innerTrack().isAvailable()  &&  (*iter)->innerTrack().isAvailable()  &&
       muJet->sameTrack(&*(orphan->innerTrack()), &*((*iter)->innerTrack()))) {
      m_dimuorphan_containstrig++;
   }
      }

      for (std::vector<pat::MuonCollection::const_iterator>::const_iterator iter = hightrigmuons.begin();  iter != hightrigmuons.end();  ++iter) {
         if (muJet->muon(0)->innerTrack().isAvailable()  &&  (*iter)->innerTrack().isAvailable()  &&
             muJet->sameTrack(&*(muJet->muon(0)->innerTrack()), &*((*iter)->innerTrack()))) {
            m_dimuorphan_containstrig2++;
    if (m_dimuorphan_containstrig2 == 2) {
      m_dimuorphan_trigpt1 = muJet->muon(0)->pt();
      m_dimuorphan_trigeta1 = muJet->muon(0)->eta();
      m_dimuorphan_trigpt2 = orphan->pt();
      m_dimuorphan_trigeta2 = orphan->eta();
    }
         }
         if (muJet->muon(1)->innerTrack().isAvailable()  &&  (*iter)->innerTrack().isAvailable()  &&
             muJet->sameTrack(&*(muJet->muon(1)->innerTrack()), &*((*iter)->innerTrack()))) {
            m_dimuorphan_containstrig2++;
    if (m_dimuorphan_containstrig2 == 2) {
      m_dimuorphan_trigpt1 = muJet->muon(1)->pt();
      m_dimuorphan_trigeta1 = muJet->muon(1)->eta();
      m_dimuorphan_trigpt2 = orphan->pt();
      m_dimuorphan_trigeta2 = orphan->eta();
    }
         }
      }


   
      m_dimuorphan_mass = muJet->mass();
      m_dimuorphan_corr_mass = -1;
      m_dimuorphan_recomass = muJet->mass();
      m_dimuorphan_pt = muJet->pt();
      m_dimuorphan_eta = muJet->eta();
      m_dimuorphan_phi = muJet->phi();
      m_dimuorphan_dr = muJet->dRmax();
      m_dimuorphan_vprob = -1.;
      m_dimuorphan_vnchi2 = -1.;
      m_dimuorphan_lxy = -1000.;
      m_dimuorphan_lxyz = -1000.;
      m_dimuorphan_caloiso = muJet->centralCaloIsolation();
      m_dimuorphan_isoTk = muJet->centralTrackIsolation();

  m_dimuorphan_isoTk_3mm = 0;
  m_dimuorphan_isoTk_2mm = 0;
  m_dimuorphan_isoTk_1mm = 0;

  for (reco::TrackCollection::const_iterator track = tracks->begin(); track != tracks->end(); ++track) {
    bool track_is_muon = false;
    if (muJet->sameTrack(&*track,&*(muJet->muon(0)->innerTrack())) || muJet->sameTrack(&*track,&*(muJet->muon(1)->innerTrack()))) track_is_muon = true;
    if (!track_is_muon) {
      double dphi = muJet->phi() - track->phi();
      if (dphi > M_PI) dphi -= 2.*M_PI;
      if (dphi < -M_PI) dphi += 2.*M_PI;
      double deta = muJet->eta() - track->eta();
      double dR = sqrt(pow(dphi, 2) + pow(deta, 2)); 
      if (dR < 0.4 && track->pt() > iso_track_pt_treshold) {
        double dz = fabs(track->dz(theBeamSpot->position())-muJet->dz(theBeamSpot->position()));
        if (dz < 0.3) m_dimuorphan_isoTk_3mm += track->pt();
        if (dz < 0.2) m_dimuorphan_isoTk_2mm += track->pt();
        if (dz < 0.1) m_dimuorphan_isoTk_1mm += track->pt();
      }
    }    
  }
  
  m_dimuorphan_isoPF_1mm = 0.0;
  for (reco::PFCandidateCollection::const_iterator pfCand = pfCandidates->begin(); pfCand != pfCandidates->end(); ++pfCand) {
    if ( pfCand->particleId() == reco::PFCandidate::h ) {
      double dPhi = muJet->phi() - pfCand->phi();
      if (dPhi > M_PI) dPhi -= 2.*M_PI;
      if (dPhi < -M_PI) dPhi += 2.*M_PI;
      double dEta = muJet->eta() - pfCand->eta();
      double dR   = sqrt( dPhi*dPhi + dEta*dEta );
//      if ( dR < 0.4 && pfCand->pt() > 0.5 ) {
      if ( dR < 0.4 ) {
        double dz = fabs( pfCand->vertex().z() - theBeamSpot->position().z() - muJet->dz(theBeamSpot->position()) );
        if ( dz < 0.1 ) m_dimuorphan_isoPF_1mm += pfCand->pt();
      }
    }
  }
  
  m_dimuorphan_orphan_isoTk_3mm = 0;
  m_dimuorphan_orphan_isoTk_2mm = 0;
  m_dimuorphan_orphan_isoTk_1mm = 0;

  for (reco::TrackCollection::const_iterator track = tracks->begin(); track != tracks->end(); ++track) {
    if (!muJet->sameTrack(&*track,&*(orphan->innerTrack()))) {
      double dphi = orphan->innerTrack()->phi() - track->phi();
      if (dphi > M_PI) dphi -= 2.*M_PI;
      if (dphi < -M_PI) dphi += 2.*M_PI;
      double deta = orphan->innerTrack()->eta() - track->eta();
      double dR = sqrt(pow(dphi, 2) + pow(deta, 2));
      if (dR < 0.4 && track->pt() > iso_track_pt_treshold) {
        double dz = fabs(track->dz(theBeamSpot->position())-orphan->innerTrack()->dz(theBeamSpot->position()));
        if (dz < 0.3) m_dimuorphan_orphan_isoTk_3mm += track->pt();
        if (dz < 0.2) m_dimuorphan_orphan_isoTk_2mm += track->pt();
        if (dz < 0.1) m_dimuorphan_orphan_isoTk_1mm += track->pt();
      }
    }
  }
  
  m_dimuorphan_orphan_isoPF_1mm = 0.0;
  for (reco::PFCandidateCollection::const_iterator pfCand = pfCandidates->begin(); pfCand != pfCandidates->end(); ++pfCand) {
    if ( pfCand->particleId() == reco::PFCandidate::h ) {
      double dPhi = orphan->innerTrack()->phi() - pfCand->phi();
      if (dPhi > M_PI) dPhi -= 2.*M_PI;
      if (dPhi < -M_PI) dPhi += 2.*M_PI;
      double dEta = orphan->innerTrack()->eta() - pfCand->eta();
      double dR   = sqrt( dPhi*dPhi + dEta*dEta );
//      if ( dR < 0.4 && pfCand->pt() > 0.5 ) {
      if ( dR < 0.4 ) {
        double dz = fabs( pfCand->vertex().z() - theBeamSpot->position().z() - orphan->innerTrack()->dz(theBeamSpot->position()) );
        if ( dz < 0.1 ) m_dimuorphan_orphan_isoPF_1mm += pfCand->pt();
      }
    }
  }
  
  m_dimuorphan_trackdensity = 0;

  for (reco::TrackCollection::const_iterator track = tracks->begin(); track != tracks->end(); ++track) {
    if (!muJet->sameTrack(&*track,&*(muJet->muon(0)->innerTrack())) && !muJet->sameTrack(&*track,&*(muJet->muon(1)->innerTrack()))) {
                        double dphi0 = muJet->muon(0)->innerTrack()->phi() - track->phi();
                        if (dphi0 > M_PI) dphi0 -= 2.*M_PI;
                        if (dphi0 < -M_PI) dphi0 += 2.*M_PI;
                        double deta0 = muJet->muon(0)->innerTrack()->eta() - track->eta();
                        double dR0 = sqrt(pow(dphi0, 2) + pow(deta0, 2));
                        double dphi1 = muJet->muon(1)->innerTrack()->phi() - track->phi();
                        if (dphi1 > M_PI) dphi1 -= 2.*M_PI;
                        if (dphi1 < -M_PI) dphi1 += 2.*M_PI;
                        double deta1 = muJet->muon(1)->innerTrack()->eta() - track->eta();
                        double dR1 = sqrt(pow(dphi1, 2) + pow(deta1, 2));
                        if ((dR0 < 0.2 || dR1 < 0.2) && track->pt() > 1.) {
                                double dz0 = fabs(track->dz(theBeamSpot->position())-muJet->muon(0)->innerTrack()->dz(theBeamSpot->position()));
        double dz1 = fabs(track->dz(theBeamSpot->position())-muJet->muon(1)->innerTrack()->dz(theBeamSpot->position()));
                                if (dz0 < 0.2 || dz1 < 0.2) m_dimuorphan_trackdensity++;
                        }
    }
  }

      if (muJet->vertexValid()) {
   m_dimuorphan_deltaphi = muJet->vertexMomentum().phi() - orphan->phi();
   while (m_dimuorphan_deltaphi > M_PI) m_dimuorphan_deltaphi -= 2.*M_PI;
   while (m_dimuorphan_deltaphi < -M_PI) m_dimuorphan_deltaphi += 2.*M_PI;

   m_dimuorphan_mass = muJet->vertexMass();
   m_dimuorphan_corr_mass = muJet->vertexMass();
   m_dimuorphan_pt = muJet->vertexMomentum().perp();
   m_dimuorphan_eta = muJet->vertexMomentum().eta();
   m_dimuorphan_phi = muJet->vertexMomentum().phi();
   m_dimuorphan_dr = muJet->dRmax(true);
   m_dimuorphan_vprob = muJet->vertexProb();
   m_dimuorphan_vnchi2 = muJet->vertexNormalizedChi2();
   if (closestPrimaryVertex != primaryVertices->end()) {
      m_dimuorphan_lxy = muJet->lxy(GlobalPoint(closestPrimaryVertex->x(), closestPrimaryVertex->y(), closestPrimaryVertex->z()));
      m_dimuorphan_lxyz = muJet->lxyz(GlobalPoint(closestPrimaryVertex->x(), closestPrimaryVertex->y(), closestPrimaryVertex->z()));
   }

        double scale0 = scalePt(muJet->vertexMomentum(0).perp(),muJet->vertexMomentum(0).eta(),muJet->vertexMomentum(0).phi(),muJet->muon(0)->charge());
        double scale1 = scalePt(muJet->vertexMomentum(1).perp(),muJet->vertexMomentum(1).eta(),muJet->vertexMomentum(1).phi(),muJet->muon(1)->charge());

        double e1 = pow(pow(muJet->vertexMomentum(0).perp()*scale0,2)+pow(muJet->vertexMomentum(0).z(),2)+pow(muJet->muon(0)->mass(),2),0.5);
        double e2 = pow(pow(muJet->vertexMomentum(1).perp()*scale1,2)+pow(muJet->vertexMomentum(1).z(),2)+pow(muJet->muon(1)->mass(),2),0.5);
        double e = e1 + e2;

        double px = muJet->vertexMomentum(0).x()*scale0 + muJet->vertexMomentum(1).x()*scale1;
        double py = muJet->vertexMomentum(0).y()*scale0 + muJet->vertexMomentum(1).y()*scale1;
        double pz = muJet->vertexMomentum(0).z() + muJet->vertexMomentum(1).z();

        m_dimuorphan_corr_mass = pow(e*e-px*px-py*py-pz*pz,0.5);

      }

      if (muJet->daughter(0)->charge() > 0) {
         m_dimuorphan_plusmatches = muJet->muon(0)->numberOfMatches(reco::Muon::SegmentAndTrackArbitration);
         m_dimuorphan_minusmatches = muJet->muon(1)->numberOfMatches(reco::Muon::SegmentAndTrackArbitration);
         m_dimuorphan_plushits = muJet->muon(0)->innerTrack()->numberOfValidHits();
         m_dimuorphan_minushits = muJet->muon(1)->innerTrack()->numberOfValidHits();
         m_dimuorphan_plusnormchi2 = muJet->muon(0)->innerTrack()->normalizedChi2();
         m_dimuorphan_minusnormchi2 = muJet->muon(1)->innerTrack()->normalizedChi2();

  m_dimuorphan_plusstationmask = muJet->muon(0)->stationMask();
  m_dimuorphan_minusstationmask = muJet->muon(1)->stationMask();

        m_dimuorphan_plus_thits = muJet->muon(0)->innerTrack()->hitPattern().numberOfValidTrackerHits();
  m_dimuorphan_plus_mhits = 0;
        if (muJet->muon(0)->isGlobalMuon()) m_dimuorphan_plus_mhits = muJet->muon(0)->globalTrack()->hitPattern().numberOfValidMuonHits();
        m_dimuorphan_plus_phits = muJet->muon(0)->innerTrack()->hitPattern().numberOfValidPixelHits();

        m_dimuorphan_minus_thits = muJet->muon(1)->innerTrack()->hitPattern().numberOfValidTrackerHits();
  m_dimuorphan_minus_mhits = 0;
        if (muJet->muon(1)->isGlobalMuon()) m_dimuorphan_minus_mhits = muJet->muon(1)->globalTrack()->hitPattern().numberOfValidMuonHits();
        m_dimuorphan_minus_phits = muJet->muon(1)->innerTrack()->hitPattern().numberOfValidPixelHits();

        m_dimuorphan_plus_dxy = muJet->muon(0)->innerTrack()->dxy(theBeamSpot->position());
        m_dimuorphan_minus_dxy = muJet->muon(1)->innerTrack()->dxy(theBeamSpot->position());

        m_dimuorphan_plus_pt = muJet->muon(0)->pt();
        m_dimuorphan_minus_pt = muJet->muon(1)->pt();
        m_dimuorphan_plus_eta = muJet->muon(0)->eta();
        m_dimuorphan_minus_eta = muJet->muon(1)->eta();
        m_dimuorphan_plus_phi = muJet->muon(0)->phi();
        m_dimuorphan_minus_phi = muJet->muon(1)->phi();

  m_dimuorphan_Deltaphi = m_dimuorphan_plus_phi-m_dimuorphan_minus_phi;
  if (m_dimuorphan_Deltaphi > M_PI) m_dimuorphan_Deltaphi -= 2.*M_PI;
  if (m_dimuorphan_Deltaphi < -M_PI) m_dimuorphan_Deltaphi += 2.*M_PI;
/*
        for (trackingRecHit_iterator hit = muJet->muon(0)->innerTrack()->recHitsBegin(); hit != muJet->muon(0)->innerTrack()->recHitsEnd(); ++hit) {
                if ((*hit)->isValid()) {
                        GlobalPoint p = tkgeom->idToDet((*hit)->geographicalId())->toGlobal((*hit)->localPosition());
                        m_dimuorphan_plus_innerR = pow(p.x()*p.x()+p.y()*p.y(),0.5);
                        break;
                }
        }
        for (trackingRecHit_iterator hit = muJet->muon(1)->innerTrack()->recHitsBegin(); hit != muJet->muon(1)->innerTrack()->recHitsEnd(); ++hit) {
                if ((*hit)->isValid()) {
                        GlobalPoint p = tkgeom->idToDet((*hit)->geographicalId())->toGlobal((*hit)->localPosition());
                        m_dimuorphan_minus_innerR = pow(p.x()*p.x()+p.y()*p.y(),0.5);
                        break;
                }
        }
*/

      }
      else {
         m_dimuorphan_plusmatches = muJet->muon(1)->numberOfMatches(reco::Muon::SegmentAndTrackArbitration);
         m_dimuorphan_minusmatches = muJet->muon(0)->numberOfMatches(reco::Muon::SegmentAndTrackArbitration);
         m_dimuorphan_plushits = muJet->muon(1)->innerTrack()->numberOfValidHits();
         m_dimuorphan_minushits = muJet->muon(0)->innerTrack()->numberOfValidHits();
         m_dimuorphan_plusnormchi2 = muJet->muon(1)->innerTrack()->normalizedChi2();
         m_dimuorphan_minusnormchi2 = muJet->muon(0)->innerTrack()->normalizedChi2();

  m_dimuorphan_plusstationmask = muJet->muon(1)->stationMask();
  m_dimuorphan_minusstationmask = muJet->muon(0)->stationMask();

        m_dimuorphan_plus_thits = muJet->muon(1)->innerTrack()->hitPattern().numberOfValidTrackerHits();
        m_dimuorphan_plus_mhits = 0;
        if (muJet->muon(1)->isGlobalMuon()) m_dimuorphan_plus_mhits = muJet->muon(1)->globalTrack()->hitPattern().numberOfValidMuonHits();
        m_dimuorphan_plus_phits = muJet->muon(1)->innerTrack()->hitPattern().numberOfValidPixelHits();

        m_dimuorphan_minus_thits = muJet->muon(0)->innerTrack()->hitPattern().numberOfValidTrackerHits();
        m_dimuorphan_minus_mhits = 0;
        if (muJet->muon(0)->isGlobalMuon()) m_dimuorphan_minus_mhits = muJet->muon(0)->globalTrack()->hitPattern().numberOfValidMuonHits();
        m_dimuorphan_minus_phits = muJet->muon(0)->innerTrack()->hitPattern().numberOfValidPixelHits();

        m_dimuorphan_plus_dxy = muJet->muon(1)->innerTrack()->dxy(theBeamSpot->position());
        m_dimuorphan_minus_dxy = muJet->muon(0)->innerTrack()->dxy(theBeamSpot->position());

        m_dimuorphan_plus_pt = muJet->muon(1)->pt();
        m_dimuorphan_minus_pt = muJet->muon(0)->pt();
        m_dimuorphan_plus_eta = muJet->muon(1)->eta();
        m_dimuorphan_minus_eta = muJet->muon(0)->eta();
        m_dimuorphan_plus_phi = muJet->muon(1)->phi();
        m_dimuorphan_minus_phi = muJet->muon(0)->phi();

  m_dimuorphan_Deltaphi = m_dimuorphan_plus_phi-m_dimuorphan_minus_phi;
  if (m_dimuorphan_Deltaphi > M_PI) m_dimuorphan_Deltaphi -= 2.*M_PI;
  if (m_dimuorphan_Deltaphi < -M_PI) m_dimuorphan_Deltaphi += 2.*M_PI;
/*
        for (trackingRecHit_iterator hit = muJet->muon(0)->innerTrack()->recHitsBegin(); hit != muJet->muon(0)->innerTrack()->recHitsEnd(); ++hit) {
                if ((*hit)->isValid()) {
                        GlobalPoint p = tkgeom->idToDet((*hit)->geographicalId())->toGlobal((*hit)->localPosition());
                        m_dimuorphan_minus_innerR = pow(p.x()*p.x()+p.y()*p.y(),0.5);
                        break;
                }
        }
        for (trackingRecHit_iterator hit = muJet->muon(1)->innerTrack()->recHitsBegin(); hit != muJet->muon(1)->innerTrack()->recHitsEnd(); ++hit) {
                if ((*hit)->isValid()) {
                        GlobalPoint p = tkgeom->idToDet((*hit)->geographicalId())->toGlobal((*hit)->localPosition());
                        m_dimuorphan_plus_innerR = pow(p.x()*p.x()+p.y()*p.y(),0.5);
                        break;
                }
        }
*/

      }
  m_dimuorphan_Deltaphi_orphan = m_dimuorphan_orphanphi - m_dimuorphan_phi;
  if (m_dimuorphan_Deltaphi_orphan > M_PI) m_dimuorphan_Deltaphi_orphan -= 2.*M_PI;
  if (m_dimuorphan_Deltaphi_orphan < -M_PI) m_dimuorphan_Deltaphi_orphan += 2.*M_PI;

  m_dimuorphan_plus_isGlobal = 0;
  m_dimuorphan_plus_isStandAlone = 0;
  m_dimuorphan_plus_GlobalHits = -1;
  m_dimuorphan_plus_GlobalChi2 = -1;
  m_dimuorphan_plus_StandAloneHits = -1;
  m_dimuorphan_plus_StandAloneChi2 = -1;

  m_dimuorphan_minus_isGlobal = 0;
  m_dimuorphan_minus_isStandAlone = 0;
  m_dimuorphan_minus_GlobalHits = -1;
  m_dimuorphan_minus_GlobalChi2 = -1;
  m_dimuorphan_minus_StandAloneHits = -1;
  m_dimuorphan_minus_StandAloneChi2 = -1;

  if (muJet->daughter(0)->charge() > 0) {
    m_dimuorphan_plus_qoverpError = muJet->muon(0)->innerTrack()->qoverpError();
                m_dimuorphan_plus_ptError = muJet->muon(0)->innerTrack()->ptError();
                m_dimuorphan_plus_phiError = muJet->muon(0)->innerTrack()->phiError();
                m_dimuorphan_plus_etaError = muJet->muon(0)->innerTrack()->etaError();
    if (muJet->muon(0)->isGlobalMuon()) {
                  m_dimuorphan_plus_isGlobal = 1;
                  m_dimuorphan_plus_GlobalHits = muJet->muon(0)->globalTrack()->numberOfValidHits();
                  m_dimuorphan_plus_GlobalChi2 = muJet->muon(0)->globalTrack()->normalizedChi2();
    }
                if (muJet->muon(0)->isStandAloneMuon()) {
                        m_dimuorphan_plus_isStandAlone = 1; 
                        m_dimuorphan_plus_StandAloneHits = muJet->muon(0)->outerTrack()->numberOfValidHits();
                        m_dimuorphan_plus_StandAloneChi2 = muJet->muon(0)->outerTrack()->normalizedChi2();
                }
                m_dimuorphan_minus_qoverpError = muJet->muon(1)->innerTrack()->qoverpError();
                m_dimuorphan_minus_ptError = muJet->muon(1)->innerTrack()->ptError();
                m_dimuorphan_minus_phiError = muJet->muon(1)->innerTrack()->phiError();
                m_dimuorphan_minus_etaError = muJet->muon(1)->innerTrack()->etaError();
                if (muJet->muon(1)->isGlobalMuon()) {
                        m_dimuorphan_minus_isGlobal = 1; 
                        m_dimuorphan_minus_GlobalHits = muJet->muon(1)->globalTrack()->numberOfValidHits();
                        m_dimuorphan_minus_GlobalChi2 = muJet->muon(1)->globalTrack()->normalizedChi2();
                }
                if (muJet->muon(1)->isStandAloneMuon()) {
                        m_dimuorphan_minus_isStandAlone = 1;
                        m_dimuorphan_minus_StandAloneHits = muJet->muon(1)->outerTrack()->numberOfValidHits();
                        m_dimuorphan_minus_StandAloneChi2 = muJet->muon(1)->outerTrack()->normalizedChi2();
                }
  }
        else { 
                m_dimuorphan_plus_qoverpError = muJet->muon(1)->innerTrack()->qoverpError();
                m_dimuorphan_plus_ptError = muJet->muon(1)->innerTrack()->ptError();
                m_dimuorphan_plus_phiError = muJet->muon(1)->innerTrack()->phiError();
                m_dimuorphan_plus_etaError = muJet->muon(1)->innerTrack()->etaError();
                if (muJet->muon(1)->isGlobalMuon()) {
                        m_dimuorphan_plus_isGlobal = 1; 
                        m_dimuorphan_plus_GlobalHits = muJet->muon(1)->globalTrack()->numberOfValidHits();
                        m_dimuorphan_plus_GlobalChi2 = muJet->muon(1)->globalTrack()->normalizedChi2();
                }
                if (muJet->muon(1)->isStandAloneMuon()) {
                        m_dimuorphan_plus_isStandAlone = 1;
                        m_dimuorphan_plus_StandAloneHits = muJet->muon(1)->outerTrack()->numberOfValidHits();
                        m_dimuorphan_plus_StandAloneChi2 = muJet->muon(1)->outerTrack()->normalizedChi2();
                }
                m_dimuorphan_minus_qoverpError = muJet->muon(0)->innerTrack()->qoverpError();
                m_dimuorphan_minus_ptError = muJet->muon(0)->innerTrack()->ptError();
                m_dimuorphan_minus_phiError = muJet->muon(0)->innerTrack()->phiError();
                m_dimuorphan_minus_etaError = muJet->muon(0)->innerTrack()->etaError();
                if (muJet->muon(0)->isGlobalMuon()) {
                        m_dimuorphan_minus_isGlobal = 1;
                        m_dimuorphan_minus_GlobalHits = muJet->muon(0)->globalTrack()->numberOfValidHits();
                        m_dimuorphan_minus_GlobalChi2 = muJet->muon(0)->globalTrack()->normalizedChi2();
                }
                if (muJet->muon(0)->isStandAloneMuon()) {
                        m_dimuorphan_minus_isStandAlone = 1;
                        m_dimuorphan_minus_StandAloneHits = muJet->muon(0)->outerTrack()->numberOfValidHits();
                        m_dimuorphan_minus_StandAloneChi2 = muJet->muon(0)->outerTrack()->normalizedChi2();
                }
        }

      m_dimuorphan_dimuonbbbarlike = -1;
      if (m_dimuorphan_isoTk > 4.5 || m_dimuorphan_lxy > 0.2) m_dimuorphan_dimuonbbbarlike = 1;
      if (m_dimuorphan_isoTk < 4.5 && m_dimuorphan_lxy < 0.2) m_dimuorphan_dimuonbbbarlike = 0;

/*
  const pat::Muon *muplus = NULL;
  const pat::Muon *muminus = NULL;

  if (muJet->muon(0)->charge() > 0) {
    muplus = &*muJet->muon(0);
    muminus = &*muJet->muon(1);
  }
        if (muJet->muon(0)->charge() < 0) { 
                muplus = &*muJet->muon(1);
                muminus = &*muJet->muon(0);
        }

      FreeTrajectoryState plus_initial(GlobalPoint(muplus->vx(), muplus->vy(), muplus->vz()), GlobalVector(muplus->px(), muplus->py(), muplus->pz()), 1, &*magneticField);
      FreeTrajectoryState minus_initial(GlobalPoint(muminus->vx(), muminus->vy(), muminus->vz()), GlobalVector(muminus->px(), muminus->py(), muminus->pz()), -1, &*magneticField);

  Cylinder::CylinderPointer m_cylinder = Cylinder::build(Cylinder::PositionType(0., 0., 0.), Cylinder::RotationType(), 600.);
  Plane::PlanePointer m_plane = Plane::build(Plane::PositionType(0., 0., 800.), Plane::RotationType());


  if (fabs(m_dimuorphan_eta) < 1.1) {
    TrajectoryStateOnSurface plus_final = propagator->propagate(plus_initial, *m_cylinder);
    TrajectoryStateOnSurface minus_final = propagator->propagate(minus_initial, *m_cylinder);
    if (plus_final.isValid()  &&  minus_final.isValid()) {
      double dphi = plus_final.globalPosition().phi() - minus_final.globalPosition().phi();
      while (dphi > M_PI) dphi -= 2.*M_PI;
      while (dphi < -M_PI) dphi += 2.*M_PI;
      m_dimuorphan_dphi = dphi;
    }
  }
  else {
                TrajectoryStateOnSurface plus_final = propagator->propagate(plus_initial, *m_plane);
                TrajectoryStateOnSurface minus_final = propagator->propagate(minus_initial, *m_plane);
                if (plus_final.isValid()  &&  minus_final.isValid()) {
                        double dphi = plus_final.globalPosition().phi() - minus_final.globalPosition().phi();
                        while (dphi > M_PI) dphi -= 2.*M_PI;
                        while (dphi < -M_PI) dphi += 2.*M_PI;
                        m_dimuorphan_dphi = dphi;
                }
        }

        if (fabs(m_dimuorphan_eta) < 0.9) {
                TrajectoryStateOnSurface plus_final = propagator->propagate(plus_initial, *m_cylinder100);
                TrajectoryStateOnSurface minus_final = propagator->propagate(minus_initial, *m_cylinder100);
                if (plus_final.isValid()  &&  minus_final.isValid()) {
                        double dphi = plus_final.globalPosition().phi() - minus_final.globalPosition().phi();
                        while (dphi > M_PI) dphi -= 2.*M_PI;
                        while (dphi < -M_PI) dphi += 2.*M_PI;
                        m_dimuorphan_dphi100 = dphi;
                }
                plus_final = propagator->propagate(plus_initial, *m_cylinder200);
                minus_final = propagator->propagate(minus_initial, *m_cylinder200);
                if (plus_final.isValid()  &&  minus_final.isValid()) {
                        double dphi = plus_final.globalPosition().phi() - minus_final.globalPosition().phi();
                        while (dphi > M_PI) dphi -= 2.*M_PI;
                        while (dphi < -M_PI) dphi += 2.*M_PI;
                        m_dimuorphan_dphi200 = dphi;
                }
                plus_final = propagator->propagate(plus_initial, *m_cylinder300);
                minus_final = propagator->propagate(minus_initial, *m_cylinder300);
                if (plus_final.isValid()  &&  minus_final.isValid()) {
                        double dphi = plus_final.globalPosition().phi() - minus_final.globalPosition().phi();
                        while (dphi > M_PI) dphi -= 2.*M_PI;
                        while (dphi < -M_PI) dphi += 2.*M_PI;
                        m_dimuorphan_dphi300 = dphi;
                }
                plus_final = propagator->propagate(plus_initial, *m_cylinder425);
                minus_final = propagator->propagate(minus_initial, *m_cylinder425);
                if (plus_final.isValid()  &&  minus_final.isValid()) {
                        double dphi = plus_final.globalPosition().phi() - minus_final.globalPosition().phi();
                        while (dphi > M_PI) dphi -= 2.*M_PI;
                        while (dphi < -M_PI) dphi += 2.*M_PI;
                        m_dimuorphan_dphi425 = dphi;
                }
                plus_final = propagator->propagate(plus_initial, *m_cylinder470);
                minus_final = propagator->propagate(minus_initial, *m_cylinder470);
                if (plus_final.isValid()  &&  minus_final.isValid()) {
                        double dphi = plus_final.globalPosition().phi() - minus_final.globalPosition().phi();
                        while (dphi > M_PI) dphi -= 2.*M_PI;
                        while (dphi < -M_PI) dphi += 2.*M_PI;
                        m_dimuorphan_dphi470 = dphi;
                }
                plus_final = propagator->propagate(plus_initial, *m_cylinder510);
                minus_final = propagator->propagate(minus_initial, *m_cylinder510);
                if (plus_final.isValid()  &&  minus_final.isValid()) {
                        double dphi = plus_final.globalPosition().phi() - minus_final.globalPosition().phi();
                        while (dphi > M_PI) dphi -= 2.*M_PI;
                        while (dphi < -M_PI) dphi += 2.*M_PI;
                        m_dimuorphan_dphi510 = dphi;
                }
                plus_final = propagator->propagate(plus_initial, *m_cylinder565);
                minus_final = propagator->propagate(minus_initial, *m_cylinder565);
                if (plus_final.isValid()  &&  minus_final.isValid()) {
                        double dphi = plus_final.globalPosition().phi() - minus_final.globalPosition().phi();
                        while (dphi > M_PI) dphi -= 2.*M_PI;
                        while (dphi < -M_PI) dphi += 2.*M_PI;
                        m_dimuorphan_dphi565 = dphi;
                }
                plus_final = propagator->propagate(plus_initial, *m_cylinder620);
                minus_final = propagator->propagate(minus_initial, *m_cylinder620);
                if (plus_final.isValid()  &&  minus_final.isValid()) {
                        double dphi = plus_final.globalPosition().phi() - minus_final.globalPosition().phi();
                        while (dphi > M_PI) dphi -= 2.*M_PI;
                        while (dphi < -M_PI) dphi += 2.*M_PI;
                        m_dimuorphan_dphi620 = dphi;
                }
                plus_final = propagator->propagate(plus_initial, *m_cylinder670);
                minus_final = propagator->propagate(minus_initial, *m_cylinder670);
                if (plus_final.isValid()  &&  minus_final.isValid()) {
                        double dphi = plus_final.globalPosition().phi() - minus_final.globalPosition().phi();
                        while (dphi > M_PI) dphi -= 2.*M_PI;
                        while (dphi < -M_PI) dphi += 2.*M_PI;
                        m_dimuorphan_dphi670 = dphi;
                }
                plus_final = propagator->propagate(plus_initial, *m_cylinder720);
                minus_final = propagator->propagate(minus_initial, *m_cylinder720);
                if (plus_final.isValid()  &&  minus_final.isValid()) {
                        double dphi = plus_final.globalPosition().phi() - minus_final.globalPosition().phi();
                        while (dphi > M_PI) dphi -= 2.*M_PI;
                        while (dphi < -M_PI) dphi += 2.*M_PI;
                        m_dimuorphan_dphi720 = dphi;
                }
                plus_final = propagator->propagate(plus_initial, *m_cylinder800);
                minus_final = propagator->propagate(minus_initial, *m_cylinder800);
                if (plus_final.isValid()  &&  minus_final.isValid()) {
                        double dphi = plus_final.globalPosition().phi() - minus_final.globalPosition().phi();
                        while (dphi > M_PI) dphi -= 2.*M_PI;
                        while (dphi < -M_PI) dphi += 2.*M_PI;
                        m_dimuorphan_dphi800 = dphi;
                }
                plus_final = propagator->propagate(plus_initial, *m_cylinder900);
                minus_final = propagator->propagate(minus_initial, *m_cylinder900);
                if (plus_final.isValid()  &&  minus_final.isValid()) {
                        double dphi = plus_final.globalPosition().phi() - minus_final.globalPosition().phi();
                        while (dphi > M_PI) dphi -= 2.*M_PI;
                        while (dphi < -M_PI) dphi += 2.*M_PI;
                        m_dimuorphan_dphi900 = dphi;
                }
        }
*/

        m_dimuorphan_dz1 = muJet->dz(theBeamSpot->position());
  m_dimuorphan_dz2 = orphan->innerTrack()->dz(theBeamSpot->position());
  m_dimuorphan_deltaz = m_dimuorphan_dz1 - m_dimuorphan_dz2;

  m_dimuorphan_muonssize = allmuons->size();

      if ((m_dimuorphan_containstrig > 0 || m_dimuorphan_containstrig2 > 0) && fabs(m_dimuorphan_deltaz) < 0.1) m_dimuorphan->Fill();

   }

/////////////////////////////////////////////////////////////
//                     DIMUON + DIMUON                     //
/////////////////////////////////////////////////////////////

  if (   muJets->size() == 2
      && (*muJets)[0].numberOfDaughters() == 2
      && (*muJets)[1].numberOfDaughters() == 2
      && m_trigger > 0) {
    const pat::MultiMuon *muJet0 = &((*muJets)[0]);
    const pat::MultiMuon *muJet1 = &((*muJets)[1]);

    bool muJet0_canBeC = false;
    bool muJet1_canBeC = false;
    for (std::vector<pat::MuonCollection::const_iterator>::const_iterator iter = hightrigmuons.begin();  iter != hightrigmuons.end();  ++iter) {
      if ( muJet0->muon(0)->innerTrack().isAvailable() && (*iter)->innerTrack().isAvailable()
          && muJet0->sameTrack(&*(muJet0->muon(0)->innerTrack()), &*((*iter)->innerTrack())) ) {
        muJet0_canBeC = true;
      }
      if ( muJet0->muon(1)->innerTrack().isAvailable() && (*iter)->innerTrack().isAvailable()
           && muJet0->sameTrack(&*(muJet0->muon(1)->innerTrack()), &*((*iter)->innerTrack())) ) {
        muJet0_canBeC = true;
      }
      if ( muJet1->muon(0)->innerTrack().isAvailable() && (*iter)->innerTrack().isAvailable()
           && muJet1->sameTrack(&*(muJet1->muon(0)->innerTrack()), &*((*iter)->innerTrack())) ) {
        muJet1_canBeC = true;
      }
      if ( muJet1->muon(1)->innerTrack().isAvailable() && (*iter)->innerTrack().isAvailable()
           && muJet1->sameTrack(&*(muJet1->muon(1)->innerTrack()), &*((*iter)->innerTrack())) ) {
        muJet1_canBeC = true;
      }
    }

      for (std::vector<pat::MuonCollection::const_iterator>::const_iterator iter = lowtrigmuons.begin();  iter != lowtrigmuons.end();  ++iter) {
         if (muJet0->muon(0)->innerTrack().isAvailable()  &&  (*iter)->innerTrack().isAvailable()  &&
             muJet0->sameTrack(&*(muJet0->muon(0)->innerTrack()), &*((*iter)->innerTrack()))) {
            m_dimudimu_containstrig2++;
         }
         if (muJet0->muon(1)->innerTrack().isAvailable()  &&  (*iter)->innerTrack().isAvailable()  &&
             muJet0->sameTrack(&*(muJet0->muon(1)->innerTrack()), &*((*iter)->innerTrack()))) {
            m_dimudimu_containstrig2++;
         }

         if (muJet1->muon(0)->innerTrack().isAvailable()  &&  (*iter)->innerTrack().isAvailable()  &&
             muJet1->sameTrack(&*(muJet1->muon(0)->innerTrack()), &*((*iter)->innerTrack()))) {
            m_dimudimu_containstrig2++;
         }
         if (muJet1->muon(1)->innerTrack().isAvailable()  &&  (*iter)->innerTrack().isAvailable()  &&
             muJet1->sameTrack(&*(muJet1->muon(1)->innerTrack()), &*((*iter)->innerTrack()))) {
            m_dimudimu_containstrig2++;
         }
      }

      const pat::MultiMuon *muJetC = NULL;
      const pat::MultiMuon *muJetF = NULL;
      if (muJet0_canBeC  &&  muJet1_canBeC) {
   m_dimudimu_containstrig = 1;

   if (m_trandom3.Integer(2) == 0) {
      muJetC = muJet0;
      muJetF = muJet1;
   }
   else {
      muJetC = muJet1;
      muJetF = muJet0;
   }
      }
      else if (muJet0_canBeC) {
   m_dimudimu_containstrig = 1;

   muJetC = muJet0;
   muJetF = muJet1;
      }
      else if (muJet1_canBeC) {
   m_dimudimu_containstrig = 1;

   muJetC = muJet1;
   muJetF = muJet0;
      }
      else {
   m_dimudimu_containstrig = 0;
      }

      if (muJetC != NULL  &&  muJetF != NULL) {
   m_dimudimu_orphans = orphans->size();

   double total_energy = muJetC->energy() + muJetF->energy();
   double total_px = muJetC->px() + muJetF->px();
   double total_py = muJetC->py() + muJetF->py();
   double total_pz = muJetC->pz() + muJetF->pz();

   m_dimudimu_wholemass = sqrt(total_energy*total_energy - total_px*total_px - total_py*total_py - total_pz*total_pz);
   m_dimudimu_wholept = sqrt(total_px*total_px + total_py*total_py);

   m_dimudimu_deltaphi = muJetC->phi() - muJetF->phi();
   while (m_dimudimu_deltaphi > M_PI) m_dimudimu_deltaphi -= 2.*M_PI;
   while (m_dimudimu_deltaphi < -M_PI) m_dimudimu_deltaphi += 2.*M_PI;

   m_dimudimu_massC = muJetC->mass();
   m_dimudimu_ptC = muJetC->pt();
   m_dimudimu_etaC = muJetC->eta();
   m_dimudimu_phiC = muJetC->phi();
   m_dimudimu_drC = muJetC->dRmax();
   m_dimudimu_vprobC = -1.;
   m_dimudimu_lxyC = -1000.;
   m_dimudimu_lxyzC = -1000.;
   m_dimudimu_C_isoTk = muJetC->centralTrackIsolation();

  m_dimudimu_C_isoTk_3mm = 0;
  m_dimudimu_C_isoTk_2mm = 0;
  m_dimudimu_C_isoTk_1mm = 0;

  for (reco::TrackCollection::const_iterator track = tracks->begin(); track != tracks->end(); ++track) {
    bool track_is_muon = false;
    if (muJetC->sameTrack(&*track,&*(muJetC->muon(0)->innerTrack())) || muJetC->sameTrack(&*track,&*(muJetC->muon(1)->innerTrack()))) track_is_muon = true;
    if (!track_is_muon) {
      double dphi = muJetC->phi() - track->phi();
      if (dphi > M_PI) dphi -= 2.*M_PI;
      if (dphi < -M_PI) dphi += 2.*M_PI;
      double deta = muJetC->eta() - track->eta();
      double dR = sqrt(pow(dphi, 2) + pow(deta, 2)); 
      if (dR < 0.4 && track->pt() > iso_track_pt_treshold) {
        double dz = fabs(track->dz(theBeamSpot->position())-muJetC->dz(theBeamSpot->position()));
        if (dz < 0.3) m_dimudimu_C_isoTk_3mm += track->pt();
        if (dz < 0.2) m_dimudimu_C_isoTk_2mm += track->pt();
        if (dz < 0.1) m_dimudimu_C_isoTk_1mm += track->pt();
      }    
    }
  }
  
  m_dimudimu_C_isoPF_1mm = 0.0;
  for (reco::PFCandidateCollection::const_iterator pfCand = pfCandidates->begin(); pfCand != pfCandidates->end(); ++pfCand) {
    if ( pfCand->particleId() == reco::PFCandidate::h ) {
      double dPhi = muJetC->phi() - pfCand->phi();
      if (dPhi > M_PI) dPhi -= 2.*M_PI;
      if (dPhi < -M_PI) dPhi += 2.*M_PI;
      double dEta = muJetC->eta() - pfCand->eta();
      double dR   = sqrt( dPhi*dPhi + dEta*dEta );
//      if ( dR < 0.4 && pfCand->pt() > 0.5 ) {
      if ( dR < 0.4 ) {
        double dz = fabs( pfCand->vertex().z() - theBeamSpot->position().z() - muJetC->dz(theBeamSpot->position()) );
        if ( dz < 0.1 ) m_dimudimu_C_isoPF_1mm += pfCand->pt();
      }
    }
  }
  
   m_dimudimu_massF = muJetF->mass();
   std::cout << "m_dimudimu_massF = muJetF->mass(): " << m_dimudimu_massF << std::endl;
   m_dimudimu_ptF = muJetF->pt();
   m_dimudimu_etaF = muJetF->eta();
   m_dimudimu_phiF = muJetF->phi();
   m_dimudimu_drF = muJetF->dRmax();
   m_dimudimu_vprobF = -1.;
   m_dimudimu_lxyF = -1000.;
   m_dimudimu_lxyzF = -1000.;
   m_dimudimu_F_isoTk = muJetF->centralTrackIsolation();

  m_dimudimu_F_isoTk_3mm = 0;
  m_dimudimu_F_isoTk_2mm = 0;
  m_dimudimu_F_isoTk_1mm = 0;

  for (reco::TrackCollection::const_iterator track = tracks->begin(); track != tracks->end(); ++track) {
    bool track_is_muon = false;
    if (muJetF->sameTrack(&*track,&*(muJetF->muon(0)->innerTrack())) || muJetF->sameTrack(&*track,&*(muJetF->muon(1)->innerTrack()))) track_is_muon = true;
    if (!track_is_muon) {
      double dphi = muJetF->phi() - track->phi();
      if (dphi > M_PI) dphi -= 2.*M_PI;
      if (dphi < -M_PI) dphi += 2.*M_PI;
      double deta = muJetF->eta() - track->eta();
      double dR = sqrt(pow(dphi, 2) + pow(deta, 2)); 
      if (dR < 0.4 && track->pt() > iso_track_pt_treshold) {
        double dz = fabs(track->dz(theBeamSpot->position())-muJetF->dz(theBeamSpot->position()));
        if (dz < 0.3) m_dimudimu_F_isoTk_3mm += track->pt();
        if (dz < 0.2) m_dimudimu_F_isoTk_2mm += track->pt();
        if (dz < 0.1) m_dimudimu_F_isoTk_1mm += track->pt();
      }
    }
  }
  
  m_dimudimu_F_isoPF_1mm = 0.0;
  for (reco::PFCandidateCollection::const_iterator pfCand = pfCandidates->begin(); pfCand != pfCandidates->end(); ++pfCand) {
    if ( pfCand->particleId() == reco::PFCandidate::h ) {
      double dPhi = muJetF->phi() - pfCand->phi();
      if (dPhi > M_PI) dPhi -= 2.*M_PI;
      if (dPhi < -M_PI) dPhi += 2.*M_PI;
      double dEta = muJetF->eta() - pfCand->eta();
      double dR   = sqrt( dPhi*dPhi + dEta*dEta );
//      if ( dR < 0.4 && pfCand->pt() > 0.5 ) {
      if ( dR < 0.4 ) {
        double dz = fabs( pfCand->vertex().z() - theBeamSpot->position().z() - muJetF->dz(theBeamSpot->position()) );
        if ( dz < 0.1 ) m_dimudimu_F_isoPF_1mm += pfCand->pt();
      }
    }
  }

   if (muJetC->vertexValid() && muJetF->vertexValid()) {
      total_energy = muJetC->vertexP4().energy() + muJetF->vertexP4().energy();
      total_px = muJetC->vertexMomentum().x() + muJetF->vertexMomentum().x();
      total_py = muJetC->vertexMomentum().y() + muJetF->vertexMomentum().y();
      total_pz = muJetC->vertexMomentum().z() + muJetF->vertexMomentum().z();

      m_dimudimu_wholemass = sqrt(total_energy*total_energy - total_px*total_px - total_py*total_py - total_pz*total_pz);
      m_dimudimu_wholept = sqrt(total_px*total_px + total_py*total_py);

      m_dimudimu_deltaphi = muJetC->vertexMomentum().phi() - muJetF->vertexMomentum().phi();
      while (m_dimudimu_deltaphi > M_PI) m_dimudimu_deltaphi -= 2.*M_PI;
      while (m_dimudimu_deltaphi < -M_PI) m_dimudimu_deltaphi += 2.*M_PI;

      m_dimudimu_massC = muJetC->vertexMass();
      m_dimudimu_ptC = muJetC->vertexMomentum().perp();
      m_dimudimu_etaC = muJetC->vertexMomentum().eta();
      m_dimudimu_phiC = muJetC->vertexMomentum().phi();
      m_dimudimu_drC = muJetC->dRmax(true);
      m_dimudimu_vprobC = muJetC->vertexProb();
      if (closestPrimaryVertex != primaryVertices->end()) {
         m_dimudimu_lxyC = muJetC->lxy(GlobalPoint(closestPrimaryVertex->x(), closestPrimaryVertex->y(), closestPrimaryVertex->z()));
         m_dimudimu_lxyzC = muJetC->lxyz(GlobalPoint(closestPrimaryVertex->x(), closestPrimaryVertex->y(), closestPrimaryVertex->z()));
      }

      m_dimudimu_massF = muJetF->vertexMass();
      std::cout << "m_dimudimu_massF = muJetF->vertexMass(): " << m_dimudimu_massF << std::endl;
      
      m_dimudimu_ptF = muJetF->vertexMomentum().perp();
      m_dimudimu_etaF = muJetF->vertexMomentum().eta();
      m_dimudimu_phiF = muJetF->vertexMomentum().phi();
      m_dimudimu_drF = muJetF->dRmax(true);
      m_dimudimu_vprobF = muJetF->vertexProb();
      if (closestPrimaryVertex != primaryVertices->end()) {
         m_dimudimu_lxyF = muJetF->lxy(GlobalPoint(closestPrimaryVertex->x(), closestPrimaryVertex->y(), closestPrimaryVertex->z()));
         m_dimudimu_lxyzF = muJetF->lxyz(GlobalPoint(closestPrimaryVertex->x(), closestPrimaryVertex->y(), closestPrimaryVertex->z()));
      }
   }

        m_dimudimu_dz1 = muJet0->dz(theBeamSpot->position());
        m_dimudimu_dz2 = muJet1->dz(theBeamSpot->position());
        m_dimudimu_deltaz = m_dimudimu_dz1 - m_dimudimu_dz2;

   if (m_dimudimu_containstrig > 0 && fabs(m_dimudimu_deltaz) < 0.1) m_dimudimu->Fill();
      }
   }
}


// ------------ method called once each job just before starting event loop  ------------
void FitNtuple::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void FitNtuple::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(FitNtuple);
