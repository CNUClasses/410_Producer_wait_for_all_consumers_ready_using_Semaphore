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
	if (count < 0)
		cv.wait(mlk);
	
	cout<<"producer Done Waiting"<<endl;
}
void Semaphore::signal() {
	unique_lock<mutex> mlk(m);
	count++;
	if (count <= 0)
		cv.notify_one();
	cout<<"Consumer ready"<<endl;
}

