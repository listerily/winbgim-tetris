#include "KeyEventListener.hpp"

#include <conio.h>
#include <cstdio>

void* KeyEventListener::thread_process(void* t)
{
    KeyEventListener* thiz = (KeyEventListener*)t;
    while(true)
    {
        int ch = getch();
        pthread_mutex_lock(&thiz->listener_mutex);
        thiz->keyEventQueue.push(ch);
        pthread_mutex_unlock(&thiz->listener_mutex);
    }
}
KeyEventListener::KeyEventListener()
{
    pthread_t th = pthread_self();
    int thread_ret = pthread_create(&th, NULL, thread_process, this );
    if( thread_ret != 0 ){
        printf( "Failed to create thread!\n");
        return;
    }
    pthread_mutex_init(&listener_mutex,NULL);
    pthread_detach(th);
}
KeyEventListener::~KeyEventListener()
{
    pthread_mutex_destroy(&listener_mutex);
}
int KeyEventListener::readKey()
{
    int result;
    pthread_mutex_lock(&listener_mutex);
    result = keyEventQueue.front();
    keyEventQueue.pop();
    pthread_mutex_unlock(&listener_mutex);
    return result;
}
bool KeyEventListener::isEmpty()
{
    bool result;
    pthread_mutex_lock(&listener_mutex);
    result = keyEventQueue.empty();
    pthread_mutex_unlock(&listener_mutex);
    return result;
}
