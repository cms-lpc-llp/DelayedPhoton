#!/bin/sh
export X509_USER_PROXY=/storage/user/$(whoami)/my_proxy

OUTDIR=/store/group/phys_susy/razor/Run2Analysis/DelayedPhotonAnalysis/2017/hadd/

if [ ! -d /mnt/hadoop/${OUTDIR} ]
then
    echo "${OUTDIR} does not exist. Creating one..."
    hadoop fs -mkdir ${OUTDIR}
fi
    
for sample in \
    GMSB_L100TeV_Ctau100cm_13TeV-pythia8 \
    GMSB_L100TeV_Ctau1cm_13TeV-pythia8 \
    GMSB_L100TeV_Ctau50cm_13TeV-pythia8 \
    GMSB_L150TeV_Ctau100cm_13TeV-pythia8 \
    GMSB_L150TeV_Ctau1cm_13TeV-pythia8 \
    GMSB_L150TeV_Ctau50cm_13TeV-pythia8 \
    GMSB_L200TeV_Ctau100cm_13TeV-pythia8 \
    GMSB_L200TeV_Ctau1cm_13TeV-pythia8 \
    GMSB_L200TeV_Ctau50cm_13TeV-pythia8 \
    GMSB_L250TeV_Ctau100cm_13TeV-pythia8 \
    GMSB_L250TeV_Ctau1cm_13TeV-pythia8 \
    GMSB_L250TeV_Ctau50cm_13TeV-pythia8 \
    GMSB_L300TeV_Ctau100cm_13TeV-pythia8 \
    GMSB_L300TeV_Ctau1cm_13TeV-pythia8 \
    GMSB_L300TeV_Ctau50cm_13TeV-pythia8 \
    GMSB_L350TeV_Ctau100cm_13TeV-pythia8 \
    GMSB_L350TeV_Ctau1cm_13TeV-pythia8 \
    GMSB_L350TeV_Ctau50cm_13TeV-pythia8 \
    GMSB_L400TeV_Ctau100cm_13TeV-pythia8 \
    GMSB_L400TeV_Ctau1cm_13TeV-pythia8 \
    GMSB_L400TeV_Ctau50cm_13TeV-pythia8

do
    correctSample=${sample/L/L-}
    correctSample=${correctSample/Ctau/Ctau-}
    echo "${correctSample}"
    hadd -k -f ${correctSample}.root /mnt/hadoop/store/group/phys_susy/razor/Run2Analysis/DelayedPhotonAnalysis/2017/jobs/${sample}_Job*.root
    eval `scram unsetenv -sh`
    gfal-copy -t 2400 -T 2400 -p -f --checksum-mode=both ${correctSample}.root gsiftp://transfer.ultralight.org/${OUTDIR}/${correctSample}.root
	eval `scram runtime -sh`

    rm ${correctSample}.root
done
