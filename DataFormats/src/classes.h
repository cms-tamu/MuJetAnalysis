#include "MuJetAnalysis/DataFormats/interface/MultiElectron.h"
#include "MuJetAnalysis/DataFormats/interface/MultiMuon.h"
#include "MuJetAnalysis/DataFormats/interface/HAA4MuCandidate.h"
#include <vector>

namespace {
   struct dictionary {
	 std::vector<pat::MultiMuon> stdvectorpatMultiMuon;
	 edm::Wrapper<std::vector<pat::MultiMuon> > edmWrapperstdvectorpatMultiMuon;
	 edm::Ref<std::vector<pat::MultiMuon> > edmRefstdvectorpatMultiMuon;
	 edm::RefProd<std::vector<pat::MultiMuon> > edmRefProdstdvectorpatMultiMuon;
	 edm::Wrapper<edm::RefVector<std::vector<pat::MultiMuon> > > edmWrapperedmRefVectorstdvectorpatMultiMuon;
	 edm::reftobase::Holder<reco::Candidate, pat::MultiMuonRef> edmreftobaseHolderrecoCandidatepatMultiMuonRef;

	 std::vector<pat::MultiElectron> stdvectorpatMultiElectron;
	 edm::Wrapper<std::vector<pat::MultiElectron> > edmWrapperstdvectorpatMultiElectron;
	 edm::Ref<std::vector<pat::MultiElectron> > edmRefstdvectorpatMultiElectron;
	 edm::RefProd<std::vector<pat::MultiElectron> > edmRefProdstdvectorpatMultiElectron;
	 edm::Wrapper<edm::RefVector<std::vector<pat::MultiElectron> > > edmWrapperedmRefVectorstdvectorpatMultiElectron;
	 edm::reftobase::Holder<reco::Candidate, pat::MultiElectronRef> edmreftobaseHolderrecoCandidatepatMultiElectronRef;

	 std::vector<pat::HAA4MuCandidate> stdvectorpatHAA4MuCandidate;
	 edm::Wrapper<std::vector<pat::HAA4MuCandidate> > edmWrapperstdvectorpatHAA4MuCandidate;
	 edm::Ref<std::vector<pat::HAA4MuCandidate> > edmRefstdvectorpatHAA4MuCandidate;
	 edm::RefProd<std::vector<pat::HAA4MuCandidate> > edmRefProdstdvectorpatHAA4MuCandidate;
	 edm::Wrapper<edm::RefVector<std::vector<pat::HAA4MuCandidate> > > edmWrapperedmRefVectorstdvectorpatHAA4MuCandidate;
	 edm::reftobase::Holder<reco::Candidate, pat::HAA4MuCandidateRef> edmreftobaseHolderrecoCandidatepatHAA4MuCandidateRef;

	 std::vector<Point3DBase<float,GlobalTag> > stdvectorPoint3DBasefloatGlobalTag;
   };
}
