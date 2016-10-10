#define SemiLeptonic_cxx
//////////////////////////////////////////////////////////////////////
// 
// Author   : Atlas LPNHE Paris
// Creation : 01/10/2015
// Purpose  : base class to fill histograms for lepton+jets analysis
// Updated  :
//////////////////////////////////////////////////////////////////////

#include "SemiLeptonic.h"
#include "HistoManagerSemiLeptonic.h"
#include "../doAna/MySemiLeptonic.h"

#include "TObject.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TObjArray.h>
#include <cmath>
#include <fstream>

ClassImp(SemiLeptonic);

// Constructor
SemiLeptonic::SemiLeptonic(MySemiLeptonic *myanalyse, TObjArray *histosObj) 
{
  myclass = myanalyse;

  //m_option = myclass->giveOption();
  
  m_RunNumber = 300000;

  // Histogram manager
  hmanag = new HistoManagerSemiLeptonic(histosObj);
  // various utilities
  myutils = new Utils();
  // utilities to handle MC datasets
  myMCDataSetutils = new MCDataSetUtils();

  // initialization of vectors
  for (int i=0;i<30;i++) {
    m_CutflowEJets[i]  = 0.;
    m_CutflowMuJets[i] = 0.;
    
    m_CutflowEJetsweight[i]  = 0.;
    m_CutflowMuJetsweight[i] = 0.;
    
    m_CutflowEJetsweightpu[i]  = 0.;
    m_CutflowMuJetsweightpu[i] = 0.;
    
    m_CutflowEJetsweightsf[i]  = 0.;
    m_CutflowMuJetsweightsf[i] = 0.;
  }
}

// ================================================================
// DESTRUCTOR:
SemiLeptonic::~SemiLeptonic()
{ 
  // Histogram manager
  delete hmanag;
  delete myutils;
  delete myMCDataSetutils;
}

