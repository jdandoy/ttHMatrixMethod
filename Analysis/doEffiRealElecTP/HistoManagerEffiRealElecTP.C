#define HistoManagerEffiRealElecTP_cxx
//////////////////////////////////////////////////////////////////////
// 
// Author   : Atlas LPNHE Paris
// Creation : 01/01/2006
// Purpose  : base class to manage 
// Updated  :
//////////////////////////////////////////////////////////////////////

#include "HistoManagerEffiRealElecTP.h"

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TObjArray.h>

ClassImp(HistoManagerEffiRealElecTP);

// Constructor
HistoManagerEffiRealElecTP::HistoManagerEffiRealElecTP(TObjArray *histosObj)
{
  // retrieve histogram 
  m_histosObj = histosObj;

  m_binid    = 1;

  m_binet           = 11;
  m_bineta          = 9;
  m_bindr           = 5;
  m_binptleadingjet = 4;
  m_bindphi         = 12;
  m_binmet          = 8;
  m_binmtw          = 8;
  m_binnbjet        = 3;
  m_binnjet         = 4;
  m_binnvert = 15;

  // book histograms
  DefineHistos();
}

// ==============================================================
// DESTRUCTOR:
HistoManagerEffiRealElecTP::~HistoManagerEffiRealElecTP()
{ 
}

// =================================================================
void HistoManagerEffiRealElecTP::DefineHistos() 
{
  //std::cout << " HistoManagerEffiRealElec::DefineHistos " << std::endl;

  m_nbin_mass = 500;
  m_mmin_mass = 0.;
  m_mmax_mass = 250.;

  m_name = "EffiRealElecTP_";

  // by PID bin
  for (int id=0;id<=m_binid;id++) {
    if (id==0) m_mytypeid = "_Loose";
    if (id==1) m_mytypeid = "_Tight";

    //
    // Mee
    m_myname  = m_name + "Mee"; 
    // define histograms for opposite-sign
    m_nameOS  = m_myname + m_mytypeid + "_OS"; 
    hmassZ_OS[id] = 
      new TH1F(m_nameOS,m_nameOS,m_nbin_mass,m_mmin_mass,m_mmax_mass);
    m_histosObj->Add(hmassZ_OS[id]);
    // define histograms for same-sign
    m_nameSS  = m_myname + m_mytypeid + "_SS"; 
    hmassZ_SS[id] = 
      new TH1F(m_nameSS,m_nameSS,m_nbin_mass,m_mmin_mass,m_mmax_mass);
    m_histosObj->Add(hmassZ_SS[id]);
    
  }

  DefineHistos_vsEt();
  DefineHistos_vsEta();
  DefineHistos_vsdRClosestJet();
  DefineHistos_vsPtLeadingJet();
  DefineHistos_vsDPhi();
  DefineHistos_vsMET();
  DefineHistos_vsMTW();
  DefineHistos_vsNJet();
  DefineHistos_vsNbJet();

  DefineHistos_NVert();
}

// =================================================================
void HistoManagerEffiRealElecTP::DefineHistos_vsEt() 
{
  //std::cout <=<= " HistoManagerEffiRealElec::DefineHistos " <=<= std::endl;
  
  // by PID bin
  for (int id=0;id<=m_binid;id++) {
    if (id==0) m_mytypeid = "_Loose";
    if (id==1) m_mytypeid = "_Tight";

    // by Et bins
    for (int iet=0;iet<=m_binet;iet++) {
      m_typeEt = BinEt(iet);      

      //
      // Mee
      m_myname  = m_name + "Mee"; 
      // define histograms for opposite-sign
      m_nameOS  = m_myname + m_mytypeid + m_typeEt + "_vsEt_OS"; 
      hmassZ_vsEt_OS[id][iet] = 
	new TH1F(m_nameOS,m_nameOS,m_nbin_mass,m_mmin_mass,m_mmax_mass);
      m_histosObj->Add(hmassZ_vsEt_OS[id][iet]);
      // define histograms for same-sign
      m_nameSS  = m_myname + m_mytypeid + m_typeEt + "_vsEt_SS"; 
      hmassZ_vsEt_SS[id][iet] = 
	new TH1F(m_nameSS,m_nameSS,m_nbin_mass,m_mmin_mass,m_mmax_mass);
      m_histosObj->Add(hmassZ_vsEt_SS[id][iet]);
      
    }
  }
}

