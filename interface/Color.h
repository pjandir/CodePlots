
#ifndef COLOR_H
        #define COLOR_H

#include "TColor.h"
#include "ToPlot.h"

enum vColors 
{ 
  vNinerRed      = 2001, vArsenalRed     = 2002, vStanfordRed  = 2003,
  vArgentineBlue = 2021, vSharkBlue      = 2022, vQuakesBlue   = 2023,
  vSabercatGreen = 2041, vOregonGreen    = 2042, vIndianGreen  = 2043,
  vGiantOrange   = 2061, vSharkOrange    = 2062, vDutchOrange  = 2063,
  vWarriorYellow = 2081, vAthleticYellow = 2082, vUCRYellow    = 2083,
  vKingsPurple   = 2101, vKStatePurple   = 2102, vUCRPurple    = 2103,
  vNeonPink      = 2121, vNeonGreen      = 2122, vNeonOrange   = 2123,
  vNinerGold     = 3001, vKingsSilver    = 3002, vQuakesSilver = 3003
};


class Color
{
private:
  int  id_; 
  float r_;
  float g_;
  float b_;

  
public:

  Color();
  Color(int a1, int a2, int a3, int a4);

  int getId() const { return id_; } 

  static std::vector<Color> init();
  static void plotTheColors();
  TColor * convert() const { return new TColor(id_,r_,g_,b_); }
  TColor convert2() const { return TColor(id_,r_,g_,b_); }

}; // class Color 

#endif
