void EfficiencyByEta_1D_vs_Lxy_Trig_0to12()
{
//=========Macro generated from canvas: eta_lxy_trig/eta_lxy_trig
//=========  (Sun May 13 10:47:26 2018) by ROOT version6.06/01
   TCanvas *eta_lxy_trig = new TCanvas("eta_lxy_trig", "eta_lxy_trig",1,1,600,576);
   eta_lxy_trig->Range(-2.25,-0.1923077,12.75,1.089744);
   eta_lxy_trig->SetFillColor(0);
   eta_lxy_trig->SetBorderMode(0);
   eta_lxy_trig->SetBorderSize(2);
   eta_lxy_trig->SetTickx(1);
   eta_lxy_trig->SetTicky(1);
   eta_lxy_trig->SetLeftMargin(0.15);
   eta_lxy_trig->SetRightMargin(0.05);
   eta_lxy_trig->SetTopMargin(0.07);
   eta_lxy_trig->SetBottomMargin(0.15);
   eta_lxy_trig->SetFrameFillStyle(0);
   eta_lxy_trig->SetFrameBorderMode(0);
   eta_lxy_trig->SetFrameFillStyle(0);
   eta_lxy_trig->SetFrameBorderMode(0);
   
   TMultiGraph *multigraph = new TMultiGraph();
   multigraph->SetName("");
   multigraph->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");
   
   Double_t divide_num_Trig_LEp8_1D_A0_LXY_by_den_Trig_LEp8_1D_A0_LXY_fx3029[5] = {
   1,
   3,
   5,
   7,
   9};
   Double_t divide_num_Trig_LEp8_1D_A0_LXY_by_den_Trig_LEp8_1D_A0_LXY_fy3029[5] = {
   0.9530272,
   0.9320988,
   0.9052144,
   0.909698,
   0.9142425};
   Double_t divide_num_Trig_LEp8_1D_A0_LXY_by_den_Trig_LEp8_1D_A0_LXY_felx3029[5] = {
   1,
   1,
   1,
   1,
   1};
   Double_t divide_num_Trig_LEp8_1D_A0_LXY_by_den_Trig_LEp8_1D_A0_LXY_fely3029[5] = {
   0.001842005,
   0.00331451,
   0.004671523,
   0.005151758,
   0.005793576};
   Double_t divide_num_Trig_LEp8_1D_A0_LXY_by_den_Trig_LEp8_1D_A0_LXY_fehx3029[5] = {
   1,
   1,
   1,
   1,
   1};
   Double_t divide_num_Trig_LEp8_1D_A0_LXY_by_den_Trig_LEp8_1D_A0_LXY_fehy3029[5] = {
   0.001777032,
   0.003174317,
   0.004478849,
   0.004906803,
   0.005469786};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(5,divide_num_Trig_LEp8_1D_A0_LXY_by_den_Trig_LEp8_1D_A0_LXY_fx3029,divide_num_Trig_LEp8_1D_A0_LXY_by_den_Trig_LEp8_1D_A0_LXY_fy3029,divide_num_Trig_LEp8_1D_A0_LXY_by_den_Trig_LEp8_1D_A0_LXY_felx3029,divide_num_Trig_LEp8_1D_A0_LXY_by_den_Trig_LEp8_1D_A0_LXY_fehx3029,divide_num_Trig_LEp8_1D_A0_LXY_by_den_Trig_LEp8_1D_A0_LXY_fely3029,divide_num_Trig_LEp8_1D_A0_LXY_by_den_Trig_LEp8_1D_A0_LXY_fehy3029);
   grae->SetName("divide_num_Trig_LEp8_1D_A0_LXY_by_den_Trig_LEp8_1D_A0_LXY");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_Graph_divide_num_Trig_LEp8_1D_A0_LXY_by_den_Trig_LEp8_1D_A0_LXY30253029 = new TH1F("Graph_Graph_divide_num_Trig_LEp8_1D_A0_LXY_by_den_Trig_LEp8_1D_A0_LXY30253029","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,11);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LXY_by_den_Trig_LEp8_1D_A0_LXY30253029->SetMinimum(0.8951167);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LXY_by_den_Trig_LEp8_1D_A0_LXY30253029->SetMaximum(0.9602304);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LXY_by_den_Trig_LEp8_1D_A0_LXY30253029->SetDirectory(0);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LXY_by_den_Trig_LEp8_1D_A0_LXY30253029->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LXY_by_den_Trig_LEp8_1D_A0_LXY30253029->SetLineColor(ci);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LXY_by_den_Trig_LEp8_1D_A0_LXY30253029->GetXaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LXY_by_den_Trig_LEp8_1D_A0_LXY30253029->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LXY_by_den_Trig_LEp8_1D_A0_LXY30253029->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LXY_by_den_Trig_LEp8_1D_A0_LXY30253029->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LXY_by_den_Trig_LEp8_1D_A0_LXY30253029->GetXaxis()->SetTitleFont(42);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LXY_by_den_Trig_LEp8_1D_A0_LXY30253029->GetYaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LXY_by_den_Trig_LEp8_1D_A0_LXY30253029->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LXY_by_den_Trig_LEp8_1D_A0_LXY30253029->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LXY_by_den_Trig_LEp8_1D_A0_LXY30253029->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LXY_by_den_Trig_LEp8_1D_A0_LXY30253029->GetYaxis()->SetTitleOffset(1.1);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LXY_by_den_Trig_LEp8_1D_A0_LXY30253029->GetYaxis()->SetTitleFont(42);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LXY_by_den_Trig_LEp8_1D_A0_LXY30253029->GetZaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LXY_by_den_Trig_LEp8_1D_A0_LXY30253029->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LXY_by_den_Trig_LEp8_1D_A0_LXY30253029->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_divide_num_Trig_LEp8_1D_A0_LXY_by_den_Trig_LEp8_1D_A0_LXY30253029->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph_divide_num_Trig_LEp8_1D_A0_LXY_by_den_Trig_LEp8_1D_A0_LXY30253029);
   
   multigraph->Add(grae,"");
   
   Double_t divide_num_Trig_Gp8_1D_A0_LXY_by_den_Trig_Gp8_1D_A0_LXY_fx3030[5] = {
   1,
   3,
   5,
   7,
   9};
   Double_t divide_num_Trig_Gp8_1D_A0_LXY_by_den_Trig_Gp8_1D_A0_LXY_fy3030[5] = {
   0.8994709,
   0.8334485,
   0.8088889,
   0.7577031,
   0.7438424};
   Double_t divide_num_Trig_Gp8_1D_A0_LXY_by_den_Trig_Gp8_1D_A0_LXY_felx3030[5] = {
   1,
   1,
   1,
   1,
   1};
   Double_t divide_num_Trig_Gp8_1D_A0_LXY_by_den_Trig_Gp8_1D_A0_LXY_fely3030[5] = {
   0.00542333,
   0.01037663,
   0.01401404,
   0.01710233,
   0.01891498};
   Double_t divide_num_Trig_Gp8_1D_A0_LXY_by_den_Trig_Gp8_1D_A0_LXY_fehx3030[5] = {
   1,
   1,
   1,
   1,
   1};
   Double_t divide_num_Trig_Gp8_1D_A0_LXY_by_den_Trig_Gp8_1D_A0_LXY_fehy3030[5] = {
   0.005181828,
   0.00989968,
   0.01329899,
   0.01634959,
   0.01807785};
   grae = new TGraphAsymmErrors(5,divide_num_Trig_Gp8_1D_A0_LXY_by_den_Trig_Gp8_1D_A0_LXY_fx3030,divide_num_Trig_Gp8_1D_A0_LXY_by_den_Trig_Gp8_1D_A0_LXY_fy3030,divide_num_Trig_Gp8_1D_A0_LXY_by_den_Trig_Gp8_1D_A0_LXY_felx3030,divide_num_Trig_Gp8_1D_A0_LXY_by_den_Trig_Gp8_1D_A0_LXY_fehx3030,divide_num_Trig_Gp8_1D_A0_LXY_by_den_Trig_Gp8_1D_A0_LXY_fely3030,divide_num_Trig_Gp8_1D_A0_LXY_by_den_Trig_Gp8_1D_A0_LXY_fehy3030);
   grae->SetName("divide_num_Trig_Gp8_1D_A0_LXY_by_den_Trig_Gp8_1D_A0_LXY");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");

   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);
   grae->SetLineStyle(2);

   ci = TColor::GetColor("#ff0000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_Graph_divide_num_Trig_Gp8_1D_A0_LXY_by_den_Trig_Gp8_1D_A0_LXY30263030 = new TH1F("Graph_Graph_divide_num_Trig_Gp8_1D_A0_LXY_by_den_Trig_Gp8_1D_A0_LXY30263030","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,11);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LXY_by_den_Trig_Gp8_1D_A0_LXY30263030->SetMinimum(0.7069549);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LXY_by_den_Trig_Gp8_1D_A0_LXY30263030->SetMaximum(0.9226253);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LXY_by_den_Trig_Gp8_1D_A0_LXY30263030->SetDirectory(0);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LXY_by_den_Trig_Gp8_1D_A0_LXY30263030->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LXY_by_den_Trig_Gp8_1D_A0_LXY30263030->SetLineColor(ci);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LXY_by_den_Trig_Gp8_1D_A0_LXY30263030->GetXaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LXY_by_den_Trig_Gp8_1D_A0_LXY30263030->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LXY_by_den_Trig_Gp8_1D_A0_LXY30263030->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LXY_by_den_Trig_Gp8_1D_A0_LXY30263030->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LXY_by_den_Trig_Gp8_1D_A0_LXY30263030->GetXaxis()->SetTitleFont(42);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LXY_by_den_Trig_Gp8_1D_A0_LXY30263030->GetYaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LXY_by_den_Trig_Gp8_1D_A0_LXY30263030->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LXY_by_den_Trig_Gp8_1D_A0_LXY30263030->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LXY_by_den_Trig_Gp8_1D_A0_LXY30263030->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LXY_by_den_Trig_Gp8_1D_A0_LXY30263030->GetYaxis()->SetTitleOffset(1.1);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LXY_by_den_Trig_Gp8_1D_A0_LXY30263030->GetYaxis()->SetTitleFont(42);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LXY_by_den_Trig_Gp8_1D_A0_LXY30263030->GetZaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LXY_by_den_Trig_Gp8_1D_A0_LXY30263030->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LXY_by_den_Trig_Gp8_1D_A0_LXY30263030->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_divide_num_Trig_Gp8_1D_A0_LXY_by_den_Trig_Gp8_1D_A0_LXY30263030->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph_divide_num_Trig_Gp8_1D_A0_LXY_by_den_Trig_Gp8_1D_A0_LXY30263030);
   
   multigraph->Add(grae,"");
   
   Double_t divide_num_Trig_LEp8_1D_A1_LXY_by_den_Trig_LEp8_1D_A1_LXY_fx3031[5] = {
   1,
   3,
   5,
   7,
   9};
   Double_t divide_num_Trig_LEp8_1D_A1_LXY_by_den_Trig_LEp8_1D_A1_LXY_fy3031[5] = {
   0.9474507,
   0.9102126,
   0.8733112,
   0.8419666,
   0.8310962};
   Double_t divide_num_Trig_LEp8_1D_A1_LXY_by_den_Trig_LEp8_1D_A1_LXY_felx3031[5] = {
   1,
   1,
   1,
   1,
   1};
   Double_t divide_num_Trig_LEp8_1D_A1_LXY_by_den_Trig_LEp8_1D_A1_LXY_fely3031[5] = {
   0.001720844,
   0.003622215,
   0.005145374,
   0.006488525,
   0.00754694};
   Double_t divide_num_Trig_LEp8_1D_A1_LXY_by_den_Trig_LEp8_1D_A1_LXY_fehx3031[5] = {
   1,
   1,
   1,
   1,
   1};
   Double_t divide_num_Trig_LEp8_1D_A1_LXY_by_den_Trig_LEp8_1D_A1_LXY_fehy3031[5] = {
   0.001670034,
   0.003497664,
   0.00497633,
   0.00628371,
   0.00729373};
   grae = new TGraphAsymmErrors(5,divide_num_Trig_LEp8_1D_A1_LXY_by_den_Trig_LEp8_1D_A1_LXY_fx3031,divide_num_Trig_LEp8_1D_A1_LXY_by_den_Trig_LEp8_1D_A1_LXY_fy3031,divide_num_Trig_LEp8_1D_A1_LXY_by_den_Trig_LEp8_1D_A1_LXY_felx3031,divide_num_Trig_LEp8_1D_A1_LXY_by_den_Trig_LEp8_1D_A1_LXY_fehx3031,divide_num_Trig_LEp8_1D_A1_LXY_by_den_Trig_LEp8_1D_A1_LXY_fely3031,divide_num_Trig_LEp8_1D_A1_LXY_by_den_Trig_LEp8_1D_A1_LXY_fehy3031);
   grae->SetName("divide_num_Trig_LEp8_1D_A1_LXY_by_den_Trig_LEp8_1D_A1_LXY");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_Graph_divide_num_Trig_LEp8_1D_A1_LXY_by_den_Trig_LEp8_1D_A1_LXY30273031 = new TH1F("Graph_Graph_divide_num_Trig_LEp8_1D_A1_LXY_by_den_Trig_LEp8_1D_A1_LXY30273031","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,11);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LXY_by_den_Trig_LEp8_1D_A1_LXY30273031->SetMinimum(0.8109921);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LXY_by_den_Trig_LEp8_1D_A1_LXY30273031->SetMaximum(0.9616779);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LXY_by_den_Trig_LEp8_1D_A1_LXY30273031->SetDirectory(0);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LXY_by_den_Trig_LEp8_1D_A1_LXY30273031->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LXY_by_den_Trig_LEp8_1D_A1_LXY30273031->SetLineColor(ci);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LXY_by_den_Trig_LEp8_1D_A1_LXY30273031->GetXaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LXY_by_den_Trig_LEp8_1D_A1_LXY30273031->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LXY_by_den_Trig_LEp8_1D_A1_LXY30273031->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LXY_by_den_Trig_LEp8_1D_A1_LXY30273031->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LXY_by_den_Trig_LEp8_1D_A1_LXY30273031->GetXaxis()->SetTitleFont(42);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LXY_by_den_Trig_LEp8_1D_A1_LXY30273031->GetYaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LXY_by_den_Trig_LEp8_1D_A1_LXY30273031->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LXY_by_den_Trig_LEp8_1D_A1_LXY30273031->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LXY_by_den_Trig_LEp8_1D_A1_LXY30273031->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LXY_by_den_Trig_LEp8_1D_A1_LXY30273031->GetYaxis()->SetTitleOffset(1.1);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LXY_by_den_Trig_LEp8_1D_A1_LXY30273031->GetYaxis()->SetTitleFont(42);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LXY_by_den_Trig_LEp8_1D_A1_LXY30273031->GetZaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LXY_by_den_Trig_LEp8_1D_A1_LXY30273031->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LXY_by_den_Trig_LEp8_1D_A1_LXY30273031->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_divide_num_Trig_LEp8_1D_A1_LXY_by_den_Trig_LEp8_1D_A1_LXY30273031->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph_divide_num_Trig_LEp8_1D_A1_LXY_by_den_Trig_LEp8_1D_A1_LXY30273031);
   
   multigraph->Add(grae,"");
   
   Double_t divide_num_Trig_Gp8_1D_A1_LXY_by_den_Trig_Gp8_1D_A1_LXY_fx3032[5] = {
   1,
   3,
   5,
   7,
   9};
   Double_t divide_num_Trig_Gp8_1D_A1_LXY_by_den_Trig_Gp8_1D_A1_LXY_fy3032[5] = {
   0.9544529,
   0.9289544,
   0.920603,
   0.9024691,
   0.9089506};
   Double_t divide_num_Trig_Gp8_1D_A1_LXY_by_den_Trig_Gp8_1D_A1_LXY_felx3032[5] = {
   1,
   1,
   1,
   1,
   1};
   Double_t divide_num_Trig_Gp8_1D_A1_LXY_by_den_Trig_Gp8_1D_A1_LXY_fely3032[5] = {
   0.003574071,
   0.007289589,
   0.009522765,
   0.0115681,
   0.01274804};
   Double_t divide_num_Trig_Gp8_1D_A1_LXY_by_den_Trig_Gp8_1D_A1_LXY_fehx3032[5] = {
   1,
   1,
   1,
   1,
   1};
   Double_t divide_num_Trig_Gp8_1D_A1_LXY_by_den_Trig_Gp8_1D_A1_LXY_fehy3032[5] = {
   0.003333976,
   0.006685819,
   0.008628251,
   0.01051624,
   0.01140085};
   grae = new TGraphAsymmErrors(5,divide_num_Trig_Gp8_1D_A1_LXY_by_den_Trig_Gp8_1D_A1_LXY_fx3032,divide_num_Trig_Gp8_1D_A1_LXY_by_den_Trig_Gp8_1D_A1_LXY_fy3032,divide_num_Trig_Gp8_1D_A1_LXY_by_den_Trig_Gp8_1D_A1_LXY_felx3032,divide_num_Trig_Gp8_1D_A1_LXY_by_den_Trig_Gp8_1D_A1_LXY_fehx3032,divide_num_Trig_Gp8_1D_A1_LXY_by_den_Trig_Gp8_1D_A1_LXY_fely3032,divide_num_Trig_Gp8_1D_A1_LXY_by_den_Trig_Gp8_1D_A1_LXY_fehy3032);
   grae->SetName("divide_num_Trig_Gp8_1D_A1_LXY_by_den_Trig_Gp8_1D_A1_LXY");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");
   grae->SetLineStyle(2);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_Graph_divide_num_Trig_Gp8_1D_A1_LXY_by_den_Trig_Gp8_1D_A1_LXY30283032 = new TH1F("Graph_Graph_divide_num_Trig_Gp8_1D_A1_LXY_by_den_Trig_Gp8_1D_A1_LXY30283032","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,11);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LXY_by_den_Trig_Gp8_1D_A1_LXY30283032->SetMinimum(0.8842124);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LXY_by_den_Trig_Gp8_1D_A1_LXY30283032->SetMaximum(0.9644755);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LXY_by_den_Trig_Gp8_1D_A1_LXY30283032->SetDirectory(0);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LXY_by_den_Trig_Gp8_1D_A1_LXY30283032->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LXY_by_den_Trig_Gp8_1D_A1_LXY30283032->SetLineColor(ci);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LXY_by_den_Trig_Gp8_1D_A1_LXY30283032->GetXaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LXY_by_den_Trig_Gp8_1D_A1_LXY30283032->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LXY_by_den_Trig_Gp8_1D_A1_LXY30283032->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LXY_by_den_Trig_Gp8_1D_A1_LXY30283032->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LXY_by_den_Trig_Gp8_1D_A1_LXY30283032->GetXaxis()->SetTitleFont(42);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LXY_by_den_Trig_Gp8_1D_A1_LXY30283032->GetYaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LXY_by_den_Trig_Gp8_1D_A1_LXY30283032->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LXY_by_den_Trig_Gp8_1D_A1_LXY30283032->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LXY_by_den_Trig_Gp8_1D_A1_LXY30283032->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LXY_by_den_Trig_Gp8_1D_A1_LXY30283032->GetYaxis()->SetTitleOffset(1.1);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LXY_by_den_Trig_Gp8_1D_A1_LXY30283032->GetYaxis()->SetTitleFont(42);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LXY_by_den_Trig_Gp8_1D_A1_LXY30283032->GetZaxis()->SetLabelFont(42);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LXY_by_den_Trig_Gp8_1D_A1_LXY30283032->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LXY_by_den_Trig_Gp8_1D_A1_LXY30283032->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_divide_num_Trig_Gp8_1D_A1_LXY_by_den_Trig_Gp8_1D_A1_LXY30283032->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph_divide_num_Trig_Gp8_1D_A1_LXY_by_den_Trig_Gp8_1D_A1_LXY30283032);
   
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
   eta_lxy_trig->Modified();
   eta_lxy_trig->cd();
   eta_lxy_trig->SetSelected(eta_lxy_trig);
}
