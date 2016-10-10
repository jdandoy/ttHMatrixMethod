#ifndef MyEffiRealMuonTP_h
#define MyEffiRealMuonTP_h
//////////////////////////////////////////////////////////////////////
// 
// Author   : Atlas LPNHE Paris
// Creation : 01/10/2015
// Purpose  : base class to perform T&P muon analysis with Run2 data
// Updated  :
//////////////////////////////////////////////////////////////////////

#include "../EventStruct/Tree_Nominal_Loose.h"

#include <TROOT.h>
#include <TChain.h>
#include <TTree.h>
#include <TFile.h>
#include <TObjArray.h>

class EffiRealMuonTP;

class MyEffiRealMuonTP : public Tree_Nominal_Loose
{
  
 public :
  
  TFile *m_newfile;
  TTree *m_newtree;

  // constructor
  MyEffiRealMuonTP(TTree * /*tree*/=0) {
    m_newtree = 0;
  };
  // destructor 
  virtual ~MyEffiRealMuonTP(){};

  // methods of the TSelector
  virtual void Begin(TTree * /*tree*/);
  virtual void SlaveBegin(TTree * /*tree*/);
  //virtual void Init(TTree *tree);
  //virtual Int_t   Version() const { return 2; }
  virtual Bool_t Process(Long64_t entry);
  virtual void SlaveTerminate();
  virtual void Terminate();

  // Class to perform filter
  EffiRealMuonTP *anaeffirealmuonTP;

  TObjArray *histosObj;

 private:

};

#endif

