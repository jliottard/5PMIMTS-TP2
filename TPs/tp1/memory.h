#include "ensitlm.h"
#include "bus.h"

struct Memory : sc_core::sc_module {
	ensitlm::target_socket<Memory> target;
	ensitlm::data_t *storage;	// array of data (one data is 32 bits, 4 bytes)
	uint32_t size; 				// in 4 bytes
	tlm::tlm_response_status write(const ensitlm::addr_t &a,
	                               const ensitlm::data_t &d);

	tlm::tlm_response_status read(const ensitlm::addr_t &a,
	                              /* */ ensitlm::data_t &d);

	SC_CTOR(Memory) { /* */	}
	Memory(sc_core::sc_module_name name, uint32_t storage_size_in_bytes);
	~Memory();
};