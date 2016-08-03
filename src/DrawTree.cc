
#include "../interface/DrawTree.h"

using std::cout;
using std::endl;
using namespace ep;


DrawTree::DrawTree() {
  // Default constructor
} 

DrawTree::DrawTree(TString n, int verboselevel) 
: treename_(n)
{

  //Set the global verbosity level here
  ep::verbose = verboselevel;

  //Init TStyle
  initStyle("CMS"); //Or 'me'

  // Set ROOT global error message level -- see TError.h
  if      ( ep::verbose ==    0 ) gErrorIgnoreLevel =    0; //kPrint 
  else if ( ep::verbose == 1000 ) gErrorIgnoreLevel = 1000; //kInfo 
  else if ( ep::verbose == 2000 ) gErrorIgnoreLevel = 2000; //kWarning 
  else if ( ep::verbose == 3000 ) gErrorIgnoreLevel = 3000; //kError 
  else if ( ep::verbose == 4000 ) gErrorIgnoreLevel = 4000; //kBreak 
  else if ( ep::verbose == 5000 ) gErrorIgnoreLevel = 5000; //kSysError 
  else if ( ep::verbose >= 6000 ) gErrorIgnoreLevel = 6000; //kFatal 
  else                            gErrorIgnoreLevel =   -1; //kUnset

  TString print;
  print.Form("\n\t\t\t\t\t\t~~  Creating DrawTree [%s] object...  ~~\n",n.Data());
  int width = print.Length(); width -= 8; 
  myp("\n\n\t\t\t\t\t\t"); pts(vError);
  for ( int i = 0; i < width; ++i ) { myp("~"); pts(vError); }
  myp("%s",print.Data()); pts(vError);


  //
  //Set all the default parameters here
  //

  //--
  savegraph1_   = false;
  savegraph2_   = true ;
  savegraph3_   = false;
  drawratio_    = false;
  drawleg_      = true ;
  drawlegborder_= false;
  drawmcerr_    = true ;
  drawlatex_    = true ;
  drawline_     = false;
  logz_         = false;
  logy_         = false;
  logx_         = false;
  dobatch_      = true ;
  dostack_      = true ;
  resetlegend_  = true ;
  addoverflow_  = true ;
  addpgnumbers_ = false;
  pdfmode_      = true ;
  hasdata_      = false;
  istwikionly_  = false;
  isprelim_     = true ;
  inframe_      = false;
  luminorm_     = true ;
  useredxtitle_ = true ;

  //--
  cmEnergy_      =  13 ;
  pagenumber_    =   0 ;
  canvaswidth_   = 600 ;
  canvasheight_  = 550 ;
  ratiopadheight_= 150 ;
  plotnumber_    =   0 ;

  //--
  legx1_        = 0.68 ;
  legx2_        = 0.90 ;
  legy1_        = 0.55 ;
  legy2_        = 0.90 ;
  xlabeloffset_ = 0.004;
  xtitleoffset_ = 1.16 ;
  ylabeloffset_ = 0.004;
  ytitleoffset_ = 1.09 ;
  rightmargin_  = 0.06 ;
  leftmargin_   = 0.14 ;
  topmargin_    = 0.08 ;
  bottommargin_ = 0.12 ;
  textinsidex_  = 0.2  ;
  textinsidey_  = 0.85 ;
  textinside2x_ = 0.2  ;
  textinside2y_ = 0.88 ;
  pavetextx1_   = 0.61 ;
  pavetextx2_   = 0.88 ;
  pavetexty1_   = 0.15 ;
  pavetexty2_   = 0.50 ;
  pgnumberx_    = 0.97 ;
  pgnumbery_    = 0.06 ;
  ratiomin_     = 0.0  ;
  ratiomax_     = 2.2  ;
  inflateymax_  = 3.0  ;
  histmax_      = -1.0 ;
  histmin_      = -1.0 ;

  //--
  lumi_ = 1000;

  //--
  outfolder_    = "./plots"  ;
  filemod_      = ""         ;
  file1ext_     = ".pdf"     ;
  file2ext_     = ".pdf"     ;
  file2name_    = "allplots" ;
  textinside_   = ""         ;
  textinside2_  = ""         ;
  pavetext_     = ""         ;
  ratioytitle_  = "Data/MC " ;
  luminame_     = "Weight"   ;

  //--
  thecan_   = 0;
  theleg_   = 0;
  text1_    = 0;
  text2_    = 0;
  text3_    = 0;
  text4_    = 0;
  ptext_    = 0;
  fileout_  = 0;
  ratio_    = 0;
  ratiolin_ = 0;
  thestack_ = 0;
  totalsm_  = 0;
  mcerr_    = 0;

  thevar_  .clear();
  thelin_  .clear();
  thebgmc_ .clear();
  thesigmc_.clear();
  thedata_ .clear();


  if ( savegraph1_ || savegraph2_ || savegraph3_ ) setOutputFolder();

  if ( savegraph3_ ) fileout_ = new TFile(getSaveName3(),"RECREATE");
  if ( pdfmode_    ) plotBlankPage(1)                               ;

  print = ".. and fully initialized";
  bool odd = ( width % 2 );
  if ( !odd ) print.Append(" !");
  else        print.Append( "!");
  int mid = print.Length()/2;
  int pad = width/2-mid-2;
  for ( int i = 0; i < pad; ++i ) { print.Prepend(" "); print.Append(" "); }
  print.Prepend("\t\t\t\t\t\t~~"); print.Append("~~\n");
  myp("%s\t\t\t\t\t\t",print.Data()); pts(vError);
  for ( int i = 0; i < width; ++i ) { myp("~"); pts(vError); }
  myp("\n\n\n"); pts(vError);


  //
  myp("\t\t\t\t\t\t\t    Initial DrawTree User Settings\n"                                ); pts(vError);
  myp("\t\t\t\t\t------------------------------------------------------------------\n"    ); pts(vError);
  myp("\t\t\t\t\t\tSave the plots (individual) : %s\n"   , BOOL_STR(savegraph1_)          ); pts(vError);
  myp("\t\t\t\t\t\tSave the plots (continuous) : %s\n"   , BOOL_STR(savegraph2_)          ); pts(vError);
  myp("\t\t\t\t\t\tDraw Data/MC ratio plot     : %s\n"   , BOOL_STR(drawratio_)           ); pts(vError);
  myp("\t\t\t\t\t\tDraw MC error bands         : %s\n"   , BOOL_STR(drawmcerr_)           ); pts(vError);
  myp("\t\t\t\t\t\tDraw y-axis in log scale    : %s\n"   , BOOL_STR(logy_)                ); pts(vError);
  myp("\t\t\t\t\t\tDraw data (black points)    : %s\n"   , BOOL_STR(hasdata_)             ); pts(vError);
  myp("\t\t\t\t\t\tCenter-of-Mass Energy [TeV] : %i\n"   , cmEnergy_                      ); pts(vError);
  myp("\t\t\t\t\t\tLuminosity scale [pb]       : %.0f\n" , lumi_                          ); pts(vError);
  myp("\t\t\t\t\t\tOutput folder name          : %s\n"   , outfolder_.Data()              ); pts(vError);
  myp("\t\t\t\t\t\tOutput continuous pdf file  : %s\n"   , getSaveName2(0).Data()         ); pts(vError);
  myp("\t\t\t\t\t------------------------------------------------------------------\n\n\n"); pts(vError);
  //


}

DrawTree::~DrawTree() {
  // Default destructor

  if ( savegraph3_ ) fileout_->Close();
  if ( pdfmode_    ) plotBlankPage(-1);

  if ( mcerr_    != 0 ) delete mcerr_   ;
  if ( totalsm_  != 0 ) delete totalsm_ ;
  if ( thestack_ != 0 ) delete thestack_;
  if ( ratiolin_ != 0 ) delete ratiolin_;
  if ( ratio_    != 0 ) delete ratio_   ;
  if ( fileout_  != 0 ) delete fileout_ ;
  if ( ptext_    != 0 ) delete ptext_   ;
  if ( text4_    != 0 ) delete text4_   ;
  if ( text3_    != 0 ) delete text3_   ;
  if ( text2_    != 0 ) delete text2_   ;
  if ( text1_    != 0 ) delete text1_   ;
  if ( theleg_   != 0 ) delete theleg_  ;
  if ( thecan_   != 0 ) delete thecan_  ;

  TDatime endtime;
  int t = endtime.Convert() - thetime_.Convert();

  TString print2 = "Terminating DrawTree object...";
  TString print1;
  if ( t < 3600 ) {
    print1.Form("The DrawTree object was in use for %02.0f:%02.0f.", (double)(t/60),(double)(t%60));
  }
  else {
    print1.Form("The DrawTree object was in use for %02.0f:%02.0f:%02.0f.", (double)t/3600,(double)((double)(t%3600)/60),(double)(t%60));
  }

  int width1 = print1.Length(); 
  int width2 = print2.Length();
  int width  = width1;
  if ( width2 > width1 ) width = width2;
  width += 8;

  bool odd = ( width2 % 2 );
  if ( !odd ) print2.Append(" !");
  else        print2.Append( "!");
  odd = ( width1 % 2 );
  if ( !odd ) print1.Append("  ");
  else        print1.Append( " ");

  int mid2 = print2.Length()/2;
  int pad2 = width/2-mid2-2;
  int mid1 = print1.Length()/2;
  int pad1 = width/2-mid1-2;

  for ( int i = 0; i < pad1; ++i ) { print1.Prepend(" "); print1.Append(" "); }
  for ( int i = 0; i < pad2; ++i ) { print2.Prepend(" "); print2.Append(" "); }
  print1.Prepend("\n\t\t\t\t\t\t~~"); print1.Append("~~\n");
  print2.Prepend(  "\t\t\t\t\t\t~~"); print2.Append("~~\n");
  myp("\n\n\n\n\t\t\t\t\t\t"); pts(vError);
  for ( int i = 0; i < width-1; ++i ) { myp("~"); pts(vError); }
  myp("%s",print1.Data()); pts(vError);
  myp("%s",print2.Data()); pts(vError);
  myp("\t\t\t\t\t\t"); pts(vError);
  for ( int i = 0; i < width-1; ++i ) { myp("~"); pts(vError); }
  myp("\n\n\n\n"); pts(vError);

}

void DrawTree::setVerbose(int v) { 
  verbose = v; 

  if      ( verbose == 0 ) gErrorIgnoreLevel =    0; //vPrint 
  else if ( verbose == 1 ) gErrorIgnoreLevel = 1000; //vInfo 
  else if ( verbose == 2 ) gErrorIgnoreLevel = 2000; //vWarning 
  else if ( verbose == 3 ) gErrorIgnoreLevel = 3000; //vError 
  else if ( verbose == 4 ) gErrorIgnoreLevel = 4000; //vBreak 
  else if ( verbose == 5 ) gErrorIgnoreLevel = 5000; //vSysError 
  else if ( verbose >= 6 ) gErrorIgnoreLevel = 6000; //vFatal 
  else                     gErrorIgnoreLevel =   -1; //vUnset
}

void DrawTree::setOutputFolder() {

  if ( outfolder_.Length() < 1 ) { 
    myp("Output folder name is not set properly. Will revert to output in working directory.\n"); pts(vWarning);
    return;
  } 

  TString path = outfolder_;
  if ( TString(path( path.Length()-1 )) != "/" ) path.Append("/");
  outfolder_ = path;

  FileStat_t fs;
  int dirnotthere = gSystem->GetPathInfo(outfolder_.Data(),fs);

  if ( dirnotthere == 1 ) { //then make the directory
    myp("Directory %s not found.\n",outfolder_.Data()); pts(vPrint);
    int mkdirstatus = gSystem->mkdir(outfolder_.Data());
    if ( mkdirstatus == 0 ) {
      myp("Created it!\n"); pts(vPrint);
    }
    else {
      myp("Problem creating directory. Will revert to output in working directory.\n"); pts(vWarning);
      outfolder_="";
    }
  }

}//set output folder

void DrawTree::addVar(ToPlot tp) {
  thevar_.push_back(tp);
}

void DrawTree::addVar(std::vector<ToPlot> tp) {
  thevar_.insert(thevar_.end(), tp.begin(), tp.end()); 
}

void DrawTree::addBGMC(Dataset ds) {
  thebgmc_.push_back(ds);
}

void DrawTree::addBGMC(std::vector<Dataset> vec) {
  thebgmc_.insert(thebgmc_.end(), vec.begin(), vec.end());
}

void DrawTree::addSigMC(Dataset ds) {
  thesigmc_.push_back(ds);
}

void DrawTree::addSigMC(std::vector<Dataset> vec) {
  thesigmc_.insert(thesigmc_.end(), vec.begin(), vec.end());
}

void DrawTree::addData(Dataset ds) {
  thedata_.push_back(ds);
}

void DrawTree::addData(std::vector<Dataset> vec) {
  thedata_.insert(thedata_.end(), vec.begin(), vec.end());
}

void DrawTree::addLine(float x1, float y1, float x2, float y2, int col, int sty, int wid) {

  TLine * lin = new TLine(x1,y1,x2,y2);
  lin->SetLineColor(col);
  lin->SetLineStyle(sty);
  lin->SetLineWidth(wid);

  thelin_.push_back(lin);
}

void DrawTree::renewCanvas(TString opt, float lm) {

  if ( thecan_ != 0 ) delete thecan_;

  int thecanvasheight = canvasheight_;
  if ( opt.Contains("ratio") ) thecanvasheight += ratiopadheight_;

  thecan_ = new TCanvas("thecan","",canvaswidth_,thecanvasheight);
  thecan_->SetBatch(dobatch_);

  thecan_->cd()->SetRightMargin(rightmargin_);
  if ( lm < 0 )
    thecan_->cd()->SetLeftMargin(leftmargin_);
  else 
    thecan_->cd()->SetLeftMargin(lm);
  thecan_->cd()->SetTopMargin(topmargin_);
  thecan_->cd()->SetBottomMargin(bottommargin_);

  if ( opt.Contains("ratio") ) {

    theStyle->SetPadBorderMode(0);
    theStyle->SetFrameBorderMode(0);
    Float_t small = 1e-5;
    thecan_->Divide(1,2,small,small);
    const float padding=1e-5; const float ydivide=0.3;
    thecan_->GetPad(1)->SetPad( padding, ydivide + padding, 1-padding, 1-padding);
    thecan_->GetPad(2)->SetPad( padding, padding, 1-padding, ydivide-padding);
    thecan_->GetPad(1)->SetTopMargin(topmargin_); //0.08 0.06
    thecan_->GetPad(1)->SetRightMargin(rightmargin_); // 0.04
    thecan_->GetPad(2)->SetRightMargin(rightmargin_); // 0.04
    thecan_->GetPad(2)->SetBottomMargin(0.6); // 0.6<->0.3 (Nominal<->For individual saved plots)
    ///if ( savegraph1_ ) thecan_->GetPad(2)->SetBottomMargin(0.3); // 0.6<->0.3 (Nominal<->For individual saved plots)
    thecan_->GetPad(1)->Modified();
    thecan_->GetPad(2)->Modified();
    thecan_->cd(1);
    gPad->SetBottomMargin(small);
    gPad->Modified();

    if ( logz_ ) thecan_->GetPad(1)->SetLogz();
    if ( logy_ ) thecan_->GetPad(1)->SetLogy();
    if ( logx_ ) thecan_->GetPad(1)->SetLogx();
  }
  else { 
    if ( logz_ ) thecan_->SetLogz(); 
    if ( logy_ ) thecan_->SetLogy(); 
    if ( logx_ ) thecan_->SetLogx();
    thecan_->GetPad(0)->SetBottomMargin(0.16); //default 0.13
  }

  int cdarg = (opt.Contains("ratio") ) ? 1 : 0; 
  thecan_->cd(cdarg);

}

