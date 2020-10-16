#ifndef CONSOMMATEUR_H
#define CONSOMMATEUR_H

#include <systemc>

using namespace sc_core;

SC_MODULE(Consommateur)
{
	sc_port<sc_fifo_in_if<int> >	entree;

	SC_CTOR(Consommateur);

	void consommation();
};

#endif
