#!/bin/sh
export X509_USER_PROXY=/storage/af/user/$(whoami)/my_proxy
x509loc=${X509_USER_PROXY}

OUTDIR=/storage/cms/store/group/phys_llp/DelayedPhoton/2016/hadd/

if [ ! -d ${OUTDIR} ]
then
    echo "${OUTDIR} does not exist. Creating one..."
    eval `scram unsetenv -sh`
    gfal-mkdir gsiftp://transfer-lb.ultralight.org/${OUTDIR}
	eval `scram runtime -sh`
fi
    
for sample in \
GMSB_L100TeV_Ctau50cm_13TeV-pythia8 \
GMSB_L150TeV_Ctau50cm_13TeV-pythia8 \
GMSB_L200TeV_Ctau50cm_13TeV-pythia8 \
GMSB_L250TeV_Ctau50cm_13TeV-pythia8 \
GMSB_L300TeV_Ctau50cm_13TeV-pythia8 \
GMSB_L350TeV_Ctau50cm_13TeV-pythia8 \
GMSB_L400TeV_Ctau50cm_13TeV-pythia8 \
GMSB_L100TeV_Ctau10000cm_13TeV-pythia8 \
GMSB_L100TeV_Ctau100cm_13TeV-pythia8 \
GMSB_L100TeV_Ctau1cm_13TeV-pythia8 \
GMSB_L150TeV_Ctau10000cm_13TeV-pythia8 \
GMSB_L150TeV_Ctau100cm_13TeV-pythia8 \
GMSB_L150TeV_Ctau1cm_13TeV-pythia8 \
GMSB_L200TeV_Ctau10000cm_13TeV-pythia8 \
GMSB_L200TeV_Ctau100cm_13TeV-pythia8 \
GMSB_L200TeV_Ctau1cm_13TeV-pythia8 \
GMSB_L250TeV_Ctau10000cm_13TeV-pythia8 \
GMSB_L250TeV_Ctau100cm_13TeV-pythia8 \
GMSB_L250TeV_Ctau1cm_13TeV-pythia8 \
GMSB_L300TeV_Ctau10000cm_13TeV-pythia8 \
GMSB_L300TeV_Ctau100cm_13TeV-pythia8 \
GMSB_L300TeV_Ctau1cm_13TeV-pythia8 \
GMSB_L350TeV_Ctau10000cm_13TeV-pythia8 \
GMSB_L350TeV_Ctau100cm_13TeV-pythia8 \
GMSB_L350TeV_Ctau1cm_13TeV-pythia8 \
GMSB_L400TeV_Ctau10000cm_13TeV-pythia8 \
GMSB_L400TeV_Ctau100cm_13TeV-pythia8 \
GMSB_L400TeV_Ctau1cm_13TeV-pythia8 \

do
    correctSample=${sample/L/L-}
    correctSample=${correctSample/Ctau/Ctau-}
    echo "${correctSample}"
    hadd -k -f ${correctSample}.root /storage/cms/store/group/phys_llp/DelayedPhoton/2016/jobs/${sample}_Job*.root
    env -i X509_USER_PROXY=${x509loc} gfal-copy -t 2400 -T 2400 -p -f --checksum-mode=both ${correctSample}.root gsiftp://transfer-lb.ultralight.org/${OUTDIR}
    rm ${correctSample}.root
done
