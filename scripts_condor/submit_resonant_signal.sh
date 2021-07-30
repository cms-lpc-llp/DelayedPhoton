#!/bin/sh
export X509_USER_PROXY=/storage/af/user/$(whoami)/my_proxy
mkdir -p log
mkdir -p submit

if [ -z "${CMSSW_BASE}" ]
then
    CMSSW_BASE=/storage/af/user/$(whoami)/DelayedPhoton/CMSSW_10_6_12/
    echo 'Setting CMSSW_BASE to be \${CMSSW_BASE}'
fi

cd ../
RazorAnalyzerDir=`pwd`
cd -

job_script=${RazorAnalyzerDir}/scripts_condor/runRazorJob_CaltechT2.sh
#filesPerJob=2
maximumjob=20

for sample in \
    ZpToSSTo4Photon_mZp500_ms100_pl1000

do
	echo "Sample " ${sample}
	inputfilelist=/src/DelayedPhoton/lists/DelayedPhoton2017/MC/${sample}.txt
	nfiles=`cat ${CMSSW_BASE}$inputfilelist | wc | awk '{print $1}' `
	filesPerJob=`python -c "print int($nfiles.0/$maximumjob)+1"`
	maxjob=`python -c "print int($nfiles.0/$filesPerJob)-1"`
	analyzer=DelayedResonantPhoton

	rm submit/${analyzer}_${sample}_Job*.jdl
	rm log/${analyzer}_${sample}_Job*

	for jobnumber in `seq 0 1 ${maxjob}`
	do
		echo "job " ${jobnumber} " out of " ${maxjob}
		jdl_file=submit/${analyzer}_${sample}_Job${jobnumber}_Of_${maxjob}.jdl
		echo "Universe = vanilla" > ${jdl_file}
		echo "Executable = ${job_script}" >> ${jdl_file}
		echo "Arguments = ${analyzer}_${sample}_Job${jobnumber}_Of_${maxjob} /store/group/phys_susy/razor/Run2Analysis/DelayedPhotonAnalysis/2017/jobs/ ${analyzer} ${inputfilelist} no 10 ${filesPerJob} ${jobnumber} ${sample}_Job${jobnumber}_Of_${maxjob}.root" >> ${jdl_file}
		echo "Log = log/${analyzer}_${sample}_Job${jobnumber}_Of_${maxjob}_PC.log" >> ${jdl_file}
		echo "Output = log/${analyzer}_${sample}_Job${jobnumber}_Of_${maxjob}_\$(Cluster).\$(Process).out" >> ${jdl_file}
		echo "Error = log/${analyzer}_${sample}_Job${jobnumber}_Of_${maxjob}_\$(Cluster).\$(Process).err" >> ${jdl_file}
		echo "should_transfer_files = YES" >> ${jdl_file}
		echo "RequestMemory = 4000" >> ${jdl_file}
		echo "RequestCpus = 1" >> ${jdl_file}
		echo "x509userproxy = \$ENV(X509_USER_PROXY)" >> ${jdl_file}
                echo "+RunAsOwner = True" >> ${jdl_file}
                echo "+InteractiveUser = true" >> ${jdl_file}
                echo '+SingularityImage = "/cvmfs/singularity.opensciencegrid.org/cmssw/cms:rhel7"' >> ${jdl_file}
                echo "+SingularityBindCVMFS = True" >> ${jdl_file}
                echo "run_as_owner = True" >> ${jdl_file}
                echo "+JobBatchName = \"${sample}"\" >> ${jdl_file}
		echo "when_to_transfer_output = ON_EXIT" >> ${jdl_file}
		echo "Queue 1" >> ${jdl_file}
		echo "condor_submit submit/${analyzer}_${sample}_Job${jobnumber}_Of_${maxjob}.jdl"
		condor_submit submit/${analyzer}_${sample}_Job${jobnumber}_Of_${maxjob}.jdl
	done
done
