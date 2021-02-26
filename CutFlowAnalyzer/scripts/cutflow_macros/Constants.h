//!!!!!!!!!!!!!!!!!!!!!
//!  Common Constants !
//!!!!!!!!!!!!!!!!!!!!!
//Luminosity each year: unit: fb^-1
const double lumi_2018 = 59.7;

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!  Constants used exclusively in TriggerSF18.C     !
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//Mass range and bin size at high mass
const double       HM_m_min  = 76.;
const double       HM_m_max  = 107.;
const unsigned int HM_m_bins = 31;//bin size GeV

//Directory of histograms
TString store_2018 = "/scratch/user/ws13/TriggerSF/2018";

//Scale MC events to Data (Xsec*Lumi/tot MC evt)
//The order is important here: WZTo3LNu
Float_t MC_ScaleFactors_2018[1] = {0.02884334739};

//Color in final legend for each bkg process, same order as above
Color_t MC_Colors[1] = {4};

//The input files below contain histograms from running the cut-flow script (with TriggerSFPlot flag on) over MET dataset and WZ MC
//script: MuJetAnalysis/CutFlowAnalyzer/scripts/cutflow_macros/CutFlow_2018L2Mu23.C
//Same order as MC_ScaleFactors above
TString MC_files_2018[1] = {
  "TriggerSF_2018_WZTo3LNu.root"
};
//MET dataset
TString DATA_files_2018[1] = {
  "TriggerSF_2018MET_ABCD.root",
};
