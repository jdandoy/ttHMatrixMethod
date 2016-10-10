#define EffiFakeElec_cxx
//////////////////////////////////////////////////////////////////////
// 
// Author   : Atlas LPNHE Paris
// Creation : 01/10/2015
// Purpose  : base class to fill histograms for efficiencies of fake electrons
// Updated  :
//////////////////////////////////////////////////////////////////////

#include "EffiFakeElec.h"
#include "HistoManagerEffiFakeElec.h"
#include "../doAna/MyEffiFakeElec.h"
#include "../EventStruct/Tree_Nominal_Loose.h"

#include <TStyle.h>
#include <TCanvas.h>
#include <TObjArray.h>
#include <TH1.h>
#include <TH2.h>
#include <TMath.h> 

ClassImp(EffiFakeElec);

// Constructor
EffiFakeElec::EffiFakeElec(MyEffiFakeElec *myanalyse, TObjArray *histosObj) 
{
  myclass         = myanalyse;

  m_Pretag        = false;
  m_Btag          = false;
  m_NoBtag        = false;
  m_Conv          = false;
  m_NoConv        = false;

  for (int i=0;i<3;i++) {
    for (int j=0;j<3;j++) {
      for (int k=0;k<4;k++) {
	m_isTot[i][j][k] = 0;
	m_isFromSignal[i][j][k] = 0;
	m_isFromb[i][j][k] = 0;
	m_isFromConv[i][j][k] = 0;
	m_isFromHadron[i][j][k] = 0;
	m_FracisFromb[i][j][k] = 0;
	m_FracisFromConv[i][j][k] = 0;
	m_FracisFromHadron[i][j][k] = 0;
      }
    }
//std::cout << "Done first step" << std::endl;
  }
  
  m_iso = "";
  m_typeCR = "";
  m_trigger = "";
  //!!m_bweightcut = -0.4434;
  m_bweightcut = 0.645925;
 
  // Histogram manager
  hmanag = new HistoManagerEffiFakeElec(histosObj);
  // various utilities
  myutils = new Utils();
  // utilities to handle MC datasets
  myMCDataSetutils = new MCDataSetUtils();
  //std::cout << " ici avent " <<  std::endl; 
}

// ================================================================
// DESTRUCTOR:
EffiFakeElec::~EffiFakeElec()
{ 
  // Histogram manager
  delete hmanag;
  delete myutils;
  delete myMCDataSetutils;
} 

// ============================================================================
bool EffiFakeElec::execute()
{
  m_weight     = 1.;
  m_weightbtag = 1.;
  float w      = 1.;

  m_print_fakecomposition = false;

  // to define event, run and mc numbers
  m_RunNumber       = myclass->runNumber;  
  m_EventNumber     = myclass->eventNumber;  
  m_mcChannelNumber = myclass->mcChannelNumber;

  // number of electrons
  
   int nel   = myclass->el_pt->size();
  //std::cout << "!!!!!!!!!!! Decision is " << myclass->ejets_2015 << std::endl;
  //int nmu   = myclass->mu_pt->size();
  /*std::cout << " runNumber = " << m_RunNumber
	    << " eventNumber = " << m_EventNumber
	    << " mcChannelNumber = " << m_mcChannelNumber
	    << " nel " << nel
	    << std::endl;*/
    std::cout << "ejets_2016 is " << myclass->ejets_2016 << 
    " ejets_2015 is " << myclass->ejets_2015 << 
    " mujets_2016 is " << myclass->mujets_2016 << 
    " mujets_2015 is " << myclass->mujets_2015 << 
    " ee_2016 is " << myclass->ee_2016 << 
    " ee_2015 is " << myclass->ee_2015 << std::endl;

//  if (myclass->ee_2016 == 1){
//    std::cout << "ee_2016 has " << nel << std::endl;
//  }


   // to check if events pass a e+jets analysis
  //if (myclass->ee_2016 != 1) return true;
  if (myclass->ejets_2016 != 1) return true;
  std::cout << "nel passing is " << nel << std::endl;
  // in case there is no electron or more than one then exit
  if (nel!=1) return true;
  //if(myclass->ejets_2015 == false)  return true;

std::cout << "2" << std::endl;
  // transverse energy/momentum
  m_et      = myclass->el_pt->at(0)/1000.;
  // eta of the cluster
  m_etacl   = myclass->el_cl_eta->at(0); 
  // phi of the cluster
  m_phicl   = myclass->el_phi->at(0);  // should be phi_cl
  // eta of the object (track)
  m_eta     = myclass->el_eta->at(0);  
  // phi of the object (track)
  m_phi     = myclass->el_phi->at(0); 
std::cout << "7" << std::endl;
  // missing transverse momentum (MET)
  m_etmiss  = myclass->met_met/1000.;
std::cout << "7.1" << std::endl;
  // phi of the MET
  m_phimiss = myclass->met_phi;
std::cout << "7.2" << std::endl;
  // transverse mass made of the lepton and the MET
  m_mlnu    = myutils->transMass(m_et,m_phi,m_etmiss,m_phimiss);
std::cout << "7.3" << std::endl;
  // delta phi between the lepton and the MET
  m_dphi    = myutils->CalcdeltaPhi2(m_phi,m_phimiss);
std::cout << "7.4" << std::endl;
  // isolation variables of the lepton
  m_etcone20 = myclass->el_topoetcone20->at(0)/1000.;
std::cout << "7.5" << std::endl;
  m_ptcone20 = myclass->el_ptvarcone20->at(0)/1000.;
  // number of jets
std::cout << "8" << std::endl;
  m_njet = CalcNJet();
  // number of b-jets
  m_nbjet = CalcNbJet();
  // HT
  m_HT = CalcHT();
  // ETmiss/sqrt(HT)
  if (m_HT>0.)
    m_etmissoversqrtht = m_etmiss/sqrt(m_HT);
  else m_etmissoversqrtht = 0.;
  //std::cout << " ETmiss/sqrt(HT) = " << m_etmissoversqrtht << std::endl;
  // boolean to know if electron is from a conversion
  //m_isConv   = myclass->EffiFakeLepton_Lept_isConv;
  
  /*std::cout << " runNumber = " << m_RunNumber
	    << " eventNumber = " << m_EventNumber
	    << " mcChannelNumber = " << m_mcChannelNumber
	    << " nel = " << nel
	    << " pT =  " << m_et
	    << " eta = " << m_eta 
	    << std::endl;*/

  // for Monte Carlo data
  //std::cout << " m_mcChannelNumber = " << m_mcChannelNumber << std::endl;
  std::cout << "9" << std::endl;
  if (m_mcChannelNumber>0) { 
    float Lumi = 1.0;
    float xsect = myMCDataSetutils->XSection(m_mcChannelNumber);
    m_XSectweight = Lumi*xsect;
    //std::cout << " xsection = " << xsect
    //	      << " " << m_XSectweight
    //	      << std::endl;
  }

  std::cout << "11" << std::endl;
  //if (m_njet==0) std::cout << " njet = " << m_njet << std::endl;
  // efficiencies are not derived for 0-jet
  //if (m_njet<1) return true;
  // remove crack
  if ((fabs(m_etacl)>=1.37 && fabs(m_etacl)<=1.52)) return true;
  // only crack
  //if (!(fabs(m_etacl)>=1.37 && fabs(m_etacl)<=1.52)) return true;
  std::cout << "2" << std::endl;
  
  //std::cout << " ici " << std::endl;
  // for Monte Carlo data
  if (m_mcChannelNumber>0) { 
    // remove real leptons
    if (!isTruthMatched()) return true;
    // retrieve MC weight
    GiveMCWeight();
  } /*else {
    if (m_trigger=="HLT_e26_lhmedium_nod0_L1EM20VH"){ 
      m_weight = myclass->PS_HLT_e26_lhmedium_nod0_L1EM20VH;
      m_weightbtag = myclass->PS_HLT_e26_lhmedium_nod0_L1EM20VH;
    }else if (m_trigger=="HLT_e24_lhmedium_nod0_L1EM18VH" ){
      m_weight = myclass->PS_HLT_e24_lhmedium_nod0_L1EM18VH;
      m_weightbtag = myclass->PS_HLT_e24_lhmedium_nod0_L1EM18VH;
    }
  }*/
  std::cout << "3" << std::endl;

  // loof for jets
  LookForLeadingandClosestJet();
std::cout << "pre " << m_typeCR << std::endl;
  // check the control region
  if ((m_typeCR=="nocut") ||   // no cut
      (m_typeCR=="highETmiss"     && m_etmiss>150.) ||  
      (m_typeCR=="lowETmissMTW"   && m_etmiss+m_mlnu<60. && m_mlnu<20.) ||
      (m_typeCR=="lowETmiss20"    && m_etmiss<20.) ||  
      (m_typeCR=="lowETmissMTW20" && m_etmiss<20. && m_mlnu<20.)) {
    
    // check weight to be applied
    if (m_Pretag) {
      w = m_weight;
    } else {
      w = m_weightbtag;
    }

    // in case one selects events with b-tagged jets
    if (m_Btag && m_bWeightmaxb<m_bweightcut) return true;
    // in case one remove events with b-tagged jets
    if (m_NoBtag && m_bWeightmaxb>=m_bweightcut) return true;
    
    // in case one selects events with b-tagged jets
    //if (m_Btag && m_nbjet<1) return true;
    // in case one selects events with conversion
    if (m_Conv && m_isConv!=1) return true;
    // in case one removes events with conversion
    if (m_NoConv && m_isConv==1) return true;
    // fill all histograms
    FillHistos(w);
    // specific to study fake composition
    if (m_print_fakecomposition) Print_FakeComposition();
  }

  return true;
}

