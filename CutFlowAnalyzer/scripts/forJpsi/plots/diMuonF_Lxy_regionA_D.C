void diMuonF_Lxy_regionA_D()
{
//=========Macro generated from canvas: c2222/c2222
//=========  (Tue Feb 27 16:39:13 2018) by ROOT version6.06/01
   TCanvas *c2222 = new TCanvas("c2222", "c2222",0,0,700,500);
   c2222->Range(-0.35,-3.54375,1.15,31.89375);
   c2222->SetFillColor(0);
   c2222->SetBorderMode(0);
   c2222->SetBorderSize(2);
   c2222->SetFrameBorderMode(0);
   c2222->SetFrameBorderMode(0);
   
   TH1F *diMuonF_Lxy_RegionA__5 = new TH1F("diMuonF_Lxy_RegionA__5","",50,-0.2,1);
   diMuonF_Lxy_RegionA__5->SetBinContent(7,1);
   diMuonF_Lxy_RegionA__5->SetBinContent(8,9);
   diMuonF_Lxy_RegionA__5->SetBinContent(9,27);
   diMuonF_Lxy_RegionA__5->SetBinContent(10,12);
   diMuonF_Lxy_RegionA__5->SetBinContent(11,9);
   diMuonF_Lxy_RegionA__5->SetBinContent(12,9);
   diMuonF_Lxy_RegionA__5->SetBinContent(13,7);
   diMuonF_Lxy_RegionA__5->SetBinContent(14,9);
   diMuonF_Lxy_RegionA__5->SetBinContent(15,4);
   diMuonF_Lxy_RegionA__5->SetBinContent(16,3);
   diMuonF_Lxy_RegionA__5->SetBinContent(17,3);
   diMuonF_Lxy_RegionA__5->SetBinContent(18,4);
   diMuonF_Lxy_RegionA__5->SetBinContent(19,1);
   diMuonF_Lxy_RegionA__5->SetBinContent(20,2);
   diMuonF_Lxy_RegionA__5->SetBinContent(21,1);
   diMuonF_Lxy_RegionA__5->SetBinContent(22,1);
   diMuonF_Lxy_RegionA__5->SetBinContent(23,2);
   diMuonF_Lxy_RegionA__5->SetBinContent(24,4);
   diMuonF_Lxy_RegionA__5->SetBinContent(25,3);
   diMuonF_Lxy_RegionA__5->SetBinContent(26,1);
   diMuonF_Lxy_RegionA__5->SetBinContent(27,2);
   diMuonF_Lxy_RegionA__5->SetBinContent(28,1);
   diMuonF_Lxy_RegionA__5->SetBinContent(29,1);
   diMuonF_Lxy_RegionA__5->SetBinContent(32,1);
   diMuonF_Lxy_RegionA__5->SetBinContent(34,1);
   diMuonF_Lxy_RegionA__5->SetEntries(118);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *AText = ptstats->AddText("diMuonF_Lxy_RegionA");
   AText->SetTextSize(0.0368);
   AText = ptstats->AddText("Entries = 118    ");
   AText = ptstats->AddText("Mean  = 0.1163");
   AText = ptstats->AddText("Std Dev   = 0.1436");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   diMuonF_Lxy_RegionA__5->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(diMuonF_Lxy_RegionA__5);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   diMuonF_Lxy_RegionA__5->SetLineColor(ci);
   diMuonF_Lxy_RegionA__5->GetXaxis()->SetTitle("Lxy_{di-#mu_{2}} [cm]");
   diMuonF_Lxy_RegionA__5->GetXaxis()->SetLabelFont(42);
   diMuonF_Lxy_RegionA__5->GetXaxis()->SetLabelSize(0.035);
   diMuonF_Lxy_RegionA__5->GetXaxis()->SetTitleSize(0.035);
   diMuonF_Lxy_RegionA__5->GetXaxis()->SetTitleFont(42);
   diMuonF_Lxy_RegionA__5->GetYaxis()->SetLabelFont(42);
   diMuonF_Lxy_RegionA__5->GetYaxis()->SetLabelSize(0.035);
   diMuonF_Lxy_RegionA__5->GetYaxis()->SetTitleSize(0.035);
   diMuonF_Lxy_RegionA__5->GetYaxis()->SetTitleFont(42);
   diMuonF_Lxy_RegionA__5->GetZaxis()->SetLabelFont(42);
   diMuonF_Lxy_RegionA__5->GetZaxis()->SetLabelSize(0.035);
   diMuonF_Lxy_RegionA__5->GetZaxis()->SetTitleSize(0.035);
   diMuonF_Lxy_RegionA__5->GetZaxis()->SetTitleFont(42);
   diMuonF_Lxy_RegionA__5->Draw("");
   TText *text = new TText(0.18,0.85,"CMS Simulation");
   text->SetNDC();
   text->Draw();
   c2222->Modified();
   c2222->cd();
   c2222->SetSelected(c2222);
}
