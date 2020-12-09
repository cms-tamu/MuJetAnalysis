# Run quiet mode
import sys
sys.argv.append( '-b' )
import ROOT
ROOT.gROOT.SetBatch(1)
ROOT.gErrorIgnoreLevel=1001
from ROOT import *
import random
import numpy
import math

M_PI = 4*math.atan(1)


def normalizePhi(result):
    while (result > M_PI):
        result -= 2*M_PI;
    while (result <= -M_PI):
        result += 2*M_PI;
    return result

#______________________________________________________________________________
def deltaPhi(phi1, phi2):
  result = phi1 - phi2;
  while (result > M_PI):
    result -= 2*M_PI;
  while (result <= -M_PI):
    result += 2*M_PI;
  return result;


#______________________________________________________________________________
def deltaR(eta1, phi1, eta2, phi2):
    dEta = eta1 - eta2
    dPhi = deltaPhi2(phi1, phi2)
    dR = math.sqrt(dEta*dEta + dPhi*dPhi)
    return dR

#______________________________________________________________________________
def printFileNames(listWithFiles):
    for p in listWithFiles:
        for q in p:
            print q

#______________________________________________________________________________
## this function puts the list of MC samples in a 2D vector
## the first dimension determines the mass/ctau
## the second dimension is the list of associated directories
def readTextFileWithSamples(fileName):
  all_samples = []
  sample = []

  debug = False

  f = open(fileName, 'r')
  for line in f:
    if debug:
      print line
    ## if line is empty add the sample to the list
    if not line.strip():
      if debug:
        print ">> add file to list"
      all_samples.append(sample)
      sample = []
    else:
      if debug:
        print ">> append sample"
      ## add a slash if it is not done yet
      if not line.endswith("/"):
        line += '/'
      ## removing trailing \n/
      if line.endswith("\n/"):
        line = line.replace("\n/","")
      ## add file to the list
      sample.append(line)

  f.close()

  return all_samples


#______________________________________________________________________________
## add single ROOT file to a chain
def addfile(ch, fileName):
  verbose = False
  tempFile = ROOT.TFile(fileName)
  if (not tempFile.IsZombie()):
    ch.Add(fileName)
  else:
    print "No such file", fileName
  return ch

#______________________________________________________________________________
## add ROOT files to a chain
def addfiles(ch, dirname=".", ext="out_ana"):
  verbose = False
  dir = TSystemDirectory(dirname, dirname);
  files = dir.GetListOfFiles();

  debug = True

  ## print file pointer
  if debug:
    print "All files", files

  #root:////cmsxrootd-site.fnal.gov//" +

  ## check if list is not empty
  if not files.First():
    print "file list is empty"
  else:
    for pp in files:
      print pp
      fname = pp.GetName()
      ## check if file is not a directory
      if (not pp.IsDirectory() and ext in fname):
        ch.Add(dirname + fname)
        #print "Adding", dirname + fname
  return ch


#______________________________________________________________________________
## add many ROOT files to a chain
def addfilesMany(ch, dirnames, ext="out_ana"):
  for dirname in dirnames:
    addfiles(ch, dirname, ext)
  return ch

#______________________________________________________________________________
def decodeDarkSUSYFileName(fileName):
  ## DarkSUSY_mH_125_mN1_10_mGammaD_0p25_cT_100_13TeV

  ## only take the part that starts with the substring above
  substring_index = fileName.find("DarkSUSY_mH_125_mN1_")
  substring = fileName[substring_index:]

  ## split up the string in substrings
  fileName_array = substring.split("_")

  neutralino_string = fileName_array[4];
  mass_string = fileName_array[6];
  cT_string = fileName_array[8];
  return neutralino_string, mass_string, cT_string


#______________________________________________________________________________
def getDarkSUSYFileName(neutralino_string, mass_string, cT_string):
  return "DarkSUSY_mH_125_mN1_" + neutralino_string + "_mGammaD_" + mass_string + "_cT_" + cT_string + "_13TeV"

#______________________________________________________________________________
def getDarkSUSYFileNameNoCT(neutralino_string, mass_string):
  return "DarkSUSY_mH_125_mN1_" + neutralino_string + "_mGammaD_" + mass_string + "_13TeV"

#______________________________________________________________________________
def decodeNMSSMFileName(fileName):
  ## NMSSM_HToAATo4Mu_M-XXX_M-YYYY_TuneCUETP8M1

  ## only take the part that starts with the substring above
  substring_index = fileName.find("NMSSM_HToAATo4Mu_M-")
  substring = fileName[substring_index:]

  ## split up the string in substrings
  fileName_array = substring.split("_")

  mH_string = fileName_array[3];
  mA_string = fileName_array[5];
  return mH, mA


#______________________________________________________________________________
def decodeDarkSUSYFileNameMany(fileNames):
  print "docoding many", fileNames
  return decodeDarkSUSYFileName(fileNames[0])


#______________________________________________________________________________
def decodeNMSSMFileNameMany(fileNames):
  return decodeNMSSMFileName(fileNames[0])


#______________________________________________________________________________
## in a list with files, pick the ones associated to the dark boson mass
def getDarkSUSYFileMaMass(all_samples, neutralino_string, mass_string):
  return_list = []
  for sample in all_samples:
    decodedFileName = decodeDarkSUSYFileNameMany(sample)

    ## must have correct neutralino mass
    if decodedFileName[0] != neutralino_string:
      continue

    ## must have correct dark boson mass
    if decodedFileName[1] != mass_string:
      continue

    return_list.append(sample)
    ## print decodedFileName

  ## print return_list
  return return_list
