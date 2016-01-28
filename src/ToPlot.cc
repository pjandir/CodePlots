
#include "../interface/ToPlot.h"

ToPlot::ToPlot() {
  // Default constructor
}

//All the other constructors
ToPlot::ToPlot(TString s, TString v, TString x, TString y, TString b, TString w, TString e, int n, double xl, double xh, double yl, double yh) 
: selection_(s), varname_(v), xtitle_(x), ytitle_(y), baseline_(b), weights_(w), extra_(e), nxbins_(n), nybins_(0), xlo_(xl), xhi_(xh), ylo_(yl), yhi_(yh) 
{ 
  initTexts();
}

ToPlot::ToPlot(TString s, TString v, TString x, TString y, TString b, TString w, TString e, int n, double xl, double xh) 
: selection_(s), varname_(v), xtitle_(x), ytitle_(y), baseline_(b), weights_(w), extra_(e), nxbins_(n), nybins_(0), xlo_(xl), xhi_(xh), ylo_(0), yhi_(0) 
{ 
  initTexts();
}

ToPlot::ToPlot(TString s, TString v, TString x, TString b, TString w, TString e, int n, double xl, double xh) 
: selection_(s), varname_(v), xtitle_(x), ytitle_(""), baseline_(b), weights_(w), extra_(e), nxbins_(n), nybins_(0), xlo_(xl), xhi_(xh), ylo_(0), yhi_(0) 
{ 
  doConstructYtitle();
  initTexts();
}

ToPlot::ToPlot(TString s, TString v, TString x, TString w, TString e, int n, double xl, double xh) 
: selection_(s), varname_(v), xtitle_(x), ytitle_(""), baseline_(""), weights_(w), extra_(e), nxbins_(n), nybins_(0), xlo_(xl), xhi_(xh), ylo_(0), yhi_(0) 
{ 
  doConstructYtitle();
  initTexts();
}

ToPlot::ToPlot(TString s, TString v, TString x, TString y, TString b, int n, double xl, double xh, double yl, double yh) 
: selection_(s), varname_(v), xtitle_(x), ytitle_(y), baseline_(b), weights_(""), extra_(""), nxbins_(n), nybins_(0), xlo_(xl), xhi_(xh), ylo_(yl), yhi_(yh) 
{ 
  initTexts();
}

ToPlot::ToPlot(TString s, TString v, TString x, int n, double xl, double xh, double yl, double yh) 
: selection_(s), varname_(v), xtitle_(x), ytitle_(""), baseline_(""), weights_(""), extra_(""), nxbins_(n), nybins_(0), xlo_(xl), xhi_(xh), ylo_(yl), yhi_(yh)
{ 
  doConstructYtitle();
  initTexts();
}

ToPlot::ToPlot(TString s, TString v, TString x, int n, double xl, double xh) 
: selection_(s), varname_(v), xtitle_(x), ytitle_(""), baseline_(""), weights_(""), extra_(""), nxbins_(n), nybins_(0), xlo_(xl), xhi_(xh), ylo_(0), yhi_(0)
{ 
  doConstructYtitle();
  initTexts();
}

ToPlot::ToPlot(TString s, TString v, int n, double xl, double xh) 
: selection_(s), varname_(v), xtitle_(v), ytitle_(""), baseline_(""), weights_(""), extra_(""), nxbins_(n), nybins_(0), xlo_(xl), xhi_(xh), ylo_(0), yhi_(0)
{ 
  doConstructYtitle();
  initTexts();
}

ToPlot::ToPlot(TString s, TString v, TString b, TString w) 
: selection_(s), varname_(v), xtitle_(v), ytitle_(""), baseline_(b), weights_(w), extra_(""), nxbins_(0), nybins_(0), xlo_(0), xhi_(0), ylo_(0), yhi_(0)
{ 
  doConstructYtitle();
  initTexts();
}

ToPlot::~ToPlot() {
  // Default destructor
}

void ToPlot::initTexts() {
  text_  = "";
  text2_ = "";
  tx1_ = -1.;
  ty1_ = -1.;
  tx2_ = -1.;
  ty2_ = -1.;
  t2x1_ = -1.;
  t2y1_ = -1.;
  t2x2_ = -1.;
  t2y2_ = -1.;
}

