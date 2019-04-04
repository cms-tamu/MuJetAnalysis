import FWCore.ParameterSet.Config as cms
from MuJetAnalysis.CutFlowAnalyzer.CutFlowAnalyzer_MiniAOD_cfi import *

cutFlowAnalyzerPXBL4PXFL3 = cutFlowAnalyzer.clone(
    barrelPixelLayer = cms.int32(4),
    endcapPixelLayer = cms.int32(3),
    muPairs = cms.InputTag("PFMuJetProducer05PXBL4PXFL3", "Pairs"),#All possible Mu pairs
    muJets = cms.InputTag("PFMuJetProducer05PXBL4PXFL3"),
    muJetOrphans = cms.InputTag("PFMuJetProducer05PXBL4PXFL3", "Orphans"),
)
cutFlowAnalyzers = cms.Sequence(
    cutFlowAnalyzerPXBL4PXFL3
)
