void EfficiencyByEta_vs_Lz_Trig()
{
//=========Macro generated from canvas: eta_lz_trig/eta_lz_trig
//=========  (Sun May 13 03:03:07 2018) by ROOT version6.06/01
   TCanvas *eta_lz_trig = new TCanvas("eta_lz_trig", "eta_lz_trig",0,0,600,600);
   eta_lz_trig->Range(-0.5125,-0.1923077,2.2375,1.089744);
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
   
   Double_t divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ_fx3033[1] = {
   1};
   Double_t divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ_fy3033[1] = {
   0.9637306};
   Double_t divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ_felx3033[1] = {
   1};
   Double_t divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ_fely3033[1] = {
   0.007067235};
   Double_t divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ_fehx3033[1] = {
   1};
   Double_t divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ_fehy3033[1] = {
   0.006023907};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(1,divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ_fx3033,divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ_fy3033,divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ_felx3033,divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ_fehx3033,divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ_fely3033,divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ_fehy3033);
   grae->SetName("divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ3033 = new TH1F("Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ3033","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,2.2);
   Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ3033->SetMinimum(0.9553542);
   Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ3033->SetMaximum(0.9710636);
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
   
   Double_t divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ_fx3034[1] = {
   1};
   Double_t divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ_fy3034[1] = {
   0.9675785};
   Double_t divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ_felx3034[1] = {
   1};
   Double_t divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ_fely3034[1] = {
   0.006670074};
   Double_t divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ_fehx3034[1] = {
   1};
   Double_t divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ_fehy3034[1] = {
   0.005637947};
   grae = new TGraphAsymmErrors(1,divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ_fx3034,divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ_fy3034,divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ_felx3034,divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ_fehx3034,divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ_fely3034,divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ_fehy3034);
   grae->SetName("divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ3034 = new TH1F("Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ3034","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,2.2);
   Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ3034->SetMinimum(0.9596776);
   Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ3034->SetMaximum(0.9744473);
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
   
   Double_t divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ_fx3035[1] = {
   1};
   Double_t divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ_fy3035[1] = {
   0.8907563};
   Double_t divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ_felx3035[1] = {
   1};
   Double_t divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ_fely3035[1] = {
   0.02412098};
   Double_t divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ_fehx3035[1] = {
   1};
   Double_t divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ_fehy3035[1] = {
   0.02050558};
   grae = new TGraphAsymmErrors(1,divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ_fx3035,divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ_fy3035,divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ_felx3035,divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ_fehx3035,divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ_fely3035,divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ_fehy3035);
   grae->SetName("divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");

   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);
   grae->SetLineStyle(2);

   ci = TColor::GetColor("#ff0000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ3035 = new TH1F("Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ3035","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,2.2);
   Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ3035->SetMinimum(0.8621727);
   Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ3035->SetMaximum(0.9157245);
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
   
   Double_t divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ_fx3036[1] = {
   1};
   Double_t divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ_fy3036[1] = {
   0.9583333};
   Double_t divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ_felx3036[1] = {
   1};
   Double_t divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ_fely3036[1] = {
   0.01724894};
   Double_t divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ_fehx3036[1] = {
   1};
   Double_t divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ_fehy3036[1] = {
   0.01282478};
   grae = new TGraphAsymmErrors(1,divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ_fx3036,divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ_fy3036,divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ_felx3036,divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ_fehx3036,divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ_fely3036,divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ_fehy3036);
   grae->SetName("divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");
   grae->SetLineStyle(2);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ3036 = new TH1F("Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ3036","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,2.2);
   Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ3036->SetMinimum(0.938077);
   Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ3036->SetMaximum(0.9741655);
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