TString ToPlot::constructYtitle(const TString y, const double low, const double high, const int nb) {

  double w = (high - low)/nb;
  //int ndecimals;
  int ndecimals = ( w >= 1 ) ? 0 : 1;
  if ( w < 0.1 ) ndecimals = 2;
  TString formstring = "%s / %.";
  formstring += ndecimals;
  formstring +="f%s";

  //Extract a unit, if any, from the x-title to use in y-title
  TString unit = "";
  TString dum  =  y;
  //dum.ReplaceAll("(","[");
  //dum.ReplaceAll(")","]");
  if ( dum.Contains("[") ) { 
    int one = dum.First("[");
    int two = dum.First("]");
    dum.Remove(two,(dum.Length()-two));
    dum.Replace(0,one+1,""); 
    unit += " ";
    if ( !dum.IsDigit() ) unit += dum;
  }

  //if ( y.Contains("/") || y.Contains("*") ) unit = ""; 
 
  TString fulltitle;
  fulltitle.Form(formstring.Data(), "Events", w, unit.Data());

  return fulltitle;
}

TString ToPlot::getFullCut(Dataset ds, TString lumiweight, double lumi) const {

  TString thecut = "";

  TString extraweight = ""; 
  if ( ds.getExtra().Contains("*") ) { 
    extraweight   = ds.getExtra();
    TString save  = ds.getExtra();
    int a1 = extraweight.Index("*");
    extraweight.Remove(0,a1);
    save.Remove(a1,save.Length());
    //cout << ds.getExtra() << endl; 
    //cout << extraweight << endl; 
    //cout << save << endl;
    ds.setExtra(save);
  }

  if ( lumiweight != "" ) { 
    thecut += "(";
    thecut += lumiweight;
    thecut += ")"; 
    char s[32]; sprintf(s,"%.6g",lumi);
    thecut += "*("; thecut += s; thecut += ")*";
  }
  thecut += "(";
  thecut += ds.getWeight();
  thecut += ")";
  thecut += "*(";
  thecut += ds.getSf();
  thecut += ")";
  if ( weights_ != "" ) { 
    thecut += "*(";
    thecut += weights_;
    if ( extraweight != "" ) thecut += extraweight;
    thecut += ")";
  }

  TString sel = "";
  if ( baseline_ == "" && extra_ == "" )
    sel = TCut(selection_.Data());
  else if ( baseline_ == "" ) 
    sel = TCut(selection_.Data()) && TCut(extra_.Data());
  else if ( extra_ == "" ) 
    sel = TCut(baseline_.Data()) && TCut(selection_.Data());
  else
    sel = TCut(baseline_.Data()) && TCut(selection_.Data()) && TCut(extra_.Data());

  if ( ds.getExtra() != "" ) { 
    if ( sel == "" ) sel += "1";
    sel += "&&";
    sel += ds.getExtra();     
  }

  if ( sel == "" ) sel = "1"; //In case there is no selection whatsoever
  thecut += "*((";
  thecut += sel;
  thecut += "))";


  return thecut;
}

