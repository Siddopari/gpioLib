/*
 * main.c
 * A simple test application showing how to use gpioLib.
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
#include <unistd.h>
#include "gpioLib.h"

int main(int argc, char **argv){
	int count = 10, val = 0, gpioNum = 0;
		
	if(argc < 2){
		printf("Usage: %s <gpio number>\n", argv[0]);
		return -1;
	}
	gpioNum = atoi(argv[1]);
	gpioExport(gpioNum);	
	gpioSetDir(gpioNum, OUT);
	printf("Setting GPIO_%d direction to OUT and toggling it\n", gpioNum);
	printf("Connect LED to GPIO_%d and press any key to continue\n", gpioNum);
	getchar();	
	while(count > 0){
		gpioSetLevel(gpioNum, HIGH);
		sleep(1);
		gpioSetLevel(gpioNum, LOW);
		sleep(1);
		count --;
	}
	count = 10;	/* Reset the count value */
	
	gpioSetDir(gpioNum, IN);
	printf("Setting GPIO_%d direction to IN and reading its state\n", gpioNum);
	printf("Connect switch to GPIO_%d and press any key to continue\n", gpioNum);
	getchar();
	
	while(count > 0){
		gpioGet(NORMAL, gpioNum, &val);
		printf("GPIO_%d Level:%d\n", gpioNum, val);
		sleep(1);
		count --;			
	}
	
	gpioUnexport(gpioNum);

return 0;
}
