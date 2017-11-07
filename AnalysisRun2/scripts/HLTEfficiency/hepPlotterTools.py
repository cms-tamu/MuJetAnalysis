"""
Created:         1 September 2016
Last Updated:   28 September 2016

Dan Marley
daniel.edison.marley@cernSPAMNOT.ch
Texas A&M University

-----
Simple functions to help with basic plots.
"""
import ROOT
import numpy as np
import matplotlib.pyplot as plt


def betterColors():
    """ Better colors for plotting """
    old_colors = [(31, 119, 180), (174, 199, 232), (255, 127, 14), (255, 187, 120),    
         (44, 160, 44), (152, 223, 138), (214, 39, 40), (255, 152, 150),    
         (148, 103, 189), (197, 176, 213), (140, 86, 75), (196, 156, 148),    
         (227, 119, 194), (247, 182, 210), (127, 127, 127), (199, 199, 199),    
         (188, 189, 34), (219, 219, 141), (23, 190, 207), (158, 218, 229)]
    lc = []
    for jj in old_colors:
        new_color = [i/255. for i in jj]
        lc.append(new_color)

    ls  = ['solid' for _ in lc]
    ls += ['dashed' for _ in lc]

    return {'linecolors':lc,'linestyles':ls}


def extract(str_value, start_='{', stop_='}'):
    """Extract a string between two symbols, e.g., parentheses."""
    extraction = str_value[str_value.index(start_)+1:str_value.index(stop_)]

    return extraction


def getName(filename):
    """Given a root file full of histograms, return the sample name
    example name: TTS_M500_XXX.root
    can be customized by users depending on their files
    best (future) solution: metadata in root file with "name" option
    """
    name = filename.split(".root")[0].split("/")[-1]

    return name


def getSampleType(name):
    """Given a sample name return the sample type"""
    backgrounds = open("share/sampleNamesShort.txt").readlines()
    backgrounds = [i.rstrip("\n") for i in backgrounds]
    signal = ['TTS','BBS','TTD','BBD','XX','YY','zprime']
    data = ['data']

    sampletype = ''
    if name=='data':
        sampletype = 'data'
    elif any(name.startswith(i) for i in signal):
        sampletype = 'signal'
    elif name in backgrounds:
        sampletype = 'background'
    else:
        sampletype = ''

    return sampletype


def data2list(data,weights=None,normed=False,binning=1):
    """Convert array of data into dictionary of information matching 'hist2list' """
    data,bins = np.histogram(data,bins=binning,weights=weights,normed=normed)

    results = {'data': data,
               'error':np.sqrt(data),
               'bins': bins,
               'center':0.5*(bins[:-1]+bins[1:]),
               'width': 0.5*(bins[:-1]-bins[1:])}

    return results


def data2list2D(data,weights=None,normed=False,binning=1):
    """Convert array of data into dictionary of information matching 'hist2list' """
    try:
        x = data['x']
        y = data['y']
    except IndexError:
        x = data[0]
        y = data[1]
    _,bins_x,bins_y = np.histogram2d(x, y, bins=binning,normed=normed,weights=weights)

    binnsx = []
    binnsy = []
    for x in 0.5*(bins_x[:-1]+bins_x[1:]):
        for y in 0.5*(bins_y[:-1]+bins_y[1:]):
            binnsx.append(x)
            binnsy.append(y)

    results = {'data':  weights,
               'error': np.sqrt(weights),
               'bins':  {'x':bins_x,'y':bins_y},
               'center':{'x':binnsx,
                         'y':binnsy},
               'width': {'x':0.5*(bins_x[:-1]-bins_x[1:]),
                         'y':0.5*(bins_y[:-1]-bins_y[1:])}}

    return results


def hist2list(histo,name='',normed=False,reBin=1):
    """Convert ROOT histogram to (dictionary of) lists"""
    if not histo.GetSumw2N():
        histo.Sumw2()

    bin_center  = []
    bin_content = []
    bin_error   = [] # just stat. uncertainty (symmetric)
    binwidth    = []

    if normed:
        histo.Scale(1./histo.Integral());

    try:
        histo.Rebin(reBin)
    except TypeError:
        newname = histo.GetName()+"_"+name
        histo.Rebin( len(reBin)-1,newname,reBin)
        histo = ROOT.gROOT.FindObject( newname )


    binns = [histo.GetXaxis().GetBinLowEdge(1)]
    # do one for loop instead of multiple list comprehensions
    for i in xrange(1,histo.GetNbinsX()+1):
        binns.append(histo.GetXaxis().GetBinUpEdge(i))
        bin_center.append(histo.GetBinCenter(i))
        bin_content.append(histo.GetBinContent(i))
        bin_error.append(histo.GetBinError(i))
        binwidth.append(histo.GetXaxis().GetBinWidth(i)/2.)

    results = {'data': np.array(bin_content),
               'error':np.array(bin_error),
               'bins': binns,
               'center':bin_center,
               'width': binwidth}

    return results


