#!/bin/bash

usage='Usage: -r <run number> '

args=`getopt rlp: -- "$@"`
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
      -l) shift; html_dir=$2;shift;;
      -p) shift; http_dir=$2;shift;;
      -z) shift; appendix=$2;shift;;
      -e) shift; eg=$2;shift;;
  esac      
done

echo 'Making TPG Webpages for ' ${run_num} 

if [ "X"${run_num} == "X" ]
    then
    echo "INVALID RUN NUMBER! Please give a valid run number!"
    echo $usage
    exit 
fi

if [ "X"${html_dir} == "X" ]
    then
    echo "using default html directory:"
    html_dir=/afs/cern.ch/work/n/ndev/CMSSW_7_5_6/src/CMS-ECAL_TPGAnalysis/Scripts/TriggerAnalysis/Commissioning2016
    echo $html_dir
fi

if [ "X"${http_dir} == "X" ]
    then
    echo "using default html directory:"
    http_dir=/ndev
    echo $http_dir
fi

if [ "X"${eg} == "X" ]
    then
    echo "using default EG trigger value for L1: EG2"
    eg=1
    echo $eg
fi

# you can also specify directories here


#html_dir='/afs/cern.ch/user/c/ccecal/scratch0/www/TPGAnalysis/EETriggerTests'
#http_dir='http://test-ecal-cosmics.web.cern.ch/test-ecal-cosmics/TPGAnalysis/EETriggerTests';

work_dir=`pwd`;
echo 'work_dir = ' $work_dir;

mkdir $html_dir/$run_num${appendix};
plots_dir=$html_dir/$run_num${appendix};

declare -i run_number_int=${run_num};
#echo $run_number_int;

echo
echo 'To make plots for all triggers, run in ROOT:'
echo '.x '${work_dir}'/DrawTPGplots.C("newhistoTPG_'${run_num}${appendix}'.root",'${run_number_int}',kTRUE,"png","'${html_dir}/${run_num}${appendix}'",0)'
echo 'To make plots for ECAL triggers, run in ROOT:'
echo '.x '${work_dir}'/DrawTPGplots.C("newhistoTPG_Ecal_'${run_num}${appendix}'.root",'${run_number_int}',kTRUE,"png","'${html_dir}/${run_num}${appendix}'",1)'
echo


# run root command in batch




root -b <<!

.x ${work_dir}/DrawTPGplots.C("newhistoTPG_${run_num}${appendix}.root",${run_number_int},kTRUE,"png","${html_dir}/${run_num}${appendix}",0)
.q
!

root -b <<!

.x ${work_dir}/DrawTPGplots.C("newhistoTPG_Ecal_${run_num}${appendix}.root",${run_number_int},kTRUE,"png","${html_dir}/${run_num}${appendix}",1)
.q
!

cd ${html_dir}/${run_num}${appendix}
#for f in *.png; do 

#export myfile=`echo $f | cut -d'.' -f1`
#convert -thumbnail x200 $f thumb_${myfile}.jpg ;

#done
cd -

#echo 'Making webpage for run' ${run_num} 

cat > ${plots_dir}/index.html <<EOF

<HTML>

<HEAD><TITLE>ECAL TPG Analysis Run ${run_num}</TITLE></HEAD>





 
<BODY link="Red">
<FONT color="Black">
 
<Center>
<h2><FONT color="Blue"> ECAL TPG Analysis </FONT></h2>
</Center>

<Center>
<h3> Run: <A href=http://cmsmon.cern.ch/cmsdb/servlet/RunSummary?RUN=${run_num}>${run_num}</A></h3>
</center>

<Center>
<h3><Center><A name="ALL"> L1 Candidates shown in plots below are the ones firing EG${eg} trigger.</A><BR></center> </h3><BR>
<h3><Center><A name="ALL"> Options used: ${appendix}.</A><BR></center> </h3>
</Center>




<head>
<style type="text/css">
p.outset {border-style:outset}
</style>
</head>
<Center>
<body>
<p class="outset"><A name="EB"><FONT color="Red"><FONT size = 8>ALL Triggers</FONT></A><BR></p>
</body>
</center>



<h5><FONT color="Black">More details on these plots can be found on the <A href=https://twiki.cern.ch/twiki/bin/view/CMS/EcalTPGPlotsExplanations>twiki page</A></FONT></h5>


<h5><FONT color="Black"> Legend for all plots:
<ol>
   <li>Vertical hatches show towers having cristals masked for readout (based on TTF value).</li>
   <li>Oblique hatches show towers being masked for the trigger.</li>
</ol>
</FONT>
</h5>

Jump to (for ALL TRIGGERS):<br>
<A href="#Info">General Run Info</A><BR>
<A href="#Spectra">TP Spectra</A><BR>
<A href="#Timing">Timing Occupancy</A><BR>
<A href="#TP">TP Occupancy</A><BR>
<A href="#Emul">TP Emulator Comparison</A><BR>
<A href="#L1I">Level 1 Trigger Comparisons (L1 Iso)</A><BR>
<A href="#L1ITiming">Level 1 Iso Timing</A><BR>
<A href="#L1N">Level 1 Trigger Comparisons (L1 Non Iso)</A><BR>
<A href="#L1NTiming">Level 1 Non Iso Timing</A><BR>
<A href="#LUMI">Lumisection plots</A><BR>
<A href="#TTF">TTF and Other Plots</A><BR>
<A href="#ECAL">JUMP TO ECAL TRIGGER PLOTS</A><BR>
<br>


<u><h3><A name="Info">General Run Info</A><BR></h3></u>

<h4><FONT color="Green"> Fired Triggers </FONT></h4>
<h5><FONT color="Black">These plots show the number of times triggers were fired.
<ol>
   <li>"Active Triggers Fired" means triggers for which the algo bit was "true", and enabled by the Global Trigger.</li>
   <li>"Triggers Fired (Before Matching)" means triggers for which the algo bit was "true".</li>
</ol>
</FONT>
</h5>


