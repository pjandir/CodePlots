
#include "../interface/DrawTree.h"

using std::cout;
using std::endl;
using namespace rt;

//
//
// Special, custom functions 
//    
//
//


std::vector<ToPlot> makeSearchBinTPs(ToPlot tp) {

  char mht_name [10] = "MHT"   ;
  char ht_name  [10] = "HT"    ;
  char njet_name[10] = "NJets" ;
  char nb_name  [10] = "BTags" ;

  const int nbin_njet  = 3 ; 
  const int nbin_nb    = 4 ; 
  const int nbin_mhtht = 6 ; 
  char sb_njet_name [nbin_njet] [10] = { "Njet456", "Njet78", "Njet9+" } ; 
  char sb_nb_name   [nbin_nb]   [10] = { "Nb0", "Nb1", "Nb2", "Nb3+" } ; 
  char sb_mhtht_name[nbin_mhtht][10] = { "MHT1-HT1", "MHT1-HT2", "MHT1-HT3", "MHT2-HT12", "MHT2-HT3", "MHT3-HT23" } ; 
  float sb_njet_bins    [nbin_njet+1] = {  3.5, 6.5, 8.5, 20. } ; 
  float sb_nb_bins      [nbin_nb  +1] = { -0.5, 0.5, 1.5, 2.5, 20. } ; 
  float sb_mhtht_mhtlo[nbin_mhtht ] = { 200., 200.,    200.,  500.,   500.,   750. } ; 
  float sb_mhtht_mhthi[nbin_mhtht ] = { 500., 500.,    500.,  750.,   750., 20000. } ; 
  float sb_mhtht_htlo [nbin_mhtht ] = { 500., 800.,   1200.,  500.,  1200.,   800. } ; 
  float sb_mhtht_hthi [nbin_mhtht ] = { 800., 1200., 20000., 1200., 20000., 20000. } ;   

  std::vector<ToPlot> thetps;

  int bin_number = 0;
  for ( int nji=0; nji<nbin_njet; nji++ ) { 
    char nj_cut[1000] ;
    sprintf( nj_cut, "%s>%.1f&&%s<=%.1f", njet_name, sb_njet_bins[nji], njet_name, sb_njet_bins[nji+1] ) ; 
    for ( int nbi=0; nbi<nbin_nb; nbi++ ) { 
      char nb_cut[1000] ;
      sprintf( nb_cut, "%s>%.1f&&%s<=%.1f", nb_name, sb_nb_bins[nbi], nb_name, sb_nb_bins[nbi+1] ) ; 
      for ( int htmhti=0; htmhti<nbin_mhtht; htmhti++ ) { 
        char ht_cut  [1000];
        char mht_cut [1000];
        TString label;

        ++bin_number;

        label.Form( "Search Bin %d  :  %s-%s-%s", bin_number, sb_njet_name[nji], sb_nb_name[nbi], sb_mhtht_name[htmhti] ) ;
        sprintf( ht_cut , "%s>%.1f&&%s<%.1f", ht_name , sb_mhtht_htlo[htmhti] , ht_name , sb_mhtht_hthi[htmhti]  ) ; 
        sprintf( mht_cut, "%s>%.1f&&%s<%.1f", mht_name, sb_mhtht_mhtlo[htmhti], mht_name, sb_mhtht_mhthi[htmhti] ) ; 
        TString all_cuts;
        all_cuts.Form( "&&((%s)&&(%s)&&(%s)&&(%s))", nb_cut, nj_cut, mht_cut, ht_cut ) ;

        ToPlot newtp(tp.getSelection()+all_cuts,tp.getVarname(),tp.getNxbins(),tp.getXlow(),tp.getXhigh());
        newtp.setBaseline(tp.getBaseline());
        newtp.setExtra(tp.getExtra());
        newtp.setText((TString)label);
        thetps.push_back(newtp);

      } //htmht
    } //nj
  } //nb

  return thetps;

}

