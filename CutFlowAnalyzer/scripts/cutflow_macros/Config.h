//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!  USER Configure Below        !
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

const int year = 2018;//Configure which year ntuples to run, options: 2017, 2018

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!  USER Configure Above        !
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!  Initialize variables for macros  !
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
Float_t luminosity;//Luminosity of a year
TString header = "";//header of plots

TString store;//Input directory for HighMassBKGShape
TString outFileTriggerSF = "";//output file of HighMassBKGShape
Float_t MC_ScaleFactors[1];//MC-Data SF for HighMassBKGShape
TString MC_files[1];//Input MC shape for HighMassBKGShape
TString DATA_files[1];//Input DATA shape for HighMassBKGShape

namespace BKG_cfg {

  inline void ConfigureInput( const int year ) {

    std::cout << "\nConfiguring inputs for year " << year << std::endl;

    if(year == 2018){
      luminosity = lumi_2018;
      store      = store_2018;
      for(int i = 0; i < 1; i++){
        MC_ScaleFactors[i] = MC_ScaleFactors_2018[i];
        MC_files[i]        = MC_files_2018[i];
      }
      for(int j = 0; j < 1; j++){
        DATA_files[j] = DATA_files_2018[j];
      }
    }//end 2018
    else{
      std::cout << "*** User input year is not 2018, please check. ***" << std::endl;
    }

    header         = header + "#bf{CMS} #it{Preliminary}    " + Form("%.1f", luminosity) + "fb^{-1} (13 TeV)";
    outFileTriggerSF = outFileTriggerSF + "TriggerZShape_" + Form("%d", year) + "_FINAL.root";

  } // End function

} // End namespace
