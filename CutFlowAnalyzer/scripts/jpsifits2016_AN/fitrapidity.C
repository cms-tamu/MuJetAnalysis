void fitrapidity()
{
  gROOT->SetBatch(true);
  gStyle->SetOptStat(0);

  TString histTitle = "       #scale[1.4]{#font[61]{CMS}}                          35.9 fb^{-1} (13 TeV)  ";

  TFile *f = new TFile("../forJpsi/plots_SPS_DPS_SD20180512/Histograms2016Charmonium_All.root");
  TFile *f1 = new TFile("../forJpsi/plots_SPS_DPS_SD20180512/HistogramsSPS.root");
  TFile *f2 = new TFile("../forJpsi/plots_SPS_DPS_SD20180512/HistogramsDPS.root");

  // unscaled ones
  TH1F *data = (TH1F*)f->Get("diMuon_DeltaRapidity_RegionA");
  TH1F *signal_SPS = (TH1F*)f1->Get("diMuon_DeltaRapidity_RegionA");
  TH1F *signal_DPS = (TH1F*)f2->Get("diMuon_DeltaRapidity_RegionA");

  // common stuff
  data->SetMarkerStyle(1);
  data->SetMarkerSize(1);
  data->SetMarkerColor(kBlack);
  data->SetLineColor(kBlack);

  data->GetXaxis()->SetTitle("|Y_{(#mu#mu)_{1}} - Y_{(#mu#mu)_{2}}|");
  data->GetYaxis()->SetTitle("Events");
  data->SetTitle(histTitle);

  signal_SPS->SetTitle(histTitle);
  signal_DPS->SetTitle(histTitle);

  signal_SPS->SetLineColor(2);
  signal_DPS->SetLineColor(4);
  signal_SPS->SetLineWidth(2);
  signal_DPS->SetLineWidth(2);

  data->Sumw2();
  signal_SPS->Sumw2();
  signal_DPS->Sumw2();

  // scaled ones
  TH1F *data_clone = (TH1F*)data->Clone("data_clone");
  TH1F *signal_SPS_clone = (TH1F*)signal_SPS->Clone("signal_SPS_clone");
  TH1F *signal_DPS_clone = (TH1F*)signal_DPS->Clone("signal_DPS_clone");
  
  cout << data->GetEntries() << endl;

  // data->Scale(409.79/data->Integral());
  // signal_SPS->Scale(data->Integral()/signal_SPS->Integral());
  // signal_DPS->Scale(data->Integral()/signal_DPS->Integral());

  // scale histograms
  data_clone->Scale(409.79/data_clone->Integral());
  signal_SPS_clone->Scale(data_clone->Integral()/signal_SPS_clone->Integral());
  signal_DPS_clone->Scale(data_clone->Integral()/signal_DPS_clone->Integral());
  
  TCanvas *c2 = new TCanvas("c2","c2",600,600);
  c2->SetFillColor(0);
  c2->SetBorderMode(0);
  c2->SetBorderSize(2);
  c2->SetTickx(1);
  c2->SetTicky(1);
  c2->SetLeftMargin(0.15);
  c2->SetRightMargin(0.05);
  c2->SetTopMargin(0.07);
  c2->SetBottomMargin(0.15);
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

  data_clone->SetMaximum(data_clone->GetMaximum()*1.5);
  data_clone->SetMinimum(0);
  data_clone->SetLineColor(1);
  data_clone->SetMarkerStyle(20);
  
  data_clone->GetXaxis()->SetLabelFont(42);
  data_clone->GetXaxis()->SetLabelOffset(0.007);
  data_clone->GetXaxis()->SetLabelSize(0.05);
  data_clone->GetXaxis()->SetTitleSize(0.06);
  data_clone->GetXaxis()->SetTitleFont(42);
  data_clone->GetXaxis()->SetTitleOffset(1.1);
  
  data_clone->GetYaxis()->SetLabelFont(42);
  data_clone->GetYaxis()->SetLabelOffset(0.007);
  data_clone->GetYaxis()->SetLabelSize(0.05);
  data_clone->GetYaxis()->SetTitleSize(0.06);
  data_clone->GetYaxis()->SetTitleOffset(1.1);
  data_clone->GetYaxis()->SetTitleFont(42);

  TLegend *leg = new TLegend(0.6,0.75,0.90,0.90);
  leg->SetFillColor(kWhite);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.05);
  leg->SetMargin(0.13);
  leg->AddEntry(data_clone,"Data","P");
  leg->AddEntry(signal_SPS_clone,"MC SPS","L");
  leg->AddEntry(signal_DPS_clone,"MC DPS","L");

  data_clone->Draw("PE");
  signal_SPS_clone->Draw("hist same");
  signal_DPS_clone->Draw("hist same");
  leg->Draw("same");

  c2->SaveAs("rapidity_dist.C","recreate");
  c2->SaveAs("rapidity_dist.pdf","recreate");
  
  TObjArray *mc = new TObjArray(3);        // MC histograms are put in this array
  mc->Add(signal_SPS);
  mc->Add(signal_DPS);

  TFractionFitter* fit = new TFractionFitter(data, mc); // initialise
  fit->Constrain(1,0.0,1.0);               // constrain fraction 1 to be between 0 and 1
  fit->SetRangeX(1,80);                    // use only the first 80 bins in the fit

  Int_t status = fit->Fit();               // perform the fit
  cout << "fit status: " << status << " chi2/ndf " << fit->GetChisquare()/fit->GetNDF() << endl;

  if (status == 0) {                       // check on fit status
    TH1F* result = (TH1F*) fit->GetPlot();

    TCanvas *c = new TCanvas("c","c",600,600);
    c->SetFillColor(0);
    c->SetBorderMode(0);
    c->SetBorderSize(2);
    c->SetTickx(1);
    c->SetTicky(1);
    c->SetLeftMargin(0.15);
    c->SetRightMargin(0.05);
    c->SetTopMargin(0.07);
    c->SetBottomMargin(0.15);
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
    
    data->SetMaximum(100);
    data->SetLineColor(1);
    data->SetMarkerStyle(20);
    
    data->GetXaxis()->SetLabelFont(42);
    data->GetXaxis()->SetLabelOffset(0.007);
    data->GetXaxis()->SetLabelSize(0.05);
    data->GetXaxis()->SetTitleSize(0.06);
    data->GetXaxis()->SetTitleFont(42);
    data->GetXaxis()->SetTitleOffset(1.1);
    
    data->GetYaxis()->SetLabelFont(42);
    data->GetYaxis()->SetLabelOffset(0.007);
    data->GetYaxis()->SetLabelSize(0.05);
    data->GetYaxis()->SetTitleSize(0.06);
    data->GetYaxis()->SetTitleOffset(1.1);
    data->GetYaxis()->SetTitleFont(42);
    
    TLegend *leg9 = new TLegend(0.50,0.75,0.90,0.90);
    leg9->SetFillColor(kWhite);
    leg9->SetFillStyle(0);
    leg9->SetBorderSize(0);
    leg9->SetTextFont(42);
    leg9->SetTextSize(0.05);
    leg9->SetMargin(0.13);
    leg9->AddEntry(data,"Data","P");
    leg9->AddEntry(result,"Simultaneous fit ","L");

    result->GetXaxis()->SetTitle("|Y_{(#mu#mu)_{1}} - Y_{(#mu#mu)_{2}}|");
    result->GetYaxis()->SetTitle("Events");
    // result->SetMaximum(30);
    data_clone->Draw("Ep");
    result->Draw("same");
    result->Scale(data_clone->Integral()/result->Integral());
    leg9->Draw("same");

    c->SaveAs("rapidityfit.pdf","recreate");
    c->SaveAs("rapidityfit.C","recreate");


    TH1F *result2 = (TH1F*)result->Clone("result2");
    result2->Sumw2();
    result2->Divide(data_clone);

    // result->Scale(data_clone->Integral()/result->Integral());

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
    
    result2->GetXaxis()->SetTitle("|Y_{(#mu#mu)_{1}} - Y_{(#mu#mu)_{2}}|");
    result2->GetYaxis()->SetTitle("Fit/Data");
    result2->SetTitle(histTitle);
    result2->SetMarkerColor(kBlack);
    result2->SetMarkerStyle(20);
    result2->SetMarkerSize(1);
    //    data_clone->SetMarkerStyle(20);
    result2->GetYaxis()->SetRangeUser(0,2);
    result2->Draw("P");
    
    TLegend *leg10 = new TLegend(0.20,0.15,0.60,0.4);
    leg10->SetFillColor(kWhite);
    leg10->SetFillStyle(0);
    leg10->SetBorderSize(0);
    leg10->SetTextFont(42);
    leg10->SetTextSize(0.05);
    leg10->SetMargin(0.13);
    leg10->AddEntry(data,"Data","P");
    leg10->AddEntry(result,"Simultaneous fit ","L");
    leg10->Draw("same");
    c->SaveAs("rapidityfit_ratio.C","recreate");
    c->SaveAs("rapidityfit_ratio.pdf","recreate");
  }
}
