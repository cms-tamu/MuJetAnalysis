from ROOT import *
import numpy as np

e_over_a_darksusy = {
    '0p25' : {
        '0' : [0.675, 0.009],
        '0p05' : [0.659, 0.009],
        '0p1' : [0.627, 0.004],
        '0p5' : [0.616, 0.006],
        '1' : [0.602, 0.013],
        '2' : [0.657, 0.009],
        '5' : [0.584, 0.020],
        '20' : [0.584, 0.040],
        '100' : [0.250, 0.217],
        }, 
    '0p4' : {
        '0' : [0.657, 0.005],
        '0p5' : [0.598, 0.006],
        '1' : [0.587, 0.005],
        '2' : [0.590, 0.008],
        '5' : [0.624, 0.023],
        '20' : [0.586, 0.043],
        '100' : [0.250, 0.217],
        },
    '0p7' : {
        '0' :   [0.651, 0.006],
        '0p5' : [0.606, 0.012],
        '1' :   [0.592, 0.005],
        '20' :  [0.632, 0.025],
        '100' : [0.500, 0.144],
        },
    '1p0' : {
        '0' :   [0.644, 0.006],
        '5' :   [0.627, 0.010],
        '20' :  [0.658, 0.025],
        '100' : [0.200, 0.179],
        },
    '5p0' : {
        '0' : [0.629, 0.005],
        '20' : [0.579, 0.013],
        '100' : [0.672, 0.029],
        },
    '8p5' : {
        '0' : [0.624, 0.004],
        '2' : [0.611, 0.002],
        '20' : [0.587, 0.002],
        '100' : [0.592, 0.007],
        },
}

## make histograms
g_darksusy_x_0p25 = [ 0, 0.05, 0.1, 0.5, 1, 2, 5, 20, 100]
g_darksusy_x_0p25_errors = [0,0,0, 0,0,0, 0,0,0]

g_darksusy_x_0p4 = [ 0, 0.5, 1, 2, 5, 20, 100]
g_darksusy_x_0p4_errors = [0,0,0,0,0,0,0]

g_darksusy_y_0p25 = [
    e_over_a_darksusy['0p25']['0'][0],
    e_over_a_darksusy['0p25']['0p05'][0],
    e_over_a_darksusy['0p25']['0p1'][0],
    e_over_a_darksusy['0p25']['0p5'][0],
    e_over_a_darksusy['0p25']['1'][0],
    e_over_a_darksusy['0p25']['2'][0],
    e_over_a_darksusy['0p25']['5'][0],
    e_over_a_darksusy['0p25']['20'][0],
    e_over_a_darksusy['0p25']['100'][0]
]
g_darksusy_y_0p25_errors = [
    e_over_a_darksusy['0p25']['0'][1],
    e_over_a_darksusy['0p25']['0p05'][1],
    e_over_a_darksusy['0p25']['0p1'][1],
    e_over_a_darksusy['0p25']['0p5'][1],
    e_over_a_darksusy['0p25']['1'][1],
    e_over_a_darksusy['0p25']['2'][1],
    e_over_a_darksusy['0p25']['5'][1],
    e_over_a_darksusy['0p25']['20'][1],
    e_over_a_darksusy['0p25']['100'][1]
]


g_darksusy_y_0p4 = [
    e_over_a_darksusy['0p4']['0'][0],
    e_over_a_darksusy['0p4']['0p5'][0],
    e_over_a_darksusy['0p4']['1'][0],
    e_over_a_darksusy['0p4']['2'][0],
    e_over_a_darksusy['0p4']['5'][0],
    e_over_a_darksusy['0p4']['20'][0],
    e_over_a_darksusy['0p4']['100'][0]
]
g_darksusy_y_0p4_errors = [
    e_over_a_darksusy['0p4']['0'][1],
    e_over_a_darksusy['0p4']['0p5'][1],
    e_over_a_darksusy['0p4']['1'][1],
    e_over_a_darksusy['0p4']['2'][1],
    e_over_a_darksusy['0p4']['5'][1],
    e_over_a_darksusy['0p4']['20'][1],
    e_over_a_darksusy['0p4']['100'][1]
]


