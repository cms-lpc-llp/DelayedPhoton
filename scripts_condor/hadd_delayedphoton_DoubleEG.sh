#!/bin/sh

export X509_USER_PROXY=/storage/user/$(whoami)/my_proxy
outdir=/store/group/phys_susy/razor/Run2Analysis/DelayedPhotonAnalysis/2016/reproduce/hadd/

if [! -d $(outdir)]
then
    echo "$(outdir) does not exist. Creating one..."
    hadoop fs -mkdir $(outdir)
fi
    
for sample in \
DoubleEG_2016B_ver1_25Mar2019 \
DoubleEG_2016B_ver2_25Mar2019 \
DoubleEG_2016C_25Mar2019 \
DoubleEG_2016D_25Mar2019 \
DoubleEG_2016E_25Mar2019 \
DoubleEG_2016F_25Mar2019 \
DoubleEG_2016G_25Mar2019 \
DoubleEG_2016H_25Mar2019

do

    hadd -k -f /tmp/${sample}.root /mnt/hadoop/store/group/phys_susy/razor/Run2Analysis/DelayedPhotonAnalysis/2016/reproduce/jobs/${sample}_Job*.root
    hadoop fs -put /tmp/${sample}.root $(outdir)

done

