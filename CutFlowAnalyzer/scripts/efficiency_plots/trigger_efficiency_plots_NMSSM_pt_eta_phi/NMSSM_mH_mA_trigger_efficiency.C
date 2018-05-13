void NMSSM_mH_mA_trigger_efficiency()
{
//=========Macro generated from canvas: c/c
//=========  (Thu Jun  8 04:34:37 2017) by ROOT version6.06/01
   TCanvas *c = new TCanvas("c", "c",0,0,800,600);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c->Range(0.2446043,0.03703708,6.239808,7.444444);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetTickx(1);
   c->SetTicky(1);
   c->SetLeftMargin(0.126);
   c->SetRightMargin(0.04);
   c->SetTopMargin(0.06);
   c->SetBottomMargin(0.13);
   c->SetFrameFillStyle(0);
   c->SetFrameBorderMode(0);
   c->SetFrameFillStyle(0);
   c->SetFrameBorderMode(0);
   
   TH2F *unnamed = new TH2F("unnamed","           #scale[1.4]{#font[61]{CMS}} #font[52]{Simulation preliminary}                                                           13 TeV",5,1,6,6,1,7);
   unnamed->SetBinContent(32,0.9559945);
   unnamed->SetMinimum(0.9);
   unnamed->SetMaximum(1);
   unnamed->SetEntries(1);
   unnamed->SetContour(20);
   unnamed->SetContourLevel(0,0.9);
   unnamed->SetContourLevel(1,0.905);
   unnamed->SetContourLevel(2,0.91);
   unnamed->SetContourLevel(3,0.915);
   unnamed->SetContourLevel(4,0.92);
   unnamed->SetContourLevel(5,0.925);
   unnamed->SetContourLevel(6,0.93);
   unnamed->SetContourLevel(7,0.935);
   unnamed->SetContourLevel(8,0.94);
   unnamed->SetContourLevel(9,0.945);
   unnamed->SetContourLevel(10,0.95);
   unnamed->SetContourLevel(11,0.955);
   unnamed->SetContourLevel(12,0.96);
   unnamed->SetContourLevel(13,0.965);
   unnamed->SetContourLevel(14,0.97);
   unnamed->SetContourLevel(15,0.975);
   unnamed->SetContourLevel(16,0.98);
   unnamed->SetContourLevel(17,0.985);
   unnamed->SetContourLevel(18,0.99);
   unnamed->SetContourLevel(19,0.995);
   
   TPaletteAxis *palette = new TPaletteAxis(6.029976,1,6.236811,7,);
palette->SetLabelColor(1);
palette->SetLabelFont(42);
palette->SetLabelOffset(0.007);
palette->SetLabelSize(0.05);
palette->SetTitleOffset(1);
palette->SetTitleSize(0.06);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#700002");
   palette->SetFillColor(ci);
   palette->SetFillStyle(1001);
   unnamed->GetListOfFunctions()->Add(palette,"br");
   unnamed->SetFillStyle(0);
   unnamed->SetLineStyle(0);
   unnamed->GetXaxis()->SetTitle("m_{h} [Gev]");
   unnamed->GetXaxis()->SetBinLabel(4,"125");
   unnamed->GetXaxis()->SetLabelFont(42);
   unnamed->GetXaxis()->SetLabelOffset(0.007);
   unnamed->GetXaxis()->SetLabelSize(0.05);
   unnamed->GetXaxis()->SetTitleSize(0.05);
   unnamed->GetXaxis()->SetTitleOffset(1.2);
   unnamed->GetXaxis()->SetTitleFont(42);
   unnamed->GetYaxis()->SetTitle("m_{a_{1}} [GeV]");
   unnamed->GetYaxis()->SetBinLabel(4,"2.0");
   unnamed->GetYaxis()->SetLabelFont(42);
   unnamed->GetYaxis()->SetLabelOffset(0.007);
   unnamed->GetYaxis()->SetLabelSize(0.05);
   unnamed->GetYaxis()->SetTitleSize(0.05);
   unnamed->GetYaxis()->SetTitleOffset(1.2);
   unnamed->GetYaxis()->SetTitleFont(42);
   unnamed->GetZaxis()->SetLabelFont(42);
   unnamed->GetZaxis()->SetLabelOffset(0.007);
   unnamed->GetZaxis()->SetLabelSize(0.05);
   unnamed->GetZaxis()->SetTitleSize(0.06);
   unnamed->GetZaxis()->SetTitleFont(42);
   unnamed->Draw("COLZ TEXT");
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