void DrawTree::renewLegend() {
  if ( theleg_ != 0 ) delete theleg_;
  theleg_ = new TLegend(legx1_, legy1_, legx2_, legy2_);
  theleg_->SetBorderSize((int)drawlegborder_); //Set to 1 for a line around the Legend
  theleg_->SetLineStyle(0);
  theleg_->SetTextFont(42); 
  theleg_->SetTextSize(0.019); 
  theleg_->SetFillColor(0); //Pure white background in Legend i.e. not 'clear' background.
}

void DrawTree::renewLegend(float x1, float y1, float x2, float y2) {
  if ( theleg_ != 0 ) delete theleg_;
  theleg_ = new TLegend(x1,y1,x2,y2);
  theleg_->SetBorderSize((int)drawlegborder_); //Set to 1 for a line around the Legend
  theleg_->SetLineStyle(0);
  theleg_->SetTextFont(42); 
  theleg_->SetNColumns(2);
  theleg_->SetFillColor(0); //Pure white background in Legend i.e. not 'clear' background.
}

void DrawTree::drawPlotHeader() {
  //Header style adapted from Gautier HAMEL de MONCHENAULT
  //https://ghm.web.cern.ch/ghm/plots/

  TString cmsString = "CMS";

  //Various constants and positions
  float cmsTextFont    =   61;  // default is helvetic-bold
  float extraTextFont  =   52;  // default is helvetica-italics
  float cmsTextSize    = 0.75;
  float lumiTextSize   = 0.6 ;
  //float cmsTextOffset  = 0.1 ;  // only used in outOfFrame version
  float lumiTextOffset = 0.2 ;
  float extraOverCmsTextSize  = 0.76; //ratio of CMS and extra text size
  float extraTextSize = extraOverCmsTextSize*cmsTextSize;
  float ratioOffset = 1.1 ; // Extra factor use in case ratio plot included 
  float relPosX    = 0.045;
  float relPosY    = 0.035;
  float relExtraDY = 1.2  ;
  float l = thecan_->GetLeftMargin()  ;
  float t = thecan_->GetTopMargin()   ;
  float r = thecan_->GetRightMargin() ;
  float b = thecan_->GetBottomMargin();
  float posX =   l + relPosX*(1-l-r) ;
  float posY = 1-t - relPosY*(1-t-b) ;


  //Draw 'CMS'
  if ( text1_ != 0 ) delete text1_;
  text1_ = new TLatex(3.570061,23.08044,cmsString);
  text1_->SetNDC();
  text1_->SetTextFont(cmsTextFont);
  text1_->SetTextSize(cmsTextSize*t);
  if ( inframe_ ) {
    if ( drawratio_ ) posX *= ratioOffset;
    text1_->SetTextAlign(13);
    text1_->DrawLatex(posX,posY,cmsString);
  }
  else {  
    if ( drawratio_ ) l *= ratioOffset;
    text1_->SetTextAlign(11);
    text1_->DrawLatex(l,1-t+lumiTextOffset*t,cmsString);
  }

  //Draw any necessary extra text
  cmsString = "";
  if      ( istwikionly_ ) cmsString = "Unpublished";
  else if (   ! hasdata_ ) cmsString = "Simulation" ;
  else if (    isprelim_ ) cmsString = "Preliminary";

  text1_->SetTextFont(extraTextFont);
  text1_->SetTextSize(extraTextSize*t);
  if ( inframe_ ) {
    text1_->SetTextAlign(13);
    text1_->DrawLatex(posX,posY-relExtraDY*cmsTextSize*t,cmsString);
  }
  else {  
    if ( drawratio_ ) l /= ratioOffset;
    posX =   l +  relPosX*3.5*(1-l-r); //3.5
    posY = 1-t +     lumiTextOffset*t;
    text1_->SetTextAlign(11);
    text1_->DrawLatex(posX,posY,cmsString);
  }

  //Draw lumi/energy 
  cmsString = "";
  //add lumi if data or lumi normalized 
  if ( hasdata_ || luminorm_ ) {
    TString lumiString;
    if      ( lumi_/1000. > 49 ) lumiString.Form(" %.0f fb^{-1}"  ,lumi_/1000.);
    else if ( lumi_ < 1000     ) lumiString.Form(" %3.1f pb^{-1}" ,lumi_      );
    else                         lumiString.Form(" %.1f fb^{-1}"  ,lumi_/1000.);
    cmsString += lumiString;
  }
  if ( hasdata_ && !luminorm_ ) cmsString = "";

  // always add energy
  TString energyString;
  energyString.Form(" (%d TeV)" , cmEnergy_);
  cmsString += energyString;

  text1_->SetTextAlign(31);
  text1_->SetTextFont(42);
  text1_->SetTextSize(lumiTextSize*t);    
  text1_->DrawLatex(1-r,1-t+lumiTextOffset*t,cmsString);
  
}

void DrawTree::drawSBText(float min, float max) {

  // Njet separation lines
  TLine *tl_njet = new TLine();
  tl_njet->SetLineStyle(2);
  tl_njet->DrawLine(25.-0.5,min,25.-0.5,max); 
  tl_njet->DrawLine(49.-0.5,min,49.-0.5,max); 

  // Njet labels
  TLatex * ttext_njet = new TLatex();
  ttext_njet->SetTextFont(42);
  ttext_njet->SetTextSize(0.050);
  ttext_njet->SetTextAlign(22);
  float tm_nj = 0.92;
  ttext_njet->DrawLatex(13.-0.5 , max*tm_nj , "4 #leq N_{#scale[0.2]{ }jet} #leq 6");
  ttext_njet->DrawLatex(37.-0.5 , max*tm_nj , "7 #leq N_{#scale[0.2]{ }jet} #leq 8");
  ttext_njet->DrawLatex(61.-0.5 , max*tm_nj , "N_{#scale[0.2]{ }jet} #geq 9");

  // Nb separation lines
  TLine *tl_nb = new TLine();
  tl_nb->SetLineStyle(3);
  float lm_nb = 0.77;
  tl_nb->DrawLine( 7.-0.5,min, 7.-0.5,max*lm_nb); 
  tl_nb->DrawLine(13.-0.5,min,13.-0.5,max*lm_nb); 
  tl_nb->DrawLine(19.-0.5,min,19.-0.5,max*lm_nb); 
  tl_nb->DrawLine(31.-0.5,min,31.-0.5,max*lm_nb); 
  tl_nb->DrawLine(37.-0.5,min,37.-0.5,max*lm_nb); 
  tl_nb->DrawLine(43.-0.5,min,43.-0.5,max*lm_nb); 
  tl_nb->DrawLine(55.-0.5,min,55.-0.5,max*lm_nb); 
  tl_nb->DrawLine(61.-0.5,min,61.-0.5,max*lm_nb); 
  tl_nb->DrawLine(67.-0.5,min,67.-0.5,max*lm_nb); 
    
  // Nb labels
  TLatex * ttext_nb = new TLatex();
  ttext_nb->SetTextFont(42);
  ttext_nb->SetTextSize(0.045);
  ttext_nb->SetTextAlign(22);
    
  float tm_nb = 0.78;
  ttext_nb->DrawLatex( 4.75   , max*tm_nb*1.1 , "N_{#scale[0.2]{ }b-jet}");
  ttext_nb->DrawLatex( 4.-0.5 , max*tm_nb , "0");
  ttext_nb->DrawLatex(10.-0.5 , max*tm_nb , "1");
  ttext_nb->DrawLatex(16.-0.5 , max*tm_nb , "2");
  ttext_nb->DrawLatex(22.-0.5 , max*tm_nb , "#geq 3");

}

void DrawTree::drawText() {
  if ( textinside_ == "" ) return;
  if ( text2_ != 0 ) delete text2_;

  text2_ = new TLatex(5,23.08044,textinside_);
  text2_->SetNDC();
  text2_->SetTextAlign(13);
  text2_->SetX(textinsidex_);
  text2_->SetY(textinsidey_);
  text2_->SetTextFont(42);
  text2_->SetTextSizePixels(24);
  text2_->SetTextSize(0.044);
  text2_->Draw();

}

void DrawTree::drawExtraText() {
  if ( textinside2_ == "" ) return;
  if ( text3_ != 0 ) delete text3_;

  text3_ = new TLatex(5,23.08044,textinside2_);
  text3_->SetNDC();
  text3_->SetTextAlign(13);
  text3_->SetX(textinside2x_);
  text3_->SetY(textinside2y_);
  text3_->SetTextFont(42);
  text3_->SetTextSizePixels(24);
  text3_->SetTextSize(0.044);
  text3_->Draw();
}

// Draw the 'blank' page (usually at the front or back of a continuous pdf) 
void DrawTree::plotBlankPage(int place, TString name) {

  renewCanvas("");

  TLatex * blank = new TLatex(5,23.08044,name);
  blank->SetNDC();
  blank->SetTextAlign(13);
  blank->SetX(0.18);
  blank->SetY(0.7);
  blank->SetTextFont(42);
  blank->SetTextSizePixels(24);
  blank->SetTextSize(0.25);
  blank->Draw();

  int hold = gErrorIgnoreLevel; 
  gErrorIgnoreLevel = 2000;
  thecan_->Print(getSaveName2(place));
  gErrorIgnoreLevel = hold;
}

void DrawTree::setupNewOutputFile(TString fname, TString fmod, TString fext) {
 
  plotBlankPage(-1);

  setFile2name(fname); 
  if ( fmod != "" ) setFilemod (fmod); 
  if ( fext != "" ) setFile2ext(fext); 

  plotBlankPage(1);

}

void DrawTree::drawPageNumber(int n) { 
  //Only draw if pdf continuous file is produced
  if ( !savegraph2_ ) return;

  if ( n == 0 ) pagenumber_ = 1; 
  else ++pagenumber_;

  TString text;
  text += pagenumber_;

  if (text4_ != 0 ) delete text4_;
  text4_ = new TLatex(3.570061,23.08044,text);
  text4_->SetNDC();
  text4_->SetTextAlign(13);
  text4_->SetX(pgnumberx_);
  text4_->SetY(pgnumbery_);
  text4_->SetTextFont(42);
  text4_->SetTextSizePixels(24);
  text4_->SetTextSize(0.030); //was 0.045
  if ( drawratio_ ) {
    text4_->SetY(pgnumbery_+0.5);
    text4_->SetTextSize(0.090);
  }
  text4_->Draw();

}

double DrawTree::findOverallMax(TH1D * hh) {
  double max=-1e9;
  for ( int i = 1; i <= hh->GetNbinsX(); ++i ) {
    double val = hh->GetBinContent(i) + hh->GetBinErrorUp(i);
    TString n = hh->GetName();
    // Rather hacky.. if data has only one point then make sure the returned max val is greater than 2
    if ( n.Contains("ata") && val < 3. && !logy_ ) val *= 1.3;
    if ( val > max ) max=val;
  }
  return max;
}

double DrawTree::findOverallMin(TH1D * hh) {
  double min=1e9;
  for ( int i = 1; i <= hh->GetNbinsX(); ++i ) {
    double val = hh->GetBinContent(i);
    if ( AreEqualAbs(val,0.,1e-6) ) continue;
    if ( val < min ) min=val;
  }
  return min;
}

double DrawTree::findTotalMin(std::vector<double> histmins) {
  //Get average of all the histogram mins
  //Perform simple arthimetic or geometric mean
  
  //Open this up to user? 
  bool geometric = false;

  std::set<double> mins;
  for ( std::vector<double>::const_iterator itr = histmins.begin(); itr != histmins.end(); ++itr ) {
    mins.insert(*itr);
  }
  mins.erase(0.);
  mins.erase(1e9);

  double sum = 0, product = 1;
  for ( std::set<double>::const_iterator itr = mins.begin(); itr != mins.end(); ++itr ) {
    sum += *itr;
    product *= *itr;
  }

  if ( !geometric )
    return sum/mins.size();
  else 
    return pow(product,1./mins.size());

}


TString DrawTree::getSaveName1(TString name) {

  //leave extra here for now for potential future expansion
  TString extra = "";
  if ( logx_ ) extra += "_logX";
  if ( logy_ ) extra += "_logY";
  if ( logz_ ) extra += "_logZ";
  TString ret = "";
  ret += outfolder_;
  ret += name;
  ret += extra;
  if ( filemod_ != "" ) { ret += "_"; ret += filemod_; }
  ret += file1ext_;

  return ret;
}

TString DrawTree::getSaveName2(int place) {

  TString ret = "";
  ret += outfolder_;
  ret += file2name_;
  if ( filemod_ != "" ) { ret += "_"; ret += filemod_; }
  ret += file2ext_;
  if      ( place ==  1 ) ret += "(";
  else if ( place == -1 ) ret += ")";
  else                    ret +=  "";

  return ret;
}

TString DrawTree::getSaveName3() {

  TString ret = "";
  ret += outfolder_;
  ret += file2name_;
  if ( filemod_ != "" ) { ret += "_"; ret += filemod_; }
  ret += ".root";

  return ret;
}

