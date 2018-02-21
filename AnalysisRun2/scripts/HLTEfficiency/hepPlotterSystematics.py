'''
Created:        9 September 2016
Last Updated:  28 September 2016

Dan Marley
daniel.edison.marley@cernSPAMNOT.ch
University of Michigan, Ann Arbor, MI 48109
-----
Class to handle calculating and drawing all of the systematic uncertainties.
Need to calculate systematics with respect to nominal samples --
  do this for each sample (ttbar, wjets, zjets, etc.)
STRONGLY RECOMMEND USING PRE-MADE HISTOGRAMS, NOT LISTS OF VALUES & WEIGHTS
'''
import os
import sys
import ROOT
from math import fabs
from copy import deepcopy
from collections import OrderedDict

## ------------------------------ ##
## Setup Matplotlib Configuration ##
import matplotlib
mpl_version = matplotlib.__version__
matplotlib.use('Agg') # Force matplotlib to not use any Xwindows backend.
from matplotlib import rc
from matplotlib import pyplot as plt
from matplotlib import gridspec
from matplotlib.colors import LogNorm
from matplotlib.ticker import AutoMinorLocator
import numpy as np

rc('text', usetex=True)
rc('font', family='sans-serif')
if mpl_version.startswith('1.5'):
    fontProperties = {}
else:
    fontProperties = {'family':'sans-serif','sans-serif':['Helvetica']}
params = {'text.latex.preamble' : [r'\usepackage{amsmath}']}
plt.rcParams.update(params)
os.environ['PATH'] = os.environ['PATH']+':/usr/texbin'+':/Library/TeX/texbin'  # LaTeX support
## ------------------------------ ##

from hepPlotter import HepPlotter
import hepPlotterTools as hpt
import hepPlotterLabels as hpl



