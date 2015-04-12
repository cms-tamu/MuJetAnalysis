#ifndef MuJetAnalysis_DataFormats_MultiLepton_h
#define MuJetAnalysis_DataFormats_MultiLepton_h

/**
  \class    pat::MultiLepton<LeptonType> MultiLepton.h "MuJetAnalysis/DataFormats/interface/MultiLepton.h"
  \brief    Analysis-level particle class

   MultiLepton defines an analysis-level multi-lepton template base class within the 'pat'
   namespace.
   MultiLepton is implemented by MultiElectron and MultiMuon
*/

// uncomment for compiling in strict FWLite
// #define MULTIMUONCANDIDATE_FOR_FWLITE

#include "DataFormats/PatCandidates/interface/CompositeCandidate.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "DataFormats/GeometryVector/interface/GlobalVector.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/PatCandidates/interface/Lepton.h"
#include "DataFormats/CaloTowers/interface/CaloTower.h"
#include "DataFormats/CaloTowers/interface/CaloTowerFwd.h"
#include "TMath.h"
#include "TTree.h"

class TransientTrackBuilder;

// Class definition
namespace pat {
  
  template <class LeptonType>
  class MultiLepton : public pat::CompositeCandidate 
  {
    public:
    /// default constructor
    MultiLepton();
    /// constructor
    MultiLepton(double phi);
    /// constructor from a composite candidate
    MultiLepton(const MultiLepton<LeptonType> & aMultiLepton);
    /// destructor
    virtual ~MultiLepton() {}

    /// cast daughters as MultiLeptons
    const pat::Lepton<LeptonType> *lepton(int i) const { return dynamic_cast<const pat::Lepton<LeptonType>*>(daughter(i)); }
    
    /// calculate a vertex from the daughter leptons (performed by constructor if transientTrackBuilder != NULL)
    virtual bool calculateVertex(const TransientTrackBuilder *transientTrackBuilder)=0;

    // Calorimeter Isolation
    virtual void calculateCaloIsolation(const CaloTowerCollection *caloTowers, double centralCone, double unionCone)=0;
    
    //------------------------------------------------------------------------------
    // Return vertex results
    //------------------------------------------------------------------------------
    bool             vertexValid()                     const { return m_vertexValid; }
    double           vertexChi2()                      const { checkVertex();  return m_chi2; }
    double           vertexNdof()                      const { checkVertex();  return m_ndof; }
    double           vertexNormalizedChi2()            const { checkVertex();  return (m_ndof > 0. ? m_chi2/m_ndof : 0.); }
    double           vertexProb()                      const { checkVertex();  return (m_ndof > 0. ? TMath::Prob(m_chi2, m_ndof) : 0.); }
    CovarianceMatrix my_vertexCovariance()             const { checkVertex();  return m_covarianceMatrix; }
    double           my_vertexCovariance(int i, int j) const { checkVertex();  return m_covarianceMatrix.At(i, j); }
    
    /// return position/momentum of each lepton closest to vertex
    GlobalPoint      vertexPCA(int i)                 const { checkVertex();  return m_vertexPCA[i]; }
    CovarianceMatrix vertexPCACovarianceMatrix(int i) const { checkVertex();  return m_vertexPCACovarianceMatrix[i]; }
    LorentzVector    vertexP4(int i)                  const { checkVertex();  return m_vertexP4[i]; }
    GlobalVector     vertexMomentum(int i)            const { LorentzVector v = vertexP4(i);  return GlobalVector(v.x(), v.y(), v.z()); }

    /// return position/momentum of multilepton object at vertex
    /// for position, use virtual const Point& reco::LeafCandidate::vertex();
    GlobalPoint vertexPoint() const { checkVertex();  Point v = vertex();  return GlobalPoint(v.x(), v.y(), v.z()); }
    LorentzVector vertexP4() const {
      checkVertex();
      LorentzVector v;
      for (unsigned int i = 0;  i < numberOfDaughters();  i++) {
	v += vertexP4(i);
      }
      return v;
    }
    GlobalVector vertexMomentum() const { LorentzVector v = vertexP4();  return GlobalVector(v.x(), v.y(), v.z()); }
    double vertexMass() const { return vertexP4().mass(); }
    virtual double vertexDz(const Point& myBeamSpot) const =0;

