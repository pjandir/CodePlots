
#include "../interface/Dataset.h"

Dataset::Dataset() {
  // Default constructor
  // Should not be used
} 

Dataset::Dataset(TString n, TString l, int c, int ms, int ls, double w, double sf, TString t) 
: name_(n), label_(l), extra_(""), color_(c), markstyle_(ms), linestyle_(ls), weight_(w), scalefactor_(sf), special_(0.)
{
  //Error checks
  if ( name_ == "" ) {
    myp("Error: Dataset has been given no name! Exiting.\n\n");
    rt::pts(vError);
    exit(0);
  }
  if ( label_ == "" ) {
    myp("Error: Dataset has been given no label! Exiting.\n\n");
    rt::pts(vError);
    exit(0);
  }

  // Constructor stuff
  h_ = 0;
  h2D_ = 0;
  label_.ReplaceAll(")","");
  label_.ReplaceAll("(","");
  label_.ReplaceAll(",","");
  label_.ReplaceAll("]","");
  label_.ReplaceAll("[","");
  extractExtra( );
  setTree     (t);
  setLegname  ( );

}

Dataset::Dataset(TString n, TString l, int c, double w, TString t) 
: name_(n), label_(l), color_(c), markstyle_(kFullDotMedium), linestyle_(1), weight_(w), scalefactor_(1.), special_(0.)
{
  //Error checks
  if ( name_ == "" ) {
    myp("Error: Dataset has been given no name! Exiting.\n\n");
    rt::pts(vError);
    exit(0);
  }
  if ( label_ == "" ) {
    myp("Error: Dataset has been given no label! Exiting.\n\n");
    rt::pts(vError);
    exit(0);
  }

  // Constructor stuff
  h_ = 0;
  h2D_ = 0;
  label_.ReplaceAll(")","");
  label_.ReplaceAll("(","");
  label_.ReplaceAll(",","");
  label_.ReplaceAll("]","");
  label_.ReplaceAll("[","");
  extractExtra( );
  setTree     (t);
  setLegname  ( ) ;
}

Dataset::~Dataset() {
  // Default destructor
  if ( h_    != 0 ) delete  h_  ;
  if ( h2D_  != 0 ) delete  h2D_;
  if ( ch_   != 0 ) { ch_->Clear(); /*ch->Delete();*/ }
}

//Does it exist
bool Dataset::isTree() const {
  if ( !( (ch_) && (!ch_->IsZombie()) ) ) return false;
  else return true; 
}
//Does it exist
bool Dataset::isHist() const {
  if ( !( (h_) && (!h_->IsZombie()) ) ) return false;
  else return true; 
}
//Does it exist
bool Dataset::isHist2D() const {
  if ( !( (h2D_) && (!h2D_->IsZombie()) ) ) return false;
  else return true; 
}

void Dataset::setTree(TString treename) {
  TChain * tree = new TChain(treename); //TODO: Make this more global!
  int nfiles = tree->Add(name_);

  //Error checks
  if ( !( (tree) && (!tree->IsZombie()) ) ) {
    myp("Error: TChain not loaded properly for sample [%s]! Exiting. \n\n",name_.Data());
    rt::pts(vError); 
    exit(0);
  }
  if ( nfiles < 1 ) {
    myp("Error: TChain did not add any files matching this name [%s]. Exiting.\n\n",name_.Data());
    rt::pts(vError);
    exit(0);
  }

  TString sfile = ( nfiles == 1 ) ? "file" : "files" ; 
  ch_ = (TChain *) tree->Clone();
  myp("New Dataset created: %s\n --> Dataset [%s] has %12i entries in %3i %s\n",name_.Data(),label_.Data(),(int)ch_->GetEntries(),nfiles,sfile.Data());
  rt::pts(vError); 

}

