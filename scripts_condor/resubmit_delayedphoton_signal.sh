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
	echo "Sample " ${sample}
	inputfilelist=/src/DelayedPhoton/lists/DelayedPhoton2016/MC2016Central/${sample}.caltech.txt
	nfiles=`cat ${CMSSW_BASE}$inputfilelist | wc | awk '{print $1}' `
	filesPerJob=`python -c "print int($nfiles.0/$maximumjob)+1"`
	maxjob=`python -c "print int($nfiles.0/$filesPerJob)-1"`
	analyzer=DelayedPhotonAnalyzer
	#rm submit/${sample}_Job*.jdl
	#rm log/${sample}_Job*

	for jobnumber in `seq 0 1 ${maxjob}`
	do
		jdl_file=submit/${analyzer}_${sample}_Job${jobnumber}_Of_${maxjob}.jdl
                #noFail=`grep YYYY log/${analyzer}_${sample}_Job${jobnumber}_Of_${maxjob}*.out`
		outRoot="/storage/cms/store/group/phys_llp/DelayedPhoton/2016/jobs/${sample}_Job${jobnumber}_Of_${maxjob}.root"
		
		minimumsize=50000	
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
                #        echo "job ${analyzer}_${sample}_Job${jobnumber}_Of_${maxjob} being processed now, be patient"
                else
                        echo "job ${analyzer}_${sample}_Job${jobnumber}_Of_${maxjob} failed, now being resubmitted"
                        rm log/${analyzer}_${sample}_Job${jobnumber}_Of_${maxjob}*
                        condor_submit submit/${analyzer}_${sample}_Job${jobnumber}_Of_${maxjob}.jdl
                fi
	done
done

