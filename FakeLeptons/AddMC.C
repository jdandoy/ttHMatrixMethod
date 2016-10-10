#include "AddMC.h"

// =============================================
std::vector<TString> AddMC(int imc) 
{
  std::cout << " AddMC " << imc << std::endl;
  m_names.clear();

  //m_isTOPQ1 = isTOPQ1;
  m_derivation = "";
  m_tag = "";
  m_derivation = "TOPQ1";
  m_tag = "p2516";
  /*if (m_isTOPQ1) {
    m_derivation = "TOPQ1";
    m_tag = "p2516";
  } else {
    m_derivation = "EXOT4";
    m_tag = "p2425";
  }*/

  AddMC_TTbar();
  AddMC_SingleTop();
  AddMC_Diboson();
  // add W/Z from Powheg+Pythia8+EvtGen
  if (imc==0) {
    AddMC_WjPythia8EvtGen(); 
    AddMC_ZjPythia8EvtGen(); 
  }
  // add W/Z from Sherpa
  if (imc==1) {
    // W+jets
    AddMC_WenujSherpa(); 
    AddMC_WmunujSherpa(); 
    AddMC_WtaunujSherpa(); 
    // Z+jets
    AddMC_ZeeMgt40Sherpa();
    AddMC_ZmumuMgt40Sherpa();
    AddMC_ZtautauMgt40Sherpa();
    // low mll
    //if (isTOPQ1) {
      AddMC_ZeeMlt40Sherpa();
      AddMC_ZmumuMlt40Sherpa();
      AddMC_ZtautauMlt40Sherpa();
    //}
  }
  
  return m_names;
}

// =============================================
void AddMC_TTbar() 
{
  TString name = "";
    
  name = "user.derue.410000.PowhegPythiaEvtGen.DAOD_TOPQ1.e3698_s2608_s2183_r7725_r7676_p2669";
  //user.derue.410000.PowhegPythiaEvtGen.DAOD_TOPQ1.e3698_s2608_s2183_r7725_r7676_p2669.EffiFakeElec_lowETmissMTW_btag.2412-fakesStd-1a_output.root
  m_names.push_back(name);
}

// =============================================
void AddMC_SingleTop() 
{
  TString name = "";
  
  /// single top
  name = "user.derue.410011.PowhegPythiaEvtGen.DAOD_TOPQ1.e3824_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.410012.PowhegPythiaEvtGen.DAOD_TOPQ1.e3824_s2608_s2183_r7725_r7676_p2669"; 
  m_names.push_back(name);
  name = "user.derue.410013.PowhegPythiaEvtGen.DAOD_TOPQ1.e3753_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.410014.PowhegPythiaEvtGen.DAOD_TOPQ1.e3753_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.410015.PowhegPythiaEvtGen.DAOD_TOPQ1.e3753_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.410016.PowhegPythiaEvtGen.DAOD_TOPQ1.e3753_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.410025.PowhegPythiaEvtGen.DAOD_TOPQ1.e3998_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.410026.PowhegPythiaEvtGen.DAOD_TOPQ1.e3998_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
}

