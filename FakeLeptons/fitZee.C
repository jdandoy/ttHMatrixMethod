#include <TMath.h>
#include <TFile.h>
#include <TH1.h>
#include <TCanvas.h>

#include <RooRealVar.h>
#include <RooArgList.h>
#include <RooAbsPdf.h>
#include <RooBreitWigner.h>
#include <RooExponential.h>
#include <RooChebychev.h>
#include <RooExtendPdf.h>
#include <RooNovosibirsk.h>
#include <RooBukinPdf.h>
#include <RooAddPdf.h>
#include <RooPlot.h>
#include <RooDataHist.h>
#include <RooDataSet.h>
#include <RooFitResult.h>
#include <RooNumConvPdf.h>
#include <RooDecay.h>
#include <RooTruthModel.h>
#include <RooLandau.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "AtlasUtils.h"
#include "AtlasLabels.h"
#include "AtlasStyle.h"

#ifndef __CINT__
#include <RooGlobalFunc.h>
#endif

using namespace RooFit;

void fitZee()
{
  gROOT->LoadMacro("AtlasStyle.C");
  gROOT->LoadMacro("AtlasUtils.C");
  gROOT->LoadMacro("AtlasLabels.C");
  
  SetAtlasStyle();

  fitZee *my = new fitZee();
  
  return;
}

class fitZee { 
public:
  
  // =============================================
  fitZee() 
  {
    //
    // Performs fitting of di-electron mass in Z mass range
    //
    
    TFile *InputFileOS;
    int m_nfiles = 1;
    
    int m_min = -1;
    int m_max = -1;
    
    bool isTOPQ1 = false;
    TString leveliso = "_Iso6";
    //leveliso = "";

    //
    // boolean to perform fit or not
    //
    bool dofit = false;
    
    //
    // boolean to perform fit on OS-SS
    //
    bool doosss = false;
    
    TString level1 = "";
    TString level2 = "";
    TString namelevel = "";
    // changed it from 4 to 0
    TString leveljet = "";
    for (int ileveljet=0;ileveljet<=0;ileveljet++) {
      if (ileveljet==0) leveljet = "-njeteq1";
      if (ileveljet==1) leveljet = "-njeteq2or3";
      if (ileveljet==2) leveljet = "-njetge4";
      if (ileveljet==3) leveljet = "-njetge1";
      if (ileveljet==4) leveljet = "-njetge2";
      
      for (int ileveltrigger=0;ileveltrigger<=0;ileveltrigger++) {
	TString leveltrigger = "";
	if (ileveltrigger==0) leveltrigger = "";
	if (ileveltrigger==1) leveltrigger = "_HLT_e24_lhmedium_iloose_L1EM20VH";
	if (ileveltrigger==2) leveltrigger = "_HLT_e24_lhmedium_L1EM20VH";
	if (ileveltrigger==3) leveltrigger = "_HLT_e60_lhmedium";
	if (ileveltrigger==4) leveltrigger = "_HLT_e120_lhloose";
	
	level1 = "_Loose";
	level2 = "_Tight";
	namelevel = "";

	// input directory name for data
	TString m_name_dir_input = "";
	if (isTOPQ1) m_name_dir_input = "/nfs/dust/atlas/group/top/Nedaa_Ntuples_MM/OutputHistos/output_Data_TP/";
	else m_name_dir_input = "/data/atlas0/data/DATA/DATA15/DAOD_EXOT4/filt/HistFinal/EffiFakeElec/";

	TString name;
	TString nameP     = "DtoJ";
	TString cr        = "";
	TString suffix    = "";
	TString suffixout = "";
	TString period    = "periodDtoJ";
	TString version = ".2341";
	
	suffix = leveljet+version;
	// =====================================
	// for data
	name = m_name_dir_input + "user.derue.Data-";
	name += period; 
	if (isTOPQ1)
	  name += ".physics_Main.DAOD_TOPQ1.p2452.EffiRealElecTP";
	else
	  name += ".physics_Main.DAOD_EXOT4.p2425.EffiRealElecTP";
	name+=leveliso; name+=leveltrigger; name+=suffix; name+=".root";
	std::cout << "data = " << name << std::endl;
	InputFileOS = new TFile(name,"read");
	
	// in case of Histo rebinning (use 1 (default) or 2)
	// other values might not give good efficiencies (as things are hardcoded
	// only for these two values)
	int nrebin = 1;
	
	//
	// fit all (eta,pt) range or individual bins
	//
	/*bool effall              = false; // 0
	  bool effbinpt            = false; // 1
	  bool effbineta           = false; // 2 
	  bool effbindr            = false; // 3
	  bool effbinptdr          = false; // 4
	  bool effbinptleadjet     = false; // 5
	  bool effbindphi          = false; // 6 
	  bool effbinmet           = false; // 7
	  bool effbinmtw           = false; // 8 
	*/
	for (int ieff=8;ieff<=9;ieff++) {
	  effall              = false; // 0
	  effbinpt            = false; // 1 
	  effbineta           = false; // 2
	  effbindr            = false; // 3
	  effbinptleadjet     = false; // 4
	  effbindphi          = false; // 5
	  effbinmet           = false; // 6
	  effbinmtw           = false; // 7
	  effbinnjet          = false; // 8
	  effbinnbjet         = false; // 9
	  
	  if (ieff==0)  effall              = true;
	  if (ieff==1)  effbinpt            = true;
	  if (ieff==2)  effbineta           = true;
	  if (ieff==3)  effbindr            = true;
	  if (ieff==4)  effbinptleadjet     = true;
	  if (ieff==5)  effbindphi          = true;
	  if (ieff==6)  effbinmet           = true;
	  if (ieff==7)  effbinmtw           = true;
	  if (ieff==8)  effbinnjet          = true;
	  if (ieff==9)  effbinnbjet         = true;
	  
	  if (effbinpt)        {m_imin=1;m_imax=10;}
	  if (effbineta)       {m_imin=1;m_imax=10;}
	  if (effbindr)        {m_imin=1;m_imax=6;}
	  if (effbinptleadjet) {m_imin=1;m_imax=5;}
	  if (effbindphi)      {m_imin=1;m_imax=13;}
	  if (effbinmet)       {m_imin=1;m_imax=9;}
	  if (effbinmtw)       {m_imin=1;m_imax=9;}
	  if (effbinnjet)      {m_imin=1;m_imax=5;}
	  if (effbinnbjet)     {m_imin=1;m_imax=3;}
	  
	  // which signal model (default=1)
	  // 1 = Conv (convolution of a Crystal Ball and a BreitWigner) 
	  // 2 = Conv an fixed (a and n parameters of CB are fixed, from MC in general)
	  // 3 = Conv ans fixed (a, n and s parameters of CB are fixed, from MC in general)
	  // 4 = CB (Crystal Ball) 
	  // 5 = CB an fixed (Crystal Ball, a and n parameters fixed, from MC in general)
	  // 6 = CB ans fixed (Crystal Ball, a, n and s parameters fixed, from MC in general)
	  // 7 = Voigt (Voigtian)
	  // 8 = BW (Breit-Wigner)
	  int sigmodel=1;
	  TString nameSigModel = "";
	  if (sigmodel==1) nameSigModel = "Conv";
	  if (sigmodel==2) nameSigModel = "Convanfixed";
	  if (sigmodel==3) nameSigModel = "Convansfixed";
	  if (sigmodel==4) nameSigModel = "CB";
	  if (sigmodel==5) nameSigModel = "CBanfixed";
	  if (sigmodel==6) nameSigModel = "CBansfixed";
	  if (sigmodel==7) nameSigModel = "Voigt";
	  if (sigmodel==8) nameSigModel = "BW";
	  
	  // which background model (default=1)
	  // 1 = RooDecay (exp*Gaussian)
	  // 2 = Cheb
	  // 3 = Exp
	  // 4 = Landau
	  for (int bkgmodel=1;bkgmodel<=1;bkgmodel++) {
	    TString nameBkgModel="";
	    if (bkgmodel==1) nameBkgModel="ExpG";
	    if (bkgmodel==2) nameBkgModel="Exp";
	    if (bkgmodel==3) nameBkgModel="Landau";
	    if (bkgmodel==4) nameBkgModel="Pol";
	    
	    // fit range (default=1)
	    //int fitrange = 1; // 55-200 GeV
	    //int fitrange = 2; // 60-150 GeV
	    for (int fitrange=1;fitrange<=1;fitrange++) {
	      TString nameFitRange = "";
	      if (fitrange==1) nameFitRange="-Fit55to200-";
	      if (fitrange==2) nameFitRange="-Fit60to150-";
	      
	      // interpretation range (default=1)
	      //int interpretrange=1; // 81-101
	      //int interpretrange=2; // 76-106
	      //int interpretrange=3; // 86-96
	      for (int interpretrange=1;interpretrange<=1;interpretrange++) {
		TString nameI="";
		if (interpretrange==1) nameI="Yield81to101";
		if (interpretrange==2) nameI="Yield76to106";
		if (interpretrange==3) nameI="Yield86to96";
		
		//
		// define names of output files (containing the efficiencies, .txt)
		//
		// open ascii file
		FILE * pFile[3];
		//TString nameFile="result-fit.txt";
		TString nameFile="eff-Zee-periodDtoJ";
		nameFile += nameSigModel;
		nameFile += nameBkgModel;
		nameFile += nameFitRange;	  
		nameFile+=nameI;
		nameFile += leveliso;	  
		nameFile += leveltrigger;	  
		nameFile += leveljet;	  

		if (effall)                   nameFile+="_vsAv.txt";
		else if (effbinpt)            nameFile+="_vsEt.txt";
		else if (effbineta)           nameFile+="_vsEta.txt";
		else if (effbindr)            nameFile+="_vsdR.txt";
		else if (effbindphi)          nameFile+="_vsdPhi.txt";
		else if (effbinptleadjet)     nameFile+="_vsPtLeadingJet.txt";
		else if (effbinmet)           nameFile+="_vsMET.txt";
		else if (effbinmtw)           nameFile+="_vsMTW.txt";
		else if (effbinnjet)          nameFile+="_vsnjet.txt";
		else if (effbinnbjet)         nameFile+="_vsnbjet.txt";
		else nameFile+=".txt";
		if (dofit) pFile[0] = fopen (nameFile,"w");
		
		nameFile="eff-Zee-periodDtoJ";
		nameFile += "-SB-";
		nameFile+=nameI;
		nameFile += leveliso;
		nameFile += leveltrigger;
		nameFile += leveljet;

		if (effall)                   nameFile+="_vsAv.txt";
		else if (effbinpt)            nameFile+="_vsEt.txt";
		else if (effbineta)           nameFile+="_vsEta.txt";
		else if (effbindr)            nameFile+="_vsdR.txt";
		else if (effbindphi)          nameFile+="_vsdPhi.txt";
		else if (effbinptleadjet)     nameFile+="_vsPtLeadingJet.txt";
		else if (effbinmet)           nameFile+="_vsMET.txt";
		else if (effbinmtw)           nameFile+="_vsMTW.txt";
		else if (effbinnjet)          nameFile+="_vsnjet.txt";
		else if (effbinnbjet)         nameFile+="_vsnbjet.txt";
		else nameFile+=".txt";
		pFile[1] = fopen (nameFile,"w");
		
		nameFile="eff-Zee-periodDtoJ";
		nameFile += "-OSSS-";
		nameFile+=nameI;
		nameFile += leveliso;
		nameFile += leveltrigger;
		nameFile += leveljet;

		if (effall)                   nameFile+="_vsAv.txt";
		else if (effbinpt)            nameFile+="_vsEt.txt";
		else if (effbineta)           nameFile+="_vsEta.txt";
		else if (effbindr)            nameFile+="_vsdR.txt";
		else if (effbindphi)          nameFile+="_vsdPhi.txt";
		else if (effbinptleadjet)     nameFile+="_vsPtLeadingJet.txt";
		else if (effbinmet)           nameFile+="_vsMET.txt";
		else if (effbinmtw)           nameFile+="_vsMTW.txt";
		else if (effbinnjet)          nameFile+="_vsnjet.txt";
		else if (effbinnbjet)         nameFile+="_vsnbjet.txt";
		else nameFile+=".txt";
		pFile[2] = fopen (nameFile,"w");
		
		float N[2][3];
		float ErrN[2][3];
		for (int i=0;i<2;i++) {
		  for (int j=0;j<3;j++) {
		    N[i][j]    = 0.;
		    ErrN[i][j] = 0.;
		  }
		}
		
		// different configurations of fits are predefined
		// performs fits before and after identification
		// and calculates the corresponding efficiencies		
		execute(dofit,doosss,0,
			fitrange,interpretrange,sigmodel,bkgmodel,
			pFile,m_nfiles,InputFileOS,nrebin,
			level1,level2);
		
		for (int i=0;i<3;i++) {
		  if (dofit) fclose (pFile[i]);    
		}
	      }
	    }
	  }
	}
      }
    }
  }

