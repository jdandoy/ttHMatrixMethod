#include "TLegend.h"
#include "TProfile.h"
#include "TDirectory.h"

#include "AtlasUtils.h"
#include "AtlasLabels.h"
#include "AtlasStyle.h"
#include "AddMC.h"
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "TFile.h"
#include "TDirectory.h"
#include "TH1F.h"

void EffiFakeMuon()
{
  gROOT->LoadMacro("AddMC.C");

  EffiFakeMuon * myeffifakes = new EffiFakeMuon();
  
  return;
}

class EffiFakeMuon {
public:
  
  // =======================================
  EffiFakeMuon()
  {
    
    m_imin       = 0;
    m_imax       = 0;

    //bool isTOPQ1 = true;
    //TString leveliso = "_Iso6";
    //leveliso = "";
    TString levelmc = ""; 
    TString leveltrigger = "";
    for (int imc=1;imc<=1;imc++) {
      if (imc==0) levelmc = "_WZPowheg";
      if (imc==1) levelmc = "_WZSherpa";
      
      for (int ileveltrigger=2;ileveltrigger<=3;ileveltrigger++) {
	if (ileveltrigger==0) leveltrigger = "";
	if (ileveltrigger==1) leveltrigger = "_HLT_mu24"; //This is the one we need
	if (ileveltrigger==2) leveltrigger = "_HLT_mu24_ivarmedium";
	if (ileveltrigger==3) leveltrigger = "_HLT_mu50";
	
	/*bool effall            = false; // 0
	  bool effbinpt            = false; // 1
	  bool effbineta           = false; // 2 
	  bool effbindr            = false; // 3
	  bool effbinptleadjet     = false; // 4
	  bool effbindphi          = false; // 5
	  bool effbind0sig         = false; // 6
	  bool effbinmet           = false; // 7
	  bool effbinmtw           = false; // 8
	  bool effbinnjet          = false; // 9
	  bool effbinnbjet         = false; // 10
	*/
        //should be from 0 to 10
	for (int ieff=0;ieff<=10;ieff++) {
	  //std::cout << " ifit = " << ifit << std::endl;
	  effall              = false; // 0
	  effbinpt            = false; // 1 
	  effbineta           = false; // 2
	  effbindr            = false; // 3 
	  effbinptleadjet     = false; // 4
	  effbindphi          = false; // 5
	  effbind0sig         = false; // 6
	  effbinmet           = false; // 7
	  effbinmtw           = false; // 8
	  effbinnjet          = false; // 9
	  effbinnbjet         = false; // 10
	  
	  if (ieff==0)  effall              = true;
	  if (ieff==1)  effbinpt            = true;
	  if (ieff==2)  effbineta           = true;
	  if (ieff==3)  effbindr            = true;
	  if (ieff==4)  effbinptleadjet     = true;
	  if (ieff==5)  effbindphi          = true;
	  if (ieff==6)  effbind0sig         = true;
	  if (ieff==7)  effbinmet           = true;
	  if (ieff==8)  effbinmtw           = true;
	  if (ieff==9)  effbinnjet          = true;
	  if (ieff==10) effbinnbjet         = true; 
	  
	  //if (effbinpt)        {m_imin=1;m_imax=10;}
	  if (effbinpt)        {m_imin=1;m_imax=8;}
	  if (effbineta)       {m_imin=1;m_imax=10;}
	  if (effbindr)        {m_imin=1;m_imax=6;}
	  if (effbinptleadjet) {m_imin=1;m_imax=5;}
	  if (effbindphi)      {m_imin=1;m_imax=13;}
	  if (effbind0sig)     {m_imin=1;m_imax=11;}
	  if (effbinmet)       {m_imin=1;m_imax=9;}
	  if (effbinmtw)       {m_imin=1;m_imax=9;}
	  if (effbinnjet)      {m_imin=1;m_imax=5;}
	  if (effbinnbjet)     {m_imin=1;m_imax=3;}
	  
	  bool isCorrMC = true;
	
          //Input for Data
          //Input for MC
          //  /nfs/dust/atlas/group/top/Nedaa_Ntuples_MM/OutputHistos/output_MCMuons/
          // /nfs/dust/atlas/group/top/Nedaa_Ntuples_MM/OutputHistos/output_DataMuons/ 
	  // input directory name for data

	  //Input dir for Data
	  TString m_name_dir_input = "/nfs/dust/atlas/group/top/Nedaa_Ntuples_MM/OutputHistos/2016/Muon/Fakes_Data/";
    //Input directory name for MC
    TString m_name_dirmc_input = "/nfs/dust/atlas/group/top/Nedaa_Ntuples_MM/OutputHistos/2016/Muon/Fakes_MC/";	
          
	  TString name; 
	  TString cr        = "";
	  TString suffix    = "";
	  TString suffixout = ""; 
	  TString period    = "2016";
	  TString version = ".2412-fakesStd-1a";

	  // loop on CR
	  for (int icr=1;icr<=1;icr++) {
	    if (icr==0) cr    = "_highd0sig";
	    if (icr==1) cr    = "_lowETmissMTW"; //THis is the one
	    if (icr==2) cr    = "_lowETmiss20";
	    
	    // loop on sample
	    for (int isample=1;isample<=2;isample++) { //We are using pretag
	      //std::cout << " isample = " << isample << std::endl;
	      if (isample==0) sample    = "_pretag";
	      if (isample==1) sample    = "_nobtag";
	      if (isample==2) sample    = "_btag";
	      
	      // loop on jets
	      for (int ijet=0;ijet<=5;ijet++) {
		if (ijet==0) leveljet = "_0j";
		if (ijet==1) leveljet = "_1j";
		if (ijet==2) leveljet = "_ge1j";
		if (ijet==3) leveljet = "_ge2j";
		if (ijet==4) leveljet = "_2or3j";
		if (ijet==5) leveljet = "_ge4j";
		
		suffix    = cr+sample+leveltrigger+version;
		suffixout = cr+sample+leveltrigger+leveljet+version;
		std::cout << " suffix = " << suffix << " " << suffixout << std::endl;
		
		// =====================================
		// for data
		name = m_name_dir_input + "user.derue.";
		name += period; 
		name += ".physics_Main.DAOD_TOPQ1.f708_m1606_p2667.EffiFakeMuon";
                name+=suffix; name+="_output.root";
		std::cout << "data = " << name << std::endl;
		m_data_file = new TFile(name,"read");
		
		// ====================================
		// for MC
		if (isCorrMC) {
		  m_names = AddMC(imc);
		  
                  suffix    = cr+sample+leveltrigger+version;

		  m_mc_files.clear();
		  int indexmc = 0;
		  for (std::vector<TString>::iterator it = m_names.begin(); it < m_names.end(); it++) {
		    TString mcname = m_name_dirmc_input+*it+".EffiFakeMuon";
		    mcname += suffix; mcname+="_output.root";
		    m_f[indexmc] = new TFile(mcname,"read");
		    //std::cout << " file = " << indexmc << " " << mcname << std::endl;
		    m_mc_files.push_back(m_f[indexmc]);
		    indexmc++;
		  }
		}
		
		// ===========================================
		// Names of output files
		FILE *pFile[20][2];
		
		// open ascii file
		// all range
		if (effall) {
		  name = "eff-FakeMuon-Raw";  name += suffixout; name += "_vsAv";
		  pFile[0][0] = fopen (name+".txt","w");		
		  name = "eff-FakeMuon-CorrMC"; name+=levelmc;   name += suffixout; name += "_vsAv";
		  pFile[0][1] = fopen (name+".txt","w");
		}
		
		// vs ET
		if (effbinpt) {
		  name = "eff-FakeMuon-Raw";  name += suffixout; name += "_vsEt";
		  pFile[1][0] = fopen (name+".txt","w");		
		  name = "eff-FakeMuon-CorrMC"; name+=levelmc;   name += suffixout; name += "_vsEt";
		  pFile[1][1] = fopen (name+".txt","w");
		}
		
		// vs eta
		if (effbineta) {
		  name = "eff-FakeMuon-Raw";  name += suffixout; name += "_vsEta";
		  pFile[2][0] = fopen (name+".txt","w");		
		  name = "eff-FakeMuon-CorrMC"; name+=levelmc;   name += suffixout; name += "_vsEta";
		  pFile[2][1] = fopen (name+".txt","w");
		}
		
		// vs dRClosestJet
		if (effbindr) {
		  name = "eff-FakeMuon-Raw";  name += suffixout; name += "_vsdR";
		  pFile[3][0] = fopen (name+".txt","w");		
		  name = "eff-FakeMuon-CorrMC"; name+=levelmc;   name += suffixout; name += "_vsdR";
		  pFile[3][1] = fopen (name+".txt","w");
		}
		
		// vs PtLeadingJet
		if (effbinptleadjet) {
		  name = "eff-FakeMuon-Raw";  name += suffixout; name += "_vsPtLeadingJet";
		  pFile[4][0] = fopen (name+".txt","w");		
		  name = "eff-FakeMuon-CorrMC"; name+=levelmc;   name += suffixout; name += "_vsPtLeadingJet";
		  pFile[4][1] = fopen (name+".txt","w");
		}
		
		// vs dPhi
		if (effbindphi) {
		  name = "eff-FakeMuon-Raw";  name += suffixout; name += "_vsdPhi";
		  pFile[5][0] = fopen (name+".txt","w");		
		  name = "eff-FakeMuon-CorrMC"; name+=levelmc;   name += suffixout; name += "_vsdPhi";
		  pFile[5][1] = fopen (name+".txt","w");
		}

		// vs d0sig
		if (effbind0sig) {
		  name = "eff-FakeMuon-Raw";  name += suffixout; name += "_vsd0sig";
		  pFile[6][0] = fopen (name+".txt","w");		
		  name = "eff-FakeMuon-CorrMC"; name+=levelmc;   name += suffixout; name += "_vsd0sig";
		  pFile[6][1] = fopen (name+".txt","w");
		}

		// vs MET
		if (effbinmet) {
		  name = "eff-FakeMuon-Raw";  name += suffixout; name += "_vsMET";
		  pFile[7][0] = fopen (name+".txt","w");		
		  name = "eff-FakeMuon-CorrMC"; name+=levelmc;   name += suffixout; name += "_vsMET";
		  pFile[7][1] = fopen (name+".txt","w");
		}

		// vs MTW
		if (effbinmtw) {
		  name = "eff-FakeMuon-Raw";  name += suffixout; name += "_vsMTW";
		  pFile[8][0] = fopen (name+".txt","w");		
		  name = "eff-FakeMuon-CorrMC"; name+=levelmc;   name += suffixout; name += "_vsMTW";
		  pFile[8][1] = fopen (name+".txt","w");
		}
		
		// vs njet
		if (effbinnjet) {
		  name = "eff-FakeMuon-Raw";  name += suffixout; name += "_vsNJet";
		  pFile[9][0] = fopen (name+".txt","w");		
		  name = "eff-FakeMuon-CorrMC"; name+=levelmc;   name += suffixout; name += "_vsNjet";
		  pFile[9][1] = fopen (name+".txt","w");
		}

		// vs nbjet
		if (effbinnbjet) {
		  name = "eff-FakeMuon-Raw";  name += suffixout; name += "_vsNbJet";
		  pFile[10][0] = fopen (name+".txt","w");		
		  name = "eff-FakeMuon-CorrMC"; name+=levelmc;   name += suffixout; name += "_vsNbjet";
		  pFile[10][1] = fopen (name+".txt","w");
		}

		std::cout << " avant Init " << std::endl;
		initN(); 
		// read histograms from files
		std::cout << " avant readHist " << std::endl;
		this->readHists(isCorrMC,leveljet,leveltrigger);
		std::cout << " apres readHist " << std::endl;
		
		this->CalcEff(isCorrMC,icr,ileveltrigger,pFile);
		
		delete m_data_file;
		for (int ix=0;ix<indexmc;ix++) {
		  delete m_f[ix];
		}
	      }
	    }
	  }
	}
      }
    }
  }
  
