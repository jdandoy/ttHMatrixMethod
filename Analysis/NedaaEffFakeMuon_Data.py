import ROOT, os, glob
import argparse
parser = argparse.ArgumentParser(description="%prog [options]", formatter_class=argparse.ArgumentDefaultsHelpFormatter)
parser.add_argument("--file", dest='file', default="", help="Input file")
parser.add_argument("--trigger", dest='trigger', default="", help="Input trigger")
parser.add_argument("--option", dest='option', default="", help="Input option")
args = parser.parse_args()

name_Tree = "nominal_Loose"

if args.trigger == '_None':
	args.trigger = ''

#Out put Histos                                                                                                                                                                    
outDir = "/nfs/dust/atlas/group/top/Nedaa_Ntuples_MM/OutputHistos/2016/Muon/Fakes_Data/"


#file = [fileDir+'user.derue.mc15_13TeV.361313.Sherpa_CT10_Wenu_Pt500_700_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.2341.root']


ROOT.gROOT.ProcessLine(".x compile.C")
codeType = "MyEffiFakeMuon" 


NewName = '.'.join(os.path.basename(args.file).split('.')[:-2])
versionout = args.file.split('.')[-2]
outName = outDir+NewName+".EffiFakeMuon"+args.option+args.trigger+'.'+versionout+".root"

dataset = ROOT.TChain(name_Tree)
dataset.Add(args.file)
dataset.Process("doAna/"+codeType+".C+",args.option+args.trigger+'_NAME'+outName)

#NewName = '.'.join(os.path.basename(args.file).split('.')[:-2])
#versionout = args.file.split('.')[-2]
#os.system('mv Ana-EffiFakeElec.root '+outDir+NewName+".EffiFakeElec"+args.option+args.trigger+'.'+versionout+".root")
		

