void diMuonF_Rapidity_regionA_DPS()
{
//=========Macro generated from canvas: c22222/c22222
//=========  (Tue Feb 27 16:25:31 2018) by ROOT version6.06/01
   TCanvas *c22222 = new TCanvas("c22222", "c22222",0,0,700,500);
   c22222->Range(-0.7125,-0.9187501,3.4125,8.26875);
   c22222->SetFillColor(0);
   c22222->SetBorderMode(0);
   c22222->SetBorderSize(2);
   c22222->SetFrameBorderMode(0);
   c22222->SetFrameBorderMode(0);
   
   TH1F *diMuonF_Rapidity_RegionA__9 = new TH1F("diMuonF_Rapidity_RegionA__9","",50,-0.3,3);
   diMuonF_Rapidity_RegionA__9->SetBinContent(0,44);
   diMuonF_Rapidity_RegionA__9->SetBinContent(1,1);
   diMuonF_Rapidity_RegionA__9->SetBinContent(3,3);
   diMuonF_Rapidity_RegionA__9->SetBinContent(4,3);
   diMuonF_Rapidity_RegionA__9->SetBinContent(5,4);
   diMuonF_Rapidity_RegionA__9->SetBinContent(6,3);
   diMuonF_Rapidity_RegionA__9->SetBinContent(7,4);
   diMuonF_Rapidity_RegionA__9->SetBinContent(8,2);
   diMuonF_Rapidity_RegionA__9->SetBinContent(9,2);
   diMuonF_Rapidity_RegionA__9->SetBinContent(10,2);
   diMuonF_Rapidity_RegionA__9->SetBinContent(11,3);
   diMuonF_Rapidity_RegionA__9->SetBinContent(12,1);
   diMuonF_Rapidity_RegionA__9->SetBinContent(14,1);
   diMuonF_Rapidity_RegionA__9->SetBinContent(15,2);
   diMuonF_Rapidity_RegionA__9->SetBinContent(16,2);
   diMuonF_Rapidity_RegionA__9->SetBinContent(17,7);
   diMuonF_Rapidity_RegionA__9->SetBinContent(19,4);
   diMuonF_Rapidity_RegionA__9->SetBinContent(21,3);
   diMuonF_Rapidity_RegionA__9->SetBinContent(22,2);
   diMuonF_Rapidity_RegionA__9->SetBinContent(23,1);
   diMuonF_Rapidity_RegionA__9->SetBinContent(24,2);
   diMuonF_Rapidity_RegionA__9->SetBinContent(26,2);
   diMuonF_Rapidity_RegionA__9->SetBinContent(27,4);
   diMuonF_Rapidity_RegionA__9->SetBinContent(28,1);
   diMuonF_Rapidity_RegionA__9->SetBinContent(29,3);
   diMuonF_Rapidity_RegionA__9->SetBinContent(30,1);
   diMuonF_Rapidity_RegionA__9->SetBinContent(31,1);
   diMuonF_Rapidity_RegionA__9->SetBinContent(32,1);
   diMuonF_Rapidity_RegionA__9->SetBinContent(34,1);
   diMuonF_Rapidity_RegionA__9->SetBinContent(35,1);
   diMuonF_Rapidity_RegionA__9->SetBinContent(36,2);
   diMuonF_Rapidity_RegionA__9->SetBinContent(37,2);
   diMuonF_Rapidity_RegionA__9->SetBinContent(38,1);
   diMuonF_Rapidity_RegionA__9->SetBinContent(39,2);
   diMuonF_Rapidity_RegionA__9->SetEntries(118);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *AText = ptstats->AddText("diMuonF_Rapidity_RegionA");
   AText->SetTextSize(0.0368);
   AText = ptstats->AddText("Entries = 118    ");
   AText = ptstats->AddText("Mean  = 0.8537");
   AText = ptstats->AddText("Std Dev   = 0.7142");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   diMuonF_Rapidity_RegionA__9->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(diMuonF_Rapidity_RegionA__9);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   diMuonF_Rapidity_RegionA__9->SetLineColor(ci);
   diMuonF_Rapidity_RegionA__9->GetXaxis()->SetTitle("Rapidity_{di-#mu_{2}}");
   diMuonF_Rapidity_RegionA__9->GetXaxis()->SetLabelFont(42);
   diMuonF_Rapidity_RegionA__9->GetXaxis()->SetLabelSize(0.035);
   diMuonF_Rapidity_RegionA__9->GetXaxis()->SetTitleSize(0.035);
   diMuonF_Rapidity_RegionA__9->GetXaxis()->SetTitleFont(42);
   diMuonF_Rapidity_RegionA__9->GetYaxis()->SetLabelFont(42);
   diMuonF_Rapidity_RegionA__9->GetYaxis()->SetLabelSize(0.035);
   diMuonF_Rapidity_RegionA__9->GetYaxis()->SetTitleSize(0.035);
   diMuonF_Rapidity_RegionA__9->GetYaxis()->SetTitleFont(42);
   diMuonF_Rapidity_RegionA__9->GetZaxis()->SetLabelFont(42);
   diMuonF_Rapidity_RegionA__9->GetZaxis()->SetLabelSize(0.035);
   diMuonF_Rapidity_RegionA__9->GetZaxis()->SetTitleSize(0.035);
   diMuonF_Rapidity_RegionA__9->GetZaxis()->SetTitleFont(42);
   diMuonF_Rapidity_RegionA__9->Draw("");
   TText *text = new TText(0.18,0.85,"CMS Simulation");
   text->SetNDC();
   text->Draw();
   c22222->Modified();
   c22222->cd();
   c22222->SetSelected(c22222);
}