// ===========================================================================
void EffiFakeElec::FillHistos(float weight) 
{
  //
  // main method to fill histograms after all seelction
  //
std::cout << "Here" << std::endl;
  //int ibinJet    = -1;
  int ibinEt             = -1;
  int ibinEta            = -1;
  int ibindRClosestJet   = -1;
  int ibinPtLeadingJet   = -1;
  int ibinDPhi           = -1;
  int ibinMET            = -1;
  int ibinMTW            = -1;
  int ibinNbJet          = -1;
  int ibinNJet           = -1;

  bool debug = false;
  
  //std::cout << " trigger0 = " << myclass->HLT_e60_lhmedium << " " << myclass->HLT_e24_lhmedium_iloose_L1EM20VH << " " << myclass->HLT_e24_lhmedium_L1EM18VH << std::endl;
  //std::cout << " trigger1 = " << myclass->el_trigMatch_HLT_e60_lhmedium->at(0) << " " << myclass->el_trigMatch_HLT_e24_lhmedium_iloose_L1EM20VH->at(0) << " " << myclass->el_trigMatch_HLT_e24_lhmedium_L1EM18VH->at(0) << std::endl;
   //Trigger for 2016 electron: HLT_e24_lhmedium_L1EM20VH, HLT_e24_lhtight_nod0_ivarloose, HLT_e60_lhmedium_nod0, HLT_e140_lhloose_nod0
  // trigger matching
  if (m_trigger=="") {
    if (debug)
      std::cout << " trigger = " << m_trigger 
		<< " mcChannelNumber = " << m_mcChannelNumber
		<< " HLT_e24_lhmedium_L1EM20VH = " << myclass->HLT_e24_lhmedium_L1EM20VH
		<< " HLT_e24_lhtight_nod0_ivarloose = " << myclass->HLT_e24_lhtight_nod0_ivarloose
    << " HLT_e60_lhmedium_nod0 = " << myclass->HLT_e60_lhmedium_nod0
    << " HLT_e140_lhloose_nod0 = " << myclass->HLT_e140_lhloose_nod0
    << " HLT_e24_lhmedium_nod0_L1EM18VH = " << myclass->HLT_e24_lhmedium_nod0_L1EM18VH
    << " HLT_e26_lhmedium_nod0_L1EM20VH = " << myclass->HLT_e26_lhmedium_nod0_L1EM20VH
		<< " el_trigMatch_HLT_e24_lhmedium_L1EM20VH = " 
		<< myclass->el_trigMatch_HLT_e24_lhmedium_L1EM20VH->at(0)
		<< " el_trigMatch_HLT_e24_lhtight_nod0_ivarloose = " 
		<< myclass->el_trigMatch_HLT_e24_lhtight_nod0_ivarloose->at(0)
		<< " el_trigMatch_HLT_e60_lhmedium_nod0 = " 
		<< myclass->el_trigMatch_HLT_e60_lhmedium_nod0->at(0)
    << " el_trigMatch_HLT_e140_lhloose_nod0 = "
    << myclass->el_trigMatch_HLT_e140_lhloose_nod0->at(0)
    << " el_trigMatch_HLT_e24_lhmedium_nod0_L1EM18VH = "
    << myclass->el_trigMatch_HLT_e24_lhmedium_nod0_L1EM18VH->at(0)
    << " el_trigMatch_HLT_e26_lhmedium_nod0_L1EM20VH = "
    << myclass->el_trigMatch_HLT_e26_lhmedium_nod0_L1EM20VH->at(0)
		<< " ET = " << m_et 
	      << std::endl;
    // check that event pass these triggers
    if (!myclass->HLT_e24_lhmedium_L1EM20VH && 
	!myclass->HLT_e24_lhtight_nod0_ivarloose && 
	!myclass->HLT_e60_lhmedium_nod0 &&
  !myclass->HLT_e140_lhloose_nod0) return;
    // check that lepton matches these triggers
    if (!myclass->el_trigMatch_HLT_e24_lhmedium_L1EM20VH->at(0) && 
	!myclass->el_trigMatch_HLT_e24_lhtight_nod0_ivarloose->at(0) && 
	!myclass->el_trigMatch_HLT_e60_lhmedium_nod0->at(0) &&
  !myclass->el_trigMatch_HLT_e140_lhloose_nod0->at(0)) return;
    if (debug) std::cout << " apres " << std::endl;
  }

// Trigger option 1 :HLT_e24_lhmedium_L1EM20VH 
  if (m_trigger=="HLT_e24_lhmedium_L1EM20VH") {
    if (debug) {
	     std::cout << " trigger = " << m_trigger 
		  << " HLT_e24_lhmedium_L1EM20VH = " 
		  << myclass->HLT_e24_lhmedium_L1EM20VH
		  << " el_trigMatch_HLT_e24_lhmedium_L1EM20VH = " 
		  << myclass->el_trigMatch_HLT_e24_lhmedium_L1EM20VH->at(0)
		  << " Pt = " << m_et 
		  << std::endl;
    }
    // check that event pass this trigger
    if( !myclass->HLT_e24_lhmedium_L1EM20VH) return;
    // check that lepton matches this trigger
    if ( !myclass->el_trigMatch_HLT_e24_lhmedium_L1EM20VH->at(0)) return;
    // additional pt cut 
    if (m_et>61.) return;
    if (debug) std::cout << " apres " << std::endl;
  }

  // Trigger option 2: HLT_e24_lhtight_nod0_ivarloose
  if (m_trigger=="HLT_e24_lhtight_nod0_ivarloose") {
    if (debug)
      std::cout << " trigger = " << m_trigger 
		<< " HLT_e24_lhtight_nod0_ivarloose = " 
		<< myclass->HLT_e24_lhtight_nod0_ivarloose
		<< " el_trigMatch_HLT_e24_lhtight_nod0_ivarloose = " 
		<< myclass->el_trigMatch_HLT_e24_lhtight_nod0_ivarloose->at(0)
		<< " Pt= " << m_et 
		<< std::endl;
     // check that event pass this trigger
    if (!myclass->HLT_e24_lhtight_nod0_ivarloose) return;
    // check that lepton matches this trigger
    if (!myclass->el_trigMatch_HLT_e24_lhtight_nod0_ivarloose->at(0)) return;
    // additional pt cut 
    if (m_et<=61.) return;
    //std::cout << " et = " << m_et << std::endl;
    if (debug) std::cout << " apres " << std::endl;
  }

    std::cout << "Makes Trig2" << std::endl;
  // Trigger option 3: HLT_e60_lhmedium_nod0
  if (m_trigger=="HLT_e60_lhmedium_nod0") {
    if (debug)
      std::cout << " trigger = " << m_trigger 
		<< " HLT_e60_lhmedium_nod0 = " 
		<< myclass->HLT_e60_lhmedium_nod0
		<< " el_trigMatch_HLT_e60_lhmedium_nod0 = " 
		<< myclass->el_trigMatch_HLT_e60_lhmedium_nod0->at(0)
		<< " Pt = " << m_et 
		<< std::endl;
    // check that event pass this trigger
    if (!myclass->HLT_e60_lhmedium_nod0) return;
    // check that lepton matches this trigger
    if (!myclass->el_trigMatch_HLT_e60_lhmedium_nod0->at(0)) return;
    // additional pt cut 
    if (m_et<=61. || m_et>141.) return;
    //std::cout << " et = " << m_et << std::endl;
    if (debug) std::cout << " apres " << std::endl;
  }
   
  // Trigger option 4: HLT_e140_lhloose_nod0
  if (m_trigger=="HLT_e140_lhloose_nod0") {
    if (debug)
      std::cout << " trigger = " << m_trigger
    << " HLT_e140_lhloose_nod0 = "
    << myclass->HLT_e140_lhloose_nod0
    << " el_trigMatch_HLT_e140_lhloose_nod0 = "
    << myclass->el_trigMatch_HLT_e140_lhloose_nod0->at(0)
    << " Pt = " << m_et
    << std::endl;
    // check that event pass this trigger
    if (!myclass->HLT_e140_lhloose_nod0) return;
    // check that lepton matches this trigger
    if (!myclass->el_trigMatch_HLT_e140_lhloose_nod0->at(0)) return;
    // additional pt cut 
    if (m_et<=141.) return;
    //std::cout << " et = " << m_et << std::endl;
    if (debug) std::cout << " apres " << std::endl;
  }

    std::cout << "Makes Trig4" << std::endl;
  // Trigger option 5:Prescaled : HLT_e24_lhmedium_nod0_L1EM18VH
  if (m_trigger=="HLT_e24_lhmedium_nod0_L1EM18VH") {
//    if (debug)
      std::cout << " trigger = " << m_trigger
    << " HLT_e24_lhmedium_nod0_L1EM18VH = "
    << myclass->HLT_e24_lhmedium_nod0_L1EM18VH
    << " el_trigMatch_HLT_e24_lhmedium_nod0_L1EM18VH = "
    << myclass->el_trigMatch_HLT_e24_lhmedium_nod0_L1EM18VH->at(0)
    << " Pt = " << m_et
    << std::endl;
    // check that event pass this trigger
    if (!myclass->HLT_e24_lhmedium_nod0_L1EM18VH) return;
std::cout << "passes trigger" << std::endl;
    // check that lepton matches this trigger
    if (!myclass->el_trigMatch_HLT_e24_lhmedium_nod0_L1EM18VH->at(0)) return;
std::cout << "is matched" << std::endl;
    // additional pt cut 
//    if (m_et<=61. || m_et>141.) return; // Not sure about this one
    //std::cout << " et = " << m_et << std::endl;
    if (debug) std::cout << " apres " << std::endl;
  }

    std::cout << "Makes Trig5" << std::endl;
  // Trigger option 6:Prescaled : HLT_e26_lhmedium_nod0_L1EM20VH  
  if (m_trigger=="HLT_e26_lhmedium_nod0_L1EM20VH") {
    if (debug)
      std::cout << " trigger = " << m_trigger
    << " HLT_e26_lhmedium_nod0_L1EM20VH = "
    << myclass->HLT_e26_lhmedium_nod0_L1EM20VH
    << " el_trigMatch_HLT_e26_lhmedium_nod0_L1EM20VH = "
    << myclass->el_trigMatch_HLT_e26_lhmedium_nod0_L1EM20VH->at(0)
    << " Pt = " << m_et
    << std::endl;
    // check that event pass this trigger
    if (!myclass->HLT_e26_lhmedium_nod0_L1EM20VH) return;
    // check that lepton matches this trigger
    if (!myclass->el_trigMatch_HLT_e26_lhmedium_nod0_L1EM20VH->at(0)) return;
    // additional pt cut 
    if (m_et<=61. || m_et>141.) return; // Not sure about this one
    //std::cout << " et = " << m_et << std::endl;
    if (debug) std::cout << " apres " << std::endl;
  }

  //if (std::isnan(weight) || std::isinf(weight)) {
  //myclass->EffiFakeLepton_SF_Wjets = 1.;
   
  //weight = myclass->EffiFakeLepton_SF_Elec*myclass->EffiFakeLepton_SF_Muon*myclass->EffiFakeLepton_SF_Trigger*myclass->EffiFakeLepton_SF_PU*myclass->EffiFakeLepton_SF_ZVertex;
    /*std::cout << " mychannel = " << m_channel 
      //<< " " << ilevel 
	      << " weight = " << weight
	      << " njet = " << m_njet
	      << " " << myclass->EffiFakeLepton_eventNumber 
	      << " ETmiss = " << m_etmiss 
	      << " hfor = " << myclass->EffiFakeLepton_top_hfor_type
	      << " mcweight = " << myclass->EffiFakeLepton_mcevt_weight 
	      << " SF = " << myclass->EffiFakeLepton_SF_AllPretag 
	      << " " << myclass->EffiFakeLepton_SF_AllBtag 
	      << " SF Ele = " << myclass->EffiFakeLepton_SF_Elec
	      << " SF Muon = " << myclass->EffiFakeLepton_SF_Muon
	      << " SF Btag = " << myclass->EffiFakeLepton_SF_Btag
	      << " SF Wj = " << myclass->EffiFakeLepton_SF_Wjets
	      << " SF Wjshape = " << myclass->EffiFakeLepton_SF_WjetsShape
	      << " SF Trigger = " << myclass->EffiFakeLepton_SF_Trigger
	      << " SF PU = " << myclass->EffiFakeLepton_SF_PU
	      << " SF ZV = " << myclass->EffiFakeLepton_SF_ZVertex
	      << std::endl;*/
  //  }
    std::cout << "Makes 0.0 " << std::endl;
 
  if (m_print_fakecomposition) {
    if (!isLoose()) return;;
    Fill_FakeComposition();
    return;
  }

  std::cout << "Makes 0.1 " << std::endl;
  // loop on PID
  for (int ipid=0;ipid<2;ipid++) {
    if (ipid==0 && !isLoose()) continue;
    if (ipid==1 && !isTight()) continue; 

    // jet bin
    std::cout << "Makes 1 " << std::endl;
    for (int ibinJet=0;ibinJet<=7;ibinJet++) {
      //std::cout << "Starting to loop of ibinJet" << ibinJet << std::endl;
      bool doesItPass = false;
      if (ibinJet==0 && m_njet==0) doesItPass = true; 
      if (ibinJet==1 && m_njet==1) doesItPass = true; 
      if (ibinJet==2 && m_njet>=1)  doesItPass = true;
      if (ibinJet==3 && m_njet>=2) doesItPass = true;
      if (ibinJet==4 && (m_njet==2 || m_njet==3)) doesItPass = true; 
      if (ibinJet==5 && m_njet>=4) doesItPass = true;  
      if (ibinJet==6 && m_njet>=5) doesItPass = true;
      if (ibinJet==7 && m_njet>=6) doesItPass = true; 

      if (!doesItPass) continue;
      std::cout << "Makes 2 " << std::endl;

//      if (ibinJet==0 && m_njet!=0) continue; 
//      if (ibinJet==1 && m_njet!=1) continue; 
//      if (ibinJet==2 && m_njet<1) continue;
//      if (ibinJet==3 && m_njet<2) continue;
//      if (ibinJet==4 && (m_njet!=2 && m_njet!=3)) continue; 
//      if (ibinJet==5 && m_njet<4) continue;  
//      if (ibinJet==6 && m_njet<5) continue;
//      if (ibinJet==7 && m_njet<6) continue; 
      
      //if (ibinJet==2) std::cout << " ici " << ipid << std::endl;

      hmanag->hETmiss[ipid][ibinJet]->Fill(m_etmiss,weight);
      std::cout << "Filling !!!!!!!! value: " << m_etmiss << " with weight " << weight << std::endl;
      hmanag->hMTW[ipid][ibinJet]->Fill(m_mlnu,weight);
      hmanag->hETmissOverSqrtHT[ipid][ibinJet]->Fill(m_etmissoversqrtht,weight);
      
      // in Et bins
      ibinEt = WhichIndexEt(m_et);
      hmanag->hETmiss_vsEt[ipid][ibinJet][ibinEt]->Fill(m_etmiss,weight);
      hmanag->hETmissOverSqrtHT_vsEt[ipid][ibinJet][ibinEt]->Fill(m_etmissoversqrtht,weight);
      // add another bin
      if (m_et>60.) {
	hmanag->hETmiss_vsEt[ipid][ibinJet][10]->Fill(m_etmiss,weight);
	hmanag->hETmissOverSqrtHT_vsEt[ipid][ibinJet][10]->Fill(m_etmissoversqrtht,weight);
      }
      if (m_et>80.) {
	hmanag->hETmiss_vsEt[ipid][ibinJet][11]->Fill(m_etmiss,weight);
	hmanag->hETmissOverSqrtHT_vsEt[ipid][ibinJet][11]->Fill(m_etmissoversqrtht,weight);
      }

      // in Eta bins
      ibinEta = WhichIndexEta(m_etacl);
      hmanag->hETmiss_vsEta[ipid][ibinJet][ibinEta]->Fill(m_etmiss,weight);
      hmanag->hETmissOverSqrtHT_vsEta[ipid][ibinJet][ibinEta]->Fill(m_etmissoversqrtht,weight);
            
      // in dRClosestJet bins
      ibindRClosestJet = WhichIndexdRClosestJet(m_dRmin);
      hmanag->hETmiss_vsdRClosestJet[ipid][ibinJet][ibindRClosestJet]->Fill(m_etmiss,weight);
      hmanag->hETmissOverSqrtHT_vsdRClosestJet[ipid][ibinJet][ibindRClosestJet]->Fill(m_etmissoversqrtht,weight);
      
      // in PtLeadingJet bins
      ibinPtLeadingJet = WhichIndexPtLeadingJet(m_ptlead);
      hmanag->hETmiss_vsPtLeadingJet[ipid][ibinJet][ibinPtLeadingJet]->Fill(m_etmiss,weight);
      hmanag->hETmissOverSqrtHT_vsPtLeadingJet[ipid][ibinJet][ibinPtLeadingJet]->Fill(m_etmissoversqrtht,weight);
      
      // in DPhi bins
      ibinDPhi = WhichIndexDPhi(m_dphi);
      hmanag->hETmiss_vsDPhi[ipid][ibinJet][ibinDPhi]->Fill(m_etmiss,weight);
      hmanag->hETmissOverSqrtHT_vsDPhi[ipid][ibinJet][ibinDPhi]->Fill(m_etmissoversqrtht,weight);
      
      // in MET bins
      ibinMET = WhichIndexMET(m_etmiss);
      hmanag->hETmiss_vsMET[ipid][ibinJet][ibinMET]->Fill(m_etmiss,weight);
      hmanag->hETmissOverSqrtHT_vsMET[ipid][ibinJet][ibinMET]->Fill(m_etmissoversqrtht,weight);

      // in MTW bins
      ibinMTW = WhichIndexMTW(m_mlnu);
      hmanag->hETmiss_vsMTW[ipid][ibinJet][ibinMTW]->Fill(m_etmiss,weight);
      hmanag->hETmissOverSqrtHT_vsMTW[ipid][ibinJet][ibinMTW]->Fill(m_etmissoversqrtht,weight);

      // in NJet bins
      ibinNJet = WhichIndexNJet(m_njet); //ibinNJet is BinNJet2
	 				 //ibinJet is BinNJet
      //std::cout << " ibinNJet " << ibinNJet << " " << m_njet << std::endl;
      hmanag->hETmiss_vsNJet[ipid][ibinJet][ibinNJet]->Fill(m_etmiss,weight);
      hmanag->hETmissOverSqrtHT_vsNJet[ipid][ibinJet][ibinNJet]->Fill(m_etmissoversqrtht,weight);
      //Fill Histograms
      // in NbJet bins
      for (int ibinNbJet=0;ibinNbJet<=5;ibinNbJet++) {
//        std::cout << "Starting to loop of ibinNbJet" << ibinNbJet << std::endl;
        bool doesItPass = false;
        if (ibinNbJet==0 && m_nbjet==0) doesItPass = true; 
        if (ibinNbJet==1 && m_nbjet==1) doesItPass = true; 
        if (ibinNbJet==2 && m_nbjet>=1)  doesItPass = true;
        if (ibinNbJet==3 && m_nbjet>=2) doesItPass = true;
        if (ibinNbJet==4 && m_nbjet>=3) doesItPass = true; 
        if (ibinNbJet==5 && m_nbjet>=4) doesItPass = true;  

        if (!doesItPass) continue;


//cout << "ijet/bjet is " << m_njet << ":" << ibinJet << " / " << m_nbjet << ":" << ibinNbJet << endl;
        hmanag->hETmiss_vsNbJet[ipid][ibinJet][ibinNbJet]->Fill(m_etmiss,weight);
        hmanag->hMTW_vsNbJet[ipid][ibinJet][ibinNbJet]->Fill(m_mlnu,weight);
        hmanag->hETmissOverSqrtHT_vsNbJet[ipid][ibinJet][ibinNbJet]->Fill(m_etmissoversqrtht,weight);
      }

//old method      ibinNbJet = WhichIndexNbJet(m_nbjet);
//old method      hmanag->hETmiss_vsNbJet[ipid][ibinJet][ibinNbJet]->Fill(m_etmiss,weight);
//old method      hmanag->hMTW_vsNbJet[ipid][ibinJet][ibinNbJet]->Fill(m_mlnu,weight);
//old method      hmanag->hETmissOverSqrtHT_vsNbJet[ipid][ibinJet][ibinNbJet]->Fill(m_etmissoversqrtht,weight);
    }
  }
}

