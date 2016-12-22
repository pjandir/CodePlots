
#ifndef DRAWTREE_H
        #define DRAWTREE_H

//Objects
#include "Color.h"
//Helper class
#include "Style.h"

class DrawTree
{
private:

  //--
  bool savegraph1_   ; // Save the graphs in a subdir with file extension defined below.
  bool savegraph2_   ; // Save the graphs in a subdir with file extension defined below.
  bool savegraph3_   ; // Save the graphs in a root file
  bool drawratio_    ; // Draw ratio plot at bottom of data/MC(-esque) plots
  bool drawleg_      ; // Draw legend
  bool drawlegborder_; // Draw legend border size
  bool drawmcerr_    ; // Draw BG MC error bands
  bool drawlatex_    ; // Draw 'standard' LaTeX box ("CMS Preliminary sqrt(s) etc.")
  bool drawline_     ; // Draw a line
  bool logz_         ; // Set z axis to log. 
  bool logy_         ; // Set y axis to log. 
  bool logx_         ; // Set x axis to log--not really used.
  bool dobatch_      ; // Set dummy TCanvas to batch mode. 
  bool dostack_      ; // Stack the histograms (BG MC) or not 
  bool resetlegend_  ; // Allow a dynamic reset of the legend position, ignoring user input
  bool addoverflow_  ; // Add overflow bin to last visible bin
  bool addpgnumbers_ ; // Add page numbers to canvas (only if savegraph2_ enabled)
  bool pdfmode_      ; // Add first and last (blank) plots to make large pdf plotting easier
  bool hasdata_      ; // If there is data to be plotted
  bool istwikionly_  ; // For plot header: format text for Twiki pages only
  bool isprelim_     ; // For plot header: format text with Preliminary
  bool inframe_      ; // For plot header: draw 'CMS' inside plot frame or outside 
  bool luminorm_     ; // Normalize MC by lumi (if no data is plotted)
  bool useredxtitle_ ; // Use a simple string to TLatex function to get x titles (discretion adivsed)
  //--
  int cmEnergy_      ; // sqrt(s) energy of LHC for plot text
  int pagenumber_    ; // (Internal) The page number to add to canvas
  int canvaswidth_   ; // Width of the canvas
  int canvasheight_  ; // Height of the canvas
  int ratiopadheight_; // Height of the ratio plot pad (added to canvas height) 
  int plotnumber_    ; // (Internal) Dummy value to number plots 
  //--
  float legx1_       ; // Set xNDC1 for legend. Low of 0.7 
  float legx2_       ; // Set xNDC2 for legend.
  float legy1_       ; // Set yNDC1 for legend. Low of 0.5 
  float legy2_       ; // Set yNDC2 for legend. 
  float xlabeloffset_; // Set label offset for x-axis 
  float xtitleoffset_; // Set title offset for x-axis (was 0.97)
  float ylabeloffset_; // Set label offset for y-axis (was 0.015)
  float ytitleoffset_; // Set title offset for y-axis (was 0.97)
  float rightmargin_ ; // Set pad margin
  float leftmargin_  ; // Set pad margin
  float topmargin_   ; // Set pad margin
  float bottommargin_; // Set pad margin
  float textinsidex_ ; // Set xNDC for text box written inside plot
  float textinsidey_ ; // Set yNDC for text box written inside plot
  float textinside2x_; // Set xNDC for text box written inside plot
  float textinside2y_; // Set yNDC for text box written inside plot
  float pavetextx1_  ; // Set xNDC1 for pave text box written inside plot
  float pavetextx2_  ; // Set xNDC2 for pave text box written inside plot
  float pavetexty1_  ; // Set yNDC1 for pave text box written inside plot
  float pavetexty2_  ; // Set yNDC2 for pave text box written inside plot
  float pgnumberx_   ; // Set xNDC for page number text
  float pgnumbery_   ; // Set yNDC for page number text
  float ratiomin_    ; // Minimum y-value for ratio plot
  float ratiomax_    ; // Maximum y-value for ratio plot
  float inflateymax_ ; // Inflate y-axis range
  float renorm_      ; // Set renormalization factor. 1 for none, and -1 for total events.
  float histmax_     ; // User input maximum for plotted histogram
  float histmin_     ; // User input minimum for plotted histogram
  //--
  double lumi_ ; // Data scale in pb
  //--
  TString outfolder_   ; // Set which directory graphs are saved to
  TString filemod_     ; // A string to modify file names of produced plots
  TString file1ext_    ; // Set file type (extension) of graphs for individual files, see--> https://root.cern.ch/root/htmldoc//TPad.html#TPad:SaveAs
  TString file2ext_    ; // Set file type (extension) of graphs for a single continuous file
  TString file2name_   ; // Name of single continuous file and root file
  TString textinside_  ; // Text to be written inside plot
  TString textinside2_ ; // Text to be written inside plot
  TString pavetext_    ; // Text to be written inside pave text box (alternate of above, this has a box around it)
  TString ratioytitle_ ; // y-title of ratio plot at bottom of histogram (Data/MC) 
  TString luminame_    ; // Name of the lumi weight variable in the tree
  TString treename_    ; // Name of the TTree (inc folders) in the file
  //--
  TDatime     thetime_ ; // The time

