#ifndef GENERATOR_H
#define GENERATOR_H

#include "ensitlm.h"
#include "bus.h"
#include "memory.h"

#define MEMORY_START_ADDRESS (0)
#define VIDEO_MEMORY_START_ADDRESS (MEMORY_START_ADDRESS + EMBEDDED_CODE_MEMORY_SIZE_IN_BYTE)
#define LCD_CONTROLER_START_ADDRESS (VIDEO_MEMORY_START_ADDRESS + VIDEO_MEMORY_SIZE_IN_BYTE)
#define ROM_START_ADDRESS (LCD_CONTROLER_START_ADDRESS + LCDC_ADDRESS_RANGE_SIZE)

struct Generator : sc_core::sc_module {
	ensitlm::initiator_socket<Generator> initiator;
	//sc_core::sc_in<bool> interruption_port;
	sc_core::sc_in<bool> irq;
	void testMemory(void);
	void testLCDC(void);
	void writeWhiteImage(void);
	void writePixel(ensitlm::data_t pixel);
	void testROM(void);
	void main(void);
	void idle(void);

	SC_CTOR(Generator);

	private:
	sc_core::sc_event irq_event;
	void error_handling(tlm::tlm_response_status status);
	void print_debug(ensitlm::addr_t address, ensitlm::data_t data);
	void convert_rom_to_lcdc_pixels(ensitlm::data_t rom_pixels, ensitlm::data_t& first_part_pixels, ensitlm::data_t& second_part_pixels);

	void handle_irq(void);

	void init_lcdc(void);
	void start_lcdc(void);
	void writeRomImage(void);
	void refresh_lcdc(void);
};

#endif