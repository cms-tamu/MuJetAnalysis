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

void decodeFileName(const TString& fileName, TString mass_string, TString cT_string)
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
}