// =============================================
void AddMC_Diboson() 
{
  TString name = "";
  
  name = "user.derue.361063.Sherpa_CT10_llll.DAOD_TOPQ1.e3836_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361064.Sherpa.DAOD_TOPQ1.e3836_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361065.Sherpa.DAOD_TOPQ1.e3836_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361066.Sherpa.DAOD_TOPQ1.e3836_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361067.Sherpa.DAOD_TOPQ1.e3836_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361068.Sherpa_CT10_llvv.DAOD_TOPQ1.e3836_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361069.Sherpa.DAOD_TOPQ1.e3836_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361070.Sherpa.DAOD_TOPQ1.e3836_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361071.Sherpa.DAOD_TOPQ1.e3836_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361072.Sherpa.DAOD_TOPQ1.e3836_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361073.Sherpa_CT10_ggllll.DAOD_TOPQ1.e3836_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361074.Sherpa.DAOD_TOPQ1.e4047_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361075.Sherpa.DAOD_TOPQ1.e3911_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361076.Sherpa.DAOD_TOPQ1.e3911_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361077.Sherpa_CT10_ggllvv.DAOD_TOPQ1.e4641_s2726_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361078.Sherpa.DAOD_TOPQ1.e4641_s2726_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361079.Sherpa.DAOD_TOPQ1.e3911_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361080.Sherpa.DAOD_TOPQ1.e3911_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361088.Sherpa_CT10_lvvv.DAOD_TOPQ1.e4483_s2726_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361089.Sherpa_CT10_vvvv.DAOD_TOPQ1.e4483_s2726_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361090.Sherpa.DAOD_TOPQ1.e4555_s2726_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361091.Sherpa.DAOD_TOPQ1.e4607_s2726_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361092.Sherpa.DAOD_TOPQ1.e4607_s2726_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361093.Sherpa.DAOD_TOPQ1.e4607_s2726_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361094.Sherpa.DAOD_TOPQ1.e4607_s2726_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361095.Sherpa.DAOD_TOPQ1.e4607_s2726_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361096.Sherpa.DAOD_TOPQ1.e4607_s2726_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361097.Sherpa.DAOD_TOPQ1.e4607_s2726_r7772_r7676_p2669";
  m_names.push_back(name);
}

// =============================================
void AddMC_WjPythia8EvtGen() 
{
  TString name = "";
  
  name = "user.nasbah.361100.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusenu.merge.DAOD_"+m_derivation+".e3601_s2576_s2132_r6765_r6282_"+m_tag;
  m_names.push_back(name);
  name = "user.nasbah.361101.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusmunu.merge.DAOD_"+m_derivation+".e3601_s2576_s2132_r6725_r6282_"+m_tag;
  m_names.push_back(name);
  name = "user.nasbah.361102.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplustaunu.merge.DAOD_"+m_derivation+".e3601_s2576_s2132_r6725_r6282_"+m_tag;
  m_names.push_back(name);
  name = "user.nasbah.361103.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminusenu.merge.DAOD_"+m_derivation+".e3601_s2576_s2132_r6765_r6282_"+m_tag;
  m_names.push_back(name);
  name = "user.nasbah.361104.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminusmunu.merge.DAOD_"+m_derivation+".e3601_s2576_s2132_r6725_r6282_"+m_tag;
  m_names.push_back(name);
  name = "user.nasbah.361105.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminustaunu.merge.DAOD_"+m_derivation+".e3601_s2576_s2132_r6725_r6282_"+m_tag;
  m_names.push_back(name);
}

// =============================================
void AddMC_ZjPythia8EvtGen() 
{
  TString name = "";
  
  name = "user.nasbah.361106.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Zee.merge.DAOD_"+m_derivation+".e3601_s2576_s2132_r6765_r6282_"+m_tag;
  m_names.push_back(name);
  name = "user.nasbah.361107.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Zmumu.merge.DAOD_"+m_derivation+".e3601_s2576_s2132_r6765_r6282_"+m_tag;
  m_names.push_back(name);
  name = "user.nasbah.361108.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Ztautau.merge.DAOD_"+m_derivation+".e3601_s2576_s2132_r6765_r6282_"+m_tag;
  m_names.push_back(name);
}

// =============================================
void AddMC_WenujSherpa() 
{
  TString name = "";
  
  // running on Wenu+jets MC
  name = "user.derue.361300.Sherpa.DAOD_TOPQ1.e3651_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361301.Sherpa.DAOD_TOPQ1.e3651_s2586_s2174_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361302.Sherpa.DAOD_TOPQ1.e3651_s2586_s2174_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361303.Sherpa.DAOD_TOPQ1.e3651_s2586_s2174_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361304.Sherpa.DAOD_TOPQ1.e3651_s2586_s2174_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361305.Sherpa.DAOD_TOPQ1.e3651_s2586_s2174_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361306.Sherpa.DAOD_TOPQ1.e3651_s2586_s2174_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361307.Sherpa.DAOD_TOPQ1.e3651_s2586_s2174_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361308.Sherpa.DAOD_TOPQ1.e3651_s2586_s2174_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361309.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
    m_names.push_back(name);
    name = "user.derue.361310.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
    m_names.push_back(name);
    name = "user.derue.361311.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
    m_names.push_back(name);
    name = "user.derue.361312.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
    m_names.push_back(name);
    name = "user.derue.361313.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
    m_names.push_back(name);
    name = "user.derue.361314.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
    m_names.push_back(name);
    name = "user.derue.361315.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
    m_names.push_back(name);
    name = "user.derue.361316.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
    m_names.push_back(name);
    name = "user.derue.361317.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
    m_names.push_back(name);
    name = "user.derue.361318.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
    m_names.push_back(name);
    name = "user.derue.361319.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
    m_names.push_back(name);
    name = "user.derue.361320.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
    m_names.push_back(name);
    name = "user.derue.361321.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
    m_names.push_back(name);
    name = "user.derue.361322.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
    m_names.push_back(name);
    name = "user.derue.361323.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
    m_names.push_back(name);
}

