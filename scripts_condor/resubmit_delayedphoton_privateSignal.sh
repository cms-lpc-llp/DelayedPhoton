#!/bin/sh

mkdir -p log
mkdir -p submit

cd ../
RazorAnalyzerDir=`pwd`
cd -

job_script=${RazorAnalyzerDir}/scripts_condor/runRazorJob_CaltechT2.sh
maximumjob=20
#filesPerJob=40

for sample in \
    GMSB_L100TeV_Ctau100cm_13TeV-pythia8 \
    GMSB_L100TeV_Ctau1cm_13TeV-pythia8 \
    GMSB_L100TeV_Ctau50cm_13TeV-pythia8 \
    GMSB_L150TeV_Ctau100cm_13TeV-pythia8 \
    GMSB_L150TeV_Ctau1cm_13TeV-pythia8 \
    GMSB_L150TeV_Ctau50cm_13TeV-pythia8 \
    GMSB_L200TeV_Ctau100cm_13TeV-pythia8 \
    GMSB_L200TeV_Ctau1cm_13TeV-pythia8 \
    GMSB_L200TeV_Ctau50cm_13TeV-pythia8 \
    GMSB_L250TeV_Ctau100cm_13TeV-pythia8 \
    GMSB_L250TeV_Ctau1cm_13TeV-pythia8 \
    GMSB_L250TeV_Ctau50cm_13TeV-pythia8 \
    GMSB_L300TeV_Ctau100cm_13TeV-pythia8 \
    GMSB_L300TeV_Ctau1cm_13TeV-pythia8 \
    GMSB_L300TeV_Ctau50cm_13TeV-pythia8 \
    GMSB_L350TeV_Ctau100cm_13TeV-pythia8 \
    GMSB_L350TeV_Ctau1cm_13TeV-pythia8 \
    GMSB_L350TeV_Ctau50cm_13TeV-pythia8 \
    GMSB_L400TeV_Ctau100cm_13TeV-pythia8 \
    GMSB_L400TeV_Ctau1cm_13TeV-pythia8 \
    GMSB_L400TeV_Ctau50cm_13TeV-pythia8

do
	echo "Sample " ${sample}
	inputfilelist=/src/DelayedPhoton/lists/DelayedPhoton2017/MC2017Private/${sample}.txt
	
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
		outRoot="/mnt/hadoop/store/group/phys_susy/razor/Run2Analysis/DelayedPhotonAnalysis/2017/jobs/${sample}_Job${jobnumber}_Of_${maxjob}.root"
		
		minimumsize=100000	
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