  // =========================================
  void readHists(bool isCorrMC, TString leveljet, TString leveltrigger) 
  {
    TString nameloose;
    TString nametight;
    TString mynameloose;
    TString mynametight;
    TString finalloose;
    TString finaltight;
    TString type="";

    TH1F* htemploose = 0;
    TH1F* htemptight = 0;

    // fill data histos
    for (int ibin=m_imin;ibin<=m_imax;ibin++) {
      std::cout << " ibin = " << ibin << std::endl;
      nameloose   = "EffiFakeMuon_ETmiss_Loose"+leveljet;
      nametight   = "EffiFakeMuon_ETmiss_Tight"+leveljet;
      
      if (effbinpt)        type = GivePtName(ibin);
      if (effbineta)       type = GiveEtaName(ibin);
      if (effbindr)        type = GivedRClosestJetName(ibin);
      if (effbinptleadjet) type = GivePtLeadingJetName(ibin);
      if (effbindphi)      type = GiveDPhiName(ibin);
      if (effbind0sig)     type = Gived0sigName(ibin);
      if (effbinmet)       type = GiveMETName(ibin);
      if (effbinmtw)       type = GiveMTWName(ibin);
      if (effbinnjet)      type = GiveNJetName(ibin);
      if (effbinnbjet)     type = GiveNbJetName(ibin);
	      
      mynameloose = nameloose+type;
      mynametight = nametight+type;
      std::cout << " mynameloose = " << mynameloose << " " << mynametight << std::endl;
      htemploose  = (TH1F*) m_data_file->GetDirectory("HistosEffiFakeMuon")->Get(mynameloose);
      htemptight  = (TH1F*) m_data_file->GetDirectory("HistosEffiFakeMuon")->Get(mynametight);
      m_NDataLoose[ibin] = htemploose->GetSumOfWeights();
      m_NDataTight[ibin] = htemptight->GetSumOfWeights();
    }
    
    std::cout << " pass data " << std::endl;
    //  
    // fill MC histos 
    if (isCorrMC) {
      int indexmc = 0;
      for (std::vector<TFile*>::iterator it = m_mc_files.begin(); it < m_mc_files.end(); it++) {
	// loop on bins
	for (int ibin=m_imin;ibin<=m_imax;ibin++) {
	  //build histoname
	  nameloose   = "EffiFakeMuon_ETmiss_Loose"+leveljet;
	  nametight   = "EffiFakeMuon_ETmiss_Tight"+leveljet;
	  
	  if (effbinpt)        type = GivePtName(ibin);
	  if (effbineta)       type = GiveEtaName(ibin);
	  if (effbindr)        type = GivedRClosestJetName(ibin);
	  if (effbinptleadjet) type = GivePtLeadingJetName(ibin);
	  if (effbindphi)      type = GiveDPhiName(ibin);
	  if (effbind0sig)     type = Gived0sigName(ibin);
	  if (effbinmet)       type = GiveMETName(ibin);
	  if (effbinmtw)       type = GiveMTWName(ibin);
	  if (effbinnjet)      type = GiveNJetName(ibin);
	  if (effbinnbjet)     type = GiveNbJetName(ibin);
		  
	  mynameloose = nameloose+type;
	  mynametight = nametight+type;
		  
	  // get histos from files
	  htemploose = (TH1F*) (*it)->GetDirectory("HistosEffiFakeMuon")->Get(mynameloose);
	  htemptight = (TH1F*) (*it)->GetDirectory("HistosEffiFakeMuon")->Get(mynametight);
	  //float lumi = 3209.05;
    float lumi = 5822.83;
	  // should apply a prescale
	  if (leveltrigger=="_HLT_mu20_L1MU15") lumi /= 10.;
	  float factor = 1.;
	  m_NMCLoose[ibin] += factor*lumi*htemploose->GetSumOfWeights();
	  m_NMCTight[ibin] += factor*lumi*htemptight->GetSumOfWeights();

	  if (htemploose->GetSumOfWeights()>0)
	    m_ErrNMCLoose[ibin] += htemploose->GetSumOfWeights()*htemploose->GetSumOfWeights();
	  if (htemptight->GetSumOfWeights()>0)
	    m_ErrNMCTight[ibin] += htemptight->GetSumOfWeights()*htemptight->GetSumOfWeights();
	}
	indexmc++;
      }
      
      std::cout << " pass mc " << std::endl;
      // loop on bins
      for (int ibin=m_imin;ibin<=m_imax;ibin++) {
	m_ErrNMCLoose[ibin] = sqrt(m_ErrNMCLoose[ibin]);
	m_ErrNMCTight[ibin] = sqrt(m_ErrNMCTight[ibin]);
      }
    }
  }
  
