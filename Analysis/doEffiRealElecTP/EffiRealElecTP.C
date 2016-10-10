#define EffiRealElecTP_cxx
//////////////////////////////////////////////////////////////////////
// 
// Author   : Atlas LPNHE Paris
// Creation : 01/01/2006
// Purpose  : base class to perform analysis 
// Updated  :
//////////////////////////////////////////////////////////////////////

#include "EffiRealElecTP.h"
#include "HistoManagerEffiRealElecTP.h"
#include "../doAna/MyEffiRealElecTP.h"

#include <TStyle.h>
#include <TCanvas.h>
#include <TObjArray.h>
#include <TLorentzVector.h>
#include <TH1.h>
#include <TH2.h>
#include <TMath.h>

ClassImp(EffiRealElecTP);

// Constructor
EffiRealElecTP::EffiRealElecTP(MyEffiRealElecTP *myanalyse, TObjArray *histosObj) 
{
  myclass = myanalyse;

  m_iso = "";
  m_trigger = "";
  m_njetthr = "";
  //m_bweightcut = -0.4434;
  m_bweightcut = 0.645925;

  // Histogram manager
  hmanag = new HistoManagerEffiRealElecTP(histosObj);
  // various utilities
  myutils = new Utils();
  // utilities to handle MC datasets
  myMCDataSetutils = new MCDataSetUtils();

}

// ================================================================
// DESTRUCTOR:
EffiRealElecTP::~EffiRealElecTP()
{ 
  // Histogram manager
  delete hmanag;
  delete myutils;
  delete myMCDataSetutils;
}

// ============================================================================
bool EffiRealElecTP::execute()
{
  // to define event, run and mc numbers
  m_RunNumber       = myclass->runNumber;  
  m_EventNumber     = myclass->eventNumber;  
  m_mcChannelNumber = myclass->mcChannelNumber;

  // number of jets
  m_njet = CalcNJet();
  // number of b-jets
  m_nbjet = CalcNbJet();
  // number of electrons and muons
  int nel   = myclass->el_pt->size();
  int nmu   = myclass->mu_pt->size();

  // no muons !
  if (nmu!=0) return true;
  // at least two electrons
  if (nel<2) return true;

  // apply selection on number of jets
  if (m_njetthr=="njetge1") {
    if (m_njet<1) return true;
  }
  if (m_njetthr=="njeteq1") {
    if (m_njet!=1) return true;
  }
  if (m_njetthr=="njetge2") {
    if (m_njet<2) return true;
  }
  if (m_njetthr=="njeteq2or3") {
    if (m_njet<2||m_njet>3) return true;
  }
  if (m_njetthr=="njetge4") {
    if (m_njet<4) return true;
  }

  std::vector<unsigned int> tagIndexes;
  std::vector<unsigned int> probeIndexes;
  tagIndexes.reserve(nel);
  probeIndexes.reserve(nel);    

  // loop on electrons
  for (int iel=0;iel<nel;iel++) {
    // eta of the cluster
    float etacl   = myclass->el_cl_eta->at(iel); 
    // remove crack
    if ((fabs(etacl)>=1.37 && fabs(etacl)<=1.52)) continue;

    // all objects at this level pass Loose selection so are probes
    probeIndexes.push_back(iel);	
    
    // check if it is tight object
    if (!isTight(iel)) continue;
    
    // all these objects are tag
    tagIndexes.push_back(iel);
  }

  //std::cout << " Nprobe = " << probeIndexes.size() 
  //	    << " Ntag = " << tagIndexes.size()
  //	    << std::endl;
  
  // loop on pairs selected
  for (unsigned int ii = 0; ii < tagIndexes.size(); ++ii) {
    unsigned int i = tagIndexes[ii];
    for (unsigned int jj = 0; jj < probeIndexes.size(); ++jj) {
      unsigned int j = probeIndexes[jj];
      
      // skip pairings of the same electron for tag and probe
      if (i == j) continue; 
      m_isOS = false;
      if (myclass->el_charge->at(i)*myclass->el_charge->at(j)<0.) m_isOS = true;
      // calculate the invriant mass
      m_mll = Calcmll(i,j) ;
      //std::cout << " mll = " << m_mll <<  " " << m_isOS << std::endl;
      // fill histograms
      FillHistos(j);
    }
  }

  return true;
}