<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_triggerBit_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_triggerBit_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_FiredTriggers_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_FiredTriggers_0_${run_number_int}.jpg"> </A>

<h4><FONT color="Green"> Masked RCT Regions </FONT></h4>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_maskedRCTEB_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_maskedRCTEB_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_maskedRCTEEPlus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_maskedRCTEEPlus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_maskedRCTEEMinus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_maskedRCTEEMinus_0_${run_number_int}.jpg"> </A>


<u><h3><A name="Spectra">TP Spectra</A><BR></h3></u>

<h5><FONT color="Black"> Plot Descriptions (from left to right):
<ol>
   <li>Spectrum of Trigger Primitives in ADC counts (from 1 to 255)</li>
   <li>Spectrum of Emulated Trigger Primitives (assuming peak at 6th sample)</li>
   <li>Spectrum of Emulated Trigger Primitives (using the max of the 5 emulated TPs)</li>
   <li>2D Spectrum of Trigger Primitives (binned in Trigger Towers and averaged over the entire run)</li>
</ol>
</FONT>
</h5>

<h4><FONT color="Green"> BARREL </FONT></h4>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEB_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEB_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulEB_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulEB_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulMaxEB_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulMaxEB_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPspectrumMapEB_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPspectrumMapEB_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEB_Ratio_when_nonzerorealexists_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEB_Ratio_when_nonzerorealexists_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulEB_when_no_NZ_TPReal_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulEB_when_no_NZ_TPReal_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_Ratio_EB_whenTPRealexists_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_Ratio_EB_whenTPRealexists_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEtaEBmisSpec_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEtaEBmisSpec_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEB_fullReadout_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEB_fullReadout_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEB_noSpike_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEB_noSpike_0_${run_number_int}.jpg"> </A>




<h4><FONT color="Green"> Plus ENDCAP </FONT></h4>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEEPlus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEEPlus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulEEPlus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulEEPlus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulMaxEEPlus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulMaxEEPlus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPspectrumMapEEPlus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPspectrumMapEEPlus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEEPlus_Ratio_when_nonzerorealexists_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEEPlus_Ratio_when_nonzerorealexists_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulEEPlus_when_no_NZ_TPReal_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulEEPlus_when_no_NZ_TPReal_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_Ratio_EEPlus_whenTPRealexists_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_Ratio_EEPlus_whenTPRealexists_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEtaEEPlusmisSpec_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEtaEEPlusmisSpec_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEEPlus_fullReadout_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEEPlus_fullReadout_0_${run_number_int}.jpg"> </A>



<h4><FONT color="Green"> Minus ENDCAP </FONT></h4>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEEMinus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEEMinus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulEEMinus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulEEMinus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulMaxEEMinus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulMaxEEMinus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPspectrumMapEEMinus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPspectrumMapEEMinus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEEMinus_Ratio_when_nonzerorealexists_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEEMinus_Ratio_when_nonzerorealexists_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulEEMinus_when_no_NZ_TPReal_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulEEMinus_when_no_NZ_TPReal_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_Ratio_EEMinus_whenTPRealexists_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_Ratio_EEMinus_whenTPRealexists_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEtaEEMinusmisSpec_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEtaEEMinusmisSpec_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEEMinus_fullReadout_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEEMinus_fullReadout_0_${run_number_int}.jpg"> </A>



<u><h3><A name="Timing">Timing Occupancy</A><BR></h3></u>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TP_vs_bx_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TP_vs_bx_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmul_vs_bx_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmul_vs_bx_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_Orbit_vs_bx_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_Orbit_vs_bx_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TriggerBit_vs_bx_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TriggerBit_vs_bx_0_${run_number_int}.jpg"> </A>

<br>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyTP_vs_EvtNb_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyTP_vs_EvtNb_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_iEta_vs_Time_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_iEta_vs_Time_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_iPhi_vs_Time_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_iPhi_vs_Time_0_${run_number_int}.jpg"> </A>

<br>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_bx_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_bx_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_eventNb_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_eventNb_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_orbit_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_orbit_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TimeStamp_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TimeStamp_0_${run_number_int}.jpg"> </A>



<u><h3><A name="TP">TP Occupancy</A><BR></h3></u>

<h4><FONT color="Green"> BARREL </FONT></h4>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyTPEB_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyTPEB_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyTPEmulEB_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyTPEmulEB_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEtaEB_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEtaEB_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPPhiEB_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPPhiEB_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_EBoccupancy_ratio_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_EBoccupancy_ratio_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyTPEmulEB_when_no_real_NZ_TP_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyTPEmulEB_when_no_real_NZ_TP_0_${run_number_int}.jpg"> </A>

<h4><FONT color="Green"> Mismatch Plots Barrel: emulated tp is off by 2 bx</FONT></h4>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyTPEBmis_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyTPEBmis_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEtaEBmis_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEtaEBmis_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPPhiEBmis_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPPhiEBmis_0_${run_number_int}.jpg"> </A>


<h4><FONT color="Green"> Plus ENDCAP </FONT></h4>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyTPEEPlus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyTPEEPlus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyTPEmulEEPlus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyTPEmulEEPlus_0_${run_number_int}.jpg"> </A>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEtaEEPlus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEtaEEPlus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPPhiEEPlus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPPhiEEPlus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_EEPlusoccupancy_ratio_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_EEPlusoccupancy_ratio_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyTPEmulEEPlus_when_no_real_NZ_TP_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyTPEmulEB_when_no_real_NZ_TP_0_${run_number_int}.jpg"> </A>

<h4><FONT color="Green">  Mismatch Plots Plus ENDCAP: emulated tp is off by 2 bx </FONT></h4>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyTPEmulEEPlus_mis_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyTPEmulEEPlus_mis_0_${run_number_int}.jpg"> </A>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulEtaEEPlus_mis_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulEtaEEPlus_mis_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulPhiEEPlus_mis_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulPhiEEPlus_mis_0_${run_number_int}.jpg"> </A>



