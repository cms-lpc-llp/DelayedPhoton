#!/bin/sh

export X509_USER_PROXY=/storage/user/$(whoami)/my_proxy

OUTDIR=/store/group/phys_susy/razor/Run2Analysis/DelayedPhotonAnalysis/2018_pho_corr/hadd/

if [ ! -d ${OUTDIR} ]
then
    echo "${OUTDIR} does not exist. Creating one..."
    hadoop fs -mkdir ${OUTDIR}
fi

for sample in \
    EGamma_Run2018D \
    EGamma_Run2018A \
    EGamma_Run2018B \
    EGamma_Run2018C \

do

    #python /storage/user/qnguyen/DelayedPhoton/CMSSW_10_6_12/src/DelayedPhoton/scripts_condor/ParHadd.py ${sample}.root "/mnt/hadoop/store/group/phys_susy/razor/Run2Analysis/DelayedPhotonAnalysis/2018_pho_corr/jobs/${sample}_Job*.root"
    root.exe -b -l -q startup.C+
    LD_PRELOAD=/storage/user/qnguyen/DelayedPhoton/CMSSW_10_6_12/src/DelayedPhoton/scripts_condor/startup_C.so hadd -f -k ${sample}.root /mnt/hadoop/store/group/phys_susy/razor/Run2Analysis/DelayedPhotonAnalysis/2018_pho_corr/jobs/${sample}_Job*.root
    eval `scram unsetenv -sh`
    gfal-copy -t 4800 -T 4800 -p -f --checksum-mode=both ${sample}.root gsiftp://transfer.ultralight.org/${OUTDIR}/${sample}.root
	eval `scram runtime -sh`
    rm ${sample}.root
done

