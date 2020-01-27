import os, sys, glob
from subprocess import Popen, PIPE
for signal in glob.glob("/mnt/hadoop/store/group/phys_susy/razor/run2/Run2DelayedPhotonNtuple/Data2017/SinglePhoton/*"):
    bare_signal = os.path.basename(signal).replace("crab_prod_Run2DelayedPhotonNtupler_Data2017_","")+"_31Mar2018"
    filelist, _ = (Popen("find {} -name *.root".format(signal), shell=True, stdout=PIPE)).communicate()
    with open("/storage/user/qnguyen/DelayedPhoton/CMSSW_10_6_6/src/DelayedPhoton/lists/DelayedPhoton2017/Data2017/{}.txt".format(bare_signal),"w") as fileout:
        fileout.write(filelist)
        print(bare_signal) 