#include "TopFakes/TopFakesMMWeightCalculator.h"
#include "TopFakes/TopFakesxAODUtils.h"
#include "TopConfiguration/TopConfig.h"
// #include "TopEvent/Event.h"
#include "TopEvent/EventTools.h"
#include "TopEvent/TopEventMaker.h"
#include "TopFakes/FakesWeights.h"
#include "TopFakes/MMEfficiency.h"
#include "TopFakes/MatrixUtils.h"
#include "TopFakes/MMEffSet.h"
#include "xAODMissingET/MissingETContainer.h"


namespace top{
  
  TopFakesMMWeightCalculator::TopFakesMMWeightCalculator( const std::string& name ) :
    asg::AsgTool( name ),
    m_config(nullptr),
    myWeight_el(nullptr),
    myWeight_mu(nullptr),
    myWeight_ee(nullptr),
    myWeight_em(nullptr),
    myWeight_mm(nullptr),
    m_leptonDefs(fakes::LeptonDefinitions::Standard)
  {
    declareProperty( "config" , m_config );
  }
  
  TopFakesMMWeightCalculator::~TopFakesMMWeightCalculator()
  {
    delete myWeight_el;
    delete myWeight_mu;
    delete myWeight_ee;
    delete myWeight_em;
    delete myWeight_mm;
  }
  