class HepPlotterSystematics(object):
    """Class for handling systematic uncertainties to put in plots"""
    def __init__(self):
        """Initialize class for each sample you want systematics"""
        self.sampleName  = ''
        self.variable    = ''
        self.outpath     = "./"
        self.binning     = 10
        self.rebin       = 1
        self.x_labels    = hpl.text_dicts()['variables']
        self.plotSystematics = True

        return



    def initialize(self,nominalHistogram,nominalWeights=None):
        """Setup some initial variables"""
        self.total    = None           # hold the total systematic uncertainty
        self.systData = OrderedDict()  # hold data for individual systematics
        if isinstance(nominalHistogram,ROOT.TH1):
            self.systData['nominal'] = hpt.hist2list(nominalHistogram,name="nominal")
        else:
            self.systData['nominal'] = hpt.data2list(nominalHistogram,bins=self.binning,
                                                     weights=nominalWeights)

        return



    def Add(self,data,weights=None,name=''):
        """
        Turn data into a numpy array to combine and plot systematic uncertainties.

        @param data        histogram (also support list/array of values) to plot
        @param weights     weights for each event for making histogram
        @param name        name of systematic (JES,JER,etc.)
        """
        if not name:
            name = data.GetName()

        if isinstance(data,ROOT.TH1):
            self.systData[name] = hpt.hist2list(data,name=name)
        else:
            self.systData[name] = hpt.data2list(data,bins=self.binning,weights=weights)

        return



    def execute(self,root_file=None,systematic="",histogram=None):
        """
        Execute the calculation of systematic uncertainties.
        This is only setup for histograms at the moment -- can be extended in the future

        @param root_file    ROOT file for accessing histograms (don't like doing this,
                             prefer to pass the histogram directly)
        @param systematic   Name of systematic histogram to access from root file
                            *Modeling uncertainties / XSection / Theory may be in 
                             different root files than the detector uncertainties*
                            Comma separated
        @param histogram    ROOT histogram
        """
        h_nominal = self.systData['nominal']['data']
        oneSided  = False

        if type(systematic)==str:
            systs = systematic.rstrip('\n').split(",") # if no comma, this still returns a 1 item list
        else:
            systs = systematic

        # If the ROOT file is None, assume histograms were passed to the function
        if root_file is None:
            # pass multiple histograms (down and up) at once with list
            if type(histogram)==list:
                self.Add(histogram[0],name=systs[0])
                if len(histogram)>1:
                    self.Add(histogram[1],name=systs[1])
                    oneSided = False
                else:
                    h_dn = self.cloneDummyHistogram(histogram[0])
                    self.Add(h_dn,name=systs[0]+'_1sided')        # add dummy data to storage
                    systs.append( systs[0]+'_1sided' )
                    oneSided = True
            # pass single histogram (one-sided systematic)
            else:
                self.Add(histogram,name=systs[0])
                h_dn = self.cloneDummyHistogram(histogram)
                self.Add(h_dn,name=systs[0]+'_1sided')
                systs.append( systs[0]+'_1sided' )
                oneSided = True
        # Get histograms from the ROOT file by name
        else:
            if len(systs)>1:
                self.Add( getattr(root_file,up),name=systs[0] )
                self.Add( getattr(root_file,down),name=systs[1] )
                oneSided = False
            else:
                self.Add( getattr(root_file,up),name=systs[0])
                h_dn = self.cloneDummyHistogram( getattr(root_file,up) )
                self.Add(h_dn,name=systs[0]+'_1sided')
                systs.append( systs[0]+'_1sided' )
                oneSided = True


        h_up_diff   = np.absolute(self.systData[systs[0]]['data'] - h_nominal)
        h_dn_diff   = np.absolute(self.systData[systs[1]]['data'] - h_nominal)
        symmetrized = ( (h_up_diff + h_dn_diff)*0.5 ) # symmetrize difference with nominal


        # Add uncertainties in quadrature
        if self.total is None:
            self.total = symmetrized**2
        else:
            self.total += symmetrized**2    # add uncertainties in quadrature


        # Plot single systematic versus nominal
        if self.plotSystematics:
            self.drawSyst(name=systs,symmetrized=symmetrized,one_sided=oneSided)

        return


    def getTotalSystematicUncertainty(self):
        """Return the total systematic uncertainty"""
        return np.sqrt(self.total)


    def drawSyst(self,name=[],symmetrized=None,one_sided=False):
        """
        Draw single systematic with nominal
        
        @param name         name(s) for histogram
        @param symmetrized  Values from symmetrized uncertainties
        @param one_sided    Boolean for one sided systematic or not
        """
        if name[0].endswith("up"):
            systname = name[0][:-2].replace("_","-")
        elif name[0].endswith("down"):
            systname = name[0][:-4].replace("_","-")

        systname = systname.split("xleptonicT-mmerged-boostedcomb-")[1]

        h_nominal = self.systData['nominal']['data']   # data (histogram bins values)
        b_nominal = self.systData['nominal']['center'] # dummy values to get binning right

        hist = HepPlotter("histogram",1)

        hist.ratio_plot = True       # plot a ratio of things [Data/MC]
        hist.ratio_type = "ratio"    # "ratio"
        hist.stacked    = False      # stack plots
        hist.rebin      = self.rebin
        hist.logplot    = False      # plot on log scale
        hist.x_label    = self.x_labels[self.variable]['label']
        hist.y_label    = "Events"
        hist.extra_text = systname+'\n '+self.sampleName
        hist.binning    = self.systData['nominal']['bins']
        hist.numLegendColumns = 1
        hist.y_ratio_label    = "Syst/Nom"
        hist.lumi             = '14.7'      # in /fb
        hist.format           = 'png'       # file format for saving image
        hist.saveAs           = self.outpath+"h_syst_"+self.sampleName+"_"+systname # save figure with unique name
        hist.CMSlabel       = 'top left'  # 'top left', 'top right'; hack code for something else
        hist.CMSlabelStatus = 'Simulation Internal'  # ('Simulation')+'Internal' || 'Preliminary' 

        hist.initialize()

        ## Regular uncertainties
        up     = self.systData[name[0]]['center']
        upData = self.systData[name[0]]['data']
        hist.Add(up,weights=upData,name=systname+" UP", label="UP",linecolor='r',color='r',
                 linestyle='dotted',draw='step',ratio_num=True,ratio_den=False,ratio_partner="nominal")
        if not one_sided:
            down     = self.systData[name[1]]['center']
            downData = self.systData[name[1]]['data']
            hist.Add(down,weights=downData,name=systname+" DOWN", label="DOWN",linecolor='b',color='b',
                     linestyle='dotted',draw='step',ratio_num=True,ratio_den=False,ratio_partner="nominal")

        ## Symmetrized uncertainties
        if symmetrized is not None:
            # - same binning as 'up' systematic
            hist.Add(up,weights=h_nominal+symmetrized,name=systname+" UP Symm.",
                     label="UP Symm.",linecolor='r',linestyle='solid',draw='step',color='r',
                     ratio_num=True,ratio_den=False,ratio_partner="nominal")
            hist.Add(up,weights=h_nominal-symmetrized,name=systname+" DOWN Symm.",
                     label="DOWN Symm.",linecolor='b',linestyle='solid',draw='step',color='b',
                     ratio_num=True,ratio_den=False,ratio_partner="nominal")

        ## nominal
        uncertainty_hists = [systname+" UP",systname+" DOWN",systname+" UP Symm.",systname+" DOWN Symm."]
        hist.Add(b_nominal,weights=h_nominal,name="nominal",label="nominal",linecolor='k',draw='step',
                 linestyle='solid',ratio_num=False,ratio_den=True,ratio_partner=uncertainty_hists)

        p = hist.execute() # can do something with p, if needed
        hist.savefig()     # save and close the figure

        return


    def cloneDummyHistogram(self,rHistogram):
        """Clone a histogram and set content/error to 0 -- for 1-sided systematics"""
        h_dummy = rHistogram.Clone()
        for bin in xrange(h_dummy.GetNbinsX()):
            h_dummy.SetBinContent(bin+1,0.0)
            h_dummy.SetBinError(bin+1,0.0)

        return h_dummy


### THE END ###
