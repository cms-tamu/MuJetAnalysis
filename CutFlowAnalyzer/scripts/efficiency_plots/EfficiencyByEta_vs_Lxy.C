void EfficiencyByEta_vs_Lxy()
{
//=========Macro generated from canvas: eta_lxy/eta_lxy
//=========  (Sun May 13 03:03:07 2018) by ROOT version6.06/01
   TCanvas *eta_lxy = new TCanvas("eta_lxy", "eta_lxy",0,0,600,600);
   eta_lxy->Range(-0.5125,-0.1923077,2.2375,1.089744);
   eta_lxy->SetFillColor(0);
   eta_lxy->SetBorderMode(0);
   eta_lxy->SetBorderSize(2);
   eta_lxy->SetTickx(1);
   eta_lxy->SetTicky(1);
   eta_lxy->SetLeftMargin(0.15);
   eta_lxy->SetRightMargin(0.05);
   eta_lxy->SetTopMargin(0.07);
   eta_lxy->SetBottomMargin(0.15);
   eta_lxy->SetFrameFillStyle(0);
   eta_lxy->SetFrameBorderMode(0);
   eta_lxy->SetFrameFillStyle(0);
   eta_lxy->SetFrameBorderMode(0);
   
   TMultiGraph *multigraph = new TMultiGraph();
   multigraph->SetName("");
   multigraph->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");
   
   Double_t divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fx3011[1] = {
   1};
   Double_t divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fy3011[1] = {
   0.9606855};
   Double_t divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_felx3011[1] = {
   1};
   Double_t divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fely3011[1] = {
   0.004863558};
   Double_t divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fehx3011[1] = {
   1};
   Double_t divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fehy3011[1] = {
   0.004372438};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(1,divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fx3011,divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fy3011,divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_felx3011,divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fehx3011,divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fely3011,divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fehy3011);
   grae->SetName("divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3011 = new TH1F("Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3011","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,2.2);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3011->SetMinimum(0.9548983);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3011->SetMaximum(0.9659815);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3011->SetDirectory(0);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3011->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3011->SetLineColor(ci);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3011->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3011->GetXaxis()->SetLabelOffset(0.007);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3011->GetXaxis()->SetLabelSize(0.05);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3011->GetXaxis()->SetTitleSize(0.06);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3011->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3011->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3011->GetYaxis()->SetLabelOffset(0.007);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3011->GetYaxis()->SetLabelSize(0.05);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3011->GetYaxis()->SetTitleSize(0.06);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3011->GetYaxis()->SetTitleOffset(1.1);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3011->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3011->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3011->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3011->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3011->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3011);
   
   multigraph->Add(grae,"");
   
   Double_t divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fx3012[1] = {
   1};
   Double_t divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fy3012[1] = {
   0.910828};
   Double_t divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_felx3012[1] = {
   1};
   Double_t divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fely3012[1] = {
   0.01513776};
   Double_t divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fehx3012[1] = {
   1};
   Double_t divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fehy3012[1] = {
   0.01325457};
   grae = new TGraphAsymmErrors(1,divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fx3012,divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fy3012,divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_felx3012,divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fehx3012,divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fely3012,divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fehy3012);
   grae->SetName("divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");

   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);
   grae->SetLineStyle(2);

   ci = TColor::GetColor("#ff0000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3012 = new TH1F("Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3012","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,2.2);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3012->SetMinimum(0.892851);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3012->SetMaximum(0.9269218);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3012->SetDirectory(0);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3012->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3012->SetLineColor(ci);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3012->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3012->GetXaxis()->SetLabelOffset(0.007);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3012->GetXaxis()->SetLabelSize(0.05);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3012->GetXaxis()->SetTitleSize(0.06);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3012->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3012->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3012->GetYaxis()->SetLabelOffset(0.007);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3012->GetYaxis()->SetLabelSize(0.05);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3012->GetYaxis()->SetTitleSize(0.06);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3012->GetYaxis()->SetTitleOffset(1.1);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3012->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3012->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3012->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3012->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3012->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3012);
   
   multigraph->Add(grae,"");
   
   Double_t divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fx3013[1] = {
   1};
   Double_t divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fy3013[1] = {
   0.9621785};
   Double_t divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_felx3013[1] = {
   1};
   Double_t divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fely3013[1] = {
   0.004785742};
   Double_t divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fehx3013[1] = {
   1};
   Double_t divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fehy3013[1] = {
   0.004292267};
   grae = new TGraphAsymmErrors(1,divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fx3013,divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fy3013,divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_felx3013,divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fehx3013,divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fely3013,divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fehy3013);
   grae->SetName("divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3013 = new TH1F("Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3013","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,2.2);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3013->SetMinimum(0.956485);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3013->SetMaximum(0.9673786);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3013->SetDirectory(0);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3013->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3013->SetLineColor(ci);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3013->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3013->GetXaxis()->SetLabelOffset(0.007);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3013->GetXaxis()->SetLabelSize(0.05);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3013->GetXaxis()->SetTitleSize(0.06);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3013->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3013->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3013->GetYaxis()->SetLabelOffset(0.007);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3013->GetYaxis()->SetLabelSize(0.05);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3013->GetYaxis()->SetTitleSize(0.06);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3013->GetYaxis()->SetTitleOffset(1.1);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3013->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3013->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3013->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3013->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3013->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3013);
   
   multigraph->Add(grae,"");
   
   Double_t divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fx3014[1] = {
   1};
   Double_t divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fy3014[1] = {
   0.9596603};
   Double_t divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_felx3014[1] = {
   1};
   Double_t divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fely3014[1] = {
   0.01123882};
   Double_t divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fehx3014[1] = {
   1};
   Double_t divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fehy3014[1] = {
   0.009061036};
   grae = new TGraphAsymmErrors(1,divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fx3014,divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fy3014,divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_felx3014,divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fehx3014,divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fely3014,divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fehy3014);
   grae->SetName("divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");
   grae->SetLineStyle(2);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3014 = new TH1F("Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3014","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,2.2);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3014->SetMinimum(0.9463915);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3014->SetMaximum(0.9707513);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3014->SetDirectory(0);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3014->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3014->SetLineColor(ci);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3014->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3014->GetXaxis()->SetLabelOffset(0.007);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3014->GetXaxis()->SetLabelSize(0.05);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3014->GetXaxis()->SetTitleSize(0.06);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3014->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3014->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3014->GetYaxis()->SetLabelOffset(0.007);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3014->GetYaxis()->SetLabelSize(0.05);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3014->GetYaxis()->SetTitleSize(0.06);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3014->GetYaxis()->SetTitleOffset(1.1);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3014->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3014->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3014->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3014->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3014->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3014);
   
   multigraph->Add(grae,"");
   multigraph->Draw("ALP");
   multigraph->GetXaxis()->SetTitle("L_{xy} [cm]");
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
   
   TLegend *leg = new TLegend(0.5866762,0.2447257,0.7858166,0.4535865,NULL,"brNDC");
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
   eta_lxy->Modified();
   eta_lxy->cd();
   eta_lxy->SetSelected(eta_lxy);
}
