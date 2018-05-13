void Efficiency_vs_Gen_pT()
{
//=========Macro generated from canvas: effpt/effpt
//=========  (Sun May 13 03:03:07 2018) by ROOT version6.06/01
   TCanvas *effpt = new TCanvas("effpt", "effpt",0,0,600,600);
   effpt->Range(-7.200001,0.2738629,136.8,1.113328);
   effpt->SetFillColor(0);
   effpt->SetBorderMode(0);
   effpt->SetBorderSize(2);
   effpt->SetTickx(1);
   effpt->SetTicky(1);
   effpt->SetLeftMargin(0.15);
   effpt->SetRightMargin(0.05);
   effpt->SetTopMargin(0.07);
   effpt->SetBottomMargin(0.15);
   effpt->SetFrameFillStyle(0);
   effpt->SetFrameBorderMode(0);
   effpt->SetFrameFillStyle(0);
   effpt->SetFrameBorderMode(0);
   
   Double_t divide_num_1D_A0_pT_by_den_1D_A0_pT_fx3009[32] = {
   25.5,
   28.5,
   31.5,
   34.5,
   37.5,
   40.5,
   43.5,
   46.5,
   49.5,
   52.5,
   55.5,
   58.5,
   61.5,
   64.5,
   67.5,
   70.5,
   73.5,
   76.5,
   79.5,
   82.5,
   85.5,
   88.5,
   91.5,
   94.5,
   97.5,
   100.5,
   103.5,
   106.5,
   109.5,
   112.5,
   115.5,
   118.5};
   Double_t divide_num_1D_A0_pT_by_den_1D_A0_pT_fy3009[32] = {
   1,
   0.8947368,
   0.9634146,
   0.9594595,
   0.9829545,
   0.9690722,
   0.9710744,
   0.9789474,
   0.9259259,
   0.96875,
   0.9464286,
   0.9485294,
   0.9649123,
   0.9333333,
   0.9324324,
   0.9454545,
   0.875,
   0.9722222,
   0.8484848,
   0.9130435,
   1,
   1,
   1,
   0.8461538,
   0.8235294,
   1,
   1,
   0.7142857,
   1,
   0.7777778,
   0.75,
   0.9090909};
   Double_t divide_num_1D_A0_pT_by_den_1D_A0_pT_felx3009[32] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t divide_num_1D_A0_pT_by_den_1D_A0_pT_fely3009[32] = {
   0.2642294,
   0.07543531,
   0.03430945,
   0.0234296,
   0.01630245,
   0.01801602,
   0.0152327,
   0.01633273,
   0.02237427,
   0.02058707,
   0.02350779,
   0.02662326,
   0.02687383,
   0.03769701,
   0.04312381,
   0.05022318,
   0.08785494,
   0.06099571,
   0.08951057,
   0.1033714,
   0.1320464,
   0.1086908,
   0.08794144,
   0.1680361,
   0.1424027,
   0.3080242,
   0.2055679,
   0.2599379,
   0.1155018,
   0.2214294,
   0.2395668,
   0.1792952};
   Double_t divide_num_1D_A0_pT_by_den_1D_A0_pT_fehx3009[32] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t divide_num_1D_A0_pT_by_den_1D_A0_pT_fehy3009[32] = {
   0,
   0.04968776,
   0.01984572,
   0.01596477,
   0.009262668,
   0.01220052,
   0.01060691,
   0.01004883,
   0.01793119,
   0.01343294,
   0.01730783,
   0.01878871,
   0.01671803,
   0.02612713,
   0.02887602,
   0.02953925,
   0.05884244,
   0.02299056,
   0.06383582,
   0.05596248,
   0,
   0,
   0,
   0.09871331,
   0.09442668,
   0,
   0,
   0.182129,
   0,
   0.1421182,
   0.1596593,
   0.07532688};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(32,divide_num_1D_A0_pT_by_den_1D_A0_pT_fx3009,divide_num_1D_A0_pT_by_den_1D_A0_pT_fy3009,divide_num_1D_A0_pT_by_den_1D_A0_pT_felx3009,divide_num_1D_A0_pT_by_den_1D_A0_pT_fehx3009,divide_num_1D_A0_pT_by_den_1D_A0_pT_fely3009,divide_num_1D_A0_pT_by_den_1D_A0_pT_fehy3009);
   grae->SetName("divide_num_1D_A0_pT_by_den_1D_A0_pT");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(21);
   
   TH1F *Graph_divide_num_1D_A0_pT_by_den_1D_A0_pT3009 = new TH1F("Graph_divide_num_1D_A0_pT_by_den_1D_A0_pT3009","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,14.4,129.6);
   Graph_divide_num_1D_A0_pT_by_den_1D_A0_pT3009->SetMinimum(0.3997826);
   Graph_divide_num_1D_A0_pT_by_den_1D_A0_pT3009->SetMaximum(1.054565);
   Graph_divide_num_1D_A0_pT_by_den_1D_A0_pT3009->SetDirectory(0);
   Graph_divide_num_1D_A0_pT_by_den_1D_A0_pT3009->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_1D_A0_pT_by_den_1D_A0_pT3009->SetLineColor(ci);
   Graph_divide_num_1D_A0_pT_by_den_1D_A0_pT3009->GetXaxis()->SetTitle("p_{T} [GeV]");
   Graph_divide_num_1D_A0_pT_by_den_1D_A0_pT3009->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_1D_A0_pT_by_den_1D_A0_pT3009->GetXaxis()->SetLabelOffset(0.007);
   Graph_divide_num_1D_A0_pT_by_den_1D_A0_pT3009->GetXaxis()->SetLabelSize(0.05);
   Graph_divide_num_1D_A0_pT_by_den_1D_A0_pT3009->GetXaxis()->SetTitleSize(0.06);
   Graph_divide_num_1D_A0_pT_by_den_1D_A0_pT3009->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_1D_A0_pT_by_den_1D_A0_pT3009->GetYaxis()->SetTitle("Efficiency");
   Graph_divide_num_1D_A0_pT_by_den_1D_A0_pT3009->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_1D_A0_pT_by_den_1D_A0_pT3009->GetYaxis()->SetLabelOffset(0.007);
   Graph_divide_num_1D_A0_pT_by_den_1D_A0_pT3009->GetYaxis()->SetLabelSize(0.05);
   Graph_divide_num_1D_A0_pT_by_den_1D_A0_pT3009->GetYaxis()->SetTitleSize(0.06);
   Graph_divide_num_1D_A0_pT_by_den_1D_A0_pT3009->GetYaxis()->SetTitleOffset(1.1);
   Graph_divide_num_1D_A0_pT_by_den_1D_A0_pT3009->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_1D_A0_pT_by_den_1D_A0_pT3009->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_1D_A0_pT_by_den_1D_A0_pT3009->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_1D_A0_pT_by_den_1D_A0_pT3009->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_1D_A0_pT_by_den_1D_A0_pT3009->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_1D_A0_pT_by_den_1D_A0_pT3009);
   
   grae->Draw("alp");
   
   Double_t divide_num_1D_A1_pT_by_den_1D_A1_pT_fx3010[32] = {
   16.5,
   19.5,
   22.5,
   25.5,
   28.5,
   31.5,
   34.5,
   37.5,
   40.5,
   43.5,
   46.5,
   49.5,
   52.5,
   55.5,
   58.5,
   61.5,
   64.5,
   67.5,
   70.5,
   73.5,
   76.5,
   79.5,
   85.5,
   88.5,
   91.5,
   94.5,
   97.5,
   100.5,
   103.5,
   106.5,
   109.5,
   112.5};
   Double_t divide_num_1D_A1_pT_by_den_1D_A1_pT_fy3010[32] = {
   1,
   0.9912281,
   0.9625668,
   0.9473684,
   0.952862,
   0.9815951,
   0.9789157,
   0.9806202,
   0.9396985,
   0.9659864,
   0.9468085,
   0.921875,
   0.9318182,
   0.9166667,
   0.9444444,
   0.9375,
   0.8888889,
   0.875,
   0.8571429,
   0.75,
   0.5,
   1,
   0.6666667,
   1,
   1,
   1,
   1,
   1,
   1,
   0.8571429,
   1,
   1};
   Double_t divide_num_1D_A1_pT_by_den_1D_A1_pT_felx3010[32] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t divide_num_1D_A1_pT_by_den_1D_A1_pT_fely3010[32] = {
   0.0636358,
   0.01988088,
   0.01958069,
   0.01926947,
   0.0157458,
   0.01083117,
   0.01117196,
   0.01289748,
   0.02195504,
   0.02235447,
   0.03438116,
   0.04939541,
   0.06190057,
   0.07446743,
   0.1164146,
   0.1294291,
   0.2115579,
   0.2322503,
   0.2571238,
   0.3684024,
   0.4172485,
   0.3688776,
   0.4145347,
   0.6016845,
   0.6016845,
   0.8413447,
   0.6016845,
   0.4586417,
   0.8413447,
   0.2571238,
   0.6016845,
   0.6016845};
   Double_t divide_num_1D_A1_pT_by_den_1D_A1_pT_fehx3010[32] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t divide_num_1D_A1_pT_by_den_1D_A1_pT_fehy3010[32] = {
   0,
   0.007257693,
   0.01370329,
   0.01477593,
   0.01228595,
   0.007276732,
   0.007743559,
   0.008345964,
   0.01689449,
   0.01461453,
   0.02278506,
   0.03333028,
   0.03687703,
   0.04500725,
   0.04600403,
   0.05176097,
   0.0920993,
   0.1036373,
   0.1184801,
   0.2077309,
   0.4172485,
   0,
   0.2773754,
   0,
   0,
   0,
   0,
   0,
   0,
   0.1184801,
   0,
   0};
   grae = new TGraphAsymmErrors(32,divide_num_1D_A1_pT_by_den_1D_A1_pT_fx3010,divide_num_1D_A1_pT_by_den_1D_A1_pT_fy3010,divide_num_1D_A1_pT_by_den_1D_A1_pT_felx3010,divide_num_1D_A1_pT_by_den_1D_A1_pT_fehx3010,divide_num_1D_A1_pT_by_den_1D_A1_pT_fely3010,divide_num_1D_A1_pT_by_den_1D_A1_pT_fehy3010);
   grae->SetName("divide_num_1D_A1_pT_by_den_1D_A1_pT");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");

   ci = TColor::GetColor("#0000ff");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#0000ff");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(21);
   
   TH1F *Graph_divide_num_1D_A1_pT_by_den_1D_A1_pT3010 = new TH1F("Graph_divide_num_1D_A1_pT_by_den_1D_A1_pT3010","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,5.1,123.9);
   Graph_divide_num_1D_A1_pT_by_den_1D_A1_pT3010->SetMinimum(0);
   Graph_divide_num_1D_A1_pT_by_den_1D_A1_pT3010->SetMaximum(1.091725);
   Graph_divide_num_1D_A1_pT_by_den_1D_A1_pT3010->SetDirectory(0);
   Graph_divide_num_1D_A1_pT_by_den_1D_A1_pT3010->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_1D_A1_pT_by_den_1D_A1_pT3010->SetLineColor(ci);
   Graph_divide_num_1D_A1_pT_by_den_1D_A1_pT3010->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_1D_A1_pT_by_den_1D_A1_pT3010->GetXaxis()->SetLabelOffset(0.007);
   Graph_divide_num_1D_A1_pT_by_den_1D_A1_pT3010->GetXaxis()->SetLabelSize(0.05);
   Graph_divide_num_1D_A1_pT_by_den_1D_A1_pT3010->GetXaxis()->SetTitleSize(0.06);
   Graph_divide_num_1D_A1_pT_by_den_1D_A1_pT3010->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_1D_A1_pT_by_den_1D_A1_pT3010->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_1D_A1_pT_by_den_1D_A1_pT3010->GetYaxis()->SetLabelOffset(0.007);
   Graph_divide_num_1D_A1_pT_by_den_1D_A1_pT3010->GetYaxis()->SetLabelSize(0.05);
   Graph_divide_num_1D_A1_pT_by_den_1D_A1_pT3010->GetYaxis()->SetTitleSize(0.06);
   Graph_divide_num_1D_A1_pT_by_den_1D_A1_pT3010->GetYaxis()->SetTitleOffset(1.1);
   Graph_divide_num_1D_A1_pT_by_den_1D_A1_pT3010->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_1D_A1_pT_by_den_1D_A1_pT3010->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_1D_A1_pT_by_den_1D_A1_pT3010->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_1D_A1_pT_by_den_1D_A1_pT3010->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_1D_A1_pT_by_den_1D_A1_pT3010->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_1D_A1_pT_by_den_1D_A1_pT3010);
   
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
   effpt->Modified();
   effpt->cd();
   effpt->SetSelected(effpt);
}
