void EfficiencyByEta_vs_Lz()
{
//=========Macro generated from canvas: eta_lz/eta_lz
//=========  (Mon Mar  7 08:02:08 2016) by ROOT version6.02/05
   TCanvas *eta_lz = new TCanvas("eta_lz", "eta_lz",321,1245,700,500);
   eta_lz->Range(-15,-0.125,95,1.125);
   eta_lz->SetFillColor(0);
   eta_lz->SetBorderMode(0);
   eta_lz->SetBorderSize(2);
   eta_lz->SetFrameBorderMode(0);
   eta_lz->SetFrameBorderMode(0);
   
   TMultiGraph *multigraph = new TMultiGraph();
   multigraph->SetName("");
   multigraph->SetTitle("");
   
   Double_t divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fx3001[17] = {
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
   Double_t divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fy3001[17] = {
   0.9080298,
   0.8202334,
   0.7553908,
   0.7090909,
   0.670787,
   0.6224337,
   0.5515311,
   0.4741744,
   0.4378014,
   0.3948586,
   0.3029491,
   0.2437673,
   0.1630435,
   0.1233333,
   0.05417607,
   0.004065041,
   0.005617978};
   Double_t divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_felx3001[17] = {
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
   Double_t divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fely3001[17] = {
   0.001541312,
   0.004453759,
   0.006612443,
   0.008263867,
   0.009814857,
   0.01115846,
   0.009204997,
   0.01492435,
   0.01581867,
   0.0112827,
   0.01209253,
   0.01325854,
   0.01301159,
   0.01358835,
   0.01078914,
   0.002625212,
   0.004647921};
   Double_t divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fehx3001[17] = {
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
   Double_t divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fehy3001[17] = {
   0.001518644,
   0.004370433,
   0.006495727,
   0.008130245,
   0.009671114,
   0.01103306,
   0.00917045,
   0.01496934,
   0.01594231,
   0.01139329,
   0.012364,
   0.0137482,
   0.01386317,
   0.01492055,
   0.01301025,
   0.005336259,
   0.01279935};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(17,divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fx3001,divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fy3001,divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_felx3001,divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fehx3001,divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fely3001,divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fehy3001);
   grae->SetName("divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ");
   grae->SetTitle("num_LEp8_1D_A0_LZ");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3001 = new TH1F("Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3001","num_LEp8_1D_A0_LZ",100,0,88);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3001->SetMinimum(0);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3001->SetMaximum(1.000406);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3001->SetDirectory(0);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3001->SetLineColor(ci);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3001->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3001->GetXaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3001->GetXaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3001->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3001->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3001->GetYaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3001->GetYaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3001->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3001->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3001->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3001->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3001->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3001);
   
   multigraph->Add(grae,"");
   
   Double_t divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fx3002[17] = {
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
   Double_t divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fy3002[17] = {
   0.9043252,
   0.790366,
   0.7452243,
   0.6891468,
   0.647705,
   0.6043902,
   0.5508524,
   0.5215094,
   0.4822203,
   0.4753036,
   0.3975904,
   0.3444882,
   0.2953822,
   0.2689721,
   0.2352321,
   0.2118467,
   0.1684266};
   Double_t divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_felx3002[17] = {
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
   Double_t divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fely3002[17] = {
   0.001634743,
   0.004828313,
   0.006544022,
   0.008413468,
   0.009714908,
   0.01109307,
   0.008688844,
   0.01411191,
   0.01512672,
   0.01023838,
   0.01140515,
   0.01239205,
   0.01309829,
   0.01398831,
   0.01400723,
   0.01092521,
   0.008681733};
   Double_t divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fehx3002[17] = {
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
   Double_t divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fehy3002[17] = {
   0.001610364,
   0.004749066,
   0.006436997,
   0.008292559,
   0.00959664,
   0.01098896,
   0.008658439,
   0.01407857,
   0.01515845,
   0.01025878,
   0.01151492,
   0.01260155,
   0.01343403,
   0.01444742,
   0.01458683,
   0.01133962,
   0.009042502};
   grae = new TGraphAsymmErrors(17,divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fx3002,divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fy3002,divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_felx3002,divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fehx3002,divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fely3002,divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fehy3002);
   grae->SetName("divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ");
   grae->SetTitle("num_LEp8_1D_A1_LZ");
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3002 = new TH1F("Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3002","num_LEp8_1D_A1_LZ",100,0,88);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3002->SetMinimum(0.08512581);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3002->SetMaximum(0.9805547);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3002->SetDirectory(0);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3002->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3002->SetLineColor(ci);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3002->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3002->GetXaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3002->GetXaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3002->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3002->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3002->GetYaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3002->GetYaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3002->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3002->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3002->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3002->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3002->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3002);
   
   multigraph->Add(grae,"");
   
   Double_t divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fx3003[17] = {
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
   Double_t divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fy3003[17] = {
   0.9137676,
   0.8726961,
   0.8518519,
   0.7936772,
   0.7884406,
   0.7881706,
   0.7514079,
   0.7118644,
   0.7027027,
   0.6429259,
   0.5347222,
   0.4498607,
   0.4194915,
   0.4225092,
   0.3761468,
   0.2380952,
   0.1374374};
   Double_t divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_felx3003[17] = {
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
   Double_t divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fely3003[17] = {
   0.003377242,
   0.007279377,
   0.009358388,
   0.01233732,
   0.01435381,
   0.01624815,
   0.01286564,
   0.02099558,
   0.02230088,
   0.01548052,
   0.01757905,
   0.01917595,
   0.01912036,
   0.02196986,
   0.02141066,
   0.01425232,
   0.009299189};
   Double_t divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fehx3003[17] = {
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
   Double_t divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fehy3003[17] = {
   0.003263802,
   0.006950033,
   0.008908972,
   0.01183151,
   0.01369971,
   0.0154201,
   0.01244805,
   0.02016033,
   0.02141713,
   0.01519666,
   0.01749599,
   0.01932073,
   0.01935624,
   0.0222679,
   0.02188472,
   0.01484072,
   0.009838194};
   grae = new TGraphAsymmErrors(17,divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fx3003,divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fy3003,divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_felx3003,divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fehx3003,divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fely3003,divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fehy3003);
   grae->SetName("divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ");
   grae->SetTitle("num_Gp8_1D_A0_LZ");

   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);
   grae->SetLineStyle(2);

   ci = TColor::GetColor("#ff0000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3003 = new TH1F("Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3003","num_Gp8_1D_A0_LZ",100,0,88);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3003->SetMinimum(0.04924885);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3003->SetMaximum(0.9959208);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3003->SetDirectory(0);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3003->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3003->SetLineColor(ci);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3003->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3003->GetXaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3003->GetXaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3003->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3003->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3003->GetYaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3003->GetYaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3003->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3003->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3003->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3003->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3003->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3003);
   
   multigraph->Add(grae,"");
   
   Double_t divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fx3004[17] = {
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
   Double_t divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fy3004[17] = {
   0.9168931,
   0.827886,
   0.7737686,
   0.7452504,
   0.6772031,
   0.6503145,
   0.6317539,
   0.5810526,
   0.5179856,
   0.4847775,
   0.3793103,
   0.3253968,
   0.2425,
   0.2758621,
   0.2034483,
   0.1534653,
   0.08866995};
   Double_t divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_felx3004[17] = {
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
   Double_t divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fely3004[17] = {
   0.002468044,
   0.007328789,
   0.01045828,
   0.01345009,
   0.01511763,
   0.01772701,
   0.01442878,
   0.02384346,
   0.02568126,
   0.01765808,
   0.01852453,
   0.02147849,
   0.02197595,
   0.0258088,
   0.02423641,
   0.01824262,
   0.01424295};
   Double_t divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fehx3004[17] = {
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
   Double_t divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fehy3004[17] = {
   0.002404119,
   0.007095188,
   0.01013583,
   0.01301246,
   0.01476713,
   0.0173351,
   0.01420331,
   0.02348679,
   0.0255909,
   0.01769492,
   0.01886992,
   0.0222034,
   0.02333645,
   0.02729915,
   0.02642606,
   0.02007379,
   0.01644289};
   grae = new TGraphAsymmErrors(17,divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fx3004,divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fy3004,divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_felx3004,divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fehx3004,divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fely3004,divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fehy3004);
   grae->SetName("divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ");
   grae->SetTitle("num_Gp8_1D_A1_LZ");
   grae->SetLineStyle(2);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3004 = new TH1F("Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3004","num_Gp8_1D_A1_LZ",100,0,88);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3004->SetMinimum(0);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3004->SetMaximum(1.003784);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3004->SetDirectory(0);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3004->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3004->SetLineColor(ci);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3004->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3004->GetXaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3004->GetXaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3004->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3004->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3004->GetYaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3004->GetYaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3004->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3004->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3004->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3004->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3004->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3004);
   
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
   TLegendEntry *entry=leg->AddEntry("divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY","|#eta_{#gamma D}| #leq 0.8 A0","L");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY","|#eta_{#gamma D}| > 0.8 A0","L");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(2);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY","|#eta_{#gamma D}| #leq 0.8 A1","L");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY","|#eta_{#gamma D}| > 0.8 A1","L");
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
