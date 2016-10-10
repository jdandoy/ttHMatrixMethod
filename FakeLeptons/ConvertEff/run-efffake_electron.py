#!/usr/bin/env python

import getopt
import os
import sys
import glob
import math
import time
from array import array
import ROOT
from ROOT import *


system=os.system
currentDir = os.getcwd()

F_out = ROOT.TFile.Open("F_el_Nedaa2016.root", "RECREATE")
#F_out = ROOT.TFile.Open("F_el_Fred_v2341.root", "RECREATE")
#F_out = ROOT.TFile.Open("F_el_Fred_WZMG_v2341.root", "RECREATE")
#F_out = ROOT.TFile.Open("F_el_Fred_WZMG_v2341.root", "RECREATE")
#F_out = ROOT.TFile.Open("F_el_Fred_CRfake_v2341.root", "RECREATE")
#F_out = ROOT.TFile.Open("F_el_Fred_MCup_v2341.root", "RECREATE")
#F_out = ROOT.TFile.Open("F_el_Fred_MCdown_v2341.root", "RECREATE")

# F_el_Fred.root (default) -> eff-FakeElec-CorrMC_lowETmissMTW
# F_el_Fred_MCup.root      -> eff-FakeElec-CorrMCUp_lowETmissMTW
# F_el_Fred_MCdown.root    -> eff-FakeElec-CorrMCDown_lowETmissMTW
# F_el_Fred_CRfake.root    -> eff-FakeElec-CorrMC_lowETmiss20_

# name of the input variables
vars = ["Av", "Et", "Eta", "dR", "PtLeadingJet", "dPhi", "MET", "MTW", "Njet", "Nbjet"]
#vars = ["Eta"]
# name of the output variables
ovars = ["av", "pt", "eta", "dR", "jetpt", "dPhi", "met", "mtw", "njet", "nbtag"]
#ovars = ["eta"]

#fakes
allbins   = [0,1000]
etbins    = [25,30,35,40,45,50,55,60,80,150]
etabins   = [0,0.1,0.6,0.8,1.15,1.37,1.52,1.81,2.01,2.37,2.47]
drbins    = [0.4,0.6,0.8,1.0,1.5,2.0,6.0]
ptjetbins = [25,50,75,100,150,500]
dphibins  = [0.,0.1,0.2,0.3,0.4,0.5,0.75,1.0,1.25,1.5,1.75,2.0,2.5,3.2]
metbins   = [0.,10.0,20.,30.0,40.,60.,100.,150.,200.,1000.]
mtwbins   = [0.,10.0,20.,30.0,40.,60.,100.,150.,200.,1000.]
njetbins  = [0.,1.,2.,3.,4.,5.]
nbjetbins = [0.,1.0,2.0,3.0]

btags = ["pretag", "nobtag", "btag"]
obtag = ["", "_0b", "_ge1b"]
#btags = ["pretag"]
#obtag = [""]

jets = ["ge1j", "1j", "ge2j", "2or3j", "ge4j"]
ojets = ["", "_1j", "_ge2j", "_2or3j", "_ge4j"]
#jets = ["ge1j"]
#ojets = [""]

trigger = ["", "HLT_e24_lhmedium_L1EM20VH", "HLT_e24_lhtight_nod0_ivarloose", "HLT_e60_lhmedium_nod0", "HLT_e140_lhloose_nod0"]
otrigger = ["", "_HLT_e24_lhmedium_L1EM20VH", "_HLT_e24_lhtight_nod0_ivarloose", "_HLT_e60_lhmedium_nod0", "_HLT_e140_lhloose_nod0"]
#trigger = ["", "HLT_e24_lhmedium_iloose_L1EM20VH", "HLT_e24_lhmedium_L1EM20VH", "HLT_e60_lhmedium", "HLT_e120_lhloose"]
#otrigger = ["", "e24i", "e24", "e60", "e120"]
#otrigger = ["", "trig0", "trig1", "trig2"]
#trigger = [""]
#otrigger = [""]

version = ".2412-fakesStd-1a"

bc = 0
for b in btags:
    jc = 0
    for j in jets:
        tc = 0
        for t in trigger:
            vc = 0
            for v in vars:
                print v
                if v == "Av":
                    eff = ROOT.TH1F("eff", "eff",1,array('d',allbins))
                elif v == "Eta":
                    eff = ROOT.TH1F("eff", "eff",10,array('d',etabins))
                elif v == "Et":
                    eff = ROOT.TH1F("eff", "eff",9,array('d',etbins))
                elif v == "dR":
                    eff = ROOT.TH1F("eff", "eff",6,array('d',drbins))
                elif v == "PtLeadingJet":
                    eff = ROOT.TH1F("eff", "eff", 5, array('d',ptjetbins))
                elif v == "dPhi":
                    eff = ROOT.TH1F("eff", "eff", 13, array('d',dphibins))
                elif v == "MET":
                    eff = ROOT.TH1F("eff", "eff", 9, array('d',metbins))
                elif v == "MTW":
                    eff = ROOT.TH1F("eff", "eff", 9, array('d',mtwbins))
                elif v == "Njet":
                    eff = ROOT.TH1F("eff", "eff", 5, array('d',njetbins))
                elif v == "Nbjet":
                    eff = ROOT.TH1F("eff", "eff", 3, array('d',nbjetbins))
                    
                il = "../eff-2341/eff-FakeElec-CorrMC_WZSherpa_lowETmissMTW_"+b+"_"+j+version+"_vs"+v+".txt"
                ol = obtag[bc]+ojets[jc]+otrigger[tc]

                print il
                print ol
                lines = [line.rstrip() for line in open(il,'r')]
                lc = 0
                for l in lines:
                    lc = lc+1
                    vl = l.split()                
                    if v == "Av":
                        eff.SetBinContent(lc,float(vl[0])/100)
                        err = float(vl[1])/100
                        print lc,vl[0],vl[1]
                    else:
                        eff.SetBinContent(lc,float(vl[2])/100)
                        err = float(vl[3])/100
                        print lc,vl[2],vl[3]
                    eff.SetBinError(lc,err)
            
                #save
                F_out.cd()
                oname = "eff_"+ovars[vc]+ol
                eff.SetName(oname)
                eff.Write(oname)
                vc = vc+1
            tc = tc+1
        jc = jc+1
    bc = bc+1
