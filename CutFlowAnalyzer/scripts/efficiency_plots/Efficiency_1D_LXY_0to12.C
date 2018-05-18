void Efficiency_1D_LXY_0to12()
{
//=========Macro generated from canvas: effxy/effxy
//=========  (Sun May 13 10:47:26 2018) by ROOT version6.06/01
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
   
   Double_t divide_num_1D_A0_LXY_by_den_1D_A0_LXY_fx3003[10] = {
   0.5,
   1.5,
   2.5,
   3.5,
   4.5,
   5.5,
   6.5,
   7.5,
   8.5,
   9.5};
   Double_t divide_num_1D_A0_LXY_by_den_1D_A0_LXY_fy3003[10] = {
   0.9366294,
   0.9122978,
   0.9044646,
   0.8802964,
   0.8687483,
   0.8419306,
   0.8356345,
   0.8479941,
   0.8526598,
   0.8378244};
   Double_t divide_num_1D_A0_LXY_by_den_1D_A0_LXY_felx3003[10] = {
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5};
   Double_t divide_num_1D_A0_LXY_by_den_1D_A0_LXY_fely3003[10] = {
   0.002203731,
   0.003468538,
   0.004216068,
   0.005145222,
   0.005855477,
   0.006592045,
   0.006996275,
   0.007202779,
   0.007263403,
   0.008656284};
   Double_t divide_num_1D_A0_LXY_by_den_1D_A0_LXY_fehx3003[10] = {
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5};
   Double_t divide_num_1D_A0_LXY_by_den_1D_A0_LXY_fehy3003[10] = {
   0.002135699,
   0.003351173,
   0.004059471,
   0.004965014,
   0.005646709,
   0.006380878,
   0.006770252,
   0.006939829,
   0.006986087,
   0.008309018};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(10,divide_num_1D_A0_LXY_by_den_1D_A0_LXY_fx3003,divide_num_1D_A0_LXY_by_den_1D_A0_LXY_fy3003,divide_num_1D_A0_LXY_by_den_1D_A0_LXY_felx3003,divide_num_1D_A0_LXY_by_den_1D_A0_LXY_fehx3003,divide_num_1D_A0_LXY_by_den_1D_A0_LXY_fely3003,divide_num_1D_A0_LXY_by_den_1D_A0_LXY_fehy3003);
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
   
   Double_t divide_num_1D_A1_LXY_by_den_1D_A1_LXY_fx3004[10] = {
   0.5,
   1.5,
   2.5,
   3.5,
   4.5,
   5.5,
   6.5,
   7.5,
   8.5,
   9.5};
   Double_t divide_num_1D_A1_LXY_by_den_1D_A1_LXY_fy3004[10] = {
   0.9125022,
   0.8645523,
   0.8202722,
   0.8029155,
   0.7808042,
   0.7467566,
   0.7070792,
   0.7075792,
   0.6939809,
   0.6879937};
   Double_t divide_num_1D_A1_LXY_by_den_1D_A1_LXY_felx3004[10] = {
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5};
   Double_t divide_num_1D_A1_LXY_by_den_1D_A1_LXY_fely3004[10] = {
   0.00219302,
   0.003761212,
   0.00493104,
   0.005702588,
   0.00625191,
   0.007199102,
   0.007794879,
   0.007849754,
   0.008161713,
   0.009479104};
   Double_t divide_num_1D_A1_LXY_by_den_1D_A1_LXY_fehx3004[10] = {
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5};
   Double_t divide_num_1D_A1_LXY_by_den_1D_A1_LXY_fehy3004[10] = {
   0.002145051,
   0.003676434,
   0.004829222,
   0.005582786,
   0.006128366,
   0.007068699,
   0.007677353,
   0.007730195,
   0.008043966,
   0.009327461};
   grae = new TGraphAsymmErrors(10,divide_num_1D_A1_LXY_by_den_1D_A1_LXY_fx3004,divide_num_1D_A1_LXY_by_den_1D_A1_LXY_fy3004,divide_num_1D_A1_LXY_by_den_1D_A1_LXY_felx3004,divide_num_1D_A1_LXY_by_den_1D_A1_LXY_fehx3004,divide_num_1D_A1_LXY_by_den_1D_A1_LXY_fely3004,divide_num_1D_A1_LXY_by_den_1D_A1_LXY_fehy3004);
   grae->SetName("divide_num_1D_A1_LXY_by_den_1D_A1_LXY");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");

   ci = TColor::GetColor("#0000ff");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#0000ff");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(22);
   
   TH1F *Graph_Graph_divide_num_1D_A1_LXY_by_den_1D_A1_LXY30023004 = new TH1F("Graph_Graph_divide_num_1D_A1_LXY_by_den_1D_A1_LXY30023004","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,11);
   Graph_Graph_divide_num_1D_A1_LXY_by_den_1D_A1_LXY30023004->SetMinimum(0.6549013);
   Graph_Graph_divide_num_1D_A1_LXY_by_den_1D_A1_LXY30023004->SetMaximum(0.9382605);
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
