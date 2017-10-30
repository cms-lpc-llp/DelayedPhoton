import copy

VERSION = '17Oct2017'
BOOST_LIMIT_DIR = "/eos/user/j/jkarancs/RazorBoost/datacards/2017_09_20"
BOOST_LOCAL_DIR = "syst_results/run_2017_08_28_syst_combined/cards"

DISP_OFFSET = 12.5 # Extra offset needed for display purposes

ALL_BOXES = ['DiJet', 'MultiJet', 'LeptonJet', 'LeptonMultiJet']
HADRONIC_BOXES = ['DiJet', 'MultiJet']
GLUINO_BOXES = ['MultiJet', 'LeptonMultiJet']
BOOST_BOXES = ['WAna_nj35', 'WAna_nj6', 'TopAna']

class SMS(object):

    def __init__(self, mgMin, mgMax, mchiMin, mchiMax,
            binWidth=25, nRebins=0, xsecMin=1.e-3, xsecMax=10., 
            diagonalOffset=25, smoothing=50, fixLSP0=False,
            boxes=ALL_BOXES, isGluino=True, submodels=None):
        """
        Struct to hold all info associated with one SMS.
        Attributes:
            mgMin, mgMax, mchiMin, mchiMax: mass bounds for limits
            binWidth: granularity of limit scan
            nRebins: number of times to iterate swiss cross interpolation
            xsecMin, xsecMax: z range on limit plot
            diagonalOffset: where the diagonal should be located
            smoothing: RBF smoothing parameter for interpolation
            fixLSP0: set to True to avoid smoothing away limit
                behavior at low LSP mass
            boxes: analysis boxes to use for this model
            isGluino: True if this is a gluino SMS
            submodels: lists MC datasets making up this scan
        """
        self.mgMin = mgMin - DISP_OFFSET
        self.mgMax = mgMax + DISP_OFFSET
        self.mchiMin = mchiMin - DISP_OFFSET
        self.mchiMax = mchiMax + DISP_OFFSET
        self.binWidth = binWidth
        self.nRebins = nRebins
        self.xsecMin = xsecMin
        self.xsecMax = xsecMax
        self.diagonalOffset = diagonalOffset + DISP_OFFSET
        self.smoothing = smoothing
        self.fixLSP0 = fixLSP0
        self.boxes = boxes
        self.isGluino = isGluino
        self.submodels = submodels


sms_models = {
        'T1bbbb':SMS(600, 2300, 0, 1650, boxes=HADRONIC_BOXES),
        'T1ttbb':SMS(600, 2300, 0, 1650, boxes=GLUINO_BOXES,
            diagonalOffset=225),
        'T1tttt':SMS(600, 2300, 0, 1650, boxes=GLUINO_BOXES,
            diagonalOffset=225),
        'T5ttcc':SMS(600, 2300, 0, 1650, boxes=GLUINO_BOXES,
            submodels=[
                'T5ttcc',
                'T5ttcc_mGluino1750to2300',
                ]),
        'T1qqqq':SMS(600, 2300, 0, 1650, boxes=HADRONIC_BOXES),
        'T2bb':SMS(100, 1500, 0, 800, boxes=HADRONIC_BOXES,
            isGluino=False),
        'T2bt':SMS(100, 1500, 0, 800, isGluino=False),
        'T2tt':SMS(100, 1500, 0, 800, isGluino=False,
            diagonalOffset=75, submodels=[
                'T2tt_dM-10to80_genHT-160_genMET-80',
                'T2tt_mStop-150to250',  
                'T2tt_mStop-250to350',
                'T2tt_mStop-350to400',
                'T2tt_mStop-400to1200',
                ]),
        'T2qq':SMS(100, 1500, 0, 800, boxes=HADRONIC_BOXES,
            isGluino=False),
        }
