import ROOT, os, glob
import argparse
parser = argparse.ArgumentParser(description="%prog [options]", formatter_class=argparse.ArgumentDefaultsHelpFormatter)
parser.add_argument("--file", dest='file', default="", help="Input file")
parser.add_argument("--trigger", dest='trigger', default="", help="Input trigger")
parser.add_argument("--jet", dest='jet', default="", help="Input jet")
args = parser.parse_args()

name_Tree = "nominal_Loose"

if args.trigger == '_None':
	args.trigger = ''

#Input merged files for Data                                                                                                                                                                          
outDir = "/nfs/dust/atlas/group/top/Nedaa_Ntuples_MM/OutputHistos/output_Data_TP/"


ROOT.gROOT.ProcessLine(".x compile.C")
codeType = "MyEffiRealElecTP" 


NewName = '.'.join(os.path.basename(args.file).split('.')[:-2])
versionout = args.file.split('.')[-2]
outName = outDir+NewName+".EffiRealElecTP"+args.trigger+args.jet+'.'+versionout+".root"

dataset = ROOT.TChain(name_Tree)
dataset.Add(args.file)
dataset.Process("doAna/"+codeType+".C+",args.trigger+args.jet+'_NAME'+outName)

#NewName = '.'.join(os.path.basename(args.file).split('.')[:-2])
#versionout = args.file.split('.')[-2]
#os.system('mv Ana-EffiFakeElec.root '+outDir+NewName+".EffiFakeElec"+args.option+args.trigger+'.'+versionout+".root")
		

