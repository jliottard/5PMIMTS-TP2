#ifndef GENERATOR_H
#define GENERATOR_H

#include "ensitlm.h"
#include "bus.h"

struct Generator : sc_core::sc_module {
	ensitlm::initiator_socket<Generator> initiator;
	sc_core::sc_in<bool> interruption_port;
	void testMemory(void);
	void testLCDC(void);
	void empty(void);

	SC_CTOR(Generator);

	private:
	void error_handling(tlm::tlm_response_status status);
};

#endif