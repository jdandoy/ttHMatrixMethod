#include "TLegend.h"
#include "TProfile.h"
#include "AtlasUtils.h"
#include "AtlasLabels.h"
#include "AtlasStyle.h"
#include "TMath.h"
#include "TString.h"
#include "TGraph.h"
#include <vector>
#include <string>
#include <cmath>

void plotControlSemiLeptonicFakesOnly()
{

  gROOT->LoadMacro("AtlasStyle.C");
  gROOT->LoadMacro("AtlasUtils.C");
  gROOT->LoadMacro("AtlasLabels.C");

  SetAtlasStyle();

  //TString inputdatadir = "/data/atlas0/data/DATA/DATA15/DAOD_TOPQ1/filt/HistFinal/SemiLeptonic/";
  //TString inputmcdir   = "/data/atlas0/data/MC/MC15/DAOD_TOPQ1/filt/HistFinal/SemiLeptonic/";
  TString inputdatadir = "/home/derue/public/data/13TeV/DATA15/DAOD_TOPQ1/filt/HistFinal/SemiLeptonic/";
  TString inputmcdir   = "/home/derue/public/data/13TeV/MC/MC15/DAOD_TOPQ1/filt/HistFinal/SemiLeptonic/";
  TString destdir = "fig-semileptonic/";
  TString iso = "";

  //plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_2j_pretag", iso, destdir, false);
  //plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_2j_ge2btag", iso, destdir, false);
  //plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_ge4j_pretag", iso, destdir, false);
  //plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_ge4j_ge1btag", iso, destdir, false);

  //plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_ge2j_pretag", iso, destdir, false);
  //plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge2j_pretag", iso, destdir, false);
  //plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_2j_pretag", iso, destdir, false);
  //plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_2j_ge2btag", iso, destdir, false);
  //plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_ge4j_ge1btag", iso, destdir, false);

  //plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_ge2j_pretag", iso, destdir, false);
  //plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_ge4j_ge1btag", iso, destdir, false);
  //plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_ge4j_ge1btag", iso, destdir, false);
  //plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_2j_alltag", iso, destdir, false);
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_ge4j_ge1btag", iso, destdir, false);
  myplot->execute();
  //delete myplot;
  // ============================================================
  // for electrons
  //
  /*  
  // pretag no cut on MET and MTW
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_ge6j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_6j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_ge5j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_5j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_ge4j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_4j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_ge3j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_3j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_ge2j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_2j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_ge1j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_1j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // pretag MET and MTW>30 GeV
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_ge6j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_6j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_ge5j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_5j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_ge4j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_4j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_ge3j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_3j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_ge2j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_2j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_ge1j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_1j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  */  
  /*  
          
  // pretag MET>20 && MET+MTW>60 GeV
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_ge6j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_6j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_ge5j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_5j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_ge4j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_4j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_ge3j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_3j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_ge2j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_2j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_ge1j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_1j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // pretag MET<20 && MET+MTW<60 GeV
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_ge6j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_6j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_ge5j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_5j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_ge4j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_4j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_ge3j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_3j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_ge2j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot; 
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_2j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_ge1j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_1j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // pretag MET+MTW<60 GeV
  //     
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_ge6j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_6j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_ge5j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_5j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_ge4j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_4j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_ge3j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_3j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_ge2j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_2j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_ge1j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_1j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
*/
  // ==================================================================
  //  =================================================================
  /*
  // alltag no cut on MET and MTW
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_ge6j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_6j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_ge5j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_5j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_ge4j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_4j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_ge3j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_3j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_ge2j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_2j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_ge1j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_1j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // alltag MET and MTW>30 GeV
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_ge6j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_6j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_ge5j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_5j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_ge4j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_4j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_ge3j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_3j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_ge2j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_2j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_ge1j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_1j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // alltag MET>20 && MET+MTW>60 GeV
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_ge6j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_6j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_ge5j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_5j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_ge4j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_4j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_ge3j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_3j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_ge2j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_2j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_ge1j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_1j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // alltag MET+MTW<60 GeV
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_ge6j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_6j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_ge5j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_5j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_ge4j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_4j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_ge3j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_3j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  */
  /*
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_ge2j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_2j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_ge1j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_1j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  */

  // ==================================================================
  //  =================================================================
  /*  
  // 0btag no cut on MET and MTW
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_ge6j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_6j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_ge5j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_5j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_ge4j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_4j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_ge3j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_3j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_ge2j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_2j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_ge1j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_1j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // 0btag MET and MTW>30 GeV
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_ge6j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_6j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_ge5j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_5j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_ge4j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_4j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_ge3j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_3j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_ge2j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_2j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_ge1j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_1j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // 0btag MET>20 && MET+MTW>60 GeV
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_ge6j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_6j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_ge5j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_5j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_ge4j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_4j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_ge3j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_3j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_ge2j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_2j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_ge1j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_1j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // 0 btag MET<20 && MET+MTW<60 GeV
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_ge6j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_6j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_ge5j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_5j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_ge4j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_4j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_ge3j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_3j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_ge2j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot; 
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_2j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_ge1j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_1j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // 0btag MET+MTW<60 GeV
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_ge6j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_6j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_ge5j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_5j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_ge4j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_4j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_ge3j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_3j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_ge2j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_2j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_ge1j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_1j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  */
  // ==================================================================
  //  =================================================================
  /*    
  // ge1btag no cut on MET and MTW
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_ge6j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_6j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_ge5j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_5j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_ge4j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_4j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_ge3j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_3j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_ge2j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_2j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_ge1j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_1j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // ge1btag MET and MTW>30 GeV
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_ge6j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_6j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_ge5j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_5j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_ge4j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_4j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_ge3j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_3j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_ge2j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_2j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_ge1j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_1j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // ge1btag MET>20 && MET+MTW>60 GeV
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_ge6j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_6j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_ge5j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_5j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_ge4j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_4j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_ge3j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_3j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_ge2j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_2j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_ge1j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_1j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // ge1btag MET<20 && MET+MTW<60 GeV
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_ge6j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_6j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_ge5j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_5j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_ge4j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_4j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_ge3j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_3j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_ge2j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot; 
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_2j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_ge1j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_1j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // ge1btag MET+MTW<60 GeV
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_ge6j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_6j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_ge5j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_5j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_ge4j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_4j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_ge3j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_3j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_ge2j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_2j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_ge1j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_1j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  */
  // ==================================================================
  //  =================================================================
  /*    
  // ge2btag no cut on MET and MTW
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_ge6j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_6j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_ge5j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_5j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_ge4j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_4j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_ge3j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_3j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_ge2j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_2j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_ge1j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_noMETMTW_1j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // ge2btag MET and MTW>30 GeV
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_ge6j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_6j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_ge5j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_5j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_ge4j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_4j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_ge3j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_3j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_ge2j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_2j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_ge1j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt30_1j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // ge2btag MET>20 && MET+MTW>60 GeV
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_ge6j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_6j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_ge5j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_5j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_ge4j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_4j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_ge3j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_3j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_ge2j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_2j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_ge1j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWgt2060_1j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // ge2btag MET<20 && MET+MTW<60 GeV
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_ge6j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_6j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_ge5j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_5j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_ge4j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_4j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_ge3j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_3j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_ge2j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot; 
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_2j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_ge1j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt2060_1j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // ge2btag MET+MTW<60 GeV
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_ge6j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_6j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_ge5j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_5j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_ge4j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_4j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_ge3j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_3j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_ge2j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_2j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_ge1j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Egamma", "_METMTWlt60_1j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  */
  // ==================================================================
  //  =================================================================

  // ============================================================
  // for muons
  //
  /*
  // pretag no cut on MET and MTW
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge6j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  return;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_6j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge5j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_5j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge4j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_4j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge3j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_3j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge2j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_2j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge1j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_1j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // pretag MET and MTW>30 GeV
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_ge6j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_6j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_ge5j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_5j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_ge4j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_4j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_ge3j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_3j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_ge2j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_2j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_ge1j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_1j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  
  // pretag MET>20 && MET+MTW>60 GeV
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_ge6j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_6j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_ge5j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_5j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_ge4j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_4j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_ge3j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_3j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_ge2j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_2j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_ge1j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_1j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // pretag MET<20 && MET+MTW<60 GeV
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_ge6j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_6j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_ge5j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_5j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_ge4j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_4j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_ge3j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_3j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_ge2j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot; 
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_2j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_ge1j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_1j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
   
   
  // pretag MET+MTW<60 GeV
  //     
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_ge6j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_6j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_ge5j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_5j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_ge4j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_4j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_ge3j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_3j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_ge2j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_2j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_ge1j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_1j_pretag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  */
  // ==================================================================
  //  =================================================================
  /*
  // alltag no cut on MET and MTW
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge6j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_6j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge5j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_5j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge4j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_4j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge3j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_3j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge2j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_2j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge1j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_1j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // alltag MET and MTW>30 GeV
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_ge6j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_6j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_ge5j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_5j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_ge4j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_4j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_ge3j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_3j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_ge2j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_2j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_ge1j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_1j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // alltag MET>20 && MET+MTW>60 GeV
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_ge6j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_6j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_ge5j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_5j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_ge4j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_4j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_ge3j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_3j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_ge2j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_2j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_ge1j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_1j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // alltag MET+MTW<60 GeV
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_ge6j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_6j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_ge5j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_5j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_ge4j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_4j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_ge3j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_3j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  */
  /*
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_ge2j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_2j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_ge1j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_1j_alltag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  */

  // ==================================================================
  //  =================================================================
  /*
  // 0btag no cut on MET and MTW
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge6j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_6j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge5j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_5j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge4j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_4j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge3j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_3j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge2j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_2j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge1j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_1j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  
  // 0btag MET and MTW>30 GeV
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_ge6j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_6j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_ge5j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_5j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_ge4j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_4j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_ge3j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_3j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_ge2j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_2j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_ge1j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_1j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // 0btag MET>20 && MET+MTW>60 GeV
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_ge6j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_6j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_ge5j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_5j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_ge4j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_4j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_ge3j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_3j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_ge2j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_2j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_ge1j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_1j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // 0 btag MET<20 && MET+MTW<60 GeV
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_ge6j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_6j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_ge5j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_5j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_ge4j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_4j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_ge3j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_3j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_ge2j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot; 
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_2j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_ge1j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_1j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // 0btag MET+MTW<60 GeV
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_ge6j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_6j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_ge5j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_5j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_ge4j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_4j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_ge3j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_3j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_ge2j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_2j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_ge1j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_1j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // ==================================================================
  //  =================================================================

  // ge1btag no cut on MET and MTW
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge6j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_6j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge5j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_5j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge4j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_4j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge3j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_3j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge2j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_2j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge1j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_1j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // ge1btag MET and MTW>30 GeV
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_ge6j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_6j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_ge5j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_5j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_ge4j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_4j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_ge3j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_3j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_ge2j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_2j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_ge1j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_1j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // ge1btag MET>20 && MET+MTW>60 GeV
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_ge6j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_6j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_ge5j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_5j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_ge4j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_4j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_ge3j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_3j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_ge2j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_2j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_ge1j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_1j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // ge1btag MET<20 && MET+MTW<60 GeV
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_ge6j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_6j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_ge5j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_5j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_ge4j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_4j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_ge3j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_3j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_ge2j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot; 
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_2j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_ge1j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_1j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // ge1btag MET+MTW<60 GeV
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_ge6j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_6j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_ge5j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_5j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_ge4j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_4j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_ge3j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_3j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_ge2j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_2j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_ge1j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_1j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // ==================================================================
  //  =================================================================

  // ge2btag no cut on MET and MTW
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge6j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_6j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge5j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_5j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge4j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_4j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge3j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_3j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge2j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_2j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge1j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_1j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // ge2btag MET and MTW>30 GeV
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_ge6j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_6j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_ge5j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_5j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_ge4j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_4j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_ge3j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_3j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_ge2j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_2j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_ge1j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt30_1j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // ge2btag MET>20 && MET+MTW>60 GeV
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_ge6j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_6j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_ge5j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_5j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_ge4j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_4j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_ge3j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_3j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_ge2j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_2j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_ge1j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWgt2060_1j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // ge2btag MET<20 && MET+MTW<60 GeV
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_ge6j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_6j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_ge5j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_5j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_ge4j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_4j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_ge3j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_3j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_ge2j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot; 
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_2j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_ge1j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt2060_1j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // ge2btag MET+MTW<60 GeV
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_ge6j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_6j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_ge5j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_5j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_ge4j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_4j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_ge3j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_3j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_ge2j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_2j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_ge1j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_METMTWlt60_1j_ge2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  // ==================================================================
  //  =================================================================

  // 1btag no cut on MET and MTW
  //   
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge6j_1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_6j_1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge5j_1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_5j_1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge4j_1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_4j_1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge3j_1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_3j_1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge2j_1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_2j_1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_ge1j_1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_1j_1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;

  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_2j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_2j_1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_2j_2btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_4j_0btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  plotControlSemiLeptonic *myplot = new plotControlSemiLeptonic(inputdatadir, inputmcdir, "_Muons", "_noMETMTW_4j_ge1btag", iso, destdir, false);
  myplot->execute();
  delete myplot;
  */
  return;
}

