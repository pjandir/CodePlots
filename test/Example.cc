
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

  // ~~~~~~~
  //First create the object that does everything  
  DrawTree * dt = new DrawTree("events",vError);
  // ~~~~~~~

  // ~~~~~~~
  //Set some of the various options for the DrawTree object
  // - See the DrawTree header for usage info
  // - Many other options are available
  dt->setLogy(true);
  dt->setCmEnergy(7);
  dt->setDrawmcerr(true);
  dt->setDostack(true);
  dt->setLumi(50);
  dt->setInframe(false);
  dt->setHasdata(true);
  dt->setDrawratio(true);
  dt->setLumiName("EventWeight");
  // ~~~~~~~


  // ~~~~~~~
  //Add the Datasets one wants to plot/analyze
  //Multiple methods are available and are shown here
  //Note the two Dataset constructors available to the user
  // - Both must be given the full path/name of the file and TTree name

  //First, some helper strings
  TString path = "files/"; //path where the root files are located
  TString back = "*.root"; //back of the filename string
  TString tree = "events"; //name of the TTree inside files

  //Method 1)
  //Create a Dataset and add it directly to DrawTree 
  //Real data is added as data with color, marker, line, and weight options
  dt->addData(Dataset(path+"data"+back,"Data",kBlack,kFullDotLarge,1,40,1,tree));

  //Method 2)
  //Create a vector of Datasets first and then add to DrawTree
  //Background MC (i.e. simulation) is added with only color, marker, line, and tree options
  std::vector<Dataset> bg;
  bg.push_back(Dataset(path+"single_top"+back,"single top",vKingsPurple,1,tree));
  bg.push_back(Dataset(path+"dy"+back,"Drell-Yan",vNinerRed,1,tree));
  bg.push_back(Dataset(path+"wj"+back,"wjets",vSabercatGreen,1,tree));
  bg.push_back(Dataset(path+"qcd"+back,"QCD",vWarriorYellow,1,tree));
  dt->addBGMC(bg);
  //Can also create a Dataset and add file(s) to it
  Dataset diboson(path+"zz"+back,"Diboson",vGiantOrange,1,tree);
  diboson.addFile(path+"w?-*.root");
  dt->addBGMC(diboson);

  //Method 3)
  //Custom function to add all datasets you want in a simple, concise way
  //Not implemented here but is recommended if the user will be using the package heavily 
  //dt->autoAddDatasets("path/to/the/root/files","fullqcd ttbar wjets singlet zinv data","*.root");
 
  // ~~~~~~~


  // ~~~~~~~
  // The plot/analysis options available to user
  // One can make both plots and tables rather quickly and easily
  // An overview of both is given    
  
  // === Plots ===   
  //Add (one or more) 'ToPlot' which sets the selection, plotted variable, plot dimensions 
  //Has some more options as well, including ability to use pre-defined options for variables

  //Helper strings to apply selection
  //Note the selections use '&&' as 'AND'
  TString baseline = "NPrimaryVertices>0&&triggerIsoMu24&&Muon1_Pt>30"; //nominal baseline cuts
  TString lep = "&&NMuon+NElectron==1";					//require only one lepton
  TString kin = "&&NGoodJet>1&&HT>50&&MET>50";				//kinematic requirements
  TString cut = baseline + lep + kin;					//the full cut to apply
  TString extraweight = "1./40";					//scale bg to better match data here (arbitrary fudge factor)

  //Add ToPlot directly to DrawTree (same as Dataset)
  dt->addVar(ToPlot(cut,"Muon1_Pt","Lead-#mu p_{T} [GeV]",extraweight,"",25,0,500));
  dt->addVar(ToPlot(cut,"HT","",extraweight,"",60,0,600));
  dt->addVar(ToPlot(cut,"MET","",extraweight,"",30,0,300));

  //With all variables input can simply plot
  //Here output two sets of plots, with and without log y-scale
  dt->plot();
  dt->setLogy(false);
  dt->plot();

  //Alternate method to make plots 
  //Function creates "N-1" style plots given the selection given
  // - Style plots one variable from selection and uses the rest of the selection and repeats for entire selection
  // - Plot dimensions are handled by fixed internal selections in ToPlot
  // - Baseline selection is applied to all plots
  //dt->Nminus1plots(ToPlot("NMuon+NElectron==1$$NGoodJet>1$$HT>50$$MET>50","HT","",extraweight,baseline,0,0,0),"$$");
   
  // === Plots ===   


  // === Tables ===   
  //Can make table of event counts (raw or weighted -- user option) as well as relative ratios (also user option) for all Datasets in DrawTree
  //Table output is to either screen or file. Can also specify LaTeX file output

  //Two examples are shown here to show what kinds of tables can be made, both output to screen
  //The strings are cuts to applied separated by a '$$' delimiter
  //But method has a number of options, so please see it for more info/flexibility

  //Table 1)
  //A typical table a user might want to make  
  //The relative ratio the table can print shows the ratio from a previous cut  
  // - First string applies cut in sequence to the last cut while second applies cut only to the last cut from the *first* string
  // - For example
  //   o Here when 'NPrimaryVertices' is applied the ratio is events pass 'NPrimaryVertices' cut / events pass '1' cut
  //   o Then when 'triggerIsoMu24' is applied the ratio is events pass 'triggerIsoMu24' cut / events passed 'NPrimaryVertices' cut
  //   o The 'NGoodBJet*' cuts then show the ratio against the 'MET>50' cut 
  //The fourth string is an optional string of names for the cuts -- none are given here 
  dt->cutflow("1$$NPrimaryVertices$$triggerIsoMu24$$NMuon+NElectron==1$$Muon1_Pt>30$$NGoodJet>1$$HT>50$$MET>50","NGoodBJet==0$$NGoodBJet==1$$NGoodBJet>=2","","","");

  //Table 2)
  //Table to try to determine which cuts affect which datasets
  //Names are given in this instance
  dt->cutflow("1$$triggerIsoMu24","Muon1_Pt>24$$Muon1_Pt>30$$NGoodBJet==0$$NGoodBJet==1$$NMuon>0$$NMuon>1$$NGoodJet>0$$NGoodJet>2$$MET>80$$HT>100","","Start$$Pass Trigger$$LeadMu pT > 24$$LeadMu pT > 30$$Num BJet = 0$$Num BJet = 1$$Num Muon > 0$$Num Muon > 1$$Num Jet > 0$$Num Jet > 2$$MET > 80$$HT > 100","");

  //A sensitivity table can also be made to check how certain cuts affect signal sensitivity, see sens_table(...) for more details
  //No example is given here but the usage is similar to the cutflow tables shown above
  // === Tables ===   

  // ~~~~~~~

  
  // ~~~~~~~
  //Delete the object, always
  delete dt;
  // ~~~~~~~

  //Exit ROOT session
  exit(0);

}

