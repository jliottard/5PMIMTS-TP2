#include "generator.h"

using namespace std;

void Generator::error_handling(tlm::tlm_response_status status) {
	switch (status) {
		case tlm::TLM_OK_RESPONSE:
			break;
		case tlm::TLM_INCOMPLETE_RESPONSE:
			cout << "error: Generator(\"" <<  name() << "\") has received an incomplete response" << endl;
			break;
		case tlm::TLM_GENERIC_ERROR_RESPONSE:
			cout << "error: Generator(\"" <<  name() << "\") has received an generic error response" << endl;
			break;
		case tlm::TLM_ADDRESS_ERROR_RESPONSE:
			cout << "error: Generator(\"" <<  name() << "\") has received an address error response" << endl;
			break;
		case tlm::TLM_COMMAND_ERROR_RESPONSE:
			cout << "error: Generator(\"" <<  name() << "\") has received an command error response" << endl;
			break;
		case tlm::TLM_BURST_ERROR_RESPONSE:
			cout << "error: Generator(\"" <<  name() << "\") has received an burst error response" << endl;
			break;
		case tlm::TLM_BYTE_ENABLE_ERROR_RESPONSE:
			cout << "error: Generator(\"" <<  name() << "\") has received an byte enable error response" << endl;
			break;
		default:
			break;
	}
}

void Generator::process(void) {
	uint32_t memory_size = 0x100;
	ensitlm::addr_t start_address = 0x10000000;

	ensitlm::data_t data = 0;
	ensitlm::addr_t end_address = start_address + memory_size;
	// Write in memory
	for (ensitlm::addr_t address = start_address; address < end_address; address += 4) {
		// cout << "Generator(\"" <<  name() << "\"): sending data: " << std::dec << data << " at memory@" << std::hex << address << endl;
		tlm::tlm_response_status response_status = initiator.write(address, data);
		error_handling(response_status);
		data++;
	}
	// Read in memory
	data = 0;
	for (ensitlm::addr_t address = start_address; address < end_address; address += 4) {
		tlm::tlm_response_status response = initiator.read(address, data);
		// cout << "Generator(\"" <<  name() << "\"): receiving data: " << std::dec << data << " from memory@" << std::hex << address << endl;
		error_handling(response);
		address += 4;
	}
}

Generator::Generator(sc_core::sc_module_name name) : sc_core::sc_module(name) {
	SC_THREAD(process);
}