    /// return the distance of flight from the primary vertex in the direction of momentum
    /// in 2D
    double vertexLxy(GlobalPoint primaryVertex) const;    
    double vertexLxy(double x, double y, double z) const { return vertexLxy(GlobalPoint(x, y, z)); }
    
    /// in 3D
    double vertexL(GlobalPoint primaryVertex) const;
    double vertexL(double x, double y, double z) const { return vertexL(GlobalPoint(x, y, z)); }
  
    //------------------------------------------------------------------------------
    // Return consistent vertex results (two lepton jets are used to find such vertex)
    //------------------------------------------------------------------------------
    
    bool consistentVtxValid()                           const { return m_consistentVtxValid; }
    void SetConsistentVtxValid(bool consistentVtxValid) const {  m_consistentVtxValid = consistentVtxValid; }
    
    void SetConsistentVtx3D(GlobalPoint                           consistentVtx3D)  const { m_consistentVtx3D  = consistentVtx3D; }
    void SetConsistentVtxP4(math::XYZTLorentzVector               consistentVtxP4)  const { m_consistentVtxP4  = consistentVtxP4; }
    void SetVConsistentVtxP4(std::vector<math::XYZTLorentzVector> vConsistentVtxP4) const { m_vConsistentVtxP4 = vConsistentVtxP4; }
    
    GlobalPoint                          consistentVtx3D()       const { checkConsistentVtx(); return m_consistentVtx3D; }
    math::XYZTLorentzVector              consistentVtxP4()       const { checkConsistentVtx(); return m_consistentVtxP4; }
    std::vector<math::XYZTLorentzVector> vConsistentVtxP4()      const { checkConsistentVtx(); return m_vConsistentVtxP4; }
    math::XYZTLorentzVector              consistentVtxP4(int i)  const { checkConsistentVtx(); return m_vConsistentVtxP4[i]; }
    
    GlobalPoint consistentVtxPoint()    const { return consistentVtx3D(); }
    GlobalVector consistentVtxMomentum() const { LorentzVector v = consistentVtxP4();  return GlobalVector(v.x(), v.y(), v.z()); }
    double consistentVtxMass()     const { return consistentVtxP4().mass(); }
    double consistentVtxDz(GlobalPoint myBeamSpot) const;

    /// return the distance of flight from the primary vertex in the direction of momentum
    /// in 2D
    double consistentVtxLxy(GlobalPoint primaryVertex) const;
    double consistentVtxLxy(double x, double y, double z) const { return consistentVtxLxy(GlobalPoint(x, y, z)); }
    
    /// in 3D
    double consistentVtxL(GlobalPoint primaryVertex) const;
    double consistentVtxL(double x, double y, double z) const { return consistentVtxL(GlobalPoint(x, y, z)); }
  
  
    /// return daughter's momentum vector in the COM frame
    GlobalVector daughterCOM(int i, bool vertex = false) const;
    /// return daughter's momentum vector in the COM frame, rotated to the boost axis (+z is parent's direction)
    GlobalVector daughterCOMrot(int i, bool vertex = false) const;
    /// return daughter's cos(theta) where theta is the angle between the daughter's momentum and the parent's momentum, in the center-of-mass frame
    double daughterCOMcosTheta(int i, bool vertex = false) const;

    /// return opening angles with or without the vertex correction
    double dphi(int i, int j, bool vertex = false) const;
    double deta(int i, int j, bool vertex = false) const;
    double dR(int i, int j, bool vertex = false) const { return sqrt(pow(dphi(i, j, vertex), 2) + pow(deta(i, j, vertex), 2)); }
    double dRmax(bool vertex = false) const;

    /// return the combination of final-state pairs most consistent with being the same mass
    /// (assumes all cascades decay to lepton pairs through a single lowest-mass resonance)
    /// return value is a set of pairs of indices: the first is the mu+, the second is the mu- of each pair
    std::vector<std::pair<int,int> > consistentPairs(bool vertex = false) const;
    /// return just the masses of the most consistent combination
    std::vector<double> consistentPairMasses(bool vertex = false) const;

