#!/bin/bash

echo $#
# Run2011A/Cosmics/RAW/v1  165078
# print usage info
# ./runTPGbatch.sh lxbatch 234610 Commissioning2015/MinimumBias/RAW/v1 GR_E_V43 -1
if [[ "$#" < "4" || "$#" > "5" ]] ; then
  echo "runBatchFromCastor.sh: tool for running Batch Jobs for TPG analysis "
  echo "Usage:"
  echo "  ./runAll.sh [mode] [nevt] {filter}"
  echo "      [mode]   - local, lxbatch, grid"
  echo "      [runNb]   - run number"
  echo "      [dataset]   - run number"
  echo "      [nevt]   - number of events per run"
  echo ""
  echo "  Example: ./runTPGbatch.sh lxbatch 234610 Commissioning2015/MinimumBias/RAW/v1 GR_E_V43 -1  "	 
  exit 1
fi
 

mode="$1"          # 1 run mode
runnb="$2"         # 2 run number
dataset="$3"       # 3 dataset name 
gtag="$4"          # 4 global tag
events="$5"        # number of events per files
eventsPerCastorFile=${events}

pathrunnb=`echo $runnb | sed 's,\([0-9][0-9][0-9]\)\([0-9][0-9][0-9]\),\1/\2,'`

echo "path runnumber " ${pathrunnb}
datasetpath=`echo ${dataset} | tr '/' '_'`

case "$mode" in

  "lxbatch" )
    # --- master mode ---
    # (this part is going on local machine)
   
    queue="cmscaf1nd"   # LXBATCH jobs queue
#    queue="8nh"
    batchdir="$(pwd)/log_and_results/${runnb}-${datasetpath}-batch"
    mkdir -p $batchdir
    mkdir -p $batchdir/logs
    mkdir -p $batchdir/results
    # prepare job submission directory


    for myfile in `/afs/cern.ch/project/eos/installation/0.3.84-aquamarine/bin/eos.select ls store/data/$dataset/000/${pathrunnb}/00000`   
      do
      echo $myfile 
      path2file=/store/data/$dataset/000/${pathrunnb}/00000
      s=$[$s+1]

#      cp -r configuration/configTPGtemplate.py $batchdir/runTPG_cfg_${s}.py
      cp -r configuration/configTPGtemplate_new.py $batchdir/runTPG_cfg_${s}.py
      cp -r configuration/batch_template.sh $batchdir/batch_job_${s}.sh

      cd $batchdir/
      sed -e "s,%globaltag%,$gtag,"        \
          -e "s,%numevents%,$eventsPerCastorFile,"        \
          -e "s,%filename%,/store/data/$dataset/000/${pathrunnb}/00000/$myfile,"      \
          -i runTPG_cfg_${s}.py
      sed -e "s,%cmsswdir%,$batchdir,"        \
          -e "s,%njob%,$s,"        \
          -i batch_job_${s}.sh
      
      chmod +x batch_job_${s}.sh
      echo "current dirctory"
      echo  $batchdir
      echo "the end"
#      bsub -q ${queue} batch_job_${s}.sh -o /dev/null -e /dev/null
  #    source batch_job_${s}.sh
      cd -
    done


     
     
      ;;

esac 
