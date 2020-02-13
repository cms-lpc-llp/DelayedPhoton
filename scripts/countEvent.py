import ROOT as rt
from collections import OrderedDict
from sys import argv
cuts = OrderedDict()
cuts['nPhoton>1'] = "n_Photons >= 1 "
cuts['photonIsEB'] = "&& abs(pho1Eta)<1.4442 "
cuts['photonPT'] = "&& pho1Pt > 70 "
cuts['METFilters'] =  " && Flag_HBHENoiseFilter == 1 && Flag_HBHEIsoNoiseFilter ==1 && Flag_goodVertices == 1 && Flag_eeBadScFilter == 1 && Flag_EcalDeadCellTriggerPrimitiveFilter == 1 && Flag_CSCTightHaloFilter == 1  && Flag_badMuonFilter == 1 && Flag_badGlobalMuonFilter == 0 && Flag_duplicateMuonFilter ==0"
cuts['photonR9'] = "  && pho1R9 > 0.9 "
cuts['photonTrackVeto'] = " && pho1passTrackVeto "
cuts['photonHoverE'] = " && pho1passHoverETight"
cuts['photonIetaeta'] = " && pho1passSigmaIetaIetaTight "
cuts['photonSminor'] = " && pho1Sminor < 0.4"
cuts['photonSmajor'] = " && pho1passSmajorTight" 
cuts['photonIsolation'] = " && pho1passIsoTight_comboIso "
cuts['nJets'] = " && n_Jets > 2 "
cuts['HT'] = " && (n_Photons == 1 && HT - pho1Pt > 400) || (n_Photons >=2 && HT - pho1Pt -pho2Pt > 400)"
cuts['Trigger'] = " && HLTDecision[880] == 1"

infile = rt.TFile.Open(argv[1],"r")
infile.Print()
intree = infile.Get("DelayedPhoton")
total_evt = intree.GetEntries()
print("All: {} (100%)".format(total_evt))
selection = ""
if "GMSB" in argv[1]: 
    print("Adding weight for MC ")
    selection = "weight * pileupWeight * triggerEffSFWeight * photonEffSF * "
for i, cut in enumerate(cuts):
    selection += cuts[cut]
    #print(selection)
    evtSelected = intree.GetEntries(selection)
    print("+ {}: {} ({:.2f}%)".format(cut, evtSelected, float(evtSelected)/float(total_evt) * 100.))


