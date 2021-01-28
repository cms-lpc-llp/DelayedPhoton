#!/bin/sh

mkdir -p log
mkdir -p submit

cd ../
RazorAnalyzerDir=`pwd`
cd -

job_script=${RazorAnalyzerDir}/scripts_condor/runRazorJob_CaltechT2_runlocal.sh
filesPerJob=1

for sample in \
DYToEE

do
	echo "Sample " ${sample}
	inputfilelist=/src/DelayedPhoton/lists/DelayedPhoton2018/MCUL/${sample}.txt
	nfiles=`cat ${CMSSW_BASE}$inputfilelist | wc | awk '{print $1}' `
	maxjob=`python -c "print int($nfiles.0/$filesPerJob)-1"`
	analyzer=ZeeTiming

    jobnumber=0
    echo "job "${jobnumber}" out of " ${maxjob}
    sh ${job_script} ${analyzer}_${sample}_Job${jobnumber}_Of_${maxjob} ${CMSSW_BASE}/src/DelayedPhoton/scripts_condor/jobs  ${analyzer} ${inputfilelist} no 10 ${filesPerJob} ${jobnumber} ${sample}_Job${jobnumber}_Of_${maxjob}.root 
done

