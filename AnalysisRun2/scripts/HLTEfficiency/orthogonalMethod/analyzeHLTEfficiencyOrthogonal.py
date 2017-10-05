# Run quiet mode
import sys
sys.argv.append( '-b' )
import ROOT
ROOT.gROOT.SetBatch(1)
ROOT.gErrorIgnoreLevel=1001
from ROOT import *
import random
import numpy
import os

def deltaPhi(phi1, phi2):
  result = phi1 - phi2;
  while (result > M_PI):
    result -= 2*M_PI;
  while (result <= -M_PI):
    result += 2*M_PI;
  return result;

def addfiles(ch, dirname=".", ext=".root"):
  theInputFiles = []
  if not os.path.isdir(dirname):
    print "ERROR: This is not a valid directory: ", dirname
    exit()
  ls = os.listdir(dirname)
  theInputFiles.extend([dirname[:] + x for x in ls if x.endswith(ext)])
  for pfile in theInputFiles:
    print pfile
    ch.Add(pfile)

  return ch

#______________________________________________________________________________
def draw_1D(p, to_draw, c_title, title, h_bins, cut="", opt = ""):
   gStyle.SetStatStyle(0)
   gStyle.SetOptStat(11111111)

   c = TCanvas("c","c",800,600)
   c.Clear()
   gStyle.SetTitleBorderSize(0);
   gStyle.SetPadLeftMargin(0.126);
   gStyle.SetPadRightMargin(0.04);
   gStyle.SetPadTopMargin(0.06);
   gStyle.SetPadBottomMargin(0.13);
   p.Draw(to_draw + ">>" + "h_name" + h_bins, cut)
   h = TH1F(gDirectory.Get("h_name").Clone("h_name"))
   if not h:
      sys.exit('h does not exist')
   h.SetTitle(title)
   h.SetLineWidth(2)
   h.SetLineColor(kBlue)
   h.GetXaxis().SetLabelSize(0.05)
   h.GetYaxis().SetLabelSize(0.05)
   h.GetXaxis().SetTitleSize(0.06)
   h.GetYaxis().SetTitleSize(0.06)
   header = "                                                         PU = 140, 14 TeV"
#   h.SetTitle(header)
   h.Draw()
   h.SetMinimum(0.)
   h.SetMaximum(h.GetMaximum()*1.2)
   c.SaveAs("" + c_title + ".png")

