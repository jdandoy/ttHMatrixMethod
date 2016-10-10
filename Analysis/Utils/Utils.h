#ifndef Utils_h
#define Utils_h
//////////////////////////////////////////////////////////////////////
// 
// Author   : Atlas LPNHE Paris
// Creation : 01/10/2015
// Purpose  : base class for utilities
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

class Utils 
{

 public:

  // constructor
  Utils();
  
  // destructor
  virtual ~Utils();

  // angular distance between two objects
  double deltaR(double eta1, double eta2, double phi1, double phi2); 
  // azimuthal distance between two objects
  double deltaPhi(double phi1, double phi2);
  // azimuthal distance between two objects
  double CalcdeltaPhi2(double phi1, double phi2);
  // transverse mass
  double transMass(double ptLep, double phiLep, 
		   double met, double phiMet); 
 
 private:

  // define the class for the cint dictionary
  ClassDef(Utils,1)
    
};

#endif // Utils_h
