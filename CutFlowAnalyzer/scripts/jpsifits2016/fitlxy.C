{
  TString histTitle = "       #scale[1.4]{#font[61]{CMS}}                          35.9 fb^{-1} (13 TeV)  ";

  TFile *f = new TFile("savehist_all.root");
  TFile *f1 = new TFile("savehist_SPS.root");
  TFile *f2 = new TFile("forfitlxy.root");

  TH1F *data = (TH1F*)f->Get("diMuonC_Lxy_RegionA");
  //  TH1F *data_old = (TH1F*)f2->Get("hlxy_data");
  TH1F *mysignal = (TH1F*)f1->Get("diMuonC_Lxy_RegionA");
  //  TH1F *mysignal = (TH1F*)f2->Get("hlxy_mc");
  TH1F *bkg = (TH1F*)f->Get("diMuonC_Lxy_RegionC");
  //  TH1F *bkg_old = (TH1F*)f2->Get("hlxy_bkgtemp");

  TH1F *data_clone = (TH1F*)data->Clone("data_clone");
  TH1F *mysignal_clone = (TH1F*)mysignal->Clone("mysignal_clone");
  TH1F *bkg_clone = (TH1F*)bkg->Clone("bkg_clone");

  data_clone->Scale(1/data_clone->Integral());
  bkg_clone->Scale(1/bkg_clone->Integral());
  mysignal_clone->Scale(1/mysignal_clone->Integral());
  
  // data_old->Scale(1/data_old->Integral());
  // data->Scale(1/data->Integral());

  // bkg_old->Scale(1/bkg_old->Integral());
  // bkg->Scale(1/bkg->Integral());

  TLegend *leg = new TLegend(0.30,0.6,0.85,0.75);
  leg->SetFillColor(kWhite);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.05);
  leg->SetMargin(0.13);
  leg->AddEntry(mysignal_clone,"MC SPS","L");
  leg->AddEntry(bkg_clone,"Data (non-isolated region)","L");
  leg->AddEntry(data_clone,"Data (isolated region)","L");
 
  TCanvas *c1 = new TCanvas("c1","c1",600,600);
  c1->SetLeftMargin(0.126);
  c1->SetRightMargin(0.154);
  c1->cd();
  c1->SetFillColor(0);
  c1->SetBorderMode(0);
  c1->SetBorderSize(2);
  c1->SetTickx(1);
  c1->SetTicky(1);
  c1->SetLeftMargin(0.15);
  c1->SetRightMargin(0.05);
  c1->SetTopMargin(0.07);
  c1->SetBottomMargin(0.17);
  c1->SetFrameFillStyle(0);
  c1->SetFrameBorderMode(0);
  c1->SetFrameFillStyle(0);
  c1->SetFrameBorderMode(0);
  
  gStyle->SetOptStat(0);
  gStyle->SetTitleFontSize(0.07);
  
  gStyle->SetTitleStyle( 0 );
  gStyle->SetTitleAlign(13);
  gStyle->SetTitleX(0.);
  gStyle->SetTitleY(1.);
  gStyle->SetTitleW(1);
  gStyle->SetTitleH(0.058);
  gStyle->SetTitleBorderSize( 0 );
  
  mysignal_clone->SetLineColor(4);
  mysignal_clone->SetLineStyle(2);
  mysignal_clone->GetXaxis()->SetTitle("Lxy_{(#mu#mu)_{1}} [mm]");
  mysignal_clone->GetYaxis()->SetTitle("Normalized");
  mysignal_clone->SetTitle(histTitle);

   mysignal_clone->GetXaxis()->SetLabelFont(42);
   mysignal_clone->GetXaxis()->SetLabelOffset(0.007);
   mysignal_clone->GetXaxis()->SetLabelSize(0.05);
   mysignal_clone->GetXaxis()->SetTitleSize(0.06);
   mysignal_clone->GetXaxis()->SetTitleFont(42);
   mysignal_clone->GetXaxis()->SetTitleOffset(1.1);

   mysignal_clone->GetYaxis()->SetLabelFont(42);
   mysignal_clone->GetYaxis()->SetLabelOffset(0.007);
   mysignal_clone->GetYaxis()->SetLabelSize(0.05);
   mysignal_clone->GetYaxis()->SetTitleSize(0.06);
   mysignal_clone->GetYaxis()->SetTitleOffset(1.1);
   mysignal_clone->GetYaxis()->SetTitleFont(42);
   
   
   mysignal_clone->SetLineWidth(2);
   data_clone->SetLineWidth(2);
   bkg_clone->SetLineWidth(2);
   bkg_clone->SetLineStyle(5);

   data_clone->SetLineStyle(1);
   
   mysignal_clone->Draw();
   data_clone->Draw("same");
   bkg_clone->SetLineColor(2);
   bkg_clone->Draw("same");
   leg->Draw("same");
   
   c1->SaveAs("lxy_sps_dps_data.C","recreate");
   c1->SaveAs("lxy_sps_dps_data.pdf","recreate");
   
  
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
  // mysignal_clone->Scale(1/mysignal_clone->Integral());
  // bkg_clone->Scale(1/bkg_clone->Integral());
  
  // TCanvas *cc = new TCanvas("cc","cc",800,600);
  // mysignal_clone->SetLineColor(2);
  // bkg_clone->SetLineColor(4);
  // mysignal_clone->Draw();
  // data_clone->Draw("same");
  // bkg_clone->Draw("same");


  TObjArray *mc = new TObjArray(3);        // MC histograms are put in this array
  mc->Add(mysignal);
  mc->Add(bkg);
  TFractionFitter* fit = new TFractionFitter(data, mc); // initialise
  fit->Constrain(1,0.0,1.0);               // constrain fraction 1 to be between 0 and 1
  fit->SetRangeX(8,50);                    // use only the first 15 bins in the fit
  Int_t status = fit->Fit();               // perform the fit
  cout << "fit status: " << status << " chi2/ndf " << fit->GetChisquare()/fit->GetNDF() << endl;

  TLegend *leg9 = new TLegend(0.40,0.6,0.80,0.75);
  leg9->SetFillColor(kWhite);
  leg9->SetFillStyle(0);
  leg9->SetBorderSize(0);
  leg9->SetTextFont(42);
  leg9->SetTextSize(0.05);
  leg9->SetMargin(0.13);
  leg9->AddEntry(data,"Data","PL");


  // TH1F *mc0_norm = (TH1F*)mysignal->Clone("mc0_norm");
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
    
    //   txtHeader = new TLegend(.93,.935,1.47,1.);
    
    // txtHeader->SetFillColor(kWhite);
    // txtHeader->SetFillStyle(0);
    // txtHeader->SetBorderSize(0);
    // txtHeader->SetTextFont(42);
    // txtHeader->SetTextSize(0.045);
    // txtHeader->SetTextAlign(22);
    // txtHeader->SetHeader("CMS 2012  #sqrt{s} = 8 TeV  L_{int} = 20.65 fb^{-1}");
     
    TCanvas *c = new TCanvas("c","c",600,600);
    //  c->SetCanvasSize(1000,900);
    c->SetLeftMargin(0.126);
    c->SetRightMargin(0.154);
    c->cd();
    c->SetFillColor(0);
    c->SetBorderMode(0);
    c->SetBorderSize(2);
    c->SetTickx(1);
    c->SetTicky(1);
    c->SetLeftMargin(0.15);
    c->SetRightMargin(0.05);
    c->SetTopMargin(0.07);
    c->SetBottomMargin(0.17);
    c->SetFrameFillStyle(0);
    c->SetFrameBorderMode(0);
    c->SetFrameFillStyle(0);
    c->SetFrameBorderMode(0);
    
    gStyle->SetTitleFontSize(0.07);
    
    gStyle->SetTitleStyle( 0 );
    gStyle->SetTitleAlign(13);
    gStyle->SetTitleX(0.);
    gStyle->SetTitleY(1.);
    gStyle->SetTitleW(1);
    gStyle->SetTitleH(0.058);
    gStyle->SetTitleBorderSize( 0 );
    
   result->GetXaxis()->SetLabelFont(42);
   result->GetXaxis()->SetLabelOffset(0.007);
   result->GetXaxis()->SetLabelSize(0.05);
   result->GetXaxis()->SetTitleSize(0.06);
   result->GetXaxis()->SetTitleFont(42);
   result->GetYaxis()->SetLabelFont(42);
   result->GetYaxis()->SetLabelOffset(0.007);
   result->GetYaxis()->SetLabelSize(0.05);
   result->GetYaxis()->SetTitleSize(0.06);
   result->GetYaxis()->SetTitleOffset(1.1);
   result->GetYaxis()->SetTitleFont(42);
    
    result->GetXaxis()->SetTitle("Lxy_{(#mu#mu)_{1}} [mm]");
    result->GetYaxis()->SetTitle("Entries");
    result->SetTitle(histTitle);
   result->SetLineWidth(2);
    result->Draw();



    data->Draw("Epsame");
    //    mc0_norm->Draw("same");
    //    mc1_norm->Draw("same");
    leg9->Draw("same");
    //    txtHeader->Draw("same");
    
    c->SaveAs("lxyfit.C","recreate");
    c->SaveAs("lxyfit.eps","recreate");
    c->SaveAs("lxyfit.pdf","recreate");

    gPad->SetLogy(1);

    c->SaveAs("lxyfit_logy.C","recreate");
    c->SaveAs("lxyfit_logy.eps","recreate");
    c->SaveAs("lxyfit_logy.pdf","recreate");

    gPad->SetLogy(0);

    TCanvas *cratio = new TCanvas("c","c",600,600);
    //  cratio->SetCanvasSize(1000,900);
    cratio->SetLeftMargin(0.126);
    cratio->SetRightMargin(0.154);
    cratio->cd();
    cratio->SetFillColor(0);
    cratio->SetBorderMode(0);
    cratio->SetBorderSize(2);
    cratio->SetTickx(1);
    cratio->SetTicky(1);
    cratio->SetLeftMargin(0.15);
    cratio->SetRightMargin(0.05);
    cratio->SetTopMargin(0.07);
    cratio->SetBottomMargin(0.17);
    cratio->SetFrameFillStyle(0);
    cratio->SetFrameBorderMode(0);
    cratio->SetFrameFillStyle(0);
    cratio->SetFrameBorderMode(0);
    
    gStyle->SetTitleFontSize(0.07);
    
    gStyle->SetTitleStyle( 0 );
    gStyle->SetTitleAlign(13);
    gStyle->SetTitleX(0.);
    gStyle->SetTitleY(1.);
    gStyle->SetTitleW(1);
    gStyle->SetTitleH(0.058);
    gStyle->SetTitleBorderSize( 0 );
    
    TH1F *result2 = (TH1F*)result->Clone("result2");
    result2->Sumw2();
    result2->Divide(data);

    result2->GetXaxis()->SetLabelFont(42);
    result2->GetXaxis()->SetLabelOffset(0.007);
    result2->GetXaxis()->SetLabelSize(0.05);
    result2->GetXaxis()->SetTitleSize(0.06);
    result2->GetXaxis()->SetTitleFont(42);
    result2->GetYaxis()->SetLabelFont(42);
    result2->GetYaxis()->SetLabelOffset(0.007);
    result2->GetYaxis()->SetLabelSize(0.05);
    result2->GetYaxis()->SetTitleSize(0.06);
    result2->GetYaxis()->SetTitleOffset(1.1);
    result2->GetYaxis()->SetTitleFont(42);
    
    result2->GetXaxis()->SetTitle("Lxy_{(#mu#mu)_{1}} [mm]");
    result2->GetYaxis()->SetTitle("Fit/Data");
    result2->SetTitle(histTitle);
    result2->SetLineWidth(2);
    result2->Draw("P");
    
    cratio->SaveAs("lxyfit_ratio.C","recreate");
    cratio->SaveAs("lxyfit_ratio.eps","recreate");
    cratio->SaveAs("lxyfit_ratio.pdf","recreate");

  }
}