  StatusCode TopFakesMMWeightCalculator::initialize()
  {
    ATH_MSG_INFO(" top::PDFScaleFactorCalculator initialize" );
    
    CheckConfiguration();
    
    if (m_leptonDefs == fakes::LeptonDefinitions::Standard) {
      ///currently this is all deactivated, until efficiencies are available in TopFakes/data
      myWeight_el = new FakesWeights();
      myWeight_el->SetDataPath("$ROOTCOREBIN/data/TopFakes");
//       myWeight_el->SetupWeighterDefault( FakesWeights::EJETS );
      myWeight_el->SetupWeighter( FakesWeights::EJETS, "Leonid15nov:NJ/TR:eta:pt:dR",       "Leonid15nov:NB/NS/TR:eta:jetpt:dPhi" );
      
      myWeight_mu = new FakesWeights();
      myWeight_mu->SetDataPath("$ROOTCOREBIN/data/TopFakes");
//       myWeight_mu->SetupWeighterDefault( FakesWeights::MUJETS );
      myWeight_mu->SetupWeighter( FakesWeights::MUJETS, "Leonid15nov:NJ/TR:eta:pt:dR",       "Leonid15nov:NB/TR:eta:pt:dR:d0sig" );
      
      myWeight_ee = new FakesWeights();
      myWeight_ee->SetDataPath("$ROOTCOREBIN/data/TopFakes");
//       myWeight_ee->SetupWeighterDefault( FakesWeights::EE );
      myWeight_ee->SetupWeighter( FakesWeights::EE, "Leonid15nov:NJ/TR:eta:pt:dR",        "Leonid15nov:NB/NS/TR:eta:jetpt:dR" );
      
      myWeight_em = new FakesWeights();
      myWeight_em->SetDataPath("$ROOTCOREBIN/data/TopFakes");
//       myWeight_em->SetupWeighterDefault( FakesWeights::EMU );
      myWeight_em->SetupWeighter( FakesWeights::EMU,  "Leonid15nov:NJ/TR:eta:pt:dR", "Leonid15nov:NB/NS/TR:eta:jetpt:dR", "Leonid15nov:NJ/TR:eta:pt:dR", "Leonid15nov:NB/TR:eta:pt:dR:d0sig" );
      
      myWeight_mm = new FakesWeights();
      myWeight_mm->SetDataPath("$ROOTCOREBIN/data/TopFakes");
//       myWeight_mm->SetupWeighterDefault( FakesWeights::MUMU );
      myWeight_mm->SetupWeighter( FakesWeights::MUMU, "Leonid15nov:NJ/TR:eta:pt:dR",        "Leonid15nov:NB/TR:eta:pt:dR:d0sig" );
    }
    else {
      std::cout<<"Warning: the used lepton definitions are not yet supported by TopFakes; therefore dummy matrix-method weights will be returned"<<std::endl;
    }
    return StatusCode::SUCCESS;
  }

  
  StatusCode TopFakesMMWeightCalculator::execute()
  {
    const xAOD::EventInfo* event_info(nullptr);
    top::check(evtStore()->retrieve(event_info, m_config->sgKeyEventInfo()), "Failed to retrieve EventInfo");
    
    const xAOD::ElectronContainer* electrons(nullptr);
    const xAOD::MuonContainer* muons(nullptr);
    const xAOD::JetContainer* jets(nullptr);
    const xAOD::MissingETContainer* METContainer(nullptr);
    top::check(evtStore()->retrieve(electrons, m_config->sgKeyElectrons(m_config->nominalHashValue())), "Failed to retrieve electrons");
    top::check(evtStore()->retrieve(muons, m_config->sgKeyMuons(m_config->nominalHashValue())), "Failed to retrieve muons");
    top::check(evtStore()->retrieve(jets, m_config->sgKeyJets(m_config->nominalHashValue(),false)), "failed to retrieve jets");
    top::check(evtStore()->retrieve(METContainer, m_config->sgKeyMissingEtLoose(m_config->nominalHashValue())), "Failed to retrieve MET");
    const xAOD::MissingET* MET = (*METContainer)[MissingETBase::Source::total()];
    
    //initialise mmweight to 0.
    float mmweight = 0.;
    
    if (event_info->eventType(xAOD::EventInfo::IS_SIMULATION)) {//assign weight = 0 for MC events
      mmweight = 0.;
    }
    else {
      if (m_leptonDefs != fakes::LeptonDefinitions::Standard) {//package yet support only standard definitions
	mmweight = -999.;
      }
      else {///currently a dummy weight 123456. is set, until efficiencies are available in TopFakes/data
	int channel = top::fakes::GetChannel(*electrons, *muons);
	if (channel==FakesWeights::EJETS) {
// 	  mmweight = getMMweightE(*MET, *electrons, *jets);
	  mmweight = 123456.;
	}
	else if (channel==FakesWeights::MUJETS) {
// 	  mmweight = getMMweightM(*MET, *muons, *jets);
	  mmweight = 123456.;
	}
	else if (channel==FakesWeights::EE) {
// 	  mmweight = getMMweightEE(*MET, *electrons, *jets);
	  mmweight = 123456.;
	}
	else if (channel==FakesWeights::MUMU) {
// 	  mmweight = getMMweightMM(*MET, *muons, *jets);
	  mmweight = 123456.;
	}
	else if (channel==FakesWeights::EMU) {
// 	  mmweight = getMMweightEM(*MET, *electrons, *muons, *jets);
	  mmweight = 123456.;
	}
	else {//for unsupported channels give dummy value
	  mmweight = -999.;
	}
      }
    }
    event_info->auxdecor<float>("MMWeight") = mmweight;
    return StatusCode::SUCCESS;
  }
  
  float TopFakesMMWeightCalculator::getMMweightE(const xAOD::MissingET& met, const xAOD::ElectronContainer& els, const xAOD::JetContainer jets) {
    //
    // Compute weight for e+jets channel
    //
    float mmWeightE = 0;
    
    std::vector<unsigned int> good_els_index = fakes::GetGoodHighPtLeptons(els);
    
    auto el = els[good_els_index.at(0)];
    MMLepton *lept = getLeptonMMInfo(*el, jets, met);
    MMEvent  *evt  = getEventMMInfo(jets, met);
    
    if (lept==0 || evt==0) {
      mmWeightE = 0.;
    }
    else {
      myWeight_el->SetLepton(*evt,*lept);
      mmWeightE = myWeight_el->GetFakesWeightLJets(el->auxdataConst<char>("passPreORSelection"));
    }
  
    delete lept;
    delete evt;
  
//     std::cout<<"  mmWeightE="<<mmWeightE<<std::endl;
    return mmWeightE;
  }
  
