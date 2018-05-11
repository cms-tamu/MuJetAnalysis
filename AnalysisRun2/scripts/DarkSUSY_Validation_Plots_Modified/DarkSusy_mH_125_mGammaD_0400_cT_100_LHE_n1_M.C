void DarkSusy_mH_125_mGammaD_0400_cT_100_LHE_n1_M()
{
//=========Macro generated from canvas: cnv/cnv
//=========  (Sun May  6 01:34:45 2018) by ROOT version6.06/01
   TCanvas *cnv = new TCanvas("cnv", "cnv",1,1,904,904);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   cnv->SetHighLightColor(2);
   cnv->Range(-4.2,-0.26,20.8,1.74);
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
   
   TH1F *h_n1_1_M_dummy__32 = new TH1F("h_n1_1_M_dummy__32","h_n1_1_M_dummy",200,0.05,20.05);
   h_n1_1_M_dummy__32->SetMaximum(1.6);
   h_n1_1_M_dummy__32->SetLineStyle(0);
   h_n1_1_M_dummy__32->SetMarkerStyle(20);
   h_n1_1_M_dummy__32->GetXaxis()->SetTitle("Mass of n_{1} [GeV]");
   h_n1_1_M_dummy__32->GetXaxis()->SetLabelFont(42);
   h_n1_1_M_dummy__32->GetXaxis()->SetLabelOffset(0.007);
   h_n1_1_M_dummy__32->GetXaxis()->SetTitleSize(0.06);
   h_n1_1_M_dummy__32->GetXaxis()->SetTitleOffset(0.95);
   h_n1_1_M_dummy__32->GetXaxis()->SetTitleFont(42);
   h_n1_1_M_dummy__32->GetYaxis()->SetTitle("Fraction of events / 0.1 GeV");
   h_n1_1_M_dummy__32->GetYaxis()->SetLabelFont(42);
   h_n1_1_M_dummy__32->GetYaxis()->SetLabelOffset(0.007);
   h_n1_1_M_dummy__32->GetYaxis()->SetTitleSize(0.06);
   h_n1_1_M_dummy__32->GetYaxis()->SetTitleOffset(1.35);
   h_n1_1_M_dummy__32->GetYaxis()->SetTitleFont(42);
   h_n1_1_M_dummy__32->GetZaxis()->SetLabelFont(42);
   h_n1_1_M_dummy__32->GetZaxis()->SetLabelOffset(0.007);
   h_n1_1_M_dummy__32->GetZaxis()->SetTitleSize(0.06);
   h_n1_1_M_dummy__32->GetZaxis()->SetTitleFont(42);
   h_n1_1_M_dummy__32->Draw("");
   
   TH1F *h_n1_1_M__33 = new TH1F("h_n1_1_M__33","h_n1_1_M",200,0.05,20.05);
   h_n1_1_M__33->SetBinContent(100,1);
   h_n1_1_M__33->SetBinError(100,0.002500016);
   h_n1_1_M__33->SetEntries(159998);
   h_n1_1_M__33->SetDirectory(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#0000ff");
   h_n1_1_M__33->SetLineColor(ci);
   h_n1_1_M__33->SetLineWidth(2);
   h_n1_1_M__33->SetMarkerStyle(20);
   h_n1_1_M__33->GetXaxis()->SetLabelFont(42);
   h_n1_1_M__33->GetXaxis()->SetLabelOffset(0.007);
   h_n1_1_M__33->GetXaxis()->SetTitleSize(0.06);
   h_n1_1_M__33->GetXaxis()->SetTitleOffset(0.95);
   h_n1_1_M__33->GetXaxis()->SetTitleFont(42);
   h_n1_1_M__33->GetYaxis()->SetLabelFont(42);
   h_n1_1_M__33->GetYaxis()->SetLabelOffset(0.007);
   h_n1_1_M__33->GetYaxis()->SetTitleSize(0.06);
   h_n1_1_M__33->GetYaxis()->SetTitleOffset(1.3);
   h_n1_1_M__33->GetYaxis()->SetTitleFont(42);
   h_n1_1_M__33->GetZaxis()->SetLabelFont(42);
   h_n1_1_M__33->GetZaxis()->SetLabelOffset(0.007);
   h_n1_1_M__33->GetZaxis()->SetTitleSize(0.06);
   h_n1_1_M__33->GetZaxis()->SetTitleFont(42);
   h_n1_1_M__33->Draw("SAMEHIST");
   
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