// ===========================================================================
bool EffiFakeElec::isLoose() 
{
  //
  // method to check if electron passes Loose selection
  //

  return true;
}

// ===========================================================================
bool EffiFakeElec::isTight() 
{
  // check if object pass Tight requirements
  bool iselecTight = false; 

  if (m_iso == "Std") {
    iselecTight = myclass->el_isTight->at(0);
  } else {
    bool iselecPID = myclass->el_LHTight->at(0);
    bool isIso = m_ptcone20/m_et<0.06 && m_etcone20/m_et<0.06;
    //std::cout << " iselecPID = " << iselecPID << " " << isIso << " " << m_ptcone20/m_et << " " << m_etcone20/m_et << std::endl;
    iselecTight = iselecPID & isIso;
  }

  return iselecTight;
}

/*
// ===============================================================
bool EffiFakeElec::isTrueElecMatch(int Type, int Typebkg, 
				   int Originbkg, int choice)
{
  //
  // check if a reconstructed electron matches a true one
  //

  bool truthMatchOK = false;
  bool isElectronFromb = false;
  bool isElectronFromConversion = false;
  bool isSignalElectron = false;
  bool isHadron = false;
  
  //std::cout << " Type= " << Type << " " << Typebkg << " " << Originbkg << std::endl;
  // b->e
  if (Type == MCTruthPartClassifier::NonIsoElectron ) isElectronFromb = true;
  
  // conversions
  if (Type == MCTruthPartClassifier::BkgElectron ) {
    //if (Originbkg == MCTruthPartClassifier::PhotonConv) truthMatchOK = true;
    //if (Originbkg == MCTruthPartClassifier::DalitzDec) truthMatchOK = true;
    isElectronFromConversion = true;
    if (Originbkg == MCTruthPartClassifier::WBoson) isElectronFromConversion = false;
    else if (Originbkg == MCTruthPartClassifier::ZBoson) isElectronFromConversion = false;
    else if (Typebkg == MCTruthPartClassifier::NonIsoPhoton && 
    Originbkg == MCTruthPartClassifier::FSRPhot) isElectronFromConversion = false;    }
  
  
  // if it is isolated electron it is ok (type=2)
  if (Type == MCTruthPartClassifier::IsoElectron ) isSignalElectron = true;
  // in case it is a "BkgElectron" (type=4)
  else if (Type == MCTruthPartClassifier::BkgElectron ) {
    if (Originbkg == MCTruthPartClassifier::WBoson ||
	Originbkg == MCTruthPartClassifier::ZBoson) isSignalElectron = true;
    else if (Typebkg == MCTruthPartClassifier::NonIsoPhoton && 
	     Originbkg == MCTruthPartClassifier::FSRPhot) isSignalElectron = true;
  }
    
  // QCD
  if (!isElectronFromb && !isElectronFromConversion && !isSignalElectron)
    isHadron = true;


  // select signal electrons
  if (choice==1) truthMatchOK = isSignalElectron;
  // select electrons from b
  if (choice==2) truthMatchOK = isElectronFromb;
  // select electrons from conversion
  if (choice==3) truthMatchOK = isElectronFromConversion;
  // select hadrons
  if (choice==4) truthMatchOK = isHadron;
  
  return truthMatchOK;
  } */


