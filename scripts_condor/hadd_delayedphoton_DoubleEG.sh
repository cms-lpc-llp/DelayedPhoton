#!/bin/sh

export X509_USER_PROXY=/storage/af/user/$(whoami)/my_proxy

OUTDIR=/storage/cms/store/group/phys_llp/DelayedPhoton/2016/hadd/

if [ ! -d ${OUTDIR} ]
then
    echo "${OUTDIR} does not exist. Creating one..."
    eval `scram unsetenv -sh`
    gfal-mkdir gsiftp://transfer-lb.ultralight.org//storage/cms/${outputDirectory}
    eval `scram runtime -sh`
fi

root.exe -b -l -q startup.C+

for sample in \
DoubleEG_Run2016B_v2 \
DoubleEG_Run2016C \
DoubleEG_Run2016D \
DoubleEG_Run2016E \
DoubleEG_Run2016F \
DoubleEG_Run2016G \
DoubleEG_Run2016H

do

    LD_PRELOAD=/storage/af/user/qnguyen/DelayedPhoton/CMSSW_10_6_12/src/DelayedPhoton/scripts_condor/startup_C.so hadd -k -f ${sample}.root /storage/cms/store/group/phys_llp/DelayedPhoton/2016/jobs/${sample}_Job*.root
    eval `scram unsetenv -sh`
    gfal-copy -t 4800 -T 4800 -p -f --checksum-mode=both ${sample}.root gsiftp://transfer-lb.ultralight.org/${OUTDIR}/${sample}.root
    eval `scram runtime -sh`
    rm ${sample}.root
done

