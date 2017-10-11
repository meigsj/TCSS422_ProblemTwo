rr.out: RoundRobin.o fifo.o pcb.o
	gcc -o rr.out RoundRobin.o fifo.o pcb.o

RoundRobin.o: RoundRobin.c fifo.h pcb.h
	gcc -c RoundRobin.c

fifo.o: fifo.c fifo.h pcb.h
	gcc -c fifo.c

pcb.o: pcb.c pcb.h
	gcc -c pcb.c