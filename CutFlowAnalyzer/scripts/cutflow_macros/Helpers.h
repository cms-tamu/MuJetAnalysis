#include <iostream>
#include <fstream>
#include <algorithm>    // std::max
#include <stdlib.h>
#include <iomanip>
#include "TSystemDirectory.h"

using namespace std;

void addfiles(TChain *ch, const TString dirname=".", const TString ext=".root")
{
  bool verbose(false);
  TSystemDirectory dir(dirname, dirname);
  TList *files = dir.GetListOfFiles();
  if (files) {
    if (verbose) std::cout << " Found files" << std::endl;
    TSystemFile *file;
    TString fname;
    TIter next(files);
    while ((file=(TSystemFile*)next())) {
      fname = file->GetName();
      if (verbose) std::cout << " found fname " << fname << std::endl;
      if (!file->IsDirectory() && fname.BeginsWith(ext)) {
        if (verbose) std::cout << " adding fname " << fname << std::endl;
        ch->Add(fname);
      }
    }
  }
}

double My_dPhi (double phi1, double phi2) {
  double dPhi = phi1 - phi2;
  if (dPhi >  M_PI) dPhi -= 2.*M_PI;
  if (dPhi < -M_PI) dPhi += 2.*M_PI;
  return dPhi;
}

void addfilesMany(TChain *ch, const std::vector<string>& v, const TString ext=".root")
{
  bool verbose(true);
  int nfiles=0;
  for(std::string dirname : v) {
    TSystemDirectory dir(dirname.c_str(), dirname.c_str());
    TList *files = dir.GetListOfFiles();
    if (files) {
      if (verbose) std::cout << " Found files" << std::endl;
      TSystemFile *file;
      TString fname;
      TIter next(files);
      while ((file=(TSystemFile*)next())) {
        fname = file->GetName();
        if (verbose) std::cout << " file name: " << dirname + fname << std::endl;
        if (!file->IsDirectory() && fname.BeginsWith(ext)) {
          nfiles++;
          if (verbose) std::cout << " adding #" << nfiles << ": " << dirname + fname << std::endl;
          ch->Add(dirname + fname);
        }
      }
    }
  }
}

void decodeFileName(const TString& fileName, TString& mass_string, TString& cT_string)
{
  ///Get the sample mass
  TString str = fileName;
  TString str2 = "DarkSUSY_mH_125_mGammaD_";
  Ssiz_t first = str.Index(str2);
  Ssiz_t last = str.Index("_cT_");
  mass_string = (str(first+str2.Length(),4));
  ///Get the sample cT
  TString str3 = "_cT_";
  cT_string = (str(last+str3.Length(),4));
  bool verbose(false);
  if (verbose) cout << "mass_string " << mass_string << " cT_string " << cT_string << endl;
}

void decodeFileNameMany(const std::vector<string>& v, TString& mass_string, TString& cT_string)
{
  ///Get the sample mass
  TString str(v[0]);
  TString str2 = "DarkSUSY_mH_125_mN1_10_mGammaD_";
  Ssiz_t first = str.Index(str2);
  Ssiz_t last = str.Index("_cT_");
  mass_string = (str(first+str2.Length(),4));
  ///Get the sample cT
  TString str3 = "_cT_";
  cT_string = (str(last+str3.Length(),4));
  bool verbose(false);
  if (verbose) cout << "mass_string " << mass_string << " cT_string " << cT_string << endl;
}

void decodeFileNameManyJpsi(const std::vector<string>& v, TString& period)
{
  //Get the Run period
  TString str(v[0]);
  TString str2 = "MuOnia_Run2016";
  Ssiz_t first = str.Index(str2);
  period = (str(first+str2.Length(),1));
  bool verbose(false);
  if (verbose) cout << " Period " << period << endl;
}

void readTextFileWithSamples(const std::string fileName, std::vector< std::vector<string> >& v)
{
  ifstream infile(fileName);
  string line;
  std::vector<string> vv;
  while (std::getline(infile, line)) {
    if (line.empty()) {
      v.push_back(vv);
      vv.clear();
    }
    else {
      if (line.back() != '/')
	line += '/';
	vv.push_back(line);
    }
  }
  v.push_back(vv);
  infile.close();
}
