//============================================================================
// Name        : 410_Producer_wait_for_all_consumers_ready_using_Semaphore.cpp
// Author      : 
// Version     :
// Copyright   : Steal this code!
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include "Semaphore.h"

using namespace std;
const int NUMB_THREADS_TO_WAIT_ON = 5;

Semaphore s(-NUMB_THREADS_TO_WAIT_ON);
mutex m;

void ts_out(string info){
	lock_guard<mutex> lck(m);
	cout<<info<<endl;
}

void producer(int numbcounts) {	
	s.signal();  //take care of the decrement associated with this thread
	
	//will wait until all 5 threads have signaled and then proceed
	s.wait();
}

void consumer(int id) {
	//will wait until all 5 threads have signaled and then proceed
	s.signal();
}

int main() {
	thread t_consumer1(consumer, 1);
	thread t_consumer2(consumer, 2);
	thread t_consumer3(consumer, 3);
	thread t_consumer4(consumer, 4);
	thread t_consumer5(consumer, 5);
	thread t_producer(producer, 10);

	t_consumer1.join();
	t_consumer2.join();
	t_consumer3.join();
	t_consumer4.join();
	t_consumer5.join();
	t_producer.join();

	return 0;
}
