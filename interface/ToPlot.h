
#ifndef TOPLOT_H
        #define TOPLOT_H

#include "Dataset.h"

class ToPlot
{
private:

  TString selection_;
  TString varname_  ;
  TString xtitle_   ;
  TString ytitle_   ;
  TString baseline_ ;
  TString weights_  ;
  TString extra_    ;
  TString text_     ;
  TString text2_    ;
  int nxbins_;
  int nybins_;
  double xlo_;
  double xhi_;
  double ylo_;
  double yhi_;
  float tx1_ ;
  float ty1_ ;
  float tx2_ ;
  float ty2_ ;
  float t2x1_;
  float t2y1_;
  float t2x2_;
  float t2y2_;

  ToPlot();

public:

  //Are all these truly needed?
  ToPlot(TString s, TString v, TString x, TString y, TString b, TString w, TString e, int n, double xl, double xh, double yl, double yh);
  ToPlot(TString s, TString v, TString x, TString y, TString b, TString w, TString e, int n, double xl, double xh);
  ToPlot(TString s, TString v, TString x, TString b, TString w, TString e, int n, double xl, double xh);
  ToPlot(TString s, TString v, TString x, TString y, TString b, int n, double xl, double xh, double yl, double yh);
  ToPlot(TString s, TString v, TString x, TString w, TString e, int n, double xl, double xh);
  ToPlot(TString s, TString v, TString x, int n, double xl, double xh, double yl, double yh);
  ToPlot(TString s, TString v, TString x, int n, double xl, double xh);
  ToPlot(TString s, TString v, int n, double xl, double xh);
  ToPlot(TString s, TString v, TString b, TString w);
  
  ~ToPlot();

  //Setters
  //
  void setSelection(TString s) { selection_ = s; }
  void setVarname  (TString s) { varname_   = s; }
  void setBaseline (TString s) { baseline_  = s; }
  void setExtra    (TString s) { extra_     = s; }
  void setXtitle   (TString s) { xtitle_    = s; doConstructYtitle(); }
  void setText     (TString s) { text_      = s; }
  void setExtraText(TString s) { text2_     = s; }
  void setNxbins   (int     i) { nxbins_    = i; }
  void setNybins   (int     i) { nybins_    = i; }
  void setXlow     (double  d) { xlo_       = d; }
  void setXhigh    (double  d) { xhi_       = d; }
  void setYlow     (double  d) { ylo_       = d; }
  void setYhigh    (double  d) { yhi_       = d; }

  //Getters
  // 
  TString getSelection() const { return selection_; }
  TString getVarname  () const { return varname_  ; }
  TString getXtitle   () const { return xtitle_   ; }
  TString getYtitle   () const { return ytitle_   ; }
  TString getBaseline () const { return baseline_ ; }
  TString getWeights  () const { return weights_  ; }
  TString getExtra    () const { return extra_    ; } 
  TString getText     () const { return text_     ; } 
  TString getExtraText() const { return text2_    ; } 
  int     getNxbins   () const { return nxbins_   ; }
  int     getNybins   () const { return nybins_   ; }
  double  getXlow     () const { return xlo_      ; }
  double  getXhigh    () const { return xhi_      ; }
  double  getYlow     () const { return ylo_      ; }
  double  getYhigh    () const { return yhi_      ; }

  //Other
  //
  void initTexts();
  TString constructYtitle(const TString y, const double low, const double high, const int nb);
  void  doConstructYtitle() { ytitle_ = constructYtitle(xtitle_,xlo_,xhi_,nxbins_); }
  TString getFullCut(Dataset ds, TString lumiweight = "", double lumi = 1.0) const; 
  TString getCommonName(TString name);
  void makeSimpleXtitle();
  void assignAxisLimits(TString a = "X");

  friend std::ostream& operator<< (std::ostream &os, const ToPlot &t);

}; // class ToPlot


#endif

