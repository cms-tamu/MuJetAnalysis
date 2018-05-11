void EfficiencyByEta_vs_Lz()
{
//=========Macro generated from canvas: eta_lz/eta_lz
//=========  (Mon May  7 00:39:50 2018) by ROOT version6.06/01
   TCanvas *eta_lz = new TCanvas("eta_lz", "eta_lz",0,0,700,500);
   eta_lz->Range(-15,-0.125,95,1.125);
   eta_lz->SetFillColor(0);
   eta_lz->SetBorderMode(0);
   eta_lz->SetBorderSize(2);
   eta_lz->SetFrameBorderMode(0);
   eta_lz->SetFrameBorderMode(0);
   
   TMultiGraph *multigraph = new TMultiGraph();
   multigraph->SetName("");
   multigraph->SetTitle("");
   
   Double_t divide_num_LEp9_1D_A0_LZ_by_den_LEp9_1D_A0_LZ_fx3001[17] = {
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
   Double_t divide_num_LEp9_1D_A0_LZ_by_den_LEp9_1D_A0_LZ_fy3001[17] = {
   0.8951272,
   0.8378807,
   0.8079942,
   0.785345,
   0.7794497,
   0.7543516,
   0.7212564,
   0.7205101,
   0.6956876,
   0.6528596,
   0.6307656,
   0.5936635,
   0.5906796,
   0.5708955,
   0.5745856,
   0.5326567,
   0.4990666};
   Double_t divide_num_LEp9_1D_A0_LZ_by_den_LEp9_1D_A0_LZ_felx3001[17] = {
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
   Double_t divide_num_LEp9_1D_A0_LZ_by_den_LEp9_1D_A0_LZ_fely3001[17] = {
   0.002141479,
   0.003879146,
   0.004866524,
   0.00562273,
   0.006247069,
   0.006925507,
   0.005524977,
   0.008701465,
   0.009563611,
   0.00668601,
   0.007590919,
   0.008795773,
   0.009918067,
   0.01095367,
   0.01259959,
   0.01071418,
   0.01277919};
   Double_t divide_num_LEp9_1D_A0_LZ_by_den_LEp9_1D_A0_LZ_fehx3001[17] = {
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
   Double_t divide_num_LEp9_1D_A0_LZ_by_den_LEp9_1D_A0_LZ_fehy3001[17] = {
   0.002103968,
   0.00380669,
   0.004775628,
   0.00551934,
   0.006124819,
   0.006798545,
   0.005459464,
   0.008541999,
   0.009400936,
   0.006627087,
   0.007527754,
   0.008737134,
   0.009846242,
   0.01088612,
   0.01250576,
   0.01068476,
   0.01278038};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(17,divide_num_LEp9_1D_A0_LZ_by_den_LEp9_1D_A0_LZ_fx3001,divide_num_LEp9_1D_A0_LZ_by_den_LEp9_1D_A0_LZ_fy3001,divide_num_LEp9_1D_A0_LZ_by_den_LEp9_1D_A0_LZ_felx3001,divide_num_LEp9_1D_A0_LZ_by_den_LEp9_1D_A0_LZ_fehx3001,divide_num_LEp9_1D_A0_LZ_by_den_LEp9_1D_A0_LZ_fely3001,divide_num_LEp9_1D_A0_LZ_by_den_LEp9_1D_A0_LZ_fehy3001);
   grae->SetName("divide_num_LEp9_1D_A0_LZ_by_den_LEp9_1D_A0_LZ");
   grae->SetTitle("num_LEp9_1D_A0_LZ");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_LEp9_1D_A0_LZ_by_den_LEp9_1D_A0_LZ3001 = new TH1F("Graph_divide_num_LEp9_1D_A0_LZ_by_den_LEp9_1D_A0_LZ3001","num_LEp9_1D_A0_LZ",100,0,88);
   Graph_divide_num_LEp9_1D_A0_LZ_by_den_LEp9_1D_A0_LZ3001->SetMinimum(0.445193);
   Graph_divide_num_LEp9_1D_A0_LZ_by_den_LEp9_1D_A0_LZ3001->SetMaximum(0.9383256);
   Graph_divide_num_LEp9_1D_A0_LZ_by_den_LEp9_1D_A0_LZ3001->SetDirectory(0);
   Graph_divide_num_LEp9_1D_A0_LZ_by_den_LEp9_1D_A0_LZ3001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_LEp9_1D_A0_LZ_by_den_LEp9_1D_A0_LZ3001->SetLineColor(ci);
   Graph_divide_num_LEp9_1D_A0_LZ_by_den_LEp9_1D_A0_LZ3001->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_LEp9_1D_A0_LZ_by_den_LEp9_1D_A0_LZ3001->GetXaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp9_1D_A0_LZ_by_den_LEp9_1D_A0_LZ3001->GetXaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp9_1D_A0_LZ_by_den_LEp9_1D_A0_LZ3001->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_LEp9_1D_A0_LZ_by_den_LEp9_1D_A0_LZ3001->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_LEp9_1D_A0_LZ_by_den_LEp9_1D_A0_LZ3001->GetYaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp9_1D_A0_LZ_by_den_LEp9_1D_A0_LZ3001->GetYaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp9_1D_A0_LZ_by_den_LEp9_1D_A0_LZ3001->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_LEp9_1D_A0_LZ_by_den_LEp9_1D_A0_LZ3001->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_LEp9_1D_A0_LZ_by_den_LEp9_1D_A0_LZ3001->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp9_1D_A0_LZ_by_den_LEp9_1D_A0_LZ3001->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp9_1D_A0_LZ_by_den_LEp9_1D_A0_LZ3001->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_LEp9_1D_A0_LZ_by_den_LEp9_1D_A0_LZ3001);
   
   multigraph->Add(grae,"");
   
   Double_t divide_num_LEp9_1D_A1_LZ_by_den_LEp9_1D_A1_LZ_fx3002[17] = {
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
   Double_t divide_num_LEp9_1D_A1_LZ_by_den_LEp9_1D_A1_LZ_fy3002[17] = {
   0.8531424,
   0.7921883,
   0.7525788,
   0.733484,
   0.7257401,
   0.7040936,
   0.6845928,
   0.689945,
   0.6755205,
   0.6558685,
   0.6298791,
   0.6132429,
   0.6029333,
   0.6002534,
   0.5854281,
   0.5798687,
   0.5705047};
   Double_t divide_num_LEp9_1D_A1_LZ_by_den_LEp9_1D_A1_LZ_felx3002[17] = {
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
   Double_t divide_num_LEp9_1D_A1_LZ_by_den_LEp9_1D_A1_LZ_fely3002[17] = {
   0.002507435,
   0.004282214,
   0.00527298,
   0.005957409,
   0.006546359,
   0.007145866,
   0.005587539,
   0.008539426,
   0.009112197,
   0.006168137,
   0.006920989,
   0.007592373,
   0.008150239,
   0.008907424,
   0.009615102,
   0.007427621,
   0.00630639};
   Double_t divide_num_LEp9_1D_A1_LZ_by_den_LEp9_1D_A1_LZ_fehx3002[17] = {
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
   Double_t divide_num_LEp9_1D_A1_LZ_by_den_LEp9_1D_A1_LZ_fehy3002[17] = {
   0.002472822,
   0.004218887,
   0.00519961,
   0.005875023,
   0.006452058,
   0.007048797,
   0.005535319,
   0.008414241,
   0.008983674,
   0.006116714,
   0.006868778,
   0.007538557,
   0.008094434,
   0.00884277,
   0.009551668,
   0.007392148,
   0.006283869};
   grae = new TGraphAsymmErrors(17,divide_num_LEp9_1D_A1_LZ_by_den_LEp9_1D_A1_LZ_fx3002,divide_num_LEp9_1D_A1_LZ_by_den_LEp9_1D_A1_LZ_fy3002,divide_num_LEp9_1D_A1_LZ_by_den_LEp9_1D_A1_LZ_felx3002,divide_num_LEp9_1D_A1_LZ_by_den_LEp9_1D_A1_LZ_fehx3002,divide_num_LEp9_1D_A1_LZ_by_den_LEp9_1D_A1_LZ_fely3002,divide_num_LEp9_1D_A1_LZ_by_den_LEp9_1D_A1_LZ_fehy3002);
   grae->SetName("divide_num_LEp9_1D_A1_LZ_by_den_LEp9_1D_A1_LZ");
   grae->SetTitle("num_LEp9_1D_A1_LZ");
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_LEp9_1D_A1_LZ_by_den_LEp9_1D_A1_LZ3002 = new TH1F("Graph_divide_num_LEp9_1D_A1_LZ_by_den_LEp9_1D_A1_LZ3002","num_LEp9_1D_A1_LZ",100,0,88);
   Graph_divide_num_LEp9_1D_A1_LZ_by_den_LEp9_1D_A1_LZ3002->SetMinimum(0.5350566);
   Graph_divide_num_LEp9_1D_A1_LZ_by_den_LEp9_1D_A1_LZ3002->SetMaximum(0.884757);
   Graph_divide_num_LEp9_1D_A1_LZ_by_den_LEp9_1D_A1_LZ3002->SetDirectory(0);
   Graph_divide_num_LEp9_1D_A1_LZ_by_den_LEp9_1D_A1_LZ3002->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_LEp9_1D_A1_LZ_by_den_LEp9_1D_A1_LZ3002->SetLineColor(ci);
   Graph_divide_num_LEp9_1D_A1_LZ_by_den_LEp9_1D_A1_LZ3002->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_LEp9_1D_A1_LZ_by_den_LEp9_1D_A1_LZ3002->GetXaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp9_1D_A1_LZ_by_den_LEp9_1D_A1_LZ3002->GetXaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp9_1D_A1_LZ_by_den_LEp9_1D_A1_LZ3002->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_LEp9_1D_A1_LZ_by_den_LEp9_1D_A1_LZ3002->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_LEp9_1D_A1_LZ_by_den_LEp9_1D_A1_LZ3002->GetYaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp9_1D_A1_LZ_by_den_LEp9_1D_A1_LZ3002->GetYaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp9_1D_A1_LZ_by_den_LEp9_1D_A1_LZ3002->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_LEp9_1D_A1_LZ_by_den_LEp9_1D_A1_LZ3002->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_LEp9_1D_A1_LZ_by_den_LEp9_1D_A1_LZ3002->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp9_1D_A1_LZ_by_den_LEp9_1D_A1_LZ3002->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp9_1D_A1_LZ_by_den_LEp9_1D_A1_LZ3002->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_LEp9_1D_A1_LZ_by_den_LEp9_1D_A1_LZ3002);
   
   multigraph->Add(grae,"");
   
   Double_t divide_num_Gp9_1D_A0_LZ_by_den_Gp9_1D_A0_LZ_fx3003[17] = {
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
   Double_t divide_num_Gp9_1D_A0_LZ_by_den_Gp9_1D_A0_LZ_fy3003[17] = {
   0.8538813,
   0.7920094,
   0.7666126,
   0.7486339,
   0.708,
   0.690205,
   0.6777368,
   0.7075718,
   0.7044855,
   0.6259542,
   0.6229299,
   0.5492021,
   0.5685997,
   0.5994398,
   0.5610465,
   0.5477569,
   0.5037199};
   Double_t divide_num_Gp9_1D_A0_LZ_by_den_Gp9_1D_A0_LZ_felx3003[17] = {
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
   Double_t divide_num_Gp9_1D_A0_LZ_by_den_Gp9_1D_A0_LZ_fely3003[17] = {
   0.009585602,
   0.0148519,
   0.01827991,
   0.01988458,
   0.02175039,
   0.02363857,
   0.01722222,
   0.02509052,
   0.02529511,
   0.01665726,
   0.01808581,
   0.01886442,
   0.01942043,
   0.0191695,
   0.01972383,
   0.01378051,
   0.01067769};
   Double_t divide_num_Gp9_1D_A0_LZ_by_den_Gp9_1D_A0_LZ_fehx3003[17] = {
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
   Double_t divide_num_Gp9_1D_A0_LZ_by_den_Gp9_1D_A0_LZ_fehy3003[17] = {
   0.009107405,
   0.01413715,
   0.01737545,
   0.01893532,
   0.02087856,
   0.0227286,
   0.01676892,
   0.02394757,
   0.02415716,
   0.01637337,
   0.01776134,
   0.01872888,
   0.01921918,
   0.01888057,
   0.01953972,
   0.01370956,
   0.01067437};
   grae = new TGraphAsymmErrors(17,divide_num_Gp9_1D_A0_LZ_by_den_Gp9_1D_A0_LZ_fx3003,divide_num_Gp9_1D_A0_LZ_by_den_Gp9_1D_A0_LZ_fy3003,divide_num_Gp9_1D_A0_LZ_by_den_Gp9_1D_A0_LZ_felx3003,divide_num_Gp9_1D_A0_LZ_by_den_Gp9_1D_A0_LZ_fehx3003,divide_num_Gp9_1D_A0_LZ_by_den_Gp9_1D_A0_LZ_fely3003,divide_num_Gp9_1D_A0_LZ_by_den_Gp9_1D_A0_LZ_fehy3003);
   grae->SetName("divide_num_Gp9_1D_A0_LZ_by_den_Gp9_1D_A0_LZ");
   grae->SetTitle("num_Gp9_1D_A0_LZ");

   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);
   grae->SetLineStyle(2);

   ci = TColor::GetColor("#ff0000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_Gp9_1D_A0_LZ_by_den_Gp9_1D_A0_LZ3003 = new TH1F("Graph_divide_num_Gp9_1D_A0_LZ_by_den_Gp9_1D_A0_LZ3003","num_Gp9_1D_A0_LZ",100,0,88);
   Graph_divide_num_Gp9_1D_A0_LZ_by_den_Gp9_1D_A0_LZ3003->SetMinimum(0.4560476);
   Graph_divide_num_Gp9_1D_A0_LZ_by_den_Gp9_1D_A0_LZ3003->SetMaximum(0.8999833);
   Graph_divide_num_Gp9_1D_A0_LZ_by_den_Gp9_1D_A0_LZ3003->SetDirectory(0);
   Graph_divide_num_Gp9_1D_A0_LZ_by_den_Gp9_1D_A0_LZ3003->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_Gp9_1D_A0_LZ_by_den_Gp9_1D_A0_LZ3003->SetLineColor(ci);
   Graph_divide_num_Gp9_1D_A0_LZ_by_den_Gp9_1D_A0_LZ3003->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_Gp9_1D_A0_LZ_by_den_Gp9_1D_A0_LZ3003->GetXaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp9_1D_A0_LZ_by_den_Gp9_1D_A0_LZ3003->GetXaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp9_1D_A0_LZ_by_den_Gp9_1D_A0_LZ3003->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_Gp9_1D_A0_LZ_by_den_Gp9_1D_A0_LZ3003->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_Gp9_1D_A0_LZ_by_den_Gp9_1D_A0_LZ3003->GetYaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp9_1D_A0_LZ_by_den_Gp9_1D_A0_LZ3003->GetYaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp9_1D_A0_LZ_by_den_Gp9_1D_A0_LZ3003->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_Gp9_1D_A0_LZ_by_den_Gp9_1D_A0_LZ3003->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_Gp9_1D_A0_LZ_by_den_Gp9_1D_A0_LZ3003->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp9_1D_A0_LZ_by_den_Gp9_1D_A0_LZ3003->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp9_1D_A0_LZ_by_den_Gp9_1D_A0_LZ3003->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_Gp9_1D_A0_LZ_by_den_Gp9_1D_A0_LZ3003);
   
   multigraph->Add(grae,"");
   
   Double_t divide_num_Gp9_1D_A1_LZ_by_den_Gp9_1D_A1_LZ_fx3004[17] = {
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
   Double_t divide_num_Gp9_1D_A1_LZ_by_den_Gp9_1D_A1_LZ_fy3004[17] = {
   0.8993787,
   0.8597064,
   0.8331528,
   0.8292994,
   0.8146154,
   0.7992734,
   0.7619048,
   0.7115385,
   0.7671033,
   0.7337317,
   0.6792157,
   0.6373057,
   0.635101,
   0.6104746,
   0.5914972,
   0.5353535,
   0.5229358};
   Double_t divide_num_Gp9_1D_A1_LZ_by_den_Gp9_1D_A1_LZ_felx3004[17] = {
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
   Double_t divide_num_Gp9_1D_A1_LZ_by_den_Gp9_1D_A1_LZ_fely3004[17] = {
   0.004108861,
   0.007367836,
   0.009133381,
   0.0100291,
   0.01141059,
   0.01280353,
   0.01038324,
   0.01656252,
   0.01725022,
   0.01187816,
   0.01360433,
   0.01613374,
   0.01790288,
   0.02071741,
   0.02221341,
   0.01838781,
   0.02233507};
   Double_t divide_num_Gp9_1D_A1_LZ_by_den_Gp9_1D_A1_LZ_fehx3004[17] = {
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
   Double_t divide_num_Gp9_1D_A1_LZ_by_den_Gp9_1D_A1_LZ_fehy3004[17] = {
   0.003968004,
   0.007065977,
   0.008761286,
   0.009595706,
   0.01090953,
   0.01223974,
   0.01008876,
   0.01603495,
   0.01643825,
   0.01155884,
   0.01331491,
   0.01583983,
   0.0175494,
   0.02034118,
   0.02186077,
   0.01829542,
   0.02224739};
   grae = new TGraphAsymmErrors(17,divide_num_Gp9_1D_A1_LZ_by_den_Gp9_1D_A1_LZ_fx3004,divide_num_Gp9_1D_A1_LZ_by_den_Gp9_1D_A1_LZ_fy3004,divide_num_Gp9_1D_A1_LZ_by_den_Gp9_1D_A1_LZ_felx3004,divide_num_Gp9_1D_A1_LZ_by_den_Gp9_1D_A1_LZ_fehx3004,divide_num_Gp9_1D_A1_LZ_by_den_Gp9_1D_A1_LZ_fely3004,divide_num_Gp9_1D_A1_LZ_by_den_Gp9_1D_A1_LZ_fehy3004);
   grae->SetName("divide_num_Gp9_1D_A1_LZ_by_den_Gp9_1D_A1_LZ");
   grae->SetTitle("num_Gp9_1D_A1_LZ");
   grae->SetLineStyle(2);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_Gp9_1D_A1_LZ_by_den_Gp9_1D_A1_LZ3004 = new TH1F("Graph_divide_num_Gp9_1D_A1_LZ_by_den_Gp9_1D_A1_LZ3004","num_Gp9_1D_A1_LZ",100,0,88);
   Graph_divide_num_Gp9_1D_A1_LZ_by_den_Gp9_1D_A1_LZ3004->SetMinimum(0.4603261);
   Graph_divide_num_Gp9_1D_A1_LZ_by_den_Gp9_1D_A1_LZ3004->SetMaximum(0.9436213);
   Graph_divide_num_Gp9_1D_A1_LZ_by_den_Gp9_1D_A1_LZ3004->SetDirectory(0);
   Graph_divide_num_Gp9_1D_A1_LZ_by_den_Gp9_1D_A1_LZ3004->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_Gp9_1D_A1_LZ_by_den_Gp9_1D_A1_LZ3004->SetLineColor(ci);
   Graph_divide_num_Gp9_1D_A1_LZ_by_den_Gp9_1D_A1_LZ3004->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_Gp9_1D_A1_LZ_by_den_Gp9_1D_A1_LZ3004->GetXaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp9_1D_A1_LZ_by_den_Gp9_1D_A1_LZ3004->GetXaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp9_1D_A1_LZ_by_den_Gp9_1D_A1_LZ3004->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_Gp9_1D_A1_LZ_by_den_Gp9_1D_A1_LZ3004->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_Gp9_1D_A1_LZ_by_den_Gp9_1D_A1_LZ3004->GetYaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp9_1D_A1_LZ_by_den_Gp9_1D_A1_LZ3004->GetYaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp9_1D_A1_LZ_by_den_Gp9_1D_A1_LZ3004->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_Gp9_1D_A1_LZ_by_den_Gp9_1D_A1_LZ3004->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_Gp9_1D_A1_LZ_by_den_Gp9_1D_A1_LZ3004->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp9_1D_A1_LZ_by_den_Gp9_1D_A1_LZ3004->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp9_1D_A1_LZ_by_den_Gp9_1D_A1_LZ3004->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_Gp9_1D_A1_LZ_by_den_Gp9_1D_A1_LZ3004);
   
   multigraph->Add(grae,"");
   multigraph->Draw("ALP");
   multigraph->GetXaxis()->SetTitle("L_{z} [cm]");
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
   TLegendEntry *entry=leg->AddEntry("divide_num_LEp9_1D_A0_LXY_by_den_LEp9_1D_A0_LXY","|#eta_{#gamma_{D}}| #leq 0.9 A0","L");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("divide_num_Gp9_1D_A0_LXY_by_den_Gp9_1D_A0_LXY","|#eta_{#gamma_{D}}| > 0.9 A0","L");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(2);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("divide_num_LEp9_1D_A1_LXY_by_den_LEp9_1D_A1_LXY","|#eta_{#gamma_{D}}| #leq 0.9 A1","L");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("divide_num_Gp9_1D_A1_LXY_by_den_Gp9_1D_A1_LXY","|#eta_{#gamma_{D}}| > 0.9 A1","L");
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