  // =====================================================
  void execute(bool dofit,bool doosss,int period,
	       int fitrange,int interpretrange,int sigmodel,int bkgmodel,
	       FILE *pFile[3], int m_nfiles, TFile *FileOS,
	       int nrebin, TString level1, TString level2)
  {
    // number of loose events
    float Nloose[2][3];
    // error on number of loose events
    float ErrNloose[2][3];
    // number of tight events
    float Ntight[2][3];
    // error on number of tight events
    float ErrNtight[2][3];
    
    // reduced chisquare
    double Reducedchi2loose   = 0.;
    double Reducedchi2tight   = 0.;
    
    float Nlooseperbin[2][3][20];
    float ErrNlooseperbin[2][3][20];
    double Reducedchi2looseperbin[20];
    float Ntightperbin[2][3][20];
    float ErrNtightperbin[2][3][20];
    double Reducedchi2tightperbin[20];
    double eff = 0.;
    double Erreff = 0.;
    
    // loop on all bins
    for (int ibin=m_imin;ibin<=m_imax;ibin++) {
      // initialization
      for (int i=0;i<2;i++) {
	for (int j=0;j<3;j++) {
	  Nloose[i][j]     = 0.;
	  ErrNloose[i][j]  = 0.;
	  Ntight[i][j]     = 0.;
	  ErrNtight[i][j]  = 0.;
	}
      }
      Reducedchi2loose  = 0.;
      Reducedchi2tight  = 0.;
      
      // for loose
      doFits(dofit,doosss,ibin,
	     true,false,period,
	     Nloose,ErrNloose,Reducedchi2loose,
	     fitrange,interpretrange,
	     sigmodel,bkgmodel,
	     m_nfiles,FileOS,nrebin,
	     level1,level2);

      // for tight
      doFits(dofit,doosss,ibin,
	     false,true,period,
	     Ntight,ErrNtight,Reducedchi2tight,
	     fitrange,interpretrange,
	     sigmodel,bkgmodel,
	     m_nfiles,FileOS,nrebin,
	     level1,level2);
      
      for (int i=0;i<2;i++) {
	for (int j=0;j<3;j++) {
	  //std::cout << " i = " << i << " " << j << " " << ipt << " " << ieta << " " << iptdr << " " << Nloose[i][j] << std::endl;
	  Nlooseperbin[i][j][ibin]    = Nloose[i][j];
	  Ntightperbin[i][j][ibin]    = Ntight[i][j];
	  ErrNlooseperbin[i][j][ibin] = ErrNloose[i][j];
	  ErrNtightperbin[i][j][ibin] = ErrNtight[i][j];
	}
      }
      Reducedchi2looseperbin[ibin] = Reducedchi2loose;
      Reducedchi2tightperbin[ibin] = Reducedchi2tight;
    
    } // end of loop
  
    // obtain results
    CalcAllEffsPerBin(dofit,
		      Nlooseperbin,ErrNlooseperbin,
		      Ntightperbin,ErrNtightperbin,
		      Reducedchi2looseperbin,
		      Reducedchi2tightperbin,
		      fitrange,interpretrange,
		      sigmodel,bkgmodel,
		      pFile);
    
    return;
  }

