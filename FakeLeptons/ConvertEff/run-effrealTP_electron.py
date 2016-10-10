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


#R_out = ROOT.TFile.Open("R_el_Fred.root", "RECREATE")
R_out = ROOT.TFile.Open("R_el_Fred_EXOT4_Iso6.root", "RECREATE")

# input variables
vars = ["Av", "Et", "Eta", "dR", "PtLeadingJet", "dPhi", "MET", "MTW", "njet", "nbjet"]
# name of the output variables
ovars = ["av", "pt", "eta", "dR", "jetpt", "dPhi", "met", "mtw", "njet", "nbtag"]

#binning in 1D
allbins = [0,1000]
etbins    = [25,30,35,40,45,50,55,60,80,120,150]
etabins = [0,0.1,0.6,0.8,1.15,1.37,1.52,1.81,2.01,2.37,2.47]
drbins    = [0.4,0.6,0.8,1.0,1.5,2.0,6.0]
ptjetbins = [25,50,75,100,150,500]
dphibins = [0.,0.1,0.2,0.3,0.4,0.5,0.75,1.0,1.25,1.5,1.75,2.0,2.5,3.2]
metbins = [0.,10.0,20.,30.0,40.,60.,100.,150.,200.,1000.]
mwtbins = [0.,10.0,20.,30.0,40.,60.,100.,150.,200.,1000.]
njetbins  = [0.,1.,2.,3.,4.,5.]
nbjetbins = [0.,1.0,2.0,3.0]

jets = ["njetge1", "njeteq1", "njetge2", "njeteq2or3", "njetge4"]
ojets = ["ge1j", "1j", "ge2j", "2or3j", "ge4j"]

#trigger = ["", "HLT_e24_lhmedium_L1EM20VH", "HLT_e60_lhmedium", "HLT_e120_lhloose"]
#otrigger = ["", "trig0", "trig1", "trig2"]
trigger = ["", "HLT_e24_lhmedium_iloose_L1EM20VH", "HLT_e24_lhmedium_L1EM20VH", "HLT_e60_lhmedium", "HLT_e120_lhloose"]
otrigger = ["", "e24i", "e24", "e60", "e120"]
#trigger = [""]
#otrigger = [""]

###### transformation in 1D
jc = 0
for j in jets:
    tc = 0
    for t in trigger:
        vc = 0
        for v in vars:
            if v == "Av":
                eff = ROOT.TH1F("eff", "eff",1,array('d',allbins))
            elif v == "Eta":
                eff = ROOT.TH1F("eff", "eff",10,array('d',etabins))
            elif v  == "Et":
                eff = ROOT.TH1F("eff", "eff",10,array('d',etbins))
            elif v == "dR":
                eff = ROOT.TH1F("eff", "eff",6,array('d',drbins))
            elif v == "PtLeadingJet":
                eff = ROOT.TH1F("eff", "eff", 5, array('d',ptjetbins))
            elif v == "dPhi":
                eff = ROOT.TH1F("eff", "eff", 13, array('d',dphibins))
            elif v == "MET":
                eff = ROOT.TH1F("eff", "eff", 9, array('d',metbins))
            elif v == "MTW":
                eff = ROOT.TH1F("eff", "eff", 9, array('d',mwtbins))
            elif v == "njet":
                eff = ROOT.TH1F("eff", "eff", 5, array('d',njetbins))
            elif v == "nbjet":
                eff = ROOT.TH1F("eff", "eff", 3, array('d',nbjetbins))

            if t == "":
                #il = "../eff-2337/eff-Zee-periodDtoJ-SB-Yield81to101"+"-"+j+"_vs"+v+".txt"
                il = "../eff-2337-EXOT4-Iso6/eff-Zee-periodDtoJ-SB-Yield81to101""_Iso6"+"-"+j+"_vs"+v+".txt"
                ol = "_"+ojets[jc]
            else:
                #il = "../eff-2337-EXOT4/eff-Zee-periodDtoJ-SB-Yield81to101"+"_"+t+"-"+j+"_vs"+v+".txt"
                il = "../eff-2337-EXOT4-Iso6/eff-Zee-periodDtoJ-SB-Yield81to101"+"_Iso6"+"_"+t+"-"+j+"_vs"+v+".txt"
                ol = "_"+ojets[jc]+"_"+otrigger[tc]

            print il
            #print ol
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
            R_out.cd()
            oname = "eff_"+ovars[vc]+ol
            #print oname
            eff.SetName(oname)
            eff.Write(oname)
            vc = vc+1
        tc = tc+1
    jc = jc+1
     