    /// return isolation information
    double centralTrackIsolationCone()       const { return m_centralTrackIsolationCone; }
    double unionTrackIsolationCone()         const { return m_unionTrackIsolationCone; }
    double centralTrackThresholdPt()         const { return m_centralTrackThresholdPt; }
    double unionTrackThresholdPt()           const { return m_unionTrackThresholdPt; }
    double centralCaloIsolationCone()        const { return m_centralCaloIsolationCone; }
    double unionCaloIsolationCone()          const { return m_unionCaloIsolationCone; }
    double centralNumberAboveThresholdCone() const { return m_centralNumberAboveThresholdCone; }
    double unionNumberAboveThresholdCone()   const { return m_unionNumberAboveThresholdCone; }
    double centralNumberAboveThresholdPt()   const { return m_centralNumberAboveThresholdPt; }
    double unionNumberAboveThresholdPt()     const { return m_unionNumberAboveThresholdPt; }

    double centralTrackIsolation()       const { return m_centralTrackIsolation; }
    double unionTrackIsolation()         const { return m_unionTrackIsolation; }
    double centralECALIsolation()        const { return m_centralECALIsolation; }
    double unionECALIsolation()          const { return m_unionECALIsolation; }
    double centralHCALIsolation()        const { return m_centralHCALIsolation; }
    double unionHCALIsolation()          const { return m_unionHCALIsolation; }
    double centralCaloIsolation()        const { return m_centralECALIsolation + m_centralHCALIsolation; }
    double unionCaloIsolation()          const { return m_unionECALIsolation + m_unionHCALIsolation; }
    int    centralNumberAboveThreshold() const { return m_centralNumberAboveThreshold; }
    int    unionNumberAboveThreshold()   const { return m_unionNumberAboveThreshold; }

    bool sameTrack(const reco::Track *one, const reco::Track *two) const;

    virtual double noiseEcal(const CaloTower &tower) const =0;
    virtual double noiseHcal(const CaloTower &tower) const =0;
    virtual double noiseHOcal(const CaloTower &tower) const =0;

    void buildPermutation(std::vector<std::vector<int> > &results, std::vector<int> working, int where, int value) const;

    void checkVertex() const;
    void checkConsistentVtx() const;

  protected:
    
    bool   m_vertexValid;
    double m_chi2;
    double m_ndof;
    CovarianceMatrix              m_covarianceMatrix;
    std::vector<GlobalPoint>      m_vertexPCA;
    std::vector<CovarianceMatrix> m_vertexPCACovarianceMatrix;
    std::vector<LorentzVector>    m_vertexP4;
    
    // Consistent vertex (calculated by MuJetAnalysis/AnalysisTools/interface/ConsistentVertexesCalculator.h)
    mutable bool                                 m_consistentVtxValid;

    mutable GlobalPoint                          m_consistentVtx3D;
    mutable math::XYZTLorentzVector              m_consistentVtxP4;
    mutable std::vector<math::XYZTLorentzVector> m_vConsistentVtxP4;

    double m_centralTrackIsolationCone;
    double m_unionTrackIsolationCone;
    double m_centralTrackThresholdPt;
    double m_unionTrackThresholdPt;
    double m_centralCaloIsolationCone;
    double m_unionCaloIsolationCone;
    double m_centralNumberAboveThresholdCone;
    double m_unionNumberAboveThresholdCone;
    double m_centralNumberAboveThresholdPt;
    double m_unionNumberAboveThresholdPt;
    double m_centralTrackIsolation;
    double m_unionTrackIsolation;
    double m_centralECALIsolation;
    double m_unionECALIsolation;
    double m_centralHCALIsolation;
    double m_unionHCALIsolation;
    int     m_centralNumberAboveThreshold;
    int     m_unionNumberAboveThreshold;
  };

