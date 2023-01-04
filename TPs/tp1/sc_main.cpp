#include "ensitlm.h"
#include "generator.h"
#include "bus.h"

int sc_main(int argc, char **argv) {
	(void)argc;
	(void)argv;

	Generator generator("Generator1");
	Bus bus("Bus");

	generator.initiator.bind(bus.target);
	
	sc_core::sc_start();
	return 0;
}