//The heavy lifter
void DrawTree::plot(TString plotopt) {

  if ( drawratio_ && !(hasdata_ && isThereData()) ) { 
    if ( thebgmc_.size() == 2 ) { 
      drawratio_ = true; 
      myp("\n\nDrawing ratio plot with MC\n"); pts(vInfo);
    }
    else {
      if ( isThereData() ) myp("\n\nWARNING: Parameter 'hasdata' not set to true. Not drawing 'Data' or Data/MC ratio plot.\n");
      else myp("\n\nWARNING: No 'Data' is added to plot. Please add this Dataset in order to draw it. Not drawing Data/MC ratio plot.\n");
      pts(vWarning);
      drawratio_ = false;
    }
  }
  TString canvasOpt = drawratio_ ? "ratio" : "";
  const int mainPadIndex = drawratio_ ? 1 : 0; 

  myp("\n\n"); pts(vInfo);

  int varnum = 0;
  ++plotnumber_ ;

  //Loop over all vars (even if its just one)
  for (std::vector<ToPlot>::iterator var = thevar_.begin(); var != thevar_.end(); ++var, ++varnum ) {

    TStopwatch sw ;
    sw.Start() ;
    bool isempty = false;
    TString s_varnum = "_"; s_varnum += plotnumber_; s_varnum += "_"; s_varnum += varnum;

    myp("\n====================  Plotting  ---> %s <---   ====================\n\n",var->getVarname().Data()); pts(vError);
    
    renewCanvas(canvasOpt);
    renewLegend();

    thecan_->cd(mainPadIndex);
    if ( useredxtitle_ ) var->makeSimpleXtitle();
    if ( var->getNxbins() <= 0 ) var->assignAxisLimits("X");

    if ( dostack_ ) {
      if ( thestack_ != 0 ) delete thestack_;
      thestack_ = new THStack("thestack","--");
    }
    if ( totalsm_ != 0 ) delete totalsm_;
    totalsm_ = new TH1D("totalsm","",var->getNxbins(),var->getXlow(),var->getXhigh()); 
    totalsm_->Sumw2();
    if ( drawratio_ ) {
      if ( ratio_ != 0 ) delete ratio_;
      ratio_ = new TH1D("ratio","",var->getNxbins(),var->getXlow(),var->getXhigh());
      ratio_->Sumw2();
      if ( ratiolin_ != 0 ) delete ratiolin_;
      ratiolin_ = new TLine(var->getXlow(), 1, var->getXhigh(), 1);
    }
    TH1D * hblank = new TH1D("hblank","",var->getNxbins(),var->getXlow(),var->getXhigh());

    //TODO: Hardcoded values.. could probably open this up to the user 
    totalsm_->SetMarkerColor(vSharkBlue);
    totalsm_->SetLineColor(vSharkBlue);
    totalsm_->SetLineWidth(1);
    totalsm_->SetMarkerStyle(kOpenCircle);

    double hmax = -1;
    std::vector<double> histmins;

    TString opt = "hist e";
    int dsnum = 0;
    //Loop over datasets
    for (std::vector<Dataset>::iterator ds = thedata_.begin(); ds != thedata_.end(); ++ds, ++dsnum) {
      TString s_dsnum = s_varnum; s_dsnum += "_"; s_dsnum += dsnum;

      ds->project(var->getVarname()+s_dsnum,var->getVarname(),var->getFullCut(*ds,""),var->getNxbins(),var->getXlow(),var->getXhigh());

      if ( addoverflow_ ) ds->addOverflow();

      ds->getHist()->SetXTitle(var->getXtitle());
      ds->getHist()->SetYTitle(var->getYtitle());
      ds->getHist()->GetXaxis()->SetLabelOffset(xlabeloffset_);
      ds->getHist()->GetXaxis()->SetTitleOffset(xtitleoffset_);
      ds->setHistMarkColor();

      if ( hmax < findOverallMax(ds->getHist()) ) hmax = findOverallMax(ds->getHist()); 
      histmins.push_back(findOverallMin(ds->getHist()));

    }//thedata loop

    for (std::vector<Dataset>::iterator ds = thebgmc_.begin(); ds != thebgmc_.end(); ++ds, ++dsnum) {

      TString s_dsnum = s_varnum; s_dsnum += "_"; s_dsnum += dsnum;
      if      ( hasdata_ && !luminorm_ )
        ds->project(var->getVarname()+s_dsnum,var->getVarname(),var->getFullCut(*ds,luminame_,lumi_),var->getNxbins(),var->getXlow(),var->getXhigh());
      else if ( hasdata_ ||  luminorm_ )
        ds->project(var->getVarname()+s_dsnum,var->getVarname(),var->getFullCut(*ds,luminame_,lumi_),var->getNxbins(),var->getXlow(),var->getXhigh());
      else
        ds->project(var->getVarname()+s_dsnum,var->getVarname(),var->getFullCut(*ds,""),var->getNxbins(),var->getXlow(),var->getXhigh());

      if ( addoverflow_ ) ds->addOverflow();
      if ( hasdata_ && !luminorm_ ) ds->getHist()->Scale(thedata_.begin()->getFullEntries()/ds->getFullEntries());


      ds->getHist()->SetXTitle(var->getXtitle());
      ds->getHist()->SetYTitle(var->getYtitle());
      ds->getHist()->GetXaxis()->SetLabelOffset(xlabeloffset_);
      ds->getHist()->GetXaxis()->SetTitleOffset(xtitleoffset_);
      //Sets global number of digits used in axis (cant set individually; or per 'plot' or 'var')
      //Default value is 5
      //The exponent conflicts with the hist title (ends up on 'CM')
      ////if ( logy_ ) TGaxis::SetMaxDigits(4);
      if ( dostack_ ) ds->setHistFillColor();
      else            ds->setHistLineAndMarkColor();

      //Somewhat hacky.. but empty hists still have 1 entry. Why?
      if ( ds->getHist()->GetEntries() > 1 ) totalsm_->Add(ds->getHist());

      if ( hmax < findOverallMax(ds->getHist()) ) hmax = findOverallMax(ds->getHist()); 
      histmins.push_back(findOverallMin(ds->getHist()));
      if ( dostack_ ) { 
        thestack_->Add(ds->getHist());
      }  

    }//thebgmc loop
    if ( dostack_ ) {
      myp("%10s passed events: %10.0f raw, %10f weighted***\n\n","***Total SM",totalsm_->GetEntries(),totalsm_->Integral(0,totalsm_->GetNbinsX()+1)); pts(vError);
    }

    for (std::vector<Dataset>::iterator ds = thesigmc_.begin(); ds != thesigmc_.end(); ++ds, ++dsnum) {
      TString s_dsnum = s_varnum; s_dsnum += "_"; s_dsnum += dsnum;

      //signal points have ppb weighting for SMS scans...
      //ds->project(var->getVarname()+s_dsnum,var->getVarname(),var->getFullCut(*ds,""),var->getNxbins(),var->getXlow(),var->getXhigh());
      ds->project(var->getVarname()+s_dsnum,var->getVarname(),var->getFullCut(*ds,luminame_,lumi_),var->getNxbins(),var->getXlow(),var->getXhigh());

      if ( addoverflow_ ) ds->addOverflow();

      ds->getHist()->SetXTitle(var->getXtitle());
      ds->getHist()->SetYTitle(var->getYtitle());
      ds->getHist()->GetXaxis()->SetLabelOffset(xlabeloffset_);
      ds->getHist()->GetXaxis()->SetTitleOffset(xtitleoffset_);
      ds->setHistLineColor();

      if ( hmax < findOverallMax(ds->getHist()) ) hmax = findOverallMax(ds->getHist()); 
      histmins.push_back(findOverallMin(ds->getHist()));

    }//thesigmc loop


    //Find max and mins to use for the plot
    if ( hmax < findOverallMax(totalsm_) ) hmax = findOverallMax(totalsm_); 
    histmins.push_back(findOverallMin(totalsm_));
    if ( logy_ ) hmax *= inflateymax_;
    else hmax *= inflateymax_ / 2.1 ; //Kinda hacky...
    if ( inframe_ && logy_  ) hmax *= 5;
    
    double hmin = findTotalMin(histmins);
    hmin /= 10;
    if ( histmax_ > 0 ) hmax = histmax_;
    if ( histmin_ > 0 ) hmin = histmin_;
    if ( std::isnan(hmin) || std::isnan(hmax) ) isempty = true;
    if ( !isempty ) {
      if ( dostack_ ) thestack_->SetMaximum(hmax);
      if ( dostack_ ) thestack_->SetMinimum(hmin);
      hblank->SetMaximum(hmax);
      hblank->SetMinimum(hmin);
    }
    float ytitleoff = ytitleoffset_;
    if ( !logy_ && (log10(hmax) >= 3) ) ytitleoff = 1.19; 

    //Special, unique user functions
    //-

    //Table for mdp H/L ratio
    if ( plotopt.Contains("hilo-ratio-table") ) {
      //makeMDP_HiLo_Table(); 
      makeMDP_HiLo_Table2(*var); //Must add back to stack 
      for (std::vector<Dataset>::iterator ds1 = thebgmc_.begin(); ds1 != thebgmc_.end(); ++ds1) thestack_->Add(ds1->getHist());
       
    }

    //-

    //Setup the legend
    //Data first, then BG MC, then Signal
    for (std::vector<Dataset>::iterator ds = thedata_.begin(); ds != thedata_.end(); ++ds) {
      if ( hasdata_ ) theleg_->AddEntry(ds->getHist(),ds->getLegname(),"P");
    }
    //Loop through backwards
    for (std::vector<Dataset>::iterator ds = thebgmc_.end()-1; ds != thebgmc_.begin()-1; --ds) {
      if ( dostack_ ) 
        theleg_->AddEntry(ds->getHist(),ds->getLegname(),"F");
      else { 
        theleg_->AddEntry(ds->getHist(),ds->getLegname(),"PL");
      }
    }
    for (std::vector<Dataset>::iterator ds = thesigmc_.begin(); ds != thesigmc_.end(); ++ds) {
      theleg_->AddEntry(ds->getHist(),ds->getLegname(),"L");
    }

    if ( hasdata_ && isThereData() ) {
      int ndof = 0, igood = 0;
      double chi2 = 0, datamcratio = 0; 
      double pval    = thedata_.begin()->getHist()->Chi2TestX(totalsm_,chi2,ndof,igood,"UW OF UF");
      double ktestn  = thedata_.begin()->getHist()->KolmogorovTest(totalsm_,"O U N");
      double ktest   = thedata_.begin()->getHist()->KolmogorovTest(totalsm_,"O U")  ;
      double dataint = thedata_.begin()->getHist()->Integral(0,thedata_.begin()->getHist()->GetNbinsX()+1);
      double smmcint = totalsm_->Integral(0,totalsm_->GetNbinsX()+1);
      if ( smmcint > 0. ) datamcratio = dataint/smmcint;

      myp("\n\n\t ------------------------ Statistical Test: Data vs MC -----------------------  \n"); pts(vError);
      myp("\t| Integral of data, total SM (ratio): \n"						    ); pts(vError);
      myp("\t| \t%f / %f = %f  \n",dataint,smmcint,datamcratio					    ); pts(vError);
      myp("\t| Chi^2 Test results: \n"								    ); pts(vError);
      myp("\t| \tprob=%f; Chi2=%f; ndof=%d; Chi2/ndof=%f; igood=%d\n",pval,chi2,ndof,chi2/ndof,igood); pts(vError);
      myp("\t| Kolmogorov Test results: (prob << 1 means not compatible) \n"			    );pts(vError);
      myp("\t| \tprob=%f ; prob (w/o \"N\")=%f \n",ktestn,ktest					    ); pts(vError);
      myp("\t  -----------------------------  End Stats Tests  -----------------------------  \n\n" ); pts(vError);
    }

    //Draw everything
    //

    hblank->Draw("hist"); // Draw dummy hist first!
    if ( !isempty ) {
      if ( dostack_ ) {
        thestack_->Draw("hist same");
        hblank->GetXaxis()->SetTitle(var->getXtitle());    
        hblank->GetXaxis()->SetLabelOffset(xlabeloffset_);
        hblank->GetXaxis()->SetTitleOffset(xtitleoffset_);
        hblank->GetYaxis()->SetTitle(var->getYtitle());
        hblank->GetYaxis()->SetLabelOffset(ylabeloffset_);
        hblank->GetYaxis()->SetTitleOffset(ytitleoff);
      }
      else {
        for (std::vector<Dataset>::iterator ds = thebgmc_.begin(); ds != thebgmc_.end(); ++ds) {
          ds->getHist()->Draw("hist same lpe");
          ds->getHist()->GetXaxis()->SetTitle(var->getXtitle());    
          ds->getHist()->GetXaxis()->SetLabelOffset(xlabeloffset_);
          ds->getHist()->GetXaxis()->SetTitleOffset(xtitleoffset_);
          ds->getHist()->GetYaxis()->SetTitle(var->getYtitle());
          ds->getHist()->GetYaxis()->SetLabelOffset(ylabeloffset_);
          ds->getHist()->GetYaxis()->SetTitleOffset(ytitleoff);
          ds->getHist()->SetMinimum(hmin);
          ds->getHist()->SetMaximum(hmax);
          hblank->GetXaxis()->SetTitle(var->getXtitle());    
          hblank->GetXaxis()->SetLabelOffset(xlabeloffset_);
          hblank->GetXaxis()->SetTitleOffset(xtitleoffset_);
          hblank->GetYaxis()->SetTitle(var->getYtitle());
          hblank->GetYaxis()->SetLabelOffset(ylabeloffset_);
          hblank->GetYaxis()->SetTitleOffset(ytitleoff);
        }
      }
    }

    if ( !isempty && drawmcerr_ && dostack_ ) {
      if ( mcerr_ != 0 ) delete mcerr_;
      mcerr_ = new TGraphErrors(totalsm_);
      mcerr_->SetFillStyle(3244); //3353 3544 3244 3001
      mcerr_->SetFillColor(kGray+2);
      //ack. TGraphs and TH1s use different conventions for numbering.
      for ( int ibin = 1; ibin <= totalsm_->GetNbinsX(); ++ibin ) {
        double yerr = mcerr_->GetErrorY(ibin-1);
        //optionally add mc stat error in quadrature with the b-tag sf uncertainty and top pt weight uncertainty

        //if (drawTopPtErrors_) yerr = sqrt( yerr*yerr + pow(getSystematicError(totalsm_,totalsm_topptP1,totalsm_topptM1,ibin),2));
        //if (drawBTagErrors_)  yerr = sqrt( yerr*yerr + pow(getSystematicError(totalsm_,totalsm_btagP1 ,totalsm_btagM1 ,ibin),2));

        //propagate back into totalsm. this is relevant for the ratio plot
        //if (drawTopPtErrors_||drawBTagErrors_)    totalsm_->SetBinError(ibin,yerr);

        //nb: could take a different strategy, and instead of combining the total data and MC errors into one error bar on 
        //on the ratio plot, could plot *only* data stat error on the point on the ratio plot, and plot all MC errors on a shaded band
        //on the ratio plot. but i won't do that for now

        double xerr = totalsm_->GetBinCenter(ibin) - totalsm_->GetBinLowEdge(ibin);
        mcerr_->SetPointError(ibin-1,xerr,yerr);
      }
      mcerr_->Draw("2 same");
    }

    for (std::vector<Dataset>::iterator ds = thesigmc_.begin(); !isempty && ds != thesigmc_.end(); ++ds) {
      ds->getHist()->Draw("hist same");
    }

    //TODO: should thedata always be size 1??
    if ( !isempty && hasdata_ && isThereData() ) thedata_.begin()->getHist()->Draw("PE same");
    hblank->SetLineWidth(1);
    hblank->Draw("axis same");
    if ( (isThereSigMC() || !drawratio_) ) {
      TLine * lblank = new TLine(var->getXlow(),hmin,var->getXhigh(),hmin);
      lblank->SetLineWidth(2);
      //lblank->Draw("same");
    }
     
    // Draw other things on top of the plot 
    //   
      
    if ( thelin_.size() > 0 ) {
      for (std::vector<TLine *>::iterator lin = thelin_.begin(); lin != thelin_.end(); ++lin) { 
        // Allow vertical line to be drawn according to the current hmin/max
        // Can adjust by multiplicative factor by user with negative number (i.e. -2.1)
        // Note: The TLines in thelin are not actually drawn, a dummy TLine is used instead
        TLine * line = (TLine*) (*lin)->Clone();
        float extra = 1.0; if ( logy_ ) extra = 2.1;
        if ( line->GetY1() < 0 ) { line->SetY1(hmin*fabs(line->GetY1())      ); }
        if ( line->GetY2() < 0 ) { line->SetY2(hmax*fabs(line->GetY2())/extra); }
        line->Draw(); 
      }
    }
    if ( var->getText() != "" ) {
      textinside2_ = var->getText() ;
    }
    if ( drawleg_           ) theleg_->Draw ();
    if ( drawlatex_         ) drawPlotHeader();
    if ( ptext_       !=  0 ) ptext_->Draw  ();
    if ( textinside_  != "" ) drawText()      ;
    if ( textinside2_ != "" ) drawExtraText() ;
 
    //Draw a Data/MC plot at bottom of canvas
    if ( !isempty && drawratio_ ) {
      thecan_->cd(2);
      if      ( hasdata_             ) ratio_->Divide(thedata_.begin()->getHist(),totalsm_);
      else if ( thebgmc_.size() == 2 ) ratio_->Divide(thebgmc_.begin()->getHist(),(thebgmc_.begin()+1)->getHist());
      else {
        myp("Attempting to draw ratio plot but don't know what samples to use, please check datasets. Exiting."); pts(vError);
        exit(0);
      }
      ratio_->SetMinimum(ratiomin_);
      ratio_->SetMaximum(ratiomax_);

      ratio_->SetLineColor(1);
      ratio_->SetLineStyle(1);
      ratio_->SetLineWidth(1);
      ratio_->SetMarkerColor(1);
      ratio_->SetMarkerStyle(8);
      ratio_->SetMarkerSize(0.5);

      ratio_->GetYaxis()->SetNdivisions(500 + int(ratiomax_-ratiomin_)+2);
 
      ratio_->GetXaxis()->SetTitle(var->getXtitle()); 
      ratio_->GetXaxis()->SetTitleSize(0.14);
      ratio_->GetXaxis()->SetLabelSize(0.09); //make y label bigger, orig 0.1
      ratio_->GetXaxis()->SetLabelOffset(0.008);
      ratio_->GetXaxis()->SetTitleOffset(xtitleoffset_-.39);
      ratio_->GetYaxis()->SetTitle(ratioytitle_);
      ratio_->GetYaxis()->SetTitleSize(0.10);
      ratio_->GetYaxis()->SetTitleOffset(0.55);
      ratio_->GetYaxis()->SetLabelSize(0.09);//0.08 

      gPad->SetTopMargin(1e-5);
      gPad->SetTickx();
      gPad->Modified();     

      ratio_->Draw("peX0");
      //Add line at ratio of 1
      ratiolin_->SetLineStyle(2);
      ratiolin_->Draw("same");
    }

    if ( addpgnumbers_ ) drawPageNumber(varnum);

    //Save it, somewhere. 
    int hold = gErrorIgnoreLevel;
    gErrorIgnoreLevel = 2000;
    if ( savegraph1_ ) { 
      if ( var->getPlotname() == "" ) thecan_->SaveAs(getSaveName1(var->getVarname()+s_varnum));
      else                            thecan_->SaveAs(getSaveName1(var->getPlotname()        ));
    }
    if ( savegraph2_ ) thecan_->Print(getSaveName2(0));
    if ( savegraph3_ ) fileout_->Write();
    gErrorIgnoreLevel = hold;

    textinside_  = "";
    textinside2_ = "";
    hblank->Clear();
    hblank->Reset();

    int t = sw.RealTime() ;
    TString print;
    print.Form("=============== Finished plotting var, %s, in %02.0f:%02.0f ==============\n\n", var->getVarname().Data(), (double)(t/60),(double)(t%60));
    myp("%s",print.Data()); pts(vError);

  }//thevar loop

}


