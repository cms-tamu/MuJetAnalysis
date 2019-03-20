import FWCore.ParameterSet.Config as cms

from MuJetAnalysis.CutFlowAnalyzer.CutFlowAnalyzer_MiniAOD_cfi import *

#Used in Phase-0 Pixel: cutFlowAnalyzerPXBL3PXFL2
#cutFlowAnalyzerPXBL3PXFL2 = cutFlowAnalyzer.clone(
#    barrelPixelLayer = cms.int32(3),
#    endcapPixelLayer = cms.int32(2),
#    muPairs = cms.InputTag("PFMuJetProducer05PXBL3PXFL2", "Pairs"),#All possible Mu pairs
#    muJets = cms.InputTag("PFMuJetProducer05PXBL3PXFL2"),#Delivered for signal
#    muJetOrphans = cms.InputTag("PFMuJetProducer05PXBL3PXFL2", "Orphans"),#Delivered to analyzer for bb est
#)

cutFlowAnalyzerPXBL4PXFL3 = cutFlowAnalyzer.clone(
    barrelPixelLayer = cms.int32(4),
    endcapPixelLayer = cms.int32(3),
    muPairs = cms.InputTag("PFMuJetProducer05PXBL4PXFL3", "Pairs"),#All possible Mu pairs
    muJets = cms.InputTag("PFMuJetProducer05PXBL4PXFL3"),
    muJetOrphans = cms.InputTag("PFMuJetProducer05PXBL4PXFL3", "Orphans"),
)
cutFlowAnalyzers = cms.Sequence(
    #cutFlowAnalyzerPXBL3PXFL2
    #cutFlowAnalyzerPXBL3PXFL2 *
    cutFlowAnalyzerPXBL4PXFL3
)
