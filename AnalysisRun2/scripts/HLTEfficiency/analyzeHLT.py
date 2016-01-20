from __future__ import division ## floating point division
from ROOT import *

def passedHltPath(t,trigger):
    return (trigger in t.hltPaths)

def error_binom(total, selected):
    '''Source: 'http://home.fnal.gov/~paterno/images/effic.pdf'''
    return 1/total*TMath.Sqrt(selected*(1-(selected/total)))

def analyzeHLT():


    file = '/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0275_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151026/151027_025434/0000/out_ana_1.root'
    file = '/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0275_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v4/DarkSUSY_mH_125_mGammaD_0275_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151026/151027_025655/0000/out_ana_1.root'

    file='/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_000_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_000_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151106/151106_193924/0000/out_ana_1.root'
    file='/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_0250_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151027/151027_160931/0000/out_ana_1.root'
    file = '/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_8500_cT_005_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_005_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151026/151027_161154/0000/out_ana_1.root'
    file='/fdata/hepx/store/user/dildick/DarkSUSY_mH_125_mGammaD_8500_cT_500_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v1/DarkSUSY_mH_125_mGammaD_8500_13TeV_cT_500_madgraph452_bridge224_LHE_pythia8_741p1_ANA_20151026/151027_161324/0000/out_ana_1.root'
    file = '/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_000_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_000_Evt_80k_PATANA_v4/151117_152519/0000/out_ana_1.root'
    file = '/fdata/hepx/store/user/bmichlin/DarkSUSY_mH_125_mGammaD_0300_cT_500_Evt_80k_13TeV_MG452_BR224_LHE_pythia8_GEN_SIM_MCRUN2_71_V1_v3/DarkSUSY_mH_125_mGammaD_0300_cT_500_Evt_80k_PATANA_v4/151117_153321/0000/out_ana_Combined_80k.root'

    f = TFile.Open(file)

    print "Processing", file
    ana = "cutFlowAnalyzer"
    dir = f.Get(ana)      
    print "Opening directory", dir.GetName()
    t = dir.Get("Events");
    print "Loading tree", t.GetName()
    
    nentries = t.GetEntries();
    m_events = 0
    m_events4GenMu = 0
    m_events1GenMu17 = 0
    m_events2GenMu8 = 0      
    m_events3GenMu8 = 0
    m_events4GenMu8 = 0
    m_events1SelMu17 = 0
    m_events2SelMu8 = 0
    m_events3SelMu8 = 0
    m_events4SelMu8 = 0
    m_events2MuJets = 0
    m_events2DiMuons = 0
    
    m_events2DiMuonsDzOK_FittedVtx = 0
    m_events2DiMuonsDzOK_ConsistentVtx = 0

    m_events2DiMuonsMassOK_FittedVtx_noHLT = 0
    m_events2DiMuonsMassOK_ConsistentVtx_noHLT = 0
    m_events2DiMuonsIsoTkOK_FittedVtx_noHLT = 0
    m_events2DiMuonsIsoTkOK_ConsistentVtx_noHLT = 0
    m_eventsVertexOK_FittedVtx_noHLT = 0
    m_eventsVertexOK_ConsistentVtx_noHLT = 0

    m_eventsDiMuonHLTFired_FittedVtx = 0
    m_eventsDiMuonHLTFired_ConsistentVtx = 0
    m_events2DiMuonsMassOK_FittedVtx = 0
    m_events2DiMuonsMassOK_ConsistentVtx = 0
    m_events2DiMuonsIsoTkOK_FittedVtx = 0
    m_events2DiMuonsIsoTkOK_ConsistentVtx = 0

    m_eventsVertexOK_FittedVtx = 0
    m_eventsVertexOK_ConsistentVtx = 0

    m_eventsGoodFailingHLT = 0
    m_eventsGoodPassingHLT = 0
    m_isDiMuonHLTFired = 0
    m_eventsVertexOK_FittedVtx_noHLT_lxyCut = 0

    ## make a dictionary to count the triggers
    hltPaths = [
        'HLT_DoubleMu33NoFiltersNoVtx_v1',
        'HLT_Mu17_Mu8_DZ_v1',
        'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v1',
        'HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v1',
        'HLT_Mu30_TkMu11_v1',
        'HLT_TripleMu_12_10_5_v1',
        'HLT_TripleMu_12_10_5_onlyL1NewSeed_v1',
        'HLT_TrkMu15_DoubleTrkMu5_v1',
        'HLT_Mu15_DoubleMu5NoVtx_v1',
        'HLT_TrkMu15_DoubleTrkMu5NoVtx_v1',
        'HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx_v1',
        'HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx_v2',
        'HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx_v1',
        'HLT_Mu17_Mu8_DZ_v1_NoDz',
        'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v1_NoIso',
        'HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v1_NoIso',
        'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v1'
    ]
    hltPathPass = {}
    hltPathFail = {}
    for p in hltPaths:
        hltPathPass[p] = 0 ## intialization
        hltPathFail[p] = 0 ## intialization

    for k in range(0,nentries):
        t.GetEntry(k)    
        m_events += 1
        ## print "Processing Event", k

        if (t.is4GenMu):
            m_events4GenMu += 1            
        if (t.is1GenMu17):
            m_events1GenMu17 += 1
            if (t.is2GenMu8):
                m_events2GenMu8 += 1      
            if (t.is3GenMu8):
                m_events3GenMu8 += 1
            if (t.is4GenMu8):
                m_events4GenMu8 += 1
        if (t.is1SelMu17):
            m_events1SelMu17 += 1
            if (t.is2SelMu8):
                m_events2SelMu8 += 1
            if (t.is3SelMu8):
                m_events3SelMu8 += 1
            if (t.is4SelMu8):
                m_events4SelMu8 += 1
                
        if (t.is2MuJets):
            m_events2MuJets += 1
            if (t.is2DiMuons):
                m_events2DiMuons += 1
                
                if (t.is2DiMuonsDzOK_FittedVtx):
                    m_events2DiMuonsDzOK_FittedVtx += 1
                    if (t.is2DiMuonsMassOK_FittedVtx):
                        m_events2DiMuonsMassOK_FittedVtx_noHLT += 1
                        if (t.is2DiMuonsIsoTkOK_FittedVtx):
                            m_events2DiMuonsIsoTkOK_FittedVtx_noHLT += 1
                            if (t.isVertexOK):
                                m_eventsVertexOK_FittedVtx_noHLT += 1                         
                                if (t.genA0_Lxy < 10.4 and t.genA1_Lxy < 10.4):                                  
                                    m_eventsVertexOK_FittedVtx_noHLT_lxyCut += 1
                                    for p in hltPaths:
                                        if passedHltPath(t,p):
                                            hltPathPass[p] += 1
                                        else:
                                            hltPathFail[p] += 1

                    if (t.isDiMuonHLTFired):
                        m_eventsDiMuonHLTFired_FittedVtx += 1
                        if (t.is2DiMuonsMassOK_FittedVtx):
                            m_events2DiMuonsMassOK_FittedVtx += 1
                            if (t.is2DiMuonsIsoTkOK_FittedVtx):
                                m_events2DiMuonsIsoTkOK_FittedVtx += 1
                                if (t.isVertexOK):
                                    m_eventsVertexOK_FittedVtx += 1
                                    
                if (t.is2DiMuonsDzOK_ConsistentVtx):
                    m_events2DiMuonsDzOK_ConsistentVtx += 1
                    if (t.is2DiMuonsMassOK_ConsistentVtx):
                        m_events2DiMuonsMassOK_ConsistentVtx_noHLT += 1
                        if (t.is2DiMuonsIsoTkOK_ConsistentVtx):
                            m_events2DiMuonsIsoTkOK_ConsistentVtx_noHLT += 1
                            if (t.isVertexOK):
                                m_eventsVertexOK_ConsistentVtx_noHLT += 1
                    if (t.isDiMuonHLTFired):
                        m_eventsDiMuonHLTFired_ConsistentVtx += 1
                        if (t.is2DiMuonsMassOK_ConsistentVtx):
                            m_events2DiMuonsMassOK_ConsistentVtx += 1
                            if (t.is2DiMuonsIsoTkOK_ConsistentVtx):
                                m_events2DiMuonsIsoTkOK_ConsistentVtx += 1
                                if (t.isVertexOK):
                                    m_eventsVertexOK_ConsistentVtx += 1
                                    
    print "m_events", m_events
    print "m_isDiMuonHLTFired", m_isDiMuonHLTFired
    print "m_events4GenMu", m_events4GenMu
    print "m_events1GenMu17", m_events1GenMu17
    print "m_events2GenMu8", m_events2GenMu8
    print "m_events3GenMu8", m_events3GenMu8
    print "m_events4GenMu8", m_events4GenMu8
    print "m_events1SelMu17", m_events1SelMu17
    print "m_events2SelMu8", m_events2SelMu8
    print "m_events3SelMu8", m_events3SelMu8
    print "m_events4SelMu8", m_events4SelMu8

    print "m_events2MuJets", m_events2MuJets
    print "m_events2DiMuons", m_events2DiMuons

    print "m_events2DiMuonsDzOK_FittedVtx", m_events2DiMuonsDzOK_FittedVtx
