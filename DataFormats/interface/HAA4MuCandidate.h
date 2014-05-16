//
// $Id: HAA4MuCandidate.h,v 1.1 2010/09/22 22:12:29 pivarski Exp $
//
// Jim Pivarski <pivarski@physics.tamu.edu>
// 

#ifndef MuJetAnalysis_DataFormats_HAA4MuCandidate_h
#define MuJetAnalysis_DataFormats_HAA4MuCandidate_h

/**
  \class    pat::HAA4MuCandidate HAA4MuCandidate.h "MuJetAnalysis/DataFormats/interface/HAA4MuCandidate.h"
  \brief    Analysis-level particle class

   HAA4MuCandidate implements an analysis-level multi-muon class within the 'pat'
   namespace.

  \version  $Id: HAA4MuCandidate.h,v 1.1 2010/09/22 22:12:29 pivarski Exp $
*/

#include "DataFormats/PatCandidates/interface/CompositeCandidate.h"
#include "MuJetAnalysis/DataFormats/interface/MultiMuon.h"

// Define typedefs for convenience
namespace pat {
   class HAA4MuCandidate;
   typedef std::vector<HAA4MuCandidate>              HAA4MuCandidateCollection; 
   typedef edm::Ref<HAA4MuCandidateCollection>       HAA4MuCandidateRef; 
   typedef edm::RefVector<HAA4MuCandidateCollection> HAA4MuCandidateRefVector; 
}

// Class definition
namespace pat {
   class HAA4MuCandidate : public pat::CompositeCandidate {
      public:
	 /// default constructor
	 HAA4MuCandidate() : pat::CompositeCandidate() {};

	 /// constructor with muons
	 HAA4MuCandidate(const pat::MultiMuon *axialHiggs0, const pat::MultiMuon *axialHiggs1);

	 /// constructor from a composite candidate
	 HAA4MuCandidate(const pat::HAA4MuCandidate & aHAA4MuCandidate) : pat::CompositeCandidate(aHAA4MuCandidate) {};

	 /// destructor
	 virtual ~HAA4MuCandidate();

	 /// required reimplementation of the Candidate's clone method
	 virtual HAA4MuCandidate * clone() const { return new HAA4MuCandidate(*this); }

	 /// cast daughters as MultiMuons
	 const MultiMuon *axialHiggs(int i) const { return dynamic_cast<const MultiMuon*>(daughter(i)); }

	 /// return opening angles with or without the vertex correction
	 double dphi(bool vertex = false) const {
	    double phi0, phi1;
	    if (vertex) {
	       phi0 = axialHiggs(0)->vertexP4().phi();
	       phi1 = axialHiggs(1)->vertexP4().phi();
	    }
	    else {
	       phi0 = daughter(0)->phi();
	       phi1 = daughter(1)->phi();
	    }
	    double delta = phi0 - phi1;
	    while (delta > M_PI) delta -= 2.*M_PI;
	    while (delta < -M_PI) delta += 2.*M_PI;
	    return delta;
	 }
	 double deta(bool vertex = false) const {
	    double eta0, eta1;
	    if (vertex) {
	       eta0 = axialHiggs(0)->vertexP4().eta();
	       eta1 = axialHiggs(1)->vertexP4().eta();
	    }
	    else {
	       eta0 = daughter(0)->eta();
	       eta1 = daughter(1)->eta();
	    }
	    return eta0 - eta1;
	 }
	 double dR(bool vertex = false) const {
	    return sqrt(pow(dphi(vertex), 2) + pow(deta(vertex), 2));
	 }
    
	 /// return dR_1 + dR_2 of the two axial Higgses
	 double dRsum(bool vertex = false) const {
	    return axialHiggs(0)->dR(0, 1, vertex) + axialHiggs(1)->dR(0, 1, vertex);
	 }
   };
}

#endif // MuJetAnalysis_DataFormats_HAA4MuCandidate_h
