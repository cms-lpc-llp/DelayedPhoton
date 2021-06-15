#ifndef DEF_DelayedResonantPhoton
#define DEF_DelayedResonantPhoton

#include "RazorAnalyzer.h"

class DelayedResonantPhoton: public RazorAnalyzer {
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

		// for 2017
        const double N_EB = 34.7;   //ns
        const double C_EB = 0.077; //ns
        const double N_EB_MC = 36.9; //ns
        const double C_EB_MC = 0.087; //ns
		

        DelayedResonantPhoton(TTree *tree=0): RazorAnalyzer(tree) { }
        void Analyze(bool isData, int option, string outputFileName, string label);
        float getADCToGeV( uint run, int isEBOrEE);
        TVector3 intersectPoint (float x0,float y0,float z0,float px,float py,float pz,float R);
        float getTimeCalibConstant(TTree *tree, vector <uint> & start_run, vector <uint> & end_run, uint run, uint detID);
};

#endif