  TCanvas   * thecan_  ; // Standard canvas
  TLegend   * theleg_  ; // Standard legend
  TLatex    * text1_   ; // Inside a plot text 
  TLatex    * text2_   ; // Plot header text
  TLatex    * text3_   ; // Page number text
  TLatex    * text4_   ; // Unused, for now
  TPaveText * ptext_   ; // Alternate to inside text
  TFile     * fileout_ ; // Standard output root file
  TH1D      * ratio_   ; // Standard ratio plot
  TLine     * ratiolin_; // Standard ratio plot line at 1
  THStack   * thestack_; // The stack of all datasets 
  TH1D      * totalsm_ ; // Sum of total SM MC
  TGraphErrors * mcerr_; // Error on SM MC
  
  std::vector<ToPlot>  thevar_;
  std::vector<TLine *> thelin_;
 
  std::vector<Dataset> thebgmc_ ;
  std::vector<Dataset> thesigmc_;
  std::vector<Dataset> thedata_ ;

  //Functions
  DrawTree();

public:
  DrawTree(TString n, int verboselevel = vPrint);
  ~DrawTree();

  //Setters
  //
  void setSavegraph1   (bool b) { savegraph1_    = b; }
  void setSavegraph2   (bool b) { savegraph2_    = b; } 
  void setSavegraph3   (bool b) { savegraph3_    = b; } 
  void setDrawratio    (bool b) { drawratio_     = b; }
  void setDrawleg      (bool b) { drawleg_       = b; }
  void setDrawlegborder(bool b) { drawlegborder_ = b; } 
  void setDrawmcerr    (bool b) { drawmcerr_     = b; }
  void setDrawlatex    (bool b) { drawlatex_     = b; } 
  void setDrawline     (bool b) { drawline_      = b; } 
  void setLogx         (bool b) { logx_          = b; } 
  void setLogy         (bool b) { logy_          = b; } 
  void setLogz         (bool b) { logz_          = b; } 
  void setDobatch      (bool b) { dobatch_       = b; } 
  void setDostack      (bool b) { dostack_       = b; }
  void setResetlegend  (bool b) { resetlegend_   = b; } 
  void setAddoverflow  (bool b) { addoverflow_   = b; } 
  void setAddpgnum     (bool b) { addpgnumbers_  = b; } 
  void setPdfmode      (bool b) { pdfmode_       = b; } 
  void setHasdata      (bool b) { hasdata_       = b; } 
  void setIstwikionly  (bool b) { istwikionly_   = b; }
  void setIsprelim     (bool b) { isprelim_      = b; }
  void setInframe      (bool b) { inframe_       = b; }
  void setLuminorm     (bool b) { luminorm_      = b; }
  void setUseRedXtitle (bool b) { useredxtitle_  = b; } 
  void setCmEnergy    (int i)        { cmEnergy_       = i;                    } 
  void setCanvasDim   (int i, int j) { canvaswidth_    = i; canvasheight_ = j; } 
  void setRatioheight (int i)        { ratiopadheight_ = i;                    } 
  void setMargins     (float  r, float  l, float  t, float  b) { rightmargin_ =  r; leftmargin_ =  l; topmargin_  =  t; bottommargin_ =  b; } 
  void setLegendDim   (float x1, float y1, float x2, float y2) { legx1_       = x1; legx2_      = x2; legy1_      = y1; legy2_        = y2; } 
  void setPaveTextDim (float x1, float y1, float x2, float y2) { pavetextx1_  = x1; pavetextx2_ = x2; pavetexty1_ = y1; pavetexty2_   = y2; } 
  void setTextDim     (float x, float y) { textinsidex_  = x; textinsidey_  = y; }
  void setExtraTextDim(float x, float y) { textinside2x_ = x; textinside2y_ = y; }
  void setPgnum       (float x, float y) { pgnumberx_    = x; pgnumbery_    = y; } 
  void setRatiolimits (float f, float g) { ratiomin_     = f; ratiomax_     = g; } 
  void setXlabeloff   (float f) { xlabeloffset_ = f; } 
  void setXtitleoff   (float f) { xtitleoffset_ = f; } 
  void setYlabeloff   (float f) { ylabeloffset_ = f; } 
  void setYtitleoff   (float f) { ytitleoffset_ = f; } 
  void setInflatey    (float f) { inflateymax_  = f; } 
  void setRenorm      (float f) { renorm_       = f; } 
  void setHistmax     (float f) { histmax_      = f; } 
  void setHistmin     (float f) { histmin_      = f; } 
  void setLumi(double d) { lumi_ = d; } 
  void setOutfolder  (TString s) { outfolder_    = s; } 
  void setFilemod    (TString s) { filemod_      = s; } 
  void setFile1ext   (TString s) { file1ext_     = s; } 
  void setFile2ext   (TString s) { file2ext_     = s; } // See also the setupNewOutputFile(...) method 
  void setFile2name  (TString s) { file2name_    = s; } 
  void setText       (TString s) { textinside_   = s; } 
  void setExtraText  (TString s) { textinside2_  = s; } 
  void setPavetext   (TString s) { pavetext_     = s; } 
  void setRatioytitle(TString s) { ratioytitle_  = s; } 
  void setLumiName   (TString s) { luminame_     = s; } 
  //Special
  void setVerbose  (int i); 
  void setText     (TString s, float x, float y) { textinside_  = s; textinsidex_  = x; textinsidey_  = y; }
  void setExtraText(TString s, float x, float y) { textinside2_ = s; textinside2x_ = x; textinside2y_ = y; }
  void setPavetext (TString s, float x1, float y1, float x2, float y2) { pavetext_ = s; pavetextx1_ = x1; pavetextx2_ = x2; pavetexty1_ = y1; pavetexty2_ = y2; }

