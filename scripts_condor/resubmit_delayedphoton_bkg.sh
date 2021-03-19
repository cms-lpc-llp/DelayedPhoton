#!/bin/sh

mkdir -p log
mkdir -p submit

cd ../
RazorAnalyzerDir=`pwd`
cd -

job_script=${RazorAnalyzerDir}/scripts_condor/runRazorJob_CaltechT2.sh
filesPerJob=1

for sample in \
QCD_Pt-120to170_EMEnriched_TuneCP5_13TeV_pythia8 \
QCD_Pt-15to20_EMEnriched_TuneCP5_13TeV_pythia8 \
QCD_Pt-170to300_EMEnriched_TuneCP5_13TeV_pythia8 \
QCD_Pt-20to30_EMEnriched_TuneCP5_13TeV_pythia8 \
QCD_Pt-300toInf_EMEnriched_TuneCP5_13TeV_pythia8 \
QCD_Pt-30to50_EMEnriched_TuneCP5_13TeV_pythia8 \
QCD_Pt-50to80_EMEnriched_TuneCP5_13TeV_pythia8 \
QCD_Pt-80to120_EMEnriched_TuneCP5_13TeV_pythia8 \
QCD_Pt-30to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8 \
QCD_Pt-30toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8 \
QCD_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8 \
GJets_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8 \
GJets_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8 \
GJets_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8 \
GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8 \
GJets_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8 \
DiPhotonJetsBox_M40_80-Sherpa \
DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa \

do
	echo "Sample " ${sample}
	inputfilelist=/src/DelayedPhoton/lists/DelayedPhoton2017/MC/${sample}.txt
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

