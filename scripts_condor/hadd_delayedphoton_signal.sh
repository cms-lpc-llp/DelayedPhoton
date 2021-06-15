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
GMSB_L-100TeV_Ctau-1000cm_13TeV-pythia8 \
GMSB_L-100TeV_Ctau-10cm_13TeV-pythia8 \
GMSB_L-100TeV_Ctau-1200cm_13TeV-pythia8 \
GMSB_L-100TeV_Ctau-200cm_13TeV-pythia8 \
GMSB_L-100TeV_Ctau-400cm_13TeV-pythia8 \
GMSB_L-100TeV_Ctau-600cm_13TeV-pythia8 \
GMSB_L-150TeV_Ctau-1000cm_13TeV-pythia8 \
GMSB_L-150TeV_Ctau-10cm_13TeV-pythia8 \
GMSB_L-150TeV_Ctau-1200cm_13TeV-pythia8 \
GMSB_L-150TeV_Ctau-200cm_13TeV-pythia8 \
GMSB_L-150TeV_Ctau-400cm_13TeV-pythia8 \
GMSB_L-150TeV_Ctau-600cm_13TeV-pythia8 \
GMSB_L-150TeV_Ctau-800cm_13TeV-pythia8 \
GMSB_L-200TeV_Ctau-1000cm_13TeV-pythia8 \
GMSB_L-200TeV_Ctau-10cm_13TeV-pythia8 \
GMSB_L-200TeV_Ctau-1200cm_13TeV-pythia8 \
GMSB_L-200TeV_Ctau-200cm_13TeV-pythia8 \
GMSB_L-200TeV_Ctau-400cm_13TeV-pythia8 \
GMSB_L-200TeV_Ctau-600cm_13TeV-pythia8 \
GMSB_L-200TeV_Ctau-800cm_13TeV-pythia8 \
GMSB_L-250TeV_Ctau-1000cm_13TeV-pythia8 \
GMSB_L-250TeV_Ctau-10cm_13TeV-pythia8 \
GMSB_L-250TeV_Ctau-1200cm_13TeV-pythia8 \
GMSB_L-250TeV_Ctau-200cm_13TeV-pythia8 \
GMSB_L-250TeV_Ctau-400cm_13TeV-pythia8 \
GMSB_L-250TeV_Ctau-600cm_13TeV-pythia8 \
GMSB_L-250TeV_Ctau-800cm_13TeV-pythia8 \
GMSB_L-300TeV_Ctau-1000cm_13TeV-pythia8 \
GMSB_L-300TeV_Ctau-10cm_13TeV-pythia8 \
GMSB_L-300TeV_Ctau-1200cm_13TeV-pythia8 \
GMSB_L-300TeV_Ctau-200cm_13TeV-pythia8 \
GMSB_L-300TeV_Ctau-400cm_13TeV-pythia8 \
GMSB_L-300TeV_Ctau-600cm_13TeV-pythia8 \
GMSB_L-300TeV_Ctau-800cm_13TeV-pythia8 \
GMSB_L-350TeV_Ctau-1000cm_13TeV-pythia8 \
GMSB_L-350TeV_Ctau-10cm_13TeV-pythia8 \
GMSB_L-350TeV_Ctau-1200cm_13TeV-pythia8 \
GMSB_L-350TeV_Ctau-200cm_13TeV-pythia8 \
GMSB_L-350TeV_Ctau-400cm_13TeV-pythia8 \
GMSB_L-350TeV_Ctau-600cm_13TeV-pythia8 \
GMSB_L-350TeV_Ctau-800cm_13TeV-pythia8 \
GMSB_L-400TeV_Ctau-1000cm_13TeV-pythia8 \
GMSB_L-400TeV_Ctau-10cm_13TeV-pythia8 \
GMSB_L-400TeV_Ctau-1200cm_13TeV-pythia8 \
GMSB_L-400TeV_Ctau-200cm_13TeV-pythia8 \
GMSB_L-400TeV_Ctau-400cm_13TeV-pythia8 \
GMSB_L-400TeV_Ctau-600cm_13TeV-pythia8 \
GMSB_L-400TeV_Ctau-800cm_13TeV-pythia8


do
    hadd -k -f ${sample}.root /storage/cms/store/group/phys_llp/DelayedPhoton/2016/jobs/${sample}_Job*.root
    eval `scram unsetenv -sh`
    env -i X509_USER_PROXY=${x509loc} gfal-copy -t 2400 -T 2400 -p -f --checksum-mode=both ${sample}.root gsiftp://transfer-lb.ultralight.org/${OUTDIR}
	eval `scram runtime -sh`
    rm ${sample}.root
done