void Dataset::setLegname() {

  TString copy = label_;
  copy.ReplaceAll(" ","");
  copy.ReplaceAll("+","");
  copy.ToLower(); 

  if ( copy == "ttbar" || copy == "tt" ) legname_ = "t#bar{t}";
  else if ( copy == "qcd" ) legname_ = "QCD";
  else if ( copy == "wjets" || copy == "wjet" ) legname_ = "W+jets";
  else if ( copy == "zjets" || copy == "zinv" || copy == "znunu" || copy == "zjet" ) legname_ = "Z#rightarrow#nu#bar{#nu}";
  else if ( copy == "singlet" || copy == "singletop" ) legname_ = "Single top";
  else if ( copy == "lostlep" ) legname_ = "Lost Lepton";
  else if ( copy == "hadtau" ) legname_ = "#splitline{Hadronic}{#tau lepton}";
  else if ( copy == "other" ) legname_ = "Other";
  else if ( copy.Contains("t1") && !copy.Contains("qcd") ) {
/*
    TString aname = rt::GetFileName(name_);
    aname.ReplaceAll("-","_");  
    aname.ReplaceAll(".","_");  
*/
    
    TObjArray * files1 = ch_->GetListOfFiles();
    TIter next1(files1);
    TChainElement * ele1 = 0;
    ele1 = (TChainElement*) next1();
    ///cout << ele1->GetTitle() << " " << ele1->GetName() << endl;
    TString aname = rt::GetFileName(ele1->GetTitle());
    aname.ReplaceAll("-","_");  
    aname.ReplaceAll(".","_");  

    int a1 = aname.Index("SMS_T1");
    if ( copy.Contains("tree") ) a1 = aname.Index("T1");
    TString copy1 = aname;
    copy1.Remove(0,a1+6);
    TString model = copy1;
    TString mgl  = copy1;
    TString mlsp = copy1;
    int a2 = model.Index("_");
    model.Remove(a2);
    //a1 = mgl.Index("mGl_");
    //a1 = mgl.Index("mGluino_");
    a1 = mgl.Index("_");
    mgl.Remove(0,a1+1);
    mlsp = mgl;
    a2 = mgl.Index("_");
    mgl.Remove(a2);
    //a1 = mlsp.Index("mLSP_");
    a1 = mlsp.Index("_");
    mlsp.Remove(0,a1+1);
    a2 = mlsp.Index("_");
    mlsp.Remove(a2);
    TString res = model;
    legname_ += model; legname_ += " ["; legname_ += mgl; legname_ += ","; legname_ += mlsp; legname_ += "]"; 
  }
  else if ( copy.Contains("t2") && !copy.Contains("qcd") ) {
    TString aname = rt::GetFileName(name_);
    aname.ReplaceAll("-","_");  
    aname.ReplaceAll(".","_");  

    int a1 = aname.Index("SMS_T2");
    TString copy1 = aname;
    copy1.Remove(0,a1+4);
    TString model = copy1;
    TString mgl  = copy1;
    TString mlsp = copy1;
    int a2 = model.Index("_");
    model.Remove(a2);
    a1 = mgl.Index("mStop_");
    mgl.Remove(0,a1+6);
    a2 = mgl.Index("_");
    mgl.Remove(a2);
    a1 = mlsp.Index("mLSP_");
    mlsp.Remove(0,a1+5);
    a2 = mlsp.Index("_");
    mlsp.Remove(a2);
    TString res = model;
    legname_ += model; legname_ += " ["; legname_ += mgl; legname_ += ","; legname_ += mlsp; legname_ += "]"; 
  }
  else legname_ = label_;

}

void Dataset::addFile(TString s) {

  if ( ! isTree() ) {
    myp("Error: TChain does not exist for this dataset! Exiting.\n\n");
    rt::pts(vError);
    exit(0);
  }  

  TObjArray * files = ch_->GetListOfFiles();
  TIter next(files);
  TChainElement * ele = 0;
  while ( (ele = (TChainElement*) next() ) ) {
    if ( rt::GetFileName(s) == rt::GetFileName(ele->GetTitle()) ) {
      myp("Error: File has already been added to this TChain! Exiting.\n\n");
      rt::pts(vError);
      exit(0);
    }
  }

  double n1 = ch_->GetEntries();
  ch_->Add(s);
  double n2 = ch_->GetEntries();

  if ( rt::AreEqualAbs(n1,n2) ) {
    myp("     Additional file pattern to be appended to existing dataset [%s] has zero entries --> Not added to dataset!\n",label_.Data());
    rt::pts(vError);
  }
  else {
    myp("     Additional file pattern appended to existing dataset [%s] --> Dataset has %12i entries in %3i files\n",label_.Data(),(int)n2,int(files->GetEntries()));
    rt::pts(vError);
  }

  //delete files;
  delete   ele;
}

TH1D * Dataset::getHist() const {
  if ( !isHist() ) {
    myp("Error: Histogram does not exist for this dataset! Exiting.\n\n");
    rt::pts(vError);
    exit(0);
  }
  TH1D * ret = (TH1D *) h_->Clone();
  return ret;
}

TH1D * Dataset::getHist() {
  if ( !isHist() ) {
    myp("Error: Histogram does not exist for this dataset! Exiting.\n\n");
    rt::pts(vError);
    exit(0);
  }
  return h_;
}

