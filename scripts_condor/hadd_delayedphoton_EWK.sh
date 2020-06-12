#!/bin/sh
export X509_USER_PROXY=/storage/user/$(whoami)/my_proxy

OUTDIR=/store/group/phys_susy/razor/Run2Analysis/DelayedPhotonAnalysis/2016/legacy/hadd/

if [ ! -d /mnt/hadoop/${OUTDIR} ]
then
    echo "${OUTDIR} does not exist. Creating one..."
    hadoop fs -mkdir ${OUTDIR}
fi
    
for sample in \
DiPhotonJetsBox_M40_80-Sherpa \
DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa \
TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8 \
TGGJets_leptonDecays_13TeV_MadGraph_madspin_pythia8 \
TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8 \
ZGGJets_ZToHadOrNu_5f_LO_madgraph_pythia8 \
WZG_TuneCUETP8M1_13TeV-amcatnlo-pythia8 \
WGGJets_TuneCUETP8M1_13TeV_madgraphMLM_pythia8 \
WWG_TuneCUETP8M1_13TeV-amcatnlo-pythia8  \
TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8 \
WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8  \
WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8  \
WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 \
WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 \
WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 \
WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 \
WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 \
WJetsToLNu_HT-70To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 


do

    hadd -k -f ${sample}.root /mnt/hadoop/store/group/phys_susy/razor/Run2Analysis/DelayedPhotonAnalysis/2016/legacy/jobs/${sample}_Job*.root
    eval `scram unsetenv -sh`
    gfal-copy -t 2400 -T 2400 -p -f --checksum-mode=both ${sample}.root gsiftp://transfer.ultralight.org//${OUTDIR}
    eval `scram runtime -sh`
    rm ${sample}.root
done

