MuJetAnalysis
=============

The structure of the code are documented below. Although one could navigate the whole repository on their own, the document provides a heuristic approach to facilitate this process. Meanwhile, in order to be new-user-friendly, the structure is described from downstream to upstream.

## Running the analyzer
`cmsRun MuJetAnalysis/DataFormats/scripts/patifyMC_13TeV/patTuple_cutana_mujets_MiniAOD_cfg.py`
By issuing the command above, one is able to produce Ntuples for various analysis studies.

MiniAODSIM samples are moved to TAMU Terra cluster, to get a list of all files in a sample:
`ls -d "$PWD"/* > text.txt`
These are stored at `MuJetAnalysis/DataFormats/scripts/patifyMC_13TeV/*SamplesTerra` for 2017 and 2018.
To get all end subdirectories:
`find <pwd> -type d -links 2 > /home/ws13/EndDir.txt`
`grep -E '2SA' EndDir.txt > /home/ws13/input.txt`
`root -l -b -q AutoList.C++`

## Cut-and-count
A simple macro is available for quick cut-and-count based on the Ntuples: `CutFlowAnalyzer/scripts/cutflow_macros/foo_modified.C`. More details on page.
