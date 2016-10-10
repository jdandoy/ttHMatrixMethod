#ifndef HistoManagerSemiLeptonic_h
#define HistoManagerSemiLeptonic_h
//////////////////////////////////////////////////////////////////////
// 
// Author   : Atlas LPNHE Paris
// Creation : 01/10/2015
// Purpose  : base class to manage efficiency histograms for lepton+jets
// Updated  :
//////////////////////////////////////////////////////////////////////

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TObjArray.h>

#include <TH1F.h>
#include <TH2F.h>
#include <iostream>
#include <fstream>

class HistoManagerSemiLeptonic
{
 public:

  // constructor
  HistoManagerSemiLeptonic(TObjArray *histosObj);

  // destructor
  virtual ~HistoManagerSemiLeptonic();

  void DefineHistos();

  TDirectory *dirSemiLeptonic;

  /// histograms 
  // [2] : type of the lept [ejet=0,mujet=1]
  // [5] : type of MET,MTW cut
  // [100] : selection cuts - mostly on njet and nbjet
  // ET miss
  TH1F *hETmiss[2][5][100];
  // HT sum
  TH1F *hHTsum[2][5][100];
  // mTW sum
  TH1F *hmTW[2][5][100];
  // number of good jets
  TH1F *hnjet[2][5][100];
  TH1F *hnbjet[2][5][100];
  // Closest jet
  TH1F *hdRClosestJet[2][5][100];
  TH1F *hbWeightClosestJet[2][5][100];
  TH1F *hpTClosestJet[2][5][100];
  TH1F *hetaClosestJet[2][5][100];
  TH1F *hphiClosestJet[2][5][100];
  // max bWeight 
  TH1F *hdRmaxbJet[2][5][100];
  TH1F *hpTmaxbJet[2][5][100];
  TH1F *hetamaxbJet[2][5][100];
  TH1F *hphimaxbJet[2][5][100];
  TH1F *hbWeightmaxbJet[2][5][100];
  // leading jet
  TH1F *hdRLeadingJet[2][5][100];
  TH1F *hpTLeadingJet[2][5][100];
  TH1F *hetaLeadingJet[2][5][100];
  TH1F *hphiLeadingJet[2][5][100];
  TH1F *hbWeightLeadingJet[2][5][100];
  // delta Phi (lept-ETmiss)
  TH1F *hdeltaPhiLeptETmiss[2][5][100];
  // for electron
  // charge of the lepton
  TH1F *hchargelept[2][5][100];
  // pt of the lepton
  TH1F *hpTlept[2][5][100];
  // eta of the lepton
  TH1F *hetalept[2][5][100];
  // phi of the lepton
  TH1F *hphilept[2][5][100];
  // ETCone20
  TH1F *hETCone20lept[2][5][100];
  // pTCone30
  TH1F *hpTCone30lept[2][5][100];

 private:

  TObjArray *m_histosObj;
  TString m_name;
  TString m_suffix;
  TFile *sFile;

  // define the class for the cint dictionary
  ClassDef(HistoManagerSemiLeptonic,1)
};

#endif // HistoManagerSemiLeptonic_h