<h4><FONT color="Green"> Minus ENDCAP </FONT></h4>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyTPEEMinus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyTPEEMinus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyTPEmulEEMinus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyTPEmulEEMinus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEtaEEMinus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEtaEEMinus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPPhiEEMinus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPPhiEEMinus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_EEMinusoccupancy_ratio_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_EEMinusoccupancy_ratio_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyTPEmulEEMinus_when_no_real_NZ_TP_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyTPEmulEEMinus_when_no_real_NZ_TP_0_${run_number_int}.jpg"> </A>

<h4><FONT color="Green"> Mismatch Plots  Minus ENDCAP: emulated tp is off by 2 bx </FONT></h4>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyTPEmulEEMinus_mis_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyTPEmulEEMinus_mis_0_${run_number_int}.jpg"> </A>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulEtaEEMinus_mis_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulEtaEEMinus_mis_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulPhiEEMinus_mis_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulPhiEEMinus_mis_0_${run_number_int}.jpg"> </A>




<br/><A href="#ALL">BACK TO TOP (ALL TRIGGER PLOTS)</A><BR>


<u><h3><A name="Emul">TP Emulator Comparison</A><BR></h3></u>
<h5><FONT color="Black">For the comparison 2D plot:
<ol>
   <li>"green" = "good" (on-time and emulated E_T = data E_T)</li>
   <li>"yellow" = emulator 1 bunch crossing earlier than data</li>
   <li>"red" = emulator 2 bunch crossings earlier than data</li>
   <li>"blue" = emulator 1 bunch crossing later than data</li>
   <li>"purple" = emulator 2 bunch crossings later than data</li>
   <li>"grey" = no matching found, whatever bunch crossing considered</li>
   <li>"white" = no data</li>
</ol>
For each Trigger Tower the value shown on the plot is the most frequent one.
</FONT>
</h5>

<h5><FONT color="Black">Fraction of non-single timing: Fraction of cases where the comparison value is not the one from the <A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPMatchEmulEB2D_0_${run_number_int}.png>comparison plot</A>.</FONT></h5>

<h5><FONT color="Black">Fraction of matching to another BX: Fraction of cases where the comparison value is not the one from the <A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPMatchEmulEB2D_0_${run_number_int}.png>comparison plot</A> (excluding "grey" values).</FONT></h5>



<h4><FONT color="Green"> BARREL </FONT></h4>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPMatchEmulEB_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPMatchEmulEB_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulMaxIndexEB_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulMaxIndexEB_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPMatchEmulEB2D_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPMatchEmulEB2D_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPCompEmulEB_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPCompEmulEB_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPMatchFractionEB2D_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPMatchFractionEB2D_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPMatchFraction2EB2D_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPMatchFraction2EB2D_0_${run_number_int}.jpg"> </A>


<h4><FONT color="Green"> Plus ENDCAP </FONT></h4>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPMatchEmulEEPlus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPMatchEmulEEPlus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulMaxIndexEEPlus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulMaxIndexEEPlus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPMatchEmulEEPlus2D_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPMatchEmulEEPlus2D_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPCompEmulEEPlus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPCompEmulEEPlus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPMatchFractionEEPlus2D_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPMatchFractionEEPlus2D_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPMatchFraction2EEPlus2D_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPMatchFraction2EEPlus2D_0_${run_number_int}.jpg"> </A>


<h4><FONT color="Green"> Minus ENDCAP </FONT></h4>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPMatchEmulEEMinus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPMatchEmulEEMinus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulMaxIndexEEMinus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulMaxIndexEEMinus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPMatchEmulEEMinus2D_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPMatchEmulEEMinus2D_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPCompEmulEEMinus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPCompEmulEEMinus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPMatchFractionEEMinus2D_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPMatchFractionEEMinus2D_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPMatchFraction2EEMinus2D_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPMatchFraction2EEMinus2D_0_${run_number_int}.jpg"> </A>

<br/><A href="#ALL">BACK TO TOP (ALL TRIGGER PLOTS)</A><BR>


<u><h3><A name="L1I">Level 1 Trigger Comparisons (L1 Iso)</A><BR></h3></u>
<h5><FONT color="Black"> These plots concern Iso Candidates.</FONT></h5>
<h5><FONT color="Black">Calculation of the TP/(2*L1) ratio: expected value is 1 .</FONT></h5>
<h5><FONT color="Black">RCT masked regions can be found in <A href="#Info">General Run Info</A><BR>.</FONT></h5>

<h4><FONT color="Green"> BARREL </FONT></h4>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyL1IsoEB_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyL1IsoEB_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1FractionMissingTPIsoEB_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1FractionMissingTPIsoEB_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1TPCompIsoEB_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1TPCompIsoEB_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1RatioTPIsoEB_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1RatioTPIsoEB_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1FractionValueMismatchIsoEB_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1FractionValueMismatchIsoEB_0_${run_number_int}.jpg"> </A>

<h4><FONT color="Green"> Plus ENDCAP </FONT></h4>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyL1IsoEEPlus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyL1IsoEEPlus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1FractionMissingTPIsoEEPlus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1FractionMissingTPIsoEEPlus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1TPCompIsoEEPlus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1TPCompIsoEEPlus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1RatioTPIsoEEPlus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1RatioTPIsoEEPlus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1FractionValueMismatchIsoEEPlus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1FractionValueMismatchIsoEEPlus_0_${run_number_int}.jpg"> </A>

<h4><FONT color="Green"> Minus ENDCAP </FONT></h4>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyL1IsoEEMinus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyL1IsoEEMinus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1FractionMissingTPIsoEEMinus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1FractionMissingTPIsoEEMinus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1TPCompIsoEEMinus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1TPCompIsoEEMinus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1RatioTPIsoEEMinus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1RatioTPIsoEEMinus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1FractionValueMismatchIsoEEMinus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1FractionValueMismatchIsoEEMinus_0_${run_number_int}.jpg"> </A>



