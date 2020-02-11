#!/bin/sh

export X509_USER_PROXY=/storage/user/$(whoami)/my_proxy

OUTDIR=/store/group/phys_susy/razor/Run2Analysis/DelayedPhotonAnalysis/2017/hadd/

if [ ! -d ${OUTDIR} ]
then
    echo "${OUTDIR} does not exist. Creating one..."
    hadoop fs -mkdir ${OUTDIR}
fi

for sample in \
SinglePhoton_Run2017B_31Mar2018 \
SinglePhoton_Run2017D_31Mar2018 \
SinglePhoton_Run2017F_31Mar2018 \
SinglePhoton_Run2017C_31Mar2018 \
SinglePhoton_Run2017E_31Mar2018
do

    hadd -k -f ${sample}.root /mnt/hadoop/store/group/phys_susy/razor/Run2Analysis/DelayedPhotonAnalysis/2017/jobs/${sample}_Job*.root
    eval `scram unsetenv -sh`
    gfal-copy -t 2400 -T 2400 -p -f --checksum-mode=both ${sample}.root gsiftp://transfer.ultralight.org/${OUTDIR}/${sample}.root
	eval `scram runtime -sh`
    rm ${sample}.root
done

