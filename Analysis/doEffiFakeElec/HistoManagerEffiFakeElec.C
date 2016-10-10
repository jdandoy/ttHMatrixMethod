#define HistoManagerEffiFakeElec_cxx
//////////////////////////////////////////////////////////////////////
// 
// Author   : Atlas LPNHE Paris
// Creation : 01/10/2015
// Purpose  : base class to manage efficiency histograms for fake electrons
// Updated  :
//////////////////////////////////////////////////////////////////////

#include "HistoManagerEffiFakeElec.h"

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TObjArray.h>

ClassImp(HistoManagerEffiFakeElec);

// Constructor
HistoManagerEffiFakeElec::HistoManagerEffiFakeElec(TObjArray *histosObj)
{
  // retrieve histogram 
  m_histosObj = histosObj;

  m_binid    = 1;
  m_binjet   = 7; //Remeber to change if you add other option 

  m_binet           = 11;
  m_bineta          = 9;
  m_bindr           = 5;
  m_binptleadingjet = 4;
  m_bindphi         = 12;
  m_binmet          = 8;
  m_binmtw          = 8;
  m_binnbjet        = 5;
  m_binnjet         = 6; //This to modify


  // book histograms
  DefineHistos();
}

// ==============================================================
// DESTRUCTOR:
HistoManagerEffiFakeElec::~HistoManagerEffiFakeElec()
{ 
  //std::cout << " delete HistoManagerEffiFakeElec" << std::endl;  

  // by PID bin
  for (int id=0;id<=m_binid;id++) {

    // loop on jet
    for (int ijet=0;ijet<=m_binjet;ijet++) {

      // vs NJet
      delete hETmiss[id][ijet];
      delete hMTW[id][ijet];
      delete hETmissOverSqrtHT[id][ijet];

      // by Et bins
      for (int iet=0;iet<=m_binet;iet++) {
	delete hETmiss_vsEt[id][ijet][iet];
	delete hETmissOverSqrtHT_vsEt[id][ijet][iet];
      }
      
      // by eta bins
      for (int ieta=0;ieta<=m_bineta;ieta++) { 
	delete hETmiss_vsEta[id][ijet][ieta];
	delete hETmissOverSqrtHT_vsEta[id][ijet][ieta];
      }
      
      // by dRClosestJet bins
      for (int idr=0;idr<=m_bindr;idr++) {
	delete hETmiss_vsdRClosestJet[id][ijet][idr];
	delete hETmissOverSqrtHT_vsdRClosestJet[id][ijet][idr];
      }

      // by PtLeadingJet bins
      for (int iptleadingjet=0;iptleadingjet<=m_binptleadingjet;iptleadingjet++) {
	delete hETmiss_vsPtLeadingJet[id][ijet][iptleadingjet];
	delete hETmissOverSqrtHT_vsPtLeadingJet[id][ijet][iptleadingjet];
      }
    
      // by DPhi bins
      for (int idphi=0;idphi<=m_bindphi;idphi++) {
	delete hETmiss_vsDPhi[id][ijet][idphi];
	delete hETmissOverSqrtHT_vsDPhi[id][ijet][idphi];
      }
      
      // by MET bins
      for (int imet=0;imet<=m_binmet;imet++) {
	delete hETmiss_vsMET[id][ijet][imet];
	delete hETmissOverSqrtHT_vsMET[id][ijet][imet];
      }

      // by MTW bins
      for (int imtw=0;imtw<=m_binmtw;imtw++) {
	delete hETmiss_vsMTW[id][ijet][imtw];
	delete hETmissOverSqrtHT_vsMTW[id][ijet][imtw];
      }

      // by NJet bins
      for (int injet=0;injet<=m_binnjet;injet++) {
	delete hETmiss_vsNJet[id][ijet][injet];
	delete hETmissOverSqrtHT_vsNJet[id][ijet][injet];
      }

      // by NbJet bins
      for (int inbjet=0;inbjet<=m_binnbjet;inbjet++) {
	delete hETmiss_vsNbJet[id][ijet][inbjet];
	delete hMTW_vsNbJet[id][ijet][inbjet];
	delete hETmissOverSqrtHT_vsNbJet[id][ijet][inbjet];
      }
    }
  }
}

