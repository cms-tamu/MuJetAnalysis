void DarkSusy_mH_125_mGammaD_0400_cT_100_LHE_dimuon_m1_vs_m2()
{
//=========Macro generated from canvas: cnv/cnv
//=========  (Sun May  6 01:34:54 2018) by ROOT version6.06/01
   TCanvas *cnv = new TCanvas("cnv", "cnv",1,1,904,904);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   cnv->SetHighLightColor(2);
   cnv->Range(-0.4989387,-0.3318237,3.678936,3.846051);
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
   
   TH2F *h_m1_vs_m2__113 = new TH2F("h_m1_vs_m2__113","h_m1_vs_m2",66,0.2113,3.5536,66,0.2113,3.5536);
   h_m1_vs_m2__113->SetBinContent(276,79999);
   h_m1_vs_m2__113->SetEntries(79999);
   h_m1_vs_m2__113->SetLineStyle(0);
   h_m1_vs_m2__113->SetMarkerStyle(20);
   h_m1_vs_m2__113->GetXaxis()->SetTitle("m_{2#mu#mu} [GeV]");
   h_m1_vs_m2__113->GetXaxis()->SetLabelFont(42);
   h_m1_vs_m2__113->GetXaxis()->SetLabelOffset(0.007);
   h_m1_vs_m2__113->GetXaxis()->SetTitleSize(0.06);
   h_m1_vs_m2__113->GetXaxis()->SetTitleOffset(0.95);
   h_m1_vs_m2__113->GetXaxis()->SetTitleFont(42);
   h_m1_vs_m2__113->GetYaxis()->SetTitle("m_{1#mu#mu} [GeV]");
   h_m1_vs_m2__113->GetYaxis()->SetLabelFont(42);
   h_m1_vs_m2__113->GetYaxis()->SetLabelOffset(0.007);
   h_m1_vs_m2__113->GetYaxis()->SetTitleSize(0.06);
   h_m1_vs_m2__113->GetYaxis()->SetTitleOffset(1.3);
   h_m1_vs_m2__113->GetYaxis()->SetTitleFont(42);
   h_m1_vs_m2__113->GetZaxis()->SetLabelFont(42);
   h_m1_vs_m2__113->GetZaxis()->SetLabelOffset(0.007);
   h_m1_vs_m2__113->GetZaxis()->SetTitleSize(0.06);
   h_m1_vs_m2__113->GetZaxis()->SetTitleFont(42);
   h_m1_vs_m2__113->Draw("");
   
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