std::vector<ToPlot> makeFineBinOwenTPs(ToPlot tp, TString elabel = "", bool axislimit = true, TString pname = "") {

  char mht_name [10] = "MHT"   ;
  char ht_name  [10] = "HT"    ;
  char njet_name[10] = "NJets" ;
  char nb_name  [10] = "BTags" ;

  const int nbin_njet = 5 ; 
  const int nbin_nb   = 4 ; 
  const int nbin_mht  = 4 ; 
  const int nbin_ht   = 3 ; 
  char fb_njet_name[nbin_njet][20] = { "Njet1a [4]", "Njet1b [5]", "Njet1c [6]", "Njet2 [7-8]", "Njet3 [9+]" } ; 
  char fb_nb_name  [nbin_nb  ][20] = {    "Nb0 [0]",    "Nb1 [1]",    "Nb2 [2]",    "Nb3 [3+]" } ; 
  char fb_mht_name [nbin_mht ][20] = { "MHT1a [200-300]", "MHT1b [300-500]", "MHT2 [500-750]", "MHT3 [750+]" } ; 
  char fb_ht_name  [nbin_ht  ][20] = {   "HT1 [500-800]",  "HT2 [800-1200]",    "HT3 [1200+]" } ; 
  float fb_njet    [nbin_njet+1] = {  3.5, 4.5, 5.5, 6.5, 8.5, 20. } ; 
  float fb_nb      [nbin_nb  +1] = { -0.5, 0.5, 1.5, 2.5, 20. } ; 
  float fb_mht[nbin_mht+1] = { 200., 300.,  500.,   750., 99999. } ; 
  float fb_ht [nbin_ht +1] = { 500., 800., 1200., 99999. } ; 

  std::vector<ToPlot> thetps;

  TString all_cuts, cut, label;
  for ( int nji=0; nji<nbin_njet; nji++ ) { 
    label.Form( "%s", fb_njet_name[nji] ) ;
    all_cuts.Form( "&&((%s>%f)&&(%s<%f))", njet_name, fb_njet[nji], njet_name, fb_njet[nji+1] ) ;

    ToPlot newtp(tp.getSelection()+all_cuts,tp.getVarname(),tp.getNxbins(),tp.getXlow(),tp.getXhigh());
    newtp.setBaseline(tp.getBaseline());
    newtp.setExtra(tp.getExtra());
    newtp.setText(label+" "+elabel);
    TString plotname = pname; plotname += "-nj"; plotname += nji+1;
    if ( pname != "" ) newtp.setPlotname(plotname);
    if ( axislimit ) newtp.assignAxisLimits("X");
    thetps.push_back(newtp);
  } //njet
  for ( int nbi=0; nbi<nbin_nb; nbi++ ) { 
    label.Form( "%s", fb_nb_name[nbi] ) ;
    all_cuts.Form( "&&((%s>%f)&&(%s<%f))", nb_name, fb_nb[nbi], nb_name, fb_nb[nbi+1] ) ;

    ToPlot newtp(tp.getSelection()+all_cuts,tp.getVarname(),tp.getNxbins(),tp.getXlow(),tp.getXhigh());
    newtp.setBaseline(tp.getBaseline());
    newtp.setExtra(tp.getExtra());
    newtp.setText(label+" "+elabel);
    TString plotname = pname; plotname += "-nb"; plotname += nbi+1;
    if ( pname != "" ) newtp.setPlotname(plotname);
    if ( axislimit ) newtp.assignAxisLimits("X");
    thetps.push_back(newtp);
  } //nb
  for ( int mhti=0; mhti<nbin_mht; mhti++ ) { 
    label.Form( "%s", fb_mht_name[mhti] ) ;
    all_cuts.Form( "&&((%s>%f)&&(%s<%f))", mht_name, fb_mht[mhti], mht_name, fb_mht[mhti+1] ) ;

    ToPlot newtp(tp.getSelection()+all_cuts,tp.getVarname(),tp.getNxbins(),tp.getXlow(),tp.getXhigh());
    newtp.setBaseline(tp.getBaseline());
    newtp.setExtra(tp.getExtra());
    newtp.setText(label+" "+elabel);
    TString plotname = pname; plotname += "-mht"; plotname += mhti+1;
    if ( pname != "" ) newtp.setPlotname(plotname);
    if ( axislimit ) newtp.assignAxisLimits("X");
    thetps.push_back(newtp);
  } //mht
  for ( int hti=0; hti<nbin_ht; hti++ ) { 
    label.Form( "%s", fb_ht_name[hti] ) ;
    all_cuts.Form( "&&((%s>%f)&&(%s<%f))", ht_name, fb_ht[hti], ht_name, fb_ht[hti+1] ) ;

    ToPlot newtp(tp.getSelection()+all_cuts,tp.getVarname(),tp.getNxbins(),tp.getXlow(),tp.getXhigh());
    newtp.setBaseline(tp.getBaseline());
    newtp.setExtra(tp.getExtra());
    newtp.setText(label+" "+elabel);
    TString plotname = pname; plotname += "-ht"; plotname += hti+1;
    if ( pname != "" ) newtp.setPlotname(plotname);
    if ( axislimit ) newtp.assignAxisLimits("X");
    thetps.push_back(newtp);
  } //ht

  return thetps;

}


