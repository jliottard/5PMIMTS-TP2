#include "memory.h"

using namespace std;

Memory::Memory(sc_core::sc_module_name name, uint32_t storage_size_in_32_bits) : sc_core::sc_module(name) {
	size = storage_size_in_32_bits / 4;
	storage = new ensitlm::data_t[size];
}

Memory::~Memory() {
	delete storage;
}

tlm::tlm_response_status Memory::write(const ensitlm::addr_t &a,
                                       const ensitlm::data_t &d) {
	//cout << "Memory(\"" <<  name() << "\"): write transaction, data: " << std::dec << d << " at @" << std::hex << a << endl;
	if (size <= a / 4 || a % 4 != 0) {
		return tlm::TLM_ADDRESS_ERROR_RESPONSE;
	}
	storage[a / 4] = d;
	return tlm::TLM_OK_RESPONSE;
}

tlm::tlm_response_status Memory::read(const ensitlm::addr_t &a,
                                      /* */ ensitlm::data_t &d) {
	if (size <= a / 4 || a % 4 != 0) {
		return tlm::TLM_ADDRESS_ERROR_RESPONSE;
	}
	d = storage[a / 4];
	//cout << "Memory(\"" <<  name() << "\"): read transaction, data: " << std::dec << d << " at @" << std::hex << a << endl;
	return tlm::TLM_OK_RESPONSE;
}