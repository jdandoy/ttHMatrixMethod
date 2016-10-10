#include "TLegend.h"
#include "TProfile.h"
#include "AtlasUtils.h"
#include "AtlasLabels.h"
#include "AtlasStyle.h"
#include "TMath.h"
#include "TString.h"
#include "TGraph.h"
#include <vector>
#include <string>
#include <cmath>

void plotControlEffiFakeMuon()
{

  gROOT->LoadMacro("AtlasStyle.C");
  gROOT->LoadMacro("AtlasUtils.C");
  gROOT->LoadMacro("AtlasLabels.C");
  
  SetAtlasStyle();

  
  TString inputdatadir = "/nfs/dust/atlas/group/top/Nedaa_Ntuples_MM/OutputHistos/output_DataMuons/";
  TString inputmcdir   = "/nfs/dust/atlas/group/top/Nedaa_Ntuples_MM/OutputHistos/output_MCMuons/";
  TString destdir = "fig-effifakemuon/";

  //TString trigger = "";
  //TString trigger = "_HLT_mu20_L1MU15";
  //TString trigger = "_HLT_mu50";
  TString trigger = "_HLT_mu20_iloose_L1MU15";

  
  plotControlEffiFakeMuon myplot(inputdatadir, inputmcdir, 
  				 "_lowETmissnocut_pretag", trigger, "_Loose","_1j", 
  				 destdir);
  //plotControlEffiFakeMuon myplot(inputdatadir, inputmcdir, 
  //				 "_highd0sig_pretag", trigger, "_Loose","_1j", 
  //				 destdir);
  //plotControlEffiFakeMuon myplot(inputdatadir, inputmcdir, 
  //				 "_lowETmissMTW_nobtag", trigger, 
  //				 "_Tight","_ge4j", 
  //				 destdir);
  myplot.execute();
  
  return;
}

class plotControlEffiFakeMuon{
public:
  TString m_name_dir_datainput;
  TString m_name_dir_mcinput;
  TString m_level;
  TString m_jet;
  TString m_figdir;
  TString m_prefix;
  TString m_option;
  TString m_suffix;
  TString m_pid;
  TString m_iso;
  TString m_trigger;
  
  int m_min;
  int m_max;

  bool m_log;
  
  plotControlEffiFakeMuon(TString dir_datainput, TString dir_mcinput, 
			  TString level, TString trigger, TString pid,
			  TString jet, TString figdir)
  {

    m_name_dir_datainput = dir_datainput;
    m_name_dir_mcinput   = dir_mcinput;
    m_level              = level;
    m_trigger            = trigger;
    m_jet                = jet;
    m_pid                = pid;
    m_figdir             = figdir;
  }
  
  // ================================================
  execute() {
    
    m_min=0; //This is only or ETmiss
    m_max=0;

    gROOT->Reset();
    gROOT->SetStyle("ATLAS");
    gROOT->ForceStyle();
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);

    TString name;
    TString version = ".2341";

    // data
    name = "user.derue.Data-periodDtoJ.physics_Main.DAOD_TOPQ1.p2452.EffiFakeMuon"+m_level+m_trigger+version+".root";

    m_fdata = new TFile(m_name_dir_datainput++name,"read"); 
    
    // ====================================================
    // ====================================================
    // tbbar
    name = "user.derue.mc15_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.DAOD_TOPQ1.e3698_s2608_s2183_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fttbar = new TFile(m_name_dir_mcinput+name,"read");
    //std::cout << " namettbar = " << name << std::endl;

    // single top
    name = "user.derue.mc15_13TeV.410011.PowhegPythiaEvtGen_P2012_singletop_tchan_lept_top.merge.DAOD_TOPQ1.e3824_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fst[0] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.410012.PowhegPythiaEvtGen_P2012_singletop_tchan_lept_antitop.merge.DAOD_TOPQ1.e3824_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fst[1] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.410013.PowhegPythiaEvtGen_P2012_Wt_inclusive_top.merge.DAOD_TOPQ1.e3753_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fst[2] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.410014.PowhegPythiaEvtGen_P2012_Wt_inclusive_antitop.merge.DAOD_TOPQ1.e3753_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fst[3] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.410015.PowhegPythiaEvtGen_P2012_Wt_dilepton_top.merge.DAOD_TOPQ1.e3753_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fst[4] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.410016.PowhegPythiaEvtGen_P2012_Wt_dilepton_antitop.merge.DAOD_TOPQ1.e3753_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fst[5] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.410025.PowhegPythiaEvtGen_P2012_SingleTopSchan_noAllHad_top.merge.DAOD_TOPQ1.e3998_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fst[6] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.410026.PowhegPythiaEvtGen_P2012_SingleTopSchan_noAllHad_antitop.merge.DAOD_TOPQ1.e3998_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fst[7] = new TFile(m_name_dir_mcinput+name,"read");
    m_numTopFiles = 8;
    //std::cout << " nameSingleTop = " << name << std::endl; 
    