g_darksusy_x_0p7 = [ 0, 0.5, 1, 20, 100]
g_darksusy_x_0p7_errors = [0,0,0,0,0]

g_darksusy_y_0p7 = [
    e_over_a_darksusy['0p7']['0'][0],
    e_over_a_darksusy['0p7']['0p5'][0],
    e_over_a_darksusy['0p7']['1'][0],
    e_over_a_darksusy['0p7']['20'][0],
    e_over_a_darksusy['0p7']['100'][0]
]
g_darksusy_y_0p7_errors = [
    e_over_a_darksusy['0p7']['0'][1],
    e_over_a_darksusy['0p7']['0p5'][1],
    e_over_a_darksusy['0p7']['1'][1],
    e_over_a_darksusy['0p7']['20'][1],
    e_over_a_darksusy['0p7']['100'][1]
]


g_darksusy_x_1p0 = [ 0, 5, 20, 100]
g_darksusy_x_1p0_errors = [0, 0, 0, 0]

g_darksusy_y_1p0 = [
    e_over_a_darksusy['1p0']['0'][0],
    e_over_a_darksusy['1p0']['5'][0],
    e_over_a_darksusy['1p0']['20'][0],
    e_over_a_darksusy['1p0']['100'][0]
]
g_darksusy_y_1p0_errors = [
    e_over_a_darksusy['1p0']['0'][1],
    e_over_a_darksusy['1p0']['5'][1],
    e_over_a_darksusy['1p0']['20'][1],
    e_over_a_darksusy['1p0']['100'][1]
]


g_darksusy_x_5p0 = [ 0, 20, 100]
g_darksusy_x_5p0_errors = [0, 0, 0]

g_darksusy_y_5p0 = [
    e_over_a_darksusy['5p0']['0'][0],
    e_over_a_darksusy['5p0']['20'][0],
    e_over_a_darksusy['5p0']['100'][0],
]
g_darksusy_y_5p0_errors = [
    e_over_a_darksusy['5p0']['0'][1],
    e_over_a_darksusy['5p0']['20'][1],
    e_over_a_darksusy['5p0']['100'][1],
]

g_darksusy_x_8p5 = [ 0, 2, 20, 100]
g_darksusy_x_8p5_errors = [0, 0, 0, 0]

g_darksusy_y_8p5 = [
    e_over_a_darksusy['8p5']['0'][0],
    e_over_a_darksusy['8p5']['2'][0],
    e_over_a_darksusy['8p5']['20'][0],
    e_over_a_darksusy['8p5']['100'][0],
]
g_darksusy_y_8p5_errors = [
    e_over_a_darksusy['8p5']['0'][1],
    e_over_a_darksusy['8p5']['2'][1],
    e_over_a_darksusy['8p5']['20'][1],
    e_over_a_darksusy['8p5']['100'][1],
]


g_darksusy_0p25 = TGraphErrors(
    len(g_darksusy_x_0p25), 
    np.array(g_darksusy_x_0p25), 
    np.array(g_darksusy_y_0p25), 
    np.array(g_darksusy_x_0p25_errors), 
    np.array(g_darksusy_y_0p25_errors))

g_darksusy_0p4 = TGraphErrors(
    len(g_darksusy_x_0p4), 
    np.array(g_darksusy_x_0p4), 
    np.array(g_darksusy_y_0p4), 
    np.array(g_darksusy_x_0p4_errors), 
    np.array(g_darksusy_y_0p4_errors))

g_darksusy_0p7 = TGraphErrors(
    len(g_darksusy_x_0p7), 
    np.array(g_darksusy_x_0p7), 
    np.array(g_darksusy_y_0p7), 
    np.array(g_darksusy_x_0p7_errors), 
    np.array(g_darksusy_y_0p7_errors))

g_darksusy_1p0 = TGraphErrors(
    4,
    np.array(g_darksusy_x_1p0),
    np.array(g_darksusy_y_1p0),
    np.array(g_darksusy_x_1p0_errors),
    np.array(g_darksusy_y_1p0_errors))

