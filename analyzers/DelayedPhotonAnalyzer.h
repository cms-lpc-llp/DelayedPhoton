#ifndef DEF_DelayedPhotonAnalyzer
#define DEF_DelayedPhotonAnalyzer

#include "RazorAnalyzer.h"

class DelayedPhotonAnalyzer: public RazorAnalyzer {
    public: 
        uint start_run_tmp;
        uint end_run_tmp;	
        uint start_time_tmp;
        uint end_time_tmp;	
        vector <float> *IC_time_all;
        vector <float> *rms_G12_all;
        vector <float> *rms_G1_all;
        vector <float> *rms_G6_all;
        vector <int> *detID_all;
		
        // for 2018ABC pre-legacy
        const double N_EB = 33.8;   //ns
        const double C_EB = 0.095; //ns
        const double N_EB_MC = 38.4; //ns
        const double C_EB_MC = 0.090; //ns

//		// for 2018ABC ultra-legacy
//        const double N_EB = 33.2;   //ns
//        const double C_EB = 0.097; //ns
//        const double N_EB_MC = 72.9; //ns
//        const double C_EB_MC = 0.104; //ns

        DelayedPhotonAnalyzer(TTree *tree=0): RazorAnalyzer(tree) { }
        void Analyze(bool isData, int option, string outputFileName, string label);
        float getADCToGeV( uint run, int isEBOrEE);
        TVector3 intersectPoint (float x0,float y0,float z0,float px,float py,float pz,float R);
        float getTimeCalibConstant(TTree *tree, vector <uint> & start_run, vector <uint> & end_run, uint run, uint detID);
};

#endif
