#include <stdio.h>
#include <stdint.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>
#include "passer.h"

#define THREAD_COUNT 4
pthread_mutex_t Mutex = PTHREAD_MUTEX_INITIALIZER; // One mutex

// A normal C function that is executed as a thread
// when its name is specified in pthread_create()
void *myThreadFun1(void *vargp) {
    int id = *((int*)vargp); //cast void pointer to int 
    message_t* msg;
    sleep(1);

    pthread_mutex_lock(&Mutex); //protects in case of new_message() spitting out the same memory location
    msg = new_message();
    printf("New Message pointer: %p\n", msg);
    pthread_mutex_unlock(&Mutex);
    
    if (msg == NULL) {
        printf("No available message\n");
        pthread_exit(NULL);
    } else {
        //printf("This is the msg pointer: %p\n", msg);
        //printf("Thread %d has new_message\n", id);
        msg->len = 12;
        msg->data[1] = 4;
        //sending message
        if (send(id+2, msg) == 0) {
            printf("Message '%d' at address %p sent successfully!\n", msg->data[1], msg);

        } else {
            printf("Message sending failed\n");
        }
        //if (id % 2 == 1){
        //    delete_message(msg);
       // }
    }
        return NULL;
}


// This thread function tests the receiving of new messages. The receiver IDs are read and printed onto the screen
void *myThreadFun2(void *vargp) {
    int id = *((int*)vargp); //cast void pointer to int 
    message_t* msg = 0;
    sleep(2);
    
    if (recv(id, msg) == 0) {
        printf("Received message Successfully!\n");
        //printf("The message received is: %d\n", msg->len);
    } else {
        printf("No available message\n");
        pthread_exit(NULL);
    }
    
    printf("This is the length value in msg pointer: %d\n", msg->len);
    return NULL;
}


//can make a dummy memory space that is an array of message_t and will test if it's full or not or what?

int main(void){
    int thread_id[THREAD_COUNT];
    pthread_t threads[THREAD_COUNT];
    
    
    printf("Before Threading\n");
    for (int i =0; i < THREAD_COUNT/2; i++){
            thread_id[i] = i;
            pthread_create(threads+i, NULL, &myThreadFun1, thread_id+i);
    }

    for (int i =THREAD_COUNT/2; i < THREAD_COUNT; i++){
            thread_id[i] = i;
            //pthread_create(threads+i, NULL, &myThreadFun2, thread_id+i);
    }

    for(int j = 0; j < 2; j++){  //CHANGE "2" BACK TO THREAD_COUNT WHEN DONE
        if(pthread_join(threads[j], 0)){
            pthread_mutex_lock(&Mutex);
            printf("Problem joining thread %d\n", j);
            pthread_mutex_unlock(&Mutex);
        }
    }
    printf("After Threading\n");

    printf("Message at message_library[1] is: %d\n", msg_library[1].msg.data[1]);

    message_t* msg;
    if (recv(3, msg) == 0) {
        printf("Received message Successfully! Pointer is at %p\n", msg);
        //printf("The message received length is: %d\n", msg->len);
    }

    
   // checking if algorithm works sequentially
   // for(int y = 0; y < 4; y++) {
   //     msg[y] = new_message();
    //    msg[y]->len = 12;
    //}
    

    for (int k = 0; k < LIBRARY_SIZE; k++) {
      //  printf("Index %d has a message length of %d and a message value of %d\n", k, msg_library[k].msg.len, msg_library[k].msg.data[1]);
    }
}