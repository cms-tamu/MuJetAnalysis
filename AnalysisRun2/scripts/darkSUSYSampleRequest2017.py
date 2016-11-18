ctauString = ["0", "0p05", "0p1", "0p2", "0p5", "1", "2", "3", "5", "10", "20", "50", "100"]
events = [100000, 100000, 100000, 100000, 100000, 200000, 200000, 200000,
          200000, 1000000, 10000000, 10000000, 10000000 ]
n=0
nEvents = 0
for mGS in mGammaSmallString:
    for cTS, evts in zip(ctauString, events):
        n = n + 1
        nEvents = nEvents +  evts
        print n, "DarkSUSY_mH_125_mN1_10_mGammaD_" + mGS + "_cT_" + cTS + "_13TeV_pythia8", evts

mGammaLargeString = ["1", "1p5", "2", "5", "8p5"]
ctauString = ["0", "0p5", "1", "2", "3", "5", "10", "20", "50", "100"]
events = [100000, 100000, 200000, 200000, 200000,
          200000, 10000000, 10000000, 10000000, 10000000 ]

print
for mGS in mGammaLargeString:
    for cTS, evts in zip(ctauString, events):
        n = n + 1
        nEvents = nEvents + evts
        print n, "DarkSUSY_mH_125_mN1_10_mGammaD_" + mGS + "_cT_" + cTS + "_13TeV_pythia8"

mGammaLargeString = ["1", "5", "10", "25", "35", "59"]

print
for mGS in mGammaLargeString:
    for cTS, evts in zip(ctauString, events):
        n = n + 1
        nEvents = nEvents + evts
        print n, "DarkSUSY_mH_125_mN1_60_mGammaD_" + mGS + "_cT_" + cTS + "_13TeV_pythia8"

print
for cTS, evts in zip(ctauString, events):
    n = n + 1
    nEvents = nEvents + evts
    print n, "DarkSUSY_mH_125_mN1_30_mGammaD_5_cT_" + cTS + "_13TeV_pythia8"


mN1String = ["15", "30"]

print
for n1s in mN1String:
    for cTS, evts in zip(ctauString, events):
        n = n + 1
        nEvents = nEvents + evts
        print n, "DarkSUSY_mH_125_mN1_" + n1s + "_mGammaD_10_cT_" + cTS + "_13TeV_pythia8"

print "Total Events", nEvents
