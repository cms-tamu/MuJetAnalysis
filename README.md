MuJetAnalysis
=============

Most updated branch: weishi10141993/for-CMSSW-94X

The structure of the code are documented below. Although one could navigate the whole repository on their own, the document provides a heuristic approach to facilitate this process. Meanwhile, in order to be new-user-friendly, the structure is described from downstream to upstream.

## Running the analyzer
`cmsRun MuJetAnalysis/DataFormats/scripts/patifyMC_13TeV/patTuple_cutana_mujets_MiniAOD_cfg.py`
By issuing the command above, one is able to produce Ntuples for various analysis studies.

## Cut-and-count
A simple macro is available for quick cut-and-count based on the Ntuples: `CutFlowAnalyzer/scripts/cutflow_macros/CutFlow_2018L2Mu23.C`. More details on page.
