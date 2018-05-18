void EfficiencyByEta_vs_Lz_Trig()
{
//=========Macro generated from canvas: eta_lz_trig/eta_lz_trig
//=========  (Sun May 13 10:47:26 2018) by ROOT version6.06/01
   TCanvas *eta_lz_trig = new TCanvas("eta_lz_trig", "eta_lz_trig",0,0,600,600);
   eta_lz_trig->Range(-12.8125,-0.1923077,55.9375,1.089744);
   eta_lz_trig->SetFillColor(0);
   eta_lz_trig->SetBorderMode(0);
   eta_lz_trig->SetBorderSize(2);
   eta_lz_trig->SetTickx(1);
   eta_lz_trig->SetTicky(1);
   eta_lz_trig->SetLeftMargin(0.15);
   eta_lz_trig->SetRightMargin(0.05);
   eta_lz_trig->SetTopMargin(0.07);
   eta_lz_trig->SetBottomMargin(0.15);
   eta_lz_trig->SetFrameFillStyle(0);
   eta_lz_trig->SetFrameBorderMode(0);
   eta_lz_trig->SetFrameFillStyle(0);
   eta_lz_trig->SetFrameBorderMode(0);
   
   TMultiGraph *multigraph = new TMultiGraph();
   multigraph->SetName("");
   multigraph->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");
   
   Double_t divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ_fx3033[5] = {
   1,
   3,
   5,
   7,
   9};
   Double_t divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ_fy3033[5] = {
   0.9377528,
   0.9197311,
   0.9345182,
   0.8901602,
   0.9159664};
   Double_t divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ_felx3033[5] = {
   1,
   1,
   1,
   1,
   1};
   Double_t divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ_fely3033[5] = {
   0.002348721,
   0.005773194,
   0.008468349,
   0.01705976,
   0.03369381};
   Double_t divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ_fehx3033[5] = {
   1,
   1,
   1,
   1,
   1};
   Double_t divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ_fehy3033[5] = {
   0.002270256,
   0.005429183,
   0.00760557,
   0.01514015,
   0.0255939};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(5,divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ_fx3033,divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ_fy3033,divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ_felx3033,divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ_fehx3033,divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ_fely3033,divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ_fehy3033);
   grae->SetName("divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ3033 = new TH1F("Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ3033","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,11);
   Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ3033->SetMinimum(0.8661981);
   Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ3033->SetMaximum(0.9490262);
   Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ3033->SetDirectory(0);
   Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ3033->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ3033->SetLineColor(ci);
   Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ3033->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ3033->GetXaxis()->SetLabelOffset(0.007);
   Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ3033->GetXaxis()->SetLabelSize(0.05);
   Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ3033->GetXaxis()->SetTitleSize(0.06);
   Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ3033->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ3033->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ3033->GetYaxis()->SetLabelOffset(0.007);
   Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ3033->GetYaxis()->SetLabelSize(0.05);
   Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ3033->GetYaxis()->SetTitleSize(0.06);
   Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ3033->GetYaxis()->SetTitleOffset(1.1);
   Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ3033->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ3033->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ3033->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ3033->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ3033->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ3033);
   
   multigraph->Add(grae,"");
   
   Double_t divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ_fx3034[15] = {
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
   47.5};
   Double_t divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ_fy3034[15] = {
   0.9358484,
   0.9056748,
   0.8695346,
   0.8640884,
   0.8192308,
   0.7783641,
   0.7550607,
   0.761194,
   0.8318584,
   0.8785714,
   0.8275862,
   0.7317073,
   0.8571429,
   0.7857143,
   1};
   Double_t divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ_felx3034[15] = {
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
   2.5};
   Double_t divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ_fely3034[15] = {
   0.002456038,
   0.006075976,
   0.009566934,
   0.0123634,
   0.01847474,
   0.02340952,
   0.02088662,
   0.04256684,
   0.04277737,
   0.03417687,
   0.05032337,
   0.08692182,
   0.09862525,
   0.1654735,
   0.2642294};
   Double_t divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ_fehx3034[15] = {
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
   2.5};
   Double_t divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ_fehy3034[15] = {
   0.002373038,
   0.00575452,
   0.009025398,
   0.0115203,
   0.01717848,
   0.02185228,
   0.01980132,
   0.03829406,
   0.03620311,
   0.02809718,
   0.04178929,
   0.07384712,
   0.06707849,
   0.1141996,
   0};
   grae = new TGraphAsymmErrors(15,divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ_fx3034,divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ_fy3034,divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ_felx3034,divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ_fehx3034,divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ_fely3034,divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ_fehy3034);
   grae->SetName("divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ3034 = new TH1F("Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ3034","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,55);
   Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ3034->SetMinimum(0.5822648);
   Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ3034->SetMaximum(1.037976);
   Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ3034->SetDirectory(0);
   Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ3034->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ3034->SetLineColor(ci);
   Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ3034->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ3034->GetXaxis()->SetLabelOffset(0.007);
   Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ3034->GetXaxis()->SetLabelSize(0.05);
   Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ3034->GetXaxis()->SetTitleSize(0.06);
   Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ3034->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ3034->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ3034->GetYaxis()->SetLabelOffset(0.007);
   Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ3034->GetYaxis()->SetLabelSize(0.05);
   Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ3034->GetYaxis()->SetTitleSize(0.06);
   Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ3034->GetYaxis()->SetTitleOffset(1.1);
   Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ3034->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ3034->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ3034->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ3034->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ3034->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ3034);
   
   multigraph->Add(grae,"");
   
   Double_t divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ_fx3035[15] = {
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
   47.5};
   Double_t divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ_fy3035[15] = {
   0.9022801,
   0.8639456,
   0.8284182,
   0.8322581,
   0.788,
   0.7647059,
   0.7820513,
   0.7564103,
   0.8510638,
   0.7352941,
   0.8181818,
   0.7826087,
   0.7,
   0.6,
   1};
   Double_t divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ_felx3035[15] = {
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
   2.5};
   Double_t divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ_fely3035[15] = {
   0.009224265,
   0.01564009,
   0.02178435,
   0.02396334,
   0.02904511,
   0.03514912,
   0.03037379,
   0.05837789,
   0.07097779,
   0.06431803,
   0.06736803,
   0.1203235,
   0.2082625,
   0.3033661,
   0.8413447};
   Double_t divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ_fehx3035[15] = {
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
   2.5};
   Double_t divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ_fehy3035[15] = {
   0.008537911,
   0.01432904,
   0.01990555,
   0.0216614,
   0.02656906,
   0.03208442,
   0.0277792,
   0.05099898,
   0.05324654,
   0.05652313,
   0.05394339,
   0.09048927,
   0.1583281,
   0.2533476,
   0};
   grae = new TGraphAsymmErrors(15,divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ_fx3035,divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ_fy3035,divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ_felx3035,divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ_fehx3035,divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ_fely3035,divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ_fehy3035);
   grae->SetName("divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");

   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);
   grae->SetLineStyle(2);

   ci = TColor::GetColor("#ff0000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ3035 = new TH1F("Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ3035","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,55);
   Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ3035->SetMinimum(0.07452078);
   Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ3035->SetMaximum(1.084134);
   Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ3035->SetDirectory(0);
   Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ3035->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ3035->SetLineColor(ci);
   Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ3035->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ3035->GetXaxis()->SetLabelOffset(0.007);
   Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ3035->GetXaxis()->SetLabelSize(0.05);
   Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ3035->GetXaxis()->SetTitleSize(0.06);
   Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ3035->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ3035->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ3035->GetYaxis()->SetLabelOffset(0.007);
   Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ3035->GetYaxis()->SetLabelSize(0.05);
   Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ3035->GetYaxis()->SetTitleSize(0.06);
   Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ3035->GetYaxis()->SetTitleOffset(1.1);
   Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ3035->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ3035->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ3035->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ3035->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ3035->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ3035);
   
   multigraph->Add(grae,"");
   
   Double_t divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ_fx3036[7] = {
   1,
   3,
   5,
   7,
   9,
   11,
   17};
   Double_t divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ_fy3036[7] = {
   0.9445585,
   0.9357639,
   0.9049296,
   0.9327731,
   0.8857143,
   1,
   1};
   Double_t divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ_felx3036[7] = {
   1,
   1,
   1,
   1,
   1,
   1,
   1};
   Double_t divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ_fely3036[7] = {
   0.004563841,
   0.01191169,
   0.02073337,
   0.03148319,
   0.08118009,
   0.8413447,
   0.8413447};
   Double_t divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ_fehx3036[7] = {
   1,
   1,
   1,
   1,
   1,
   1,
   1};
   Double_t divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ_fehy3036[7] = {
   0.004247307,
   0.01027163,
   0.01760003,
   0.02292857,
   0.05387941,
   0,
   0};
   grae = new TGraphAsymmErrors(7,divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ_fx3036,divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ_fy3036,divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ_felx3036,divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ_fehx3036,divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ_fely3036,divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ_fehy3036);
   grae->SetName("divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");
   grae->SetLineStyle(2);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ3036 = new TH1F("Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ3036","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,19.8);
   Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ3036->SetMinimum(0.07452078);
   Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ3036->SetMaximum(1.084134);
   Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ3036->SetDirectory(0);
   Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ3036->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ3036->SetLineColor(ci);
   Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ3036->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ3036->GetXaxis()->SetLabelOffset(0.007);
   Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ3036->GetXaxis()->SetLabelSize(0.05);
   Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ3036->GetXaxis()->SetTitleSize(0.06);
   Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ3036->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ3036->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ3036->GetYaxis()->SetLabelOffset(0.007);
   Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ3036->GetYaxis()->SetLabelSize(0.05);
   Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ3036->GetYaxis()->SetTitleSize(0.06);
   Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ3036->GetYaxis()->SetTitleOffset(1.1);
   Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ3036->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ3036->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ3036->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ3036->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ3036->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ3036);
   
   multigraph->Add(grae,"");
   multigraph->Draw("ALP");
   multigraph->GetXaxis()->SetTitle("L_{z} [cm]");
   multigraph->GetXaxis()->SetLabelFont(42);
   multigraph->GetXaxis()->SetLabelOffset(0.007);
   multigraph->GetXaxis()->SetLabelSize(0.05);
   multigraph->GetXaxis()->SetTitleSize(0.06);
   multigraph->GetXaxis()->SetTitleFont(42);
   multigraph->GetYaxis()->SetTitle("Efficiency");
   multigraph->GetYaxis()->SetLabelFont(42);
   multigraph->GetYaxis()->SetLabelOffset(0.007);
   multigraph->GetYaxis()->SetLabelSize(0.05);
   multigraph->GetYaxis()->SetTitleSize(0.06);
   multigraph->GetYaxis()->SetTitleOffset(1.1);
   multigraph->GetYaxis()->SetTitleFont(42);
   
   TPaveText *pt = new TPaveText(0,0.942,1,1,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *AText = pt->AddText("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");
   pt->Draw();
   TLine *line = new TLine(34.5,0,34.5,1);

   ci = TColor::GetColor("#0000ff");
   line->SetLineColor(ci);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   line = new TLine(46.5,0,46.5,1);

   ci = TColor::GetColor("#0000ff");
   line->SetLineColor(ci);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   
   TLegend *leg = new TLegend(0.6389685,0.2447257,0.8381089,0.4535865,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.05);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY","|#eta_{#gamma D1}| #leq 0.9","L");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY","|#eta_{#gamma D1}| > 0.9","L");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(2);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY","|#eta_{#gamma D2}| #leq 0.9","L");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY","|#eta_{#gamma D2}| > 0.9","L");
   entry->SetLineColor(1);
   entry->SetLineStyle(2);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   eta_lz_trig->Modified();
   eta_lz_trig->cd();
   eta_lz_trig->SetSelected(eta_lz_trig);
}
