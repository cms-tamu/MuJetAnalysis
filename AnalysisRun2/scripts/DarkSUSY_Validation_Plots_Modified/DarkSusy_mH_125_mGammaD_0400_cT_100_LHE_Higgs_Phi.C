void DarkSusy_mH_125_mGammaD_0400_cT_100_LHE_Higgs_Phi()
{
//=========Macro generated from canvas: cnv/cnv
//=========  (Sun May  6 01:34:40 2018) by ROOT version6.06/01
   TCanvas *cnv = new TCanvas("cnv", "cnv",1,1,904,904);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   cnv->SetHighLightColor(2);
   cnv->Range(-5.7,-0.2275,4.3,1.5225);
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
   
   TH1F *h_higgs_Phi_dummy__7 = new TH1F("h_higgs_Phi_dummy__7","h_higgs_Phi_dummy",80,-4,4);
   h_higgs_Phi_dummy__7->SetMaximum(1.4);
   h_higgs_Phi_dummy__7->SetLineStyle(0);
   h_higgs_Phi_dummy__7->SetMarkerStyle(20);
   h_higgs_Phi_dummy__7->GetXaxis()->SetTitle("#phi of h [rad]");
   h_higgs_Phi_dummy__7->GetXaxis()->SetLabelFont(42);
   h_higgs_Phi_dummy__7->GetXaxis()->SetLabelOffset(0.007);
   h_higgs_Phi_dummy__7->GetXaxis()->SetTitleSize(0.06);
   h_higgs_Phi_dummy__7->GetXaxis()->SetTitleOffset(0.95);
   h_higgs_Phi_dummy__7->GetXaxis()->SetTitleFont(42);
   h_higgs_Phi_dummy__7->GetYaxis()->SetTitle("Fraction of events");
   h_higgs_Phi_dummy__7->GetYaxis()->SetLabelFont(42);
   h_higgs_Phi_dummy__7->GetYaxis()->SetLabelOffset(0.007);
   h_higgs_Phi_dummy__7->GetYaxis()->SetTitleSize(0.06);
   h_higgs_Phi_dummy__7->GetYaxis()->SetTitleOffset(1.35);
   h_higgs_Phi_dummy__7->GetYaxis()->SetTitleFont(42);
   h_higgs_Phi_dummy__7->GetZaxis()->SetLabelFont(42);
   h_higgs_Phi_dummy__7->GetZaxis()->SetLabelOffset(0.007);
   h_higgs_Phi_dummy__7->GetZaxis()->SetTitleSize(0.06);
   h_higgs_Phi_dummy__7->GetZaxis()->SetTitleFont(42);
   h_higgs_Phi_dummy__7->Draw("");
   
   TH1F *h_higgs_Phi__8 = new TH1F("h_higgs_Phi__8","h_higgs_Phi",80,-4,4);
   h_higgs_Phi__8->SetBinContent(41,1);
   h_higgs_Phi__8->SetBinError(41,0.003535556);
   h_higgs_Phi__8->SetEntries(79999);
   h_higgs_Phi__8->SetDirectory(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#0000ff");
   h_higgs_Phi__8->SetLineColor(ci);
   h_higgs_Phi__8->SetLineWidth(2);
   h_higgs_Phi__8->SetMarkerStyle(20);
   h_higgs_Phi__8->GetXaxis()->SetLabelFont(42);
   h_higgs_Phi__8->GetXaxis()->SetLabelOffset(0.007);
   h_higgs_Phi__8->GetXaxis()->SetTitleSize(0.06);
   h_higgs_Phi__8->GetXaxis()->SetTitleOffset(0.95);
   h_higgs_Phi__8->GetXaxis()->SetTitleFont(42);
   h_higgs_Phi__8->GetYaxis()->SetLabelFont(42);
   h_higgs_Phi__8->GetYaxis()->SetLabelOffset(0.007);
   h_higgs_Phi__8->GetYaxis()->SetTitleSize(0.06);
   h_higgs_Phi__8->GetYaxis()->SetTitleOffset(1.3);
   h_higgs_Phi__8->GetYaxis()->SetTitleFont(42);
   h_higgs_Phi__8->GetZaxis()->SetLabelFont(42);
   h_higgs_Phi__8->GetZaxis()->SetLabelOffset(0.007);
   h_higgs_Phi__8->GetZaxis()->SetTitleSize(0.06);
   h_higgs_Phi__8->GetZaxis()->SetTitleFont(42);
   h_higgs_Phi__8->Draw("SAMEHIST");
   
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
