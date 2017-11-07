from ROOT import *

Samples_2017_C_MET = {
  '2017C' : [
    '/fdata/hepx/store/user/dildick/MET/crab_MET-Run2017C-PromptReco-v1-20170906/170906_181237/0000/out_ana*.root',
    '/fdata/hepx/store/user/dildick/MET/crab_MET-Run2017C-PromptReco-v2-20170906/170906_181251/0000/out_ana*.root',
    '/fdata/hepx/store/user/dildick/MET/crab_MET-Run2017C-PromptReco-v2-20170906/170906_181251/0001/out_ana*.root',
    '/fdata/hepx/store/user/dildick/MET/crab_MET-Run2017C-PromptReco-v2-20170906/170906_181251/0002/out_ana*.root'
    ],
  }

def makeSkim(era, date="20171012"):

  chain = TChain("cutFlowAnalyzer_Data/Events");

  for p in Samples_2017_C_MET[era]:
      chain.Add(p)
      print p

  ## save to file
  newFile = TFile.Open("out_ana_selected_MET_" + era + "_" + date + ".root","RECREATE") 
  newChain = chain.CopyTree("nRecoMu>=3")
  newChain.AutoSave()
  newFile.Close()

  print "Processed", era


def makeSkims():

  for p in Samples_2017_C_MET:
      makeSkim(p)

makeSkims()
