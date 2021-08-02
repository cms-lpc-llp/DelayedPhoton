#!/bin/sh

hostname
echo "Job started"
date

voms-proxy-info -all
x509loc=${X509_USER_PROXY}

echo "x509 loc: ${x509loc}"

code_dir_suffix=$1
outputDirectory=$2
analysisType=$3
inputfilelist=$4
isData=$5
option=$6
filePerJob=$7
jobnumber=$8
outputfile=$9

currentDir=`pwd`
homeDir=/storage/af/user/$(whoami)/
localDir=/storage/af/user/$(whoami)/DelayedPhoton/CMSSW_10_6_12/src/DelayedPhoton/local_storage/
runDir=${currentDir}/$(whoami)_${code_dir_suffix}/
rm -rf ${runDir}
mkdir -p ${runDir}

rm -rf /tmp/$(whoami)*

if [ -f /cvmfs/cms.cern.ch/cmsset_default.sh ]
then

	#setup cmssw
	cd ${homeDir}/DelayedPhoton/CMSSW_10_6_12/src/DelayedPhoton/
	workDir=`pwd`
	echo "entering directory: ${workDir}"
	source /cvmfs/cms.cern.ch/cmsset_default.sh
	#export SCRAM_ARCH=slc6_amd64_gcc700
	ulimit -c 0
	eval `scram runtime -sh`
	echo `which root`

	cd ${runDir}
	echo "entering directory: ${runDir}"

	if [ -f $CMSSW_BASE/src/DelayedPhoton/RazorRun_T2 ]
	then 
		cp $CMSSW_BASE/src/DelayedPhoton/RazorRun_T2 ./

		#get grid proxy
		export X509_USER_PROXY=/storage/af/user/qnguyen/my_proxy
		
		#run the job
        echo "Getting input file list from: ${CMSSW_BASE}${inputfilelist}"
		cat ${CMSSW_BASE}${inputfilelist} | awk "NR > (${jobnumber}*${filePerJob}) && NR <= ((${jobnumber}+1)*${filePerJob})" > inputfilelistForThisJob_${jobnumber}.txt
		echo ""
		echo "************************************"
		echo "Running on these input files:"
		cat inputfilelistForThisJob_${jobnumber}.txt
		echo "************************************"
		echo ""

		#remove empty input files
		for ifile in `cat inputfilelistForThisJob_${jobnumber}.txt`
		do
			minimumsize=60000
                	actualsize=0
                	if [ -f ${ifile} ]
                	then
                        	actualsize=$(wc -c <"${ifile}")
                	fi
			if [ $actualsize -ge ${minimumsize} ]
                	then
				echo ${ifile} >> inputfilelistForThisJob_${jobnumber}_filter.txt
			fi

		done
		echo "************************************"
		echo "Running on these input files after removing bad files"
		cat inputfilelistForThisJob_${jobnumber}_filter.txt
		echo "************************************"
		
		echo " "; echo "Starting razor run job now"; echo " ";
		echo ./RazorRun_T2 inputfilelistForThisJob_${jobnumber}_filter.txt ${analysisType} -d=${isData} -n=${option} -f=${outputfile}

		./RazorRun_T2 inputfilelistForThisJob_${jobnumber}_filter.txt ${analysisType} -d=${isData} -n=${option} -f=${outputfile}

		echo ${outputfile}
		echo ${outputDirectory}
        if [ ! -d ${localDir}/${outputDirectory} ];
        then
            mkdir -p ${localDir}/${outputDirectory}
        fi

		##^_^##
		echo "RazorRun_T2 finished"
		date

		sleep 2
		echo "I slept for 2 second" 

		##job finished, copy file to T2
		echo "copying output file to ${localDir}/${outputDirectory}"
        eval `scram unsetenv -sh`
		echo "cp ${outputfile} ${localDir}/${outputDirectory}/${outputfile}"
		cp ${outputfile} ${localDir}/${outputDirectory}/${outputfile}
		if [ -f ${localDir}/${outputDirectory}/${outputfile} ]
		then
			echo "SUCCESS ============ good news, job finished successfully "
		else
			echo "FAILED ============ somehow job failed, please consider resubmitting"
		fi
	else
		echo echo "FAILED NO ACCESS ============= failed to access file RazorRun_T2, job anandoned"
		sleep 1
	fi

else
	echo "FAILED NO ACCESS CVMFS ============= failed to access file /cvmfs/cms.cern.ch/cmsset_default.sh, job anandoned"
fi

cd ${currentDir}
rm -rf ${runDir}
echo "Job finished"
date