print g_darksusy_x_1p0, len(g_darksusy_x_1p0) 
print g_darksusy_y_1p0, len(g_darksusy_y_1p0)
print g_darksusy_x_1p0_errors, len(g_darksusy_x_1p0_errors)
print g_darksusy_y_1p0_errors, len(g_darksusy_y_1p0_errors)

g_darksusy_5p0 = TGraphErrors(
    len(g_darksusy_x_5p0),
    np.array(g_darksusy_x_5p0),
    np.array(g_darksusy_y_5p0),
    np.array(g_darksusy_x_5p0_errors),
    np.array(g_darksusy_y_5p0_errors))

g_darksusy_8p5 = TGraphErrors(
    len(g_darksusy_x_8p5),
    np.array(g_darksusy_x_8p5),
    np.array(g_darksusy_y_8p5),
    np.array(g_darksusy_x_8p5_errors),
    np.array(g_darksusy_y_8p5_errors))

g_darksusy_0p25.SetMarkerColor(kBlack)
g_darksusy_0p4.SetMarkerColor(kRed)
g_darksusy_0p7.SetMarkerColor(kBlue)
g_darksusy_1p0.SetMarkerColor(kOrange-3)
g_darksusy_5p0.SetMarkerColor(kGreen+2)
g_darksusy_8p5.SetMarkerColor(kMagenta+1)

g_darksusy_0p25.SetLineColor(kBlack)
g_darksusy_0p4.SetLineColor(kRed)
g_darksusy_0p7.SetLineColor(kBlue)
g_darksusy_1p0.SetLineColor(kOrange-3)
g_darksusy_5p0.SetLineColor(kGreen+2)
g_darksusy_8p5.SetLineColor(kMagenta+1)

g_darksusy_0p25.SetLineWidth(2)
g_darksusy_0p4.SetLineWidth(2)
g_darksusy_0p7.SetLineWidth(2)
g_darksusy_1p0.SetLineWidth(2)
g_darksusy_5p0.SetLineWidth(2)
g_darksusy_8p5.SetLineWidth(2)

g_darksusy_0p25.SetMarkerStyle(20)
g_darksusy_0p4.SetMarkerStyle(21)
g_darksusy_0p7.SetMarkerStyle(22)
g_darksusy_1p0.SetMarkerStyle(23)
g_darksusy_5p0.SetMarkerStyle(24)
g_darksusy_8p5.SetMarkerStyle(25)

g_darksusy_0p25.SetLineStyle(1)
g_darksusy_0p4.SetLineStyle(2)
g_darksusy_0p7.SetLineStyle(3)
g_darksusy_1p0.SetLineStyle(4)
g_darksusy_5p0.SetLineStyle(5)
g_darksusy_8p5.SetLineStyle(6)

cdark = TCanvas("c","",321,1245,800,600)
cdark.cd()
basedark = TH1F("basedark","",10000,0.025,100);
gPad.SetLogx()
gPad.SetGridx(1)
gPad.SetGridy(1)
gStyle.SetOptStat(00000)
basedark.GetXaxis().SetTitle("c#tau [mm]");
basedark.GetXaxis().SetLabelFont(42);
basedark.GetXaxis().SetLabelSize(0.035);
basedark.GetXaxis().SetTitleSize(0.035);
basedark.GetXaxis().SetTitleFont(42);
basedark.GetYaxis().SetTitle("#epsilon_{Full}/#alpha_{GEN}");
basedark.GetYaxis().SetLabelFont(42);
basedark.GetYaxis().SetLabelSize(0.035);
basedark.GetYaxis().SetTitleSize(0.035);
basedark.GetYaxis().SetTitleFont(42);
basedark.SetMaximum(1)
basedark.SetMinimum(0)
basedark.Draw("");

g_darksusy_0p25.Draw("PL")
g_darksusy_0p4.Draw("PL")
g_darksusy_0p7.Draw("PL")
g_darksusy_1p0.Draw("PL")
g_darksusy_5p0.Draw("PL")
g_darksusy_8p5.Draw("PL")