// ================================================================
void EffiFakeElec::GiveMCWeight()
{
  //
  // method to retrieve weights to be applied to MC
  //

  m_weight = myclass->weight_mc;
  m_weight *= myclass->weight_pileup*myclass->weight_leptonSF;
  /*if (m_mcChannelNumber>363100 && m_mcChannelNumber<363500){
    m_weight *= myclass->weight_sherpa_22_vjets;
    }*/
  m_weightbtag = m_weight*myclass->weight_bTagSF_77;
  return;
}

// ==============================================================
int EffiFakeElec::CalcNJet()
{
  //
  // method to get the number of bjets
  //

  int njet = 0;
  // loop on jets
  for (unsigned int ijet=0;ijet<myclass->jet_pt->size();ijet++) {
    float etajet  = myclass->jet_eta->at(ijet);
    if (fabs(etajet)>2.5) continue;
    njet++;
  }

  return njet;
}

// ==============================================================
int EffiFakeElec::CalcNbJet()
{
  //
  // method to get the number of bjets
  //

  int nbjet = 0;
  // loop on jets
  for (unsigned int ijet=0;ijet<myclass->jet_pt->size();ijet++) {
    float etajet  = myclass->jet_eta->at(ijet);
    if (fabs(etajet)>2.5) continue;
    float bweight = myclass->jet_mv2c10->at(ijet);
    if (bweight>m_bweightcut) nbjet++;
  }

  return nbjet;
}