  // =============================================
  void CalcEff(bool isCorrMC, int icr, int ileveltrigger, FILE *pFile[10][2])
  {
    char* nameBin      = "";
    float Bin          = 0.;
    float errBin       = 0.;
    
    std::cout<<" ============================================"<<std::endl;
    std::cout<<" ============ Results in bins   ============="<<std::endl;
    std::cout<<" ============================================"<<std::endl;
    
    for (int ibin=m_imin;ibin<=m_imax;ibin++) {
      PrepareASCII(ibin,icr);
      std::cout << " bin=" << ibin << " " << m_nameBin << std::endl; 
	      
      // retrieve number of events
      float ndataloose = m_NDataLoose[ibin];
      float ndatatight = m_NDataTight[ibin];
      float nmcloose   = m_NMCLoose[ibin];
      float nmctight   = m_NMCTight[ibin];
	      
      // efficiencies
      float effraw = 0.;
      if (ndataloose>0.) effraw = ndatatight/ndataloose;
      float erreffraw = 0.;
      if (ndataloose>0.) erreffraw = sqrt(effraw*(1.-effraw)/ndataloose);
      effraw *= 100.;
      erreffraw *= 100.;
      float effcorr = 0.;
      if ((ndataloose-nmcloose)>0.) 
	effcorr = (ndatatight-nmctight)/(ndataloose-nmcloose);
      float erreffcorr = 0.;
      if ((ndataloose-nmcloose)>0.) {
	erreffcorr = ndatatight+nmctight+effcorr*effcorr*(ndataloose+nmcloose);
	// remove covariance term
	erreffcorr -= 2.*effcorr*(ndatatight+nmctight);
	erreffcorr  = sqrt(erreffcorr);
	erreffcorr /=(ndataloose-nmcloose); 	  
      }
      effcorr *= 100.;
      erreffcorr *= 100.;
      std::cout<<"ndataloose = "<<ndataloose<<" ndatatight  = "<<ndatatight;
      std::cout<<" nmcloose = "<<nmcloose<<" nmctight  = "<<nmctight<<std::endl;	
      std::cout<< " effraw = " << effraw << " +/- " << erreffraw 
	       << " effcorr = " << effcorr << " +/- " << erreffcorr << std::endl;
      
      
      WriteFiles(ileveltrigger,ibin,
		 effraw,erreffraw,effcorr,erreffcorr,pFile);
    }
  }

