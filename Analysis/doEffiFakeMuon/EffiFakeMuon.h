#ifndef EffiFakeMuon_h
#define EffiFakeMuon_h
//////////////////////////////////////////////////////////////////////
// 
// Author   : Atlas LPNHE Paris
// Creation : 01/10/2015
// Purpose  : base class to fill histograms for efficiencies of fake muons
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
#include "../Utils/MCDataSetUtils.h"
#include "../Utils/Utils.h"

class MyEffiFakeMuon;
class HistoManagerEffiFakeMuon;
using namespace TMath;

class EffiFakeMuon 
{
 public:
  // constructor
  EffiFakeMuon(MyEffiFakeMuon *myanalyse=0, TObjArray *histosObj=0);
  // destructor
  virtual ~EffiFakeMuon();
  // execute method
  bool execute();
  
  // histogram manager
  HistoManagerEffiFakeMuon *hmanag;
  
  void SetPretag(bool Pretag) {m_Pretag=Pretag;}
  void SetBtag(bool Btag) {m_Btag=Btag;}
  void SetNoBtag(bool NoBtag) {m_NoBtag=NoBtag;}
  
  void SetTrigger(TString Trigger) {m_trigger=Trigger;}
  void SetIso(TString Iso) {m_iso=Iso;}
  void SetCR(TString typeCR) {m_typeCR = typeCR;}
  
  void SetRunNumber(int RunNumber){m_RunNumber=RunNumber;}
  int GetRunNumber(){return m_RunNumber;}
  float XSectWeight(){return m_XSectweight;}
  void GiveMCWeight();
  
 private:

  MyEffiFakeMuon *myclass;
  Utils *myutils;
  MCDataSetUtils *myMCDataSetutils;

  bool isLoose();
  bool isTight();
  
  void FillHistos(float weight);
  void LookForLeadingandClosestJet();
  int CalcNJet();
  int CalcNbJet();
  double CalcHT();
  bool isTruthMatched();
  
  int WhichIndexPt(float Pt);
  int WhichIndexEta(float eta);
  int WhichIndexdRClosestJet(float dr);
  int WhichIndexPtLeadingJet(float var);
  int WhichIndexDPhi(float dphi);
  int WhichIndexMET(float met);
  int WhichIndexMTW(float mtw);
  int WhichIndexd0sig(float d0sig);
  int WhichIndexNJet(int nbjet);
  int WhichIndexNbJet(int nbjet);

  // weight 
  float m_weight;
  float m_weightbtag;
  
  float m_XSectweight;

  bool m_Pretag;//not to use btagging information
  bool m_Btag;//to filter btagged events
  bool m_NoBtag;//to veto btagged events
  
  TString m_typeCR;
  TString m_trigger;
  TString m_iso;
  
  int m_channel;
  int m_EventNumber;
  int m_RunNumber;
  int m_mcChannelNumber;

  float m_bweightcut;
  
  float m_pt;      
  float m_eta;     
  float m_phi;     
  float m_HT;
  float m_etmiss;  
  float m_phimiss; 
  float m_mlnu;
  float m_etmissoversqrtht;
  float m_d0sig;
  float m_d0sigPV;
  float m_dphi;
  float m_ptcone30;
  int m_njet;        
  int m_nbjet;       
  int m_isConv;      

  float m_dRmaxb;
  float m_bWeightmaxb;
  float m_dRlead;
  float m_ptlead;
  float m_dRmin;
  float m_ptmin;
  float m_ptdRmin;
  float m_bWeight;

  int m_isTot[3][3][4];
  int m_isFromSignal[3][3][4]; 
  int m_isFromb[3][3][4]; 
  int m_isFromHadron[3][3][4]; 

  int m_FracisFromb[3][3][4]; 
  int m_FracisFromHadron[3][3][4]; 

  // define the class for the cint dictionary
  ClassDef(EffiFakeMuon,1)
    
};

#endif // EffiFakeMuon_h
