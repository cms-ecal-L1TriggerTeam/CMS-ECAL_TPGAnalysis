
import FWCore.ParameterSet.Config as cms

process = cms.Process("TPGANALYSIS")

process.load("SimCalorimetry.EcalTrigPrimProducers.ecalTriggerPrimitiveDigis_readDBOffline_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.prefer("GlobalTag")
process.GlobalTag.globaltag = 'GR_P_V14::All'

# Trigger ###
process.load("L1TriggerConfig.L1GtConfigProducers.L1GtConfig_cff")
process.load("L1TriggerConfig.L1GtConfigProducers.Luminosity.startup.L1Menu_startup_v3_Unprescaled_cff")
process.load("L1TriggerConfig.L1GtConfigProducers.L1GtBoardMapsConfig_cff")
process.load("L1TriggerConfig.L1ScalesProducers.L1MuTriggerScalesConfig_cff")
process.load("L1TriggerConfig.L1ScalesProducers.L1MuTriggerPtScaleConfig_cff")
import FWCore.Modules.printContent_cfi
process.dumpEv = FWCore.Modules.printContent_cfi.printContent.clone()
import EventFilter.L1GlobalTriggerRawToDigi.l1GtUnpack_cfi
process.gtDigis = EventFilter.L1GlobalTriggerRawToDigi.l1GtUnpack_cfi.l1GtUnpack.clone()
process.gtDigis.DaqGtInputTag = 'source'
 
# ECAL Unpacker ###
process.load("EventFilter.EcalRawToDigi.EcalUnpackerMapping_cfi")
process.load("EventFilter.EcalRawToDigi.EcalUnpackerData_cfi")

# ECAL TPG Producer ###
process.load("Geometry.EcalMapping.EcalMapping_cfi")
process.load("Geometry.EcalMapping.EcalMappingRecord_cfi")


# commented by Dima: process.load("CalibCalorimetry.Configuration.Ecal_FakeConditions_cff")

# ECAL TPG Analyzer ###
process.load("Geometry.CaloEventSetup.CaloGeometry_cfi")
process.load("Geometry.CaloEventSetup.EcalTrigTowerConstituents_cfi")
process.load("Geometry.CMSCommonData.cmsIdealGeometryXML_cfi")

process.ecalTriggerPrimitiveDigis = cms.EDProducer("EcalTrigPrimProducer",
    InstanceEB = cms.string('ebDigis'),
    InstanceEE = cms.string('eeDigis'),
    Label = cms.string('ecalDigis'),

    BarrelOnly = cms.bool(False),
    Famos = cms.bool(False),
    TcpOutput = cms.bool(False),

    Debug = cms.bool(False),

    binOfMaximum = cms.int32(6), ## optional from release 200 on, from 1-10
                                                   
#    TTFHighEnergyEB = cms.double(1.0),
#    TTFHighEnergyEE = cms.double(1.0),
#    TTFLowEnergyEB = cms.double(1.0), ## this + the following is added from 140_pre4 on
#    TTFLowEnergyEE = cms.double(1.0)
)


# ECAL rechits and co
process.load("Configuration/StandardSequences/Reconstruction_cff")
import RecoLocalCalo.EcalRecProducers.ecalGlobalUncalibRecHit_cfi
process.ecalUncalibHit = RecoLocalCalo.EcalRecProducers.ecalGlobalUncalibRecHit_cfi.ecalGlobalUncalibRecHit.clone()
process.load("RecoLocalCalo.EcalRecProducers.ecalRecHit_cfi")
process.load("Geometry.CaloEventSetup.CaloTopology_cfi")
process.load("RecoLocalCalo.EcalRecProducers.ecalDetIdToBeRecovered_cfi")
process.ecalRecHit.EBuncalibRecHitCollection = 'ecalUncalibHit:EcalUncalibRecHitsEB'
process.ecalRecHit.EEuncalibRecHitCollection = 'ecalUncalibHit:EcalUncalibRecHitsEE'



process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
fileNames = (cms.untracked.vstring('/store/data/Run2011A/MinimumBias/RAW/v1/000/163/369/2EFC4AA0-B26E-E011-9A3A-000423D94E70.root'))
)

process.out = cms.OutputModule("PoolOutputModule",
                               outputCommands = cms.untracked.vstring("keep *"),
                               fileName = cms.untracked.string( 'reco.root' )
                               )



ecalTriggerPrimitiveDigis = cms.EDProducer("EcalTrigPrimProducer",
    InstanceEB = cms.string('ebDigis'),
    InstanceEE = cms.string('eeDigis'),
    Label = cms.string('ecalDigis'),

    BarrelOnly = cms.bool(False),
    Famos = cms.bool(False),
    TcpOutput = cms.bool(False),

    Debug = cms.bool(False),

    binOfMaximum = cms.int32(6), ## optional from release 200 on, from 1-10
                                                   
#    TTFHighEnergyEB = cms.double(1.0),
#    TTFHighEnergyEE = cms.double(1.0),
#    TTFLowEnergyEB = cms.double(1.0), ## this + the following is added from 140_pre4 on
#    TTFLowEnergyEE = cms.double(1.0)
)



process.load("EcalPFG.TriggerAnalysis.EcalTPGAnalyzer_cfi")



process.load("Configuration.StandardSequences.RawToDigi_Data_cff")
process.load("Configuration.StandardSequences.L1Reco_cff")
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)


process.p = cms.Path(process.gtDigis*process.RawToDigi*process.L1Reco*process.ecalTriggerPrimitiveDigis*process.ecalUncalibHit*process.ecalDetIdToBeRecovered*process.ecalRecHit*process.tpAnalyzer)


process.MessageLogger = cms.Service("MessageLogger",
    cout = cms.untracked.PSet(threshold = cms.untracked.string('ERROR')),
    destinations = cms.untracked.vstring('cout')
)

