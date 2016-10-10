#ifndef MyFakeSemiLeptonic_h
#define MyFakeSemiLeptonic_h
//////////////////////////////////////////////////////////////////////
// 
// Author   : Atlas LPNHE Paris
// Creation : 01/10/2015
// Purpose  : base class to perform lepton+jets analysis with Run2 data
// Updated  :
//////////////////////////////////////////////////////////////////////

#include "../EventStruct/Tree_Nominal_Loose.h"

#include <TROOT.h>
#include <TChain.h>
#include <TTree.h>
#include <TFile.h>
#include <TObjArray.h>
#include <TH1F.h>

class FakeSemiLeptonic;

class MyFakeSemiLeptonic : public Tree_Nominal_Loose
{
  
 public :
  
  TFile *m_newfile;
  TTree *m_newtree;

  // constructor
  MyFakeSemiLeptonic(TTree * /*tree*/=0) {
    m_newtree = 0;
  };
  // destructor 
  virtual ~MyFakeSemiLeptonic(){};

  // methods of the TSelector
  virtual void Begin(TTree * /*tree*/);
  virtual void SlaveBegin(TTree * /*tree*/);
  //virtual void Init(TTree *tree);
  //virtual Int_t   Version() const { return 2; }
  virtual Bool_t Process(Long64_t entry);
  virtual void SlaveTerminate();
  virtual void Terminate();

  TString giveOption() { return m_option; }

  // Class to perform filter
  FakeSemiLeptonic *anafakesemileptonic;

  TObjArray *histosObj;

  TString m_option;

  bool m_first;
  float m_norm;

 private:

};

#endif

