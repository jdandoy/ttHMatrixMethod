#define EffiFakeMuon_cxx
//////////////////////////////////////////////////////////////////////
// 
// Author   : Atlas LPNHE Paris
// Creation : 01/10/2015
// Purpose  : base class to fill histograms for efficiencies of fake muons
// Updated  :
//////////////////////////////////////////////////////////////////////

#include "EffiFakeMuon.h"
#include "HistoManagerEffiFakeMuon.h"
#include "../doAna/MyEffiFakeMuon.h"
#include "../EventStruct/Tree_Nominal_Loose.h"

#include <TStyle.h>
#include <TCanvas.h>
#include <TObjArray.h>
#include <TH1.h>
#include <TH2.h>
#include <TMath.h> 

ClassImp(EffiFakeMuon);

// Constructor
EffiFakeMuon::EffiFakeMuon(MyEffiFakeMuon *myanalyse, TObjArray *histosObj) 
{
  myclass         = myanalyse;

  m_Pretag        = false;
  m_Btag          = false;
  m_NoBtag        = false;

  for (int i=0;i<3;i++) {
    for (int j=0;j<3;j++) {
      for (int k=0;k<4;k++) {
	m_isTot[i][j][k] = 0;
	m_isFromSignal[i][j][k] = 0;
	m_isFromb[i][j][k] = 0;
	m_isFromHadron[i][j][k] = 0;
	m_FracisFromb[i][j][k] = 0;
	m_FracisFromHadron[i][j][k] = 0;
      }
    }
  }
  
  m_trigger = "";
  m_iso = "";
  m_typeCR = "";
  //m_bweightcut = -0.4434;
  m_bweightcut = 0.645925;

  // Histogram manager
  hmanag = new HistoManagerEffiFakeMuon(histosObj);
  // various utilities
  myutils = new Utils();
  // utilities to handle MC datasets
  myMCDataSetutils = new MCDataSetUtils();
    
}

// ================================================================
// DESTRUCTOR:
EffiFakeMuon::~EffiFakeMuon()
{ 
  // Histogram manager
  delete hmanag;
  delete myutils;
  delete myMCDataSetutils;
} 

