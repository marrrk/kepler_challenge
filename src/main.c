#include <stdio.h>
#include <stdint.h>
#include "passer.h"

//can make a dummy memory space that is an array of message_t and will test if it's full or not or what?

int main(void){
    message_t* msg;
    msg = new_message();
    printf("This is the msg piinter: %p\n", msg);
    printf("This is the value in msg pointer: %d\n", msg->len);

    delete_message(msg);
}