<u><h3><A name="L1ITiming">Level 1 Iso Timing</A><BR></h3></u>
<h5><FONT color="Black">These plots concern Iso Candidates.</FONT></h5>
<h5><FONT color="Black">Timing plot:
<ol>
   <li>negative value = pre-firing</li>
   <li>value 0 = on-time</li>
   <li>positive value = post-firing</li>
</ol>
</FONT>
</h5>
<h5><FONT color="Black">RCT masked regions can be found in <A href="#Info">General Run Info</A><BR>.</FONT></h5>

<h4><FONT color="Green"> ISOPTSPECTRUM </FONT></h4>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_ptisopostfiring_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_ptisopostfiring_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_ptisoprefiring_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_ptisoprefiring_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_ptisoontime_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_ptisoontime_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_ptnonisopostfiring_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_ptnonisopostfiring_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_ptnonisoprefiring_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_ptnonisoprefiring_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_ptnonisoontime_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_ptnonisoontime_0_${run_number_int}.jpg"> </A>






<h4><FONT color="Green"> BARREL </FONT></h4>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1IsotimingEB_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1IsotimingEB_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyL1preIsoEB_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyL1preIsoEB_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyL1postIsoEB_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyL1postIsoEB_0_${run_number_int}.jpg"> </A>

<h4><FONT color="Green"> Plus ENDCAP </FONT></h4>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1IsotimingEEPlus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1IsotimingEEPlus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyL1preIsoEEPlus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyL1preIsoEEPlus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyL1postIsoEEPlus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyL1postIsoEEPlus_0_${run_number_int}.jpg"> </A>


<h4><FONT color="Green"> Minus ENDCAP </FONT></h4>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1IsotimingEEMinus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1IsotimingEEMinus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyL1preIsoEEMinus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyL1preIsoEEMinus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyL1postIsoEEMinus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyL1postIsoEEMinus_0_${run_number_int}.jpg"> </A>

<br/><A href="#ALL">BACK TO TOP (ALL TRIGGER PLOTS)</A><BR>


<u><h3><A name="L1N">Level 1 Trigger Comparisons (L1 Non Iso)</A><BR></h3></u>
<h5><FONT color="Black">These plots concern Non Iso Candidates.</FONT></h5>
<h5><FONT color="Black">Calculation of the L1/TP ratio is in ADC counts: expected value is 0.5 (turquoise) (here TP=2*int(TP/2)).</FONT></h5>
<h5><FONT color="Black">RCT masked regions can be found in <A href="#Info">General Run Info</A><BR>.</FONT></h5>

<h4><FONT color="Green"> BARREL </FONT></h4>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyL1NonisoEB_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyL1NonisoEB_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1FractionMissingTPNonisoEB_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1FractionMissingTPNonisoEB_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1TPCompNonisoEB_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1TPCompNonisoEB_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1RatioTPNonisoEB_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1RatioTPNonisoEB_0_${run_number_int}.jpg"> </A>


<h4><FONT color="Green"> Plus ENDCAP </FONT></h4>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyL1NonisoEEPlus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyL1NonisoEEPlus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1FractionMissingTPNonisoEEPlus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1FractionMissingTPNonisoEEPlus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1TPCompNonisoEEPlus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1TPCompNonisoEEPlus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1RatioTPNonisoEEPlus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1RatioTPNonisoEEPlus_0_${run_number_int}.jpg"> </A>


<h4><FONT color="Green"> Minus ENDCAP </FONT></h4>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyL1NonisoEEMinus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyL1NonisoEEMinus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1FractionMissingTPNonisoEEMinus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1FractionMissingTPNonisoEEMinus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1TPCompNonisoEEMinus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1TPCompNonisoEEMinus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1RatioTPNonisoEEMinus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1RatioTPNonisoEEMinus_0_${run_number_int}.jpg"> </A>


<u><h3><A name="L1NTiming">Level 1 Non Iso Timing</A><BR></h3></u>
<h5><FONT color="Black">These plots concern Non Iso Candidates.</FONT></h5>
<h5><FONT color="Black">Timing plot:
<ol>
   <li>negative value = pre-firing</li>
   <li>value 0 = on-time</li>
   <li>positive value = post-firing</li>
</ol>
</FONT>
</h5>
<h5><FONT color="Black">RCT masked regions can be found in <A href="#Info">General Run Info</A><BR>.</FONT></h5>

<h4><FONT color="Green"> BARREL </FONT></h4>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1NonisotimingEB_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1NonisotimingEB_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyL1preNonisoEB_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyL1preNonisoEB_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyL1postNonisoEB_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyL1postNonisoEB_0_${run_number_int}.jpg"> </A>

<h4><FONT color="Green"> Plus ENDCAP </FONT></h4>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1NonisotimingEEPlus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1NonisotimingEEPlus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyL1preNonisoEEPlus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyL1preNonisoEEPlus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyL1postNonisoEEPlus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyL1postNonisoEEPlus_0_${run_number_int}.jpg"> </A>

<h4><FONT color="Green"> Minus ENDCAP </FONT></h4>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1NonisotimingEEMinus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1NonisotimingEEMinus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyL1preNonisoEEMinus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyL1preNonisoEEMinus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyL1postNonisoEEMinus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyL1postNonisoEEMinus_0_${run_number_int}.jpg"> </A>

<br/><A href="#ALL">BACK TO TOP (ALL TRIGGER PLOTS)</A><BR>

<u><h3><A name="LUMI">Lumisection Plots</A><BR></h3></u>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_LumiSection_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_LumiSection_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_Lumi2D_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_Lumi2D_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_iEta_vs_LS_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_iEta_vs_LS_0_${run_number_int}.jpg"> </A> 
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_iPhi_vs_LS_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_iPhi_vs_LS_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_ttfstatus_all_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_ttfstatus_all_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_ttfstatus_vs_LS_all_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_ttfstatus_vs_LS_all_0_${run_number_int}.jpg"> </A



