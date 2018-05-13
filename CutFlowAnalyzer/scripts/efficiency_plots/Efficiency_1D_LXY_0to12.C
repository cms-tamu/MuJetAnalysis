void Efficiency_1D_LXY_0to12()
{
//=========Macro generated from canvas: effxy/effxy
//=========  (Sun May 13 03:03:07 2018) by ROOT version6.06/01
   TCanvas *effxy = new TCanvas("effxy", "effxy",1,1,600,576);
   effxy->Range(-2.25,-0.1923077,12.75,1.089744);
   effxy->SetFillColor(0);
   effxy->SetBorderMode(0);
   effxy->SetBorderSize(2);
   effxy->SetTickx(1);
   effxy->SetTicky(1);
   effxy->SetLeftMargin(0.15);
   effxy->SetRightMargin(0.05);
   effxy->SetTopMargin(0.07);
   effxy->SetBottomMargin(0.15);
   effxy->SetFrameFillStyle(0);
   effxy->SetFrameBorderMode(0);
   effxy->SetFrameFillStyle(0);
   effxy->SetFrameBorderMode(0);
   
   Double_t divide_num_1D_A0_LXY_by_den_1D_A0_LXY_fx3003[1] = {
   0.5};
   Double_t divide_num_1D_A0_LXY_by_den_1D_A0_LXY_fy3003[1] = {
   0.9511202};
   Double_t divide_num_1D_A0_LXY_by_den_1D_A0_LXY_felx3003[1] = {
   0.5};
   Double_t divide_num_1D_A0_LXY_by_den_1D_A0_LXY_fely3003[1] = {
   0.004749273};
   Double_t divide_num_1D_A0_LXY_by_den_1D_A0_LXY_fehx3003[1] = {
   0.5};
   Double_t divide_num_1D_A0_LXY_by_den_1D_A0_LXY_fehy3003[1] = {
   0.004364631};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(1,divide_num_1D_A0_LXY_by_den_1D_A0_LXY_fx3003,divide_num_1D_A0_LXY_by_den_1D_A0_LXY_fy3003,divide_num_1D_A0_LXY_by_den_1D_A0_LXY_felx3003,divide_num_1D_A0_LXY_by_den_1D_A0_LXY_fehx3003,divide_num_1D_A0_LXY_by_den_1D_A0_LXY_fely3003,divide_num_1D_A0_LXY_by_den_1D_A0_LXY_fehy3003);
   grae->SetName("divide_num_1D_A0_LXY_by_den_1D_A0_LXY");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(25);
   
   TH1F *Graph_Graph_divide_num_1D_A0_LXY_by_den_1D_A0_LXY30013003 = new TH1F("Graph_Graph_divide_num_1D_A0_LXY_by_den_1D_A0_LXY30013003","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,12);
   Graph_Graph_divide_num_1D_A0_LXY_by_den_1D_A0_LXY30013003->SetMinimum(0);
   Graph_Graph_divide_num_1D_A0_LXY_by_den_1D_A0_LXY30013003->SetMaximum(1);
   Graph_Graph_divide_num_1D_A0_LXY_by_den_1D_A0_LXY30013003->SetDirectory(0);
   Graph_Graph_divide_num_1D_A0_LXY_by_den_1D_A0_LXY30013003->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_divide_num_1D_A0_LXY_by_den_1D_A0_LXY30013003->SetLineColor(ci);
   Graph_Graph_divide_num_1D_A0_LXY_by_den_1D_A0_LXY30013003->GetXaxis()->SetTitle("L_{xy} [cm]");
   Graph_Graph_divide_num_1D_A0_LXY_by_den_1D_A0_LXY30013003->GetXaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_1D_A0_LXY_by_den_1D_A0_LXY30013003->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph_divide_num_1D_A0_LXY_by_den_1D_A0_LXY30013003->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph_divide_num_1D_A0_LXY_by_den_1D_A0_LXY30013003->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph_divide_num_1D_A0_LXY_by_den_1D_A0_LXY30013003->GetXaxis()->SetTitleFont(42);
   Graph_Graph_divide_num_1D_A0_LXY_by_den_1D_A0_LXY30013003->GetYaxis()->SetTitle("Efficiency");
   Graph_Graph_divide_num_1D_A0_LXY_by_den_1D_A0_LXY30013003->GetYaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_1D_A0_LXY_by_den_1D_A0_LXY30013003->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph_divide_num_1D_A0_LXY_by_den_1D_A0_LXY30013003->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph_divide_num_1D_A0_LXY_by_den_1D_A0_LXY30013003->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph_divide_num_1D_A0_LXY_by_den_1D_A0_LXY30013003->GetYaxis()->SetTitleOffset(1.1);
   Graph_Graph_divide_num_1D_A0_LXY_by_den_1D_A0_LXY30013003->GetYaxis()->SetTitleFont(42);
   Graph_Graph_divide_num_1D_A0_LXY_by_den_1D_A0_LXY30013003->GetZaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_1D_A0_LXY_by_den_1D_A0_LXY30013003->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_divide_num_1D_A0_LXY_by_den_1D_A0_LXY30013003->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_divide_num_1D_A0_LXY_by_den_1D_A0_LXY30013003->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph_divide_num_1D_A0_LXY_by_den_1D_A0_LXY30013003);
   
   grae->Draw("alp");
   
   Double_t divide_num_1D_A1_LXY_by_den_1D_A1_LXY_fx3004[1] = {
   0.5};
   Double_t divide_num_1D_A1_LXY_by_den_1D_A1_LXY_fy3004[1] = {
   0.9616952};
   Double_t divide_num_1D_A1_LXY_by_den_1D_A1_LXY_felx3004[1] = {
   0.5};
   Double_t divide_num_1D_A1_LXY_by_den_1D_A1_LXY_fely3004[1] = {
   0.004278343};
   Double_t divide_num_1D_A1_LXY_by_den_1D_A1_LXY_fehx3004[1] = {
   0.5};
   Double_t divide_num_1D_A1_LXY_by_den_1D_A1_LXY_fehy3004[1] = {
   0.00388234};
   grae = new TGraphAsymmErrors(1,divide_num_1D_A1_LXY_by_den_1D_A1_LXY_fx3004,divide_num_1D_A1_LXY_by_den_1D_A1_LXY_fy3004,divide_num_1D_A1_LXY_by_den_1D_A1_LXY_felx3004,divide_num_1D_A1_LXY_by_den_1D_A1_LXY_fehx3004,divide_num_1D_A1_LXY_by_den_1D_A1_LXY_fely3004,divide_num_1D_A1_LXY_by_den_1D_A1_LXY_fehy3004);
   grae->SetName("divide_num_1D_A1_LXY_by_den_1D_A1_LXY");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");

   ci = TColor::GetColor("#0000ff");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#0000ff");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(22);
   
   TH1F *Graph_Graph_divide_num_1D_A1_LXY_by_den_1D_A1_LXY30023004 = new TH1F("Graph_Graph_divide_num_1D_A1_LXY_by_den_1D_A1_LXY30023004","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,1.1);
   Graph_Graph_divide_num_1D_A1_LXY_by_den_1D_A1_LXY30023004->SetMinimum(0.9566008);
   Graph_Graph_divide_num_1D_A1_LXY_by_den_1D_A1_LXY30023004->SetMaximum(0.9663936);
   Graph_Graph_divide_num_1D_A1_LXY_by_den_1D_A1_LXY30023004->SetDirectory(0);
   Graph_Graph_divide_num_1D_A1_LXY_by_den_1D_A1_LXY30023004->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_divide_num_1D_A1_LXY_by_den_1D_A1_LXY30023004->SetLineColor(ci);
   Graph_Graph_divide_num_1D_A1_LXY_by_den_1D_A1_LXY30023004->GetXaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_1D_A1_LXY_by_den_1D_A1_LXY30023004->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph_divide_num_1D_A1_LXY_by_den_1D_A1_LXY30023004->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph_divide_num_1D_A1_LXY_by_den_1D_A1_LXY30023004->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph_divide_num_1D_A1_LXY_by_den_1D_A1_LXY30023004->GetXaxis()->SetTitleFont(42);
   Graph_Graph_divide_num_1D_A1_LXY_by_den_1D_A1_LXY30023004->GetYaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_1D_A1_LXY_by_den_1D_A1_LXY30023004->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph_divide_num_1D_A1_LXY_by_den_1D_A1_LXY30023004->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph_divide_num_1D_A1_LXY_by_den_1D_A1_LXY30023004->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph_divide_num_1D_A1_LXY_by_den_1D_A1_LXY30023004->GetYaxis()->SetTitleOffset(1.1);
   Graph_Graph_divide_num_1D_A1_LXY_by_den_1D_A1_LXY30023004->GetYaxis()->SetTitleFont(42);
   Graph_Graph_divide_num_1D_A1_LXY_by_den_1D_A1_LXY30023004->GetZaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_1D_A1_LXY_by_den_1D_A1_LXY30023004->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_divide_num_1D_A1_LXY_by_den_1D_A1_LXY30023004->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_divide_num_1D_A1_LXY_by_den_1D_A1_LXY30023004->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph_divide_num_1D_A1_LXY_by_den_1D_A1_LXY30023004);
   
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
   effxy->Modified();
   effxy->cd();
   effxy->SetSelected(effxy);
}
