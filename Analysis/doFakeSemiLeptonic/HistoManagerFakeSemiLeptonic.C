#define HistoManagerFakeSemiLeptonic_cxx
//////////////////////////////////////////////////////////////////////
// 
// Author   : Atlas LPNHE Paris
// Creation : 01/10/2015
// Purpose  : base class to manage efficiency histograms for lepton+jets
// Updated  :
//////////////////////////////////////////////////////////////////////

#include "HistoManagerFakeSemiLeptonic.h"

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TObjArray.h>

ClassImp(HistoManagerFakeSemiLeptonic);

// Constructor
HistoManagerFakeSemiLeptonic::HistoManagerFakeSemiLeptonic(TObjArray *histosObj)
{
  // retrieve histogram 
  m_histosObj = histosObj;

  // book histograms
  DefineHistos();
}

// ==============================================================
// DESTRUCTOR:
HistoManagerFakeSemiLeptonic::~HistoManagerFakeSemiLeptonic()
{ 
  // loop on type of lepton 
  for (int itype=0;itype<2;itype++) {
    // loop on level of MET/MTW 
    for (int ilevel=0;ilevel<5;ilevel++) {
      // loop on level of cut
      for (int icut=0;icut<84;icut++) {

	//histo containing fake yield
	delete hFakeYield[itype][ilevel][icut];
	//histo containing the squared systematic error on the fake yield
	delete hFakeYieldSqSys[itype][ilevel][icut];

	// ET miss
	delete hETmiss[itype][ilevel][icut];
	// HT sum
	delete hHTsum[itype][ilevel][icut];
	// mTW sum
	delete hmTW[itype][ilevel][icut];
	// number of good jets
	delete hnjet[itype][ilevel][icut];
	delete hnbjet[itype][ilevel][icut];
	// Closest jet
	delete hdRClosestJet[itype][ilevel][icut];
	delete hbWeightClosestJet[itype][ilevel][icut];
	delete hpTClosestJet[itype][ilevel][icut];
	delete hetaClosestJet[itype][ilevel][icut];
	delete hphiClosestJet[itype][ilevel][icut];
	// max bWeight 
	delete hdRmaxbJet[itype][ilevel][icut];
	delete hpTmaxbJet[itype][ilevel][icut];
	delete hetamaxbJet[itype][ilevel][icut];
	delete hphimaxbJet[itype][ilevel][icut];
	delete hbWeightmaxbJet[itype][ilevel][icut];
	// leading jet
	delete hdRLeadingJet[itype][ilevel][icut];
	delete hpTLeadingJet[itype][ilevel][icut];
	delete hetaLeadingJet[itype][ilevel][icut];
	delete hphiLeadingJet[itype][ilevel][icut];
	delete hbWeightLeadingJet[itype][ilevel][icut];
	// delta Phi (lept-ETmiss)
	delete hdeltaPhiLeptETmiss[itype][ilevel][icut];
	// for electron
	// charge of the lepton
	delete hchargelept[itype][ilevel][icut];
	// pt of the lepton
	delete hpTlept[itype][ilevel][icut];
	// eta of the lepton
	delete hetalept[itype][ilevel][icut];
	// phi of the lepton
	delete hphilept[itype][ilevel][icut];
	// ETCone20
	delete hETCone20lept[itype][ilevel][icut];
	// pTCone30
	delete hpTCone30lept[itype][ilevel][icut];
      }
    }
  }
}