  // ================================================================
  doFits(bool dofit,bool doosss,int ibin,
	 bool loose,bool tight,int period,
	 float N[2][3], float ErrN[2][3], 
	 double& Reducedchi2,
	 int fitrange, int interpretrange,
	 int sigmodel, int bkgmodel, 
	 int nfiles, TFile *FileOS,
	 int nrebin, TString level1, TString level2) 
  {
    // 
    // constructor of class to perform fit of Z mass
    //
    // loose  = true : check invariant mass after "Loose" definition
    // tight  = true : check invariant mass after "Tight" definition
    //

    // do extended fit or not 
    // (include poisson errors for statistical fluctuations)
    bool doextended = true;

    // range to define Mee and to fit it
    float xmin   = 55.;
    float xmax   = 200.;
    if (fitrange==1) {
      xmin = 55.;
      xmax = 200.;
    }
    if (fitrange==2) {
      xmin = 60.;
      xmax = 150.;
    }
    float defmin = 81.;
    float defmax = 101.;
    if (interpretrange==1) {
      defmin = 81.;
      defmax = 101.;
    }
    if (interpretrange==2) {
      defmin = 76.;
      defmax = 106.;
    }
    if (interpretrange==3) {
      defmin = 86.;
      defmax = 96.;
    }
    float fitmin = xmin;
    float fitmax = xmax;
   
    // which signal model
    isConv        = false;
    isGauss       = false;
    isBW          = false;
    isVoigt       = false;
    isCB          = false;
    isNovosibirsk = false;
    // which background model
    isExp      = false;
    isRooDecay = false;
    isCheb     = false;
    isLandau   = false;

    // parameters to initialize the Pdf of background
    float dgs_mean = 0., dgs_mean_min = 0., dgs_mean_max = 0.;
    float dgs_sigma = 0., dgs_sigma_min = 0., dgs_sigma_max = 0.;
    float dgs_pdf = 0., dgs_pdf_min = 0., dgs_pdf_max = 0.;
    float ded_arg = 0., dec_arg_min = 0., dec_arg_max = 0.;

     // which signal model
    if (sigmodel==1 || sigmodel==2 || sigmodel==3) isConv        = true;
    if (sigmodel==4 || sigmodel==5 || sigmodel==6) isCB          = true;
    if (sigmodel==7) isVoigt       = true;
    if (sigmodel==8) isBW          = true;
    // check if parameters of CB have to be free or not    
    int isfreeParam = 1;
    if (sigmodel==2 || sigmodel==5) isfreeParam = 3;
    if (sigmodel==3 || sigmodel==6) isfreeParam = 2;

    // which background model
    if (bkgmodel==1) isRooDecay = true;
    if (bkgmodel==2) isExp      = true;
    if (bkgmodel==3) isLandau   = true;     
    if (bkgmodel==4) isCheb     = true;
     
    bool isMC = false;
    
    // =============================================
    // Read input histograms
    // =============================================
    m_nfiles = nfiles;
    m_InputFileOS = FileOS;

    // construct name of input histogram
    NameInputHisto(ibin,loose,tight,level1,level2); 
    // retrieve the histogram
    // for opposite sign (OS), same sign (SS), and OS-SS
    TH1F *histoOS, *histoSS, *histoOSSS;
    histoOS = (TH1F*) m_InputFileOS->GetDirectory("HistosEffiRealElecTP")->Get(m_nameHistoOS);
    std::cout << " histoOS = " << histoOS << std::endl;
    histoSS = (TH1F*) m_InputFileOS->GetDirectory("HistosEffiRealElecTP")->Get(m_nameHistoSS);
    std::cout << " histoSS = " << histoSS << std::endl;
    histoOSSS = (TH1F*)histoOS->Clone();
    histoOSSS->Add(histoSS,-1);
    std::cout << " histoOSSS = " << histoOSSS << std::endl;

    // number of OS events in fit range
    //int NeventOS = histoOS->Integral(1,500);  // 50-200 GeV
    int NeventOS = histoOS->Integral(163,203); // 81-101 GeV
    int NeventSS = histoSS->Integral(163,203); // 81-101 GeV
    if (interpretrange==1) {
      NeventOS = histoOS->Integral(163,203); // 81-101 GeV
      NeventSS = histoSS->Integral(163,203); // 81-101 GeV
    }
    if (interpretrange==2) {
      NeventOS = histoOS->Integral(153,213); // 76-106 GeV
      NeventSS = histoSS->Integral(153,213); // 76-106 GeV
    }
    if (interpretrange==3) {
      NeventOS = histoOS->Integral(173,193); // 86-96 GeV
      NeventSS = histoSS->Integral(173,193); // 86-96 GeV
    }
    std::cout << " NEvent total = " << histoOS->Integral(1,500) << std::endl;
    std::cout << " NEvent = " << NeventOS << " " << NeventSS << std::endl;


    // perform rebinning if necessary
    histoOS->Rebin(nrebin);
    histoSS->Rebin(nrebin);
    histoOSSS->Rebin(nrebin);

    //fprintf(pFile,"%d %d\n",NeventOS,NeventSS);
    int nbinx = histoOS->GetNbinsX();
    //for (int i=0;i<nbinx;i++) {
    //std::cout << " i = " << i 
    //		<< " " << histoOS->GetBinContent(i) 
    //		<< " " << histoOS->GetBinLowEdge(i)
    //		<< std::endl;
    //}
    // we look at histo in 55-200 GeV range in practice
    NeventOS = histoOS->Integral(112,402);  // 55-200 GeV
    if (nrebin==2) NeventOS = histoOS->Integral(56,201);  // 55-200 GeV

    float S[2];
    CalcSideBands(histoOS,histoSS,S,interpretrange,nrebin);
    std::cout << " S = " << S[0] << " " << S[1] << std::endl; 
    //histoOS->Rebin(2);

    // build name of the output file
    NameTitleOutput(ibin,loose,tight,fitrange,sigmodel,period);
    
    // 
    // define observables
    //
    // for Opposite Sign (OS)
    RooRealVar *mee;
    mee = new  RooRealVar("mee","m_{ee}", xmin,xmax,"");
    mee->setRange("interpretrange",defmin,defmax);  // interpretation range
    mee->setRange("fitrange",fitmin,fitmax);        // full range for fit

    //
    // define parameters of functions to fit
    //
    RooRealVar *Gamma;
    if (!isBW) {
      Gamma = new RooRealVar("Gamma", "Gamma", 1., 0.1, 5., "GeV");
   } else {
      Gamma = new RooRealVar("Gamma", "Gamma", 2.5, 0.2, 5., "GeV");
    }

    mmean = 91.;
    float alphainit = 0.8;
    RooRealVar *alpha = new RooRealVar("alpha","alpha", alphainit , 0., 5., "");
    RooRealVar *slope = new RooRealVar("slope", "slope", -0.01, -2., 1.);
    if (isVoigt || isConv || isBW) slope = new RooRealVar("slope", "slope", -0.01, -5., 1.);

    float alphamean = 1.4;
    float alphamin  = 0.1;
    float alphamax  = 5.;

    float nmean = 10.;
    //if (binpt==4 || binpt==5) nmean=10.;
    float nmin  = 1.;
    float nmax  = 100.;

    sigmamean = 1.70;
    sigmamin  = 0.1;
    sigmamax  = 5.;
    RooRealVar *n;
    RooRealVar *alpha;
    RooRealVar *Sigma;
    
    // paramerers of CB are free
    if (isfreeParam==1) {
      n = new RooRealVar("n","n",nmean,nmin,nmax,"");
      alpha = new RooRealVar("alpha","alpha", alphamean , alphamin, alphamax, "");
      Sigma = new RooRealVar("Sigma", "Sigma", sigmamean, sigmamin, sigmamax, "GeV");
    }

    // parameters of tail of CB are fixed (2), all fixed (3)
    if (isfreeParam==2 || isfreeParam==3) {
      n = new RooRealVar("n","n",nmean);
      alpha = new RooRealVar("a","a", alphamean);
      if (isfreeParam==2) Sigma = new RooRealVar("Sigma", "Sigma", sigmamean, sigmamin, sigmamax, "GeV");
      if (isfreeParam==3) Sigma = new RooRealVar("Sigma", "Sigma", sigmamean);
    }

    RooRealVar *mass = new RooRealVar("mass","mass",mmean, 81., 105., "GeV");
    RooRealVar *tail = new RooRealVar("tail","tail",-0.2, -10., 10., "");
    // used for convolution
    RooRealVar *mass2 = new RooRealVar("mass2","mass2",0. , "GeV");
     
    // for Landau
    RooRealVar *meanl = new RooRealVar("meanL","meanL",0.);// , 0., 5., "GeV");
    RooRealVar *sigmal = new RooRealVar("sigL","sigL",3. , 0.01, 10., "GeV");

    // ===================================================
    // define pdf(s) models
    // ===================================================

    // ===========================
    // Signal model
    // ===========================
    
    // Number of signal events : SignalYieldOS
    RooRealVar *SignalYieldOS;
    //int n_ninit = 1000000;
    //int n_nmax  = 10000000;
    int n_ninit = 100000;
    int n_nmax  = 10000000;
    SignalYieldOS = new RooRealVar("SignalYield","Number of signal events", 
				   n_ninit, 1, n_nmax);
    
    // functions to describe the signal
    RooAbsPdf *SignalModel;
    if (isGauss)
      SignalModel = new RooGaussian("SignalModel","Signal model (Gaussian)",
				    *mee, *mass, *Sigma) ;
    if (isBW)
      SignalModel = new RooBreitWigner("SignalModel", "Signal model (Breit-Wigner)", 
				       *mee, *mass, *Gamma);
    if (isVoigt)
      SignalModel = new RooVoigtian("SignalModel", "Signal model (Voigtian)", 
				    *mee, *mass, *Gamma, *Sigma);
    if (isCB)
      SignalModel = new RooCBShape("SignalModel", "Signal model (Crystal Ball)", 
				   *mee, *mass, *Sigma, *alpha, *n);
    if (isNovosibirsk)
      SignalModel = new RooNovosibirsk("SignalModel", "Signal model (Novosibirsk)",
				       *mee, *mass, *Sigma, *tail);
    if (isConv) {
      RooBreitWigner *Model = new RooBreitWigner("Model", "Signal model (BW)", 
						 *mee, *mass, *Gamma);
      RooCBShape *Resol = new RooCBShape("Resol", "Resolution model (CB)", 
					 *mee, *mass2, *Sigma, *alpha, *n);
      SignalModel = new RooFFTConvPdf("SignalModel","Signal model BW (X) CB",
				      *mee, *Model, *Resol);
    }
    
    //==========================
    // background model
    //==========================
    
    // for opposite sign
    RooRealVar *BkgYieldOS = new RooRealVar("BkgYield","Number of background events", 
    					    1000, 1., 100000);
    
    // modelisation of the remaining background
    RooAbsPdf *BkgModel;
    if (isSlope)
      BkgModel = new RooPolynomial("BkgModel", "Background model (Pol1)", 
				   *mee, RooArgList(slope),1);
    if (isExp)
      BkgModel = new RooExponential("BkgModel", "Background model (Exp)", 
				    *mee, *slope);
    // Build Chebychev polynomial p.d.f.  
    RooRealVar *a0, *a1, *a2, *a3, *a4, *a5, *a6, *a7;
    if (isCheb) {
      a0 = new RooRealVar("a0","a0",-0.1,-3.,3.) ;
      a1 = new RooRealVar("a1","a1",0.1,-3.,3.) ;

      a2 = new RooRealVar("a2","a2",-0.1,-3.,3.) ;
      a3 = new RooRealVar("a3","a3",0.1,-1.,1.) ;
      a4 = new RooRealVar("a4","a4",-0.1,-1.,1.) ;
      a5 = new RooRealVar("a5","a5",0.1,-1.,1.) ;
      a6 = new RooRealVar("a6","a6",-0.1,-1.,1.) ;
      a7 = new RooRealVar("a7","a7",0.1,-1.,1.) ;
 
      BkgModel = new RooChebychev("BkgModel","Background model (Chebychev)",
				  *mee,RooArgSet(*a0,*a1,*a2)) ;
    }
    // RooDecay
    if (isRooDecay) {
      dgs_mean = 80.; dgs_mean_min = 50.; dgs_mean_max = 90.;
      if (effbinpt && ibin==1) {
	dgs_mean = 60;
      }
      dgsMean  = new RooRealVar("bkg_gs_mean","",dgs_mean,dgs_mean_min,dgs_mean_max);
      
      dgs_sigma = 10.; dgs_sigma_min = 1.; dgs_sigma_max = 50.;
      //dgs_sigma = 10.; dgs_sigma_min = 5.; dgs_sigma_max = 50.;
      dgsSigma = new RooRealVar("bkg_gs_sigma","",dgs_sigma,dgs_sigma_min,dgs_sigma_max);

      dgsPdf   = new RooGaussModel("gsm_pdf","",*mee,*dgsMean,*dgsSigma);

      //dec_arg = 50.; dec_arg_min = 1.; dec_arg_max = 100.;
      dec_arg = 5.; dec_arg_min = 1.; dec_arg_max = 100.;
      decArg   = new RooRealVar("bkg_decay","",dec_arg,dec_arg_min,dec_arg_max);

      BkgModel = new RooDecay("BkgModel","",*mee,*decArg,*dgsPdf,RooDecay::SingleSided);
      //BkgModel = new RooDecay("BkgModel","",*mee,*decArg,*dgsPdf,RooDecay::DoubleSided);
    }
    if (isLandau) {
      BkgModel = new RooLandau("BkgModel","Background model (Landau)",
			       *mee,*meanl,*sigmal);
    }
    // ====================================
    // total pdf
    // ====================================    
    RooAddPdf *TotalModel;
    if (!isMC) {
      TotalModel = new RooAddPdf("TotalModel", "Signal + Background", 
				 RooArgList(*SignalModel,*BkgModel), 
				 RooArgList(*SignalYieldOS, *BkgYieldOS));
    } else {
      TotalModel = new RooAddPdf("TotalModel", "Signal ", 
				 RooArgList(*SignalModel), 
				 RooArgList(*SignalYieldOS));
    }
 
    // tell roofit that the coefficients of the summed pdf 
    // (i.e. the nsig and nbkg yields) are to be interpreted 
    // as yields in the interpret range
    TotalModel->fixCoefRange("interpretrange");
   
    // ==================================================
    // Fill a RooDataHist from the input histogram
    // ==================================================
    histoOS->SetMarkerStyle(20);
    histoOS->SetMarkerColor(1);
    histoOS->SetFillColor(1);
    RooDataHist *dataOS   = new RooDataHist("dataOS","dataOS",*mee,histoOS);
    histoSS->SetMarkerStyle(21);
    histoSS->SetMarkerColor(2);
    histoSS->SetFillColor(2);
    RooDataHist *dataSS   = new RooDataHist("dataSS","dataSS",*mee,histoSS);
    histoOSSS->SetMarkerStyle(24);
    histoOSSS->SetMarkerColor(12);
    histoOSSS->SetFillColor(12);
    RooDataHist *dataOSSS = new RooDataHist("dataOSSS","dataOSSS",*mee,histoOSSS);
    
    //
    // do the fit
    // use Minos errors, 
    // save the results in a RooFitResult object, 
    // perform an extended fit if you want to take into account in the error 
    // on nsig also statistical Poisson fluctuations    

    
    RooFitResult* fitresult = 0;
    if (dofit) {
      if (doosss) fitresult = TotalModel->fitTo(*dataOSSS,Minos(true),
						Range("fitrange"),
						Save(true),Extended(doextended));
      else fitresult = TotalModel->fitTo(*dataOS,Minos(true),Range("fitrange"),
					 Save(true),Extended(doextended));
    }

   
    // ============================
    // plot the results for OS
    // ============================    
    RooPlot* meeosframe = mee->frame();
    // plot data
    dataOS->plotOn(meeosframe, MarkerStyle(20),MarkerColor(1),LineColor(1), RooFit::Name("dataOS"),DataError(RooAbsData::SumW2));
    if (doosss) 
      dataOSSS->plotOn(meeosframe, MarkerStyle(24),MarkerColor(12),LineColor(12), RooFit::Name("dataOSSS"),DataError(RooAbsData::SumW2));
    
    
    // ==============================================
    bool onLimit = false;
    /*if (isRooDecay) {
    //std::cout << " N = " << n->getVal() << std::endl;
    // dgsMean 
    if (dgsMean->getVal()<=dgs_mean_min || dgsMean->getVal()>=dgs_mean_max) onLimit = true;
    // dgsSigma 
    if (dgsSigma->getVal()<=dgs_sigma_min || dgsSigma->getVal()>=dgs_sigma_max) onLimit = true;
    // decArg
    if (decArg->getVal()<=dec_arg_min || decArg->getVal()>=dec_arg_max) onLimit = true;
    // n
    if (fabs(n->getVal()-nmin)>=0.001 || fabs(n->getVal()-nmax)>=0.001) onLimit = true;
    std::cout << " N = " << n->getVal() << " " << nmin << " " << nmax << " " << fabs(n->getVal()-nmax) << " " << onLimit << std::endl;
    }*/
    
    // ==============================================
    
    // plot model
    if (dofit) {
      //TotalModel->plotOn(meeosframe,RooFit::Name("model"),LineColor(kRed));
      //TotalModel->plotOn(meeosframe,RooFit::Name("model"),RooFit::DrawOption("A*"));
      
      //
      // plot background component of model
      if (!isMC) {
	TotalModel->plotOn(meeosframe, Components(*BkgModel), 
			   LineColor(kGreen),
			   LineStyle(kDashed));
      }
      // plot signal component of model
      TotalModel->plotOn(meeosframe, Components(*SignalModel), 
			 LineColor(kRed),
			 LineStyle(kDashed));
      // plot signal+background component of model
      TotalModel->plotOn(meeosframe, RooFit::Name("TotalModel"), 
			 LineColor(kBlue));
      //
      //TotalModel->plotOn(meeosframe, Components(RooArgList(*SignalModel,*BkgModel)), 
	//	 LineColor(kBlue));
      //
      TotalModel->paramOn(meeosframe,Layout(0.7,0.95,0.95),
			  Format("NELU",AutoPrecision(1)));//chiffres significatifs=erreur+1
      
      meeosframe->getAttText()->SetTextSize(14);
      meeosframe->getAttText()->SetTextFont(34);
      //taille de la boite
      ((TBox*)meeosframe->findObject("TotalModel_paramBox"))->SetX1(0.7);
      ((TBox*)meeosframe->findObject("TotalModel_paramBox"))->SetX2(0.95);
      ((TBox*)meeosframe->findObject("TotalModel_paramBox"))->SetY1(0.6);
      ((TBox*)meeosframe->findObject("TotalModel_paramBox"))->SetY2(0.95); 
    }

    // add SS histo
    dataSS->plotOn(meeosframe, MarkerStyle(21),MarkerColor(33),LineColor(33), RooFit::Name("dataSS"),DataError(RooAbsData::SumW2));
    
   // save canvas 
    TCanvas* cos = new TCanvas(m_titleOutOS,m_titleOutOS,200,10,600,600);
    cos->SetLogy();
    meeosframe->SetYTitle("Events/GeV");
    meeosframe->SetXTitle("m_{ee} [GeV]");
    meeosframe->SetMinimum(1.);
    meeosframe->SetMaximum(3.*histoOS->GetMaximum());

    meeosframe->Draw();
    
    float myy[2], myx[2];
    myx[0] = 61.;
    myx[1] = 61.;
    myy[0] = 1.;
    myy[1] = 1000000.;//histoOS->GetBinContent(61);
    TGraph *plot0 = new TGraph(2,myx,myy);
    plot0->SetLineColor(2);
    plot0->SetLineWidth(2);
    plot0->Draw("same");

    myx[0] = 81.;
    myx[1] = 81.;
    myy[0] = 1.;
    myy[1] = 1000000.;//histoOS->GetBinContent(81);
    TGraph *plot1 = new TGraph(2,myx,myy);
    plot1->SetLineColor(2);
    plot1->SetLineWidth(2);
    plot1->Draw("same");

    myx[0] = 101.;
    myx[1] = 101.;
    myy[0] = 1.;
    myy[1] = 1000000.;//histoOS->GetBinContent(101);
    TGraph *plot2 = new TGraph(2,myx,myy);
    plot2->SetLineColor(2);
    plot2->SetLineWidth(2);
    plot2->Draw("same");
    
    myx[0] = 121.;
    myx[1] = 121.;
    myy[0] = 1.;
    myy[1] = 1000000.;//histoOS->GetBinContent(121);
    TGraph *plot3 = new TGraph(2,myx,myy);
    plot3->SetLineColor(2);
    plot3->SetLineWidth(2);
    plot3->Draw("same");

    //myText(0.23,0.25,2,"B");
    //myText(0.35,0.25,2,"A");
    //myText(0.46,0.25,2,"C");
    float ytext = 0.2;
    ytext = 0.8;
    myText(0.19,ytext,2,"sideband",0.03);
    myText(0.32,ytext,2,"signal",0.03);
    myText(0.41,ytext,2,"sideband",0.03);

    TArrow *arr1 = new TArrow(61.,300.,81.,300.,0.03,"<|>");
    arr1->SetLineColor(2);
    arr1->SetFillColor(2);
    arr1->SetLineWidth(2);
    arr1->Draw();
    TArrow *arr2 = new TArrow(81.,300.,101.,300.,0.03,"<|>");
    arr2->SetLineColor(2);
    arr2->SetFillColor(2);
    arr2->SetLineWidth(2);
    arr2->Draw();
    TArrow *arr3 = new TArrow(101.,300.,121.,300.,0.03,"<|>");
    arr3->SetLineColor(2);
    arr3->SetFillColor(2);
    arr3->SetLineWidth(2);
    arr3->Draw();

    //Reducedchi2 = meeosframe->chiSquare("TotalModel","dataOS",
    //				fitresult->floatParsFinal().getSize());

    //myatlasStyle->SetTextFont(0.01);
    ATLASLabel(0.55,0.89,"Internal");
    myText(      0.55,0.81,1,"#sqrt{s}= 13 TeV, 3.34 fb^{-1}",0.045);
    //myText(      0.55,0.73,1,"3.34 fb^{-1}",0.045);
    //leg = new TLegend(0.42,0.65,0.72,0.8);
    leg = new TLegend(0.5,0.7,0.7,0.8);

    leg->SetFillColor(0);
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->AddEntry(histoOS,"Data (OS)","ep");
    leg->AddEntry(histoSS,"Data (SS)","ep");
    if (doosss) leg->AddEntry(histoOSSS,"Data (OS-SS)","ep");

    if (dofit) {
      TF1 *f1=new TF1("f1","f1",-10,10);
      f1->SetLineColor(kBlue);
      leg->AddEntry(f1,"Fit","l");
      
      TF1 *f2=new TF1("f2","f2",-10,10);
      f2->SetLineColor(kRed);
      f2->SetLineStyle(kDashed);
      if (isCB) leg->AddEntry(f2,"Signal (CB)","l");
      if (isConv) leg->AddEntry(f2,"Signal (CB*BW)","l");
      if (isVoigt) leg->AddEntry(f2,"Signal (G*BW)","l");
      if (isBW) leg->AddEntry(f2,"Signal (BW)","l");
      
      TF1 *f3=new TF1("f3","f3",-10,10);
      f3->SetLineColor(kGreen);
      f3->SetLineStyle(kDashed);
      if (isExp) leg->AddEntry(f3,"Background (Exp)","l");
      if (isCheb) leg->AddEntry(f3,"Background (Cheb)","l");
      if (isLandau) leg->AddEntry(f3,"Background (L)","l");
      if (isRooDecay) leg->AddEntry(f3,"Background (Exp*G)","l");
    }
    //leg->Draw();
     
   //ATLAS_LABEL(0.2,0.2); myText( 0.37,0.2,1,"Preliminary");
    
    // new method for ATLAS labels. Use this!
    //ATLASLabel(0.2,0.2);
    //ATLASLabel(0.2,0.9,"Preliminary");
    //if (!successes) ATLASLabel(0.2,0.45,"Preliminary");
    //ATLASLabel(0.2,0.2,"Work in progress");
    //m_titleOutOS+="-withatlaslabel";
    cos->SaveAs(m_titleOutOS+".eps");   
    cos->SaveAs(m_titleOutOS+".pdf");   
    cos->SaveAs(m_titleOutOS+".png");   
    
    delete histoOS; // important to delete this one as it has same histoname as histoOSSS
    delete histoSS;
    //std::cout << " histoOSSS = " << histoOSSS << std::endl;
    //delete histoOSSS;

    //
    //Reducedchi2 = meeosframe->chiSquare("model","dataOS",
    //				fitresult->floatParsFinal().getSize());
    //Reducedchi2 = meeosframe->chiSquare("model","dataOS",3);
    
    //cout << " nparam = " << fitresult->floatParsFinal().getSize() << std::endl;
    cout<<"chi2/ndoff: "<< Reducedchi2 <<endl; 
    
    //fitresult->Print();
    
    // results from the fit
    if (!onLimit) {
      N[0][0]    += SignalYieldOS->getVal();
      N[1][0]    += BkgYieldOS->getVal();
      //std::cout << " myNeventSS = " << N[2][0] << std::endl;
      ErrN[0][0] += SignalYieldOS->getError();
      ErrN[1][0] += BkgYieldOS->getError();
      std::cout << " nsig = " << N[0][0] << " " << N[1][0] 
      	      << " " << ErrN[0][0] << " " << ErrN[1][0]
      //<< " " << nsig.sum(kTRUE)
		<< std::endl;
    }
    
    // result from OS-SS
    N[0][1] = NeventOS;
    N[1][1] = NeventSS;
    ErrN[0][1] = sqrt(1.*NeventOS);
    ErrN[1][1] = sqrt(1.*NeventSS);

    // result from side-bands
    N[0][2] = S[0];
    N[1][2] = S[1];
    ErrN[0][2] = S[0];
    ErrN[1][2] = S[1];

    // delete
    delete mee;
    delete Gamma;
    delete Sigma;
    delete mass;
    delete alpha;
    delete slope;
    delete n;
    delete tail;
    delete mass2;
    delete SignalYieldOS;
    delete BkgYieldOS;
    delete SignalModel;
    delete BkgModel;
    delete TotalModel;
    delete dataOS;
    delete dataSS;
    delete dataOSSS;

    delete Gamma;
    delete Sigma;
    delete mass;
    delete alpha;
    delete n;
    delete tail;
    delete mass2;

    if (isExp)
      delete slope;

    delete a0;
    delete a1;
    delete a2;
    delete a3;
    delete a4;
    delete a5;
    delete a6;
    delete a7;
  
    if (isLandau) {
      delete meanl;
      delete sigmal;
    }
  }

