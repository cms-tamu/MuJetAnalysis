void runme(){
  gROOT->ProcessLine(".L jpsi.C");
  gROOT->ProcessLine("analysis("Charmonium_C.txt")");
  gROOT->ProcessLine(".q");
}