<u><h3><A name="TTF">TTF and FG</A><BR></h3></u>
<h5><FONT color="Black">TTF Mismatch: TTF code required all read-out, but not all towers were read out.</FONT></h5>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_ttfMismatchEB_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_ttfMismatchEB_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_ttfMismatchEEPlus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_ttfMismatchEEPlus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_ttfMismatchEEMinus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_ttfMismatchEEMinus_0_${run_number_int}.jpg"> </A>


<u><h3>Emulated TP in right timing</h3></u>
<h5><FONT color="Black">Occupancy of emulated TP for which the index of maximum E_T is 3.</FONT></h5>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPTimingEBFromEmulOK_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPTimingEBFromEmulOK_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPTimingEEPlusFromEmulOK_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPTimingEEPlusFromEmulOK_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPTimingEEMinusFromEmulOK_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPTimingEEMinusFromEmulOK_0_${run_number_int}.jpg"> </A>


<u><h3>Emulated TP in right timing and matching with data</h3></u>
<h5><FONT color="Black">Occupancy of emulated TP for which the index of maximum E_T is 3, matching the TP data.</FONT></h5>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPTimingEBFromEmulOKAndMatch_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPTimingEBFromEmulOKAndMatch_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPTimingEEPlusFromEmulOKAndMatch_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPTimingEEPlusFromEmulOKAndMatch_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPTimingEEMinusFromEmulOKAndMatch_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPTimingEEMinusFromEmulOKAndMatch_0_${run_number_int}.jpg"> </A>


<u><h3>Emulated TP in wrong timing</h3></u>
<h5><FONT color="Black">Occupancy of emulated TP for which the index of maximum E_T is NOT 3.</FONT></h5>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPTimingEBFromEmulWrong_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPTimingEBFromEmulWrong_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPTimingEEPlusFromEmulWrong_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPTimingEEPlusFromEmulWrong_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPTimingEEMinusFromEmulWrong_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPTimingEEMinusFromEmulWrong_0_${run_number_int}.jpg"> </A>



<u><h3>Map of maximum index and its value (emulated TP)</h3></u>
<h5><FONT color="Black">Index of the emulated TP with largest E_T.</FONT></h5>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulMapMaxIndexEB_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulMapMaxIndexEB_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulMapMaxIndexEEPlus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulMapMaxIndexEEPlus_0_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulMapMaxIndexEEMinus_0_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulMapMaxIndexEEMinus_0_${run_number_int}.jpg"> </A>


<Center><A name="ECAL">---</A><BR></center>


<head>
<style type="text/css">
p.outset {border-style:outset}
</style>
</head>
<Center>
<body>
<p class="outset"><A name="EB"><FONT color="Red"><FONT size = 8>ECAL Triggers</FONT></A><BR></p>
</body>
</center>

Jump to (for ECAL TRIGGERS):<br>
<A href="#Spectra1">TP Spectra</A><BR>
<A href="#Timing1">Timing Occupancy</A><BR>
<A href="#TP1">TP Occupancy</A><BR>
<A href="#Emul1">TP Emulator Comparison</A><BR>
<A href="#L1I1">Level 1 Trigger Comparisons (L1 Iso)</A><BR>
<A href="#L1ITiming1">Level 1 Iso Timing</A><BR>
<A href="#L1N1">Level 1 Trigger Comparisons (L1 Non Iso)</A><BR>
<A href="#L1NTiming1">Level 1 Non Iso Timing</A><BR>
<A href="#TTF1">TTF and Other Plots</A><BR>
<A href="#ALL">BACK TO ALL TRIGGER PLOTS</A><BR>
<br>


<u><h3><A name="Spectra1">TP Spectra</h3></A><BR></u>
<h5><FONT color="Black"> Plot Descriptions (from left to right):
<ol>
   <li>Spectrum of Trigger Primitives in ADC counts (from 1 to 255)</li>
   <li>Spectrum of Emulated Trigger Primitives (assuming peak at 6th sample)</li>
   <li>Spectrum of Emulated Trigger Primitives (using the max of the 5 emulated TPs)</li>
   <li>2D Spectrum of Trigger Primitives (binned in Trigger Towers and averaged over the entire run)</li>
</ol>
</FONT>
</h5>

<h4><FONT color="Green"> BARREL </FONT></h4>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEB_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEB_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulEB_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulEB_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulMaxEB_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulMaxEB_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPspectrumMapEB_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPspectrumMapEB_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEB_Ratio_when_nonzerorealexists_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEB_Ratio_when_nonzerorealexists_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulEB_when_no_NZ_TPReal_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulEB_when_no_NZ_TPReal_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_Ratio_EB_whenTPRealexists_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_Ratio_EB_whenTPRealexists_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEtaEBmisSpec_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEtaEBmisSpec_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEB_fullReadout_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEB_fullReadout_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEB_noSpike_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEB_noSpike_1_${run_number_int}.jpg"> </A>


<h4><FONT color="Green"> Plus ENDCAP </FONT></h4>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEEPlus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEEPlus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulEEPlus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulEEPlus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulMaxEEPlus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulMaxEEPlus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPspectrumMapEEPlus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPspectrumMapEEPlus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEEPlus_Ratio_when_nonzerorealexists_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEEPlus_Ratio_when_nonzerorealexists_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulEEPlus_when_no_NZ_TPReal_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulEEPlus_when_no_NZ_TPReal_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_Ratio_EEPlus_whenTPRealexists_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_Ratio_EEPlus_whenTPRealexists_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEtaEEPlusmisSpec_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEtaEEPlusmisSpec_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEEPlus_fullReadout_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEEPlus_fullReadout_1_${run_number_int}.jpg"> </A>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEEMinus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEEMinus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulEEMinus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulEEMinus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulMaxEEMinus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulMaxEEMinus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPspectrumMapEEMinus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPspectrumMapEEMinus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEEMinus_Ratio_when_nonzerorealexists_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEEMinus_Ratio_when_nonzerorealexists_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulEEMinus_when_no_NZ_TPReal_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulEEMinus_when_no_NZ_TPReal_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_Ratio_EEMinus_whenTPRealexists_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_Ratio_EEMinus_whenTPRealexists_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEtaEEMinusmisSpec_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEtaEEMinusmisSpec_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEEMinus_fullReadout_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEEMinus_fullReadout_1_${run_number_int}.jpg"> </A>