  // =========================================================
  void NameInputHisto(int ibin,bool loose,bool tight,
		      TString level1, TString level2)
  {
    //
    // construct name of the output file
    //
    
    m_nameHistoOS = "EffiRealElecTP_Mee";
    if (loose) m_nameHistoOS+=level1;
    if (tight) m_nameHistoOS+=level2; 
    TString suffix = "";
    
    // vs Pt
    if (effbinpt) {
      suffix = "_vsEt"; 
      if (ibin==1)  m_nameHistoOS += "_Et_25to30GeV";
      if (ibin==2)  m_nameHistoOS += "_Et_30to35GeV";
      if (ibin==3)  m_nameHistoOS += "_Et_35to40GeV";
      if (ibin==4)  m_nameHistoOS += "_Et_40to45GeV";
      if (ibin==5)  m_nameHistoOS += "_Et_45to50GeV";
      if (ibin==6)  m_nameHistoOS += "_Et_50to55GeV";
      if (ibin==7)  m_nameHistoOS += "_Et_55to60GeV";
      if (ibin==8)  m_nameHistoOS += "_Et_60to80GeV";
      if (ibin==9)  m_nameHistoOS += "_Et_80to120GeV";
      if (ibin==10) m_nameHistoOS += "_Et_gt120GeV";
    }

    // vs Eta
    if (effbineta) {
      suffix = "_vsEta"; 
      if (ibin==1)  m_nameHistoOS += "_Eta_0to01";
      if (ibin==2)  m_nameHistoOS += "_Eta_01to06";
      if (ibin==3)  m_nameHistoOS += "_Eta_06to08";
      if (ibin==4)  m_nameHistoOS += "_Eta_08to115";
      if (ibin==5)  m_nameHistoOS += "_Eta_115to137";
      if (ibin==6)  m_nameHistoOS += "_Eta_137to152";
      if (ibin==7)  m_nameHistoOS += "_Eta_152to181";
      if (ibin==8)  m_nameHistoOS += "_Eta_181to201";
      if (ibin==9)  m_nameHistoOS += "_Eta_201to237";
      if (ibin==10) m_nameHistoOS += "_Eta_237to247";
    }

    // vs dR
    if (effbindr) {
      suffix = "_vsdRClosestJet"; 
      if (ibin==1) m_nameHistoOS += "_dRClosestJet_04to06";
      if (ibin==2) m_nameHistoOS += "_dRClosestJet_06to08";
      if (ibin==3) m_nameHistoOS += "_dRClosestJet_08to10";
      if (ibin==4) m_nameHistoOS += "_dRClosestJet_10to15";
      if (ibin==5) m_nameHistoOS += "_dRClosestJet_15to20";
      if (ibin==6) m_nameHistoOS += "_dRClosestJet_gt20";
    }

    // vs Pt leadingjet
    if (effbinptleadjet) {
      suffix = "_vsPtLeadingJet"; 
      if (ibin==1) m_nameHistoOS += "_PtLeadingJet_25to50GeV";
      if (ibin==2) m_nameHistoOS += "_PtLeadingJet_50to75GeV";
      if (ibin==3) m_nameHistoOS += "_PtLeadingJet_75to100GeV";
      if (ibin==4) m_nameHistoOS += "_PtLeadingJet_100to150GeV";
      if (ibin==5) m_nameHistoOS += "_PtLeadingJet_gt150GeV";
    }
    
    // vs dPhi
    if (effbindphi) {
      suffix = "_vsDPhi";
      if (ibin==1)  m_nameHistoOS += "_DPhi_0to010";
      if (ibin==2)  m_nameHistoOS += "_DPhi_010to020";
      if (ibin==3)  m_nameHistoOS += "_DPhi_020to030";
      if (ibin==4)  m_nameHistoOS += "_DPhi_030to040";
      if (ibin==5)  m_nameHistoOS += "_DPhi_040to050";
      if (ibin==6)  m_nameHistoOS += "_DPhi_050to075";
      if (ibin==7)  m_nameHistoOS += "_DPhi_075to100";
      if (ibin==8)  m_nameHistoOS += "_DPhi_100to125";
      if (ibin==9)  m_nameHistoOS += "_DPhi_125to150";
      if (ibin==10) m_nameHistoOS += "_DPhi_150to175";
      if (ibin==11) m_nameHistoOS += "_DPhi_175to200";
      if (ibin==12) m_nameHistoOS += "_DPhi_200to250";
      if (ibin==13) m_nameHistoOS += "_DPhi_250topi";
    }

    // vs MET
    if (effbinmet) {
      suffix = "_vsMET";
      if (ibin==1) m_nameHistoOS += "_MET_0to10";
      if (ibin==2) m_nameHistoOS += "_MET_10to20";
      if (ibin==3) m_nameHistoOS += "_MET_20to30";
      if (ibin==4) m_nameHistoOS += "_MET_30to40";
      if (ibin==5) m_nameHistoOS += "_MET_40to60";
      if (ibin==6) m_nameHistoOS += "_MET_60to100";
      if (ibin==7) m_nameHistoOS += "_MET_100to150";
      if (ibin==8) m_nameHistoOS += "_MET_150to200";
      if (ibin==9) m_nameHistoOS += "_MET_gt200";
    }

    // vs MTW
    if (effbinmtw) {
      suffix = "_vsMTW";
      if (ibin==1) m_nameHistoOS += "_MTW_0to10";
      if (ibin==2) m_nameHistoOS += "_MTW_10to20";
      if (ibin==3) m_nameHistoOS += "_MTW_20to30";
      if (ibin==4) m_nameHistoOS += "_MTW_30to40";
      if (ibin==5) m_nameHistoOS += "_MTW_40to60";
      if (ibin==6) m_nameHistoOS += "_MTW_60to100";
      if (ibin==7) m_nameHistoOS += "_MTW_100to150";
      if (ibin==8) m_nameHistoOS += "_MTW_150to200";
      if (ibin==9) m_nameHistoOS += "_MTW_gt200";
    }

    // vs NJet
    if (effbinnjet) {
      suffix = "_vsNJet"; 
      if (ibin==1) m_nameHistoOS += "_0Jet";
      if (ibin==2) m_nameHistoOS += "_1Jet";
      if (ibin==3) m_nameHistoOS += "_2Jet";
      if (ibin==4) m_nameHistoOS += "_3Jet";
      if (ibin==5) m_nameHistoOS += "_ge4Jet";
    }

    // vs NbJet
    if (effbinnbjet) {
      suffix = "_vsNbJet"; 
      if (ibin==1) m_nameHistoOS += "_0bJet";
      if (ibin==2) m_nameHistoOS += "_1bJet";
      if (ibin==3) m_nameHistoOS += "_ge2bJet";
    }

    m_nameHistoSS   = m_nameHistoOS;
    m_nameHistoOSSS = m_nameHistoOS;

    m_nameHistoOS+=suffix;
    m_nameHistoSS+=suffix;
    m_nameHistoOSSS+=suffix;    

    m_nameHistoOS+="_OS";
    m_nameHistoSS+="_SS";
    m_nameHistoOSSS+="_OSSS";

    std::cout << " histo : " << m_nameHistoOS << " " << loose << " " << tight << std::endl;
  }
  
