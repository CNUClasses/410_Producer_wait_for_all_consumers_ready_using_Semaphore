/*
 * Semaphore.cpp
 *
 *  Created on: Nov 8, 2017
 *      Author: keith
 */
#include <iostream>
#include "Semaphore.h"
using namespace std;

Semaphore::Semaphore(int cnt) :
		count(cnt) {
}
Semaphore::~Semaphore() {
}

void Semaphore::wait() {
	unique_lock<mutex> mlk(m);
	count--;
	while (count < 0)
		cv.wait(mlk);
	
	cout<<"producer Done Waiting, count is "<<count<<endl;
}
void Semaphore::signal() {
	{
		unique_lock<mutex> mlk(m);
		count++;
		cout<<"Consumer ready"<<endl;
	}
	cv.notify_all();
}

