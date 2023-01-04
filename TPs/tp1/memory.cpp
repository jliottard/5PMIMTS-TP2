#include "memory.h"

using namespace std;

Memory::Memory(sc_core::sc_module_name name, int32_t storage_size_in_byte) : sc_core::sc_module(name) {
	storage = new ensitlm::data_t[storage_size_in_byte / 4];
	size = storage_size_in_byte;
}

Memory::~Memory() {
	delete storage;
}

tlm::tlm_response_status Memory::write(const ensitlm::addr_t &a,
                                       const ensitlm::data_t &d) {
	cout << "Memory(\"" <<  name() << "\"): write transaction, data: " << std::dec << d << " at @" << std::hex << a << endl;
	//if (a < 0 || size )
	//TODO dernier point de Question3
	return tlm::TLM_OK_RESPONSE;
}

tlm::tlm_response_status Memory::read(const ensitlm::addr_t &a,
                                      /* */ ensitlm::data_t &d) {
	cout << "Memory(\"" <<  name() << "\"): read transaction, data: " << std::dec << d << " at @" << std::hex << a << endl;
	abort();
}