  // =========================================================
  void NameTitleOutput(int ibin,bool loose,bool tight,
		       int fitrange,int sigmodel, int period)
  {
    //
    // construct name of the output file name
    //

    m_titleOutOS = "Mee-Zee";

    if (period==0) m_titleOutOS += "DtoJ";

    if (loose)  m_titleOutOS+="-Loose";
    if (tight)  m_titleOutOS+="-Tight";
    
    if (isConv)        m_titleOutOS += "-Conv";
    if (isGauss)       m_titleOutOS += "-Gauss";
    if (isBW)          m_titleOutOS += "-BW";
    if (isVoigt)       m_titleOutOS += "-Voigt";
    if (isCB)          m_titleOutOS += "-CB";
    if (isNovosibirsk) m_titleOutOS += "-Novo";
    
    if (isRooDecay) m_titleOutOS += "ExpG";
    if (isExp)      m_titleOutOS += "Exp";
    if (isCheb)     m_titleOutOS += "Cheb";
    if (isLandau)   m_titleOutOS += "Landau";

    if (fitrange==1) m_titleOutOS += "-Fit55to200";
    if (fitrange==2) m_titleOutOS += "-Fit60to150";

    if (sigmodel==2 || sigmodel==5) m_titleOutOS += "-anfixed";
    if (sigmodel==3 || sigmodel==6) m_titleOutOS += "-ansfixed";
    m_titleOutOS += "-Yield81to101";

    int iloose = 0;
    //if (tight) iloose = 0;
    if (iloose==0)  m_titleOutOS += "";
 
    // vs Et
    if (effbinpt) {
      suffix = "_vsEt"; 
      if (ibin==1)  m_titleOutOS += "_Et_25to30GeV";
      if (ibin==2)  m_titleOutOS += "_Et_30to35GeV";
      if (ibin==3)  m_titleOutOS += "_Et_35to40GeV";
      if (ibin==4)  m_titleOutOS += "_Et_40to45GeV";
      if (ibin==5)  m_titleOutOS += "_Et_45to50GeV";
      if (ibin==6)  m_titleOutOS += "_Et_50to55GeV";
      if (ibin==7)  m_titleOutOS += "_Et_55to60GeV";
      if (ibin==8)  m_titleOutOS += "_Et_60to80GeV";
      if (ibin==9)  m_titleOutOS += "_Et_80to120GeV";
      if (ibin==10) m_titleOutOS += "_Et_gt120GeV";
    }

    // vs Eta
    if (effbineta) {
      suffix = "_vsEta"; 
      if (ibin==1)  m_titleOutOS += "_Eta_0to01";
      if (ibin==2)  m_titleOutOS += "_Eta_01to06";
      if (ibin==3)  m_titleOutOS += "_Eta_06to08";
      if (ibin==4)  m_titleOutOS += "_Eta_08to115";
      if (ibin==5)  m_titleOutOS += "_Eta_115to137";
      if (ibin==6)  m_titleOutOS += "_Eta_137to152";
      if (ibin==7)  m_titleOutOS += "_Eta_152to181";
      if (ibin==8)  m_titleOutOS += "_Eta_181to201";
      if (ibin==9)  m_titleOutOS += "_Eta_201to237";
      if (ibin==10) m_titleOutOS += "_Eta_237to247";
    }

    // vs dR
    if (effbindr) {
      suffix = "_vsdRClosestJet"; 
      if (ibin==1) m_titleOutOS += "_dRClosestJet_04to06";
      if (ibin==2) m_titleOutOS += "_dRClosestJet_06to08";
      if (ibin==3) m_titleOutOS += "_dRClosestJet_08to10";
      if (ibin==4) m_titleOutOS += "_dRClosestJet_10to15";
      if (ibin==5) m_titleOutOS += "_dRClosestJet_15to20";
      if (ibin==6) m_titleOutOS += "_dRClosestJet_gt20";
    }

    // vs Pt leadingjet
    if (effbinptleadjet) {
      suffix = "_vsPtLeadingJet"; 
      if (ibin==1) m_titleOutOS += "_PtLeadingJet_25to50GeV";
      if (ibin==2) m_titleOutOS += "_PtLeadingJet_50to75GeV";
      if (ibin==3) m_titleOutOS += "_PtLeadingJet_75to100GeV";
      if (ibin==4) m_titleOutOS += "_PtLeadingJet_100to150GeV";
      if (ibin==5) m_titleOutOS += "_PtLeadingJet_gt150GeV";
    }
    
    // vs dPhi
    if (effbindphi) {
      suffix = "_vsDPhi";
      if (ibin==1)  m_titleOutOS += "_DPhi_0to010";
      if (ibin==2)  m_titleOutOS += "_DPhi_010to020";
      if (ibin==3)  m_titleOutOS += "_DPhi_020to030";
      if (ibin==4)  m_titleOutOS += "_DPhi_030to040";
      if (ibin==5)  m_titleOutOS += "_DPhi_040to050";
      if (ibin==6)  m_titleOutOS += "_DPhi_050to075";
      if (ibin==7)  m_titleOutOS += "_DPhi_075to100";
      if (ibin==8)  m_titleOutOS += "_DPhi_100to125";
      if (ibin==9)  m_titleOutOS += "_DPhi_125to150";
      if (ibin==10) m_titleOutOS += "_DPhi_150to175";
      if (ibin==11) m_titleOutOS += "_DPhi_175to200";
      if (ibin==12) m_titleOutOS += "_DPhi_200to250";
      if (ibin==13) m_titleOutOS += "_DPhi_250topi";
    }
   
   // vs MET
    if (effbinmet) {
      suffix = "_vsMET";
      if (ibin==1) m_titleOutOS += "_MET_0to10";
      if (ibin==2) m_titleOutOS += "_MET_10to20";
      if (ibin==3) m_titleOutOS += "_MET_20to30";
      if (ibin==4) m_titleOutOS += "_MET_30to40";
      if (ibin==5) m_titleOutOS += "_MET_40to60";
      if (ibin==6) m_titleOutOS += "_MET_60to100";
      if (ibin==7) m_titleOutOS += "_MET_100to150";
      if (ibin==8) m_titleOutOS += "_MET_150to200";
      if (ibin==9) m_titleOutOS += "_MET_gt200";
    }

    // vs MTW
    if (effbinmtw) {
      suffix = "_vsMTW";
      if (ibin==1) m_titleOutOS += "_MTW_0to10";
      if (ibin==2) m_titleOutOS += "_MTW_10to20";
      if (ibin==3) m_titleOutOS += "_MTW_20to30";
      if (ibin==4) m_titleOutOS += "_MTW_30to40";
      if (ibin==5) m_titleOutOS += "_MTW_40to60";
      if (ibin==6) m_titleOutOS += "_MTW_60to100";
      if (ibin==7) m_titleOutOS += "_MTW_100to150";
      if (ibin==8) m_titleOutOS += "_MTW_150to200";
      if (ibin==9) m_titleOutOS += "_MTW_gt200";
    }

    // vs NJet
    if (effbinnjet) {
      suffix = "_vsNJet";
      if (ibin==1) m_titleOutOS += "_0Jet";
      if (ibin==2) m_titleOutOS += "_1Jet";
      if (ibin==3) m_titleOutOS += "_2Jet";
      if (ibin==4) m_titleOutOS += "_3Jet";
      if (ibin==5) m_titleOutOS += "_ge4Jet";
    }

    // vs NbJet
    if (effbinnbjet) {
      suffix = "_vsNbJet";
      if (ibin==1) m_titleOutOS += "_0bJet";
      if (ibin==2) m_titleOutOS += "_1bJet";
      if (ibin==3) m_titleOutOS += "_ge2bJet";
    }

    m_titleOutOS+="-OS";
  }

// ==================================================
void CalcSideBands(TH1F * histoOS, TH1F * histoSS, float S[2], 
		   int interpretrange, int nrebin)
{
  //
  // method to estimate background from side bands
  //

  int nbin = histoOS->GetNbinsX();
  //std::cout << " nbin " << nbin << std::endl;
  int imin = 0;
  int imax = 0;

  /*for (int i=1;i<=500;i++) {
    std::cout << " i = " << i << " " << histoOS->GetBinContent(i) 
	      << " " << histoOS->GetBinLowEdge(i)
	      << std::endl;
	      }*/

  float A = 0.;
  if (interpretrange==1) { // 61-81
    imin = 123;
    imax = 163;
  }
  if (interpretrange==2) { // 66-76
    imin = 133;
    imax = 163;
  }
  if (interpretrange==3) { // 61-81
    imin = 123;
    imax = 163;
    }

  // in case of rebinning
  imin /= nrebin;
  imax /= nrebin;
  for (int i=imin;i<imax;i++) {
    A +=  histoSS->GetBinContent(i);
  }
  
  float B = 0.; 
  if (interpretrange==1) { // 81-101
    imin = 163;
    imax = 203;
  }
  if (interpretrange==2) { // 76-106
    imin = 153;
    imax = 213;
  }
  if (interpretrange==3) { // 86-96
    imin = 173;
    imax = 193;
  }
  // in case of rebinning
  imin /= nrebin;
  imax /= nrebin;
  for (int i=imin;i<imax;i++) {
    B +=  histoOS->GetBinContent(i);
  }

  float C = 0.;
  if (interpretrange==1) { // 101-121
    imin = 203;
    imax = 243;
  }
  if (interpretrange==2) { // 106-116
    imin = 213;
    imax = 233;
  }
  if (interpretrange==3) { // 101-121
    imin = 203;
    imax = 243;
    }

  // in case of rebinning
  imin /= nrebin;
  imax /= nrebin;
  for (int i=imin;i<imax;i++) {
    C +=  histoSS->GetBinContent(i);
  }

  if (interpretrange==1 || interpretrange==2) {
    S[0] = B-(A+C)/2.;
    S[1] = sqrt(B+0.25*(A+C));
  }
  if (interpretrange==3) {
    S[0] = B-(A+C)/4.;
    S[1] = sqrt(B+(A+C)/16.);
  }
  /*std::cout << " A = " << A << " B = " << B << " C = " << C 
  	    << " (A+C)/2 = " << (A+C)/2.
  	    << " S = " << S[0]
  	    << std::endl;*/
  return;
}

// =====================================================
void CalcAllEffs(float Nloose[2][3],float ErrNloose[2][3],
		 float Ntight[2][3],float ErrNtight[2][3], 
		 double Reducedchi2loose, double Reducedchi2tight)
{
  float Nftight, ErrNftight;
  Nftight    = Nloose[0][0]-Ntight[0][0];
  ErrNftight = sqrt(ErrNloose[0][0]*ErrNloose[0][0]-ErrNtight[0][0]*ErrNtight[0][0]);  
  float efftight = Ntight[0][0]/Nloose[0][0];
  float part1tight = (1.-efftight)*ErrNtight[0][0];
  float part2tight = efftight*ErrNftight;
  float Errefftight = sqrt(part1tight*part1tight+part2tight*part2tight)/Nloose[0][0];
  
  std::cout << " efftight = " << efftight << " +/- " << Errefftight << std::endl;
  std::cout << " Loose: "
	    << " Nsig   = " << Nloose[0][0] << " +/- " << ErrNloose[0][0] 
	    << " Nbkg   = " << Nloose[1][0] << " +/- " << ErrNloose[1][0]
	    << std::endl;
  std::cout << " Tight: "
	    << " Nsig   = " << Ntight[0][0] << " +/- " << ErrNtight[0][0]
	    << " Nbkg   = " << Ntight[1][0] << " +/- " << ErrNtight[1][0]
	    << std::endl;
  std::cout << " chi2/ndf(Loose) = " << Reducedchi2loose << std::endl;
  std::cout << " chi2/ndf(Tight) = " << Reducedchi2tight << std::endl;
}

// =====================================================
void CalcAllEffsPerBin(bool dofit,
		       float Nlooseperbin[2][3][20], 
		       float ErrNlooseperbin[2][3][20],
		       float Ntightperbin[2][3][20], 
		       float ErrNtightperbin[2][3][20],
		       double Reducedchi2looseperbin[20], 
		       double Reducedchi2tightperbin[20], 
		       int fitrange,int interpretrange,
		       int sigmodel,int bkgmodel,
		       FILE *pFile[3])
{
  float effbinloose[20];
  float Erreffbinloose[20];
  float effbintight[20];
  float Erreffbintight[20];

  // which signal model
  bool isGauss       = false;
  bool isBW          = false;
  bool isVoigt       = false;
  bool isCB          = false;
  bool isNovosibirsk = false;
  bool isConv        = false;
  // which background model
  bool isRooDecay = false;
  bool isExp      = false;
  bool isCheb     = false;
  bool isLandau   = false;

  // which signal model
  if (sigmodel==1 || sigmodel==2 || sigmodel==3) isConv        = true;
  if (sigmodel==4 || sigmodel==5 || sigmodel==6) isCB          = true;
  if (sigmodel==7) isVoigt       = true;
  if (sigmodel==8) isBW          = true;

  // check if parameters of CB have to be free or not    
  int isfreeParam = 1;
  if (sigmodel==2 || sigmodel==5) isfreeParam = 2;
  if (sigmodel==3 || sigmodel==6) isfreeParam = 3;

  // which background model
  if (bkgmodel==1) isRooDecay = true;
  if (bkgmodel==2) isExp      = true;
  if (bkgmodel==3) isLandau   = true;
  if (bkgmodel==4) isCheb     = true;
  
  // loop on bins
  for (int ibin=m_imin;ibin<=m_imax;ibin++) {
    PrepareASCII(ibin);
    std::cout << " bin=" << ibin << " " << m_nameBin << std::endl;

    if (dofit) {
      float Nftight, ErrNftight;
      float efftight; 
      float part1tight; 
      float part2tight; 
      float Errefftight;
      
      float nloose    = Nlooseperbin[0][0][ibin];
      float errnloose = ErrNlooseperbin[0][0][ibin];
      float ntight    = Ntightperbin[0][0][ibin];
      float errntight = ErrNtightperbin[0][0][ibin];
      Nftight    = nloose-ntight;
      ErrNftight = sqrt(errnloose*errnloose-errntight*errntight);
      efftight = ntight/nloose;
      part1tight = (1.-efftight)*errntight;
      part2tight = efftight*ErrNftight;
      Errefftight = sqrt(part1tight*part1tight+part2tight*part2tight)/nloose;
      std::cout << " ==== Results by a fit ===== " << std::endl;
      efftight*=100.;
      Errefftight*=100.;
      std::cout << " efftight = " << efftight 
		<< " +/- " << Errefftight << std::endl;
      std::cout << " Loose: "
		<< " Nsig   = " << Nlooseperbin[0][0][ibin]
      << " +/- " << ErrNlooseperbin[0][0][ibin]
      << " Nbkg   = " << Nlooseperbin[1][0][ibin]
      << " +/- " << ErrNlooseperbin[1][0][ibin]
      << std::endl;
      std::cout << " Tight: "
		<< " Nsig   = " << Ntightperbin[0][0][ibin]
      << " +/- " << ErrNtightperbin[0][0][ibin]
		<< " Nbkg   = " << Ntightperbin[1][0][ibin]
		<< " +/- " << ErrNtightperbin[1][0][ibin]
		<< std::endl;
      std::cout << " chi2/ndf(Loose) = " << Reducedchi2looseperbin[ibin] << std::endl;
      std::cout << " chi2/ndf(Tight) = " << Reducedchi2tightperbin[ibin] << std::endl;
      
      if (TMath::IsNaN(Errefftight)) Errefftight = -999.;
      
      fprintf(pFile[0],"%6.2f %6.2f %6.2f %4.2f \n",
	      m_Bin,m_errBin,efftight,Errefftight);
    }
	
    // ====================================================
    std::cout << " ==== Results from sidebands ===== " << std::endl;
    efftight*=100.;
    Errefftight*=100.;
    if (Nlooseperbin[0][2][ibin]>0.) {
      efftight = Ntightperbin[0][2][ibin]/Nlooseperbin[0][2][ibin]; 
      Errefftight = sqrt(efftight*(1.-efftight)/Nlooseperbin[0][2][ibin]);
    } 	 
    if (effbineta && ibin==6) {
      efftight = 0.;
      Errefftight = 0.;
    }
    // protection against stupid results (linked to trigger pt threshold)
    if (effbinpt && efftight>1.) {
      efftight = 0.;
      Errefftight = 0.;
    }
    efftight*=100.;
    Errefftight*=100.;
    std::cout << " efftight = " << efftight 
	      << " +/- " << Errefftight << std::endl;
    std::cout << " Loose: "
	      << " Nsig   = " << Nlooseperbin[0][2][ibin] 
	      << " +/- " << ErrNlooseperbin[0][2][ibin]
	      << " Nbkg   = " << Nlooseperbin[1][2][ibin]
	      << " +/- " << ErrNlooseperbin[1][2][ibin]
	      << std::endl;
    std::cout << " Tight: "
	      << " Nsig   = " << Ntightperbin[0][2][ibin]
	      << " +/- " << ErrNtightperbin[0][2][ibin]
	      << " Nbkg   = " << Ntightperbin[1][2][ibin]
		  << " +/- " << ErrNtightperbin[1][2][ibin]
	      << std::endl;
    
    fprintf(pFile[1],"%6.2f %6.2f %6.2f %4.2f \n",
	    m_Bin,m_errBin,efftight,Errefftight);
    
    // ======================================================
    std::cout << " ==== Results from OS-SS ===== " << std::endl;
    efftight = 0.;
    Errefftight = 0.;
    if (Nlooseperbin[0][1][ibin]-Nlooseperbin[1][1][ibin]>0.) {
      efftight = (Ntightperbin[0][1][ibin]-Ntightperbin[1][1][ibin])/(Nlooseperbin[0][1][ibin]-Nlooseperbin[1][1][ibin]); 
      Errefftight = sqrt(efftight*(1.-efftight)/(Nlooseperbin[0][1][ibin]-Nlooseperbin[1][1][ibin]));
    }
    // protection against stupid results (linked to trigger pt threshold)
    if (effbinpt && efftight>1.) {
      efftight = 0.;
      Errefftight = 0.;
    }
    efftight*=100.;
    Errefftight*=100.;
    std::cout << " efftight = " << efftight 
	      << " +/- " << Errefftight << std::endl;
    std::cout << " Loose: "
	      << " Nsig   = " << Nlooseperbin[0][1][ibin]
	      << " +/- " << ErrNlooseperbin[0][1][ibin]
	      << " Nbkg   = " << Nlooseperbin[1][1][ibin]
	      << " +/- " << ErrNlooseperbin[1][1][ibin]
	      << std::endl;
    std::cout << " Tight: "
	      << " Nsig   = " << Ntightperbin[0][1][ibin]
	      << " +/- " << ErrNtightperbin[0][1][ibin]
	      << " Nbkg   = " << Ntightperbin[1][1][ibin]
	      << " +/- " << ErrNtightperbin[1][1][ibin]
	      << std::endl;
    
    fprintf(pFile[2],"%6.2f %6.2f %6.2f %4.2f \n",
	    m_Bin,m_errBin,efftight,Errefftight);
  }  
}

