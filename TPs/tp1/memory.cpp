#include "memory.h"

using namespace std;

tlm::tlm_response_status Memory::write(const ensitlm::addr_t &a,
                                       const ensitlm::data_t &d) {
	cout << "Memory(\"" <<  name() << "\"): write transaction, data: " << std::dec << d << " at @" << std::hex << a << endl;
	return tlm::TLM_OK_RESPONSE;
}

tlm::tlm_response_status Memory::read(const ensitlm::addr_t &a,
                                      /* */ ensitlm::data_t &d) {
	cout << "Memory(\"" <<  name() << "\"): read transaction, data: " << std::dec << d << " at @" << std::hex << a << endl;
	abort();
}