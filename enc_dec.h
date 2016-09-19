// Dane Schoonover
// Date: 5 June 2016
// Description: Header file 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdint.h>


int getText(char *file1, char *file2, char *data1, char *data2);
int sendData(int sockfd, char *data1, char *data2, char *output);
char convertNumbers(int);
int convertLetters(char);
void encode(char*, char*, char*);
void decode(char*, char*, char*);
int sendMsg(int sockfd, char *msg);
int recvMsg(int, char*, unsigned);
int serverTransfer(int client_sock, int flag);
int connectClient(int sockfd, char sendFlag);
int connectServer(int sockfd, char sendFlag);
int checkString(char*, char*);
unsigned sendNum(int sockfd, unsigned num);
unsigned recvNum(int sockfd);
int readFile(char*, char*);
int checkChars(char *string1);
int createSocketDec(int port);
int createSocketDecD(int port);
int createSocketEnc(int port);
int createSocketEncD(int port);
void getChildPID(int sigNum);
int validatePort(char *input);
void usage1();
void usage2(char *cmd);





// getText reads two input files and copies their data to a corresponding string
int getText(char *file1, char *file2, char *data1, char *data2){
	int flag;

	// File 1
	flag = readFile(file1, data1);
	if(flag < 0){
		return -1;
	}

	// File 2
	flag = readFile(file2, data2);
	
	if(flag < 0){
		return -2;
	
	}
	
	return 0;
}


// sendData transfers data between the client and server
int sendData(int sockfd, char *data1, char *data2, char *output){


	// Send input 1
	int temp = sendNum(sockfd, strlen(data1) + 1);
	if (temp < 0){
		return -4;
	}
	temp = sendMsg(sockfd, data1);
	if (temp < 0){
		return -1;
	}


	// Send input 2
	temp = sendNum(sockfd, strlen(data2) + 1);
	if (temp < 0){
		return -4;
	}

	temp = sendMsg(sockfd, data2);
	
	if (temp < 0){
		return -2;
	}

	// Receive ouput
	unsigned size = recvNum(sockfd);
	
	if (size < 0){
		return -4;
	}
	
	temp = recvMsg(sockfd, output, size);
	
	if (temp < 0){
		return -3;
	}

	return 0;
}


// convertLetters converts ascii letter chars to numbers
int convertLetters(char letter){
	switch (letter){
	case 'A':
		return 0;
		break;
	case 'B':
		return 1;
		break;
	case 'C':
		return 2;
		break;
	case 'D':
		return 3;
		break;
	case 'E':
		return 4;
		break;
	case 'F':
		return 5;
		break;
	case 'G':
		return 6;
		break;
	case 'H':
		return 7;
		break;
	case 'I':
		return 8;
		break;
	case 'J':
		return 9;
		break;
	case 'K':
		return 10;
		break;
	case 'L':
		return 11;
		break;
	case 'M':
		return 12;
		break;
	case 'N':
		return 13;
		break;
	case 'O':
		return 14;
		break;
	case 'P':
		return 15;
		break;
	case 'Q':
		return 16;
		break;
	case 'R':
		return 17;
		break;
	case 'S':
		return 18;
		break;
	case 'T':
		return 19;
		break;
	case 'U':
		return 20;
		break;
	case 'V':
		return 21;
		break;
	case 'W':
		return 22;
		break;
	case 'X':
		return 23;
		break;
	case 'Y':
		return 24;
		break;
	case 'Z':
		return 25;
		break;
	case ' ':
		return 26;
		break;
	default:
		return -1;
	}
}
// convertNumbers converts numbers to letters
char convertNumbers(int number){
	switch (number){
	case 0:
		return 'A';
		break;
	case 1:
		return 'B';
		break;
	case 2:
		return 'C';
		break;
	case 3:
		return 'D';
		break;
	case 4:
		return 'E';
		break;
	case 5:
		return 'F';
		break;
	case 6:
		return 'G';
		break;
	case 7:
		return 'H';
		break;
	case 8:
		return 'I';
		break;
	case 9:
		return 'J';
		break;
	case 10:
		return 'K';
		break;
	case 11:
		return 'L';
		break;
	case 12:
		return 'M';
		break;
	case 13:
		return 'N';
		break;
	case 14:
		return 'O';
		break;
	case 15:
		return 'P';
		break;
	case 16:
		return 'Q';
		break;
	case 17:
		return 'R';
		break;
	case 18:
		return 'S';
		break;
	case 19:
		return 'T';
		break;
	case 20:
		return 'U';
		break;
	case 21:
		return 'V';
		break;
	case 22:
		return 'W';
		break;
	case 23:
		return 'X';
		break;
	case 24:
		return 'Y';
		break;
	case 25:
		return 'Z';
		break;
	case 26:
		return ' ';
		break;
	default:
		return '!';
	}
}

