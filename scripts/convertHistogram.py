import ROOT as rt

def GetKeyNames( self, dir = "" ):
        self.cd(dir)
        return [key.GetName() for key in rt.gDirectory.GetListOfKeys()]
def GetClassNames( self, dir = "" ):
        self.cd(dir)
        return [key.GetClassName() for key in rt.gDirectory.GetListOfKeys()]

rt.TFile.GetKeyNames = GetKeyNames
rt.TFile.GetClassNames = GetClassNames


infile = rt.TFile("/storage/af/user/qnguyen/DelayedPhoton/CMSSW_10_6_12/src/DelayedPhoton/ElectronEffFastsimToFullsimCorrectionFactors.2016.root","READ")
infile.Print()
keyList = infile.GetKeyNames()
classList = infile.GetClassNames()
outputFile = rt.TFile("tempOut.root","recreate")
for j in range(0, len(keyList)):
    print (classList[j] + "   ===   " + keyList[j])

    if classList[j] == "TH2F":
        infile.cd()
        histThis = infile.Get(keyList[j])
        outputFile.cd()
        histThis_out = rt.TH2D()
        histThis.Copy(histThis_out)
        histThis_out.Write()
infile.Close()
outputFile.Close()

