void EfficiencyByEta_1D_vs_Lz_0to12()
{
//=========Macro generated from canvas: eta_lz/eta_lz
//=========  (Sun May 13 10:47:26 2018) by ROOT version6.06/01
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
   
   Double_t divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fx3021[5] = {
   1,
   3,
   5,
   7,
   9};
   Double_t divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fy3021[5] = {
   0.9327595,
   0.9172477,
   0.920354,
   0.8815166,
   0.9197531};
   Double_t divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_felx3021[5] = {
   1,
   1,
   1,
   1,
   1};
   Double_t divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fely3021[5] = {
   0.002217281,
   0.005079048,
   0.007705373,
   0.01427226,
   0.02740075};
   Double_t divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fehx3021[5] = {
   1,
   1,
   1,
   1,
   1};
   Double_t divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fehy3021[5] = {
   0.002152519,
   0.004818142,
   0.007105714,
   0.01299389,
   0.02149308};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(5,divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fx3021,divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fy3021,divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_felx3021,divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fehx3021,divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fely3021,divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fehy3021);
   grae->SetName("divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ30173021 = new TH1F("Graph_Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ30173021","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,11);
   Graph_Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ30173021->SetMinimum(0.8598441);
   Graph_Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ30173021->SetMaximum(0.9486464);
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
   
   Double_t divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fx3022[15] = {
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
   Double_t divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fy3022[15] = {
   0.8692569,
   0.7875399,
   0.7230199,
   0.6910394,
   0.6200466,
   0.5353218,
   0.5117371,
   0.5390947,
   0.5925926,
   0.5827338,
   0.5297619,
   0.5679012,
   0.5576923,
   0.5185185,
   0.7777778};
   Double_t divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_felx3022[15] = {
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
   Double_t divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fely3022[15] = {
   0.002961916,
   0.006884957,
   0.009966409,
   0.0128664,
   0.01728796,
   0.02058705,
   0.01771535,
   0.03413111,
   0.03880393,
   0.03162942,
   0.04154142,
   0.06172513,
   0.07889241,
   0.1129943,
   0.2214294};
   Double_t divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fehx3022[15] = {
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
   Double_t divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fehy3022[15] = {
   0.002906672,
   0.006728818,
   0.009754905,
   0.0125847,
   0.0169985,
   0.02047186,
   0.01768687,
   0.03378953,
   0.03775514,
   0.03099945,
   0.04116118,
   0.05987558,
   0.07639601,
   0.1113997,
   0.1421182};
   grae = new TGraphAsymmErrors(15,divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fx3022,divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fy3022,divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_felx3022,divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fehx3022,divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fely3022,divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fehy3022);
   grae->SetName("divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ30183022 = new TH1F("Graph_Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ30183022","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,55);
   Graph_Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ30183022->SetMinimum(0.354087);
   Graph_Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ30183022->SetMaximum(0.9713332);
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
   
   Double_t divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fx3023[15] = {
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
   Double_t divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fy3023[15] = {
   0.851585,
   0.7780899,
   0.7310924,
   0.6943765,
   0.621547,
   0.6462094,
   0.610951,
   0.6509434,
   0.6081081,
   0.5779817,
   0.6321839,
   0.6756757,
   0.4545455,
   0.5,
   0.5};
   Double_t divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_felx3023[15] = {
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
   Double_t divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fely3023[15] = {
   0.01016393,
   0.01667409,
   0.02186343,
   0.02447361,
   0.02718806,
   0.03103847,
   0.02790926,
   0.05232539,
   0.06466148,
   0.05241622,
   0.05877106,
   0.09462755,
   0.1229998,
   0.1951821,
   0.4172485};
   Double_t divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fehx3023[15] = {
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
   Double_t divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fehy3023[15] = {
   0.009638422,
   0.01585841,
   0.02084359,
   0.02347363,
   0.02648137,
   0.02991903,
   0.02723578,
   0.04920643,
   0.06142075,
   0.05085594,
   0.05541987,
   0.08366854,
   0.1278601,
   0.1951821,
   0.4172485};
   grae = new TGraphAsymmErrors(15,divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fx3023,divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fy3023,divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_felx3023,divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fehx3023,divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fely3023,divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fehy3023);
   grae->SetName("divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");

   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);
   grae->SetLineStyle(2);

   ci = TColor::GetColor("#ff0000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ30193023 = new TH1F("Graph_Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ30193023","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,55);
   Graph_Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ30193023->SetMinimum(0);
   Graph_Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ30193023->SetMaximum(1.000698);
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
   
   Double_t divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fx3024[7] = {
   1,
   3,
   5,
   7,
   9,
   11,
   17};
   Double_t divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fy3024[7] = {
   0.9395649,
   0.92719,
   0.8991228,
   0.9210526,
   0.8909091,
   1,
   1};
   Double_t divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_felx3024[7] = {
   1,
   1,
   1,
   1,
   1,
   1,
   1};
   Double_t divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fely3024[7] = {
   0.004162404,
   0.00985299,
   0.01614199,
   0.02471569,
   0.05947333,
   0.6016845,
   0.8413447};
   Double_t divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fehx3024[7] = {
   1,
   1,
   1,
   1,
   1,
   1,
   1};
   Double_t divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fehy3024[7] = {
   0.003918179,
   0.008818545,
   0.01425778,
   0.01970423,
   0.04240908,
   0,
   0};
   grae = new TGraphAsymmErrors(7,divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fx3024,divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fy3024,divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_felx3024,divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fehx3024,divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fely3024,divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fehy3024);
   grae->SetName("divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");
   grae->SetLineStyle(2);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ30203024 = new TH1F("Graph_Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ30203024","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,19.8);
   Graph_Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ30203024->SetMinimum(0.07452078);
   Graph_Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ30203024->SetMaximum(1.084134);
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
   line->SetLineWidth(2);
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
   line->SetLineWidth(2);
   line->Draw();
   line = new TLine(60.5,0,60.5,1);

   ci = TColor::GetColor("#00cc00");
   line->SetLineColor(ci);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
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
