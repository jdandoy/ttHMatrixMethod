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


F_out = ROOT.TFile.Open("F_mu_Fred.root", "RECREATE")
R_out = ROOT.TFile.Open("R_mu_Fred.root", "RECREATE")

vars = ["Pt", "Eta", "Ptoverdr", "dR", "PtCone40"]

ovars = ["pt", "eta", "ptdR", "dRlepjet", "PtCone40"]

#fakes
etbins = [25,30,35,40,45,50,60,80,110]
etabins = [0,0.1,0.6,0.8,1.15,1.37,1.52,1.81,2.01,2.37,2.47]
drptbins = [0,10,50,100,150]
drbins = [0,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4,2.6,2.8,3.0,3.5,4.0,4.3]
ptconebins = [0,0.5,2.0,4.0,6.0,10.0,15.0,20.0,30.0]

btags = ["", "Global0Btag", "btag"]
obtag = ["", "0b", "ge1b"]

jets = ["", "njeteq1or2", "njeteq3", "njetge4"]
ojets = ["", "1or2j", "3j", "ge4j"]

#bc = 0
#for b in btags:
#    jc = 0
#    for j in jets:
#        vc = 0
#        for v in vars:
#            if v == "Eta":
#                eff = ROOT.TH1F("eff", "eff",10,array('d',etabins))
#            elif v == "Et":
#                eff = ROOT.TH1F("eff", "eff",8,array('d',etbins))
#            elif v == "Var":
#                eff = ROOT.TH1F("eff", "eff",4,array('d',drptbins))
#                    
#            if b in ("") and j in (""):
#                il = "eff-Fakes_LooseNoIsolowETmissTightisoat90-p1401_vs"+v+".txt"
#                ol = ""
#            elif b in ("") and j not in (""):
#                il = "eff-Fakes_LooseNoIsolowETmiss-"+j+"Tightisoat90-p1401_vs"+v+".txt"
#                ol = "_"+ojets[jc]
#            elif b not in ("") and j in (""):
#                il = "eff-Fakes_LooseNoIsolowETmiss"+b+"Tightisoat90-p1401_vs"+v+".txt"
#                ol = "_"+obtag[bc]
#            else:
#                il = "eff-Fakes_LooseNoIsolowETmiss"+b+"-"+j+"Tightisoat90-p1401_vs"+v+".txt"
#                ol = "_"+obtag[bc]+"_"+ojets[jc]
#                    
#            lines = [line.rstrip() for line in open(il,'r')]
#            lc = 0
#            for l in lines:
#                lc = lc+1
#                vl = l.split()                
#                eff.SetBinContent(lc,float(vl[2])/100)
#                err = float(vl[3])*float(vl[2])/100
#                eff.SetBinError(lc,err)
#            
#            #save
#            F_out.cd()
#            oname = "eff_"+ovars[vc]+ol
#            eff.SetName(oname)
#            eff.Write(oname)
#            vc = vc+1
#        jc = jc+1
#    bc = bc+1


#real

jets = ["njeteq1", "njeteq2or3", "njetge2", "njetge4"]
ojets = ["1j", "2or3j", "ge2j", "ge4j"]

trigger = ["trigmatch17", "trigmatch1"]
otrigger = ["mu36", "mu24i"]

jc = 0
for j in jets:
    tc = 0
    for t in trigger:
        vc = 0
        for v in vars:
            if v == "Eta":
                eff = ROOT.TH1F("eff", "eff",10,array('d',etabins))
            elif v  == "Pt":
                eff = ROOT.TH1F("eff", "eff",8,array('d',etbins))
            elif v  == "Ptoverdr":
                eff = ROOT.TH1F("eff", "eff",4,array('d',drptbins))
            elif v == "dR":
                eff = ROOT.TH1F("eff", "eff",16,array('d',drbins))
            elif v == "PtCone40":
                eff = ROOT.TH1F("eff", "eff", 8, array('d',ptconebins))
                    
                    
            il = "effZmumu/eff/eff-Zmumu-periodAtoM-SB-Yield81to101_LooseNoIsoTightisoat90-p1401-"+j+"-"+t+"_vs"+v+".txt"
            ol = "_"+ojets[jc]+"_"+otrigger[tc]
            
            lines = [line.rstrip() for line in open(il,'r')]
            lc = 0
            for l in lines:
                lc = lc+1
                vl = l.split()
                eff.SetBinContent(lc,float(vl[10])/100)
                err = float(vl[11])/100
                eff.SetBinError(lc,err)
            
            #save
            R_out.cd()
            oname = "eff_"+ovars[vc]+ol
            eff.SetName(oname)
            eff.Write(oname)
            vc = vc+1
        tc = tc+1
    jc = jc+1
     