// ============================================================================
bool EffiFakeMuon::execute()
{
  m_weight     = 1.;
  m_weightbtag = 1.;
  float w      = 1.;

  // to define event, run and mc numbers
  m_RunNumber       = myclass->runNumber;  
  m_EventNumber     = myclass->eventNumber;  
  m_mcChannelNumber = myclass->mcChannelNumber;

  // number of muons
  int nmu   = myclass->mu_pt->size();
  int nel   = myclass->el_pt->size();
  /*std::cout << " runNumber = " << m_RunNumber
	    << " eventNumber = " << m_EventNumber
	    << " mcChannelNumber = " << m_mcChannelNumber
	    << " nmu " << nmu
	    << std::endl;*/

  // in case there is no muon or more than one then exit
  //!!if (nmu!=1) return true;
  if (!myclass->mujets_2016) return true;
  if (nmu!=1) return true;
  // transverse momentum
  m_pt      = myclass->mu_pt->at(0)/1000.;
  // eta of the object (track)
  m_eta     = myclass->mu_eta->at(0);  
  // phi of the object (track)
  m_phi     = myclass->mu_phi->at(0); 
  // missing transverse momentum (MET)
  m_etmiss  = myclass->met_met/1000.;
  // phi of the MET
  m_phimiss = myclass->met_phi;
  // transverse mass made of the lepton and the MET
  m_mlnu    = myutils->transMass(m_pt,m_phi,m_etmiss,m_phimiss);
  // delta phi between the lepton and the MET
  m_dphi    = myutils->CalcdeltaPhi2(m_phi,m_phimiss);
  // significance of the transverse impact parameter
  //m_d0sig   = fabs(myclass->mu_d0->at(0)/sqrt(fabs(myclass->mu_d0sig->at(0))));
  m_d0sig   = fabs(myclass->mu_d0sig->at(0));
  //m_d0sigPV = fabs(myclass->mu_d0sigPV->at(0));
  // isolation variables of the lepton
  m_ptcone30 = myclass->mu_ptvarcone30->at(0)/1000.;
  // number of jets
  m_njet     = CalcNJet();//myclass->jet_pt->size();
  // number of b-jets
  m_nbjet    = CalcNbJet();
  // HT
  m_HT = CalcHT();
  // ETmiss/sqrt(HT)
  if (m_HT>0.)
    m_etmissoversqrtht = m_etmiss/sqrt(m_HT);
  else m_etmissoversqrtht = 0.;
  //std::cout << " ETmiss/sqrt(HT) = " << m_etmissoversqrtht << std::endl;

  /*std::cout << " runNumber = " << m_RunNumber
	    << " eventNumber = " << m_EventNumber
	    << " mcChannelNumber = " << m_mcChannelNumber
	    << " nel = " << nel
	    << " pT =  " << m_et
	    << " eta = " << m_eta 
	    << std::endl;*/

  // for Monte Carlo data
  //std::cout << " m_mcChannelNumber = " << m_mcChannelNumber << std::endl;
  if (m_mcChannelNumber>0) { 
    float Lumi = 1.;
    float xsect = myMCDataSetutils->XSection(m_mcChannelNumber);
    m_XSectweight = Lumi*xsect;
    //std::cout << " xsection = " << xsect
    //	      << " " << m_XSectweight
    //	      << std::endl;
  }

  // efficiencies are not derived for 0-jet
  //if (m_njet<1) return true;
 
  // for Monte Carlo data
  if (m_mcChannelNumber>0) { 
    // remove real leptons
    if (!isTruthMatched()) return true;
    // retrieve MC weight
    GiveMCWeight();
  } 

  // check for leading and closest jet
  LookForLeadingandClosestJet();

  //    std::cout << " avant CR = " << m_typeCR << " " << fabs(m_d0sig) << std::endl;
  if ((m_typeCR=="nocut") ||
      (m_typeCR=="d0sig") ||
      (m_typeCR=="highMTW"        && m_mlnu>100.) ||  
      (m_typeCR=="lowETmissMTW"   && m_etmiss+m_mlnu<60. && m_mlnu<20.) ||
      (m_typeCR=="lowETmiss20"    && m_etmiss<20.) ||  
      (m_typeCR=="lowETmissMTW20" && m_etmiss<20. && m_mlnu<20.)) {
    //std::cout << " CR = " << m_typeCR << " " << fabs(m_d0sig) << std::endl;

    //std::cout << " d0 = " << myclass->mu_d0PV->at(0)
    //	    << " z0 = " << myclass->mu_z0PV->at(0)
    //	    << " " << m_d0sig
    //	    << " " << m_d0sigPV << std::endl;

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
    // fill all histograms
    FillHistos(w);
  }

  return true;
}