class plotControlSemiLeptonic{
public:
  TString m_name_dir_datainput;
  TString m_name_dir_mcinput;
  TString m_figdir;
  
  TString m_stream;
  TString m_level;
  TString m_prefix;
  TString m_option;
  TString m_suffix;
  TString m_iso;
    TString m_cuts;
  TString m_channel;
  
  bool m_log;
  
  int m_min;
  int m_max;
  int m_systmax;
  TPad *m_pad1;
  TPad *m_pad2;
  TGraph* m_graxis1;
  TGraph* m_graxis2;

  Float_t m_x[1000];
  Float_t m_y[1000]; 
  Float_t m_exl[1000];
  Float_t m_eyl[1000];
  Float_t m_exh[1000];
  Float_t m_eyh[1000];
  Float_t m_x2[1000];
  Float_t m_y2[1000]; 
  Float_t m_exl2[1000];
  Float_t m_eyl2[1000];
  Float_t m_exh2[1000];
  Float_t m_eyh2[1000];
  
  plotControlSemiLeptonic(TString dir_datainput, TString dir_mcinput, 
			  TString stream, TString level, 
			  TString iso, TString figdir, bool log)
  {

    m_name_dir_datainput = dir_datainput;
    m_name_dir_mcinput   = dir_mcinput;
    m_stream             = stream;
    m_level              = level;
    m_iso                = iso;
    m_figdir             = figdir;
    m_log                = log;
  }
  
