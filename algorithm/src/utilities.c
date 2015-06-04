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

char *random_string(int length){
	static const char alphanum[] =
	"0123456789"
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"abcdefghijklmnopqrstuvwxyz";
	int stringLength = sizeof(alphanum) - 1;
	char *str = (char *) malloc(length+1);
	int i = 0;
	for( i = 0; i < length; i++){
	    str[i] = alphanum[rand()%stringLength];// starting on 'A', ending on 'Z'
	}
	str[length] = '\0';
	return str;
}
void printArr(int arr[] , int n){
	int i = 0;
	for (i = 0 ; i < n ; i++){
		printf("%d,", arr[i]);
	}
	printf("\n");
}
