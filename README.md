# Xavier Jeffy
# Producer-Consumer

# Explanation
My version of the producer/consumer problem uses two separate processes with a shared memory buffer for the 
producer to place items into and for the consumer to print items from. In this case, the size of the buffer 
is 2, and the producer is set to place 10 items into the buffer before exiting. I made my items be characters, 
starting at 'a', that are alphabetically incremented with each iteration, so the consumer prints out a different 
letter with each line. After an item is placed in the buffer, the producer waits for that item to be consumed 
before producing another item. Similarly, the consumer must wait for the producer to place an item into the 
buffer before it consumes. This effectively achieves mutual exclusivity, and it is done with the use of semaphores. 

# The files are compiled using:
gcc producer.c -pthread -lrt -o producer

gcc consumer.c -pthread -lrt -o consumer

# The files are run using:
./producer & ./consumer &

# Example output
Got char a

Got char b

Got char c

Got char d

Got char e

Got char f

Got char g

Got char h

Got char i

Got char j
