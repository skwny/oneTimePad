// Dane Schoonover
// Date: 5 June 2016
// Description: This program generates a key file with a length provided by user input.
#include "enc_dec.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

		int i, size;
		size = atoi((argv[1]));
		srand(time(NULL));

		for(i = 0; i < size; i++){
			printf("%c", convertNumbers(rand() % 27));
		}
		printf("\n");
		return 0;
	}
