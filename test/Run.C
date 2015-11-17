
//Link all objects 
{
  gROOT->LoadMacro("../src/Dataset.cc++ ");
  gROOT->LoadMacro("../src/ToPlot.cc++  ");
  gROOT->LoadMacro("../src/Color.cc++   ");
  gROOT->LoadMacro("../src/DrawTree.cc++");
  gROOT->LoadMacro("../test/TestIt.cc++ ");

  gROOT->ProcessLine("Example()");
}
