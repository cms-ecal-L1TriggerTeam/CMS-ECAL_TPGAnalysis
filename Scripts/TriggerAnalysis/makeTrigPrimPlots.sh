#!/bin/bash

usage='Usage: -r <run number> ( -d <eos dir> -l <html dir> -p <http dir> -e <EG trigger value for L1> )'

echo " "

args=`getopt rdlp: -- "$@"`
if test $? != 0
     then
         echo $usage
         exit 1
fi

eval set -- "$args"
for i
  do
    case "$i" in
      -r) shift; run=$2;shift;;
      -a) shift; ADDENDUM=$2;shift;;
      -d) shift; EOSDIR=$2;shift;;
      -l) shift; HTMLDIR=$2;shift;;
      -p) shift; HTTPDIR=$2;shift;;
      -e) shift; EG=$2;shift;;
      -tp) shift; TPcut=$2;shift;;
      -towers) shift; TOWERS=$2;shift;;
      -bcs) shift; BCS=$2;shift;;
      -orbits) shift; ORBITS=$2;shift;;
      -timestamps) shift; TIMESTAMPS=$2;shift;;
      -levent) shift; LEVENT=$2;shift;;
      -lumi) shift; LUMI=$2;shift;;
      -techtrig) shift; TECHTRIG=$2;shift;;
      -goodcoll) shift; GOODCOLL=$2;shift;;
      -firstEntry) shift; FIRSTENTRY=$2;shift;;
      -lastEntry) shift; LASTENTRY=$2;shift;;
    esac
done

#export SCRAM_ARCH=slc5_amd64_gcc434
source /afs/cern.ch/cms/LCG/LCG-2/UI/cms_ui_env.sh
eval `scramv1 runtime -sh`;

MYRELEASE=${CMSSW_BASE}

echo " My release path ${CMSSW_BASE} "

#TPGPLOTTINGDIR=${CMSSW_BASE}/src/CMS-ECAL_TPGAnalysis/TPGPlotting
TPGPLOTTINGDIR=${CMSSW_BASE}/src/CMS-ECAL_TPGAnalysis/TPGPlotting

echo "TPGPLOTTINGDIR ${TPGPLOTTINGDIR}"

APPENDIX=""
OPTIONS=""

if [ "X"${ADDENDUM} != "X" ]
    then
    ADDENDUM="_"$ADDENDUM     
fi

if [ "X"${EG} != "X" ] 
   then
   APPENDIX=$APPENDIX$ADDENDUM"_eg"$EG
   fi

if [ "X"${EG} == "X" ]
   then
   EG=12
   echo "using default EG trigger value for L1:" $EG
   APPENDIX=$APPENDIX$ADDENDUM"_eg"$EG
   fi

if [ "X"${TPcut} != "X" ]
   then
   APPENDIX=$APPENDIX"_tp_"$TPcut
   OPTIONS=$OPTIONS" -th1 "$TPcut
   fi
   
if [ "X"${TOWERS} != "X" ]
    then
    APPENDIX=$APPENDIX"_towers_"$TOWERS
    OPTIONS=$OPTIONS" -towers "$TOWERS
fi

if [ "X"${TECHTRIG} != "X" ]
    then
    APPENDIX=$APPENDIX"_techtrig_"$TECHTRIG
    OPTIONS=$OPTIONS" -techtrig "$TECHTRIG
fi

if [ "X"${GOODCOLL} != "X" ]
    then
    APPENDIX=$APPENDIX"_goodcoll_"$GOODCOLL
    OPTIONS=$OPTIONS" -goodcoll "$GOODCOLL
fi

if [ "X"${BCS} != "X" ]
    then
    APPENDIX=$APPENDIX"_bcs_"$BCS
    OPTIONS=$OPTIONS" -bcs "$BCS
fi

if [ "X"${ORBITS} != "X" ]
    then
    APPENDIX=$APPENDIX"_orbits_"$ORBITS
    OPTIONS=$OPTIONS" -orbits "$ORBITS
fi

