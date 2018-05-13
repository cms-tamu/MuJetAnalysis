void diMuonC_Lxy_regionA_DPS()
{
//=========Macro generated from canvas: c2221/c2221
//=========  (Tue Feb 27 16:25:31 2018) by ROOT version6.06/01
   TCanvas *c2221 = new TCanvas("c2221", "c2221",0,0,700,500);
   c2221->Range(-0.35,-3.9375,1.15,35.4375);
   c2221->SetFillColor(0);
   c2221->SetBorderMode(0);
   c2221->SetBorderSize(2);
   c2221->SetFrameBorderMode(0);
   c2221->SetFrameBorderMode(0);
   
   TH1F *diMuonC_Lxy_RegionA__4 = new TH1F("diMuonC_Lxy_RegionA__4","",50,-0.2,1);
   diMuonC_Lxy_RegionA__4->SetBinContent(8,14);
   diMuonC_Lxy_RegionA__4->SetBinContent(9,30);
   diMuonC_Lxy_RegionA__4->SetBinContent(10,14);
   diMuonC_Lxy_RegionA__4->SetBinContent(11,8);
   diMuonC_Lxy_RegionA__4->SetBinContent(12,8);
   diMuonC_Lxy_RegionA__4->SetBinContent(13,7);
   diMuonC_Lxy_RegionA__4->SetBinContent(14,4);
   diMuonC_Lxy_RegionA__4->SetBinContent(15,2);
   diMuonC_Lxy_RegionA__4->SetBinContent(16,1);
   diMuonC_Lxy_RegionA__4->SetBinContent(17,2);
   diMuonC_Lxy_RegionA__4->SetBinContent(18,4);
   diMuonC_Lxy_RegionA__4->SetBinContent(19,3);
   diMuonC_Lxy_RegionA__4->SetBinContent(20,2);
   diMuonC_Lxy_RegionA__4->SetBinContent(21,2);
   diMuonC_Lxy_RegionA__4->SetBinContent(22,1);
   diMuonC_Lxy_RegionA__4->SetBinContent(23,1);
   diMuonC_Lxy_RegionA__4->SetBinContent(24,3);
   diMuonC_Lxy_RegionA__4->SetBinContent(26,2);
   diMuonC_Lxy_RegionA__4->SetBinContent(27,1);
   diMuonC_Lxy_RegionA__4->SetBinContent(30,1);
   diMuonC_Lxy_RegionA__4->SetBinContent(31,1);
   diMuonC_Lxy_RegionA__4->SetBinContent(35,1);
   diMuonC_Lxy_RegionA__4->SetBinContent(37,1);
   diMuonC_Lxy_RegionA__4->SetBinContent(38,1);
   diMuonC_Lxy_RegionA__4->SetBinContent(41,1);
   diMuonC_Lxy_RegionA__4->SetBinContent(43,1);
   diMuonC_Lxy_RegionA__4->SetBinContent(49,1);
   diMuonC_Lxy_RegionA__4->SetBinContent(51,1);
   diMuonC_Lxy_RegionA__4->SetEntries(118);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *AText = ptstats->AddText("diMuonC_Lxy_RegionA");
   AText->SetTextSize(0.0368);
   AText = ptstats->AddText("Entries = 118    ");
   AText = ptstats->AddText("Mean  = 0.1263");
   AText = ptstats->AddText("Std Dev   = 0.1947");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   diMuonC_Lxy_RegionA__4->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(diMuonC_Lxy_RegionA__4);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   diMuonC_Lxy_RegionA__4->SetLineColor(ci);
   diMuonC_Lxy_RegionA__4->GetXaxis()->SetTitle("Lxy_{di-#mu_{1}} [cm]");
   diMuonC_Lxy_RegionA__4->GetXaxis()->SetLabelFont(42);
   diMuonC_Lxy_RegionA__4->GetXaxis()->SetLabelSize(0.035);
   diMuonC_Lxy_RegionA__4->GetXaxis()->SetTitleSize(0.035);
   diMuonC_Lxy_RegionA__4->GetXaxis()->SetTitleFont(42);
   diMuonC_Lxy_RegionA__4->GetYaxis()->SetLabelFont(42);
   diMuonC_Lxy_RegionA__4->GetYaxis()->SetLabelSize(0.035);
   diMuonC_Lxy_RegionA__4->GetYaxis()->SetTitleSize(0.035);
   diMuonC_Lxy_RegionA__4->GetYaxis()->SetTitleFont(42);
   diMuonC_Lxy_RegionA__4->GetZaxis()->SetLabelFont(42);
   diMuonC_Lxy_RegionA__4->GetZaxis()->SetLabelSize(0.035);
   diMuonC_Lxy_RegionA__4->GetZaxis()->SetTitleSize(0.035);
   diMuonC_Lxy_RegionA__4->GetZaxis()->SetTitleFont(42);
   diMuonC_Lxy_RegionA__4->Draw("");
   TText *text = new TText(0.18,0.85,"CMS Simulation");
   text->SetNDC();
   text->Draw();
   c2221->Modified();
   c2221->cd();
   c2221->SetSelected(c2221);
}
