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
	
        const double N_EB = 30.4;   //ns
        const double C_EB = 0.095; //ns
        const double N_EB_MC = 34.3; //ns
        const double C_EB_MC = 0.103; //ns

        DelayedPhotonAnalyzer(TTree *tree=0): RazorAnalyzer(tree) { }
        void Analyze(bool isData, int option, string outputFileName, string label);
        float getADCToGeV( uint run, int isEBOrEE);
        TVector3 intersectPoint (float x0,float y0,float z0,float px,float py,float pz,float R);

};

#endif
