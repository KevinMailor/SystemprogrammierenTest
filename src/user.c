#include <pthread.h>
#include "user.h"
#include "clientthread.h"
#include "network.c"

static pthread_mutex_t userLock = PTHREAD_MUTEX_INITIALIZER;
static User *userFront = NULL;
static User *userBack = NULL;



void* NewUser(User *newUser){
	if(userFront == NULL){
		pthread_mutex_lock(&userLock);

		userFront=newUser;
		userFront->prev=newUser;
		userFront->next=newUser;
		
		userBack=newUser;
		userBack->next=newUser;
		userBack->prev=newUser;
		
		pthread_mutex_unlock(&userLock);
	}
	else{
		pthread_mutex_lock(&userLock);
		
		userBack->next = newUser;
		userBack = newUser;
		userBack->next = userFront;

		pthread_mutex_unlock(&userLock);
	}
}


void* DeleteUser(User *delUser){
	User *usertmp = userFront;
	while(	!(delUser == usertmp)	){
		usertmp = usertmp->next;
	}
	pthread_mutex_lock(&userLock);

	usertmp->prev->next=usertmp->next;
	
	pthread_mutex_lock(&userLock);
}	

void* MessageToAllUser(Message *buffer){
	User *user = userFront;
	do{
		pthread_mutex_lock(&userLock);

		networkSend(-1,buffer);
		user = userFront->next;

		pthread_mutex_unlock(&userLock);
	}
	while(user == userFront->prev);

}

//TODO: Implement the functions declared in user.h
