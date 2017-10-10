## user packages
import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from Helpers import *
from ROOT import *

## open the file with locations to MC files
mcSamples = readTextFileWithSamples("../DarkSUSY_All_2016.txt")


A0Lxy_histos = {}
A0Lxy_histos["0p25"] = {}

A1Lxy_histos = {}
A1Lxy_histos["0p25"] = {}

for sample in mcSamples:
    chain = TChain("cutFlowAnalyzerPXBL3PXFL2/Events")

    n1, ma, ctau = decodeDarkSUSYFileNameMany(sample)
    print "Checking", "mN1", n1, "mA", ma, "cT", ctau

    ## only process the low mass samples now
    if ma != '0p25':
        continue
    
    if ctau == '1':
        break
    
    chain = addfilesMany(chain, sample)    
    print "Processing", n1, ma, ctau, chain.GetEntries()

    lxy_hist = TH1F("lxy_hist", "A0Lxy distribution; A0 Lxy [cm]; Events", 150, 0, 300);
    chain.Draw("genA0_Lxy>>lxy_hist");
    A0Lxy_histos[ma][ctau] = lxy_hist

    lxy_hist = TH1F("lxy_hist", "A1Lxy distribution; A1 Lxy [cm]; Events", 150, 0, 300);
    chain.Draw("genA1_Lxy>>lxy_hist");
    A1Lxy_histos[ma][ctau] = lxy_hist


    """
    break

    for event in range(0,chain.GetEntries()):
        chain.GetEntry(event)
        print "Processing event", event
        print chain.genA0_Lxy

    break
    """
   
cT_colors = [1,2,3,4,5,kOrange,7,8,9]

c1 = TCanvas("c1","test",800,600);
c1.cd()

gPad.SetTickx(1)
gPad.SetTicky(1)
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

gStyle.SetPadLeftMargin(3*0.126);
gStyle.SetPadRightMargin(0.04);
gStyle.SetPadTopMargin(0.06);
gStyle.SetPadBottomMargin(3*0.13);

b1 = TH1F("b1","b1", 150,0,300)
b1.GetYaxis().SetTitleOffset(1.2)
b1.SetMinimum(0.0)
#b1.GetYaxis().SetNdivisions(520)
b1.GetXaxis().SetTitle("A0 Lxy [cm]")
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
for cT,cT_color in zip(A0Lxy_histos["0p25"], cT_colors):

    ## define the histogram
    histo = A0Lxy_histos["0p25"][cT]
    histo.SetLineWidth(2)
    histo.SetLineColor(cT_color)

    ## draw the histogram
    histo.Draw("same");

    ## adjust the maximum
    newmax = max(newmax, histo.GetMaximum())
    b1.SetMaximum(newmax)
    
canvasName = getDarkSUSYFileNameNoCT(n1, ma)
c1.SaveAs("DarkBosonLxyPlots/" + canvasName + "_A0_Lxy" + ".png")
c1.SaveAs("DarkBosonLxyPlots/" + canvasName + "_A0_Lxy" + ".C")
c1.SaveAs("DarkBosonLxyPlots/" + canvasName + "_A0_Lxy" + ".py")






   
c1 = TCanvas("c1","test",800,600);
c1.cd()

gPad.SetTickx(1)
gPad.SetTicky(1)
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

gStyle.SetPadLeftMargin(3*0.126);
gStyle.SetPadRightMargin(0.04);
gStyle.SetPadTopMargin(0.06);
gStyle.SetPadBottomMargin(3*0.13);

b1 = TH1F("b1","b1", 150,0,300)
b1.GetYaxis().SetTitleOffset(1.2)
b1.SetMinimum(0.0)
#b1.GetYaxis().SetNdivisions(520)
b1.GetXaxis().SetTitle("A1 Lxy [cm]")
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
for cT,cT_color in zip(A1Lxy_histos["0p25"], cT_colors):

    ## define the histogram
    histo = A1Lxy_histos["0p25"][cT]
    histo.SetLineWidth(2)
    histo.SetLineColor(cT_color)

    ## draw the histogram
    histo.Draw("same");

    ## adjust the maximum
    newmax = max(newmax, histo.GetMaximum())
    b1.SetMaximum(newmax)
    
