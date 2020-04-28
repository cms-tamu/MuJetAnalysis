## Cut Flow Table

Run the following command to get the cut flow table for all signals:
```
echo 'gROOT->ProcessLine(".L foo_modified.C++"); analysis("SignalsList2017MSSMD.txt")' | root -l -b
```

The "SignalsList201*.txt" file list text files for all signal samples in this year (2017/2018). Each text file point to the Ntuple path of a signal sample.

Similarly, the "SignalsList201*.txt" file can be replaced by "BKGsList201*.txt", which is the relevant one for all background Ntuples; and "DataList201*.txt" for data.

The "SignalsList2017MSSMD_0pT.txt" file list text files for ntuples produced with setting "minPt = cms.double(0.)" in "MuJetProducerRun2_cfi.py" when pairing muons, instead of 8GeV for other cases.
