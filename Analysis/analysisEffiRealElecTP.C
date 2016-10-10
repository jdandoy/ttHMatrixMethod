void analysisEffiRealElecTP ()
{
  //
  // macro to get histograms (Missing transverse momentum and transverse mass)
  // at Loose and Tight levels of electrons+jets events
  // These histos will be used to get real and fake efficiencies
  //

  TString name;

  // name of the TTree (at Loose level)
  TString name_Tree("nominal_Loose");
  // directory which contains input data
  TString name_dir_input("/data/atlas0/data/DATA/DATA15/DAOD_TOPQ1/filt/NTUP/merge/");
  //TString name_dir_input("/data/atlas0/data/DATA/DATA15/DAOD_EXOT4/filt/NTUP/merge/");
  // directory which contains output data
  TString name_dir_output("/data/atlas0/data/DATA/DATA15/DAOD_TOPQ1/filt/HistFinal/EffiFakeElec/");
  //TString name_dir_output("/data/atlas0/data/DATA/DATA15/DAOD_EXOT4/filt/HistFinal/EffiFakeElec/");

  // versioning of the files
  TString version = ".2337-2";
  TString versionout = ".2337-2";

  // vector of names
  std::vector<TString> names;

  name = "";
  TString option;
  TString iso = "";
  TString trigger = "";
  TStopwatch timer;
  
  gROOT->ProcessLine(".x compile.C");

  // loop on isolation
  for (int iiso = 1; iiso <= 1; iiso++) {
    if (iiso==0) iso = "";
    if (iiso==1) iso = "_Iso6";

    // loop on number of jets
    for (int ijet = 0; ijet<=4; ijet++) { 
      if (ijet==0) jet = "-njeteq1";
      if (ijet==1) jet = "-njetge1";
      if (ijet==2) jet = "-njetge2";
      if (ijet==3) jet = "-njeteq2or3";
      if (ijet==4) jet = "-njetge4";
      
      // loop on trigger
      for (int itrigger = 1; itrigger<=1; itrigger++) { 
	if (itrigger==0) trigger = "";
	if (itrigger==1) trigger = "_HLT_e24_lhmedium_iloose_L1EM20VH";
	if (itrigger==2) trigger = "_HLT_e24_lhmedium_L1EM20VH";
	if (itrigger==3) trigger = "_HLT_e60_lhmedium";
	if (itrigger==4) trigger = "_HLT_e120_lhloose";
	
	// location and name of the input file
	name = name_dir_input+"user.derue.Data-periodDtoJ.physics_Main.DAOD_TOPQ1.p2452"+version+".root";
	
	// chain 
	TChain dataset(name_Tree);
	// electron
	dataset.Add(name);
	timer.Start();
	// performs the selection
	dataset.Process("doAna/MyEffiRealElecTP.C+",option+iso+trigger+jet);
	timer.Stop(); timer.Print(); timer.Reset();
	// save output
	gROOT->ProcessLine(".! mv Ana-EffiRealElecTP.root "+name_dir_output+"user.derue.Data-periodDtoJ.physics_Main.DAOD_TOPQ1.p2452.EffiRealElecTP"+option+iso+trigger+jet+version+".root");
      }
    }
  }
}    
    
