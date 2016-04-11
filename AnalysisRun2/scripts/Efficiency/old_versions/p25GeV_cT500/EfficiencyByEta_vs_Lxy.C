void EfficiencyByEta_vs_Lxy()
{
//=========Macro generated from canvas: eta_lxy/eta_lxy
//=========  (Wed Oct 28 08:48:45 2015) by ROOT version6.02/05
   TCanvas *eta_lxy = new TCanvas("eta_lxy", "eta_lxy",71,99,700,500);
   eta_lxy->Range(-15,-0.125,95,1.125);
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
   0.9041916,
   0.8774194,
   0.8184358,
   0.8381877,
   0.8735632,
   0.8239203,
   0.8613377,
   0.8152866,
   0.7259259,
   0.6594203,
   0.5838415,
   0.5108153,
   0.4686411,
   0.4130019,
   0.3320537,
   0.1867663,
   0.006};
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
   0.01892337,
   0.02155063,
   0.0226994,
   0.023725,
   0.02040164,
   0.02474564,
   0.01539287,
   0.02454227,
   0.02984042,
   0.01899282,
   0.02012469,
   0.02122296,
   0.02162311,
   0.02229047,
   0.02123546,
   0.0129128,
   0.001959686};
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
   0.01628284,
   0.01891001,
   0.02080173,
   0.02137171,
   0.01808561,
   0.02243524,
   0.01414627,
   0.02239228,
   0.02805688,
   0.0185126,
   0.0198592,
   0.02118553,
   0.02173682,
   0.02263752,
   0.02190935,
   0.01360897,
   0.002728157};
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
   Graph_divide_num_LEp8_1D_A0_LXY_by_den_LEp8_1D_A0_LXY3001->SetMaximum(1.012118);
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
   0.6481481,
   0.546875,
   0.5625,
   0.62,
   0.5098039,
   0.5106383,
   0.5487805,
   0.56,
   0.5869565,
   0.4226804,
   0.3186813,
   0.3092784,
   0.1935484,
   0.362069,
   0.2758621,
   0.1265823,
   0.01};
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
   0.07660054,
   0.07024511,
   0.08252993,
   0.0804924,
   0.07913821,
   0.08280313,
   0.06129672,
   0.08065244,
   0.08459361,
   0.05412955,
   0.05183638,
   0.04964651,
   0.05217956,
   0.06838673,
   0.06234882,
   0.03812865,
   0.008273954};
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
   0.07040901,
   0.06861333,
   0.07958834,
   0.07506644,
   0.07870561,
   0.08229174,
   0.05998547,
   0.07794705,
   0.08030995,
   0.05587582,
   0.0562379,
   0.05398158,
   0.06352952,
   0.07373092,
   0.07111118,
   0.04908684,
   0.02261812};
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
   Graph_divide_num_Gp8_1D_A0_LXY_by_den_Gp8_1D_A0_LXY3002->SetMaximum(0.7902403);
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
   0.5917266,
   0.6365385,
   0.6011029,
   0.5775862,
   0.5820225,
   0.5958763,
   0.5954654,
   0.5983607,
   0.5786802,
   0.4923913,
   0.4713764,
   0.3904494,
   0.3903509,
   0.3621908,
   0.3055556,
   0.1708428,
   0.004827031};
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
   0.02189608,
   0.02230776,
   0.02208692,
   0.02415653,
   0.02466934,
   0.02349548,
   0.01765839,
   0.02723558,
   0.0263201,
   0.01700799,
   0.01798313,
   0.0188122,
   0.01920291,
   0.02081363,
   0.0210868,
   0.01287575,
   0.001913048};
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
   0.02155228,
   0.02175933,
   0.02169939,
   0.02380686,
   0.02428352,
   0.02308235,
   0.0174227,
   0.0266704,
   0.025901,
   0.01702507,
   0.01805524,
   0.01913147,
   0.01953578,
   0.02132133,
   0.02189472,
   0.01365862,
   0.002871944};
   grae = new TGraphAsymmErrors(17,divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fx3003,divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fy3003,divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_felx3003,divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fehx3003,divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fely3003,divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY_fehy3003);
   grae->SetName("divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY");
   grae->SetTitle("num_LEp8_1D_A1_LXY");
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003 = new TH1F("Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003","num_LEp8_1D_A1_LXY",100,0,88);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003->SetMinimum(0);
   Graph_divide_num_LEp8_1D_A1_LXY_by_den_LEp8_1D_A1_LXY3003->SetMaximum(0.7238362);
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
   0.8157895,
   0.7384615,
   0.7571429,
   0.8194444,
   0.8214286,
   0.7301587,
   0.8129032,
   0.8113208,
   0.6351351,
   0.5648855,
   0.6742424,
   0.5747126,
   0.3465347,
   0.4880952,
   0.3176471,
   0.1796407,
   0.004219409};
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
   0.05551623,
   0.06588366,
   0.06215439,
   0.05706844,
   0.06634722,
   0.06749043,
   0.03668804,
   0.06950296,
   0.06429371,
   0.04747579,
   0.04584502,
   0.05932819,
   0.05036481,
   0.05993866,
   0.0536644,
   0.03052969,
   0.003490756};
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
   0.04605996,
   0.05759644,
   0.05386274,
   0.04693058,
   0.05302869,
   0.05923482,
   0.03225312,
   0.05587008,
   0.06023675,
   0.04640318,
   0.04297388,
   0.0574387,
   0.05369987,
   0.0602506,
   0.05841802,
   0.03473695,
   0.009635271};
   grae = new TGraphAsymmErrors(17,divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fx3004,divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fy3004,divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_felx3004,divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fehx3004,divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fely3004,divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY_fehy3004);
   grae->SetName("divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY");
   grae->SetTitle("num_Gp8_1D_A1_LXY");
   grae->SetLineStyle(2);
   grae->SetMarkerStyle(2);
   
   TH1F *Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004 = new TH1F("Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004","num_Gp8_1D_A1_LXY",100,0,88);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004->SetMinimum(0);
   Graph_divide_num_Gp8_1D_A1_LXY_by_den_Gp8_1D_A1_LXY3004->SetMaximum(0.9618301);
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

   ci = TColor::GetColor("#0000ff");
   line->SetLineColor(ci);
   line->SetLineStyle(2);
   line->Draw();
   line = new TLine(11,0,11,1);

   ci = TColor::GetColor("#0000ff");
   line->SetLineColor(ci);
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
