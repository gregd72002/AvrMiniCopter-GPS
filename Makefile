CXX=g++
CXX_OPTS= -Wall -g -O2 -Ilibs/ 
CXXFLAGS=$(CXX_OPTS)

CC=cc
CFLAGS=
CC_OPTS=-lstdc++ -lm
LDFLAGS=$(CC_OPTS)
#LDFLAGS=-lpthread -pthread -lstdc++ -lsupc++ 
#LD_OPTS=-lpthread -lrt -lstdc++

INSTALL=install

OBJ_AVRGPS=avrgps.o routines.o libs/libi2cdev.a

%.o: %.c                                                                         
	$(CXX) -c $(CXXFLAGS) $(CXX_OPTS) $< -o $@ 

all: avrgps 

avrgps: $(OBJ_AVRGPS)
	$(CC) $(CFLAGS) $(OBJ_AVRGPS) -o avrgps $(LDFLAGS) $(CC_OPTS) 

libs/libi2cdev.a:
	$(MAKE) -C libs/i2cdev

install:
	$(INSTALL) -m 0755 -d $(DESTDIR)/usr/local/bin
	$(INSTALL) -m 755 avrgps $(DESTDIR)/usr/local/bin/

clean:
	cd libs/i2cdev && $(MAKE) clean
	rm -rf avrgps
	rm -rf *.o

