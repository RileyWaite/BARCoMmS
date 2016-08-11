CFLAGS = -c -g -Wall -I. -I../PUB

default : cfdp copy 

cfdp : cfdp.o comm.o link_sim.o link_type.o \
              trans_list.o udp.o user.o usleep.o \
              ../PRI/libcfdp.a
	gcc -g -L../PRI -o cfdp cfdp.o \
            comm.o link_sim.o link_type.o \
            trans_list.o user.o udp.o usleep.o -lcfdp

copy :
	cp cfdp ../TEST/cfdp_app ; echo "Binary copied."


clean : remove_executable remove_objects cfdp copy remove_objects

remove_executable :
	rm -f cfdp

remove_objects :
	rm -f *.o
