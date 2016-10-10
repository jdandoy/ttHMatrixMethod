#define HistoManagerEffiFakeMuon_cxx
//////////////////////////////////////////////////////////////////////
// 
// Author   : Atlas LPNHE Paris
// Creation : 01/10/2015
// Purpose  : base class to manage efficiency histograms for fake muons
// Updated  :
//////////////////////////////////////////////////////////////////////

#include "HistoManagerEffiFakeMuon.h"

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TObjArray.h>

ClassImp(HistoManagerEffiFakeMuon);

// Constructor
HistoManagerEffiFakeMuon::HistoManagerEffiFakeMuon(TObjArray *histosObj)
{
  // retrieve histogram 
  m_histosObj = histosObj;

  m_binid    = 1;
  m_binjet   = 5; 

  m_binpt           = 12;
  m_bineta          = 9;
  m_bindr           = 5;
  m_binptleadingjet = 4;
  m_bindphi         = 12;
  m_binmet          = 8;
  m_binmtw          = 8;
  m_bind0sig        = 10;
  m_binnbjet        = 3;
  m_binnjet         = 4;

  // book histograms
  DefineHistos();
}

// ==============================================================
// DESTRUCTOR:
HistoManagerEffiFakeMuon::~HistoManagerEffiFakeMuon()
{ 
  //std::cout << " delete HistoManagerEffiFakeMuon" << std::endl;  

  // by PID bin
  for (int id=0;id<=m_binid;id++) {

    // loop on jet
    for (int ijet=0;ijet<=m_binjet;ijet++) {

      // vs NJet
      delete hETmiss[id][ijet];
      delete hMTW[id][ijet];
      delete hd0sig[id][ijet];
      delete hd0sigPV[id][ijet];
      delete hETmissOverSqrtHT[id][ijet];
      
      // by Pt bins
      for (int ipt=0;ipt<=m_binpt;ipt++) {
	delete hETmiss_vsPt[id][ijet][ipt];
	delete hETmissOverSqrtHT_vsPt[id][ijet][ipt];
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
	delete hETmissOverSqrtHT_vsNbJet[id][ijet][inbjet];
      }
 
      // by d0sig bins
      for (int id0sig=0;id0sig<=m_bind0sig;id0sig++) {
	delete hETmiss_vsd0sig[id][ijet][id0sig];
	delete hETmissOverSqrtHT_vsd0sig[id][ijet][id0sig];
      }

    }
  }
}

// =================================================================
void HistoManagerEffiFakeMuon::DefineHistos() 
{
  //
  // definition of histograms for fake efficiency
  //

  int nbin    = 1000;
  double mmin = 0.;
  double mmax = 1000.;

  TString mytypeid;

  TString name = "EffiFakeMuon_";
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
      
      // d0sig
      myname  = name + "d0sig" + mytypeid + typeJet; 
      hd0sig[id][ijet] = new TH1F(myname,myname,100,-20.,20.);
      m_histosObj->Add(hd0sig[id][ijet]);

      // d0sigPV
      myname  = name + "d0sigPV" + mytypeid + typeJet; 
      hd0sigPV[id][ijet] = new TH1F(myname,myname,100,-20.,20.);
      m_histosObj->Add(hd0sigPV[id][ijet]);

      // ETmissOverSqrtHT
      myname  = name + "ETmissOverSqrtHT" + mytypeid + typeJet; 
      hETmissOverSqrtHT[id][ijet] = new TH1F(myname,myname,nbin,mmin,mmax);
      m_histosObj->Add(hETmissOverSqrtHT[id][ijet]);
    } 
  }

  DefineHistos_vsPt();
  DefineHistos_vsEta();
  DefineHistos_vsdRClosestJet();
  DefineHistos_vsPtLeadingJet();
  DefineHistos_vsDPhi();
  DefineHistos_vsMET();
  DefineHistos_vsMTW();
  DefineHistos_vsd0sig();
  DefineHistos_vsNJet();
  DefineHistos_vsNbJet();
  
  for (int s = 0; s<m_histosObj->GetEntriesFast();s++) {
    ((TH1F*) m_histosObj->At(s))->Sumw2();
  }
}