def hist2list(histo,name='',normed=False,reBin=1):
    """Convert ROOT histogram to (dictionary of) lists"""
    if not histo.GetSumw2N():
        histo.Sumw2()

    bin_center  = []
    bin_content = []
    bin_error   = [] # just stat. uncertainty (symmetric)
    binwidth    = []

    if normed:
        histo.Scale(1./histo.Integral());

    try:
        histo.Rebin(reBin)
    except TypeError:
        newname = histo.GetName()+"_"+name
        histo.Rebin( len(reBin)-1,newname,reBin)
        histo = ROOT.gROOT.FindObject( newname )


    binns = [histo.GetXaxis().GetBinLowEdge(1)]
    # do one for loop instead of multiple list comprehensions
    for i in xrange(1,histo.GetNbinsX()+1):
        binns.append(histo.GetXaxis().GetBinUpEdge(i))
        bin_center.append(histo.GetBinCenter(i))
        bin_content.append(histo.GetBinContent(i))
        bin_error.append(histo.GetBinError(i))
        binwidth.append(histo.GetXaxis().GetBinWidth(i)/2.)

    results = {'data': np.array(bin_content),
               'error':np.array(bin_error),
               'bins': binns,
               'center':bin_center,
               'width': binwidth}

    return results



def hist2list2D(histo,name='',reBin=None,normed=False):
    """Convert ROOT histogram to list for 2D plots."""
    if not histo.GetSumw2N():
        histo.Sumw2()

    bin_center  = {'x':[],'y':[]}
    bin_content = []
    bin_error   = [] # just stat. uncertainty (symmetric)
    binwidth    = {'x':[],'y':[]}

    if normed:
        histo.Scale(1./histo.Integral())

    ## -- Rebin
    if reBin is not None:
        try:
            histo.Rebin2D(reBin,reBin)
        except TypeError:
            newname = histo.GetName()+"_"+name

            old_histo = histo.Clone()     # special rebinning, redefine histo
            new_x     = reBin['x']
            new_y     = reBin['y']
            histo     = ROOT.TH2F(old_histo.GetName()+newname,old_histo.GetTitle()+newname,len(new_x)-1,new_x,len(new_y)-1,new_y)
            xaxis = old_histo.GetXaxis()
            yaxis = old_histo.GetYaxis()
            for i in xrange(1,xaxis.GetNbins()):
                for j in xrange(1,yaxis.GetNbins()):
                    histo.Fill(xaxis.GetBinCenter(i),yaxis.GetBinCenter(j),old_histo.GetBinContent(i,j) )

    binns = {'x':[histo.GetXaxis().GetBinLowEdge(1)],\
             'y':[histo.GetYaxis().GetBinLowEdge(1)]}
    # do one for loop instead of multiple list comprehensions
    binns['x']+=[histo.GetXaxis().GetBinUpEdge(i) for i in xrange(1,histo.GetNbinsX()+1)]
    binns['y']+=[histo.GetYaxis().GetBinUpEdge(j) for j in xrange(1,histo.GetNbinsY()+1)]
    for i in xrange(1,histo.GetNbinsX()+1):
        for j in xrange(1,histo.GetNbinsY()+1):
            bin_center['x'].append(histo.GetXaxis().GetBinCenter(i))
            bin_center['y'].append(histo.GetYaxis().GetBinCenter(j))

            bin_content.append(histo.GetBinContent(i,j))
            bin_error.append(histo.GetBinError(i,j))

            binwidth['x'].append(histo.GetXaxis().GetBinWidth(i)/2.)
            binwidth['y'].append(histo.GetYaxis().GetBinWidth(i)/2.)

    results = {'data': np.array(bin_content),
               'error':np.array(bin_error),
               'bins': binns,
               'center':bin_center,
               'width': binwidth}

    return results