// =============================================
void AddMC_WmunujSherpa() 
{
  TString name = "";

  // running on Wmunu+jets MC
  name = "user.derue.361324.Sherpa.DAOD_TOPQ1.e3651_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361325.Sherpa.DAOD_TOPQ1.e3651_s2586_s2174_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361326.Sherpa.DAOD_TOPQ1.e3651_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361327.Sherpa.DAOD_TOPQ1.e3651_s2586_s2174_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361328.Sherpa.DAOD_TOPQ1.e3651_s2586_s2174_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361329.Sherpa.DAOD_TOPQ1.e3651_s2586_s2174_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361330.Sherpa.DAOD_TOPQ1.e3651_s2586_s2174_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361331.Sherpa.DAOD_TOPQ1.e3651_s2586_s2174_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361332.Sherpa.DAOD_TOPQ1.e3651_s2586_s2174_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361333.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361334.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361335.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361336.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361337.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361338.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361339.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361340.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361341.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361342.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361343.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361344.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361345.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361346.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361347.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
}
  
// =============================================
void AddMC_WtaunujSherpa() 
{
  TString name = "";
  
  // running on Wtaunu+jets MC
  name = "user.derue.361348.Sherpa.DAOD_TOPQ1.e3733_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361349.Sherpa.DAOD_TOPQ1.e3733_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361350.Sherpa.DAOD_TOPQ1.e3733_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361351.Sherpa.DAOD_TOPQ1.e3733_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361352.Sherpa.DAOD_TOPQ1.e3733_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361353.Sherpa.DAOD_TOPQ1.e3733_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361354.Sherpa.DAOD_TOPQ1.e3733_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361355.Sherpa.DAOD_TOPQ1.e3733_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361356.Sherpa.DAOD_TOPQ1.e3733_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361357.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361358.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361359.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361360.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361361.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361362.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361363.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361364.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361365.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361366.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361367.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361368.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361369.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361370.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361371.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7725_r7676_p2669";
  m_names.push_back(name);
}

// =============================================
void AddMC_ZeeMgt40Sherpa() 
{
  TString name = "";

  // if running on Zee+jets Mll>40 GeV MC
  name = "user.derue.361372.Sherpa.DAOD_TOPQ1.e3651_s2586_s2174_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361373.Sherpa.DAOD_TOPQ1.e3651_s2586_s2174_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361374.Sherpa.DAOD_TOPQ1.e3651_s2586_s2174_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361375.Sherpa.DAOD_TOPQ1.e3651_s2586_s2174_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361376.Sherpa.DAOD_TOPQ1.e3651_s2586_s2174_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361377.Sherpa.DAOD_TOPQ1.e3651_s2586_s2174_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361378.Sherpa.DAOD_TOPQ1.e3651_s2586_s2174_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361379.Sherpa.DAOD_TOPQ1.e3651_s2586_s2174_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361380.Sherpa.DAOD_TOPQ1.e3651_s2586_s2174_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361381.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361382.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361383.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361384.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361385.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361386.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361387.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361388.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361389.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361390.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361391.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361392.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361393.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361394.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361395.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
}

