import ROOT as rt
from collections import OrderedDict
from sys import argv
import shlex
import re

lumi_2016 = 35922.0
lumi_2017 = 41530.0
lumi = lumi_2017

cuts = OrderedDict()
cuts['nPhoton>=1'] = " n_Photons >= 1 "
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
cuts['HT'] = " && ((n_Photons == 1 && (HT - pho1Pt) > 400) || (n_Photons >=2 && (HT - pho1Pt -pho2Pt) > 400))"
cuts['Trigger'] = " && HLTDecision[880] == 1"
#cuts['nPhoton>1'] = " && n_Photons > 1 "

def getXsecBR(Lambda, Ctau):
    fxsecBR = 0.0
    efxsecBR = 0.0
    Ctau_this=str(Ctau)
    if Ctau_this == "10.0":
        Ctau_this = "10"
    if Ctau_this == "0.1":
        Ctau_this = "0_1"
    if Ctau_this == "0.01":
        Ctau_this = "0_01"
    if Ctau_this == "0.001":
        Ctau_this = "0_001"

    model_to_find="L"+str(Lambda)+"TeV_Ctau"+Ctau_this+"cm"
    print("Finding model {}".format(model_to_find))
    with open("/storage/user/qnguyen/DelayedPhoton/CMSSW_8_1_0/src/HiggsAnalysis/DelayedPhotonLimit/data/XsecBR.dat","r") as xsec_file:
        for this_model in xsec_file:
            this_model_array = shlex.split(this_model)
            if this_model_array[0] == model_to_find:
                #print this_model
                fxsecBR = float(this_model_array[4])
                efxsecBR = float(this_model_array[5])
    #print model_to_find
    return fxsecBR,efxsecBR

infile = rt.TFile.Open(argv[1],"r")
infile.Print()
intree = infile.Get("DelayedPhoton")
total_evt = intree.GetEntries()
print("All: {} (100%)".format(total_evt))
selection = ""
isMC = False
if "GMSB" in argv[1]: 
    model_name = argv[1].split('/')[-1]
    model_num = re.findall(r'\d+', model_name)
    Lambda = model_num[0]
    ctau = model_num[1]
    xsecBR, _ = getXsecBR(Lambda, ctau)
    print("Adding weight for MC with lambda = {}, ctau = {}".format(Lambda, ctau))
    sumWeights = infile.Get('SumWeights').GetBinContent(1)
    print("xsecBR = {}".format(xsecBR))
    print("sumWeights = {}".format(sumWeights))
    isMC = True
    weight_selection = "weight * pileupWeight * triggerEffSFWeight * photonEffSF * {lumi} * ({xsecBR} / {sumWeights}) * ".format(lumi=lumi,
                                                                                                     xsecBR=xsecBR,
                                                                                                    sumWeights=sumWeights)

for i, cut in enumerate(cuts):
    selection += cuts[cut]
    #print(selection)
    if not isMC:
        evtSelected = intree.GetEntries(selection)
    else:
        all_selection = weight_selection + '(' + selection + ')'
        metHist = rt.TH1F("metHist","",500,0,60000)
        intree.Draw("t1MET>>metHist",all_selection)
        evtSelected = metHist.Integral()
        if i==0: total_evt = evtSelected
        del metHist
    print("+ {}: {} ({:.2f}%)".format(cut, evtSelected, float(evtSelected)/float(total_evt) * 100.))