// ==============================================================
void HistoManagerEffiFakeMuon::DefineHistos_vsPt() 
{
  //
  // definition of histograms for fake efficiency
  //

  int nbin = 1000;
  double mmin = 0.;
  double mmax = 1000.;

  TString mytypeid;

  TString name = "EffiFakeMuon_";
  TString myname;
  
  TString typeJet;
  TString typePt;

  // by PID bin
  for (int id=0;id<=m_binid;id++) {
    if (id==0) mytypeid = "_Loose";
    if (id==1) mytypeid = "_Tight";    
    
    // by jet bin
    for (int ijet=0;ijet<=m_binjet;ijet++) {
      typeJet = BinNJet(ijet);      

      // by PT bins
      for (int ipt=0;ipt<=m_binpt;ipt++) {
	typePt = BinPt(ipt);      
	
	// ETmiss
	myname  = name + "ETmiss" + mytypeid + typeJet + typePt; 
	hETmiss_vsPt[id][ijet][ipt] = 
	  new TH1F(myname,myname,nbin,mmin,mmax);
	m_histosObj->Add(hETmiss_vsPt[id][ijet][ipt]);

	// ETmissOverSqrtHT
	myname  = name + "ETmissOverSqrtHT" + mytypeid + typeJet + typePt; 
	hETmissOverSqrtHT_vsPt[id][ijet][ipt] = 
	  new TH1F(myname,myname,nbin,mmin,mmax);
	m_histosObj->Add(hETmissOverSqrtHT_vsPt[id][ijet][ipt]);
      }
    }
  }
}

