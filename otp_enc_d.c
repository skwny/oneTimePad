// Dane Schoonover
// Date: 5 June 2016
// Description: This program encodes the plaintext that it receives with the key that it receives.
#include "enc_dec.h"
#include <stdio.h>
#include <signal.h>
// otp_enc_d filename
#define fn "otp_enc_d"
// Encode flag
#define enc_flag '^'
#define TRUTHY 1


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
		sprintf(buffer1, "%s error: port %s is invalid", fn, argv[1]);
		perror(buffer1);
		exit(1);
	}
	
	// Create socket
	int sockfd = createSocketEncD(port);
	if(sockfd < 0){
		sprintf(buffer1, "%s error: error listening on port %d", fn, port);
		perror(buffer1);
		exit(1);
	}

	// Listen for connections
	while(1){
		int csockfd = accept(sockfd, NULL, NULL);

		if(csockfd < 0){
			sprintf(buffer1, "%s error: failed accepting connection", fn);
			perror(buffer1);
			close(csockfd);
		}

		else {
			pid = fork();

			if(pid < 0){
				sprintf(buffer1, "%s error: failed fork", fn);
				perror(buffer1);
				exit(1);
			}

			// In the child
			else if(pid == 0){
				
				int sfd = connectServer(csockfd, enc_flag);

				if(sfd < 0){
					close(csockfd);
					_exit(0);
				}

				// Transfer data
				int st = serverTransfer(csockfd, TRUTHY);
				switch(st){
					case -1:
						sprintf(buffer1, "%s error: failed to receive input1", fn);
						perror(buffer1);
						close(csockfd);
						break;
					case -2:
						sprintf(buffer1, "%s error: failed to receive input2", fn);
						perror(buffer1);
						close(csockfd);
						break;
					case -3:
						sprintf(buffer1, "%s error: failed to send output", fn);
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