  // ================================================
  execute() {
    
    m_min=0;
    m_max=1;

    // open files
    this->openFiles();
    
    // read histograms from files
    this->readHists();
    // add/stack histograms
    this->addHists();
    // plot histograms
    this->plotHists();
    
  }
  
  // =============================================
  void openFiles()
  {
    //
    // open all files
    //

    TString name;

    // fakes estimate from data
    name =  "user.derue.Data-periodDtoJ.physics_Main.DAOD_TOPQ1.p2452.FakeSemiLeptonic_estimate.2337-2.root";
    m_ffakesdata[0] = new TFile(m_name_dir_datainput+name);

    name =  "user.derue.Data-periodDtoJ.physics_Main.DAOD_TOPQ1.p2452.FakeSemiLeptonic_estimateCRreal.2337-2.root";
    m_ffakesdata[1] = new TFile(m_name_dir_datainput+name);
    name =  "user.derue.Data-periodDtoJ.physics_Main.DAOD_TOPQ1.p2452.FakeSemiLeptonic_estimateCRfake.2337-2.root";
    m_ffakesdata[2] = new TFile(m_name_dir_datainput+name);
    name =  "user.derue.Data-periodDtoJ.physics_Main.DAOD_TOPQ1.p2452.FakeSemiLeptonic_estimateMCup.2337-2.root";
    m_ffakesdata[3] = new TFile(m_name_dir_datainput+name);
    name =  "user.derue.Data-periodDtoJ.physics_Main.DAOD_TOPQ1.p2452.FakeSemiLeptonic_estimateMCdown.2337-2.root";
    m_ffakesdata[4] = new TFile(m_name_dir_datainput+name);
    name =  "user.derue.Data-periodDtoJ.physics_Main.DAOD_TOPQ1.p2452.FakeSemiLeptonic_estimateEffPar.2337-2.root";
    m_ffakesdata[5] = new TFile(m_name_dir_datainput+name);

  }

  // =========================================
  void readHists() 
  {
    for (int var=m_min; var<=m_max; var++) {
      m_HistogramNames[var] = GiveHistoName(var);
     //std::cout << " i = " << i << " " << GiveHistoName(i) << std::endl;
    }
    
    // loop on each histo
    for (int var=m_min ; var<=m_max; var++ ) {
      std::string hname = m_HistogramNames[var];
      std::cerr << "Reading histogram " << m_HistogramNames[var] << std::endl;
      
      // read fakes
      for (int i=0;i<=5;i++) {
	m_hfakesdata[i][var]  = GetHistogram(var, m_ffakesdata[i]);
	std::cout << " fakes = " << i << " " << m_hfakesdata[i][var] << " " << m_hfakesdata[i][var]->GetNbinsX() << std::endl;
	if (var==m_max) m_ffakesdata[i]->Close(); 
      }
    }
      
  }

  // =============================================
  void addHists()
  {
    //
    //  add/stack histograms
    //
    
    std::string name; 

    // loop on variables to plot
    for (int var=m_min; var<=m_max; var++ ) {
      
      /// sum
      // fakes estimate
      m_hfakesdata[0][var]->SetLineColor(1);
      m_hfakesdata[0][var]->SetFillColor(kYellow);
      // fakes estimate CRreal
      m_hfakesdata[1][var]->SetLineColor(2);
      // fakes estimate CRfake
      m_hfakesdata[2][var]->SetLineColor(3);
      // fakes estimate MCup
      m_hfakesdata[3][var]->SetLineColor(4);
      // fakes estimate MCdown
      m_hfakesdata[4][var]->SetLineColor(5);
      // fakes estimate EffPar
      m_hfakesdata[5][var]->SetLineColor(6);

      // ratios
      m_hfakesratio[1][var] = GetHistogram(var);
      m_hfakesratio[1][var]->SetLineColor(2);
      m_hfakesratio[1][var]->Divide(m_hfakesdata[1][var],m_hfakesdata[0][var]);
      //
      m_hfakesratio[2][var] = GetHistogram(var);
      m_hfakesratio[2][var]->SetLineColor(3);
      m_hfakesratio[2][var]->Divide(m_hfakesdata[2][var],m_hfakesdata[0][var]);
      //
      m_hfakesratio[3][var] = GetHistogram(var);
      m_hfakesratio[3][var]->SetLineColor(4);
      m_hfakesratio[3][var]->Divide(m_hfakesdata[3][var],m_hfakesdata[0][var]);
      //
      m_hfakesratio[4][var] = GetHistogram(var);
      m_hfakesratio[4][var]->SetLineColor(5);
      m_hfakesratio[4][var]->Divide(m_hfakesdata[4][var],m_hfakesdata[0][var]);
      //
      m_hfakesratio[5][var] = GetHistogram(var);
      m_hfakesratio[5][var]->SetLineColor(6);
      m_hfakesratio[5][var]->Divide(m_hfakesdata[5][var],m_hfakesdata[0][var]);
      
      for (int i=0;i<=5;i++) {
	m_hfakesdata[i][var]->SetLineWidth(2);
	if (i>0)m_hfakesratio[i][var]->SetLineWidth(2);
      }

      // print number of entries
      PrintEntries(var);
    } 
  }

