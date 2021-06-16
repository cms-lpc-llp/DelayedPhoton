#!/bin/sh
export X509_USER_PROXY=/storage/af/user/$(whoami)/my_proxy

OUTDIR=/store/group/phys_susy/razor/Run2Analysis/DelayedPhotonAnalysis/2017/hadd/

if [ ! -d /storage/cms/${OUTDIR} ]
then
    echo "${OUTDIR} does not exist. Creating one..."
    eval `scram unsetenv -sh`
    gfal-mkdir gsiftp://transfer-lb.ultralight.org//storage/cms/${OUTDIR}
    eval `scram runtime -sh`
fi
    
for sample in \
    ZpToSSTo4Photon_mZp500_ms100_pl1000

do
    hadd -k -f ${sample}.root /storage/cms/store/group/phys_susy/razor/Run2Analysis/DelayedPhotonAnalysis/2017/jobs/${sample}_Job*.root
    eval `scram unsetenv -sh`
    gfal-copy -t 2400 -T 2400 -p -f --checksum-mode=both ${sample}.root gsiftp://transfer-lb.ultralight.org/storage/cms/${OUTDIR}/${sample}.root
	eval `scram runtime -sh`

    rm ${sample}.root
done

