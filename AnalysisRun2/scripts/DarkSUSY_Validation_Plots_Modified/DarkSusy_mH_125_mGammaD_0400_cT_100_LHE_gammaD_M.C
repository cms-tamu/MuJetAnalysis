void DarkSusy_mH_125_mGammaD_0400_cT_100_LHE_gammaD_M()
{
//=========Macro generated from canvas: cnv/cnv
//=========  (Sun May  6 01:34:48 2018) by ROOT version6.06/01
   TCanvas *cnv = new TCanvas("cnv", "cnv",1,1,904,904);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   cnv->SetHighLightColor(2);
   cnv->Range(-1.425918,-0.2275,1.079483,1.5225);
   cnv->SetFillColor(0);
   cnv->SetBorderMode(0);
   cnv->SetBorderSize(2);
   cnv->SetLogx();
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
   
   TH1F *h_gammaD_1_M_dummy__86 = new TH1F("h_gammaD_1_M_dummy__86","h_gammaD_1_M_dummy",101,0.1,10.1);
   h_gammaD_1_M_dummy__86->SetMaximum(1.4);
   h_gammaD_1_M_dummy__86->SetLineStyle(0);
   h_gammaD_1_M_dummy__86->SetMarkerStyle(20);
   h_gammaD_1_M_dummy__86->GetXaxis()->SetTitle("Mass of #gamma_{D} [GeV]");
   h_gammaD_1_M_dummy__86->GetXaxis()->SetLabelFont(42);
   h_gammaD_1_M_dummy__86->GetXaxis()->SetLabelOffset(0.007);
   h_gammaD_1_M_dummy__86->GetXaxis()->SetTitleSize(0.06);
   h_gammaD_1_M_dummy__86->GetXaxis()->SetTitleOffset(0.95);
   h_gammaD_1_M_dummy__86->GetXaxis()->SetTitleFont(42);
   h_gammaD_1_M_dummy__86->GetYaxis()->SetTitle("Fraction of events / 0.1 GeV");
   h_gammaD_1_M_dummy__86->GetYaxis()->SetLabelFont(42);
   h_gammaD_1_M_dummy__86->GetYaxis()->SetLabelOffset(0.007);
   h_gammaD_1_M_dummy__86->GetYaxis()->SetTitleSize(0.06);
   h_gammaD_1_M_dummy__86->GetYaxis()->SetTitleOffset(1.35);
   h_gammaD_1_M_dummy__86->GetYaxis()->SetTitleFont(42);
   h_gammaD_1_M_dummy__86->GetZaxis()->SetLabelFont(42);
   h_gammaD_1_M_dummy__86->GetZaxis()->SetLabelOffset(0.007);
   h_gammaD_1_M_dummy__86->GetZaxis()->SetTitleSize(0.06);
   h_gammaD_1_M_dummy__86->GetZaxis()->SetTitleFont(42);
   h_gammaD_1_M_dummy__86->Draw("");
   
   TH1F *h_gammaD_1_M__87 = new TH1F("h_gammaD_1_M__87","h_gammaD_1_M",101,0.1,10.1);
   h_gammaD_1_M__87->SetBinContent(4,1);
   h_gammaD_1_M__87->SetBinError(4,0.002500016);
   h_gammaD_1_M__87->SetEntries(159998);
   h_gammaD_1_M__87->SetDirectory(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#0000ff");
   h_gammaD_1_M__87->SetLineColor(ci);
   h_gammaD_1_M__87->SetLineWidth(2);
   h_gammaD_1_M__87->SetMarkerStyle(20);
   h_gammaD_1_M__87->GetXaxis()->SetLabelFont(42);
   h_gammaD_1_M__87->GetXaxis()->SetLabelOffset(0.007);
   h_gammaD_1_M__87->GetXaxis()->SetTitleSize(0.06);
   h_gammaD_1_M__87->GetXaxis()->SetTitleOffset(0.95);
   h_gammaD_1_M__87->GetXaxis()->SetTitleFont(42);
   h_gammaD_1_M__87->GetYaxis()->SetLabelFont(42);
   h_gammaD_1_M__87->GetYaxis()->SetLabelOffset(0.007);
   h_gammaD_1_M__87->GetYaxis()->SetTitleSize(0.06);
   h_gammaD_1_M__87->GetYaxis()->SetTitleOffset(1.3);
   h_gammaD_1_M__87->GetYaxis()->SetTitleFont(42);
   h_gammaD_1_M__87->GetZaxis()->SetLabelFont(42);
   h_gammaD_1_M__87->GetZaxis()->SetLabelOffset(0.007);
   h_gammaD_1_M__87->GetZaxis()->SetTitleSize(0.06);
   h_gammaD_1_M__87->GetZaxis()->SetTitleFont(42);
   h_gammaD_1_M__87->Draw("SAMEHIST");
   
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