  // =============================================
  void plotHists()
  {
    //
    // plot histograms, show data and MC superimposed
    //

    gROOT->Reset();
    gROOT->SetStyle("ATLAS");
    gROOT->ForceStyle();
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    gStyle->SetTitleXOffset(0.1);
    gStyle->SetTitleYOffset(2.);
    
    std::string canvname;
    
    // loop on variables to plot
    for (int var = m_min; var <= m_max; var++ ) {
      canvname = GiveCanvasName(var);
      //m_c[var] = new TCanvas(canvname.c_str(),canvname.c_str(),200,10,800,600);
      m_c[var] = new TCanvas(canvname.c_str(),canvname.c_str(),200,10,600,600);
      int n = m_hfakesdata[0][var]->GetNbinsX();

      // define and set pads 
      SetPad(var);
      m_pad1->cd();

     
      // plot axis
      plotAxisForAll(var,1,m_c[var],m_graxis1,m_hfakesdata[0][var]);

      // plot histograms
      plot(var,1,m_hfakesdata[0][var],GiveAxisName(var).c_str());

      // plot additional text
      plotText(var);
      // plot the TLegend
      plotLegend(var);
      
      TPave *mbox= new TPave(0.105,0.,0.155,0.2,0,"NDC");
      mbox->SetFillColor(0);
      mbox->SetFillStyle(1111);
      //mbox->Draw("");

      m_pad1->RedrawAxis();
            
      //
      // handle data/MC distribution
      //
      m_pad2->cd();
            
      // plot axis
      plotAxisForAll(var,2,m_c[var],m_graxis2,m_hfakesratio[1][var]);
      
      // plot histograms
      plot(var,2,m_hfakesratio[1][var],GiveAxisName(var).c_str());

      float myy[2], myx[2];
      myy[0] = 1.;
      myy[1] = 1.;
      myx[0] = -2000.; myx[1] = 2000.;
      TGraph *plot0 = new TGraph(2,myx,myy);
      plot0->SetLineColor(2);
      //gr->SetLineWidth(2);
      plot0->Draw("same");
            
      if (!m_log) myText(0.135,0.965,1,"0");
      else myText(0.134,0.965,1,"1"); 
      m_pad2->RedrawAxis();       

      m_pad1->cd();
      m_pad1->RedrawAxis();
      m_c[var]->RedrawAxis(); 
    
      TString filename = GiveOutputName(var);
      std::cout << " filename = " << filename << " " << m_log << std::endl;
      filename +="";
      m_c[var]->SaveAs(m_figdir+filename+"_onlyfakes.eps");
      m_c[var]->SaveAs(m_figdir+filename+"_onlyfakes.pdf");
      m_c[var]->SaveAs(m_figdir+filename+"_onlyfakes.png");
      
      //std::cout << " data = " << m_hsum_all[var]->GetBincontent(1) << std::endl;
      //delete m_hstack_all[var];
      //delete m_c[var];
    }    
  } 
  
  // ==================================================================
  void SetPad(int var)
  {
    Float_t x3[2];
    Float_t y3[2]; 
    x3[0] = m_hfakesdata[0][var]->GetBinCenter(1);
    x3[1] = m_hfakesdata[0][var]->GetBinCenter(m_hfakesdata[0][var]->GetNbinsX());
    y3[0] = 0.;
    y3[1] = 2.;
    
    float fSubPadSize = 0.33;
    m_pad1 = new TPad("pad1","pad1",0,1-(1-fSubPadSize)/(1-gStyle->GetPadBottomMargin()),1,1,0,0,0);
    m_pad1->SetTopMargin(0.06);
    m_pad1->SetFrameBorderMode(0);
    
    m_pad2 = new TPad("pad2","pad2",0,0,1,fSubPadSize,0,0,0);
    m_pad2->SetTopMargin(0.0);
    m_pad2->SetFrameBorderMode(0);
    m_pad2->SetBottomMargin(gStyle->GetPadBottomMargin()*m_pad1->GetAbsHNDC()/m_pad2->GetAbsHNDC());

    Float_t xaxis1[2];
    Float_t yaxis1[2]; 
    xaxis1[0] = 0.; xaxis1[1] = 1.;
    yaxis1[0] = 0.; yaxis1[1] = 1.;
    m_graxis1 = new TGraph(2,xaxis1,yaxis1);
    
    Float_t xaxis2[2];
    Float_t yaxis2[2]; 
    xaxis2[0] = 0.; xaxis2[1] = 1.;
    yaxis2[0] = 0.; yaxis2[1] = 1.;
    m_graxis2 = new TGraph(2,xaxis2,yaxis2);
    
    /*if (var==2 || var==3 || var==6 || var==7 || 
	var==17 || var==18 || var==19 ||
	var==20 || var==21 || var==22 ||
	var==26 || var==27 || var==28	||
	var==29 || var==30 || var==31 ||
	var==41 || var==422) {
      m_pad1->SetLogy();
      m_log = true;
    } else {
      m_log = false;
      }*/
    //m_pad1->SetLogy();
    //m_log = true;
    //m_log = false;
    m_pad1->Draw(); 
    m_pad2->Draw();     
  }

  // ==================================================================
  void PrintEntries(int var) 
  {
    //
    // print number of entries
    //
    
    std::cout << " print entries " << std::endl;
    PrintDataFakes(var);
  }  

  // ==================================================================
  void PrintDataFakes(int var) 
  {
    //
    // data and fakes
    //

    float errCRreal = std::fabs(m_hfakesdata[0][var]->GetSumOfWeights()-m_hfakesdata[1][var]->GetSumOfWeights());
    float errCRfake = std::fabs(m_hfakesdata[0][var]->GetSumOfWeights()-m_hfakesdata[2][var]->GetSumOfWeights());
    float errMCup = std::fabs(m_hfakesdata[0][var]->GetSumOfWeights()-m_hfakesdata[3][var]->GetSumOfWeights());
    float errMCdown = std::fabs(m_hfakesdata[0][var]->GetSumOfWeights()-m_hfakesdata[4][var]->GetSumOfWeights());
    float errMC = 0.;
    if (errMCup>errMCdown) errMC = errMCup;
    else errMC = errMCdown;
    float errEffPar = std::fabs(m_hfakesdata[0][var]->GetSumOfWeights()-m_hfakesdata[5][var]->GetSumOfWeights());
    float errsys = sqrt(errCRreal*errCRreal+errCRfake*errCRfake+errMC*errMC+
			errEffPar*errEffPar);
    
    if (m_hfakesdata[0][var]->GetSumOfWeights()<0.) 
      std::cout << " fakes data entries   = " << m_hfakesdata[0][var]->GetSumOfWeights() << std::endl;
    else 
      std::cout << " fakes data entries   = " << m_hfakesdata[0][var]->GetSumOfWeights() << " +/- " << sqrt(m_hfakesdata[0][var]->GetSumOfWeights()) << " +/- " << errsys << std::endl;
    std::cout << " fakes CRreal = " << m_hfakesdata[1][var]->GetSumOfWeights() << " err = "<< errCRreal << std::endl;
    std::cout << " fakes CRfake = " << m_hfakesdata[2][var]->GetSumOfWeights() << " err = "<< errCRfake << std::endl;
    std::cout << " fakes MCup = " << m_hfakesdata[3][var]->GetSumOfWeights() << " err = " << errMCup << std::endl;
    std::cout << " fakes MCdown = " << m_hfakesdata[4][var]->GetSumOfWeights() << " err = " << errMCdown << std::endl;
    std::cout << " fakes EffPar = " << m_hfakesdata[5][var]->GetSumOfWeights() << " err = " << errEffPar << std::endl;
    //std::cout << " fakes data entries = " << m_hfakesdata[var]->GetEntries() << std::endl;
    
  }

  // ==========================================================
  void InitArrays()
  {
    for (int i=0;i<1000;i++) {
      m_x[i]    = -999.;
      m_y[i]    = -999.; 
      m_exl[i]  = 0.;
      m_eyl[i]  = 0.;
      m_exh[i]  = 0.;
      m_eyh[i]  = 0.;
      m_x2[i]   = -999.;
      m_y2[i]   = -999.; 
      m_exl2[i] = 0.;
      m_eyl2[i] = 0.;
      m_exh2[i] = 0.;
      m_eyh2[i] = 0.;
    }
  }