// =================================================================
void HistoManagerFakeSemiLeptonic::DefineHistos() 
{
  //
  // definition of histograms
  //

  int nbin = 500;
  double mmax = 500.;
  double mmin = 0.;
  
  TString name = "";
  TString suffix = "";
  TString typeLept = "";
  TString typeLevel = "";
  TString typeCut = "";

  // loop on type of lepton 
  for (int itype=0;itype<2;itype++) {
    if (itype==0) typeLept = "_EJet";
    else if (itype==1) typeLept = "_MuJet";

    // loop on level of MET/MTW 
    for (int ilevel=0;ilevel<5;ilevel++) {
      if (ilevel==0) typeLevel = "_noMETMTW";
      else if (ilevel==1) typeLevel = "_METMTWgt30";
      else if (ilevel==2) typeLevel = "_METMTWgt2060";
      else if (ilevel==3) typeLevel = "_METMTWlt2060";
      else if (ilevel==4) typeLevel = "_METMTWlt60";

      // loop on level of cut
      for (int icut=0;icut<84;icut++) {
	// >=6 jets
	if (icut==0)       typeCut =  "_ge6j_pretag";
	else if (icut==1)  typeCut =  "_ge6j_alltag";
	else if (icut==2)  typeCut =  "_ge6j_0btag";
	else if (icut==3)  typeCut =  "_ge6j_1btag";
	else if (icut==4)  typeCut =  "_ge6j_2btag";
	else if (icut==5)  typeCut =  "_ge6j_ge1btag";
	else if (icut==6)  typeCut =  "_ge6j_ge2btag";
	// ==6 jets
	else if (icut==7)  typeCut =  "_6j_pretag";
	else if (icut==8)  typeCut =  "_6j_alltag";
	else if (icut==9)  typeCut =  "_6j_0btag";
	else if (icut==10) typeCut =  "_6j_1btag";
	else if (icut==11) typeCut =  "_6j_2btag";
	else if (icut==12) typeCut =  "_6j_ge1btag";
	else if (icut==13) typeCut =  "_6j_ge2btag";
	// >=5 jets
	else if (icut==14) typeCut =  "_ge5j_pretag";
	else if (icut==15) typeCut =  "_ge5j_alltag";
	else if (icut==16) typeCut =  "_ge5j_0btag";
	else if (icut==17) typeCut =  "_ge5j_1btag";
	else if (icut==18) typeCut =  "_ge5j_2btag";
	else if (icut==19) typeCut =  "_ge5j_ge1btag";
	else if (icut==20) typeCut =  "_ge5j_ge2btag";
	// ==5 jets
	else if (icut==21) typeCut =  "_5j_pretag";
	else if (icut==22) typeCut =  "_5j_alltag";
	else if (icut==23) typeCut =  "_5j_0btag";
	else if (icut==24) typeCut =  "_5j_1btag";
	else if (icut==25) typeCut =  "_5j_2btag";
	else if (icut==26) typeCut =  "_5j_ge1btag";
	else if (icut==27) typeCut =  "_5j_ge2btag";
	// >=4 jets
	else if (icut==28) typeCut =  "_ge4j_pretag";
	else if (icut==29) typeCut =  "_ge4j_alltag";
	else if (icut==30) typeCut =  "_ge4j_0btag";
	else if (icut==31) typeCut =  "_ge4j_1btag";
	else if (icut==32) typeCut =  "_ge4j_2btag";
	else if (icut==33) typeCut =  "_ge4j_ge1btag";
	else if (icut==34) typeCut =  "_ge4j_ge2btag";
	// ==4 jets
	else if (icut==35) typeCut =  "_4j_pretag";
	else if (icut==36) typeCut =  "_4j_alltag";
	else if (icut==37) typeCut =  "_4j_0btag";
	else if (icut==38) typeCut =  "_4j_1btag";
	else if (icut==39) typeCut =  "_4j_2btag";
	else if (icut==40) typeCut =  "_4j_ge1btag";
	else if (icut==41) typeCut =  "_4j_ge2btag";
	// >=3 jets
	else if (icut==42) typeCut =  "_ge3j_pretag";
	else if (icut==43) typeCut =  "_ge3j_alltag";
	else if (icut==44) typeCut =  "_ge3j_0btag";
	else if (icut==45) typeCut =  "_ge3j_1btag";
	else if (icut==46) typeCut =  "_ge3j_2btag";
	else if (icut==47) typeCut =  "_ge3j_ge1btag";
	else if (icut==48) typeCut =  "_ge3j_ge2btag";
	// ==3 jets
	else if (icut==49) typeCut =  "_3j_pretag";
	else if (icut==50) typeCut =  "_3j_alltag";
	else if (icut==51) typeCut =  "_3j_0btag";
	else if (icut==52) typeCut =  "_3j_1btag";
	else if (icut==53) typeCut =  "_3j_2btag";
	else if (icut==54) typeCut =  "_3j_ge1btag";
	else if (icut==55) typeCut =  "_3j_ge2btag";
	// >=2 jets
	else if (icut==56) typeCut =  "_ge2j_pretag";
	else if (icut==57) typeCut =  "_ge2j_alltag";
	else if (icut==58) typeCut =  "_ge2j_0btag";
	else if (icut==59) typeCut =  "_ge2j_1btag";
	else if (icut==60) typeCut =  "_ge2j_2btag";
	else if (icut==61) typeCut =  "_ge2j_ge1btag";
	else if (icut==62) typeCut =  "_ge2j_ge2btag";
	// ==2 jets
	else if (icut==63) typeCut =  "_2j_pretag";
	else if (icut==64) typeCut =  "_2j_alltag";
	else if (icut==65) typeCut =  "_2j_0btag";
	else if (icut==66) typeCut =  "_2j_1btag";
	else if (icut==67) typeCut =  "_2j_2btag";
	else if (icut==68) typeCut =  "_2j_ge1btag";
	else if (icut==69) typeCut =  "_2j_ge2btag";
	// >=1 jet
	else if (icut==70) typeCut =  "_ge1j_pretag";
	else if (icut==71) typeCut =  "_ge1j_alltag";
	else if (icut==72) typeCut =  "_ge1j_0btag";
	else if (icut==73) typeCut =  "_ge1j_1btag";
	else if (icut==74) typeCut =  "_ge1j_2btag";
	else if (icut==75) typeCut =  "_ge1j_ge1btag";
	else if (icut==76) typeCut =  "_ge1j_ge2btag";
	// ==1 jet
	else if (icut==77) typeCut =  "_1j_pretag";
	else if (icut==78) typeCut =  "_1j_alltag";
	else if (icut==79) typeCut =  "_1j_0btag";
	else if (icut==80) typeCut =  "_1j_1btag";
	else if (icut==81) typeCut =  "_1j_2btag";
	else if (icut==82) typeCut =  "_1j_ge1btag";
	else if (icut==83) typeCut =  "_1j_ge2btag";
	
	suffix = typeLept + typeLevel + typeCut;
	
	// Yields
	name = "hSemiLeptonicYield";
	name += suffix;
	hFakeYield[itype][ilevel][icut] = new TH1F(name,name,1,0.,1.);
	hFakeYield[itype][ilevel][icut]->Sumw2();
	// syst. Yields
	name = "hSemiLeptonicYieldSqSys";
	name += suffix;
	hFakeYieldSqSys[itype][ilevel][icut] = new TH1F(name,name,1,0.,1.);
	hFakeYieldSqSys[itype][ilevel][icut]->Sumw2();

	// ETmiss
	name  = "hSemiLeptonicETmiss";
	name += suffix;
	hETmiss[itype][ilevel][icut] = new TH1F(name,name,nbin,mmin,mmax);
	hETmiss[itype][ilevel][icut]->Sumw2();
	m_histosObj->Add(hETmiss[itype][ilevel][icut]);
	
	// HTsum
	name  = "hSemiLeptonicHTsum";
	name += suffix;
	hHTsum[itype][ilevel][icut] = new TH1F(name,name,500,0.,500.);
	hHTsum[itype][ilevel][icut]->Sumw2();
	m_histosObj->Add(hHTsum[itype][ilevel][icut]);
	
	// mTW
	name  = "hSemiLeptonictransvmass";
	name += suffix;
	hmTW[itype][ilevel][icut] = new TH1F(name,name,500,0.,500.);
	hmTW[itype][ilevel][icut]->Sumw2();
	m_histosObj->Add(hmTW[itype][ilevel][icut]);
	
	// number of jets
	name  = "hSemiLeptonicnjet";
	name += suffix;
	hnjet[itype][ilevel][icut] = new TH1F(name,name,10,-0.5,9.5);
	hnjet[itype][ilevel][icut]->Sumw2();
	m_histosObj->Add(hnjet[itype][ilevel][icut]);
	
	// number of b-tagged jets
	name  = "hSemiLeptonicnbjet";
	name += suffix;
	hnbjet[itype][ilevel][icut] = new TH1F(name,name,10,-0.5,9.5);
	hnbjet[itype][ilevel][icut]->Sumw2();
	m_histosObj->Add(hnbjet[itype][ilevel][icut]);
	
	// =====================================================
	// distance to the closest jet
	name  = "hSemiLeptonicdRClosestJet";
	name += suffix;
	hdRClosestJet[itype][ilevel][icut] = new TH1F(name,name,100,0.,10.);
	hdRClosestJet[itype][ilevel][icut]->Sumw2();
	m_histosObj->Add(hdRClosestJet[itype][ilevel][icut]);      
	
	// pT of the closest jet
	name  = "hSemiLeptonicpTClosestJet";
	name += suffix;
	hpTClosestJet[itype][ilevel][icut] = new TH1F(name,name,300,0,300.);
	hpTClosestJet[itype][ilevel][icut]->Sumw2();
	m_histosObj->Add(hpTClosestJet[itype][ilevel][icut]);      
	
	// eta of the closest jet
	name  = "hSemiLeptonicetaClosestJet";
	name += suffix;
	hetaClosestJet[itype][ilevel][icut] = new TH1F(name,name,50,-2.5,2.5);
	hetaClosestJet[itype][ilevel][icut]->Sumw2();
	m_histosObj->Add(hetaClosestJet[itype][ilevel][icut]);      
	
	// phi of the closest jet
	name  = "hSemiLeptonicphiClosestJet";
	name += suffix;
	hphiClosestJet[itype][ilevel][icut] = new TH1F(name,name,100,-3.2,3.2);
	hphiClosestJet[itype][ilevel][icut]->Sumw2();
	m_histosObj->Add(hphiClosestJet[itype][ilevel][icut]);      
	
	// weight of the closest jet
	name  = "hSemiLeptonicbWeightClosestJet";
	name += suffix;
	hbWeightClosestJet[itype][ilevel][icut] = new TH1F(name,name,100,0.,1.);
	hbWeightClosestJet[itype][ilevel][icut]->Sumw2();
	m_histosObj->Add(hbWeightClosestJet[itype][ilevel][icut]);      
	
	// ======================================================
	// distance to the bjet
	name  = "hSemiLeptonicdRmaxbJet";
	name += suffix;
	hdRmaxbJet[itype][ilevel][icut] = new TH1F(name,name,100,0.,10.);
	hdRmaxbJet[itype][ilevel][icut]->Sumw2();
	m_histosObj->Add(hdRmaxbJet[itype][ilevel][icut]);       

	// pT of the maxb jet
	name  = "hSemiLeptonicpTmaxbJet";
	name += suffix;
	hpTmaxbJet[itype][ilevel][icut] = new TH1F(name,name,300,0,300.);
	hpTmaxbJet[itype][ilevel][icut]->Sumw2();
	m_histosObj->Add(hpTmaxbJet[itype][ilevel][icut]);      
	
	// eta of the maxb jet
	name  = "hSemiLeptonicetamaxbJet";
	name += suffix;
	hetamaxbJet[itype][ilevel][icut] = new TH1F(name,name,50,-2.5,2.5);
	hetamaxbJet[itype][ilevel][icut]->Sumw2();
	m_histosObj->Add(hetamaxbJet[itype][ilevel][icut]);      
	
	// phi of the maxb jet
	name  = "hSemiLeptonicphimaxbJet";
	name += suffix;
	hphimaxbJet[itype][ilevel][icut] = new TH1F(name,name,100,-3.2,3.2);
	hphimaxbJet[itype][ilevel][icut]->Sumw2();
	m_histosObj->Add(hphimaxbJet[itype][ilevel][icut]);      

	// weight of the bjet
	name  = "hSemiLeptonicbWeightmaxbJet";
	name += suffix;
	hbWeightmaxbJet[itype][ilevel][icut] = new TH1F(name,name,100,0.,1.);
	hbWeightmaxbJet[itype][ilevel][icut]->Sumw2();
	m_histosObj->Add(hbWeightmaxbJet[itype][ilevel][icut]);      
	
	// =====================================
	// distance to the leading jet
	name  = "hSemiLeptonicdRLeadingJet";
	name += suffix;
	hdRLeadingJet[itype][ilevel][icut] = new TH1F(name,name,100,0.,10.);
	hdRLeadingJet[itype][ilevel][icut]->Sumw2();
	m_histosObj->Add(hdRLeadingJet[itype][ilevel][icut]);      
	
	// pT of the leading jet
	name  = "hSemiLeptonicpTLeadingJet";
	name += suffix;
	hpTLeadingJet[itype][ilevel][icut] = new TH1F(name,name,300,0,300.);
	hpTLeadingJet[itype][ilevel][icut]->Sumw2();
	m_histosObj->Add(hpTLeadingJet[itype][ilevel][icut]);      
	
	// eta of the leading jet
	name  = "hSemiLeptonicetaLeadingJet";
	name += suffix;
	hetaLeadingJet[itype][ilevel][icut] = new TH1F(name,name,50,-2.5,2.5);
	hetaLeadingJet[itype][ilevel][icut]->Sumw2();
	m_histosObj->Add(hetaLeadingJet[itype][ilevel][icut]);      
	
	// phi of the leading jet
	name  = "hSemiLeptonicphiLeadingJet";
	name += suffix;
	hphiLeadingJet[itype][ilevel][icut] = new TH1F(name,name,100,-3.2,3.2);
	hphiLeadingJet[itype][ilevel][icut]->Sumw2();
	m_histosObj->Add(hphiLeadingJet[itype][ilevel][icut]);      
	
	// weight of the leading jet
	name  = "hSemiLeptonicbWeightLeadingJet";
	name += suffix;
	hbWeightLeadingJet[itype][ilevel][icut] = new TH1F(name,name,100,0.,1.);
	hbWeightLeadingJet[itype][ilevel][icut]->Sumw2();
	m_histosObj->Add(hbWeightLeadingJet[itype][ilevel][icut]);      

	// ================================================
	// deltaPhi (lept-ETmiss)
	name  = "hSemiLeptonicdeltaPhiLeptETmiss"; 
	name += suffix;
	hdeltaPhiLeptETmiss[itype][ilevel][icut] = new TH1F(name,name,100,-3.2,3.2);
	hdeltaPhiLeptETmiss[itype][ilevel][icut]->Sumw2();
	m_histosObj->Add(hdeltaPhiLeptETmiss[itype][ilevel][icut]);      
	
	// ==============================================
	// charge lepton
	name  = "hSemiLeptonicchargelept"; 
	name += suffix;
	hchargelept[itype][ilevel][icut] = new TH1F(name,name,3,-1.,1.);
	hchargelept[itype][ilevel][icut]->Sumw2();
	m_histosObj->Add(hchargelept[itype][ilevel][icut]);

	// ==============================================
	// pT lepton
	name  = "hSemiLeptonicptlept"; 
	name += suffix;
	hpTlept[itype][ilevel][icut] = new TH1F(name,name,200,0.,200.);
	hpTlept[itype][ilevel][icut]->Sumw2();
	m_histosObj->Add(hpTlept[itype][ilevel][icut]);
	
	// eta lepton
	name  = "hSemiLeptonicetalept"; 
	name += suffix;
	hetalept[itype][ilevel][icut] = new TH1F(name,name,50,-2.5,2.5);
	hetalept[itype][ilevel][icut]->Sumw2();
	m_histosObj->Add(hetalept[itype][ilevel][icut]);
	
	// phi lepton
	name  = "hSemiLeptonicphilept"; 
	name += suffix;
	hphilept[itype][ilevel][icut] = new TH1F(name,name,100,-3.2,3.2);
	hphilept[itype][ilevel][icut]->Sumw2();
	m_histosObj->Add(hphilept[itype][ilevel][icut]);
	
	// ETCone20
	name  = "hSemiLeptonicETCone20lept"; 
	name += suffix;
	hETCone20lept[itype][ilevel][icut] = new TH1F(name,name,70,-5.,30.);
	hETCone20lept[itype][ilevel][icut]->Sumw2();
	m_histosObj->Add(hETCone20lept[itype][ilevel][icut]);
	
	// pTCone30
	name  = "hSemiLeptonicpTCone30lept"; 
	name += suffix;
	hpTCone30lept[itype][ilevel][icut] = new TH1F(name,name,70,-5.,30.);
	hpTCone30lept[itype][ilevel][icut]->Sumw2();
	m_histosObj->Add(hpTCone30lept[itype][ilevel][icut]);
	
      }
    }
  }
}

