#ifndef MuJetAnalysis_DataFormats_MultiElectron_h
#define MuJetAnalysis_DataFormats_MultiElectron_h

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "MuJetAnalysis/DataFormats/interface/MultiLepton.h"

// Define typedefs for convenience
namespace pat {
   class   MultiElectron;
   typedef std::vector<MultiElectron>              MultiElectronCollection; 
   typedef edm::Ref<MultiElectronCollection>       MultiElectronRef; 
   typedef edm::RefVector<MultiElectronCollection> MultiElectronRefVector; 
}

// Class definition
namespace pat {
  class MultiElectron : public MultiLepton<reco::GsfElectron> {

  public:
    /// default constructor
  MultiElectron() : MultiLepton<reco::GsfElectron>() {}
    
  MultiElectron(double phi) : MultiLepton<reco::GsfElectron>() { 
      setP4( PolarLorentzVector(0,0,phi,0)); 
    }
	 
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
    virtual MultiElectron * clone() const { return new MultiElectron(*this); }

    /// cast daughters as MultiElectrons
    const pat::Electron *electron(int i) const { return dynamic_cast<const pat::Electron*>(daughter(i)); }

    /* /// calculate a vertex from the daughter electrons (performed by constructor if transientTrackBuilder != NULL) */
    /* bool calculateVertex(const TransientTrackBuilder *transientTrackBuilder); */

    /*
    // calculate isolation (performed by constructor if tracks, electrons, and caloTowers != NULL)
    // Track Isolation
    void calculateTrackIsolation(const reco::TrackCollection *tracks,
				 const  pat::ElectronCollection   *allelectrons,
				 double centralCone,
				 double unionCone,
				 double centralThreshold,
				 double unionThreshold,
				 TTree   *diagnosticTTree = NULL,
				 Float_t *diagnosticdR    = NULL,
				 Float_t *diagnosticpT    = NULL);
    
    // Calorimeter Isolation
    void calculateCaloIsolation(const CaloTowerCollection *caloTowers, double centralCone, double unionCone);

    void calculateNumberAboveThresholdIsolation(const reco::TrackCollection *tracks,
						const  pat::ElectronCollection   *allelectrons,
						double centralCone,
						double unionCone,
						double centralThreshold,
						double unionThreshold,
						TTree   *diagnosticTTree = NULL,
						Float_t *diagnosticdR    = NULL,
						Float_t *diagnosticpT    = NULL);
    
    /// create a new MultiElectron which has electrons from this and aMultiElectron
    pat::MultiElectron merge(const pat::MultiElectron        &aMultiElectron,
			     const TransientTrackBuilder *transientTrackBuilder = NULL,
			     const reco::TrackCollection *tracks                = NULL,
			     const pat::ElectronCollection   *allelectrons              = NULL,
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
    */
    
    protected:
    
    double noiseEcal(const CaloTower &tower) const;
    double noiseHcal(const CaloTower &tower) const;
    double noiseHOcal(const CaloTower &tower) const;
    void   buildPermutation(std::vector<std::vector<int> > &results, std::vector<int> working, int where, int value) const;
    
    void   checkVertex() const;
    
    // Consistent vertex (calculated by MuJetAnalysis/AnalysisTools/interface/ConsistentVertexesCalculator.h)
    void     checkConsistentVtx() const;

  };
}

#endif // MuJetAnalysis_DataFormats_MultiElectron_h