// ===========================================================================
void EffiRealElecTP::FillHistos(int iel) 
{
  //
  // Fill histograms for OS or SS 
  //
  bool debug = false;

  int ibinEt             = -1;
  int ibinEta            = -1;
  int ibindRClosestJet   = -1;
  int ibinPtLeadingJet   = -1;
  int ibinDPhi           = -1;
  int ibinMET            = -1;
  int ibinMTW            = -1;
  int ibinNJet           = -1;
  int ibinNbJet          = -1; 
  int ibinNVert          = -1;

  // transverse energy/momentum
  m_et      = myclass->el_pt->at(iel)/1000.;
  // eta of the cluster
  m_etacl   = myclass->el_cl_eta->at(iel); 
  // phi of the cluster
  m_phicl   = myclass->el_phi->at(iel);  // should be phi_cl
  // eta of the object (track)
  m_eta     = myclass->el_eta->at(iel);  
  // phi of the object (track)
  m_phi     = myclass->el_phi->at(iel); 
  // missing transverse momentum (MET)
  m_etmiss  = myclass->met_met/1000.;
  // phi of the MET
  m_phimiss = myclass->met_phi;
  // transverse mass made of the lepton and the MET
  m_mlnu    = myutils->transMass(m_et,m_phi,m_etmiss,m_phimiss);
  // delta phi between the lepton and the MET
  m_dphi    = myutils->CalcdeltaPhi2(m_phi,m_phimiss);
  // isolation variables of the lepton
  m_etcone20 = myclass->el_topoetcone20->at(iel)/1000.;
  m_ptcone20 = myclass->el_ptvarcone20->at(iel)/1000.;
  // find the closest jet
  LookForLeadingandClosestJet(iel);

  // trigger matching
  if (m_trigger=="") {
    if (debug)
      std::cout << " trigger = " << m_trigger 
		<< " mcChannelNumber = " << m_mcChannelNumber
		<< " HLT_e24_lhmedium_L1EM20VH = " 
		<< myclass->HLT_e24_lhmedium_L1EM20VH
		<< " HLT_e60_lhmedium = " << myclass->HLT_e60_lhmedium
		<< " HLT_e120_lhloose = " << myclass->HLT_e120_lhloose
		<< " el_trigMatch_HLT_e24_lhmedium_L1EM20VH = " 
		<< myclass->el_trigMatch_HLT_e24_lhmedium_L1EM20VH->at(iel)
		//<< " el_trigMatch_HLT_e24_lhmedium_L1EM18VH = " 
		//<< myclass->el_trigMatch_HLT_e24_lhmedium_L1EM18VH->at(iel)
		<< " el_trigMatch_HLT_e60_lhmedium = " 
		<< myclass->el_trigMatch_HLT_e60_lhmedium->at(iel)
		<< " el_trigMatch_HLT_e120_lhloose = " 
		<< myclass->el_trigMatch_HLT_e120_lhloose->at(iel)
		<< " ET = " << m_et 
	      << std::endl;
    // check that event pass these triggers
    if ((m_mcChannelNumber==0 && !myclass->HLT_e24_lhmedium_L1EM20VH) && 
	!myclass->HLT_e60_lhmedium && 
	!myclass->HLT_e120_lhloose) return;
    // check that lepton matches these triggers
    if ((m_mcChannelNumber==0 && 
	  !myclass->el_trigMatch_HLT_e24_lhmedium_L1EM20VH->at(iel)) && 
	!myclass->el_trigMatch_HLT_e60_lhmedium->at(iel) && 
	!myclass->el_trigMatch_HLT_e120_lhloose->at(iel)) return;
    if (debug) std::cout << " apres " << std::endl;
  }

  /*// HLT_e24_lhmedium_iloose_L1EM20VH
  if (m_trigger=="HLT_e24_lhmedium_iloose_L1EM20VH") {
    if (debug)
      std::cout << " trigger = " << m_trigger 
		<< " HLT_e24_lhmedium_iloose_L1EM20VH = " 
		<< myclass->HLT_e24_lhmedium_iloose_L1EM20VH
		<< " el_trigMatch_HLT_e24_lhmedium_iloose_L1EM20VH = " 
		<< myclass->el_trigMatch_HLT_e24_lhmedium_iloose_L1EM20VH->at(0)
		<< " ET = " << m_et 
		<< std::endl;
    
    // check that event pass this trigger
    if (!myclass->HLT_e24_lhmedium_iloose_L1EM20VH) return;
    // check that lepton matches this trigger
    if (!myclass->el_trigMatch_HLT_e24_lhmedium_iloose_L1EM20VH->at(0)) return;
    // additional pt cut 
    if (m_et>62.) return;
    std::cout << " apres " << std::endl;
    }*/

  /*// HLT_e24_lhmedium_L1EM18VH 
  if (m_trigger=="HLT_e24_lhmedium_L1EM18VH") {
    if (debug)
      std::cout << " trigger = " << m_trigger 
		<< " HLT_e24_lhmedium_L1EM18VH = " 
		<< myclass->HLT_e24_lhmedium_L1EM18VH
		<< " el_trigMatch_HLT_e24_lhmedium_L1EM18VH = " 
		<< myclass->el_trigMatch_HLT_e24_lhmedium_L1EM18VH->at(0)
		<< " ET = " << m_et 
		<< std::endl;
    // check that event pass this trigger
    if (!myclass->HLT_e24_lhmedium_L1EM18VH) return;
    // check that lepton matches this trigger
    if (!myclass->el_trigMatch_HLT_e24_lhmedium_L1EM18VH->at(0)) return;
    // additional pt cut 
    if (m_et>62.) return;
    std::cout << " apres " << std::endl;
    }*/

  // HLT_e24_lhmedium_L1EM20VH (not included in the MC files)
  if (m_trigger=="HLT_e24_lhmedium_L1EM20VH") {
    if (debug) {
      std::cout << " trigger = " << m_trigger 
		  << " HLT_e24_lhmedium_L1EM20VH = " 
		  << myclass->HLT_e24_lhmedium_L1EM20VH
		  << " el_trigMatch_HLT_e24_lhmedium_L1EM20VH = " 
		  << myclass->el_trigMatch_HLT_e24_lhmedium_L1EM20VH->at(iel)
		  << " ET = " << m_et 
		  << std::endl;
      // for MC
//      if (m_mcChannelNumber>0)
//	std::cout << " trigger = " << m_trigger 
//		  << " HLT_e24_lhmedium_L1EM20VH/L1EM18VH = " 
//		  << myclass->HLT_e24_lhmedium_L1EM18VH
//		  << " el_trigMatch_HLT_e24_lhmedium_L1EM20VH/L1EM18VH = " 
//		  << myclass->el_trigMatch_HLT_e24_lhmedium_L1EM18VH->at(iel)
//		  << " ET = " << m_et 
//		  << std::endl;
    }
    // check that event pass this trigger
//!    if (((m_mcChannelNumber>0 && !myclass->HLT_e24_lhmedium_L1EM18VH) || 
//!	 (m_mcChannelNumber==0 && !myclass->HLT_e24_lhmedium_L1EM20VH))) return;
    if( !myclass->HLT_e24_lhmedium_L1EM20VH) return;
    // check that lepton matches this trigger
    if ( !myclass->el_trigMatch_HLT_e24_lhmedium_L1EM20VH->at(0)) return;
    // additional pt cut 
    if (m_et>62.) return;
    if (debug) std::cout << " apres " << std::endl;
  }

  // HLT_e60_lhmedium
  if (m_trigger=="HLT_e60_lhmedium") {
    if (debug)
      std::cout << " trigger = " << m_trigger 
		<< " HLT_e60_lhmedium = " 
		<< myclass->HLT_e60_lhmedium
		<< " el_trigMatch_HLT_e60_lhmedium = " 
		<< myclass->el_trigMatch_HLT_e60_lhmedium->at(iel)
		<< " ET = " << m_et 
		<< std::endl;
     // check that event pass this trigger
    if (!myclass->HLT_e60_lhmedium) return;
    // check that lepton matches this trigger
    if (!myclass->el_trigMatch_HLT_e60_lhmedium->at(iel)) return;
    // additional pt cut 
    if (m_et<=62. || m_et>122) return;
    //std::cout << " et = " << m_et << std::endl;
    if (debug) std::cout << " apres " << std::endl;
  }

  // HLT_e120_lhloose
  if (m_trigger=="HLT_e120_lhloose") {
    if (debug)
      std::cout << " trigger = " << m_trigger 
		<< " HLT_e120_lhloose = " 
		<< myclass->HLT_e120_lhloose
		<< " el_trigMatch_HLT_e120_lhloose = " 
		<< myclass->el_trigMatch_HLT_e120_lhloose->at(iel)
		<< " ET = " << m_et 
		<< std::endl;
    // check that event pass this trigger
    if (!myclass->HLT_e120_lhloose) return;
    // check that lepton matches this trigger
    if (!myclass->el_trigMatch_HLT_e120_lhloose->at(iel)) return;
    // additional pt cut 
    if (m_et<=122.) return;
    //std::cout << " et = " << m_et << std::endl;
    if (debug) std::cout << " apres " << std::endl;
  }

  // loop on PID
  for (int ipid=0;ipid<2;ipid++) {
    if (ipid==0 && !isLoose()) continue;
    if (ipid==1 && !isTight(iel)) continue; 

    // no binning
    //std::cout << " no binning " << std::endl;
    //std::cout << " select : " << ipid << " " << m_mll << " " << m_isOS << std::endl;
    if (m_isOS) {
      hmanag->hmassZ_OS[ipid]->Fill(m_mll);
    } else {
      hmanag->hmassZ_SS[ipid]->Fill(m_mll);
    }

    // ================================================
    // in Et bins
    ibinEt = WhichIndexEt(m_et);
    //if (et>100. && (ipid==3 || ipid==7))
    //std::cout << " binEt " << ibinEt << " " << m_et << " " << ipid << std::endl;
    if (m_isOS) {
    //if (et>100. && (ipid==3 || ipid==7))
    //std::cout << " binEt " << ibinEt << " " << et << " " << ipid << std::endl;
      hmanag->hmassZ_vsEt_OS[ipid][ibinEt]->Fill(m_mll);
      if (m_et>60.) 
	hmanag->hmassZ_vsEt_OS[ipid][10]->Fill(m_mll);
      if (m_et>80.) 
	hmanag->hmassZ_vsEt_OS[ipid][11]->Fill(m_mll);
    } else {
      hmanag->hmassZ_vsEt_SS[ipid][ibinEt]->Fill(m_mll);
      if (m_et>60.) 
	hmanag->hmassZ_vsEt_SS[ipid][10]->Fill(m_mll);
      if (m_et>80.) 
	hmanag->hmassZ_vsEt_SS[ipid][11]->Fill(m_mll);
    }

    // ================================================
    // in Eta bins
    ibinEta = WhichIndexEta(m_eta);
    //std::cout << " binEta " << ibinEta << std::endl;
    if (m_isOS) {
      hmanag->hmassZ_vsEta_OS[ipid][ibinEta]->Fill(m_mll);
    } else {
      hmanag->hmassZ_vsEta_SS[ipid][ibinEta]->Fill(m_mll);
    }

    // ================================================
    // in dRClosestJet bins
    ibindRClosestJet = WhichIndexdRClosestJet(m_dRmin);
    //std::cout << " ibindRClosestJet = " << ibindRClosestJet << " " << m_dRmin << std::endl;
    if (m_isOS) {
      hmanag->hmassZ_vsdRClosestJet_OS[ipid][ibindRClosestJet]->Fill(m_mll);
    } else {
      hmanag->hmassZ_vsdRClosestJet_SS[ipid][ibindRClosestJet]->Fill(m_mll);
    }

    // ================================================
    // in PtLeadingJet bins
    ibinPtLeadingJet = WhichIndexPtLeadingJet(m_ptlead);
    //std::cout << " ptlead = " << m_ptlead << " " << ibinPtLeadingJet << std::endl;
    if (m_isOS) {
      hmanag->hmassZ_vsPtLeadingJet_OS[ipid][ibinPtLeadingJet]->Fill(m_mll);
    } else {
      hmanag->hmassZ_vsPtLeadingJet_SS[ipid][ibinPtLeadingJet]->Fill(m_mll);
    }

    // ================================================
    // in DPhi bins
    ibinDPhi = WhichIndexDPhi(m_dphi);
    //std::cout << " dphi = " << m_dphi << " " << ibinDPhi << std::endl;
    if (m_isOS) {
      hmanag->hmassZ_vsDPhi_OS[ipid][ibinDPhi]->Fill(m_mll);
    } else {
      hmanag->hmassZ_vsDPhi_SS[ipid][ibinDPhi]->Fill(m_mll);
    }

    // ================================================
    // in MET bins
    ibinMET = WhichIndexMET(m_etmiss);
    //std::cout << " mer = " << m_etmiss << " " << ibinMET << std::endl;
    if (m_isOS) {
      hmanag->hmassZ_vsMET_OS[ipid][ibinMET]->Fill(m_mll);
    } else {
      hmanag->hmassZ_vsMET_SS[ipid][ibinMET]->Fill(m_mll);
    }

    // ================================================
    // in MTW bins
    ibinMTW = WhichIndexMTW(m_mlnu);
    //std::cout << " mtw = " << m_mlnu << " " << ibinMTW << std::endl;
    if (m_isOS) {
      hmanag->hmassZ_vsMTW_OS[ipid][ibinMTW]->Fill(m_mll);
    } else {
      hmanag->hmassZ_vsMTW_SS[ipid][ibinMTW]->Fill(m_mll);
    }

    // ==================================================
    // efficiency vs NVert
    ibinNVert = WhichIndexNVert((int)m_nvert);
    //std::cout << " nvert = " << m_nvert << " " << ibinNVert << std::endl;
    if (ibinNVert>=0) {
      if (m_isOS) {
	hmanag->hmassZNVert_OS[ipid][ibinNVert]->Fill(m_mll);
      } else {
	hmanag->hmassZNVert_SS[ipid][ibinNVert]->Fill(m_mll);
      }
    }

    // ================================================
    // in NJet bins
    //if (m_njet<=6) {
    ibinNJet = WhichIndexNJet(m_njet);
    //std::cout << " njet = " << m_njet << " " << ibinNJet << std::endl;
    if (m_isOS) {
      hmanag->hmassZ_vsNJet_OS[ipid][ibinNJet]->Fill(m_mll);
    } else {
      hmanag->hmassZ_vsNJet_SS[ipid][ibinNJet]->Fill(m_mll);
    }

    // ================================================
    // in NbJet bins
    //std::cout << " mnbjet = " << m_nbjet << std::endl;
    ibinNbJet = WhichIndexNbJet(m_nbjet);
    //std::cout << " mnbjet = " << m_nbjet << std::endl;
    //std::cout << " nbjet = " << m_nbjet << " " << ibinNbJet << std::endl;
    if (m_isOS) {
      hmanag->hmassZ_vsNbJet_OS[ipid][ibinNbJet]->Fill(m_mll);
      if (m_nbjet>=1) hmanag->hmassZ_vsNbJet_OS[ipid][3]->Fill(m_mll);
    } else {
      hmanag->hmassZ_vsNbJet_SS[ipid][ibinNbJet]->Fill(m_mll);
      if (m_nbjet>=1) hmanag->hmassZ_vsNbJet_SS[ipid][3]->Fill(m_mll);
    }

  }
}

