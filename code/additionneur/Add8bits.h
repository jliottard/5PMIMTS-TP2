#include <systemc>

SC_MODULE(Add8bits)
{
	sc_core::sc_in<sc_dt::sc_uint<8> > a, b;
	sc_core::sc_out<sc_dt::sc_uint<8> > c;

	SC_CTOR(Add8bits);

	void calcul();
};
