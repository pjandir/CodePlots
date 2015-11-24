

#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <map>
#include <cmath>
#include <set>

#include "TROOT.h"
#include "TRint.h"
#include "TSystem.h"
#include "TObjectTable.h"
#include "TError.h"
#include "TFile.h"
#include "TInterpreter.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TCut.h"
#include "TLatex.h"
#include "THStack.h"
#include "TLine.h"
#include "TStopwatch.h"
#include "TGraphAsymmErrors.h"
#include "TGraphErrors.h"
#include "TRegexp.h"
#include "TChain.h"
#include "TChainElement.h"
#include "TAxis.h"
#include "TGaxis.h"
#include "TPaveStats.h"
#include "TProfile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TF1.h"
#include "TList.h"
#include "TIterator.h"
#include "TLorentzVector.h"


// Simple helper methods and other miscellanea 
// -------------------------------------------
//

//Make dictionary for accessing vectors of TLorentzVector
#ifdef __MAKECINT__
#pragma link C++ class vector<TLorentzVector>+;
#endif

//Used as shorthand for sprintf into the global char array
#define myp(...) sprintf(rt::myout,__VA_ARGS__)

//Easy printout for bools
#define BOOL_STR(b) ((b)?"true":"false")


//Used for verbose levels of printing during execution
//Identical to TError.h (except 'v' instead of 'k')
enum VerbosityLevels {vPrint=0,vInfo=1000,vWarning=2000,vError=3000,vBreak=4000,vSysError=5000,vFatal=6000,vUnset=-1};


//Namespace
//Use for print out as well as other useful functions/logic
namespace rt
{

  //
  // Print stuff
  //

  //Used as global printout variable
  char myout[1000];
  //Used as global verbosity level
  //Default is print everything
  int verbose = 0;

  //Print To Screen: with verbosity levels included (See VerbosityLevels Enum class above)
  //Default string is built-in global char array -- myout
  //Default behavior is zero, i.e. vPrint
  void pts(int v = vPrint) { 
    if ( v >= gErrorIgnoreLevel ) std::cout << myout ;
    //if ( v >= verbose ) std::cout << myout ;
  }
  //Just in case
  void pts(char * str, int v = vPrint) { 
    if ( v >= gErrorIgnoreLevel ) std::cout << str ;
    //if ( v >= verbose ) std::cout << str ;
  }

  //
  // Other stuff
  //
  
  void SaveHist(const char* filename, const char* pat) {
    TList* list = gDirectory->GetList() ;
    TIterator* iter = list->MakeIterator();

    TRegexp re(pat,kTRUE) ;

    TFile outf(filename,"UPDATE") ;
    //TFile outf(filename,"RECREATE") ;
    TObject* obj ;
    while((obj=iter->Next())) {    
      if (TString(obj->GetName()).Index(re)>=0) {
        obj->Write() ;
        std::cout << "." ;
      }   
    }
    std::cout << std::endl ;
    outf.Close() ;

    delete iter ;
  }


  void GetHistRatio( TH1D * hp, float cut, float& rval, float& rerr, float& vlo, float& vloerr, float& vhi, float& vhierr ) {

    rval = 0.; rerr   = 0.;
    vlo  = 0.; vloerr = 0.;
    vhi  = 0.; vhierr = 0.;
    if ( hp == 0x0 ) return;

    TAxis * xaxis = hp -> GetXaxis();
    int nbins = hp->GetNbinsX();
    int cbi = 0;

    for ( int bi = 1; bi <= nbins; ++bi ) {
       if ( xaxis -> GetBinLowEdge(bi) >= cut ) {
          cbi = bi;
          break;
       }
    } // bi

    double ivl, iel, ivh, ieh;
    ivl = hp -> IntegralAndError( 1, cbi-1, iel );
    ivh = hp -> IntegralAndError( cbi, nbins, ieh );
    vlo = ivl; vloerr = iel;
    vhi = ivh; vhierr = ieh;
    if ( ivl > 0 ) rval = ivh / ivl;
    if ( ivh > 0 && ivl > 0 ) rerr = rval * sqrt( pow(iel/ivl,2) + pow(ieh/ivh,2) );
    return;
  }

  //implemented in TMath in later versions of root, so i'm using the TMath name
  //borrowed from Josh
  bool AreEqualAbs(const double & a, const double & b, const double epsilon=0.001) {
    return ( fabs(a-b) < epsilon ) ; 
  }

  bool ContainsMathSym(TString s) {
    if ( s.Contains("+") ) return true;
    if ( s.Contains("-") ) return true;
    if ( s.Contains("*") ) return true;
    if ( s.Contains("/") ) return true;
    return false;
  }

  TString GetFileName(TString s) {
    std::string name ( s.Data() ) ;
    unsigned long pos = name.find_last_of("/");
    TString ret;
    if ( pos != std::string::npos ) {
    ret = name.substr(pos+1);
    }
    else {
      ret = name;
    }
    return ret;
   }


}// end namespace

