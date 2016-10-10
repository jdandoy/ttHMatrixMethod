#!/usr/bin/env python
import ROOT, os, glob


thisDir = os.getcwd()+'/'

#Input merged files for MC                                                                                                                                     
#fileDir = "/nfs/dust/atlas/group/top/Nedaa_Ntuples_MM/MergedInput/MC/"

#Input merged files for Data
fileDir = "/nfs/dust/atlas/group/top/Nedaa_Ntuples_MM/MergedInput/Data-2016/"

fileList = glob.glob(fileDir+'/*.root')

#Trigger Menu 2016
triggers = ["_HLT_mu24", "_HLT_mu24_ivarmedium", "_HLT_mu50"]
#triggers = ["_HLT_mu50"]

#Option Menu for CR1
#options = ["_lowETmissMTW_pretag", "_lowETmissMTW_nobtag", "_lowETmissMTW_btag"]

#Option Menu for CR1 (mtw<20GeV and MET+MTW<60GeV)
options = ["_lowETmissMTW_nobtag", "_lowETmissMTW_btag"]

#Option Menu for NoCut
#options = ["_lowETmissnocut_pretag"]

for trigger in triggers:
	for option in options:
		# Do data here
		for thisFile in fileList:
			logFile = thisDir+'Bird_logs/qsubLog_'+os.path.basename(thisFile).replace('.root','')+'_'+trigger+'_'+option+'.txt'
		        command = 'qsub -o '+logFile+' -e '+logFile+' runBatchMuon.sh '+thisFile + ' '+trigger + ' '+option 
#		        command = 'source runBatchMuon.sh '+thisFile + ' '+trigger + ' '+option 
			print command
			os.system(command)


