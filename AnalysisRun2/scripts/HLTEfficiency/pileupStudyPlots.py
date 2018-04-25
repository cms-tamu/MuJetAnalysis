import sys
from ROOT import *
from argparse import ArgumentParser
import numpy as np
from array import array
from hepPlotter import HepPlotter
from hepPlotterDataMC import HepPlotterDataMC
import hepPlotterTools as hpt
#import hepPlotterLabels as hpl
import math as m
import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from Helpers import *

numberOfVertices = [
1,
2,
3,
4,
5,
6,
7,
8,
9,
10,
11,
12,
13,
14,
15,
16,
17,
18,
19,
20,
21,
22,
23,
24,
25,
26,
27,
28,
29,
30,
31,
32,
33,
34,
35,
36,
37,
38,
39,
40,
41,
42,
43,
44,
45,
46,
47,
48,
49,
50,
51,
52,
53,
54,
55,
56,
57,
58,
59,
60,
61,
62,
63,
64,
65,
66,
67,
68,
69,
70,
71,
72,
73,
74,
75,
76,
77,
78,
79,
80,
81,
82,
83,
84,
85,
86,
87,
88,
89,
90,
91,
92,
93,
94,
95,
96,
97,
98,
99,
100,
]

nominal = [
238797,
837543,
2.31E+06,
3.12E+06,
4.48E+06,
6E+06,
7E+06,
1.29E+07,
3.53E+07,
7.87E+07,
1.77E+08,
3.6E+08,
6.03E+08,
8.77E+08,
1.17E+09,
1.49E+09,
1.76E+09,
1.94E+09,
2.05E+09,
2.1E+09,
2.13E+09,
2.15E+09,
2.13E+09,
2.06E+09,
1.96E+09,
1.84E+09,
1.7E+09,
1.55E+09,
1.4E+09,
1.24E+09,
1.09E+09,
9.37E+08,
7.92E+08,
6.57E+08,
5.34E+08,
4.27E+08,
3.35E+08,
2.58E+08,
1.94E+08,
1.42E+08,
1.01E+08,
6.9E+07,
4.55E+07,
2.88E+07,
1.75E+07,
1.02E+07,
5.64E+06,
2.99E+06,
1.51E+06,
731845,
339822,
152545,
67404.8,
30489.7,
15152.1,
8975.91,
6496.15,
5434.81,
4889.96,
4521.72,
4208.46,
3909.76,
3614.27,
3320.72,
3031.1,
2748.24,
2474.98,
2213.82,
1966.82,
1735.55,
1521.11,
1324.15,
1144.9,
983.22,
838.668,
710.534,
597.91,
499.739,
414.866,
342.082,
280.162,
227.901,
184.137,
147.773,
117.789,
93.2547,
73.3322,
57.2764,
44.4338,
34.2379,
26.2034,
19.9188,
15.0392,
11.2782,
8.40063,
6.21495,
4.56686,
3.33312,
2.41623,
1.73972,
]

up = [
232231,
646482,
2.17E+06,
2.72E+06,
4.04E+06,
5.35E+06,
6.34E+06,
8.82E+06,
2.3E+07,
5.23E+07,
1.12E+08,
2.38E+08,
4.31E+08,
6.65E+08,
9.2E+08,
1.2E+09,
1.48E+09,
1.71E+09,
1.87E+09,
1.96E+09,
2E+09,
2.03E+09,
2.05E+09,
2.03E+09,
1.98E+09,
1.89E+09,
1.79E+09,
1.67E+09,
1.53E+09,
1.39E+09,
1.25E+09,
1.11E+09,
9.71E+08,
8.36E+08,
7.07E+08,
5.88E+08,
4.81E+08,
3.87E+08,
3.06E+08,
2.38E+08,
1.81E+08,
1.34E+08,
9.67E+07,
6.76E+07,
4.56E+07,
2.97E+07,
1.86E+07,
1.12E+07,
6.47E+06,
3.58E+06,
1.9E+06,
971228,
476252,
225514,
104152,
47956.9,
23001.1,
12312.6,
7840.12,
5954.11,
5096.35,
4628.04,
4298.76,
4014.88,
3743.74,
3475.58,
3208.98,
2945.4,
2687.11,
2436.5,
2195.72,
1966.59,
1750.55,
1548.67,
1361.67,
1189.9,
1033.42,
892.01,
765.231,
652.447,
552.875,
465.629,
389.747,
324.233,
268.078,
220.291,
179.914,
146.037,
117.812,
94.4604,
75.2731,
59.6157,
46.9257,
36.7106,
28.5432,
22.0568,
16.9399,
12.9303,
9.80926,
7.3959,
]