/*
//Another experimental method
void DrawTree::plot2D_sb(TString plot, TString sel, TString base) {
TString what = plot; what += base; what += sel;
temp taken out

  TString totaldummy = plot; totaldummy += sel;
  rightmargin_ = 0.14;
  renewCanvas("");
  thecan->cd(0);

  //Signal definition
  int nsearch_njet = 3 ; 
  int nsearch_nb = 4 ; 
  int nsearch_mhtht = 6 ; 

  char search_njet_name[3][10] = { "Njet456", "Njet78", "Njet9+" } ; 
  char search_nb_name[4][10] = { "Nb0", "Nb1", "Nb2", "Nb3+" } ; 
  char search_mhtht_name[6][10] = { "MHT1-HT1", "MHT1-HT2", "MHT1-HT3", "MHT2-HT12", "MHT2-HT3", "MHT3-HT23" } ; 

  float search_njet_bins[4] = { 3.5, 6.5, 8.5, 20. } ; 
  float search_nb_bins[5] = { -0.5, 0.5, 1.5, 2.5, 20. } ; 
  float search_mhtht_mhtlow[6]  = { 200., 200., 200., 500., 500.,   750. } ; 
  float search_mhtht_mhthigh[6] = { 500., 500., 500., 750., 750., 20000. } ; 
  float search_mhtht_htlow[6]  = { 500.,  800.,  1200.,  500.,  1200.,   800. } ; 
  float search_mhtht_hthigh[6] = { 800., 1200., 20000., 1200., 20000., 20000. } ; 

  ++plotnumber_ ;
  int dsnum = 0;
  TString s_varnum = "_"; s_varnum += plotnumber_;
  TString opt = "hist text colz";

  for (std::vector<Dataset>::iterator ds = thebgmc.begin(); ds != thebgmc.end(); ++ds, ++dsnum) {
    TString s_dsnum = s_varnum; s_dsnum += "_"; s_dsnum += dsnum;

             int bin_number = 0 ; 
             for ( int nji=0; nji<nsearch_njet; nji++ ) {  // don't bother filling unused first one.

               char nj_cut[1000] ;
               sprintf( nj_cut, "njets30 > %.1f && njets30 <= %.1f", search_njet_bins[nji], search_njet_bins[nji+1] ) ; 

               for ( int nbi=0; nbi<nsearch_nb; nbi++ ) { 

                  char nb_cut[1000] ;
                  sprintf( nb_cut, "nbjets30 > %.1f && nbjets30 <= %.1f", search_nb_bins[nbi], search_nb_bins[nbi+1] ) ; 

                  for ( int htmhti=0; htmhti<nsearch_mhtht; htmhti++ ) {
                      char label[1000] ;
                      char leptons_cut[1000] ;
                      char ldp_cut[1000] ;
                      char sel_cut[1000] ;
                      char ht_cut[1000] ;
                      char mht_cut[1000] ;
                      char all_cuts[10000] ;
                      char hname[1000] ;
                      char htitle[1000] ;
                      char arg1[1000] ;

                      ++bin_number;

                      sprintf( label, "SB-%s-%s-%s %d", search_njet_name[nji], search_nb_name[nbi], search_mhtht_name[htmhti], bin_number) ;

                      //Lepton veto
                      sprintf( leptons_cut, "nElectrons == 0 && nMuons == 0" ) ;
                      //mdp cut
                      sprintf( ldp_cut, "minDeltaPhiN_pt30 > 6.0" ) ;
                      sprintf( sel_cut, "((%s) && (%s))", ldp_cut, leptons_cut ) ;

                      sprintf( ht_cut, "HT30 > %.1f && HT30 < %.1f", search_mhtht_htlow[htmhti], search_mhtht_hthigh[htmhti] ) ;
                      sprintf( mht_cut, "MHT > %.1f && MHT < %.1f", search_mhtht_mhtlow[htmhti], search_mhtht_mhthigh[htmhti] ) ;

                      //Histogram name and title
                      sprintf( hname, "h_nb%d_nj%d_nhtmht%d_%s_%d", nbi, nji+1, htmhti+1, sname[si], bin_number ) ;

                      //Get all the cuts
                      sprintf( all_cuts, "((%s) && (%s) && (%s) && (%s) && (%s))*weight3*%.0f*%.6e", sel_cut, nb_cut, nj_cut, mht_cut, ht_cut, integrated_lumi_ipb, weights[si] ) ;
                      printf("====>  %s : sample%d, Nb%d, Nj%d HTMHT%d %d, %s\n", hname, si, nbi, nji, htmhti, bin_number, all_cuts ) ;


              } //htmht
            }//nbjet
          }//njet

    ds->project2D(strp[1]+"_"+strp[0]+s_dsnum,strp[1]+":"+strp[0],base,nbinx-1,binx,nbiny-1,biny);
    ds->getHist2D()->Draw(opt);
    ds->getHist2D()->GetXaxis()->SetLabelOffset(xlabeloffset_);
    ds->getHist2D()->GetXaxis()->SetTitleOffset(xtitleoffset_);
    ds->getHist2D()->GetYaxis()->SetLabelOffset(ylabeloffset_);
    ds->getHist2D()->GetYaxis()->SetTitleOffset(ytitleoffset_);
    ds->getHist2D()->GetXaxis()->SetRangeUser(0,1500);
    ds->getHist2D()->GetYaxis()->SetRangeUser(0,1000);
    gPad->Update();
    ds->getHist2D()->SetTitle(";HT;MHT");

    if ( drawlatex_    ) drawPlotHeader()      ;
    if ( addpgnumbers_ ) drawPageNumber(dsnum);
    //Save it, somewhere. 
    int hold = gErrorIgnoreLevel;
    gErrorIgnoreLevel = 2000;
    if ( savegraph2_ ) thecan->Print(getSaveName2(0));
    gErrorIgnoreLevel = hold;

  } 

 cout << "fin" << endl;
}
*/

