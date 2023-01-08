#ifndef GENERATOR_H
#define GENERATOR_H

#include "ensitlm.h"
#include "bus.h"
#include "memory.h"

#define MEMORY_START_ADDRESS (0)
#define VIDEO_MEMORY_START_ADDRESS (MEMORY_START_ADDRESS + EMBEDDED_CODE_MEMORY_SIZE_IN_BYTE)
#define LCD_CONTROLER_START_ADDRESS (VIDEO_MEMORY_START_ADDRESS + VIDEO_MEMORY_SIZE_IN_BYTE)

struct Generator : sc_core::sc_module {
	ensitlm::initiator_socket<Generator> initiator;
	sc_core::sc_in<bool> interruption_port;
	void testMemory(void);
	void testLCDC(void);
	void whiteImage(void);
	void idle(void);

	SC_CTOR(Generator);

	private:
	void error_handling(tlm::tlm_response_status status);
	void print_debug(ensitlm::addr_t address, ensitlm::data_t data);
};

#endif