// ===========================================================================
void EffiFakeMuon::FillHistos(float weight) 
{
  //
  // main method to fill histograms after all seelction
  //

  //int ibinJet    = -1;
  int ibinPt    = -1;
  int ibinEta   = -1;
  int ibindRClosestJet = -1;
  int ibinPtLeadingJet = -1;
  int ibinDPhi  = -1;
  int ibinMET   = -1;
  int ibinMTW   = -1;
  int ibind0sig = -1;
  int ibinNbJet = -1;
  int ibinNJet  = -1;
  
  bool debug = false;
//Trigger for Muons 2016 HLT_mu24, HLT_mu24_ivarmedium, HLT_mu50
  // trigger matching
  if (m_trigger=="") {
    if (debug)
      std::cout << " trigger = " << m_trigger 
		<< " HLT_mu24 = " 
		<< myclass->HLT_mu24
		<< " HLT_mu24_ivarmedium = " 
		<< myclass->HLT_mu24_ivarmedium
		<< " HLT_mu50 = " 
		<< myclass->HLT_mu50
		<< " mu_trigMatch_HLT_mu24 = " 
		<< myclass->mu_trigMatch_HLT_mu24->at(0)
		<< " mu_trigMatch_HLT_mu24_ivarmedium = " 
		<< myclass->mu_trigMatch_HLT_mu24_ivarmedium->at(0)
		<< " mu_trigMatch_HLT_mu50 = " 
		<< myclass->mu_trigMatch_HLT_mu50
		<< " pt = " << m_pt
		<< std::endl;

    // check that event pass this trigger
    if (!myclass->HLT_mu24 && 
	!myclass->HLT_mu24_ivarmedium && 
	!myclass->HLT_mu50) return;
    // check that lepton matches this trigger
   if (!myclass->mu_trigMatch_HLT_mu24 ->at(0) && 
	 !myclass->mu_trigMatch_HLT_mu24_ivarmedium->at(0) &&
   !myclass->mu_trigMatch_HLT_mu50->at(0)) return;
    // additional pt cut
    //if (m_pt>52.) return;
    if (debug) std::cout << " apres " << std::endl;
  }

  // HLT_mu24
  if (m_trigger=="HLT_mu24") {
    if (debug)
      std::cout << " trigger = " << m_trigger 
		<< " HLT_mu24 = " 
		<< myclass->HLT_mu24
		<< " mu_trigMatch_HLT_mu24 = " 
		<< myclass->mu_trigMatch_HLT_mu24->at(0)
		<< " pt = " << m_pt
		<< std::endl;

    // check that event pass this trigger
    if (!myclass->HLT_mu24) return;
    // check that lepton matches this trigger
    if (!myclass->mu_trigMatch_HLT_mu24->at(0)) return;
    // additional pt cut
    if (m_pt>51.) return;
    if (debug) std::cout << " apres " << std::endl;
  }

  // HLT_mu24_ivarmedium
  if (m_trigger=="HLT_mu24_ivarmedium") {
    if (debug)
      std::cout << " trigger = " << m_trigger 
		<< " HLT_mu24_ivarmedium = " 
		<< myclass->HLT_mu24_ivarmedium
		<< " mu_trigMatch_HLT_mu24_ivarmedium = " 
		<< myclass->mu_trigMatch_HLT_mu24_ivarmedium->at(0)
		<< " pt = " << m_pt
		<< std::endl;
    // check that event pass this trigger
    if (!myclass->HLT_mu24_ivarmedium) return;
    // check that lepton matches this trigger
    if (!myclass->mu_trigMatch_HLT_mu24_ivarmedium->at(0)) return;
    // additional pt cut
    if (m_pt>51.) return;
    if (debug) std::cout << " apres " << std::endl;
  }

  // HLT_mu50
  if (m_trigger=="HLT_mu50") {
    if (debug)
      std::cout << " trigger = " << m_trigger 
		<< " HLT_mu50 = " 
		<< myclass->HLT_mu50
		<< " mu_trigMatch_HLT_mu50 = " 
		<< myclass->mu_trigMatch_HLT_mu50->at(0)
		<< " pt = " << m_pt
		<< std::endl;
    // check that event pass this trigger
    if (!myclass->HLT_mu50) return;
    // check that lepton matches this trigger
    if (!myclass->mu_trigMatch_HLT_mu50->at(0)) return;
    // additional pt cut
    if (m_pt<=51.) return;
    if (debug) std::cout << " apres " << std::endl;
  }

  //std::cout << " ici " << std::endl;
  // loop on PID
  for (int ipid=0;ipid<=1;ipid++) {
    if (ipid==0 && !isLoose()) continue;
    if (ipid==1 && !isTight()) continue; 
    
    // jet bin
    for (int ibinJet=0;ibinJet<=5;ibinJet++) {
      if (ibinJet==0 && m_njet!=0) continue; 
      if (ibinJet==1 && m_njet!=1) continue; 
      if (ibinJet==2 && m_njet<1) continue;
      if (ibinJet==3 && m_njet<2) continue; 
      if (ibinJet==4 && (m_njet!=2 && m_njet!=3)) continue; 
      if (ibinJet==5 && m_njet<4) continue; 

      hmanag->hETmiss[ipid][ibinJet]->Fill(m_etmiss,weight);
      hmanag->hMTW[ipid][ibinJet]->Fill(m_mlnu,weight);
      hmanag->hd0sig[ipid][ibinJet]->Fill(m_d0sig,weight);
      hmanag->hETmissOverSqrtHT[ipid][ibinJet]->Fill(m_etmissoversqrtht,weight);
     
      // in Pt bins
      ibinPt = WhichIndexPt(m_pt);
      hmanag->hETmiss_vsPt[ipid][ibinJet][ibinPt]->Fill(m_etmiss,weight);
      hmanag->hETmissOverSqrtHT_vsPt[ipid][ibinJet][ibinPt]->Fill(m_etmissoversqrtht,weight);
      // add another bin
      if (m_pt>80.) {
	hmanag->hETmiss_vsPt[ipid][ibinJet][10]->Fill(m_etmiss,weight);
	hmanag->hETmissOverSqrtHT_vsPt[ipid][ibinJet][10]->Fill(m_etmissoversqrtht,weight);
      }
      if (m_pt>60.) {
	hmanag->hETmiss_vsPt[ipid][ibinJet][11]->Fill(m_etmiss,weight);
	hmanag->hETmissOverSqrtHT_vsPt[ipid][ibinJet][11]->Fill(m_etmissoversqrtht,weight);
      }
      if (m_pt>50.) {
	hmanag->hETmiss_vsPt[ipid][ibinJet][12]->Fill(m_etmiss,weight);
	hmanag->hETmissOverSqrtHT_vsPt[ipid][ibinJet][12]->Fill(m_etmissoversqrtht,weight);
      } 

      // in Eta bins
      ibinEta = WhichIndexEta(m_eta);
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
      ibinNJet = WhichIndexNJet(m_njet);
      //std::cout << " ibinNJet " << ibinNJet << " " << m_njet << std::endl;
      hmanag->hETmiss_vsNJet[ipid][ibinJet][ibinNJet]->Fill(m_etmiss,weight);
      hmanag->hETmissOverSqrtHT_vsNJet[ipid][ibinJet][ibinNJet]->Fill(m_etmissoversqrtht,weight);

      // in NbJet bins
      ibinNbJet = WhichIndexNbJet(m_nbjet);
      hmanag->hETmiss_vsNbJet[ipid][ibinJet][ibinNbJet]->Fill(m_etmiss,weight);
      hmanag->hETmissOverSqrtHT_vsNbJet[ipid][ibinJet][ibinNbJet]->Fill(m_etmissoversqrtht,weight);
      // add another bin
      if (m_nbjet>=1) {
	hmanag->hETmiss_vsNbJet[ipid][ibinJet][3]->Fill(m_etmiss,weight);
	hmanag->hETmissOverSqrtHT_vsNbJet[ipid][ibinJet][3]->Fill(m_etmissoversqrtht,weight);
      }

      // in d0sig bins
      ibind0sig = WhichIndexd0sig(m_d0sig);
      //std::cout << " ibind0sig = " << ibind0sig << std::endl;
      hmanag->hETmiss_vsd0sig[ipid][ibinJet][ibind0sig]->Fill(m_etmiss,weight);
      hmanag->hETmissOverSqrtHT_vsd0sig[ipid][ibinJet][ibind0sig]->Fill(m_etmissoversqrtht,weight);

    }
  }
}

