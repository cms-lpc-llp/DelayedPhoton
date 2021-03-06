//LOCLAL INCLUDES
#include "DelayedPhotonAnalyzer.h"
#include "JetCorrectorParameters.h"
#include "JetCorrectionUncertainty.h"
#include "RazorHelper.h"
#include "BTagCalibrationStandalone.h"
#include "EnergyScaleCorrection_class.hh"
#include "EnergyScaleCorrection_class_2017.hh"

//C++ includes
#include <sys/stat.h>
#include <random>
//ROOT includes
#include "TH1F.h"
#include "TLorentzVector.h"
#include "TVector3.h"

using namespace std;
const double SPEED_OF_LIGHT = 29.9792458; // speed of light in cm / ns
const float EB_R = 129.7;
const float EE_Z = 317.0;
const double JET_CUT = 30.;
const int NUM_PDF_WEIGHTS = 60;

const bool photonOrderByTime = false;
//const double TR_SMEAR = 0.2210;
const int N_E_divide = 19;
double E_divide[N_E_divide] = {43.0, 46.0, 49.0, 52.0, 55.0, 58.0, 61.0, 64.0, 67.0, 70.0, 73.0, 78.0, 84.0, 91.0, 100.0, 115.0, 140.0, 190.0, 1000.0};
//double timecorr_shift[N_E_divide] = {277.32228254, 275.67500044, 272.10244004, 287.15428262, 294.29875716, 287.44070277, 282.95400642, 279.80934988, 282.70083441, 277.48972614, 275.41563559, 274.64132692, 268.13864834, 266.62392304, 270.24297452, 260.13781686, 263.16768474, 242.21320465, 181.26510246};
double timecorr_shift[N_E_divide] = {279.9466476,  278.14972231, 289.29761875, 289.53508063, 294.00756053, 285.88226868, 286.03238378, 281.17150628, 282.09074926, 277.63137454, 274.44859489, 276.70782472, 271.64726448, 272.08565454, 261.00671411, 260.43733686, 258.90569305, 250.88234587, 188.61409597};

//double timecorr_smear_aa = 6591.9*6591.9 - 6536.8*6536.8;
double timecorr_smear_aa = 6408.7*6408.7 - 6143.0*6143.0;
//double timecorr_smear_bb = 2.0*211.1*211.1 - 2.0*96.2*96.2;
double timecorr_smear_bb = 2.0*289.1*289.1 - 2.0*168.8*168.8;

#define _phodebug 0

TVector3 DelayedPhotonAnalyzer::intersectPoint(float x0,float y0,float z0,float px,float py,float pz,float R)
{
  TVector3 sol;


  float x1,y1,z1;
  float x2,y2,z2;

  if((px*px*py*py*R*R + py*py*py*py*R*R - py*py*py*py*x0*x0 + 2.0*px*py*py*py*x0*y0 - px*px*py*py*y0*y0) > 0.0 )
  {
  y1 = (-px*py*x0 + px*px*y0)/(px*px+py*py) - pow((px*px*py*py*R*R + py*py*py*py*R*R - py*py*py*py*x0*x0 + 2.0*px*py*py*py*x0*y0 - px*px*py*py*y0*y0),0.5) / (px*px+py*py);
  x1 =  x0 + (px/py) * (y1-y0);
  z1 =  z0 + (pz/py) * (y1-y0);

  y2 = (-px*py*x0 + px*px*y0)/(px*px+py*py) + pow((px*px*py*py*R*R + py*py*py*py*R*R - py*py*py*py*x0*x0 + 2.0*px*py*py*py*x0*y0 - px*px*py*py*y0*y0),0.5) / (px*px+py*py); 
  x2 =  x0 + (px/py) * (y2-y0);
  z2 =  z0 + (pz/py) * (y2-y0);
  }
 
  else
  {
   x1=0,y1=0,z1=0,x2=0,y2=0,z2=0; 
  }


  if( (z1-z0)*pz > 0.0 ) 
  {
	sol.SetXYZ(x1,y1,z1);
  }

  else if( (z2-z0)*pz > 0.0 )
  {
	sol.SetXYZ(x2,y2,z2);
  }

  else
  {
	sol.SetXYZ(0,0,0);
  }	
  return sol;
};


float DelayedPhotonAnalyzer::getADCToGeV( uint run, int isFromEB) {
  double ADCToGeV = 0;
  //EB
  if (isFromEB == 1)  ADCToGeV = 0.039510;
  
  //EE
  else if (isFromEB == 0) ADCToGeV = 0.068182;
  
  return ADCToGeV;
}


