#!/bin/sh
export X509_USER_PROXY=/storage/user/$(whoami)/my_proxy

mkdir -p log
mkdir -p submit

if [ -z "${CMSSW_BASE}" ]
then
    CMSSW_BASE=/storage/user/$(whoami)/DelayedPhoton/CMSSW_10_6_12/
    echo 'Setting CMSSW_BASE to be \${CMSSW_BASE}'
fi

cd ../
RazorAnalyzerDir=`pwd`
cd -

job_script=${RazorAnalyzerDir}/scripts_condor/runRazorJob_CaltechT2.sh
filesPerJob=1

for sample in \
SinglePhoton_Run2017B_31Mar2018 \
SinglePhoton_Run2017D_31Mar2018 \
SinglePhoton_Run2017F_31Mar2018 \
SinglePhoton_Run2017C_31Mar2018 \
SinglePhoton_Run2017E_31Mar2018
do
	echo "Sample " ${sample}
	inputfilelist=/src/DelayedPhoton/lists/DelayedPhoton2017/Data2017/${sample}.txt
	nfiles=`cat ${CMSSW_BASE}$inputfilelist | wc | awk '{print $1}' `
	maxjob=`python -c "print int($nfiles.0/$filesPerJob)-1"`
	analyzer=DelayedPhotonAnalyzer
	#rm submit/${sample}_Job*.jdl
	#rm log/${sample}_Job*

	for jobnumber in `seq 0 1 ${maxjob}`
	do
		jdl_file=submit/${analyzer}_${sample}_Job${jobnumber}_Of_${maxjob}.jdl
		#noFail=`grep YYYY log/${analyzer}_${sample}_Job${jobnumber}_Of_${maxjob}*.out`
        outRoot="/mnt/hadoop/store/group/phys_susy/razor/Run2Analysis/DelayedPhotonAnalysis/2017/jobs/${sample}_Job${jobnumber}_Of_${maxjob}.root"

		minimumsize=20000
                actualsize=0
                if [ -f ${outRoot} ]
                then
                        actualsize=$(wc -c <"${outRoot}")
                fi
                if [ $actualsize -ge $minimumsize ]
                then
                        finished=yes
			#echo "job ${analyzer}_${sample}_Job${jobnumber}_Of_${maxjob} finished already "
		#elif [ -z "${noFail}" ]
		#then
		#	echo "job ${analyzer}_${sample}_Job${jobnumber}_Of_${maxjob} being processed now, be patient"
		else
            echo "File ${outRoot} seems corrupted."
			echo "job ${analyzer}_${sample}_Job${jobnumber}_Of_${maxjob} failed, now being resubmitted"
			rm log/${analyzer}_${sample}_Job${jobnumber}_Of_${maxjob}*
			condor_submit submit/${analyzer}_${sample}_Job${jobnumber}_Of_${maxjob}.jdl
		fi
	done
done