  float TopFakesMMWeightCalculator::getMMweightM(const xAOD::MissingET& met, const xAOD::MuonContainer& mus, const xAOD::JetContainer jets) {
    //
    // Compute weight for m+jets channel
    //
    float mmWeightM = 0;
    
    std::vector<unsigned int> good_mus_index = fakes::GetGoodHighPtLeptons(mus);
    
    auto mu = mus[good_mus_index.at(0)];
    MMLepton *lept = getLeptonMMInfo(*mu, jets, met);
    MMEvent  *evt  = getEventMMInfo(jets, met);
  
    if (lept==0 || evt==0) {
      mmWeightM = 0.;
    }
    else {
      myWeight_mu->SetLepton(*evt,*lept);
      mmWeightM = myWeight_mu->GetFakesWeightLJets(mu->auxdataConst<char>("passPreORSelection"));
    }
  
    delete lept;
    delete evt;
  
//     std::cout<<"  mmWeightM="<<mmWeightM<<std::endl;
    return mmWeightM;
  }
  
  float TopFakesMMWeightCalculator::getMMweightEE(const xAOD::MissingET& met, const xAOD::ElectronContainer& els, const xAOD::JetContainer jets) {
    //
    // Compute weight for ee channel
    //
    float mmWeightEE = 0;
    
    std::vector<unsigned int> good_els_index = fakes::GetGoodHighPtLeptons(els);
    
    auto el1 = els[good_els_index.at(0)];
    auto el2 = els[good_els_index.at(1)];
    MMLepton *lept_e1 = getLeptonMMInfo(*el1, jets, met);
    MMLepton *lept_e2 = getLeptonMMInfo(*el2, jets, met);
    MMEvent  *evt  = getEventMMInfo(jets, met);
    
    if (lept_e1==0 || lept_e2==0 || evt==0) {
      mmWeightEE = 0.;
    }
    else {
      myWeight_ee->SetLeptons(*evt,*lept_e1,*lept_e2);
      mmWeightEE = myWeight_ee->GetFakesWeightDilep(el1->auxdataConst<char>("passPreORSelection"),el2->auxdataConst<char>("passPreORSelection"));
    }
    
    delete lept_e1;
    delete lept_e2;
    delete evt;
    
//     std::cout<<"  mmWeightEE="<<mmWeightEE<<std::endl;
    return mmWeightEE;
  }
  
  float TopFakesMMWeightCalculator::getMMweightMM(const xAOD::MissingET& met, const xAOD::MuonContainer& mus, const xAOD::JetContainer jets) {
    //
    // Compute weight for mm channel
    //
    float mmWeightMM = 0;
    
    std::vector<unsigned int> good_mus_index = fakes::GetGoodHighPtLeptons(mus);
    
    auto mu1 = mus[good_mus_index.at(0)];
    auto mu2 = mus[good_mus_index.at(1)];
    MMLepton *lept_m1 = getLeptonMMInfo(*mu1, jets, met);
    MMLepton *lept_m2 = getLeptonMMInfo(*mu2, jets, met);
    MMEvent  *evt  = getEventMMInfo(jets, met);
    
    if (lept_m1==0 || lept_m2==0 || evt==0) {
      mmWeightMM = 0.;
    }
    else {
      myWeight_mm->SetLeptons(*evt,*lept_m1,*lept_m2);
      mmWeightMM = myWeight_mm->GetFakesWeightDilep(mu1->auxdataConst<char>("passPreORSelection"),mu2->auxdataConst<char>("passPreORSelection"));
    }
    
    delete lept_m1;
    delete lept_m2;
    delete evt;
    
//     std::cout<<"  mmWeightMM="<<mmWeightMM<<std::endl;
    return mmWeightMM;
  }
  