  //void set(bool b) { = b; } 
  //void set(int i) { = i; } 
  //void set(float f) { = f; } 
  //void set(double d) {  = d; } 
  //void set(TString s) { = s; } 

  //Getters
  //
  

  //Other
  //
  bool isThereBGMC () { return (thebgmc_ .size()>0); }
  bool isThereSigMC() { return (thesigmc_.size()>0); }
  bool isThereData () { return (thedata_ .size()>0); }
  void clearVar  () { thevar_  .clear(); }
  void clearBGMC () { thebgmc_ .clear(); }
  void clearSigMC() { thesigmc_.clear(); }
  void clearData () { thedata_ .clear(); }
  void clearLine () { thelin_  .clear(); }

  void addVar  (ToPlot  tp);
  void addBGMC (Dataset ds);
  void addSigMC(Dataset ds);
  void addData (Dataset ds);
  void addVar  (std::vector<ToPlot>  vtp);
  void addBGMC (std::vector<Dataset> vec);
  void addSigMC(std::vector<Dataset> vec);
  void addData (std::vector<Dataset> vec);
  void addLine(float x1, float y1, float x2, float y2, int col = 1, int sty = 7, int wid = 3);
  void renewCanvas(TString opt = "", float lm = -1.);
  void renewLegend();
  void renewLegend(float x1, float y1, float x2, float y2);

  TString getSaveName1(TString name);
  TString getSaveName2(int    place);
  TString getSaveName3();
  void setOutputFolder();

  double findOverallMax(TH1D * h);
  double findOverallMin(TH1D * h);
  double findTotalMin(std::vector<double> histmins);

  void plotBlankPage(int place, TString name = "BLANK");
  void setupNewOutputFile(TString fname, TString fmod =  "", TString fext = "");

  void drawPlotHeader();
  void drawSBText(float min, float max); 
  void drawPageNumber(int n);
  void drawText();
  void drawExtraText();

  void plot(TString plotopt = "");

  //Custom functions
  void autoAddDatasets(TString path = "../files/", TString what = "", TString back = "-skim.root");
  void plotInSB(TString plotopt = ""); 
 
  //Experimental functions
  void Nminus1plots(ToPlot tp, TString token = "$$"); 
  void cutflow(TString strcuts, TString strcuts2 = "", TString strweight = "", TString strnames = "", TString strfile = "", 
               bool dolumi = true, bool doraw = true, bool dolatex = false);
  void sens_table(Dataset bg, TString strcuts, TString strweight, TString strnames, TString strfile = "", TString strvar = "Q", bool dolatex = false);
  void plot2D_sb(TString plot, TString sel, TString base);

  //Custom, unique functions
  void makeMDP_HiLo_Table();
  void makeMDP_HiLo_Table2(ToPlot tp);
  double calcTotal(TChain * tree, int flag);
  double calcTotal2(TChain * tree, TString name, int flag);
  int findSearchBin(double ht, double mht, int njets, int nbjets);

};  // class DrawTree 

#endif