  template <class LeptonType>
  MultiLepton<LeptonType>::MultiLepton() : pat::CompositeCandidate()
    , m_vertexValid(false)
    , m_chi2(0.)
    , m_ndof(0.)
    , m_centralTrackIsolationCone(0.)
    , m_unionTrackIsolationCone(0.)
    , m_centralTrackThresholdPt(0.)
    , m_unionTrackThresholdPt(0.)
    , m_centralCaloIsolationCone(0.)
    , m_unionCaloIsolationCone(0.)
    , m_centralNumberAboveThresholdCone(0.)
    , m_unionNumberAboveThresholdCone(0.)
    , m_centralNumberAboveThresholdPt(0.)
    , m_unionNumberAboveThresholdPt(0.)
    , m_centralTrackIsolation(0.)
    , m_unionTrackIsolation(0.)
    , m_centralECALIsolation(0.)
    , m_unionECALIsolation(0.)
    , m_centralHCALIsolation(0.)
    , m_unionHCALIsolation(0.)
    , m_centralNumberAboveThreshold(0)
    , m_unionNumberAboveThreshold(0) 
  {
  }

  template <class LeptonType>
  MultiLepton<LeptonType>::MultiLepton(double phi) : pat::CompositeCandidate()
    , m_vertexValid(false)
    , m_chi2(0.)
    , m_ndof(0.)
    , m_centralTrackIsolationCone(0.)
    , m_unionTrackIsolationCone(0.)
    , m_centralTrackThresholdPt(0.)
    , m_unionTrackThresholdPt(0.)
    , m_centralCaloIsolationCone(0.)
    , m_unionCaloIsolationCone(0.)
    , m_centralNumberAboveThresholdCone(0.)
    , m_unionNumberAboveThresholdCone(0.)
    , m_centralNumberAboveThresholdPt(0.)
    , m_unionNumberAboveThresholdPt(0.)
    , m_centralTrackIsolation(0.)
    , m_unionTrackIsolation(0.)
    , m_centralECALIsolation(0.)
    , m_unionECALIsolation(0.)
    , m_centralHCALIsolation(0.)
    , m_unionHCALIsolation(0.)
    , m_centralNumberAboveThreshold(0)
    , m_unionNumberAboveThreshold(0) 
  { 
      setP4( PolarLorentzVector(0,0,phi,0)); 
  }

  /// constructor from MultiLeptonType
  template <class LeptonType>
  MultiLepton<LeptonType>::MultiLepton(const MultiLepton<LeptonType> &aMultiLepton)
  {
    setP4( PolarLorentzVector(aMultiLepton.pt(),aMultiLepton.eta(),aMultiLepton.phi(),aMultiLepton.mass())  );
    
    if (aMultiLepton.genParticle() != NULL) setGenParticle(*(aMultiLepton.genParticle()));
    
    m_vertexValid = aMultiLepton.m_vertexValid;
    m_chi2 = aMultiLepton.m_chi2;
    m_ndof = aMultiLepton.m_ndof;
    m_covarianceMatrix = aMultiLepton.m_covarianceMatrix;
    for (unsigned int i = 0;  i < aMultiLepton.m_vertexPCA.size();  i++) {
      m_vertexPCA.push_back(aMultiLepton.m_vertexPCA[i]);
      m_vertexPCACovarianceMatrix.push_back(aMultiLepton.m_vertexPCACovarianceMatrix[i]);
      m_vertexP4.push_back(aMultiLepton.m_vertexP4[i]);
    }
    
    m_consistentVtxValid = aMultiLepton.m_consistentVtxValid;
    
    m_centralTrackIsolationCone       = aMultiLepton.m_centralTrackIsolationCone;
    m_unionTrackIsolationCone         = aMultiLepton.m_unionTrackIsolationCone;
    m_centralTrackThresholdPt         = aMultiLepton.m_centralTrackThresholdPt;
    m_unionTrackThresholdPt           = aMultiLepton.m_unionTrackThresholdPt;
    m_centralCaloIsolationCone        = aMultiLepton.m_centralCaloIsolationCone;
    m_unionCaloIsolationCone          = aMultiLepton.m_unionCaloIsolationCone;
    m_centralNumberAboveThresholdCone = aMultiLepton.m_centralNumberAboveThresholdCone;
    m_unionNumberAboveThresholdCone   = aMultiLepton.m_unionNumberAboveThresholdCone;
    m_centralNumberAboveThresholdPt   = aMultiLepton.m_centralNumberAboveThresholdPt;
    m_unionNumberAboveThresholdPt     = aMultiLepton.m_unionNumberAboveThresholdPt;
    
    m_centralTrackIsolation       = aMultiLepton.m_centralTrackIsolation;
    m_unionTrackIsolation         = aMultiLepton.m_unionTrackIsolation;
    m_centralECALIsolation        = aMultiLepton.m_centralECALIsolation;
    m_unionECALIsolation          = aMultiLepton.m_unionECALIsolation;
    m_centralHCALIsolation        = aMultiLepton.m_centralHCALIsolation;
    m_unionHCALIsolation          = aMultiLepton.m_unionHCALIsolation;
    m_centralNumberAboveThreshold = aMultiLepton.m_centralNumberAboveThreshold;
    m_unionNumberAboveThreshold   = aMultiLepton.m_unionNumberAboveThreshold;
  }

