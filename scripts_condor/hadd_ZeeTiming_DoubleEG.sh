#!/bin/sh

export X509_USER_PROXY=/storage/af/user/$(whoami)/my_proxy

#OUTDIR=/storage/cms/store/group/phys_llp/ZeeTiming/2018/hadd/
OUTDIR=/storage/af/user/qnguyen/DelayedPhoton/CMSSW_10_6_12/src/DelayedPhoton/local_storage/store/group/phys_llp/ZeeTiming/2016/hadd/

if [ ! -d ${OUTDIR} ]
then
    echo "${OUTDIR} does not exist. Creating one..."
    mkdir -p ${OUTDIR}
fi

for sample in \
DoubleEG_Run2016B_v2 \
DoubleEG_Run2016C \
DoubleEG_Run2016D \
DoubleEG_Run2016E \
DoubleEG_Run2016F \
DoubleEG_Run2016G \
DoubleEG_Run2016H

do

    #python /storage/af/user/qnguyen/DelayedPhoton/CMSSW_10_6_12/src/DelayedPhoton/scripts_condor/ParHadd.py ${sample}.root "/storage/cms/store/group/phys_susy/razor/Run2Analysis/DelayedPhotonAnalysis/2018_pho_corr/jobs/${sample}_Job*.root"
    root.exe -b -l -q startup.C+
    LD_PRELOAD=/storage/af/user/qnguyen/DelayedPhoton/CMSSW_10_6_12/src/DelayedPhoton/scripts_condor/startup_C.so hadd -f -k ${sample}.root /storage/af/user/qnguyen/DelayedPhoton/CMSSW_10_6_12/src/DelayedPhoton/local_storage/store/group/phys_llp/ZeeTiming/2016/jobs/${sample}_Job*.root
    #eval `scram unsetenv -sh`
    cp ${sample}.root ${OUTDIR}/${sample}.root
	#eval `scram runtime -sh`
    rm ${sample}.root
done

#root.exe -b -l -q startup.C+
#LD_PRELOAD=/storage/af/user/qnguyen/DelayedPhoton/CMSSW_10_6_12/src/DelayedPhoton/scripts_condor/startup_C.so hadd -f -k EGamma_Run2018ABC.root /storage/cms/store/group/phys_llp/ZeeTiming/2018/hadd//EGamma_Run2018A.root /storage/cms/store/group/phys_llp/ZeeTiming/2018/hadd//EGamma_Run2018B.root /storage/cms/store/group/phys_llp/ZeeTiming/2018/hadd/EGamma_Run2018C.root
#
#eval `scram unsetenv -sh`
#gfal-copy -t 4800 -T 4800 -p -f --checksum-mode=both EGamma_Run2018ABC.root gsiftp://transfer-lb.ultralight.org//${OUTDIR}/EGamma_Run2018ABC.root
#eval `scram runtime -sh`
#
#root.exe -b -l -q startup.C+
#LD_PRELOAD=/storage/af/user/qnguyen/DelayedPhoton/CMSSW_10_6_12/src/DelayedPhoton/scripts_condor/startup_C.so hadd -f -k EGamma_Run2018.root /storage/cms//store/group/phys_susy/razor/Run2Analysis/EcalTiming/2021May3/hadd/EGamma_Run2018A.root   /storage/cms//store/group/phys_susy/razor/Run2Analysis/EcalTiming/2021May3/hadd/EGamma_Run2018B.root /storage/cms//store/group/phys_susy/razor/Run2Analysis/EcalTiming/2021May3/hadd/EGamma_Run2018C.root /storage/cms//store/group/phys_susy/razor/Run2Analysis/EcalTiming/2021May3/hadd/EGamma_Run2018D.root
#
#
#eval `scram unsetenv -sh`
#gfal-copy -t 4800 -T 4800 -p -f --checksum-mode=both EGamma_Run2018.root gsiftp://transfer.ultralight.org/${OUTDIR}/EGamma_Run2018.root
#eval `scram runtime -sh`
#rm EGamma_Run2018.root
#


