{
 
  TFile *f = new TFile("savehist_all.root");
  TFile *f = new TFile("savehist_all.root");
  TFile *f1 = new TFile("savehist_SPS.root");
  TFile *f2 = new TFile("forfitlxy.root");

  TH1F *data = (TH1F*)f->Get("diMuonC_Lxy_RegionA");
  //  TH1F *data_old = (TH1F*)f2->Get("hlxy_data");
  TH1F *signal = (TH1F*)f1->Get("diMuonC_Lxy_RegionA");
  //  TH1F *signal = (TH1F*)f2->Get("hlxy_mc");
  TH1F *bkg = (TH1F*)f->Get("diMuonC_Lxy_RegionC");
  //  TH1F *bkg_old = (TH1F*)f2->Get("hlxy_bkgtemp");

  TH1F *data_clone = (TH1F*)data->Clone("data_clone");
  TH1F *signal_clone = (TH1F*)signal->Clone("signal_clone");
  TH1F *bkg_clone = (TH1F*)bkg->Clone("bkg_clone");

  data_clone->Scale(1/data_clone->Integral());
  bkg_clone->Scale(1/bkg_clone->Integral());
  signal_clone->Scale(1/signal_clone->Integral());
  
  // data_old->Scale(1/data_old->Integral());
  // data->Scale(1/data->Integral());

  // bkg_old->Scale(1/bkg_old->Integral());
  // bkg->Scale(1/bkg->Integral());

  TLegend *leg = new TLegend(0.40,0.6,0.80,0.75);
  leg->AddEntry(signal_clone,"MC SPS","L");
  leg->AddEntry(bkg_clone,"DATA (non-isolated region)","L");
  leg->AddEntry(data_clone,"DATA (isolated region)","L");
 

  
 TCanvas *c1 = new TCanvas("c1","c1",800,600);
  signal_clone->SetLineColor(4);
  signal_clone->SetLineStyle(2);
  signal_clone->GetXaxis()->SetTitle("Lxy dimuon1 [mm]");
  signal_clone->Draw();
  data_clone->Draw("same");
  bkg_clone->SetLineColor(2);
  bkg_clone->Draw("same");
  leg->Draw("same");


  
  // data_old->SetLineColor(2);
  // data_old->GetXaxis()->SetTitle("Lxy [mm]");
  // data_old->GetYaxis()->SetTitle("normalized to 1");
  // data_old->Draw("");
  // data->Draw("same");
  // leg->Draw("same");


  // TCanvas *c2 = new TCanvas("c2","c2",800,600);
  // bkg_old->SetLineColor(2);
  // bkg->GetXaxis()->SetTitle("Lxy [mm]");
  // bkg->GetYaxis()->SetTitle("normalized to 1");
  // bkg->Draw();
  // bkg_old->Draw("same");
  // leg->Draw("same");
  
  
  
  // Float_t evdata = data->Integral();

  // data_clone->Scale(1/data_clone->Integral());
  // signal_clone->Scale(1/signal_clone->Integral());
  // bkg_clone->Scale(1/bkg_clone->Integral());
  
  // TCanvas *cc = new TCanvas("cc","cc",800,600);
  // signal_clone->SetLineColor(2);
  // bkg_clone->SetLineColor(4);
  // signal_clone->Draw();
  // data_clone->Draw("same");
  // bkg_clone->Draw("same");


  TObjArray *mc = new TObjArray(3);        // MC histograms are put in this array
  mc->Add(signal);
  mc->Add(bkg);
  TFractionFitter* fit = new TFractionFitter(data, mc); // initialise
  fit->Constrain(1,0.0,1.0);               // constrain fraction 1 to be between 0 and 1
  fit->SetRangeX(8,50);                    // use only the first 15 bins in the fit
  Int_t status = fit->Fit();               // perform the fit
  cout << "fit status: " << status << endl;

  TLegend *leg9 = new TLegend(0.40,0.6,0.80,0.75);
  leg9->SetFillColor(kWhite);
  leg9->SetFillStyle(0);
  leg9->SetBorderSize(0);
  leg9->SetTextFont(42);
  leg9->SetTextSize(0.035);
  leg9->SetMargin(0.13);
  leg9->AddEntry(data,"Data","PL");


  // TH1F *mc0_norm = (TH1F*)signal->Clone("mc0_norm");
  // TH1F *mc1_norm = (TH1F*)bkg->Clone("mc1_norm");

  // mc0_norm->Scale( (0.37*evdata)/mc0_norm->Integral());
  // mc1_norm->Scale( (0.63*evdata)/mc1_norm->Integral());
  
  // mc0_norm->SetLineColor(3);
  // mc1_norm->SetLineColor(4);

  if (status == 0) {                       // check on fit status
    TH1F* result = (TH1F*) fit->GetPlot();
    leg9->AddEntry(result,"Simultaneous fit ","FL");
    data->GetXaxis()->SetTitle("di-#mu_{2} lxy [mm]");
    data->GetYaxis()->SetTitle("Events");

    txtHeader = new TLegend(.93,.935,.1.47,1.);

  txtHeader->SetFillColor(kWhite);
  txtHeader->SetFillStyle(0);
  txtHeader->SetBorderSize(0);
  txtHeader->SetTextFont(42);
  txtHeader->SetTextSize(0.045);
  txtHeader->SetTextAlign(22);
  txtHeader->SetHeader("CMS 2012  #sqrt{s} = 8 TeV  L_{int} = 20.65 fb^{-1}");




  TCanvas *c = new TCanvas("c","c",800,600);
  //  c->SetCanvasSize(1000,900);
  c->SetLeftMargin(0.126);
  c->SetRightMargin(0.154);
  c->cd();

  result->GetXaxis()->SetTitle("Lxy dimuon1 [mm]");
  result->Draw();
  data->Draw("Epsame");
  //    mc0_norm->Draw("same");
  //    mc1_norm->Draw("same");
  leg9->Draw("same");
  //    txtHeader->Draw("same");
  
  c->SaveAs("lxyfit.eps","recreate");
  c->SaveAs("lxyfit.pdf","recreate");
  }
}
