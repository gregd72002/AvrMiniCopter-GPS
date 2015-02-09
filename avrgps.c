#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <time.h>
#include <sched.h>
#include <sys/mman.h>
#include <getopt.h>

#include "i2cdev/i2cdev.h"

#include "routines.h"

int stop = 0;

#define BUFFER_SIZE  190
uint8_t gpsAddress = 0x42;
uint8_t slaves = 0;
uint8_t buf[BUFFER_SIZE];


void loop() {
	mssleep(200);	
	uint16_t bytes = readBytes(gpsAddress,0xFD,2,(uint8_t*) buf);
	if (!bytes) return; // got some TWI error. Return
	uint16_t totalBytes = ((uint16_t) buf[0] << 8) | buf[1];
	if (!totalBytes) return; // GPS not ready to send data. Return
	printf("GPS is ready to transfer %i bytes\n",totalBytes);
	while (totalBytes) {
		uint16_t bytes2Read;
		if (totalBytes > BUFFER_SIZE) {
			bytes2Read = BUFFER_SIZE;
		} else {
			bytes2Read = totalBytes;
		}
		bytes = readBytes(gpsAddress, 0xFF, bytes2Read,(uint8_t *) buf);
		for (uint8_t i = 0; i < bytes; i++) {
			printf("%c",buf[i]);
		}
		totalBytes -= bytes2Read;
	}
	printf("\n");
}

int main(int argc, char **argv) {

	while (!stop) {
		loop();
	}

	return 0;
}

