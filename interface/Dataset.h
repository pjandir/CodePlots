
#ifndef DATASET_H
        #define DATASET_H

#include "HelpDraw.h"

class Dataset
{
private:

  TString name_   ;
  TString label_  ;
  TString legname_;
  TString extra_  ;
  int color_    ;
  int markstyle_;
  int linestyle_;
  double weight_     ;
  double scalefactor_;
  double special_    ;
  TChain * ch_;
  TH1D * h_  ;
  TH2D * h2D_;

  Dataset();

public:
  Dataset(TString n, TString l, int c, int ms = kFullDotMedium, int ls = 1, double w = 1., double sf = 1., TString t = "tree");
  Dataset(TString n, TString l, int c, double w, TString t = "tree");
  ~Dataset();

  //Setters
  //
  void setLabel (TString s) { label_       = s; }
  void setExtra (TString s) { extra_       = s; }
  void setColor     (int i) { color_       = i; } 
  void setMarkstyle (int i) { markstyle_   = i; }
  void setLinestyle (int i) { linestyle_   = i; }
  void setWeight (double d) { weight_      = d; }
  void setSf     (double d) { scalefactor_ = d; }
  void setSpecial(double d) { special_     = d; }
  //Not quite the 'normal' setters
  void setLegname(); 
  void setHist  (TH1D * h1d) { h_   = (TH1D*) h1d->Clone(); }
  void setHist  (TH2D * h2d) { h2D_ = (TH2D*) h2d->Clone(); }
  void setTree  (TString treename);

  //Getters
  //
  TString    getName() const { return name_       ; }
  TString   getLabel() const { return label_      ; }
  TString getLegname() const { return legname_    ; }
  int       getColor() const { return color_      ; }
  int   getMarkstyle() const { return markstyle_  ; }
  int   getLinestyle() const { return linestyle_  ; }
  double   getWeight() const { return weight_     ; }
  double       getSf() const { return scalefactor_; }
  double  getSpecial() const { return special_    ; }
  TString   getExtra() const { return extra_      ; }
  TH1D     * getHist(); 
  TH1D     * getHist() const; 
  TH2D     * getHist2D(); 
  TChain   * getTree();
  
  //Other
  //
  bool isTree  () const;
  bool isHist  () const;
  bool isHist2D() const;
  double getFullEntries();
  void addFile(TString s);
  void addOverflow();
  void extractExtra();
  
  void setHistLineColor();
  void setHistMarkColor();
  void setHistFillColor();
  void setHistLineAndMarkColor();

  void  project    (TString hname, TString var, TString cut, int nbins, double lo, double hi, bool forcutflow = false);
  TH1D* project_ret(TString hname, TString var, TString cut, int nbins, double lo, double hi, bool forcutflow = false);
  void project2D(TString hname, TString var, TString cut, int nbinsx, double * binx, int nbinsy, double * biny);

};  // class Dataset 

#endif