canvasName = getDarkSUSYFileNameNoCT(n1, ma)
c1.SaveAs("DarkBosonLxyPlots/" + canvasName + "_A1_Lxy" + ".png")
c1.SaveAs("DarkBosonLxyPlots/" + canvasName + "_A1_Lxy" + ".C")
c1.SaveAs("DarkBosonLxyPlots/" + canvasName + "_A1_Lxy" + ".py")







































exit(1)

for k in range(0,tree.GetEntries()):
    tree.GetEntry(k)

    print 
    print "Processing event", k

    ## ignore all irrelevant cases
    if not (tree.is4GenMu8 and
            abs(tree.genA0_Lxy) < 9.8 and
            abs(tree.genA1_Lxy) < 9.8 and
            abs(tree.genA0_Lz) < 46.5 and
            abs(tree.genA1_Lz) < 46.5
            and tree.is4SelMu8
            and tree.isVertexOK
            and tree.is2MuJets
            and tree.is2DiMuons
            and tree.is2DiMuonsFittedVtxOK
            ): continue
    
    print "Generator level"
    print "Vertex location"
    print tree.genA0Mu0_vx, tree.genA0Mu0_vy
    print tree.genA0Mu1_vx, tree.genA0Mu1_vy
    print tree.genA1Mu0_vx, tree.genA1Mu0_vy
    print tree.genA1Mu1_vx, tree.genA1Mu1_vy

    print "Lxy"
    print tree.genA0_Lxy
    print tree.genA1_Lxy
    
    print "RECO level"
    print tree.diMuonF_FittedVtx_vx, tree.diMuonF_FittedVtx_vy, tree.diMuonF_FittedVtx_vz
    print tree.diMuonF_FittedVtx_px, tree.diMuonF_FittedVtx_py
    print tree.diMuonF_FittedVtx_vx * tree.diMuonF_FittedVtx_px + tree.diMuonF_FittedVtx_vy * tree.diMuonF_FittedVtx_py

    print tree.diMuonC_FittedVtx_vx, tree.diMuonC_FittedVtx_vy, tree.diMuonC_FittedVtx_vz
    print tree.diMuonC_FittedVtx_px, tree.diMuonC_FittedVtx_py
    print tree.diMuonC_FittedVtx_vx * tree.diMuonC_FittedVtx_px + tree.diMuonC_FittedVtx_vy * tree.diMuonC_FittedVtx_py

    print "Lxy"
    print tree.diMuonF_FittedVtx_Lxy
    print tree.diMuonC_FittedVtx_Lxy

    print
    print "Check if the displaced vertex is outside the fiducial region"
    if tree.diMuonF_FittedVtx_Lxy > 9.8:
      print "diMuonF_vtx outside pixel"
    if tree.diMuonC_FittedVtx_Lxy > 9.8:
      print "diMuonC_vtx outside pixel"

    ## match the correct GEN level muon to RECO level muon
    deltaR_GenA0_diMuonF = deltaR(tree.genA0_eta, tree.genA0_phi, tree.diMuonF_FittedVtx_eta, tree.diMuonF_FittedVtx_phi)
    deltaR_GenA1_diMuonF = deltaR(tree.genA1_eta, tree.genA1_phi, tree.diMuonF_FittedVtx_eta, tree.diMuonF_FittedVtx_phi)
    deltaR_GenA0_diMuonC = deltaR(tree.genA0_eta, tree.genA0_phi, tree.diMuonC_FittedVtx_eta, tree.diMuonC_FittedVtx_phi)
    deltaR_GenA1_diMuonC = deltaR(tree.genA1_eta, tree.genA1_phi, tree.diMuonC_FittedVtx_eta, tree.diMuonC_FittedVtx_phi)

    print 
    print "DeltaR(GEN,RECO)"
    print "F", deltaR_GenA0_diMuonF, deltaR_GenA1_diMuonF
    print "C", deltaR_GenA0_diMuonC, deltaR_GenA1_diMuonC

    ## associated the reco dimuon to the gen dimuon
    is_dR_A0_diMuonF_smaller = deltaR_GenA0_diMuonF < deltaR_GenA1_diMuonF
    genRecoCase = -1
    
    if is_dR_A0_diMuonF_smaller: genRecoCase = 1
    else:                        genRecoCase = 2

    
    