  float TopFakesMMWeightCalculator::getMMweightEM(const xAOD::MissingET& met, const xAOD::ElectronContainer& els, const xAOD::MuonContainer& mus, const xAOD::JetContainer jets) {
    //
    // Compute weight for em channel
    //
    float mmWeightEM = 0;
    
    std::vector<unsigned int> good_els_index = fakes::GetGoodHighPtLeptons(els);
    std::vector<unsigned int> good_mus_index = fakes::GetGoodHighPtLeptons(mus);
    
    auto el = els[good_els_index.at(0)];
    auto mu = mus[good_mus_index.at(0)];
    MMLepton *lept_e = getLeptonMMInfo(*el, jets, met);
    MMLepton *lept_m = getLeptonMMInfo(*mu, jets, met);
    MMEvent  *evt  = getEventMMInfo(jets, met);
    
    if (lept_e==0 || lept_m==0 || evt==0) {
      mmWeightEM = 0.;
    }
    else {
      myWeight_em->SetLeptons(*evt,*lept_e,*lept_m);
      mmWeightEM = myWeight_mm->GetFakesWeightDilep(el->auxdataConst<char>("passPreORSelection"),mu->auxdataConst<char>("passPreORSelection"));
    }
    
    delete lept_e;
    delete lept_m;
    delete evt;
    
//     std::cout<<"  mmWeightEM="<<mmWeightEM<<std::endl;
    return mmWeightEM;
  }
  
  MMLepton* TopFakesMMWeightCalculator::getLeptonMMInfo(const xAOD::Electron& el, const xAOD::JetContainer& jets, const xAOD::MissingET& met)
  {
    float eta_cl = el.caloCluster()->etaBE(2);
//     float eta = el.eta();
//     float phi = el.phi();
    float pt  = el.pt()/1.e3; // tool needs GeV
    int trigger = 0.;
    top::fakes::GetTrigMatchVariable(el, trigger);

    const xAOD::TrackParticle* eltrack = el.trackParticle();
    float d0 = eltrack->d0();
    const xAOD::ParametersCovMatrix_t elcov = eltrack->definingParametersCovMatrix();
    float d0signif = d0/sqrt(elcov(0,0));
    
    float dR;
    float pTj;
    float dRpt;
    float dRCentral;
    float pTjCentral;
    float dRptCentral;
    fakes::GetClosestJet (el, jets, dR, pTj, dRpt, dRCentral, pTjCentral, dRptCentral);
    
    float dphilmet;
    fakes::GetdPhiLepMET (el, met, dphilmet);
  
    MMLepton* lept = new MMLepton();
    lept->pt      = pt;
    lept->eta     = std::fabs(eta_cl);
    lept->dR      = dR;
    lept->dRpt    = dRpt;
    lept->dPhi    = dphilmet;
    lept->trigger = trigger;
    lept->d0sig  = d0signif;
//     std::cout<<"Electron";
//     std::cout<<" pt="<<pt;
//     std::cout<<" eta="<<std::fabs(eta_cl);
//     std::cout<<" dR="<<dR;
//     std::cout<<" dRpt="<<dRpt;
//     std::cout<<" dPhi="<<dphilmet;
//     std::cout<<" trigger="<<trigger;
//     std::cout<<" d0sig="<<d0signif;
//     std::cout<<std::endl;
  
    return lept;
  }
  
