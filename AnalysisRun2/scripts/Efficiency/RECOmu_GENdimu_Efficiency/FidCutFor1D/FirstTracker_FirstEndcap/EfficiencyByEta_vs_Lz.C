void EfficiencyByEta_vs_Lz()
{
//=========Macro generated from canvas: eta_lz/eta_lz
//=========  (Tue Apr  5 07:29:20 2016) by ROOT version6.02/05
   TCanvas *eta_lz = new TCanvas("eta_lz", "eta_lz",0,0,700,500);
   eta_lz->Range(-6.5625,-0.125,41.5625,1.125);
   eta_lz->SetFillColor(0);
   eta_lz->SetBorderMode(0);
   eta_lz->SetBorderSize(2);
   eta_lz->SetFrameBorderMode(0);
   eta_lz->SetFrameBorderMode(0);
   
   TMultiGraph *multigraph = new TMultiGraph();
   multigraph->SetName("");
   multigraph->SetTitle("");
   
   Double_t divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fx3001[10] = {
   1,
   3,
   5,
   7,
   9,
   11,
   14,
   17,
   19,
   22.5};
   Double_t divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fy3001[10] = {
   0.9255811,
   0.887184,
   0.8789174,
   0.8852085,
   0.8950226,
   0.8479381,
   0.7993119,
   0.7869822,
   0.7105263,
   0.5384615};
   Double_t divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_felx3001[10] = {
   1,
   1,
   1,
   1,
   1,
   1,
   2,
   1,
   1,
   2.5};
   Double_t divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fely3001[10] = {
   0.001480903,
   0.00433367,
   0.006472957,
   0.00813138,
   0.01004846,
   0.01400104,
   0.0144885,
   0.03622352,
   0.06131092,
   0.1720041};
   Double_t divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fehx3001[10] = {
   1,
   1,
   1,
   1,
   1,
   1,
   2,
   1,
   1,
   2.5};
   Double_t divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fehy3001[10] = {
   0.001454562,
   0.00419584,
   0.006195321,
   0.007675046,
   0.009298784,
   0.01306018,
   0.01377348,
   0.03252222,
   0.05512412,
   0.1648473};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(10,divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fx3001,divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fy3001,divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_felx3001,divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fehx3001,divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fely3001,divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fehy3001);
   grae->SetName("divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ");
   grae->SetTitle("num_LEp8_1D_A0_LZ");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3001 = new TH1F("Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3001","num_LEp8_1D_A0_LZ",100,0,27.5);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3001->SetMinimum(0.3103996);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3001->SetMaximum(0.9830935);
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
   
   Double_t divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fx3002[12] = {
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
   32.5};
   Double_t divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fy3002[12] = {
   0.9399291,
   0.9001285,
   0.8902202,
   0.8792473,
   0.8573519,
   0.8445122,
   0.8166895,
   0.7649485,
   0.7375,
   0.7456576,
   0.6967871,
   0.7176871};
   Double_t divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_felx3002[12] = {
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
   2.5};
   Double_t divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fely3002[12] = {
   0.001405873,
   0.004229466,
   0.005917511,
   0.007916015,
   0.01009448,
   0.01242246,
   0.01068294,
   0.02084312,
   0.0238508,
   0.01626845,
   0.02199496,
   0.02869559};
   Double_t divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fehx3002[12] = {
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
   2.5};
   Double_t divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fehy3002[12] = {
   0.001376087,
   0.004079244,
   0.005657549,
   0.007505729,
   0.00955166,
   0.01169187,
   0.01023525,
   0.01969351,
   0.02259777,
   0.01563471,
   0.02116716,
   0.02712215};
   grae = new TGraphAsymmErrors(12,divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fx3002,divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fy3002,divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_felx3002,divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fehx3002,divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fely3002,divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fehy3002);
   grae->SetName("divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ");
   grae->SetTitle("num_LEp8_1D_A1_LZ");
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3002 = new TH1F("Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3002","num_LEp8_1D_A1_LZ",100,0,38.5);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3002->SetMinimum(0.6481409);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3002->SetMaximum(0.9679565);
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
   
   Double_t divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fx3003[12] = {
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
   32.5};
   Double_t divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fy3003[12] = {
   0.9226259,
   0.8929907,
   0.878169,
   0.835122,
   0.8467742,
   0.8478632,
   0.8158954,
   0.7928389,
   0.7811634,
   0.735119,
   0.7272727,
   0.6801802};
   Double_t divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_felx3003[12] = {
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
   2.5};
   Double_t divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fely3003[12] = {
   0.003328733,
   0.007105987,
   0.009308612,
   0.01241554,
   0.01436289,
   0.0163258,
   0.01312262,
   0.02254821,
   0.02394814,
   0.01811984,
   0.0258094,
   0.03434908};
   Double_t divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fehx3003[12] = {
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
   2.5};
   Double_t divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fehy3003[12] = {
   0.003205148,
   0.006725961,
   0.008754592,
   0.01173451,
   0.01338404,
   0.01506936,
   0.0124614,
   0.02095935,
   0.02229414,
   0.01739016,
   0.02444323,
   0.032614};
   grae = new TGraphAsymmErrors(12,divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fx3003,divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fy3003,divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_felx3003,divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fehx3003,divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fely3003,divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fehy3003);
   grae->SetName("divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ");
   grae->SetTitle("num_Gp8_1D_A0_LZ");

   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);
   grae->SetLineStyle(2);

   ci = TColor::GetColor("#ff0000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3003 = new TH1F("Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3003","num_Gp8_1D_A0_LZ",100,0,38.5);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3003->SetMinimum(0.6178311);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3003->SetMaximum(0.953831);
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
   
   Double_t divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fx3004[12] = {
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
   32.5};
   Double_t divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fy3004[12] = {
   0.9385068,
   0.9029813,
   0.8920233,
   0.8859935,
   0.8653061,
   0.8677419,
   0.8693467,
   0.7536232,
   0.7717391,
   0.7142857,
   0.7833333,
   0.7941176};
   Double_t divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_felx3004[12] = {
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
   2.5};
   Double_t divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fely3004[12] = {
   0.002317847,
   0.007117628,
   0.01056605,
   0.01430681,
   0.01723106,
   0.02212471,
   0.0191375,
   0.0421842,
   0.05225554,
   0.0459041,
   0.06646625,
   0.09317978};
   Double_t divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fehx3004[12] = {
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
   2.5};
   Double_t divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fehy3004[12] = {
   0.002240421,
   0.00669502,
   0.009765471,
   0.01297094,
   0.0156433,
   0.01955835,
   0.01714648,
   0.03816421,
   0.04566168,
   0.04218646,
   0.05566409,
   0.07263947};
   grae = new TGraphAsymmErrors(12,divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fx3004,divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fy3004,divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_felx3004,divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fehx3004,divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fely3004,divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fehy3004);
   grae->SetName("divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ");
   grae->SetTitle("num_Gp8_1D_A1_LZ");
   grae->SetLineStyle(2);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3004 = new TH1F("Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3004","num_Gp8_1D_A1_LZ",100,0,38.5);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3004->SetMinimum(0.6411451);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3004->SetMaximum(0.9679838);
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
