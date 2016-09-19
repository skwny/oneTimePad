// Dane Schoonover
// Date: 5 June 2016
// Description: This program decodes the cipher with the given key.
#include "enc_dec.h"
#include <stdio.h>
#include <signal.h>
// otp_dec filename
#define fn "otp_dec_d"
// Decode flag
#define dec_flag '#'
#define FALSY 	0


int main(int argc, char *argv[]){
	
	// Catch signal
	signal(SIGCHLD, getChildPID);

	char buffer1[256];
	int pid;
	int status;

	// Validate args
	if(argc < 2 || argc > 2){
		usage2(fn);
		exit(1);
	}

	// Validate port
	int port = validatePort(argv[1]);
	if(port < 0){
		sprintf(buffer1, "error: %s port %s is invalid", fn, argv[1]);
		perror(buffer1);
		exit(1);
	}
	
	// Create socket
	int sockfd = createSocketDecD(port);
	if(sockfd < 0){
		sprintf(buffer1, "error: %s error listening on port %d", fn, port);
		perror(buffer1);
		exit(1);
	}
	
	// Listen for connections
	while(1){
		int csockfd = accept(sockfd, NULL, NULL);

		if(csockfd < 0){
			sprintf(buffer1, "error: %s failed accepting connection", fn);
			perror(buffer1);
			close(csockfd);
		}

		else {
			pid = fork();

			if(pid < 0){
				sprintf(buffer1, "error: %s failed fork", fn);
				perror(buffer1);
				exit(1);
			}

			// In the child
			else if(pid == 0){

				// Connect to the client
				int sfd = connectServer(csockfd, dec_flag);

				if(sfd < 0){
					close(csockfd);
					_exit(0);
				}

				// Transfer Data
				int st = serverTransfer(csockfd, FALSY);
				switch(st){
					case -1:
						sprintf(buffer1, "error: %s  input1 failed", fn);
						perror(buffer1);
						close(csockfd);
						break;
					case -2:
						sprintf(buffer1, "error: %s input2 failed", fn);
						perror(buffer1);
						close(csockfd);
						break;
					case -3:
						sprintf(buffer1, "error: %s output failed", fn);
						perror(buffer1);
						close(csockfd);
						break;
					default:
						close(csockfd);
						_exit(0);
				}
			}
			
			// In the parent
			else {
				close(csockfd);
			}
		}
	}
	return 0;
}