    // diboson samples
    name = "user.derue.mc15_13TeV.361063.Sherpa_CT10_llll.merge.DAOD_TOPQ1.e3836_s2608_s2183_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fdiboson[0] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361064.Sherpa_CT10_lllvSFMinus.merge.DAOD_TOPQ1.e3836_s2608_s2183_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fdiboson[1] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361065.Sherpa_CT10_lllvOFMinus.merge.DAOD_TOPQ1.e3836_s2608_s2183_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fdiboson[2] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361066.Sherpa_CT10_lllvSFPlus.merge.DAOD_TOPQ1.e3836_s2608_s2183_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fdiboson[3] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361067.Sherpa_CT10_lllvOFPlus.merge.DAOD_TOPQ1.e3836_s2608_s2183_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fdiboson[4] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361068.Sherpa_CT10_llvv.merge.DAOD_TOPQ1.e3836_s2608_s2183_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fdiboson[5] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361069.Sherpa_CT10_llvvjj_ss_EW4.merge.DAOD_TOPQ1.e3836_s2608_s2183_r7267_r6282_p2460.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fdiboson[6] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361070.Sherpa_CT10_llvvjj_ss_EW6.merge.DAOD_TOPQ1.e3836_s2608_s2183_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fdiboson[7] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361071.Sherpa_CT10_lllvjj_EW6.merge.DAOD_TOPQ1.e3836_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fdiboson[8] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361072.Sherpa_CT10_lllljj_EW6.merge.DAOD_TOPQ1.e3836_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fdiboson[9] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361077.Sherpa_CT10_ggllvv.merge.DAOD_TOPQ1.e4641_s2726_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fdiboson[10] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361078.Sherpa_CT10_ggllvvNoHiggs.merge.DAOD_TOPQ1.e4641_s2726_r7326_r6282_p2471.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fdiboson[11] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361081.Sherpa_CT10_WplvWmqq.merge.DAOD_TOPQ1.e3836_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fdiboson[12] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361082.Sherpa_CT10_WpqqWmlv.merge.DAOD_TOPQ1.e3836_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fdiboson[13] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361083.Sherpa_CT10_WlvZqq.merge.DAOD_TOPQ1.e3836_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fdiboson[14] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361084.Sherpa_CT10_WqqZll.merge.DAOD_TOPQ1.e3836_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fdiboson[15] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361086.Sherpa_CT10_ZqqZll.merge.DAOD_TOPQ1.e3926_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fdiboson[16] = new TFile(m_name_dir_mcinput+name,"read");
    m_numDibosonFiles = 17;
    //std::cout << " nameDiboson = " << name << std::endl;

      
    // ### Z+jets samples (Pythia8+EvtGen)
    //## Z+jets unfiltered
    /*name = "user.derue.mc15_13TeV.361106.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Zee.merge.DAOD_TOPQ1.e3601_s2576_s2132_r6765_r6282_p2454.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[0] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361107.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Zmumu.merge.DAOD_TOPQ1.e3601_s2576_s2132_r6765_r6282_p2454.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[1] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361108.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Ztautau.merge.DAOD_TOPQ1.e3601_s2576_s2132_r6765_r6282_p2454.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[2] = new TFile(m_name_dir_mcinput+name,"read");
    
    // ### W+jets samples (Pythia8+EvtGen)
    //## W+jets unfiltered
    name = "user.derue.mc15_13TeV.361100.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusenu.merge.DAOD_TOPQ1.e3601_s2576_s2132_r6765_r6282_p2454.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[0] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361101.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusmunu.merge.DAOD_TOPQ1.e3601_s2576_s2132_r6725_r6282_p2454.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[1] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361102.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplustaunu.merge.DAOD_TOPQ1.e3601_s2576_s2132_r6725_r6282_p2454.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[2] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361103.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminusenu.merge.DAOD_TOPQ1.e3601_s2576_s2132_r6765_r6282_p2454.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[3] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361104.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminusmunu.merge.DAOD_TOPQ1.e3601_s2576_s2132_r6725_r6282_p2454.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[4] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361105.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminustaunu.merge.DAOD_TOPQ1.e3601_s2576_s2132_r6725_r6282_p2454.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[5] = new TFile(m_name_dir_mcinput+name,"read");
*/
    //W+jets Sherpa
    name = "user.derue.mc15_13TeV.361371.Sherpa_CT10_Wtaunu_Pt2000_E_CMS_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[0] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361301.Sherpa_CT10_Wenu_Pt0_70_CFilterBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[1] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361302.Sherpa_CT10_Wenu_Pt0_70_BFilter.DAOD_TOPQ1.e3651_s2586_s2174_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[2] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361303.Sherpa_CT10_Wenu_Pt70_140_CVetoBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[3] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361304.Sherpa_CT10_Wenu_Pt70_140_CFilterBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[4] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361305.Sherpa_CT10_Wenu_Pt70_140_BFilter.DAOD_TOPQ1.e3651_s2586_s2174_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[5] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361306.Sherpa_CT10_Wenu_Pt140_280_CVetoBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[6] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361307.Sherpa_CT10_Wenu_Pt140_280_CFilterBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[7] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361308.Sherpa_CT10_Wenu_Pt140_280_BFilter.DAOD_TOPQ1.e3651_s2586_s2174_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[8] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361309.Sherpa_CT10_Wenu_Pt280_500_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[9] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361310.Sherpa_CT10_Wenu_Pt280_500_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[10] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361311.Sherpa_CT10_Wenu_Pt280_500_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[11] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361312.Sherpa_CT10_Wenu_Pt500_700_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[12] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361313.Sherpa_CT10_Wenu_Pt500_700_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[13] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361314.Sherpa_CT10_Wenu_Pt500_700_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[14] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361315.Sherpa_CT10_Wenu_Pt700_1000_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[15] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361316.Sherpa_CT10_Wenu_Pt700_1000_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[16] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361317.Sherpa_CT10_Wenu_Pt700_1000_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[17] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361318.Sherpa_CT10_Wenu_Pt1000_2000_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[18] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361319.Sherpa_CT10_Wenu_Pt1000_2000_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[19] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361320.Sherpa_CT10_Wenu_Pt1000_2000_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[20] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361321.Sherpa_CT10_Wenu_Pt2000_E_CMS_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[21] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361322.Sherpa_CT10_Wenu_Pt2000_E_CMS_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[22] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361323.Sherpa_CT10_Wenu_Pt2000_E_CMS_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[23] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361324.Sherpa_CT10_Wmunu_Pt0_70_CVetoBVeto.DAOD_TOPQ1.e3651_s2608_s2183_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[24] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361325.Sherpa_CT10_Wmunu_Pt0_70_CFilterBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[25] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361326.Sherpa_CT10_Wmunu_Pt0_70_BFilter.DAOD_TOPQ1.e3651_s2608_s2183_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[26] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361327.Sherpa_CT10_Wmunu_Pt70_140_CVetoBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[27] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361328.Sherpa_CT10_Wmunu_Pt70_140_CFilterBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[28] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361329.Sherpa_CT10_Wmunu_Pt70_140_BFilter.DAOD_TOPQ1.e3651_s2586_s2174_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[29] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361330.Sherpa_CT10_Wmunu_Pt140_280_CVetoBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[30] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361331.Sherpa_CT10_Wmunu_Pt140_280_CFilterBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[31] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361332.Sherpa_CT10_Wmunu_Pt140_280_BFilter.DAOD_TOPQ1.e3651_s2586_s2174_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[32] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361333.Sherpa_CT10_Wmunu_Pt280_500_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[33] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361334.Sherpa_CT10_Wmunu_Pt280_500_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[34] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361335.Sherpa_CT10_Wmunu_Pt280_500_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[35] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361336.Sherpa_CT10_Wmunu_Pt500_700_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[36] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361337.Sherpa_CT10_Wmunu_Pt500_700_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[37] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361338.Sherpa_CT10_Wmunu_Pt500_700_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[38] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361339.Sherpa_CT10_Wmunu_Pt700_1000_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[39] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361341.Sherpa_CT10_Wmunu_Pt700_1000_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[40] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361342.Sherpa_CT10_Wmunu_Pt1000_2000_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[41] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361343.Sherpa_CT10_Wmunu_Pt1000_2000_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[42] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361344.Sherpa_CT10_Wmunu_Pt1000_2000_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[43] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361345.Sherpa_CT10_Wmunu_Pt2000_E_CMS_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[44] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361346.Sherpa_CT10_Wmunu_Pt2000_E_CMS_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[45] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361347.Sherpa_CT10_Wmunu_Pt2000_E_CMS_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[46] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361348.Sherpa_CT10_Wtaunu_Pt0_70_CVetoBVeto.DAOD_TOPQ1.e3733_s2608_s2183_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[47] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361349.Sherpa_CT10_Wtaunu_Pt0_70_CFilterBVeto.DAOD_TOPQ1.e3733_s2608_s2183_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[48] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361350.Sherpa_CT10_Wtaunu_Pt0_70_BFilter.DAOD_TOPQ1.e3733_s2608_s2183_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[49] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361351.Sherpa_CT10_Wtaunu_Pt70_140_CVetoBVeto.DAOD_TOPQ1.e3733_s2608_s2183_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[50] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361352.Sherpa_CT10_Wtaunu_Pt70_140_CFilterBVeto.DAOD_TOPQ1.e3733_s2608_s2183_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[51] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361353.Sherpa_CT10_Wtaunu_Pt70_140_BFilter.DAOD_TOPQ1.e3733_s2608_s2183_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[52] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361354.Sherpa_CT10_Wtaunu_Pt140_280_CVetoBVeto.DAOD_TOPQ1.e3733_s2608_s2183_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[53] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361355.Sherpa_CT10_Wtaunu_Pt140_280_CFilterBVeto.DAOD_TOPQ1.e3733_s2608_s2183_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[54] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361356.Sherpa_CT10_Wtaunu_Pt140_280_BFilter.DAOD_TOPQ1.e3733_s2608_s2183_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[55] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361357.Sherpa_CT10_Wtaunu_Pt280_500_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[56] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361358.Sherpa_CT10_Wtaunu_Pt280_500_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[57] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361359.Sherpa_CT10_Wtaunu_Pt280_500_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[58] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361360.Sherpa_CT10_Wtaunu_Pt500_700_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[59] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361361.Sherpa_CT10_Wtaunu_Pt500_700_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[60] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361362.Sherpa_CT10_Wtaunu_Pt500_700_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[61] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361363.Sherpa_CT10_Wtaunu_Pt700_1000_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[62] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361365.Sherpa_CT10_Wtaunu_Pt700_1000_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[63] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361366.Sherpa_CT10_Wtaunu_Pt1000_2000_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[64] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361367.Sherpa_CT10_Wtaunu_Pt1000_2000_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[65] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361368.Sherpa_CT10_Wtaunu_Pt1000_2000_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[66] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361369.Sherpa_CT10_Wtaunu_Pt2000_E_CMS_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[67] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361370.Sherpa_CT10_Wtaunu_Pt2000_E_CMS_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[68] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361300.Sherpa_CT10_Wenu_Pt0_70_CVetoBVeto.merge.DAOD_TOPQ1.e3651_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[69] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361340.Sherpa_CT10_Wmunu_Pt700_1000_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[70] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361364.Sherpa_CT10_Wtaunu_Pt700_1000_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fw[71] = new TFile(m_name_dir_mcinput+name,"read");
    m_numWFiles = 72;

