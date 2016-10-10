#ifndef HistoManagerEffiRealMuonTP_h
#define HistoManagerEffiRealMuonTP_h
//////////////////////////////////////////////////////////////////////
// 
// Author   : Atlas LPNHE Paris
// Creation : 01/10/2015
// Purpose  : base class to manage efficiency histograms for T&P muons
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

class HistoManagerEffiRealMuonTP
{
 public:

  // constructor
  HistoManagerEffiRealMuonTP(TObjArray *histosObj);

  // destructor
  virtual ~HistoManagerEffiRealMuonTP();

  void DefineHistos();
  void DefineHistos_vsPt();
  void DefineHistos_vsEta();
  void DefineHistos_vsdRClosestJet();
  void DefineHistos_vsPtLeadingJet();
  void DefineHistos_vsDPhi();
  void DefineHistos_vsMET();
  void DefineHistos_vsMTW();
  void DefineHistos_vsd0sig();
  void DefineHistos_NVert();
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
  TString BinVert(int);
  TString BinNJet(int injet);
  TString BinNbJet(int inbjet);
  
 private:

  TObjArray *m_histosObj;
  int m_binid;

  int m_binpt;
  int m_bineta;
  int m_bindr;
  int m_binptleadingjet;
  int m_bindphi;
  int m_binmet;
  int m_binmtw;
  int m_bind0sig;
  int m_binnvert;
  int m_binnjet;
  int m_binnbjet;

  int m_nbin_mass; 
  double m_mmin_mass;
  double m_mmax_mass;

  TString m_mytypeid;

  TString m_nameOS;
  TString m_nameSS;

  TString m_name;
  TString m_myname;
  
  TString m_typePt;
  TString m_typeEta;
  TString m_typedRClosestJet;
  TString m_typePtLeadingJet;
  TString m_typeDPhi;
  TString m_typeMET;
  TString m_typeMTW;
  TString m_typed0sig;
  TString m_typeNJet;
  TString m_typeNbJet;

  // number of vertex
  TH1F *hmassZNVert_OS[10][20];
  TH1F *hmassZNVert_SS[10][20];

  // ==============================================
  // all bins
  // [10];
  // invariant mass 
  TH1F *hmassZ_OS[10];
  TH1F *hmassZ_SS[10];

  // ==============================================
  // vs Pt
  // [10][20];
  // 10 : PID type
  // 20 : Pt bins
  // invariant mass 
  TH1F *hmassZ_vsPt_OS[10][20];
  TH1F *hmassZ_vsPt_SS[10][20];

  // ==============================================
  // vs Eta
  // [10][20];
  // 10 : PID type
  // 20 : Eta bins
  // invariant mass 
  TH1F *hmassZ_vsEta_OS[10][20];
  TH1F *hmassZ_vsEta_SS[10][20];

  // ==============================================
  // vs dRClosestJet
  // [10][20];
  // 10 : PID type
  // 20 : dRClosestJet bins
  // invariant mass 
  TH1F *hmassZ_vsdRClosestJet_OS[10][20];
  TH1F *hmassZ_vsdRClosestJet_SS[10][20];

  // ==============================================
  // vs PtLeadingJet
  // [10][20];
  // 10 : PID type
  // 20 : PtLeadingJet bins
  // invariant mass 
  TH1F *hmassZ_vsPtLeadingJet_OS[10][20];
  TH1F *hmassZ_vsPtLeadingJet_SS[10][20];

  // ==============================================
  // vs DPhi(ETmiss-lepton)
  // [10][20];
  // 10 : PID type
  // 20 : DPhi bins
  // invariant mass 
  TH1F *hmassZ_vsDPhi_OS[10][20];
  TH1F *hmassZ_vsDPhi_SS[10][20];

  // ==============================================
  // vs MET
  // [10][20];
  // 10 : PID type
  // 20 : MET bins
  // invariant mass 
  TH1F *hmassZ_vsMET_OS[10][20];
  TH1F *hmassZ_vsMET_SS[10][20];

  // ==============================================
  // vs MTW
  // [10][20];
  // 10 : PID type
  // 20 : MTW bins
  // invariant mass 
  TH1F *hmassZ_vsMTW_OS[10][20];
  TH1F *hmassZ_vsMTW_SS[10][20];

  // ==============================================
  // vs d0sig
  // [10][20];
  // 10 : PID type
  // 20 : d0sig bins
  // invariant mass 
  TH1F *hmassZ_vsd0sig_OS[10][20];
  TH1F *hmassZ_vsd0sig_SS[10][20];

  // ==============================================
  // vs NJet
  // [10][8];
  // 10 : PID type
  // 10 : NJet bins
  // invariant mass 
  TH1F *hmassZ_vsNJet_OS[10][10];
  TH1F *hmassZ_vsNJet_SS[10][10];

  // ==============================================
  // vs NbJet
  // [10][8];
  // 10 : PID type
  // 10 : NbJet bins
  // invariant mass 
  TH1F *hmassZ_vsNbJet_OS[10][10];
  TH1F *hmassZ_vsNbJet_SS[10][10];

  // define the class for the cint dictionary
  ClassDef(HistoManagerEffiRealMuonTP,1)
};

#endif // HistoManagerEffiRealMuonTP_h
