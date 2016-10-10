#!/bin/bash
#$ -l site=hh
###(to prevent from starving in queue)
####$ -R y
# (only accept jobs with correct resources)
#$ -w e
#
######3# (stderr and stdout are merged together to stdout)
#$ -j y
#
# (send mail on job's end and abort)
###$ -m ae -M nedaa.asbah@desy.de
#
# (put log files into current working directory)
#$ -cwd
#
# (use ATLAS project)
#####$ -P atlas
#
# (choose memory)
####$ -l s_vmem=6G
###$ -l h_vmem=6G 
###$ -l h_stack=10M
#
# (choose time)
###$ -l h_rt=24:00:00
###$ -l h_cpu=23:59:00
###$ -l h_rt=02:59:00
###$ -l h_cpu=02:58:00
# (choose operation system)
#$ -l os=sld6
###$ -l distro=sld6
###$ -l arch=x86
#
#####$ -l cvmfs=yes
#
####$ -l hostname="!(bird035.desy.de|bird080.desy.de|bird120.desy.de|bird132.desy.de|crf-wgs05.desy.de|bird163.desy.de|bird151.desy.de|bird056.desy.de|bird122.desy.de|bird119.desy.de|bird128.desy.de|bird163.desy.de|bird127.desy.de|bird097.desy.de|bird055.desy.de|bird043.desy.de|bird159.desy.de|bird040.desy.de|theol04.desy.de|bird045.desy.de|bird119.desy.de|bird123.desy.de|bird129.desy.de|bird130.desy.de|bird131.desy.de|bird134.desy.de|bird119.desy.de|bird151.desy.de)|bird152.desy.de|bird153.desy.de|bird155.desy.de|bird157.desy.de|bird159.desy.de|bird160.desy.de|bird162.desy.de|bird163.desy.de"
#### mine removed from 045

echo "----------------------------------------------------------------"
echo "Started at:"
date
echo "on host: " ${HOSTNAME}
echo "----------------------------------------------------------------"

WORKDIR=${TMPDIR}
cd $WORKDIR

FILE=$1
TRIGGER=$2
OPTION=$3

echo "----------------------------------------------------------------"
echo "----------------------------------------------------------------"

echo "FILE: "${FILE}
echo "TRIGGER: "${TRIGGER}
echo "OPTION: "${OPTION}

echo $PWD

echo "----------------------------------------------------------------"
ls -lsa
echo "----------------------------------------------------------------"

cd /nfs/dust/atlas/group/top/Nedaa_Ntuples_MM/AT-2016/Analysis/
echo "Setting up ROOT"
source setupROOT.sh
echo "Running python file"
#MC
echo "python NedaaEffFakeElec_MC.py --file ${FILE} --trigger ${TRIGGER} --option ${OPTION}"
python NedaaEffFakeElec_MC.py --file ${FILE} --trigger ${TRIGGER} --option ${OPTION} 
#Data
#echo "python NedaaEffFakeElec_Data.py --file ${FILE} --trigger ${TRIGGER} --option ${OPTION}"
#python NedaaEffFakeElec_Data.py --file ${FILE} --trigger ${TRIGGER} --option ${OPTION}
echo "Finished python file"

echo "----------------------------------------------------------------"
echo "Ended at:"
date
echo "on host: " ${HOSTNAME}
echo "----------------------------------------------------------------"
echo "FINISHED JOB"

#python NedaaEffFakeElec_MC.py --file /nfs/dust/atlas/group/top/Nedaa_Ntuples_MM/MergedInput/TEST/user.derue.mc15_13TeV.361313.Sherpa_CT10_Wenu_Pt500_700_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.2341.root --trigger _HLT_e24_lhmedium_iloose_L1EM20VH --option _lowETmissMTW_nobtag
#./runBatch.sh /nfs/dust/atlas/group/top/Nedaa_Ntuples_MM/MergedInput/TEST/user.derue.mc15_13TeV.361313.Sherpa_CT10_Wenu_Pt500_700_CFilterBVeto.DAOD_TOPQ1.e4133_s2608_s2183_r7326_r6282_p2516.2341.root _HLT_e24_lhmedium_iloose_L1EM20VH _lowETmissMTW_nobtag