// ===========================================================================
bool EffiFakeMuon::isLoose() 
{
  //
  // method to check if muon passes Loose selection
  //

  return true;
}

// ===========================================================================
bool EffiFakeMuon::isTight() 
{
  // check if object pass Tight requirements
  bool isMuonTight  = false;

/*  if (m_iso == "Std") {
    isMuonTight = myclass->mu_isTight->at(0);
  } else {
    bool ismuonPID = myclass->mu_Medium->at(0);
    bool isIso = m_ptcone30/m_pt<0.06;
    //std::cout << " ismuonPID = " << ismuonPID << " " << isIso << " " << m_ptcone30/m_et << std::endl;
    isMuonTight = ismuonPID & isIso;
  }

  return isMuonTight;*/

  isMuonTight = myclass->mu_isTight->at(0);
  return isMuonTight;
}

// ================================================================
void EffiFakeMuon::GiveMCWeight()
{
  //
  // method to retrieve weights to be applied to MC
  //

  m_weight = myclass->weight_mc;
  m_weight *= myclass->weight_pileup*myclass->weight_leptonSF;
  m_weightbtag = m_weight*myclass->weight_bTagSF_77;

  return;
}

// ==============================================================
int EffiFakeMuon::CalcNJet()
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
int EffiFakeMuon::CalcNbJet()
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
void EffiFakeMuon::LookForLeadingandClosestJet()
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
double EffiFakeMuon::CalcHT()
{
  //
  // calc sum of pt of leptons and jets
  //

  // get pt of the lepton
  double ht = m_pt;

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
int EffiFakeMuon::WhichIndexEta(float eta)
{
  int index = -1;

  float eta2 = fabs(eta);
  
  if ( eta2 > 0. && eta2 <= 0.25 ) {
    index = 0;
  } else if ( eta2 > 0.25 && eta2 <= 0.50 ) {
      index = 1;
  } else if ( eta2 > 0.50 && eta2 <= 0.75 ) {
    index = 2;
  } else if ( eta2 > 0.75 && eta2 <= 1.00 ) {
    index = 3;
  } else if ( eta2 > 1.00 && eta2 <= 1.25 ) {
    index = 4;
  } else if ( eta2 > 1.25 && eta2 <= 1.50 ) {
    index = 5;
  } else if ( eta2 > 1.50 && eta2 <= 1.75 ) {
    index = 6;
  } else if ( eta2 > 1.75 && eta2 <= 2.00 ) {
    index = 7;
  } else if ( eta2 > 2.00 && eta2 <= 2.25 ) {
    index = 8;
  } else {
    index = 9;
  } 

  return index;
}

// ==============================================================
int EffiFakeMuon::WhichIndexPt(float Pt)
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
int EffiFakeMuon::WhichIndexdRClosestJet(float dRClosestJet)
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
int EffiFakeMuon::WhichIndexPtLeadingJet(float PtJet)
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
int EffiFakeMuon::WhichIndexDPhi(float dphi)
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
int EffiFakeMuon::WhichIndexMET(float met)
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
int EffiFakeMuon::WhichIndexMTW(float mtw)
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
int EffiFakeMuon::WhichIndexd0sig(float d0sig)
{
  int index = -1;

  float d0sig2 = fabs(d0sig);
  
  if ( d0sig2 > 0. && d0sig2 <= 1. ) {
    index = 0;
  } else if ( d0sig2 <= 2.0 ) {
    index = 1;
  } else if ( d0sig2 <= 3.0 ) {
    index = 2;
  } else if ( d0sig2 <= 4.0 ) {
    index = 3;
  } else if ( d0sig2 <= 5.0 ) {
    index = 4;
  } else if ( d0sig2 <= 6.0 ) {
    index = 5;
  } else if ( d0sig2 <= 7.0 ) {
    index = 6;
  } else if ( d0sig2 <= 8.0 ) {
    index = 7;
  } else if ( d0sig2 <= 9.0 ) {
    index = 8;
  } else if ( d0sig2 <= 10.0 ) {
    index = 9;
  } else {
    index = 10;
  } 

  return index;
}

// ==============================================================
int EffiFakeMuon::WhichIndexNJet(int njet)
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
  } else if (njet>=4) {
    index = 4;
  } 

  return index;
}

// ==============================================================
int EffiFakeMuon::WhichIndexNbJet(int nbjet)
{
  int index = -1;

  if (nbjet==0) {
    index = 0;
  } else if (nbjet==1) {
    index = 1;
  } else if (nbjet>=2) {
    index = 2;
  } 

  return index;
}

// ==============================================================
bool EffiFakeMuon::isTruthMatched()
{
  
  // type 
  int type   = myclass->mu_true_type->at(0);
  // origin 
  int origin = myclass->mu_true_origin->at(0);
  // pdg value
  //int pdg = myclass->mu_true_pdg->at(0);

  //std::cout << " type = " << type << " origin = " << origin << " originbkg = " << originbkg << " pdg = " << pdg << std::endl;

  // truth matching ?
  //if (td->mu_truth_matched->at(mu_index) != 1) return false; 
  // test the type of the particle
  //if (pdg!=13) return false;
  //if (type==6 && (origin == 10 || origin ==12 || origin == 13 || origin == 14)) return true; // Isolated muon
  if (type==6) return true; // Isolated muon
  // Capture muons from Z/W->tau(tau)->mu(mu) decays 
  //if (type==7 && origin==9) return true;

  return false;
}