  // ===================================================================
  void plotText(int var) {
    
    double xlabel = 0.2;
    double ylabel = 0.88;
    float tsize = 0.045;

    if (var==0) { xlabel = 0.2; }
    ATLASLabel(xlabel,ylabel,"Internal");
    myText(xlabel,ylabel-0.08,1,
	   "#sqrt{s}= 13 TeV, L=3.34 fb^{-1}",tsize);
    double xmin  = 0.55;
    double ymin  = 0.88;
    double xmin2  = 0.55;
    double ymin2  = 0.82;

    // pretag MET>30 GeV MTW>30 GeV
    if (m_level.Contains("noMETMTW")) {
      myText(xmin2,ymin2,1,"no cut on #slash{E}_{T} and m_{T}^{W}",tsize);
    } else if (m_level.Contains("METMTWgt30")) {
      myText(xmin2,ymin2,1,"#slash{E}_{T}>30 GeV, m_{T}^{W}>30 GeV",tsize);
    } else if (m_level.Contains("METMTWgt2060")) {
      myText(xmin2,ymin2,1,"#slash{E}_{T}>20 GeV, #slash{E}_{T}+m_{T}^{W}>60 GeV",tsize);
    } else if (m_level.Contains("METMTWlt2060")) {
      myText(xmin2,ymin2,1,"#slash{E}_{T}<20 GeV, #slash{E}_{T}+m_{T}^{W}<60 GeV",tsize);
    } else if (m_level.Contains("METMTWlt60")) {
      myText(xmin2,ymin2,1,"#slash{E}_{T}+m_{T}^{W}<60 GeV",tsize);
    }
    
    TString lep = "";
    if (m_stream.Contains("Egamma")) lep = "e";
    else lep = "#mu";
    
    TString levelbtag = "";
    TString leveljet = "";
    
    if (m_level.Contains("pretag")) levelbtag = "pretag";
    else if (m_level.Contains("alltag")) levelbtag = "#geq 0 btag";
    else if (m_level.Contains("0btag")) levelbtag = "0 btag";
    else if (m_level.Contains("ge2btag")) levelbtag = "#geq 2 btag";
    else if (m_level.Contains("2btag")) levelbtag = "2 btag";
    else if (m_level.Contains("ge1btag")) levelbtag = "#geq 1 btag";
    else if (m_level.Contains("1btag")) levelbtag = "1 btag";
    
    if (m_level.Contains("ge6j")) leveljet = "#geq 6j";
    else if (m_level.Contains("6j")) leveljet = "6j";
    else if (m_level.Contains("ge5j")) leveljet = "#geq 5j";
    else if (m_level.Contains("5j")) leveljet = "5j";
    else if (m_level.Contains("ge4j")) leveljet = "#geq 4j";
    else if (m_level.Contains("4j")) leveljet = "4j";
    else if (m_level.Contains("ge3j")) leveljet = "#geq 3j";
    else if (m_level.Contains("3j")) leveljet = "3j";
    else if (m_level.Contains("ge2j")) leveljet = "#geq 2j";
    else if (m_level.Contains("2j")) leveljet = "2j";
    else if (m_level.Contains("ge1j")) leveljet = "#geq 1j";
    else if (m_level.Contains("1j")) leveljet = "1j";
    
    myText(xmin,ymin,1,levelbtag+", "+lep+"+"+leveljet,tsize);
    
  }

   // ===================================================================
  void plotLegend(int var) 
  {
    //
    // plot the TLegend
    //

    double xmin = 0.65;
    double ymin = 0.45;
    double xmax = 0.95;
    double ymax = 0.78;
    
    if (var==2 && !m_log) { // dphi
      xmin = 0.2; ymin = 0.35; xmax = 0.55; ymax = 0.77;
    }
    if (var==20) { // b-weight
      xmin = 0.2; ymin = 0.35; xmax = 0.55; ymax = 0.75;
    }
    
    TLegend *leg = new TLegend(xmin,ymin,xmax,ymax,"");
    leg->SetFillColor(0);
    leg->SetMargin(0.15);
    leg->SetBorderSize(0);  // no border
    leg->SetFillStyle(0);  // no background
    //std::cout << " text size = " << gStyle->GetTextSize() << std::endl;
    //leg->SetTextSize(gStyle->GetTextSize());
    leg->SetTextSize(0.045);  
    leg->SetTextFont(42);  
    leg->AddEntry(m_hfakesdata[0][var],"Fakes standard","f");
    leg->AddEntry(m_hfakesdata[1][var],"Fakes CRreal","f");
    leg->AddEntry(m_hfakesdata[2][var],"Fakes CRfake","f");
    leg->AddEntry(m_hfakesdata[3][var],"Fakes MCup","f");
    leg->AddEntry(m_hfakesdata[4][var],"Fakes MCdown","f");
    leg->AddEntry(m_hfakesdata[5][var],"Fakes EffPar","f");
    leg->SetFillColor(0);      
    leg->SetBorderSize(0); 
    leg->Draw("");    
  }

  // ===================================================================
  bool isDataOver(TH1F* h, THStack *s)//return true if data is greater than MC
  {
    if (h->GetMaximum() > s->GetMaximum()) return true;
    else return false;
  }

  
  // ===================================================================
  float GetMaximum(TH1F* h, TH1F *s)//return true if data is greater than MC
  {
    if (h->GetMaximum() > s->GetMaximum()) return h->GetMaximum();
    else return s->GetMaximum();
  }

  // ===================================================================
  float GetMaximum(TH1F* h, THStack *s)//return true if data is greater than MC
  {
    if (h->GetMaximum() > s->GetMaximum()) return h->GetMaximum();
    else return s->GetMaximum();
  }

  // ================================================
  void plot(int var, int choice, TH1F * h, TString title, 
	    float min = -9999., float max = -9999.)
  {
    // for 1st pad
    if (choice==1) {
      h->GetXaxis()->SetTitle(title);
      
      if (var==0 || var==1) h->GetYaxis()->SetTitle("Events/(5 GeV)");
      else if (var==7) 
	h->GetYaxis()->SetTitle("Events/(10 GeV)");
      else if (var==10) 
	h->GetYaxis()->SetTitle("Events/(5 GeV)");
      else if (var==13 || var==14 || var==15 || var==16) 
	h->GetYaxis()->SetTitle("Events/(0.5 GeV)");
      else 
	h->GetYaxis()->SetTitle("Events");
      
      h->SetMarkerStyle(20);
      h->SetLineColor(1);
      h->SetLineWidth(2);
      if (m_log) h->SetMinimum(10.);
      h->SetMaximum(h->GetMaximum()*1.1);
      if (m_log) h->GetYaxis()->SetRangeUser(10.,this->GetMaximum(h,h)+0.1*this->GetMaximum(h,h));
      else h->GetYaxis()->SetRangeUser(0.,this->GetMaximum(h,h)+0.5*this->GetMaximum(h,h));
      if (min>-9000 && max >-9000)
	h->GetXaxis()->SetRangeUser(min,max);
      
      m_hfakesdata[0][var]->Draw("HISTsame");
      m_hfakesdata[1][var]->Draw("HISTsame");
      m_hfakesdata[2][var]->Draw("HISTsame");
      m_hfakesdata[3][var]->Draw("HISTsame");
      m_hfakesdata[4][var]->Draw("HISTsame");
      m_hfakesdata[5][var]->Draw("HISTsame");
      //m_hfakesdata[0][var]->Draw("Psame");
    } else { // ratio
     h->GetXaxis()->SetTitle(title);
     h->GetXaxis()->SetTitle("Syst / Std");

     if (min>-9000 && max >-9000) 
       h->GetXaxis()->SetRangeUser(min,max);

     //m_hfakesratio[1][var]->SetMaximum(20.);      
     m_hfakesratio[1][var]->Draw("HISTsame");
     /*for (int i=1;i<m_hfakesratio[1][var]->GetNbinsX();i++) {
      float x = m_hfakesratio[1][var]->GetBinCenter(i);
      float y = m_hfakesratio[1][var]->GetBinContent(i);
      std::cout << " i = " << i << " " << x << " " << y << std::endl;
      }*/

     m_hfakesratio[2][var]->Draw("HISTsame");
     m_hfakesratio[3][var]->Draw("HISTsame");
     m_hfakesratio[4][var]->Draw("HISTsame");
     m_hfakesratio[5][var]->Draw("HISTsame");
    }
  }

  
  // ================================================
  void plot(TGraph * gr, TString title, float min = -9999., float max = -9999.)
  {
    gr->SetMarkerStyle(20);
    gr->SetLineColor(1);
    gr->SetLineWidth(2);
    gr->Draw("P");
  }
  