void DelayedPhotonAnalyzer::Analyze(bool isData, int option, string outFileName, string label) {

  //isData = false;//////remember to delete this when we are dealing with data.....

  //*****************************************************************************
  //Settings
  //*****************************************************************************
  TRandom3 random(3003);
  bool doPhotonScaleCorrection = true;

  string analysisTag = "Razor2017_31Mar2018Rereco_DelayedPhoton";
  if ( label != "") analysisTag = label;

  if ( label != "") analysisTag = label;
  
  RazorHelper *helper = 0;
  RazorHelper *helper_GED = 0;
  helper = new RazorHelper(analysisTag, isData, false); 
  helper_GED = new RazorHelper("Razor2017_31Mar2018Rereco", isData, false); 
 
  //Get CMSSW Directory
  char* cmsswPath;
  cmsswPath = getenv("CMSSW_BASE");

  //--------------------------------
  //Photon Energy Scale and Resolution Corrections
  //--------------------------------
  
  std::string photonCorrectionPath = "./";
  if ( cmsswPath != NULL ) photonCorrectionPath = string(cmsswPath) + "/src/DelayedPhoton/data/PhotonCorrections/";
  std::string photonCorrectionFile = photonCorrectionPath + "/Run2017_17Nov2017_v1_ele_unc";
  EnergyScaleCorrection_class_2017 *photonCorrector = 0;
  photonCorrector = new EnergyScaleCorrection_class_2017(photonCorrectionFile);
  
  if(!isData) {
    photonCorrector->doScale = false;
    photonCorrector->doSmearings = true;
  } else {
    photonCorrector->doScale = true;
    photonCorrector->doSmearings = false;
  }


//  //*****************************************************************************
//  //Load Pedestals
//  //*****************************************************************************
//  vector <uint> start_time;//start run of all IOV 
//  vector <uint> end_time;//end run of all IOV
//  start_time_tmp=0; 
//  end_time_tmp=0;
//  rms_G12_all=0;
//  detID_all=0 ;
//
//  //std::cout<< "[DEBUG] opening f_pedestal"<<endl; 
//  //TFile *f_pedestal = TFile::Open("root://cms-xrd-global.cern.ch//store/group/phys_susy/razor/EcalTiming/EcalPedestals_Legacy2016_time_v1/tree_EcalPedestals_Legacy2016_time_v1.root","READ"); // use this if you run on lxplus
//  TFile *f_pedestal = 0;//TFile::Open("/mnt/hadoop/store/group/phys_susy/razor/Run2Analysis/EcalTiming/EcalPedestals_Legacy2016_time_v1/tree_EcalPedestals_Legacy2016_time_v1.root","READ"); // use this if you run on Caltech T2
//  TTree *tree_pedestal = 0;//(TTree*)f_pedestal->Get("pedestal");
//  
//  //TFile *f_pedestal = new TFile("tree_EcalPedestals_Legacy2016_time_v1_G12rmsonly.root","READ");
//  //TTree *tree_pedestal = (TTree*)f_pedestal->Get("pedestal");
//
//  if(isData)
//  { 
//	  f_pedestal = TFile::Open("/mnt/hadoop/store/group/phys_susy/razor/Run2Analysis/EcalTiming/EcalPedestals_Legacy2016_time_v1/tree_EcalPedestals_Legacy2016_time_v1_G12rmsonly.root","READ"); // use this if you run on Caltech T2
//	  //f_pedestal = new TFile("tree_EcalPedestals_Legacy2016_time_v1_G12rmsonly.root","READ"); // use this if you run on Caltech T2
//	  tree_pedestal = (TTree*)f_pedestal->Get("pedestal");
//	  tree_pedestal->SetBranchAddress("start_time_second", &start_time_tmp);
//	  tree_pedestal->SetBranchAddress("end_time_second", &end_time_tmp);
//	  tree_pedestal->SetBranchAddress("rms_G12", &rms_G12_all);
//	  tree_pedestal->SetBranchAddress("detID", &detID_all);
//	  int N_entries_pedestal = tree_pedestal->GetEntries();
// 
//
//	  cout << "Total Pedestal IOVs: " << N_entries_pedestal << "\n";
//	  for(int i=0;i<N_entries_pedestal;i++) {
//	    cout << "Loading Pedestal IOV " << i << "\n";
//	    tree_pedestal->GetEntry(i);
//	    start_time.push_back(start_time_tmp);
//	    end_time.push_back(end_time_tmp);
//	  }
//
//}

  // //test 
  // uint test_time = 1464000000;
  // //cout<<"EB test..."<<endl;
  // for(int ieta=-85;ieta<=85 && ieta!=0;ieta++) {
  //   for(int iphi=1;iphi<=360;iphi++) {
  //     int detID = detID_from_iEtaiPhi(ieta, iphi, true, false);
  //     cout<<test_time<<"  "<<ieta<<"  "<<iphi<<"  "<<detID;      
  //     float pedestalRMS = getPedestalNoise(tree_pedestal, start_time,end_time,test_time, detID);
  //     cout << "   " << pedestalRMS << endl;      
  //   }
  // }
  
  
  //*****************************************************************************
  //Open Output File
  //*****************************************************************************
  if ( outFileName.empty() ) {
    std::cout << "DelayedPhotonAnalyzer: Output filename not specified!" << endl << "Using default output name DelayedPhoton.root" << std::endl;
    outFileName = "DelayedPhoton.root";
  }
  TFile* outFile = new TFile( outFileName.c_str(), "RECREATE" );


  //---------------------------
  //one tree to hold all events
  //---------------------------
  TTree *outputTree = new TTree("DelayedPhoton", "Delayed photon events");


  int NPU;
  int nLooseMuons, nTightMuons;
  unsigned int run, lumi, event;
  float genVertexTime = 0.0;//genVertexT;
  float weight;
  float pileupWeight, pileupWeightUp, pileupWeightDown;
  float photonEffSF; 
  float triggerEffWeight;
  float triggerEffSFWeight;
  float ISRSystWeightUp, ISRSystWeightDown;
  float sf_facScaleUp, sf_facScaleDown;
  float sf_renScaleUp, sf_renScaleDown;
  float sf_facRenScaleUp, sf_facRenScaleDown;
  std::vector<float> sf_pdf;

  float TOF_total1;
  float TOF_total2;
  float TOF_total1_genV;
  float TOF_total2_genV;
  float TOF_neu1, TOF_neu2;
  float TOF_neu1_RF, TOF_neu2_RF;
  float TOF_pho1, TOF_pho2;
  
  int n_Photons;
  int n_Photons_reco;
  float pho1E, pho1Pt, pho1Pt_scaleUp, pho1Pt_scaleDown, pho1Pt_smearUp, pho1Pt_smearDown, pho1Eta, pho1Phi, pho1SeedE, pho1SeedPt, pho1SeedEta, pho1SeedPhi, pho1SC_E, pho1SC_Pt, pho1SC_Eta, pho1SC_Phi, pho1angle_xtal, pho1SigmaIetaIeta, pho1R9, pho1HoverE, pho1sumChargedHadronPt, pho1sumNeutralHadronEt, pho1sumPhotonEt, pho1PFsumChargedHadronPt, pho1PFsumNeutralHadronEt, pho1PFsumPhotonEt, pho1ecalPFClusterIso, pho1hcalPFClusterIso, pho1trkSumPtHollowConeDR03, pho1sigmaEOverE, pho1SeedTimeRaw, pho1SeedTimeCalib, pho1SeedTimeCalibTOF, pho1SeedTimeGenV, pho1ClusterTime, pho1ClusterTime_SmearToData, pho1Sminor, pho1Smajor, pho1Setaeta, pho1Sphiphi, pho1Setaphi, pho1GenE, pho1GenPt, pho1GenEta, pho1GenPhi, pho1ClusterTime_scaleUp, pho1ClusterTime_scaleDown, pho1ClusterTime_smearUp, pho1ClusterTime_smearDown;
  float pho2E, pho2Pt, pho2Pt_scaleUp, pho2Pt_scaleDown, pho2Pt_smearUp, pho2Pt_smearDown, pho2Eta, pho2Phi, pho2SeedE, pho2SeedPt, pho2SeedEta, pho2SeedPhi, pho2SC_E, pho2SC_Pt, pho2SC_Eta, pho2SC_Phi, pho2angle_xtal, pho2SigmaIetaIeta, pho2R9, pho2HoverE, pho2sumChargedHadronPt, pho2sumNeutralHadronEt, pho2sumPhotonEt, pho2PFsumChargedHadronPt, pho2PFsumNeutralHadronEt, pho2PFsumPhotonEt, pho2ecalPFClusterIso, pho2hcalPFClusterIso, pho2trkSumPtHollowConeDR03, pho2sigmaEOverE, pho2SeedTimeRaw, pho2SeedTimeCalib, pho2SeedTimeCalibTOF, pho2SeedTimeGenV, pho2ClusterTime, pho2ClusterTime_SmearToData, pho2Smajor, pho2Sminor, pho2Setaeta, pho2Sphiphi, pho2Setaphi, pho2GenE, pho2GenPt, pho2GenEta, pho2GenPhi;
  bool pho1passEleVeto, pho1passTrackVeto, pho1passIsoLoose, pho1passIsoMedium, pho1passIsoTight, pho1isStandardPhoton, pho1isPromptPhoton, pho1isDelayedPhoton;
  bool pho1passIsoLoose_privatePF, pho1passIsoMedium_privatePF, pho1passIsoTight_privatePF;
  bool pho1passIsoLoose_OOT, pho1passIsoMedium_OOT, pho1passIsoTight_OOT;
  bool pho1passIsoLoose_comboIso, pho1passIsoMedium_comboIso, pho1passIsoTight_comboIso;
  bool pho2passEleVeto, pho2passIsoLoose, pho2passIsoMedium, pho2passIsoTight, pho2isStandardPhoton, pho2isPromptPhoton, pho2isDelayedPhoton;
  bool pho2passIsoLoose_privatePF, pho2passIsoMedium_privatePF, pho2passIsoTight_privatePF;
  bool pho2passIsoLoose_OOT, pho2passIsoMedium_OOT, pho2passIsoTight_OOT;
  bool pho2passIsoLoose_comboIso, pho2passIsoMedium_comboIso, pho2passIsoTight_comboIso;
  bool pho1passHoverELoose, pho1passHoverEMedium, pho1passHoverETight;
  bool pho2passHoverELoose, pho2passHoverEMedium, pho2passHoverETight;
  bool pho1passSigmaIetaIetaLoose, pho1passSigmaIetaIetaMedium, pho1passSigmaIetaIetaTight;
  bool pho2passSigmaIetaIetaLoose, pho2passSigmaIetaIetaMedium, pho2passSigmaIetaIetaTight;
  bool pho1passSmajorLoose, pho1passSmajorMedium, pho1passSmajorTight;
  bool pho2passSmajorLoose, pho2passSmajorMedium, pho2passSmajorTight;
  bool pho1passSminorLoose, pho1passSminorMedium, pho1passSminorTight;
  bool pho2passSminorLoose, pho2passSminorMedium, pho2passSminorTight;

  // XYZ rechit where photon is detected
  float pho1SeedX;
  float pho1SeedY;
  float pho1SeedZ;
  float pho2SeedX;
  float pho2SeedY;
  float pho2SeedZ;
  
  bool hasJetL1PreFiring;
  int n_Jets;
  int n_Jets_JESUp, n_Jets_JESDown;
  float jet1E, jet1Pt, jet1Eta, jet1Phi;
  float jet2E, jet2Pt, jet2Eta, jet2Phi;

  float MET, t1MET, MET_JESUp, MET_JESDown, t1MET_JESUp, t1MET_JESDown, t1MET_phoScaleUp, t1MET_phoScaleDown, t1MET_phoSmearUp, t1MET_phoSmearDown;
  float HT;

  float deltaR_pho12;
  float deltaPt_pho1, deltaPt_pho2;
  float deltaR_pho1, deltaR_pho2;
  float deltaEta_pho1, deltaEta_pho2;
  float deltaPhi_pho1, deltaPhi_pho2;
  float reco_eta1, reco_eta2;
  float gen_eta1, gen_eta2;
  float R1, R2;
  float pho1_genVtxX, pho2_genVtxX;
  float pho1_genVtxY, pho2_genVtxY;
  float pho1_genVtxZ, pho2_genVtxZ;
  float pho1_genVtxEta, pho2_genVtxEta;
  float pho1_genVtxPhi, pho2_genVtxPhi;
  float ZD1, ZD2;

  //leptons
  float lep1Pt, lep2Pt, mll;
  Int_t lep1Type, lep2Type;


  //MET filters
  outputTree->Branch("Flag_HBHENoiseFilter", &Flag_HBHENoiseFilter, "Flag_HBHENoiseFilter/O");
  outputTree->Branch("Flag_HBHEIsoNoiseFilter", &Flag_HBHEIsoNoiseFilter, "Flag_HBHEIsoNoiseFilter/O");
  //outputTree->Branch("Flag_badChargedCandidateFilter", &Flag_badChargedCandidateFilter, "Flag_badChargedCandidateFilter/O");
  outputTree->Branch("Flag_badChargedCandidateFilter", &Flag_BadChargedCandidateFilter, "Flag_badChargedCandidateFilter/O");
  //outputTree->Branch("Flag_badMuonFilter", &Flag_badMuonFilter, "Flag_badMuonFilter/O");
  outputTree->Branch("Flag_badMuonFilter", &Flag_BadPFMuonFilter, "Flag_badMuonFilter/O");
  outputTree->Branch("Flag_badGlobalMuonFilter", &Flag_badGlobalMuonFilter, "Flag_badGlobalMuonFilter/O");
  outputTree->Branch("Flag_duplicateMuonFilter", &Flag_duplicateMuonFilter, "Flag_duplicateMuonFilter/O");
  outputTree->Branch("Flag_CSCTightHaloFilter", &Flag_CSCTightHaloFilter, "Flag_CSCTightHaloFilter/O");
  outputTree->Branch("Flag_hcalLaserEventFilter", &Flag_hcalLaserEventFilter, "Flag_hcalLaserEventFilter/O");
  outputTree->Branch("Flag_EcalDeadCellTriggerPrimitiveFilter", &Flag_EcalDeadCellTriggerPrimitiveFilter, "Flag_EcalDeadCellTriggerPrimitiveFilter/O");
  outputTree->Branch("Flag_goodVertices", &Flag_goodVertices, "Flag_goodVertices/O");
  outputTree->Branch("Flag_trackingFailureFilter", &Flag_trackingFailureFilter, "Flag_trackingFailureFilter/O");
  outputTree->Branch("Flag_eeBadScFilter", &Flag_eeBadScFilter, "Flag_eeBadScFilter/O");
  outputTree->Branch("Flag_ecalLaserCorrFilter", &Flag_ecalLaserCorrFilter, "Flag_ecalLaserCorrFilter/O");
  outputTree->Branch("Flag_trkPOGFilters", &Flag_trkPOGFilters, "Flag_trkPOGFilters/O");
  outputTree->Branch("Flag_trkPOG_manystripclus53X", &Flag_trkPOG_manystripclus53X, "Flag_trkPOG_manystripclus53X/O");
  outputTree->Branch("Flag_trkPOG_toomanystripclus53X", &Flag_trkPOG_toomanystripclus53X, "Flag_trkPOG_toomanystripclus53X/O");
  outputTree->Branch("Flag_trkPOG_logErrorTooManyClusters", &Flag_trkPOG_logErrorTooManyClusters, "Flag_trkPOG_logErrorTooManyClusters/O");
  outputTree->Branch("Flag_METFilters", &Flag_METFilters, "Flag_METFilters/O");


  outputTree->Branch("run", &run, "run/i");
  outputTree->Branch("lumi", &lumi, "lumi/i");
  outputTree->Branch("event", &event, "event/i");
  if (!isData)
  {
      outputTree->Branch("weight", &weight, "weight/F");
      outputTree->Branch("pileupWeight", &pileupWeight, "pileupWeight/F");
      outputTree->Branch("pileupWeightUp", &pileupWeightUp, "pileupWeightUp/F");
      outputTree->Branch("pileupWeightDown", &pileupWeightDown, "pileupWeightDown/F");
      //outputTree->Branch("pdfWeights", "std::vector<float>",&pdfWeights);
      outputTree->Branch("sf_pdf", "std::vector<float>",&sf_pdf);
      outputTree->Branch("NPU", &NPU, "npu/i");
  }
  outputTree->Branch("triggerEffWeight", &triggerEffWeight, "triggerEffWeight/F");
  outputTree->Branch("triggerEffSFWeight", &triggerEffSFWeight, "triggerEffSFWeight/F");
  outputTree->Branch("photonEffSF", &photonEffSF, "photonEffSF/F");
  outputTree->Branch("ISRSystWeightUp", &ISRSystWeightUp, "ISRSystWeightUp/F");
  outputTree->Branch("ISRSystWeightDown", &ISRSystWeightDown, "ISRSystWeightDown/F");
  outputTree->Branch("sf_facScaleUp", &sf_facScaleUp, "sf_facScaleUp/F");
  outputTree->Branch("sf_facScaleDown", &sf_facScaleDown, "sf_facScaleDown/F");
  outputTree->Branch("sf_renScaleUp", &sf_renScaleUp, "sf_renScaleUp/F");
  outputTree->Branch("sf_renScaleDown", &sf_renScaleDown, "sf_renScaleDown/F");
  outputTree->Branch("sf_facRenScaleUp", &sf_facRenScaleUp, "sf_facRenScaleUp/F");
  outputTree->Branch("sf_facRenScaleDown", &sf_facRenScaleDown, "sf_facRenScaleDown/F");

  outputTree->Branch("nLooseMuons", &nLooseMuons, "npu/i");
  outputTree->Branch("nTightMuons", &nTightMuons, "npu/i");
  outputTree->Branch("fixedGridRhoFastjetAll", &fixedGridRhoFastjetAll, "fixedGridRhoFastjetAll/F");
  outputTree->Branch("fixedGridRhoFastjetAllCalo", &fixedGridRhoFastjetAllCalo, "fixedGridRhoFastjetAllCalo/F");
  outputTree->Branch("pvX", &pvX, "pvX/F");
  outputTree->Branch("pvY", &pvY, "pvY/F");
  outputTree->Branch("pvZ", &pvZ, "pvZ/F");

  outputTree->Branch("genVertexX", &genVertexX, "genVertexX/F");
  outputTree->Branch("genVertexY", &genVertexY, "genVertexY/F");
  outputTree->Branch("genVertexZ", &genVertexZ, "genVertexZ/F");
  outputTree->Branch("genVertexTime", &genVertexTime, "genVertexTime/F");
  
  outputTree->Branch("TOF_total1", &TOF_total1, "TOF_total1/F");
  outputTree->Branch("TOF_total2", &TOF_total2, "TOF_total2/F");
  outputTree->Branch("TOF_total1_genV", &TOF_total1_genV, "TOF_total1_genV/F");
  outputTree->Branch("TOF_total2_genV", &TOF_total2_genV, "TOF_total2_genV/F");
  outputTree->Branch("TOF_neu1", &TOF_neu1, "TOF_neu1/F");
  outputTree->Branch("TOF_neu1_RF", &TOF_neu1_RF, "TOF_neu1_RF/F");
  outputTree->Branch("TOF_neu2", &TOF_neu2, "TOF_neu2/F");
  outputTree->Branch("TOF_neu2_RF", &TOF_neu2_RF, "TOF_neu2_RF/F");
  outputTree->Branch("TOF_pho1", &TOF_pho1, "TOF_pho1/F");
  outputTree->Branch("TOF_pho2", &TOF_pho2, "TOF_pho2/F");

  outputTree->Branch("n_Photons", &n_Photons, "n_Photons/I"); // 1 or 2
  outputTree->Branch("n_Photons_reco", &n_Photons_reco, "n_Photons_reco/I"); // 1 or 2
  outputTree->Branch("nPhotons_overlap", &nPhotons_overlap, "nPhotons_overlap/I"); // 1 or 2
  outputTree->Branch("pho1E", &pho1E, "pho1E/F");
  outputTree->Branch("pho1Pt", &pho1Pt, "pho1Pt/F");
  outputTree->Branch("pho1Pt_scaleUp", &pho1Pt_scaleUp, "pho1Pt_scaleUp/F");
  outputTree->Branch("pho1Pt_scaleDown", &pho1Pt_scaleDown, "pho1Pt_scaleDown/F");
  outputTree->Branch("pho1Pt_smearUp", &pho1Pt_smearUp, "pho1Pt_smearUp/F");
  outputTree->Branch("pho1Pt_smearDown", &pho1Pt_smearDown, "pho1Pt_smearDown/F");
  outputTree->Branch("pho1Eta", &pho1Eta, "pho1Eta/F");
  outputTree->Branch("pho1Phi", &pho1Phi, "pho1Phi/F");  
  outputTree->Branch("pho1SeedX", &pho1SeedX, "pho1SeedX/F");
  outputTree->Branch("pho1SeedY", &pho1SeedY, "pho1SeedY/F");
  outputTree->Branch("pho1SeedZ", &pho1SeedZ, "pho1SeedZ/F");
  outputTree->Branch("pho1SeedE", &pho1SeedE, "pho1SeedE/F");
  outputTree->Branch("pho1SeedPt", &pho1SeedPt, "pho1SeedPt/F");
  outputTree->Branch("pho1SeedEta", &pho1SeedEta, "pho1SeedEta/F");
  outputTree->Branch("pho1SeedPhi", &pho1SeedPhi, "pho1SeedPhi/F");
  outputTree->Branch("pho1SC_E", &pho1SC_E, "pho1SC_E/F");
  outputTree->Branch("pho1SC_Pt", &pho1SC_Pt, "pho1SC_Pt/F");
  outputTree->Branch("pho1SC_Eta", &pho1SC_Eta, "pho1SC_Eta/F");
  outputTree->Branch("pho1SC_Phi", &pho1SC_Phi, "pho1SC_Phi/F");
  outputTree->Branch("pho1isStandardPhoton", &pho1isStandardPhoton, "pho1isStandardPhoton/O");
  outputTree->Branch("pho1isPromptPhoton", &pho1isPromptPhoton, "pho1isPromptPhoton/O");
  outputTree->Branch("pho1isDelayedPhoton", &pho1isDelayedPhoton, "pho1isDelayedPhoton/O");
  outputTree->Branch("pho1angle_xtal", &pho1angle_xtal, "pho1angle_xtal/F");
  outputTree->Branch("pho1SigmaIetaIeta", &pho1SigmaIetaIeta, "pho1SigmaIetaIeta/F");
  outputTree->Branch("pho1R9", &pho1R9, "pho1R9/F");
  outputTree->Branch("pho1HoverE", &pho1HoverE, "pho1HoverE/F");
  outputTree->Branch("pho1sumChargedHadronPt", &pho1sumChargedHadronPt, "pho1sumChargedHadronPt/F");
  outputTree->Branch("pho1PFsumChargedHadronPt", &pho1PFsumChargedHadronPt, "pho1PFsumChargedHadronPt/F");
  outputTree->Branch("pho1sumNeutralHadronEt", &pho1sumNeutralHadronEt, "pho1sumNeutralHadronEt/F");
  outputTree->Branch("pho1PFsumNeutralHadronEt", &pho1PFsumNeutralHadronEt, "pho1PFsumNeutralHadronEt/F");
  outputTree->Branch("pho1sumPhotonEt", &pho1sumPhotonEt, "pho1sumPhotonEt/F");
  outputTree->Branch("pho1PFsumPhotonEt", &pho1PFsumPhotonEt, "pho1PFsumPhotonEt/F");
  outputTree->Branch("pho1ecalPFClusterIso", &pho1ecalPFClusterIso, "pho1ecalPFClusterIso/F");
  outputTree->Branch("pho1hcalPFClusterIso", &pho1hcalPFClusterIso, "pho1hcalPFClusterIso/F");
  outputTree->Branch("pho1trkSumPtHollowConeDR03", &pho1trkSumPtHollowConeDR03, "pho1trkSumPtHollowConeDR03/F");
  outputTree->Branch("pho1sigmaEOverE", &pho1sigmaEOverE, "pho1sigmaEOverE/F");
  outputTree->Branch("pho1passEleVeto", &pho1passEleVeto, "pho1passEleVeto/O");
  outputTree->Branch("pho1passTrackVeto", &pho1passTrackVeto, "pho1passTrackVeto/O");
  outputTree->Branch("pho1passIsoLoose", &pho1passIsoLoose, "pho1passIsoLoose/O");
  outputTree->Branch("pho1passIsoLoose_privatePF", &pho1passIsoLoose_privatePF, "pho1passIsoLoose_privatePF/O");
  outputTree->Branch("pho1passIsoLoose_OOT", &pho1passIsoLoose_OOT, "pho1passIsoLoose_OOT/O");
  outputTree->Branch("pho1passIsoMedium", &pho1passIsoMedium, "pho1passIsoMedium/O");
  outputTree->Branch("pho1passIsoMedium_privatePF", &pho1passIsoMedium_privatePF, "pho1passIsoMedium_privatePF/O");
  outputTree->Branch("pho1passIsoMedium_OOT", &pho1passIsoMedium_OOT, "pho1passIsoMedium_OOT/O");
  outputTree->Branch("pho1passIsoTight", &pho1passIsoTight, "pho1passIsoTight/O");
  outputTree->Branch("pho1passIsoTight_privatePF", &pho1passIsoTight_privatePF, "pho1passIsoTight_privatePF/O");
  outputTree->Branch("pho1passIsoTight_OOT", &pho1passIsoTight_OOT, "pho1passIsoTight_OOT/O");
  
  outputTree->Branch("pho1passIsoLoose_comboIso", &pho1passIsoLoose_comboIso, "pho1passIsoLoose_comboIso/O");
  outputTree->Branch("pho1passIsoMedium_comboIso", &pho1passIsoMedium_comboIso, "pho1passIsoMedium_comboIso/O");
  outputTree->Branch("pho1passIsoTight_comboIso", &pho1passIsoTight_comboIso, "pho1passIsoTight_comboIso/O");
  outputTree->Branch("pho1passHoverELoose", &pho1passHoverELoose, "pho1passHoverELoose/O");
  outputTree->Branch("pho1passHoverEMedium", &pho1passHoverEMedium, "pho1passHoverEMedium/O");
  outputTree->Branch("pho1passHoverETight", &pho1passHoverETight, "pho1passHoverETight/O");
  outputTree->Branch("pho1passSigmaIetaIetaLoose", &pho1passSigmaIetaIetaLoose, "pho1passSigmaIetaIetaLoose/O");
  outputTree->Branch("pho1passSigmaIetaIetaMedium", &pho1passSigmaIetaIetaMedium, "pho1passSigmaIetaIetaMedium/O");
  outputTree->Branch("pho1passSigmaIetaIetaTight", &pho1passSigmaIetaIetaTight, "pho1passSigmaIetaIetaTight/O");
  outputTree->Branch("pho1passSmajorLoose", &pho1passSmajorLoose, "pho1passSmajorLoose/O");
  outputTree->Branch("pho1passSmajorMedium", &pho1passSmajorMedium, "pho1passSmajorMedium/O");
  outputTree->Branch("pho1passSmajorTight", &pho1passSmajorTight, "pho1passSmajorTight/O");
  outputTree->Branch("pho1passSminorLoose", &pho1passSminorLoose, "pho1passSminorLoose/O");
  outputTree->Branch("pho1passSminorMedium", &pho1passSminorMedium, "pho1passSminorMedium/O");
  outputTree->Branch("pho1passSminorTight", &pho1passSminorTight, "pho1passSminorTight/O");
  outputTree->Branch("pho1SeedTimeRaw", &pho1SeedTimeRaw, "pho1SeedTimeRaw/F");
  outputTree->Branch("pho1SeedTimeCalib", &pho1SeedTimeCalib, "pho1SeedTimeCalib/F");
  outputTree->Branch("pho1SeedTimeCalibTOF", &pho1SeedTimeCalibTOF, "pho1SeedTimeCalibTOF/F");
  outputTree->Branch("pho1SeedTimeGenV", &pho1SeedTimeGenV, "pho1SeedTimeGenV/F");
  outputTree->Branch("pho1ClusterTime", &pho1ClusterTime, "pho1ClusterTime/F");
  outputTree->Branch("pho1ClusterTime_SmearToData", &pho1ClusterTime_SmearToData, "pho1ClusterTime_SmearToData/F");
  outputTree->Branch("pho1ClusterTime_scaleUp", &pho1ClusterTime_scaleUp, "pho1ClusterTime_scaleUp/F");
  outputTree->Branch("pho1ClusterTime_scaleDown", &pho1ClusterTime_scaleDown, "pho1ClusterTime_scaleDown/F");
  outputTree->Branch("pho1ClusterTime_smearUp", &pho1ClusterTime_smearUp, "pho1ClusterTime_smearUp/F");
  outputTree->Branch("pho1ClusterTime_smearDown", &pho1ClusterTime_smearDown, "pho1ClusterTime_smearDown/F");
  outputTree->Branch("pho1Sminor", &pho1Sminor, "pho1Sminor/F");
  outputTree->Branch("pho1Smajor", &pho1Smajor, "pho1Smajor/F");
  outputTree->Branch("pho1Setaeta", &pho1Setaeta, "pho1Setaeta/F");
  outputTree->Branch("pho1Sphiphi", &pho1Sphiphi, "pho1Sphiphi/F");
  outputTree->Branch("pho1Setaphi", &pho1Setaphi, "pho1Setaphi/F");
  outputTree->Branch("pho1GenE", &pho1GenE, "pho1GenE/F");
  outputTree->Branch("pho1GenPt", &pho1GenPt, "pho1GenPt/F");
  outputTree->Branch("pho1GenEta", &pho1GenEta, "pho1GenEta/F");
  outputTree->Branch("pho1GenPhi", &pho1GenPhi, "pho1GenPhi/F");

  outputTree->Branch("pho2E", &pho2E, "pho2E/F");
  outputTree->Branch("pho2Pt", &pho2Pt, "pho2Pt/F");
  outputTree->Branch("pho2Pt_scaleUp", &pho2Pt_scaleUp, "pho2Pt_scaleUp/F");
  outputTree->Branch("pho2Pt_scaleDown", &pho2Pt_scaleDown, "pho2Pt_scaleDown/F");
  outputTree->Branch("pho2Pt_smearUp", &pho2Pt_smearUp, "pho2Pt_smearUp/F");
  outputTree->Branch("pho2Pt_smearDown", &pho2Pt_smearDown, "pho2Pt_smearDown/F");
  outputTree->Branch("pho2Eta", &pho2Eta, "pho2Eta/F");
  outputTree->Branch("pho2Phi", &pho2Phi, "pho2Phi/F");  
  outputTree->Branch("pho2SeedX", &pho2SeedX, "pho2SeedX/F");
  outputTree->Branch("pho2SeedY", &pho2SeedY, "pho2SeedY/F");
  outputTree->Branch("pho2SeedZ", &pho2SeedZ, "pho2SeedZ/F");
  outputTree->Branch("pho2SeedE", &pho2SeedE, "pho2SeedE/F");
  outputTree->Branch("pho2SeedPt", &pho2SeedPt, "pho2SeedPt/F");
  outputTree->Branch("pho2SeedEta", &pho2SeedEta, "pho2SeedEta/F");
  outputTree->Branch("pho2SeedPhi", &pho2SeedPhi, "pho2SeedPhi/F");
  outputTree->Branch("pho2SC_E", &pho2SC_E, "pho2SC_E/F");
  outputTree->Branch("pho2SC_Pt", &pho2SC_Pt, "pho2SC_Pt/F");
  outputTree->Branch("pho2SC_Eta", &pho2SC_Eta, "pho2SC_Eta/F");
  outputTree->Branch("pho2SC_Phi", &pho2SC_Phi, "pho2SC_Phi/F");
  outputTree->Branch("pho2isStandardPhoton", &pho2isStandardPhoton, "pho2isStandardPhoton/O");
  outputTree->Branch("pho2isPromptPhoton", &pho2isPromptPhoton, "pho2isPromptPhoton/O");
  outputTree->Branch("pho2isDelayedPhoton", &pho2isDelayedPhoton, "pho2isDelayedPhoton/O");
  outputTree->Branch("pho2angle_xtal", &pho2angle_xtal, "pho2angle_xtal/F");
  outputTree->Branch("pho2SigmaIetaIeta", &pho2SigmaIetaIeta, "pho2SigmaIetaIeta/F");
  outputTree->Branch("pho2R9", &pho2R9, "pho2R9/F");
  outputTree->Branch("pho2HoverE", &pho2HoverE, "pho2HoverE/F");
  outputTree->Branch("pho2sumChargedHadronPt", &pho2sumChargedHadronPt, "pho2sumChargedHadronPt/F");
  outputTree->Branch("pho2PFsumChargedHadronPt", &pho2PFsumChargedHadronPt, "pho2PFsumChargedHadronPt/F");
  outputTree->Branch("pho2sumNeutralHadronEt", &pho2sumNeutralHadronEt, "pho2sumNeutralHadronEt/F");
  outputTree->Branch("pho2PFsumNeutralHadronEt", &pho2PFsumNeutralHadronEt, "pho2PFsumNeutralHadronEt/F");
  outputTree->Branch("pho2sumPhotonEt", &pho2sumPhotonEt, "pho2sumPhotonEt/F");
  outputTree->Branch("pho2PFsumPhotonEt", &pho2PFsumPhotonEt, "pho2PFsumPhotonEt/F");
  outputTree->Branch("pho2ecalPFClusterIso", &pho2ecalPFClusterIso, "pho2ecalPFClusterIso/F");
  outputTree->Branch("pho2hcalPFClusterIso", &pho2hcalPFClusterIso, "pho2hcalPFClusterIso/F");
  outputTree->Branch("pho2trkSumPtHollowConeDR03", &pho2trkSumPtHollowConeDR03, "pho2trkSumPtHollowConeDR03/F");
  outputTree->Branch("pho2sigmaEOverE", &pho2sigmaEOverE, "pho2sigmaEOverE/F");
  outputTree->Branch("pho2passEleVeto", &pho2passEleVeto, "pho2passEleVeto/O");
  outputTree->Branch("pho2passIsoLoose", &pho2passIsoLoose, "pho2passIsoLoose/O");
  outputTree->Branch("pho2passIsoLoose_privatePF", &pho2passIsoLoose_privatePF, "pho2passIsoLoose_privatePF/O");
  outputTree->Branch("pho2passIsoLoose_OOT", &pho2passIsoLoose_OOT, "pho2passIsoLoose_OOT/O");
  outputTree->Branch("pho2passIsoMedium", &pho2passIsoMedium, "pho2passIsoMedium/O");
  outputTree->Branch("pho2passIsoMedium_privatePF", &pho2passIsoMedium_privatePF, "pho2passIsoMedium_privatePF/O");
  outputTree->Branch("pho2passIsoMedium_OOT", &pho2passIsoMedium_OOT, "pho2passIsoMedium_OOT/O");
  outputTree->Branch("pho2passIsoTight", &pho2passIsoTight, "pho2passIsoTight/O");
  outputTree->Branch("pho2passIsoTight_privatePF", &pho2passIsoTight_privatePF, "pho2passIsoTight_privatePF/O");
  outputTree->Branch("pho2passIsoTight_OOT", &pho2passIsoTight_OOT, "pho2passIsoTight_OOT/O");
 
  outputTree->Branch("pho2passIsoLoose_comboIso", &pho2passIsoLoose_comboIso, "pho2passIsoLoose_comboIso/O");
  outputTree->Branch("pho2passIsoMedium_comboIso", &pho2passIsoMedium_comboIso, "pho2passIsoMedium_comboIso/O");
  outputTree->Branch("pho2passIsoTight_comboIso", &pho2passIsoTight_comboIso, "pho2passIsoTight_comboIso/O");
  outputTree->Branch("pho2passHoverELoose", &pho2passHoverELoose, "pho2passHoverELoose/O");
  outputTree->Branch("pho2passHoverEMedium", &pho2passHoverEMedium, "pho2passHoverEMedium/O");
  outputTree->Branch("pho2passHoverETight", &pho2passHoverETight, "pho2passHoverETight/O");
  outputTree->Branch("pho2passSigmaIetaIetaLoose", &pho2passSigmaIetaIetaLoose, "pho2passSigmaIetaIetaLoose/O");
  outputTree->Branch("pho2passSigmaIetaIetaMedium", &pho2passSigmaIetaIetaMedium, "pho2passSigmaIetaIetaMedium/O");
  outputTree->Branch("pho2passSigmaIetaIetaTight", &pho2passSigmaIetaIetaTight, "pho2passSigmaIetaIetaTight/O");
  outputTree->Branch("pho2passSmajorLoose", &pho2passSmajorLoose, "pho2passSmajorLoose/O");
  outputTree->Branch("pho2passSmajorMedium", &pho2passSmajorMedium, "pho2passSmajorMedium/O");
  outputTree->Branch("pho2passSmajorTight", &pho2passSmajorTight, "pho2passSmajorTight/O");
  outputTree->Branch("pho2passSminorLoose", &pho2passSminorLoose, "pho2passSminorLoose/O");
  outputTree->Branch("pho2passSminorMedium", &pho2passSminorMedium, "pho2passSminorMedium/O");
  outputTree->Branch("pho2passSminorTight", &pho2passSminorTight, "pho2passSminorTight/O");

  outputTree->Branch("pho2SeedTimeRaw", &pho2SeedTimeRaw, "pho2SeedTimeRaw/F");
  outputTree->Branch("pho2SeedTimeCalib", &pho2SeedTimeCalib, "pho2SeedTimeCalib/F");
  outputTree->Branch("pho2SeedTimeCalibTOF", &pho2SeedTimeCalibTOF, "pho2SeedTimeCalibTOF/F");
  outputTree->Branch("pho2SeedTimeGenV", &pho2SeedTimeGenV, "pho2SeedTimeGenV/F");
  outputTree->Branch("pho2ClusterTime", &pho2ClusterTime, "pho2ClusterTime/F");
  outputTree->Branch("pho2ClusterTime_SmearToData", &pho2ClusterTime_SmearToData, "pho2ClusterTime_SmearToData/F");
  outputTree->Branch("pho2Sminor", &pho2Sminor, "pho2Sminor/F");
  outputTree->Branch("pho2Smajor", &pho2Smajor, "pho2Smajor/F");
  outputTree->Branch("pho2Setaeta", &pho2Setaeta, "pho2Setaeta/F");
  outputTree->Branch("pho2Sphiphi", &pho2Sphiphi, "pho2Sphiphi/F");
  outputTree->Branch("pho2Setaphi", &pho2Setaphi, "pho2Setaphi/F");
  outputTree->Branch("pho2GenE", &pho2GenE, "pho2GenE/F");
  outputTree->Branch("pho2GenPt", &pho2GenPt, "pho2GenPt/F");
  outputTree->Branch("pho2GenEta", &pho2GenEta, "pho2GenEta/F");
  outputTree->Branch("pho2GenPhi", &pho2GenPhi, "pho2GenPhi/F");

  outputTree->Branch("hasJetL1PreFiring", &hasJetL1PreFiring, "hasJetL1PreFiring/O");
  outputTree->Branch("n_Jets", &n_Jets, "n_Jets/I");
  outputTree->Branch("n_Jets_JESUp", &n_Jets_JESUp, "n_Jets_JESUp/I");
  outputTree->Branch("n_Jets_JESDown", &n_Jets_JESDown, "n_Jets_JESDown/I");

  outputTree->Branch("jet1E", &jet1E, "jet1E/F");
  outputTree->Branch("jet1Pt", &jet1Pt, "jet1Pt/F");
  outputTree->Branch("jet1Eta", &jet1Eta, "jet1Eta/F");
  outputTree->Branch("jet1Phi", &jet1Phi, "jet1Phi/F");  

  outputTree->Branch("jet2E", &jet2E, "jet2E/F");
  outputTree->Branch("jet2Pt", &jet2Pt, "jet2Pt/F");
  outputTree->Branch("jet2Eta", &jet2Eta, "jet2Eta/F");
  outputTree->Branch("jet2Phi", &jet2Phi, "jet2Phi/F");  

  outputTree->Branch("MET", &MET, "MET/F");
  outputTree->Branch("genMetPt", &genMetPt, "genMetPt/F");
  outputTree->Branch("genMetPhi", &genMetPhi, "genMetPhi/F");
  outputTree->Branch("sumMET", &sumMET, "sumMET/F");
  outputTree->Branch("MET_JESUp", &MET_JESUp, "MET_JESUp/F");
  outputTree->Branch("MET_JESDown", &MET_JESDown, "MET_JESDown/F");
  outputTree->Branch("t1MET", &t1MET, "t1MET/F");
  outputTree->Branch("t1MET_raw", &metType1Pt_raw, "t1MET_raw/F");
  outputTree->Branch("t1METPhi", &metType1Phi, "t1METPhi/F");
  outputTree->Branch("t1METPhi_raw", &metType1Phi_raw, "t1METPhi_raw/F");
  outputTree->Branch("t1MET_JESUp", &t1MET_JESUp, "t1MET_JESUp/F");
  outputTree->Branch("t1MET_JESDown", &t1MET_JESDown, "t1MET_JESDown/F");
  outputTree->Branch("t1MET_phoScaleUp", &t1MET_phoScaleUp, "t1MET_phoScaleUp/F");
  outputTree->Branch("t1MET_phoScaleDown", &t1MET_phoScaleDown, "t1MET_phoScaleDown/F");
  outputTree->Branch("t1MET_phoSmearUp", &t1MET_phoSmearUp, "t1MET_phoSmearUp/F");
  outputTree->Branch("t1MET_phoSmearDown", &t1MET_phoSmearDown, "t1MET_phoSmearDown/F");
  outputTree->Branch("HT", &HT, "HT/F");

  outputTree->Branch("lep1Pt", &lep1Pt, "lep1Pt/F");
  outputTree->Branch("lep2Pt", &lep2Pt, "lep2Pt/F");
  outputTree->Branch("mll", &mll, "mll/F");
  outputTree->Branch("lep1Type", &lep1Type, "lep1Type/I");
  outputTree->Branch("lep2Type", &lep2Type, "lep2Type/I");

  outputTree->Branch("HLTDecision", HLTDecision, "HLTDecision[1000]/O");
//  outputTree->Branch("HLTPrescale", HLTPrescale,"HLTPrescale[300]/I");

  outputTree->Branch("deltaPt_pho1", &deltaPt_pho1, "deltaPt_pho1/F");
  outputTree->Branch("deltaPt_pho2", &deltaPt_pho2, "deltaPt_pho2/F");
  outputTree->Branch("deltaR_pho12", &deltaR_pho12, "deltaR_pho12/F");
  outputTree->Branch("deltaR_pho1", &deltaR_pho1, "deltaR_pho1/F");
  outputTree->Branch("deltaR_pho2", &deltaR_pho2, "deltaR_pho2/F");
  outputTree->Branch("deltaEta_pho1", &deltaEta_pho1, "deltaEta_pho1/F");
  outputTree->Branch("deltaEta_pho2", &deltaEta_pho2, "deltaEta_pho2/F");
  outputTree->Branch("deltaPhi_pho1", &deltaPhi_pho1, "deltaPhi_pho1/F");
  outputTree->Branch("deltaPhi_pho2", &deltaPhi_pho2, "deltaPhi_pho2/F");
  outputTree->Branch("reco_eta1", &reco_eta1, "reco_eta1/F");
  outputTree->Branch("reco_eta2", &reco_eta2, "reco_eta2/F");
  outputTree->Branch("gen_eta1", &gen_eta1, "gen_eta1/F");
  outputTree->Branch("gen_eta2", &gen_eta2, "gen_eta2/F");

  outputTree->Branch("R1", &R1, "R1/F");
  outputTree->Branch("R2", &R2, "R2/F");
  outputTree->Branch("pho1_genVtxX", &pho1_genVtxX, "pho1_genVtxX/F");
  outputTree->Branch("pho2_genVtxX", &pho2_genVtxX, "pho2_genVtxX/F");
  outputTree->Branch("pho1_genVtxY", &pho1_genVtxY, "pho1_genVtxY/F");
  outputTree->Branch("pho2_genVtxY", &pho2_genVtxY, "pho2_genVtxY/F");
  outputTree->Branch("pho1_genVtxZ", &pho1_genVtxZ, "pho1_genVtxZ/F");
  outputTree->Branch("pho2_genVtxZ", &pho2_genVtxZ, "pho2_genVtxZ/F");
  outputTree->Branch("pho1_genVtxEta", &pho1_genVtxEta, "pho1_genVtxEta/F");
  outputTree->Branch("pho2_genVtxEta", &pho2_genVtxEta, "pho2_genVtxEta/F");
  outputTree->Branch("pho1_genVtxPhi", &pho1_genVtxPhi, "pho1_genVtxPhi/F");
  outputTree->Branch("pho2_genVtxPhi", &pho2_genVtxPhi, "pho2_genVtxPhi/F");
  outputTree->Branch("ZD1", &ZD1, "ZD1/F");
  outputTree->Branch("ZD2", &ZD2, "ZD2/F");

  TH1F *NEvents = new TH1F("NEvents", "NEvents", 1, 1, 2);
  TH1F *SumWeights = new TH1F("SumWeights", "SumWeights", 1, 0.5, 1.5);
  TH1F *SumScaleWeights = new TH1F("SumScaleWeights", "SumScaleWeights", 6, -0.5, 5.5);
  TH1F *SumPdfWeights = new TH1F("SumPdfWeights", "SumPdfWeights", NUM_PDF_WEIGHTS, -0.5, NUM_PDF_WEIGHTS-0.5);

  //begin loop
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  std::cout << "Number of entries " << nentries << std::endl;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    //begin event
    if(jentry % 1000 == 0) cout << "Processing entry " << jentry << endl;
    Long64_t ientry = LoadTree(jentry);
    // For some reason the ecalRechit pointers (ie, the vector) disappear after loading the entry. 
    // Need to manually set the pointer value.
    delete ecalRechit_ID, ecalRechit_Eta, ecalRechit_Phi, ecalRechit_X, 
           ecalRechit_Y, ecalRechit_Z, ecalRechit_E, ecalRechit_T, 
           ecalRechit_FlagOOT, ecalRechit_GainSwitch1,
           ecalRechit_GainSwitch6, ecalRechit_transpCorr, 
           ecalRechit_pedrms12, ecalRechit_pedrms6, ecalRechit_pedrms1,
           scaleWeights, pdfWeights, alphasWeights;
    std::vector<unsigned int>  *ecalRechit_ID = 0;
    std::vector<float> *ecalRechit_Eta = 0, *ecalRechit_Phi = 0, *ecalRechit_X = 0, 
        *ecalRechit_Y = 0, *ecalRechit_Z = 0, *ecalRechit_E = 0, *ecalRechit_T = 0, 
        *ecalRechit_transpCorr = 0, *ecalRechit_pedrms12 = 0, 
        *ecalRechit_pedrms6 = 0, *ecalRechit_pedrms1 = 0, 
        *scaleWeights = 0, *pdfWeights = 0, *alphasWeights = 0;
    std::vector<bool> *ecalRechit_FlagOOT = 0, *ecalRechit_GainSwitch1 = 0,
        *ecalRechit_GainSwitch6 = 0;
    b_ecalRechit_ID->SetAddress(&ecalRechit_ID);
    b_ecalRechit_Eta->SetAddress(&ecalRechit_Eta);
    b_ecalRechit_Phi->SetAddress(&ecalRechit_Phi);
    b_ecalRechit_X->SetAddress(&ecalRechit_X);
    b_ecalRechit_Y->SetAddress(&ecalRechit_Y);
    b_ecalRechit_Z->SetAddress(&ecalRechit_Z);
    b_ecalRechit_E->SetAddress(&ecalRechit_E);
    b_ecalRechit_T->SetAddress(&ecalRechit_T);
    b_ecalRechit_FlagOOT->SetAddress(&ecalRechit_FlagOOT);
    b_ecalRechit_GainSwitch1->SetAddress(&ecalRechit_GainSwitch1);
    b_ecalRechit_GainSwitch6->SetAddress(&ecalRechit_GainSwitch6);
    b_ecalRechit_transpCorr->SetAddress(&ecalRechit_transpCorr);
    if (isData)
    {
        b_ecalRechit_pedrms12->SetAddress(&ecalRechit_pedrms12);
        b_ecalRechit_pedrms6->SetAddress(&ecalRechit_pedrms6);
        b_ecalRechit_pedrms1->SetAddress(&ecalRechit_pedrms1);
    }
    else
    {
        b_scaleWeights->SetAddress(&scaleWeights);
        b_pdfWeights->SetAddress(&pdfWeights);
        b_alphasWeights->SetAddress(&alphasWeights);
    }
    //std::cout << "[DEBUG] dummy->GetAddress(): " << dummy->GetAddress() << std::endl;
    //std::cout << "[DEBUG] fChain->GetBranchStatus(\"ecalRechit_ID\"): " << fChain->GetBranchStatus("ecalRechit_ID") << std::endl;
    if (ientry < 0) 
    {
        std::cout << "Exiting\n";
        break;
    }
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    //initialize branches
    run = runNum;
    lumi = lumiNum;
    event = eventNum;
    genVertexTime = 0.0;//genVertexT
    NPU = 0;   
    nLooseMuons = 0;   
    nTightMuons = 0;   
    weight = 1.0;
    pileupWeight = 1.0;
    pileupWeightUp = 1.0;
    pileupWeightDown = 1.0;
    triggerEffWeight  = 1.0;
    triggerEffSFWeight  = 1.0;
    ISRSystWeightUp   = 1.0;
    ISRSystWeightDown = 1.0;
    photonEffSF = 1.0;
    sf_facScaleUp = 1.0;
    sf_facScaleDown = 1.0;
    sf_renScaleUp = 1.0;
    sf_renScaleDown = 1.0;
    sf_facRenScaleUp = 1.0;
    sf_facRenScaleDown = 1.0;
    

    TOF_total1 = -999;
    TOF_total2 = -999;
    TOF_total1_genV = -999;
    TOF_total2_genV = -999;
    TOF_neu1 = -999;
    TOF_neu2 = -999;
    TOF_pho1 = -999;
    TOF_pho2 = -999;
    TOF_neu1_RF = -999;
    TOF_neu2_RF = -999;

    n_Photons = 0;
    n_Photons_reco = 0;
    pho1E = -999, pho1Pt = -999, pho1Pt_scaleUp = -999, pho1Pt_scaleDown = -999, pho1Pt_smearUp = -999, pho1Pt_smearDown = -999, pho1Eta = -999, pho1Phi = -999, pho1SeedE = -999, pho1SeedPt = -999, pho1SeedEta = -999, pho1SeedPhi = -999, pho1SC_E = -999, pho1SC_Pt = -999, pho1SC_Eta = -999, pho1SC_Phi = -999, pho1angle_xtal = -999, pho1SigmaIetaIeta = -999, pho1R9 = -999, pho1HoverE = -999, pho1sumChargedHadronPt = -999, pho1sumNeutralHadronEt = -999, pho1sumPhotonEt = -999, pho1PFsumChargedHadronPt = -999, pho1PFsumNeutralHadronEt = -999, pho1PFsumPhotonEt = -999, pho1ecalPFClusterIso = -999, pho1hcalPFClusterIso = -999, pho1trkSumPtHollowConeDR03 = -999, pho1sigmaEOverE = -999, pho1SeedTimeRaw = -999, pho1SeedTimeCalib = -999, pho1SeedTimeCalibTOF = -999, pho1SeedTimeGenV = -999, pho1ClusterTime = -999, pho1ClusterTime_SmearToData, pho1Sminor = -999, pho1Smajor = -999, pho1Setaeta = -999, pho1Sphiphi = -999, pho1Setaphi = -999, pho1GenE = -999, pho1GenPt = -999, pho1GenEta = -999, pho1GenPhi = -999, pho1ClusterTime_scaleUp=-999, pho1ClusterTime_scaleDown=-999, pho1ClusterTime_smearUp=-999, pho1ClusterTime_smearDown=-999;
    pho2E = -999, pho2Pt = -999, pho2Pt_scaleDown = -999, pho2Pt_scaleDown = -999, pho1Pt_smearUp = -999, pho2Pt_smearDown = -999, pho2Eta = -999, pho2Phi = -999, pho2SeedE = -999, pho2SeedPt = -999, pho2SeedEta = -999, pho2SeedPhi = -999, pho2SC_E = -999, pho2SC_Pt = -999, pho2SC_Eta = -999, pho2SC_Phi = -999, pho2angle_xtal = -999, pho2SigmaIetaIeta = -999, pho2R9 = -999, pho2HoverE = -999, pho2sumChargedHadronPt = -999, pho2sumNeutralHadronEt = -999, pho2sumPhotonEt = -999, pho2PFsumChargedHadronPt = -999, pho2PFsumNeutralHadronEt = -999, pho2PFsumPhotonEt = -999, pho2ecalPFClusterIso = -999, pho2hcalPFClusterIso = -999, pho2trkSumPtHollowConeDR03 = -999, pho2sigmaEOverE = -999, pho2SeedTimeRaw = -999, pho2SeedTimeCalib = -999, pho2SeedTimeCalibTOF = -999, pho2SeedTimeGenV = -999, pho2ClusterTime = -999, pho2ClusterTime_SmearToData, pho2Sminor = -999, pho2Smajor = -999, pho2Setaeta = -999, pho2Sphiphi = -999, pho2Setaphi = -999, pho2GenE = -999, pho2GenPt = -999, pho2GenEta = -999, pho2GenPhi = -999;
    pho1passEleVeto = false, pho1passTrackVeto = false; pho1passIsoLoose = false, pho1passIsoMedium = false, pho1passIsoTight = false, pho1isStandardPhoton = false, pho1isPromptPhoton = false, pho1isDelayedPhoton = false;
    pho1passIsoLoose_privatePF = false, pho1passIsoMedium_privatePF = false, pho1passIsoTight_privatePF = false;
    pho1passIsoLoose_OOT = false, pho1passIsoMedium_OOT = false, pho1passIsoTight_OOT = false;
    pho2passEleVeto = false, pho2passIsoLoose = false, pho2passIsoMedium = false, pho2passIsoTight = false, pho2isStandardPhoton = false, pho2isPromptPhoton = false, pho2isDelayedPhoton = false;
    pho2passIsoLoose_privatePF = false, pho2passIsoMedium_privatePF = false, pho2passIsoTight_privatePF = false;
    pho2passIsoLoose_OOT = false, pho2passIsoMedium_OOT = false, pho2passIsoTight_OOT = false;

    pho1SeedX = -999;
    pho1SeedY = -999;
    pho1SeedZ = -999;
    pho2SeedX = -999;
    pho2SeedY = -999;
    pho2SeedZ = -999;

    hasJetL1PreFiring = false;
    n_Jets = 0;
    n_Jets_JESUp = 0;
    n_Jets_JESDown = 0;

    jet1E = -999, jet1Pt = -999, jet1Eta = -999, jet1Phi = -999;	
    jet2E = -999, jet2Pt = -999, jet2Eta = -999, jet2Phi = -999;	
    
    MET = -999, t1MET = -999, MET_JESUp = -999, MET_JESDown = -999, t1MET_JESUp = -999, t1MET_JESDown = -999, t1MET_phoScaleUp=-999, t1MET_phoScaleDown=-999, t1MET_phoSmearUp = -999, t1MET_phoSmearDown = -999;
    HT = -999;
  

    lep1Pt = -999, lep2Pt = -999;
    mll =-999;
    lep1Type = 0, lep2Type = 0;

    deltaPt_pho1 = -999;
    deltaPt_pho2 = -999;
    deltaR_pho12 = -999;
    deltaR_pho1 = -999;
    deltaR_pho2 = -999;
    deltaEta_pho1 = -999;
    deltaEta_pho2 = -999;
    deltaPhi_pho1 = -999;
    deltaPhi_pho2 = -999;
    reco_eta1 = -999;
    reco_eta2 = -999;
    gen_eta1 = -999;
    gen_eta2 = -999;

    R1 = -999;
    R2 = -999;
    pho1_genVtxX = -999;
    pho2_genVtxX = -999;
    pho1_genVtxY = -999;
    pho2_genVtxY = -999;
    pho1_genVtxZ = -999;
    pho2_genVtxZ = -999;
    pho1_genVtxEta = -999;
    pho2_genVtxEta = -999;
    pho1_genVtxPhi = -999;
    pho2_genVtxPhi = -999;
    ZD1 = -999;
    ZD2 = -999;


    //fill normalization histogram
    NEvents->SetBinContent( 1, NEvents->GetBinContent(1) + genWeight);
    weight = genWeight;
    SumWeights->Fill(1.0, weight);

    //get NPU
    if( !isData )
    {
    for (int i=0; i < nBunchXing; ++i) {
      if (BunchXing[i] == 0) {
        NPU = nPUmean[i];
      }
    }
    pileupWeight = helper->getPileupWeight(NPU);
    pileupWeightUp = helper->getPileupWeightUp(NPU) / pileupWeight;
    pileupWeightDown = helper->getPileupWeightDown(NPU) / pileupWeight;
    
    if ( (*scaleWeights).size() >= 9 )
        {
          sf_facScaleUp      = (*scaleWeights)[1]/genWeight;
          sf_facScaleDown    = (*scaleWeights)[2]/genWeight;
          sf_renScaleUp      = (*scaleWeights)[3]/genWeight;
          sf_renScaleDown    = (*scaleWeights)[6]/genWeight;
          sf_facRenScaleUp   = (*scaleWeights)[4]/genWeight;
          sf_facRenScaleDown = (*scaleWeights)[8]/genWeight;
	
	  SumScaleWeights->Fill(0.0, (*scaleWeights)[1]);
	  SumScaleWeights->Fill(1.0, (*scaleWeights)[2]);
	  SumScaleWeights->Fill(2.0, (*scaleWeights)[3]);
	  SumScaleWeights->Fill(3.0, (*scaleWeights)[6]);
	  SumScaleWeights->Fill(4.0, (*scaleWeights)[4]);
	  SumScaleWeights->Fill(5.0, (*scaleWeights)[8]);

    }
   
    sf_pdf.erase( sf_pdf.begin(), sf_pdf.end() );
    for ( unsigned int iwgt = 0; iwgt < pdfWeights->size(); ++iwgt )
        {
          sf_pdf.push_back( pdfWeights->at(iwgt)/genWeight );
	  SumPdfWeights->Fill(double(iwgt),(*pdfWeights)[iwgt]);
	} 
  
    }
 
    int nPho = 0;
    TLorentzVector pho1 = makeTLorentzVector(0,0,0,0);
    TLorentzVector pho1_scaleUp = makeTLorentzVector(0,0,0,0);
    TLorentzVector pho1_scaleDown = makeTLorentzVector(0,0,0,0);
    TLorentzVector pho1_smearUp = makeTLorentzVector(0,0,0,0);
    TLorentzVector pho1_smearDown = makeTLorentzVector(0,0,0,0);
    TLorentzVector pho2 = makeTLorentzVector(0,0,0,0);
    TLorentzVector pho2_scaleUp = makeTLorentzVector(0,0,0,0);
    TLorentzVector pho2_scaleDown = makeTLorentzVector(0,0,0,0);
    TLorentzVector pho2_smearUp = makeTLorentzVector(0,0,0,0);
    TLorentzVector pho2_smearDown = makeTLorentzVector(0,0,0,0);



    TVector3 vtx( pvX, pvY, pvZ );
        

    for(int ind_pho = 0; ind_pho < nPhotons; ind_pho++) 
    { //photon loop
        // apply cuts
        if (ecalRechit_ID->empty()) continue;
        if (phoPt[ind_pho] < 40) 
        {
            continue; // basic Pt cut
        }
        if(fabs(phoEta[ind_pho]) > 2.5) continue; // tracker region
        if(fabs(phoEta[ind_pho]) > 1.4442 && fabs(phoEta[ind_pho]) < 1.566) continue; //the eta range for photon, this takes care of the gap between barrel and endcap
        //if(!photonPassLooseIso(ind_pho)) continue;
        //if(!pho_passEleVeto[ind_pho]) continue;
        //if(!(isEGammaPOGTightElectron(i))) continue;
        //check overlap, this is mainly for overlap within one collection
        //float dR_pho1 = deltaR(phoEta[ind_pho], phoPhi[ind_pho], pho1Eta, pho1Phi);
        //float dR_pho2 = deltaR(phoEta[ind_pho], phoPhi[ind_pho], pho2Eta, pho2Phi);
        //if(dR_pho1 < 0.3 && phoPt[ind_pho]<pho1Pt) continue; // overlap, remove
        //if(dR_pho2 < 0.3 && phoPt[ind_pho]<pho2Pt) continue; // overlap, remove

        nPho++;
        float pho_pt_corr = phoPt[ind_pho];
        float pho_pt_corr_scaleUp = phoPt[ind_pho];
        float pho_pt_corr_scaleDown = phoPt[ind_pho];
        float pho_pt_corr_smearUp = phoPt[ind_pho];
        float pho_pt_corr_smearDown = phoPt[ind_pho];
        //    double scale = photonCorrector->ScaleCorrection(run, (fabs(pho_superClusterEta[ind_pho]) < 1.5), phoR9[ind_pho], pho_superClusterEta[ind_pho], phoE[ind_pho]/cosh(pho_superClusterEta[ind_pho]));
        //    double scaleUnc = photonCorrector->ScaleCorrectionUncertainty(run, (fabs(pho_superClusterEta[ind_pho]) < 1.5), phoR9[ind_pho], pho_superClusterEta[ind_pho], phoE[ind_pho]/cosh(pho_superClusterEta[ind_pho]));
        //    double scaleUp = scale + scaleUnc;
        //    double scaleDown = scale - scaleUnc;
        //    double smear = photonCorrector->getSmearingSigma(run, (fabs(pho_superClusterEta[ind_pho]) < 1.5), phoR9[ind_pho], pho_superClusterEta[ind_pho], phoE[ind_pho]/cosh(pho_superClusterEta[ind_pho]), 0., 0.);

        double scale = 1;
        double scaleUnc = 0;
        double scaleUp = 1;
        double scaleDown = 1;
        double smear = 0;
        const EnergyScaleCorrection_class_2017::ScaleCorrection_class_2017* scaleCorr = photonCorrector->EnergyScaleCorrection_class_2017::getScaleCorr(run, phoE[ind_pho]/cosh(pho_superClusterEta[ind_pho]), fabs(pho_superClusterEta[ind_pho]), phoR9[ind_pho], 12);
        const EnergyScaleCorrection_class_2017::SmearCorrection_class_2017* smearCorr = photonCorrector->EnergyScaleCorrection_class_2017::getSmearCorr(run, phoE[ind_pho]/cosh(pho_superClusterEta[ind_pho]), fabs(pho_superClusterEta[ind_pho]), phoR9[ind_pho], 12);
        if (scaleCorr!=NULL) 
        {
            scale  = scaleCorr->scale();
            scaleUnc = scaleCorr->scaleErr(EnergyScaleCorrection_class_2017::kErrGainBitNr);
            scaleUp = scale + scaleUnc;
            scaleDown = scale - scaleUnc;
        }
        if (scaleCorr!=NULL) 
        if (smearCorr!=NULL) smear  = smearCorr->sigma(phoE[ind_pho]/cosh(pho_superClusterEta[ind_pho]));

        if (doPhotonScaleCorrection) {
            if (isData) {
                pho_pt_corr = phoPt[ind_pho]*scale;
                pho_pt_corr_scaleUp = phoPt[ind_pho]*scaleUp;
                pho_pt_corr_scaleDown = phoPt[ind_pho]*scaleDown;
                if (_phodebug) std::cout << "[DEBUG] : Photon Energy Scale Corrections: " << phoPt[ind_pho] << " * " << scale << " --> " << pho_pt_corr << "\n";
            } else {
                pho_pt_corr = phoPt[ind_pho]*(1+smear*random.Gaus());
                pho_pt_corr_scaleUp = pho_pt_corr/scaleUp;
                pho_pt_corr_scaleDown = pho_pt_corr/scaleDown;
                pho_pt_corr_smearUp = phoPt[ind_pho]*(1+smear);
                pho_pt_corr_smearDown = phoPt[ind_pho]*(1-smear);
            }
        }

        //photon cluster
        TVector3 vec, vec_scaleUp, vec_scaleDown, vec_smearUp, vec_smearDown;
        vec.SetPtEtaPhi( pho_pt_corr, phoEta[ind_pho], phoPhi[ind_pho] );
        vec_scaleUp.SetPtEtaPhi( pho_pt_corr_scaleUp, phoEta[ind_pho], phoPhi[ind_pho] );
        vec_scaleDown.SetPtEtaPhi( pho_pt_corr_scaleDown, phoEta[ind_pho], phoPhi[ind_pho] );
        vec_smearUp.SetPtEtaPhi( pho_pt_corr_smearUp, phoEta[ind_pho], phoPhi[ind_pho] );
        vec_smearDown.SetPtEtaPhi( pho_pt_corr_smearDown, phoEta[ind_pho], phoPhi[ind_pho] );
        TLorentzVector thisPhoton, thisPhoton_scaleUp, thisPhoton_scaleDown, thisPhoton_smearUp, thisPhoton_smearDown; //= makeTLorentzVector(phoPt[ind_pho], phoEta[ind_pho], phoPhi[ind_pho], phoE[ind_pho]);
        thisPhoton.SetVectM( vec, .0 );
        thisPhoton_scaleUp.SetVectM( vec_scaleUp, .0 );
        thisPhoton_scaleDown.SetVectM( vec_scaleDown, .0 );
        thisPhoton_smearUp.SetVectM( vec_smearUp, .0 );
        thisPhoton_smearDown.SetVectM( vec_smearDown, .0 );

        //photon super cluster
        TVector3 phoPos;
        if ( fabs( pho_superClusterEta[ind_pho] ) < 1.479 )
        {
            phoPos.SetXYZ( EB_R*cos( pho_superClusterPhi[ind_pho]), EB_R*sin( pho_superClusterPhi[ind_pho] ), EB_R*sinh( pho_superClusterEta[ind_pho] ) );
        }
        else
        {
            double R = fabs( EE_Z/sinh( pho_superClusterEta[ind_pho] ) );
            if ( pho_superClusterEta[ind_pho] > .0 )
            {
                phoPos.SetXYZ( R*cos( pho_superClusterPhi[ind_pho] ), R*sin( pho_superClusterPhi[ind_pho] ), EE_Z);
            }
            else
            {
                phoPos.SetXYZ( R*cos( pho_superClusterPhi[ind_pho] ), R*sin( pho_superClusterPhi[ind_pho] ), -EE_Z);
            }
        }
        TLorentzVector phoSC = GetCorrectedMomentum( vtx, phoPos, pho_RegressionE[ind_pho] );

        //rough definition
        uint seedhitIndex =  (*pho_SeedRechitIndex)[ind_pho];

        //cout<<"reco Photon - "<<i<<" : seedX = "<<(*ecalRechit_X)[seedhitIndex]<<" : seedY = "<<(*ecalRechit_Y)[seedhitIndex]<<" : seedZ = "<<(*ecalRechit_Z)[seedhitIndex]<<"  pT = "<<phoPt[ind_pho]<<"  Energy = "<<phoE[ind_pho]<<endl;
        //cout<<"seedhitIndex: "<<seedhitIndex<<endl;
        //cout<<"ecalRechit_ID size: "<<ecalRechit_ID->size()<<endl;
        //cout<<"ecalRechit_ID: "<<(*ecalRechit_ID)[seedhitIndex]<<endl;

        bool isFromEB = bool( (*ecalRechit_ID)[seedhitIndex] < 840000000 ); //barrel vs. endcap
        double rawSeedHitTime =  (*ecalRechit_T)[seedhitIndex];

        //apply intercalibration2      
        double IC_time_SeptRereco = 0.0;//isData ? getTimeCalibConstant(tree_timeCalib_rereco, start_run_rereco,end_run_rereco,runNum, (*ecalRechit_ID)[seedhitIndex]) : 0;
        double IC_time_LagacyRereco = 0.0;//isData ? getTimeCalibConstant(tree_timeCalib, start_run,end_run,runNum, (*ecalRechit_ID)[seedhitIndex]) : 0;
        double calibratedSeedHitTime = rawSeedHitTime + IC_time_LagacyRereco - IC_time_SeptRereco;

        //apply TOF correction
        double TOFCorrectedSeedHitTime = calibratedSeedHitTime + (std::sqrt(pow((*ecalRechit_X)[seedhitIndex],2)+pow((*ecalRechit_Y)[seedhitIndex],2)+pow((*ecalRechit_Z)[seedhitIndex],2))-std::sqrt(pow((*ecalRechit_X)[seedhitIndex]-pvX,2)+pow((*ecalRechit_Y)[seedhitIndex]-pvY,2)+pow((*ecalRechit_Z)[seedhitIndex]-pvZ,2)))/SPEED_OF_LIGHT;

        //generator xyz information

        double TOFCorrectedSeedHitTime_genV = isData ? TOFCorrectedSeedHitTime : ( calibratedSeedHitTime + (std::sqrt(pow((*ecalRechit_X)[seedhitIndex],2)+pow((*ecalRechit_Y)[seedhitIndex],2)+pow((*ecalRechit_Z)[seedhitIndex],2))-std::sqrt(pow((*ecalRechit_X)[seedhitIndex]-genVertexX,2)+pow((*ecalRechit_Y)[seedhitIndex]-genVertexY,2)+pow((*ecalRechit_Z)[seedhitIndex]-genVertexZ,2)))/SPEED_OF_LIGHT );

        double tmpSumWeightedTime = 0;
        double tmpSumWeight = 0;

        double etaAverage = 0.0;
        double phiAverage = 0.0;
        double mTotalWeight = 0.0;
        double tmpSumE = 0.0;
        double phoSetaeta = 0.0;//second moments of eta eta
        double phoSphiphi = 0.0;
        double phoSetaphi = 0.0;

        for (uint k=0; k<(*pho_EcalRechitIndex)[ind_pho].size(); ++k) 
        {
            uint rechitIndex = (*pho_EcalRechitIndex)[ind_pho][k];

            if((*ecalRechit_E)[rechitIndex] < 1.0) continue;	

            double rawT = (*ecalRechit_T)[rechitIndex];
            //apply intercalibration
            double IC_time_SeptRereco_this = 0.0;
            double IC_time_LagacyRereco_this = 0.0;
            double calibratedSeedHitTime_this = rawT + IC_time_LagacyRereco_this - IC_time_SeptRereco_this;


            double corrT = calibratedSeedHitTime_this + (std::sqrt(pow((*ecalRechit_X)[rechitIndex],2)+pow((*ecalRechit_Y)[rechitIndex],2)+pow((*ecalRechit_Z)[rechitIndex],2))-std::sqrt(pow((*ecalRechit_X)[rechitIndex]-pvX,2)+pow((*ecalRechit_Y)[rechitIndex]-pvY,2)+pow((*ecalRechit_Z)[rechitIndex]-pvZ,2)))/SPEED_OF_LIGHT;

            double pedNoise = isData ? (*ecalRechit_pedrms12)[rechitIndex] : 1.0;  
            //double pedNoise = 1;
            double ADCToGeV = isData ? getADCToGeV(runNum, isFromEB) : 1;
            double sigmaE = pedNoise * ADCToGeV;

            double sigmaT2 = N_EB*N_EB / ((*ecalRechit_E)[rechitIndex] * (*ecalRechit_E)[rechitIndex] / (sigmaE*sigmaE)) + 2.0 * C_EB * C_EB;

            if(!isData) sigmaT2 = 0.5*N_EB_MC*N_EB_MC / ((*ecalRechit_E)[rechitIndex] * (*ecalRechit_E)[rechitIndex] / (sigmaE*sigmaE)) + C_EB_MC * C_EB_MC;

            tmpSumWeightedTime += corrT * ( 1.0 / sigmaT2 );
            tmpSumWeight += ( 1.0 / sigmaT2 );
            // cout << "\n";
            tmpSumE += (*ecalRechit_E)[rechitIndex];	

        }

        double weightedTime = tmpSumWeightedTime / tmpSumWeight;

        bool isPromptPhoton = false;
        //photon gen matching
        if(!isData)
        {
            bool foundMatch = false;
            int phoMatchingGenPhotonIndex = -1;
            double deltaEOverEBest = 999;
            for(int g = 0; g < nGenParticle; g++)
            {
                if(gParticleStatus[g] != 1) continue;
                if(gParticleId[g] != 22) continue;
                if(gParticleE[g] < 1.) continue;
                if(deltaR(thisPhoton.Eta(), thisPhoton.Phi(), gParticleEta[g], gParticlePhi[g]) > 0.2) continue;		
                float deltaEOverE = fabs(phoSC.E() - gParticleE[g])/gParticleE[g];
                if(deltaEOverE > 1.) continue;

                foundMatch = true;
                if(deltaEOverE < deltaEOverEBest)
                {
                    deltaEOverEBest = deltaEOverE;
                    phoMatchingGenPhotonIndex = g;
                }	
            }

            if(foundMatch)
            {	
                int motherId = abs(gParticleMotherId[phoMatchingGenPhotonIndex]);
                if(motherId == 25 || (motherId >= 1 && motherId <= 6) || (motherId >= 11 && motherId <= 16)) isPromptPhoton = true;
            }
        }	


        if ( photonOrderByTime ? ( weightedTime > pho1ClusterTime) : (thisPhoton.Pt() > pho1.Pt()))  
        { // find two highest momentum photons, or two largest time photons
            pho2 = pho1;
            pho2_scaleUp = pho1_scaleUp;
            pho2_scaleDown = pho1_scaleDown;
            pho2_smearUp = pho1_smearUp;
            pho2_smearDown = pho1_smearDown;

            pho2E = pho2.E();
            pho2Pt = pho2.Pt();
            pho2Pt_scaleUp = pho2_scaleUp.Pt();
            pho2Pt_scaleDown = pho2_scaleDown.Pt();
            pho2Pt_smearUp = pho2_smearUp.Pt();
            pho2Pt_smearDown = pho2_smearDown.Pt();
            pho2Eta = pho2.Eta();
            pho2Phi = pho2.Phi();
            pho2SeedE = pho1SeedE;
            pho2SeedEta = pho2SeedEta;
            pho2SeedPhi = pho1SeedPhi;
            pho2SeedPt = pho1SeedPt; 
            pho2SC_E = pho1SC_E;
            pho2SC_Pt = pho1SC_Pt; 
            pho2SC_Eta = pho1SC_Eta;
            pho2SC_Phi = pho1SC_Phi;
            pho2SigmaIetaIeta = pho1SigmaIetaIeta;
            pho2R9 = pho1R9;
            pho2HoverE = pho1HoverE;
            pho2sumChargedHadronPt = pho1sumChargedHadronPt;
            pho2PFsumChargedHadronPt = pho1PFsumChargedHadronPt;
            pho2sumNeutralHadronEt = pho1sumNeutralHadronEt;
            pho2PFsumNeutralHadronEt = pho1PFsumNeutralHadronEt;
            pho2sumPhotonEt = pho1sumPhotonEt;
            pho2PFsumPhotonEt = pho1PFsumPhotonEt;
            pho2ecalPFClusterIso = pho1ecalPFClusterIso;
            pho2hcalPFClusterIso = pho1hcalPFClusterIso;
            pho2trkSumPtHollowConeDR03 = pho1trkSumPtHollowConeDR03;
            pho2sigmaEOverE = pho1sigmaEOverE;
            pho2SeedTimeRaw = pho1SeedTimeRaw;
            pho2SeedTimeCalib = pho1SeedTimeCalib;
            pho2SeedTimeCalibTOF = pho1SeedTimeCalibTOF;
            pho2SeedTimeGenV = pho1SeedTimeGenV;
            pho2ClusterTime = pho1ClusterTime;
            pho2Sminor = pho1Sminor;
            pho2Smajor = pho1Smajor;
            pho2Setaeta = pho1Setaeta;
            pho2Sphiphi = pho1Sphiphi;
            pho2Setaphi = pho1Setaphi;
            pho2passEleVeto = pho1passEleVeto;
            pho2passIsoLoose = pho1passIsoLoose;
            pho2passIsoLoose_privatePF = pho1passIsoLoose_privatePF;
            pho2passIsoLoose_OOT = pho1passIsoLoose_OOT;
            pho2passIsoMedium = pho1passIsoMedium;
            pho2passIsoMedium_privatePF = pho1passIsoMedium_privatePF;
            pho2passIsoMedium_OOT = pho1passIsoMedium_OOT;
            pho2passIsoTight = pho1passIsoTight;
            pho2passIsoTight_privatePF = pho1passIsoTight_privatePF;
            pho2passIsoTight_OOT = pho1passIsoTight_OOT;
            pho2isStandardPhoton = pho1isStandardPhoton;
            pho2isPromptPhoton = pho1isPromptPhoton;
            pho2SeedX = pho1SeedX;
            pho2SeedY = pho1SeedY;
            pho2SeedZ = pho1SeedZ;

            //	
            pho1 = thisPhoton;
            pho1_scaleUp = thisPhoton_scaleUp;
            pho1_scaleDown = thisPhoton_scaleDown;
            pho1_smearUp = thisPhoton_smearUp;
            pho1_smearDown = thisPhoton_smearDown;

            pho1E = thisPhoton.E();
            pho1Pt = thisPhoton.Pt();
            pho1Pt_scaleUp = thisPhoton_scaleUp.Pt();
            pho1Pt_scaleDown = thisPhoton_scaleDown.Pt();
            t1MET_phoScaleUp = metType1Pt - (pho1Pt_scaleUp*cos(metType1Phi - thisPhoton_scaleUp.Phi()) - pho1Pt*cos(metType1Phi - thisPhoton.Phi()));
            t1MET_phoScaleDown = metType1Pt - (pho1Pt_scaleDown*cos(metType1Phi - thisPhoton_scaleDown.Phi()) - pho1Pt*cos(metType1Phi - thisPhoton.Phi()));
            pho1Pt_smearUp = thisPhoton_smearUp.Pt();
            pho1Pt_smearDown = thisPhoton_smearDown.Pt();
            t1MET_phoSmearUp = metType1Pt - (pho1Pt_smearUp*cos(metType1Phi - thisPhoton_smearUp.Phi()) - pho1Pt*cos(metType1Phi - thisPhoton.Phi()));
            t1MET_phoSmearDown = metType1Pt - (pho1Pt_smearDown*cos(metType1Phi - thisPhoton_smearDown.Phi()) - pho1Pt*cos(metType1Phi - thisPhoton.Phi()));
            pho1Eta = thisPhoton.Eta();
            pho1Phi = thisPhoton.Phi();
            pho1SeedE = (*ecalRechit_E)[seedhitIndex];
            pho1SeedEta = (*ecalRechit_Eta)[seedhitIndex];
            pho1SeedPhi = (*ecalRechit_Phi)[seedhitIndex];
            pho1SeedPt = pho1SeedE/cosh(pho1SeedEta);
            pho1SC_E = phoSC.E();
            pho1SC_Pt = phoSC.Pt();
            pho1SC_Eta = phoSC.Eta();
            pho1SC_Phi = phoSC.Phi();
            pho1SigmaIetaIeta = phoFull5x5SigmaIetaIeta[ind_pho];
            pho1R9 = phoR9[ind_pho];
            pho1HoverE = pho_HoverE[ind_pho];
            pho1Sminor = pho_sminor[ind_pho];
            pho1Smajor = pho_smajor[ind_pho];
            pho1sumChargedHadronPt = pho_sumChargedHadronPt[ind_pho];
            pho1PFsumChargedHadronPt = pho_pfIsoChargedHadronIso[ind_pho];
            pho1sumNeutralHadronEt = pho_sumNeutralHadronEt[ind_pho];
            pho1PFsumNeutralHadronEt = pho_pfIsoNeutralHadronIso[ind_pho];
            pho1sumPhotonEt = pho_sumPhotonEt[ind_pho];
            pho1PFsumPhotonEt = pho_pfIsoPhotonIso[ind_pho];
            pho1ecalPFClusterIso = pho_ecalPFClusterIso[ind_pho];
            pho1hcalPFClusterIso = pho_hcalPFClusterIso[ind_pho];
            pho1trkSumPtHollowConeDR03 = pho_trkSumPtHollowConeDR03[ind_pho];
            pho1sigmaEOverE = pho_RegressionEUncertainty[ind_pho]/pho_RegressionE[ind_pho];
            pho1SeedTimeRaw = rawSeedHitTime;
            pho1SeedTimeCalib = calibratedSeedHitTime;
            pho1SeedTimeCalibTOF = TOFCorrectedSeedHitTime;
            pho1SeedTimeGenV = TOFCorrectedSeedHitTime_genV;
            pho1ClusterTime = weightedTime;
            pho1Setaeta = phoSetaeta;
            pho1Sphiphi = phoSphiphi;
            pho1Setaphi = phoSetaphi;
            pho1passEleVeto = pho_passEleVeto[ind_pho];
            pho1passTrackVeto = (!(pho_trackMatching[ind_pho]));
            pho1passIsoLoose = photonPassLooseIso(ind_pho);
            pho1passIsoLoose_privatePF = photonPassLooseIso(ind_pho, true, true);
            pho1passIsoLoose_OOT = photonPassLooseIso_OOT2016(ind_pho);
            pho1passIsoMedium = photonPassMediumIso(ind_pho);
            pho1passIsoMedium_privatePF = photonPassMediumIso(ind_pho, true, true);
            pho1passIsoMedium_OOT = photonPassMediumIso_OOT2016(ind_pho); // We don't seem to use loose and medium, so I don't update these
            pho1passIsoTight = photonPassTightIso(ind_pho);
            pho1passIsoTight_privatePF = photonPassTightIso(ind_pho, true, true);
            pho1passIsoTight_OOT = photonPassTightIso_OOT2017(ind_pho);
            pho1isStandardPhoton = pho_isStandardPhoton[ind_pho];
            pho1isPromptPhoton = isPromptPhoton;

            pho1SeedX = (*ecalRechit_X)[seedhitIndex];
            pho1SeedY = (*ecalRechit_Y)[seedhitIndex];
            pho1SeedZ = (*ecalRechit_Z)[seedhitIndex];
        } 
        else if ( ( photonOrderByTime ? ( weightedTime > pho2ClusterTime) : (thisPhoton.Pt() > pho2.Pt())  ) ) 
        {
            pho2 = thisPhoton;
            pho2_scaleUp = thisPhoton_scaleUp;
            pho2_scaleDown = thisPhoton_scaleDown;
            pho2_smearUp = thisPhoton_smearUp;
            pho2_smearDown = thisPhoton_smearDown;

            pho2E = thisPhoton.E();
            pho2Pt = thisPhoton.Pt();
            pho2Pt_scaleUp = thisPhoton_scaleUp.Pt();
            pho2Pt_scaleDown = thisPhoton_scaleDown.Pt();
            pho2Pt_smearUp = thisPhoton_smearUp.Pt();
            pho2Pt_smearDown = thisPhoton_smearDown.Pt();
            pho2Eta = thisPhoton.Eta();
            pho2Phi = thisPhoton.Phi();
            pho2SeedE = (*ecalRechit_E)[seedhitIndex];
            pho2SeedEta = (*ecalRechit_Eta)[seedhitIndex];
            pho2SeedPhi = (*ecalRechit_Phi)[seedhitIndex];
            pho2SeedPt = pho2SeedE/cosh(pho2SeedEta);
            pho2SC_E = phoSC.E();
            pho2SC_Pt = phoSC.Pt();
            pho2SC_Eta = phoSC.Eta();
            pho2SC_Phi = phoSC.Phi();
            pho2SigmaIetaIeta = phoFull5x5SigmaIetaIeta[ind_pho];
            pho2R9 = phoR9[ind_pho];
            pho2HoverE = pho_HoverE[ind_pho];
            pho2Sminor = pho_sminor[ind_pho];
            pho2Smajor = pho_smajor[ind_pho];
            pho2sumChargedHadronPt = pho_sumChargedHadronPt[ind_pho];
            pho2PFsumChargedHadronPt = pho_pfIsoChargedHadronIso[ind_pho];
            pho2sumNeutralHadronEt = pho_sumNeutralHadronEt[ind_pho];
            pho2PFsumNeutralHadronEt = pho_pfIsoNeutralHadronIso[ind_pho];
            pho2sumPhotonEt = pho_sumPhotonEt[ind_pho];
            pho2PFsumPhotonEt = pho_pfIsoPhotonIso[ind_pho];
            pho2ecalPFClusterIso = pho_ecalPFClusterIso[ind_pho];
            pho2hcalPFClusterIso = pho_hcalPFClusterIso[ind_pho];
            pho2trkSumPtHollowConeDR03 = pho_trkSumPtHollowConeDR03[ind_pho];
            pho2sigmaEOverE = pho_RegressionEUncertainty[ind_pho]/pho_RegressionE[ind_pho];
            pho2SeedTimeRaw = rawSeedHitTime;
            pho2SeedTimeCalib = calibratedSeedHitTime;
            pho2SeedTimeCalibTOF = TOFCorrectedSeedHitTime;
            pho2SeedTimeGenV = TOFCorrectedSeedHitTime_genV;
            pho2ClusterTime = weightedTime;
            pho2Setaeta = phoSetaeta;
            pho2Sphiphi = phoSphiphi;
            pho2Setaphi = phoSetaphi;
            pho2passEleVeto = pho_passEleVeto[ind_pho];
            pho2passIsoLoose = photonPassLooseIso(ind_pho);
            pho2passIsoLoose_privatePF = photonPassLooseIso(ind_pho, true, true);
            pho2passIsoLoose_OOT = photonPassLooseIso_OOT2016(ind_pho);
            pho2passIsoMedium = photonPassMediumIso(ind_pho);
            pho2passIsoMedium_privatePF = photonPassMediumIso(ind_pho, true, true);
            pho2passIsoMedium_OOT = photonPassMediumIso_OOT2016(ind_pho);
            pho2passIsoTight = photonPassTightIso(ind_pho);
            pho2passIsoTight_privatePF = photonPassTightIso(ind_pho, true, true);
            pho2passIsoTight_OOT = photonPassTightIso_OOT2016(ind_pho);
            pho2isStandardPhoton = pho_isStandardPhoton[ind_pho];
            pho2isPromptPhoton = isPromptPhoton;

            pho2SeedX = (*ecalRechit_X)[seedhitIndex];
            pho2SeedY = (*ecalRechit_Y)[seedhitIndex];
            pho2SeedZ = (*ecalRechit_Z)[seedhitIndex];
        }    
    } //end photon loop

    //smear photon time in MC
    if(!isData)
    {
        double TR_SMEAR1 = 0.0;
        double TR_SMEAR2 = 0.0;
        double TR_SHIFT1 = 0.0;
        double TR_SHIFT2 = 0.0;
        int E_bin1 = 0;
        int E_bin2 = 0;
        for(int ipt = 0; ipt <N_E_divide; ipt++)
        {
            if(pho1Pt>E_divide[ipt]) E_bin1 ++;
            if(pho2Pt>E_divide[ipt]) E_bin2 ++;
        }

        if(E_bin1 >= N_E_divide) E_bin1 = N_E_divide-1;
        if(E_bin2 >= N_E_divide) E_bin2 = N_E_divide-1;

        TR_SHIFT1 = 0.001*timecorr_shift[E_bin1]; 
        TR_SHIFT2 = 0.001*timecorr_shift[E_bin2]; 

        if(pho1Pt>0.0) TR_SMEAR1 = 0.001*sqrt((timecorr_smear_aa/(pho1Pt*pho1Pt) + timecorr_smear_bb));
        if(pho2Pt>0.0) TR_SMEAR2 = 0.001*sqrt((timecorr_smear_aa/(pho2Pt*pho2Pt) + timecorr_smear_bb));

        std::random_device rd;
        std::mt19937 e2(rd());
        std::normal_distribution<> dist1(pho1ClusterTime, TR_SMEAR1);
        std::normal_distribution<> dist2(pho2ClusterTime, TR_SMEAR2);
        pho1ClusterTime_SmearToData = dist1(e2) + TR_SHIFT1;		
        pho2ClusterTime_SmearToData = dist2(e2) + TR_SHIFT2;		

        double time_smear = 0.1;
        double time_scale = 0.01;
        pho1ClusterTime_smearUp = pho1ClusterTime_SmearToData*(1.0+time_smear*random.Gaus());
        pho1ClusterTime_smearDown = pho1ClusterTime_SmearToData*(1.0-time_smear*random.Gaus());
        pho1ClusterTime_scaleUp = pho1ClusterTime_SmearToData+time_scale;
        pho1ClusterTime_scaleDown = pho1ClusterTime_SmearToData-time_scale;

    }
else
{
	pho1ClusterTime_SmearToData = pho1ClusterTime;
	pho2ClusterTime_SmearToData = pho2ClusterTime;
	pho1ClusterTime_scaleUp = pho1ClusterTime;
	pho1ClusterTime_scaleDown = pho1ClusterTime;
	pho1ClusterTime_smearUp = pho1ClusterTime;
	pho1ClusterTime_smearDown = pho1ClusterTime;
}

n_Photons_reco = nPho;

// if(nPho == 0) continue; 

deltaR_pho12 = deltaR(pho1Eta, pho1Phi, pho2Eta, pho2Phi);

HT = 0.0;
HT += pho1Pt;
if(nPho>=2) HT += pho2Pt;


//******************************************************
//compute photon efficiency scale factor
//******************************************************

if(pho1isStandardPhoton) 
{
photonEffSF = helper_GED->getPhotonScaleFactor_Tight(pho1Pt, pho1Eta, true);
if (_phodebug) std::cout << "DEBUG getPhotonScaleFactor_Tight_GED, pt = "<<pho1Pt<<", eta ="<<pho1Eta<<", sf = "<<photonEffSF<<endl;
}
else photonEffSF = helper->getPhotonScaleFactor_Tight(pho1Pt, pho1Eta, true);

//******************************************************
//compute trigger efficiency weights for MC
//******************************************************
triggerEffWeight = 1.0;
triggerEffSFWeight = 1.0;

double leadPhoPt=0;
double leadPhoEta=0;
double trailingPhoPt=0;
double trailingPhoEta=0;
if (pho1Pt > pho2Pt)
{
	leadPhoPt = pho1Pt;
	leadPhoEta = pho1Eta;
	trailingPhoPt = pho2Pt;
	trailingPhoEta= pho2Eta;
}
else
{
	leadPhoPt = pho2Pt;
	leadPhoEta = pho2Eta;
        trailingPhoPt = pho1Pt;
        trailingPhoEta= pho1Eta;
}
// Comment out because we assume trigger efficiency scale factor is 1.0
//if(nPho==1)
//{
//	triggerEffWeight = helper->getDiphotonTrigLeadingLegEff( pho1Pt, pho1Eta );
//	triggerEffSFWeight = helper->getDiphotonTrigLeadingLegEffSF( pho1Pt, pho1Eta );
//}
//else
//{
//	double triggerEffLeadingLeg = helper->getDiphotonTrigLeadingLegEff( leadPhoPt, leadPhoEta );
//	double triggerEffTrailingLeg = helper->getDiphotonTrigTrailingLegEff( trailingPhoPt, trailingPhoEta );
//	triggerEffWeight = triggerEffLeadingLeg*triggerEffTrailingLeg;
//	double triggerEffSFLeadingLeg = helper->getDiphotonTrigLeadingLegEffSF( leadPhoPt, leadPhoEta );
//	double triggerEffSFTrailingLeg = helper->getDiphotonTrigTrailingLegEffSF( trailingPhoPt, trailingPhoEta );
//	triggerEffSFWeight = triggerEffSFLeadingLeg*triggerEffSFTrailingLeg;
//}

//jet loop

std::vector<FactorizedJetCorrector*> JetCorrector = helper->getJetCorrector();
std::vector<std::pair<int,int> > JetCorrectorIOV = helper->getJetCorrectionsIOV();


vector <float> jetE_all;
vector <float> jetPt_all;
vector <float> jetEta_all;
vector <float> jetPhi_all;
float MetXCorr_JESUp = 0;
float MetYCorr_JESUp = 0;
float MetXCorr_JESDown = 0;
float MetYCorr_JESDown = 0;
vector<TLorentzVector> GoodJetsJESUp;
vector<TLorentzVector> GoodJetsJESDown;

for(int i = 0; i < nJets; i++)
{

	double JEC = JetEnergyCorrectionFactor( jetPt[i], jetEta[i], jetPhi[i], jetE[i],
                                                 fixedGridRhoAll, jetJetArea[i], runNum,
                                                 JetCorrectorIOV, JetCorrector );
	
	//cout<<"DEBUG JEC = "<<JEC<<endl;
      	TLorentzVector thisJet = makeTLorentzVector( jetPt[i]*JEC, jetEta[i], jetPhi[i], jetE[i]*JEC );

        if ( !jetPassIDTight[i] ) continue;
        if( fabs( thisJet.Eta() ) >= 3.0 ) continue;
	double deltaRJetPhoton = 0.0;
	if(nPho==1) deltaRJetPhoton = thisJet.DeltaR( pho1 );
	if(nPho>=2) deltaRJetPhoton = min( thisJet.DeltaR( pho1 ), thisJet.DeltaR( pho2 ) );
	if ( deltaRJetPhoton <= 0.3 ) continue;//According to the April 1st 2015 AN


        //JEC up and down
	double jetCorrPt = thisJet.Pt();
        double jetCorrE  = thisJet.E();
	if ( !isData )
	{
		double unc = helper->getJecUnc( jetCorrPt, jetEta[i] , 999 );
		double jetPtJESUp = jetCorrPt*(1+unc);
		double jetPtJESDown = jetCorrPt/(1+unc);
		double jetEJESUp = jetCorrE*(1+unc);
		double jetEJESDown = jetCorrE/(1+unc);
		TLorentzVector thisJetJESUp = makeTLorentzVector(jetPtJESUp, jetEta[i], jetPhi[i], jetEJESUp);
		TLorentzVector thisJetJESDown = makeTLorentzVector(jetPtJESDown, jetEta[i], jetPhi[i], jetEJESDown);

		if (jetPtJESUp > 20)
		{
			MetXCorr_JESUp += -1 * (thisJetJESUp.Px() - thisJet.Px());
			MetYCorr_JESUp += -1 * (thisJetJESUp.Py() - thisJet.Py());
		}
		if (jetPtJESDown > 20)
		{
			MetXCorr_JESDown += -1 * (thisJetJESDown.Px() - thisJet.Px());
			MetYCorr_JESDown += -1 * (thisJetJESDown.Py() - thisJet.Py());
		}


		if ( jetPtJESUp > JET_CUT )
		{
			GoodJetsJESUp.push_back(thisJetJESUp);
			n_Jets_JESUp++;
		}
		if ( jetPtJESDown > JET_CUT )
		{
			GoodJetsJESDown.push_back(thisJetJESDown);
                  	n_Jets_JESDown++;
                }
	}	
	
	if( thisJet.Pt() < JET_CUT ) continue;//According to the April 1st 2015 AN
	n_Jets++;
	//check for L1 pre-firing
	if(thisJet.Pt() > 100.0 && abs(thisJet.Eta()) > 2.25 && abs(thisJet.Eta()) < 3.0) hasJetL1PreFiring = true;
	HT += thisJet.Pt();
	jetE_all.push_back(thisJet.E());
	jetPt_all.push_back(thisJet.Pt());
	jetEta_all.push_back(thisJet.Eta());
	jetPhi_all.push_back(thisJet.Phi());
	
	if(thisJet.Pt() > jet1Pt)
	{
		jet1E = thisJet.E();	
		jet1Pt = thisJet.Pt();	
		jet1Eta = thisJet.Eta();	
		jet1Phi = thisJet.Phi();	
	}
}

 //apply nJets cut
// if(n_Jets<=2) continue;

 for(int i=0;i<jetPt_all.size();i++)
 {
	if(jetPt_all[i]>jet2Pt && jetPt_all[i]<jet1Pt)
	{
		jet2E = jetE_all[i];	
		jet2Pt = jetPt_all[i];	
		jet2Eta = jetEta_all[i];	
		jet2Phi = jetPhi_all[i];	
	}
 }

 MET = metPt;
 t1MET = metType1Pt;
	
//Calculations for JES systematics
if( !isData )
{

	TLorentzVector PFMET = makeTLorentzVectorPtEtaPhiM(metPt, 0, metPhi, 0);
	TLorentzVector t1PFMET = makeTLorentzVectorPtEtaPhiM( metType1Pt, 0, metType1Phi, 0 );

	//JES up
	float PFMetXJESUp   = PFMET.Px() + MetXCorr_JESUp;
	float PFMetYJESUp   = PFMET.Py() + MetYCorr_JESUp;
	float t1PFMetXJESUp = t1PFMET.Px() + MetXCorr_JESUp;
	float t1PFMetYJESUp = t1PFMET.Py() + MetYCorr_JESUp;

	TLorentzVector PFMET_JESUp(PFMetXJESUp, PFMetYJESUp, 0, sqrt( pow(PFMetXJESUp,2) + pow(PFMetYJESUp,2) ));
	TLorentzVector t1PFMET_JESUp(t1PFMetXJESUp, t1PFMetYJESUp, 0, sqrt( pow(t1PFMetXJESUp,2) + pow(t1PFMetYJESUp,2) ));
	MET_JESUp    = PFMET_JESUp.Pt();
	t1MET_JESUp  = t1PFMET_JESUp.Pt();

	//JES down
	float PFMetXJESDown   = PFMET.Px() + MetXCorr_JESDown;
	float PFMetYJESDown   = PFMET.Py() + MetYCorr_JESDown;
	float t1PFMetXJESDown = t1PFMET.Px() + MetXCorr_JESDown;
	float t1PFMetYJESDown = t1PFMET.Py() + MetYCorr_JESDown;
	TLorentzVector PFMET_JESDown(PFMetXJESDown, PFMetYJESDown, 0, sqrt( pow(PFMetXJESDown,2) + pow(PFMetYJESDown,2) ));
	TLorentzVector t1PFMET_JESDown(t1PFMetXJESDown, t1PFMetYJESDown, 0, sqrt( pow(t1PFMetXJESDown,2) + pow(t1PFMetYJESDown,2) ));
	MET_JESDown    = PFMET_JESDown.Pt();
       	t1MET_JESDown  = t1PFMET_JESDown.Pt();
} 

////lepton loop
vector<TLorentzVector> GoodLeptons;
vector<int> GoodLeptonType;
vector<float> GoodLeptonPt;

TLorentzVector lep1;
TLorentzVector lep2;

lep1.SetPtEtaPhiM(0,0,0,0);
lep2.SetPtEtaPhiM(0,0,0,0);

for(int i = 0; i < nMuons; i++){
 	if(muonPt[i] < 5) continue;
        if(fabs(muonEta[i]) > 2.4) continue;
	bool alreadySelected = false;
        for (uint j=0; j<GoodLeptons.size(); j++) {
          if ( deltaR(GoodLeptons[j].Eta(), GoodLeptons[j].Phi(), muonEta[i],muonPhi[i]) < 0.1) alreadySelected = true;
        }
	
	if (alreadySelected) continue;
	
	if(muonPt[i] > 20 && isLooseMuon(i)) nLooseMuons++;
	if(muonPt[i] > 20 && isTightMuon(i)) nTightMuons++;
	
	//use only tight leptons
	if(isTightMuon(i) && muonPt[i] >= 20) {	
	  
          GoodLeptonType.push_back(13 * -1 * muonCharge[i]);
          GoodLeptonPt.push_back(muonPt[i]);
	  
	  TLorentzVector thisMuon = makeTLorentzVector(muonPt[i], muonEta[i], muonPhi[i], muonE[i]);
          thisMuon.SetPtEtaPhiM( muonPt[i], muonEta[i], muonPhi[i], 0.1057);
	  GoodLeptons.push_back(thisMuon);

        }
}

for(int i = 0; i < nElectrons; i++){
	float eleCorrPt = elePt[i];
	if(eleCorrPt < 5) continue;
        if(fabs(eleEta[i]) > 2.5) continue;
	
	bool alreadySelected = false;
        for (uint j=0; j<GoodLeptons.size(); j++) {
          if ( deltaR(GoodLeptons[j].Eta(), GoodLeptons[j].Phi(), eleEta[i],elePhi[i]) < 0.1) alreadySelected = true;
        }
	
	if (alreadySelected) continue;

        if( isTightElectron(i) && eleCorrPt > 25 ) {
	  TLorentzVector thisElectron;
	  thisElectron.SetPtEtaPhiM( eleCorrPt, eleEta[i], elePhi[i], 0.000511);
	  GoodLeptons.push_back(thisElectron);
       		
          GoodLeptonType.push_back(11 * -1 * eleCharge[i]);
          GoodLeptonPt.push_back(eleCorrPt);
        }
	
}	

for(int i = 0; i < nTaus; i++){
        if (tauPt[i] < 20) continue;
        if (fabs(tauEta[i]) > 2.4) continue;
	bool alreadySelected = false;
        for (uint j=0; j<GoodLeptons.size(); j++) {
          if ( deltaR(GoodLeptons[j].Eta(), GoodLeptons[j].Phi(), tauEta[i],tauPhi[i]) < 0.1 ) alreadySelected = true;
        }

	if (alreadySelected) continue;
	if (isTightTau(i)) {
	  TLorentzVector thisTau;
          thisTau.SetPtEtaPhiM( tauPt[i], tauEta[i], tauPhi[i], 1.777);
	  GoodLeptons.push_back(thisTau);
	
	  GoodLeptonType.push_back(15);
          GoodLeptonPt.push_back(tauPt[i]);
	}	
}

//get lep1 and lep2

for (uint i=0; i<GoodLeptons.size(); i++) {
	if (GoodLeptonPt[i] > lep1Pt) {
		//swap: 1->2, this -> 1
		lep2 = lep1;
		lep2Pt = lep1Pt;
		lep2Type = lep1Type;
		lep1Pt = GoodLeptonPt[i];
		lep1Type = GoodLeptonType[i];
		lep1 =  GoodLeptons[i];	
	}
	else if (GoodLeptonPt[i] > lep2Pt) {
		//swap: this -> 2, don't change 1
		lep2Pt = GoodLeptonPt[i];
		lep2Type = GoodLeptonType[i];
		lep2 =  GoodLeptons[i];	
	}
}

mll = (lep1+lep2).M();


 //fill the output tree
 if (nPho >= 1) // require at least one photon
 { 
    	//cout << "THIS IS THE 2 PHOTON LOOP" << endl;
 	if(nPho == 1) n_Photons = 1;
 	if(nPho > 1) n_Photons = 2;

	bool isMatched = false;

	if(!isData && nPho>=2) //for two neutralino -> photon + gravitino signal MC studies only
	{
		bool foundN1 = false;
		bool foundN2 = false; 
		int pho1index = 0;
		int pho2index = 0;
		int neu1_index = 0;
		int neu2_index = 0;
		// finding the neutralino and photon index
		for(int ind_gen = 0; ind_gen < nGenParticle; ind_gen++)
		{ //this is gen particle loop within event and photon loop
			if ( !foundN1 && gParticleId[ind_gen] == 22 && gParticleMotherId[ind_gen] == 1000022 )
			{ //finds a photon from a neutralino
				pho1index = ind_gen;
				neu1_index = gParticleMotherIndex[ind_gen];
				foundN1 = true;
			}
			else if ( foundN1 && !foundN2 && gParticleId[ind_gen] == 22 && gParticleMotherId[ind_gen] == 1000022 ) 
			{
				pho2index = ind_gen;
				neu2_index = gParticleMotherIndex[ind_gen];
				foundN2 = true;
			}
		}
	
		//bool insideECAL = false;
		//if((gParticleDecayVertexX[neu1_index]*gParticleDecayVertexX[neu1_index]+gParticleDecayVertexY[neu1_index]*gParticleDecayVertexY[neu1_index] < EB_R*EB_R) && abs(gParticleDecayVertexZ[neu1_index])<300.0 && (gParticleDecayVertexX[neu2_index]*gParticleDecayVertexX[neu2_index]+gParticleDecayVertexY[neu2_index]*gParticleDecayVertexY[neu2_index] < EB_R*EB_R) && abs(gParticleDecayVertexZ[neu2_index])<300.0 ) insideECAL = true;
		//if(foundN1==1 && foundN2==1 && insideECAL)
		if(foundN1==1 && foundN2==1)
		{

			float decay_x1 = gParticleDecayVertexX[neu1_index];
			float decay_y1 = gParticleDecayVertexY[neu1_index];
			float decay_z1 = gParticleDecayVertexZ[neu1_index];
			float decay_x2 = gParticleDecayVertexX[neu2_index];
			float decay_y2 = gParticleDecayVertexY[neu2_index];
			float decay_z2 = gParticleDecayVertexZ[neu2_index];
			
			TVector3 vec_decay1(decay_x1, decay_y1, decay_z1);
			TVector3 vec_decay2(decay_x2, decay_y2, decay_z2);

			// need to match up the photon index and the reco photon - this is done based on momentum
			// pho1Pt is reco level, gpho1Pt is gen level information
			float gpho1Pt = gParticlePt[pho1index];
			float gpho2Pt = gParticlePt[pho2index];
			float deltaPt11 = fabs(pho1Pt - gpho1Pt);
			float deltaPt21 = fabs(pho1Pt - gpho2Pt);
			float deltaPt12 = fabs(pho2Pt - gpho1Pt);
			float deltaPt22 = fabs(pho2Pt - gpho2Pt);

			TVector3 genSeed1;
			TVector3 genSeed2;

			float norm1 = pow((pow(gParticlePx[pho1index],2)+pow(gParticlePy[pho1index],2)+pow(gParticlePz[pho1index],2)),0.5);
			float px1 = (gParticlePx[pho1index]) / norm1;
			float py1 = (gParticlePy[pho1index]) / norm1;
			float pz1 = (gParticlePz[pho1index]) / norm1;
			genSeed1 = intersectPoint(decay_x1, decay_y1, decay_z1, px1, py1, pz1, EB_R); // using intersection function written above, radius as 129.7 cm
			float norm2 = pow((pow(gParticlePx[pho2index],2)+pow(gParticlePy[pho2index],2)+pow(gParticlePz[pho2index],2)),0.5);
			float px2 = (gParticlePx[pho2index]) / norm2;
			float py2 = (gParticlePy[pho2index]) / norm2;
			float pz2 = (gParticlePz[pho2index]) / norm2;
			genSeed2 = intersectPoint(decay_x2, decay_y2, decay_z2, px2, py2, pz2, EB_R); // using intersection function written above, radius as 129 cm

			TVector3 recoSeed1(pho1SeedX,pho1SeedY,pho1SeedZ);
			TVector3 recoSeed2(pho2SeedX,pho2SeedY,pho2SeedZ);

			float deltaR11 = genSeed1.DeltaR(recoSeed1); 
			float deltaR12 = genSeed1.DeltaR(recoSeed2);
			float deltaR21 = genSeed2.DeltaR(recoSeed1);
			float deltaR22 = genSeed2.DeltaR(recoSeed2);

			float deltaEta11 = recoSeed1.Eta()-genSeed1.Eta();
			float deltaPhi11 = recoSeed1.Phi()-genSeed1.Phi();
			float deltaEta12 = recoSeed2.Eta()-genSeed1.Eta();
			float deltaPhi12 = recoSeed2.Phi()-genSeed1.Phi();

			float deltaEta21 = recoSeed1.Eta()-genSeed2.Eta();
			float deltaPhi21 = recoSeed1.Phi()-genSeed2.Phi();
			float deltaEta22 = recoSeed2.Eta()-genSeed2.Eta();
			float deltaPhi22 = recoSeed2.Phi()-genSeed2.Phi();

			reco_eta1 = recoSeed1.Eta();
			reco_eta2 = recoSeed2.Eta();
			
			bool is1To1 = false;
	  //cout << "deltaR11  "<<deltaR11<<"  deltaR12  "<<deltaR12<<"  deltaR21  "<<deltaR21<<"  deltaR22  "<<deltaR22<<endl;

			if ( deltaR11 < deltaR12 && deltaPt11 < deltaPt12) 
			{
				is1To1 = true;
				isMatched = true;
			}
			else if(deltaR12 < deltaR11 && deltaPt12 < deltaPt11)
			{
				is1To1 = false;
				isMatched = true;
			}
			
			if(isMatched)
			{
				pho1isDelayedPhoton = true;
				pho2isDelayedPhoton = true;
				
				pho1GenE = is1To1 ? gParticleE[pho1index] : gParticleE[pho2index];
				pho1GenPt = is1To1 ? gParticlePt[pho1index] : gParticlePt[pho2index];
				pho1GenEta = is1To1 ? gParticleEta[pho1index] : gParticleEta[pho2index];
				pho1GenPhi = is1To1 ? gParticlePhi[pho1index] : gParticlePhi[pho2index];
					
				pho2GenE = is1To1 ? gParticleE[pho2index] : gParticleE[pho1index];
				pho2GenPt = is1To1 ? gParticlePt[pho2index] : gParticlePt[pho1index];
				pho2GenEta = is1To1 ? gParticleEta[pho2index] : gParticleEta[pho1index];
				pho2GenPhi = is1To1 ? gParticlePhi[pho2index] : gParticlePhi[pho1index];
					
				R1 = is1To1 ? pow(decay_x1*decay_x1 + decay_y1*decay_y1, 0.5) : pow(decay_x2*decay_x2 + decay_y2*decay_y2, 0.5) ; 
				R2 = is1To1 ? pow(decay_x2*decay_x2 + decay_y2*decay_y2, 0.5) : pow(decay_x1*decay_x1 + decay_y1*decay_y1, 0.5) ; 
				pho1_genVtxX = is1To1 ? decay_x1 : decay_x2;
				pho2_genVtxX = is1To1 ? decay_x2 : decay_x1;
				pho1_genVtxY = is1To1 ? decay_y1 : decay_y2;
				pho2_genVtxY = is1To1 ? decay_y2 : decay_y1;
				pho1_genVtxZ = is1To1 ? decay_z1 : decay_z2;
				pho2_genVtxZ = is1To1 ? decay_z2 : decay_z1;
				pho1_genVtxEta = is1To1 ? vec_decay1.Eta() : vec_decay2.Eta();
				pho2_genVtxEta = is1To1 ? vec_decay2.Eta() : vec_decay1.Eta();
				pho1_genVtxPhi = is1To1 ? vec_decay1.Phi() : vec_decay2.Phi();
				pho2_genVtxPhi = is1To1 ? vec_decay2.Phi() : vec_decay1.Phi();

				ZD1 = is1To1 ? decay_z1 : decay_z2 ;
				ZD2 = is1To1 ? decay_z2 : decay_z1 ;

				gen_eta1 = is1To1 ? genSeed1.Eta() : genSeed2.Eta();
				gen_eta2 = is1To1 ? genSeed2.Eta() : genSeed1.Eta();
				deltaR_pho1 = is1To1 ? deltaR11 : deltaR21;
				deltaEta_pho1 = is1To1 ? deltaEta11 : deltaEta21;
				deltaPhi_pho1 = is1To1 ? deltaPhi11 : deltaPhi21;
				deltaPt_pho1 = is1To1 ? deltaPt11 : deltaPt21;
				deltaR_pho2 = is1To1 ? deltaR22 : deltaR12;
				deltaEta_pho2 = is1To1 ? deltaEta22 : deltaEta12;
				deltaPhi_pho2 = is1To1 ? deltaPhi22 : deltaPhi12;
				deltaPt_pho2 = is1To1 ? deltaPt22 : deltaPt12;

				float massNeu = 1000.0;
				//float p_neu1 = is1To1 ? (gParticlePt[neu1_index]*cosh(gParticleEta[neu1_index])) : (gParticlePt[neu2_index]*cosh(gParticleEta[neu2_index]) );
				float p_neu1 = is1To1 ? pow(gParticlePx[neu1_index]*gParticlePx[neu1_index]+gParticlePy[neu1_index]*gParticlePy[neu1_index]+gParticlePz[neu1_index]*gParticlePz[neu1_index],0.5) : pow(gParticlePx[neu2_index]*gParticlePx[neu2_index]+gParticlePy[neu2_index]*gParticlePy[neu2_index]+gParticlePz[neu2_index]*gParticlePz[neu2_index],0.5);
				//float p_neu2 = is1To1 ? (gParticlePt[neu2_index]*cosh(gParticleEta[neu2_index])) : (gParticlePt[neu1_index]*cosh(gParticleEta[neu1_index]) );
				float p_neu2 = is1To1 ? pow(gParticlePx[neu2_index]*gParticlePx[neu2_index]+gParticlePy[neu2_index]*gParticlePy[neu2_index]+gParticlePz[neu2_index]*gParticlePz[neu2_index],0.5) : pow(gParticlePx[neu1_index]*gParticlePx[neu1_index]+gParticlePy[neu1_index]*gParticlePy[neu1_index]+gParticlePz[neu1_index]*gParticlePz[neu1_index],0.5);
			
				TVector3 point_genPV(genVertexX,genVertexY,genVertexZ);	
				TVector3 point_decayV1(is1To1 ? decay_x1: decay_x2,is1To1 ? decay_y1: decay_y2, is1To1 ? decay_z1: decay_z2);
				TVector3 point_decayV2(is1To1 ? decay_x2: decay_x1,is1To1 ? decay_y2: decay_y1, is1To1 ? decay_z2: decay_z1);

				TOF_neu1 = (point_decayV1-point_genPV).Mag() / (SPEED_OF_LIGHT*p_neu1) * pow((pow(massNeu,2) + pow(p_neu1,2)),0.5);
				TOF_neu2 = (point_decayV2-point_genPV).Mag() / (SPEED_OF_LIGHT*p_neu2) * pow((pow(massNeu,2) + pow(p_neu2,2)),0.5);
				TOF_neu1_RF = TOF_neu1*massNeu*pow((pow(massNeu,2) + pow(p_neu1,2)),-0.5);
				TOF_neu2_RF = TOF_neu2*massNeu*pow((pow(massNeu,2) + pow(p_neu2,2)),-0.5);

				TOF_pho1 = (recoSeed1 - point_decayV1).Mag() / SPEED_OF_LIGHT ;
				TOF_pho2 = (recoSeed2 - point_decayV2).Mag() / SPEED_OF_LIGHT ;

				if(abs(genVertexTime) < 100.)
				{
					TOF_total1 = genVertexTime + TOF_neu1 + TOF_pho1 - recoSeed1.Mag() / SPEED_OF_LIGHT;
					TOF_total1_genV = genVertexTime + TOF_neu1 + TOF_pho1 - (recoSeed1 - point_genPV).Mag() / SPEED_OF_LIGHT;
					TOF_total2 = genVertexTime + TOF_neu2 + TOF_pho2 - recoSeed2.Mag() / SPEED_OF_LIGHT;
				TOF_total2_genV = genVertexTime + TOF_neu2 + TOF_pho2 - (recoSeed2 - point_genPV).Mag() / SPEED_OF_LIGHT;
				}
				else
				{
					TOF_total1 = TOF_neu1 + TOF_pho1 - recoSeed1.Mag() / SPEED_OF_LIGHT;
					TOF_total1_genV = TOF_neu1 + TOF_pho1 - (recoSeed1 - point_genPV).Mag() / SPEED_OF_LIGHT;
					TOF_total2 = TOF_neu2 + TOF_pho2 - recoSeed2.Mag() / SPEED_OF_LIGHT;
					TOF_total2_genV = TOF_neu2 + TOF_pho2 - (recoSeed2 - point_genPV).Mag() / SPEED_OF_LIGHT;
				}
				
				pho1angle_xtal = recoSeed1.Angle(recoSeed1 - point_decayV1); 
				pho2angle_xtal = recoSeed2.Angle(recoSeed2 - point_decayV2); 
				
			}//if isMatched
		}//if gen found
	}//if !isData


       //apply photon ID according to whether it's GED or OOT photon
       
        pho1passIsoLoose_comboIso = pho1isStandardPhoton ? pho1passIsoLoose : pho1passIsoLoose_OOT;
        pho1passIsoMedium_comboIso = pho1isStandardPhoton ? pho1passIsoMedium : pho1passIsoMedium_OOT;
        pho1passIsoTight_comboIso = pho1isStandardPhoton ? pho1passIsoTight : pho1passIsoTight_OOT;
        pho2passIsoLoose_comboIso = pho2isStandardPhoton ? pho2passIsoLoose : pho2passIsoLoose_OOT;
        pho2passIsoMedium_comboIso = pho2isStandardPhoton ? pho2passIsoMedium : pho2passIsoMedium_OOT;
        pho2passIsoTight_comboIso = pho2isStandardPhoton ? pho2passIsoTight : pho2passIsoTight_OOT;
		
	pho1passHoverELoose = pho1isStandardPhoton ? ((abs(pho1Eta)<1.4442) ? (pho1HoverE < 0.04596) : (pho1HoverE < 0.0590)) : true;
	pho1passHoverEMedium = pho1isStandardPhoton ? ((abs(pho1Eta)<1.4442) ? (pho1HoverE < 0.02197) : (pho1HoverE < 0.0326)) : true;
	pho1passHoverETight = pho1isStandardPhoton ? ((abs(pho1Eta)<1.4442) ? (pho1HoverE < 0.02148) : (pho1HoverE < 0.0321)) : true;
		
	pho2passHoverELoose = pho2isStandardPhoton ? ((abs(pho2Eta)<1.4442) ? (pho2HoverE < 0.04596) : (pho2HoverE < 0.0590)) : true;
	pho2passHoverEMedium = pho2isStandardPhoton ? ((abs(pho2Eta)<1.4442) ? (pho2HoverE < 0.02197) : (pho2HoverE < 0.0326)) : true;
	pho2passHoverETight = pho2isStandardPhoton ? ((abs(pho2Eta)<1.4442) ? (pho2HoverE < 0.02148) : (pho2HoverE < 0.0321)) : true;

	pho1passSigmaIetaIetaLoose = pho1SigmaIetaIeta < 0.022;
	pho1passSigmaIetaIetaMedium = pho1SigmaIetaIeta < 0.019;
	pho1passSigmaIetaIetaTight = pho1SigmaIetaIeta < 0.014;
	pho2passSigmaIetaIetaLoose = pho2SigmaIetaIeta < 0.022;
	pho2passSigmaIetaIetaMedium = pho2SigmaIetaIeta < 0.019;
	pho2passSigmaIetaIetaTight = pho2SigmaIetaIeta < 0.014;

	pho1passSmajorLoose  =  pho1isStandardPhoton ?  true : (pho1Smajor < 1.7);
	pho1passSmajorMedium  =  pho1isStandardPhoton ?  true : (pho1Smajor < 1.5);
	pho1passSmajorTight  =  pho1isStandardPhoton ?  true : (pho1Smajor < 1.3);

	pho2passSmajorLoose  =  pho2isStandardPhoton ?  true : (pho2Smajor < 1.7);
	pho2passSmajorMedium  =  pho2isStandardPhoton ?  true : (pho2Smajor < 1.5);
	pho2passSmajorTight  =  pho2isStandardPhoton ?  true : (pho2Smajor < 1.3);
	
    pho1passSminorLoose  =  pho1isStandardPhoton ?  true : (pho1Sminor < 0.8);
	pho1passSminorMedium  =  pho1isStandardPhoton ?  true : (pho1Sminor < 0.6);
	pho1passSminorTight  =  pho1isStandardPhoton ?  true : (pho1Sminor < 0.4);

	pho2passSminorLoose  =  pho2isStandardPhoton ?  true : (pho2Sminor < 0.8);
	pho2passSminorMedium  =  pho2isStandardPhoton ?  true : (pho2Sminor < 0.6);
	pho2passSminorTight  =  pho2isStandardPhoton ?  true : (pho2Sminor < 0.4);

	outputTree->Fill();		

   }//if nPho>=1


JetCorrector.clear();
JetCorrectorIOV.clear();

jetE_all.clear();
jetPt_all.clear();
jetEta_all.clear();
jetPhi_all.clear();
GoodJetsJESUp.clear();
GoodJetsJESDown.clear();

GoodLeptons.clear();
GoodLeptonType.clear();
GoodLeptonPt.clear();

}//event loop

cout << "Writing output trees..." << endl;
outputTree->Write();
cout << "Writing NEvents histogram..." << endl;
NEvents->Write();
cout << "Writing SumWeights histogram..." << endl;
SumWeights->Write();
cout << "Writing SumScaleWeights histogram..." << endl;
SumScaleWeights->Write();
cout << "Writing SumPdfWeights histogram..." << endl;
SumPdfWeights->Write();
outFile->Close();

//if(isData)
//{
//f_pedestal->Close();
//start_time.clear();
//end_time.clear();
//}

delete helper;
delete photonCorrector;
}//analyzer function


