from ROOT import *
import array
import numpy as np
import copy

def My_dPhi (phi1, phi2):
  dPhi = phi1 - phi2
  if (dPhi >  TMath.Pi()):
      dPhi -= 2*TMath.Pi()

  if (dPhi <  -TMath.Pi()):
      dPhi += 2*TMath.Pi()

  return abs(dPhi)


def deltaR(eta1, phi1, eta2, phi2):
    deta = eta1 - eta1
    dphi = My_dPhi(phi1, phi2)
    dR   = np.sqrt(dphi*dphi + deta*deta)
    return dR

def matchGenMuToRecoMuon(genEta0, genPhi0,
                         genEta1, genPhi1,
                         genEta2, genPhi2,
                         genEta3, genPhi3,
                         recoEta0, recoPhi0,
                         recoEta1, recoPhi1,
                         recoEta2, recoPhi2,
                         recoEta3, recoPhi3):

    recoEtas = [recoEta0, recoEta1, recoEta2, recoEta3]
    recoPhis = [recoPhi0, recoPhi1, recoPhi2, recoPhi3]
  
    # first check the dEta for muon 0
    dR00 = deltaR(genEta0, genPhi0, recoEta0, recoPhi0)
    dR01 = deltaR(genEta0, genPhi0, recoEta1, recoPhi1)
    dR02 = deltaR(genEta0, genPhi0, recoEta2, recoPhi2)
    dR03 = deltaR(genEta0, genPhi0, recoEta3, recoPhi3)

    dR0 = [dR00, dR01, dR02, dR03]
    print dR0
    dR0_sorted = copy.copy(dR0)
    ## sort and trim
    dR0_sorted.sort()
    dR0_sorted = dR0_sorted[:-2]
    ## check if both are exactly the same
    print dR0_sorted
    if dR0_sorted[0] == dR0_sorted[1]:
      dR0_indices = [0,1]
    else:
      dR0_indices = [dR0.index(dR0_sorted[0]), dR0.index(dR0_sorted[1])]
    print dR0, dR0_indices
    
    ## indices of second muon pair
    dR2_indices = [x for x in [0,1,2,3] if x not in dR0_indices]

    if ( deltaR(genEta2, genPhi2, recoEtas[dR2_indices[0]], recoPhis[dR2_indices[0]]) < 
         deltaR(genEta2, genPhi2, recoEtas[dR2_indices[1]], recoPhis[dR2_indices[1]]) ):
      dR2_indices = dR2_indices
    else:
      dR2_indices = dR2_indices[::-1]
      
    print dR2_indices
    print 

    indices = dR0_indices + dR2_indices
    print indices
    return indices

def matchAllGenMuToAllRecoMu(genA0Mu0_eta, genA0Mu0_phi, 
                             genA0Mu1_eta, genA0Mu1_phi, 
                             genA1Mu0_eta, genA1Mu0_phi, 
                             genA1Mu1_eta, genA1Mu1_phi,
                             selMu0_eta,   selMu0_phi, 
                             selMu1_eta,   selMu1_phi, 
                             selMu2_eta,   selMu2_phi, 
                             selMu3_eta,   selMu3_phi):
  
  indices = [-1,-1,-1,-1]
  
  # step 1: quick calculation
  dEta_0_0 = abs(genA0Mu0_eta - selMu0_eta) < 0.3


genA0_RecoIndex = array.array("i", [0])
genA1_RecoIndex = array.array("i", [0])

genA0Mu0_RecoIndex = array.array("i", [0])
genA0Mu1_RecoIndex = array.array("i", [0])
genA1Mu0_RecoIndex = array.array("i", [0])
genA1Mu1_RecoIndex = array.array("i", [0])

"""
myfile  = TFile.Open("total_DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_all.root")


#tree = myfile.Get("cutFlowAnalyzerPXBL3PXFL2/Events")
tree = myfile.Get("Events")

newFile = TFile.Open("preselected_DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_all.root",
                     "RECREATE") 
newChain = tree.CopyTree("nRecoMu>=4")
newChain.AutoSave()
newFile.Close()
exit(1)
"""

myfile  = TFile.Open("total_DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_all.root")
tree = myfile.Get("Events")


newfile = TFile("new_DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_all.root","RECREATE")
tree_clone = tree.CloneTree()
new_tree = TTree( 'RecoIndex', '' )
 
b_genA0_RecoIndex = new_tree.Branch( "genA0_RecoIndex" , genA0_RecoIndex, 'genA0_RecoIndex/I' )
b_genA1_RecoIndex = new_tree.Branch( "genA1_RecoIndex" , genA1_RecoIndex, 'genA1_RecoIndex/I' )

b_genA0Mu0_RecoIndex = new_tree.Branch( "genA0Mu0_RecoIndex" , genA0Mu0_RecoIndex, 'genA0Mu0_RecoIndex/I' )
b_genA0Mu1_RecoIndex = new_tree.Branch( "genA0Mu1_RecoIndex" , genA0Mu1_RecoIndex, 'genA0Mu1_RecoIndex/I' )
b_genA1Mu0_RecoIndex = new_tree.Branch( "genA1Mu0_RecoIndex" , genA1Mu0_RecoIndex, 'genA1Mu0_RecoIndex/I' )
b_genA1Mu1_RecoIndex = new_tree.Branch( "genA1Mu1_RecoIndex" , genA1Mu1_RecoIndex, 'genA1Mu1_RecoIndex/I' )