// ==============================================================
void EffiFakeElec::LookForLeadingandClosestJet()
{
  //
  // find the leading pT jet and the jet closest to the lepton
  //

  float ptjet       = -9999.;
  float ptjetmax    = -9999.;
  float etajet      = -9999.;
  float phijet      = -9999.;
  float dR          = -9999.;
  float dRmin       = 9999.;
  float bWeight     = -9999.;
  float bWeightmax  = -9999.;

  m_ptlead      = 0.;
  m_dRlead      = 0.;
  m_dRmin       = 0.;
  m_ptmin       = 0.;
  m_ptdRmin     = 0.;  
  m_bWeight     = -9999.;
  m_dRmaxb      = 0.;
  m_bWeightmaxb = -9999.;

  // eta/phi of the lepton
  //float et  = myclass->EffiFakeLepton_Lept_pt;
  float eta = m_eta;
  float phi = m_phi;

  // loop on all jets
  //std::cout << " njet = " << m_njet << " " << myclass->jet_n << " " << myclass->jet_nCentral << std::endl;
  for (unsigned int ijet=0;ijet<myclass->jet_pt->size();ijet++) {
    // check if jet is good
    //if (!myclass->EffiFakeLepton_isGoodJet->at(ijet)) continue;
    etajet  = myclass->jet_eta->at(ijet);
    /*std::cout << " ijet = " << ijet 
	      << " pt = " << myclass->jet_pt->at(ijet)/1000.
	      << " eta = " << myclass->jet_eta->at(ijet)
	      << " isCentral = " << myclass->jet_isCentral->at(ijet) 
	      << " bw = " << myclass->jet_mv2c20->at(ijet) 
	      << " isb77 = " << myclass->jet_isbtagged_77->at(ijet) 
	      << std::endl;*/
    if (fabs(etajet)>2.5) continue;
    ptjet   = myclass->jet_pt->at(ijet)/1000.;
    phijet  = myclass->jet_phi->at(ijet);
    dR      = myutils->deltaR(etajet,eta,phijet,phi);
    bWeight = myclass->jet_mv2c10->at(ijet);
    //if (fabs(etajet)>2.5) continue;
    //std::cout << " eta = " << etajet << " " << ptjet << std::endl;

    // look for leading jet
    if (ptjet>ptjetmax) {
      ptjetmax = ptjet;
      m_ptlead = ptjet;
      //std::cout << " eta lead = " << etajet << " " << ptjet << std::endl;
      m_dRlead = dR;
    }
    // look for closest jet
    if (dR<dRmin) {
      dRmin = dR;
      m_dRmin = dR;
      m_ptmin = ptjet;
      if (dR>0.) m_ptdRmin = ptjet/dR;
    }
    // look for jet with highest b-weight
    if (bWeight>bWeightmax) {
      bWeightmax = bWeight;
      m_dRmaxb = dR;
      m_bWeightmaxb = bWeight;
    }
  }
  /*std::cout << " pT lead = " << m_ptlead 
	    << " " << myclass->leadingCentralJetpT/1000.
	    << " " << myclass->leadingJetpT/1000.
	    << std::endl;
  */
}