// ===========================================================================
bool EffiRealElecTP::isLoose() 
{
  //
  // method to check if electron passes Loose selection
  //

  return true;
}

// ===========================================================================
bool EffiRealElecTP::isTight(int iel) 
{
  //
  // check if object pass Tight requirements
  //

  bool iselecTight = false; 

  // transverse energy/momentum
  double et      = myclass->el_pt->at(iel)/1000.;
  // isolation variables of the lepton
  double etcone20 = myclass->el_topoetcone20->at(iel)/1000.;
  double ptcone20 = myclass->el_ptvarcone20->at(iel)/1000.;

  if (m_iso == "Std") {
    iselecTight = myclass->el_isTight->at(iel);
  } else {
    bool iselecPID = myclass->el_LHTight->at(iel);
    bool isIso = ptcone20/et<0.06 && etcone20/et<0.06;
    //std::cout << " iselecPID = " << iselecPID << " " << isIso << " " << m_ptcone20/m_et << " " << m_etcone20/m_et << std::endl;
    iselecTight = iselecPID & isIso;
  }

  //std::cout << " isTight = " << iselecTight << " " << m_ptcone20 << " " << m_etcone20 << " " << etcone20 << std::endl;
  return iselecTight;
}

// ==============================================================
double EffiRealElecTP::deltaR(double eta1, double eta2, double phi1, double phi2) 
{
  double dPhi=deltaPhi(phi1,phi2);
  double dEta=std::fabs(eta1-eta2);
  double dR=std::sqrt(std::pow(dEta,2)+std::pow(dPhi,2));
  return dR;
}
  
