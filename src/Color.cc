
#include "../interface/Color.h"

Color::Color() {
  // Default constructor
}

Color::Color(int a1, int a2, int a3, int a4) :
    id_(a1)
{   
  r_ = a2/255.;
  g_ = a3/255.;
  b_ = a4/255.;
}   

//Static function to initialize all custom colors into vector of Colors
std::vector<Color> Color::init() {

  std::vector<Color> mycolors;

  //Define all custom colors 
  mycolors.push_back(Color(vNinerRed       , 175,  30,  44));
  mycolors.push_back(Color(vArsenalRed     , 234,  34,  18));//lightest
  mycolors.push_back(Color(vStanfordRed    , 140,  21,  21));//darkest
  mycolors.push_back(Color(vArgentineBlue  , 117, 170, 219));//sample
  mycolors.push_back(Color(vSharkBlue      ,   5,  83,  93));//'dark' teal
  mycolors.push_back(Color(vQuakesBlue     ,   0,  81, 186));//brighter
  mycolors.push_back(Color(vSabercatGreen  ,   0, 102,  51));
  mycolors.push_back(Color(vOregonGreen    ,   0,  79,  39));
  mycolors.push_back(Color(vIndianGreen    ,  19, 136,   8));//lightest
  mycolors.push_back(Color(vGiantOrange    , 242,  85,  44));//darkest
  mycolors.push_back(Color(vSharkOrange    , 243, 143,  32));//more yellowish
  mycolors.push_back(Color(vDutchOrange    , 255,  79,   0));//lightest
  mycolors.push_back(Color(vWarriorYellow  , 255, 204,  51));//darkest
  mycolors.push_back(Color(vAthleticYellow , 255, 216,   0));//lightest
  mycolors.push_back(Color(vUCRYellow      , 241, 171,   0));//gold-ish
  mycolors.push_back(Color(vKingsPurple    , 117,  59, 189));//lightest
  mycolors.push_back(Color(vKStatePurple   ,  79,  38, 131));//darkest
  mycolors.push_back(Color(vUCRPurple      ,  98,  74, 126));//dull
  mycolors.push_back(Color(vNeonGreen      ,  57, 255,  20));
  mycolors.push_back(Color(vNeonPink       , 213,  38, 181));
  mycolors.push_back(Color(vNeonOrange     , 255, 103,   0));
  mycolors.push_back(Color(vNinerGold      , 230, 190, 138));
  mycolors.push_back(Color(vKingsSilver    , 138, 141, 143));//darker
  mycolors.push_back(Color(vQuakesSilver   , 177, 180, 178));//lighter
  //  
  //mycolors.push_back(Color(9999            ,  50, 132, 191));//sample
  mycolors.push_back(Color(3004,255,253,208));//Giants Offwhite
  //Retired colors..
  ////mycolors.push_back(Color(vAthleticGreen  ,   0,  56,  49));//darkest
  ////mycolors.push_back(Color(vWarriorBlue    ,   4,  82, 156));

  return mycolors;
}

//Plot all custom colors
//Can call this static function without DrawTree object created beforehand (perhaps even recommended)
void Color::plotTheColors() {

  myp("Creating plot of all custom colors\n");
  ep::pts(vInfo);

  TCanvas * can = new TCanvas("can","",400,400);

  std::vector<Color> mycolors = init();
  std::vector<TColor *> theColors;
  std::vector<TH2I   *> hists;
  std::vector<TLine  *> vert;
  std::vector<TLine  *> hori;

  //Create all custom TColors
  for ( std::vector<Color>::const_iterator col = mycolors.begin(); col != mycolors.end(); ++col )
    theColors.push_back(col->convert());

  //Set initial values
  //TLine values
  int lcolor = kBlack;
  int lwidth = 3;
  //Logic for a RxC grid of colors
  //  - For now keep only 3 columns, as there are not enough colors to justify a fourth column
  int ncolors = mycolors.size();
  int columns = 3;
  int rows  = ncolors / columns;
  rows = ncolors % columns == 0 ? rows : rows + 1;

  //Create objects
  for ( std::vector<Color>::const_iterator itr = mycolors.begin() ; itr != mycolors.end() ; ++itr) {
    TString name = "hist"; name += itr->getId();
    hists.push_back(new TH2I(name.Data(),name.Data(),columns,0,columns*10,rows,0,rows*5));
  }
  //Create lines to separate the boxes
  TH2I * first = * hists.begin();
  int xmax = first->GetXaxis()->GetXmax();
  int ymax = first->GetYaxis()->GetXmax();
  for (int ix = 1; ix <= first->GetXaxis()->GetNbins()+1; ++ix ) {
    vert.push_back(new TLine(first->GetXaxis()->GetBinLowEdge(ix),0,first->GetXaxis()->GetBinLowEdge(ix),ymax));
  }
  for (int iy = 1; iy <= first->GetYaxis()->GetNbins()+1; ++iy ) {
    hori.push_back(new TLine(0,first->GetYaxis()->GetBinLowEdge(iy),xmax,first->GetYaxis()->GetBinLowEdge(iy)));
  }

  //Stylize the objects
  int bin = 0, binx = 1, biny = 0;
  for ( std::vector<TH2I *>::const_iterator itr = hists.begin() ; itr != hists.end() ; ++itr) {
    if   ( (bin)%columns==0 ) { binx = 1; ++biny; }
    else                      {           ++binx; }
    (*itr)->SetBinContent(binx,biny,mycolors[bin].getId()); 
    (*itr)->SetFillColor(mycolors[bin].getId()); 
    (*itr)->SetTitle("Custom Colors");
    (*itr)->SetStats(0);
    ++bin;
  }

  //Draw the objects
  for ( std::vector<TH2I *>::const_iterator itr = hists.begin() ; itr != hists.end() ; ++itr) {
    TString opt = "text a box";
    if ( itr != hists.begin() ) opt += " same";
    (*itr)->Draw(opt);
  }
  for ( std::vector<TLine *>::const_iterator itr = vert.begin() ; itr != vert.end() ; ++itr) {
    (*itr)->SetLineWidth(lwidth);
    (*itr)->SetLineColor(lcolor);
    (*itr)->Draw("same");
  }
  for ( std::vector<TLine *>::const_iterator itr = hori.begin() ; itr != hori.end() ; ++itr) {
    (*itr)->SetLineWidth(lwidth);
    (*itr)->SetLineColor(lcolor);
    (*itr)->Draw("same");
  }

  //Save it somewhere obvious
  can->SaveAs("AllCustomColors.pdf"); 

}

