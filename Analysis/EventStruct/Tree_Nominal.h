//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Nov 23 09:44:30 2015 by ROOT version 5.34/11
// from TTree nominal/tree
// found on file: /data/atlas0/data/MC/MC15/DAOD_TOPQ1/filt/NTUP/25ns/tmp/user.derue.7047923._000001.output.root
//////////////////////////////////////////////////////////

#ifndef Tree_Nominal_h
#define Tree_Nominal_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <vector>
#include <vector>
#include <vector>

// Fixed size dimensions of array or collections stored in the TTree if any.

class Tree_Nominal : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
   Float_t         weight_mc;
   Float_t         weight_pileup;
   Float_t         weight_leptonSF;
   Float_t         weight_bTagSF_85;
   Float_t         weight_bTagSF_77;
   Float_t         weight_bTagSF_70;
   Float_t         weight_bTagSF_60;
   Float_t         weight_pileup_UP;
   Float_t         weight_pileup_DOWN;
   Float_t         weight_leptonSF_EL_SF_Trigger_UP;
   Float_t         weight_leptonSF_EL_SF_Trigger_DOWN;
   Float_t         weight_leptonSF_EL_SF_Reco_UP;
   Float_t         weight_leptonSF_EL_SF_Reco_DOWN;
   Float_t         weight_leptonSF_EL_SF_ID_UP;
   Float_t         weight_leptonSF_EL_SF_ID_DOWN;
   Float_t         weight_leptonSF_EL_SF_Isol_UP;
   Float_t         weight_leptonSF_EL_SF_Isol_DOWN;
   Float_t         weight_leptonSF_MU_SF_Trigger_STAT_UP;
   Float_t         weight_leptonSF_MU_SF_Trigger_STAT_DOWN;
   Float_t         weight_leptonSF_MU_SF_Trigger_SYST_UP;
   Float_t         weight_leptonSF_MU_SF_Trigger_SYST_DOWN;
   Float_t         weight_leptonSF_MU_SF_ID_STAT_UP;
   Float_t         weight_leptonSF_MU_SF_ID_STAT_DOWN;
   Float_t         weight_leptonSF_MU_SF_ID_SYST_UP;
   Float_t         weight_leptonSF_MU_SF_ID_SYST_DOWN;
   Float_t         weight_leptonSF_MU_SF_Isol_STAT_UP;
   Float_t         weight_leptonSF_MU_SF_Isol_STAT_DOWN;
   Float_t         weight_leptonSF_MU_SF_Isol_SYST_UP;
   Float_t         weight_leptonSF_MU_SF_Isol_SYST_DOWN;
   Float_t         weight_indiv_SF_EL_Trigger;
   Float_t         weight_indiv_SF_EL_Trigger_UP;
   Float_t         weight_indiv_SF_EL_Trigger_DOWN;
   Float_t         weight_indiv_SF_EL_Reco;
   Float_t         weight_indiv_SF_EL_Reco_UP;
   Float_t         weight_indiv_SF_EL_Reco_DOWN;
   Float_t         weight_indiv_SF_EL_ID;
   Float_t         weight_indiv_SF_EL_ID_UP;
   Float_t         weight_indiv_SF_EL_ID_DOWN;
   Float_t         weight_indiv_SF_EL_Isol;
   Float_t         weight_indiv_SF_EL_Isol_UP;
   Float_t         weight_indiv_SF_EL_Isol_DOWN;
   Float_t         weight_indiv_SF_MU_Trigger;
   Float_t         weight_indiv_SF_MU_Trigger_STAT_UP;
   Float_t         weight_indiv_SF_MU_Trigger_STAT_DOWN;
   Float_t         weight_indiv_SF_MU_Trigger_SYST_UP;
   Float_t         weight_indiv_SF_MU_Trigger_SYST_DOWN;
   Float_t         weight_indiv_SF_MU_ID;
   Float_t         weight_indiv_SF_MU_ID_STAT_UP;
   Float_t         weight_indiv_SF_MU_ID_STAT_DOWN;
   Float_t         weight_indiv_SF_MU_ID_SYST_UP;
   Float_t         weight_indiv_SF_MU_ID_SYST_DOWN;
   Float_t         weight_indiv_SF_MU_Isol;
   Float_t         weight_indiv_SF_MU_Isol_STAT_UP;
   Float_t         weight_indiv_SF_MU_Isol_STAT_DOWN;
   Float_t         weight_indiv_SF_MU_Isol_SYST_UP;
   Float_t         weight_indiv_SF_MU_Isol_SYST_DOWN;
   vector<float>   *weight_bTagSF_85_eigenvars_B_up;
   vector<float>   *weight_bTagSF_85_eigenvars_C_up;
   vector<float>   *weight_bTagSF_85_eigenvars_Light_up;
   vector<float>   *weight_bTagSF_85_eigenvars_B_down;
   vector<float>   *weight_bTagSF_85_eigenvars_C_down;
   vector<float>   *weight_bTagSF_85_eigenvars_Light_down;
   Float_t         weight_bTagSF_85_extrapolation_up;
   Float_t         weight_bTagSF_85_extrapolation_down;
   Float_t         weight_bTagSF_85_extrapolation_from_charm_up;
   Float_t         weight_bTagSF_85_extrapolation_from_charm_down;
   vector<float>   *weight_bTagSF_77_eigenvars_B_up;
   vector<float>   *weight_bTagSF_77_eigenvars_C_up;
   vector<float>   *weight_bTagSF_77_eigenvars_Light_up;
   vector<float>   *weight_bTagSF_77_eigenvars_B_down;
   vector<float>   *weight_bTagSF_77_eigenvars_C_down;
   vector<float>   *weight_bTagSF_77_eigenvars_Light_down;
   Float_t         weight_bTagSF_77_extrapolation_up;
   Float_t         weight_bTagSF_77_extrapolation_down;
   Float_t         weight_bTagSF_77_extrapolation_from_charm_up;
   Float_t         weight_bTagSF_77_extrapolation_from_charm_down;
   vector<float>   *weight_bTagSF_70_eigenvars_B_up;
   vector<float>   *weight_bTagSF_70_eigenvars_C_up;
   vector<float>   *weight_bTagSF_70_eigenvars_Light_up;
   vector<float>   *weight_bTagSF_70_eigenvars_B_down;
   vector<float>   *weight_bTagSF_70_eigenvars_C_down;
   vector<float>   *weight_bTagSF_70_eigenvars_Light_down;
   Float_t         weight_bTagSF_70_extrapolation_up;
   Float_t         weight_bTagSF_70_extrapolation_down;
   Float_t         weight_bTagSF_70_extrapolation_from_charm_up;
   Float_t         weight_bTagSF_70_extrapolation_from_charm_down;
   vector<float>   *weight_bTagSF_60_eigenvars_B_up;
   vector<float>   *weight_bTagSF_60_eigenvars_C_up;
   vector<float>   *weight_bTagSF_60_eigenvars_Light_up;
   vector<float>   *weight_bTagSF_60_eigenvars_B_down;
   vector<float>   *weight_bTagSF_60_eigenvars_C_down;
   vector<float>   *weight_bTagSF_60_eigenvars_Light_down;
   Float_t         weight_bTagSF_60_extrapolation_up;
   Float_t         weight_bTagSF_60_extrapolation_down;
   Float_t         weight_bTagSF_60_extrapolation_from_charm_up;
   Float_t         weight_bTagSF_60_extrapolation_from_charm_down;
   ULong64_t       eventNumber;
   UInt_t          runNumber;
   UInt_t          mcChannelNumber;
   Float_t         mu;
   vector<float>   *el_pt;
   vector<float>   *el_eta;
   vector<float>   *el_cl_eta;
   vector<float>   *el_phi;
   vector<float>   *el_e;
   vector<float>   *el_charge;
   vector<float>   *el_topoetcone20;
   vector<float>   *el_ptvarcone20;
   vector<float>   *el_d0sig;
   vector<float>   *el_delta_z0_sintheta;
   vector<float>   *mu_pt;
   vector<float>   *mu_eta;
   vector<float>   *mu_phi;
   vector<float>   *mu_e;
   vector<float>   *mu_charge;
   vector<float>   *mu_topoetcone20;
   vector<float>   *mu_ptvarcone30;
   vector<float>   *mu_d0sig;
   vector<float>   *mu_delta_z0_sintheta;
   vector<float>   *jet_pt;
   vector<float>   *jet_eta;
   vector<float>   *jet_phi;
   vector<float>   *jet_e;
   vector<float>   *jet_mv1;
   vector<float>   *jet_mvb;
   vector<float>   *jet_mv1c;
   vector<float>   *jet_mv2c00;
   vector<float>   *jet_mv2c10;
   vector<float>   *jet_mv2c20;
   vector<float>   *jet_ip3dsv1;
   vector<float>   *jet_jvt;
   Float_t         met_met;
   Float_t         met_phi;
   Int_t           ejets;
   Int_t           mujets;
   Int_t           ee;
   Int_t           mumu;
   Int_t           emu;
   Bool_t          HLT_mu20_iloose_L1MU15;
   Bool_t          HLT_mu20_L1MU15;
   Bool_t          HLT_mu50;
   Bool_t          HLT_e60_lhmedium;
   Bool_t          HLT_e24_lhmedium_iloose_L1EM20VH;
   Bool_t          HLT_e24_lhmedium_L1EM20VH;
   Bool_t          HLT_e24_lhmedium_L1EM18VH;
   Bool_t          HLT_e120_lhloose;
   vector<bool>    *el_trigMatch_HLT_e60_lhmedium;
   vector<bool>    *el_trigMatch_HLT_e24_lhmedium_iloose_L1EM20VH;
   vector<bool>    *el_trigMatch_HLT_e24_lhmedium_L1EM20VH;
   vector<bool>    *el_trigMatch_HLT_e24_lhmedium_L1EM18VH;
   vector<bool>    *el_trigMatch_HLT_e120_lhloose;
   vector<bool>    *mu_trigMatch_HLT_mu50;
   vector<bool>    *mu_trigMatch_HLT_mu20_iloose_L1MU15;
   vector<bool>    *mu_trigMatch_HLT_mu20_L1MU15;
   UInt_t          lbn;
   Float_t         Vtxz;
   UInt_t          npVtx;
   UInt_t          el_n;
   vector<bool>    *el_LHLoose;
   vector<bool>    *el_LHMedium;
   vector<bool>    *el_LHTight;
   vector<bool>    *el_isoGradient;
   vector<bool>    *el_isoGradientLoose;
   vector<bool>    *el_isoTight;
   vector<bool>    *el_isoLoose;
   vector<bool>    *el_isoLooseTrackOnly;
   vector<bool>    *el_isoFixedCutTight;
   vector<bool>    *el_isoFixedCutTightTrackOnly;
   vector<bool>    *el_isoFixedCutLoose;
   vector<float>   *el_d0PV;
   vector<float>   *el_z0PV;
   vector<float>   *el_d0sigPV;
   vector<float>   *el_z0sigPV;
   vector<float>   *el_topoetcone30;
   vector<float>   *el_topoetcone40;
   vector<float>   *el_ptcone30;
   vector<float>   *el_ptcone40;
   vector<float>   *el_MT;
   vector<float>   *el_dRClosetJet;
   vector<float>   *el_dRClosetJet_WithFwds;
   vector<float>   *el_PtClosetJet;
   vector<float>   *el_PtClosetJet_WithFwds;
   vector<float>   *el_dROverPtClosetJet;
   vector<float>   *el_dROverPtClosetJet_WithFwds;
   vector<float>   *el_dPhiMET;
   vector<int>     *el_trigMatch;
   vector<int>     *el_true_type;
   vector<int>     *el_true_origin;
   vector<int>     *el_true_typebkg;
   vector<int>     *el_true_originbkg;
   vector<int>     *el_true_pdg;
   vector<float>   *el_true_pt;
   vector<float>   *el_true_eta;
   vector<float>   *el_true_phi;
   vector<float>   *el_f3core;
   vector<int>     *el_nBL;
   vector<int>     *el_nPix;
   UInt_t          mu_n;
   vector<bool>    *mu_Tight;
   vector<bool>    *mu_Medium;
   vector<bool>    *mu_Loose;
   vector<bool>    *mu_isoGradient;
   vector<bool>    *mu_isoGradientLoose;
   vector<bool>    *mu_isoTight;
   vector<bool>    *mu_isoLoose;
   vector<bool>    *mu_isoLooseTrackOnly;
   vector<bool>    *mu_isoFixedCutTightTrackOnly;
   vector<bool>    *mu_isoFixedCutLoose;
   vector<float>   *mu_d0PV;
   vector<float>   *mu_z0PV;
   vector<float>   *mu_d0sigPV;
   vector<float>   *mu_z0sigPV;
   vector<float>   *mu_topoetcone30;
   vector<float>   *mu_topoetcone40;
   vector<float>   *mu_ptcone30;
   vector<float>   *mu_ptcone40;
   vector<float>   *mu_MT;
   vector<float>   *mu_dRClosetJet;
   vector<float>   *mu_dRClosetJet_WithFwds;
   vector<float>   *mu_PtClosetJet;
   vector<float>   *mu_PtClosetJet_WithFwds;
   vector<float>   *mu_dROverPtClosetJet;
   vector<float>   *mu_dROverPtClosetJet_WithFwds;
   vector<float>   *mu_dPhiMET;
   vector<int>     *mu_trigMatch;
   vector<int>     *mu_true_type;
   vector<int>     *mu_true_origin;
   vector<int>     *mu_true_pdg;
   vector<float>   *mu_true_pt;
   vector<float>   *mu_true_eta;
   vector<float>   *mu_true_phi;
   UInt_t          jet_n;
   UInt_t          jet_n_WithFwds;
   UInt_t          jet_nbtag_60;
   UInt_t          jet_nbtag_70;
   UInt_t          jet_nbtag_77;
   UInt_t          jet_nbtag_85;
   vector<float>   *jet_m;
   vector<bool>    *jet_isFwd;
   vector<bool>    *jet_isbtagged_60;
   vector<bool>    *jet_isbtagged_70;
   vector<bool>    *jet_isbtagged_77;
   vector<bool>    *jet_isbtagged_85;
   Float_t         leadingJetpT;
   Float_t         leadingJetpT_WithFwds;
   Float_t         met_px;
   Float_t         met_py;
   Float_t         met_sumet;
   Float_t         Ht;
   Float_t         Ht_WithFwds;

   // List of branches
   TBranch        *b_weight_mc;   //!
   TBranch        *b_weight_pileup;   //!
   TBranch        *b_weight_leptonSF;   //!
   TBranch        *b_weight_bTagSF_85;   //!
   TBranch        *b_weight_bTagSF_77;   //!
   TBranch        *b_weight_bTagSF_70;   //!
   TBranch        *b_weight_bTagSF_60;   //!
   TBranch        *b_weight_pileup_UP;   //!
   TBranch        *b_weight_pileup_DOWN;   //!
   TBranch        *b_weight_leptonSF_EL_SF_Trigger_UP;   //!
   TBranch        *b_weight_leptonSF_EL_SF_Trigger_DOWN;   //!
   TBranch        *b_weight_leptonSF_EL_SF_Reco_UP;   //!
   TBranch        *b_weight_leptonSF_EL_SF_Reco_DOWN;   //!
   TBranch        *b_weight_leptonSF_EL_SF_ID_UP;   //!
   TBranch        *b_weight_leptonSF_EL_SF_ID_DOWN;   //!
   TBranch        *b_weight_leptonSF_EL_SF_Isol_UP;   //!
   TBranch        *b_weight_leptonSF_EL_SF_Isol_DOWN;   //!
   TBranch        *b_weight_leptonSF_MU_SF_Trigger_STAT_UP;   //!
   TBranch        *b_weight_leptonSF_MU_SF_Trigger_STAT_DOWN;   //!
   TBranch        *b_weight_leptonSF_MU_SF_Trigger_SYST_UP;   //!
   TBranch        *b_weight_leptonSF_MU_SF_Trigger_SYST_DOWN;   //!
   TBranch        *b_weight_leptonSF_MU_SF_ID_STAT_UP;   //!
   TBranch        *b_weight_leptonSF_MU_SF_ID_STAT_DOWN;   //!
   TBranch        *b_weight_leptonSF_MU_SF_ID_SYST_UP;   //!
   TBranch        *b_weight_leptonSF_MU_SF_ID_SYST_DOWN;   //!
   TBranch        *b_weight_leptonSF_MU_SF_Isol_STAT_UP;   //!
   TBranch        *b_weight_leptonSF_MU_SF_Isol_STAT_DOWN;   //!
   TBranch        *b_weight_leptonSF_MU_SF_Isol_SYST_UP;   //!
   TBranch        *b_weight_leptonSF_MU_SF_Isol_SYST_DOWN;   //!
   TBranch        *b_weight_indiv_SF_EL_Trigger;   //!
   TBranch        *b_weight_indiv_SF_EL_Trigger_UP;   //!
   TBranch        *b_weight_indiv_SF_EL_Trigger_DOWN;   //!
   TBranch        *b_weight_indiv_SF_EL_Reco;   //!
   TBranch        *b_weight_indiv_SF_EL_Reco_UP;   //!
   TBranch        *b_weight_indiv_SF_EL_Reco_DOWN;   //!
   TBranch        *b_weight_indiv_SF_EL_ID;   //!
   TBranch        *b_weight_indiv_SF_EL_ID_UP;   //!
   TBranch        *b_weight_indiv_SF_EL_ID_DOWN;   //!
   TBranch        *b_weight_indiv_SF_EL_Isol;   //!
   TBranch        *b_weight_indiv_SF_EL_Isol_UP;   //!
   TBranch        *b_weight_indiv_SF_EL_Isol_DOWN;   //!
   TBranch        *b_weight_indiv_SF_MU_Trigger;   //!
   TBranch        *b_weight_indiv_SF_MU_Trigger_STAT_UP;   //!
   TBranch        *b_weight_indiv_SF_MU_Trigger_STAT_DOWN;   //!
   TBranch        *b_weight_indiv_SF_MU_Trigger_SYST_UP;   //!
   TBranch        *b_weight_indiv_SF_MU_Trigger_SYST_DOWN;   //!
   TBranch        *b_weight_indiv_SF_MU_ID;   //!
   TBranch        *b_weight_indiv_SF_MU_ID_STAT_UP;   //!
   TBranch        *b_weight_indiv_SF_MU_ID_STAT_DOWN;   //!
   TBranch        *b_weight_indiv_SF_MU_ID_SYST_UP;   //!
   TBranch        *b_weight_indiv_SF_MU_ID_SYST_DOWN;   //!
   TBranch        *b_weight_indiv_SF_MU_Isol;   //!
   TBranch        *b_weight_indiv_SF_MU_Isol_STAT_UP;   //!
   TBranch        *b_weight_indiv_SF_MU_Isol_STAT_DOWN;   //!
   TBranch        *b_weight_indiv_SF_MU_Isol_SYST_UP;   //!
   TBranch        *b_weight_indiv_SF_MU_Isol_SYST_DOWN;   //!
   TBranch        *b_weight_bTagSF_85_eigenvars_B_up;   //!
   TBranch        *b_weight_bTagSF_85_eigenvars_C_up;   //!
   TBranch        *b_weight_bTagSF_85_eigenvars_Light_up;   //!
   TBranch        *b_weight_bTagSF_85_eigenvars_B_down;   //!
   TBranch        *b_weight_bTagSF_85_eigenvars_C_down;   //!
   TBranch        *b_weight_bTagSF_85_eigenvars_Light_down;   //!
   TBranch        *b_weight_bTagSF_85_extrapolation_up;   //!
   TBranch        *b_weight_bTagSF_85_extrapolation_down;   //!
   TBranch        *b_weight_bTagSF_85_extrapolation_from_charm_up;   //!
   TBranch        *b_weight_bTagSF_85_extrapolation_from_charm_down;   //!
   TBranch        *b_weight_bTagSF_77_eigenvars_B_up;   //!
   TBranch        *b_weight_bTagSF_77_eigenvars_C_up;   //!
   TBranch        *b_weight_bTagSF_77_eigenvars_Light_up;   //!
   TBranch        *b_weight_bTagSF_77_eigenvars_B_down;   //!
   TBranch        *b_weight_bTagSF_77_eigenvars_C_down;   //!
   TBranch        *b_weight_bTagSF_77_eigenvars_Light_down;   //!
   TBranch        *b_weight_bTagSF_77_extrapolation_up;   //!
   TBranch        *b_weight_bTagSF_77_extrapolation_down;   //!
   TBranch        *b_weight_bTagSF_77_extrapolation_from_charm_up;   //!
   TBranch        *b_weight_bTagSF_77_extrapolation_from_charm_down;   //!
   TBranch        *b_weight_bTagSF_70_eigenvars_B_up;   //!
   TBranch        *b_weight_bTagSF_70_eigenvars_C_up;   //!
   TBranch        *b_weight_bTagSF_70_eigenvars_Light_up;   //!
   TBranch        *b_weight_bTagSF_70_eigenvars_B_down;   //!
   TBranch        *b_weight_bTagSF_70_eigenvars_C_down;   //!
   TBranch        *b_weight_bTagSF_70_eigenvars_Light_down;   //!
   TBranch        *b_weight_bTagSF_70_extrapolation_up;   //!
   TBranch        *b_weight_bTagSF_70_extrapolation_down;   //!
   TBranch        *b_weight_bTagSF_70_extrapolation_from_charm_up;   //!
   TBranch        *b_weight_bTagSF_70_extrapolation_from_charm_down;   //!
   TBranch        *b_weight_bTagSF_60_eigenvars_B_up;   //!
   TBranch        *b_weight_bTagSF_60_eigenvars_C_up;   //!
   TBranch        *b_weight_bTagSF_60_eigenvars_Light_up;   //!
   TBranch        *b_weight_bTagSF_60_eigenvars_B_down;   //!
   TBranch        *b_weight_bTagSF_60_eigenvars_C_down;   //!
   TBranch        *b_weight_bTagSF_60_eigenvars_Light_down;   //!
   TBranch        *b_weight_bTagSF_60_extrapolation_up;   //!
   TBranch        *b_weight_bTagSF_60_extrapolation_down;   //!
   TBranch        *b_weight_bTagSF_60_extrapolation_from_charm_up;   //!
   TBranch        *b_weight_bTagSF_60_extrapolation_from_charm_down;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_runNumber;   //!
   TBranch        *b_mcChannelNumber;   //!
   TBranch        *b_mu;   //!
   TBranch        *b_el_pt;   //!
   TBranch        *b_el_eta;   //!
   TBranch        *b_el_cl_eta;   //!
   TBranch        *b_el_phi;   //!
   TBranch        *b_el_e;   //!
   TBranch        *b_el_charge;   //!
   TBranch        *b_el_topoetcone20;   //!
   TBranch        *b_el_ptvarcone20;   //!
   TBranch        *b_el_d0sig;   //!
   TBranch        *b_el_delta_z0_sintheta;   //!
   TBranch        *b_mu_pt;   //!
   TBranch        *b_mu_eta;   //!
   TBranch        *b_mu_phi;   //!
   TBranch        *b_mu_e;   //!
   TBranch        *b_mu_charge;   //!
   TBranch        *b_mu_topoetcone20;   //!
   TBranch        *b_mu_ptvarcone30;   //!
   TBranch        *b_mu_d0sig;   //!
   TBranch        *b_mu_delta_z0_sintheta;   //!
   TBranch        *b_jet_pt;   //!
   TBranch        *b_jet_eta;   //!
   TBranch        *b_jet_phi;   //!
   TBranch        *b_jet_e;   //!
   TBranch        *b_jet_mv1;   //!
   TBranch        *b_jet_mvb;   //!
   TBranch        *b_jet_mv1c;   //!
   TBranch        *b_jet_mv2c00;   //!
   TBranch        *b_jet_mv2c10;   //!
   TBranch        *b_jet_mv2c20;   //!
   TBranch        *b_jet_ip3dsv1;   //!
   TBranch        *b_jet_jvt;   //!
   TBranch        *b_met_met;   //!
   TBranch        *b_met_phi;   //!
   TBranch        *b_ejets;   //!
   TBranch        *b_mujets;   //!
   TBranch        *b_ee;   //!
   TBranch        *b_mumu;   //!
   TBranch        *b_emu;   //!
   TBranch        *b_HLT_mu20_iloose_L1MU15;   //!
   TBranch        *b_HLT_mu20_L1MU15;   //!
   TBranch        *b_HLT_mu50;   //!
   TBranch        *b_HLT_e60_lhmedium;   //!
   TBranch        *b_HLT_e24_lhmedium_iloose_L1EM20VH;   //!
   TBranch        *b_HLT_e24_lhmedium_L1EM20VH;   //!
   TBranch        *b_HLT_e24_lhmedium_L1EM18VH;   //!
   TBranch        *b_HLT_e120_lhloose;   //!
   TBranch        *b_el_trigMatch_HLT_e60_lhmedium;   //!
   TBranch        *b_el_trigMatch_HLT_e24_lhmedium_iloose_L1EM20VH;   //!
   TBranch        *b_el_trigMatch_HLT_e24_lhmedium_L1EM20VH;   //!
   TBranch        *b_el_trigMatch_HLT_e24_lhmedium_L1EM18VH;   //!
   TBranch        *b_el_trigMatch_HLT_e120_lhloose;   //!
   TBranch        *b_mu_trigMatch_HLT_mu50;   //!
   TBranch        *b_mu_trigMatch_HLT_mu20_iloose_L1MU15;   //!
   TBranch        *b_mu_trigMatch_HLT_mu20_L1MU15;   //!
   TBranch        *b_lbn;   //!
   TBranch        *b_Vtxz;   //!
   TBranch        *b_npVtx;   //!
   TBranch        *b_el_n;   //!
   TBranch        *b_el_LHLoose;   //!
   TBranch        *b_el_LHMedium;   //!
   TBranch        *b_el_LHTight;   //!
   TBranch        *b_el_isoGradient;   //!
   TBranch        *b_el_isoGradientLoose;   //!
   TBranch        *b_el_isoTight;   //!
   TBranch        *b_el_isoLoose;   //!
   TBranch        *b_el_isoLooseTrackOnly;   //!
   TBranch        *b_el_isoFixedCutTight;   //!
   TBranch        *b_el_isoFixedCutTightTrackOnly;   //!
   TBranch        *b_el_isoFixedCutLoose;   //!
   TBranch        *b_el_d0PV;   //!
   TBranch        *b_el_z0PV;   //!
   TBranch        *b_el_d0sigPV;   //!
   TBranch        *b_el_z0sigPV;   //!
   TBranch        *b_el_topoetcone30;   //!
   TBranch        *b_el_topoetcone40;   //!
   TBranch        *b_el_ptcone30;   //!
   TBranch        *b_el_ptcone40;   //!
   TBranch        *b_el_MT;   //!
   TBranch        *b_el_dRClosetJet;   //!
   TBranch        *b_el_dRClosetJet_WithFwds;   //!
   TBranch        *b_el_PtClosetJet;   //!
   TBranch        *b_el_PtClosetJet_WithFwds;   //!
   TBranch        *b_el_dROverPtClosetJet;   //!
   TBranch        *b_el_dROverPtClosetJet_WithFwds;   //!
   TBranch        *b_el_dPhiMET;   //!
   TBranch        *b_el_trigMatch;   //!
   TBranch        *b_el_true_type;   //!
   TBranch        *b_el_true_origin;   //!
   TBranch        *b_el_true_typebkg;   //!
   TBranch        *b_el_true_originbkg;   //!
   TBranch        *b_el_true_pdg;   //!
   TBranch        *b_el_true_pt;   //!
   TBranch        *b_el_true_eta;   //!
   TBranch        *b_el_true_phi;   //!
   TBranch        *b_el_f3core;   //!
   TBranch        *b_el_nBL;   //!
   TBranch        *b_el_nPix;   //!
   TBranch        *b_mu_n;   //!
   TBranch        *b_mu_Tight;   //!
   TBranch        *b_mu_Medium;   //!
   TBranch        *b_mu_Loose;   //!
   TBranch        *b_mu_isoGradient;   //!
   TBranch        *b_mu_isoGradientLoose;   //!
   TBranch        *b_mu_isoTight;   //!
   TBranch        *b_mu_isoLoose;   //!
   TBranch        *b_mu_isoLooseTrackOnly;   //!
   TBranch        *b_mu_isoFixedCutTightTrackOnly;   //!
   TBranch        *b_mu_isoFixedCutLoose;   //!
   TBranch        *b_mu_d0PV;   //!
   TBranch        *b_mu_z0PV;   //!
   TBranch        *b_mu_d0sigPV;   //!
   TBranch        *b_mu_z0sigPV;   //!
   TBranch        *b_mu_topoetcone30;   //!
   TBranch        *b_mu_topoetcone40;   //!
   TBranch        *b_mu_ptcone30;   //!
   TBranch        *b_mu_ptcone40;   //!
   TBranch        *b_mu_MT;   //!
   TBranch        *b_mu_dRClosetJet;   //!
   TBranch        *b_mu_dRClosetJet_WithFwds;   //!
   TBranch        *b_mu_PtClosetJet;   //!
   TBranch        *b_mu_PtClosetJet_WithFwds;   //!
   TBranch        *b_mu_dROverPtClosetJet;   //!
   TBranch        *b_mu_dROverPtClosetJet_WithFwds;   //!
   TBranch        *b_mu_dPhiMET;   //!
   TBranch        *b_mu_trigMatch;   //!
   TBranch        *b_mu_true_type;   //!
   TBranch        *b_mu_true_origin;   //!
   TBranch        *b_mu_true_pdg;   //!
   TBranch        *b_mu_true_pt;   //!
   TBranch        *b_mu_true_eta;   //!
   TBranch        *b_mu_true_phi;   //!
   TBranch        *b_jet_n;   //!
   TBranch        *b_jet_n_WithFwds;   //!
   TBranch        *b_jet_nbtag_60;   //!
   TBranch        *b_jet_nbtag_70;   //!
   TBranch        *b_jet_nbtag_77;   //!
   TBranch        *b_jet_nbtag_85;   //!
   TBranch        *b_jet_m;   //!
   TBranch        *b_jet_isFwd;   //!
   TBranch        *b_jet_isbtagged_60;   //!
   TBranch        *b_jet_isbtagged_70;   //!
   TBranch        *b_jet_isbtagged_77;   //!
   TBranch        *b_jet_isbtagged_85;   //!
   TBranch        *b_leadingJetpT;   //!
   TBranch        *b_leadingJetpT_WithFwds;   //!
   TBranch        *b_met_px;   //!
   TBranch        *b_met_py;   //!
   TBranch        *b_met_sumet;   //!
   TBranch        *b_Ht;   //!
   TBranch        *b_Ht_WithFwds;   //!

   Tree_Nominal(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~Tree_Nominal() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(Tree_Nominal,0);
};

