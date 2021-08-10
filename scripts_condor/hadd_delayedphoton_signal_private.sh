#!/bin/sh
export X509_USER_PROXY=/storage/af/user/$(whoami)/my_proxy
x509loc=${X509_USER_PROXY}

OUTDIR=/storage/af/user/qnguyen/DelayedPhoton/CMSSW_10_6_12/src/DelayedPhoton/local_storage///store/group/phys_llp/DelayedPhoton/2016/hadd/

if [ ! -d ${OUTDIR} ]
then
    echo "${OUTDIR} does not exist. Creating one..."
    mkdir -p ${OUTDIR}
fi
    
for sample in \
GMSB_L100TeV_Ctau10000cm_13TeV-pythia8 \
GMSB_L150TeV_Ctau10000cm_13TeV-pythia8 \
GMSB_L200TeV_Ctau10000cm_13TeV-pythia8 \
GMSB_L250TeV_Ctau10000cm_13TeV-pythia8 \
GMSB_L300TeV_Ctau10000cm_13TeV-pythia8 \
GMSB_L350TeV_Ctau10000cm_13TeV-pythia8 \
GMSB_L400TeV_Ctau10000cm_13TeV-pythia8 \
#GMSB_L100TeV_Ctau50cm_13TeV-pythia8 \
#GMSB_L150TeV_Ctau50cm_13TeV-pythia8 \
#GMSB_L200TeV_Ctau50cm_13TeV-pythia8 \
#GMSB_L250TeV_Ctau50cm_13TeV-pythia8 \
#GMSB_L300TeV_Ctau50cm_13TeV-pythia8 \
#GMSB_L350TeV_Ctau50cm_13TeV-pythia8 \
#GMSB_L400TeV_Ctau50cm_13TeV-pythia8 \
#GMSB_L100TeV_Ctau100cm_13TeV-pythia8 \
#GMSB_L100TeV_Ctau1cm_13TeV-pythia8 \
#GMSB_L150TeV_Ctau100cm_13TeV-pythia8 \
#GMSB_L150TeV_Ctau1cm_13TeV-pythia8 \
#GMSB_L200TeV_Ctau100cm_13TeV-pythia8 \
#GMSB_L200TeV_Ctau1cm_13TeV-pythia8 \
#GMSB_L250TeV_Ctau100cm_13TeV-pythia8 \
#GMSB_L250TeV_Ctau1cm_13TeV-pythia8 \
#GMSB_L300TeV_Ctau100cm_13TeV-pythia8 \
#GMSB_L300TeV_Ctau1cm_13TeV-pythia8 \
#GMSB_L350TeV_Ctau100cm_13TeV-pythia8 \
#GMSB_L350TeV_Ctau1cm_13TeV-pythia8 \
#GMSB_L400TeV_Ctau100cm_13TeV-pythia8 \
#GMSB_L400TeV_Ctau1cm_13TeV-pythia8 \

do
    correctSample=${sample/L/L-}
    correctSample=${correctSample/Ctau/Ctau-}
    echo "${correctSample}"
    hadd -k -f ${correctSample}.root /storage/af/user/qnguyen/DelayedPhoton/CMSSW_10_6_12/src/DelayedPhoton/local_storage///store/group/phys_llp/DelayedPhoton/2016/jobs/${sample}_Job*.root
    cp ${correctSample}.root ${OUTDIR}/${correctSample}.root
    rm ${correctSample}.root
done
