import ROOT as rt
from array import array

infile = rt.TFile.Open("SF_isTrk_281118.root", "read")
infile.ls()
# Get Pt bins
data_eb = infile.Get("Data_EB_Eff")
tothist = data_eb.GetTotalHistogram()
nBinsPt = tothist.GetNbinsX()
PtBins = []
for i in range(1, nBinsPt+1):
    PtBins.append(tothist.GetBinLowEdge(i))
PtBins.append(PtBins[-1]+tothist.GetBinWidth(nBinsPt))
#print(PtBins)
EtaBins = [-2.5, -1.442, 1.442, 2.5]
outhist = rt.TH2F("EGamma_SF2D", ";eta;pt", 3, array('f', EtaBins), nBinsPt, array('f', PtBins))

# Get actual data
eff_eb = infile.Get("EB_Hist")
eff_ee = infile.Get("EE_Hist")
for i in range(1, nBinsPt+1):
    outhist.SetBinContent(2, i, eff_eb.GetBinContent(i))
    outhist.SetBinContent(1, i, eff_ee.GetBinContent(i))
    outhist.SetBinContent(3, i, eff_ee.GetBinContent(i))
outhist.SetEntries(1)
print(outhist.GetEntries())

outfile = rt.TFile.Open("SF_TrkVetoEff_2017.root","recreate")
outhist.Write()
outfile.Close()


#c1 = rt.TCanvas("c1","",600, 600)
#outhist.Draw("COLZ TEXT")

#c1.SaveAs("test.png")



