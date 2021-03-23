#!/bin/sh
export X509_USER_PROXY=/storage/user/$(whoami)/my_proxy

OUTDIR=/store/group/phys_susy/razor/Run2Analysis/DelayedPhotonAnalysis/2017/hadd/

if [ ! -d /mnt/hadoop/${OUTDIR} ]
then
    echo "${OUTDIR} does not exist. Creating one..."
    hadoop fs -mkdir ${OUTDIR}
fi
    
for sample in \
    QCD_Pt-120to170_EMEnriched_TuneCP5_13TeV_pythia8 \
    QCD_Pt-15to20_EMEnriched_TuneCP5_13TeV_pythia8 \
    QCD_Pt-170to300_EMEnriched_TuneCP5_13TeV_pythia8 \
    QCD_Pt-20to30_EMEnriched_TuneCP5_13TeV_pythia8 \
    QCD_Pt-300toInf_EMEnriched_TuneCP5_13TeV_pythia8 \
    QCD_Pt-30to50_EMEnriched_TuneCP5_13TeV_pythia8 \
    QCD_Pt-50to80_EMEnriched_TuneCP5_13TeV_pythia8 \
    QCD_Pt-80to120_EMEnriched_TuneCP5_13TeV_pythia8 \
    GJets_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8 \
    GJets_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8 \
    GJets_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8 \
    GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8 \
    GJets_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8 \
    DiPhotonJetsBox_M40_80-Sherpa \
    DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa \
#    QCD_Pt-30to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8 \
#    QCD_Pt-30toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8 \
#    QCD_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8 \
do
    hadd -k -f ${sample}.root /mnt/hadoop/store/group/phys_susy/razor/Run2Analysis/DelayedPhotonAnalysis/2017/jobs/${sample}_Job*.root
    eval `scram unsetenv -sh`
    gfal-copy -t 2400 -T 2400 -p -f --checksum-mode=both ${sample}.root gsiftp://transfer.ultralight.org/${OUTDIR}/${sample}.root
	eval `scram runtime -sh`

    rm ${sample}.root
done