// ============================================================================
bool SemiLeptonic::execute()
{
  m_weight     = 1.;
  m_weightbtag = 1.;
  float w      = 1.;

  // to define event, run and mc numbers
  m_RunNumber       = myclass->runNumber;  
  m_EventNumber     = myclass->eventNumber;  
  m_mcChannelNumber = myclass->mcChannelNumber;

  // to check if events pass a e+jets or a mu+jets analysius
  int isejet  =  myclass->ejets_2015;
  int ismujet =  myclass->mujets_2015;
  if (isejet==1) m_channel=0;
  if (ismujet==1) m_channel=1;

  // number of electrons
  int nel   = myclass->el_pt->size();
  // number of muons
  int nmu   = myclass->mu_pt->size();
  /*std::cout << " runNumber = " << m_RunNumber
	    << " eventNumber = " << m_EventNumber
	    << " mcChannelNumber = " << m_mcChannelNumber
	    << " channel = " << m_channel
	    << " nel " << nel
	    << " nmu " << nmu
	    << " isejet = " << isejet
	    << " ismujet = " << ismujet
	    << std::endl;
  */
  if (m_channel==0) {
    // in case there is no electron or more than one then exit
    if (nel!=1) return true;    
    // transverse energy/momentum
    m_pt      = myclass->el_pt->at(0)/1000.;
    // charge
    m_charge  = myclass->el_charge->at(0);
    // eta of the cluster
    m_etacl   = myclass->el_cl_eta->at(0); 
    // phi of the cluster
    m_phicl   = myclass->el_phi->at(0);  // should be phi_cl
    // eta of the object (track)
    m_eta     = myclass->el_eta->at(0);  
    // phi of the object (track)
    m_phi     = myclass->el_phi->at(0); 
    // isolation variables of the lepton
    m_etcone20 = myclass->el_topoetcone20->at(0)/1000.;
    m_ptcone20 = myclass->el_ptvarcone20->at(0)/1000.;
    m_ptcone30 = myclass->el_ptcone30->at(0)/1000.;
  } else {
    // in case there is no muon or more than one then exit
    if (nmu!=1) return true;    
    // transverse momentum
    m_pt      = myclass->mu_pt->at(0)/1000.;
    // charge
    m_charge  = myclass->mu_charge->at(0);
    // eta of the object (track)
    m_eta     = myclass->mu_eta->at(0);  
    // phi of the object (track)
    m_phi     = myclass->mu_phi->at(0); 
    // isolation variables of the lepton
    m_etcone20 = myclass->mu_topoetcone20->at(0)/1000.;
    m_ptcone20 = 0.;
    m_ptcone30 = myclass->mu_ptvarcone30->at(0)/1000.;
  }
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
  //m_d0sig   = fabs(myclass->mu_d0sig->at(0));
  //std::cout << " d0 = " << myclass->mu_d0->at(0)
  //	    << " " << myclass->mu_d0sig->at(0)
  //	    << " " << m_d0sig << std::endl;
  //std::cout << " mtw = " << m_mlnu << " " << myclass->el_MT->at(0)/1000. << std::endl;
  // number of jets
  m_njet = CalcNJet();
  // number of b-jets
  m_nbjet = CalcNbJet();
  // HT
  m_HT = CalcHT();
  // isTight
  m_istight = isTight();

  // for Monte Carlo 
  if (m_mcChannelNumber>0) { 
    float Lumi = 1.;
    float xsect = myMCDataSetutils->XSection(m_mcChannelNumber);
    m_XSectweight = Lumi*xsect;
    //std::cout << " xsection = " << xsect
    //	      << " " << m_XSectweight
    //	      << std::endl;
  } 

  if (m_njet<1) return true;
  
  // loop on type of lepton 
  for (int itype=0;itype<2;itype++) {
    // loop on level of MET/MTW 
    for (int ilevel=0;ilevel<5;ilevel++) {
      // loop on level of cut
      for (int icut=0;icut<84;icut++) {
	m_passSelectionCuts[itype][ilevel][icut] = false;
      }
    }
  }
  
  // for Monte Carlo data
  if (m_mcChannelNumber>0) { 
    // keep only true leptons
    if (!isTrueLepton()) return true;
    // calculate MC weight SF
    GiveMCWeight();
  } else {
    //std::cout << " channel = " << m_channel << " " << m_doChannel << std::endl;
    //if (m_channel != m_doChannel) return true;
  } 
  
  // check for leading and closest jet
  LookForLeadingandClosestJet();
  
  // apply the different selections
  if (!m_istight) return true;
  if (!Select()) return true;
  
  // loop on level of MET/MTW 
  for (int ilevel=0;ilevel<5;ilevel++) {
    // loop on level of cut
    for (int icut=0;icut<84;icut++) {
      // check if it passes selection
      if (!m_passSelectionCuts[m_channel][ilevel][icut]) continue;
      
      // pretag selection
      if (icut==0 || icut==7 || icut==14 || icut==21 || icut==28 || 
	  icut==35 || icut==42 || icut==49 || icut==56 || icut==63 || 
	  icut==70 || icut==77) {
	w = m_weight;
	// all tag selection
      } else if (icut==1 || icut==8 || icut==15 || icut==22 || icut==29 || 
		 icut==36 || icut==43 || icut==49 || icut==56 || icut==63 || 
		 icut==70 || icut==77) {
	if (m_nbjet==0) {
	  w = m_weight;
	} else {
	  w = m_weightbtag;
	}
	// 0-btag selection
      } else if (icut==2 || icut==9 || icut==16 || icut==23 || icut==30 || 
		 icut==37 || icut==44 || icut==50 || icut==57 || icut==64 || 
		 icut==71 || icut==78) {
	w = m_weight;
      } else {
	w = m_weightbtag;
      }

      /*//if (m_channel==0 && icut==28 && ilevel==0) 
      //if (m_channel==0 && icut==33 && ilevel==1) 
      if (m_channel==0 && icut==70 && ilevel==0) 
	std::cout << " Event " << m_EventNumber
		  << " njet " << m_njet 
		  << " nbjet = " << m_nbjet
		  << " ETmiss = " << m_etmiss
		  << " mlnu " << m_mlnu
		  << " pT = " << m_pt
		  << " eta = " << m_eta
		  << " w = " << w
	  //<< " SF Ele = " << myclass->SemiLeptonic_SF_Elec
	  //<< " SF muon = " << myclass->SemiLeptonic_SF_Muon
	  //<< " SF Trigger = " << myclass->SemiLeptonic_SF_Trigger
	  //	  << " SF PU = " << myclass->SemiLeptonic_SF_PU
	  //	  << " SF ZV = " << myclass->SemiLeptonic_SF_ZVertex
	  //	  << " SF btag = " << myclass->SemiLeptonic_SF_Btag
		  << std::endl;
      */
      FillHistos(ilevel,icut,w);
      
    }
  }

  return true;
}