  // =======================================================
  void WriteFiles(int ileveltrigger, int ibin, 
		  float effraw, float erreffraw, 
		  float effcorr, float erreffcorr,
		  FILE *pFile[20][2])
  {
    int index = -1;
    // for all bins
    if (effall) {
      fprintf(pFile[0][0],"%6.2f %4.2f\n",effraw,erreffraw);
      fprintf(pFile[0][1],"%6.2f %4.2f\n",effcorr,erreffcorr);
    } else {
      if (effbinpt)        {
	index = 1;
	// avoid negative values for high pt trigger
	if (ileveltrigger==2 && ibin<6) {
	  effcorr = 0.;
	  erreffcorr = 0.;
	}
	if ((ileveltrigger==1 || ileveltrigger==3) && ibin>=6) {
	  effcorr = 0.;
	  erreffcorr = 0.;
	}
      }
      if (effbineta)       index = 2;
      if (effbindr)        index = 3;
      if (effbinptleadjet) index = 4;
      if (effbindphi)      index = 5;
      if (effbind0sig)     index = 6;
      if (effbinmet)       index = 7;
      if (effbinmtw)       index = 8;
      if (effbinnjet)      index = 9;
      if (effbinnbjet)     index = 10;
     
      fprintf(pFile[index][0],"%6.2f %6.2f %6.2f %4.2f\n",
	      m_Bin,m_errBin,effraw,erreffraw);
      fprintf(pFile[index][1],"%6.2f %6.2f %6.2f %4.2f\n",
	      m_Bin,m_errBin,effcorr,erreffcorr);
    }
  }
  
