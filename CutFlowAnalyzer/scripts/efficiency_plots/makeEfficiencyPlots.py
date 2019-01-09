from ROOT import *

file = TFile.Open("new_DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_all.root")
tree = file.Get("Events")
tree2 = file.Get("RecoIndex")
tree.AddFriend(tree2)

def makePlot(tree, denominator, cut, extracut, xbin, minbin, maxbin,
title):
    denom  = TH1F("denom","",xbin, minbin, maxbin)
    num  = TH1F("num","",xbin, minbin, maxbin)
    tree.Draw(denominator + ">>denom", cut,"goff")
    tree.Draw(denominator + ">>num", TCut("%s && %s"%(cut,extracut)),"goff")
    myeff = TEfficiency(num, denom)

    gROOT.SetBatch(True);
    gStyle.SetOptStat(0);


    c = TCanvas("c", "c", 600, 600)
    c.cd()
    base = TH1F("base","",xbin,minbin,maxbin)
    base.GetXaxis().SetTitle("Dark photon L_{xy}")
    base.GetYaxis().SetTitle("Efficiency")

    c.SetBorderMode(0);
    c.SetBorderSize(2);
    c.SetTickx(1);
    c.SetTicky(1);
    c.SetLeftMargin(0.15);
    c.SetRightMargin(0.05);
    c.SetTopMargin(0.07);
    c.SetBottomMargin(0.15);
    c.SetFrameFillStyle(0);
    c.SetFrameBorderMode(0);
    c.SetFrameFillStyle(0);
    c.SetFrameBorderMode(0);
    
    gStyle.SetTitleFontSize(0.07);
    
    gStyle.SetTitleStyle( 0 );
    gStyle.SetTitleAlign(13);
    gStyle.SetTitleX(0.);
    gStyle.SetTitleY(1.);
    gStyle.SetTitleW(1);
    gStyle.SetTitleH(0.058);
    gStyle.SetTitleBorderSize( 0 );

    myeff.SetMarkerColor(1);
    myeff.SetMarkerStyle(20);
   
    base.GetXaxis().SetLabelFont(42);
    base.GetXaxis().SetLabelOffset(0.007);
    base.GetXaxis().SetLabelSize(0.05);
    base.GetXaxis().SetTitleSize(0.06);
    base.GetXaxis().SetTitleFont(42);
    base.GetXaxis().SetTitleOffset(1.1);
    
    base.GetYaxis().SetLabelFont(42);
    base.GetYaxis().SetLabelOffset(0.007);
    base.GetYaxis().SetLabelSize(0.05);
    base.GetYaxis().SetTitleSize(0.06);
    base.GetYaxis().SetTitleOffset(1.1);
    base.GetYaxis().SetTitleFont(42);
    
    base.Draw()
    myeff.Draw("P same")

    c.SaveAs(title + ".pdf")

makePlot(tree, 
         "genA0_Lxy", 
         "genA0_Lxy>0 && abs(genA0_eta)<2.4 && is4GenMu8 && abs(genA0Mu0_eta)<2.4 && (genA0Mu0_px>8 || genA0Mu0_py>8) && abs(genA0Mu1_eta)<2.4 && (genA0Mu1_px>8 || genA0Mu1_py>8) && isDiMuonHLTFired == 1", 
         "genA0_RecoIndex>=1", 100, 0, 100, "eff_genA0_lxy")

makePlot(tree, 
         "genA0_Lxy", 
         "genA0_Lxy>0 && abs(genA0_eta)<2.4 && is4GenMu8 && abs(genA0Mu0_eta)<2.4 && abs(genA0Mu1_eta)<2.4 && isDiMuonHLTFired == 1", 
         "genA0_RecoIndex>=1", 100, 0, 100, "eff_genA0_lz")

## single muon reconstruction efficiency vs lxy
## single muon efficiency vs lxy
