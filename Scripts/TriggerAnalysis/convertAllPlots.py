#!/bin/env python

import os 
import argparse

 
parser = argparse.ArgumentParser(description='Script to convert png plots to jpg thumbnails.')
parser.add_argument('-r','--runnumber', help='Run number',required=True)
parser.add_argument('-a','--addendum',help='Addendum to differentiate different running conditions', required=True)
args=parser.parse_args()

cmssw_base= os.environ['CMSSW_BASE']


path=cmssw_base+'/src/CMS-ECAL_TPGAnalysis/Scripts/TriggerAnalysis/Commissioning2016/'+str(args.runnumber)+'_'+str(args.addendum)

print path

for file in os.listdir(path):
    current_file = os.path.join(path, file)
    if os.path.isfile(current_file) and 'png' in current_file:
        new_file_name="".join(['thumb_',file.replace('.png','.jpg')])
        new_file=os.path.join(path,new_file_name)
        
        out=os.popen("convert -thumbnail x200 "+current_file+" "+new_file)
