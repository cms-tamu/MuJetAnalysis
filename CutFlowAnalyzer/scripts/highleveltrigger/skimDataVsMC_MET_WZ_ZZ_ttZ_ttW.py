import sys
from ROOT import *
from argparse import ArgumentParser

import math as m
import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from Helpers import *
import numpy

verbose = False

## mass of the muon in GeV
mmu = 105.6583745 * 0.001
mZ = 91.1876

verbose = True

def getPhi(m1):
    return m1[4]

## total energy of the muon
def energy(mmu, px, py, pz):
    return numpy.sqrt(mmu*mmu + px*px + py*py + pz*pz)

## dimuon invariant mass
def inner(m1, m2):
    return m1[0] * m2[0] - m1[1] * m2[1] - m1[2] * m2[2] - m1[3] * m2[3]

def invmass(m1, m2):
    a = inner(m1,m1)
    b = inner(m2,m2)
    c = 2*inner(m1,m2)
    return numpy.sqrt(a+b+c)

def inv3mass(m1, m2, m3):
    a = inner(m1,m1)
    b = inner(m2,m2)
    c = inner(m3,m3)
    d = 2*inner(m1,m2)
    e = 2*inner(m1,m3)
    f = 2*inner(m2,m3)
    return numpy.sqrt(a+b+c+d+e+f)

def isMassInZPeak(m):
    return abs(m-mZ)<15

def bestMassInZPeak(m1, m2, m3):
    masses = [m1, m2, m3]
    massdiffs = [abs(m1-mZ), abs(m2-mZ), abs(m3-mZ)]
    index = massdiffs.index(min(massdiffs))
    return masses[index]

def bestMassInZPeak(m1, m2):
    masses = [m1, m2]
    massdiffs = [abs(m1-mZ), abs(m2-mZ)]
    index = massdiffs.index(min(massdiffs))
    return masses[index]

histograms = {}

print 'Number of arguments:', len(sys.argv), 'arguments.'
print 'Argument List:', str(sys.argv)

## get the input file
inputFile = list(sys.argv)[1]
print inputFile
rootFile = ROOT.TFile(inputFile,"")

#tree = rootFile.Get("cutFlowAnalyzerPXBL4PXFL3/Events")
tree = rootFile.Get("Events")

newTitle = inputFile
print
newTitle = newTitle.replace('out_ana','out_ana_clone')
print newTitle
print tree
newfile = TFile(newTitle, "RECREATE")
print newfile
newtree = tree.CloneTree(0)
sumGenWeight = numpy.zeros(1, dtype=float)
best_OS_dimuon_mass = numpy.zeros(1, dtype=float)
best_SS_dimuon_mass = numpy.zeros(1, dtype=float)
m123 = numpy.zeros(1, dtype=float)
newtree.Branch( 'best_OS_dimuon_mass', best_OS_dimuon_mass, 'best_OS_dimuon_mass/D')
newtree.Branch( 'best_SS_dimuon_mass', best_SS_dimuon_mass, 'best_SS_dimuon_mass/D')
newtree.Branch( 'm123', m123, 'm123/D')
#newtree.Branch( 'sumGenWeight', sumGenWeight, 'sumGenWeight/D')

for k in range(0, tree.GetEntries()):

    if k%1000==0: print "Processing event ", k, "/",tree.GetEntries()
    tree.GetEntry(k)

    genWeight = tree.genWeight
    #sumGenWeight += genWeight

    q0 = tree.selMu0_charge
    q1 = tree.selMu1_charge
    q2 = tree.selMu2_charge

    px0 = tree.selMu0_px
    px1 = tree.selMu1_px
    px2 = tree.selMu2_px

    py0 = tree.selMu0_py
    py1 = tree.selMu1_py
    py2 = tree.selMu2_py

    pz0 = tree.selMu0_pz
    pz1 = tree.selMu1_pz
    pz2 = tree.selMu2_pz

    E0 = energy(mmu, tree.selMu0_px, py0, pz0)
    E1 = energy(mmu, px1, py1, pz1)
    E2 = energy(mmu, px2, py2, pz2)

    mu0 = [E0, tree.selMu0_px, py0, pz0]
    mu1 = [E1, px1, py1, pz1]
    mu2 = [E2, px2, py2, pz2]

    invm3 = inv3mass(mu0, mu1, mu2)
    m123[0] = invm3
    #print m123[0], type(invm3)

    SS_dimuon_mass = 0
    OS_dimuon_mass1 = 0
    OS_dimuon_mass2 = 0

    if q0 * q1 > 0:
        SS_dimuon_mass = invmass(mu0, mu1)
        OS_dimuon_mass1 = invmass(mu1, mu2)
        OS_dimuon_mass2 = invmass(mu0, mu2)
        OS_dimuon_mass = bestMassInZPeak(OS_dimuon_mass1, OS_dimuon_mass2)

    elif q0 * q2 > 0:
        SS_dimuon_mass = invmass(mu0, mu2)
        OS_dimuon_mass1 = invmass(mu0, mu1)
        OS_dimuon_mass2 = invmass(mu1, mu2)
        OS_dimuon_mass = bestMassInZPeak(OS_dimuon_mass1, OS_dimuon_mass2)

    elif q1 * q2 > 0:
        SS_dimuon_mass = invmass(mu1, mu2)
        OS_dimuon_mass1 = invmass(mu0, mu1)
        OS_dimuon_mass2 = invmass(mu0, mu2)
        OS_dimuon_mass = bestMassInZPeak(OS_dimuon_mass1, OS_dimuon_mass2)

    else:
        SS_dimuon_mass = 0
        OS_dimuon_mass1 = 0
        OS_dimuon_mass2 = 0
        OS_dimuon_mass = 0

    best_OS_dimuon_mass[0] = 0
    best_SS_dimuon_mass[0] = 0
    best_OS_dimuon_mass[0] = OS_dimuon_mass
    best_SS_dimuon_mass[0] = SS_dimuon_mass

    newtree.Fill()

newfile.Write()
newfile.Close()