i = 0
for event in tree_clone:
    i += 1
    if i%1000==0:
      print "Event", i

    if i>10000000000000000: 
        break

    ## match muon to muon
    genA0Mu0_RecoIndex[0] = -1 
    genA0Mu1_RecoIndex[0] = -1
    genA1Mu0_RecoIndex[0] = -1
    genA1Mu1_RecoIndex[0] = -1

    ## match dark photon to dimuon
    genA0_RecoIndex[0] = -1 
    genA1_RecoIndex[0] = -1

    ## eta-phi
    genA0_eta = tree_clone.genA0_eta
    genA0_phi = tree_clone.genA0_phi

    genA1_eta = tree_clone.genA1_eta
    genA1_phi = tree_clone.genA1_phi
    
    selDiMuC_eta = tree_clone.diMuonC_FittedVtx_eta
    selDiMuC_phi = tree_clone.diMuonC_FittedVtx_phi

    selDiMuF_eta = tree_clone.diMuonF_FittedVtx_eta
    selDiMuF_phi = tree_clone.diMuonF_FittedVtx_phi

    genA0Mu0_eta = tree_clone.genA0Mu0_eta
    genA0Mu1_eta = tree_clone.genA0Mu1_eta
    genA1Mu0_eta = tree_clone.genA1Mu0_eta
    genA1Mu1_eta = tree_clone.genA1Mu1_eta

    genA0Mu0_phi = tree_clone.genA0Mu0_phi
    genA0Mu1_phi = tree_clone.genA0Mu1_phi
    genA1Mu0_phi = tree_clone.genA1Mu0_phi
    genA1Mu1_phi = tree_clone.genA1Mu1_phi

    selMuEta0 = tree_clone.selMu0_eta
    selMuEta1 = tree_clone.selMu1_eta
    selMuEta2 = tree_clone.selMu2_eta
    selMuEta3 = tree_clone.selMu3_eta

    selMuPhi0 = tree_clone.selMu0_phi
    selMuPhi1 = tree_clone.selMu1_phi
    selMuPhi2 = tree_clone.selMu2_phi
    selMuPhi3 = tree_clone.selMu3_phi

    ## calculate the dRs    
    dR0 = [
      deltaR(genA0Mu0_eta, genA0Mu0_phi, selMuEta0, selMuPhi0),
      deltaR(genA0Mu0_eta, genA0Mu0_phi, selMuEta1, selMuPhi1),
      deltaR(genA0Mu0_eta, genA0Mu0_phi, selMuEta2, selMuPhi2),
      deltaR(genA0Mu0_eta, genA0Mu0_phi, selMuEta3, selMuPhi3)
           ]
    dR1 = [
      deltaR(genA0Mu1_eta, genA0Mu1_phi, selMuEta0, selMuPhi0),
      deltaR(genA0Mu1_eta, genA0Mu1_phi, selMuEta1, selMuPhi1),
      deltaR(genA0Mu1_eta, genA0Mu1_phi, selMuEta2, selMuPhi2),
      deltaR(genA0Mu1_eta, genA0Mu1_phi, selMuEta3, selMuPhi3)
           ]
    dR2 = [
      deltaR(genA1Mu0_eta, genA1Mu0_phi, selMuEta0, selMuPhi0),
      deltaR(genA1Mu0_eta, genA1Mu0_phi, selMuEta1, selMuPhi1),
      deltaR(genA1Mu0_eta, genA1Mu0_phi, selMuEta2, selMuPhi2),
      deltaR(genA1Mu0_eta, genA1Mu0_phi, selMuEta3, selMuPhi3)
           ]
    dR3 = [
      deltaR(genA1Mu1_eta, genA1Mu1_phi, selMuEta0, selMuPhi0),
      deltaR(genA1Mu1_eta, genA1Mu1_phi, selMuEta1, selMuPhi1),
      deltaR(genA1Mu1_eta, genA1Mu1_phi, selMuEta2, selMuPhi2),
      deltaR(genA1Mu1_eta, genA1Mu1_phi, selMuEta3, selMuPhi3)
           ]
    
    ## check if dR is less than 0.2 
    maxdR = 0.2
    genA0Mu0_RecoIndex[0] = len([x for x in dR0 if x < maxdR]) 
    genA0Mu1_RecoIndex[0] = len([x for x in dR1 if x < maxdR])
    genA1Mu0_RecoIndex[0] = len([x for x in dR2 if x < maxdR])
    genA1Mu1_RecoIndex[0] = len([x for x in dR3 if x < maxdR])

    #print [x for x in dR0 if x < maxdR]
    #print [x for x in dR1 if x < maxdR]
    #print [x for x in dR2 if x < maxdR]
    #print [x for x in dR3 if x < maxdR]
    
    #print genA0Mu0_RecoIndex[0], genA0Mu1_RecoIndex[0], genA1Mu0_RecoIndex[0], genA1Mu1_RecoIndex[0]
    
    dRA0 = [
      deltaR(genA0_eta, genA0_phi, selDiMuC_eta, selDiMuC_phi),
      deltaR(genA0_eta, genA0_phi, selDiMuF_eta, selDiMuF_phi)
      ]
    dRA1 = [
      deltaR(genA1_eta, genA1_phi, selDiMuC_eta, selDiMuC_phi),
      deltaR(genA1_eta, genA1_phi, selDiMuF_eta, selDiMuF_phi)
      ]

    genA0_RecoIndex[0] = len([x for x in dRA0 if x < maxdR]) 
    genA1_RecoIndex[0] = len([x for x in dRA1 if x < maxdR])

    print [x for x in dRA0 if x < maxdR]
    print [x for x in dRA1 if x < maxdR]
    print genA0_RecoIndex[0], genA1_RecoIndex[0]

    new_tree.Fill()

newfile.Write()
newfile.Close()
myfile.Close()
