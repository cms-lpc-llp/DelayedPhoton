import os, sys, glob
from subprocess import Popen, PIPE
for signal in glob.glob("/storage/cms//store/group/phys_llp/Run2DelayedPhotonNtuple/2018/DataUL/EGamma/*"):
    bare_signal = os.path.basename(signal).replace("crab_prod_Run2DelayedPhotonNtupler_Data2018_","")
    cmd = "find {} -name \"*.root\"".format(signal)
    #print(cmd)
    filelist, _ = (Popen(cmd, shell=True, stdout=PIPE)).communicate()
    with open("/storage/af/user/qnguyen/DelayedPhoton/CMSSW_10_6_12/src/DelayedPhoton/lists/DelayedPhoton2018/DataUL/{}.txt".format(bare_signal),"w") as fileout:
        fileout.write(filelist)
        print(bare_signal) 
