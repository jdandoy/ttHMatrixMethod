#define MyEffiRealMuonTP_cxx
//////////////////////////////////////////////////////////////////////
// 
// Author   : Atlas LPNHE Paris
// Creation : 01/10/2015
// Purpose  : base class to perform T&P muon analysis with Run2 data
// Updated  :
//////////////////////////////////////////////////////////////////////

#include "MyEffiRealMuonTP.h"
#include "../doEffiRealMuonTP/EffiRealMuonTP.h"

#include "TObject.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TObjArray.h>

// ====================================================================
void MyEffiRealMuonTP::Begin(TTree *)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();
  std::cout << "Begin: starting MyEffiRealMuonTP with process option: " 
	    << option.Data() << std::endl;
  
  histosObj = new TObjArray();
  // Tool for Filter
  anaeffirealmuonTP = new EffiRealMuonTP(this,histosObj);
  
  // define options for trigger
  anaeffirealmuonTP->SetTrigger("");
  if (option.Contains("HLT_mu20_iloose_L1MU15")) anaeffirealmuonTP->SetTrigger("HLT_mu20_iloose_L1MU15");
  if (option.Contains("HLT_mu20_L1MU15")) anaeffirealmuonTP->SetTrigger("HLT_mu20_L1MU15");
  if (option.Contains("HLT_mu50")) anaeffirealmuonTP->SetTrigger("HLT_mu50");

  anaeffirealmuonTP->SetIso("Std");
  if (option.Contains("Iso6")) anaeffirealmuonTP->SetIso("Iso6");

  // define options for njet
  if (option.Contains("njeteq1"))    anaeffirealmuonTP->SetNJet("njeteq1");
  if (option.Contains("njetge1"))    anaeffirealmuonTP->SetNJet("njetge1");
  if (option.Contains("njetge2"))    anaeffirealmuonTP->SetNJet("njetge2");
  if (option.Contains("njeteq2or3")) anaeffirealmuonTP->SetNJet("njeteq2or3");
  if (option.Contains("njetge4"))    anaeffirealmuonTP->SetNJet("njetge4");
}

//====================================================================
void MyEffiRealMuonTP::SlaveBegin(TTree * /*tree*/)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).
  
  TString option = GetOption();
}

//====================================================================
Bool_t MyEffiRealMuonTP::Process(Long64_t entry)
{
  
  // The Process() function is called for each entry in the tree (or possibly
  // keyed object in the case of PROOF) to be processed. The entry argument
  // specifies which entry in the currently loaded tree is to be processed.
  // It can be passed to either AnlClass_General::GetEntry() or TBranch::GetEntry()
  // to read either all or the required parts of the data. When processing
  // keyed objects with PROOF, the object is already loaded and is available
  // via the fObject pointer.
  //
  // This function should contain the "body" of the analysis. It can contain
  // simple or elaborate selection criteria, run algorithms on the data
  // of the event and typically fill histograms.
  //
  // The processing can be stopped by calling Abort().
  //
  // Use fStatus to set the return value of TTree::Process().
  //
  // The return value is currently not used.

  // retrieve event number 
  
  Long64_t chainEntry = fChain->GetChainEntryNumber(entry);
  
  //
  // selection of data by run and LB
  //
  b_runNumber->GetEntry(entry);
  b_eventNumber->GetEntry(entry);
  b_mcChannelNumber->GetEntry(entry);

  fChain->GetTree()->GetEntry(entry);

  if(entry%10000==0) 
    //     if(evts%100==0) 
    std::cout << "Event #" << chainEntry << " , "  
  	      << " entry = " << entry << " , " 
      //	      << " " << evts << "th event after GRL " 
	      << std::endl;
  
  bool iseffirealmuonTP = anaeffirealmuonTP->execute();
 
  return kTRUE;
}

// ===============================================================
void MyEffiRealMuonTP::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.
  
}

// ===============================================================
void MyEffiRealMuonTP::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.
  
  //
  // Save previously filled histos in root file
  //return;
  // 
  TString name_output="Ana-EffiRealMuonTP.root";
  TFile  df(name_output,"RECREATE");
  df.mkdir("HistosEffiRealMuonTP");
  df.cd("HistosEffiRealMuonTP");  
  histosObj->Print();
  histosObj->Write();
  df.Close();

}

