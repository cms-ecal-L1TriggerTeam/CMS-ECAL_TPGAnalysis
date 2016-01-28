import FWCore.ParameterSet.Config as cms

tpAnalyzer = cms.EDAnalyzer("EcalTPGAnalyzer",

    TPCollection = cms.InputTag("ecalDigis","EcalTriggerPrimitives"),
    TPEmulatorCollection =  cms.InputTag("ecalTriggerPrimitiveDigis",""),
    DigiCollectionEB = cms.InputTag("ecalDigis","ebDigis"),
    DigiCollectionEE = cms.InputTag("ecalDigis","eeDigis"),
    uncalibratedRecHitCollectionEB = cms.InputTag("ecalMaxSampleUncalibRecHit","EcalUncalibRecHitsEB"),
    uncalibratedRecHitCollectionEE = cms.InputTag("ecalMaxSampleUncalibRecHit","EcalUncalibRecHitsEE"),
    GTRecordCollection = cms.string('gtDigis'),
    EcalRecHitCollectionEB = cms.InputTag("ecalRecHit","EcalRecHitsEB"),
    EcalRecHitCollectionEE = cms.InputTag("ecalRecHit","EcalRecHitsEE"),                                                                        

    Print = cms.bool(False),
    L1Print = cms.bool(False),
    ReadTriggerPrimitives = cms.bool(True),

    UseEndCap = cms.bool(True),

    keepOnlyTowersAboveZero = cms.bool(True),
    skipWritingEndcapDigi = cms.bool(True)

)

