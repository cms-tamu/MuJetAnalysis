import shutil
import os 
import sys
import fileinput




cTaus = ["000","005","010","020","050","100","200","300","500","1000","2000","5000","10000"]
masses = ["0250","0275","0300","0350","0400","0550","0700","0850","1000","1500","2000","3000","5000","7000","9000"]


for mass in masses:
    for cT in cTaus:
       infile = open('DarkSUSY_mH_125_mGammaD_XXX_13TeV_cT_YYY_madgraph452_bridge224_LHE_pythia8_cfi_GEN.py','r')
#       print "mass: %s  ctau %s " % (mass,cT)
       name = "DarkSUSY_mH_125_mGammaD_%s_13TeV_cT_%s_madgraph452_bridge224_LHE_pythia8_cfi_GEN.py" % (mass,cT)
       outfile = open(name,'w')
       cT_temp = "%s" %cT
       mass_temp = "%s" %mass
       replacements = {'XXX':mass_temp,'YYY':cT_temp}
       for line in infile:
           mass_Temp = '%s' %mass
           cTau_Temp = '%s' %cT
           line = line.replace('XXX',mass_Temp)
           line = line.replace('YYY',cTau_Temp)
           outfile.write(line)
       outfile.close()
       infile.close()

for mass in masses:
    for cT in cTaus:
       infile = open('DarkSUSY_mH_125_mGammaD_XXX_13TeV_cT_YYY_madgraph452_bridge224_LHE_pythia8_731p2_GEN_v1.CRAB.cfg','r')
#       print "mass: %s  ctau %s " % (mass,cT)
       name = "DarkSUSY_mH_125_mGammaD_%s_13TeV_cT_%s_madgraph452_bridge224_LHE_pythia8_731p2_GEN_v1.CRAB.cfg" % (mass,cT)
       outfile = open(name,'w')
       cT_temp = "%s" %cT
       mass_temp = "%s" %mass
       replacements = {'XXX':mass_temp,'YYY':cT_temp}
       for line in infile:
           mass_Temp = '%s' %mass
           cTau_Temp = '%s' %cT
           line = line.replace('XXX',mass_Temp)
           line = line.replace('YYY',cTau_Temp)
           outfile.write(line)
       outfile.close()
       infile.close()
