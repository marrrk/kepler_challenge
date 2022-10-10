#include <stdio.h>
#include <stdint.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>
#include "passer.h"

#define THREAD_COUNT 18
pthread_mutex_t Mutex = PTHREAD_MUTEX_INITIALIZER;


// This thread function tests the creation and sending of a message in the messaage library
void *myThreadFun1(void *vargp) {
    int id = *((int*)vargp);
    message_t* msg;
    sleep(1);

    pthread_mutex_lock(&Mutex);
    msg = new_message();                                    //Receiving new message struct
    pthread_mutex_unlock(&Mutex);
    
    if (msg == NULL) {
        pthread_mutex_lock(&Mutex);                           //protects in case of new_message() producing the same memory location
        printf("Message couldn't be created\n");
        pthread_mutex_unlock(&Mutex);
        pthread_exit(NULL);
    } else {
        msg->len = 8;                                      // setting random number as message length
        msg->data[1] = id + 4;                             // setting random number as data

        //sending message
        if (send(18-id, msg) != 0) {
            pthread_mutex_lock(&Mutex);
            printf("Message sending failed\n");
            pthread_mutex_unlock(&Mutex);

        }
    }
        return NULL;
}


// This thread function tests the receiving of new messages. It also tests the deletion of the received messages 
void *myThreadFun2(void *vargp) {
    int id = *((int*)vargp); 
    message_t* msg = 0;
    sleep(2);                                   //waiting for first thread function to complete
    
    if (recv(id, &msg) == 0) {
        pthread_mutex_lock(&Mutex);
        printf("Received message Successfully!\n");
        pthread_mutex_unlock(&Mutex);
        delete_message(msg);                    // Deleting message after successful receipt
    } else {
        pthread_exit(NULL);
    }
    
    return NULL;
}



int main(void){
    int thread_id[THREAD_COUNT];
    pthread_t threads[THREAD_COUNT];
    printf("*******************************************************");
    printf("*******************************************************");
    printf("*******************************************************\n");
    printf("*******************************************************");
    printf("*********Kepler Challenge Question 2 Testing***********");
    printf("*******************************************************\n");
    printf("*******************************************************");
    printf("*******************************************************");
    printf("*******************************************************\n");



    /******** TESTING THE CREATE AND DELETE MESSAGE FUNCTIONS SEQUENTIALLY *************/
    printf("\nStarting with basic bequential test to create and delete a message\n");

    message_t* msg;
    printf("\nCalling new_message()\n");
    msg = new_message();
    
    printf("Value of message length before setting: %d\n",msg->len);
    msg->len = 45;
    printf("Value of message length after setting: %d\n",msg->len);

    printf("Deleting message\n");
    delete_message(msg);

    printf("Value of message length after deleting: %d\n\n",msg->len);

    /**************************************************************************************/
    

    /*************************** TESTING WITH THREADS *************************************/
    printf("*******************************************************");
    printf("******************** Threading Test *******************");
    printf("*******************************************************\n");
    printf("\n");
    
    printf("Created 14 threads to request a message struct from a library of 10 messages\n");
    printf("Therefore expecting four error messages to be created\n");
    printf("\nThen creating 4 more threads to receive data, expecting 4 success messages\n\n");


    for (int i =0; i < 14; i++){
            thread_id[i] = i;
            pthread_create(threads+i, NULL, &myThreadFun1, thread_id+i);
    }

    for (int i = 14; i < THREAD_COUNT; i++){
            thread_id[i] = i;
            pthread_create(threads+i, NULL, &myThreadFun2, thread_id+i);
    }

    for(int j = 0; j < THREAD_COUNT; j++){ 
        if(pthread_join(threads[j], 0)){
            pthread_mutex_lock(&Mutex);
            printf("Problem joining thread %d\n", j);
            pthread_mutex_unlock(&Mutex);
        }
    }
    
    printf("\n");
    printf("*******************************************************");
    printf("*****************End of Threading Test*****************");
    printf("*******************************************************\n");
    printf("\n");    printf("\n\n");
    /****************************************************************************************/

    //printf("Message at message_library[1] is: %d\n", msg_library[1].msg.data[1]);
    /**
    message_t* msg;
    if (recv(3, &msg) == 0) {
        printf("Received message Successfully! Pointer is at %p\n", msg);
        printf("The message received length is: %d\n", msg->len);
        printf("The message received data is: %d\n", msg->data[1]);

    }
    **/
    
    printf("*******************************************************");
    printf("*****************Final Message Library*****************");
    printf("*******************************************************\n");
    printf("\n");

    printf("| Index     |  Message Length   |  Dummy Data at [1]  |   Receiver ID    |\n");
    for (int k = 0; k < LIBRARY_SIZE; k++) {
        printf("| %d         |       %d           |           %d         |       %d          |\n", k, msg_library[k].msg.len, msg_library[k].msg.data[1], msg_library[k].receiver);
    }


    printf("\n");
    printf("*******************************************************");
    printf("*******************************************************");
    printf("*******************************************************\n");
    printf("*******************************************************");
    printf("**************End of Challenge Testing*****************");
    printf("*******************************************************\n");
    printf("*******************************************************");
    printf("*******************************************************");
    printf("*******************************************************\n");
}