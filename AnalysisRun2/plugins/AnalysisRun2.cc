// -*- C++ -*-
//
// Package:    MuJetAnalysis/AnalysisRun2
// Class:      AnalysisRun2
// 
/**\class AnalysisRun2 AnalysisRun2.cc MuJetAnalysis/AnalysisRun2/plugins/AnalysisRun2.cc

   Description: [one line class summary]

   Implementation:
   [Notes on implementation]
*/
//
// Original Author:  alfredo castaneda
//         Created:  Thu, 10 Sep 2015 11:37:28 GMT
//
//


// system include files
#include <memory>

//#include "RecoTracker/SiTrackerMRHTools/interface/SimpleDAFHitCollector.h"
//#include "RecoTracker/SiTrackerMRHTools/interface/SiTrackerMultiRecHitUpdator.h"



#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "DataFormats/GeometrySurface/interface/Plane.h"
#include "DataFormats/GeometryVector/interface/Point2DBase.h"

#include <DataFormats/SiPixelDetId/interface/PXBDetId.h>
#include <DataFormats/SiPixelDetId/interface/PXFDetId.h>

#include "TTree.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/ESInputTag.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"

#include <DataFormats/TrackingRecHit/interface/InvalidTrackingRecHit.h>
#include "DataFormats/Common/interface/AssociationMap.h"
#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandMatchMap.h"
#include "DataFormats/TrackingRecHit/interface/TrackingRecHit.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/TrackReco/interface/HitPattern.h"

#include "RecoTracker/TrackProducer/interface/TrackProducerBase.h"
#include "RecoTracker/Record/interface/NavigationSchoolRecord.h"
#include <RecoTracker/MeasurementDet/interface/MeasurementTracker.h>
#include "RecoTracker/MeasurementDet/interface/MeasurementTrackerEvent.h"
#include "RecoTracker/Record/interface/CkfComponentsRecord.h"
#include "RecoTracker/Record/interface/TrackerRecoGeometryRecord.h"

#include "TrackingTools/Records/interface/TrackingComponentsRecord.h" 
#include "TrackingTools/TransientTrackingRecHit/interface/TransientTrackingRecHit.h"
#include "TrackingTools/TrackFitters/interface/TrajectoryFitterRecord.h" 
#include "TrackingTools/Records/interface/TransientRecHitRecord.h" 
#include "TrackingTools/TrackFitters/interface/TrajectoryFitter.h"
#include "TrackingTools/GeomPropagators/interface/Propagator.h"
#include "TrackingTools/DetLayers/interface/NavigationSchool.h"
//#include "TrackingTools/DetLayers/interface/NavigationSetter.h"
//#include "RecoTracker/TkNavigation/interface/SimpleNavigationSchool.h"
#include "RecoTracker/SiTrackerMRHTools/interface/SiTrackerMultiRecHitUpdator.h"
#include <TrackingTools/KalmanUpdators/interface/Chi2MeasurementEstimator.h>
#include <TrackingTools/DetLayers/interface/GeometricSearchDet.h> 
#include <TrackingTools/MeasurementDet/interface/MeasurementDet.h>
#include "TrackingTools/DetLayers/interface/DetLayerGeometry.h"
#include "TrackingTools/DetLayers/interface/NavigableLayer.h"
#include "TrackingTools/TrackFitters/interface/TrajectoryFitter.h"
#include "TrackingTools/PatternTools/interface/Trajectory.h"
#include "TrackingTools/PatternTools/interface/TrajectoryMeasurement.h"
#include "TrackingTools/DetLayers/interface/DetLayer.h"
#include "TrackingTools/GeomPropagators/interface/Propagator.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"

#include "MagneticField/Engine/interface/MagneticField.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h" 
#include "RecoMuon/Navigation/interface/MuonNavigableLayer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "MagneticField/Engine/interface/MagneticField.h"

#include "DataFormats/TrackReco/interface/TrackFwd.h"

#include "MuJetAnalysis/DataFormats/interface/MultiMuon.h"
#include "MuJetAnalysis/AnalysisTools/interface/ConsistentVertexesCalculator.h"
#include "MuJetAnalysis/AnalysisTools/src/ConsistentVertexesCalculator.cc"

#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

//#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/PatCandidates/interface/TriggerEvent.h"

using namespace std;

//
// class declaration
//


double cotan(double i) { return(1 / tan(i)); }

bool PtOrderGen (const reco::GenParticle* p1, const reco::GenParticle* p2) { return (p1->pt() > p2->pt() ); }
bool PtOrder (const reco::Muon* p1, const reco::Muon* p2) { return (p1->pt() > p2->pt() ); }
bool dRorder(const std::pair<Int_t,Float_t>  &v1, const std::pair<Int_t,Float_t> &v2) { return (v1.second < v2.second ); }
bool matchorder(const std::pair<Int_t,Float_t>  &v1, const std::pair<Int_t,Float_t> &v2) { return (abs(v1.second) < abs(v2.second) ); }
bool order(Float_t v1, Float_t v2){ return (abs(v1)<abs(v2));}


double My_dPhi (double phi1, double phi2) {
  double dPhi = phi1 - phi2;
  if (dPhi >  M_PI) dPhi -= 2.*M_PI;
  if (dPhi < -M_PI) dPhi += 2.*M_PI;
  return dPhi;
}

bool sameTrack(const reco::Track *one, const reco::Track *two) {
  return (fabs(one->px() - two->px()) < 1e-10  &&
	  fabs(one->py() - two->py()) < 1e-10  &&
	  fabs(one->pz() - two->pz()) < 1e-10  &&
	  fabs(one->vx() - two->vx()) < 1e-10  &&
	  fabs(one->vy() - two->vy()) < 1e-10  &&
	  fabs(one->vz() - two->vz()) < 1e-10);
}


// Refitted Track with slightly different pT than general Tracks. 
// better using 1/pT, vertex and angular variables

// bool sameTrackRF(const reco::Track *one, const reco::Track *two) {
//   return ( fabs( 1/(one->pt()) - 1/(two->pt()) ) < 1e-6  ||       
// 	   (fabs(one->vx() - two->vx()) < 1e-6  &&
// 	    fabs(one->vy() - two->vy()) < 1e-6  &&
// 	    fabs(one->vz() - two->vz()) < 1e-6 ) || 
// 	   fabs(one->eta() - two->eta()) <1e-6);
// }



bool sameTrackRF(const reco::Track *one, const reco::Track *two) {
  return ( fabs( one->charge() - two->charge())==0 && 
	   fabs( cotan(one->theta()) - cotan(two->theta()) ) < 0.02  &&
	   fabs( (1/one->pt()) - (1/two->pt()) ) < 0.02  &&
	   fabs( one->phi() - two->phi() ) < 0.02  &&
	   fabs( one->dxy() - two->dxy() ) < 0.1  && 
	   fabs( one->dz() - two->dz() ) < 0.1);
}



//
// class declaration
//

class AnalysisRun2 : public edm::EDAnalyzer {
public:
  explicit AnalysisRun2(const edm::ParameterSet&);
  ~AnalysisRun2();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;



  Int_t nevents=0;
  
  // ----------member data ---------------------------
  edm::ParameterSet param_;

  edm::InputTag m_muJets; // muon jets built from reconstructed muons
  edm::InputTag m_muons;  // reconstructed PAT muons

  edm::EDGetTokenT<MeasurementTrackerEvent> measurementTrkToken_;

  Float_t m_threshold_DiMuons_dz;

  Float_t m_threshold_DiMuons_Iso;
  Float_t m_threshold_DiMuons_Iso_dR;  
  Float_t m_threshold_DiMuons_Iso_dz;
  Float_t m_threshold_DiMuons_Iso_pT;

  bool m_fillGenLevel; // TRUE for simulation, FALSE for data

  Float_t m_threshold_Mu_HighpT_pT;
  Float_t m_threshold_Mu_HighpT_Eta;
  Float_t m_threshold_Mu_pT;
  Float_t m_threshold_Mu_Eta;

  TRandom3 m_trandom3;


  Int_t b_is1GenMu17;
  Int_t b_is2GenMu8;
  Int_t b_is3GenMu8;
  Int_t b_is4GenMu8;


  Float_t b_genA0Mu0_vx_rorig;
  Float_t b_genA0Mu1_vx_rorig;
  Float_t b_genA1Mu0_vx_rorig;
  Float_t b_genA1Mu1_vx_rorig;
  Float_t b_genA0Mu0_vy_rorig;
  Float_t b_genA0Mu1_vy_rorig;
  Float_t b_genA1Mu0_vy_rorig;
  Float_t b_genA1Mu1_vy_rorig;
  Float_t b_genA0Mu0_vz_rorig;
  Float_t b_genA0Mu1_vz_rorig;
  Float_t b_genA1Mu0_vz_rorig;
  Float_t b_genA1Mu1_vz_rorig;

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
  
  Float_t b_genA0_pt;
  Float_t b_genA1_pt;

  Float_t b_genA0_eta;
  Float_t b_genA1_eta;

  Float_t b_genA0_phi;
  Float_t b_genA1_phi;


  Float_t b_genA0_vx_rorig;
  Float_t b_genA0_vy_rorig;
  Float_t b_genA0_vz_rorig;
  
  Float_t b_genA1_vx_rorig;
  Float_t b_genA1_vy_rorig;
  Float_t b_genA1_vz_rorig;


  Float_t b_genA0_Lz_rdet;
  Float_t b_genA0_Lxy_rdet;
  Float_t b_genA1_Lz_rdet;
  Float_t b_genA1_Lxy_rdet;



  Bool_t b_is2MuJets;
  
  Int_t m_debug;
  Int_t m_antraj;
  TTree * m_ttree;  // Store variables in branches of this tree for later access           
  Int_t b_event;
  Int_t b_nevent;
  Int_t b_run;
  Int_t b_lumi;
  Int_t b_nJob;

  Float_t b_beamSpot_x;
  Float_t b_beamSpot_y;
  Float_t b_beamSpot_z;


  Int_t b_nrecm;
  Int_t b_npatm;

  Int_t b_nmjets;

  Int_t b_is1SelMu17;
  Int_t b_is2SelMu8;
  Int_t b_is3SelMu8;
  Int_t b_is4SelMu8;

  Float_t b_selMu0_phi;
  Float_t b_selMu1_phi;
  Float_t b_selMu2_phi;
  Float_t b_selMu3_phi;

  Float_t b_selMu0_eta;
  Float_t b_selMu1_eta;
  Float_t b_selMu2_eta;
  Float_t b_selMu3_eta;

  
  Int_t b_4recm;
  Int_t b_2mjets;
  Int_t b_2dimuon;

  Int_t b_ntracks;

  Float_t b_diMuons_dz;
  Float_t b_diMuonC_IsoTk;
  Float_t b_diMuonF_IsoTk;

  Float_t b_diMuonC_Mass;
  Float_t b_diMuonF_Mass;

  Bool_t b_is2DiMuonsVtxOK;
  Bool_t b_is2DiMuonsDzOK;
  Bool_t b_isDiMuonHLTFired;
  Bool_t b_is2DiMuonsMassOK;
  Bool_t b_is2DiMuonsIsoTkOK;
  Bool_t b_isVertexOK;

  Int_t b_numvtx;
  Int_t b_numvtxbc;

  Int_t b_match_mu1track_muJetC;
  Int_t b_match_mu2track_muJetC;
  Int_t b_match_mu1track_muJetF;
  Int_t b_match_mu2track_muJetF;

  Int_t b_muJetC_hitpix[2];
  Int_t b_muJetF_hitpix[2];

  Int_t b_muJetC_hitpix_2ndlay[2];
  Int_t b_muJetF_hitpix_2ndlay[2];

  Int_t b_muJetC_hitpix_3rdlay[2];
  Int_t b_muJetF_hitpix_3rdlay[2];

  Float_t HiggsPt;

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



  Int_t b_muJetC_hitpix_genTrk[2];
  Int_t b_muJetF_hitpix_genTrk[2];

  Int_t b_muJetC_hitpix_2ndlay_genTrk[2];
  Int_t b_muJetF_hitpix_2ndlay_genTrk[2];

  Int_t b_muJetC_hitpix_3rdlay_genTrk[2];
  Int_t b_muJetF_hitpix_3rdlay_genTrk[2];

  Bool_t muJetC_validVtx;
  Bool_t muJetC_validVtx_fitted;
  Bool_t muJetC_validVtx_mindist;

  Bool_t muJetF_validVtx;
  Bool_t muJetF_validVtx_fitted;
  Bool_t muJetF_validVtx_mindist;

  Float_t muJetC_vtx_x;
  Float_t muJetC_vtx_y;
  Float_t muJetC_vtx_z;

  Float_t muJetF_vtx_x;
  Float_t muJetF_vtx_y;
  Float_t muJetF_vtx_z;

  Float_t muJetC_mindisttracks;
  Float_t muJetF_mindisttracks;

  Float_t muJetC_mindisttracks_scan;
  Float_t muJetF_mindisttracks_scan;

  Float_t muJetC_vtx_x_scan;
  Float_t muJetC_vtx_y_scan;
  Float_t muJetC_vtx_z_scan;

  Float_t muJetF_vtx_x_scan;
  Float_t muJetF_vtx_y_scan;
  Float_t muJetF_vtx_z_scan;

  Float_t muJetC_cpx;
  Float_t muJetC_cpy;
  Float_t muJetC_cpz;

  Float_t muJetF_cpx;
  Float_t muJetF_cpy;
  Float_t muJetF_cpz;


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


  Float_t b_errposx_inlay_mu1_muJetC;
  Float_t b_errposx_inlay_mu2_muJetC;
  Float_t b_errposx_inlay_mu1_muJetF;
  Float_t b_errposx_inlay_mu2_muJetF;

  Float_t b_errposy_inlay_mu1_muJetC;
  Float_t b_errposy_inlay_mu2_muJetC;
  Float_t b_errposy_inlay_mu1_muJetF;
  Float_t b_errposy_inlay_mu2_muJetF;

  Int_t b_muJetC_hitpix_gt[2];
  Int_t b_muJetF_hitpix_gt[2];

  Int_t b_innerlayers_mu1_muJetC;
  Int_t b_innerlayers_mu2_muJetC;
  Int_t b_innerlayers_mu1_muJetF;
  Int_t b_innerlayers_mu2_muJetF;

  Int_t b_comphits_mu1_muJetC;
  Int_t b_comphits_mu1_muJetF;
  Int_t b_comphits_mu2_muJetC;
  Int_t b_comphits_mu2_muJetF;

  Int_t b_Det_mu1_muJetC;
  Int_t b_Det_mu2_muJetC;
  Int_t b_Det_mu1_muJetF;
  Int_t b_Det_mu2_muJetF;


  Float_t b_muJetC_trackdist_1stpixel;
  Float_t b_muJetF_trackdist_1stpixel;


  Int_t b_muJetC_muon1_layerB[200];
  Int_t b_muJetC_muon2_layerB[200];
  Int_t b_muJetF_muon1_layerB[200];
  Int_t b_muJetF_muon2_layerB[200];

  Int_t b_muJetC_muon1_layerF[200];
  Int_t b_muJetC_muon2_layerF[200];
  Int_t b_muJetF_muon1_layerF[200];
  Int_t b_muJetF_muon2_layerF[200];

  Float_t b_muJetC_muon1_posx1stpix[200];
  Float_t b_muJetC_muon1_posy1stpix[200];
  Float_t b_muJetC_muon1_posz1stpix[200];

  Float_t b_muJetC_muon2_posx1stpix[200];
  Float_t b_muJetC_muon2_posy1stpix[200];
  Float_t b_muJetC_muon2_posz1stpix[200];

  Float_t b_muJetF_muon1_posx1stpix[200];
  Float_t b_muJetF_muon1_posy1stpix[200];
  Float_t b_muJetF_muon1_posz1stpix[200];

  Float_t b_muJetF_muon2_posx1stpix[200];
  Float_t b_muJetF_muon2_posy1stpix[200];
  Float_t b_muJetF_muon2_posz1stpix[200];


  Float_t b_muJetC_muon1_errposx1stpix[200];
  Float_t b_muJetC_muon1_errposy1stpix[200];
  Float_t b_muJetC_muon1_errposz1stpix[200];

  Float_t b_muJetC_muon2_errposx1stpix[200];
  Float_t b_muJetC_muon2_errposy1stpix[200];
  Float_t b_muJetC_muon2_errposz1stpix[200];

  Float_t b_muJetF_muon1_errposx1stpix[200];
  Float_t b_muJetF_muon1_errposy1stpix[200];
  Float_t b_muJetF_muon1_errposz1stpix[200];

  Float_t b_muJetF_muon2_errposx1stpix[200];
  Float_t b_muJetF_muon2_errposy1stpix[200];
  Float_t b_muJetF_muon2_errposz1stpix[200];


  Float_t b_muJetC_muon1_posx1stpix_lastmeas[200];
  Float_t b_muJetC_muon1_posy1stpix_lastmeas[200];

  Float_t b_muJetC_muon2_posx1stpix_lastmeas[200];
  Float_t b_muJetC_muon2_posy1stpix_lastmeas[200];

  Float_t b_muJetF_muon1_posx1stpix_lastmeas[200];
  Float_t b_muJetF_muon1_posy1stpix_lastmeas[200];

  Float_t b_muJetF_muon2_posx1stpix_lastmeas[200];
  Float_t b_muJetF_muon2_posy1stpix_lastmeas[200];


  Float_t b_mindist_hit_mu1_muJetC[200];
  Float_t b_mindist_hit_mu2_muJetC[200];
  Float_t b_mindist_hit_mu1_muJetF[200];
  Float_t b_mindist_hit_mu2_muJetF[200];
  
  Float_t b_dist_muon_muJetC;
  Float_t b_dist_muon_muJetF;

  Float_t b_pixelhit_mu1_muJetC_posx[200];
  Float_t b_pixelhit_mu1_muJetC_posy[200];
  Float_t b_pixelhit_mu1_muJetC_posz[200];

  Float_t b_pixelhit_mu2_muJetC_posx[200];
  Float_t b_pixelhit_mu2_muJetC_posy[200];
  Float_t b_pixelhit_mu2_muJetC_posz[200];

  Float_t b_pixelhit_mu1_muJetF_posx[200];
  Float_t b_pixelhit_mu1_muJetF_posy[200];
  Float_t b_pixelhit_mu1_muJetF_posz[200];

  Float_t b_pixelhit_mu2_muJetF_posx[200];
  Float_t b_pixelhit_mu2_muJetF_posy[200];
  Float_t b_pixelhit_mu2_muJetF_posz[200];


  Float_t b_pixelhit_mu1_muJetC_errposx[200];
  Float_t b_pixelhit_mu1_muJetC_errposy[200];
  Float_t b_pixelhit_mu1_muJetC_errposz[200];

  Float_t b_pixelhit_mu2_muJetC_errposx[200];
  Float_t b_pixelhit_mu2_muJetC_errposy[200];
  Float_t b_pixelhit_mu2_muJetC_errposz[200];

  Float_t b_pixelhit_mu1_muJetF_errposx[200];
  Float_t b_pixelhit_mu1_muJetF_errposy[200];
  Float_t b_pixelhit_mu1_muJetF_errposz[200];

  Float_t b_pixelhit_mu2_muJetF_errposx[200];
  Float_t b_pixelhit_mu2_muJetF_errposy[200];
  Float_t b_pixelhit_mu2_muJetF_errposz[200];


  Int_t b_hitrecover_mj2_r001;
  Int_t b_hitrecover_mj2_r005;
  Int_t b_hitrecover_mj2_r01;
  Int_t b_hitrecover_mj2_r03;
  Int_t b_hitrecover_mj2_r05;
  Int_t b_hitrecover_mj2_r1;

  Int_t b_hitrecover_mj1_r001;
  Int_t b_hitrecover_mj1_r005;
  Int_t b_hitrecover_mj1_r01;
  Int_t b_hitrecover_mj1_r03;
  Int_t b_hitrecover_mj1_r05;
  Int_t b_hitrecover_mj1_r1;

  Int_t b_hitrecover_mj12_r001;
  Int_t b_hitrecover_mj12_r005;
  Int_t b_hitrecover_mj12_r01;
  Int_t b_hitrecover_mj12_r03;
  Int_t b_hitrecover_mj12_r05;
  Int_t b_hitrecover_mj12_r1;


  std::vector<std::string> hltPaths_;
  std::vector<std::string> b_hltPaths;


  
  //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
  //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
  //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
  //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