// ==============================================================
double EffiFakeElec::CalcHT()
{
  //
  // calc sum of pt of leptons and jets
  //

  // get pt of the lepton
  double ht = m_et;

  // loop on jets
  for (unsigned int ijet=0;ijet<myclass->jet_pt->size();ijet++) {
    float etajet = myclass->jet_eta->at(ijet);
    if (fabs(etajet)>2.5) continue;
    float ptjet = myclass->jet_pt->at(ijet)/1000.;
    ht += ptjet;
  }

  return ht;
}
// ==============================================================
int EffiFakeElec::WhichIndexPt(float Pt)
{
  int index = -1;

   if (Pt>=25 && Pt<30.) index=0;
   else if (Pt<35.)  index=1;
   else if (Pt<40.)  index=2;
   else if (Pt<45.)  index=3;
   else if (Pt<50.)  index=4;
   else if (Pt<55.)  index=5;
   else if (Pt<60.)  index=6;
   else if (Pt<80.)  index=7;
   else if (Pt<120.) index=8;
   else index=9;

   return index;
}

// ==============================================================

// ==============================================================
int EffiFakeElec::WhichIndexEta(float eta)
{
  int index = -1;

  float eta2 = fabs(eta);

  if ( eta2 > 0. && eta2 <= 0.1 ) {
    index = 0;
  } else if ( eta2 > 0.1 && eta2 <= 0.6 ) {
    index = 1;
  } else if ( eta2 > 0.6 && eta2 <= 0.8 ) {
    index = 2;
  } else if ( eta2 > 0.8 && eta2 <= 1.15 ) {
    index = 3;
  } else if ( eta2 > 1.15 && eta2 <= 1.37 ) {
    index = 4;
  } else if ( eta2 > 1.37 && eta2 <= 1.52 ) {
    index = 5;
  } else if ( eta2 > 1.52 && eta2 <= 1.81 ) {
    index = 6;
  } else if ( eta2 > 1.81 && eta2 <= 2.01 ) {
    index = 7;
  } else if ( eta2 > 2.01 && eta2 <= 2.37 ) {
    index = 8;
  } else {
    index = 9;
  } 

  return index;
}

