/*
 * utilities.c
 *
 *  Created on: May 24, 2015
 *      Author: hunglv
 */
 #include <string.h>

void random_array(int _array[], int size, int max){
	int i = 0;
	memset(_array, 0, sizeof(_array));
	for( i= 0; i < size; i++ ) _array[i] = rand() %max;
}

