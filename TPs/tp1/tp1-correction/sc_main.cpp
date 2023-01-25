#include "ensitlm.h"
#include "generator.h"
#include "memory.h"
#include "LCDC.h"
#include "ROM.h"
#include "bus.h"
#include "memmap.h"

#define RAM_SIZE 0x15400

using namespace sc_core;

int sc_main(int, char **) {
	Generator generator("Generatorx");
	Memory memory("Memoryks", RAM_SIZE);
	LCDC lcdc("LCDC", sc_time(1.0 / 25, SC_SEC));
	ROM rom("ROM");
	Bus bus("Bus");
	sc_signal<bool, SC_MANY_WRITERS> irq_signal("IRQ");

	// initiators
	generator.socket(bus.target);
	lcdc.initiator_socket(bus.target);

	// targets
	bus.initiator(memory.target);
	bus.initiator(lcdc.target_socket);
	bus.initiator(rom.socket);

	// interrupts
	lcdc.display_intr(irq_signal);
	generator.irq(irq_signal);

	bus.map(memory.target,      MEMORY_BASE, RAM_SIZE);
	bus.map(lcdc.target_socket, LCDC_BASE,   12);
	bus.map(rom.socket,         VROM_BASE,   ROM_SIZE);

	// start the simulation
	sc_start();

	return 0;
}