// ==============================================================
int EffiFakeElec::WhichIndexEt(float Et)
{
  int index = -1;
  
  if (Et>=25 && Et<30.) index=0;
  else if (Et<35.)  index=1;
  else if (Et<40.)  index=2;
  else if (Et<45.)  index=3;
  else if (Et<50.)  index=4;
  else if (Et<55.)  index=5;
  else if (Et<60.)  index=6;
  else if (Et<80.)  index=7;
  else if (Et<120.) index=8;
  else index=9;

  return index;
} 

// ==============================================================
int EffiFakeElec::WhichIndexdRClosestJet(float dRClosestJet)
{
  int index = -1;

  if (dRClosestJet<0.6) index=0;
  else if (dRClosestJet<0.8) index=1;
  else if (dRClosestJet<1.0) index=2;
  else if (dRClosestJet<1.5) index=3;
  else if (dRClosestJet<2.0) index=4;
  else index=5;

  return index;
} 

// ==============================================================
int EffiFakeElec::WhichIndexPtLeadingJet(float PtJet)
{
  int index = -1;

  if (PtJet<50.) index=0;
  else if (PtJet<75.)  index=1;
  else if (PtJet<100.) index=2;
  else if (PtJet<150.) index=3;
  else index=4;

  return index;
} 

// ==============================================================
int EffiFakeElec::WhichIndexDPhi(float dphi)
{
  int index = -1;

  float dphi2 = fabs(dphi);
  if (dphi2<0.1) index=0;
  else if (dphi2<0.2)  index=1;
  else if (dphi2<0.3)  index=2;
  else if (dphi2<0.4)  index=3;
  else if (dphi2<0.5)  index=4;
  else if (dphi2<0.75) index=5;
  else if (dphi2<1.0)  index=6;
  else if (dphi2<1.25) index=7;
  else if (dphi2<1.5)  index=8;
  else if (dphi2<1.75) index=9;
  else if (dphi2<2.0)  index=10;
  else if (dphi2<2.5)  index=11;
  else index=12;

  return index;
} 

// ==============================================================
int EffiFakeElec::WhichIndexMET(float met)
{
  int index = -1;

  if (met<10.0) index=0;
  else if (met<20.)  index=1;
  else if (met<30.)  index=2;
  else if (met<40.)  index=3;
  else if (met<60.)  index=4;
  else if (met<100.) index=5;
  else if (met<150.) index=6;
  else if (met<200.) index=7;
  else index=8;

  return index;
} 

// ==============================================================
int EffiFakeElec::WhichIndexMTW(float mtw)
{
  int index = -1;

  if (mtw<10.0) index=0;
  else if (mtw<20.)  index=1;
  else if (mtw<30.)  index=2;
  else if (mtw<40.)  index=3;
  else if (mtw<60.)  index=4;
  else if (mtw<100.) index=5;
  else if (mtw<150.) index=6;
  else if (mtw<200.) index=7;
  else index=8;

  return index;
}

// ==============================================================
int EffiFakeElec::WhichIndexNJet(int njet)
{
  int index = -1;

  if (njet==0) {
    index = 0;
  } else if (njet==1) {
    index = 1;
  } else if (njet==2) {
    index = 2;
  } else if (njet==3) {
    index = 3;
  } else if (njet>=4) {   ///THIS IS A PROBLEM
    index = 4;
  } else if (njet>=5) {
    index = 5;
  } else if (njet>=6) {
    index = 6;
  }

  return index;
}

// ==============================================================
int EffiFakeElec::WhichIndexNbJet(int nbjet)
{
  int index = -1;

  if (nbjet==0) {
    index = 0;
  } else if (nbjet==1) {
    index = 1;
  } else if (nbjet>=1) {
    index = 2;
  } else if (nbjet>=2) {
    index = 3;
  } else if (nbjet>=3) {
    index = 4;
  } else if (nbjet>=4) {
    index = 5;
  }

  return index;
}


// ==================================================================
void EffiFakeElec::Print_FakeComposition() 
{
  //
  //
  //

  for (int i=0;i<3;i++) {
    for (int j=0;j<3;j++) {
      for (int k=0;k<4;k++) {
	m_FracisFromb[i][j][k] = 100.*m_isFromb[i][j][k]/(m_isFromb[i][j][k]+m_isFromConv[i][j][k]+m_isFromHadron[i][j][k]);
	m_FracisFromConv[i][j][k] = 100.*m_isFromConv[i][j][k]/(m_isFromb[i][j][k]+m_isFromConv[i][j][k]+m_isFromHadron[i][j][k]);
	m_FracisFromHadron[i][j][k] = 100.*m_isFromHadron[i][j][k]/(m_isFromb[i][j][k]+m_isFromConv[i][j][k]+m_isFromHadron[i][j][k]);
      }
    }
  } 
    
  //std::cout << " ***************************** " << std::endl;
  for (int i=1;i<2;i++) {
    //if (i==0) std::cout << " !=1 ";
    //if (i==1) std::cout << " \\ge 1 ";
    //if (i==2) std::cout << " \\ge 2 ";
    for (int j=0;j<3;j++) {
      if (j==0)   std::cout << "        & all      "; 
      if (j==1) {
	if (i==0) std::cout << " all    & 25-60    ";
	if (i==1) std::cout << " \\ge 1 & 25-60    ";
	if (i==2) std::cout << " $\\ge 2$ & 25-60    ";
      }
      if (j==2)   std::cout << "        & $\\ge 60$ ";
      
      //std::cout << " toto " << m_isTot[i][j][0];
      std::cout   // << " " << m_isFromSignal[i][j][0]
	<< " & " << m_isFromb[i][j][0]
	<< " & " << m_isFromConv[i][j][0]
	<< " & " << m_isFromHadron[i][j][0]
	//<< " & : " << m_isTot[i][j][1]
	//<< " " << m_isFromSignal[i][j][1]
	<< " & " << m_isFromb[i][j][1]
	<< " & " << m_isFromConv[i][j][1]
	<< " & " << m_isFromHadron[i][j][1]
	//     << " & : " << m_isTot[i][j][2]
	//     << " " << m_isFromSignal[i][j][2]
	<< " & " << m_isFromb[i][j][2]
	<< " & " << m_isFromConv[i][j][2]
	<< " & " << m_isFromHadron[i][j][2]
	//     << " & : " << m_isTot[i][j][3]
	//     << " " << m_isFromSignal[i][j][3]
	<< " & " << m_isFromb[i][j][3]
	<< " & " << m_isFromConv[i][j][3]
	<< " & " << m_isFromHadron[i][j][3]
	<< " \\\\ " << std::endl;
      
      std::cout    //<< " " << m_isFromSignal[i][j][0]
	<< "        &           & (" << m_FracisFromb[i][j][0]
	<< ") & (" << m_FracisFromConv[i][j][0]
	<< ") & (" << m_FracisFromHadron[i][j][0]
	//<< " & : " << m_isTot[i][j][1]
	//     << " " << m_isFromSignal[i][j][1]
	<< ") & (" << m_FracisFromb[i][j][1]
	<< ") & (" << m_FracisFromConv[i][j][1]
	<< ") & (" << m_FracisFromHadron[i][j][1]
	//     << " & : " << m_isTot[i][j][2]
	//     << " " << m_isFromSignal[i][j][2]
	<< ") & (" << m_FracisFromb[i][j][2]
	<< ") & (" << m_FracisFromConv[i][j][2]
	<< ") & (" << m_FracisFromHadron[i][j][2]
	//     << " & : " << m_isTot[i][j][3]
	//     << " " << m_isFromSignal[i][j][3]
	<< ") & (" << m_FracisFromb[i][j][3]
	<< ") & (" << m_FracisFromConv[i][j][3]
	<< ") & (" << m_FracisFromHadron[i][j][3];
      if (j==2) std::cout << ") \\\\ \\hline" << std::endl;
      else std::cout << ") \\\\" << std::endl;
    }
  }  
}

