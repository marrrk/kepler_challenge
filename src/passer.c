#include "passer.h"
#include <stdio.h>

//message_t msg_library[10];

message_t* new_message(){
    //check if library is full?
    //if there is space, return new_msg
    //if full return NULL;
    //new_msg.len = 12;
    //msg_library[0] = new_msg;
    bool found = false;

    for (int i = 0; i < 10; i++){
        if (msg_library[i].len == 0) {
            //Message available due to length of current message being zero.
            //message_t new_msg;
            //msg_library[i] = new_msg; //no need to create a new message it is already in the list, just return the pointer!
            found = true;
            msg_library[i].len = 1; //protection in case another gets this message struct at the same time
            return &msg_library[i];
        }

        if (!found) {
            return NULL;
        }

    }

    //should never get here
    return NULL;
}

void delete_message(message_t* msg){
    //set message length to zero so that new thread can use this message struct
    msg->len = 0;
}