TH2D * Dataset::getHist2D() {
  if ( !isHist2D() ) {
    myp("Error: Histogram 2D does not exist for this dataset! Exiting.\n\n");
    rt::pts(vError);
    exit(0);
  }
  return h2D_;
}

TChain * Dataset::getTree() {
  if ( !isTree() ) {
    myp("Error: TChain does not exist for this dataset! Exiting.\n\n");
    rt::pts(vError);
    exit(0);
  }
  return ch_;
}

double Dataset::getFullEntries() {
  if ( !isHist() ) {
    myp("Error: Histogram does not exist for this dataset! Exiting.\n\n");
    rt::pts(vError);
    exit(0);
  }
  return h_->Integral(0,h_->GetNbinsX()+1);
}

//TODO: Need to handle error bars here much, much better!
void Dataset::addOverflow() {
  if ( !isHist() ) {
    myp("Error: Histogram does not exist for this dataset! Exiting.\n\n");
    rt::pts(vError);
    exit(0);
  }
  int nbins = h_->GetNbinsX();
  h_->SetBinContent(nbins,h_->GetBinContent(nbins)+h_->GetBinContent(nbins+1));
  h_->SetBinError(nbins,sqrt(h_->GetBinError(nbins)*h_->GetBinError(nbins)+h_->GetBinError(nbins+1)*h_->GetBinError(nbins+1)));
}

void Dataset::setHistLineColor() {
  if ( !isHist() ) {
    myp("Error: Histogram does not exist for this dataset! Exiting.\n\n");
    rt::pts(vError);
    exit(0);
  }
  h_->SetLineColor(color_);
  h_->SetLineStyle(linestyle_);
  h_->SetLineWidth(2);
}

void Dataset::setHistMarkColor() {
  if ( !isHist() ) {
    myp("Error: Histogram does not exist for this dataset! Exiting.\n\n");
    rt::pts(vError);
    exit(0);
  }
  h_->SetMarkerColor(color_);
  h_->SetMarkerStyle(markstyle_);
}

void Dataset::setHistFillColor() {
  if ( !isHist() ) {
    myp("Error: Histogram does not exist for this dataset! Exiting.\n\n");
    rt::pts(vError);
    exit(0);
  }
  h_->SetFillColor(color_);
}

void Dataset::setHistLineAndMarkColor() {
  if ( !isHist() ) {
    myp("Error: Histogram does not exist for this dataset! Exiting.\n\n");
    rt::pts(vError);
    exit(0);
  }
  h_->SetLineColor(color_);
  h_->SetLineStyle(linestyle_);
  h_->SetLineWidth(2);
  h_->SetMarkerColor(color_);
  h_->SetMarkerStyle(20);
}

void Dataset::extractExtra() {

  if ( name_.Contains("$") ) {

    //careful...need to clean up memory after tokenize
    TObjArray * substrs = name_.Tokenize("$");
    if ( substrs->At(1) == 0 || substrs->At(2) == 0 ) {
      myp("Hmm, the attempted extraction of signal masses failed. Exiting.");
      rt::pts(vError); 
      exit(0);
    }

    int index_mlsp = 2; 
    TString mintermediate = "";
    if ( substrs->At(3) != 0) {
      index_mlsp=3;
      mintermediate = TString(substrs->At(2)->GetName());
    }
    TString m0 =  TString(substrs->At(1)->GetName());
    TString m12 = TString(substrs->At(index_mlsp)->GetName());

    delete substrs;  
    extra_ = "(";
    extra_ += "m0=="; 
    extra_ += m0;
    extra_ += "&&";
    extra_ += "m12=="; 
    extra_ += m12;
    if ( mintermediate != "" ) {
      extra_ += "&&";
      extra_ += "mIntermediate==";
      extra_ += mintermediate;
    } 
    extra_ += ")";

    int rem = name_.Index("$");
    name_.Remove(rem,name_.Length());
  }
  else if ( name_.Contains("#") ) {
    TObjArray * substrs = name_.Tokenize("#");
    if ( substrs->At(1) == 0 ) { 
      myp("Hmm, the attempted extraction of extra dataset cuts failed. Exiting.");
      rt::pts(vError); 
      exit(0);
    }

    TString copy = name_;
    int rem = copy.Index("#");
    copy.Remove(0,rem+1);
    extra_ = copy;
    name_.Remove(rem,name_.Length());
    delete substrs;  
  }
  else {
    extra_ = "";
  }

}

