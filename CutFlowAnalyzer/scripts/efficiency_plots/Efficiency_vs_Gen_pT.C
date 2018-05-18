void Efficiency_vs_Gen_pT()
{
//=========Macro generated from canvas: effpt/effpt
//=========  (Sun May 13 10:47:26 2018) by ROOT version6.06/01
   TCanvas *effpt = new TCanvas("effpt", "effpt",0,0,600,600);
   effpt->Range(-7.200001,0.6431446,136.8,0.9754946);
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
   0.8300654,
   0.8955068,
   0.9107221,
   0.9036145,
   0.9069156,
   0.9120228,
   0.9050863,
   0.8910701,
   0.8919949,
   0.8837793,
   0.8962642,
   0.8864558,
   0.8856126,
   0.8612836,
   0.8973214,
   0.8755605,
   0.8711567,
   0.8763066,
   0.8765432,
   0.875,
   0.8956835,
   0.8768116,
   0.9121339,
   0.8529412,
   0.856383,
   0.8071066,
   0.8366013,
   0.875,
   0.8646617,
   0.7719298,
   0.7653061,
   0.8586957};
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
   0.03593977,
   0.01084565,
   0.006370672,
   0.005328121,
   0.004953094,
   0.004581105,
   0.004624556,
   0.005036196,
   0.005177247,
   0.005599427,
   0.005871811,
   0.006753039,
   0.007633384,
   0.009683027,
   0.009888559,
   0.0120531,
   0.01412262,
   0.0153062,
   0.01677375,
   0.01968881,
   0.02168762,
   0.02306956,
   0.02232635,
   0.02910915,
   0.03028618,
   0.03228808,
   0.03552229,
   0.03094413,
   0.03643756,
   0.04615574,
   0.05070629,
   0.04607653};
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
   0.03118075,
   0.009975938,
   0.005998076,
   0.005084059,
   0.004733156,
   0.004380407,
   0.004435886,
   0.004844322,
   0.004972924,
   0.005379965,
   0.00559959,
   0.006429736,
   0.007227528,
   0.009165615,
   0.009144505,
   0.0111689,
   0.01297469,
   0.01391334,
   0.01511937,
   0.01749374,
   0.01856857,
   0.02009561,
   0.01849348,
   0.02531861,
   0.02611468,
   0.02889963,
   0.03066158,
   0.02597798,
   0.03028896,
   0.0408827,
   0.0446869,
   0.03717657};
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
   Graph_divide_num_1D_A0_pT_by_den_1D_A0_pT3009->SetMinimum(0.6929971);
   Graph_divide_num_1D_A0_pT_by_den_1D_A0_pT3009->SetMaximum(0.9522301);
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
   
   Double_t divide_num_1D_A1_pT_by_den_1D_A1_pT_fx3010[35] = {
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
   Double_t divide_num_1D_A1_pT_by_den_1D_A1_pT_fy3010[35] = {
   0.6714286,
   0.6705632,
   0.6852941,
   0.7355727,
   0.8090118,
   0.8572146,
   0.8792745,
   0.8833393,
   0.8841359,
   0.8843343,
   0.9036433,
   0.8882396,
   0.8581006,
   0.8833922,
   0.8776758,
   0.8952381,
   0.8956044,
   0.8741259,
   0.8153846,
   0.8640777,
   0.7936508,
   0.9152542,
   0.8113208,
   0.8444444,
   0.9189189,
   0.8823529,
   0.8333333,
   0.96,
   0.8823529,
   0.85,
   0.8333333,
   0.7777778,
   1,
   0.9,
   0.9};
   Double_t divide_num_1D_A1_pT_by_den_1D_A1_pT_felx3010[35] = {
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
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t divide_num_1D_A1_pT_by_den_1D_A1_pT_fely3010[35] = {
   0.01700313,
   0.007838889,
   0.00642232,
   0.005473831,
   0.004551283,
   0.004027027,
   0.003956207,
   0.004446406,
   0.005222365,
   0.005985451,
   0.006901324,
   0.009176069,
   0.01263908,
   0.01509275,
   0.02089054,
   0.02559453,
   0.02783121,
   0.03412578,
   0.04045654,
   0.04254526,
   0.06385177,
   0.05326417,
   0.06950296,
   0.07370022,
   0.07262648,
   0.08329135,
   0.1122974,
   0.08605119,
   0.1346015,
   0.1247114,
   0.1359989,
   0.2214294,
   0.2312605,
   0.1941354,
   0.1941354};
   Double_t divide_num_1D_A1_pT_by_den_1D_A1_pT_fehx3010[35] = {
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
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t divide_num_1D_A1_pT_by_den_1D_A1_pT_fehy3010[35] = {
   0.01658028,
   0.007746704,
   0.006353211,
   0.005403159,
   0.004471039,
   0.003935958,
   0.0038493,
   0.004306814,
   0.005030008,
   0.005734433,
   0.006500067,
   0.008584797,
   0.01180107,
   0.01365079,
   0.01839031,
   0.02141875,
   0.02297395,
   0.02826022,
   0.0350828,
   0.03451126,
   0.05319295,
   0.03611541,
   0.05587008,
   0.05553005,
   0.04380024,
   0.05543815,
   0.0779889,
   0.03311367,
   0.07561142,
   0.08048226,
   0.08927179,
   0.1421182,
   0,
   0.08287299,
   0.08287299};
   grae = new TGraphAsymmErrors(35,divide_num_1D_A1_pT_by_den_1D_A1_pT_fx3010,divide_num_1D_A1_pT_by_den_1D_A1_pT_fy3010,divide_num_1D_A1_pT_by_den_1D_A1_pT_felx3010,divide_num_1D_A1_pT_by_den_1D_A1_pT_fehx3010,divide_num_1D_A1_pT_by_den_1D_A1_pT_fely3010,divide_num_1D_A1_pT_by_den_1D_A1_pT_fehy3010);
   grae->SetName("divide_num_1D_A1_pT_by_den_1D_A1_pT");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");

   ci = TColor::GetColor("#0000ff");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#0000ff");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(21);
   
   TH1F *Graph_divide_num_1D_A1_pT_by_den_1D_A1_pT3010 = new TH1F("Graph_divide_num_1D_A1_pT_by_den_1D_A1_pT3010","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,4.5,130.5);
   Graph_divide_num_1D_A1_pT_by_den_1D_A1_pT3010->SetMinimum(0.5119832);
   Graph_divide_num_1D_A1_pT_by_den_1D_A1_pT3010->SetMaximum(1.044365);
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
