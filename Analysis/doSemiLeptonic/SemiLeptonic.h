#ifndef SemiLeptonic_h
#define SemiLeptonic_h
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

class MySemiLeptonic;
class HistoManagerSemiLeptonic;

class SemiLeptonic
{
 public :
  // constructor
  SemiLeptonic(MySemiLeptonic *myanalyse=0, TObjArray *histosObj=0);  
  // destructor
  virtual ~SemiLeptonic();
  // execute method
  bool execute();

  void SetChannel(int channel) {m_doChannel=channel;}
  // method to retrieve the vectors
  float giveCutflowEJets(int ibin) const { return m_CutflowEJets[ibin]; }
  float giveCutflowMuJets(int ibin) const { return m_CutflowMuJets[ibin]; }
  float giveCutflowEJetsweight(int ibin) const { return m_CutflowEJetsweight[ibin]; }
  float giveCutflowMuJetsweight(int ibin) const { return m_CutflowMuJetsweight[ibin]; }
  float giveCutflowEJetsweightpu(int ibin) const { return m_CutflowEJetsweightpu[ibin]; }
  float giveCutflowMuJetsweightpu(int ibin) const { return m_CutflowMuJetsweightpu[ibin]; }
  float giveCutflowEJetsweightsf(int ibin) const { return m_CutflowEJetsweightsf[ibin]; }
  float giveCutflowMuJetsweightsf(int ibin) const { return m_CutflowMuJetsweightsf[ibin]; }

  // histogram manager
  HistoManagerSemiLeptonic *hmanag;

  float m_CutflowEJets[30];
  float m_CutflowMuJets[30];

  float m_CutflowEJetsweight[30];
  float m_CutflowMuJetsweight[30];

  float m_CutflowEJetsweightpu[30];
  float m_CutflowMuJetsweightpu[30];

  float m_CutflowEJetsweightsf[30];
  float m_CutflowMuJetsweightsf[30];
  
  void SetRunNumber(int RunNumber){m_RunNumber=RunNumber;}
  int GetRunNumber(){return m_RunNumber;}
  float XSectWeight(){return m_XSectweight;}

 private:
  
  MySemiLeptonic *myclass;
  Utils *myutils;
  MCDataSetUtils *myMCDataSetutils;

  void LookForLeadingandClosestJet();
  int CalcNJet();
  int CalcNbJet();
  double CalcHT();
  
  void GiveMCWeight();
  bool Select();
  bool isTight();

  bool isTrueLepton();
  bool isTrueElectron();
  bool isTrueMuon();
  void FillHistos(int ilevel, int icut, float weight);

  // weight 
  float m_weight;
  float m_weightbtag;
  
  float m_XSectweight;

  bool m_Pretag;//not to use btagging information
  bool m_Btag;//to filter btagged events
  bool m_NoBtag;//to veto btagged events
  
  int m_doChannel;

  int m_typeCR;
  
  TString m_trigger;
  TString m_iso;
  
  int m_channel;
  int m_EventNumber;
  int m_RunNumber;
  int m_mcChannelNumber;

  bool m_passPreSelectionCuts;
  bool m_passSelectionCuts[2][5][100];

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

  int m_isTot[3][3][4];
  int m_isFromSignal[3][3][4]; 
  int m_isFromb[3][3][4]; 
  int m_isFromHadron[3][3][4]; 

  int m_FracisFromb[3][3][4]; 
  int m_FracisFromHadron[3][3][4]; 

  // define the class for the cint dictionary
  ClassDef(SemiLeptonic,1)

};

#endif
