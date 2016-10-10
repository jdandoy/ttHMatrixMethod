#define MyFakeSemiLeptonic_cxx
//////////////////////////////////////////////////////////////////////
// 
// Author   : Atlas LPNHE Paris
// Creation : 01/10/2015
// Purpose  : base class to perform lepton+jets analysis with Run2 data
// Updated  :
//////////////////////////////////////////////////////////////////////

#include "MyFakeSemiLeptonic.h"
#include "../doFakeSemiLeptonic/FakeSemiLeptonic.h"
#include "../doFakeSemiLeptonic/HistoManagerFakeSemiLeptonic.h"

#include "TObject.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TObjArray.h>

// ====================================================================
void MyFakeSemiLeptonic::Begin(TTree *)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).

  m_option = GetOption();
  std::cout << "Begin: starting MyFakeSemiLeptonic with process option: " 
	    << m_option.Data() << std::endl;
  
  histosObj = new TObjArray();
  // Tool for Filter
  anafakesemileptonic = new FakeSemiLeptonic(this,histosObj);

  // pass the channel to be analyzed
  if (m_option.Contains("ejet"))  anafakesemileptonic->SetChannel(0);
  if (m_option.Contains("mujet")) anafakesemileptonic->SetChannel(1);

  // pass the lepton isolation to be used at Tight level
  anafakesemileptonic->SetIso("Std");
  if (m_option.Contains("Iso6")) anafakesemileptonic->SetIso("Iso6");

  // pass which systematic uncertainty
  if (m_option.Contains("estimate")) {
    anafakesemileptonic->SetDoEstimate(true);
    if (m_option.Contains("MCup")) anafakesemileptonic->SetSyst("MCup");
    else if (m_option.Contains("MCdown")) anafakesemileptonic->SetSyst("MCdown");
    else if (m_option.Contains("CRfake")) anafakesemileptonic->SetSyst("CRfake");
    else if (m_option.Contains("CRreal")) anafakesemileptonic->SetSyst("CRreal");
    else if (m_option.Contains("EffPar")) anafakesemileptonic->SetSyst("EffPar");
    else anafakesemileptonic->SetSyst("");
  }
  anafakesemileptonic->setEfficiencies();

  m_first = true;
}

//====================================================================
void MyFakeSemiLeptonic::SlaveBegin(TTree * /*tree*/)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).
  
  m_option = GetOption();
}

//====================================================================
Bool_t MyFakeSemiLeptonic::Process(Long64_t entry)
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
  
  //std::cout << " MyFakeSemiLeptonic::Process " << std::endl;
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
    std::cout << " norm = " << m_norm << std::endl;

    printf("nevent = %8.2f\n",m_norm);
    delete h; 
    delete file;
    m_first = false;
  }
  
  fChain->GetTree()->GetEntry(entry);

  /*if(entry%10000==0) 
    std::cout << "Event #" << chainEntry << " , "  
    	      << " entry = " << entry << " , " 
  	      << std::endl;*/
  
  bool isfakesemileptonic = anafakesemileptonic->execute();
 
  return kTRUE;
}

// ===============================================================
void MyFakeSemiLeptonic::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.
  
}

