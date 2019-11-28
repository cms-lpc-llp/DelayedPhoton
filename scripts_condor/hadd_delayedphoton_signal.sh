#!/bin/sh
export X509_USER_PROXY=/storage/user/$(whoami)/my_proxy

OUTDIR=/store/group/phys_susy/razor/Run2Analysis/DelayedPhotonAnalysis/2016/reproduce/hadd/

if [ ! -d ${OUTDIR}]
then
    echo "${OUTDIR} does not exist. Creating one..."
    hadoop fs -mkdir ${OUTDIR}
fi
    
for sample in \
    GMSB_L100TeV_Ctau0_001cm_13TeV-pythia8 \
    GMSB_L100TeV_Ctau0_1cm_13TeV-pythia8 \
    GMSB_L100TeV_Ctau1000cm_13TeV-pythia8 \
    GMSB_L100TeV_Ctau10000cm_13TeV-pythia8 \
    GMSB_L100TeV_Ctau10cm_13TeV-pythia8 \
    GMSB_L100TeV_Ctau1200cm_13TeV-pythia8 \
    GMSB_L100TeV_Ctau200cm_13TeV-pythia8 \
    GMSB_L100TeV_Ctau400cm_13TeV-pythia8 \
    GMSB_L100TeV_Ctau600cm_13TeV-pythia8 \
    GMSB_L100TeV_Ctau800cm_13TeV-pythia8 \
    GMSB_L150TeV_Ctau0_001cm_13TeV-pythia8 \
    GMSB_L150TeV_Ctau0_1cm_13TeV-pythia8 \
    GMSB_L150TeV_Ctau1000cm_13TeV-pythia8 \
    GMSB_L150TeV_Ctau10000cm_13TeV-pythia8 \
    GMSB_L150TeV_Ctau10cm_13TeV-pythia8 \
    GMSB_L150TeV_Ctau1200cm_13TeV-pythia8 \
    GMSB_L150TeV_Ctau200cm_13TeV-pythia8 \
    GMSB_L150TeV_Ctau400cm_13TeV-pythia8 \
    GMSB_L150TeV_Ctau600cm_13TeV-pythia8 \
    GMSB_L150TeV_Ctau800cm_13TeV-pythia8 \
    GMSB_L200TeV_Ctau0_001cm_13TeV-pythia8 \
    GMSB_L200TeV_Ctau0_1cm_13TeV-pythia8 \
    GMSB_L200TeV_Ctau1000cm_13TeV-pythia8 \
    GMSB_L200TeV_Ctau10000cm_13TeV-pythia8 \
    GMSB_L200TeV_Ctau10cm_13TeV-pythia8 \
    GMSB_L200TeV_Ctau1200cm_13TeV-pythia8 \
    GMSB_L200TeV_Ctau200cm_13TeV-pythia8 \
    GMSB_L200TeV_Ctau400cm_13TeV-pythia8 \
    GMSB_L200TeV_Ctau600cm_13TeV-pythia8 \
    GMSB_L200TeV_Ctau800cm_13TeV-pythia8 \
    GMSB_L250TeV_Ctau0_001cm_13TeV-pythia8 \
    GMSB_L250TeV_Ctau0_1cm_13TeV-pythia8 \
    GMSB_L250TeV_Ctau1000cm_13TeV-pythia8 \
    GMSB_L250TeV_Ctau10000cm_13TeV-pythia8 \
    GMSB_L250TeV_Ctau10cm_13TeV-pythia8 \
    GMSB_L250TeV_Ctau1200cm_13TeV-pythia8 \
    GMSB_L250TeV_Ctau200cm_13TeV-pythia8 \
    GMSB_L250TeV_Ctau400cm_13TeV-pythia8 \
    GMSB_L250TeV_Ctau600cm_13TeV-pythia8 \
    GMSB_L250TeV_Ctau800cm_13TeV-pythia8 \
    GMSB_L300TeV_Ctau0_001cm_13TeV-pythia8 \
    GMSB_L300TeV_Ctau0_1cm_13TeV-pythia8 \
    GMSB_L300TeV_Ctau0_1cm_13TeV-pythia8_private \
    GMSB_L300TeV_Ctau1000cm_13TeV-pythia8 \
    GMSB_L300TeV_Ctau10000cm_13TeV-pythia8 \
    GMSB_L300TeV_Ctau10cm_13TeV-pythia8 \
    GMSB_L300TeV_Ctau1200cm_13TeV-pythia8 \
    GMSB_L300TeV_Ctau1200cm_13TeV-pythia8_private \
    GMSB_L300TeV_Ctau200cm_13TeV-pythia8 \
    GMSB_L300TeV_Ctau400cm_13TeV-pythia8 \
    GMSB_L300TeV_Ctau600cm_13TeV-pythia8 \
    GMSB_L300TeV_Ctau800cm_13TeV-pythia8 \
    GMSB_L350TeV_Ctau0_001cm_13TeV-pythia8 \
    GMSB_L350TeV_Ctau0_1cm_13TeV-pythia8 \
    GMSB_L350TeV_Ctau1000cm_13TeV-pythia8 \
    GMSB_L350TeV_Ctau10000cm_13TeV-pythia8 \
    GMSB_L350TeV_Ctau10cm_13TeV-pythia8 \
    GMSB_L350TeV_Ctau1200cm_13TeV-pythia8 \
    GMSB_L350TeV_Ctau200cm_13TeV-pythia8 \
    GMSB_L350TeV_Ctau400cm_13TeV-pythia8 \
    GMSB_L350TeV_Ctau600cm_13TeV-pythia8 \
    GMSB_L350TeV_Ctau800cm_13TeV-pythia8 \
    GMSB_L400TeV_Ctau0_001cm_13TeV-pythia8 \
    GMSB_L400TeV_Ctau0_1cm_13TeV-pythia8 \
    GMSB_L400TeV_Ctau1000cm_13TeV-pythia8 \
    GMSB_L400TeV_Ctau10000cm_13TeV-pythia8 \
    GMSB_L400TeV_Ctau10cm_13TeV-pythia8 \
    GMSB_L400TeV_Ctau1200cm_13TeV-pythia8 \
    GMSB_L400TeV_Ctau200cm_13TeV-pythia8 \
    GMSB_L400TeV_Ctau400cm_13TeV-pythia8 \
    GMSB_L400TeV_Ctau600cm_13TeV-pythia8 \
    GMSB_L400TeV_Ctau800cm_13TeV-pythia8

do

    hadd -k -f /tmp/${sample}.root /mnt/hadoop/store/group/phys_susy/razor/Run2Analysis/DelayedPhotonAnalysis/2016/reproduce/jobs/${sample}_Job*.root
    hadoop fs -put /tmp/${sample}.root ${OUTDIR}
    rm /tmp/${sample}.root
done