// =========================================================
void EffiFakeElec::Fill_FakeComposition()
{
  /*
  // jet bin
  for (int ibinJet=0;ibinJet<=2;ibinJet++) {
    if (ibinJet==0 && m_njet!=1) continue; 
    if (ibinJet==1 && m_njet<1) continue;
    if (ibinJet==2 && m_njet<2) continue;  
    
    // et bin
    for (int iet=0;iet<3;iet++) {
      if (iet==1 && m_et>60.) continue;
      if (iet==2 && m_et<60.) continue;
      
      bool isFromSignal = isTrueElecMatch(myclass->EffiFakeLepton_Lept_mcType, myclass->EffiFakeLepton_Lept_mcTypebkg, myclass->EffiFakeLepton_Lept_mcOriginbkg,1);
      bool isFromb = isTrueElecMatch(myclass->EffiFakeLepton_Lept_mcType, myclass->EffiFakeLepton_Lept_mcTypebkg, myclass->EffiFakeLepton_Lept_mcOriginbkg,2) ;
      bool isFromConv = isTrueElecMatch(myclass->EffiFakeLepton_Lept_mcType, myclass->EffiFakeLepton_Lept_mcTypebkg, myclass->EffiFakeLepton_Lept_mcOriginbkg,3);
      bool isFromHadron = isTrueElecMatch(myclass->EffiFakeLepton_Lept_mcType, myclass->EffiFakeLepton_Lept_mcTypebkg, myclass->EffiFakeLepton_Lept_mcOriginbkg,4);
    
      // type bin
      for (int itype=0;itype<4;itype++) {
	//std::cout << " itype = " << itype << " " << m_bWeightmaxb
	//  << " " << isConv << std::endl; 
	if (itype==1 && m_bWeightmaxb<0.7892) continue;
	if (itype==2 && m_isConv!=1) continue;
	if (itype==3 && (m_bWeightmaxb>0.7892 || m_isConv==1)) continue;
	
	//std::cout << " itype = " << itype << std::endl;
	m_isTot[ibinJet][iet][itype]++;
	if (ibinJet==0 && iet==0 && itype==0 && isFromb) std::cout << " njet = " << m_njet << std::endl;
	if (isFromSignal) m_isFromSignal[ibinJet][iet][itype]++;
	if (isFromb) m_isFromb[ibinJet][iet][itype]++;
	if (isFromConv) m_isFromConv[ibinJet][iet][itype]++;
	if (isFromHadron) m_isFromHadron[ibinJet][iet][itype]++;
      }
      
      //if (ipid==0)   
	//std::cout << " etmiss = " << m_etmiss
	//<< " " << m_et << " " << m_eta
	//<< " mcmatch = " << myclass->EffiFakeLepton_Lept_mcMatch 
	//<< " isFromSignal = " << isFromSignal
	//<< " isFromb = " << isFromb
	//<< " isFromConv = " << isFromConv
	//<< " isFromHadron = " << isFromHadron
	//<<std::endl;
      
    }
  }
*/
  return;
}
/*
// ==============================================================
bool EffiFakeElec::isTruthMatched()
{
  
  // type 
  int type   = myclass->el_true_type->at(0);
  // origin 
  int origin = myclass->el_true_origin->at(0);
  // origin Bkg
  int originbkg = myclass->el_true_originbkg->at(0);
  // pdg value
  int pdg = myclass->el_true_pdg->at(0);

  //std::cout << " type = " << type << " origin = " << origin << " originbkg = " << originbkg << " pdg = " << pdg << std::endl;

  if (pdg!=11) return false;
  if (type==2) return true; // Isolated electron
  // Capture electrons from Z/W->tau(tau)->e(e) decays 
  if (type==3 && origin==9) return true;
  // Capture electrons from Photon conversion
  if (type==4 && origin==5) {
    if (originbkg==9 || // Tau lepton
	originbkg==12 || // W boson
	originbkg==13) return true; // Z boson
  }
  return false;

}
*/
// ==============================================================
bool EffiFakeElec::isTruthMatched()
{
  
  // type 
  int type   = myclass->el_true_type->at(0);
  // origin 
  int origin = myclass->el_true_origin->at(0);
  // origin Bkg
  int originbkg = myclass->el_true_originbkg->at(0);
  // pdg value
//!!  int pdg = myclass->el_true_pdg->at(0);

  //std::cout << " type = " << type << " origin = " << origin << " originbkg = " << originbkg << " pdg = " << pdg << std::endl;

  //if (pdg!=11) return false;
  // check if it is IsolatedElectron
  if (type==2 && (origin==10 ||  // from top
		  origin==12 ||  // from W
		  origin==13 ||  // from Z
		  origin==14)    // from Higgs
      ) return true; // Isolated electron

  // Capture electrons from Z/W->tau(tau)->e(e) decays 
  //if (type==3 && origin==9) return true;
  // Capture electrons from Photon conversion
  if (type==4 && origin==5) { // BkgElectron and origin=PhotonConversion
    if (originbkg==10 || // from top
	  originbkg==12 || // from W
	  originbkg==13 || // from Z
	  originbkg==14)   // from Higgs
      return true; 
      }
  return false;

}
