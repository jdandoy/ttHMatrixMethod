#!/usr/bin/env python
import ROOT, os, glob


thisDir = os.getcwd()+'/'

#Input merged files for Data for Tag&Probe
fileDir = "/nfs/dust/atlas/group/top/Nedaa_Ntuples_MM/MergedInput/Data/"

fileList = glob.glob(fileDir+'/*.root')

#Trigger Menu
#triggers = ["_None", "_HLT_e24_lhmedium_iloose_L1EM20VH", "_HLT_e60_lhmedium", "_HLT_e120_lhloose"]
triggers = ["_None"]

#Option for jets
jets = ["_njeteq1", "_njetge1", "_njetge2", "_njeteq2or3", "_njetge4"]
#jets= ["_njeteq1"]


for trigger in triggers:
	for jet in jets:
		# Do data here
		for thisFile in fileList:
			logFile = thisDir+'Bird_logs/qsubLog_'+os.path.basename(thisFile).replace('.root','')+'_'+trigger+'_'+jet+'.txt'
		        command = 'qsub -o '+logFile+' -e '+logFile+' runBatch_TP.sh  '+thisFile + ' '+trigger + ' '+jet 
#		        command = 'source runBatch_TP.sh  '+thisFile + ' '+trigger + ' '+jet 
			print command
			os.system(command)


