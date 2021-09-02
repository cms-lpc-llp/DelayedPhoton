//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jul 13 11:48:11 2021 by ROOT version 6.14/09
// from TTree RazorEvents/selected miniAOD information
// found on file: razorNtuple.root
//////////////////////////////////////////////////////////

#ifndef razorNtuple_h
#define razorNtuple_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"
#include "vector"
#include "vector"

class razorNtuple {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Bool_t          isData;
   Int_t           nPV;
   UInt_t          runNum;
   UInt_t          nSlimmedSecondV;
   UInt_t          lumiNum;
   UInt_t          eventNum;
   UInt_t          eventTime;
   Float_t         pvX;
   Float_t         pvY;
   Float_t         pvZ;
   Float_t         fixedGridRhoAll;
   Float_t         fixedGridRhoFastjetAll;
   Float_t         fixedGridRhoFastjetAllCalo;
   Float_t         fixedGridRhoFastjetCentralCalo;
   Float_t         fixedGridRhoFastjetCentralChargedPileUp;
   Float_t         fixedGridRhoFastjetCentralNeutral;
   Int_t           nPVAll;
   Float_t         pvAllX[115];   //[nPVAll]
   Float_t         pvAllY[115];   //[nPVAll]
   Float_t         pvAllZ[115];   //[nPVAll]
   Float_t         pvAllLogSumPtSq[115];   //[nPVAll]
   Float_t         pvAllSumPx[115];   //[nPVAll]
   Float_t         pvAllSumPy[115];   //[nPVAll]
   Int_t           nBunchXing;
   Int_t           BunchXing[16];   //[nBunchXing]
   Int_t           nPU[16];   //[nBunchXing]
   Float_t         nPUmean[16];   //[nBunchXing]
   Int_t           nElectrons;
   Float_t         eleE[6];   //[nElectrons]
   Float_t         elePt[6];   //[nElectrons]
   Float_t         eleEta[6];   //[nElectrons]
   Float_t         elePhi[6];   //[nElectrons]
   Float_t         eleCharge[6];   //[nElectrons]
   Float_t         eleEta_SC[6];   //[nElectrons]
   Float_t         eleSigmaIetaIeta[6];   //[nElectrons]
   Float_t         eleFull5x5SigmaIetaIeta[6];   //[nElectrons]
   Float_t         eleR9[6];   //[nElectrons]
   Float_t         ele_dEta[6];   //[nElectrons]
   Float_t         ele_dPhi[6];   //[nElectrons]
   Float_t         ele_HoverE[6];   //[nElectrons]
   Float_t         ele_d0[6];   //[nElectrons]
   Float_t         ele_dZ[6];   //[nElectrons]
   Float_t         ele_ip3d[6];   //[nElectrons]
   Float_t         ele_ip3dSignificance[6];   //[nElectrons]
   Float_t         ele_pileupIso[6];   //[nElectrons]
   Float_t         ele_chargedIso[6];   //[nElectrons]
   Float_t         ele_photonIso[6];   //[nElectrons]
   Float_t         ele_neutralHadIso[6];   //[nElectrons]
   Int_t           ele_MissHits[6];   //[nElectrons]
   Bool_t          ele_PassConvVeto[6];   //[nElectrons]
   Float_t         ele_OneOverEminusOneOverP[6];   //[nElectrons]
   Float_t         ele_RegressionE[6];   //[nElectrons]
   Float_t         ele_CombineP4[6];   //[nElectrons]
   Float_t         ele_ptrel[6];   //[nElectrons]
   Float_t         ele_chargedMiniIso[6];   //[nElectrons]
   Float_t         ele_photonAndNeutralHadronMiniIso[6];   //[nElectrons]
   Float_t         ele_chargedPileupMiniIso[6];   //[nElectrons]
   Float_t         ele_activityMiniIsoAnnulus[6];   //[nElectrons]
   Bool_t          ele_passSingleEleTagFilter[6];   //[nElectrons]
   Bool_t          ele_passTPOneTagFilter[6];   //[nElectrons]
   Bool_t          ele_passTPTwoTagFilter[6];   //[nElectrons]
   Bool_t          ele_passTPOneProbeFilter[6];   //[nElectrons]
   Bool_t          ele_passTPTwoProbeFilter[6];   //[nElectrons]
   Bool_t          ele_passHLTFilter[6][100];   //[nElectrons]
   Bool_t          ele_cutBasedID_loose[6];   //[nElectrons]
   Bool_t          ele_cutBasedID_medium[6];   //[nElectrons]
   Bool_t          ele_cutBasedID_tight[6];   //[nElectrons]
   Float_t         ele_mvaValue[6];   //[nElectrons]
   Int_t           ele_mvaCategory[6];   //[nElectrons]
   vector<vector<unsigned int> > *ele_EcalRechitIndex;
   vector<unsigned int> *ele_SeedRechitIndex;
   Int_t           nPhotons;
   Int_t           nPhotons_overlap;
   Float_t         phoE[7];   //[nPhotons]
   Float_t         phoPt[7];   //[nPhotons]
   Float_t         phoEta[7];   //[nPhotons]
   Float_t         phoPhi[7];   //[nPhotons]
   Float_t         phoSigmaIetaIeta[7];   //[nPhotons]
   Float_t         phoFull5x5SigmaIetaIeta[7];   //[nPhotons]
   Float_t         phoR9[7];   //[nPhotons]
   Float_t         pho_sminor[7];   //[nPhotons]
   Float_t         pho_smajor[7];   //[nPhotons]
   Float_t         pho_HoverE[7];   //[nPhotons]
   Float_t         pho_sumChargedHadronPtAllVertices[7][200];   //[nPhotons]
   Float_t         pho_sumChargedHadronPt[7];   //[nPhotons]
   Float_t         pho_sumNeutralHadronEt[7];   //[nPhotons]
   Float_t         pho_sumPhotonEt[7];   //[nPhotons]
   Float_t         pho_ecalPFClusterIso[7];   //[nPhotons]
   Float_t         pho_hcalPFClusterIso[7];   //[nPhotons]
   Float_t         pho_trkSumPtHollowConeDR03[7];   //[nPhotons]
   Float_t         pho_sumWorstVertexChargedHadronPt[7];   //[nPhotons]
   Float_t         pho_pfIsoChargedHadronIso[7];   //[nPhotons]
   Float_t         pho_pfIsoChargedHadronIsoWrongVtx[7];   //[nPhotons]
   Float_t         pho_pfIsoNeutralHadronIso[7];   //[nPhotons]
   Float_t         pho_pfIsoPhotonIso[7];   //[nPhotons]
   Float_t         pho_pfIsoModFrixione[7];   //[nPhotons]
   Float_t         pho_pfIsoSumPUPt[7];   //[nPhotons]
   Bool_t          pho_isConversion[7];   //[nPhotons]
   Bool_t          pho_passEleVeto[7];   //[nPhotons]
   Float_t         pho_RegressionE[7];   //[nPhotons]
   Float_t         pho_RegressionEUncertainty[7];   //[nPhotons]
   Float_t         pho_superClusterEnergy[7];   //[nPhotons]
   Float_t         pho_superClusterRawEnergy[7];   //[nPhotons]
   Float_t         pho_superClusterEta[7];   //[nPhotons]
   Float_t         pho_superClusterPhi[7];   //[nPhotons]
   Float_t         pho_superClusterX[7];   //[nPhotons]
   Float_t         pho_superClusterY[7];   //[nPhotons]
   Float_t         pho_superClusterZ[7];   //[nPhotons]
   Bool_t          pho_hasPixelSeed[7];   //[nPhotons]
   Bool_t          pho_passHLTFilter[7][100];   //[nPhotons]
   Int_t           pho_convType[7];   //[nPhotons]
   Float_t         pho_convTrkZ[7];   //[nPhotons]
   Float_t         pho_convTrkClusZ[7];   //[nPhotons]
   Float_t         pho_vtxSumPx[7][200];   //[nPhotons]
   Float_t         pho_vtxSumPy[7][200];   //[nPhotons]
   Bool_t          pho_isStandardPhoton[7];   //[nPhotons]
   Float_t         pho_seedRecHitSwitchToGain6[7];   //[nPhotons]
   Float_t         pho_seedRecHitSwitchToGain1[7];   //[nPhotons]
   Float_t         pho_anyRecHitSwitchToGain6[7];   //[nPhotons]
   Float_t         pho_anyRecHitSwitchToGain1[7];   //[nPhotons]
   Bool_t          pho_cutBasedID_loose[7];   //[nPhotons]
   Bool_t          pho_cutBasedID_medium[7];   //[nPhotons]
   Bool_t          pho_cutBasedID_tight[7];   //[nPhotons]
   Float_t         pho_mvaValue[7];   //[nPhotons]
   Int_t           pho_mvaCategory[7];   //[nPhotons]
   Bool_t          pho_trackMatching[7];   //[nPhotons]
   Float_t         pho_energy_scale[7];   //[nPhotons]
   Float_t         pho_energy_scale_up[7];   //[nPhotons]
   Float_t         pho_energy_scale_down[7];   //[nPhotons]
   Float_t         pho_energy_smear[7];   //[nPhotons]
   vector<vector<unsigned int> > *pho_EcalRechitIndex;
   vector<unsigned int> *pho_SeedRechitIndex;
   Int_t           nJets;
   Float_t         jetE[49];   //[nJets]
   Float_t         jetPt[49];   //[nJets]
   Float_t         jetEta[49];   //[nJets]
   Float_t         jetPhi[49];   //[nJets]
   Float_t         jetCSV[49];   //[nJets]
   Float_t         jetCISV[49];   //[nJets]
   Float_t         jetProbb[49];   //[nJets]
   Float_t         jetProbc[49];   //[nJets]
   Float_t         jetProbudsg[49];   //[nJets]
   Float_t         jetProbbb[49];   //[nJets]
   Float_t         jetMass[49];   //[nJets]
   Float_t         jetJetArea[49];   //[nJets]
   Float_t         jetPileupE[49];   //[nJets]
   Float_t         jetPileupId[49];   //[nJets]
   Int_t           jetPileupIdFlag[49];   //[nJets]
   Bool_t          jetPassIDLoose[49];   //[nJets]
   Bool_t          jetPassIDTight[49];   //[nJets]
   Bool_t          jetPassMuFrac[49];   //[nJets]
   Bool_t          jetPassEleFrac[49];   //[nJets]
   Int_t           jetPartonFlavor[49];   //[nJets]
   Int_t           jetHadronFlavor[49];   //[nJets]
   Float_t         jetChargedEMEnergyFraction[49];   //[nJets]
   Float_t         jetNeutralEMEnergyFraction[49];   //[nJets]
   Float_t         jetChargedHadronEnergyFraction[49];   //[nJets]
   Float_t         jetNeutralHadronEnergyFraction[49];   //[nJets]
   Float_t         jetMuonEnergyFraction[49];   //[nJets]
   Float_t         jetHOEnergyFraction[49];   //[nJets]
   Float_t         jetHFHadronEnergyFraction[49];   //[nJets]
   Float_t         jetHFEMEnergyFraction[49];   //[nJets]
   Float_t         jetAllMuonPt[49];   //[nJets]
   Float_t         jetAllMuonEta[49];   //[nJets]
   Float_t         jetAllMuonPhi[49];   //[nJets]
   Float_t         jetAllMuonM[49];   //[nJets]
   Float_t         jetPtWeightedDZ[49];   //[nJets]
   Float_t         metPt;
   Float_t         metPhi;
   Float_t         sumMET;
   Float_t         metType0Pt;
   Float_t         metType0Phi;
   Float_t         metType1Pt_raw;
   Float_t         metType1Pt;
   Float_t         metType1Px;
   Float_t         metType1Py;
   Float_t         metType1Eta;
   Float_t         metType1Phi;
   Float_t         metType1Phi_raw;
   Float_t         metType0Plus1Pt;
   Float_t         metType0Plus1Phi;
   Float_t         metNoHFPt;
   Float_t         metNoHFPhi;
   Float_t         metPuppiPt;
   Float_t         metPuppiPhi;
   Float_t         metCaloPt;
   Float_t         metCaloPhi;
   Bool_t          Flag_HBHENoiseFilter;
   Bool_t          Flag_HBHETightNoiseFilter;
   Bool_t          Flag_HBHEIsoNoiseFilter;
   Bool_t          Flag_badChargedCandidateFilter;
   Bool_t          Flag_badMuonFilter;
   Bool_t          Flag_badGlobalMuonFilter;
   Bool_t          Flag_duplicateMuonFilter;
   Bool_t          Flag_CSCTightHaloFilter;
   Bool_t          Flag_hcalLaserEventFilter;
   Bool_t          Flag_EcalDeadCellTriggerPrimitiveFilter;
   Bool_t          Flag_EcalDeadCellBoundaryEnergyFilter;
   Bool_t          Flag_goodVertices;
   Bool_t          Flag_trackingFailureFilter;
   Bool_t          Flag_eeBadScFilter;
   Bool_t          Flag_ecalLaserCorrFilter;
   Bool_t          Flag_trkPOGFilters;
   Bool_t          Flag_trkPOG_manystripclus53X;
   Bool_t          Flag_trkPOG_toomanystripclus53X;
   Bool_t          Flag_trkPOG_logErrorTooManyClusters;
   Bool_t          Flag_BadPFMuonFilter;
   Bool_t          Flag_BadChargedCandidateFilter;
   Bool_t          Flag_ecalBadCalibFilter;
   Bool_t          Flag_METFilters;
   Bool_t          HLTDecision[1000];
   Int_t           HLTPrescale[1000];
   Float_t         HLTMR;
   Float_t         HLTRSQ;
   vector<float>   *ecalRechit_Eta;
   vector<float>   *ecalRechit_Phi;
   vector<float>   *ecalRechit_X;
   vector<float>   *ecalRechit_Y;
   vector<float>   *ecalRechit_Z;
   vector<float>   *ecalRechit_E;
   vector<float>   *ecalRechit_T;
   vector<unsigned int> *ecalRechit_ID;
   vector<bool>    *ecalRechit_FlagOOT;
   vector<bool>    *ecalRechit_GainSwitch1;
   vector<bool>    *ecalRechit_GainSwitch6;
   vector<float>   *ecalRechit_transpCorr;
   Int_t           nGenJets;
   Float_t         genJetE[26];   //[nGenJets]
   Float_t         genJetPt[26];   //[nGenJets]
   Float_t         genJetEta[26];   //[nGenJets]
   Float_t         genJetPhi[26];   //[nGenJets]
   Float_t         genMetPt;
   Float_t         genMetPhi;
   Float_t         genVertexX;
   Float_t         genVertexY;
   Float_t         genVertexZ;
   Float_t         genVertexT;
   Float_t         genWeight;
   UInt_t          genSignalProcessID;
   Float_t         genQScale;
   Float_t         genAlphaQCD;
   Float_t         genAlphaQED;
   vector<float>   *scaleWeights;
   vector<float>   *pdfWeights;
   vector<float>   *alphasWeights;
   Int_t           nGenParticle;
   Int_t           gParticleMotherId[44];   //[nGenParticle]
   Int_t           gParticleMotherIndex[44];   //[nGenParticle]
   Int_t           gParticleId[44];   //[nGenParticle]
   Int_t           gParticleStatus[44];   //[nGenParticle]
   Float_t         gParticleE[44];   //[nGenParticle]
   Float_t         gParticlePt[44];   //[nGenParticle]
   Float_t         gParticlePx[44];   //[nGenParticle]
   Float_t         gParticlePy[44];   //[nGenParticle]
   Float_t         gParticlePz[44];   //[nGenParticle]
   Float_t         gParticleEta[44];   //[nGenParticle]
   Float_t         gParticlePhi[44];   //[nGenParticle]
   Float_t         gParticleDecayVertexX[44];   //[nGenParticle]
   Float_t         gParticleDecayVertexY[44];   //[nGenParticle]
   Float_t         gParticleDecayVertexZ[44];   //[nGenParticle]
   Float_t         gParticleProductionVertexX[44];   //[nGenParticle]
   Float_t         gParticleProductionVertexY[44];   //[nGenParticle]
   Float_t         gParticleProductionVertexZ[44];   //[nGenParticle]

