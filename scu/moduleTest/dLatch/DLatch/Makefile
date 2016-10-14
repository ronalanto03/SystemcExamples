#Nombre del programa
MODULE = test.sm

#compilador usado
CC= g++-4.4
#Archivos que se compilaran
SRCS =DLatch_main.cpp
SCU_PATH=/home/ronalanto03/Desktop/scu
#Direccion de systemc
SYSTEMC = /usr/local/lib/systemc-2.2.0


include ./Makefile.defs

run:$(EXE)
	@./$(EXE)

view: tf.vcd
	@gtkwave -f tf.vcd -cpu=4

trace:$(EXE)
		@./$(EXE) -mt
		clear

info:
	@echo "\ndLatch class to simulate any kind of latch register clocked and unclocked\n" 
