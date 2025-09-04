#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <fstream>

#include <stack>
#include <array>
#include <vector>
#include <chrono>
#include <map>

enum STAGE {  
  ENCODER_OVERALL = 0,

  INTRA_OVERALL = 1,
  INTER_OVERALL = 2,

  INTER_IME = 3,
  INTER_FME = 4,
  INTER_AME = 5,
  
  NUM_STAGES = 6
};

typedef std::milli rep;
typedef std::chrono::steady_clock clock_s;
typedef std::chrono::time_point<clock_s> time_point;
typedef std::chrono::duration<double, rep> duration;

class TimeProfilerPredictions {  

  public:
    static std::vector<time_point> previous;
    static std::vector<duration> durations;
    static std::vector<int> calls;
    static std::map<STAGE, std::string> stageToString;
    static std::string reportFileName;

    static void init(char fileName[]);
    static void start( STAGE s );
    static void stop( STAGE s );
    static void report();
};
