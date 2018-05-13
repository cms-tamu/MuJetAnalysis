void diMuonF_Rapidity_regionC_D()
{
//=========Macro generated from canvas: c22224/c22224
//=========  (Tue Feb 27 16:39:14 2018) by ROOT version6.06/01
   TCanvas *c22224 = new TCanvas("c22224", "c22224",0,0,700,500);
   c22224->Range(-0.7125,-1.3125,3.4125,11.8125);
   c22224->SetFillColor(0);
   c22224->SetBorderMode(0);
   c22224->SetBorderSize(2);
   c22224->SetFrameBorderMode(0);
   c22224->SetFrameBorderMode(0);
   
   TH1F *diMuonF_Rapidity_RegionC__11 = new TH1F("diMuonF_Rapidity_RegionC__11","",50,-0.3,3);
   diMuonF_Rapidity_RegionC__11->SetBinContent(0,139);
   diMuonF_Rapidity_RegionC__11->SetBinContent(1,4);
   diMuonF_Rapidity_RegionC__11->SetBinContent(2,6);
   diMuonF_Rapidity_RegionC__11->SetBinContent(3,8);
   diMuonF_Rapidity_RegionC__11->SetBinContent(4,9);
   diMuonF_Rapidity_RegionC__11->SetBinContent(5,6);
   diMuonF_Rapidity_RegionC__11->SetBinContent(6,7);
   diMuonF_Rapidity_RegionC__11->SetBinContent(7,3);
   diMuonF_Rapidity_RegionC__11->SetBinContent(8,4);
   diMuonF_Rapidity_RegionC__11->SetBinContent(9,6);
   diMuonF_Rapidity_RegionC__11->SetBinContent(10,8);
   diMuonF_Rapidity_RegionC__11->SetBinContent(11,3);
   diMuonF_Rapidity_RegionC__11->SetBinContent(12,4);
   diMuonF_Rapidity_RegionC__11->SetBinContent(13,8);
   diMuonF_Rapidity_RegionC__11->SetBinContent(14,4);
   diMuonF_Rapidity_RegionC__11->SetBinContent(15,9);
   diMuonF_Rapidity_RegionC__11->SetBinContent(16,6);
   diMuonF_Rapidity_RegionC__11->SetBinContent(17,8);
   diMuonF_Rapidity_RegionC__11->SetBinContent(18,6);
   diMuonF_Rapidity_RegionC__11->SetBinContent(19,6);
   diMuonF_Rapidity_RegionC__11->SetBinContent(20,4);
   diMuonF_Rapidity_RegionC__11->SetBinContent(21,4);
   diMuonF_Rapidity_RegionC__11->SetBinContent(22,9);
   diMuonF_Rapidity_RegionC__11->SetBinContent(23,7);
   diMuonF_Rapidity_RegionC__11->SetBinContent(24,5);
   diMuonF_Rapidity_RegionC__11->SetBinContent(25,10);
   diMuonF_Rapidity_RegionC__11->SetBinContent(26,6);
   diMuonF_Rapidity_RegionC__11->SetBinContent(27,3);
   diMuonF_Rapidity_RegionC__11->SetBinContent(28,3);
   diMuonF_Rapidity_RegionC__11->SetBinContent(29,5);
   diMuonF_Rapidity_RegionC__11->SetBinContent(30,2);
   diMuonF_Rapidity_RegionC__11->SetBinContent(31,1);
   diMuonF_Rapidity_RegionC__11->SetBinContent(32,2);
   diMuonF_Rapidity_RegionC__11->SetBinContent(33,2);
   diMuonF_Rapidity_RegionC__11->SetBinContent(34,3);
   diMuonF_Rapidity_RegionC__11->SetBinContent(35,1);
   diMuonF_Rapidity_RegionC__11->SetBinContent(36,2);
   diMuonF_Rapidity_RegionC__11->SetBinContent(39,3);
   diMuonF_Rapidity_RegionC__11->SetBinContent(40,1);
   diMuonF_Rapidity_RegionC__11->SetEntries(327);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *AText = ptstats->AddText("diMuonF_Rapidity_RegionC");
   AText->SetTextSize(0.0368);
   AText = ptstats->AddText("Entries = 327    ");
   AText = ptstats->AddText("Mean  = 0.7565");
   AText = ptstats->AddText("Std Dev   = 0.6404");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   diMuonF_Rapidity_RegionC__11->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(diMuonF_Rapidity_RegionC__11);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   diMuonF_Rapidity_RegionC__11->SetLineColor(ci);
   diMuonF_Rapidity_RegionC__11->GetXaxis()->SetTitle("Rapidity_{di-#mu_{2}}");
   diMuonF_Rapidity_RegionC__11->GetXaxis()->SetLabelFont(42);
   diMuonF_Rapidity_RegionC__11->GetXaxis()->SetLabelSize(0.035);
   diMuonF_Rapidity_RegionC__11->GetXaxis()->SetTitleSize(0.035);
   diMuonF_Rapidity_RegionC__11->GetXaxis()->SetTitleFont(42);
   diMuonF_Rapidity_RegionC__11->GetYaxis()->SetLabelFont(42);
   diMuonF_Rapidity_RegionC__11->GetYaxis()->SetLabelSize(0.035);
   diMuonF_Rapidity_RegionC__11->GetYaxis()->SetTitleSize(0.035);
   diMuonF_Rapidity_RegionC__11->GetYaxis()->SetTitleFont(42);
   diMuonF_Rapidity_RegionC__11->GetZaxis()->SetLabelFont(42);
   diMuonF_Rapidity_RegionC__11->GetZaxis()->SetLabelSize(0.035);
   diMuonF_Rapidity_RegionC__11->GetZaxis()->SetTitleSize(0.035);
   diMuonF_Rapidity_RegionC__11->GetZaxis()->SetTitleFont(42);
   diMuonF_Rapidity_RegionC__11->Draw("");
   TText *text = new TText(0.18,0.85,"CMS Simulation");
   text->SetNDC();
   text->Draw();
   c22224->Modified();
   c22224->cd();
   c22224->SetSelected(c22224);
}