def TEfficiency2list(histo):
    """Convert TEfficiency to lists.  Return dictionary of lists"""
    h_histo  = histo.GetPassedHistogram()

    h_eff    = []
    h_eff_up = []
    h_eff_dn = []
    h_eff_mp = []
    binwidth = []
    binns = [h_histo.GetXaxis().GetBinLowEdge(1)]
    for i in xrange(1,h_histo.GetNbinsX()+1):
        h_eff.append(histo.GetEfficiency(i))
        h_eff_up.append(histo.GetEfficiencyErrorUp(i))
        h_eff_dn.append(histo.GetEfficiencyErrorLow(i))
        h_eff_mp.append(h_histo.GetXaxis().GetBinCenter(i))
        binns.append(h_histo.GetXaxis().GetBinUpEdge(i))
        binwidth.append(h_histo.GetXaxis().GetBinWidth(1)/2.)

    results  = {'data': np.array(h_eff),
                'error':[h_eff_dn,h_eff_up],
                'bins': binns,
                'center':h_eff_mp,
                'width': binwidth}

    return results



def TEfficiency2list2D(histo):
    """Convert 2D TEfficiency to lists"""
    h_histo  = histo.GetPassedHistogram()

    bin_center   = {'x':[],'y':[]}
    bin_content  = []
    bin_error_up = [] # eff uncertainty up   -- not necessarily symmetric
    bin_error_dn = [] # eff uncertainty down
    binwidth     = {'x':[],'y':[]}

    binns = {'x':[h_histo.GetXaxis().GetBinLowEdge(1)],\
             'y':[h_histo.GetYaxis().GetBinLowEdge(1)]}
    # do one for loop instead of multiple list comprehensions
    binns['x']+=[h_histo.GetXaxis().GetBinUpEdge(i) for i in xrange(1,h_histo.GetNbinsX()+1)]
    binns['y']+=[h_histo.GetYaxis().GetBinUpEdge(j) for j in xrange(1,h_histo.GetNbinsY()+1)]
    for i in xrange(1,h_histo.GetNbinsX()+1):
        for j in xrange(1,h_histo.GetNbinsY()+1):
            bin_center['x'].append(h_histo.GetXaxis().GetBinCenter(i))
            bin_center['y'].append(h_histo.GetYaxis().GetBinCenter(j))

            this_bin = histo.GetGlobalBin(i,j)
            bin_content.append(histo.GetEfficiency(this_bin))
            bin_error_up.append(histo.GetEfficiencyErrorUp(this_bin))
            bin_error_dn.append(histo.GetEfficiencyErrorLow(this_bin))
            binwidth['x'].append(h_histo.GetXaxis().GetBinWidth(1)/2.)
            binwidth['y'].append(h_histo.GetYaxis().GetBinWidth(1)/2.)

    results  = {'data': np.array(bin_content),
                'error':[bin_error_up,bin_error_dn],
                'bins': binns,
                'center':bin_center,
                'width': binwidth}

    return results


def getDataStructure(h_data):
    """
    Find the data structure determining the appropriate color scheme.
    Only call if the self.colormap attribute is None.

    @param h_data    The histogram data
    @param colorMap  Current choice for colormap
    """
    max_value = max(h_data)
    min_value = min(h_data)

    ## linear (same sign)
    if max_value*min_value > 0:
        if max_value>0:
            colormap = plt.cm.Reds    # positive values
        else:
            colormap = plt.cm.Blues   # negative values
    ## diverging
    else:
        colormap = plt.cm.bwr         # blue2red map

    return colormap


## -- Classes for handling text on plots

class Text(object):
    """Class to hold extra text object"""
    def __init__(self):
        self.text     = ''
        self.coords   = [0.,0.]
        self.fontsize = 16
        self.color    = 'k'
        self.ha = 'left'
        self.va = 'top'
        self.transform = None   # 'None' so the user can change it -- it will be set below
        return
    def __str__(self):
        """print text object with attributes"""
        for i in ['text','coords','fontsize','color','ha','va','transform']:
            print "%-*s: %s" % (10,i,self.__dict__[i])
        return



class PlotText(object):
    """Class to draw new text on the plots"""
    def __init__(self):
        self.texts  = []
        self.params = ['coords','fontsize','color','ha','va','transform']

    def Add(self,plt_text,**txt_kwargs):
        """
        Add new text to the plot
        @param plt_text    text to draw
        @param txt_kwargs  key-word arguments:
                             'coords','fontsize','color','ha','va','transform'
        """
        pltTextObject = Text()
        pltTextObject.text = plt_text

        # set parameters of the text object if they are passed to the 'Add()' function
        # - use defaults if no argument is passed - this ensures any extra arguments don't
        # harm anything in the text object
        for param in self.params:
            try:
                setattr( pltTextObject,param,txt_kwargs[param] )
            except KeyError:
                # use the defaults
                continue

        self.texts.append(pltTextObject)

        return
    
    def Print(self):
        """Print out the text arguments"""
        for text in self.texts:
            print text
    def getText(self):
        """Return the list of Text objects"""
        return self.texts


## THE END
