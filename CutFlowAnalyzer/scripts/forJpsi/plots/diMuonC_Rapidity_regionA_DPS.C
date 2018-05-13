void diMuonC_Rapidity_regionA_DPS()
{
//=========Macro generated from canvas: c22221/c22221
//=========  (Tue Feb 27 16:25:31 2018) by ROOT version6.06/01
   TCanvas *c22221 = new TCanvas("c22221", "c22221",0,0,700,500);
   c22221->Range(-0.7125,-0.7875001,3.4125,7.0875);
   c22221->SetFillColor(0);
   c22221->SetBorderMode(0);
   c22221->SetBorderSize(2);
   c22221->SetFrameBorderMode(0);
   c22221->SetFrameBorderMode(0);
   
   TH1F *diMuonC_Rapidity_RegionA__8 = new TH1F("diMuonC_Rapidity_RegionA__8","",50,-0.3,3);
   diMuonC_Rapidity_RegionA__8->SetBinContent(0,46);
   diMuonC_Rapidity_RegionA__8->SetBinContent(1,2);
   diMuonC_Rapidity_RegionA__8->SetBinContent(2,2);
   diMuonC_Rapidity_RegionA__8->SetBinContent(3,1);
   diMuonC_Rapidity_RegionA__8->SetBinContent(4,2);
   diMuonC_Rapidity_RegionA__8->SetBinContent(5,1);
   diMuonC_Rapidity_RegionA__8->SetBinContent(7,3);
   diMuonC_Rapidity_RegionA__8->SetBinContent(8,1);
   diMuonC_Rapidity_RegionA__8->SetBinContent(9,2);
   diMuonC_Rapidity_RegionA__8->SetBinContent(11,1);
   diMuonC_Rapidity_RegionA__8->SetBinContent(12,3);
   diMuonC_Rapidity_RegionA__8->SetBinContent(13,1);
   diMuonC_Rapidity_RegionA__8->SetBinContent(14,1);
   diMuonC_Rapidity_RegionA__8->SetBinContent(15,2);
   diMuonC_Rapidity_RegionA__8->SetBinContent(16,6);
   diMuonC_Rapidity_RegionA__8->SetBinContent(17,1);
   diMuonC_Rapidity_RegionA__8->SetBinContent(18,1);
   diMuonC_Rapidity_RegionA__8->SetBinContent(20,2);
   diMuonC_Rapidity_RegionA__8->SetBinContent(21,5);
   diMuonC_Rapidity_RegionA__8->SetBinContent(22,6);
   diMuonC_Rapidity_RegionA__8->SetBinContent(23,2);
   diMuonC_Rapidity_RegionA__8->SetBinContent(24,2);
   diMuonC_Rapidity_RegionA__8->SetBinContent(26,2);
   diMuonC_Rapidity_RegionA__8->SetBinContent(27,4);
   diMuonC_Rapidity_RegionA__8->SetBinContent(29,6);
   diMuonC_Rapidity_RegionA__8->SetBinContent(30,3);
   diMuonC_Rapidity_RegionA__8->SetBinContent(32,1);
   diMuonC_Rapidity_RegionA__8->SetBinContent(33,2);
   diMuonC_Rapidity_RegionA__8->SetBinContent(34,1);
   diMuonC_Rapidity_RegionA__8->SetBinContent(35,2);
   diMuonC_Rapidity_RegionA__8->SetBinContent(37,1);
   diMuonC_Rapidity_RegionA__8->SetBinContent(38,1);
   diMuonC_Rapidity_RegionA__8->SetBinContent(40,2);
   diMuonC_Rapidity_RegionA__8->SetEntries(118);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *AText = ptstats->AddText("diMuonC_Rapidity_RegionA");
   AText->SetTextSize(0.0368);
   AText = ptstats->AddText("Entries = 118    ");
   AText = ptstats->AddText("Mean  =      1");
   AText = ptstats->AddText("Std Dev   = 0.6701");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   diMuonC_Rapidity_RegionA__8->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(diMuonC_Rapidity_RegionA__8);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   diMuonC_Rapidity_RegionA__8->SetLineColor(ci);
   diMuonC_Rapidity_RegionA__8->GetXaxis()->SetTitle("Rapidity_{di-#mu_{1}}");
   diMuonC_Rapidity_RegionA__8->GetXaxis()->SetLabelFont(42);
   diMuonC_Rapidity_RegionA__8->GetXaxis()->SetLabelSize(0.035);
   diMuonC_Rapidity_RegionA__8->GetXaxis()->SetTitleSize(0.035);
   diMuonC_Rapidity_RegionA__8->GetXaxis()->SetTitleFont(42);
   diMuonC_Rapidity_RegionA__8->GetYaxis()->SetLabelFont(42);
   diMuonC_Rapidity_RegionA__8->GetYaxis()->SetLabelSize(0.035);
   diMuonC_Rapidity_RegionA__8->GetYaxis()->SetTitleSize(0.035);
   diMuonC_Rapidity_RegionA__8->GetYaxis()->SetTitleFont(42);
   diMuonC_Rapidity_RegionA__8->GetZaxis()->SetLabelFont(42);
   diMuonC_Rapidity_RegionA__8->GetZaxis()->SetLabelSize(0.035);
   diMuonC_Rapidity_RegionA__8->GetZaxis()->SetTitleSize(0.035);
   diMuonC_Rapidity_RegionA__8->GetZaxis()->SetTitleFont(42);
   diMuonC_Rapidity_RegionA__8->Draw("");
   TText *text = new TText(0.18,0.85,"CMS Simulation");
   text->SetNDC();
   text->Draw();
   c22221->Modified();
   c22221->cd();
   c22221->SetSelected(c22221);
}
