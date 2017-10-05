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
if __name__ == "__main__":

  ## extension for figures - add more?
  ext = ".png"

  ## Style
  gStyle.SetStatStyle(0)

  print "Making the plots"

  verbose = False


  ch = TChain("cutFlowAnalyzer_Data/Events")
  ch = addfiles(ch, dirname="/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016B-23Sep2016-v3/170201_153656/0000/")
  #ch.Add("out_ana.root")
  #ch.Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016B-23Sep2016-v3/170201_153656/0000/out_ana*.root")
  #  ch.Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016B-23Sep2016-v3/170201_153656/0001/out_ana*.root")
  #  ch.Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016B-23Sep2016-v3/170201_153656/0002/out_ana*.root")
  #  ch.Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016B-23Sep2016-v3/170201_153656/0003/out_ana*.root")
  #  ch.Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016B-23Sep2016-v3/170201_153656/0004/out_ana*.root")
  #  ch.Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016B-23Sep2016-v3/170201_153656/0005/out_ana*.root")
  """

  ch.Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016E-23Sep2016-v1/170201_154551/0000/out_ana*.root")
  ch.Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016E-23Sep2016-v1/170201_154551/0001/out_ana*.root")
  ch.Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016E-23Sep2016-v1/170201_154551/0002/out_ana*.root")

  ch.Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016G-23Sep2016-v1/170201_155152/0000/out_ana*.root")
  ch.Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016G-23Sep2016-v1/170201_155152/0001/out_ana*.root")
  ch.Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016G-23Sep2016-v1/170201_155152/0002/out_ana*.root")
  ch.Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016G-23Sep2016-v1/170201_155152/0003/out_ana*.root")
  ch.Add("/fdata/hepx/store/user/dildick/MET/crab_MET-Run2016G-23Sep2016-v1/170201_155152/0004/out_ana*.root")
  """
  treeHits = ch

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
  
  ## ranges
  for k in range(0,1000000):
      treeHits.GetEntry(k)
      
      if k%1000==0:
        print k
      #print treeHits.nRecoMu

      nMuPt5 = 0
      nMuPt15 = 0

      nMuPt8 = 0
      nMuPt17 = 0
      isTripleMuTriggered = False

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

      if treeHits.selMu0_pT >= 17: nMuPt17 += 1
      if treeHits.selMu1_pT >= 17: nMuPt17 += 1
      if treeHits.selMu2_pT >= 17: nMuPt17 += 1
      if treeHits.selMu3_pT >= 17: nMuPt17 += 1

      if nMuPt5 >= 3: n3MuPt5 += 1
      if nMuPt5 >= 3 and nMuPt15 >= 1: n3MuPt5MuPt15 += 1

      if nMuPt8 >= 3: n4MuPt8 += 1
      if nMuPt8 >= 3 and nMuPt17 >= 1: n4MuPt8MuPt17 += 1


      if treeHits.nRecoMu >= 3:
        n3Mu += 1
      for p in treeHits.hltPaths:
        for pp in goodTriggers:
          #print pp, p
          if pp in p:
            nMETTrigger2016 += 1
        if "HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx" in p:
          isTripleMuTriggered = True
           
      if nMETTrigger2016 >= 1:
        nEvent_METTrigger2016 += 1


        if nMuPt5 >= 3 and nMuPt15 >= 1: 
          denominator5 +=1 
          #print treeHits.selMu0_pT, treeHits.selMu1_pT, treeHits.selMu2_pT, treeHits.selMu3_pT
          #          for p in treeHits.hltPaths:
          #            print p
          if isTripleMuTriggered: 
            numerator5 +=1

        if nMuPt8 >= 4 and nMuPt17 >= 1: 
          denominator8 +=1 
          if isTripleMuTriggered: numerator8 +=1

          """
          for p in treeHits.hltPaths:
              nTripleMu += 1
              numerator +=1
            #print "OK TripleMu"
          """

  print "n3Mu", n3Mu
  print "n3MuPt5", n3MuPt5
  print "n3MuPt5MuPt15", n3MuPt5MuPt15
  print "n4MuPt8", n4MuPt8
  print "n4MuPt8MuPt17", n4MuPt8MuPt17
  print "nTripleMu", nTripleMu 
  print "nMETTrigger2016", nMETTrigger2016
  print "nEvent_METTrigger2016", nEvent_METTrigger2016

  print numerator5, denominator5
  print "efficiency", numerator5 / denominator5
  print numerator8, denominator8

  #  print numerator8, denominator8
  # print "efficiency", numerator8 / denominator8
