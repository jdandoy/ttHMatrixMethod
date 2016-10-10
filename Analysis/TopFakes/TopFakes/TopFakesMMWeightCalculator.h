// $Id: TopFakesMMWeightCalculator.h 695678 2015-09-18 16:07:50Z tpelzer $
#ifndef TOPFAKESMMWEIGHTCALCULATOR_H
#define TOPFAKESMMWEIGHTCALCULATOR_H

/**
  * @author Timothée Theveneaux-Pelzer <tpelzer@cern.ch>
  * 
  * @brief TopFakesMMWeightCalculator
  *   Calculate Matrix-Method Weights for fake prompt lepton background estimates
  **/

// Framework include(s):
#include "AsgTools/AsgTool.h"
#include "AsgTools/ToolHandle.h"

// For Object containers
#include "TopEvent/Event.h"

// Classes from fakesWeight framework
class FakesWeights;
class MMLepton;
class MMEvent;

// Forward declaration(s):
namespace top{
  class TopConfig;
  class Event;
  namespace fakes {
    enum class LeptonDefinitions;
  }
}

namespace top{

  class TopFakesMMWeightCalculator final : public asg::AsgTool {
    public:
      explicit TopFakesMMWeightCalculator( const std::string& name );
      virtual ~TopFakesMMWeightCalculator();

      // Delete Standard constructors
      TopFakesMMWeightCalculator(const TopFakesMMWeightCalculator& rhs) = delete;
      TopFakesMMWeightCalculator(TopFakesMMWeightCalculator&& rhs) = delete;
      TopFakesMMWeightCalculator& operator=(const TopFakesMMWeightCalculator& rhs) = delete;

      StatusCode initialize();
      StatusCode execute();

    private:
      std::shared_ptr<top::TopConfig> m_config;
      
      FakesWeights *myWeight_el;
      FakesWeights *myWeight_mu;
      FakesWeights *myWeight_ee;
      FakesWeights *myWeight_em;
      FakesWeights *myWeight_mm;
      
      float getMMweightE(const xAOD::MissingET& met, const xAOD::ElectronContainer& els, const xAOD::JetContainer jets);
      float getMMweightM(const xAOD::MissingET& met, const xAOD::MuonContainer& mus, const xAOD::JetContainer jets);
      float getMMweightEE(const xAOD::MissingET& met, const xAOD::ElectronContainer& els, const xAOD::JetContainer jets);
      float getMMweightMM(const xAOD::MissingET& met, const xAOD::MuonContainer& mus, const xAOD::JetContainer jets);
      float getMMweightEM(const xAOD::MissingET& met, const xAOD::ElectronContainer& els, const xAOD::MuonContainer& mus, const xAOD::JetContainer jets);
      
      MMLepton* getLeptonMMInfo(const xAOD::Electron& el, const xAOD::JetContainer& jets, const xAOD::MissingET& met);
      MMLepton* getLeptonMMInfo(const xAOD::Muon& mu, const xAOD::JetContainer& jets, const xAOD::MissingET& met);
      MMEvent*  getEventMMInfo( const xAOD::JetContainer& jets, const xAOD::MissingET& met);
      
      fakes::LeptonDefinitions m_leptonDefs;
      void CheckConfiguration();
      
      ///-- Tell RootCore to build a dictionary (we need this) --///
      ClassDef(top::TopFakesMMWeightCalculator, 0);

  };
} // namespace
#endif
