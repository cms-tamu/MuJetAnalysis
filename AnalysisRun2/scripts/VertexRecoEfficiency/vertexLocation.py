## user packages
import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from Helpers import *
from ROOT import *

## open the file with locations to MC files
mcSamples = readTextFileWithSamples("../DarkSUSY_All_2016.txt")


Lxy_histos = {}
Lxy_histos["0p25"] = {}

for sample in mcSamples:
    chain = TChain("cutFlowAnalyzerPXBL3PXFL2/Events")

    n1, ma, ctau = decodeDarkSUSYFileNameMany(sample)
    print "Checking", "mN1", n1, "mA", ma, "cT", ctau

    ## only process the low mass samples now
    if ma != '0p25':
        continue
    
    chain = addfilesMany(chain, sample)    
    print "Processing", n1, ma, ctau, chain.GetEntries()

    lxy_hist = TH1F("lxy_hist", "Lxy distribution", 150, 0, 300);
    chain.Draw("genA0_Lxy>>lxy_hist");
    Lxy_histos[ma][ctau] = lxy_hist
    
    """
    break

    for event in range(0,chain.GetEntries()):
        chain.GetEntry(event)
        print "Processing event", event
        print chain.genA0_Lxy

    break
    """
   
c1 = TCanvas("c1","test",800,600);
c1.cd()

first = True
for histo in Lxy_histos["0p25"]:
    if first: 
        lxy_hist.Draw();
        first = False
    else:
        lxy_hist.Draw("same");
    
canvasName = getDarkSUSYFileName(n1, ma, ctau)
c1.SaveAs(canvasName + "_temp" + ".png")

   
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

    
    