// encodes plaintext with the *key and stores it in *cipher
void encode(char *plainText, char *key, char *cipher){
	int size, i, temp1, temp2, mod;
	size = strlen(plainText);

	// Conversion
	for (i = 0; i < size; i++){
		temp1 = convertLetters(plainText[i]);
		temp2 = convertLetters(key[i]);
		
		mod = temp1 + temp2;

		// Account for > 27
		if (mod > 27){
			mod = mod - 27;
		}
		mod = mod % 27;

		// Convert
		cipher[i] = convertNumbers(mod);
	}
}

// decodes the *cipher with the *key and stores it in *plainText
void decode(char *cipher, char *key, char *plainText){
	int size, i, temp1, temp2, mod;
	size = strlen(cipher);

	for (i = 0; i < size; i++){
		temp1 = convertLetters(key[i]);
		temp2 = convertLetters(cipher[i]);

		mod = temp2 - temp1;

		if (mod < 0){
			mod = mod + 27;
		}

		mod = mod % 27;

		// convert
		plainText[i] = convertNumbers(mod);
	}
}


// connectClient ensures a successful socket connection to the server by writing a test char to a socket
int connectClient(int sockfd, char sendFlag){
	
	char receiveFlag;

	// Conduct connection
	int temp = write(sockfd, &sendFlag, 1);
	if(temp < 0){
		return -1;
	}
	temp = read(sockfd, &receiveFlag, 1);

	if(temp < 0){
		return -1;
	}
	
	// Connection successful
	else if(receiveFlag == sendFlag){
		return 0;
	}
	
	else {
		return -2;
	}
}

// connectServer ensures a successful socket connecticon to the client by writing a test char to a socket
int connectServer(int sockfd, char sendFlag){
	char receiveFlag;

	// Conduct connection
	int temp = read(sockfd, &receiveFlag, 1);

	if(temp < 0){
		return -1;
	}
	// send the return handshake byte
	temp = write(sockfd, &sendFlag, 1);

	if(temp < 0){
		return -1;
	}
	
	// Connection successful
	else if(sendFlag == receiveFlag){
		return 0;
	}

	else {
		return -2;
	}
}

// recvMsg receives a message thru a socket
int recvMsg(int sockfd, char *output, unsigned size){
	char buffer[99999];
	unsigned temp;
	unsigned bytes = 0;


	while (bytes < size){
		temp = read(sockfd, buffer + bytes, size - bytes);
		bytes += temp;
		if (temp < 0){
			return -1;
		}
		else if (temp == 0){
			bytes = size - bytes;
		}
	}
	strncpy(output, buffer, size);
	return 0;
}

// sendMsg sends data thru a socket
int sendMsg(int sockfd, char *data){
	unsigned temp;
	unsigned size = strlen(data) + 1;
	unsigned bytes = 0;

	// Send until complete
	while (bytes < size) {
		temp = write(sockfd, data + bytes, size - bytes);
		
		// Count bytes
		bytes += temp;

		if (temp < 0){
			return -1;
		}

		else if (temp == 0){
			bytes = size - bytes;
		}
	}
	return 0;
}



// sendNum sends number thru a socket
unsigned sendNum(int sockfd, unsigned number){
	unsigned num = number;
	
	// Send the number
	int temp = write(sockfd, &num, sizeof(unsigned));
	if(temp < 0){
		return -1;
	}
	else return 0;
}

// recvNum receives a number thru a socket
unsigned recvNum(int sockfd){
	unsigned num;
	int temp = read(sockfd, &num, sizeof(unsigned));
	if(temp < 0){
		return -1;
	}
	else return num;
}

