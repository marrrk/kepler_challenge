#ifndef PASSER_H
#define PASSER_H


//Including necessary headers
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

// Constants
#define LIBRARY_SIZE 10


//Message type Declaration
typedef struct {
    uint8_t len;
    uint8_t data[255];
} message_t;

//message packet
typedef struct {
    uint8_t handler;
    uint8_t receiver;
    message_t msg;
} msg_packet_t;

//Dummy memory space used for testing
msg_packet_t msg_library[LIBRARY_SIZE];


//Function Declarations
/**
 * @brief Traverses through msg_library to find an empty message struct.
 * If msg_struct available, then returns memory address to be used by thread
 * 
 * @return message_t* 
 */
message_t* new_message();


/**
 * @brief 
 * 
 * @param msg 
 */
void delete_message(message_t* msg);

/**
 * @brief 
 * 
 * @param destination_id 
 * @param msg 
 * @return int 
 */
int send(uint8_t destination_id, message_t* msg);

/**
 * @brief 
 * 
 * @param receiver_id 
 * @param msg 
 * @return int 
 */
int recv(uint8_t receiver_id, message_t* msg);



#endif /* PASSER_H */