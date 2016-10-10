#include "TopFakes/TopFakesxAODUtils.h"

#include "TopEvent/EventTools.h"
#include "TopFakes/FakesWeights.h"

void top::fakes::GetClosestJet (const xAOD::Electron& el, const xAOD::JetContainer& jets,
			    float& dRClosetJet, float& PtClosetJet, float& dROverPtClosetJet,
			    float& dRClosetCentralJet, float& PtClosetCentralJet, float& dROverPtClosetCentralJet)
{
  //the dRs are initialised to a very high positive value
  dRClosetJet = 999.;
  dRClosetCentralJet = 999.;
  //the pTs are initialised to a negative value
  PtClosetJet = -999.;
  PtClosetCentralJet = -999.;
  dROverPtClosetJet = -999.;
  dROverPtClosetCentralJet = -999.;
  for (const auto* const jetPtr : jets) {
    if (jetPtr->pt()<25000.) continue;
    double newdR = top::deltaR(*jetPtr,el);
    if (jetPtr->eta()<2.5) {
      if (newdR<dRClosetCentralJet) {
	dRClosetCentralJet = newdR;
	PtClosetCentralJet = jetPtr->pt()/1000.; // tool needs GeV
      }
    }
    if (newdR<dRClosetJet) {
      dRClosetJet = newdR;
      PtClosetJet = jetPtr->pt()/1000.; // tool needs GeV
    }
  }
  if ((dRClosetJet!=999.) && (PtClosetJet!=-999.)) dROverPtClosetJet = dRClosetJet/PtClosetJet;
  if ((dRClosetCentralJet!=999.) && (PtClosetCentralJet!=-999.)) dROverPtClosetCentralJet = dRClosetCentralJet/PtClosetCentralJet;
  
  //if the dRs are at their default value, give them a negative value
  if (dRClosetJet == 999.) dRClosetJet = -999.;
  if (dRClosetCentralJet == 999.) dRClosetCentralJet = -999.;
}

void top::fakes::GetClosestJet (const xAOD::Muon& mu, const xAOD::JetContainer& jets,
			    float& dRClosetJet, float& PtClosetJet, float& dROverPtClosetJet,
			    float& dRClosetCentralJet, float& PtClosetCentralJet, float& dROverPtClosetCentralJet)
{
  //the dRs are initialised to a very high positive value
  dRClosetJet = 999.;
  dRClosetCentralJet = 999.;
  //the pTs are initialised to a negative value
  PtClosetJet = -999.;
  PtClosetCentralJet = -999.;
  dROverPtClosetJet = -999.;
  dROverPtClosetCentralJet = -999.;
  for (const auto* const jetPtr : jets) {
    if (jetPtr->pt()<25000.) continue;
    double newdR = top::deltaR(*jetPtr,mu);
    double newdRCentral = newdR;
    if (jetPtr->eta()<2.5) {
      if (newdRCentral<dRClosetCentralJet) {
	dRClosetCentralJet = newdRCentral;
	PtClosetCentralJet = jetPtr->pt()/1000.; // tool needs GeV
      }
    }
    if (newdR<dRClosetJet) {
      dRClosetJet = newdR;
      PtClosetJet = jetPtr->pt()/1000.; // tool needs GeV
    }
  }
  if ((dRClosetJet!=999.) && (PtClosetJet!=-999.)) dROverPtClosetJet = dRClosetJet/PtClosetJet;
  if ((dRClosetCentralJet!=999.) && (PtClosetCentralJet!=-999.)) dROverPtClosetCentralJet = dRClosetCentralJet/PtClosetCentralJet;
  
  //if the dRs are at their default value, give them a negative value
  if (dRClosetJet == 999.) dRClosetJet = -999.;
  if (dRClosetCentralJet == 999.) dRClosetCentralJet = -999.;
}

void top::fakes::GetdPhiLepMET (const xAOD::Electron& el, const xAOD::MissingET& met, float& dPhi)
{
  dPhi = -999.;
  if (met.mpx()!=0. && met.mpx()!=0.) {
    TLorentzVector met_4vect;
    met_4vect.SetPxPyPzE(met.mpx(),met.mpx(),0.,0.);
    dPhi = el.p4().DeltaPhi(met_4vect);
  }
}

