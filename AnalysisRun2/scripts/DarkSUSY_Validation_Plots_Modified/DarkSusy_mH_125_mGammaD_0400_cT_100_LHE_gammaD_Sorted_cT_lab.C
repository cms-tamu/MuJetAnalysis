void DarkSusy_mH_125_mGammaD_0400_cT_100_LHE_gammaD_Sorted_cT_lab()
{
//=========Macro generated from canvas: cnv/cnv
//=========  (Sun May  6 01:34:47 2018) by ROOT version6.06/01
   TCanvas *cnv = new TCanvas("cnv", "cnv",1,1,904,904);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   cnv->SetHighLightColor(2);
   cnv->Range(-21.25,-0.006988404,103.75,0.04676855);
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
   
   TH1F *h_gammaD_1_cT_lab_dummy__62 = new TH1F("h_gammaD_1_cT_lab_dummy__62","h_gammaD_1_cT_lab_dummy",5,0,100);
   h_gammaD_1_cT_lab_dummy__62->SetMaximum(0.04300556);
   h_gammaD_1_cT_lab_dummy__62->SetLineStyle(0);
   h_gammaD_1_cT_lab_dummy__62->SetMarkerStyle(20);
   h_gammaD_1_cT_lab_dummy__62->GetXaxis()->SetTitle("L of #gamma_{D} [mm]");
   h_gammaD_1_cT_lab_dummy__62->GetXaxis()->SetLabelFont(42);
   h_gammaD_1_cT_lab_dummy__62->GetXaxis()->SetLabelOffset(0.007);
   h_gammaD_1_cT_lab_dummy__62->GetXaxis()->SetTitleSize(0.06);
   h_gammaD_1_cT_lab_dummy__62->GetXaxis()->SetTitleOffset(0.95);
   h_gammaD_1_cT_lab_dummy__62->GetXaxis()->SetTitleFont(42);
   h_gammaD_1_cT_lab_dummy__62->GetYaxis()->SetTitle("Normalized Fraction of events / 1.0 mm");
   h_gammaD_1_cT_lab_dummy__62->GetYaxis()->SetLabelFont(42);
   h_gammaD_1_cT_lab_dummy__62->GetYaxis()->SetLabelOffset(0.007);
   h_gammaD_1_cT_lab_dummy__62->GetYaxis()->SetTitleSize(0.05);
   h_gammaD_1_cT_lab_dummy__62->GetYaxis()->SetTitleOffset(1.3);
   h_gammaD_1_cT_lab_dummy__62->GetYaxis()->SetTitleFont(42);
   h_gammaD_1_cT_lab_dummy__62->GetZaxis()->SetLabelFont(42);
   h_gammaD_1_cT_lab_dummy__62->GetZaxis()->SetLabelOffset(0.007);
   h_gammaD_1_cT_lab_dummy__62->GetZaxis()->SetTitleSize(0.06);
   h_gammaD_1_cT_lab_dummy__62->GetZaxis()->SetTitleFont(42);
   h_gammaD_1_cT_lab_dummy__62->Draw("");
   
   TH1F *h_gammaD_1_cT_lab__63 = new TH1F("h_gammaD_1_cT_lab__63","h_gammaD_1_cT_lab",5,0,100);
   h_gammaD_1_cT_lab__63->SetBinContent(1,0.0159935);
   h_gammaD_1_cT_lab__63->SetBinContent(2,0.01168478);
   h_gammaD_1_cT_lab__63->SetBinContent(3,0.008931014);
   h_gammaD_1_cT_lab__63->SetBinContent(4,0.007250884);
   h_gammaD_1_cT_lab__63->SetBinContent(5,0.00613983);
   h_gammaD_1_cT_lab__63->SetBinContent(6,0.05323251);
   h_gammaD_1_cT_lab__63->SetEntries(79999);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#0000ff");
   h_gammaD_1_cT_lab__63->SetLineColor(ci);
   h_gammaD_1_cT_lab__63->SetLineWidth(2);
   h_gammaD_1_cT_lab__63->SetMarkerStyle(20);
   h_gammaD_1_cT_lab__63->GetXaxis()->SetLabelFont(42);
   h_gammaD_1_cT_lab__63->GetXaxis()->SetLabelOffset(0.007);
   h_gammaD_1_cT_lab__63->GetXaxis()->SetTitleSize(0.06);
   h_gammaD_1_cT_lab__63->GetXaxis()->SetTitleOffset(0.95);
   h_gammaD_1_cT_lab__63->GetXaxis()->SetTitleFont(42);
   h_gammaD_1_cT_lab__63->GetYaxis()->SetLabelFont(42);
   h_gammaD_1_cT_lab__63->GetYaxis()->SetLabelOffset(0.007);
   h_gammaD_1_cT_lab__63->GetYaxis()->SetTitleSize(0.06);
   h_gammaD_1_cT_lab__63->GetYaxis()->SetTitleOffset(1.3);
   h_gammaD_1_cT_lab__63->GetYaxis()->SetTitleFont(42);
   h_gammaD_1_cT_lab__63->GetZaxis()->SetLabelFont(42);
   h_gammaD_1_cT_lab__63->GetZaxis()->SetLabelOffset(0.007);
   h_gammaD_1_cT_lab__63->GetZaxis()->SetTitleSize(0.06);
   h_gammaD_1_cT_lab__63->GetZaxis()->SetTitleFont(42);
   h_gammaD_1_cT_lab__63->Draw("same");
   
   TH1F *h_gammaD_2_cT_lab__64 = new TH1F("h_gammaD_2_cT_lab__64","h_gammaD_2_cT_lab",5,0,100);
   h_gammaD_2_cT_lab__64->SetBinContent(1,0.02389198);
   h_gammaD_2_cT_lab__64->SetBinContent(2,0.01081913);
   h_gammaD_2_cT_lab__64->SetBinContent(3,0.006869729);
   h_gammaD_2_cT_lab__64->SetBinContent(4,0.004790957);
   h_gammaD_2_cT_lab__64->SetBinContent(5,0.003628207);
   h_gammaD_2_cT_lab__64->SetBinContent(6,0.02177373);
   h_gammaD_2_cT_lab__64->SetEntries(79999);

   ci = TColor::GetColor("#ff0000");
   h_gammaD_2_cT_lab__64->SetLineColor(ci);
   h_gammaD_2_cT_lab__64->SetLineWidth(2);
   h_gammaD_2_cT_lab__64->SetMarkerStyle(20);
   h_gammaD_2_cT_lab__64->GetXaxis()->SetLabelFont(42);
   h_gammaD_2_cT_lab__64->GetXaxis()->SetLabelOffset(0.007);
   h_gammaD_2_cT_lab__64->GetXaxis()->SetTitleSize(0.06);
   h_gammaD_2_cT_lab__64->GetXaxis()->SetTitleOffset(0.95);
   h_gammaD_2_cT_lab__64->GetXaxis()->SetTitleFont(42);
   h_gammaD_2_cT_lab__64->GetYaxis()->SetLabelFont(42);
   h_gammaD_2_cT_lab__64->GetYaxis()->SetLabelOffset(0.007);
   h_gammaD_2_cT_lab__64->GetYaxis()->SetTitleSize(0.06);
   h_gammaD_2_cT_lab__64->GetYaxis()->SetTitleOffset(1.3);
   h_gammaD_2_cT_lab__64->GetYaxis()->SetTitleFont(42);
   h_gammaD_2_cT_lab__64->GetZaxis()->SetLabelFont(42);
   h_gammaD_2_cT_lab__64->GetZaxis()->SetLabelOffset(0.007);
   h_gammaD_2_cT_lab__64->GetZaxis()->SetTitleSize(0.06);
   h_gammaD_2_cT_lab__64->GetZaxis()->SetTitleFont(42);
   h_gammaD_2_cT_lab__64->Draw("same");
   
   TLegend *leg = new TLegend(0.46,0.6744444,0.6955556,0.7644444,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.02777778);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("h_gammaD_1_cT_lab","1st dark photon (leading p_{T})","L");

   ci = TColor::GetColor("#0000ff");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("h_gammaD_2_cT_lab","2nd dark photon","L");

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