// ================================================================
void SemiLeptonic::GiveMCWeight()
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
int SemiLeptonic::CalcNJet()
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
int SemiLeptonic::CalcNbJet()
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
void SemiLeptonic::LookForLeadingandClosestJet()
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

  // for leading jet
  m_pt_LeadingJet      = 0.;
  m_eta_LeadingJet     = 0.;
  m_phi_LeadingJet     = 0.;
  m_dR_LeadingJet      = 0.;
  m_bWeight_LeadingJet = -9999.;

  // for closest jet
  m_dR_ClosestJet       = 0.;
  m_pt_ClosestJet       = 0.;
  m_eta_ClosestJet      = 0.;
  m_phi_ClosestJet      = 0.;
  m_bWeight_ClosestJet  = -9999.;

  // for jet with higher b-weight
  m_dR_maxbWeightJet      = 0.;
  m_pt_maxbWeightJet      = 0.;
  m_eta_maxbWeightJet     = 0.;
  m_phi_maxbWeightJet     = 0.;
  m_bWeight_maxbWeightJet = -9999.;

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
      ptjetmax      = ptjet;
      m_pt_LeadingJet      = ptjet;
      m_eta_LeadingJet     = etajet;
      m_phi_LeadingJet     = phijet;
      m_dR_LeadingJet      = dR;
      m_bWeight_LeadingJet = bWeight;
    }
    // look for closest jet
    if (dR<dRmin) {
      dRmin                = dR;
      m_dR_ClosestJet      = dR;
      m_pt_ClosestJet      = ptjet;
      m_eta_ClosestJet     = etajet;
      m_phi_ClosestJet     = phijet;
      m_bWeight_ClosestJet = bWeight;
    }
    // look for jet with highest b-weight
    if (bWeight>bWeightmax) {
      bWeightmax              = bWeight;
      m_dR_maxbWeightJet      = dR;
      m_pt_maxbWeightJet      = ptjet;
      m_eta_maxbWeightJet     = etajet;
      m_phi_maxbWeightJet     = phijet;
      m_bWeight_maxbWeightJet = bWeight;
    }
  }
  /*std::cout << " pT lead = " << m_ptlead 
	    << " " << myclass->leadingCentralJetpT/1000.
	    << " " << myclass->leadingJetpT/1000.
	    << std::endl;
  */
}

// ==============================================================
double SemiLeptonic::CalcHT()
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

// ===========================================================================
bool SemiLeptonic::isTight() 
{
  // check if object pass Tight requirements
  bool isLeptonTight = false; 

  // case for electrons
  if (m_channel==0) {
    if (m_iso == "Std") {
      isLeptonTight = myclass->el_isTight->at(0);
    } else {
      bool iselecPID = myclass->el_LHTight->at(0);
      bool isIso = m_ptcone20/m_pt<0.06 && m_etcone20/m_pt<0.06;
      //std::cout << " iselecPID = " << iselecPID << " " << isIso << " " << m_ptcone20/m_pt << " " << m_etcone20/m_pt << std::endl;
      isLeptonTight = iselecPID & isIso;
    }
  }

  // case for muons
  if (m_channel==1) {
    if (m_iso == "Std") {
      isLeptonTight = myclass->mu_isTight->at(0);
    } else {
      bool ismuonPID = myclass->mu_Medium->at(0);
      bool isIso = m_ptcone30/m_pt<0.06;
      //std::cout << " ismuonPID = " << ismuonPID << " " << isIso << " " << m_ptcone30/m_pt << std::endl;
      isLeptonTight = ismuonPID & isIso;
    }
  }

  return isLeptonTight;
}

