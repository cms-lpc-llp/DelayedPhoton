#!/bin/sh
export X509_USER_PROXY=/storage/af/user/$(whoami)/my_proxy

OUTDIR=/storage/af/user/qnguyen/DelayedPhoton/CMSSW_10_6_12/src/DelayedPhoton/local_storage///store/group/phys_llp/DelayedPhoton/2017/hadd/

if [ ! -d ${OUTDIR} ]
then
    echo "${OUTDIR} does not exist. Creating one..."
    mkdir -p ${OUTDIR}
fi
    
for sample in \
GMSB_Lambda450TeV_CTau10000cm \
GMSB_Lambda450TeV_CTau1000cm \
GMSB_Lambda450TeV_CTau100cm \
GMSB_Lambda450TeV_CTau10cm \
GMSB_Lambda450TeV_CTau1200cm \
GMSB_Lambda450TeV_CTau200cm \
GMSB_Lambda450TeV_CTau400cm \
GMSB_Lambda450TeV_CTau50cm \
GMSB_Lambda450TeV_CTau600cm \
GMSB_Lambda450TeV_CTau800cm \
GMSB_Lambda500TeV_CTau10000cm \
GMSB_Lambda500TeV_CTau1000cm \
GMSB_Lambda500TeV_CTau100cm \
GMSB_Lambda500TeV_CTau10cm \
GMSB_Lambda500TeV_CTau1200cm \
GMSB_Lambda500TeV_CTau200cm \
GMSB_Lambda500TeV_CTau400cm \
GMSB_Lambda500TeV_CTau50cm \
GMSB_Lambda500TeV_CTau600cm \
GMSB_Lambda500TeV_CTau800cm \

do
    correctSample=${sample/Lambda/L-}
    correctSample=${correctSample/CTau/Ctau-}
    correctSample=${correctSample/cm/cm_13TeV-pythia8}
    echo "${correctSample}"
    hadd -k -f ${correctSample}.root /storage/af/user/qnguyen/DelayedPhoton/CMSSW_10_6_12/src/DelayedPhoton/local_storage///store/group/phys_llp/DelayedPhoton/2017/jobs/${sample}_Job*.root
    cp ${correctSample}.root ${OUTDIR}/${correctSample}.root

    rm ${correctSample}.root
done

