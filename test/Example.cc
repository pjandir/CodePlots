
#include "../interface/DrawTree.h"
#include "../src/UserFunctions.cc"

//
// Example function to show how the package works
// There are four objects: Color, ToPlot, Dataset, and DrawTree
//   - Color is simply a holder for custom colors   
//     - This statement will show them: Color::plotTheColors();
//   - ToPlot holds the plotted variable, selection, plot dimensions at its core
//   - Dataset holds an individual physics dataset as well as a Color
//   - DrawTree is the driver of it all, incorporating the above three
//     - Use ToPlot to graph variable from Dataset(s)
// 
// The style used is the 2015 RunII CMS style    
//  

void Example() {
  
  //The object that draws it all
  DrawTree * dt = new DrawTree("tree",vError);

  //Set some of the various options
  //Many other options are available - see the DrawTree header
  dt->setLogy(true);
  dt->setDrawmcerr(true);
  dt->setDostack(true);
  dt->setLumi(1000);
  dt->setInframe(false);
  dt->setHasdata(true);
  dt->setDrawratio(true);

  //Custom function to add all datasets you want in a simple, concise way
  //See function to see how to add datasets to the DrawTree object by hand
  dt->autoAddDatasets("path/to/the/root/files","fullqcd ttbar wjets singlet zinv data","*.root");

  //Add (one or more) 'ToPlot' which sets the selection, plotted variable, plot dimensions 
  //Has some more options as well, including ability to use pre-defined options for variables
  //     
  //This will plot HT and MHT variables
  dt->addVar(ToPlot("MHT>200&&Leptons==0&&BTags>=0&&NJets>3&&HT>500&&JetID>0","HT","","","",50,500,2500));
  dt->addVar(ToPlot("MHT>200&&Leptons==0&&BTags>=0&&NJets>3&&HT>500&&JetID>0","MHT","","","",50,200,2200));

  //Function plots N-1 style in first argument - see function for full details
  //dt->Nminus1plots(ToPlot("HT>500$$MHT>200$$(Leptons==0)$$BTags>=0$$NJets>3$$MinDeltaPhi>0.5","HT","","","(isoPionTracks+isoElectronTracks+isoMuonTracks==0)&&(JetID>0)",40,0,4000),"$$");
   
  //Makes cutflow table with various options - see function for full details
  //dt->cutflow("1$$HT>500$$MHT>200$$(Leptons==0)$$NJets>3","BTags==0$$BTags==1$$BTags>=2","","No Cut$$HT>500$$MHT>200$$Lepton veto$$NJet>3$$NBjet==0$$NBjet==1$$NBjet>=2","");

  //Plot two sets of plots, with and without log y-scale
  dt->plot();
  dt->setLogy(false);
  dt->plot();

  //Delete the object, always
  delete dt;

  exit(0);

}