void Dataset::project(TString n, TString var, TString cut, int nbins, double lo, double hi, bool forcutflow) {

  //Error checks
  if ( !isTree() ) { 
    myp("Error: TChain not loaded for sample [%s]! Exiting. \n\n",name_.Data());
    rt::pts(vError); 
    exit(0);
  }  

  n.ReplaceAll("\\","_");
  n.ReplaceAll("+","_");
  n.ReplaceAll("-","_");
  n.ReplaceAll("*","_");
  n.ReplaceAll("/","_");
  n.ReplaceAll("(","_");
  n.ReplaceAll(")","_");
  n.ReplaceAll("[","_");
  n.ReplaceAll("]","_");
  n.ReplaceAll(">","_");

  TString hname = label_;
  hname += "_";
  hname += n;
  TH1D * hist = new TH1D(hname,hname,nbins,lo,hi);
  hist->Sumw2();
  ch_->Project(hname,var,cut);
  float percent = hist->GetEntries() / ch_->GetEntries() * 100;
  float hint = hist->Integral(0,hist->GetNbinsX()+1);
  if ( !forcutflow ) {
    if ( ch_->GetEntries() > 0 ) 
      myp("%10s passed entries: %10.0f raw, %10f weighted [ %3.1f %% of total dataset ] \n",label_.Data(),hist->GetEntries(),hint,percent);
    else 
      myp("%10s passed entries: %10s    :    Dataset itself is empty \n",label_.Data(),"NULL");
    rt::pts(vError);
    if ( ch_->GetEntries() > 0 ) { 
      myp("\t      => full cut:      %s\n",cut.Data());
      rt::pts(vError);
    }
    if ( label_.Contains("Data") ) { myp("\n"); rt::pts(vError); }
  }
  setHist(hist);

}

TH1D * Dataset::project_ret(TString n, TString var, TString cut, int nbins, double lo, double hi, bool forcutflow) {

  //Error checks
  if ( !isTree() ) { 
    myp("Error: TChain not loaded for sample [%s]! Exiting. \n\n",name_.Data());
    rt::pts(vError); 
    exit(0);
  }  

  n.ReplaceAll("\\","_");
  n.ReplaceAll("+","_");
  n.ReplaceAll("-","_");
  n.ReplaceAll("*","_");
  n.ReplaceAll("/","_");
  n.ReplaceAll("(","_");
  n.ReplaceAll(")","_");
  n.ReplaceAll(">","_");

  TString hname = label_;
  hname += "_";
  hname += n;
  TH1D * hist = new TH1D(hname,hname,nbins,lo,hi);
  hist->Sumw2();
  ch_->Project(hname,var,cut);
  float percent = hist->GetEntries() / ch_->GetEntries() * 100;
  float hint = hist->Integral(0,hist->GetNbinsX()+1);
  if ( !forcutflow ) {
    if ( ch_->GetEntries() > 0 ) 
      myp("%10s passed entries: %10.0f raw, %10f weighted [ %3.1f %% of total dataset ] \n",label_.Data(),hist->GetEntries(),hint,percent);
    else 
      myp("%10s passed entries: %10s    :    Dataset itself is empty \n",label_.Data(),"NULL");
    rt::pts(vError);
    if ( ch_->GetEntries() > 0 ) { 
      myp("\t      => full cut:      %s\n",cut.Data());
      rt::pts(vError);
    }
    if ( label_.Contains("Data") ) { myp("\n"); rt::pts(vError); }
  }
 
  //Have no idea why but if project is called before this one, have to re-set hist again
  //setHistFillColor();
  setHist(h_);
  return hist;

}

void Dataset::project2D(TString n, TString var, TString cut, int nbinsx, double *binx, int nbinsy, double *biny) {

  //Error checks
  if ( !isTree() ) { 
    myp("Error: TChain not loaded for sample [%s]! Exiting. \n\n",name_.Data());
    rt::pts(vError); 
    exit(0);
  }  

  TString hname = label_;
  hname += "_";
  hname += n;
  TH2D * hist = new TH2D(hname,hname,nbinsx,binx,nbinsy,biny);
  hist->Sumw2();
  ch_->Project(hname,var,cut);
  myp("%10s passed entries: %10.0f raw, %10f weighted\n",label_.Data(),hist->GetEntries(),hist->Integral());
  rt::pts(vInfo);
  myp("\t      => full cut:      %s\n",cut.Data());
  rt::pts(vInfo);
  setHist(hist);

}

