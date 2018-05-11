void DarkSusy_mH_125_mGammaD_0400_cT_100_LHE_gammaD_L()
{
//=========Macro generated from canvas: cnv/cnv
//=========  (Sun May  6 01:34:46 2018) by ROOT version6.06/01
   TCanvas *cnv = new TCanvas("cnv", "cnv",1,1,904,904);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   cnv->SetHighLightColor(2);
   cnv->Range(-21.25,-0.006040899,103.75,0.04042755);
   cnv->SetFillColor(0);
   cnv->SetBorderMode(0);
   cnv->SetBorderSize(2);
   cnv->SetTickx(1);
   cnv->SetTicky(1);
   cnv->SetLeftMargin(0.17);
   cnv->SetRightMargin(0.03);
   cnv->SetTopMargin(0.07);
   cnv->SetBottomMargin(0.13);
   cnv->SetFrameFillStyle(0);
   cnv->SetFrameBorderMode(0);
   cnv->SetFrameFillStyle(0);
   cnv->SetFrameBorderMode(0);
   
   TH1F *h_gammaD_cT_lab_dummy__53 = new TH1F("h_gammaD_cT_lab_dummy__53","h_gammaD_cT_lab_dummy",5,0,100);
   h_gammaD_cT_lab_dummy__53->SetMaximum(0.03717476);
   h_gammaD_cT_lab_dummy__53->SetLineStyle(0);
   h_gammaD_cT_lab_dummy__53->SetMarkerStyle(20);
   h_gammaD_cT_lab_dummy__53->GetXaxis()->SetTitle("L of #gamma_{D} [mm]");
   h_gammaD_cT_lab_dummy__53->GetXaxis()->SetLabelFont(42);
   h_gammaD_cT_lab_dummy__53->GetXaxis()->SetLabelOffset(0.007);
   h_gammaD_cT_lab_dummy__53->GetXaxis()->SetTitleSize(0.06);
   h_gammaD_cT_lab_dummy__53->GetXaxis()->SetTitleOffset(0.95);
   h_gammaD_cT_lab_dummy__53->GetXaxis()->SetTitleFont(42);
   h_gammaD_cT_lab_dummy__53->GetYaxis()->SetTitle("Normalized Fraction of Events / 1.0 mm");
   h_gammaD_cT_lab_dummy__53->GetYaxis()->SetLabelFont(42);
   h_gammaD_cT_lab_dummy__53->GetYaxis()->SetLabelOffset(0.007);
   h_gammaD_cT_lab_dummy__53->GetYaxis()->SetTitleSize(0.05);
   h_gammaD_cT_lab_dummy__53->GetYaxis()->SetTitleOffset(1.3);
   h_gammaD_cT_lab_dummy__53->GetYaxis()->SetTitleFont(42);
   h_gammaD_cT_lab_dummy__53->GetZaxis()->SetLabelFont(42);
   h_gammaD_cT_lab_dummy__53->GetZaxis()->SetLabelOffset(0.007);
   h_gammaD_cT_lab_dummy__53->GetZaxis()->SetTitleSize(0.06);
   h_gammaD_cT_lab_dummy__53->GetZaxis()->SetTitleFont(42);
   h_gammaD_cT_lab_dummy__53->Draw("");
   
   TH1F *h_gammaD_cT_lab__54 = new TH1F("h_gammaD_cT_lab__54","h_gammaD_cT_lab",5,0,100);
   h_gammaD_cT_lab__54->SetBinContent(1,0.02065265);
   h_gammaD_cT_lab__54->SetBinContent(2,0.01117415);
   h_gammaD_cT_lab__54->SetBinContent(3,0.007715105);
   h_gammaD_cT_lab__54->SetBinContent(4,0.005799824);
   h_gammaD_cT_lab__54->SetBinContent(5,0.004658277);
   h_gammaD_cT_lab__54->SetBinContent(6,0.03467564);
   h_gammaD_cT_lab__54->SetEntries(159998);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#0000ff");
   h_gammaD_cT_lab__54->SetLineColor(ci);
   h_gammaD_cT_lab__54->SetLineWidth(2);
   h_gammaD_cT_lab__54->SetMarkerStyle(20);
   h_gammaD_cT_lab__54->GetXaxis()->SetTitle("L of #gamma_{D} [mm]");
   h_gammaD_cT_lab__54->GetXaxis()->SetLabelFont(42);
   h_gammaD_cT_lab__54->GetXaxis()->SetLabelOffset(0.007);
   h_gammaD_cT_lab__54->GetXaxis()->SetTitleSize(0.06);
   h_gammaD_cT_lab__54->GetXaxis()->SetTitleOffset(0.95);
   h_gammaD_cT_lab__54->GetXaxis()->SetTitleFont(42);
   h_gammaD_cT_lab__54->GetYaxis()->SetTitle("Events");
   h_gammaD_cT_lab__54->GetYaxis()->SetLabelFont(42);
   h_gammaD_cT_lab__54->GetYaxis()->SetLabelOffset(0.007);
   h_gammaD_cT_lab__54->GetYaxis()->SetTitleSize(0.06);
   h_gammaD_cT_lab__54->GetYaxis()->SetTitleOffset(1.5);
   h_gammaD_cT_lab__54->GetYaxis()->SetTitleFont(42);
   h_gammaD_cT_lab__54->GetZaxis()->SetLabelFont(42);
   h_gammaD_cT_lab__54->GetZaxis()->SetLabelOffset(0.007);
   h_gammaD_cT_lab__54->GetZaxis()->SetTitleSize(0.06);
   h_gammaD_cT_lab__54->GetZaxis()->SetTitleFont(42);
   h_gammaD_cT_lab__54->Draw("same");
   
   TLegend *leg = new TLegend(0.4566667,0.82,0.7822222,0.9066667,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.02777778);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("NULL","#splitline{pp #rightarrow h #rightarrow 2n_{1} #rightarrow 2n_{D} + 2 #gamma_{D} #rightarrow 2n_{D} + 4#mu}{#splitline{m_{h} = 125 GeV, m_{n_{1}} = 10 GeV, m_{n_{D}} = 1 GeV}{m_{#gamma_{D}} = 0.4 GeV, c#tau_{#gamma_{D}} = 1. mm}}","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   leg = new TLegend(0.17,0.935,0.97,1,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextAlign(22);
   leg->SetTextSize(0.045);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   entry=leg->AddEntry("NULL","CMS Simulation (LHE) 13 TeV","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   cnv->Modified();
   cnv->cd();
   cnv->SetSelected(cnv);
}
