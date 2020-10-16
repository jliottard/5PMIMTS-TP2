#include <systemc>

using namespace sc_core;

SC_MODULE(Testbench)
{
	sc_out<bool>              clk;
	sc_out<bool>              reset;
	sc_in<sc_dt::sc_uint<8> > count;

	SC_CTOR(Testbench);

	void genClk();
	void genReset();
};
