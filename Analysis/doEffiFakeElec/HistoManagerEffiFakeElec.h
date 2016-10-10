#ifndef HistoManagerEffiFakeElec_h
#define HistoManagerEffiFakeElec_h
//////////////////////////////////////////////////////////////////////
// 
// Author   : Atlas LPNHE Paris
// Creation : 01/10/2015
// Purpose  : base class to manage efficiency histograms for fake electrons
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

class HistoManagerEffiFakeElec
{
 public:

  // constructor
  HistoManagerEffiFakeElec(TObjArray *histosObj);

  // destructor
  virtual ~HistoManagerEffiFakeElec();

  void DefineHistos();
  void DefineHistos_vsEt();
  void DefineHistos_vsEta();
  void DefineHistos_vsdRClosestJet();
  void DefineHistos_vsPtLeadingJet();
  void DefineHistos_vsDPhi();
  void DefineHistos_vsMET();
  void DefineHistos_vsMTW();
  void DefineHistos_vsNJet();
  void DefineHistos_vsNbJet();

  TString BinEt(int iet);
  TString BinEta(int ieta);
  TString BindRClosestJet(int idr);
  TString BinPtLeadingJet(int ipt);
  TString BinDPhi(int idphi);
  TString BinMET(int index);
  TString BinMTW(int index);
  TString BinNbJet(int inbjet);
  TString BinNJet2(int inbjet);

  TString BinNJet(int ijet);

  int m_binid;
  int m_binjet;

  int m_binet;
  int m_bineta;
  int m_bindr;
  int m_binptleadingjet;
  int m_bindphi;
  int m_binmet;
  int m_binmtw;
  int m_binnjet;
  int m_binnbjet;

  TDirectory *dirEffiFakeElec;

  // ==============================================
  // vs Njet
  // [2][5]; 
  // 2 : PID type
  // 5 : NJet bins -> 7
  TH1F *hETmiss[2][12];
  TH1F *hMTW[2][12];
  TH1F *hETmissOverSqrtHT[2][12];

  // ==============================================
  // vs Et
  // [2][5][20];
  // 2 : PID type
  // 5 : NJet bins
  // 20 : Et bins
  TH1F *hETmiss_vsEt[2][12][20];
  TH1F *hETmissOverSqrtHT_vsEt[2][12][20];

  // ==============================================
  // vs Eta
  // [2][5][20];
  // 2 : PID type
  // 5 : NJet bins
  // 20 : Eta bins
  TH1F *hETmiss_vsEta[2][12][20];
  TH1F *hETmissOverSqrtHT_vsEta[2][12][20];

  // ==============================================
  // vs dRClosestJet
  // [2][5][20];
  // 2 : PID type
  // 5 : NJet bins
  // 20 : dRClosestJet bins
  TH1F *hETmiss_vsdRClosestJet[2][12][20];
  TH1F *hETmissOverSqrtHT_vsdRClosestJet[2][12][20];

  // ==============================================
  // vs PtLeadingJet
  // [2][5][20];
  // 2 : PID type
  // 5 : NJet bins
  // 20 : PLeadingJet bins
  TH1F *hETmiss_vsPtLeadingJet[2][12][20];
  TH1F *hETmissOverSqrtHT_vsPtLeadingJet[2][12][20];

  // ==============================================
  // vs DPhi(ETmiss-lepton)
  // [2][5][20];
  //  2 : PID type
  // 5 : NJet bins
  // 20 : DPhi bins
  TH1F *hETmiss_vsDPhi[2][12][20];
  TH1F *hETmissOverSqrtHT_vsDPhi[2][12][20];

  // ==============================================
  // vs MET
  // [2][5][20];
  //  2 : PID type
  //  5 : Njet bins
  // 20 : MET bins
  TH1F *hETmiss_vsMET[2][12][20];
  TH1F *hETmissOverSqrtHT_vsMET[2][12][20];

  // ==============================================
  // vs MTW
  // [2][5][20];
  //  2 : PID type
  //  5 : Njet bins
  // 20 : MTW bins
  TH1F *hETmiss_vsMTW[2][12][20];
  TH1F *hETmissOverSqrtHT_vsMTW[2][12][20];

  // ==============================================
  // vs Njet
  // [2][5][4];
  // 2 : PID type
  // 5 : NJet bins
  TH1F *hETmiss_vsNJet[2][12][10];
  TH1F *hETmissOverSqrtHT_vsNJet[2][12][10];

  // ==============================================
  // vs Nbjet
  // [2][5][4];
  // 2 : PID type
  // 5 : NJet bins
  TH1F *hETmiss_vsNbJet[2][12][6];
  TH1F *hMTW_vsNbJet[2][12][6];
  TH1F *hETmissOverSqrtHT_vsNbJet[2][12][6];

 private:

  TObjArray *m_histosObj;
  TString m_baseName;
  TString m_name;
  TString m_titlefile;
  TFile *sFile;
  int m_etabin;

  // define the class for the cint dictionary
  ClassDef(HistoManagerEffiFakeElec,1)
};

#endif // HistoManagerEffiFakeElec_h
