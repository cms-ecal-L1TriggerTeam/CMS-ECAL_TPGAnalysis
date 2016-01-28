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


//FAN
using namespace std;


int *unhashTr(int value)
{
   
   /*
   size_t mysize = 5;
   int *coef=new int[mysize];
   //int coef[5]; //FAN
   for (size_t a=0;a<mysize;a++) coef[a] = 0;
   */

   //FAN 
   int *coef=new int[5]; 
   coef[5] = {0};
   

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
   uint bxNb ; //bx means bunch crossing
   uint lumiBlock ;
   ULong64_t orbitNb ; //orbit means Objective Ring Beam Injection and Tracking
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
   float eRec[4032] ;
   int spike[4032] ;
   
   uint nMaskedRCT ;
   int iMaskedRCTeta[100] ;
   int iMaskedRCTphi[100] ;
   int iMaskedRCTcrate[100] ;
 
   //FAN
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
   //FAN   


} ;


//FAN
struct EcalTPGVariablesForIsoNonIso
{
   
   uint nbOfL1Cands ;
   int L1Ieta[4] ;
   int L1Iphi[4] ;
   int L1Rank[4] ; 
   
   uint nbOfL1preCands ;
   int L1preIeta[4] ;
   int L1preIphi[4] ;
   int L1preRank[4] ; 
   
   uint nbOfL1postCands ;
   int L1postIeta[4] ;
   int L1postIphi[4] ;
   int L1postRank[4] ; 
   
} ;
//FAN


// set address for the tree variables //FAN
void setBranchAddresses (TChain * chain, EcalTPGVariables & treeVars)
{
   //chain->SetBranchAddress ("runNb",&treeVars.runNb) ; 
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
   chain->SetBranchAddress ("spike",treeVars.spike) ; 
   
   chain->SetBranchAddress ("nMaskedRCT",&treeVars.nMaskedRCT); //
   chain->SetBranchAddress ("iMaskedRCTeta", treeVars.iMaskedRCTeta);//
   chain->SetBranchAddress ("iMaskedRCTcrate", treeVars.iMaskedRCTcrate);//
   chain->SetBranchAddress ("iMaskedRCTphi", treeVars.iMaskedRCTphi);//
  
/*//FAN 
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
*/
//FAN

}


//FAN
void setBranchAddressesIso (TChain * chain, EcalTPGVariablesForIsoNonIso & treeVars)
{
   chain->SetBranchAddress ("nbOfL1IsoCands",&treeVars.nbOfL1Cands); //
   chain->SetBranchAddress ("L1IsoIeta", treeVars.L1Ieta);//
   chain->SetBranchAddress ("L1IsoIphi", treeVars.L1Iphi);//
   chain->SetBranchAddress ("L1IsoRank", treeVars.L1Rank);//
   
   chain->SetBranchAddress ("nbOfL1preIsoCands",&treeVars.nbOfL1preCands); //
   chain->SetBranchAddress ("L1preIsoIeta", treeVars.L1preIeta);//
   chain->SetBranchAddress ("L1preIsoIphi", treeVars.L1preIphi);//
   chain->SetBranchAddress ("L1preIsoRank", treeVars.L1preRank);//
   
   chain->SetBranchAddress ("nbOfL1postIsoCands",&treeVars.nbOfL1postCands); //
   chain->SetBranchAddress ("L1postIsoIeta", treeVars.L1postIeta);//
   chain->SetBranchAddress ("L1postIsoIphi", treeVars.L1postIphi);//
   chain->SetBranchAddress ("L1postIsoRank", treeVars.L1postRank);//
} 


