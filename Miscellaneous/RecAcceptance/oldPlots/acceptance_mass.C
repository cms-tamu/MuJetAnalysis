void acceptance_mass()
{
//=========Macro generated from canvas: c2/c2
//=========  (Sun Oct 18 11:11:51 2015) by ROOT version6.02/05
   TCanvas *c2 = new TCanvas("c2", "c2",0,22,700,500);
   gStyle->SetOptStat(0);
   c2->Range(-1.3125,-0.025,9.8125,0.225);
   c2->SetFillColor(0);
   c2->SetBorderMode(0);
   c2->SetBorderSize(2);
   c2->SetFrameBorderMode(0);
   c2->SetFrameBorderMode(0);
   
   TH2F *dummy42 = new TH2F("dummy42","dummy4",178,-0.2,8.7,100,0,0.2);
   dummy42->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   dummy42->SetLineColor(ci);
   dummy42->GetXaxis()->SetTitle("Mass [GeV]");
   dummy42->GetXaxis()->SetLabelFont(42);
   dummy42->GetXaxis()->SetLabelSize(0.035);
   dummy42->GetXaxis()->SetTitleSize(0.035);
   dummy42->GetXaxis()->SetTitleFont(42);
   dummy42->GetYaxis()->SetTitle("#epsilon_{rec} = N_{rec}/N_{tot}");
   dummy42->GetYaxis()->SetLabelFont(42);
   dummy42->GetYaxis()->SetLabelSize(0.035);
   dummy42->GetYaxis()->SetTitleSize(0.035);
   dummy42->GetYaxis()->SetTitleFont(42);
   dummy42->GetZaxis()->SetLabelFont(42);
   dummy42->GetZaxis()->SetLabelSize(0.035);
   dummy42->GetZaxis()->SetTitleSize(0.035);
   dummy42->GetZaxis()->SetTitleFont(42);
   dummy42->Draw("");
   
   Double_t Graph0_fx1006[4] = {
   0.25,
   0.275,
   0.3,
   2};
   Double_t Graph0_fy1006[4] = {
   0.0865404,
   0.08208333,
   0.0749858,
   0.05958333};
   Double_t Graph0_fex1006[4] = {
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1006[4] = {
   0.0009990599,
   0.0009753636,
   0.0009926071,
   0.0008541653};
   TGraphErrors *gre = new TGraphErrors(4,Graph0_fx1006,Graph0_fy1006,Graph0_fex1006,Graph0_fey1006);
   gre->SetName("Graph0");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetMarkerStyle(7);
   gre->SetMarkerSize(5);
   
   TH1F *Graph_Graph1006 = new TH1F("Graph_Graph1006","Graph",100,0.075,2.175);
   Graph_Graph1006->SetMinimum(0.05584814);
   Graph_Graph1006->SetMaximum(0.09042049);
   Graph_Graph1006->SetDirectory(0);
   Graph_Graph1006->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph1006->SetLineColor(ci);
   Graph_Graph1006->GetXaxis()->SetLabelFont(42);
   Graph_Graph1006->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1006->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1006->GetXaxis()->SetTitleFont(42);
   Graph_Graph1006->GetYaxis()->SetLabelFont(42);
   Graph_Graph1006->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1006->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1006->GetYaxis()->SetTitleFont(42);
   Graph_Graph1006->GetZaxis()->SetLabelFont(42);
   Graph_Graph1006->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1006->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1006->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1006);
   
   gre->Draw(" pl");
   
   Double_t Graph1_fx1007[4] = {
   0.25,
   0.275,
   2,
   8.5};
   Double_t Graph1_fy1007[4] = {
   0.08294682,
   0.07862374,
   0.06207908,
   0.137474};
   Double_t Graph1_fex1007[4] = {
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1007[4] = {
   0.0009899688,
   0.000956385,
   0.0008617826,
   0.001242555};
   gre = new TGraphErrors(4,Graph1_fx1007,Graph1_fy1007,Graph1_fex1007,Graph1_fey1007);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(7);
   gre->SetMarkerSize(5);
   
   TH1F *Graph_Graph1007 = new TH1F("Graph_Graph1007","Graph",100,0,9.325);
   Graph_Graph1007->SetMinimum(0.05346738);
   Graph_Graph1007->SetMaximum(0.1464664);
   Graph_Graph1007->SetDirectory(0);
   Graph_Graph1007->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph1007->SetLineColor(ci);
   Graph_Graph1007->GetXaxis()->SetLabelFont(42);
   Graph_Graph1007->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1007->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1007->GetXaxis()->SetTitleFont(42);
   Graph_Graph1007->GetYaxis()->SetLabelFont(42);
   Graph_Graph1007->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1007->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1007->GetYaxis()->SetTitleFont(42);
   Graph_Graph1007->GetZaxis()->SetLabelFont(42);
   Graph_Graph1007->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1007->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1007->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1007);
   
   gre->Draw(" pl");
   
   Double_t Graph2_fx1008[5] = {
   0.25,
   0.275,
   0.3,
   2,
   8.5};
   Double_t Graph2_fy1008[5] = {
   0.06949495,
   0.06748737,
   0.0642268,
   0.06051768,
   0.1364046};
   Double_t Graph2_fex1008[5] = {
   0,
   0,
   0,
   0,
   0};
   Double_t Graph2_fey1008[5] = {
   0.0009035941,
   0.000891407,
   0.0008800606,
   0.000847272,
   0.00123208};
   gre = new TGraphErrors(5,Graph2_fx1008,Graph2_fy1008,Graph2_fex1008,Graph2_fey1008);
   gre->SetName("Graph2");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetLineColor(3);
   gre->SetMarkerColor(3);
   gre->SetMarkerStyle(7);
   gre->SetMarkerSize(5);
   
   TH1F *Graph_Graph1008 = new TH1F("Graph_Graph1008","Graph",100,0,9.325);
   Graph_Graph1008->SetMinimum(0.05187377);
   Graph_Graph1008->SetMaximum(0.1454334);
   Graph_Graph1008->SetDirectory(0);
   Graph_Graph1008->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph1008->SetLineColor(ci);
   Graph_Graph1008->GetXaxis()->SetLabelFont(42);
   Graph_Graph1008->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1008->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1008->GetXaxis()->SetTitleFont(42);
   Graph_Graph1008->GetYaxis()->SetLabelFont(42);
   Graph_Graph1008->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1008->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1008->GetYaxis()->SetTitleFont(42);
   Graph_Graph1008->GetZaxis()->SetLabelFont(42);
   Graph_Graph1008->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1008->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1008->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1008);
   
   gre->Draw(" pl");
   
   Double_t Graph3_fx1009[5] = {
   0.25,
   0.275,
   0.3,
   2,
   8.5};
   Double_t Graph3_fy1009[5] = {
   0.04645202,
   0.04597222,
   0.04502717,
   0.05941919,
   0.1359975};
   Double_t Graph3_fex1009[5] = {
   0,
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1009[5] = {
   0.000747844,
   0.0007441589,
   0.0007643529,
   0.0008400378,
   0.001218037};
   gre = new TGraphErrors(5,Graph3_fx1009,Graph3_fy1009,Graph3_fex1009,Graph3_fey1009);
   gre->SetName("Graph3");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(7);
   gre->SetMarkerSize(5);
   
   TH1F *Graph_Graph1009 = new TH1F("Graph_Graph1009","Graph",100,0,9.325);
   Graph_Graph1009->SetMinimum(0.03496755);
   Graph_Graph1009->SetMaximum(0.1465108);
   Graph_Graph1009->SetDirectory(0);
   Graph_Graph1009->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph1009->SetLineColor(ci);
   Graph_Graph1009->GetXaxis()->SetLabelFont(42);
   Graph_Graph1009->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1009->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1009->GetXaxis()->SetTitleFont(42);
   Graph_Graph1009->GetYaxis()->SetLabelFont(42);
   Graph_Graph1009->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1009->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1009->GetYaxis()->SetTitleFont(42);
   Graph_Graph1009->GetZaxis()->SetLabelFont(42);
   Graph_Graph1009->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1009->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1009->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1009);
   
   gre->Draw(" pl");
   
   Double_t Graph4_fx1010[5] = {
   0.25,
   0.275,
   0.3,
   2,
   8.5};
   Double_t Graph4_fy1010[5] = {
   0.0157633,
   0.01659091,
   0.01693182,
   0.05516582,
   0.1364646};
   Double_t Graph4_fex1010[5] = {
   0,
   0,
   0,
   0,
   0};
   Double_t Graph4_fey1010[5] = {
   0.0004493916,
   0.0004538785,
   0.0004584384,
   0.0008153701,
   0.001219797};
   gre = new TGraphErrors(5,Graph4_fx1010,Graph4_fy1010,Graph4_fex1010,Graph4_fey1010);
   gre->SetName("Graph4");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetLineColor(6);
   gre->SetMarkerColor(6);
   gre->SetMarkerStyle(7);
   gre->SetMarkerSize(5);
   
   TH1F *Graph_Graph1010 = new TH1F("Graph_Graph1010","Graph",100,0,9.325);
   Graph_Graph1010->SetMinimum(0.003076858);
   Graph_Graph1010->SetMaximum(0.1499215);
   Graph_Graph1010->SetDirectory(0);
   Graph_Graph1010->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph1010->SetLineColor(ci);
   Graph_Graph1010->GetXaxis()->SetLabelFont(42);
   Graph_Graph1010->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1010->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1010->GetXaxis()->SetTitleFont(42);
   Graph_Graph1010->GetYaxis()->SetLabelFont(42);
   Graph_Graph1010->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1010->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1010->GetYaxis()->SetTitleFont(42);
   Graph_Graph1010->GetZaxis()->SetLabelFont(42);
   Graph_Graph1010->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1010->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1010->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1010);
   
   gre->Draw(" pl");
   
   Double_t Graph5_fx1011[4] = {
   0.25,
   0.275,
   2,
   8.5};
   Double_t Graph5_fy1011[4] = {
   0.005542929,
   0.005892857,
   0.04303571,
   0.132096};
   Double_t Graph5_fex1011[4] = {
   0,
   0,
   0,
   0};
   Double_t Graph5_fey1011[4] = {
   0.0002638154,
   0.0002733515,
   0.0007247769,
   0.001203145};
   gre = new TGraphErrors(4,Graph5_fx1011,Graph5_fy1011,Graph5_fex1011,Graph5_fey1011);
   gre->SetName("Graph5");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetLineColor(7);
   gre->SetMarkerColor(7);
   gre->SetMarkerStyle(7);
   gre->SetMarkerSize(5);
   
   TH1F *Graph_Graph1011 = new TH1F("Graph_Graph1011","Graph",100,0,9.325);
   Graph_Graph1011->SetMinimum(0);
   Graph_Graph1011->SetMaximum(0.1461011);
   Graph_Graph1011->SetDirectory(0);
   Graph_Graph1011->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph1011->SetLineColor(ci);
   Graph_Graph1011->GetXaxis()->SetLabelFont(42);
   Graph_Graph1011->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1011->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1011->GetXaxis()->SetTitleFont(42);
   Graph_Graph1011->GetYaxis()->SetLabelFont(42);
   Graph_Graph1011->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1011->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1011->GetYaxis()->SetTitleFont(42);
   Graph_Graph1011->GetZaxis()->SetLabelFont(42);
   Graph_Graph1011->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1011->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1011->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1011);
   
   gre->Draw(" pl");
   
   Double_t Graph6_fx1012[5] = {
   0.25,
   0.275,
   0.3,
   2,
   8.5};
   Double_t Graph6_fy1012[5] = {
   0.00155303,
   0.001868687,
   0.002222281,
   0.02356061,
   0.1211862};
   Double_t Graph6_fex1012[5] = {
   0,
   0,
   0,
   0,
   0};
   Double_t Graph6_fey1012[5] = {
   0.0001399232,
   0.0001534615,
   0.0001707546,
   0.000538956,
   0.001165513};
   gre = new TGraphErrors(5,Graph6_fx1012,Graph6_fy1012,Graph6_fex1012,Graph6_fey1012);
   gre->SetName("Graph6");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetLineColor(8);
   gre->SetMarkerColor(8);
   gre->SetMarkerStyle(7);
   gre->SetMarkerSize(5);
   
   TH1F *Graph_Graph1012 = new TH1F("Graph_Graph1012","Graph",100,0,9.325);
   Graph_Graph1012->SetMinimum(0);
   Graph_Graph1012->SetMaximum(0.1344456);
   Graph_Graph1012->SetDirectory(0);
   Graph_Graph1012->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph1012->SetLineColor(ci);
   Graph_Graph1012->GetXaxis()->SetLabelFont(42);
   Graph_Graph1012->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1012->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1012->GetXaxis()->SetTitleFont(42);
   Graph_Graph1012->GetYaxis()->SetLabelFont(42);
   Graph_Graph1012->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1012->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1012->GetYaxis()->SetTitleFont(42);
   Graph_Graph1012->GetZaxis()->SetLabelFont(42);
   Graph_Graph1012->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1012->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1012->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1012);
   
   gre->Draw(" pl");
   
   Double_t Graph7_fx1013[4] = {
   0.25,
   0.275,
   2,
   8.5};
   Double_t Graph7_fy1013[4] = {
   0.0009974747,
   0.0009974747,
   0.01513298,
   0.1061111};
   Double_t Graph7_fex1013[4] = {
   0,
   0,
   0,
   0};
   Double_t Graph7_fey1013[4] = {
   0.0001121687,
   0.0001121687,
   0.0004451866,
   0.001147773};
   gre = new TGraphErrors(4,Graph7_fx1013,Graph7_fy1013,Graph7_fex1013,Graph7_fey1013);
   gre->SetName("Graph7");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetLineColor(9);
   gre->SetMarkerColor(9);
   gre->SetMarkerStyle(7);
   gre->SetMarkerSize(5);
   
   TH1F *Graph_Graph1013 = new TH1F("Graph_Graph1013","Graph",100,0,9.325);
   Graph_Graph1013->SetMinimum(0);
   Graph_Graph1013->SetMaximum(0.1178962);
   Graph_Graph1013->SetDirectory(0);
   Graph_Graph1013->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph1013->SetLineColor(ci);
   Graph_Graph1013->GetXaxis()->SetLabelFont(42);
   Graph_Graph1013->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1013->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1013->GetXaxis()->SetTitleFont(42);
   Graph_Graph1013->GetYaxis()->SetLabelFont(42);
   Graph_Graph1013->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1013->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1013->GetYaxis()->SetTitleFont(42);
   Graph_Graph1013->GetZaxis()->SetLabelFont(42);
   Graph_Graph1013->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1013->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1013->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1013);
   
   gre->Draw(" pl");
   
   Double_t Graph8_fx1014[5] = {
   0.25,
   0.275,
   0.3,
   2,
   8.5};
   Double_t Graph8_fy1014[5] = {
   0.0002651515,
   0.0004419192,
   0.0003815789,
   0.006989796,
   0.07766414};
   Double_t Graph8_fex1014[5] = {
   0,
   0,
   0,
   0,
   0};
   Double_t Graph8_fey1014[5] = {
   5.785313e-05,
   7.468147e-05,
   7.084391e-05,
   0.0002975439,
   0.0009510256};
   gre = new TGraphErrors(5,Graph8_fx1014,Graph8_fy1014,Graph8_fex1014,Graph8_fey1014);
   gre->SetName("Graph8");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#ffcc00");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#ffcc00");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(7);
   gre->SetMarkerSize(5);
   
   TH1F *Graph_Graph1014 = new TH1F("Graph_Graph1014","Graph",100,0,9.325);
   Graph_Graph1014->SetMinimum(0);
   Graph_Graph1014->SetMaximum(0.08645595);
   Graph_Graph1014->SetDirectory(0);
   Graph_Graph1014->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph1014->SetLineColor(ci);
   Graph_Graph1014->GetXaxis()->SetLabelFont(42);
   Graph_Graph1014->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1014->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1014->GetXaxis()->SetTitleFont(42);
   Graph_Graph1014->GetYaxis()->SetLabelFont(42);
   Graph_Graph1014->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1014->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1014->GetYaxis()->SetTitleFont(42);
   Graph_Graph1014->GetZaxis()->SetLabelFont(42);
   Graph_Graph1014->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1014->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1014->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1014);
   
   gre->Draw(" pl");
   
   TLegend *leg = new TLegend(0.158046,0.5369979,0.5071839,0.8372093,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.045);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("Graph0","c#Tau=0.00 mm","PL");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(7);
   entry->SetMarkerSize(5);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph1","c#Tau=0.05 mm","PL");
   entry->SetLineColor(2);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(7);
   entry->SetMarkerSize(5);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph2","c#Tau=0.10 mm","PL");
   entry->SetLineColor(3);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(3);
   entry->SetMarkerStyle(7);
   entry->SetMarkerSize(5);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph3","c#Tau=0.20 mm","PL");
   entry->SetLineColor(4);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(4);
   entry->SetMarkerStyle(7);
   entry->SetMarkerSize(5);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph4","c#Tau=0.50 mm","PL");
   entry->SetLineColor(6);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(6);
   entry->SetMarkerStyle(7);
   entry->SetMarkerSize(5);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph5","c#Tau=1.00 mm","PL");
   entry->SetLineColor(7);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(7);
   entry->SetMarkerStyle(7);
   entry->SetMarkerSize(5);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph6","c#Tau=2.00 mm","PL");
   entry->SetLineColor(8);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(8);
   entry->SetMarkerStyle(7);
   entry->SetMarkerSize(5);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph7","c#Tau=3.00 mm","PL");
   entry->SetLineColor(9);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(9);
   entry->SetMarkerStyle(7);
   entry->SetMarkerSize(5);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph8","c#Tau=5.00 mm","PL");

   ci = TColor::GetColor("#ffcc00");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ffcc00");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(7);
   entry->SetMarkerSize(5);
   entry->SetTextFont(42);
   leg->Draw();
   
   TPaveText *pt = new TPaveText(0.4195977,0.9339831,0.5804023,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *AText = pt->AddText("dummy4");
   pt->Draw();
   c2->Modified();
   c2->cd();
   c2->SetSelected(c2);
}
