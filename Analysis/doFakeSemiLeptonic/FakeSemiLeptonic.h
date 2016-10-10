#ifndef FakeSemiLeptonic_h
#define FakeSemiLeptonic_h
//////////////////////////////////////////////////////////////////////
// 
// Author   : Atlas LPNHE Paris
// Creation : 01/10/2015
// Purpose  : base class to fill histograms for lepton+jets analysis
// Updated  :
//////////////////////////////////////////////////////////////////////

#include <TROOT.h>
#include <TChain.h>
#include <TTree.h>
#include <TFile.h>
#include <TObjArray.h>
#include <TH1F.h>
#include <iostream>
#include <vector>
#include <fstream>

#include "../Utils/MCDataSetUtils.h"
#include "../Utils/Utils.h"

#include "../TopFakes/TopFakes/FakesWeights.h"
#include "../TopFakes/TopFakes/MMEfficiency.h"
#include "../TopFakes/TopFakes/MatrixUtils.h"

class MyFakeSemiLeptonic;
class HistoManagerFakeSemiLeptonic;

class FakeSemiLeptonic
{
 public :
  // constructor
  FakeSemiLeptonic(MyFakeSemiLeptonic *myanalyse=0, TObjArray *histosObj=0);  
  // destructor
  virtual ~FakeSemiLeptonic();
  // execute method
  bool execute();

  float giveNtotEJet(int ilevel, int icut) { return m_NtotEJet[ilevel][icut]; }
  float giveNtotMuJet(int ilevel, int icut) { return m_NtotMuJet[ilevel][icut]; }
  
  float giveNLEJet(int ilevel, int icut) { return m_NLEJet[ilevel][icut]; }
  float giveNLMuJet(int ilevel, int icut) { return m_NLMuJet[ilevel][icut]; }
  float giveNTEJet(int ilevel, int icut) { return m_NTEJet[ilevel][icut]; }
  float giveNTMuJet(int ilevel, int icut) { return m_NTMuJet[ilevel][icut]; }

  float giveNfakesEJet(int ilevel, int icut) { return m_NfakesEJet[ilevel][icut]; }
  float giveNfakesMuJet(int ilevel, int icut) { return m_NfakesMuJet[ilevel][icut]; }
  float giveErrNfakesEJet(int ilevel, int icut) { return m_ErrNfakesEJet[ilevel][icut]; }
  float giveErrNfakesMuJet(int ilevel, int icut) { return m_ErrNfakesMuJet[ilevel][icut]; }

  // histogram manager
  HistoManagerFakeSemiLeptonic *hmanag;

  void SetChannel(int channel) {m_doChannel=channel;}
  void SetDoEstimate(bool doEstimate) {m_doEstimate=doEstimate;}
  void SetSyst(TString syst) {m_syst=syst;}
  void SetIso(TString iso) {m_iso=iso;}
  
  void SetRunNumber(int RunNumber){m_RunNumber=RunNumber;}
  int GetRunNumber(){return m_RunNumber;}
  float XSectWeight(){return m_XSectweight;}

 private:
  
  MyFakeSemiLeptonic *myclass;
  Utils *myutils;
  MCDataSetUtils *myMCDataSetutils;

  void LookForLeadingandClosestJet();
  int CalcNJet();
  int CalcNbJet();
  double CalcHT();
  
  void GiveMCWeight();
  bool Select();

  bool isTrueLepton();
  bool isTrueElectron();
  bool isTrueMuon();
  void FillHistos(int ilevel, int icut, float weight);

  bool m_passPreSelectionCuts;
  bool m_passSelectionCuts[2][5][100];
  bool m_pass1Jetincl;
  
  void GiveWeight();
  void CalcWeight();
  
  bool isLoose();
  bool isTight();

  // method to fill efficiency values from files, given the options
  void setEfficiencies();

  bool  m_isMC;
  bool m_doEstimate;
  TString m_syst;
  TString m_iso;
  
  int m_doChannel;
    
  FakesWeights *m_myWeight_el;
  FakesWeights *m_myWeight_el1;
  FakesWeights *m_myWeight_el2;
  FakesWeights *m_myWeight_mu;
  FakesWeights *m_myWeight_mu1;
  FakesWeights *m_myWeight_mu2;
  MatrixUtils *m_matrixutils; 

  float m_XSectweight;

  // weight
  float m_weight;
  float m_errweight;
  float m_weightbtag;
  float m_errweightbtag;
  
  float m_r;
  float m_f;

  int m_channel;
  int m_EventNumber;
  int m_RunNumber;
  int m_mcChannelNumber;

  float m_bweightcut;
  
  float m_pt;      
  float m_charge;
  float m_eta;     
  float m_phi; 
  float m_etacl;
  float m_phicl;
  float m_etmiss;  
  float m_phimiss;
  float m_HT;
  float m_mlnu;
  float m_d0sig;
  float m_dphi;
  float m_etcone20;
  float m_ptcone20;
  float m_ptcone30;
  int m_njet;        
  int m_nbjet;       
  int m_isConv;      

  bool m_isloose;
  bool m_istight;

  // leading jet
  float m_dR_LeadingJet;
  float m_pt_LeadingJet;
  float m_eta_LeadingJet;
  float m_phi_LeadingJet;
  float m_bWeight_LeadingJet;
  // closest jet
  float m_dR_ClosestJet;
  float m_pt_ClosestJet;
  float m_eta_ClosestJet;
  float m_phi_ClosestJet;
  float m_bWeight_ClosestJet;
  // jet with highest bWeight
  float m_dR_maxbWeightJet;
  float m_pt_maxbWeightJet;
  float m_eta_maxbWeightJet;
  float m_phi_maxbWeightJet;
  float m_bWeight_maxbWeightJet;

  // arrays for selection
  float m_NtotEJet[5][100];
  float m_NtotMuJet[5][100];
  
  float m_NLEJet[5][100];
  float m_NLMuJet[5][100];
  float m_NTEJet[5][100];
  float m_NTMuJet[5][100];
  
  float m_NfakesEJet[5][100];
  float m_NfakesMuJet[5][100];
  float m_ErrNfakesEJet[5][100];
  float m_ErrNfakesMuJet[5][100];

  // define the class for the cint dictionary
  ClassDef(FakeSemiLeptonic,1)

};

#endif
