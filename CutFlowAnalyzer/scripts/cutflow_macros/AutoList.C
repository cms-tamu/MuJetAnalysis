#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;
#include <algorithm>
#include <stdlib.h>
#include <math.h>

void AutoList(){
  ifstream infile;
	infile.open("/home/ws13/input.txt");
  int linecount = 0;

  while ( !infile.eof() ) {
    std::string newline;
    std::getline(infile, newline);
    linecount++;
    std::cout<<"line #"<< linecount << ": " << newline << '\n';

    //Assume newline format: /scratch/user/hyunyong/MSSMD_mH_125_mN1_60_mGammaD_5_cT_3_TuneCP5_13TeV-madgraph-pythia8/Run2_2017_SA_noVtxCut/200522_214055/0000
    //Need to create MSSMD_mH_125_mN1_60_mGammaD_5_cT_3.txt and put the path in
    if ( newline.find("MSSMD") != string::npos && newline.find("_Tune") != string::npos ) {
      unsigned delimiterleft  = newline.find("MSSMD");
      unsigned delimiterright = newline.find("_Tune");
      string ntuplefilename = newline.substr(delimiterleft, delimiterright - delimiterleft);
      std::cout<<"file name: " << ntuplefilename << '\n';
      char ntuplefiledir[100];
      sprintf( ntuplefiledir, "./%s.txt", ntuplefilename.c_str() );
      FILE *ntuplefile = fopen(ntuplefiledir, "a");//append instead of overwrite in case the same signal has multiple dirs
      fprintf(ntuplefile, "%s\n", newline.c_str() );
      fclose(ntuplefile);
    }//end if
    else{
      std::cout<< "Above line doesn't match" << '\n';
    }

  }//end while
  infile.close();

}
