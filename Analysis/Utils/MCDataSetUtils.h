#ifndef MCDataSetUtils_h
#define MCDataSetUtils_h
//////////////////////////////////////////////////////////////////////
// 
// Author   : Atlas LPNHE Paris
// Creation : 01/10/2015
// Purpose  : Utilities to handle MC datasets
// Updated  :
//////////////////////////////////////////////////////////////////////

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TObjArray.h>
#include <TMath.h>

#include <TH1F.h>
#include <iostream>
#include <fstream>

class MCDataSetUtils 
{

 public:

  // constructor
  MCDataSetUtils();
  
  // destructor
  virtual ~MCDataSetUtils();

  float XSection(int mcChannelNumber);
  
 private:

  float m_xs;
  float m_kf;

  // define the class for the cint dictionary
  ClassDef(MCDataSetUtils,1)
    
};

#endif // MCDataSetUtils_h
