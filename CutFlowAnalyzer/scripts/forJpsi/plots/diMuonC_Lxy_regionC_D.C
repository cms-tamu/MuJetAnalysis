void diMuonC_Lxy_regionC_D()
{
//=========Macro generated from canvas: c2223/c2223
//=========  (Tue Feb 27 16:39:13 2018) by ROOT version6.06/01
   TCanvas *c2223 = new TCanvas("c2223", "c2223",0,0,700,500);
   c2223->Range(-0.35,-4.725,1.15,42.525);
   c2223->SetFillColor(0);
   c2223->SetBorderMode(0);
   c2223->SetBorderSize(2);
   c2223->SetFrameBorderMode(0);
   c2223->SetFrameBorderMode(0);
   
   TH1F *diMuonC_Lxy_RegionC__6 = new TH1F("diMuonC_Lxy_RegionC__6","",50,-0.2,1);
   diMuonC_Lxy_RegionC__6->SetBinContent(6,1);
   diMuonC_Lxy_RegionC__6->SetBinContent(8,13);
   diMuonC_Lxy_RegionC__6->SetBinContent(9,36);
   diMuonC_Lxy_RegionC__6->SetBinContent(10,26);
   diMuonC_Lxy_RegionC__6->SetBinContent(11,32);
   diMuonC_Lxy_RegionC__6->SetBinContent(12,25);
   diMuonC_Lxy_RegionC__6->SetBinContent(13,18);
   diMuonC_Lxy_RegionC__6->SetBinContent(14,20);
   diMuonC_Lxy_RegionC__6->SetBinContent(15,18);
   diMuonC_Lxy_RegionC__6->SetBinContent(16,13);
   diMuonC_Lxy_RegionC__6->SetBinContent(17,10);
   diMuonC_Lxy_RegionC__6->SetBinContent(18,17);
   diMuonC_Lxy_RegionC__6->SetBinContent(19,13);
   diMuonC_Lxy_RegionC__6->SetBinContent(20,10);
   diMuonC_Lxy_RegionC__6->SetBinContent(21,9);
   diMuonC_Lxy_RegionC__6->SetBinContent(22,8);
   diMuonC_Lxy_RegionC__6->SetBinContent(23,8);
   diMuonC_Lxy_RegionC__6->SetBinContent(24,7);
   diMuonC_Lxy_RegionC__6->SetBinContent(25,7);
   diMuonC_Lxy_RegionC__6->SetBinContent(26,1);
   diMuonC_Lxy_RegionC__6->SetBinContent(27,2);
   diMuonC_Lxy_RegionC__6->SetBinContent(28,3);
   diMuonC_Lxy_RegionC__6->SetBinContent(29,3);
   diMuonC_Lxy_RegionC__6->SetBinContent(30,2);
   diMuonC_Lxy_RegionC__6->SetBinContent(31,3);
   diMuonC_Lxy_RegionC__6->SetBinContent(32,1);
   diMuonC_Lxy_RegionC__6->SetBinContent(34,2);
   diMuonC_Lxy_RegionC__6->SetBinContent(35,3);
   diMuonC_Lxy_RegionC__6->SetBinContent(36,1);
   diMuonC_Lxy_RegionC__6->SetBinContent(37,1);
   diMuonC_Lxy_RegionC__6->SetBinContent(38,2);
   diMuonC_Lxy_RegionC__6->SetBinContent(39,1);
   diMuonC_Lxy_RegionC__6->SetBinContent(40,1);
   diMuonC_Lxy_RegionC__6->SetBinContent(45,1);
   diMuonC_Lxy_RegionC__6->SetBinContent(47,2);
   diMuonC_Lxy_RegionC__6->SetBinContent(48,1);
   diMuonC_Lxy_RegionC__6->SetBinContent(51,6);
   diMuonC_Lxy_RegionC__6->SetEntries(327);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *AText = ptstats->AddText("diMuonC_Lxy_RegionC");
   AText->SetTextSize(0.0368);
   AText = ptstats->AddText("Entries = 327    ");
   AText = ptstats->AddText("Mean  =  0.175");
   AText = ptstats->AddText("Std Dev   = 0.1814");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   diMuonC_Lxy_RegionC__6->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(diMuonC_Lxy_RegionC__6);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   diMuonC_Lxy_RegionC__6->SetLineColor(ci);
   diMuonC_Lxy_RegionC__6->GetXaxis()->SetTitle("Lxy_{di-#mu_{1}} [cm]");
   diMuonC_Lxy_RegionC__6->GetXaxis()->SetLabelFont(42);
   diMuonC_Lxy_RegionC__6->GetXaxis()->SetLabelSize(0.035);
   diMuonC_Lxy_RegionC__6->GetXaxis()->SetTitleSize(0.035);
   diMuonC_Lxy_RegionC__6->GetXaxis()->SetTitleFont(42);
   diMuonC_Lxy_RegionC__6->GetYaxis()->SetLabelFont(42);
   diMuonC_Lxy_RegionC__6->GetYaxis()->SetLabelSize(0.035);
   diMuonC_Lxy_RegionC__6->GetYaxis()->SetTitleSize(0.035);
   diMuonC_Lxy_RegionC__6->GetYaxis()->SetTitleFont(42);
   diMuonC_Lxy_RegionC__6->GetZaxis()->SetLabelFont(42);
   diMuonC_Lxy_RegionC__6->GetZaxis()->SetLabelSize(0.035);
   diMuonC_Lxy_RegionC__6->GetZaxis()->SetTitleSize(0.035);
   diMuonC_Lxy_RegionC__6->GetZaxis()->SetTitleFont(42);
   diMuonC_Lxy_RegionC__6->Draw("");
   TText *text = new TText(0.18,0.85,"CMS Simulation");
   text->SetNDC();
   text->Draw();
   c2223->Modified();
   c2223->cd();
   c2223->SetSelected(c2223);
}
