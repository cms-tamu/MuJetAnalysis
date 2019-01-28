void EfficiencyByEta_vs_Lz()
{
//=========Macro generated from canvas: eta_lz/eta_lz
//=========  (Tue Oct 27 11:35:30 2015) by ROOT version6.02/05
   TCanvas *eta_lz = new TCanvas("eta_lz", "eta_lz",321,1245,700,500);
   eta_lz->Range(-15,-0.1263381,95,1.137043);
   eta_lz->SetFillColor(0);
   eta_lz->SetBorderMode(0);
   eta_lz->SetBorderSize(2);
   eta_lz->SetFrameBorderMode(0);
   eta_lz->SetFrameBorderMode(0);
   
   TMultiGraph *multigraph = new TMultiGraph();
   multigraph->SetName("");
   multigraph->SetTitle("");
   
   Double_t divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fx3005[18] = {
   2,
   6,
   10,
   14,
   18,
   22,
   26,
   30,
   34,
   38,
   42,
   46,
   50,
   54,
   58,
   62,
   66,
   70};
   Double_t divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fy3005[18] = {
   0.937704,
   0.7922078,
   0.7325378,
   0.6741091,
   0.6201506,
   0.5637931,
   0.4565953,
   0.4230769,
   0.3585657,
   0.3341969,
   0.3033333,
   0.199005,
   0.1032258,
   0.04132231,
   0,
   0.01923077,
   0,
   0};
   Double_t divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_felx3005[18] = {
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2};
   Double_t divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fely3005[18] = {
   0.001426432,
   0.005476655,
   0.007764811,
   0.01000126,
   0.01203645,
   0.01504157,
   0.01722811,
   0.02000858,
   0.02208411,
   0.02482075,
   0.02746755,
   0.02896739,
   0.02476475,
   0.01773434,
   0,
   0.01591409,
   0,
   0};
   Double_t divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fehx3005[18] = {
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2};
   Double_t divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fehy3005[18] = {
   0.001396921,
   0.005373827,
   0.007626873,
   0.009848483,
   0.0118939,
   0.01492839,
   0.01732921,
   0.02025443,
   0.02267308,
   0.02572472,
   0.02885809,
   0.03221671,
   0.03053613,
   0.02698692,
   0.01960128,
   0.04283441,
   0.09234949,
   0.4586417};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(18,divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fx3005,divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fy3005,divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_felx3005,divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fehx3005,divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fely3005,divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ_fehy3005);
   grae->SetName("divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ");
   grae->SetTitle("num_LEp8_1D_A0_LZ");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005 = new TH1F("Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005","num_LEp8_1D_A0_LZ",100,0,79.2);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005->SetMinimum(0);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005->SetMaximum(1.033011);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005->SetDirectory(0);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005->SetLineColor(ci);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005->GetXaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005->GetXaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005->GetYaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005->GetYaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_LEp8_1D_A0_LZ_by_den_LEp8_1D_A0_LZ3005);
   
   multigraph->Add(grae,"");
   
   Double_t divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fx3006[20] = {
   2,
   6,
   10,
   14,
   18,
   22,
   26,
   30,
   34,
   38,
   42,
   46,
   50,
   54,
   58,
   62,
   66,
   70,
   74,
   78};
   Double_t divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fy3006[20] = {
   0.9159326,
   0.7907389,
   0.7246975,
   0.6802189,
   0.6661475,
   0.5977011,
   0.5885609,
   0.5675105,
   0.5255172,
   0.508982,
   0.4889643,
   0.4496644,
   0.4254279,
   0.4169279,
   0.3861671,
   0.3481781,
   0.3471074,
   0.3665158,
   0.4313725,
   0.2634731};
   Double_t divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_felx3006[20] = {
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2};
   Double_t divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fely3006[20] = {
   0.001597039,
   0.005294978,
   0.007607062,
   0.009487171,
   0.01109092,
   0.01356948,
   0.01548456,
   0.01668252,
   0.01925774,
   0.02008931,
   0.0214076,
   0.02450115,
   0.02544577,
   0.02885085,
   0.02719145,
   0.03161684,
   0.03192751,
   0.03395104,
   0.04267398,
   0.03544632};
   Double_t divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fehx3006[20] = {
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2};
   Double_t divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fehy3006[20] = {
   0.001570219,
   0.005199705,
   0.007481192,
   0.009343312,
   0.01091428,
   0.01342534,
   0.01531621,
   0.01653552,
   0.01918479,
   0.0200614,
   0.02144657,
   0.02473674,
   0.02582808,
   0.02940017,
   0.02788246,
   0.03292491,
   0.03327288,
   0.03523965,
   0.04364022,
   0.03851602};
   grae = new TGraphAsymmErrors(20,divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fx3006,divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fy3006,divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_felx3006,divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fehx3006,divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fely3006,divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ_fehy3006);
   grae->SetName("divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ");
   grae->SetTitle("num_LEp8_1D_A1_LZ");
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006 = new TH1F("Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006","num_LEp8_1D_A1_LZ",100,0,88);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006->SetMinimum(0.1590791);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006->SetMaximum(0.9864504);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006->SetDirectory(0);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006->SetLineColor(ci);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006->GetXaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006->GetXaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006->GetYaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006->GetYaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_LEp8_1D_A1_LZ_by_den_LEp8_1D_A1_LZ3006);
   
   multigraph->Add(grae,"");
   
   Double_t divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fx3007[20] = {
   2,
   6,
   10,
   14,
   18,
   22,
   26,
   30,
   34,
   38,
   42,
   46,
   50,
   54,
   58,
   62,
   66,
   70,
   74,
   78};
   Double_t divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fy3007[20] = {
   0.9602346,
   0.8914641,
   0.8292683,
   0.8123012,
   0.7651246,
   0.7387518,
   0.7071547,
   0.6441516,
   0.60625,
   0.6384977,
   0.5151515,
   0.5427729,
   0.4736842,
   0.4042553,
   0.394052,
   0.3670886,
   0.2983871,
   0.255814,
   0.3089005,
   0.2341772};
   Double_t divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_felx3007[20] = {
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2};
   Double_t divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fely3007[20] = {
   0.002476874,
   0.007907895,
   0.0116176,
   0.01358605,
   0.01551365,
   0.01781265,
   0.0197396,
   0.02048726,
   0.02354891,
   0.02476329,
   0.02761246,
   0.02862034,
   0.03013812,
   0.03058043,
   0.03117391,
   0.03275091,
   0.0301441,
   0.03079533,
   0.03488295,
   0.03492248};
   Double_t divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fehx3007[20] = {
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2};
   Double_t divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fehy3007[20] = {
   0.002341187,
   0.00744854,
   0.01104269,
   0.01289651,
   0.01485957,
   0.0170902,
   0.01902008,
   0.01999267,
   0.02308613,
   0.02408128,
   0.02752475,
   0.02835473,
   0.03032081,
   0.03129906,
   0.0320088,
   0.03394491,
   0.03187843,
   0.03323717,
   0.03703351,
   0.03858853};
   grae = new TGraphAsymmErrors(20,divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fx3007,divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fy3007,divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_felx3007,divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fehx3007,divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fely3007,divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ_fehy3007);
   grae->SetName("divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ");
   grae->SetTitle("num_Gp8_1D_A0_LZ");

   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);
   grae->SetLineStyle(2);

   ci = TColor::GetColor("#ff0000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007 = new TH1F("Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007","num_Gp8_1D_A0_LZ",100,0,88);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007->SetMinimum(0.1229226);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007->SetMaximum(1.038908);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007->SetDirectory(0);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007->SetLineColor(ci);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007->GetXaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007->GetXaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007->GetYaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007->GetYaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_Gp8_1D_A0_LZ_by_den_Gp8_1D_A0_LZ3007);
   
   multigraph->Add(grae,"");
   
   Double_t divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fx3008[20] = {
   2,
   6,
   10,
   14,
   18,
   22,
   26,
   30,
   34,
   38,
   42,
   46,
   50,
   54,
   58,
   62,
   66,
   70,
   74,
   78};
   Double_t divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fy3008[20] = {
   0.9405691,
   0.8371474,
   0.7836153,
   0.7245146,
   0.6649746,
   0.6493213,
   0.5677233,
   0.5,
   0.5528846,
   0.4778325,
   0.4050633,
   0.4333333,
   0.33,
   0.3026316,
   0.3157895,
   0.173913,
   0.3617021,
   0.375,
   0.5806452,
   0.2083333};
   Double_t divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_felx3008[20] = {
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2};
   Double_t divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fely3008[20] = {
   0.002641702,
   0.008967871,
   0.01299047,
   0.01644465,
   0.02053595,
   0.02415605,
   0.0281983,
   0.03221759,
   0.03705531,
   0.03730662,
   0.04143097,
   0.04857761,
   0.04988652,
   0.05598534,
   0.05679527,
   0.04716961,
   0.07644599,
   0.08423524,
   0.1058249,
   0.08686774};
   Double_t divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fehx3008[20] = {
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2,
   2};
   Double_t divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fehy3008[20] = {
   0.002538323,
   0.008597916,
   0.01246735,
   0.01587888,
   0.01995394,
   0.02344771,
   0.02778756,
   0.03221759,
   0.03651301,
   0.03753963,
   0.04272481,
   0.04978454,
   0.05362362,
   0.06177717,
   0.06219399,
   0.05801586,
   0.08312783,
   0.09138358,
   0.09980968,
   0.1163792};
   grae = new TGraphAsymmErrors(20,divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fx3008,divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fy3008,divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_felx3008,divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fehx3008,divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fely3008,divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ_fehy3008);
   grae->SetName("divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ");
   grae->SetTitle("num_Gp8_1D_A1_LZ");

   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);
   grae->SetLineStyle(2);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008 = new TH1F("Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008","num_Gp8_1D_A1_LZ",100,0,88);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008->SetMinimum(0.03930142);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008->SetMaximum(1.025272);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008->SetDirectory(0);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008->SetLineColor(ci);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008->GetXaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008->GetXaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008->GetYaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008->GetYaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_Gp8_1D_A1_LZ_by_den_Gp8_1D_A1_LZ3008);
   
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
   
   TLegend *leg = new TLegend(0.1695402,0.1458774,0.2816092,0.4460888,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.045);
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

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
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
