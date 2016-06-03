
//Use this to link all objects together and run your code
//At command line can just do:
//$ root -b Run.C

{
  //Link all objects 
  gROOT->LoadMacro("../src/Dataset.cc++ ");
  gROOT->LoadMacro("../src/ToPlot.cc++  ");
  gROOT->LoadMacro("../src/Color.cc++   ");
  gROOT->LoadMacro("../src/DrawTree.cc++");
  gROOT->LoadMacro("../test/Example.cc++");

  //Run the actual function
  gROOT->ProcessLine("Example()");
}
