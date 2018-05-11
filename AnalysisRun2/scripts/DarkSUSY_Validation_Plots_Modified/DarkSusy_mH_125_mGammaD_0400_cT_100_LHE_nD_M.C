void DarkSusy_mH_125_mGammaD_0400_cT_100_LHE_nD_M()
{
//=========Macro generated from canvas: cnv/cnv
//=========  (Sun May  6 01:34:46 2018) by ROOT version6.06/01
   TCanvas *cnv = new TCanvas("cnv", "cnv",1,1,904,904);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   cnv->SetHighLightColor(2);
   cnv->Range(-0.375,-0.26,2.125,1.74);
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
   
   TH1F *h_nD_1_M_dummy__49 = new TH1F("h_nD_1_M_dummy__49","h_nD_1_M_dummy",20,0.05,2.05);
   h_nD_1_M_dummy__49->SetMaximum(1.6);
   h_nD_1_M_dummy__49->SetLineStyle(0);
   h_nD_1_M_dummy__49->SetMarkerStyle(20);
   h_nD_1_M_dummy__49->GetXaxis()->SetTitle("Mass of n_{D} [GeV]");
   h_nD_1_M_dummy__49->GetXaxis()->SetLabelFont(42);
   h_nD_1_M_dummy__49->GetXaxis()->SetLabelOffset(0.007);
   h_nD_1_M_dummy__49->GetXaxis()->SetTitleSize(0.06);
   h_nD_1_M_dummy__49->GetXaxis()->SetTitleOffset(0.95);
   h_nD_1_M_dummy__49->GetXaxis()->SetTitleFont(42);
   h_nD_1_M_dummy__49->GetYaxis()->SetTitle("Fraction of events / 0.1 GeV");
   h_nD_1_M_dummy__49->GetYaxis()->SetLabelFont(42);
   h_nD_1_M_dummy__49->GetYaxis()->SetLabelOffset(0.007);
   h_nD_1_M_dummy__49->GetYaxis()->SetTitleSize(0.06);
   h_nD_1_M_dummy__49->GetYaxis()->SetTitleOffset(1.35);
   h_nD_1_M_dummy__49->GetYaxis()->SetTitleFont(42);
   h_nD_1_M_dummy__49->GetZaxis()->SetLabelFont(42);
   h_nD_1_M_dummy__49->GetZaxis()->SetLabelOffset(0.007);
   h_nD_1_M_dummy__49->GetZaxis()->SetTitleSize(0.06);
   h_nD_1_M_dummy__49->GetZaxis()->SetTitleFont(42);
   h_nD_1_M_dummy__49->Draw("");
   
   TH1F *h_nD_1_M__50 = new TH1F("h_nD_1_M__50","h_nD_1_M",20,0.05,2.05);
   h_nD_1_M__50->SetBinContent(10,1);
   h_nD_1_M__50->SetBinError(10,0.002500016);
   h_nD_1_M__50->SetEntries(159998);
   h_nD_1_M__50->SetDirectory(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#0000ff");
   h_nD_1_M__50->SetLineColor(ci);
   h_nD_1_M__50->SetLineWidth(2);
   h_nD_1_M__50->SetMarkerStyle(20);
   h_nD_1_M__50->GetXaxis()->SetLabelFont(42);
   h_nD_1_M__50->GetXaxis()->SetLabelOffset(0.007);
   h_nD_1_M__50->GetXaxis()->SetTitleSize(0.06);
   h_nD_1_M__50->GetXaxis()->SetTitleOffset(0.95);
   h_nD_1_M__50->GetXaxis()->SetTitleFont(42);
   h_nD_1_M__50->GetYaxis()->SetLabelFont(42);
   h_nD_1_M__50->GetYaxis()->SetLabelOffset(0.007);
   h_nD_1_M__50->GetYaxis()->SetTitleSize(0.06);
   h_nD_1_M__50->GetYaxis()->SetTitleOffset(1.3);
   h_nD_1_M__50->GetYaxis()->SetTitleFont(42);
   h_nD_1_M__50->GetZaxis()->SetLabelFont(42);
   h_nD_1_M__50->GetZaxis()->SetLabelOffset(0.007);
   h_nD_1_M__50->GetZaxis()->SetTitleSize(0.06);
   h_nD_1_M__50->GetZaxis()->SetTitleFont(42);
   h_nD_1_M__50->Draw("SAMEHIST");
   
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
