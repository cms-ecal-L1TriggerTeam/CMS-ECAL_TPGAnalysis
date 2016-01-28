#!/bin/bash

echo $#

if [[ "$#" < "4" || "$#" > "6" ]] ; then
  echo "runBatchFromCastor.sh: tool for running Batch Jobs for TPG analysis "
  echo "Usage:"
  echo "  ./runAll.sh [mode] [nevt] {filter}"
  echo "      [mode]   - local, lxbatch, grid"
  echo "      [runNb]   - run number"
  echo "      [dataset]   - run number"
  echo "      [nevt]   - number of events per run"
  echo ""
  echo "  Example: ./runTPGbatch.sh lxbatch 234610 Commissioning2015/MinimumBias/RAW/v1 GR_E_V43::All -1  "	 
  exit 1
fi
 

mode="$1"          # 1 run mode
runnb="$2"         # 2 run number
dataset="$3"       # 3 dataset name 
gtag="$4"          # 4 global tag
events="$5"        # number of events per files
eventsPerCastorFile=${events}
isMC="$6"
echo $isMC

#pathrunnb=`echo $runnb | sed 's,\([0-9][0-9][0-9]\)\([0-9][0-9][0-9]\),\1/\2,'`
pathrunnb=`echo $runnb | sed 's,\([0-9][0-9][0-9]\)\([0-9][0-9][0-9]\),\1/\2,'`



myusername="$USER"

echo "path runnumber " ${pathrunnb}
datasetpath=`echo ${dataset} | tr '/' '_'`
echo $datasetpath
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


    /afs/cern.ch/project/eos/installation/0.3.84-aquamarine/bin/eos.select mkdir -p /eos/cms/store/caf/user/${myusername}/TPG/${runnb}_${datasetpath}
    
    retval=`voms-proxy-info &> /dev/null  ; echo $?`
    ppid=$PPID
    #echo "retval " $retval $ppid
    if [ $retval -ne 0 ]; then
	voms-proxy-init --voms cms 
    fi
    cp `find /tmp/x509up_u* -user ${myusername}` $batchdir/.
    
    for myfile in `./das_client.py --query="file dataset=${dataset} run=${runnb}" --limit=0`
      do
      echo "myfile " $myfile 
    #  echo $dataset
      path2file=/store/mc/$dataset/60000
      s=$[$s+1]

      cp -r configuration/configTPGtemplate_AAA.py $batchdir/runTPG_cfg_${s}.py
      cp -r configuration/batch_template_AAA.sh $batchdir/batch_job_${s}.sh

      cd $batchdir/
      sed -e "s,%globaltag%,$gtag,"        \
          -e "s,%numevents%,$eventsPerCastorFile,"        \
	  -e "s,%filename%,root://xrootd-cms.infn.it/$myfile,"      \
	  -e "s,%isMC_%,$isMC," \
          -i runTPG_cfg_${s}.py

      sed -e "s,%cmsswdir%,$batchdir,"        \
          -e "s,%njob%,$s,"        \
	  -e "s,%runNb%,${runnb}," \
	  -e "s,%datasetPath%,${datasetpath}," \
	  -e "s,%username%,${myusername}," \
          -i batch_job_${s}.sh
      
      chmod +x batch_job_${s}.sh
      bsub -q ${queue} batch_job_${s}.sh -o /dev/null -e /dev/null

      cd -
    done


     
     
      ;;

esac 
