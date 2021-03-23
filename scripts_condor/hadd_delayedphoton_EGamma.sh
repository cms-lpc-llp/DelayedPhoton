#!/bin/sh

export X509_USER_PROXY=/storage/user/$(whoami)/my_proxy

OUTDIR=/store/group/phys_susy/razor/Run2Analysis/DelayedPhotonAnalysis/2018/hadd/

if [ ! -d ${OUTDIR} ]
then
    echo "${OUTDIR} does not exist. Creating one..."
    hadoop fs -mkdir ${OUTDIR}
fi

for sample in \
    EGamma_Run2018A \
    EGamma_Run2018B \
    EGamma_Run2018C \
    EGamma_Run2018D_v2 \

do

    hadd -k -f ${sample}.root /mnt/hadoop/store/group/phys_susy/razor/Run2Analysis/DelayedPhotonAnalysis/2018/jobs/${sample}_Job*.root
    eval `scram unsetenv -sh`
    gfal-copy -t 2400 -T 2400 -p -f --checksum-mode=both ${sample}.root gsiftp://transfer.ultralight.org/${OUTDIR}/${sample}.root
	eval `scram runtime -sh`
    rm ${sample}.root
done

