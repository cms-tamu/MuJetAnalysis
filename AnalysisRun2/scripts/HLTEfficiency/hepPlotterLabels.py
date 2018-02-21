"""
Created:        12 September 2015
Last Updated:    2 September 2016

Dan Marley
daniel.edison.marley@cernSPAMNOT.ch
Texas A&M University

-----
File for containing information about plotting.
Note: in hepPlotter package, function "hist1d" is deprecated
"""
from collections import OrderedDict



#----------------------------------------------------------------------------------------#

def hist1d(nbins,bin_low,bin_up):
    """
    Set the binning for each histogram.
    
    @param nbins      Number of bins in histogram
    @param bin_low    Lower bin edge
    @param bin_up     Upper bin edge     
    """
    binsize = float(bin_up-bin_low)/nbins
    arr     = [i*binsize+bin_low for i in xrange(nbins+1)]

    return arr



#----------------------------------------------------------------------------------------#

def text_dicts():
    """
    Dictionaries that contain labels, colors, and binnings for plots.
    This make it a little easier to edit everything you need to
    in one spot.
    
    NB: The colors for TTS_M* are numbers because they are sampled
    from the colormap under: signal['color'] ='Reds' -- the value at this time.
    """
    samples = OrderedDict()
    samples['TTS_M500']  = {'label':r'm$_\text{T}$=500 GeV',\
                            'color':17}
    samples['TTS_M600']  = {'label':r'm$_\text{T}$=600 GeV',\
                            'color':34}
    samples['TTS_M700']  = {'label':r'm$_\text{T}$=700 GeV',\
                            'color':51}
    samples['TTS_M750']  = {'label':r'm$_\text{T}$=750 GeV',\
                            'color':68}
    samples['TTS_M800']  = {'label':r'm$_\text{T}$=800 GeV',\
                            'color':85}
    samples['TTS_M850']  = {'label':r'm$_\text{T}$=850 GeV',\
                            'color':102}
    samples['TTS_M900']  = {'label':r'm$_\text{T}$=900 GeV',\
                            'color':119}
    samples['TTS_M950']  = {'label':r'm$_\text{T}$=950 GeV',\
                            'color':136}
    samples['TTS_M1000'] = {'label':r'm$_\text{T}$=1000 GeV',\
                            'color':153}
    samples['TTS_M1050'] = {'label':r'm$_\text{T}$=1050 GeV',\
                            'color':170}
    samples['TTS_M1100'] = {'label':r'm$_\text{T}$=1100 GeV',\
                            'color':187}
    samples['TTS_M1150'] = {'label':r'm$_\text{T}$=1150 GeV',\
                            'color':204}
    samples['TTS_M1200'] = {'label':r'm$_\text{T}$=1200 GeV',\
                            'color':221}
    samples['TTS_M1300'] = {'label':r'm$_\text{T}$=1300 GeV',\
                            'color':238}
    samples['TTS_M1400'] = {'label':r'm$_\text{T}$=1400 GeV',\
                            'color':256}
    samples['BBS_M500']  = {'label':r'm$_\text{B}$=500 GeV',\
                            'color':17}
    samples['BBS_M600']  = {'label':r'm$_\text{B}$=600 GeV',\
                            'color':34}
    samples['BBS_M700']  = {'label':r'm$_\text{B}$=700 GeV',\
                            'color':51}
    samples['BBS_M750']  = {'label':r'm$_\text{B}$=750 GeV',\
                            'color':68}
    samples['BBS_M800']  = {'label':r'm$_\text{B}$=800 GeV',\
                            'color':85}
    samples['BBS_M850']  = {'label':r'm$_\text{B}$=850 GeV',\
                            'color':102}
    samples['BBS_M900']  = {'label':r'm$_\text{B}$=900 GeV',\
                            'color':119}
    samples['BBS_M950']  = {'label':r'm$_\text{B}$=950 GeV',\
                            'color':136}
    samples['BBS_M1000'] = {'label':r'm$_\text{B}$=1000 GeV',\
                            'color':153}
    samples['BBS_M1050'] = {'label':r'm$_\text{B}$=1050 GeV',\
                            'color':170}
    samples['BBS_M1100'] = {'label':r'm$_\text{B}$=1100 GeV',\
                            'color':187}
    samples['BBS_M1150'] = {'label':r'm$_\text{B}$=1150 GeV',\
                            'color':204}
    samples['BBS_M1200'] = {'label':r'm$_\text{B}$=1200 GeV',\
                            'color':221}
    samples['BBS_M1300'] = {'label':r'm$_\text{B}$=1300 GeV',\
                            'color':238}
    samples['BBS_M1400'] = {'label':r'm$_\text{B}$=1400 GeV',\
                            'color':256}
    samples['zprime_1000'] = {'label':r'm$_{\text{Z}^\prime}$=1.0 TeV','color':'r'}
    samples['zprime_1250'] = {'label':r'm$_{\text{Z}^\prime}$=1.25 TeV','color':'r'}
    samples['zprime_2250'] = {'label':r'm$_{\text{Z}^\prime}$=2.25 TeV','color':'r'}
    samples['zprime_2500'] = {'label':r'm$_{\text{Z}^\prime}$=2.5 TeV','color':'r'}
    samples['zprime_2750'] = {'label':r'm$_{\text{Z}^\prime}$=2.75 TeV','color':'r'}
    samples['zprime_3000'] = {'label':r'm$_{\text{Z}^\prime}$=3.0 TeV','color':'r'}
    samples['zprime_4000'] = {'label':r'm$_{\text{Z}^\prime}$=4.0 TeV','color':'r'}
    samples['zprime_5000'] = {'label':r'm$_{\text{Z}^\prime}$=5.0 TeV','color':'r'}
    samples['signal']      = {'label':'Signal','color':'Reds'}
    samples['one_signal']  = {'label':'Signal','color':'red'}
    samples['ttbar']       = {'label':r't$\bar{\text{t}}$','color':'white'}
    samples['ttbar_lep']   = {'label':r't$\bar{\text{t}}$ (non all-hadronic)','color':'#00ffff'}
    samples['ttbar_had']   = {'label':r't$\bar{\text{t}}$ (all-hadronic)','color':'white'}
    samples['ttbar_inclu'] = {'label':r't$\bar{\text{t}}$','color':'white'}
    samples['ttbar_HT']    = {'label':r't$\bar{\text{t}}$ (H$_{\text{T}}$)','color':'gray'}
    samples['ttbar_matched']   = {'label':r'$t\bar{t}$ (matched)','color':'lightgray'}
    samples['ttbar_other']     = {'label':r'$t\bar{t}$ (other)','color':'lightgray'}
    samples['ttbar_had_top']   = {'label':r't$\bar{\text{t}}$ (allhad t)','color':'white'}
    samples['ttbar_had_tbar']  = {'label':r't$\bar{\text{t}}$ (allhad $\bar{\text{t}}$)','color':'gray'}
    samples['ttbar_had_other'] = {'label':r't$\bar{\text{t}}$ (allhad other)','color':'darkgray'}
    samples['dijet']           = {'label':r'Dijets', 'color':'purple'}
    samples['multijet']        = {'label':r'Multi-jet', 'color':'purple'}
    samples['diboson']         = {'label':r'Diboson','color':'green'}
    samples['singletop']       = {'label':r'Single Top','color':'blue'}
    samples['singletop_tchan'] = {'label':r'Single Top (t-chan)','color':'darkblue'}
    samples['singletop_schan'] = {'label':r'Single Top (s-chan)','color':'lightblue'}
    samples['singletop_Wt']    = {'label':r'Single Top ($Wt$)','color':'cornflowerblue'}
    samples['ttbarW']    = {'label':r't$\bar{\text{t}}$W','color':'#C9FFE5'}
    samples['ttbarZ']    = {'label':r't$\bar{\text{t}}$Z','color':'#7FFFD4'}
    samples['ttbarV']    = {'label':r't$\bar{\text{t}}$V','color':'cyan'}
    samples['ttbarH']    = {'label':r't$\bar{\text{t}}$H','color':'#3AB09E'}
    samples['ttbarX']    = {'label':r't$\bar{\text{t}}$V','color':'#008B8B'}
    samples['wc']        = {'label':r'W+c','color':'gold'}
    samples['w_cfilter'] = {'label':r'W+CFilter','color':'gold'}
    samples['wbbcc']     = {'label':r'W+b$\bar{\text{b}}$/c$\bar{\text{c}}$','color':'yellow'}
    samples['w_bfilter'] = {'label':r'W+BFilter','color':'yellow'}
    samples['wlight']    = {'label':r'W+light','color':'#FBEC5D'}
    samples['w_light']   = {'label':r'W+light','color':'#FBEC5D'}
    samples['wjets']     = {'label':r'W+jets','color':'yellow'}
    samples['zc']        = {'label':r'Z+c','color':'#FF9F00'}
    samples['zbbcc']     = {'label':r'Z+b$\bar{\text{b}}$/c$\bar{\text{c}}$','color':'darkorange'}
    samples['zlight']    = {'label':r'Z+light','color':'#FF9966'}
    samples['zjets']     = {'label':r'Z+jets','color':'darkorange'}
    samples['data']      = {'label':r'Data','color':'black'}

    samples['WZto3Mu']      = {'label':r'$WZ \rightarrow 3\mu\nu$','color':'blue'}
    samples['ZZto4Mu']      = {'label':r'$ZZ \rightarrow 4\mu$','color':'red'}
    samples['ttW']      = {'label':r'$t\bar{t}W$','color':'orange'}
    samples['ttZ']      = {'label':r'$t\bar{t}Z$','color':'green'}

    ## Custom flavor component colors: Wikipedia 
    ## wlight = 'maize' (University of Michigan!)
    ## zc     = 'orange peel'
    ## zlight = 'Atomic Tangerine'
    ##   <https://en.wikipedia.org/wiki/Shades_of_cyan>
    ## ttbarW = 'Aero Blue'
    ## ttbarZ = 'Aquamarine'
    ## ttbarX = 'Dark Cyan'
    ## ttbarH = 'Keppel'

    _eta  = r'$\eta$'
    _T    = r'$_{\text{T}}$ [GeV]'
    _mass = 'Mass [GeV]'

    # set the binning for your variables
    # hist1d takes (nbinsx, xlow, xhigh)
    # set the label for each variable (need raw string, 'r' at beginning of each string)
    variables = OrderedDict()
    variables['DeltaM_hadtopleptop'] = {'bins':hist1d(20,  0., 500.0),\
                                        'label':r'$|\Delta$m$|$(T$_{\text{had}}$,T$_{\text{lep}}$) [GeV]',\
                                        'gev':True}
    variables['DeltaR_bjet1bjet2']   = {'bins':hist1d(10,  0.,   5.0),\
                                        'label':r'$\Delta$R(b-jets)',\
                                        'gev':False}
    variables['DeltaR_lepnu']        = {'bins':hist1d(12,  0.,   3.0),\
                                        'label':r'$\Delta$R($\ell$,$\nu$)',\
                                        'gev':False}
    variables['minDeltaR_hadWbjet']  = {'bins':hist1d(12,  0.,   3.0),\
                                        'label':r'min($\Delta$R(W$_{\text{had}}$,b-jet))',\
                                        'gev':False}
    variables['minDeltaR_lepbjet']   = {'bins':hist1d(12,  0.,   3.0),\
                                        'label':r'min($\Delta$R($\ell$,b-jet))',\
                                        'gev':False}
    variables['HT']                  = {'bins':hist1d(39,100., 4000.),\
                                        'label':r'H'+_T,\
                                        'gev':True}
    variables['bjet_eta']            = {'bins':hist1d(10,-2.5,   2.5),\
                                        'label':r'b-jet '+_eta,\
                                        'gev':False}
    variables['bjet_pt']             = {'bins':hist1d(10, 25.,  500.),\
                                        'label':r'b-jet p'+_T,\
                                        'gev':True}
    variables['bjet_mv2c20']         = {'bins':hist1d(10, -1.,    1.),\
                                        'label':r'b-jet mv2c20',\
                                        'gev':False}
    variables['bjet_jvt']            = {'bins':hist1d(20,  0.,    1.),\
                                        'label':r'b-jet JVT',\
                                        'gev':False}
    variables['ljet_C2']         = {'bins':hist1d(10,  0.,   0.6),\
                                        'label':r'C$_2^{\beta\text{=1}}$',\
                                        'gev':False}
    variables['ljet_D2']         = {'bins':hist1d(20,  0.,   5.0),\
                                        'label':r'D$_2^{\beta\text{=1}}$',\
                                        'gev':False}
    variables['ljet_d12']        = {'bins':hist1d(20,  0.,  125.),\
                                        'label':r'$\sqrt{\text{d}_{\text{12}}}$ [GeV]',\
                                        'gev':True}
    variables['ljet_d23']        = {'bins':hist1d(12,  0.,   60.),\
                                        'label':r'$\sqrt{\text{d}_{\text{23}}}$ [GeV]',\
                                        'gev':True}
    variables['ljet_isWmed']     = {'bins':hist1d(4, -0.5,  3.5),\
                                        'label':r'Large-R Jet W-tag (50\% $\epsilon$)',\
                                        'gev':False}
    variables['ljet_isWtight']   = {'bins':hist1d(4, -0.5,  3.5),\
                                        'label':r'Large-R Jet W-tag (25\% $\epsilon$)',\
                                        'gev':False}
    variables['ljet_isSmoothTop50'] = {'bins':hist1d(2, -0.5,   1.5),\
                                           'label':r'Large-R Jet Top-tag (50\% $\epsilon$)',\
                                           'gev':False}
    variables['ljet_isSmoothTop80'] = {'bins':hist1d(2, -0.5,   1.5),\
                                           'label':r'Large-R Jet Top-tag (80\% $\epsilon$)',\
                                           'gev':False}
    variables['ljet_eta']        = {'bins':hist1d(20, -2.,    2.),\
                                       'label':r'Large-R Jet '+_eta,\
                                       'gev':False}
    variables['ljet_phi']        = {'bins':hist1d(20, -2.,    2.),\
                                       'label':r'Large-R Jet $\phi$',\
                                       'gev':False}
    variables['ljet_m']          = {'bins':hist1d(40,  0.,  400.),\
                                        'label':r'Large-R Jet '+_mass,\
                                        'gev':True}
    variables['ljet_pt']         = {'bins':hist1d(14,200., 1500.),\
                                        'label':r'Large-R Jet p'+_T,\
                                        'gev':True}
    variables['ljet_tau1']       = {'bins':hist1d(10,  0.,   0.6),\
                                        'label':r'$\tau_{\text{1}}$',\
                                        'gev':False}
    variables['ljet_tau1_wta']   = {'bins':hist1d(10,  0.,   0.7),\
                                        'label':r'$\tau_{\text{1}}^{\text{wta}}$',\
                                        'gev':False}
    variables['ljet_tau2']       = {'bins':hist1d(10,  0.,   0.5),\
                                        'label':r'$\tau_{\text{2}}$',\
                                        'gev':False}
    variables['ljet_tau21']      = {'bins':hist1d(11,  0.,   1.1),\
                                        'label':r'$\tau_{\text{21}}$',\
                                        'gev':False}
    variables['ljet_tau21_wta']  = {'bins':hist1d(10,  0.,   1.1),\
                                        'label':r'$\tau_{\text{21}}^{\text{wta}}$',\
                                        'gev':False}
    variables['ljet_tau2_wta']   = {'bins':hist1d(10,  0.,   0.5),\
                                        'label':r'$\tau_{\text{2}}^{\text{wta}}$',\
                                        'gev':False}
    variables['ljet_tau3']       = {'bins':hist1d(10,  0.,   0.6),\
                                        'label':r'$\tau_{\text{3}}$',\
                                        'gev':False}
    variables['ljet_tau32']      = {'bins':hist1d(11,  0.,   1.1),\
                                        'label':r'$\tau_{\text{32}}$',\
                                        'gev':False}
    variables['ljet_tau32_wta']  = {'bins':hist1d(11,  0.,   1.1),\
                                        'label':r'$\tau_{\text{32}}^{\text{wta}}$',\
                                        'gev':False}
    variables['ljet_tau3_wta']   = {'bins':hist1d(10,  0.,   0.6),\
                                        'label':r'$\tau_{\text{3}}^{\text{wta}}$',\
                                        'gev':False}
    variables['btags_n']             = {'bins':hist1d(4, -0.5,  3.5),\
                                        'label':r'Number of b-tags',\
                                        'gev':False}
    variables['hadronicT_eta']       = {'bins':hist1d(30, -4.,    4.),\
                                        'label':r'T$_{\text{had}}$ '+_eta,\
                                        'gev':False}
    variables['hadronicT_m']         = {'bins':hist1d(25,  0., 1500.),\
                                        'label':r'T$_{\text{had}}$ '+_mass,\
                                        'gev':True}
    variables['hadronicT_pt']        = {'bins':hist1d(15,200., 1500.),\
                                        'label':r'T$_{\text{had}}$ p'+_T,\
                                        'gev':True}
    variables['hadronicW_eta']       = {'bins':hist1d(10,-2.5,   2.5),\
                                        'label':r'W$_{\text{had}}$ '+_eta,\
                                        'gev':False}
    variables['hadronicW_m']         = {'bins':hist1d(14, 50.,  120.),\
                                        'label':r'W$_{\text{had}}$ '+_mass,\
                                        'gev':True}
    variables['hadronicW_pt']        = {'bins':hist1d(16,200., 1000.),\
                                        'label':r'W$_{\text{had}}$ p'+_T,\
                                        'gev':True}
    variables['jet_eta']             = {'bins':hist1d(10,-2.5,   2.5),\
                                        'label':r'Small-R Jet '+_eta,\
                                        'gev':False}
    variables['jet_pt']              = {'bins':hist1d(10, 25.,  500.),\
                                        'label':r'Small-R Jet p'+_T,\
                                        'gev':True}
    variables['jet_mv2c20']          = {'bins':hist1d(10, -1.,    1.),\
                                        'label':r'Small-R Jet mv2c20',\
                                        'gev':False}
    variables['jet_jvt']             = {'bins':hist1d(20,  0.,    1.),\
                                        'label':r'Small-R Jet JVT',\
                                        'gev':False}
    variables['lep_eta']             = {'bins':hist1d(10,-2.5,   2.5),\
                                        'label':r'Lepton '+_eta,\
                                        'gev':False}
    variables['lep_pt']              = {'bins':hist1d(10, 25.,  300.),\
                                        'label':r'Lepton p'+_T,\
                                        'gev':True}
    variables['leptonicT_m']         = {'bins':hist1d(25,  0., 1500.),\
                                        'label':r'm$_\text{T}^\text{lep}$ [GeV]',\
                                        'gev':True}
    variables['leptonicT_pt']        = {'bins':hist1d(18,200., 1200.),\
                                        'label':r'T$_{\text{lep}}$ p'+_T,\
                                        'gev':True}
    variables['leptonicT_eta']       = {'bins':hist1d(10,-2.5,   2.5),\
                                        'label':r'T$_{\text{lep}}$ '+_eta,\
                                        'gev':False}
    variables['leptonicW_eta']       = {'bins':hist1d(10,-2.5,   2.5),\
                                        'label':r'W$_{\text{lep}}$ '+_eta,\
                                        'gev':False}
    variables['leptonicW_m']         = {'bins':hist1d(10, 78.,   82.),\
                                        'label':r'W$_{\text{lep}}$ '+_mass,\
                                        'gev':True}
    variables['leptonicW_pt']        = {'bins':hist1d(16,  0.,  400.),\
                                        'label':r'W$_{\text{lep}}$ p'+_T,\
                                        'gev':True}
    variables['mass_lb']             = {'bins':hist1d(32,  0.,  800.),\
                                        'label':r'm$_{\ell\text{b}}$',\
                                        'gev':True}
    variables['met_met']             = {'bins':hist1d(29, 20.,  500.),\
                                        'label':r'E$_{\text{T}}^{\text{Miss}}$ [GeV]',\
                                        'gev':True}
    variables['mtw']                 = {'bins':hist1d(12,  0.,  120.),\
                                        'label':r'$\mathsf{M_T^W}$ [GeV]',\
                                        'gev':True}
    variables['nu_eta']              = {'bins':hist1d(10,-2.5,   2.5),\
                                        'label':r'$\nu$ '+_eta,\
                                        'gev':False}
    variables['nu_pt']               = {'bins':hist1d(20, 25.,  600.),\
                                        'label':r'$\nu$ p'+_T,\
                                        'gev':True}
    variables['reclusteredW_eta']    = {'bins':hist1d(10,-2.5,   2.5),\
                                        'label':r'Re-clustered Jet '+_eta,\
                                        'gev':False}
    variables['reclusteredW_m']      = {'bins':hist1d( 14, 50.,  120.),\
                                        'label':r'Re-clustered Jet '+_mass,\
                                        'gev':True}
    variables['reclusteredW_pt']     = {'bins':hist1d(50,200., 2000.),\
                                        'label':r'Re-clustered Jet p'+_T,\
                                        'gev':True}
    variables['reclusteredW_nsub']   = {'bins':hist1d( 5,   0,     5),\
                                        'label':r'Re-clustered Jet N Subjets',\
                                        'gev':False}
    variables['reclusteredW_D2']     = {'bins':hist1d(20,  0.,   5.0),\
                                        'label':r'D$_2^{\beta\text{=1}}$',\
                                        'gev':False}
    variables['reclusteredW_rctau']  = {'bins':hist1d(20,  1.,   5.0),\
                                        'label':r'$\tau_{\text{RC}}$',\
                                        'gev':False}
    variables['resolvedW_eta']       = {'bins':hist1d(10,-2.5,   2.5),\
                                        'label':r'Resolved W '+_eta,\
                                        'gev':False}
    variables['resolvedW_m']         = {'bins':hist1d( 7, 50.,  120.),\
                                        'label':r'Resolved W '+_mass,\
                                        'gev':True}
    variables['resolvedW_pt']        = {'bins':hist1d(16,200.,  800.),\
                                        'label':r'Resolved W p'+_T,\
                                        'gev':True}
    variables['m_TTbar']             = {'bins':hist1d(30,300., 3000.),\
                                        'label':r'm$_{\text{T}\bar{\text{T}}}$',\
                                        'gev':True}
    variables['mu']   = {'label':r'$\mu$+jets','bins':None,'gev':None}
    variables['el']   = {'label':r'e+jets','bins':None,'gev':None}
    variables['muel'] = {'label':r'$\ell$+jets','bins':None,'gev':None}

    all_dicts = {'samples':samples,\
                 'variables':variables}

    return all_dicts



#----------------------------------------------------------------------------------------#

if __name__ == '__main__':

    print "Do not execute this file, only import it."
    sys.exit(1)

###          ###
### The End. ###
###          ###