down = [
248319,
1.09E+06,
2.44E+06,
3.61E+06,
5.04E+06,
6.65E+06,
8.24E+06,
2.08E+07,
5.37E+07,
1.24E+08,
2.83E+08,
5.29E+08,
8.22E+08,
1.14E+09,
1.49E+09,
1.81E+09,
2.03E+09,
2.15E+09,
2.21E+09,
2.25E+09,
2.26E+09,
2.23E+09,
2.15E+09,
2.04E+09,
1.9E+09,
1.74E+09,
1.57E+09,
1.4E+09,
1.23E+09,
1.06E+09,
8.93E+08,
7.39E+08,
5.98E+08,
4.75E+08,
3.69E+08,
2.81E+08,
2.09E+08,
1.51E+08,
1.05E+08,
7.04E+07,
4.53E+07,
2.78E+07,
1.63E+07,
9.07E+06,
4.81E+06,
2.42E+06,
1.16E+06,
528799,
231182,
98240.3,
41962.1,
19292.2,
10517.5,
7169.83,
5827.13,
5183.99,
4769.09,
4421.64,
4090.93,
3763.71,
3438.96,
3119.38,
2808.5,
2509.7,
2225.89,
1959.37,
1711.84,
1484.38,
1277.49,
1091.21,
925.119,
778.435,
650.109,
538.875,
443.333,
362.002,
293.381,
235.99,
188.405,
149.291,
117.412,
91.6503,
71.0056,
54.5998,
41.6704,
31.5648,
23.731,
17.7079,
13.1146,
9.64009,
7.03304,
5.09262,
3.65995,
2.61062,
1.8482,
1.29864,
0.90565,
0.626855,
0.430633,
0.293617,
]

n_vert = numberOfVertices
n_eventsnom = nominal
n_eventsup = up
n_eventsdown = down

print len(numberOfVertices), len(nominal), len(up), len(down)


c1 = TCanvas( 'c1', '', 700, 500 )

gStyle.SetOptTitle(0)

c1.SetBorderSize(2);
c1.SetLeftMargin(0.14);
c1.SetRightMargin(0.06);
c1.SetTopMargin(0.06);


#c1.SetFillColor( 0 )

gr = TGraph( 100, np.asarray(n_vert,'d'), np.asarray(n_eventsnom,'d') )
gr.SetLineColor( kBlack )
gr.SetLineStyle(1)
gr.SetLineWidth( 2 )
gr.SetTitle( '' )

gr.GetXaxis().SetTitle( 'Number of vertices' )
gr.GetXaxis().SetLabelSize(0.05)
gr.GetXaxis().SetTitleSize(0.05)
#gr.GetXaxis().SetTitleOffset(0.05)
gr.SetTitle("Nominal")
gr.GetYaxis().SetTitle( 'Number of events' )
gr.GetYaxis().SetTitleSize(0.05)
gr.GetYaxis().SetLabelSize(0.05)
gr.GetYaxis().SetTitleOffset(1.3)

gr.GetXaxis().SetLimits(0.,75)
gr.Draw( 'AL' )

grup = TGraph( 100, np.asarray(n_vert,'d'), np.asarray(n_eventsup,'d') )
grup.SetTitle("5% Up")
grup.SetLineStyle(6)
grup.SetLineColor( kRed )
grup.SetLineWidth( 2 )
grup.Draw( 'Lsame' )

grdown = TGraph( 100, np.asarray(n_vert,'d'), np.asarray(n_eventsdown,'d') )
grdown.SetTitle("5% Down")
grdown.SetLineColor( 4 )
grdown.SetLineStyle(10)
grdown.SetLineWidth( 2 )
grdown.Draw( 'Lsame' )

gr.SetFillColor(kWhite);
grup.SetFillColor(kWhite);
grdown.SetFillColor(kWhite);

gr.SetFillStyle(0);
grup.SetFillStyle(0);
grdown.SetFillStyle(0);
gr.SetFillColor(0);
grup.SetFillColor(0);
grdown.SetFillColor(0);

c1.BuildLegend();
c1.Update()
legend = TLegend(0.7,0.9,0.7,0.9);
legend.SetBorderSize(0)
legend.AddEntry(gr,"Nominal","lp");
legend.AddEntry(grup,"5% Up","lp");
legend.AddEntry(grdown,"5% Down","lp");
#legend.Draw();
c1.Update()
#c1.GetFrame().SetFillColor( 21 )
#c1.GetFrame().SetBorderSize( 12 )
#c1.Modified()
#c1.Update()
c1.SaveAs("pileupPlotNominalUpDown.pdf")


#h_nom = ROOT.TH1D("h","",len(n_eventsnom)-1,np.asarray(n_eventsnom,'d'))
#h_up = ROOT.TH1D("h","",len(n_eventsup)-1,np.asarray(n_eventsup,'d'))
#h_down = ROOT.TH1D("h","",len(n_eventsdown)-1,np.asarray(n_eventsdown,'d'))
exit(1)

hist = HepPlotter("histogram",1)#
hist.x_relative_size = 10
hist.y_relative_size = 7
hist.drawEffDist = False    # draw the physics distribution for efficiency (jet_pt for jet trigger)
hist.x_label     = "Number of vertices"# "Dimuon invariant mass"
hist.y_label     = "Number of events"
hist.format      = "pdf"      # file format for saving image
hist.saveDir     = './'
hist.saveAs      = "pileupPlotNominalUpDownMPL"# "Z_peak_2016MonteCarlo_WZ" # save figure with name
hist.CMSlabel       = 'outer'  # 'top left', 'top right'; hack code for something else
hist.CMSlabelStatus = 'Preliminary'  # ('Simulation')+'Internal' || 'Preliminary' 
hist.initialize()
hist.lumi = '2016 B-H, 35.9'
hist.plotLUMI = True
hist.drawStatUncertainty = True    
hist.Add([n_vert, n_eventsnom], draw='errorbar', color='black', linecolor='black', label=r'Nominal')
#hist.Add([n_vert, n_eventsup], draw='step', color='blue', linecolor='blue', label=r'5\% up')
#hist.Add([n_vert, n_eventsdown], draw='step', color='orange', linecolor='orange', label=r'5\% down')
plot = hist.execute()
#plot.tight_layout()
hist.savefig()
