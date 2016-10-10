{
gROOT->ProcessLine("#include <vector>");
gROOT->ProcessLine("#include <string>");

// Event Structure
gROOT->LoadMacro("EventStruct/Tree_Nominal.C+");
gROOT->LoadMacro("EventStruct/Tree_Nominal_Loose.C+");

// Utils
gROOT->LoadMacro("Utils/Utils.C+");
gROOT->LoadMacro("Utils/MCDataSetUtils.C+");

// MatrixUtils
//gROOT->LoadMacro("FakesMacros/Root/MatrixUtils.C+");
//gROOT->LoadMacro("FakesMacros/Root/MMEfficiency.C+");
//gROOT->LoadMacro("FakesMacros/Root/MMEffSet.C+");
//gROOT->LoadMacro("FakesMacros/Root/FakesWeights.C+");

// MatrixUtils
gROOT->LoadMacro("TopFakes/Root/MatrixUtils.C+");
gROOT->LoadMacro("TopFakes/Root/MMEfficiency.C+");
gROOT->LoadMacro("TopFakes/Root/MMEffSet.C+");
gROOT->LoadMacro("TopFakes/Root/FakesWeights.C+");

// FakeElec
gROOT->LoadMacro("doEffiFakeElec/HistoManagerEffiFakeElec.C+");
gROOT->LoadMacro("doEffiFakeElec/EffiFakeElec.C+");

// FakeMuon
gROOT->LoadMacro("doEffiFakeMuon/HistoManagerEffiFakeMuon.C+");
gROOT->LoadMacro("doEffiFakeMuon/EffiFakeMuon.C+");

// T&P for electrons
gROOT->LoadMacro("doEffiRealElecTP/HistoManagerEffiRealElecTP.C+");
gROOT->LoadMacro("doEffiRealElecTP/EffiRealElecTP.C+");

// T&P for muons
gROOT->LoadMacro("doEffiRealMuonTP/HistoManagerEffiRealMuonTP.C+");
gROOT->LoadMacro("doEffiRealMuonTP/EffiRealMuonTP.C+");

// SemiLeptonic
gROOT->LoadMacro("doSemiLeptonic/HistoManagerSemiLeptonic.C+");
gROOT->LoadMacro("doSemiLeptonic/SemiLeptonic.C+");

// FakeSemiLeptonic
gROOT->LoadMacro("doFakeSemiLeptonic/HistoManagerFakeSemiLeptonic.C+");
gROOT->LoadMacro("doFakeSemiLeptonic/FakeSemiLeptonic.C+");

// main methods
gROOT->LoadMacro("doAna/MyEffiFakeElec.C+");
gROOT->LoadMacro("doAna/MyEffiFakeMuon.C+");
gROOT->LoadMacro("doAna/MyEffiRealElecTP.C+");
gROOT->LoadMacro("doAna/MyEffiRealMuonTP.C+");
gROOT->LoadMacro("doAna/MySemiLeptonic.C+");
gROOT->LoadMacro("doAna/MyFakeSemiLeptonic.C+");

}
