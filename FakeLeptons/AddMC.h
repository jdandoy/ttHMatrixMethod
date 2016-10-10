#ifndef __ADDMC_H
#define __ADDMC_H

std::vector<TString> AddMC(int imc);
		
std::vector<TString> m_names;

void AddMC_TTbar();
void AddMC_SingleTop();
void AddMC_Diboson();

// add W/Z from Powheg+Pythia8+EvtGen
void AddMC_WjPythia8EvtGen(); 
void AddMC_ZjPythia8EvtGen(); 

// add W/Z from Sherpa
void AddMC_WenujSherpa(); 
void AddMC_WmunujSherpa(); 
void AddMC_WtaunujSherpa(); 

void AddMC_ZeeMgt40Sherpa();
void AddMC_ZmumuMgt40Sherpa();
void AddMC_ZtautauMgt40Sherpa();
void AddMC_ZeeMlt40Sherpa();
void AddMC_ZmumuMlt40Sherpa();
void AddMC_ZtautauMlt40Sherpa();

bool m_isTOPQ1;
TString m_derivation;
TString m_tag;

#endif // __ADDMC_H
