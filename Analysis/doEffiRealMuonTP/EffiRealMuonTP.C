#define EffiRealMuonTP_cxx
//////////////////////////////////////////////////////////////////////
// 
// Author   : Atlas LPNHE Paris
// Creation : 01/10/2015
// Purpose  : base class to manage efficiency histograms for T&P muons
// Updated  :
//////////////////////////////////////////////////////////////////////

#include "EffiRealMuonTP.h"
#include "HistoManagerEffiRealMuonTP.h"
#include "../doAna/MyEffiRealMuonTP.h"

#include <TStyle.h>
#include <TCanvas.h>
#include <TObjArray.h>
#include <TLorentzVector.h>
#include <TH1.h>
#include <TH2.h>
#include <TMath.h>

ClassImp(EffiRealMuonTP);

// Constructor
EffiRealMuonTP::EffiRealMuonTP(MyEffiRealMuonTP *myanalyse, TObjArray *histosObj) 
{
  myclass = myanalyse;

  m_iso = "";
  m_trigger = "";
  m_njetthr = "";
  //m_bweightcut = -0.4434;
  m_bweightcut = 0.645925;

  // Histogram manager
  hmanag = new HistoManagerEffiRealMuonTP(histosObj);
  // various utilities
  myutils = new Utils();
  // utilities to handle MC datasets
  myMCDataSetutils = new MCDataSetUtils();

}

// ================================================================
// DESTRUCTOR:
EffiRealMuonTP::~EffiRealMuonTP()
{ 
  // Histogram manager
  delete hmanag;
  delete myutils;
  delete myMCDataSetutils;
}

