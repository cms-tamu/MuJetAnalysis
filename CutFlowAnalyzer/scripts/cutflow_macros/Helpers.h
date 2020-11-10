#include <iostream>
#include <fstream>
#include <algorithm>    // std::max
#include <stdlib.h>
#include <iomanip>
#include "TSystemDirectory.h"

//CB fitted mean mass [GeV] for prompt signals
double mean[11] = {0.2560, 0.4012, 0.7003, 1.0000, 1.9990, 4.9980, 8.4920, 14.990, 24.980, 34.970, 57.930};

//80% signal eff needed mass window size for prompt signals
//double window[11] = {0.030922364, 0.0201698988, 0.02337757474, 0.0275968, 0.04615657165, 0.124742502, 0.2110350916, 0.3849085576, 0.67586519, 0.914118934, 1.860449598};

//85% signal eff needed mass window size for prompt signals
//double window[11] = {0.0359823872, 0.0252123735, 0.02787326219, 0.0326656, 0.056518251, 0.1538490858, 0.2586881768, 0.46940068, 0.849659096, 1.102319891, 2.524895883};

//90% signal eff needed mass window size for prompt signals
double window[11] = {0.0438535344, 0.0336164980, 0.0359654996, 0.0428032000, 0.0753576680, 0.2037460866, 0.3539943472, 0.7041010200, 1.1972469080, 1.6131510600, 3.9866777100};

//95% signal eff needed mass window size for prompt signals
//double window[11] = {0.0629691776, 0.05176940692, 0.05574652438, 0.0664576, 0.1224562105, 0.3617532558, 0.748834196, 1.40820204, 2.70346076, 2.6885851, 9.523730085};

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

double My_MassWindow(double m1, double m2) {
  //return this mass window size given m1 and m2
  double mysize = 0.0;

  //Interpolation by drawing staight line, we use (m1+m2)/2 here
  //mass window size = y1 + (x-x1)*(y2-y1)/(x2-x1), x = (m1+m2)/2
  //Start and end with 0.2113 and 60GeV to match bkg analysis
  if ( (m1+m2)/2 >= 0.2113   && (m1+m2)/2 < mean[1] ) mysize = window[0] + ( (m1+m2)/2 - mean[0] )*( window[1]  - window[0] )/( mean[1]  - mean[0] );
  if ( (m1+m2)/2 >= mean[1]  && (m1+m2)/2 < mean[2] ) mysize = window[1] + ( (m1+m2)/2 - mean[1] )*( window[2]  - window[1] )/( mean[2]  - mean[1] );
  if ( (m1+m2)/2 >= mean[2]  && (m1+m2)/2 < mean[3] ) mysize = window[2] + ( (m1+m2)/2 - mean[2] )*( window[3]  - window[2] )/( mean[3]  - mean[2] );
  if ( (m1+m2)/2 >= mean[3]  && (m1+m2)/2 < mean[4] ) mysize = window[3] + ( (m1+m2)/2 - mean[3] )*( window[4]  - window[3] )/( mean[4]  - mean[3] );
  if ( (m1+m2)/2 >= mean[4]  && (m1+m2)/2 < mean[5] ) mysize = window[4] + ( (m1+m2)/2 - mean[4] )*( window[5]  - window[4] )/( mean[5]  - mean[4] );
  if ( (m1+m2)/2 >= mean[5]  && (m1+m2)/2 < mean[6] ) mysize = window[5] + ( (m1+m2)/2 - mean[5] )*( window[6]  - window[5] )/( mean[6]  - mean[5] );
  if ( (m1+m2)/2 >= mean[6]  && (m1+m2)/2 < mean[7] ) mysize = window[6] + ( (m1+m2)/2 - mean[6] )*( window[7]  - window[6] )/( mean[7]  - mean[6] );
  if ( (m1+m2)/2 >= mean[7]  && (m1+m2)/2 < mean[8] ) mysize = window[7] + ( (m1+m2)/2 - mean[7] )*( window[8]  - window[7] )/( mean[8]  - mean[7] );
  if ( (m1+m2)/2 >= mean[8]  && (m1+m2)/2 < mean[9] ) mysize = window[8] + ( (m1+m2)/2 - mean[8] )*( window[9]  - window[8] )/( mean[9]  - mean[8] );
  if ( (m1+m2)/2 >= mean[9]  && (m1+m2)/2 < 60.000  ) mysize = window[9] + ( (m1+m2)/2 - mean[9] )*( window[10] - window[9] )/( mean[10] - mean[9] );

  return mysize;
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