  template <class LeptonType>
  double MultiLepton<LeptonType>::vertexLxy(GlobalPoint primaryVertex) const 
  {
    GlobalPoint  v = vertexPoint();
    GlobalVector p = vertexMomentum();
    double      pt_mag = sqrt( p.x()*p.x() + p.y()*p.y() );
    return ((v.x()-primaryVertex.x())*p.x() + (v.y()-primaryVertex.y())*p.y())/pt_mag;
  }  

  template <class LeptonType>
  double MultiLepton<LeptonType>::vertexL(GlobalPoint primaryVertex) const 
  { 
    GlobalPoint  v  = vertexPoint();
    GlobalVector p  = vertexMomentum(); 
    double      p_mag = sqrt( p.x()*p.x() + p.y()*p.y() + p.z()*p.z() ); 
    return ( (v.x()-primaryVertex.x())*p.x() + (v.y()-primaryVertex.y())*p.y() + (v.z()-primaryVertex.z())*p.z() ) / p_mag;
  }  

  template <class LeptonType>
  double MultiLepton<LeptonType>::consistentVtxDz(GlobalPoint myBeamSpot) const 
  {
    checkConsistentVtx();
    GlobalPoint  v      = consistentVtxPoint();
    GlobalVector p      = consistentVtxMomentum();
    double      pt_mag = sqrt( p.x()*p.x() + p.y()*p.y() );
    return (v.z()-myBeamSpot.z()) - ((v.x()-myBeamSpot.x())*p.x()+(v.y()-myBeamSpot.y())*p.y())/pt_mag * p.z()/pt_mag;
  }

  template <class LeptonType>
  double MultiLepton<LeptonType>::consistentVtxLxy(GlobalPoint primaryVertex) const 
  {
    checkConsistentVtx();
    GlobalPoint  v = consistentVtxPoint();
    GlobalVector p = consistentVtxMomentum();
    double      pt_mag = sqrt( p.x()*p.x() + p.y()*p.y() );
    return ((v.x()-primaryVertex.x())*p.x() + (v.y()-primaryVertex.y())*p.y())/pt_mag;
  }
  
  template <class LeptonType>
  double MultiLepton<LeptonType>::consistentVtxL(GlobalPoint primaryVertex) const 
  {
    checkConsistentVtx();
    GlobalPoint  v  = consistentVtxPoint();
    GlobalVector p  = consistentVtxMomentum();
    double      p_mag = sqrt( p.x()*p.x() + p.y()*p.y() + p.z()*p.z() );
    return ( (v.x()-primaryVertex.x())*p.x() + (v.y()-primaryVertex.y())*p.y() + (v.z()-primaryVertex.z())*p.z() ) / p_mag;
  }

  template <class LeptonType>
  double MultiLepton<LeptonType>::dphi(int i, int j, bool vertex) const 
  {
    double phi_i, phi_j;
    if (vertex) {
      checkVertex();
      phi_i = vertexP4(i).phi();
      phi_j = vertexP4(j).phi();
    }
    else {
      phi_i = daughter(i)->phi();
      phi_j = daughter(j)->phi();
    }
    double delta = phi_i - phi_j;
    while (delta > M_PI) delta -= 2.*M_PI;
    while (delta < -M_PI) delta += 2.*M_PI;
    return delta;
  }

