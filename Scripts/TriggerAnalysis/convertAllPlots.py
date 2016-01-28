#!/bin/env python
import os 
path='/afs/cern.ch/work/n/ndev/CMSSW_7_5_6/src/CMS-ECAL_TPGAnalysis/Scripts/TriggerAnalysis/Commissioning2016/254833_test_package_eg12'



for file in os.listdir(path):
    current_file = os.path.join(path, file)
    if os.path.isfile(current_file) and 'png' in current_file:
        new_file_name="".join(['thumb_',file.replace('.png','.jpg')])
        new_file=os.path.join(path,new_file_name)
        
        out=os.popen("convert -thumbnail x200 "+current_file+" "+new_file)
