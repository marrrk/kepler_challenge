#include "passer.h"
#include <stdio.h>

//message_t msg_library[10];

message_t* new_message(){
    message_t new_msg;
    //check if library is full?
    //if there is space, return new_msg
    //if full return NULL;
    new_msg.len = 12;
    msg_library[0] = new_msg;

    for (int i = 0; i < 10; i++){
        if (msg_library[i].len == 0) {
            //Message available due to length of current message being zero.
            //message_t new_msg;
            //msg_library[i] = new_msg;
            return &msg_library[i];
        }
        else {
            return NULL;
        }

    }

    //return a pointer to the element in array that does has available capacity
    return &msg_library[0];
}

void delete_message(message_t* msg){
    uint8_t* test[3] = {NULL};
    printf("message is: %s\n",*test);
}