  template <class LeptonType>
  double MultiLepton<LeptonType>::deta(int i, int j, bool vertex) const 
  {
    double eta_i, eta_j;
    if (vertex) {
      checkVertex();
      eta_i = vertexP4(i).eta();
      eta_j = vertexP4(j).eta();
    }
    else {
      eta_i = daughter(i)->eta();
      eta_j = daughter(j)->eta();
    }
    return eta_i - eta_j;
  }

  template <class LeptonType>
  double MultiLepton<LeptonType>::dRmax(bool vertex) const 
  {
    double max = 0.;
    for (unsigned int i = 0;  i < numberOfDaughters();  i++) {
      for (unsigned int j = i+1;  j < numberOfDaughters();  j++) {
	double dR_ij = dR(i, j, vertex);
	if (dR_ij > max) max = dR_ij;
      }
    }
    return max;
  }

  template <class LeptonType>
  std::vector<std::pair<int,int> > pat::MultiLepton<LeptonType>::consistentPairs(bool vertex) const 
  {
    std::vector<int> positives, negatives;
    for (unsigned int i = 0;  i < numberOfDaughters();  i++) {
      if (daughter(i)->charge() > 0) {
	positives.push_back(i);
      } else {
	negatives.push_back(i);
      }
    }

    std::vector<int> largerset, smallerset;
    if (positives.size() > negatives.size()) {
      largerset = positives;
      smallerset = negatives;
    } else {
      largerset = negatives;
      smallerset = positives;
    }
    std::vector<std::vector<int> > permutations;
    std::vector<int> working;
    buildPermutation(permutations, working, 0, largerset.size() - 1);

    std::vector<int> bestPermutation;
    double minMassDistance = -1.;
    for (std::vector<std::vector<int> >::const_iterator permutation = permutations.begin();  permutation != permutations.end();  ++permutation) {
      std::vector<double> masses;
      unsigned int smallerset_index = 0;
      for (std::vector<int>::const_iterator largerset_index = permutation->begin();  largerset_index != permutation->end();  ++largerset_index, ++smallerset_index) {
	if (smallerset_index < smallerset.size()) {
	  GlobalVector lepton1, lepton2;

	  if (vertex) {
	    lepton1 = vertexMomentum(largerset[*largerset_index]);
	    lepton2 = vertexMomentum(smallerset[smallerset_index]);
	  } else {
	    reco::Candidate::Vector v1 = daughter(largerset[*largerset_index])->momentum();
	    reco::Candidate::Vector v2 = daughter(smallerset[smallerset_index])->momentum();
	    lepton1 = GlobalVector(v1.x(), v1.y(), v1.z());
	    lepton2 = GlobalVector(v2.x(), v2.y(), v2.z());
	  }
        
	  double lepton_mass    = daughter(largerset[*largerset_index])->mass();  // get the lepton mass from CMSSW
	  double total_energy = sqrt(lepton1.mag2() + pow(lepton_mass, 2)) + sqrt(lepton2.mag2() + pow(lepton_mass, 2));
	  double total_px     = lepton1.x() + lepton2.x();
	  double total_py     = lepton1.y() + lepton2.y();
	  double total_pz     = lepton1.z() + lepton2.z();
	  double mass         = sqrt(pow(total_energy, 2) - pow(total_px, 2) - pow(total_py, 2) - pow(total_pz, 2));

	  masses.push_back(mass);
	}
      }
      double massDistance = 0.;
      for (unsigned int i = 0;  i < masses.size();  i++) {
	for (unsigned int j = i + 1;  j < masses.size();  j++) {
	  massDistance += pow(masses[i] - masses[j], 2);
	}
      }

      if (minMassDistance < 0.  ||  massDistance < minMassDistance) {
	bestPermutation = *permutation;
	minMassDistance = massDistance;
      }
    }

    std::vector<std::pair<int,int> > output;
    unsigned int smallerset_index = 0;
    for (std::vector<int>::const_iterator largerset_index = bestPermutation.begin();  largerset_index != bestPermutation.end();  ++largerset_index, ++smallerset_index) {
      if (smallerset_index < smallerset.size()) {
	if (daughter(largerset[*largerset_index])->charge() > 0) {
	  output.push_back(std::pair<int,int>(largerset[*largerset_index], smallerset[smallerset_index]));
	} else {
	  output.push_back(std::pair<int,int>(smallerset[smallerset_index], largerset[*largerset_index]));
	}
      }
    }
  
    return output;
  }