// =================================================================
void HistoManagerEffiRealElecTP::DefineHistos_vsEta() 
{
  //std::cout <=<= " HistoManagerEffiRealElec::DefineHistos_vsEta " <=<= std::endl;
  
  // by PID bin
  for (int id=0;id<=m_binid;id++) {
    if (id==0) m_mytypeid = "_Loose";
    if (id==1) m_mytypeid = "_Tight";

    // by Eta bins
    for (int ieta=0;ieta<=m_bineta;ieta++) {
      m_typeEta = BinEta(ieta);      

      //
      // Mee
      m_myname  = m_name + "Mee"; 
      // define histograms for opposite-sign
      m_nameOS  = m_myname + m_mytypeid + m_typeEta + "_vsEta_OS"; 
      hmassZ_vsEta_OS[id][ieta] = 
	new TH1F(m_nameOS,m_nameOS,m_nbin_mass,m_mmin_mass,m_mmax_mass);
      m_histosObj->Add(hmassZ_vsEta_OS[id][ieta]);
      // define histograms for same-sign
      m_nameSS  = m_myname + m_mytypeid + m_typeEta + "_vsEta_SS"; 
      hmassZ_vsEta_SS[id][ieta] = 
	new TH1F(m_nameSS,m_nameSS,m_nbin_mass,m_mmin_mass,m_mmax_mass);
      m_histosObj->Add(hmassZ_vsEta_SS[id][ieta]);
      
    }
  }
}

// =================================================================
void HistoManagerEffiRealElecTP::DefineHistos_vsdRClosestJet() 
{
  //std::cout <=<= " HistoManagerEffiRealElec::DefineHistos_vsVar " <=<= std::endl;
  
  // by PID bin
  for (int id=0;id<=m_binid;id++) {
    if (id==0) m_mytypeid = "_Loose";
    if (id==1) m_mytypeid = "_Tight";

    // by dRClosestJet bins
    for (int idr=0;idr<=m_bindr;idr++) {
      m_typedRClosestJet = BindRClosestJet(idr);      

      //
      // Mee
      m_myname  = m_name + "Mee"; 
      // define histograms for opposite-sign
      m_nameOS  = m_myname + m_mytypeid + m_typedRClosestJet + "_vsdRClosestJet_OS"; 
      hmassZ_vsdRClosestJet_OS[id][idr] = 
	new TH1F(m_nameOS,m_nameOS,m_nbin_mass,m_mmin_mass,m_mmax_mass);
      m_histosObj->Add(hmassZ_vsdRClosestJet_OS[id][idr]);
      // define histograms for same-sign
      m_nameSS  = m_myname + m_mytypeid + m_typedRClosestJet + "_vsdRClosestJet_SS"; 
      hmassZ_vsdRClosestJet_SS[id][idr] = 
	new TH1F(m_nameSS,m_nameSS,m_nbin_mass,m_mmin_mass,m_mmax_mass);
      m_histosObj->Add(hmassZ_vsdRClosestJet_SS[id][idr]);
      
    }
  }
}