    //Z+jets Sherpa
    name = "user.derue.mc15_13TeV.361372.Sherpa_CT10_Zee_Pt0_70_CVetoBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[0] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361373.Sherpa_CT10_Zee_Pt0_70_CFilterBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[1] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361374.Sherpa_CT10_Zee_Pt0_70_BFilter.DAOD_TOPQ1.e3651_s2586_s2174_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[2] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361375.Sherpa_CT10_Zee_Pt70_140_CVetoBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[3] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361376.Sherpa_CT10_Zee_Pt70_140_CFilterBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[4] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361377.Sherpa_CT10_Zee_Pt70_140_BFilter.DAOD_TOPQ1.e3651_s2586_s2174_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[5] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361378.Sherpa_CT10_Zee_Pt140_280_CVetoBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[6] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361379.Sherpa_CT10_Zee_Pt140_280_CFilterBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[7] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361380.Sherpa_CT10_Zee_Pt140_280_BFilter.DAOD_TOPQ1.e3651_s2586_s2174_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[8] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361381.Sherpa_CT10_Zee_Pt280_500_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[9] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361382.Sherpa_CT10_Zee_Pt280_500_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[10] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361383.Sherpa_CT10_Zee_Pt280_500_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[11] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361384.Sherpa_CT10_Zee_Pt500_700_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[12] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361385.Sherpa_CT10_Zee_Pt500_700_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[13] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361386.Sherpa_CT10_Zee_Pt500_700_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[14] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361387.Sherpa_CT10_Zee_Pt700_1000_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[15] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361388.Sherpa_CT10_Zee_Pt700_1000_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[16] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361389.Sherpa_CT10_Zee_Pt700_1000_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[17] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361390.Sherpa_CT10_Zee_Pt1000_2000_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[18] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361391.Sherpa_CT10_Zee_Pt1000_2000_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[19] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361392.Sherpa_CT10_Zee_Pt1000_2000_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[20] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361393.Sherpa_CT10_Zee_Pt2000_E_CMS_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[21] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361394.Sherpa_CT10_Zee_Pt2000_E_CMS_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[22] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361395.Sherpa_CT10_Zee_Pt2000_E_CMS_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[23] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361396.Sherpa_CT10_Zmumu_Pt0_70_CVetoBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[24] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361397.Sherpa_CT10_Zmumu_Pt0_70_CFilterBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[25] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361398.Sherpa_CT10_Zmumu_Pt0_70_BFilter.DAOD_TOPQ1.e3651_s2586_s2174_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[26] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361399.Sherpa_CT10_Zmumu_Pt70_140_CVetoBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[27] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361400.Sherpa_CT10_Zmumu_Pt70_140_CFilterBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[28] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361401.Sherpa_CT10_Zmumu_Pt70_140_BFilter.DAOD_TOPQ1.e3651_s2586_s2174_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[29] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361402.Sherpa_CT10_Zmumu_Pt140_280_CVetoBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[30] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361412.Sherpa_CT10_Zmumu_Pt700_1000_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[31] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361403.Sherpa_CT10_Zmumu_Pt140_280_CFilterBVeto.DAOD_TOPQ1.e3651_s2586_s2174_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[32] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361404.Sherpa_CT10_Zmumu_Pt140_280_BFilter.DAOD_TOPQ1.e3651_s2586_s2174_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[33] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361405.Sherpa_CT10_Zmumu_Pt280_500_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[34] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361406.Sherpa_CT10_Zmumu_Pt280_500_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[35] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361407.Sherpa_CT10_Zmumu_Pt280_500_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[36] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361408.Sherpa_CT10_Zmumu_Pt500_700_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[37] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361409.Sherpa_CT10_Zmumu_Pt500_700_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[38] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361410.Sherpa_CT10_Zmumu_Pt500_700_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[39] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361411.Sherpa_CT10_Zmumu_Pt700_1000_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[40] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361413.Sherpa_CT10_Zmumu_Pt700_1000_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[41] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361414.Sherpa_CT10_Zmumu_Pt1000_2000_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[42] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361415.Sherpa_CT10_Zmumu_Pt1000_2000_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[43] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361416.Sherpa_CT10_Zmumu_Pt1000_2000_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[44] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361417.Sherpa_CT10_Zmumu_Pt2000_E_CMS_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[45] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361418.Sherpa_CT10_Zmumu_Pt2000_E_CMS_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[46] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361419.Sherpa_CT10_Zmumu_Pt2000_E_CMS_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[47] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361420.Sherpa_CT10_Ztautau_Pt0_70_CVetoBVeto.DAOD_TOPQ1.e3733_s2608_s2183_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[48] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361421.Sherpa_CT10_Ztautau_Pt0_70_CFilterBVeto.DAOD_TOPQ1.e3733_s2608_s2183_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[49] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361422.Sherpa_CT10_Ztautau_Pt0_70_BFilter.DAOD_TOPQ1.e3733_s2608_s2183_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[50] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361423.Sherpa_CT10_Ztautau_Pt70_140_CVetoBVeto.DAOD_TOPQ1.e3733_s2608_s2183_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[51] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361424.Sherpa_CT10_Ztautau_Pt70_140_CFilterBVeto.DAOD_TOPQ1.e3733_s2608_s2183_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[52] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361425.Sherpa_CT10_Ztautau_Pt70_140_BFilter.DAOD_TOPQ1.e3733_s2608_s2183_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[53] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361426.Sherpa_CT10_Ztautau_Pt140_280_CVetoBVeto.DAOD_TOPQ1.e3733_s2608_s2183_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[54] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361427.Sherpa_CT10_Ztautau_Pt140_280_CFilterBVeto.DAOD_TOPQ1.e3733_s2608_s2183_r7267_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[55] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361428.Sherpa_CT10_Ztautau_Pt140_280_BFilter.DAOD_TOPQ1.e3733_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[56] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361429.Sherpa_CT10_Ztautau_Pt280_500_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[57] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361430.Sherpa_CT10_Ztautau_Pt280_500_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[58] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361431.Sherpa_CT10_Ztautau_Pt280_500_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[59] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361432.Sherpa_CT10_Ztautau_Pt500_700_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[60] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361433.Sherpa_CT10_Ztautau_Pt500_700_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[61] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361434.Sherpa_CT10_Ztautau_Pt500_700_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[62] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361435.Sherpa_CT10_Ztautau_Pt700_1000_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[63] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361436.Sherpa_CT10_Ztautau_Pt700_1000_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[64] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361437.Sherpa_CT10_Ztautau_Pt700_1000_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[65] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361438.Sherpa_CT10_Ztautau_Pt1000_2000_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[66] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361439.Sherpa_CT10_Ztautau_Pt1000_2000_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[67] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361440.Sherpa_CT10_Ztautau_Pt1000_2000_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[68] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361441.Sherpa_CT10_Ztautau_Pt2000_E_CMS_CVetoBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[69] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361442.Sherpa_CT10_Ztautau_Pt2000_E_CMS_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[70] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361443.Sherpa_CT10_Ztautau_Pt2000_E_CMS_BFilter.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[71] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361468.Sherpa_CT10_Zee_Mll10to40_Pt0_70_BVeto.DAOD_TOPQ1.e4198_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[72] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361469.Sherpa_CT10_Zee_Mll10to40_Pt0_70_BFilter.DAOD_TOPQ1.e4198_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[73] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361470.Sherpa_CT10_Zee_Mll10to40_Pt70_140_BVeto.DAOD_TOPQ1.e4198_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[74] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361471.Sherpa_CT10_Zee_Mll10to40_Pt70_140_BFilter.DAOD_TOPQ1.e4198_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[75] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361472.Sherpa_CT10_Zee_Mll10to40_Pt140_400_BVeto.DAOD_TOPQ1.e4198_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[76] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361473.Sherpa_CT10_Zee_Mll10to40_Pt140_400_BFilter.DAOD_TOPQ1.e4198_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[77] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361474.Sherpa_CT10_Zee_Mll10to40_Pt400_E_CMS_BVeto.DAOD_TOPQ1.e4198_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[78] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361475.Sherpa_CT10_Zee_Mll10to40_Pt400_E_CMS_BFilter.DAOD_TOPQ1.e4198_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[79] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361476.Sherpa_CT10_Zmumu_Mll10to40_Pt0_70_BVeto.DAOD_TOPQ1.e4198_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[80] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361477.Sherpa_CT10_Zmumu_Mll10to40_Pt0_70_BFilter.DAOD_TOPQ1.e4198_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[81] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361478.Sherpa_CT10_Zmumu_Mll10to40_Pt70_140_BVeto.DAOD_TOPQ1.e4198_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[82] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361479.Sherpa_CT10_Zmumu_Mll10to40_Pt70_140_BFilter.DAOD_TOPQ1.e4198_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[83] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361480.Sherpa_CT10_Zmumu_Mll10to40_Pt140_400_BVeto.DAOD_TOPQ1.e4198_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[84] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361481.Sherpa_CT10_Zmumu_Mll10to40_Pt140_400_BFilter.DAOD_TOPQ1.e4198_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[85] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361482.Sherpa_CT10_Zmumu_Mll10to40_Pt400_E_CMS_BVeto.DAOD_TOPQ1.e4198_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[86] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361483.Sherpa_CT10_Zmumu_Mll10to40_Pt400_E_CMS_BFilter.DAOD_TOPQ1.e4198_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[87] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361484.Sherpa_CT10_Ztautau_Mll10to40_Pt0_70_BVeto.DAOD_TOPQ1.e4198_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[88] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361485.Sherpa_CT10_Ztautau_Mll10to40_Pt0_70_BFilter.DAOD_TOPQ1.e4198_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[89] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361486.Sherpa_CT10_Ztautau_Mll10to40_Pt70_140_BVeto.DAOD_TOPQ1.e4198_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[90] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361487.Sherpa_CT10_Ztautau_Mll10to40_Pt70_140_BFilter.DAOD_TOPQ1.e4198_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[91] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361488.Sherpa_CT10_Ztautau_Mll10to40_Pt140_400_BVeto.DAOD_TOPQ1.e4198_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[92] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361489.Sherpa_CT10_Ztautau_Mll10to40_Pt140_400_BFilter.DAOD_TOPQ1.e4198_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[93] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361490.Sherpa_CT10_Ztautau_Mll10to40_Pt400_E_CMS_BVeto.DAOD_TOPQ1.e4198_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[94] = new TFile(m_name_dir_mcinput+name,"read");
    name = "user.derue.mc15_13TeV.361491.Sherpa_CT10_Ztautau_Mll10to40_Pt400_E_CMS_BFilter.DAOD_TOPQ1.e4198_s2608_s2183_r7326_r6282_p2516.EffiFakeMuon"+m_level+m_trigger+version+".root";
    m_fz[95] = new TFile(m_name_dir_mcinput+name,"read");
    m_numZFiles = 96;

