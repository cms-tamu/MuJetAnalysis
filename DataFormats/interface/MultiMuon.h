//
// $Id: MultiMuon.h,v 1.12 2012/05/01 10:00:52 aysen Exp $
//
// Jim Pivarski <pivarski@physics.tamu.edu>
//

#ifndef MuJetAnalysis_DataFormats_MultiMuon_h
#define MuJetAnalysis_DataFormats_MultiMuon_h

/**
  \class    pat::MultiMuon MultiMuon.h "MuJetAnalysis/DataFormats/interface/MultiMuon.h"
  \brief    Analysis-level particle class

   MultiMuon implements an analysis-level multi-muon class within the 'pat'
   namespace.

  \version  $Id: MultiMuon.h,v 1.12 2012/05/01 10:00:52 aysen Exp $
*/

// uncomment for compiling in strict FWLite
// #define MULTIMUONCANDIDATE_FOR_FWLITE

#include "DataFormats/PatCandidates/interface/CompositeCandidate.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "DataFormats/GeometryVector/interface/GlobalVector.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/CaloTowers/interface/CaloTower.h"
#include "DataFormats/CaloTowers/interface/CaloTowerDefs.h"
#include "TMath.h"
#include "TTree.h"

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
  class MultiMuon : public pat::CompositeCandidate {
    public:
	 /// default constructor
    MultiMuon() : pat::CompositeCandidate()
      , m_vertexValid(false)
      , m_vertexValid_fitted(false)
      , m_vertexValid_mindist(false)
      , m_chi2(0.)
      , m_ndof(0.)
      , m_mindisttrack(0.)
      , m_mindisttrack_scan(0.)
      , m_vtx_x_scan(0.)
      , m_vtx_y_scan(0.)
      , m_vtx_z_scan(0.)
      //, m_centralTrackIsolationCone(0.)
      //, m_unionTrackIsolationCone(0.)
      //, m_centralTrackThresholdPt(0.)
      //, m_unionTrackThresholdPt(0.)
      //, m_centralCaloIsolationCone(0.)
      //, m_unionCaloIsolationCone(0.)
      //, m_centralNumberAboveThresholdCone(0.)
      //, m_unionNumberAboveThresholdCone(0.)
      //, m_centralNumberAboveThresholdPt(0.)
      //, m_unionNumberAboveThresholdPt(0.)
      //, m_centralTrackIsolation(0.)
      //, m_unionTrackIsolation(0.)
      //, m_centralECALIsolation(0.)
      //, m_unionECALIsolation(0.)
      //, m_centralHCALIsolation(0.)
      //, m_unionHCALIsolation(0.)
      //, m_centralNumberAboveThreshold(0)
      //, m_unionNumberAboveThreshold(0)
      {};

    MultiMuon(double phi) : pat::CompositeCandidate()
      , m_vertexValid(false)
      , m_vertexValid_fitted(false)
      , m_vertexValid_mindist(false)
      , m_chi2(0.)
      , m_ndof(0.)
      , m_mindisttrack(0.)
      , m_mindisttrack_scan(0.)
      , m_vtx_x_scan(0.)
      , m_vtx_y_scan(0.)
      , m_vtx_z_scan(0.)
      //, m_centralTrackIsolationCone(0.)
      //, m_unionTrackIsolationCone(0.)
      //, m_centralTrackThresholdPt(0.)
      //, m_unionTrackThresholdPt(0.)
      //, m_centralCaloIsolationCone(0.)
      //, m_unionCaloIsolationCone(0.)
      //, m_centralNumberAboveThresholdCone(0.)
      //, m_unionNumberAboveThresholdCone(0.)
      //, m_centralNumberAboveThresholdPt(0.)
      //, m_unionNumberAboveThresholdPt(0.)
      //, m_centralTrackIsolation(0.)
      //, m_unionTrackIsolation(0.)
      //, m_centralECALIsolation(0.)
      //, m_unionECALIsolation(0.)
      //, m_centralHCALIsolation(0.)
      //, m_unionHCALIsolation(0.)
      //, m_centralNumberAboveThreshold(0)
      //, m_unionNumberAboveThreshold(0)
      { setP4( PolarLorentzVector(0,0,phi,0)); }

    /// constructor with muons
    MultiMuon( std::vector<const pat::Muon*> &muons,
	             const TransientTrackBuilder   *transientTrackBuilder = NULL,
	             //const reco::TrackCollection   *tracks                = NULL,
	             //const pat::MuonCollection     *allmuons              = NULL,
	             //const CaloTowerCollection     *caloTowers            = NULL,
	             //double centralTrackIsolationCone       = 0.,
	             //double unionTrackIsolationCone         = 0.,
	             //double centralTrackThresholdPt         = 1e6,
	             //double unionTrackThresholdPt           = 1e6,
	             //double centralCaloIsolationCone        = 0.,
	             //double unionCaloIsolationCone          = 0.,
	             //double centralNumberAboveThresholdCone = 0.,
	             //double unionNumberAboveThresholdCone   = 0.,
	             //double centralNumberAboveThresholdPt   = 1e6,
	             //double unionNumberAboveThresholdPt     = 1e6,
	             int barrelPixelLayer = 1,
	             int endcapPixelLayer = 1);
    /// constructor from a composite candidate
    MultiMuon(const pat::MultiMuon & aMultiMuon);

    /// destructor
    virtual ~MultiMuon();

    /// required reimplementation of the Candidate's clone method
    virtual MultiMuon * clone() const { return new MultiMuon(*this); }

    /// cast daughters as MultiMuons
    const pat::Muon *muon(int i) const { return dynamic_cast<const pat::Muon*>(daughter(i)); }

    /// calculate a vertex from the daughter muons (performed by constructor if transientTrackBuilder != NULL)
    bool calculateVertex(const TransientTrackBuilder *transientTrackBuilder, int barrelPixelLayer, int endcapPixelLayer);

/*
    // calculate isolation (performed by constructor if tracks, muons, and caloTowers != NULL)
    // Track Isolation
    void calculateTrackIsolation( const  reco::TrackCollection *tracks,
	                                 const  pat::MuonCollection   *allmuons,
	                                 double centralCone,
	                                 double unionCone,
	                                 double centralThreshold,
	                                 double unionThreshold,
	                                 TTree   *diagnosticTTree = NULL,
	                                 Float_t *diagnosticdR    = NULL,
	                                 Float_t *diagnosticpT    = NULL);
                                   */
/*
    // Calorimeter Isolation
    void calculateCaloIsolation(const CaloTowerCollection *caloTowers, double centralCone, double unionCone);*/
/*
    void calculateNumberAboveThresholdIsolation( const  reco::TrackCollection *tracks,
	                                                const  pat::MuonCollection   *allmuons,
	                                                double centralCone,
	                                                double unionCone,
	                                                double centralThreshold,
	                                                double unionThreshold,
	                                                TTree   *diagnosticTTree = NULL,
	                                                Float_t *diagnosticdR    = NULL,
	                                                Float_t *diagnosticpT    = NULL);*/

    /// does this MultiMuon overlap another one? or contain a given muon?
    bool overlaps(const pat::MultiMuon &aMultiMuon) const;
    bool contains(const pat::Muon &aMuon) const;

    /// create a new MultiMuon which has muons from this and aMultiMuon
    pat::MultiMuon merge( const pat::MultiMuon        &aMultiMuon,
	                        const TransientTrackBuilder *transientTrackBuilder = NULL
	                        //const reco::TrackCollection *tracks                = NULL,
	                        //const pat::MuonCollection   *allmuons              = NULL,
	                        //const CaloTowerCollection   *caloTowers            = NULL,
	                        //double centralTrackIsolationCone       = 0.,
	                        //double unionTrackIsolationCone         = 0.,
	                        //double centralTrackThresholdPt         = 1e6,
	                        //double unionTrackThresholdPt           = 1e6,
	                        //double centralCaloIsolationCone        = 0.,
	                        //double unionCaloIsolationCone          = 0.,
	                        //double centralNumberAboveThresholdCone = 0.,
	                        //double unionNumberAboveThresholdCone   = 0.,
	                        //double centralNumberAboveThresholdPt   = 1e6,
	                        //double unionNumberAboveThresholdPt     = 1e6
                        );

//------------------------------------------------------------------------------
// Return vertex results
//------------------------------------------------------------------------------
    bool            vertexValid()                   const { return m_vertexValid; }
    bool            vertexValid_fitted()            const { return m_vertexValid_fitted; }
    bool            vertexValid_mindist()           const { return m_vertexValid_mindist; }
    double          vertexChi2()                    const { checkVertex();  return m_chi2; }
    double          vertexNdof()                    const { checkVertex();  return m_ndof; }
    double          mindist_track()                 const { checkVertex();  return m_mindisttrack; }
    double          mindist_trackscan()             const { checkVertex();  return m_mindisttrack_scan; }
    double          get_vtx_x_scan()                const { return m_vtx_x_scan; }
    double          get_vtx_y_scan()                const { return m_vtx_y_scan; }
    double          get_vtx_z_scan()                const { return m_vtx_z_scan; }

    double          vertexNormalizedChi2()          const { checkVertex();  return (m_ndof > 0. ? m_chi2/m_ndof : 0.); }
    double          vertexProb()                    const { checkVertex();  return (m_ndof > 0. ? TMath::Prob(m_chi2, m_ndof) : 0.); }
    CovarianceMatrix my_vertexCovariance()            const { checkVertex();  return m_covarianceMatrix; }
    double          my_vertexCovariance(int i, int j) const { checkVertex();  return m_covarianceMatrix.At(i, j); }

    /// return position/momentum of each muon closest to vertex
    GlobalPoint      vertexPCA(int i)                 const { checkVertex();  return m_vertexPCA[i]; }
    CovarianceMatrix vertexPCACovarianceMatrix(int i) const { checkVertex();  return m_vertexPCACovarianceMatrix[i]; }
    LorentzVector    vertexP4(int i)                  const { checkVertex();  return m_vertexP4[i]; }
    GlobalVector     vertexMomentum(int i)            const { LorentzVector v = vertexP4(i);  return GlobalVector(v.x(), v.y(), v.z()); }

    /// return position/momentum of multimuon object at vertex
    /// for position, use virtual const Point& reco::LeafCandidate::vertex();
    GlobalPoint   vertexPoint()    const { checkVertex();  Point v = vertex();  return GlobalPoint(v.x(), v.y(), v.z()); }
    LorentzVector vertexP4()       const {
      checkVertex();
      LorentzVector v;
      for (unsigned int i = 0;  i < numberOfDaughters();  i++) {
        v += vertexP4(i);
      }
      return v;
    }
    GlobalVector  vertexMomentum() const { LorentzVector v = vertexP4();  return GlobalVector(v.x(), v.y(), v.z()); }
    double       vertexMass()     const { return vertexP4().mass(); }

    double vertexDz(const Point& myBeamSpot) const {
      if (vertexValid()) {
        GlobalPoint  v      = vertexPoint();
        GlobalVector p      = vertexMomentum();
        double      pt_mag = sqrt( p.x()*p.x() + p.y()*p.y() );
        return ( v.z()-myBeamSpot.z() ) - ( (v.x()-myBeamSpot.x())*p.x() + (v.y()-myBeamSpot.y())*p.y() )/pt_mag * p.z()/pt_mag;
      }
      //else if ( muon(0)->innerTrack().isAvailable() && muon(0)->isTrackerMuon() && muon(0)->isPFMuon() ){
      //use innerTrack only if the muon is tracker muon & PF muon
      else if ( muon(0)->innerTrack().isAvailable() ){
        return muon(0)->innerTrack()->dz(myBeamSpot);
      }
      //else if ( muon(1)->innerTrack().isAvailable() && muon(1)->isTrackerMuon() && muon(1)->isPFMuon() ){
      else if ( muon(1)->innerTrack().isAvailable() ){
        return muon(1)->innerTrack()->dz(myBeamSpot);
      }
      else if ( muon(0)->outerTrack().isAvailable() ){
        return muon(0)->outerTrack()->dz(myBeamSpot);
      }
      else return muon(1)->outerTrack()->dz(myBeamSpot);
    }

    /// return the distance of flight from the primary vertex in the direction of momentum
    /// in 2D
    double vertexLxy(GlobalPoint primaryVertex) const {
      GlobalPoint  v = vertexPoint();
      GlobalVector p = vertexMomentum();
      double      pt_mag = sqrt( p.x()*p.x() + p.y()*p.y() );
      return ((v.x()-primaryVertex.x())*p.x() + (v.y()-primaryVertex.y())*p.y())/pt_mag;
    };

    double vertexLxy(double x, double y, double z) const {
      return vertexLxy(GlobalPoint(x, y, z));
    };

    /// in 3D
    double vertexL(GlobalPoint primaryVertex) const {
      GlobalPoint  v  = vertexPoint();
      GlobalVector p  = vertexMomentum();
      double      p_mag = sqrt( p.x()*p.x() + p.y()*p.y() + p.z()*p.z() );
      return ( (v.x()-primaryVertex.x())*p.x() + (v.y()-primaryVertex.y())*p.y() + (v.z()-primaryVertex.z())*p.z() ) / p_mag;
    };

    double vertexL(double x, double y, double z) const {
      return vertexL(GlobalPoint(x, y, z));
    };

//------------------------------------------------------------------------------
// Return consistent vertex results (two muon jets are used to find such vertex)
//------------------------------------------------------------------------------
/*
    //bool consistentVtxValid()                            const { return m_consistentVtxValid; }
    //void SetConsistentVtxValid(bool consistentVtxValid) const {  m_consistentVtxValid = consistentVtxValid; }

    void SetConsistentVtx3D(GlobalPoint                           consistentVtx3D)  const { m_consistentVtx3D  = consistentVtx3D; }
    void SetConsistentVtxP4(math::XYZTLorentzVector               consistentVtxP4)  const { m_consistentVtxP4  = consistentVtxP4; }
    void SetVConsistentVtxP4(std::vector<math::XYZTLorentzVector> vConsistentVtxP4) const { m_vConsistentVtxP4 = vConsistentVtxP4; }

    GlobalPoint                          consistentVtx3D()       const { checkConsistentVtx(); return m_consistentVtx3D; }
    math::XYZTLorentzVector              consistentVtxP4()       const { checkConsistentVtx(); return m_consistentVtxP4; }
    std::vector<math::XYZTLorentzVector> vConsistentVtxP4()      const { checkConsistentVtx(); return m_vConsistentVtxP4; }
    math::XYZTLorentzVector              consistentVtxP4(int i)  const { checkConsistentVtx(); return m_vConsistentVtxP4[i]; }

    GlobalPoint  consistentVtxPoint()    const { return consistentVtx3D(); }
    GlobalVector consistentVtxMomentum() const { LorentzVector v = consistentVtxP4();  return GlobalVector(v.x(), v.y(), v.z()); }
    double      consistentVtxMass()     const { return consistentVtxP4().mass(); }

    double consistentVtxDz(GlobalPoint myBeamSpot) const {
      checkConsistentVtx();
      GlobalPoint  v      = consistentVtxPoint();
      GlobalVector p      = consistentVtxMomentum();
      double      pt_mag = sqrt( p.x()*p.x() + p.y()*p.y() );
      return (v.z()-myBeamSpot.z()) - ((v.x()-myBeamSpot.x())*p.x()+(v.y()-myBeamSpot.y())*p.y())/pt_mag * p.z()/pt_mag;
    }

    /// return the distance of flight from the primary vertex in the direction of momentum
    /// in 2D
    double consistentVtxLxy(GlobalPoint primaryVertex) const {
      checkConsistentVtx();
      GlobalPoint  v = consistentVtxPoint();
      GlobalVector p = consistentVtxMomentum();
      double      pt_mag = sqrt( p.x()*p.x() + p.y()*p.y() );
      return ((v.x()-primaryVertex.x())*p.x() + (v.y()-primaryVertex.y())*p.y())/pt_mag;
    };

    double consistentVtxLxy(double x, double y, double z) const {
      return consistentVtxLxy(GlobalPoint(x, y, z));
    };

    /// in 3D
    double consistentVtxL(GlobalPoint primaryVertex) const {
      checkConsistentVtx();
      GlobalPoint  v  = consistentVtxPoint();
      GlobalVector p  = consistentVtxMomentum();
      double      p_mag = sqrt( p.x()*p.x() + p.y()*p.y() + p.z()*p.z() );
      return ( (v.x()-primaryVertex.x())*p.x() + (v.y()-primaryVertex.y())*p.y() + (v.z()-primaryVertex.z())*p.z() ) / p_mag;
    };

    double consistentVtxL(double x, double y, double z) const {
      return consistentVtxL(GlobalPoint(x, y, z));
    };
*/

    /// return daughter's momentum vector in the COM frame
    GlobalVector daughterCOM(int i, bool vertex = false) const;
    /// return daughter's momentum vector in the COM frame, rotated to the boost axis (+z is parent's direction)
    GlobalVector daughterCOMrot(int i, bool vertex = false) const;
    /// return daughter's cos(theta) where theta is the angle between the daughter's momentum and the parent's momentum, in the center-of-mass frame
    double daughterCOMcosTheta(int i, bool vertex = false) const;

    /// return opening angles with or without the vertex correction
    double dphi(int i, int j, bool vertex = false) const {
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
    double deta(int i, int j, bool vertex = false) const {
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
    double dR(int i, int j, bool vertex = false) const {
      return sqrt(pow(dphi(i, j, vertex), 2) + pow(deta(i, j, vertex), 2));
    }
    double dRmax(bool vertex = false) const {
      double max = 0.;
      for (unsigned int i = 0;  i < numberOfDaughters();  i++) {
        for (unsigned int j = i+1;  j < numberOfDaughters();  j++) {
          double dR_ij = dR(i, j, vertex);
          if (dR_ij > max) max = dR_ij;
        }
      }
      return max;
    }

/*
    /// return the combination of final-state pairs most consistent with being the same mass
    /// (assumes all cascades decay to muon pairs through a single lowest-mass resonance)
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
    int    unionNumberAboveThreshold()   const { return m_unionNumberAboveThreshold; }*/

    bool sameTrack(const reco::Track *one, const reco::Track *two) const;

    protected:
/*
    double noiseEcal(const CaloTower &tower) const;
    double noiseHcal(const CaloTower &tower) const;
    double noiseHOcal(const CaloTower &tower) const;*/
    void   buildPermutation(std::vector<std::vector<int> > &results, std::vector<int> working, int where, int value) const;

    bool   m_vertexValid;
    bool   m_vertexValid_fitted;
    bool   m_vertexValid_mindist;

    void   checkVertex() const;
    double m_chi2;
    double m_ndof;
    double m_mindisttrack;
    double m_mindisttrack_scan;
    double m_vtx_x_scan;
    double m_vtx_y_scan;
    double m_vtx_z_scan;

    CovarianceMatrix              m_covarianceMatrix;
    std::vector<GlobalPoint>      m_vertexPCA;
    std::vector<CovarianceMatrix> m_vertexPCACovarianceMatrix;
    std::vector<LorentzVector>    m_vertexP4;
/*
    // Consistent vertex (calculated by MuJetAnalysis/AnalysisTools/interface/ConsistentVertexesCalculator.h)
    mutable bool                                 m_consistentVtxValid;
    void     checkConsistentVtx() const;
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
    int    m_centralNumberAboveThreshold;
    int    m_unionNumberAboveThreshold;
*/
    int    m_barrelPixelLayer;
    int    m_endcapPixelLayer;
  };

  // functions that define fiducial volume
  double pixelBarrelR(int pixelBarrelLayer);
  double pixelBarrelR2(int pixelBarrelLayer);
  double pixelEndcapZ(int pixelEndcapLayer);
}

#endif // MuJetAnalysis_DataFormats_MultiMuon_h
