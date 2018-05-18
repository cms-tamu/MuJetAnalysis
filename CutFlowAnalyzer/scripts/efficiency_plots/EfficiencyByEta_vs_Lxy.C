void EfficiencyByEta_vs_Lxy()
{
//=========Macro generated from canvas: eta_lxy/eta_lxy
//=========  (Sun May 13 10:47:26 2018) by ROOT version6.06/01
   TCanvas *eta_lxy = new TCanvas("eta_lxy", "eta_lxy",0,0,600,600);
   eta_lxy->Range(-2.5625,-0.1923077,11.1875,1.089744);
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
   
   Double_t divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fx3011[5] = {
   1,
   3,
   5,
   7,
   9};
   Double_t divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fy3011[5] = {
   0.9491453,
   0.9283338,
   0.9025559,
   0.8988285,
   0.9097278};
   Double_t divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_felx3011[5] = {
   1,
   1,
   1,
   1,
   1};
   Double_t divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fely3011[5] = {
   0.00177846,
   0.003038066,
   0.004112854,
   0.004594527,
   0.004952698};
   Double_t divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fehx3011[5] = {
   1,
   1,
   1,
   1,
   1};
   Double_t divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fehy3011[5] = {
   0.001722442,
   0.002926036,
   0.003966756,
   0.00442054,
   0.004725587};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(5,divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fx3011,divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fy3011,divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_felx3011,divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fehx3011,divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fely3011,divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fehy3011);
   grae->SetName("divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3011 = new TH1F("Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3011","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,11);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3011->SetMinimum(0.8885706);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3011->SetMaximum(0.9565311);
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
   
   Double_t divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fx3012[5] = {
   1,
   3,
   5,
   7,
   9};
   Double_t divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fy3012[5] = {
   0.8399285,
   0.7420436,
   0.6538462,
   0.5883459,
   0.5860927};
   Double_t divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_felx3012[5] = {
   1,
   1,
   1,
   1,
   1};
   Double_t divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fely3012[5] = {
   0.006074658,
   0.01075355,
   0.01369607,
   0.01563542,
   0.01700387};
   Double_t divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fehx3012[5] = {
   1,
   1,
   1,
   1,
   1};
   Double_t divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fehy3012[5] = {
   0.005897337,
   0.01047606,
   0.0134526,
   0.01546428,
   0.01680754};
   grae = new TGraphAsymmErrors(5,divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fx3012,divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fy3012,divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_felx3012,divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fehx3012,divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fely3012,divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fehy3012);
   grae->SetName("divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");

   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);
   grae->SetLineStyle(2);

   ci = TColor::GetColor("#ff0000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3012 = new TH1F("Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3012","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,11);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3012->SetMinimum(0.5414151);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3012->SetMaximum(0.8734996);
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
   
   Double_t divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fx3013[5] = {
   1,
   3,
   5,
   7,
   9};
   Double_t divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fy3013[5] = {
   0.8847481,
   0.7867259,
   0.7314762,
   0.6666667,
   0.6453621};
   Double_t divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_felx3013[5] = {
   1,
   1,
   1,
   1,
   1};
   Double_t divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fely3013[5] = {
   0.002222283,
   0.004294409,
   0.005415988,
   0.006293641,
   0.007025211};
   Double_t divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fehx3013[5] = {
   1,
   1,
   1,
   1,
   1};
   Double_t divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fehy3013[5] = {
   0.002186009,
   0.004233046,
   0.005348617,
   0.006235577,
   0.006963982};
   grae = new TGraphAsymmErrors(5,divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fx3013,divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fy3013,divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_felx3013,divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fehx3013,divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fely3013,divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fehy3013);
   grae->SetName("divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3013 = new TH1F("Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3013","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,11);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3013->SetMinimum(0.6134772);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3013->SetMaximum(0.9117939);
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
   
   Double_t divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fx3014[5] = {
   1,
   3,
   5,
   7,
   9};
   Double_t divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fy3014[5] = {
   0.94982,
   0.9301541,
   0.9208443,
   0.8888037,
   0.898971};
   Double_t divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_felx3014[5] = {
   1,
   1,
   1,
   1,
   1};
   Double_t divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fely3014[5] = {
   0.003381567,
   0.006052156,
   0.007555715,
   0.009400166,
   0.01007731};
   Double_t divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fehx3014[5] = {
   1,
   1,
   1,
   1,
   1};
   Double_t divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fehy3014[5] = {
   0.003184756,
   0.005620012,
   0.006974305,
   0.008777844,
   0.009293404};
   grae = new TGraphAsymmErrors(5,divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fx3014,divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fy3014,divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_felx3014,divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fehx3014,divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fely3014,divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fehy3014);
   grae->SetName("divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY");
   grae->SetTitle("#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV");
   grae->SetLineStyle(2);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3014 = new TH1F("Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3014","#scale[1.4]{    #font[61]{CMS}}#font[52]{Simulation}                          13 TeV",100,0,11);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3014->SetMinimum(0.8720434);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3014->SetMaximum(0.9603649);
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
   eta_lxy->Modified();
   eta_lxy->cd();
   eta_lxy->SetSelected(eta_lxy);
}