void DrawTree::autoAddDatasets(TString path, TString what, TString back) {

  TString front = "/*";
  TString trig = "";
  

  //BG MC
  if ( what.Contains("other") || what == "" ) {
    Dataset ds1(path+front+"ttHJetTobb_*"+back+trig,"Other",vArgentineBlue,1,treename_);
    ds1.addFile(path+front+"TTZTo*-*"+back+trig);
    ds1.addFile(path+front+"TTWJetsTo*-*"+back+trig);
    ds1.addFile(path+front+"ZH_*-*"+back+trig);
    ds1.addFile(path+front+"WH_*-*"+back+trig);
    ds1.addFile(path+front+"WWTo*-*"+back+trig);
    ds1.addFile(path+front+"WZTo*-*"+back+trig);
    ds1.addFile(path+front+"ZZTo*-*"+back+trig);
    ds1.addFile(path+front+"TTTT-*"+back+trig);
    ds1.addFile(path+front+"WWZ-*"+back+trig);
    ds1.addFile(path+front+"WZZ-*"+back+trig);
    ds1.addFile(path+front+"ZZZ-*"+back+trig);
    thebgmc_.push_back(ds1);
  }
  if ( what.Contains("singlet") || what == "" ) {
    Dataset ds(path+front+"ST_*"+back+trig,"Singlet",vKingsPurple,1,treename_);
    thebgmc_.push_back(ds);
  }
  if ( what.Contains("wjets") || what == "" ) {
    thebgmc_.push_back(Dataset(path+front+"WJetsToLNu_HT-*"+back+trig,"WJets",vSabercatGreen,1,treename_));
  }
  if ( what.Contains("zinv") || what.Contains("zjets") || what == "" ) {
    thebgmc_.push_back(Dataset(path+front+"ZJetsToNuNu_HT-*"+back+trig,"ZJets",vNinerRed,1,treename_)); //StanfordRed w/lostlep?
  }
  if ( what.Contains("allqcd") || what == "" ) {
    thebgmc_.push_back(Dataset(path+front+"QCD_HT-*"+back+trig,"QCD",vWarriorYellow,1,treename_));
  }
  if ( what.Contains("indqcd") ) {
    Dataset ds1(path+front+"QCD_HT-200to300*"+back,"QCD-HT-200-300",kBlack);
    Dataset ds2(path+front+"QCD_HT-300to500*"+back,"QCD-HT-300-500",vNinerRed);
    Dataset ds3(path+front+"QCD_HT-500to700*"+back,"QCD-HT-500-700",vArgentineBlue);
    Dataset ds4(path+front+"QCD_HT-700to1000*"+back,"QCD-HT-700to1000",vSabercatGreen);
    Dataset ds5(path+front+"QCD_HT-1000to1500*"+back,"QCD-HT-1000to1500",vGiantOrange);
    Dataset ds6(path+front+"QCD_HT-1500to2000*"+back,"QCD-HT-1500to2000",vWarriorYellow);
    Dataset ds7(path+front+"QCD_HT-2000toInf*"+back,"QCD-HT-2000toInf",vKingsPurple);
    thebgmc_.push_back(ds1); thebgmc_.push_back(ds2); thebgmc_.push_back(ds3);
    thebgmc_.push_back(ds4); thebgmc_.push_back(ds5); thebgmc_.push_back(ds6);
    thebgmc_.push_back(ds7); 
  }
  if ( what.Contains("ttbar-ind") || what == "" ) {
    thebgmc_.push_back(Dataset(path+front+"TTJets-skim*"+back+trig,"ttbar",vQuakesBlue,1,treename_));
  }
  if ( what.Contains("ttbar-full") || what == "" ) {
    thebgmc_.push_back(Dataset(path+front+"TTJets_FULL*"+back+trig,"ttbar",vQuakesBlue,1,treename_));
  }
  if ( what.Contains("lostlep") ) {
    Dataset ds(path+front+"ST_*"+back+trig+"#(@GenTaus->size()==0)","Lost lep",vArgentineBlue,1,treename_);
    //ds.addFile(path+front+"ST_tW_*"+back);
    //ds.addFile(path+front+"ST_s-channel*"+back);
    ds.addFile(path+front+"TTJets-skim*"+back);
    //ds.addFile(path+front+"TTJets_FULL*"+back);
    ds.addFile(path+front+"WJetsToLNu_HT-*"+back);
    thebgmc_.push_back(ds);
  }
  if ( what.Contains("hadtau") ) {
    Dataset ds(path+front+"ST_*"+back+trig+"#(@GenTaus->size()>0)","Had tau",vOregonGreen,1,treename_);
    //ds.addFile(path+front+"ST_tW_*"+back);
    //ds.addFile(path+front+"ST_s-channel*"+back);
    ds.addFile(path+front+"TTJets-skim*"+back);
    //ds.addFile(path+front+"TTJets_FULL*"+back);
    ds.addFile(path+front+"WJetsToLNu_HT-*"+back);
    thebgmc_.push_back(ds);
  }
  if ( what.Contains("totalsm") ) {
    Dataset ds(path+front+"ST_t-channel_*"+back+trig,"Total SM",vArgentineBlue,1,treename_);
    ds.addFile(path+front+"ST_tW_*"+back);
    ds.addFile(path+front+"ST_s-channel*"+back);
    ds.addFile(path+front+"TTJets_FULL*"+back);
    ds.addFile(path+front+"WJetsToLNu_HT-*"+back);
    ds.addFile(path+front+"ZJetsToNuNu_HT-*"+back);
    ds.addFile(path+front+"QCD_HT-*"+back);
    ds.addFile(path+front+"ttHJetTobb_*"+back+trig);
    ds.addFile(path+front+"TTZTo*-*"+back+trig);
    ds.addFile(path+front+"TTWJetsTo*-*"+back+trig);
    ds.addFile(path+front+"ZH_*-*"+back+trig);
    ds.addFile(path+front+"WH_*-*"+back+trig);
    ds.addFile(path+front+"WWTo*-*"+back+trig);
    ds.addFile(path+front+"WZTo*-*"+back+trig);
    ds.addFile(path+front+"ZZTo*-*"+back+trig);
    ds.addFile(path+front+"TTTT-*"+back+trig);
    ds.addFile(path+front+"WWZ-*"+back+trig);
    ds.addFile(path+front+"WZZ-*"+back+trig);
    ds.addFile(path+front+"ZZZ-*"+back+trig);
    thebgmc_.push_back(ds);
  }


  //SIG MC
  if ( what.Contains("t1bbbb") || what == "" ) {
    Dataset ds1(path+front+"T1bbbb_1000_900*"+back,"T1bbbbC",vNeonOrange,kFullCircle,3,1.0); 
    Dataset ds2(path+front+"T1bbbb_1500_100*"+back,"T1bbbbH",vNeonOrange,kFullCircle,1,1.0); 
    thesigmc_.push_back(ds1);
    thesigmc_.push_back(ds2);
  }
  if ( what.Contains("t1tttt") || what == "" ) {
    Dataset ds1(path+front+"T1tttt_1200_800*"+back,"T1ttttC",vNeonGreen,kFullCircle,2,1.0); 
    Dataset ds2(path+front+"T1tttt_1500_100*"+back,"T1ttttH",vNeonGreen,kFullCircle,1,1.0); 
    thesigmc_.push_back(ds1);
    thesigmc_.push_back(ds2);
  }
  if ( what.Contains("t1qqqq") ) {
    Dataset ds1(path+front+"T1qqqq_1000_800*"+back,"T1qqqqC",vNeonPink,kFullCircle,2,1.0); 
    Dataset ds2(path+front+"T1qqqq_1400_100*"+back,"T1qqqqH",vNeonPink,kFullCircle,1,1.0); 
    thesigmc_.push_back(ds1);
    thesigmc_.push_back(ds2);
  }
  
  //DATA
  if ( what.Contains("data") || what == "" ) {
    // The "#PassTrigger" adds that as a specific selection to the dataset
    Dataset ds(path+front+"HTMHT_re2015C-skim.root#PassTrigger","Data",kBlack,kFullCircle,1,1,1,treename_); 
    ds.addFile(path+front+"HTMHT_*2015D*-skim.root");
    thedata_.push_back(ds);
  }

  //if ( what.Contains("") || what == "" ) {
  //  thebgmc_.push_back(Dataset(path+front+""+back,"",vColor));
  //}
 
}

/*

Give one ToPlot with the full selection/baseline
ex sel = MET>350&&HT>1000&&njets>4&&(nMuons+nElectrons==0)...
ex bas = cutPV==1&&passMETfilter&&...

Will extract all variables from selection and plot them N-1 style
Still experimental, use with caution

*/

void DrawTree::Nminus1plots(ToPlot tp, TString token) {

  TString base = tp.getBaseline();
  TString sel = tp.getSelection();
  TObjArray * array = sel.Tokenize(token.Data());
  std::vector<TString> strings;
  std::vector<ToPlot>   thetps;

  for ( int i = 0; i <= array->GetLast(); ++i ) { 
    TObjString * str = (TObjString*) array->At(i) ;
    TString thestr = str->String();
    strings.push_back(str->String());
    thetps.push_back(ToPlot(sel,sel,tp.getXtitle(),base,tp.getWeights(),tp.getExtra(),1,0,1));
  }   


  int j = 0;
  for ( std::vector<TString>::const_iterator itr = strings.begin(); itr != strings.end(); ++itr, ++j ) { 
    TString var = *itr;

    int symbol = 0;
    TString sym;
    if      ( var.Contains(">=") ) { symbol = 2; sym = ">="; }
    else if ( var.Contains("<=") ) { symbol = 2; sym = "<="; }
    else if ( var.Contains("==") ) { symbol = 2; sym = "=="; }
    else if ( var.Contains("!=") ) { symbol = 2; sym = "!="; }
    else if ( var.Contains("<")  ) { symbol = 1; sym = "<" ; }
    else if ( var.Contains(">")  ) { symbol = 1; sym = ">" ; }
    else    { myp("No math comparison symbol found in %s. Will break here.",var.Data()); pts(vError); exit(0); }
    
    TString rem = var; 
    if ( itr != strings.end()-1 ) rem += token; 
    else rem.Prepend(token);
    int a = var.Index(sym);  
    TString one = var;
    TString two = var;
    one.Remove(a);
    two.Remove(0,a+symbol);
    two.ReplaceAll(")","");
    two.ReplaceAll("(","");
    if ( one.Contains("(") && !one.Contains(")") ) one += ")";
    
    thetps[j].setSelection(thetps[j].getSelection().ReplaceAll(rem,""));
    if (token != "&&" ) thetps[j].setSelection(thetps[j].getSelection().ReplaceAll(token,"&&"));
    thetps[j].setVarname(one);
    thetps[j].setXtitle(one);
    thetps[j].assignAxisLimits("X"); 
    //cout << thetps[j] << endl;

  }//strings   

  addVar(thetps);

  plot();
}


