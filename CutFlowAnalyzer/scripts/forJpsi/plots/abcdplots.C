void abcdplots(){

  TFile *f = new TFile("savehist_all.root");

   gStyle->SetTitleFontSize(0.07);
   
   gStyle->SetTitleStyle( 0 );
   gStyle->SetTitleAlign(13);
   gStyle->SetTitleX(0.);
   gStyle->SetTitleY(1.);
   gStyle->SetTitleW(1);
   gStyle->SetTitleH(0.058);
   gStyle->SetTitleBorderSize( 0 );

   TH2F *Iso_dim1_vs_dim2_aftmasscut__3 = new TH2F("Iso_dim1_vs_dim2_aftmasscut__3","#scale[1.4]{#font[61]{CMS}}                35.9 fb^{-1} (13 TeV)  ",100,0,12,100,0,12);


  TH2F *iso;

  iso = (TH2F*)f->Get("Iso_dim1_vs_dim2_aftmasscut");
  iso->SetTitle()
  
  TLine *line = new TLine(0,2,12,2);
  TLine *line2 = new TLine(2,0,2,12);

  line->SetLineStyle(2);
  line2->SetLineStyle(2);
  line->SetLineWidth(3);
  line2->SetLineWidth(3);

  TText *t2 = new TText(0.2,0.2,"A");
  t2->SetNDC();
  t2->SetTextSize(0.045);
  t2->SetTextColor(3);

  TText *t3 = new TText(0.2,0.43,"B");
  t3->SetNDC();
  t3->SetTextSize(0.045);
  t3->SetTextColor(3);


  TText *t4 = new TText(0.45,0.43,"C");
  t4->SetNDC();
  t4->SetTextSize(0.045);
  t4->SetTextColor(3);

  TText *t5 = new TText(0.45,0.2,"D");
  t5->SetNDC();
  t5->SetTextSize(0.045);
  t5->SetTextColor(3);
  
  TCanvas *c = new TCanvas();
  c->SetRightMargin(0.18);
  iso->Draw("COLORZ");
  line->Draw("same");
  line2->Draw("same");
  t2->Draw("same");
  t3->Draw("same");
  t4->Draw("same");
  t5->Draw("same");
  c->SaveAs("Iso_dim1_vs_dim2_aftmasscutallWlines_thesisSvenDildick.pdf","recreate");



}
