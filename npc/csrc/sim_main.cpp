#include <stdlib.h>
#include <iostream>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Valu.h"

#define MAX_SIM_TIME 20
vluint64_t sim_time = 0;

int main(int argc, char** argv, char** env) {
    Valu *alu = new Valu;

    Verilated::traceEverOn(true);
    VerilatedVcdC *m_trace = new VerilatedVcdC;
    alu->trace(m_trace, 5);
    m_trace->open("waveform.vcd");

    while (sim_time < MAX_SIM_TIME) {
        int a = rand() & 1;
        int b = rand() & 1;
        alu->a = a;
        alu->b = b;
        alu->eval();
        m_trace->dump(sim_time);
        sim_time++;
    }

    m_trace->close();
    delete alu;
    exit(EXIT_SUCCESS);
}
