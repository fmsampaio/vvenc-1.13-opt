#include "TraceIntraCUs.h"

std::ofstream TraceIntraCUs::fp;

void TraceIntraCUs::init() {
    fp.open("intra-cu-trace.txt");
}

void TraceIntraCUs::trace(int framePoc, int wCU, int hCU) {
    fp << framePoc << ";" << wCU << ";" << hCU << std::endl;
}

void TraceIntraCUs::finish() {
    fp.close();
}