//Add more variables as necessary 
TString ToPlot::getCommonName(TString name) {
  
  TString ret = "";
  if      ( name == "MET" || name == "METPt" ) ret = "met";
  else if ( name == "HT" || name == "HT30" ) ret = "ht";
  else if ( name == "MHT"  || name == "MHT30" ) ret = "mht";   
  else if ( name == "MHT/sqrt(HT30)"  || name == "MHT/sqrt(HT)" ) ret = "mht/sqrt(ht)";   
  else if ( name == "MET/sqrt(HT30)"  || name == "MET/sqrt(HT)" ) ret = "met/sqrt(ht)";   
  else if ( name == "METPt/CaloMETPt" ) ret = "pfmet/calomet";
  else if ( name == "METPhi" ) ret = "metphi";
  else if ( name == "njets" || name == "njets30" || name == "NJets" ) ret = "njets";
  else if ( name == "nbjets" || name == "nbjets30" || name == "nbjetsCSVM" || name == "BTags" ) ret = "nbjets";
  else if ( name == "Leptons" || name == "(Leptons)" || name == "@Muons.size()+@Electrons.size()" || name == "@Electrons.size()+@Muons.size()" 
         || name == "(@Muons.size()+@Electrons.size())" || name == "(@Electrons.size()+@Muons.size())" ) 
    ret = "nmuons+nelectrons";
  else if ( name == "NVtx" ) ret = "npv";
  else if ( name.Contains("MinDeltaPhiEta") && name.Contains("[3]") ) ret = "deltaphistar";
  else if ( name == "mindeltaphiN" || name == "minDeltaPhiN" || name == "minDeltaPhiN_pt30" || name == "minDeltaPhiN_MHT" ) ret = "mindeltaphin";
  else if ( name == "MinDeltaPhi" || name == "minDeltaPhi30" || name == "minDeltaPhi" || name == "minDeltaPhi_MHT" 
          || (name.Contains("MinDeltaPhiEta") && !name.Contains("-")) ) ret = "mindeltaphi";
  else if ( name.Contains("DeltaPhi[0]") || name.Contains("DeltaPhi1") ) ret = "deltaphi1";
  else if ( name.Contains("DeltaPhi[1]") || name.Contains("DeltaPhi2")  ) ret = "deltaphi2";
  else if ( name.Contains("DeltaPhi[2]") || name.Contains("DeltaPhi3") ) ret = "deltaphi3";
  else if ( name.Contains("DeltaPhi[3]") || name.Contains("DeltaPhi4") ) ret = "deltaphi4";
  else if ( name.Contains("DeltaPhi[4]") || name.Contains("DeltaPhi5") ) ret = "deltaphi5";
  else if ( name.Contains("DeltaPhi[5]") || name.Contains("DeltaPhi6") ) ret = "deltaphi6";
  else if ( name.Contains("deltaPhiN1") ) ret = "deltaphin1";
  else if ( name.Contains("deltaPhiN2") ) ret = "deltaphin2";
  else if ( name.Contains("deltaPhiN3") ) ret = "deltaphin3";
  else if ( name.Contains("deltaPhiN4") ) ret = "deltaphin4";
  else if ( name.Contains("deltaPhiN5") ) ret = "deltaphin5";
  else if ( name.Contains("deltaPhiN6") ) ret = "deltaphin6";
  else if ( name.Contains("DeltaPhiStar") ) ret = "deltaphistar";
  else if ( name.Contains("Jets[0].Pt") ) ret = "jetpt1";
  else if ( name.Contains("Jets[1].Pt") ) ret = "jetpt2";
  else if ( name.Contains("Jets[2].Pt") ) ret = "jetpt3";
  else if ( name.Contains("Jets[3].Pt") ) ret = "jetpt4";
  else if ( name.Contains("Jets[4].Pt") ) ret = "jetpt5";
  else if ( name.Contains("Jets[5].Pt") ) ret = "jetpt6";
  else if ( name.Contains("Jets[0].Phi") ) ret = "jetphi1";
  else if ( name.Contains("Jets[1].Phi") ) ret = "jetphi2";
  else if ( name.Contains("Jets[2].Phi") ) ret = "jetphi3";
  else if ( name.Contains("Jets[3].Phi") ) ret = "jetphi4";
  else if ( name.Contains("Jets[4].Phi") ) ret = "jetphi5";
  else if ( name.Contains("Jets[5].Phi") ) ret = "jetphi6";
  else if ( name.Contains("Jets[0].Eta") ) ret = "jeteta1";
  else if ( name.Contains("Jets[1].Eta") ) ret = "jeteta2";
  else if ( name.Contains("Jets[2].Eta") ) ret = "jeteta3";
  else if ( name.Contains("Jets[3].Eta") ) ret = "jeteta4";
  else if ( name.Contains("Jets[4].Eta") ) ret = "jeteta5";
  else if ( name.Contains("Jets[5].Eta") ) ret = "jeteta6";
  else ret = name;

  return ret;
}