void DrawTree::plotInSB(TString plotopt) {

  TStopwatch sw ;
  sw.Start() ;

  if ( drawratio_ && !(hasdata_ && isThereData()) ) { 
    if ( thebgmc_.size() == 2 ) { 
      drawratio_ = true; 
      myp("\n\nDrawing ratio plot with MC\n"); pts(vInfo);
    }
    else {
      if ( isThereData() ) myp("\n\nWARNING: Parameter 'hasdata' not set to true. Not drawing 'Data' or Data/MC ratio plot.\n");
      else myp("\n\nWARNING: No 'Data' is added to plot. Please add this Dataset in order to draw it. Not drawing Data/MC ratio plot.\n");
      pts(vWarning);
      drawratio_ = false;
    }
  }
  TString canvasOpt = drawratio_ ? "ratio" : "";
  const int mainPadIndex = drawratio_ ? 1 : 0; 
  plotopt += "";

  myp("\n\n"); pts(vInfo);

  int varnum = 0;
  ++plotnumber_ ;
  const int sbnum = thevar_.size();
  TH1D * dummy = new TH1D("dummy","",sbnum,0+0.5,sbnum+0.5);
  TH1D * hblank = (TH1D*) dummy->Clone("hblank");
  std::vector<TH1D*> theplots;

  for (std::vector<Dataset>::iterator ds = thebgmc_.begin(); ds != thebgmc_.end(); ++ds) {
    TH1D * bgplot = (TH1D*) dummy->Clone(ds->getLegname());
    theplots.push_back(bgplot);
  }

  //Loop over all vars (even if its just one)
  for (std::vector<ToPlot>::iterator var = thevar_.begin(); var != thevar_.end(); ++var, ++varnum ) {

    TString s_varnum = "_"; s_varnum += plotnumber_; s_varnum += "_"; s_varnum += varnum;

    myp("\n============  Plotting  ---> %s <--- Bin%i ============\n\n",var->getVarname().Data(),varnum+1); pts(vError);
    
    renewCanvas(canvasOpt);
    renewLegend();

    thecan_->cd(mainPadIndex);
    if ( useredxtitle_ ) var->makeSimpleXtitle();
    if ( var->getNxbins() <= 0 ) var->assignAxisLimits("X");

    if ( dostack_ ) {
      if ( thestack_ != 0 ) delete thestack_;
      thestack_ = new THStack("thestack","--");
    }
    if ( totalsm_ != 0 ) delete totalsm_;
    totalsm_ = new TH1D("totalsm","",var->getNxbins(),var->getXlow(),var->getXhigh()); 
    totalsm_->Sumw2();
    if ( drawratio_ ) {
      if ( ratio_ != 0 ) delete ratio_;
      ratio_ = new TH1D("ratio","",var->getNxbins(),var->getXlow(),var->getXhigh());
      ratio_->Sumw2();
      if ( ratiolin_ != 0 ) delete ratiolin_;
      ratiolin_ = new TLine(var->getXlow(), 1, var->getXhigh(), 1);
    }

    //TODO: Hardcoded values.. could probably open this up to the user 
    totalsm_->SetMarkerColor(vSharkBlue);
    totalsm_->SetLineColor(vSharkBlue);
    totalsm_->SetLineWidth(1);
    totalsm_->SetMarkerStyle(kOpenCircle);

    TString opt = "hist e";
    int dsnum = 0;
    //Loop over datasets
    for (std::vector<Dataset>::iterator ds = thebgmc_.begin(); ds != thebgmc_.end(); ++ds, ++dsnum) {
      TString s_dsnum = s_varnum; s_dsnum += "_"; s_dsnum += dsnum;
      if      ( hasdata_ && !luminorm_ )
        ds->project(var->getVarname()+s_dsnum,var->getVarname(),var->getFullCut(*ds,luminame_,lumi_),var->getNxbins(),var->getXlow(),var->getXhigh());
      else if ( hasdata_ ||  luminorm_ )
        ds->project(var->getVarname()+s_dsnum,var->getVarname(),var->getFullCut(*ds,luminame_,lumi_),var->getNxbins(),var->getXlow(),var->getXhigh());
      else
        ds->project(var->getVarname()+s_dsnum,var->getVarname(),var->getFullCut(*ds,""),var->getNxbins(),var->getXlow(),var->getXhigh());

      if ( addoverflow_ ) ds->addOverflow();

      ds->getHist()->SetXTitle(var->getXtitle());
      ds->getHist()->SetYTitle(var->getYtitle());
      ds->getHist()->GetXaxis()->SetLabelOffset(xlabeloffset_);
      ds->getHist()->GetXaxis()->SetTitleOffset(xtitleoffset_);
      if ( dostack_ ) ds->setHistFillColor();
      else            ds->setHistLineAndMarkColor();
      //Somewhat hacky.. but empty hists still have 1 entry. Why?
      if ( ds->getHist()->GetEntries() > 1 ) totalsm_->Add(ds->getHist());

      theplots[dsnum]->SetBinContent(varnum+1,ds->getFullEntries());
    }//thebgmc loop
    if ( dostack_ ) {
      myp("%10s passed events: %10.0f raw, %10f weighted***\n\n","***Total SM",totalsm_->GetEntries(),totalsm_->Integral(0,totalsm_->GetNbinsX()+1)); pts(vError);
    }

    //Special, unique user functions
    //-
    if ( plotopt.Contains("norm") ) {
      dsnum = 0;
      for (std::vector<Dataset>::iterator ds = thebgmc_.begin(); ds != thebgmc_.end(); ++ds, ++dsnum) {
        theplots[dsnum]->SetBinContent(varnum+1,ds->getFullEntries()/totalsm_->Integral(0,totalsm_->GetNbinsX()+1));
      }
    }
    //-


  }//thevar loop

  //Setup the legend
  //Data first, then BG MC, then Signal
  //Loop through backwards
  int dsnum = 0;
  for (std::vector<Dataset>::iterator ds = thebgmc_.begin(); ds != thebgmc_.end(); ++ds, ++dsnum) {
    theplots[dsnum]->SetFillColor(ds->getColor());
    thestack_->Add(theplots[dsnum]);
  }
  for (std::vector<TH1D *>::iterator ds = theplots.begin(); ds != theplots.end(); ++ds) {
    theleg_->AddEntry(*ds,(*ds)->GetName(),"F");
  }

  if ( histmax_ > 0 ) hblank->SetMaximum(histmax_);
  if ( histmin_ > 0 ) hblank->SetMinimum(histmin_);

  hblank->Draw("hist"); // Draw dummy hist first!
  if ( dostack_ ) {
    thestack_->Draw("hist same");
    hblank->GetXaxis()->SetTitle("Search region bin number");    
    hblank->GetXaxis()->SetLabelOffset(xlabeloffset_);
    hblank->GetXaxis()->SetTitleOffset(xtitleoffset_);
    hblank->GetYaxis()->SetTitle("Event Fraction ");
    hblank->GetYaxis()->SetLabelOffset(ylabeloffset_);
    hblank->GetYaxis()->SetTitleOffset(ytitleoffset_);
  }
  else {
    for (std::vector<TH1D*>::iterator ds = theplots.begin(); ds != theplots.end(); ++ds) {
      (*ds)->Draw("hist same lpe");
      (*ds)->GetXaxis()->SetTitle("Search region bin number");    
      (*ds)->GetXaxis()->SetLabelOffset(xlabeloffset_);
      (*ds)->GetXaxis()->SetTitleOffset(xtitleoffset_);
      (*ds)->GetYaxis()->SetTitle("Event Fraction ");
      (*ds)->GetYaxis()->SetLabelOffset(ylabeloffset_);
      (*ds)->GetYaxis()->SetTitleOffset(ytitleoffset_);
      //ds->getHist()->SetMinimum(hmin);
      //ds->getHist()->SetMaximum(hmax);
      hblank->GetXaxis()->SetTitle("Search region bin number");    
      hblank->GetXaxis()->SetLabelOffset(xlabeloffset_);
      hblank->GetXaxis()->SetTitleOffset(xtitleoffset_);
      hblank->GetYaxis()->SetTitle("Event Fraction ");
      hblank->GetYaxis()->SetLabelOffset(ylabeloffset_);
      hblank->GetYaxis()->SetTitleOffset(ytitleoffset_);
    }
  }

  hblank->SetLineWidth(1);
  hblank->Draw("axis same");
     
  // Draw other things on top of the plot 
  //   
      
  //if ( thethevar_.begin()_.begin()->getText() != "" ) {
  //  textinside2_ = thethevar_.begin()_.begin()->getText() ;
  //}
  drawSBText(histmin_,histmax_);
  if ( drawleg_           ) theleg_->Draw ();
  if ( drawlatex_         ) drawPlotHeader();
  if ( ptext_       !=  0 ) ptext_->Draw  ();
  if ( textinside_  != "" ) drawText()      ;
  if ( textinside2_ != "" ) drawExtraText() ;
 
  //Draw a Data/MC plot at bottom of canvas
  //Not implemented yet for the SB plots..
  /*
    if ( drawratio_ ) {
      thecan_->cd(2);
      if      ( hasdata_             ) ratio_->Divide(thedata_.begin()->getHist(),totalsm_);
      else if ( thebgmc_.size() == 2 ) ratio_->Divide(thebgmc_.begin()->getHist(),(thebgmc_.begin()+1)->getHist());
      else {
        myp("Attempting to draw ratio plot but don't know what samples to use, please check datasets. Exiting."); pts(vError);
        exit(0);
      }
      ratio_->SetMinimum(ratiomin_);
      ratio_->SetMaximum(ratiomax_);

      ratio_->SetLineColor(1);
      ratio_->SetLineStyle(1);
      ratio_->SetLineWidth(1);
      ratio_->SetMarkerColor(1);
      ratio_->SetMarkerStyle(8);
      ratio_->SetMarkerSize(0.5);

      ratio_->GetYaxis()->SetNdivisions(500 + int(ratiomax_-ratiomin_)+2);
 
      ratio_->GetXaxis()->SetTitle(thevar_.begin()->getXtitle()); 
      ratio_->GetXaxis()->SetTitleSize(0.14);
      ratio_->GetXaxis()->SetLabelSize(0.09); //make y label bigger, orig 0.1
      ratio_->GetXaxis()->SetLabelOffset(0.008);
      ratio_->GetXaxis()->SetTitleOffset(xtitleoffset_-.39);
      ratio_->GetYaxis()->SetTitle(ratioytitle_);
      ratio_->GetYaxis()->SetTitleSize(0.10);
      ratio_->GetYaxis()->SetTitleOffset(0.55);
      ratio_->GetYaxis()->SetLabelSize(0.09);//0.08 

      gPad->SetTopMargin(1e-5);
      gPad->SetTickx();
      gPad->Modified();     

      ratio_->Draw("peX0");
      //Add line at ratio of 1
      ratiolin_->SetLineStyle(2);
      ratiolin_->Draw("same");
    }
    */

    //Save it, somewhere. 
    int hold = gErrorIgnoreLevel;
    gErrorIgnoreLevel = 2000;
    ///if ( savegraph1_ ) thecan_->SaveAs(getSaveName1(var->getVarname()+s_varnum));
    if ( savegraph2_ ) thecan_->Print(getSaveName2(0));
    if ( savegraph3_ ) fileout_->Write();
    gErrorIgnoreLevel = hold;

    hblank->Clear();
    hblank->Reset();

    int t = sw.RealTime() ;
    TString print;
    print.Form("=============== Finished plotting 72SB in %02.0f:%02.0f ==============\n\n", (double)(t/60),(double)(t%60));
    myp("%s",print.Data()); pts(vError);

}


