{
  gROOT->SetBatch(true);
  
  TFile *f = new TFile("savehist_all.root");
  TFile *f1 = new TFile("savehist_SPS.root");
  TFile *f2 = new TFile("savehist_DPS.root");

  TH1F *data = (TH1F*)f->Get("diMuonC_Rapidity_RegionA");
  TH1F *mysignal = (TH1F*)f1->Get("diMuonC_Rapidity_RegionA");
  TH1F *mysignal2 = (TH1F*)f2->Get("diMuonC_Rapidity_RegionA");

  TH1F *mysignal_clone = (TH1F*)mysignal->Clone("mysignal_clone");
  TH1F *mysignal2_clone = (TH1F*)mysignal2->Clone("mysignal2_clone");
  
  cout << data->GetEntries() << endl;

  data->Scale(409.79/data->Integral());
  mysignal_clone->Scale(data->Integral()/mysignal_clone->Integral());
  mysignal2_clone->Scale(data->Integral()/mysignal2_clone->Integral());

  cout << data->Integral() << endl;
  // data_old->Scale(1/data_old->Integral());
  // data->Scale(1/data->Integral());

  // bkg_old->Scale(1/bkg_old->Integral());
  // bkg->Scale(1/bkg->Integral());

  TLegend *leg = new TLegend(0.50,0.75,0.90,0.90);
  leg->AddEntry(data,"Data","PL");
  leg->AddEntry(mysignal_clone,"MC SPS","L");
  leg->AddEntry(mysignal2_clone,"MC DPS","L");

  TText *t = new TText(0.15,0.8,"CMS");
  t->SetNDC();
  
  TLatex* t1 = new TLatex();;
  t1->SetTextSize(0.035);
  t1->SetNDC();

  TCanvas *c2 = new TCanvas("c2","c2",800,800);
  c2->SetFillColor(0);
  c2->SetBorderMode(0);
  c2->SetBorderSize(2);
  c2->SetTickx(1);
  c2->SetTicky(1);
  c2->SetLeftMargin(0.10);
  c2->SetRightMargin(0.05);
  c2->SetTopMargin(0.07);
  c2->SetBottomMargin(0.1);
  c2->SetFrameFillStyle(0);
  c2->SetFrameBorderMode(0);
  c2->SetFrameFillStyle(0);
  c2->SetFrameBorderMode(0);

  gStyle->SetTitleFontSize(0.07);

  gStyle->SetTitleStyle( 0 );
  gStyle->SetTitleAlign(13);
  gStyle->SetTitleX(0.);
  gStyle->SetTitleY(1.);
  gStyle->SetTitleW(1);
  gStyle->SetTitleH(0.058);
  gStyle->SetTitleBorderSize( 0 );

  data->SetLineColor(1);
  data->SetMarkerStyle(20);

   data->GetXaxis()->SetLabelFont(42);
  data->GetXaxis()->SetLabelOffset(0.007);
  data->GetXaxis()->SetLabelSize(0.05);
  data->GetXaxis()->SetTitleSize(0.06);
  data->GetXaxis()->SetTitleFont(42);
  data->GetYaxis()->SetLabelFont(42);
  data->GetYaxis()->SetLabelOffset(0.007);
  data->GetYaxis()->SetLabelSize(0.05);
  data->GetYaxis()->SetTitleSize(0.06);
  data->GetYaxis()->SetTitleOffset(1.1);
  data->GetYaxis()->SetTitleFont(42);


  data->Draw("PE");
  mysignal_clone->SetLineColor(2);
  mysignal2_clone->SetLineColor(4);
  mysignal_clone->SetLineWidth(2);
  mysignal2_clone->SetLineWidth(2);
  mysignal_clone->Draw("same");
  mysignal2_clone->Draw("same");
  leg->Draw("same");
  t->Draw("same");
  t1->DrawLatex(0.67,0.92,"35.9 fb^{-1} (13 TeV)");

  c2->SaveAs("rapidity_dist.C","recreate");
  c2->SaveAs("rapidity_dist.pdf","recreate");
  //  c2->SaveAs("rapidity_dist.png","recreate");
  

  TObjArray *mc = new TObjArray(3);        // MC histograms are put in this array
  mc->Add(mysignal);
  mc->Add(mysignal2);
  TFractionFitter* fit = new TFractionFitter(data, mc); // initialise
  fit->Constrain(1,0.0,1.0);               // constrain fraction 1 to be between 0 and 1
  fit->SetRangeX(1,80);                    // use only the first 15 bins in the fit
  Int_t status = fit->Fit();               // perform the fit
  cout << "fit status: " << status << endl;

  TLegend *leg9 = new TLegend(0.65,0.75,0.92,0.90);
  leg9->SetFillColor(kWhite);
  leg9->SetFillStyle(0);
  leg9->SetBorderSize(0);
  leg9->SetTextFont(42);
  leg9->SetTextSize(0.035);
  leg9->SetMargin(0.13);
  leg9->AddEntry(data,"Data","PL");
  
  if (status == 0) {                       // check on fit status
    TH1F* result = (TH1F*) fit->GetPlot();
    leg9->AddEntry(result,"Simultaneous fit ","FL");
    data->GetXaxis()->SetTitle("di-#mu_{1} Rapidity");
    data->GetYaxis()->SetTitle("Events");
    
    txtHeader = new TLegend(.8,8,0.92,0.9);
    
    txtHeader->SetFillColor(kWhite);
    txtHeader->SetFillStyle(0);
    txtHeader->SetBorderSize(0);
    txtHeader->SetTextFont(24);
    txtHeader->SetTextSize(0.045);
    txtHeader->SetTextAlign(22);
    txtHeader->SetHeader("CMS    35.9 fb^{-1} (13 TeV)");

    //    TText *t1 = new TText(2.0,32.0,"35.7 fb^{-1} (13 TeV)");
    //    t->SetTextAlign(22);
    //    t->SetTextColor(Black);
    //    t->SetTextFont(26);
    //    t->SetTextSize(24);
    // t->SetTextAngle(45);

    TCanvas *c = new TCanvas("c","c",800,800);
    c->SetFillColor(0);
    c->SetBorderMode(0);
    c->SetBorderSize(2);
    c->SetTickx(1);
    c->SetTicky(1);
    c->SetLeftMargin(0.10);
    c->SetRightMargin(0.05);
    c->SetTopMargin(0.07);
    c->SetBottomMargin(0.1);
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
    gStyle->SetTitleBorderSize( 0 );    //    c->SetCanvasSize(1000,900);
    //    c->SetLeftMargin(0.126);
    //    c->SetRightMargin(0.154);
    //    c->cd();

    result->GetXaxis()->SetTitle("di-#mu_{1} Rapidity");
    result->GetYaxis()->SetTitle("Events");
    result->SetMaximum(30);
    data->Draw("Ep");
    result->Draw("same");

    //    TPaveStats st = (TPaveStats*)result->FindObject("stats");
    //    st->SetOptFit(1);
    //    st.SetX1NDC(0.7);
    //    st->SetX2NDC(0.99);
    //    st->SetY1NDC(0.2);
    //    st->SetY2NDC(0.5);


    //    mc0_norm->Draw("same");
    //    mc1_norm->Draw("same");
    //    leg9->Draw("same");
    //    t->Draw("same");
    t1->DrawLatex(0.67,0.92,"35.9 fb^{-1} (13 TeV)");

    //    c->Update();
    //    TPaveStats *stat = (TPaveStats*)(data->FindObject("stats"));
    //    stat->Draw("same");
    
    //    c->SaveAs("rapidityfit.eps","recreate");
    c->SaveAs("rapidityfit.pdf","recreate");
    c->SaveAs("rapidityfit.C","recreate");
  }
}
