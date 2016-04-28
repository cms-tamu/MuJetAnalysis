void PrintAnalysis(){


  //    TFile *f = new TFile("mGamma_0250.root");
  //    TFile *f = new TFile("mGamma_0250_ctau005.root");
  //    TFile *f = new TFile("mGamma_0250_ctau01.root");
  //    TFile *f = new TFile("mGamma_0250_ctau02.root");
  //    TFile *f = new TFile("mGamma_0250_ctau1.root");
  //   TFile *f = new TFile("mGamma_0250_ctau2.root");
  //    TFile *f = new TFile("mGamma_0250_ctau3.root");
  //    TFile *f = new TFile("mGamma_0250_ctau5.root");
  //    TFile *f = new TFile("mGamma_0275.root");
  //    TFile *f = new TFile("mGamma_0300.root");
  //    TFile *f = new TFile("mGamma_0300_ctau01.root");
  //    TFile *f = new TFile("mGamma_0300_ctau02.root");
  //    TFile *f = new TFile("mGamma_0300_ctau05.root");
  //    TFile *f = new TFile("mGamma_0350.root");

  //    TFile *f = new TFile("mGamma_0400_ctau02.root");
  //    TFile *f = new TFile("mGamma_0400_ctau05.root");
  //    TFile *f = new TFile("mGamma_0400_ctau5.root");
  //    TFile *f = new TFile("mGamma_0550.root");
  //    TFile *f = new TFile("mGamma_0550_ctau02.root");
  //    TFile *f = new TFile("mGamma_0550_ctau1.root");
  //    TFile *f = new TFile("mGamma_0550_ctau2.root");
  //    TFile *f = new TFile("mGamma_0550_ctau3.root");
  //    TFile *f = new TFile("mGamma_0550_ctau5.root");
  //    TFile *f = new TFile("mGamma_0700.root");
  //    TFile *f = new TFile("mGamma_0700_ctau02.root");
  //    TFile *f = new TFile("mGamma_0700_ctau2.root");
  //    TFile *f = new TFile("mGamma_0700_ctau5.root");
  //    TFile *f = new TFile("mGamma_0850.root");
  //    TFile *f = new TFile("mGamma_0850_ctau02.root");
  //    TFile *f = new TFile("mGamma_0850_ctau05.root");
  //    TFile *f = new TFile("mGamma_0850_ctau2.root");
  //    TFile *f = new TFile("mGamma_0850_ctau5.root");
  //    TFile *f = new TFile("mGamma_1000.root");
  //    TFile *f = new TFile("mGamma_1000_ctau02.root");
  //    TFile *f = new TFile("mGamma_1000_ctau1.root");
  //    TFile *f = new TFile("mGamma_1000_ctau2.root");
  //    TFile *f = new TFile("mGamma_1000_ctau3.root");
  //    TFile *f = new TFile("mGamma_1000_ctau5.root");

  //   TFile *f = new TFile("DoubleMuParked_Run2012ABCD.root");

  TFile *f = new TFile("DarkSUSY_mH_125_mGammaD_0250_ctauExp_5_8TeV-madgraph452_bridge224_LHE_pythia6_537p4_PAT_v1.root");


  //   f->cd("Analysis");
  f->cd("cutFlowAnalyzer");
  
  f->ls();


  Int_t event;
  Int_t run;
  Int_t lumi;

  Int_t m_events;
  Int_t m_events4GenMu;
  Int_t m_events1GenMu17;
  Int_t m_events2GenMu8;
  Int_t m_events3GenMu8;
  Int_t m_events4GenMu8;
  Int_t m_events1SelMu17;
  Int_t m_events2SelMu8;
  Int_t m_events3SelMu8;
  Int_t m_events4SelMu8;
  Int_t m_events2MuJets;
  Int_t m_events2DiMuons;
  Int_t m_eventsDz2DiMuonsOK;
  Int_t m_eventsDiMuonsHLTFired;
  Int_t m_eventsMassDiMuonsOK;
  Int_t m_eventsIsoDiMuonsOK;
  Int_t m_eventsVertexOK;

  Int_t m_eventsOK_diMuonsLxy;

  Bool_t is1SelMu17;
  Bool_t is4SelMu8;
  Bool_t is2MuJets;
  Bool_t is2DiMuons;
  Bool_t isDzDiMuonsOK;
  Bool_t isDiMuonsHLTFired;
  Bool_t isMassDiMuonsOK;
  Bool_t isIsoDiMuonsOK;
  Bool_t isVLT;
  Bool_t isOK_diMuonsLxy;
  Bool_t isVertexOK;

  Bool_t is4GenMu;
  Bool_t is1GenMu17;
  Bool_t is2GenMu8;
  Bool_t is3GenMu8;
  Bool_t is4GenMu8;
  Bool_t is2SelMu8;
  Bool_t is3SelMu8;

  TTree *t = (TTree*)f->Get("cutFlowAnalyzer/Events");

  m_events = 0;
  m_events4GenMu = 0;
  m_events1GenMu17 = 0;
  m_events2GenMu8 = 0;
  m_events3GenMu8 = 0;
  m_events4GenMu8 = 0;
  m_events1SelMu17 = 0;
  m_events2SelMu8 = 0;
  m_events3SelMu8 = 0;
  m_events4SelMu8 = 0;
  m_events2MuJets = 0;
  m_events2DiMuons = 0;
  m_eventsDz2DiMuonsOK = 0;
  m_eventsDiMuonsHLTFired = 0;
  m_eventsMassDiMuonsOK = 0;
  m_eventsIsoDiMuonsOK = 0;
  m_eventsVertexOK = 0;
  m_eventsOK_diMuonsLxy = 0;


  t->SetBranchAddress("event", &event);
  t->SetBranchAddress("run", &run);
  t->SetBranchAddress("lumi", &lumi);

  t->SetBranchAddress("is1SelMu17", &is1SelMu17);
  t->SetBranchAddress("is4SelMu8", &is4SelMu8);
  t->SetBranchAddress("is2MuJets", &is2MuJets);
  t->SetBranchAddress("is2DiMuons", &is2DiMuons);
  t->SetBranchAddress("isDzDiMuonsOK", &isDzDiMuonsOK);
  t->SetBranchAddress("isDiMuonHLTFired", &isDiMuonsHLTFired);
  t->SetBranchAddress("isMassDiMuonsOK", &isMassDiMuonsOK);
  t->SetBranchAddress("isIsoDiMuonsOK", &isIsoDiMuonsOK);
  t->SetBranchAddress("isVLT", &isVLT);
  t->SetBranchAddress("isOK_diMuonsLxy", &isOK_diMuonsLxy);
  t->SetBranchAddress("isVertexOK", &isVertexOK);

  t->SetBranchAddress("is4GenMu", &is4GenMu);
  t->SetBranchAddress("is1GenMu17", &is1GenMu17);
  t->SetBranchAddress("is2GenMu8", &is2GenMu8);
  t->SetBranchAddress("is3GenMu8", &is3GenMu8);
  t->SetBranchAddress("is4GenMu8", &is4GenMu8);
  t->SetBranchAddress("is2SelMu8", &is2SelMu8);
  t->SetBranchAddress("is3SelMu8", &is3SelMu8);


  Int_t nentries = t->GetEntries();

  for(int k=0;k<nentries;k++){
    
    t->GetEntry(k);

    m_events++;


    if ( is4GenMu){
      m_events4GenMu++;
    }
    if ( is1GenMu17){
      m_events1GenMu17++;
      if ( is2GenMu8){
	m_events2GenMu8++;
      }
      if ( is3GenMu8){
	m_events3GenMu8++;
      }
      if ( is4GenMu8){
	m_events4GenMu8++;
      }
    }




    if (is1SelMu17){
      m_events1SelMu17++;
      if (is2SelMu8) m_events2SelMu8++;
      if (is3SelMu8) m_events3SelMu8++;
      if (is4SelMu8) m_events4SelMu8++;
    }

    if (is2MuJets) m_events2MuJets++;
    if (is2MuJets && is2DiMuons){
      m_events2DiMuons++;
    }
    if (is2MuJets && is2DiMuons && isDzDiMuonsOK) m_eventsDz2DiMuonsOK++;
    if (is2MuJets && is2DiMuons && isDzDiMuonsOK && isDiMuonsHLTFired) m_eventsDiMuonsHLTFired++;
    if (is2MuJets && is2DiMuons && isDzDiMuonsOK && isDiMuonsHLTFired && isMassDiMuonsOK) m_eventsMassDiMuonsOK++;
    if (is2MuJets && is2DiMuons && isDzDiMuonsOK && isDiMuonsHLTFired && isMassDiMuonsOK && isIsoDiMuonsOK) m_eventsIsoDiMuonsOK++;
    if (is2MuJets && is2DiMuons && isDzDiMuonsOK && isDiMuonsHLTFired && isMassDiMuonsOK && isIsoDiMuonsOK && isVertexOK) m_eventsVertexOK++;
  
    if (isOK_diMuonsLxy) m_eventsOK_diMuonsLxy++;



  }
  std:: cout << "Total number of events:          " << m_events << std::endl;
  std:: cout << "Total number of events with 4mu: " << m_events4GenMu << " fraction: " <<  m_events4GenMu/m_events << std::endl;
  
  std:: cout << "********** GEN **********" << std::endl;
  std:: cout << "Selection              " << "nEv"         << " \t RelEff"                                       << " \t Eff" << std::endl;
  std:: cout << "pT1>17 |eta1|<0.9:       " << m_events1GenMu17 << " \t" << (float)m_events1GenMu17/(float)m_events << " \t" << (float)m_events1GenMu17/(float)m_events << std::endl;
  std:: cout << "pT2>8  |eta2|<2.4:       " << m_events2GenMu8  << " \t" << (float)m_events2GenMu8/(float)m_events1GenMu17  << " \t" << (float)m_events2GenMu8/(float)m_events << std::endl;
  std:: cout << "pT3>8  |eta2|<2.4:       " << m_events3GenMu8  << " \t" << (float)m_events3GenMu8/(float)m_events2GenMu8   << " \t" << (float)m_events3GenMu8/(float)m_events << std::endl;
  std:: cout << "pT4>8  |eta2|<2.4:       " << m_events4GenMu8  << " \t" << (float)m_events4GenMu8/(float)m_events3GenMu8   << " \t" << (float)m_events4GenMu8/(float)m_events << std::endl;
  std:: cout << "Basic MC Acceptance:     " << (float)m_events4GenMu8/(float)m_events << std::endl;

  std:: cout << "********** RECO **********" << std::endl;
  std:: cout << "Selection                " << "nEv"                   << " \t RelEff"                                                         << " \t Eff" << std::endl;
  std:: cout << "m_events1SelMu17:        " << m_events1SelMu17        << " \t" << (float)m_events1SelMu17/(float)m_events                << " \t" << (float)m_events1SelMu17/(float)m_events        << std::endl;


  std:: cout << "m_events2SelMu8:         " << m_events2SelMu8         << " \t" << (float)m_events2SelMu8/(float)m_events1SelMu17              << " \t" << (float)m_events2SelMu8/(float)m_events         << std::endl;
  std:: cout << "m_events3SelMu8:         " << m_events3SelMu8         << " \t" << (float)m_events3SelMu8/(float)m_events2SelMu8               << " \t" << (float)m_events3SelMu8/(float)m_events         << std::endl;
  std:: cout << "m_events4SelMu8:         " << m_events4SelMu8         << " \t" << (float)m_events4SelMu8/(float)m_events3SelMu8               << " \t" << (float)m_events4SelMu8/(float)m_events         << std::endl;

  std:: cout << "Basic Acceptance:        " << (float)m_events4SelMu8/(float)m_events << std::endl;
  std:: cout << "Basic MC Accept. a_gen:  " << (float)m_events4GenMu8/(float)m_events << std::endl; 

  std:: cout << "m_events2MuJets:         " << m_events2MuJets         << " \t" << (float)m_events2MuJets/(float)m_events4SelMu8               << " \t" << (float)m_events2MuJets/(float)m_events         << std::endl;
  std:: cout << "m_events2DiMuons:        " << m_events2DiMuons        << " \t" << (float)m_events2DiMuons/(float)m_events2MuJets              << " \t" << (float)m_events2DiMuons/(float)m_events        << std::endl;
  std:: cout << "m_eventsDz2DiMuonsOK:     " << m_eventsDz2DiMuonsOK     << " \t" << (float)m_eventsDz2DiMuonsOK/(float)m_events2DiMuons          << " \t" << (float)m_eventsDz2DiMuonsOK/(float)m_events     << std::endl;
  std:: cout << "m_eventsDiMuonsHLTFired: " << m_eventsDiMuonsHLTFired << " \t" << (float)m_eventsDiMuonsHLTFired/(float)m_eventsDz2DiMuonsOK   << " \t" << (float)m_eventsDiMuonsHLTFired/(float)m_events << std::endl;
  std:: cout << "m_eventsMassDiMuonsOK:   " << m_eventsMassDiMuonsOK   << " \t" << (float)m_eventsMassDiMuonsOK/(float)m_eventsDiMuonsHLTFired << " \t" << (float)m_eventsMassDiMuonsOK/(float)m_events   << std::endl;
  std:: cout << "m_eventsIsoDiMuonsOK:    " << m_eventsIsoDiMuonsOK    << " \t" << (float)m_eventsIsoDiMuonsOK/(float)m_eventsMassDiMuonsOK    << " \t" << (float)m_eventsIsoDiMuonsOK/(float)m_events    << std::endl;
  std:: cout << "m_eventsVertexOK:        " << m_eventsVertexOK        << " \t" << (float)m_eventsVertexOK/(float)m_eventsIsoDiMuonsOK         << " \t" << (float)m_eventsVertexOK/(float)m_events        << std::endl;
  
  std:: cout << "Further selections:      " << (float)m_eventsVertexOK/(float)m_events4SelMu8 << std::endl;
  float e_full = (float)m_eventsVertexOK/(float)m_events;
  float de_full = sqrt( e_full*( 1.0 - e_full )/(float)m_events );
  std:: cout << "Full sel eff e_full:     " << e_full << " +- " << de_full << std::endl;
  std:: cout << "e_full/a_gen:            " << (float)m_eventsVertexOK/(float)m_events4GenMu8 << std::endl;



}










