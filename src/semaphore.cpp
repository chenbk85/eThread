#include "semaphore.h"

semaphore::semaphore(int initialValue){
	this->value = initialValue;
}

void semaphore::wait(void){
	sighold(SIGALRM);
	this->value -= 1;
	if(this->value < 0){
		getRunningThread()->state = BLOCKED;
		this->waitQueue.push(getRunningThread());
		sigrelse(SIGALRM);
		raise(SIGALRM);
	}
	else{
		sigrelse(SIGALRM);
	}
}

void semaphore::signal(void){
	sighold(SIGALRM);
	this->value += 1;
	if(this->value < 0){
		this->waitQueue.front()->state = RUNNABLE;
		this->waitQueue.pop();
	}
	sigrelse(SIGALRM);
}