  // ==========================================
  void PrepareASCII(int ibin)
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
      }
    }

    // ======================================
    // vs Eta
    if (effbineta) {
      if (ibin==1) {
	m_nameBin = "0,0.1";
	m_Bin = 0.05;
	m_errBin = 0.05;
      }
      if (ibin==2) {
	m_nameBin = "0.1,0.6";
	m_Bin = 0.35;
	m_errBin = 0.25;
      }
      if (ibin==3) {
	m_nameBin = "0.6,0.8";
	m_Bin = 0.7;
	m_errBin = 0.1;
		}
      if (ibin==4) {
	m_nameBin = "0.8,1.15";
	m_Bin = 0.975;
	m_errBin = 0.175;
      }
      if (ibin==5) {
	m_nameBin = "1.15,1.37";
	m_Bin = 1.26;
	m_errBin = 0.11;
      }
      if (ibin==6) {
	m_nameBin = "1.37,1.52";
	m_Bin = 1.445;
	m_errBin = 0.075;
      }
      if (ibin==7) {
	m_nameBin = "1.52,1.81";
	m_Bin = 1.665;
	m_errBin = 0.145;
      }
      if (ibin==8) {
	m_nameBin = "1.81,2.01";
	m_Bin = 1.91;
	m_errBin = 0.1;
      }
      if (ibin==9) {
	m_nameBin = "2.01,2.37";
	m_Bin = 2.19;
	m_errBin = 0.18;
      }
      if (ibin==10) {
	m_nameBin = "2.37,2.47";
	m_Bin = 2.42;
	m_errBin = 0.05;
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

    // =========================================
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
	m_nameBin = "0.4;0.5";
	m_Bin = 0.45;
	m_errBin = 0.05;
      }
      if (ibin==6) {
	m_nameBin = "0.5;0.75";
	m_Bin = 0.625;
	m_errBin = 0.125;
      }
      if (ibin==7) {
	m_nameBin = "0.75;1.";
	m_Bin = 0.875;
	m_errBin = 0.125;
      }
      if (ibin==8) {
	m_nameBin = "1;1.25";
	m_Bin = 1.125;
	m_errBin = 0.125;
      }
      if (ibin==9) {
	m_nameBin = "1.25;1.5";
	m_Bin = 1.375;
	m_errBin = 0.125;
      }
      if (ibin==10) {
	m_nameBin = "1.5;1.75";
	m_Bin = 1.625;
	m_errBin = 0.125;
      }
      if (ibin==11) {
	m_nameBin = "1.75;2.";
	m_Bin = 1.875;
	m_errBin = 0.125;
      }
      if (ibin==12) {
	m_nameBin = "2.;2.5";
	m_Bin = 2.25;
	m_errBin = 0.25;
      }
      if (ibin==13) {
	m_nameBin = "2.5;pi";
	m_Bin = 2.81;
	m_errBin = 0.31;
      }
    }

    // ===================================================
    // vs MET/MTW
    if (effbinmet || effbinmtw) {
      if (ibin==1) {
	m_nameBin = "0;10";
	m_Bin = 5.;
	m_errBin = 5.;
      }
      if (ibin==2) {
	m_nameBin = "10;20";
	m_Bin = 15.;
	m_errBin = 5.;
      }
      if (ibin==3) {
	m_nameBin = "20;30";
	m_Bin = 25.;
	m_errBin = 5.;
      }
      if (ibin==4) {
	m_nameBin = "30;40";
	m_Bin = 35.;
	m_errBin = 5.;
      }
      if (ibin==5) {
	m_nameBin = "40;60";
	m_Bin = 50.;
	m_errBin = 10.;
      }
      if (ibin==6) {
	m_nameBin = "60;100";
	m_Bin = 80.;
	m_errBin = 20.;
      }
      if (ibin==7) {
	m_nameBin = "100;150";
	m_Bin = 125.;
	m_errBin = 25.;
      }
      if (ibin==8) {
	m_nameBin = "150;200";
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

  // which signal model
  bool isGauss;       
  bool isBW;          
  bool isVoigt;       
  bool isCB;          
  bool isNovosibirsk; 
  bool isConv;        
  // which background model
  bool isSlope;  
  bool isExp;    
  bool isCheb;   
  bool isRooDecay;  
  bool isLandau; 

  // range to perform the fit
  float fitmin; 
  float fitmax; 
  float sigmamean, nmean, alphamean, mmean;
  float sigmamin, sigmamax;
  float nmin, nmax;

  bool effall;
  bool effbinpt;
  bool effbineta;
  bool effbinaeta;
  bool effbindr;
  bool effbinptdr;
  bool effbinptleadjet;
  bool effbindphi;
  bool effbinmet;
  bool effbinmtw;
  bool effbinnjet;
  bool effbinnbjet;

  int m_imin;
  int m_imax;

  char* m_nameBin;
  float m_Bin;
  float m_errBin;

private:
  
  int m_nfiles;
  TFile *m_InputFileOS;
  TString m_nameHistoOS, m_nameHistoSS, m_nameHistoOSSS, m_titleOutOS; 
};


