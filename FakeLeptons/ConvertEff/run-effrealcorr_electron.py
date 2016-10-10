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


R_out = ROOT.TFile.Open("RCorr_el_Fred.root", "RECREATE")

# input variables
vars = ["Et", "Eta", "Ptoverdr", "dR", "PtCone40", "PtLeadingJet"]
# names of the output histograms
ovars = ["pt", "aeta", "dRpt", "dR", "ptcone40", "jetpt"]

#binning in 1D
allbins = [0,1000]
etbins = [25,30,35,40,45,50,60,80,150]
etabins = [0,0.1,0.6,0.8,1.15,1.37,1.52,1.81,2.01,2.37,2.47]
drptbins = [0,10,50,100,150]
drbins = [0,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4,2.6,2.8,3.0,3.5,4.0,6.]
ptconebins = [0,1.0,2.0,4.0,6.0,10.0,15.0,20.0,30.0]
ptjetbins = [25,30,40,50,75,100,150,150]

#binning in "3D"
etbins3D = [25,40,50,60,150]
etabins3D = [0,0.8,1.37,1.52,1.81,2.01,2.47]
drptbins3D = [0,50,100,150]
drbins3D = [0,0.8,1.5,2.0,3.0,6.0]
ptconebins3D = [0,1.0,2.0,4.0,30.0]

jets = ["njeteq1", "njeteq2or3", "njetge2", "njetge4"]
ojets = ["1j", "2or3j", "ge2j", "ge4j"]

trigger = ["", "EF_trigmatch", "EF_e24vhi_medium1", "EF_e60_medium1"]
otrigger = ["noEF", "", "e24vhi", "e60"]

###### transformation in 1D
jc = 0
for j in jets:
    tc = 0
    for t in trigger:
        vc = 0
        for v in vars:
            #if v == "":
            #    eff = ROOT.TH1F("eff", "eff",1,array('d',allbins))
            #el
            if v == "Eta":
                eff = ROOT.TH1F("MC corr", "MC corr",10,array('d',etabins))
            elif v  == "Et":
                eff = ROOT.TH1F("MC corr", "MC corr",8,array('d',etbins))
            elif v  == "Ptoverdr":
                eff = ROOT.TH1F("MC corr", "MC corr",4,array('d',drptbins))
            elif v == "dR":
                eff = ROOT.TH1F("MC corr", "MC corr",16,array('d',drbins))
            elif v == "PtCone40":
                eff = ROOT.TH1F("MC corr", "MC corr", 8, array('d',ptconebins))
            elif v == "PtLeadingJet":
                eff = ROOT.TH1F("MC corr", "MC corr", 7, array('d',ptjetbins))

            if t == "EF_trigmatch":
                if v == "":
                    il = "../effZee/corr/eff-ZttbarCorr-"+j+".txt"
                else:
                    il = "../effZee/corr/eff-ZttbarCorr-"+j+"_vs"+v+".txt"
                ol = "_"+ojets[jc]
            elif t == "":
                if v == "":
                    il = "../effZee/corr/eff-ZttbarCorr-"+j+".txt"
                else:
                    il = "../effZee/corr/eff-ZttbarCorr-"+j+"_vs"+v+".txt"
                ol = "_"+ojets[jc]+"_"+otrigger[tc]
            else:
                if v == "":
                    il = "../effZee/corr/eff-ZttbarCorr-"+j+"-"+t+".txt"
                else:
                    il = "../effZee/corr/eff-ZttbarCorr-"+j+"-"+t+"_vs"+v+".txt"
                ol = "_"+ojets[jc]+"_"+otrigger[tc]
            #print jc
            
            lines = [line.rstrip() for line in open(il,'r')]
            lc = 0
            for l in lines:
                lc = lc+1
                vl = l.split()
                if v == "PtLeadingJet":
                    eff.SetBinContent(lc,float(vl[2]))
                    err = float(vl[3])
                else:
                    eff.SetBinContent(lc,float(vl[10]))
                    err = float(vl[11])
                eff.SetBinError(lc,err)
                #print vl[10] 
            
            #save
            R_out.cd()
            if v == "":
                oname = "corr"+ol
            else:
                oname = "corr_"+ovars[vc]+ol
            #print oname
            eff.SetName(oname)
            eff.Write(oname)
            vc = vc+1
        tc = tc+1
    jc = jc+1