    // read histograms from files
    this->readHists();
    // plot histograms
    this->plotHists();
    
    /*delete m_fdata;
    delete m_fttbar;
    for (int ifile=0;ifile<7;ifile++)  delete m_fst[ifile];
    for (int ifile=0;ifile<6;ifile++)  delete m_fwenu[ifile];
    for (int ifile=0;ifile<5;ifile++)  delete m_fwmunu[ifile];
    for (int ifile=0;ifile<5;ifile++)  delete m_fwtaunu[ifile];
    for (int ifile=0;ifile<13;ifile++) delete m_fwhf[ifile];

    for (int ifile=0;ifile<6;ifile++)  delete m_fzee[ifile];
    for (int ifile=0;ifile<6;ifile++)  delete m_fzmumu[ifile];
    for (int ifile=0;ifile<6;ifile++)  delete m_fztautau[ifile];

    for (int ifile=0;ifile<4;ifile++)  delete m_fzeebb[ifile];
    for (int ifile=0;ifile<4;ifile++)  delete m_fzmumubb[ifile];
    for (int ifile=0;ifile<4;ifile++)  delete m_fztautaubb[ifile];
    for (int ifile=0;ifile<4;ifile++)  delete m_fzeecc[ifile];
    for (int ifile=0;ifile<4;ifile++)  delete m_fzmumucc[ifile];
    for (int ifile=0;ifile<4;ifile++)  delete m_fztautaucc[ifile];

    for (int ifile=0;ifile<16;ifile++) delete m_fdiboson[ifile];
    */    
  }
  
  // =========================================
  void readHists() 
  {
    //float lumi = 3342.58;
    float lumi = 3209.05;
    std::cout << " readHist " << std::endl;

    for (int i = m_min; i<=m_max; i++) {
      m_HistogramNames[i] = GiveHistoName(i);
      std::cout << " i = " << i << " " << GiveHistoName(i) << std::endl;
    }

    // loop on each histo
    for (int var = m_min ; var <=m_max; var++ ) {
      std::string hname = m_HistogramNames[var];
      std::cerr << "Reading histogram " << m_HistogramNames[var] << std::endl;
       
      // read data
      m_hdata[var]  = GetHistogram(var, m_fdata);
      std::cout << " data = " << m_hdata[var] << " " << m_hdata[var]->GetNbinsX() << std::endl;
      
      // ttbar
      m_httbar[var]  = GetHistogram(var, m_fttbar);
      m_httbar[var]->Scale(lumi);  
      std::cout << " httbar = " << m_httbar[var] << " " << m_httbar[var]->GetNbinsX() << std::endl;
      std::cout << "number of singleTop Files:" << m_numTopFiles << std::endl;     
      // single top files
      for (int ifile=0;ifile<m_numTopFiles;ifile++) {
	m_hst[ifile][var]  = GetHistogram(var, m_fst[ifile]);
	m_hst[ifile][var]->Scale(lumi);  
        std::cout << " SingleTop Yield = " << m_hst[ifile][var] << std::endl;
        std::cout << "Files:" << ifile << std::endl; 
      } 
      std::cout << "1" << std::endl; 

     // loop on Z files
      for (int ifile=0;ifile<m_numZFiles;ifile++) {
	m_hz[ifile][var]  = GetHistogram(var, m_fz[ifile]);
	m_hz[ifile][var]->Scale(lumi);  
      }

      std::cout << "2" << std::endl; 
    // loop on W files
      for (int ifile=0;ifile<m_numWFiles;ifile++) {
	m_hw[ifile][var]  = GetHistogram(var, m_fw[ifile]);
	m_hw[ifile][var]->Scale(lumi);  
      }

      std::cout << "3" << std::endl; 
      // loop on diboson files
      for (int ifile=0;ifile<m_numDibosonFiles;ifile++) {
	m_hdiboson[ifile][var]  = GetHistogram(var, m_fdiboson[ifile]);
	m_hdiboson[ifile][var]->Scale(lumi);  
	//std::cout << " hww = " << m_hww[ifile][var] << std::endl;
      }
            
      std::cout << "4" << std::endl; 
    }
  }

  // =============================================
  void plotHists()
  {
    //
    // plot histograms, show data and MC superimposed
    //

    std::string name; 
    
    // loop on variables to plot
    for (int var = m_min; var <= m_max; var++ ) {

      gROOT->Reset();
      gROOT->SetStyle("ATLAS");
      gROOT->ForceStyle();
      gStyle->SetOptStat(0);
      gStyle->SetOptTitle(0);

      /// sum
      m_hsum_all[var] = GetHistogram(var);
      std::cout << " var = " << var << " " << m_hsum_all[var] << " " << m_hsum_all[var]->GetNbinsX() << std::endl;
      
      // ttbar
      //std::cout << " ttbar " << std::endl;
      m_httbar[var]->SetFillColor(kWhite);
      if (m_httbar[var]->GetEntries()>0) m_hsum_all[var]->Add(m_httbar[var]);
      std::cout << " ttbar entries = " << m_httbar[var]->GetSumOfWeights() << std::endl;
      
      // single top
      std::cout << " singletop " << std::endl;
      name = "hst_all_";
      name += GiveVarName(var).c_str();
      std::cout<<name<<std::endl;
      m_hst_all[var] = GetHistogram(var);
      m_hst_all[var]->SetLineColor(62);
      m_hst_all[var]->SetFillColor(62);

      for (int i=0;i<m_numTopFiles;i++) {
	if (m_hst[i][var]->GetEntries()>0) {
	  m_hst_all[var]->Add(m_hst[i][var]);
	  m_hsum_all[var]->Add(m_hst[i][var]);
	}
      }
      std::cout << " single top entries = " << m_hst_all[var]->GetSumOfWeights() << std::endl;
      
      /// W+jets
      std::cout << " W+jets " << std::endl;
      name = "hwjets_all_";
      name += GiveVarName(var).c_str();
      std::cout<<name<<std::endl;
      m_hwjets_all[var] = GetHistogram(var);
      m_hwjets_all[var]->SetFillColor(92);
      m_hwjets_all[var]->SetLineColor(92);

      for (int i=0;i<m_numWFiles;i++) {
	//std::cout << " i = " << i << std::endl;
	if (m_hw[i][var]->GetEntries()>0) {
	  m_hwjets_all[var]->Add(m_hw[i][var]);
	  m_hsum_all[var]->Add(m_hw[i][var]);
	}
      }
      std::cout << " W+j entries = " << m_hwjets_all[var]->GetSumOfWeights() << std::endl;
              
      /// Z+jets
      std::cout << " Z+jets " << std::endl;
      m_hzjets_all[var] = GetHistogram(var);
      m_hzjets_all[var]->SetLineColor(95);
      m_hzjets_all[var]->SetFillColor(95);

      for (int i=0;i<m_numZFiles;i++) {
	//std::cout << " i = " << i << std::endl;
	if (m_hz[i][var]->GetEntries()>0) {
	  m_hzjets_all[var]->Add(m_hz[i][var]);
	  m_hsum_all[var]->Add(m_hz[i][var]);
	}
      }
      std::cout << " Z+j entries = " << m_hzjets_all[var]->GetSumOfWeights() << std::endl;
            
      /// dibosons
      std::cout << " diboson " << std::endl;
      m_hdiboson_all[var] = GetHistogram(var);
      m_hdiboson_all[var]->SetLineColor(5);
      m_hdiboson_all[var]->SetFillColor(5);
      
      for (int i=0;i<m_numDibosonFiles;i++) {
	if (m_hdiboson[i][var]->GetEntries()>0) {
	  m_hdiboson_all[var]->Add(m_hdiboson[i][var]);
	  m_hsum_all[var]->Add(m_hdiboson[i][var]);
	}
      }
      std::cout << " diboson entries = " << m_hdiboson_all[var]->GetSumOfWeights() << std::endl;
            

      /// stack all
      name = "hstack_";
      name += GiveVarName(var).c_str();
      std::cout<<name<<std::endl;
      m_hstack_all[var] = new THStack(name.c_str(),m_httbar[var]->GetTitle());
      m_hstack_all[var]->Add(m_hdiboson_all[var]);
      m_hstack_all[var]->Add(m_hzjets_all[var]);
      m_hstack_all[var]->Add(m_hwjets_all[var]);
      m_hstack_all[var]->Add(m_hst_all[var]);
      m_hstack_all[var]->Add(m_httbar[var]);
      
    }
    
    std::string canvname;
    std::string m_canvNames[100];
    for (int i = m_min; i<m_max; i++) {
      m_canvNames[i] = GiveCanvasName(i);
    }
    
    // loop on variables
    for ( var = m_min; var <= m_max; var++ ) {

      int nbinx = m_hdata[var]->GetNbinsX();
      float mysumdata0toall = 0.;
      float mysumw0toall = 0.;
      float mysumz0toall = 0.;
      float myfracw0toall = 0.;
      float myfracz0toall = 0.;

      float mysumdata0to20 = 0.;
      float mysumw0to20 = 0.;
      float mysumz0to20 = 0.;
      float myfracw0to20 = 0.;
      float myfracz0to20 = 0.;

      float mysumdata0to30 = 0.;
      float mysumw0to30 = 0.;
      float mysumz0to30 = 0.;
      float myfracw0to30 = 0.;
      float myfracz0to30 = 0.;

      float mysumdata0to25 = 0.;
      float mysumw0to25 = 0.;
      float mysumz0to25 = 0.;
      float myfracw0to25 = 0.;
      float myfracz0to25 = 0.;

      float mysumdata0to15 = 0.;
      float mysumw0to15 = 0.;
      float mysumz0to15 = 0.;
      float myfracw0to15 = 0.;
      float myfracz0to15 = 0.;

      float mysumdata5to20 = 0.;
      float mysumw5to20 = 0.;
      float mysumz5to20 = 0.;
      float myfracw5to20 = 0.;
      float myfracz5to20 = 0.;

      float mysumdata20to40 = 0.;
      float mysumw20to40 = 0.;
      float mysumz20to40 = 0.;
      float myfracw20to40 = 0.;
      float myfracz20to40 = 0.;

      float mysumdata0to5 = 0.;
      float mysumw0to5 = 0.;
      float mysumz0to5 = 0.;
      float myfracw0to5 = 0.;
      float myfracz0to5 = 0.;

      float mysumdata0to4 = 0.;
      float mysumw0to4 = 0.;
      float mysumz0to4 = 0.;
      float myfracw0to4 = 0.;
      float myfracz0to4 = 0.;

      float mysumdata0to3 = 0.;
      float mysumw0to3 = 0.;
      float mysumz0to3 = 0.;
      float myfracw0to3 = 0.;
      float myfracz0to3 = 0.;

      float mysumdata0to2 = 0.;
      float mysumw0to2 = 0.;
      float mysumz0to2 = 0.;
      float myfracw0to2 = 0.;
      float myfracz0to2 = 0.;

      float mysumdata0to1 = 0.;
      float mysumw0to1 = 0.;
      float mysumz0to1 = 0.;
      float myfracw0to1 = 0.;
      float myfracz0to1 = 0.;

      float mysumdata20mtw = 0.;
      
      std::cout << " nbinx = " << nbinx << std::endl;
      for (int ii=1;ii<nbinx;ii++) {
	mysumdata0toall += m_hdata[var]->GetBinContent(ii);
	mysumw0toall += m_hwjets_all[var]->GetBinContent(ii);
	mysumz0toall += m_hzjets_all[var]->GetBinContent(ii);

	if (ii<=20) {
	  mysumdata0to20 += m_hdata[var]->GetBinContent(ii);
	  mysumw0to20 += m_hwjets_all[var]->GetBinContent(ii);
	  mysumz0to20 += m_hzjets_all[var]->GetBinContent(ii);
	}
	if (ii<=25) {
	  mysumdata0to25 += m_hdata[var]->GetBinContent(ii);
	  mysumw0to25 += m_hwjets_all[var]->GetBinContent(ii);
	  mysumz0to25 += m_hzjets_all[var]->GetBinContent(ii);
	}
	if (ii<=30) {
	  mysumdata0to30 += m_hdata[var]->GetBinContent(ii);
	  mysumw0to30 += m_hwjets_all[var]->GetBinContent(ii);
	  mysumz0to30 += m_hzjets_all[var]->GetBinContent(ii);
	}
	if (ii<=15) {
	  mysumdata0to15 += m_hdata[var]->GetBinContent(ii);
	  mysumw0to15 += m_hwjets_all[var]->GetBinContent(ii);
	  mysumz0to15 += m_hzjets_all[var]->GetBinContent(ii);
	}
	if (ii>=5 && ii<=20) {
	  mysumdata5to20 += m_hdata[var]->GetBinContent(ii);
	  mysumw5to20 += m_hwjets_all[var]->GetBinContent(ii);
	  mysumz5to20 += m_hzjets_all[var]->GetBinContent(ii);
	}
	if (ii>=20 && ii<=40) {
	  mysumdata20to40 += m_hdata[var]->GetBinContent(ii);
	  mysumw20to40 += m_hwjets_all[var]->GetBinContent(ii);
	  mysumz20to40 += m_hzjets_all[var]->GetBinContent(ii);
	}
	if (ii<=5) {
	  mysumdata0to5 += m_hdata[var]->GetBinContent(ii);
	  mysumw0to5 += m_hwjets_all[var]->GetBinContent(ii);
	  mysumz0to5 += m_hzjets_all[var]->GetBinContent(ii);
	}
	if (ii<=4) {
	  mysumdata0to4 += m_hdata[var]->GetBinContent(ii);
	  mysumw0to4 += m_hwjets_all[var]->GetBinContent(ii);
	  mysumz0to4 += m_hzjets_all[var]->GetBinContent(ii);
	}
	if (ii<=3) {
	  mysumdata0to3 += m_hdata[var]->GetBinContent(ii);
	  mysumw0to3 += m_hwjets_all[var]->GetBinContent(ii);
	  mysumz0to3 += m_hzjets_all[var]->GetBinContent(ii);
	}
	if (ii<=2) {
	  mysumdata0to2 += m_hdata[var]->GetBinContent(ii);
	  mysumw0to2 += m_hwjets_all[var]->GetBinContent(ii);
	  mysumz0to2 += m_hzjets_all[var]->GetBinContent(ii);
	}
	if (ii<=1) {
	  mysumdata0to1 += m_hdata[var]->GetBinContent(ii);
	  mysumw0to1 += m_hwjets_all[var]->GetBinContent(ii);
	  mysumz0to1 += m_hzjets_all[var]->GetBinContent(ii);
	}
	//std::cout << " ii = " << ii << " " << m_hdata[var]->GetBinCenter(ii) << " " << m_hdata[var]->GetBinContent(ii) << std::endl;
      }
      myfracw0toall = 100.*mysumw0toall/mysumdata0toall;
      myfracz0toall = 100.*mysumz0toall/mysumdata0toall;

      myfracw0to20 = 100.*mysumw0to20/mysumdata0to20;
      myfracz0to20 = 100.*mysumz0to20/mysumdata0to20;

      myfracw0to25 = 100.*mysumw0to25/mysumdata0to25;
      myfracz0to25 = 100.*mysumz0to25/mysumdata0to25;

      myfracw0to30 = 100.*mysumw0to30/mysumdata0to30;
      myfracz0to30 = 100.*mysumz0to30/mysumdata0to30;

      myfracw0to15 = 100.*mysumw0to15/mysumdata0to15;
      myfracz0to15 = 100.*mysumz0to15/mysumdata0to15;

      myfracw5to20 = 100.*mysumw5to20/mysumdata5to20;
      myfracz5to20 = 100.*mysumz5to20/mysumdata5to20;

      myfracw20to40 = 100.*mysumw20to40/mysumdata20to40;
      myfracz20to40 = 100.*mysumz20to40/mysumdata20to40;

      myfracw0to5 = 100.*mysumw0to5/mysumdata0to5;
      myfracz0to5 = 100.*mysumz0to5/mysumdata0to5;

      myfracw0to4 = 100.*mysumw0to4/mysumdata0to4;
      myfracz0to4 = 100.*mysumz0to4/mysumdata0to4;

      myfracw0to3 = 100.*mysumw0to3/mysumdata0to3;
      myfracz0to3 = 100.*mysumz0to3/mysumdata0to3;

      myfracw0to2 = 100.*mysumw0to2/mysumdata0to2;
      myfracz0to2 = 100.*mysumz0to2/mysumdata0to2;

      myfracw0to1 = 100.*mysumw0to1/mysumdata0to1;
      myfracz0to1 = 100.*mysumz0to1/mysumdata0to1;

      printf(" mysumdata0toall = %d w=%d z=%d fraction w=%4.2f z=%4.2f\n",
	     mysumdata0toall,mysumw0toall,mysumz0toall,myfracw0toall,myfracz0toall);
      printf(" mysumdata0to20 = %d w=%d z=%d fraction w=%4.2f z=%4.2f\n",
	     mysumdata0to20,mysumw0to20,mysumz0to20,myfracw0to20,myfracz0to20);
      printf(" mysumdata0to25 = %d w=%d z=%d fraction w=%4.2f z=%4.2f\n",
	     mysumdata0to25,mysumw0to25,mysumz0to25,myfracw0to25,myfracz0to25);
      printf(" mysumdata0to30 = %d w=%d z=%d fraction w=%4.2f z=%4.2f\n",
	     mysumdata0to30,mysumw0to30,mysumz0to30,myfracw0to30,myfracz0to30);
      printf(" mysumdata0to15 = %d w=%d z=%d fraction w=%4.2f z=%4.2f\n",
	     mysumdata0to15,mysumw0to15,mysumz0to15,myfracw0to15,myfracz0to15);
      printf(" mysumdata5to20 = %d w=%d z=%d fraction w=%4.2f z=%4.2f\n",
	     mysumdata5to20,mysumw5to20,mysumz5to20,myfracw5to20,myfracz5to20);
      printf(" mysumdata20to40 = %d w=%d z=%d fraction w=%4.2f z=%4.2f\n",
	     mysumdata20to40,mysumw20to40,mysumz20to40,myfracw20to40,myfracz20to40);
      printf(" mysumdata0to5 = %d w=%d z=%d fraction w=%4.2f z=%4.2f\n",
	     mysumdata0to5,mysumw0to5,mysumz0to5,myfracw0to5,myfracz0to5);
      printf(" mysumdata0to4 = %d w=%d z=%d fraction w=%4.2f z=%4.2f\n",
	     mysumdata0to4,mysumw0to4,mysumz0to4,myfracw0to4,myfracz0to4);
      printf(" mysumdata0to3 = %d w=%d z=%d fraction w=%4.2f z=%4.2f\n",
	     mysumdata0to3,mysumw0to3,mysumz0to3,myfracw0to3,myfracz0to3);
      printf(" mysumdata0to2 = %d w=%d z=%d fraction w=%4.2f z=%4.2f\n",
	     mysumdata0to2,mysumw0to2,mysumz0to2,myfracw0to2,myfracz0to2);
      printf(" mysumdata0to1 = %d w=%d z=%d fraction w=%4.2f z=%4.2f\n",
	     mysumdata0to1,mysumw0to1,mysumz0to1,myfracw0to1,myfracz0to1);
      
      canvname = m_canvNames[var];
      m_c[var] = new TCanvas(canvname.c_str(),canvname.c_str(),200,10,800,600);
      //m_c[var] = new TCanvas(canvname.c_str(),canvname.c_str(),200,10,600,600)

      
      int n = m_hsum_all[var]->GetNbinsX();
      float myxmax = 120.;
      if (var==2) myxmax = 20.;
      float myxmax2 = 150.;
      if (var==2) myxmax2 = 25.;
      plotAxis(1,m_hdata[var],m_hsum_all[var],GiveAxisName(var).c_str(),0.,myxmax);
      plot(m_hdata[var],m_hstack_all[var],GiveAxisName(var).c_str(),0.,myxmax2);

      double xmin = 0.75;
      double ymin = 0.54;
      double xmax = 0.9;
      double ymax = 0.79;
      if (var==2) {
	xmin = 0.75;
	ymin = 0.54;
	xmax = 0.9;
	ymax = 0.79;
      }
      double xlabel = 0.2;
      double ylabel = 0.88;
      //if (var==1) { 
      //if (m_pid=="_Loose") xlabel = 0.4; 
      //}
      plotText(var,xlabel, ylabel);
	
      TLegend *leg = new TLegend(xmin,ymin,xmax,ymax,"");
      leg->SetBorderSize(0); 
      leg->SetTextSize(0.045); 
      leg->AddEntry(m_hdata[var],"data","p");
      leg->AddEntry(m_httbar[var],"t#bar{t}","f");
      leg->AddEntry(m_hwjets_all[var],"W+jets","f");
      leg->AddEntry(m_hzjets_all[var],"Z/#gamma+jets","f");
      leg->AddEntry(m_hdiboson_all[var],"Diboson","f");
      leg->AddEntry(m_hst_all[var],"Single top","f");
      leg->SetFillColor(0);      
      leg->Draw("");      
      m_c[var]->RedrawAxis(); 
      

      TString filename = GiveOutputName(var);
      //filename +="";
      m_c[var]->SaveAs(m_figdir+filename+".eps");
      m_c[var]->SaveAs(m_figdir+filename+".pdf");
      m_c[var]->SaveAs(m_figdir+filename+".png");
      
      //delete m_hstack_all[var];
      //delete m_c[var];
    }
  }
  
  // ===================================================================
  void plotText(int var, float xlabel, float ylabel) {
    
    //ATLASLabel(xlabel,ylabel,"Internal");
    ATLASLabel(xlabel,ylabel,"Work in progress");
    //myText(      0.2,0.88,1,"ATLAS Work in progress");
    //myText(xlabel,ylabel-0.05,1,
    //   "Data 2012, #sqrt{s}= 13 TeV, #intLdt=20.28 fb^{-1}");

    if (m_pid=="_Loose") {
      if (m_jet=="_1j") myText(xlabel,ylabel-0.05,1,
			       "Data 2015, #sqrt{s}= 13 TeV, 3.34 fb^{-1}, Loose level, 1 jet");
      if (m_jet=="_2or3j") myText(xlabel,ylabel-0.05,1,
				  "Data 2015, #sqrt{s}= 13 TeV, 3.34 fb^{-1}, Loose level, 2 or 3 jets");
      if (m_jet=="_ge2j") myText(xlabel,ylabel-0.05,1,
				 "Data 2015, #sqrt{s}= 13 TeV, 3.34 fb^{-1}, Loose level, #geq 2 jets");
      if (m_jet=="_ge4j") myText(xlabel,ylabel-0.05,1,
				 "Data 2015, #sqrt{s}= 13 TeV, 3.34 fb^{-1}, Loose level, #geq 4 jets");
    } else {
      if (m_jet=="_1j") myText(xlabel,ylabel-0.05,1,
			       "Data 2015, #sqrt{s}= 13 TeV, 3.34 fb^{-1}, Tight level, 1 jet");
      if (m_jet=="_2or3j") myText(xlabel,ylabel-0.05,1,
				  "Data 2015, #sqrt{s}= 13 TeV, 3.34 fb^{-1}, Tight level, 2 or 3 jets");
      if (m_jet=="_ge2j") myText(xlabel,ylabel-0.05,1,
				 "Data 2015, #sqrt{s}= 13 TeV, 3.34 fb^{-1}, Tight level, #geq 2 jets");
      if (m_jet=="_ge4j") myText(xlabel,ylabel-0.05,1,
				 "Data 2015, #sqrt{s}= 13 TeV, 3.34 fb^{-1}, Tight level, #geq 4 jets");
    }
  }

  // ===================================================================
  bool isDataOver(TH1F* h, THStack *s)//return true if data is greater than MC
  {
    if (h->GetMaximum() > s->GetMaximum()) return true;
    else return false;
  }

  
  // ===================================================================
  float GetMaximum(TH1F* h, TH1F *s)//return true if data is greater than MC
  {
    if (h->GetMaximum() > s->GetMaximum()) return h->GetMaximum();
    else return s->GetMaximum();
  }

  // ===================================================================
  float GetMaximum(TH1F* h, THStack *s)//return true if data is greater than MC
  {
    if (h->GetMaximum() > s->GetMaximum()) return h->GetMaximum();
    else return s->GetMaximum();
  }

  // ================================================
  void plot(TH1F * h, THStack * s, TString title, float min = -9999., float max = -9999.)
  {
    //h->GetXaxis()->SetTitleOffset(0.9);
    h->GetYaxis()->SetTitleOffset(1.5);
    h->GetXaxis()->SetTitle(title);
    h->GetYaxis()->SetTitle("Events");
    h->SetMarkerStyle(20);
    h->SetLineColor(1);
    h->SetLineWidth(2);
    if (m_log) h->SetMinimum(1.);
    h->SetMaximum(h->GetMaximum()*1.4);
    if (m_log) h->GetYaxis()->SetRangeUser(1.,this->GetMaximum(h,s)+0.1*this->GetMaximum(h,s));
    else h->GetYaxis()->SetRangeUser(0.,this->GetMaximum(h,s)+0.1*this->GetMaximum(h,s));
    if (min>-9000 && max >-9000)
    {
      h->GetXaxis()->SetRangeUser(min,max);
    }
    h->Draw("Psame");
    s->Draw("HISTsame");
    h->Draw("Psame");
  }
  
  // ================================================
  void plotH(TH1F *h, TString title, int icolor, int choice) {

    h->GetXaxis()->SetTitle(title);
    //h->GetYaxis()->SetTitle("Events/(2 GeV)");
    h->GetYaxis()->SetTitle("Events/GeV");
     //h->SetMinimum(0.);
    //h->SetMaximum(1.); 
    h->SetLineWidth(2);
    h->SetMarkerStyle(20);
    h->SetLineColor(icolor);
//     if (m_log) h->SetMinimum(0.01);
    if (m_log) h->SetMinimum(1.);
    if (choice==0) h->Draw("HIST");
    if (choice==1) h->Draw("sames,HIST");
    if (choice==2) h->Draw("P");
    if (choice==3) h->Draw("sames,P");
  }

  // ================================================
  void plotH(THStack *h, TString title, int icolor, int choice) 
  {
    if (m_log) h->SetMinimum(1.);
    if (choice==0) h->Draw("sames");
    if (choice==1) h->Draw("sames,HIST");
    if (choice==2) h->Draw("P");
  }

  // ================================================
  void plot(TGraph * gr, TString title, float min = -9999., float max = -9999.)
  {
    gr->SetMarkerStyle(20);
    gr->SetLineColor(1);
    gr->SetLineWidth(2);
    gr->Draw("P");
  }
  
  // ======================================================
  void plotAxis(int choice, TH1F *h, TH1F *s, TString title, 
		float min = -9999., float max = -9999.)
  {    
    Float_t x[2];
    Float_t y[2]; 
    x[0] = s->GetBinCenter(1);
    x[1] = s->GetBinCenter(s->GetNbinsX());
    
    // for 1st pad
    if (choice==1) {
      //if (m_log) h->SetMinimum(1.);
      //h->SetMaximum(h->GetMaximum()*1.4);
      if (m_log) {
	y[0] = 1.;
	y[1] = this->GetMaximum(h,s)+0.1*this->GetMaximum(h,s);
      } else {
	y[0] = 0.;
	y[1] = this->GetMaximum(h,s)+0.1*this->GetMaximum(h,s);
      }
      //y[0] = 0.;
      //y[1] = 1000.;
    }
    // for 2nd pad
    if (choice==2) {
      y[0] = 0.4;
      y[1] = 1.6;
    }
    if (min>-9000 && max >-9000) {
      x[0] = min;
      x[1] = max;
    }

    gr = new TGraph(2,x,y);
    gr->SetFillColor(19);
    gr->SetLineColor(0);
    gr->SetLineWidth(4);
    gr->SetMarkerColor(0);
    gr->SetMarkerStyle(20);
    
    gr->GetXaxis()->SetTitle(title);
    //if (choice==1) gr->GetYaxis()->SetTitle("Events/(2 GeV)");
    if (choice==1) gr->GetYaxis()->SetTitle("Events/GeV");
    if (choice==2) gr->GetYaxis()->SetTitle("data/MC");
    gr->GetXaxis()->SetTitleOffset(0.9);
    gr->GetYaxis()->SetTitleOffset(0.5);

    if (choice==1) {
      gr->GetXaxis()->SetTitleOffset(1.5);
      gr->GetYaxis()->SetTitleOffset(1.5);
      gr->GetXaxis()->SetTitleSize(0.04);
      gr->GetXaxis()->SetLabelSize(0.04);
      gr->GetYaxis()->SetTitleSize(0.04);
      gr->GetYaxis()->SetLabelSize(0.04);
    }
    if (choice==2) {
      gr->GetXaxis()->SetTitleSize(0.09);
      gr->GetXaxis()->SetLabelSize(0.09);
      gr->GetYaxis()->SetTitleSize(0.09);
      gr->GetYaxis()->SetLabelSize(0.09);
    }
    gr->Draw("AP");
  }
  
