#include <fstream>

class TraceIntraCUs {
    private:
        static std::ofstream fp; 

    public:
        static void init();
        static void trace(int framePoc, int wCU, int hCU);
        static void finish();
};