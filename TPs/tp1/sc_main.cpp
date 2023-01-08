#include "ensitlm.h"
#include "generator.h"
#include "memory.h"
#include "bus.h"
#include "LCDC.h"
#include "ROM.h"

using namespace sc_core;

int sc_main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	Generator generator("Generator1");
	Bus bus("Bus");
	Memory memory("Memory", TOTAL_MEMORY_SIZE_IN_BYTE);
	// Memory ports: [0; 87040[
	std::cout << "Memory ports: [" << MEMORY_START_ADDRESS << ";" << MEMORY_START_ADDRESS + TOTAL_MEMORY_SIZE_IN_BYTE << '[' << std::endl;
	bus.map(memory.target, MEMORY_START_ADDRESS, TOTAL_MEMORY_SIZE_IN_BYTE);
	generator.initiator.bind(bus.target);
	bus.initiator.bind(memory.target);

	LCDC lcdc("LCDC", sc_time(1.0 / 25, SC_SEC));
	// LCDC ports: [87040; 87096]
	std::cout << "LCDC ports: [" << LCD_CONTROLER_START_ADDRESS << ";" << LCD_CONTROLER_START_ADDRESS + LCDC_ADDRESS_RANGE_SIZE << "[" << std::endl;
	bus.map(lcdc.target_socket, LCD_CONTROLER_START_ADDRESS, LCDC_ADDRESS_RANGE_SIZE);
	lcdc.initiator_socket.bind(bus.target);
	lcdc.target_socket.bind(bus.initiator);
	
	sc_signal<bool> lcdc_generator_interruption_signal("lcdc_generator_interruption_signal");
	lcdc.display_intr.bind(lcdc_generator_interruption_signal);
	generator.interruption_port.bind(lcdc_generator_interruption_signal);

	ROM rom("ROM");
	// ROM ports : [87 096; 125 496]
	bus.map(rom.socket, ROM_START_ADDRESS, ROM_SIZE);
	bus.initiator.bind(rom.socket);

	sc_core::sc_start();
	return 0;
}
