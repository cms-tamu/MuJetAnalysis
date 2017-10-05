## user packages
import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from Helpers import *
from ROOT import *

## open the file with locations to MC files
readTextFileWithSamples("../DarkSUSY_All_2016.txt")

chain = TChain("Events")

location = "/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mN1_10_mGammaD_8p5_cT_3_13TeV_pythia8/DarkSUSY_mH_125_mN1_10_mGammaD_8p5_cT_3_13TeV_pythia8_PATANA_v1/170716_080047/0000/"

## files = addfiles(chain, location)

print decodeDarkSUSYFileName(location)

exit(1)
## 
file = TFile("/fdata/hepx/store/user/lpernie/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_0_13TeV_20k_MG452_BR224_LHE_pythia8_GEN_SIM_MINIAOD_V2_v1/DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_0_13TeV_20k_PAT_ANA_V2_v1/170124_224445/0000/out_ana_1.root")

#file = TFile("/fdata/hepx/store/user/castaned/DarkSUSY_mH_125_mN1_10_mGammaD_0p7_cT_0p05_13TeV_pythia8/DarkSUSY_mH_125_mN1_10_mGammaD_0p7_cT_0p05_13TeV_pythia8_PATANA_v1/170716_075345/0000/out_ana_1.root")

dirAna = file.Open("cutFlowAnalyzerPXBL3PXFL2")
tree = file.Get("cutFlowAnalyzerPXBL3PXFL2/Events") 

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

    
    