// ==============================================================
double EffiRealElecTP::deltaPhi(double phi1, double phi2) 
{
  double dPhi=std::fabs(phi1-phi2);
  if (dPhi>M_PI) dPhi=2*M_PI-dPhi;
  return dPhi;
}

// ===============================================================
double EffiRealElecTP::CalcdeltaPhi2(double phi1, double phi2) 
{
  double dPhi=phi1-phi2;
  if (dPhi>M_PI)  dPhi=2*M_PI-dPhi;
  if (dPhi<-M_PI) dPhi=2*M_PI+dPhi;
  return dPhi;
}

// ===============================================================
double EffiRealElecTP::transMass(double ptLep, double phiLep, 
				 double met, double phiMet) 
{
  return std::sqrt(2.0*ptLep*met*( 1 - std::cos( phiLep-phiMet ) ) );
}
 
// ===========================================================================
double EffiRealElecTP::Calcmll(int i, int j) 
{
  //
  // method to calculate invariant mass of the two leptons
  //

  // mass of the electron (GeV)
  double melec = 0.000510998902;

  TLorentzVector myvec[2], myvec12;
  double pt1, eta1, phi1;
  double pt2, eta2, phi2;

  //std::cout << " fill 1st lepton " << std::endl;
  // 1st lepton
  pt1  = myclass->el_pt->at(i)/1000.;
  //std::cout << " pt1 = " << pt1 << std::endl;
  eta1 = myclass->el_eta->at(i); 
  //std::cout << " eta1 = " << eta1 << std::endl;
  phi1 = myclass->el_phi->at(i); 
  myvec[0].SetPtEtaPhiM(pt1,eta1,phi1,melec);

  // 2nd lepton
  pt2  = myclass->el_pt->at(j)/1000.;
  eta2 = myclass->el_eta->at(j); 
  phi2 = myclass->el_phi->at(j); 
  myvec[1].SetPtEtaPhiM(pt2,eta2,phi2,melec);

  //std::cout << " fill combined " << std::endl;
  // associate the two particles
  myvec12 = myvec[0]+myvec[1];
  //std::cout << " mass = " << myvec12.Mag() << std::endl;

  return myvec12.Mag();
}

