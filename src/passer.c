#include "passer.h"
#include <stdio.h>

//message_t msg_library[10];

message_t* new_message(){
    //check if library is full?
    //if there is space, return new_msg
    //if full return NULL;
    bool found = false;

    for (int i = 0; i < LIBRARY_SIZE; i++){
        if (msg_library[i].msg.len == 0) {
            //Message available due to length of current message being zero.
            found = true;
            msg_library[i].msg.len = 1; //protection in case another gets this message struct at the same time, maybe mutex fixes it?
            return &msg_library[i].msg;
        }
    }
    if (!found) {
        return NULL;
    }

    //should never get here
    return NULL;
}

void delete_message(message_t* msg){
    //set message length to zero so that different thread can use this message struct
    msg->len = 0;
}

int send(uint8_t destination_id, message_t* msg){
    bool success = false;
    for (int i = 0; i < LIBRARY_SIZE; i++) {
        // Searching for the message pointer in order to set receiver id
        if (msg == &msg_library[i].msg){
            //printf("The message address has been found! setting the destination lcoation\n");
            printf("Message address of message is: %p\n", &msg_library[i].msg);
            msg_library[i].receiver = destination_id;
            success = true;
            return 0;
        }
    }

    if (!success) {
        return 1;
    }
    //
    return 1;
}


//msg is passed by value, meaning a copy of the variable is created in this function specifically.
// need to find a way to pass it by reference :)
int recv(uint8_t receiver_id, message_t* msg){  
    bool success = false;
    for (int i =0 ; i < LIBRARY_SIZE; i++){
        // Searching if any messages are assigned to receiver_id
        if (msg_library[i].receiver == receiver_id){
            printf("msg pointer currently pointing at: %p\n", msg);
            printf("Message to receive pointer: %p\n", &msg_library[i].msg);
            msg = &msg_library[i].msg; //telling the receiver the message
            printf("msg pointer currently pointing at: %p\n", msg);
            success = true;
            return 0;
        }
    }
    if (success) {
        return 0;
    } else {
        return 1;
    }
}
