#include "ensitlm.h"
#include "generator.h"
#include "memory.h"
#include "bus.h"
#include "LCDC.h"

using namespace sc_core;

int sc_main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	Generator generator("Generator1");
	Bus bus("Bus");
	Memory memory("Memory", MEMORY_SIZE_IN_BYTE);

	bus.map(memory.target, 0x0, MEMORY_SIZE_IN_BYTE);
	generator.initiator.bind(bus.target);
	bus.initiator.bind(memory.target);

	LCDC lcdc("LCDC", sc_time(1.0 / 25, SC_SEC));
	uint32_t lcdc_address_range_in_byte = 32 * 3;
	bus.map(lcdc.target_socket, MEMORY_SIZE_IN_BYTE + 4, lcdc_address_range_in_byte);
	lcdc.initiator_socket.bind(bus.target);
	lcdc.target_socket.bind(bus.initiator);
	
	sc_signal<bool> lcdc_generator_interruption_signal("lcdc_generator_interruption_signal");
	lcdc.display_intr.bind(lcdc_generator_interruption_signal);
	generator.interruption_port.bind(lcdc_generator_interruption_signal);

	sc_core::sc_start();
	return 0;
}
