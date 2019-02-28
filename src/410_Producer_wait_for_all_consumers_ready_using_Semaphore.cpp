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
const int NUMB_CONSUMERS = 5;
const int NUMB_PRODUCERS = 1;

//initialize to neg number
Semaphore s(-(NUMB_CONSUMERS-NUMB_PRODUCERS) );
mutex m_cout;

void producer(int numbcounts) {	
	//will wait until all 5 threads have signaled and then proceed
	s.wait();

	//do work here knowing all threads have started
	unique_lock<mutex> mlk(m_cout);
	cout<<"Producer proceeding now that consumers ready"<<endl;
}

void consumer(int id) {
	//will wait until all 5 threads have signaled and then proceed
	s.signal();

	unique_lock<mutex> mlk(m_cout);
	cout<<"Consumer "<<id<< " ready"<<endl;
}

int main() {
	thread t_producer(producer, 10);
	thread t_consumer1(consumer, 1);
	thread t_consumer2(consumer, 2);
	thread t_consumer3(consumer, 3);
	thread t_consumer4(consumer, 4);
	thread t_consumer5(consumer, 5);

	t_consumer1.join();
	t_consumer2.join();
	t_consumer3.join();
	t_consumer4.join();
	t_consumer5.join();
	t_producer.join();

	return 0;
}