//Make a cutflow table
//Print out to screen if not saving to file, always
//
//Main cuts in cutflow, staggered cuts, weight variable cuts, output names to each cut, output file name, apply lumi?, output event yields or percentages?, output to latex?
void DrawTree::cutflow(TString strcuts, TString strcuts2, TString strweight, TString strnames, TString strfile, bool dolumi, bool doraw, bool dolatex) {

  bool relative = true; 
  TString fullcut, lumiweight; 
  TString varcut = "NJets";
  double nbins = 100, xlo = 0, xhi = 100;
  char dump[1000];
  bool use_names = true, printout = false;
  ofstream ofs;
  int          width = 10; //Width for datasets in ascii cutflow table 
  int    label_width = 16; //Width for cuts in ascii cutflow table 
  int      precision =  3; //Numbers after decimal point for lumi counts and percentages

  if ( !dolumi ) precision = 0;
  if ( !doraw  ) precision = 3;
  if ( relative ) precision = 3;
  if (  dolumi ) { lumiweight = "*" + luminame_ + "*"; lumiweight+=lumi_; } 
  if ( dolatex  && strfile == "" ) {
    myp("Requesting LaTeX table without output file supplied. This is a requirement. Exiting\n"); pts(vError);
    exit(0);
  } 

  if ( strnames == "" ) use_names = false;
  if ( strfile  == "" ) printout  = true ;
  if ( strfile  != "" ) { 
    strfile.Prepend("Cutflow.");
    if ( dolatex ) strfile.Append(".tex");
    else           strfile.Append(".txt");
    ofs.open(strfile);
  }

  myp("\n\n\n==>> Make Cutflow table <<==\n\n\n"); pts(vError);
  myp("Settings\n"); pts(vError);
  myp("---------------------------------------------\n"  ); pts(vError);
  myp("Save to file    : %s\n"   , BOOL_STR(strfile!="") ); pts(vError);
  if ( strfile != "" ) { 
  myp("Outputfile      : %s\n"   , strfile.Data()        ); pts(vError); }
  myp("Use lumi weight : %s\n"   , BOOL_STR(dolumi )     ); pts(vError);
  if ( dolumi ) { 
  myp("Luminosity [pb] : %.1f\n" , lumi_                 ); pts(vError); }
  myp("Raw event yield : %s\n"   , BOOL_STR(doraw  )     ); pts(vError);
  myp("Latex output    : %s\n"   , BOOL_STR(dolatex)     ); pts(vError);
  myp("Use input names : %s\n"   , BOOL_STR(strnames!="")); pts(vError);
  myp("---------------------------------------------\n\n"); pts(vError);

  //Get one list of datasets
  std::vector<Dataset> datasets;
  datasets.insert(datasets.end(),thedata_ .begin(),thedata_ .end());
  datasets.insert(datasets.end(),thebgmc_ .begin(),thebgmc_ .end());
  datasets.insert(datasets.end(),thesigmc_.begin(),thesigmc_.end());

  TObjArray * array1 =  strcuts.Tokenize("$$");
  TObjArray * array2 = strcuts2.Tokenize("$$");
  TObjArray * array3 = strnames.Tokenize("$$");
  std::vector<TString> cuts1, cuts2, names;

  for ( int i = 0; i <= array1->GetLast(); ++i ) {  
    TObjString * str = (TObjString*) array1->At(i) ;
    TString thestr = str->String();
    if ( !use_names && thestr.Length() > label_width ) label_width = thestr.Length();
    cuts1.push_back(str->String());
  }    
  for ( int i = 0; i <= array2->GetLast(); ++i ) {  
    TObjString * str = (TObjString*) array2->At(i) ;
    TString thestr = str->String();
    if ( !use_names && thestr.Length() > label_width ) label_width = thestr.Length();
    cuts2.push_back(str->String());
  }    
  for ( int i = 0; i <= array3->GetLast(); ++i ) {  
    TObjString * str = (TObjString*) array3->At(i) ;
    TString thestr = str->String();
    if ( use_names && thestr.Length() > label_width ) label_width = thestr.Length();
    names.push_back(str->String());
  }    

  int ncuts  = cuts1.size();
  int ncuts2 = cuts2.size();
  int nnames = names.size();
  std::vector<double> ds_vals1;  
  std::vector<double> ds_vals2; 
  std::vector<int> dswidths;
  if ( strnames != "" && nnames < (ncuts+ncuts2) ) {
    myp("Warning: There are less cut names given than are total cuts to make. Will not use names.\n"); pts(vWarning);
    use_names = false;
  }

  //Make the table
  if ( printout ) cout << endl << endl; 
  else ofs << endl << endl; 
  if ( dolatex ) {
    ofs << "\\documentclass[11pt]{article}\n\n"  ; 
    ofs << "\\usepackage{mathtools}\n" ;
    ofs << "\\usepackage{multirow}\n" ;
    ofs << "\\usepackage{rotating}\n" ;
    ofs << "\\usepackage{geometry}\n\n\n" ;
    ofs << "\\begin{document}\n"  ; 
    ofs << "\n\n\n"  ; 
    ofs << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n" ;
    ofs << "%\\newgeometry{margin=2mm} % modify this if you need even more space\n" ;
    ofs << "%\\begin{sidewaystable} \n" ;
    ofs << "   \\centering \n" ;
    ofs << "    \\begin{tabular}{l" ;
    for (unsigned int ii = 0; ii < datasets.size(); ++ii) ofs << "|c" ;
    ofs << "}\n" ;
    ofs << "    \\hline\n" ;
  }
  TString print = "Cut";
  if ( dolatex ) print.Prepend("     ");
  int extra_width = 0;
  if ( relative ) extra_width = 7;
  for (std::vector<Dataset>::iterator ds = datasets.begin(); ds != datasets.end(); ++ds) {
    if ( dolatex ) {
      TString label = ds->getLegname(), texstr = "";
      if ( label.Contains("#") || label.Contains("{") ) texstr = "$";
      label.ReplaceAll("#","\\"); 
      if ( ds == datasets.end()-1 ) sprintf(dump," & %s%s%s \\\\ \n",texstr.Data(),label.Data(),texstr.Data());
      else sprintf(dump," & %s%s%s ",texstr.Data(),label.Data(),texstr.Data()); 
      dswidths.push_back(width);
    }
    else {
      int len = ds->getLabel().Length();
      int thewidth = width;
      if ( len >= width ) { 
        thewidth = len+1; 
        if ( relative ) thewidth -= extra_width;
      }
      dswidths.push_back(thewidth); 
      if ( ds == datasets.begin() ) sprintf(dump,"%*s|%*s ",label_width-3,"",thewidth+extra_width,ds->getLabel().Data());
      else sprintf(dump,"|%*s ",thewidth+extra_width,ds->getLabel().Data()); 
    }
    print += dump;
  }
  if ( printout ) cout << print << endl; 
  else ofs << print << endl; 
  for ( int i = 0; i < print.Length() && !dolatex; ++i ) { if ( printout ) cout << "="; else ofs << "="; }
  if ( printout ) cout << endl; 
  else ofs << endl; 
  if ( dolatex ) ofs << "    \\hline\n    \\hline\n" ;

  for ( int i = 0; i < ncuts; ++i) {
    TString cut = "((";
    for ( int j = 0; j < i + 1; ++j ) {
      cut += cuts1[j];
      if ( j != i ) cut += "&&";
    }   
    cut+="))";
    if ( strweight != "" ) { cut += "*"; cut += strweight; }
    fullcut = cut;

    TString texstr = "";
    if ( dolatex ) texstr = "     ";
    if ( use_names ) sprintf(dump,"%s%-*s",texstr.Data(),label_width,names[i].Data());
    else sprintf(dump,"%s%-*s",texstr.Data(),label_width,cuts1[i].Data());
    if ( printout ) cout << dump;
    else ofs << dump;

    //Loop over datasets
    int dsi = 0;
    for (std::vector<Dataset>::iterator ds = datasets.begin(); ds != datasets.end(); ++ds, ++dsi) {
      TString s_dsnum = "cf_" ; s_dsnum += i;
      double val = 0, tot = 0, rel = 0;
      TString thecut = cut;
      if ( !ds->getLabel().Contains("Data") ) thecut += lumiweight;
      

      if ( !doraw ) {
        TString totcut = "1"; 
        if ( !ds->getLabel().Contains("Data") ) totcut += lumiweight; //Need to take care of other event weights too
        if ( strweight != "" ) { totcut += "*"; totcut += strweight; }

        ds->project(varcut+s_dsnum+"_tot",varcut,totcut,nbins,xlo,xhi,true);
        tot = ds->getFullEntries();
      }

      //Does not take DS weight/sf into account
      ds->project(varcut+s_dsnum,varcut,thecut,nbins,xlo,xhi,true);
      val = ds->getFullEntries();
      if ( relative ) { 
        if ( i != 0 ) rel = val/ds->getSpecial();
        else          rel = 1.0;
      }
      ds->setSpecial(val);

      if ( !doraw ) val = val/tot*100;
      if ( dolatex ) {
        //if ( !doraw || !ds->getLabel().Contains("Data") ) sprintf(dump,"& %*.*f ",dswidths[dsi],precision,val);
        if ( !doraw ) sprintf(dump,"& %*.*f ",dswidths[dsi],precision,val);
        else { 
          if ( !relative ) sprintf(dump,"& %*.*f ",dswidths[dsi],precision,val);
          else sprintf(dump,"& %*.*f (%.*f)",dswidths[dsi],precision,val,precision,rel); 
        }
        if ( ds->getLabel().Contains("Data") ) sprintf(dump,"& %*.0f",dswidths[dsi],val); 
        if ( ds == datasets.end()-1 ) strcat(dump," \\\\");
      }
      else {
        //if ( !doraw || !(ds->getLabel().Contains("Data")) ) { sprintf(dump,"|%*.*f ",dswidths[dsi],precision,val); cout << "HERE" << endl;}
        if ( !doraw  ) sprintf(dump,"|%*.*f ",dswidths[dsi],precision,val); 
        else { 
          if ( !relative ) sprintf(dump,"|%*.*f ",dswidths[dsi],precision,val);
          else sprintf(dump,"|%*.*f (%.*f)",dswidths[dsi],precision,val,precision,rel); 
        }
        if ( ds->getLabel().Contains("Data") ) sprintf(dump,"|%*.0f",dswidths[dsi],val);
      }

      if ( printout ) cout << dump;
      else ofs << dump;
    }//datasets
    if ( printout ) cout << endl;
    else ofs << endl;

    if ( i != 0 ) ds_vals1.clear();
  }//cuts1

  if ( ncuts2 > 0 ) {
    for ( int i = 0; i < print.Length() && !dolatex; ++i ) { if ( printout ) cout << "-" ; else ofs << "-"; }
    if (  dolatex ) ofs  << "    \\hline\n" ;
    if ( printout ) cout << endl; 
    else ofs << endl;
  }

  //cuts2
  for ( int i = 0; i < ncuts2; ++i) {
    TString cut = "(";
    cut += fullcut;
    cut += "&&";
    cut += cuts2[i];
    cut += ")";
    if ( strweight != "" ) { cut += "*"; cut += strweight; }

    TString texstr = "";
    if ( dolatex ) texstr = "     ";
    if ( use_names ) sprintf(dump,"%s%-*s",texstr.Data(),label_width,names[ncuts+i].Data());
    else sprintf(dump,"%s%-*s",texstr.Data(),label_width,cuts2[i].Data());
    if ( printout ) cout << dump;
    else ofs << dump;

    //Loop over datasets
    int dsi = 0;
    for (std::vector<Dataset>::iterator ds = datasets.begin(); ds != datasets.end(); ++ds, ++dsi) {
      TString s_dsnum = "cf_" ; s_dsnum += i;
      double val = 0, tot = 0, rel = 0;
      TString thecut = cut;
      if ( !ds->getLabel().Contains("Data") ) thecut += lumiweight;

      TString totcut = "1"; 
      if ( !ds->getLabel().Contains("Data") ) totcut += lumiweight; //Need to take care of other weights too
      if ( strweight != "" ) { totcut += "*"; totcut += strweight; }

      ds->project(varcut+s_dsnum+"_tot",varcut,totcut,nbins,xlo,xhi,true);
      tot = ds->getFullEntries();
      ///tot=calcTotal(ds->getTree(),1);
      ///tot=calcTotal2(ds->getTree(),1);

      ds->project(varcut+s_dsnum,varcut,thecut,nbins,xlo,xhi,true);
      ///if ( addoverflow_ ) ds->addOverflow();
      val = ds->getFullEntries();
      //val=calcTotal(ds->getTree(),i+1);
      //val=calcTotal2(ds->getTree(),ds->getLabel(),i+1);
      //tot = val;
      rel = val/ds->getSpecial();

      if ( !doraw ) val = val/tot*100;
      if ( dolatex ) {
        //if ( !doraw || !ds->getLabel().Contains("Data") ) sprintf(dump,"& %*.*f ",dswidths[dsi],precision,val);
        if ( !doraw ) sprintf(dump,"& %*.*f ",dswidths[dsi],precision,val);
        else { 
          if ( !relative ) sprintf(dump,"& %*.*f ",dswidths[dsi],precision,val);
          else sprintf(dump,"& %*.*f (%.*f)",dswidths[dsi],precision,val,precision,rel); 
        }
        if ( ds->getLabel().Contains("Data") ) sprintf(dump,"& %*.0f",dswidths[dsi],val); 
        if ( ds == datasets.end()-1 ) strcat(dump," \\\\");
      }
      else {
        //if ( !doraw || !ds->getLabel().Contains("Data") ) sprintf(dump,"|%*.*f ",dswidths[dsi],precision,val);
        if ( !doraw  ) sprintf(dump,"|%*.*f ",dswidths[dsi],precision,val); 
        else { 
          if ( !relative ) sprintf(dump,"|%*.*f ",dswidths[dsi],precision,val);
          else sprintf(dump,"|%*.*f (%.*f)",dswidths[dsi],precision,val,precision,rel); 
        }
        if ( ds->getLabel().Contains("Data") ) sprintf(dump,"|%*.0f",dswidths[dsi],val);
      }

      if ( printout ) cout << dump;
      else ofs << dump;
    }
    if ( printout ) cout << endl;
    else ofs << endl;
 
  }//cuts2
  if ( printout ) cout << endl << endl;
  else ofs << endl << endl;
  if ( dolatex ) {
    ofs << "    \\hline\n" ;
    ofs << "    \\end{tabular}\n"  ;
    ofs << "   %\\caption{The yield blah}\n" ;
    ofs << " %\\end{sidewaystable}\n" ;
    ofs << " %\\restoregeometry\n" ;
    ofs << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n" ;
    ofs << "\n\n\n" ;
    ofs << "\\end{document}\n" ;
  }

  if ( savegraph3_ ) fileout_->Write();
}//end cutflow code


//Make a signal sensitivity table
//Has some custom, specific functions within  
//
void DrawTree::sens_table(Dataset bg, TString strcuts, TString strweight, TString strnames, TString strfile, TString strvar, bool dolatex) {

  strweight = ""; //TODO: implement weights
  TString fullcut, lumiweight; 
  TString sens, sens_tex; int isens;  
  TString varcut = "NJets";
  ///double nbins = 100, xlo = 0, xhi = 100;
  char dump[1000];
  bool use_names = true, printout = false;
  ofstream ofs;
  int       width = 10; //Width for datasets in ascii sensitivity table 
  int label_width = 15; //Width for cuts in ascii sensitivity table 
  int   precision =  3; //Numbers after decimal point for counts

  lumiweight = "*" + luminame_ + "*"; lumiweight+=lumi_; 
  if ( dolatex  && strfile == "" ) {
    myp("Requesting LaTeX table without output file supplied. This is a requirement. Exiting\n"); pts(vError);
    exit(0);
  } 

  strvar.ReplaceAll("(","");
  strvar.ReplaceAll(")","");
  strvar.ReplaceAll("/","");
  strvar.ReplaceAll("+","");
  strvar.ToLower();
  if ( strvar == "sb" || strvar == "soverb" ) {
    sens = "S/B"; 
    sens_tex = "S/B";
    isens = 1;
  }
  else if ( strvar == "ssqrtb" || strvar == "soversqrtb" ) {
    sens = "S/sqrt(B)"; 
    sens_tex = "S/\\sqrt{B}";
    isens = 2;
  }
  else if ( strvar == "ssqrtsb" || strvar == "soversqrtsb" || strvar == "ssqrtbs" || strvar == "soversqrtbs" ) {
    sens = "S/sqrt(S+B)"; 
    sens_tex = "S/\\sqrt{S+B}";
    isens = 3;
  }
  else if ( strvar == "q" ) {
    sens = "Q"; 
    sens_tex = "Q";
    isens = 4;
  }
  else {
    myp("Error: Do not know which sensitivity variable to calculate. Exiting\n"); pts(vError);
    exit(0);
  }

  if ( strnames == "" ) use_names = false;
  if ( strfile  == "" ) printout  = true ;
  if ( strfile != "" ) { 
    strfile.Prepend("Sens-Table.");
    if ( dolatex ) strfile.Append(".tex");
    else           strfile.Append(".txt");
    ofs.open(strfile);
  }

  myp("\n\n\n==>> Signal Sensitivity table <<==\n\n\n"   ); pts(vError);
  myp("Settings\n");                                        pts(vError);
  myp("---------------------------------------------\n"  ); pts(vError);
  myp("Save to file    : %s\n"   , BOOL_STR(strfile!="") ); pts(vError);
  myp("Sensitivity Var : %s\n"   , sens.Data()           ); pts(vError); 
  if ( strfile != "" ) { 
  myp("Outputfile      : %s\n"   , strfile.Data()        ); pts(vError); }
  myp("Latex output    : %s\n"   , BOOL_STR(dolatex)     ); pts(vError);
  myp("Use input names : %s\n"   , BOOL_STR(strnames!="")); pts(vError);
  myp("---------------------------------------------\n\n"); pts(vError);


  TObjArray * array1 =  strcuts.Tokenize("$$");
  TObjArray * array2 = strnames.Tokenize("$$");
  std::vector<TString> cuts1, names;

  for ( int i = 0; i <= array1->GetLast(); ++i ) {  
    TObjString * str = (TObjString*) array1->At(i) ;
    TString thestr = str->String();
    if ( !use_names && thestr.Length() > label_width ) label_width = thestr.Length();
    cuts1.push_back(str->String());
  }    
  for ( int i = 0; i <= array2->GetLast(); ++i ) {  
    TObjString * str = (TObjString*) array2->At(i) ;
    TString thestr = str->String();
    if ( thestr.Length() > label_width ) label_width = thestr.Length();
    names.push_back(str->String());
  }    

  int ncuts  = cuts1.size();
  int nnames = names.size();
  if ( strnames != "" && nnames < (ncuts) ) {
    myp("Warning: There are less cut names given than are total cuts to make. Will not use names.\n"); pts(vWarning);
    use_names = false;
  }

  //Make the table
  if ( printout ) cout << endl << endl; 
  else ofs << endl << endl; 
  if ( dolatex ) {
    ofs << "\\documentclass[11pt]{article}\n\n"  ; 
    ofs << "\\usepackage{mathtools}\n" ;
    ofs << "\\usepackage{multirow}\n\n\n" ;
    ofs << "\\begin{document}\n"  ; 
    ofs << "\n\n\n"  ; 
    ofs << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n" ;
    ofs << "   \\centering \n" ;
    ofs << "    \\begin{tabular}{l" ;
    for (unsigned int ii = 0; ii < thesigmc_.size(); ++ii) ofs << "|c" ;
    ofs << "}\n" ;
    ofs << "    \\hline\n" ;
  }
  TString print = sens;
  if ( dolatex ) { print = sens_tex; print.Prepend("     "); }
  for (std::vector<Dataset>::iterator ds = thesigmc_.begin(); ds != thesigmc_.end(); ++ds) {
    if ( dolatex ) {
      TString label = ds->getLegname(), texstr = "";
      if ( label.Contains("#") || label.Contains("{") ) texstr = "$";
      label.ReplaceAll("#","\\"); 
      if ( ds == thesigmc_.end()-1 ) sprintf(dump," & %s%s%s \\\\ \n",texstr.Data(),label.Data(),texstr.Data());
      else sprintf(dump," & %s%s%s ",texstr.Data(),label.Data(),texstr.Data()); 
    }
    else {
      if ( ds == thesigmc_.begin() ) sprintf(dump,"%*s|%*s ",label_width-sens.Length(),"",width,ds->getLabel().Data());
      else sprintf(dump,"|%*s ",width,ds->getLabel().Data()); 
    }
    print += dump;
  }
  if ( printout ) cout << print << endl; 
  else ofs << print << endl; 
  for ( int i = 0; i < print.Length() && !dolatex; ++i ) { if ( printout ) cout << "="; else ofs << "="; }
  if ( printout ) cout << endl; 
  else ofs << endl; 
  if ( dolatex ) ofs << "    \\hline\n    \\hline\n" ;

  //double ret = calcTotal(bg.getTree(),0);

  fullcut = "1";
  for ( int i = 0; i < ncuts; ++i) {
    TString cut = "(";
    cut += fullcut;
    cut += "&&";
    cut += cuts1[i];
    cut += ")";
    cut += lumiweight;

    TString texstr = "";
    if ( dolatex ) texstr = "     ";
    if ( use_names ) sprintf(dump,"%s%-*s",texstr.Data(),label_width,names[i].Data());
    else sprintf(dump,"%s%-*s",texstr.Data(),label_width,cuts1[i].Data());
    if ( printout ) cout << dump;
    else ofs << dump;

    //bg.project(varcut+"_bg",varcut,cut,nbins,xlo,xhi,true);
    //double totbg = bg.getFullEntries();
    //double totbg = calcTotal(bg.getTree(),i);
    double totbg = calcTotal2(bg.getTree(),bg.getLabel(),i);
    //double totbg = 1;

    //Loop over datasets
    for (std::vector<Dataset>::iterator ds = thesigmc_.begin(); ds != thesigmc_.end(); ++ds) {
      TString s_dsnum = "cf_" ; s_dsnum += i;
      double val = 0, sig = 0;

      //ds->project(varcut+s_dsnum,varcut,cut,nbins,xlo,xhi,true);
      //sig = ds->getFullEntries();
      //sig = calcTotal(ds->getTree(),i);
      sig = calcTotal2(ds->getTree(),ds->getLabel(),i);

      if      ( isens == 1 ) {
        val = sig/totbg;
      }
      else if ( isens == 2 ) {
        val = sig/sqrt(totbg);
      }
      else if ( isens == 3 ) {
        val = sig/sqrt(sig+totbg);
      }
      else if ( isens == 4 ) {
        val = 2*(sqrt(sig+totbg)-sqrt(totbg));
      }
      //double tot = calcTotal(ds->getTree(),0);
      //val = sig/tot;


      if ( dolatex ) {
        sprintf(dump,"& %*.*f ",width,precision,val);
        if ( ds == thesigmc_.end()-1 ) strcat(dump," \\\\");
      }
      else {
        sprintf(dump,"|%*f ",width,val);
      }

      if ( printout ) cout << dump;
      else ofs << dump;
    }//datasets
    if ( printout ) cout << endl;
    else ofs << endl;

  }//cuts1

  if ( printout ) cout << endl << endl;
  else ofs << endl << endl;
  if ( dolatex ) {
    ofs << "    \\hline\n" ;
    ofs << "    \\end{tabular}\n"  ;
    ofs << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n" ;
    ofs << "\n\n\n" ;
    ofs << "\\end{document}\n" ;
  }

  //saveHist(getSaveName3(),"h_");
  if ( savegraph3_ ) fileout_->Write();
  

}//end sensitivity table code

