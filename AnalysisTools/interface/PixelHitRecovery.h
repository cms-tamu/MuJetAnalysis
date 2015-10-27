#ifndef PixelHitRecovery_H
#define PixelHitRecovery_H
// -*- C++ -*-
//
// Package:    AnalysisTools
// Class:      PixelHitRecovery
// 
//
// Original Author:  Sven Dildick
//
//

// user include files
#include "TTree.h"
#include "TRandom3.h"
#include "TMath.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "DataFormats/GeometryVector/interface/GlobalVector.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"

#include "MuJetAnalysis/DataFormats/interface/MultiMuon.h"
 

//******************************************************************************
//                Class to perform pixel hit recovery calculation                 
//******************************************************************************

class PixelHitRecovery 
{
 public:
  PixelHitRecovery(const edm::Event&, const edm::EventSetup&, const edm::ParameterSet&);
  ~PixelHitRecovery();

  void run();

 private:
    
  int  _debug;
  
};

#endif // PixelHitRecovery_H
