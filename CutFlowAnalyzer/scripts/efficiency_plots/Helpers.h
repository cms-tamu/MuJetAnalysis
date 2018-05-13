#include <iostream>
#include <fstream>

const std::string cmssw_base(std::getenv("CMSSW_BASE"));
const std::string fileWithAnaDirs(cmssw_base + "/src/MuJetAnalysis/AnalysisRun2/scripts/ExtFidCut_UnHardCodeCuts_SampleList.txt");

void addfiles(TChain *ch, const TString dirname=".", const TString ext=".root")
{
  bool verbose(false);
  TSystemDirectory dir(dirname, dirname);
  TList *files = dir.GetListOfFiles();
  if (files) {
    if (verbose) std::cout << "Found files" << std::endl;
    TSystemFile *file;
    TString fname;
    TIter next(files);
    while ((file=(TSystemFile*)next())) {
      fname = file->GetName();
      if (verbose) std::cout << "found fname " << fname << std::endl;
      if (!file->IsDirectory() && fname.BeginsWith(ext)) {
        if (verbose) std::cout << "adding fname " << fname << std::endl;
        ch->Add(fname);
      }
    }
  }
}

void addfilesMany(TChain *ch, const std::vector<string>& v, const TString ext=".root")
{
  bool verbose(false);
  for(std::string dirname : v) {
    TSystemDirectory dir(dirname.c_str(), dirname.c_str());
    TList *files = dir.GetListOfFiles();
    if (files) {
      if (verbose) std::cout << "Found files" << std::endl;
      TSystemFile *file;
      TString fname;
      TIter next(files);
      while ((file=(TSystemFile*)next())) {
	fname = file->GetName();
	if (verbose) std::cout << "found fname " << dirname + fname << std::endl;
	if (!file->IsDirectory() && fname.BeginsWith(ext)) {
	  if (verbose) std::cout << "adding fname " << dirname + fname << std::endl;
	  ch->Add(dirname + fname);
	}
      }
    }
  }
}

struct tokens: std::ctype<char> 
{
 tokens(): std::ctype<char>(get_table()) {}

  static std::ctype_base::mask const* get_table()
  {
    typedef std::ctype<char> cctype;
    static const cctype::mask *const_rc= cctype::classic_table();

    static cctype::mask rc[cctype::table_size];
    std::memcpy(rc, const_rc, cctype::table_size * sizeof(cctype::mask));

    rc['_'] = std::ctype_base::space; 
    rc['-'] = std::ctype_base::space; 
    return &rc[0];
  }
};

void decodeDarkSUSYFileName(const TString& fileName, TString& mass_string, TString& cT_string)
{  
  // template: DarkSUSY_mH_125_mGammaD_XXXX_cT_YYYY_
  TString str1 = "DarkSUSY_mH_125_mGammaD_";
  Ssiz_t loc1 = fileName.Index(str1);
  TString substr(fileName(loc1, 100)); 

  std::stringstream ss(std::string(substr.Data()));
  ss.imbue(std::locale(std::locale(), new tokens()));
  std::istream_iterator<std::string> begin(ss);
  std::istream_iterator<std::string> end;
  std::vector<std::string> vstrings(begin, end);
  
  mass_string = vstrings[4];
  cT_string = vstrings[6];

  bool verbose(false);
  if (verbose) cout << "mass_string " << mass_string << " cT_string " << cT_string << endl;
}

void decodeNMSSMFileName(const TString& fileName, TString& mH_string, TString& mA_string)
{  
  // template: NMSSM_HToAATo4Mu_M-XXX_M-YYYY_TuneCUETP8M1
  TString str1 = "NMSSM_HToAATo4Mu_M-";
  Ssiz_t loc1 = fileName.Index(str1);
  TString substr(fileName(loc1, 100)); 

  std::stringstream ss(std::string(substr.Data()));
  ss.imbue(std::locale(std::locale(), new tokens()));
  std::istream_iterator<std::string> begin(ss);
  std::istream_iterator<std::string> end;
  std::vector<std::string> vstrings(begin, end);
  
  mH_string = vstrings[3];
  mA_string = vstrings[5];

  bool verbose(false);
  if (verbose) cout << "mH_string " << mH_string << " mA_string " << mA_string << endl;
}

void decodeFileDarkSUSYNameMany(const std::vector<string>& v, TString& mass_string, TString& cT_string)
{  
  decodeDarkSUSYFileName(v[0], mass_string, cT_string);
  bool verbose(false);
  if (verbose) cout << "mass_string " << mass_string << " cT_string " << cT_string << endl;
}

void decodeFileNMSSMNameMany(const std::vector<string>& v, TString& mH_string, TString& mA_string)
{  
  decodeNMSSMFileName(v[0], mH_string, mA_string);
  bool verbose(false);
  if (verbose) cout << "mH_string " << mH_string << " mA_string " << mA_string << endl;
}

void readTextFileWithSamples(const std::string fileName, std::vector< std::vector<string> >& v)
{
  ifstream infile(fileName);
  string line;
  std::vector<string> vv;
  while (std::getline(infile, line)) {
    // skip lines in txt file
    if (line.find("#") == 0) continue;
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

void readTextFileWithSamples(std::vector< std::vector<string> >& v)
{
  readTextFileWithSamples(fileWithAnaDirs, v);
}

void printFileNames(const std::vector< std::vector<string> >& vec)
{
  for (int i = 0; i < vec.size(); i++){
    for (int j = 0; j < vec[i].size(); j++){
      cout << vec[i][j] <<endl;
    }
    cout <<endl;
  }
}

double My_dPhi(double phi1, double phi2) {
  double dPhi = phi1 - phi2;
  if (dPhi >  M_PI) dPhi -= 2.*M_PI;
  if (dPhi < -M_PI) dPhi += 2.*M_PI;
  return dPhi;
}

double deltaR(double eta1, double phi1, double eta2, double phi2)
{
  double dEta = eta1 - eta2;
  double dPhi = My_dPhi(phi1,phi2);
  return sqrt(dEta*dEta+dPhi*dPhi);
}
