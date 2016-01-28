# CMS-ECAL_TPGAnalysis (7_5_6)

##This houses the latest version of the Level 1 Ecal TPG analysis of CMS
======================================================================
How to run:

Get the CMSSW release area
```bash
cmsrel CMSSW_7_5_6
cd CMSSW_7_5_6/src
cmsenv
```

Checkout the repository
```
git cms-init
git clone https://github.com/cms-ecal-L1TriggerTeam/CMS-ECAL_TPGAnalysis.git
scram b
``` 


BEFORE YOU RUN, you need to make sure you change the directory/path names to your directories or directories you want results in.

 `cd CMS-ECAL_TPGAnalysis/Scripts/TriggerAnalysis`

In particular the files you need to modify are : `mergeTPGAnalysis.sh; makeTrigPrimPlots.sh ; convertAllPlots.py ;produceplotonCAFqueues.sh `

  `cd ../../TPGPlotting/plots` and also modify path in `makeTPGPlots.sh`

(what follows is to be modified- Nabarun)
       
Then follow instructions on this twiki here:

https://twiki.cern.ch/twiki/bin/viewauth/CMS/EcalPFGCode#Trigger_Primitive_Analysis

