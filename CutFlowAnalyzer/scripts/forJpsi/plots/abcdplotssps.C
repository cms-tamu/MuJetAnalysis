void abcdplotssps(){

  TFile *f = new TFile("savehist_SPS.root");


  TH2F *iso;

  iso = (TH2F*)f->Get("Iso_dim1_vs_dim2_aftmasscut");

  iso->SetTitle("CMS");
  iso->SetContour(100);
  
  iso->SetTitle("#scale[1.4]{#font[61]{CMS}}                35.9 fb^{-1} (13 TeV)  ");
  iso->SetTitle("#scale[1.4]{#font[61]{CMS}}#font[52]{Simulation}                13 TeV  ");
  iso->GetXaxis()->SetRangeUser(0.001, 12.);
  iso->GetYaxis()->SetRangeUser(0.001, 12.);
  iso->GetXaxis()->SetLimits(0.001,12.);
  iso->GetYaxis()->SetLimits(0.001,12.);

  cout << iso->Integral(0,20,0,20) << endl;;
  cout << iso->Integral(0,20,21,120) << endl;;
  cout << iso->Integral(21,120,21,120) << endl;;
  cout << iso->Integral(21,120,0,20) << endl;;
  
  TLine *line = new TLine(0,2,12,2);
  TLine *line2 = new TLine(2,0,2,12);
  
  line->SetNDC();
  line2->SetNDC(2);

  line->SetLineStyle(2);
  line2->SetLineStyle(2);
  line->SetLineWidth(3);
  line2->SetLineWidth(3);
  int mycolor = kRed+1;
  line->SetLineColor(mycolor);
  line2->SetLineColor(mycolor);
  
  TText *t2 = new TText(0.2,0.2,"A");
  t2->SetNDC();
  t2->SetTextSize(0.05);
  t2->SetTextColor(mycolor);
  
  TText *t3 = new TText(0.2,0.43,"B");
  t3->SetNDC();
  t3->SetTextSize(0.05);
  t3->SetTextColor(mycolor);
  
  
  TText *t4 = new TText(0.45,0.43,"C");
  t4->SetNDC();
  t4->SetTextSize(0.05);
  t4->SetTextColor(mycolor);
  
  TText *t5 = new TText(0.45,0.2,"D");
  t5->SetNDC();
  t5->SetTextSize(0.05);
  t5->SetTextColor(mycolor);
  
  TCanvas *c = new TCanvas("","",600,600);
  
  gStyle->SetOptFit(1);
  gStyle->SetOptStat(0);
   // gStyle->SetOptTitle(0);
  gPad->SetLogz();
  // gPad->SetLogx();
  // gPad->SetLogy();
  c->Range(-2.686567,-2.684211,15.22388,13.10526);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(2);
  c->SetTickx(1);
  c->SetTicky(1);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.18);
  c->SetTopMargin(0.07);
   c->SetBottomMargin(0.17);
   c->SetFrameFillStyle(0);
   c->SetFrameBorderMode(0);
   c->SetFrameFillStyle(0);
   c->SetFrameBorderMode(0);
   
   gStyle->SetTitleFontSize(0.07);
   
   gStyle->SetTitleStyle( 0 );
   gStyle->SetTitleAlign(13);
   gStyle->SetTitleX(0.);
   gStyle->SetTitleY(1.);
   gStyle->SetTitleW(1);
   gStyle->SetTitleH(0.058);
   gStyle->SetTitleBorderSize( 0 );
   gStyle->SetPalette(55);


  iso->Draw("COLZ");
  line->Draw("same");
  line2->Draw("same");
  t2->Draw("same");
  t3->Draw("same");
  t4->Draw("same");
  t5->Draw("same");
  c->SaveAs("Iso_dim1_vs_dim2_aftmasscutSPSWlines_thesisSvenDildick.pdf","recreate");
}