if [ "X"${TIMESTAMPS} != "X" ]
    then
    APPENDIX=$APPENDIX"_timestamps_"$TIMESTAMPS
    OPTIONS=$OPTIONS" -timestamps "$TIMESTAMPS
fi

if [ "X"${LEVENT} != "X" ]
    then
    APPENDIX=$APPENDIX"_levent_"$LEVENT
    OPTIONS=$OPTIONS" -levent "$LEVENT
fi

if [ "X"${LUMI} != "X" ]
   then
   APPENDIX=$APPENDIX"_lumi_"$LUMI
   OPTIONS=$OPTIONS" -lumi "$LUMI
fi
   
if [ "X"${FIRSTENTRY} != "X" ]
   then
   APPENDIX=$APPENDIX"_firstEntry_"$FIRSTENTRY
   OPTIONS=$OPTIONS" -firstEntry "$FIRSTENTRY
fi
   
   if [ "X"${LASTENTRY} != "X" ]
   then
   APPENDIX=$APPENDIX"_lastEntry_"$LASTENTRY
   OPTIONS=$OPTIONS" -lastEntry "$LASTENTRY
fi
   
if [ "X"${EOSDIR} == "X" ]
   then
   EOSDIR=/store/user/ndev/TPG/
   echo "using default EOSDIR:" $EOSDIR
fi
   
if [ "X"${HTMLDIR} == "X" ]
    then
   # HTMLDIR=/afs/cern.ch/user/c/ccecal/scratch0/www/TPGAnalysis/Commissioning2015
    HTMLDIR=${CMSSW_BASE}/src/CMS-ECAL_TPGAnalysis/Scripts/TriggerAnalysis/Commissioning2016
    echo "using default HTMLDIR:" $HTMLDIR
fi

if [ "X"${HTTPDIR} == "X" ]
    then
    HTTPDIR=/ndev/TPGAnalysis/2016/Beam
    echo "using default HTTPDIR:" $HTTPDIR
fi

mkdir -p tmpdir
echo "using appendix:" $APPENDIX
echo ""

#PFNDIR="/afs/cern.ch/user/n/ndev/CMSSW_7_4_10/src/CMS-ECAL_TPGAnalysis/Scripts/TriggerAnalysis"
#PFNDIR=`cmsPfn $EOSDIR`
PFNDIR="root://eoscms.cern.ch//eos/cms/store/user/ndev/TPG/ECALTPG_tree"

echo PFNDIR=$PFNDIR



cat > FixLimits.C <<EOFO
void FixLimits(){
  
  //TFile *_file0 = TFile::Open("root://eoscms.cern.ch//eos/cms/store/caf/user/taroni/TPG/ECALTPGtree_${run}.root");
/* TFile *_file0 = TFile::Open("root://eoscms.cern.ch//eos/cms/store/caf/user/ndev/TPG/ECALTPG_tree/ECALTPGtree_${run}.root");
  EcalTPGAnalysis->Draw("timeStamp/60>>h1"); // use time in minutes
  EcalTPGAnalysis->Draw("orbitNb/1000000>>h2"); // Scale by 10^6
  EcalTPGAnalysis->Draw("evtNb/1000000>>h3"); // Scale by 10^6
    
  std::cout 
    << "setTimeMax " << h1->GetXaxis()->GetXmax()
    << "\nsetTimeMin " << h1->GetXaxis()->GetXmin()
    << std::endl;

  std::cout 
    << "setOrbMax " << h2->GetXaxis()->GetXmax()
    << "\nsetOrbMin " << h2->GetXaxis()->GetXmin()
    << std::endl;

  std::cout 
    << "setEvtMax " << h3->GetXaxis()->GetXmax()
    << "\nsetEvtMin " << h3->GetXaxis()->GetXmin()
    << std::endl;*/

}

EOFO

echo "Processing FixLimits.C..."
root -l -b FixLimits.C > log.txt<<EOF
.q
EOF
#cat log.txt

MINEVT=`cat log.txt | grep setEvtMin`
for WORD in $MINEVT; do
    if [[ $WORD == [0-9,.]* ]] ; then
        MINevtVAL=$WORD
    fi
done

