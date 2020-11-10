## Cut Flow Table

Run the following command to get the cut flow table for all signals:
```
echo 'gROOT->ProcessLine(".L CutFlow_2018L2Mu23.C++"); analysis("SignalsList2018ALP_2SAmu_NoVtxProbCut_4HLT.txt")' | root -l -b
```

The "SignalsList201*.txt" file list text files for all signal samples in this year. Each text file point to the Ntuple path of a signal sample.

Similarly, the "SignalsList201*.txt" file can be replaced by "BKGsList201*.txt", which is the relevant one for all background Ntuples; and "DataList201*.txt" for data.

MiniAODSIM samples are moved to TAMU Terra cluster, to get a list of all files in a sample:
`ls -d "$PWD"/* > text.txt`
These are stored at `MuJetAnalysis/DataFormats/scripts/patifyMC_13TeV/*SamplesTerra` for 2017 and 2018.
To get all end subdirectories:
`find <pwd> -type d -links 2 > /home/ws13/EndDir.txt`
`grep -E '2SA' EndDir.txt > /home/ws13/input.txt`
`root -l -b -q AutoList.C++`
