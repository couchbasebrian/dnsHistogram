#include <stdio.h>
#include <netdb.h>
#include <time.h>

// How to compile
// gcc dnshistogram.c -lrt -o dnshistogram

// call this function to start a nanosecond-resolution timer
struct timespec timer_start(){
    struct timespec start_time;
    clock_gettime(CLOCK_REALTIME, &start_time);
    return start_time;
}

// call this function to end a timer, returning nanoseconds elapsed as a long
long timer_end(struct timespec start_time){
    struct timespec end_time;
    clock_gettime(CLOCK_REALTIME, &end_time);
    long diffInNanos = end_time.tv_nsec - start_time.tv_nsec;
    return diffInNanos;
}

int main() {

  int numberIterations = 100;

  // Buckets with size 0.01 seconds ( 10000000 nanoseconds )

  long bucketSize = 10000000;

  // number of Buckets

  int numBuckets = 10;

  int counter[numBuckets];

  struct hostent *foo;

  int i = 0;

  for (i = 0; i < numBuckets; i++) {
    counter[i] = 0;
  }

  int others = 0;

  while (numberIterations >= 0) {

  printf("About to do lookup\n");

  struct timespec vartime = timer_start();  // begin a timer called 'vartime'

  foo = gethostbyname("www.google.com");

  long time_elapsed_nanos = timer_end(vartime);

  printf("Time taken (nanoseconds): %ld\n", time_elapsed_nanos);

  printf("After doing lookup\n");

  // This will return a number like 25602923 nanoseconds which is 0.02 seconds

  int bucketNumber = time_elapsed_nanos / bucketSize;

  printf("The bucket number is: %d\n", bucketNumber); 

  if (bucketNumber >= 0) {
    counter[bucketNumber] = counter[bucketNumber] + 1;
  } else {
    others++;
  }

  
  numberIterations--;

  }

  // print histogram

  long b1, b2;

  for (i = 0; i < numBuckets; i++) {
     b1 = i * bucketSize;
     b2 = ((i+1) * bucketSize);
     printf("%10lu - %10lu : %10lu \n", b1, b2, counter[i] );
  }

  printf("Others: %d\n", others);

}

