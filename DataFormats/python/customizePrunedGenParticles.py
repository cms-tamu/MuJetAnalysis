import FWCore.ParameterSet.Config as cms


def customizePrunedGenParticles(process):
    print process
    process.prunedGenParticles.select.extend([
            'keep pdgId = 3000022',
            'keep pdgId = 3000001',
            'keep pdgId = 3000002',
            'keep pdgId = 36'
            ]
    )
    return process
