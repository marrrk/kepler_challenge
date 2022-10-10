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


//message packet, contains message and receiver
typedef struct {
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
 * @return New message struct to be used by the thread
 */
message_t* new_message();


/**
 * @brief Clears a message struct used by the thread. Allows for a new thread to use message struct
 * 
 * @param msg pointer to the message struct
 */
void delete_message(message_t* msg);

/**
 * @brief Sends a message struct from one thread to another. That is, sets a message to have a receiver
 * 
 * @param destination_id Thread ID of the receiving thread
 * @param msg Pointert o message struct to be sent
 * @return Success or Error Code
 */
int send(uint8_t destination_id, message_t* msg);

/**
 * @brief  Receives a message from the message libarry
 * 
 * @param receiver_id  ID of the receiving thread
 * @param msg Pointer to message being received
 * @return Success or Error Code
 */
int recv(uint8_t receiver_id, message_t** msg);


#endif /* PASSER_H */