###### transformation in 3D (Et,Eta,dR)
jc = 0
for j in jets:
    tc = 0
    for t in trigger:
        v = "EtEtadR"
        eff = ROOT.TH3F("MC corr", "MC corr",4,array('d',etbins3D),6,array('d',etabins3D),5,array('d',drbins3D))

        if t == "EF_trigmatch":
            il = "../effZee/corr/eff-ZttbarCorr-"+j+"_vsEtEtadR.txt"
            ol = "_"+ojets[jc]
        elif t == "":
            il = "../effZee/corr/eff-ZttbarCorr-"+j+"_vsEtEtadR.txt"
            ol = "_"+ojets[jc]+"_"+otrigger[tc]
        else:
            il = "../effZee/corr/eff-ZttbarCorr-"+j+"-"+t+"_vsEtEtadR.txt"
            ol = "_"+ojets[jc]+"_"+otrigger[tc]

        #print jc
        lines = [line.rstrip() for line in open(il,'r')]
        lcx = 1
        lcy = 1
        lcz = 0
        for l in lines:
            lcz = lcz+1
            vl = l.split()
            eff.SetBinContent(lcx,lcy,lcz,float(vl[10]))
            err = float(vl[11])
            eff.SetBinError(lcx,lcy,lcz,err)
            
            #print lcx,lcy,lcz,vl[10]
            if lcz == 5:
                lcz = 0
                lcy = lcy+1
            if lcy == 7:
                lcy = 1
                lcx = lcx+1
                
        #save
        R_out.cd()
        oname = "corr_et_aeta_dR"+ol
        #    #print oname
        eff.SetName(oname)
        eff.Write(oname)
        tc = tc+1
    jc = jc+1

###### transformation in 3D (Et,Eta,PtoverdR)
jc = 0
for j in jets:
    tc = 0
    for t in trigger:
        v = "EtEtaPtoverdr"
        eff = ROOT.TH3F("MC corr", "MC corr",4,array('d',etbins3D),6,array('d',etabins3D),3,array('d',drptbins3D))

        if t == "EF_trigmatch":
            il = "../effZee/corr/eff-ZttbarCorr-"+j+"_vsEtEtaPtoverdr.txt"
            ol = "_"+ojets[jc]
        elif t == "":
            il = "../effZee/corr/eff-ZttbarCorr-"+j+"_vsEtEtaPtoverdr.txt"
            ol = "_"+ojets[jc]+"_"+otrigger[tc]
        else:
            il = "../effZee/corr/eff-ZttbarCorr-"+j+"-"+t+"_vsEtEtaPtoverdr.txt"
            ol = "_"+ojets[jc]+"_"+otrigger[tc]

        #print jc
        lines = [line.rstrip() for line in open(il,'r')]
        lcx = 1
        lcy = 1
        lcz = 0
        for l in lines:
            lcz = lcz+1
            vl = l.split()
            eff.SetBinContent(lcx,lcy,lcz,float(vl[10]))
            err = float(vl[11])
            eff.SetBinError(lcx,lcy,lcz,err)
        
            print lcx,lcy,lcz,vl[10]
            if lcz == 3:
                lcz = 0
                lcy = lcy+1
            if lcy == 7:
                lcy = 1
                lcx = lcx+1

        #save
        R_out.cd()
        oname = "corr_et_aeta_dRpt"+ol
        #    #print oname
        eff.SetName(oname)
        eff.Write(oname)
        
        tc = tc+1
    jc = jc+1

###### transformation in 3D (Et,Eta,PtCone40)
jc = 0
for j in jets:
    tc = 0
    for t in trigger:
        v = "EtEtaPtCone40"
        eff = ROOT.TH3F("MC corr", "MC corr",4,array('d',etbins3D),6,array('d',etabins3D),4,array('d',ptconebins3D))

        if t == "EF_trigmatch":
            il = "../effZee/corr/eff-ZttbarCorr-"+j+"_vsEtEtaPtCone40.txt"
            ol = "_"+ojets[jc]
        elif t == "":
            il = "../effZee/corr/eff-ZttbarCorr-"+j+"_vsEtEtaPtCone40.txt"
            ol = "_"+ojets[jc]+"_"+otrigger[tc]
        else:
            il = "../effZee/corr/eff-ZttbarCorr-"+j+"-"+t+"_vsEtEtaPtCone40.txt"
            ol = "_"+ojets[jc]+"_"+otrigger[tc]

        #print jc
        lines = [line.rstrip() for line in open(il,'r')]
        lcx = 1
        lcy = 1
        lcz = 0
        for l in lines:
            lcz = lcz+1
            vl = l.split()
            eff.SetBinContent(lcx,lcy,lcz,float(vl[10]))
            err = float(vl[11])
            eff.SetBinError(lcx,lcy,lcz,err)
        
            #print lcx,lcy,lcz,vl[10]
            if lcz == 4:
                lcz = 0
                lcy = lcy+1
            if lcy == 7:
                lcy = 1
                lcx = lcx+1

        #save
        R_out.cd()
        oname = "corr_et_aeta_ptcone40"+ol
        #print oname
        eff.SetName(oname)
        eff.Write(oname)

        tc = tc+1
    jc = jc+1


