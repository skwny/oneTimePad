// Dane Schoonover
// Date: 5 June 2016
// Description: This program requests encoding from otp_enc_d.
#include "enc_dec.h"
#include <stdio.h>
#include <stdlib.h>
// otp_dec filename
#define fn "otp_enc"
// Encode flag
#define enc_flag '^'
#define fn "otp_enc"


int main(int argc, char *argv[]){
	
	// Check for user provided port
	if(argc < 4 || argc > 4){
		usage1();
		exit(1);
	}
	
	// BUFFERS
	// input 1
	char buffer1[99999];
	bzero(buffer1,99999);		
	// input 2
	char buffer2[99999];
	bzero(buffer2,99999);		
	// output
	char buffer3[99999];
	bzero(buffer3,99999);		
	// errors
	char buffer4[256];	
	bzero(buffer4, 256);

	int flag;

	// Get input file
	flag = getText(argv[1], argv[2], buffer1, buffer2);
	if (flag == -1) {
		sprintf(buffer4, "%s error: cound not read '%s'", fn, argv[1]);
		perror(buffer4);
		exit(1);
	}

	else if (flag == -2) {
		sprintf(buffer4, "%s error: could not read '%s'", fn, argv[2]);
		perror(buffer4);;
		exit(1);
	}

	// Validate input
	flag = checkString(buffer1, buffer2);
	switch(flag){
		case -1:
			sprintf(buffer4, "%s error: key in '%s' is too short", fn, argv[2]);
			perror(buffer4);
			exit(1);
		case -2:
			if(checkChars(buffer1) < 0){
				sprintf(buffer4, "%s error: invalid characters in %s", fn, argv[1]);
				perror(buffer4);
			}
			else if(checkChars(buffer2) < 0){
				sprintf(buffer4, "%s error: invalid characters in %s", fn, argv[2]);
				perror(buffer4);
			}
			else
				exit(1);
		default:
			break;
	}

	// Validate port
	int port = validatePort(argv[3]);
    if(port < 0){
		sprintf(buffer4, "%s error: '%s' is an invalid port", fn, argv[3]);
		perror(buffer4);
            exit(1);
    }

	// Create Socket
	int sockfd = createSocketEnc(port);
	if(sockfd < 0){
		sprintf(buffer4, "%s error: unable to connect on port %d", fn, port);
		perror(buffer4);
		exit(2);
	}

	// Connect to the client
	int sfd = connectClient(sockfd, enc_flag);
	if(sfd < 0){
		sprintf(buffer4, "%s error: unable to connect on port %d", fn, port);
		perror(buffer4);
		exit(2);
	}

	// Transfer Data
	int dataVal = sendData(sockfd, buffer1, buffer2, buffer3);
	switch(dataVal){
		case -1:
			sprintf(buffer4, "%s error: failed to send '%s'", fn, argv[1]);
			perror(buffer4);
			exit(1);
		case -2:
			sprintf(buffer4, "%s error: failed to send '%s'", fn, argv[2]);
			perror(buffer4);
			exit(1);
		case -3:
			sprintf(buffer4, "%s error: failed to receive buffer3 file", fn);
			perror(buffer4);
			exit(1);
		default:
			break;
	}
	
	printf("%s\n", buffer3);
	close(sockfd);
	
	return 0;
}