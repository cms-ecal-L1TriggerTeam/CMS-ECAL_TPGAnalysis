#!/bin/bash

die(){
   echo "$@"
   exit 1
}

usage='Usage: -r <run number> -m <merge_dir> Example: ./mergeTPGAnalysis.sh -r 165078 -m log_and_results/165078-Run2011A_Cosmics_RAW_v1-batch/results/ -a addendum'  

eos='/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select'

args=`getopt rowm: -- "$@"`
if test $? != 0
     then
         echo $usage
         exit 1
fi

eval set -- "$args"
for i 
  do
  case "$i" in
      -r) shift; run_num=$2;shift;;
      -m) shift; merge_dir=$2;shift;;
      -a) shift; addendum=$2;shift;;
  esac      
done

if [ "X"${run_num} == "X" ]
    then
    echo "INVALID RUN NUMBER! Please give a valid run number!"
    echo $usage
    exit 
fi

if [ "X"${merge_dir} == "X" ]
    then
    echo $usage
    exit	
fi


#to distingusih between several files produced from the same input run with different parameters etc.
if [ "X"${addendum} != "X" ]
    then
    addendum="_"$addendum     
fi


echo 'Merging TPG Analysis output for run' ${run_num} 

hadd -f ECALTPGtree${addendum}_${run_num}.root ${merge_dir}/ECALTPGtree_*root

if [ "X"${output_dir} == "X" ]
    then
   # 	output_dir=eos/cms/store/caf/user/ccecal/TPG/
    	output_dir=eos/cms/store/user/ndev/TPG/ECALTPG_tree/
        output_root_dir=root://eoscms//${output_dir}
    	echo " use default output dir" $output_dir
    	#rfmkdir ${output_dir}
    	#rfchmod 775 ${output_dir}
    	#rfcp ECALTPGtree_${addendum}_${run_num}.root ${output_dir}
    	#eos mkdir ${output_dir} 
    	#eos chmod 775 ${output_dir}
        echo xrdcp -f ECALTPGtree${addendum}_${run_num}.root ${output_root_dir}
    	xrdcp -f ECALTPGtree${addendum}_${run_num}.root ${output_root_dir} 
        echo eos chmod 775 ${output_dir}/ECALTPGtree${addendum}_${run_num}.root
        $eos chmod 775 ${output_dir}/ECALTPGtree${addendum}_${run_num}.root
    	#rfchmod 775 ${output_dir}/ECALTPGtree_${addendum}_${run_num}.root
    else
   	 echo " using output dir "${output_dir}
    	#rfmkdir ${output_dir}
   	 #rfchmod 775 ${output_dir}
    	#rfcp ECALTPGtree_${addendum}_${run_num}.root ${output_dir}
   	 eosmkdir ${output_dir}
   	 eos chmod 775 ${output_dir}
    	xrdcp ECALTPGtree${addendum}_${run_num}.root ${output_dir} 
    	#rfchmod 775 ${output_dir}/ECALTPGtree_${addendum}_${run_num}.root
fi

size=`\ls -l ECALTPGtree${addendum}_${run_num}.root | grep -c ${run_num}`;
echo $size

