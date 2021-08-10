import ROOT as rt
from collections import OrderedDict
from sys import argv
import shlex
import re

lumi_2016 = 35922.0
lumi_2017 = 41530.0
lumi = lumi_2016

cuts = OrderedDict()
cuts['None'] = " 1 "
cuts['nPhoton>1'] = " && n_Photons >1 "
cuts['photonIsEB'] = "&& abs(pho1Eta)<1.4442 "
cuts['photonPT>70'] = "&& pho1Pt > 70 "
cuts['METFilters'] =  " && Flag_HBHENoiseFilter == 1 && Flag_HBHEIsoNoiseFilter ==1 && Flag_goodVertices == 1 && Flag_eeBadScFilter == 1 && Flag_EcalDeadCellTriggerPrimitiveFilter == 1 && Flag_CSCTightHaloFilter == 1  && Flag_badMuonFilter == 1 && Flag_badGlobalMuonFilter == 0 && Flag_duplicateMuonFilter ==0"
cuts['photonR9>0.85'] = "  && pho1R9 > 0.85"
cuts['photonEleVeto'] = " && pho1passEleVeto "
cuts['photonHoverE<0.08'] = " && pho1HoverE < 0.08"
cuts['photonIetaeta<0.024'] = " && pho1SigmaIetaIeta < 0.024"
#cuts['photonSminor<0.4'] = " && pho1Sminor < 0.4"
#cuts['photonSmajor'] = " && pho1passSmajorTight" 
#cuts['photonIsolationTight'] = " && pho1passIsoTight_comboIso "
cuts['nJets>2'] = " && n_Jets > 2 "
#cuts['HT'] = " && HT > 400"
#cuts['HT'] = " && ((n_Photons == 1 && (HT - pho1Pt) > 400) || (n_Photons >=2 && (HT - pho1Pt -pho2Pt) > 400))"
cuts['Trigger'] = " && HLTDecision[81] == 1"
cuts['DNN'] = " && pho1DNN > 0.0890 "
#cuts['photonTriggerCut'] = " && abs(pho1ecalPFClusterIso) < (5+0.01*pho1Pt) && abs(pho1hcalPFClusterIso) < (12.5+0.03*pho1Pt+3.0e-5*pho1Pt*pho1Pt) && abs(pho1trkSumPtHollowConeDR03) < (6+2.0e-3*pho1Pt) "
#cuts['pho2cuts'] = " && (pho2Pt > 40 && (abs(pho2Eta) < 1.4442 || (abs(pho2Eta) > 1.566 && abs(pho2Eta) < 2.5))) && abs(pho2ecalPFClusterIso) < 30.0 && abs(pho2hcalPFClusterIso) < 30.0 && abs(pho2trkSumPtHollowConeDR03) < 30.0 "
#cuts['nPhoton==1'] = " && n_Photons == 1 "

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

    model_to_find="L-"+str(Lambda)+"TeV_Ctau-"+Ctau_this+"cm"
    print("Finding model {}".format(model_to_find))
    with open("/storage/af/user/qnguyen/DelayedPhoton/CMSSW_10_6_12/src/DelayedPhotonID/data/XsecBR.dat","r") as xsec_file:
        for this_model in xsec_file:
            this_model_array = shlex.split(this_model)
            if this_model_array[0] == model_to_find:
                #print this_model
                fxsecBR = float(this_model_array[4])
                efxsecBR = float(this_model_array[5])
    #print model_to_find
    return fxsecBR,efxsecBR

def getXS(sample):
    with open("/storage/af/user/qnguyen/DelayedPhoton/CMSSW_10_6_6/src/DelayedPhotonID/data/all_bkg_back.list", "r") as xsfile:
        allxs = xsfile.readlines()
        for xs in allxs:
            if xs.split(' ')[0] in sample:
                return xs.split(' ')[-1].replace('\n','')
    print("[WARNING] {} cross section not found".format(sample))
    return 0

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

if "DiPhoton" in argv[1] or "GJets" in argv[1] or "QCD" in argv[1]:
    xs = getXS(argv[1])
    print("Using cross section of {} for {} with luminosity of {} pb-1".format(xs, argv[1], lumi))
    sumWeights = infile.Get('SumWeights').Integral()
    weight_selection = "weight * pileupWeight * {lumi} * ({xsec} / {sumWeights}) * ".format(lumi=lumi,
                                                                                            xsec=xs,
                                                                                            sumWeights=sumWeights)
    isMC = True

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
    print("+ {}: {:.2f} ({:.2f}%)".format(cut, evtSelected, float(evtSelected)/float(total_evt) * 100.))

