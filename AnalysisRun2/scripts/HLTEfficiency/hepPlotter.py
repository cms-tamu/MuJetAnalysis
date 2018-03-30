"""
Created:         6 April     2016
Last Updated:    5 November  2016

Dan Marley
daniel.edison.marley@cernSPAMNOT.ch
University of Michigan, Ann Arbor, MI 48109

Bennett Magy
bmagy@umichSPAMNOT.edu
University of Michigan, Ann Arbor, MI 48109
-----
Class to make a simple instance each time we want some basic plots!

This does not include an interface to load/access data.
Here we just plot the data we're given.
See "python/runHistogram.py" and "python/runEfficiency.py" as an example setup script.

template for making histograms or efficiency curves
"""
import os
import sys
import ROOT
from math import fabs
from copy import deepcopy
from collections import OrderedDict
os.environ['PATH'] = os.environ['PATH']+':/usr/texbin'+':/Library/TeX/texbin' # LaTeX support

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
params = {'text.latex.preamble' : [r'\usepackage{amsmath}']}
plt.rcParams.update(params)

if mpl_version.startswith('1.5'):
    fontProperties = {}
else:
    fontProperties = {'family':'sans-serif','sans-serif':['Helvetica']}
    import colormaps as cmaps
    plt.register_cmap(name='viridis', cmap=cmaps.viridis)
    plt.register_cmap(name='magma',   cmap=cmaps.magma)
    plt.register_cmap(name='inferno', cmap=cmaps.inferno)
    plt.register_cmap(name='plasma',  cmap=cmaps.plasma)
## ------------------------------ ##
import hepPlotterTools as hpt
from hepPlotterTools import PlotText,Text