// =================================================================
void HistoManagerEffiRealElecTP::DefineHistos_vsPtLeadingJet() 
{
  //std::cout <=<= " HistoManagerEffiRealElec::DefineHistos_vsVar " <=<= std::endl;
  
  // by PID bin
  for (int id=0;id<=m_binid;id++) {
    if (id==0) m_mytypeid = "_Loose";
    if (id==1) m_mytypeid = "_Tight";

    // by PtLeadingJet bins
    for (int iptleadingjet=0;iptleadingjet<=m_binptleadingjet;iptleadingjet++) {
      m_typePtLeadingJet = BinPtLeadingJet(iptleadingjet);      

      //
      // Mee
      m_myname  = m_name + "Mee"; 
      // define histograms for opposite-sign
      m_nameOS  = m_myname + m_mytypeid + m_typePtLeadingJet + "_vsPtLeadingJet_OS"; 
      hmassZ_vsPtLeadingJet_OS[id][iptleadingjet] = 
	new TH1F(m_nameOS,m_nameOS,m_nbin_mass,m_mmin_mass,m_mmax_mass);
      m_histosObj->Add(hmassZ_vsPtLeadingJet_OS[id][iptleadingjet]);
      // define histograms for same-sign
      m_nameSS  = m_myname + m_mytypeid + m_typePtLeadingJet + "_vsPtLeadingJet_SS"; 
      hmassZ_vsPtLeadingJet_SS[id][iptleadingjet] = 
	new TH1F(m_nameSS,m_nameSS,m_nbin_mass,m_mmin_mass,m_mmax_mass);
      m_histosObj->Add(hmassZ_vsPtLeadingJet_SS[id][iptleadingjet]);
      
    }
  }
}

// =================================================================
void HistoManagerEffiRealElecTP::DefineHistos_vsDPhi() 
{
  //std::cout <=<= " HistoManagerEffiRealElec::DefineHistos_vsVar " <=<= std::endl;
  
 // by PID bin
  for (int id=0;id<=m_binid;id++) {
    if (id==0) m_mytypeid = "_Loose";
    if (id==1) m_mytypeid = "_Tight";

    // by DPhi bins
    for (int idphi=0;idphi<=m_bindphi;idphi++) {
      m_typeDPhi = BinDPhi(idphi);      

      //
      // Mee
      m_myname  = m_name + "Mee"; 
      // define histograms for opposite-sign
      m_nameOS  = m_myname + m_mytypeid + m_typeDPhi + "_vsDPhi_OS"; 
      hmassZ_vsDPhi_OS[id][idphi] = 
	new TH1F(m_nameOS,m_nameOS,m_nbin_mass,m_mmin_mass,m_mmax_mass);
      m_histosObj->Add(hmassZ_vsDPhi_OS[id][idphi]);
      // define histograms for same-sign
      m_nameSS  = m_myname + m_mytypeid + m_typeDPhi + "_vsDPhi_SS"; 
      hmassZ_vsDPhi_SS[id][idphi] = 
	new TH1F(m_nameSS,m_nameSS,m_nbin_mass,m_mmin_mass,m_mmax_mass);
      m_histosObj->Add(hmassZ_vsDPhi_SS[id][idphi]);
      
    }
  }
}

// =================================================================
void HistoManagerEffiRealElecTP::DefineHistos_vsMET() 
{
  //std::cout <=<= " HistoManagerEffiRealElec::DefineHistos_vsVar " <=<= std::endl;
  
 // by PID bin
  for (int id=0;id<=m_binid;id++) {
    if (id==0) m_mytypeid = "_Loose";
    if (id==1) m_mytypeid = "_Tight";

    // by MET bins
    for (int imet=0;imet<=m_binmet;imet++) {
      m_typeMET = BinMET(imet);      

      //
      // Mee
      m_myname  = m_name + "Mee"; 
      // define histograms for opposite-sign
      m_nameOS  = m_myname + m_mytypeid + m_typeMET + "_vsMET_OS"; 
      hmassZ_vsMET_OS[id][imet] = 
	new TH1F(m_nameOS,m_nameOS,m_nbin_mass,m_mmin_mass,m_mmax_mass);
      m_histosObj->Add(hmassZ_vsMET_OS[id][imet]);
      // define histograms for same-sign
      m_nameSS  = m_myname + m_mytypeid + m_typeMET + "_vsMET_SS"; 
      hmassZ_vsMET_SS[id][imet] = 
	new TH1F(m_nameSS,m_nameSS,m_nbin_mass,m_mmin_mass,m_mmax_mass);
      m_histosObj->Add(hmassZ_vsMET_SS[id][imet]);
      
    }
  }
}

