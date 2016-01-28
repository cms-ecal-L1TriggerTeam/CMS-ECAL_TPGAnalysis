#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <map>
#include <boost/tokenizer.hpp>
#include <vector>

#include <TChain.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TProfile2D.h>

using  namespace std;

int *unhashTr(int value)
{
  size_t mysize = 5;
  int *coef=new int[mysize];
  for (size_t a=0;a<mysize;a++) coef[a] = 0;
   
  if ( value/10000 == 1 ) coef[0] = 1;
  if ( coef[0] == 1 ) value = value - 10000;
   
  if ( value/1000 == 1 ) coef[1] = 1;
  if ( coef[1] == 1 ) value = value - 1000;
   
  if ( value/100 == 1 ) coef[2] = 1;
  if ( coef[2] == 1 ) value = value - 100;
   
  if ( value/10 == 1 ) coef[3] = 1;
  if ( coef[3] == 1 ) value = value - 10;
   
  if ( value/1 == 1 ) coef[4] = 1;
   
  return coef;
}



struct EcalAux
{
  int iMaskedTTeta[100];
  int iMaskedTTphi[100];
  int nMaskedCh;
  int runNb;
  int iMaskedChannelsFromStripsX[500];
  int iMaskedChannelsFromStripsY[500];
  int iMaskedChannelsFromStripsZ[500];
  int nMaskedChannelsFromStrips;
};




struct EcalTPGVariables
{
   
  // event variables
  uint runNb ;
  ULong64_t evtNb ;
  uint bxNb ;
  uint lumiBlock ;
  ULong64_t orbitNb ;
  double timeStamp ; 
  uint nbOfActiveTriggers ;
  uint nbOfActiveTriggersBX ;
   
  int activeTriggers[128] ;
  int activeTriggersBX[128] ;
   
  int activeTechTriggers[64] ;
  uint nbOfActiveTechTriggers ;
   
  // tower variables
  uint nbOfTowers ; //max 4032 EB+EE
  int ieta[4032] ;
  int iphi[4032] ;
  int nbOfXtals[4032] ;
  int rawTPData[4032] ;
  int rawTPEmul1[4032] ;
  int rawTPEmul2[4032] ;
  int rawTPEmul3[4032] ;
  int rawTPEmul4[4032] ;
  int rawTPEmul5[4032] ;
  int rawTPEmulttFlag1[4032] ;
  int rawTPEmulttFlag2[4032] ;
  int rawTPEmulttFlag3[4032] ;
  int rawTPEmulttFlag4[4032] ;
  int rawTPEmulttFlag5[4032] ;
  int rawTPEmulsFGVB1[4032] ;
  int rawTPEmulsFGVB2[4032] ;
  int rawTPEmulsFGVB3[4032] ;
  int rawTPEmulsFGVB4[4032] ;
  int rawTPEmulsFGVB5[4032] ;
  
  float eRec[4032] ;
  int crystNb[4032] ;
  int spike[4032] ;
  int sevlv[4032];
  int ttFlag[4032];
  int trig_tower_adc[4032], trig_tower_sFGVB[4032]; 

   
  uint nMaskedRCT ;
  int iMaskedRCTeta[100] ;
  int iMaskedRCTphi[100] ;
  int iMaskedRCTcrate[100] ;
   
  uint nbOfL1IsoCands ;
  int L1IsoIeta[4] ;
  int L1IsoIphi[4] ;
  int L1IsoRank[4] ; 
  uint nbOfL1NonisoCands ;
  int L1NonisoIeta[4] ;
  int L1NonisoIphi[4] ;
  int L1NonisoRank[4] ; 
   
  uint nbOfL1preIsoCands ;
  int L1preIsoIeta[4] ;
  int L1preIsoIphi[4] ;
  int L1preIsoRank[4] ; 
  uint nbOfL1preNonisoCands ;
  int L1preNonisoIeta[4] ;
  int L1preNonisoIphi[4] ;
  int L1preNonisoRank[4] ; 
   
  uint nbOfL1postIsoCands ;
  int L1postIsoIeta[4] ;
  int L1postIsoIphi[4] ;
  int L1postIsoRank[4] ; 
  uint nbOfL1postNonisoCands ;
  int L1postNonisoIeta[4] ;
  int L1postNonisoIphi[4] ;
  int L1postNonisoRank[4] ; 
   
} ;




void setBranchAddresses (TChain * chain, EcalTPGVariables & treeVars)
{ //chain->SetBranchAddress ("runNb",&treeVars.runNb) ; 
  chain->SetBranchAddress ("evtNb",&treeVars.evtNb) ; 
  chain->SetBranchAddress ("bxNb",&treeVars.bxNb) ; 
  chain->SetBranchAddress ("lumiBlock",&treeVars.lumiBlock) ;
  chain->SetBranchAddress ("orbitNb",&treeVars.orbitNb) ; 
  chain->SetBranchAddress ("timeStamp",&treeVars.timeStamp) ; 
  chain->SetBranchAddress ("nbOfActiveTriggers",&treeVars.nbOfActiveTriggers) ; 
  chain->SetBranchAddress ("activeTriggers",treeVars.activeTriggers) ; 
  chain->SetBranchAddress ("activeTriggersBX",treeVars.activeTriggersBX) ;
   
  chain->SetBranchAddress ("nbOfActiveTechTriggers",&treeVars.nbOfActiveTechTriggers) ; 
  chain->SetBranchAddress ("activeTechTriggers",treeVars.activeTechTriggers) ; 
   
  chain->SetBranchAddress ("nbOfTowers",&treeVars.nbOfTowers) ; 
  chain->SetBranchAddress ("ieta",treeVars.ieta) ; 
  chain->SetBranchAddress ("iphi",treeVars.iphi) ; 
  chain->SetBranchAddress ("nbOfXtals",treeVars.nbOfXtals) ; 
  chain->SetBranchAddress ("rawTPData",treeVars.rawTPData) ; 
  chain->SetBranchAddress ("rawTPEmul1",treeVars.rawTPEmul1) ; 
  chain->SetBranchAddress ("rawTPEmul2",treeVars.rawTPEmul2) ; 
  chain->SetBranchAddress ("rawTPEmul3",treeVars.rawTPEmul3) ; 
  chain->SetBranchAddress ("rawTPEmul4",treeVars.rawTPEmul4) ; 
  chain->SetBranchAddress ("rawTPEmul5",treeVars.rawTPEmul5) ; 
  chain->SetBranchAddress ("eRec",treeVars.eRec) ; 
  chain->SetBranchAddress ("crystNb",treeVars.crystNb) ;
  chain->SetBranchAddress ("spike",treeVars.spike) ;
  chain->SetBranchAddress ("sevlv", treeVars.sevlv);
  chain->SetBranchAddress ("ttFlag", treeVars.ttFlag);
  chain->SetBranchAddress ("trig_tower_adc",treeVars.trig_tower_adc) ; 
  chain->SetBranchAddress ("trig_tower_sFGVB",treeVars.trig_tower_sFGVB) ; 
  chain->SetBranchAddress ("rawTPEmulsFGVB1",treeVars.rawTPEmulsFGVB1) ; 
  chain->SetBranchAddress ("rawTPEmulsFGVB2",treeVars.rawTPEmulsFGVB2) ; 
  chain->SetBranchAddress ("rawTPEmulsFGVB3",treeVars.rawTPEmulsFGVB3) ; 
  chain->SetBranchAddress ("rawTPEmulsFGVB4",treeVars.rawTPEmulsFGVB4) ; 
  chain->SetBranchAddress ("rawTPEmulsFGVB5",treeVars.rawTPEmulsFGVB5) ; 
  chain->SetBranchAddress ("rawTPEmulttFlag1",treeVars.rawTPEmulttFlag1) ; 
  chain->SetBranchAddress ("rawTPEmulttFlag2",treeVars.rawTPEmulttFlag2) ; 
  chain->SetBranchAddress ("rawTPEmulttFlag3",treeVars.rawTPEmulttFlag3) ; 
  chain->SetBranchAddress ("rawTPEmulttFlag4",treeVars.rawTPEmulttFlag4) ; 
  chain->SetBranchAddress ("rawTPEmulttFlag5",treeVars.rawTPEmulttFlag5) ; 


   
  chain->SetBranchAddress ("nMaskedRCT",&treeVars.nMaskedRCT); //
  chain->SetBranchAddress ("iMaskedRCTeta", treeVars.iMaskedRCTeta);//
  chain->SetBranchAddress ("iMaskedRCTcrate", treeVars.iMaskedRCTcrate);//
  chain->SetBranchAddress ("iMaskedRCTphi", treeVars.iMaskedRCTphi);//
   
  chain->SetBranchAddress ("nbOfL1IsoCands",&treeVars.nbOfL1IsoCands); //
  chain->SetBranchAddress ("L1IsoIeta", treeVars.L1IsoIeta);//
  chain->SetBranchAddress ("L1IsoIphi", treeVars.L1IsoIphi);//
  chain->SetBranchAddress ("L1IsoRank", treeVars.L1IsoRank);//
   
  chain->SetBranchAddress ("nbOfL1NonisoCands",&treeVars.nbOfL1NonisoCands); //
  chain->SetBranchAddress ("L1NonisoIeta", treeVars.L1NonisoIeta);//
  chain->SetBranchAddress ("L1NonisoIphi", treeVars.L1NonisoIphi);//
  chain->SetBranchAddress ("L1NonisoRank", treeVars.L1NonisoRank);//
   
  chain->SetBranchAddress ("nbOfL1preIsoCands",&treeVars.nbOfL1preIsoCands); //
  chain->SetBranchAddress ("L1preIsoIeta", treeVars.L1preIsoIeta);//
  chain->SetBranchAddress ("L1preIsoIphi", treeVars.L1preIsoIphi);//
  chain->SetBranchAddress ("L1preIsoRank", treeVars.L1preIsoRank);//
   
  chain->SetBranchAddress ("nbOfL1preNonisoCands",&treeVars.nbOfL1preNonisoCands); //
  chain->SetBranchAddress ("L1preNonisoIeta", treeVars.L1preNonisoIeta);//
  chain->SetBranchAddress ("L1preNonisoIphi", treeVars.L1preNonisoIphi);//
  chain->SetBranchAddress ("L1preNonisoRank", treeVars.L1preNonisoRank);//
   
  chain->SetBranchAddress ("nbOfL1postIsoCands",&treeVars.nbOfL1postIsoCands); //
  chain->SetBranchAddress ("L1postIsoIeta", treeVars.L1postIsoIeta);//
  chain->SetBranchAddress ("L1postIsoIphi", treeVars.L1postIsoIphi);//
  chain->SetBranchAddress ("L1postIsoRank", treeVars.L1postIsoRank);//
   
  chain->SetBranchAddress ("nbOfL1postNonisoCands",&treeVars.nbOfL1postNonisoCands); //
  chain->SetBranchAddress ("L1postNonisoIeta", treeVars.L1postNonisoIeta);//
  chain->SetBranchAddress ("L1postNonisoIphi", treeVars.L1postNonisoIphi);//
  chain->SetBranchAddress ("L1postNonisoRank", treeVars.L1postNonisoRank);//
}



void setAuxBranchAddresses (TChain * chain, EcalAux & auxVars)
{
  chain->SetBranchAddress ("iMaskedTTeta",auxVars.iMaskedTTeta) ; 
  chain->SetBranchAddress ("iMaskedTTphi",auxVars.iMaskedTTphi) ;
  chain->SetBranchAddress ("nMaskedCh",&auxVars.nMaskedCh) ;
  chain->SetBranchAddress ("runNb",&auxVars.runNb) ;   
   
  chain->SetBranchAddress ("nMaskedChannelsFromStrips",&auxVars.nMaskedChannelsFromStrips) ;
  chain->SetBranchAddress ("iMaskedChannelsFromStripsX",auxVars.iMaskedChannelsFromStripsX) ;
  chain->SetBranchAddress ("iMaskedChannelsFromStripsY",auxVars.iMaskedChannelsFromStripsY) ;
  chain->SetBranchAddress ("iMaskedChannelsFromStripsZ",auxVars.iMaskedChannelsFromStripsZ) ;   
}



void printHelp()
{
  std::cout << "\n Help" << std::endl ;
  std::cout << " -h : display help" << std::endl ;
  std::cout << " -i <input root files containing the TPG tree>, default=ECALTPGtree.root" << std::endl ;     
  std::cout << "    2 possible formats when more than 1 file:" << std::endl ;
  std::cout << "    - files names separated by comma without blanks: file1.root,file2.root,file3.root" << std::endl ;
  std::cout << "    - files names using the wildcard \":\" file:1:3:.root" << std::endl ;
  std::cout << "      with this last format, the loop from file1.root to file3.root is performed (see examples below)" << std::endl ;
  std::cout << " -d <directory containing the input root files, default=ignored>" << std::endl ;     
  std::cout << " -o <output root file name, default=histoTPG.root>" << std::endl ;
  std::cout << " -g <endcap geometry file name, default=none>, default=data/endcapGeometry.root" << std::endl ;
  std::cout << " -v <verbosity level(int), default=0 (minimal)>" << std::endl ;
  std::cout << " -l1 <L1 algo bits required. If several, use a comma with no blank. Default=select all>" << std::endl ;
  std::cout << " -l1bx <L1 algo bits required to fill orbit-bx plots. Default=any>" << std::endl ;
  std::cout << " -m <file containing the list of TT to ignore>" << std::endl ;
  std::cout << " -th1 <minimal value of TP, TPEmul to fill the occupancy plot, default=3 (TP>3 ADC, i.e. TP>=1 GeV)>" << std::endl ;
  std::cout << "\n Example:" << std::endl ;
  std::cout << "1) TPGTreeReder -o myfile -l1 16,46 -i file1,file2" << std::endl ;
  std::cout << "will produce histo in file myfile, selecting only events triggered "<< std::endl ;
  std::cout << "by algo bit 16 and 46 and using as inputs the file1 and file2" << std::endl ;
  std::cout << "2) TPGTreeReder -d rfio:/castor/cern.ch/user/p/paganini/67977 -i run67977_:1:18:.root" << std::endl ;
  std::cout << "will produce histo in the default file histoTPG.root, selecting all events"<< std::endl ;
  std::cout << "and using as inputs the 18 files run67977_1.root to run67977_18.root" << std::endl ;
  std::cout << "located in the castor directory /castor/cern.ch/user/p/paganini " << std::endl ;
  std::cout << " -SLMinEvt <set upper limit on eventnumber histogram>, default=10^8" << std::endl ;     
  std::cout << " -SLMaxEvt <set upper limit on eventnumber histogram>, default=10^8" << std::endl ;     
  std::cout << " -SLMinOrb <set upper limit on orbit histogram>, default=10^8" << std::endl ;     
  std::cout << " -SLMaxOrb <set upper limit on orbit histogram>, default=10^8" << std::endl ;     
  std::cout << " -SLMaxLS <set upper limit on lumi section histogram>, default=1000" << std::endl ;     
  std::cout << " -SLMinLS <set lower limit on lumi section histogram>, default=0" << std::endl ;  
  std::cout << " -SLMaxTime <set upper limit on time stamp histogram>, default=100" << std::endl ;     
  std::cout << " -SLMinTime <set lower limit on time stamp histogram>, default=0" << std::endl ;     
  std::cout << " -EG <the trigger energy you want to trig on, e.g. 1, 2, 5, 8, ...>, default=1" << std::endl ;     
  std::cout << " -lumi <select lumi sections, e.g. 15,20-25; 15-0 means from 15 to end>, default=all, -1 means all" << std::endl ;
  std::cout << " -techtrig <select  technical triggers>, default=all, -1 means all"  << std::endl ;
  std::cout << " -goodcoll <trigger selection corresponding to flag 'GOODCOLL'>, default=no, 1 means yes, 0 means no"  << std::endl ;
  std::cout << " -firstEntry <first entry in the rootuple to be processed>, default=0" << std::endl ;
  std::cout << " -lastEntry <last entry in the rootuple to be processed>, default=all, -1 means all" << std::endl ;
}



int getEt(uint val) {return (val&0xff) ;}

uint getFg(uint val) {return ((val&0x100)!=0) ;}

uint getTtf(uint val) {return ((val>>9)&0x7) ;}



std::vector<std::string> split(std::string msg, std::string separator)
{
  boost::char_separator<char> sep(separator.c_str());
  boost::tokenizer<boost::char_separator<char> > tok(msg, sep );
  std::vector<std::string> token ;
  for ( boost::tokenizer<boost::char_separator<char> >::const_iterator i = tok.begin(); i != tok.end(); ++i ) {
    token.push_back(std::string(*i)) ;
  }
  return token ;
}



double getEta(int ietaTower) 
{
  // Paga: to be confirmed, specially in EE:
  return 0.0174*fabs(ietaTower) ;
}



void getTTnb(int iphi, int ieta, int & SM, int & TT)
{
  if (iphi == 1 || iphi == 2 || iphi == 71 || iphi == 72) {
    SM = 1 ;
    if (iphi<71)
      TT = (iphi-1) + 3 + 4*(abs(ieta)-1) ;
    else
      TT = (iphi-71) + 1 + 4*(abs(ieta)-1) ;      
  }
  else {
    SM = (iphi-3)/4 + 2 ; 
    TT = (iphi-3)%4 + 1 + 4*(abs(ieta)-1) ;
  }
  if (ieta<0) SM = -SM ;
  else {
    uint col = (TT-1)%4;
    uint row = (TT-1)-col;
    uint mirror[4] = {4,3,2,1};
    TT = row+mirror[col];
  }
}


void findsecondtp(int l1isocand,int tp,int maxtpeta,int maxtpphi,int* SecondTPinIsoRegion,int TTieta,int TTiphi)
{
  
  int L1ieta = maxtpeta;
  int L1iphi = maxtpphi;
  
      //find neighbor towers
  //cout<<"in fun//cotion ieta "<<L1ieta<<endl;
  //cout<<" in fun//cotion iphi"<<L1iphi<<endl;
  //cout<<" in fun//cotion TTiphi"<<TTiphi<<endl;
  //cout<<" in fun//cotion TTieta"<<TTieta<<endl;
  //cout<<" tp "<<tp<<endl;
  //special cases
  if(L1iphi==1 && TTiphi==72 && L1ieta==TTieta){  
    if(tp>=SecondTPinIsoRegion[l1isocand]) SecondTPinIsoRegion[l1isocand]=tp;
  }
  else if(L1iphi==72 && TTiphi==1 && L1ieta==TTieta){   
    if(tp>=SecondTPinIsoRegion[l1isocand]) SecondTPinIsoRegion[l1isocand]=tp;
  }
  else if(L1ieta==1 && TTieta==-1 && L1iphi==TTiphi){
    if(tp>=SecondTPinIsoRegion[l1isocand]) SecondTPinIsoRegion[l1isocand]=tp;
  }
  else if(L1ieta==-1 && TTieta==1 && L1iphi==TTiphi){
    if(tp>=SecondTPinIsoRegion[l1isocand]) SecondTPinIsoRegion[l1isocand]=tp;
  }
  //normal cases
  else if(L1ieta==TTieta && abs(L1iphi-TTiphi)==1){//towers left and right
    if(tp>=SecondTPinIsoRegion[l1isocand]) SecondTPinIsoRegion[l1isocand]=tp;
  }
  else if(L1iphi==TTiphi && abs(L1ieta-TTieta)==1){//towers above and below
    if(tp>=SecondTPinIsoRegion[l1isocand]) SecondTPinIsoRegion[l1isocand]=tp;
  }  
  
}  
  




int getGCTRegionPhi(int ttphi)
// ttphi is trigger tower phi which is not the same as phi

{
  int gctphi=0;
  gctphi = (ttphi+1)/4;
  if(ttphi<=2) gctphi=0;
  if(ttphi>=71) gctphi=0;
   
  return gctphi;
}



int getGCTRegionPhi2(int crate, int phi)
{
  int gctphi2=0;
  int crate2;
  if(crate<9) crate2=crate;
  else crate2=crate-9;
  //gctphi2 = (ttphi+1)/4;
  if(crate2<2 || (crate2==2 && phi==0)) gctphi2 = 4 - 2*crate2 - phi;
  if(crate2>2 || (crate2==2 && phi==1)) gctphi2 = 22 - phi - 2*crate2;
  return gctphi2;
}



std::vector <int> getECALRegionEta2(int crate, int eta)
{
  std::vector <int> tteta2;
   
  if(crate<9){ 
    for(int i=0;i<4;++i){ 
      tteta2.push_back( -eta + i); 
    }
  }
  else{ 
    for(int i=0;i<4;++i){
      tteta2.push_back( eta - i); 
    }
  }
   
  return tteta2;
}



int getGCTRegionEta(int tteta)
{
  int gcteta = 0;
   
  if(tteta>0) gcteta = (tteta-1)/4 + 11;
  else if(tteta<0) gcteta = (tteta+1)/4 + 10;
   
  return gcteta;
}



std::vector <int> getECALRegionPhi(int gctphi)
{
  std::vector <int> ttphi;
   
  if(gctphi==0){
    ttphi.push_back(71);
    ttphi.push_back(72);
    ttphi.push_back(1);
    ttphi.push_back(2);
  }
  else{
    for(int i=0;i!=4;++i) ttphi.push_back(gctphi*4-1+i);
  } 
   
  return ttphi;
}



std::vector <int> getECALRegionEta(int gcteta)
{
  std::vector <int> tteta;
   
  if(gcteta>=11){ 
    for(int i=1;i<=4;++i){ 
      tteta.push_back( (gcteta-11)*4+i ); 
    }
  }
  else{ 
    for(int i=0;i!=4;++i){
      tteta.push_back( (gcteta-11)*4+i); 
    }
  }
   
  return tteta;
}




