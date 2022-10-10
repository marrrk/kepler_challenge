#include "passer.h"
#include <stdio.h>

//message_t msg_library[10];

message_t* new_message(){
    //Search for empty message struct and return it
    //Message struct is deemed empty if the length of the message is 0

    for (int i = 0; i < LIBRARY_SIZE; i++){
        if (msg_library[i].msg.len == 0) {                    //Message available due to length of current message being zero.
           
            msg_library[i].msg.len = 1;                       //protection in case another gets this message struct at the same time, maybe mutex fixes it?
            return &msg_library[i].msg;
        }
    }

    //No message with a length of zero found, therefore no available message struct
    return NULL;
}

void delete_message(message_t* msg){
    msg->len = 0;       //set message length to zero so that different thread can use this message struct
    
    //deleting message data
    for (int i = 0; i< 255; i++){
        msg->data[i] = 0;
    }
}

int send(uint8_t destination_id, message_t* msg){
    for (int i = 0; i < LIBRARY_SIZE; i++) {
        if (msg == &msg_library[i].msg){                  // Searching for the message pointer in order to set receiver id
            msg_library[i].receiver = destination_id;     // Setting Receiver of message
            return 0;
        }
    }
    // Sending of a message was not successfull
    return 1;
}


//msg is passed by value, meaning a copy of the variable is created in this function specifically.
// need to find a way to pass it by reference :)
int recv(uint8_t receiver_id, message_t** msg){  
    for (int i =0 ; i < LIBRARY_SIZE; i++){
        if (msg_library[i].receiver == receiver_id){            // Searching if any messages are assigned to receiver_id
            //printf("msg pointer currently pointing at: %p\n", msg);
            //printf("Message to receive pointer: %p\n", &msg_library[i].msg);
            *msg = &msg_library[i].msg;                         //telling the receiving thread the message
            msg_library[i].receiver = 0;                        //Resetting the Receiver ID
            //printf("msg pointer currently pointing at: %p\n", msg);
            return 0;
        }
    }
    // Message wasn't received
    return 1;
}