//
// Specific functions
//
//

void DrawTree::makeMDP_HiLo_Table() { 

  renewLegend(0.68,0.05,0.90,0.40);
  if ( ptext_ != 0 ) delete ptext_;
  ptext_ = new TPaveText(0.45,0.55,0.91,0.89,"brNDC");
  ptext_->SetBorderSize(1); //0 for no line
  ptext_->SetFillColor(0); //Set color to white
  ptext_->SetFillStyle(4000); //Set style to transparent
  ptext_->SetTextFont(42);
  ///ptext_->SetTextSizePixels(20);
  ptext_->SetTextSize(0.040);

  float smbg_ratio, smbg_ratioerr, smbg_lo, smbg_loerr, smbg_hi, smbg_hierr;
  float  qcd_ratio,  qcd_ratioerr,  qcd_lo,  qcd_loerr,  qcd_hi,  qcd_hierr;
  float data_ratio, data_ratioerr, data_lo, data_loerr, data_hi, data_hierr;
  float mdpcut = 0.5;
  TString text;

  addLine(mdpcut,-1,mdpcut,-0.7);

  text.Form("#Delta#phi_{min} > %3.1f H/L Ratio",mdpcut);
  ptext_->AddText(text);
  ptext_->AddLine(0.,0.79,1.,0.79);

  GetHistRatio(totalsm_, mdpcut, smbg_ratio, smbg_ratioerr, smbg_lo, smbg_loerr, smbg_hi, smbg_hierr);
  text.Form("BG: #frac{%5.2f#pm%3.2f}{%5.2f#pm%3.2f} = %1.3f#pm%0.3f",smbg_hi,smbg_hierr,smbg_lo,smbg_loerr,smbg_ratio,smbg_ratioerr);
  ptext_->AddText(text);
  for (std::vector<Dataset>::iterator ds = thebgmc_.begin(); ds != thebgmc_.end(); ++ds) {
    if ( !ds->getLabel().Contains("QCD") ) continue;
    GetHistRatio(ds->getHist(), mdpcut, qcd_ratio, qcd_ratioerr, qcd_lo, qcd_loerr, qcd_hi, qcd_hierr);
    text.Form("QCD: #frac{%5.2f#pm%3.2f}{%5.2f#pm%3.2f} = %1.3f#pm%0.3f",qcd_hi,qcd_hierr,qcd_lo,qcd_loerr,qcd_ratio,qcd_ratioerr);
    ptext_->AddText(text);  
  }
  GetHistRatio(thedata_.begin()->getHist(), mdpcut, data_ratio, data_ratioerr, data_lo, data_loerr, data_hi, data_hierr);
  text.Form("Data: #frac{%.0f#pm%3.2f}{%.0f#pm%3.2f} = %1.3f#pm%0.3f",data_hi,data_hierr,data_lo,data_loerr,data_ratio,data_ratioerr);
  ptext_->AddText(text);

}
//
void DrawTree::makeMDP_HiLo_Table2(ToPlot tp) { 

  bool print = true; //true for no output
  ToPlot var(tp.getSelection(),"10*PassMinDeltaPhi","",tp.getWeights(),tp.getExtra(),11,0,11);
  float mdpcut = 5;

  renewLegend(0.68,0.05,0.90,0.40);
  if ( !hasdata_ ) renewLegend(0.68,0.29,0.90,0.59);
  if ( ptext_ != 0 ) delete ptext_;
  ptext_ = new TPaveText(0.50,0.55,0.90,0.89,"brNDC");
  if ( !hasdata_ ) { 
    delete ptext_;
    ptext_ = new TPaveText(0.45,0.66,0.90,0.89,"brNDC");
  }
  ptext_->SetBorderSize(1); //0 for no line
  ptext_->SetFillColor(0); //Set color to white
  ptext_->SetFillStyle(4000); //Set style to transparent
  ptext_->SetTextFont(42);
  ///ptext_->SetTextSizePixels(20);
  ptext_->SetTextSize(0.038);

  float smbg_ratio, smbg_ratioerr, smbg_lo, smbg_loerr, smbg_hi, smbg_hierr;
  float  qcd_ratio,  qcd_ratioerr,  qcd_lo,  qcd_loerr,  qcd_hi,  qcd_hierr;
  float data_ratio, data_ratioerr, data_lo, data_loerr, data_hi, data_hierr;
  TString text;

  text.Form(" #Delta#phi  High/Low Ratio ");
  ptext_->AddText(text);
  if ( hasdata_ ) ptext_->AddLine(0.,0.79,1.,0.79);
  else ptext_->AddLine(0.,0.74,1.,0.74);

  TH1D * totalbg = new TH1D("totalbg","",var.getNxbins(),var.getXlow(),var.getXhigh());
  TH1D * justqcd = new TH1D("justqcd","",var.getNxbins(),var.getXlow(),var.getXhigh());
  TH1D * alldata = new TH1D("alldata","",var.getNxbins(),var.getXlow(),var.getXhigh());
  TH1D * h = new TH1D("dummy","",var.getNxbins(),var.getXlow(),var.getXhigh());
  totalbg->Sumw2();
  justqcd->Sumw2();
  alldata->Sumw2();
  int dsnum = 0;

  for (std::vector<Dataset>::iterator ds = thebgmc_.begin(); ds != thebgmc_.end(); ++ds, ++dsnum) {
    TString s_dsnum = "table"; s_dsnum += "_"; s_dsnum += dsnum;
    if      ( hasdata_ && !luminorm_ )
      h = ds->project_ret(var.getVarname()+s_dsnum,var.getVarname(),var.getFullCut(*ds,luminame_,lumi_),var.getNxbins(),var.getXlow(),var.getXhigh(),print);
    else if ( hasdata_ ||  luminorm_ )
      h = ds->project_ret(var.getVarname()+s_dsnum,var.getVarname(),var.getFullCut(*ds,luminame_,lumi_),var.getNxbins(),var.getXlow(),var.getXhigh(),print);
    else 
      h = ds->project_ret(var.getVarname()+s_dsnum,var.getVarname(),var.getFullCut(*ds,""),var.getNxbins(),var.getXlow(),var.getXhigh(),print);

     if ( ds->getLabel().Contains("QCD") ) justqcd = (TH1D*) h->Clone();
     totalbg->Add(h);

    delete h;
  }//thebgmc loop
  for (std::vector<Dataset>::iterator ds = thedata_.begin(); hasdata_ && ds != thedata_.end(); ++ds, ++dsnum) {
    TString s_dsnum = "table"; s_dsnum += "_"; s_dsnum += dsnum;

    alldata = ds->project_ret(var.getVarname()+s_dsnum,var.getVarname(),var.getFullCut(*ds,""),var.getNxbins(),var.getXlow(),var.getXhigh(),print);
  }

  GetHistRatio(totalbg, mdpcut, smbg_ratio, smbg_ratioerr, smbg_lo, smbg_loerr, smbg_hi, smbg_hierr);
  text.Form("BG: #frac{%5.2f}{%5.2f} = %1.3f #pm %0.3f",smbg_hi,smbg_lo,smbg_ratio,smbg_ratioerr);
  //text.Form("BG: #frac{%5.2f#pm%3.2f}{%5.2f#pm%3.2f} = %1.3f#pm%0.3f",smbg_hi,smbg_hierr,smbg_lo,smbg_loerr,smbg_ratio,smbg_ratioerr);
  ptext_->AddText(text);
  GetHistRatio(justqcd, mdpcut, qcd_ratio, qcd_ratioerr, qcd_lo, qcd_loerr, qcd_hi, qcd_hierr);
  text.Form("QCD: #frac{%5.2f}{%5.2f} = %1.3f #pm %0.3f",qcd_hi,qcd_lo,qcd_ratio,qcd_ratioerr);
  //text.Form("QCD: #frac{%5.2f#pm%3.2f}{%5.2f#pm%3.2f} = %1.3f#pm%0.3f",qcd_hi,qcd_hierr,qcd_lo,qcd_loerr,qcd_ratio,qcd_ratioerr);
  ptext_->AddText(text);  
  if ( hasdata_ ) {
    GetHistRatio(alldata, mdpcut, data_ratio, data_ratioerr, data_lo, data_loerr, data_hi, data_hierr);
    text.Form("Data: #frac{%.0f}{%.0f} = %1.3f #pm %0.3f",data_hi,data_lo,data_ratio,data_ratioerr);
    //text.Form("Data: #frac{%.0f#pm%3.2f}{%.0f#pm%3.2f} = %1.3f#pm%0.3f",data_hi,data_hierr,data_lo,data_loerr,data_ratio,data_ratioerr);
    ptext_->AddText(text);
  }
}

int DrawTree::findSearchBin(double ht, double mht, int njets, int nbjets) {

  const int nbin_njet = 3 ; 
  const int nbin_nb   = 4 ; 
  //const int nbin_mht  = 3 ; 
  //const int nbin_ht   = 3 ; 
  const int nbin_htmht = 6;
  float sb_njet[nbin_njet+1] = {  3.5, 6.5, 8.5, 99. } ; 
  float sb_nb  [nbin_nb  +1] = { -0.5, 0.5, 1.5, 2.5, 99. } ; 
  //float sb_mht[nbin_mht+1] = { 200., 500.,  750., 99999. } ; 
  //float sb_ht [nbin_ht +1] = { 500., 800., 1200., 99999. } ; 
  float sb_mhtht_mhtlow [nbin_htmht] = { 200., 200., 200., 500., 500.,   750. } ; 
  float sb_mhtht_mhthigh[nbin_htmht] = { 500., 500., 500., 750., 750., 99999. } ; 
  float sb_mhtht_htlow  [nbin_htmht] = { 500.,  800.,  1200.,  500.,  1200.,   800. } ; 
  float sb_mhtht_hthigh [nbin_htmht] = { 800., 1200., 99999., 1200., 99999., 99999. } ; 


  int bin_number = 0;
  int nji = 0, nbi = 0, nhtmht = 0;
  for ( ; nji < nbin_njet; ++nji ) {   
    if ( njets > sb_njet[nji] && njets <= sb_njet[nji+1] ) break;
  }
  for ( ; nbi < nbin_nb; ++nbi ) {   
    if ( nbjets > sb_nb[nbi] && nbjets <= sb_nb[nbi+1] ) break;
  }
  for ( ; nhtmht < nbin_htmht; ++nhtmht ) {   
    if ( ht > sb_mhtht_htlow[nhtmht] && ht <= sb_mhtht_hthigh[nhtmht] && mht > sb_mhtht_mhtlow[nhtmht] && mht <= sb_mhtht_mhthigh[nhtmht] ) break;
  }
  if ( nhtmht >= 6 ) return -1; 

  nhtmht+=1;
  bin_number = nhtmht + nbin_htmht*nbi + nbin_htmht*nbin_nb*nji; 
  return bin_number;

}

