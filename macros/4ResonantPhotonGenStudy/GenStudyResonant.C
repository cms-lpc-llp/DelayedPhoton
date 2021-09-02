#define razorNtuple_cxx
#include "razorNtuple.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include "TLorentzVector.h"
#include "TVector3.h"

#include <iostream>

const float EB_R = 129.7;

TVector3 intersectPoint(float x0,float y0,float z0,float px,float py,float pz,float R)
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
        x1=0,y1=0,z1=999,x2=0,y2=0,z2=999; 
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
        sol.SetXYZ(0,0,999);
    } 
    return sol;
};


void razorNtuple::Loop()
{

   //*************************************************************************
   //Open Output File
   //*************************************************************************
   string outFileName = "DelayedPhoton_resonant_200000.root";

   TFile* outFile = new TFile( outFileName.c_str(), "RECREATE" );

   //---------------------------
   //one tree to hold all events
   //---------------------------
   TTree * outputTree = new TTree("DelayedPhoton", "Delayed photon events");


   //--------------------
   //initialize variables
   //--------------------

   int nGenPhotons;
   int nGenPhotonsOver10GeV;

   float Pt, Eta, Phi;

   float gPho1Pt, gPho1Eta, gPho1Phi;
   float gPho2Pt, gPho2Eta, gPho2Phi;
   float gPho3Pt, gPho3Eta, gPho3Phi;
   float gPho4Pt, gPho4Eta, gPho4Phi;

   float gPho12Pt, gPho12Eta, gPho12Phi;
   float gPho34Pt, gPho34Eta, gPho34Phi;

   float gPho1RecHitEta, gPho1RecHitPhi;
   float gPho2RecHitEta, gPho2RecHitPhi;
   float gPho3RecHitEta, gPho3RecHitPhi;
   float gPho4RecHitEta, gPho4RecHitPhi;

   float BadPhoton[10];
   
   float pho1E, pho1Pt, pho1Eta, pho1Phi, pho1SeedE, pho1SeedPt, pho1SeedEta, pho1SeedPhi, pho1SeedX, pho1SeedY, pho1SeedZ;
   float pho2E, pho2Pt, pho2Eta, pho2Phi, pho2SeedE, pho2SeedPt, pho2SeedEta, pho2SeedPhi, pho2SeedX, pho2SeedY, pho2SeedZ;
   float pho3E, pho3Pt, pho3Eta, pho3Phi, pho3SeedE, pho3SeedPt, pho3SeedEta, pho3SeedPhi, pho3SeedX, pho3SeedY, pho3SeedZ;
   float pho4E, pho4Pt, pho4Eta, pho4Phi, pho4SeedE, pho4SeedPt, pho4SeedEta, pho4SeedPhi, pho4SeedX, pho4SeedY, pho4SeedZ;
   
   float gDeltaR_pho12, gDeltaR_pho13, gDeltaR_pho14, gDeltaR_pho23, gDeltaR_pho24, gDeltaR_pho34;
   float gDeltaPhi_pho12, gDeltaPhi_pho13, gDeltaPhi_pho14, gDeltaPhi_pho23, gDeltaPhi_pho24, gDeltaPhi_pho34;
   float gDeltaEta_pho12, gDeltaEta_pho13, gDeltaEta_pho14, gDeltaEta_pho23, gDeltaEta_pho24, gDeltaEta_pho34;

   float nGenPhoEcal = 0;
   
   float gRecHitDeltaR_pho12, gRecHitDeltaR_pho13, gRecHitDeltaR_pho14, gRecHitDeltaR_pho23, gRecHitDeltaR_pho24, gRecHitDeltaR_pho34;
   float gRecHitDeltaPhi_pho12, gRecHitDeltaPhi_pho13, gRecHitDeltaPhi_pho14, gRecHitDeltaPhi_pho23, gRecHitDeltaPhi_pho24, gRecHitDeltaPhi_pho34;
   float gRecHitDeltaEta_pho12, gRecHitDeltaEta_pho13, gRecHitDeltaEta_pho14, gRecHitDeltaEta_pho23, gRecHitDeltaEta_pho24, gRecHitDeltaEta_pho34;
   

   float nMother, m_mother1, m_mother2, mother1Pt, mother2Pt, mother1Eta, mother2Eta, mother1Phi, mother2Phi;

   float m_diMother, m_diphoton1, m_diphoton2;
   float diMotherPt, diPhotonPt1, diPhotonPt2;

   float nZp, m_zPrime, zPrimePt, zPrimeEta, zPrimePhi;

   float gDeltaR_mother, gDeltaEta_mother, gDeltaPhi_mother;

   float decayRadius1, decayEta1, ctau1, decayRadius2, decayEta2, ctau2, Radius3D1, Radius3D2;
   float decay_x1, decay_y1, decay_z1, decay_x2, decay_y2, decay_z2;
   
   float nMatched = 0, nCorrectMatched = 0, GenPhoOver4NEvents = 0, SigPhoOver4NEvents = 0;

   float efficiency_deltaR[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

   TH1F * h1 = new TH1F("h1", "nMother", 10, -0.5, 9.5);
   TH1F * h2 = new TH1F("h2", "nZp", 10, -0.5, 9.5);

   outputTree->Branch("nGenPhotons", &nGenPhotons, "nGenPhotons/I");
   outputTree->Branch("nGenPhotonsOver10GeV", &nGenPhotonsOver10GeV, "nGenPhotonsOver10GeV/I");

   outputTree->Branch("gPho1Pt", &gPho1Pt, "gPho1Pt/F");
   outputTree->Branch("gPho1Eta", &gPho1Eta, "gPho1Eta/F");
   outputTree->Branch("gPho1Phi", &gPho1Phi, "gPho1Phi/F");
   outputTree->Branch("gPho1RecHitEta", &gPho1RecHitEta, "gPho1RecHitEta/F");
   outputTree->Branch("gPho1RecHitPhi", &gPho1RecHitPhi, "gPho1RecHitPhi/F");

   outputTree->Branch("gPho2Pt", &gPho2Pt, "gPho2Pt/F");
   outputTree->Branch("gPho2Eta", &gPho2Eta, "gPho2Eta/F");
   outputTree->Branch("gPho2Phi", &gPho2Phi, "gPho2Phi/F");
   outputTree->Branch("gPho2RecHitEta", &gPho2RecHitEta, "gPho2RecHitEta/F");
   outputTree->Branch("gPho2RecHitPhi", &gPho2RecHitPhi, "gPho2RecHitPhi/F");

   outputTree->Branch("gPho3Pt", &gPho3Pt, "gPho3Pt/F");
   outputTree->Branch("gPho3Eta", &gPho3Eta, "gPho3Eta/F");
   outputTree->Branch("gPho3Phi", &gPho3Phi, "gPho3Phi/F");
   outputTree->Branch("gPho3RecHitEta", &gPho3RecHitEta, "gPho3RecHitEta/F");
   outputTree->Branch("gPho3RecHitPhi", &gPho3RecHitPhi, "gPho3RecHitPhi/F");

   outputTree->Branch("gPho4Pt", &gPho4Pt, "gPho4Pt/F");
   outputTree->Branch("gPho4Eta", &gPho4Eta, "gPho4Eta/F");
   outputTree->Branch("gPho4Phi", &gPho4Phi, "gPho4Phi/F");
   outputTree->Branch("gPho4RecHitEta", &gPho4RecHitEta, "gPho4RecHitEta/F");
   outputTree->Branch("gPho4RecHitPhi", &gPho4RecHitPhi, "gPho4RecHitPhi/F");
   
   outputTree->Branch("gPho12Pt", &gPho12Pt, "gPho12Pt/F");
   outputTree->Branch("gPho12Eta", &gPho12Eta, "gPho12Eta/F");
   outputTree->Branch("gPho12Phi", &gPho12Phi, "gPho12Phi/F");
   
   outputTree->Branch("gPho34Pt", &gPho34Pt, "gPho34Pt/F");
   outputTree->Branch("gPho34Eta", &gPho34Eta, "gPho34Eta/F");
   outputTree->Branch("gPho34Phi", &gPho34Phi, "gPho34Phi/F");

   outputTree->Branch("BadPhoton", &BadPhoton, "BadPhoton/F");

   outputTree->Branch("pho1Pt", &pho1Pt, "Pho1Pt/F");
   outputTree->Branch("pho1Eta", &pho1Eta, "pho1Eta/F");
   outputTree->Branch("pho1Phi", &pho1Phi, "pho1Phi/F");
   outputTree->Branch("pho1SeedE", &pho1SeedE, "pho1SeedE/F");
   outputTree->Branch("pho1SeedPt", &pho1SeedPt, "pho1SeedPt/F");
   outputTree->Branch("pho1SeedEta", &pho1SeedEta, "pho1SeedEta/F");
   outputTree->Branch("pho1SeedPhi", &pho1SeedPhi, "pho1SeedPhi/F");
   outputTree->Branch("pho1SeedX", &pho1SeedX, "pho1SeedX/F");
   outputTree->Branch("pho1SeedY", &pho1SeedY, "pho1SeedY/F");
   outputTree->Branch("pho1SeedZ", &pho1SeedZ, "pho1SeedZ/F");

   outputTree->Branch("pho2E", &pho2E, "pho2E/F");
   outputTree->Branch("pho2Pt", &pho2Pt, "pho2Pt/F");
   outputTree->Branch("pho2Eta", &pho2Eta, "pho2Eta/F");
   outputTree->Branch("pho2Phi", &pho2Phi, "pho2Phi/F");
   outputTree->Branch("pho2SeedE", &pho2SeedE, "pho2SeedE/F");
   outputTree->Branch("pho2SeedPt", &pho2SeedPt, "pho2SeedPt/F");
   outputTree->Branch("pho2SeedEta", &pho2SeedEta, "pho2SeedEta/F");
   outputTree->Branch("pho2SeedPhi", &pho2SeedPhi, "pho2SeedPhi/F");
   outputTree->Branch("pho2SeedX", &pho2SeedX, "pho2SeedX/F");
   outputTree->Branch("pho2SeedY", &pho2SeedY, "pho2SeedY/F");
   outputTree->Branch("pho2SeedZ", &pho2SeedZ, "pho2SeedZ/F");

   outputTree->Branch("pho3Pt", &pho3Pt, "pho3Pt/F");
   outputTree->Branch("pho3Eta", &pho3Eta, "pho3Eta/F");
   outputTree->Branch("pho3Phi", &pho3Phi, "pho3Phi/F");
   outputTree->Branch("pho3SeedE", &pho3SeedE, "pho3SeedE/F");
   outputTree->Branch("pho3SeedPt", &pho3SeedPt, "pho3SeedPt/F");
   outputTree->Branch("pho3SeedEta", &pho3SeedEta, "pho3SeedEta/F");
   outputTree->Branch("pho3SeedPhi", &pho3SeedPhi, "pho3SeedPhi/F");
   outputTree->Branch("pho3SeedX", &pho3SeedX, "pho3SeedX/F");
   outputTree->Branch("pho3SeedY", &pho3SeedY, "pho3SeedY/F");
   outputTree->Branch("pho3SeedZ", &pho3SeedZ, "pho3SeedZ/F");

   outputTree->Branch("pho4Pt", &pho4Pt, "pho4Pt/F");
   outputTree->Branch("pho4Eta", &pho4Eta, "pho4Eta/F");
   outputTree->Branch("pho4Phi", &pho4Phi, "pho4Phi/F");
   outputTree->Branch("pho4SeedE", &pho4SeedE, "pho4SeedE/F");
   outputTree->Branch("pho4SeedPt", &pho4SeedPt, "pho4SeedPt/F");
   outputTree->Branch("pho4SeedEta", &pho4SeedEta, "pho4SeedEta/F");
   outputTree->Branch("pho4SeedPhi", &pho4SeedPhi, "pho4SeedPhi/F");
   outputTree->Branch("pho4SeedX", &pho4SeedX, "pho4SeedX/F");
   outputTree->Branch("pho4SeedY", &pho4SeedY, "pho4SeedY/F");
   outputTree->Branch("pho4SeedZ", &pho4SeedZ, "pho4SeedZ/F");

   
   outputTree->Branch("gDeltaR_pho12", &gDeltaR_pho12, "gDeltaR_pho12/F");
   outputTree->Branch("gDeltaR_pho13", &gDeltaR_pho13, "gDeltaR_pho13/F");
   outputTree->Branch("gDeltaR_pho14", &gDeltaR_pho14, "gDeltaR_pho14/F");
   outputTree->Branch("gDeltaR_pho23", &gDeltaR_pho23, "gDeltaR_pho23/F");
   outputTree->Branch("gDeltaR_pho24", &gDeltaR_pho24, "gDeltaR_pho24/F");
   outputTree->Branch("gDeltaR_pho34", &gDeltaR_pho34, "gDeltaR_pho34/F");

   outputTree->Branch("gDeltaPhi_pho12", &gDeltaPhi_pho12, "gDeltaPhi_pho12/F");
   outputTree->Branch("gDeltaPhi_pho13", &gDeltaPhi_pho13, "gDeltaPhi_pho13/F");
   outputTree->Branch("gDeltaPhi_pho14", &gDeltaPhi_pho14, "gDeltaPhi_pho14/F");
   outputTree->Branch("gDeltaPhi_pho23", &gDeltaPhi_pho23, "gDeltaPhi_pho23/F");
   outputTree->Branch("gDeltaPhi_pho24", &gDeltaPhi_pho24, "gDeltaPhi_pho24/F");
   outputTree->Branch("gDeltaPhi_pho34", &gDeltaPhi_pho34, "gDeltaPhi_pho34/F");

   outputTree->Branch("gDeltaEta_pho12", &gDeltaEta_pho12, "gDeltaEta_pho12/F");
   outputTree->Branch("gDeltaEta_pho13", &gDeltaEta_pho13, "gDeltaEta_pho13/F");
   outputTree->Branch("gDeltaEta_pho14", &gDeltaEta_pho14, "gDeltaEta_pho14/F");
   outputTree->Branch("gDeltaEta_pho23", &gDeltaEta_pho23, "gDeltaEta_pho23/F");
   outputTree->Branch("gDeltaEta_pho24", &gDeltaEta_pho24, "gDeltaEta_pho24/F");
   outputTree->Branch("gDeltaEta_pho34", &gDeltaEta_pho34, "gDeltaEta_pho34/F");
   
   outputTree->Branch("nGenPhoEcal", &nGenPhoEcal, "nGenPhoEcal/I");

   outputTree->Branch("gRecHitDeltaR_pho12", &gRecHitDeltaR_pho12, "gRecHitDeltaR_pho12/F");
   outputTree->Branch("gRecHitDeltaR_pho13", &gRecHitDeltaR_pho13, "gRecHitDeltaR_pho13/F");
   outputTree->Branch("gRecHitDeltaR_pho14", &gRecHitDeltaR_pho14, "gRecHitDeltaR_pho14/F");
   outputTree->Branch("gRecHitDeltaR_pho23", &gRecHitDeltaR_pho23, "gRecHitDeltaR_pho23/F");
   outputTree->Branch("gRecHitDeltaR_pho24", &gRecHitDeltaR_pho24, "gRecHitDeltaR_pho24/F");
   outputTree->Branch("gRecHitDeltaR_pho34", &gRecHitDeltaR_pho34, "gRecHitDeltaR_pho34/F");

   outputTree->Branch("gRecHitDeltaPhi_pho12", &gRecHitDeltaPhi_pho12, "gRecHitDeltaPhi_pho12/F");
   outputTree->Branch("gRecHitDeltaPhi_pho13", &gRecHitDeltaPhi_pho13, "gRecHitDeltaPhi_pho13/F");
   outputTree->Branch("gRecHitDeltaPhi_pho14", &gRecHitDeltaPhi_pho14, "gRecHitDeltaPhi_pho14/F");
   outputTree->Branch("gRecHitDeltaPhi_pho23", &gRecHitDeltaPhi_pho23, "gRecHitDeltaPhi_pho23/F");
   outputTree->Branch("gRecHitDeltaPhi_pho24", &gRecHitDeltaPhi_pho24, "gRecHitDeltaPhi_pho24/F");
   outputTree->Branch("gRecHitDeltaPhi_pho34", &gRecHitDeltaPhi_pho34, "gRecHitDeltaPhi_pho34/F");

   outputTree->Branch("gRecHitDeltaEta_pho12", &gRecHitDeltaEta_pho12, "gRecHitDeltaEta_pho12/F");
   outputTree->Branch("gRecHitDeltaEta_pho13", &gRecHitDeltaEta_pho13, "gRecHitDeltaEta_pho13/F");
   outputTree->Branch("gRecHitDeltaEta_pho14", &gRecHitDeltaEta_pho14, "gRecHitDeltaEta_pho14/F");
   outputTree->Branch("gRecHitDeltaEta_pho23", &gRecHitDeltaEta_pho23, "gRecHitDeltaEta_pho23/F");
   outputTree->Branch("gRecHitDeltaEta_pho24", &gRecHitDeltaEta_pho24, "gRecHitDeltaEta_pho24/F");
   outputTree->Branch("gRecHitDeltaEta_pho34", &gRecHitDeltaEta_pho34, "gRecHitDeltaEta_pho34/F");

   outputTree->Branch("nMother", &nMother, "nMother/I");
   outputTree->Branch("m_mother1", &m_mother1, "m_mother1/F");
   outputTree->Branch("m_mother2", &m_mother2, "m_mother2/F");
   outputTree->Branch("mother1Pt", &mother1Pt, "mother1Pt/F");
   outputTree->Branch("mother2Pt", &mother2Pt, "mother2Pt/F");
   outputTree->Branch("mother1Eta", &mother1Eta, "mother1Eta/F");
   outputTree->Branch("mother2Eta", &mother2Eta, "mother2Eta/F");
   outputTree->Branch("mother1Phi", &mother1Phi, "mother1Phi/F");
   outputTree->Branch("mother2Phi", &mother2Phi, "mother2Phi/F");

   outputTree->Branch("m_diphoton1", &m_diphoton1, "m_diphoton1/F");
   outputTree->Branch("m_diphoton2", &m_diphoton2, "m_diphoton2/F");

   outputTree->Branch("m_diMother", &m_diMother, "m_diMother/F");

   outputTree->Branch("diMotherPt", &diMotherPt, "diMotherPt/F");

   outputTree->Branch("diPhotonPt1", &diPhotonPt1, "diPhotonPt1/F");
   outputTree->Branch("diPhotonPt2", &diPhotonPt2, "diPhotonPt2/F");

   outputTree->Branch("nZp", &nZp, "nZp/F");
   outputTree->Branch("m_zPrime", &m_zPrime, "m_zPrime/F");
   outputTree->Branch("zPrimePt", &zPrimePt, "zPrimePt/F");
   outputTree->Branch("zPrimeEta", &zPrimeEta, "zPrimeEta/F");
   outputTree->Branch("zPrimePhi", &zPrimePhi, "zPrimePhi/F");

   outputTree->Branch("gDeltaR_mother", &gDeltaR_mother, "gDeltaR_mother/F");
   outputTree->Branch("gDeltaEta_mother", &gDeltaEta_mother, "gDeltaEta_mother/F");
   outputTree->Branch("gDeltaPhi_mother", &gDeltaPhi_mother, "gDeltaPhi_mother/F");

   outputTree->Branch("decayRadius1", &decayRadius1, "decayRadius1/F");
   outputTree->Branch("decayRadius2", &decayRadius2, "decayRadius2/F");
   outputTree->Branch("decayEta1", &decayEta1, "decayEta1/F");
   outputTree->Branch("decayEta2", &decayEta2, "decayEta2/F");
   outputTree->Branch("ctau1", &ctau1, "ctau1/F");
   outputTree->Branch("ctau2", &ctau2, "ctau2/F");
   outputTree->Branch("Radius3D1", &Radius3D1, "Radius3D1/F");
   outputTree->Branch("Radius3D2", &Radius3D2, "Radius3D2/F");

   outputTree->Branch("decay_x1", &decay_x1, "decay_x1/F");
   outputTree->Branch("decay_y1", &decay_y1, "decay_y1/F");
   outputTree->Branch("decay_z1", &decay_z1, "decay_z1/F");
   outputTree->Branch("decay_x2", &decay_x2, "decay_x2/F");
   outputTree->Branch("decay_y2", &decay_y2, "decay_y2/F");
   outputTree->Branch("decay_z2", &decay_z2, "decay_z2/F");


   //for TGraphErrors
   float motherPtN1[127841], motherPtN2[127841], gDeltaPhi_N1[127841], gDeltaPhi_N2[127841], motherDeltaPhi[127841], zPPt[127841];
   int csv_ind = 0;
   ofstream file1;
   ofstream file2;

   file1.open("particlestatus_scalarOffShell.csv");
   file1 << "jentry, ind_gen, gParticleId, gParticleStatus, gParticleE, gParticlePt, gParticleEta, gParticlePhi, gParticle.M() , gParticleMotherIndex" <<endl;
   file2.open("particlestatus_zPOffShell.csv");
   file2 << "jentry, ind_gen, gParticleId, gParticleStatus, gParticleE, gParticlePt, gParticleEta, gParticlePhi, gParticle.M() , gParticleMotherIndex" <<endl;


   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<100000;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if(jentry % 10000 == 0){
          std::cout << "\nProcessing\t"<< jentry << "/" << nentries << " entry\r" << std::flush;
          std::cout << endl;
          std::cout << endl;
      }
      if (ientry < 0){
          cout << "Exiting Job\n";
          break;
      }

      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      
      //initialize branches
      nGenPhotons = 0;
      nGenPhotonsOver10GeV = 0;

      gPho1Pt = -999, gPho1Eta = -999, gPho1Phi = -999;
      gPho2Pt = -999, gPho2Eta = -999, gPho2Phi = -999;
      gPho3Pt = -999, gPho3Eta = -999, gPho3Phi = -999;
      gPho4Pt = -999, gPho4Eta = -999, gPho4Phi = -999;

      gPho12Pt = -999, gPho12Eta = -999, gPho12Phi = -999;
      gPho34Pt = -999, gPho34Eta = -999, gPho34Phi = -999;

      gPho1RecHitEta = -999, gPho1RecHitPhi = -999;
      gPho2RecHitEta = -999, gPho2RecHitPhi = -999;
      gPho3RecHitEta = -999, gPho3RecHitPhi = -999;
      gPho4RecHitEta = -999, gPho4RecHitPhi = -999;

      pho1E = -999, pho1Pt = -999, pho1Eta = -999, pho1Phi = -999, pho1SeedE = -999, pho1SeedPt = -999, pho1SeedEta = -999, pho1SeedPhi = -999, pho1SeedX = -999, pho1SeedY = -999, pho1SeedZ = -999;
      pho2E = -999, pho2Pt = -999, pho2Eta = -999, pho2Phi = -999, pho2SeedE = -999, pho2SeedPt = -999, pho2SeedEta = -999, pho2SeedPhi = -999, pho2SeedX = -999, pho2SeedY = -999, pho2SeedZ = -999;
      pho3E = -999, pho3Pt = -999, pho3Eta = -999, pho3Phi = -999, pho3SeedE = -999, pho3SeedPt = -999, pho3SeedEta = -999, pho3SeedPhi = -999, pho3SeedX = -999, pho3SeedY = -999, pho3SeedZ = -999;
      pho4E = -999, pho4Pt = -999, pho4Eta = -999, pho4Phi = -999, pho4SeedE = -999, pho4SeedPt = -999, pho4SeedEta = -999, pho4SeedPhi = -999, pho4SeedX = -999, pho4SeedY = -999, pho4SeedZ = -999;

      gDeltaR_pho12 = -999;
      gDeltaR_pho13 = -999;
      gDeltaR_pho14 = -999;
      gDeltaR_pho23 = -999;
      gDeltaR_pho24 = -999;
      gDeltaR_pho34 = -999;

      gDeltaPhi_pho12 = -999;
      gDeltaPhi_pho13 = -999;
      gDeltaPhi_pho14 = -999;
      gDeltaPhi_pho23 = -999;
      gDeltaPhi_pho24 = -999;
      gDeltaPhi_pho34 = -999;

      gDeltaEta_pho12 = -999;
      gDeltaEta_pho13 = -999;
      gDeltaEta_pho14 = -999;
      gDeltaEta_pho23 = -999;
      gDeltaEta_pho24 = -999;
      gDeltaEta_pho34 = -999;
     

      gRecHitDeltaR_pho12 = -999;
      gRecHitDeltaR_pho13 = -999;
      gRecHitDeltaR_pho14 = -999;
      gRecHitDeltaR_pho23 = -999;
      gRecHitDeltaR_pho24 = -999;
      gRecHitDeltaR_pho34 = -999;

      gRecHitDeltaPhi_pho12 = -999;
      gRecHitDeltaPhi_pho13 = -999;
      gRecHitDeltaPhi_pho14 = -999;
      gRecHitDeltaPhi_pho23 = -999;
      gRecHitDeltaPhi_pho24 = -999;
      gRecHitDeltaPhi_pho34 = -999;

      gRecHitDeltaEta_pho12 = -999;
      gRecHitDeltaEta_pho13 = -999;
      gRecHitDeltaEta_pho14 = -999;
      gRecHitDeltaEta_pho23 = -999;
      gRecHitDeltaEta_pho24 = -999;
      gRecHitDeltaEta_pho34 = -999;

      nMother = 0;
      m_mother1 = -999;
      m_mother2 = -999;
      mother1Pt = -999;
      mother2Pt = -999;
      mother1Eta = -999;
      mother2Eta = -999;
      mother1Phi = -999;
      mother2Phi = -999;

      m_diphoton1 = -999;
      m_diphoton2 = -999;

      m_diMother = -999;

      diMotherPt = -999;
      diPhotonPt1 = -999;
      diPhotonPt2 = -999;

      nZp = 0;
      m_zPrime = -999;
      zPrimePt = -999;
      zPrimeEta = -999;
      zPrimePhi = -999;

      gDeltaR_mother = -999;
      gDeltaEta_mother = -999;
      gDeltaPhi_mother = -999;

      decayRadius1 = -999;
      decayRadius2 = -999;
      decayEta1 = -999;
      decayEta2 = -999;
      ctau1 = -999;
      ctau2 = -999;
      Radius3D1 = -999;
      Radius3D2 = -999;


      for (int ind_gen = 0; ind_gen < nGenParticle; ind_gen++){
          if (abs(gParticleId[ind_gen]) == 58) {
              nMother++;
          }
          if (abs(gParticleId[ind_gen]) == 61) {
              nZp++;
          }
          h1->Fill(nMother);
          h2->Fill(nZp);
      }

      for (int ind_gen = 0; ind_gen < nGenParticle; ind_gen++){

          TLorentzVector gParticle(0., 0., 0., 0.);
          gParticle.SetPtEtaPhiE(gParticlePt[ind_gen], gParticleEta[ind_gen], gParticlePhi[ind_gen], gParticleE[ind_gen]);

          if (nMother == 0) file1 << jentry << ", " << ind_gen << ", " << gParticleId[ind_gen] << ", " << gParticleStatus[ind_gen] << ", " << gParticleE[ind_gen] << ", " << gParticlePt[ind_gen] << ", " << gParticleEta[ind_gen] << ", " << gParticlePhi[ind_gen] << ", " << gParticle.M() <<  ", " << gParticleMotherIndex[ind_gen] << ", " << nGenParticle <<endl;
          if (nZp == 0) file2 << jentry << ", " << ind_gen << ", " << gParticleId[ind_gen] << ", " << gParticleStatus[ind_gen] << ", " << gParticleE[ind_gen] << ", " << gParticlePt[ind_gen] << ", " << gParticleEta[ind_gen] << ", " << gParticlePhi[ind_gen] << ", " << gParticle.M() <<  ", " << gParticleMotherIndex[ind_gen] << ", " << nGenParticle <<endl;
          
      }
      
      TLorentzVector pho1(0.,0.,0.,0.);
      TLorentzVector pho2(0.,0.,0.,0.);
      TLorentzVector pho3(0.,0.,0.,0.);
      TLorentzVector pho4(0.,0.,0.,0.);

      //photon loop
      for(int ind_pho = 0; ind_pho < nPhotons; ind_pho++){ 
          //apply some cuts
          
          //if(ecalRechit_ID->empty()) continue;
          //if(phoPt[ind_pho] < 40) continue; //basic Pt cut

          if(fabs(phoEta[ind_pho]) > 2.5) continue; // tracker region
          if(fabs(phoEta[ind_pho]) > 1.4442 && fabs(phoEta[ind_pho]) < 1.566) continue; //the eta range for photon, this takes care of the gap between barrel and endcap
          

          //photon cluster
          TVector3 pho_vec;
          pho_vec.SetPtEtaPhi(phoPt[ind_pho], phoEta[ind_pho], phoPhi[ind_pho]);
          TLorentzVector thisPhoton;
          thisPhoton.SetVectM(pho_vec, .0);

          uint seedhitIndex = (*pho_SeedRechitIndex)[ind_pho];
          //std::cout << "ind_pho : " << ind_pho <<endl;
          //std::cout << "seedhitIndex : " << seedhitIndex << endl;


          if(thisPhoton.Pt() > pho1.Pt()){
              //
              pho4 = pho3;

              pho4E = pho4.E();
              pho4Pt = pho4.Pt();
              pho4Eta = pho4.Eta();
              pho4Phi = pho4.Phi();
              pho4SeedE = pho3SeedE;
              pho4SeedEta = pho3SeedEta;
              pho4SeedPhi = pho3SeedPhi;
              pho4SeedPt = pho3SeedPt;

              pho4SeedX = pho3SeedX;
              pho4SeedY = pho3SeedY;
              pho4SeedZ = pho3SeedZ;

              //
              pho3 = pho2;

              pho3E = pho3.E();
              pho3Pt = pho3.Pt();
              pho3Eta = pho3.Eta();
              pho3Phi = pho3.Phi();
              pho3SeedE = pho2SeedE;
              pho3SeedEta = pho2SeedEta;
              pho3SeedPhi = pho2SeedPhi;
              pho3SeedPt = pho2SeedPt;

              pho3SeedX = pho2SeedX;
              pho3SeedY = pho2SeedY;
              pho3SeedZ = pho2SeedZ;


              //
              pho2 = pho1;

              pho2E = pho2.E();
              pho2Pt = pho2.Pt();
              pho2Eta = pho2.Eta();
              pho2Phi = pho2.Phi();
              pho2SeedE = pho1SeedE;
              pho2SeedEta = pho1SeedEta;
              pho2SeedPhi = pho1SeedPhi;
              pho2SeedPt = pho1SeedPt;

              pho2SeedX = pho1SeedX;
              pho2SeedY = pho1SeedY;
              pho2SeedZ = pho1SeedZ;


              //
              pho1 = thisPhoton;

              pho1E = thisPhoton.E();
              pho1Pt = thisPhoton.Pt();
              pho1Eta = thisPhoton.Eta();
              pho1Phi = thisPhoton.Phi();
              pho1SeedE = (*ecalRechit_E)[seedhitIndex];
              pho1SeedEta = (*ecalRechit_Eta)[seedhitIndex];
              pho1SeedPhi = (*ecalRechit_Phi)[seedhitIndex];
              pho1SeedPt = pho1SeedE/cosh(pho1SeedEta);

              pho1SeedX = (*ecalRechit_X)[seedhitIndex];
              pho1SeedY = (*ecalRechit_Y)[seedhitIndex];
              pho1SeedZ = (*ecalRechit_Z)[seedhitIndex];
          }
          
          else if(thisPhoton.Pt() > pho2.Pt()){
              //
              pho4 = pho3;

              pho4E = pho4.E();
              pho4Pt = pho4.Pt();
              pho4Eta = pho4.Eta();
              pho4Phi = pho4.Phi();
              pho4SeedE = pho3SeedE;
              pho4SeedEta = pho3SeedEta;
              pho4SeedPhi = pho3SeedPhi;
              pho4SeedPt = pho3SeedPt;

              pho4SeedX = pho3SeedX;
              pho4SeedY = pho3SeedY;
              pho4SeedZ = pho3SeedZ;


              //
              pho3 = pho2;

              pho3E = pho3.E();
              pho3Pt = pho3.Pt();
              pho3Eta = pho3.Eta();
              pho3Phi = pho3.Phi();
              pho3SeedE = pho2SeedE;
              pho3SeedEta = pho2SeedEta;
              pho3SeedPhi = pho2SeedPhi;
              pho3SeedPt = pho2SeedPt;

              pho3SeedX = pho2SeedX;
              pho3SeedY = pho2SeedY;
              pho3SeedZ = pho2SeedZ;


              //
              pho2 = thisPhoton;

              pho2E = thisPhoton.E();
              pho2Pt = thisPhoton.Pt();
              pho2Eta = thisPhoton.Eta();
              pho2Phi = thisPhoton.Phi();
              pho2SeedE = (*ecalRechit_E)[seedhitIndex];
              pho2SeedEta = (*ecalRechit_Eta)[seedhitIndex];
              pho2SeedPhi = (*ecalRechit_Phi)[seedhitIndex];
              pho2SeedPt = pho2SeedE/cosh(pho2SeedEta);

              pho2SeedX = (*ecalRechit_X)[seedhitIndex];
              pho2SeedY = (*ecalRechit_Y)[seedhitIndex];
              pho2SeedZ = (*ecalRechit_Z)[seedhitIndex];
          }

          else if(thisPhoton.Pt() > pho3.Pt()){
              //
              pho4 = pho3;

              pho4E = pho4.E();
              pho4Pt = pho4.Pt();
              pho4Eta = pho4.Eta();
              pho4Phi = pho4.Phi();
              pho4SeedE = pho3SeedE;
              pho4SeedEta = pho3SeedEta;
              pho4SeedPhi = pho3SeedPhi;
              pho4SeedPt = pho3SeedPt;

              pho4SeedX = pho3SeedX;
              pho4SeedY = pho3SeedY;
              pho4SeedZ = pho3SeedZ;


              //
              pho3 = thisPhoton;

              pho3E = thisPhoton.E();
              pho3Pt = thisPhoton.Pt();
              pho3Eta = thisPhoton.Eta();
              pho3Phi = thisPhoton.Phi();
              pho3SeedE = (*ecalRechit_E)[seedhitIndex];
              pho3SeedEta = (*ecalRechit_Eta)[seedhitIndex];
              pho3SeedPhi = (*ecalRechit_Phi)[seedhitIndex];
              pho3SeedPt = pho3SeedE/cosh(pho3SeedEta);

              pho3SeedX = (*ecalRechit_X)[seedhitIndex];
              pho3SeedY = (*ecalRechit_Y)[seedhitIndex];
              pho3SeedZ = (*ecalRechit_Z)[seedhitIndex];
          }

          else if(thisPhoton.Pt() > pho4.Pt()){
              //
              pho4 = thisPhoton;

              pho4E = thisPhoton.E();
              pho4Pt = thisPhoton.Pt();
              pho4Eta = thisPhoton.Eta();
              pho4Phi = thisPhoton.Phi();
              pho4SeedE = (*ecalRechit_E)[seedhitIndex];
              pho4SeedEta = (*ecalRechit_Eta)[seedhitIndex];
              pho4SeedPhi = (*ecalRechit_Phi)[seedhitIndex];
              pho4SeedPt = pho4SeedE/cosh(pho4SeedEta);

              pho4SeedX = (*ecalRechit_X)[seedhitIndex];
              pho4SeedY = (*ecalRechit_Y)[seedhitIndex];
              pho4SeedZ = (*ecalRechit_Z)[seedhitIndex];

          } //4 reco photons data has been entered (sorted by pT)
          
      } //photon loop ended

      TVector3 mother_vec1, mother_vec2;
      TLorentzVector mother1(0.,0.,0.,0.);
      TLorentzVector mother2(0.,0.,0.,0.);

      bool isMatched = false;

      for(int ind_gen = 0; ind_gen < nGenParticle; ind_gen++) if (gParticleId[ind_gen] == 22) nGenPhotons++;

      if (!isData && nGenPhotons>=4){
					GenPhoOver4NEvents++;
          bool foundN1 = false;
          bool foundN2 = false;
          bool foundP1 = false;
          bool foundP2 = false;
          bool foundP3 = false;
          bool foundP4 = false;
          int pho1index = 0;
          int pho2index = 0;
          int pho3index = 0;
          int pho4index = 0;
          int neu1_index = 0;
          int neu2_index = 0;
          int zP_index = 1;
          int temp;

          
          //finding the neutralino and photon index
          for (int ind_gen = 0; ind_gen < nGenParticle; ind_gen++){
              if (gParticleId[ind_gen] == 58 && gParticleStatus[ind_gen] == 22){
                  neu1_index = ind_gen;
              }
              if (gParticleId[ind_gen] == -58 && gParticleStatus[ind_gen] == 22){
                  neu2_index = ind_gen;
              }

              if (abs(gParticleId[ind_gen]) == 61) zP_index = ind_gen;
          } //neutralino index (neu*_index), z prime index (zP_index)
          if (gParticlePt[neu1_index] < gParticlePt[neu2_index]){
              temp = neu2_index;
              neu2_index = neu1_index;
              neu1_index = temp;
          }

          // pick 1~4 photons and sort by pT
          for (int ind_gen = 0; ind_gen < nGenParticle; ind_gen++){ 
              if (!foundP1 && gParticleId[ind_gen] == 22 && gParticleMotherIndex[ind_gen] == neu1_index){
                  pho1index = ind_gen;
                  foundP1 = true;
              }
              else if (foundP1 && !foundP2 && gParticleId[ind_gen] == 22 && gParticleMotherIndex[ind_gen] == neu1_index){
                  pho2index = ind_gen;
                  foundP2 = true;
              }
          }

          if (gParticlePt[pho1index] < gParticlePt[pho2index]){
              temp = pho2index;
              pho2index = pho1index;
              pho1index = temp;
          }

          for (int ind_gen = 0; ind_gen < nGenParticle; ind_gen++){
              if (!foundP3 && gParticleId[ind_gen] == 22 && gParticleMotherIndex[ind_gen] == neu2_index){
                  pho3index = ind_gen;
                  foundP3 = true;
              }
              else if (foundP3 && !foundP4 && gParticleId[ind_gen] == 22 && gParticleMotherIndex[ind_gen] == neu2_index){
                  pho4index = ind_gen;
                  foundP4 = true;
              }

          } 

          if (gParticlePt[pho3index] < gParticlePt[pho4index]){
              temp = pho4index;
              pho4index = pho3index;
              pho3index = temp;
          }
          

               //1-2 and 3-4 have the same mother for each
           //finding the neutralino and photon index

          if (pho1index != 0 && pho2index != 0 && pho3index != 0 && pho4index != 0){
							SigPhoOver4NEvents++;
              //pho* : reco Photon, phoSeed* : ecal Rechit, gpho* : gen Photon
              //delta R btw gen photons?
              
              //Gen Z Prime info
              TLorentzVector zPrime;
              zPrime.SetPtEtaPhiE(gParticlePt[zP_index], gParticleEta[zP_index], gParticlePhi[zP_index], gParticleE[zP_index]);
              m_zPrime = zPrime.M();
              zPrimePt = zPrime.Pt();
              zPrimeEta = zPrime.Eta();
              zPrimePhi = zPrime.Phi();

              //Gen Photon momentum info (gPho*Pt, Eta, Phi gDeltaEta, Phi_pho**)
              TLorentzVector gPho1, gPho2, gPho3, gPho4;

              gPho1.SetPtEtaPhiE(gParticlePt[pho1index], gParticleEta[pho1index], gParticlePhi[pho1index], gParticleE[pho1index]);
              gPho2.SetPtEtaPhiE(gParticlePt[pho2index], gParticleEta[pho2index], gParticlePhi[pho2index], gParticleE[pho2index]);
              gPho3.SetPtEtaPhiE(gParticlePt[pho3index], gParticleEta[pho3index], gParticlePhi[pho3index], gParticleE[pho3index]);
              gPho4.SetPtEtaPhiE(gParticlePt[pho4index], gParticleEta[pho4index], gParticlePhi[pho4index], gParticleE[pho4index]);

              gPho1Pt = gPho1.Pt();
              gPho2Pt = gPho2.Pt();
              gPho3Pt = gPho3.Pt();
              gPho4Pt = gPho4.Pt();

              gPho1Eta = gPho1.Eta();
              gPho2Eta = gPho2.Eta();
              gPho3Eta = gPho3.Eta();
              gPho4Eta = gPho4.Eta();

              gPho1Phi = gPho1.Phi();
              gPho2Phi = gPho2.Phi();
              gPho3Phi = gPho3.Phi();
              gPho4Phi = gPho4.Phi();

              gPho12Pt = (gPho1 + gPho2).Pt();
              gPho34Pt = (gPho3 + gPho4).Pt();

              gPho12Eta = (gPho1 + gPho2).Eta();
              gPho34Eta = (gPho3 + gPho4).Eta();

              gPho12Phi = (gPho1 + gPho2).Phi();
              gPho34Phi = (gPho3 + gPho4).Phi();

              gDeltaR_pho12 = gPho1.DeltaR(gPho2);
              gDeltaR_pho13 = gPho1.DeltaR(gPho3);
              gDeltaR_pho14 = gPho1.DeltaR(gPho4);
              gDeltaR_pho23 = gPho2.DeltaR(gPho3);
              gDeltaR_pho24 = gPho2.DeltaR(gPho4);
              gDeltaR_pho34 = gPho3.DeltaR(gPho4);

              gDeltaEta_pho12 = gPho1.Eta() - gPho2.Eta();
              gDeltaEta_pho13 = gPho1.Eta() - gPho3.Eta();
              gDeltaEta_pho14 = gPho1.Eta() - gPho4.Eta();
              gDeltaEta_pho23 = gPho2.Eta() - gPho3.Eta();
              gDeltaEta_pho24 = gPho2.Eta() - gPho4.Eta();
              gDeltaEta_pho34 = gPho3.Eta() - gPho4.Eta();

              gDeltaPhi_pho12 = gPho1.DeltaPhi(gPho2);
              gDeltaPhi_pho13 = gPho1.DeltaPhi(gPho3);
              gDeltaPhi_pho14 = gPho1.DeltaPhi(gPho4);
              gDeltaPhi_pho23 = gPho2.DeltaPhi(gPho3);
              gDeltaPhi_pho24 = gPho2.DeltaPhi(gPho4);
              gDeltaPhi_pho34 = gPho3.DeltaPhi(gPho4);
              
              m_diphoton1 = (gPho1+gPho2).M();
              m_diphoton2 = (gPho3+gPho4).M();

              diPhotonPt1 = (gPho1+gPho2).Pt();
              diPhotonPt2 = (gPho3+gPho4).Pt();


              //Gen Photon recHit info (gPho*RecHitEta, Phi, and also Delta..)
              TVector3 genSeed1;
              TVector3 genSeed2;
              TVector3 genSeed3;
              TVector3 genSeed4;

              float decay_x1 = gParticleDecayVertexX[neu1_index];
              float decay_y1 = gParticleDecayVertexY[neu1_index];
              float decay_z1 = gParticleDecayVertexZ[neu1_index];

              float norm1 = pow((pow(gParticlePx[pho1index],2)+pow(gParticlePy[pho1index],2)+pow(gParticlePz[pho1index],2)),0.5);
              float px1 = (gParticlePx[pho1index]) / norm1;
              float py1 = (gParticlePy[pho1index]) / norm1;
              float pz1 = (gParticlePz[pho1index]) / norm1;
              genSeed1 = intersectPoint(decay_x1, decay_y1, decay_z1, px1, py1, pz1, EB_R);
              float norm2 = pow((pow(gParticlePx[pho2index],2)+pow(gParticlePy[pho2index],2)+pow(gParticlePz[pho2index],2)),0.5);
              float px2 = (gParticlePx[pho2index]) / norm2;
              float py2 = (gParticlePy[pho2index]) / norm2;
              float pz2 = (gParticlePz[pho2index]) / norm2;
              genSeed2 = intersectPoint(decay_x1, decay_y1, decay_z1, px2, py2, pz2, EB_R);

              float decay_x2 = gParticleDecayVertexX[neu2_index];
              float decay_y2 = gParticleDecayVertexY[neu2_index];
              float decay_z2 = gParticleDecayVertexZ[neu2_index];

              float norm3 = pow((pow(gParticlePx[pho3index],2)+pow(gParticlePy[pho3index],2)+pow(gParticlePz[pho3index],2)),0.5);
              float px3 = (gParticlePx[pho3index]) / norm3;
              float py3 = (gParticlePy[pho3index]) / norm3;
              float pz3 = (gParticlePz[pho3index]) / norm3;
              genSeed3 = intersectPoint(decay_x2, decay_y2, decay_z2, px3, py3, pz3, EB_R);
              float norm4 = pow((pow(gParticlePx[pho4index],2)+pow(gParticlePy[pho4index],2)+pow(gParticlePz[pho4index],2)),0.5);
              float px4 = (gParticlePx[pho4index]) / norm4;
              float py4 = (gParticlePy[pho4index]) / norm4;
              float pz4 = (gParticlePz[pho4index]) / norm4;
              genSeed4 = intersectPoint(decay_x2, decay_y2, decay_z2, px4, py4, pz4, EB_R);

              TVector3 decayVector1;
              TVector3 decayVector2;

              decayVector1.SetXYZ(decay_x1, decay_y1, decay_z1);
              Radius3D1 = sqrt(decay_x1 * decay_x1 + decay_y1 * decay_y1 + decay_z1 * decay_z1);
              decayRadius1 = sqrt(decay_x1 * decay_x1 + decay_y1 * decay_y1);
              //decayRadius1 = decayVector1.Pt();
              decayEta1 = decayVector1.Eta();

              decayVector2.SetXYZ(decay_x2, decay_y2, decay_z2);
              decayRadius2 = sqrt(decay_x2 * decay_x2 + decay_y2 * decay_y2);
              Radius3D2 = sqrt(decay_x2 * decay_x2 + decay_y2 * decay_y2 + decay_z2 * decay_z2);
              //decayRadius2 = decayVector2.Pt();
              decayEta2 = decayVector2.Eta();

              mother1.SetPtEtaPhiE(gParticlePt[neu1_index], gParticleEta[neu1_index], gParticlePhi[neu1_index], gParticleE[neu1_index]);
              mother2.SetPtEtaPhiE(gParticlePt[neu2_index], gParticleEta[neu2_index], gParticlePhi[neu2_index], gParticleE[neu2_index]);


              m_mother1 = mother1.M();
              m_mother2 = mother2.M();
              mother1Pt = mother1.Pt();
              mother2Pt = mother2.Pt();
              mother1Eta = mother1.Eta();
              mother2Eta = mother2.Eta();
              mother1Phi = mother1.Phi();
              mother2Phi = mother2.Phi();
              
              m_diMother = (mother1+mother2).M();

              diMotherPt = (mother1+mother2).Pt();

              float beta1 = mother1.Beta();
              float beta2 = mother2.Beta();

              float gamma1 = 1.0/sqrt(1-beta1*beta1);
              float gamma2 = 1.0/sqrt(1-beta2*beta2);

              float decayVecMag1 = decayVector1.Mag();
              float decayVecMag2 = decayVector2.Mag();

              ctau1 = decayVecMag1 / (beta1 * gamma1);
              ctau2 = decayVecMag2 / (beta2 * gamma2);

              gDeltaR_mother = mother1.DeltaR(mother2);
              gDeltaEta_mother = mother1Eta - mother2Eta;
              gDeltaPhi_mother = mother1.DeltaPhi(mother2);


              if ( abs(genSeed1.Eta()) < 2.5 && abs(genSeed2.Eta()) < 2.5 && abs(genSeed3.Eta()) < 2.5 && abs(genSeed4.Eta()) < 2.5 ){
              //if ( (genSeed1.Pt() != 0 || genSeed2.Pt() != 0 || genSeed3.Pt() != 0 || genSeed4.Pt() != 0) ){
									nGenPhoEcal++;


                  gPho1RecHitEta = genSeed1.Eta();
                  gPho2RecHitEta = genSeed2.Eta();
                  gPho3RecHitEta = genSeed3.Eta();
                  gPho4RecHitEta = genSeed4.Eta();

                  gPho1RecHitPhi = genSeed1.Phi();
                  gPho2RecHitPhi = genSeed2.Phi();
                  gPho3RecHitPhi = genSeed3.Phi();
                  gPho4RecHitPhi = genSeed4.Phi();
                  
                  
                  gRecHitDeltaR_pho12 = genSeed1.DeltaR(genSeed2);
                  gRecHitDeltaR_pho13 = genSeed1.DeltaR(genSeed3);
                  gRecHitDeltaR_pho14 = genSeed1.DeltaR(genSeed4);
                  gRecHitDeltaR_pho23 = genSeed2.DeltaR(genSeed3);
                  gRecHitDeltaR_pho24 = genSeed2.DeltaR(genSeed4);
                  gRecHitDeltaR_pho34 = genSeed3.DeltaR(genSeed4);

                  gRecHitDeltaPhi_pho12 = genSeed1.DeltaPhi(genSeed2);
                  gRecHitDeltaPhi_pho13 = genSeed1.DeltaPhi(genSeed3);
                  gRecHitDeltaPhi_pho14 = genSeed1.DeltaPhi(genSeed4);
                  gRecHitDeltaPhi_pho23 = genSeed2.DeltaPhi(genSeed3);
                  gRecHitDeltaPhi_pho24 = genSeed2.DeltaPhi(genSeed4);
                  gRecHitDeltaPhi_pho34 = genSeed3.DeltaPhi(genSeed4);
                  
                  gRecHitDeltaEta_pho12 = genSeed1.Eta() - genSeed2.Eta();
                  gRecHitDeltaEta_pho13 = genSeed1.Eta() - genSeed3.Eta();
                  gRecHitDeltaEta_pho14 = genSeed1.Eta() - genSeed4.Eta();
                  gRecHitDeltaEta_pho23 = genSeed2.Eta() - genSeed3.Eta();
                  gRecHitDeltaEta_pho24 = genSeed2.Eta() - genSeed4.Eta();
                  gRecHitDeltaEta_pho34 = genSeed3.Eta() - genSeed4.Eta();
                  

                  //start gen matching

                  bool trigger_check = false;
                  TVector3 reco_pho1, reco_pho2, reco_pho3, reco_pho4;

                  if (pho1.Pt() > 50 && pho2.Pt() > 50){

                      trigger_check = true;


                      reco_pho1.SetXYZ(pho1SeedX, pho1SeedY, pho1SeedZ);
                      reco_pho3.SetXYZ(pho2SeedX, pho2SeedY, pho2SeedZ);

                      float DeltaR12 = pho1.DeltaR(pho2); 
                      float DeltaR13 = pho1.DeltaR(pho3); 
                      float DeltaR14 = pho1.DeltaR(pho4); 

                      if (DeltaR13 > DeltaR14){
                          reco_pho2.SetXYZ(pho4SeedX, pho4SeedY, pho4SeedZ);
                          reco_pho4.SetXYZ(pho3SeedX, pho3SeedY, pho3SeedZ);
                      }
                      else{
                          reco_pho2.SetXYZ(pho3SeedX, pho3SeedY, pho3SeedZ);
                          reco_pho4.SetXYZ(pho4SeedX, pho4SeedY, pho4SeedZ);
                      }


                      if (abs(reco_pho1.DeltaPhi(reco_pho3)) < 2.) trigger_check = false;
                      //if (reco_pho1.DeltaR(reco_pho2) > 3.5) trigger_check = false;
                      //if (reco_pho1.DeltaR(reco_pho3) < 2.) trigger_check = false;
                      //if (reco_pho1.DeltaR(reco_pho4) < 2.) trigger_check = false;

                      //if (reco_pho3.DeltaR(reco_pho4) > 3.5) trigger_check = false;
                      //if (reco_pho3.DeltaR(reco_pho2) < 2.) trigger_check = false;
                  }

                  //if (trigger_check == true){
                  //nMatched++;

                  for (int k = 0; k < 20; k++) {
                      float DR_ = float(k) * 0.05;
                      if ((reco_pho1.DeltaR(genSeed1) < DR_ && reco_pho2.DeltaR(genSeed2) < DR_ && reco_pho3.DeltaR(genSeed3) < DR_ && reco_pho4.DeltaR(genSeed4) < DR_) || (reco_pho1.DeltaR(genSeed3) < DR_ && reco_pho2.DeltaR(genSeed4) < DR_ && reco_pho3.DeltaR(genSeed1) < DR_ && reco_pho4.DeltaR(genSeed2) < DR_)) efficiency_deltaR[k]++;
                      //if ((reco_pho1.DeltaR(genSeed1) < DR_ && reco_pho2.DeltaR(genSeed2) < DR_ && reco_pho3.DeltaR(genSeed3) < DR_ && reco_pho4.DeltaR(genSeed4) < DR_) || (reco_pho1.DeltaR(genSeed3) < DR_ && reco_pho2.DeltaR(genSeed4) < DR_ && reco_pho3.DeltaR(genSeed1) < DR_ && reco_pho4.DeltaR(genSeed2) < DR_)) nMatched++;
                      //if ((reco_pho1.DeltaR(genSeed1) < 0.5 && reco_pho2.DeltaR(genSeed2) < 0.5 && reco_pho3.DeltaR(genSeed3) < 0.5 && reco_pho4.DeltaR(genSeed4) < 0.5) || (reco_pho1.DeltaR(genSeed3) < 0.5 && reco_pho2.DeltaR(genSeed4) < 0.5 && reco_pho3.DeltaR(genSeed1) < 0.5 && reco_pho4.DeltaR(genSeed2) < 0.5)) nCorrectMatched++;
                  }




              }
          }
      }
      outputTree->Fill();

   } //event loop

   for (int i = 0 ; i < 20; i++) {
      efficiency_deltaR[i] = efficiency_deltaR[i]/nGenPhoEcal;
      std::cout << i * 0.05 << " : " << efficiency_deltaR[i] << endl;
   }

   std::cout << "GenPhoOver4NEvents : " << GenPhoOver4NEvents << std::endl;
   std::cout << "SigPhoOver4NEvents : " << SigPhoOver4NEvents << std::endl;
   std::cout << "nGenPhoEcal : " << nGenPhoEcal << std::endl;
   std::cout << "nMatched : " << nMatched << std::endl;
   //std::cout << "nCorrectMatched : " << nCorrectMatched << std::endl;
   std::cout << endl;
   std::cout << "trigger rate : " << nMatched/nGenPhoEcal << endl;
   //std::cout << "correct ratio : " << nCorrectMatched/nMatched << endl;

   h1->Write();
   h2->Write();
   outputTree->Write();
   outFile->Close();
   

   file1.close();
   file2.close();
   

   std::cout << "Done!\n" << std::endl;

}