private:

  TFile *m_fdata, *m_ffakesdata, *m_fttbar, *m_fst[20], *m_fw[100], *m_fwenu[6], *m_fwmunu[6], *m_fwtaunu[6], *m_fwhf[13], *m_fz[100], *m_fzee[6], *m_fzmumu[6], *m_fztautau[6],
    *m_fzeebb[4], *m_fzmumubb[4], *m_fztautaubb[4],
    *m_fzeecc[4], *m_fzmumucc[4], *m_fztautaucc[4],
    *m_fdiboson[20];/// input files

int m_numTopFiles, m_numZFiles, m_numWFiles, m_numDibosonFiles;    

  TFile *m_ffakesdataerrors;/// input files filled with squared errors on fakes estimate
  TFile *m_ffakesdatarup;/// input files for fakes estimate with up fake rate
  TFile *m_ffakesdatafup;/// input files for fakes estimate with up fake rate
  TFile *m_ffakesdatardown;/// input files for fakes estimate with down fake rate
  TFile *m_ffakesdatafdown;/// input files for fakes estimate with down fake rate
  
  TH1F *m_hdata[40], *m_hfakesdata[40], *m_httbar[40], *m_hst[100][40], *m_hw[100][40], *m_hwenu[6][40], *m_hwmunu[6][40], *m_hwtaunu[6][40], *m_hwhf[13][40], *m_hz[100][40], *m_hzee[6][40], *m_hzmumu[6][40], *m_hztautau[6][40], *m_hzeebb[4][40], *m_hzmumubb[4][40], *m_hztautaubb[4][40], *m_hzeecc[4][40], *m_hzmumucc[4][40], *m_hztautaucc[4][40], *m_hdiboson[100][40];/// histos from files

  TH1F *m_hwjets_all[40], *m_hwjetshf_all[40], *m_hzjets_all[40], *m_hzemjets_all[40], *m_hztjets_all[40], *m_hztautau_all[40], *m_hst_all[40], *m_hdiboson_all[40];/// sum of MC from different samples

  THStack *m_hstack_all[100];/// the stack of all MC histos
  TH1F *m_hsum_all[100];/// the sum of all histos with uncertainty from fakes estimate
  TH1F *m_hfakessquarederrors[100];/// the squared uncertainties from fakes estimate
  TH1F *m_hfakesrup[100], *m_hfakesfup[100];/// fakes estimate with up fake rate
  TH1F *m_hfakesrdown[100], *m_hfakesfdown[100];/// fakes estimate with down fake rate
  
  TCanvas* m_c[100];
  
  std::string m_HistogramNames[100];
  
  // ===================================================================
  TH1F * CreateHistVar(std::string namehisto, int var)
  {
    TH1F * htemp;
    htemp = new TH1F(namehisto.c_str(),namehisto.c_str(),500,0.,500.);
    return htemp;
  }
  
  // ===================================================================
  std::string GiveAxisName(int ivar)
  {
    if (ivar==0) return std::string("E_{T}^{miss} [GeV]");
    if (ivar==1) return std::string("m_{T}^{W} [GeV]");
    if (ivar==2) return std::string("E_{T}^{miss}/#sqrt{H_{T}} [GeV^{1/2}]");
  }

  // ===================================================================
  std::string GiveVarName(int ivar)
  {
    if (ivar==0) return std::string("ETmiss");
    if (ivar==1) return std::string("MTW");
    if (ivar==2) return std::string("ETmissOverSqrtHT");
  }
    
  // ===================================================================
  std::string GiveHistoName(int ivar)
  {
    std::string temp = "EffiFakeMuon_";
    temp += GiveVarName(ivar);
    temp += m_pid;
    temp += m_jet;
    return temp;
  }
    
  // ===================================================================
  std::string GiveCanvasName(int ivar)
  {
    std::string temp = "c";
    temp += GiveVarName(ivar);
    temp += m_level;
    temp += m_iso;
    temp += m_jet;
    temp += m_pid;
    if (m_log) temp += "log";
    return temp;
  }
  
  // ===================================================================
  std::string GiveOutputName(int ivar)
  {
    std::string temp;
    temp = GiveVarName(ivar);
    temp += "_";
    temp += m_level;
    temp += "_";
    temp += m_iso;
    temp += m_jet;
    temp += m_pid;
    if (m_log) temp += "log";
    return temp;
  }

  // ===================================================================
  void Style()
  {
    gROOT->Reset();
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
  }
  
  // =========================================================
  TH1F* GetHistogram(int var, TFile * f)
  {
    TH1F * htemp;
    std::string namehisto = m_HistogramNames[var];
    htemp = (TH1F*) f->GetDirectory("HistosEffiFakeMuon")->Get(namehisto.c_str());
    ReBinHisto(var, htemp);
    return htemp;
  }

  // =============================================================
  TH1F* GetHistogram(int var)
  {
    TH1F * htemp;
    std::string namehisto = m_HistogramNames[var];
    htemp = new TH1F(namehisto.c_str(),namehisto.c_str(),1000,0.,1000.);
    ReBinHisto(var, htemp);    
    return htemp;
  }
  
  void ReBinHisto(int var, TH1F* htemp)
  {
    htemp->Rebin(1);
  }
  
};
