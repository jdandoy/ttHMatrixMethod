import ROOT, os, glob

f_check = True
f_local = False
f_grid = True


thisDir = os.getcwd()+'/'
#Input merged files for MC                                                                                                                                                                          
logDir = thisDir+'/Bird_logs/'

#Mc
fileDir = "/nfs/dust/atlas/group/top/Nedaa_Ntuples_MM/MergedInput/MC/"

#Data
#fileDir = "/nfs/dust/atlas/group/top/Nedaa_Ntuples_MM/MergedInput/Data/"

if (f_check):
	print "Checking number of unfinished jobs"
	os.system('grep -L -r "FINISHED" '+logDir+' | wc -l')
	print "out of the total number of jobs"
	os.system('ls '+logDir+' | wc -l')

os.system('grep -L -r "FINISHED" '+logDir+' >> tmpUnfinishedJobs.txt')


with open('tmpUnfinishedJobs.txt','r') as f:
	for line in f:
		inLogFile = line.rstrip()
		splitLine = inLogFile.split('__')

		fileName = fileDir+os.path.basename(splitLine[0]).replace('qsubLog_','')+'.root'
		triggerName = '_'+splitLine[1]
		optionName = '_'+splitLine[2].replace('.txt','')

		logFile = thisDir+'Bird_logs/qsubLog_'+os.path.basename(fileName).replace('.root','')+'_'+triggerName+'_'+optionName+'.txt'

		if (f_grid):
	        	command = 'qsub -o '+logFile+' -e '+logFile+' runBatchMuon.sh '+fileName + ' '+triggerName + ' '+optionName 
#			os.system('rm '+inLogFile)  if electron runBatch.sh and for Muons: runBatchMuon.sh
		if (f_local):
	        	command = 'source runBatchMuon.sh '+fileName + ' '+triggerName + ' '+optionName 
		print command
		os.system(command)

os.system('rm tmpUnfinishedJobs.txt')