// ===============================================================
void MyFakeSemiLeptonic::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.
  

  //std::cout << " MyFakeSemiLeptonic::SlaveTerminate() " << std::endl;
  //
  // Save previously filled histos in root file
  //return;
  // 
  TString name_output="Ana-FakeSemiLeptonic.root";
  TFile  df(name_output,"RECREATE");
  df.mkdir("HistosSemiLeptonic");
  df.cd("HistosSemiLeptonic");  

  std::cout << " mc = " << mcChannelNumber << std::endl;
  if (mcChannelNumber>0) {      
    /// Scale MC to lumi
    for (int s = 0; s<histosObj->GetEntriesFast();s++) {
      //       std::cout<<&histosObj[s]<<std::endl;
      ((TH1F*) histosObj->At(s))->Scale(anafakesemileptonic->XSectWeight()/m_norm);
    }
  }
  
  //histosObj->Print();
  histosObj->Write();
  df.Close();
  //anafakesemileptonic->delEfficiencies();

  // arrays for selection
  float NtotEJet[5][100];
  float NtotMuJet[5][100];
  
  float NLEJet[5][100];
  float NLMuJet[5][100];
  float NTEJet[5][100];
  float NTMuJet[5][100];
  
  float NfakesEJet[5][100];
  float NfakesMuJet[5][100];
  float ErrNfakesEJet[5][100];
  float ErrNfakesMuJet[5][100];

  // loop on level of MET/MTW 
  for (int ilevel=0;ilevel<5;ilevel++) {
    // loop on level of cut
    for (int icut=0;icut<84;icut++) {
      NtotEJet[ilevel][icut]       = anafakesemileptonic->giveNtotEJet(ilevel,icut);
      NtotMuJet[ilevel][icut]      = anafakesemileptonic->giveNtotMuJet(ilevel,icut);
      
      NLEJet[ilevel][icut]         = anafakesemileptonic->giveNLEJet(ilevel,icut);
      NLMuJet[ilevel][icut]        = anafakesemileptonic->giveNLMuJet(ilevel,icut);
      NTEJet[ilevel][icut]         = anafakesemileptonic->giveNTEJet(ilevel,icut);
      NTMuJet[ilevel][icut]        = anafakesemileptonic->giveNTMuJet(ilevel,icut);
      
      NfakesEJet[ilevel][icut]     = anafakesemileptonic->giveNfakesEJet(ilevel,icut);
      NfakesMuJet[ilevel][icut]    = anafakesemileptonic->giveNfakesMuJet(ilevel,icut);
      ErrNfakesEJet[ilevel][icut]  = anafakesemileptonic->giveErrNfakesEJet(ilevel,icut);
      ErrNfakesMuJet[ilevel][icut] = anafakesemileptonic->giveErrNfakesMuJet(ilevel,icut);
    }
  }

  // histo containing fake yield
  TH1F *hFakeYield[2][5][100];
  // histo containing the squared systematic error on the fake yield
  TH1F *hFakeYieldSqSys[2][5][100];

  // loop on type of lepton 
  for (int itype=0;itype<2;itype++) {
    // loop on level of MET/MTW 
    for (int ilevel=0;ilevel<5;ilevel++) {
      // loop on level of cut
      for (int icut=0;icut<84;icut++) {
	hFakeYield[itype][ilevel][icut]      = anafakesemileptonic->hmanag->givehFakeYield(itype,ilevel,icut);
	hFakeYieldSqSys[itype][ilevel][icut] = anafakesemileptonic->hmanag->givehFakeYieldSqSys(itype,ilevel,icut);
      }
    }
  }

  bool doEstimate = false;
  if (m_option.Contains("estimate")) doEstimate = true;
  if (!doEstimate) {
    delete anafakesemileptonic;
    delete histosObj;
    return;
  }

  FILE *filestr;
  TString nameFile="Yields";
  nameFile+=m_option.Data();
  nameFile+=".txt";std::cout<<nameFile<<std::endl;
  filestr = fopen (nameFile,"w");
  
  fprintf(filestr,"%s\n","Cuts:    Channel: Nevents:      NL:       NT:       Nfakes:");
  std::cout<<"Cuts:    "<<"Channel: "<<"Nevents:      "<<"NL:       "<<"NT:       "<<"Nfakes: (+/-stat) (+/-sys)"<<std::endl;
    
  TString typeLept = "";
  TString typeLevel = "";
  TString typeCut = "";
  
  // loop on level of MET/MTW 
  for (int ilevel=0;ilevel<5;ilevel++) {
    if (ilevel==0) typeLevel = "    no cut on MET, MTW";
    else if (ilevel==1) typeLevel = "    cut on MET, MTW>30 GeV";
    else if (ilevel==2) typeLevel = "    cut on MTW>20 GeV & MET+MTW>60 GeV";
    else if (ilevel==3) typeLevel = "    cut on MTW<20 GeV & MET+MTW<60 GeV";
    else if (ilevel==4) typeLevel = "    cut on MET+MTW<60 GeV";
    
    // loop on level of cut
    for (int icut=0;icut<84;icut++) {
      // >=6 jets
      if (icut==0)       typeCut =  "ge6j_pretag";
      else if (icut==1)  typeCut =  "ge6j_alltag";
      else if (icut==2)  typeCut =  "ge6j_0btag";
      else if (icut==3)  typeCut =  "ge6j_1btag";
      else if (icut==4)  typeCut =  "ge6j_2btag";
      else if (icut==5)  typeCut =  "ge6j_ge1btag";
      else if (icut==6)  typeCut =  "ge6j_ge2btag";
      // ==6 jets
      else if (icut==7)  typeCut =  "6j_pretag";
      else if (icut==8)  typeCut =  "6j_alltag";
      else if (icut==9)  typeCut =  "6j_0btag";
      else if (icut==10) typeCut =  "6j_1btag";
      else if (icut==11) typeCut =  "6j_2btag";
      else if (icut==12) typeCut =  "6j_ge1btag";
      else if (icut==13) typeCut =  "6j_ge2btag";
      // >=5 jets
      else if (icut==14) typeCut =  "ge5j_pretag";
      else if (icut==15) typeCut =  "ge5j_alltag";
      else if (icut==16) typeCut =  "ge5j_0btag";
      else if (icut==17) typeCut =  "ge5j_1btag";
      else if (icut==18) typeCut =  "ge5j_2btag";
      else if (icut==19) typeCut =  "ge5j_ge1btag";
      else if (icut==20) typeCut =  "ge5j_ge2btag";
      // ==5 jets
      else if (icut==21) typeCut =  "5j_pretag";
      else if (icut==22) typeCut =  "5j_alltag";
      else if (icut==23) typeCut =  "5j_0btag";
      else if (icut==24) typeCut =  "5j_1btag";
      else if (icut==25) typeCut =  "5j_2btag";
      else if (icut==26) typeCut =  "5j_ge1btag";
      else if (icut==27) typeCut =  "5j_ge2btag";
      // >=4 jets
      else if (icut==28) typeCut =  "ge4j_pretag";
      else if (icut==29) typeCut =  "ge4j_alltag";
      else if (icut==30) typeCut =  "ge4j_0btag";
      else if (icut==31) typeCut =  "ge4j_1btag";
      else if (icut==32) typeCut =  "ge4j_2btag";
      else if (icut==33) typeCut =  "ge4j_ge1btag";
      else if (icut==34) typeCut =  "ge4j_ge2btag";
      // ==4 jets
      else if (icut==35) typeCut =  "4j_pretag";
      else if (icut==36) typeCut =  "4j_alltag";
      else if (icut==37) typeCut =  "4j_0btag";
      else if (icut==38) typeCut =  "4j_1btag";
      else if (icut==39) typeCut =  "4j_2btag";
      else if (icut==40) typeCut =  "4j_ge1btag";
      else if (icut==41) typeCut =  "4j_ge2btag";
      // >=3 jets
      else if (icut==42) typeCut =  "ge3j_pretag";
      else if (icut==43) typeCut =  "ge3j_alltag";
      else if (icut==44) typeCut =  "ge3j_0btag";
      else if (icut==45) typeCut =  "ge3j_1btag";
      else if (icut==46) typeCut =  "ge3j_2btag";
      else if (icut==47) typeCut =  "ge3j_ge1btag";
      else if (icut==48) typeCut =  "ge3j_ge2btag";
      // ==3 jets
      else if (icut==49) typeCut =  "3j_pretag";
      else if (icut==50) typeCut =  "3j_alltag";
      else if (icut==51) typeCut =  "3j_0btag";
      else if (icut==52) typeCut =  "3j_1btag";
      else if (icut==53) typeCut =  "3j_2btag";
      else if (icut==54) typeCut =  "3j_ge1btag";
      else if (icut==55) typeCut =  "3j_ge2btag";
      // >=2 jets
      else if (icut==56) typeCut =  "ge2j_pretag";
      else if (icut==57) typeCut =  "ge2j_alltag";
      else if (icut==58) typeCut =  "ge2j_0btag";
      else if (icut==59) typeCut =  "ge2j_1btag";
      else if (icut==60) typeCut =  "ge2j_2btag";
      else if (icut==61) typeCut =  "ge2j_ge1btag";
      else if (icut==62) typeCut =  "ge2j_ge2btag";
      // ==2 jets
      else if (icut==63) typeCut =  "2j_pretag";
      else if (icut==64) typeCut =  "2j_alltag";
      else if (icut==65) typeCut =  "2j_0btag";
      else if (icut==66) typeCut =  "2j_1btag";
      else if (icut==67) typeCut =  "2j_2btag";
      else if (icut==68) typeCut =  "2j_ge1btag";
      else if (icut==69) typeCut =  "2j_ge2btag";
      // >=1 jet
      else if (icut==70) typeCut =  "ge1j_pretag";
      else if (icut==71) typeCut =  "ge1j_alltag";
      else if (icut==72) typeCut =  "ge1j_0btag";
      else if (icut==73) typeCut =  "ge1j_1btag";
      else if (icut==74) typeCut =  "ge1j_2btag";
      else if (icut==75) typeCut =  "ge1j_ge1btag";
      else if (icut==76) typeCut =  "ge1j_ge2btag";
      // ==1 jet
      else if (icut==77) typeCut =  "1j_pretag";
      else if (icut==78) typeCut =  "1j_alltag";
      else if (icut==79) typeCut =  "1j_0btag";
      else if (icut==80) typeCut =  "1j_1btag";
      else if (icut==81) typeCut =  "1j_2btag";
      else if (icut==82) typeCut =  "1j_ge1btag";
      else if (icut==83) typeCut =  "1j_ge2btag";
	
      TString title2 = typeCut + typeLevel;
      const char* title = title2;

      std::cout<< title<<"EJet       "<<NtotEJet[ilevel][icut]<<" "<<NLEJet[ilevel][icut]<<" "<<NTEJet[ilevel][icut]<<" "<<hFakeYield[0][ilevel][icut]->GetBinContent(1)<<" +/- " <<hFakeYield[0][ilevel][icut]->GetBinError(1) <<" +/- " <<sqrt(hFakeYieldSqSys[0][ilevel][icut]->GetBinContent(1)) <<std::endl;
      fprintf(filestr,"%s %s %d %d %d %7.1f %s %7.1f %s %7.1f\n",
	      (char*)title," EJet       ",(int)NtotEJet[ilevel][icut],
	      (int)NLEJet[ilevel][icut],
	      (int)NTEJet[ilevel][icut],
	      hFakeYield[0][ilevel][icut]->GetBinContent(1)," +/- ",
	      hFakeYield[0][ilevel][icut]->GetBinError(1)," +/- ",
	      sqrt(hFakeYieldSqSys[0][ilevel][icut]->GetBinContent(1)));
    
      std::cout<<title<<"MuJet       "<<NtotMuJet[ilevel][icut]<<" "<<NLMuJet[ilevel][icut]<<" "<<NTMuJet[ilevel][icut]<<" "<<hFakeYield[1][ilevel][icut]->GetBinContent(1)<<" +/- " <<hFakeYield[1][ilevel][icut]->GetBinError(1) <<" +/- " <<sqrt(hFakeYieldSqSys[1][ilevel][icut]->GetBinContent(1)) <<std::endl;
      fprintf(filestr,"%s %s %d %d %d %7.1f %s %7.1f %s %7.1f\n",
	      (char*)title," MuJet       ",(int)NtotMuJet[ilevel][icut],
	      (int)NLMuJet[ilevel][icut],
	      (int)NTMuJet[ilevel][icut],
	      hFakeYield[1][ilevel][icut]->GetBinContent(1)," +/- ",
	      hFakeYield[1][ilevel][icut]->GetBinError(1)," +/- ",
	      sqrt(hFakeYieldSqSys[1][ilevel][icut]->GetBinContent(1)));
    }
  }
  
  fclose (filestr);
    
  delete anafakesemileptonic;
  delete histosObj;
}


