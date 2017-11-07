## user packages
import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from Helpers import *
from ROOT import *

## open the file with locations to MC files
mcSamples = readTextFileWithSamples("../DarkSUSY_All_2016.txt")

## print the properties of each sample
print "Printing properties"
for sample in mcSamples:
    print decodeDarkSUSYFileNameMany(sample)


mass_strings = {
    "0p25": "0.25", 
    "0p275" : "0.275", "0p3": "0.3", "0p4" : "0.4", "0700" : "0.7", 
    "1" : "1.0", "1500" : "1.5", "2000" : "2.0", "8500" : "8.5"
}
cT_strings = {
  "0" : 0.0, "0p05" :  0.05, "0p1" :  0.10, "0p2" :  0.20, "0p5" :  0.50, "1" :  1.00, 
  "200" :  2.00, "300" :  3.00, "500" :  5.00, "1000" :  10.0, "2000" :  20.0, "8500" :  85.0
}

cT_strings2 = {
  "0" : "0", "0p05" : "0.05", "0p1" : "0.1", "0p2" : "0.2", "0p5" : "0.50", "1" : "1", 
  "2" : "2", "3" : "3", "5" : "5", "10" : "10", "20" : "20", "50" : "50", "100" : "100"
}


## prepare dictionaries of histograms
A0Lxy_histos = {}
A0Lxy_histos["0p25"] = {}
A0Lxy_histos["0p3"] = {}
A0Lxy_histos["0p4"] = {}
A0Lxy_histos["0p7"] = {}
A0Lxy_histos["1"] = {}
A0Lxy_histos["1p5"] = {}
A0Lxy_histos["2"] = {}
A0Lxy_histos["5"] = {}
A0Lxy_histos["8p5"] = {}

A1Lxy_histos = {}
A1Lxy_histos["0p25"] = {}
A1Lxy_histos["0p3"] = {}
A1Lxy_histos["0p4"] = {}
A1Lxy_histos["0p7"] = {}
A1Lxy_histos["1"] = {}
A1Lxy_histos["1p5"] = {}
A1Lxy_histos["2"] = {}
A1Lxy_histos["5"] = {}
A1Lxy_histos["8p5"] = {}


## pick a certain dark boson mass ma value
def getA0A1LxyValuesMaMass(neutralino_string, mass_string):

    cT_samples =  getDarkSUSYFileMaMass(mcSamples, neutralino_string, mass_string)

    for cT_sample in cT_samples:

        ## define a new tree
        chain = TChain("cutFlowAnalyzerPXBL3PXFL2/Events")

        ## check the n1 mass, ma mass and cT displacement
        n1, ma, ctau = decodeDarkSUSYFileNameMany(cT_sample)

        ## place a cut-off if need be!!
        ## if ctau == '1':
        ##    break

        ## check the number of events!
        print "Processing", n1, ma, ctau, 
        chain = addfilesMany(chain, cT_sample)    
        print "Events", chain.GetEntries()

        lxy_hist = TH1F("lxy_hist", "A0Lxy distribution; A0 Lxy [cm]; Events", 150, 0.1, 300);
        chain.Draw("genA0_Lxy>>lxy_hist");
        A0Lxy_histos[ma][ctau] = lxy_hist
        
        lxy_hist = TH1F("lxy_hist", "A1Lxy distribution; A1 Lxy [cm]; Events", 150, 0.1, 300);
        chain.Draw("genA1_Lxy>>lxy_hist");
        A1Lxy_histos[ma][ctau] = lxy_hist


## process all samples
def getA0A1LxyValues():
    for mass in A0Lxy_histos:
        print mass
        getA0A1LxyValuesMaMass('10', mass)


## plot the dark boson lxy values
def makePlotDarkBosonLxyMaMassAllCtau(darkBoson, mass_string):

    if   darkBoson == 'A0':
        DarkBosonLxy_histos = A0Lxy_histos
    elif darkBoson == 'A1':
        DarkBosonLxy_histos = A1Lxy_histos
    else:
        print "Not a valid dark boson choice"
        return
    

    cT_colors = [1,2,3,4,5,kOrange,7,8,9]

    c1 = TCanvas("c1","test",800,600);
    c1.cd()
    
    gPad.SetTickx(1)
    gPad.SetTicky(1)
    gPad.SetLogx(1)
    gPad.SetLogy(1)

    c1.SetGridx()
    c1.SetGridy()

    gStyle.SetStatStyle(0)
    gStyle.SetOptStat(0)

    gStyle.SetTitleStyle( 0 )
    gStyle.SetTitleAlign(13) ##// coord in top left
    gStyle.SetTitleX(0.)
    gStyle.SetTitleY(1.)
    gStyle.SetTitleW(1)
    gStyle.SetTitleH(0.058)
    gStyle.SetTitleBorderSize( 0 )
    
    gStyle.SetPadLeftMargin(0.126);
    gStyle.SetPadRightMargin(0.04);
    gStyle.SetPadTopMargin(0.06);
    gStyle.SetPadBottomMargin(0.13);
    
    b1 = TH1F("b1","b1", 150,0,300)
    b1.GetYaxis().SetTitleOffset(1.2)
    b1.SetMinimum(0.0)
    #b1.GetYaxis().SetNdivisions(520)
    b1.GetXaxis().SetTitle(darkBoson + " Lxy [cm]")
    b1.GetYaxis().SetTitle("Events")
    b1.GetXaxis().SetTitleOffset(1.2)
    b1.GetYaxis().SetTitleOffset(1.2)
    b1.GetXaxis().SetTitleSize(0.05)
    b1.GetYaxis().SetTitleSize(0.05)
    b1.GetXaxis().SetLabelSize(0.05)
    b1.GetYaxis().SetLabelSize(0.05)
    b1.SetTitle("           #scale[1.4]{#font[61]{CMS}} #font[52]{Simulation preliminary}                                                          13 TeV")
    b1.Draw();
    
    newmax = 0
    for cT,cT_color in zip(DarkBosonLxy_histos[mass_string], cT_colors):

        ## define the histogram
        histo = DarkBosonLxy_histos[mass_string][cT]
        histo.SetLineWidth(2)
        histo.SetLineColor(cT_color)
        
        ## draw the histogram
        histo.Draw("same");

        ## adjust the maximum
        newmax = max(newmax, histo.GetMaximum())
        b1.SetMaximum(newmax)
    
    canvasName = getDarkSUSYFileNameNoCT(n1, ma)
    c1.SaveAs("DarkBosonLxyPlots/" + canvasName + "_" + darkBoson + "_Lxy" + ".png")
    c1.SaveAs("DarkBosonLxyPlots/" + canvasName + "_" + darkBoson + "_Lxy" + ".C")

    ## clear the canvas
    c1.Clear()



getA0A1LxyValues()

makePlotDarkBosonLxyMaMassAllCtau('A0')
makePlotDarkBosonLxyMaMassAllCtau('A1')