<br/><A href="#ALL">BACK TO TOP (ALL TRIGGER PLOTS)</A><BR>


<u><h3><A name="Timing">Timing Occupancy</A><BR></h3></u>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TP_vs_bx_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TP_vs_bx_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmul_vs_bx_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmul_vs_bx_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_Orbit_vs_bx_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_Orbit_vs_bx_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TriggerBit_vs_bx_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TriggerBit_vs_bx_1_${run_number_int}.jpg"> </A>

<br>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyTP_vs_EvtNb_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyTP_vs_EvtNb_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_iEta_vs_Time_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_iEta_vs_Time_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_iPhi_vs_Time_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_iPhi_vs_Time_1_${run_number_int}.jpg"> </A>

<br>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_bx_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_bx_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_eventNb_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_eventNb_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_orbit_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_orbit_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TimeStamp_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TimeStamp_1_${run_number_int}.jpg"> </A>



<u><h3><A name="TP">TP Occupancy</A><BR></h3></u>

<h4><FONT color="Green"> BARREL </FONT></h4>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyTPEB_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyTPEB_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyTPEmulEB_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyTPEmulEB_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEtaEB_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEtaEB_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPPhiEB_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPPhiEB_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_EBoccupancy_ratio_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_EBoccupancy_ratio_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyTPEmulEB_when_no_real_NZ_TP_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyTPEmulEB_when_no_real_NZ_TP_1_${run_number_int}.jpg"> </A>

<h4><FONT color="Green"> Mismatch Plots Barrel:emulated tp is off by 2bx</FONT></h4>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyTPEBmis_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyTPEBmis_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEtaEBmis_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEtaEBmis_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPPhiEBmis_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPPhiEBmis_1_${run_number_int}.jpg"> </A>


<h4><FONT color="Green"> Plus ENDCAP </FONT></h4>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyTPEEPlus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyTPEEPlus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyTPEmulEEPlus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyTPEmulEEPlus_1_${run_number_int}.jpg"> </A>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEtaEEPlus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEtaEEPlus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPPhiEEPlus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPPhiEEPlus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_EEPlusoccupancy_ratio_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_EEPlusoccupancy_ratio_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyTPEmulEEPlus_when_no_real_NZ_TP_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyTPEmulEB_when_no_real_NZ_TP_1_${run_number_int}.jpg"> </A>

<h4><FONT color="Green">  Mismatch Plots  Plus ENDCAP:emulated tp is off by 2bx </FONT></h4>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyTPEmulEEPlus_mis_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyTPEmulEEPlus_mis_1_${run_number_int}.jpg"> </A>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulEtaEEPlus_mis_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulEtaEEPlus_mis_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulPhiEEPlus_mis_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulPhiEEPlus_mis_1_${run_number_int}.jpg"> </A>



<h4><FONT color="Green"> Minus ENDCAP </FONT></h4>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyTPEEMinus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyTPEEMinus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyTPEmulEEMinus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyTPEmulEEMinus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEtaEEMinus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEtaEEMinus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPPhiEEMinus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPPhiEEMinus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_EEMinusoccupancy_ratio_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_EEMinusoccupancy_ratio_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyTPEmulEEMinus_when_no_real_NZ_TP_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyTPEmulEEMinus_when_no_real_NZ_TP_1_${run_number_int}.jpg"> </A>

<h4><FONT color="Green">  Mismatch Plots  Minus ENDCAP:emulated tp is off by 2bx </FONT></h4>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyTPEmulEEMinus_mis_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyTPEmulEEMinus_mis_1_${run_number_int}.jpg"> </A>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulEtaEEMinus_mis_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulEtaEEMinus_mis_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulPhiEEMinus_mis_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulPhiEEMinus_mis_1_${run_number_int}.jpg"> </A>




<br/><A href="#ALL">BACK TO TOP (ALL TRIGGER PLOTS)</A><BR>


<u><h3><A name="Emul">TP Emulator Comparison</A><BR></h3></u>
<h5><FONT color="Black">For the comparison 2D plot:
<ol>
   <li>"green" = "good" (on-time and emulated E_T = data E_T)</li>
   <li>"yellow" = emulator 1 bunch crossing earlier than data</li>
   <li>"red" = emulator 2 bunch crossings earlier than data</li>
   <li>"blue" = emulator 1 bunch crossing later than data</li>
   <li>"purple" = emulator 2 bunch crossings later than data</li>
   <li>"grey" = no matching found, whatever bunch crossing considered</li>
   <li>"white" = no data</li>
</ol>
For each Trigger Tower the value shown on the plot is the most frequent one.
</FONT>
</h5>

<h5><FONT color="Black">Fraction of non-single timing: Fraction of cases where the comparison value is not the one from the <A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPMatchEmulEB2D_1_${run_number_int}.png>comparison plot</A>.</FONT></h5>

<h5><FONT color="Black">Fraction of matching to another BX: Fraction of cases where the comparison value is not the one from the <A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPMatchEmulEB2D_1_${run_number_int}.png>comparison plot</A> (excluding "grey" values).</FONT></h5>



<h4><FONT color="Green"> BARREL </FONT></h4>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPMatchEmulEB_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPMatchEmulEB_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulMaxIndexEB_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulMaxIndexEB_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPMatchEmulEB2D_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPMatchEmulEB2D_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPCompEmulEB_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPCompEmulEB_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPMatchFractionEB2D_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPMatchFractionEB2D_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPMatchFraction2EB2D_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPMatchFraction2EB2D_1_${run_number_int}.jpg"> </A>