// =================================================================
void HistoManagerEffiRealElecTP::DefineHistos_vsMTW() 
{
  //std::cout <=<= " HistoManagerEffiRealElec::DefineHistos_vsVar " <=<= std::endl;
  // by PID bin
  for (int id=0;id<=m_binid;id++) {
    if (id==0) m_mytypeid = "_Loose";
    if (id==1) m_mytypeid = "_Tight";

    // by MTW bins
    for (int imet=0;imet<=m_binmet;imet++) {
      m_typeMTW = BinMTW(imet);      

      //
      // Mee
      m_myname  = m_name + "Mee"; 
      // define histograms for opposite-sign
      m_nameOS  = m_myname + m_mytypeid + m_typeMTW + "_vsMTW_OS"; 
      hmassZ_vsMTW_OS[id][imet] = 
	new TH1F(m_nameOS,m_nameOS,m_nbin_mass,m_mmin_mass,m_mmax_mass);
      m_histosObj->Add(hmassZ_vsMTW_OS[id][imet]);
      // define histograms for same-sign
      m_nameSS  = m_myname + m_mytypeid + m_typeMTW + "_vsMTW_SS"; 
      hmassZ_vsMTW_SS[id][imet] = 
	new TH1F(m_nameSS,m_nameSS,m_nbin_mass,m_mmin_mass,m_mmax_mass);
      m_histosObj->Add(hmassZ_vsMTW_SS[id][imet]);
      
    }
  }
}

// =================================================================
void HistoManagerEffiRealElecTP::DefineHistos_vsNJet() 
{
  //std::cout <=<= " HistoManagerEffiRealElec::DefineHistos_vsVar " <=<= std::endl;
  // by PID bin
  for (int id=0;id<=m_binid;id++) {
    if (id==0) m_mytypeid = "_Loose";
    if (id==1) m_mytypeid = "_Tight";

    // by NJet bins
    for (int injet=0;injet<=m_binnjet;injet++) {
      m_typeNJet = BinNJet(injet);      

      //
      // Mee
      m_myname  = m_name + "Mee"; 
      // define histograms for opposite-sign
      m_nameOS  = m_myname + m_mytypeid + m_typeNJet + "_vsNJet_OS"; 
      hmassZ_vsNJet_OS[id][injet] = 
	new TH1F(m_nameOS,m_nameOS,m_nbin_mass,m_mmin_mass,m_mmax_mass);
      m_histosObj->Add(hmassZ_vsNJet_OS[id][injet]);
      // define histograms for same-sign
      m_nameSS  = m_myname + m_mytypeid + m_typeNJet + "_vsNJet_SS"; 
      hmassZ_vsNJet_SS[id][injet] = 
	new TH1F(m_nameSS,m_nameSS,m_nbin_mass,m_mmin_mass,m_mmax_mass);
      m_histosObj->Add(hmassZ_vsNJet_SS[id][injet]);
      
    }
  }
}

// =================================================================
void HistoManagerEffiRealElecTP::DefineHistos_vsNbJet() 
{
  //std::cout <=<= " HistoManagerEffiRealElec::DefineHistos_vsVar " <=<= std::endl;
  // by PID bin
  for (int id=0;id<=m_binid;id++) {
    if (id==0) m_mytypeid = "_Loose";
    if (id==1) m_mytypeid = "_Tight";

    // by NbJet bins
    for (int inbjet=0;inbjet<=m_binnbjet;inbjet++) {
      m_typeNbJet = BinNbJet(inbjet);      

      //
      // Mee
      m_myname  = m_name + "Mee"; 
      // define histograms for opposite-sign
      m_nameOS  = m_myname + m_mytypeid + m_typeNbJet + "_vsNbJet_OS"; 
      hmassZ_vsNbJet_OS[id][inbjet] = 
	new TH1F(m_nameOS,m_nameOS,m_nbin_mass,m_mmin_mass,m_mmax_mass);
      m_histosObj->Add(hmassZ_vsNbJet_OS[id][inbjet]);
      // define histograms for same-sign
      m_nameSS  = m_myname + m_mytypeid + m_typeNbJet + "_vsNbJet_SS"; 
      hmassZ_vsNbJet_SS[id][inbjet] = 
	new TH1F(m_nameSS,m_nameSS,m_nbin_mass,m_mmin_mass,m_mmax_mass);
      m_histosObj->Add(hmassZ_vsNbJet_SS[id][inbjet]);
      
    }
  }
}

