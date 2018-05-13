void Efficiency_1D_Lz()
{
//=========Macro generated from canvas: effz2/effz2
//=========  (Sun May 13 03:03:07 2018) by ROOT version6.06/01
   TCanvas *effz2 = new TCanvas("effz2", "effz2",0,0,600,600);
   effz2->Range(-0.20625,-0.1923077,1.16875,1.089744);
   effz2->SetFillColor(0);
   effz2->SetBorderMode(0);
   effz2->SetBorderSize(2);
   effz2->SetTickx(1);
   effz2->SetTicky(1);
   effz2->SetLeftMargin(0.15);
   effz2->SetRightMargin(0.05);
   effz2->SetTopMargin(0.07);
   effz2->SetBottomMargin(0.15);
   effz2->SetFrameFillStyle(0);
   effz2->SetFrameBorderMode(0);
   effz2->SetFrameFillStyle(0);
   effz2->SetFrameBorderMode(0);
   
   Double_t divide_num_1D_A0_LZ_by_den_1D_A0_LZ_fx3005[1] = {
   0.5};
   Double_t divide_num_1D_A0_LZ_by_den_1D_A0_LZ_fy3005[1] = {
   0.9492934};
   Double_t divide_num_1D_A0_LZ_by_den_1D_A0_LZ_felx3005[1] = {
   0.5};
   Double_t divide_num_1D_A0_LZ_by_den_1D_A0_LZ_fely3005[1] = {
   0.007143374};
   Double_t divide_num_1D_A0_LZ_by_den_1D_A0_LZ_fehx3005[1] = {
   0.5};
   Double_t divide_num_1D_A0_LZ_by_den_1D_A0_LZ_fehy3005[1] = {
   0.006347663};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(1,divide_num_1D_A0_LZ_by_den_1D_A0_LZ_fx3005,divide_num_1D_A0_LZ_by_den_1D_A0_LZ_fy3005,divide_num_1D_A0_LZ_by_den_1D_A0_LZ_felx3005,divide_num_1D_A0_LZ_by_den_1D_A0_LZ_fehx3005,divide_num_1D_A0_LZ_by_den_1D_A0_LZ_fely3005,divide_num_1D_A0_LZ_by_den_1D_A0_LZ_fehy3005);
   grae->SetName("divide_num_1D_A0_LZ_by_den_1D_A0_LZ");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(21);
   
   TH1F *Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3005 = new TH1F("Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3005","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,1.1);
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3005->SetMinimum(0);
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3005->SetMaximum(1);
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3005->SetDirectory(0);
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3005->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3005->SetLineColor(ci);
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3005->GetXaxis()->SetTitle("L_{z} [cm]");
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3005->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3005->GetXaxis()->SetLabelOffset(0.007);
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3005->GetXaxis()->SetLabelSize(0.05);
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3005->GetXaxis()->SetTitleSize(0.06);
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3005->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3005->GetYaxis()->SetTitle("Efficiency");
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3005->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3005->GetYaxis()->SetLabelOffset(0.007);
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3005->GetYaxis()->SetLabelSize(0.05);
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3005->GetYaxis()->SetTitleSize(0.06);
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3005->GetYaxis()->SetTitleOffset(1.1);
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3005->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3005->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3005->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3005->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3005->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3005);
   
   grae->Draw("alp");
   
   Double_t divide_num_1D_A1_LZ_by_den_1D_A1_LZ_fx3006[1] = {
   0.5};
   Double_t divide_num_1D_A1_LZ_by_den_1D_A1_LZ_fy3006[1] = {
   0.9657702};
   Double_t divide_num_1D_A1_LZ_by_den_1D_A1_LZ_felx3006[1] = {
   0.5};
   Double_t divide_num_1D_A1_LZ_by_den_1D_A1_LZ_fely3006[1] = {
   0.006014065};
   Double_t divide_num_1D_A1_LZ_by_den_1D_A1_LZ_fehx3006[1] = {
   0.5};
   Double_t divide_num_1D_A1_LZ_by_den_1D_A1_LZ_fehy3006[1] = {
   0.005195556};
   grae = new TGraphAsymmErrors(1,divide_num_1D_A1_LZ_by_den_1D_A1_LZ_fx3006,divide_num_1D_A1_LZ_by_den_1D_A1_LZ_fy3006,divide_num_1D_A1_LZ_by_den_1D_A1_LZ_felx3006,divide_num_1D_A1_LZ_by_den_1D_A1_LZ_fehx3006,divide_num_1D_A1_LZ_by_den_1D_A1_LZ_fely3006,divide_num_1D_A1_LZ_by_den_1D_A1_LZ_fehy3006);
   grae->SetName("divide_num_1D_A1_LZ_by_den_1D_A1_LZ");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");

   ci = TColor::GetColor("#0000ff");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#0000ff");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(21);
   
   TH1F *Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ3006 = new TH1F("Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ3006","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,1.1);
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ3006->SetMinimum(0.9586351);
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ3006->SetMaximum(0.9720867);
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ3006->SetDirectory(0);
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ3006->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ3006->SetLineColor(ci);
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ3006->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ3006->GetXaxis()->SetLabelOffset(0.007);
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ3006->GetXaxis()->SetLabelSize(0.05);
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ3006->GetXaxis()->SetTitleSize(0.06);
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ3006->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ3006->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ3006->GetYaxis()->SetLabelOffset(0.007);
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ3006->GetYaxis()->SetLabelSize(0.05);
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ3006->GetYaxis()->SetTitleSize(0.06);
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ3006->GetYaxis()->SetTitleOffset(1.1);
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ3006->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ3006->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ3006->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ3006->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ3006->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ3006);
   
   grae->Draw("p ");
   
   TLegend *leg = new TLegend(0.2,0.2,0.35,0.35,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.05);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("divide_num_1D_A0_LXY_by_den_1D_A0_LXY","#gamma_{D1}","LP");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ff0000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(25);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("divide_num_1D_A1_LXY_by_den_1D_A1_LXY","#gamma_{D2}","LP");

   ci = TColor::GetColor("#0000ff");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#0000ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(22);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   TPaveText *pt = new TPaveText(0,0.942,1,1,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *AText = pt->AddText("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");
   pt->Draw();
   effz2->Modified();
   effz2->cd();
   effz2->SetSelected(effz2);
}
