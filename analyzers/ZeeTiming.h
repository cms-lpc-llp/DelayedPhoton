#ifndef DEF_ZeeTiming
#define DEF_ZeeTiming

#include "RazorAnalyzer.h"
#include "RazorEvents.h"

class ZeeTiming: public RazorAnalyzer {
    public: 
        ZeeTiming(TTree *tree=0): RazorAnalyzer(tree) { }
        void Analyze(bool isData, int option, string outputFileName, string label);
		float getTimeCalibConstant(TTree *tree, vector <uint> & start_run, vector <uint> & end_run, uint run, uint detID);
		float getPedestalNoise(TTree *tree, vector <uint> & start_time, vector <uint> & end_time, uint time, uint detID);
		float getADCToGeV( uint run, int isFromEB);

        const double N_EB = 30.4;   //ns
        const double C_EB = 0.095; //ns
        const double N_EB_MC = 34.3; //ns
        const double C_EB_MC = 0.103; //ns

        uint start_run_tmp;
        uint end_run_tmp;	
        uint start_time_tmp;
        uint end_time_tmp;	
        vector <float> *IC_time_all;
        vector <float> *rms_G12_all;
        vector <float> *rms_G1_all;
        vector <float> *rms_G6_all;
        vector <int> *detID_all;
};

#endif