// ===============================================================
bool SemiLeptonic::Select()
{
  // remove events with electron in crack that we don't use by default
  if (m_channel==0 && (fabs(m_eta)>=1.37 && fabs(m_eta)<=1.52)) return false;

  // loop on level of MET/MTW 
  for (int ilevel=0;ilevel<5;ilevel++) {
    if (ilevel==1 && !(m_etmiss>30. && m_mlnu>30.)) continue;
    if (ilevel==2 && !(m_etmiss>20. && m_etmiss+m_mlnu>60.)) continue;
    if (ilevel==3 && !(m_mlnu>20. && m_etmiss+m_mlnu<60.)) continue;
    if (ilevel==4 && m_etmiss+m_mlnu>60.) continue;
     
    // >=6 jets
    m_passSelectionCuts[m_channel][ilevel][0] = (m_njet>=6);
    m_passSelectionCuts[m_channel][ilevel][1] = (m_njet>=6);
    m_passSelectionCuts[m_channel][ilevel][2] = (m_njet>=6 && m_nbjet==0);
    m_passSelectionCuts[m_channel][ilevel][3] = (m_njet>=6 && m_nbjet==1);
    m_passSelectionCuts[m_channel][ilevel][4] = (m_njet>=6 && m_nbjet==2);
    m_passSelectionCuts[m_channel][ilevel][5] = (m_njet>=6 && m_nbjet>=1);
    m_passSelectionCuts[m_channel][ilevel][6] = (m_njet>=6 && m_nbjet>=2);
    // ==6 jets
    m_passSelectionCuts[m_channel][ilevel][7]  = (m_njet==6);
    m_passSelectionCuts[m_channel][ilevel][8]  = (m_njet==6);
    m_passSelectionCuts[m_channel][ilevel][9]  = (m_njet==6 && m_nbjet==0);
    m_passSelectionCuts[m_channel][ilevel][10] = (m_njet==6 && m_nbjet==1);
    m_passSelectionCuts[m_channel][ilevel][11] = (m_njet==6 && m_nbjet==2);
    m_passSelectionCuts[m_channel][ilevel][12] = (m_njet==6 && m_nbjet>=1);
    m_passSelectionCuts[m_channel][ilevel][13] = (m_njet==6 && m_nbjet>=2);
    // >=5 jets
    m_passSelectionCuts[m_channel][ilevel][14] = (m_njet>=5);
    m_passSelectionCuts[m_channel][ilevel][15] = (m_njet>=5);
    m_passSelectionCuts[m_channel][ilevel][16] = (m_njet>=5 && m_nbjet==0);
    m_passSelectionCuts[m_channel][ilevel][17] = (m_njet>=5 && m_nbjet==1);
    m_passSelectionCuts[m_channel][ilevel][18] = (m_njet>=5 && m_nbjet==2);
    m_passSelectionCuts[m_channel][ilevel][19] = (m_njet>=5 && m_nbjet>=1);
    m_passSelectionCuts[m_channel][ilevel][20] = (m_njet>=5 && m_nbjet>=2);
    // ==5 jets
    m_passSelectionCuts[m_channel][ilevel][21] = (m_njet==5);
    m_passSelectionCuts[m_channel][ilevel][22] = (m_njet==5);
    m_passSelectionCuts[m_channel][ilevel][23] = (m_njet==5 && m_nbjet==0);
    m_passSelectionCuts[m_channel][ilevel][24] = (m_njet==5 && m_nbjet==1);
    m_passSelectionCuts[m_channel][ilevel][25] = (m_njet==5 && m_nbjet==2);
    m_passSelectionCuts[m_channel][ilevel][26] = (m_njet==5 && m_nbjet>=1);
    m_passSelectionCuts[m_channel][ilevel][27] = (m_njet==5 && m_nbjet>=2);
    // >=4 jets
    m_passSelectionCuts[m_channel][ilevel][28] = (m_njet>=4);
    m_passSelectionCuts[m_channel][ilevel][29] = (m_njet>=4);
    m_passSelectionCuts[m_channel][ilevel][30] = (m_njet>=4 && m_nbjet==0);
    m_passSelectionCuts[m_channel][ilevel][31] = (m_njet>=4 && m_nbjet==1);
    m_passSelectionCuts[m_channel][ilevel][32] = (m_njet>=4 && m_nbjet==2);
    m_passSelectionCuts[m_channel][ilevel][33] = (m_njet>=4 && m_nbjet>=1);
    m_passSelectionCuts[m_channel][ilevel][34] = (m_njet>=4 && m_nbjet>=2);
    // ==4 jets
    m_passSelectionCuts[m_channel][ilevel][35] = (m_njet==4);
    m_passSelectionCuts[m_channel][ilevel][36] = (m_njet==4);
    m_passSelectionCuts[m_channel][ilevel][37] = (m_njet==4 && m_nbjet==0);
    m_passSelectionCuts[m_channel][ilevel][38] = (m_njet==4 && m_nbjet==1);
    m_passSelectionCuts[m_channel][ilevel][39] = (m_njet==4 && m_nbjet==2);
    m_passSelectionCuts[m_channel][ilevel][40] = (m_njet==4 && m_nbjet>=1);
    m_passSelectionCuts[m_channel][ilevel][41] = (m_njet==4 && m_nbjet>=2);
    // >=3 jets
    m_passSelectionCuts[m_channel][ilevel][42] = (m_njet>=3);
    m_passSelectionCuts[m_channel][ilevel][43] = (m_njet>=3);
    m_passSelectionCuts[m_channel][ilevel][44] = (m_njet>=3 && m_nbjet==0);
    m_passSelectionCuts[m_channel][ilevel][45] = (m_njet>=3 && m_nbjet==1);
    m_passSelectionCuts[m_channel][ilevel][46] = (m_njet>=3 && m_nbjet==2);
    m_passSelectionCuts[m_channel][ilevel][47] = (m_njet>=3 && m_nbjet>=1);
    m_passSelectionCuts[m_channel][ilevel][48] = (m_njet>=3 && m_nbjet>=2);
    // ==3 jets
    m_passSelectionCuts[m_channel][ilevel][49] = (m_njet==3);
    m_passSelectionCuts[m_channel][ilevel][50] = (m_njet==3);
    m_passSelectionCuts[m_channel][ilevel][51] = (m_njet==3 && m_nbjet==0);
    m_passSelectionCuts[m_channel][ilevel][52] = (m_njet==3 && m_nbjet==1);
    m_passSelectionCuts[m_channel][ilevel][53] = (m_njet==3 && m_nbjet==2);
    m_passSelectionCuts[m_channel][ilevel][54] = (m_njet==3 && m_nbjet>=1);
    m_passSelectionCuts[m_channel][ilevel][55] = (m_njet==3 && m_nbjet>=2);
    // >=2 jets
    m_passSelectionCuts[m_channel][ilevel][56] = (m_njet>=2);
    m_passSelectionCuts[m_channel][ilevel][57] = (m_njet>=2);
    m_passSelectionCuts[m_channel][ilevel][58] = (m_njet>=2 && m_nbjet==0);
    m_passSelectionCuts[m_channel][ilevel][59] = (m_njet>=2 && m_nbjet==1);
    m_passSelectionCuts[m_channel][ilevel][60] = (m_njet>=2 && m_nbjet==2);
    m_passSelectionCuts[m_channel][ilevel][61] = (m_njet>=2 && m_nbjet>=1);
    m_passSelectionCuts[m_channel][ilevel][62] = (m_njet>=2 && m_nbjet>=2);
    // ==2 jets
    m_passSelectionCuts[m_channel][ilevel][63] = (m_njet==2);
    m_passSelectionCuts[m_channel][ilevel][64] = (m_njet==2);
    m_passSelectionCuts[m_channel][ilevel][65] = (m_njet==2 && m_nbjet==0);
    m_passSelectionCuts[m_channel][ilevel][66] = (m_njet==2 && m_nbjet==1);
    m_passSelectionCuts[m_channel][ilevel][67] = (m_njet==2 && m_nbjet==2);
    m_passSelectionCuts[m_channel][ilevel][68] = (m_njet==2 && m_nbjet>=1);
    m_passSelectionCuts[m_channel][ilevel][69] = (m_njet==2 && m_nbjet>=2);
    // >=1 jets
    m_passSelectionCuts[m_channel][ilevel][70] = (m_njet>=1);
    m_passSelectionCuts[m_channel][ilevel][71] = (m_njet>=1);
    m_passSelectionCuts[m_channel][ilevel][72] = (m_njet>=1 && m_nbjet==0);
    m_passSelectionCuts[m_channel][ilevel][73] = (m_njet>=1 && m_nbjet==1);
    m_passSelectionCuts[m_channel][ilevel][74] = (m_njet>=1 && m_nbjet==2);
    m_passSelectionCuts[m_channel][ilevel][75] = (m_njet>=1 && m_nbjet>=1);
    m_passSelectionCuts[m_channel][ilevel][76] = (m_njet>=1 && m_nbjet>=2);
    // ==1 jets
    m_passSelectionCuts[m_channel][ilevel][77] = (m_njet==1);
    m_passSelectionCuts[m_channel][ilevel][78] = (m_njet==1);
    m_passSelectionCuts[m_channel][ilevel][79] = (m_njet==1 && m_nbjet==0);
    m_passSelectionCuts[m_channel][ilevel][80] = (m_njet==1 && m_nbjet==1);
    m_passSelectionCuts[m_channel][ilevel][81] = (m_njet==1 && m_nbjet==2);
    m_passSelectionCuts[m_channel][ilevel][82] = (m_njet==1 && m_nbjet>=1);
    m_passSelectionCuts[m_channel][ilevel][83] = (m_njet==1 && m_nbjet>=2);
  }

  return true;
}

