#include "ensitlm.h"
#include "bus.h"

struct Generator : sc_core::sc_module {
	ensitlm::initiator_socket<Generator> initiator;
	void process(void);

	SC_CTOR(Generator);

	private:
	void error_handling(tlm::tlm_response_status status);
};