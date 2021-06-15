import ROOT as rt
import sys

def GetKeyNames( self, dir = "" ):
        self.cd(dir)
        return [key.GetName() for key in rt.gDirectory.GetListOfKeys()]
def GetClassNames( self, dir = "" ):
        self.cd(dir)
        return [key.GetClassName() for key in rt.gDirectory.GetListOfKeys()]

rt.TFile.GetKeyNames = GetKeyNames
rt.TFile.GetClassNames = GetClassNames

infile_name = sys.argv[1]
outfile_name = sys.argv[2]

infile = rt.TFile(infile_name,"READ")
keyList = infile.GetKeyNames()
classList = infile.GetClassNames()
outputFile = rt.TFile(outfile_name,"recreate")
for j in range(0, len(keyList)):
    print (classList[j] + "   ===   " + keyList[j])

    if classList[j] == "TH2F":
        infile.cd()
        histThis = infile.Get(keyList[j])
        objThisName = keyList[j]
        outputFile.cd()
        histThis_out = rt.TH2D()
        histThis.Copy(histThis_out)
        histThis_out.Write(objThisName)
    else:
        infile.cd()
        objThis = infile.Get(keyList[j])
        objThisName = keyList[j]
        #print("Name of this object: {}".format(objThisName))
        outputFile.cd()
        objThis_out = objThis.Clone(objThisName)
        objThis_out.Write()

infile.Close()
outputFile.Close()