// ==============================================================
int EffiRealElecTP::CalcNJet()
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
int EffiRealElecTP::CalcNbJet()
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
void EffiRealElecTP::LookForLeadingandClosestJet(int i)
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
int EffiRealElecTP::WhichIndexEta(float eta)
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
int EffiRealElecTP::WhichIndexEt(float Et)
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
int EffiRealElecTP::WhichIndexdRClosestJet(float dRClosestJet)
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
int EffiRealElecTP::WhichIndexPtLeadingJet(float PtJet)
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
int EffiRealElecTP::WhichIndexDPhi(float dphi)
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
int EffiRealElecTP::WhichIndexMET(float met)
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
int EffiRealElecTP::WhichIndexMTW(float mtw)
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
int EffiRealElecTP::WhichIndexNVert(int nvert)
{
  int index = -1;

  if (nvert==0) {
    index = 0;
  } else if (nvert==2) {
    index = 1;
  } else if (nvert==4) {
    index = 2;
  } else if (nvert==6) {
    index = 3;
  } else if (nvert==8) {
    index = 4;
  } else if (nvert==10) {
    index = 5;
  } else if (nvert==12) {
    index = 6;
  } else if (nvert==14) {
    index = 7;
  } else if (nvert==16) {
    index = 8;
  } else if (nvert==18) {
    index = 9;
  } else if (nvert==20) {
    index = 10;
  } else if (nvert==22) {
    index = 11;
  } else if (nvert==24) {
    index = 12;
  } else if (nvert==26) {
    index = 13;
  } else if (nvert==28) {
    index = 14;
  } else if (nvert==30) {
    index = 15;
  } 
  return index;
}

// ==============================================================
int EffiRealElecTP::WhichIndexNJet(int njet)
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
int EffiRealElecTP::WhichIndexNbJet(int nbjet)
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