// ============================================================================
void SemiLeptonic::FillHistos(int ilevel, int icut, float weight)
{
  //
  // Fill histograms
  //
  
  /*bool isSignal = isTrueElecMatch(myclass->SemiLeptonic_Lept_mcType, myclass->SemiLeptonic_Lept_mcTypebkg, myclass->SemiLeptonic_Lept_mcOriginbkg,1);
  bool isFromb = isTrueElecMatch(myclass->SemiLeptonic_Lept_mcType, myclass->SemiLeptonic_Lept_mcTypebkg, myclass->SemiLeptonic_Lept_mcOriginbkg,2) ;
  bool isFromConv = isTrueElecMatch(myclass->SemiLeptonic_Lept_mcType, myclass->SemiLeptonic_Lept_mcTypebkg, myclass->SemiLeptonic_Lept_mcOriginbkg,3);
  bool isHadron = isTrueElecMatch(myclass->SemiLeptonic_Lept_mcType, myclass->SemiLeptonic_Lept_mcTypebkg, myclass->SemiLeptonic_Lept_mcOriginbkg,4);
if (ilevel==1 && icut==56)   std::cout << " etmiss = " << ETmiss 
	    << " " << ptlept << " " << etalept 
	    << " mcmatch = " << myclass->SemiLeptonic_Lept_mcMatch 
	    << " isSignal = " << isSignal
	    << " isFromb = " << isFromb
	    << " isFromConv = " << isFromConv
	    << " isHadron = " << isHadron
    //<< " isConv = " << myclass->SemiLeptonic_Lept_isConv << " " << myclass->SemiLeptonic_Lept_RConv << " " << myclass->SemiLeptonic_Lept_zConv << " nBL = " << myclass->SemiLeptonic_Lept_nBLHits 
	    <<std::endl;
  //if (!isTrueElecMatch(myclass->SemiLeptonic_Lept_mcType, myclass->SemiLeptonic_Lept_mcTypebkg, myclass->SemiLeptonic_Lept_mcOriginbkg,1)) return;
  if (!isFromb) return;
  */ 

  //if (j==112) 
  //std::cout << " mychannel = " << m_channel << " " << ilevel << " " << myclass->SemiLeptonic_eventNumber << " ETmiss = " << m_etmiss << " " << hfor << " mcweight = " << myclass->SemiLeptonic_mcevt_weight << " SF = " << myclass->SemiLeptonic_SF_AllPretag << " " << myclass->SemiLeptonic_SF_AllBtag << std::endl;

  // if (std::isnan(weight)) 
  /*  std::cout << " mychannel = " << m_channel 
	      << " " << ilevel 
	      << " " << myclass->SemiLeptonic_eventNumber 
	      << " ETmiss = " << m_etmiss 
	      << " hfor = " << hfor 
	      << " mcweight = " << myclass->SemiLeptonic_mcevt_weight 
	      << " SF = " << myclass->SemiLeptonic_SF_AllPretag 
	      << " " << myclass->SemiLeptonic_SF_AllBtag 
	      << " SF Ele = " << myclass->SemiLeptonic_SF_Elec
	      << " SF Muon = " << myclass->SemiLeptonic_SF_Muon
	      << " SF Btag = " << myclass->SemiLeptonic_SF_Btag
	      << " SF Wj = " << myclass->SemiLeptonic_SF_Wjets
	      << " SF Wjshape = " << myclass->SemiLeptonic_SF_WjetsShape
	      << " SF Trigger = " << myclass->SemiLeptonic_SF_Trigger
	      << " SF PU = " << myclass->SemiLeptonic_SF_PU
	      << " SF ZV = " << myclass->SemiLeptonic_SF_ZVertex
	      << std::endl;
  */  
  hmanag->hETmiss[m_channel][ilevel][icut]->Fill(m_etmiss,weight);
  hmanag->hmTW[m_channel][ilevel][icut]->Fill(m_mlnu,weight);
  hmanag->hnjet[m_channel][ilevel][icut]->Fill(m_njet,weight);
  hmanag->hnbjet[m_channel][ilevel][icut]->Fill(m_nbjet,weight);

  // leading jet
  hmanag->hdRLeadingJet[m_channel][ilevel][icut]->Fill(m_dR_LeadingJet,weight);
  hmanag->hpTLeadingJet[m_channel][ilevel][icut]->Fill(m_pt_LeadingJet,weight);
  hmanag->hetaLeadingJet[m_channel][ilevel][icut]->Fill(m_eta_LeadingJet,weight);
  hmanag->hphiLeadingJet[m_channel][ilevel][icut]->Fill(m_phi_LeadingJet,weight);
  hmanag->hbWeightLeadingJet[m_channel][ilevel][icut]->Fill(m_bWeight_LeadingJet,weight);      
  // closest jet
  hmanag->hdRClosestJet[m_channel][ilevel][icut]->Fill(m_dR_ClosestJet,weight);
  hmanag->hbWeightClosestJet[m_channel][ilevel][icut]->Fill(m_bWeight_ClosestJet,weight);      
  hmanag->hpTClosestJet[m_channel][ilevel][icut]->Fill(m_pt_ClosestJet,weight);
  hmanag->hetaClosestJet[m_channel][ilevel][icut]->Fill(m_eta_ClosestJet,weight);
  hmanag->hphiClosestJet[m_channel][ilevel][icut]->Fill(m_phi_ClosestJet,weight);
  // jet with highest bWeight
  hmanag->hdRmaxbJet[m_channel][ilevel][icut]->Fill(m_dR_maxbWeightJet,weight);
  hmanag->hpTClosestJet[m_channel][ilevel][icut]->Fill(m_pt_maxbWeightJet,weight);
  hmanag->hetamaxbJet[m_channel][ilevel][icut]->Fill(m_eta_maxbWeightJet,weight);
  hmanag->hphimaxbJet[m_channel][ilevel][icut]->Fill(m_phi_maxbWeightJet,weight);
  hmanag->hbWeightmaxbJet[m_channel][ilevel][icut]->Fill(m_bWeight_maxbWeightJet,weight);
  // delta Phi (lept-ETmiss)
  hmanag->hdeltaPhiLeptETmiss[m_channel][ilevel][icut]->Fill(m_dphi,weight);
  
  // for electron
  // charge of the lepton
  hmanag->hchargelept[m_channel][ilevel][icut]->Fill(m_charge,weight);
  // pt of the lepton
  hmanag->hpTlept[m_channel][ilevel][icut]->Fill(m_pt,weight);
  // eta of the lepton
  hmanag->hetalept[m_channel][ilevel][icut]->Fill(m_eta,weight);
  // phi of the lepton
  hmanag->hphilept[m_channel][ilevel][icut]->Fill(m_phi,weight);
  
  //std::cout << " eta = " << m_eta << " " << m_phi << " " << weight << std::endl;
  // ETCone20
  hmanag->hETCone20lept[m_channel][ilevel][icut]->Fill(m_etcone20,weight);
  // pTCone30
  hmanag->hpTCone30lept[m_channel][ilevel][icut]->Fill(m_ptcone30,weight);
  
  return;
}

