
#include "../interface/DrawTree.h"
#include "../src/UserFunctions.cc"

void Example() {
  
//
// To see all the custom colors:  
// Color::plotTheColors();
//


  //The object that draws it all
  DrawTree * dt = new DrawTree("tree",vError);

  //Set the options
  dt->setLogy(true);
  dt->setDrawmcerr(true);
  dt->setDostack(true);
  dt->setLumi(1000);
  dt->setInframe(false);
  dt->setHasdata(true);
  dt->setDrawratio(true);

  //Custom function to add all datasets you want
  dt->autoAddDatasets("/data/strange2/pjandir/TreeMaker-Trees/LPC-CentralProdSkim-V4/","fullqcd ttbar wjets singlet zinv data","*.root");

  //Add 'ToPlot' which sets the selection, plotted variable, plot dimensions 
  dt->addVar(ToPlot("MHT>200&&Leptons==0&&BTags>=0&&NJets>3&&HT>500&&JetID>0","HT","","","",50,500,2500));
  dt->addVar(ToPlot("MHT>200&&Leptons==0&&BTags>=0&&NJets>3&&HT>500&&JetID>0","MHT","","","",50,200,2200));


  //Function plots N-1 style in first argument
  //dt->Nminus1plots(ToPlot("HT>500$$MHT>200$$(Leptons==0)$$BTags>=0$$NJets>3$$MinDeltaPhi>0.5","HT","","","(isoPionTracks+isoElectronTracks+isoMuonTracks==0)&&(JetID>0)",40,0,4000),"$$");
   
  //Makes cutflow table with various options 
  //dt->cutflow("1$$HT>500$$MHT>200$$(Leptons==0)$$NJets>3","BTags==0$$BTags==1$$BTags>=2","","No Cut$$HT>500$$MHT>200$$Lepton veto$$NJet>3$$NBjet==0$$NBjet==1$$NBjet>=2","");

  dt->setLogy(false);
  dt->plot();

  delete dt;

  exit(0);

}

