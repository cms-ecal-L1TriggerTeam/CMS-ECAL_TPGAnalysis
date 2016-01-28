#!/bin/bash

ps | grep `echo $$` | awk '{ print $4 }' 

export mypwd=`pwd`




cd %cmsswdir%

#export SCRAM_ARCH slc5_amd64_gcc434
#source /afs/cern.ch/cms/LCG/LCG-2/UI/cms_ui_env.sh

eval `scram runtime -sh`
if [ $X509_USER_PROXY!="" ]; then 
    export X509_USER_PROXY=`find %cmsswdir%/x509up_u*`
fi 
echo 
cd -
#cd \${lxbatchpwd}

echo "Starting CMSSW" 
cp %cmsswdir%/runTPG_cfg_%njob%.py .
#cmsRun runTPG_cfg_%njob%.py  >& /dev/null

cmsRun runTPG_cfg_%njob%.py  >& /dev/null

mv ECALTPGtree.root %cmsswdir%/results/ECALTPGtree_%njob%.root

#cmsStage -f ECALTPGtree.root /store/caf/user/%username%/TPG/%runNb%/ECALTPGtree_%njob%.root
#cmsStage -f ECALTPGtree.root /store/caf/user/%username%/TPG/%runNb%_%datasetPath%/ECALTPGtree_%njob%.root

echo "LAST PWD" 'pwd'