// ============================================================================
bool EffiRealMuonTP::execute()
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

  // no electrons !
  if (nel!=0) return true;
  // at least two muons
  if (nmu<2) return true;

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
  tagIndexes.reserve(nmu);
  probeIndexes.reserve(nmu);    

  // loop on muons
  for (int imu=0;imu<nmu;imu++) {
    // all objects at this level pass Loose selection so are probes
    probeIndexes.push_back(imu);	
    
    // check if it is tight object
    if (!isTight(imu)) continue;
    
    // all these objects are tag
    tagIndexes.push_back(imu);
  }

  //std::cout << " Nprobe = " << probeIndexes.size() 
  //	    << " Ntag = " << tagIndexes.size()
  //	    << std::endl;
  
  // loop on pairs selected
  for (unsigned int ii = 0; ii < tagIndexes.size(); ++ii) {
    unsigned int i = tagIndexes[ii];
    for (unsigned int jj = 0; jj < probeIndexes.size(); ++jj) {
      unsigned int j = probeIndexes[jj];
      
      // skip pairings of the same muon for tag and probe
      if (i == j) continue; 
      m_isOS = false;
      if (myclass->mu_charge->at(i)*myclass->mu_charge->at(j)<0.) m_isOS = true;
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
void EffiRealMuonTP::FillHistos(int imu) 
{
  //
  // Fill histograms for OS or SS 
  //
  bool debug = false;

  int ibinPt             = -1;
  int ibinEta            = -1;
  int ibindRClosestJet   = -1;
  int ibinPtLeadingJet   = -1;
  int ibinDPhi           = -1;
  int ibinMET            = -1;
  int ibinMTW            = -1;
  int ibind0sig          = -1;
  int ibinNVert          = -1;
  int ibinNJet           = -1;
  int ibinNbJet          = -1; 

  // transverse energy/momentum
  m_pt      = myclass->mu_pt->at(imu)/1000.;
  // eta of the object (track)
  m_eta     = myclass->mu_eta->at(imu);  
  // phi of the object (track)
  m_phi     = myclass->mu_phi->at(imu); 
  // missing transverse momentum (MET)
  m_etmiss  = myclass->met_met/1000.;
  // phi of the MET
  m_phimiss = myclass->met_phi;
  // transverse mass made of the lepton and the MET
  m_mlnu    = myutils->transMass(m_pt,m_phi,m_etmiss,m_phimiss);
  // delta phi between the lepton and the MET
  m_dphi    = myutils->CalcdeltaPhi2(m_phi,m_phimiss);
  // d0sig
  m_d0sig   = fabs(myclass->mu_d0sig->at(imu));
  // isolation variables of the lepton
  m_ptcone30 = myclass->mu_ptvarcone30->at(imu)/1000.;
  // find the closest jet
  LookForLeadingandClosestJet(imu);

  // trigger matching
  if (m_trigger=="") {
    if (debug)
      std::cout << " trigger = " << m_trigger 
		<< " HLT_mu20_iloose_L1MU15 = " 
		<< myclass->HLT_mu20_iloose_L1MU15
		<< " HLT_mu20_L1MU15 = " 
		<< myclass->HLT_mu20_L1MU15
		<< " HLT_mu50 = " 
		<< myclass->HLT_mu50
		<< " mu_trigMatch_HLT_mu20_iloose_L1MU15 = " 
		<< myclass->mu_trigMatch_HLT_mu20_iloose_L1MU15->at(imu)
		<< " mu_trigMatch_HLT_mu20_L1MU15 = " 
		<< myclass->mu_trigMatch_HLT_mu20_L1MU15->at(imu)
		<< " mu_trigMatch_HLT_mu50 = " 
		<< myclass->mu_trigMatch_HLT_mu50
		<< " pt = " << m_pt
		<< std::endl;

    // check that event pass this trigger
    if (!myclass->HLT_mu20_iloose_L1MU15 && 
	!myclass->HLT_mu20_L1MU15 && 
	!myclass->HLT_mu50) return;
    // check that lepton matches this trigger
    if (!myclass->mu_trigMatch_HLT_mu20_iloose_L1MU15->at(imu) && 
	!myclass->mu_trigMatch_HLT_mu20_L1MU15->at(imu) &&
	!myclass->mu_trigMatch_HLT_mu50->at(imu)) return;
    // additional pt cut
    //if (m_pt>52.) return;
    if (debug) std::cout << " apres " << std::endl;
  }

  // HLT_mu20_iloose_L1MU15
  if (m_trigger=="HLT_mu20_iloose_L1MU15") {
    if (debug)
      std::cout << " trigger = " << m_trigger 
		<< " HLT_mu20_iloose_L1MU15 = " 
		<< myclass->HLT_mu20_iloose_L1MU15
		<< " mu_trigMatch_HLT_mu20_iloose_L1MU15 = " 
		<< myclass->mu_trigMatch_HLT_mu20_iloose_L1MU15->at(imu)
		<< " pt = " << m_pt
		<< std::endl;

    // check that event pass this trigger
    if (!myclass->HLT_mu20_iloose_L1MU15) return;
    // check that lepton matches this trigger
    if (!myclass->mu_trigMatch_HLT_mu20_iloose_L1MU15->at(imu)) return;
    // additional pt cut
    if (m_pt>52.) return;
    if (debug) std::cout << " apres " << std::endl;
  }

  // HLT_mu20_L1MU15
  if (m_trigger=="HLT_mu20_L1MU15") {
    if (debug)
      std::cout << " trigger = " << m_trigger 
		<< " HLT_mu20_L1MU15 = " 
		<< myclass->HLT_mu20_L1MU15
		<< " mu_trigMatch_HLT_mu20_L1MU15 = " 
		<< myclass->mu_trigMatch_HLT_mu20_L1MU15->at(imu)
		<< " pt = " << m_pt
		<< std::endl;
    // check that event pass this trigger
    if (!myclass->HLT_mu20_L1MU15) return;
    // check that lepton matches this trigger
    if (!myclass->mu_trigMatch_HLT_mu20_L1MU15->at(imu)) return;
    // additional pt cut
    if (m_pt>52.) return;
    if (debug) std::cout << " apres " << std::endl;
  }

  // HLT_mu50
  if (m_trigger=="HLT_mu50") {
    if (debug)
      std::cout << " trigger = " << m_trigger 
		<< " HLT_mu50 = " 
		<< myclass->HLT_mu50
		<< " mu_trigMatch_HLT_mu50 = " 
		<< myclass->mu_trigMatch_HLT_mu50->at(imu)
		<< " pt = " << m_pt
		<< std::endl;
    // check that event pass this trigger
    if (!myclass->HLT_mu50) return;
    // check that lepton matches this trigger
    if (!myclass->mu_trigMatch_HLT_mu50->at(imu)) return;
    // additional pt cut
    if (m_pt<=52.) return;
    if (debug) std::cout << " apres " << std::endl;
  }

  // loop on PID
  for (int ipid=0;ipid<2;ipid++) {
    if (ipid==0 && !isLoose()) continue;
    if (ipid==1 && !isTight(imu)) continue; 

    // no binning
    //std::cout << " no binning " << std::endl;
    //std::cout << " select : " << ipid << " " << m_mll << " " << m_isOS << std::endl;
    if (m_isOS) {
      hmanag->hmassZ_OS[ipid]->Fill(m_mll);
    } else {
      hmanag->hmassZ_SS[ipid]->Fill(m_mll);
    }

    // ================================================
    // in Pt bins
    ibinPt = WhichIndexPt(m_pt);
    //std::cout << " binPt " << ibinPt << " " << m_pt << " " << ipid << std::endl;
    if (m_isOS) {
      hmanag->hmassZ_vsPt_OS[ipid][ibinPt]->Fill(m_mll);
      if (m_pt>60.) 
	hmanag->hmassZ_vsPt_OS[ipid][10]->Fill(m_mll);
      if (m_pt>80.) 
	hmanag->hmassZ_vsPt_OS[ipid][11]->Fill(m_mll);
    } else {
      hmanag->hmassZ_vsPt_SS[ipid][ibinPt]->Fill(m_mll);
      if (m_pt>60.) 
	hmanag->hmassZ_vsPt_SS[ipid][10]->Fill(m_mll);
      if (m_pt>80.) 
	hmanag->hmassZ_vsPt_SS[ipid][11]->Fill(m_mll);
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

    // ================================================
    // in d0sig bins
    ibind0sig = WhichIndexd0sig(m_d0sig);
    //std::cout << " d0sig = " << m_d0sig << " " << ibind0sig << std::endl;
    if (m_isOS) {
      hmanag->hmassZ_vsd0sig_OS[ipid][ibind0sig]->Fill(m_mll);
    } else {
      hmanag->hmassZ_vsd0sig_SS[ipid][ibind0sig]->Fill(m_mll);
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
    //std::cout << " nbjet = " << m_nbjet << " " << ibinNbJet << std::endl;
    if (m_isOS) {
      hmanag->hmassZ_vsNbJet_OS[ipid][ibinNbJet]->Fill(m_mll);
      if (m_nbjet>=1) hmanag->hmassZ_vsNbJet_OS[ipid][3]->Fill(m_mll);
    } else {
      hmanag->hmassZ_vsNbJet_SS[ipid][ibinNbJet]->Fill(m_mll);
      if (m_nbjet>=1) hmanag->hmassZ_vsNbJet_OS[ipid][3]->Fill(m_mll);
    }
  }
}

// ===========================================================================
bool EffiRealMuonTP::isLoose() 
{
  //
  // method to check if electron passes Loose selection
  //

  return true;
}

// ===========================================================================
bool EffiRealMuonTP::isTight(int imu) 
{
  //
  // check if object pass Tight requirements
  //

  // check if object pass Tight requirements
  bool isMuonTight  = false;
  // transverse energy/momentum
  double pt      = myclass->mu_pt->at(imu)/1000.;
  // isolation variables of the lepton
  double ptcone30 = myclass->mu_ptvarcone30->at(imu)/1000.;

  if (m_iso == "Std") {
    isMuonTight = myclass->mu_isTight->at(imu);
  } else {
    bool ismuonPID = myclass->mu_Medium->at(imu);
    bool isIso = ptcone30/pt<0.06;
    //std::cout << " ismuonPID = " << ismuonPID << " " << isIso << " " << m_ptcone30/m_et << std::endl;
    isMuonTight = ismuonPID & isIso;
  }

  return isMuonTight;
}

// ==============================================================
double EffiRealMuonTP::deltaR(double eta1, double eta2, double phi1, double phi2) 
{
  double dPhi=deltaPhi(phi1,phi2);
  double dEta=std::fabs(eta1-eta2);
  double dR=std::sqrt(std::pow(dEta,2)+std::pow(dPhi,2));
  return dR;
}
  
// ==============================================================
double EffiRealMuonTP::deltaPhi(double phi1, double phi2) 
{
  double dPhi=std::fabs(phi1-phi2);
  if (dPhi>M_PI) dPhi=2*M_PI-dPhi;
  return dPhi;
}

// ===============================================================
double EffiRealMuonTP::CalcdeltaPhi2(double phi1, double phi2) 
{
  double dPhi=phi1-phi2;
  if (dPhi>M_PI)  dPhi=2*M_PI-dPhi;
  if (dPhi<-M_PI) dPhi=2*M_PI+dPhi;
  return dPhi;
}

// ===============================================================
double EffiRealMuonTP::transMass(double ptLep, double phiLep, 
				 double met, double phiMet) 
{
  return std::sqrt(2.0*ptLep*met*( 1 - std::cos( phiLep-phiMet ) ) );
}
 
// ===========================================================================
double EffiRealMuonTP::Calcmll(int i, int j) 
{
  //
  // method to calculate invariant mass of the two leptons
  //

  // mass of the muon (GeV)
  double mmuon = 0.105658367;

  TLorentzVector myvec[2], myvec12;
  double pt1, eta1, phi1;
  double pt2, eta2, phi2;

  //std::cout << " fill 1st lepton " << std::endl;
  // 1st lepton
  pt1  = myclass->mu_pt->at(i)/1000.;
  //std::cout << " pt1 = " << pt1 << std::endl;
  eta1 = myclass->mu_eta->at(i); 
  //std::cout << " eta1 = " << eta1 << std::endl;
  phi1 = myclass->mu_phi->at(i); 
  myvec[0].SetPtEtaPhiM(pt1,eta1,phi1,mmuon);

  // 2nd lepton
  pt2  = myclass->mu_pt->at(j)/1000.;
  eta2 = myclass->mu_eta->at(j); 
  phi2 = myclass->mu_phi->at(j); 
  myvec[1].SetPtEtaPhiM(pt2,eta2,phi2,mmuon);

  //std::cout << " fill combined " << std::endl;
  // associate the two particles
  myvec12 = myvec[0]+myvec[1];
  //std::cout << " mass = " << myvec12.Mag() << std::endl;

  return myvec12.Mag();
}

// ==============================================================
int EffiRealMuonTP::CalcNJet()
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
int EffiRealMuonTP::CalcNbJet()
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
void EffiRealMuonTP::LookForLeadingandClosestJet(int i)
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
int EffiRealMuonTP::WhichIndexEta(float eta)
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
int EffiRealMuonTP::WhichIndexPt(float Pt)
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
int EffiRealMuonTP::WhichIndexdRClosestJet(float dRClosestJet)
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
int EffiRealMuonTP::WhichIndexPtLeadingJet(float PtJet)
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
int EffiRealMuonTP::WhichIndexDPhi(float dphi)
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
int EffiRealMuonTP::WhichIndexMET(float met)
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
int EffiRealMuonTP::WhichIndexMTW(float mtw)
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
int EffiRealMuonTP::WhichIndexd0sig(float d0sig)
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
int EffiRealMuonTP::WhichIndexNVert(int nvert)
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
int EffiRealMuonTP::WhichIndexNJet(int njet)
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
int EffiRealMuonTP::WhichIndexNbJet(int nbjet)
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
