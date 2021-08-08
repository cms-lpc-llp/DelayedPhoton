#!/bin/sh
export X509_USER_PROXY=/storage/af/user/$(whoami)/my_proxy

#OUTDIR=/storage/cms/store/group/phys_llp/ZeeTiming/2017/hadd/
OUTDIR=/storage/af/user/qnguyen/DelayedPhoton/CMSSW_10_6_12/src/DelayedPhoton/local_storage/store/group/phys_llp/ZeeTiming/2017/hadd

if [ ! -d ${OUTDIR} ]
then
    echo "${OUTDIR} does not exist. Creating one..."
    mkdir -p ${OUTDIR}
fi

for sample in \
    DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8 \
    #DYJetsToEE_M-50_TuneCP5_13TeV-madgraphMLM-pythia8

do

    #python /storage/af/user/qnguyen/DelayedPhoton/CMSSW_10_6_12/src/DelayedPhoton/scripts_condor/ParHadd.py ${sample}.root "/mnt/hadoop/store/group/phys_susy/razor/Run2Analysis/DelayedPhotonAnalysis/2018_pho_corr/jobs/${sample}_Job*.root"
    root.exe -b -l -q startup.C+
    LD_PRELOAD=/storage/af/user/qnguyen/DelayedPhoton/CMSSW_10_6_12/src/DelayedPhoton/scripts_condor/startup_C.so hadd -f -k ${OUTDIR}/${sample}.root /storage/af/user/qnguyen/DelayedPhoton/CMSSW_10_6_12/src/DelayedPhoton/local_storage/store/group/phys_llp/ZeeTiming/2017/jobs/${sample}_Job*.root
#    eval `scram unsetenv -sh`
#    gfal-copy -t 4800 -T 4800 -p -f --checksum-mode=both ${sample}.root gsiftp://transfer-lb.ultralight.org/${OUTDIR}/${sample}.root
#	eval `scram runtime -sh`
#    rm ${sample}.root
done

