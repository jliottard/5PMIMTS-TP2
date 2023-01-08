#ifndef MEMORY_H
#define MEMORY_H

#include "ensitlm.h"
#include "bus.h"
#include "LCDC.h"

static const uint32_t EMBEDDED_CODE_MEMORY_SIZE_IN_BYTE = 10 * 1024;
static const uint32_t IMAGE_SIZE_IN_BYTE = LCDC::kWidth * LCDC::kHeight;
static const uint32_t VIDEO_MEMORY_SIZE_IN_BYTE = IMAGE_SIZE_IN_BYTE;
static const uint32_t TOTAL_MEMORY_SIZE_IN_BYTE = EMBEDDED_CODE_MEMORY_SIZE_IN_BYTE + VIDEO_MEMORY_SIZE_IN_BYTE;

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

#endif