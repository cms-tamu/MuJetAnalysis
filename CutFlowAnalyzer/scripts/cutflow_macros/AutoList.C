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

    //Assume newline format: */MSSMD_mH_125_mN1_60_mGammaD_5_cT_3_TuneCP5_13TeV-madgraph-pythia8/*
    //Need to create MSSMD_mH_125_mN1_60_mGammaD_5_cT_3.txt and put the path in

    //Assume newline format: */ALP_mH_125_mALP_30_PSWeights_TuneCP5_13TeV-madgraph-pythia8/*
    //Need to create ALP_mH_125_mALP_30.txt and put the path in

    //Assume newline format: */NMSSM_HToAATo4Mu_mH_150_mA_0p5_PSWeights_TuneCP5_13TeV-pythia8/*
    //Need to create ALP_mH_125_mALP_30.txt and put the path in

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
    }//end MSSMD
    else if ( newline.find("ALP") != string::npos && newline.find("_PSWeights") != string::npos ) {
      unsigned delimiterleft  = newline.find("ALP");
      unsigned delimiterright = newline.find("_PSWeights");
      string ntuplefilename = newline.substr(delimiterleft, delimiterright - delimiterleft);
      std::cout<<"file name: " << ntuplefilename << '\n';
      char ntuplefiledir[100];
      sprintf( ntuplefiledir, "./%s.txt", ntuplefilename.c_str() );
      FILE *ntuplefile = fopen(ntuplefiledir, "a");//append instead of overwrite in case the same signal has multiple dirs
      fprintf(ntuplefile, "%s\n", newline.c_str() );
      fclose(ntuplefile);
    }//end ALP
    else if ( newline.find("NMSSM") != string::npos && newline.find("_PSWeights") != string::npos ) {
      unsigned delimiterleft  = newline.find("NMSSM");
      unsigned delimiterright = newline.find("_PSWeights");
      string ntuplefilename = newline.substr(delimiterleft, delimiterright - delimiterleft);
      std::cout<<"file name: " << ntuplefilename << '\n';
      char ntuplefiledir[100];
      sprintf( ntuplefiledir, "./%s.txt", ntuplefilename.c_str() );
      FILE *ntuplefile = fopen(ntuplefiledir, "a");//append instead of overwrite in case the same signal has multiple dirs
      fprintf(ntuplefile, "%s\n", newline.c_str() );
      fclose(ntuplefile);
    }//end NMSSM
    else{
      std::cout<< "Above line doesn't match" << '\n';
    }

  }//end while
  infile.close();

}