<h4><FONT color="Green"> Plus ENDCAP </FONT></h4>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPMatchEmulEEPlus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPMatchEmulEEPlus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulMaxIndexEEPlus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulMaxIndexEEPlus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPMatchEmulEEPlus2D_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPMatchEmulEEPlus2D_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPCompEmulEEPlus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPCompEmulEEPlus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPMatchFractionEEPlus2D_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPMatchFractionEEPlus2D_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPMatchFraction2EEPlus2D_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPMatchFraction2EEPlus2D_1_${run_number_int}.jpg"> </A>


<h4><FONT color="Green"> Minus ENDCAP </FONT></h4>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPMatchEmulEEMinus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPMatchEmulEEMinus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulMaxIndexEEMinus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulMaxIndexEEMinus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPMatchEmulEEMinus2D_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPMatchEmulEEMinus2D_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPCompEmulEEMinus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPCompEmulEEMinus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPMatchFractionEEMinus2D_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPMatchFractionEEMinus2D_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPMatchFraction2EEMinus2D_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPMatchFraction2EEMinus2D_1_${run_number_int}.jpg"> </A>

<br/><A href="#ALL">BACK TO TOP (ALL TRIGGER PLOTS)</A><BR>


<u><h3><A name="L1I">Level 1 Trigger Comparisons (L1 Iso)</A><BR></h3></u>
<h5><FONT color="Black"> These plots concern Iso Candidates.</FONT></h5>
<h5><FONT color="Black">Calculation of the L1/TP ratio is in ADC counts: expected value is 0.5 (turquoise) (here TP=2*int(TP/2)).</FONT></h5>
<h5><FONT color="Black">RCT masked regions can be found in <A href="#Info">General Run Info</A><BR>.</FONT></h5>

<h4><FONT color="Green"> BARREL </FONT></h4>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyL1IsoEB_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyL1IsoEB_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1FractionMissingTPIsoEB_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1FractionMissingTPIsoEB_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1TPCompIsoEB_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1TPCompIsoEB_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1RatioTPIsoEB_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1RatioTPIsoEB_1_${run_number_int}.jpg"> </A>


<h4><FONT color="Green"> Plus ENDCAP </FONT></h4>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyL1IsoEEPlus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyL1IsoEEPlus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1FractionMissingTPIsoEEPlus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1FractionMissingTPIsoEEPlus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1TPCompIsoEEPlus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1TPCompIsoEEPlus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1RatioTPIsoEEPlus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1RatioTPIsoEEPlus_1_${run_number_int}.jpg"> </A>


<h4><FONT color="Green"> Minus ENDCAP </FONT></h4>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyL1IsoEEMinus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyL1IsoEEMinus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1FractionMissingTPIsoEEMinus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1FractionMissingTPIsoEEMinus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1TPCompIsoEEMinus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1TPCompIsoEEMinus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1RatioTPIsoEEMinus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1RatioTPIsoEEMinus_1_${run_number_int}.jpg"> </A>


<u><h3><A name="L1ITiming">Level 1 Iso Timing</A><BR></h3></u>
<h5><FONT color="Black">These plots concern Iso Candidates.</FONT></h5>
<h5><FONT color="Black">Timing plot:
<ol>
   <li>negative value = pre-firing</li>
   <li>value 0 = on-time</li>
   <li>positive value = post-firing</li>
</ol>
</FONT>
</h5>
<h5><FONT color="Black">RCT masked regions can be found in <A href="#Info">General Run Info</A><BR>.</FONT></h5>

<h4><FONT color="Green"> BARREL </FONT></h4>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1IsotimingEB_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1IsotimingEB_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyL1preIsoEB_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyL1preIsoEB_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyL1postIsoEB_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyL1postIsoEB_1_${run_number_int}.jpg"> </A>

<h4><FONT color="Green"> Plus ENDCAP </FONT></h4>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1IsotimingEEPlus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1IsotimingEEPlus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyL1preIsoEEPlus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyL1preIsoEEPlus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyL1postIsoEEPlus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyL1postIsoEEPlus_1_${run_number_int}.jpg"> </A>



<h4><FONT color="Green"> Minus ENDCAP </FONT></h4>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1IsotimingEEMinus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1IsotimingEEMinus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyL1preIsoEEMinus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyL1preIsoEEMinus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyL1postIsoEEMinus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyL1postIsoEEMinus_1_${run_number_int}.jpg"> </A>

<br/><A href="#ALL">BACK TO TOP (ALL TRIGGER PLOTS)</A><BR>


<u><h3><A name="L1N">Level 1 Trigger Comparisons (L1 Non Iso)</A><BR></h3></u>
<h5><FONT color="Black">These plots concern Non Iso Candidates.</FONT></h5>
<h5><FONT color="Black">Calculation of the L1/TP ratio is in ADC counts: expected value is 0.5 (turquoise) (here TP=2*int(TP/2)).</FONT></h5>
<h5><FONT color="Black">RCT masked regions can be found in <A href="#Info">General Run Info</A><BR>.</FONT></h5>

<h4><FONT color="Green"> BARREL </FONT></h4>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyL1NonisoEB_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyL1NonisoEB_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1FractionMissingTPNonisoEB_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1FractionMissingTPNonisoEB_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1TPCompNonisoEB_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1TPCompNonisoEB_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1RatioTPNonisoEB_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1RatioTPNonisoEB_1_${run_number_int}.jpg"> </A>


<h4><FONT color="Green"> Plus ENDCAP </FONT></h4>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyL1NonisoEEPlus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyL1NonisoEEPlus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1FractionMissingTPNonisoEEPlus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1FractionMissingTPNonisoEEPlus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1TPCompNonisoEEPlus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1TPCompNonisoEEPlus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1RatioTPNonisoEEPlus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1RatioTPNonisoEEPlus_1_${run_number_int}.jpg"> </A>


