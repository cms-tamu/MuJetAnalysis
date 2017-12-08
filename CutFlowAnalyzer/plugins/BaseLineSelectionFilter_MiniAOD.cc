// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

//******************************************************************************
//                           Class declaration
//******************************************************************************

class BaseLineSelectionFilter_MiniAOD : public edm::EDFilter
{
public:
  explicit BaseLineSelectionFilter_MiniAOD(const edm::ParameterSet&);
  ~BaseLineSelectionFilter_MiniAOD();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  virtual void beginJob() ;
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

  //****************************************************************************
  //          RECO LEVEL VARIABLES, BRANCHES, COUNTERS AND SELECTORS
  //****************************************************************************

  // Labels to access
  edm::EDGetTokenT<std::vector<pat::Muon> > m_muons;
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
BaseLineSelectionFilter_MiniAOD::BaseLineSelectionFilter_MiniAOD(const edm::ParameterSet& iConfig)
{
  m_muons           = consumes<std::vector<pat::Muon> >(edm::InputTag("slimmedMuons"));
}


BaseLineSelectionFilter_MiniAOD::~BaseLineSelectionFilter_MiniAOD()
{
}

//
// member functions
//

// ------------ method called for each event  ------------
bool
BaseLineSelectionFilter_MiniAOD::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;

  //****************************************************************************
  //                          RECO LEVEL ANALYSIS START
  //****************************************************************************

  edm::Handle<std::vector<pat::Muon> > muonsH;
  iEvent.getByToken(m_muons, muonsH);
  const std::vector<pat::Muon>& muons = *muonsH.product();

  // require at least 4 muons with 8 GeV and 1 muon with 17 GeV in the barrel region
  int nMu8 = 0;
  int nMu17Barrel = 0;
  for (const auto& p : muons){
    if (p.pt() >= 8) nMu8++;
    if (p.pt() >= 17 and std::abs(p.eta())<0.9) nMu17Barrel++;
  }

  return nMu8 >= 4 and nMu17Barrel >= 1;
}


// ------------ method called once each job just before starting event loop  ------------
void
BaseLineSelectionFilter_MiniAOD::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
BaseLineSelectionFilter_MiniAOD::endJob()
{
}

// ------------ method called when starting to processes a run  ------------
void
BaseLineSelectionFilter_MiniAOD::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void
BaseLineSelectionFilter_MiniAOD::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void
BaseLineSelectionFilter_MiniAOD::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void
BaseLineSelectionFilter_MiniAOD::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
BaseLineSelectionFilter_MiniAOD::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//Indentation change
//define this as a plug-in
DEFINE_FWK_MODULE(BaseLineSelectionFilter_MiniAOD);