  template <class LeptonType>
  std::vector<double> pat::MultiLepton<LeptonType>::consistentPairMasses(bool vertex) const 
  {
    std::vector<std::pair<int,int> > pairIndicies = consistentPairs(vertex);
    std::vector<double> output;
    
    for (std::vector<std::pair<int,int> >::const_iterator pairIndex = pairIndicies.begin();  pairIndex != pairIndicies.end();  ++pairIndex) {
      GlobalVector lepton1, lepton2;

      assert(daughter(pairIndex->first)->charge() > 0);
      assert(daughter(pairIndex->second)->charge() < 0);

      if (vertex) {
	lepton1 = vertexMomentum(pairIndex->first);
	lepton2 = vertexMomentum(pairIndex->second);
      } else {
	reco::Candidate::Vector v1 = daughter(pairIndex->first)->momentum();
	reco::Candidate::Vector v2 = daughter(pairIndex->second)->momentum();
	lepton1 = GlobalVector(v1.x(), v1.y(), v1.z());
	lepton2 = GlobalVector(v2.x(), v2.y(), v2.z());
      }
      double lepton_mass = daughter(pairIndex->first)->mass();  // get the lepton mass from CMSSW
      double total_energy = sqrt(lepton1.mag2() + pow(lepton_mass, 2)) + sqrt(lepton2.mag2() + pow(lepton_mass, 2));
      double total_px = lepton1.x() + lepton2.x();
      double total_py = lepton1.y() + lepton2.y();
      double total_pz = lepton1.z() + lepton2.z();
      double mass = sqrt(pow(total_energy, 2) - pow(total_px, 2) - pow(total_py, 2) - pow(total_pz, 2));
      
      output.push_back(mass);
    }
    
    return output;
  }

  template <class LeptonType>
  void MultiLepton<LeptonType>::buildPermutation(std::vector<std::vector<int> > &results, std::vector<int> working, int where, int value) const 
  {
    std::vector<int>::iterator iter = working.begin();
    for (int i = 0;  i < where;  i++) ++iter;
    working.insert(iter, value);

    if (value - 1 >= 0) {
      for (unsigned int i = 0;  i <= working.size();  i++) {
	buildPermutation(results, working, i, value - 1);
      }
    } else {
      results.push_back(working);
    }
  }

  template <class LeptonType>
  bool MultiLepton<LeptonType>::sameTrack(const reco::Track *one, const reco::Track *two) const 
  {
    return (fabs(one->px() - two->px()) < 1e-10  &&
	    fabs(one->py() - two->py()) < 1e-10  &&
	    fabs(one->pz() - two->pz()) < 1e-10  &&
	    fabs(one->vx() - two->vx()) < 1e-10  &&
	    fabs(one->vy() - two->vy()) < 1e-10  &&
	    fabs(one->vz() - two->vz()) < 1e-10    );
  }

  template <class LeptonType>
  void MultiLepton<LeptonType>::checkVertex() const 
  {
    if (!m_vertexValid) {
      throw cms::Exception("MultiLepton") << "Request for vertex information, but no vertex has been calculated.";
    }
  }

  template <class LeptonType>
  void  MultiLepton<LeptonType>::checkConsistentVtx() const 
  {
    if (!m_consistentVtxValid) {
      throw cms::Exception("MultiLepton") << "Request for consistent vertex information, but no vertex has been calculated.";
    }
  }  
}

#endif // MuJetAnalysis_DataFormats_MultiLepton_h
