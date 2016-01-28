#!/bin/bash

cd /afs/cern.ch/work/n/ndev/CMSSW_7_5_6/src/CMS-ECAL_TPGAnalysis/Scripts/TriggerAnalysis


eval `scramv1 runtime -csh`

./makeTrigPrimPlots.sh -r 254833 -a _test_package

exit
