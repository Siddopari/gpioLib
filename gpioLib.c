/*
 * gpioLib.c
 * This file is part of gpioLib
 *
 * Copyright (C) 2014 - BhuvanChandra DV <bhuvanchandradv@gmail.com>
 *
 * gpioLib is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * gpioLib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with gpioLib. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/poll.h>

#include "gpioLib.h"

void gpioExport(int gpio){
	
	int fd = 0;
	char buf[128];
	fd = open(GPIO_EXPORT, O_WRONLY);
	if(fd < 0){
		perror("gpioExport: Open failed!");
		close(fd);
		return;
	}
	sprintf(buf, "%d", gpio);
	write(fd, buf, strlen(buf));
	if(fd < 0){
		perror("gpioExport: Write failed!");
		close(fd);
		return;
	}	
	close(fd);
}

void gpioUnexport(int gpio){
	int fd = 0;
	char buf[128];
	fd = open(GPIO_UNEXPORT, O_WRONLY);
	if(fd < 0){
		perror("gpioUnexport: Open failed!");
		close(fd);
		return;
	}
	sprintf(buf, "%d", gpio);
	write(fd, buf, strlen(buf));
	if(fd < 0){
		perror("gpioUnexport: Write failed!");
		close(fd);
		return;
	}		
	close(fd);
}

void gpioSetDir(int gpio, bool dir){
	
	int fd = 0, ret = 0;
	char path[128] = {0};
	sprintf(path, GPIO_DIR, gpio);
	
	fd = open(path, O_WRONLY);
	if(fd < 0){
		perror("gpioSetDir: Open failed!");
		close(fd);
		return;
	}

	switch(dir){
		case IN:
			ret = write(fd, "in", 2);
			if(ret < 0){
				perror("gpioSetDir: Write failed!");
				close(fd);
				return;
			}			
			break;
		case OUT:
			ret = write(fd, "out", 3);
			if(ret < 0){
				perror("gpioSetDir: Write failed!");
				close(fd);
				return;
			}			
			break;
	}
	close(fd);
}

void gpioSetLevel(int gpio, bool level){
	int fd = 0, retVal = 0;
	char path[128] = {0};
	sprintf(path, GPIO_VAL, gpio);
	fd = open(path, O_WRONLY);
	if(fd < 0){
		perror("gpioSetLevel: Open failed!");
		close(fd);
		return;
	}
	switch(level){
		case HIGH:
			retVal = write(fd, "1", 1);
			if(retVal < 0){
				perror("gpioSetLevel: Write failed!");
				close(fd);
				return;
			}			
			break;
		case LOW:
			retVal = write(fd, "0", 1);
			if(retVal < 0){
				perror("gpioSetLevel: Write failed!");
				close(fd);
				return;
			}			
			break;
	}
	close(fd);
}

void gpioEdge(int gpio, int type){
	int fd = 0, retVal = 0;
	char path[128] = {0};
	sprintf(path, GPIO_IRQ, gpio);
	fd = open(path, O_WRONLY);
	if(fd < 0){
		perror("gpioEdge: Open failed!");
		close(fd);
		return;
	}

	switch(type){
		case NONE:
			retVal = write(fd, "none", 4);
			if(retVal < 0){
				perror("gpioEdge: Write failed!");
				close(fd);
				return;
			}			 
			break;
		case RISING:
			retVal = write(fd, "rising", 6);
			if(retVal < 0){
				perror("gpioEdge: Write failed!");
				close(fd);
				return;
			}			
			break;
		case FALLING:
			retVal = write(fd,"falling", 7);
			if(retVal < 0){
				perror("gpioEdge: Write failed!");
				close(fd);
				return;
			}			
			break;
		case BOTH:
			retVal = write(fd, "both", 4);
			if(retVal < 0){
				perror("gpioEdge: Write failed!");
				close(fd);
				return;
			}			
			break;
	}
	close(fd);

}

void gpioGet(int mode, int gpio, int *retVal){
	int fd = 0, ret = 0;
	char path[128] = {0}, val;
	sprintf(path, GPIO_VAL, gpio);

	switch(mode){
		case NORMAL:
			fd = open(path, O_RDONLY);
			if(fd < 0){
				perror("gpioGet: Open failed!");
				close(fd);
			}		
			ret = read(fd, &val, 1);
			if(ret < 0){
				perror("gpioGet: Read failed!");
				close(fd);
				return;
			}			
			
			if(val == '1'){ 
				*retVal = HIGH;
			}
			else{
				*retVal = LOW;
			}			
			close(fd);
			break;
		case IO_POLLED:
			//gpioGetIoPolled(gpio, retVal);
			break;
		case EVENT_DRIVEN:
			//gpioGetEventDriven(gpio, retVal);
			break;
		case THREAED:
			//gpioGetThreaded(gpio, retVal);
			break;
	}

}

#if 0
void gpioGetIoPolled(int gpio, int *retVal){
	int fd = 0;
	char path[128] = {0}, val;
	sprintf(path, GPIO_VAL, gpio);
}

void gpioGetEventDriven(int gpio, int *retVal){
	int fd = 0;
	char path[128] = {0}, val;
	sprintf(path, GPIO_VAL, gpio);
}

void gpioGetThreaded(int gpio, int *retVal)(){
	int fd = 0;
	char path[128] = {0}, val;
	sprintf(path, GPIO_VAL, gpio);
}
#endif
