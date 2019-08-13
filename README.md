MuJetAnalysis
=============

The structure of the code are documented below. Although one could navigate the whole repository on their own, the document provides a heuristic approach to facilitate this process. Meanwhile, in order to be new-user-friendly, the structure is described from downstream to upstream.

## Running the analyzer
`cmsRun MuJetAnalysis/DataFormats/scripts/patifyMC_13TeV/patTuple_cutana_mujets_MiniAOD_cfg.py`
By issuing the command above, one is able to produce Ntuples for various analysis studies.

## Cut-and-count
A simple macro is available for quick cut-and-count based on the Ntuples: `CutFlowAnalyzer/scripts/cutflow_macros/foo_modified.C`.

## Analyzer modules
The analyzer code consists of the following modules, namely, from a offline reconstructed file (MiniAOD), PAT objects is created. Then these PAT muons are used in muon pair formation and selections.

After the muon pair selections, they are used in `CutFlowAnalyzer/plugins/CutFlowAnalyzer_MiniAOD.cc`.

## Muon pair modules
The muon pair is an instance of the pat::MultiMuon. This is defined in `DataFormats/interface/MultiMuon.h` and `DataFormats/src/MultiMuon.cc`.
