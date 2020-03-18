// C Program for Message Queue (Reader Process) 
#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 

// structure for message queue 
struct mesg_buffer { 
	long mesg_type; 
	char mesg_text[100]; 
} message; 

int main() 
{ 
	key_t key; 
	int msgid; 

	// ftok to generate unique key 
	key = ftok("progfile", 65); 

	// msgget creates a message queue 
	// and returns identifier 
	msgid = msgget(key, 0666 | IPC_CREAT); 

	while(1){

		// msgrcv to receive message 
		msgrcv(msgid, &message, sizeof(message), 1, 0); 

		// display the message 
		printf("Data Received is : %s \n", message.mesg_text); 
	}
	return 0; 
} 

