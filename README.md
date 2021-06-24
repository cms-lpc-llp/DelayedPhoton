DelayedPhoton analyzer for Delayed photon analysis (2017)
=============

Setup
-------------

    cmsrel CMSSW_9_4_9
    cd CMSSW_9_4_9/src
    git clone git@github.com:cms-lpc-llp/DelayedPhoton.git
    cd DelayedPhoton
    make

Run
-------------

    ./RazorRun_T2 <list of input files> <name of your analyzer> <options>    

Example: to process the DY sample, do:
	
     ./RazorRun_T2 lists/DelayedPhoton2017/example.txt DelayedPhotonAnalyzer -d=yes -f=example.root
     
     ./RazorRun_T2 lists/DelayedPhoton2017/exampleMC.txt DelayedPhotonAnalyzer -d=no -f=example.root

For the resonant photon analysis, do

     ./RazorRun_T2 lists/DelayedPhoton2017/MC/example.txt DelayedResonantPhoton -d=no -f=example.root

(we use V4p1 razorNtupler for 2016 paper; they are all in: lists/Run2/razorNtuplerV4p1/)

submit condor jobs to run all samples 
-------------

     cd scripts_condor
     source submit_delayedphoton_signal.sh
     source resubmit_delayedphoton_signal.sh # to check failed jobs and resubmit
     source hadd_delayedphoton_signal.sh # to hadd the files
    
(might need to update the scripts since Caltech T2 condor configs keep changing...)

The razoranalyzer ntupler we use for the 2016 paper are in: /mnt/hadoop/store/group/phys_susy/razor/Run2Analysis/DelayedPhotonAnalysis/2016/orderByPt/withcut

For 2016 analysis, only need to run MC signal and DoubleEG data. No need for MC background.