//Add variables as necessary
void ToPlot::makeSimpleXtitle() {
  TString title, copy;
  if ( xtitle_ == "" ) copy = varname_;
  else 		       copy = xtitle_ ;
  title = getCommonName(copy);

  if      ( title == "met" ) title = "E_{T}^{miss} [GeV]";
  else if ( title == "ht"  ) title = "H_{T} [GeV]";
  else if ( title == "mht"  ) title = "H_{T}^{miss} [GeV]";   
  else if ( title == "mht/sqrt(ht)"  ) title = "H_{T}^{miss} / #sqrt{H_{T}} [#sqrt{GeV}]";   
  else if ( title == "met/sqrt(ht)"  ) title = "E_{T}^{miss} / #sqrt{H_{T}} [#sqrt{GeV}]";   
  else if ( title == "pfmet/calomet"  ) title = "PF E_{T}^{miss} / Calo E_{T}^{miss}";   
  else if ( title == "njets"  ) title = "N_{jet}";
  else if ( title == "nbjets" ) title = "N_{b-jet}";
  else if ( title == "nmuons+nelectrons" ) title = "N_{#mu+e}";
  else if ( title == "npv" ) title = "N_{PV}";
  else if ( title == "mindeltaphin" ) title = "#Delta#hat#phi_{min}";
  else if ( title == "mindeltaphi" ) title = "#Delta#phi_{min} [rad.]";
  else if ( title == "deltaphistar" ) title = "#Delta#phi* [rad.]";
  else if ( title == "deltaphi1" ) title = "#Delta#phi(jet_{1}, H_{T}^{miss}) [rad.]";
  else if ( title == "deltaphi2" ) title = "#Delta#phi(jet_{2}, H_{T}^{miss}) [rad.]";
  else if ( title == "deltaphi3" ) title = "#Delta#phi(jet_{3}, H_{T}^{miss}) [rad.]";
  else if ( title == "deltaphi4" ) title = "#Delta#phi(jet_{4}, H_{T}^{miss}) [rad.]";
  else if ( title == "deltaphi5" ) title = "#Delta#phi(jet_{5}, H_{T}^{miss}) [rad.]";
  else if ( title == "deltaphi6" ) title = "#Delta#phi(jet_{6}, H_{T}^{miss}) [rad.]";
  else if ( title == "deltaphin1" ) title = "#Delta#hat#phi_{1}";
  else if ( title == "deltaphin2" ) title = "#Delta#hat#phi_{2}";
  else if ( title == "deltaphin3" ) title = "#Delta#hat#phi_{3}";
  else if ( title == "deltaphin4" ) title = "#Delta#hat#phi_{4}";
  else if ( title == "deltaphin5" ) title = "#Delta#hat#phi_{5}";
  else if ( title == "deltaphin6" ) title = "#Delta#hat#phi_{6}";
  else if ( title == "jetpt1" ) title = "Jet_{1} p_{T} [GeV]";
  else if ( title == "jetpt2" ) title = "Jet_{2} p_{T} [GeV]";
  else if ( title == "jetpt3" ) title = "Jet_{3} p_{T} [GeV]";
  else if ( title == "jetpt4" ) title = "Jet_{4} p_{T} [GeV]";
  else if ( title == "jetpt5" ) title = "Jet_{5} p_{T} [GeV]";
  else if ( title == "jetpt6" ) title = "Jet_{6} p_{T} [GeV]";
  else if ( title == "jetphi1" ) title = "Jet_{1} #phi [rad.]";
  else if ( title == "jetphi2" ) title = "Jet_{2} #phi [rad.]";
  else if ( title == "jetphi3" ) title = "Jet_{3} #phi [rad.]";
  else if ( title == "jetphi4" ) title = "Jet_{4} #phi [rad.]";
  else if ( title == "jetphi5" ) title = "Jet_{5} #phi [rad.]";
  else if ( title == "jetphi6" ) title = "Jet_{6} #phi [rad.]";
  else if ( title == "jeteta1" ) title = "Jet_{1} #eta";
  else if ( title == "jeteta2" ) title = "Jet_{2} #eta";
  else if ( title == "jeteta3" ) title = "Jet_{3} #eta";
  else if ( title == "jeteta4" ) title = "Jet_{4} #eta";
  else if ( title == "jeteta5" ) title = "Jet_{5} #eta";
  else if ( title == "jeteta6" ) title = "Jet_{6} #eta";
  setXtitle(title);

}

