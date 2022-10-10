# Kepler Challenge Question 2

This is my solution to the second question in the Kepler Challenge.
Instructions for building:

1. `make`
2. `make run`

In my solution, I used an array to simulate the message library and by extension memory location. I also created a struct that contains a receiver's ID as well as the message struct in order to keep track of the receiver ID. I made the following assumptions:

1. A message of length 0 indiciates no message in the message struct, and a thread can be allocated that message.
2. Threads can only send and/or receive one message at a time.
3. The memory needed to be handled by my code should be done manually, and not with the use of special libraries.
4. The entire memory (simulated message library) needs to be accessible at any time by any thread in order to find a free message struct. That is not breaking up the memory into smaller sections that different threads have exclusive access to.

I considered using dynamic memory allocation but I decided against it as I felt that the use of the malloc(), calloc(), etc functions would be innefective for both my test machine and my simulated message library. I would not have been able to test a case when there is no available message structs. Additionally, it did not allign with my second assumption.

In receiving and sending messages, I considered a few solutions. I initially had my message library be an array of `message_t` structs however I noticed that being able to pass messages between threads required more information stored. I needed a way to assign the message to a new thread with `destination_id` and also a way to check for `receiver_id`. I considered having a mechanism that has each the message library keep track of which thread is using which message struct and thought of using the thread index of the message library correspond to the thread id. This was because I was trying to keep the message library only contain message structs, however I quickly realised that the solution would mean only one thread can work with a specific message struct at all times. As in the first message struct in the array would always be tied to a thread of ID 1, and so on. Therefore I added another variable to be stored in the message library that would store the receiver of a message. Allowing threads to set an ID of a receiver.
