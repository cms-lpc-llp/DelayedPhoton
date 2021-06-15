#!/bin/bash

sample_array=()


################################
#For 2017 Data SingleEG
#inputfilelist_=/src/DelayedPhoton/lists/DelayedPhoton2017/Data2017/
#sample_array+=(SinglePhoton_Run2017B_31Mar2018)
#sample_array+=(SinglePhoton_Run2017C_31Mar2018)
#sample_array+=(SinglePhoton_Run2017D_31Mar2018)
#sample_array+=(SinglePhoton_Run2017E_31Mar2018)
#sample_array+=(SinglePhoton_Run2017F_31Mar2018)
#outputfilepath=store/group/phys_susy/razor/Run2Analysis/EcalTiming/2021May16/2017Data/SingleEG/
#isData=yes
################################

################################
#For 2017 Data DoubleEG
#inputfilelist_=/src/DelayedPhoton/lists/DelayedPhoton2017/Data2017/
#sample_array+=(DoubleEG_2017B_31Mar2018)
#sample_array+=(DoubleEG_2017C_31Mar2018)
#sample_array+=(DoubleEG_2017D_31Mar2018)
#sample_array+=(DoubleEG_2017E_31Mar2018)
#sample_array+=(DoubleEG_2017F_31Mar2018)
#outputfilepath=store/group/phys_susy/razor/Run2Analysis/EcalTiming/2021May16/2017Data/DoubleEG/
#isData=yes
################################

################################
##For 2017 MC
inputfilelist_=/src/DelayedPhoton/lists/DelayedPhoton2017/MC/
sample_array+=(DYToEE)
outputfilepath=store/group/phys_susy/razor/Run2Analysis/EcalTiming/2021May16/2017MC_DYToEE_Smearing_NC/
isData=no
################################


################################
# For 2018 MCUL
#inputfilelist_=/src/DelayedPhoton/lists/DelayedPhoton2018/MCUL/
#sample_array+=(DYToEE)
#outputfilepath=store/group/phys_susy/razor/Run2Analysis/EcalTiming/2021Feb17/EcalTimeSmearing_2018UL/MC/
#isData=no
################################


################################
#For 2018 MC
#inputfilelist_=/src/DelayedPhoton/lists/DelayedPhoton2018/MC/
#sample_array+=(DYJetsToEE_M-50_TuneCP5_13TeV-madgraphMLM-pythia8)
#outputfilepath=store/group/phys_susy/razor/Run2Analysis/EcalTiming/2021Feb17/EcalTimeSmearing_2018/MC/
#isData=no
################################

mkdir -p log
mkdir -p submit

cd ../
RazorAnalyzerDir=`pwd`
cd -
cd ../../../
CMSSW_BASE=`pwd`
cd -


job_script=${RazorAnalyzerDir}/scripts_condor/runRazorJob_CaltechT2.sh
filesPerJob=1

for sample in "${sample_array[@]}"

do
	echo "Sample " ${sample}
	inputfilelist=${inputfilelist_}${sample}.txt
	nfiles=`cat ${CMSSW_BASE}${inputfilelist} | wc | awk '{print $1}' `
	maxjob=`python -c "print int($nfiles.0/$filesPerJob)-1"`
	analyzer=ZeeTiming

	rm submit/${analyzer}_${sample}_Job*.jdl
	rm log/${analyzer}_${sample}_Job*

	for jobnumber in `seq 0 1 ${maxjob}`
	do
		echo "job " ${jobnumber} " out of " ${maxjob}
		jdl_file=submit/${analyzer}_${sample}_Job${jobnumber}_Of_${maxjob}.jdl
		echo "Universe = vanilla" > ${jdl_file}
		echo "Executable = ${job_script}" >> ${jdl_file}
		echo "Arguments = ${analyzer}_${sample}_Job${jobnumber}_Of_${maxjob} ${outputfilepath}/jobs ${analyzer} ${inputfilelist} ${isData} 10 ${filesPerJob} ${jobnumber} ${sample}_Job${jobnumber}_Of_${maxjob}.root" >> ${jdl_file}
		echo "Log = log/${analyzer}_${sample}_Job${jobnumber}_Of_${maxjob}_PC.log" >> ${jdl_file}
		echo "Output = log/${analyzer}_${sample}_Job${jobnumber}_Of_${maxjob}_\$(Cluster).\$(Process).out" >> ${jdl_file}
		echo "Error = log/${analyzer}_${sample}_Job${jobnumber}_Of_${maxjob}_\$(Cluster).\$(Process).err" >> ${jdl_file}
		echo 'Requirements=TARGET.OpSysAndVer=="CentOS7"' >> ${jdl_file}
		echo "should_transfer_files = YES" >> ${jdl_file}
		echo "RequestMemory = 4000" >> ${jdl_file}
		echo "RequestCpus = 1" >> ${jdl_file}
		echo "x509userproxy = \$ENV(X509_USER_PROXY)" >> ${jdl_file}
                echo "+RunAsOwner = True" >> ${jdl_file}
                echo "+InteractiveUser = true" >> ${jdl_file}
                echo '+SingularityImage = "/cvmfs/singularity.opensciencegrid.org/cmssw/cms:rhel7"' >> ${jdl_file}
                echo "+SingularityBindCVMFS = True" >> ${jdl_file}
                echo "run_as_owner = True" >> ${jdl_file}
		echo "when_to_transfer_output = ON_EXIT" >> ${jdl_file}
		echo "Queue 1" >> ${jdl_file}
		echo "condor_submit submit/${analyzer}_${sample}_Job${jobnumber}_Of_${maxjob}.jdl"
		condor_submit submit/${analyzer}_${sample}_Job${jobnumber}_Of_${maxjob}.jdl
	done
done