#endif

#ifdef Tree_Nominal_cxx
void Tree_Nominal::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   weight_bTagSF_85_eigenvars_B_up = 0;
   weight_bTagSF_85_eigenvars_C_up = 0;
   weight_bTagSF_85_eigenvars_Light_up = 0;
   weight_bTagSF_85_eigenvars_B_down = 0;
   weight_bTagSF_85_eigenvars_C_down = 0;
   weight_bTagSF_85_eigenvars_Light_down = 0;
   weight_bTagSF_77_eigenvars_B_up = 0;
   weight_bTagSF_77_eigenvars_C_up = 0;
   weight_bTagSF_77_eigenvars_Light_up = 0;
   weight_bTagSF_77_eigenvars_B_down = 0;
   weight_bTagSF_77_eigenvars_C_down = 0;
   weight_bTagSF_77_eigenvars_Light_down = 0;
   weight_bTagSF_70_eigenvars_B_up = 0;
   weight_bTagSF_70_eigenvars_C_up = 0;
   weight_bTagSF_70_eigenvars_Light_up = 0;
   weight_bTagSF_70_eigenvars_B_down = 0;
   weight_bTagSF_70_eigenvars_C_down = 0;
   weight_bTagSF_70_eigenvars_Light_down = 0;
   weight_bTagSF_60_eigenvars_B_up = 0;
   weight_bTagSF_60_eigenvars_C_up = 0;
   weight_bTagSF_60_eigenvars_Light_up = 0;
   weight_bTagSF_60_eigenvars_B_down = 0;
   weight_bTagSF_60_eigenvars_C_down = 0;
   weight_bTagSF_60_eigenvars_Light_down = 0;
   el_pt = 0;
   el_eta = 0;
   el_cl_eta = 0;
   el_phi = 0;
   el_e = 0;
   el_charge = 0;
   el_topoetcone20 = 0;
   el_ptvarcone20 = 0;
   el_d0sig = 0;
   el_delta_z0_sintheta = 0;
   mu_pt = 0;
   mu_eta = 0;
   mu_phi = 0;
   mu_e = 0;
   mu_charge = 0;
   mu_topoetcone20 = 0;
   mu_ptvarcone30 = 0;
   mu_d0sig = 0;
   mu_delta_z0_sintheta = 0;
   jet_pt = 0;
   jet_eta = 0;
   jet_phi = 0;
   jet_e = 0;
   jet_mv1 = 0;
   jet_mvb = 0;
   jet_mv1c = 0;
   jet_mv2c00 = 0;
   jet_mv2c10 = 0;
   jet_mv2c20 = 0;
   jet_ip3dsv1 = 0;
   jet_jvt = 0;
   el_trigMatch_HLT_e60_lhmedium = 0;
   el_trigMatch_HLT_e24_lhmedium_iloose_L1EM20VH = 0;
   el_trigMatch_HLT_e24_lhmedium_L1EM20VH = 0;
   el_trigMatch_HLT_e24_lhmedium_L1EM18VH = 0;
   el_trigMatch_HLT_e120_lhloose = 0;
   mu_trigMatch_HLT_mu50 = 0;
   mu_trigMatch_HLT_mu20_iloose_L1MU15 = 0;
   mu_trigMatch_HLT_mu20_L1MU15 = 0;
   el_LHLoose = 0;
   el_LHMedium = 0;
   el_LHTight = 0;
   el_isoGradient = 0;
   el_isoGradientLoose = 0;
   el_isoTight = 0;
   el_isoLoose = 0;
   el_isoLooseTrackOnly = 0;
   el_isoFixedCutTight = 0;
   el_isoFixedCutTightTrackOnly = 0;
   el_isoFixedCutLoose = 0;
   el_d0PV = 0;
   el_z0PV = 0;
   el_d0sigPV = 0;
   el_z0sigPV = 0;
   el_topoetcone30 = 0;
   el_topoetcone40 = 0;
   el_ptcone30 = 0;
   el_ptcone40 = 0;
   el_MT = 0;
   el_dRClosetJet = 0;
   el_dRClosetJet_WithFwds = 0;
   el_PtClosetJet = 0;
   el_PtClosetJet_WithFwds = 0;
   el_dROverPtClosetJet = 0;
   el_dROverPtClosetJet_WithFwds = 0;
   el_dPhiMET = 0;
   el_trigMatch = 0;
   el_true_type = 0;
   el_true_origin = 0;
   el_true_typebkg = 0;
   el_true_originbkg = 0;
   el_true_pdg = 0;
   el_true_pt = 0;
   el_true_eta = 0;
   el_true_phi = 0;
   el_f3core = 0;
   el_nBL = 0;
   el_nPix = 0;
   mu_Tight = 0;
   mu_Medium = 0;
   mu_Loose = 0;
   mu_isoGradient = 0;
   mu_isoGradientLoose = 0;
   mu_isoTight = 0;
   mu_isoLoose = 0;
   mu_isoLooseTrackOnly = 0;
   mu_isoFixedCutTightTrackOnly = 0;
   mu_isoFixedCutLoose = 0;
   mu_d0PV = 0;
   mu_z0PV = 0;
   mu_d0sigPV = 0;
   mu_z0sigPV = 0;
   mu_topoetcone30 = 0;
   mu_topoetcone40 = 0;
   mu_ptcone30 = 0;
   mu_ptcone40 = 0;
   mu_MT = 0;
   mu_dRClosetJet = 0;
   mu_dRClosetJet_WithFwds = 0;
   mu_PtClosetJet = 0;
   mu_PtClosetJet_WithFwds = 0;
   mu_dROverPtClosetJet = 0;
   mu_dROverPtClosetJet_WithFwds = 0;
   mu_dPhiMET = 0;
   mu_trigMatch = 0;
   mu_true_type = 0;
   mu_true_origin = 0;
   mu_true_pdg = 0;
   mu_true_pt = 0;
   mu_true_eta = 0;
   mu_true_phi = 0;
   jet_m = 0;
   jet_isFwd = 0;
   jet_isbtagged_60 = 0;
   jet_isbtagged_70 = 0;
   jet_isbtagged_77 = 0;
   jet_isbtagged_85 = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("weight_mc", &weight_mc, &b_weight_mc);
   fChain->SetBranchAddress("weight_pileup", &weight_pileup, &b_weight_pileup);
   fChain->SetBranchAddress("weight_leptonSF", &weight_leptonSF, &b_weight_leptonSF);
   fChain->SetBranchAddress("weight_bTagSF_85", &weight_bTagSF_85, &b_weight_bTagSF_85);
   fChain->SetBranchAddress("weight_bTagSF_77", &weight_bTagSF_77, &b_weight_bTagSF_77);
   fChain->SetBranchAddress("weight_bTagSF_70", &weight_bTagSF_70, &b_weight_bTagSF_70);
   fChain->SetBranchAddress("weight_bTagSF_60", &weight_bTagSF_60, &b_weight_bTagSF_60);
   fChain->SetBranchAddress("weight_pileup_UP", &weight_pileup_UP, &b_weight_pileup_UP);
   fChain->SetBranchAddress("weight_pileup_DOWN", &weight_pileup_DOWN, &b_weight_pileup_DOWN);
   fChain->SetBranchAddress("weight_leptonSF_EL_SF_Trigger_UP", &weight_leptonSF_EL_SF_Trigger_UP, &b_weight_leptonSF_EL_SF_Trigger_UP);
   fChain->SetBranchAddress("weight_leptonSF_EL_SF_Trigger_DOWN", &weight_leptonSF_EL_SF_Trigger_DOWN, &b_weight_leptonSF_EL_SF_Trigger_DOWN);
   fChain->SetBranchAddress("weight_leptonSF_EL_SF_Reco_UP", &weight_leptonSF_EL_SF_Reco_UP, &b_weight_leptonSF_EL_SF_Reco_UP);
   fChain->SetBranchAddress("weight_leptonSF_EL_SF_Reco_DOWN", &weight_leptonSF_EL_SF_Reco_DOWN, &b_weight_leptonSF_EL_SF_Reco_DOWN);
   fChain->SetBranchAddress("weight_leptonSF_EL_SF_ID_UP", &weight_leptonSF_EL_SF_ID_UP, &b_weight_leptonSF_EL_SF_ID_UP);
   fChain->SetBranchAddress("weight_leptonSF_EL_SF_ID_DOWN", &weight_leptonSF_EL_SF_ID_DOWN, &b_weight_leptonSF_EL_SF_ID_DOWN);
   fChain->SetBranchAddress("weight_leptonSF_EL_SF_Isol_UP", &weight_leptonSF_EL_SF_Isol_UP, &b_weight_leptonSF_EL_SF_Isol_UP);
   fChain->SetBranchAddress("weight_leptonSF_EL_SF_Isol_DOWN", &weight_leptonSF_EL_SF_Isol_DOWN, &b_weight_leptonSF_EL_SF_Isol_DOWN);
   fChain->SetBranchAddress("weight_leptonSF_MU_SF_Trigger_STAT_UP", &weight_leptonSF_MU_SF_Trigger_STAT_UP, &b_weight_leptonSF_MU_SF_Trigger_STAT_UP);
   fChain->SetBranchAddress("weight_leptonSF_MU_SF_Trigger_STAT_DOWN", &weight_leptonSF_MU_SF_Trigger_STAT_DOWN, &b_weight_leptonSF_MU_SF_Trigger_STAT_DOWN);
   fChain->SetBranchAddress("weight_leptonSF_MU_SF_Trigger_SYST_UP", &weight_leptonSF_MU_SF_Trigger_SYST_UP, &b_weight_leptonSF_MU_SF_Trigger_SYST_UP);
   fChain->SetBranchAddress("weight_leptonSF_MU_SF_Trigger_SYST_DOWN", &weight_leptonSF_MU_SF_Trigger_SYST_DOWN, &b_weight_leptonSF_MU_SF_Trigger_SYST_DOWN);
   fChain->SetBranchAddress("weight_leptonSF_MU_SF_ID_STAT_UP", &weight_leptonSF_MU_SF_ID_STAT_UP, &b_weight_leptonSF_MU_SF_ID_STAT_UP);
   fChain->SetBranchAddress("weight_leptonSF_MU_SF_ID_STAT_DOWN", &weight_leptonSF_MU_SF_ID_STAT_DOWN, &b_weight_leptonSF_MU_SF_ID_STAT_DOWN);
   fChain->SetBranchAddress("weight_leptonSF_MU_SF_ID_SYST_UP", &weight_leptonSF_MU_SF_ID_SYST_UP, &b_weight_leptonSF_MU_SF_ID_SYST_UP);
   fChain->SetBranchAddress("weight_leptonSF_MU_SF_ID_SYST_DOWN", &weight_leptonSF_MU_SF_ID_SYST_DOWN, &b_weight_leptonSF_MU_SF_ID_SYST_DOWN);
   fChain->SetBranchAddress("weight_leptonSF_MU_SF_Isol_STAT_UP", &weight_leptonSF_MU_SF_Isol_STAT_UP, &b_weight_leptonSF_MU_SF_Isol_STAT_UP);
   fChain->SetBranchAddress("weight_leptonSF_MU_SF_Isol_STAT_DOWN", &weight_leptonSF_MU_SF_Isol_STAT_DOWN, &b_weight_leptonSF_MU_SF_Isol_STAT_DOWN);
   fChain->SetBranchAddress("weight_leptonSF_MU_SF_Isol_SYST_UP", &weight_leptonSF_MU_SF_Isol_SYST_UP, &b_weight_leptonSF_MU_SF_Isol_SYST_UP);
   fChain->SetBranchAddress("weight_leptonSF_MU_SF_Isol_SYST_DOWN", &weight_leptonSF_MU_SF_Isol_SYST_DOWN, &b_weight_leptonSF_MU_SF_Isol_SYST_DOWN);
   fChain->SetBranchAddress("weight_indiv_SF_EL_Trigger", &weight_indiv_SF_EL_Trigger, &b_weight_indiv_SF_EL_Trigger);
   fChain->SetBranchAddress("weight_indiv_SF_EL_Trigger_UP", &weight_indiv_SF_EL_Trigger_UP, &b_weight_indiv_SF_EL_Trigger_UP);
   fChain->SetBranchAddress("weight_indiv_SF_EL_Trigger_DOWN", &weight_indiv_SF_EL_Trigger_DOWN, &b_weight_indiv_SF_EL_Trigger_DOWN);
   fChain->SetBranchAddress("weight_indiv_SF_EL_Reco", &weight_indiv_SF_EL_Reco, &b_weight_indiv_SF_EL_Reco);
   fChain->SetBranchAddress("weight_indiv_SF_EL_Reco_UP", &weight_indiv_SF_EL_Reco_UP, &b_weight_indiv_SF_EL_Reco_UP);
   fChain->SetBranchAddress("weight_indiv_SF_EL_Reco_DOWN", &weight_indiv_SF_EL_Reco_DOWN, &b_weight_indiv_SF_EL_Reco_DOWN);
   fChain->SetBranchAddress("weight_indiv_SF_EL_ID", &weight_indiv_SF_EL_ID, &b_weight_indiv_SF_EL_ID);
   fChain->SetBranchAddress("weight_indiv_SF_EL_ID_UP", &weight_indiv_SF_EL_ID_UP, &b_weight_indiv_SF_EL_ID_UP);
   fChain->SetBranchAddress("weight_indiv_SF_EL_ID_DOWN", &weight_indiv_SF_EL_ID_DOWN, &b_weight_indiv_SF_EL_ID_DOWN);
   fChain->SetBranchAddress("weight_indiv_SF_EL_Isol", &weight_indiv_SF_EL_Isol, &b_weight_indiv_SF_EL_Isol);
   fChain->SetBranchAddress("weight_indiv_SF_EL_Isol_UP", &weight_indiv_SF_EL_Isol_UP, &b_weight_indiv_SF_EL_Isol_UP);
   fChain->SetBranchAddress("weight_indiv_SF_EL_Isol_DOWN", &weight_indiv_SF_EL_Isol_DOWN, &b_weight_indiv_SF_EL_Isol_DOWN);
   fChain->SetBranchAddress("weight_indiv_SF_MU_Trigger", &weight_indiv_SF_MU_Trigger, &b_weight_indiv_SF_MU_Trigger);
   fChain->SetBranchAddress("weight_indiv_SF_MU_Trigger_STAT_UP", &weight_indiv_SF_MU_Trigger_STAT_UP, &b_weight_indiv_SF_MU_Trigger_STAT_UP);
   fChain->SetBranchAddress("weight_indiv_SF_MU_Trigger_STAT_DOWN", &weight_indiv_SF_MU_Trigger_STAT_DOWN, &b_weight_indiv_SF_MU_Trigger_STAT_DOWN);
   fChain->SetBranchAddress("weight_indiv_SF_MU_Trigger_SYST_UP", &weight_indiv_SF_MU_Trigger_SYST_UP, &b_weight_indiv_SF_MU_Trigger_SYST_UP);
   fChain->SetBranchAddress("weight_indiv_SF_MU_Trigger_SYST_DOWN", &weight_indiv_SF_MU_Trigger_SYST_DOWN, &b_weight_indiv_SF_MU_Trigger_SYST_DOWN);
   fChain->SetBranchAddress("weight_indiv_SF_MU_ID", &weight_indiv_SF_MU_ID, &b_weight_indiv_SF_MU_ID);
   fChain->SetBranchAddress("weight_indiv_SF_MU_ID_STAT_UP", &weight_indiv_SF_MU_ID_STAT_UP, &b_weight_indiv_SF_MU_ID_STAT_UP);
   fChain->SetBranchAddress("weight_indiv_SF_MU_ID_STAT_DOWN", &weight_indiv_SF_MU_ID_STAT_DOWN, &b_weight_indiv_SF_MU_ID_STAT_DOWN);
   fChain->SetBranchAddress("weight_indiv_SF_MU_ID_SYST_UP", &weight_indiv_SF_MU_ID_SYST_UP, &b_weight_indiv_SF_MU_ID_SYST_UP);
   fChain->SetBranchAddress("weight_indiv_SF_MU_ID_SYST_DOWN", &weight_indiv_SF_MU_ID_SYST_DOWN, &b_weight_indiv_SF_MU_ID_SYST_DOWN);
   fChain->SetBranchAddress("weight_indiv_SF_MU_Isol", &weight_indiv_SF_MU_Isol, &b_weight_indiv_SF_MU_Isol);
   fChain->SetBranchAddress("weight_indiv_SF_MU_Isol_STAT_UP", &weight_indiv_SF_MU_Isol_STAT_UP, &b_weight_indiv_SF_MU_Isol_STAT_UP);
   fChain->SetBranchAddress("weight_indiv_SF_MU_Isol_STAT_DOWN", &weight_indiv_SF_MU_Isol_STAT_DOWN, &b_weight_indiv_SF_MU_Isol_STAT_DOWN);
   fChain->SetBranchAddress("weight_indiv_SF_MU_Isol_SYST_UP", &weight_indiv_SF_MU_Isol_SYST_UP, &b_weight_indiv_SF_MU_Isol_SYST_UP);
   fChain->SetBranchAddress("weight_indiv_SF_MU_Isol_SYST_DOWN", &weight_indiv_SF_MU_Isol_SYST_DOWN, &b_weight_indiv_SF_MU_Isol_SYST_DOWN);
   fChain->SetBranchAddress("weight_bTagSF_85_eigenvars_B_up", &weight_bTagSF_85_eigenvars_B_up, &b_weight_bTagSF_85_eigenvars_B_up);
   fChain->SetBranchAddress("weight_bTagSF_85_eigenvars_C_up", &weight_bTagSF_85_eigenvars_C_up, &b_weight_bTagSF_85_eigenvars_C_up);
   fChain->SetBranchAddress("weight_bTagSF_85_eigenvars_Light_up", &weight_bTagSF_85_eigenvars_Light_up, &b_weight_bTagSF_85_eigenvars_Light_up);
   fChain->SetBranchAddress("weight_bTagSF_85_eigenvars_B_down", &weight_bTagSF_85_eigenvars_B_down, &b_weight_bTagSF_85_eigenvars_B_down);
   fChain->SetBranchAddress("weight_bTagSF_85_eigenvars_C_down", &weight_bTagSF_85_eigenvars_C_down, &b_weight_bTagSF_85_eigenvars_C_down);
   fChain->SetBranchAddress("weight_bTagSF_85_eigenvars_Light_down", &weight_bTagSF_85_eigenvars_Light_down, &b_weight_bTagSF_85_eigenvars_Light_down);
   fChain->SetBranchAddress("weight_bTagSF_85_extrapolation_up", &weight_bTagSF_85_extrapolation_up, &b_weight_bTagSF_85_extrapolation_up);
   fChain->SetBranchAddress("weight_bTagSF_85_extrapolation_down", &weight_bTagSF_85_extrapolation_down, &b_weight_bTagSF_85_extrapolation_down);
   fChain->SetBranchAddress("weight_bTagSF_85_extrapolation_from_charm_up", &weight_bTagSF_85_extrapolation_from_charm_up, &b_weight_bTagSF_85_extrapolation_from_charm_up);
   fChain->SetBranchAddress("weight_bTagSF_85_extrapolation_from_charm_down", &weight_bTagSF_85_extrapolation_from_charm_down, &b_weight_bTagSF_85_extrapolation_from_charm_down);
   fChain->SetBranchAddress("weight_bTagSF_77_eigenvars_B_up", &weight_bTagSF_77_eigenvars_B_up, &b_weight_bTagSF_77_eigenvars_B_up);
   fChain->SetBranchAddress("weight_bTagSF_77_eigenvars_C_up", &weight_bTagSF_77_eigenvars_C_up, &b_weight_bTagSF_77_eigenvars_C_up);
   fChain->SetBranchAddress("weight_bTagSF_77_eigenvars_Light_up", &weight_bTagSF_77_eigenvars_Light_up, &b_weight_bTagSF_77_eigenvars_Light_up);
   fChain->SetBranchAddress("weight_bTagSF_77_eigenvars_B_down", &weight_bTagSF_77_eigenvars_B_down, &b_weight_bTagSF_77_eigenvars_B_down);
   fChain->SetBranchAddress("weight_bTagSF_77_eigenvars_C_down", &weight_bTagSF_77_eigenvars_C_down, &b_weight_bTagSF_77_eigenvars_C_down);
   fChain->SetBranchAddress("weight_bTagSF_77_eigenvars_Light_down", &weight_bTagSF_77_eigenvars_Light_down, &b_weight_bTagSF_77_eigenvars_Light_down);
   fChain->SetBranchAddress("weight_bTagSF_77_extrapolation_up", &weight_bTagSF_77_extrapolation_up, &b_weight_bTagSF_77_extrapolation_up);
   fChain->SetBranchAddress("weight_bTagSF_77_extrapolation_down", &weight_bTagSF_77_extrapolation_down, &b_weight_bTagSF_77_extrapolation_down);
   fChain->SetBranchAddress("weight_bTagSF_77_extrapolation_from_charm_up", &weight_bTagSF_77_extrapolation_from_charm_up, &b_weight_bTagSF_77_extrapolation_from_charm_up);
   fChain->SetBranchAddress("weight_bTagSF_77_extrapolation_from_charm_down", &weight_bTagSF_77_extrapolation_from_charm_down, &b_weight_bTagSF_77_extrapolation_from_charm_down);
   fChain->SetBranchAddress("weight_bTagSF_70_eigenvars_B_up", &weight_bTagSF_70_eigenvars_B_up, &b_weight_bTagSF_70_eigenvars_B_up);
   fChain->SetBranchAddress("weight_bTagSF_70_eigenvars_C_up", &weight_bTagSF_70_eigenvars_C_up, &b_weight_bTagSF_70_eigenvars_C_up);
   fChain->SetBranchAddress("weight_bTagSF_70_eigenvars_Light_up", &weight_bTagSF_70_eigenvars_Light_up, &b_weight_bTagSF_70_eigenvars_Light_up);
   fChain->SetBranchAddress("weight_bTagSF_70_eigenvars_B_down", &weight_bTagSF_70_eigenvars_B_down, &b_weight_bTagSF_70_eigenvars_B_down);
   fChain->SetBranchAddress("weight_bTagSF_70_eigenvars_C_down", &weight_bTagSF_70_eigenvars_C_down, &b_weight_bTagSF_70_eigenvars_C_down);
   fChain->SetBranchAddress("weight_bTagSF_70_eigenvars_Light_down", &weight_bTagSF_70_eigenvars_Light_down, &b_weight_bTagSF_70_eigenvars_Light_down);
   fChain->SetBranchAddress("weight_bTagSF_70_extrapolation_up", &weight_bTagSF_70_extrapolation_up, &b_weight_bTagSF_70_extrapolation_up);
   fChain->SetBranchAddress("weight_bTagSF_70_extrapolation_down", &weight_bTagSF_70_extrapolation_down, &b_weight_bTagSF_70_extrapolation_down);
   fChain->SetBranchAddress("weight_bTagSF_70_extrapolation_from_charm_up", &weight_bTagSF_70_extrapolation_from_charm_up, &b_weight_bTagSF_70_extrapolation_from_charm_up);
   fChain->SetBranchAddress("weight_bTagSF_70_extrapolation_from_charm_down", &weight_bTagSF_70_extrapolation_from_charm_down, &b_weight_bTagSF_70_extrapolation_from_charm_down);
   fChain->SetBranchAddress("weight_bTagSF_60_eigenvars_B_up", &weight_bTagSF_60_eigenvars_B_up, &b_weight_bTagSF_60_eigenvars_B_up);
   fChain->SetBranchAddress("weight_bTagSF_60_eigenvars_C_up", &weight_bTagSF_60_eigenvars_C_up, &b_weight_bTagSF_60_eigenvars_C_up);
   fChain->SetBranchAddress("weight_bTagSF_60_eigenvars_Light_up", &weight_bTagSF_60_eigenvars_Light_up, &b_weight_bTagSF_60_eigenvars_Light_up);
   fChain->SetBranchAddress("weight_bTagSF_60_eigenvars_B_down", &weight_bTagSF_60_eigenvars_B_down, &b_weight_bTagSF_60_eigenvars_B_down);
   fChain->SetBranchAddress("weight_bTagSF_60_eigenvars_C_down", &weight_bTagSF_60_eigenvars_C_down, &b_weight_bTagSF_60_eigenvars_C_down);
   fChain->SetBranchAddress("weight_bTagSF_60_eigenvars_Light_down", &weight_bTagSF_60_eigenvars_Light_down, &b_weight_bTagSF_60_eigenvars_Light_down);
   fChain->SetBranchAddress("weight_bTagSF_60_extrapolation_up", &weight_bTagSF_60_extrapolation_up, &b_weight_bTagSF_60_extrapolation_up);
   fChain->SetBranchAddress("weight_bTagSF_60_extrapolation_down", &weight_bTagSF_60_extrapolation_down, &b_weight_bTagSF_60_extrapolation_down);
   fChain->SetBranchAddress("weight_bTagSF_60_extrapolation_from_charm_up", &weight_bTagSF_60_extrapolation_from_charm_up, &b_weight_bTagSF_60_extrapolation_from_charm_up);
   fChain->SetBranchAddress("weight_bTagSF_60_extrapolation_from_charm_down", &weight_bTagSF_60_extrapolation_from_charm_down, &b_weight_bTagSF_60_extrapolation_from_charm_down);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("mcChannelNumber", &mcChannelNumber, &b_mcChannelNumber);
   fChain->SetBranchAddress("mu", &mu, &b_mu);
   fChain->SetBranchAddress("el_pt", &el_pt, &b_el_pt);
   fChain->SetBranchAddress("el_eta", &el_eta, &b_el_eta);
   fChain->SetBranchAddress("el_cl_eta", &el_cl_eta, &b_el_cl_eta);
   fChain->SetBranchAddress("el_phi", &el_phi, &b_el_phi);
   fChain->SetBranchAddress("el_e", &el_e, &b_el_e);
   fChain->SetBranchAddress("el_charge", &el_charge, &b_el_charge);
   fChain->SetBranchAddress("el_topoetcone20", &el_topoetcone20, &b_el_topoetcone20);
   fChain->SetBranchAddress("el_ptvarcone20", &el_ptvarcone20, &b_el_ptvarcone20);
   fChain->SetBranchAddress("el_d0sig", &el_d0sig, &b_el_d0sig);
   fChain->SetBranchAddress("el_delta_z0_sintheta", &el_delta_z0_sintheta, &b_el_delta_z0_sintheta);
   fChain->SetBranchAddress("mu_pt", &mu_pt, &b_mu_pt);
   fChain->SetBranchAddress("mu_eta", &mu_eta, &b_mu_eta);
   fChain->SetBranchAddress("mu_phi", &mu_phi, &b_mu_phi);
   fChain->SetBranchAddress("mu_e", &mu_e, &b_mu_e);
   fChain->SetBranchAddress("mu_charge", &mu_charge, &b_mu_charge);
   fChain->SetBranchAddress("mu_topoetcone20", &mu_topoetcone20, &b_mu_topoetcone20);
   fChain->SetBranchAddress("mu_ptvarcone30", &mu_ptvarcone30, &b_mu_ptvarcone30);
   fChain->SetBranchAddress("mu_d0sig", &mu_d0sig, &b_mu_d0sig);
   fChain->SetBranchAddress("mu_delta_z0_sintheta", &mu_delta_z0_sintheta, &b_mu_delta_z0_sintheta);
   fChain->SetBranchAddress("jet_pt", &jet_pt, &b_jet_pt);
   fChain->SetBranchAddress("jet_eta", &jet_eta, &b_jet_eta);
   fChain->SetBranchAddress("jet_phi", &jet_phi, &b_jet_phi);
   fChain->SetBranchAddress("jet_e", &jet_e, &b_jet_e);
   fChain->SetBranchAddress("jet_mv1", &jet_mv1, &b_jet_mv1);
   fChain->SetBranchAddress("jet_mvb", &jet_mvb, &b_jet_mvb);
   fChain->SetBranchAddress("jet_mv1c", &jet_mv1c, &b_jet_mv1c);
   fChain->SetBranchAddress("jet_mv2c00", &jet_mv2c00, &b_jet_mv2c00);
   fChain->SetBranchAddress("jet_mv2c10", &jet_mv2c10, &b_jet_mv2c10);
   fChain->SetBranchAddress("jet_mv2c20", &jet_mv2c20, &b_jet_mv2c20);
   fChain->SetBranchAddress("jet_ip3dsv1", &jet_ip3dsv1, &b_jet_ip3dsv1);
   fChain->SetBranchAddress("jet_jvt", &jet_jvt, &b_jet_jvt);
   fChain->SetBranchAddress("met_met", &met_met, &b_met_met);
   fChain->SetBranchAddress("met_phi", &met_phi, &b_met_phi);
   fChain->SetBranchAddress("ejets", &ejets, &b_ejets);
   fChain->SetBranchAddress("mujets", &mujets, &b_mujets);
   fChain->SetBranchAddress("ee", &ee, &b_ee);
   fChain->SetBranchAddress("mumu", &mumu, &b_mumu);
   fChain->SetBranchAddress("emu", &emu, &b_emu);
   fChain->SetBranchAddress("HLT_mu20_iloose_L1MU15", &HLT_mu20_iloose_L1MU15, &b_HLT_mu20_iloose_L1MU15);
   fChain->SetBranchAddress("HLT_mu20_L1MU15", &HLT_mu20_L1MU15, &b_HLT_mu20_L1MU15);
   fChain->SetBranchAddress("HLT_mu50", &HLT_mu50, &b_HLT_mu50);
   fChain->SetBranchAddress("HLT_e60_lhmedium", &HLT_e60_lhmedium, &b_HLT_e60_lhmedium);
   fChain->SetBranchAddress("HLT_e24_lhmedium_iloose_L1EM20VH", &HLT_e24_lhmedium_iloose_L1EM20VH, &b_HLT_e24_lhmedium_iloose_L1EM20VH);
   fChain->SetBranchAddress("HLT_e24_lhmedium_L1EM20VH", &HLT_e24_lhmedium_L1EM20VH, &b_HLT_e24_lhmedium_L1EM20VH);
   fChain->SetBranchAddress("HLT_e24_lhmedium_L1EM18VH", &HLT_e24_lhmedium_L1EM18VH, &b_HLT_e24_lhmedium_L1EM18VH);
   fChain->SetBranchAddress("HLT_e120_lhloose", &HLT_e120_lhloose, &b_HLT_e120_lhloose);
   fChain->SetBranchAddress("el_trigMatch_HLT_e60_lhmedium", &el_trigMatch_HLT_e60_lhmedium, &b_el_trigMatch_HLT_e60_lhmedium);
   fChain->SetBranchAddress("el_trigMatch_HLT_e24_lhmedium_iloose_L1EM20VH", &el_trigMatch_HLT_e24_lhmedium_iloose_L1EM20VH, &b_el_trigMatch_HLT_e24_lhmedium_iloose_L1EM20VH);
   fChain->SetBranchAddress("el_trigMatch_HLT_e24_lhmedium_L1EM20VH", &el_trigMatch_HLT_e24_lhmedium_L1EM20VH, &b_el_trigMatch_HLT_e24_lhmedium_L1EM20VH);
   fChain->SetBranchAddress("el_trigMatch_HLT_e24_lhmedium_L1EM18VH", &el_trigMatch_HLT_e24_lhmedium_L1EM18VH, &b_el_trigMatch_HLT_e24_lhmedium_L1EM18VH);
   fChain->SetBranchAddress("el_trigMatch_HLT_e120_lhloose", &el_trigMatch_HLT_e120_lhloose, &b_el_trigMatch_HLT_e120_lhloose);
   fChain->SetBranchAddress("mu_trigMatch_HLT_mu50", &mu_trigMatch_HLT_mu50, &b_mu_trigMatch_HLT_mu50);
   fChain->SetBranchAddress("mu_trigMatch_HLT_mu20_iloose_L1MU15", &mu_trigMatch_HLT_mu20_iloose_L1MU15, &b_mu_trigMatch_HLT_mu20_iloose_L1MU15);
   fChain->SetBranchAddress("mu_trigMatch_HLT_mu20_L1MU15", &mu_trigMatch_HLT_mu20_L1MU15, &b_mu_trigMatch_HLT_mu20_L1MU15);
   fChain->SetBranchAddress("lbn", &lbn, &b_lbn);
   fChain->SetBranchAddress("Vtxz", &Vtxz, &b_Vtxz);
   fChain->SetBranchAddress("npVtx", &npVtx, &b_npVtx);
   fChain->SetBranchAddress("el_n", &el_n, &b_el_n);
   fChain->SetBranchAddress("el_LHLoose", &el_LHLoose, &b_el_LHLoose);
   fChain->SetBranchAddress("el_LHMedium", &el_LHMedium, &b_el_LHMedium);
   fChain->SetBranchAddress("el_LHTight", &el_LHTight, &b_el_LHTight);
   fChain->SetBranchAddress("el_isoGradient", &el_isoGradient, &b_el_isoGradient);
   fChain->SetBranchAddress("el_isoGradientLoose", &el_isoGradientLoose, &b_el_isoGradientLoose);
   fChain->SetBranchAddress("el_isoTight", &el_isoTight, &b_el_isoTight);
   fChain->SetBranchAddress("el_isoLoose", &el_isoLoose, &b_el_isoLoose);
   fChain->SetBranchAddress("el_isoLooseTrackOnly", &el_isoLooseTrackOnly, &b_el_isoLooseTrackOnly);
   fChain->SetBranchAddress("el_isoFixedCutTight", &el_isoFixedCutTight, &b_el_isoFixedCutTight);
   fChain->SetBranchAddress("el_isoFixedCutTightTrackOnly", &el_isoFixedCutTightTrackOnly, &b_el_isoFixedCutTightTrackOnly);
   fChain->SetBranchAddress("el_isoFixedCutLoose", &el_isoFixedCutLoose, &b_el_isoFixedCutLoose);
   fChain->SetBranchAddress("el_d0PV", &el_d0PV, &b_el_d0PV);
   fChain->SetBranchAddress("el_z0PV", &el_z0PV, &b_el_z0PV);
   fChain->SetBranchAddress("el_d0sigPV", &el_d0sigPV, &b_el_d0sigPV);
   fChain->SetBranchAddress("el_z0sigPV", &el_z0sigPV, &b_el_z0sigPV);
   fChain->SetBranchAddress("el_topoetcone30", &el_topoetcone30, &b_el_topoetcone30);
   fChain->SetBranchAddress("el_topoetcone40", &el_topoetcone40, &b_el_topoetcone40);
   fChain->SetBranchAddress("el_ptcone30", &el_ptcone30, &b_el_ptcone30);
   fChain->SetBranchAddress("el_ptcone40", &el_ptcone40, &b_el_ptcone40);
   fChain->SetBranchAddress("el_MT", &el_MT, &b_el_MT);
   fChain->SetBranchAddress("el_dRClosetJet", &el_dRClosetJet, &b_el_dRClosetJet);
   fChain->SetBranchAddress("el_dRClosetJet_WithFwds", &el_dRClosetJet_WithFwds, &b_el_dRClosetJet_WithFwds);
   fChain->SetBranchAddress("el_PtClosetJet", &el_PtClosetJet, &b_el_PtClosetJet);
   fChain->SetBranchAddress("el_PtClosetJet_WithFwds", &el_PtClosetJet_WithFwds, &b_el_PtClosetJet_WithFwds);
   fChain->SetBranchAddress("el_dROverPtClosetJet", &el_dROverPtClosetJet, &b_el_dROverPtClosetJet);
   fChain->SetBranchAddress("el_dROverPtClosetJet_WithFwds", &el_dROverPtClosetJet_WithFwds, &b_el_dROverPtClosetJet_WithFwds);
   fChain->SetBranchAddress("el_dPhiMET", &el_dPhiMET, &b_el_dPhiMET);
   fChain->SetBranchAddress("el_trigMatch", &el_trigMatch, &b_el_trigMatch);
   fChain->SetBranchAddress("el_true_type", &el_true_type, &b_el_true_type);
   fChain->SetBranchAddress("el_true_origin", &el_true_origin, &b_el_true_origin);
   fChain->SetBranchAddress("el_true_typebkg", &el_true_typebkg, &b_el_true_typebkg);
   fChain->SetBranchAddress("el_true_originbkg", &el_true_originbkg, &b_el_true_originbkg);
   fChain->SetBranchAddress("el_true_pdg", &el_true_pdg, &b_el_true_pdg);
   fChain->SetBranchAddress("el_true_pt", &el_true_pt, &b_el_true_pt);
   fChain->SetBranchAddress("el_true_eta", &el_true_eta, &b_el_true_eta);
   fChain->SetBranchAddress("el_true_phi", &el_true_phi, &b_el_true_phi);
   fChain->SetBranchAddress("el_f3core", &el_f3core, &b_el_f3core);
   fChain->SetBranchAddress("el_nBL", &el_nBL, &b_el_nBL);
   fChain->SetBranchAddress("el_nPix", &el_nPix, &b_el_nPix);
   fChain->SetBranchAddress("mu_n", &mu_n, &b_mu_n);
   fChain->SetBranchAddress("mu_Tight", &mu_Tight, &b_mu_Tight);
   fChain->SetBranchAddress("mu_Medium", &mu_Medium, &b_mu_Medium);
   fChain->SetBranchAddress("mu_Loose", &mu_Loose, &b_mu_Loose);
   fChain->SetBranchAddress("mu_isoGradient", &mu_isoGradient, &b_mu_isoGradient);
   fChain->SetBranchAddress("mu_isoGradientLoose", &mu_isoGradientLoose, &b_mu_isoGradientLoose);
   fChain->SetBranchAddress("mu_isoTight", &mu_isoTight, &b_mu_isoTight);
   fChain->SetBranchAddress("mu_isoLoose", &mu_isoLoose, &b_mu_isoLoose);
   fChain->SetBranchAddress("mu_isoLooseTrackOnly", &mu_isoLooseTrackOnly, &b_mu_isoLooseTrackOnly);
   fChain->SetBranchAddress("mu_isoFixedCutTightTrackOnly", &mu_isoFixedCutTightTrackOnly, &b_mu_isoFixedCutTightTrackOnly);
   fChain->SetBranchAddress("mu_isoFixedCutLoose", &mu_isoFixedCutLoose, &b_mu_isoFixedCutLoose);
   fChain->SetBranchAddress("mu_d0PV", &mu_d0PV, &b_mu_d0PV);
   fChain->SetBranchAddress("mu_z0PV", &mu_z0PV, &b_mu_z0PV);
   fChain->SetBranchAddress("mu_d0sigPV", &mu_d0sigPV, &b_mu_d0sigPV);
   fChain->SetBranchAddress("mu_z0sigPV", &mu_z0sigPV, &b_mu_z0sigPV);
   fChain->SetBranchAddress("mu_topoetcone30", &mu_topoetcone30, &b_mu_topoetcone30);
   fChain->SetBranchAddress("mu_topoetcone40", &mu_topoetcone40, &b_mu_topoetcone40);
   fChain->SetBranchAddress("mu_ptcone30", &mu_ptcone30, &b_mu_ptcone30);
   fChain->SetBranchAddress("mu_ptcone40", &mu_ptcone40, &b_mu_ptcone40);
   fChain->SetBranchAddress("mu_MT", &mu_MT, &b_mu_MT);
   fChain->SetBranchAddress("mu_dRClosetJet", &mu_dRClosetJet, &b_mu_dRClosetJet);
   fChain->SetBranchAddress("mu_dRClosetJet_WithFwds", &mu_dRClosetJet_WithFwds, &b_mu_dRClosetJet_WithFwds);
   fChain->SetBranchAddress("mu_PtClosetJet", &mu_PtClosetJet, &b_mu_PtClosetJet);
   fChain->SetBranchAddress("mu_PtClosetJet_WithFwds", &mu_PtClosetJet_WithFwds, &b_mu_PtClosetJet_WithFwds);
   fChain->SetBranchAddress("mu_dROverPtClosetJet", &mu_dROverPtClosetJet, &b_mu_dROverPtClosetJet);
   fChain->SetBranchAddress("mu_dROverPtClosetJet_WithFwds", &mu_dROverPtClosetJet_WithFwds, &b_mu_dROverPtClosetJet_WithFwds);
   fChain->SetBranchAddress("mu_dPhiMET", &mu_dPhiMET, &b_mu_dPhiMET);
   fChain->SetBranchAddress("mu_trigMatch", &mu_trigMatch, &b_mu_trigMatch);
   fChain->SetBranchAddress("mu_true_type", &mu_true_type, &b_mu_true_type);
   fChain->SetBranchAddress("mu_true_origin", &mu_true_origin, &b_mu_true_origin);
   fChain->SetBranchAddress("mu_true_pdg", &mu_true_pdg, &b_mu_true_pdg);
   fChain->SetBranchAddress("mu_true_pt", &mu_true_pt, &b_mu_true_pt);
   fChain->SetBranchAddress("mu_true_eta", &mu_true_eta, &b_mu_true_eta);
   fChain->SetBranchAddress("mu_true_phi", &mu_true_phi, &b_mu_true_phi);
   fChain->SetBranchAddress("jet_n", &jet_n, &b_jet_n);
   fChain->SetBranchAddress("jet_n_WithFwds", &jet_n_WithFwds, &b_jet_n_WithFwds);
   fChain->SetBranchAddress("jet_nbtag_60", &jet_nbtag_60, &b_jet_nbtag_60);
   fChain->SetBranchAddress("jet_nbtag_70", &jet_nbtag_70, &b_jet_nbtag_70);
   fChain->SetBranchAddress("jet_nbtag_77", &jet_nbtag_77, &b_jet_nbtag_77);
   fChain->SetBranchAddress("jet_nbtag_85", &jet_nbtag_85, &b_jet_nbtag_85);
   fChain->SetBranchAddress("jet_m", &jet_m, &b_jet_m);
   fChain->SetBranchAddress("jet_isFwd", &jet_isFwd, &b_jet_isFwd);
   fChain->SetBranchAddress("jet_isbtagged_60", &jet_isbtagged_60, &b_jet_isbtagged_60);
   fChain->SetBranchAddress("jet_isbtagged_70", &jet_isbtagged_70, &b_jet_isbtagged_70);
   fChain->SetBranchAddress("jet_isbtagged_77", &jet_isbtagged_77, &b_jet_isbtagged_77);
   fChain->SetBranchAddress("jet_isbtagged_85", &jet_isbtagged_85, &b_jet_isbtagged_85);
   fChain->SetBranchAddress("leadingJetpT", &leadingJetpT, &b_leadingJetpT);
   fChain->SetBranchAddress("leadingJetpT_WithFwds", &leadingJetpT_WithFwds, &b_leadingJetpT_WithFwds);
   fChain->SetBranchAddress("met_px", &met_px, &b_met_px);
   fChain->SetBranchAddress("met_py", &met_py, &b_met_py);
   fChain->SetBranchAddress("met_sumet", &met_sumet, &b_met_sumet);
   fChain->SetBranchAddress("Ht", &Ht, &b_Ht);
   fChain->SetBranchAddress("Ht_WithFwds", &Ht_WithFwds, &b_Ht_WithFwds);
}

Bool_t Tree_Nominal::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef Tree_Nominal_cxx