// ==============================================================
bool SemiLeptonic::isTrueLepton()
{
  // case of e+jets selection
  if (m_channel==0) {
    if (!isTrueElectron()) return false;
  }
  // case of mu+jets selection
  if (m_channel==1) {
    if (!isTrueMuon()) return false;
  }

  return true;
}

// ==============================================================
bool SemiLeptonic::isTrueElectron()
{
  
  // type 
  int type   = myclass->el_true_type->at(0);
  // origin 
  int origin = myclass->el_true_origin->at(0);
  // origin Bkg
  int originbkg = myclass->el_true_originbkg->at(0);
  // pdg value
  //int pdg = myclass->el_true_pdg->at(0);

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
  /*if (type==4 && origin==5) { // BkgElectron and origin=PhotonConversion
    if (originbkg==10 || // from top
	originbkg==12 || // from W
	originbkg==13 || // from Z
	originbkg==14)   // from Higgs
      return true; 
      }*/
  return false;

}

// ==============================================================
bool SemiLeptonic::isTrueMuon()
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
  if (type==6 && (origin == 10 || origin ==12 || origin == 13 || origin == 14)) return true; // Isolated muon
  // Capture muons from Z/W->tau(tau)->mu(mu) decays 
  //if (type==7 && origin==9) return true;

  return false;
}
