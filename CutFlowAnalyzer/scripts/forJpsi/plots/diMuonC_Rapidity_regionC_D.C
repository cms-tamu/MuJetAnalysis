void diMuonC_Rapidity_regionC_D()
{
//=========Macro generated from canvas: c22223/c22223
//=========  (Tue Feb 27 16:39:14 2018) by ROOT version6.06/01
   TCanvas *c22223 = new TCanvas("c22223", "c22223",0,0,700,500);
   c22223->Range(-0.7125,-1.3125,3.4125,11.8125);
   c22223->SetFillColor(0);
   c22223->SetBorderMode(0);
   c22223->SetBorderSize(2);
   c22223->SetFrameBorderMode(0);
   c22223->SetFrameBorderMode(0);
   
   TH1F *diMuonC_Rapidity_RegionC__10 = new TH1F("diMuonC_Rapidity_RegionC__10","",50,-0.3,3);
   diMuonC_Rapidity_RegionC__10->SetBinContent(0,141);
   diMuonC_Rapidity_RegionC__10->SetBinContent(1,6);
   diMuonC_Rapidity_RegionC__10->SetBinContent(2,3);
   diMuonC_Rapidity_RegionC__10->SetBinContent(3,5);
   diMuonC_Rapidity_RegionC__10->SetBinContent(4,6);
   diMuonC_Rapidity_RegionC__10->SetBinContent(5,3);
   diMuonC_Rapidity_RegionC__10->SetBinContent(6,10);
   diMuonC_Rapidity_RegionC__10->SetBinContent(7,8);
   diMuonC_Rapidity_RegionC__10->SetBinContent(8,5);
   diMuonC_Rapidity_RegionC__10->SetBinContent(9,4);
   diMuonC_Rapidity_RegionC__10->SetBinContent(10,6);
   diMuonC_Rapidity_RegionC__10->SetBinContent(11,4);
   diMuonC_Rapidity_RegionC__10->SetBinContent(12,9);
   diMuonC_Rapidity_RegionC__10->SetBinContent(13,5);
   diMuonC_Rapidity_RegionC__10->SetBinContent(14,5);
   diMuonC_Rapidity_RegionC__10->SetBinContent(15,4);
   diMuonC_Rapidity_RegionC__10->SetBinContent(16,6);
   diMuonC_Rapidity_RegionC__10->SetBinContent(17,2);
   diMuonC_Rapidity_RegionC__10->SetBinContent(18,8);
   diMuonC_Rapidity_RegionC__10->SetBinContent(19,9);
   diMuonC_Rapidity_RegionC__10->SetBinContent(20,5);
   diMuonC_Rapidity_RegionC__10->SetBinContent(21,5);
   diMuonC_Rapidity_RegionC__10->SetBinContent(22,6);
   diMuonC_Rapidity_RegionC__10->SetBinContent(23,4);
   diMuonC_Rapidity_RegionC__10->SetBinContent(24,6);
   diMuonC_Rapidity_RegionC__10->SetBinContent(25,6);
   diMuonC_Rapidity_RegionC__10->SetBinContent(26,4);
   diMuonC_Rapidity_RegionC__10->SetBinContent(27,9);
   diMuonC_Rapidity_RegionC__10->SetBinContent(28,5);
   diMuonC_Rapidity_RegionC__10->SetBinContent(29,1);
   diMuonC_Rapidity_RegionC__10->SetBinContent(30,1);
   diMuonC_Rapidity_RegionC__10->SetBinContent(31,5);
   diMuonC_Rapidity_RegionC__10->SetBinContent(32,4);
   diMuonC_Rapidity_RegionC__10->SetBinContent(33,3);
   diMuonC_Rapidity_RegionC__10->SetBinContent(34,8);
   diMuonC_Rapidity_RegionC__10->SetBinContent(35,1);
   diMuonC_Rapidity_RegionC__10->SetBinContent(36,2);
   diMuonC_Rapidity_RegionC__10->SetBinContent(38,2);
   diMuonC_Rapidity_RegionC__10->SetBinContent(39,1);
   diMuonC_Rapidity_RegionC__10->SetEntries(327);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *AText = ptstats->AddText("diMuonC_Rapidity_RegionC");
   AText->SetTextSize(0.0368);
   AText = ptstats->AddText("Entries = 327    ");
   AText = ptstats->AddText("Mean  = 0.8205");
   AText = ptstats->AddText("Std Dev   = 0.6631");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   diMuonC_Rapidity_RegionC__10->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(diMuonC_Rapidity_RegionC__10);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   diMuonC_Rapidity_RegionC__10->SetLineColor(ci);
   diMuonC_Rapidity_RegionC__10->GetXaxis()->SetTitle("Rapidity_{di-#mu_{1}}");
   diMuonC_Rapidity_RegionC__10->GetXaxis()->SetLabelFont(42);
   diMuonC_Rapidity_RegionC__10->GetXaxis()->SetLabelSize(0.035);
   diMuonC_Rapidity_RegionC__10->GetXaxis()->SetTitleSize(0.035);
   diMuonC_Rapidity_RegionC__10->GetXaxis()->SetTitleFont(42);
   diMuonC_Rapidity_RegionC__10->GetYaxis()->SetLabelFont(42);
   diMuonC_Rapidity_RegionC__10->GetYaxis()->SetLabelSize(0.035);
   diMuonC_Rapidity_RegionC__10->GetYaxis()->SetTitleSize(0.035);
   diMuonC_Rapidity_RegionC__10->GetYaxis()->SetTitleFont(42);
   diMuonC_Rapidity_RegionC__10->GetZaxis()->SetLabelFont(42);
   diMuonC_Rapidity_RegionC__10->GetZaxis()->SetLabelSize(0.035);
   diMuonC_Rapidity_RegionC__10->GetZaxis()->SetTitleSize(0.035);
   diMuonC_Rapidity_RegionC__10->GetZaxis()->SetTitleFont(42);
   diMuonC_Rapidity_RegionC__10->Draw("");
   TText *text = new TText(0.18,0.85,"CMS Simulation");
   text->SetNDC();
   text->Draw();
   c22223->Modified();
   c22223->cd();
   c22223->SetSelected(c22223);
}
