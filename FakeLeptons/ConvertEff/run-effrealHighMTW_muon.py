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

R_out = ROOT.TFile.Open("R_mu_Fred_CRreal_new.root", "RECREATE")
#R_out = ROOT.TFile.Open("R_mu_Fred_CRreal_EXOT4.root", "RECREATE")
#R_out = ROOT.TFile.Open("R_mu_Fred_CRreal_Iso6.root", "RECREATE")
#R_out = ROOT.TFile.Open("R_mu_Fred_CRreal_EXOT4_Iso6.root", "RECREATE")

# name of the input variables
vars = ["Av", "Pt", "Eta", "dR", "PtLeadingJet", "dPhi", "MET", "MTW", "NJet", "NbJet"]
# name of the output variables
ovars = ["av", "pt", "eta", "dR", "jetpt", "dPhi", "met", "mwt", "njet", "nbtag"]

#binning in 1D
allbins   = [0,1000]
etbins    = [25,30,35,40,45,50,55,60,80,120,150]
etabins   = [0,0.25,0.50,0.75,1.00,1.25,1.50,1.75,2.00,2.25,2.50]
drbins    = [0.4,0.6,0.8,1.0,1.5,2.0,6.]
ptjetbins = [25,50,75,100,150,500]
dphibins  = [0.,0.1,0.2,0.3,0.4,0.5,0.75,1.0,1.25,1.5,1.75,2.0,2.5,3.2]
metbins   = [0.,10.0,20.,30.0,40.,60.,100.,150.,200.,1000.]
mwtbins   = [0.,10.0,20.,30.0,40.,60.,100.,150.,200.,1000.]
njetbins  = [0.,1.,2.,3.,4.,5.]
nbjetbins = [0.,1.0,2.0,3.0]

btags = ["pretag", "nobtag", "btag"]
obtag = ["", "0b", "ge1b"]

jets = ["0j", "1j", "ge1j", "ge2j", "2or3j", "ge4j"]
ojets = ["0j", "1j", "ge1j", "ge2j", "2or3j", "ge4j"]

trigger = ["HLT_mu20_iloose_L1MU15", "HLT_mu20_L1MU15",  "HLT_mu50"]
otrigger = ["mu20i", "mu20", "mu50"]

version = ".2337-2"

bc = 0
for b in btags:
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
                elif v == "Pt":
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
                elif v == "NJet":
                    eff = ROOT.TH1F("eff", "eff", 5, array('d',njetbins))
                elif v == "NbJet":
                    eff = ROOT.TH1F("eff", "eff", 3, array('d',nbjetbins))
               
                if b in ("pretag"):
                    #il = "../eff-2337-EXOT4-Iso6/eff-RealMuon_highMTW_"+b+"_Iso6"+"_"+t+"_"+j+"_periodDtoJ"+version+"_vs"+v+".txt"
                    il = "../eff-2337/eff-RealMuon_highMTW_"+b+"_"+t+"_"+j+"_periodDtoJ"+version+"_vs"+v+".txt"
                    #if j == "ge1j":
                    #    ol = "_"+otrigger[tc] 
                    #else:
                    ol = "_"+ojets[jc]+"_"+otrigger[tc]
                else:
                    #il = "../eff-2337-EXOT4-Iso6/eff-RealMuon_highMTW_"+b+"_Iso6"+"_"+t+"_"+j+"_periodDtoJ"+version+"_vs"+v+".txt"
                    il = "../eff-2337/eff-RealMuon_highMTW_"+b+"_"+t+"_"+j+"_periodDtoJ"+version+"_vs"+v+".txt"
                    #if j == "ge1j":
                    #    ol = "_"+obtag[bc]+"_"+otrigger[tc]
                    #else:
                    ol = "_"+obtag[bc]+"_"+ojets[jc]+"_"+otrigger[tc]
                    
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
                eff.SetName(oname)
                eff.Write(oname)
                vc = vc+1
            tc = tc+1
        jc = jc+1
    bc = bc+1

