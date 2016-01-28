#!/bin/bash

ps | grep `echo $$` | awk '{ print $4 }' 

export mypwd=`pwd`




cd %cmsswdir%

#export SCRAM_ARCH slc5_amd64_gcc434
#source /afs/cern.ch/cms/LCG/LCG-2/UI/cms_ui_env.sh

eval `scramv1 runtime -sh`

cd -
#cd \${lxbatchpwd}

echo "Starting CMSSW" 
cp %cmsswdir%/runTPG_cfg_%njob%.py .
cmsRun runTPG_cfg_%njob%.py  >& /dev/null

mv ECALTPGtree.root %cmsswdir%/results/ECALTPGtree_%njob%.root

echo "LAST PWD" 'pwd'

