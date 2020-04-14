import os, sys, glob
from subprocess import Popen, PIPE
for signal in glob.glob("/mnt/hadoop/store/group/phys_susy/razor/run2/Run2RazorNtupleV4.1/MC/MC2016PrivateGMSB/v1/zhicaiz/*"):
    bare_signal = os.path.basename(signal)#.replace("crab_prod_Run2DelayedPhotonNtupler_Data2017_","")+"_31Mar2018"
    cmd = "find {} -name \"*.root\"".format(signal)
    #print(cmd)
    filelist, _ = (Popen(cmd, shell=True, stdout=PIPE)).communicate()
    with open("/storage/user/qnguyen/DelayedPhoton/CMSSW_10_6_6/src/DelayedPhoton/lists/Run2/razorNtuplerV4p1/MC_Summer16_reMINIAOD//{}.caltech.txt".format(bare_signal),"w") as fileout:
        fileout.write(filelist)
        print(bare_signal) 
