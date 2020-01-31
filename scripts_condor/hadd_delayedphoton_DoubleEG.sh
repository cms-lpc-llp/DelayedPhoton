#!/bin/sh

export X509_USER_PROXY=/storage/user/$(whoami)/my_proxy

OUTDIR=/store/group/phys_susy/razor/Run2Analysis/DelayedPhotonAnalysis/2017/hadd/

if [ ! -d ${OUTDIR} ]
then
    echo "${OUTDIR} does not exist. Creating one..."
    hadoop fs -mkdir ${OUTDIR}
fi

for sample in \
DoubleEG_2017B_31Mar2018 \
DoubleEG_2017D_31Mar2018 \
DoubleEG_2017F_31Mar2018 \
DoubleEG_2017C_31Mar2018 \
DoubleEG_2017E_31Mar2018
do

    hadd -k -f ${sample}.root /mnt/hadoop/store/group/phys_susy/razor/Run2Analysis/DelayedPhotonAnalysis/2017/jobs/${sample}_Job*.root
    hadoop fs -put ${sample}.root ${OUTDIR}
    rm ${sample}.root
done