void setBranchAddressesNonIso (TChain * chain, EcalTPGVariablesForIsoNonIso & treeVars)
{
   
   chain->SetBranchAddress ("nbOfL1NonisoCands",&treeVars.nbOfL1Cands); //
   chain->SetBranchAddress ("L1NonisoIeta", treeVars.L1Ieta);//
   chain->SetBranchAddress ("L1NonisoIphi", treeVars.L1Iphi);//
   chain->SetBranchAddress ("L1NonisoRank", treeVars.L1Rank);//
   
   
   chain->SetBranchAddress ("nbOfL1preNonisoCands",&treeVars.nbOfL1preCands); //
   chain->SetBranchAddress ("L1preNonisoIeta", treeVars.L1preIeta);//
   chain->SetBranchAddress ("L1preNonisoIphi", treeVars.L1preIphi);//
   chain->SetBranchAddress ("L1preNonisoRank", treeVars.L1preRank);//
   
   
   chain->SetBranchAddress ("nbOfL1postNonisoCands",&treeVars.nbOfL1postCands); //
   chain->SetBranchAddress ("L1postNonisoIeta", treeVars.L1postIeta);//
   chain->SetBranchAddress ("L1postNonisoIphi", treeVars.L1postIphi);//
   chain->SetBranchAddress ("L1postNonisoRank", treeVars.L1postRank);//
}
//FAN


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
   cout << "\n Help" << endl ;
   cout << " -h : display help" << endl ;
   cout << " -i <input root files containing the TPG tree>, default=ECALTPGtree.root" << endl ;     
   cout << "    2 possible formats when more than 1 file:" << endl ;
   cout << "    - files names separated by comma without blanks: file1.root,file2.root,file3.root" << endl ;
   cout << "    - files names using the wildcard \":\" file:1:3:.root" << endl ;
   cout << "      with this last format, the loop from file1.root to file3.root is performed (see examples below)" << endl ;
   cout << " -d <directory containing the input root files, default=ignored>" << endl ;     
   cout << " -o <output root file name, default=histoTPG.root>" << endl ;
   cout << " -g <endcap geometry file name, default=none>, default=data/endcapGeometry.root" << endl ;
   cout << " -v <verbosity level(int), default=0 (minimal)>" << endl ;
   cout << " -l1 <L1 algo bits required. If several, use a comma with no blank. Default=select all>" << endl ;
   cout << " -l1bx <L1 algo bits required to fill orbit-bx plots. Default=any>" << endl ;
   cout << " -m <file containing the list of TT to ignore>" << endl ;
   cout << " -th1 <minimal value of TP, TPEmul to fill the occupancy plot, default=3 (TP>3 ADC, i.e. TP>=1 GeV)>" << endl ;
   cout << "\n Example:" << endl ;
   cout << "1) TPGTreeReder -o myfile -l1 16,46 -i file1,file2" << endl ;
   cout << "will produce histo in file myfile, selecting only events triggered "<< endl ;
   cout << "by algo bit 16 and 46 and using as inputs the file1 and file2" << endl ;
   cout << "2) TPGTreeReder -d rfio:/castor/cern.ch/user/p/paganini/67977 -i run67977_:1:18:.root" << endl ;
   cout << "will produce histo in the default file histoTPG.root, selecting all events"<< endl ;
   cout << "and using as inputs the 18 files run67977_1.root to run67977_18.root" << endl ;
   cout << "located in the castor directory /castor/cern.ch/user/p/paganini " << endl ;
   cout << " -SLMinEvt <set upper limit on eventnumber histogram>, default=10^8" << endl ;     
   cout << " -SLMaxEvt <set upper limit on eventnumber histogram>, default=10^8" << endl ;     
   cout << " -SLMinOrb <set upper limit on orbit histogram>, default=10^8" << endl ;     
   cout << " -SLMaxOrb <set upper limit on orbit histogram>, default=10^8" << endl ;     
   cout << " -SLMaxLS <set upper limit on lumi section histogram>, default=1000" << endl ;     
   cout << " -SLMinLS <set lower limit on lumi section histogram>, default=0" << endl ;  
   cout << " -SLMaxTime <set upper limit on time stamp histogram>, default=100" << endl ;     
   cout << " -SLMinTime <set lower limit on time stamp histogram>, default=0" << endl ;     
   cout << " -EG <the trigger energy you want to trig on, e.g. 1, 2, 5, 8, ...>, default=1" << endl ;     
   cout << " -lumi <select lumi sections, e.g. 15,20-25; 15-0 means from 15 to end>, default=all, -1 means all" << endl ;
   cout << " -techtrig <select  technical triggers>, default=all, -1 means all"  << endl ;
   cout << " -goodcoll <trigger selection corresponding to flag 'GOODCOLL'>, default=no, 1 means yes, 0 means no"  << endl ;
   cout << " -firstEntry <first entry in the rootuple to be processed>, default=0" << endl ;
   cout << " -lastEntry <last entry in the rootuple to be processed>, default=all, -1 means all" << endl ;
}



uint getEt(uint val) {return (val&0xff) ;}

uint getFg(uint val) {return ((val&0x100)!=0) ;}

uint getTtf(uint val) {return ((val>>9)&0x7) ;}


//define some functions //FAN
//this is the function to split one string "msg" with the separator "separator", better to look directly how it is used 
vector<string> split(string msg, string separator)
{
   boost::char_separator<char> sep(separator.c_str());
   boost::tokenizer<boost::char_separator<char> > tok(msg, sep );
   vector<string> token ;
   for ( boost::tokenizer<boost::char_separator<char> >::const_iterator i = tok.begin(); i != tok.end(); ++i ) {
      token.push_back(string(*i)) ;
   }
   return token ;
}


//get eta value for the tower, 0.0174 is the crystal cross-section in eta direction, see TDRv1 P147
double getEta(int ietaTower) 
{
   // Paga: to be confirmed, specially in EE:
   return 0.0174*fabs(ietaTower) ;
}


//SM means supermodel,total 36. TT means trigger tower, one trigger tower is 25 crystals in EB, in EE things are much complicated,see webpage: https://twiki.cern.ch/twiki/bin/view/Main/PascalPaganiniTriggerExpertDuties
void getTTnb(int iphi, int ieta, int & SM, int & TT)
{
   if (iphi == 1 || iphi == 2 || iphi == 71 || iphi == 72) {
      SM = 1 ;
      if (iphi<71)
         TT = (iphi-1) + 3 + 4*(abs(ieta)-1) ; //define the trigger towerID 
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


//GCT means Global Calorimeter Trigger, this is to define the GCT ID, it depends on the TT ID. Look for "Glossary" in TDR, you can find all the abbreviations
int getGCTRegionPhi(int ttphi)
{
   int gctphi=0;
   gctphi = (ttphi+1)/4;
   if(ttphi<=2) gctphi=0;
   if(ttphi>=71) gctphi=0;
   
   return gctphi;
}


//not too clear about the difference between the previous one.
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



vector <int> getECALRegionEta2(int crate, int eta)
{
   vector <int> tteta2;
   
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


//define GCT eta ID.
int getGCTRegionEta(int tteta)
{
   int gcteta = 0;
   
   if(tteta>0) gcteta = (tteta-1)/4 + 11;
   else if(tteta<0) gcteta = (tteta+1)/4 + 10;
   
   return gcteta;
}


//seems to get trigger tower phi ID.
vector <int> getECALRegionPhi(int gctphi)
{
   vector <int> ttphi;
   
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


//not too clear about the difference between getECALRegionEta2 
vector <int> getECALRegionEta(int gcteta)
{
   vector <int> tteta;
   
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