   // List of branches
   TBranch        *b_isData;   //!
   TBranch        *b_nPV;   //!
   TBranch        *b_runNum;   //!
   TBranch        *b_nSlimmedSecondV;   //!
   TBranch        *b_lumiNum;   //!
   TBranch        *b_eventNum;   //!
   TBranch        *b_eventTime;   //!
   TBranch        *b_pvX;   //!
   TBranch        *b_pvY;   //!
   TBranch        *b_pvZ;   //!
   TBranch        *b_fixedGridRhoAll;   //!
   TBranch        *b_fixedGridRhoFastjetAll;   //!
   TBranch        *b_fixedGridRhoFastjetAllCalo;   //!
   TBranch        *b_fixedGridRhoFastjetCentralCalo;   //!
   TBranch        *b_fixedGridRhoFastjetCentralChargedPileUp;   //!
   TBranch        *b_fixedGridRhoFastjetCentralNeutral;   //!
   TBranch        *b_nPVAll;   //!
   TBranch        *b_pvAllX;   //!
   TBranch        *b_pvAllY;   //!
   TBranch        *b_pvAllZ;   //!
   TBranch        *b_pvAllLogSumPtSq;   //!
   TBranch        *b_pvAllSumPx;   //!
   TBranch        *b_pvAllSumPy;   //!
   TBranch        *b_nBunchXing;   //!
   TBranch        *b_BunchXing;   //!
   TBranch        *b_nPU;   //!
   TBranch        *b_nPUmean;   //!
   TBranch        *b_nElectrons;   //!
   TBranch        *b_eleE;   //!
   TBranch        *b_elePt;   //!
   TBranch        *b_eleEta;   //!
   TBranch        *b_elePhi;   //!
   TBranch        *b_eleCharge;   //!
   TBranch        *b_eleEta_SC;   //!
   TBranch        *b_eleSigmaIetaIeta;   //!
   TBranch        *b_eleFull5x5SigmaIetaIeta;   //!
   TBranch        *b_eleR9;   //!
   TBranch        *b_ele_dEta;   //!
   TBranch        *b_ele_dPhi;   //!
   TBranch        *b_ele_HoverE;   //!
   TBranch        *b_ele_d0;   //!
   TBranch        *b_ele_dZ;   //!
   TBranch        *b_ele_ip3d;   //!
   TBranch        *b_ele_ip3dSignificance;   //!
   TBranch        *b_ele_pileupIso;   //!
   TBranch        *b_ele_chargedIso;   //!
   TBranch        *b_ele_photonIso;   //!
   TBranch        *b_ele_neutralHadIso;   //!
   TBranch        *b_ele_MissHits;   //!
   TBranch        *b_ele_PassConvVeto;   //!
   TBranch        *b_ele_OneOverEminusOneOverP;   //!
   TBranch        *b_ele_RegressionE;   //!
   TBranch        *b_ele_CombineP4;   //!
   TBranch        *b_ele_ptrel;   //!
   TBranch        *b_ele_chargedMiniIso;   //!
   TBranch        *b_ele_photonAndNeutralHadronMiniIso;   //!
   TBranch        *b_ele_chargedPileupMiniIso;   //!
   TBranch        *b_ele_activityMiniIsoAnnulus;   //!
   TBranch        *b_ele_passSingleEleTagFilter;   //!
   TBranch        *b_ele_passTPOneTagFilter;   //!
   TBranch        *b_ele_passTPTwoTagFilter;   //!
   TBranch        *b_ele_passTPOneProbeFilter;   //!
   TBranch        *b_ele_passTPTwoProbeFilter;   //!
   TBranch        *b_ele_passHLTFilter;   //!
   TBranch        *b_ele_cutBasedID_loose;   //!
   TBranch        *b_ele_cutBasedID_medium;   //!
   TBranch        *b_ele_cutBasedID_tight;   //!
   TBranch        *b_ele_mvaValue;   //!
   TBranch        *b_ele_mvaCategory;   //!
   TBranch        *b_ele_EcalRechitIndex;   //!
   TBranch        *b_ele_SeedRechitIndex;   //!
   TBranch        *b_nPhotons;   //!
   TBranch        *b_nPhotons_overlap;   //!
   TBranch        *b_phoE;   //!
   TBranch        *b_phoPt;   //!
   TBranch        *b_phoEta;   //!
   TBranch        *b_phoPhi;   //!
   TBranch        *b_phoSigmaIetaIeta;   //!
   TBranch        *b_phoFull5x5SigmaIetaIeta;   //!
   TBranch        *b_phoR9;   //!
   TBranch        *b_pho_sminor;   //!
   TBranch        *b_pho_smajor;   //!
   TBranch        *b_pho_HoverE;   //!
   TBranch        *b_pho_sumChargedHadronPtAllVertices;   //!
   TBranch        *b_pho_sumChargedHadronPt;   //!
   TBranch        *b_pho_sumNeutralHadronEt;   //!
   TBranch        *b_pho_sumPhotonEt;   //!
   TBranch        *b_pho_ecalPFClusterIso;   //!
   TBranch        *b_pho_hcalPFClusterIso;   //!
   TBranch        *b_pho_trkSumPtHollowConeDR03;   //!
   TBranch        *b_pho_sumWorstVertexChargedHadronPt;   //!
   TBranch        *b_pho_pfIsoChargedHadronIso;   //!
   TBranch        *b_pho_pfIsoChargedHadronIsoWrongVtx;   //!
   TBranch        *b_pho_pfIsoNeutralHadronIso;   //!
   TBranch        *b_pho_pfIsoPhotonIso;   //!
   TBranch        *b_pho_pfIsoModFrixione;   //!
   TBranch        *b_pho_pfIsoSumPUPt;   //!
   TBranch        *b_pho_isConversion;   //!
   TBranch        *b_pho_passEleVeto;   //!
   TBranch        *b_pho_RegressionE;   //!
   TBranch        *b_pho_RegressionEUncertainty;   //!
   TBranch        *b_pho_superClusterEnergy;   //!
   TBranch        *b_pho_superClusterRawEnergy;   //!
   TBranch        *b_pho_superClusterEta;   //!
   TBranch        *b_pho_superClusterPhi;   //!
   TBranch        *b_pho_superClusterX;   //!
   TBranch        *b_pho_superClusterY;   //!
   TBranch        *b_pho_superClusterZ;   //!
   TBranch        *b_pho_hasPixelSeed;   //!
   TBranch        *b_pho_passHLTFilter;   //!
   TBranch        *b_pho_convType;   //!
   TBranch        *b_pho_convTrkZ;   //!
   TBranch        *b_pho_convTrkClusZ;   //!
   TBranch        *b_pho_vtxSumPx;   //!
   TBranch        *b_pho_vtxSumPy;   //!
   TBranch        *b_pho_isStandardPhoton;   //!
   TBranch        *b_pho_seedRecHitSwitchToGain6;   //!
   TBranch        *b_pho_seedRecHitSwitchToGain1;   //!
   TBranch        *b_pho_anyRecHitSwitchToGain6;   //!
   TBranch        *b_pho_anyRecHitSwitchToGain1;   //!
   TBranch        *b_pho_cutBasedID_loose;   //!
   TBranch        *b_pho_cutBasedID_medium;   //!
   TBranch        *b_pho_cutBasedID_tight;   //!
   TBranch        *b_pho_mvaValue;   //!
   TBranch        *b_pho_mvaCategory;   //!
   TBranch        *b_pho_trackMatching;   //!
   TBranch        *b_pho_energy_scale;   //!
   TBranch        *b_pho_energy_scale_up;   //!
   TBranch        *b_pho_energy_scale_down;   //!
   TBranch        *b_pho_energy_smear;   //!
   TBranch        *b_pho_EcalRechitIndex;   //!
   TBranch        *b_pho_SeedRechitIndex;   //!
   TBranch        *b_nJets;   //!
   TBranch        *b_jetE;   //!
   TBranch        *b_jetPt;   //!
   TBranch        *b_jetEta;   //!
   TBranch        *b_jetPhi;   //!
   TBranch        *b_jetCSV;   //!
   TBranch        *b_jetCISV;   //!
   TBranch        *b_jetProbb;   //!
   TBranch        *b_jetProbc;   //!
   TBranch        *b_jetProbudsg;   //!
   TBranch        *b_jetProbbb;   //!
   TBranch        *b_jetMass;   //!
   TBranch        *b_jetJetArea;   //!
   TBranch        *b_jetPileupE;   //!
   TBranch        *b_jetPileupId;   //!
   TBranch        *b_jetPileupIdFlag;   //!
   TBranch        *b_jetPassIDLoose;   //!
   TBranch        *b_jetPassIDTight;   //!
   TBranch        *b_jetPassMuFrac;   //!
   TBranch        *b_jetPassEleFrac;   //!
   TBranch        *b_jetPartonFlavor;   //!
   TBranch        *b_jetHadronFlavor;   //!
   TBranch        *b_jetChargedEMEnergyFraction;   //!
   TBranch        *b_jetNeutralEMEnergyFraction;   //!
   TBranch        *b_jetChargedHadronEnergyFraction;   //!
   TBranch        *b_jetNeutralHadronEnergyFraction;   //!
   TBranch        *b_jetMuonEnergyFraction;   //!
   TBranch        *b_jetHOEnergyFraction;   //!
   TBranch        *b_jetHFHadronEnergyFraction;   //!
   TBranch        *b_jetHFEMEnergyFraction;   //!
   TBranch        *b_jetAllMuonPt;   //!
   TBranch        *b_jetAllMuonEta;   //!
   TBranch        *b_jetAllMuonPhi;   //!
   TBranch        *b_jetAllMuonM;   //!
   TBranch        *b_jetPtWeightedDZ;   //!
   TBranch        *b_metPt;   //!
   TBranch        *b_metPhi;   //!
   TBranch        *b_sumMET;   //!
   TBranch        *b_metType0Pt;   //!
   TBranch        *b_metType0Phi;   //!
   TBranch        *b_metType1Pt_raw;   //!
   TBranch        *b_metType1Pt;   //!
   TBranch        *b_metType1Px;   //!
   TBranch        *b_metType1Py;   //!
   TBranch        *b_metType1Eta;   //!
   TBranch        *b_metType1Phi;   //!
   TBranch        *b_metType1Phi_raw;   //!
   TBranch        *b_metType0Plus1Pt;   //!
   TBranch        *b_metType0Plus1Phi;   //!
   TBranch        *b_metNoHFPt;   //!
   TBranch        *b_metNoHFPhi;   //!
   TBranch        *b_metPuppiPt;   //!
   TBranch        *b_metPuppiPhi;   //!
   TBranch        *b_metCaloPt;   //!
   TBranch        *b_metCaloPhi;   //!
   TBranch        *b_Flag_HBHENoiseFilter;   //!
   TBranch        *b_Flag_HBHETightNoiseFilter;   //!
   TBranch        *b_Flag_HBHEIsoNoiseFilter;   //!
   TBranch        *b_Flag_badChargedCandidateFilter;   //!
   TBranch        *b_Flag_badMuonFilter;   //!
   TBranch        *b_Flag_badGlobalMuonFilter;   //!
   TBranch        *b_Flag_duplicateMuonFilter;   //!
   TBranch        *b_Flag_CSCTightHaloFilter;   //!
   TBranch        *b_Flag_hcalLaserEventFilter;   //!
   TBranch        *b_Flag_EcalDeadCellTriggerPrimitiveFilter;   //!
   TBranch        *b_Flag_EcalDeadCellBoundaryEnergyFilter;   //!
   TBranch        *b_Flag_goodVertices;   //!
   TBranch        *b_Flag_trackingFailureFilter;   //!
   TBranch        *b_Flag_eeBadScFilter;   //!
   TBranch        *b_Flag_ecalLaserCorrFilter;   //!
   TBranch        *b_Flag_trkPOGFilters;   //!
   TBranch        *b_Flag_trkPOG_manystripclus53X;   //!
   TBranch        *b_Flag_trkPOG_toomanystripclus53X;   //!
   TBranch        *b_Flag_trkPOG_logErrorTooManyClusters;   //!
   TBranch        *b_Flag_BadPFMuonFilter;   //!
   TBranch        *b_Flag_BadChargedCandidateFilter;   //!
   TBranch        *b_Flag_ecalBadCalibFilter;   //!
   TBranch        *b_Flag_METFilters;   //!
   TBranch        *b_HLTDecision;   //!
   TBranch        *b_HLTPrescale;   //!
   TBranch        *b_HLTMR;   //!
   TBranch        *b_HLTRSQ;   //!
   TBranch        *b_ecalRechit_Eta;   //!
   TBranch        *b_ecalRechit_Phi;   //!
   TBranch        *b_ecalRechit_X;   //!
   TBranch        *b_ecalRechit_Y;   //!
   TBranch        *b_ecalRechit_Z;   //!
   TBranch        *b_ecalRechit_E;   //!
   TBranch        *b_ecalRechit_T;   //!
   TBranch        *b_ecalRechit_ID;   //!
   TBranch        *b_ecalRechit_FlagOOT;   //!
   TBranch        *b_ecalRechit_GainSwitch1;   //!
   TBranch        *b_ecalRechit_GainSwitch6;   //!
   TBranch        *b_ecalRechit_transpCorr;   //!
   TBranch        *b_nGenJets;   //!
   TBranch        *b_genJetE;   //!
   TBranch        *b_genJetPt;   //!
   TBranch        *b_genJetEta;   //!
   TBranch        *b_genJetPhi;   //!
   TBranch        *b_genMetPt;   //!
   TBranch        *b_genMetPhi;   //!
   TBranch        *b_genVertexX;   //!
   TBranch        *b_genVertexY;   //!
   TBranch        *b_genVertexZ;   //!
   TBranch        *b_genVertexT;   //!
   TBranch        *b_genWeight;   //!
   TBranch        *b_genSignalProcessID;   //!
   TBranch        *b_genQScale;   //!
   TBranch        *b_genAlphaQCD;   //!
   TBranch        *b_genAlphaQED;   //!
   TBranch        *b_scaleWeights;   //!
   TBranch        *b_pdfWeights;   //!
   TBranch        *b_alphasWeights;   //!
   TBranch        *b_nGenParticle;   //!
   TBranch        *b_gParticleMotherId;   //!
   TBranch        *b_gParticleMotherIndex;   //!
   TBranch        *b_gParticleId;   //!
   TBranch        *b_gParticleStatus;   //!
   TBranch        *b_gParticleE;   //!
   TBranch        *b_gParticlePt;   //!
   TBranch        *b_gParticlePx;   //!
   TBranch        *b_gParticlePy;   //!
   TBranch        *b_gParticlePz;   //!
   TBranch        *b_gParticleEta;   //!
   TBranch        *b_gParticlePhi;   //!
   TBranch        *b_gParticleDecayVertexX;   //!
   TBranch        *b_gParticleDecayVertexY;   //!
   TBranch        *b_gParticleDecayVertexZ;   //!
   TBranch        *b_gParticleProductionVertexX;   //!
   TBranch        *b_gParticleProductionVertexY;   //!
   TBranch        *b_gParticleProductionVertexZ;   //!

