#include "MuJetAnalysis/AnalysisTools/interface/PixelHitRecovery.h"

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
#include <FWCore/Utilities/interface/ESInputTag.h>

#include <DataFormats/TrackingRecHit/interface/InvalidTrackingRecHit.h>
#include "DataFormats/Common/interface/AssociationMap.h"
#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandMatchMap.h"
#include "DataFormats/TrackingRecHit/interface/TrackingRecHit.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"

#include "RecoTracker/TrackProducer/interface/TrackProducerBase.h"
#include "RecoTracker/Record/interface/NavigationSchoolRecord.h"
#include <RecoTracker/MeasurementDet/interface/MeasurementTracker.h>
//#include "RecoTracker/MeasurementDet/interface/MeasurementTrackerEvent.h"
#include "RecoTracker/Record/interface/CkfComponentsRecord.h"

#include "TrackingTools/Records/interface/TrackingComponentsRecord.h" 
#include "TrackingTools/TransientTrackingRecHit/interface/TransientTrackingRecHit.h"
#include "TrackingTools/TrackFitters/interface/TrajectoryFitterRecord.h" 
#include "TrackingTools/Records/interface/TransientRecHitRecord.h" 
#include "TrackingTools/TrackFitters/interface/TrajectoryFitter.h"
#include "TrackingTools/GeomPropagators/interface/Propagator.h"
#include "TrackingTools/DetLayers/interface/NavigationSchool.h"
//#include "TrackingTools/DetLayers/interface/NavigationSetter.h"
//#include "RecoTracker/TkNavigation/interface/SimpleNavigationSchool.h"

//#include "RecoTracker/SiTrackerMRHTools/interface/SiTrackerMultiRecHitUpdator.h"
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

#include "DataFormats/VertexReco/interface/VertexFwd.h"

PixelHitRecovery::PixelHitRecovery(const edm::Event& iEvent, 
				   const edm::EventSetup& iSetup, 
				   const edm::ParameterSet& iConfig)
{
  edm::ESHandle<MeasurementTracker> theMeasTk;
  std::string measTkName = iConfig.getParameter<std::string>("MeasurementTracker");
  iSetup.get<CkfComponentsRecord>().get(measTkName,theMeasTk);
  
  // This is also needed to extrapolate amongst the tracker layers.
  edm::ESHandle<NavigationSchool> theSchool;
  iSetup.get<NavigationSchoolRecord>().get("SimpleNavigationSchool",theSchool);
  // NavigationSetter junk(*theSchool);
  
  edm::ESHandle<Propagator> thePropagator;
  std::string propagatorName = iConfig.getParameter<std::string>("Propagator");
  iSetup.get<TrackingComponentsRecord>().get(propagatorName,thePropagator);
  
  // very very relaxed cuts to capture all nearby hits
  Chi2MeasurementEstimator estimator(1.e10,100.);
  
  // to find compatible layers
  Chi2MeasurementEstimator estimator2(30,10.);  
  
  // Refitted collection of tracks
  edm::Handle<reco::TrackCollection> tracksrf;  
  iEvent.getByLabel("TrackRefitter",tracksrf); 
}

PixelHitRecovery::~PixelHitRecovery()
{}

