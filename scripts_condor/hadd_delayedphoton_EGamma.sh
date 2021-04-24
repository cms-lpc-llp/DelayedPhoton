#!/bin/sh

export X509_USER_PROXY=/storage/user/$(whoami)/my_proxy

OUTDIR=/store/group/phys_susy/razor/Run2Analysis/DelayedPhotonAnalysis/2018_pho_corr/hadd/

if [ ! -d ${OUTDIR} ]
then
    echo "${OUTDIR} does not exist. Creating one..."
    hadoop fs -mkdir ${OUTDIR}
fi

for sample in \
    EGamma_Run2018A \
    EGamma_Run2018B \
    EGamma_Run2018C \
    EGamma_Run2018D \

do

    python /storage/user/qnguyen/DelayedPhoton/CMSSW_10_6_12/src/DelayedPhoton/scripts_condor/ParHadd.py ${sample}.root "/mnt/hadoop/store/group/phys_susy/razor/Run2Analysis/DelayedPhotonAnalysis/2018_pho_corr/jobs/${sample}_Job*.root"
    eval `scram unsetenv -sh`
    gfal-copy -t 2400 -T 2400 -p -f --checksum-mode=both ${sample}.root gsiftp://transfer.ultralight.org/${OUTDIR}/${sample}.root
	eval `scram runtime -sh`
    rm ${sample}.root
done

