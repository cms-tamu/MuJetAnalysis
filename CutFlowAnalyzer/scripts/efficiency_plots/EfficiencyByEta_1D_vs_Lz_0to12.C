void EfficiencyByEta_1D_vs_Lz_0to12()
{
//=========Macro generated from canvas: eta_lz/eta_lz
//=========  (Sun May 13 03:03:07 2018) by ROOT version6.06/01
   TCanvas *eta_lz = new TCanvas("eta_lz", "eta_lz",1,1,600,576);
   eta_lz->Range(-2.25,-0.1923077,12.75,1.089744);
   eta_lz->SetFillColor(0);
   eta_lz->SetBorderMode(0);
   eta_lz->SetBorderSize(2);
   eta_lz->SetTickx(1);
   eta_lz->SetTicky(1);
   eta_lz->SetLeftMargin(0.15);
   eta_lz->SetRightMargin(0.05);
   eta_lz->SetTopMargin(0.07);
   eta_lz->SetBottomMargin(0.15);
   eta_lz->SetFrameFillStyle(0);
   eta_lz->SetFrameBorderMode(0);
   eta_lz->SetFrameFillStyle(0);
   eta_lz->SetFrameBorderMode(0);
   
   TMultiGraph *multigraph = new TMultiGraph();
   multigraph->SetName("");
   multigraph->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");
   
   Double_t divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fx3021[1] = {
   1};
   Double_t divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fy3021[1] = {
   0.9637306};
   Double_t divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_felx3021[1] = {
   1};
   Double_t divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fely3021[1] = {
   0.007067235};
   Double_t divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fehx3021[1] = {
   1};
   Double_t divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fehy3021[1] = {
   0.006023907};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(1,divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fx3021,divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fy3021,divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_felx3021,divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fehx3021,divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fely3021,divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fehy3021);
   grae->SetName("divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ30173021 = new TH1F("Graph_Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ30173021","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,2.2);
   Graph_Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ30173021->SetMinimum(0.9553542);
   Graph_Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ30173021->SetMaximum(0.9710636);
   Graph_Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ30173021->SetDirectory(0);
   Graph_Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ30173021->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ30173021->SetLineColor(ci);
   Graph_Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ30173021->GetXaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ30173021->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ30173021->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ30173021->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ30173021->GetXaxis()->SetTitleFont(42);
   Graph_Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ30173021->GetYaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ30173021->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ30173021->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ30173021->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ30173021->GetYaxis()->SetTitleOffset(1.1);
   Graph_Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ30173021->GetYaxis()->SetTitleFont(42);
   Graph_Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ30173021->GetZaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ30173021->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ30173021->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ30173021->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ30173021);
   
   multigraph->Add(grae,"");
   
   Double_t divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fx3022[1] = {
   1};
   Double_t divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fy3022[1] = {
   0.9675785};
   Double_t divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_felx3022[1] = {
   1};
   Double_t divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fely3022[1] = {
   0.006670074};
   Double_t divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fehx3022[1] = {
   1};
   Double_t divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fehy3022[1] = {
   0.005637947};
   grae = new TGraphAsymmErrors(1,divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fx3022,divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fy3022,divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_felx3022,divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fehx3022,divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fely3022,divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fehy3022);
   grae->SetName("divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ30183022 = new TH1F("Graph_Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ30183022","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,2.2);
   Graph_Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ30183022->SetMinimum(0.9596776);
   Graph_Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ30183022->SetMaximum(0.9744473);
   Graph_Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ30183022->SetDirectory(0);
   Graph_Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ30183022->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ30183022->SetLineColor(ci);
   Graph_Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ30183022->GetXaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ30183022->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ30183022->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ30183022->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ30183022->GetXaxis()->SetTitleFont(42);
   Graph_Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ30183022->GetYaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ30183022->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ30183022->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ30183022->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ30183022->GetYaxis()->SetTitleOffset(1.1);
   Graph_Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ30183022->GetYaxis()->SetTitleFont(42);
   Graph_Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ30183022->GetZaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ30183022->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ30183022->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ30183022->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ30183022);
   
   multigraph->Add(grae,"");
   
   Double_t divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fx3023[1] = {
   1};
   Double_t divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fy3023[1] = {
   0.8907563};
   Double_t divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_felx3023[1] = {
   1};
   Double_t divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fely3023[1] = {
   0.02412098};
   Double_t divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fehx3023[1] = {
   1};
   Double_t divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fehy3023[1] = {
   0.02050558};
   grae = new TGraphAsymmErrors(1,divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fx3023,divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fy3023,divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_felx3023,divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fehx3023,divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fely3023,divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fehy3023);
   grae->SetName("divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");

   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);
   grae->SetLineStyle(2);

   ci = TColor::GetColor("#ff0000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ30193023 = new TH1F("Graph_Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ30193023","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,2.2);
   Graph_Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ30193023->SetMinimum(0.8621727);
   Graph_Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ30193023->SetMaximum(0.9157245);
   Graph_Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ30193023->SetDirectory(0);
   Graph_Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ30193023->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ30193023->SetLineColor(ci);
   Graph_Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ30193023->GetXaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ30193023->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ30193023->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ30193023->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ30193023->GetXaxis()->SetTitleFont(42);
   Graph_Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ30193023->GetYaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ30193023->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ30193023->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ30193023->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ30193023->GetYaxis()->SetTitleOffset(1.1);
   Graph_Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ30193023->GetYaxis()->SetTitleFont(42);
   Graph_Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ30193023->GetZaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ30193023->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ30193023->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ30193023->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ30193023);
   
   multigraph->Add(grae,"");
   
   Double_t divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fx3024[1] = {
   1};
   Double_t divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fy3024[1] = {
   0.9583333};
   Double_t divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_felx3024[1] = {
   1};
   Double_t divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fely3024[1] = {
   0.01724894};
   Double_t divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fehx3024[1] = {
   1};
   Double_t divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fehy3024[1] = {
   0.01282478};
   grae = new TGraphAsymmErrors(1,divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fx3024,divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fy3024,divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_felx3024,divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fehx3024,divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fely3024,divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fehy3024);
   grae->SetName("divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");
   grae->SetLineStyle(2);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ30203024 = new TH1F("Graph_Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ30203024","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,2.2);
   Graph_Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ30203024->SetMinimum(0.938077);
   Graph_Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ30203024->SetMaximum(0.9741655);
   Graph_Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ30203024->SetDirectory(0);
   Graph_Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ30203024->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ30203024->SetLineColor(ci);
   Graph_Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ30203024->GetXaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ30203024->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ30203024->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ30203024->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ30203024->GetXaxis()->SetTitleFont(42);
   Graph_Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ30203024->GetYaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ30203024->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ30203024->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ30203024->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ30203024->GetYaxis()->SetTitleOffset(1.1);
   Graph_Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ30203024->GetYaxis()->SetTitleFont(42);
   Graph_Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ30203024->GetZaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ30203024->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ30203024->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ30203024->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ30203024);
   
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
   eta_lz->Modified();
   eta_lz->cd();
   eta_lz->SetSelected(eta_lz);
}
