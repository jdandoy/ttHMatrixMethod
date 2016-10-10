#ifndef EffiRealElecTP_h
#define EffiRealElecTP_h
//////////////////////////////////////////////////////////////////////
// 
// Author   : Atlas LPNHE Paris
// Creation : 01/01/2006
// Purpose  : base class to perform analysis 
// Updated  :
//////////////////////////////////////////////////////////////////////

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TObjArray.h>

#include <TH1F.h>
#include <iostream>
#include <fstream>
#include "../Utils/MCDataSetUtils.h"
#include "../Utils/Utils.h"

class MyEffiRealElecTP;
class HistoManagerEffiRealElecTP;
class EffiRealElecTP
{
 public:
  // constructor
  EffiRealElecTP(MyEffiRealElecTP *myanalyse=0, TObjArray *histosObj=0);  
  // destructor
  virtual ~EffiRealElecTP();
  // execute method
  bool execute();

  // histogram manager
  HistoManagerEffiRealElecTP *hmanag;

  void SetTrigger(TString Trigger) {m_trigger=Trigger;}
  void SetIso(TString Iso) {m_iso=Iso;}
  void SetNJet(TString Njet) {m_njetthr=Njet;}

  void SetRunNumber(int RunNumber){m_RunNumber=RunNumber;}
  int GetRunNumber(){return m_RunNumber;}
  float XSectWeight(){return m_XSectweight;}

 private:

  MyEffiRealElecTP *myclass;
  Utils *myutils;
  MCDataSetUtils *myMCDataSetutils;

  void FillHistos(int i);
  double deltaR(double eta1, double eta2, double phi1, double phi2); 
  double deltaPhi(double phi1, double phi2);
  double CalcdeltaPhi2(double phi1, double phi2);
  double transMass(double ptLep, double phiLep, 
		   double met, double phiMet); 
  double Calcmll(int i, int j); 

  void LookForLeadingandClosestJet(int i);
  int CalcNJet();
  int CalcNbJet();

  int WhichIndexEt(float Et);
  int WhichIndexEta(float Eta);
  int WhichIndexdRClosestJet(float dRClosestJet);
  int WhichIndexPtLeadingJet(float PtJet);
  int WhichIndexDPhi(float dphi);
  int WhichIndexMET(float met);
  int WhichIndexMTW(float mtw);
  int WhichIndexNJet(int njet);
  int WhichIndexNbJet(int nbjet);
  int WhichIndexNVert(int nvert);
  
  bool isLoose(); 
  bool isTight(int iel); 

  TString m_iso;
  TString m_trigger;
  TString m_njetthr;

  // weight 
  float m_weight;
  float m_weightbtag;
  
  float m_XSectweight;

  int m_channel;
  int m_EventNumber;
  int m_RunNumber;
  int m_mcChannelNumber;

  float m_mll;
  float m_et;      
  float m_eta;     
  float m_phi;     
  float m_etacl;     
  float m_phicl;     
  float m_HT;
  float m_etmiss;  
  float m_phimiss; 
  float m_mlnu;   
  float m_etmissoversqrtht;
  float m_etcone20;
  float m_ptcone20;
  float m_dphi;
  int m_njet;        
  int m_nbjet;       
  int m_isConv;      

  bool m_isOS;
  float m_nvert;

  float m_bweightcut;

  float m_dRmaxb;
  float m_bWeightmaxb;
  float m_dRlead;
  float m_ptlead;
  float m_dRmin;
  float m_ptmin;
  float m_ptdRmin;
  float m_bWeight;

  // define the class for the cint dictionary
  ClassDef(EffiRealElecTP,1)
    
};

#endif // EffiRealElecTP_h
