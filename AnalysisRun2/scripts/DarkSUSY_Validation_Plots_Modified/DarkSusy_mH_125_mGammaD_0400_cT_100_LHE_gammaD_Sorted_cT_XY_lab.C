void DarkSusy_mH_125_mGammaD_0400_cT_100_LHE_gammaD_Sorted_cT_XY_lab()
{
//=========Macro generated from canvas: cnv/cnv
//=========  (Sun May  6 01:34:47 2018) by ROOT version6.06/01
   TCanvas *cnv = new TCanvas("cnv", "cnv",1,1,904,904);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   cnv->SetHighLightColor(2);
   cnv->Range(-21.25,-0.008443335,103.75,0.0565054);
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
   
   TH1F *h_gammaD_1_cT_XY_lab_dummy__65 = new TH1F("h_gammaD_1_cT_XY_lab_dummy__65","h_gammaD_1_cT_XY_lab_dummy",5,0,100);
   h_gammaD_1_cT_XY_lab_dummy__65->SetMaximum(0.05195899);
   h_gammaD_1_cT_XY_lab_dummy__65->SetLineStyle(0);
   h_gammaD_1_cT_XY_lab_dummy__65->SetMarkerStyle(20);
   h_gammaD_1_cT_XY_lab_dummy__65->GetXaxis()->SetTitle("L_{XY} of #gamma_{D} [mm]");
   h_gammaD_1_cT_XY_lab_dummy__65->GetXaxis()->SetLabelFont(42);
   h_gammaD_1_cT_XY_lab_dummy__65->GetXaxis()->SetLabelOffset(0.007);
   h_gammaD_1_cT_XY_lab_dummy__65->GetXaxis()->SetTitleSize(0.06);
   h_gammaD_1_cT_XY_lab_dummy__65->GetXaxis()->SetTitleOffset(0.95);
   h_gammaD_1_cT_XY_lab_dummy__65->GetXaxis()->SetTitleFont(42);
   h_gammaD_1_cT_XY_lab_dummy__65->GetYaxis()->SetTitle("Normalized Fraction of events / 1.0 mm");
   h_gammaD_1_cT_XY_lab_dummy__65->GetYaxis()->SetLabelFont(42);
   h_gammaD_1_cT_XY_lab_dummy__65->GetYaxis()->SetLabelOffset(0.007);
   h_gammaD_1_cT_XY_lab_dummy__65->GetYaxis()->SetTitleSize(0.05);
   h_gammaD_1_cT_XY_lab_dummy__65->GetYaxis()->SetTitleOffset(1.3);
   h_gammaD_1_cT_XY_lab_dummy__65->GetYaxis()->SetTitleFont(42);
   h_gammaD_1_cT_XY_lab_dummy__65->GetZaxis()->SetLabelFont(42);
   h_gammaD_1_cT_XY_lab_dummy__65->GetZaxis()->SetLabelOffset(0.007);
   h_gammaD_1_cT_XY_lab_dummy__65->GetZaxis()->SetTitleSize(0.06);
   h_gammaD_1_cT_XY_lab_dummy__65->GetZaxis()->SetTitleFont(42);
   h_gammaD_1_cT_XY_lab_dummy__65->Draw("");
   
   TH1F *h_gammaD_1_cT_XY_lab__66 = new TH1F("h_gammaD_1_cT_XY_lab__66","h_gammaD_1_cT_XY_lab",5,0,100);
   h_gammaD_1_cT_XY_lab__66->SetBinContent(1,0.01886752);
   h_gammaD_1_cT_XY_lab__66->SetBinContent(2,0.01181469);
   h_gammaD_1_cT_XY_lab__66->SetBinContent(3,0.008376094);
   h_gammaD_1_cT_XY_lab__66->SetBinContent(4,0.006242682);
   h_gammaD_1_cT_XY_lab__66->SetBinContent(5,0.004699015);
   h_gammaD_1_cT_XY_lab__66->SetBinContent(6,0.01887441);
   h_gammaD_1_cT_XY_lab__66->SetEntries(79999);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#0000ff");
   h_gammaD_1_cT_XY_lab__66->SetLineColor(ci);
   h_gammaD_1_cT_XY_lab__66->SetLineWidth(2);
   h_gammaD_1_cT_XY_lab__66->SetMarkerStyle(20);
   h_gammaD_1_cT_XY_lab__66->GetXaxis()->SetLabelFont(42);
   h_gammaD_1_cT_XY_lab__66->GetXaxis()->SetLabelOffset(0.007);
   h_gammaD_1_cT_XY_lab__66->GetXaxis()->SetTitleSize(0.06);
   h_gammaD_1_cT_XY_lab__66->GetXaxis()->SetTitleOffset(0.95);
   h_gammaD_1_cT_XY_lab__66->GetXaxis()->SetTitleFont(42);
   h_gammaD_1_cT_XY_lab__66->GetYaxis()->SetLabelFont(42);
   h_gammaD_1_cT_XY_lab__66->GetYaxis()->SetLabelOffset(0.007);
   h_gammaD_1_cT_XY_lab__66->GetYaxis()->SetTitleSize(0.06);
   h_gammaD_1_cT_XY_lab__66->GetYaxis()->SetTitleOffset(1.3);
   h_gammaD_1_cT_XY_lab__66->GetYaxis()->SetTitleFont(42);
   h_gammaD_1_cT_XY_lab__66->GetZaxis()->SetLabelFont(42);
   h_gammaD_1_cT_XY_lab__66->GetZaxis()->SetLabelOffset(0.007);
   h_gammaD_1_cT_XY_lab__66->GetZaxis()->SetTitleSize(0.06);
   h_gammaD_1_cT_XY_lab__66->GetZaxis()->SetTitleFont(42);
   h_gammaD_1_cT_XY_lab__66->Draw("same");
   
   TH1F *h_gammaD_2_cT_XY_lab__67 = new TH1F("h_gammaD_2_cT_XY_lab__67","h_gammaD_2_cT_XY_lab",5,0,100);
   h_gammaD_2_cT_XY_lab__67->SetBinContent(1,0.0288661);
   h_gammaD_2_cT_XY_lab__67->SetBinContent(2,0.009995923);
   h_gammaD_2_cT_XY_lab__67->SetBinContent(3,0.005493084);
   h_gammaD_2_cT_XY_lab__67->SetBinContent(4,0.003401552);
   h_gammaD_2_cT_XY_lab__67->SetBinContent(5,0.002243337);
   h_gammaD_2_cT_XY_lab__67->SetBinContent(6,0.006223293);
   h_gammaD_2_cT_XY_lab__67->SetEntries(79999);

   ci = TColor::GetColor("#ff0000");
   h_gammaD_2_cT_XY_lab__67->SetLineColor(ci);
   h_gammaD_2_cT_XY_lab__67->SetLineWidth(2);
   h_gammaD_2_cT_XY_lab__67->SetMarkerStyle(20);
   h_gammaD_2_cT_XY_lab__67->GetXaxis()->SetLabelFont(42);
   h_gammaD_2_cT_XY_lab__67->GetXaxis()->SetLabelOffset(0.007);
   h_gammaD_2_cT_XY_lab__67->GetXaxis()->SetTitleSize(0.06);
   h_gammaD_2_cT_XY_lab__67->GetXaxis()->SetTitleOffset(0.95);
   h_gammaD_2_cT_XY_lab__67->GetXaxis()->SetTitleFont(42);
   h_gammaD_2_cT_XY_lab__67->GetYaxis()->SetLabelFont(42);
   h_gammaD_2_cT_XY_lab__67->GetYaxis()->SetLabelOffset(0.007);
   h_gammaD_2_cT_XY_lab__67->GetYaxis()->SetTitleSize(0.06);
   h_gammaD_2_cT_XY_lab__67->GetYaxis()->SetTitleOffset(1.3);
   h_gammaD_2_cT_XY_lab__67->GetYaxis()->SetTitleFont(42);
   h_gammaD_2_cT_XY_lab__67->GetZaxis()->SetLabelFont(42);
   h_gammaD_2_cT_XY_lab__67->GetZaxis()->SetLabelOffset(0.007);
   h_gammaD_2_cT_XY_lab__67->GetZaxis()->SetTitleSize(0.06);
   h_gammaD_2_cT_XY_lab__67->GetZaxis()->SetTitleFont(42);
   h_gammaD_2_cT_XY_lab__67->Draw("same");
   
   TLegend *leg = new TLegend(0.46,0.6744444,0.6955556,0.7644444,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.02777778);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("h_gammaD_1_cT_XY_lab","1st dark photon (leading p_{T})","L");

   ci = TColor::GetColor("#0000ff");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("h_gammaD_2_cT_XY_lab","2nd dark photon","L");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   leg = new TLegend(0.4566667,0.82,0.7822222,0.9066667,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.02777778);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   entry=leg->AddEntry("NULL","#splitline{pp #rightarrow h #rightarrow 2n_{1} #rightarrow 2n_{D} + 2 #gamma_{D} #rightarrow 2n_{D} + 4#mu}{#splitline{m_{h} = 125 GeV, m_{n_{1}} = 10 GeV, m_{n_{D}} = 1 GeV}{m_{#gamma_{D}} = 0.4 GeV, c#tau_{#gamma_{D}} = 1. mm}}","h");
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
