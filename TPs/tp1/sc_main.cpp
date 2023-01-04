#include "ensitlm.h"
#include "generator.h"
#include "memory.h"
#include "bus.h"

int sc_main(int argc, char **argv) {
	(void)argc;
	(void)argv;

	Generator generator("Generator1");
	Bus bus("Bus");
	uint32_t memory_size_in_byte = 0x100;
	Memory memory("Memory", memory_size_in_byte);

	bus.map(memory.target, 0x10000000, (ensitlm::addr_t) memory_size_in_byte);
	generator.initiator.bind(bus.target);
	bus.initiator.bind(memory.target);

	sc_core::sc_start();
	return 0;
}