// =================================================================
void HistoManagerEffiRealElecTP::DefineHistos_NVert() 
{
  //std::cout <=<= " HistoManagerEffiRealElec::DefineHistos " <=<= std::endl;
  
  // by PID bin
  for (int id=0;id<=m_binid;id++) {
    if (id==0) m_mytypeid = "_Loose";
    if (id==1) m_mytypeid = "_Tight";

    for (int ivert=0;ivert<=m_binnvert;ivert++) {
      TString typevert = BinVert(ivert);
      
      //
      // Mee Nvert
      m_myname  = m_name + "Mee"; 
      // define histograms for opposite-sign
      m_nameOS  = m_myname + m_mytypeid + typevert + "_OS"; 
      hmassZNVert_OS[id][ivert] = 
	new TH1F(m_nameOS,m_nameOS,m_nbin_mass,m_mmin_mass,m_mmax_mass);
      m_histosObj->Add(hmassZNVert_OS[id][ivert]);
      // define histograms for same-sign
      m_nameSS  = m_myname + m_mytypeid + typevert + "_SS"; 
      hmassZNVert_SS[id][ivert] = 
	new TH1F(m_nameSS,m_nameSS,m_nbin_mass,m_mmin_mass,m_mmax_mass);
      m_histosObj->Add(hmassZNVert_SS[id][ivert]);
    }
  }
}

// =================================================================
TString HistoManagerEffiRealElecTP::BinEt(int index)
{
  TString type;

  if (index==0)  type = "_Et_25to30GeV";
  if (index==1)  type = "_Et_30to35GeV";
  if (index==2)  type = "_Et_35to40GeV";
  if (index==3)  type = "_Et_40to45GeV";
  if (index==4)  type = "_Et_45to50GeV";
  if (index==5)  type = "_Et_50to55GeV";
  if (index==6)  type = "_Et_55to60GeV";
  if (index==7)  type = "_Et_60to80GeV";
  if (index==8)  type = "_Et_80to120GeV";
  if (index==9)  type = "_Et_gt120GeV";
  if (index==10) type = "_Et_gt80GeV";
  if (index==11) type = "_Et_gt60GeV";

  return type;
}

// =================================================================
TString HistoManagerEffiRealElecTP::BinEta(int index)
{
  TString type;

  if (index==0) type = "_Eta_0to01";
  if (index==1) type = "_Eta_01to06";
  if (index==2) type = "_Eta_06to08";
  if (index==3) type = "_Eta_08to115";
  if (index==4) type = "_Eta_115to137";
  if (index==5) type = "_Eta_137to152";
  if (index==6) type = "_Eta_152to181";
  if (index==7) type = "_Eta_181to201";
  if (index==8) type = "_Eta_201to237";
  if (index==9) type = "_Eta_237to247";

  return type;
}

// =================================================================
TString HistoManagerEffiRealElecTP::BindRClosestJet(int index)
{
  TString type;

  if (index==0)  type = "_dRClosestJet_04to06";
  if (index==1)  type = "_dRClosestJet_06to08";
  if (index==2)  type = "_dRClosestJet_08to10";
  if (index==3)  type = "_dRClosestJet_10to15";
  if (index==4)  type = "_dRClosestJet_15to20";
  if (index==5)  type = "_dRClosestJet_gt20";

  return type;
}

