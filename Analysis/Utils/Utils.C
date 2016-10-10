#define Utils_cxx
//////////////////////////////////////////////////////////////////////
// 
// Author   : Atlas LPNHE Paris
// Creation : 01/10/2015
// Purpose  : utilities
// Updated  :
//////////////////////////////////////////////////////////////////////

#include "Utils.h"

#include <TStyle.h>
#include <TCanvas.h>
#include <TObjArray.h>
#include <TH1.h>
#include <TH2.h>
#include <TMath.h> 

ClassImp(Utils);

// Constructor
Utils::Utils() 
{
}

// ================================================================
// DESTRUCTOR:
Utils::~Utils()
{ 
} 

// ==============================================================
double Utils::deltaR(double eta1, double eta2, double phi1, double phi2) 
{
  //
  // angular distance between two objects
  //

  double dPhi=deltaPhi(phi1,phi2);
  double dEta=std::fabs(eta1-eta2);
  double dR=std::sqrt(std::pow(dEta,2)+std::pow(dPhi,2));
  return dR;
}
  
// ==============================================================
double Utils::deltaPhi(double phi1, double phi2) 
{
  //
  // azimuthal distance between two objects
  //

  double dPhi=std::fabs(phi1-phi2);
  if (dPhi>M_PI) dPhi=2*M_PI-dPhi;
  return dPhi;
}

// ===============================================================
double Utils::CalcdeltaPhi2(double phi1, double phi2) 
{
  //
  // azimuthal distance between two objects
  //

  double dPhi=phi1-phi2;
  if (dPhi>M_PI)  dPhi=2*M_PI-dPhi;
  if (dPhi<-M_PI) dPhi=2*M_PI+dPhi;
  return dPhi;
}

// ===============================================================
double Utils::transMass(double ptLep, double phiLep, 
			double met, double phiMet) 
{
  //
  // transverse mass made of a lepton and missing transverse momentum
  //

  return std::sqrt(2.0*ptLep*met*( 1 - std::cos( phiLep-phiMet ) ) );
}
