// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"

#include "DataFormats/TrackReco/interface/Track.h"

//
// class declaration
//

class HighPtBarrelMuonFilter : public edm::EDFilter {
   public:
      explicit HighPtBarrelMuonFilter(const edm::ParameterSet&);
      ~HighPtBarrelMuonFilter();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual bool beginRun(edm::Run&, edm::EventSetup const&);
      virtual bool endRun(edm::Run&, edm::EventSetup const&);
      virtual bool beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      virtual bool endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);

      // ----------member data ---------------------------
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
HighPtBarrelMuonFilter::HighPtBarrelMuonFilter(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed

}


HighPtBarrelMuonFilter::~HighPtBarrelMuonFilter()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
HighPtBarrelMuonFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  int nMuonsInBarrelPt17;
	int nMuonsPt8;

  edm::Handle<reco::MuonCollection> muons;
	iEvent.getByLabel("muons", muons);

  // Loop over all muons and count
  // - number of Tracker Muons with our private ID cuts with pT > 8 GeV and |eta| < 2.4
  // - number of Tracker Muons with our private ID cuts with pT > 17 GeV and |eta| < 0.9
  nMuonsInBarrelPt17 = 0;
	nMuonsPt8 = 0;
  for (reco::MuonCollection::const_iterator muon = muons->begin(); muon != muons->end(); ++muon) {
		if (    muon->isTrackerMuon()
		     && muon->numberOfMatches(reco::Muon::SegmentAndTrackArbitration) >= 2
         && muon->innerTrack().isNonnull()
		     && muon->innerTrack()->numberOfValidHits() >= 8
		     && muon->innerTrack()->normalizedChi2() < 4. ) {
			if ( muon->pt() > 8.  && fabs(muon->eta()) < 2.4 ) nMuonsPt8++;
			if ( muon->pt() > 17. && fabs(muon->eta()) < 0.9 ) nMuonsInBarrelPt17++;
		}
	}
	// Accept event if there are
	// - 3 or more muons with pT > 8 GeV and |eta| < 2.4
	// - 1 or more muons with pT > 17 GeV and |eta| < 0.9
	if ( nMuonsPt8 >= 3 && nMuonsInBarrelPt17 >= 1 ) return true;

  // Loop over all muons and count
  // - number of PF Muons with "Loose" ID with pT > 8 GeV and |eta| < 2.4
  // - number of PF Muons with "Loose" ID with pT > 17 GeV and |eta| < 0.9
  // "Loose" ID = isPFMuon() && ( isGlobalMuon() || isTrackerMuon() )
  // See https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonId#Loose_Muon
  nMuonsInBarrelPt17 = 0;
	nMuonsPt8 = 0;
  for (reco::MuonCollection::const_iterator muon = muons->begin(); muon != muons->end(); ++muon) {
		if (    muon->isPFMuon()
		     && ( muon->isGlobalMuon() || muon->isTrackerMuon() ) ) {
			if ( muon->pt() > 8.  && fabs(muon->eta()) < 2.4 ) nMuonsPt8++;
			if ( muon->pt() > 17. && fabs(muon->eta()) < 0.9 ) nMuonsInBarrelPt17++;
		}
	}
	// Accept event if there are
	// - 3 or more muons with pT > 8 GeV and |eta| < 2.4
	// - 1 or more muons with pT > 17 GeV and |eta| < 0.9
	if ( nMuonsPt8 >= 3 && nMuonsInBarrelPt17 >= 1 ) return true;

	return false;
}

// ------------ method called once each job just before starting event loop  ------------
void
HighPtBarrelMuonFilter::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
HighPtBarrelMuonFilter::endJob() {
}

// ------------ method called when starting to processes a run  ------------
bool
HighPtBarrelMuonFilter::beginRun(edm::Run&, edm::EventSetup const&)
{
  return true;
}

// ------------ method called when ending the processing of a run  ------------
bool
HighPtBarrelMuonFilter::endRun(edm::Run&, edm::EventSetup const&)
{
  return true;
}

// ------------ method called when starting to processes a luminosity block  ------------
bool
HighPtBarrelMuonFilter::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
  return true;
}

// ------------ method called when ending the processing of a luminosity block  ------------
bool
HighPtBarrelMuonFilter::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
  return true;
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
HighPtBarrelMuonFilter::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(HighPtBarrelMuonFilter);