// =============================================
void AddMC_ZmumuMgt40Sherpa() 
{
  TString name = "";
  // if running on Zmumu+jets Mll>40 GeV MC

  name = "user.derue.361396.Sherpa.DAOD_TOPQ1.e3651_s2586_s2174_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361397.Sherpa.DAOD_TOPQ1.e3651_s2586_s2174_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361398.Sherpa.DAOD_TOPQ1.e3651_s2586_s2174_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361399.Sherpa.DAOD_TOPQ1.e3651_s2586_s2174_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361400.Sherpa.DAOD_TOPQ1.e3651_s2586_s2174_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361401.Sherpa.DAOD_TOPQ1.e3651_s2586_s2174_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361402.Sherpa.DAOD_TOPQ1.e3651_s2586_s2174_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361403.Sherpa.DAOD_TOPQ1.e3651_s2586_s2174_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361404.Sherpa.DAOD_TOPQ1.e3651_s2586_s2174_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361405.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361406.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361407.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361408.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361409.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361410.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361411.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361412.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361413.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361414.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361415.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361416.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361417.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361418.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361419.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
}

// =============================================
void AddMC_ZtautauMgt40Sherpa() 
{
  TString name = "";
  // if running on Ztautau+jets Mll>40 GeV MC

  name = "user.derue.361420.Sherpa.DAOD_TOPQ1.e3733_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361420.Sherpa.DAOD_TOPQ1.e3733_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361421.Sherpa.DAOD_TOPQ1.e3733_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361422.Sherpa.DAOD_TOPQ1.e3733_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361423.Sherpa.DAOD_TOPQ1.e3733_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361424.Sherpa.DAOD_TOPQ1.e3733_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361425.Sherpa.DAOD_TOPQ1.e3733_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361426.Sherpa.DAOD_TOPQ1.e3733_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361427.Sherpa.DAOD_TOPQ1.e3733_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361428.Sherpa.DAOD_TOPQ1.e3733_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361429.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361430.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361431.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361432.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361433.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361434.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361435.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361436.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361437.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361438.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361439.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361440.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361441.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361442.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361443.Sherpa.DAOD_TOPQ1.e4133_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
}

// =============================================
void AddMC_ZeeMlt40Sherpa() 
{
  TString name = "";
  
  // if running on Zee+jets 10GeV<Mll<40GeV MC
 
  name = "user.derue.361468.Sherpa.DAOD_TOPQ1.e4198_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361469.Sherpa.DAOD_TOPQ1.e4198_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361470.Sherpa.DAOD_TOPQ1.e4198_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361471.Sherpa.DAOD_TOPQ1.e4198_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361472.Sherpa.DAOD_TOPQ1.e4198_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361473.Sherpa.DAOD_TOPQ1.e4198_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361474.Sherpa.DAOD_TOPQ1.e4198_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361475.Sherpa.DAOD_TOPQ1.e4198_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
}

// =============================================
void AddMC_ZmumuMlt40Sherpa() 
{
  TString name = "";
  // if running on Zmumu+jets 10GeV<Mll<40GeV MC
 
  name = "user.derue.361476.Sherpa.DAOD_TOPQ1.e4198_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361477.Sherpa.DAOD_TOPQ1.e4198_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361478.Sherpa.DAOD_TOPQ1.e4198_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361479.Sherpa.DAOD_TOPQ1.e4198_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361480.Sherpa.DAOD_TOPQ1.e4198_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361481.Sherpa.DAOD_TOPQ1.e4198_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361482.Sherpa.DAOD_TOPQ1.e4198_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361483.Sherpa.DAOD_TOPQ1.e4198_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
}

// =============================================
void AddMC_ZtautauMlt40Sherpa() 
{
  TString name = "";
  // if running on Ztautau+jets 10GeV<Mll<40GeV MC
  
  name = "user.derue.361484.Sherpa.DAOD_TOPQ1.e4198_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361485.Sherpa.DAOD_TOPQ1.e4198_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361486.Sherpa.DAOD_TOPQ1.e4198_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361487.Sherpa.DAOD_TOPQ1.e4198_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361488.Sherpa.DAOD_TOPQ1.e4198_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361489.Sherpa.DAOD_TOPQ1.e4198_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361490.Sherpa.DAOD_TOPQ1.e4198_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
  name = "user.derue.361491.Sherpa.DAOD_TOPQ1.e4198_s2608_s2183_r7772_r7676_p2669";
  m_names.push_back(name);
}
