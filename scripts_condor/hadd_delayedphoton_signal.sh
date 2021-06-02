#!/bin/sh
export X509_USER_PROXY=/storage/user/$(whoami)/my_proxy

OUTDIR=/store/group/phys_susy/razor/Run2Analysis/DelayedPhotonAnalysis/2018/hadd/

if [ ! -d /mnt/hadoop/${OUTDIR} ]
then
    echo "${OUTDIR} does not exist. Creating one..."
    hadoop fs -mkdir ${OUTDIR}
fi
    
for sample in \
    GMSB_L-100TeV_Ctau-10000cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-100TeV_Ctau-1000cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-100TeV_Ctau-100cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-100TeV_Ctau-10cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-100TeV_Ctau-1200cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-100TeV_Ctau-200cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-100TeV_Ctau-400cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-100TeV_Ctau-50cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-100TeV_Ctau-600cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-100TeV_Ctau-800cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-150TeV_Ctau-10000cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-150TeV_Ctau-1000cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-150TeV_Ctau-100cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-150TeV_Ctau-10cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-150TeV_Ctau-1200cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-150TeV_Ctau-200cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-150TeV_Ctau-400cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-150TeV_Ctau-50cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-150TeV_Ctau-600cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-150TeV_Ctau-800cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-200TeV_Ctau-10000cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-200TeV_Ctau-1000cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-200TeV_Ctau-100cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-200TeV_Ctau-10cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-200TeV_Ctau-1200cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-200TeV_Ctau-200cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-200TeV_Ctau-400cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-200TeV_Ctau-50cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-200TeV_Ctau-600cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-200TeV_Ctau-800cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-250TeV_Ctau-10000cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-250TeV_Ctau-1000cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-250TeV_Ctau-100cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-250TeV_Ctau-10cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-250TeV_Ctau-1200cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-250TeV_Ctau-200cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-250TeV_Ctau-400cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-250TeV_Ctau-50cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-250TeV_Ctau-600cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-250TeV_Ctau-800cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-300TeV_Ctau-10000cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-300TeV_Ctau-1000cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-300TeV_Ctau-100cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-300TeV_Ctau-10cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-300TeV_Ctau-1200cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-300TeV_Ctau-200cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-300TeV_Ctau-400cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-300TeV_Ctau-50cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-300TeV_Ctau-600cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-300TeV_Ctau-800cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-350TeV_Ctau-10000cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-350TeV_Ctau-1000cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-350TeV_Ctau-100cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-350TeV_Ctau-10cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-350TeV_Ctau-1200cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-350TeV_Ctau-200cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-350TeV_Ctau-400cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-350TeV_Ctau-50cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-350TeV_Ctau-600cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-350TeV_Ctau-800cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-400TeV_Ctau-10000cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-400TeV_Ctau-1000cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-400TeV_Ctau-100cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-400TeV_Ctau-10cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-400TeV_Ctau-1200cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-400TeV_Ctau-200cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-400TeV_Ctau-400cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-400TeV_Ctau-50cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-400TeV_Ctau-600cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-400TeV_Ctau-800cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-450TeV_Ctau-10000cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-450TeV_Ctau-1000cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-450TeV_Ctau-100cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-450TeV_Ctau-10cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-450TeV_Ctau-1200cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-450TeV_Ctau-200cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-450TeV_Ctau-400cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-450TeV_Ctau-50cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-450TeV_Ctau-600cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-450TeV_Ctau-800cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-500TeV_Ctau-10000cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-500TeV_Ctau-1000cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-500TeV_Ctau-100cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-500TeV_Ctau-10cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-500TeV_Ctau-1200cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-500TeV_Ctau-200cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-500TeV_Ctau-400cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-500TeV_Ctau-50cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-500TeV_Ctau-600cm_TuneCP5_13TeV-pythia8 \
    GMSB_L-500TeV_Ctau-800cm_TuneCP5_13TeV-pythia8 \

do
    hadd -k -f ${sample}.root /mnt/hadoop/store/group/phys_susy/razor/Run2Analysis/DelayedPhotonAnalysis/2018/jobs/${sample}_Job*.root
    eval `scram unsetenv -sh`
    gfal-copy -t 2400 -T 2400 -p -f --checksum-mode=both ${sample}.root gsiftp://transfer.ultralight.org/${OUTDIR}/${sample}.root
	eval `scram runtime -sh`

    rm ${sample}.root
done

