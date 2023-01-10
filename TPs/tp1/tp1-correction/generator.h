#ifndef GENERATOR_H
#define GENERATOR_H

#include "ensitlm.h"

struct Generator : sc_core::sc_module {
	ensitlm::initiator_socket<Generator> socket;
	sc_core::sc_in<bool> irq;

	SC_CTOR(Generator);

	void compute();
	void test(unsigned initvalue);

	void interrupt_handler();

	bool interrupt;
	sc_core::sc_event interrupt_event;
};

#endif