MAXEVT=`cat log.txt | grep setEvtMax`
for WORD in $MAXEVT; do
    if [[ $WORD == [0-9,.]* ]] ; then
        MAXevtVAL=$WORD
    fi
done

MINTIME=`cat log.txt | grep setTimeMin`
for WORD in $MINTIME; do
    if [[ $WORD == [0-9,.]* ]] ; then
        MINtimeVAL=$WORD
    fi
done

MAXTIME=`cat log.txt | grep setTimeMax`
for WORD in $MAXTIME; do
    if [[ $WORD == [0-9,.]* ]] ; then
        MAXtimeVAL=$WORD
    fi
done

MINORB=`cat log.txt | grep setOrbMin`
for WORD in $MINORB; do
    if [[ $WORD == [0-9,.]* ]] ; then
        MINorbVAL=$WORD
    fi
done

MAXORB=`cat log.txt | grep setOrbMax`
for WORD in $MAXORB; do
    if [[ $WORD == [0-9,.]* ]] ; then
        MAXorbVAL=$WORD
    fi
done

echo "   TimeMin="${MINTIME}
echo "   TimeMax="${MAXTIME}
echo "   OrbitMin="${MINORB}" (10^6)"
echo "   OrbitMax="${MAXORB}" (10^6)"
echo "   EventMin="${MINEVT}" (10^6)"
echo "   EventMax="${MAXEVT}" (10^6)"

rm FixLimits.C
rm log.txt
cat > tmpdir/plot_$run.sh << EOF0

cd  $MYRELEASE/src/
eval \`scramv1 runtime -sh\`;
cd -;
echo ""
echo "TPGTreeReader running on all triggers..."
echo ""
echo $ADDENDUM
echo ""
$MYRELEASE/bin/${SCRAM_ARCH}/TPGTreeReader -SLMinEvt $MINevtVAL -SLMaxEvt $MAXevtVAL -SLMinOrb $MINorbVAL -SLMaxOrb $MAXorbVAL -SLMaxTime $MAXtimeVAL -SLMinTime $MINtimeVAL -d $PFNDIR -i ECALTPGtree${ADDENDUM}_${run}.root -o newhistoTPG_$run$APPENDIX.root -l1bx 47,49,50,51,52,53  -g $TPGPLOTTINGDIR/plots/endcapGeometry.txt -EG $EG $OPTIONS
cmsStage -f newhistoTPG_$run$APPENDIX.root ${EOSDIR}histofiles/
mv newhistoTPG_$run$APPENDIX.root $TPGPLOTTINGDIR/plots/.
echo ""
echo "TPGTreeReader running on Ecal triggers..."
$MYRELEASE/bin/${SCRAM_ARCH}/TPGTreeReader -SLMinEvt $MINevtVAL -SLMaxEvt $MAXevtVAL -SLMinOrb $MINorbVAL -SLMaxOrb $MAXorbVAL -SLMaxTime $MAXtimeVAL -SLMinTime $MINtimeVAL -d $PFNDIR -i ECALTPGtree${ADDENDUM}_${run}.root -o newhistoTPG_Ecal_$run$APPENDIX.root -l1 47,49,50,51,52,53  -l1bx 47,49,50,51,52,53 -g $TPGPLOTTINGDIR/plots/endcapGeometry.txt -EG $EG $OPTIONS
cmsStage -f newhistoTPG_Ecal_$run$APPENDIX.root ${EOSDIR}histofiles/
mv newhistoTPG_Ecal_$run$APPENDIX.root $TPGPLOTTINGDIR/plots/.


echo ""
echo "Now producing plots..."
echo 'cd $TPGPLOTTINGDIR/plots'
echo 'in the TPGdirecotry?'
echo './makeTPGPlots.sh -r $run -l $HTMLDIR -p $HTTPDIR -e $EG -z $APPENDIX'
cd $TPGPLOTTINGDIR/plots
./makeTPGPlots.sh -r $run -l $HTMLDIR -p $HTTPDIR -e $EG -z $APPENDIX
EOF0

chmod +x tmpdir/plot_$run.sh
./tmpdir/plot_$run.sh
