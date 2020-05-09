#!/bin/sh

export X509_USER_PROXY=/storage/user/$(whoami)/my_proxy

OUTDIR=/store/group/phys_susy/razor/Run2Analysis/DelayedPhotonAnalysis/2016/legacy/hadd/

if [ ! -d /mnt/hadoop/${OUTDIR} ]
then
    echo "${OUTDIR} does not exist. Creating one..."
    hadoop fs -mkdir ${OUTDIR}
fi

for sample in \
SinglePhoton_Run2016B_v2 \
SinglePhoton_Run2016C \
SinglePhoton_Run2016D \
SinglePhoton_Run2016E \
SinglePhoton_Run2016F \
SinglePhoton_Run2016G \
SinglePhoton_Run2016H

do

    hadd -k -f ${sample}.root /mnt/hadoop/store/group/phys_susy/razor/Run2Analysis/DelayedPhotonAnalysis/2016/legacy/jobs/${sample}_Job*.root
    hadoop fs -put -f ${sample}.root ${OUTDIR}
    rm ${sample}.root
done