   razorNtuple(TTree *tree=0);
   virtual ~razorNtuple();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef razorNtuple_cxx
razorNtuple::razorNtuple(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/yeseo/work/LLP/resonant_Photon/sample/razorNtuple.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/home/yeseo/work/LLP/resonant_Photon/sample/razorNtuple.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("/home/yeseo/work/LLP/resonant_Photon/sample/razorNtuple.root:/ntuples");
      dir->GetObject("RazorEvents",tree);

   }
   Init(tree);
}

razorNtuple::~razorNtuple()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t razorNtuple::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t razorNtuple::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void razorNtuple::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   ele_EcalRechitIndex = 0;
   ele_SeedRechitIndex = 0;
   pho_EcalRechitIndex = 0;
   pho_SeedRechitIndex = 0;
   ecalRechit_Eta = 0;
   ecalRechit_Phi = 0;
   ecalRechit_X = 0;
   ecalRechit_Y = 0;
   ecalRechit_Z = 0;
   ecalRechit_E = 0;
   ecalRechit_T = 0;
   ecalRechit_ID = 0;
   ecalRechit_FlagOOT = 0;
   ecalRechit_GainSwitch1 = 0;
   ecalRechit_GainSwitch6 = 0;
   ecalRechit_transpCorr = 0;
   scaleWeights = 0;
   pdfWeights = 0;
   alphasWeights = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("isData", &isData, &b_isData);
   fChain->SetBranchAddress("nPV", &nPV, &b_nPV);
   fChain->SetBranchAddress("runNum", &runNum, &b_runNum);
   fChain->SetBranchAddress("nSlimmedSecondV", &nSlimmedSecondV, &b_nSlimmedSecondV);
   fChain->SetBranchAddress("lumiNum", &lumiNum, &b_lumiNum);
   fChain->SetBranchAddress("eventNum", &eventNum, &b_eventNum);
   fChain->SetBranchAddress("eventTime", &eventTime, &b_eventTime);
   fChain->SetBranchAddress("pvX", &pvX, &b_pvX);
   fChain->SetBranchAddress("pvY", &pvY, &b_pvY);
   fChain->SetBranchAddress("pvZ", &pvZ, &b_pvZ);
   fChain->SetBranchAddress("fixedGridRhoAll", &fixedGridRhoAll, &b_fixedGridRhoAll);
   fChain->SetBranchAddress("fixedGridRhoFastjetAll", &fixedGridRhoFastjetAll, &b_fixedGridRhoFastjetAll);
   fChain->SetBranchAddress("fixedGridRhoFastjetAllCalo", &fixedGridRhoFastjetAllCalo, &b_fixedGridRhoFastjetAllCalo);
   fChain->SetBranchAddress("fixedGridRhoFastjetCentralCalo", &fixedGridRhoFastjetCentralCalo, &b_fixedGridRhoFastjetCentralCalo);
   fChain->SetBranchAddress("fixedGridRhoFastjetCentralChargedPileUp", &fixedGridRhoFastjetCentralChargedPileUp, &b_fixedGridRhoFastjetCentralChargedPileUp);
   fChain->SetBranchAddress("fixedGridRhoFastjetCentralNeutral", &fixedGridRhoFastjetCentralNeutral, &b_fixedGridRhoFastjetCentralNeutral);
   fChain->SetBranchAddress("nPVAll", &nPVAll, &b_nPVAll);
   fChain->SetBranchAddress("pvAllX", pvAllX, &b_pvAllX);
   fChain->SetBranchAddress("pvAllY", pvAllY, &b_pvAllY);
   fChain->SetBranchAddress("pvAllZ", pvAllZ, &b_pvAllZ);
   fChain->SetBranchAddress("pvAllLogSumPtSq", pvAllLogSumPtSq, &b_pvAllLogSumPtSq);
   fChain->SetBranchAddress("pvAllSumPx", pvAllSumPx, &b_pvAllSumPx);
   fChain->SetBranchAddress("pvAllSumPy", pvAllSumPy, &b_pvAllSumPy);
   fChain->SetBranchAddress("nBunchXing", &nBunchXing, &b_nBunchXing);
   fChain->SetBranchAddress("BunchXing", BunchXing, &b_BunchXing);
   fChain->SetBranchAddress("nPU", nPU, &b_nPU);
   fChain->SetBranchAddress("nPUmean", nPUmean, &b_nPUmean);
   fChain->SetBranchAddress("nElectrons", &nElectrons, &b_nElectrons);
   fChain->SetBranchAddress("eleE", eleE, &b_eleE);
   fChain->SetBranchAddress("elePt", elePt, &b_elePt);
   fChain->SetBranchAddress("eleEta", eleEta, &b_eleEta);
   fChain->SetBranchAddress("elePhi", elePhi, &b_elePhi);
   fChain->SetBranchAddress("eleCharge", eleCharge, &b_eleCharge);
   fChain->SetBranchAddress("eleEta_SC", eleEta_SC, &b_eleEta_SC);
   fChain->SetBranchAddress("eleSigmaIetaIeta", eleSigmaIetaIeta, &b_eleSigmaIetaIeta);
   fChain->SetBranchAddress("eleFull5x5SigmaIetaIeta", eleFull5x5SigmaIetaIeta, &b_eleFull5x5SigmaIetaIeta);
   fChain->SetBranchAddress("eleR9", eleR9, &b_eleR9);
   fChain->SetBranchAddress("ele_dEta", ele_dEta, &b_ele_dEta);
   fChain->SetBranchAddress("ele_dPhi", ele_dPhi, &b_ele_dPhi);
   fChain->SetBranchAddress("ele_HoverE", ele_HoverE, &b_ele_HoverE);
   fChain->SetBranchAddress("ele_d0", ele_d0, &b_ele_d0);
   fChain->SetBranchAddress("ele_dZ", ele_dZ, &b_ele_dZ);
   fChain->SetBranchAddress("ele_ip3d", ele_ip3d, &b_ele_ip3d);
   fChain->SetBranchAddress("ele_ip3dSignificance", ele_ip3dSignificance, &b_ele_ip3dSignificance);
   fChain->SetBranchAddress("ele_pileupIso", ele_pileupIso, &b_ele_pileupIso);
   fChain->SetBranchAddress("ele_chargedIso", ele_chargedIso, &b_ele_chargedIso);
   fChain->SetBranchAddress("ele_photonIso", ele_photonIso, &b_ele_photonIso);
   fChain->SetBranchAddress("ele_neutralHadIso", ele_neutralHadIso, &b_ele_neutralHadIso);
   fChain->SetBranchAddress("ele_MissHits", ele_MissHits, &b_ele_MissHits);
   fChain->SetBranchAddress("ele_PassConvVeto", ele_PassConvVeto, &b_ele_PassConvVeto);
   fChain->SetBranchAddress("ele_OneOverEminusOneOverP", ele_OneOverEminusOneOverP, &b_ele_OneOverEminusOneOverP);
   fChain->SetBranchAddress("ele_RegressionE", ele_RegressionE, &b_ele_RegressionE);
   fChain->SetBranchAddress("ele_CombineP4", ele_CombineP4, &b_ele_CombineP4);
   fChain->SetBranchAddress("ele_ptrel", ele_ptrel, &b_ele_ptrel);
   fChain->SetBranchAddress("ele_chargedMiniIso", ele_chargedMiniIso, &b_ele_chargedMiniIso);
   fChain->SetBranchAddress("ele_photonAndNeutralHadronMiniIso", ele_photonAndNeutralHadronMiniIso, &b_ele_photonAndNeutralHadronMiniIso);
   fChain->SetBranchAddress("ele_chargedPileupMiniIso", ele_chargedPileupMiniIso, &b_ele_chargedPileupMiniIso);
   fChain->SetBranchAddress("ele_activityMiniIsoAnnulus", ele_activityMiniIsoAnnulus, &b_ele_activityMiniIsoAnnulus);
   fChain->SetBranchAddress("ele_passSingleEleTagFilter", ele_passSingleEleTagFilter, &b_ele_passSingleEleTagFilter);
   fChain->SetBranchAddress("ele_passTPOneTagFilter", ele_passTPOneTagFilter, &b_ele_passTPOneTagFilter);
   fChain->SetBranchAddress("ele_passTPTwoTagFilter", ele_passTPTwoTagFilter, &b_ele_passTPTwoTagFilter);
   fChain->SetBranchAddress("ele_passTPOneProbeFilter", ele_passTPOneProbeFilter, &b_ele_passTPOneProbeFilter);
   fChain->SetBranchAddress("ele_passTPTwoProbeFilter", ele_passTPTwoProbeFilter, &b_ele_passTPTwoProbeFilter);
   fChain->SetBranchAddress("ele_passHLTFilter", ele_passHLTFilter, &b_ele_passHLTFilter);
   fChain->SetBranchAddress("ele_cutBasedID_loose", ele_cutBasedID_loose, &b_ele_cutBasedID_loose);
   fChain->SetBranchAddress("ele_cutBasedID_medium", ele_cutBasedID_medium, &b_ele_cutBasedID_medium);
   fChain->SetBranchAddress("ele_cutBasedID_tight", ele_cutBasedID_tight, &b_ele_cutBasedID_tight);
   fChain->SetBranchAddress("ele_mvaValue", ele_mvaValue, &b_ele_mvaValue);
   fChain->SetBranchAddress("ele_mvaCategory", ele_mvaCategory, &b_ele_mvaCategory);
   fChain->SetBranchAddress("ele_EcalRechitIndex", &ele_EcalRechitIndex, &b_ele_EcalRechitIndex);
   fChain->SetBranchAddress("ele_SeedRechitIndex", &ele_SeedRechitIndex, &b_ele_SeedRechitIndex);
   fChain->SetBranchAddress("nPhotons", &nPhotons, &b_nPhotons);
   fChain->SetBranchAddress("nPhotons_overlap", &nPhotons_overlap, &b_nPhotons_overlap);
   fChain->SetBranchAddress("phoE", phoE, &b_phoE);
   fChain->SetBranchAddress("phoPt", phoPt, &b_phoPt);
   fChain->SetBranchAddress("phoEta", phoEta, &b_phoEta);
   fChain->SetBranchAddress("phoPhi", phoPhi, &b_phoPhi);
   fChain->SetBranchAddress("phoSigmaIetaIeta", phoSigmaIetaIeta, &b_phoSigmaIetaIeta);
   fChain->SetBranchAddress("phoFull5x5SigmaIetaIeta", phoFull5x5SigmaIetaIeta, &b_phoFull5x5SigmaIetaIeta);
   fChain->SetBranchAddress("phoR9", phoR9, &b_phoR9);
   fChain->SetBranchAddress("pho_sminor", pho_sminor, &b_pho_sminor);
   fChain->SetBranchAddress("pho_smajor", pho_smajor, &b_pho_smajor);
   fChain->SetBranchAddress("pho_HoverE", pho_HoverE, &b_pho_HoverE);
   fChain->SetBranchAddress("pho_sumChargedHadronPtAllVertices", pho_sumChargedHadronPtAllVertices, &b_pho_sumChargedHadronPtAllVertices);
   fChain->SetBranchAddress("pho_sumChargedHadronPt", pho_sumChargedHadronPt, &b_pho_sumChargedHadronPt);
   fChain->SetBranchAddress("pho_sumNeutralHadronEt", pho_sumNeutralHadronEt, &b_pho_sumNeutralHadronEt);
   fChain->SetBranchAddress("pho_sumPhotonEt", pho_sumPhotonEt, &b_pho_sumPhotonEt);
   fChain->SetBranchAddress("pho_ecalPFClusterIso", pho_ecalPFClusterIso, &b_pho_ecalPFClusterIso);
   fChain->SetBranchAddress("pho_hcalPFClusterIso", pho_hcalPFClusterIso, &b_pho_hcalPFClusterIso);
   fChain->SetBranchAddress("pho_trkSumPtHollowConeDR03", pho_trkSumPtHollowConeDR03, &b_pho_trkSumPtHollowConeDR03);
   fChain->SetBranchAddress("pho_sumWorstVertexChargedHadronPt", pho_sumWorstVertexChargedHadronPt, &b_pho_sumWorstVertexChargedHadronPt);
   fChain->SetBranchAddress("pho_pfIsoChargedHadronIso", pho_pfIsoChargedHadronIso, &b_pho_pfIsoChargedHadronIso);
   fChain->SetBranchAddress("pho_pfIsoChargedHadronIsoWrongVtx", pho_pfIsoChargedHadronIsoWrongVtx, &b_pho_pfIsoChargedHadronIsoWrongVtx);
   fChain->SetBranchAddress("pho_pfIsoNeutralHadronIso", pho_pfIsoNeutralHadronIso, &b_pho_pfIsoNeutralHadronIso);
   fChain->SetBranchAddress("pho_pfIsoPhotonIso", pho_pfIsoPhotonIso, &b_pho_pfIsoPhotonIso);
   fChain->SetBranchAddress("pho_pfIsoModFrixione", pho_pfIsoModFrixione, &b_pho_pfIsoModFrixione);
   fChain->SetBranchAddress("pho_pfIsoSumPUPt", pho_pfIsoSumPUPt, &b_pho_pfIsoSumPUPt);
   fChain->SetBranchAddress("pho_isConversion", pho_isConversion, &b_pho_isConversion);
   fChain->SetBranchAddress("pho_passEleVeto", pho_passEleVeto, &b_pho_passEleVeto);
   fChain->SetBranchAddress("pho_RegressionE", pho_RegressionE, &b_pho_RegressionE);
   fChain->SetBranchAddress("pho_RegressionEUncertainty", pho_RegressionEUncertainty, &b_pho_RegressionEUncertainty);
   fChain->SetBranchAddress("pho_superClusterEnergy", pho_superClusterEnergy, &b_pho_superClusterEnergy);
   fChain->SetBranchAddress("pho_superClusterRawEnergy", pho_superClusterRawEnergy, &b_pho_superClusterRawEnergy);
   fChain->SetBranchAddress("pho_superClusterEta", pho_superClusterEta, &b_pho_superClusterEta);
   fChain->SetBranchAddress("pho_superClusterPhi", pho_superClusterPhi, &b_pho_superClusterPhi);
   fChain->SetBranchAddress("pho_superClusterX", pho_superClusterX, &b_pho_superClusterX);
   fChain->SetBranchAddress("pho_superClusterY", pho_superClusterY, &b_pho_superClusterY);
   fChain->SetBranchAddress("pho_superClusterZ", pho_superClusterZ, &b_pho_superClusterZ);
   fChain->SetBranchAddress("pho_hasPixelSeed", pho_hasPixelSeed, &b_pho_hasPixelSeed);
   fChain->SetBranchAddress("pho_passHLTFilter", pho_passHLTFilter, &b_pho_passHLTFilter);
   fChain->SetBranchAddress("pho_convType", pho_convType, &b_pho_convType);
   fChain->SetBranchAddress("pho_convTrkZ", pho_convTrkZ, &b_pho_convTrkZ);
   fChain->SetBranchAddress("pho_convTrkClusZ", pho_convTrkClusZ, &b_pho_convTrkClusZ);
   fChain->SetBranchAddress("pho_vtxSumPx", pho_vtxSumPx, &b_pho_vtxSumPx);
   fChain->SetBranchAddress("pho_vtxSumPy", pho_vtxSumPy, &b_pho_vtxSumPy);
   fChain->SetBranchAddress("pho_isStandardPhoton", pho_isStandardPhoton, &b_pho_isStandardPhoton);
   fChain->SetBranchAddress("pho_seedRecHitSwitchToGain6", pho_seedRecHitSwitchToGain6, &b_pho_seedRecHitSwitchToGain6);
   fChain->SetBranchAddress("pho_seedRecHitSwitchToGain1", pho_seedRecHitSwitchToGain1, &b_pho_seedRecHitSwitchToGain1);
   fChain->SetBranchAddress("pho_anyRecHitSwitchToGain6", pho_anyRecHitSwitchToGain6, &b_pho_anyRecHitSwitchToGain6);
   fChain->SetBranchAddress("pho_anyRecHitSwitchToGain1", pho_anyRecHitSwitchToGain1, &b_pho_anyRecHitSwitchToGain1);
   fChain->SetBranchAddress("pho_cutBasedID_loose", pho_cutBasedID_loose, &b_pho_cutBasedID_loose);
   fChain->SetBranchAddress("pho_cutBasedID_medium", pho_cutBasedID_medium, &b_pho_cutBasedID_medium);
   fChain->SetBranchAddress("pho_cutBasedID_tight", pho_cutBasedID_tight, &b_pho_cutBasedID_tight);
   fChain->SetBranchAddress("pho_mvaValue", pho_mvaValue, &b_pho_mvaValue);
   fChain->SetBranchAddress("pho_mvaCategory", pho_mvaCategory, &b_pho_mvaCategory);
   fChain->SetBranchAddress("pho_trackMatching", pho_trackMatching, &b_pho_trackMatching);
   fChain->SetBranchAddress("pho_energy_scale", pho_energy_scale, &b_pho_energy_scale);
   fChain->SetBranchAddress("pho_energy_scale_up", pho_energy_scale_up, &b_pho_energy_scale_up);
   fChain->SetBranchAddress("pho_energy_scale_down", pho_energy_scale_down, &b_pho_energy_scale_down);
   fChain->SetBranchAddress("pho_energy_smear", pho_energy_smear, &b_pho_energy_smear);
   fChain->SetBranchAddress("pho_EcalRechitIndex", &pho_EcalRechitIndex, &b_pho_EcalRechitIndex);
   fChain->SetBranchAddress("pho_SeedRechitIndex", &pho_SeedRechitIndex, &b_pho_SeedRechitIndex);
   fChain->SetBranchAddress("nJets", &nJets, &b_nJets);
   fChain->SetBranchAddress("jetE", jetE, &b_jetE);
   fChain->SetBranchAddress("jetPt", jetPt, &b_jetPt);
   fChain->SetBranchAddress("jetEta", jetEta, &b_jetEta);
   fChain->SetBranchAddress("jetPhi", jetPhi, &b_jetPhi);
   fChain->SetBranchAddress("jetCSV", jetCSV, &b_jetCSV);
   fChain->SetBranchAddress("jetCISV", jetCISV, &b_jetCISV);
   fChain->SetBranchAddress("jetProbb", jetProbb, &b_jetProbb);
   fChain->SetBranchAddress("jetProbc", jetProbc, &b_jetProbc);
   fChain->SetBranchAddress("jetProbudsg", jetProbudsg, &b_jetProbudsg);
   fChain->SetBranchAddress("jetProbbb", jetProbbb, &b_jetProbbb);
   fChain->SetBranchAddress("jetMass", jetMass, &b_jetMass);
   fChain->SetBranchAddress("jetJetArea", jetJetArea, &b_jetJetArea);
   fChain->SetBranchAddress("jetPileupE", jetPileupE, &b_jetPileupE);
   fChain->SetBranchAddress("jetPileupId", jetPileupId, &b_jetPileupId);
   fChain->SetBranchAddress("jetPileupIdFlag", jetPileupIdFlag, &b_jetPileupIdFlag);
   fChain->SetBranchAddress("jetPassIDLoose", jetPassIDLoose, &b_jetPassIDLoose);
   fChain->SetBranchAddress("jetPassIDTight", jetPassIDTight, &b_jetPassIDTight);
   fChain->SetBranchAddress("jetPassMuFrac", jetPassMuFrac, &b_jetPassMuFrac);
   fChain->SetBranchAddress("jetPassEleFrac", jetPassEleFrac, &b_jetPassEleFrac);
   fChain->SetBranchAddress("jetPartonFlavor", jetPartonFlavor, &b_jetPartonFlavor);
   fChain->SetBranchAddress("jetHadronFlavor", jetHadronFlavor, &b_jetHadronFlavor);
   fChain->SetBranchAddress("jetChargedEMEnergyFraction", jetChargedEMEnergyFraction, &b_jetChargedEMEnergyFraction);
   fChain->SetBranchAddress("jetNeutralEMEnergyFraction", jetNeutralEMEnergyFraction, &b_jetNeutralEMEnergyFraction);
   fChain->SetBranchAddress("jetChargedHadronEnergyFraction", jetChargedHadronEnergyFraction, &b_jetChargedHadronEnergyFraction);
   fChain->SetBranchAddress("jetNeutralHadronEnergyFraction", jetNeutralHadronEnergyFraction, &b_jetNeutralHadronEnergyFraction);
   fChain->SetBranchAddress("jetMuonEnergyFraction", jetMuonEnergyFraction, &b_jetMuonEnergyFraction);
   fChain->SetBranchAddress("jetHOEnergyFraction", jetHOEnergyFraction, &b_jetHOEnergyFraction);
   fChain->SetBranchAddress("jetHFHadronEnergyFraction", jetHFHadronEnergyFraction, &b_jetHFHadronEnergyFraction);
   fChain->SetBranchAddress("jetHFEMEnergyFraction", jetHFEMEnergyFraction, &b_jetHFEMEnergyFraction);
   fChain->SetBranchAddress("jetAllMuonPt", jetAllMuonPt, &b_jetAllMuonPt);
   fChain->SetBranchAddress("jetAllMuonEta", jetAllMuonEta, &b_jetAllMuonEta);
   fChain->SetBranchAddress("jetAllMuonPhi", jetAllMuonPhi, &b_jetAllMuonPhi);
   fChain->SetBranchAddress("jetAllMuonM", jetAllMuonM, &b_jetAllMuonM);
   fChain->SetBranchAddress("jetPtWeightedDZ", jetPtWeightedDZ, &b_jetPtWeightedDZ);
   fChain->SetBranchAddress("metPt", &metPt, &b_metPt);
   fChain->SetBranchAddress("metPhi", &metPhi, &b_metPhi);
   fChain->SetBranchAddress("sumMET", &sumMET, &b_sumMET);
   fChain->SetBranchAddress("metType0Pt", &metType0Pt, &b_metType0Pt);
   fChain->SetBranchAddress("metType0Phi", &metType0Phi, &b_metType0Phi);
   fChain->SetBranchAddress("metType1Pt_raw", &metType1Pt_raw, &b_metType1Pt_raw);
   fChain->SetBranchAddress("metType1Pt", &metType1Pt, &b_metType1Pt);
   fChain->SetBranchAddress("metType1Px", &metType1Px, &b_metType1Px);
   fChain->SetBranchAddress("metType1Py", &metType1Py, &b_metType1Py);
   fChain->SetBranchAddress("metType1Eta", &metType1Eta, &b_metType1Eta);
   fChain->SetBranchAddress("metType1Phi", &metType1Phi, &b_metType1Phi);
   fChain->SetBranchAddress("metType1Phi_raw", &metType1Phi_raw, &b_metType1Phi_raw);
   fChain->SetBranchAddress("metType0Plus1Pt", &metType0Plus1Pt, &b_metType0Plus1Pt);
   fChain->SetBranchAddress("metType0Plus1Phi", &metType0Plus1Phi, &b_metType0Plus1Phi);
   fChain->SetBranchAddress("metNoHFPt", &metNoHFPt, &b_metNoHFPt);
   fChain->SetBranchAddress("metNoHFPhi", &metNoHFPhi, &b_metNoHFPhi);
   fChain->SetBranchAddress("metPuppiPt", &metPuppiPt, &b_metPuppiPt);
   fChain->SetBranchAddress("metPuppiPhi", &metPuppiPhi, &b_metPuppiPhi);
   fChain->SetBranchAddress("metCaloPt", &metCaloPt, &b_metCaloPt);
   fChain->SetBranchAddress("metCaloPhi", &metCaloPhi, &b_metCaloPhi);
   fChain->SetBranchAddress("Flag_HBHENoiseFilter", &Flag_HBHENoiseFilter, &b_Flag_HBHENoiseFilter);
   fChain->SetBranchAddress("Flag_HBHETightNoiseFilter", &Flag_HBHETightNoiseFilter, &b_Flag_HBHETightNoiseFilter);
   fChain->SetBranchAddress("Flag_HBHEIsoNoiseFilter", &Flag_HBHEIsoNoiseFilter, &b_Flag_HBHEIsoNoiseFilter);
   fChain->SetBranchAddress("Flag_badChargedCandidateFilter", &Flag_badChargedCandidateFilter, &b_Flag_badChargedCandidateFilter);
   fChain->SetBranchAddress("Flag_badMuonFilter", &Flag_badMuonFilter, &b_Flag_badMuonFilter);
   fChain->SetBranchAddress("Flag_badGlobalMuonFilter", &Flag_badGlobalMuonFilter, &b_Flag_badGlobalMuonFilter);
   fChain->SetBranchAddress("Flag_duplicateMuonFilter", &Flag_duplicateMuonFilter, &b_Flag_duplicateMuonFilter);
   fChain->SetBranchAddress("Flag_CSCTightHaloFilter", &Flag_CSCTightHaloFilter, &b_Flag_CSCTightHaloFilter);
   fChain->SetBranchAddress("Flag_hcalLaserEventFilter", &Flag_hcalLaserEventFilter, &b_Flag_hcalLaserEventFilter);
   fChain->SetBranchAddress("Flag_EcalDeadCellTriggerPrimitiveFilter", &Flag_EcalDeadCellTriggerPrimitiveFilter, &b_Flag_EcalDeadCellTriggerPrimitiveFilter);
   fChain->SetBranchAddress("Flag_EcalDeadCellBoundaryEnergyFilter", &Flag_EcalDeadCellBoundaryEnergyFilter, &b_Flag_EcalDeadCellBoundaryEnergyFilter);
   fChain->SetBranchAddress("Flag_goodVertices", &Flag_goodVertices, &b_Flag_goodVertices);
   fChain->SetBranchAddress("Flag_trackingFailureFilter", &Flag_trackingFailureFilter, &b_Flag_trackingFailureFilter);
   fChain->SetBranchAddress("Flag_eeBadScFilter", &Flag_eeBadScFilter, &b_Flag_eeBadScFilter);
   fChain->SetBranchAddress("Flag_ecalLaserCorrFilter", &Flag_ecalLaserCorrFilter, &b_Flag_ecalLaserCorrFilter);
   fChain->SetBranchAddress("Flag_trkPOGFilters", &Flag_trkPOGFilters, &b_Flag_trkPOGFilters);
   fChain->SetBranchAddress("Flag_trkPOG_manystripclus53X", &Flag_trkPOG_manystripclus53X, &b_Flag_trkPOG_manystripclus53X);
   fChain->SetBranchAddress("Flag_trkPOG_toomanystripclus53X", &Flag_trkPOG_toomanystripclus53X, &b_Flag_trkPOG_toomanystripclus53X);
   fChain->SetBranchAddress("Flag_trkPOG_logErrorTooManyClusters", &Flag_trkPOG_logErrorTooManyClusters, &b_Flag_trkPOG_logErrorTooManyClusters);
   fChain->SetBranchAddress("Flag_BadPFMuonFilter", &Flag_BadPFMuonFilter, &b_Flag_BadPFMuonFilter);
   fChain->SetBranchAddress("Flag_BadChargedCandidateFilter", &Flag_BadChargedCandidateFilter, &b_Flag_BadChargedCandidateFilter);
   fChain->SetBranchAddress("Flag_ecalBadCalibFilter", &Flag_ecalBadCalibFilter, &b_Flag_ecalBadCalibFilter);
   fChain->SetBranchAddress("Flag_METFilters", &Flag_METFilters, &b_Flag_METFilters);
   fChain->SetBranchAddress("HLTDecision", HLTDecision, &b_HLTDecision);
   fChain->SetBranchAddress("HLTPrescale", HLTPrescale, &b_HLTPrescale);
   fChain->SetBranchAddress("HLTMR", &HLTMR, &b_HLTMR);
   fChain->SetBranchAddress("HLTRSQ", &HLTRSQ, &b_HLTRSQ);
   fChain->SetBranchAddress("ecalRechit_Eta", &ecalRechit_Eta, &b_ecalRechit_Eta);
   fChain->SetBranchAddress("ecalRechit_Phi", &ecalRechit_Phi, &b_ecalRechit_Phi);
   fChain->SetBranchAddress("ecalRechit_X", &ecalRechit_X, &b_ecalRechit_X);
   fChain->SetBranchAddress("ecalRechit_Y", &ecalRechit_Y, &b_ecalRechit_Y);
   fChain->SetBranchAddress("ecalRechit_Z", &ecalRechit_Z, &b_ecalRechit_Z);
   fChain->SetBranchAddress("ecalRechit_E", &ecalRechit_E, &b_ecalRechit_E);
   fChain->SetBranchAddress("ecalRechit_T", &ecalRechit_T, &b_ecalRechit_T);
   fChain->SetBranchAddress("ecalRechit_ID", &ecalRechit_ID, &b_ecalRechit_ID);
   fChain->SetBranchAddress("ecalRechit_FlagOOT", &ecalRechit_FlagOOT, &b_ecalRechit_FlagOOT);
   fChain->SetBranchAddress("ecalRechit_GainSwitch1", &ecalRechit_GainSwitch1, &b_ecalRechit_GainSwitch1);
   fChain->SetBranchAddress("ecalRechit_GainSwitch6", &ecalRechit_GainSwitch6, &b_ecalRechit_GainSwitch6);
   fChain->SetBranchAddress("ecalRechit_transpCorr", &ecalRechit_transpCorr, &b_ecalRechit_transpCorr);
   fChain->SetBranchAddress("nGenJets", &nGenJets, &b_nGenJets);
   fChain->SetBranchAddress("genJetE", genJetE, &b_genJetE);
   fChain->SetBranchAddress("genJetPt", genJetPt, &b_genJetPt);
   fChain->SetBranchAddress("genJetEta", genJetEta, &b_genJetEta);
   fChain->SetBranchAddress("genJetPhi", genJetPhi, &b_genJetPhi);
   fChain->SetBranchAddress("genMetPt", &genMetPt, &b_genMetPt);
   fChain->SetBranchAddress("genMetPhi", &genMetPhi, &b_genMetPhi);
   fChain->SetBranchAddress("genVertexX", &genVertexX, &b_genVertexX);
   fChain->SetBranchAddress("genVertexY", &genVertexY, &b_genVertexY);
   fChain->SetBranchAddress("genVertexZ", &genVertexZ, &b_genVertexZ);
   fChain->SetBranchAddress("genVertexT", &genVertexT, &b_genVertexT);
   fChain->SetBranchAddress("genWeight", &genWeight, &b_genWeight);
   fChain->SetBranchAddress("genSignalProcessID", &genSignalProcessID, &b_genSignalProcessID);
   fChain->SetBranchAddress("genQScale", &genQScale, &b_genQScale);
   fChain->SetBranchAddress("genAlphaQCD", &genAlphaQCD, &b_genAlphaQCD);
   fChain->SetBranchAddress("genAlphaQED", &genAlphaQED, &b_genAlphaQED);
   fChain->SetBranchAddress("scaleWeights", &scaleWeights, &b_scaleWeights);
   fChain->SetBranchAddress("pdfWeights", &pdfWeights, &b_pdfWeights);
   fChain->SetBranchAddress("alphasWeights", &alphasWeights, &b_alphasWeights);
   fChain->SetBranchAddress("nGenParticle", &nGenParticle, &b_nGenParticle);
   fChain->SetBranchAddress("gParticleMotherId", gParticleMotherId, &b_gParticleMotherId);
   fChain->SetBranchAddress("gParticleMotherIndex", gParticleMotherIndex, &b_gParticleMotherIndex);
   fChain->SetBranchAddress("gParticleId", gParticleId, &b_gParticleId);
   fChain->SetBranchAddress("gParticleStatus", gParticleStatus, &b_gParticleStatus);
   fChain->SetBranchAddress("gParticleE", gParticleE, &b_gParticleE);
   fChain->SetBranchAddress("gParticlePt", gParticlePt, &b_gParticlePt);
   fChain->SetBranchAddress("gParticlePx", gParticlePx, &b_gParticlePx);
   fChain->SetBranchAddress("gParticlePy", gParticlePy, &b_gParticlePy);
   fChain->SetBranchAddress("gParticlePz", gParticlePz, &b_gParticlePz);
   fChain->SetBranchAddress("gParticleEta", gParticleEta, &b_gParticleEta);
   fChain->SetBranchAddress("gParticlePhi", gParticlePhi, &b_gParticlePhi);
   fChain->SetBranchAddress("gParticleDecayVertexX", gParticleDecayVertexX, &b_gParticleDecayVertexX);
   fChain->SetBranchAddress("gParticleDecayVertexY", gParticleDecayVertexY, &b_gParticleDecayVertexY);
   fChain->SetBranchAddress("gParticleDecayVertexZ", gParticleDecayVertexZ, &b_gParticleDecayVertexZ);
   fChain->SetBranchAddress("gParticleProductionVertexX", gParticleProductionVertexX, &b_gParticleProductionVertexX);
   fChain->SetBranchAddress("gParticleProductionVertexY", gParticleProductionVertexY, &b_gParticleProductionVertexY);
   fChain->SetBranchAddress("gParticleProductionVertexZ", gParticleProductionVertexZ, &b_gParticleProductionVertexZ);
   Notify();
}

Bool_t razorNtuple::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void razorNtuple::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t razorNtuple::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef razorNtuple_cxx