double DrawTree::calcTotal(TChain * tree, int flag) {

   Bool_t          HBHENoiseFilter;
   Bool_t          JetID;
   Int_t           CSCTightHaloFilter;
   Int_t           EcalDeadCellTriggerPrimitiveFilter;
   Int_t           eeBadScFilter;
   Int_t           NVtx;
   Int_t           NJets;
   Int_t           BTags;
   Int_t           Leptons;
   Int_t           isoElectronTracks;
   Int_t           isoMuonTracks;
   Int_t           isoPionTracks;
   Double_t        HT;
   Double_t        MHT;
   Double_t        MHT_Phi;
   Double_t        Weight;
   Double_t        DeltaPhi1;
   Double_t        DeltaPhi2;
   Double_t        DeltaPhi3;
   std::vector<double>  *RJetDeltaPhi;
   std::vector<double>  *RJetMinDeltaPhiEta24;
   std::vector<double>  *RJetMinDeltaPhiEta5;
   std::vector<int>     *RJetMinDeltaPhiIndexEta24;
   std::vector<int>     *RJetMinDeltaPhiIndexEta5;
   std::vector<bool>    *TriggerPass;
   std::vector<string>  *TriggerNames;
   std::vector<TLorentzVector> *Jets;
  
   HBHENoiseFilter = 0;
   JetID = 0;
   CSCTightHaloFilter = 0;
   EcalDeadCellTriggerPrimitiveFilter = 0;
   eeBadScFilter = 0;
   NVtx = 0;
   NJets = 0;
   BTags = 0;
   Leptons = 0;
   isoElectronTracks = 0;
   isoMuonTracks = 0;
   isoPionTracks = 0;
   HT = 0;
   MHT = 0;
   MHT_Phi = 0;
   Weight = 0;
   DeltaPhi1 = 0;
   DeltaPhi2 = 0;
   DeltaPhi3 = 0;
   RJetDeltaPhi = 0;
   RJetMinDeltaPhiEta24 = 0;
   RJetMinDeltaPhiEta5 = 0;
   RJetMinDeltaPhiIndexEta24 = 0;
   RJetMinDeltaPhiIndexEta5 = 0;
   TriggerPass = 0;
   TriggerNames = 0;
   Jets = 0;
  

   tree->SetBranchAddress("BTags", &BTags);
   tree->SetBranchAddress("CSCTightHaloFilter", &CSCTightHaloFilter);
   tree->SetBranchAddress("DeltaPhi1", &DeltaPhi1);
   tree->SetBranchAddress("DeltaPhi2", &DeltaPhi2);
   tree->SetBranchAddress("DeltaPhi3", &DeltaPhi3);
   tree->SetBranchAddress("EcalDeadCellTriggerPrimitiveFilter", &EcalDeadCellTriggerPrimitiveFilter);
   tree->SetBranchAddress("eeBadScFilter", &eeBadScFilter);
   tree->SetBranchAddress("HBHENoiseFilter", &HBHENoiseFilter);
   tree->SetBranchAddress("HT", &HT);
   tree->SetBranchAddress("isoElectronTracks", &isoElectronTracks);
   tree->SetBranchAddress("isoMuonTracks", &isoMuonTracks);
   tree->SetBranchAddress("isoPionTracks", &isoPionTracks);
   tree->SetBranchAddress("JetID", &JetID);
   tree->SetBranchAddress("Jets", &Jets);
   tree->SetBranchAddress("Leptons", &Leptons);
   tree->SetBranchAddress("MHT", &MHT);
   tree->SetBranchAddress("MHT_Phi", &MHT_Phi);
   tree->SetBranchAddress("NJets", &NJets);
   tree->SetBranchAddress("NVtx", &NVtx);
   tree->SetBranchAddress("RJetDeltaPhi", &RJetDeltaPhi);
   tree->SetBranchAddress("RJetMinDeltaPhiEta24", &RJetMinDeltaPhiEta24);
   tree->SetBranchAddress("RJetMinDeltaPhiEta5", &RJetMinDeltaPhiEta5);
   tree->SetBranchAddress("RJetMinDeltaPhiIndexEta24", &RJetMinDeltaPhiIndexEta24);
   tree->SetBranchAddress("RJetMinDeltaPhiIndexEta5", &RJetMinDeltaPhiIndexEta5);
   tree->SetBranchAddress("TriggerNames", &TriggerNames);
   tree->SetBranchAddress("TriggerPass", &TriggerPass);
   tree->SetBranchAddress("Weight", &Weight);

   double total = 0;
   Long64_t nentries = tree->GetEntries();
   Long64_t ientry = 0;

   //nentries = 100;
   for (Long64_t jentry=0; jentry<nentries;++jentry) {
     tree->GetEntry(jentry);
     

     if ( JetID <= 0 ) continue;
     if ( NVtx <= 0 ) continue;
     if ( eeBadScFilter <= 0 ) continue; 
     if ( CSCTightHaloFilter <= 0 ) continue;
     if ( HBHENoiseFilter <= 0 )  continue; 
     if ( (isoPionTracks+isoElectronTracks+isoMuonTracks)!=0 ) continue;
     if ( Leptons != 0 )  continue; 

     ++ientry;

     unsigned int c = 0;
     std::vector<double>::iterator dp = RJetDeltaPhi->begin();
     std::vector<double> dpvec;
     bool pass = false;
     int i = 0;
     for ( std::vector<TLorentzVector>::iterator itr = Jets->begin(); itr != Jets->end(); ++itr, ++i ) {
       if ( (itr)->Pt() > 30. && itr->Eta() < 5.0 && itr->Eta() > -5.0 ) { 
         ++c;
         if ( itr->Eta() < 2.4 && itr->Eta() > -2.4 ) dpvec.push_back(*dp);
         ++dp;
       }
     }
     if ( RJetDeltaPhi->size() != c && RJetDeltaPhi->size() > 8 ) {
       total = -1;
       cout << c << " " << RJetDeltaPhi->size() << endl;
       break;
     }

     if ( flag == 1 ) {
       pass = dpvec[0]>0.5 && dpvec[1]>0.5 && dpvec[2]>0.3 ; 
       ////pass = RJetDeltaPhi->at(0)>0.5 && RJetDeltaPhi->at(1)>0.5 && RJetDeltaPhi->at(2)>0.3 ; 
     }
     else if ( flag == 2 ) {
       pass = dpvec[0]>0.5 && dpvec[1]>0.5 && dpvec[2]>0.5 ; 
     }
     else if ( flag == 3 ) {
       pass = dpvec[0]>0.5 && dpvec[1]>0.5 && dpvec[2]>0.3 && dpvec[3]>0.3 ; 
     }
     else if ( flag == 4 ) {
       pass = dpvec[0]>0.5 && dpvec[1]>0.5 && dpvec[2]>0.5 && dpvec[3]>0.3 ; 
     }
     else if ( flag == 5 ) {
       pass = dpvec[0]>0.5 && dpvec[1]>0.5 && dpvec[2]>0.5 && dpvec[3]>0.5; 
     }
     else if ( flag == 6 ) {
       //pass = dpvec[0]>0.45 && dpvec[1]>0.45 && dpvec[2]>0.45 && dpvec[3]>0.45; 
       pass = dpvec[0]>0.5 && dpvec[1]>0.5 && dpvec[2]>0.3 && dpvec[3]>0.3 && dpvec[4]>0.3; 
     }
     else if ( flag == 7 ) {
       //pass = dpvec[0]>0.4 && dpvec[1]>0.4 && dpvec[2]>0.4 && dpvec[3]>0.4; 
       pass = dpvec[0]>0.5 && dpvec[1]>0.5 && dpvec[2]>0.5 && dpvec[3]>0.3 && dpvec[4]>0.3; 
     }
     else if ( flag == 8 ) {
       //pass = dpvec[0]>0.35 && dpvec[1]>0.35 && dpvec[2]>0.35 && dpvec[3]>0.35 ; 
       pass = dpvec[0]>0.5 && dpvec[1]>0.5 && dpvec[2]>0.5 && dpvec[3]>0.5 && dpvec[4]>0.3; 
     }
     else if ( flag == 9 ) {
       //pass = dpvec[0]>0.3 && dpvec[1]>0.3 && dpvec[2]>0.3 && dpvec[3]>0.3 ; 
       pass = dpvec[0]>0.5 && dpvec[1]>0.5 && dpvec[2]>0.5 && dpvec[3]>0.5 && dpvec[4]>0.5; 
     }
     else if ( flag == 10 ) {
       //pass = dpvec[0]>0.25 && dpvec[1]>0.25 && dpvec[2]>0.25 && dpvec[3]>0.25 ; 
       pass = dpvec[0]>0.25 && dpvec[1]>0.25 && dpvec[2]>0.25 && dpvec[3]>0.25 ; 
     }
     else pass = true;

     if ( !pass ) continue;
     total += Weight;

   }
   ///cout << "Calc total " << nentries << "  " << ientry << endl;

   return total*lumi_;

}

double DrawTree::calcTotal2(TChain * tree, TString name,  int flag) {

   if ( !savegraph3_ ) return 0;

   Bool_t          HBHENoiseFilter;
   Bool_t          JetID;
   Int_t           CSCTightHaloFilter;
   Int_t           EcalDeadCellTriggerPrimitiveFilter;
   Int_t           eeBadScFilter;
   Int_t           NVtx;
   Int_t           NJets;
   Int_t           BTags;
   Int_t           Leptons;
   Int_t           isoElectronTracks;
   Int_t           isoMuonTracks;
   Int_t           isoPionTracks;
   Double_t        HT;
   Double_t        MHT;
   Double_t        MHT_Phi;
   Double_t        Weight;
   Double_t        DeltaPhi1;
   Double_t        DeltaPhi2;
   Double_t        DeltaPhi3;
   std::vector<double>  *RJetDeltaPhi;
   std::vector<double>  *RJetMinDeltaPhiEta24;
   std::vector<double>  *RJetMinDeltaPhiEta5;
   std::vector<int>     *RJetMinDeltaPhiIndexEta24;
   std::vector<int>     *RJetMinDeltaPhiIndexEta5;
   std::vector<bool>    *TriggerPass;
   std::vector<string>  *TriggerNames;
   std::vector<TLorentzVector> *Jets;
  
   HBHENoiseFilter = 0;
   JetID = 0;
   CSCTightHaloFilter = 0;
   EcalDeadCellTriggerPrimitiveFilter = 0;
   eeBadScFilter = 0;
   NVtx = 0;
   NJets = 0;
   BTags = 0;
   Leptons = 0;
   isoElectronTracks = 0;
   isoMuonTracks = 0;
   isoPionTracks = 0;
   HT = 0;
   MHT = 0;
   MHT_Phi = 0;
   Weight = 0;
   DeltaPhi1 = 0;
   DeltaPhi2 = 0;
   DeltaPhi3 = 0;
   RJetDeltaPhi = 0;
   RJetMinDeltaPhiEta24 = 0;
   RJetMinDeltaPhiEta5 = 0;
   RJetMinDeltaPhiIndexEta24 = 0;
   RJetMinDeltaPhiIndexEta5 = 0;
   TriggerPass = 0;
   TriggerNames = 0;
   Jets = 0;
  

   tree->SetBranchAddress("BTags", &BTags);
   tree->SetBranchAddress("CSCTightHaloFilter", &CSCTightHaloFilter);
   tree->SetBranchAddress("DeltaPhi1", &DeltaPhi1);
   tree->SetBranchAddress("DeltaPhi2", &DeltaPhi2);
   tree->SetBranchAddress("DeltaPhi3", &DeltaPhi3);
   tree->SetBranchAddress("EcalDeadCellTriggerPrimitiveFilter", &EcalDeadCellTriggerPrimitiveFilter);
   tree->SetBranchAddress("eeBadScFilter", &eeBadScFilter);
   tree->SetBranchAddress("HBHENoiseFilter", &HBHENoiseFilter);
   tree->SetBranchAddress("HT", &HT);
   tree->SetBranchAddress("isoElectronTracks", &isoElectronTracks);
   tree->SetBranchAddress("isoMuonTracks", &isoMuonTracks);
   tree->SetBranchAddress("isoPionTracks", &isoPionTracks);
   tree->SetBranchAddress("JetID", &JetID);
   tree->SetBranchAddress("Jets", &Jets);
   tree->SetBranchAddress("Leptons", &Leptons);
   tree->SetBranchAddress("MHT", &MHT);
   tree->SetBranchAddress("MHT_Phi", &MHT_Phi);
   tree->SetBranchAddress("NJets", &NJets);
   tree->SetBranchAddress("NVtx", &NVtx);
   tree->SetBranchAddress("RJetDeltaPhi", &RJetDeltaPhi);
   tree->SetBranchAddress("RJetMinDeltaPhiEta24", &RJetMinDeltaPhiEta24);
   tree->SetBranchAddress("RJetMinDeltaPhiEta5", &RJetMinDeltaPhiEta5);
   tree->SetBranchAddress("RJetMinDeltaPhiIndexEta24", &RJetMinDeltaPhiIndexEta24);
   tree->SetBranchAddress("RJetMinDeltaPhiIndexEta5", &RJetMinDeltaPhiIndexEta5);
   tree->SetBranchAddress("TriggerNames", &TriggerNames);
   tree->SetBranchAddress("TriggerPass", &TriggerPass);
   tree->SetBranchAddress("Weight", &Weight);

   double total = 0;
   Long64_t nentries = tree->GetEntries();
   Long64_t ientry = 0;

   int sb = 72;
   name.ReplaceAll(" ","");
   TString hname = "h_"; hname += name; hname += "_"; hname += flag; 
   TH1D * hist = new TH1D(hname,hname,sb,1,sb); //72 SB
   double content[sb];
   for ( int i = 0; i < sb; ++i ) { content[i] = 0; }
   

   ///cout << "Calc total " << nentries << endl;
   //nentries = 100;
   for (Long64_t jentry=0; jentry<nentries;++jentry) {
     tree->GetEntry(jentry);
     

     if ( JetID <= 0 ) continue;
     if ( NVtx <= 0 ) continue;
     if ( eeBadScFilter <= 0 ) continue; 
     if ( CSCTightHaloFilter <= 0 ) continue;
     if ( HBHENoiseFilter <= 0 )  continue; 
     if ( (isoPionTracks+isoElectronTracks+isoMuonTracks)!=0 ) continue;
     if ( Leptons != 0 )  continue; 

     ++ientry;

     unsigned int c = 0;
     std::vector<double>::iterator dp = RJetDeltaPhi->begin();
     std::vector<double> dpvec;
     bool pass = false;
     int i = 0;
     for ( std::vector<TLorentzVector>::iterator itr = Jets->begin(); itr != Jets->end(); ++itr, ++i ) {
       if ( (itr)->Pt() > 30. && itr->Eta() < 5.0 && itr->Eta() > -5.0 ) { 
         ++c;
         if ( itr->Eta() < 2.4 && itr->Eta() > -2.4 ) dpvec.push_back(*dp);
         ++dp;
       }
     }
     if ( RJetDeltaPhi->size() != c && RJetDeltaPhi->size() > 8 ) {
       total = -1;
       cout << c << " " << RJetDeltaPhi->size() << endl;
       break;
     }

     if ( flag == 1 ) {
       pass = dpvec[0]>0.5 && dpvec[1]>0.5 && dpvec[2]>0.3 ; 
       ////pass = RJetDeltaPhi->at(0)>0.5 && RJetDeltaPhi->at(1)>0.5 && RJetDeltaPhi->at(2)>0.3 ; 
     }
     else if ( flag == 2 ) {
       pass = dpvec[0]>0.5 && dpvec[1]>0.5 && dpvec[2]>0.5 ; 
     }
     else if ( flag == 3 ) {
       pass = dpvec[0]>0.5 && dpvec[1]>0.5 && dpvec[2]>0.3 && dpvec[3]>0.3 ; 
     }
     else if ( flag == 4 ) {
       pass = dpvec[0]>0.5 && dpvec[1]>0.5 && dpvec[2]>0.5 && dpvec[3]>0.3 ; 
     }
     else if ( flag == 5 ) {
       pass = dpvec[0]>0.5 && dpvec[1]>0.5 && dpvec[2]>0.5 && dpvec[3]>0.5; 
     }
     else if ( flag == 6 ) {
       //pass = dpvec[0]>0.45 && dpvec[1]>0.45 && dpvec[2]>0.45 && dpvec[3]>0.45; 
       pass = dpvec[0]>0.5 && dpvec[1]>0.5 && dpvec[2]>0.3 && dpvec[3]>0.3 && dpvec[4]>0.3; 
     }
     else if ( flag == 7 ) {
       //pass = dpvec[0]>0.4 && dpvec[1]>0.4 && dpvec[2]>0.4 && dpvec[3]>0.4; 
       pass = dpvec[0]>0.5 && dpvec[1]>0.5 && dpvec[2]>0.5 && dpvec[3]>0.3 && dpvec[4]>0.3; 
     }
     else if ( flag == 8 ) {
       //pass = dpvec[0]>0.35 && dpvec[1]>0.35 && dpvec[2]>0.35 && dpvec[3]>0.35 ; 
       pass = dpvec[0]>0.5 && dpvec[1]>0.5 && dpvec[2]>0.5 && dpvec[3]>0.5 && dpvec[4]>0.3; 
     }
     else if ( flag == 9 ) {
       //pass = dpvec[0]>0.3 && dpvec[1]>0.3 && dpvec[2]>0.3 && dpvec[3]>0.3 ; 
       pass = dpvec[0]>0.5 && dpvec[1]>0.5 && dpvec[2]>0.5 && dpvec[3]>0.5 && dpvec[4]>0.5; 
     }
     else if ( flag == 10 ) {
       //pass = dpvec[0]>0.25 && dpvec[1]>0.25 && dpvec[2]>0.25 && dpvec[3]>0.25 ; 
       pass = dpvec[0]>0.25 && dpvec[1]>0.25 && dpvec[2]>0.25 && dpvec[3]>0.25 ; 
     }
     else pass = true;

     if ( pass ) {
       content[findSearchBin(HT,MHT,NJets,BTags)-1] += Weight*lumi_;
       total += Weight;
     }


   }
   ///cout << "Calc total " << nentries << "  " << ientry << endl;

   for ( int i = 0; i < sb; ++i ) { 
     hist->SetBinContent(i+1,content[i]); 
     hist->SetBinError(i+1,sqrt(content[i])); 
   }

   return total*lumi_;

}


