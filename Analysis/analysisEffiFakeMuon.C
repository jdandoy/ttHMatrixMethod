void analysisEffiFakeMuon ()
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
  // directory which contains input MC
  TString name_dirmc_input("/data/atlas0/data/MC/MC15/DAOD_TOPQ1/filt/NTUP/merge/");
  // directory which contains output data
  TString name_dir_output("/data/atlas0/data/DATA/DATA15/DAOD_TOPQ1/filt/HistFinal/EffiFakeMuon/");
  //TString name_dir_output("/data/atlas0/data/DATA/DATA15/DAOD_EXOT4/filt/HistFinal/EffiFakeMuon/");
  // directory which contains output MC
  TString name_dirmc_output("/data/atlas0/data/MC/MC15/DAOD_TOPQ1/filt/HistFinal/EffiFakeMuon/");

  // versioning of the files
  TString version = ".2337-2";
  TString versionout = ".2337-2";

  // vector of names
  std::vector<TString> names;

  // if running on data
  bool useData = true;
 
  // if running on MC
  bool useMC = false;
  // if running on ttbar MC
  bool useMC_TTbar = false;
  // if running on single top MC
  bool useMC_SingleTop = false;
  // if running on diboson MC
  bool useMC_DiBoson = false;
  // if running on Z+jets (PowHeg)
  bool useMC_ZPythia8 = false;
  // if running on Z+jets (Sherpa)
  bool useMC_ZeeSherpa = false;
  bool useMC_ZmumuSherpa = false;
  bool useMC_ZtautauSherpa = false;
  bool useMC_ZeeMlt40Sherpa = false;
  bool useMC_ZmumuMlt40Sherpa = false;
  bool useMC_ZtautauMlt40Sherpa = false;

  // if running on W+jets (PowHeg)
  bool useMC_WPythia8 = false;
  // if running on W+jets (Sherpa)
  bool useMC_WenuSherpa = false;
  bool useMC_WmunuSherpa = false;
  bool useMC_WtaunuSherpa = false;
  
  // if running on dijets
  bool useMC_DiJets = false;

  // if running on ttbar MC
  if (useMC_TTbar) {        
    // ttbar at 172.5 GeV 
    name = "user.derue.mc15_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.DAOD_TOPQ1.e3698_s2608_s2183_r6765_r6282_p2454";
    names.push_back(name);
  }

  // if running on single top MC
  if (useMC_SingleTop) {        
    name = "user.derue.mc15_13TeV.410011.PowhegPythiaEvtGen_P2012_singletop_tchan_lept_top.merge.DAOD_TOPQ1.e3824_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.410012.PowhegPythiaEvtGen_P2012_singletop_tchan_lept_antitop.merge.DAOD_TOPQ1.e3824_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.410013.PowhegPythiaEvtGen_P2012_Wt_inclusive_top.merge.DAOD_TOPQ1.e3753_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.410014.PowhegPythiaEvtGen_P2012_Wt_inclusive_antitop.merge.DAOD_TOPQ1.e3753_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.410015.PowhegPythiaEvtGen_P2012_Wt_dilepton_top.merge.DAOD_TOPQ1.e3753_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.410016.PowhegPythiaEvtGen_P2012_Wt_dilepton_antitop.merge.DAOD_TOPQ1.e3753_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.410025.PowhegPythiaEvtGen_P2012_SingleTopSchan_noAllHad_top.merge.DAOD_TOPQ1.e3998_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.410026.PowhegPythiaEvtGen_P2012_SingleTopSchan_noAllHad_antitop.merge.DAOD_TOPQ1.e3998_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
  }

  // if running on diboson MC
  if (useMC_DiBoson) {        
    name = "user.derue.mc15_13TeV.361081.Sherpa_CT10_WplvWmqq.merge.DAOD_TOPQ1.e3836_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361082.Sherpa_CT10_WpqqWmlv.merge.DAOD_TOPQ1.e3836_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361083.Sherpa_CT10_WlvZqq.merge.DAOD_TOPQ1.e3836_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361084.Sherpa_CT10_WqqZll.merge.DAOD_TOPQ1.e3836_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361085.Sherpa_CT10_WqqZvv.merge.DAOD_TOPQ1.e3836_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361086.Sherpa_CT10_ZqqZll.merge.DAOD_TOPQ1.e3926_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
  }
    
  // if running on Z+jets MC
  if (useMC_ZPythia8) {    
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361106.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Zee.merge.DAOD_TOPQ1.e3601_s2576_s2132_r6765_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361107.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Zmumu.merge.DAOD_TOPQ1.e3601_s2576_s2132_r6765_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361108.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Ztautau.merge.DAOD_TOPQ1.e3601_s2576_s2132_r6765_r6282_p2454";
    names.push_back(name);
  }

  // if running on W+jets MC
  if (useMC_WPythia8) {
    name = "user.derue.mc15_13TeV.361100.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusenu.merge.DAOD_TOPQ1.e3601_s2576_s2132_r6765_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361101.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusmunu.merge.DAOD_TOPQ1.e3601_s2576_s2132_r6725_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361102.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplustaunu.merge.DAOD_TOPQ1.e3601_s2576_s2132_r6725_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361103.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminusenu.merge.DAOD_TOPQ1.e3601_s2576_s2132_r6765_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361104.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminusmunu.merge.DAOD_TOPQ1.e3601_s2576_s2132_r6725_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361105.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminustaunu.merge.DAOD_TOPQ1.e3601_s2576_s2132_r6725_r6282_p2454";
    names.push_back(name);
  }
  
  // if running on Wenu+jets MC
  if (useMC_WenuSherpa) {
    name = "user.derue.mc15_13TeV.361301.Sherpa_CT10_Wenu_Pt0_70_CFilterBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361302.Sherpa_CT10_Wenu_Pt0_70_BFilter.DAOD_TOPQ1.e3651_s2586_s2174_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361303.Sherpa_CT10_Wenu_Pt70_140_CVetoBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361304.Sherpa_CT10_Wenu_Pt70_140_CFilterBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361305.Sherpa_CT10_Wenu_Pt70_140_BFilter.DAOD_TOPQ1.e3651_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361306.Sherpa_CT10_Wenu_Pt140_280_CVetoBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361307.Sherpa_CT10_Wenu_Pt140_280_CFilterBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361308.Sherpa_CT10_Wenu_Pt140_280_BFilter.DAOD_TOPQ1.e3651_s2586_s2174_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361309.Sherpa_CT10_Wenu_Pt280_500_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361310.Sherpa_CT10_Wenu_Pt280_500_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361311.Sherpa_CT10_Wenu_Pt280_500_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361312.Sherpa_CT10_Wenu_Pt500_700_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361313.Sherpa_CT10_Wenu_Pt500_700_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361314.Sherpa_CT10_Wenu_Pt500_700_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361315.Sherpa_CT10_Wenu_Pt700_1000_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361316.Sherpa_CT10_Wenu_Pt700_1000_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361317.Sherpa_CT10_Wenu_Pt700_1000_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361318.Sherpa_CT10_Wenu_Pt1000_2000_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361319.Sherpa_CT10_Wenu_Pt1000_2000_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361320.Sherpa_CT10_Wenu_Pt1000_2000_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361321.Sherpa_CT10_Wenu_Pt2000_E_CMS_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361322.Sherpa_CT10_Wenu_Pt2000_E_CMS_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361323.Sherpa_CT10_Wenu_Pt2000_E_CMS_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
  }

  // if running on Wmunu+jets MC
  if (useMC_WmunuSherpa) {
    name = "user.derue.mc15_13TeV.361324.Sherpa_CT10_Wmunu_Pt0_70_CVetoBVeto.DAOD_TOPQ1.e3651_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361325.Sherpa_CT10_Wmunu_Pt0_70_CFilterBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361326.Sherpa_CT10_Wmunu_Pt0_70_BFilter.DAOD_TOPQ1.e3651_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361327.Sherpa_CT10_Wmunu_Pt70_140_CVetoBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361328.Sherpa_CT10_Wmunu_Pt70_140_CFilterBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361329.Sherpa_CT10_Wmunu_Pt70_140_BFilter.DAOD_TOPQ1.e3651_s2586_s2174_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361330.Sherpa_CT10_Wmunu_Pt140_280_CVetoBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361331.Sherpa_CT10_Wmunu_Pt140_280_CFilterBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361332.Sherpa_CT10_Wmunu_Pt140_280_BFilter.DAOD_TOPQ1.e3651_s2586_s2174_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361333.Sherpa_CT10_Wmunu_Pt280_500_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361334.Sherpa_CT10_Wmunu_Pt280_500_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361335.Sherpa_CT10_Wmunu_Pt280_500_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361336.Sherpa_CT10_Wmunu_Pt500_700_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361337.Sherpa_CT10_Wmunu_Pt500_700_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361338.Sherpa_CT10_Wmunu_Pt500_700_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361339.Sherpa_CT10_Wmunu_Pt700_1000_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361340.Sherpa_CT10_Wmunu_Pt700_1000_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361341.Sherpa_CT10_Wmunu_Pt700_1000_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361342.Sherpa_CT10_Wmunu_Pt1000_2000_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361343.Sherpa_CT10_Wmunu_Pt1000_2000_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361344.Sherpa_CT10_Wmunu_Pt1000_2000_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361345.Sherpa_CT10_Wmunu_Pt2000_E_CMS_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361346.Sherpa_CT10_Wmunu_Pt2000_E_CMS_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361347.Sherpa_CT10_Wmunu_Pt2000_E_CMS_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
  }

  // if running on Wtaunu+jets MC
  if (useMC_WtaunuSherpa) {
    name = "user.derue.mc15_13TeV.361348.Sherpa_CT10_Wtaunu_Pt0_70_CVetoBVeto.DAOD_TOPQ1.e3733_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361349.Sherpa_CT10_Wtaunu_Pt0_70_CFilterBVeto.DAOD_TOPQ1.e3733_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361350.Sherpa_CT10_Wtaunu_Pt0_70_BFilter.DAOD_TOPQ1.e3733_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361351.Sherpa_CT10_Wtaunu_Pt70_140_CVetoBVeto.DAOD_TOPQ1.e3733_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361352.Sherpa_CT10_Wtaunu_Pt70_140_CFilterBVeto.DAOD_TOPQ1.e3733_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361353.Sherpa_CT10_Wtaunu_Pt70_140_BFilter.DAOD_TOPQ1.e3733_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361354.Sherpa_CT10_Wtaunu_Pt140_280_CVetoBVeto.DAOD_TOPQ1.e3733_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361355.Sherpa_CT10_Wtaunu_Pt140_280_CFilterBVeto.DAOD_TOPQ1.e3733_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361356.Sherpa_CT10_Wtaunu_Pt140_280_BFilter.DAOD_TOPQ1.e3733_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361357.Sherpa_CT10_Wtaunu_Pt280_500_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361358.Sherpa_CT10_Wtaunu_Pt280_500_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361359.Sherpa_CT10_Wtaunu_Pt280_500_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361360.Sherpa_CT10_Wtaunu_Pt500_700_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361361.Sherpa_CT10_Wtaunu_Pt500_700_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361362.Sherpa_CT10_Wtaunu_Pt500_700_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361363.Sherpa_CT10_Wtaunu_Pt700_1000_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361364.Sherpa_CT10_Wtaunu_Pt700_1000_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361365.Sherpa_CT10_Wtaunu_Pt700_1000_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361366.Sherpa_CT10_Wtaunu_Pt1000_2000_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361367.Sherpa_CT10_Wtaunu_Pt1000_2000_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361368.Sherpa_CT10_Wtaunu_Pt1000_2000_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361369.Sherpa_CT10_Wtaunu_Pt2000_E_CMS_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361370.Sherpa_CT10_Wtaunu_Pt2000_E_CMS_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361371.Sherpa_CT10_Wtaunu_Pt2000_E_CMS_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
  }

  // if running on Zee+jets Mll>40 GeV MC
  if (useMC_ZeeSherpa) {
    name = "user.derue.mc15_13TeV.361372.Sherpa_CT10_Zee_Pt0_70_CVetoBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361373.Sherpa_CT10_Zee_Pt0_70_CFilterBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361374.Sherpa_CT10_Zee_Pt0_70_BFilter.DAOD_TOPQ1.e3651_s2586_s2174_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361375.Sherpa_CT10_Zee_Pt70_140_CVetoBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361376.Sherpa_CT10_Zee_Pt70_140_CFilterBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361377.Sherpa_CT10_Zee_Pt70_140_BFilter.DAOD_TOPQ1.e3651_s2586_s2174_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361378.Sherpa_CT10_Zee_Pt140_280_CVetoBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361379.Sherpa_CT10_Zee_Pt140_280_CFilterBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361380.Sherpa_CT10_Zee_Pt140_280_BFilter.DAOD_TOPQ1.e3651_s2586_s2174_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361381.Sherpa_CT10_Zee_Pt280_500_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361382.Sherpa_CT10_Zee_Pt280_500_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361383.Sherpa_CT10_Zee_Pt280_500_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361384.Sherpa_CT10_Zee_Pt500_700_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361385.Sherpa_CT10_Zee_Pt500_700_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361386.Sherpa_CT10_Zee_Pt500_700_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361387.Sherpa_CT10_Zee_Pt700_1000_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361388.Sherpa_CT10_Zee_Pt700_1000_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361389.Sherpa_CT10_Zee_Pt700_1000_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361390.Sherpa_CT10_Zee_Pt1000_2000_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361391.Sherpa_CT10_Zee_Pt1000_2000_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361392.Sherpa_CT10_Zee_Pt1000_2000_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361393.Sherpa_CT10_Zee_Pt2000_E_CMS_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361394.Sherpa_CT10_Zee_Pt2000_E_CMS_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361395.Sherpa_CT10_Zee_Pt2000_E_CMS_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
  }

  // if running on Zmumu+jets Mll>40 GeV MC
  if (useMC_ZmumuSherpa) {
    name = "user.derue.mc15_13TeV.361396.Sherpa_CT10_Zmumu_Pt0_70_CVetoBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361397.Sherpa_CT10_Zmumu_Pt0_70_CFilterBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361398.Sherpa_CT10_Zmumu_Pt0_70_BFilter.DAOD_TOPQ1.e3651_s2586_s2174_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361399.Sherpa_CT10_Zmumu_Pt70_140_CVetoBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361400.Sherpa_CT10_Zmumu_Pt70_140_CFilterBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361401.Sherpa_CT10_Zmumu_Pt70_140_BFilter.DAOD_TOPQ1.e3651_s2586_s2174_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361402.Sherpa_CT10_Zmumu_Pt140_280_CVetoBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361402.Sherpa_CT10_Zmumu_Pt140_280_CVetoBVeto.DAOD_TOPQ1.e3651_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361403.Sherpa_CT10_Zmumu_Pt140_280_CFilterBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361404.Sherpa_CT10_Zmumu_Pt140_280_BFilter.DAOD_TOPQ1.e3651_s2586_s2174_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361405.Sherpa_CT10_Zmumu_Pt280_500_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361406.Sherpa_CT10_Zmumu_Pt280_500_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361407.Sherpa_CT10_Zmumu_Pt280_500_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361408.Sherpa_CT10_Zmumu_Pt500_700_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361409.Sherpa_CT10_Zmumu_Pt500_700_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361410.Sherpa_CT10_Zmumu_Pt500_700_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361411.Sherpa_CT10_Zmumu_Pt700_1000_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361412.Sherpa_CT10_Zmumu_Pt700_1000_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361413.Sherpa_CT10_Zmumu_Pt700_1000_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361414.Sherpa_CT10_Zmumu_Pt1000_2000_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361415.Sherpa_CT10_Zmumu_Pt1000_2000_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361416.Sherpa_CT10_Zmumu_Pt1000_2000_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361417.Sherpa_CT10_Zmumu_Pt2000_E_CMS_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361418.Sherpa_CT10_Zmumu_Pt2000_E_CMS_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361419.Sherpa_CT10_Zmumu_Pt2000_E_CMS_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
  }

  // if running on Ztautau+jets Mll>40 GeV MC
  if (useMC_ZtautauSherpa) {
    name = "user.derue.mc15_13TeV.361420.Sherpa_CT10_Ztautau_Pt0_70_CVetoBVeto.DAOD_TOPQ1.e3733_s2586_s2174_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361420.Sherpa_CT10_Ztautau_Pt0_70_CVetoBVeto.DAOD_TOPQ1.e3733_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361421.Sherpa_CT10_Ztautau_Pt0_70_CFilterBVeto.DAOD_TOPQ1.e3733_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361422.Sherpa_CT10_Ztautau_Pt0_70_BFilter.DAOD_TOPQ1.e3733_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361423.Sherpa_CT10_Ztautau_Pt70_140_CVetoBVeto.DAOD_TOPQ1.e3733_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361424.Sherpa_CT10_Ztautau_Pt70_140_CFilterBVeto.DAOD_TOPQ1.e3733_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361425.Sherpa_CT10_Ztautau_Pt70_140_BFilter.DAOD_TOPQ1.e3733_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361426.Sherpa_CT10_Ztautau_Pt140_280_CVetoBVeto.DAOD_TOPQ1.e3733_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361427.Sherpa_CT10_Ztautau_Pt140_280_CFilterBVeto.DAOD_TOPQ1.e3733_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361428.Sherpa_CT10_Ztautau_Pt140_280_BFilter.DAOD_TOPQ1.e3733_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361429.Sherpa_CT10_Ztautau_Pt280_500_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361430.Sherpa_CT10_Ztautau_Pt280_500_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361431.Sherpa_CT10_Ztautau_Pt280_500_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361432.Sherpa_CT10_Ztautau_Pt500_700_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361433.Sherpa_CT10_Ztautau_Pt500_700_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361434.Sherpa_CT10_Ztautau_Pt500_700_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361435.Sherpa_CT10_Ztautau_Pt700_1000_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361436.Sherpa_CT10_Ztautau_Pt700_1000_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361437.Sherpa_CT10_Ztautau_Pt700_1000_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361438.Sherpa_CT10_Ztautau_Pt1000_2000_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361439.Sherpa_CT10_Ztautau_Pt1000_2000_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361440.Sherpa_CT10_Ztautau_Pt1000_2000_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361441.Sherpa_CT10_Ztautau_Pt2000_E_CMS_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361442.Sherpa_CT10_Ztautau_Pt2000_E_CMS_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361443.Sherpa_CT10_Ztautau_Pt2000_E_CMS_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
  }


  // if running on Zee+jets 10GeV<Mll<40GeV MC
  if (useMC_ZeeMlt40Sherpa) {
    name = "user.derue.mc15_13TeV.361468.Sherpa_CT10_Zee_Mll10to40_Pt0_70_BVeto.DAOD_TOPQ1.e4198_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361469.Sherpa_CT10_Zee_Mll10to40_Pt0_70_BFilter.DAOD_TOPQ1.e4198_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361470.Sherpa_CT10_Zee_Mll10to40_Pt70_140_BVeto.DAOD_TOPQ1.e4198_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361471.Sherpa_CT10_Zee_Mll10to40_Pt70_140_BFilter.DAOD_TOPQ1.e4198_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361472.Sherpa_CT10_Zee_Mll10to40_Pt140_400_BVeto.DAOD_TOPQ1.e4198_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361473.Sherpa_CT10_Zee_Mll10to40_Pt140_400_BFilter.DAOD_TOPQ1.e4198_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361474.Sherpa_CT10_Zee_Mll10to40_Pt400_E_CMS_BVeto.DAOD_TOPQ1.e4198_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361475.Sherpa_CT10_Zee_Mll10to40_Pt400_E_CMS_BFilter.DAOD_TOPQ1.e4198_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
  }

  // if running on Zmumu+jets 10GeV<Mll<40GeV MC
  if (useMC_ZmumuMlt40Sherpa) {
    name = "user.derue.mc15_13TeV.361476.Sherpa_CT10_Zmumu_Mll10to40_Pt0_70_BVeto.DAOD_TOPQ1.e4198_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361477.Sherpa_CT10_Zmumu_Mll10to40_Pt0_70_BFilter.DAOD_TOPQ1.e4198_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361478.Sherpa_CT10_Zmumu_Mll10to40_Pt70_140_BVeto.DAOD_TOPQ1.e4198_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361479.Sherpa_CT10_Zmumu_Mll10to40_Pt70_140_BFilter.DAOD_TOPQ1.e4198_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361480.Sherpa_CT10_Zmumu_Mll10to40_Pt140_400_BVeto.DAOD_TOPQ1.e4198_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361481.Sherpa_CT10_Zmumu_Mll10to40_Pt140_400_BFilter.DAOD_TOPQ1.e4198_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361482.Sherpa_CT10_Zmumu_Mll10to40_Pt400_E_CMS_BVeto.DAOD_TOPQ1.e4198_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361483.Sherpa_CT10_Zmumu_Mll10to40_Pt400_E_CMS_BFilter.DAOD_TOPQ1.e4198_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
  }

  // if running on Ztautau+jets 10GeV<Mll<40GeV MC
  if (useMC_ZtautauMlt40Sherpa) {
    name = "user.derue.mc15_13TeV.361484.Sherpa_CT10_Ztautau_Mll10to40_Pt0_70_BVeto.DAOD_TOPQ1.e4198_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361485.Sherpa_CT10_Ztautau_Mll10to40_Pt0_70_BFilter.DAOD_TOPQ1.e4198_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361486.Sherpa_CT10_Ztautau_Mll10to40_Pt70_140_BVeto.DAOD_TOPQ1.e4198_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361487.Sherpa_CT10_Ztautau_Mll10to40_Pt70_140_BFilter.DAOD_TOPQ1.e4198_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361488.Sherpa_CT10_Ztautau_Mll10to40_Pt140_400_BVeto.DAOD_TOPQ1.e4198_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361489.Sherpa_CT10_Ztautau_Mll10to40_Pt140_400_BFilter.DAOD_TOPQ1.e4198_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361490.Sherpa_CT10_Ztautau_Mll10to40_Pt400_E_CMS_BVeto.DAOD_TOPQ1.e4198_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
    name = "user.derue.mc15_13TeV.361491.Sherpa_CT10_Ztautau_Mll10to40_Pt400_E_CMS_BFilter.DAOD_TOPQ1.e4198_s2608_s2183_r6869_r6282_p2454";
    names.push_back(name);
  }

  // if running on dijets MC
  if (useMC_DiJets) {
  }
  
  name = "";
  TString option;
  TString iso = "";
  TString trigger = "";
  TStopwatch timer;
  
  gROOT->ProcessLine(".x compile.C");

  // loop on isolation
  for (int iiso = 0; iiso <= 0; iiso++) {
    if (iiso==0) iso = "";
    if (iiso==1) iso = "_Iso6";

    // loop on trigger
    for (int itrigger = 0; itrigger<=0; itrigger++) { 
      if (itrigger==0) trigger = "";
      if (itrigger==1) trigger = "_HLT_mu20_iloose_L1MU15";
      if (itrigger==2) trigger = "_HLT_mu50";
      if (itrigger==3) trigger = "_HLT_mu20_L1MU15"; // not ok for TOPQ1
      
      // loop on selection
      for (int i = 0; i <= 0; i++) { 
	
	// CR (no cut)
	if (i==0)  option = "_lowETmissnocut_pretag";
	if (i==1)  option = "_lowETmissnocut_nobtag";
	if (i==2)  option = "_lowETmissnocut_btag";
	
	// CR HighMTW (for real efficiencies)
	if (i==3)  option = "_highMTW_pretag";
	if (i==4)  option = "_highMTW_nobtag";
	if (i==5)  option = "_highMTW_btag";
		
	// CR with MET+MTW<60 GeV & MTW<20 GeV
	if (i==6)  option = "_lowETmissMTW_pretag";
	if (i==7)  option = "_lowETmissMTW_nobtag";
	if (i==8)  option = "_lowETmissMTW_btag";
	
	// CR with MET<20 GeV
	if (i==9)  option = "_lowETmiss20_pretag";
	if (i==10)  option = "_lowETmiss20_nobtag";
	if (i==11)  option = "_lowETmiss20_btag";
	
	// CR |d0sig|>5
	if (i==12)  option = "_highd0sig_pretag";
	if (i==13)  option = "_highd0sig_nobtag";
	if (i==14)  option = "_highd0sig_btag";

	// CR with MET<20 GeV & MT><20 GeV
	if (i==15)  option = "_lowETmissMTW20_pretag";
	if (i==16)  option = "_lowETmissMTW20_nobtag";
	if (i==17)  option = "_lowETmissMTW20_btag";
	
	/// data 
	if (useData) {
	  // location and name of the input file
	  name = name_dir_input+"user.derue.Data-periodDtoJ.physics_Main.DAOD_TOPQ1.p2452"+version+".root";
	  //name = name_dir_input+"user.derue.Data-periodD.physics_Main.DAOD_EXOT4.p2425"+version+".root";
	  // chain 
	  TChain dataset(name_Tree);
	  // electron
	  dataset.Add(name);
	  timer.Start();
	  // performs the selection
	  dataset.Process("doAna/MyEffiFakeMuon.C+",option+iso+trigger);
	  timer.Stop(); timer.Print(); timer.Reset();
	  // save output
	  gROOT->ProcessLine(".! mv Ana-EffiFakeMuon.root "+name_dir_output+"user.derue.Data-periodDtoJ.physics_Main.DAOD_TOPQ1.p2452.EffiFakeMuon"+option+iso+trigger+version+".root");
	  //gROOT->ProcessLine(".! mv Ana-EffiFakeMuon.root "+name_dir_output+"user.derue.Data-periodD.physics_Main.DAOD_EXOT4.p2425.EffiFakeMuon"+option+trigger+version+".root");
	}    
    
	// MC
	if (useMC) {
	  // loop on all datasets
	  for (std::vector<TString>::iterator it = names.begin(); it < names.end(); it++) {
	    // location and name of the input file
	    name = name_dirmc_input+*it+version+".root";
	    // chain
	    TChain dataset(name_Tree); 
	    dataset.Add(name);
	    std::cout<<"Reading file "<<name<<std::endl;
	    timer.Start();
	    // performs the selection
	    dataset.Process("doAna/MyEffiFakeMuon.C+",option+iso+trigger);
	    timer.Stop(); timer.Print(); timer.Reset();
	    // save output
	    gROOT->ProcessLine(".! mv Ana-EffiFakeMuon.root "+name_dirmc_output+*it+".EffiFakeMuon"+option+iso+trigger+versionout+".root");
	  }
	}
      }
    }
  }
}