void top::fakes::GetdPhiLepMET (const xAOD::Muon& mu, const xAOD::MissingET& met, float& dPhi)
{
  dPhi = -999.;
  if (met.mpx()!=0. && met.mpx()!=0.) {
    TLorentzVector met_4vect;
    met_4vect.SetPxPyPzE(met.mpx(),met.mpx(),0.,0.);
    dPhi = mu.p4().DeltaPhi(met_4vect);
  }
}

void top::fakes::GetTrigMatchVariable(const xAOD::Electron& el, int& trigmatch)
{
  trigmatch = 0;
  bool trig_lowpTIso = el.auxdataConst<char>("TRIGMATCH_HLT_e24_lhmedium_iloose_L1EM20VH");
  bool trig_hightpTNoIso = el.auxdataConst<char>("TRIGMATCH_HLT_e60_lhmedium");
  bool trig_veryhightpTNoIso = el.auxdataConst<char>("TRIGMATCH_HLT_e120_lhloose");
  bool trig_lowpTNoIso = ( el.auxdataConst<char>("TRIGMATCH_HLT_e24_lhmedium_L1EM18VH") || el.auxdataConst<char>("TRIGMATCH_HLT_e24_lhmedium_L1EM20VH") );
  
  if (trig_lowpTIso)                              trigmatch |= 0x1 << 0;
  if (trig_hightpTNoIso || trig_veryhightpTNoIso) trigmatch |= 0x1 << 1;
  
//   if (trig_lowpTNoIso)         trigmatch |= 0x1 << 0;
//   if (trig_lowpTIso)           trigmatch |= 0x1 << 1;
//   if (trig_hightpTNoIso)       trigmatch |= 0x1 << 2;
//   if (trig_veryhightpTNoIso)   trigmatch |= 0x1 << 3;
}

void top::fakes::GetTrigMatchVariable(const xAOD::Muon& mu, int& trigmatch)
{
  trigmatch = 0;
  bool trig_lowpTIso = mu.auxdataConst<char>("TRIGMATCH_HLT_mu20_iloose_L1MU15");
  bool trig_hightpTNoIso = mu.auxdataConst<char>("TRIGMATCH_HLT_mu50");
  bool trig_lowpTNoIso = mu.auxdataConst<char>("TRIGMATCH_HLT_mu20_L1MU15");
  
  if (trig_lowpTIso)     trigmatch |= 0x1 << 0;
  if (trig_hightpTNoIso) trigmatch |= 0x1 << 1;
  
//   if (trig_lowpTNoIso)         trigmatch |= 0x1 << 0;
//   if (trig_lowpTIso)           trigmatch |= 0x1 << 1;
//   if (trig_hightpTNoIso)       trigmatch |= 0x1 << 2;
}

std::vector<unsigned int> top::fakes::GetGoodHighPtLeptons(const xAOD::ElectronContainer& els)
{
  unsigned int i(0);
  std::vector<unsigned int> good_els_index;
  for (const auto* const elPtr : els) {//loop on electrons
    if ( elPtr->isAvailable<char>("passPreORSelectionLoose") )  {//count only leptons wigth pT>25GeV that pass selection
      if ( elPtr->pt()> 25000. && (elPtr->auxdataConst<char>("passPreORSelectionLoose") == 1) ) good_els_index.push_back(i);
    }
    i++;
  }//loop on electrons
  return good_els_index;
}

std::vector<unsigned int> top::fakes::GetGoodHighPtLeptons(const xAOD::MuonContainer& mus)
{
  unsigned int i(0);
  std::vector<unsigned int> good_mus_index;
  for (const auto* const muPtr : mus) {//loop on muons
    if ( muPtr->isAvailable<char>("passPreORSelectionLoose") )  {//count only leptons wigth pT>25GeV that pass selection
      if ( muPtr->pt()> 25000. && (muPtr->auxdataConst<char>("passPreORSelectionLoose") == 1) ) good_mus_index.push_back(i);
    }
    i++;
  }//loop on muons
  return good_mus_index;
}

int top::fakes::GetChannel(const xAOD::ElectronContainer& els, const xAOD::MuonContainer& mus)
{
  unsigned int iels = GetGoodHighPtLeptons(els).size();
  unsigned int imus = GetGoodHighPtLeptons(mus).size();
  if (iels==1 && imus==0) return FakesWeights::EJETS;
  else if (iels==0 && imus==1) return FakesWeights::MUJETS;
  else if (iels==2 && imus==0) return FakesWeights::EE;
  else if (iels==0 && imus==2) return FakesWeights::MUMU;
  else if (iels==1 && imus==1) return FakesWeights::EMU;
  else return -1;
}
