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

class FilterSample3RecoMu_MiniAOD : public edm::EDFilter
{
public:
  explicit FilterSample3RecoMu_MiniAOD(const edm::ParameterSet&);
  ~FilterSample3RecoMu_MiniAOD();

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
FilterSample3RecoMu_MiniAOD::FilterSample3RecoMu_MiniAOD(const edm::ParameterSet& iConfig)
{
  m_muons           = consumes<std::vector<pat::Muon> >(edm::InputTag("slimmedMuons"));
}


FilterSample3RecoMu_MiniAOD::~FilterSample3RecoMu_MiniAOD()
{
}

//
// member functions
//

// ------------ method called for each event  ------------
bool
FilterSample3RecoMu_MiniAOD::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;

  //****************************************************************************
  //                          RECO LEVEL ANALYSIS START
  //****************************************************************************

  edm::Handle<std::vector<pat::Muon> > muons;
  iEvent.getByToken(m_muons, muons);
  const std::vector<pat::Muon>& muonC = *muons.product();

  // require at least 3 muons
  int nMu = 0;
  for (const auto& p : muonC){
    std::cout << p.pt() << " " << p.eta() << " " << p.phi() << std::endl;
    if (p.pt() >= 5) nMu++;
  }
  if (nMu >= 3)
    std::cout << "Pass" << std::endl;
  return nMu >= 3;
}


// ------------ method called once each job just before starting event loop  ------------
void
FilterSample3RecoMu_MiniAOD::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
FilterSample3RecoMu_MiniAOD::endJob()
{
}

// ------------ method called when starting to processes a run  ------------
void
FilterSample3RecoMu_MiniAOD::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void
FilterSample3RecoMu_MiniAOD::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void
FilterSample3RecoMu_MiniAOD::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void
FilterSample3RecoMu_MiniAOD::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
FilterSample3RecoMu_MiniAOD::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//Indentation change
//define this as a plug-in
DEFINE_FWK_MODULE(FilterSample3RecoMu_MiniAOD);
