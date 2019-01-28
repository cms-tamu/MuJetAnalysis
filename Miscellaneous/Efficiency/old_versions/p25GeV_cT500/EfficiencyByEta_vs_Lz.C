void EfficiencyByEta_vs_Lz()
{
//=========Macro generated from canvas: eta_lz/eta_lz
//=========  (Wed Oct 28 08:49:19 2015) by ROOT version6.02/05
   TCanvas *eta_lz = new TCanvas("eta_lz", "eta_lz",78,647,700,500);
   eta_lz->Range(-15,-0.125,95,1.125);
   eta_lz->SetFillColor(0);
   eta_lz->SetBorderMode(0);
   eta_lz->SetBorderSize(2);
   eta_lz->SetFrameBorderMode(0);
   eta_lz->SetFrameBorderMode(0);
   
   TMultiGraph *multigraph = new TMultiGraph();
   multigraph->SetName("");
   multigraph->SetTitle("");
   
   Double_t divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fx3005[17] = {
   1,
   3,
   5,
   7,
   9,
   11,
   14,
   17,
   19,
   22.5,
   27.5,
   32.5,
   37.5,
   42.5,
   47.5,
   55,
   70};
   Double_t divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fy3005[17] = {
   0.8207681,
   0.7183406,
   0.6823529,
   0.6296296,
   0.6016949,
   0.5540541,
   0.4752187,
   0.3962264,
   0.4306569,
   0.4033898,
   0.2211982,
   0.2352941,
   0.1679389,
   0.1630435,
   0,
   0,
   0};
   Double_t divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_felx3005[17] = {
   1,
   1,
   1,
   1,
   1,
   1,
   2,
   1,
   1,
   2.5,
   2.5,
   2.5,
   2.5,
   2.5,
   2.5,
   5,
   10};
   Double_t divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fely3005[17] = {
   0.01564874,
   0.02258889,
   0.02724798,
   0.03011546,
   0.03436919,
   0.03578772,
   0.02830245,
   0.04109258,
   0.04522796,
   0.02985828,
   0.0290375,
   0.03208442,
   0.03356904,
   0.03963993,
   0,
   0,
   0};
   Double_t divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fehx3005[17] = {
   1,
   1,
   1,
   1,
   1,
   1,
   2,
   1,
   1,
   2.5,
   2.5,
   2.5,
   2.5,
   2.5,
   2.5,
   5,
   10};
   Double_t divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fehy3005[17] = {
   0.01469211,
   0.02158727,
   0.02611493,
   0.02919205,
   0.03345254,
   0.03526936,
   0.02845448,
   0.04249806,
   0.04632244,
   0.03055065,
   0.03180918,
   0.03514912,
   0.03920329,
   0.04793882,
   0.02750881,
   0.02093884,
   0.05124115};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(17,divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fx3005,divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fy3005,divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_felx3005,divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fehx3005,divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fely3005,divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fehy3005);
   grae->SetName("divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ");
   grae->SetTitle("num_LEp8_1D_A0_LZ");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005 = new TH1F("Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005","num_LEp8_1D_A0_LZ",100,0,88);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005->SetMinimum(0);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005->SetMaximum(0.9190063);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005->SetDirectory(0);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005->SetLineColor(ci);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005->GetXaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005->GetXaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005->GetYaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005->GetYaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005);
   
   multigraph->Add(grae,"");
   
   Double_t divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fx3006[17] = {
   1,
   3,
   5,
   7,
   9,
   11,
   14,
   17,
   19,
   22.5,
   27.5,
   32.5,
   37.5,
   42.5,
   47.5,
   55,
   70};
   Double_t divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fy3006[17] = {
   0.6332418,
   0.5798687,
   0.5823529,
   0.5357143,
   0.5034722,
   0.4377682,
   0.3896104,
   0.3832335,
   0.4342105,
   0.3407821,
   0.2759857,
   0.2627119,
   0.2279793,
   0.2328767,
   0.1691176,
   0.1392405,
   0.1223881};
   Double_t divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_felx3006[17] = {
   1,
   1,
   1,
   1,
   1,
   1,
   2,
   1,
   1,
   2.5,
   2.5,
   2.5,
   2.5,
   2.5,
   2.5,
   5,
   10};
   Double_t divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fely3006[17] = {
   0.01872525,
   0.02433834,
   0.02842864,
   0.03011177,
   0.03115367,
   0.034285,
   0.02581644,
   0.03973677,
   0.04287325,
   0.02594182,
   0.02765258,
   0.02963204,
   0.03119337,
   0.03629216,
   0.03303557,
   0.02291424,
   0.01817166};
   Double_t divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fehx3006[17] = {
   1,
   1,
   1,
   1,
   1,
   1,
   2,
   1,
   1,
   2.5,
   2.5,
   2.5,
   2.5,
   2.5,
   2.5,
   5,
   10};
   Double_t divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fehy3006[17] = {
   0.01834545,
   0.02397274,
   0.02791852,
   0.02986711,
   0.03112819,
   0.0348529,
   0.02641888,
   0.04124068,
   0.04380578,
   0.02687925,
   0.02936211,
   0.03178592,
   0.03424404,
   0.04029203,
   0.03843241,
   0.02623551,
   0.02060956};
   grae = new TGraphAsymmErrors(17,divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fx3006,divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fy3006,divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_felx3006,divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fehx3006,divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fely3006,divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fehy3006);
   grae->SetName("divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ");
   grae->SetTitle("num_LEp8_1D_A1_LZ");
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006 = new TH1F("Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006","num_LEp8_1D_A1_LZ",100,0,88);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006->SetMinimum(0.04947932);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006->SetMaximum(0.7063243);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006->SetDirectory(0);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006->SetLineColor(ci);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006->GetXaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006->GetXaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006->GetYaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006->GetYaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006);
   
   multigraph->Add(grae,"");
   
   Double_t divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fx3007[17] = {
   1,
   3,
   5,
   7,
   9,
   11,
   14,
   17,
   19,
   22.5,
   27.5,
   32.5,
   37.5,
   42.5,
   47.5,
   55,
   70};
   Double_t divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fy3007[17] = {
   0.6829268,
   0.6,
   0.6851852,
   0.6,
   0.6060606,
   0.5588235,
   0.5571429,
   0.5853659,
   0.6071429,
   0.5454545,
   0.3875,
   0.3333333,
   0.2727273,
   0.4090909,
   0.2957746,
   0.1875,
   0.1058201};
   Double_t divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_felx3007[17] = {
   1,
   1,
   1,
   1,
   1,
   1,
   2,
   1,
   1,
   2.5,
   2.5,
   2.5,
   2.5,
   2.5,
   2.5,
   5,
   10};
   Double_t divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fely3007[17] = {
   0.08888679,
   0.1079526,
   0.07564299,
   0.09880854,
   0.1021968,
   0.1001643,
   0.06689406,
   0.09028307,
   0.1123558,
   0.0589631,
   0.05875506,
   0.06081322,
   0.05358554,
   0.06599562,
   0.05755151,
   0.0355912,
   0.02268587};
   Double_t divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fehx3007[17] = {
   1,
   1,
   1,
   1,
   1,
   1,
   2,
   1,
   1,
   2.5,
   2.5,
   2.5,
   2.5,
   2.5,
   2.5,
   5,
   10};
   Double_t divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fehy3007[17] = {
   0.07863764,
   0.1002229,
   0.06787653,
   0.09223778,
   0.0947793,
   0.09618714,
   0.06508215,
   0.08553781,
   0.1034446,
   0.05782793,
   0.06186464,
   0.06620896,
   0.06018711,
   0.06906434,
   0.06399194,
   0.04099953,
   0.02733468};
   grae = new TGraphAsymmErrors(17,divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fx3007,divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fy3007,divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_felx3007,divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fehx3007,divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fely3007,divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fehy3007);
   grae->SetName("divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ");
   grae->SetTitle("num_Gp8_1D_A0_LZ");

   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);
   grae->SetLineStyle(2);

   ci = TColor::GetColor("#ff0000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007 = new TH1F("Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007","num_Gp8_1D_A0_LZ",100,0,88);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007->SetMinimum(0.01529121);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007->SetMaximum(0.8294075);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007->SetDirectory(0);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007->SetLineColor(ci);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007->GetXaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007->GetXaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007->GetYaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007->GetYaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007);
   
   multigraph->Add(grae,"");
   
   Double_t divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fx3008[17] = {
   1,
   3,
   5,
   7,
   9,
   11,
   14,
   17,
   19,
   22.5,
   27.5,
   32.5,
   37.5,
   42.5,
   47.5,
   55,
   70};
   Double_t divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fy3008[17] = {
   0.7852761,
   0.6949153,
   0.71875,
   0.6984127,
   0.6896552,
   0.5396825,
   0.6160714,
   0.5849057,
   0.4878049,
   0.4134615,
   0.3707865,
   0.3285714,
   0.1860465,
   0.3181818,
   0.1290323,
   0.09259259,
   0.04081633};
   Double_t divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_felx3008[17] = {
   1,
   1,
   1,
   1,
   1,
   1,
   2,
   1,
   1,
   2.5,
   2.5,
   2.5,
   2.5,
   2.5,
   2.5,
   5,
   10};
   Double_t divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fely3008[17] = {
   0.03705341,
   0.04823626,
   0.04535158,
   0.06876912,
   0.0574394,
   0.07080895,
   0.05131149,
   0.07811071,
   0.08866469,
   0.05191296,
   0.05487944,
   0.06007627,
   0.06168667,
   0.0758668,
   0.06070612,
   0.03940801,
   0.02631971};
   Double_t divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fehx3008[17] = {
   1,
   1,
   1,
   1,
   1,
   1,
   2,
   1,
   1,
   2.5,
   2.5,
   2.5,
   2.5,
   2.5,
   2.5,
   5,
   10};
   Double_t divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fehy3008[17] = {
   0.03323423,
   0.04462224,
   0.04161652,
   0.06168108,
   0.05261086,
   0.06940483,
   0.04905056,
   0.07450589,
   0.08934127,
   0.05373144,
   0.05807812,
   0.06554546,
   0.07886975,
   0.08532197,
   0.09032566,
   0.05778523,
   0.05131203};
   grae = new TGraphAsymmErrors(17,divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fx3008,divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fy3008,divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_felx3008,divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fehx3008,divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fely3008,divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fehy3008);
   grae->SetName("divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ");
   grae->SetTitle("num_Gp8_1D_A1_LZ");
   grae->SetLineStyle(2);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008 = new TH1F("Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008","num_Gp8_1D_A1_LZ",100,0,88);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008->SetMinimum(0);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008->SetMaximum(0.8989117);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008->SetDirectory(0);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008->SetLineColor(ci);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008->GetXaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008->GetXaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008->GetYaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008->GetYaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008);
   
   multigraph->Add(grae,"");
   multigraph->Draw("ALP");
   multigraph->GetXaxis()->SetTitle("L_{Z} [cm]");
   multigraph->GetXaxis()->SetLabelFont(42);
   multigraph->GetXaxis()->SetLabelSize(0.035);
   multigraph->GetXaxis()->SetTitleSize(0.035);
   multigraph->GetXaxis()->SetTitleFont(42);
   multigraph->GetYaxis()->SetTitle("Efficiency");
   multigraph->GetYaxis()->SetLabelFont(42);
   multigraph->GetYaxis()->SetLabelSize(0.035);
   multigraph->GetYaxis()->SetTitleSize(0.035);
   multigraph->GetYaxis()->SetTitleFont(42);
   TLine *line = new TLine(34.5,0,34.5,1);

   ci = TColor::GetColor("#0000ff");
   line->SetLineColor(ci);
   line->SetLineStyle(2);
   line->Draw();
   line = new TLine(46.5,0,46.5,1);

   ci = TColor::GetColor("#0000ff");
   line->SetLineColor(ci);
   line->SetLineStyle(2);
   line->Draw();
   
   TLegend *leg = new TLegend(0.6982759,0.6701903,0.8979885,0.8794926,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.03171247);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY","|#eta_{#gamma D}| #leq 0.8 A0 #mu_{0}","L");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY","|#eta_{#gamma D}| > 0.8 A0 #mu_{0}","L");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(2);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY","|#eta_{#gamma D}| #leq 0.8 A1 #mu_{1}","L");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY","|#eta_{#gamma D}| > 0.8 A1 #mu_{1}","L");
   entry->SetLineColor(1);
   entry->SetLineStyle(2);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   eta_lz->Modified();
   eta_lz->cd();
   eta_lz->SetSelected(eta_lz);
}
