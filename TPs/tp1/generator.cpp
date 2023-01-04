#include "generator.h"

using namespace std;

void Generator::process(void) {
	ensitlm::data_t data = 0;
	ensitlm::addr_t address = 0x10000000;
	for (int i = 0; i < 10; i++) {
		cout << "Generator(\"" <<  name() << "\"): sending data: " << std::dec << data << " at @" << std::hex << address << endl;
		tlm::tlm_response_status response = initiator.write(address, data);
		switch (response) {
			case tlm::TLM_OK_RESPONSE:
				break;
			case tlm::TLM_INCOMPLETE_RESPONSE:
				cout << "Generator: incomplete response" << endl;
				break;
			case tlm::TLM_GENERIC_ERROR_RESPONSE:
				cout << "Generator: generic error response" << endl;
				break;
			case tlm::TLM_ADDRESS_ERROR_RESPONSE:
				cout << "Generator: address error response" << endl;
				break;
			case tlm::TLM_COMMAND_ERROR_RESPONSE:
				cout << "Generator: command error response" << endl;
				break;
			case tlm::TLM_BURST_ERROR_RESPONSE:
				cout << "Generator: burst error response" << endl;
				break;
			case tlm::TLM_BYTE_ENABLE_ERROR_RESPONSE:
				cout << "Generator: byte enable error response" << endl;
				break;
			default:
				break;
		}
		data++;
		address += 4;
	}
}

Generator::Generator(sc_core::sc_module_name name) : sc_core::sc_module(name) {
	SC_THREAD(process);
}