  // ==========================================
  void PrepareASCII(int ibin, int icr)
  {
    m_nameBin  = "";
    m_Bin      = 0.;
    m_errBin   = 0.;

    // =====================================================
    // vs ET
    if (effbinpt) {
      if (ibin==1) {
	m_nameBin = "25-30";
	m_Bin = 27.5;
	m_errBin = 2.5;
      }
      if (ibin==2) {
	m_nameBin = "30-35";
	m_Bin = 32.5;
	m_errBin = 2.5;
      }
      if (ibin==3) {
	m_nameBin = "35-40";
	m_Bin = 37.5;
	m_errBin = 2.5;
      }
      if (ibin==4) {
	m_nameBin = "40-45";
	m_Bin = 42.5;
	m_errBin = 2.5;
      }
      if (ibin==5) {
	m_nameBin = "45-50";
	m_Bin = 47.5;
	m_errBin = 2.5;
      }
      if (ibin==6) {
	m_nameBin = "50-55";
	m_Bin = 52.5;
	m_errBin = 2.5;
      }
      if (ibin==7) {
	m_nameBin = "55-60";
	m_Bin = 57.5;
	m_errBin = 2.5;
      }
      if (ibin==8) {
	m_nameBin = "\$>\$ 60";
	m_Bin = 105.;
	m_errBin = 45.;
      }
      /*if (ibin==8) {
	m_nameBin = "60-80";
	m_Bin = 70.;
	m_errBin = 10.;
      }
      if (ibin==9) {
	m_nameBin = "80-120";
	m_Bin = 100.;
	m_errBin = 20.;
      }
      if (ibin==10) {
	m_nameBin = "\$>\$ 120";
	m_Bin = 135.;
	m_errBin = 15.;
      }*/
    }

    // ======================================
    // vs Eta
    if (effbineta) {
      if (ibin==1) {
	m_nameBin = "0,0.25";
	m_Bin = 0.125;
	m_errBin = 0.125;
      }
      if (ibin==2) {
	m_nameBin = "0.25,0.50";
	m_Bin = 0.375;
	m_errBin = 0.125;
      }
      if (ibin==3) {
	m_nameBin = "0.50,0.75";
	m_Bin = 0.625;
	m_errBin = 0.125;
      }
      if (ibin==4) {
	m_nameBin = "0.75,1.00";
	m_Bin = 0.875;
	m_errBin = 0.125;
      }
      if (ibin==5) {
	m_nameBin = "1.00,1.25";
	m_Bin = 1.125;
	m_errBin = 0.25;
      }
      if (ibin==6) {
	m_nameBin = "1.25,1.50";
	m_Bin = 1.375;
	m_errBin = 0.125;
      }
      if (ibin==7) {
	m_nameBin = "1.50,1.75";
	m_Bin = 1.625;
	m_errBin = 0.125;
      }
      if (ibin==8) {
	m_nameBin = "1.75,2.00";
	m_Bin = 1.875;
	m_errBin = 0.125;
      }
      if (ibin==9) {
	m_nameBin = "2.00,2.25";
	m_Bin = 2.125;
	m_errBin = 0.125;
      }
      if (ibin==10) {
	m_nameBin = "2.25,2.50";
	m_Bin = 2.325;
	m_errBin = 0.125;
      }
    }
    
    // ===========================
    // vs dR
    if (effbindr) {
      if (ibin==1) {
	m_nameBin = "0.4-0.6";
	m_Bin = 0.5;
	m_errBin = 0.1;
      }
      if (ibin==2) {
	m_nameBin = "0.6-0.8";
	m_Bin = 0.7;
	m_errBin = 0.1;
      }
      if (ibin==3) {
	m_nameBin = "0.8-1.0";
	m_Bin = 0.9;
	m_errBin = 0.1;
      }
      if (ibin==4) {
	m_nameBin = "1.0-1.5";
	m_Bin = 1.25;
	m_errBin = 0.25;
      }
      if (ibin==5) {
	m_nameBin = "1.5-2.0";
	m_Bin = 1.75;
	m_errBin = 0.25;
      }
      if (ibin==6) {
	m_nameBin = "$>$2";
	m_Bin = 4.;
	m_errBin = 2.;
      }
    }

    // ===================================================
    // vs Pt Leading Jet
    if (effbinptleadjet) {
      if (ibin==1) {
	m_nameBin = "25-50";
	m_Bin = 37.5;
	m_errBin = 12.5;
      }
      if (ibin==2) {
	m_nameBin = "50-75";
	m_Bin = 62.5;
	m_errBin = 12.5;
      }
      if (ibin==3) {
	m_nameBin = "75-100";
	m_Bin = 87.5;
	m_errBin = 12.5;
      }
      if (ibin==4) {
	m_nameBin = "100-150";
	m_Bin = 125.;
	m_errBin = 25.;
      }
      if (ibin==4) {
	m_nameBin = "\$>\$ 150";
	m_Bin = 575.;
	m_errBin = 425.;
      }
    }
    
    // ============================================
    // vs dPhi
    if (effbindphi) {
      if (ibin==1) {
	m_nameBin = "0;0.1";
	m_Bin = 0.05;
	m_errBin = 0.05;
      }
      if (ibin==2) {
	m_nameBin = "0.1;0.2";
	m_Bin = 0.15;
	m_errBin = 0.05;
      }
      if (ibin==3) {
	m_nameBin = "0.2;0.3";
	m_Bin = 0.25;
	m_errBin = 0.05;
      }
      if (ibin==4) {
	m_nameBin = "0.3;0.4";
	m_Bin = 0.35;
	m_errBin = 0.05;
      }
      if (ibin==5) {
	m_nameBin = "0.5;0.75";
	m_Bin = 0.625;
	m_errBin = 0.125;
      }
      if (ibin==6) {
	m_nameBin = "0.75;1.0";
	m_Bin = 0.875;
	m_errBin = 0.125;
      }
      if (ibin==7) {
	m_nameBin = "1.0;1.25";
	m_Bin = 1.125;
	m_errBin = 0.125;
      }
      if (ibin==8) {
	m_nameBin = "1.25;1.5";
	m_Bin = 1.375;
	m_errBin = 0.125;
      }
      if (ibin==9) {
	m_nameBin = "1.5;1.75";
	m_Bin = 1.625;
	m_errBin = 0.125;
      }
      if (ibin==10) {
	m_nameBin = "1.75;2.0";
	m_Bin = 1.875;
	m_errBin = 0.125;
      }
      if (ibin==11) {
	m_nameBin = "2.0;2.5";
	m_Bin = 2.25;
	m_errBin = 0.25;
      }
      if (ibin==12) {
	m_nameBin = "2.5;pi";
	m_Bin = 2.82;
	m_errBin = 0.32;
      }
    }

    // ============================================
    // vs d0sig
    if (effbind0sig) {
      if (ibin==1) {
	m_nameBin = "0;1";
	m_Bin = 0.5;
	m_errBin = 0.5;
      }
      if (ibin==2) {
	m_nameBin = "1;2";
	m_Bin = 1.5;
	m_errBin = 0.5;
      }
      if (ibin==3) {
	m_nameBin = "2;3";
	m_Bin = 2.5;
	m_errBin = 0.5;
      }
      if (ibin==4) {
	m_nameBin = "3;4";
	m_Bin = 3.5;
	m_errBin = 0.5;
      }
      if (ibin==5) {
	m_nameBin = "4;5";
	m_Bin = 4.5;
	m_errBin = 0.5;
      }
      if (ibin==6) {
	m_nameBin = "5;6";
	m_Bin = 5.5;
	m_errBin = 0.5;
      }
      if (ibin==7) {
	m_nameBin = "6;7";
	m_Bin = 6.5;
	m_errBin = 0.5;
      }
      if (ibin==8) {
	m_nameBin = "7;8";
	m_Bin = 7.5;
	m_errBin = 0.5;
      }
      if (ibin==9) {
	m_nameBin = "8;9";
	m_Bin = 8.5;
	m_errBin = 0.5;
      }
      if (ibin==10) {
	m_nameBin = "9;10";
	m_Bin = 9.5;
	m_errBin = 0.5;
      }
      if (ibin==11) {
	m_nameBin = "\$>\$ 10";
	m_Bin = 10.5;
	m_errBin = 0.5;
      }
    }

    // ===================================================
    // vs MET or vs MTW
    if (effbinmet || effbinmtw) {
      if (ibin==1) {
	m_nameBin = "0-10";
	m_Bin = 5.0;
	m_errBin = 5.;
      }
      if (ibin==2) {
	m_nameBin = "10-20";
	m_Bin = 15.;
	m_errBin = 5.;
      }
      if (ibin==3) {
	m_nameBin = "20-30";
	m_Bin = 25.;
	m_errBin = 5.;
      }
      if (ibin==4) {
	m_nameBin = "30-40";
	m_Bin = 35.;
	m_errBin = 5.;
      }
      if (ibin==5) {
	m_nameBin = "40-60";
	m_Bin = 50.;
	m_errBin = 10.;
      }
      if (ibin==6) {
	m_nameBin = "60-100";
	m_Bin = 80.;
	m_errBin = 20.;
      }
      if (ibin==7) {
	m_nameBin = "100-150";
	m_Bin = 125.;
	m_errBin = 25.;
      }
      if (ibin==8) {
	m_nameBin = "150-200";
	m_Bin = 175.;
	m_errBin = 25.;
      }
      if (ibin==9) {
	m_nameBin = "\$>\$ 200";
	m_Bin = 600.;
	m_errBin = 400.;
      }
    }
    
    // ===================================================
    // vs Njet
    if (effbinnjet) {
      if (ibin==1) {
	m_nameBin = "0";
	m_Bin = 0.;
	m_errBin = 0.5;
      }
      if (ibin==2) {
	m_nameBin = "1";
	m_Bin = 1.;
	m_errBin = 0.5;
      }
      if (ibin==3) {
	m_nameBin = "2";
	m_Bin = 2.;
	m_errBin = 0.5;
      }
      if (ibin==4) {
	m_nameBin = "3";
	m_Bin = 3.;
	m_errBin = 0.5;
      }
      if (ibin==5) {
	m_nameBin = "\$>=\$ 4";
	m_Bin = 4.;
	m_errBin = 0.5;
      }
    }

    // ===================================================
    // vs Nbjet
    if (effbinnbjet) {
      if (ibin==1) {
	m_nameBin = "0";
	m_Bin = 0.;
	m_errBin = 0.5;
      }
      if (ibin==1) {
	m_nameBin = "2";
	m_Bin = 1.;
	m_errBin = 0.5;
      }
      if (ibin==2) {
	m_nameBin = "\$>=\$ 2";
	m_Bin = 2.;
	m_errBin = 0.5;
      }
    }
  }
  