#    print "m_events2DiMuonsDzOK_ConsistentVtx", m_events2DiMuonsDzOK_ConsistentVtx
    
    print "m_events2DiMuonsMassOK_FittedVtx_noHLT", m_events2DiMuonsMassOK_FittedVtx_noHLT
    print "m_events2DiMuonsIsoTkOK_FittedVtx_noHLT", m_events2DiMuonsIsoTkOK_FittedVtx_noHLT
    print "m_eventsVertexOK_FittedVtx_noHLT", m_eventsVertexOK_FittedVtx_noHLT
    print "m_eventsVertexOK_FittedVtx_noHLT_lxyCut", m_eventsVertexOK_FittedVtx_noHLT_lxyCut
    print
    print "m_events2DiMuonsMassOK_FittedVtx", m_events2DiMuonsMassOK_FittedVtx
    print "m_events2DiMuonsIsoTkOK_FittedVtx", m_events2DiMuonsIsoTkOK_FittedVtx
    print "m_eventsVertexOK_FittedVtx", m_eventsVertexOK_FittedVtx
    print
##     print "m_events2DiMuonsMassOK_ConsistentVtx_noHLT", m_events2DiMuonsMassOK_ConsistentVtx_noHLT
##     print "m_events2DiMuonsIsoTkOK_ConsistentVtx_noHLT", m_events2DiMuonsIsoTkOK_ConsistentVtx_noHLT
##     print "m_eventsVertexOK_ConsistentVtx_noHLT", m_eventsVertexOK_ConsistentVtx_noHLT
##     print
##     print "m_events2DiMuonsMassOK_ConsistentVtx", m_events2DiMuonsMassOK_ConsistentVtx
##     print "m_events2DiMuonsIsoTkOK_ConsistentVtx", m_events2DiMuonsIsoTkOK_ConsistentVtx
##     print "m_eventsVertexOK_ConsistentVtx", m_eventsVertexOK_ConsistentVtx
    print
    print "Trigger efficiencies:"
    for p in hltPaths:
        eff = hltPathPass[p]/m_eventsVertexOK_FittedVtx_noHLT_lxyCut
        data = p, hltPathPass[p], hltPathFail[p], eff
        print '\t{0[0]:<20} Pass {0[1]:<5} Fail {0[2]:<5} Efficiency {0[3]:<10}'.format(data), error_binom(m_eventsVertexOK_FittedVtx_noHLT_lxyCut, hltPathPass[p])
    
if __name__ == "__main__":
    analyzeHLT()
