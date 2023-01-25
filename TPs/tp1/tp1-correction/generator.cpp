#include "generator.h"
#include "LCDC_registermap.h"
#include "memmap.h"

#define WIDTH 320
#define HEIGHT 240
#define IMG_SIZE (WIDTH * HEIGHT)

using namespace std;
using namespace sc_core;

Generator::Generator(sc_module_name name) : sc_module(name), irq("irq") {
	SC_THREAD(compute);

	SC_METHOD(interrupt_handler);
	sensitive << irq.pos();
	dont_initialize();

	interrupt = false;
}

void Generator::compute() {
	unsigned i = 0;

	test(0);
	socket.write(LCDC_BASE + LCDC_ADDR_REG, VRAM_BASE);
	socket.write(LCDC_BASE + LCDC_START_REG, 0x000000001);

	while (true) {
		if (!interrupt)
			wait(interrupt_event);
		interrupt = false;

		cout << name() << ": interrupt caught!" << endl;
		socket.write(LCDC_BASE + LCDC_INT_REG, 0x00000000);

                // Just to show that the image is moving each time an interrupt is triggered
		i = i % HEIGHT;
		test(i);
		i++;
	}
}

void Generator::test(unsigned initvalue) {
	ensitlm::addr_t a = VRAM_BASE;
	ensitlm::addr_t b = VROM_BASE + initvalue * WIDTH;
	ensitlm::data_t rvalue, wval1, wval2;

#ifdef DEBUG
	cout << name() << ": test(" << initvalue << ")" << endl;
#endif
	for (int y = 0; y < HEIGHT * WIDTH / 8; y++) {
		if (b >= (VROM_BASE + IMG_SIZE / 2))
			b = b - IMG_SIZE / 2;
		socket.read(b, rvalue);
#ifdef DEBUG
		cout << name() << ": done read (0x" << hex << b << ", 0x"
		     << rvalue << ") /* ROM */;" << endl;
#endif

		wval1 = ((rvalue & 0xF0000000)) +
                        ((rvalue & 0x0F000000) >> 4) +
		        ((rvalue & 0x00F00000) >> 8) +
		        ((rvalue & 0x000F0000) >> 12);

		wval2 = ((rvalue & 0x0000F000) << 16) +
		        ((rvalue & 0x00000F00) << 12) +
		        ((rvalue & 0x000000F0) << 8) +
		        ((rvalue & 0x0000000F) << 4);

		socket.write(a, wval1);
#ifdef DEBUG
		cout << name() << ": done write(0x" << hex << a << ", 0x"
		     << wval1 << ") /* RAM */;" << endl;
#endif
		a += 4;
		socket.write(a, wval2);
#ifdef DEBUG
		cout << name() << ": done write(0x" << hex << a << ", 0x"
		     << wval2 << ") /* RAM */;" << endl;
#endif
		a += 4;
		b += 4;
	}
	cout << name() << ": finished image" << endl;
}

void Generator::interrupt_handler() {
	interrupt = true;
	interrupt_event.notify();
}