void
PixelHitRecovery::run()
{
	// Int_t indxtrkmj1_validhit[2];
	// Int_t indxtrkmj2_validhit[2];

	// indxtrkmj1_validhit[0]=-100000;
	// indxtrkmj1_validhit[1]=-100000;

	// indxtrkmj2_validhit[0]=-100000;
	// indxtrkmj2_validhit[1]=-100000;


	// Int_t indxtrkmj1[2];
	// Int_t indxtrkmj2[2];

	// indxtrkmj1[0]=-100000;
	// indxtrkmj1[1]=-100000;

	// indxtrkmj2[0]=-100000;
	// indxtrkmj2[1]=-100000;

	// // Int_t indxtrkmj1_gt[2]={-100000};
	// // Int_t indxtrkmj2_gt[2]={-100000};

	// if(m_antraj==1){

	//   //=================  Calling methods for propagation between layers====================//
	//   edm::ESHandle<MeasurementTracker> theMeasTk;
	//   std::string measTkName = param_.getParameter<std::string>("MeasurementTracker");
	//   iSetup.get<CkfComponentsRecord>().get(measTkName,theMeasTk);
	//   theMeasTk->update(iEvent);
	  
	//   // This is also needed to extrapolate amongst the tracker layers.
	//   edm::ESHandle<NavigationSchool> theSchool;
	//   iSetup.get<NavigationSchoolRecord>().get("SimpleNavigationSchool",theSchool);
	//   NavigationSetter junk(*theSchool);
	  
	//   edm::ESHandle<Propagator> thePropagator;
	//   std::string propagatorName = param_.getParameter<std::string>("Propagator");
	//   iSetup.get<TrackingComponentsRecord>().get(propagatorName,thePropagator);
	  
	//   Chi2MeasurementEstimator estimator(1.e10,100.);  // very very relaxed cuts to capture all nearby hits
	//   Chi2MeasurementEstimator estimator2(30,10.);  // to find compatible layers
	  
	//   //============================================================================================//
	  

	// Handle<reco::TrackCollection> tracksrf;  //============== Refitted collection of tracks
	// iEvent.getByLabel("TrackRefitter",tracksrf); 
	
	// vector<Float_t> mincharge;
	// vector<Float_t> mintheta;
	// vector<Float_t> minqoverpt;
	// vector<Float_t> minphi;
	// vector<Float_t> mindxy;
 	// vector<Float_t> mindz;
	
	// std::vector<std::pair<Int_t,Float_t> > minchi2_mu1_muJetC;
	// std::vector<std::pair<Int_t,Float_t> > minchi2_mu2_muJetC;
	// std::vector<std::pair<Int_t,Float_t> > minchi2_mu1_muJetF;
	// std::vector<std::pair<Int_t,Float_t> > minchi2_mu2_muJetF;
	


	
	// //====== matching selected muons to refitted tracks and asking for hits in 1st layer (barrel or endcap)
	
	// for(uint32_t k=0;k<2;k++){
	  
	//   mtrack_pt[k] = muJetC->muon(k)->innerTrack()->pt();
	//   mtrack_charge[k] = muJetC->muon(k)->innerTrack()->charge();
	//   mtrack_qoverp[k] = muJetC->muon(k)->innerTrack()->qoverp();
	//   mtrack_theta[k] = muJetC->muon(k)->innerTrack()->theta();
	//   mtrack_phi[k] = muJetC->muon(k)->innerTrack()->phi();
	//   mtrack_dxy[k] = muJetC->muon(k)->innerTrack()->dxy();
	//   mtrack_dz[k] = muJetC->muon(k)->innerTrack()->dz();
	  
	//   mtrack_errpt[k] = muJetC->muon(k)->innerTrack()->ptError();
	//   mtrack_errcharge[k] = muJetC->muon(k)->innerTrack()->charge();
	//   mtrack_errqoverp[k] = muJetC->muon(k)->innerTrack()->qoverpError();
	//   mtrack_errtheta[k] = muJetC->muon(k)->innerTrack()->thetaError();
	//   mtrack_errphi[k] = muJetC->muon(k)->innerTrack()->phiError();
	//   mtrack_errdxy[k] = muJetC->muon(k)->innerTrack()->dxyError();
	//   mtrack_errdz[k] = muJetC->muon(k)->innerTrack()->dzError();
	  

	//   Int_t counter_match=0;
	//   Int_t counter_track=0;
	  
	//   for (reco::TrackCollection::const_iterator trackrf = tracksrf->begin(); trackrf != tracksrf->end(); ++trackrf) {
	    
	//     if(trackrf->pt()>3.0 && fabs(trackrf->eta())<2.5){
	      
	      
	//       if(k==1){
	// 	std::pair<Int_t,Float_t> temp_mu2_muJetC;
	// 	std::pair<Int_t,Float_t> temp_mu2_muJetF;
		
	// 	temp_mu2_muJetC.first = counter_match;
	// 	temp_mu2_muJetF.first = counter_match;
		
		
	// 	temp_mu2_muJetC.second = pow(cotan(muJetC->muon(k)->innerTrack()->theta()) - cotan(trackrf->theta()),2)/pow(1.23140e-07,2) + 
	// 	  pow((muJetC->muon(k)->innerTrack()->charge()/muJetC->muon(k)->innerTrack()->pt()) - (trackrf->charge()/trackrf->pt()),2)/pow(1.76958e-07,2) +
	// 	  pow(My_dPhi(muJetC->muon(k)->innerTrack()->phi(),trackrf->phi()),2)/pow(2.98078e-08,2) + 
	// 	  pow(muJetC->muon(k)->innerTrack()->dxy() - trackrf->dxy(),2)/pow(3.24229e-07,2) + 
	// 	  pow(muJetC->muon(k)->innerTrack()->dz() - trackrf->dz(),2)/pow(8.72624e-07,2);
		
	// 	temp_mu2_muJetF.second = pow(cotan(muJetF->muon(k)->innerTrack()->theta()) - cotan(trackrf->theta()),2)/pow(1.23140e-07,2) + 
	// 	  pow((muJetF->muon(k)->innerTrack()->charge()/muJetF->muon(k)->innerTrack()->pt()) - (trackrf->charge()/trackrf->pt()),2)/pow(1.76958e-07,2) +
	// 	  pow(My_dPhi(muJetF->muon(k)->innerTrack()->phi(),trackrf->phi()),2)/pow(2.98078e-08,2) + 
	// 	  pow(muJetF->muon(k)->innerTrack()->dxy() - trackrf->dxy(),2)/pow(3.24229e-07,2) + 
	// 	  pow(muJetF->muon(k)->innerTrack()->dz() - trackrf->dz(),2)/pow(8.72624e-07,2);
		


	// 	// std::cout<<" track    "<<counter_match<<"    chi2  muon2 muJetC   "<< temp_mu2_muJetC.second <<std::endl;
	// 	// std::cout<<" track    "<<counter_match<<"    chi2  muon2 muJetF   "<< temp_mu2_muJetF.second <<std::endl;


	// 	minchi2_mu2_muJetC.push_back(temp_mu2_muJetC);
	// 	minchi2_mu2_muJetF.push_back(temp_mu2_muJetF);

	// 	muJetC_muon2_track_diffcharge[counter_track] = muJetC->muon(k)->innerTrack()->charge() - trackrf->charge();
	// 	muJetC_muon2_track_diffpt[counter_track] = muJetC->muon(k)->innerTrack()->pt() - trackrf->pt();
	// 	muJetC_muon2_track_diffqoverp[counter_track] = muJetC->muon(k)->innerTrack()->qoverp() - trackrf->qoverp();
	// 	muJetC_muon2_track_difftheta[counter_track] = muJetC->muon(k)->innerTrack()->theta() - trackrf->theta();
	// 	muJetC_muon2_track_diffphi[counter_track] = muJetC->muon(k)->innerTrack()->phi() - trackrf->phi();
	// 	muJetC_muon2_track_diffdxy[counter_track] = muJetC->muon(k)->innerTrack()->dxy() - trackrf->dxy();
	// 	muJetC_muon2_track_diffdz[counter_track] = muJetC->muon(k)->innerTrack()->dz() - trackrf->dz();
	      
	//       }
	      
	      
	//       if(k==0){
		
	// 	std::pair<Int_t,Float_t> temp_mu1_muJetC;
	// 	std::pair<Int_t,Float_t> temp_mu1_muJetF;
		
	// 	temp_mu1_muJetC.first = counter_match;
	// 	temp_mu1_muJetF.first = counter_match;
		

	// 	temp_mu1_muJetC.second = pow(cotan(muJetC->muon(k)->innerTrack()->theta()) - cotan(trackrf->theta()),2)/pow(1.23140e-07,2) + 
	// 	  pow((muJetC->muon(k)->innerTrack()->charge()/muJetC->muon(k)->innerTrack()->pt()) - (trackrf->charge()/trackrf->pt()),2)/pow(1.76958e-07,2) +
	// 	  pow(My_dPhi(muJetC->muon(k)->innerTrack()->phi(),trackrf->phi()),2)/pow(2.98078e-08,2) + 
	// 	  pow(muJetC->muon(k)->innerTrack()->dxy() - trackrf->dxy(),2)/pow(3.24229e-07,2) + 
	// 	  pow(muJetC->muon(k)->innerTrack()->dz() - trackrf->dz(),2)/pow(8.72624e-07,2);
		
	// 	temp_mu1_muJetF.second = pow(cotan(muJetF->muon(k)->innerTrack()->theta()) - cotan(trackrf->theta()),2)/pow(1.23140e-07,2) + 
	// 	  pow((muJetF->muon(k)->innerTrack()->charge()/muJetF->muon(k)->innerTrack()->pt()) - (trackrf->charge()/trackrf->pt()),2)/pow(1.76958e-07,2) +
	// 	  pow(My_dPhi(muJetF->muon(k)->innerTrack()->phi(),trackrf->phi()),2)/pow(2.98078e-08,2) + 
	// 	  pow(muJetF->muon(k)->innerTrack()->dxy() - trackrf->dxy(),2)/pow(3.24229e-07,2) + 
	// 	  pow(muJetF->muon(k)->innerTrack()->dz() - trackrf->dz(),2)/pow(8.72624e-07,2);


	// 	// std::cout<<" track    "<<counter_match<<"    chi2  muon1 muJetC   "<< temp_mu1_muJetC.second <<std::endl;
	// 	// std::cout<<" track    "<<counter_match<<"    chi2  muon1 muJetF   "<< temp_mu1_muJetF.second <<std::endl;

	// 	minchi2_mu1_muJetC.push_back(temp_mu1_muJetC);
	// 	minchi2_mu1_muJetF.push_back(temp_mu1_muJetF);

	// 	//======================
		
	// 	mintheta.push_back( cotan(muJetC->muon(k)->innerTrack()->theta()) - cotan(trackrf->theta()) );
	// 	minqoverpt.push_back((muJetC->muon(k)->innerTrack()->charge()/muJetC->muon(k)->innerTrack()->pt())  -  (trackrf->charge()/trackrf->pt())  );
	// 	minphi.push_back(  My_dPhi(muJetC->muon(k)->innerTrack()->phi(),trackrf->phi()) );
	// 	mindxy.push_back(muJetC->muon(k)->innerTrack()->dxy() - trackrf->dxy() );
	// 	mindz.push_back( muJetC->muon(k)->innerTrack()->dz() - trackrf->dz() );
	// 	mincharge.push_back( muJetC->muon(k)->innerTrack()->charge() - trackrf->charge());
		
		
	// 	muJetC_muon1_track_diffpt[counter_track] = muJetC->muon(k)->innerTrack()->pt() - trackrf->pt();
	// 	muJetC_muon1_track_diffcharge[counter_track] = muJetC->muon(k)->innerTrack()->charge() - trackrf->charge();
	// 	muJetC_muon1_track_diffqoverp[counter_track] = (muJetC->muon(k)->innerTrack()->charge()/muJetC->muon(k)->innerTrack()->pt()) - (trackrf->charge()/trackrf->pt());
	// 	muJetC_muon1_track_difftheta[counter_track] = cotan(muJetC->muon(k)->innerTrack()->theta()) - cotan(trackrf->theta());
	// 	muJetC_muon1_track_diffphi[counter_track] =  My_dPhi(muJetC->muon(k)->innerTrack()->phi(),trackrf->phi());
	// 	muJetC_muon1_track_diffdxy[counter_track] = muJetC->muon(k)->innerTrack()->dxy() - trackrf->dxy();
	// 	muJetC_muon1_track_diffdz[counter_track] = muJetC->muon(k)->innerTrack()->dz() - trackrf->dz();
		
	// 	muJetC_muon1_track_diffchi2[counter_track] = pow(cotan(muJetC->muon(k)->innerTrack()->theta()) - cotan(trackrf->theta()),2)/pow(1.23140e-07,2) + 
	// 	  pow((muJetC->muon(k)->innerTrack()->charge()/muJetC->muon(k)->innerTrack()->pt()) - (trackrf->charge()/trackrf->pt()),2)/pow(1.76958e-07,2) +
	// 	  pow(My_dPhi(muJetC->muon(k)->innerTrack()->phi(),trackrf->phi()),2)/pow(2.98078e-08,2) + 
	// 	  pow(muJetC->muon(k)->innerTrack()->dxy() - trackrf->dxy(),2)/pow(3.24229e-07,2) + 
	// 	  pow(muJetC->muon(k)->innerTrack()->dz() - trackrf->dz(),2)/pow(8.72624e-07,2);
		
		
		
	// 	muJetC_muon1_track_diffchi2theta[counter_track] = pow(cotan(muJetC->muon(k)->innerTrack()->theta()) - cotan(trackrf->theta()),2)/pow(1.23140e-07,2);
	// 	muJetC_muon1_track_diffchi2qoverpt[counter_track] = pow((muJetC->muon(k)->innerTrack()->charge()/muJetC->muon(k)->innerTrack()->pt()) - (trackrf->charge()/trackrf->pt()),2)/pow(1.76958e-07,2);
	// 	muJetC_muon1_track_diffchi2phi[counter_track] = pow(My_dPhi(muJetC->muon(k)->innerTrack()->phi(),trackrf->phi()),2)/pow(2.98078e-08,2); 
	// 	muJetC_muon1_track_diffchi2dxy[counter_track] = pow(muJetC->muon(k)->innerTrack()->dxy() - trackrf->dxy(),2)/pow(3.24229e-07,2);
	// 	muJetC_muon1_track_diffchi2dz[counter_track] = pow(muJetC->muon(k)->innerTrack()->dz() - trackrf->dz(),2)/pow(8.72624e-07,2);
		
	// 	b_track_pt[counter_track] = trackrf->pt();
	// 	b_track_charge[counter_track] = trackrf->charge();
	// 	b_track_qoverp[counter_track] = trackrf->qoverp();
	// 	b_track_theta[counter_track] = trackrf->theta();
	// 	b_track_phi[counter_track] = trackrf->phi();
	// 	b_track_dxy[counter_track] = trackrf->dxy();
	// 	b_track_dz[counter_track] = trackrf->dz();
		
	// 	b_track_errpt[counter_track] = trackrf->ptError();
	// 	b_track_errcharge[counter_track] = trackrf->charge();
	// 	b_track_errqoverp[counter_track] = trackrf->qoverpError();
	// 	b_track_errtheta[counter_track] = trackrf->thetaError();
	// 	b_track_errphi[counter_track] = trackrf->phiError();
	// 	b_track_errdxy[counter_track] = trackrf->dxyError();
	// 	b_track_errdz[counter_track] = trackrf->dzError();
	//       }
	      
	      
	//       // if(sameTrackRF(&*trackrf,&*(muJetC->muon(k)->innerTrack()))){
	      
	//       // // std::cout<<" charge   "<<track->charge()<<std::endl;
	//       // // std::cout<<" qoverp   "<<track->qoverp()<<std::endl;
	//       // // std::cout<<" theta    "<<track->theta()<<std::endl;
	//       // // std::cout<<" phi      "<<track->phi()<<std::endl;
	//       // // std::cout<<" dxy      "<<track->dxy()<<std::endl;

	//       // // std::cout<<" charge m   "<<muJetC->muon(k)->innerTrack()->charge()<<std::endl;
	//       // // std::cout<<" qoverp m  "<<muJetC->muon(k)->innerTrack()->qoverp()<<std::endl;
	//       // // std::cout<<" theta m   "<<muJetC->muon(k)->innerTrack()->theta()<<std::endl;
	//       // // std::cout<<" phi   m   "<<muJetC->muon(k)->innerTrack()->phi()<<std::endl;
	//       // // std::cout<<" dxy   m   "<<muJetC->muon(k)->innerTrack()->dxy()<<std::endl;



	//       // //	    if(sameTrack(&*track,&*(muJetC->muon(k)->innerTrack()))){
	//       //   indxtrkmj1[k] = counter_match;
	//       //   if(k==0) b_match_mu1track_muJetC=1;
	//       //   if(k==1) b_match_mu2track_muJetC=1;

	//       //   if(m_debug>10){
	//       // 	if(k==0) std::cout<<"  match mj1m0 muon track with indx   "<<counter_match<<" track pT  "<<trackrf->pt()<<" muon track pT  "<<muJetC->muon(k)->innerTrack()->pt()<<std::endl;
	//       // 	if(k==1) std::cout<<"  match mj1m1 muon track with indx   "<<counter_match<<" track pT  "<<trackrf->pt()<<" muon track pT  "<<muJetC->muon(k)->innerTrack()->pt()<<std::endl;

	//       // 	if(k==0) std::cout<<"  match mj1m0 muon track with indx   "<<counter_match<<" track 1/pT  "<<1/trackrf->pt()<<" muon track 1/pT  "<<1/muJetC->muon(k)->innerTrack()->pt()<<std::endl;
	//       // 	if(k==1) std::cout<<"  match mj1m1 muon track with indx   "<<counter_match<<" track 1/pT  "<<1/trackrf->pt()<<" muon track 1/pT  "<<1/muJetC->muon(k)->innerTrack()->pt()<<std::endl;

	//       // 	if(k==0) std::cout<<"  match mj1m0 muon track with indx   "<<counter_match<<" track eta  "<<trackrf->eta()<<" muon track pT  "<<muJetC->muon(k)->innerTrack()->eta()<<std::endl;
	//       // 	if(k==1) std::cout<<"  match mj1m1 muon track with indx   "<<counter_match<<" track eta  "<<trackrf->eta()<<" muon track pT  "<<muJetC->muon(k)->innerTrack()->eta()<<std::endl;


	//       // 	if(k==0) std::cout<<"  match mj1m0 muon track with indx   "<<counter_match<<" track vx  "<<trackrf->vx()<<" muon track vx  "<<muJetC->muon(k)->innerTrack()->vx()<<std::endl;
	//       // 	if(k==1) std::cout<<"  match mj1m1 muon track with indx   "<<counter_match<<" track vx  "<<trackrf->vx()<<" muon track vx  "<<muJetC->muon(k)->innerTrack()->vx()<<std::endl;

	//       // 	if(k==0) std::cout<<"  match mj1m0 muon track with indx   "<<counter_match<<" track vx  "<<trackrf->vy()<<" muon track vx  "<<muJetC->muon(k)->innerTrack()->vy()<<std::endl;
	//       // 	if(k==1) std::cout<<"  match mj1m1 muon track with indx   "<<counter_match<<" track vx  "<<trackrf->vy()<<" muon track vx  "<<muJetC->muon(k)->innerTrack()->vy()<<std::endl;

	//       // 	if(k==0) std::cout<<"  match mj1m0 muon track with indx   "<<counter_match<<" track vx  "<<trackrf->vz()<<" muon track vx  "<<muJetC->muon(k)->innerTrack()->vz()<<std::endl;
	//       // 	if(k==1) std::cout<<"  match mj1m1 muon track with indx   "<<counter_match<<" track vx  "<<trackrf->vz()<<" muon track vx  "<<muJetC->muon(k)->innerTrack()->vz()<<std::endl;
	//       //   }
	//       //   const reco::HitPattern& p = trackrf->hitPattern();
	//       //   if(p.hasValidHitInFirstPixelEndcap() || p.hasValidHitInFirstPixelBarrel()){
	//       // 	//		dim1_hit=true;
	//       // 	indxtrkmj1_validhit[k] = 1;
	//       // 	b_muJetC_hitpix[k] = 1;
	//       //   }
	//       // }
	  
	//       // if(sameTrackRF(&*trackrf,&*(muJetF->muon(k)->innerTrack()))){
	//       // //	    if(sameTrack(&*track,&*(muJetF->muon(k)->innerTrack()))){
	//       //   indxtrkmj2[k] = counter_match;
	//       //   if(k==0) b_match_mu1track_muJetF=1;
	//       //   if(k==1) b_match_mu2track_muJetF=1;
	//       //   if(m_debug>10){
	//       // 	if(k==0) std::cout<<"  match mj2m0 muon track with indx   "<<counter_match<<" track pT  "<<trackrf->pt()<<std::endl;

	//       //   }
	//       //   const reco::HitPattern& p = trackrf->hitPattern();
	//       //   if(p.hasValidHitInFirstPixelEndcap() || p.hasValidHitInFirstPixelBarrel()){
	//       // 	//		dim2_hit=true;
	//       // 	indxtrkmj2_validhit[k] = 1;
	//       // 	b_muJetF_hitpix[k] = 1;
	//       //   }
	//       // }
	//       counter_track++;
	//     }
	//     counter_match++;
	//   }
	//   if(k==0) b_ntracks = counter_track;
	// }

	// std::sort(mintheta.begin(),mintheta.end(),order);
	// std::sort(minqoverpt.begin(),minqoverpt.end(),order);
	// std::sort(minphi.begin(),minphi.end(),order);
	// std::sort(mindxy.begin(),mindxy.end(),order);
	// std::sort(mindz.begin(),mindz.end(),order);
	// std::sort(mincharge.begin(),mincharge.end(),order);
	
	// muJetC_muon1_track_mincharge  = mincharge[0];
	// muJetC_muon1_track_minqoverpt = minqoverpt[0];
	// muJetC_muon1_track_mintheta   = mintheta[0];
	// muJetC_muon1_track_minphi     = minphi[0];
	// muJetC_muon1_track_mindxy     = mindxy[0];
	// muJetC_muon1_track_mindz      = mindz[0];


	// // muJetC_muon1_track_minchi2 = pow(mintheta[0],2)/pow(1.23140e-07,2) + pow(minqoverpt[0],2)/pow(1.76958e-07,2) + 
	// //   pow(minphi[0],2)/pow(2.98078e-08,2) + pow(mindxy[0],2)/pow(3.24229e-07,2) + pow(mindz[0],2)/pow(8.72624e-07,2);
	

	// muJetC_muon1_track_minchi2theta   = pow(mintheta[0],2)/pow(1.23140e-07,2);
	// muJetC_muon1_track_minchi2qoverpt = pow(minqoverpt[0],2)/pow(1.76958e-07,2);
	// muJetC_muon1_track_minchi2phi     = pow(minphi[0],2)/pow(2.98078e-08,2);
	// muJetC_muon1_track_minchi2dxy     =  pow(mindxy[0],2)/pow(3.24229e-07,2);
	// muJetC_muon1_track_minchi2dz      = pow(mindz[0],2)/pow(8.72624e-07,2);

	// mintheta.clear();
	// minqoverpt.clear();
	// minphi.clear();
	// mindxy.clear();
	// mindz.clear();
	// mincharge.clear();

	// //==================================================================================================
	
	// std::sort(minchi2_mu1_muJetC.begin(),minchi2_mu1_muJetC.end(),matchorder);
	// std::sort(minchi2_mu2_muJetC.begin(),minchi2_mu2_muJetC.end(),matchorder);
	// std::sort(minchi2_mu1_muJetF.begin(),minchi2_mu1_muJetF.end(),matchorder);
	// std::sort(minchi2_mu2_muJetF.begin(),minchi2_mu2_muJetF.end(),matchorder);


	// muJetC_muon1_track_minchi2 = minchi2_mu1_muJetC[0].second;
	// muJetC_muon2_track_minchi2 = minchi2_mu2_muJetC[0].second;
	// muJetF_muon1_track_minchi2 = minchi2_mu1_muJetF[0].second;
	// muJetF_muon2_track_minchi2 = minchi2_mu2_muJetF[0].second;


	// if(minchi2_mu1_muJetC[0].second<100000.0){
	//   b_match_mu1track_muJetC=1;
	//   indxtrkmj1[0] = minchi2_mu1_muJetC[0].first;
	// }
	// if(minchi2_mu2_muJetC[0].second<100000.0){
	//   b_match_mu2track_muJetC=1;
	//   indxtrkmj1[1] = minchi2_mu2_muJetC[0].first;
	// }
	// if(minchi2_mu1_muJetF[0].second<100000.0){
	//   b_match_mu1track_muJetF=1;
	//   indxtrkmj2[0] = minchi2_mu1_muJetF[0].first;
	// }
	// if(minchi2_mu2_muJetF[0].second<100000.0){
	//   b_match_mu2track_muJetF=1;
	//   indxtrkmj2[1] = minchi2_mu2_muJetF[0].first;
	// }


	// if(m_debug>10){
	// std::cout<<"  matching   chi2  mu1 muJetC  "<<minchi2_mu1_muJetC[0].first<<std::endl;
	// std::cout<<"  matching   chi2  mu2 muJetC  "<<minchi2_mu2_muJetC[0].first<<std::endl;
	// std::cout<<"  matching   chi2  mu1 muJetF  "<<minchi2_mu1_muJetF[0].first<<std::endl;
	// std::cout<<"  matching   chi2  mu2 muJetF  "<<minchi2_mu2_muJetF[0].first<<std::endl;
	// }



	// minchi2_mu1_muJetC.clear();
	// minchi2_mu2_muJetC.clear();
	// minchi2_mu1_muJetF.clear();
	// minchi2_mu2_muJetF.clear();

	// Int_t counter_track_hit=0;
	// for (reco::TrackCollection::const_iterator trackrf = tracksrf->begin(); trackrf != tracksrf->end(); ++trackrf) {
	  
	//   if(counter_track_hit == indxtrkmj1[0]){

	//     // if(m_debug>10){
	//     //   if(k==0) std::cout<< "p.hasValidHitInFirstPixelEndcap(): " << p.hasValidHitInFirstPixelEndcap() <<counter_gt<<std::endl;
	//     //   if(k==1) std::cout<< "  matching   gt  mu2 muJetC  "<<counter_gt<<std::endl;
	//     // }

	//       const reco::HitPattern& p = trackrf->hitPattern();
	//       if(p.hasValidHitInFirstPixelEndcap() || p.hasValidHitInFirstPixelBarrel()){
	// 	//		dim1_hit=true;
	// 	indxtrkmj1_validhit[0] = 1;
	// 	b_muJetC_hitpix[0] = 1;
	//       }
	//     }

	//     if(counter_track_hit == indxtrkmj1[1]){

	//       const reco::HitPattern& p = trackrf->hitPattern();
	//       if(p.hasValidHitInFirstPixelEndcap() || p.hasValidHitInFirstPixelBarrel()){
	// 	//		dim1_hit=true;
	// 	indxtrkmj1_validhit[1] = 1;
	// 	b_muJetC_hitpix[1] = 1;
	//       }
	//     }

	//     if(counter_track_hit == indxtrkmj2[0]){

	//       const reco::HitPattern& p = trackrf->hitPattern();
	//       if(p.hasValidHitInFirstPixelEndcap() || p.hasValidHitInFirstPixelBarrel()){
	// 	//		dim1_hit=true;
	// 	indxtrkmj2_validhit[0] = 1;
	// 	b_muJetF_hitpix[0] = 1;
	//       }
	//     }

	//     if(counter_track_hit == indxtrkmj2[1]){

	//       const reco::HitPattern& p = trackrf->hitPattern();
	//       if(p.hasValidHitInFirstPixelEndcap() || p.hasValidHitInFirstPixelBarrel()){
	// 	//		dim1_hit=true;
	// 	indxtrkmj2_validhit[1] = 1;
	// 	b_muJetF_hitpix[1] = 1;
	//       }
	//     }

	//     counter_track_hit++;
	// }
	




	// // //====== matching selected muons to generalTracks
	// // for(uint32_t k=0;k<2;k++){
	// //   Int_t counter_match=0;
	// //   for (reco::TrackCollection::const_iterator track = tracks->begin(); track != tracks->end(); ++track) {
	// //     //	  for (reco::TrackCollection::const_iterator track = tracks->begin(); track != tracks->end(); ++track) {
	// //     if(sameTrack(&*track,&*(muJetC->muon(k)->innerTrack()))){
	// //       indxtrkmj1_gt[k] = counter_match;
	// //       if(m_debug>10){
	// // 	if(k==0) std::cout<<"  match mj1m0 muon track with indx genTrk  "<<counter_match<<" track pT  "<<track->pt()<<std::endl;
	// // 	if(k==1) std::cout<<"  match mj1m1 muon track with indx gentrk  "<<counter_match<<" track pT  "<<track->pt()<<std::endl;
	// //       }
	// //       const reco::HitPattern& p = track->hitPattern();
	// //       if(p.hasValidHitInFirstPixelEndcap() || p.hasValidHitInFirstPixelBarrel()){
	// // 	//		dim1_hit=true;
	// // 	indxtrkmj1_validhit_gt[k] = 1;
	// // 	b_muJetC_hitpix_gt[k] = 1;
	// //       }
	// //       else{
	// // 	indxtrkmj1_validhit_gt[k] = 0;
	// // 	b_muJetC_hitpix_gt[k] = 0;
	// //       }
	// //     }
	  
	// //     if(sameTrack(&*track,&*(muJetF->muon(k)->innerTrack()))){
	// //       indxtrkmj2_gt[k] = counter_match;
	// //       if(m_debug>10){
	// // 	if(k==0) std::cout<<"  match mj2m0 muon track with indx genTrk  "<<counter_match<<" track pT  "<<track->pt()<<std::endl;
	// // 	if(k==1) std::cout<<"  match mj2m1 muon track with indx genTrk  "<<counter_match<<" track pT  "<<track->pt()<<std::endl;
	// //       }
	// //       const reco::HitPattern& p = track->hitPattern();
	// //       if(p.hasValidHitInFirstPixelEndcap() || p.hasValidHitInFirstPixelBarrel()){
	// // 	//		dim2_hit_gt=true;
	// // 	indxtrkmj2_validhit_gt[k] = 1;
	// // 	b_muJetF_hitpix_gt[k] = 1;
	// //       }
	// //       else{
	// // 	indxtrkmj2_validhit_gt[k] = 0;
	// // 	b_muJetF_hitpix_gt[k] = 0;
	// //       }
	// //     }
	// //     counter_match++;
	// //   }
	// // }
    

	// if(m_debug>10){
	//   std::cout<<"  MuJetC  mu0 valid hit  "<<indxtrkmj1_validhit[0]<<std::endl;
	//   std::cout<<"  MuJetC  mu1 valid hit  "<<indxtrkmj1_validhit[1]<<std::endl;
	//   std::cout<<"  MuJetF  mu0 valid hit  "<<indxtrkmj2_validhit[0]<<std::endl;
	//   std::cout<<"  MuJetF  mu1 valid hit  "<<indxtrkmj2_validhit[1]<<std::endl;

	//   // std::cout<<"  MuJet1  mu0 valid hit genTrk  "<<indxtrkmj1_validhit_gt[0]<<std::endl;
	//   // std::cout<<"  MuJet1  mu1 valid hit genTrk "<<indxtrkmj1_validhit_gt[1]<<std::endl;
	//   // std::cout<<"  MuJet2  mu0 valid hit genTrk "<<indxtrkmj2_validhit_gt[0]<<std::endl;
	//   // std::cout<<"  MuJet2  mu1 valid hit genTrk "<<indxtrkmj2_validhit_gt[1]<<std::endl;
	// }
	
	// Local2DPoint mj1m0pos[200];
	// Local2DPoint mj1m1pos[200];
	// Local2DPoint mj2m0pos[200];
	// Local2DPoint mj2m1pos[200];

	// for(int in=0;in<200;in++){
	//   mj1m0pos[in] = Local2DPoint(-10000,-10000);
	//   mj1m1pos[in] = Local2DPoint(-10000,-10000);
	//   mj2m0pos[in] = Local2DPoint(-10000,-10000);
	//   mj2m1pos[in] = Local2DPoint(-10000,-10000);
	// }


	// Local2DPoint mj1m0poserr[200];
	// Local2DPoint mj1m1poserr[200];
	// Local2DPoint mj2m0poserr[200];
	// Local2DPoint mj2m1poserr[200];

	// for(int in=0;in<200;in++){
	//   mj1m0poserr[in] = Local2DPoint(-10000,-10000);
	//   mj1m1poserr[in] = Local2DPoint(-10000,-10000);
	//   mj2m0poserr[in] = Local2DPoint(-10000,-10000);
	//   mj2m1poserr[in] = Local2DPoint(-10000,-10000);
	// }



	// Local2DPoint mj1m0pos_lastmeas[200];
	// Local2DPoint mj1m1pos_lastmeas[200];
	// Local2DPoint mj2m0pos_lastmeas[200];
	// Local2DPoint mj2m1pos_lastmeas[200];

	// for(int in=0;in<200;in++){
	//   mj1m0pos_lastmeas[in] = Local2DPoint(-10000,-10000);
	//   mj1m1pos_lastmeas[in] = Local2DPoint(-10000,-10000);
	//   mj2m0pos_lastmeas[in] = Local2DPoint(-10000,-10000);
	//   mj2m1pos_lastmeas[in] = Local2DPoint(-10000,-10000);
	// }
    
	// // 	std::vector<Local2DPoint> rechit_muon1_muJetC;
	// // 	std::vector<Local2DPoint> rechit_muon2_muJetC;

	// // 	std::vector<Local2DPoint> rechit_muon1_muJetF;
	// // 	std::vector<Local2DPoint> rechit_muon2_muJetF;
      
	
	// // Collection of Trajectories from Refitted Tracks
	// Handle<vector<Trajectory> > trajCollectionHandle;
	// iEvent.getByLabel(param_.getParameter<string>("trajectoryInput"),trajCollectionHandle);
      
	// if(m_debug>10){
	//   std::cout<<"   genTrack collection: " <<tracks->size()<<std::endl;
	//   std::cout<<"   Refitted trajectoryColl->size(): " << trajCollectionHandle->size()<<std::endl;
	// }


	// for(uint32_t km=0;km<2;km++){  // loop for muJetC muon trajectories
	  
	//   if(m_debug>10){
	//     std::cout<<"  muon-track indx   "<<indxtrkmj1[km]<<"  muon pT   "<<muJetC->muon(km)->pt()<<"  muon eta  "
	// 	     <<muJetC->muon(km)->eta()<<std::endl;
	//   }
      

	//   //===================   Information for the muon-tracks ===================================//
	//   if(km==0)  b_mutrack_pT_mu1JetC = muJetC->muon(km)->pt();
	//   if(km==1)  b_mutrack_pT_mu2JetC = muJetC->muon(km)->pt();

	//   if(km==0)  b_mutrack_phi_mu1JetC = muJetC->muon(km)->phi();
	//   if(km==1)  b_mutrack_phi_mu2JetC = muJetC->muon(km)->phi();

	//   if(km==0)  b_mutrack_charge_mu1JetC = muJetC->muon(km)->charge();
	//   if(km==1)  b_mutrack_charge_mu2JetC = muJetC->muon(km)->charge();

	//   if(km==0)  b_mutrack_eta_mu1JetC = muJetC->muon(km)->eta();
	//   if(km==1)  b_mutrack_eta_mu2JetC = muJetC->muon(km)->eta();

	//   //====================== Loop for Trajectories from TrackRefitter  =================================//
	//   Int_t counter_traj=0;
	//   for(vector<Trajectory>::const_iterator it = trajCollectionHandle->begin(); it!=trajCollectionHandle->end();it++){
	    
	//     if(counter_traj==indxtrkmj1[km]){
	
	//       if(m_debug>10){std::cout<<"  track   "<<counter_traj<<  "    this traj has " << it->foundHits() << " valid hits"  << " , "
	// 			      << "isValid: " << it->isValid()<<std::endl;
	//       }
	      
	//       //	    if(it->firstMeasurement().updatedState().isValid() && it->lastMeasurement().updatedState().isValid()){

	//       if(it->lastMeasurement().updatedState().isValid()){  // lastMeasurement correspond to the innerLayer assuming direction oppositetoMomentum
	      
	// 	FreeTrajectoryState*  outerState = it->firstMeasurement().updatedState().freeState();    
	// 	FreeTrajectoryState*  innerState = it->lastMeasurement().updatedState().freeState(); 
	// 	TrajectoryStateOnSurface outerTSOS = it->firstMeasurement().updatedState();
	// 	TrajectoryStateOnSurface innerTSOS = it->lastMeasurement().updatedState();
		
	// 	if(innerTSOS.hasError()){
	// 	  if(m_debug>10) std::cout<<" innerTSOS muJetC has errors and they are:   "<<std::endl;
	// 	  if(m_debug>10) std::cout<<" innerTrajectory local error xx  "<<sqrt(innerTSOS.localError().positionError().xx())<<std::endl;
	// 	  if(m_debug>10) std::cout<<" innerTrajectory local error yy  "<<sqrt(innerTSOS.localError().positionError().yy())<<std::endl;
	// 	  if(m_debug>10) std::cout<<" innerTrajectory local error xy "<<sqrt(innerTSOS.localError().positionError().xy())<<std::endl;


	// 	  if(km==0) {
	// 	    b_errposx_inlay_mu1_muJetC = sqrt(innerTSOS.localError().positionError().xx());
	// 	    b_errposy_inlay_mu1_muJetC = sqrt(innerTSOS.localError().positionError().yy());
	// 	  }

	// 	  if(km==1) {
	// 	    b_errposx_inlay_mu2_muJetC = sqrt(innerTSOS.localError().positionError().xx());
	// 	    b_errposy_inlay_mu2_muJetC = sqrt(innerTSOS.localError().positionError().yy());
	// 	  }
	// 	}

	// 	const DetLayer* outerLayer = it->firstMeasurement().layer();
	// 	const DetLayer* innerLayer = it->lastMeasurement().layer();
		
	// 	if (!outerLayer || !innerLayer){
	// 	  //means  that the trajectory was fit/smoothed in a special case: not setting those pointers
		  
	// 	  if(m_debug>10) std::cout<<"the trajectory was fit/smoothed in a special case: not setting those pointers.\n"
	// 				  <<" Filling the secondary hit patterns was requested. So I will bail out."<<std::endl;
	// 	}
		
	// 	//WARNING: we are assuming that the hits were originally sorted along momentum (and therefore oppositeToMomentum after smoothing)
	// 	PropagationDirection dirForInnerLayers = oppositeToMomentum;
	// 	PropagationDirection dirForOuterLayers = alongMomentum;
	// 	if(it->direction() != oppositeToMomentum){
	// 	  dirForInnerLayers = alongMomentum;
	// 	  dirForOuterLayers = oppositeToMomentum;
	// 	  //throw cms::Exception("TrackProducer") 
	// 	}
	    
	// 	std::vector< const DetLayer * > innerCompLayers = innerLayer->compatibleLayers(*innerState,dirForInnerLayers);
	// 	std::vector< const DetLayer * > outerCompLayers = outerLayer->compatibleLayers(*outerState,dirForOuterLayers);
		
		
	// 	if(m_debug>10){
	// 	  std::cout<<"========================================================"<<std::endl;
	// 	  std::cout<< "inner DetLayer  sub: " 
	// 		   << innerLayer->subDetector() <<"\n"
	// 		   << "outer DetLayer  sub: " 
	// 		   << outerLayer->subDetector() << "\n"
	// 		   <<" innerstate local position x "<< it->firstMeasurement().updatedState().localPosition().x()<< "\n"
	// 		   <<" innerstate local position y "<< it->firstMeasurement().updatedState().localPosition().y()<< "\n"
	// 		   <<" innerstate local position lastmeas x "<< it->lastMeasurement().updatedState().localPosition().x()<<"\n"
	// 		   <<" innerstate local position lastmeas y "<< it->lastMeasurement().updatedState().localPosition().y()<<"\n"
	// 		   << "innercompatlbleLayers: " << innerCompLayers.size() << "\n"
	// 		   << "outercompatibleLayers: " << outerCompLayers.size() << std::endl;
	// 	  std::cout<<"========================================================"<<std::endl;
	// 	}

		
	// 	if(km==0) b_innerlayers_mu1_muJetC = innerCompLayers.size();
	// 	if(km==1) b_innerlayers_mu2_muJetC = innerCompLayers.size();

	// 	if(innerCompLayers.size()==0) {
		  
	// 	  if(m_debug>10) std::cout<<"  already in 1st pixel layer   "<<std::endl;
		  
	// 	  if(km==0) mj1m0pos[0] = Local2DPoint(it->firstMeasurement().updatedState().localPosition().x(),
	// 					       it->firstMeasurement().updatedState().localPosition().y());
	// 	  if(km==1) mj1m1pos[0] = Local2DPoint(it->firstMeasurement().updatedState().localPosition().x(),
	// 					       it->firstMeasurement().updatedState().localPosition().y());
		  
		  
	// 	  if(km==0) mj1m0pos_lastmeas[0] = Local2DPoint(it->lastMeasurement().updatedState().localPosition().x(),
	// 							it->lastMeasurement().updatedState().localPosition().y());
	// 	  if(km==1) mj1m1pos_lastmeas[0] = Local2DPoint(it->lastMeasurement().updatedState().localPosition().x(),
	// 							it->lastMeasurement().updatedState().localPosition().y());
		  
	// 	}
	    


	// 	Int_t det1stpix=0;
	// 	Int_t counter_hit=0;

		
	// 	for(vector<const DetLayer *>::const_iterator dd=innerCompLayers.begin(); dd!=innerCompLayers.end();++dd){
	      
	// 	  if ((*dd)->basicComponents().empty()) {
	// 	    //		this should never happen. but better protect for it
	// 	    if(m_debug>10) std::cout<<" a detlayer with no components: I cannot figure out a DetId from this layer. please investigate."<<std::endl;
	// 	    continue;
	// 	  }
 
	// 	  Propagator* localProp = thePropagator->clone();
	// 	  localProp->setPropagationDirection(oppositeToMomentum);
	      
	// 	  if(m_debug>10) std::cout<<" propagation to compatible detwithstate using estimator2  "<<std::endl;
	// 	  vector< GeometricSearchDet::DetWithState > detWithState = (*dd)->compatibleDets(innerTSOS,*localProp,estimator2);
	      
	// 	  if(!detWithState.size()) continue;
	  
	// 	  if(m_debug>10) std::cout<<" Dets compatible with a trajectoryState according to estimator)  "<<
	// 			   detWithState.size()<<std::endl;
	      
	// 	  if(m_debug>10) std::cout<<"========================================================"<<std::endl;
		  
		  

	// 	  for(uint32_t k=0;k<detWithState.size();k++){
		    
	// 	    DetId id = detWithState[k].first->geographicalId();
	// 	    const MeasurementDet* measDet = theMeasTk->idToDet(id);

	// 	    if( ( ( (*dd)->subDetector() == GeomDetEnumerators::PixelBarrel && PXBDetId(id).layer()==1) || 
	// 		  ( (*dd)->subDetector() == GeomDetEnumerators::PixelEndcap && PXFDetId(id).disk()==1) ) && measDet->isActive() ){

	// 	      if(m_debug>10){
	// 		std::cout<<"  compatible Det  number  "<<k<<std::endl;
	// 		std::cout<<" local position rho  Det   "<<detWithState[k].second.localPosition().perp()<<std::endl;
	// 		std::cout<<" local position x  Det   "<<detWithState[k].second.localPosition().x()<<std::endl;
	// 		std::cout<<" local position y  Det   "<<detWithState[k].second.localPosition().y()<<std::endl;
	// 	      }

	// 	      if(km==0) mj1m0pos[det1stpix] = Local2DPoint(detWithState[k].second.localPosition().x(),detWithState[k].second.localPosition().y());
	// 	      if(km==1) mj1m1pos[det1stpix] = Local2DPoint(detWithState[k].second.localPosition().x(),detWithState[k].second.localPosition().y());

	// 	      if(km==0) mj1m0poserr[det1stpix] = Local2DPoint(sqrt(detWithState[k].second.localError().positionError().xx()),
	// 							      sqrt(detWithState[k].second.localError().positionError().yy()));
	// 	      if(km==1) mj1m1poserr[det1stpix] = Local2DPoint(sqrt(detWithState[k].second.localError().positionError().xx()),
	// 							      sqrt(detWithState[k].second.localError().positionError().yy()));


	// 	      LocalError localErr2 = detWithState[k].second.localError().positionError();
	// 	      localErr2.scale(2); // get the 2 sigma ellipse;
	// 	      Float_t xx2 = sqrt(localErr2.xx());
	// 	      Float_t xy2 = sqrt(localErr2.xy());
	// 	      Float_t yy2 = sqrt(localErr2.yy());
		      
		      
	// 	      if(m_debug>10){
	// 		std::cout<<" local error extp innerlayer xx   "<<xx2<<endl;
	// 		std::cout<<" local error extp innerlayer xy   "<<xy2<<endl;
	// 		std::cout<<" local error extp innerlayer yy   "<<yy2<<endl;
	// 	      }
		      
	// 	      std::cout<<"========================================================"<<std::endl;
			
			
	// 	      TrajectoryStateOnSurface ts; //dummy
		
	// 	      std::vector<TrajectoryMeasurement> tmp = measDet->fastMeasurements(detWithState[k].second,ts,*localProp,estimator);
			
			
	// 	      // 		      vector<TrajectoryMeasurement> tmpVec;
			
	// 	      // 		      if(!tmp.empty()){
	// 	      // 			if(m_debug>10) std::cout<<"  Number of nearby rechits using chi2estimator   "<<tmp.size()<<std::endl;
			  
	// 	      // 			//collecting only valid rechits
	// 	      // 			if(tmp.back().recHit()->getType() == TrackingRecHit::missing) tmp.pop_back();
	// 	      // #if defined( __GXX_EXPERIMENTAL_CXX0X__)
	// 	      // 			tmpVec.insert( tmpVec.end(), std::make_move_iterator(tmp.begin()), std::make_move_iterator(tmp.end()));
	// 	      // #else
	// 	      // 			tmpVec.insert( tmpVec.end(), tmp.begin(), tmp.end());
	// 	      // #endif
			  
	// 	      // 		      }
	      
			
	// 	      if(m_debug>10) std::cout<<" number of hits  "<<tmp.size()<<std::endl;
			

	// 	      for(vector<TrajectoryMeasurement>::iterator tmpIt=tmp.begin();tmpIt!=tmp.end();tmpIt++){
			  
	// 		if(tmpIt->recHit()->getType()==0){ // valid hit
			    
	// 		  if(m_debug>10){
	// 		    std::cout<<"   status of rechit       "<<tmpIt->recHit()->getType()<<std::endl;
	// 		    std::cout<<"   local position rho:   "<<tmpIt->recHit()->localPosition().perp()<<std::endl;
	// 		    std::cout<<"   local position x:     "<<tmpIt->recHit()->localPosition().x()<<std::endl;
	// 		    std::cout<<"   local position y:     "<<tmpIt->recHit()->localPosition().y()<<std::endl;
	// 		  }

	// 		  if(km==0){
	// 		    b_pixelhit_mu1_muJetC_posx[counter_hit] = tmpIt->recHit()->localPosition().x();
	// 		    b_pixelhit_mu1_muJetC_posy[counter_hit] = tmpIt->recHit()->localPosition().y();

	// 		    b_pixelhit_mu1_muJetC_errposx[counter_hit] = sqrt(tmpIt->recHit()->localPositionError().xx());
	// 		    b_pixelhit_mu1_muJetC_errposy[counter_hit] = sqrt(tmpIt->recHit()->localPositionError().yy());
	// 		  }

	// 		  if(km==1){
	// 		    b_pixelhit_mu2_muJetC_posx[counter_hit] = tmpIt->recHit()->localPosition().x();
	// 		    b_pixelhit_mu2_muJetC_posy[counter_hit] = tmpIt->recHit()->localPosition().y();

	// 		    b_pixelhit_mu2_muJetC_errposx[counter_hit] = sqrt(tmpIt->recHit()->localPositionError().xx());
	// 		    b_pixelhit_mu2_muJetC_errposy[counter_hit] = sqrt(tmpIt->recHit()->localPositionError().yy());
	// 		  }


	// 		  Local2DPoint tmphitpos(tmpIt->recHit()->localPosition().x(),tmpIt->recHit()->localPosition().y());
	// 		  counter_hit++;
	// 		}
	// 	      }
	// 	      tmp.clear();
	// 	      det1stpix++;
	// 	    }
	// 	  }
	// 	  delete localProp;
	// 	}
		
	// 	if(km==0) b_Det_mu1_muJetC = det1stpix;
	// 	if(km==1) b_Det_mu2_muJetC = det1stpix;
		
	// 	if(km==0)  b_comphits_mu1_muJetC = counter_hit;
	// 	if(km==1)  b_comphits_mu2_muJetC = counter_hit;
		
	//       }
	//     }
	//     counter_traj++;
	//   }
	// }

	// if(m_debug>10) std::cout<<" second muonJet  muJetF  "<<std::endl;
      
	// for(uint32_t km=0;km<2;km++){
	
	//   //	std::cout<<" indx track   "<<indxtrkmj2[km]<<std::endl;

	//   if(m_debug>10) std::cout<<"  muon-track indx   "<<indxtrkmj2[km]<<"  muon pT   "<<muJetF->muon(km)->pt()<<"  muon eta  "<<muJetF->muon(km)->eta()<<std::endl;
	

	  
	//   //===================   Information for the muon-tracks ===================================//
	//   if(km==0)  b_mutrack_pT_mu1JetF = muJetF->muon(km)->pt();
	//   if(km==1)  b_mutrack_pT_mu2JetF = muJetF->muon(km)->pt();

	//   if(km==0)  b_mutrack_phi_mu1JetF = muJetF->muon(km)->phi();
	//   if(km==1)  b_mutrack_phi_mu2JetF = muJetF->muon(km)->phi();

	//   if(km==0)  b_mutrack_charge_mu1JetF = muJetF->muon(km)->charge();
	//   if(km==1)  b_mutrack_charge_mu2JetF = muJetF->muon(km)->charge();

	//   if(km==0)  b_mutrack_eta_mu1JetF = muJetF->muon(km)->eta();
	//   if(km==1)  b_mutrack_eta_mu2JetF = muJetF->muon(km)->eta();


	//   //====================== Loop for Trajectories from TrackRefitter  =================================//
	//   Int_t counter_traj=0;
	//   for(vector<Trajectory>::const_iterator it = trajCollectionHandle->begin(); it!=trajCollectionHandle->end();it++){
	  
	//     if(counter_traj==indxtrkmj2[km]){

	//       if(m_debug>10) std::cout<<"  track   "<<counter_traj<<  "    this traj has " << it->foundHits() << " valid hits"  << " , "
	// 			      << "isValid: " << it->isValid()<<std::endl;
	    
	//       //	    if(it->firstMeasurement().updatedState().isValid() && it->lastMeasurement().updatedState().isValid()){
	//       if(it->lastMeasurement().updatedState().isValid()){
	      
	// 	FreeTrajectoryState*  outerState = it->firstMeasurement().updatedState().freeState();    
	// 	FreeTrajectoryState*  innerState = it->lastMeasurement().updatedState().freeState(); 
	// 	TrajectoryStateOnSurface outerTSOS = it->firstMeasurement().updatedState();
	// 	TrajectoryStateOnSurface innerTSOS = it->lastMeasurement().updatedState();
	      
	// 	if(innerTSOS.hasError()){
	// 	  if(m_debug>10) std::cout<<" innerTSOS muJetF has errors and they are:   "<<std::endl;
	// 	  if(m_debug>10) std::cout<<" innerTrajectory local error xx  "<<sqrt(innerTSOS.localError().positionError().xx())<<std::endl;
	// 	  if(m_debug>10) std::cout<<" innerTrajectory local error yy  "<<sqrt(innerTSOS.localError().positionError().yy())<<std::endl;
	// 	  if(m_debug>10) std::cout<<" innerTrajectory local error xy "<<sqrt(innerTSOS.localError().positionError().xy())<<std::endl;


	// 	  if(km==0) {
	// 	    b_errposx_inlay_mu1_muJetF = sqrt(innerTSOS.localError().positionError().xx());
	// 	    b_errposy_inlay_mu1_muJetF = sqrt(innerTSOS.localError().positionError().yy());
	// 	  }
		  
	// 	  if(km==1) {
	// 	    b_errposx_inlay_mu2_muJetF = sqrt(innerTSOS.localError().positionError().xx());
	// 	    b_errposy_inlay_mu2_muJetF = sqrt(innerTSOS.localError().positionError().yy());
	// 	  }


	// 	}
	      
	// 	const DetLayer* outerLayer = it->firstMeasurement().layer();
	// 	const DetLayer* innerLayer = it->lastMeasurement().layer();
	      
	// 	if (!outerLayer || !innerLayer){
	// 	  //means  that the trajectory was fit/smoothed in a special case: not setting those pointers
	    
	// 	  if(m_debug>10) std::cout<<"the trajectory was fit/smoothed in a special case: not setting those pointers.\n"
	// 				  <<" Filling the secondary hit patterns was requested. So I will bail out."<<std::endl;
	// 	}
	      
	// 	//WARNING: we are assuming that the hits were originally sorted along momentum (and therefore oppositeToMomentum after smoothing)
	// 	PropagationDirection dirForInnerLayers = oppositeToMomentum;
	// 	PropagationDirection dirForOuterLayers = alongMomentum;
	// 	if(it->direction() != oppositeToMomentum){
	// 	  dirForInnerLayers = alongMomentum;
	// 	  dirForOuterLayers = oppositeToMomentum;
	// 	  //throw cms::Exception("TrackProducer") 
	// 	}
	      
	// 	std::vector< const DetLayer * > innerCompLayers = innerLayer->compatibleLayers(*innerState,dirForInnerLayers);
	// 	std::vector< const DetLayer * > outerCompLayers = outerLayer->compatibleLayers(*outerState,dirForOuterLayers);
	    
	// 	if(m_debug>10){
	// 	  std::cout<<"========================================================"<<std::endl;
	// 	  std::cout<< "inner DetLayer  sub: " 
	// 		   << innerLayer->subDetector() <<"\n"
	// 		   << "outer DetLayer  sub: " 
	// 		   << outerLayer->subDetector() << "\n"
	// 		   <<" innerstate local position x "<< it->firstMeasurement().updatedState().localPosition().x()<<"\n"
	// 		   <<" innerstate local position y "<< it->firstMeasurement().updatedState().localPosition().y()<<"\n"
	// 		   <<" innerstate local position lastmeas x "<< it->lastMeasurement().updatedState().localPosition().x()<<"\n"
	// 		   <<" innerstate local position lastmeas y "<< it->lastMeasurement().updatedState().localPosition().y()<<"\n"
	// 		   << "innercompatlbleLayers: " << innerCompLayers.size() << "\n"
	// 		   << "outercompatibleLayers: " << outerCompLayers.size() << std::endl;
	// 	  std::cout<<"========================================================"<<std::endl;
	// 	}


	// 	if(km==0) b_innerlayers_mu1_muJetF = innerCompLayers.size();
	// 	if(km==1) b_innerlayers_mu2_muJetF = innerCompLayers.size();
		
	// 	if(innerCompLayers.size()==0) {

	// 	  if(m_debug>10) std::cout<<"  already in 1st pixel layer   "<<std::endl;

	// 	  if(km==0) mj2m0pos[0] = Local2DPoint(it->firstMeasurement().updatedState().localPosition().x(),
	// 					       it->firstMeasurement().updatedState().localPosition().y());
	// 	  if(km==1) mj2m1pos[0] = Local2DPoint(it->firstMeasurement().updatedState().localPosition().x(),
	// 					       it->firstMeasurement().updatedState().localPosition().y());


	// 	  if(km==0) mj2m0pos_lastmeas[0] = Local2DPoint(it->lastMeasurement().updatedState().localPosition().x(),
	// 							it->lastMeasurement().updatedState().localPosition().y());
	// 	  if(km==1) mj2m1pos_lastmeas[0] = Local2DPoint(it->lastMeasurement().updatedState().localPosition().x(),
	// 							it->lastMeasurement().updatedState().localPosition().y());


	// 	}

	// 	Int_t counter_hit=0;
	// 	Int_t det1stpix=0;
	// 	for(vector<const DetLayer *>::const_iterator dd=innerCompLayers.begin(); dd!=innerCompLayers.end();++dd){

	// 	  if ((*dd)->basicComponents().empty()) {
	// 	    //this should never happen. but better protect for it
	// 	    if(m_debug>10) std::cout<<" a detlayer with no components: I cannot figure out a DetId from this layer. please investigate."<<std::endl;
	// 	    continue;
	// 	  }
	  
 	// 	  Propagator* localProp = thePropagator->clone();
 	// 	  localProp->setPropagationDirection(oppositeToMomentum);

 	// 	  vector< GeometricSearchDet::DetWithState > detWithState = (*dd)->compatibleDets(innerTSOS,*localProp,estimator2);

 	// 	  if(!detWithState.size()) continue;
	  
 	// 	  if(m_debug>10) std::cout<<" Dets compatible with a trajectoryState according to estimator)  "<<
 	// 			   detWithState.size()<<std::endl;

 	// 	  if(m_debug>10) std::cout<<"========================================================"<<std::endl;
		  

 	// 	  for(uint32_t k=0;k<detWithState.size();k++){

		    
 	// 	    DetId id = detWithState[k].first->geographicalId();
 	// 	    const MeasurementDet* measDet = theMeasTk->idToDet(id);

 	// 	    if( ( ((*dd)->subDetector() == GeomDetEnumerators::PixelBarrel && PXBDetId(id).layer()==1) 
	// 		  || ((*dd)->subDetector()  == GeomDetEnumerators::PixelEndcap && PXFDetId(id).disk()==1) ) && measDet->isActive()  ){
		      
	// 	      if(m_debug>10){
	// 		std::cout<<"  compatible Det  number  "<<k<<std::endl;
	// 		std::cout<<" local position rho  Det   "<<detWithState[k].second.localPosition().perp()<<std::endl;
	// 		std::cout<<" local position x  Det   "<<detWithState[k].second.localPosition().x()<<std::endl;
	// 		std::cout<<" local position y  Det   "<<detWithState[k].second.localPosition().y()<<std::endl;
	// 	      }
		      
	// 	      if(km==0) mj2m0pos[det1stpix] = Local2DPoint(detWithState[k].second.localPosition().x(),detWithState[k].second.localPosition().y());
	// 	      if(km==1) mj2m1pos[det1stpix] = Local2DPoint(detWithState[k].second.localPosition().x(),detWithState[k].second.localPosition().y());
		      
	// 	      if(km==0) mj2m0poserr[det1stpix] = Local2DPoint(sqrt(detWithState[k].second.localError().positionError().xx()),
	// 							      sqrt(detWithState[k].second.localError().positionError().yy()));
	// 	      if(km==1) mj2m1poserr[det1stpix] = Local2DPoint(sqrt(detWithState[k].second.localError().positionError().xx()),
	// 							      sqrt(detWithState[k].second.localError().positionError().yy()));

	// 	      LocalError localErr2 = detWithState[k].second.localError().positionError();
	// 	      localErr2.scale(2); // get the 2 sigma ellipse;
	// 	      Float_t xx2 = sqrt(localErr2.xx());
	// 	      Float_t xy2 = sqrt(localErr2.xy());
	// 	      Float_t yy2 = sqrt(localErr2.yy());
		      
		      
	// 	      if(m_debug>10){
	// 		std::cout<<" local error extp innerlayer xx   "<<xx2<<endl;
	// 		std::cout<<" local error extp innerlayer xy   "<<xy2<<endl;
	// 		std::cout<<" local error extp innerlayer yy   "<<yy2<<endl;
	// 	      }

	// 	      std::cout<<"========================================================"<<std::endl;
		      
		      
	// 	      TrajectoryStateOnSurface ts; //dummy
		      
	// 	      std::vector<TrajectoryMeasurement> tmp = measDet->fastMeasurements(detWithState[k].second,ts,*localProp,estimator);

	// 	      if(m_debug>10) std::cout<<" number of hits      "<<tmp.size()<<std::endl;
		      
	// 	      for(vector<TrajectoryMeasurement>::iterator tmpIt=tmp.begin();tmpIt!=tmp.end();tmpIt++){
			
	// 		if(tmpIt->recHit()->getType()==0){ // valid hit
			  
	// 		  if(m_debug>10){
	// 		    std::cout<<"   status of rechit       "<<tmpIt->recHit()->getType()<<std::endl;
	// 		    std::cout<<"   local position rho:   "<<tmpIt->recHit()->localPosition().perp()<<std::endl;
	// 		    std::cout<<"   local position x:     "<<tmpIt->recHit()->localPosition().x()<<std::endl;
	// 		    std::cout<<"   local position y:     "<<tmpIt->recHit()->localPosition().y()<<std::endl;
	// 		    std::cout<<"   local position z:     "<<tmpIt->recHit()->localPosition().z()<<std::endl;
	// 		  }
			  
			  
	// 		  if(km==0){
	// 		    b_pixelhit_mu1_muJetF_posx[counter_hit] = tmpIt->recHit()->localPosition().x();
	// 		    b_pixelhit_mu1_muJetF_posy[counter_hit] = tmpIt->recHit()->localPosition().y();

	// 		    b_pixelhit_mu1_muJetF_errposx[counter_hit] = sqrt(tmpIt->recHit()->localPositionError().xx());
	// 		    b_pixelhit_mu1_muJetF_errposy[counter_hit] = sqrt(tmpIt->recHit()->localPositionError().yy());


	// 		  }
			  
	// 		  if(km==1){
	// 		    b_pixelhit_mu2_muJetF_posx[counter_hit] = tmpIt->recHit()->localPosition().x();
	// 		    b_pixelhit_mu2_muJetF_posy[counter_hit] = tmpIt->recHit()->localPosition().y();

	// 		    b_pixelhit_mu2_muJetF_errposx[counter_hit] = sqrt(tmpIt->recHit()->localPositionError().xx());
	// 		    b_pixelhit_mu2_muJetF_errposy[counter_hit] = sqrt(tmpIt->recHit()->localPositionError().yy());
	// 		  }
			  
	// 		  Local2DPoint tmphitpos(tmpIt->recHit()->localPosition().x(),tmpIt->recHit()->localPosition().y());
	// 		  counter_hit++;
	// 		}
	// 	      }
	// 	      tmp.clear();
 	// 	      det1stpix++;
	// 	    }
	// 	  }
	// 	  delete localProp;
	      
 	// 	  // 	  tracking::TempMeasurements tmps;
 	// 	  // 	  std::vector<const TrackingRecHit*> hits;
		  
 	// 	  // 	  TrajectoryStateOnSurface current =  (*dd)->updateState();

 	// 	  // 	  //if(measDet->isActive() && !measDet->hasBadComponents(detWithState.front().second)){
 	// 	  // 	  if(measDet->isActive()){  
 	// 	  // 	    //	    InvalidTrackingRecHit  tmpHit(id,TrackingRecHit::missing);
 	// 	  // 	    //	    tmpTrack.setTrackerExpectedHitsInner(tmpHit,counter); counter_h++;
 	// 	  // 	    std::cout << "WARNING: this hit is marked as lost because the detector was marked as active" << std::endl;
 	// 	  // 	  }else{
 	// 	  // 	    std::cout << "WARNING: this hit is NOT marked as lost because the detector was marked as inactive" << std::endl;
 	// 	  // 	  }
	// 	}
	// 	if(km==0) b_Det_mu1_muJetF = det1stpix;
	// 	if(km==1) b_Det_mu2_muJetF = det1stpix;

	// 	if(km==0)  b_comphits_mu1_muJetF = counter_hit;
	// 	if(km==1)  b_comphits_mu2_muJetF = counter_hit;
	//       }
	//     }
	//     counter_traj++;
	//   }
	// }


	// if(b_Det_mu1_muJetC>0 && b_Det_mu2_muJetC>0){
	//   b_muJetC_trackdist_1stpixel = sqrt(pow(mj1m0pos[0].x()-mj1m1pos[0].x(),2)+pow(mj1m0pos[0].y() - mj1m1pos[0].y(),2));
	// }

	// if(b_Det_mu1_muJetF>0 && b_Det_mu2_muJetF>0){
	//   b_muJetF_trackdist_1stpixel = sqrt(pow(mj2m0pos[0].x()-mj2m1pos[0].x(),2)+pow(mj2m0pos[0].y() - mj2m1pos[0].y(),2));
	// }


 	// for(int ndet = 0; ndet<b_Det_mu1_muJetC;ndet++){
 	//   b_muJetC_muon1_posx1stpix[ndet] = mj1m0pos[ndet].x();
	//   b_muJetC_muon1_posy1stpix[ndet] = mj1m0pos[ndet].y();
	// }

	// for(int ndet = 0; ndet<b_Det_mu2_muJetC;ndet++){
	//   b_muJetC_muon2_posx1stpix[ndet] = mj1m1pos[ndet].x();
	//   b_muJetC_muon2_posy1stpix[ndet] = mj1m1pos[ndet].y();
	// }

	// for(int ndet = 0; ndet<b_Det_mu1_muJetF;ndet++){
	//   b_muJetF_muon1_posx1stpix[ndet] = mj2m0pos[ndet].x();
	//   b_muJetF_muon1_posy1stpix[ndet] = mj2m0pos[ndet].y();
	// }

	// for(int ndet = 0; ndet<b_Det_mu2_muJetF;ndet++){
	//   b_muJetF_muon2_posx1stpix[ndet] = mj2m1pos[ndet].x();
	//   b_muJetF_muon2_posy1stpix[ndet] = mj2m1pos[ndet].y();
	// }

	// //============ Error =========================//


 	// for(int ndet = 0; ndet<b_Det_mu1_muJetC;ndet++){
 	//   b_muJetC_muon1_errposx1stpix[ndet] = mj1m0poserr[ndet].x();
	//   b_muJetC_muon1_errposy1stpix[ndet] = mj1m0poserr[ndet].y();
	// }

	// for(int ndet = 0; ndet<b_Det_mu2_muJetC;ndet++){
	//   b_muJetC_muon2_errposx1stpix[ndet] = mj1m1poserr[ndet].x();
	//   b_muJetC_muon2_errposy1stpix[ndet] = mj1m1poserr[ndet].y();
	// }

	// for(int ndet = 0; ndet<b_Det_mu1_muJetF;ndet++){
	//   b_muJetF_muon1_errposx1stpix[ndet] = mj2m0poserr[ndet].x();
	//   b_muJetF_muon1_errposy1stpix[ndet] = mj2m0poserr[ndet].y();
	// }

	// for(int ndet = 0; ndet<b_Det_mu2_muJetF;ndet++){
	//   b_muJetF_muon2_errposx1stpix[ndet] = mj2m1poserr[ndet].x();
	//   b_muJetF_muon2_errposy1stpix[ndet] = mj2m1poserr[ndet].y();
	// }


	

 	// for(int ndet = 0; ndet<b_Det_mu1_muJetC;ndet++){
 	//   b_muJetC_muon1_posx1stpix_lastmeas[ndet] = mj1m0pos_lastmeas[ndet].x();
	//   b_muJetC_muon1_posy1stpix_lastmeas[ndet] = mj1m0pos_lastmeas[ndet].y();
	// }

	// for(int ndet = 0; ndet<b_Det_mu2_muJetC;ndet++){
	//   b_muJetC_muon2_posx1stpix_lastmeas[ndet] = mj1m1pos_lastmeas[ndet].x();
	//   b_muJetC_muon2_posy1stpix_lastmeas[ndet] = mj1m1pos_lastmeas[ndet].y();
	// }

	// for(int ndet = 0; ndet<b_Det_mu1_muJetF;ndet++){
	//   b_muJetF_muon1_posx1stpix_lastmeas[ndet] = mj2m0pos_lastmeas[ndet].x();
	//   b_muJetF_muon1_posy1stpix_lastmeas[ndet] = mj2m0pos_lastmeas[ndet].y();
	// }

	// for(int ndet = 0; ndet<b_Det_mu2_muJetF;ndet++){
	//   b_muJetF_muon2_posx1stpix_lastmeas[ndet] = mj2m1pos_lastmeas[ndet].x();
	//   b_muJetF_muon2_posy1stpix_lastmeas[ndet] = mj2m1pos_lastmeas[ndet].y();
	// }


	// std::vector<std::pair<Int_t,Float_t> > d_mu1_muJetC_hit;
	// std::vector<std::pair<Int_t,Float_t> > d_mu2_muJetC_hit;
	// std::vector<std::pair<Int_t,Float_t> > d_mu1_muJetF_hit;
	// std::vector<std::pair<Int_t,Float_t> > d_mu2_muJetF_hit;
	
	// for(int ndet = 0; ndet<b_Det_mu1_muJetC;ndet++){
	//   if(m_debug>10) std::cout<<"   ndet    "<<ndet<<std::endl;
	//   std::pair<Int_t,Float_t> temp;
	//   Float_t temp_d=-10000.0;
	//   for(int nhit=0;nhit<b_comphits_mu1_muJetC;nhit++){
	//     if(m_debug>10) std::cout<<"  nhit    "<<nhit<<std::endl;
	//     temp_d  = sqrt(pow(mj1m0pos[ndet].x()-b_pixelhit_mu1_muJetC_posx[nhit],2)+pow(mj1m0pos[ndet].y() - b_pixelhit_mu1_muJetC_posy[nhit],2));
	//     temp.first = nhit;
	//     temp.second = temp_d;
	//     d_mu1_muJetC_hit.push_back(temp);
	//   }
	//   if(d_mu1_muJetC_hit.size()>0){
	//     sort(d_mu1_muJetC_hit.begin(),d_mu1_muJetC_hit.end(),dRorder);
	//     b_mindist_hit_mu1_muJetC[ndet] = d_mu1_muJetC_hit[0].second;
	//   }

	//   d_mu1_muJetC_hit.clear();
	// }
	

	// for(int ndet = 0; ndet<b_Det_mu2_muJetC;ndet++){
	//   std::pair<Int_t,Float_t> temp;
	//   Float_t temp_d;
	//   for(int nhit=0;nhit<b_comphits_mu2_muJetC;nhit++){
	//     temp_d  = sqrt(pow(mj1m1pos[ndet].x()-b_pixelhit_mu2_muJetC_posx[nhit],2)+pow(mj1m1pos[ndet].y() - b_pixelhit_mu2_muJetC_posy[nhit],2));
	//     temp.first = nhit;
	//     temp.second = temp_d;
	//     d_mu2_muJetC_hit.push_back(temp);
	//   }
	//   if(d_mu2_muJetC_hit.size()>0){
	//     sort(d_mu2_muJetC_hit.begin(),d_mu2_muJetC_hit.end(),dRorder);
	//     b_mindist_hit_mu2_muJetC[ndet] = d_mu2_muJetC_hit[0].second;
	//   }
	//   d_mu2_muJetC_hit.clear();
	// }



	// for(int ndet = 0; ndet<b_Det_mu1_muJetF;ndet++){
	//   std::pair<Int_t,Float_t> temp;
	//   Float_t temp_d;
	//   for(int nhit=0;nhit<b_comphits_mu1_muJetF;nhit++){
	//     temp_d  = sqrt(pow(mj2m0pos[ndet].x()-b_pixelhit_mu1_muJetF_posx[nhit],2)+pow(mj2m0pos[ndet].y() - b_pixelhit_mu1_muJetF_posy[nhit],2));
	//     temp.first = nhit;
	//     temp.second = temp_d;
	//     d_mu1_muJetF_hit.push_back(temp);
	//   }
	//   if(d_mu1_muJetF_hit.size()>0){
	//     sort(d_mu1_muJetF_hit.begin(),d_mu1_muJetF_hit.end(),dRorder);
	//     b_mindist_hit_mu1_muJetF[ndet] = d_mu1_muJetF_hit[0].second;
	//   }
	//   d_mu1_muJetF_hit.clear();
	// }


	// for(int ndet = 0; ndet<b_Det_mu2_muJetF;ndet++){
	//   std::pair<Int_t,Float_t> temp;
	//   Float_t temp_d;
	//   for(int nhit=0;nhit<b_comphits_mu2_muJetF;nhit++){
	//     temp_d  = sqrt(pow(mj2m1pos[ndet].x()-b_pixelhit_mu2_muJetF_posx[nhit],2)+pow(mj2m1pos[ndet].y() - b_pixelhit_mu2_muJetF_posy[nhit],2));
	//     temp.first = nhit;
	//     temp.second = temp_d;
	//     d_mu2_muJetF_hit.push_back(temp);
	//   }
	//   if(d_mu2_muJetF_hit.size()>0){
	//     sort(d_mu2_muJetF_hit.begin(),d_mu2_muJetF_hit.end(),dRorder);
	//     b_mindist_hit_mu2_muJetF[ndet] = d_mu2_muJetF_hit[0].second;
	//   }
	//   d_mu2_muJetF_hit.clear();
	// }




	// //===============  HIT RECOVERY IMPLEMENTATION (BIKE CHAIN)  =======================//

	// Bool_t recovermj1[6];
	// Bool_t recovermj2[6];
	// Bool_t tmprecovermj1[6];
	// Bool_t tmprecovermj2[6];
	// Bool_t recovermj12[6];
	

	// Float_t d_m1hit;
	// Float_t d_m2hit;

	// Float_t radius[6] ={0.1,0.05,0.03,0.01,0.005,0.001};  // Different radius around the muon position used to define the bike chain
	
	
	// for(int m=0;m<6;m++){

	//   if( (b_muJetC_hitpix[0]!=1&&b_muJetC_hitpix[1]!=1)&&(b_muJetF_hitpix[0]==1||b_muJetF_hitpix[1]==1) ){    // First case muJetC fails but muJetF pass
	//     recovermj1[m]=false;
	    
	//     if(b_Det_mu1_muJetC>0 && b_Det_mu2_muJetC>0){ // need to have both muons extrapolated positions
	      
	//       Float_t d_m1m2;  // distance between muons
	//       d_m1m2 = sqrt(pow(mj1m0pos[0].x() - mj1m1pos[0].x(),2) + pow(mj1m0pos[0].y() - mj1m1pos[0].y(),2));
	    
	      
	//       for(int l=0;l<b_comphits_mu1_muJetC;l++){  // loop for all compatible hits
	    
	// 	d_m1hit = sqrt(pow(mj1m0pos[0].x() - b_pixelhit_mu1_muJetC_posx[l],2)+pow(mj1m0pos[0].y() - b_pixelhit_mu1_muJetC_posy[l],2));  // distance between muon1 and hits
	// 	d_m2hit = sqrt(pow(mj1m1pos[0].x() - b_pixelhit_mu1_muJetC_posx[l],2)+pow(mj1m1pos[0].y() - b_pixelhit_mu1_muJetC_posy[l],2));  // distance between muon2 and hits
		
	// 	Float_t alpha;   
	// 	alpha = acos( ( pow(d_m1hit,2) + pow(d_m1m2,2) - pow(d_m2hit,2) )/ (2*d_m1hit*d_m1m2));   // by law of cosines find relations to get perpendicular distance between hit and the line between the two muons
		
	// 	Float_t alpha2;
	// 	alpha2 = acos( ( pow(d_m2hit,2) + pow(d_m1m2,2) - pow(d_m1hit,2) )/ (2*d_m2hit*d_m1m2));
	    
	// 	if(m_debug>10){
	// 	  std::cout<<" distance between muons  "<<d_m1m2<<std::endl;
	// 	  std::cout<<" distance between m1 and hit  "<<d_m1hit<<std::endl;
	// 	  std::cout<<" distance between m2 and hit  "<<d_m2hit<<std::endl;
	// 	}
		 
		 
	// 	Float_t h;
	// 	h = d_m1hit*sin(alpha);   // perpendicular distance between the hit and the line defined by the two muons 
	// 	Float_t h2;
	// 	h2 = d_m2hit*sin(alpha2);   // perpendicular distance between the hit and the line defined by the two muons 
		 
	// 	if(m_debug>10){
	// 	  std::cout<<"    alpha1    "<<alpha<<"  alpha2   "<<alpha2<<std::endl;
	// 	  std::cout<<"   h value   "<<h<<std::endl;
	// 	  std::cout<<"   h2 value   "<<h2<<std::endl;
	// 	}
		 
	// 	if( ( (alpha<1.57 && alpha2<1.57) && h<radius[m]) || d_m1hit<radius[m] || d_m2hit<radius[m]){  // h<radius and constrain on the angles < pi/2   or the hit inside the radious around the muon position
	// 	  recovermj1[m] = true;
	// 	  if(m_debug>10) std::cout<<" recovery of muJetF   "<<std::endl;
	// 	}
	//       }
	//     }
	//   }


	//   if( (b_muJetF_hitpix[0]!=1&&b_muJetF_hitpix[1]!=1)&&(b_muJetC_hitpix[0]==1||b_muJetC_hitpix[1]==1) ){ //second case the muJetF fails and MuJetC pass
	//     recovermj2[m]=false;
	    
	//     if(b_Det_mu1_muJetF>0 && b_Det_mu2_muJetF>0){

	//       Float_t d_m1m2;  // distance between muons
	//       d_m1m2 = sqrt(pow(mj2m0pos[0].x() - mj2m1pos[0].x(),2) + pow(mj2m0pos[0].y() - mj2m1pos[0].y(),2));
	    
	      
	//       for(int l=0;l<b_comphits_mu1_muJetF;l++){
	    
	// 	d_m1hit = sqrt(pow(mj2m0pos[0].x() -  b_pixelhit_mu1_muJetF_posx[l],2)+pow(mj2m0pos[0].y() -  b_pixelhit_mu1_muJetF_posy[l],2));
	// 	d_m2hit = sqrt(pow(mj2m1pos[0].x() -  b_pixelhit_mu1_muJetF_posx[l],2)+pow(mj2m1pos[0].y() -  b_pixelhit_mu1_muJetF_posy[l],2));
	    
	// 	Float_t alpha;
	// 	alpha = acos( ( pow(d_m1hit,2) + pow(d_m1m2,2) - pow(d_m2hit,2) )/ (2*d_m1hit*d_m1m2));
	    
	// 	Float_t alpha2;
	// 	alpha2 = acos( ( pow(d_m2hit,2) + pow(d_m1m2,2) - pow(d_m1hit,2) )/ (2*d_m2hit*d_m1m2));
	    
	// 	if(m_debug>10){
	// 	  std::cout<<" distance between muons  "<<d_m1m2<<std::endl;
	// 	  std::cout<<" distance between m1 and hit  "<<d_m1hit<<std::endl;
	// 	  std::cout<<" distance between m2 and hit  "<<d_m2hit<<std::endl;
	// 	}
		 
		 
	// 	Float_t h;
	// 	h = d_m1hit*sin(alpha);
		 
	// 	if(m_debug>10){
	// 	  std::cout<<"    alpha1    "<<alpha<<"  alpha2   "<<alpha2<<std::endl;
	// 	  std::cout<<"   h value   "<<h<<std::endl;
	// 	}
		 
	// 	if( ( (alpha<1.57 && alpha2<1.57) && h<radius[m]) || d_m1hit<radius[m] || d_m2hit<radius[m]){
	// 	  recovermj2[m] = true;
	// 	  if(m_debug>10) std::cout<<" recovery of muJetF   "<<std::endl;
	// 	}
	//       }
	//     }
	//   }



	//   if( (b_muJetF_hitpix[0]!=1&&b_muJetF_hitpix[1]!=1)&&(b_muJetC_hitpix[0]!=1&&b_muJetC_hitpix[1]!=1) ){  // third case both dimuons fail
	//     recovermj12[m]=false;
	//     tmprecovermj1[m] = false;
	//     tmprecovermj2[m] = false;
	    
	//     if(b_Det_mu1_muJetF>0 && b_Det_mu2_muJetF>0){

	//       Float_t d_m1m2;  // distance between muons
	//       d_m1m2 = sqrt(pow(mj2m0pos[0].x() - mj2m1pos[0].x(),2) + pow(mj2m0pos[0].y() - mj2m1pos[0].y(),2));
	    
	      
	//       for(int l=0;l<b_comphits_mu1_muJetF;l++){
	    
	// 	d_m1hit = sqrt(pow(mj2m0pos[0].x() - b_pixelhit_mu1_muJetF_posx[l],2)+pow(mj2m0pos[0].y() - b_pixelhit_mu1_muJetF_posy[l],2));
	// 	d_m2hit = sqrt(pow(mj2m1pos[0].x() - b_pixelhit_mu1_muJetF_posx[l],2)+pow(mj2m1pos[0].y() - b_pixelhit_mu1_muJetF_posy[l],2));
	    
	// 	Float_t alpha;
	// 	alpha = acos( ( pow(d_m1hit,2) + pow(d_m1m2,2) - pow(d_m2hit,2) )/ (2*d_m1hit*d_m1m2));
	    
	// 	Float_t alpha2;
	// 	alpha2 = acos( ( pow(d_m2hit,2) + pow(d_m1m2,2) - pow(d_m1hit,2) )/ (2*d_m2hit*d_m1m2));
	    
	// 	if(m_debug>10){
	// 	  std::cout<<" distance between muons  "<<d_m1m2<<std::endl;
	// 	  std::cout<<" distance between m1 and hit  "<<d_m1hit<<std::endl;
	// 	  std::cout<<" distance between m2 and hit  "<<d_m2hit<<std::endl;
	// 	}
		 
		 
	// 	Float_t h;
	// 	h = d_m1hit*sin(alpha);
		 
	// 	if(m_debug>10){
	// 	  std::cout<<"    alpha1    "<<alpha<<"  alpha2   "<<alpha2<<std::endl;
	// 	  std::cout<<"   h value   "<<h<<std::endl;
	// 	}
		 
	// 	if( ( (alpha<1.57 && alpha2<1.57) && h<radius[m]) || d_m1hit<radius[m] || d_m2hit<radius[m]){
	// 	  tmprecovermj2[m] = true;
	// 	  if(m_debug>10) std::cout<<" recovery of muJetF   "<<std::endl;
	// 	}
	//       }
	//     }


	//     if(b_Det_mu1_muJetC>0 && b_Det_mu2_muJetC>0){

	//       Float_t d_m1m2;  // distance between muons
	//       d_m1m2 = sqrt(pow(mj1m0pos[0].x() - mj1m1pos[0].x(),2) + pow(mj1m0pos[0].y() - mj1m1pos[0].y(),2));
	    
	      
	//       for(int l=0;l<b_comphits_mu1_muJetC;l++){
	    
	// 	d_m1hit = sqrt(pow(mj1m0pos[0].x() - b_pixelhit_mu1_muJetC_posx[l],2)+pow(mj1m0pos[0].y() - b_pixelhit_mu1_muJetC_posy[l],2));
	// 	d_m2hit = sqrt(pow(mj1m1pos[0].x() - b_pixelhit_mu1_muJetC_posx[l],2)+pow(mj1m1pos[0].y() - b_pixelhit_mu1_muJetC_posy[l],2));
	    
	// 	Float_t alpha;
	// 	alpha = acos( ( pow(d_m1hit,2) + pow(d_m1m2,2) - pow(d_m2hit,2) )/ (2*d_m1hit*d_m1m2));
	    
	// 	Float_t alpha2;
	// 	alpha2 = acos( ( pow(d_m2hit,2) + pow(d_m1m2,2) - pow(d_m1hit,2) )/ (2*d_m2hit*d_m1m2));
	    
	// 	if(m_debug>10){
	// 	  std::cout<<" distance between muons  "<<d_m1m2<<std::endl;
	// 	  std::cout<<" distance between m1 and hit  "<<d_m1hit<<std::endl;
	// 	  std::cout<<" distance between m2 and hit  "<<d_m2hit<<std::endl;
	// 	}
		 
		 
	// 	Float_t h;
	// 	h = d_m1hit*sin(alpha);
		 
	// 	if(m_debug>10){
	// 	  std::cout<<"    alpha1    "<<alpha<<"  alpha2   "<<alpha2<<std::endl;
	// 	  std::cout<<"   h value   "<<h<<std::endl;
	// 	}
		 
	// 	if( ( (alpha<1.57 && alpha2<1.57) && h<radius[m]) || d_m1hit<radius[m] || d_m2hit<radius[m]){
	// 	  tmprecovermj1[m] = true;
	// 	  if(m_debug>10) std::cout<<" recovery of muJetF   "<<std::endl;
	// 	}
	//       }
	//     }


	//     if(tmprecovermj1[m] && tmprecovermj2[m]) recovermj12[m] = true;
	//   }


	// }




	// // recovery flags for different radius
	// if(recovermj1[0]) b_hitrecover_mj1_r1=1;
	// if(recovermj1[1]) b_hitrecover_mj1_r05=1;
	// if(recovermj1[2]) b_hitrecover_mj1_r03=1;
	// if(recovermj1[3]) b_hitrecover_mj1_r01=1;
	// if(recovermj1[4]) b_hitrecover_mj1_r005=1;
	// if(recovermj1[5]) b_hitrecover_mj1_r001=1;

	// if(recovermj2[0]) b_hitrecover_mj2_r1=1;
	// if(recovermj2[1]) b_hitrecover_mj2_r05=1;
	// if(recovermj2[2]) b_hitrecover_mj2_r03=1;
	// if(recovermj2[3]) b_hitrecover_mj2_r01=1;
	// if(recovermj2[4]) b_hitrecover_mj2_r005=1;
	// if(recovermj2[5]) b_hitrecover_mj2_r001=1;

	// if(recovermj12[0]) b_hitrecover_mj12_r1=1;
	// if(recovermj12[1]) b_hitrecover_mj12_r05=1;
	// if(recovermj12[2]) b_hitrecover_mj12_r03=1;
	// if(recovermj12[3]) b_hitrecover_mj12_r01=1;
	// if(recovermj12[4]) b_hitrecover_mj12_r005=1;
	// if(recovermj12[5]) b_hitrecover_mj12_r001=1;
	

	// // if(b_muJetF_hitpix[0]!=1&&b_muJetF_hitpix[1]!=1){
	    

	// // }



	// // if(dim1_hit && !dim2_hit){
	    
	// //      if(m_debug>10) std::cout<<" number of nearby hits  "<<rechitposmj2.size()<<std::endl;
	  
	// //      Float_t d_m1m2;  // distance between muons
	// //      d_m1m2 = sqrt(pow(mj2m0pos.x() - mj2m1pos.x(),2) + pow(mj2m0pos.y() - mj2m1pos.y(),2));
	  
	// //      Float_t d_m1hit;
	// //      Float_t d_m2hit;
	  
	// //      for(uint32_t l=0;l<rechitposmj2.size();l++){
	    
	// //        d_m1hit = sqrt(pow(mj2m0pos.x() - rechitposmj2[l].x(),2)+pow(mj2m0pos.y() - rechitposmj2[l].y(),2));
	// //        d_m2hit = sqrt(pow(mj2m1pos.x() - rechitposmj2[l].x(),2)+pow(mj2m1pos.y() - rechitposmj2[l].y(),2));
	    
	// //        Float_t alpha;
	// //        alpha = acos( ( pow(d_m1hit,2) + pow(d_m1m2,2) - pow(d_m2hit,2) )/ (2*d_m1hit*d_m1m2));
	    
	// //        Float_t alpha2;
	// //        alpha2 = acos( ( pow(d_m2hit,2) + pow(d_m1m2,2) - pow(d_m1hit,2) )/ (2*d_m2hit*d_m1m2));
	    
	// //        if(m_debug>10){
	// // 	 std::cout<<" distance between muons  "<<d_m1m2<<std::endl;
	// // 	 std::cout<<" distance between m1 and hit  "<<d_m1hit<<std::endl;
	// // 	 std::cout<<" distance between m2 and hit  "<<d_m2hit<<std::endl;
	// //        }


	// //        Float_t h;
	// //        h = d_m1hit*sin(alpha);
	       
	// //        if(m_debug>10){
	// // 	 std::cout<<"    alpha1    "<<alpha<<"  alpha2   "<<alpha2<<std::endl;
	// // 	 std::cout<<"   h value   "<<h<<std::endl;
	// //        }
	       
	// //        if( ( (alpha<1.57 && alpha2<1.57) && h<radius[m]) || d_m1hit<radius[m] || d_m2hit<radius[m]){
	// // 	 recovermj2[m] = true;
	// // 	 if(m_debug>10) std::cout<<" recovery of muJetF   "<<std::endl;
	// //        }
	// //      }
	// //    }


	// //    if(!dim1_hit && dim2_hit){

	// //      if(m_debug>10) std::cout<<" number of nearby hits  "<<rechitposmj1.size()<<std::endl;
	    
	// //      Float_t d_m1m2;  // distance between muons
	// //      d_m1m2 = sqrt(pow(mj1m0pos.x() - mj1m1pos.x(),2) + pow(mj1m0pos.y() - mj1m1pos.y(),2));
	
	// //      Float_t d_m1hit;
	// //      Float_t d_m2hit;

	// //      for(uint32_t l=0;l<rechitposmj1.size();l++){
	       
	// //        d_m1hit = sqrt(pow(mj1m0pos.x() - rechitposmj1[l].x(),2)+pow(mj1m0pos.y() - rechitposmj1[l].y(),2));
	// //        d_m2hit = sqrt(pow(mj1m1pos.x() - rechitposmj1[l].x(),2)+pow(mj1m1pos.y() - rechitposmj1[l].y(),2));
	       
	// //        Float_t alpha;
	// //        alpha = acos( ( pow(d_m1hit,2) + pow(d_m1m2,2) - pow(d_m2hit,2) )/ (2*d_m1hit*d_m1m2));
	      
	// //        Float_t alpha2;
	// //        alpha2 = acos( ( pow(d_m2hit,2) + pow(d_m1m2,2) - pow(d_m1hit,2) )/ (2*d_m2hit*d_m1m2));
	       
	// //        if(m_debug>10){
	// // 	 std::cout<<" distance between muons  "<<d_m1m2<<std::endl;
	// // 	 std::cout<<" distance between m1 and hit  "<<d_m1hit<<std::endl;
	// // 	 std::cout<<" distance between m2 and hit  "<<d_m2hit<<std::endl;
	// //        }
	// //        Float_t h;
	// //        h = d_m1hit*sin(alpha);
	       
	// //        if(m_debug>10){
	// // 	 std::cout<<"    alpha1    "<<alpha<<"  alpha2   "<<alpha2<<std::endl;
	// // 	 std::cout<<"   h value   "<<h<<std::endl;
	// //        }
	      
	// //        if( ( (alpha<1.57 && alpha2<1.57) && h<radius[m])  || d_m1hit<radius[m] || d_m2hit<radius[m]){
	// // 	 recovermj1[m] = true;
	// // 	 if(m_debug>10) std::cout<<" recovery of muJetC   "<<std::endl;
	// //        }
	// //      }
	// //    }
	// //  }

	// //  if( (dim1_hit&&!dim2_hit) && recovermj2[0])  b_hitrecover_mj2_r0005=1;
	// //  if( (dim1_hit&&!dim2_hit) && recovermj2[1])  b_hitrecover_mj2_r005=1;
	// //  if( (dim1_hit&&!dim2_hit) && recovermj2[2])  b_hitrecover_mj2_r05=1;
	// //  if( (dim1_hit&&!dim2_hit) && recovermj2[3])  b_hitrecover_mj2_r01=1;
	// //  if( (dim1_hit&&!dim2_hit) && recovermj2[4])  b_hitrecover_mj2_r5=1;

	// //  if( (!dim1_hit&&dim2_hit) && recovermj1[0])  b_hitrecover_mj1_r0005=1;
	// //  if( (!dim1_hit&&dim2_hit) && recovermj1[1])  b_hitrecover_mj1_r005=1;
	// //  if( (!dim1_hit&&dim2_hit) && recovermj1[2])  b_hitrecover_mj1_r05=1;
	// //  if( (!dim1_hit&&dim2_hit) && recovermj1[3])  b_hitrecover_mj1_r01=1;
	// //  if( (!dim1_hit&&dim2_hit) && recovermj1[4])  b_hitrecover_mj1_r5=1;






	// // if(m_debug>10){
	// //   std::cout<<" MuJetC   "<<std::endl;
	// //   std::cout<<" muon1 position in x   "<<mj1m0pos.x()<<std::endl;
	// //   std::cout<<" muon1 position in y   "<<mj1m0pos.y()<<std::endl;
	// //   //	  std::cout<<" muon1 position in z   "<<mj1m0pos.z()<<std::endl;
    
	// //   std::cout<<" muon2 position in x   "<<mj1m1pos.x()<<std::endl;
	// //   std::cout<<" muon2 position in y   "<<mj1m1pos.y()<<std::endl;
	// //   //	  std::cout<<" muon2 position in z   "<<mj1m1pos.z()<<std::endl;
    
    
	// //   std::cout<<" MuJetF   "<<std::endl;
	// //   std::cout<<" muon1 position in x   "<<mj2m0pos.x()<<std::endl;
	// //   std::cout<<" muon1 position in y   "<<mj2m0pos.y()<<std::endl;
	// //   //	  std::cout<<" muon1 position in z   "<<mj2m0pos.z()<<std::endl;
    
	// //   std::cout<<" muon2 position in x   "<<mj2m1pos.x()<<std::endl;
	// //   std::cout<<" muon2 position in y   "<<mj2m1pos.y()<<std::endl;
	// //   //	  std::cout<<" muon2 position in z   "<<mj2m1pos.z()<<std::endl;
	// // }
	
	// // Float_t mj1_dm1m2 = sqrt(pow(mj1m0pos.x()-mj1m1pos.x(),2)+pow(mj1m0pos.y()-mj1m1pos.y(),2));
	// // Float_t mj2_dm1m2 = sqrt(pow(mj2m0pos.x()-mj2m1pos.x(),2)+pow(mj2m0pos.y()-mj2m1pos.y(),2));
	
	
	// // b_dist_muon_muJetC = mj1_dm1m2;
	// // b_dist_muon_muJetF = mj2_dm1m2;

	
	// // if(m_debug>10){
	// //   std::cout<<" distance between muons in MuJet1 xz "<<mj1_dm1m2<<std::endl;
	// //   std::cout<<" distance between muons in MuJet2 xz "<<mj2_dm1m2<<std::endl;
	// // }

	// // if(m_debug>10){
	// //   if(dim1_hit) std::cout<<" MuJet1 with at least one muon in the 1st pixel layer  "<<std::endl;
	// //   if(dim2_hit) std::cout<<" MuJet2 with at least one muon in the 1st pixel layer  "<<std::endl;
	// // }
	
      
	// // if(dim1_hit && dim2_hit){
	// //   if(m_debug>10) std::cout<<"  No need for hit recovery   "<<std::endl; 
	// // }
	// // if(!dim1_hit && !dim2_hit) {
	// //   if(m_debug>10) std::cout<<"  Both dimuons need the hit recovery (very unlikely case) not considering for the moment "<<std::endl;
	// // }


	// // Bool_t recovermj2[5]={false,false,false,false};
	// // Bool_t recovermj1[5]={false,false,false,false};


	// // Float_t radius[5] ={0.0005,0.005,0.01,0.05,0.5};  // radius to look around the trajectory for compatible hits.


	// //  for(int m=0;m<5;m++){

	// //    if(dim1_hit && !dim2_hit){
	    
	// //      if(m_debug>10) std::cout<<" number of nearby hits  "<<rechitposmj2.size()<<std::endl;
	  
	// //      Float_t d_m1m2;  // distance between muons
	// //      d_m1m2 = sqrt(pow(mj2m0pos.x() - mj2m1pos.x(),2) + pow(mj2m0pos.y() - mj2m1pos.y(),2));
	  
	// //      Float_t d_m1hit;
	// //      Float_t d_m2hit;
	  
	// //      for(uint32_t l=0;l<rechitposmj2.size();l++){
	    
	// //        d_m1hit = sqrt(pow(mj2m0pos.x() - rechitposmj2[l].x(),2)+pow(mj2m0pos.y() - rechitposmj2[l].y(),2));
	// //        d_m2hit = sqrt(pow(mj2m1pos.x() - rechitposmj2[l].x(),2)+pow(mj2m1pos.y() - rechitposmj2[l].y(),2));
	    
	// //        Float_t alpha;
	// //        alpha = acos( ( pow(d_m1hit,2) + pow(d_m1m2,2) - pow(d_m2hit,2) )/ (2*d_m1hit*d_m1m2));
	    
	// //        Float_t alpha2;
	// //        alpha2 = acos( ( pow(d_m2hit,2) + pow(d_m1m2,2) - pow(d_m1hit,2) )/ (2*d_m2hit*d_m1m2));
	    
	// //        if(m_debug>10){
	// // 	 std::cout<<" distance between muons  "<<d_m1m2<<std::endl;
	// // 	 std::cout<<" distance between m1 and hit  "<<d_m1hit<<std::endl;
	// // 	 std::cout<<" distance between m2 and hit  "<<d_m2hit<<std::endl;
	// //        }


	// //        Float_t h;
	// //        h = d_m1hit*sin(alpha);
	       
	// //        if(m_debug>10){
	// // 	 std::cout<<"    alpha1    "<<alpha<<"  alpha2   "<<alpha2<<std::endl;
	// // 	 std::cout<<"   h value   "<<h<<std::endl;
	// //        }
	       
	// //        if( ( (alpha<1.57 && alpha2<1.57) && h<radius[m]) || d_m1hit<radius[m] || d_m2hit<radius[m]){
	// // 	 recovermj2[m] = true;
	// // 	 if(m_debug>10) std::cout<<" recovery of muJetF   "<<std::endl;
	// //        }
	// //      }
	// //    }


	// //    if(!dim1_hit && dim2_hit){

	// //      if(m_debug>10) std::cout<<" number of nearby hits  "<<rechitposmj1.size()<<std::endl;
	    
	// //      Float_t d_m1m2;  // distance between muons
	// //      d_m1m2 = sqrt(pow(mj1m0pos.x() - mj1m1pos.x(),2) + pow(mj1m0pos.y() - mj1m1pos.y(),2));
	
	// //      Float_t d_m1hit;
	// //      Float_t d_m2hit;

	// //      for(uint32_t l=0;l<rechitposmj1.size();l++){
	       
	// //        d_m1hit = sqrt(pow(mj1m0pos.x() - rechitposmj1[l].x(),2)+pow(mj1m0pos.y() - rechitposmj1[l].y(),2));
	// //        d_m2hit = sqrt(pow(mj1m1pos.x() - rechitposmj1[l].x(),2)+pow(mj1m1pos.y() - rechitposmj1[l].y(),2));
	       
	// //        Float_t alpha;
	// //        alpha = acos( ( pow(d_m1hit,2) + pow(d_m1m2,2) - pow(d_m2hit,2) )/ (2*d_m1hit*d_m1m2));
	      
	// //        Float_t alpha2;
	// //        alpha2 = acos( ( pow(d_m2hit,2) + pow(d_m1m2,2) - pow(d_m1hit,2) )/ (2*d_m2hit*d_m1m2));
	       
	// //        if(m_debug>10){
	// // 	 std::cout<<" distance between muons  "<<d_m1m2<<std::endl;
	// // 	 std::cout<<" distance between m1 and hit  "<<d_m1hit<<std::endl;
	// // 	 std::cout<<" distance between m2 and hit  "<<d_m2hit<<std::endl;
	// //        }
	// //        Float_t h;
	// //        h = d_m1hit*sin(alpha);
	       
	// //        if(m_debug>10){
	// // 	 std::cout<<"    alpha1    "<<alpha<<"  alpha2   "<<alpha2<<std::endl;
	// // 	 std::cout<<"   h value   "<<h<<std::endl;
	// //        }
	      
	// //        if( ( (alpha<1.57 && alpha2<1.57) && h<radius[m])  || d_m1hit<radius[m] || d_m2hit<radius[m]){
	// // 	 recovermj1[m] = true;
	// // 	 if(m_debug>10) std::cout<<" recovery of muJetC   "<<std::endl;
	// //        }
	// //      }
	// //    }
	// //  }

	// //  if( (dim1_hit&&!dim2_hit) && recovermj2[0])  b_hitrecover_mj2_r0005=1;
	// //  if( (dim1_hit&&!dim2_hit) && recovermj2[1])  b_hitrecover_mj2_r005=1;
	// //  if( (dim1_hit&&!dim2_hit) && recovermj2[2])  b_hitrecover_mj2_r05=1;
	// //  if( (dim1_hit&&!dim2_hit) && recovermj2[3])  b_hitrecover_mj2_r01=1;
	// //  if( (dim1_hit&&!dim2_hit) && recovermj2[4])  b_hitrecover_mj2_r5=1;

	// //  if( (!dim1_hit&&dim2_hit) && recovermj1[0])  b_hitrecover_mj1_r0005=1;
	// //  if( (!dim1_hit&&dim2_hit) && recovermj1[1])  b_hitrecover_mj1_r005=1;
	// //  if( (!dim1_hit&&dim2_hit) && recovermj1[2])  b_hitrecover_mj1_r05=1;
	// //  if( (!dim1_hit&&dim2_hit) && recovermj1[3])  b_hitrecover_mj1_r01=1;
	// //  if( (!dim1_hit&&dim2_hit) && recovermj1[4])  b_hitrecover_mj1_r5=1;


	// //  if(m_debug>10){
	// //    if( (dim1_hit&&!dim2_hit) && recovermj2[0])  cout<<" hit recover for mujet2 and 0.0005cm  "<<endl;
	// //    if( (dim1_hit&&!dim2_hit) && recovermj2[1])  cout<<" hit recover for mujet2 and 0.005cm  "<<endl;
	// //    if( (dim1_hit&&!dim2_hit) && recovermj2[2])  cout<<" hit recover for mujet2 and 0.01cm  "<<endl;
	// //    if( (dim1_hit&&!dim2_hit) && recovermj2[3])  cout<<" hit recover for mujet2 and 0.05cm  "<<endl;
	// //    if( (dim1_hit&&!dim2_hit) && recovermj2[4])  cout<<" hit recover for mujet2 and 0.5cm  "<<endl;
	   
	// //    if( (!dim1_hit&&dim2_hit) && recovermj1[0])  cout<<" hit recover for mujet1 and 0.0005cm  "<<endl;   
	// //    if( (!dim1_hit&&dim2_hit) && recovermj1[1])  cout<<" hit recover for mujet1 and 0.005cm  "<<endl;  
	// //    if( (!dim1_hit&&dim2_hit) && recovermj1[2])  cout<<" hit recover for mujet1 and 0.01cm  "<<endl; 
	// //    if( (!dim1_hit&&dim2_hit) && recovermj1[3])  cout<<" hit recover for mujet1 and 0.05cm  "<<endl; 
	// //    if( (!dim1_hit&&dim2_hit) && recovermj1[4])  cout<<" hit recover for mujet1 and 0.5cm  "<<endl;
	// //  }

	  //	}
}