  // =============================================
  void plotHists()
  {
    Style();    
  } 
  
  // =============================================
  void plotEffHists()
  {
    char canvname[100];
    
    Style();
  }

  // ================================================
  void plotEff(TH1F *h) 
  {
    h->SetMinimum(0.);
    h->SetMaximum(1.); 
    h->SetLineWidth(2);
    h->SetLineColor(1);
    h->SetMarkerStyle(20);
    h->SetMarkerColor(1);
    h->Draw("P");
  }
  
  // ==============================
  void initN() 
  {
    for (int ibin=m_imin;ibin<=m_imax;ibin++) {
      m_NDataLoose[ibin] = 0;
      m_NDataTight[ibin] = 0;
      m_NMCLoose[ibin] = 0;
      m_NMCTight[ibin] = 0;
      m_ErrNDataLoose[ibin] = 0;
      m_ErrNDataTight[ibin] = 0;
      m_ErrNMCLoose[ibin] = 0;
      m_ErrNMCTight[ibin] = 0;
    }
  }
  
private:

  bool effall;
  bool effbinpt;
  bool effbineta;
  bool effbindr;
  bool effbinptleadjet;
  bool effbindphi;
  bool effbind0sig;
  bool effbinmet;
  bool effbinmtw;
  bool effbinnjet;
  bool effbinnbjet;

