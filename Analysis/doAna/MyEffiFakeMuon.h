#ifndef MyEffFakeMuon_h
#define MyEffiFakeMuon_h
//////////////////////////////////////////////////////////////////////
// 
// Author   : Atlas LPNHE Paris
// Creation : 01/10/2015
// Purpose  : base class to perform fake muon analysis with Run2 data
// Updated  :
//////////////////////////////////////////////////////////////////////

#include <TROOT.h>
#include <TChain.h>
#include <TTree.h>
#include <TFile.h>
#include <TObjArray.h>
#include <TH1F.h>
#include "../EventStruct/Tree_Nominal_Loose.h"

class EffiFakeMuon;

class MyEffiFakeMuon : public Tree_Nominal_Loose
{
 public :
  
  TFile *m_newfile;
  TTree *m_newtree;

  // constructor
  MyEffiFakeMuon(TTree * /*tree*/=0) {
    m_newtree = 0;
  };
  // destructor 
  virtual ~MyEffiFakeMuon(){};

  // methods of the TSelector
  virtual void Begin(TTree * /*tree*/);
  virtual void SlaveBegin(TTree * /*tree*/);
  //virtual void Init(TTree *tree);
  //virtual Int_t   Version() const { return 2; }
  virtual Bool_t Process(Long64_t entry);
  virtual void SlaveTerminate();
  virtual void Terminate();

  // Class to perform filter
  EffiFakeMuon *anaeffifakemuon;

  TObjArray *histosObj;

  TString m_outName;
  bool m_first;
  float m_norm;

 private:

};

#endif

