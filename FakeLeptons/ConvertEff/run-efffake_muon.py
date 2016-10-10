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

F_out = ROOT.TFile.Open("F_mu_Nedaa2016.root", "RECREATE")
#F_out = ROOT.TFile.Open("F_mu_Fred_Iso6_new.root", "RECREATE")
#F_out = ROOT.TFile.Open("F_mu_Fred_CRfake_new.root", "RECREATE")
#F_out = ROOT.TFile.Open("F_mu_Fred_WZPowheg_new.root", "RECREATE")
#F_out = ROOT.TFile.Open("F_mu_Fred_MCup_new.root", "RECREATE")
#F_out = ROOT.TFile.Open("F_mu_Fred_MCdown_new.root", "RECREATE")

#F_out = ROOT.TFile.Open("F_mu_Fred_EXOT4.root", "RECREATE")
#F_out = ROOT.TFile.Open("F_mu_Fred_CRfake_EXOT4_new.root", "RECREATE")
#F_out = ROOT.TFile.Open("F_mu_Fred_MCup_EXOT4_new.root", "RECREATE")
#F_out = ROOT.TFile.Open("F_mu_Fred_MCdown_EXOT4_new.root", "RECREATE")
#F_out = ROOT.TFile.Open("F_mu_Fred_EXOT4_new.root", "RECREATE")

#F_out = ROOT.TFile.Open("F_mu_Fred_Iso6_new.root", "RECREATE")
#F_out = ROOT.TFile.Open("F_mu_Fred_WZPowheg_Iso6_new.root", "RECREATE")
#F_out = ROOT.TFile.Open("F_mu_Fred_CRfake_Iso6_new.root", "RECREATE")
#F_out = ROOT.TFile.Open("F_mu_Fred_MCup_Iso6_new.root", "RECREATE")
#F_out = ROOT.TFile.Open("F_mu_Fred_MCdown_Iso6_new.root", "RECREATE")

#F_out = ROOT.TFile.Open("F_mu_Fred_EXOT4_Iso6_new.root", "RECREATE")
#F_out = ROOT.TFile.Open("F_mu_Fred_CRfake_EXOT4_Iso6_new.root", "RECREATE")
#F_out = ROOT.TFile.Open("F_mu_Fred_MCup_EXOT4_Iso6_new.root", "RECREATE")
#F_out = ROOT.TFile.Open("F_mu_Fred_MCdown_EXOT4_Iso6_new.root", "RECREATE")

#F_out = ROOT.TFile.Open("F_mu_Fred_EXOT4.root", "RECREATE")
#F_out = ROOT.TFile.Open("F_mu_Fred_WZPowheg_new.root", "RECREATE")

# F_mu_Fred.root (default) -> eff-FakeMuon-CorrMC_highd0sig
# F_mu_Fred_MCup.root      -> eff-FakeMuon-CorrMCUp_highd0sig
# F_mu_Fred_MCdown.root    -> eff-FakeMuon-CorrMCDown_highd0sig
# F_mu_Fred_CRfake.root    -> eff-FakeMuon-CorrMC_lowETmissMTW20_

# name of the input variables
vars = ["Av", "Et", "Eta", "dR", "PtLeadingJet", "dPhi", "MET", "MTW", "d0sig", "Njet", "Nbjet"]
#vars = ["Eta"]
# name of the output variables
ovars = ["av", "pt", "eta", "dR", "jetpt", "dPhi", "met", "mtw", "d0sig", "njet", "nbtag"]
#ovars = ["eta"]

#fakes
allbins = [0,1000]
#etbins = [25,30,35,40,45,50,55,60,80,120,150]
etbins = [25,30,35,40,45,50,55,60,150]
etabins = [0,0.25,0.50,0.75,1.00,1.25,1.50,1.75,2.00,2.25,2.50]
drbins = [0.,0.6,0.8,1.0,1.5,2.0,6.]
ptjetbins = [25,50,75,100,150,500]
dphibins = [0.,0.1,0.2,0.3,0.4,0.5,0.75,1.0,1.25,1.5,1.75,2.0,2.5,3.2]
metbins = [0.,10.0,20.,30.0,40.,60.,100.,150.,200.,1000.]
mwtbins = [0.,10.0,20.,30.0,40.,60.,100.,150.,200.,1000.]
d0sigbins = [0.,1.,2.,3.,4.,5.,6.,7.,8.,9.,10.,20.]
njetbins = [0.,1.,2.,3.,4.,5.]
nbjetbins = [0.,1.0,2.0,3.0]

btags = ["pretag", "nobtag", "btag"]
obtag = ["", "_0b", "_ge1b"]
#btags = ["pretag"]
#obtag = [""]

#jets = ["0j", "1j", "ge1j", "ge2j", "2or3j", "ge4j"]
#ojets = ["0j", "1j", "ge1j", "ge2j", "2or3j", "ge4j"]
jets = ["ge1j", "1j", "ge2j", "2or3j", "ge4j"]
ojets = ["", "_1j", "_ge2j", "_2or3j", "_ge4j"]

trigger = ["HLT_mu24", "HLT_mu24_ivarmedium",  "HLT_mu50"]
otrigger = ["_mu24", "_mu24_ivarmedium", "_mu50"]

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
                    #eff = ROOT.TH1F("eff", "eff",10,array('d',etbins))
                    eff = ROOT.TH1F("eff", "eff",8,array('d',etbins))
                elif v == "dR":
                    eff = ROOT.TH1F("eff", "eff",6,array('d',drbins))
                elif v == "PtLeadingJet":
                    eff = ROOT.TH1F("eff", "eff", 5, array('d',ptjetbins))
                elif v == "DPhi":
                    eff = ROOT.TH1F("eff", "eff", 13, array('d',dphibins))
                elif v == "MET":
                    eff = ROOT.TH1F("eff", "eff", 9, array('d',metbins))
                elif v == "MTW":
                    eff = ROOT.TH1F("eff", "eff", 9, array('d',mwtbins))
                elif v == "d0sig":
                    eff = ROOT.TH1F("eff", "eff", 11, array('d',d0sigbins))
                elif v == "NJet":
                    eff = ROOT.TH1F("eff", "eff", 5, array('d',njetbins))
                elif v == "NbJet":
                    eff = ROOT.TH1F("eff", "eff", 3, array('d',nbjetbins))

                #if b in ("pretag"):
                il = "../eff-2412Muons/eff-FakeMuon-CorrMC_WZSherpa_lowETmissMTW_"+b+"_"+t+"_"+j+version+"_vs"+v+".txt"
                    #il = "../eff-2337-Iso6-new/eff-FakeMuon-CorrMCDown_WZSherpa_lowETmissMTW_"+b+"_Iso6"+"_"+t+"_"+j+version+"_vs"+v+".txt"
                    #if j == "njetge1":
                    #    ol = "_"+otrigger[tc] 
                    #else:
                    #ol = "_"+ojets[jc]+"_"+otrigger[tc]
                #else:
                    #il = "../eff-2412Muons/eff-FakeMuon-CorrMC_WZSherpa_lowETmissMTW_"+b+"_"+t+"_"+j+version+"_vs"+v+".txt"
                    #il = "../eff-2337-Iso6-new/eff-FakeMuon-CorrMCDown_WZSherpa_lowETmissMTW_"+b+"_Iso6"+"_"+t+"_"+j+version+"_vs"+v+".txt"
                    #if j == "njetge1":
                    #    ol = "_"+obtag[bc]+"_"+otrigger[tc]
                    #else:
                    #ol = "_"+obtag[bc]+"_"+ojets[jc]+"_"+otrigger[tc]
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

