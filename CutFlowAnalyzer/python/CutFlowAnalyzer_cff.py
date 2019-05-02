import FWCore.ParameterSet.Config as cms

from MuJetAnalysis.CutFlowAnalyzer.CutFlowAnalyzer_cfi import *

## Monte Carlo
cutFlowAnalyzerPXBL4PXFL3 = cutFlowAnalyzer.clone(
    barrelPixelLayer = cms.int32(4),
    endcapPixelLayer = cms.int32(3),
    muJets = cms.InputTag("PFMuJetProducer05PXBL4PXFL3"),
    muJetOrphans = cms.InputTag("PFMuJetProducer05PXBL4PXFL3", "Orphans"),
)
cutFlowAnalyzers = cms.Sequence(
    cutFlowAnalyzerPXBL4PXFL3
)
