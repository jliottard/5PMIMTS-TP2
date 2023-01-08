#include "generator.h"
#include "LCDC_registermap.h"
#include "memory.h"

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

void Generator::print_debug(ensitlm::addr_t address, ensitlm::data_t data) {
	cout << "Generator(\"" <<  name() << "\"): writing: 0x" << hex << data << " at @" << dec << address << endl;
}

// check memory write and read
void Generator::testMemory(void) {
	uint32_t memory_size = TOTAL_MEMORY_SIZE_IN_BYTE;
	ensitlm::addr_t start_address = MEMORY_START_ADDRESS;

	ensitlm::data_t data_to_write = 0;
	ensitlm::data_t read_data = 0;
	ensitlm::addr_t end_address = start_address + memory_size;
	for (ensitlm::addr_t address = start_address; address < end_address; address += 4) {
		// Write in memory
		print_debug(address, data_to_write);	
		tlm::tlm_response_status response_status = initiator.write(address, data_to_write);
		error_handling(response_status);
		// Read in memory
		tlm::tlm_response_status response = initiator.read(address, read_data);
		error_handling(response);
		if (response == tlm::TLM_OK_RESPONSE) {
			cout << "Generator(\"" <<  name() << "\"): receiving data: 0x" << hex << read_data << " at @" << dec << address << endl;
		}
		if (data_to_write != read_data) {
			cout << "Error : written data and read data mismatch" << endl;
			return;
		}
		data_to_write++;
	}
}

// check LCDC's start phase
void Generator::testLCDC(void) {
	// Init LCDC ADDR_REG
	ensitlm::addr_t addr_reg_address = VIDEO_MEMORY_START_ADDRESS + LCDC_ADDR_REG;
	ensitlm::data_t data = VIDEO_MEMORY_START_ADDRESS;
	tlm::tlm_response_status response_status = initiator.write(addr_reg_address, data);
	error_handling(response_status);

	// Test LDCC REG_START register
	ensitlm::addr_t reg_start_address = VIDEO_MEMORY_START_ADDRESS + LCDC_START_REG;
	data = 0x1;
	print_debug(reg_start_address, data);
	response_status = initiator.write(reg_start_address, data);
	error_handling(response_status);
}

void Generator::whiteImage(void) {
	// Init the ADDR_REG of the LCDC
	ensitlm::addr_t addr_reg_address = LCD_CONTROLER_START_ADDRESS + LCDC_ADDR_REG;
	ensitlm::data_t video_memory_buffer_address = VIDEO_MEMORY_START_ADDRESS;
	print_debug(addr_reg_address, video_memory_buffer_address);
	tlm::tlm_response_status response_status = initiator.write(addr_reg_address, video_memory_buffer_address);
	error_handling(response_status);

	// Write white pixels in video memory
	ensitlm::data_t white_pixel = 0xFFFFFFFF;
	ensitlm::addr_t video_mem_end_addr = VIDEO_MEMORY_START_ADDRESS + IMAGE_SIZE_IN_BYTE;
	for (ensitlm::addr_t cur_pixel_addr = VIDEO_MEMORY_START_ADDRESS; cur_pixel_addr < video_mem_end_addr; cur_pixel_addr += 4) {
		//print_debug(cur_pixel_addr, white_pixel);
		response_status = initiator.write(cur_pixel_addr, white_pixel);
		error_handling(response_status);
		if (response_status == tlm::TLM_ADDRESS_ERROR_RESPONSE) {
			cout << "breaking in white pixel writting" << endl;
			return;
		}
	}

	// Start the LCDC
	ensitlm::addr_t start_reg_address = LCD_CONTROLER_START_ADDRESS + LCDC_START_REG;
	ensitlm::data_t start_trigger = 1;
	print_debug(start_reg_address, start_trigger);
	response_status = initiator.write(start_reg_address, start_trigger);
	if (response_status == tlm::TLM_ADDRESS_ERROR_RESPONSE) {
		return;
	}
	error_handling(response_status);

	// Refresh LCDC
	ensitlm::addr_t interrupt_register_address = LCD_CONTROLER_START_ADDRESS + LCDC_INT_REG;
	ensitlm::data_t deassert_interrupt_data = 0;
	print_debug(interrupt_register_address, deassert_interrupt_data);
	response_status = initiator.write(interrupt_register_address, deassert_interrupt_data);
	error_handling(response_status);
}

void Generator::idle(void) {}

Generator::Generator(sc_core::sc_module_name name) : sc_core::sc_module(name) {
	SC_THREAD(whiteImage);
}