// double percPass = (double)mjcountvtx/(double)t->GetEntries();
// double percErr = TMath::Sqrt((1.-percPass)*(percPass)/(double)t->GetEntries());

// double percPassDz = (double)mjcountdz/(mjcount2mu*1.0);
// double percErrDz = TMath::Sqrt((1.-percPassDz)*(percPassDz)/(mjcount2mu*1.0));

// double percPassm = (double)mjcountm/(mjcounttrig*1.0);
// double percErrm = TMath::Sqrt((1.-percPassm)*(percPassm)/(mjcounttrig*1.0));
// cout << "-------------------------------" << endl;
// cout<<"  dz efficiency         "<<mjcountdz/(mjcount2mu*1.0)<< " +/- " << percErrDz << std::endl;
// cout<<"  mass efficiency         "<<mjcountm/(mjcounttrig*1.0)<< " +/- " << percErrm << std::endl;
// cout << "-------------------------------" << endl;

// cout<<"  Full efficiency         "<<mjcountvtx/(t->GetEntries()*1.0)<< " +/- " << percErr << std::endl;
// cout<<"  Full efficiency/gen       "<<( (rmcount[3]/(t->GetEntries()*1.0))*mjcountiso/(mjcount*1.0)) /(mcount[3]/(t->GetEntries()*1.0)) <<endl;
