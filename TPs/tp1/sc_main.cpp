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
	uint32_t memory_size_in_byte = 0x100;
	Memory memory("Memory", memory_size_in_byte);

	bus.map(memory.target, 0x10000000, memory_size_in_byte + 1);
	generator.initiator.bind(bus.target);
	bus.initiator.bind(memory.target);

	LCDC lcdc("LCDC", sc_time(1.0 / 25, SC_SEC));
	bus.map(lcdc.target_socket, 0x20000000, 0x100 + 1);
	lcdc.initiator_socket.bind(bus.target);
	lcdc.target_socket.bind(bus.initiator);
	
	sc_signal<bool> lcdc_generator_interruption_signal("lcdc_generator_interruption_signal");
	lcdc.display_intr.bind(lcdc_generator_interruption_signal);
	generator.interruption_port.bind(lcdc_generator_interruption_signal);

	sc_core::sc_start();
	return 0;
}
