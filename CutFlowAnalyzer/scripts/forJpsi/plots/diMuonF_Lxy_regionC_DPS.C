void diMuonF_Lxy_regionC_DPS()
{
//=========Macro generated from canvas: c2224/c2224
//=========  (Tue Feb 27 16:25:31 2018) by ROOT version6.06/01
   TCanvas *c2224 = new TCanvas("c2224", "c2224",0,0,700,500);
   c2224->Range(-0.35,-5.38125,1.15,48.43125);
   c2224->SetFillColor(0);
   c2224->SetBorderMode(0);
   c2224->SetBorderSize(2);
   c2224->SetFrameBorderMode(0);
   c2224->SetFrameBorderMode(0);
   
   TH1F *diMuonF_Lxy_RegionC__7 = new TH1F("diMuonF_Lxy_RegionC__7","",50,-0.2,1);
   diMuonF_Lxy_RegionC__7->SetBinContent(7,2);
   diMuonF_Lxy_RegionC__7->SetBinContent(8,11);
   diMuonF_Lxy_RegionC__7->SetBinContent(9,41);
   diMuonF_Lxy_RegionC__7->SetBinContent(10,28);
   diMuonF_Lxy_RegionC__7->SetBinContent(11,32);
   diMuonF_Lxy_RegionC__7->SetBinContent(12,20);
   diMuonF_Lxy_RegionC__7->SetBinContent(13,14);
   diMuonF_Lxy_RegionC__7->SetBinContent(14,14);
   diMuonF_Lxy_RegionC__7->SetBinContent(15,16);
   diMuonF_Lxy_RegionC__7->SetBinContent(16,13);
   diMuonF_Lxy_RegionC__7->SetBinContent(17,12);
   diMuonF_Lxy_RegionC__7->SetBinContent(18,13);
   diMuonF_Lxy_RegionC__7->SetBinContent(19,8);
   diMuonF_Lxy_RegionC__7->SetBinContent(20,8);
   diMuonF_Lxy_RegionC__7->SetBinContent(21,16);
   diMuonF_Lxy_RegionC__7->SetBinContent(22,4);
   diMuonF_Lxy_RegionC__7->SetBinContent(23,5);
   diMuonF_Lxy_RegionC__7->SetBinContent(24,4);
   diMuonF_Lxy_RegionC__7->SetBinContent(25,4);
   diMuonF_Lxy_RegionC__7->SetBinContent(26,4);
   diMuonF_Lxy_RegionC__7->SetBinContent(27,4);
   diMuonF_Lxy_RegionC__7->SetBinContent(28,7);
   diMuonF_Lxy_RegionC__7->SetBinContent(29,2);
   diMuonF_Lxy_RegionC__7->SetBinContent(30,2);
   diMuonF_Lxy_RegionC__7->SetBinContent(31,2);
   diMuonF_Lxy_RegionC__7->SetBinContent(32,1);
   diMuonF_Lxy_RegionC__7->SetBinContent(33,1);
   diMuonF_Lxy_RegionC__7->SetBinContent(34,3);
   diMuonF_Lxy_RegionC__7->SetBinContent(35,1);
   diMuonF_Lxy_RegionC__7->SetBinContent(36,2);
   diMuonF_Lxy_RegionC__7->SetBinContent(37,3);
   diMuonF_Lxy_RegionC__7->SetBinContent(39,4);
   diMuonF_Lxy_RegionC__7->SetBinContent(40,2);
   diMuonF_Lxy_RegionC__7->SetBinContent(41,1);
   diMuonF_Lxy_RegionC__7->SetBinContent(42,2);
   diMuonF_Lxy_RegionC__7->SetBinContent(44,3);
   diMuonF_Lxy_RegionC__7->SetBinContent(45,1);
   diMuonF_Lxy_RegionC__7->SetBinContent(46,3);
   diMuonF_Lxy_RegionC__7->SetBinContent(47,1);
   diMuonF_Lxy_RegionC__7->SetBinContent(48,3);
   diMuonF_Lxy_RegionC__7->SetBinContent(51,10);
   diMuonF_Lxy_RegionC__7->SetEntries(327);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *AText = ptstats->AddText("diMuonF_Lxy_RegionC");
   AText->SetTextSize(0.0368);
   AText = ptstats->AddText("Entries = 327    ");
   AText = ptstats->AddText("Mean  = 0.2036");
   AText = ptstats->AddText("Std Dev   = 0.2272");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   diMuonF_Lxy_RegionC__7->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(diMuonF_Lxy_RegionC__7);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   diMuonF_Lxy_RegionC__7->SetLineColor(ci);
   diMuonF_Lxy_RegionC__7->GetXaxis()->SetTitle("Lxy_{di-#mu_{2}} [cm]");
   diMuonF_Lxy_RegionC__7->GetXaxis()->SetLabelFont(42);
   diMuonF_Lxy_RegionC__7->GetXaxis()->SetLabelSize(0.035);
   diMuonF_Lxy_RegionC__7->GetXaxis()->SetTitleSize(0.035);
   diMuonF_Lxy_RegionC__7->GetXaxis()->SetTitleFont(42);
   diMuonF_Lxy_RegionC__7->GetYaxis()->SetLabelFont(42);
   diMuonF_Lxy_RegionC__7->GetYaxis()->SetLabelSize(0.035);
   diMuonF_Lxy_RegionC__7->GetYaxis()->SetTitleSize(0.035);
   diMuonF_Lxy_RegionC__7->GetYaxis()->SetTitleFont(42);
   diMuonF_Lxy_RegionC__7->GetZaxis()->SetLabelFont(42);
   diMuonF_Lxy_RegionC__7->GetZaxis()->SetLabelSize(0.035);
   diMuonF_Lxy_RegionC__7->GetZaxis()->SetTitleSize(0.035);
   diMuonF_Lxy_RegionC__7->GetZaxis()->SetTitleFont(42);
   diMuonF_Lxy_RegionC__7->Draw("");
   TText *text = new TText(0.18,0.85,"CMS Simulation");
   text->SetNDC();
   text->Draw();
   c2224->Modified();
   c2224->cd();
   c2224->SetSelected(c2224);
}