legdark = TLegend(0.15,0.15,0.5,0.45,"Dark photon mass m_{#gamma_{D}} [GeV]");
legdark.SetTextSize(0.04);
legdark.SetLineColor(1);
legdark.SetLineStyle(1);
legdark.SetLineWidth(1);
legdark.SetFillColor(0);
legdark.SetFillStyle(1001);

legdark.AddEntry(g_darksusy_0p25,"0.25","PL");
legdark.AddEntry(g_darksusy_0p4,"0.4","PL");
legdark.AddEntry(g_darksusy_0p7,"0.7","PL");
legdark.AddEntry(g_darksusy_1p0,"1.0","PL");
legdark.AddEntry(g_darksusy_5p0,"5.0","PL");
legdark.AddEntry(g_darksusy_8p5,"8.5","PL");

legdark.Draw("same")

cdark.SaveAs("epsilon_over_alpha_darksusy_SD.pdf")
cdark.SaveAs("epsilon_over_alpha_darksusy_SD.C")




e_over_a_nmssm = {
    '90' : {
        '0p25' : [0.647, 0.002],
        '0p5' : [0.644, 0.003],
        '0p75' : [0.643, 0.003],
        '1' : [0.640, 0.003],
        '2' : [0.635, 0.003],
        '3' : [0.629, 0.003],
        '3p55' : [0.62725,0.003],
        },
    '100' : {
        '0p25' : [0.637, 0.002],
        '0p5' : [0.646, 0.002],
        '0p75' : [0.637, 0.003],
        '1' : [0.635, 0.003],
        '2' : [0.631, 0.003],
        '3' : [0.626, 0.003],
        '3p55' : [0.6248,0.003],
        },
    '110' : {
        '0p25' : [0.634, 0.002],
        '0p5' : [0.633, 0.002],
        '0p75' : [0.631, 0.002],
        '1' : [0.628, 0.002],
        '2' : [0.626, 0.002],
        '3' : [0.622, 0.002],
        '3p55' : [0.6229,0.002],
        },
    '125' : {
        '0p25' : [0.616, 0.002],
        '0p5' : [0.626, 0.002],
        '0p75' : [0.627, 0.002],
        '1' : [0.622, 0.002],
        '2' : [0.619, 0.002],
        '3' : [0.612, 0.002],
        '3p55' : [0.61435,0.002],
        },
    '150' : {
        '0p25' : [0.591, 0.002],
        '0p5' : [0.617, 0.002],
        '0p75' : [0.617, 0.002],
        '1' : [0.611, 0.002],
        '2' : [0.608, 0.002],
        '3' : [0.602, 0.002],
        '3p55' : [0.60335,0.002],
        },
}
## make histograms
g_nmssm_x = [ 0.25, 0.5, 0.75, 1, 2, 3, 3.55]
g_nmssm_x_errors = [0,0,0,0,0,0,0]

g_nmssm_y_90 = [
    e_over_a_nmssm['90']['0p25'][0],
    e_over_a_nmssm['90']['0p5'][0],
    e_over_a_nmssm['90']['0p75'][0],
    e_over_a_nmssm['90']['1'][0],
    e_over_a_nmssm['90']['2'][0],
    e_over_a_nmssm['90']['3'][0],
    e_over_a_nmssm['90']['3p55'][0]
]
g_nmssm_y_errors_90 = [
    e_over_a_nmssm['90']['0p25'][1],
    e_over_a_nmssm['90']['0p5'][1],
    e_over_a_nmssm['90']['0p75'][1],
    e_over_a_nmssm['90']['1'][1],
    e_over_a_nmssm['90']['2'][1],
    e_over_a_nmssm['90']['3'][1],
    e_over_a_nmssm['90']['3p55'][1]
]