  // ----------member data ---------------------------
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
AnalysisRun2::AnalysisRun2(const edm::ParameterSet& iConfig)

{
  param_ = iConfig;

  hltPaths_ = iConfig.getParameter<std::vector<std::string> >("hltPaths");

  m_muJets = iConfig.getParameter<edm::InputTag>("muJets");
  m_muons = iConfig.getParameter<edm::InputTag>("muons");
  
  measurementTrkToken_ = consumes<MeasurementTrackerEvent>(iConfig.getParameter<edm::InputTag>("MeasurementTrackerEvent"));

  // edm::Service<TFileService> tFileService;
  // h_mj1_dm1m2 = tFileService->make<TH1F>( "h_mj1_dm1m2"  , "h_mj1_dm1m2", 100,  0., 0.4);

  m_threshold_DiMuons_Iso = 2.0;

  m_threshold_DiMuons_dz = 0.1; //
  m_threshold_DiMuons_Iso_dR = 0.4; // Isolation cone
  m_threshold_DiMuons_Iso_dz = 0.1; // Track displacement [cm]
  m_threshold_DiMuons_Iso_pT = 0.5; // Track pT [GeV]

  b_ntracks=0;


  m_threshold_Mu_HighpT_pT  = iConfig.getParameter<double>("highpT_muon_pT"); // min pT in GeV
  m_threshold_Mu_HighpT_Eta =  iConfig.getParameter<double>("highpT_muon_eta"); // max eta in Barrel
  m_threshold_Mu_pT   =  iConfig.getParameter<double>("muon_pT"); // min pT in GeV
  m_threshold_Mu_Eta  =  iConfig.getParameter<double>("muon_eta"); // max eta in Endcaps

  m_fillGenLevel = iConfig.getParameter<bool>("fillGenLevel");

  m_debug = iConfig.getParameter<int>("analyzerDebug");
  m_antraj = iConfig.getParameter<int>("analyzerTraj");
  b_nJob = iConfig.getParameter<int>("nJob");
  m_ttree  = NULL;

  b_nrecm = 0;
  b_npatm = 0;
  b_nmjets = 0;

  //now do what ever initialization is needed

}


AnalysisRun2::~AnalysisRun2()
{
 
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
AnalysisRun2::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;

  b_is1GenMu17=0;
  b_is2GenMu8=0;
  b_is3GenMu8=0;
  b_is4GenMu8=0;

  b_is1SelMu17=0;
  b_is2SelMu8=0;
  b_is3SelMu8=0;
  b_is4SelMu8=0;

  HiggsPt=0.;



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



  muJetC_mindisttracks=-100000.;
  muJetF_mindisttracks=-100000.;

  muJetC_mindisttracks_scan=-100000.;
  muJetF_mindisttracks_scan=-100000.;

  muJetC_vtx_x_scan=-100000.;
  muJetC_vtx_y_scan=-100000.;
  muJetC_vtx_z_scan=-100000.;


  muJetF_vtx_x_scan=-100000.;
  muJetF_vtx_y_scan=-100000.;
  muJetF_vtx_z_scan=-100000.;


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

  b_errposx_inlay_mu1_muJetC=0.;
  b_errposx_inlay_mu2_muJetC=0.;
  b_errposx_inlay_mu1_muJetF=0.;
  b_errposx_inlay_mu2_muJetF=0.;

  b_errposy_inlay_mu1_muJetC=0.;
  b_errposy_inlay_mu2_muJetC=0.;
  b_errposy_inlay_mu1_muJetF=0.;
  b_errposy_inlay_mu2_muJetF=0.;

  b_muJetC_trackdist_1stpixel=-10000;
  b_muJetF_trackdist_1stpixel=-10000;

  for(int k=0;k<2;k++) b_muJetC_hitpix[k]=-100000;
  for(int k=0;k<2;k++) b_muJetF_hitpix[k]=-100000;

  for(int k=0;k<2;k++) b_muJetC_hitpix_2ndlay[k]=-100000;
  for(int k=0;k<2;k++) b_muJetF_hitpix_2ndlay[k]=-100000;

  for(int k=0;k<2;k++) b_muJetC_hitpix_3rdlay[k]=-100000;
  for(int k=0;k<2;k++) b_muJetF_hitpix_3rdlay[k]=-100000;

  for(int k=0;k<2;k++) b_muJetC_hitpix_genTrk[k]=-100000;
  for(int k=0;k<2;k++) b_muJetF_hitpix_genTrk[k]=-100000;

  for(int k=0;k<2;k++) b_muJetC_hitpix_2ndlay_genTrk[k]=-100000;
  for(int k=0;k<2;k++) b_muJetF_hitpix_2ndlay_genTrk[k]=-100000;

  for(int k=0;k<2;k++) b_muJetC_hitpix_3rdlay_genTrk[k]=-100000;
  for(int k=0;k<2;k++) b_muJetF_hitpix_3rdlay_genTrk[k]=-100000;

  for(int k=0;k<200;k++) b_mindist_hit_mu1_muJetC[k]=-10000;
  for(int k=0;k<200;k++) b_mindist_hit_mu2_muJetC[k]=-10000;
  for(int k=0;k<200;k++) b_mindist_hit_mu1_muJetF[k]=-10000;
  for(int k=0;k<200;k++) b_mindist_hit_mu2_muJetF[k]=-10000;

  for(int k=0;k<200;k++) b_muJetC_muon1_layerB[k]=-100000.;
  for(int k=0;k<200;k++) b_muJetC_muon2_layerB[k]=-100000.;
  for(int k=0;k<200;k++) b_muJetF_muon1_layerB[k]=-100000.;
  for(int k=0;k<200;k++) b_muJetF_muon2_layerB[k]=-100000.;

  for(int k=0;k<200;k++) b_muJetC_muon1_layerF[k]=-100000.;
  for(int k=0;k<200;k++) b_muJetC_muon2_layerF[k]=-100000.;
  for(int k=0;k<200;k++) b_muJetF_muon1_layerF[k]=-100000.;
  for(int k=0;k<200;k++) b_muJetF_muon2_layerF[k]=-100000.;
  

  for(int k=0;k<200;k++) b_muJetC_muon1_posx1stpix[k]=-100000.;
  for(int k=0;k<200;k++) b_muJetC_muon1_posy1stpix[k]=-100000.;
  for(int k=0;k<200;k++) b_muJetC_muon1_posz1stpix[k]=-100000.;

  for(int k=0;k<200;k++) b_muJetC_muon2_posx1stpix[k]=-100000.;
  for(int k=0;k<200;k++) b_muJetC_muon2_posy1stpix[k]=-100000.;
  for(int k=0;k<200;k++) b_muJetC_muon2_posz1stpix[k]=-100000.;

  for(int k=0;k<200;k++) b_muJetF_muon1_posx1stpix[k]=-100000.;
  for(int k=0;k<200;k++) b_muJetF_muon1_posy1stpix[k]=-100000.;
  for(int k=0;k<200;k++) b_muJetF_muon1_posz1stpix[k]=-100000.;

  for(int k=0;k<200;k++) b_muJetF_muon2_posx1stpix[k]=-100000.;
  for(int k=0;k<200;k++) b_muJetF_muon2_posy1stpix[k]=-100000.;
  for(int k=0;k<200;k++) b_muJetF_muon2_posz1stpix[k]=-100000.;


  for(int k=0;k<200;k++) b_muJetC_muon1_errposx1stpix[k]=-100000.;
  for(int k=0;k<200;k++) b_muJetC_muon1_errposy1stpix[k]=-100000.;
  for(int k=0;k<200;k++) b_muJetC_muon1_errposz1stpix[k]=-100000.;

  for(int k=0;k<200;k++) b_muJetC_muon2_errposx1stpix[k]=-100000.;
  for(int k=0;k<200;k++) b_muJetC_muon2_errposy1stpix[k]=-100000.;
  for(int k=0;k<200;k++) b_muJetC_muon2_errposz1stpix[k]=-100000.;

  for(int k=0;k<200;k++) b_muJetF_muon1_errposx1stpix[k]=-100000.;
  for(int k=0;k<200;k++) b_muJetF_muon1_errposy1stpix[k]=-100000.;
  for(int k=0;k<200;k++) b_muJetF_muon1_errposz1stpix[k]=-100000.;

  for(int k=0;k<200;k++) b_muJetF_muon2_errposx1stpix[k]=-100000.;
  for(int k=0;k<200;k++) b_muJetF_muon2_errposy1stpix[k]=-100000.;
  for(int k=0;k<200;k++) b_muJetF_muon2_errposz1stpix[k]=-100000.;


  for(int k=0;k<200;k++) b_muJetC_muon1_posx1stpix_lastmeas[k]=-100000.;
  for(int k=0;k<200;k++) b_muJetC_muon1_posy1stpix_lastmeas[k]=-100000.;

  for(int k=0;k<200;k++) b_muJetC_muon2_posx1stpix_lastmeas[k]=-100000.;
  for(int k=0;k<200;k++) b_muJetC_muon2_posy1stpix_lastmeas[k]=-100000.;

  for(int k=0;k<200;k++) b_muJetF_muon1_posx1stpix_lastmeas[k]=-100000.;
  for(int k=0;k<200;k++) b_muJetF_muon1_posy1stpix_lastmeas[k]=-100000.;

  for(int k=0;k<200;k++) b_muJetF_muon2_posx1stpix_lastmeas[k]=-100000.;
  for(int k=0;k<200;k++) b_muJetF_muon2_posy1stpix_lastmeas[k]=-100000.;


  b_dist_muon_muJetC = -100000;
  b_dist_muon_muJetF = -100000;


  muJetC_vtx_x = -10000;
  muJetC_vtx_y = -10000;
  muJetC_vtx_z = -10000;


  muJetF_vtx_x = -10000;
  muJetF_vtx_y = -10000;
  muJetF_vtx_z = -10000;

  for(int k=0;k<200;k++) b_pixelhit_mu1_muJetC_posx[k]=-100000.0;
  for(int k=0;k<200;k++) b_pixelhit_mu1_muJetC_posy[k]=-100000.0;
  for(int k=0;k<200;k++) b_pixelhit_mu1_muJetC_posz[k]=-100000.0;

  for(int k=0;k<200;k++) b_pixelhit_mu2_muJetC_posx[k]=-100000.0;
  for(int k=0;k<200;k++) b_pixelhit_mu2_muJetC_posy[k]=-100000.0;
  for(int k=0;k<200;k++) b_pixelhit_mu2_muJetC_posz[k]=-100000.0;

  for(int k=0;k<200;k++) b_pixelhit_mu1_muJetF_posx[k]=-100000.0;
  for(int k=0;k<200;k++) b_pixelhit_mu1_muJetF_posy[k]=-100000.0;
  for(int k=0;k<200;k++) b_pixelhit_mu1_muJetF_posz[k]=-100000.0;

  for(int k=0;k<200;k++) b_pixelhit_mu2_muJetF_posx[k]=-100000.0;
  for(int k=0;k<200;k++) b_pixelhit_mu2_muJetF_posy[k]=-100000.0;
  for(int k=0;k<200;k++) b_pixelhit_mu2_muJetF_posz[k]=-100000.0;


  for(int k=0;k<200;k++) b_pixelhit_mu1_muJetC_errposx[k]=-100000.0;
  for(int k=0;k<200;k++) b_pixelhit_mu1_muJetC_errposy[k]=-100000.0;
  for(int k=0;k<200;k++) b_pixelhit_mu1_muJetC_errposz[k]=-100000.0;

  for(int k=0;k<200;k++) b_pixelhit_mu2_muJetC_errposx[k]=-100000.0;
  for(int k=0;k<200;k++) b_pixelhit_mu2_muJetC_errposy[k]=-100000.0;
  for(int k=0;k<200;k++) b_pixelhit_mu2_muJetC_errposz[k]=-100000.0;

  for(int k=0;k<200;k++) b_pixelhit_mu1_muJetF_errposx[k]=-100000.0;
  for(int k=0;k<200;k++) b_pixelhit_mu1_muJetF_errposy[k]=-100000.0;
  for(int k=0;k<200;k++) b_pixelhit_mu1_muJetF_errposz[k]=-100000.0;

  for(int k=0;k<200;k++) b_pixelhit_mu2_muJetF_errposx[k]=-100000.0;
  for(int k=0;k<200;k++) b_pixelhit_mu2_muJetF_errposy[k]=-100000.0;
  for(int k=0;k<200;k++) b_pixelhit_mu2_muJetF_errposz[k]=-100000.0;


  b_Det_mu1_muJetC = 0;
  b_Det_mu2_muJetC = 0;
  b_Det_mu1_muJetF = 0;
  b_Det_mu2_muJetF = 0;
  
  b_innerlayers_mu1_muJetC = 0;
  b_innerlayers_mu2_muJetC = 0;
  b_innerlayers_mu1_muJetF = 0;
  b_innerlayers_mu2_muJetF = 0;

  b_comphits_mu1_muJetC = 0;
  b_comphits_mu2_muJetC = 0;
  b_comphits_mu1_muJetF = 0;
  b_comphits_mu2_muJetF = 0;
  

  b_hitrecover_mj2_r001=0;
  b_hitrecover_mj2_r005=0;
  b_hitrecover_mj2_r01=0;
  b_hitrecover_mj2_r03=0;
  b_hitrecover_mj2_r05=0;
  b_hitrecover_mj2_r1=0;

  b_hitrecover_mj1_r001=0;
  b_hitrecover_mj1_r005=0;
  b_hitrecover_mj1_r01=0;
  b_hitrecover_mj1_r03=0;
  b_hitrecover_mj1_r05=0;
  b_hitrecover_mj1_r1=0;

  b_hitrecover_mj12_r001=0;
  b_hitrecover_mj12_r005=0;
  b_hitrecover_mj12_r01=0;
  b_hitrecover_mj12_r03=0;
  b_hitrecover_mj12_r05=0;
  b_hitrecover_mj12_r1=0;

  b_4recm=0;
  b_2mjets=0;
  b_2dimuon=0;

  b_is1SelMu17 = 0;
  b_is2SelMu8 = 0;
  b_is3SelMu8 = 0;
  b_is4SelMu8 = 0;


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
  double eq = 0.000001; // small number used below to compare variables

  if (m_fillGenLevel){  
    

    edm::Handle<reco::GenParticleCollection> genParticles;
    iEvent.getByLabel("genParticles", genParticles);
  
    // Loop over all genParticles and save prompt muons from particles with codes 36 (a1) or 3000022 (gammaD) in vector genMuons
    std::vector<const reco::GenParticle*> genH;
    std::vector<const reco::GenParticle*> genA_unsorted;
    std::vector<const reco::GenParticle*> genA;
    std::vector<const reco::GenParticle*> genMuons;
    std::vector<const reco::Candidate*>   genMuonMothers;

    //    Loop over all gen particles
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
	  if ( genMuonCand->mother(iMother)->pdgId() == 36 || genMuonCand->mother(iMother)->pdgId() == 3000022 || genMuonCand->mother(iMother)->pdgId() == 443 ) {
	    //	        if ( genMuonCand->mother(iMother)->pdgId() == 36 || genMuonCand->mother(iMother)->pdgId() == 3000022 ) {
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
	HiggsPt = iGenParticle->pt();
      }
      // Check if gen particle is
      if (    ( iGenParticle->status() == 22 && iGenParticle->pdgId() == 36      ) // decaying (status = 3) CP-odd Higgs (pdgId = 36)
    	      || ( iGenParticle->status() == 22 && iGenParticle->pdgId() == 3000022 ) // decaying (status = 3) gamma_Dark (pdgId = 3000022)
    	      || ( iGenParticle->status() == 2 && iGenParticle->pdgId() == 443   ) // decaying (status = 2) J/psi (pdgId = 443)
    	      ) {
	genA_unsorted.push_back(&(*iGenParticle));
	std::cout<<"   Dark Photon foundedn with  ID "<<iGenParticle->pdgId()<<" and status:   "<<iGenParticle->status()<<std::endl;
      }
    }
  
    if ( genA_unsorted.size() >= 2 ) {
      // Sort genA by pT (leading pT first)
      std::sort (genA_unsorted.begin(), genA_unsorted.end(), PtOrderGen);
    }
  
    genA = genA_unsorted;
    if ( genA.size() >= 2 ) {
      
      b_genA0_pt = genA[0]->pt();
      b_genA1_pt = genA[1]->pt();

      b_genA0_eta = genA[0]->eta();
      b_genA1_eta = genA[1]->eta();

      b_genA0_phi = genA[0]->phi();
      b_genA1_phi = genA[1]->phi();


      b_genA0_vx_rorig  = genA[0]->vx();
      b_genA0_vy_rorig  = genA[0]->vy();
      b_genA0_vz_rorig  = genA[0]->vz();
    
      b_genA1_vx_rorig  = genA[1]->vx();
      b_genA1_vy_rorig  = genA[1]->vy();
      b_genA1_vz_rorig  = genA[1]->vz();
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
      std::sort( genMuonGroups[0].begin(), genMuonGroups[0].end(), PtOrderGen );
      std::sort( genMuonGroups[1].begin(), genMuonGroups[1].end(), PtOrderGen );


      b_genA0Mu0_vx_rorig = genMuonGroups[0][0]->vx(); 
      b_genA0Mu1_vx_rorig = genMuonGroups[0][1]->vx();
      b_genA1Mu0_vx_rorig = genMuonGroups[1][0]->vx();
      b_genA1Mu1_vx_rorig = genMuonGroups[1][1]->vx(); 

      b_genA0Mu0_vy_rorig = genMuonGroups[0][0]->vy(); 
      b_genA0Mu1_vy_rorig = genMuonGroups[0][1]->vy(); 
      b_genA1Mu0_vy_rorig = genMuonGroups[1][0]->vy(); 
      b_genA1Mu1_vy_rorig = genMuonGroups[1][1]->vy(); 
    
      b_genA0Mu0_vz_rorig = genMuonGroups[0][0]->vz(); 
      b_genA0Mu1_vz_rorig = genMuonGroups[0][1]->vz(); 
      b_genA1Mu0_vz_rorig = genMuonGroups[1][0]->vz(); 
      b_genA1Mu1_vz_rorig = genMuonGroups[1][1]->vz(); 

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



      
      if (    fabs(b_genA0Mu0_vx_rorig - b_genA0Mu1_vx_rorig) < eq
    	      && fabs(b_genA1Mu0_vx_rorig - b_genA1Mu1_vx_rorig) < eq
    	      && fabs(b_genA0Mu0_vy_rorig - b_genA0Mu1_vy_rorig) < eq
    	      && fabs(b_genA1Mu0_vy_rorig - b_genA1Mu1_vy_rorig) < eq
    	      && fabs(b_genA0Mu0_vz_rorig - b_genA0Mu1_vz_rorig) < eq
    	      && fabs(b_genA1Mu0_vz_rorig - b_genA1Mu1_vz_rorig) < eq
    	      ) {

    	b_genA0_Lz_rdet = b_genA0Mu0_vz_rorig;
    	b_genA1_Lz_rdet = b_genA1Mu0_vz_rorig;
            
    	b_genA0_Lxy_rdet = sqrt( b_genA0Mu0_vx_rorig * b_genA0Mu0_vx_rorig + b_genA0Mu0_vy_rorig * b_genA0Mu0_vy_rorig );
    	b_genA1_Lxy_rdet = sqrt( b_genA1Mu0_vx_rorig * b_genA1Mu0_vx_rorig + b_genA1Mu0_vy_rorig * b_genA1Mu0_vy_rorig );

      }
    }


  
    // Sort genMuons by pT (leading pT first)
    if ( genMuons.size() > 1 ) std::sort( genMuons.begin(), genMuons.end(), PtOrderGen );
  
    std::vector<const reco::GenParticle*> genMuons17;
    std::vector<const reco::GenParticle*> genMuons8;
  
    for ( unsigned int i = 0; i < genMuons.size(); i++ ) {
      if ( genMuons[i]->pt() > m_threshold_Mu_HighpT_pT && fabs( genMuons[i]->eta() ) < m_threshold_Mu_HighpT_Eta ) {
    	//      if ( genMuons[i]->pt() > m_threshold_Mu17_pT ) {
        genMuons17.push_back(genMuons[i]);
      }
      if ( genMuons[i]->pt() > m_threshold_Mu_pT && fabs( genMuons[i]->eta() ) < m_threshold_Mu_Eta ) {
    	//      if ( genMuons[i]->pt() > m_threshold_Mu8_pT ) {
        genMuons8.push_back(genMuons[i]);
      }
    }

    if ( genMuons17.size() >=1) {
      b_is1GenMu17 = true;
      if ( genMuons8.size() >=2 ) {
        b_is2GenMu8 = true;
      }
      if ( genMuons8.size() >=3 ) {
        b_is3GenMu8 = true;
      }
      if ( genMuons8.size() >=4 ) {
        b_is4GenMu8 = true;
      }
    }
  
  }
  
  //****************************************************************************
  //                          GEN LEVEL ANALYSIS FINISH                         
  //****************************************************************************


  //============================================================================================//

  //  if(iEvent.id().event()==5613){  // Analyzing specific event
  
  nevents++;

  b_event = iEvent.id().event();
  b_nevent = nevents;
  b_run   = iEvent.id().run();
  b_lumi  = iEvent.id().luminosityBlock();


  //  if (b_event == 159896605) m_debug = 100;
  if(m_debug>10) std::cout<<"  Event :    "<<iEvent.id().event()<<std::endl;
  if(m_debug>10) std::cout<<"  nJob*10000+nevent (MC) :    "<<b_nJob*10000+nevents<<std::endl;
  if(m_debug>10) std::cout<<"  Lumi  :    "<<iEvent.id().luminosityBlock()<<std::endl;
  
  edm::Handle<reco::MuonCollection> muons;
  iEvent.getByLabel("muons",muons);
  
  edm::Handle<pat::MuonCollection> patmuons;
  iEvent.getByLabel(m_muons, patmuons);
  
  Bool_t is4recm=false;  // Flag for events with 4rec muons with pt and eta cuts
  
  Int_t countrm=0;
  Int_t countrm_hpt=0;
  
  std::vector<const reco::Muon*> selrecoMuons;
  std::vector<const reco::Muon*> selpatMuons;
  
  // std::cout<<"    RECO muon size     "<<muons->size()<<std::endl;
  // std::cout<<"    PAT  muon size     "<<patmuons->size()<<std::endl;
  

  if(m_antraj==1){
    for (reco::MuonCollection::const_iterator iMuon = muons->begin();  iMuon != muons->end();  ++iMuon) {
      
      if( iMuon->isPFMuon() && ( iMuon->isTrackerMuon() || iMuon->isGlobalMuon() ) ){
	
	//std::cout<<" muon eta      "<<iMuon->eta()<<"  muon pt   "<<iMuon->pt()<<std::endl;
	if( fabs(iMuon->eta()) < m_threshold_Mu_Eta && iMuon->pt()> m_threshold_Mu_pT) selrecoMuons.push_back( &(*iMuon) );
	//     if( fabs(iMuon->eta()) < 0.9 && iMuon->pt()>17.0) countrm_hpt++;
      }
    }
    if(selrecoMuons.size()>1) std::sort(selrecoMuons.begin(),selrecoMuons.end(),PtOrder);
    b_nrecm = selrecoMuons.size();
  }

  for(pat::MuonCollection::const_iterator iMuon = patmuons->begin();  iMuon != patmuons->end();  ++iMuon) {
    
    if( iMuon->isPFMuon() && ( iMuon->isTrackerMuon() || iMuon->isGlobalMuon() ) ){
     
      //std::cout<<" muon eta      "<<iMuon->eta()<<"  muon pt   "<<iMuon->pt()<<std::endl;
      if( fabs(iMuon->eta()) <  m_threshold_Mu_Eta && iMuon->pt()>  m_threshold_Mu_pT){ countrm++; selpatMuons.push_back( &(*iMuon) ); }
      if( fabs(iMuon->eta()) <   m_threshold_Mu_HighpT_Eta && iMuon->pt()> m_threshold_Mu_HighpT_pT) countrm_hpt++;
    }
  }


  if(selpatMuons.size()>1) std::sort(selpatMuons.begin(),selpatMuons.end(),PtOrder);


  if(countrm_hpt>0 && countrm>=4) is4recm=true;
 
  if(countrm_hpt>0 && countrm>=1){ b_is1SelMu17 = true; b_selMu0_phi = selpatMuons[0]->phi(); b_selMu0_eta = selpatMuons[0]->eta();}
  if(countrm_hpt>0 && countrm>=2){ b_is2SelMu8 = true;  b_selMu1_phi = selpatMuons[1]->phi(); b_selMu1_eta = selpatMuons[1]->eta();}
  if(countrm_hpt>0 && countrm>=3){ b_is3SelMu8 = true;  b_selMu2_phi = selpatMuons[2]->phi(); b_selMu2_eta = selpatMuons[2]->eta();}
  if(countrm_hpt>0 && countrm>=4){ b_is4SelMu8 = true;  b_selMu3_phi = selpatMuons[3]->phi(); b_selMu3_eta = selpatMuons[3]->eta();}


  
  b_npatm = selpatMuons.size();
  
  if(m_debug>10){
    cout<<"  RECO muons pt>8, eta<2.4  "<<selrecoMuons.size()<<endl;
    cout<<"  PAT muons pt>8, eta<2.4   "<<selpatMuons.size()<<endl;
  }


  edm::Handle<pat::MultiMuonCollection> muJets;
  iEvent.getByLabel(m_muJets, muJets);
  const pat::MultiMuon *muJetC = NULL;
  const pat::MultiMuon *muJetF = NULL;
  int   nMuJetsContainMu17     = 0;
  unsigned int nMuJets = muJets->size();
  b_is2MuJets = false;

  
  b_nmjets = nMuJets;
	

