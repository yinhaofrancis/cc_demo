#include"CCMath.h"
#include<unistd.h>
#include<pthread.h>
#include<iostream>
#include<signal.h>

int n_thread_is_run = 0;

pthread_mutex_t mutux;

void * thread_run(void* param){
    const char * info = (const char *)param;
    while (n_thread_is_run >= 0){
        usleep(1000 * 900);
        std::cout<<info<<std::endl;
        pthread_mutex_lock(&mutux);
        n_thread_is_run += 1;
        pthread_mutex_unlock(&mutux);
    }
    return 0;
}

void sig_callback(int info){
    std::cout<<"sig  "<<info<<std::endl;
    n_thread_is_run = -99999;
}
int cc::testSignel(){
    pthread_t thread1;
    pthread_t thread2;
    pthread_mutex_init(&mutux,NULL);
    signal(SIGINT,sig_callback);
    pthread_create(&thread1,NULL,thread_run,(void *)"this is a");
    pthread_create(&thread2,NULL,thread_run,(void *)"this is b");
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    pthread_mutex_destroy(&mutux);
    return 0;
}

int cc::add(int a,int b){
    return a + b;
}