  MMLepton* TopFakesMMWeightCalculator::getLeptonMMInfo(const xAOD::Muon& mu, const xAOD::JetContainer& jets, const xAOD::MissingET& met)
  {
    float eta = mu.eta();
//     float phi = mu.phi();
    float pt  = mu.pt()/1.e3; // tool needs GeV
    int trigger = 0.;
    top::fakes::GetTrigMatchVariable(mu, trigger);

    const xAOD::TrackParticle* mutrack = mu.primaryTrackParticle();
    float d0 = mutrack->d0();
    const xAOD::ParametersCovMatrix_t mucov=mutrack->definingParametersCovMatrix();
    float d0signif = d0/sqrt(mucov(0,0));
    
    float dR;
    float pTj;
    float dRpt;
    float dRCentral;
    float pTjCentral;
    float dRptCentral;
    fakes::GetClosestJet (mu, jets, dR, pTj, dRpt, dRCentral, pTjCentral, dRptCentral);
    
    float dphilmet;
    fakes::GetdPhiLepMET (mu, met, dphilmet);
  
    MMLepton* lept = new MMLepton();
    lept->pt      = pt;
    lept->eta     = std::fabs(eta);
    lept->dR      = dR;
    lept->dRpt    = dRpt;
    lept->dPhi    = dphilmet;
    lept->trigger = trigger;
    lept->d0sig  = d0signif;
//     std::cout<<"Muon";
//     std::cout<<" pt="<<pt;
//     std::cout<<" eta="<<std::fabs(eta);
//     std::cout<<" dR="<<dR;
//     std::cout<<" dRpt="<<dRpt;
//     std::cout<<" dPhi="<<dphilmet;
//     std::cout<<" trigger="<<trigger;
//     std::cout<<" d0sig="<<d0signif;
//     std::cout<<std::endl;
  
    return lept;
  }
  
  MMEvent* TopFakesMMWeightCalculator::getEventMMInfo(const xAOD::JetContainer& jets, const xAOD::MissingET& met)
  {
    float leadingJetpT = -999.;
    float leadingCentralJetpT = -999.;
    unsigned int Njets = 0;
    unsigned int NCentraljets = 0;
    unsigned int nbtag = 0;
    for (const auto* const jetPtr : jets) {
      if (jetPtr->pt()<25000.) continue;
      Njets++;
      if (jetPtr->pt()>leadingJetpT) leadingJetpT = jetPtr->pt();
      if (jetPtr->eta()<2.5) {
	NCentraljets++;
	if (jetPtr->pt()>leadingCentralJetpT) leadingCentralJetpT = jetPtr->pt()/1000.;
      }
      double mvx = -999.;
      jetPtr->btagging()->MVx_discriminant("MV2c20", mvx);
      if (mvx>std::stof(m_config->bTagWP_77())) {
	nbtag++;
      }
    }
  
    MMEvent* evnt = new MMEvent();
    evnt->njets = NCentraljets;
    evnt->ntag = nbtag;
    evnt->jetpt = leadingCentralJetpT;
    evnt->sumet = met.sumet()/1e3;//tool needs GeV
//     std::cout<<"Event";
//     std::cout<<" njets="<<NCentraljets;
//     std::cout<<" ntag="<<nbtag;
//     std::cout<<" jetpt="<<leadingCentralJetpT;
//     std::cout<<" sumet="<<met.sumet()/1e3;//tool needs GeV
//     std::cout<<" met="<<met.met()/1e3;//tool needs GeV
//     std::cout<<" metx="<<met.mpx()/1e3;//tool needs GeV
//     std::cout<<" mety="<<met.mpy()/1e3;//tool needs GeV
//     std::cout<<" metphi="<<met.phi();
//     std::cout<<std::endl;
  
    return evnt;
  }
  
