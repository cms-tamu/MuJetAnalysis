void EfficiencyByEta_1D_vs_Lz_Trig_0to12()
{
//=========Macro generated from canvas: eta_lz_trig/eta_lz_trig
//=========  (Sun May 13 03:03:07 2018) by ROOT version6.06/01
   TCanvas *eta_lz_trig = new TCanvas("eta_lz_trig", "eta_lz_trig",1,1,600,576);
   eta_lz_trig->Range(-2.25,-0.1923077,12.75,1.089744);
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
   
   Double_t divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ_fx3037[1] = {
   1};
   Double_t divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ_fy3037[1] = {
   0.9637306};
   Double_t divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ_felx3037[1] = {
   1};
   Double_t divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ_fely3037[1] = {
   0.007067235};
   Double_t divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ_fehx3037[1] = {
   1};
   Double_t divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ_fehy3037[1] = {
   0.006023907};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(1,divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ_fx3037,divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ_fy3037,divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ_felx3037,divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ_fehx3037,divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ_fely3037,divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ_fehy3037);
   grae->SetName("divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ30333037 = new TH1F("Graph_Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ30333037","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,2.2);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ30333037->SetMinimum(0.9553542);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ30333037->SetMaximum(0.9710636);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ30333037->SetDirectory(0);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ30333037->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ30333037->SetLineColor(ci);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ30333037->GetXaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ30333037->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ30333037->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ30333037->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ30333037->GetXaxis()->SetTitleFont(42);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ30333037->GetYaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ30333037->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ30333037->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ30333037->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ30333037->GetYaxis()->SetTitleOffset(1.1);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ30333037->GetYaxis()->SetTitleFont(42);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ30333037->GetZaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ30333037->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ30333037->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ30333037->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph_divide_num_Trig_LEp8_1D_A0_LZ_by_den_Trig_LEp8_1D_A0_LZ30333037);
   
   multigraph->Add(grae,"");
   
   Double_t divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ_fx3038[1] = {
   1};
   Double_t divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ_fy3038[1] = {
   0.9675785};
   Double_t divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ_felx3038[1] = {
   1};
   Double_t divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ_fely3038[1] = {
   0.006670074};
   Double_t divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ_fehx3038[1] = {
   1};
   Double_t divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ_fehy3038[1] = {
   0.005637947};
   grae = new TGraphAsymmErrors(1,divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ_fx3038,divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ_fy3038,divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ_felx3038,divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ_fehx3038,divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ_fely3038,divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ_fehy3038);
   grae->SetName("divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ30343038 = new TH1F("Graph_Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ30343038","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,2.2);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ30343038->SetMinimum(0.9596776);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ30343038->SetMaximum(0.9744473);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ30343038->SetDirectory(0);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ30343038->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ30343038->SetLineColor(ci);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ30343038->GetXaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ30343038->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ30343038->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ30343038->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ30343038->GetXaxis()->SetTitleFont(42);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ30343038->GetYaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ30343038->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ30343038->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ30343038->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ30343038->GetYaxis()->SetTitleOffset(1.1);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ30343038->GetYaxis()->SetTitleFont(42);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ30343038->GetZaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ30343038->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ30343038->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ30343038->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph_divide_num_Trig_LEp8_1D_A1_LZ_by_den_Trig_LEp8_1D_A1_LZ30343038);
   
   multigraph->Add(grae,"");
   
   Double_t divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ_fx3039[1] = {
   1};
   Double_t divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ_fy3039[1] = {
   0.8907563};
   Double_t divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ_felx3039[1] = {
   1};
   Double_t divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ_fely3039[1] = {
   0.02412098};
   Double_t divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ_fehx3039[1] = {
   1};
   Double_t divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ_fehy3039[1] = {
   0.02050558};
   grae = new TGraphAsymmErrors(1,divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ_fx3039,divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ_fy3039,divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ_felx3039,divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ_fehx3039,divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ_fely3039,divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ_fehy3039);
   grae->SetName("divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");

   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);
   grae->SetLineStyle(2);

   ci = TColor::GetColor("#ff0000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ30353039 = new TH1F("Graph_Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ30353039","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,2.2);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ30353039->SetMinimum(0.8621727);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ30353039->SetMaximum(0.9157245);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ30353039->SetDirectory(0);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ30353039->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ30353039->SetLineColor(ci);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ30353039->GetXaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ30353039->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ30353039->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ30353039->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ30353039->GetXaxis()->SetTitleFont(42);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ30353039->GetYaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ30353039->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ30353039->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ30353039->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ30353039->GetYaxis()->SetTitleOffset(1.1);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ30353039->GetYaxis()->SetTitleFont(42);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ30353039->GetZaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ30353039->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ30353039->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ30353039->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph_divide_num_Trig_Gp8_1D_A0_LZ_by_den_Trig_Gp8_1D_A0_LZ30353039);
   
   multigraph->Add(grae,"");
   
   Double_t divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ_fx3040[1] = {
   1};
   Double_t divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ_fy3040[1] = {
   0.9583333};
   Double_t divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ_felx3040[1] = {
   1};
   Double_t divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ_fely3040[1] = {
   0.01724894};
   Double_t divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ_fehx3040[1] = {
   1};
   Double_t divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ_fehy3040[1] = {
   0.01282478};
   grae = new TGraphAsymmErrors(1,divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ_fx3040,divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ_fy3040,divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ_felx3040,divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ_fehx3040,divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ_fely3040,divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ_fehy3040);
   grae->SetName("divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");
   grae->SetLineStyle(2);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ30363040 = new TH1F("Graph_Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ30363040","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,2.2);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ30363040->SetMinimum(0.938077);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ30363040->SetMaximum(0.9741655);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ30363040->SetDirectory(0);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ30363040->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ30363040->SetLineColor(ci);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ30363040->GetXaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ30363040->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ30363040->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ30363040->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ30363040->GetXaxis()->SetTitleFont(42);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ30363040->GetYaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ30363040->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ30363040->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ30363040->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ30363040->GetYaxis()->SetTitleOffset(1.1);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ30363040->GetYaxis()->SetTitleFont(42);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ30363040->GetZaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ30363040->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ30363040->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ30363040->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph_divide_num_Trig_Gp8_1D_A1_LZ_by_den_Trig_Gp8_1D_A1_LZ30363040);
   
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
   TLine *line = new TLine(4,0,4,1);

   ci = TColor::GetColor("#0000ff");
   line->SetLineColor(ci);
   line->SetLineStyle(2);
   line->Draw();
   line = new TLine(6.9,0,6.9,1);

   ci = TColor::GetColor("#0000ff");
   line->SetLineColor(ci);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   line = new TLine(9.8,0,9.8,1);

   ci = TColor::GetColor("#0000ff");
   line->SetLineColor(ci);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   line = new TLine(23.9,0,23.9,1);

   ci = TColor::GetColor("#00cc00");
   line->SetLineColor(ci);
   line->SetLineStyle(2);
   line->Draw();
   line = new TLine(60.5,0,60.5,1);

   ci = TColor::GetColor("#00cc00");
   line->SetLineColor(ci);
   line->SetLineStyle(2);
   line->Draw();
   
   TPaveText *pt = new TPaveText(0,0.942,1,1,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *AText = pt->AddText("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");
   pt->Draw();
   eta_lz_trig->Modified();
   eta_lz_trig->cd();
   eta_lz_trig->SetSelected(eta_lz_trig);
}