void ToPlot::assignAxisLimits(TString a) {

  if ( rt::ContainsMathSym(varname_) ) {
    nxbins_ = 20; xlo_ = -9.5; xhi_ = 10.5; 
    return;
  }
  TString copy = varname_;
  copy = getCommonName(copy);
  int nb = 0;
  double xl = 0, xh = 0;

  if      ( copy == "met" ) {
    nb = 30; xl = 100; xh = 1600; 
  }
  else if ( copy == "ht" ) {
    nb = 40; xl = 200; xh = 4200; 
  } 
  else if ( copy == "mht" ) {
    nb = 30; xl = 100; xh = 1600; 
  } 
  else if ( copy == "mht/sqrt(ht)" ) {
    nb = 50; xl = 0; xh = 100; 
  } 
  else if ( copy == "met/sqrt(ht)" ) {
    nb = 50; xl = 0; xh = 100; 
  } 
  else if ( copy == "pfmet/calomet" ) {
    nb = 50; xl = 0; xh = 10; 
  } 
  else if ( copy == "njets" ) {
    nb = 15; xl = 2.5; xh = 17.5; 
  } 
  else if ( copy == "nbjets" ) {
    nb = 10; xl = -0.5; xh = 9.5; 
  } 
  else if ( copy.Contains("jetpt") ) {
    nb = 50; xl = 0; xh = 1000; 
  } 
  else if ( copy.Contains("jeteta") ) {
    nb = 25; xl = -5; xh = 5; 
  } 
  else if ( copy.Contains("jetphi") ) {
    nb = 50; xl = 0; xh = 5; 
  } 
  else if ( copy == "mindeltaphin" ) {
    nb = 50; xl = 0; xh = 50; 
  } 
  else if ( copy == "mindeltaphi" ) {
    nb = 50; xl = 0; xh = 5; 
  } 
  else if ( copy.Contains("deltaphistar") ) {
    nb = 30; xl = 0; xh = 3; 
  } 
  else if ( copy.Contains("deltaphin") ) {
    nb = 50; xl = 0; xh = 50; 
  } 
  else if ( copy.Contains("deltaphi") ) {
    nb = 50; xl = 0; xh = 5; 
  } 
  else if ( copy.Contains("phi") ) {
    nb = 50; xl = 0; xh = 5; 
  } 
  else if ( copy == "nmuons+nelectrons" ) {
    nb = 10; xl = -0.5; xh = 9.5; 
  } 
  else if ( copy == "npv" ) {
    nb = 40; xl = 0; xh = 40; 
  } 
  else {
    nb = 20; xl = -9.5; xh = 10.5; 
  }

  a.ToLower();
  if      ( a == "x" ) {
    nxbins_ = nb;
    xlo_   = xl;
    xhi_   = xh;
  }
  else if ( a == "y" ) {
    nybins_ = nb;
    ylo_   = xl;
    yhi_   = xh;
  }
  else {
    myp("Warning: Attempting to assign axis limits to unknown axis. See ToPlot.cc for more info");
    rt::pts(vWarning);
  }
  doConstructYtitle();

}


std::ostream& operator<< (std::ostream & os, const ToPlot & t) {
  char out[2000];
  sprintf(out,"---ToPlot Object---\n\tSelection: %s\n\tVariable: %s\n\tXtitle: %s\tYtitle: %s\n\tBaseline: %s\n\tWeights: %s\n\tExtra: %s\n\tNXbins: %i\tXlow: %f \tXhigh: %f \tNYbins: %i \tYlow: %f \tYhigh: %f \n"
             ,t.selection_.Data(),t.varname_.Data(),t.xtitle_.Data(),t.ytitle_.Data(),t.baseline_.Data(),t.weights_.Data(),t.extra_.Data(),t.nxbins_,t.xlo_,t.xhi_,t.nybins_,t.ylo_,t.yhi_); 
  os << out;
  return os; 
}

