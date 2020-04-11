## Cut Flow Table

Run the following command to get the cut flow table for all signals:
```
echo 'gROOT->ProcessLine(".L foo_modified.C++"); analysis("SignalsList2017MSSMD.txt")' | root -l -b
```

The "SignalsList201*.txt" file list text files for all signal samples in this year (2017/2018). Each text file point to the Ntuple path of a signal sample.

Similarly, the "SignalsList201*.txt" file can be replaced by "BKGsList201*.txt", which is the relevant one for all background Ntuples; and "DataList201*.txt" for data.