class HepPlotter(object):
    def __init__(self,typeOfPlot,dimensions):
        """
        @param typeOfPlot    Set the kind of plot: histogram or efficiency
        """
        if not isinstance(dimensions,(int,long)):
            print " You have specified a dimension of non-integer type."
            print " This is not supported. "
            print " For the hepPlotter class, choose either 1 or 2 dimenions."
            sys.exit(1)

        # customizable options
        self.typeOfPlot = typeOfPlot.lower()  # histogram or efficiency plot (ignore capitals)
        self.dimensions = dimensions  # number of dimensions in histogram
        self.ratio_plot = False       # plot a ratio of things
        self.ratio_type = "ratio"     # "ratio","significance"
        self.stacked    = False       # stack plots (1D only)
        self.binning    = 20          # integer for number of bins, or list for non-uniform bins
        self.rebin      = 1           # rebin root histograms
        self.label_size = 20          #
        self.normed     = False       # normalize histogram
        self.logplot    = False       # plot on log scale
        self.underflow  = False       # plot the underflow
        self.overflow   = False       # plot the overflow
        self.colormap   = None        # 2D plot colormap
        self.colorbar_title = None
        self.xlim       = None        # tuple for (xmin,xmax)
        self.ymaxScale  = None        # scale y-axis
        self.bin_yields = False       # print bin yields inside histogram
        self.bin_yields_color = None  # array of text colors for each bin
        self.drawEffDist    = False    # draw the physics distribution for efficiency (jet_pt for jet trigger)
        self.x_label        = 'x'
        self.y_label        = 'y'
        self.y_ratio_label  = 'y ratio'
        self.extra_text     = PlotText()
        self.minor_ticks    = True
        self.lumi           = '37'
        self.plotLUMI       = True
        self.CMSlabel       = 'top left'     # 'top left', 'top right' & 'outer' for 2D
        self.CMSlabelStatus = 'Internal'  # ('Simulation')+'Internal' || 'Preliminary'
        self.format         = 'png'          # file format for saving image
        self.saveDir        = './'
        self.saveAs         = "plot_{0}d_{1}".format(self.dimensions,self.CMSlabelStatus) # save figure with name
        self.numLegendColumns = 2
        self.legendLoc        = 1
        self.drawStatUncertainty   = False
        self.drawUncertaintyTopFig = False  # draw uncertainties in the top frame
        self.uncertaintyHistType   = 'step'
        self.x_relative_size = 10
        self.y_relative_size = 6

        return

    def initialize(self):
        """Initialize some things."""
        self.ax1          = None
        self.ax2          = None
        self.kwargs       = {}
        self.names        = []
        self.errorbarplot = []
        self.effData      = []
        self.hists2plot   = OrderedDict()
        self.yerrors      = OrderedDict()
        self.colors       = OrderedDict()
        self.linecolors   = OrderedDict()
        self.linestyles   = OrderedDict()
        self.linewidths   = OrderedDict()
        self.draw_types   = OrderedDict()
        self.labels       = OrderedDict()
        self.weights      = OrderedDict()
        self.histograms   = OrderedDict()
        self.ratio_den    = OrderedDict()
        self.ratio_num    = OrderedDict()
        self.ratio_partner = OrderedDict()
        self.uncertainties = OrderedDict()

        # Arguments for plotting uncertainties [color = kGreen-8 , alpha=0.5]
        self.p_hatch_args = {'hatch':'','color':'#99cc99',\
                             'edgecolor':'none','alpha':0.5}
        self.yMaxScaleValues = {"histogram":1.3,"efficiency":1.1}

        # colormap setup
        linear_cmap_choice  = np.random.choice(["Reds","Blues","Greens"])
        default_cmap_choice = np.random.choice(["viridis","magma","inferno","plasma"])

        colormaps = {'diverge':"bwr",
                     'linear':linear_cmap_choice,
                     'default':default_cmap_choice}



        ## 2D plot
        if self.dimensions==2:
            if colormaps.get( self.colormap ):
                ## 2D plot with colormap in the dictionary above ('diverge','linear','default')
                if self.colormap=="default" and not mpl_version.startswith("1.5"):
                    ## if the colormap is 'default' but mpl_version < 1.5, need to use
                    ## cmaps to load the correct map
                    plt.set_cmap( getattr(cmaps,colormaps["default"]) )
                    self.colormap = colormaps["default"]
                else:
                    ## can get the colormap from matplotlib
                    self.colormap = getattr( plt.cm,colormaps[self.colormap] )
            elif self.colormap is not None:
                ## custom colormap choices
                if self.colormap in ["viridis","magma","inferno","plasma"] and not mpl_version.startswith("1.5"):
                    plt.set_cmap( getattr(cmaps,self.colormap) ) # chosen a colormap not supported by matplotlib
                else:
                    try:
                        self.colormap = getattr(plt.cm,self.colormap)
                    except AttributeError:
                        print " WARNING : You have chosen a colormap that is not supported "
                        print "           by CyMiniAna or matplotlib.  Choosing the colormap "
                        print "           based on data structure "
                        self.colormap = None

        # draw minor ticks
        self.x1minorLocator = AutoMinorLocator()
        self.y1minorLocator = AutoMinorLocator()
        self.x2minorLocator = AutoMinorLocator()
        self.y2minorLocator = AutoMinorLocator()

        return


    def Add(self,data,name='',weights=None,linecolor='k',linestyle='solid',color='k',
                 linewidth=2,draw='step',label='',ratio_den=False,ratio_num=False,
                 ratio_partner=None,yerr=None,**kwargs):
        """
        Add histogram data for this figure.

        args   = data (1D) || x_data,y_data (2D)        array or ROOT hist
        kwargs = bins (int or list/np.array):           default = 10
                 weights (None or list/np.array):       default = None
                 uncertainties (None or list/np.array): default = None
                 linecolor 'black',etc:                 default = None
                 fillcolor 'blue',etc.
                 draw   step,stepfilled,errorbar
                 label "ttbar" or something
        """
        self.names.append(name)

        normed = False
        if 'normed' in kwargs.keys():
            normed = kwargs['normed']

        if self.typeOfPlot=="histogram" and isinstance(data,ROOT.TH1):
            if self.dimensions==1:
                self.hists2plot[name] = hpt.hist2list(data,name=name,
                                                      reBin=self.rebin,normed=normed)
            else:
                self.hists2plot[name] = hpt.hist2list2D(data,name=name,
                                                        reBin=self.rebin,normed=normed)
        elif self.typeOfPlot=="efficiency" and isinstance(data,ROOT.TEfficiency):
            self.hists2plot[name] = hpt.TEfficiency2list(data)
        elif self.typeOfPlot=="efficiency" and isinstance(data,ROOT.TH1):
            total_data = data.Integral()
            data.Scale(1./total_data) # normalize distribution to show on plot
            self.hists2plot[name] = hpt.hist2list(data,name=name,reBin=self.rebin,normed=normed)
            self.drawEffDist = True
            self.effData.append(name)
        else:
            if self.dimensions==1:
                self.hists2plot[name] = hpt.data2list(data,weights=weights,normed=normed,
                                                      binning=self.binning)
                if yerr is not None: self.hists2plot[name]['error'] = yerr
            else:
                self.hists2plot[name] = hpt.data2list2D(data,weights=weights,normed=normed,
                                                        binning=self.binning)


        self.kwargs[name]     = kwargs      # pass normal matplotlib arguments
        self.colors[name]     = color
        self.yerrors[name]    = yerr        # method for drawing y-errors
        self.linecolors[name] = linecolor
        self.linestyles[name] = linestyle
        self.linewidths[name] = linewidth
        self.labels[name]     = label
        self.weights[name]    = weights
        self.ratio_den[name]  = ratio_den   # denominator in ratio
        self.ratio_num[name]  = ratio_num   # numerator in ratio
        self.ratio_partner[name] = ratio_partner
        self.draw_types[name] = draw
        if draw=='errorbar':
            self.errorbarplot.append(name)
            if linestyle=='solid':
                self.linestyles[name] = 'o'        # default setting for errorbar
            else:
                self.linestyles[name] = linestyle  # user custom option

        return


    def execute(self):
        """
        Execute the plot.  Pass arguments concerning the data in the following way:

        return the Figure object to the user (they can edit it if they please)
        """
        if self.dimensions == 1:
            this_figure = self.plot_hist1d()
        else:
            this_figure = self.plot_hist2d()

        return this_figure



    def plot_hist1d(self):
        """Plot a 1D histogram."""
        self.ratio_ylims  = {}
        self.ratio_yticks = {}
        if self.ratio_plot:
            fig = plt.figure()
            gs  = matplotlib.gridspec.GridSpec(2,1,height_ratios=[3,1],hspace=0.0)
            self.ax1 = fig.add_subplot(gs[0])
            self.ax2 = fig.add_subplot(gs[1],sharex=self.ax1)
            plt.setp(self.ax1.get_xticklabels(),visible=False)

            self.ratio_ylims = {'ymin':{'ratio':0.5,'significance':0.0},
                                'ymax':{'ratio':1.2,'significance':None}}
            self.ratio_yticks = {'ratio':np.asarray([0.6,1.0,1.2]),
                                 'significance':self.ax2.get_yticks()[::2]}

        else:
            fig,self.ax1 = plt.subplots(figsize=(self.x_relative_size,self.y_relative_size))


        if self.typeOfPlot=="efficiency":
            # draw horizontal lines to guide the eye
            self.ax1.axhline(y=0.25,color='lightgray',ls='--',lw=1,zorder=0)
            self.ax1.axhline(y=0.50,color='lightgray',ls='--',lw=1,zorder=0)
            self.ax1.axhline(y=0.75,color='lightgray',ls='--',lw=1,zorder=0)
            self.ax1.axhline(y=1.00,color='lightgray',ls='--',lw=1,zorder=0)
            self.yTwinMinorLocator = AutoMinorLocator()

            ## -- Twin axis :: Efficiency only
            if self.drawEffDist:
                axTwin = self.ax1.twinx()
                if self.ymaxScale is None:
                    self.ymaxScale = self.yMaxScaleValues['efficiency']
                ## Get the histogram
                for effData in self.effData:
                    h_effDist = self.hists2plot[effData]
                    n,b,p = axTwin.hist(h_effDist['center'],bins=h_effDist['bins'],
                                        weights=h_effDist['data'],histtype='step',
                                        color=self.colors[effData],lw=self.linewidths[effData],
                                        label=self.labels[effData],**self.kwargs[effData])
                axTwin.yaxis.set_tick_params(which='major', length=8)
                axTwin.set_ylabel("",fontsize=0,ha='right',va='top')
                axTwin.set_ylim(ymin=0.0,ymax=self.ymaxScale*max(n))
                # hide y-ticks
                axTwin.set_yticks( np.linspace(axTwin.get_yticks()[0],axTwin.get_yticks()[-1],len(self.ax1.get_yticks())) )
                axTwin.set_yticklabels([])
                self.ax1.set_zorder(axTwin.get_zorder()+1) # put ax in front of axTwin
                self.ax1.patch.set_visible(False)          # hide the 'canvas'
            ## -- End Twin axis :: Efficiency only


        ## -- Loop over samples for errorbar plot
        binning    = None
        totpred    = [0]
        bottomEdge = None    # for stacking plots (use this instead of the 'stack' argument
                             # so that all plots can be made in one for-loop
        for n,name in enumerate(self.names):
            if name in self.effData: continue

            data       = self.hists2plot[name]['data']
            error      = self.hists2plot[name]['error']
            bin_center = self.hists2plot[name]['center']
            bin_width  = self.hists2plot[name]['width']
            binning    = self.hists2plot[name]['bins']

            if name in self.errorbarplot:
                data  = np.array([i if i else float('NaN') for i in data])  # hide empty values
                if not self.kwargs[name].get("mec"):
                    self.kwargs[name]["mec"] = self.linecolors[name]
                if not self.kwargs[name].get("mfc"):
                    self.kwargs[name]["mfc"] = self.colors[name]
                if not self.kwargs[name].get("capsize"):
                    self.kwargs[name]["capsize"] = 0

                # Make the errorbar plot
                p,c,b = self.ax1.errorbar(bin_center,data,yerr=error,fmt=self.linestyles[name],
                                     color=self.colors[name],label=self.labels[name],
                                     zorder=100,**self.kwargs[name])
                # record data for later
                self.histograms[name]    = data
                self.uncertainties[name] = np.array(error)
            else:
                # Hack for changing legend for step histograms (line instead of rectangle)
                if self.draw_types[name]=='step':
                    this_label      = None
                    histStep_pseudo = self.ax1.plot([],[],color=self.linecolors[name],
                                               lw=self.linewidths[name],ls=self.linestyles[name],
                                               label=self.labels[name])
                else:
                    this_label = self.labels[name]

                # Make the histogram
                data,b,p = self.ax1.hist(bin_center,bins=binning,weights=data,lw=self.linewidths[name],
                                 histtype=self.draw_types[name],bottom=bottomEdge,
                                 ls=self.linestyles[name],log=self.logplot,color=self.colors[name],
                                 edgecolor=self.linecolors[name],label=this_label,
                                 normed=self.normed,**self.kwargs[name])
                if self.stacked:
                    if bottomEdge is None:
                        bottomEdge  = data
                    else:
                        bottomEdge += data

                # record data for later
                self.histograms[name]    = data
                self.uncertainties[name] = np.array(error)

                # draw uncertainties -- use GetBinError() or just np.sqrt()
                # only using this for histograms because errorbar has a yerr option
                if self.drawStatUncertainty and self.drawUncertaintyTopFig:
                    self.plotUncertainty(self.ax1,pltname=name,normalize=False)

            # record tallest point for scaling plot
            if max(data) > max(totpred):
                totpred = data
        ## End loop over data

        self.binning = np.array(binning) # re-set binning for this instance of hepPlotter

        # y-axis
        if self.ymaxScale is None:
            self.ymaxScale = self.yMaxScaleValues[self.typeOfPlot]
        self.ax1.set_ylim(0.,self.ymaxScale*self.ax1.get_ylim()[1])
        self.ax1.set_yticks(self.ax1.get_yticks()[1:])
        self.setYAxis(self.ax1)

        # x-axis
        if self.xlim is not None:
            plt.xlim(self.xlim)
        if self.ratio_plot:
            self.drawRatio()
            x_axis = self.ax2
        else:
            x_axis = self.ax1
        print" setting x axis"
        self.setXAxis(x_axis)


        # axis ticks
        self.setAxisTickMarks()
        plt.tick_params(which='minor', length=4) # ticks

        # CMS label
        if self.CMSlabel is not None:
            self.text_labels()

        # Legend
        handles, labels  = self.ax1.get_legend_handles_labels() # for re-ordering, if needed
        leg = self.ax1.legend(handles,labels,numpoints=1,fontsize=self.label_size-2,
                              ncol=self.numLegendColumns,columnspacing=0.3,loc=self.legendLoc)
        leg.draw_frame(False)

        return fig



    def plot_hist2d(self):
        """Plot a 2D histogram."""
        fig,self.ax1 = plt.subplots()

        h_data       = None
        x_bin_center = None
        y_bin_center = None
        binns_x      = None
        binns_y      = None

        for key in self.names:
            if key in self.effData: continue

            h_data = np.array(self.hists2plot[key]['data'])
            x_bin_center = self.hists2plot[key]['center']['x']
            y_bin_center = self.hists2plot[key]['center']['y']
            binns_x = self.hists2plot[key]['bins']['x']
            binns_y = self.hists2plot[key]['bins']['y']


        if self.colormap is None:
            hh,bb = np.histogram2d( x_bin_center,y_bin_center,bins=[binns_x,binns_y],
                                  weights=h_data )
            self.colormap = hpt.getDataStructure( hh )

        if self.logplot:  norm2d = LogNorm()
        else:             norm2d = None

        # Make the plot
        plt.hist2d(x_bin_center,y_bin_center,bins=[binns_x,binns_y],
                   weights=h_data,cmap=self.colormap,norm=norm2d)

        # Plot bin values, if requested
        if self.bin_yields:
            self.plotBinYields()

        # Configure the labels
        self.setYAxis(self.ax1)
        self.setXAxis(self.ax1)
        self.setAxisTickMarks()

        # Configure the colorbar
        cbar = plt.colorbar()
        if self.logplot:
            cbar.ax.set_yticklabels( [r"10$^{\text{%s}}$"%(hpt.extract(i.get_text())) for i in cbar.ax.get_yticklabels()] )
        else:
            cbar.ax.set_yticklabels( [r"$\text{%s}$"%(i.get_text().replace(r'$','')) for i in cbar.ax.get_yticklabels()],fontProperties )
        if self.colorbar_title != None:
            cbar.ax.set_ylabel(self.colorbar_title)

        # CMS label
        if self.CMSlabel is not None:
            self.text_labels()

        return fig



    def drawRatio(self):
        """Ratio plot in frame under main plot
           (assume this -- could extend functionality and make 2D version)
           Can handle plotting multiple ratios with one quantity
           (e.g., up/down systs with nominal)
        """
        for i in self.names:
            num_hists       = []   # list of histograms for numerator of ratio
            num_hists_names = []   # names of histograms in numerator of ratio
            if self.ratio_den[ i ]:
                den_hist = np.array( self.histograms[ i ] )
                try:
                    num_hists.append( np.array(self.histograms[self.ratio_partner[i]]) )
                    num_hists_names.append( self.ratio_partner[i] )
                except TypeError: # unhashable type: 'list'
                    for j in self.ratio_partner[i]:
                        num_hists.append( np.array(self.histograms[j]) )
                        num_hists_names.append( j )
            else: # only look at the 'ratio_den' terms to prevent plotting ratio twice
                continue


            if self.ratio_type=='ratio':
                self.ax2.axhline(y=1,ls='--',c='k',zorder=1) # draw once


            for nh,num_hist in enumerate(num_hists):

                histName = num_hists_names[nh]

                if self.ratio_type=="ratio":
                    residual     = deepcopy( num_hist / den_hist )
                    residual_err = deepcopy( np.sqrt(num_hist) / den_hist )
                elif self.ratio_type == "significance":
                    residual     = deepcopy( num_hist / np.sqrt(den_hist) )
                    residual_err = [0 for _ in residual] # don't know how to estimate this
                else:
                    print " WARNING :: Un-specified method for ratio plot "
                    print "            Setting ratio equal to 1.0"
                    residual     = np.ones( len(num_hist) )
                    residual_err = [0 for _ in residual]

                # Obtain data points for drawing the ratio
                bin_center = self.hists2plot[histName]['center']
                bin_width  = self.hists2plot[histName]['width']

                if histName in self.errorbarplot:
                    if self.linestyles[histName]=='solid':
                        self.linestyles[histName] = 'o'
                    lcolor = self.linecolors[histName]
                    self.ax2.errorbar(bin_center,residual,xerr=bin_width,yerr=residual_err,
                                  capsize=0,fmt=self.linestyles[histName],
                                  mec=lcolor,mfc=lcolor,color=lcolor,zorder=100)
                else:
                    residual = np.array( [fabs(rr) if (not np.isnan(rr) and not np.isinf(rr)) else 0.0 for rr in residual] )
                    self.ax2.hist(bin_center,bins=self.binning,weights=residual,
                                  edgecolor=self.linecolors[histName],lw=2,
                                  color=self.colors[histName],ls=self.linestyles[histName],
                                  histtype='step',zorder=100)

            ## Simulation Uncertainties
            if self.drawStatUncertainty:
                self.plotUncertainty(self.ax2,pltname=i,normalize=True)

        ## Set the axis properties of the ratio y-axis
        self.ax2.set_ylim(ymin=self.ratio_ylims['ymin'][self.ratio_type],
                          ymax=self.ratio_ylims['ymax'][self.ratio_type])
        self.ratio_yticks['significance']=self.ax2.get_yticks()[::2]

        self.ax2.set_yticks(self.ax2.get_yticks()[::2])
        self.ax2.set_yticklabels(self.ax2.get_yticks(),fontProperties,fontsize=self.label_size)
        self.ax2.set_ylabel(self.y_ratio_label,fontsize=self.label_size,ha='center',va='bottom')

        return

    def plotUncertainty(self,axis,pltname='',normalize=False):
        """
        Plot uncertainties

        @param axis
        @param name        Name of sample to plot (access data from global dictionaries)
        @param normalize   draw on ratio plot (divide by total prediction)
        """
        if self.yerrors[pltname] is None:
            return

        error   = self.uncertainties[pltname]
        nominal = self.histograms[pltname]

        # Draw errorbars that are rectangles for each bin
        if self.yerrors[pltname]=='rectangle':
            if normalize:
                resid_unc = {'up': list(((nominal+error)/nominal).repeat(2)),
                             'dn': list(((nominal-error)/nominal).repeat(2))}
            else:
                resid_unc = {'up': list((nominal+error).repeat(2)),
                             'dn': list((nominal-error).repeat(2))}

            fill_between_bins = self.binning   ## for plotting hatch uncertainty
            fill_between_bins = [self.binning[0]]+list(fill_between_bins[1:-1].repeat(2))+[self.binning[-1]]

            axis.fill_between(fill_between_bins,resid_unc['dn'],resid_unc['up'],
                              zorder=10,color=self.colors[pltname],**self.kwargs[pltname])
        # Draw vertical line for errors
        elif self.yerrors[pltname]=='line':
            if normalize:
                resid_unc = {'up': list(((nominal+error)/nominal)),
                             'dn': list(((nominal-error)/nominal))}
            else:
                resid_unc = {'up': list((nominal+error)),
                             'dn': list((nominal-error))}

            error      = [resid_unc['dn'],resid_unc['up']]
            data       = [1. for _ in nominal] if normalize else nominal
            bin_center = 0.5*(self.binning[:-1]+self.binning[1:])
            p,c,b = self.ax1.errorbar(bin_center,data,yerr=error,
                                     fmt=self.linestyles[pltname],color=self.colors[pltname],
                                     zorder=100,**self.kwargs[pltname])

        return



    def setYAxis(self,y_axis):
        """Draw labels for y-axis -- simple so that users can specify limits/range
           of their y-axis and just pass the axis ticks here"""
        y_axis.set_ylabel(self.y_label,fontsize=self.label_size,ha='right',va='bottom',position=(0,1))
        axis_yticks = y_axis.get_yticks()

        if self.logplot:
            logTickLabels = [r"10$^{\text{%s}}$"%(int(np.log10(i)) ) for i in axis_yticks]
            y_axis.set_yticklabels(logTickLabels,fontProperties,fontsize=self.label_size)
        else:
            if len(set(axis_yticks.astype(int)))==len(axis_yticks):
                y_axis.set_yticklabels(axis_yticks.astype(int),fontProperties,fontsize=self.label_size)
            else:
                y_axis.set_yticklabels(axis_yticks[0:-1],fontProperties,fontsize=self.label_size)

        return



    def setXAxis(self,x_axis):
        """Draw labels for x-axis"""
        x_axis.set_xlabel(self.x_label,fontsize=self.label_size,ha='right',va='top',position=(1,0))
        x_axis_xticks = x_axis.get_xticks()
        if len(set(x_axis_xticks.astype(int)))==len(x_axis_xticks):
            x_axis.set_xticklabels(x_axis_xticks.astype(int),fontProperties,fontsize=self.label_size)
        else:
            x_axis.set_xticklabels(x_axis_xticks,fontProperties,fontsize=self.label_size)

        return



    def setAxisTickMarks(self):
        """Setup axis ticks"""
        self.ax1.yaxis.set_tick_params(which='major', length=8)
        self.ax1.xaxis.set_tick_params(which='major', length=8)
        if self.minor_ticks:
            if not self.logplot:
                self.ax1.yaxis.set_minor_locator(self.y1minorLocator) # causes tick number error on logplot
            self.ax1.xaxis.set_minor_locator(self.x1minorLocator)
            if self.ratio_plot:
                self.ax2.xaxis.set_minor_locator(self.x2minorLocator)
                self.ax2.yaxis.set_minor_locator(self.y2minorLocator)

        return


    def text_labels(self):
        """Labels for CMS plots"""
        text_args = {'fontsize':18,'ha':'left','va':'top','transform':self.ax1.transAxes}

        if self.dimensions==2 and self.CMSlabel!='outer':
            print " "
            print " WARNING :: You have chosen a label position "
            print "            not considered for 2D plots. "
            print "            Please consider changing the "
            print "            parameter 'CMSlabel' to 'outer'."
            
        coords = {'top left':{'x':[0.0]*3,'y':[1.05,0.90,0.83]},\
                  'top right':{'x':[1.0]*3,'y':[1.05,0.90,0.83]},\
                  'outer':{'x':[0.0,1,1],'y':[1.01,1.01,1.01]}}
        text = coords[self.CMSlabel]

        energy = r"13 TeV"
        lumi   = r"%s fb$^{\text{-1}}$"%(self.lumi)

        if self.CMSlabel == 'top right':
            text_args['ha'] = 'right'
        if self.dimensions==2 or self.CMSlabel=='outer':
            text_args['va'] = 'bottom' # change alignment for 2d labels

        ## CMS Label
        self.ax1.text(text['x'][0],text['y'][0],r"\textbf{CMS} "+ r"{\Large \textit{%s}}"%(self.CMSlabelStatus),**text_args)

        ## Luminosity & Energy
        if self.dimensions==2 or self.CMSlabel=='outer':
            text_args['ha'] = 'right' # change alignment for energy label
        if self.dimensions==2:
            text_args['ha'] = 'left' # change alignment for energy label

        if self.plotLUMI:
            self.ax1.text(text['x'][1],text['y'][1],lumi + " (" + energy + ")",**text_args)
        else:
            self.ax1.text(text['x'][1],text['y'][1],energy,**text_args)

        ## Extra text
        if len( self.extra_text.texts )>0:

            # loop over text items and draw them on plot
            for txtItem in self.extra_text.texts:
                if txtItem.transform is None:
                    txtItem.transform = self.ax1.transAxes
                self.ax1.text( txtItem.coords[0],txtItem.coords[1],txtItem.text,
                               fontsize=txtItem.fontsize,ha=txtItem.ha,va=txtItem.va,
                               color=txtItem.color,transform=txtItem.transform  )

        return



    def plotBinYields(self):
        """Print bin values inside the plots for each bin."""
        h_data       = None
        x_bin_center = None
        y_bin_center = None
        binns_x      = None
        binns_y      = None

        for key in self.names:
            if key in self.effData: continue

            h_data = np.array(self.hists2plot[key]['data'])
            x_bin_center = self.hists2plot[key]['center']['x']
            y_bin_center = self.hists2plot[key]['center']['y']
            binns_x = self.hists2plot[key]['bins']['x']
            binns_y = self.hists2plot[key]['bins']['y']

        N = len(x_bin_center) # number of bins (a flattened list for both TH1/TH2)

        text_colors = self.bin_yields_color
        if text_colors == None:
            text_colors = ['0.00' for i in range(N)]

        for i in range(N):
            self.ax1.text(x_bin_center[i],
                            y_bin_center[i],
                            "{0:.1f}".format(h_data[i]),
                            horizontalalignment='center',
                            verticalalignment='center',
                            color=text_colors[i])



    def savefig(self):
        """Save the figure"""
        plt.savefig(self.saveDir + self.saveAs+'.'+self.format,format=self.format,dpi=300,bbox_inches='tight')
        plt.close()

        return



## THE END