g_nmssm_y_100 = [
    e_over_a_nmssm['100']['0p25'][0],
    e_over_a_nmssm['100']['0p5'][0],
    e_over_a_nmssm['100']['0p75'][0],
    e_over_a_nmssm['100']['1'][0],
    e_over_a_nmssm['100']['2'][0],
    e_over_a_nmssm['100']['3'][0],
    e_over_a_nmssm['100']['3p55'][0]
]
g_nmssm_y_errors_100 = [
    e_over_a_nmssm['100']['0p25'][1],
    e_over_a_nmssm['100']['0p5'][1],
    e_over_a_nmssm['100']['0p75'][1],
    e_over_a_nmssm['100']['1'][1],
    e_over_a_nmssm['100']['2'][1],
    e_over_a_nmssm['100']['3'][1],
    e_over_a_nmssm['100']['3p55'][1]
]

g_nmssm_y_110 = [
    e_over_a_nmssm['110']['0p25'][0],
    e_over_a_nmssm['110']['0p5'][0],
    e_over_a_nmssm['110']['0p75'][0],
    e_over_a_nmssm['110']['1'][0],
    e_over_a_nmssm['110']['2'][0],
    e_over_a_nmssm['110']['3'][0],
    e_over_a_nmssm['110']['3p55'][0]
]
g_nmssm_y_errors_110 = [
    e_over_a_nmssm['110']['0p25'][1],
    e_over_a_nmssm['110']['0p5'][1],
    e_over_a_nmssm['110']['0p75'][1],
    e_over_a_nmssm['110']['1'][1],
    e_over_a_nmssm['110']['2'][1],
    e_over_a_nmssm['110']['3'][1],
    e_over_a_nmssm['110']['3p55'][1]
]

g_nmssm_y_125 = [
    e_over_a_nmssm['125']['0p25'][0],
    e_over_a_nmssm['125']['0p5'][0],
    e_over_a_nmssm['125']['0p75'][0],
    e_over_a_nmssm['125']['1'][0],
    e_over_a_nmssm['125']['2'][0],
    e_over_a_nmssm['125']['3'][0],
    e_over_a_nmssm['125']['3p55'][0]
]
g_nmssm_y_errors_125 = [
    e_over_a_nmssm['125']['0p25'][1],
    e_over_a_nmssm['125']['0p5'][1],
    e_over_a_nmssm['125']['0p75'][1],
    e_over_a_nmssm['125']['1'][1],
    e_over_a_nmssm['125']['2'][1],
    e_over_a_nmssm['125']['3'][1],
    e_over_a_nmssm['125']['3p55'][1]
]

g_nmssm_y_150 = [
    e_over_a_nmssm['150']['0p25'][0],
    e_over_a_nmssm['150']['0p5'][0],
    e_over_a_nmssm['150']['0p75'][0],
    e_over_a_nmssm['150']['1'][0],
    e_over_a_nmssm['150']['2'][0],
    e_over_a_nmssm['150']['3'][0],
    e_over_a_nmssm['150']['3p55'][0]
]
g_nmssm_y_errors_150 = [
    e_over_a_nmssm['150']['0p25'][1],
    e_over_a_nmssm['150']['0p5'][1],
    e_over_a_nmssm['150']['0p75'][1],
    e_over_a_nmssm['150']['1'][1],
    e_over_a_nmssm['150']['2'][1],
    e_over_a_nmssm['150']['3'][1],
    e_over_a_nmssm['150']['3p55'][1]
]


g_nmssm_90 = TGraphErrors(len(g_nmssm_x), 
                          np.array(g_nmssm_x), 
                          np.array(g_nmssm_y_90), 
                          np.array(g_nmssm_x_errors), 
                          np.array(g_nmssm_y_errors_90))
g_nmssm_100 = TGraphErrors(len(g_nmssm_x), 
                          np.array(g_nmssm_x), 
                          np.array(g_nmssm_y_100), 
                          np.array(g_nmssm_x_errors), 
                          np.array(g_nmssm_y_errors_100))
g_nmssm_110 = TGraphErrors(len(g_nmssm_x), 
                          np.array(g_nmssm_x), 
                          np.array(g_nmssm_y_110), 
                          np.array(g_nmssm_x_errors), 
                          np.array(g_nmssm_y_errors_110))