// =================================================================
TString HistoManagerEffiRealElecTP::BinPtLeadingJet(int index)
{
  TString type;

  if (index==0) type = "_PtLeadingJet_25to50GeV";
  if (index==1) type = "_PtLeadingJet_50to75GeV";
  if (index==2) type = "_PtLeadingJet_75to100GeV";
  if (index==3) type = "_PtLeadingJet_100to150GeV";
  if (index==4) type = "_PtLeadingJet_gt150GeV";

  return type;
}

// =================================================================
TString HistoManagerEffiRealElecTP::BinDPhi(int index)
{
  TString type;

  if (index==0)  type = "_DPhi_0to010";
  if (index==1)  type = "_DPhi_010to020";
  if (index==2)  type = "_DPhi_020to030";
  if (index==3)  type = "_DPhi_030to040";
  if (index==4)  type = "_DPhi_040to050";
  if (index==5)  type = "_DPhi_050to075";
  if (index==6)  type = "_DPhi_075to100";
  if (index==7)  type = "_DPhi_100to125";
  if (index==8)  type = "_DPhi_125to150";
  if (index==9)  type = "_DPhi_150to175";
  if (index==10) type = "_DPhi_175to200";
  if (index==11) type = "_DPhi_200to250";
  if (index==12) type = "_DPhi_250topi";

  return type;
}

// =================================================================
TString HistoManagerEffiRealElecTP::BinMET(int index)
{
  TString type;

  if (index==0)  type = "_MET_0to10";
  if (index==1)  type = "_MET_10to20";
  if (index==2)  type = "_MET_20to30";
  if (index==3)  type = "_MET_30to40";
  if (index==4)  type = "_MET_40to60";
  if (index==5)  type = "_MET_60to100";
  if (index==6)  type = "_MET_100to150";
  if (index==7)  type = "_MET_150to200";
  if (index==8)  type = "_MET_gt200";

  return type;
}

// =================================================================
TString HistoManagerEffiRealElecTP::BinMTW(int index)
{
  TString type;

  if (index==0)  type = "_MTW_0to10";
  if (index==1)  type = "_MTW_10to20";
  if (index==2)  type = "_MTW_20to30";
  if (index==3)  type = "_MTW_30to40";
  if (index==4)  type = "_MTW_40to60";
  if (index==5)  type = "_MTW_60to100";
  if (index==6)  type = "_MTW_100to150";
  if (index==7)  type = "_MTW_150to200";
  if (index==8)  type = "_MTW_gt200";

  return type;
}

// =================================================================
TString HistoManagerEffiRealElecTP::BinNJet(int index)
{
  TString type;

  if (index==0)  type = "_0Jet";
  if (index==1)  type = "_1Jet";
  if (index==2)  type = "_2Jet";
  if (index==3)  type = "_3Jet";
  if (index==4)  type = "_ge4Jet";

  return type;
}

// =================================================================
TString HistoManagerEffiRealElecTP::BinNbJet(int index)
{
  TString type;

  if (index==0) type = "_0bJet";
  if (index==1) type = "_1bJet";
  if (index==2) type = "_ge1bJet";
  if (index==3) type = "_ge2bJet";

  return type;
}

// =================================================================
TString HistoManagerEffiRealElecTP::BinVert(int index)
{
  TString type;

  if (index==0)  type = "_NVert0";
  if (index==1)  type = "_NVert2";
  if (index==2)  type = "_NVert4";
  if (index==3)  type = "_NVert6";
  if (index==4)  type = "_NVert8";
  if (index==5)  type = "_NVert10";
  if (index==6)  type = "_NVert12";
  if (index==7)  type = "_NVert14";
  if (index==8)  type = "_NVert16";
  if (index==9)  type = "_NVert18";
  if (index==10) type = "_NVert20";
  if (index==11) type = "_NVert22";
  if (index==12) type = "_NVert24";
  if (index==13) type = "_NVert26";
  if (index==14) type = "_NVert28";
  if (index==15) type = "_NVert30";

  return type;
}
