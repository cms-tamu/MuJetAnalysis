#ifndef MuJetAnalysis_DataFormats_MultiMuon_h
#define MuJetAnalysis_DataFormats_MultiMuon_h

/**
  \class    pat::MultiMuon MultiMuon.h "MuJetAnalysis/DataFormats/interface/MultiMuon.h"
  \brief    Analysis-level particle class

   MultiMuon implements an analysis-level multi-muon class within the 'pat'
   namespace.
*/

// uncomment for compiling in strict FWLite
// #define MULTIMUONCANDIDATE_FOR_FWLITE

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "MuJetAnalysis/DataFormats/interface/MultiLepton.h"

class TransientTrackBuilder;

// Define typedefs for convenience
namespace pat {
   class   MultiMuon;
   typedef std::vector<MultiMuon>              MultiMuonCollection; 
   typedef edm::Ref<MultiMuonCollection>       MultiMuonRef; 
   typedef edm::RefVector<MultiMuonCollection> MultiMuonRefVector; 
}

// Class definition
namespace pat {
  class MultiMuon : public MultiLepton<Muon> {
    public:
    /// default constructor
    MultiMuon() : MultiLepton<Muon>() {}
    /// constructor
    MultiMuon(double phi) : MultiLepton<Muon>(phi) {} 
	 
    /// constructor with muons
    MultiMuon( std::vector<const pat::Muon*> &muons,
	             const TransientTrackBuilder   *transientTrackBuilder = NULL,
	             const reco::TrackCollection   *tracks                = NULL,
	             const pat::MuonCollection     *allmuons              = NULL,
	             const CaloTowerCollection     *caloTowers            = NULL,
	             double centralTrackIsolationCone       = 0.,
	             double unionTrackIsolationCone         = 0.,
	             double centralTrackThresholdPt         = 1e6,
	             double unionTrackThresholdPt           = 1e6,
	             double centralCaloIsolationCone        = 0.,
	             double unionCaloIsolationCone          = 0.,
	             double centralNumberAboveThresholdCone = 0.,
	             double unionNumberAboveThresholdCone   = 0.,
	             double centralNumberAboveThresholdPt   = 1e6,
	             double unionNumberAboveThresholdPt     = 1e6);
	 
    /// constructor from a composite candidate
    MultiMuon(const pat::MultiMuon & aMultiMuon);

    /// destructor
    virtual ~MultiMuon();

    /// required reimplementation of the Candidate's clone method
    MultiMuon * clone() const { return new MultiMuon(*this); }

    /// cast daughters as MultiMuons
    const pat::Muon *muon(int i) const { return dynamic_cast<const pat::Muon*>(daughter(i)); }

    /// calculate a vertex from the daughter muons (performed by constructor if transientTrackBuilder != NULL)
    virtual bool calculateVertex(const TransientTrackBuilder *transientTrackBuilder);

    // Calorimeter Isolation
    virtual void calculateCaloIsolation(const CaloTowerCollection *caloTowers, double centralCone, double unionCone);

    // calculate isolation (performed by constructor if tracks, muons, and caloTowers != NULL)
    // Track Isolation
    virtual void calculateTrackIsolation(const  reco::TrackCollection *tracks,
	                                 const  pat::MuonCollection   *allmuons,
	                                 double centralCone,
	                                 double unionCone,
	                                 double centralThreshold,
	                                 double unionThreshold,
	                                 TTree   *diagnosticTTree = NULL,
	                                 Float_t *diagnosticdR    = NULL,
	                                 Float_t *diagnosticpT    = NULL);

    // Calorimeter Isolation
    void calculateNumberAboveThresholdIsolation(const  reco::TrackCollection *tracks,
						const  pat::MuonCollection   *allmuons,
						double centralCone,
						double unionCone,
						double centralThreshold,
						double unionThreshold,
						TTree   *diagnosticTTree = NULL,
						Float_t *diagnosticdR    = NULL,
						Float_t *diagnosticpT    = NULL);
	 
    /// does this MultiMuon overlap another one? or contain a given muon?
    bool overlaps(const pat::MultiMuon &aMultiMuon) const;
    bool contains(const pat::Muon &aMuon) const;

    /// create a new MultiMuon which has muons from this and aMultiMuon
    pat::MultiMuon merge(const pat::MultiMuon        &aMultiMuon,
			 const TransientTrackBuilder *transientTrackBuilder = NULL,
			 const reco::TrackCollection *tracks                = NULL,
			 const pat::MuonCollection   *allmuons              = NULL,
			 const CaloTowerCollection   *caloTowers            = NULL,
			 double centralTrackIsolationCone       = 0.,
			 double unionTrackIsolationCone         = 0.,
			 double centralTrackThresholdPt         = 1e6,
			 double unionTrackThresholdPt           = 1e6,
			 double centralCaloIsolationCone        = 0.,
			 double unionCaloIsolationCone          = 0.,
			 double centralNumberAboveThresholdCone = 0.,
			 double unionNumberAboveThresholdCone   = 0.,
			 double centralNumberAboveThresholdPt   = 1e6,
			 double unionNumberAboveThresholdPt     = 1e6);

    //------------------------------------------------------------------------------
    // Return vertex results
    //------------------------------------------------------------------------------
    virtual double vertexDz(const Point& myBeamSpot) const {
      if (vertexValid()) {
        GlobalPoint  v      = vertexPoint();
        GlobalVector p      = vertexMomentum();
        double      pt_mag = sqrt( p.x()*p.x() + p.y()*p.y() );
        return (v.z()-myBeamSpot.z()) - ((v.x()-myBeamSpot.x())*p.x()+(v.y()-myBeamSpot.y())*p.y())/pt_mag * p.z()/pt_mag;
      }
      else return muon(0)->innerTrack()->dz(myBeamSpot);
    }
  
    virtual double noiseEcal(const CaloTower &tower) const;
    virtual double noiseHcal(const CaloTower &tower) const;
    virtual double noiseHOcal(const CaloTower &tower) const;
  };
}

#endif // MuJetAnalysis_DataFormats_MultiMuon_h
