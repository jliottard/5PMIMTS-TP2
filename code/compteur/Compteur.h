#include <systemc>

using namespace sc_core;

SC_MODULE(Compteur)
{
	sc_in<bool>         clk;
	sc_in<bool>         reset;
	sc_out<sc_dt::sc_uint<8> > count;

	SC_CTOR(Compteur);

	void calcul();
};
