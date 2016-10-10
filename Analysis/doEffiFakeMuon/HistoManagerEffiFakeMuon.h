#ifndef HistoManagerEffiFakeMuon_h
#define HistoManagerEffiFakeMuon_h
//////////////////////////////////////////////////////////////////////
// 
// Author   : Atlas LPNHE Paris
// Creation : 01/10/2015
// Purpose  : base class to manage efficiency histograms for fake muons
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

class HistoManagerEffiFakeMuon
{
 public:

  // constructor
  HistoManagerEffiFakeMuon(TObjArray *histosObj);

  // destructor
  virtual ~HistoManagerEffiFakeMuon();

  void DefineHistos();
  void DefineHistos_vsPt();
  void DefineHistos_vsEta();
  void DefineHistos_vsdRClosestJet();
  void DefineHistos_vsPtLeadingJet();
  void DefineHistos_vsDPhi();
  void DefineHistos_vsMET();
  void DefineHistos_vsMTW();
  void DefineHistos_vsd0sig();
  void DefineHistos_vsNJet();
  void DefineHistos_vsNbJet();

  TString BinPt(int ipt);
  TString BinEta(int ieta);
  TString BindRClosestJet(int idr);
  TString BinPtLeadingJet(int ipt);
  TString BinDPhi(int idphi);
  TString BinMET(int index);
  TString BinMTW(int index);
  TString Bind0sig(int index);
  TString BinNbJet(int inbjet);
  TString BinNJet(int ijet);
  TString BinNJet2(int inbjet);

  int m_binid;
  int m_binjet;

  int m_binpt;
  int m_bineta;
  int m_bindr;
  int m_binptleadingjet;
  int m_bindphi;
  int m_binmet;
  int m_binmtw;
  int m_bind0sig;
  int m_binnjet;
  int m_binnbjet;

  TDirectory *dirEffiFakeMuon;

  // ==============================================
  // vs Njet
  // [2][6];
  // 2 : PID type
  // 6 : NJet bins
  TH1F *hETmiss[2][6];
  TH1F *hMTW[2][6];
  TH1F *hd0sig[2][6];
  TH1F *hd0sigPV[2][6];
  TH1F *hETmissOverSqrtHT[2][6];

 // ==============================================
  // vs Et
  // [2][5][20];
  // 2 : PID type
  // 5 : NJet bins
  // 20 : Et bins
  TH1F *hETmiss_vsPt[2][6][20];
  TH1F *hETmissOverSqrtHT_vsPt[2][6][20];

  // ==============================================
  // vs Eta
  // [2][5][20];
  // 2 : PID type
  // 5 : NJet bins
  // 20 : Eta bins
  TH1F *hETmiss_vsEta[2][6][20];
  TH1F *hETmissOverSqrtHT_vsEta[2][6][20];

  // ==============================================
  // vs dRClosestJet
  // [2][5][20];
  // 2 : PID type
  // 5 : NJet bins
  // 20 : dRClosestJet bins
  TH1F *hETmiss_vsdRClosestJet[2][6][20];
  TH1F *hETmissOverSqrtHT_vsdRClosestJet[2][6][20];

  // ==============================================
  // vs PtLeadingJet
  // [2][5][20];
  // 2 : PID type
  // 5 : NJet bins
  // 20 : PLeadingJet bins
  TH1F *hETmiss_vsPtLeadingJet[2][6][20];
  TH1F *hETmissOverSqrtHT_vsPtLeadingJet[2][6][20];

  // ==============================================
  // vs DPhi(ETmiss-lepton)
  // [2][5][20];
  //  2 : PID type
  // 5 : NJet bins
  // 20 : DPhi bins
  TH1F *hETmiss_vsDPhi[2][6][20];
  TH1F *hETmissOverSqrtHT_vsDPhi[2][6][20];

  // ==============================================
  // vs MET
  // [2][5][20];
  //  2 : PID type
  //  5 : Njet bins
  // 20 : MET bins
  TH1F *hETmiss_vsMET[2][6][20];
  TH1F *hETmissOverSqrtHT_vsMET[2][6][20];

  // ==============================================
  // vs MTW
  // [2][5][20];
  //  2 : PID type
  //  5 : Njet bins
  // 20 : MTW bins
  TH1F *hETmiss_vsMTW[2][6][20];
  TH1F *hETmissOverSqrtHT_vsMTW[2][6][20];

  // ==============================================
  // vs Njet
  // [2][5][4];
  // 2 : PID type
  // 5 : NJet bins
  TH1F *hETmiss_vsNJet[2][6][10];
  TH1F *hETmissOverSqrtHT_vsNJet[2][6][10];

  // ==============================================
  // vs Nbjet
  // [2][5][4];
  // 2 : PID type
  // 5 : NJet bins
  TH1F *hETmiss_vsNbJet[2][6][4];
  TH1F *hETmissOverSqrtHT_vsNbJet[2][6][4];

  // ==============================================
  // vs d0sig
  // [2][6][20];
  //  2 : PID type
  //  6 : Njet bins
  // 20 : d0sig bins
  TH1F *hETmiss_vsd0sig[2][6][20];
  TH1F *hETmissOverSqrtHT_vsd0sig[2][6][20];


 private:

  TObjArray *m_histosObj;
  TString m_baseName;
  TString m_name;
  TString m_titlefile;
  TFile *sFile;
  int m_etabin;

  // define the class for the cint dictionary
  ClassDef(HistoManagerEffiFakeMuon,1)
};

#endif // HistoManagerEffiFakeMuon_h
