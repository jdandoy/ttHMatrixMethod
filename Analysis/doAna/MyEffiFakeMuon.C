#define MyEffiFakeMuon_cxx
//////////////////////////////////////////////////////////////////////
// 
// Author   : Atlas LPNHE Paris
// Creation : 01/10/2015
// Purpose  : base class to perform fake muon analysis with Run2 data
// Updated  :
//////////////////////////////////////////////////////////////////////

#include "MyEffiFakeMuon.h"
#include "../doEffiFakeMuon/EffiFakeMuon.h"

#include "TObject.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TObjArray.h>

// ====================================================================
void MyEffiFakeMuon::Begin(TTree *)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();
  std::cout << "Begin: starting MyEffiFakeMuon with process option: " 
	    << option.Data() << std::endl;

  histosObj = new TObjArray();
  // Tool for analysis
  anaeffifakemuon = new EffiFakeMuon(this,histosObj);
  
  if (option.Contains("pretag")) anaeffifakemuon->SetPretag(true);

  if (option.Contains("nobtag")) anaeffifakemuon->SetNoBtag(true);
  else if (option.Contains("btag")) {anaeffifakemuon->SetBtag(true);std::cout<<"oui"<<std::endl;}
  
  anaeffifakemuon->SetIso("Std");
  if (option.Contains("Iso6")) anaeffifakemuon->SetIso("Iso6");

  anaeffifakemuon->SetCR("");
  if (option.Contains("lowETmissnocut")) anaeffifakemuon->SetCR("nocut");
  else if (option.Contains("d0sig")) anaeffifakemuon->SetCR("d0sig");
  else if (option.Contains("highMTW"))anaeffifakemuon->SetCR("highMTW");
  else if (option.Contains("lowETmissMTW"))anaeffifakemuon->SetCR("lowETmissMTW");
  else if (option.Contains("lowETmiss20")) anaeffifakemuon->SetCR("lowETmiss20");
  else if (option.Contains("lowETmissMTW20"))anaeffifakemuon->SetCR("lowETmissMTW20");

  // define options for trigger
  anaeffifakemuon->SetTrigger("");
  if (option.Contains("HLT_mu20_iloose_L1MU15")) anaeffifakemuon->SetTrigger("HLT_mu20_iloose_L1MU15");
  if (option.Contains("HLT_mu20_L1MU15")) anaeffifakemuon->SetTrigger("HLT_mu20_L1MU15");
  if (option.Contains("HLT_mu50")) anaeffifakemuon->SetTrigger("HLT_mu50");
  
  m_outName = "Ana-EffiFakeMuon.root";
  if (option.Contains("NAME")){
        m_outName = option( option.Index("NAME")+4, option.Length() );
        std::cout << "Setting Output name to " << m_outName << std::endl;
  }

  m_first = true;
}                                   

//====================================================================
void MyEffiFakeMuon::SlaveBegin(TTree * /*tree*/)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();

}

//====================================================================
Bool_t MyEffiFakeMuon::Process(Long64_t entry)
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

  //std::cout << " process " << std::endl;
  // retrieve event number 
  Long64_t chainEntry = fChain->GetChainEntryNumber(entry);
  
  //
  // selection of data by run and LB
  //
  b_runNumber->GetEntry(entry);
  b_eventNumber->GetEntry(entry);
  b_mcChannelNumber->GetEntry(entry);

  //std::cout << " channel = " << EffiFakeLepton_channelNumber << std::endl;
  // retrieve normalization kept in some histos
  if (m_first && mcChannelNumber>0) {
    const char *current_file_name = ((TChain*)(fChain))->GetFile()->GetName();
    std::cout << " name = " << current_file_name << std::endl;
    TFile* file = new TFile(current_file_name,"read");
    std::cout << " file = " << file << std::endl;
    TH1F* h = (TH1F*) file->GetDirectory("mujets_2016")->Get("cutflow_mc_pu_zvtx_Loose");
    //m_norm = h->GetSumOfWeights();
    m_norm = h->GetBinContent(1);
    //std::cout << " norm = " << m_norm << std::endl;

    printf("nevent = %8.2f\n",m_norm);
    //delete h2; 
    delete h; 
    delete file;
    m_first = false;
    
    //m_norm = 1.;
  }
  fChain->GetTree()->GetEntry(entry);

  if(entry%10000==0) 
    //     if(evts%100==0) 
    std::cout << "Event #" << chainEntry << " , "  
  	      << " entry = " << entry << " , " 
  //	      << " " << evts << "th event after GRL " << std::endl;
	      << std::endl;

  bool iseffifakemuon = anaeffifakemuon->execute();
  if (iseffifakemuon) {;}

  return kTRUE;
}

// ===============================================================
void MyEffiFakeMuon::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.
  
}

// ===============================================================
void MyEffiFakeMuon::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.
  
  //
  // Save previously filled histos in root file
  // 
  //TString name_output="Ana-EffiFakeMuon.root";
  TFile  df(m_outName,"RECREATE");
  df.mkdir("HistosEffiFakeMuon");
  df.cd("HistosEffiFakeMuon");  
  //df.cd();
  std::cout << " mc = " << mcChannelNumber << std::endl;
  if (mcChannelNumber>0) {      
      /// Scale MC to lumi
      for (int s = 0; s<histosObj->GetEntriesFast();s++) {
	//       std::cout<<&histosObj[s]<<std::endl;
	((TH1F*) histosObj->At(s))->Scale(anaeffifakemuon->XSectWeight()/m_norm);
      }
  }
  //histosObj->Print();
  histosObj->Write();
  df.Close();
  
}

