#include <string>
#include <iostream>

#include "TCanvas.h"
#include "TFile.h"
#include "TH1F.h"

#include "Root/MMeff.cxx"

// NB: run it from outside utils/ directory:
//   root -l -b -q utils/GetEff.C+

const int MAXvar = 20;

void GetEff(string ch="el",string sel="ge2j_trig0",bool isReal=false,string opt="r"){
  MMeff *myMMeff = new MMeff();
  
  bool useRebinning = false;
  bool useSmoothing = false;
  bool mergeOverflow = false;
  if(opt.find("r")!=string::npos) useRebinning = true;
  if(opt.find("s")!=string::npos) useSmoothing = true;
  if(opt.find("o")!=string::npos) mergeOverflow = true;
  
  float lumi = 84.9676;
  
  //string path = "/gpfs/atlas/public/ttH_ntup2015/flatNtup_AT_L2";
  string path = "/gpfs/atlas/public/ttH_ntup2015/flatNtup_AT_L2";
  
  int nVar = 8;
  string var[]     = {"av",
                     "eta","pt","jetpt",
                     "dPhi","dR",
                     "njet","nbtag"};
                     
  string varName[] = {"nev",
                     "lep_eta","lep_pt","jet_pt",
                     "dPhi_lnu","dR_ljmin",
                     "jet_n","nJet_tagged"};
                     
  string xtitle[]  = {"Average",
                     "|#eta^{lep}|","p_{T}^{lep} [GeV]","p_{T}^{jet1} [GeV]",
                     "#Delta#phi(lep,E_{T}^{miss})","min #Delta R(lep,jet)",
                     "Number of jets","Number of b-tags"};
                     
  int rebin[]   = {0,
                     1,1,1,
                     1,1,
                     0,0};
                     
  int smooth[]   = {0,
                     1,1,1,
                     1,1,
                     0,0};
  
  string selLoose = path+"/";
  if(ch=="el") selLoose += "ejets_";
  if(ch=="mu") selLoose += "mujets_";
  selLoose += sel;

  string selTight = path+"/";
  if(ch=="el") selTight += "ejets_";
  if(ch=="mu") selTight += "mujets_";
  selTight += "tight_";
  selTight += sel;
  
  string name;
  if(isReal){
    for(int i_var=0;i_var<nVar;i_var++){
      name = sel+"_"+var[i_var];
      // from high ;ET / MTW regions in Data
//       TH1F* h_loose = (TH1F*)HistFromFile(selLoose+"_CRreal/data_histo.root/"+varName[i_var]); h_loose->SetName(Form("h_loose_%s",var[i_var].c_str()));
//       TH1F* h_tight = (TH1F*)HistFromFile(selTight+"_CRreal/data_histo.root/"+varName[i_var]); h_tight->SetName(Form("h_tight_%s",var[i_var].c_str()));
//       myMMeff->SetDataHisto( name, h_loose, h_tight);
      // From MC only, as data has too small stat...
      TH1F* h_loose = (TH1F*)HistFromFile(selLoose+"_CRreal/wjets_histo.root/"+varName[i_var]); h_loose->SetName(Form("h_loose_%s",var[i_var].c_str()));
      TH1F* h_tight = (TH1F*)HistFromFile(selTight+"_CRreal/wjets_histo.root/"+varName[i_var]); h_tight->SetName(Form("h_tight_%s",var[i_var].c_str()));
      h_loose->Add((TH1F*)HistFromFile(selLoose+"_CRreal/ttbar_histo.root/"+varName[i_var]));
      h_tight->Add((TH1F*)HistFromFile(selTight+"_CRreal/ttbar_histo.root/"+varName[i_var]));
      myMMeff->SetDataHisto( name, h_loose, h_tight);
    }
  }
  else{
    for(int i_var=0;i_var<nVar;i_var++){
      name = sel+"_"+var[i_var];
      myMMeff->SetDataHisto( name, (TH1F*)HistFromFile(selLoose+"_CRfake/data_histo.root/"+varName[i_var]),(TH1F*)HistFromFile(selTight+"_CRfake/data_histo.root/"+varName[i_var]) );
      myMMeff->AddMCHisto(   name, (TH1F*)HistFromFile(selLoose+"_CRfake/ttbar_histo.root/"+varName[i_var]),(TH1F*)HistFromFile(selTight+"_CRfake/ttbar_histo.root/"+varName[i_var]), lumi );
      myMMeff->AddMCHisto(   name, (TH1F*)HistFromFile(selLoose+"_CRfake/wjets_histo.root/"+varName[i_var]),(TH1F*)HistFromFile(selTight+"_CRfake/wjets_histo.root/"+varName[i_var]), lumi );
      myMMeff->AddMCHisto(   name, (TH1F*)HistFromFile(selLoose+"_CRfake/zjets_histo.root/"+varName[i_var]),(TH1F*)HistFromFile(selTight+"_CRfake/zjets_histo.root/"+varName[i_var]), lumi );
      myMMeff->AddMCHisto(   name, (TH1F*)HistFromFile(selLoose+"_CRfake/singleTop_histo.root/"+varName[i_var]),(TH1F*)HistFromFile(selTight+"_CRfake/singleTop_histo.root/"+varName[i_var]), lumi );
    }
  }
  
  // Overflow
  if(mergeOverflow){
    for(int i_var=0;i_var<nVar;i_var++){
      name = sel+"_"+var[i_var];
      myMMeff->MergeUnderOverFlowBins(name);
    }
  }
  
  myMMeff->Evaluate();
  
  // Rebin
  if(useRebinning){
    for(int i_var=0;i_var<nVar;i_var++){
      name = sel+"_"+var[i_var];
      if(rebin[i_var]>0) myMMeff->Rebin(name);
    }
  }
  myMMeff->Evaluate();

  // Smooth
  if(useSmoothing){
    for(int i_var=0;i_var<nVar;i_var++){
      name = sel+"_"+var[i_var];
      if(smooth[i_var]>0) myMMeff->Smooth(name);
    }
  }
  
  // Draw and save in a ROOT file
  TCanvas *c = new TCanvas("c","c",600,600);
  gSystem->Exec("mkdir plots");
  TFile *f_eff;
  if(!isReal) f_eff = new TFile(("data/F_"+ch+"_Default.root").c_str(),"UPDATE");
  else        f_eff = new TFile(("data/R_"+ch+"_Default.root").c_str(),"UPDATE");
  TH1F* h_eff[MAXvar];
  for(int i_var=0;i_var<nVar;i_var++){
    h_eff[i_var] = (TH1F*)myMMeff->GetEffHisto(sel+"_"+var[i_var]);
    h_eff[i_var]->Draw("E");
    if(!isReal) h_eff[i_var]->GetYaxis()->SetTitle("#varepsilon_{fake}");
    else        h_eff[i_var]->GetYaxis()->SetTitle("#varepsilon_{real}");
    h_eff[i_var]->GetXaxis()->SetTitle(xtitle[i_var].c_str());
    h_eff[i_var]->SetMinimum(0.);
    h_eff[i_var]->SetMaximum(1.);
    h_eff[i_var]->Draw("E");
    if(!isReal) c->SaveAs(("plots/FakeEff_"+ch+"_"+sel+"_"+var[i_var]+".png").c_str());
    if(isReal)  c->SaveAs(("plots/RealEff_"+ch+"_"+sel+"_"+var[i_var]+".png").c_str());
    f_eff->cd();
    if(sel=="ge1j"){
      h_eff[i_var]->Write(("eff_"+var[i_var]).c_str(),TObject::kOverwrite);
    }
    else            h_eff[i_var]->Write(("eff_"+var[i_var]+"_"+sel).c_str(),TObject::kOverwrite);
  }
}