  int m_indexfile;
  int m_imin;
  int m_imax;

  char* m_nameBin;
  float m_Bin;
  float m_errBin;

  // for data
  float m_NDataLoose[20];
  float m_ErrNDataLoose[20];
  float m_NDataTight[20];
  float m_ErrNDataTight[20];
  float m_NMCLoose[20];
  float m_ErrNMCLoose[20];
  float m_NMCTight[20];
  float m_ErrNMCTight[20];
  
  TString m_name_dir_input;
  std::vector<TString> m_names; 
  std::vector<TFile*> m_mc_files;
  TFile* m_data_file;
  TFile *m_f[400];

  TCanvas* m_c[33]; 
  
  // ===================================================================
  void Style()
  {
    gROOT->Reset();
    gROOT->SetStyle("ATLAS");
    gROOT->ForceStyle();
    
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
  }
  
  // =================================================================
  TString GivePtName(int index)
  {
    TString type="";
    
    if (index==1)  type = "_Pt_25to30GeV";
    if (index==2)  type = "_Pt_30to35GeV";
    if (index==3)  type = "_Pt_35to40GeV";
    if (index==4)  type = "_Pt_40to45GeV";
    if (index==5)  type = "_Pt_45to50GeV";
    if (index==6)  type = "_Pt_50to55GeV";
    if (index==7)  type = "_Pt_55to60GeV";
    if (index==8) type = "_Pt_gt60GeV";
    //if (index==8)  type = "_Pt_60to80GeV";
    //if (index==9)  type = "_Pt_80to120GeV";
    //if (index==10) type = "_Pt_gt120GeV";

    return type;
  }
  