g_nmssm_125 = TGraphErrors(len(g_nmssm_x), 
                          np.array(g_nmssm_x), 
                          np.array(g_nmssm_y_125), 
                          np.array(g_nmssm_x_errors), 
                          np.array(g_nmssm_y_errors_125))
g_nmssm_150 = TGraphErrors(len(g_nmssm_x), 
                          np.array(g_nmssm_x), 
                          np.array(g_nmssm_y_150), 
                          np.array(g_nmssm_x_errors), 
                          np.array(g_nmssm_y_errors_150))


g_nmssm_90.SetMarkerColor(kBlack)
g_nmssm_100.SetMarkerColor(kRed)
g_nmssm_110.SetMarkerColor(kBlue)
g_nmssm_125.SetMarkerColor(kOrange-3)
g_nmssm_150.SetMarkerColor(kGreen+2)

g_nmssm_90.SetLineColor(kBlack)
g_nmssm_100.SetLineColor(kRed)
g_nmssm_110.SetLineColor(kBlue)
g_nmssm_125.SetLineColor(kOrange-3)
g_nmssm_150.SetLineColor(kGreen+2)

g_nmssm_90.SetLineWidth(2)
g_nmssm_100.SetLineWidth(2)
g_nmssm_110.SetLineWidth(2)
g_nmssm_125.SetLineWidth(2)
g_nmssm_150.SetLineWidth(2)

g_nmssm_90.SetMarkerStyle(20)
g_nmssm_100.SetMarkerStyle(21)
g_nmssm_110.SetMarkerStyle(22)
g_nmssm_125.SetMarkerStyle(23)
g_nmssm_150.SetMarkerStyle(24)

g_nmssm_90.SetLineStyle(1)
g_nmssm_100.SetLineStyle(2)
g_nmssm_110.SetLineStyle(3)
g_nmssm_125.SetLineStyle(4)
g_nmssm_150.SetLineStyle(5)

##print g_nmssm_90.Eval(3.55)
#print g_nmssm_100.Eval(3.55)
#print g_nmssm_110.Eval(3.55)
#print g_nmssm_125.Eval(3.55)
#print g_nmssm_150.Eval(3.55)

c = TCanvas("c","",321,1245,800,600)
c.cd()
base = TH1F("base","",10,0.2,3.75);
#gPad.SetLogx()
gPad.SetGridx(1)
gPad.SetGridy(1)
gStyle.SetOptStat(00000)
base.GetXaxis().SetTitle("m_{a} [GeV]");
base.GetXaxis().SetLabelFont(42);
base.GetXaxis().SetLabelSize(0.035);
base.GetXaxis().SetTitleSize(0.035);
base.GetXaxis().SetTitleFont(42);
base.GetYaxis().SetTitle("#epsilon_{Full}/#alpha_{GEN}");
base.GetYaxis().SetLabelFont(42);
base.GetYaxis().SetLabelSize(0.035);
base.GetYaxis().SetTitleSize(0.035);
base.GetYaxis().SetTitleFont(42);
base.SetMaximum(1)
base.SetMinimum(0)
base.Draw("");

g_nmssm_90.Draw("PL")
g_nmssm_100.Draw("PL")
g_nmssm_110.Draw("PL")
g_nmssm_125.Draw("PL")
g_nmssm_150.Draw("PL")

leg = TLegend(0.15,0.15,0.5,0.45,"Higgs boson mass m_{h} [GeV]");
#leg.SetBorderSize(0);
leg.SetTextSize(0.04);
leg.SetLineColor(1);
leg.SetLineStyle(1);
leg.SetLineWidth(1);
leg.SetFillColor(0);
leg.SetFillStyle(1001);

leg.AddEntry(g_nmssm_90,"90","PL");
leg.AddEntry(g_nmssm_100,"100","PL");
leg.AddEntry(g_nmssm_110,"110","PL");
leg.AddEntry(g_nmssm_125,"125","PL");
leg.AddEntry(g_nmssm_150,"150","PL");

leg.Draw("same")

c.SaveAs("epsilon_over_alpha_nmssm_SD.pdf")
c.SaveAs("epsilon_over_alpha_nmssm_SD.C")


##########################################
##########################################

