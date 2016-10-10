#define MySemiLeptonic_cxx
//////////////////////////////////////////////////////////////////////
// 
// Author   : Atlas LPNHE Paris
// Creation : 01/10/2015
// Purpose  : base class to perform lepton+jets analysis with Run2 data
// Updated  :
//////////////////////////////////////////////////////////////////////

#include "MySemiLeptonic.h"
#include "../doSemiLeptonic/SemiLeptonic.h"

#include "TObject.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TObjArray.h>

// ====================================================================
void MySemiLeptonic::Begin(TTree *)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).

  m_option = GetOption();
  std::cout << "Begin: starting MySemiLeptonic with process option: " 
	    << m_option.Data() << std::endl;
  
  histosObj = new TObjArray();
  // Tool for Filter
  anasemileptonic = new SemiLeptonic(this,histosObj);

  if (m_option.Contains("ejet"))  anasemileptonic->SetChannel(0);
  if (m_option.Contains("mujet")) anasemileptonic->SetChannel(1);

  m_first = true;
}

//====================================================================
void MySemiLeptonic::SlaveBegin(TTree * /*tree*/)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).
  
  m_option = GetOption();
}

//====================================================================
Bool_t MySemiLeptonic::Process(Long64_t entry)
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
  
  //std::cout << " MySemiLeptonic::Process " << std::endl;
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
    TH1F* h = (TH1F*) file->GetDirectory("ejets")->Get("cutflow_mc_pu_zvtx");
    //m_norm = h->GetSumOfWeights();
    m_norm = h->GetBinContent(1);
    std::cout << " norm elec = " << m_norm << std::endl;
    TH1F* h2 = (TH1F*) file->GetDirectory("mujets")->Get("cutflow_mc_pu_zvtx");
    //m_norm = h->GetSumOfWeights();
    m_norm = h2->GetBinContent(1);
    std::cout << " norm muon = " << m_norm << std::endl;

    printf("nevent = %8.2f\n",m_norm);
    delete h; 
    delete h2;
    delete file;
    m_first = false;
  }
  
  fChain->GetTree()->GetEntry(entry);

  /*if(entry%10000==0) 
    std::cout << "Event #" << chainEntry << " , "  
    	      << " entry = " << entry << " , " 
  	      << std::endl;*/
  
  bool issemileptonic = anasemileptonic->execute();
 
  return kTRUE;
}

// ===============================================================
void MySemiLeptonic::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.
  
}

// ===============================================================
void MySemiLeptonic::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.
  

  //std::cout << " MySemiLeptonic::SlaveTerminate() " << std::endl;
  //
  // Save previously filled histos in root file
  //return;
  // 
  TString name_output="Ana-SemiLeptonic.root";
  TFile  df(name_output,"RECREATE");
  df.mkdir("HistosSemiLeptonic");
  df.cd("HistosSemiLeptonic");  

  // retrieve the cut flow
  DefineHistos_CutFlow();
  for (int i=0;i<30;i++) {
    hCutflowEJets->SetBinContent(i+1,anasemileptonic->giveCutflowEJets(i));
    hCutflowMuJets->SetBinContent(i+1,anasemileptonic->giveCutflowMuJets(i));
    hCutflowEJetsweight->SetBinContent(i+1,anasemileptonic->giveCutflowEJetsweight(i));
    hCutflowMuJetsweight->SetBinContent(i+1,anasemileptonic->giveCutflowMuJetsweight(i));
    hCutflowEJetsweightpu->SetBinContent(i+1,anasemileptonic->giveCutflowEJetsweightpu(i));
    hCutflowMuJetsweightpu->SetBinContent(i+1,anasemileptonic->giveCutflowMuJetsweightpu(i));
    hCutflowEJetsweightsf->SetBinContent(i+1,anasemileptonic->giveCutflowEJetsweightsf(i));
    hCutflowMuJetsweightsf->SetBinContent(i+1,anasemileptonic->giveCutflowMuJetsweightsf(i));
  }

  std::cout << " mc = " << mcChannelNumber << std::endl;
  if (mcChannelNumber>0) {      
    /// Scale MC to lumi
    for (int s = 0; s<histosObj->GetEntriesFast();s++) {
      //       std::cout<<&histosObj[s]<<std::endl;
      ((TH1F*) histosObj->At(s))->Scale(anasemileptonic->XSectWeight()/m_norm);
    }
  }
  
  //histosObj->Print();
  histosObj->Write();
  df.Close();
}

// =================================================================
void MySemiLeptonic::DefineHistos_CutFlow() 
{
  //
  // definition of histograms for cut flow
  //

  hCutflowEJets = new TH1F("hCutflowEJets", "Electron-Jets Cutflow", 
			   30, 0, 30);
  hCutflowMuJets = new TH1F("hCutflowMuJets", "Muon-Jets Cutflow", 
			    30, 0, 30);
  
  // histograms containing cutflows for weighted events
  // weight = weightMC
  //
  hCutflowEJetsweight = new TH1F("hCutflowEJetsweight", 
				 "Electron-Jets Cutflow - sum of weights", 
				 30, 0, 30);
  hCutflowMuJetsweight = new TH1F("hCutflowMuJetsweight", 
				  "Muon-Jets Cutflow - sum of weights", 
				  30, 0, 30);
    
  //
  // histograms containing cutflows for weighted events
  // weight = weightMC*weightpu
  //
  hCutflowEJetsweightpu = new TH1F("hCutflowEJetsweightpu", 
				   "Electron-Jets Cutflow - sum of weightpus", 
				   30, 0, 30);
  hCutflowMuJetsweightpu = new TH1F("hCutflowMuJetsweightpu", 
				    "Muon-Jets Cutflow - sum of weightpus", 
				    30, 0, 30);
  
  //std::cout << " end of Define Histos" << std::endl;
  //
  // histograms containing cutflows for weighted events
  // weight = weightMC*SF
  //
  hCutflowEJetsweightsf = new TH1F("hCutflowEJetsweightsf", 
				   "Electron-Jets Cutflow - sum of weightsfs", 
				   30, 0, 30);
  hCutflowMuJetsweightsf = new TH1F("hCutflowMuJetsweightsf", 
				    "Muon-Jets Cutflow - sum of weightsfs", 
				    30, 0, 30);
}

