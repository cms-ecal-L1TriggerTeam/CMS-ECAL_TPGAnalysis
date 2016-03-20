#ifndef EcalTPGAnalyzer_h
#define EcalTPGAnalyzer_h
// -*- C++ -*-
//
// Class:      EcalTPGAnalyzer
// 
//
// Original Author:  Pascal Paganini
//

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "Geometry/CaloTopology/interface/EcalTrigTowerConstituentsMap.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include <vector>
#include <string>
#include <TFile.h>
#include <TTree.h>



class CaloSubdetectorGeometry ;
class EcalElectronicsMapping ;

// Auxiliary class
class towerEner {   
 public:
  float eRec_ ;
  int crystNb_ ;
  int tpgEmul_[5] ;
  int tpgEmulFlag_[5] ;
  int tpgEmulsFGVB_[5] ;
  int tpgADC_; 
  int iphi_, ieta_, nbXtal_, spike_ ;
  int twrADC, sFGVB, sevlv_, ttFlag_;
  towerEner()
    : eRec_(0),  crystNb_(0), tpgADC_(0),  
    iphi_(-999), ieta_(-999), nbXtal_(0), spike_(0), twrADC(0), sFGVB(-999), sevlv_(0) , ttFlag_(0)
  { 
    for (int i=0 ; i<5 ; i ++) {
      tpgEmul_[i] = 0 ; 
      tpgEmulFlag_[i]=0;
      tpgEmulsFGVB_[i]=0;
    }
  }
};



class EcalTPGAnalyzer : public edm::EDAnalyzer {
public:
  explicit EcalTPGAnalyzer(const edm::ParameterSet&);
  ~EcalTPGAnalyzer();  
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void beginJob() ;
  virtual void beginRun() ;
  
private:
  struct EcalTPGVariables
  {
    // event variables
    uint runNb ;
    ULong64_t evtNb ;
    uint bxNb ;
    uint bxGT ;	
    ULong64_t orbitNb ;
    uint lumiBlock ;
    double timeStamp ;
    uint nbOfActiveTriggers ;
    int activeTriggers[128] ;
    int activeTriggersBX[128] ;  // all triggers from gt even disabled

    uint nbOfActiveTechTriggers ;
    int activeTechTriggers[64] ;      

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
    int crystNb[4032];
    int sevlv[4032];
    int spike[4032] ;
    int ttFlag[4032];

    uint nbOfL1IsoCands ; //
    int L1IsoIeta[10] ;
    int L1IsoIphi[10] ;
    int L1IsoRank[10] ; 
    uint nbOfL1NonisoCands ; //
    int L1NonisoIeta[10] ;
    int L1NonisoIphi[10] ;
    int L1NonisoRank[10] ;    

    int iMaskedRCTeta[100];
    int iMaskedRCTphi[100];
    int iMaskedRCTcrate[100];
    int nMaskedRCT;   

    uint nbOfL1preIsoCands ; //
    int L1preIsoIeta[10] ;
    int L1preIsoIphi[10] ;
    int L1preIsoRank[10] ; 
    uint nbOfL1preNonisoCands ; //
    int L1preNonisoIeta[10] ;
    int L1preNonisoIphi[10] ;
    int L1preNonisoRank[10] ;  

    uint nbOfL1postIsoCands ; //
    int L1postIsoIeta[10] ;
    int L1postIsoIphi[10] ;
    int L1postIsoRank[10] ; 
    uint nbOfL1postNonisoCands ; //
    int L1postNonisoIeta[10] ;
    int L1postNonisoIphi[10] ;
    int L1postNonisoRank[10] ; 

    int twrADC[4032], sFGVB[4032]; 
  } ;

  struct EcalTPGVariablesShape
  {
     ULong64_t evtNb ;
    int ieta, iphi, ixXtal, iyXtal, TCCid, TowerInTCC, strip ;
    uint nbOfSamples ;
    int samp[10] ;
  } ;

    struct EcalAux
    {
        int iMaskedTTeta[100];
        int iMaskedTTphi[100];
        int nMaskedCh;

        int iMaskedChannelsFromStripsX[500];
        int iMaskedChannelsFromStripsY[500];
        int iMaskedChannelsFromStripsZ[500];
        int nMaskedChannelsFromStrips;
        
        int runNb;

    };
    

private:
  TFile * file_;
  TTree * tree_ ;
  EcalTPGVariables treeVariables_ ;
  TTree * treeShape_ ;
  EcalTPGVariablesShape treeVariablesShape_ ;

  TTree * treeAux ;
  EcalAux ecalAux_;

  edm::InputTag tpCollection_ ;
  edm::InputTag tpEmulatorCollection_ ;
  edm::InputTag digiCollectionEB_ ;
  edm::InputTag digiCollectionEE_ ;
  std::string gtRecordCollectionTag_ ;
  edm::InputTag EcalRecHitCollectionEB_;
  edm::InputTag EcalRecHitCollectionEE_;
  edm::InputTag l1extraIsol_;
  edm::InputTag l1extraNonIsol_;

  //  edm::EDGetTokenT<GTRecordCollection> Token1_;
  edm::EDGetTokenT<EcalTrigPrimDigiCollection> tpCollection1_ ;
  edm::EDGetTokenT<EcalTrigPrimDigiCollection> tpEmulatorCollection1_ ;
  edm::EDGetTokenT<EBDigiCollection> digiCollectionEB1_ ;
  edm::EDGetTokenT<EEDigiCollection> digiCollectionEE1_ ;
  edm::EDGetTokenT<L1GlobalTriggerReadoutRecord> gtRecordCollectionTag1_ ;
  //  edm::EDGetTokenT<l1extra::L1EmParticleCollection.l1extraParticles> l1extraParticles1_ ;
  edm::EDGetTokenT<EcalRecHitCollection> EcalRecHitCollectionEB1_  ;
  edm::EDGetTokenT<EcalRecHitCollection> EcalRecHitCollectionEE1_  ;
  edm::EDGetTokenT<l1extra::L1EmParticleCollection> l1extraIsolT_  ;
  edm::EDGetTokenT<l1extra::L1EmParticleCollection> l1extraNonIsolT_  ;


  bool allowTP_ ;
  bool useEE_ ;
  bool skipWritingEndcapDigis_;
  bool keepOnlyTowersAboveZero_ ;
  bool print_ ;
  bool L1print_ ;
  bool noL1Info;


  const CaloSubdetectorGeometry * theEndcapGeometry_ ;
  const CaloSubdetectorGeometry * theBarrelGeometry_ ;
  edm::ESHandle<EcalTrigTowerConstituentsMap> eTTmap_;
  const EcalElectronicsMapping * theMapping_ ;

  ULong64_t myevt;  

};

#endif