///////  Main program /////////
int main (int argc, char** argv)
{  

  bool debug = false;
   
  std::string inputfiles = "ECALTPGtree.root";
  std::string geomName = "/afs/cern.ch/work/n/ndev/TPG/CMSSW_7_5_6/src/CMS-ECAL_TPGAnalysis/Scripts/TriggerAnalysis/macros/endcapGeometry.txt";
   
  std::string inputdir, maskfileName  ;
  std::string outputRootName = "histoTPG.root" ;
  int verbose = 0 ;
  int occupancyCut = 3 ;
   
  Double_t slMinEvt = 0;
  Double_t slMaxEvt = 100000000;
  Double_t slMinOrb = 0;
  Double_t slMaxOrb = 100000000;
  Double_t slMinLS = 0;
  Double_t slMaxLS = 1000;
  Double_t slMinTime = 0;
  Double_t slMaxTime = 1000;
  Long64_t firstEntry = 0;
  Long64_t lastEntry = -1;
  int GoodColl = 0;
  int eg = 2;
  std::string l1algo, l1algobx; 
  std::string bcs ; 
  std::string orbits ; 
  std::string lumi ;
  std::string towers ; 
  std::string timestamps ; 
   
  std::string levent ;
  std::string ltechtrig;
   
   
   
  for (int i=0 ; i<argc ; i++)
    {
      if (argv[i] == std::string("-h") ) {
	printHelp() ;
	exit(1);
      }
      if (argv[i] == std::string("-i") && argc>i+1) {
	inputfiles = argv[i+1] ;
      }
      if (argv[i] == std::string("-d") && argc>i+1) {
	inputdir = argv[i+1] ;
	inputdir = inputdir + "/" ;
      }
      if (argv[i] == std::string("-o") && argc>i+1) outputRootName = argv[i+1] ;
      if (argv[i] == std::string("-g") && argc>i+1) geomName = argv[i+1] ;
      if (argv[i] == std::string("-v") && argc>i+1) verbose = atoi(argv[i+1]) ;
      if (argv[i] == std::string("-l1") && argc>i+1) l1algo =  std::string(argv[i+1]) ;
      if (argv[i] == std::string("-l1bx") && argc>i+1) l1algobx =  std::string(argv[i+1]) ;
      if (argv[i] == std::string("-th1") && argc>i+1) occupancyCut= atoi(argv[i+1]) ;
      if (argv[i] == std::string("-m") && argc>i+1) maskfileName = argv[i+1] ;
      if (argv[i] == std::string("-SLMinEvt") && argc>i+1)  slMinEvt = atof(argv[i+1]) ;
      if (argv[i] == std::string("-SLMaxEvt") && argc>i+1)  slMaxEvt = atof(argv[i+1]) ;
      if (argv[i] == std::string("-SLMinOrb") && argc>i+1)  slMinOrb = atof(argv[i+1]) ;
      if (argv[i] == std::string("-SLMaxOrb") && argc>i+1)  slMaxOrb = atof(argv[i+1]) ;
      if (argv[i] == std::string("-SLMinLS") && argc>i+1) slMinLS= atof(argv[i+1]) ;
      if (argv[i] == std::string("-SLMaxLS") && argc>i+1) slMaxLS= atof(argv[i+1]) ;
      if (argv[i] == std::string("-SLMinTime") && argc>i+1) slMinTime= atof(argv[i+1]) ;
      if (argv[i] == std::string("-SLMaxTime") && argc>i+1) slMaxTime= atof(argv[i+1]) ;
      if (argv[i] == std::string("-EG") && argc>i+1) eg = atoi(argv[i+1]) ;
      
      if (argv[i] == std::string("-bcs") && argc>i+1) bcs= std::string(argv[i+1]) ;
      if (argv[i] == std::string("-orbits") && argc>i+1) orbits= std::string(argv[i+1]) ;
      if (argv[i] == std::string("-timestamps") && argc>i+1) timestamps= std::string(argv[i+1]) ;
      if (argv[i] == std::string("-towers") && argc>i+1) towers= std::string(argv[i+1]) ;
      if (argv[i] == std::string("-levent") && argc>i+1) levent= std::string(argv[i+1]) ;
      if (argv[i] == std::string("-techtrig") && argc>i+1) ltechtrig= std::string(argv[i+1]) ;
      if (argv[i] == std::string("-goodcoll") && argc>i+1) GoodColl = atoi(argv[i+1]) ;
      if (argv[i] == std::string("-lumi") && argc>i+1) lumi= std::string(argv[i+1]) ;
      if (argv[i] == std::string("-firstEntry") && argc>i+1) firstEntry= atol(argv[i+1]) ;
      if (argv[i] == std::string("-lastEntry") && argc>i+1) lastEntry= atol(argv[i+1]) ;
    }
   
   
  std::vector<int> algobits ;
  std::vector<std::string> algos = split(l1algo,",") ;
  for (uint i=0 ; i<algos.size() ; i++) algobits.push_back(atoi(algos[i].c_str())) ;
   
  std::vector<int> algobitsbx ;
  std::vector<std::string> algosbx = split(l1algobx,",") ;
  for (uint i=0 ; i<algosbx.size() ; i++) algobitsbx.push_back(atoi(algosbx[i].c_str())) ;
   
  //   std::vector<int> myevents ;
  //   std::vector<std::string> vevents = split(levent,",") ;
  //   for (uint i=0 ; i<vevents.size() ; i++) myevents.push_back(atoi(vevents[i].c_str())) ;
   
  std::vector<int> mytechtriggers ;
  std::vector<std::string> vmytechtriggers = split(ltechtrig,",") ;
  for (uint i=0 ; i<vmytechtriggers.size() ; i++) mytechtriggers.push_back(atoi(vmytechtriggers[i].c_str())) ;  
   
  std::vector<std::string> techTrgRangeStringVector;
  std::vector<int> techTrgRangeIntVector;
  std::vector<std::vector<int> > techTrgIncludeVector ;
  std::vector<std::vector<int> > techTrgExcludeVector ;
   
  std::vector<std::string> techTrgStringVector = split(ltechtrig,",") ;
   
  if(debug)
    {
      for (uint i=0 ; i<techTrgStringVector.size();i++){
	std::cout << "techTrgStringVector["<<i<<"] = " << techTrgStringVector[i] << std::endl;
      }
      std::cout << std::endl;
    }
   
  for (uint i=0 ; i<techTrgStringVector.size() ; i++)
    {
      bool exclude = false;
      
      if(techTrgStringVector[i].at(0)=='x'){
	exclude = true;
	techTrgStringVector[i].erase(0,1);
      }
      techTrgRangeStringVector = split(techTrgStringVector[i],"-") ;
      
      if(debug){
	for (uint i=0 ; i<techTrgRangeStringVector.size();i++){
	  std::cout << "techTrgRangeStringVector["<<i<<"] = " << techTrgRangeStringVector[i] << std::endl;
	}    
	std::cout << std::endl;
      }
      
      techTrgRangeIntVector.clear();
      for(uint j=0; j<techTrgRangeStringVector.size();j++) {
	techTrgRangeIntVector.push_back(atoi(techTrgRangeStringVector[j].c_str()));
      }
      if(exclude) techTrgExcludeVector.push_back(techTrgRangeIntVector);
      else techTrgIncludeVector.push_back(techTrgRangeIntVector);
      
    }
   
  if(debug)
    {
      std::cout << "techTrgIncludeVector.size(): " << techTrgIncludeVector.size() << "\n\n";
      for (uint i=0 ; i<techTrgIncludeVector.size();i++){
	std::cout << "techTrgIncludeVector["<<i<<"].size(): " << techTrgIncludeVector[i].size() << "\n";
	for (uint j=0 ; j<techTrgIncludeVector[i].size();j++){
	  std::cout << "techTrgIncludeVector["<<i<<"]["<<j<<"]: " << techTrgIncludeVector[i][j] << "\t";
	}
	std::cout << "\n";
      }
      
      std::cout << "techTrgExcludeVector.size(): " << techTrgExcludeVector.size() << "\n\n";
      for (uint i=0 ; i<techTrgExcludeVector.size();i++){
	std::cout << "techTrgExcludeVector["<<i<<"].size(): " << techTrgExcludeVector[i].size() << "\n";
	for (uint j=0 ; j<techTrgExcludeVector[i].size();j++){
	  std::cout << "techTrgExcludeVector["<<i<<"]["<<j<<"]: " << techTrgExcludeVector[i][j] << "\t";
	}
	std::cout << "\n";
      }
    }
   
   
   
  std::vector<std::string> bcRangeStringVector;
  std::vector<int> bcRangeIntVector;
  std::vector<std::vector<int> > bcIncludeVector ;
  std::vector<std::vector<int> > bcExcludeVector ;
   
  std::vector<std::string> bcStringVector = split(bcs,",") ;
   
  if(debug){
    for (uint i=0 ; i<bcStringVector.size();i++){
      std::cout << "bcStringVector["<<i<<"] = " << bcStringVector[i] << std::endl;
    }
    std::cout << std::endl;
  }
   
  for (uint i=0 ; i<bcStringVector.size() ; i++) {
    bool exclude = false;
      
    if(bcStringVector[i].at(0)=='x'){
      exclude = true;
      bcStringVector[i].erase(0,1);
    }
    bcRangeStringVector = split(bcStringVector[i],"-") ;
      
    if(debug){
      for (uint i=0 ; i<bcRangeStringVector.size();i++){
	std::cout << "bcRangeStringVector["<<i<<"] = " << bcRangeStringVector[i] << std::endl;
      }    
      std::cout << std::endl;
    }
      
    bcRangeIntVector.clear();
    for(uint j=0; j<bcRangeStringVector.size();j++) {
      bcRangeIntVector.push_back(atoi(bcRangeStringVector[j].c_str()));
    }
    if(exclude) bcExcludeVector.push_back(bcRangeIntVector);
    else bcIncludeVector.push_back(bcRangeIntVector);
      
  }
   
  if(debug){
    std::cout << "bcIncludeVector.size(): " << bcIncludeVector.size() << "\n\n";
    for (uint i=0 ; i<bcIncludeVector.size();i++){
      std::cout << "bcIncludeVector["<<i<<"].size(): " << bcIncludeVector[i].size() << "\n";
      for (uint j=0 ; j<bcIncludeVector[i].size();j++){
	std::cout << "bcIncludeVector["<<i<<"]["<<j<<"]: " << bcIncludeVector[i][j] << "\t";
      }
      std::cout << "\n";
    }
      
    std::cout << "bcExcludeVector.size(): " << bcExcludeVector.size() << "\n\n";
    for (uint i=0 ; i<bcExcludeVector.size();i++){
      std::cout << "bcExcludeVector["<<i<<"].size(): " << bcExcludeVector[i].size() << "\n";
      for (uint j=0 ; j<bcExcludeVector[i].size();j++){
	std::cout << "bcExcludeVector["<<i<<"]["<<j<<"]: " << bcExcludeVector[i][j] << "\t";
      }
      std::cout << "\n";
    }
  }
   
   
  std::vector<std::string> lumiRangeStringVector;
  std::vector<double> lumiRangeIntVector;
  std::vector<std::vector<double> > lumiIncludeVector ;
  std::vector<std::vector<double> > lumiExcludeVector ;
   
  if(lumi != "-1"){
    std::vector<std::string> lumiStringVector = split(lumi,",") ;
      
    for (uint i=0 ; i<lumiStringVector.size() ; i++) {
      bool exclude = false;
         
      if(lumiStringVector[i].at(0)=='x'){
	exclude = true;
	lumiStringVector[i].erase(0,1);
      }
      lumiRangeStringVector = split(lumiStringVector[i],"-") ;
         
      lumiRangeIntVector.clear();
      for(uint j=0; j<lumiRangeStringVector.size();j++) {
	lumiRangeIntVector.push_back(atof(lumiRangeStringVector[j].c_str()));
      }
      if(exclude) lumiExcludeVector.push_back(lumiRangeIntVector);
      else lumiIncludeVector.push_back(lumiRangeIntVector);
         
    }
  }
   
   
   
  std::vector<std::string> eventRangeStringVector;
  std::vector<ULong64_t> eventRangeIntVector;
  std::vector<std::vector<ULong64_t> > eventIncludeVector ;
  std::vector<std::vector<ULong64_t> > eventExcludeVector ;
   
  if(levent != "-1"){
    std::vector<std::string> eventStringVector = split(levent,",") ;
      
    for (uint i=0 ; i<eventStringVector.size() ; i++) {
      bool exclude = false;
         
      if(eventStringVector[i].at(0)=='x'){
	exclude = true;
	eventStringVector[i].erase(0,1);
      }
      eventRangeStringVector = split(eventStringVector[i],"-") ;
         
      eventRangeIntVector.clear();
      for(uint j=0; j<eventRangeStringVector.size();j++) {
	eventRangeIntVector.push_back(atol(eventRangeStringVector[j].c_str()));
      }
      if(exclude) eventExcludeVector.push_back(eventRangeIntVector);
      else eventIncludeVector.push_back(eventRangeIntVector);
         
    }
  }
   
  if(debug)
    {
      for(uint j=0; j<eventRangeIntVector.size();j++)
	std::cout << "eventRangeIntVector["<<j<<"]="<<eventRangeIntVector[j]<<std::endl;
    }

   
  std::vector<std::string> orbitRangeStringVector;
  std::vector<double> orbitRangeIntVector;
  std::vector<std::vector<double> > orbitIncludeVector ;
  std::vector<std::vector<double> > orbitExcludeVector ;
   
  std::vector<std::string> orbitStringVector = split(orbits,",") ;
   
  if(debug){
    for (uint i=0 ; i<orbitStringVector.size();i++){
      std::cout << "orbitStringVector["<<i<<"] = " << orbitStringVector[i] << std::endl;
    }
    std::cout << std::endl;
  }
   
  for (uint i=0 ; i<orbitStringVector.size() ; i++) {
    bool exclude = false;
      
    if(orbitStringVector[i].at(0)=='x'){
      exclude = true;
      orbitStringVector[i].erase(0,1);
    }
    orbitRangeStringVector = split(orbitStringVector[i],"-") ;
      
    if(debug){
      for (uint i=0 ; i<orbitRangeStringVector.size();i++){
	std::cout << "orbitRangeStringVector["<<i<<"] = " << orbitRangeStringVector[i] << std::endl;
      }    
      std::cout << std::endl;
    }
      
    orbitRangeIntVector.clear();
    for(uint j=0; j<orbitRangeStringVector.size();j++) {
      orbitRangeIntVector.push_back(atof(orbitRangeStringVector[j].c_str()));
    }
    if(exclude) orbitExcludeVector.push_back(orbitRangeIntVector);
    else orbitIncludeVector.push_back(orbitRangeIntVector);
      
  }
   
  if(debug){
    std::cout << "orbitIncludeVector.size(): " << orbitIncludeVector.size() << "\n\n";
    for (uint i=0 ; i<orbitIncludeVector.size();i++){
      std::cout << "orbitIncludeVector["<<i<<"].size(): " << orbitIncludeVector[i].size() << "\n";
      for (uint j=0 ; j<orbitIncludeVector[i].size();j++){
	std::cout << "orbitIncludeVector["<<i<<"]["<<j<<"]: " << orbitIncludeVector[i][j] << "\t";
      }
      std::cout << "\n";
    }
      
    std::cout << "orbitExcludeVector.size(): " << orbitExcludeVector.size() << "\n\n";
    for (uint i=0 ; i<orbitExcludeVector.size();i++){
      std::cout << "orbitExcludeVector["<<i<<"].size(): " << orbitExcludeVector[i].size() << "\n";
      for (uint j=0 ; j<orbitExcludeVector[i].size();j++){
	std::cout << "orbitExcludeVector["<<i<<"]["<<j<<"]: " << orbitExcludeVector[i][j] << "\t";
      }
      std::cout << "\n";
    }
  }
   
   
  std::vector<std::string> timestampRangeStringVector;
  std::vector<double> timestampRangeIntVector;
  std::vector<std::vector<double> > timestampIncludeVector ;
  std::vector<std::vector<double> > timestampExcludeVector ;
   
  std::vector<std::string> timestampStringVector = split(timestamps,",") ;
   
  if(debug){
    for (uint i=0 ; i<timestampStringVector.size();i++){
      std::cout << "timestampStringVector["<<i<<"] = " << timestampStringVector[i] << std::endl;
    }
    std::cout << std::endl;
  }
   
  for (uint i=0 ; i<timestampStringVector.size() ; i++) {
    bool exclude = false;
      
    if(timestampStringVector[i].at(0)=='x'){
      exclude = true;
      timestampStringVector[i].erase(0,1);
    }
    timestampRangeStringVector = split(timestampStringVector[i],"-") ;
      
    if(debug){
      for (uint i=0 ; i<timestampRangeStringVector.size();i++){
	std::cout << "timestampRangeStringVector["<<i<<"] = " << timestampRangeStringVector[i] << std::endl;
      }    
      std::cout << std::endl;
    }
      
    timestampRangeIntVector.clear();
    for(uint j=0; j<timestampRangeStringVector.size();j++) {
      timestampRangeIntVector.push_back(atof(timestampRangeStringVector[j].c_str()));
    }
    if(exclude) timestampExcludeVector.push_back(timestampRangeIntVector);
    else timestampIncludeVector.push_back(timestampRangeIntVector);
      
  }
   
  if(debug){
    std::cout << "timestampIncludeVector.size(): " << timestampIncludeVector.size() << "\n\n";
    for (uint i=0 ; i<timestampIncludeVector.size();i++){
      std::cout << "timestampIncludeVector["<<i<<"].size(): " << timestampIncludeVector[i].size() << "\n";
      for (uint j=0 ; j<timestampIncludeVector[i].size();j++){
	std::cout << "timestampIncludeVector["<<i<<"]["<<j<<"]: " << timestampIncludeVector[i][j] << "\t";
      }
      std::cout << "\n";
    }
      
    std::cout << "timestampExcludeVector.size(): " << timestampExcludeVector.size() << "\n\n";
    for (uint i=0 ; i<timestampExcludeVector.size();i++){
      std::cout << "timestampExcludeVector["<<i<<"].size(): " << timestampExcludeVector[i].size() << "\n";
      for (uint j=0 ; j<timestampExcludeVector[i].size();j++){
	std::cout << "timestampExcludeVector["<<i<<"]["<<j<<"]: " << timestampExcludeVector[i][j] << "\t";
      }
      std::cout << "\n";
    }
  }
      
   
  std::vector<std::string> towerRangeStringVector;
  std::vector<int> towerIncludeVector ;
  std::vector<int> towerExcludeVector ;
   
  std::vector<std::string> towerStringVector = split(towers,",") ;
   
  if(debug){
    for (uint i=0 ; i<towerStringVector.size();i++){
      std::cout << "towerStringVector["<<i<<"] = " << towerStringVector[i] << std::endl;
    }
    std::cout << std::endl;
  }
  for (uint i=0 ; i<towerStringVector.size() ; i++) {
      
    if(towerStringVector[i].at(0)=='x'){
      towerStringVector[i].erase(0,1);
      towerExcludeVector.push_back(atoi(towerStringVector[i].c_str()));
    }
    else towerIncludeVector.push_back(atoi(towerStringVector[i].c_str()));
  }
   
  if(debug){
    std::cout << "towerIncludeVector.size(): " << towerIncludeVector.size() << "\n\n";
    for (uint i=0 ; i<towerIncludeVector.size();i++){
      std::cout << "towerIncludeVector["<<i<<"]= " << towerIncludeVector[i] << "\n";
         
      std::cout << "\n";
    }
    std::cout << "towerExcludeVector.size(): " << towerExcludeVector.size() << "\n\n";
    for (uint i=0 ; i<towerExcludeVector.size();i++){
      std::cout << "towerExcludeVector["<<i<<"]= " << towerExcludeVector[i] << "\n";
         
      std::cout << "\n";
    }
  }
   
   
  uint ref = 2 ;  //emulator array index corresponding to 3rd sample of 5.
  //this should match the real TP data (theoretically)
   
   
  ///////////////////////
  // parse geometry file
  ///////////////////////
  ifstream fin ;
  std::string line;
  int hashedIndex, ix, iy;
  std::map < int , std::vector< std::pair<int, int> > > geometry;
   
  fin.open(geomName.c_str());
  if (fin.is_open())
    {
      while(!fin.eof()) {
	fin >> hashedIndex >> ix >> iy;
	if(fin.eof()){
	  break ; // avoid last line duplication
	}
	geometry[hashedIndex].push_back( std::pair<int,int>(ix,iy) ); 
      }
    }
   
   
  ///////////////////////
  // book the histograms
  ///////////////////////
  //TH1F * bx_all = new TH1F("bx_all","bx_all",3570, 0, 3570) ;
  TH1F * bx_bit45_all = new TH1F("bx_bit45_all","bx_bit45_all",3570, 0, 3570) ;
  TH1F * bx_bit46_all = new TH1F("bx_bit46_all","bx_bit46_all",3570, 0, 3570) ;
  TH1F * bx_nTT = new TH1F("bx_nTT","bx_nTT",21, -0.5, 20.5) ;
   
   
  //TH1F * bx_all_ecal = new TH1F("bx_all_ecal","bx_all_ecal",3570, 0, 3570) ;
  //TH1F * bx_all_eb = new TH1F("bx_all_eb","bx_all_eb",3570, 0, 3570) ;
  //TH1F * bx_all_ee_m = new TH1F("bx_all_ee_m","bx_all_ee_m",3570, 0, 3570) ;
  //TH1F * bx_all_ee_p = new TH1F("bx_all_ee_p","bx_all_ee_p",3570, 0, 3570) ;
  TH1F *  l1EGAlgos = new TH1F("L1EGAlgos","L1EGAlgos", 30, 39.5 , 69.5);
  TH2F *  l1EGAlgos2D = new TH2F("L1EGAlgos2D","L1EGAlgos2D", 30, 39.5 , 69.5, 30, 39.5 , 69.5);
   
  TH1F * techTrigCor   = new TH1F("techTrigCor","techTrigCor", 10, 39.5 , 49.5);
  TH2F * techTrigCor2D = new TH2F("techTrigCor2D","techTrigCor2D", 10, 39.5 , 49.5, 10, 39.5 , 49.5);
   
  TH2F * histoEgTrigTechTrigCor = new TH2F("histoEgTrigTechTrigCor","histoEgTrigTechTrigCor",30, 39.5 , 69.5, 10, 39.5 , 49.5); 
   
  //BARREL
   
  //barrel TP occupancy

  TH2F * occupancyTPEB = new TH2F("occupancyTPEB", "TP Occupancy: Barrel", 72, 1, 73, 38, -19, 19) ;
  occupancyTPEB->GetYaxis()->SetTitle("eta index") ;
  occupancyTPEB->GetXaxis()->SetTitle("phi index") ;
  //this is new: barrel TP Occupancy for mismatched by two bx

  TH2F * occupancyTPEBmis = new TH2F("occupancyTPEBmis", "Emulatedmax TP Occupancy: Barrel(mismatched by 2 bx)", 72, 1, 73, 38, -19, 19) ;
  occupancyTPEB->GetYaxis()->SetTitle("eta index") ;
  occupancyTPEB->GetXaxis()->SetTitle("phi index") ;


  TH2F * occupancyTPEmulEB_when_no_real_NZ_TP = new TH2F("occupancyTPEmulEB_when_no_real_NZ_TP", "Emulated TP_{BX0}_occupancy_when_no_non-zero_realTP ", 72, 1, 73, 38, -19, 19) ;
  occupancyTPEmulEB_when_no_real_NZ_TP->GetYaxis()->SetTitle("eta index") ;
  occupancyTPEmulEB_when_no_real_NZ_TP->GetXaxis()->SetTitle("phi index") ;




  //barrel emulated TP occupancy
  TH2F * occupancyTPEmulEB = new TH2F("occupancyTPEmulEB", "Emulated TP Occupancy: Barrel", 72, 1, 73, 38, -19, 19) ;
  occupancyTPEmulEB->GetYaxis()->SetTitle("eta index") ;
  occupancyTPEmulEB->GetXaxis()->SetTitle("phi index") ;
  //barrel TP eta
  TH1F * TPEtaEB = new TH1F("TPEtaEB", "TP: Barrel eta", 35, -17, 18) ;
  TPEtaEB->GetXaxis()->SetTitle("eta index") ;
  //barrel TP phi
  TH1F * TPPhiEB = new TH1F("TPPhiEB", "TP: Barrel phi", 72, 1, 73) ;
  TPPhiEB->GetXaxis()->SetTitle("phi index") ;

  //this is new
  TH1F * TPEtaEBmis = new TH1F("TPEtaEBmis", "TP: Barrel eta(mismatched by 2bx)", 35, -17, 18) ;
  TPEtaEBmis->GetXaxis()->SetTitle("eta index") ;
  //barrel TP phi
  TH1F * TPPhiEBmis = new TH1F("TPPhiEBmis", "TP: Barrel phi(mismatched by 2bx)", 72, 1, 73) ;
  TPPhiEBmis->GetXaxis()->SetTitle("phi index") ;
   


  //TP-emulatedTP-erec_outliers
  TH2F * occu_TPvemulatedTP_outliers_EB = new TH2F("occu_TPvemulatedTP_outliers_EB", "occupancy of otuliers in TPvemulatedTP: Barrel", 72, 1, 73, 38, -19, 19) ;
  occu_TPvemulatedTP_outliers_EB->GetYaxis()->SetTitle("eta index") ;
  occu_TPvemulatedTP_outliers_EB->GetXaxis()->SetTitle("phi index") ;
  TH2F * occu_TPvemulatedTP_outliers_EEPlus = new TH2F("occu_TPvemulatedTP_outliers_EEPlus", "occupancy of otuliers in TPvemulatedTP: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
  occu_TPvemulatedTP_outliers_EEPlus->GetYaxis()->SetTitle("y index") ;
  occu_TPvemulatedTP_outliers_EEPlus->GetXaxis()->SetTitle("x index") ;
  TH2F * occu_TPvemulatedTP_outliers_EEMinus = new TH2F("occu_TPvemulatedTP_outliers_EEMinus", "occupancy of otuliers in TPvemulatedTP: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
  occu_TPvemulatedTP_outliers_EEMinus->GetYaxis()->SetTitle("y index") ;
  occu_TPvemulatedTP_outliers_EEMinus->GetXaxis()->SetTitle("x index") ;


   
  //ENDCAPS
   
  //endcap TP occupancy
  TH2F * occupancyTPEEPlus = new TH2F("occupancyTPEEPlus", "TP Occupancy: E>0: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
  occupancyTPEEPlus->GetYaxis()->SetTitle("y index") ;
  occupancyTPEEPlus->GetXaxis()->SetTitle("x index") ;
  TH2F * occupancyTPEEMinus = new TH2F("occupancyTPEEMinus", "TP Occupancy: E>0: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
  occupancyTPEEMinus->GetYaxis()->SetTitle("y index") ;
  occupancyTPEEMinus->GetXaxis()->SetTitle("x index") ;
  TH2F * occupancyTPEEPlusAll = new TH2F("occupancyTPEEPlusAll", "TP Occupancy: All TPs: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
  occupancyTPEEPlusAll->GetYaxis()->SetTitle("y index") ;
  occupancyTPEEPlusAll->GetXaxis()->SetTitle("x index") ;
  TH2F * occupancyTPEEMinusAll = new TH2F("occupancyTPEEMinusAll", "TP Occupancy: All TPs: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
  occupancyTPEEMinusAll->GetYaxis()->SetTitle("y index") ;
  occupancyTPEEMinusAll->GetXaxis()->SetTitle("x index") ;
  
   
 
  //endcap emulated TP occupancy
  TH2F * occupancyTPEmulEEPlus = new TH2F("occupancyTPEmulEEPlus", "Emulated TP Occupancy: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
  occupancyTPEmulEEPlus->GetYaxis()->SetTitle("y index") ;
  occupancyTPEmulEEPlus->GetXaxis()->SetTitle("x index") ;
  TH2F * occupancyTPEmulEEMinus = new TH2F("occupancyTPEmulEEMinus", "Emulated TP Occupancy: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
  occupancyTPEmulEEMinus->GetYaxis()->SetTitle("y index") ;
  occupancyTPEmulEEMinus->GetXaxis()->SetTitle("x index") ;
  TH2F * occupancyTPEmulEEPlusALL = new TH2F("occupancyTPEmulEEPlusALL", "Occupancy of Emulated TPs: ANY emu sample > 0: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
  occupancyTPEmulEEPlusALL->GetYaxis()->SetTitle("y index") ;
  occupancyTPEmulEEPlusALL->GetXaxis()->SetTitle("x index") ;
  TH2F * occupancyTPEmulEEMinusALL = new TH2F("occupancyTPEmulEEMinusALL", "Occupancy of Emulated TPs: ANY emu sample > 0: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
  occupancyTPEmulEEMinusALL->GetYaxis()->SetTitle("y index") ;
  occupancyTPEmulEEMinusALL->GetXaxis()->SetTitle("x index") ;
   
  //endcap TP eta
  TH1F * TPEtaEEPlus = new TH1F("TPEtaEEPlus", "TP: Plus Endcap eta", 11, 18, 29) ;
  TPEtaEEPlus->GetXaxis()->SetTitle("eta index") ;
  TH1F * TPEtaEEMinus = new TH1F("TPEtaEEMinus", "TP: Minus Endcap eta", 11, -28, -17) ;
  TPEtaEEMinus->GetXaxis()->SetTitle("eta index") ;
   
  //endcap TP phi
  TH1F * TPPhiEEPlus = new TH1F("TPPhiEEPlus", "TP: Plus Endcap phi", 72, 1, 73) ;
  TPPhiEEPlus->GetXaxis()->SetTitle("phi index") ;
  TH1F * TPPhiEEMinus = new TH1F("TPPhiEEMinus", "TP: Minus Endcap phi", 72, 1, 73) ;
  TPPhiEEMinus->GetXaxis()->SetTitle("phi index") ;
   

  //this is new adding mismatch plots for endcaps

  TH2F * occupancyTPEmulEEPlus_mis = new TH2F("occupancyTPEmulEEPlus_mis", "Emulated TP Occupancy: Plus Endcap(mismatched by 2 bx)", 121, -10, 111, 121, -10, 111) ;
  occupancyTPEmulEEPlus_mis->GetYaxis()->SetTitle("y index") ;
  occupancyTPEmulEEPlus_mis->GetXaxis()->SetTitle("x index") ;
  TH2F * occupancyTPEmulEEMinus_mis = new TH2F("occupancyTPEmulEEMinus_mis", "Emulated TP Occupancy: Minus Endcap(mismatched by 2 bx)", 121, -10, 111, 121, -10, 111) ;
  occupancyTPEmulEEMinus_mis->GetYaxis()->SetTitle("y index") ;
  occupancyTPEmulEEMinus_mis->GetXaxis()->SetTitle("x index") ;
   

  TH2F * occupancyTPEmulEEPlus_when_no_real_NZ_TP = new TH2F("occupancyTPEmulEEPlus_when_no_real_NZ_TP", "Emulated TP_{BX0}_occupancy_when_no_non-zero_realTP ", 121, -10, 111, 121, -10, 111) ;
  occupancyTPEmulEEPlus_when_no_real_NZ_TP->GetYaxis()->SetTitle("eta index") ;
  occupancyTPEmulEEPlus_when_no_real_NZ_TP->GetXaxis()->SetTitle("phi index") ;


  TH2F * occupancyTPEmulEEMinus_when_no_real_NZ_TP = new TH2F("occupancyTPEmulEEMinus_when_no_real_NZ_TP", "Emulated TP_{BX0}_occupancy_when_no_non-zero_realTP ", 121, -10, 111, 121, -10, 111) ;
  occupancyTPEmulEEMinus_when_no_real_NZ_TP->GetYaxis()->SetTitle("eta index") ;
  occupancyTPEmulEEMinus_when_no_real_NZ_TP->GetXaxis()->SetTitle("phi index") ;



  




  //endcap TP eta
  TH1F * TPEmulEtaEEPlus_mis = new TH1F("TPEmulEtaEEPlus_mis", "TP: Plus Endcap eta(mismatched by 2 bx)", 11, 18, 29) ;
  TPEmulEtaEEPlus_mis->GetXaxis()->SetTitle("eta index") ;
  TH1F * TPEmulEtaEEMinus_mis = new TH1F("TPEmulEtaEEMinus_mis", "TP: Minus Endcap eta(mismatched by 2 bx)", 11, -28, -17) ;
  TPEmulEtaEEMinus_mis->GetXaxis()->SetTitle("eta index") ;
   
  //endcap TP phi
  TH1F * TPEmulPhiEEPlus_mis = new TH1F("TPEmulPhiEEPlus_mis", "TP: Plus Endcap phi(mismatched by 2 bx)", 72, 1, 73) ;
  TPEmulPhiEEPlus_mis->GetXaxis()->SetTitle("phi index") ;
  TH1F * TPEmulPhiEEMinus_mis = new TH1F("TPEmulPhiEEMinus_mis", "TP: Minus Endcap phi(mismatched by 2 bx)", 72, 1, 73) ;
  TPEmulPhiEEMinus_mis->GetXaxis()->SetTitle("phi index") ;



   
   
  // ============================= Fill histos related to time evolution
  int timeBin = int(slMaxTime-slMinTime);
   
  //std::cout << "time bin: " << timeBin << std::endl;
  TH1F * occupancyTP_vs_EvtNb = new TH1F("occupancyTP_vs_EvtNb", "TP occupancy vs. EvtNb", 1000, slMinEvt, slMaxEvt) ;
  occupancyTP_vs_EvtNb->GetXaxis()->SetTitle("EvtNb / 10^6") ;
  occupancyTP_vs_EvtNb->GetYaxis()->SetTitle("# of TPs") ;
   
  TH2F * ttfstatus_eb13 = new TH2F("ttfstatus_eb13", "ttfstatus_eb13 vs. Time",timeBin, 0, slMaxTime-slMinTime, 6, -1.0, 5.) ;
  ttfstatus_eb13->GetYaxis()->SetTitle("ttfstatus") ;
  ttfstatus_eb13->GetXaxis()->SetTitle("Time (min)") ;
  
  TH2F * ttfstatus_all = new TH2F("ttfstatus_all", "ttfstatus_all vs. Time",timeBin, 0, slMaxTime-slMinTime, 6, -1.0, 5.) ;
  ttfstatus_all->GetYaxis()->SetTitle("ttfstatus") ;
  ttfstatus_all->GetXaxis()->SetTitle("Time (min)") ;
 
 



  TH2F * iEta_vs_Time = new TH2F("iEta_vs_Time", "iEta vs. Time",timeBin, 0, slMaxTime-slMinTime, 57, -28, 29) ;
  iEta_vs_Time->GetYaxis()->SetTitle("iEta") ;
  iEta_vs_Time->GetXaxis()->SetTitle("Time (min)") ;
  TH2F * iPhi_vs_Time = new TH2F("iPhi_vs_Time", "iPhi vs. Time",timeBin, 0, slMaxTime-slMinTime, 72, 1, 73) ;
  iPhi_vs_Time->GetYaxis()->SetTitle("iPhi") ;
  iPhi_vs_Time->GetXaxis()->SetTitle("Time (min)") ;
   
  TH3F * time3D = new TH3F("time3D", "TT vs time", 72, 1, 73, 57, -28, 29, timeBin, 0, slMaxTime-slMinTime) ;
  time3D->GetYaxis()->SetTitle("eta index") ;
  time3D->GetXaxis()->SetTitle("phi index") ;
   
   
  int LSBin = int(slMaxLS-slMinLS);

  
  TH2F * ttfstatus_vs_LS_all = new TH2F("ttfstatus_vs_LS_all", "ttfstatus_vs_LS_all vs. LS",LSBin, slMinLS, slMaxLS, 6, -1.0, 5.) ;
  ttfstatus_vs_LS_all->GetYaxis()->SetTitle("ttfstatus_vs_LS") ;
  ttfstatus_vs_LS_all->GetXaxis()->SetTitle("LS (min)") ;

   
  TH2F * iEta_vs_LS = new TH2F("iEta_vs_LS", "iEta vs. LS",LSBin, slMinLS, slMaxLS, 57, -28, 29) ;
  iEta_vs_LS->GetYaxis()->SetTitle("iEta") ;
  iEta_vs_LS->GetXaxis()->SetTitle("Lumi Section") ;
  TH2F * iPhi_vs_LS = new TH2F("iPhi_vs_LS", "iPhi vs. LS",LSBin, slMinLS, slMaxLS, 72, 1, 73) ;
  iPhi_vs_LS->GetYaxis()->SetTitle("iPhi") ;
  iPhi_vs_LS->GetXaxis()->SetTitle("Lumi Section") ;
   
  TH3F * LS3D = new TH3F("LS3D", "TT vs lumi section", 72, 1, 73, 57, -28, 29, LSBin, slMinLS, slMaxLS) ;
  LS3D->GetYaxis()->SetTitle("eta index") ;
  LS3D->GetXaxis()->SetTitle("phi index") ;
   
   
  TH1F * orbit = new TH1F("orbit", "orbit number", 1000, slMinOrb, slMaxOrb) ;
  orbit->GetXaxis()->SetTitle("Orbit Number / 10^6") ;
  TH1F * eventNb = new TH1F("eventNb", "event number", 100,slMinEvt, slMaxEvt) ;
  eventNb->GetXaxis()->SetTitle("Event Number / 10^6") ;
  eventNb->GetYaxis()->SetTitle("# of Events ") ;
  TH1F * TimeStamp = new TH1F("TimeStamp", "time stamp", timeBin, 0, timeBin) ;
  TimeStamp->GetXaxis()->SetTitle("Time Stamp (min) ") ;
   
  TH1F * LumiSection = new TH1F("LumiSection", "lumi section", LSBin, slMinLS, slMaxLS) ;
  LumiSection->GetXaxis()->SetTitle("Luminosity Section ") ;
   
  TH1F * triggerBit = new TH1F("triggerBit", "Active Triggers Fired", 256, 0., 128.) ;
  triggerBit->GetXaxis()->SetTitle("Trigger Bit") ;
   
  TH1F * FiredTriggers = new TH1F("FiredTriggers", "Triggers Fired (before masking)", 256, 0., 128.) ;
  FiredTriggers->GetXaxis()->SetTitle("Trigger Bit") ;
   
  TH1F * TPEB = new TH1F("TPEB", "TP: Barrel", 256, 0., 256.) ;
  TPEB->GetXaxis()->SetTitle("TP (ADC)") ;
  TH1F * TPEEPlus = new TH1F("TPEEPlus", "TP: EE Plus", 256, 0., 256.) ;
  TPEEPlus->GetXaxis()->SetTitle("TP (ADC)") ;
  TH1F * TPEEMinus = new TH1F("TPEEMinus", "TP: EE Minus", 256, 0., 256.) ;
  TPEEMinus->GetXaxis()->SetTitle("TP (ADC)") ;

  //from silvia
  TH1F * TPEB_noSpike = new TH1F("TPEB_noSpike", "low energy spike removed TP: Barrel", 256, 0., 256.) ;
  TPEB_noSpike->GetXaxis()->SetTitle("TP (ADC)") ;
    

  TH1F *TPEB_fullReadout = new TH1F("TPEB_fullReadout", "TP, full readout: Barrel", 256, 0., 256.) ;
  TPEB_fullReadout->GetXaxis()->SetTitle("TP (ADC)") ;
  TH1F *TP_emulatedTPEnergy_ratio_EB = new TH1F( "TP_emulatedTPEnergy_ratio_EB", "TP emulatedTP crystal energy ratio: Barrel", 100, 0.,20.) ;
   
  TH1F *TPEEPlus_fullReadout = new TH1F("TPEEPlus_fullReadout", "TP, full readout: EE Plus", 256, 0., 256.) ;
  TPEEPlus_fullReadout->GetXaxis()->SetTitle("TP (ADC)") ;
  TH1F *TP_emulatedTPEnergy_ratio_EEPlus = new TH1F( "TP_emulatedTPEnergy_ratio_EEPlus", "TP emulatedTP crystal energy ratio: EE Plus",100, 0., 20.) ;
   
  TH1F *TPEEMinus_fullReadout = new TH1F("TPEEMinus_fullReadout", "TP, full readout: EE Minus", 256, 0., 256.) ;
  TPEEMinus_fullReadout->GetXaxis()->SetTitle("TP (ADC)") ;
  TH1F *TP_emulatedTPEnergy_ratio_EEMinus = new TH1F( "TP_emulatedTPEnergy_ratio_EEMinus", "TP emulatedTP crystal energy ratio: EE Minus", 100, 0., 20.) ;

  //2d TPEt vs emulatedTP
 
  TH2F * TP_vs_emulatedTP_EEMinus = new TH2F("TP_vs_emulatedTP_EEMinus", "TP vs emulatedTP ",  400, 0.,400., 400, 0., 400.);
  TP_vs_emulatedTP_EEMinus->GetYaxis()->SetTitle("TP (ADC)") ;
  TP_vs_emulatedTP_EEMinus->GetXaxis()->SetTitle(" emulatedTP (ADC)") ;
 
  TH2F * TP_vs_emulatedTP_EEMinus_18_22 = new TH2F("TP_vs_emulatedTP_EEMinus_18_22", "TP vs emulatedTP 18-22",  400, 0.,400., 400, 0., 400.);
  TP_vs_emulatedTP_EEMinus_18_22->GetYaxis()->SetTitle("TP (ADC)") ;
  TP_vs_emulatedTP_EEMinus_18_22->GetXaxis()->SetTitle(" emulatedTP (ADC)") ;

  TH2F * TP_vs_emulatedTP_EEMinus_23_27 = new TH2F("TP_vs_emulatedTP_EEMinus_23_27", "TP vs emulatedTP 23-27",  400, 0.,400., 400, 0., 400.);
  TP_vs_emulatedTP_EEMinus_23_27->GetYaxis()->SetTitle("TP (ADC)") ;
  TP_vs_emulatedTP_EEMinus_23_27->GetXaxis()->SetTitle(" emulatedTP (ADC)") ;

  TH2F * TP_vs_emulatedTP_EEMinus_28_end = new TH2F("TP_vs_emulatedTP_EEMinus_28_end", "TP vs emulatedTP 28-end",  400, 0.,400., 400, 0., 400.);
  TP_vs_emulatedTP_EEMinus_28_end->GetYaxis()->SetTitle("TP (ADC)") ;
  TP_vs_emulatedTP_EEMinus_28_end->GetXaxis()->SetTitle(" emulatedTP (ADC)") ;



  TH2F * TP_vs_emulatedTP_EEPlus_18_22 = new TH2F("TP_vs_emulatedTP_EEPlus_18_22", "TP vs emulatedTP ieta 18-22 ",  400, 0.,400., 400, 0., 400.);
  TP_vs_emulatedTP_EEPlus_18_22->GetYaxis()->SetTitle("TP (ADC)") ;
  TP_vs_emulatedTP_EEPlus_18_22->GetXaxis()->SetTitle(" emulatedTP (ADC)") ;

  TH2F * TP_vs_emulatedTP_EEPlus_23_27 = new TH2F("TP_vs_emulatedTP_EEPlus_23_27", "TP vs emulatedTP ieta 23-27",  400, 0.,400., 400, 0., 400.);
  TP_vs_emulatedTP_EEPlus_23_27->GetYaxis()->SetTitle("TP (ADC)") ;
  TP_vs_emulatedTP_EEPlus_23_27->GetXaxis()->SetTitle(" emulatedTP (ADC)") ;

  TH2F * TP_vs_emulatedTP_EEPlus_28_end = new TH2F("TP_vs_emulatedTP_EEPlus_28_end", "TP vs emulatedTP 28-end",  400, 0.,400., 400, 0., 400.);
  TP_vs_emulatedTP_EEPlus_28_end->GetYaxis()->SetTitle("TP (ADC)") ;
  TP_vs_emulatedTP_EEPlus_28_end->GetXaxis()->SetTitle(" emulatedTP (ADC)") ;


  TH2F * TP_vs_emulatedTP_EEPlus = new TH2F("TP_vs_emulatedTP_EEPlus", "TP vs emulatedTP ",  400, 0.,400., 400, 0., 400.);
  TP_vs_emulatedTP_EEPlus->GetYaxis()->SetTitle("TP (ADC)") ;
  TP_vs_emulatedTP_EEPlus->GetXaxis()->SetTitle(" emulatedTP (ADC)") ;

  TH2F * TP_vs_emulatedTP_EB = new TH2F("TP_vs_emulatedTP_EB", "TP vs emulatedTP ",  400, 0.,400., 400, 0., 400.);
  TP_vs_emulatedTP_EB->GetYaxis()->SetTitle("TP (ADC)") ;
  TP_vs_emulatedTP_EB->GetXaxis()->SetTitle(" emulatedTP (ADC)") ;

  //ratio vs energy
  TH2F * TP_emul_ratio_vs_Et_EEPlus = new TH2F("TP_emul_ratio_vs_Et_EEPlus", "TP_emul_ratio vs Et ",  400, 0.,400., 400, 0., 400.);
  TP_emul_ratio_vs_Et_EEPlus->GetYaxis()->SetTitle("ratio") ;
  TP_emul_ratio_vs_Et_EEPlus->GetXaxis()->SetTitle(" Et (Gev)") ;
  
  TH2F * TP_emul_ratio_vs_Et_EB = new TH2F("TP_emul_ratio_vs_Et_EB", "TP_emul_ratio vs Et ",  400, 0.,400., 400, 0., 400.);
  TP_emul_ratio_vs_Et_EB->GetYaxis()->SetTitle("ratio") ;
  TP_emul_ratio_vs_Et_EB->GetXaxis()->SetTitle(" Et (Gev)") ;

  TH2F * TP_emul_ratio_vs_Et_EEMinus = new TH2F("TP_emul_ratio_vs_Et_EEMinus", "TP_emul_ratio vs Et ",  400, 0.,400., 400, 0., 400.);
  TP_emul_ratio_vs_Et_EEMinus->GetYaxis()->SetTitle("ratio") ;
  TP_emul_ratio_vs_Et_EEMinus->GetXaxis()->SetTitle(" Et (Gev)") ;


 

  //2D profile
  TH2F * TP_EB2D = new TH2F("TP_EB2D", "TP_ADC: Barrel", 72, 1, 73, 38, -19, 19) ;
  TP_EB2D->GetYaxis()->SetTitle("eta index") ;
  TP_EB2D->GetXaxis()->SetTitle("phi index") ;

  TH2F * TP_EEPlus2D = new TH2F("TP_EEPlus2D", "TP_ADC: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
  TP_EEPlus2D->GetYaxis()->SetTitle("y index") ;
  TP_EEPlus2D->GetXaxis()->SetTitle("x index") ;
  TH2F * TP_EEMinus2D = new TH2F("TP_EEMinus2D", "TP_ADC: Minus2D Endcap", 121, -10, 111, 121, -10, 111) ;
  TP_EEMinus2D->GetYaxis()->SetTitle("y index") ;
  TP_EEMinus2D->GetXaxis()->SetTitle("x index") ;
  

  TH2F * ADC_emulatedTP_EB2D = new TH2F("ADC_emulatedTP_EB2D", "ADC_emulatedTP: Barrel", 72, 1, 73, 38, -19, 19) ;
  ADC_emulatedTP_EB2D->GetYaxis()->SetTitle("eta index") ;
  ADC_emulatedTP_EB2D->GetXaxis()->SetTitle("phi index") ;

  TH2F * ADC_emulatedTP_EEPlus2D = new TH2F("ADC_emulatedTP_EEPlus2D", "ADC_emulatedTP: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
  ADC_emulatedTP_EEPlus2D->GetYaxis()->SetTitle("y index") ;
  ADC_emulatedTP_EEPlus2D->GetXaxis()->SetTitle("x index") ;
  TH2F * ADC_emulatedTP_EEMinus2D = new TH2F("ADC_emulatedTP_EEMinus2D", "ADC_emulatedTP: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
  ADC_emulatedTP_EEMinus2D->GetYaxis()->SetTitle("y index") ;
  ADC_emulatedTP_EEMinus2D->GetXaxis()->SetTitle("x index") ;
  //outlier spectra
  TH1F * TPSpect_TPvemulatedTP_outliers_EEMinus = new TH1F("TPSpect_TPvemulatedTP_outliers_EEMinus", "TPSpect_TPvemulatedTP_outliers:Barrel ",  256, 0., 256.) ;
  TPSpect_TPvemulatedTP_outliers_EEMinus->GetYaxis()->SetTitle("TP (ADC)") ;


  TH1F * TPSpect_TPvemulatedTP_outliers_EEPlus = new TH1F("TPSpect_TPvemulatedTP_outliers_EEPlus", "TPSpect_TPvemulatedTP_outliers :EEPlus ",  256, 0., 256.) ;
  TPSpect_TPvemulatedTP_outliers_EEPlus->GetYaxis()->SetTitle("TP (ADC)") ;

  TH1F * TPSpect_TPvemulatedTP_outliers_EB = new TH1F("TPSpect_TPvemulatedTP_outliers_EB", "TPSpect_TPvemulatedTP_outliers :EEMinus",  256, 0., 256.) ;
  TPSpect_TPvemulatedTP_outliers_EB->GetYaxis()->SetTitle("TP (ADC)") ;



  
  



  //new mismatch Spectra

  TH1F * TPEtaEBmisSpec = new TH1F ("TPEtaEBmisSpec", "TP: Barrel", 256, 0., 256.) ;
  TPEtaEBmisSpec->GetXaxis()->SetTitle("TP (ADC)") ;
  TH1F * TPEtaEEPlusmisSpec = new TH1F ("TPEtaEEPlusmisSpec", "TP: Barrel", 256, 0., 256.) ;
  TPEtaEEPlusmisSpec->GetXaxis()->SetTitle("TP (ADC)") ;
  TH1F * TPEtaEEMinusmisSpec = new TH1F ("TPEtaEEMinusmisSpec", "TP: Barrel", 256, 0., 256.) ;
  TPEtaEEMinusmisSpec->GetXaxis()->SetTitle("TP (ADC)") ;





  //new Nabarun
  TH1F * TPEmulEB_whenTPRealexists = new TH1F("TPEmulEB_whenTPRealexists", "Emul TP{BX0} when real non zero TP exists", 256, 0., 256.) ;
  TPEmulEB_whenTPRealexists->GetXaxis()->SetTitle("TP (ADC)") ;


  TH1F * TPEmulEEPlus_whenTPRealexists = new TH1F("TPEmulEEPlus_whenTPRealexists", "Emul TP{BX0} when real non zero TP exists", 256, 0., 256.) ;
  TPEmulEEPlus_whenTPRealexists->GetXaxis()->SetTitle("TP (ADC)") ;

  TH1F * TPEmulEEMinus_whenTPRealexists = new TH1F("TPEmulEEMinus_whenTPRealexists", "Emul TP{BX0} when real non zero TP exists", 256, 0., 256.) ;
  TPEmulEEMinus_whenTPRealexists->GetXaxis()->SetTitle("TP (ADC)") ;

  TH1F * TPEmulEB_when_no_NZ_TPReal = new TH1F("TPEmulEB_when_no_NZ_TPReal", "Emul TP{BX0} when no non zero TP exists", 256, 0., 256.) ;
  TPEmulEB_when_no_NZ_TPReal->GetXaxis()->SetTitle("TP (ADC)") ;


  TH1F * TPEmulEEPlus_when_no_NZ_TPReal = new TH1F("TPEmulEEPlus_when_no_NZ_TPReal", "Emul TP{BX0} when no non zero TP exists", 256, 0., 256.) ;
  TPEmulEEPlus_when_no_NZ_TPReal->GetXaxis()->SetTitle("TP (ADC)") ;

  TH1F * TPEmulEEMinus_when_no_NZ_TPReal = new TH1F("TPEmulEEMinus_when_no_NZ_TPReal", "Emul TP{BX0} when no non zero TP exists", 256, 0., 256.) ;
  TPEmulEEMinus_when_no_NZ_TPReal->GetXaxis()->SetTitle("TP (ADC)") ;

  //ratio distribution histograms
  TH1F * Ratio_EEPlus_whenTPRealexists = new TH1F("Ratio_EEPlus_whenTPRealexists", "Distribution of ratio EMUL/REAL: When NZ real exists", 70, 0., 3.5) ;
  Ratio_EEPlus_whenTPRealexists->GetXaxis()->SetTitle("Ratio_Emul_to_TP_whenNZRealTPexist");
  TH1F * Ratio_EEMinus_whenTPRealexists = new TH1F("Ratio_EEMinus_whenTPRealexists", "Distribution of ratio EMUL/REAL: When NZ real exists", 70, 0., 3.5) ;
  Ratio_EEMinus_whenTPRealexists->GetXaxis()->SetTitle("Ratio_Emul_to_TP_whenNZRealTPexist");
  TH1F * Ratio_EB_whenTPRealexists = new TH1F("Ratio_EB_whenTPRealexists", "Distribution of ratio EMUL/REAL: When NZ real exists", 60, 0., 3.) ;
  Ratio_EB_whenTPRealexists->GetXaxis()->SetTitle("Ratio_Emul_to_TP_whenNZRealTPexist");


  
  TH1F * TPEmulEB = new TH1F("TPEmulEB", "Emulated TPs: Barrel", 256, 0., 256.) ;
  TPEmulEB->GetXaxis()->SetTitle("TP (ADC)") ;
  TH1F * TPEmulEEPlus = new TH1F("TPEmulEEPlus", "Emulated TPs: EE Plus", 256, 0., 256.) ;
  TPEmulEEPlus->GetXaxis()->SetTitle("TP (ADC)") ;
  TH1F * TPEmulEEMinus = new TH1F("TPEmulEEMinus", "Emulated TPs: EE Minus", 256, 0., 256.) ;
  TPEmulEEMinus->GetXaxis()->SetTitle("TP (ADC)") ;
   
  TH1F * TPEmulMaxEB = new TH1F("TPEmulMaxEB", "TP Emulator max: Barrel", 256, 0., 256.) ;
  TPEmulMaxEB->GetXaxis()->SetTitle("TP (ADC)") ;
  TH1F * TPEmulMaxEEPlus = new TH1F("TPEmulMaxEEPlus", "TP Emulator max: Plus Endcap", 256, 0., 256.) ;
  TPEmulMaxEEPlus->GetXaxis()->SetTitle("TP (ADC)") ;
  TH1F * TPEmulMaxEEMinus = new TH1F("TPEmulMaxEEMinus", "TP Emulator max: Minus Endcap", 256, 0., 256.) ;
  TPEmulMaxEEMinus->GetXaxis()->SetTitle("TP (ADC)") ;
   
  TH2F * TPEmulMapMaxIndexEEPlus = new TH2F("TPEmulMapMaxIndexEEPlus", "Map Index of the max TP from Emulator: Plus Endcap",  121, -10, 111, 121, -10, 111);
  TPEmulMapMaxIndexEEPlus->GetYaxis()->SetTitle("y index") ;
  TPEmulMapMaxIndexEEPlus->GetXaxis()->SetTitle("x index") ;
  TH2F * TPEmulMapMaxIndexEEMinus = new TH2F("TPEmulMapMaxIndexEEMinus", "Map Index of the max TP from Emulator: Minus Endcap",  121, -10, 111, 121, -10, 111)  ;
  TPEmulMapMaxIndexEEMinus->GetYaxis()->SetTitle("y index") ;
  TPEmulMapMaxIndexEEMinus->GetXaxis()->SetTitle("x index") ;
  TH2F * TPEmulMapMaxIndexEB = new TH2F("TPEmulMapMaxIndexEB", "Map Index of the max TP from Emulator: Barrel",   72, 1, 73, 38, -19, 19) ;
  TPEmulMapMaxIndexEB->GetYaxis()->SetTitle("eta index") ;
  TPEmulMapMaxIndexEB->GetXaxis()->SetTitle("phi index") ;
   
   
  TH3F * TPspectrumMap3DEB = new TH3F("TPspectrumMap3DEB", "TP  spectrum map: Barrel", 72, 1, 73, 38, -19, 19, 256, 0., 256.) ;
  TPspectrumMap3DEB->GetYaxis()->SetTitle("eta index") ;
  TPspectrumMap3DEB->GetXaxis()->SetTitle("phi index") ;
   
  TH3F * TPspectrumMap3DEEPlus = new TH3F("TPspectrumMap3DEEPlus", "TP  spectrum map: Plus Endcap", 121, -10, 111, 121, -10, 111, 256, -0.5, 255.5) ;
  TPspectrumMap3DEEPlus->GetYaxis()->SetTitle("y index") ;
  TPspectrumMap3DEEPlus->GetXaxis()->SetTitle("x index") ;
  TH3F * TPspectrumMap3DEEMinus = new TH3F("TPspectrumMap3DEEMinus", "TP  spectrum map: Minus Endcap", 121, -10, 111, 121, -10, 111, 256, 0., 256.) ;
  TPspectrumMap3DEEMinus->GetYaxis()->SetTitle("y index") ;
  TPspectrumMap3DEEMinus->GetXaxis()->SetTitle("x index") ;
   
   
  TH1F * TPMatchEmulEB = new TH1F("TPMatchEmulEB", "TP data matching Emulator: Barrel", 7, -1., 6) ;
  TPMatchEmulEB->GetXaxis()->SetTitle("Emulator Index") ;
  TH1F * TPMatchEmulEEPlus = new TH1F("TPMatchEmulEEPlus", "TP data matching Emulator: Plus Endcap", 7, -1., 6) ;
  TPMatchEmulEEPlus->GetXaxis()->SetTitle("Emulator Index") ;
  TH1F * TPMatchEmulEEMinus = new TH1F("TPMatchEmulEEMinus", "TP data matching Emulator: Minus Endcap", 7, -1., 6) ;
  TPMatchEmulEEMinus->GetXaxis()->SetTitle("Emulator Index") ;
  TH1F * TPEmulMaxIndexEB = new TH1F("TPEmulMaxIndexEB", "Index of the max TP from Emulator: Barrel", 7, -1., 6) ;
  TPEmulMaxIndexEB->GetXaxis()->SetTitle("Emulator Index") ;
  TH1F * TPEmulMaxIndexEEPlus = new TH1F("TPEmulMaxIndexEEPlus", "Index of the max TP from Emulator: Plus Endcap", 7, -1., 6) ;
  TPEmulMaxIndexEEPlus->GetXaxis()->SetTitle("Emulator Index") ;
  TH1F * TPEmulMaxIndexEEMinus = new TH1F("TPEmulMaxIndexEEMinus", "Index of the max TP from Emulator: Minus Endcap", 7, -1., 6) ;
  TPEmulMaxIndexEEMinus->GetXaxis()->SetTitle("Emulator Index") ;
  TH3I * TPMatchEmul3D = new TH3I("TPMatchEmul3D", "TP data matching Emulator", 72, 1, 73, 57, -28, 29, 7, -1, 6) ;
  TPMatchEmul3D->GetYaxis()->SetTitle("eta index") ;
  TPMatchEmul3D->GetXaxis()->SetTitle("phi index") ;
  TH3I * TPEmulMax3D = new TH3I("TPEmulMax3D", "Index of max TP Emulator 3D", 72, 1, 73, 57, -28, 29, 7, -1, 6) ;
  TPEmulMax3D->GetYaxis()->SetTitle("eta index") ;
  TPEmulMax3D->GetXaxis()->SetTitle("phi index") ;
   
  TH2F * TPCompEmulEB = new TH2F("TPCompEmulEB", "Number of TP-Emulator comparisons: Barrel", 72, 1, 73, 38, -19, 19) ;
  TPCompEmulEB->GetYaxis()->SetTitle("eta index") ; 
  TPCompEmulEB->GetXaxis()->SetTitle("phi index") ;
  TH2F * TPCompEmulEEPlus = new TH2F("TPCompEmulEEPlus", "Number of TP-Emulator comparisons: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
  TPCompEmulEEPlus->GetYaxis()->SetTitle("y index") ; 
  TPCompEmulEEPlus->GetXaxis()->SetTitle("x index") ;
  TH2F * TPCompEmulEEMinus = new TH2F("TPCompEmulEEMinus", "Number of TP-Emulator comparisons: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
  TPCompEmulEEMinus->GetYaxis()->SetTitle("y index") ; 
  TPCompEmulEEMinus->GetXaxis()->SetTitle("x index") ;
   
   
   
  TH2F * TPTimingEBFromEmulOK = new TH2F("TPTimingEBFromEmulOK", "Good TP Timing: Barrel", 72, 1, 73, 38, -19, 19) ;
  TPTimingEBFromEmulOK->GetYaxis()->SetTitle("eta index") ;
  TPTimingEBFromEmulOK->GetXaxis()->SetTitle("phi index") ;
  TH2F * TPTimingEBFromEmulOKAndMatch = new TH2F("TPTimingEBFromEmulOKAndMatch", "Good TP Timing and match: Barrel", 72, 1, 73, 38, -19, 19) ;
  TPTimingEBFromEmulOKAndMatch->GetYaxis()->SetTitle("eta index") ;
  TPTimingEBFromEmulOKAndMatch->GetXaxis()->SetTitle("phi index") ;
  TH2F * TPTimingEBFromEmulWrong = new TH2F("TPTimingEBFromEmulWrong", "Wrong TP Timing: Barrel", 72, 1, 73, 38, -19, 19) ;
  TPTimingEBFromEmulWrong->GetYaxis()->SetTitle("eta index") ;
  TPTimingEBFromEmulWrong->GetXaxis()->SetTitle("phi index") ;
   
  TH2F * TPTimingEEMinusFromEmulOK = new TH2F("TPTimingEEMinusFromEmulOK", "Good TP Timing: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
  TPTimingEEMinusFromEmulOK->GetYaxis()->SetTitle("y index") ; 
  TPTimingEEMinusFromEmulOK->GetXaxis()->SetTitle("x index") ;
  TH2F * TPTimingEEMinusFromEmulOKAndMatch= new TH2F("TPTimingEEMinusFromEmulOKAndMatch", "Good TP Timing and match: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
  TPTimingEEMinusFromEmulOK->GetYaxis()->SetTitle("y index") ; 
  TPTimingEEMinusFromEmulOK->GetXaxis()->SetTitle("x index") ;
  TH2F * TPTimingEEMinusFromEmulWrong = new TH2F("TPTimingEEMinusFromEmulWrong", "Wrong TP Timing: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
  TPTimingEEMinusFromEmulOK->GetYaxis()->SetTitle("y index") ; 
  TPTimingEEMinusFromEmulOK->GetXaxis()->SetTitle("x index") ;
   
  TH2F * TPTimingEEPlusFromEmulOK = new TH2F("TPTimingEEPlusFromEmulOK", "Good TP Timing: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
  TPTimingEEPlusFromEmulOK->GetYaxis()->SetTitle("y index") ; 
  TPTimingEEPlusFromEmulOK->GetXaxis()->SetTitle("x index") ;
  TH2F * TPTimingEEPlusFromEmulOKAndMatch= new TH2F("TPTimingEEPlusFromEmulOKAndMatch", "Good TP Timing and match: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
  TPTimingEEPlusFromEmulOK->GetYaxis()->SetTitle("y index") ; 
  TPTimingEEPlusFromEmulOK->GetXaxis()->SetTitle("x index") ;
  TH2F * TPTimingEEPlusFromEmulWrong = new TH2F("TPTimingEEPlusFromEmulWrong", "Wrong TP Timing: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
  TPTimingEEPlusFromEmulOK->GetYaxis()->SetTitle("y index") ; 
  TPTimingEEPlusFromEmulOK->GetXaxis()->SetTitle("x index") ;
   
   
  TH2I * ttfMismatchEB = new TH2I("ttfMismatchEB", "TTF mismatch map",  72, 1, 73, 38, -19, 19) ;
  ttfMismatchEB->GetYaxis()->SetTitle("eta index") ;
  ttfMismatchEB->GetXaxis()->SetTitle("phi index") ;
  TH2I * ttfMismatchEEPlus = new TH2I("ttfMismatchEEPlus", "TTF mismatch map: Plus Endcap",  121, -10, 111, 121, -10, 111) ;
  ttfMismatchEEPlus->GetYaxis()->SetTitle("y index") ;
  ttfMismatchEEPlus->GetXaxis()->SetTitle("x index") ;
  TH2I * ttfMismatchEEMinus = new TH2I("ttfMismatchEEMinus", "TTF mismatch map: Minus Endcap",  121, -10, 111, 121, -10, 111) ;
  ttfMismatchEEMinus->GetYaxis()->SetTitle("y index") ;
  ttfMismatchEEMinus->GetXaxis()->SetTitle("x index") ;
   
   
  std::stringstream title1 ;
  if (l1algo.size()==0) title1 <<"TPEmul_vs_bx"<<" tp>"<<occupancyCut;
  else title1 <<"TPEmul_vs_bx"<<" tp>"<<occupancyCut<<" l1="<<l1algo;
  TH2F * bx_Vs_TPEmul = new TH2F("TPEmul_vs_bx", title1.str().c_str(),3570, 0, 3570, 256, 0, 256) ;
  bx_Vs_TPEmul->GetYaxis()->SetTitle("TP Emul") ;
  bx_Vs_TPEmul->GetXaxis()->SetTitle("Bunch crossing") ;
   
  std::stringstream title2 ;
  if (l1algo.size()==0) title2 <<"TP_vs_bx"<<" tp>"<<occupancyCut;
  else title2 <<"TP_vs_bx"<<" tp>"<<occupancyCut<<" l1="<<l1algo;
  TH2F * bx_Vs_TP = new TH2F("TP_vs_bx", title2.str().c_str(),3570, 0, 3570, 256, 0, 256) ;
  bx_Vs_TP->GetYaxis()->SetTitle("TP") ;
  bx_Vs_TP->GetXaxis()->SetTitle("Bunch crossing") ;
   
  std::stringstream title3 ;
  if (l1algo.size()==0) title3 <<"Orbit_vs_bx"<<" tp>"<<occupancyCut;
  else title3 <<"Orbit_vs_bx"<<" tp>"<<occupancyCut<<" l1="<<l1algo;
  TH2F * bx_Vs_Orbit = new TH2F("Orbit_vs_bx", title3.str().c_str(),3570, 0, 3570, 1000, slMinOrb,slMaxOrb) ;
  bx_Vs_Orbit->GetYaxis()->SetTitle("Orbit / 10^6") ;
  bx_Vs_Orbit->GetXaxis()->SetTitle("Bunch crossing") ;
   
  std::stringstream title4 ;
  if (l1algo.size()==0) title4 <<"TriggerBit_vs_bx"<<" tp>"<<occupancyCut;
  else title4 <<"TriggerBit_vs_bx"<<" tp>"<<occupancyCut<<" l1="<<l1algo;
  TH2F * bx_Vs_TriggerBit = new TH2F("TriggerBit_vs_bx", title4.str().c_str(),3570, 0, 3570, 256, 0, 64) ;
  bx_Vs_TriggerBit->GetYaxis()->SetTitle("Trigger Bit") ;
  bx_Vs_TriggerBit->GetXaxis()->SetTitle("Bunch crossing") ;
   
  std::stringstream title5 ;
  if (l1algo.size()==0) title5 <<"bx"<<" tp>"<<occupancyCut<<" l1bx"<<l1algobx;
  else title5 <<"bx"<<" tp>"<<occupancyCut<<" l1="<<l1algo<<" l1bx"<<l1algobx;
  TH1F * bx = new TH1F("bx", title5.str().c_str(), 3570, 0, 3570) ;
  bx->GetXaxis()->SetTitle("Bunch crossing ") ;
   
  std::stringstream title6 ;
  if (l1algo.size()==0) title6 <<"time"<<" tp>"<<occupancyCut<<" l1"<<l1algo;
  else title6 <<"time"<<" tp>"<<occupancyCut<<" l1="<<l1algo<<" l1"<<l1algo;
  TH1F * time = new TH1F("time", title6.str().c_str(), 3570, 0, 3570) ;
  time->GetXaxis()->SetTitle("Bunch crossing ") ;
   
   
  /////////////////////////
  //L1 candidate histograms
  /////////////////////////
   
  TH1F * nbOfL1IsoCands = new TH1F("nbOfL1IsoCands", "nbOfL1IsoCands", 5, 0., 5.) ;
  TH1F * nbOfL1NonisoCands = new TH1F("nbOfL1NonisoCands", "nbOfL1NonisoCands", 5, 0., 5.) ; 
  TH1F * L1IsoCandRank = new TH1F("L1IsoCandRank", "L1IsoCandRank", 64, 0., 64) ;
  TH1F * L1NonisoCandRank = new TH1F("L1NonisoCandRank", "L1NonisoCandRank", 64, 0., 64) ; 
   
  TH1F * nbOfL1preIsoCands = new TH1F("nbOfL1preIsoCands", "nbOfL1preIsoCands", 5, 0., 5.) ;
  TH1F * nbOfL1preNonisoCands = new TH1F("nbOfL1preNonisoCands", "nbOfL1preNonisoCands", 5, 0., 5.) ; 
  TH1F * L1preIsoCandRank = new TH1F("L1preIsoCandRank", "L1preIsoCandRank", 64, 0., 64) ;
  TH1F * L1preNonisoCandRank = new TH1F("L1preNonisoCandRank", "L1preNonisoCandRank", 64, 0., 64) ; 
   
  TH1F * nbOfL1postIsoCands = new TH1F("nbOfL1postIsoCands", "nbOfL1postIsoCands", 5, 0., 5.) ;
  TH1F * nbOfL1postNonisoCands = new TH1F("nbOfL1postNonisoCands", "nbOfL1postNonisoCands", 5, 0., 5.) ; 
  TH1F * L1postIsoCandRank = new TH1F("L1postIsoCandRank", "L1postIsoCandRank", 64, 0., 64) ;
  TH1F * L1postNonisoCandRank = new TH1F("L1postNonisoCandRank", "L1postNonisoCandRank", 64, 0., 64) ; 
   
  TH1F * L1Isotiming = new TH1F("L1Isotiming", "L1Isotiming", 5, -2., 3.) ;
  TH1F * L1Nonisotiming = new TH1F("L1Nonisotiming", "L1Nonisotiming", 5, -2., 3.) ;
   
  TH1F * L1IsotimingEB = new TH1F("L1IsotimingEB", "L1IsotimingEB", 5, -2., 3.) ;
  TH1F * L1NonisotimingEB = new TH1F("L1NonisotimingEB", "L1NonisotimingEB", 5, -2., 3.) ;
   
  TH1F * L1IsotimingEEPlus = new TH1F("L1IsotimingEEPlus", "L1IsotimingEEPlus", 5, -2., 3.) ;
  TH1F * L1NonisotimingEEPlus = new TH1F("L1NonisotimingEEPlus", "L1NonisotimingEEPlus", 5, -2., 3.) ;
   
  TH1F * L1IsotimingEEMinus = new TH1F("L1IsotimingEEMinus", "L1IsotimingEEMinus", 5, -2., 3.) ;
  TH1F * L1NonisotimingEEMinus = new TH1F("L1NonisotimingEEMinus", "L1NonisotimingEEMinus", 5, -2., 3.) ;

  // prefcheck


  TH1F * ptisoontime = new TH1F("ptisoontime", "L1 Spectrum", 64, 0., 64.) ;
  ptisoontime->GetXaxis()->SetTitle("Pt (GeV)") ;
 

  TH1F * ptnonisoontime = new TH1F("ptnonisoontime", "L1 Spectrum", 64, 0., 64.) ;
  ptnonisoontime->GetXaxis()->SetTitle("Pt (GeV)") ;



  TH1F * ptisopostfiring = new TH1F("ptisopostfiring", "L1 Spectrum", 64, 0., 64.) ;
  ptisopostfiring->GetXaxis()->SetTitle("Pt (GeV)") ;
 

  TH1F * ptnonisopostfiring = new TH1F("ptnonisopostfiring", "L1 Spectrum", 64, 0., 64.) ;
  ptnonisopostfiring->GetXaxis()->SetTitle("Pt (GeV)") ;


  TH1F * ptisoprefiring = new TH1F("ptisoprefiring", "L1 Spectrum", 64, 0., 64.) ;
  ptisoprefiring->GetXaxis()->SetTitle("Pt (GeV)") ;
 

  TH1F * ptnonisoprefiring = new TH1F("ptnonisoprefiring", "L1 Spectrum", 64, 0., 64.) ;
  ptnonisoprefiring->GetXaxis()->SetTitle("Pt (GeV)") ;


   
  //all ecal l1 occupancy
  TH2F * occupancyL1Iso = new TH2F("occupancyL1Iso", "Iso L1 Occupancy", 14, 4, 18, 18, 0, 18) ;
  occupancyL1Iso->GetXaxis()->SetTitle("RCT eta index") ;
  occupancyL1Iso->GetYaxis()->SetTitle("RCT phi index") ;
  TH2F * occupancyL1Noniso = new TH2F("occupancyL1Noniso", "Noniso L1 Occupancy", 14, 4, 18, 18, 0, 18) ;
  occupancyL1Noniso->GetXaxis()->SetTitle("RCT eta index") ;
  occupancyL1Noniso->GetYaxis()->SetTitle("RCT phi index") ;
  TH2F * occupancyL1preIso = new TH2F("occupancyL1preIso", "Pre-firing Iso L1 Occupancy", 14, 4, 18, 18, 0, 18) ;
  occupancyL1preIso->GetXaxis()->SetTitle("RCT eta index") ;
  occupancyL1preIso->GetYaxis()->SetTitle("RCT phi index") ;
  TH2F * occupancyL1preNoniso = new TH2F("occupancyL1preNoniso", "Pre-firing Noniso L1 Occupancy", 14, 4, 18, 18, 0, 18) ;
  occupancyL1preNoniso->GetXaxis()->SetTitle("RCT eta index") ;
  occupancyL1preNoniso->GetYaxis()->SetTitle("RCT phi index") ;
  TH2F * occupancyL1postIso = new TH2F("occupancyL1postIso", "Post-firing Iso L1 Occupancy", 14, 4, 18, 18, 0, 18) ;
  occupancyL1postIso->GetXaxis()->SetTitle("RCT eta index") ;
  occupancyL1postIso->GetYaxis()->SetTitle("RCT phi index") ;
  TH2F * occupancyL1postNoniso = new TH2F("occupancyL1postNoniso", "Post-firing Noniso L1 Occupancy", 14, 4, 18, 18, 0, 18) ;
  occupancyL1postNoniso->GetXaxis()->SetTitle("RCT eta index") ;
  occupancyL1postNoniso->GetYaxis()->SetTitle("RCT phi index") ;
   
  //barrel l1 occupancy
  TH2F * occupancyL1IsoEB = new TH2F("occupancyL1IsoEB", "L1Iso Occupancy: Barrel", 72, 1, 73, 38, -19, 19) ;
  occupancyL1IsoEB->GetYaxis()->SetTitle("eta index") ;
  occupancyL1IsoEB->GetXaxis()->SetTitle("phi index") ;
  TH2F * occupancyL1NonisoEB = new TH2F("occupancyL1NonisoEB", "L1Noniso Occupancy: Barrel", 72, 1, 73, 38, -19, 19) ;
  occupancyL1NonisoEB->GetYaxis()->SetTitle("eta index") ;
  occupancyL1NonisoEB->GetXaxis()->SetTitle("phi index") ;
  TH2F * occupancyL1preIsoEB = new TH2F("occupancyL1preIsoEB", "Pre-firing L1Iso Occupancy: Barrel", 72, 1, 73, 38, -19, 19) ;
  occupancyL1preIsoEB->GetYaxis()->SetTitle("eta index") ;
  occupancyL1preIsoEB->GetXaxis()->SetTitle("phi index") ;
  TH2F * occupancyL1preNonisoEB = new TH2F("occupancyL1preNonisoEB", "Pre-firing L1Noniso Occupancy: Barrel", 72, 1, 73, 38, -19, 19) ;
  occupancyL1preNonisoEB->GetYaxis()->SetTitle("eta index") ;
  occupancyL1preNonisoEB->GetXaxis()->SetTitle("phi index") ;
  TH2F * occupancyL1postIsoEB = new TH2F("occupancyL1postIsoEB", "Post-firing L1Iso Occupancy: Barrel", 72, 1, 73, 38, -19, 19) ;
  occupancyL1postIsoEB->GetYaxis()->SetTitle("eta index") ;
  occupancyL1postIsoEB->GetXaxis()->SetTitle("phi index") ;
  TH2F * occupancyL1postNonisoEB = new TH2F("occupancyL1postNonisoEB", "Post-firing L1Noniso Occupancy: Barrel", 72, 1, 73, 38, -19, 19) ;
  occupancyL1postNonisoEB->GetYaxis()->SetTitle("eta index") ;
  occupancyL1postNonisoEB->GetXaxis()->SetTitle("phi index") ;
   
  //endcap l1 occupancy
  TH2F * occupancyL1IsoEEPlus = new TH2F("occupancyL1IsoEEPlus", "L1Iso Occupancy: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
  occupancyL1IsoEEPlus->GetYaxis()->SetTitle("y index") ;
  occupancyL1IsoEEPlus->GetXaxis()->SetTitle("x index") ;
  TH2F * occupancyL1IsoEEMinus = new TH2F("occupancyL1IsoEEMinus", "L1Iso Occupancy: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
  occupancyL1IsoEEMinus->GetYaxis()->SetTitle("y index") ;
  occupancyL1IsoEEMinus->GetXaxis()->SetTitle("x index") ;
  TH2F * occupancyL1NonisoEEPlus = new TH2F("occupancyL1NonisoEEPlus", "L1Noniso Occupancy: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
  occupancyL1NonisoEEPlus->GetYaxis()->SetTitle("y index") ;
  occupancyL1NonisoEEPlus->GetXaxis()->SetTitle("x index") ;
  TH2F * occupancyL1NonisoEEMinus = new TH2F("occupancyL1NonisoEEMinus", "L1Noniso Occupancy: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
  occupancyL1NonisoEEMinus->GetYaxis()->SetTitle("y index") ;
  occupancyL1NonisoEEMinus->GetXaxis()->SetTitle("x index") ;
   
  TH2F * occupancyL1preIsoEEPlus = new TH2F("occupancyL1preIsoEEPlus", "Pre-firing L1Iso Occupancy: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
  occupancyL1preIsoEEPlus->GetYaxis()->SetTitle("y index") ;
  occupancyL1preIsoEEPlus->GetXaxis()->SetTitle("x index") ;
  TH2F * occupancyL1preIsoEEMinus = new TH2F("occupancyL1preIsoEEMinus", "Pre-firing L1Iso Occupancy: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
  occupancyL1preIsoEEMinus->GetYaxis()->SetTitle("y index") ;
  occupancyL1preIsoEEMinus->GetXaxis()->SetTitle("x index") ;
  TH2F * occupancyL1preNonisoEEPlus = new TH2F("occupancyL1preNonisoEEPlus", "Pre-firing L1Noniso Occupancy: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
  occupancyL1preNonisoEEPlus->GetYaxis()->SetTitle("y index") ;
  occupancyL1preNonisoEEPlus->GetXaxis()->SetTitle("x index") ;
  TH2F * occupancyL1preNonisoEEMinus = new TH2F("occupancyL1preNonisoEEMinus", "Pre-firing L1Noniso Occupancy: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
  occupancyL1preNonisoEEMinus->GetYaxis()->SetTitle("y index") ;
  occupancyL1preNonisoEEMinus->GetXaxis()->SetTitle("x index") ;
   
  TH2F * occupancyL1postIsoEEPlus = new TH2F("occupancyL1postIsoEEPlus", "Post-firing L1Iso Occupancy: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
  occupancyL1postIsoEEPlus->GetYaxis()->SetTitle("y index") ;
  occupancyL1postIsoEEPlus->GetXaxis()->SetTitle("x index") ;
  TH2F * occupancyL1postIsoEEMinus = new TH2F("occupancyL1postIsoEEMinus", "Post-firing L1Iso Occupancy: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
  occupancyL1postIsoEEMinus->GetYaxis()->SetTitle("y index") ;
  occupancyL1postIsoEEMinus->GetXaxis()->SetTitle("x index") ;
  TH2F * occupancyL1postNonisoEEPlus = new TH2F("occupancyL1postNonisoEEPlus", "Occupancy: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
  occupancyL1postNonisoEEPlus->GetYaxis()->SetTitle("y index") ;
  occupancyL1postNonisoEEPlus->GetXaxis()->SetTitle("x index") ;
  TH2F * occupancyL1postNonisoEEMinus = new TH2F("occupancyL1postNonisoEEMinus", "Post-firing L1Noniso Occupancy: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
  occupancyL1postNonisoEEMinus->GetYaxis()->SetTitle("y index") ;
  occupancyL1postNonisoEEMinus->GetXaxis()->SetTitle("x index") ;
   
  //masked RCT regions
  TH2F * maskedRCT = new TH2F("maskedRCT", "Masked RCT Regions", 14, 4, 18, 18, 0, 18) ;
  maskedRCT->GetXaxis()->SetTitle("RCT eta index") ;
  maskedRCT->GetYaxis()->SetTitle("RCT phi index") ;
   
  TH2F * maskedRCTEB = new TH2F("maskedRCTEB", "Masked RCT Regions: Barrel", 72, 1, 73, 38, -19, 19) ;
  maskedRCTEB->GetXaxis()->SetTitle("eta index") ;
  maskedRCTEB->GetYaxis()->SetTitle("phi index") ;
   
  TH2F * maskedRCTEEPlus = new TH2F("maskedRCTEEPlus", "Masked RCT Regions: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
  maskedRCTEEPlus->GetYaxis()->SetTitle("y index") ;
  maskedRCTEEPlus->GetXaxis()->SetTitle("x index") ;
   
  TH2F * maskedRCTEEMinus = new TH2F("maskedRCTEEMinus", "Masked RCT Regions: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
  maskedRCTEEMinus->GetYaxis()->SetTitle("y index") ;
  maskedRCTEEMinus->GetXaxis()->SetTitle("x index") ;
   
   
  //comparison with TPs 
  TH2F * L1MissingTPIso = new TH2F("L1MissingTPIso", "L1 Iso Mismatch: Missing TP", 14, 4, 18, 18, 0, 18) ;
  L1MissingTPIso->GetXaxis()->SetTitle("RCT eta index") ;
  L1MissingTPIso->GetYaxis()->SetTitle("RCT phi index") ;
   
  //   TH2F * L1FractionMissingTPIso = new TH2F("L1FractionMissingTPIso", "Fraction of L1 Iso Mismatch: Missing TP", 14, 4, 18, 18, 0, 18) ;
  //   L1FractionMissingTPIso->GetXaxis()->SetTitle("RCT eta index") ;
  //   L1FractionMissingTPIso->GetYaxis()->SetTitle("RCT phi index") ;
  //   TH2F * L1FractionMissingTPNoniso = new TH2F("L1FractionMissingTPNoniso", "Fraction of L1 Noniso Mismatch: Missing TP", 14, 4, 18, 18, 0, 18) ;
  //   L1FractionMissingTPNoniso->GetXaxis()->SetTitle("RCT eta index") ;
  //   L1FractionMissingTPNoniso->GetYaxis()->SetTitle("RCT phi index") ;
   
  TH2F * L1ValueMismatchIso = new TH2F("L1ValueMismatchIso", "L1 Iso Mismatch: Value Mismatch", 14, 4, 18, 18, 0, 18) ;
  L1ValueMismatchIso->GetXaxis()->SetTitle("RCT eta index") ;
  L1ValueMismatchIso->GetYaxis()->SetTitle("RCT phi index") ;
   
  TH1F * L1IsoRatio = new TH1F("L1IsoRatio", "iso ratio of sum of TPs to L1 rank", 1000, 0, 10.) ;

   
  TH1F * L1Iso2TPSum = new TH1F("L1Iso2TPSum", "sum of two highest adjacent TPs in GCT region of L1 Iso Cand", 505, 0, 505.) ;

   
   
  //barrel l1 geometric mismatch
  TH2F * L1MissingTPIsoEB = new TH2F("L1MissingTPIsoEB", "L1 Iso Mismatch: Missing TP: Barrel", 72, 1, 73, 38, -19, 19) ;
  L1MissingTPIsoEB->GetYaxis()->SetTitle("eta index") ;
  L1MissingTPIsoEB->GetXaxis()->SetTitle("phi index") ;

  TH2F * L1FractionMissingTPIsoEB = new TH2F("L1FractionMissingTPIsoEB", "Fraction of L1 Iso Mismatch: Missing TP: Barrel", 72, 1, 73, 38, -19, 19) ;
  L1FractionMissingTPIsoEB->GetYaxis()->SetTitle("eta index") ;
  L1FractionMissingTPIsoEB->GetXaxis()->SetTitle("phi index") ;

   
  //endcap l1 geometric mismatch
  TH2F * L1MissingTPIsoEEPlus = new TH2F("L1MissingTPIsoEEPlus", "L1 Iso Mismatch: Missing TP: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
  L1MissingTPIsoEEPlus->GetYaxis()->SetTitle("y index") ;
  L1MissingTPIsoEEPlus->GetXaxis()->SetTitle("x index") ;
  TH2F * L1MissingTPIsoEEMinus = new TH2F("L1MissingTPIsoEEMinus", "L1 Iso Mismatch: Missing TP: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
  L1MissingTPIsoEEMinus->GetYaxis()->SetTitle("y index") ;
  L1MissingTPIsoEEMinus->GetXaxis()->SetTitle("x index") ;
   
  TH2F * L1FractionMissingTPIsoEEPlus = new TH2F("L1FractionMissingTPIsoEEPlus", "Fraction of L1 Iso Mismatch: Missing TP: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
  L1FractionMissingTPIsoEEPlus->GetYaxis()->SetTitle("y index") ;
  L1FractionMissingTPIsoEEPlus->GetXaxis()->SetTitle("x index") ;
  TH2F * L1FractionMissingTPIsoEEMinus = new TH2F("L1FractionMissingTPIsoEEMinus", "Fraction of L1 Iso Mismatch: Missing TP: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
  L1FractionMissingTPIsoEEMinus->GetYaxis()->SetTitle("y index") ;
  L1FractionMissingTPIsoEEMinus->GetXaxis()->SetTitle("x index") ;
 
  TH2F * L1FractionValueMismatchIsoEEPlus = new TH2F("L1FractionValueMismatchIsoEEPlus", "Fraction of L1 Iso Mismatch: Value Mismatch: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
  L1FractionValueMismatchIsoEEPlus->GetYaxis()->SetTitle("y index") ;
  L1FractionValueMismatchIsoEEPlus->GetXaxis()->SetTitle("x index") ;
  TH2F * L1FractionValueMismatchIsoEEMinus = new TH2F("L1FractionValueMismatchIsoEEMinus", "Fraction of L1 Iso Mismatch: Value Mismatch: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
  L1FractionValueMismatchIsoEEMinus->GetYaxis()->SetTitle("y index") ;
  L1FractionValueMismatchIsoEEMinus->GetXaxis()->SetTitle("x index") ;
  TH2F * L1FractionValueMismatchIsoEB = new TH2F("L1FractionValueMismatchIsoEB", "Fraction of L1 Iso Mismatch: Value Mismatch: Barrel", 72, 1, 73, 38, -19, 19) ;
  L1FractionValueMismatchIsoEB->GetYaxis()->SetTitle("eta index") ;
  L1FractionValueMismatchIsoEB->GetXaxis()->SetTitle("phi index") ;
 


  
  //barrel L1 TP comparisons
  TH2F * L1TPCompIsoEB = new TH2F("L1TPCompIsoEB", "L1 Iso - TP comparisons: Barrel", 72, 1, 73, 38, -19, 19) ;
  L1TPCompIsoEB->GetYaxis()->SetTitle("eta index") ;
  L1TPCompIsoEB->GetXaxis()->SetTitle("phi index") ;
  //endcap L1 TP comparisons
  TH2F * L1TPCompIsoEEPlus = new TH2F("L1TPCompIsoEEPlus", "L1 Iso - TP comparisons: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
  L1TPCompIsoEEPlus->GetYaxis()->SetTitle("y index") ;
  L1TPCompIsoEEPlus->GetXaxis()->SetTitle("x index") ;
  TH2F * L1TPCompIsoEEMinus = new TH2F("L1TPCompIsoEEMinus", "L1 Iso - TP comparisons: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
  L1TPCompIsoEEMinus->GetYaxis()->SetTitle("y index") ;
  L1TPCompIsoEEMinus->GetXaxis()->SetTitle("x index") ;
  // L1/TP ratio (ISO)
  TH3F * L1RatioTPIso3DEB = new TH3F("L1RatioTPIso3DEB", "L1 Iso: ADC Ratio L1/TP: Barrel", 72, 1, 73, 38, -19, 19, 150, 0., 1.5) ;
  L1RatioTPIso3DEB->GetYaxis()->SetTitle("eta index") ;
  L1RatioTPIso3DEB->GetXaxis()->SetTitle("phi index") ;
   
  TH3F * L1RatioTPIso3DEEPlus = new TH3F("L1RatioTPIso3DEEPlus", "L1 Iso: ADC Ratio L1/TP: Plus Endcap", 121, -10, 111, 121, -10, 111, 150, 0., 1.5) ;
  L1RatioTPIso3DEEPlus->GetYaxis()->SetTitle("y index") ;
  L1RatioTPIso3DEEPlus->GetXaxis()->SetTitle("x index") ;
   
  TH3F * L1RatioTPIso3DEEMinus = new TH3F("L1RatioTPIso3DEEMinus", "L1 Iso: ADC Ratio L1/TP: Minus Endcap", 121, -10, 111, 121, -10, 111, 150, 0., 1.5) ;
  L1RatioTPIso3DEEMinus->GetYaxis()->SetTitle("y index") ;
  L1RatioTPIso3DEEMinus->GetXaxis()->SetTitle("x index") ;

  //barrel l1 value mismatch
  TH2F * L1ValueMismatchIsoEB = new TH2F("L1ValueMismatchIsoEB", "L1 Iso Mismatch: Value Mismatch: Barrel", 72, 1, 73, 38, -19, 19) ;
  L1ValueMismatchIsoEB->GetYaxis()->SetTitle("eta index") ;
  L1ValueMismatchIsoEB->GetXaxis()->SetTitle("phi index") ;
  //endcap l1 value mismatch
  TH2F * L1ValueMismatchIsoEEPlus = new TH2F("L1ValueMismatchIsoEEPlus", "L1 Iso Mismatch: Value Mismatch: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
  L1ValueMismatchIsoEEPlus->GetYaxis()->SetTitle("y index") ;
  L1ValueMismatchIsoEEPlus->GetXaxis()->SetTitle("x index") ;
  TH2F * L1ValueMismatchIsoEEMinus = new TH2F("L1ValueMismatchIsoEEMinus", "L1 Iso Mismatch: Value Mismatch: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
  L1ValueMismatchIsoEEMinus->GetYaxis()->SetTitle("y index") ;
  L1ValueMismatchIsoEEMinus->GetXaxis()->SetTitle("x index") ;
   
  //Pre firing ISO comaparison with reco TP

  
  //comparison with TPs 

  
  //barrel L1 TP comparisons
  TH2F * L1TPComppreIsoEB = new TH2F("L1TPComppreIsoEB", "L1 preIso - TP comparisons: Barrel", 72, 1, 73, 38, -19, 19) ;
  L1TPComppreIsoEB->GetYaxis()->SetTitle("eta index") ;
  L1TPComppreIsoEB->GetXaxis()->SetTitle("phi index") ;
  //endcap L1 TP comparisons
  TH2F * L1TPComppreIsoEEPlus = new TH2F("L1TPComppreIsoEEPlus", "L1 preIso - TP comparisons: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
  L1TPComppreIsoEEPlus->GetYaxis()->SetTitle("y index") ;
  L1TPComppreIsoEEPlus->GetXaxis()->SetTitle("x index") ;
  TH2F * L1TPComppreIsoEEMinus = new TH2F("L1TPComppreIsoEEMinus", "L1 preIso - TP comparisons: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
  L1TPComppreIsoEEMinus->GetYaxis()->SetTitle("y index") ;
  L1TPComppreIsoEEMinus->GetXaxis()->SetTitle("x index") ;
  // L1/TP ratio (ISO)
  TH3F * L1RatioTPpreIso3DEB = new TH3F("L1RatioTPpreIso3DEB", "L1 preIso: ADC Ratio L1/TP: Barrel", 72, 1, 73, 38, -19, 19, 150, 0., 1.5) ;
  L1RatioTPpreIso3DEB->GetYaxis()->SetTitle("eta index") ;
  L1RatioTPpreIso3DEB->GetXaxis()->SetTitle("phi index") ;
   
  TH3F * L1RatioTPpreIso3DEEPlus = new TH3F("L1RatioTPpreIso3DEEPlus", "L1 preIso: ADC Ratio L1/TP: Plus Endcap", 121, -10, 111, 121, -10, 111, 150, 0., 1.5) ;
  L1RatioTPpreIso3DEEPlus->GetYaxis()->SetTitle("y index") ;
  L1RatioTPpreIso3DEEPlus->GetXaxis()->SetTitle("x index") ;
   
  TH3F * L1RatioTPpreIso3DEEMinus = new TH3F("L1RatioTPpreIso3DEEMinus", "L1 preIso: ADC Ratio L1/TP: Minus Endcap", 121, -10, 111, 121, -10, 111, 150, 0., 1.5) ;
  L1RatioTPpreIso3DEEMinus->GetYaxis()->SetTitle("y index") ;
  L1RatioTPpreIso3DEEMinus->GetXaxis()->SetTitle("x index") ;

  //barrel l1 value mismatch
  TH2F * L1ValueMismatchpreIsoEB = new TH2F("L1ValueMismatchpreIsoEB", "L1 preIso Mismatch: Value Mismatch: Barrel", 72, 1, 73, 38, -19, 19) ;
  L1ValueMismatchpreIsoEB->GetYaxis()->SetTitle("eta index") ;
  L1ValueMismatchpreIsoEB->GetXaxis()->SetTitle("phi index") ;
  //endcap l1 value mismatch
  TH2F * L1ValueMismatchpreIsoEEPlus = new TH2F("L1ValueMismatchpreIsoEEPlus", "L1 preIso Mismatch: Value Mismatch: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
  L1ValueMismatchpreIsoEEPlus->GetYaxis()->SetTitle("y index") ;
  L1ValueMismatchpreIsoEEPlus->GetXaxis()->SetTitle("x index") ;
  TH2F * L1ValueMismatchpreIsoEEMinus = new TH2F("L1ValueMismatchpreIsoEEMinus", "L1 preIso Mismatch: Value Mismatch: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
  L1ValueMismatchpreIsoEEMinus->GetYaxis()->SetTitle("y index") ;
  L1ValueMismatchpreIsoEEMinus->GetXaxis()->SetTitle("x index") ;
   


  //NONISO
  TH2F * L1MissingTPNoniso = new TH2F("L1MissingTPNoniso", "L1 Noniso Mismatch: Missing TP", 14, 4, 18, 18, 0, 18) ;
  L1MissingTPNoniso->GetXaxis()->SetTitle("RCT eta index") ;
  L1MissingTPNoniso->GetYaxis()->SetTitle("RCT phi index") ;
  TH2F * L1ValueMismatchNoniso = new TH2F("L1ValueMismatchNoniso", "L1 Noniso Mismatch: Value Mismatch", 14, 4, 18, 18, 0, 18) ;
  L1ValueMismatchNoniso->GetXaxis()->SetTitle("RCT eta index") ;
  L1ValueMismatchNoniso->GetYaxis()->SetTitle("RCT phi index") ;

  TH1F * L1Noniso2TPSum = new TH1F("L1Noniso2TPSum", "sum of two highest adjacent TPs in GCT region of L1 Iso Cand", 505, 0, 505.) ;
  TH1F * L1NonisoRatio = new TH1F("L1NonisoRatio", "noniso ratio of sum of TPs to L1 rank", 1000, 0, 10.) ;

  TH2F * L1MissingTPNonisoEB = new TH2F("L1MissingTPNonisoEB", "L1 Noniso Mismatch: Missing TP: Barrel", 72, 1, 73, 38, -19, 19) ;
  L1MissingTPNonisoEB->GetYaxis()->SetTitle("eta index") ;
  L1MissingTPNonisoEB->GetXaxis()->SetTitle("phi index") ;

  TH2F * L1FractionMissingTPNonisoEB = new TH2F("L1FractionMissingTPNonisoEB", "Fraction of L1 Noniso Mismatch: Missing TP: Barrel", 72, 1, 73, 38, -19, 19) ;
  L1FractionMissingTPNonisoEB->GetYaxis()->SetTitle("eta index") ;
  L1FractionMissingTPNonisoEB->GetXaxis()->SetTitle("phi index") ;



  TH2F * L1MissingTPNonisoEEPlus = new TH2F("L1MissingTPNonisoEEPlus", "L1 Noniso Mismatch: Missing TP: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
  L1MissingTPNonisoEEPlus->GetYaxis()->SetTitle("y index") ;
  L1MissingTPNonisoEEPlus->GetXaxis()->SetTitle("x index") ;
  TH2F * L1MissingTPNonisoEEMinus = new TH2F("L1MissingTPNonisoEEMinus", "L1 Noniso Mismatch: Missing TP: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
  L1MissingTPNonisoEEMinus->GetYaxis()->SetTitle("y index") ;
  L1MissingTPNonisoEEMinus->GetXaxis()->SetTitle("x index") ;

  TH2F * L1FractionMissingTPNonisoEEPlus = new TH2F("L1FractionMissingTPNonisoEEPlus", "Fraction of L1 Noniso Mismatch: Missing TP: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
  L1FractionMissingTPNonisoEEPlus->GetYaxis()->SetTitle("y index") ;
  L1FractionMissingTPNonisoEEPlus->GetXaxis()->SetTitle("x index") ;
  TH2F * L1FractionMissingTPNonisoEEMinus = new TH2F("L1FractionMissingTPNonisoEEMinus", "Fraction of L1 Noniso Mismatch: Missing TP: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
  L1FractionMissingTPNonisoEEMinus->GetYaxis()->SetTitle("y index") ;
  L1FractionMissingTPNonisoEEMinus->GetXaxis()->SetTitle("x index") ;

 //barrel L1 TP comparisons
  TH2F * L1TPCompNonisoEB = new TH2F("L1TPCompNonisoEB", "L1 Non Iso - TP comparisons: Barrel", 72, 1, 73, 38, -19, 19) ;
  L1TPCompNonisoEB->GetYaxis()->SetTitle("eta index") ;
  L1TPCompNonisoEB->GetXaxis()->SetTitle("phi index") ;

   
  //endcap L1 TP comparisons
  TH2F * L1TPCompNonisoEEPlus = new TH2F("L1TPCompNonisoEEPlus", "L1 Non Iso - TP comparisons: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
  L1TPCompNonisoEEPlus->GetYaxis()->SetTitle("y index") ;
  L1TPCompNonisoEEPlus->GetXaxis()->SetTitle("x index") ;
  TH2F * L1TPCompNonisoEEMinus = new TH2F("L1TPCompNonisoEEMinus", "L1 Non Iso - TP comparisons: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
  L1TPCompNonisoEEMinus->GetYaxis()->SetTitle("y index") ;
  L1TPCompNonisoEEMinus->GetXaxis()->SetTitle("x index") ;
   
  // L1/TP ratio (NON ISO)
  TH3F * L1RatioTPNoniso3DEB = new TH3F("L1RatioTPNoniso3DEB", "L1 Non Iso: ADC Ratio L1/TP: Barrel", 72, 1, 73, 38, -19, 19, 400, 0., 4.) ;
  L1RatioTPNoniso3DEB->GetYaxis()->SetTitle("eta index") ;
  L1RatioTPNoniso3DEB->GetXaxis()->SetTitle("phi index") ;
   
  TH3F * L1RatioTPNoniso3DEEPlus = new TH3F("L1RatioTPNoniso3DEEPlus", "L1 Non Iso: ADC Ratio L1/TP: Plus Endcap", 121, -10, 111, 121, -10, 111, 400, 0., 4.) ;
  L1RatioTPNoniso3DEEPlus->GetYaxis()->SetTitle("y index") ;
  L1RatioTPNoniso3DEEPlus->GetXaxis()->SetTitle("x index") ;
   
  TH3F * L1RatioTPNoniso3DEEMinus = new TH3F("L1RatioTPNoniso3DEEMinus", "L1 Non Iso: ADC Ratio L1/TP: Minus Endcap", 121, -10, 111, 121, -10, 111, 400, 0., 4.) ;
  L1RatioTPNoniso3DEEMinus->GetYaxis()->SetTitle("y index") ;
  L1RatioTPNoniso3DEEMinus->GetXaxis()->SetTitle("x index") ;
   

  //barrel l1 value mismatch
  TH2F * L1ValueMismatchNonisoEB = new TH2F("L1ValueMismatchNonisoEB", "L1 Noniso Mismatch: Value Mismatch: Barrel", 72, 1, 73, 38, -19, 19) ;
  L1ValueMismatchNonisoEB->GetYaxis()->SetTitle("eta index") ;
  L1ValueMismatchNonisoEB->GetXaxis()->SetTitle("phi index") ;
   
  //endcap l1 value mismatch
  TH2F * L1ValueMismatchNonisoEEPlus = new TH2F("L1ValueMismatchNonisoEEPlus", "L1 Noniso Mismatch: Value Mismatch: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
  L1ValueMismatchNonisoEEPlus->GetYaxis()->SetTitle("y index") ;
  L1ValueMismatchNonisoEEPlus->GetXaxis()->SetTitle("x index") ;
  TH2F * L1ValueMismatchNonisoEEMinus = new TH2F("L1ValueMismatchNonisoEEMinus", "L1 Noniso Mismatch: Value Mismatch: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
  L1ValueMismatchNonisoEEMinus->GetYaxis()->SetTitle("y index") ;
  L1ValueMismatchNonisoEEMinus->GetXaxis()->SetTitle("x index") ;
   
   
  //histos to hold the masked towers
  TH2F * MaskedTowersEB = new TH2F("MaskedTowersEB", "MaskedTowersEB", 72, 1, 73, 38, -19, 19) ;
  TH2F * MaskedTowersEEPlus = new TH2F("MaskedTowersEEPlus", "MaskedTowersEEPlus", 121, -10, 111, 121, -10, 111) ;
  TH2F * MaskedTowersEEMinus = new TH2F("MaskedTowersEEMinus", "MaskedTowersEEMinus", 121, -10, 111, 121, -10, 111) ;
   
  //histos to hold the masked towers
  TH2F * MaskedReadOutEB = new TH2F("MaskedReadOutEB", "MaskedReadOutEB", 72, 1, 73, 38, -19, 19) ;
  TH2F * MaskedReadOutEEPlus = new TH2F("MaskedReadOutEEPlus", "MaskedReadOutEEPlus", 121, -10, 111, 121, -10, 111) ;
  TH2F * MaskedReadOutEEMinus = new TH2F("MaskedReadOutEEMinus", "MaskedReadOutEEMinus", 121, -10, 111, 121, -10, 111) ;
   
   
  ///////////////////////
  // Chain the trees:
  ///////////////////////
  TChain * chainAux = new TChain ("treeAux") ;
  TChain * chain = new TChain ("EcalTPGAnalysis") ;
  std::vector<std::string> files ;
  if (inputfiles.find(std::string(":")) != std::string::npos) {
    std::vector<std::string> filesbase = split(inputfiles,":") ;
    if (filesbase.size() == 4) {
      int first = atoi(filesbase[1].c_str()) ;
      int last = atoi(filesbase[2].c_str()) ;
      for (int i=first ; i<=last ; i++) {
	std::stringstream name ;
	name<<filesbase[0]<<i<<filesbase[3] ;
	files.push_back(name.str()) ;
      }
    }
  }
  else files = split(inputfiles,",") ;
   
  for (uint i=0 ; i<uint(files.size()) ; i++) {
    files[i] = inputdir+files[i] ;
    std::cout<<"\nInput file: "<<files[i]<<std::endl ;
    chain->Add (files[i].c_str()) ;
    chainAux->Add (files[i].c_str()) ;
  }
   
  EcalTPGVariables treeVars ;
  setBranchAddresses (chain, treeVars) ;
   
   
   
  EcalAux auxVars ;
  setAuxBranchAddresses (chainAux, auxVars) ;
   
   
  chainAux->GetEntry (0) ;
   
  std::cout << "\nMasked Towers:  " << std::endl;
  for (int nMaskCh = 0; nMaskCh < auxVars.nMaskedCh; nMaskCh++)
    {
      int ieta= auxVars.iMaskedTTeta[nMaskCh];  
      int iphi= auxVars.iMaskedTTphi[nMaskCh];
      int hashedIndex =0 ;
      if (ieta >0)
	hashedIndex = ieta * 100 + iphi ;
      else 
	hashedIndex = ieta * 100 - iphi ; 
      
      if (abs(ieta)<18) {
	MaskedTowersEB->Fill(iphi, ieta) ;
	std::cout << "   EB:  ieta=" << ieta << " iphi=" << iphi << std::endl;
      }
      else if(ieta<=-18){
	for (uint i=0; i !=geometry[hashedIndex].size();++i)
	  {
            MaskedTowersEEMinus->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second) ;
            std::cout << "   EE-:  ix=" << geometry[hashedIndex][i].first << " iy=" << geometry[hashedIndex][i].second << std::endl;
	  }
      }
      else if(ieta>=18){
	for (uint i=0; i !=geometry[hashedIndex].size();++i)
	  {
            MaskedTowersEEPlus->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second) ;
            std::cout << "   EE+:  ix=" << geometry[hashedIndex][i].first << " iy=" << geometry[hashedIndex][i].second << std::endl;
	  }
      }
    }
   
  std::cout << "\nMasked Strips in Endcaps:  " << std::endl;
  for (int nMaskChInStrip = 0; nMaskChInStrip < auxVars.nMaskedChannelsFromStrips; nMaskChInStrip++)
    {
      if ( auxVars.iMaskedChannelsFromStripsZ[nMaskChInStrip] > 0 ){
         
	MaskedTowersEEPlus->Fill(auxVars.iMaskedChannelsFromStripsX[nMaskChInStrip],auxVars.iMaskedChannelsFromStripsY[nMaskChInStrip]);
	std::cout << "   EE+: iStripsX=" << auxVars.iMaskedChannelsFromStripsX[nMaskChInStrip]
		  << "  iStripsY" << auxVars.iMaskedChannelsFromStripsY[nMaskChInStrip] << std::endl;
      }
      if ( auxVars.iMaskedChannelsFromStripsZ[nMaskChInStrip] < 0 ) {
	MaskedTowersEEMinus->Fill(auxVars.iMaskedChannelsFromStripsX[nMaskChInStrip],auxVars.iMaskedChannelsFromStripsY[nMaskChInStrip]);
	std::cout << "   EE-: iStripsX=" << auxVars.iMaskedChannelsFromStripsX[nMaskChInStrip]
		  << "  iStripsY=" << auxVars.iMaskedChannelsFromStripsY[nMaskChInStrip] << std::endl;
      }
      
    }
   
  if(lastEntry<0 || lastEntry>chain->GetEntries()) lastEntry = chain->GetEntries() ;
   
  std::cout << "\n\nNumber of entries in rootuple: " << chain->GetEntries() <<std::endl;
  std::cout << "Entries to be processed: [" << firstEntry << "-" << lastEntry << "]\n\n";
   
  ULong64_t maxEvNb=0;
  
   
   
  ///////////////////////
  // Main loop over entries
  ///////////////////////
   
  int iRCT=0;
  for (int entry = firstEntry ; entry < lastEntry ; ++entry)
    {
      //      cout<<"fsdfsd"<<treeVars.nbOfActiveTriggers<<endl;      

      chain->GetEntry (entry) ;
      if (entry%100000==0) std::cout <<"------> Entry "<< entry <<" is being processed" << " <------\n" ; 
      bool keepEvent = false ;
      
      ULong64_t evNb = treeVars.evtNb;
      if(evNb>maxEvNb) {
	maxEvNb=evNb;
      }
      

      //applying event selection
      if(eventIncludeVector.size()==0) keepEvent = true;
      for(uint i=0; i!=eventIncludeVector.size();++i){
	if(eventIncludeVector[i].size()==1 && evNb==eventIncludeVector[i][0]) keepEvent=true;
	else if(eventIncludeVector[i].size()==2 && (evNb>=eventIncludeVector[i][0] && evNb<=eventIncludeVector[i][1]) ) {
	  keepEvent=true;
	  //std::cout<<"include event vector"<<std::endl;
	}
	if(eventIncludeVector[i].size()==2 && eventIncludeVector[i][1]<eventIncludeVector[i][0] && evNb>=eventIncludeVector[i][0]) keepEvent=true;
      }
      if(!keepEvent) continue;
      
      keepEvent = true;
      for(uint i=0; i!=eventExcludeVector.size();++i){
	//std::cout<<"exclude event vector"<<std::endl;
	if(eventExcludeVector[i].size()==1 && evNb==eventExcludeVector[i][0]) keepEvent=false;
	else if(eventExcludeVector[i].size()==2 && (evNb>=eventExcludeVector[i][0] && evNb<=eventExcludeVector[i][1])) keepEvent=false;
      }
      if(!keepEvent) continue;
      
      if (!keepEvent) continue;
      
      //applying 'GOODCOLL' selection if required
      bool keepGC = false;
      bool tech0 = false;
      bool tech40or41 = false;
      bool tech36or37or38or39 = false;
      bool tech42 = false;
      bool tech43 = false;
      for (uint ntrig = 0 ; ntrig < treeVars.nbOfActiveTechTriggers ; ntrig++)
	{
	  if(treeVars.activeTechTriggers[ntrig]==0) tech0 = true;
	  if(treeVars.activeTechTriggers[ntrig]==40 || treeVars.activeTechTriggers[ntrig]==41) tech40or41 = true;
	  if(treeVars.activeTechTriggers[ntrig]==36 || treeVars.activeTechTriggers[ntrig]==37 || treeVars.activeTechTriggers[ntrig]==38 || treeVars.activeTechTriggers[ntrig]==39) tech36or37or38or39 = true;
	  if(treeVars.activeTechTriggers[ntrig]==42) tech42 = true;
	  if(treeVars.activeTechTriggers[ntrig]==43) tech43 = true;
	}
      bool tech42xor43 = false;
      if(tech42 && !tech43) tech42xor43 = true;
      if(tech43 && !tech42) tech42xor43 = true;
      if(GoodColl!=1 || (tech0 && tech40or41 && !(tech36or37or38or39) && !(tech42xor43))) keepGC = true;
      
      if (!keepGC) continue;
      
      //applying "techTrgs" option
      bool keep = false;
      if(techTrgIncludeVector.size()==0) keep = true;  
      for(uint i=0; i!=techTrgIncludeVector.size();++i){
	for (uint ntrig = 0 ; ntrig < treeVars.nbOfActiveTechTriggers ; ntrig++)
	  {
            if(techTrgIncludeVector[i].size()==1 && treeVars.activeTechTriggers[ntrig]==techTrgIncludeVector[i][0])
	      {
		keep=true;
		//  std::cout << "event taken trg " <<   treeVars.activeTechTriggers[ntrig] << std::endl;
	      }
            else if(techTrgIncludeVector[i].size()==2 && (treeVars.activeTechTriggers[ntrig]>=techTrgIncludeVector[i][0] && treeVars.activeTechTriggers[ntrig]<=techTrgIncludeVector[i][1]))
	      {
		keep=true;
		// std::cout << "event taken trg " <<   treeVars.activeTechTriggers[ntrig] << std::endl;
	      }
	  }
      }
      if(!keep) continue;
      
      keep = true;
      for(uint i=0; i!=techTrgExcludeVector.size();++i){
	for (uint ntrig = 0 ; ntrig < treeVars.nbOfActiveTechTriggers ; ntrig++)
	  {
            if(techTrgExcludeVector[i].size()==1 && treeVars.activeTechTriggers[ntrig]==techTrgExcludeVector[i][0])
	      {
		keep=false;
		//  std::cout << "event skipped trg " <<   treeVars.activeTechTriggers[ntrig] << std::endl;
	      }
            else if(techTrgExcludeVector[i].size()==2 && (treeVars.activeTechTriggers[ntrig]>=techTrgExcludeVector[i][0] && treeVars.activeTechTriggers[ntrig]<=techTrgExcludeVector[i][1]))
	      {
		keep=false;
		//  std::cout << "event skipped trg " <<   treeVars.activeTechTriggers[ntrig] << std::endl;
	      }
	  }
      }
      if(!keep) continue;
      

      // std::cout<<"koto gula aase  "<<treeVars.nbOfActiveTriggers<<std::endl;
      for(uint i=0;i!=treeVars.nbOfActiveTriggers;++i){
	//if (treeVars.activeTriggers[i]!=0) std::cout << treeVars.activeTriggers[i] << "\n";
	//	std::cout<<"trigger bit  "<<treeVars.activeTriggers[i]<<std::endl;
	if (treeVars.activeTriggers[i]!=0) {
	  triggerBit->Fill(treeVars.activeTriggers[i]) ;
	  // std::cout<<"keee re bhaaii"<<std::endl;
	}
      }
      for(uint i=0;i!=128;++i){
	int fireBX = int(treeVars.activeTriggersBX[i]/100);
	if(fireBX==1 || fireBX == 11 || fireBX == 111 || fireBX == 101)
	  {//only look at on-time trigger
	    FiredTriggers->Fill(i);
	  }
      }
      
      int bxNb=treeVars.bxNb;
      
      //applying "bcs" option
      keep = false;
      if(bcIncludeVector.size()==0) keep = true;  
      for(uint i=0; i!=bcIncludeVector.size();++i){
	if(bcIncludeVector[i].size()==1 && bxNb==bcIncludeVector[i][0]) keep=true;
	else if(bcIncludeVector[i].size()==2 && (bxNb>=bcIncludeVector[i][0] && bxNb<=bcIncludeVector[i][1])) keep=true;
      }
      if(!keep) continue;
      
      keep = true;
      for(uint i=0; i!=bcExcludeVector.size();++i){
	if(bcExcludeVector[i].size()==1 && bxNb==bcExcludeVector[i][0]) keep=false;
	else if(bcExcludeVector[i].size()==2 && (bxNb>=bcExcludeVector[i][0] && bxNb<=bcExcludeVector[i][1])) keep=false;
      }
      if(!keep) continue;
      
      
      //std::cout<<"event kept BX"<<std::endl;
      
      ULong64_t orbitNb = treeVars.orbitNb;
      
      //applying "orbits" option
      keep = false;
      if(orbitIncludeVector.size()==0) keep = true;
      for(uint i=0; i!=orbitIncludeVector.size();++i){
	if(orbitIncludeVector[i].size()==1 && (orbitNb)/1000000.==orbitIncludeVector[i][0]) keep=true;
	else if(orbitIncludeVector[i].size()==2 && ((orbitNb)/1000000.>=orbitIncludeVector[i][0] && (orbitNb)/1000000.<=orbitIncludeVector[i][1])) keep=true;
      }
      if(!keep) continue;
      
      keep = true;
      for(uint i=0; i!=orbitExcludeVector.size();++i){
	if(orbitExcludeVector[i].size()==1 && (orbitNb)/1000000.==orbitExcludeVector[i][0]) keep=false;
	else if(orbitExcludeVector[i].size()==2 && ((orbitNb)/1000000.>=orbitExcludeVector[i][0] && (orbitNb)/1000000.<=orbitExcludeVector[i][1])) keep=false;
      }
      if(!keep) continue;
      
      
      int lumiNb = treeVars.lumiBlock;
      
      //applying "lumi" option
      keep = false;
      if(lumiIncludeVector.size()==0) keep = true;
      for(uint i=0; i!=lumiIncludeVector.size();++i){
	if(lumiIncludeVector[i].size()==1 && lumiNb==lumiIncludeVector[i][0]) keep=true;
	else if(lumiIncludeVector[i].size()==2 && (lumiNb>=lumiIncludeVector[i][0] && lumiNb<=lumiIncludeVector[i][1])) keep=true;
      }
      if(!keep) continue;
      
      keep = true;
      for(uint i=0; i!=lumiExcludeVector.size();++i){
	if(lumiExcludeVector[i].size()==1 && lumiNb==lumiExcludeVector[i][0]) keep=false;
	else if(lumiExcludeVector[i].size()==2 && (lumiNb>=lumiExcludeVector[i][0] && lumiNb<=lumiExcludeVector[i][1])) keep=false;
      }
      if(!keep) continue;
      
      
      //std::cout<<"event kept lumi"<<std::endl;
      
      double timeStamp = treeVars.timeStamp-slMinTime;
      
      //applying "timestamps" option
      keep = false;
      if(timestampIncludeVector.size()==0) keep = true;
      for(uint i=0; i!=timestampIncludeVector.size();++i){
	if(timestampIncludeVector[i].size()==1 && timeStamp==timestampIncludeVector[i][0]) keep=true;
	else if(timestampIncludeVector[i].size()==2 && (timeStamp>=timestampIncludeVector[i][0] && timeStamp<=timestampIncludeVector[i][1])) keep=true;
      }
      if(!keep) continue;
      
      keep = true;
      for(uint i=0; i!=timestampExcludeVector.size();++i){
	if(timestampExcludeVector[i].size()==1 && timeStamp==timestampExcludeVector[i][0]) keep=false;
	else if(timestampExcludeVector[i].size()==2 && (timeStamp>=timestampExcludeVector[i][0] && timeStamp<=timestampExcludeVector[i][1])) keep=false;
      }
      if(!keep) continue;
      
      
      // trigger selection if any
      /*      keep=false ;
      if (!algobits.size()) keep = false ; // keep all events when no trigger selection
      for (uint algo = 0 ; algo<algobits.size() ; algo++)
	for (uint ntrig = 0 ; ntrig < treeVars.nbOfActiveTriggers ; ntrig++)
	  if (algobits[algo] == treeVars.activeTriggers[ntrig]) 
	    {
	      keep = true ;
	        cout<<"algobit: "<<algobits[algo]<<endl;
	      cout<<"treevars: "<<treeVars.activeTriggers[ntrig]<<endl;
	      cout<<endl;
	
	    } 
      
      
      if (keep) continue ;*/
      keep=false ;
      if (!algobits.size()) keep = true ; // keep all events when no trigger selection
      for (uint algo = 0 ; algo<algobits.size() ; algo++)
         for (uint ntrig = 0 ; ntrig < treeVars.nbOfActiveTriggers ; ntrig++)
            if (algobits[algo] == treeVars.activeTriggers[ntrig]) keep = true ;
      if (!keep) continue ;
      

      
      int * ibitGT45;
      ibitGT45 = unhashTr(treeVars.activeTriggersBX[45]);    
      
      int * ibitGT46;
      ibitGT46 = unhashTr(treeVars.activeTriggersBX[46]);
      
      for (int kshift = 0;kshift<5;kshift++)
	{
	  if (ibitGT45[kshift]==1) bx_bit45_all->Fill(treeVars.bxNb+kshift-2);
	  if (ibitGT46[kshift]==1) bx_bit46_all->Fill(treeVars.bxNb+kshift-2);
	}
      if (ibitGT45[2]==1) bx_nTT->Fill(treeVars.nbOfTowers);
      
      delete [] ibitGT46;
      delete [] ibitGT45;
      
      
      //int egbits = {40,41,42,43,44,45,46,47,48,49,50,51,52}
      TH2F l1EGAlgos2Dtest("L1EGAlgos2Dtest","L1EGAlgos2Dtest", 30, 39.5 , 69.5, 30, 39.5 , 69.5);
      
      
      for (int ibit = 40; ibit<=52;ibit++)
	{
	  int * ibitGT;
	  ibitGT = unhashTr(treeVars.activeTriggersBX[ibit]);
	  if (ibitGT[2]==1) l1EGAlgos->Fill(ibit);
	  for (uint ntrig = 0 ; ntrig < treeVars.nbOfActiveTechTriggers ; ntrig++)
	    {
	      if (ibitGT[2]==1) histoEgTrigTechTrigCor->Fill(ibit,treeVars.activeTechTriggers[ntrig]);
	    }
         
         
         
	  for (int ibit2 = 40; ibit2<=52;ibit2++)
	    {
	      int * ibitGT2;   
	      ibitGT2 = unhashTr(treeVars.activeTriggersBX[ibit2]);
            
            
	      if (ibitGT[2]==1 && ibitGT2[2]==1)
		//       && l1EGAlgos2Dtest.GetBinContent(ibit-39,ibit2-39)>-100)
		{ 
		  l1EGAlgos2D->Fill(ibit,ibit2);
		  l1EGAlgos2Dtest.Fill(ibit,ibit2);
               
		}
	      delete [] ibitGT2;
	    }
	  delete [] ibitGT;
	}
      
      // Tech Triggers correlation plots
      
      for (uint ntrig = 0 ; ntrig < treeVars.nbOfActiveTechTriggers ; ntrig++)
	{
	  techTrigCor->Fill(treeVars.activeTechTriggers[ntrig]);
	  for (uint ntrig2 = 0 ; ntrig2 < treeVars.nbOfActiveTechTriggers ; ntrig2++)
	    {
	      techTrigCor2D->Fill(treeVars.activeTechTriggers[ntrig],treeVars.activeTechTriggers[ntrig2] );
	    }
	}
      
      // end Tech Triggers correlation plots
      
      
      
      // fill RCT masks
      
      if(iRCT==0) {
	for (uint iMaskRCT = 0 ; iMaskRCT < treeVars.nMaskedRCT ; iMaskRCT++) {
	  int tteta = 0;
	  if (treeVars.iMaskedRCTcrate[iMaskRCT]>8) tteta = treeVars.iMaskedRCTeta[iMaskRCT]+1;
	  else tteta = - treeVars.iMaskedRCTeta[iMaskRCT]-1;
	  int rcteta = getGCTRegionEta(tteta);
	  int rctphi = getGCTRegionPhi2(treeVars.iMaskedRCTcrate[iMaskRCT],treeVars.iMaskedRCTphi[iMaskRCT]);
	  std::vector<int>  ttphi =  getECALRegionPhi(rctphi);
	  maskedRCT->Fill(rcteta,rctphi);
	  for(uint j=0;j!=ttphi.size();++j)
            {   
	      int l1hash=0;
	      if (tteta>0) l1hash= tteta * 100 + ttphi[j] ;
	      else l1hash = tteta * 100 - ttphi[j] ;   
	      if(abs(tteta)<18)
		{ //EB
		  maskedRCTEB->Fill(ttphi[j],tteta);
		}
	      if (tteta>=18)
		{ //EE+
		  for (uint k=0; k !=geometry[l1hash].size();++k){
		    maskedRCTEEPlus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second ) ;
		  }
		}
	      if(tteta<=-18)
		{ //EE-
		  for (uint k=0; k !=geometry[l1hash].size();++k){
		    maskedRCTEEMinus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second ) ;
		  }
		}
            }
	}
	iRCT=1;
      }
      
      
      //std::cout<<"event kept RCT"<<std::endl;
      
      //fill some L1 histograms
      
      
      nbOfL1IsoCands->Fill(treeVars.nbOfL1IsoCands);
      for (uint l1isocand = 0 ; l1isocand < treeVars.nbOfL1IsoCands ; l1isocand++)
	{
	  //if(treeVars.L1IsoRank[l1isocand]>=2*eg) {//require EG2 by default, EG eg in general
	  if(treeVars.L1IsoRank[l1isocand]>=eg)
	    { //require EG2 by default, EG eg in general
	      
	      //prefcheck
	      ptisoontime->Fill(treeVars.L1IsoRank[l1isocand]);
	      
	      occupancyL1Iso->Fill(treeVars.L1IsoIeta[l1isocand],treeVars.L1IsoIphi[l1isocand]);
	      L1IsoCandRank->Fill(treeVars.L1IsoRank[l1isocand]);
	      L1Isotiming->Fill(0);
	      std::vector<int> tteta = getECALRegionEta(treeVars.L1IsoIeta[l1isocand]);
	      std::vector<int> ttphi = getECALRegionPhi(treeVars.L1IsoIphi[l1isocand]);
	      if(abs(tteta[0])<17){//EB
		L1IsotimingEB->Fill(0);
	      }
	      if(tteta[0]>=17){//EE+
		L1IsotimingEEPlus->Fill(0); 
	      }
	      if(tteta[0]<=-17){//EE-
		L1IsotimingEEMinus->Fill(0);   
	      }
         
	      for(uint i=0;i!=tteta.size();++i){
		for(uint j=0;j!=ttphi.size();++j){   
		  int l1hash=0;
		  if (tteta[i]>0)
		    l1hash= tteta[i] * 100 + ttphi[j] ;
		  else 
		    l1hash = tteta[i] * 100 - ttphi[j] ;
               
               
		  if(abs(tteta[i])<18){//EB
		    occupancyL1IsoEB->Fill(ttphi[j],tteta[i]);
		  }
		  if(tteta[i]>=18){//EE+
		    for (uint k=0; k !=geometry[l1hash].size();++k){
		      occupancyL1IsoEEPlus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second ) ;
		    }
		  }
		  if(tteta[i]<=-18){//EE-
		    for (uint k=0; k !=geometry[l1hash].size();++k){
		      occupancyL1IsoEEMinus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second ) ;
		    }
		  }
		}
	      }
	    }
	}
      
      
      nbOfL1NonisoCands->Fill(treeVars.nbOfL1NonisoCands);
      for (uint l1nonisocand = 0 ; l1nonisocand < treeVars.nbOfL1NonisoCands ; l1nonisocand++)
	{
	  if(treeVars.L1NonisoRank[l1nonisocand]>=eg)
	    { //require EG2 by default, EG eg in general

	      //prefcheck
	      ptnonisoontime->Fill(treeVars.L1NonisoRank[l1nonisocand]);
	      
	      occupancyL1Noniso->Fill(treeVars.L1NonisoIeta[l1nonisocand],treeVars.L1NonisoIphi[l1nonisocand]);
	      L1NonisoCandRank->Fill(treeVars.L1NonisoRank[l1nonisocand]);
	      L1Nonisotiming->Fill(0);
	      std::vector<int> tteta = getECALRegionEta(treeVars.L1NonisoIeta[l1nonisocand]);
	      std::vector<int> ttphi = getECALRegionPhi(treeVars.L1NonisoIphi[l1nonisocand]);
	      if(abs(tteta[0])<17){//EB
		L1NonisotimingEB->Fill(0);
	      }
	      if(tteta[0]>=17){//EE+
		L1NonisotimingEEPlus->Fill(0); 
	      }
	      if(tteta[0]<=-17){//EE-
		L1NonisotimingEEMinus->Fill(0);   
	      }
         
	      for(uint i=0;i!=tteta.size();++i){
		for(uint j=0;j!=ttphi.size();++j){   
		  int l1hash=0;
		  if (tteta[i]>0)
		    l1hash= tteta[i] * 100 + ttphi[j] ;
		  else 
		    l1hash = tteta[i] * 100 - ttphi[j] ;
               
		  if(abs(tteta[i])<18){//EB
		    occupancyL1NonisoEB->Fill(ttphi[j],tteta[i]);
		  }
		  if(tteta[i]>=18){//EE+
		    for (uint k=0; k !=geometry[l1hash].size();++k){
		      occupancyL1NonisoEEPlus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second ) ;
		    }
		  }
		  if(tteta[i]<=-18){//EE-
		    for (uint k=0; k !=geometry[l1hash].size();++k){
		      occupancyL1NonisoEEMinus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second ) ;
		    }
		  }
		}
	      }
	    }
	}
      
      
      //fill some pre-firing L1 histograms
  
      nbOfL1preIsoCands->Fill(treeVars.nbOfL1preIsoCands);
      for (uint l1preisocand = 0 ; l1preisocand < treeVars.nbOfL1preIsoCands ; l1preisocand++)
	{
	  if(treeVars.L1preIsoRank[l1preisocand]>=0)
	    {
	      
	      //cout<<"a pre firing L1"<<treeVars.L1preIsoRank[l1preisocand]<<endl;



	      if(treeVars.L1preIsoRank[l1preisocand]>=eg)
		{ //require EG2 by default, EG eg in general
		  //prefcheck
		  ptisoprefiring->Fill(treeVars.L1preIsoRank[l1preisocand]);

		  occupancyL1preIso->Fill(treeVars.L1preIsoIeta[l1preisocand],treeVars.L1preIsoIphi[l1preisocand]);
		  L1preIsoCandRank->Fill(treeVars.L1preIsoRank[l1preisocand]);
		  L1Isotiming->Fill(-1);
		  std::vector<int> tteta = getECALRegionEta(treeVars.L1preIsoIeta[l1preisocand]);
		  std::vector<int> ttphi = getECALRegionPhi(treeVars.L1preIsoIphi[l1preisocand]);
            
		  if(abs(tteta[0])<17){//EB
		    L1IsotimingEB->Fill(-1);
		  }
		  if(tteta[0]>=17){//EE+
		    L1IsotimingEEPlus->Fill(-1); 
		  }
		

		  if(tteta[0]<=-17){//EE-
		    L1IsotimingEEMinus->Fill(-1);   
		  }
            
		  for(uint i=0;i!=tteta.size();++i){
		    for(uint j=0;j!=ttphi.size();++j){ 
		      int l1prehash=0;
		      if (tteta[i]>0)
			l1prehash= tteta[i] * 100 + ttphi[j] ;
		      else 
			l1prehash = tteta[i] * 100 - ttphi[j] ;
                  
                  
		      if(abs(tteta[i])<18){//EB
                        occupancyL1preIsoEB->Fill(ttphi[j],tteta[i]);
		      }
		      if(tteta[i]>=18){//EE+
                        for (uint k=0; k !=geometry[l1prehash].size();++k){
			  occupancyL1preIsoEEPlus->Fill(geometry[l1prehash][k].first,geometry[l1prehash][k].second ) ;
                        }
		      }
		      if(tteta[i]<=-18){//EE-
                        for (uint k=0; k !=geometry[l1prehash].size();++k){
			  occupancyL1preIsoEEMinus->Fill(geometry[l1prehash][k].first,geometry[l1prehash][k].second ) ;
                        }
		      }
		    }
		  }
		}
	    }
	}
      
      nbOfL1preNonisoCands->Fill(treeVars.nbOfL1preNonisoCands);
      for (uint l1prenonisocand = 0 ; l1prenonisocand < treeVars.nbOfL1preNonisoCands ; l1prenonisocand++)
	{
	  if(treeVars.L1preNonisoRank[l1prenonisocand]>=2)
	    {
	      if(treeVars.L1preNonisoRank[l1prenonisocand]>=eg)
		{ //require EG2 by default, EG eg in general


		  //prefcheck
		  ptnonisoprefiring->Fill(treeVars.L1preNonisoRank[l1prenonisocand]);


		  occupancyL1preNoniso->Fill(treeVars.L1preNonisoIeta[l1prenonisocand],treeVars.L1preNonisoIphi[l1prenonisocand]);
		  L1preNonisoCandRank->Fill(treeVars.L1preNonisoRank[l1prenonisocand]);
		  L1Nonisotiming->Fill(-1);
		  std::vector<int> tteta = getECALRegionEta(treeVars.L1preNonisoIeta[l1prenonisocand]);
		  std::vector<int> ttphi = getECALRegionPhi(treeVars.L1preNonisoIphi[l1prenonisocand]);
            
		  if(abs(tteta[0])<17){//EB
		    L1NonisotimingEB->Fill(-1);
		  }
		  if(tteta[0]>=17){//EE+
		    L1NonisotimingEEPlus->Fill(-1); 
		  }
		  if(tteta[0]<=-17){//EE-
		    L1NonisotimingEEMinus->Fill(-1);   
		  }
            
		  for(uint i=0;i!=tteta.size();++i){
		    for(uint j=0;j!=ttphi.size();++j){ 
		      int l1prehash=0;
		      if (tteta[i]>0)
			l1prehash= tteta[i] * 100 + ttphi[j] ;
		      else 
			l1prehash = tteta[i] * 100 - ttphi[j] ;
                  
                  
		      if(abs(tteta[i])<18){//EB
                        occupancyL1preNonisoEB->Fill(ttphi[j],tteta[i]);
		      }
		      if(tteta[i]>=18){//EE+
                        for (uint k=0; k !=geometry[l1prehash].size();++k){
			  occupancyL1preNonisoEEPlus->Fill(geometry[l1prehash][k].first,geometry[l1prehash][k].second ) ;
                        }
		      }
		      if(tteta[i]<=-18){//EE-
                        for (uint k=0; k !=geometry[l1prehash].size();++k){
			  occupancyL1preNonisoEEMinus->Fill(geometry[l1prehash][k].first,geometry[l1prehash][k].second ) ;
                        }
		      }
		    }
		  }
		}
	    }
	}
      
      
      //fill some post-firing L1 histograms
      nbOfL1postIsoCands->Fill(treeVars.nbOfL1postIsoCands);
      for (uint l1postisocand = 0 ; l1postisocand < treeVars.nbOfL1postIsoCands ; l1postisocand++)
	{
	  if(treeVars.L1postIsoRank[l1postisocand]>=2)
	    {
	      if(treeVars.L1postIsoRank[l1postisocand]>=eg)
		{

		  //prefcheck
		  ptisopostfiring->Fill(treeVars.L1postIsoRank[l1postisocand]);



		  //require EG2 by default, EG eg in general
		  occupancyL1postIso->Fill(treeVars.L1postIsoIeta[l1postisocand],treeVars.L1postIsoIphi[l1postisocand]);
		  L1postIsoCandRank->Fill(treeVars.L1postIsoRank[l1postisocand]);
		  L1Isotiming->Fill(1);
		  std::vector<int> tteta = getECALRegionEta(treeVars.L1postIsoIeta[l1postisocand]);
		  std::vector<int> ttphi = getECALRegionPhi(treeVars.L1postIsoIphi[l1postisocand]);
               
		  if(abs(tteta[0])<17){//EB
		    L1IsotimingEB->Fill(1);
		  }
		  if(tteta[0]>=17){//EE+
		    L1IsotimingEEPlus->Fill(1);  
		  }
		  
		  if(tteta[0]<=-17){//EE-
		    L1IsotimingEEMinus->Fill(1); 
		  }
               
               
		  for(uint i=0;i!=tteta.size();++i){
		    for(uint j=0;j!=ttphi.size();++j){ 
		      int l1posthash=0;
		      if (tteta[i]>0)
                        l1posthash= tteta[i] * 100 + ttphi[j] ;
		      else 
                        l1posthash = tteta[i] * 100 - ttphi[j] ;
                     
                     
		      if(abs(tteta[i])<18){//EB
                        occupancyL1postIsoEB->Fill(ttphi[j],tteta[i]);
		      }
		      if(tteta[i]>=18){//EE+
                        for (uint k=0; k !=geometry[l1posthash].size();++k){
			  occupancyL1postIsoEEPlus->Fill(geometry[l1posthash][k].first,geometry[l1posthash][k].second ) ;
                        }
		      }
		      if(tteta[i]<=-18){//EE-
                        for (uint k=0; k !=geometry[l1posthash].size();++k){
			  occupancyL1postIsoEEMinus->Fill(geometry[l1posthash][k].first,geometry[l1posthash][k].second ) ;
                        }
		      }
		    }
		  }
		}
	    }
	}
      
      nbOfL1postNonisoCands->Fill(treeVars.nbOfL1postNonisoCands);
      for (uint l1postnonisocand = 0 ; l1postnonisocand < treeVars.nbOfL1postNonisoCands ; l1postnonisocand++)
	{
	  if(treeVars.L1postNonisoRank[l1postnonisocand]>=2)
	    {
	      if(treeVars.L1postNonisoRank[l1postnonisocand]>=eg)
		{



		  //prefcheck
		  ptnonisopostfiring->Fill(treeVars.L1postNonisoRank[l1postnonisocand]);

		  //require EG2 by default, EG eg in general
		  occupancyL1postNoniso->Fill(treeVars.L1postNonisoIeta[l1postnonisocand],treeVars.L1postNonisoIphi[l1postnonisocand]);
		  L1postNonisoCandRank->Fill(treeVars.L1postNonisoRank[l1postnonisocand]);
		  L1Nonisotiming->Fill(1);
		  std::vector<int> tteta = getECALRegionEta(treeVars.L1postNonisoIeta[l1postnonisocand]);
		  std::vector<int> ttphi = getECALRegionPhi(treeVars.L1postNonisoIphi[l1postnonisocand]);
		  if(abs(tteta[0])<17){//EB
		    L1NonisotimingEB->Fill(1);
		  }
		  if(tteta[0]>=17){//EE+
		    L1NonisotimingEEPlus->Fill(1);  
		  }
		  if(tteta[0]<=-17){//EE-
		    L1NonisotimingEEMinus->Fill(1); 
		  }
		  for(uint i=0;i!=tteta.size();++i){
		    for(uint j=0;j!=ttphi.size();++j){ 
		      int l1posthash=0;
		      if (tteta[i]>0)
                        l1posthash= tteta[i] * 100 + ttphi[j] ;
		      else 
                        l1posthash = tteta[i] * 100 - ttphi[j] ;
                     
                     
		      if(abs(tteta[i])<18){//EB
                        occupancyL1postNonisoEB->Fill(ttphi[j],tteta[i]);
		      }
		      if(tteta[i]>=18){//EE+
                        for (uint k=0; k !=geometry[l1posthash].size();++k){
			  occupancyL1postNonisoEEPlus->Fill(geometry[l1posthash][k].first,geometry[l1posthash][k].second ) ;
                        }
		      }
		      if(tteta[i]<=-18){//EE-
                        for (uint k=0; k !=geometry[l1posthash].size();++k){
			  occupancyL1postNonisoEEMinus->Fill(geometry[l1posthash][k].first,geometry[l1posthash][k].second ) ;
                        }
		      }
		    }
		  }
		}
	    }
	}
      
      
      
      //counters for filling L1 histos after looping over all the towers
      
      int MaxTPinIsoRegion[4];
      int MaxTPinIsoRegionIeta[4];
      int MaxTPinIsoRegionIphi[4];
      int SecondTPinIsoRegion[4];
      // int sevlev_Iso[4];     


      int MaxTPinpreIsoRegion[4];
      int MaxTPinpreIsoRegionIeta[4];
      int MaxTPinpreIsoRegionIphi[4];
      int SecondTPinpreIsoRegion[4];
     

       
      int MaxTPinpreIsoRegion_min2[4];
      int MaxTPinpreIsoRegion_min2Ieta[4];
      int MaxTPinpreIsoRegion_min2Iphi[4];
      int SecondTPinpreIsoRegion_min2[4];
     
 
      int MaxTPinpreIsoRegion_min1[4];
      int MaxTPinpreIsoRegion_min1Ieta[4];
      int MaxTPinpreIsoRegion_min1Iphi[4];
      int SecondTPinpreIsoRegion_min1[4];
     
 
      int MaxTPinpreIsoRegion_corrbx[4];
      int MaxTPinpreIsoRegion_corrbxIeta[4];
      int MaxTPinpreIsoRegion_corrbxIphi[4];
      int SecondTPinpreIsoRegion_corrbx[4];
     
 
      int MaxTPinpreIsoRegion_plus1[4];
      int MaxTPinpreIsoRegion_plus1Ieta[4];
      int MaxTPinpreIsoRegion_plus1Iphi[4];
      int SecondTPinpreIsoRegion_plus1[4];
     
 
      int MaxTPinpreIsoRegion_plus2[4];
      int MaxTPinpreIsoRegion_plus2Ieta[4];
      int MaxTPinpreIsoRegion_plus2Iphi[4];
      int SecondTPinpreIsoRegion_plus2[4];
     
 

 
      int MaxTPinNonisoRegion[4];
      int MaxTPinNonisoRegionIeta[4];
      int MaxTPinNonisoRegionIphi[4];
      int SecondTPinNonisoRegion[4];
      //      int sevlev_NonIso[4];     
      
      for(int i=0;i<4;++i)
	{
	  MaxTPinIsoRegion[i]=0;
	  MaxTPinIsoRegionIeta[i]=0;
	  MaxTPinIsoRegionIphi[i]=0;
	  SecondTPinIsoRegion[i]=0;
	  // sevlev_Iso[i]=0;     

	  MaxTPinNonisoRegion[i]=0;
	  MaxTPinNonisoRegionIeta[i]=0;
	  MaxTPinNonisoRegionIphi[i]=0;
	  SecondTPinNonisoRegion[i]=0;

	  MaxTPinpreIsoRegion[i]=0;
	  MaxTPinpreIsoRegionIeta[i]=0;
	  MaxTPinpreIsoRegionIphi[i]=0;
	  SecondTPinpreIsoRegion[i]=0;
     

       
	  MaxTPinpreIsoRegion_min2[i]=0;
	  MaxTPinpreIsoRegion_min2Ieta[i]=0;
	  MaxTPinpreIsoRegion_min2Iphi[i]=0;
	  SecondTPinpreIsoRegion_min2[i]=0;
	   
	   
	  MaxTPinpreIsoRegion_min1[i]=0;
	  MaxTPinpreIsoRegion_min1Ieta[i]=0;
	  MaxTPinpreIsoRegion_min1Iphi[i]=0;
	  SecondTPinpreIsoRegion_min1[i]=0;
	   
	   
	  MaxTPinpreIsoRegion_corrbx[i]=0;
	  MaxTPinpreIsoRegion_corrbxIeta[i]=0;
	  MaxTPinpreIsoRegion_corrbxIphi[i]=0;
	  SecondTPinpreIsoRegion_corrbx[i]=0;
	   
	   
	  MaxTPinpreIsoRegion_plus1[i]=0;
	  MaxTPinpreIsoRegion_plus1Ieta[i]=0;
	  MaxTPinpreIsoRegion_plus1Iphi[i]=0;
	  SecondTPinpreIsoRegion_plus1[i]=0;
	   
	   
	  MaxTPinpreIsoRegion_plus2[i]=0;
	  MaxTPinpreIsoRegion_plus2Ieta[i]=0;
	  MaxTPinpreIsoRegion_plus2Iphi[i]=0;
	  SecondTPinpreIsoRegion_plus2[i]=0;
	  // sevlev_NonIso[i]=0;     

	}
      
      
      
      bool eventBool=false;
      // loop on towers
      
      for (uint tower = 0 ; tower < treeVars.nbOfTowers ; tower++)
	{
         
	  //std::cout<<"event kept, in tower loop"<<std::endl;
         
	  int tp = getEt(treeVars.rawTPData[tower]) ;
	  int raw_spike = treeVars.trig_tower_sFGVB[tower];
	  float erec_val=treeVars.eRec[tower];
	  //	  int severity_level=treeVars.sevlv[tower];
	  int emul[5] = {getEt(treeVars.rawTPEmul1[tower]),  
			 getEt(treeVars.rawTPEmul2[tower]),
			 getEt(treeVars.rawTPEmul3[tower]),
			 getEt(treeVars.rawTPEmul4[tower]),
			 getEt(treeVars.rawTPEmul5[tower])} ;
         
	  //std::cout<<"event kept, TP&emul filled"<<std::endl;
         
         
	  int maxOfTPEmul = 0 ;
	  int indexOfTPEmulMax = -1 ;
	  for (int i=0 ; i<5 ; i++) if (emul[i]>maxOfTPEmul)
				      {
					maxOfTPEmul = emul[i] ; 
					indexOfTPEmulMax = i ;
				      }
	  int ieta = treeVars.ieta[tower] ;
	  int iphi = treeVars.iphi[tower] ;
	  int hashedIndex =0 ;
	  if (ieta >0)
            hashedIndex = ieta * 100 + iphi ;
	  else 
            hashedIndex = ieta * 100 - iphi ;
         
	  //apply hashedIndex filter
	  keep = false;
	  if(towerIncludeVector.size()==0) keep = true;
	  for(uint i=0; i!=towerIncludeVector.size();++i){
	    if(hashedIndex==towerIncludeVector[i]) keep=true;
	  }
	  if(!keep) continue;
	  keep = true;
	  for(uint i=0; i!=towerExcludeVector.size();++i){
	    if(hashedIndex==towerExcludeVector[i]) keep=false;
	  }
	  if(!keep) continue;
            
            
	  //do comparison with L1 objects
            
            
	  for (uint l1isocand = 0 ; l1isocand < treeVars.nbOfL1IsoCands ; l1isocand++)
	    {
	      if(treeVars.L1IsoRank[l1isocand]>=eg)
		{
		  //require EG1 by default, EG eg in general
		  if(treeVars.L1IsoIphi[l1isocand]==getGCTRegionPhi(iphi) && treeVars.L1IsoIeta[l1isocand]==getGCTRegionEta(ieta))
		    {
		      //geometric match
		      if(tp>= MaxTPinIsoRegion[l1isocand])
			{//we have a new maximum
			  MaxTPinIsoRegion[l1isocand]=tp;
			  MaxTPinIsoRegionIeta[l1isocand]=ieta;
			  MaxTPinIsoRegionIphi[l1isocand]=iphi;
			  // sevlev_Iso[l1isocand]=severity_level;
			}
		    }
		}
	    }
	    
	    
	  for (uint l1nonisocand = 0 ; l1nonisocand < treeVars.nbOfL1NonisoCands ; l1nonisocand++)
	    {
	      if(treeVars.L1NonisoRank[l1nonisocand]>=eg)
		{
		  //require EG1 by default, EG eg in general
		  if(treeVars.L1NonisoIphi[l1nonisocand]==getGCTRegionPhi(iphi) && treeVars.L1NonisoIeta[l1nonisocand]==getGCTRegionEta(ieta))
		    {
		      //geometric match
		      if(tp>= MaxTPinNonisoRegion[l1nonisocand])
			{//we have a new maximum
			  MaxTPinNonisoRegion[l1nonisocand]=tp;
			  MaxTPinNonisoRegionIeta[l1nonisocand]=ieta;
			  MaxTPinNonisoRegionIphi[l1nonisocand]=iphi;
			  // sevlev_NonIso[l1nonisocand]=severity_level;
			}
		    }
		}
	    }
	      
	  //comparing preiso candidates to tp
            
	  for (uint l1preIsocand = 0 ; l1preIsocand < treeVars.nbOfL1preIsoCands ; l1preIsocand++)
	    {
	      if(treeVars.L1preIsoRank[l1preIsocand]>=eg)
		{ 
		  //require EG1 by default, EG eg in general
		  if(treeVars.L1preIsoIphi[l1preIsocand]==getGCTRegionPhi(iphi) && treeVars.L1preIsoIeta[l1preIsocand]==getGCTRegionEta(ieta))
		    {
		      //geometric match
		      if(tp>= MaxTPinpreIsoRegion[l1preIsocand])
			{//we have a new maximum
			 // cout<<"1"<<endl;
			  MaxTPinpreIsoRegion[l1preIsocand]=tp;
			  MaxTPinpreIsoRegionIeta[l1preIsocand]=ieta;
			  MaxTPinpreIsoRegionIphi[l1preIsocand]=iphi;
			}
		      if(emul[0]>= MaxTPinpreIsoRegion_min2[l1preIsocand])
			{//we have a new maximum
			 // cout<<"2"<<endl;
			  MaxTPinpreIsoRegion_min2[l1preIsocand]=emul[0];
			  MaxTPinpreIsoRegion_min2Ieta[l1preIsocand]=ieta;
			  MaxTPinpreIsoRegion_min2Iphi[l1preIsocand]=iphi;
			}
		      
		      
		      if(emul[1]>= MaxTPinpreIsoRegion_min1[l1preIsocand])
			{//we have a new maximum
			 // cout<<"3"<<endl;
			  MaxTPinpreIsoRegion_min1[l1preIsocand]=emul[1];
			  MaxTPinpreIsoRegion_min1Ieta[l1preIsocand]=ieta;
			  MaxTPinpreIsoRegion_min1Iphi[l1preIsocand]=iphi;
			}
		      if(emul[ref]>= MaxTPinpreIsoRegion_corrbx[l1preIsocand])
			{//we have a new maximum
			 // cout<<"4"<<endl;
			  MaxTPinpreIsoRegion_corrbx[l1preIsocand]=emul[ref];
			  MaxTPinpreIsoRegion_corrbxIeta[l1preIsocand]=ieta;
			  MaxTPinpreIsoRegion_corrbxIphi[l1preIsocand]=iphi;
			}
			  
		      if(emul[3]>= MaxTPinpreIsoRegion_plus1[l1preIsocand])
			{//we have a new maximum
			  //cout<<"5"<<endl;
			  MaxTPinpreIsoRegion_plus1[l1preIsocand]=emul[3];
			  MaxTPinpreIsoRegion_plus1Ieta[l1preIsocand]=ieta;
			  MaxTPinpreIsoRegion_plus1Iphi[l1preIsocand]=iphi;
			}

		      if(emul[4]>= MaxTPinpreIsoRegion_plus2[l1preIsocand])
			{//we have a new maximum
			 // cout<<"5"<<endl;
			  MaxTPinpreIsoRegion_plus2[l1preIsocand]=emul[4];
			  MaxTPinpreIsoRegion_plus2Ieta[l1preIsocand]=ieta;
			  MaxTPinpreIsoRegion_plus2Iphi[l1preIsocand]=iphi;
			}

		      

		    }
		}
	    }
	    
	    

            
	  if (maxOfTPEmul>occupancyCut) TPEmulMax3D->Fill(iphi, ieta, indexOfTPEmulMax+1 );
	  //if (maxOfTPEmul==0) TPEmulMax3D->Fill(iphi, ieta, -1 );
      
      
	  uint nbXtals = treeVars.nbOfXtals[tower] ;
	  int ttf = getTtf(treeVars.rawTPData[tower]) ;
      
      
	  if (verbose>9 && (tp>0 || maxOfTPEmul>0)) {
	    std::cout<<"(phi,eta, Nbxtals)="<<std::dec<<iphi<<" "<<ieta<<" "<<nbXtals<<std::endl ;
	    std::cout<<"Data Et, TTF: "<<tp<<" "<<ttf<<std::endl ;
	    std::cout<<"Emulator: " ;
	    for (int i=0 ; i<5 ; i++) std::cout<<emul[i]<<"jugal " ;
	    std::cout<<std::endl ;
	  }
      
	  if(tp>occupancyCut) {
	    occupancyTP_vs_EvtNb->Fill(treeVars.evtNb/1000000.);
	    time3D->Fill(iphi,ieta,treeVars.timeStamp/60. - slMinTime);
	    TimeStamp->Fill(treeVars.timeStamp/60. - slMinTime);
	    LumiSection->Fill(treeVars.lumiBlock - slMinLS);
	    LS3D->Fill(iphi,ieta,treeVars.lumiBlock - slMinLS);
	    iEta_vs_LS->Fill(treeVars.lumiBlock - slMinLS, ieta);
	    iPhi_vs_LS->Fill(treeVars.lumiBlock - slMinLS, iphi);
	    iEta_vs_Time->Fill(treeVars.timeStamp/60. - slMinTime, ieta);
	    iPhi_vs_Time->Fill(treeVars.timeStamp/60. - slMinTime, iphi);
	  }
      
	
	  // Fill TP spectra
	  if (abs(ieta)<18)
	    {
	      //barrel
	      if (tp>0 && emul[ref]>0) 
		{
		  TPEB->Fill(tp) ;
		if (raw_spike!=0) {
		  TPEB_noSpike->Fill(tp) ;
		  if (treeVars.ttFlag[tower]==3){
		    TPEB_fullReadout->Fill(tp) ;
		    if (tp>24 && tp<3500 && erec_val>24){
		      TP_emul_ratio_vs_Et_EB->Fill(tp/(emul[ref]),tp/2);
		      TP_vs_emulatedTP_EB->Fill((emul[ref]),tp);
		      TP_emulatedTPEnergy_ratio_EB->Fill(tp/(emul[ref])) ;
		      if(tp/(emul[ref])>1.3 || tp/(emul[ref])<0.7){
			TPSpect_TPvemulatedTP_outliers_EB->Fill(tp);
		      }
		    }
		  }
		}
	      }
	      if (tp>0){
		if (emul[ref]>0)
		  {
		    TPEmulEB_whenTPRealexists->Fill(emul[ref]);
		    if(tp>20 && emul[ref]>20){
		      Ratio_EB_whenTPRealexists->Fill(float(emul[ref])/float(tp));
		    }
		  }
	      }
	      else
		{
		  {if (emul[ref]>0) TPEmulEB_when_no_NZ_TPReal->Fill(emul[ref]);
		  }
		}
	      if (tp>0) TPspectrumMap3DEB->Fill(iphi, ieta, tp) ;
	      if (emul[ref]>0) TPEmulEB->Fill(emul[ref]) ;
	      if (maxOfTPEmul>occupancyCut) TPEmulMaxEB->Fill(maxOfTPEmul) ;
	    }
      
	  if (geometry.size()>0)
	    {
         
	      if (ieta>=18)
		{
		  // EE+
		  if (tp>occupancyCut) {TPEEPlus->Fill(tp) ;
		    if (treeVars.ttFlag[tower]==3){
		      TPEEPlus_fullReadout->Fill(tp) ; 
		      if (tp>24 && tp<3500 && erec_val>24 &&emul[ref]>0){
			TP_emul_ratio_vs_Et_EEPlus->Fill(tp/(emul[ref]),tp/2);
			if (ieta>=18 && ieta<=22){TP_vs_emulatedTP_EEPlus_18_22->Fill((emul[ref]),tp);}
			if (ieta>=23 && ieta<=27){TP_vs_emulatedTP_EEPlus_23_27->Fill((emul[ref]),tp);}
			if (ieta>=28){TP_vs_emulatedTP_EEPlus_28_end->Fill((emul[ref]),tp);}
			TP_vs_emulatedTP_EEPlus->Fill((emul[ref]),tp);
			TP_emulatedTPEnergy_ratio_EEPlus->Fill(tp/(emul[ref])) ;
			if(tp/(emul[ref])>1.3 || tp/(emul[ref])<0.7){
			  TPSpect_TPvemulatedTP_outliers_EEPlus->Fill(tp);
			}
		      }
		    }
		  }
		
		  if (tp>0){
		    if (emul[ref]>0){
		      TPEmulEEPlus_whenTPRealexists->Fill(emul[ref]);
		      if (tp>20 && emul[ref]>20){
			Ratio_EEPlus_whenTPRealexists->Fill(float(emul[ref])/float(tp));
		      }
		    }
		  }
		  else
		    {if (emul[ref]>0) TPEmulEEPlus_when_no_NZ_TPReal->Fill(emul[ref]);}
		  
		  if (emul[ref]>occupancyCut) TPEmulEEPlus->Fill(emul[ref]) ;
		  if (maxOfTPEmul>occupancyCut) TPEmulMaxEEPlus->Fill(maxOfTPEmul) ;
		  if (tp>occupancyCut)
		    {
		      for (uint i=0; i !=geometry[hashedIndex].size();++i)
			TPspectrumMap3DEEPlus->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second,tp) ;
		    }
		}
         
	      if (ieta<=-18)
		{
		  //EE-
		  if (tp>occupancyCut) {TPEEMinus->Fill(tp) ;
		    if (treeVars.ttFlag[tower]==3){
		      TPEEMinus_fullReadout->Fill(tp) ; 
		      if (tp>24 && tp<3500 && emul[ref]>0){
			TP_emul_ratio_vs_Et_EEMinus->Fill(tp/(emul[ref]),tp/2);
			if (ieta<=-18 && ieta>=-22){TP_vs_emulatedTP_EEMinus_18_22->Fill((emul[ref]),tp);}
			if (ieta<=-23 && ieta>=-27){TP_vs_emulatedTP_EEMinus_23_27->Fill((emul[ref]),tp);}
			if (ieta<=-28){TP_vs_emulatedTP_EEMinus_28_end->Fill((emul[ref]),tp);}

			TP_vs_emulatedTP_EEMinus->Fill((emul[ref]),tp);
			TP_emulatedTPEnergy_ratio_EEMinus->Fill(tp/(emul[ref])) ; 
			if(tp/(emul[ref])>1.3 || tp/(emul[ref])<0.7){
			  TPSpect_TPvemulatedTP_outliers_EEMinus->Fill(tp);
			}
		      }
		    }
		  }
		  
		  if (tp>0){
		    if (emul[ref]>0)
		      {
			TPEmulEEMinus_whenTPRealexists->Fill(emul[ref]);
			if (tp>20 && emul[ref]>20){
			  Ratio_EEMinus_whenTPRealexists->Fill(float(emul[ref])/float(tp));
			}
		      }
		  }
		  else
		    { if(emul[ref]>0) TPEmulEEMinus_when_no_NZ_TPReal->Fill(emul[ref]);}
		  
		  
		  if (emul[ref]>occupancyCut) TPEmulEEMinus->Fill(emul[ref]) ;
		  if (maxOfTPEmul>occupancyCut) TPEmulMaxEEMinus->Fill(maxOfTPEmul) ;
	   
		  if (tp>occupancyCut){   
		    for (uint i=0; i !=geometry[hashedIndex].size();++i)
		      TPspectrumMap3DEEMinus->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second,tp) ;
		  }
		}
	    }
      
      
      
	  // Fill BX histo  TIMING OCCUPANCY HISTOs
      
	  if (tp>occupancyCut) bx_Vs_TP->Fill(bxNb,tp) ;
	  if (emul[ref]>occupancyCut) bx_Vs_TPEmul->Fill(bxNb,emul[ref]); // only reference Tp 
	  if (tp>occupancyCut)  bx_Vs_Orbit->Fill(bxNb,float(orbitNb)/1000000.);  
         
	  if (tp>occupancyCut)
	    {
	      for (uint ntrig = 0 ; ntrig < treeVars.nbOfActiveTriggers ; ntrig++)
		{
		  if (algobitsbx.size()>0) {
		    for (uint algo = 0 ; algo<algobitsbx.size() ; algo++)
		      if (algobitsbx[algo] == treeVars.activeTriggers[ntrig]) bx_Vs_TriggerBit->Fill(bxNb,treeVars.activeTriggers[ntrig]) ;
		  } else {
		    bx_Vs_TriggerBit->Fill(bxNb,treeVars.activeTriggers[ntrig]) ;
		  }
		}
	      orbit ->Fill(float(orbitNb)/1000000.);
	      bx ->Fill(bxNb);
	    }
	  //ratio vs ieta code from silvia      



	  // Fill TP occupancy
      
	  if (tp>occupancyCut && abs(ieta)<18 && emul[ref]>0)
	    {
	      //barrel
	      occupancyTPEB->Fill(iphi, ieta) ;         
	      TPEtaEB->Fill(ieta) ; 
	      TPPhiEB->Fill(iphi) ;
	      if (raw_spike!=0) {
		if (treeVars.ttFlag[tower]==3){
		  if (tp>24 && tp<3500 && erec_val>24){
		    ADC_emulatedTP_EB2D->Fill(iphi,ieta,(emul[ref]));
		    TP_EB2D->Fill(iphi,ieta,tp);
		    if(tp/(emul[ref])>1.3 || tp/(emul[ref])<0.7){
		      //if (entry%3==0) cout<<"severity_level :"<<severity_level<<endl;  
		      occu_TPvemulatedTP_outliers_EB->Fill(iphi,ieta);
		    }
		  }
		}
	      }
	    }
	  else
	    {
	      if (emul[ref]>occupancyCut && abs(ieta)<18) occupancyTPEmulEB_when_no_real_NZ_TP->Fill(iphi, ieta) ;}  //barrel
	  
	  if (emul[ref]>occupancyCut && abs(ieta)<18) occupancyTPEmulEB->Fill(iphi, ieta) ;  //barrel
	  //this is new, filling the mismatched occupancy
	  
	  if (maxOfTPEmul>occupancyCut && ((indexOfTPEmulMax+1==5) | (indexOfTPEmulMax+1==1))&& abs(ieta)<18) {
	    occupancyTPEBmis->Fill(iphi,ieta);
	    TPEtaEBmis->Fill(ieta);
	    TPPhiEBmis->Fill(iphi);
	    TPEtaEBmisSpec->Fill(maxOfTPEmul);
	  }
	
	  if (geometry.size()>0)
	    {
	      if (ieta>=18 )
		{  
		  //EE+
		  if(tp>occupancyCut)
		    {
		      TPEtaEEPlus->Fill(ieta) ; 
		      TPPhiEEPlus->Fill(iphi) ;
	       
		    }
		  if (maxOfTPEmul>occupancyCut && ((indexOfTPEmulMax+1==5) | (indexOfTPEmulMax+1==1))) 
		    {
		      TPEmulEtaEEPlus_mis->Fill(ieta) ; 
		      TPEmulPhiEEPlus_mis->Fill(iphi) ;
		      TPEtaEEPlusmisSpec->Fill(maxOfTPEmul);
		    } 
	     
		  for (uint i=0; i !=geometry[hashedIndex].size();++i)
		    {
		      if (tp>occupancyCut && emul[ref]>0) 
			{ 
			  occupancyTPEEPlus->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second ) ;       
			  if (treeVars.ttFlag[tower]==3){
			    if (tp>24 && tp<3500){
			      ADC_emulatedTP_EEPlus2D->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second,(emul[ref]));
			      TP_EEPlus2D->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second,tp);
			      if(tp/(emul[ref])>1.3 || tp/(emul[ref])<0.7){
				occu_TPvemulatedTP_outliers_EEPlus->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second);
			      }
			    }
			  }
			}
		      else
			{
			  if (emul[ref]>occupancyCut && ieta>=18) occupancyTPEmulEEPlus_when_no_real_NZ_TP->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second ) ;  
			}     
		      
		      
		      occupancyTPEEPlusAll->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second ) ;  
		 
		      if ( maxOfTPEmul>occupancyCut)
			{    
			  occupancyTPEmulEEPlusALL->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second ) ;
			}
		      if (emul[ref]>occupancyCut) 
			{
			  occupancyTPEmulEEPlus->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second ) ;        
			}
		      if (maxOfTPEmul>occupancyCut && ((indexOfTPEmulMax+1==5) | (indexOfTPEmulMax+1==1))) 
			{
			  occupancyTPEmulEEPlus_mis->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second ) ;        
			}
		    }
		}
         
	      if (ieta<=-18 )
		{
		  //EE-
		  if(tp>occupancyCut)
		    {
		      TPEtaEEMinus->Fill(ieta) ; 
		      TPPhiEEMinus->Fill(iphi) ;
		    }
		  if (maxOfTPEmul>occupancyCut && ((indexOfTPEmulMax+1==5) | (indexOfTPEmulMax+1==1))) 
		    {
		      TPEmulEtaEEMinus_mis->Fill(ieta) ; 
		      TPEmulPhiEEMinus_mis->Fill(iphi) ;
		      TPEtaEEMinusmisSpec->Fill(maxOfTPEmul);
		    } 
	    
		  for (uint i=0; i !=geometry[hashedIndex].size();++i)
		    {
		      if (tp>occupancyCut && emul[ref]>0)
			{
			  occupancyTPEEMinus->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second ) ;
			  if (treeVars.ttFlag[tower]==3){
			    if (tp>24 && tp<3500){
			      ADC_emulatedTP_EEMinus2D->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second,(emul[ref]));
			      TP_EEMinus2D->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second,tp);
			      if(tp/(emul[ref])>1.3 || tp/(emul[ref])<0.7){
				occu_TPvemulatedTP_outliers_EEMinus->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second);
			      }
			    }
			  }
			}
		      else
			{
			  if (emul[ref]>occupancyCut && ieta<=-18) occupancyTPEmulEEMinus_when_no_real_NZ_TP->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second ) ;       
			} 

		      occupancyTPEEMinusAll->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second ) ;
		
		      if ( maxOfTPEmul>occupancyCut)
			{
			  occupancyTPEmulEEMinusALL->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second ) ;       
		    
			}
		      if (emul[ref]>occupancyCut) 
			{
			  occupancyTPEmulEEMinus->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second ) ;       
			}
		      if (maxOfTPEmul>occupancyCut && ((indexOfTPEmulMax+1==5) | (indexOfTPEmulMax+1==1))) 
			{
			  occupancyTPEmulEEMinus_mis->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second ) ;        
			}
		
		
		    }
		}
	    }
      
      
	  // Fill Emulator-TP matching
	  // as soon as emul[ref]>0 we look to the TP. No need to check nb of crystal readout, it's more timing oriented.
	  if (emul[ref]>occupancyCut) {
	    if (tp>occupancyCut) {
	      if (abs(ieta)<=17) {
		TPTimingEBFromEmulOK->Fill(iphi, ieta) ;
		if (emul[ref] == tp) TPTimingEBFromEmulOKAndMatch->Fill(iphi, ieta) ;
	      } else if (ieta<-17) {
		for (uint i=0; i !=geometry[hashedIndex].size();++i) {
                  TPTimingEEMinusFromEmulOK->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second) ;
                  if (emul[ref] == tp) TPTimingEEMinusFromEmulOKAndMatch->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second) ;
		}
	      } else if (ieta>17) {
		for (uint i=0; i !=geometry[hashedIndex].size();++i) {
                  TPTimingEEPlusFromEmulOK->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second) ;
                  if (emul[ref] == tp) TPTimingEEPlusFromEmulOKAndMatch->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second) ;
		}     
	      }
	    }
	    else {
	      if (abs(ieta)<=17)
		TPTimingEBFromEmulWrong->Fill(iphi, ieta) ;
	      else if (ieta<-17) {
		for (uint i=0; i !=geometry[hashedIndex].size();++i)
                  TPTimingEEMinusFromEmulWrong->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second) ;      
	      } else if (ieta>17) {
		for (uint i=0; i !=geometry[hashedIndex].size();++i)
                  TPTimingEEPlusFromEmulWrong->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second) ;       
	      }
	    }
	  }
      
	  // Fill TP-Emulator matching
	  // comparison is meaningful when:
      
	  //for barrel
	  if (tp>occupancyCut && abs(ieta)<=17) {
	    if (nbXtals==25) {
	      TPCompEmulEB->Fill(iphi, ieta);
	      bool match(false) ;
	      for (int i=0 ; i<5 ; i++) {
		if (tp == emul[i]) {
                  TPMatchEmulEB->Fill(i+1) ;
                  TPMatchEmul3D->Fill(iphi, ieta, i+1) ;
                  match = true ;
		}
	      }
	      if (!match) {
		TPMatchEmulEB->Fill(-1) ;
		TPMatchEmul3D->Fill(iphi, ieta, -1) ;
		if (verbose>5) {
                  std::cout<<"MISMATCH"<<std::endl ;
                  std::cout<<"(phi,eta, Nbxtals)="<<std::dec<<iphi<<" "<<ieta<<" "<<nbXtals<<std::endl ;
                  std::cout<<"Data Et, TTF: "<<tp<<" "<<ttf<<std::endl ;
                  std::cout<<"Emulator: " ;
                  for (int i=0 ; i<5 ; i++) std::cout<<emul[i]<<" " ;
                  std::cout<<std::endl ;
		}
	      }
	    }
	    else {
	      if (ttf==1 || ttf==3) {
		MaskedReadOutEB->Fill(iphi, ieta);
	      }
	    }
	  }
      
	  //for endcaps
	  else if (tp>occupancyCut && ieta>=18) {
	    if(nbXtals==geometry[hashedIndex].size() ) {
	      for (uint i=0; i !=geometry[hashedIndex].size();++i) {
		TPCompEmulEEPlus->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second) ;
	      }
	      bool match(false) ;
            
	      for (int i=0 ; i<5 ; i++) {
               
		if (tp == emul[i]) {
                  TPMatchEmulEEPlus->Fill(i+1) ;
                  TPMatchEmul3D->Fill(iphi, ieta, i+1) ;
                  match = true ;
		}
	      }
	      if (!match) {
		TPMatchEmulEEPlus->Fill(-1) ;
		TPMatchEmul3D->Fill(iphi, ieta, -1) ;
		if (verbose>5) {
                  std::cout<<"MISMATCH"<<std::endl ;
                  std::cout<<"(phi,eta, Nbxtals)="<<std::dec<<iphi<<" "<<ieta<<" "<<nbXtals<<std::endl ;
                  std::cout<<"Data Et, TTF: "<<tp<<" "<<ttf<<std::endl ;
                  std::cout<<"Emulator: " ;
                  for (int i=0 ; i<5 ; i++) std::cout<<emul[i]<<" " ;
                  std::cout<<std::endl ;
		}
	      }
	    }
         
	    else {
	      if (ttf==1 || ttf==3){
		for (uint i=0; i !=geometry[hashedIndex].size();++i)
                  MaskedReadOutEEPlus->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second ) ;
	      }
	    }
	  }
      
	  //EE-
	  else if (tp>occupancyCut && ieta<=-18) {
	    if (nbXtals==geometry[hashedIndex].size() ) {
	      for (uint i=0; i !=geometry[hashedIndex].size();++i) {
		TPCompEmulEEMinus->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second ) ;
	      }
            
	      bool match(false) ;
	      for (int i=0 ; i<5 ; i++) {
		if (tp == emul[i]) {
                  TPMatchEmulEEMinus->Fill(i+1) ;
                  TPMatchEmul3D->Fill(iphi, ieta, i+1) ;
                  match = true ;
		}
	      }
	      if (!match) {
		TPMatchEmulEEMinus->Fill(-1) ;
		TPMatchEmul3D->Fill(iphi, ieta, -1) ;
		if (verbose>5) {
                  std::cout<<"MISMATCH"<<std::endl ;
                  std::cout<<"(phi,eta, Nbxtals)="<<std::dec<<iphi<<" "<<ieta<<" "<<nbXtals<<std::endl ;
                  std::cout<<"Data Et, TTF: "<<tp<<" "<<ttf<<std::endl ;
                  std::cout<<"Emulator: " ;
                  for (int i=0 ; i<5 ; i++) std::cout<<emul[i]<<" " ;
		  std::cout<<std::endl ;
		}
	      }
	    }
         
	    else {
	      if (ttf==1 || ttf==3) {
		for (uint i=0; i !=geometry[hashedIndex].size();++i)
		  MaskedReadOutEEMinus->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second) ;
	      }
            }
            
	  }
         
	  if (maxOfTPEmul>occupancyCut) {
           
            if(ieta<=-18)      TPEmulMaxIndexEEMinus->Fill(indexOfTPEmulMax+1) ;
            else if(ieta<18)    TPEmulMaxIndexEB->Fill(indexOfTPEmulMax+1) ;
            else if(ieta>=18)   TPEmulMaxIndexEEPlus->Fill(indexOfTPEmulMax+1) ;
	  }
	
	  if(tp>occupancyCut) 
	    {
	      ttfstatus_vs_LS_all->Fill(treeVars.lumiBlock,float(treeVars.ttFlag[tower]));
	      ttfstatus_all->Fill(float(treeVars.timeStamp/60),float(treeVars.ttFlag[tower]));
	    }

	  if (abs(ieta)<=17 && (ttf==1 || ttf==3) && nbXtals != 25) ttfMismatchEB->Fill(iphi, ieta) ; //EB
	  else if (ieta>=18 && (ttf==1 || ttf==3) && nbXtals != geometry[hashedIndex].size()) { //EE+
            for (uint i=0; i !=geometry[hashedIndex].size();++i) {
	      ttfMismatchEEPlus->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second ) ;
            }
	  }
	  else if (ieta<=-18 && (ttf==1 || ttf==3) && nbXtals != geometry[hashedIndex].size()) { //EE-
            for (uint i=0; i !=geometry[hashedIndex].size();++i) {
	      ttfMismatchEEMinus->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second ) ;
            }
	  }
         
	  if(tp>occupancyCut) eventBool=true;
         
	} // end loop towers
      
      
      if(eventBool) eventNb->Fill(treeVars.evtNb/1000000.);
    
      
      //loop over towers again to find the highest energy neighbor of the MaxTPinIsoRegion

      for (uint tower = 0 ; tower < treeVars.nbOfTowers ; tower++)
	{
	  int tp = getEt(treeVars.rawTPData[tower]) ;
	  int TTieta = treeVars.ieta[tower] ;
	  int TTiphi = treeVars.iphi[tower] ;
          int emul[5] = {getEt(treeVars.rawTPEmul1[tower]),  
			 getEt(treeVars.rawTPEmul2[tower]),
			 getEt(treeVars.rawTPEmul3[tower]),
			 getEt(treeVars.rawTPEmul4[tower]),
			 getEt(treeVars.rawTPEmul5[tower])} ;
	
	  if (abs(TTieta)>26)
	    {
	      for (uint l1preisocand = 0 ; l1preisocand < treeVars.nbOfL1preIsoCands ; l1preisocand++) 
		{
		  
		  int l1preisorank=treeVars.L1preIsoRank[l1preisocand];
		  if (l1preisorank>=eg)  
		    {
		      int maxtpieta=MaxTPinpreIsoRegionIeta[l1preisocand];
		      int maxtpiphi=MaxTPinpreIsoRegionIphi[l1preisocand];
		     
		      findsecondtp(l1preisocand,tp,maxtpieta,maxtpiphi,SecondTPinpreIsoRegion,TTieta,TTiphi);
		      findsecondtp(l1preisocand,emul[0],MaxTPinpreIsoRegion_min2Ieta[l1preisocand],MaxTPinpreIsoRegion_min2Iphi[l1preisocand],SecondTPinpreIsoRegion_min2,TTieta,TTiphi);
		      findsecondtp(l1preisocand,emul[1],MaxTPinpreIsoRegion_min1Ieta[l1preisocand],MaxTPinpreIsoRegion_min1Iphi[l1preisocand],SecondTPinpreIsoRegion_min1,TTieta,TTiphi);
		      findsecondtp(l1preisocand,emul[2],MaxTPinpreIsoRegion_corrbxIeta[l1preisocand],MaxTPinpreIsoRegion_corrbxIphi[l1preisocand],SecondTPinpreIsoRegion_corrbx,TTieta,TTiphi);
		      findsecondtp(l1preisocand,emul[3],MaxTPinpreIsoRegion_plus1Ieta[l1preisocand],MaxTPinpreIsoRegion_plus1Iphi[l1preisocand],SecondTPinpreIsoRegion_plus1,TTieta,TTiphi);
		      findsecondtp(l1preisocand,emul[4],MaxTPinpreIsoRegion_plus2Ieta[l1preisocand],MaxTPinpreIsoRegion_plus2Iphi[l1preisocand],SecondTPinpreIsoRegion_plus2,TTieta,TTiphi);	  
		    }
		}
	    }
	  for (uint l1isocand = 0 ; l1isocand < treeVars.nbOfL1IsoCands ; l1isocand++) {
            if(treeVars.L1IsoRank[l1isocand]>=eg) {
	      //require EG1 by default, EG eg in general
	      int L1ieta = MaxTPinIsoRegionIeta[l1isocand];
	      int L1iphi = MaxTPinIsoRegionIphi[l1isocand];
               
	      //find neighbor towers
               
	      //special cases
	      if(L1iphi==1 && TTiphi==72 && L1ieta==TTieta){  
		if(tp>=SecondTPinIsoRegion[l1isocand]) SecondTPinIsoRegion[l1isocand]=tp;
	      }
	      else if(L1iphi==72 && TTiphi==1 && L1ieta==TTieta){   
		if(tp>=SecondTPinIsoRegion[l1isocand]) SecondTPinIsoRegion[l1isocand]=tp;
	      }
	      else if(L1ieta==1 && TTieta==-1 && L1iphi==TTiphi){
		if(tp>=SecondTPinIsoRegion[l1isocand]) SecondTPinIsoRegion[l1isocand]=tp;
	      }
	      else if(L1ieta==-1 && TTieta==1 && L1iphi==TTiphi){
		if(tp>=SecondTPinIsoRegion[l1isocand]) SecondTPinIsoRegion[l1isocand]=tp;
	      }
	      //normal cases
	      else if(L1ieta==TTieta && abs(L1iphi-TTiphi)==1){//towers left and right
		if(tp>=SecondTPinIsoRegion[l1isocand]) SecondTPinIsoRegion[l1isocand]=tp;
	      }
	      else if(L1iphi==TTiphi && abs(L1ieta-TTieta)==1){//towers above and below
		if(tp>=SecondTPinIsoRegion[l1isocand]) SecondTPinIsoRegion[l1isocand]=tp;
	      }  
            }
	  }
         
	  for (uint l1nonisocand = 0 ; l1nonisocand < treeVars.nbOfL1NonisoCands ; l1nonisocand++) 
	    {
            
            if(treeVars.L1NonisoRank[l1nonisocand]>=eg) {
	      //require EG1 by default, EG eg in general
	      int L1ieta = MaxTPinNonisoRegionIeta[l1nonisocand];
	      int L1iphi = MaxTPinNonisoRegionIphi[l1nonisocand];
               
	      //find neighbor towers
               
	      //special cases
	      if(L1iphi==1 && TTiphi==72 && L1ieta==TTieta){  
		if(tp>=SecondTPinNonisoRegion[l1nonisocand]) SecondTPinNonisoRegion[l1nonisocand]=tp;
	      }
	      else if(L1iphi==72 && TTiphi==1 && L1ieta==TTieta){   
		if(tp>=SecondTPinNonisoRegion[l1nonisocand]) SecondTPinNonisoRegion[l1nonisocand]=tp;
	      }
	      else if(L1ieta==1 && TTieta==-1 && L1iphi==TTiphi){
		if(tp>=SecondTPinNonisoRegion[l1nonisocand]) SecondTPinNonisoRegion[l1nonisocand]=tp;
	      }
	      else if(L1ieta==-1 && TTieta==1 && L1iphi==TTiphi){
		if(tp>=SecondTPinNonisoRegion[l1nonisocand]) SecondTPinNonisoRegion[l1nonisocand]=tp;
	      }
               
	      //normal cases
	      else if(L1ieta==TTieta && abs(L1iphi-TTiphi)==1){//towers left and right
		if(tp>=SecondTPinNonisoRegion[l1nonisocand]) SecondTPinNonisoRegion[l1nonisocand]=tp;
	      }
	      else if(L1iphi==TTiphi && abs(L1ieta-TTieta)==1){//towers above and below
		if(tp>=SecondTPinNonisoRegion[l1nonisocand]) SecondTPinNonisoRegion[l1nonisocand]=tp;
	      }  
            }
	  }

	}




      for (uint l1isocand = 0 ; l1isocand < treeVars.nbOfL1IsoCands ; l1isocand++)
	{
      
	  if(treeVars.L1IsoRank[l1isocand]>=eg)
	    {
	      //require EG1 by default, EG eg in general
	      int twoTPSum = MaxTPinIsoRegion[l1isocand]+SecondTPinIsoRegion[l1isocand];
	      float ratio= float(twoTPSum)/(2*float(treeVars.L1IsoRank[l1isocand]));
	      //	      float ratio2= float(treeVars.L1IsoRank[l1isocand])/float(2*int(twoTPSum/2));
            
	      if(l1isocand==0) 
		L1Iso2TPSum->Fill(twoTPSum);
            
	      L1IsoRatio->Fill(ratio);
            
	      if(ratio==0)
		{
		  //missing TP
		  //std::cout << treeVars.evtNb << ",";
		  L1MissingTPIso->Fill(treeVars.L1IsoIeta[l1isocand],treeVars.L1IsoIphi[l1isocand]);
               
		  std::vector<int> tteta = getECALRegionEta(treeVars.L1IsoIeta[l1isocand]);
		  std::vector<int> ttphi = getECALRegionPhi(treeVars.L1IsoIphi[l1isocand]);
               
		  for(uint i=0;i!=tteta.size();++i)
		    {
		      for(uint j=0;j!=ttphi.size();++j)
			{
			  int l1hash=0;
                     
			  if (tteta[i]>0)
			    l1hash= tteta[i] * 100 + ttphi[j] ;
			  else 
			    l1hash = tteta[i] * 100 - ttphi[j] ;
                     
			  if(abs(tteta[i])<18){//EB
			    L1MissingTPIsoEB->Fill(ttphi[j],tteta[i]);
			  }
                     
			  if(tteta[i]>=18){//EE+
			    for (uint k=0; k !=geometry[l1hash].size();++k){
			      L1MissingTPIsoEEPlus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second ) ;
			    }
			  }
			  if(tteta[i]<=-18){//EE-
			    for (uint k=0; k !=geometry[l1hash].size();++k){
			      L1MissingTPIsoEEMinus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second ) ;
			    }
			  }
			}
		    }
		}
         
	      else {
		if(MaxTPinIsoRegion[l1isocand] != 255 && SecondTPinIsoRegion[l1isocand] != 255 && treeVars.L1IsoRank[l1isocand] != 63)
		  {
		    std::vector<int> tteta = getECALRegionEta(treeVars.L1IsoIeta[l1isocand]);
		    std::vector<int> ttphi = getECALRegionPhi(treeVars.L1IsoIphi[l1isocand]);
                  
		    for(uint i=0;i!=tteta.size();++i){
		      for(uint j=0;j!=ttphi.size();++j){
                        
                        int l1hash=0;
                        if (tteta[i]>0)
			  l1hash= tteta[i] * 100 + ttphi[j] ;
                        else 
			  l1hash = tteta[i] * 100 - ttphi[j] ;
                        
                        if(abs(tteta[i])<18)
			  {//EB
			  L1RatioTPIso3DEB->Fill(ttphi[j],tteta[i], ratio);
			  L1TPCompIsoEB->Fill(ttphi[j],tteta[i]);
			  }
                        if(tteta[i]>=18){//EE+
			  for (uint k=0; k !=geometry[l1hash].size();++k){
			    L1RatioTPIso3DEEPlus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second, ratio ) ;
			    L1TPCompIsoEEPlus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second );
			  }
                        }
                        if(tteta[i]<=-18){//EE-
			  for (uint k=0; k !=geometry[l1hash].size();++k){
			    L1RatioTPIso3DEEMinus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second, ratio ) ;
			    L1TPCompIsoEEMinus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second );
			  }
                        }
                        
		      }
		    }
		  }
	      }
            
	      if(ratio>1.3 || ratio<0.7)
		{
		  //value mismatch
		  L1ValueMismatchIso->Fill(treeVars.L1IsoIeta[l1isocand],treeVars.L1IsoIphi[l1isocand]);
               
		  std::vector<int> tteta = getECALRegionEta(treeVars.L1IsoIeta[l1isocand]);
		  std::vector<int> ttphi = getECALRegionPhi(treeVars.L1IsoIphi[l1isocand]);
               
		  for(uint i=0;i!=tteta.size();++i){
		    for(uint j=0;j!=ttphi.size();++j){
                     
		      int l1hash=0;
		      if (tteta[i]>0)
                        l1hash= tteta[i] * 100 + ttphi[j] ;
		      else 
                        l1hash = tteta[i] * 100 - ttphi[j] ;
                     
		      if(abs(tteta[i])<18){//EB
                        L1ValueMismatchIsoEB->Fill(ttphi[j],tteta[i]);
		      }
		      if(tteta[i]>=18){//EE+
                        for (uint k=0; k !=geometry[l1hash].size();++k){
			  L1ValueMismatchIsoEEPlus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second ) ;
                        }
		      }
		      if(tteta[i]<=-18){//EE-
                        for (uint k=0; k !=geometry[l1hash].size();++k){
			  L1ValueMismatchIsoEEMinus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second ) ;
                        }
		      }
		    }
		  }
		}
	    }
	}
   

    
          
      

      for (uint l1nonisocand = 0 ; l1nonisocand < treeVars.nbOfL1NonisoCands ; l1nonisocand++)
	{
         
	  if(treeVars.L1NonisoRank[l1nonisocand]>=eg)
	    {
	      //require EG1 by default, EG eg in general
	      float twoTPSum = float(MaxTPinNonisoRegion[l1nonisocand]+SecondTPinNonisoRegion[l1nonisocand]);
	      float ratio= float(MaxTPinNonisoRegion[l1nonisocand]+SecondTPinNonisoRegion[l1nonisocand])/float(treeVars.L1NonisoRank[l1nonisocand]);
	      float ratio2= float(treeVars.L1NonisoRank[l1nonisocand])/float(2*int(twoTPSum/2));
	      L1NonisoRatio->Fill(ratio);
            
	      L1Noniso2TPSum->Fill(twoTPSum);
            
	      if(ratio==0)
		{
               
		  L1MissingTPNoniso->Fill(treeVars.L1NonisoIeta[l1nonisocand],treeVars.L1NonisoIphi[l1nonisocand]);
               
		  std::vector<int> tteta = getECALRegionEta(treeVars.L1NonisoIeta[l1nonisocand]);
		  std::vector<int> ttphi = getECALRegionPhi(treeVars.L1NonisoIphi[l1nonisocand]);
               
		  for(uint i=0;i!=tteta.size();++i){
		    for(uint j=0;j!=ttphi.size();++j){
                     
		      int l1hash=0;
		      if (tteta[i]>0)
                        l1hash= tteta[i] * 100 + ttphi[j] ;
		      else 
                        l1hash = tteta[i] * 100 - ttphi[j] ;
                     
		      if(abs(tteta[i])<18){//EB
			L1MissingTPNonisoEB->Fill(ttphi[j],tteta[i]);
		      }
		      if(tteta[i]>=18){//EE+
			for (uint k=0; k !=geometry[l1hash].size();++k){
			  L1MissingTPNonisoEEPlus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second ) ;
			}
		      }
		      if(tteta[i]<=-18){//EE-
			for (uint k=0; k !=geometry[l1hash].size();++k){
			  L1MissingTPNonisoEEMinus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second ) ;
			}
		      }
		    }
		  }
		}
            
	      else
		{
		  if(MaxTPinNonisoRegion[l1nonisocand] != 255 && SecondTPinNonisoRegion[l1nonisocand] != 255 && treeVars.L1NonisoRank[l1nonisocand] != 63)
		    {
                  
		      std::vector<int> tteta = getECALRegionEta(treeVars.L1NonisoIeta[l1nonisocand]);
		      std::vector<int> ttphi = getECALRegionPhi(treeVars.L1NonisoIphi[l1nonisocand]);
                  
		      for(uint i=0;i!=tteta.size();++i){
			for(uint j=0;j!=ttphi.size();++j){
                        
			  int l1hash=0;
			  if (tteta[i]>0)
			    l1hash= tteta[i] * 100 + ttphi[j] ;
			  else 
			    l1hash = tteta[i] * 100 - ttphi[j] ;
                        
			  if(abs(tteta[i])<18){//EB
			    L1RatioTPNoniso3DEB->Fill(ttphi[j],tteta[i], ratio2);
			    L1TPCompNonisoEB->Fill(ttphi[j],tteta[i]);
			  }
			  if(tteta[i]>=18){//EE+
			    for (uint k=0; k !=geometry[l1hash].size();++k){
			      L1RatioTPNoniso3DEEPlus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second, ratio2 ) ;
			      L1TPCompNonisoEEPlus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second );
			    }
			  }
			  if(tteta[i]<=-18){//EE-
			    for (uint k=0; k !=geometry[l1hash].size();++k){
			      L1RatioTPNoniso3DEEMinus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second, ratio2 ) ;
			      L1TPCompNonisoEEMinus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second );
			    }
			  }
			}
		      }
		    }
		}
	                
	      if(ratio>4.1 || ratio<2.){
               
		L1ValueMismatchNoniso->Fill(treeVars.L1NonisoIeta[l1nonisocand],treeVars.L1NonisoIphi[l1nonisocand]);
               
		std::vector<int> tteta = getECALRegionEta(treeVars.L1NonisoIeta[l1nonisocand]);
		std::vector<int> ttphi = getECALRegionPhi(treeVars.L1NonisoIphi[l1nonisocand]);
               
		for(uint i=0;i!=tteta.size();++i){
                  for(uint j=0;j!=ttphi.size();++j){   
                     
		    int l1hash=0;
		    if (tteta[i]>0)
		      l1hash= tteta[i] * 100 + ttphi[j] ;
		    else 
		      l1hash = tteta[i] * 100 - ttphi[j] ;
                     
		    if(abs(tteta[i])<18){//EB
		      L1ValueMismatchNonisoEB->Fill(ttphi[j],tteta[i]);
		    }
		    if(tteta[i]>=18){//EE+
		      for (uint k=0; k !=geometry[l1hash].size();++k){
			L1ValueMismatchNonisoEEPlus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second ) ;
		      }
		    }
		    if(tteta[i]<=-18){//EE-
		      for (uint k=0; k !=geometry[l1hash].size();++k){
			L1ValueMismatchNonisoEEMinus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second ) ;
		      }
		    }
                  }
		}
	      }
	    }
	}
      
        

    } // end  main loop entries

  





  std::cout<<"\nMax. event number: "<<maxEvNb<<std::endl;
   
  L1FractionMissingTPIsoEB->Divide(L1MissingTPIsoEB, occupancyL1IsoEB);
  L1FractionMissingTPIsoEEPlus->Divide(L1MissingTPIsoEEPlus, occupancyL1IsoEEPlus);
  L1FractionMissingTPIsoEEMinus->Divide(L1MissingTPIsoEEMinus, occupancyL1IsoEEMinus);

  L1FractionValueMismatchIsoEB->Divide(L1ValueMismatchIsoEB, occupancyL1IsoEB);
  L1FractionValueMismatchIsoEEPlus->Divide(L1ValueMismatchIsoEEPlus, occupancyL1IsoEEPlus);
  L1FractionValueMismatchIsoEEMinus->Divide(L1ValueMismatchIsoEEMinus, occupancyL1IsoEEMinus);
    
 
  L1FractionMissingTPNonisoEB->Divide(L1MissingTPNonisoEB, occupancyL1NonisoEB);
  L1FractionMissingTPNonisoEEPlus->Divide(L1MissingTPNonisoEEPlus, occupancyL1NonisoEEPlus);
  L1FractionMissingTPNonisoEEMinus->Divide(L1MissingTPNonisoEEMinus, occupancyL1NonisoEEMinus);
   
   
   
  ///////////////////////
  // Format & write histos
  ///////////////////////
   
   
  // 1. TP Spectrum  
  TProfile2D * TPspectrumMapEB = TPspectrumMap3DEB->Project3DProfile("yx") ;
  TPspectrumMapEB->SetName("TPspectrumMapEB") ;
  TPspectrumMapEB->GetYaxis()->SetTitle("eta index") ; 
  TPspectrumMapEB->GetXaxis()->SetTitle("phi index") ;
  TProfile2D * TPspectrumMapEEPlus = TPspectrumMap3DEEPlus->Project3DProfile("yx") ;
  TPspectrumMapEEPlus->SetName("TPspectrumMapEEPlus") ;
  TPspectrumMapEEPlus->GetYaxis()->SetTitle("y index") ; 
  TPspectrumMapEEPlus->GetXaxis()->SetTitle("x index") ;
  TProfile2D * TPspectrumMapEEMinus = TPspectrumMap3DEEMinus->Project3DProfile("yx") ;
  TPspectrumMapEEMinus->SetName("TPspectrumMapEEMinus") ;
  TPspectrumMapEEMinus->GetYaxis()->SetTitle("y index") ; 
  TPspectrumMapEEMinus->GetXaxis()->SetTitle("x index") ;
 
  //lumisection
  TProfile2D * Lumi2D = LS3D->Project3DProfile("yx") ;
  Lumi2D->SetName("Lumi2D") ;
  Lumi2D->GetYaxis()->SetTitle("eta index") ; 
  Lumi2D->GetXaxis()->SetTitle("phi index") ;
 
  
  // 2. TP Timing
  TH2F * TPMatchEmulEB2D = new TH2F("TPMatchEmulEB2D", "TP data matching Emulator: Barrel", 72, 1, 73, 38, -19, 19) ;
  TPMatchEmulEB2D->GetYaxis()->SetTitle("eta index") ; 
  TPMatchEmulEB2D->GetXaxis()->SetTitle("phi index") ;
  TPMatchEmulEB2D->GetZaxis()->SetRangeUser(-2,6) ;
  TH2F * TPMatchEmulEEPlus2D = new TH2F("TPMatchEmulEEPlus2D", "TP data matching Emulator: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
  TPMatchEmulEEPlus2D->GetYaxis()->SetTitle("y index") ; 
  TPMatchEmulEEPlus2D->GetXaxis()->SetTitle("x index") ;
  TPMatchEmulEEPlus2D->GetZaxis()->SetRangeUser(-2,6) ;
  TH2F * TPMatchEmulEEMinus2D = new TH2F("TPMatchEmulEEMinus2D", "TP data matching Emulator: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
  TPMatchEmulEEMinus2D->GetYaxis()->SetTitle("y index") ; 
  TPMatchEmulEEMinus2D->GetXaxis()->SetTitle("x index") ;
  TPMatchEmulEEMinus2D->GetZaxis()->SetRangeUser(-2,6) ;
  TH2F * TPMatchFractionEB2D = new TH2F("TPMatchFractionEB2D", "TP data: fraction of non-single timing: Barrel", 72, 1, 73, 38, -19, 19) ;
  TPMatchFractionEB2D->GetYaxis()->SetTitle("eta index") ; 
  TPMatchFractionEB2D->GetXaxis()->SetTitle("phi index") ;
  TH2F * TPMatchFractionEEPlus2D = new TH2F("TPMatchFractionEEPlus2D", "TP data: fraction of non-single timing: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
  TPMatchFractionEEPlus2D->GetYaxis()->SetTitle("y index") ; 
  TPMatchFractionEEPlus2D->GetXaxis()->SetTitle("x index") ;
  TH2F * TPMatchFractionEEMinus2D = new TH2F("TPMatchFractionEEMinus2D", "TP data: fraction of non-single timing: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
  TPMatchFractionEEMinus2D->GetYaxis()->SetTitle("y index") ; 
  TPMatchFractionEEMinus2D->GetXaxis()->SetTitle("x index") ;
   
  TH2F * TPMatchFraction2EB2D = new TH2F("TPMatchFraction2EB2D", "TP data: fraction of matching to another BX: Barrel", 72, 1, 73, 38, -19, 19) ;
  TPMatchFraction2EB2D->GetYaxis()->SetTitle("eta index") ; 
  TPMatchFraction2EB2D->GetXaxis()->SetTitle("phi index") ;
  TH2F * TPMatchFraction2EEPlus2D = new TH2F("TPMatchFraction2EEPlus2D", "TP data: fraction of matching to another BX: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
  TPMatchFraction2EEPlus2D->GetYaxis()->SetTitle("y index") ; 
  TPMatchFraction2EEPlus2D->GetXaxis()->SetTitle("x index") ;
  TH2F * TPMatchFraction2EEMinus2D = new TH2F("TPMatchFraction2EEMinus2D", "TP data: fraction of matching to another BX: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
  TPMatchFraction2EEMinus2D->GetYaxis()->SetTitle("y index") ; 
  TPMatchFraction2EEMinus2D->GetXaxis()->SetTitle("x index") ;
   
   
  for (int binx=1 ; binx<=72 ; binx++) {  //looping over iphi
    for (int biny=1 ; biny<=57 ; biny++) { //looping over ieta

      int maxBinEmulz = -1 ;
      double maxEmulCell = TPEmulMax3D->GetBinContent(binx, biny, maxBinEmulz) ;
      double totalEmulCell(0) ;
      for (int binz=1; binz<=7 ; binz++) {
	double content = TPEmulMax3D->GetBinContent(binx, biny, binz) ;
	if (content>maxEmulCell) {
	  maxEmulCell = content ;
	  maxBinEmulz = binz ;
	}
	totalEmulCell += content ;
      }
         
      int maxBinz = 5 ;
      double maxCell = TPMatchEmul3D->GetBinContent(binx, biny, maxBinz) ;
      double totalCell(0) ;
      double totalCell2(0) ;
         
      for (int binz=1; binz<=7 ; binz++) {
	double content = TPMatchEmul3D->GetBinContent(binx, biny, binz) ;
            
	if (content>maxCell) {
	  maxCell = content ;
	  maxBinz = binz ;
	}
	totalCell += content ;
	if(binz>1) {
	  totalCell2 += content ;
	}
      }
      if (maxCell <=0) maxBinz = 2 ; // empty cell

      if(biny<=11){ //minus endcap (ieta <=-18)
	int hashedIndex = (biny-29) * 100 - binx ;
            
	for (uint i=0; i !=geometry[hashedIndex].size();++i) {
	  TPMatchEmulEEMinus2D->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second,float(maxBinz)-2. ) ;
	  TPEmulMapMaxIndexEEMinus->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second,float(maxBinEmulz)-2 ) ;
	}
            
	double fraction = 0 ;
	if (totalCell>0) fraction = 1.- maxCell/totalCell ;
	for (uint i=0; i !=geometry[hashedIndex].size();++i) {
	  TPMatchFractionEEMinus2D->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second,fraction ) ;         
	}
            
	double fraction2 = 0 ;
	if (maxBinz != 1 && totalCell2>0) fraction2 = 1.- maxCell/totalCell2 ;
	for (uint i=0; i !=geometry[hashedIndex].size();++i) {
	  TPMatchFraction2EEMinus2D->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second,fraction2 ) ;       
	}
      }
         
      else if(biny<=46 && biny!=29)
	{ 
	  //barrel (excluding ieta=0)
            
	  TPMatchEmulEB2D->SetBinContent(binx, biny-9, float(maxBinz)-2.) ; //z must be in [-1,5] 
	  TPEmulMapMaxIndexEB->SetBinContent(binx, biny-9,float(maxBinEmulz)-2 ) ;
            
	  double fraction = 0 ;
	  if (totalCell>0) fraction = 1.- maxCell/totalCell ;
	  TPMatchFractionEB2D->SetBinContent(binx, biny-9, fraction) ;
            
	  double fraction2 = 0 ;
	  if (maxBinz != 1 && totalCell2>0) fraction2 = 1.- maxCell/totalCell2 ;
	  TPMatchFraction2EB2D->SetBinContent(binx, biny-9, fraction2 ) ;         
	}
         
      else if(biny>=47)
	{ 
	  //plus endcap (ieta >=18)
	  int hashedIndex = (biny-29) * 100 + binx ;
            
	  for (uint i=0; i !=geometry[hashedIndex].size();++i) {
	    TPMatchEmulEEPlus2D->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second,float(maxBinz)-2. ) ;
	    TPEmulMapMaxIndexEEPlus->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second,float(maxBinEmulz)-2 ) ;
	  }
            
	  double fraction = 0 ;
	  if (totalCell>0) fraction = 1.- maxCell/totalCell ;
	  for (uint i=0; i !=geometry[hashedIndex].size();++i) {
	    TPMatchFractionEEPlus2D->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second,fraction ) ;       
	  }
            
	  double fraction2 = 0 ;
	  if (maxBinz != 1 && totalCell2>0) fraction2 = 1.- maxCell/totalCell2 ;
	  for (uint i=0; i !=geometry[hashedIndex].size();++i) {
	    TPMatchFraction2EEPlus2D->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second,fraction2 ) ;        
	  }
	}
         
         
    }//end loop over ieta
      
  }//end loop over iphi
   
   
   //3. L1/TP ratio
   
  TProfile2D * L1RatioTPIsoEB = L1RatioTPIso3DEB->Project3DProfile("yx") ;
  L1RatioTPIsoEB->SetName("L1RatioTPIsoEB") ;
  L1RatioTPIsoEB->GetYaxis()->SetTitle("eta index") ; 
  L1RatioTPIsoEB->GetXaxis()->SetTitle("phi index") ;
  TProfile2D * L1RatioTPIsoEEPlus = L1RatioTPIso3DEEPlus->Project3DProfile("yx") ;
  L1RatioTPIsoEEPlus->SetName("L1RatioTPIsoEEPlus") ;
  L1RatioTPIsoEEPlus->GetYaxis()->SetTitle("y index") ; 
  L1RatioTPIsoEEPlus->GetXaxis()->SetTitle("x index") ;
  TProfile2D * L1RatioTPIsoEEMinus = L1RatioTPIso3DEEMinus->Project3DProfile("yx") ;
  L1RatioTPIsoEEMinus->SetName("L1RatioTPIsoEEMinus") ;
  L1RatioTPIsoEEMinus->GetYaxis()->SetTitle("y index") ; 
  L1RatioTPIsoEEMinus->GetXaxis()->SetTitle("x index") ;


  TProfile2D * L1RatioTPpreIsoEB = L1RatioTPpreIso3DEB->Project3DProfile("yx") ;
  L1RatioTPpreIsoEB->SetName("L1RatioTPpreIsoEB") ;
  L1RatioTPpreIsoEB->GetYaxis()->SetTitle("eta index") ; 
  L1RatioTPpreIsoEB->GetXaxis()->SetTitle("phi index") ;
  TProfile2D * L1RatioTPpreIsoEEPlus = L1RatioTPpreIso3DEEPlus->Project3DProfile("yx") ;
  L1RatioTPpreIsoEEPlus->SetName("L1RatioTPpreIsoEEPlus") ;
  L1RatioTPpreIsoEEPlus->GetYaxis()->SetTitle("y index") ; 
  L1RatioTPpreIsoEEPlus->GetXaxis()->SetTitle("x index") ;
  TProfile2D * L1RatioTPpreIsoEEMinus = L1RatioTPpreIso3DEEMinus->Project3DProfile("yx") ;
  L1RatioTPpreIsoEEMinus->SetName("L1RatioTPpreIsoEEMinus") ;
  L1RatioTPpreIsoEEMinus->GetYaxis()->SetTitle("y index") ; 
  L1RatioTPpreIsoEEMinus->GetXaxis()->SetTitle("x index") ;


   
  TProfile2D * L1RatioTPNonisoEB = L1RatioTPNoniso3DEB->Project3DProfile("yx") ;
  L1RatioTPNonisoEB->SetName("L1RatioTPNonisoEB") ;
  L1RatioTPNonisoEB->GetYaxis()->SetTitle("eta index") ; 
  L1RatioTPNonisoEB->GetXaxis()->SetTitle("phi index") ;
  TProfile2D * L1RatioTPNonisoEEPlus = L1RatioTPNoniso3DEEPlus->Project3DProfile("yx") ;
  L1RatioTPNonisoEEPlus->SetName("L1RatioTPNonisoEEPlus") ;
  L1RatioTPNonisoEEPlus->GetYaxis()->SetTitle("y index") ; 
  L1RatioTPNonisoEEPlus->GetXaxis()->SetTitle("x index") ;
  TProfile2D * L1RatioTPNonisoEEMinus = L1RatioTPNoniso3DEEMinus->Project3DProfile("yx") ;
  L1RatioTPNonisoEEMinus->SetName("L1RatioTPNonisoEEMinus") ;
  L1RatioTPNonisoEEMinus->GetYaxis()->SetTitle("y index") ; 
  L1RatioTPNonisoEEMinus->GetXaxis()->SetTitle("x index") ;
  //  Lumisection
 

  // TP_emulatedTP_ratio
  TH2F * TP_emulatedTP_ratio_2D_EB = new TH2F("TP_emulatedTP_ratio_2D_EB", "TP/emulatedTP: Barrel", 72, 1, 73, 38, -19, 19) ;
  TP_emulatedTP_ratio_2D_EB->Divide(TP_EB2D,ADC_emulatedTP_EB2D);
  TP_emulatedTP_ratio_2D_EB->SetMinimum(0.1);
  TP_emulatedTP_ratio_2D_EB->SetMaximum(4);
  TP_emulatedTP_ratio_2D_EB->GetYaxis()->SetTitle("eta index") ;
  TP_emulatedTP_ratio_2D_EB->GetXaxis()->SetTitle("phi index") ;

  TH2F * TP_emulatedTP_ratio_2D_EEPlus = new TH2F("TP_emulatedTP_ratio_2D_EEPlus", "TP/emulatedTP: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
  TP_emulatedTP_ratio_2D_EEPlus->Divide(TP_EEPlus2D,ADC_emulatedTP_EEPlus2D);
  TP_emulatedTP_ratio_2D_EEPlus->SetMinimum(0.1);
  TP_emulatedTP_ratio_2D_EEPlus->SetMaximum(4);
  TP_emulatedTP_ratio_2D_EEPlus->GetYaxis()->SetTitle("eta index") ;
  TP_emulatedTP_ratio_2D_EEPlus->GetXaxis()->SetTitle("phi index") ;

  TH2F * TP_emulatedTP_ratio_2D_EEMinus = new TH2F("TP_emulatedTP_ratio_2D_EEMinus", "TP/emulatedTP: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
  TP_emulatedTP_ratio_2D_EEMinus->Divide(TP_EEMinus2D,ADC_emulatedTP_EEMinus2D);
  TP_emulatedTP_ratio_2D_EEMinus->SetMinimum(0.1);
  TP_emulatedTP_ratio_2D_EEMinus->SetMaximum(4);
  TP_emulatedTP_ratio_2D_EEMinus->GetYaxis()->SetTitle("eta index") ;
  TP_emulatedTP_ratio_2D_EEMinus->GetXaxis()->SetTitle("phi index") ;
  


  //new ratio stuff :occupancy
  TH2F* EBoccupancy_ratio=new TH2F("EBoccupancy_ratio","",72,1,73,38,-19,19);

  EBoccupancy_ratio->Divide(occupancyTPEmulEB,occupancyTPEB);
  EBoccupancy_ratio->SetMinimum(0.1);
  EBoccupancy_ratio->SetMaximum(4);
  EBoccupancy_ratio->GetXaxis()->SetTitle("phi index");
  EBoccupancy_ratio->GetYaxis()->SetTitle("eta index");
  EBoccupancy_ratio->SetTitle("TP OccupancyEB RATIO: emul/real");
   
   
  TH2F* EEPlusoccupancy_ratio=new TH2F("EEPlusoccupancy_ratio","", 121, -10, 111, 121, -10, 111) ;

  EEPlusoccupancy_ratio->Divide(occupancyTPEmulEEPlus,occupancyTPEEPlus);
  EEPlusoccupancy_ratio->SetMinimum(0.1);
  EEPlusoccupancy_ratio->SetMaximum(8);
  EEPlusoccupancy_ratio->GetXaxis()->SetTitle("phi index");
  EEPlusoccupancy_ratio->GetYaxis()->SetTitle("eta index");
  EEPlusoccupancy_ratio->SetTitle("TP OccupancyEEPLUS RATIO: emul/real");
   
  TH2F* EEMinusoccupancy_ratio=new TH2F("EEMinusoccupancy_ratio","", 121, -10, 111, 121, -10, 111) ;

  EEMinusoccupancy_ratio->Divide(occupancyTPEmulEEMinus,occupancyTPEEMinus);
  EEMinusoccupancy_ratio->SetMinimum(0.1);
  EEMinusoccupancy_ratio->SetMaximum(8);
  EEMinusoccupancy_ratio->GetXaxis()->SetTitle("phi index");
  EEMinusoccupancy_ratio->GetYaxis()->SetTitle("eta index");
  EEMinusoccupancy_ratio->SetTitle("TP OccupancyEEMINUS RATIO: emul/real");   

  TH1F *TPEmulEB_whenTPRealexists_rebinned=(TH1F*) TPEmulEB_whenTPRealexists->Clone();
  TPEmulEB_whenTPRealexists_rebinned->Rebin(4);
  TH1F *TPEBrebinned=(TH1F*) TPEB->Clone();
  TPEBrebinned->Rebin(4);

  TH1F *TPEmulEEPlus_whenTPRealexists_rebinned=(TH1F*) TPEmulEEPlus_whenTPRealexists->Clone();
  TPEmulEEPlus_whenTPRealexists_rebinned->Rebin(4);
  TH1F *TPEEPlusrebinned=(TH1F*) TPEEPlus->Clone();
  TPEEPlusrebinned->Rebin(4);

  TH1F *TPEmulEEMinus_whenTPRealexists_rebinned=(TH1F*) TPEmulEEMinus_whenTPRealexists->Clone();
  TPEmulEEMinus_whenTPRealexists_rebinned->Rebin(4);
  TH1F *TPEEMinusrebinned=(TH1F*) TPEEMinus->Clone();
  TPEEMinusrebinned->Rebin(4);

  

  TH1F * TPEB_Ratio_when_nonzerorealexists = new TH1F("TPEB_Ratio_when_nonzerorealexists", "Ratio:Emul_{BX0}/Real;when_non-zero_real_exists", 64, 0.0, 256.0) ;
  TPEB_Ratio_when_nonzerorealexists->Divide(TPEmulEB_whenTPRealexists_rebinned,TPEBrebinned);
  TPEB_Ratio_when_nonzerorealexists->GetXaxis()->SetTitle("TP (ADC)") ;
  //  TPEB_Ratio_when_nonzerorealexists->SetMinimum(0.1);
  // TPEB_Ratio_when_nonzerorealexists->SetMaximum(20);
  TPEB_Ratio_when_nonzerorealexists->GetYaxis()->SetRangeUser(0.3,3);


  TH1F * TPEEPlus_Ratio_when_nonzerorealexists = new TH1F("TPEEPlus_Ratio_when_nonzerorealexists", "Ratio:Emul_{BX0}/Real;when_non-zero_real_exists", 64, 0.0, 256.0) ;
  TPEEPlus_Ratio_when_nonzerorealexists->Divide(TPEmulEEPlus_whenTPRealexists_rebinned,TPEEPlusrebinned);
  TPEEPlus_Ratio_when_nonzerorealexists->GetXaxis()->SetTitle("TP (ADC)") ;
  // TPEEPlus_Ratio_when_nonzerorealexists->SetMinimum(0.1);
  // TPEEPlus_Ratio_when_nonzerorealexists->SetMaximum(20);
  TPEEPlus_Ratio_when_nonzerorealexists->GetYaxis()->SetRangeUser(0.3,3);

  TH1F * TPEEMinus_Ratio_when_nonzerorealexists = new TH1F("TPEEMinus_Ratio_when_nonzerorealexists", "Ratio:Emul_{BX0}/Real;when_non-zero_real_exists", 64, 0.0, 256.0) ;
  TPEEMinus_Ratio_when_nonzerorealexists->Divide(TPEmulEEMinus_whenTPRealexists_rebinned,TPEEMinusrebinned);
  TPEEMinus_Ratio_when_nonzerorealexists->GetXaxis()->SetTitle("TP ADC") ;
  // TPEEMinus_Ratio_when_nonzerorealexists->SetMinimum(0.1);
  // TPEEMinus_Ratio_when_nonzerorealexists->SetMaximum(20);
  TPEEMinus_Ratio_when_nonzerorealexists->GetYaxis()->SetRangeUser(0.3,3);






  TFile saving (outputRootName.c_str (),"recreate") ;
  saving.cd () ;
  
   
   
  TPEtaEB->Write() ;
  TPPhiEB->Write() ;
  TPEtaEEPlus->Write() ;
  TPPhiEEPlus->Write() ;
  TPEtaEEMinus->Write() ;
  TPPhiEEMinus->Write() ;
   
  

  occupancyTPEB->Write() ;
  occupancyTPEEPlus->Write() ;
  occupancyTPEEMinus->Write() ;
  occupancyTPEEPlusAll->Write() ;
  occupancyTPEEMinusAll->Write() ;
   
  occupancyTPEmulEB->Write() ;
  occupancyTPEmulEEPlus->Write() ;
  occupancyTPEmulEEPlusALL->Write() ;
  occupancyTPEmulEEMinus->Write() ;
  occupancyTPEmulEEMinusALL->Write() ;
  
  occupancyTPEmulEB_when_no_real_NZ_TP->Write();
  occupancyTPEmulEEPlus_when_no_real_NZ_TP->Write();
  occupancyTPEmulEEMinus_when_no_real_NZ_TP->Write();

  occu_TPvemulatedTP_outliers_EB->Write();
  occu_TPvemulatedTP_outliers_EEPlus->Write();
  occu_TPvemulatedTP_outliers_EEMinus->Write();



  //writing the new stuff barrel
  occupancyTPEBmis->Write();
  TPEtaEBmis->Write();
  TPPhiEBmis->Write();
  //new for endcap plus
  occupancyTPEmulEEPlus_mis->Write();
  TPEmulEtaEEPlus_mis->Write();
  TPEmulPhiEEPlus_mis->Write();
  //new for endcap minus   
  occupancyTPEmulEEMinus_mis->Write();
  TPEmulEtaEEMinus_mis->Write();
  TPEmulPhiEEMinus_mis->Write();
  //new ratio plots
  EBoccupancy_ratio->Write();
  EEMinusoccupancy_ratio->Write();
  EEPlusoccupancy_ratio->Write();

  TPEB_Ratio_when_nonzerorealexists->Write();
  TPEEMinus_Ratio_when_nonzerorealexists->Write();
  TPEEPlus_Ratio_when_nonzerorealexists->Write();

  Ratio_EEPlus_whenTPRealexists->Write();
  Ratio_EEMinus_whenTPRealexists->Write();
  Ratio_EB_whenTPRealexists->Write();


   
  FiredTriggers->Write() ;
   
  //new 
  TPEmulEB_whenTPRealexists->Write();
  TPEmulEEPlus_whenTPRealexists->Write();
  TPEmulEEMinus_whenTPRealexists->Write();
  TPEmulEB_when_no_NZ_TPReal->Write();
  TPEmulEEPlus_when_no_NZ_TPReal->Write();
  TPEmulEEMinus_when_no_NZ_TPReal->Write();



  //from Silvia

  TPEB_fullReadout->Write() ; 
  TP_emulatedTPEnergy_ratio_EB->Write() ; 
  TPEEPlus_fullReadout->Write() ;
  TP_emulatedTPEnergy_ratio_EEPlus->Write() ;
  TPEEMinus_fullReadout->Write() ;
  TP_emulatedTPEnergy_ratio_EEMinus->Write() ;

  TP_vs_emulatedTP_EEMinus->Write();
  TP_vs_emulatedTP_EEPlus->Write();
  TP_vs_emulatedTP_EB->Write();
  
  TP_vs_emulatedTP_EEMinus_18_22->Write();
  TP_vs_emulatedTP_EEMinus_23_27->Write();
  TP_vs_emulatedTP_EEMinus_28_end->Write();

  TP_vs_emulatedTP_EEPlus_18_22->Write();
  TP_vs_emulatedTP_EEPlus_23_27->Write();
  TP_vs_emulatedTP_EEPlus_28_end->Write();
 
  TP_emulatedTP_ratio_2D_EB->Write();
  TP_emulatedTP_ratio_2D_EEPlus->Write();
  TP_emulatedTP_ratio_2D_EEMinus->Write();
  
  TP_emul_ratio_vs_Et_EEPlus->Write();
  TP_emul_ratio_vs_Et_EEMinus->Write();
  TP_emul_ratio_vs_Et_EB->Write();



  

  TPEB_noSpike->Write();
  


  TPSpect_TPvemulatedTP_outliers_EEMinus->Write();
  TPSpect_TPvemulatedTP_outliers_EEPlus->Write();
  TPSpect_TPvemulatedTP_outliers_EB->Write();


  TPEB->Write() ;
  TPEEPlus->Write() ;
  TPEEMinus->Write() ;
  TPEmulEB->Write() ;
  TPEmulEEPlus->Write() ;
  TPEmulEEMinus->Write() ;
  TPEmulMaxEB->Write() ;
  TPEmulMaxEEPlus->Write() ;
  TPEmulMaxEEMinus->Write() ;
  TPspectrumMapEB->Write() ;
  TPspectrumMap3DEB->Write() ;
  TPspectrumMapEEPlus->Write() ;
  TPspectrumMap3DEEPlus->Write() ;
  TPspectrumMapEEMinus->Write() ;
  TPspectrumMap3DEEMinus->Write() ;
  
  TPEtaEEPlusmisSpec->Write();
  TPEtaEEMinusmisSpec->Write();
  TPEtaEBmisSpec->Write();
 
  //L1RatioTPIso
   
  L1RatioTPIsoEB->Write() ;
  L1RatioTPIso3DEB->Write() ;
  L1RatioTPIsoEEPlus->Write() ;
  L1RatioTPIso3DEEPlus->Write() ;
  L1RatioTPIsoEEMinus->Write() ;
  L1RatioTPIso3DEEMinus->Write() ;

  L1RatioTPpreIsoEB->Write() ;
  L1RatioTPpreIso3DEB->Write() ;
  L1RatioTPpreIsoEEPlus->Write() ;
  L1RatioTPpreIso3DEEPlus->Write() ;
  L1RatioTPpreIsoEEMinus->Write() ;
  L1RatioTPpreIso3DEEMinus->Write() ;


   
  L1RatioTPNonisoEB->Write() ;
  L1RatioTPNoniso3DEB->Write() ;
  L1RatioTPNonisoEEPlus->Write() ;
  L1RatioTPNoniso3DEEPlus->Write() ;
  L1RatioTPNonisoEEMinus->Write() ;
  L1RatioTPNoniso3DEEMinus->Write() ;
   
  L1TPCompIsoEB->Write() ;
  L1TPCompNonisoEB->Write() ;
  L1TPCompIsoEEPlus->Write() ;
  L1TPCompNonisoEEPlus->Write() ;
  L1TPCompIsoEEMinus->Write() ;
  L1TPCompNonisoEEMinus->Write() ;


  L1TPComppreIsoEB->Write() ;

  L1TPComppreIsoEEPlus->Write() ;

  L1TPComppreIsoEEMinus->Write() ;

   
  bx_Vs_TPEmul->Write() ;
  bx_Vs_Orbit->Write() ;
  bx_Vs_TP->Write() ;
  bx_Vs_TriggerBit->Write() ;
  bx ->Write();
  occupancyTP_vs_EvtNb->Write();
  iEta_vs_LS->Write();
  iPhi_vs_LS->Write();
  iEta_vs_Time->Write();
  iPhi_vs_Time->Write();
  orbit->Write();
  eventNb->Write();
  LumiSection->Write();
  TimeStamp->Write();
  LS3D->Write();
  time3D->Write();
  triggerBit->Write();
  Lumi2D->Write();
   
  TPMatchEmulEB->Write() ; 
  TPMatchEmulEEPlus->Write() ; 
  TPMatchEmulEEMinus->Write() ; 
  TPMatchEmul3D->Write() ; 
  TPEmulMaxIndexEB->Write() ;
  TPEmulMaxIndexEEPlus->Write() ;
  TPEmulMaxIndexEEMinus->Write() ;
   
  TPCompEmulEB->Write() ; 
  TPCompEmulEEPlus->Write() ; 
  TPCompEmulEEMinus->Write() ;
   
  TPMatchEmulEB2D->Write() ;
  TPMatchEmulEEPlus2D->Write() ;
  TPMatchEmulEEMinus2D->Write() ;
   
  TPMatchFractionEB2D->Write() ;
  TPMatchFractionEEPlus2D->Write() ; 
  TPMatchFractionEEMinus2D->Write() ; 
   
  TPMatchFraction2EB2D->Write() ;
  TPMatchFraction2EEPlus2D->Write() ; 
  TPMatchFraction2EEMinus2D->Write() ; 
   
  ttfMismatchEB->Write() ; 
  ttfMismatchEEPlus->Write() ; 
  ttfMismatchEEMinus->Write() ; 
   
  TPEmulMapMaxIndexEEPlus->Write() ; 
  TPEmulMapMaxIndexEEMinus->Write() ; 
  TPEmulMapMaxIndexEB->Write() ;
  TPEmulMax3D->Write() ;
   
  TPTimingEBFromEmulOK->Write() ; 
  TPTimingEBFromEmulOKAndMatch->Write() ; 
  TPTimingEBFromEmulWrong->Write() ; 
  TPTimingEEMinusFromEmulOK->Write() ; 
  TPTimingEEMinusFromEmulOKAndMatch->Write() ; 
  TPTimingEEMinusFromEmulWrong->Write() ; 
  TPTimingEEPlusFromEmulOK->Write() ; 
  TPTimingEEPlusFromEmulOKAndMatch->Write() ; 
  TPTimingEEPlusFromEmulWrong->Write() ; 
   
  occupancyL1Iso->Write();
  occupancyL1Noniso->Write();
  occupancyL1IsoEB->Write();
  occupancyL1NonisoEB->Write();
  occupancyL1IsoEEPlus->Write();
  occupancyL1IsoEEMinus->Write();
  occupancyL1NonisoEEPlus->Write();
  occupancyL1NonisoEEMinus->Write();
   
  occupancyL1preIso->Write();
  occupancyL1preNoniso->Write();
  occupancyL1preIsoEB->Write();
  occupancyL1preNonisoEB->Write();
  occupancyL1preIsoEEPlus->Write();
  occupancyL1preIsoEEMinus->Write();
  occupancyL1preNonisoEEPlus->Write();
  occupancyL1preNonisoEEMinus->Write();
   
  occupancyL1postIso->Write();
  occupancyL1postNoniso->Write();
  occupancyL1postIsoEB->Write();
  occupancyL1postNonisoEB->Write();
  occupancyL1postIsoEEPlus->Write();
  occupancyL1postIsoEEMinus->Write();
  occupancyL1postNonisoEEPlus->Write();
  occupancyL1postNonisoEEMinus->Write();
  


  ttfstatus_all->Write();
  ttfstatus_vs_LS_all->Write();



  //prefcheck
  ptisopostfiring->Write();
  ptnonisopostfiring->Write();
  ptisoprefiring->Write();
  ptnonisoprefiring->Write();
  ptisoontime->Write();
  ptnonisoontime->Write();


  nbOfL1IsoCands->Write();
  nbOfL1NonisoCands->Write();
  L1IsoCandRank->Write();
  L1NonisoCandRank->Write();
   
  nbOfL1preIsoCands->Write();
  nbOfL1preNonisoCands->Write();
  L1preIsoCandRank->Write();
  L1preNonisoCandRank->Write();
   
  nbOfL1postIsoCands->Write();
  nbOfL1postNonisoCands->Write();
  L1postIsoCandRank->Write();
  L1postNonisoCandRank->Write();
   
  L1Isotiming->Write();
  L1Nonisotiming->Write();
  L1IsotimingEB->Write();
  L1NonisotimingEB->Write();
  L1IsotimingEEPlus->Write();
  L1NonisotimingEEPlus->Write();
  L1IsotimingEEMinus->Write();
  L1NonisotimingEEMinus->Write();
   
  L1IsoRatio->Write();
  L1NonisoRatio->Write();
   
  L1MissingTPIso->Write();
  L1MissingTPNoniso->Write();
  L1MissingTPIsoEB->Write();
  L1MissingTPNonisoEB->Write();
  L1MissingTPIsoEEPlus->Write();
  L1MissingTPIsoEEMinus->Write();
  L1MissingTPNonisoEEPlus->Write();
  L1MissingTPNonisoEEMinus->Write();
   
  L1FractionMissingTPIsoEB->Write();
  L1FractionMissingTPIsoEEPlus->Write();
  L1FractionMissingTPIsoEEMinus->Write();
  L1FractionValueMismatchIsoEB->Write();
  L1FractionValueMismatchIsoEEPlus->Write();
  L1FractionValueMismatchIsoEEMinus->Write();
  

  
  L1FractionMissingTPNonisoEB->Write();
  L1FractionMissingTPNonisoEEPlus->Write();
  L1FractionMissingTPNonisoEEMinus->Write();
   
  L1ValueMismatchIso->Write();
  L1ValueMismatchNoniso->Write();
  L1ValueMismatchIsoEB->Write();
  L1ValueMismatchNonisoEB->Write();
  L1ValueMismatchIsoEEPlus->Write();
  L1ValueMismatchIsoEEMinus->Write();
  L1ValueMismatchNonisoEEPlus->Write();
  L1ValueMismatchNonisoEEMinus->Write();
   
  L1Iso2TPSum->Write();
  L1Noniso2TPSum->Write();
   
  maskedRCT->Write();
  maskedRCTEB->Write();
  maskedRCTEEPlus->Write();
  maskedRCTEEMinus->Write();
   
  MaskedTowersEB->Write();
  MaskedTowersEEPlus->Write();
  MaskedTowersEEMinus->Write();
   
  MaskedReadOutEB->Write();
  MaskedReadOutEEPlus->Write();
  MaskedReadOutEEMinus->Write();
   
  bx_bit45_all->Write() ;
  bx_bit46_all->Write() ;
  bx_nTT->Write() ;
   
  l1EGAlgos->Write() ;
  l1EGAlgos2D->Write() ;
   
  techTrigCor->Write() ;
  techTrigCor2D->Write() ;
  histoEgTrigTechTrigCor->Write() ;
   
  saving.Close () ;
  delete chain ;
   
  return 0 ;
   
}


