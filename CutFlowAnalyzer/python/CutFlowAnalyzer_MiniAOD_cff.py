import FWCore.ParameterSet.Config as cms

from MuJetAnalysis.CutFlowAnalyzer.CutFlowAnalyzer_MiniAOD_cfi import *

## Monte Carlo
cutFlowAnalyzerPXBL3PXFL2 = cutFlowAnalyzer.clone(
    barrelPixelLayer = cms.int32(3),
    endcapPixelLayer = cms.int32(2),
    muJets = cms.InputTag("PFMuJetProducer05PXBL3PXFL2"),
    muJetOrphans = cms.InputTag("PFMuJetProducer05PXBL3PXFL2", "Orphans"),
)
cutFlowAnalyzerPXBL4PXFL3 = cutFlowAnalyzer.clone(
    barrelPixelLayer = cms.int32(4),
    endcapPixelLayer = cms.int32(3),
    muJets = cms.InputTag("PFMuJetProducer05PXBL4PXFL3"),
    muJetOrphans = cms.InputTag("PFMuJetProducer05PXBL4PXFL3", "Orphans"),
)
cutFlowAnalyzers = cms.Sequence(
    cutFlowAnalyzerPXBL3PXFL2
    #cutFlowAnalyzerPXBL3PXFL2 *
    #cutFlowAnalyzerPXBL4PXFL3
)
