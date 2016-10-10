void analysisFakeSemiLeptonic()
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
  // directory which contains output data
  TString name_dir_output("/data/atlas0/data/DATA/DATA15/DAOD_TOPQ1/filt/HistFinal/SemiLeptonic/");

  // versioning of the files
  TString version = ".2337-2";

  // vector of names
  std::vector<TString> names;

  // if running on data 
  bool useData = true;
  
  name = "";
  TString iso = "";
  TString option = "";
  TStopwatch timer;
  
  gROOT->ProcessLine(".x compile.C");
  
  // loop on isolation
  for (int iiso = 0; iiso <= 0; iiso++) {
    if (iiso==0) iso = "";
    if (iiso==1) iso = "_Iso6";
  
    for (int i=1; i<=1; i++) {
      if (i==0)   option = "";
      if (i==1)   option = "_estimate";
      if (i==2)   option = "_estimateMCup";
      if (i==3)   option = "_estimateMCdown";
      if (i==4)   option = "_estimateCRfake";
      if (i==5)   option = "_estimateCRreal";
      if (i==6)   option = "_estimateEffPar";
      
      /// data 
      if (useData) {
      // location and name of the input file
	name = name_dir_input+"user.derue.Data-periodDtoJ.physics_Main.DAOD_TOPQ1.p2452"+version+".root";
	// chain 
	TChain dataset(name_Tree);
	
	// l+jet
	dataset.Add(name);
	timer.Start();
	// performs the selection
	dataset.Process("doAna/MyFakeSemiLeptonic.C+",option+iso);
	timer.Stop(); timer.Print(); timer.Reset();
	// save output
	gROOT->ProcessLine(".! mv Ana-FakeSemiLeptonic.root "+name_dir_output+"user.derue.Data-periodDtoJ.physics_Main.DAOD_TOPQ1.p2452.FakeSemiLeptonic"+option+iso+version+".root");
	
      }   
    } 
  }
}