  // ======================================================
  void plotAxisForAll(int var, int choice, TCanvas *fCanvas, 
		      TGraph* gr, TH1F *h1)
  {
    //
    // pot axis for all variables
    //

    //std::cout << " plotAxisForAll " << std::endl;
    TString title = GiveAxisName(var).c_str();
    TString YAxisTitle = "Events";
    float xmin = 0.;
    float xmax = 0.;
    float scale = 0.7;
    Float_t x[2];
    Float_t y[2]; 
    x[0] = h1->GetBinCenter(1);
    x[1] = h1->GetBinCenter(h1->GetNbinsX());
    fDummyHist = new TH1F("dummy","dummy",1,0,0);
    fDummyHist->SetBinContent(1,0);
    
    scale = 0.2;
    if (var == 0) { // Etmiss
      scale = 0.2; if (m_log) scale = 100.;
      YAxisTitle = "Events / 25 GeV";
      //std::cout << " level = " << m_level << std::endl;
      //if (m_level.Contains("noMETMTW")) { xmin = 0.; xmax = 140.;}
      if (m_level.Contains("noMETMTW")) { xmin = 0.; xmax = 60.;}
      else if (m_level.Contains("METMTWgt2060"))  { xmin = 30.; xmax = 140.;}
      else if (m_level.Contains("METMTWlt2060"))  { xmin = 0.; xmax = 60.;}
      else if (m_level.Contains("METMTWlt60"))  { xmin = 0.; xmax = 60.;}
      else if (m_level.Contains("METMTWgt30"))  { xmin = 40.; xmax = 140.;}
      else { xmin = 40.; xmax = 140.;}
    } else if (var==1) {  // MTW
      scale = 0.3; if (m_log) scale = 100.;
      YAxisTitle = "Events / 5 GeV";
      if (m_level.Contains("noMETMTW")) { xmin = 0.; xmax = 190.;}
      else if (m_level.Contains("METMTWgt2060"))  { xmin = 20.; xmax = 190.;}
      else if (m_level.Contains("METMTWlt2060"))  { xmin = 0.; xmax = 60.;}
      else if (m_level.Contains("METMTWlt60"))  { xmin = 0.; xmax = 60.;}
      else if (m_level.Contains("METMTWgt30"))  { xmin = 40.; xmax = 140.;}
      else { xmin = 40.; xmax = 140.;}
    } 
    else if (var == 4) { xmin = -2.7; xmax = 2.7; YAxisTitle = "Events / #pi/5";} // DPhi(lept,ETmiss)
    else if (var == 5) { xmin = 0.; xmax = 5.; YAxisTitle = "Events / 25 GeV";}// dR closest jet
    else if (var == 6) { xmin = 35.; xmax = 200.; YAxisTitle = "Events / 25 GeV";} // pt of the closest jet
    else if (var == 7) { xmin = -2.1; xmax = 2.1; YAxisTitle = "Events / 25 GeV";} // eta of the closest jet
    else if (var == 8) { xmin = -2.7; xmax = 2.7; YAxisTitle = "Events / 25 GeV";}  // phi of the closest jet
    else if (var == 9) { xmin = 0.; xmax = 5.; YAxisTitle = "Events / 25 GeV";}// dR of the leading jet
    else if (var == 10) { xmin = 35.; xmax = 200.; YAxisTitle = "Events / 25 GeV";} // pt of the leading jet
    else if (var == 11) { xmin = -2.1; xmax = 2.1; YAxisTitle = "Events / 25 GeV";} // eta of the leading jet
    else if (var == 12) { xmin = -2.7; xmax = 2.7; YAxisTitle = "Events / 25 GeV";}  // phi of the leading jet
    else if (var == 13) { xmin = 0.; xmax = 5.; YAxisTitle = "Events / 25 GeV";}// dR maxb jet
    else if (var == 14) { xmin = 35.; xmax = 200.; YAxisTitle = "Events / 25 GeV";} // pt of the maxb jet
    else if (var == 15) { xmin = -2.1; xmax = 2.1; YAxisTitle = "Events / 25 GeV";} // eta of the maxb jet
    else if (var == 16) { xmin = -2.7; xmax = 2.7; YAxisTitle = "Events / 25 GeV";}  // phi of the maxb jet
    else if (var == 17) { xmin = 0.; xmax = 1.; YAxisTitle = "Events / 25 GeV";}  // bWeight of the maxb jet
    else if (var == 18) { xmin = -1.; xmax = 1.; YAxisTitle = "Events / 25 GeV";} // charge of the lepton
    else if (var == 19) { xmin = 35.; xmax = 140.; YAxisTitle = "Events / 25 GeV";} // pt of the lepton
    else if (var == 20) { xmin = -2.; xmax = 2.; YAxisTitle = "Events / 25 GeV";}  // eta of the lepton
    else if (var == 21) { xmin = -2.7; xmax = 2.7; YAxisTitle = "Events / 25 GeV";} // phi of the lepton
    else {
      xmin = 0.; xmax = 10.;
      YAxisTitle = "Events / 25 GeV";
    }

    // for 1st pad
    if (choice==1) {
      if (m_log) {
	y[0] = 1.;
	y[1] = this->GetMaximum(h1,h1)+scale*this->GetMaximum(h1,h1);
      } else {
	y[0] = 0.;
	y[1] = this->GetMaximum(h1,h1)+scale*this->GetMaximum(h1,h1);
      }
    }
    // for 2nd pad
    if (choice==2) {
      //y[0] = 0.4;
      //y[1] = 1.599;
      y[0] = 0.001;
      y[1] = 1.999;
      //y[0] = 0.7;
      //y[1] = 1.299;
    }
    if (xmin>-9000 && xmax >-9000) {
      x[0] = xmin;
      x[1] = xmax;
    }

    std::cout << " xmin = " << xmin << " " << xmax 
	      << " " << x[0] << " " << x[1] 
	      << " " << y[1]
	      << std::endl;

    gr = new TGraph(2,x,y);
    gr->SetFillColor(19);
    gr->SetLineColor(0);
    gr->SetLineWidth(4);
    gr->SetMarkerColor(0);
    gr->SetMarkerStyle(20);
    
    gr->GetXaxis()->SetTitle(title);

    if (choice==1) {
      gr->GetYaxis()->SetTitle(YAxisTitle);
      gr->GetYaxis()->SetNoExponent(kFALSE);
      gr->GetXaxis()->SetTickLength(0.03);
      gr->GetYaxis()->SetTickLength(0.03);
      gr->GetYaxis()->SetLabelOffset(0.02);
      gr->GetYaxis()->SetTitleOffset(0.9*gr->GetYaxis()->GetTitleOffset()*fCanvas->GetYsizeReal()/fCanvas->GetXsizeReal());
      gr->GetXaxis()->SetTitleOffset(0.9*h1->GetXaxis()->GetTitleOffset()*m_pad1->GetAbsHNDC()/m_pad2->GetAbsHNDC());
    }
    if (choice==2) {
      gr->GetYaxis()->SetTitle("Syst / Std");
      //gr->GetYaxis()->SetTitle("Pred. / Data");
      gr->GetYaxis()->SetNdivisions(5);
      gr->GetYaxis()->CenterTitle();
      gr->GetXaxis()->SetTitleSize(0.1);
      gr->GetYaxis()->SetTitleSize(0.1);
      gr->GetXaxis()->SetLabelSize(0.1);
      gr->GetYaxis()->SetLabelSize(0.1);
      gr->GetXaxis()->SetTickLength(0.05);
      gr->GetYaxis()->SetTickLength(0.05);
      gr->GetYaxis()->SetLabelOffset(0.02);
      gr->GetYaxis()->SetTitleOffset(0.3*gr->GetYaxis()->GetTitleOffset()*fCanvas->GetYsizeReal()/fCanvas->GetXsizeReal());
      gr->GetXaxis()->SetTitleOffset(0.4*h1->GetXaxis()->GetTitleOffset()*m_pad1->GetAbsHNDC()/m_pad2->GetAbsHNDC());
    }


    gr->Draw("AP");
    //std::cout << " end of plotAxisForAll " << std::endl;
  }

private:
  // input files
  TFile *m_ffakesdata[6];
 
