#ifndef MuJetAnalysis_DataFormats_MultiElectron_h
#define MuJetAnalysis_DataFormats_MultiElectron_h

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "MuJetAnalysis/DataFormats/interface/MultiLepton.h"

class TransientTrackBuilder;

// Define typedefs for convenience
namespace pat {
   class   MultiElectron;
   typedef std::vector<MultiElectron>              MultiElectronCollection; 
   typedef edm::Ref<MultiElectronCollection>       MultiElectronRef; 
   typedef edm::RefVector<MultiElectronCollection> MultiElectronRefVector; 
}

// Class definition
namespace pat {
  class MultiElectron : public MultiLepton<Electron> {

  public:
    /// default constructor
    MultiElectron() : MultiLepton<Electron>() {}
    /// constructor
    MultiElectron(double phi) : MultiLepton<Electron>(phi) {} 
	 
    /// constructor with electrons
    MultiElectron(std::vector<const pat::Electron*> &electrons,
		  const TransientTrackBuilder   *transientTrackBuilder = NULL,
		  const reco::TrackCollection   *tracks                = NULL,
		  const pat::ElectronCollection     *allelectrons              = NULL,
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
    MultiElectron(const pat::MultiElectron & aMultiElectron);

    /// destructor
    virtual ~MultiElectron();

    /// required reimplementation of the Candidate's clone method
    MultiElectron * clone() const { return new MultiElectron(*this); }

    /// cast daughters as MultiElectrons
    const pat::Electron *electron(int i) const { return dynamic_cast<const pat::Electron*>(daughter(i)); }

    /// does this MultiLepton overlap another one? or contain a given lepton?
    bool overlaps(const pat::MultiElectron&) const;
    bool contains(const pat::Electron &) const;

    /// calculate a vertex from the daughter leptons (performed by constructor if transientTrackBuilder != NULL)
    virtual bool calculateVertex(const TransientTrackBuilder *transientTrackBuilder);

    // calculate isolation (performed by constructor if tracks, electrons, and caloTowers != NULL)
    // Track Isolation
    virtual void calculateTrackIsolation(const reco::TrackCollection *tracks,
				 const pat::ElectronCollection   *allelectrons,
				 double centralCone,
				 double unionCone,
				 double centralThreshold,
				 double unionThreshold,
				 TTree   *diagnosticTTree = NULL,
				 Float_t *diagnosticdR    = NULL,
				 Float_t *diagnosticpT    = NULL);    

    virtual void calculateNumberAboveThresholdIsolation(const reco::TrackCollection *tracks,
						const  pat::ElectronCollection   *allelectrons,
						double centralCone,
						double unionCone,
						double centralThreshold,
						double unionThreshold,
						TTree   *diagnosticTTree = NULL,
						Float_t *diagnosticdR    = NULL,
						Float_t *diagnosticpT    = NULL);

    /// create a new MultiElectron which has electrons from this and aMultiElectron
    pat::MultiElectron merge(const pat::MultiElectron &aMultiElectron,
			     const TransientTrackBuilder *transientTrackBuilder = NULL,
			     const reco::TrackCollection *tracks                = NULL,
			     const pat::ElectronCollection *allelectrons        = NULL,
			     const CaloTowerCollection *caloTowers              = NULL,
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

    virtual double vertexDz(const Point& myBeamSpot) const;

    virtual double noiseEcal(const CaloTower &tower) const;
    virtual double noiseHcal(const CaloTower &tower) const; 
    virtual double noiseHOcal(const CaloTower &tower) const;
  };
}

#endif // MuJetAnalysis_DataFormats_MultiElectron_h
