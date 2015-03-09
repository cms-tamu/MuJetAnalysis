//
// $Id: HAA4MuCandidate.cc,v 1.2 2010/09/22 22:17:28 pivarski Exp $
//
// Jim Pivarski <pivarski@physics.tamu.edu>
// 

#include "MuJetAnalysis/DataFormats/interface/HAA4MuCandidate.h"

/// default constructor
pat::HAA4MuCandidate::HAA4MuCandidate(const pat::MultiMuon *axialHiggs0, const pat::MultiMuon *axialHiggs1) {
   pat::CompositeCandidate();

   int charge = 0;
   LorentzVector lorentzVector;
   std::vector<const reco::GenParticle*> genParticles;
  
   addDaughter(*axialHiggs0);
   charge += axialHiggs0->charge();
   lorentzVector += axialHiggs0->p4();
   genParticles.push_back(axialHiggs0->genParticle());
  
   addDaughter(*axialHiggs1);
   charge += axialHiggs1->charge();
   lorentzVector += axialHiggs1->p4();
   genParticles.push_back(axialHiggs1->genParticle());
  
   setCharge(charge);
   setP4( PolarLorentzVector(lorentzVector.pt(),lorentzVector.eta(),lorentzVector.phi(),lorentzVector.mass()));

   std::map<const reco::Candidate*,unsigned int> ancestorCounter;
   for (std::vector<const reco::GenParticle*>::const_iterator genParticle = genParticles.begin();  genParticle != genParticles.end();  ++genParticle) {
      if (*genParticle != NULL) {
	 const reco::Candidate *mother = (*genParticle)->mother();
	 while (mother != NULL) {
	    if (ancestorCounter.find(mother) == ancestorCounter.end()) {
	       ancestorCounter[mother] = 0;
	    }
	    ancestorCounter[mother]++;
	    mother = mother->mother();
	 }
      }
   }

   const reco::Candidate *youngestCommonAncestor = NULL;
   unsigned int maxDepth = 0;
   for (std::map<const reco::Candidate*,unsigned int>::const_iterator ancestor = ancestorCounter.begin();  ancestor != ancestorCounter.end();  ++ancestor) {
      if (ancestor->second == numberOfDaughters()) {
	 unsigned int depth = 0;
	 for (const reco::Candidate *mother = ancestor->first;  mother != NULL;  mother = mother->mother()) {
	    depth++;
	 }
	 if (depth > maxDepth) {
	    maxDepth = depth;
	    youngestCommonAncestor = ancestor->first;
	 }
      }
   }

   if (youngestCommonAncestor != NULL) {
      const reco::GenParticle *asGenParticle = dynamic_cast<const reco::GenParticle*>(youngestCommonAncestor);
      setGenParticle(*asGenParticle);
   }
}

/// destructor
pat::HAA4MuCandidate::~HAA4MuCandidate() {}
