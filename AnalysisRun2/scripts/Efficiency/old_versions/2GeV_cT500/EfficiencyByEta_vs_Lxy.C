void EfficiencyByEta_vs_Lxy()
{
//=========Macro generated from canvas: eta_lxy/eta_lxy
//=========  (Wed Oct 28 08:31:34 2015) by ROOT version6.02/05
   TCanvas *eta_lxy = new TCanvas("eta_lxy", "eta_lxy",80,64,700,500);
   eta_lxy->Range(-15,-0.1297391,95,1.167652);
   eta_lxy->SetFillColor(0);
   eta_lxy->SetBorderMode(0);
   eta_lxy->SetBorderSize(2);
   eta_lxy->SetFrameBorderMode(0);
   eta_lxy->SetFrameBorderMode(0);
   
   TMultiGraph *multigraph = new TMultiGraph();
   multigraph->SetName("");
   multigraph->SetTitle("");
   
   Double_t divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fx3001[17] = {
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
   Double_t divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fy3001[17] = {
   0.9767171,
   0.9836553,
   0.9488055,
   0.9147727,
   0.8722359,
   0.8616715,
   0.8594507,
   0.8319328,
   0.8027523,
   0.8230958,
   0.7406015,
   0.625,
   0.6266667,
   0.4897959,
   0.5494505,
   0.4324324,
   0.1139241};
   Double_t divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_felx3001[17] = {
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
   Double_t divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fely3001[17] = {
   0.006360646,
   0.006487176,
   0.01080646,
   0.01394772,
   0.01875001,
   0.02108435,
   0.01538629,
   0.02781688,
   0.03069776,
   0.02097195,
   0.02967173,
   0.03652488,
   0.04358989,
   0.05517467,
   0.05790185,
   0.06285861,
   0.03627377};
   Double_t divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fehx3001[17] = {
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
   Double_t divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fehy3001[17] = {
   0.005125822,
   0.004832813,
   0.009132705,
   0.01225601,
   0.01678793,
   0.01884165,
   0.01415891,
   0.0247937,
   0.02769252,
   0.01928366,
   0.02774072,
   0.03524082,
   0.04176628,
   0.05540243,
   0.05670913,
   0.06488092,
   0.04767879};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(17,divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fx3001,divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fy3001,divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_felx3001,divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fehx3001,divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fely3001,divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fehy3001);
   grae->SetName("divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY");
   grae->SetTitle("num_LEp8_1D_A0_LXY");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001 = new TH1F("Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001","num_LEp8_1D_A0_LXY",100,0,88);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001->SetMinimum(0);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001->SetMaximum(1.079572);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001->SetDirectory(0);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001->SetLineColor(ci);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001->GetXaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001->GetXaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001->GetYaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001->GetYaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001);
   
   multigraph->Add(grae,"");
   
   Double_t divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fx3002[17] = {
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
   Double_t divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fy3002[17] = {
   0.968,
   0.952381,
   0.9186047,
   0.9146341,
   0.7532468,
   0.7625,
   0.8191489,
   0.8285714,
   0.7027027,
   0.7868852,
   0.7727273,
   0.6538462,
   0.5454545,
   0.4285714,
   0.3333333,
   0.1428571,
   0};
   Double_t divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_felx3002[17] = {
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
   Double_t divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fely3002[17] = {
   0.02457859,
   0.02735958,
   0.04108824,
   0.04295129,
   0.05898118,
   0.05720489,
   0.04866517,
   0.08833361,
   0.09373265,
   0.06557259,
   0.0809453,
   0.1170398,
   0.1278601,
   0.1545563,
   0.2773754,
   0.1184801,
   0};
   Double_t divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fehx3002[17] = {
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
   Double_t divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fehy3002[17] = {
   0.0152529,
   0.01872806,
   0.02952947,
   0.03094413,
   0.0515977,
   0.0498414,
   0.04101873,
   0.06581177,
   0.08104267,
   0.05481558,
   0.06654532,
   0.1031432,
   0.1229998,
   0.1668696,
   0.4145347,
   0.2571238,
   0.2312605};
   grae = new TGraphAsymmErrors(17,divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fx3002,divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fy3002,divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_felx3002,divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fehx3002,divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fely3002,divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fehy3002);
   grae->SetName("divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY");
   grae->SetTitle("num_Gp8_1D_A0_LXY");

   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);
   grae->SetLineStyle(2);

   ci = TColor::GetColor("#ff0000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002 = new TH1F("Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002","num_Gp8_1D_A0_LXY",100,0,88);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002->SetMinimum(0);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002->SetMaximum(1.081578);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002->SetDirectory(0);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002->SetLineColor(ci);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002->GetXaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002->GetXaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002->GetYaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002->GetYaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002);
   
   multigraph->Add(grae,"");
   
   Double_t divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fx3003[17] = {
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
   Double_t divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fy3003[17] = {
   0.9488994,
   0.9476386,
   0.9173028,
   0.8683788,
   0.8542601,
   0.8250653,
   0.8339921,
   0.8192771,
   0.8055556,
   0.7939914,
   0.7468354,
   0.6521739,
   0.5892857,
   0.3714286,
   0.3684211,
   0.3684211,
   0.0952381};
   Double_t divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_felx3003[17] = {
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
   Double_t divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fely3003[17] = {
   0.006946442,
   0.008148843,
   0.01102751,
   0.01496951,
   0.01866644,
   0.02160586,
   0.01821851,
   0.03491858,
   0.03869342,
   0.02995526,
   0.03934879,
   0.05660023,
   0.07572179,
   0.09019263,
   0.1245183,
   0.1245183,
   0.06127008};
   Double_t divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fehx3003[17] = {
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
   Double_t divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fehy3003[17] = {
   0.006195976,
   0.00716407,
   0.009897707,
   0.01371802,
   0.01697352,
   0.01979712,
   0.01682119,
   0.03070012,
   0.03402365,
   0.02723467,
   0.03595224,
   0.05295602,
   0.07214281,
   0.09865776,
   0.141036,
   0.141036,
   0.1120626};
   grae = new TGraphAsymmErrors(17,divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fx3003,divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fy3003,divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_felx3003,divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fehx3003,divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fely3003,divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fehy3003);
   grae->SetName("divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY");
   grae->SetTitle("num_LEp8_1D_A1_LXY");
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003 = new TH1F("Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003","num_LEp8_1D_A1_LXY",100,0,88);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003->SetMinimum(0);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003->SetMaximum(1.047208);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003->SetDirectory(0);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003->SetLineColor(ci);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003->GetXaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003->GetXaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003->GetYaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003->GetYaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003);
   
   multigraph->Add(grae,"");
   
   Double_t divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fx3004[17] = {
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
   Double_t divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fy3004[17] = {
   0.9456522,
   0.94,
   0.9701493,
   0.8934426,
   0.84375,
   0.8421053,
   0.875,
   0.9411765,
   0.9259259,
   0.8611111,
   0.8461538,
   0.6875,
   0.4444444,
   0.3333333,
   0.5,
   0.2857143,
   0};
   Double_t divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_felx3004[17] = {
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
   Double_t divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fely3004[17] = {
   0.02228736,
   0.0261995,
   0.02297303,
   0.03568151,
   0.05914675,
   0.06372643,
   0.04127598,
   0.0723694,
   0.08945996,
   0.08304282,
   0.1050332,
   0.1560626,
   0.1982671,
   0.1752104,
   0.2569096,
   0.182129,
   0};
   Double_t divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fehx3004[17] = {
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
   Double_t divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fehy3004[17] = {
   0.01667607,
   0.01935551,
   0.01423237,
   0.02832525,
   0.04668913,
   0.04971307,
   0.03304802,
   0.0379027,
   0.04769829,
   0.0586464,
   0.07212428,
   0.1276151,
   0.2134628,
   0.2213608,
   0.2569096,
   0.2599379,
   0.6016845};
   grae = new TGraphAsymmErrors(17,divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fx3004,divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fy3004,divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_felx3004,divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fehx3004,divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fely3004,divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fehy3004);
   grae->SetName("divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY");
   grae->SetTitle("num_Gp8_1D_A1_LXY");
   grae->SetLineStyle(2);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004 = new TH1F("Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004","num_Gp8_1D_A1_LXY",100,0,88);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004->SetMinimum(0);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004->SetMaximum(1.08282);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004->SetDirectory(0);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004->SetLineColor(ci);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004->GetXaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004->GetXaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004->GetYaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004->GetYaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004);
   
   multigraph->Add(grae,"");
   multigraph->Draw("ALP");
   multigraph->GetXaxis()->SetTitle("L_{XY} [cm]");
   multigraph->GetXaxis()->SetLabelFont(42);
   multigraph->GetXaxis()->SetLabelSize(0.035);
   multigraph->GetXaxis()->SetTitleSize(0.035);
   multigraph->GetXaxis()->SetTitleFont(42);
   multigraph->GetYaxis()->SetTitle("Efficiency");
   multigraph->GetYaxis()->SetLabelFont(42);
   multigraph->GetYaxis()->SetLabelSize(0.035);
   multigraph->GetYaxis()->SetTitleSize(0.035);
   multigraph->GetYaxis()->SetTitleFont(42);
   
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
   TLine *line = new TLine(4.3,0,4.3,1);

   ci = TColor::GetColor("#0000ff");
   line->SetLineColor(ci);
   line->SetLineStyle(2);
   line->Draw();
   line = new TLine(7.2,0,7.2,1);
   line->SetLineStyle(2);
   line->Draw();
   line = new TLine(11,0,11,1);
   line->SetLineStyle(2);
   line->Draw();
   line = new TLine(23.9,0,23.9,1);

   ci = TColor::GetColor("#00ff00");
   line->SetLineColor(ci);
   line->SetLineStyle(2);
   line->Draw();
   line = new TLine(60.5,0,60.5,1);

   ci = TColor::GetColor("#00ff00");
   line->SetLineColor(ci);
   line->SetLineStyle(2);
   line->Draw();
   eta_lxy->Modified();
   eta_lxy->cd();
   eta_lxy->SetSelected(eta_lxy);
}
