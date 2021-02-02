#!/bin/sh

mkdir -p log
mkdir -p submit

cd ../
RazorAnalyzerDir=`pwd`
cd -

job_script=${RazorAnalyzerDir}/scripts_condor/runRazorJob_CaltechT2_runlocal.sh
filesPerJob=1

for sample in \
crab_prod_Run2DelayedPhotonNtupler_DataUL2018_EGamma_Run2018D

do
    inputfilelist=/src/DelayedPhoton/lists/DelayedPhoton2018/DataUL/${sample}.txt
    nfiles=`cat ${CMSSW_BASE}$inputfilelist | wc | awk '{print $1}' `
    maxjob=`python -c "print int($nfiles.0/$filesPerJob)-1"`
    analyzer=ZeeTiming
    #for jobnumber in `seq 0 1 ${maxjob}`
    for jobnumber in 0 #`seq 0 1 ${maxjob}`
    do
       echo "Sample " ${sample}

       echo "job "${jobnumber}" out of " ${maxjob}
       sh ${job_script} ${analyzer}_${sample}_Job${jobnumber}_Of_${maxjob} ${CMSSW_BASE}/src/DelayedPhoton/scripts_condor/jobs  ${analyzer} ${CMSSW_BASE}${inputfilelist} yes 10 ${filesPerJob} ${jobnumber} ${sample}_Job${jobnumber}_Of_${maxjob}.root 
    done
done