// serverTransfer encodess or decodes a message based on the flag passed in, and 
// returns the newly encoded or decoded message
int serverTransfer(int client_sock, int flag){

	// Data 1
	unsigned size = recvNum(client_sock);
	if(size < 0){
		return -4;
	}

	char data1[size];
	bzero(data1, size);

	int temp = recvMsg(client_sock, data1, size);
    if(temp < 0){
            return -1;
    }


	// Data 2
	size = recvNum(client_sock);
	if(size < 0){
		return -4;
	}
	char data2[size];
	bzero(data2, size);
	temp = recvMsg(client_sock, data2, size);
    if(temp < 0){
            return -2;
    }

	char output[strlen(data1)+1];
	bzero(output, strlen(data1)+1);

	

	// Encode requested
	if(flag == 1){
		encode(data1, data2, output);
	}
	
	// Decode requested
	else {
		decode(data1, data2, output);
	}

	// Respond to request
	temp = sendNum(client_sock, strlen(output)+1);
	if(temp < 0){
		return -4;
	}

	temp = sendMsg(client_sock, output);
	if(temp < 0){
		return -3;
	}
	return 0;
}


// readFile reads a file into a string
int readFile(char *fileName, char *string){

	// open the file
	FILE *fileptr;
	fileptr = fopen(fileName, "r");
	if(fileptr == NULL){
		return -1;
	}

	if(fgets(string, 99999, fileptr) == NULL){
		return -1;
	}

	// Strip newline
	int newL = strlen(string) - 1;
	if (string[newL] == '\n') {
		string[newL] = '\0';
	}
	return 0;
}

// checks for valid characters and string size match
int checkString(char *str1, char *str2){
	int size1 = strlen(str1);
	int size2 = strlen(str2);

	// Confirm size requirement
	if(size1 > size2){
		return -1;
	}

	// Confirm characters are valid
	else if(checkChars(str1) < 0){
		return -2;
	}

	else if(checkChars(str2) < 0){
		return -2;
	}

	else
		return 1;
}


// checks a string for valid characters
int checkChars(char *string1){
	int i;
	for(i = 0; i < strlen(string1); i++){
		if(convertLetters(string1[i]) < 0){
			return -1;
		}
	}

	return 0;
}


// Creates a socket with the supplied port
int createSocketDec(int port){
	int sockfd;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		return -1;
	}

	struct hostent *server;
	struct sockaddr_in serverAddress;

	server = gethostbyname("localhost");
	if (server == NULL){
		return -1;
	}

	// IP info
	serverAddress.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serverAddress.sin_addr.s_addr, server->h_length);
	serverAddress.sin_port = htons(port);

	if (connect(sockfd, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0){
		return -1;
	}

	return sockfd;
}


// Creates a socket with the supplied port
int createSocketEnc(int port){
	int sockfd;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		return -1;
	}
	struct hostent *server;
	struct sockaddr_in serverAddress;

	server = gethostbyname("localhost");
	if (server == NULL){
		return -1;
	}

	// IP info
	serverAddress.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serverAddress.sin_addr.s_addr, server->h_length);
	serverAddress.sin_port = htons(port);

	if (connect(sockfd, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0){
		return -1;
	}

	return sockfd;
}


// Creates a server socket with the supplied port
int createSocketDecD(int port){
	int sockfd;
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		return -1;
	}
	// IP info
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = INADDR_ANY;
	
	if (bind(sockfd, (struct sockaddr *) &server, sizeof(server)) < 0){
		return -1;
	}
	
	else if (listen(sockfd, 10) < 0){
		return -1;
	}
	else
		return sockfd;
}



// Creates a socket with the supplied port
int createSocketEncD(int port){
	int sockfd;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		return -1;
	}

	// IP info
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = INADDR_ANY;

	if (bind(sockfd, (struct sockaddr *) &server, sizeof(server)) < 0){
		return -1;
	}

	else if (listen(sockfd, 10) < 0){
		return -1;
	}
	else
		return sockfd;
}

// getChildPID gets the child process PID
void getChildPID(int sigNum){
	pid_t pid;
	int status;
	pid = waitpid(-1, &status, WNOHANG);
}

// Checks if number is > 0 (i.e. a port)
int validatePort(char *num){
	int port = atoi(num);
	if (port < 0){
		return -1;
	}

	else
		return port;
}

// Tells user how to use the program
void usage1(){
	printf("usage:\n %% %s plaintext [key] [port]\n");
}

// Tells user how to use the program
void usage2(char *cmd){
	printf("usage:\n %% %s listen_port", cmd);
}