<h4><FONT color="Green"> Minus ENDCAP </FONT></h4>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyL1NonisoEEMinus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyL1NonisoEEMinus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1FractionMissingTPNonisoEEMinus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1FractionMissingTPNonisoEEMinus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1TPCompNonisoEEMinus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1TPCompNonisoEEMinus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1RatioTPNonisoEEMinus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1RatioTPNonisoEEMinus_1_${run_number_int}.jpg"> </A>


<u><h3><A name="L1NTiming">Level 1 Non Iso Timing</A><BR></h3></u>
<h5><FONT color="Black">These plots concern Non Iso Candidates.</FONT></h5>
<h5><FONT color="Black">Timing plot:
<ol>
   <li>negative value = pre-firing</li>
   <li>value 0 = on-time</li>
   <li>positive value = post-firing</li>
</ol>
</FONT>
</h5>
<h5><FONT color="Black">RCT masked regions can be found in <A href="#Info">General Run Info</A><BR>.</FONT></h5>

<h4><FONT color="Green"> BARREL </FONT></h4>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1NonisotimingEB_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1NonisotimingEB_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyL1preNonisoEB_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyL1preNonisoEB_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyL1postNonisoEB_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyL1postNonisoEB_1_${run_number_int}.jpg"> </A>

<h4><FONT color="Green"> Plus ENDCAP </FONT></h4>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1NonisotimingEEPlus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1NonisotimingEEPlus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyL1preNonisoEEPlus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyL1preNonisoEEPlus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyL1postNonisoEEPlus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyL1postNonisoEEPlus_1_${run_number_int}.jpg"> </A>

<h4><FONT color="Green"> Minus ENDCAP </FONT></h4>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_L1NonisotimingEEMinus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_L1NonisotimingEEMinus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyL1preNonisoEEMinus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyL1preNonisoEEMinus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_occupancyL1postNonisoEEMinus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_occupancyL1postNonisoEEMinus_1_${run_number_int}.jpg"> </A>

<br/><A href="#ALL">BACK TO TOP (ALL TRIGGER PLOTS)</A><BR>


<u><h3><A name="TTF">TTF and FG</A><BR></h3></u>
<h5><FONT color="Black">TTF Mismatch: TTF code required all read-out, but not all towers were read out.</FONT></h5>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_ttfMismatchEB_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_ttfMismatchEB_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_ttfMismatchEEPlus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_ttfMismatchEEPlus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_ttfMismatchEEMinus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_ttfMismatchEEMinus_1_${run_number_int}.jpg"> </A>


<u><h3>Emulated TP in right timing</h3></u>
<h5><FONT color="Black">Occupancy of emulated TP for which the index of maximum E_T is 3.</FONT></h5>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPTimingEBFromEmulOK_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPTimingEBFromEmulOK_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPTimingEEPlusFromEmulOK_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPTimingEEPlusFromEmulOK_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPTimingEEMinusFromEmulOK_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPTimingEEMinusFromEmulOK_1_${run_number_int}.jpg"> </A>


<u><h3>Emulated TP in right timing and matching with data</h3></u>
<h5><FONT color="Black">Occupancy of emulated TP for which the index of maximum E_T is 3, matching the TP data.</FONT></h5>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPTimingEBFromEmulOKAndMatch_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPTimingEBFromEmulOKAndMatch_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPTimingEEPlusFromEmulOKAndMatch_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPTimingEEPlusFromEmulOKAndMatch_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPTimingEEMinusFromEmulOKAndMatch_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPTimingEEMinusFromEmulOKAndMatch_1_${run_number_int}.jpg"> </A>


<u><h3>Emulated TP in wrong timing</h3></u>
<h5><FONT color="Black">Occupancy of emulated TP for which the index of maximum E_T is NOT 3.</FONT></h5>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPTimingEBFromEmulWrong_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPTimingEBFromEmulWrong_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPTimingEEPlusFromEmulWrong_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPTimingEEPlusFromEmulWrong_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPTimingEEMinusFromEmulWrong_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPTimingEEMinusFromEmulWrong_1_${run_number_int}.jpg"> </A>



<u><h3>Map of maximum index and its value (emulated TP)</h3></u>
<h5><FONT color="Black">Index of the emulated TP with largest E_T.</FONT></h5>

<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulMapMaxIndexEB_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulMapMaxIndexEB_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulMapMaxIndexEEPlus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulMapMaxIndexEEPlus_1_${run_number_int}.jpg"> </A>
<A HREF=${http_dir}/${run_num}$appendix/TPGAnalysis_TPEmulMapMaxIndexEEMinus_1_${run_number_int}.png> <img height="200" src="${http_dir}/${run_num}$appendix/thumb_TPGAnalysis_TPEmulMapMaxIndexEEMinus_1_${run_number_int}.jpg"> </A>







<head>
<style type="text/css">
p.double {border-style:double}
</style>
</head>
<Center>
<body>
<p class="double"><A name="EB"><FONT color="Red"><FONT size = 4>ROOT Files Download</FONT></A><BR></p>
</body>
</center>




<h4> ALL Trigger ROOT File </h4>
<h5><FONT color="Black">On lxplus: rfcp /castor/cern.ch/user/c/ccecal/TPG/plots/histoTPG_${run_num}${appendix}.root . </FONT></h5>
<h4> ECAL Trigger ROOT File </h4>
<h5><FONT color="Black">On lxplus: rfcp /castor/cern.ch/user/c/ccecal/TPG/plots/histoTPG_Ecal_${run_num}${appendix}.root . </FONT></h5>


</FONT>
</BODY>
</HTML>

EOF

pwd
ls -ltr

#rfcp histoTPG_${run_num}${appendix}.root /castor/cern.ch/user/c/ccecal/TPG/plots/histoTPG_${run_num}${appendix}.root
#rfcp histoTPG_Ecal_${run_num}${appendix}.root /castor/cern.ch/user/c/ccecal/TPG/plots/histoTPG_Ecal_${run_num}${appendix}.root

mkdir ${run_num}

mv newhistoTPG_${run_num}${appendix}.root  ${run_num}
mv newhistoTPG_Ecal_${run_num}${appendix}.root  ${run_num}

exit
EOF