#______________________________________________________________________________
if __name__ == "__main__":

  ## extension for figures - add more?
  ext = ".png"

  ## Style
  gStyle.SetStatStyle(0)

  print "Making the plots"

  verbose = False

  newFile = TFile.Open("out_ana_selected_170213_161713.root"); 
  treeHits = newFile.Get("Events");

  n3Mu = 0
  n3MuSelect = 0
 
  n3MuPt5 = 0
  n3MuPt5MuPt15 = 0

  n4MuPt8 = 0
  n4MuPt8MuPt17 = 0

  nTripleMu = 0
  nMETTrigger2016 = 0
  nEvent_METTrigger2016 = 0
  
  denominator5 = 0.
  numerator5 = 0.

  denominator8 = 0.
  numerator8 = 0.

  goodTriggers = [
    'HLT_MET100_v',
    'HLT_MET150_v',
    'HLT_MET200_v',
    'HLT_MET250_v',
    'HLT_MET300_v',
    'HLT_MET600_v',
    'HLT_MET700_v',
    'HLT_PFMET110_PFMHT110_IDTight_v',
    'HLT_PFMET120_PFMHT120_IDTight_v',
    'HLT_PFMET170_BeamHaloCleaned_v',
    'HLT_PFMET170_HBHECleaned_v',
    'HLT_PFMET170_HBHE_BeamHaloCleaned_v',
    'HLT_PFMET170_JetIdCleaned_v',
    'HLT_PFMET170_NoiseCleaned_v',
    'HLT_PFMET170_NotCleaned_v',
    'HLT_PFMET300_v',
    'HLT_PFMET400_v',
    'HLT_PFMET500_v',
    'HLT_PFMET600_v',
    'HLT_PFMETTypeOne190_HBHE_BeamHaloCleaned_v'
    ]

  draw_1D(treeHits, "diMuonC_FittedVtx_m", "diMuonMass01", ";Invariant mass (#mu_{0}, #mu_{1});Events", "(150,0,150)", cut="", opt = "")
  draw_1D(treeHits, "diMuonF_FittedVtx_m", "diMuonMass02", ";Invariant mass (#mu_{0}, #mu_{1});Events", "(150,0,150)", cut="", opt = "")

  exit(1)

  ## ranges
  for k in range(0,100000): #treeHits.GetEntries()
      treeHits.GetEntry(k)
      
      if k%1000==0:
        print k
      #print treeHits.nRecoMu

      n3RecoMu = 0
      nMuPt5 = 0
      nMuPt15 = 0

      nMuPt8 = 0
      nMuPt17 = 0
      isTripleMuTriggered = False

      if treeHits.nRecoMu < 3 : n3RecoMu += 1#continue

      if treeHits.selMu0_pT >= 5: nMuPt5 += 1
      if treeHits.selMu1_pT >= 5: nMuPt5 += 1
      if treeHits.selMu2_pT >= 5: nMuPt5 += 1
      if treeHits.selMu3_pT >= 5: nMuPt5 += 1

      if treeHits.selMu0_pT >= 8: nMuPt8 += 1
      if treeHits.selMu1_pT >= 8: nMuPt8 += 1
      if treeHits.selMu2_pT >= 8: nMuPt8 += 1
      if treeHits.selMu3_pT >= 8: nMuPt8 += 1

      if treeHits.selMu0_pT >= 15: nMuPt15 += 1
      if treeHits.selMu1_pT >= 15: nMuPt15 += 1
      if treeHits.selMu2_pT >= 15: nMuPt15 += 1
      if treeHits.selMu3_pT >= 15: nMuPt15 += 1

      if treeHits.selMu0_pT >= 17 and abs(treeHits.selMu0_eta)<0.9: nMuPt17 += 1
      if treeHits.selMu1_pT >= 17 and abs(treeHits.selMu1_eta)<0.9: nMuPt17 += 1
      if treeHits.selMu2_pT >= 17 and abs(treeHits.selMu2_eta)<0.9: nMuPt17 += 1
      if treeHits.selMu3_pT >= 17 and abs(treeHits.selMu3_eta)<0.9: nMuPt17 += 1

      if nMuPt5 >= 3: n3MuPt5 += 1
      if nMuPt5 >= 3 and nMuPt15 >= 1: n3MuPt5MuPt15 += 1

      if nMuPt8 >= 3: n4MuPt8 += 1
      if nMuPt8 >= 3 and nMuPt17 >= 1: n4MuPt8MuPt17 += 1

      diMuonC_FittedVtx_m
      diMuonF_FittedVtx_m

      ## calculate the dimuon invariant masses
      if treeHits.nRecoMu >=3:
        v0 = TLorentzVector()
        v1 = TLorentzVector()
        v2 = TLorentzVector()
        v3 = TLorentzVector()
        v0.SetXYZM(treeHits.selMu0_px, treeHits.selMu0_py, treeHits.selMu0_pz, 0.1056583745)
        v1.SetXYZM(treeHits.selMu1_px, treeHits.selMu1_py, treeHits.selMu1_pz, 0.1056583745)
        v2.SetXYZM(treeHits.selMu2_px, treeHits.selMu2_py, treeHits.selMu2_pz, 0.1056583745)
        v3.SetXYZM(0, 0, 0, 0)

        v0_v1 = v0.Dot(v1)
        v0_v2 = v0.Dot(v2)
        v1_v2 = v1.Dot(v2)
        v0_v3 = v0.Dot(v3)
        v1_v3 = v1.Dot(v3)
        v2_v3 = v2.Dot(v3)
        

      if treeHits.nRecoMu >=4:
        v3 = TLorentzVector()
        v3.SetXYZM(treeHits.selMu3_px, treeHits.selMu3_py, treeHits.selMu3_pz, 0.1056583745)

        v0_v3 = v0.Dot(v3)
        v1_v3 = v1.Dot(v3)
        v2_v3 = v2.Dot(v3)
        
      verbose = False
      if verbose: 
        print treeHits.selMu0_px, treeHits.selMu0_py, treeHits.selMu0_pz
        print treeHits.selMu1_px, treeHits.selMu1_py, treeHits.selMu1_pz
        print treeHits.selMu2_px, treeHits.selMu2_py, treeHits.selMu2_pz
        print treeHits.selMu3_px, treeHits.selMu3_py, treeHits.selMu3_pz
        print
        print "invariant masses"
        print v0_v1, v0_v2, v0_v3, v1_v2, v1_v3, v2_v3
        print 

      def checkZMassConsistency(invM):
        return invM < 110 and invM > 70

      def atLeastOneGoodDiMuonZ(v0_v1, v0_v2, v0_v3, v1_v2, v1_v3, v2_v3):
        return (checkZMassConsistency(v0_v1) or 
                checkZMassConsistency(v0_v2) or
                checkZMassConsistency(v0_v3) or
                checkZMassConsistency(v1_v2) or
                checkZMassConsistency(v1_v3) or
                checkZMassConsistency(v2_v3))

      def checkJPsiMassConsistency(invM):
        return invM < 3.2 and invM > 2.8

      def atLeastOneGoodDiMuonJPsi(v0_v1, v0_v2, v0_v3, v1_v2, v1_v3, v2_v3):
        return (checkJPsiMassConsistency(v0_v1) or 
                checkJPsiMassConsistency(v0_v2) or
                checkJPsiMassConsistency(v0_v3) or
                checkJPsiMassConsistency(v1_v2) or
                checkJPsiMassConsistency(v1_v3) or
                checkJPsiMassConsistency(v2_v3))

      goodDiMuonZ_01 = checkZMassConsistency(v0_v1)
      goodDiMuonZ_02 = checkZMassConsistency(v0_v2)
      goodDiMuonZ_03 = checkZMassConsistency(v0_v3)
      goodDiMuonZ_12 = checkZMassConsistency(v1_v2)
      goodDiMuonZ_13 = checkZMassConsistency(v1_v2)
      goodDiMuonZ_23 = checkZMassConsistency(v2_v3)

      minPt = 40
      atLeastOneGoodDiMuonZ_v2 = (
        ( checkZMassConsistency(v0_v1) and (treeHits.selMu2_pT > minPt or treeHits.selMu3_pT > minPt) ) or
        ( checkZMassConsistency(v0_v2) and (treeHits.selMu1_pT > minPt or treeHits.selMu3_pT > minPt) ) or
        ( checkZMassConsistency(v0_v3) and (treeHits.selMu1_pT > minPt or treeHits.selMu2_pT > minPt) ) or
        ( checkZMassConsistency(v1_v2) and (treeHits.selMu0_pT > minPt or treeHits.selMu3_pT > minPt) ) or
        ( checkZMassConsistency(v1_v3) and (treeHits.selMu0_pT > minPt or treeHits.selMu2_pT > minPt) ) or
        ( checkZMassConsistency(v2_v3) and (treeHits.selMu0_pT > minPt or treeHits.selMu1_pT > minPt) )
      )

      passZSelection = atLeastOneGoodDiMuonZ(v0_v1, v0_v2, v0_v3, v1_v2, v1_v3, v2_v3)
      passJPsiSelection = atLeastOneGoodDiMuonJPsi(v0_v1, v0_v2, v0_v3, v1_v2, v1_v3, v2_v3)

      #extraSelection = treeHits.selMu0_pT > 20 and treeHits.selMu1_pT > 20 and (treeHits.selMu2_pT > 20 or treeHits.selMu3_pT > 20)
      #passZSelection = passZSelection and extraSelection
      #passZSelection_v2 = atLeastOneGoodDiMuonZ_v2

      passZSelection_v2 = (checkZMassConsistency(treeHits.diMuonF_FittedVtx_m) or checkZMassConsistency(treeHits.diMuonC_FittedVtx_m)) and treeHits.orphan_PtOrph > 8

      
      if verbose: print "Passes Z mass", passZSelection
      if verbose: print
      
      if treeHits.nRecoMu >= 3:
        n3Mu += 1

      for pp in goodTriggers:
        #if verbose: print pp,
        for p in treeHits.hltPaths:
          #print pp, p
          if pp in p:
            nMETTrigger2016 += 1
            #print "pass MET selection"
          if "HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx" in p:
            isTripleMuTriggered = True
            #if verbose: print "\t pass signal trigger"

      if verbose: print
 
      if nMETTrigger2016 >= 1:
        nEvent_METTrigger2016 += 1

        if nMuPt8 >= 3 and nMuPt17 >= 1:# and passZSelection_v2: 
          denominator5 +=1 
          print treeHits.diMuonF_FittedVtx_m, treeHits.diMuonC_FittedVtx_m
          #print treeHits.selMu0_pT, treeHits.selMu0_eta, treeHits.selMu0_phi
          #print treeHits.selMu1_pT, treeHits.selMu1_eta, treeHits.selMu1_phi
          #print treeHits.selMu2_pT, treeHits.selMu2_eta, treeHits.selMu2_phi
          #print treeHits.selMu3_pT, treeHits.selMu3_eta, treeHits.selMu3_phi
          #print treeHits.selMu0_pT, treeHits.selMu1_pT, treeHits.selMu2_pT, treeHits.selMu3_pT
          #print
          #for p in treeHits.hltPaths:
          #  print p
          if isTripleMuTriggered: 
            numerator5 +=1
            #print "\tPasses signal trigger" 
            
        if nMuPt8 >= 4 and nMuPt17 >= 1: 
          denominator8 +=1 
          if isTripleMuTriggered: numerator8 +=1

  print "n3RecoMu", n3RecoMu
  print "n3Mu", n3Mu
  print "n3MuPt5", n3MuPt5
  print "n3MuPt5MuPt15", n3MuPt5MuPt15
  #print "n4MuPt8", n4MuPt8
  #print "n4MuPt8MuPt17", n4MuPt8MuPt17
  print "nTripleMu", nTripleMu 
  print "nMETTrigger2016", nMETTrigger2016
  print "nEvent_METTrigger2016", nEvent_METTrigger2016

  print numerator5, denominator5
  print "efficiency", numerator5 / denominator5
  #print numerator8, denominator8

  #  print numerator8, denominator8
  # print "efficiency", numerator8 / denominator8