  // histograms
  TH1F *m_hfakesdata[6][40];
  TH1F *m_hfakesratio[6][40];
  TCanvas* m_c[40];
  
  std::string m_HistogramNames[40];

  // ===================================================================
  std::string GiveAxisName(int ivar)
  {
    if (ivar == 0) return std::string("E_{T}^{miss} [GeV]");
    if (ivar == 1) return std::string("m_{T}(l#nu) [GeV]");
    if (ivar == 2) return std::string("n_{jet}");
    if (ivar == 3) return std::string("n_{bjet}");

    if (ivar == 4) return std::string("#Delta#Phi_{lept-E_{T}^{miss}}");

    if (ivar == 5) return std::string("#DeltaR^{lept-closest Jet}");
    if (ivar == 6) return std::string("p_{T}^{closest Jet} [GeV]");
    if (ivar == 7) return std::string("#eta^{closest Jet}");
    if (ivar == 8) return std::string("#phi^{closest Jet}");

    if (ivar == 9)  return std::string("#DeltaR^{lept-leading Jet}");
    if (ivar == 10) return std::string("p_{T}^{leading Jet} [GeV]");
    if (ivar == 11) return std::string("#eta^{leading Jet}");
    if (ivar == 12) return std::string("#phi^{leading Jet}");

    if (ivar == 13) return std::string("#DeltaR^{lept-maxb Jet}");
    if (ivar == 14) return std::string("p_{T}^{maxb Jet} [GeV]");
    if (ivar == 15) return std::string("#eta^{maxb Jet}");
    if (ivar == 16) return std::string("#phi^{maxb Jet}");
    if (ivar == 17) return std::string("#bWeight^{maxb Jet}");

    if (ivar == 18) return std::string("q^{lept}");
    if (ivar == 19) return std::string("p_{T}^{lept} [GeV]");
    if (ivar == 20) return std::string("|#eta^{lept}|");
    if (ivar == 21) return std::string("#phi^{lept}");
    if (ivar == 22) return std::string("#sum E_{T}^{lept}(#DeltaR<0.2) [GeV]");
    if (ivar == 23) return std::string("#sum p_{T}^{lept}(#DeltaR<0.3) [GeV]");

  }

  // ===================================================================
  std::string GiveVarName(int ivar)
  {
    if (ivar == 0) return std::string("ETmiss");
    if (ivar == 1) return std::string("transvmass");
    if (ivar == 2) return std::string("njet");
    if (ivar == 3) return std::string("nbjet");

    if (ivar == 4) return std::string("deltaPhiLeptETmiss");

    if (ivar == 5) return std::string("dRClosestJet");
    if (ivar == 6) return std::string("pTClosestJet");
    if (ivar == 7) return std::string("etaClosestJet");
    if (ivar == 8) return std::string("phiClosestJet");

    if (ivar == 9)  return std::string("dRLeadingJet");
    if (ivar == 10) return std::string("pTLeadingJet");
    if (ivar == 11) return std::string("etaLeadingJet");
    if (ivar == 12) return std::string("phiLeadingJet");

    if (ivar == 13) return std::string("dRmaxbJet");
    if (ivar == 14) return std::string("pTmaxbJet");
    if (ivar == 15) return std::string("etamaxbJet");
    if (ivar == 16) return std::string("phimaxbJet");
    if (ivar == 17) return std::string("bWeightmaxbJet");

    if (ivar == 18) return std::string("chargelept");
    if (ivar == 19) return std::string("ptlept");
    if (ivar == 20) return std::string("etalept");
    if (ivar == 21) return std::string("philept");
    if (ivar == 22) return std::string("ETCone20lept");
    if (ivar == 23) return std::string("pTCone30lept");

  }
    
  // ===================================================================
  std::string GiveHistoName(int ivar)
  {
    std::string temp = "hSemiLeptonic";
    temp += GiveVarName(ivar);
    if (m_stream=="_Egamma") temp += "_EJet";
    if (m_stream=="_Muons") temp += "_MuJet";
    temp += m_level;
    return temp;
  }
    
  // ===================================================================
  std::string GiveCanvasName(int ivar)
  {
    std::string temp = "c";
    temp += GiveVarName(ivar);
    temp += m_level;
    temp += m_iso;
    //if (m_log) temp += "log";
    return temp;
  }
  
  // ===================================================================
  std::string GiveOutputName(int ivar)
  {
    std::string temp;
    temp = GiveVarName(ivar);
    temp += m_stream;
    temp += m_level;
    temp += m_iso;
    //if (m_log) temp += "log";
    return temp;
  }

  // ===================================================================
  void Style()
  {
    gROOT->Reset();
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
  }
  
