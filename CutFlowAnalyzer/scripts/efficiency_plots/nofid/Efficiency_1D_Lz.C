{
//=========Macro generated from canvas: effz2/effz2
//=========  (Thu May 11 04:01:02 2017) by ROOT version5.34/36
   TCanvas *effz2 = new TCanvas("effz2", "effz2",0,0,700,500);
   effz2->Range(-11,-0.125,99,1.125);
   effz2->SetFillColor(0);
   effz2->SetBorderMode(0);
   effz2->SetBorderSize(2);
   effz2->SetFrameBorderMode(0);
   effz2->SetFrameBorderMode(0);
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(20);
   grae->SetName("divide_num_1D_A0_LZ_by_den_1D_A0_LZ");
   grae->SetTitle("");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(21);
   grae->SetPoint(0,2,0.8906055);
   grae->SetPointError(0,2,2,0.002297786,0.002256681);
   grae->SetPoint(1,6,0.7926713);
   grae->SetPointError(1,2,2,0.00573699,0.00562398);
   grae->SetPoint(2,10,0.7530979);
   grae->SetPointError(2,2,2,0.007823576,0.007663591);
   grae->SetPoint(3,14,0.6563032);
   grae->SetPointError(3,2,2,0.01008038,0.009944386);
   grae->SetPoint(4,18,0.6249247);
   grae->SetPointError(4,2,2,0.01225374,0.01209956);
   grae->SetPoint(5,22,0.5502495);
   grae->SetPointError(5,2,2,0.01366937,0.01359585);
   grae->SetPoint(6,26,0.4881292);
   grae->SetPointError(6,2,2,0.01585945,0.01588268);
   grae->SetPoint(7,30,0.4371396);
   grae->SetPointError(7,2,2,0.01733765,0.01748751);
   grae->SetPoint(8,34,0.3993711);
   grae->SetPointError(8,2,2,0.02002622,0.02035515);
   grae->SetPoint(9,38,0.3917137);
   grae->SetPointError(9,2,2,0.02189097,0.02231646);
   grae->SetPoint(10,42,0.3660714);
   grae->SetPointError(10,2,2,0.02353585,0.02416219);
   grae->SetPoint(11,46,0.3055556);
   grae->SetPointError(11,2,2,0.02506319,0.02620325);
   grae->SetPoint(12,50,0.3432836);
   grae->SetPointError(12,2,2,0.03019082,0.03143265);
   grae->SetPoint(13,54,0.3050847);
   grae->SetPointError(13,2,2,0.0311439,0.03290776);
   grae->SetPoint(14,58,0.3050847);
   grae->SetPointError(14,2,2,0.03614458,0.03851821);
   grae->SetPoint(15,62,0.3216783);
   grae->SetPointError(15,2,2,0.04105807,0.04376313);
   grae->SetPoint(16,66,0.288);
   grae->SetPointError(16,2,2,0.04247703,0.04618482);
   grae->SetPoint(17,70,0.3333333);
   grae->SetPointError(17,2,2,0.04952459,0.05311279);
   grae->SetPoint(18,74,0.202381);
   grae->SetPointError(18,2,2,0.04555502,0.05354023);
   grae->SetPoint(19,78,0.32);
   grae->SetPointError(19,2,2,0.05744162,0.06278845);
   
   TH1F *Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3 = new TH1F("Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3","",100,0,88);
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3->SetMinimum(0);
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3->SetMaximum(1);
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3->SetDirectory(0);
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3->SetLineColor(ci);
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3->GetXaxis()->SetTitle("L_{Z} [cm]");
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3->GetXaxis()->SetLabelSize(0.035);
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3->GetXaxis()->SetTitleSize(0.035);
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3->GetYaxis()->SetTitle("Efficiency");
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3->GetYaxis()->SetLabelSize(0.035);
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3->GetYaxis()->SetTitleSize(0.035);
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_1D_A0_LZ_by_den_1D_A0_LZ3);
   
   grae->Draw("alp");
   
   grae = new TGraphAsymmErrors(20);
   grae->SetName("divide_num_1D_A1_LZ_by_den_1D_A1_LZ");
   grae->SetTitle("num_1D_A1_LZ");

   ci = TColor::GetColor("#0000ff");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#0000ff");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(21);
   grae->SetPoint(0,2,0.9051879);
   grae->SetPointError(0,2,2,0.002147454,0.002105278);
   grae->SetPoint(1,6,0.8109472);
   grae->SetPointError(1,2,2,0.00561321,0.005490367);
   grae->SetPoint(2,10,0.7512421);
   grae->SetPointError(2,2,2,0.008117191,0.00794728);
   grae->SetPoint(3,14,0.7033739);
   grae->SetPointError(3,2,2,0.01021753,0.01002247);
   grae->SetPoint(4,18,0.6700189);
   grae->SetPointError(4,2,2,0.01220871,0.01198937);
   grae->SetPoint(5,22,0.6259051);
   grae->SetPointError(5,2,2,0.01422578,0.01401736);
   grae->SetPoint(6,26,0.5712821);
   grae->SetPointError(6,2,2,0.01642896,0.0162781);
   grae->SetPoint(7,30,0.5195266);
   grae->SetPointError(7,2,2,0.01779214,0.01774437);
   grae->SetPoint(8,34,0.4653614);
   grae->SetPointError(8,2,2,0.02004034,0.02014863);
   grae->SetPoint(9,38,0.4990859);
   grae->SetPointError(9,2,2,0.02226953,0.02227301);
   grae->SetPoint(10,42,0.4481928);
   grae->SetPointError(10,2,2,0.02545381,0.02571541);
   grae->SetPoint(11,46,0.4255875);
   grae->SetPointError(11,2,2,0.02632984,0.02673783);
   grae->SetPoint(12,50,0.431746);
   grae->SetPointError(12,2,2,0.029218,0.0296751);
   grae->SetPoint(13,54,0.4206897);
   grae->SetPointError(13,2,2,0.03036916,0.0309474);
   grae->SetPoint(14,58,0.3429752);
   grae->SetPointError(14,2,2,0.03182305,0.03320503);
   grae->SetPoint(15,62,0.3837209);
   grae->SetPointError(15,2,2,0.03913909,0.04059176);
   grae->SetPoint(16,66,0.3643411);
   grae->SetPointError(16,2,2,0.04491883,0.04720301);
   grae->SetPoint(17,70,0.3680556);
   grae->SetPointError(17,2,2,0.04251368,0.0444957);
   grae->SetPoint(18,74,0.453125);
   grae->SetPointError(18,2,2,0.04730715,0.04810058);
   grae->SetPoint(19,78,0.4033613);
   grae->SetPointError(19,2,2,0.04806909,0.04983538);
   
   TH1F *Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ4 = new TH1F("Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ4","num_1D_A1_LZ",100,0,88);
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ4->SetMinimum(0.2515381);
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ4->SetMaximum(0.9669073);
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ4->SetDirectory(0);
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ4->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ4->SetLineColor(ci);
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ4->GetXaxis()->SetLabelFont(42);
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ4->GetXaxis()->SetLabelSize(0.035);
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ4->GetXaxis()->SetTitleSize(0.035);
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ4->GetXaxis()->SetTitleFont(42);
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ4->GetYaxis()->SetLabelFont(42);
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ4->GetYaxis()->SetLabelSize(0.035);
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ4->GetYaxis()->SetTitleSize(0.035);
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ4->GetYaxis()->SetTitleFont(42);
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ4->GetZaxis()->SetLabelFont(42);
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ4->GetZaxis()->SetLabelSize(0.035);
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ4->GetZaxis()->SetTitleSize(0.035);
   Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ4->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_divide_num_1D_A1_LZ_by_den_1D_A1_LZ4);
   
   grae->Draw("");
   
   TLegend *leg = new TLegend(0.1690544,0.1476793,0.3008596,0.3333333,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.045);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("divide_num_1D_A0_LXY_by_den_1D_A0_LXY","#gamma_{D1}","L");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("divide_num_1D_A1_LXY_by_den_1D_A1_LXY","#gamma_{D2}","L");

   ci = TColor::GetColor("#0000ff");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   effz2->Modified();
   effz2->cd();
   effz2->SetSelected(effz2);
}