// =================================================================
void HistoManagerEffiFakeElec::DefineHistos() 
{
  //
  // definition of histograms for fake efficiency
  //

  int nbin    = 1000;
  double mmin = 0.;
  double mmax = 1000.;

  TString mytypeid;

  TString name = "EffiFakeElec_";
  TString myname;

  TString typeJet;

  // by PID bin
  for (int id=0;id<=m_binid;id++) {
    if (id==0) mytypeid = "_Loose";
    if (id==1) mytypeid = "_Tight";    
    
    // by jet bin
    for (int ijet=0;ijet<=m_binjet;ijet++) {
      typeJet = BinNJet(ijet);      

      // ETmiss
      myname  = name + "ETmiss" + mytypeid + typeJet; 
      hETmiss[id][ijet] = new TH1F(myname,myname,nbin,mmin,mmax);
      m_histosObj->Add(hETmiss[id][ijet]);
      
      // MTW
      myname  = name + "MTW" + mytypeid + typeJet; 
      hMTW[id][ijet] = new TH1F(myname,myname,nbin,mmin,mmax);
      m_histosObj->Add(hMTW[id][ijet]);

      // ETmissOverSqrtHT
      myname  = name + "ETmissOverSqrtHT" + mytypeid + typeJet; 
      hETmissOverSqrtHT[id][ijet] = new TH1F(myname,myname,nbin,mmin,mmax);
      m_histosObj->Add(hETmissOverSqrtHT[id][ijet]);
    }  
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

  for (int s = 0; s<m_histosObj->GetEntriesFast();s++) {
    ((TH1F*) m_histosObj->At(s))->Sumw2();
  }
}

// ==============================================================
void HistoManagerEffiFakeElec::DefineHistos_vsEt() 
{
  //
  // definition of histograms for fake efficiency
  //

  int nbin = 1000;
  double mmin = 0.;
  double mmax = 1000.;

  TString mytypeid;

  TString name = "EffiFakeElec_";
  TString myname;
  
  TString typeJet;
  TString typeEt;

  // by PID bin
  for (int id=0;id<=m_binid;id++) {
    if (id==0) mytypeid = "_Loose";
    if (id==1) mytypeid = "_Tight";    
    
    // by jet bin
    for (int ijet=0;ijet<=m_binjet;ijet++) {
      typeJet = BinNJet(ijet);      

      // by ET bins
      for (int iet=0;iet<=m_binet;iet++) {
	typeEt = BinEt(iet);      
	
	// ETmiss
	myname  = name + "ETmiss" + mytypeid + typeJet + typeEt; 
	hETmiss_vsEt[id][ijet][iet] = 
	  new TH1F(myname,myname,nbin,mmin,mmax);
	m_histosObj->Add(hETmiss_vsEt[id][ijet][iet]);

	// ETmissOverSqrtHT
	myname  = name + "ETmissOverSqrtHT" + mytypeid + typeJet + typeEt; 
	hETmissOverSqrtHT_vsEt[id][ijet][iet] = 
	  new TH1F(myname,myname,nbin,mmin,mmax);
	m_histosObj->Add(hETmissOverSqrtHT_vsEt[id][ijet][iet]);
      }
    }
  }
}

// ==============================================================
void HistoManagerEffiFakeElec::DefineHistos_vsEta() 
{
  //
  // definition of histograms for fake efficiency
  //

  int nbin = 1000;
  double mmin = 0.;
  double mmax = 1000.;

  TString mytypeid;

  TString name = "EffiFakeElec_";
  TString myname;
  
  TString typeJet;
  TString typeEta;

  // by PID bin
  for (int id=0;id<=m_binid;id++) {
    if (id==0) mytypeid = "_Loose";
    if (id==1) mytypeid = "_Tight";    

    // by jet bin
    for (int ijet=0;ijet<=m_binjet;ijet++) {
      typeJet = BinNJet(ijet);      

      // by Eta bins
      for (int ieta=0;ieta<=m_bineta;ieta++) {
	typeEta = BinEta(ieta);      
	
	// ETmiss
	myname  = name + "ETmiss" + mytypeid + typeJet + typeEta; 
	hETmiss_vsEta[id][ijet][ieta] = 
	  new TH1F(myname,myname,nbin,mmin,mmax);
	m_histosObj->Add(hETmiss_vsEta[id][ijet][ieta]);
	
	// ETmissOverSqrtHT
	myname  = name + "ETmissOverSqrtHT" + mytypeid + typeJet + typeEta; 
	hETmissOverSqrtHT_vsEta[id][ijet][ieta] = 
	  new TH1F(myname,myname,nbin,mmin,mmax);
	m_histosObj->Add(hETmissOverSqrtHT_vsEta[id][ijet][ieta]);
       }
    }
  }	
}

// ==============================================================
void HistoManagerEffiFakeElec::DefineHistos_vsdRClosestJet() 
{
  //
  // definition of histograms for fake efficiency
  //

  int nbin = 1000;
  double mmin = 0.;
  double mmax = 1000.;

  TString mytypeid;

  TString name = "EffiFakeElec_";
  TString myname;
  
  TString typeJet;
  TString typedRClosestJet;

  // by PID bin
  for (int id=0;id<=m_binid;id++) {
    if (id==0) mytypeid = "_Loose";
    if (id==1) mytypeid = "_Tight";    

    // by jet bin
    for (int ijet=0;ijet<=m_binjet;ijet++) {
      typeJet = BinNJet(ijet);      

      // by dRClosestJet bins
      for (int idr=0;idr<=m_bindr;idr++) {
	typedRClosestJet = BindRClosestJet(idr);      
	
	// ETmiss
	myname  = name + "ETmiss" + mytypeid + typeJet + typedRClosestJet; 
	hETmiss_vsdRClosestJet[id][ijet][idr] = 
	  new TH1F(myname,myname,nbin,mmin,mmax);
	m_histosObj->Add(hETmiss_vsdRClosestJet[id][ijet][idr]);
	
	// ETmissOverSqrtHT
	myname  = name + "ETmissOverSqrtHT" + mytypeid + typeJet + typedRClosestJet; 
	hETmissOverSqrtHT_vsdRClosestJet[id][ijet][idr] = 
	  new TH1F(myname,myname,nbin,mmin,mmax);
	m_histosObj->Add(hETmissOverSqrtHT_vsdRClosestJet[id][ijet][idr]);
      }
    }
  }	  
}

// ==============================================================
void HistoManagerEffiFakeElec::DefineHistos_vsPtLeadingJet() 
{
  //
  // definition of histograms for fake efficiency
  //

  int nbin = 1000;
  double mmin = 0.;
  double mmax = 1000.;

  TString mytypeid;

  TString name = "EffiFakeElec_";
  TString myname;
  
  TString typeJet;
  TString typePtLeadingJet;

  // by PID bin
  for (int id=0;id<=m_binid;id++) {
    if (id==0) mytypeid = "_Loose";
    if (id==1) mytypeid = "_Tight";    

    // by jet bin
    for (int ijet=0;ijet<=m_binjet;ijet++) {
      typeJet = BinNJet(ijet);      

      // by PtLeadingJet bins
      for (int iptleadingjet=0;iptleadingjet<=m_binptleadingjet;iptleadingjet++) {
	typePtLeadingJet = BinPtLeadingJet(iptleadingjet);      
	
	// ETmiss
	myname  = name + "ETmiss" + mytypeid + typeJet + typePtLeadingJet; 
	hETmiss_vsPtLeadingJet[id][ijet][iptleadingjet] = 
	  new TH1F(myname,myname,nbin,mmin,mmax);
	m_histosObj->Add(hETmiss_vsPtLeadingJet[id][ijet][iptleadingjet]);
	
	// ETmissOverSqrtHT
	myname  = name + "ETmissOverSqrtHT" + mytypeid + typeJet + typePtLeadingJet; 
	hETmissOverSqrtHT_vsPtLeadingJet[id][ijet][iptleadingjet] = 
	  new TH1F(myname,myname,nbin,mmin,mmax);
	m_histosObj->Add(hETmissOverSqrtHT_vsPtLeadingJet[id][ijet][iptleadingjet]);
      }
    }
  }
}

// ==============================================================
void HistoManagerEffiFakeElec::DefineHistos_vsDPhi() 
{
  //
  // definition of histograms for fake efficiency
  //

  int nbin = 1000;
  double mmin = 0.;
  double mmax = 1000.;

  TString mytypeid;

  TString name = "EffiFakeElec_";
  TString myname;
  
  TString typeJet;
  TString typeDPhi;

  // by PID bin
  for (int id=0;id<=m_binid;id++) {
    if (id==0) mytypeid = "_Loose";
    if (id==1) mytypeid = "_Tight";    

    // by jet bin
    for (int ijet=0;ijet<=m_binjet;ijet++) {
      typeJet = BinNJet(ijet);      

      // by DPhi bins
      for (int idphi=0;idphi<=m_bindphi;idphi++) {
	typeDPhi = BinDPhi(idphi);      
	
	// ETmiss
	myname  = name + "ETmiss" + mytypeid + typeJet +  typeDPhi; 
	hETmiss_vsDPhi[id][ijet][idphi] = 
	  new TH1F(myname,myname,nbin,mmin,mmax);
	m_histosObj->Add(hETmiss_vsDPhi[id][ijet][idphi]);
	
	// ETmissOverSqrtHT
	myname  = name + "ETmissOverSqrtHT" + mytypeid + typeJet +  typeDPhi; 
	hETmissOverSqrtHT_vsDPhi[id][ijet][idphi] = 
	  new TH1F(myname,myname,nbin,mmin,mmax);
	m_histosObj->Add(hETmissOverSqrtHT_vsDPhi[id][ijet][idphi]);
      }
    }
  }
}

// ==============================================================
void HistoManagerEffiFakeElec::DefineHistos_vsMET() 
{
  //
  // definition of histograms for fake efficiency
  //

  int nbin = 1000;
  double mmin = 0.;
  double mmax = 1000.;

  TString mytypeid;

  TString name = "EffiFakeElec_";
  TString myname;
  
  TString typeJet;
  TString typeMET;

  // by PID bin
  for (int id=0;id<=m_binid;id++) {
    if (id==0) mytypeid = "_Loose";
    if (id==1) mytypeid = "_Tight";    

    // by jet bin
    for (int ijet=0;ijet<=m_binjet;ijet++) {
      typeJet = BinNJet(ijet);      

      // by MET bins
      for (int imet=0;imet<=m_binmet;imet++) {
	typeMET = BinMET(imet);      
	
	// ETmiss
	myname  = name + "ETmiss" + mytypeid + typeJet + typeMET; 
	hETmiss_vsMET[id][ijet][imet] = 
	  new TH1F(myname,myname,nbin,mmin,mmax);
	m_histosObj->Add(hETmiss_vsMET[id][ijet][imet]);
	
	// ETmissOverSqrtHT
	myname  = name + "ETmissOverSqrtHT" + mytypeid + typeJet + typeMET; 
	hETmissOverSqrtHT_vsMET[id][ijet][imet] = 
	  new TH1F(myname,myname,nbin,mmin,mmax);
	m_histosObj->Add(hETmissOverSqrtHT_vsMET[id][ijet][imet]);
      }
    }
  }
}

// ==============================================================
void HistoManagerEffiFakeElec::DefineHistos_vsMTW() 
{
  //
  // definition of histograms for fake efficiency
  //

  int nbin = 1000;
  double mmin = 0.;
  double mmax = 1000.;

  TString mytypeid;

  TString name = "EffiFakeElec_";
  TString myname;
  
  TString typeJet;
  TString typeMTW;

  // by PID bin
  for (int id=0;id<=m_binid;id++) {
    if (id==0) mytypeid = "_Loose";
    if (id==1) mytypeid = "_Tight";    

    // by jet bin
    for (int ijet=0;ijet<=m_binjet;ijet++) {
      typeJet = BinNJet(ijet);      

      // by MTW bins
      for (int imtw=0;imtw<=m_binmtw;imtw++) {
	typeMTW = BinMTW(imtw);      
	
	// ETmiss
	myname  = name + "ETmiss" + mytypeid + typeJet + typeMTW; 
	hETmiss_vsMTW[id][ijet][imtw] = 
	  new TH1F(myname,myname,nbin,mmin,mmax);
	m_histosObj->Add(hETmiss_vsMTW[id][ijet][imtw]);
	
	// ETmissOverSqrtHT
	myname  = name + "ETmissOverSqrtHT" + mytypeid + typeJet + typeMTW; 
	hETmissOverSqrtHT_vsMTW[id][ijet][imtw] = 
	  new TH1F(myname,myname,nbin,mmin,mmax);
	m_histosObj->Add(hETmissOverSqrtHT_vsMTW[id][ijet][imtw]);
      }
    }
  }
}

// ==============================================================
void HistoManagerEffiFakeElec::DefineHistos_vsNJet() 
{
  //
  // definition of histograms for fake efficiency
  //

  int nbin = 1000;
  double mmin = 0.;
  double mmax = 1000.;

  TString mytypeid;

  TString name = "EffiFakeElec_";
  TString myname;
  
  TString typeJet;
  TString typeNJet;

  // by PID bin
  for (int id=0;id<=m_binid;id++) {
    if (id==0) mytypeid = "_Loose";
    if (id==1) mytypeid = "_Tight";    

    // by jet bin
    for (int ijet=0;ijet<=m_binjet;ijet++) {
      typeJet = BinNJet(ijet);      

      // by NJet bins
      for (int injet=0;injet<=m_binnjet;injet++) {
	typeNJet = BinNJet2(injet);      
	
	// ETmiss
	myname  = name + "ETmiss" + mytypeid + typeJet + typeNJet; 
	hETmiss_vsNJet[id][ijet][injet] = 
	  new TH1F(myname,myname,nbin,mmin,mmax);
	m_histosObj->Add(hETmiss_vsNJet[id][ijet][injet]);
	
	// ETmissOverSqrtHT
	myname  = name + "ETmissOverSqrtHT" + mytypeid + typeJet + typeNJet; 
	hETmissOverSqrtHT_vsNJet[id][ijet][injet] = 
	  new TH1F(myname,myname,nbin,mmin,mmax);
	m_histosObj->Add(hETmissOverSqrtHT_vsNJet[id][ijet][injet]);
      }
    }
  }
}

// ==============================================================
void HistoManagerEffiFakeElec::DefineHistos_vsNbJet() 
{
  //
  // definition of histograms for fake efficiency
  //

  int nbin = 1000;
  double mmin = 0.;
  double mmax = 1000.;

  TString mytypeid;

  TString name = "EffiFakeElec_";
  TString myname;
  
  TString typeJet;
  TString typeNbJet;

  // by PID bin
  for (int id=0;id<=m_binid;id++) {
    if (id==0) mytypeid = "_Loose";
    if (id==1) mytypeid = "_Tight";    

    // by jet bin
    for (int ijet=0;ijet<=m_binjet;ijet++) {
      typeJet = BinNJet(ijet);      
      //cout << "A" << ijet << endl;
      // by NbJet bins
      for (int inbjet=0;inbjet<=m_binnbjet;inbjet++) {
	typeNbJet = BinNbJet(inbjet);      
        //cout << "B" << inbjet << endl;
// ETmiss
	myname  = name + "ETmiss" + mytypeid + typeJet + typeNbJet; 
	hETmiss_vsNbJet[id][ijet][inbjet] = 
	  new TH1F(myname,myname,nbin,mmin,mmax);
	m_histosObj->Add(hETmiss_vsNbJet[id][ijet][inbjet]);
//cout << "DONE" << endl;
//This is for MTW
        myname  = name + "MTW" + mytypeid + typeJet + typeNbJet;
        hMTW_vsNbJet[id][ijet][inbjet] =
          new TH1F(myname,myname,nbin,mmin,mmax);
        m_histosObj->Add(hMTW_vsNbJet[id][ijet][inbjet]);
// ETmissOverSqrtHT
	myname  = name + "ETmissOverSqrtHT" + mytypeid + typeJet + typeNbJet; 
	hETmissOverSqrtHT_vsNbJet[id][ijet][inbjet] = 
	  new TH1F(myname,myname,nbin,mmin,mmax);
	m_histosObj->Add(hETmissOverSqrtHT_vsNbJet[id][ijet][inbjet]);
      }
    }
  }
//std::cout << "DONE---- DONE" << std::endl;
}
//std::cout << "DONE---- FINISHED" << std::endl;
// =================================================================
TString HistoManagerEffiFakeElec::BinEt(int index)
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
TString HistoManagerEffiFakeElec::BinEta(int index)
{
  TString type="";
  
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
TString HistoManagerEffiFakeElec::BindRClosestJet(int index)
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
TString HistoManagerEffiFakeElec::BinPtLeadingJet(int index)
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
TString HistoManagerEffiFakeElec::BinDPhi(int index)
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
TString HistoManagerEffiFakeElec::BinMET(int index)
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
TString HistoManagerEffiFakeElec::BinMTW(int index)
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
TString HistoManagerEffiFakeElec::BinNJet(int index)
{
  TString type="";

  if (index==0) type = "_0j";
  if (index==1) type = "_1j";
  if (index==2) type = "_ge1j";
  if (index==3) type = "_ge2j";
  if (index==4) type = "_2or3j";
  if (index==5) type = "_ge4j";
  if (index==6) type = "_ge5j";
  if (index==7) type = "_ge6j";
  return type;
}

// =================================================================
TString HistoManagerEffiFakeElec::BinNJet2(int index)
{
  TString type;

  if (index==0)  type = "_0Jet";
  if (index==1)  type = "_1Jet";
  if (index==2)  type = "_2Jet";
  if (index==3)  type = "_3Jet";
  if (index==4)  type = "_ge4Jet";
  if (index==5)  type = "_ge5Jet";
  if (index==6)  type = "_ge6Jet";
  return type;
}

// =================================================================
TString HistoManagerEffiFakeElec::BinNbJet(int index)
{
  TString type="";

  if (index==0) type = "_0bJet";
  if (index==1) type = "_1bJet";
  if (index==2) type = "_ge1bJet";
  if (index==3) type = "_ge2bJet";
  if (index==4) type = "_ge3bJet";
  if (index==5) type = "_ge4bJet";
  return type;
}
