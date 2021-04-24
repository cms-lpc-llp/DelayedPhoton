import os, sys, glob
from subprocess import Popen, PIPE
for signal in glob.glob("/mnt/hadoop/store/group/phys_susy/razor/run2/Run2DelayedPhotonNtuple/Data2018_pho_corr/EGamma/*"):
    bare_signal = os.path.basename(signal).replace("crab_prod_Run2DelayedPhotonNtupler_Data2018_","")
    cmd = "find {} -name \"*.root\"".format(signal)
    #print(cmd)
    filelist, _ = (Popen(cmd, shell=True, stdout=PIPE)).communicate()
    with open("/storage/user/qnguyen/DelayedPhoton/CMSSW_10_6_12/src/DelayedPhoton/lists/DelayedPhoton2018_pho_corr/Data2018/{}.txt".format(bare_signal),"w") as fileout:
        fileout.write(filelist)
        print(bare_signal) 
