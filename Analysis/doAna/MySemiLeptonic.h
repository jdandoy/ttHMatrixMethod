#ifndef MySemiLeptonic_h
#define MySemiLeptonic_h
//////////////////////////////////////////////////////////////////////
// 
// Author   : Atlas LPNHE Paris
// Creation : 01/10/2015
// Purpose  : base class to perform lepton+jets analysis with Run2 data
// Updated  :
//////////////////////////////////////////////////////////////////////

//#include "../EventStruct/Tree_Nominal.h"
#include "../EventStruct/Tree_Nominal_Loose.h"

#include <TROOT.h>
#include <TChain.h>
#include <TTree.h>
#include <TFile.h>
#include <TObjArray.h>
#include <TH1F.h>

class SemiLeptonic;

//class MySemiLeptonic : public Tree_Nominal
class MySemiLeptonic : public Tree_Nominal_Loose
{
  
 public :
  
  TFile *m_newfile;
  TTree *m_newtree;

  // constructor
  MySemiLeptonic(TTree * /*tree*/=0) {
    m_newtree = 0;
  };
  // destructor 
  virtual ~MySemiLeptonic(){};

  // methods of the TSelector
  virtual void Begin(TTree * /*tree*/);
  virtual void SlaveBegin(TTree * /*tree*/);
  //virtual void Init(TTree *tree);
  //virtual Int_t   Version() const { return 2; }
  virtual Bool_t Process(Long64_t entry);
  virtual void SlaveTerminate();
  virtual void Terminate();

  TString giveOption() { return m_option; }
  void DefineHistos_CutFlow(); 

  // Class to perform filter
  SemiLeptonic *anasemileptonic;

  TObjArray *histosObj;

  TString m_option;

  // histograms for cut flow
  TH1F *hCutflowEJets;
  TH1F *hCutflowMuJets;

  TH1F *hCutflowEJetsweight;
  TH1F *hCutflowMuJetsweight;

  TH1F *hCutflowEJetsweightpu;
  TH1F *hCutflowMuJetsweightpu;

  TH1F *hCutflowEJetsweightsf;
  TH1F *hCutflowMuJetsweightsf;

  bool m_first;
  float m_norm;

 private:

};

#endif

