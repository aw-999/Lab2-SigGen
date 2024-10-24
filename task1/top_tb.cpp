#include "Vsinegen.h" 
#include "verilated.h"
#include "verilated_vcd_c.h"

#include "vbuddy.cpp"     // include vbuddy code
#define MAX_SIM_CYC 1000000
#define ADDRESS_WIDTH 8
#define ROM_SZ 256

int main(int argc, char **argv, char **env) {
    int simcyc;
    int tick;

    Verilated::commandArgs(argc, argv);

    // init top verilog instance
    Vsinegen* top = new Vsinegen;       //Vtop instead of Vcounter

    // init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("sinegen.vcd");

    //init Vbuddy
    if (vbdOpen() != 1){
        return -1;
    }
    vbdHeader("Lab 2: SigGen");
    //vbdSetMode(1);

    // initialize simulation inputs
    top->clk = 1;
    top->rst = 0;
    //top->en = 0;
    top->en = 1;                    
    top->incr = 1;

    // run simulation for many clock cycles
    for (simcyc = 0; simcyc < MAX_SIM_CYC; symcic++) {

        // dump variables into VCD file and toggle clock
        for (tick = 0; tick < 2; tick++) {
            tfp->dump(2*simcyc+tick);  // unit is in ps!!!
            top->clk = !top->clk;
            top->eval();
        }
    
        // send count to vbuddy
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        vbdHex(4, (int(top->bcd) >> 16) & 0xF);     //updated bcd to count
        vbdHex(3, (int(top->bcd) >> 8) & 0xF);
        vbdHex(2, (int(top->bcd) >> 4) & 0xF);
        vbdHex(1, int(top->bcd) & 0xF);
        vbdCycle(i + 1);
        // end of output section

        // Change rst and en signals during simulation
        top->incr = vbdValue();
        top->rst = (i < 2) | (i == 15);
        top->en = vbdFlag();

        if ((Verilated::gotFinish()) exit(0) || vbdGetkey() == 'q'){
            exit(0);
        }
    }
    
    vbdClose(); // closes vbuddy
    tfp->close();
    exit(0);
}
