'''
Created:       31 August    2016
Last Updated:  15 June      2017

Dan Marley
daniel.edison.marley@cernSPAMNOT.ch
Texas A&M University

Bennett Magy
bmagy@umichSPAMNOT.edu
University of Michigan, Ann Arbor, MI 48109 (former student)
-----
Much of the code was inherited from a plotting packaged developed by Bennett.
As it has merged with CyMiniAnaAC, other features have been added to improve modularity.
'''
import os
import sys
import ROOT
from math import log10
from copy import deepcopy
from collections import OrderedDict

os.environ['PATH'] = os.environ['PATH']+':/usr/texbin'+':/Library/TeX/texbin'  # LaTeX support

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
## ------------------------------ ##
from hepPlotter import HepPlotter
import hepPlotterTools as hpt
import hepPlotterLabels as hpl



class HepPlotterDataMC(HepPlotter):
    def __init__(self):
        """
        @param typeOfPlot    Set the kind of plot: histogram or efficiency
        """
        HepPlotter.__init__(self,"histogram",1)

        self.stackSignal = False
        self.plotLUMI    = True
        self.blind       = False
        self.ymaxScale   = 1.3
        self.drawStatUncertainty = True      # draw stat uncertainty separately
        self.drawSystUncertainty = False     # draw syst uncertainty separately
        self.drawStatSystUncertainty = False # draw stat+syst uncertainty
        self.drawTotalUncertainty    = False # draw a total uncertainty (that you can pass into the plotting)
        self.totaluncertainty = None         # total uncertainty to plot (pass this in directly as an array)
        self.statColor     = '#66b266'  # '#336633' <- use alpha=0.5 with this
        self.systColor     = '#99cc99'  # '#4d994d' <- use alpha=0.5 with this
        self.statSystColor = '#cce5cc'  # '#99cc99' <- use alpha=0.5 with this (=#c1e1c0)
        self.legendLoc     = 1

        return



    def initialize(self):
        """Initialize some things."""
        HepPlotter.initialize(self)
        self.sampleTypes = {'background':[],
                            'signal':[],
                            'data':[],
                            'systematic':[]}  # systematic is for plotting single systematic uncertainties
        self.labels      = hpl.text_dicts()
        self.systematics = OrderedDict()

        self.uncertainty_handles = []
        self.uncertainty_labels  = []

        return



    def Add(self,data,name='',weights=None,sampleType='background',file=None,systematics=None):
        """
        Add histogram data for this figure.

        @param data        histogram or list/array of values to plot
        @param name        name of sample ('ttbar','wjets',etc.)
        @param weights     weights (if any) for histogram
        @param sampleType  Kind of sample ('background','signal', or 'data')
        @param file        The root file of histograms to get systematic uncertainties
        @param systematics The total systematic uncertainty for a given sample 
                           (histogram or array of bin content from histogram)
        """
        self.names.append(name)

        if isinstance(data,ROOT.TH1):
            self.hists2plot[name] = hpt.hist2list(data,name=name,reBin=self.rebin)
        else:
            self.hists2plot[name] = hpt.data2list(data)

        self.weights[name]     = weights
        self.sampleTypes[sampleType].append( name )
        self.systematics[name] = systematics

        return


    def execute(self):
        """
        Execute the plot.  Pass arguments concerning the data in the following way:

        return the Figure object to the user (they can edit it if they please)
        """
        totpred = 0.0

        fig = plt.figure()
        gs  = matplotlib.gridspec.GridSpec(2,1,height_ratios=[3,1],hspace=0.0)
        self.ax1 = fig.add_subplot(gs[0])
        self.ax2 = fig.add_subplot(gs[1],sharex=self.ax1)
        plt.setp(self.ax1.get_xticklabels(),visible=False)

        ## -- Loop over samples for data plot [should only be one entry, but loop for protection]
        if not self.blind:
            totDataError=None
            for name in self.sampleTypes['data']:
                data  = self.hists2plot[name]['data']
                data  = np.asarray([i if i else float('NaN') for i in data])
                error = self.hists2plot[name]['error']
                binning    = self.hists2plot[name]['bins']
                bin_center = self.hists2plot[name]['center']
                bin_width  = self.hists2plot[name]['width']

                if totDataError is None:
                    totDataError  = np.square(error)
                else:
                    totDataError += np.square(error)

                p,c,b = self.ax1.errorbar(bin_center,data,yerr=error,capsize=0,
                                     fmt="o",mec="k",mfc="k",color="k",
                                     label=self.labels['samples'][name]['label'],zorder=100)

                self.histograms[name]    = data
                self.uncertainties[name] = np.sqrt(totDataError)
                totpred = max([i+j for i,j in zip(data,error)])


        ## -- Loop over samples for regular histograms -- ##

        ## -- Background -- ##
        weights     = []
        datas       = []
        labels      = []
        fillcolors  = []
        k_wargs     = {}
        totalErrors = None
        for name in self.sampleTypes['background']:
            weights.append(self.hists2plot[name]['data'])
            datas.append(self.hists2plot[name]['center'])
            binning = self.hists2plot[name]['bins']

            if totalErrors is None:
                totalErrors  = np.square(self.hists2plot[name]['error'])
            else:
                totalErrors += np.square(self.hists2plot[name]['error'])

            self.uncertainties[name] = self.hists2plot[name]['error']
            self.histograms[name]    = weights

            labels.append(self.labels['samples'][name]['label'])
            fillcolors.append(self.labels['samples'][name]['color'])

        totalBckg,b,p = self.ax1.hist(datas,bins=binning,
                                 weights=weights,histtype="stepfilled",
                                 edgecolor='k',ls="solid",color=fillcolors,
                                 label=labels,stacked=self.stacked,
                                 log=self.logplot,zorder=10)
        self.histograms["background"]    = totalBckg[-1]          # total background prediction
        self.uncertainties["background"] = np.sqrt( totalErrors ) # stat errors added in quadrature


        if max(totalBckg[-1]) > totpred:
            totpred = max(totalBckg[-1])


        ## -- Signal -- ##
        signal_colormap = plt.get_cmap(self.labels['samples']['signal']['color']) # map integer to color
        totalErrors = None
        for name in self.sampleTypes['signal']:
            weight  = self.hists2plot[name]['data']
            data    = self.hists2plot[name]['center']
            binning = self.hists2plot[name]['bins']
            if totalErrors is None:
                totalErrors  = np.square(self.hists2plot[name]['error'])
            else:
                totalErrors += np.square(self.hists2plot[name]['error'])

            # set the signal color
            if len(self.sampleTypes['signal'])>1:
                signal_color = signal_colormap(self.labels['samples'][name]['color'])
            else:
                signal_color = 'red'

            # stack the signal or just show it normalized
            if self.stackSignal:
                signalHistType = "stepfilled"
                bottomEdge     = self.histograms["background"]
                signal_label   = self.labels['samples'][name]['label']
            else:
                signalHistType = "step"
                bottomEdge     = 0.0
                signal_label   = None
                # draw the 'step' histogram as a line in the legend
                h_pseudo       = self.ax1.plot([],[],color=signal_color,lw=2,ls='solid',
                                            label=self.labels['samples'][name]['label'])

            signalPred,b,p = self.ax1.hist(data,bins=binning,
                        weights=weight,histtype=signalHistType,
                        lw=2,edgecolor=signal_color,color=signal_color,
                        label=signal_label,
                        stacked=self.stackSignal,bottom=bottomEdge,
                        log=self.logplot,zorder=11) # draw in front of background/behind data
            if max(signalPred) > totpred:
                totpred = signalPred
            self.histograms[name]    = signalPred
            self.uncertainties[name] = totalErrors



        ## -- Systematics -- ##
        ## Draw a systematic in the ratio plot to compare with total systematic
        for name in self.sampleTypes['systematic']:
            try:
                weight  = self.hists2plot[name]['data']
                data    = self.hists2plot[name]['center']
                binning = self.hists2plot[name]['bins']
            except TypeError:
                data,binning = np.histogram(self.hists2plot[name],self.binning,
                                                weights=self.weights[name])
                weight = self.weights[name]
                bin_center = 0.5*(binning[:-1]+binning[1:])
                bin_width  = 0.5*(binning[:-1]-binning[1:])

            if name.lower().endswith("up"):
                color = 'r'
            else:
                color = 'b'

            # Add to the legend in the top plot
            histStep_pseudo = self.ax1.plot([],[],color=color,lw=2,ls='solid',
                                            label=self.labels['samples'][name]['label'])
            # Draw in the bottom plot
            systHist,b,p = self.ax2.hist(data,bins=binning,weights=weight,histtype='step',
                                         lw=2,edgecolor=color,color=color,log=self.logplot,
                                         label=self.labels['samples'][name]['label'],
                                         stacked=False,zorder=10)

            # Add to the legend in the top plot
            self.uncertainty_handles.append(systHist)
            self.uncertainty_labels.append( self.labels['samples'][name]['label'] )

            self.histograms[name]    = systHist
            self.uncertainties[name] = 0


        self.binning = np.array(binning) # all binning should be the same in a Data/MC plot


        ## Residual plotting ##
        ratio_ylims  = {'ymin':0.5,'ymax':1.5}
        ratio_yticks = np.asarray([0.6,1.0,1.4])

        data_array   = np.array(self.histograms['data'])
        bckg_array   = np.array(totalBckg[-1])
        residual     = deepcopy( data_array / bckg_array )
        residual_err = deepcopy( np.sqrt(data_array) / bckg_array )

        ## Obtain data points for drawing the ratio
        try:
            bin_center = self.hists2plot["data"]["center"]
            bin_width  = self.hists2plot["data"]["width"]
        except TypeError:
            bin_center = 0.5*(self.binning[:-1]+self.binning[1:]) # midpoint in bins
            bin_width  = (self.binning[1:]-self.binning[:-1])*0.5 # bin widths

        self.ax2.errorbar(bin_center,residual,xerr=bin_width,yerr=residual_err,\
                     capsize=0,fmt="o",mec="k",mfc="k",color="k",zorder=100)


        ## -- Labels, legends, and text -- ##
        self.ax2.axhline(y=1.0,ls='--',c='k',zorder=50)

        ## Set the axis properties of the ratio y-axis
        self.ax2.set_ylim(ymin=ratio_ylims['ymin'],ymax=ratio_ylims['ymax'])
        self.ax2.set_yticks(ratio_yticks)
        self.ax2.set_yticklabels(self.ax2.get_yticks(),fontProperties,fontsize=self.label_size)
        self.ax2.set_ylabel(self.y_ratio_label,fontsize=self.label_size,ha='center',va='bottom')


        ## -- Simulation Uncertainties
        self.plotUncertainty(stat=self.drawStatUncertainty,
                             syst=self.drawSystUncertainty,
                             statsyst=self.drawStatSystUncertainty,
                             total=self.drawTotalUncertainty)

        # y-axis
        if self.ymaxScale is None:
            self.ymaxScale = self.yMaxScaleValues[self.typeOfPlot]
        yminimum = 0.1 if self.logplot else 0.0

        self.ax1.set_ylim(yminimum,self.ymaxScale*self.ax1.get_ylim()[1])
        self.ax1.set_yticks(self.ax1.get_yticks()[1:])                  # remove the first point (overlaps with ratio plot)
        if self.logplot: self.ax1.set_yticks(self.ax1.get_yticks()[1:]) # remove the first point (again)
        self.setYAxis(self.ax1)

        # x-axis
        if self.xlim is not None:
            plt.xlim(self.xlim)
        if self.ratio_plot:
            x_axis = self.ax2
        else:
            x_axis = self.ax1
        self.setXAxis(x_axis)


        # axis ticks
        self.setAxisTickMarks()
        plt.tick_params(which='minor', length=4) # ticks

        # CMS label
        self.text_labels()

        # Legend
        handles, labels = self.ax1.get_legend_handles_labels()
        handles+=self.uncertainty_handles # add legend items from uncertainty drawings in the ratio
        labels+=self.uncertainty_labels

        handles.insert(0,handles.pop()) # move data to the top
        labels.insert(0,labels.pop())   # move data to the top

        leg = self.ax1.legend(handles,labels,numpoints=1,fontsize=14,
                              ncol=self.numLegendColumns,columnspacing=0.3,loc=self.legendLoc)
        leg.draw_frame(False)

        return fig



    def plotUncertainty(self,stat=False,syst=False,statsyst=False,total=False):
        """
        Plot uncertainties (imagine drawing stat+syst OR stat+syst with stat-only)

        @param stat       Draw statistical uncertainty only
        @param syst       Draw systematic uncertainty only
        @param statsyst   Draw stat+syst uncertainty
        @param total      Draw total uncertainty (provide total uncertainty from external source)
        """
        fill_between_bins = self.binning   ## for plotting hatch uncertainty
        fill_between_bins = [self.binning[0]]+list(fill_between_bins[1:-1].repeat(2))+[self.binning[-1]]

        unc_kwargs = {'alpha':1.0,'lw':0,'edgecolor':'none'}
        # check if alpha is necessary, replace with color to match alpha effect
        # (don't need transparency)

        totalYield = self.histograms['background']       # calculated above
        totalError = None
        systError  = None
        statError  = None

        ## Need to loop over all samples and add uncertainties in quadrature
        if syst or statsyst:
            for name in self.sampleTypes['background']:
                # systematic uncertainty
                if syst:
                    if systError is None:
                        systError  = self.systematics[name]**2
                    else:
                        systError += self.systematics[name]**2
                # stat + syst uncertainty
                if statsyst:
                    if totalError is None:
                        totalError  = (self.uncertainties[name]**2+self.systematics[name]**2)
                    else:
                        totalError += (self.uncertainties[name]**2+self.systematics[name]**2)


        if stat:
            statError = self.uncertainties['background']
            resid_unc = {'up': list(((totalYield+statError)/totalYield).repeat(2)),
                         'dn': list(((totalYield-statError)/totalYield).repeat(2))}

            self.ax2.fill_between(fill_between_bins,resid_unc['dn'],resid_unc['up'],
                                  zorder=2,color=self.statColor,**unc_kwargs)
                                  # zorder plots in front of syst and total
            stat_handle = matplotlib.patches.Patch(color=self.statColor,linewidth=0)
            self.uncertainty_handles.append(stat_handle)
            self.uncertainty_labels.append( "Stat. Uncertainty" )

        if syst:
            systError = np.sqrt(systError)
            resid_unc = {'up': list(((totalYield+systError)/totalYield).repeat(2)),
                         'dn': list(((totalYield-systError)/totalYield).repeat(2))}

            self.ax2.fill_between(fill_between_bins,resid_unc['dn'],resid_unc['up'],
                                  zorder=1,color=self.systColor,**unc_kwargs)
                                  # zorder plots behind stat and in front of total
            syst_handle = matplotlib.patches.Patch(color=self.systColor,linewidth=0)
            self.uncertainty_handles.append(syst_handle)
            self.uncertainty_labels.append( "Syst. Uncertainty" )

        if statsyst:
            statsystError = np.sqrt(statsystError)
            resid_unc  = {'up': list(((totalYield+statsystError)/totalYield).repeat(2)),
                          'dn': list(((totalYield-statsystError)/totalYield).repeat(2))}

            self.ax2.fill_between(fill_between_bins,resid_unc['dn'],resid_unc['up'],
                                  zorder=0,color=self.statSystColor,**unc_kwargs)
                                  # zorder plots behind stat and syst
            statsyst_handle = matplotlib.patches.Patch(color=self.statSystColor,linewidth=0)
            self.uncertainty_handles.append(statsyst_handle)
            self.uncertainty_labels.append( "Stat+Syst. Uncertainty" )

        ## total uncertainty (provided directly to plotter)
        if total:
            totalError  = self.totaluncertainty
            resid_unc  = {'up': list(((totalYield+totalError)/totalYield).repeat(2)),
                          'dn': list(((totalYield-totalError)/totalYield).repeat(2))}

            self.ax2.fill_between(fill_between_bins,resid_unc['dn'],resid_unc['up'],
                                  zorder=0,color=self.systColor,**unc_kwargs)
                                  # zorder plots behind stat and syst
            total_handle = matplotlib.patches.Patch(color=self.systColor,linewidth=0)
            self.uncertainty_handles.append(total_handle)
            self.uncertainty_labels.append( "Total Uncertainty" )

        return

### THE END ###