  // =========================================================
  TH1F* GetHistogram(int var, TFile * f) 
  {
    TH1F * htemp;
    std::string namehisto =  m_HistogramNames[var];
    htemp = (TH1F*) f->GetDirectory("HistosSemiLeptonic")->Get(namehisto.c_str());
    std::cout << " htemp = " << htemp << " " << namehisto << std::endl;
    htemp->SetDirectory(0); // "detach" the histogram from the file
    ReBinHisto(var, htemp);

    float x = 0.;
    float y = 0.;
    int imax = 9999;
    float sum = 0.;
    float width = 1.;
    for (int i=1;i<htemp->GetNbinsX();i++) {
      x = htemp->GetBinCenter(i);
      y = htemp->GetBinContent(i);
      width = htemp->GetBinWidth(i);
      width = 1.;
      //std::cout << " i = " << i << " " << x << " " << y << " " << sum << " " << imax << std::endl;
      if (var==0 && x>200. && x<205.) imax = i; // for ETmiss
      //if (var==1 && x>145. && x<150.) imax = i; // for MTW
      if (i>=imax) sum+=y;
      // divide the number of events in this bin by the width of the bin
      htemp->SetBinContent(i,y/width);
    }
    //std::cout << " imax = " << imax << " " << sum << std::endl;
    // set the last "visible" (on plot) bin to overflow
    htemp->SetBinContent(imax,sum/width);

    return htemp;
  }

  // =============================================================
  TH1F* GetHistogram(int var)
  {
    TH1F * htemp;
    std::string namehisto = m_HistogramNames[var];
    
    double xetabins[21];
    xetabins[0]  = -2.47;
    xetabins[1]  = -2.37;
    xetabins[2]  = -2.01;
    xetabins[3]  = -1.81;
    xetabins[4]  = -1.52;
    xetabins[5]  = -1.37;
    xetabins[6]  = -1.15;
    xetabins[7]  = -0.80;
    xetabins[8]  = -0.60;
    xetabins[9]  = -0.10;
    xetabins[10] = 0.;
    xetabins[11] = 0.10;
    xetabins[12] = 0.60;
    xetabins[13] = 0.80;
    xetabins[14] = 1.15;
    xetabins[15] = 1.37;
    xetabins[16] = 1.52;
    xetabins[17] = 1.81;
    xetabins[18] = 2.01;
    xetabins[19] = 2.37;
    xetabins[20] = 2.47;

    if (var==0) // Etmiss
      htemp = new TH1F(namehisto.c_str(),namehisto.c_str(),500,0.,500.);
    if (var==1) // mtW
      htemp = new TH1F(namehisto.c_str(),namehisto.c_str(),500,0.,500.);
    if (var==2) // njet
      htemp = new TH1F(namehisto.c_str(),namehisto.c_str(),10,0.,10.);
    if (var==3) // nbjet
      htemp = new TH1F(namehisto.c_str(),namehisto.c_str(),10,0.,10.);

    if (var==4) // DPhi(lept-ETmiss)
      htemp = new TH1F(namehisto.c_str(),namehisto.c_str(),100,-3.2,3.2);

    if (var==5) // dR closest jet
      htemp = new TH1F(namehisto.c_str(),namehisto.c_str(),100,0.,10.);
    if (var==6) // pt closest jet
      htemp = new TH1F(namehisto.c_str(),namehisto.c_str(),300,0,300.);
    if (var==7) // eta closest jet
      htemp = new TH1F(namehisto.c_str(),namehisto.c_str(),50,-2.5,2.5);
    if (var==8) // phi closest jet
      htemp = new TH1F(namehisto.c_str(),namehisto.c_str(),100,-3.2,3.2);

    if (var==9) // dR leading jet
      htemp = new TH1F(namehisto.c_str(),namehisto.c_str(),100,0.,10.);
    if (var==10) // pt leading jet
      htemp = new TH1F(namehisto.c_str(),namehisto.c_str(),300,0,300.);
    if (var==11) // eta leading jet
      htemp = new TH1F(namehisto.c_str(),namehisto.c_str(),50,-2.5,2.5);
    if (var==12) // phi leading jet
      htemp = new TH1F(namehisto.c_str(),namehisto.c_str(),100,-3.2,3.2);

    if (var==13) // dR maxb jet
      htemp = new TH1F(namehisto.c_str(),namehisto.c_str(),100,0.,10.);
    if (var==14) // pt maxb jet
      htemp = new TH1F(namehisto.c_str(),namehisto.c_str(),300,0,300.);
    if (var==15) // eta maxb jet
      htemp = new TH1F(namehisto.c_str(),namehisto.c_str(),50,-2.5,2.5);
    if (var==16) // phi maxb jet
      htemp = new TH1F(namehisto.c_str(),namehisto.c_str(),100,-3.2,3.2);
    if (var==17) // bWeight maxb jet
      htemp = new TH1F(namehisto.c_str(),namehisto.c_str(),100,0.,1.);

    if (var==18) // charge lept
      htemp = new TH1F(namehisto.c_str(),namehisto.c_str(),3,-1.,1.);
    if (var==19) // pt lept
      htemp = new TH1F(namehisto.c_str(),namehisto.c_str(),200,0.,200.);
    if (var==20) // eta lept
      htemp = new TH1F(namehisto.c_str(),namehisto.c_str(),50,-2.5,2.5);
    if (var==21) // phi lept
      htemp = new TH1F(namehisto.c_str(),namehisto.c_str(),100,-3.2,3.2);
    if (var==22) // ETCone20
      htemp = new TH1F(namehisto.c_str(),namehisto.c_str(),70,-5.,30.);    
    if (var==23) // pTCone30
      htemp = new TH1F(namehisto.c_str(),namehisto.c_str(),70,-5.,30.);    

    ReBinHisto(var, htemp);

    return htemp;
  }
 
  // =========================================================  
  void ReBinHisto(int var, TH1F* htemp)
  {
    if (var==0) htemp->Rebin(5); // ET miss
    if (var==1) htemp->Rebin(5); // mtW

    if (var==4) htemp->Rebin(5); // Dphi

    if (var==5) htemp->Rebin(4); // dR closest jet
    if (var==6) htemp->Rebin(10);// pt closest jet
    if (var==7) htemp->Rebin(2); // eta closest jet
    if (var==8) htemp->Rebin(4); // phi closest jet

    if (var==9)  htemp->Rebin(4); // dR leading jet
    if (var==10) htemp->Rebin(10);// pt leading jet
    if (var==11) htemp->Rebin(2); // eta leading jet
    if (var==12) htemp->Rebin(4); // phi leading jet

    if (var==13) htemp->Rebin(4); // dR maxb jet
    if (var==14) htemp->Rebin(10);// pt maxb jet
    if (var==15) htemp->Rebin(2); // eta maxb jet
    if (var==16) htemp->Rebin(4); // phi maxb jet
    if (var==17) htemp->Rebin(4); // bWeight maxb jet

    if (var==18) htemp->Rebin(5); // pT(lept)
    if (var==19) htemp->Rebin(4); // phi lept
    //if (var==13) htemp->Rebin(2);// ETCone20
    //if (var==14) htemp->Rebin(2);// pTCone30
    //if (var==15) htemp->Rebin(2);// pTCone40
  }
  
};