  // =================================================================
  TString GiveEtaName(int index)
  {
    TString type="";

    if (index==1)  type = "_Eta_0to025";
    if (index==2)  type = "_Eta_025to050";
    if (index==3)  type = "_Eta_050to075";
    if (index==4)  type = "_Eta_075to100";
    if (index==5)  type = "_Eta_100to125";
    if (index==6)  type = "_Eta_125to150";
    if (index==7)  type = "_Eta_150to175";
    if (index==8)  type = "_Eta_175to200";
    if (index==9)  type = "_Eta_200to225";
    if (index==10) type = "_Eta_225to250";

    return type;
  }
  
  // =================================================================
  TString GivedRClosestJetName(int index)
  {
    TString type="";
    
    if (index==1) type = "_dRClosestJet_04to06";
    if (index==2) type = "_dRClosestJet_06to08";
    if (index==3) type = "_dRClosestJet_08to10";
    if (index==4) type = "_dRClosestJet_10to15";
    if (index==5) type = "_dRClosestJet_15to20";
    if (index==6) type = "_dRClosestJet_gt20";

    return type;
  }

  // =================================================================
  TString GivePtLeadingJetName(int index)
  {
    TString type="";
    
    if (index==1) type = "_PtLeadingJet_25to50GeV";
    if (index==2) type = "_PtLeadingJet_50to75GeV";
    if (index==3) type = "_PtLeadingJet_75to100GeV";
    if (index==4) type = "_PtLeadingJet_100to150GeV";
    if (index==5) type = "_PtLeadingJet_gt150GeV";

    return type;
  }

  // =================================================================
  TString GiveDPhiName(int index)
  {
    TString type="";
    
    if (index==1)  type = "_DPhi_0to010";
    if (index==2)  type = "_DPhi_010to020";
    if (index==3)  type = "_DPhi_020to030";
    if (index==4)  type = "_DPhi_030to040";
    if (index==5)  type = "_DPhi_040to050";
    if (index==6)  type = "_DPhi_050to075";
    if (index==7)  type = "_DPhi_075to100";
    if (index==8)  type = "_DPhi_100to125";
    if (index==9)  type = "_DPhi_125to150";
    if (index==10) type = "_DPhi_150to175";
    if (index==11) type = "_DPhi_175to200";
    if (index==12) type = "_DPhi_200to250";
    if (index==13) type = "_DPhi_250topi";

    return type;
  }

  // =================================================================
  TString Gived0sigName(int index)
  {
    TString type="";
    
    if (index==1)  type = "_d0sig_0to1";
    if (index==2)  type = "_d0sig_1to2";
    if (index==3)  type = "_d0sig_2to3";
    if (index==4)  type = "_d0sig_3to4";
    if (index==5)  type = "_d0sig_4to5";
    if (index==6)  type = "_d0sig_5to6";
    if (index==7)  type = "_d0sig_6to7";
    if (index==8)  type = "_d0sig_7to8";
    if (index==9)  type = "_d0sig_8to9";
    if (index==10) type = "_d0sig_9to10";
    if (index==11) type = "_d0sig_gt10";
  
    return type;
  }

  // =================================================================
  TString GiveMETName(int index)
  {
    TString type="";
    
    if (index==1)  type = "_MET_0to10";
    if (index==2)  type = "_MET_10to20";
    if (index==3)  type = "_MET_20to30";
    if (index==4)  type = "_MET_30to40";
    if (index==5)  type = "_MET_40to60";
    if (index==6)  type = "_MET_60to100";
    if (index==7)  type = "_MET_100to150";
    if (index==8)  type = "_MET_150to200";
    if (index==9)  type = "_MET_gt200";

    return type;
  }

  // =================================================================
  TString GiveMTWName(int index)
  {
    TString type="";
    
    if (index==1)  type = "_MTW_0to10";
    if (index==2)  type = "_MTW_10to20";
    if (index==3)  type = "_MTW_20to30";
    if (index==4)  type = "_MTW_30to40";
    if (index==5)  type = "_MTW_40to60";
    if (index==6)  type = "_MTW_60to100";
    if (index==7)  type = "_MTW_100to150";
    if (index==8)  type = "_MTW_150to200";
    if (index==9)  type = "_MTW_gt200";

    return type;
  }

  // =================================================================
  TString GiveNJetName(int index)
  {
    TString type="";
    
    if (index==1) type = "_0Jet";
    if (index==2) type = "_1Jet";
    if (index==3) type = "_2Jet";
    if (index==4) type = "_3Jet";
    if (index==5) type = "_ge4Jet";

    return type;
  }

  // =================================================================
  TString GiveNbJetName(int index)
  {
    TString type="";
    
    if (index==1) type = "_0bJet";
    if (index==2) type = "_1bJet";
    if (index==3) type = "_ge2bJet";

    return type;
  }

};
 
