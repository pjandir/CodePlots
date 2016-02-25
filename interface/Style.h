

//
// Style, palette and color definitions: global functions
//


void setPalette(TStyle * ts) {
  //Set Rainbow Palette with max continuity 
  const Int_t NRGBs = 5;
  const Int_t NCont = 999; //255 is probably enough

  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t red  [NRGBs] = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue [NRGBs] = { 0.51, 1.00, 0.12, 0.00, 0.00 };
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  ts->SetNumberContours(NCont);

}

//The custom color vector
///std::vector<TColor *> theColors;

//The style
TStyle *theStyle = 0;
void initStyle(TString ts) {

  //Load info for all custom colors
  std::vector<Color> mycolors = Color::init(); 
  std::vector<TColor *> theColors;

  //Create all custom TColors
  for ( std::vector<Color>::const_iterator col = mycolors.begin(); col != mycolors.end(); ++col )
    theColors.push_back(col->convert());
 

  //Define full style
  if (theStyle==0 && gROOT->GetStyle("CMS")==0 && ts == "CMS") {
    theStyle = new TStyle("CMS","Style for P-TDR");

    setPalette(theStyle);

    // For the canvas:
    theStyle->SetCanvasBorderMode(0);
    theStyle->SetCanvasColor(kWhite);
    theStyle->SetCanvasDefH(600); //Height of canvas
    theStyle->SetCanvasDefW(600); //Width of canvas
    theStyle->SetCanvasDefX(0);   //POsition on screen
    theStyle->SetCanvasDefY(0);

    // For the Pad:
    theStyle->SetPadBorderMode(0);
    //theStyle->SetPadBorderSize(Width_t size = 1);
    theStyle->SetPadColor(kWhite);
    theStyle->SetPadGridX(false);
    theStyle->SetPadGridY(false);
    theStyle->SetGridColor(0);
    theStyle->SetGridStyle(3);
    theStyle->SetGridWidth(1);

    // For the frame:
    theStyle->SetFrameBorderMode(0);
    theStyle->SetFrameBorderSize(1);
    theStyle->SetFrameFillColor(0);
    theStyle->SetFrameFillStyle(0);
    theStyle->SetFrameLineColor(1);
    theStyle->SetFrameLineStyle(1);
    theStyle->SetFrameLineWidth(1);
  
    // For the histo:
    //theStyle->SetHistFillColor(1);
    //theStyle->SetHistFillStyle(0);
    theStyle->SetHistLineColor(1);
    theStyle->SetHistLineStyle(0);
    theStyle->SetHistLineWidth(1);
    //theStyle->SetLegoInnerR(Float_t rad = 0.5);
    //theStyle->SetNumberContours(Int_t number = 20);

    theStyle->SetEndErrorSize(2);
    //theStyle->SetErrorMarker(20);
    //theStyle->SetErrorX(0.);
              
    theStyle->SetMarkerStyle(20);
  
    //For the fit/function:
    theStyle->SetOptFit(1);
    theStyle->SetFitFormat("5.4g");
    theStyle->SetFuncColor(2);
    theStyle->SetFuncStyle(1);
    theStyle->SetFuncWidth(1);

    //For the date:
    theStyle->SetOptDate(0);
    //theStyle->SetDateX(Float_t x = 0.01);
    //theStyle->SetDateY(Float_t y = 0.01);

    // For the statistics box:
    theStyle->SetOptFile(0);
    theStyle->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");
    theStyle->SetStatColor(kWhite);
    theStyle->SetStatFont(42);
    theStyle->SetStatFontSize(0.025);
    theStyle->SetStatTextColor(1);
    theStyle->SetStatFormat("6.4g");
    theStyle->SetStatBorderSize(1);
    theStyle->SetStatH(0.1);
    theStyle->SetStatW(0.15);
    //theStyle->SetStatStyle(Style_t style = 1001);
    //theStyle->SetStatX(Float_t x = 0);
    //theStyle->SetStatY(Float_t y = 0);

    // Margins:
    theStyle->SetPadTopMargin(0.05);
    theStyle->SetPadBottomMargin(0.13);
    theStyle->SetPadLeftMargin(0.16);
    theStyle->SetPadRightMargin(0.02);

    // For the Global title:
    //theStyle->SetOptTitle(0);
    theStyle->SetTitleFont(42);
    theStyle->SetTitleColor(1);
    theStyle->SetTitleTextColor(1);
    theStyle->SetTitleFillColor(10);
    theStyle->SetTitleFontSize(0.05);
    //theStyle->SetTitleH(0); // Set the height of the title box
    //theStyle->SetTitleW(0); // Set the width of the title box
    //theStyle->SetTitleX(0); // Set the position of the title box
    //theStyle->SetTitleY(0.985); // Set the position of the title box
    //theStyle->SetTitleStyle(Style_t style = 1001);
    //theStyle->SetTitleBorderSize(2);

    // For the axis titles:
    theStyle->SetTitleColor(1, "XYZ");
    theStyle->SetTitleFont(42, "XYZ");
    theStyle->SetTitleSize(0.06, "XYZ");
    //theStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
    //theStyle->SetTitleYSize(Float_t size = 0.02);
    theStyle->SetTitleXOffset(0.9);
    theStyle->SetTitleYOffset(1.25);
    //theStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset

    // For the axis labels:
    theStyle->SetLabelColor(1, "XYZ");
    theStyle->SetLabelFont(42, "XYZ");
    theStyle->SetLabelOffset(0.007, "XYZ");
    theStyle->SetLabelSize(0.05, "XYZ");

    // For the axis:
    theStyle->SetAxisColor(1, "XYZ");
    theStyle->SetStripDecimals(kTRUE);
    theStyle->SetTickLength(0.03, "XYZ");
    theStyle->SetNdivisions(510, "XYZ");
    theStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
    theStyle->SetPadTickY(1);

    // Change for log plots:
    theStyle->SetOptLogx(0);
    theStyle->SetOptLogy(0);
    theStyle->SetOptLogz(0);

    // Postscript options:
    theStyle->SetPaperSize(20.,20.);
    //theStyle->SetLineScalePS(Float_t scale = 3);
    //theStyle->SetLineStyleString(Int_t i, const char* text);
    //theStyle->SetHeaderPS(const char* header);
    //theStyle->SetTitlePS(const char* pstitle);

    //theStyle->SetBarOffset(Float_t baroff = 0.5);
    //theStyle->SetBarWidth(Float_t barwidth = 0.5);
    //theStyle->SetPaintTextFormat(const char* format = "g");
    //theStyle->SetPalette(Int_t ncolors = 0, Int_t* colors = 0);
    //theStyle->SetTimeOffset(Double_t toffset);
    //theStyle->SetHistMinimumZero(kTRUE);

    //theStyle->SetHatchesLineWidth(5);
    //theStyle->SetHatchesSpacing(0.05);
 
    theStyle->cd(); //what does this do?
    //end CMS style
    
  }

  //My style based on CMS tdr style and 'Modern'
  //Much of it is perhaps not necessary
  //Note that in order to bring back 'bold' global title switch to 'Plain'
  if ( ts == "me" ) {
    
//    theStyle = new TStyle("me","My Style");
    theStyle = gROOT->GetStyle("Modern");

    theStyle->SetOptFile(0);
    theStyle->SetOptStat(0);
    setPalette(theStyle);
    //theStyle->SetPalette(1);
    // Margins
    theStyle->SetPadTopMargin(0.08);
    theStyle->SetPadBottomMargin(0.12);
    theStyle->SetPadLeftMargin(0.12);
    theStyle->SetPadRightMargin(0.04);
    // For the global title
    theStyle->SetTitleFont(42);
    theStyle->SetTitleColor(1);
    theStyle->SetTitleTextColor(1);
    theStyle->SetTitleFillColor(10);
    theStyle->SetTitleFontSize(0.05);
    theStyle->SetTitleBorderSize(0);
    theStyle->SetTitleX(0.5);
    theStyle->SetTitleAlign(23); //Note: this is SetTitleAlign(vh) where v and h are independent numbers. 
                                 //'v' can be 1,2,3 for left,center,right. 'h' can be 1,2,3 for bottom,middle,top.
    // For the axis titles:
    theStyle->SetTitleColor(1, "XYZ");
    theStyle->SetTitleFont(42, "XYZ");
    theStyle->SetTitleSize(0.06, "XYZ");
    theStyle->SetTitleXOffset(0.7);
    theStyle->SetTitleYOffset(0.24);
    // For the axis labels:
    theStyle->SetLabelColor(1, "XYZ");
    theStyle->SetLabelFont(42, "XYZ");
    theStyle->SetLabelOffset(0.004, "XYZ");
    //theStyle->SetLabelOffset(0.007, "XYZ");
    theStyle->SetLabelSize(0.06, "XYZ");
    // For the axis:
    theStyle->SetAxisColor(1, "XYZ");
    theStyle->SetStripDecimals(kTRUE);
    theStyle->SetTickLength(0.03, "XYZ");
    theStyle->SetNdivisions(510, "XYZ");
    theStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
    theStyle->SetPadTickY(1);

    theStyle->cd();

  }

}

