CC=gcc -std=c11
INCLUDE=-I. -I../../
CFLAGS=$(INCLUDE) -g

# Là on compile le logiciel embarqué en natif : c'est un .c
# On a vu qu'il inclut address_map.h => on en dépend, vu que c'est
# un fichier .h maison (pas genre stdout.h)
# Il inclut plein de trucs à nous aussi, donc on explicite ces dépendances
# Si qqchose devait bouger dans ces .h, il faudrait recompiler le soft embarqué
main.o: ../main.c ../../address_map.h ../../hardware/offsets/gpio.h ../../hardware/offsets/timer.h ../../hardware/offsets/vga.h ../../hardware/offsets/uart.h ../../hardware/offsets/intc.h hal.h
	# Là je mets un -o car si je voulais pour une raison ou pour une autre changer ce nom, ça serait facile
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean realclean
clean:
	$(RM) main.o

realclean: clean
	-$(RM) *~
