Run the following command to get the cut flow table for all signals:

    echo 'gROOT->ProcessLine(".L foo_modified.C++"); analysis("SignalsList2017.txt" )' | root -l -b

The "SignalsList2017.txt" file contains a text file for each 2017 signal samples. Each txt file list the Ntuple path for this signal sample.
Similarly, "BKGsList2017.txt" points to all background samples ntuples; "DataList2017.txt" contains all 2017 data ntuple paths.
