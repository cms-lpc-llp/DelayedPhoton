import os, sys, glob
from subprocess import Popen, PIPE
for signal in glob.glob("/storage/af/user/yeseo/DelayedPhoton_origin/CMSSW_10_6_6/src/Tuplizer/DelayedPhotonTuplizer/python/GMSB_2016signal/*"):
    bare_signal = os.path.basename(signal).replace('.root','')#.replace("crab_prod_Run2DelayedPhotonNtupler_Data2017_","")+"_31Mar2018"
    cmd = "find {} -name \"*.root\"".format(signal)
    #print(cmd)
    filelist, _ = (Popen(cmd, shell=True, stdout=PIPE)).communicate()
    with open("/storage/af/user/qnguyen/DelayedPhoton/CMSSW_10_6_12/src/DelayedPhoton/lists/DelayedPhoton2016/ExtraSignal/{}.txt".format(bare_signal),"w") as fileout:
        fileout.write(filelist)
        print(bare_signal) 