  ///This function checks if the lepton ID, isolation, etc... match one of those supported by Top-Fakes
  ///Currently only the "standard" definition is supported
  ///The list of definitions could be expanded in TopFakesxAODUtils (the top::fakes::LeptonDefinitions enum class)
  ///The function also checks the pT range of the leptons - this allows users to have leptons with pT<25GeV (they are ignored) - and the eta range of the jets - this allows users to have forward jets  (they are ignored too)
  void TopFakesMMWeightCalculator::CheckConfiguration()
  {
    if (m_config == nullptr) {
      m_leptonDefs = fakes::LeptonDefinitions::Other;
      std::cout<<"Warning: TopFakesMMWeightCalculator::CheckLeptonDefs() was unable to assess the configuration; therefore dummy matrix-method weights will be returned"<<std::endl;
    }
      else {
	if (  m_config->electronID() == "TightLH"
		&& m_config->electronIDLoose() == "MediumLH"
		&& m_config->electronIsolation() == "Gradient"
		&& m_config->electronIsolationLoose() == "None"
		&& m_config->muonQuality() == "Medium"
		&& m_config->muonQualityLoose() == "Loose"
		&& m_config->muonIsolation() == "Gradient"
		&& m_config->muonIsolationLoose() == "None" ) {
	  m_leptonDefs = fakes::LeptonDefinitions::Standard;
	  //now do checks on object definitions
	  //electrons
	  if (m_config->electronPtcut() < 25000.) {
	    std::cout<<"Warning: electrons below pT=25GeV are used (pT cut is at "<<m_config->electronPtcut()/1000.<<"GeV). This is non-standard and not yet supported by TopFakes; therefore all electrons below this threshold will be ignored in the calculation of matrix-method weights."<<std::endl;
	  }
	  else if (m_config->electronPtcut() != 25000.) {
	    std::cout<<"Warning: non-standard electron pT cut of "<<m_config->electronPtcut()/1000.<<"GeV is used (standard is 25GeV). It may have unexpected behaviour for the calculation of matrix-method weights."<<std::endl;
	  }
	  if (!m_config->electronVetoLArCrack()) {
	    std::cout<<"Warning: veto of electrons on LAr crack was disabled; this is non-standard and not yet supported by TopFakes"<<std::endl;
	  }
	  
	  //muons
	  if (m_config->muonPtcut() < 25000.) {
	    std::cout<<"Warning: muons below pT=25GeV are used (pT cut is at "<<m_config->muonPtcut()/1000.<<"GeV). This is non-standard and not yet supported by TopFakes; therefore all muons below this threshold will be ignored in the calculation of matrix-method weights."<<std::endl;
	  }
	  else if (m_config->muonPtcut() != 25000.) {
	    std::cout<<"Warning: non-standard muon pT cut of "<<m_config->muonPtcut()/1000.<<"GeV is used (standard is 25GeV). It may have unexpected behaviour for the calculation of matrix-method weights."<<std::endl;
	  }
	  if (m_config->muonEtacut() != 2.5) {
	    std::cout<<"Warning: non-standard muon eta cut of "<<m_config->jetEtacut()<<" is used (standard is 2.5). It may have unexpected behaviour for the calculation of matrix-method weights."<<std::endl;
	  }
	  
	  //jets
	  if (m_config->jetEtacut() > 2.5) {
	    std::cout<<"Warning: forward jets are used (eta cut is at "<<m_config->jetEtacut()<<"). This is non-standard and not yet supported by TopFakes; therefore all jets above |eta|=2.5 will be ignored in the calculation of matrix-method weights."<<std::endl;
	  }
	  else if (m_config->jetEtacut() != 2.5) {
	    std::cout<<"Warning: non-standard jet eta cut of "<<m_config->jetEtacut()<<" is used (standard is 2.5). It may have unexpected behaviour for the calculation of matrix-method weights."<<std::endl;
	  }
	  if (m_config->jetPtcut() != 25000.) {
	    std::cout<<"Warning: non-standard jet pT cut of "<<m_config->jetPtcut()/1000.<<"GeV is used (standard is 25GeV). It may have unexpected behaviour for the calculation of matrix-method weights."<<std::endl;
	  }
	}
	else {
	  std::cout<<"Warning: the used lepton definitions are not yet supported by TopFakes; therefore dummy matrix-method weights will be returned"<<std::endl;
	}
	
	
    }
    
  }
}