  if ( nMuJets == 2) {
    for ( unsigned int j = 0; j < nMuJets; j++ ) {
      bool isMuJetContainMu17 = false;
      for ( unsigned int m = 0; m < (*muJets)[j].numberOfDaughters(); m++ ) {
	if ( (*muJets)[j].muon(m)->pt() > m_threshold_Mu_HighpT_pT && fabs( (*muJets)[j].muon(m)->eta() ) < m_threshold_Mu_HighpT_Eta ) {
	  if(m_debug>10) std::cout<<" muon pt  "<<(*muJets)[j].muon(m)->pt()<<std::endl;
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

  
  
  if(is4recm){
    
    b_4recm=1;
    if(m_debug>10) std::cout<<" 4 recmuons with pt/eta cust  "<<std::endl;
    
    
    if(b_is2MuJets){
      
      b_2mjets=1;
      if(m_debug>10) std::cout<<" 2 MuonJets   "<<std::endl;
      
      
      if(muJetC->numberOfDaughters()==2 && muJetF->numberOfDaughters()==2){
	
	b_2dimuon=1;
	if(m_debug>10) std::cout<<" muons dimuonsC  "<<muJetC->numberOfDaughters()<<" muons diMuonF "<<muJetF->numberOfDaughters()<<std::endl;
	
	
	muJetC_validVtx = false;
	muJetC_validVtx_fitted = false;
	muJetC_validVtx_mindist = false;
	
	
	muJetF_validVtx = false;
	muJetF_validVtx_fitted = false;
	muJetF_validVtx_mindist = false;
	
	if(muJetC->vertexValid()) std::cout<<"   valid MuJetC   "<<std::endl;
	else std::cout<<"  NOT  valid MuJetC   "<<std::endl;
	
	muJetC_validVtx = muJetC->vertexValid();
	muJetC_validVtx_fitted = muJetC->vertexValid_fitted();
	muJetC_validVtx_mindist = muJetC->vertexValid_mindist();
	
	muJetF_validVtx = muJetF->vertexValid();
	muJetF_validVtx_fitted = muJetF->vertexValid_fitted();
	muJetF_validVtx_mindist = muJetF->vertexValid_mindist();

	 if(muJetC_validVtx){
	   muJetC_vtx_x = muJetC->vertexPoint().x();
	   muJetC_vtx_y = muJetC->vertexPoint().y();
	   muJetC_vtx_z = muJetC->vertexPoint().z();
	//   muJetC_mindisttracks = muJetC->mindist_track();
	//   muJetC_mindisttracks_scan = muJetC->mindist_trackscan();
	//   muJetC_vtx_x_scan = muJetC->get_vtx_x_scan();
	//   muJetC_vtx_y_scan = muJetC->get_vtx_y_scan();
	//   muJetC_vtx_z_scan = muJetC->get_vtx_z_scan();
	   }
	
	 if(muJetF_validVtx){
	   muJetF_vtx_x = muJetF->vertexPoint().x();
	   muJetF_vtx_y = muJetF->vertexPoint().y();
	   muJetF_vtx_z = muJetF->vertexPoint().z();
	//   muJetF_mindisttracks = muJetF->mindist_track();
	//   muJetF_mindisttracks_scan = muJetF->mindist_trackscan();
	//   muJetF_vtx_x_scan = muJetF->get_vtx_x_scan();
	//   muJetF_vtx_y_scan = muJetF->get_vtx_y_scan();
	//   muJetF_vtx_z_scan = muJetF->get_vtx_z_scan();
	 }
	
	// muJetC_cpx = muJetC->cpx_tracks();
	// muJetC_cpy = muJetC->cpy_tracks();
	// muJetC_cpz = muJetC->cpz_tracks();
	
	// muJetF_cpx = muJetF->cpx_tracks();
	// muJetF_cpy = muJetF->cpy_tracks();
	// muJetF_cpz = muJetF->cpz_tracks();
	
	// }
	
	b_is2DiMuonsVtxOK = false;
	if ( muJetC != NULL && muJetF != NULL ) {
	  if ( muJetC->vertexValid() && muJetF->vertexValid() ) {
	    b_is2DiMuonsVtxOK = true;
	  }
	}

	// Calculate dz between dimuons - use fitted vertexes
	b_is2DiMuonsDzOK = false;
	if ( b_is2DiMuonsVtxOK ) {
	  b_diMuons_dz = muJetC->vertexDz(beamSpot->position()) - muJetF->vertexDz(beamSpot->position());
	  if ( fabs( b_diMuons_dz ) < m_threshold_DiMuons_dz) b_is2DiMuonsDzOK = true;
	  //	  if (b_event == 471192181){
	  //	    std::cout << "b_diMuons_dz: " << b_diMuons_dz << std::endl;
	  //	  }
	}
	
	// HLT cut
	edm::Handle<pat::TriggerEvent> triggerEvent;
	iEvent.getByLabel("patTriggerEvent", triggerEvent);
	
	// b_isDiMuonHLTFired = false;
	// if (    ( triggerEvent->path("HLT_Mu17_Mu8_v22") && triggerEvent->path("HLT_Mu17_Mu8_v22")->wasAccept() )
	// 	|| ( triggerEvent->path("HLT_Mu17_Mu8_v21") && triggerEvent->path("HLT_Mu17_Mu8_v21")->wasAccept() )
	// 	|| ( triggerEvent->path("HLT_Mu17_Mu8_v19") && triggerEvent->path("HLT_Mu17_Mu8_v19")->wasAccept() )
	// 	|| ( triggerEvent->path("HLT_Mu17_Mu8_v18") && triggerEvent->path("HLT_Mu17_Mu8_v18")->wasAccept() )
	// 	|| ( triggerEvent->path("HLT_Mu17_Mu8_v17") && triggerEvent->path("HLT_Mu17_Mu8_v17")->wasAccept() )
	// 	|| ( triggerEvent->path("HLT_Mu17_Mu8_v16") && triggerEvent->path("HLT_Mu17_Mu8_v16")->wasAccept() ) ) {
	//   b_isDiMuonHLTFired = true;
	// }
	
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

	// Cut on dimuon masses - use fitted vertexes
	b_is2DiMuonsMassOK = false;
	if ( b_is2DiMuonsVtxOK ) {
	  double massC = muJetC->vertexMass();
	  double massF = muJetF->vertexMass();
	  if ( fabs(massC-massF) < (0.13 + 0.065*(massC+massF)/2.0) ) b_is2DiMuonsMassOK = true;
	}
	
	if ( b_is2DiMuonsVtxOK ) {
	  b_diMuonC_Mass = muJetC->vertexMass();
	  b_diMuonF_Mass = muJetF->vertexMass();
	  if(m_debug>10) std::cout<<" mass diMuonC  "<<b_diMuonC_Mass<<" mass diMuonF  "<<b_diMuonF_Mass<<std::endl;
	}
	
	Handle<reco::TrackCollection> tracks;  //============== Original collection of tracks
	iEvent.getByLabel("generalTracks",tracks); 

	// Cut on isolation - use fitted vertexes
	b_is2DiMuonsIsoTkOK = false;
	b_diMuonC_IsoTk = -1.;
	b_diMuonF_IsoTk = -1.;
	if ( b_is2DiMuonsVtxOK ) {
	  double diMuonC_IsoTk = 0.0;
	  double diMuonF_IsoTk = 0.0;
	  
	  const pat::MultiMuon *diMuonTmp = NULL;
	  for ( unsigned int i = 1; i <= 2; i++ ) { 
	    double diMuonTmp_IsoTk = 0.0;
	    
	    if ( i == 1 ) diMuonTmp = muJetC;
	    if ( i == 2 ) diMuonTmp = muJetF;
	    
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
		  diMuonTmp_IsoTk += track->pt();
		}    
	      }
	    }

	    if ( i == 1 ) {
	      diMuonC_IsoTk = diMuonTmp_IsoTk;
	    }
	    if ( i == 2 ) {
	      diMuonF_IsoTk = diMuonTmp_IsoTk;
	    }
	  }
	  b_diMuonC_IsoTk = diMuonC_IsoTk;
	  b_diMuonF_IsoTk = diMuonF_IsoTk;
	  
	  if (b_event == 471192181){
	    std::cout << "b_diMuonC_IsoTk: " << b_diMuonC_IsoTk << std::endl;
	    std::cout << "b_diMuonF_IsoTk: " << b_diMuonF_IsoTk << std::endl;
	  }
	  if ( b_diMuonC_IsoTk < m_threshold_DiMuons_Iso && b_diMuonF_IsoTk < m_threshold_DiMuons_Iso ) b_is2DiMuonsIsoTkOK = true;
	}
	
	// Cut on primary vertex in event
	edm::Handle<reco::VertexCollection> primaryVertices;
	iEvent.getByLabel("offlinePrimaryVertices", primaryVertices);
	
	b_isVertexOK = false;
	Int_t nvtx=0;
	Int_t nvtxbc=0;
	for (reco::VertexCollection::const_iterator vertex = primaryVertices->begin();  vertex != primaryVertices->end();  ++vertex) {
	  nvtxbc++;
	  if (vertex->isValid() && !vertex->isFake() && vertex->tracksSize() >= 4 && fabs(vertex->z()) < 24.) {
	    b_isVertexOK = true;
	    nvtx++;
	  }
	}
	
	b_numvtx = nvtx;
	b_numvtxbc = nvtxbc;
	//    ev_w2dim++;
	
	// UInt_t indxmj1[2]={1000000000};
	// UInt_t indxmj2[2]={1000000000};
    
	//=========================== Built dimuons based only on dR match 
	//  std::vector<std::pair<Int_t,Float_t> > dRmin;
	//     //   std::pair<Int_t,Float_t> temp;
    
	//   UInt_t skip_indx=100000000;
	//   bool firstdim=false;
	//   bool seconddim=false;
	//   for(uint32_t k=0;k<selMuons.size();k++){

	//     if(k!=skip_indx){
	// 	//	std::cout<<"  k index   "<<k<<std::endl;
	// 	for(uint32_t j=0;j<selMuons.size();j++){
	// 	  if(j!=k && j!=skip_indx){
	// 	    //	    std::cout<<"  j index   "<<j<<std::endl;
	// 	    Float_t dphi = My_dPhi(selMuons[k]->phi(),selMuons[j]->phi());
	// 	    Float_t deta = selMuons[k]->eta()-selMuons[j]->eta();
	// 	    Float_t dR = sqrt(dphi*dphi+deta*deta);
	// 	    //	    std::cout<<" dR   "<<dR<<std::endl;
	// 	    if(dR<0.015) {
	// 	      temp.first = j;
	// 	      temp.second = dR;
	// 	      dRmin.push_back(temp);
	// 	    }
	// 	  }
	// 	}
	
	// 	if(dRmin.size()>0){
	// 	  if(!firstdim){
	// 	    std::sort(dRmin.begin(),dRmin.end(),dRorder);
	// 	    indxmj1[0]=k;indxmj1[1]=dRmin[0].first;
	// 	    skip_indx = dRmin[0].first;
	// 	    firstdim=true;
	// 	  }
	// 	  else{
	// 	    indxmj2[0]=k;indxmj2[1]=dRmin[0].first;
	// 	    seconddim=true;
	// 	  }
	// 	}
	//     }
	//     dRmin.clear();
	//   }

	//#####################################################################################
    
    
	//	Bool_t dim1_hit=false;
	//	Bool_t dim2_hit=false;
	
	Int_t counter_gt=0;
	for(uint32_t k=0;k<2;k++){
	  //	  for (reco::TrackCollection::const_iterator track = tracksrf->begin(); track != tracksrf->end(); ++track) {
	  for (reco::TrackCollection::const_iterator track = tracks->begin(); track != tracks->end(); ++track) {
	  
	    //  if(sameTrackRF(&*track,&*(muJetC->muon(k)->innerTrack()))){
	    if(sameTrack(&*track,&*(muJetC->muon(k)->innerTrack()))){
	      if(m_debug>10){
		if(k==0) std::cout<<"  matching   gt  mu1 muJetC  "<<counter_gt<<std::endl;
		if(k==1) std::cout<<"  matching   gt  mu2 muJetC  "<<counter_gt<<std::endl;
	      }
	      const reco::HitPattern& p = track->hitPattern();
	      if(p.hasValidHitInFirstPixelEndcap() || p.hasValidHitInFirstPixelBarrel()){
		b_muJetC_hitpix_genTrk[k] = 1;
		if(m_debug>10){
		  if(k==0) std::cout<<"  hit   gt  mu1 muJetC  "<<counter_gt<<std::endl;
		  if(k==1) std::cout<<"  hit   gt  mu2 muJetC  "<<counter_gt<<std::endl;
		}
	      }
	      if(p.hasValidHitInSecondPixelEndcap() || p.hasValidHitInSecondPixelBarrel()){
		b_muJetC_hitpix_2ndlay_genTrk[k] = 1;
	      }
	      if(p.hasValidHitInThirdPixelBarrel()){
		b_muJetC_hitpix_3rdlay_genTrk[k] = 1;
	      }
	    }

	    
	    //	    if(sameTrackRF(&*track,&*(muJetF->muon(k)->innerTrack()))){
	    if(sameTrack(&*track,&*(muJetF->muon(k)->innerTrack()))){
	      if(m_debug>10){
		if(k==0) std::cout<<"  matching   gt  mu1 muJetF  "<<counter_gt<<std::endl;
		if(k==1) std::cout<<"  matching   gt  mu2 muJetF  "<<counter_gt<<std::endl;
	      }
	      const reco::HitPattern& p = track->hitPattern();
	      if(p.hasValidHitInFirstPixelEndcap() || p.hasValidHitInFirstPixelBarrel()){
		b_muJetF_hitpix_genTrk[k] = 1;
		if(m_debug>10){
		  if(k==0) std::cout<<"  hit   gt  mu1 muJetF  "<<counter_gt<<std::endl;
		  if(k==1) std::cout<<"  hit   gt  mu2 muJetF  "<<counter_gt<<std::endl;
		}
	      }
	      if(p.hasValidHitInSecondPixelEndcap() || p.hasValidHitInSecondPixelBarrel()){
	      	b_muJetF_hitpix_2ndlay_genTrk[k] = 1;
	      }
	      if(p.hasValidHitInThirdPixelBarrel()){
	      	b_muJetF_hitpix_3rdlay_genTrk[k] = 1;
	      }
	    }
	    counter_gt++;
	  }
	}



    
	Int_t indxtrkmj1_validhit[2];
	Int_t indxtrkmj2_validhit[2];

	indxtrkmj1_validhit[0]=-100000;
	indxtrkmj1_validhit[1]=-100000;

	indxtrkmj2_validhit[0]=-100000;
	indxtrkmj2_validhit[1]=-100000;


	Int_t indxtrkmj1[2];
	Int_t indxtrkmj2[2];

	indxtrkmj1[0]=-100000;
	indxtrkmj1[1]=-100000;

	indxtrkmj2[0]=-100000;
	indxtrkmj2[1]=-100000;

	//	Int_t indxtrkmj1_gt[2]={-100000};
	//	Int_t indxtrkmj2_gt[2]={-100000};


	if(m_antraj==1){

      	  edm::ESHandle<NavigationSchool> theSchool;
	  edm::ESHandle<MeasurementTracker> theMeasTk;
	  edm::Handle<MeasurementTrackerEvent> theMeasTkEventHandle;
	  iEvent.getByToken(measurementTrkToken_, theMeasTkEventHandle);
	  const MeasurementTrackerEvent *theMeasTkEvent = theMeasTkEventHandle.product();

	  std::string theNavigationSchool ="";
	  if (param_.exists("NavigationSchool")) theNavigationSchool= param_.getParameter<std::string>("NavigationSchool");
	  else edm::LogWarning("TrackProducerBase")<<"NavigationSchool parameter not set. secondary hit pattern will not be filled.";

	  if (theNavigationSchool!=""){
	    iSetup.get<NavigationSchoolRecord>().get(theNavigationSchool, theSchool);
	    LogDebug("TrackProducer") << "get also the measTk" << "\n";
	    std::string measTkName = param_.getParameter<std::string>("MeasurementTracker");
	    iSetup.get<CkfComponentsRecord>().get(measTkName,theMeasTk);
	    
	  }
	  else{
	    theSchool = edm::ESHandle<NavigationSchool>(); //put an invalid handle
	    theMeasTk = edm::ESHandle<MeasurementTracker>(); //put an invalid handle
	  }

	  if (!theSchool.isValid()) 
	    edm::LogWarning("NavigationSchool")<<"NavigationSchool is invalid!";


      	  // //===============  Calling methods for propagation between layers====================//
	  //	  edm::ESHandle<MeasurementTracker> theMeasTk;
	  //	  std::string measTkName = param_.getParameter<std::string>("MeasurementTracker");
	  //	  iSetup.get<CkfComponentsRecord>().get(measTkName,theMeasTk);
      	  // //	theMeasTk->update(iEvent);
	  
	  //	  NavigationSetter junk(*theSchool);
	  
      	  edm::ESHandle<Propagator> thePropagator;
      	  std::string propagatorName = param_.getParameter<std::string>("Propagator");
      	  iSetup.get<TrackingComponentsRecord>().get(propagatorName,thePropagator);
	  
      	  Chi2MeasurementEstimator estimator(1.e10,100.);  // very very relaxed cuts to capture all nearby hits
      	  Chi2MeasurementEstimator estimator2(30,10.);  // to find compatible layers
	  
      	  //============================================================================================//
	  
	  //============== Refitted collection of tracks
      	  Handle<reco::TrackCollection> tracksrf;  
	  iEvent.getByLabel("TrackRefitter",tracksrf); 
	  //      	  iEvent.getByLabel("RefittedTracks",tracksrf); 
	  
	  cout<<" number of refitted traks  "<<tracksrf->size()<<endl;

      	  vector<Float_t> mincharge;
      	  vector<Float_t> mintheta;
      	  vector<Float_t> minqoverpt;
      	  vector<Float_t> minphi;
      	  vector<Float_t> mindxy;
      	  vector<Float_t> mindz;
	 
      	  std::vector<std::pair<Int_t,Float_t> > minchi2_mu1_muJetC;
      	  std::vector<std::pair<Int_t,Float_t> > minchi2_mu2_muJetC;
      	  std::vector<std::pair<Int_t,Float_t> > minchi2_mu1_muJetF;
      	  std::vector<std::pair<Int_t,Float_t> > minchi2_mu2_muJetF;
	
	
      	  //====== MATCHING selected muons to refitted tracks and asking for hits in 1st layer (barrel or endcap)
	
      	  for(uint32_t k=0;k<2;k++){
	  
      	    mtrack_pt[k] = muJetC->muon(k)->innerTrack()->pt();
      	    mtrack_charge[k] = muJetC->muon(k)->innerTrack()->charge();

      	    mtrack_theta[k] = muJetC->muon(k)->innerTrack()->theta();
      	    mtrack_phi[k] = muJetC->muon(k)->innerTrack()->phi();
      	    mtrack_dxy[k] = muJetC->muon(k)->innerTrack()->dxy();
      	    mtrack_dz[k] = muJetC->muon(k)->innerTrack()->dz();
	  
      	    mtrack_errpt[k] = muJetC->muon(k)->innerTrack()->ptError();
      	    mtrack_errcharge[k] = muJetC->muon(k)->innerTrack()->charge();
      	    mtrack_errqoverp[k] = muJetC->muon(k)->innerTrack()->qoverpError();
      	    mtrack_errtheta[k] = muJetC->muon(k)->innerTrack()->thetaError();
      	    mtrack_errphi[k] = muJetC->muon(k)->innerTrack()->phiError();
      	    mtrack_errdxy[k] = muJetC->muon(k)->innerTrack()->dxyError();
      	    mtrack_errdz[k] = muJetC->muon(k)->innerTrack()->dzError();
	  

      	    Int_t counter_match=0;
      	    Int_t counter_track=0;
	  
      	    for (reco::TrackCollection::const_iterator trackrf = tracksrf->begin(); trackrf != tracksrf->end(); ++trackrf) {
	    
      	      if(trackrf->pt()>3.0 && fabs(trackrf->eta())<2.5){
	      
	      
      	  	if(k==1){
      	  	  std::pair<Int_t,Float_t> temp_mu2_muJetC;
      	  	  std::pair<Int_t,Float_t> temp_mu2_muJetF;
		
      	  	  temp_mu2_muJetC.first = counter_match;
      	  	  temp_mu2_muJetF.first = counter_match;
		
		
      	  	  temp_mu2_muJetC.second = pow(cotan(muJetC->muon(k)->innerTrack()->theta()) - cotan(trackrf->theta()),2)/pow(6.515e-07,2) + 
      	  	    pow((muJetC->muon(k)->innerTrack()->charge()/muJetC->muon(k)->innerTrack()->pt()) - (trackrf->charge()/trackrf->pt()),2)/pow(5.847e-07,2) +
      	  	    pow(My_dPhi(muJetC->muon(k)->innerTrack()->phi(),trackrf->phi()),2)/pow(5.34e-07,2) + 
      	  	    pow(muJetC->muon(k)->innerTrack()->dxy() - trackrf->dxy(),2)/pow(3.6e-06,2) + 
      	  	    pow(muJetC->muon(k)->innerTrack()->dz() - trackrf->dz(),2)/pow(3.703e-06,2);

      	  	  temp_mu2_muJetF.second = pow(cotan(muJetF->muon(k)->innerTrack()->theta()) - cotan(trackrf->theta()),2)/pow(6.515e-07,2) + 
      	  	    pow((muJetF->muon(k)->innerTrack()->charge()/muJetF->muon(k)->innerTrack()->pt()) - (trackrf->charge()/trackrf->pt()),2)/pow(5.847e-07,2) +
      	  	    pow(My_dPhi(muJetF->muon(k)->innerTrack()->phi(),trackrf->phi()),2)/pow(5.34e-07,2) + 
      	  	    pow(muJetF->muon(k)->innerTrack()->dxy() - trackrf->dxy(),2)/pow(3.6e-06,2) + 
      	  	    pow(muJetF->muon(k)->innerTrack()->dz() - trackrf->dz(),2)/pow(3.703e-06,2);
		
      	  	  // std::cout<<" track    "<<counter_match<<"    chi2  muon2 muJetC   "<< temp_mu2_muJetC.second <<std::endl;
      	  	  // std::cout<<" track    "<<counter_match<<"    chi2  muon2 muJetF   "<< temp_mu2_muJetF.second <<std::endl;


      	  	  minchi2_mu2_muJetC.push_back(temp_mu2_muJetC);
      	  	  minchi2_mu2_muJetF.push_back(temp_mu2_muJetF);

      	  	  muJetC_muon2_track_diffcharge[counter_track] = muJetC->muon(k)->innerTrack()->charge() - trackrf->charge();
      	  	  muJetC_muon2_track_diffpt[counter_track] = muJetC->muon(k)->innerTrack()->pt() - trackrf->pt();
      	  	  muJetC_muon2_track_diffqoverp[counter_track] = muJetC->muon(k)->innerTrack()->qoverp() - trackrf->qoverp();
      	  	  muJetC_muon2_track_difftheta[counter_track] = muJetC->muon(k)->innerTrack()->theta() - trackrf->theta();
      	  	  muJetC_muon2_track_diffphi[counter_track] = muJetC->muon(k)->innerTrack()->phi() - trackrf->phi();
      	  	  muJetC_muon2_track_diffdxy[counter_track] = muJetC->muon(k)->innerTrack()->dxy() - trackrf->dxy();
      	  	  muJetC_muon2_track_diffdz[counter_track] = muJetC->muon(k)->innerTrack()->dz() - trackrf->dz();
	      
      	  	}
	      
	      
      	  	if(k==0){
		
      	  	  std::pair<Int_t,Float_t> temp_mu1_muJetC;
      	  	  std::pair<Int_t,Float_t> temp_mu1_muJetF;
		
      	  	  temp_mu1_muJetC.first = counter_match;
      	  	  temp_mu1_muJetF.first = counter_match;
      	  	  temp_mu1_muJetC.second = pow(cotan(muJetC->muon(k)->innerTrack()->theta()) - cotan(trackrf->theta()),2)/pow(6.515e-07,2) + 
      	  	    pow((muJetC->muon(k)->innerTrack()->charge()/muJetC->muon(k)->innerTrack()->pt()) - (trackrf->charge()/trackrf->pt()),2)/pow(5.847e-07,2) +
      	  	    pow(My_dPhi(muJetC->muon(k)->innerTrack()->phi(),trackrf->phi()),2)/pow(5.34e-07,2) + 
      	  	    pow(muJetC->muon(k)->innerTrack()->dxy() - trackrf->dxy(),2)/pow(3.6e-06,2) + 
      	  	    pow(muJetC->muon(k)->innerTrack()->dz() - trackrf->dz(),2)/pow(3.703e-06,2);

      	  	  temp_mu1_muJetF.second = pow(cotan(muJetF->muon(k)->innerTrack()->theta()) - cotan(trackrf->theta()),2)/pow(6.515e-07,2) + 
      	  	    pow((muJetF->muon(k)->innerTrack()->charge()/muJetF->muon(k)->innerTrack()->pt()) - (trackrf->charge()/trackrf->pt()),2)/pow(5.847e-07,2) +
      	  	    pow(My_dPhi(muJetF->muon(k)->innerTrack()->phi(),trackrf->phi()),2)/pow(5.34e-07,2) + 
      	  	    pow(muJetF->muon(k)->innerTrack()->dxy() - trackrf->dxy(),2)/pow(3.6e-06,2) + 
      	  	    pow(muJetF->muon(k)->innerTrack()->dz() - trackrf->dz(),2)/pow(3.703e-06,2);


      	  	  // std::cout<<" track    "<<counter_match<<"    chi2  muon1 muJetC   "<< temp_mu1_muJetC.second <<std::endl;
      	  	  // std::cout<<" track    "<<counter_match<<"    chi2  muon1 muJetF   "<< temp_mu1_muJetF.second <<std::endl;

      	  	  minchi2_mu1_muJetC.push_back(temp_mu1_muJetC);
      	  	  minchi2_mu1_muJetF.push_back(temp_mu1_muJetF);

      	  	  //======================
		
      	  	  mintheta.push_back( cotan(muJetC->muon(k)->innerTrack()->theta()) - cotan(trackrf->theta()) );
      	  	  minqoverpt.push_back((muJetC->muon(k)->innerTrack()->charge()/muJetC->muon(k)->innerTrack()->pt())  -  (trackrf->charge()/trackrf->pt())  );
      	  	  minphi.push_back(  My_dPhi(muJetC->muon(k)->innerTrack()->phi(),trackrf->phi()) );
      	  	  mindxy.push_back(muJetC->muon(k)->innerTrack()->dxy() - trackrf->dxy() );
      	  	  mindz.push_back( muJetC->muon(k)->innerTrack()->dz() - trackrf->dz() );
      	  	  mincharge.push_back( muJetC->muon(k)->innerTrack()->charge() - trackrf->charge());
		
		
      	  	  muJetC_muon1_track_diffpt[counter_track] = muJetC->muon(k)->innerTrack()->pt() - trackrf->pt();
      	  	  muJetC_muon1_track_diffcharge[counter_track] = muJetC->muon(k)->innerTrack()->charge() - trackrf->charge();
      	  	  muJetC_muon1_track_diffqoverp[counter_track] = (muJetC->muon(k)->innerTrack()->charge()/muJetC->muon(k)->innerTrack()->pt()) - (trackrf->charge()/trackrf->pt());
      	  	  muJetC_muon1_track_difftheta[counter_track] = cotan(muJetC->muon(k)->innerTrack()->theta()) - cotan(trackrf->theta());
      	  	  muJetC_muon1_track_diffphi[counter_track] =  My_dPhi(muJetC->muon(k)->innerTrack()->phi(),trackrf->phi());
      	  	  muJetC_muon1_track_diffdxy[counter_track] = muJetC->muon(k)->innerTrack()->dxy() - trackrf->dxy();
      	  	  muJetC_muon1_track_diffdz[counter_track] = muJetC->muon(k)->innerTrack()->dz() - trackrf->dz();
		  
      	  	  muJetC_muon1_track_diffchi2[counter_track] = pow(cotan(muJetC->muon(k)->innerTrack()->theta()) - cotan(trackrf->theta()),2)/pow(6.515e-07,2) + 
      	  	    pow((muJetC->muon(k)->innerTrack()->charge()/muJetC->muon(k)->innerTrack()->pt()) - (trackrf->charge()/trackrf->pt()),2)/pow(5.847e-07,2) +
      	  	    pow(My_dPhi(muJetC->muon(k)->innerTrack()->phi(),trackrf->phi()),2)/pow(5.34e-07,2) + 
      	  	    pow(muJetC->muon(k)->innerTrack()->dxy() - trackrf->dxy(),2)/pow(3.6e-06,2) + 
      	  	    pow(muJetC->muon(k)->innerTrack()->dz() - trackrf->dz(),2)/pow(3.703e-06,2);
		
		
		  
      	  	  muJetC_muon1_track_diffchi2theta[counter_track] = pow(cotan(muJetC->muon(k)->innerTrack()->theta()) - cotan(trackrf->theta()),2)/pow(6.515e-07,2);
      	  	  muJetC_muon1_track_diffchi2qoverpt[counter_track] = pow((muJetC->muon(k)->innerTrack()->charge()/muJetC->muon(k)->innerTrack()->pt()) - (trackrf->charge()/trackrf->pt()),2)/pow(5.847e-07,2);
      	  	  muJetC_muon1_track_diffchi2phi[counter_track] = pow(My_dPhi(muJetC->muon(k)->innerTrack()->phi(),trackrf->phi()),2)/pow(5.34e-07,2); 
      	  	  muJetC_muon1_track_diffchi2dxy[counter_track] = pow(muJetC->muon(k)->innerTrack()->dxy() - trackrf->dxy(),2)/pow(3.6e-06,2);
      	  	  muJetC_muon1_track_diffchi2dz[counter_track] = pow(muJetC->muon(k)->innerTrack()->dz() - trackrf->dz(),2)/pow(3.703e-06,2);
		
      	  	  b_track_pt[counter_track] = trackrf->pt();
      	  	  b_track_charge[counter_track] = trackrf->charge();
      	  	  b_track_qoverp[counter_track] = trackrf->qoverp();
      	  	  b_track_theta[counter_track] = trackrf->theta();
      	  	  b_track_phi[counter_track] = trackrf->phi();
      	  	  b_track_dxy[counter_track] = trackrf->dxy();
      	  	  b_track_dz[counter_track] = trackrf->dz();
		
      	  	  b_track_errpt[counter_track] = trackrf->ptError();
      	  	  b_track_errcharge[counter_track] = trackrf->charge();
      	  	  b_track_errqoverp[counter_track] = trackrf->qoverpError();
      	  	  b_track_errtheta[counter_track] = trackrf->thetaError();
      	  	  b_track_errphi[counter_track] = trackrf->phiError();
      	  	  b_track_errdxy[counter_track] = trackrf->dxyError();
      	  	  b_track_errdz[counter_track] = trackrf->dzError();
      	  	}
	      
      	  	// if(sameTrackRF(&*trackrf,&*(muJetC->muon(k)->innerTrack()))){
	      
      	  	// // std::cout<<" charge   "<<track->charge()<<std::endl;
      	  	// // std::cout<<" qoverp   "<<track->qoverp()<<std::endl;
      	  	// // std::cout<<" theta    "<<track->theta()<<std::endl;
      	  	// // std::cout<<" phi      "<<track->phi()<<std::endl;
      	  	// // std::cout<<" dxy      "<<track->dxy()<<std::endl;

      	  	// // std::cout<<" charge m   "<<muJetC->muon(k)->innerTrack()->charge()<<std::endl;
      	  	// // std::cout<<" qoverp m  "<<muJetC->muon(k)->innerTrack()->qoverp()<<std::endl;
      	  	// // std::cout<<" theta m   "<<muJetC->muon(k)->innerTrack()->theta()<<std::endl;
      	  	// // std::cout<<" phi   m   "<<muJetC->muon(k)->innerTrack()->phi()<<std::endl;
      	  	// // std::cout<<" dxy   m   "<<muJetC->muon(k)->innerTrack()->dxy()<<std::endl;



      	  	//	    if(sameTrack(&*track,&*(muJetC->muon(k)->innerTrack()))){
      	  	  indxtrkmj1[k] = counter_match;
      	  	  if(k==0) b_match_mu1track_muJetC=1;
      	  	  if(k==1) b_match_mu2track_muJetC=1;

      	  	  if(m_debug>10){
		    if(k==0) std::cout<<"  match mj1m0 muon track with indx   "<<counter_match<<" track pT  "<<trackrf->pt()<<" muon track pT  "<<muJetC->muon(k)->innerTrack()->pt()<<std::endl;
		    if(k==1) std::cout<<"  match mj1m1 muon track with indx   "<<counter_match<<" track pT  "<<trackrf->pt()<<" muon track pT  "<<muJetC->muon(k)->innerTrack()->pt()<<std::endl;
		    
		    if(k==0) std::cout<<"  match mj1m0 muon track with indx   "<<counter_match<<" track 1/pT  "<<1/trackrf->pt()<<" muon track 1/pT  "<<1/muJetC->muon(k)->innerTrack()->pt()<<std::endl;
		    if(k==1) std::cout<<"  match mj1m1 muon track with indx   "<<counter_match<<" track 1/pT  "<<1/trackrf->pt()<<" muon track 1/pT  "<<1/muJetC->muon(k)->innerTrack()->pt()<<std::endl;
		    
		    if(k==0) std::cout<<"  match mj1m0 muon track with indx   "<<counter_match<<" track eta  "<<trackrf->eta()<<" muon track pT  "<<muJetC->muon(k)->innerTrack()->eta()<<std::endl;
		    if(k==1) std::cout<<"  match mj1m1 muon track with indx   "<<counter_match<<" track eta  "<<trackrf->eta()<<" muon track pT  "<<muJetC->muon(k)->innerTrack()->eta()<<std::endl;
		    
		    
		    if(k==0) std::cout<<"  match mj1m0 muon track with indx   "<<counter_match<<" track vx  "<<trackrf->vx()<<" muon track vx  "<<muJetC->muon(k)->innerTrack()->vx()<<std::endl;
		    if(k==1) std::cout<<"  match mj1m1 muon track with indx   "<<counter_match<<" track vx  "<<trackrf->vx()<<" muon track vx  "<<muJetC->muon(k)->innerTrack()->vx()<<std::endl;
		    
		    if(k==0) std::cout<<"  match mj1m0 muon track with indx   "<<counter_match<<" track vx  "<<trackrf->vy()<<" muon track vx  "<<muJetC->muon(k)->innerTrack()->vy()<<std::endl;
		    if(k==1) std::cout<<"  match mj1m1 muon track with indx   "<<counter_match<<" track vx  "<<trackrf->vy()<<" muon track vx  "<<muJetC->muon(k)->innerTrack()->vy()<<std::endl;
		    
		    if(k==0) std::cout<<"  match mj1m0 muon track with indx   "<<counter_match<<" track vx  "<<trackrf->vz()<<" muon track vx  "<<muJetC->muon(k)->innerTrack()->vz()<<std::endl;
		    if(k==1) std::cout<<"  match mj1m1 muon track with indx   "<<counter_match<<" track vx  "<<trackrf->vz()<<" muon track vx  "<<muJetC->muon(k)->innerTrack()->vz()<<std::endl;

      	  	  }

      	  	  // const reco::HitPattern& p = trackrf->hitPattern();
      	  	  // if(p.hasValidHitInFirstPixelEndcap() || p.hasValidHitInFirstPixelBarrel()){
      	  	  // 	//		dim1_hit=true;
      	  	  // 	indxtrkmj1_validhit[k] = 1;
      	  	  // 	b_muJetC_hitpix[k] = 1;
      	  	  // }


	  
		  if(sameTrackRF(&*trackrf,&*(muJetF->muon(k)->innerTrack()))){
		    //	    if(sameTrack(&*track,&*(muJetF->muon(k)->innerTrack()))){
		    indxtrkmj2[k] = counter_match;
		    if(k==0) b_match_mu1track_muJetF=1;
		    if(k==1) b_match_mu2track_muJetF=1;
		    if(m_debug>10){
      	  		if(k==0) std::cout<<"  match mj2m0 muon track with indx   "<<counter_match<<" track pT  "<<trackrf->pt()<<std::endl;
			
		    }

		    // const reco::HitPattern& p = trackrf->hitPattern();
		    // if(p.hasValidHitInFirstPixelEndcap() || p.hasValidHitInFirstPixelBarrel()){
		    //   //		dim2_hit=true;
		    //   indxtrkmj2_validhit[k] = 1;
		    //   b_muJetF_hitpix[k] = 1;
		    // }
		  }
		  counter_track++;
      	      }
      	      counter_match++;
      	    }
      	    if(k==0) b_ntracks = counter_track;
	  }

      	  std::sort(mintheta.begin(),mintheta.end(),order);
      	  std::sort(minqoverpt.begin(),minqoverpt.end(),order);
      	  std::sort(minphi.begin(),minphi.end(),order);
      	  std::sort(mindxy.begin(),mindxy.end(),order);
      	  std::sort(mindz.begin(),mindz.end(),order);
      	  std::sort(mincharge.begin(),mincharge.end(),order);
	  
      	  muJetC_muon1_track_mincharge  = mincharge[0];
      	  muJetC_muon1_track_minqoverpt = minqoverpt[0];
      	  muJetC_muon1_track_mintheta   = mintheta[0];
      	  muJetC_muon1_track_minphi     = minphi[0];
      	  muJetC_muon1_track_mindxy     = mindxy[0];
      	  muJetC_muon1_track_mindz      = mindz[0];


      	  // muJetC_muon1_track_minchi2 = pow(mintheta[0],2)/pow(1.23140e-07,2) + pow(minqoverpt[0],2)/pow(1.76958e-07,2) + 
      	  //   pow(minphi[0],2)/pow(2.98078e-08,2) + pow(mindxy[0],2)/pow(3.24229e-07,2) + pow(mindz[0],2)/pow(8.72624e-07,2);
	

      	  muJetC_muon1_track_minchi2theta   = pow(mintheta[0],2)/pow(6.515e-07,2);
      	  muJetC_muon1_track_minchi2qoverpt = pow(minqoverpt[0],2)/pow(5.847e-07,2);
      	  muJetC_muon1_track_minchi2phi     = pow(minphi[0],2)/pow(5.34e-07,2);
      	  muJetC_muon1_track_minchi2dxy     =  pow(mindxy[0],2)/pow(3.6e-06,2);
      	  muJetC_muon1_track_minchi2dz      = pow(mindz[0],2)/pow(3.703e-06,2);

      	  mintheta.clear();
      	  minqoverpt.clear();
      	  minphi.clear();
      	  mindxy.clear();
      	  mindz.clear();
      	  mincharge.clear();

      	  //==================================================================================================
	
      	  std::sort(minchi2_mu1_muJetC.begin(),minchi2_mu1_muJetC.end(),matchorder);
      	  std::sort(minchi2_mu2_muJetC.begin(),minchi2_mu2_muJetC.end(),matchorder);
      	  std::sort(minchi2_mu1_muJetF.begin(),minchi2_mu1_muJetF.end(),matchorder);
      	  std::sort(minchi2_mu2_muJetF.begin(),minchi2_mu2_muJetF.end(),matchorder);


      	  muJetC_muon1_track_minchi2 = minchi2_mu1_muJetC[0].second;
      	  muJetC_muon2_track_minchi2 = minchi2_mu2_muJetC[0].second;
      	  muJetF_muon1_track_minchi2 = minchi2_mu1_muJetF[0].second;
      	  muJetF_muon2_track_minchi2 = minchi2_mu2_muJetF[0].second;


      	  if(minchi2_mu1_muJetC[0].second<100000.0){
      	    b_match_mu1track_muJetC=1;
      	    indxtrkmj1[0] = minchi2_mu1_muJetC[0].first;
      	  }
      	  if(minchi2_mu2_muJetC[0].second<100000.0){
      	    b_match_mu2track_muJetC=1;
      	    indxtrkmj1[1] = minchi2_mu2_muJetC[0].first;
      	  }
      	  if(minchi2_mu1_muJetF[0].second<100000.0){
      	    b_match_mu1track_muJetF=1;
      	    indxtrkmj2[0] = minchi2_mu1_muJetF[0].first;
      	  }
      	  if(minchi2_mu2_muJetF[0].second<100000.0){
      	    b_match_mu2track_muJetF=1;
      	    indxtrkmj2[1] = minchi2_mu2_muJetF[0].first;
      	  }


      	  if(m_debug>10){
      	    std::cout<<"  matching   chi2  mu1 muJetC  "<<minchi2_mu1_muJetC[0].first<<std::endl;
      	    std::cout<<"  matching   chi2  mu2 muJetC  "<<minchi2_mu2_muJetC[0].first<<std::endl;
      	    std::cout<<"  matching   chi2  mu1 muJetF  "<<minchi2_mu1_muJetF[0].first<<std::endl;
      	    std::cout<<"  matching   chi2  mu2 muJetF  "<<minchi2_mu2_muJetF[0].first<<std::endl;
      	  }


      	  minchi2_mu1_muJetC.clear();
      	  minchi2_mu2_muJetC.clear();
      	  minchi2_mu1_muJetF.clear();
      	  minchi2_mu2_muJetF.clear();



      	  Int_t counter_track_hit=0;
      	  for (reco::TrackCollection::const_iterator trackrf = tracksrf->begin(); trackrf != tracksrf->end(); ++trackrf) {
	  
      	    if(counter_track_hit == indxtrkmj1[0]){

	      if(m_debug>10) std::cout<<" match refitted  id mj1_0  "<<counter_track_hit<<std::endl;
      	      const reco::HitPattern& p = trackrf->hitPattern();
      	      if(p.hasValidHitInFirstPixelEndcap() || p.hasValidHitInFirstPixelBarrel()){
		if(m_debug>10) std::cout<<" match refitted  hit "<<std::endl;
      	  	//		dim1_hit=true;
      	  	indxtrkmj1_validhit[0] = 1;
      	  	b_muJetC_hitpix[0] = 1;
      	      }
	      if(p.hasValidHitInSecondPixelEndcap() || p.hasValidHitInSecondPixelBarrel()){
	      	b_muJetC_hitpix_2ndlay[0] = 1;
	      }
	      if(p.hasValidHitInThirdPixelBarrel()){
	      	b_muJetC_hitpix_3rdlay[0] = 1;
	      }
	      
      	    }

      	    if(counter_track_hit == indxtrkmj1[1]){

	      if(m_debug>10) std::cout<<" match refitted  id mj1_1 "<<counter_track_hit<<std::endl;
      	      const reco::HitPattern& p = trackrf->hitPattern();
      	      if(p.hasValidHitInFirstPixelEndcap() || p.hasValidHitInFirstPixelBarrel()){
		if(m_debug>10) std::cout<<" match refitted  hit      "<<std::endl;
      	  	//		dim1_hit=true;
      	  	indxtrkmj1_validhit[1] = 1;
      	  	b_muJetC_hitpix[1] = 1;
      	      }
	      if(p.hasValidHitInSecondPixelEndcap() || p.hasValidHitInSecondPixelBarrel()){
	      	b_muJetC_hitpix_2ndlay[1] = 1;
	      }
	      if(p.hasValidHitInThirdPixelBarrel()){
	      	b_muJetC_hitpix_3rdlay[1] = 1;
	      }

      	    }

      	    if(counter_track_hit == indxtrkmj2[0]){


	      if(m_debug>10) std::cout<<" match refitted  id mj2_0 "<<counter_track_hit<<std::endl;
      	      const reco::HitPattern& p = trackrf->hitPattern();
      	      if(p.hasValidHitInFirstPixelEndcap() || p.hasValidHitInFirstPixelBarrel()){
		if(m_debug>10) std::cout<<" match refitted  hit      "<<std::endl;
      	  	//		dim1_hit=true;
      	  	indxtrkmj2_validhit[0] = 1;
      	  	b_muJetF_hitpix[0] = 1;
      	      }
	      if(p.hasValidHitInSecondPixelEndcap() || p.hasValidHitInSecondPixelBarrel()){
	      	b_muJetF_hitpix_2ndlay[0] = 1;
	      }
	      if(p.hasValidHitInThirdPixelBarrel()){
	      	b_muJetF_hitpix_3rdlay[0] = 1;
	      }

      	    }

      	    if(counter_track_hit == indxtrkmj2[1]){

	      if(m_debug>10) std::cout<<" match refitted  id mj2_1 "<<counter_track_hit<<std::endl;
      	      const reco::HitPattern& p = trackrf->hitPattern();
      	      if(p.hasValidHitInFirstPixelEndcap() || p.hasValidHitInFirstPixelBarrel()){
		if(m_debug>10) std::cout<<" match refitted  hit      "<<std::endl;
      	  	//		dim1_hit=true;
      	  	indxtrkmj2_validhit[1] = 1;
      	  	b_muJetF_hitpix[1] = 1;
      	      }
	      if(p.hasValidHitInSecondPixelEndcap() || p.hasValidHitInSecondPixelBarrel()){
	      	b_muJetF_hitpix_2ndlay[1] = 1;
	      }
	      if(p.hasValidHitInThirdPixelBarrel()){
	      	b_muJetF_hitpix_3rdlay[1] = 1;
	      }
	    }

	      
      	    counter_track_hit++;
	  }
	  


      	  // //====== matching selected muons to generalTracks
      	  // for(uint32_t k=0;k<2;k++){
      	  //   Int_t counter_match=0;
      	  //   for (reco::TrackCollection::const_iterator track = tracks->begin(); track != tracks->end(); ++track) {
      	  //     //	  for (reco::TrackCollection::const_iterator track = tracks->begin(); track != tracks->end(); ++track) {
      	  //     if(sameTrack(&*track,&*(muJetC->muon(k)->innerTrack()))){
	  // 	//      	        indxtrkmj1_gt[k] = counter_match;
      	  //       if(m_debug>10){
      	  // 	if(k==0) std::cout<<"  match mj1m0 muon track with indx genTrk  "<<counter_match<<" track pT  "<<track->pt()<<std::endl;
      	  // 	if(k==1) std::cout<<"  match mj1m1 muon track with indx gentrk  "<<counter_match<<" track pT  "<<track->pt()<<std::endl;
      	  //       }
      	  //       const reco::HitPattern& p = track->hitPattern();
      	  //       if(p.hasValidHitInFirstPixelEndcap() || p.hasValidHitInFirstPixelBarrel()){
      	  // 	//		dim1_hit=true;
	  // 	  //      	  	indxtrkmj1_validhit_gt[k] = 1;
      	  // 	b_muJetC_hitpix_gt[k] = 1;
      	  //       }
      	  //       else{
	  // 	  //      	  	indxtrkmj1_validhit_gt[k] = 0;
      	  // 	b_muJetC_hitpix_gt[k] = 0;
      	  //       }
      	  //     }
	  
      	  //     if(sameTrack(&*track,&*(muJetF->muon(k)->innerTrack()))){
	  // 	//      	        indxtrkmj2_gt[k] = counter_match;
      	  //       if(m_debug>10){
      	  // 	if(k==0) std::cout<<"  match mj2m0 muon track with indx genTrk  "<<counter_match<<" track pT  "<<track->pt()<<std::endl;
      	  // 	if(k==1) std::cout<<"  match mj2m1 muon track with indx genTrk  "<<counter_match<<" track pT  "<<track->pt()<<std::endl;
      	  //       }
      	  //       const reco::HitPattern& p = track->hitPattern();
      	  //       if(p.hasValidHitInFirstPixelEndcap() || p.hasValidHitInFirstPixelBarrel()){
      	  // 	//		dim2_hit_gt=true;
	  // 	  //      	  	indxtrkmj2_validhit_gt[k] = 1;
      	  // 	b_muJetF_hitpix_gt[k] = 1;
      	  //       }
      	  //       else{
	  // 	  //      	  	indxtrkmj2_validhit_gt[k] = 0;
      	  // 	b_muJetF_hitpix_gt[k] = 0;
      	  //       }
      	  //     }
      	  //     counter_match++;
      	  //   }
      	  // }
    

	    if(m_debug>10){
	      std::cout<<"  MuJetC  mu0 valid hit  "<<indxtrkmj1_validhit[0]<<std::endl;
	      std::cout<<"  MuJetC  mu1 valid hit  "<<indxtrkmj1_validhit[1]<<std::endl;
	      std::cout<<"  MuJetF  mu0 valid hit  "<<indxtrkmj2_validhit[0]<<std::endl;
	      std::cout<<"  MuJetF  mu1 valid hit  "<<indxtrkmj2_validhit[1]<<std::endl;

	      // std::cout<<"  MuJet1  mu0 valid hit genTrk  "<<indxtrkmj1_validhit_gt[0]<<std::endl;
	      // std::cout<<"  MuJet1  mu1 valid hit genTrk "<<indxtrkmj1_validhit_gt[1]<<std::endl;
	      // std::cout<<"  MuJet2  mu0 valid hit genTrk "<<indxtrkmj2_validhit_gt[0]<<std::endl;
	      // std::cout<<"  MuJet2  mu1 valid hit genTrk "<<indxtrkmj2_validhit_gt[1]<<std::endl;
	    }
	
	    Local2DPoint mj1m0pos[200];
	    Local2DPoint mj1m1pos[200];
	    Local2DPoint mj2m0pos[200];
	    Local2DPoint mj2m1pos[200];

	    for(int in=0;in<200;in++){
	      mj1m0pos[in] = Local2DPoint(-10000,-10000);
	      mj1m1pos[in] = Local2DPoint(-10000,-10000);
	      mj2m0pos[in] = Local2DPoint(-10000,-10000);
	      mj2m1pos[in] = Local2DPoint(-10000,-10000);
	    }


	    Local2DPoint mj1m0poserr[200];
	    Local2DPoint mj1m1poserr[200];
	    Local2DPoint mj2m0poserr[200];
	    Local2DPoint mj2m1poserr[200];

	    for(int in=0;in<200;in++){
	      mj1m0poserr[in] = Local2DPoint(-10000,-10000);
	      mj1m1poserr[in] = Local2DPoint(-10000,-10000);
	      mj2m0poserr[in] = Local2DPoint(-10000,-10000);
	      mj2m1poserr[in] = Local2DPoint(-10000,-10000);
	    }


	    Local2DPoint mj1m0pos_lastmeas[200];
	    Local2DPoint mj1m1pos_lastmeas[200];
	    Local2DPoint mj2m0pos_lastmeas[200];
	    Local2DPoint mj2m1pos_lastmeas[200];

	    for(int in=0;in<200;in++){
	      mj1m0pos_lastmeas[in] = Local2DPoint(-10000,-10000);
	      mj1m1pos_lastmeas[in] = Local2DPoint(-10000,-10000);
	      mj2m0pos_lastmeas[in] = Local2DPoint(-10000,-10000);
	      mj2m1pos_lastmeas[in] = Local2DPoint(-10000,-10000);
	    }
    



	    // 	std::vector<Local2DPoint> rechit_muon1_muJetC;
	    // 	std::vector<Local2DPoint> rechit_muon2_muJetC;

	    // 	std::vector<Local2DPoint> rechit_muon1_muJetF;
	    // 	std::vector<Local2DPoint> rechit_muon2_muJetF;
      
	
	    // Collection of Trajectories from Refitted Tracks
	    Handle<vector<Trajectory> > trajCollectionHandle;
	    iEvent.getByLabel(param_.getParameter<string>("trajectoryInput"),trajCollectionHandle);
      
	    if(m_debug>10){
	      std::cout<<"   genTrack collection: " <<tracks->size()<<std::endl;
	      std::cout<<"   Refitted trajectoryColl->size(): " << trajCollectionHandle->size()<<std::endl;
	    }


    for(uint32_t km=0;km<2;km++){  // loop for muJetC muon trajectories
	  
      if(m_debug>10){
        std::cout<<"  muon-track indx   "<<indxtrkmj1[km]<<"  muon pT   "<<muJetC->muon(km)->pt()<<"  muon eta  "
  	       <<muJetC->muon(km)->eta()<<std::endl;
      }
      

      //===================   Information for the muon-tracks ===================================//
      if(km==0)  b_mutrack_pT_mu1JetC = muJetC->muon(km)->pt();
      if(km==1)  b_mutrack_pT_mu2JetC = muJetC->muon(km)->pt();

      if(km==0)  b_mutrack_phi_mu1JetC = muJetC->muon(km)->phi();
      if(km==1)  b_mutrack_phi_mu2JetC = muJetC->muon(km)->phi();

      if(km==0)  b_mutrack_charge_mu1JetC = muJetC->muon(km)->charge();
      if(km==1)  b_mutrack_charge_mu2JetC = muJetC->muon(km)->charge();

      if(km==0)  b_mutrack_eta_mu1JetC = muJetC->muon(km)->eta();
      if(km==1)  b_mutrack_eta_mu2JetC = muJetC->muon(km)->eta();


      
      
      //====================== Loop for Trajectories from TrackRefitter  =================================//
      Int_t counter_traj=0;
      for(vector<Trajectory>::const_iterator it = trajCollectionHandle->begin(); it!=trajCollectionHandle->end();it++){
	
	if(counter_traj==indxtrkmj1[km]){
	  
	  if(m_debug>10){std::cout<<"  track   "<<counter_traj<<  "    this traj has " << it->foundHits() << " valid hits"  << " , "
				  << "isValid: " << it->isValid()<<std::endl;
	  }
	  
	  //	    if(it->firstMeasurement().updatedState().isValid() && it->lastMeasurement().updatedState().isValid()){
	  
	  if(it->lastMeasurement().updatedState().isValid()){  // lastMeasurement correspond to the innerLayer assuming direction oppositetoMomentum
	    
	    const FreeTrajectoryState*  outerState = it->firstMeasurement().updatedState().freeState();    
	    const FreeTrajectoryState*  innerState = it->lastMeasurement().updatedState().freeState(); 
	    TrajectoryStateOnSurface outerTSOS = it->firstMeasurement().updatedState();
	    TrajectoryStateOnSurface innerTSOS = it->lastMeasurement().updatedState();
	    
		  if (!outerState || !innerState){
		    std::cout << "No outer layer or no inner layer!" << std::endl;
		  }

  		  if(innerTSOS.hasError()){
  		    if(m_debug>10) std::cout<<" innerTSOS muJetC has errors and they are:   "<<std::endl;
  		    if(m_debug>10) std::cout<<" innerTrajectory local error xx  "<<sqrt(innerTSOS.localError().positionError().xx())<<std::endl;
  		    if(m_debug>10) std::cout<<" innerTrajectory local error yy  "<<sqrt(innerTSOS.localError().positionError().yy())<<std::endl;
		    //  		    if(m_debug>10) std::cout<<" innerTrajectory local error xy "<<sqrt(innerTSOS.localError().positionError().xy())<<std::endl;


  		    if(km==0) {
  		      b_errposx_inlay_mu1_muJetC = sqrt(innerTSOS.localError().positionError().xx());
  		      b_errposy_inlay_mu1_muJetC = sqrt(innerTSOS.localError().positionError().yy());
  		    }

  		    if(km==1) {
  		      b_errposx_inlay_mu2_muJetC = sqrt(innerTSOS.localError().positionError().xx());
  		      b_errposy_inlay_mu2_muJetC = sqrt(innerTSOS.localError().positionError().yy());
  		    }
  		  }

  		  const DetLayer* outerLayer = it->firstMeasurement().layer();
  		  const DetLayer* innerLayer = it->lastMeasurement().layer();

  		  if (!outerLayer || !innerLayer){
  		    //means  that the trajectory was fit/smoothed in a special case: not setting those pointers
  		    if(m_debug>10) std::cout<<"the trajectory was fit/smoothed in a special case: not setting those pointers.\n"
					    <<" Filling the secondary hit patterns was requested. So I will bail out."<<std::endl;
  		  }

  		  //WARNING: we are assuming that the hits were originally sorted along momentum (and therefore oppositeToMomentum after smoothing)
  		  PropagationDirection dirForInnerLayers = oppositeToMomentum;
  		  PropagationDirection dirForOuterLayers = alongMomentum;
  		  if(it->direction() != oppositeToMomentum){
  		    dirForInnerLayers = alongMomentum;
  		    dirForOuterLayers = oppositeToMomentum;
  		    //throw cms::Exception("TrackProducer") 
  		  }
		  
		  std::vector< const DetLayer * > innerCompLayers = (*theSchool).compatibleLayers(*innerLayer,*innerState,dirForInnerLayers);
		  std::vector< const DetLayer * > outerCompLayers = (*theSchool).compatibleLayers(*outerLayer,*outerState,dirForOuterLayers);

		  std::cout<< "innercompatlbleLayers: " << innerCompLayers.size() <<std::endl;
		  std::cout<<"outercompatibleLayers: " << outerCompLayers.size() << std::endl;

		
  		  if(m_debug>10){
  		    std::cout<<"========================================================"<<std::endl;
  		    std::cout<< "inner DetLayer  sub: " 
  			     << innerLayer->subDetector() <<"\n"
  			     << "outer DetLayer  sub: " 
  			     << outerLayer->subDetector() << "\n"
  			     <<" innerstate local position x "<< it->firstMeasurement().updatedState().localPosition().x()<< "\n"
  			     <<" innerstate local position y "<< it->firstMeasurement().updatedState().localPosition().y()<< "\n"
  			     <<" innerstate local position lastmeas x "<< it->lastMeasurement().updatedState().localPosition().x()<<"\n"
  			     <<" innerstate local position lastmeas y "<< it->lastMeasurement().updatedState().localPosition().y()<<std::endl; //"\n"
		    //  			     << "innercompatlbleLayers: " << innerCompLayers.size() << "\n"
		    //  			     << "outercompatibleLayers: " << outerCompLayers.size() << std::endl;
  		    std::cout<<"========================================================"<<std::endl;
  		  }

  		  if(km==0) b_innerlayers_mu1_muJetC = innerCompLayers.size();
  		  if(km==1) b_innerlayers_mu2_muJetC = innerCompLayers.size();

  		  if(innerCompLayers.size()==0) {

  		    if(m_debug>10) std::cout<<"  already in 1st pixel layer   "<<std::endl;
		  
  		    if(km==0) mj1m0pos[0] = Local2DPoint(it->firstMeasurement().updatedState().localPosition().x(),
  							 it->firstMeasurement().updatedState().localPosition().y());
  		    if(km==1) mj1m1pos[0] = Local2DPoint(it->firstMeasurement().updatedState().localPosition().x(),
  							 it->firstMeasurement().updatedState().localPosition().y());
		  
		  
  		    if(km==0) mj1m0pos_lastmeas[0] = Local2DPoint(it->lastMeasurement().updatedState().localPosition().x(),
  								  it->lastMeasurement().updatedState().localPosition().y());
  		    if(km==1) mj1m1pos_lastmeas[0] = Local2DPoint(it->lastMeasurement().updatedState().localPosition().x(),
  								  it->lastMeasurement().updatedState().localPosition().y());
		  
  		  }
	    


  		  Int_t det1stpix=0;
  		  Int_t counter_hit=0;

		
  		  for(vector<const DetLayer *>::const_iterator dd=innerCompLayers.begin(); dd!=innerCompLayers.end();++dd){
	      
  		    if ((*dd)->basicComponents().empty()) {
  		      //		this should never happen. but better protect for it
  		      if(m_debug>10) std::cout<<" a detlayer with no components: I cannot figure out a DetId from this layer. please investigate."<<std::endl;
  		      continue;
  		    }
 
  		    Propagator* localProp = thePropagator->clone();
  		    localProp->setPropagationDirection(oppositeToMomentum);
	      
  		    if(m_debug>10) std::cout<<" propagation to compatible detwithstate using estimator2  "<<std::endl;
  		    vector< GeometricSearchDet::DetWithState > detWithState = (*dd)->compatibleDets(innerTSOS,*localProp,estimator2);
	      
  		    if(!detWithState.size()) continue;
	  
  		    if(m_debug>10) std::cout<<" Dets compatible with a trajectoryState according to estimator)  "<<
  				     detWithState.size()<<std::endl;
	      
  		    if(m_debug>10) std::cout<<"========================================================"<<std::endl;
		  
		  
  		    for(uint32_t k=0;k<detWithState.size();k++){
		    
		      DetId id = detWithState[k].first->geographicalId();
  		      MeasurementDetWithData measDet = theMeasTkEvent->idToDet(id);
  		      // if( ( ( (*dd)->subDetector() == GeomDetEnumerators::PixelBarrel && PXBDetId(id).layer()==1) || 
  		      // 	    ( (*dd)->subDetector() == GeomDetEnumerators::PixelEndcap && PXFDetId(id).disk()==1) ) && measDet.isActive() ){

  		      if( ( ( (*dd)->subDetector() == GeomDetEnumerators::PixelBarrel) || 
  			    ( (*dd)->subDetector() == GeomDetEnumerators::PixelEndcap) ) && measDet.isActive() ){
			
			if(km==0){
			  b_muJetC_muon1_layerB[k] = PXBDetId(id).layer()==1;
			  b_muJetC_muon1_layerF[k] = PXFDetId(id).disk()==1;
			}
			if(km==1){
			  b_muJetC_muon2_layerB[k] = PXBDetId(id).layer()==1;
			  b_muJetC_muon2_layerF[k] = PXFDetId(id).disk()==1;
			}


  			if(m_debug>10){
  			  std::cout<<"  compatible Det  number  "<<k<<std::endl;
  			  std::cout<<" local position rho  Det   "<<detWithState[k].second.localPosition().perp()<<std::endl;
  			  std::cout<<" local position x  Det   "<<detWithState[k].second.localPosition().x()<<std::endl;
  			  std::cout<<" local position y  Det   "<<detWithState[k].second.localPosition().y()<<std::endl;
  			}

  			if(km==0) mj1m0pos[det1stpix] = Local2DPoint(detWithState[k].second.localPosition().x(),detWithState[k].second.localPosition().y());
  			if(km==1) mj1m1pos[det1stpix] = Local2DPoint(detWithState[k].second.localPosition().x(),detWithState[k].second.localPosition().y());
  			if(km==0) mj1m0poserr[det1stpix] = Local2DPoint(sqrt(detWithState[k].second.localError().positionError().xx()),
  									sqrt(detWithState[k].second.localError().positionError().yy()));
  			if(km==1) mj1m1poserr[det1stpix] = Local2DPoint(sqrt(detWithState[k].second.localError().positionError().xx()),
  									sqrt(detWithState[k].second.localError().positionError().yy()));

  			LocalError localErr2 = detWithState[k].second.localError().positionError();
  			localErr2.scale(2); // get the 2 sigma ellipse;
  			Float_t xx2 = sqrt(localErr2.xx());
  			Float_t xy2 = sqrt(localErr2.xy());
  			Float_t yy2 = sqrt(localErr2.yy());
		      
		      
  			if(m_debug>10){
  			  std::cout<<" local error extp innerlayer xx   "<<xx2<<endl;
  			  std::cout<<" local error extp innerlayer xy   "<<xy2<<endl;
  			  std::cout<<" local error extp innerlayer yy   "<<yy2<<endl;
  			}
		      
  			std::cout<<"========================================================"<<std::endl;
			
			
  			TrajectoryStateOnSurface ts; //dummy
		
  			std::vector<TrajectoryMeasurement> tmp = measDet.fastMeasurements(detWithState[k].second,ts,*localProp,estimator);
			
			
  			// 		      vector<TrajectoryMeasurement> tmpVec;
			
  			// 		      if(!tmp.empty()){
  			// 			if(m_debug>10) std::cout<<"  Number of nearby rechits using chi2estimator   "<<tmp.size()<<std::endl;
			  
  			// 			//collecting only valid rechits
  			// 			if(tmp.back().recHit()->getType() == TrackingRecHit::missing) tmp.pop_back();
  			// #if defined( __GXX_EXPERIMENTAL_CXX0X__)
  			// 			tmpVec.insert( tmpVec.end(), std::make_move_iterator(tmp.begin()), std::make_move_iterator(tmp.end()));
  			// #else
  			// 			tmpVec.insert( tmpVec.end(), tmp.begin(), tmp.end());
  			// #endif
			  
  			// 		      }
	      
			
  			if(m_debug>10) std::cout<<" number of hits  "<<tmp.size()<<std::endl;
			

  			for(vector<TrajectoryMeasurement>::iterator tmpIt=tmp.begin();tmpIt!=tmp.end();tmpIt++){
			  
  			  if(tmpIt->recHit()->getType()==0){ // valid hit
			    
  			    if(m_debug>10){
  			      std::cout<<"   status of rechit       "<<tmpIt->recHit()->getType()<<std::endl;
  			      std::cout<<"   local position rho:   "<<tmpIt->recHit()->localPosition().perp()<<std::endl;
  			      std::cout<<"   local position x:     "<<tmpIt->recHit()->localPosition().x()<<std::endl;
  			      std::cout<<"   local position y:     "<<tmpIt->recHit()->localPosition().y()<<std::endl;
  			    }

  			    if(km==0){
  			      b_pixelhit_mu1_muJetC_posx[counter_hit] = tmpIt->recHit()->localPosition().x();
  			      b_pixelhit_mu1_muJetC_posy[counter_hit] = tmpIt->recHit()->localPosition().y();

  			      b_pixelhit_mu1_muJetC_errposx[counter_hit] = sqrt(tmpIt->recHit()->localPositionError().xx());
  			      b_pixelhit_mu1_muJetC_errposy[counter_hit] = sqrt(tmpIt->recHit()->localPositionError().yy());
  			    }

  			    if(km==1){
  			      b_pixelhit_mu2_muJetC_posx[counter_hit] = tmpIt->recHit()->localPosition().x();
  			      b_pixelhit_mu2_muJetC_posy[counter_hit] = tmpIt->recHit()->localPosition().y();

  			      b_pixelhit_mu2_muJetC_errposx[counter_hit] = sqrt(tmpIt->recHit()->localPositionError().xx());
  			      b_pixelhit_mu2_muJetC_errposy[counter_hit] = sqrt(tmpIt->recHit()->localPositionError().yy());
  			    }


  			    Local2DPoint tmphitpos(tmpIt->recHit()->localPosition().x(),tmpIt->recHit()->localPosition().y());
  			    counter_hit++;
  			  }
  			}
  			tmp.clear();
  			det1stpix++;
  		      }
  		    }
  		    delete localProp;
  		  }
		
  		  if(km==0) b_Det_mu1_muJetC = det1stpix;
  		  if(km==1) b_Det_mu2_muJetC = det1stpix;
		
  		  if(km==0)  b_comphits_mu1_muJetC = counter_hit;
  		  if(km==1)  b_comphits_mu2_muJetC = counter_hit;
		
  		}
  	      }
  	      counter_traj++;
  	    }
  	  }

  	  if(m_debug>10) std::cout<<" second muonJet  muJetF  "<<std::endl;
      
  	  for(uint32_t km=0;km<2;km++){
	
  	    //	std::cout<<" indx track   "<<indxtrkmj2[km]<<std::endl;

  	    if(m_debug>10) std::cout<<"  muon-track indx   "<<indxtrkmj2[km]<<"  muon pT   "<<muJetF->muon(km)->pt()<<"  muon eta  "<<muJetF->muon(km)->eta()<<std::endl;
	

	  
  	    //===================   Information for the muon-tracks ===================================//
  	    if(km==0)  b_mutrack_pT_mu1JetF = muJetF->muon(km)->pt();
  	    if(km==1)  b_mutrack_pT_mu2JetF = muJetF->muon(km)->pt();

  	    if(km==0)  b_mutrack_phi_mu1JetF = muJetF->muon(km)->phi();
  	    if(km==1)  b_mutrack_phi_mu2JetF = muJetF->muon(km)->phi();

  	    if(km==0)  b_mutrack_charge_mu1JetF = muJetF->muon(km)->charge();
  	    if(km==1)  b_mutrack_charge_mu2JetF = muJetF->muon(km)->charge();

  	    if(km==0)  b_mutrack_eta_mu1JetF = muJetF->muon(km)->eta();
  	    if(km==1)  b_mutrack_eta_mu2JetF = muJetF->muon(km)->eta();


  	    //====================== Loop for Trajectories from TrackRefitter  =================================//
  	    Int_t counter_traj=0;
  	    for(vector<Trajectory>::const_iterator it = trajCollectionHandle->begin(); it!=trajCollectionHandle->end();it++){
	  
  	      if(counter_traj==indxtrkmj2[km]){

  		if(m_debug>10) std::cout<<"  track   "<<counter_traj<<  "    this traj has " << it->foundHits() << " valid hits"  << " , "
  					<< "isValid: " << it->isValid()<<std::endl;
	    
  		//	    if(it->firstMeasurement().updatedState().isValid() && it->lastMeasurement().updatedState().isValid()){
  		if(it->lastMeasurement().updatedState().isValid()){
	      
  		  const FreeTrajectoryState*  outerState = it->firstMeasurement().updatedState().freeState();    
  		  const FreeTrajectoryState*  innerState = it->lastMeasurement().updatedState().freeState(); 
  		  TrajectoryStateOnSurface outerTSOS = it->firstMeasurement().updatedState();
  		  TrajectoryStateOnSurface innerTSOS = it->lastMeasurement().updatedState();
	      
  		  if(innerTSOS.hasError()){
  		    if(m_debug>10) std::cout<<" innerTSOS muJetF has errors and they are:   "<<std::endl;
  		    if(m_debug>10) std::cout<<" innerTrajectory local error xx  "<<sqrt(innerTSOS.localError().positionError().xx())<<std::endl;
  		    if(m_debug>10) std::cout<<" innerTrajectory local error yy  "<<sqrt(innerTSOS.localError().positionError().yy())<<std::endl;
  		    if(m_debug>10) std::cout<<" innerTrajectory local error xy "<<sqrt(innerTSOS.localError().positionError().xy())<<std::endl;


  		    if(km==0) {
  		      b_errposx_inlay_mu1_muJetF = sqrt(innerTSOS.localError().positionError().xx());
  		      b_errposy_inlay_mu1_muJetF = sqrt(innerTSOS.localError().positionError().yy());
  		    }
		  
  		    if(km==1) {
  		      b_errposx_inlay_mu2_muJetF = sqrt(innerTSOS.localError().positionError().xx());
  		      b_errposy_inlay_mu2_muJetF = sqrt(innerTSOS.localError().positionError().yy());
  		    }


  		  }
	      
  		  const DetLayer* outerLayer = it->firstMeasurement().layer();
  		  const DetLayer* innerLayer = it->lastMeasurement().layer();
	      
  		  if (!outerLayer || !innerLayer){
  		    //means  that the trajectory was fit/smoothed in a special case: not setting those pointers
	    
  		    if(m_debug>10) std::cout<<"the trajectory was fit/smoothed in a special case: not setting those pointers.\n"
  					    <<" Filling the secondary hit patterns was requested. So I will bail out."<<std::endl;
  		  }
	      
  		  //WARNING: we are assuming that the hits were originally sorted along momentum (and therefore oppositeToMomentum after smoothing)
  		  PropagationDirection dirForInnerLayers = oppositeToMomentum;
  		  PropagationDirection dirForOuterLayers = alongMomentum;
  		  if(it->direction() != oppositeToMomentum){
  		    dirForInnerLayers = alongMomentum;
  		    dirForOuterLayers = oppositeToMomentum;
  		    //throw cms::Exception("TrackProducer") 
  		  }
	      
  		  auto  innerCompLayers = (*theSchool).compatibleLayers(*innerLayer,*innerState,dirForInnerLayers);
  		  auto  outerCompLayers = (*theSchool).compatibleLayers(*outerLayer,*outerState,dirForOuterLayers);

  		  // std::vector< const DetLayer * > innerCompLayers = innerLayer->compatibleLayers(*innerState,dirForInnerLayers);
  		  // std::vector< const DetLayer * > outerCompLayers = outerLayer->compatibleLayers(*outerState,dirForOuterLayers);
	    
  		  if(m_debug>10){
  		    std::cout<<"========================================================"<<std::endl;
  		    std::cout<< "inner DetLayer  sub: " 
  			     << innerLayer->subDetector() <<"\n"
  			     << "outer DetLayer  sub: " 
  			     << outerLayer->subDetector() << "\n"
  			     <<" innerstate local position x "<< it->firstMeasurement().updatedState().localPosition().x()<<"\n"
  			     <<" innerstate local position y "<< it->firstMeasurement().updatedState().localPosition().y()<<"\n"
  			     <<" innerstate local position lastmeas x "<< it->lastMeasurement().updatedState().localPosition().x()<<"\n"
  			     <<" innerstate local position lastmeas y "<< it->lastMeasurement().updatedState().localPosition().y()<<"\n"
  			     << "innercompatlbleLayers: " << innerCompLayers.size() << "\n"
  			     << "outercompatibleLayers: " << outerCompLayers.size() << std::endl;
  		    std::cout<<"========================================================"<<std::endl;
  		  }


  		  if(km==0) b_innerlayers_mu1_muJetF = innerCompLayers.size();
  		  if(km==1) b_innerlayers_mu2_muJetF = innerCompLayers.size();
		
  		  if(innerCompLayers.size()==0) {

  		    if(m_debug>10) std::cout<<"  already in 1st pixel layer   "<<std::endl;

  		    if(km==0) mj2m0pos[0] = Local2DPoint(it->firstMeasurement().updatedState().localPosition().x(),
  							 it->firstMeasurement().updatedState().localPosition().y());
  		    if(km==1) mj2m1pos[0] = Local2DPoint(it->firstMeasurement().updatedState().localPosition().x(),
  							 it->firstMeasurement().updatedState().localPosition().y());


  		    if(km==0) mj2m0pos_lastmeas[0] = Local2DPoint(it->lastMeasurement().updatedState().localPosition().x(),
  								  it->lastMeasurement().updatedState().localPosition().y());
  		    if(km==1) mj2m1pos_lastmeas[0] = Local2DPoint(it->lastMeasurement().updatedState().localPosition().x(),
  								  it->lastMeasurement().updatedState().localPosition().y());


  		  }

  		  Int_t counter_hit=0;
  		  Int_t det1stpix=0;
  		  for(vector<const DetLayer *>::const_iterator dd=innerCompLayers.begin(); dd!=innerCompLayers.end();++dd){

  		    if ((*dd)->basicComponents().empty()) {
  		      //this should never happen. but better protect for it
  		      if(m_debug>10) std::cout<<" a detlayer with no components: I cannot figure out a DetId from this layer. please investigate."<<std::endl;
  		      continue;
  		    }
	  
  		    Propagator* localProp = thePropagator->clone();
  		    localProp->setPropagationDirection(oppositeToMomentum);

  		    vector< GeometricSearchDet::DetWithState > detWithState = (*dd)->compatibleDets(innerTSOS,*localProp,estimator2);

  		    if(!detWithState.size()) continue;
	  
  		    if(m_debug>10) std::cout<<" Dets compatible with a trajectoryState according to estimator)  "<<
  				     detWithState.size()<<std::endl;

  		    if(m_debug>10) std::cout<<"========================================================"<<std::endl;
		  
  		    for(uint32_t k=0;k<detWithState.size();k++){
		      DetId id = detWithState[k].first->geographicalId();
		      MeasurementDetWithData measDet = theMeasTkEvent->idToDet(id);

  		      // if( ( ((*dd)->subDetector() == GeomDetEnumerators::PixelBarrel && PXBDetId(id).layer()==1) 
  		      // 	    || ((*dd)->subDetector()  == GeomDetEnumerators::PixelEndcap && PXFDetId(id).disk()==1) ) && measDet.isActive()  ){

  		      if( ( ((*dd)->subDetector() == GeomDetEnumerators::PixelBarrel) 
  			    || ((*dd)->subDetector()  == GeomDetEnumerators::PixelEndcap) ) && measDet.isActive()  ){


			if(km==0){
			  b_muJetF_muon1_layerB[k] = PXBDetId(id).layer()==1;
			  b_muJetF_muon1_layerF[k] = PXFDetId(id).disk()==1;
			}
			if(km==1){
			  b_muJetF_muon2_layerB[k] = PXBDetId(id).layer()==1;
			  b_muJetF_muon2_layerF[k] = PXFDetId(id).disk()==1;
			}
		      
  			if(m_debug>10){
  			  std::cout<<"  compatible Det  number  "<<k<<std::endl;
  			  std::cout<<" local position rho  Det   "<<detWithState[k].second.localPosition().perp()<<std::endl;
  			  std::cout<<" local position x  Det   "<<detWithState[k].second.localPosition().x()<<std::endl;
  			  std::cout<<" local position y  Det   "<<detWithState[k].second.localPosition().y()<<std::endl;
  			}
		      
  			if(km==0) mj2m0pos[det1stpix] = Local2DPoint(detWithState[k].second.localPosition().x(),detWithState[k].second.localPosition().y());
  			if(km==1) mj2m1pos[det1stpix] = Local2DPoint(detWithState[k].second.localPosition().x(),detWithState[k].second.localPosition().y());
		      
  			if(km==0) mj2m0poserr[det1stpix] = Local2DPoint(sqrt(detWithState[k].second.localError().positionError().xx()),
  									sqrt(detWithState[k].second.localError().positionError().yy()));
  			if(km==1) mj2m1poserr[det1stpix] = Local2DPoint(sqrt(detWithState[k].second.localError().positionError().xx()),
  									sqrt(detWithState[k].second.localError().positionError().yy()));

  			LocalError localErr2 = detWithState[k].second.localError().positionError();
  			localErr2.scale(2); // get the 2 sigma ellipse;
  			Float_t xx2 = sqrt(localErr2.xx());
  			Float_t xy2 = sqrt(localErr2.xy());
  			Float_t yy2 = sqrt(localErr2.yy());
		      
		      
  			if(m_debug>10){
  			  std::cout<<" local error extp innerlayer xx   "<<xx2<<endl;
  			  std::cout<<" local error extp innerlayer xy   "<<xy2<<endl;
  			  std::cout<<" local error extp innerlayer yy   "<<yy2<<endl;
  			}

  			std::cout<<"========================================================"<<std::endl;
		      
		      
  			TrajectoryStateOnSurface ts; //dummy
		      
  			std::vector<TrajectoryMeasurement> tmp = measDet.fastMeasurements(detWithState[k].second,ts,*localProp,estimator);

  			if(m_debug>10) std::cout<<" number of hits      "<<tmp.size()<<std::endl;
		      
  			for(vector<TrajectoryMeasurement>::iterator tmpIt=tmp.begin();tmpIt!=tmp.end();tmpIt++){
			
  			  if(tmpIt->recHit()->getType()==0){ // valid hit
			  
  			    if(m_debug>10){
  			      std::cout<<"   status of rechit       "<<tmpIt->recHit()->getType()<<std::endl;
  			      std::cout<<"   local position rho:   "<<tmpIt->recHit()->localPosition().perp()<<std::endl;
  			      std::cout<<"   local position x:     "<<tmpIt->recHit()->localPosition().x()<<std::endl;
  			      std::cout<<"   local position y:     "<<tmpIt->recHit()->localPosition().y()<<std::endl;
  			      std::cout<<"   local position z:     "<<tmpIt->recHit()->localPosition().z()<<std::endl;
  			    }
			  
			  
  			    if(km==0){
  			      b_pixelhit_mu1_muJetF_posx[counter_hit] = tmpIt->recHit()->localPosition().x();
  			      b_pixelhit_mu1_muJetF_posy[counter_hit] = tmpIt->recHit()->localPosition().y();

  			      b_pixelhit_mu1_muJetF_errposx[counter_hit] = sqrt(tmpIt->recHit()->localPositionError().xx());
  			      b_pixelhit_mu1_muJetF_errposy[counter_hit] = sqrt(tmpIt->recHit()->localPositionError().yy());


  			    }
			  
  			    if(km==1){
  			      b_pixelhit_mu2_muJetF_posx[counter_hit] = tmpIt->recHit()->localPosition().x();
  			      b_pixelhit_mu2_muJetF_posy[counter_hit] = tmpIt->recHit()->localPosition().y();

  			      b_pixelhit_mu2_muJetF_errposx[counter_hit] = sqrt(tmpIt->recHit()->localPositionError().xx());
  			      b_pixelhit_mu2_muJetF_errposy[counter_hit] = sqrt(tmpIt->recHit()->localPositionError().yy());
  			    }
			  
  			    Local2DPoint tmphitpos(tmpIt->recHit()->localPosition().x(),tmpIt->recHit()->localPosition().y());
  			    counter_hit++;
  			  }
  			}
  			tmp.clear();
  			det1stpix++;
  		      }
  		    }
  		    delete localProp;
	      
  		    // 	  tracking::TempMeasurements tmps;
  		    // 	  std::vector<const TrackingRecHit*> hits;
		  
  		    // 	  TrajectoryStateOnSurface current =  (*dd)->updateState();

  		    // 	  //if(measDet->isActive() && !measDet->hasBadComponents(detWithState.front().second)){
  		    // 	  if(measDet->isActive()){  
  		    // 	    //	    InvalidTrackingRecHit  tmpHit(id,TrackingRecHit::missing);
  		    // 	    //	    tmpTrack.setTrackerExpectedHitsInner(tmpHit,counter); counter_h++;
  		    // 	    std::cout << "WARNING: this hit is marked as lost because the detector was marked as active" << std::endl;
  		    // 	  }else{
  		    // 	    std::cout << "WARNING: this hit is NOT marked as lost because the detector was marked as inactive" << std::endl;
  		    // 	  }
  		  }
  		  if(km==0) b_Det_mu1_muJetF = det1stpix;
  		  if(km==1) b_Det_mu2_muJetF = det1stpix;

  		  if(km==0)  b_comphits_mu1_muJetF = counter_hit;
  		  if(km==1)  b_comphits_mu2_muJetF = counter_hit;
  		}
  	      }
  	      counter_traj++;
  	    }
  	  }


  	  if(b_Det_mu1_muJetC>0 && b_Det_mu2_muJetC>0){
  	    b_muJetC_trackdist_1stpixel = sqrt(pow(mj1m0pos[0].x()-mj1m1pos[0].x(),2)+pow(mj1m0pos[0].y() - mj1m1pos[0].y(),2));
  	  }

  	  if(b_Det_mu1_muJetF>0 && b_Det_mu2_muJetF>0){
  	    b_muJetF_trackdist_1stpixel = sqrt(pow(mj2m0pos[0].x()-mj2m1pos[0].x(),2)+pow(mj2m0pos[0].y() - mj2m1pos[0].y(),2));
  	  }


  	  for(int ndet = 0; ndet<b_Det_mu1_muJetC;ndet++){
  	    b_muJetC_muon1_posx1stpix[ndet] = mj1m0pos[ndet].x();
  	    b_muJetC_muon1_posy1stpix[ndet] = mj1m0pos[ndet].y();
  	  }

  	  for(int ndet = 0; ndet<b_Det_mu2_muJetC;ndet++){
  	    b_muJetC_muon2_posx1stpix[ndet] = mj1m1pos[ndet].x();
  	    b_muJetC_muon2_posy1stpix[ndet] = mj1m1pos[ndet].y();
  	  }

  	  for(int ndet = 0; ndet<b_Det_mu1_muJetF;ndet++){
  	    b_muJetF_muon1_posx1stpix[ndet] = mj2m0pos[ndet].x();
  	    b_muJetF_muon1_posy1stpix[ndet] = mj2m0pos[ndet].y();
  	  }

  	  for(int ndet = 0; ndet<b_Det_mu2_muJetF;ndet++){
  	    b_muJetF_muon2_posx1stpix[ndet] = mj2m1pos[ndet].x();
  	    b_muJetF_muon2_posy1stpix[ndet] = mj2m1pos[ndet].y();
  	  }

  	  //============ Error =========================//


  	  for(int ndet = 0; ndet<b_Det_mu1_muJetC;ndet++){
  	    b_muJetC_muon1_errposx1stpix[ndet] = mj1m0poserr[ndet].x();
  	    b_muJetC_muon1_errposy1stpix[ndet] = mj1m0poserr[ndet].y();
  	  }

  	  for(int ndet = 0; ndet<b_Det_mu2_muJetC;ndet++){
  	    b_muJetC_muon2_errposx1stpix[ndet] = mj1m1poserr[ndet].x();
  	    b_muJetC_muon2_errposy1stpix[ndet] = mj1m1poserr[ndet].y();
  	  }

  	  for(int ndet = 0; ndet<b_Det_mu1_muJetF;ndet++){
  	    b_muJetF_muon1_errposx1stpix[ndet] = mj2m0poserr[ndet].x();
  	    b_muJetF_muon1_errposy1stpix[ndet] = mj2m0poserr[ndet].y();
  	  }

  	  for(int ndet = 0; ndet<b_Det_mu2_muJetF;ndet++){
  	    b_muJetF_muon2_errposx1stpix[ndet] = mj2m1poserr[ndet].x();
  	    b_muJetF_muon2_errposy1stpix[ndet] = mj2m1poserr[ndet].y();
  	  }


	

  	  for(int ndet = 0; ndet<b_Det_mu1_muJetC;ndet++){
  	    b_muJetC_muon1_posx1stpix_lastmeas[ndet] = mj1m0pos_lastmeas[ndet].x();
  	    b_muJetC_muon1_posy1stpix_lastmeas[ndet] = mj1m0pos_lastmeas[ndet].y();
  	  }

  	  for(int ndet = 0; ndet<b_Det_mu2_muJetC;ndet++){
  	    b_muJetC_muon2_posx1stpix_lastmeas[ndet] = mj1m1pos_lastmeas[ndet].x();
  	    b_muJetC_muon2_posy1stpix_lastmeas[ndet] = mj1m1pos_lastmeas[ndet].y();
  	  }

  	  for(int ndet = 0; ndet<b_Det_mu1_muJetF;ndet++){
  	    b_muJetF_muon1_posx1stpix_lastmeas[ndet] = mj2m0pos_lastmeas[ndet].x();
  	    b_muJetF_muon1_posy1stpix_lastmeas[ndet] = mj2m0pos_lastmeas[ndet].y();
  	  }

  	  for(int ndet = 0; ndet<b_Det_mu2_muJetF;ndet++){
  	    b_muJetF_muon2_posx1stpix_lastmeas[ndet] = mj2m1pos_lastmeas[ndet].x();
  	    b_muJetF_muon2_posy1stpix_lastmeas[ndet] = mj2m1pos_lastmeas[ndet].y();
  	  }


  	  std::vector<std::pair<Int_t,Float_t> > d_mu1_muJetC_hit;
  	  std::vector<std::pair<Int_t,Float_t> > d_mu2_muJetC_hit;
  	  std::vector<std::pair<Int_t,Float_t> > d_mu1_muJetF_hit;
  	  std::vector<std::pair<Int_t,Float_t> > d_mu2_muJetF_hit;
	
  	  for(int ndet = 0; ndet<b_Det_mu1_muJetC;ndet++){
  	    if(m_debug>10) std::cout<<"   ndet    "<<ndet<<std::endl;
  	    std::pair<Int_t,Float_t> temp;
  	    Float_t temp_d=-10000.0;
  	    for(int nhit=0;nhit<b_comphits_mu1_muJetC;nhit++){
  	      if(m_debug>10) std::cout<<"  nhit    "<<nhit<<std::endl;
  	      temp_d  = sqrt(pow(mj1m0pos[ndet].x()-b_pixelhit_mu1_muJetC_posx[nhit],2)+pow(mj1m0pos[ndet].y() - b_pixelhit_mu1_muJetC_posy[nhit],2));
  	      temp.first = nhit;
  	      temp.second = temp_d;
  	      d_mu1_muJetC_hit.push_back(temp);
  	    }
  	    if(d_mu1_muJetC_hit.size()>0){
  	      sort(d_mu1_muJetC_hit.begin(),d_mu1_muJetC_hit.end(),dRorder);
  	      b_mindist_hit_mu1_muJetC[ndet] = d_mu1_muJetC_hit[0].second;
  	    }

  	    d_mu1_muJetC_hit.clear();
  	  }
	

  	  for(int ndet = 0; ndet<b_Det_mu2_muJetC;ndet++){
  	    std::pair<Int_t,Float_t> temp;
  	    Float_t temp_d;
  	    for(int nhit=0;nhit<b_comphits_mu2_muJetC;nhit++){
  	      temp_d  = sqrt(pow(mj1m1pos[ndet].x()-b_pixelhit_mu2_muJetC_posx[nhit],2)+pow(mj1m1pos[ndet].y() - b_pixelhit_mu2_muJetC_posy[nhit],2));
  	      temp.first = nhit;
  	      temp.second = temp_d;
  	      d_mu2_muJetC_hit.push_back(temp);
  	    }
  	    if(d_mu2_muJetC_hit.size()>0){
  	      sort(d_mu2_muJetC_hit.begin(),d_mu2_muJetC_hit.end(),dRorder);
  	      b_mindist_hit_mu2_muJetC[ndet] = d_mu2_muJetC_hit[0].second;
  	    }
  	    d_mu2_muJetC_hit.clear();
  	  }



  	  for(int ndet = 0; ndet<b_Det_mu1_muJetF;ndet++){
  	    std::pair<Int_t,Float_t> temp;
  	    Float_t temp_d;
  	    for(int nhit=0;nhit<b_comphits_mu1_muJetF;nhit++){
  	      temp_d  = sqrt(pow(mj2m0pos[ndet].x()-b_pixelhit_mu1_muJetF_posx[nhit],2)+pow(mj2m0pos[ndet].y() - b_pixelhit_mu1_muJetF_posy[nhit],2));
  	      temp.first = nhit;
  	      temp.second = temp_d;
  	      d_mu1_muJetF_hit.push_back(temp);
  	    }
  	    if(d_mu1_muJetF_hit.size()>0){
  	      sort(d_mu1_muJetF_hit.begin(),d_mu1_muJetF_hit.end(),dRorder);
  	      b_mindist_hit_mu1_muJetF[ndet] = d_mu1_muJetF_hit[0].second;
  	    }
  	    d_mu1_muJetF_hit.clear();
  	  }


  	  for(int ndet = 0; ndet<b_Det_mu2_muJetF;ndet++){
  	    std::pair<Int_t,Float_t> temp;
  	    Float_t temp_d;
  	    for(int nhit=0;nhit<b_comphits_mu2_muJetF;nhit++){
  	      temp_d  = sqrt(pow(mj2m1pos[ndet].x()-b_pixelhit_mu2_muJetF_posx[nhit],2)+pow(mj2m1pos[ndet].y() - b_pixelhit_mu2_muJetF_posy[nhit],2));
  	      temp.first = nhit;
  	      temp.second = temp_d;
  	      d_mu2_muJetF_hit.push_back(temp);
  	    }
  	    if(d_mu2_muJetF_hit.size()>0){
  	      sort(d_mu2_muJetF_hit.begin(),d_mu2_muJetF_hit.end(),dRorder);
  	      b_mindist_hit_mu2_muJetF[ndet] = d_mu2_muJetF_hit[0].second;
  	    }
  	    d_mu2_muJetF_hit.clear();
  	  }

  	  //===============  HIT RECOVERY IMPLEMENTATION (BIKE CHAIN)  =======================//

  	  Bool_t recovermj1[6];
  	  Bool_t recovermj2[6];
  	  Bool_t tmprecovermj1[6];
  	  Bool_t tmprecovermj2[6];
  	  Bool_t recovermj12[6];
	

  	  Float_t d_m1hit;
  	  Float_t d_m2hit;

  	  Float_t radius[6] ={0.1,0.05,0.03,0.01,0.005,0.001};  // Different radius around the muon position used to define the bike chain
	
	
  	  for(int m=0;m<6;m++){

  	    if( (b_muJetC_hitpix[0]!=1&&b_muJetC_hitpix[1]!=1)&&(b_muJetF_hitpix[0]==1||b_muJetF_hitpix[1]==1) ){    // First case muJetC fails but muJetF pass
  	      recovermj1[m]=false;
	    
  	      if(b_Det_mu1_muJetC>0 && b_Det_mu2_muJetC>0){ // need to have both muons extrapolated positions
	      
  		Float_t d_m1m2;  // distance between muons
  		d_m1m2 = sqrt(pow(mj1m0pos[0].x() - mj1m1pos[0].x(),2) + pow(mj1m0pos[0].y() - mj1m1pos[0].y(),2));
	    
	      
  		for(int l=0;l<b_comphits_mu1_muJetC;l++){  // loop for all compatible hits
	    
  		  d_m1hit = sqrt(pow(mj1m0pos[0].x() - b_pixelhit_mu1_muJetC_posx[l],2)+pow(mj1m0pos[0].y() - b_pixelhit_mu1_muJetC_posy[l],2));  // distance between muon1 and hits
  		  d_m2hit = sqrt(pow(mj1m1pos[0].x() - b_pixelhit_mu1_muJetC_posx[l],2)+pow(mj1m1pos[0].y() - b_pixelhit_mu1_muJetC_posy[l],2));  // distance between muon2 and hits
		
  		  Float_t alpha;   
  		  alpha = acos( ( pow(d_m1hit,2) + pow(d_m1m2,2) - pow(d_m2hit,2) )/ (2*d_m1hit*d_m1m2));   // by law of cosines find relations to get perpendicular distance between hit and the line between the two muons
		
  		  Float_t alpha2;
  		  alpha2 = acos( ( pow(d_m2hit,2) + pow(d_m1m2,2) - pow(d_m1hit,2) )/ (2*d_m2hit*d_m1m2));
	    
  		  if(m_debug>10){
  		    std::cout<<" distance between muons  "<<d_m1m2<<std::endl;
  		    std::cout<<" distance between m1 and hit  "<<d_m1hit<<std::endl;
  		    std::cout<<" distance between m2 and hit  "<<d_m2hit<<std::endl;
  		  }
		 
		 
  		  Float_t h;
  		  h = d_m1hit*sin(alpha);   // perpendicular distance between the hit and the line defined by the two muons 
  		  Float_t h2;
  		  h2 = d_m2hit*sin(alpha2);   // perpendicular distance between the hit and the line defined by the two muons 
		 
  		  if(m_debug>10){
  		    std::cout<<"    alpha1    "<<alpha<<"  alpha2   "<<alpha2<<std::endl;
  		    std::cout<<"   h value   "<<h<<std::endl;
  		    std::cout<<"   h2 value   "<<h2<<std::endl;
  		  }
		 
  		  if( ( (alpha<1.57 && alpha2<1.57) && h<radius[m]) || d_m1hit<radius[m] || d_m2hit<radius[m]){  // h<radius and constrain on the angles < pi/2   or the hit inside the radious around the muon position
  		    recovermj1[m] = true;
  		    if(m_debug>10) std::cout<<" recovery of muJetF   "<<std::endl;
  		  }
  		}
  	      }
  	    }


  	    if( (b_muJetF_hitpix[0]!=1&&b_muJetF_hitpix[1]!=1)&&(b_muJetC_hitpix[0]==1||b_muJetC_hitpix[1]==1) ){ //second case the muJetF fails and MuJetC pass
  	      recovermj2[m]=false;
	    
  	      if(b_Det_mu1_muJetF>0 && b_Det_mu2_muJetF>0){

  		Float_t d_m1m2;  // distance between muons
  		d_m1m2 = sqrt(pow(mj2m0pos[0].x() - mj2m1pos[0].x(),2) + pow(mj2m0pos[0].y() - mj2m1pos[0].y(),2));
	    
	      
  		for(int l=0;l<b_comphits_mu1_muJetF;l++){
	    
  		  d_m1hit = sqrt(pow(mj2m0pos[0].x() -  b_pixelhit_mu1_muJetF_posx[l],2)+pow(mj2m0pos[0].y() -  b_pixelhit_mu1_muJetF_posy[l],2));
  		  d_m2hit = sqrt(pow(mj2m1pos[0].x() -  b_pixelhit_mu1_muJetF_posx[l],2)+pow(mj2m1pos[0].y() -  b_pixelhit_mu1_muJetF_posy[l],2));
	    
  		  Float_t alpha;
  		  alpha = acos( ( pow(d_m1hit,2) + pow(d_m1m2,2) - pow(d_m2hit,2) )/ (2*d_m1hit*d_m1m2));
	    
  		  Float_t alpha2;
  		  alpha2 = acos( ( pow(d_m2hit,2) + pow(d_m1m2,2) - pow(d_m1hit,2) )/ (2*d_m2hit*d_m1m2));
	    
  		  if(m_debug>10){
  		    std::cout<<" distance between muons  "<<d_m1m2<<std::endl;
  		    std::cout<<" distance between m1 and hit  "<<d_m1hit<<std::endl;
  		    std::cout<<" distance between m2 and hit  "<<d_m2hit<<std::endl;
  		  }
		 
		 
  		  Float_t h;
  		  h = d_m1hit*sin(alpha);
		 
  		  if(m_debug>10){
  		    std::cout<<"    alpha1    "<<alpha<<"  alpha2   "<<alpha2<<std::endl;
  		    std::cout<<"   h value   "<<h<<std::endl;
  		  }
		 
  		  if( ( (alpha<1.57 && alpha2<1.57) && h<radius[m]) || d_m1hit<radius[m] || d_m2hit<radius[m]){
  		    recovermj2[m] = true;
  		    if(m_debug>10) std::cout<<" recovery of muJetF   "<<std::endl;
  		  }
  		}
  	      }
  	    }



  	    if( (b_muJetF_hitpix[0]!=1&&b_muJetF_hitpix[1]!=1)&&(b_muJetC_hitpix[0]!=1&&b_muJetC_hitpix[1]!=1) ){  // third case both dimuons fail
  	      recovermj12[m]=false;
  	      tmprecovermj1[m] = false;
  	      tmprecovermj2[m] = false;
	    
  	      if(b_Det_mu1_muJetF>0 && b_Det_mu2_muJetF>0){

  		Float_t d_m1m2;  // distance between muons
  		d_m1m2 = sqrt(pow(mj2m0pos[0].x() - mj2m1pos[0].x(),2) + pow(mj2m0pos[0].y() - mj2m1pos[0].y(),2));
	    
	      
  		for(int l=0;l<b_comphits_mu1_muJetF;l++){
	    
  		  d_m1hit = sqrt(pow(mj2m0pos[0].x() - b_pixelhit_mu1_muJetF_posx[l],2)+pow(mj2m0pos[0].y() - b_pixelhit_mu1_muJetF_posy[l],2));
  		  d_m2hit = sqrt(pow(mj2m1pos[0].x() - b_pixelhit_mu1_muJetF_posx[l],2)+pow(mj2m1pos[0].y() - b_pixelhit_mu1_muJetF_posy[l],2));
	    
  		  Float_t alpha;
  		  alpha = acos( ( pow(d_m1hit,2) + pow(d_m1m2,2) - pow(d_m2hit,2) )/ (2*d_m1hit*d_m1m2));
	    
  		  Float_t alpha2;
  		  alpha2 = acos( ( pow(d_m2hit,2) + pow(d_m1m2,2) - pow(d_m1hit,2) )/ (2*d_m2hit*d_m1m2));
	    
  		  if(m_debug>10){
  		    std::cout<<" distance between muons  "<<d_m1m2<<std::endl;
  		    std::cout<<" distance between m1 and hit  "<<d_m1hit<<std::endl;
  		    std::cout<<" distance between m2 and hit  "<<d_m2hit<<std::endl;
  		  }
		 
		 
  		  Float_t h;
  		  h = d_m1hit*sin(alpha);
		 
  		  if(m_debug>10){
  		    std::cout<<"    alpha1    "<<alpha<<"  alpha2   "<<alpha2<<std::endl;
  		    std::cout<<"   h value   "<<h<<std::endl;
  		  }
		 
  		  if( ( (alpha<1.57 && alpha2<1.57) && h<radius[m]) || d_m1hit<radius[m] || d_m2hit<radius[m]){
  		    tmprecovermj2[m] = true;
  		    if(m_debug>10) std::cout<<" recovery of muJetF   "<<std::endl;
  		  }
  		}
  	      }


  	      if(b_Det_mu1_muJetC>0 && b_Det_mu2_muJetC>0){

  		Float_t d_m1m2;  // distance between muons
  		d_m1m2 = sqrt(pow(mj1m0pos[0].x() - mj1m1pos[0].x(),2) + pow(mj1m0pos[0].y() - mj1m1pos[0].y(),2));
	    
	      
  		for(int l=0;l<b_comphits_mu1_muJetC;l++){
	    
  		  d_m1hit = sqrt(pow(mj1m0pos[0].x() - b_pixelhit_mu1_muJetC_posx[l],2)+pow(mj1m0pos[0].y() - b_pixelhit_mu1_muJetC_posy[l],2));
  		  d_m2hit = sqrt(pow(mj1m1pos[0].x() - b_pixelhit_mu1_muJetC_posx[l],2)+pow(mj1m1pos[0].y() - b_pixelhit_mu1_muJetC_posy[l],2));
	    
  		  Float_t alpha;
  		  alpha = acos( ( pow(d_m1hit,2) + pow(d_m1m2,2) - pow(d_m2hit,2) )/ (2*d_m1hit*d_m1m2));
	    
  		  Float_t alpha2;
  		  alpha2 = acos( ( pow(d_m2hit,2) + pow(d_m1m2,2) - pow(d_m1hit,2) )/ (2*d_m2hit*d_m1m2));
	    
  		  if(m_debug>10){
  		    std::cout<<" distance between muons  "<<d_m1m2<<std::endl;
  		    std::cout<<" distance between m1 and hit  "<<d_m1hit<<std::endl;
  		    std::cout<<" distance between m2 and hit  "<<d_m2hit<<std::endl;
  		  }
		 
		 
  		  Float_t h;
  		  h = d_m1hit*sin(alpha);
		 
  		  if(m_debug>10){
  		    std::cout<<"    alpha1    "<<alpha<<"  alpha2   "<<alpha2<<std::endl;
  		    std::cout<<"   h value   "<<h<<std::endl;
  		  }
		 
  		  if( ( (alpha<1.57 && alpha2<1.57) && h<radius[m]) || d_m1hit<radius[m] || d_m2hit<radius[m]){
  		    tmprecovermj1[m] = true;
  		    if(m_debug>10) std::cout<<" recovery of muJetF   "<<std::endl;
  		  }
  		}
  	      }


  	      if(tmprecovermj1[m] && tmprecovermj2[m]) recovermj12[m] = true;
  	    }


  	  }




  	  // recovery flags for different radius
  	  if(recovermj1[0]) b_hitrecover_mj1_r1=1;
  	  if(recovermj1[1]) b_hitrecover_mj1_r05=1;
  	  if(recovermj1[2]) b_hitrecover_mj1_r03=1;
  	  if(recovermj1[3]) b_hitrecover_mj1_r01=1;
  	  if(recovermj1[4]) b_hitrecover_mj1_r005=1;
  	  if(recovermj1[5]) b_hitrecover_mj1_r001=1;

  	  if(recovermj2[0]) b_hitrecover_mj2_r1=1;
  	  if(recovermj2[1]) b_hitrecover_mj2_r05=1;
  	  if(recovermj2[2]) b_hitrecover_mj2_r03=1;
  	  if(recovermj2[3]) b_hitrecover_mj2_r01=1;
  	  if(recovermj2[4]) b_hitrecover_mj2_r005=1;
  	  if(recovermj2[5]) b_hitrecover_mj2_r001=1;

  	  if(recovermj12[0]) b_hitrecover_mj12_r1=1;
  	  if(recovermj12[1]) b_hitrecover_mj12_r05=1;
  	  if(recovermj12[2]) b_hitrecover_mj12_r03=1;
  	  if(recovermj12[3]) b_hitrecover_mj12_r01=1;
  	  if(recovermj12[4]) b_hitrecover_mj12_r005=1;
  	  if(recovermj12[5]) b_hitrecover_mj12_r001=1;
	

  	  // if(b_muJetF_hitpix[0]!=1&&b_muJetF_hitpix[1]!=1){
	    

  	  // }



  	  // if(dim1_hit && !dim2_hit){
	    
  	  //      if(m_debug>10) std::cout<<" number of nearby hits  "<<rechitposmj2.size()<<std::endl;
	  
  	  //      Float_t d_m1m2;  // distance between muons
  	  //      d_m1m2 = sqrt(pow(mj2m0pos.x() - mj2m1pos.x(),2) + pow(mj2m0pos.y() - mj2m1pos.y(),2));
	  
  	  //      Float_t d_m1hit;
  	  //      Float_t d_m2hit;
	  
  	  //      for(uint32_t l=0;l<rechitposmj2.size();l++){
	    
  	  //        d_m1hit = sqrt(pow(mj2m0pos.x() - rechitposmj2[l].x(),2)+pow(mj2m0pos.y() - rechitposmj2[l].y(),2));
  	  //        d_m2hit = sqrt(pow(mj2m1pos.x() - rechitposmj2[l].x(),2)+pow(mj2m1pos.y() - rechitposmj2[l].y(),2));
	    
  	  //        Float_t alpha;
  	  //        alpha = acos( ( pow(d_m1hit,2) + pow(d_m1m2,2) - pow(d_m2hit,2) )/ (2*d_m1hit*d_m1m2));
	    
  	  //        Float_t alpha2;
  	  //        alpha2 = acos( ( pow(d_m2hit,2) + pow(d_m1m2,2) - pow(d_m1hit,2) )/ (2*d_m2hit*d_m1m2));
	    
  	  //        if(m_debug>10){
  	  // 	 std::cout<<" distance between muons  "<<d_m1m2<<std::endl;
  	  // 	 std::cout<<" distance between m1 and hit  "<<d_m1hit<<std::endl;
  	  // 	 std::cout<<" distance between m2 and hit  "<<d_m2hit<<std::endl;
  	  //        }


  	  //        Float_t h;
  	  //        h = d_m1hit*sin(alpha);
	       
  	  //        if(m_debug>10){
  	  // 	 std::cout<<"    alpha1    "<<alpha<<"  alpha2   "<<alpha2<<std::endl;
  	  // 	 std::cout<<"   h value   "<<h<<std::endl;
  	  //        }
	       
  	  //        if( ( (alpha<1.57 && alpha2<1.57) && h<radius[m]) || d_m1hit<radius[m] || d_m2hit<radius[m]){
  	  // 	 recovermj2[m] = true;
  	  // 	 if(m_debug>10) std::cout<<" recovery of muJetF   "<<std::endl;
  	  //        }
  	  //      }
  	  //    }


  	  //    if(!dim1_hit && dim2_hit){

  	  //      if(m_debug>10) std::cout<<" number of nearby hits  "<<rechitposmj1.size()<<std::endl;
	    
  	  //      Float_t d_m1m2;  // distance between muons
  	  //      d_m1m2 = sqrt(pow(mj1m0pos.x() - mj1m1pos.x(),2) + pow(mj1m0pos.y() - mj1m1pos.y(),2));
	
  	  //      Float_t d_m1hit;
  	  //      Float_t d_m2hit;

  	  //      for(uint32_t l=0;l<rechitposmj1.size();l++){
	       
  	  //        d_m1hit = sqrt(pow(mj1m0pos.x() - rechitposmj1[l].x(),2)+pow(mj1m0pos.y() - rechitposmj1[l].y(),2));
  	  //        d_m2hit = sqrt(pow(mj1m1pos.x() - rechitposmj1[l].x(),2)+pow(mj1m1pos.y() - rechitposmj1[l].y(),2));
	       
  	  //        Float_t alpha;
  	  //        alpha = acos( ( pow(d_m1hit,2) + pow(d_m1m2,2) - pow(d_m2hit,2) )/ (2*d_m1hit*d_m1m2));
	      
  	  //        Float_t alpha2;
  	  //        alpha2 = acos( ( pow(d_m2hit,2) + pow(d_m1m2,2) - pow(d_m1hit,2) )/ (2*d_m2hit*d_m1m2));
	       
  	  //        if(m_debug>10){
  	  // 	 std::cout<<" distance between muons  "<<d_m1m2<<std::endl;
  	  // 	 std::cout<<" distance between m1 and hit  "<<d_m1hit<<std::endl;
  	  // 	 std::cout<<" distance between m2 and hit  "<<d_m2hit<<std::endl;
  	  //        }
  	  //        Float_t h;
  	  //        h = d_m1hit*sin(alpha);
	       
  	  //        if(m_debug>10){
  	  // 	 std::cout<<"    alpha1    "<<alpha<<"  alpha2   "<<alpha2<<std::endl;
  	  // 	 std::cout<<"   h value   "<<h<<std::endl;
  	  //        }
	      
  	  //        if( ( (alpha<1.57 && alpha2<1.57) && h<radius[m])  || d_m1hit<radius[m] || d_m2hit<radius[m]){
  	  // 	 recovermj1[m] = true;
  	  // 	 if(m_debug>10) std::cout<<" recovery of muJetC   "<<std::endl;
  	  //        }
  	  //      }
  	  //    }
  	  //  }

  	  //  if( (dim1_hit&&!dim2_hit) && recovermj2[0])  b_hitrecover_mj2_r0005=1;
  	  //  if( (dim1_hit&&!dim2_hit) && recovermj2[1])  b_hitrecover_mj2_r005=1;
  	  //  if( (dim1_hit&&!dim2_hit) && recovermj2[2])  b_hitrecover_mj2_r05=1;
  	  //  if( (dim1_hit&&!dim2_hit) && recovermj2[3])  b_hitrecover_mj2_r01=1;
  	  //  if( (dim1_hit&&!dim2_hit) && recovermj2[4])  b_hitrecover_mj2_r5=1;

  	  //  if( (!dim1_hit&&dim2_hit) && recovermj1[0])  b_hitrecover_mj1_r0005=1;
  	  //  if( (!dim1_hit&&dim2_hit) && recovermj1[1])  b_hitrecover_mj1_r005=1;
  	  //  if( (!dim1_hit&&dim2_hit) && recovermj1[2])  b_hitrecover_mj1_r05=1;
  	  //  if( (!dim1_hit&&dim2_hit) && recovermj1[3])  b_hitrecover_mj1_r01=1;
  	  //  if( (!dim1_hit&&dim2_hit) && recovermj1[4])  b_hitrecover_mj1_r5=1;






  	  // if(m_debug>10){
  	  //   std::cout<<" MuJetC   "<<std::endl;
  	  //   std::cout<<" muon1 position in x   "<<mj1m0pos.x()<<std::endl;
  	  //   std::cout<<" muon1 position in y   "<<mj1m0pos.y()<<std::endl;
  	  //   //	  std::cout<<" muon1 position in z   "<<mj1m0pos.z()<<std::endl;
    
  	  //   std::cout<<" muon2 position in x   "<<mj1m1pos.x()<<std::endl;
  	  //   std::cout<<" muon2 position in y   "<<mj1m1pos.y()<<std::endl;
  	  //   //	  std::cout<<" muon2 position in z   "<<mj1m1pos.z()<<std::endl;
    
    
  	  //   std::cout<<" MuJetF   "<<std::endl;
  	  //   std::cout<<" muon1 position in x   "<<mj2m0pos.x()<<std::endl;
  	  //   std::cout<<" muon1 position in y   "<<mj2m0pos.y()<<std::endl;
  	  //   //	  std::cout<<" muon1 position in z   "<<mj2m0pos.z()<<std::endl;
    
  	  //   std::cout<<" muon2 position in x   "<<mj2m1pos.x()<<std::endl;
  	  //   std::cout<<" muon2 position in y   "<<mj2m1pos.y()<<std::endl;
  	  //   //	  std::cout<<" muon2 position in z   "<<mj2m1pos.z()<<std::endl;
  	  // }
	
  	  // Float_t mj1_dm1m2 = sqrt(pow(mj1m0pos.x()-mj1m1pos.x(),2)+pow(mj1m0pos.y()-mj1m1pos.y(),2));
  	  // Float_t mj2_dm1m2 = sqrt(pow(mj2m0pos.x()-mj2m1pos.x(),2)+pow(mj2m0pos.y()-mj2m1pos.y(),2));
	
	
  	  // b_dist_muon_muJetC = mj1_dm1m2;
  	  // b_dist_muon_muJetF = mj2_dm1m2;

	
  	  // if(m_debug>10){
  	  //   std::cout<<" distance between muons in MuJet1 xz "<<mj1_dm1m2<<std::endl;
  	  //   std::cout<<" distance between muons in MuJet2 xz "<<mj2_dm1m2<<std::endl;
  	  // }

  	  // if(m_debug>10){
  	  //   if(dim1_hit) std::cout<<" MuJet1 with at least one muon in the 1st pixel layer  "<<std::endl;
  	  //   if(dim2_hit) std::cout<<" MuJet2 with at least one muon in the 1st pixel layer  "<<std::endl;
  	  // }
	
      
  	  // if(dim1_hit && dim2_hit){
  	  //   if(m_debug>10) std::cout<<"  No need for hit recovery   "<<std::endl; 
  	  // }
  	  // if(!dim1_hit && !dim2_hit) {
  	  //   if(m_debug>10) std::cout<<"  Both dimuons need the hit recovery (very unlikely case) not considering for the moment "<<std::endl;
  	  // }


  	  // Bool_t recovermj2[5]={false,false,false,false};
  	  // Bool_t recovermj1[5]={false,false,false,false};


  	  // Float_t radius[5] ={0.0005,0.005,0.01,0.05,0.5};  // radius to look around the trajectory for compatible hits.


  	  //  for(int m=0;m<5;m++){

  	  //    if(dim1_hit && !dim2_hit){
	    
  	  //      if(m_debug>10) std::cout<<" number of nearby hits  "<<rechitposmj2.size()<<std::endl;
	  
  	  //      Float_t d_m1m2;  // distance between muons
  	  //      d_m1m2 = sqrt(pow(mj2m0pos.x() - mj2m1pos.x(),2) + pow(mj2m0pos.y() - mj2m1pos.y(),2));
	  
  	  //      Float_t d_m1hit;
  	  //      Float_t d_m2hit;
	  
  	  //      for(uint32_t l=0;l<rechitposmj2.size();l++){
	    
  	  //        d_m1hit = sqrt(pow(mj2m0pos.x() - rechitposmj2[l].x(),2)+pow(mj2m0pos.y() - rechitposmj2[l].y(),2));
  	  //        d_m2hit = sqrt(pow(mj2m1pos.x() - rechitposmj2[l].x(),2)+pow(mj2m1pos.y() - rechitposmj2[l].y(),2));
	    
  	  //        Float_t alpha;
  	  //        alpha = acos( ( pow(d_m1hit,2) + pow(d_m1m2,2) - pow(d_m2hit,2) )/ (2*d_m1hit*d_m1m2));
	    
  	  //        Float_t alpha2;
  	  //        alpha2 = acos( ( pow(d_m2hit,2) + pow(d_m1m2,2) - pow(d_m1hit,2) )/ (2*d_m2hit*d_m1m2));
	    
  	  //        if(m_debug>10){
  	  // 	 std::cout<<" distance between muons  "<<d_m1m2<<std::endl;
  	  // 	 std::cout<<" distance between m1 and hit  "<<d_m1hit<<std::endl;
  	  // 	 std::cout<<" distance between m2 and hit  "<<d_m2hit<<std::endl;
  	  //        }


  	  //        Float_t h;
  	  //        h = d_m1hit*sin(alpha);
	       
  	  //        if(m_debug>10){
  	  // 	 std::cout<<"    alpha1    "<<alpha<<"  alpha2   "<<alpha2<<std::endl;
  	  // 	 std::cout<<"   h value   "<<h<<std::endl;
  	  //        }
	       
  	  //        if( ( (alpha<1.57 && alpha2<1.57) && h<radius[m]) || d_m1hit<radius[m] || d_m2hit<radius[m]){
  	  // 	 recovermj2[m] = true;
  	  // 	 if(m_debug>10) std::cout<<" recovery of muJetF   "<<std::endl;
  	  //        }
  	  //      }
  	  //    }


  	  //    if(!dim1_hit && dim2_hit){

  	  //      if(m_debug>10) std::cout<<" number of nearby hits  "<<rechitposmj1.size()<<std::endl;
	    
  	  //      Float_t d_m1m2;  // distance between muons
  	  //      d_m1m2 = sqrt(pow(mj1m0pos.x() - mj1m1pos.x(),2) + pow(mj1m0pos.y() - mj1m1pos.y(),2));
	
  	  //      Float_t d_m1hit;
  	  //      Float_t d_m2hit;

  	  //      for(uint32_t l=0;l<rechitposmj1.size();l++){
	       
  	  //        d_m1hit = sqrt(pow(mj1m0pos.x() - rechitposmj1[l].x(),2)+pow(mj1m0pos.y() - rechitposmj1[l].y(),2));
  	  //        d_m2hit = sqrt(pow(mj1m1pos.x() - rechitposmj1[l].x(),2)+pow(mj1m1pos.y() - rechitposmj1[l].y(),2));
	       
  	  //        Float_t alpha;
  	  //        alpha = acos( ( pow(d_m1hit,2) + pow(d_m1m2,2) - pow(d_m2hit,2) )/ (2*d_m1hit*d_m1m2));
	      
  	  //        Float_t alpha2;
  	  //        alpha2 = acos( ( pow(d_m2hit,2) + pow(d_m1m2,2) - pow(d_m1hit,2) )/ (2*d_m2hit*d_m1m2));
	       
  	  //        if(m_debug>10){
  	  // 	 std::cout<<" distance between muons  "<<d_m1m2<<std::endl;
  	  // 	 std::cout<<" distance between m1 and hit  "<<d_m1hit<<std::endl;
  	  // 	 std::cout<<" distance between m2 and hit  "<<d_m2hit<<std::endl;
  	  //        }
  	  //        Float_t h;
  	  //        h = d_m1hit*sin(alpha);
	       
  	  //        if(m_debug>10){
  	  // 	 std::cout<<"    alpha1    "<<alpha<<"  alpha2   "<<alpha2<<std::endl;
  	  // 	 std::cout<<"   h value   "<<h<<std::endl;
  	  //        }
	      
  	  //        if( ( (alpha<1.57 && alpha2<1.57) && h<radius[m])  || d_m1hit<radius[m] || d_m2hit<radius[m]){
  	  // 	 recovermj1[m] = true;
  	  // 	 if(m_debug>10) std::cout<<" recovery of muJetC   "<<std::endl;
  	  //        }
  	  //      }
  	  //    }
  	  //  }

  	  //  if( (dim1_hit&&!dim2_hit) && recovermj2[0])  b_hitrecover_mj2_r0005=1;
  	  //  if( (dim1_hit&&!dim2_hit) && recovermj2[1])  b_hitrecover_mj2_r005=1;
  	  //  if( (dim1_hit&&!dim2_hit) && recovermj2[2])  b_hitrecover_mj2_r05=1;
  	  //  if( (dim1_hit&&!dim2_hit) && recovermj2[3])  b_hitrecover_mj2_r01=1;
  	  //  if( (dim1_hit&&!dim2_hit) && recovermj2[4])  b_hitrecover_mj2_r5=1;

  	  //  if( (!dim1_hit&&dim2_hit) && recovermj1[0])  b_hitrecover_mj1_r0005=1;
  	  //  if( (!dim1_hit&&dim2_hit) && recovermj1[1])  b_hitrecover_mj1_r005=1;
  	  //  if( (!dim1_hit&&dim2_hit) && recovermj1[2])  b_hitrecover_mj1_r05=1;
  	  //  if( (!dim1_hit&&dim2_hit) && recovermj1[3])  b_hitrecover_mj1_r01=1;
  	  //  if( (!dim1_hit&&dim2_hit) && recovermj1[4])  b_hitrecover_mj1_r5=1;


  	  //  if(m_debug>10){
  	  //    if( (dim1_hit&&!dim2_hit) && recovermj2[0])  cout<<" hit recover for mujet2 and 0.0005cm  "<<endl;
  	  //    if( (dim1_hit&&!dim2_hit) && recovermj2[1])  cout<<" hit recover for mujet2 and 0.005cm  "<<endl;
  	  //    if( (dim1_hit&&!dim2_hit) && recovermj2[2])  cout<<" hit recover for mujet2 and 0.01cm  "<<endl;
  	  //    if( (dim1_hit&&!dim2_hit) && recovermj2[3])  cout<<" hit recover for mujet2 and 0.05cm  "<<endl;
  	  //    if( (dim1_hit&&!dim2_hit) && recovermj2[4])  cout<<" hit recover for mujet2 and 0.5cm  "<<endl;
	   
  	  //    if( (!dim1_hit&&dim2_hit) && recovermj1[0])  cout<<" hit recover for mujet1 and 0.0005cm  "<<endl;   
  	  //    if( (!dim1_hit&&dim2_hit) && recovermj1[1])  cout<<" hit recover for mujet1 and 0.005cm  "<<endl;  
  	  //    if( (!dim1_hit&&dim2_hit) && recovermj1[2])  cout<<" hit recover for mujet1 and 0.01cm  "<<endl; 
  	  //    if( (!dim1_hit&&dim2_hit) && recovermj1[3])  cout<<" hit recover for mujet1 and 0.05cm  "<<endl; 
  	  //    if( (!dim1_hit&&dim2_hit) && recovermj1[4])  cout<<" hit recover for mujet1 and 0.5cm  "<<endl;
  	  //  }


	}
      }
    }
  }

    m_ttree->Fill();


  
#ifdef THIS_IS_AN_EVENT_EXAMPLE
  Handle<ExampleData> pIn;
  iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  ESHandle<SetupData> pSetup;
  iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void 
AnalysisRun2::beginJob()
{
  edm::Service<TFileService> tFileService;
  m_ttree = tFileService->make<TTree>("Events", "Events");
  
  // Event info                                                                                                                                           
  
  m_ttree->Branch("event", &b_event, "event/I");
  m_ttree->Branch("nevent", &b_nevent, "nevent/I");
  m_ttree->Branch("run",   &b_run,   "run/I");
  m_ttree->Branch("lumi",  &b_lumi,  "lumi/I");
  m_ttree->Branch("nJob",  &b_nJob,  "nJob/I");

  m_ttree->Branch("beamSpot_x", &b_beamSpot_x,"beamSpot_x/F");
  m_ttree->Branch("beamSpot_y", &b_beamSpot_y,"beamSpot_y/F");
  m_ttree->Branch("beamSpot_z", &b_beamSpot_z,"beamSpot_z/F");
  
  m_ttree->Branch("is1GenMu17", &b_is1GenMu17, "is1GenMu17/I");
  m_ttree->Branch("is2GenMu8", &b_is2GenMu8, "is2GenMu8/I");
  m_ttree->Branch("is3GenMu8", &b_is3GenMu8, "is3GenMu8/I");
  m_ttree->Branch("is4GenMu8",  &b_is4GenMu8, "is4GenMu8/I");

  m_ttree->Branch("is1SelMu17", &b_is1SelMu17, "is1SelMu17/I");
  m_ttree->Branch("is2SelMu8", &b_is2SelMu8, "is2SelMu8/I");
  m_ttree->Branch("is3SelMu8", &b_is3SelMu8, "is3SelMu8/I");
  m_ttree->Branch("is4SelMu8",  &b_is4SelMu8, "is4SelMu8/I");

  m_ttree->Branch("selMu0_phi",  &b_selMu0_phi, "selMu0_phi/F");
  m_ttree->Branch("selMu1_phi",  &b_selMu1_phi, "selMu1_phi/F");
  m_ttree->Branch("selMu2_phi",  &b_selMu2_phi, "selMu2_phi/F");
  m_ttree->Branch("selMu3_phi",  &b_selMu3_phi, "selMu3_phi/F");

  m_ttree->Branch("selMu0_eta",  &b_selMu0_eta, "selMu0_eta/F");
  m_ttree->Branch("selMu1_eta",  &b_selMu1_eta, "selMu1_eta/F");
  m_ttree->Branch("selMu2_eta",  &b_selMu2_eta, "selMu2_eta/F");
  m_ttree->Branch("selMu3_eta",  &b_selMu3_eta, "selMu3_eta/F");

  m_ttree->Branch("genA0_pt",&b_genA0_pt, "genA0_pt/F");
  m_ttree->Branch("genA1_pt",&b_genA1_pt, "genA1_pt/F");

  m_ttree->Branch("genA0_eta",&b_genA0_eta, "genA0_eta/F");
  m_ttree->Branch("genA1_eta",&b_genA1_eta, "genA1_eta/F");

  m_ttree->Branch("genA0_phi",&b_genA0_phi, "genA0_phi/F");
  m_ttree->Branch("genA1_phi",&b_genA1_phi, "genA1_phi/F");


  m_ttree->Branch("genA0_vx_rorig", &b_genA0_vx_rorig, "genA0_vx_rorig/F");
  m_ttree->Branch("genA0_vy_rorig", &b_genA0_vy_rorig, "genA0_vy_rorig/F");
  m_ttree->Branch("genA0_vz_rorig", &b_genA0_vz_rorig, "genA0_vz_rorig/F");

  m_ttree->Branch("genA1_vx_rorig", &b_genA1_vx_rorig, "genA1_vx_rorig/F");
  m_ttree->Branch("genA1_vy_rorig", &b_genA1_vy_rorig, "genA1_vy_rorig/F");
  m_ttree->Branch("genA1_vz_rorig", &b_genA1_vz_rorig, "genA1_vz_rorig/F");

  m_ttree->Branch("genA0Mu0_vx_rorig", &b_genA0Mu0_vx_rorig, "genA0Mu0_vx_rorig/F");
  m_ttree->Branch("genA0Mu1_vx_rorig", &b_genA0Mu1_vx_rorig, "genA0Mu1_vx_rorig/F");
  m_ttree->Branch("genA1Mu0_vx_rorig", &b_genA1Mu0_vx_rorig, "genA1Mu0_vx_rorig/F");
  m_ttree->Branch("genA1Mu1_vx_rorig", &b_genA1Mu1_vx_rorig, "genA1Mu1_vx_rorig/F");
  m_ttree->Branch("genA0Mu0_vy_rorig", &b_genA0Mu0_vy_rorig, "genA0Mu0_vy_rorig/F");
  m_ttree->Branch("genA0Mu1_vy_rorig", &b_genA0Mu1_vy_rorig, "genA0Mu1_vy_rorig/F");
  m_ttree->Branch("genA1Mu0_vy_rorig", &b_genA1Mu0_vy_rorig, "genA1Mu0_vy_rorig/F");
  m_ttree->Branch("genA1Mu1_vy_rorig", &b_genA1Mu1_vy_rorig, "genA1Mu1_vy_rorig/F");
  m_ttree->Branch("genA0Mu0_vz_rorig", &b_genA0Mu0_vz_rorig, "genA0Mu0_vz_rorig/F");
  m_ttree->Branch("genA0Mu1_vz_rorig", &b_genA0Mu1_vz_rorig, "genA0Mu1_vz_rorig/F");
  m_ttree->Branch("genA1Mu0_vz_rorig", &b_genA1Mu0_vz_rorig, "genA1Mu0_vz_rorig/F");
  m_ttree->Branch("genA1Mu1_vz_rorig", &b_genA1Mu1_vz_rorig, "genA1Mu1_vz_rorig/F");

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


  m_ttree->Branch("genA0_Lxy_rdet", &b_genA0_Lxy_rdet, "genA0_Lxy_rdet/F");
  m_ttree->Branch("genA1_Lxy_rdet", &b_genA1_Lxy_rdet, "genA1_Lxy_rdet/F");

  m_ttree->Branch("genA0_Lz_rdet", &b_genA0_Lz_rdet, "genA0_Lz_rdet/F");
  m_ttree->Branch("genA1_Lz_rdet", &b_genA1_Lz_rdet, "genA1_Lz_rdet/F");

  m_ttree->Branch("nrecm", &b_nrecm, "nrecm/I");
  m_ttree->Branch("npatm", &b_npatm, "npatm/I");

  m_ttree->Branch("nmjets", &b_nmjets, "nmjets/I");


  m_ttree->Branch("4recm", &b_4recm, "4recm/I");
  m_ttree->Branch("2mjets", &b_2mjets, "2mjets/I");
  m_ttree->Branch("2dimuon", &b_2dimuon, "2dimuon/I");

  m_ttree->Branch("diMuonC_Mass",&b_diMuonC_Mass,"diMuonC_Mass/F");
  m_ttree->Branch("diMuonF_Mass",&b_diMuonF_Mass,"diMuonF_Mass/F");

  m_ttree->Branch("diMuonC_IsoTk",&b_diMuonC_IsoTk,"diMuonC_IsoTk/F");
  m_ttree->Branch("diMuonF_IsoTk",&b_diMuonF_IsoTk,"diMuonF_IsoTk/F");

  m_ttree->Branch("is2DiMuonsVtxOK", &b_is2DiMuonsVtxOK, "is2DiMuonsVtxOK/O");
  m_ttree->Branch("is2DiMuonsDzOK", &b_is2DiMuonsDzOK, "is2DiMuonsDzOK/O");
  m_ttree->Branch("is2DiMuonHLTFired", &b_isDiMuonHLTFired, "isDiMuonHLTFired/O");
  m_ttree->Branch("is2DiMuonsMassOK", &b_is2DiMuonsMassOK, "is2DiMuonsMassOK/O");
  m_ttree->Branch("is2DiMuonsIsoTkOK", &b_is2DiMuonsIsoTkOK, "is2DiMuonsIsoTkOK/O");

  m_ttree->Branch("isVertexOK", &b_isVertexOK, "isVertexOK/O");
  m_ttree->Branch("numvtx", &b_numvtx, "numvtx/I");
  m_ttree->Branch("numvtxbc", &b_numvtxbc, "numvtxbc/I");


  m_ttree->Branch("innerlayers_mu1_muJetC",&b_innerlayers_mu1_muJetC, "innerlayers_mu1_muJetC/I");
  m_ttree->Branch("innerlayers_mu2_muJetC",&b_innerlayers_mu2_muJetC, "innerlayers_mu2_muJetC/I");
  m_ttree->Branch("innerlayers_mu1_muJetF",&b_innerlayers_mu1_muJetF, "innerlayers_mu1_muJetF/I");
  m_ttree->Branch("innerlayers_mu2_muJetF",&b_innerlayers_mu2_muJetF, "innerlayers_mu2_muJetF/I");
  
  m_ttree->Branch("muJetC_trackdist_1stpixel",&b_muJetC_trackdist_1stpixel,"muJetC_trackdist_1stpixel/F");
  m_ttree->Branch("muJetF_trackdist_1stpixel",&b_muJetF_trackdist_1stpixel,"muJetF_trackdist_1stpixel/F");


  m_ttree->Branch("muJetC_hitpix", &b_muJetC_hitpix, "muJetC_hitpix[2]/I");
  m_ttree->Branch("muJetF_hitpix", &b_muJetF_hitpix, "muJetF_hitpix[2]/I");

  m_ttree->Branch("muJetC_hitpix_2ndlay", &b_muJetC_hitpix_2ndlay, "muJetC_hitpix_2ndlay[2]/I");
  m_ttree->Branch("muJetF_hitpix_2ndlay", &b_muJetF_hitpix_2ndlay, "muJetF_hitpix_2ndlay[2]/I");

  m_ttree->Branch("muJetC_hitpix_3rdlay", &b_muJetC_hitpix_3rdlay, "muJetC_hitpix_3rdlay[2]/I");
  m_ttree->Branch("muJetF_hitpix_3rdlay", &b_muJetF_hitpix_3rdlay, "muJetF_hitpix_3rdlay[2]/I");

  m_ttree->Branch("ntracks",&b_ntracks,"ntracks/I");

  m_ttree->Branch("HiggsPt", &HiggsPt,"HiggsPt/F");


  m_ttree->Branch("track_pt", &b_track_pt,"track_pt[ntracks]/F");
  m_ttree->Branch("track_charge", &b_track_charge,"track_charge[ntracks]/F");
  m_ttree->Branch("track_qoverp", &b_track_qoverp,"track_qoverp[ntracks]/F");
  m_ttree->Branch("track_theta", &b_track_theta,"track_theta[ntracks]/F");
  m_ttree->Branch("track_phi", &b_track_phi,"track_phi[ntracks]/F");
  m_ttree->Branch("track_dxy", &b_track_dxy,"track_dxy[ntracks]/F");
  m_ttree->Branch("track_dz", &b_track_dz,"track_dz[ntracks]/F");

  m_ttree->Branch("track_errpt", &b_track_errpt,"track_errpt[ntracks]/F");
  m_ttree->Branch("track_errcharge", &b_track_errcharge,"track_errcharge[ntracks]/F");
  m_ttree->Branch("track_errqoverp", &b_track_errqoverp,"track_errqoverp[ntracks]/F");
  m_ttree->Branch("track_errtheta", &b_track_errtheta,"track_errtheta[ntracks]/F");
  m_ttree->Branch("track_errphi", &b_track_errphi,"track_errphi[ntracks]/F");
  m_ttree->Branch("track_errdxy", &b_track_errdxy,"track_errdxy[ntracks]/F");
  m_ttree->Branch("track_errdz", &b_track_errdz,"track_errdz[ntracks]/F");


  m_ttree->Branch("mtrack_pt", &mtrack_pt,"mtrack_pt[2]/F");
  m_ttree->Branch("mtrack_charge", &mtrack_charge,"mtrack_charge[2]/F");
  m_ttree->Branch("mtrack_qoverp", &mtrack_qoverp,"mtrack_qoverp[2]/F");
  m_ttree->Branch("mtrack_theta", &mtrack_theta,"mtrack_theta[2]/F");
  m_ttree->Branch("mtrack_phi", &mtrack_phi,"mtrack_phi[2]/F");
  m_ttree->Branch("mtrack_dxy", &mtrack_dxy,"mtrack_dxy[2]/F");
  m_ttree->Branch("mtrack_dz", &mtrack_dz,"mtrack_dz[2]/F");

  m_ttree->Branch("mtrack_errpt", &mtrack_errpt,"mtrack_errpt[2]/F");
  m_ttree->Branch("mtrack_errcharge", &mtrack_errcharge,"mtrack_errcharge[2]/F");
  m_ttree->Branch("mtrack_errqoverp", &mtrack_errqoverp,"mtrack_errqoverp[2]/F");
  m_ttree->Branch("mtrack_errtheta", &mtrack_errtheta,"mtrack_errtheta[2]/F");
  m_ttree->Branch("mtrack_errphi", &mtrack_errphi,"mtrack_errphi[2]/F");
  m_ttree->Branch("mtrack_errdxy", &mtrack_errdxy,"mtrack_errdxy[2]/F");
  m_ttree->Branch("mtrack_errdz", &mtrack_errdz,"mtrack_errdz[2]/F");


  m_ttree->Branch("muJetC_muon1_track_minchi2", &muJetC_muon1_track_minchi2,"muJetC_muon1_track_minchi2/F");
  m_ttree->Branch("muJetC_muon2_track_minchi2", &muJetC_muon2_track_minchi2,"muJetC_muon2_track_minchi2/F");
  m_ttree->Branch("muJetF_muon1_track_minchi2", &muJetF_muon1_track_minchi2,"muJetF_muon1_track_minchi2/F");
  m_ttree->Branch("muJetF_muon2_track_minchi2", &muJetF_muon2_track_minchi2,"muJetF_muon2_track_minchi2/F");




  m_ttree->Branch("muJetC_muon1_track_minchi2theta", &muJetC_muon1_track_minchi2theta,"muJetC_muon1_track_minchi2theta/F");
  m_ttree->Branch("muJetC_muon1_track_minchi2qoverpt", &muJetC_muon1_track_minchi2qoverpt,"muJetC_muon1_track_minchi2qoverpt/F");
  m_ttree->Branch("muJetC_muon1_track_minchi2phi", &muJetC_muon1_track_minchi2phi,"muJetC_muon1_track_minchi2phi/F");
  m_ttree->Branch("muJetC_muon1_track_minchi2dxy", &muJetC_muon1_track_minchi2dxy,"muJetC_muon1_track_minchi2dxy/F");
  m_ttree->Branch("muJetC_muon1_track_minchi2dz", &muJetC_muon1_track_minchi2dz,"muJetC_muon1_track_minchi2dz/F");


  m_ttree->Branch("muJetC_muon1_track_mincharge", &muJetC_muon1_track_mincharge,"muJetC_muon1_track_mincharge/F");
  m_ttree->Branch("muJetC_muon1_track_minqoverpt", &muJetC_muon1_track_minqoverpt,"muJetC_muon1_track_minqoverpt/F");
  m_ttree->Branch("muJetC_muon1_track_mintheta", &muJetC_muon1_track_mintheta,"muJetC_muon1_track_mintheta/F");
  m_ttree->Branch("muJetC_muon1_track_minphi", &muJetC_muon1_track_minphi,"muJetC_muon1_track_minphi/F");
  m_ttree->Branch("muJetC_muon1_track_mindxy", &muJetC_muon1_track_mindxy,"muJetC_muon1_track_mindxy/F");
  m_ttree->Branch("muJetC_muon1_track_mindz", &muJetC_muon1_track_mindz,"muJetC_muon1_track_mindz/F");


  m_ttree->Branch("muJetC_muon1_track_diffchi2", &muJetC_muon1_track_diffchi2,"muJetC_muon1_track_diffchi2[ntracks]/F");

  m_ttree->Branch("muJetC_muon1_track_diffchi2theta", &muJetC_muon1_track_diffchi2theta,"muJetC_muon1_track_diffchi2theta[ntracks]/F");
  m_ttree->Branch("muJetC_muon1_track_diffchi2qoverpt", &muJetC_muon1_track_diffchi2qoverpt,"muJetC_muon1_track_diffchi2qoverpt[ntracks]/F");
  m_ttree->Branch("muJetC_muon1_track_diffchi2phi", &muJetC_muon1_track_diffchi2phi,"muJetC_muon1_track_diffchi2phi[ntracks]/F");
  m_ttree->Branch("muJetC_muon1_track_diffchi2dxy", &muJetC_muon1_track_diffchi2dxy,"muJetC_muon1_track_diffchi2dxy[ntracks]/F");
  m_ttree->Branch("muJetC_muon1_track_diffchi2dz", &muJetC_muon1_track_diffchi2dz,"muJetC_muon1_track_diffchi2dz[ntracks]/F");



  m_ttree->Branch("muJetC_muon1_track_diffcharge", &muJetC_muon1_track_diffcharge,"muJetC_muon1_track_diffcharge[ntracks]/F");
  m_ttree->Branch("muJetC_muon1_track_diffpt", &muJetC_muon1_track_diffpt,"muJetC_muon1_track_diffpt[ntracks]/F");
  m_ttree->Branch("muJetC_muon1_track_diffqoverp", &muJetC_muon1_track_diffqoverp,"muJetC_muon1_track_diffqoverp[ntracks]/F");
  m_ttree->Branch("muJetC_muon1_track_difftheta", &muJetC_muon1_track_difftheta,"muJetC_muon1_track_difftheta[ntracks]/F");
  m_ttree->Branch("muJetC_muon1_track_diffphi", &muJetC_muon1_track_diffphi,"muJetC_muon1_track_diffphi[ntracks]/F");
  m_ttree->Branch("muJetC_muon1_track_diffdxy", &muJetC_muon1_track_diffdxy,"muJetC_muon1_track_diffdxy[ntracks]/F");
  m_ttree->Branch("muJetC_muon1_track_diffdz", &muJetC_muon1_track_diffdz,"muJetC_muon1_track_diffdz[ntracks]/F");

  m_ttree->Branch("muJetC_muon2_track_diffcharge", &muJetC_muon2_track_diffcharge,"muJetC_muon2_track_diffcharge[ntracks]/F");
  m_ttree->Branch("muJetC_muon2_track_diffpt", &muJetC_muon2_track_diffpt,"muJetC_muon2_track_diffpt[ntracks]/F");
  m_ttree->Branch("muJetC_muon2_track_diffqoverp", &muJetC_muon2_track_diffqoverp,"muJetC_muon2_track_diffqoverp[ntracks]/F");
  m_ttree->Branch("muJetC_muon2_track_difftheta", &muJetC_muon2_track_difftheta,"muJetC_muon2_track_difftheta[ntracks]/F");
  m_ttree->Branch("muJetC_muon2_track_diffphi", &muJetC_muon2_track_diffphi,"muJetC_muon2_track_diffphi[ntracks]/F");
  m_ttree->Branch("muJetC_muon2_track_diffdxy", &muJetC_muon2_track_diffdxy,"muJetC_muon2_track_diffdxy[ntracks]/F");
  m_ttree->Branch("muJetC_muon2_track_diffdz", &muJetC_muon2_track_diffdz,"muJetC_muon2_track_diffdz[ntracks]/F");


  m_ttree->Branch("muJetC_hitpix_genTrk", &b_muJetC_hitpix_genTrk, "muJetC_hitpix_genTrk[2]/I");
  m_ttree->Branch("muJetF_hitpix_genTrk", &b_muJetF_hitpix_genTrk, "muJetF_hitpix_genTrk[2]/I");

  m_ttree->Branch("muJetC_hitpix_2ndlay_genTrk", &b_muJetC_hitpix_2ndlay_genTrk, "muJetC_hitpix_2ndlay_genTrk[2]/I");
  m_ttree->Branch("muJetF_hitpix_2ndlay_genTrk", &b_muJetF_hitpix_2ndlay_genTrk, "muJetF_hitpix_2ndlay_genTrk[2]/I");

  m_ttree->Branch("muJetC_hitpix_3rdlay_genTrk", &b_muJetC_hitpix_3rdlay_genTrk, "muJetC_hitpix_3rdlay_genTrk[2]/I");
  m_ttree->Branch("muJetF_hitpix_3rdlay_genTrk", &b_muJetF_hitpix_3rdlay_genTrk, "muJetF_hitpix_3rdlay_genTrk[2]/I");

  m_ttree->Branch("muJetC_validVtx", &muJetC_validVtx, "muJetC_validVtx/O");
  m_ttree->Branch("muJetC_validVtx_fitted", &muJetC_validVtx_fitted, "muJetC_validVtx_fitted/O");
  m_ttree->Branch("muJetC_validVtx_mindist", &muJetC_validVtx_mindist, "muJetC_validVtx_mindist/O");

  m_ttree->Branch("muJetF_validVtx", &muJetF_validVtx, "muJetF_validVtx/O");
  m_ttree->Branch("muJetF_validVtx_fitted", &muJetF_validVtx_fitted, "muJetF_validVtx_fitted/O");
  m_ttree->Branch("muJetF_validVtx_mindist", &muJetF_validVtx_mindist, "muJetF_validVtx_mindist/O");

  m_ttree->Branch("muJetC_vtx_x", &muJetC_vtx_x, "muJetC_vtx_x/F");
  m_ttree->Branch("muJetC_vtx_y", &muJetC_vtx_y, "muJetC_vtx_y/F");
  m_ttree->Branch("muJetC_vtx_z", &muJetC_vtx_z, "muJetC_vtx_z/F");

  m_ttree->Branch("muJetF_vtx_x", &muJetF_vtx_x, "muJetF_vtx_x/F");
  m_ttree->Branch("muJetF_vtx_y", &muJetF_vtx_y, "muJetF_vtx_y/F");
  m_ttree->Branch("muJetF_vtx_z", &muJetF_vtx_z, "muJetF_vtx_z/F");

  
  m_ttree->Branch("muJetC_mindisttracks", &muJetC_mindisttracks, "muJetC_mindisttracks/F");
  m_ttree->Branch("muJetF_mindisttracks", &muJetF_mindisttracks, "muJetF_mindisttracks/F");
  
  m_ttree->Branch("muJetC_vtx_x_scan", &muJetC_vtx_x_scan, "muJetC_vtx_x_scan/F");
  m_ttree->Branch("muJetC_vtx_y_scan", &muJetC_vtx_y_scan, "muJetC_vtx_y_scan/F");
  m_ttree->Branch("muJetC_vtx_z_scan", &muJetC_vtx_z_scan, "muJetC_vtx_z_scan/F");

  m_ttree->Branch("muJetF_vtx_x_scan", &muJetF_vtx_x_scan, "muJetF_vtx_x_scan/F");
  m_ttree->Branch("muJetF_vtx_y_scan", &muJetF_vtx_y_scan, "muJetF_vtx_y_scan/F");
  m_ttree->Branch("muJetF_vtx_z_scan", &muJetF_vtx_z_scan, "muJetF_vtx_z_scan/F");

  m_ttree->Branch("muJetC_mindisttracks_scan", &muJetC_mindisttracks_scan, "muJetC_mindisttracks_scan/F");
  m_ttree->Branch("muJetF_mindisttracks_scan", &muJetF_mindisttracks_scan, "muJetF_mindisttracks_scan/F");
  
  m_ttree->Branch("muJetC_cpx", &muJetC_cpx, "muJetC_cpx/F");
  m_ttree->Branch("muJetC_cpy", &muJetC_cpy, "muJetC_cpy/F");
  m_ttree->Branch("muJetC_cpz", &muJetC_cpz, "muJetC_cpz/F");

  m_ttree->Branch("muJetF_cpx", &muJetF_cpx, "muJetF_cpx/F");
  m_ttree->Branch("muJetF_cpy", &muJetF_cpy, "muJetF_cpy/F");
  m_ttree->Branch("muJetF_cpz", &muJetF_cpz, "muJetF_cpz/F");


  m_ttree->Branch("mutrack_pT_mu1JetC", &b_mutrack_pT_mu1JetC, "mutrack_pT_mu1JetC/F");
  m_ttree->Branch("mutrack_pT_mu2JetC", &b_mutrack_pT_mu2JetC, "mutrack_pT_mu2JetC/F");
  m_ttree->Branch("mutrack_eta_mu1JetC", &b_mutrack_eta_mu1JetC, "mutrack_eta_mu1JetC/F");
  m_ttree->Branch("mutrack_eta_mu2JetC", &b_mutrack_eta_mu2JetC, "mutrack_eta_mu2JetC/F");

  m_ttree->Branch("mutrack_phi_mu1JetC", &b_mutrack_phi_mu1JetC, "mutrack_phi_mu1JetC/F");
  m_ttree->Branch("mutrack_phi_mu2JetC", &b_mutrack_phi_mu2JetC, "mutrack_phi_mu2JetC/F");
  m_ttree->Branch("mutrack_phi_mu1JetF", &b_mutrack_phi_mu1JetF, "mutrack_phi_mu1JetF/F");
  m_ttree->Branch("mutrack_phi_mu2JetF", &b_mutrack_phi_mu2JetF, "mutrack_phi_mu2JetF/F");

  m_ttree->Branch("mutrack_pT_mu1JetF", &b_mutrack_pT_mu1JetF, "mutrack_pT_mu1JetF/F");
  m_ttree->Branch("mutrack_pT_mu2JetF", &b_mutrack_pT_mu2JetF, "mutrack_pT_mu2JetF/F");
  m_ttree->Branch("mutrack_eta_mu1JetF", &b_mutrack_eta_mu1JetF, "mutrack_eta_mu1JetF/F");
  m_ttree->Branch("mutrack_eta_mu2JetF", &b_mutrack_eta_mu2JetF, "mutrack_eta_mu2JetF/F");

  m_ttree->Branch("mutrack_charge_mu1JetC", &b_mutrack_charge_mu1JetC, "mutrack_charge_mu1JetC/F");
  m_ttree->Branch("mutrack_charge_mu2JetC", &b_mutrack_charge_mu2JetC, "mutrack_charge_mu2JetC/F");
  m_ttree->Branch("mutrack_charge_mu1JetF", &b_mutrack_charge_mu1JetF, "mutrack_charge_mu1JetF/F");
  m_ttree->Branch("mutrack_charge_mu2JetF", &b_mutrack_charge_mu2JetF, "mutrack_charge_mu2JetF/F");



  m_ttree->Branch("match_mu1track_muJetC",&b_match_mu1track_muJetC,"match_mu1track_muJetC/I");
  m_ttree->Branch("match_mu2track_muJetC",&b_match_mu2track_muJetC,"match_mu2track_muJetC/I");
  m_ttree->Branch("match_mu1track_muJetF",&b_match_mu1track_muJetF,"match_mu1track_muJetF/I");
  m_ttree->Branch("match_mu2track_muJetF",&b_match_mu2track_muJetF,"match_mu2track_muJetF/I");


  m_ttree->Branch("errposx_inlay_mu1_muJetC", &b_errposx_inlay_mu1_muJetC, "errposx_inlay_mu1_muJetC/F");
  m_ttree->Branch("errposx_inlay_mu2_muJetC", &b_errposx_inlay_mu2_muJetC, "errposx_inlay_mu2_muJetC/F");
  m_ttree->Branch("errposy_inlay_mu1_muJetC", &b_errposy_inlay_mu1_muJetC, "errposy_inlay_mu1_muJetC/F");
  m_ttree->Branch("errposy_inlay_mu2_muJetC", &b_errposy_inlay_mu2_muJetC, "errposy_inlay_mu2_muJetC/F");


  m_ttree->Branch("errposx_inlay_mu1_muJetF", &b_errposx_inlay_mu1_muJetF, "errposx_inlay_mu1_muJetF/F");
  m_ttree->Branch("errposx_inlay_mu2_muJetF", &b_errposx_inlay_mu2_muJetF, "errposx_inlay_mu2_muJetF/F");
  m_ttree->Branch("errposy_inlay_mu1_muJetF", &b_errposy_inlay_mu1_muJetF, "errposy_inlay_mu1_muJetF/F");
  m_ttree->Branch("errposy_inlay_mu2_muJetF", &b_errposy_inlay_mu2_muJetF, "errposy_inlay_mu2_muJetF/F");



  m_ttree->Branch("comphits_mu1_muJetC", &b_comphits_mu1_muJetC,"comphits_mu1_muJetC/I");
  m_ttree->Branch("comphits_mu1_muJetF", &b_comphits_mu1_muJetF,"comphits_mu1_muJetF/I");
  m_ttree->Branch("comphits_mu2_muJetC", &b_comphits_mu2_muJetC,"comphits_mu2_muJetC/I");
  m_ttree->Branch("comphits_mu2_muJetF", &b_comphits_mu2_muJetF,"comphits_mu2_muJetF/I");

  m_ttree->Branch("Det_mu1_muJetC", &b_Det_mu1_muJetC,"Det_mu1_muJetC/I");
  m_ttree->Branch("Det_mu2_muJetC", &b_Det_mu2_muJetC,"Det_mu2_muJetC/I");
  m_ttree->Branch("Det_mu1_muJetF", &b_Det_mu1_muJetF,"Det_mu1_muJetF/I");
  m_ttree->Branch("Det_mu2_muJetF", &b_Det_mu2_muJetF,"Det_mu2_muJetF/I");

  m_ttree->Branch("muJetC_muon1_layerB",&b_muJetC_muon1_layerB,"muJetC_muon1_layerB[Det_mu1_muJetC]/F");
  m_ttree->Branch("muJetC_muon2_layerB",&b_muJetC_muon2_layerB,"muJetC_muon2_layerB[Det_mu2_muJetC]/F");
  m_ttree->Branch("muJetF_muon1_layerB",&b_muJetF_muon1_layerB,"muJetF_muon1_layerB[Det_mu1_muJetC]/F");
  m_ttree->Branch("muJetF_muon2_layerB",&b_muJetF_muon2_layerB,"muJetF_muon2_layerB[Det_mu2_muJetC]/F");

  m_ttree->Branch("muJetC_muon1_layerF",&b_muJetC_muon1_layerF,"muJetC_muon1_layerF[Det_mu1_muJetC]/F");
  m_ttree->Branch("muJetC_muon2_layerF",&b_muJetC_muon2_layerF,"muJetC_muon2_layerF[Det_mu2_muJetC]/F");
  m_ttree->Branch("muJetF_muon1_layerF",&b_muJetF_muon1_layerF,"muJetF_muon1_layerF[Det_mu1_muJetC]/F");
  m_ttree->Branch("muJetF_muon2_layerF",&b_muJetF_muon2_layerF,"muJetF_muon2_layerF[Det_mu2_muJetC]/F");

  m_ttree->Branch("muJetC_muon1_posx1stpix", &b_muJetC_muon1_posx1stpix, "muJetC_muon1_posx1stpix[Det_mu1_muJetC]/F");
  m_ttree->Branch("muJetC_muon1_posy1stpix", &b_muJetC_muon1_posy1stpix, "muJetC_muon1_posy1stpix[Det_mu1_muJetC]/F");
  m_ttree->Branch("muJetC_muon1_posz1stpix", &b_muJetC_muon1_posz1stpix, "muJetC_muon1_posz1stpix[Det_mu1_muJetC]/F");

  m_ttree->Branch("muJetC_muon2_posx1stpix", &b_muJetC_muon2_posx1stpix, "muJetC_muon2_posx1stpix[Det_mu2_muJetC]/F");
  m_ttree->Branch("muJetC_muon2_posy1stpix", &b_muJetC_muon2_posy1stpix, "muJetC_muon2_posy1stpix[Det_mu2_muJetC]/F");
  m_ttree->Branch("muJetC_muon2_posz1stpix", &b_muJetC_muon2_posz1stpix, "muJetC_muon2_posz1stpix[Det_mu2_muJetC]/F");

  m_ttree->Branch("muJetF_muon1_posx1stpix", &b_muJetF_muon1_posx1stpix, "muJetF_muon1_posx1stpix[Det_mu1_muJetF]/F");
  m_ttree->Branch("muJetF_muon1_posy1stpix", &b_muJetF_muon1_posy1stpix, "muJetF_muon1_posy1stpix[Det_mu1_muJetF]/F");
  m_ttree->Branch("muJetF_muon1_posz1stpix", &b_muJetF_muon1_posz1stpix, "muJetF_muon1_posz1stpix[Det_mu1_muJetF]/F");

  m_ttree->Branch("muJetF_muon2_posx1stpix", &b_muJetF_muon2_posx1stpix, "muJetF_muon2_posx1stpix[Det_mu2_muJetF]/F");
  m_ttree->Branch("muJetF_muon2_posy1stpix", &b_muJetF_muon2_posy1stpix, "muJetF_muon2_posy1stpix[Det_mu2_muJetF]/F");
  m_ttree->Branch("muJetF_muon2_posz1stpix", &b_muJetF_muon2_posz1stpix, "muJetF_muon2_posz1stpix[Det_mu2_muJetF]/F");


  m_ttree->Branch("muJetC_muon1_errposx1stpix", &b_muJetC_muon1_errposx1stpix, "muJetC_muon1_errposx1stpix[Det_mu1_muJetC]/F");
  m_ttree->Branch("muJetC_muon1_errposy1stpix", &b_muJetC_muon1_errposy1stpix, "muJetC_muon1_errposy1stpix[Det_mu1_muJetC]/F");
  m_ttree->Branch("muJetC_muon1_errposz1stpix", &b_muJetC_muon1_errposz1stpix, "muJetC_muon1_errposz1stpix[Det_mu1_muJetC]/F");

  m_ttree->Branch("muJetC_muon2_errposx1stpix", &b_muJetC_muon2_errposx1stpix, "muJetC_muon2_errposx1stpix[Det_mu2_muJetC]/F");
  m_ttree->Branch("muJetC_muon2_errposy1stpix", &b_muJetC_muon2_errposy1stpix, "muJetC_muon2_errposy1stpix[Det_mu2_muJetC]/F");
  m_ttree->Branch("muJetC_muon2_errposz1stpix", &b_muJetC_muon2_errposz1stpix, "muJetC_muon2_errposz1stpix[Det_mu2_muJetC]/F");

  m_ttree->Branch("muJetF_muon1_errposx1stpix", &b_muJetF_muon1_errposx1stpix, "muJetF_muon1_errposx1stpix[Det_mu1_muJetF]/F");
  m_ttree->Branch("muJetF_muon1_errposy1stpix", &b_muJetF_muon1_errposy1stpix, "muJetF_muon1_errposy1stpix[Det_mu1_muJetF]/F");
  m_ttree->Branch("muJetF_muon1_errposz1stpix", &b_muJetF_muon1_errposz1stpix, "muJetF_muon1_errposz1stpix[Det_mu1_muJetF]/F");

  m_ttree->Branch("muJetF_muon2_errposx1stpix", &b_muJetF_muon2_errposx1stpix, "muJetF_muon2_errposx1stpix[Det_mu2_muJetF]/F");
  m_ttree->Branch("muJetF_muon2_errposy1stpix", &b_muJetF_muon2_errposy1stpix, "muJetF_muon2_errposy1stpix[Det_mu2_muJetF]/F");
  m_ttree->Branch("muJetF_muon2_errposz1stpix", &b_muJetF_muon2_errposz1stpix, "muJetF_muon2_errposz1stpix[Det_mu2_muJetF]/F");


  m_ttree->Branch("muJetC_muon1_posx1stpix_lastmeas", &b_muJetC_muon1_posx1stpix_lastmeas, "muJetC_muon1_posx1stpix_lastmeas[Det_mu1_muJetC]/F");
  m_ttree->Branch("muJetC_muon1_posy1stpix_lastmeas", &b_muJetC_muon1_posy1stpix_lastmeas, "muJetC_muon1_posy1stpix_lastmeas[Det_mu1_muJetC]/F");

  m_ttree->Branch("muJetC_muon2_posx1stpix_lastmeas", &b_muJetC_muon2_posx1stpix_lastmeas, "muJetC_muon2_posx1stpix_lastmeas[Det_mu2_muJetC]/F");
  m_ttree->Branch("muJetC_muon2_posy1stpix_lastmeas", &b_muJetC_muon2_posy1stpix_lastmeas, "muJetC_muon2_posy1stpix_lastmeas[Det_mu2_muJetC]/F");

  m_ttree->Branch("muJetF_muon1_posx1stpix_lastmeas", &b_muJetF_muon1_posx1stpix_lastmeas, "muJetF_muon1_posx1stpix_lastmeas[Det_mu1_muJetF]/F");
  m_ttree->Branch("muJetF_muon1_posy1stpix_lastmeas", &b_muJetF_muon1_posy1stpix_lastmeas, "muJetF_muon1_posy1stpix_lastmeas[Det_mu1_muJetF]/F");

  m_ttree->Branch("muJetF_muon2_posx1stpix_lastmeas", &b_muJetF_muon2_posx1stpix_lastmeas, "muJetF_muon2_posx1stpix_lastmeas[Det_mu2_muJetF]/F");
  m_ttree->Branch("muJetF_muon2_posy1stpix_lastmeas", &b_muJetF_muon2_posy1stpix_lastmeas, "muJetF_muon2_posy1stpix_lastmeas[Det_mu2_muJetF]/F");


  m_ttree->Branch("mindist_hit_mu1_muJetC", &b_mindist_hit_mu1_muJetC, "mindist_hit_mu1_muJetC[Det_mu1_muJetC]/F");
  m_ttree->Branch("mindist_hit_mu2_muJetC", &b_mindist_hit_mu2_muJetC, "mindist_hit_mu2_muJetC[Det_mu2_muJetC]/F");
  m_ttree->Branch("mindist_hit_mu1_muJetF", &b_mindist_hit_mu1_muJetF, "mindist_hit_mu1_muJetF[Det_mu1_muJetF]/F");
  m_ttree->Branch("mindist_hit_mu2_muJetF", &b_mindist_hit_mu2_muJetF, "mindist_hit_mu2_muJetF[Det_mu2_muJetF]/F");


  m_ttree->Branch("pixelhit_mu1_muJetC_posx",&b_pixelhit_mu1_muJetC_posx,"pixelhit_mu1_muJetC_posx[comphits_mu1_muJetC]/F");
  m_ttree->Branch("pixelhit_mu1_muJetC_posy",&b_pixelhit_mu1_muJetC_posy,"pixelhit_mu1_muJetC_posy[comphits_mu1_muJetC]/F");
  m_ttree->Branch("pixelhit_mu1_muJetC_posz",&b_pixelhit_mu1_muJetC_posz,"pixelhit_mu1_muJetC_posz[comphits_mu1_muJetC]/F");

  m_ttree->Branch("pixelhit_mu2_muJetC_posx",&b_pixelhit_mu2_muJetC_posx,"pixelhit_mu2_muJetC_posx[comphits_mu2_muJetC]/F");
  m_ttree->Branch("pixelhit_mu2_muJetC_posy",&b_pixelhit_mu2_muJetC_posy,"pixelhit_mu2_muJetC_posy[comphits_mu2_muJetC]/F");
  m_ttree->Branch("pixelhit_mu2_muJetC_posz",&b_pixelhit_mu2_muJetC_posz,"pixelhit_mu2_muJetC_posz[comphits_mu2_muJetC]/F");

  m_ttree->Branch("pixelhit_mu1_muJetF_posx",&b_pixelhit_mu1_muJetF_posx,"pixelhit_mu1_muJetF_posx[comphits_mu1_muJetF]/F");
  m_ttree->Branch("pixelhit_mu1_muJetF_posy",&b_pixelhit_mu1_muJetF_posy,"pixelhit_mu1_muJetF_posy[comphits_mu1_muJetF]/F");
  m_ttree->Branch("pixelhit_mu1_muJetF_posz",&b_pixelhit_mu1_muJetF_posz,"pixelhit_mu1_muJetF_posz[comphits_mu1_muJetF]/F");

  m_ttree->Branch("pixelhit_mu2_muJetF_posx",&b_pixelhit_mu2_muJetF_posx,"pixelhit_mu2_muJetF_posx[comphits_mu2_muJetF]/F");
  m_ttree->Branch("pixelhit_mu2_muJetF_posy",&b_pixelhit_mu2_muJetF_posy,"pixelhit_mu2_muJetF_posy[comphits_mu2_muJetF]/F");
  m_ttree->Branch("pixelhit_mu2_muJetF_posz",&b_pixelhit_mu2_muJetF_posz,"pixelhit_mu2_muJetF_posz[comphits_mu2_muJetF]/F");


  m_ttree->Branch("pixelhit_mu1_muJetC_errposx",&b_pixelhit_mu1_muJetC_errposx,"pixelhit_mu1_muJetC_errposx[comphits_mu1_muJetC]/F");
  m_ttree->Branch("pixelhit_mu1_muJetC_errposy",&b_pixelhit_mu1_muJetC_errposy,"pixelhit_mu1_muJetC_errposy[comphits_mu1_muJetC]/F");
  m_ttree->Branch("pixelhit_mu1_muJetC_errposz",&b_pixelhit_mu1_muJetC_errposz,"pixelhit_mu1_muJetC_errposz[comphits_mu1_muJetC]/F");

  m_ttree->Branch("pixelhit_mu2_muJetC_errposx",&b_pixelhit_mu2_muJetC_errposx,"pixelhit_mu2_muJetC_errposx[comphits_mu2_muJetC]/F");
  m_ttree->Branch("pixelhit_mu2_muJetC_errposy",&b_pixelhit_mu2_muJetC_errposy,"pixelhit_mu2_muJetC_errposy[comphits_mu2_muJetC]/F");
  m_ttree->Branch("pixelhit_mu2_muJetC_errposz",&b_pixelhit_mu2_muJetC_errposz,"pixelhit_mu2_muJetC_errposz[comphits_mu2_muJetC]/F");

  m_ttree->Branch("pixelhit_mu1_muJetF_errposx",&b_pixelhit_mu1_muJetF_errposx,"pixelhit_mu1_muJetF_errposx[comphits_mu1_muJetF]/F");
  m_ttree->Branch("pixelhit_mu1_muJetF_errposy",&b_pixelhit_mu1_muJetF_errposy,"pixelhit_mu1_muJetF_errposy[comphits_mu1_muJetF]/F");
  m_ttree->Branch("pixelhit_mu1_muJetF_errposz",&b_pixelhit_mu1_muJetF_errposz,"pixelhit_mu1_muJetF_errposz[comphits_mu1_muJetF]/F");

  m_ttree->Branch("pixelhit_mu2_muJetF_errposx",&b_pixelhit_mu2_muJetF_errposx,"pixelhit_mu2_muJetF_errposx[comphits_mu2_muJetF]/F");
  m_ttree->Branch("pixelhit_mu2_muJetF_errposy",&b_pixelhit_mu2_muJetF_errposy,"pixelhit_mu2_muJetF_errposy[comphits_mu2_muJetF]/F");
  m_ttree->Branch("pixelhit_mu2_muJetF_errposz",&b_pixelhit_mu2_muJetF_errposz,"pixelhit_mu2_muJetF_errposz[comphits_mu2_muJetF]/F");


  m_ttree->Branch("hitrecover_mj2_r001",&b_hitrecover_mj2_r001,"hitrecover_mj2_r001/I");
  m_ttree->Branch("hitrecover_mj2_r005",&b_hitrecover_mj2_r005,"hitrecover_mj2_r005/I");
  m_ttree->Branch("hitrecover_mj2_r01",&b_hitrecover_mj2_r01,"hitrecover_mj2_r01/I");
  m_ttree->Branch("hitrecover_mj2_r03",&b_hitrecover_mj2_r03,"hitrecover_mj2_r03/I");
  m_ttree->Branch("hitrecover_mj2_r05",&b_hitrecover_mj2_r05,"hitrecover_mj2_r05/I");
  m_ttree->Branch("hitrecover_mj2_r1",&b_hitrecover_mj2_r1,"hitrecover_mj2_r1/I");

  m_ttree->Branch("hitrecover_mj1_r001",&b_hitrecover_mj1_r001,"hitrecover_mj1_r001/I");
  m_ttree->Branch("hitrecover_mj1_r005",&b_hitrecover_mj1_r005,"hitrecover_mj1_r005/I");
  m_ttree->Branch("hitrecover_mj1_r01",&b_hitrecover_mj1_r01,"hitrecover_mj1_r01/I");
  m_ttree->Branch("hitrecover_mj1_r03",&b_hitrecover_mj1_r03,"hitrecover_mj1_r03/I");
  m_ttree->Branch("hitrecover_mj1_r05",&b_hitrecover_mj1_r05,"hitrecover_mj1_r05/I");
  m_ttree->Branch("hitrecover_mj1_r1",&b_hitrecover_mj1_r1,"hitrecover_mj1_r1/I");

  m_ttree->Branch("hitrecover_mj12_r001",&b_hitrecover_mj12_r001,"hitrecover_mj12_r001/I");
  m_ttree->Branch("hitrecover_mj12_r005",&b_hitrecover_mj12_r005,"hitrecover_mj12_r005/I");
  m_ttree->Branch("hitrecover_mj12_r01",&b_hitrecover_mj12_r01,"hitrecover_mj12_r01/I");
  m_ttree->Branch("hitrecover_mj12_r03",&b_hitrecover_mj12_r03,"hitrecover_mj12_r03/I");
  m_ttree->Branch("hitrecover_mj12_r05",&b_hitrecover_mj12_r05,"hitrecover_mj12_r05/I");
  m_ttree->Branch("hitrecover_mj12_r1",&b_hitrecover_mj12_r1,"hitrecover_mj12_r1/I");


  // m_ttree->Branch("dist_muon_muJetC",&b_dist_muon_muJetC,"dist_muon_muJetC/F");
  // m_ttree->Branch("dist_muon_muJetF",&b_dist_muon_muJetF,"dist_muon_muJetF/F");


}

// ------------ method called once each job just after ending the event loop  ------------
void 
AnalysisRun2::endJob() 
{

  cout<<" Total number of events   "<<nevents<<endl;

  
}

// ------------ method called when starting to processes a run  ------------
/*
  void 
  AnalysisRun2::beginRun(edm::Run const&, edm::EventSetup const&)
  {
  }
*/

// ------------ method called when ending the processing of a run  ------------
/*
  void 
  AnalysisRun2::endRun(edm::Run const&, edm::EventSetup const&)
  {
  }
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
  void 
  AnalysisRun2::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
  {
  }
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
  void 
  AnalysisRun2::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
  {
  }
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
AnalysisRun2::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(AnalysisRun2);
