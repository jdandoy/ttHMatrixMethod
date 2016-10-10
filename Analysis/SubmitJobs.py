#!/usr/bin/env python
import ROOT, os, glob


thisDir = os.getcwd()+'/'
#Input merged files for MC                                                                                                                                     
#fileDir = "/nfs/dust/atlas/group/top/Nedaa_Ntuples_MM/MergedInput/MC/"
#Test dir
fileDir = "/nfs/dust/atlas/group/top/Nedaa_Ntuples_MM/MergedInput/Test/"

#Input merged files for Data
#fileDir = "/nfs/dust/atlas/group/top/Nedaa_Ntuples_MM/MergedInput/Data-2016/"

fileList = glob.glob(fileDir+'/*.root')

#Trigger Menu 2016 
#triggers = ["_None", "_HLT_e24_lhmedium_L1EM20VH", "_HLT_e24_lhtight_nod0_ivarloose", "_HLT_e60_lhmedium_nod0", "_HLT_e140_lhloose_nod0", "_HLT_e24_lhmedium_nod0_L1EM18VH", "_HLT_e26_lhmedium_nod0_L1EM20VH"]
triggers = ["_HLT_e24_lhmedium_nod0_L1EM18VH", "_HLT_e26_lhmedium_nod0_L1EM20VH"]

#Option Menu for CR1
#options = ["_lowETmissMTW_pretag", "_lowETmissMTW_nobtag", "_lowETmissMTW_btag"]

options = ["_lowETmissnocut_pretag", "_lowETmissnocut_btag"]

#Option Menu for CR1 (mtw<20GeV and MET+MTW<60GeV)
#options = ["_lowETmissMTW"]

#Option Menu for NoCut
#options = ["_lowETmissnocut"]

for trigger in triggers:
	for option in options:
		# Do data here
		for thisFile in fileList:
			logFile = thisDir+'Bird_logs/qsubLog_'+os.path.basename(thisFile).replace('.root','')+'_'+trigger+'_'+option+'.txt'
		        command = 'qsub -o '+logFile+' -e '+logFile+' runBatch.sh '+thisFile + ' '+trigger + ' '+option 
#		        command = 'source runBatch.sh '+thisFile + ' '+trigger + ' '+option 
			print command
			os.system(command)