/*
void DrawTree::plot2D_sb(TString plot, TString sel, TString base) {

  TObjArray * arrayp = plot.Tokenize("&&");
  TObjArray * arrays = sel.Tokenize("&&");
  std::vector<TString> strp, strs;
  std::vector<double> limx, limy;

  for ( int i = 0; i <= arrayp->GetLast(); ++i ) {  
    TObjString * ostr = (TObjString*) arrayp->At(i);
    TObjArray * ap = ostr->String().Tokenize(":");
    for ( int j = 0; j <= ap->GetLast(); ++j ) {
      TObjString * osp = (TObjString*) ap->At(j);
      if ( j == 0 ) { strp.push_back(osp->String()); continue;}
      if ( i == 0 ) limy.push_back(osp->String().Atof());
      if ( i == 1 ) limx.push_back(osp->String().Atof());
    }
  }    

  delete arrayp;
  //delete arrayp, arrays;
  const int nbinx = limx.size();
  const int nbiny = limy.size();
  double binx[nbinx], biny[nbiny];
  for ( int i = 0; i < nbinx; ++i ) {
    binx[i] = limx[i];
  }
  for ( int i = 0; i < nbiny; ++i ) {
    biny[i] = limy[i];
  }

  rightmargin_ = 0.14;
  renewCanvas("");
  thecan->cd(0);

  ++plotnumber_ ;
  int dsnum = 0;
  TString s_varnum = "_"; s_varnum += plotnumber_;
  TString opt = "hist text colz";

  for (std::vector<Dataset>::iterator ds = thebgmc.begin(); ds != thebgmc.end(); ++ds, ++dsnum) {
    TString s_dsnum = s_varnum; s_dsnum += "_"; s_dsnum += dsnum;

    ds->project2D(strp[1]+"_"+strp[0]+s_dsnum,strp[1]+":"+strp[0],base,nbinx-1,binx,nbiny-1,biny);
    ds->getHist2D()->Draw(opt);
    ds->getHist2D()->GetXaxis()->SetLabelOffset(xlabeloffset_);
    ds->getHist2D()->GetXaxis()->SetTitleOffset(xtitleoffset_);
    ds->getHist2D()->GetYaxis()->SetLabelOffset(ylabeloffset_);
    ds->getHist2D()->GetYaxis()->SetTitleOffset(ytitleoffset_);
    ds->getHist2D()->GetXaxis()->SetRangeUser(0,1500);
    ds->getHist2D()->GetYaxis()->SetRangeUser(0,1000);
    gPad->Update();
    ds->getHist2D()->SetTitle(";HT;MHT");

    if ( drawlatex_    ) drawPlotHeader()      ;
    if ( addpgnumbers_ ) drawPageNumber(dsnum);
    //Save it, somewhere. 
    int hold = gErrorIgnoreLevel;
    gErrorIgnoreLevel = 2000;
    if ( savegraph2_ ) thecan->Print(getSaveName2(0));
    gErrorIgnoreLevel = hold;

  } 



 cout << "fin" << endl;
}
*/


