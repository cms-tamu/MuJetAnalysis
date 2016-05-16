void EfficiencyByEta_vs_Lxy()
{
//=========Macro generated from canvas: eta_lxy/eta_lxy
//=========  (Tue Oct 27 13:03:01 2015) by ROOT version6.02/05
   TCanvas *eta_lxy = new TCanvas("eta_lxy", "eta_lxy",321,1245,700,500);
   eta_lxy->Range(-15,-0.1285154,95,1.156638);
   eta_lxy->SetFillColor(0);
   eta_lxy->SetBorderMode(0);
   eta_lxy->SetBorderSize(2);
   eta_lxy->SetFrameBorderMode(0);
   eta_lxy->SetFrameBorderMode(0);
   
   TMultiGraph *multigraph = new TMultiGraph();
   multigraph->SetName("");
   multigraph->SetTitle("");
   
   Double_t divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fx3001[17] = {
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
   Double_t divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fy3001[17] = {
   0.9791763,
   0.9734804,
   0.9416267,
   0.9064787,
   0.8721704,
   0.8586762,
   0.8487568,
   0.8402062,
   0.8325446,
   0.8144422,
   0.7400211,
   0.6468345,
   0.5669507,
   0.5320057,
   0.4879267,
   0.3936282,
   0.02923046};
   Double_t divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_felx3001[17] = {
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
   Double_t divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fely3001[17] = {
   0.000750902,
   0.001760143,
   0.003015275,
   0.004053299,
   0.005169441,
   0.005790164,
   0.00447142,
   0.007083557,
   0.007429464,
   0.005357242,
   0.006530839,
   0.007785347,
   0.008815401,
   0.009597263,
   0.01039981,
   0.008029614,
   0.002378261};
   Double_t divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fehx3001[17] = {
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
   Double_t divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fehy3001[17] = {
   0.0007257331,
   0.001656474,
   0.00287928,
   0.00390489,
   0.005000588,
   0.005602659,
   0.00436707,
   0.006843871,
   0.007181215,
   0.00524234,
   0.006427791,
   0.007709445,
   0.008773942,
   0.009574074,
   0.01041006,
   0.00808655,
   0.002573308};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(17,divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fx3001,divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fy3001,divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_felx3001,divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fehx3001,divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fely3001,divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY_fehy3001);
   grae->SetName("divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY");
   grae->SetTitle("num_LEp8_1D_A0_LXY");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001 = new TH1F("Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001","num_LEp8_1D_A0_LXY",100,0,88);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001->SetMinimum(0);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001->SetMaximum(1.075207);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001->SetDirectory(0);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001->SetLineColor(ci);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001->GetXaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001->GetXaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001->GetYaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001->GetYaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001);
   
   multigraph->Add(grae,"");
   
   Double_t divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fx3002[17] = {
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
   Double_t divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fy3002[17] = {
   0.9602934,
   0.9238452,
   0.8698113,
   0.8470847,
   0.7894073,
   0.7488076,
   0.7798434,
   0.7566462,
   0.744186,
   0.7030905,
   0.5842697,
   0.5563636,
   0.4564706,
   0.384375,
   0.2666667,
   0.2401055,
   0.02295918};
   Double_t divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_felx3002[17] = {
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
   Double_t divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fely3002[17] = {
   0.002621859,
   0.007217296,
   0.01117074,
   0.01288342,
   0.0154831,
   0.01848894,
   0.01372949,
   0.02096192,
   0.02278017,
   0.0159555,
   0.01928152,
   0.02217926,
   0.02519962,
   0.02832854,
   0.02862391,
   0.02250918,
   0.0074702};
   Double_t divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fehx3002[17] = {
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
   Double_t divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fehy3002[17] = {
   0.00247032,
   0.00666341,
   0.01044153,
   0.01208509,
   0.01472198,
   0.01766226,
   0.01316151,
   0.01985832,
   0.02158337,
   0.01549119,
   0.01903602,
   0.02196575,
   0.02541412,
   0.02909122,
   0.03057873,
   0.02396074,
   0.01030964};
   grae = new TGraphAsymmErrors(17,divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fx3002,divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fy3002,divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_felx3002,divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fehx3002,divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fely3002,divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY_fehy3002);
   grae->SetName("divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY");
   grae->SetTitle("num_Gp8_1D_A0_LXY");

   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);
   grae->SetLineStyle(2);

   ci = TColor::GetColor("#ff0000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002 = new TH1F("Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002","num_Gp8_1D_A0_LXY",100,0,88);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002->SetMinimum(0);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002->SetMaximum(1.057491);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002->SetDirectory(0);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002->SetLineColor(ci);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002->GetXaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002->GetXaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002->GetYaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002->GetYaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002);
   
   multigraph->Add(grae,"");
   
   Double_t divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fx3003[17] = {
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
   Double_t divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fy3003[17] = {
   0.9585358,
   0.9161585,
   0.8630685,
   0.8231251,
   0.7795438,
   0.7804343,
   0.7618467,
   0.7686615,
   0.7556657,
   0.723798,
   0.6502242,
   0.5705651,
   0.490991,
   0.442963,
   0.370347,
   0.3248049,
   0.02697342};
   Double_t divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_felx3003[17] = {
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
   Double_t divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fely3003[17] = {
   0.0009604277,
   0.002707293,
   0.003951056,
   0.004842006,
   0.005814963,
   0.006302565,
   0.005059667,
   0.00781219,
   0.008354225,
   0.006005385,
   0.007479705,
   0.00877651,
   0.01031525,
   0.01125388,
   0.01235715,
   0.009889229,
   0.003228681};
   Double_t divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fehx3003[17] = {
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
   Double_t divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fehy3003[17] = {
   0.000939842,
   0.002631388,
   0.003858866,
   0.004741707,
   0.005708709,
   0.006177356,
   0.0049878,
   0.007635663,
   0.008169233,
   0.005926843,
   0.007407662,
   0.008733119,
   0.01032277,
   0.01131146,
   0.01252494,
   0.01004451,
   0.003626966};
   grae = new TGraphAsymmErrors(17,divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fx3003,divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fy3003,divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_felx3003,divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fehx3003,divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fely3003,divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fehy3003);
   grae->SetName("divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY");
   grae->SetTitle("num_LEp8_1D_A1_LXY");
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003 = new TH1F("Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003","num_LEp8_1D_A1_LXY",100,0,88);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003->SetMinimum(0);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003->SetMaximum(1.053049);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003->SetDirectory(0);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003->SetLineColor(ci);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003->GetXaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003->GetXaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003->GetYaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003->GetYaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003);
   
   multigraph->Add(grae,"");
   
   Double_t divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fx3004[17] = {
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
   Double_t divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fy3004[17] = {
   0.9675691,
   0.9345742,
   0.9172078,
   0.8658777,
   0.8238702,
   0.835958,
   0.817454,
   0.8339552,
   0.7990971,
   0.7699115,
   0.6885714,
   0.6038394,
   0.5306122,
   0.5280899,
   0.4027304,
   0.3639922,
   0.02414487};
   Double_t divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_felx3004[17] = {
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
   Double_t divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fely3004[17] = {
   0.002242637,
   0.006412949,
   0.008614134,
   0.01157048,
   0.0139336,
   0.01452845,
   0.01159135,
   0.01765572,
   0.0208634,
   0.01485559,
   0.01848495,
   0.02147491,
   0.02494179,
   0.02790446,
   0.02995421,
   0.02196342,
   0.006829423};
   Double_t divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fehx3004[17] = {
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
   Double_t divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fehy3004[17] = {
   0.002106365,
   0.00589934,
   0.007902147,
   0.010816,
   0.01315003,
   0.01360426,
   0.01106465,
   0.01633877,
   0.01943499,
   0.01423526,
   0.01792468,
   0.0210974,
   0.02479655,
   0.02773857,
   0.0306562,
   0.02251954,
   0.009021511};
   grae = new TGraphAsymmErrors(17,divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fx3004,divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fy3004,divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_felx3004,divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fehx3004,divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fely3004,divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fehy3004);
   grae->SetName("divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY");
   grae->SetTitle("num_Gp8_1D_A1_LXY");
   grae->SetLineStyle(2);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004 = new TH1F("Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004","num_Gp8_1D_A1_LXY",100,0,88);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004->SetMinimum(0);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004->SetMaximum(1.064911);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004->SetDirectory(0);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004->SetLineColor(ci);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004->GetXaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004->GetXaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004->GetYaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004->GetYaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004);
   
   multigraph->Add(grae,"");
   multigraph->Draw("ALP");
   multigraph->GetXaxis()->SetTitle("L_{XY} [cm]");
   multigraph->GetXaxis()->SetLabelFont(42);
   multigraph->GetXaxis()->SetLabelSize(0.035);
   multigraph->GetXaxis()->SetTitleSize(0.035);
   multigraph->GetXaxis()->SetTitleFont(42);
   multigraph->GetYaxis()->SetTitle("Efficiency");
   multigraph->GetYaxis()->SetLabelFont(42);
   multigraph->GetYaxis()->SetLabelSize(0.035);
   multigraph->GetYaxis()->SetTitleSize(0.035);
   multigraph->GetYaxis()->SetTitleFont(42);
   
   TLegend *leg = new TLegend(0.6982759,0.6701903,0.8979885,0.8794926,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.03171247);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY","|#eta_{#gamma D}| #leq 0.8 A0 #mu_{0}","L");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY","|#eta_{#gamma D}| > 0.8 A0 #mu_{0}","L");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(2);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY","|#eta_{#gamma D}| #leq 0.8 A1 #mu_{1}","L");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY","|#eta_{#gamma D}| > 0.8 A1 #mu_{1}","L");
   entry->SetLineColor(1);
   entry->SetLineStyle(2);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   TLine *line = new TLine(4.3,0,4.3,1);

   ci = TColor::GetColor("#0000ff");
   line->SetLineColor(ci);
   line->SetLineStyle(2);
   line->Draw();
   line = new TLine(7.2,0,7.2,1);
   line->SetLineStyle(2);
   line->Draw();
   line = new TLine(11,0,11,1);
   line->SetLineStyle(2);
   line->Draw();
   line = new TLine(23.9,0,23.9,1);

   ci = TColor::GetColor("#00ff00");
   line->SetLineColor(ci);
   line->SetLineStyle(2);
   line->Draw();
   line = new TLine(60.5,0,60.5,1);

   ci = TColor::GetColor("#00ff00");
   line->SetLineColor(ci);
   line->SetLineStyle(2);
   line->Draw();
   eta_lxy->Modified();
   eta_lxy->cd();
   eta_lxy->SetSelected(eta_lxy);
}
