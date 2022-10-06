#ifndef PASSER_H
#define PASSER_H


//Including necessary headers
#include <stdint.h>
#include <stddef.h>

//Message type Declaration
typedef struct {
    uint8_t len;
    uint8_t data[255];
} message_t;

//Dummy memory space used for testing
message_t msg_library[10];


//Function Declarations
message_t* new_message();
void delete_message(message_t* msg);
int send(uint8_t destination_id, message_t* msg);
int recv(uint8_t receiver_id, message_t* msg);



#endif /* PASSER_H */