// ==============================================================
void HistoManagerEffiFakeMuon::DefineHistos_vsEta() 
{
  //
  // definition of histograms for fake efficiency
  //

  int nbin = 1000;
  double mmin = 0.;
  double mmax = 1000.;

  TString mytypeid;

  TString name = "EffiFakeMuon_";
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
void HistoManagerEffiFakeMuon::DefineHistos_vsdRClosestJet() 
{
  //
  // definition of histograms for fake efficiency
  //

  int nbin = 1000;
  double mmin = 0.;
  double mmax = 1000.;

  TString mytypeid;

  TString name = "EffiFakeMuon_";
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
void HistoManagerEffiFakeMuon::DefineHistos_vsPtLeadingJet() 
{
  //
  // definition of histograms for fake efficiency
  //

  int nbin = 1000;
  double mmin = 0.;
  double mmax = 1000.;

  TString mytypeid;

  TString name = "EffiFakeMuon_";
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
void HistoManagerEffiFakeMuon::DefineHistos_vsDPhi() 
{
  //
  // definition of histograms for fake efficiency
  //

  int nbin = 1000;
  double mmin = 0.;
  double mmax = 1000.;

  TString mytypeid;

  TString name = "EffiFakeMuon_";
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
void HistoManagerEffiFakeMuon::DefineHistos_vsMET() 
{
  //
  // definition of histograms for fake efficiency
  //

  int nbin = 1000;
  double mmin = 0.;
  double mmax = 1000.;

  TString mytypeid;

  TString name = "EffiFakeMuon_";
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
void HistoManagerEffiFakeMuon::DefineHistos_vsMTW() 
{
  //
  // definition of histograms for fake efficiency
  //

  int nbin = 1000;
  double mmin = 0.;
  double mmax = 1000.;

  TString mytypeid;

  TString name = "EffiFakeMuon_";
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
void HistoManagerEffiFakeMuon::DefineHistos_vsNJet() 
{
  //
  // definition of histograms for fake efficiency
  //

  int nbin = 1000;
  double mmin = 0.;
  double mmax = 1000.;

  TString mytypeid;

  TString name = "EffiFakeMuon_";
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
void HistoManagerEffiFakeMuon::DefineHistos_vsNbJet() 
{
  //
  // definition of histograms for fake efficiency
  //

  int nbin = 1000;
  double mmin = 0.;
  double mmax = 1000.;

  TString mytypeid;

  TString name = "EffiFakeMuon_";
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

      // by NbJet bins
      for (int inbjet=0;inbjet<=m_binnbjet;inbjet++) {
	typeNbJet = BinNbJet(inbjet);      
	
	// ETmiss
	myname  = name + "ETmiss" + mytypeid + typeJet + typeNbJet; 
	hETmiss_vsNbJet[id][ijet][inbjet] = 
	  new TH1F(myname,myname,nbin,mmin,mmax);
	m_histosObj->Add(hETmiss_vsNbJet[id][ijet][inbjet]);
	
	// ETmissOverSqrtHT
	myname  = name + "ETmissOverSqrtHT" + mytypeid + typeJet + typeNbJet; 
	hETmissOverSqrtHT_vsNbJet[id][ijet][inbjet] = 
	  new TH1F(myname,myname,nbin,mmin,mmax);
	m_histosObj->Add(hETmissOverSqrtHT_vsNbJet[id][ijet][inbjet]);
      }
    }
  }
}

// ==============================================================
void HistoManagerEffiFakeMuon::DefineHistos_vsd0sig() 
{
  //
  // definition of histograms for real efficiency
  //

  int nbin = 1000;
  double mmin = 0.;
  double mmax = 1000.;

  TString mytypeid;

  TString name = "EffiFakeMuon_";
  TString myname;
  
  TString typeJet;
  TString typed0sig;

  // by PID bin
  for (int id=0;id<=m_binid;id++) {
    if (id==0) mytypeid = "_Loose";
    if (id==1) mytypeid = "_Tight";    

    // by jet bin
    for (int ijet=0;ijet<=m_binjet;ijet++) {
      typeJet = BinNJet(ijet);      

      // by d0sig bins
      for (int id0sig=0;id0sig<=m_bind0sig;id0sig++) {
	typed0sig = Bind0sig(id0sig);      
	
	// ETmiss
	myname  = name + "ETmiss" + mytypeid + typeJet + typed0sig; 
	hETmiss_vsd0sig[id][ijet][id0sig] = 
	  new TH1F(myname,myname,nbin,mmin,mmax);
	m_histosObj->Add(hETmiss_vsd0sig[id][ijet][id0sig]);
	
	// ETmissOverSqrtHT
	myname  = name + "ETmissOverSqrtHT" + mytypeid + typeJet + typed0sig; 
	hETmissOverSqrtHT_vsd0sig[id][ijet][id0sig] = 
	  new TH1F(myname,myname,nbin,mmin,mmax);
	m_histosObj->Add(hETmissOverSqrtHT_vsd0sig[id][ijet][id0sig]);
      }
    }
  }
}

// =================================================================
TString HistoManagerEffiFakeMuon::BinPt(int index)
{
  TString type="";

  if (index==0)  type = "_Pt_25to30GeV";
  if (index==1)  type = "_Pt_30to35GeV";
  if (index==2)  type = "_Pt_35to40GeV";
  if (index==3)  type = "_Pt_40to45GeV";
  if (index==4)  type = "_Pt_45to50GeV";
  if (index==5)  type = "_Pt_50to55GeV";
  if (index==6)  type = "_Pt_55to60GeV";
  if (index==7)  type = "_Pt_60to80GeV";
  if (index==8)  type = "_Pt_80to120GeV";
  if (index==9)  type = "_Pt_gt120GeV";
  if (index==10) type = "_Pt_gt80GeV"; 
  if (index==11) type = "_Pt_gt60GeV";
  if (index==12) type = "_Pt_gt50GeV";

  return type;
}

// =================================================================
TString HistoManagerEffiFakeMuon::BinEta(int index)
{
  TString type="";
  
  if (index==0) type = "_Eta_0to025";
  if (index==1) type = "_Eta_025to050";
  if (index==2) type = "_Eta_050to075";
  if (index==3) type = "_Eta_075to100";
  if (index==4) type = "_Eta_100to125";
  if (index==5) type = "_Eta_125to150";
  if (index==6) type = "_Eta_150to175";
  if (index==7) type = "_Eta_175to200";
  if (index==8) type = "_Eta_200to225";
  if (index==9) type = "_Eta_225to250";

  return type;
}

// =================================================================
TString HistoManagerEffiFakeMuon::BindRClosestJet(int index)
{
  TString type="";

  if (index==0) type = "_dRClosestJet_04to06";
  if (index==1) type = "_dRClosestJet_06to08";
  if (index==2) type = "_dRClosestJet_08to10";
  if (index==3) type = "_dRClosestJet_10to15";
  if (index==4) type = "_dRClosestJet_15to20";
  if (index==5) type = "_dRClosestJet_gt20";
 
  return type;
}

// =================================================================
TString HistoManagerEffiFakeMuon::BinPtLeadingJet(int index)
{
  TString type="";

  if (index==0) type = "_PtLeadingJet_25to50GeV";
  if (index==1) type = "_PtLeadingJet_50to75GeV";
  if (index==2) type = "_PtLeadingJet_75to100GeV";
  if (index==3) type = "_PtLeadingJet_100to150GeV";
  if (index==4) type = "_PtLeadingJet_gt150GeV";

  return type;
}

// =================================================================
TString HistoManagerEffiFakeMuon::BinDPhi(int index)
{
  TString type="";

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
TString HistoManagerEffiFakeMuon::BinMET(int index)
{
  TString type="";

  if (index==0) type = "_MET_0to10";
  if (index==1) type = "_MET_10to20";
  if (index==2) type = "_MET_20to30";
  if (index==3) type = "_MET_30to40";
  if (index==4) type = "_MET_40to60";
  if (index==5) type = "_MET_60to100";
  if (index==6) type = "_MET_100to150";
  if (index==7) type = "_MET_150to200";
  if (index==8) type = "_MET_gt200";

  return type;
}

// =================================================================
TString HistoManagerEffiFakeMuon::BinMTW(int index)
{
  TString type="";

  if (index==0) type = "_MTW_0to10";
  if (index==1) type = "_MTW_10to20";
  if (index==2) type = "_MTW_20to30";
  if (index==3) type = "_MTW_30to40";
  if (index==4) type = "_MTW_40to60";
  if (index==5) type = "_MTW_60to100";
  if (index==6) type = "_MTW_100to150";
  if (index==7) type = "_MTW_150to200";
  if (index==8) type = "_MTW_gt200";

  return type;
}

// =================================================================
TString HistoManagerEffiFakeMuon::Bind0sig(int index)
{
  TString type="";

  if (index==0)  type = "_d0sig_0to1";
  if (index==1)  type = "_d0sig_1to2";
  if (index==2)  type = "_d0sig_2to3";
  if (index==3)  type = "_d0sig_3to4";
  if (index==4)  type = "_d0sig_4to5";
  if (index==5)  type = "_d0sig_5to6";
  if (index==6)  type = "_d0sig_6to7";
  if (index==7)  type = "_d0sig_7to8";
  if (index==8)  type = "_d0sig_8to9";
  if (index==9)  type = "_d0sig_9to10";
  if (index==10) type = "_d0sig_gt10";

  return type;
}

// =================================================================
TString HistoManagerEffiFakeMuon::BinNJet(int index)
{
  TString type="";

  if (index==0) type = "_0j";
  if (index==1) type = "_1j";
  if (index==2) type = "_ge1j";
  if (index==3) type = "_ge2j";
  if (index==4) type = "_2or3j";
  if (index==5) type = "_ge4j";

  return type;
}

// =================================================================
TString HistoManagerEffiFakeMuon::BinNJet2(int index)
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
TString HistoManagerEffiFakeMuon::BinNbJet(int index)
{
  TString type="";

  if (index==0) type = "_0bJet";
  if (index==1) type = "_1bJet";
  if (index==2) type = "_ge1bJet";
  if (index==3) type = "_ge2bJet";

  return type;
}
