#include "TimeProfilerPredictions.h"

std::vector<time_point> TimeProfilerPredictions::previous;
std::vector<duration> TimeProfilerPredictions::durations;
std::vector<int> TimeProfilerPredictions::calls;
std::string TimeProfilerPredictions::reportFileName;

std::map<STAGE, std::string> TimeProfilerPredictions::stageToString;

void TimeProfilerPredictions::init(char fileName[])  {
    durations.resize( NUM_STAGES );
    previous.resize( NUM_STAGES );
    calls.resize( NUM_STAGES );

    for( size_t i = 0; i < NUM_STAGES; ++i ) {
        durations[i] = durations[i].zero();
        calls[i] = 0;
    }

    stageToString[INTRA_OVERALL] = "INTRA";
    stageToString[INTER_OVERALL] = "INTER";

    stageToString[INTER_IME] = "INTER_IME";
    stageToString[INTER_FME] = "INTER_FME";
    stageToString[INTER_AME] = "INTER_AME";

    stageToString[ENCODER_OVERALL] = "ENCODER";

    reportFileName = fileName;
}

void TimeProfilerPredictions::start( STAGE s ) {
    previous[s] = clock_s::now();
}

void TimeProfilerPredictions::stop( STAGE s ) {
    time_point now = clock_s::now();
    durations[s] += ( now - previous[s] );
    calls[s] ++;
}

void TimeProfilerPredictions::report() {    
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