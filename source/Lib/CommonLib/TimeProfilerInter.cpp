#include "TimeProfilerInter.h"

std::vector<time_point> TimeProfilerInter::previous;
std::vector<duration> TimeProfilerInter::durations;
std::vector<int> TimeProfilerInter::calls;
std::string TimeProfilerInter::reportFileName;

std::map<STAGE, std::string> TimeProfilerInter::stageToString;

void TimeProfilerInter::init(char fileName[])  {
    durations.resize( NUM_STAGES );
    previous.resize( NUM_STAGES );
    calls.resize( NUM_STAGES );

    for( size_t i = 0; i < NUM_STAGES; ++i ) {
        durations[i] = durations[i].zero();
        calls[i] = 0;
    }

    stageToString[QT_LEVEL_0]= "QT_0";
    stageToString[QT_LEVEL_1] = "QT_1";
    stageToString[QT_LEVEL_2] = "QT_2";
    stageToString[QT_LEVEL_3] = "QT_3";
    stageToString[QT_LEVEL_4] = "QT_4";
    stageToString[INTER_OVERALL] = "INTER";
    stageToString[ENCODER_OVERALL] ="ENCODER";

    reportFileName = fileName;
}

void TimeProfilerInter::start( STAGE s ) {
    previous[s] = clock_s::now();
}

void TimeProfilerInter::stop( STAGE s ) {
    time_point now = clock_s::now();
    durations[s] += ( now - previous[s] );
    calls[s] ++;
}

void TimeProfilerInter::report() {    
    std::ofstream reportFp;
    reportFp.open(reportFileName);
    
    reportFp << "Stage;Calls;Time(ms);TimePerCall(ms)\n";
    for( size_t i = 0; i < NUM_STAGES; ++i ) {
        STAGE s = (STAGE) i;
        double duration = durations[i].count();
        reportFp << stageToString[s] << ";" << calls[s] << ";" << duration << ";" << (duration / calls[i]) << std::endl;
    }
    reportFp.close();

}