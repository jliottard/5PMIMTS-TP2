#include "generator.h"

using namespace std;

void Generator::process(void) {
}

Generator::Generator(sc_core::sc_module_name name) : sc_core::sc_module(name) {
	SC_THREAD(process);
}